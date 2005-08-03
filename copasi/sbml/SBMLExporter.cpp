/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/Attic/SBMLExporter.cpp,v $
   $Revision: 1.50 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/08/03 11:11:52 $
   End CVS Header */

#include <math.h>
#include <list>

#include <algorithm>

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CVersion.h"

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
SBMLExporter::SBMLExporter(): sbmlDocument(NULL), mpIdSet(NULL)
{
  /* nothing to do */
}

/**
 ** Destructor for the exporter.
 */
SBMLExporter::~SBMLExporter()
{
  /* delete the SBMLDocument created if it is not NULL
    if (this->sbmlDocument != NULL)
    {
      delete this->sbmlDocument;
    }
    */
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

  this->createFunctionDefinitions();

  return this->sbmlDocument;
}

/**
 ** This method taked a copasi CModel and generates a SBML Model object
 **  which is returned. On failure NULL is returned.
 */
Model* SBMLExporter::createSBMLModelFromCModel(CModel* copasiModel)
{
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
  if (!(copasiModel->getVolumeUnit() == "l"))
    {
      UnitDefinition* uDef = this->createSBMLVolumeUnitDefinitionFromCopasiVolumeUnit(copasiModel->getVolumeUnit());
      if (sbmlModel->getUnitDefinition("volume"))
        {
          if (!UnitConversionFactory::areEqual(*sbmlModel->getUnitDefinition("volume"), *uDef))
            {
              ListOf& list = sbmlModel->getListOfUnitDefinitions();
              unsigned int i = list.getNumItems();
              for (; i > 0;++i)
                {
                  UnitDefinition* uDef = dynamic_cast<UnitDefinition*>(list.get(i - 1));
                  if (uDef->getId() == "volume")
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
  if (!(copasiModel->getTimeUnit() == "s"))
    {
      UnitDefinition* uDef = this->createSBMLTimeUnitDefinitionFromCopasiTimeUnit(copasiModel->getTimeUnit());
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
  if (!(copasiModel->getQuantityUnit() == "Mol"))
    {
      UnitDefinition* uDef = this->createSBMLSubstanceUnitDefinitionFromCopasiQuantityUnit(copasiModel->getQuantityUnit());
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
  unsigned int counter;
  for (counter = 0; counter < copasiModel->getCompartments().size(); counter++)
    {
      Compartment* sbmlCompartment = this->createSBMLCompartmentFromCCompartment(copasiModel->getCompartments()[counter]);
      if (!sbmlModel->getCompartment(sbmlCompartment->getId()))
        {
          sbmlModel->addCompartment(*sbmlCompartment);
        }
    }
  /* create all metabolites */
  for (counter = 0; counter < copasiModel->getMetabolites().size(); counter++)
    {
      Species* sbmlSpecies = this->createSBMLSpeciesFromCMetab(copasiModel->getMetabolites()[counter]);
      if (!sbmlModel->getSpecies(sbmlSpecies->getId()))
        {
          sbmlModel->addSpecies(*sbmlSpecies);
        }
    }
  /* create all global parameters */
  for (counter = 0; counter < copasiModel->getModelValues().size(); counter++)
    {
      Parameter* sbmlParameter = this->createSBMLParameterFromCModelValue(copasiModel->getModelValues()[counter]);
      if (!sbmlModel->getParameter(sbmlParameter->getId()))
        {
          sbmlModel->addParameter(*sbmlParameter);
        }
    }
  /* create all reactions */
  for (counter = 0; counter < copasiModel->getReactions().size(); counter++)
    {
      Reaction* sbmlReaction = this->createSBMLReactionFromCReaction(copasiModel->getReactions()[counter]);
      if (!sbmlModel->getReaction(sbmlReaction->getId()))
        {
          sbmlModel->addReaction(*sbmlReaction);
        }
    }
  pdelete(this->mpIdSet);

  return sbmlModel;
}

/**
 ** This method takes a string that specifies the time unit used in the
 ** copasi model and returns a pointer to the corresponding SBML
 ** UnitDefinition object.
 */
UnitDefinition* SBMLExporter::createSBMLTimeUnitDefinitionFromCopasiTimeUnit(const std::string& u)
{
  UnitDefinition* uDef = new UnitDefinition("time");
  uDef->setId("time");
  Unit* unit;

  if (u == "d")
    {
      unit = new Unit(UNIT_KIND_SECOND, 1, 0);
      unit->setMultiplier(86400);
    }
  else if (u == "h")
    {
      unit = new Unit(UNIT_KIND_SECOND, 1, 0);
      unit->setMultiplier(3600);
    }
  else if (u == "m")
    {
      unit = new Unit(UNIT_KIND_SECOND, 1, 0);
      unit->setMultiplier(60);
    }

  else if (u == "ms")
    {
      unit = new Unit(UNIT_KIND_SECOND, 1, -3);
    }
  else if (u == "\xc2\xb5s")
    {
      unit = new Unit(UNIT_KIND_SECOND, 1, -6);
    }
  else if (u == "ns")
    {
      unit = new Unit(UNIT_KIND_SECOND, 1, -9);
    }
  else if (u == "ps")
    {
      unit = new Unit(UNIT_KIND_SECOND, 1, -12);
    }
  else if (u == "fs")
    {
      unit = new Unit(UNIT_KIND_SECOND, 1, -15);
    }
  else
    {
      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, "SBMLExporter Error: Unknown copasi time unit.");
    }

  uDef->addUnit(*unit);
  return uDef;
}

/**
 ** This method takes a string that specifies the substance unit used in the
 ** copasi model and returns a pointer to the corresponding SBML
 ** UnitDefinition object.
 */
UnitDefinition* SBMLExporter::createSBMLSubstanceUnitDefinitionFromCopasiQuantityUnit(const std::string& u)
{
  UnitDefinition* uDef = new UnitDefinition("substance");
  uDef->setId("substance");
  Unit* unit;
  if (u == "mMol")
    {
      unit = new Unit(UNIT_KIND_MOLE, 1, -3);
    }
  else if (u == "\xc2\xb5Mol")
    {
      unit = new Unit(UNIT_KIND_MOLE, 1, -6);
    }
  else if (u == "nMol")
    {
      unit = new Unit(UNIT_KIND_MOLE, 1, -9);
    }
  else if (u == "pMol")
    {
      unit = new Unit(UNIT_KIND_MOLE, 1, -12);
    }
  else if (u == "fMol")
    {
      unit = new Unit(UNIT_KIND_MOLE, 1, -15);
    }
  else if (u == "#")
    {
      unit = new Unit(UNIT_KIND_ITEM, 1, 1);
    }
  else
    {
      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, "SBMLExporter Error: Unknown copasi quantity unit.");
    }
  uDef->addUnit(*unit);
  return uDef;
}

/**
 ** This method takes a string that specifies the volume unit used in the
 ** copasi model and returns a pointer to the corresponding SBML
 ** UnitDefinition object.
 */
UnitDefinition* SBMLExporter::createSBMLVolumeUnitDefinitionFromCopasiVolumeUnit(const std::string& u)
{
  UnitDefinition* uDef = new UnitDefinition("volume");
  uDef->setId("volume");
  Unit* unit;
  if (u == "ml")
    {
      unit = new Unit(UNIT_KIND_LITRE, 1, -3);
    }
  else if (u == "\xc2\xb5l")
    {
      unit = new Unit(UNIT_KIND_LITRE, 1, -6);
    }
  else if (u == "nl")
    {
      unit = new Unit(UNIT_KIND_LITRE, 1, -9);
    }
  else if (u == "pl")
    {
      unit = new Unit(UNIT_KIND_LITRE, 1, -12);
    }
  else if (u == "fl")
    {
      unit = new Unit(UNIT_KIND_LITRE, 1, -15);
    }
  else if (u == "m3")
    {
      unit = new Unit(UNIT_KIND_METRE, 3, 1);
    }
  else
    {
      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, "SBMLExporter Error: Unknown copasi volume unit.");
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
      std::string parameterName1 = cMassAction.getVariables()[0]->getObjectName();
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
          std::string parameterName2 = cMassAction.getVariables()[2]->getObjectName();
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
      CEvaluationNode* pTmpRoot = copasiReaction->getExpressionTree();
      // walk the tree and look for function calls
      std::list<const CEvaluationTree*> usedFunctionList;
      this->findUsedFunctions(pTmpRoot, usedFunctionList);
      node = pTmpRoot->toAST();
      pdelete(pTmpRoot);
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
      if (para->getUsage() == "PARAMETER")
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

/*
void SBMLExporter::findUsedFunctions(CEvaluationNode* pNode,std::list<std::string>& usedFunctionList)
{
    if(pNode)
    {
        if(CEvaluationNode::type(pNode->getType())==CEvaluationNode::CALL)
        {
            CFunctionDB* pFunDB=CCopasiDataModel::Global->getFunctionList();
            CEvaluationTree* pFun=pFunDB->findFunction(pNode->getData());
            if(!pFun)
            {
                CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION,MCSBML + 15,pNode->getData().c_str());
            }
            if(usedFunctionList.find(pFun)!=usedFunctionList.end())
            {
                // we have a loop
                CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION,MCSBML + 16);
            }
            else
            {
              usedFunctionList.push_back(pFun);
              // go through the tree of that function as well
              this->findUsedFunctions(pFun->getRoot(),usedFunctionList);
              // find the list node for the current function name
              // add all nodes that come after it to the mUsedFunctions
              // delete those nodes 
            }
        }
        else
        {
            CEvaluationNode* pChildNode=static_cast<CEvaluationNode*>(pNode->getChild());
            while(pChildNode)
            {
                this->findUsedFunctions(pChildNode,usedFunctionList);
            }
        }
    }
}
 */

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
          if (!this->existsInList(pFun, this->mUsedFunctions))
            {
              usedFunctionList.push_back(pFun);
              std::list<const CEvaluationTree*>::iterator pos = usedFunctionList.end();
              --pos;
              this->findUsedFunctions(pFun->getRoot(), usedFunctionList);
              // add this function to mUsedFunctions after the last function in usedFunctionList
              // if usedFunctionList does not have any entries after pos, just insert the function
              // at the beginning
              if (usedFunctionList.back() == (*pos))
                {
                  this->mUsedFunctions.push_front(pFun);
                }
              else
                {
                  std::list<const CEvaluationTree*>::iterator it = this->mUsedFunctions.begin();
                  std::list<const CEvaluationTree*>::iterator endIt = this->mUsedFunctions.end();
                  std::list<const CEvaluationTree*>::iterator afterPos = this->mUsedFunctions.end();
                  while ((it != endIt) && (usedFunctionList.back() != (*pos)))
                    {
                      std::list<const CEvaluationTree*>::iterator it2 = usedFunctionList.begin();
                      std::list<const CEvaluationTree*>::iterator endIt2 = usedFunctionList.end();
                      while (it2 != endIt2)
                        {
                          if ((*it) == (*it2))
                            {
                              usedFunctionList.erase(it2);
                              afterPos = it;
                              break;
                            }
                        }
                      ++it;
                    }
                  afterPos++;
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
  std::map<std::string, std::string> replacementMap;

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
      replacementMap[(*it)->getObjectName()] = (*it)->getSBMLId();
      FunctionDefinition* pSBMLFunDef = this->createSBMLFunctionDefinitionFromCEvaluationTree((*it), replacementMap);
      ++it;
    }
}

FunctionDefinition* SBMLExporter::createSBMLFunctionDefinitionFromCEvaluationTree(const CEvaluationTree* tree, const std::map<std::string, std::string>& replacementMap)
{
  // convert the tree root to an AST tree.
  FunctionDefinition& pFunDef = this->sbmlDocument->getModel()->createFunctionDefinition();
  pFunDef.setId(tree->getSBMLId());

  ASTNode* pFunNode = tree->getRoot()->toAST();
  // go through the AST tree and replace all function call nodes with with a call to the sbml id
  this->replaceFunctionNames(pFunNode, replacementMap);
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

void SBMLExporter::replaceFunctionNames(ASTNode* pNode, std::map<std::string, std::string> replacementMap)
{
  if (pNode->getType() == AST_FUNCTION)
    {
      pNode->setName(replacementMap[pNode->getName()].c_str());
      assert(pNode->getName() != "");
    }
  unsigned int i, iMax = pNode->getNumChildren();
  for (i = 0; i < iMax;++i)
    {
      this->replaceFunctionNames(pNode->getChild(i), replacementMap);
    }
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
