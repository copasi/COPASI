/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/Attic/SBMLExporter.cpp,v $
   $Revision: 1.38 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/07/04 15:26:44 $
   End CVS Header */

#include <math.h>

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CVersion.h"

#include "SBMLExporter.h"
#include "UnitConversionFactory.hpp"

//#include "sbml/SBMLTypes.h"
#include "sbml/Unit.h"
#include "sbml/UnitDefinition.h"
#include "sbml/UnitKind.h"
#include "sbml/SBMLDocument.h"
#include "sbml/SBMLWriter.h"

#include "sbml/ModifierSpeciesReference.h"
#include "sbml/SpeciesReference.h"
#include "xml/CCopasiXMLInterface.h"

#include <fstream>

const char* SBMLExporter::HTML_HEADER = "<body xmlns=\"http://www.w3.org/1999/xhtml\">";

const char* SBMLExporter::HTML_FOOTER = "</body>";

/**
 ** Constructor for the exporter.
 */
SBMLExporter::SBMLExporter(): sbmlDocument(NULL)
{
  /* nothing to do */
}

/**
 ** Destructor for the exporter.
 */
SBMLExporter::~SBMLExporter()
{
  /* delete the SBMLDocument created if it is not NULL */
  if (this->sbmlDocument != NULL)
    {
      delete this->sbmlDocument;
    }
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
  /* create the SBMLDocument from the copasi model */
  this->sbmlDocument = this->createSBMLDocumentFromCModel(copasiModel, sbmlLevel, sbmlVersion);
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
  SBMLDocument* sbmlDocument = CCopasiDataModel::Global->getCurrentSBMLDocument();
  if (!sbmlDocument)
    {
      /* create a new document object */
      sbmlDocument = new SBMLDocument();
    }
  sbmlDocument->setLevel(sbmlLevel);
  sbmlDocument->setVersion(sbmlVersion);
  /* create the model object from the copasi model */
  Model* sbmlModel = this->createSBMLModelFromCModel(copasiModel);
  if (sbmlDocument->getModel() != sbmlModel)
    {
      sbmlDocument->setModel(sbmlModel);
    }
  return sbmlDocument;
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
          if (!UnitConversionFactory::areEqual(*sbmlModel->getUnitDefinition("volume"), *uDef));
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
          if (!UnitConversionFactory::areEqual(*sbmlModel->getUnitDefinition("time"), *uDef));
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
          if (!UnitConversionFactory::areEqual(*sbmlModel->getUnitDefinition("substance"), *uDef));
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
      sbmlCompartment->setId(copasiCompartment->getKey().c_str());
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
      sbmlSpecies->setId(copasiMetabolite->getKey().c_str());
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
      pParameter->setId(pModelValue->getKey());
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
    }
  this->mHandledSBMLObjects.push_back(sbmlReaction);
  sbmlReaction->setId(copasiReaction->getKey().c_str());
  sbmlReaction->setName(copasiReaction->getObjectName().c_str());
  sbmlReaction->setReversible(copasiReaction->isReversible());
  const CChemEq chemicalEquation = copasiReaction->getChemEq();
  /* Add all substrates */
  unsigned int counter;
  for (counter = 0; counter < chemicalEquation.getSubstrates().size(); counter++)
    {
      CChemEqElement* element = chemicalEquation.getSubstrates()[counter];
      SpeciesReference* sRef = new SpeciesReference();
      sRef->setSpecies(element->getMetaboliteKey().c_str());
      sRef->setStoichiometry(element->getMultiplicity());
      sRef->setDenominator(1);
      sbmlReaction->addReactant(*sRef);
    }
  /* Add all products */
  for (counter = 0; counter < chemicalEquation.getProducts().size(); counter++)
    {
      CChemEqElement* element = chemicalEquation.getProducts()[counter];
      SpeciesReference* sRef = new SpeciesReference();
      sRef->setSpecies(element->getMetaboliteKey().c_str());
      sRef->setStoichiometry(element->getMultiplicity());
      sRef->setDenominator(1);
      sbmlReaction->addProduct(*sRef);
    }
  /* Add all modifiers */
  for (counter = 0; counter < chemicalEquation.getModifiers().size(); counter++)
    {
      CChemEqElement* element = chemicalEquation.getModifiers()[counter];
      ModifierSpeciesReference* sRef = new ModifierSpeciesReference();
      sRef->setSpecies(element->getMetaboliteKey().c_str());
      sbmlReaction->addModifier(*sRef);
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
  if (copasiReaction->getFunction().getType() == CFunction::MassAction)
    {
      const CMassAction cMassAction = static_cast<const CMassAction>(copasiReaction->getFunction());
      /* create the ASTNode that multiplies all substrates with the first
      ** kinetic constant.
      */
      ASTNode* forwardNode = new ASTNode(AST_TIMES);

      ASTNode* parameterNode1 = new ASTNode(AST_NAME);
      std::string parameterName1 = cMassAction.getVariables()[0]->getObjectName();
      parameterNode1->setName(parameterName1.c_str());
      // only create a parameter instance if it is a local parameter
      if (copasiReaction->isLocalParameter(0))
        {
          Parameter* parameter1 = new Parameter();
          parameter1->setId(parameterName1.c_str());
          double value = copasiReaction->getParameterValue(parameterName1);
          // if the value is NaN, leave the parameter value unset.
          if (!isnan(value))
            {
              parameter1->setValue(value);
            }
          kLaw->addParameter(*parameter1);
        }
      else
        {
          // Need to get the name from the mapping
          std::string modelValueKey = copasiReaction->getParameterMappings()[0][0];
          parameterNode1->setName(modelValueKey.c_str());
        }
      forwardNode->addChild(parameterNode1);
      forwardNode->addChild(this->createTimesTree(copasiReaction->getChemEq().getSubstrates()));
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
          // only create a parameter instance if it is a local parameter
          if (copasiReaction->isLocalParameter(2))
            {
              Parameter* parameter2 = new Parameter();
              parameter2->setId(parameterName2);
              double value = copasiReaction->getParameterValue(parameterName2);
              if (!isnan(value))
                {
                  parameter2->setValue(value);
                }
              parameter2->setValue(copasiReaction->getParameterValue(parameterName2));
              kLaw->addParameter(*parameter2);
            }
          else
            {
              // Need to get the name from the mapping
              std::string modelValueKey = copasiReaction->getParameterMappings()[2][0];
              parameterNode2->setName(modelValueKey.c_str());
            }
          backwardNode->addChild(parameterNode2);

          backwardNode->addChild(this->createTimesTree(copasiReaction->getChemEq().getProducts()));
          ASTNode* tempNode = new ASTNode(AST_MINUS);
          tempNode->addChild(forwardNode);
          tempNode->addChild(backwardNode);
          forwardNode = tempNode;
        }

      /*
       ** If the reaction takes place in a single compartment, the rate law has
       ** to be converted from concentration/time to substance/time by
       ** multiplying the rate law with the volume of the compartment.
       */
      if (copasiReaction->getCompartmentNumber() == 1)
        {
          ASTNode* tNode = new ASTNode(AST_TIMES);
          ASTNode* vNode = new ASTNode(AST_REAL);
          double volume = 0.0;
          if (copasiReaction->getChemEq().getSubstrates().size() != 0)
            {
              volume = copasiReaction->getChemEq().getSubstrates()[0]->getMetabolite().getCompartment()->getInitialVolume();
            }
          else
            {
              volume = copasiReaction->getChemEq().getProducts()[0]->getMetabolite().getCompartment()->getInitialVolume();
            }
          /* only multiply if the volume is neither 1 nor 0 */
          if (volume != 1.0 && volume != 0.0)
            {
              /* if the whole function already has been divided by the same
              ** volume, e.g. by a formaer export, drop one level instead of
              ** adding another one */
              if ((forwardNode->getType() == AST_DIVIDE) && (forwardNode->getRightChild()->getType() == AST_REAL) && (forwardNode->getRightChild()->getReal() == volume))
                {
                  forwardNode = forwardNode->getLeftChild();
                }
              else
                {
                  vNode->setValue(volume);
                  tNode->addChild(forwardNode);
                  tNode->addChild(vNode);
                  forwardNode = tNode;
                }
            }
        }
      kLaw->setMath(forwardNode);
    }
  /* if the copasi CFunction does not specify a mass-action kinetic, it is a
  ** CKinFunction */
  else
    {
      CKinFunction cKinFunction = static_cast<CKinFunction>(copasiReaction->getFunction());
      ASTNode* node = this->createASTNodeFromCNodeK(cKinFunction.getNodes()[0]->getLeft(), cKinFunction, copasiReaction->getParameterMappings());

      /*
       ** If the reaction takes place in a single compartment, the rate law has
       ** to be converted from concentration/time to substance/time by
       ** multiplying the rate law with the volume of the compartment.
       */
      if (copasiReaction->getCompartmentNumber() == 1)
        {
          ASTNode* tNode = new ASTNode(AST_TIMES);
          ASTNode* vNode = new ASTNode(AST_REAL);
          double volume = 0.0;
          if (copasiReaction->getChemEq().getSubstrates().size() != 0)
            {
              volume = copasiReaction->getChemEq().getSubstrates()[0]->getMetabolite().getCompartment()->getInitialVolume();
            }
          else
            {
              volume = copasiReaction->getChemEq().getProducts()[0]->getMetabolite().getCompartment()->getInitialVolume();
            }
          if (volume != 1.0 && volume != 0.0)
            {
              /* if the whole function already has been divided by the same
              ** volume, e.g. by a formaer export, drop one level instead of
              ** adding another one */
              if ((node->getType() == AST_DIVIDE) && (node->getRightChild()->getType() == AST_REAL) && (node->getRightChild()->getReal() == volume))
                {
                  node = node->getLeftChild();
                }
              else
                {
                  vNode->setValue(volume);
                  tNode->addChild(vNode);
                  tNode->addChild(node);
                  node = tNode;
                }
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
    }
  return kLaw;
}

/**
 ** This method creates an ASTNode tree where all the species specified in
 ** the given vector are multiplied. This is used to create the mass action
 ** kinetic law.
 */
ASTNode* SBMLExporter::createASTNodeFromCNodeK(const CNodeK& cNodeK, const CKinFunction& kinFunction, const std::vector< std::vector < std::string > >& vect)
{
  ASTNode* node = new ASTNode();
  char mType = cNodeK.getType();
  char mSubtype = cNodeK.getSubtype();
  ASTNode* childNode = NULL;
  switch (mType)
    {
    case N_NUMBER:
      //ASTNode_setType(node, AST_REAL);
      node->setValue(cNodeK.getConstant());
      break;
    case N_IDENTIFIER:
      node->setType(AST_NAME);
      CFunctionParameter::DataType dataType;
      /* resolve the parameter name mapping */
      if (mSubtype == N_KCONSTANT)
        {
          node->setName(cNodeK.getName().c_str());
        }
      else
        {
          node->setName(vect[kinFunction.getVariables().findParameterByName(cNodeK.getName(), dataType)][0].c_str());
        }
      break;
    case N_OPERATOR:
      switch (mSubtype)
        {
        case '+':
          node->setType(AST_PLUS);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case '-':
          node->setType(AST_MINUS);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case '*':
          node->setType(AST_TIMES);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case '/':
          node->setType(AST_DIVIDE);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case '^':
          node->setType(AST_POWER);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          node->addChild(childNode);
          break;
        default:
          break;
        }
      break;
    case N_FUNCTION:
      switch (mSubtype)
        {
        case '+':
          node = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          break;
        case '-':
          node->setType(AST_MINUS);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case N_EXP:
          node->setType(AST_FUNCTION_EXP);
          node->setName("exp");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case N_LOG:
          node->setType(AST_FUNCTION_LN);
          node->setName("ln");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case N_LOG10:
          node->setType(AST_FUNCTION_LOG);
          node->setName("log");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case N_SIN:
          node->setType(AST_FUNCTION_SIN);
          node->setName("sin");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case N_COS:
          node->setType(AST_FUNCTION_COS);
          node->setName("cos");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          break;
        default:
          break;
        }
      break;
    default:
      break;
    }
  return node;
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
      node->setName(vect[pos]->getMetaboliteKey().c_str());
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
      child->setName(vect[pos]->getMetaboliteKey().c_str());

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
  for (i = list->getNumItems(); i > 0;++i)
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
  for (i = list->getNumItems(); i > 0;++i)
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
  for (i = list->getNumItems(); i > 0;++i)
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
  for (i = list->getNumItems(); i > 0;++i)
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
