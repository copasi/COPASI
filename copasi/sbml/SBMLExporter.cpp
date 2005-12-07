/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/Attic/SBMLExporter.cpp,v $
   $Revision: 1.72 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/12/07 11:02:42 $
   End CVS Header */

#include <math.h>
#include <list>

#include <algorithm>

#include "copasi.h"
#include "report/CKeyFactory.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CVersion.h"
#include "utilities/CProcessReport.h"

#include "SBMLExporter.h"
#include "ConverterASTNode.h"
#include "UnitConversionFactory.hpp"

#include "utilities/CCopasiTree.h"

#include "function/CFunctionDB.h"

#include "sbml/Unit.h"
#include "sbml/UnitDefinition.h"
#include "sbml/UnitKind.h"
#include "sbml/SBMLDocument.h"
#include "sbml/SBMLWriter.h"

#include "sbml/ModifierSpeciesReference.h"
#include "sbml/SpeciesReference.h"
#include "sbml/FunctionDefinition.h"
#include "sbml/Event.h"
#include "xml/CCopasiXMLInterface.h"

#include <fstream>

const char* SBMLExporter::HTML_HEADER = "<body xmlns=\"http://www.w3.org/1999/xhtml\">";

const char* SBMLExporter::HTML_FOOTER = "</body>";

/**
 ** Constructor for the exporter.
 */
SBMLExporter::SBMLExporter(): sbmlDocument(NULL), mpIdSet(NULL), mpExportHandler(NULL), mExportExpressions(false)
{
  this->mpIdSet = new std::set<std::string>;
}

/**
 ** Destructor for the exporter.
 */
SBMLExporter::~SBMLExporter()
{
  pdelete(this->mpIdSet);
}

/**
 ** This method takes a copasi CModel object, creates an SBMLDocument from
 ** it and writes it to a file. The filename is given as the second
 ** argument to the function. The function return "true" on success and
 ** "false" on failure.
 */
bool SBMLExporter::exportSBML(CModel* copasiModel, std::string sbmlFilename, bool overwriteFile, int sbmlLevel, int sbmlVersion)
{
  this->mHandledSBMLObjects.clear();
  this->mpCopasiModel = copasiModel;
  /* create the SBMLDocument from the copasi model */
  this->createSBMLDocumentFromCModel(copasiModel, sbmlLevel, sbmlVersion);
  this->removeUnusedObjects();
  if (this->sbmlDocument->getModel() != NULL)
    {
      SBMLWriter* writer = new SBMLWriter();

      writer->setProgramName("COPASI");
      writer->setProgramVersion(CCopasiDataModel::Global->getVersion()->getVersion().c_str());

      /* check if the file already exisits.
         If yes, write if overwrite is true, 
         else create an appropriate  CCopasiMessage. */
      std::ifstream testInfile(sbmlFilename.c_str(), std::ios::in);
      if (testInfile && !overwriteFile)
        {
          // create a CCopasiMessage with the appropriate error
          CCopasiMessage(CCopasiMessage::ERROR, MCDirEntry + 1, sbmlFilename.c_str());
          return false;
        }
      /* write the document to a file */
      bool returnValue = writer->write(*this->sbmlDocument, sbmlFilename);
      pdelete(writer);
      return returnValue;
    }
  else
    {
      /* if no SBMLDocument could be created return false */
      return false;
    }
}

/**
 **  This method takes a copasi CModel object and generates a SBMLDocument
 ** object from it.
 ** Optionally the method takes two integers that specify the level and the
 ** version number of the SBMLDocument that will be generated.
 */
SBMLDocument* SBMLExporter::createSBMLDocumentFromCModel(CModel* copasiModel, int sbmlLevel, int sbmlVersion)
{
  if (mpExportHandler)
    {
      mStep = 0;
      mTotalSteps = 6;
      mpExportHandler->setName("SBML Export");
      mHStep = mpExportHandler->addItem("Exporting model to SBML...",
                                        CCopasiParameter::UINT,
                                        & mStep,
                                        &mTotalSteps);
    }

  this->sbmlDocument = CCopasiDataModel::Global->getCurrentSBMLDocument();
  if (!this->sbmlDocument)
    {
      /* create a new document object */
      this->sbmlDocument = new SBMLDocument();
    }
  this->sbmlDocument->setLevel(sbmlLevel);
  this->sbmlDocument->setVersion(sbmlVersion);
  /* create the model object from the copasi model */
  Model* sbmlModel = this->createSBMLModelFromCModel(copasiModel);
  if (this->sbmlDocument->getModel() != sbmlModel)
    {
      this->sbmlDocument->setModel(sbmlModel);
    }

  if (mpExportHandler)
    {
      mStep = 6;
      if (!mpExportHandler->progress(mHStep)) return false;
    }
  this->createFunctionDefinitions();
  if (mpExportHandler)
    {
      mpExportHandler->finish(mHStep);
    }
  return this->sbmlDocument;
}

/**
 ** This method taked a copasi CModel and generates a SBML Model object
 **  which is returned. On failure NULL is returned.
 */
Model* SBMLExporter::createSBMLModelFromCModel(CModel* copasiModel)
{
  unsigned C_INT32 step = 0, totalSteps, hStep;
  Model* sbmlModel = NULL;
  std::map<CCopasiObject*, SBase*>& copasi2sbmlmap = CCopasiDataModel::Global->getCopasi2SBMLMap();
  std::map<CCopasiObject*, SBase*>::const_iterator pos = copasi2sbmlmap.find(copasiModel);
  if (pos != copasi2sbmlmap.end())
    {
      sbmlModel = dynamic_cast<Model*>(pos->second);
      assert(sbmlModel);
    }
  else
    {
      /* create a new model object */
      sbmlModel = new Model();
      copasi2sbmlmap[copasiModel] = sbmlModel;
      sbmlModel->setId(copasiModel->getKey().c_str());
    }
  this->mHandledSBMLObjects.push_back(sbmlModel);
  if (this->mpIdSet) pdelete(this->mpIdSet);
  this->mpIdSet = SBMLExporter::createIdSet(sbmlModel);
  if (!copasiModel->getObjectName().empty())
    {
      sbmlModel->setName(copasiModel->getObjectName().c_str());
    }
  if ((!copasiModel->getComments().empty()) && !(this->isEmptyString(copasiModel->getComments())))
    {
      sbmlModel->setNotes((SBMLExporter::HTML_HEADER +
                           CCopasiXMLInterface::encode(copasiModel->getComments()) + SBMLExporter::HTML_FOOTER).c_str());
    }
  /* if the copasi volume unit does not correspond to the default SBML volume
  ** unit, we have to create a UnitDefinition and make it the default in the
  ** SBML model.
  */
  if (!(copasiModel->getVolumeUnitEnum() == CModel::l))
    {
      UnitDefinition* uDef = this->createSBMLVolumeUnitDefinitionFromCopasiVolumeUnit(copasiModel->getVolumeUnitEnum());
      if (sbmlModel->getUnitDefinition("volume"))
        {
          if (!UnitConversionFactory::areEqual(*sbmlModel->getUnitDefinition("volume"), *uDef))
            {
              ListOf& list = sbmlModel->getListOfUnitDefinitions();
              unsigned int i = list.getNumItems();
              for (; i > 0;--i)
                {
                  UnitDefinition* uDef = dynamic_cast<UnitDefinition*>(list.get(i - 1));
                  if (uDef && uDef->getId() == "volume")
                    {
                      list.remove(i - 1);
                      pdelete(uDef);
                      break;
                    }
                }
              sbmlModel->addUnitDefinition(*uDef);
            }
        }
      else
        {
          sbmlModel->addUnitDefinition(*uDef);
        }
    }
  /* if the copasi time unit does not correspond to the default SBML time
  ** unit, we have to create a UnitDefinition and make it the default in the
  ** SBML model.
  */
  if (!(copasiModel->getTimeUnitEnum() == CModel::s))
    {
      UnitDefinition* uDef = this->createSBMLTimeUnitDefinitionFromCopasiTimeUnit(copasiModel->getTimeUnitEnum());
      if (sbmlModel->getUnitDefinition("time"))
        {
          if (!UnitConversionFactory::areEqual(*sbmlModel->getUnitDefinition("time"), *uDef))
            {
              ListOf& list = sbmlModel->getListOfUnitDefinitions();
              unsigned int i = list.getNumItems();
              for (; i > 0;++i)
                {
                  UnitDefinition* uDef = dynamic_cast<UnitDefinition*>(list.get(i - 1));
                  if (uDef->getId() == "time")
                    {
                      list.remove(i - 1);
                      pdelete(uDef);
                      break;
                    }
                }
              sbmlModel->addUnitDefinition(*uDef);
            }
        }
      else
        {
          sbmlModel->addUnitDefinition(*uDef);
        }
    }
  /* if the copasi quantity unit does not correspond to the default SBML
  ** substance
  ** unit, we have to create a UnitDefinition and make it the default in the
  ** SBML model.
  */
  if (!(copasiModel->getQuantityUnitEnum() == CModel::Mol))
    {
      UnitDefinition* uDef = this->createSBMLSubstanceUnitDefinitionFromCopasiQuantityUnit(copasiModel->getQuantityUnitEnum());
      if (sbmlModel->getUnitDefinition("substance"))
        {
          if (!UnitConversionFactory::areEqual(*sbmlModel->getUnitDefinition("substance"), *uDef))
            {
              ListOf& list = sbmlModel->getListOfUnitDefinitions();
              unsigned int i = list.getNumItems();
              for (; i > 0;++i)
                {
                  UnitDefinition* uDef = dynamic_cast<UnitDefinition*>(list.get(i - 1));
                  if (uDef->getId() == "substance")
                    {
                      list.remove(i - 1);
                      pdelete(uDef);
                      break;
                    }
                }
              sbmlModel->addUnitDefinition(*uDef);
            }
        }
      else
        {
          sbmlModel->addUnitDefinition(*uDef);
        }
    }
  /* create all compartments */
  unsigned int counter, iMax = copasiModel->getCompartments().size();
  if (mpExportHandler)
    {
      mStep = 1;
      mpExportHandler->progress(mHStep);
      totalSteps = iMax;
      step = 0;
      hStep = mpExportHandler->addItem("Creating compartments...",
                                       CCopasiParameter::UINT,
                                       & step,
                                       &totalSteps);
    }
  for (counter = 0; counter < iMax; counter++)
    {
      Compartment* sbmlCompartment = this->createSBMLCompartmentFromCCompartment(copasiModel->getCompartments()[counter]);
      if (!sbmlModel->getCompartment(sbmlCompartment->getId()))
        {
          sbmlModel->addCompartment(*sbmlCompartment);
        }
      ++step;
      if (mpExportHandler && !mpExportHandler->progress(hStep)) return false;
    }
  /* create all metabolites */
  iMax = copasiModel->getMetabolites().size();
  if (mpExportHandler)
    {
      mpExportHandler->finish(hStep);
      mStep = 2;
      mpExportHandler->progress(mHStep);
      totalSteps = iMax;
      step = 0;
      hStep = mpExportHandler->addItem("Creating species...",
                                       CCopasiParameter::UINT,
                                       & step,
                                       &totalSteps);
    }
  for (counter = 0; counter < iMax; counter++)
    {
      Species* sbmlSpecies = this->createSBMLSpeciesFromCMetab(copasiModel->getMetabolites()[counter]);
      if (!sbmlModel->getSpecies(sbmlSpecies->getId()))
        {
          sbmlModel->addSpecies(*sbmlSpecies);
        }
      ++step;
      if (mpExportHandler && !mpExportHandler->progress(hStep)) return false;
    }
  /* create all global parameters */
  iMax = copasiModel->getModelValues().size();
  if (mpExportHandler)
    {
      mpExportHandler->finish(hStep);
      mStep = 3;
      mpExportHandler->progress(mHStep);
      totalSteps = iMax;
      step = 0;
      hStep = mpExportHandler->addItem("Creating global parameters...",
                                       CCopasiParameter::UINT,
                                       & step,
                                       &totalSteps);
    }
  for (counter = 0; counter < iMax; counter++)
    {
      Parameter* sbmlParameter = this->createSBMLParameterFromCModelValue(copasiModel->getModelValues()[counter]);
      if (!sbmlModel->getParameter(sbmlParameter->getId()))
        {
          sbmlModel->addParameter(*sbmlParameter);
        }
      ++step;
      if (mpExportHandler && !mpExportHandler->progress(hStep)) return false;
    }
  /* create all reactions */
  iMax = copasiModel->getReactions().size();
  if (mpExportHandler)
    {
      mpExportHandler->finish(hStep);
      mStep = 4;
      mpExportHandler->progress(mHStep);
      totalSteps = iMax;
      step = 0;
      hStep = mpExportHandler->addItem("Creating reactions...",
                                       CCopasiParameter::UINT,
                                       & step,
                                       &totalSteps);
    }
  for (counter = 0; counter < iMax; counter++)
    {
      Reaction* sbmlReaction = this->createSBMLReactionFromCReaction(copasiModel->getReactions()[counter]);
      if (!sbmlModel->getReaction(sbmlReaction->getId()))
        {
          sbmlModel->addReaction(*sbmlReaction);
        }
      ++step;
      if (mpExportHandler && !mpExportHandler->progress(hStep)) return false;
    }
  pdelete(this->mpIdSet);
  if (mpExportHandler)
    {
      mpExportHandler->finish(hStep);
    }
  return sbmlModel;
}

/**
 ** This method takes a string that specifies the time unit used in the
 ** copasi model and returns a pointer to the corresponding SBML
 ** UnitDefinition object.
 */
UnitDefinition* SBMLExporter::createSBMLTimeUnitDefinitionFromCopasiTimeUnit(CModel::TimeUnit u)
{
  UnitDefinition* uDef = new UnitDefinition("time");
  uDef->setId("time");
  Unit* unit;

  switch (u)
    {
    case CModel::d:
      unit = new Unit(UNIT_KIND_SECOND, 1, 0);
      unit->setMultiplier(86400);
      break;
    case CModel::h:
      unit = new Unit(UNIT_KIND_SECOND, 1, 0);
      unit->setMultiplier(3600);
      break;
    case CModel::min:
      unit = new Unit(UNIT_KIND_SECOND, 1, 0);
      unit->setMultiplier(60);
      break;
    case CModel::ms:
      unit = new Unit(UNIT_KIND_SECOND, 1, -3);
      break;
    case CModel::micros:
      unit = new Unit(UNIT_KIND_SECOND, 1, -6);
      break;
    case CModel::ns:
      unit = new Unit(UNIT_KIND_SECOND, 1, -9);
      break;
    case CModel::ps:
      unit = new Unit(UNIT_KIND_SECOND, 1, -12);
      break;
    case CModel::fs:
      unit = new Unit(UNIT_KIND_SECOND, 1, -15);
      break;
    default:
      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, "SBMLExporter Error: Unknown copasi time unit.");
      break;
    }

  uDef->addUnit(*unit);
  return uDef;
}

/**
 ** This method takes a string that specifies the substance unit used in the
 ** copasi model and returns a pointer to the corresponding SBML
 ** UnitDefinition object.
 */
UnitDefinition* SBMLExporter::createSBMLSubstanceUnitDefinitionFromCopasiQuantityUnit(CModel::QuantityUnit u)
{
  UnitDefinition* uDef = new UnitDefinition("substance");
  uDef->setId("substance");
  Unit* unit;
  switch (u)
    {
    case CModel::mMol:
      unit = new Unit(UNIT_KIND_MOLE, 1, -3);
      break;
    case CModel::microMol:
      unit = new Unit(UNIT_KIND_MOLE, 1, -6);
      break;
    case CModel::nMol:
      unit = new Unit(UNIT_KIND_MOLE, 1, -9);
      break;
    case CModel::pMol:
      unit = new Unit(UNIT_KIND_MOLE, 1, -12);
      break;
    case CModel::fMol:
      unit = new Unit(UNIT_KIND_MOLE, 1, -15);
      break;
    case CModel::number:
      unit = new Unit(UNIT_KIND_ITEM, 1, 1);
      break;
    default:
      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, "SBMLExporter Error: Unknown copasi quantity unit.");
      break;
    }
  uDef->addUnit(*unit);
  return uDef;
}

/**
 ** This method takes a string that specifies the volume unit used in the
 ** copasi model and returns a pointer to the corresponding SBML
 ** UnitDefinition object.
 */
UnitDefinition* SBMLExporter::createSBMLVolumeUnitDefinitionFromCopasiVolumeUnit(CModel::VolumeUnit u)
{
  UnitDefinition* uDef = new UnitDefinition("volume");
  uDef->setId("volume");
  Unit* unit;
  switch (u)
    {
    case CModel::ml:
      unit = new Unit(UNIT_KIND_LITRE, 1, -3);
      break;
    case CModel::microl:
      unit = new Unit(UNIT_KIND_LITRE, 1, -6);
      break;
    case CModel::nl:
      unit = new Unit(UNIT_KIND_LITRE, 1, -9);
      break;
    case CModel::pl:
      unit = new Unit(UNIT_KIND_LITRE, 1, -12);
      break;
    case CModel::fl:
      unit = new Unit(UNIT_KIND_LITRE, 1, -15);
      break;
    case CModel::m3:
      unit = new Unit(UNIT_KIND_METRE, 3, 0);
      break;
    default:
      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, "SBMLExporter Error: Unknown copasi volume unit.");
      break;
    }
  uDef->addUnit(*unit);
  return uDef;
}

/**
 ** This method takes a pointer to a copasi CCompartment object and creates
 ** a SBML Compartment. The pointer to the SBML Comprtment is returned.
 */
Compartment* SBMLExporter::createSBMLCompartmentFromCCompartment(CCompartment* copasiCompartment)
{
  Compartment* sbmlCompartment = NULL;
  std::map<CCopasiObject*, SBase*>& copasi2sbmlmap = CCopasiDataModel::Global->getCopasi2SBMLMap();
  std::map<CCopasiObject*, SBase*>::iterator pos = copasi2sbmlmap.find(copasiCompartment);
  if (pos != copasi2sbmlmap.end())
    {
      sbmlCompartment = dynamic_cast<Compartment*>(pos->second);
      assert(sbmlCompartment);
    }
  else
    {
      sbmlCompartment = new Compartment();
      copasi2sbmlmap[copasiCompartment] = sbmlCompartment;

      std::string id = copasiCompartment->getSBMLId();
      if (id == "")
        {
          id = SBMLExporter::createUniqueId(this->mpIdSet, "compartment_");
          copasiCompartment->setSBMLId(id);
          this->mpIdSet->insert(id);
        }
      sbmlCompartment->setId(id);
      sbmlCompartment->setSpatialDimensions(3);
      sbmlCompartment->setConstant(true);
    }
  this->mHandledSBMLObjects.push_back(sbmlCompartment);
  sbmlCompartment->setName(copasiCompartment->getObjectName().c_str());
  double value = copasiCompartment->getInitialVolume();
  // if the value is NaN, unset the initial volume
  if (!isnan(value))
    {
      sbmlCompartment->setVolume(value);
    }
  else
    {
      sbmlCompartment->unsetVolume();
    }
  return sbmlCompartment;
}

/**
 ** This method takes a pointer to a copasi CMetab object and creates a SBML 
 ** Species object. The pointer to the species object is returned.
 */
Species* SBMLExporter::createSBMLSpeciesFromCMetab(CMetab* copasiMetabolite)
{
  Species* sbmlSpecies = NULL;
  std::map<CCopasiObject*, SBase*>& copasi2sbmlmap = CCopasiDataModel::Global->getCopasi2SBMLMap();
  std::map<CCopasiObject*, SBase*>::iterator pos = copasi2sbmlmap.find(copasiMetabolite);
  if (pos != copasi2sbmlmap.end())
    {
      sbmlSpecies = dynamic_cast<Species*>(pos->second);
      assert(sbmlSpecies);
    }
  else
    {
      sbmlSpecies = new Species();
      copasi2sbmlmap[copasiMetabolite] = sbmlSpecies;
      std::string id = copasiMetabolite->getSBMLId();
      if (id == "")
        {
          id = SBMLExporter::createUniqueId(this->mpIdSet, "species_");
          copasiMetabolite->setSBMLId(id);
          this->mpIdSet->insert(id);
        }
      sbmlSpecies->setId(id);
    }
  this->mHandledSBMLObjects.push_back(sbmlSpecies);
  sbmlSpecies->setName(copasiMetabolite->getObjectName().c_str());
  sbmlSpecies->setBoundaryCondition(copasiMetabolite->getStatus() == CModelEntity::FIXED);
  sbmlSpecies->setConstant(copasiMetabolite->getStatus() == CModelEntity::FIXED);

  Compartment* sbmlCompartment = dynamic_cast<Compartment*>(copasi2sbmlmap[const_cast<CCompartment*>(copasiMetabolite->getCompartment())]);
  assert(sbmlCompartment);
  sbmlSpecies->setCompartment(sbmlCompartment->getId());
  double value = copasiMetabolite->getInitialConcentration();
  // if the value is NaN, unset the initial amount
  if (!isnan(value))
    {
      if (sbmlSpecies->isSetInitialAmount())
        {
          sbmlSpecies->setInitialAmount(value*copasiMetabolite->getCompartment()->getInitialVolume());
        }
      else
        {
          sbmlSpecies->setInitialConcentration(value);
        }
    }
  else
    {
      sbmlSpecies->unsetInitialConcentration();
      sbmlSpecies->unsetInitialAmount();
    }
  return sbmlSpecies;
}

/**
 ** This method takes a pointer to a copasi CModelValue object and creates a SBML 
 ** Parameter object. The pointer to the parameter object is returned.
 */
Parameter* SBMLExporter::createSBMLParameterFromCModelValue(CModelValue* pModelValue)
{
  Parameter* pParameter = NULL;
  std::map<CCopasiObject*, SBase*>& copasi2sbmlmap = CCopasiDataModel::Global->getCopasi2SBMLMap();
  std::map<CCopasiObject*, SBase*>::iterator pos = copasi2sbmlmap.find(pModelValue);
  if (pos != copasi2sbmlmap.end())
    {
      pParameter = dynamic_cast<Parameter*>(pos->second);
      assert(pParameter);
    }
  else
    {
      pParameter = new Parameter();
      copasi2sbmlmap[pModelValue] = pParameter;
      std::string id = pModelValue->getSBMLId();
      if (id == "")
        {
          id = SBMLExporter::createUniqueId(this->mpIdSet, "parameter_");
          pModelValue->setSBMLId(id);
          this->mpIdSet->insert(id);
        }
      pParameter->setId(id);
    }
  this->mHandledSBMLObjects.push_back(pParameter);
  pParameter->setName(pModelValue->getObjectName());
  double value = pModelValue->getValue();
  // if the value is NaN, unset the parameters value
  if (!isnan(value))
    {
      pParameter->setValue(pModelValue->getValue());
    }
  else
    {
      pParameter->unsetValue();
    }
  return pParameter;
}

/**
 ** This method takes a pointer to a copasi CReaction object and creates an
 ** SBML Reaction object. The pointer to the created reaction object is
 ** returned.
 */
Reaction* SBMLExporter::createSBMLReactionFromCReaction(CReaction* copasiReaction)
{
  Reaction* sbmlReaction = NULL;
  std::map<CCopasiObject*, SBase*>& copasi2sbmlmap = CCopasiDataModel::Global->getCopasi2SBMLMap();
  std::map<CCopasiObject*, SBase*>::iterator pos = copasi2sbmlmap.find(copasiReaction);
  if (pos != copasi2sbmlmap.end())
    {
      sbmlReaction = dynamic_cast<Reaction*>(pos->second);
      assert(sbmlReaction);
    }
  else
    {
      /* create a new reaction object */
      sbmlReaction = new Reaction();
      copasi2sbmlmap[copasiReaction] = sbmlReaction;
      std::string id = copasiReaction->getSBMLId();
      if (id == "")
        {
          id = SBMLExporter::createUniqueId(this->mpIdSet, "reaction_");
          copasiReaction->setSBMLId(id);
          this->mpIdSet->insert(id);
        }
      sbmlReaction->setId(id);
    }
  this->mHandledSBMLObjects.push_back(sbmlReaction);
  sbmlReaction->setName(copasiReaction->getObjectName().c_str());
  sbmlReaction->setReversible(copasiReaction->isReversible());
  const CChemEq chemicalEquation = copasiReaction->getChemEq();
  /* Add all substrates */
  unsigned int counter;
  std::set<std::string> usedReferences;
  for (counter = 0; counter < chemicalEquation.getSubstrates().size(); counter++)
    {
      CChemEqElement* element = chemicalEquation.getSubstrates()[counter];
      const CMetab& metabolite = element->getMetabolite();
      SpeciesReference* sRef = NULL;
      if (!(sRef = sbmlReaction->getReactant(metabolite.getSBMLId())))
        {
          sRef = new SpeciesReference();
          sbmlReaction->addReactant(*sRef);
          sRef->setSpecies(metabolite.getSBMLId().c_str());
        }
      sRef->setStoichiometry(element->getMultiplicity());
      sRef->setDenominator(1);
      usedReferences.insert(sRef->getSpecies());
    }
  ListOf* l = &sbmlReaction->getListOfReactants();
  for (counter = l->getNumItems(); counter > 0;--counter)
    {
      if (usedReferences.find(static_cast<SimpleSpeciesReference*>(l->get(counter - 1))->getSpecies()) == usedReferences.end())
        {
          l->remove(counter - 1);
        }
    }
  /* Add all products */
  usedReferences.clear();
  for (counter = 0; counter < chemicalEquation.getProducts().size(); counter++)
    {
      CChemEqElement* element = chemicalEquation.getProducts()[counter];
      const CMetab& metabolite = element->getMetabolite();
      SpeciesReference* sRef = NULL;
      if (!(sRef = sbmlReaction->getProduct(metabolite.getSBMLId())))
        {
          sRef = new SpeciesReference();
          sRef->setSpecies(metabolite.getSBMLId().c_str());
          sbmlReaction->addProduct(*sRef);
        }
      sRef->setStoichiometry(element->getMultiplicity());
      sRef->setDenominator(1);
      usedReferences.insert(sRef->getSpecies());
    }
  l = &sbmlReaction->getListOfProducts();
  for (counter = l->getNumItems(); counter > 0;--counter)
    {
      if (usedReferences.find(static_cast<SimpleSpeciesReference*>(l->get(counter - 1))->getSpecies()) == usedReferences.end())
        {
          l->remove(counter - 1);
        }
    }
  /* Add all modifiers */
  usedReferences.clear();
  for (counter = 0; counter < chemicalEquation.getModifiers().size(); counter++)
    {
      CChemEqElement* element = chemicalEquation.getModifiers()[counter];
      const CMetab& metabolite = element->getMetabolite();
      ModifierSpeciesReference* sRef = NULL;
      if (!(sRef = sbmlReaction->getModifier(metabolite.getSBMLId())))
        {
          sRef = new ModifierSpeciesReference();
          sRef->setSpecies(metabolite.getSBMLId().c_str());
          sbmlReaction->addModifier(*sRef);
        }
      usedReferences.insert(sRef->getSpecies());
    }
  l = &sbmlReaction->getListOfModifiers();
  for (counter = l->getNumItems(); counter > 0;--counter)
    {
      if (usedReferences.find(static_cast<SimpleSpeciesReference*>(l->get(counter - 1))->getSpecies()) == usedReferences.end())
        {
          l->remove(counter - 1);
        }
    }
  /* create the kinetic law */
  /* if there is one on copasi */
  if ((&copasiReaction->getFunction()) != CCopasiDataModel::Global->mpUndefined)
    {
      KineticLaw* kLaw = this->createSBMLKineticLawFromCReaction(copasiReaction);
      sbmlReaction->setKineticLaw(*kLaw);
    }
  else
    {
      sbmlReaction->unsetKineticLaw();
    }
  return sbmlReaction;
}

/**
 ** This method takes a pointer to a copasi CReation object and creates a
 ** SBML KineticLaw object from the kintik function of the copasi reaction
 ** object. The pointer to the created KineticLaw is returned.
 */
KineticLaw* SBMLExporter::createSBMLKineticLawFromCReaction(CReaction* copasiReaction)
{
  KineticLaw* kLaw = NULL;
  /*
   * This code can not be activated yet since roundtripping of kinetcs is not so trivial.
   *   
  std::map<CCopasiObject*,SBase*>& copasi2sbmlmap=CCopasiDataModel::Global->getCopasi2SBMLMap();   
  std::map<CCopasiObject*,SBase*>::iterator pos=copasi2sbmlmap.find(copasiReaction);
  if(pos!=copasi2sbmlmap.end())
  {
    Reaction* pTmpReaction=dynamic_cast<Reaction*>(pos->second);
    assert(pTmpReaction);
    kLaw=pTMpReaction->getKineticLaw();
  }
  */
  if (!kLaw)
    {
      /* create a new KineticLaw */
      kLaw = new KineticLaw();
    }
  /* if the copasi CFunction specifies a mass-action kinetic */
  ASTNode* node = NULL;
  if (copasiReaction->getFunction().getType() == CFunction::MassAction)
    {
      const CMassAction cMassAction = static_cast<const CMassAction>(copasiReaction->getFunction());
      /* create the ASTNode that multiplies all substrates with the first
      ** kinetic constant.
      */
      node = new ASTNode(AST_TIMES);

      ASTNode* parameterNode1 = new ASTNode(AST_NAME);
      std::string parameterName1;
      if (copasiReaction->isLocalParameter(0))
        {
          parameterName1 = cMassAction.getVariables()[0]->getObjectName();
        }
      else
        {
          parameterName1 = copasiReaction->getParameterMappings()[0][0];
          const CModelValue* pMV = dynamic_cast<const CModelValue*>(GlobalKeys.get(parameterName1));
          if (!pMV) fatalError();
          parameterName1 = pMV->getSBMLId();
        }
      parameterNode1->setName(parameterName1.c_str());
      node->addChild(parameterNode1);
      node->addChild(this->createTimesTree(copasiReaction->getChemEq().getSubstrates()));
      /* if the reaction is reversible, create the ASTNode tree that
      ** multiplies all products with the second kinetic constant and
      ** subtract this tree from the tree of the forward reaction.
      */
      if (cMassAction.isReversible() == TriTrue)
        {
          ASTNode* backwardNode = new ASTNode(AST_TIMES);

          ASTNode* parameterNode2 = new ASTNode(AST_NAME);
          std::string parameterName2;
          if (copasiReaction->isLocalParameter(2))
            {
              parameterName2 = cMassAction.getVariables()[2]->getObjectName();
            }
          else
            {
              parameterName2 = copasiReaction->getParameterMappings()[2][0];
              const CModelValue* pMV = dynamic_cast<const CModelValue*>(GlobalKeys.get(parameterName2));
              if (!pMV) fatalError();
              parameterName2 = pMV->getSBMLId();
            }
          parameterNode2->setName(parameterName2.c_str());
          backwardNode->addChild(parameterNode2);

          backwardNode->addChild(this->createTimesTree(copasiReaction->getChemEq().getProducts()));
          ASTNode* tempNode = new ASTNode(AST_MINUS);
          tempNode->addChild(node);
          tempNode->addChild(backwardNode);
          node = tempNode;
        }
    }
  /* if the copasi CFunction does not specify a mass-action kinetic, it is a
  ** CKinFunction */
  else
    {
      // walk the tree and look for function calls
      if (!this->mExportExpressions)
        {
          CEvaluationTree* pTree = new CEvaluationTree("NoName", NULL, CEvaluationTree::Expression);
          CEvaluationNodeCall* pTmpRoot = new CEvaluationNodeCall(CEvaluationNodeCall::FUNCTION, copasiReaction->getFunction().getObjectName());
          const std::vector< std::vector<std::string> >& parameterMappings = copasiReaction->getParameterMappings();
          unsigned int i, iMax = parameterMappings.size();
          for (i = 0;i < iMax;++i)
            {
              CEvaluationNodeObject* pObjectNode = new CEvaluationNodeObject(CEvaluationNodeObject::ANY, "<" + GlobalKeys.get(parameterMappings[i][0])->getCN() + ">");
              pTmpRoot->addChild(pObjectNode);
            }
          pTree->setRoot(pTmpRoot);
          pTree->compileNodes();
          std::list<const CEvaluationTree*> usedFunctionList;
          this->findUsedFunctions(pTmpRoot, usedFunctionList);
          node = pTmpRoot->toAST();
          pdelete(pTree);
        }
      else
        {
          CEvaluationNode* pExpressionRoot = this->createExpressionTree(&copasiReaction->getFunction(), copasiReaction->getParameterMappings());
          if (!pExpressionRoot) fatalError();
          node = pExpressionRoot->toAST();
          if (!node) fatalError();
        }
    }

  /*
   ** If the reaction takes place in a single compartment, the rate law has
   ** to be converted from concentration/time to substance/time by
   ** multiplying the rate law with the volume of the compartment.
   */
  if (copasiReaction->getCompartmentNumber() == 1)
    {
      const CCompartment* compartment = NULL;
      if (copasiReaction->getChemEq().getSubstrates().size() != 0)
        {
          compartment = copasiReaction->getChemEq().getSubstrates()[0]->getMetabolite().getCompartment();
        }
      else
        {
          compartment = copasiReaction->getChemEq().getProducts()[0]->getMetabolite().getCompartment();
        }
      // check if the importer has added a division by the volume
      // if so remove it instead of multiplying again
      ASTNode* tNode = this->isDividedByVolume(node, compartment->getSBMLId());
      if (tNode)
        {
          if (tNode->getNumChildren() == 0)
            {
              fatalError();
            }
          if (tNode->getNumChildren() == 1)
            {
              ASTNode* tmp = static_cast<ConverterASTNode*>(tNode)->removeChild(0);
              delete tNode;
              tNode = tmp;
            }
          delete node;
          node = tNode;
        }
      else
        {
          tNode = new ASTNode(AST_TIMES);
          ASTNode* vNode = new ASTNode(AST_NAME);
          vNode->setName(compartment->getSBMLId().c_str());
          tNode->addChild(vNode);
          tNode->addChild(node);
          node = tNode;
        }
    }

  kLaw->setMath(node);
  /* add the parameters */
  unsigned int counter;
  for (counter = 0; counter < copasiReaction->getFunctionParameters().size(); counter++)
    {
      const CFunctionParameter* para = copasiReaction->getFunctionParameters()[counter];
      if (para->getUsage() == CFunctionParameter::PARAMETER)
        {
          // only create a parameter if it is a local parameter,
          // otherwise the parameter already has been created
          if (copasiReaction->isLocalParameter(counter))
            {
              Parameter* sbmlPara = new Parameter();

              std::string parameterKey = copasiReaction->getParameterMappings()[counter][0];

              sbmlPara->setId(para->getObjectName().c_str());
              double value = copasiReaction->getParameterValue(para->getObjectName());
              // if the value is NaN, leave the parameter value unset.
              if (!isnan(value))
                {
                  sbmlPara->setValue(value);
                }
              kLaw->addParameter(*sbmlPara);
            }
          else
            {
              // the corresponding node has to be changed
              std::string modelValueKey = copasiReaction->getParameterMappings()[counter][0];
              this->replaceNodeName(node, para->getObjectName(), modelValueKey);
            }
        }
    }
  return kLaw;
}

/**
 ** This method creates an ASTNode tree where all the species specified in
 ** the given vector are multiplied. This is used to create the mass action
 ** kinetic law.
 */
ASTNode* SBMLExporter::createTimesTree(const CCopasiVector<CChemEqElement >& vect, unsigned int pos)
{
  ASTNode* node = NULL;
  double multiplicity = vect[pos]->getMultiplicity();
  if (pos == vect.size() - 1)
    {
      node = new ASTNode(AST_NAME);
      const CMetab& pMetab = vect[pos]->getMetabolite();

      node->setName(pMetab.getSBMLId().c_str());
      /* if the stoichiometry is not 1.0, we have to add it to the exponent */
      if (multiplicity != 1.0)
        {
          ASTNode* tmpNode1 = new ASTNode(AST_POWER);
          ASTNode* tmpNode2 = new ASTNode(AST_REAL);
          tmpNode2->setValue(multiplicity);
          tmpNode1->addChild(node);
          tmpNode1->addChild(tmpNode2);
          node = tmpNode1;
        }
    }
  else
    {
      node = new ASTNode(AST_TIMES);
      ASTNode* child = new ASTNode(AST_NAME);
      const CMetab& pMetab = vect[pos]->getMetabolite();

      child->setName(pMetab.getSBMLId().c_str());

      /* if the stoichiometry is not 1.0, we have to add it to the exponent */
      if (multiplicity != 1.0)
        {
          ASTNode* tmpNode1 = new ASTNode(AST_POWER);
          ASTNode* tmpNode2 = new ASTNode(AST_REAL);
          tmpNode2->setValue(multiplicity);
          tmpNode1->addChild(child);
          tmpNode1->addChild(tmpNode2);
          child = tmpNode1;
        }

      node->addChild(child);
      node->addChild(this->createTimesTree(vect, pos + 1));
    }
  return node;
}

/**
 ** This method tests if a string only consists of whitespace characters
 */
bool SBMLExporter::isEmptyString(const std::string& str)
{
  return (str.find_first_not_of(" \n\t\r") == std::string::npos);
}

void SBMLExporter::replaceNodeName(ASTNode* pNode, const std::string& oldName, const std::string& newName)
{
  if (pNode->isName() && pNode->getName() == oldName)
    {
      pNode->setName(newName.c_str());
    }
  unsigned int i;
  unsigned int maxI = pNode->getNumChildren();
  for (i = 0; i < maxI;++i)
    {
      replaceNodeName(pNode->getChild(i), oldName, newName);
    }
}

void SBMLExporter::removeUnusedObjects()
{
  // go through the sbmlDocument and remove all species, compartments, parameters and reactions
  // that are not in mHandledSBMLObjects because this means they are no longer in the copasi model.
  Model* model = this->sbmlDocument->getModel();
  assert(model);
  unsigned int i;
  std::vector<SBase*>::iterator pos;
  std::vector<SBase*>::iterator endPos = this->mHandledSBMLObjects.end();
  ListOf* list = &model->getListOfCompartments();
  for (i = list->getNumItems(); i > 0;--i)
    {
      SBase* object = list->get(i - 1);
      pos = std::find(this->mHandledSBMLObjects.begin(), this->mHandledSBMLObjects.end(), object);
      if (pos == endPos)
        {
          list->remove(i - 1);
          pdelete(object);
        }
    }
  list = &model->getListOfSpecies();
  for (i = list->getNumItems(); i > 0;--i)
    {
      SBase* object = list->get(i - 1);
      pos = std::find(this->mHandledSBMLObjects.begin(), this->mHandledSBMLObjects.end(), object);
      if (pos == endPos)
        {
          list->remove(i - 1);
          pdelete(object);
        }
    }
  list = &model->getListOfParameters();
  for (i = list->getNumItems(); i > 0;--i)
    {
      SBase* object = list->get(i - 1);
      pos = std::find(this->mHandledSBMLObjects.begin(), this->mHandledSBMLObjects.end(), object);
      if (pos == endPos)
        {
          list->remove(i - 1);
          pdelete(object);
        }
    }
  list = &model->getListOfReactions();
  for (i = list->getNumItems(); i > 0;--i)
    {
      SBase* object = list->get(i - 1);
      pos = std::find(this->mHandledSBMLObjects.begin(), this->mHandledSBMLObjects.end(), object);
      if (pos == endPos)
        {
          list->remove(i - 1);
          pdelete(object);
        }
    }

  this->removeUnusedFunctionDefinitions();
  this->removeUnusedUnitDefinitions();
}

void SBMLExporter::removeUnusedFunctionDefinitions()
{
  // does nothing yet
  // this can only be done one we understand events and rules and function calls
}

void SBMLExporter::removeUnusedUnitDefinitions()
{
  // does nothing yet
  // this can only be done one we understand events and rules
}

std::set<std::string>* SBMLExporter::createIdSet(const Model* pSBMLModel)
{
  // go through all function definitions, compartments, species, reactions,
  // parameters and events and create a set with all used ids.
  // Later on, we need to add the species references as well.

  std::set<std::string>* pIdSet = NULL;
  if (pSBMLModel)
    {
      pIdSet = new std::set<std::string>();
      unsigned int i, iMax;
      iMax = pSBMLModel->getNumFunctionDefinitions();
      for (i = 0; i < iMax;++i)
        {
          pIdSet->insert(pSBMLModel->getFunctionDefinition(i)->getId());
        }
      iMax = pSBMLModel->getNumCompartments();
      for (i = 0; i < iMax;++i)
        {
          pIdSet->insert(pSBMLModel->getCompartment(i)->getId());
        }
      iMax = pSBMLModel->getNumSpecies();
      for (i = 0; i < iMax;++i)
        {
          pIdSet->insert(pSBMLModel->getSpecies(i)->getId());
        }
      iMax = pSBMLModel->getNumParameters();
      for (i = 0; i < iMax;++i)
        {
          pIdSet->insert(pSBMLModel->getParameter(i)->getId());
        }
      iMax = pSBMLModel->getNumReactions();
      for (i = 0; i < iMax;++i)
        {
          pIdSet->insert(pSBMLModel->getReaction(i)->getId());
        }
      iMax = pSBMLModel->getNumEvents();
      for (i = 0; i < iMax;++i)
        {
          pIdSet->insert(pSBMLModel->getEvent(i)->getId());
        }
    }
  else
    {
      pIdSet = new std::set<std::string>();
      std::string id;
      unsigned int i, iMax;
      CCopasiVectorN<CEvaluationTree>& loadedFunctions = CCopasiDataModel::Global->getFunctionList()->loadedFunctions();
      iMax = loadedFunctions.size();
      for (i = 0;i < iMax;++i)
        {
          id = loadedFunctions[i]->getSBMLId();
          if (id != "") pIdSet->insert(id);
        }
      iMax = this->mpCopasiModel->getNumMetabs();
      for (i = 0; i < iMax;++i)
        {
          id = this->mpCopasiModel->getMetabolites()[i]->getSBMLId();
          if (id != "") pIdSet->insert(id);
        }
      iMax = this->mpCopasiModel->getNumModelValues();
      for (i = 0; i < iMax;++i)
        {
          id = this->mpCopasiModel->getModelValues()[i]->getSBMLId();
          if (id != "") pIdSet->insert(id);
        }
      iMax = this->mpCopasiModel->getCompartments().size();
      for (i = 0; i < iMax;++i)
        {
          id = this->mpCopasiModel->getCompartments()[i]->getSBMLId();
          if (id != "") pIdSet->insert(id);
        }
      iMax = this->mpCopasiModel->getReactions().size();
      for (i = 0; i < iMax;++i)
        {
          id = this->mpCopasiModel->getReactions()[i]->getSBMLId();
          if (id != "") pIdSet->insert(id);
        }
    }
  return pIdSet;
}

std::string SBMLExporter::createUniqueId(const std::set<std::string>* idSet, const std::string& prefix)
{
  unsigned int i = 0;
  std::ostringstream numberStream;
  numberStream << i;
  std::string id = prefix + numberStream.str();
  if (idSet)
    {
      while (idSet->find(id) != idSet->end())
        {
          ++i;
          numberStream.str("");
          numberStream << i;
          id = prefix + numberStream.str();
        }
    }
  return id;
}

ASTNode* SBMLExporter::isDividedByVolume(const ASTNode* node, const std::string& compartmentSBMLId)
{
  ASTNode* result = NULL;
  if (node->getType() == AST_DIVIDE || node->getType() == AST_TIMES)
    {
      ASTNode* pTmpResultNode = new ConverterASTNode(node->getType());
      unsigned int i, iMax = node->getNumChildren();
      bool found = false;
      for (i = 0; i < iMax;++i)
        {
          const ASTNode* child = node->getChild(i);
          if (node->getType() == AST_DIVIDE && child->getType() == AST_NAME && child->getName() == compartmentSBMLId)
            {
              found = true;
            }
          else if ((!found) && (child->getType() == AST_DIVIDE || child->getType() == AST_TIMES))
            {
              ASTNode* pSubResult = this->isDividedByVolume(child, compartmentSBMLId);
              if (pSubResult)
                {
                  found = true;
                  if (pSubResult->getNumChildren() > 1)
                    {
                      pTmpResultNode->addChild(pSubResult);
                    }
                  else if (pSubResult->getNumChildren() == 1)
                    {
                      pTmpResultNode->addChild(static_cast<ASTNode*>(static_cast<ConverterASTNode*>(pSubResult)->removeChild(0)));
                      delete pSubResult;
                    }
                  else
                    {
                      delete pSubResult;
                    }
                }
              else
                {
                  pTmpResultNode->addChild(new ConverterASTNode(*child));
                }
            }
          else
            {
              pTmpResultNode->addChild(new ConverterASTNode(*child));
            }
        }
      if (found)
        {
          result = pTmpResultNode;
        }
      else
        {
          delete pTmpResultNode;
        }
    }
  return result;
}

void SBMLExporter::findUsedFunctions(CEvaluationNode* pNode, std::list<const CEvaluationTree*>& usedFunctionList)
{
  CFunctionDB* pFunDB = CCopasiDataModel::Global->getFunctionList();
  CCopasiTree<CEvaluationNode>::iterator treeIt = pNode;
  CCopasiTree<CEvaluationNode>::iterator treeEndIt = NULL;

  while (treeIt != treeEndIt)
    {
      if (CEvaluationNode::type((*treeIt).getType()) == CEvaluationNode::CALL)
        {
          // find used function used in the corresponding function
          CEvaluationTree* pFun = pFunDB->findFunction((*treeIt).getData());
          if (!pFun)
            {
              CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 15, (*treeIt).getData().c_str());
            }
          if (this->existsInList(pFun, usedFunctionList))
            {
              // we have a loop
              CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 16);
            }
          // if the function is already in the list of used functions, we don't have
          // to go through it again.
          usedFunctionList.push_back(pFun);
          if (!this->existsInList(pFun, this->mUsedFunctions))
            {
              std::list<const CEvaluationTree*>::iterator pos = usedFunctionList.end();
              --pos;
              this->findUsedFunctions(pFun->getRoot(), usedFunctionList);
              // add this function to mUsedFunctions after the last function in usedFunctionList
              // if usedFunctionList does not have any entries after pos, just insert the function
              // at the beginning
              if (usedFunctionList.back() == (*pos))
                {
                  if (pFun->getSBMLId().empty())
                    {
                      if (this->isValidSId(pFun->getObjectName()) && this->mpIdSet->find(pFun->getObjectName()) == this->mpIdSet->end())
                        {
                          pFun->setSBMLId(pFun->getObjectName());
                        }
                      else
                        {
                          std::string id = this->createUniqueId(this->mpIdSet, "function_");
                          pFun->setSBMLId(id);
                          this->mpIdSet->insert(id);
                        }
                    }
                  this->mUsedFunctions.push_front(pFun);
                }
              else
                {
                  std::list<const CEvaluationTree*>::iterator it = this->mUsedFunctions.begin();
                  std::list<const CEvaluationTree*>::iterator endIt = this->mUsedFunctions.end();
                  std::list<const CEvaluationTree*>::iterator afterPos = this->mUsedFunctions.end();
                  while ((it != endIt) && (usedFunctionList.back() != (*pos)))
                    {
                      // pos is the position of the current function in usedFunctionList
                      // so find the function after pos in usedFunctions that has the position
                      // furthest to the back of this->mUsedFunctions
                      std::list<const CEvaluationTree*>::iterator it2 = pos;
                      std::list<const CEvaluationTree*>::iterator endIt2 = usedFunctionList.end();
                      while (it2 != endIt2)
                        {
                          if ((*it) == (*it2))
                            {
                              usedFunctionList.erase(it2);
                              afterPos = it;
                              break;
                            }
                          ++it2;
                        }
                      ++it;
                    }
                  if (afterPos == this->mUsedFunctions.end())
                    {
                      fatalError();
                    }
                  ++afterPos;
                  this->mUsedFunctions.insert(afterPos, pFun);
                }
            }
        }
      ++treeIt;
    }
}

void SBMLExporter::createFunctionDefinitions()
{
  ListOf& listOfFunctionDefinitions = this->sbmlDocument->getModel()->getListOfFunctionDefinitions();
  std::list<const CEvaluationTree*>::const_iterator it = this->mUsedFunctions.begin();
  std::list<const CEvaluationTree*>::const_iterator endIt = this->mUsedFunctions.end();
  while (it != endIt)
    {
      // delete an existing function definition with this name
      // add the new function definition
      unsigned int i, iMax = listOfFunctionDefinitions.getNumItems();
      for (i = 0; i < iMax;++i)
        {
          if (static_cast<FunctionDefinition*>(listOfFunctionDefinitions.get(i))->getId() == (*it)->getSBMLId())
            {
              listOfFunctionDefinitions.remove(i);
              break;
            }
        }
      const CEvaluationTree* tree = (*it);
      std::string on = tree->getObjectName();
      std::string id = tree->getSBMLId();
      this->createSBMLFunctionDefinitionFromCEvaluationTree((*it));
      ++it;
    }
}

FunctionDefinition* SBMLExporter::createSBMLFunctionDefinitionFromCEvaluationTree(const CEvaluationTree* tree)
{
  // convert the tree root to an AST tree.
  FunctionDefinition& pFunDef = this->sbmlDocument->getModel()->createFunctionDefinition();
  pFunDef.setId(tree->getSBMLId());
  if (!tree->getRoot())
    {
      std::string errorMessage = std::string("Can not export function");
      errorMessage += tree->getObjectName();
      errorMessage += std::string(". Function does not have a valid root node.");
      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, errorMessage.c_str());
    }
  ASTNode* pFunNode = tree->getRoot()->toAST();
  // go through the AST tree and replace all function call nodes with with a call to the sbml id
  ASTNode* pLambda = new ASTNode(AST_LAMBDA);
  // add the parameters to the function definition
  const CFunctionParameters& funParams = static_cast<const CFunction*>(tree)->getVariables();
  unsigned int i, iMax = funParams.size();
  ASTNode* pParamNode = NULL;
  for (i = 0; i < iMax;++i)
    {
      pParamNode = new ASTNode(AST_NAME);
      pParamNode->setName(funParams[i]->getObjectName().c_str());
      pLambda->addChild(pParamNode);
    }
  pLambda->addChild(pFunNode);
  pFunDef.setMath(pLambda);
  return &pFunDef;
}

bool SBMLExporter::existsInList(CEvaluationTree* tree, const std::list<const CEvaluationTree*>& list)
{
  std::list<const CEvaluationTree*>::const_iterator it = list.begin();
  std::list<const CEvaluationTree*>::const_iterator endIt = list.end();
  while (it != endIt)
    {
      if ((*it) == tree) break;
      ++it;
    }
  return it != endIt;
}

SBMLDocument* SBMLExporter::getSBMLDocument() const
  {
    return this->sbmlDocument;
  }

bool SBMLExporter::isValidSId(const std::string& id)
{
  bool result = true;
  if (id.length() > 0)
    {
      char c = id[0];
      result = (c == '_' || (c > 64 && c < 91) || (c > 96 && c < 123));
      unsigned int i, iMax = id.length();
      for (i = 1;(i < iMax) && result;++i)
        {
          c = id[i];
          result = (c == '_' || (c > 64 && c < 91) || (c > 96 && c < 123) || (c > 47 && c < 58));
        }
    }
  else
    {
      result = false;
    }
  return result;
}

CProcessReport* SBMLExporter::getExportHandler()
{
  return this->mpExportHandler;
}

void SBMLExporter::setExportHandler(CProcessReport* pExportHandler)
{
  this->mpExportHandler = pExportHandler;
}

void SBMLExporter::fillCopasi2SBMLMap()
{
  this->mCopasi2SBMLMap.clear();
  // check if we currently have an SBMLDocument;
  SBMLDocument* pSBMLDoc = CCopasiDataModel::Global->getCurrentSBMLDocument();
  unsigned int level = pSBMLDoc->getLevel();
  if (pSBMLDoc)
    {
      // go through this SBMLDocument and create a map that maps the ids of each object to the object
      std::map<std::string, SBase*> sbmlMap;
      Model* pSBMLModel = pSBMLDoc->getModel();
      if (pSBMLModel && mpCopasiModel)
        {
          unsigned int i, iMax = pSBMLModel->getNumFunctionDefinitions();
          for (i = 0;i < iMax;++i)
            {
              FunctionDefinition* p = pSBMLModel->getFunctionDefinition(i);
              if (level == 1)
                {
                  sbmlMap[p->getName()] = p;
                }
              else
                {
                  sbmlMap[p->getId()] = p;
                }
            }
          iMax = pSBMLModel->getNumCompartments();
          for (i = 0;i < iMax;++i)
            {
              Compartment* p = pSBMLModel->getCompartment(i);
              if (level == 1)
                {
                  sbmlMap[p->getName()] = p;
                }
              else
                {
                  sbmlMap[p->getId()] = p;
                }
            }
          iMax = pSBMLModel->getNumParameters();
          for (i = 0;i < iMax;++i)
            {
              Parameter* p = pSBMLModel->getParameter(i);
              if (level == 1)
                {
                  sbmlMap[p->getName()] = p;
                }
              else
                {
                  sbmlMap[p->getId()] = p;
                }
            }
          iMax = pSBMLModel->getNumSpecies();
          for (i = 0;i < iMax;++i)
            {
              Species* p = pSBMLModel->getSpecies(i);
              if (level == 1)
                {
                  sbmlMap[p->getName()] = p;
                }
              else
                {
                  sbmlMap[p->getId()] = p;
                }
            }
          iMax = pSBMLModel->getNumReactions();
          for (i = 0;i < iMax;++i)
            {
              Reaction* p = pSBMLModel->getReaction(i);
              if (level == 1)
                {
                  sbmlMap[p->getName()] = p;
                }
              else
                {
                  sbmlMap[p->getId()] = p;
                }
            }

          // go through the copasi model and create a map of all objects that already have an sbml id
          CFunctionDB* pFunDB = CCopasiDataModel::Global->getFunctionList();
          iMax = pFunDB->loadedFunctions().size();
          for (i = 0;i < iMax;++i)
            {
              CEvaluationTree* p = pFunDB->loadedFunctions()[i];
              std::string sbmlId = p->getSBMLId();
              if (!sbmlId.empty())
                {
                  std::map<std::string, SBase*>::iterator pos = sbmlMap.find(sbmlId);
                  if (pos != sbmlMap.end())
                    {
                      this->mCopasi2SBMLMap[p] = pos->second;
                      sbmlMap.erase(pos);
                    }
                }
            }
          iMax = this->mpCopasiModel->getCompartments().size();
          for (i = 0;i < iMax;++i)
            {
              CCompartment* p = this->mpCopasiModel->getCompartments()[i];
              std::string sbmlId = p->getSBMLId();
              if (!sbmlId.empty())
                {
                  std::map<std::string, SBase*>::iterator pos = sbmlMap.find(sbmlId);
                  if (pos != sbmlMap.end())
                    {
                      this->mCopasi2SBMLMap[p] = pos->second;
                      sbmlMap.erase(pos);
                    }
                }
            }
          iMax = this->mpCopasiModel->getMetabolites().size();
          for (i = 0;i < iMax;++i)
            {
              CMetab* p = this->mpCopasiModel->getMetabolites()[i];
              std::string sbmlId = p->getSBMLId();
              if (!sbmlId.empty())
                {
                  std::map<std::string, SBase*>::iterator pos = sbmlMap.find(sbmlId);
                  if (pos != sbmlMap.end())
                    {
                      this->mCopasi2SBMLMap[p] = pos->second;
                      sbmlMap.erase(pos);
                    }
                }
            }
          iMax = this->mpCopasiModel->getModelValues().size();
          for (i = 0;i < iMax;++i)
            {
              CModelValue* p = this->mpCopasiModel->getModelValues()[i];
              std::string sbmlId = p->getSBMLId();
              if (!sbmlId.empty())
                {
                  std::map<std::string, SBase*>::iterator pos = sbmlMap.find(sbmlId);
                  if (pos != sbmlMap.end())
                    {
                      this->mCopasi2SBMLMap[p] = pos->second;
                      sbmlMap.erase(pos);
                    }
                }
            }
          iMax = this->mpCopasiModel->getReactions().size();
          for (i = 0;i < iMax;++i)
            {
              CReaction* p = this->mpCopasiModel->getReactions()[i];
              std::string sbmlId = p->getSBMLId();
              if (!sbmlId.empty())
                {
                  std::map<std::string, SBase*>::iterator pos = sbmlMap.find(sbmlId);
                  if (pos != sbmlMap.end())
                    {
                      this->mCopasi2SBMLMap[p] = pos->second;
                      sbmlMap.erase(pos);
                    }
                }
            }
          // add the model
          this->mCopasi2SBMLMap[this->mpCopasiModel] = pSBMLModel;
          while (sbmlMap.size() > 0)
            {
              // delete all SBML objects that don't have corresponding Copasi objects
              std::map<std::string, SBase*>::iterator pos = sbmlMap.begin();
              SBase* p = pos->second;
              switch (p->getTypeCode())
                {
                case SBML_FUNCTION_DEFINITION:
                  this->removeFromList(pSBMLModel->getListOfFunctionDefinitions(), p);
                  break;
                case SBML_COMPARTMENT:
                  this->removeFromList(pSBMLModel->getListOfCompartments(), p);
                  break;
                case SBML_SPECIES:
                  this->removeFromList(pSBMLModel->getListOfSpecies(), p);
                  break;
                case SBML_REACTION:
                  this->removeFromList(pSBMLModel->getListOfReactions(), p);
                  break;
                case SBML_PARAMETER:
                  this->removeFromList(pSBMLModel->getListOfParameters(), p);
                  break;
                default:
                  fatalError();
                }
              sbmlMap.erase(pos);
            }
        }
    }
}

void SBMLExporter::removeFromList(ListOf& list, SBase* pObject)
{
  unsigned i, iMax = list.getNumItems();
  for (i = 0;i < iMax;++i)
    {
      if (list.get(i) == pObject)
        {
          list.remove(i);
          pdelete(pObject);
          break;
        }
    }
}

CEvaluationNode* SBMLExporter::createExpressionTree(const CFunction* const pFun, const std::vector<std::vector<std::string> >& arguments)
{
  if (!pFun || pFun->getVariables().size() != arguments.size()) fatalError();
  std::map< std::string, std::string > parameterMap;
  unsigned int i, iMax = arguments.size();
  for (i = 0;i < iMax;++i)
    {
      if (arguments[i].size() != 1) fatalError(); // we can't have arrays here.
      const CCopasiObject* pObject = GlobalKeys.get(arguments[i][0]);
      if (!pObject) fatalError();
      parameterMap[pFun->getVariables()[i]->getObjectName()] = "<" + pObject->getCN() + ">";
    }
  return this->createExpressionTree(pFun, parameterMap);
}

CEvaluationNode* SBMLExporter::createExpressionTree(const CFunction* const pFun, const std::map<std::string, std::string>& parameterMap)
{
  if (!pFun) fatalError();
  return this->createExpressionTree(pFun->getRoot(), parameterMap);
}

CEvaluationNode* SBMLExporter::createExpressionTree(const CEvaluationNode* const pNode, const std::map<std::string, std::string>& parameterMap)
{
  if (!pNode) fatalError();
  CEvaluationNode* pResultNode = NULL;
  const CFunction* pFun = NULL;
  std::map<std::string, std::string>::const_iterator pos;
  std::vector<std::vector<std::string> > arguments;
  const CEvaluationNode* pChildNode = NULL;
  std::vector<CCopasiContainer*> containerList;
  containerList.push_back(this->mpCopasiModel);
  const CCopasiObject* pObject = NULL;
  switch (CEvaluationNode::type(pNode->getType()))
    {
    case CEvaluationNode::CALL:
      pFun = dynamic_cast<const CFunction*>(CCopasiDataModel::Global->getFunctionList()->findFunction(pNode->getData()));
      assert(pFun);
      pChildNode = static_cast<const CEvaluationNode*>(pNode->getChild());
      while (pChildNode)
        {
          pos = parameterMap.find(pChildNode->getData());
          if (pos == parameterMap.end()) fatalError();
          pObject = CCopasiContainer::ObjectFromName(containerList, pos->second.substr(1, pos->second.size() - 2));
          assert(pObject);
          arguments.push_back(std::vector<std::string>());
          if (pObject->isReference())
            {
              pObject = pObject->getObjectParent();
              assert(pObject);
            }
          arguments[arguments.size() - 1].push_back(pObject->getKey());
          pChildNode = static_cast<const CEvaluationNode*>(pChildNode->getSibling());
        }
      pResultNode = this->createExpressionTree(pFun, arguments);
      break;
    case CEvaluationNode::VARIABLE:
      // replace the variable node with an object node
      pos = parameterMap.find(pNode->getData());
      if (pos == parameterMap.end()) fatalError();
      pResultNode = new CEvaluationNodeObject(CEvaluationNodeObject::ANY, pos->second);
      break;
    case CEvaluationNode::NUMBER:
      pResultNode = new CEvaluationNodeNumber((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pNode->getType()), pNode->getData());
      break;
    case CEvaluationNode::CONSTANT:
      pResultNode = new CEvaluationNodeConstant((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(pNode->getType()), pNode->getData());
      break;
    case CEvaluationNode::OPERATOR:
      pResultNode = new CEvaluationNodeOperator((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType()), pNode->getData());
      break;
    case CEvaluationNode::CHOICE:
      pResultNode = new CEvaluationNodeChoice((CEvaluationNodeChoice::SubType)CEvaluationNode::subType(pNode->getType()), pNode->getData());
      break;
    case CEvaluationNode::LOGICAL:
      pResultNode = new CEvaluationNodeLogical((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(pNode->getType()), pNode->getData());
      break;
    default:
      fatalError();
      break;
    }
  pChildNode = static_cast<const CEvaluationNode*>(pNode->getChild());
  while (pChildNode)
    {
      pResultNode->addChild(this->createExpressionTree(pChildNode, parameterMap));
      pChildNode = static_cast<const CEvaluationNode*>(pChildNode->getSibling());
    }
  assert(pResultNode);
  return pResultNode;
}

bool SBMLExporter::isSetExportExpressions() const
  {
    return this->mExportExpressions;
  }

void SBMLExporter::setExportExpressions(bool value)
{
  this->mExportExpressions = value;
}

const std::list<const CEvaluationTree*>& SBMLExporter::getUsedFunctionList() const
  {
    return this->mUsedFunctions;
  }
