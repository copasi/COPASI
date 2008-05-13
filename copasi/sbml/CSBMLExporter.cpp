// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/CSBMLExporter.cpp,v $
//   $Revision: 1.24 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/05/13 14:13:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CSBMLExporter.h"

#include "SBMLImporter.h"
#include "utilities/CCopasiException.h"
#include "sbml/SBMLDocument.h"
#include "sbml/Compartment.h"
#include "sbml/Model.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/Reaction.h"
#include "sbml/KineticLaw.h"
#include "sbml/SBMLWriter.h"
#include "sbml/SpeciesReference.h"
#include "sbml/math/ASTNode.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "SBMLIncompatibility.h"
#include "model/CCompartment.h"
#include "model/CModel.h"
#include "model/CEvent.h"
#include "model/CMetab.h"
#include "function/CExpression.h"
#include "function/CEvaluationNode.h"
#include "model/CReaction.h"
#include "utilities/CCopasiParameter.h"
#include "model/CModelValue.h"
#include "function/CFunction.h"
#include "report/CKeyFactory.h"
#include "ConverterASTNode.h"
#include "utilities/CCopasiTree.h"
#include "model/CChemEqElement.h"
#include "utilities/CVersion.h"
#include "sbml/Trigger.h"
#include "sbml/Event.h"
#include "sbml/EventAssignment.h"
#include <sbml/xml/XMLInputStream.h>
#include "compareExpressions/compare_utilities.h"
#include "MIRIAM/CRDFUtilities.h"

CSBMLExporter::CSBMLExporter(): mpSBMLDocument(NULL), mSBMLLevel(2), mSBMLVersion(1), mVariableVolumes(false), mpAvogadro(NULL), mAvogadroCreated(false), mMIRIAMWarning(false)
{}

CSBMLExporter::~CSBMLExporter()
{
  pdelete(mpSBMLDocument);
};

/**
 * Creates the units for the SBML model.
 */
void CSBMLExporter::createUnits(const CCopasiDataModel& dataModel)
{
  createVolumeUnit(dataModel);
  createTimeUnit(dataModel);
  createSubstanceUnit(dataModel);
}

/**
 * Creates the time unit for the SBML model.
 */
void CSBMLExporter::createTimeUnit(const CCopasiDataModel& dataModel)
{
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL) return;
  UnitDefinition uDef("time");
  uDef.setId("time");
  Unit unit;

  switch (dataModel.getModel()->getTimeUnitEnum())
    {
    case CModel::d:
      unit = Unit(UNIT_KIND_SECOND, 1, 0);
      unit.setMultiplier(86400);
      break;
    case CModel::h:
      unit = Unit(UNIT_KIND_SECOND, 1, 0);
      unit.setMultiplier(3600);
      break;
    case CModel::min:
      unit = Unit(UNIT_KIND_SECOND, 1, 0);
      unit.setMultiplier(60);
      break;
    case CModel::s:
      unit = Unit(UNIT_KIND_SECOND, 1, 0);
      unit.setMultiplier(1);
      break;
    case CModel::ms:
      unit = Unit(UNIT_KIND_SECOND, 1, -3);
      break;
    case CModel::micros:
      unit = Unit(UNIT_KIND_SECOND, 1, -6);
      break;
    case CModel::ns:
      unit = Unit(UNIT_KIND_SECOND, 1, -9);
      break;
    case CModel::ps:
      unit = Unit(UNIT_KIND_SECOND, 1, -12);
      break;
    case CModel::fs:
      unit = Unit(UNIT_KIND_SECOND, 1, -15);
      break;
    default:
      CCopasiMessage(CCopasiMessage::EXCEPTION, "SBMLExporter Error: Unknown copasi time unit.");
      break;
    }

  uDef.addUnit(&unit);
  Model* pSBMLModel = this->mpSBMLDocument->getModel();
  UnitDefinition* pUdef = pSBMLModel->getUnitDefinition("time");
  if (pUdef != NULL)
    {
      // check if it is the same unit as the exisiting one if there is one
      // if yes, return, else replace the existing one
      if (!SBMLImporter::areSBMLUnitDefinitionsIdentical(pUdef, &uDef))
        {
          (*pUdef) = uDef;
        }
    }
  else
    {
      if (unit.getKind() != UNIT_KIND_SECOND || unit.getScale() != 0 || unit.getExponent() != 1 || unit.getMultiplier() != 1.0)
        {
          // set the unit definition
          pSBMLModel->addUnitDefinition(&uDef);
        }
    }
}

/**
 * Creates the volume unit for the SBML model.
 */
void CSBMLExporter::createVolumeUnit(const CCopasiDataModel& dataModel)
{
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL) return;
  UnitDefinition uDef("volume");
  uDef.setId("volume");
  Unit unit;
  switch (dataModel.getModel()->getVolumeUnitEnum())
    {
    case CModel::l:
      unit = Unit(UNIT_KIND_LITRE, 1, 0);
      break;
    case CModel::ml:
      unit = Unit(UNIT_KIND_LITRE, 1, -3);
      break;
    case CModel::microl:
      unit = Unit(UNIT_KIND_LITRE, 1, -6);
      break;
    case CModel::nl:
      unit = Unit(UNIT_KIND_LITRE, 1, -9);
      break;
    case CModel::pl:
      unit = Unit(UNIT_KIND_LITRE, 1, -12);
      break;
    case CModel::fl:
      unit = Unit(UNIT_KIND_LITRE, 1, -15);
      break;
    case CModel::m3:
      unit = Unit(UNIT_KIND_METRE, 3, 0);
      break;
    default:
      CCopasiMessage(CCopasiMessage::EXCEPTION, "SBMLExporter Error: Unknown copasi volume unit.");
      break;
    }
  uDef.addUnit(&unit);
  Model* pSBMLModel = this->mpSBMLDocument->getModel();
  UnitDefinition* pUdef = pSBMLModel->getUnitDefinition("volume");
  if (pUdef != NULL)
    {
      // check if it is the same unit as the exisiting one if there is one
      // if yes, return, else replace the existing one
      if (!SBMLImporter::areSBMLUnitDefinitionsIdentical(pUdef, &uDef))
        {
          (*pUdef) = uDef;
        }
    }
  else
    {
      if (unit.getKind() != UNIT_KIND_LITRE || unit.getScale() != 0 || unit.getExponent() != 1 || unit.getMultiplier() != 1.0)
        {
          // set the unit definition
          pSBMLModel->addUnitDefinition(&uDef);
        }
    }
}

/**
 * Creates the substance unit for the SBML model.
 */
void CSBMLExporter::createSubstanceUnit(const CCopasiDataModel& dataModel)
{
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL) return;
  UnitDefinition uDef("substance");
  uDef.setId("substance");
  Unit unit;
  switch (dataModel.getModel()->getQuantityUnitEnum())
    {
    case CModel::Mol:
      unit = Unit(UNIT_KIND_MOLE, 1, 0);
      break;
    case CModel::mMol:
      unit = Unit(UNIT_KIND_MOLE, 1, -3);
      break;
    case CModel::microMol:
      unit = Unit(UNIT_KIND_MOLE, 1, -6);
      break;
    case CModel::nMol:
      unit = Unit(UNIT_KIND_MOLE, 1, -9);
      break;
    case CModel::pMol:
      unit = Unit(UNIT_KIND_MOLE, 1, -12);
      break;
    case CModel::fMol:
      unit = Unit(UNIT_KIND_MOLE, 1, -15);
      break;
    case CModel::number:
      unit = Unit(UNIT_KIND_ITEM, 1, 0);
      break;
    default:
      CCopasiMessage(CCopasiMessage::EXCEPTION, "SBMLExporter Error: Unknown copasi quantity unit.");
      break;
    }
  uDef.addUnit(&unit);
  Model* pSBMLModel = this->mpSBMLDocument->getModel();
  UnitDefinition* pUdef = pSBMLModel->getUnitDefinition("substance");
  if (pUdef != NULL)
    {
      // check if it is the same unit as the exisiting one if there is one
      // if yes, return, else replace the existing one
      if (!SBMLImporter::areSBMLUnitDefinitionsIdentical(pUdef, &uDef))
        {
          (*pUdef) = uDef;
        }
    }
  else
    {
      if (unit.getKind() != UNIT_KIND_MOLE || unit.getScale() != 0 || unit.getExponent() != 1 || unit.getMultiplier() != 1.0)
        {
          // set the unit definition
          pSBMLModel->addUnitDefinition(&uDef);
        }
    }
}

/**
 * Creates the compartments for the model.
 */
void CSBMLExporter::createCompartments(CCopasiDataModel& dataModel)
{
  // make sure the SBML Document already exists anf that it has a Model set
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL) return;
  CCopasiVectorNS<CCompartment>::const_iterator it = dataModel.getModel()->getCompartments().begin(), endit = dataModel.getModel()->getCompartments().end();
  while (it != endit)
    {
      createCompartment(**it);
      ++it;
    }
}

/**
 * Creates the compartment for the given COPASI compartment.
 */
void CSBMLExporter::createCompartment(CCompartment& compartment)
{
  Compartment* pSBMLCompartment = NULL;
  std::string sbmlId = compartment.getSBMLId();
  if (!sbmlId.empty())
    {
      pSBMLCompartment = this->mpSBMLDocument->getModel()->getCompartment(sbmlId);
      if (pSBMLCompartment == NULL)
        {
          pSBMLCompartment = this->mpSBMLDocument->getModel()->createCompartment();
          this->mCOPASI2SBMLMap[&compartment] = pSBMLCompartment;
          pSBMLCompartment->setId(sbmlId);
        }
    }
  else
    {
      pSBMLCompartment = this->mpSBMLDocument->getModel()->createCompartment();
      this->mCOPASI2SBMLMap[&compartment] = pSBMLCompartment;
      sbmlId = CSBMLExporter::createUniqueId(this->mIdMap, "compartment_");
      compartment.setSBMLId(sbmlId);
      pSBMLCompartment->setId(sbmlId);
    }
  this->mIdMap.insert(std::make_pair(sbmlId, pSBMLCompartment));
  this->mHandledSBMLObjects.insert(pSBMLCompartment);
  pSBMLCompartment->setName(compartment.getObjectName().c_str());
  double value = compartment.getInitialValue();
  // if the value is NaN, unset the initial volume
  if (!isnan(value))
    {
      pSBMLCompartment->setVolume(value);
    }
  else
    {
      pSBMLCompartment->unsetVolume();
    }
  // fill assignment set
  // a compartment can either have an assignment or an initial assignment but not
  // both
  CModelEntity::Status status = compartment.getStatus();
  if (status == CModelEntity::ASSIGNMENT)
    {
      this->mVariableVolumes = true;
      this->mAssignmentVector.push_back(&compartment);
      pSBMLCompartment->setConstant(false);
      removeInitialAssignment(pSBMLCompartment->getId());
    }
  else if (status == CModelEntity::ODE)
    {
      this->mVariableVolumes = true;
      this->mODEVector.push_back(&compartment);
      pSBMLCompartment->setConstant(false);
      if (compartment.getInitialExpression() != "")
        {
          this->mInitialAssignmentVector.push_back(&compartment);
        }
      else
        {
          removeInitialAssignment(pSBMLCompartment->getId());
        }
    }
  else
    {
      // do this expolicitly since we might handle an exisiting object from an
      // earlier import that had it attribute set already
      pSBMLCompartment->setConstant(true);
      removeRule(pSBMLCompartment->getId());
      // fill initial assignment set
      if (compartment.getInitialExpression() != "")
        {
          // only set the flag if the initial assignments would actually be
          // exported.
          if (this->mSBMLLevel > 2 || (this->mSBMLLevel == 2 && this->mSBMLVersion >= 2))
            {
              this->mVariableVolumes = true;
            }
          this->mInitialAssignmentVector.push_back(&compartment);
        }
      else
        {
          removeInitialAssignment(pSBMLCompartment->getId());
        }
    }
  CSBMLExporter::updateMIRIAMAnnotation(&compartment, pSBMLCompartment, this->mMetaIdMap);
}

/**
 * Creates the compartments for the model.
 */
void CSBMLExporter::createMetabolites(CCopasiDataModel& dataModel)
{
  // make sure the SBML Document already exists anf that it has a Model set
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL) return;
  CCopasiVector<CMetab>::const_iterator it = dataModel.getModel()->getMetabolites().begin(), endit = dataModel.getModel()->getMetabolites().end();
  while (it != endit)
    {
      createMetabolite(**it);
      ++it;
    }
}

/**
 * Creates the species for the given COPASI metabolite.
 */
void CSBMLExporter::createMetabolite(CMetab& metab)
{
  Species* pSBMLSpecies = NULL;
  std::string sbmlId = metab.getSBMLId();
  if (!sbmlId.empty())
    {
      pSBMLSpecies = this->mpSBMLDocument->getModel()->getSpecies(sbmlId);
      if (pSBMLSpecies == NULL)
        {
          pSBMLSpecies = this->mpSBMLDocument->getModel()->createSpecies();
          this->mCOPASI2SBMLMap[&metab] = pSBMLSpecies;
          pSBMLSpecies->setId(sbmlId);
        }
    }
  else
    {
      pSBMLSpecies = this->mpSBMLDocument->getModel()->createSpecies();
      this->mCOPASI2SBMLMap[&metab] = pSBMLSpecies;
      sbmlId = CSBMLExporter::createUniqueId(this->mIdMap, "species_");
      metab.setSBMLId(sbmlId);
      pSBMLSpecies->setId(sbmlId);
    }
  this->mIdMap.insert(std::make_pair(sbmlId, pSBMLSpecies));
  this->mHandledSBMLObjects.insert(pSBMLSpecies);
  pSBMLSpecies->setName(metab.getObjectName().c_str());

  //const Compartment* pSBMLCompartment = dynamic_cast<const Compartment*>(this->mCOPASI2SBMLMap[const_cast<CCompartment*>(metab.getCompartment())]);
  const Compartment* pSBMLCompartment = this->mpSBMLDocument->getModel()->getCompartment(metab.getCompartment()->getSBMLId());
  assert(pSBMLCompartment);
  pSBMLSpecies->setCompartment(pSBMLCompartment->getId());
  if (this->mVariableVolumes == true)
    {
      pSBMLSpecies->setHasOnlySubstanceUnits(true);
    }
  double value = metab.getInitialConcentration();
  // if the value is NaN, unset the initial amount
  if (!isnan(value))
    {
      // if we set the concentration on a species that had the amount
      // set, the meaning of the model is different when the user changed
      // to size of the corresponding compartment
      // So if the amount had been set, we try to keep this.
      // we also have to set the iniital amount if the model has variable
      // volumes since those models export all species with the
      // hasOnlySubstanceUnits flag set to true
      if (pSBMLSpecies->isSetInitialAmount() || this->mVariableVolumes == true)
        {
          pSBMLSpecies->setInitialAmount(value*metab.getCompartment()->getInitialValue());
        }
      else
        {
          pSBMLSpecies->setInitialConcentration(value);
        }
    }
  else
    {
      pSBMLSpecies->unsetInitialConcentration();
      pSBMLSpecies->unsetInitialAmount();
    }
  CModelEntity::Status status = metab.getStatus();
  // a species can either have an assignment or an initial assignment but not
  // both
  if (status == CModelEntity::ASSIGNMENT)
    {
      this->mAssignmentVector.push_back(&metab);
      pSBMLSpecies->setConstant(false);
      pSBMLSpecies->setBoundaryCondition(true);
      removeInitialAssignment(pSBMLSpecies->getId());
    }
  else if (status == CModelEntity::ODE)
    {
      this->mODEVector.push_back(&metab);
      pSBMLSpecies->setConstant(false);
      pSBMLSpecies->setBoundaryCondition(true);
      if (metab.getInitialExpression() != "")
        {
          this->mInitialAssignmentVector.push_back(&metab);
        }
      else
        {
          removeInitialAssignment(pSBMLSpecies->getId());
        }
    }
  else if (status == CModelEntity::FIXED)
    {
      // do this expolicitly since we might handle an exisiting object from an
      // earlier import that had it attribute set already
      pSBMLSpecies->setConstant(true);
      pSBMLSpecies->setBoundaryCondition(true);
      removeRule(pSBMLSpecies->getId());
      // fill initial assignment set
      if (metab.getInitialExpression() != "")
        {
          this->mInitialAssignmentVector.push_back(&metab);
        }
      else
        {
          removeInitialAssignment(pSBMLSpecies->getId());
        }
    }
  else if (status == CModelEntity::REACTIONS)
    {
      pSBMLSpecies->setConstant(false);
      pSBMLSpecies->setBoundaryCondition(false);
      if (metab.getInitialExpression() != "")
        {
          this->mInitialAssignmentVector.push_back(&metab);
        }
    }
  CSBMLExporter::updateMIRIAMAnnotation(&metab, pSBMLSpecies, this->mMetaIdMap);
}

/**
 * Creates the parameters for the model.
 */
void CSBMLExporter::createParameters(CCopasiDataModel& dataModel)
{
  // make sure the SBML Document already exists anf that it has a Model set
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL) return;
  CCopasiVectorN<CModelValue>::const_iterator it = dataModel.getModel()->getModelValues().begin(), endit = dataModel.getModel()->getModelValues().end();
  while (it != endit)
    {
      createParameter(**it);
      ++it;
    }
}

/**
 * Creates the parameter for the given COPASI parameter.
 */
void CSBMLExporter::createParameter(CModelValue& modelValue)
{
  Parameter* pParameter = NULL;
  std::string sbmlId = modelValue.getSBMLId();
  if (!sbmlId.empty())
    {
      pParameter = this->mpSBMLDocument->getModel()->getParameter(sbmlId);
      if (pParameter == NULL)
        {
          pParameter = this->mpSBMLDocument->getModel()->createParameter();
          this->mCOPASI2SBMLMap[&modelValue] = pParameter;
          pParameter->setId(sbmlId);
        }
    }
  else
    {
      pParameter = this->mpSBMLDocument->getModel()->createParameter();
      this->mCOPASI2SBMLMap[&modelValue] = pParameter;
      sbmlId = CSBMLExporter::createUniqueId(this->mIdMap, "parameter_");
      modelValue.setSBMLId(sbmlId);
      pParameter->setId(sbmlId);
    }
  this->mIdMap.insert(std::make_pair(sbmlId, pParameter));
  this->mHandledSBMLObjects.insert(pParameter);
  pParameter->setName(modelValue.getObjectName());
  double value = modelValue.getInitialValue();
  // if the value is NaN, unset the parameters value
  if (!isnan(value))
    {
      pParameter->setValue(value);
    }
  else
    {
      pParameter->unsetValue();
    }
  // fill assignment set
  // a parameter can either have an assignment or an initial assignment but not
  // both
  CModelEntity::Status status = modelValue.getStatus();
  if (status == CModelEntity::ASSIGNMENT)
    {
      this->mAssignmentVector.push_back(&modelValue);
      pParameter->setConstant(false);
      removeInitialAssignment(pParameter->getId());
    }
  else if (status == CModelEntity::ODE)
    {
      this->mODEVector.push_back(&modelValue);
      pParameter->setConstant(false);
      if (modelValue.getInitialExpression() != "")
        {
          this->mInitialAssignmentVector.push_back(&modelValue);
        }
      else
        {
          removeInitialAssignment(pParameter->getId());
        }
    }
  else
    {
      // do this expolicitly since we might handle an exisiting object from an
      // earlier import that had it attribute set already
      pParameter->setConstant(true);
      // fill initial assignment set
      removeRule(pParameter->getId());
      if (modelValue.getInitialExpression() != "")
        {
          this->mInitialAssignmentVector.push_back(&modelValue);
        }
      else
        {
          removeInitialAssignment(pParameter->getId());
        }
    }
  CSBMLExporter::updateMIRIAMAnnotation(&modelValue, pParameter, this->mMetaIdMap);
}

/**
 * Creates the reactions for the model.
 */
void CSBMLExporter::createReactions(CCopasiDataModel& dataModel)
{
  // make sure the SBML Document already exists anf that it has a Model set
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL) return;
  CCopasiVectorNS<CReaction>::const_iterator it = dataModel.getModel()->getReactions().begin(), endit = dataModel.getModel()->getReactions().end();
  while (it != endit)
    {
      createReaction(**it, dataModel);
      ++it;
    }
}

/**
 * Creates the reaction for the given COPASI reaction.
 */
void CSBMLExporter::createReaction(CReaction& reaction, CCopasiDataModel& dataModel)
{
  // make sure the mCOPASI2SBMLMap is already updated
  Reaction* pSBMLReaction = NULL;
  // if the reaction has nothing set but the name, we don't do anything
  if (reaction.getChemEq().getSubstrates().size() == 0 &&
      reaction.getChemEq().getProducts().size() == 0) return;
  std::string sbmlId = reaction.getSBMLId();
  if (!sbmlId.empty())
    {
      pSBMLReaction = this->mpSBMLDocument->getModel()->getReaction(sbmlId);
      if (pSBMLReaction == NULL)
        {
          /* create a new reaction object */
          pSBMLReaction = this->mpSBMLDocument->getModel()->createReaction();
          mCOPASI2SBMLMap[&reaction] = pSBMLReaction;
          pSBMLReaction->setId(sbmlId);
        }
    }
  else
    {
      pSBMLReaction = this->mpSBMLDocument->getModel()->createReaction();
      this->mCOPASI2SBMLMap[&reaction] = pSBMLReaction;
      sbmlId = CSBMLExporter::createUniqueId(this->mIdMap, "reaction_");
      reaction.setSBMLId(sbmlId);
      pSBMLReaction->setId(sbmlId);
    }
  this->mIdMap.insert(std::make_pair(sbmlId, pSBMLReaction));
  this->mHandledSBMLObjects.insert(pSBMLReaction);
  pSBMLReaction->setName(reaction.getObjectName().c_str());
  pSBMLReaction->setReversible(reaction.isReversible());
  const CChemEq& chemicalEquation = reaction.getChemEq();
  /* Add all substrates */
  unsigned int counter;
  std::set<std::string> usedReferences;
  for (counter = 0; counter < chemicalEquation.getSubstrates().size(); counter++)
    {
      const CChemEqElement* element = chemicalEquation.getSubstrates()[counter];
      const CMetab* pMetabolite = element->getMetabolite();
      assert(pMetabolite);
      SpeciesReference* sRef = NULL;
      if (!(sRef = pSBMLReaction->getReactant(pMetabolite->getSBMLId())))
        {
          sRef = pSBMLReaction->createReactant();
          sRef->setSpecies(pMetabolite->getSBMLId().c_str());
        }
      sRef->setStoichiometry(element->getMultiplicity());
      sRef->setDenominator(1);
      usedReferences.insert(sRef->getSpecies());
    }
  ListOf* l = pSBMLReaction->getListOfReactants();
  for (counter = l->size(); counter > 0;--counter)
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
      const CChemEqElement* element = chemicalEquation.getProducts()[counter];
      const CMetab* pMetabolite = element->getMetabolite();
      assert(pMetabolite);
      SpeciesReference* sRef = NULL;
      if (!(sRef = pSBMLReaction->getProduct(pMetabolite->getSBMLId())))
        {
          sRef = pSBMLReaction->createProduct();
          sRef->setSpecies(pMetabolite->getSBMLId().c_str());
        }
      sRef->setStoichiometry(element->getMultiplicity());
      sRef->setDenominator(1);
      usedReferences.insert(sRef->getSpecies());
    }
  l = pSBMLReaction->getListOfProducts();
  for (counter = l->size(); counter > 0;--counter)
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
      const CChemEqElement* element = chemicalEquation.getModifiers()[counter];
      const CMetab* pMetabolite = element->getMetabolite(); assert(pMetabolite);
      ModifierSpeciesReference* sRef = NULL;
      if (!(sRef = pSBMLReaction->getModifier(pMetabolite->getSBMLId())))
        {
          sRef = pSBMLReaction->createModifier();
          sRef->setSpecies(pMetabolite->getSBMLId().c_str());
        }
      usedReferences.insert(sRef->getSpecies());
    }
  l = pSBMLReaction->getListOfModifiers();
  for (counter = l->size(); counter > 0;--counter)
    {
      if (usedReferences.find(static_cast<SimpleSpeciesReference*>(l->get(counter - 1))->getSpecies()) == usedReferences.end())
        {
          l->remove(counter - 1);
        }
    }
  /* create the kinetic law */
  /* if there is one on copasi */
  if ((reaction.getFunction()) != dataModel.mpUndefined)
    {
      KineticLaw* pKineticLaw = this->createKineticLaw(reaction, dataModel);
      if (pKineticLaw != NULL)
        {
          pSBMLReaction->setKineticLaw(pKineticLaw);
          delete pKineticLaw;
        }
      else
        {
          // create an error message and abort
          // maybe only abort if incomplete export is not wanted
          if (this->mIncompleteExport != true)
            {
              CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 8, reaction.getObjectName().c_str());
            }
          else
            {
              pSBMLReaction->unsetKineticLaw();
            }
        }
    }
  else
    {
      pSBMLReaction->unsetKineticLaw();
    }
  CSBMLExporter::updateMIRIAMAnnotation(&reaction, pSBMLReaction, this->mMetaIdMap);
}

/**
 * Creates the initial assignments for the model.
 */
void CSBMLExporter::createInitialAssignments(CCopasiDataModel& dataModel)
{
  // make sure the mInitialAssignmentVector has been filled already

  // create the initial assignments
  unsigned int i, iMax = this->mInitialAssignmentVector.size();
  const CModelEntity* pME = NULL;
  for (i = 0;i < iMax;++i)
    {
      pME = mInitialAssignmentVector[i];
      assert(pME != NULL);
      if (pME != NULL)
        {
          createInitialAssignment(*pME, dataModel);
        }
    }
}

/**
 * Creates the initial assignment for the given COPASI model entity.
 */
void CSBMLExporter::createInitialAssignment(const CModelEntity& modelEntity, CCopasiDataModel& dataModel)
{
  // check the expression
  std::vector<SBMLIncompatibility> result;
  std::string type = "initial expression for ";
  type += modelEntity.getObjectType();
  CSBMLExporter::isExpressionSBMLCompatible(*modelEntity.getInitialExpressionPtr(), dataModel, this->mSBMLLevel, this->mSBMLVersion, result, modelEntity.getObjectName(), type, true);
  // collect directly used functions
  if (result.empty())
    {
      std::set<std::string> directlyUsedFunctionNames;
      CSBMLExporter::findDirectlyUsedFunctions(modelEntity.getInitialExpressionPtr()->getRoot(), directlyUsedFunctionNames);
      std::set<CFunction*> usedFunctions = CSBMLExporter::createFunctionSetFromFunctionNames(directlyUsedFunctionNames, dataModel.getFunctionList());

#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
      {
        std::set<CFunction*>::const_iterator it = usedFunctions.begin();
        std::set<CFunction*>::const_iterator end = usedFunctions.end();

        for (; it != end; ++it)
          this->mUsedFunctions.insert(*it);
      }
#else
      this->mUsedFunctions.insert(usedFunctions.begin(), usedFunctions.end());
#endif

      // create the actual initial assignment
      InitialAssignment* pInitialAssignment = this->mpSBMLDocument->getModel()->getInitialAssignment(modelEntity.getSBMLId());
      if (pInitialAssignment == NULL)
        {
          pInitialAssignment = this->mpSBMLDocument->getModel()->createInitialAssignment();
          pInitialAssignment->setSymbol(modelEntity.getSBMLId());
        }
      // set the math
      this->mHandledSBMLObjects.insert(pInitialAssignment);
      const CEvaluationNode* pOrigNode = modelEntity.getInitialExpressionPtr()->getRoot();
      // the next few lines replace references to species depending on whether
      // it is a reference to an amount or a reference to a concentration.
      // Other factors that influence this replacement are if the model
      // contains variable volumes or if the quantity units are set to CModel::number
      pOrigNode = this->replaceSpeciesReferences(pOrigNode, dataModel);
      assert(pOrigNode != NULL);
      ASTNode* pNode = this->convertToASTNode(pOrigNode, dataModel);
      delete pOrigNode;
      if (pNode != NULL)
        {
          pInitialAssignment->setMath(pNode);
          delete pNode;
        }
      else
        {
          if (this->mIncompleteExport == true)
            {
              // remove the initial assignment from the SBML model
              unsigned int i = 0, iMax = this->mpSBMLDocument->getModel()->getNumInitialAssignments();
              while (i < iMax)
                {
                  if (this->mpSBMLDocument->getModel()->getInitialAssignment(i)->getSymbol() == modelEntity.getSBMLId())
                    {
                      this->mpSBMLDocument->getModel()->getListOfInitialAssignments()->remove(i);
                      break;
                    }
                  ++i;
                }
            }
          else
            {
              CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 60, "initial assignment", modelEntity.getObjectType().c_str(), modelEntity.getObjectName().c_str());
            }
        }
    }
  else
    {
      if (this->mIncompleteExport)
        {
          this->mIncompatibilities.insert(this->mIncompatibilities.end(), result.begin(), result.end());
        }
      else
        {
          CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 60, "initial assignment", modelEntity.getObjectType().c_str(), modelEntity.getObjectName().c_str());
        }
    }
}

/**
 * Creates the rules for the model.
 */
void CSBMLExporter::createRules(CCopasiDataModel& dataModel)
{
  // make sure the mAssignmentVector has been filled already
  // make sure the mODEVector has been filled already
  // order the rules for Level 1 export
  // rules in Level 2 are not ordered.
  //if (this->mSBMLLevel == 1 || (this->mSBMLLevel == 2 && this->mSBMLVersion == 1))
  //  {
  std::vector<CModelEntity*> orderedAssignmentRules = orderRules(dataModel);
  //}
  //
  // remove all rules from the SBML model
  // and put them in a map
  std::map<std::string, Rule*> ruleMap;
  Model* pSBMLModel = this->mpSBMLDocument->getModel();
  assert(pSBMLModel != NULL);
  while (pSBMLModel->getNumRules() != 0)
    {
      Rule* pRule = pSBMLModel->getRule(0);
      assert(pRule != NULL);
      // ignore algebraic rules
      if (pRule->getTypeCode() == SBML_ASSIGNMENT_RULE)
        {
          AssignmentRule* pARule = dynamic_cast<AssignmentRule*>(pRule);
          assert(pARule != NULL);
          ruleMap[pARule->getVariable()] = pARule;
        }
      else if (pRule->getTypeCode() == SBML_RATE_RULE)
        {
          RateRule* pRRule = dynamic_cast<RateRule*>(pRule);
          assert(pRRule != NULL);
          ruleMap[pRRule->getVariable()] = pRRule;
        }
      pSBMLModel->getListOfRules()->remove(0);
    }
  // create the rules
  const CModelEntity* pME = NULL;
  unsigned int i, iMax = orderedAssignmentRules.size();
  for (i = 0;i < iMax;++i)
    {
      pME = orderedAssignmentRules[i];
      assert(pME != NULL);
      if (pME != NULL)
        {
          std::map<std::string, Rule*>::const_iterator pos = ruleMap.find(pME->getSBMLId());
          Rule* pOldRule = NULL;
          if (pos != ruleMap.end())
            {
              pOldRule = pos->second;
              assert(pOldRule != NULL);
              ruleMap.erase(pos->first);
            }
          createRule(*pME, dataModel, pOldRule);
        }
    }
  iMax = mODEVector.size();
  for (i = 0;i < iMax;++i)
    {
      pME = mODEVector[i];
      assert(pME != NULL);
      if (pME != NULL)
        {
          std::map<std::string, Rule*>::const_iterator pos = ruleMap.find(pME->getSBMLId());
          Rule* pOldRule = NULL;
          if (pos != ruleMap.end())
            {
              pOldRule = pos->second;
              assert(pOldRule != NULL);
              ruleMap.erase(pos->first);
            }
          createRule(*pME, dataModel, pOldRule);
        }
    }
  // delete the remaining rules
  std::map<std::string, Rule*>::iterator mapIt = ruleMap.begin(), mapEndit = ruleMap.end();
  while (mapIt != mapEndit)
    {
      delete mapIt->second;
      ++mapIt;
    }
  ruleMap.clear();
}

/**
 * Creates the rule for the given COPASI model entity.
 */
void CSBMLExporter::createRule(const CModelEntity& modelEntity, CCopasiDataModel& dataModel, Rule* pOldRule)
{
  // check the expression
  std::vector<SBMLIncompatibility> result;
  std::string type = "rule for ";
  type += modelEntity.getObjectType();
  CSBMLExporter::isExpressionSBMLCompatible(*modelEntity.getExpressionPtr(), dataModel, this->mSBMLLevel, this->mSBMLVersion, result, modelEntity.getObjectName(), type);
  // collect directly used functions
  if (result.empty())
    {
      std::set<std::string> directlyUsedFunctionNames;
      CSBMLExporter::findDirectlyUsedFunctions(modelEntity.getExpressionPtr()->getRoot(), directlyUsedFunctionNames);
      std::set<CFunction*> usedFunctions = CSBMLExporter::createFunctionSetFromFunctionNames(directlyUsedFunctionNames, dataModel.getFunctionList());

# if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
      {
        std::set<CFunction*>::const_iterator it = usedFunctions.begin();
        std::set<CFunction*>::const_iterator end = usedFunctions.end();

        for (; it != end; ++it)
          this->mUsedFunctions.insert(*it);
      }
#else
      this->mUsedFunctions.insert(usedFunctions.begin(), usedFunctions.end());
#endif

      // create the actual rule
      //Rule* pRule = this->mpSBMLDocument->getModel()->getRule(modelEntity.getSBMLId());
      if (pOldRule == NULL)
        {
          if (modelEntity.getStatus() == CModelEntity::ASSIGNMENT)
            {
              pOldRule = this->mpSBMLDocument->getModel()->createAssignmentRule();
            }
          else
            {
              const CMetab* pMetab = dynamic_cast<const CMetab*>(&modelEntity);
              if (pMetab != NULL)
                {
                  // check if the compartment is fixed
                  if (pMetab->getCompartment()->getStatus() != CModelEntity::FIXED)
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 52, pMetab->getObjectName().c_str());
                    }
                }
              pOldRule = this->mpSBMLDocument->getModel()->createRateRule();
            }
          pOldRule->setVariable(modelEntity.getSBMLId());
        }
      else
        {
          // readd the rule to the model
          this->mpSBMLDocument->getModel()->getListOfRules()->appendAndOwn(pOldRule);
        }
      // set the math
      const CEvaluationNode* pOrigNode = modelEntity.getExpressionPtr()->getRoot();
      // the next few lines replace references to species depending on whether
      // it is a reference to an amount or a reference to a concentration.
      // Other factors that influence this replacement are if the model
      // contains variable volumes or if the quantity units are set to CModel::number
      pOrigNode = this->replaceSpeciesReferences(pOrigNode, dataModel);
      assert(pOrigNode != NULL);
      ASTNode* pNode = this->convertToASTNode(pOrigNode, dataModel);
      delete pOrigNode;
      if (pNode != NULL)
        {
          pOldRule->setMath(pNode);
          delete pNode;
        }
      else
        {
          if (this->mIncompleteExport == true)
            {
              // remove the rule from the SBML model
              /* This is no longer necessary since we already remove all rules
               * prior to calling createRules.
              unsigned int i = 0, iMax = this->mpSBMLDocument->getModel()->getNumRules();
              while (i < iMax)
                {
                  if (this->mpSBMLDocument->getModel()->getRule(i)->getVariable() == modelEntity.getSBMLId())
                    {
                      this->mpSBMLDocument->getModel()->getListOfRules()->remove(i);
                      break;
                    }
                  ++i;
                }
               */
            }
          else
            {
              CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 60, "rule", modelEntity.getObjectType().c_str(), modelEntity.getObjectName().c_str());
            }
        }
    }
  else
    {
      if (this->mIncompleteExport)
        {
          this->mIncompatibilities.insert(this->mIncompatibilities.end(), result.begin(), result.end());
        }
      else
        {
          CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 60, "rule", modelEntity.getObjectType().c_str(), modelEntity.getObjectName().c_str());
        }
    }
}

const std::map<std::string, const SBase*> CSBMLExporter::createIdMap(const Model& sbmlModel)
{
  // go through all function definitions, compartments, species, reactions,
  // parameters and events and create a set with all used ids.
  std::map<std::string, const SBase*> idMap;
  unsigned int i, iMax;
  if (sbmlModel.isSetId())
    {
      idMap.insert(std::make_pair(sbmlModel.getId(), &sbmlModel));
    }
  if (sbmlModel.getListOfFunctionDefinitions()->isSetId())
    {
      idMap.insert(std::make_pair(sbmlModel.getListOfFunctionDefinitions()->getId(), sbmlModel.getListOfFunctionDefinitions()));
    }
  iMax = sbmlModel.getNumFunctionDefinitions();
  for (i = 0; i < iMax;++i)
    {
      idMap.insert(std::make_pair(sbmlModel.getFunctionDefinition(i)->getId(), sbmlModel.getFunctionDefinition(i)));
    }
  if (sbmlModel.getListOfCompartments()->isSetId())
    {
      idMap.insert(std::make_pair(sbmlModel.getListOfCompartments()->getId(), sbmlModel.getListOfCompartments()));
    }
  iMax = sbmlModel.getNumCompartments();
  for (i = 0; i < iMax;++i)
    {
      idMap.insert(std::make_pair(sbmlModel.getCompartment(i)->getId(), sbmlModel.getCompartment(i)));
    }
  if (sbmlModel.getListOfSpecies()->isSetId())
    {
      idMap.insert(std::make_pair(sbmlModel.getListOfSpecies()->getId(), sbmlModel.getListOfSpecies()));
    }
  iMax = sbmlModel.getNumSpecies();
  for (i = 0; i < iMax;++i)
    {
      idMap.insert(std::make_pair(sbmlModel.getSpecies(i)->getId(), sbmlModel.getSpecies(i)));
    }
  if (sbmlModel.getListOfParameters()->isSetId())
    {
      idMap.insert(std::make_pair(sbmlModel.getListOfParameters()->getId(), sbmlModel.getListOfParameters()));
    }
  iMax = sbmlModel.getNumParameters();
  for (i = 0; i < iMax;++i)
    {
      idMap.insert(std::make_pair(sbmlModel.getParameter(i)->getId(), sbmlModel.getParameter(i)));
    }
  if (sbmlModel.getListOfReactions()->isSetId())
    {
      idMap.insert(std::make_pair(sbmlModel.getListOfReactions()->getId(), sbmlModel.getListOfReactions()));
    }
  iMax = sbmlModel.getNumReactions();
  for (i = 0; i < iMax;++i)
    {
      const Reaction* pReaction = sbmlModel.getReaction(i);
      if (pReaction != NULL)
        {
          idMap.insert(std::make_pair(pReaction->getId(), pReaction));
          if (pReaction->getListOfReactants()->isSetId())
            {
              idMap.insert(std::make_pair(pReaction->getListOfReactants()->getId(), pReaction->getListOfReactants()));
            }
          unsigned int j, jMax = pReaction->getNumReactants();
          const SpeciesReference* pSRef = NULL;
          for (j = 0;j < jMax;++j)
            {
              pSRef = pReaction->getReactant(j);
              if (pSRef->isSetId())
                {
                  idMap.insert(std::make_pair(pSRef->getId(), pSRef));
                }
            }
          if (pReaction->getListOfProducts()->isSetId())
            {
              idMap.insert(std::make_pair(pReaction->getListOfProducts()->getId(), pReaction->getListOfProducts()));
            }
          jMax = pReaction->getNumProducts();
          for (j = 0;j < jMax;++j)
            {
              pSRef = pReaction->getProduct(j);
              if (pSRef->isSetId())
                {
                  idMap.insert(std::make_pair(pSRef->getId(), pSRef));
                }
            }
          if (pReaction->getListOfModifiers()->isSetId())
            {
              idMap.insert(std::make_pair(pReaction->getListOfModifiers()->getId(), pReaction->getListOfModifiers()));
            }
          jMax = pReaction->getNumModifiers();
          const ModifierSpeciesReference* pModSRef;
          for (j = 0;j < jMax;++j)
            {
              pModSRef = pReaction->getModifier(j);
              if (pModSRef->isSetId())
                {
                  idMap.insert(std::make_pair(pModSRef->getId(), pModSRef));
                }
            }
        }
    }
  if (sbmlModel.getListOfEvents()->isSetId())
    {
      idMap.insert(std::make_pair(sbmlModel.getListOfEvents()->getId(), sbmlModel.getListOfEvents()));
    }
  iMax = sbmlModel.getNumEvents();
  for (i = 0; i < iMax;++i)
    {
      idMap.insert(std::make_pair(sbmlModel.getEvent(i)->getId(), sbmlModel.getEvent(i)));
    }
  // if COPASI is compiled with layout, we have to add those ids as well
#ifdef WITH_LAYOUT
  if (sbmlModel.getListOfLayouts()->isSetId())
    {
      idMap.insert(std::make_pair(sbmlModel.getListOfLayouts()->getId(), sbmlModel.getListOfLayouts()));
    }
  iMax = sbmlModel.getListOfLayouts()->size();
  for (i = 0;i < iMax;++i)
    {
      const Layout* pLayout = sbmlModel.getLayout(i);
      if (pLayout != NULL)
        {
          if (pLayout->isSetId())
            {
              idMap.insert(std::make_pair(pLayout->getId(), pLayout));
            }
        }
    }
#endif // WITH_LAYOUT
  return idMap;
}

/**
 * Create a unique id for an SBML object.
 * I can't just take the Copasi key of the object since this might conflict
 * with an already existing sbml id which came from the sbmlid attribute in a
 * copasi file or directly by importing an SBML file.
 */
const std::string CSBMLExporter::createUniqueId(const std::map<std::string, const SBase*>& idMap, const std::string& prefix)
{
  unsigned int i = 1;
  std::ostringstream numberStream;
  numberStream << prefix << i;
  while (idMap.find(numberStream.str()) != idMap.end())
    {
      ++i;
      numberStream.str("");
      numberStream << prefix << i;
    }
  return numberStream.str();
}

/**
 * Checks all assignments (initial and transient) for references to objects
 * that can not be exported to SBML.
 */
void CSBMLExporter::checkForUnsupportedObjectReferences(const CCopasiDataModel& dataModel, unsigned int sbmlLevel, unsigned int sbmlVersion, std::vector<SBMLIncompatibility>& result)
{
  // check all metabolites,parameters and compartments
  const CModel* pModel = dataModel.getModel();
  assert(pModel);
  if (pModel == NULL) return;
  unsigned int i, iMax = this->mAssignmentVector.size();
  const CModelEntity* pME;
  for (i = 0;i < iMax;++i)
    {
      pME = this->mAssignmentVector[i];
      assert(pME != NULL);
      if (pME != NULL)
        {
          checkForUnsupportedObjectReferences(*pME->getExpressionPtr(), dataModel, sbmlLevel, sbmlVersion, result);
        }
    }
  // check ode rules
  iMax = this->mODEVector.size();
  for (i = 0;i < iMax;++i)
    {
      pME = this->mODEVector[i];
      assert(pME != NULL);
      if (pME != NULL)
        {
          checkForUnsupportedObjectReferences(*pME->getExpressionPtr(), dataModel, sbmlLevel, sbmlVersion, result);
        }
    }
  // check initial assignments
  iMax = this->mInitialAssignmentVector.size();
  for (i = 0;i < iMax;++i)
    {
      pME = this->mInitialAssignmentVector[i];
      assert(pME != NULL);
      if (pME != NULL)
        {
          checkForUnsupportedObjectReferences(*pME->getInitialExpressionPtr(), dataModel, sbmlLevel, sbmlVersion, result);
        }
    }
}

void CSBMLExporter::checkForUnsupportedObjectReferences(const CEvaluationTree& expr, const CCopasiDataModel& dataModel, unsigned int sbmlLevel, unsigned int sbmlVersion, std::vector<SBMLIncompatibility>& result, bool initialExpression)
{
  // SBML Level 1 and Level 2 Version 1 can have references to transient values of
  // compartments, metabolites and global parameters as well as time (model)

  // SBML Level 2 Version 2 and above can have the same references as level 1 plus references to
  // reaction fluxes.
  const std::vector<CEvaluationNode*>& objectNodes = expr.getNodeList();
  unsigned j, jMax = objectNodes.size();
  for (j = 0;j < jMax;++j)
    {
      if (CEvaluationNode::type(objectNodes[j]->getType()) == CEvaluationNode::OBJECT)
        {
          const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(objectNodes[j]);
          assert(pObjectNode);
          if (pObjectNode == NULL) continue;
          std::vector<CCopasiContainer*> containers;
          containers.push_back(const_cast<CModel*>(dataModel.getModel()));
          const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(containers, pObjectNode->getObjectCN());
          assert(pObject);
          if (pObject->isReference())
            {
              const CCopasiObject* pObjectParent = pObject->getObjectParent();
              assert(pObjectParent);
              std::string typeString = pObjectParent->getObjectType();
              if (typeString == "Compartment")
                {
                  // must be a reference to the (transient) or initial volume
                  if (initialExpression == true)
                    {
                      if (pObject->getObjectName() != "InitialVolume")
                        {
                          result.push_back(SBMLIncompatibility(1, pObject->getObjectName().c_str(), "compartment", pObjectParent->getObjectName().c_str()));
                        }
                    }
                  else
                    {
                      if (pObject->getObjectName() != "Volume")
                        {
                          result.push_back(SBMLIncompatibility(1, pObject->getObjectName().c_str(), "compartment", pObjectParent->getObjectName().c_str()));
                        }
                    }
                }
              else if (typeString == "Metabolite")
                {
                  // must be a reference to the transient or initial concentration
                  if (initialExpression == true)
                    {
                      if (pObject->getObjectName() != "InitialConcentration" && pObject->getObjectName() != "InitialParticleNumber")
                        {
                          result.push_back(SBMLIncompatibility(1, pObject->getObjectName().c_str(), "metabolite", pObjectParent->getObjectName().c_str()));
                        }
                    }
                  else
                    {
                      if (pObject->getObjectName() != "Concentration" && pObject->getObjectName() != "ParticleNumber")
                        {
                          result.push_back(SBMLIncompatibility(1, pObject->getObjectName().c_str(), "metabolite", pObjectParent->getObjectName().c_str()));
                        }
                    }
                }
              else if (typeString == "ModelValue")
                {
                  // must be a reference to the transient or initial value
                  if (initialExpression == true)
                    {
                      if (pObject->getObjectName() != "InitialValue")
                        {
                          result.push_back(SBMLIncompatibility(1, pObject->getObjectName().c_str(), "parameter", pObjectParent->getObjectName().c_str()));
                        }
                    }
                  else
                    {
                      if (pObject->getObjectName() != "Value")
                        {
                          result.push_back(SBMLIncompatibility(1, pObject->getObjectName().c_str(), "parameter", pObjectParent->getObjectName().c_str()));
                        }
                    }
                }
              else if (typeString == "Model")
                {
                  // must be a reference to the model time
                  if (pObject->getObjectName() != "Time")
                    {
                      result.push_back(SBMLIncompatibility(1, pObject->getObjectName().c_str(), "model", pObjectParent->getObjectName().c_str()));
                    }
                }
              else
                {
                  if (sbmlLevel == 1 || (sbmlLevel == 2 && sbmlVersion == 1))
                    {
                      if (typeString == "Reaction")
                        {
                          if (pObject->getObjectName() != "Flux")
                            {
                              result.push_back(SBMLIncompatibility(1, pObject->getObjectName().c_str(), "reaction", pObjectParent->getObjectName().c_str()));
                            }
                        }
                    }
                  else
                    {
                      result.push_back(SBMLIncompatibility(1, pObject->getObjectName().c_str(), typeString.c_str(), pObjectParent->getObjectName().c_str()));
                    }
                }
            }
          else
            {
              result.push_back(SBMLIncompatibility(1, "value", pObject->getObjectType().c_str() , pObject->getObjectName().c_str()));
            }
        }
    }
}

/**
 * Checks whether the given data model can be exported to SBML Level1
 * If it can be exported, the result vector will be empty, otherwise it will
 * contain a number of messages that specify why it can't be exported.
 */
void CSBMLExporter::isModelSBMLL1Compatible(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result)
{
  // check for piecewise functions
  checkForPiecewiseFunctions(dataModel, result);

  // check for initial assignments
  checkForInitialAssignments(dataModel, result);

  // check for event
  checkForEvents(dataModel, result);
}

/**
 * Checks whether the given data model can be exported to SBML Level2 Version1.
 * If it can be exported, the result vector will be empty, otherwise it will
 * contain a number of messages that specify why it can't be exported.
 */
void CSBMLExporter::isModelSBMLL2V1Compatible(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result)
{
  // check for initial assignments
  CSBMLExporter::checkForInitialAssignments(dataModel, result);
}

/**
 * Checks whether the given data model can be exported to SBML Level2 Version3.
 * If it can be exported, the result vector will be empty, otherwise it will
 * contain a number of messages that specify why it can't be exported.
 */
void CSBMLExporter::isModelSBMLL2V3Compatible(const CCopasiDataModel& /*dataModel*/, std::vector<SBMLIncompatibility>& /*result*/)
{
  // there are no special checks for the Level and Version yet
}

/**
 * Checks whether the model contains a metabolite that is defined by an ODE
 * expression and that is located in a variable volume. Since COPASI
 * interprets the expression differntly from SBML, we can not correctly
 * export this yet. See Bug 903.
 */
void CSBMLExporter::checkForODESpeciesInNonfixedCompartment(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility> result)
{
  const CModel* pModel = dataModel.getModel();
  const CCopasiVector<CMetab>& metabolites = pModel->getMetabolites();
  CCopasiVector<CMetab>::const_iterator it = metabolites.begin(), endit = metabolites.end();
  while (it != endit)
    {
      if ((*it)->getStatus() == CModelValue::ODE)
        {
          const CCompartment* pCompartment = (*it)->getCompartment();
          assert(pCompartment != NULL);
          if (pCompartment->getStatus() != CModelValue::FIXED)
            {
              result.push_back(SBMLIncompatibility(3, (*it)->getObjectName().c_str(), pCompartment->getObjectName().c_str()));
            }
        }
      ++it;
    }
}

/**
 * Checks whether the rule in the given model entity can be exported to
 * the specified version of SBML.
 * If it can be exported, the result vector will be empty, otherwise it will
 * contain a number of messages that specify why it can't be exported.
 */
void CSBMLExporter::isExpressionSBMLCompatible(const CEvaluationTree& expr, const CCopasiDataModel& dataModel, int sbmlLevel, int sbmlVersion, std::vector<SBMLIncompatibility>& result,
    const std::string& objectName, const std::string& objectType, bool initialExpression)
{
  checkForUnsupportedObjectReferences(expr, dataModel, sbmlLevel, sbmlVersion, result, initialExpression);
  std::set<CEvaluationNodeFunction::SubType> unsupportedFunctionTypes = CSBMLExporter::createUnsupportedFunctionTypeSet(sbmlLevel);
  checkForUnsupportedFunctionCalls(*expr.getRoot(), unsupportedFunctionTypes, result, objectName, objectType);
}

/**
 * This static methods checks, whether the model uses any function calls
 * that can not be expressed in SBML like the random distribution
 * functions.
 */
void CSBMLExporter::checkForUnsupportedFunctionCalls(const CCopasiDataModel& dataModel,
    unsigned int sbmlLevel, unsigned int /*sbmlVersion*/, std::vector<SBMLIncompatibility>& result)
{
  // Fill the set of unsupported functions depending on the level and
  // version
  std::set<CEvaluationNodeFunction::SubType> unsupportedFunctionTypes = CSBMLExporter::createUnsupportedFunctionTypeSet(sbmlLevel);
  // check all metabolites,parameters and compartments
  // make sure the list of assignments and initial assignments is filled
  // before this function is called
  const CModel* pModel = dataModel.getModel();
  assert(pModel);
  unsigned int i, iMax = mAssignmentVector.size();
  const CModelEntity* pME = NULL;
  for (i = 0;i < iMax;++i)
    {
      pME = mAssignmentVector[i];
      assert(pME != NULL);
      if (pME != NULL)
        {
          checkForUnsupportedFunctionCalls(*pME->getExpressionPtr()->getRoot(), unsupportedFunctionTypes, result, pME->getObjectName(), pME->getObjectType());
        }
    }
  // check ode rules
  iMax = mODEVector.size();
  for (i = 0;i < iMax;++i)
    {
      pME = mODEVector[i];
      assert(pME != NULL);
      if (pME != NULL)
        {
          checkForUnsupportedFunctionCalls(*pME->getExpressionPtr()->getRoot(), unsupportedFunctionTypes, result, pME->getObjectName(), pME->getObjectType());
        }
    }
  // check initial assignments
  iMax = mInitialAssignmentVector.size();
  for (i = 0;i < iMax;++i)
    {
      pME = mInitialAssignmentVector[i];
      assert(pME != NULL);
      if (pME != NULL)
        {
          checkForUnsupportedFunctionCalls(*pME->getInitialExpressionPtr()->getRoot(), unsupportedFunctionTypes, result, pME->getObjectName(), pME->getObjectType());
        }
    }
  // if we already have a list of used functions, we can go through this here
  // make sure the list of used function has been filled before this is
  // called
  iMax = mUsedFunctions.size();
  std::set<CFunction*>::iterator it = this->mUsedFunctions.begin(), endit = this->mUsedFunctions.end();
  while (it != endit)
    {
      assert(*it != NULL);
      if (*it != NULL)
        {
          checkForUnsupportedFunctionCalls(*(*it)->getRoot(), unsupportedFunctionTypes, result, (*it)->getObjectName(), "function");
        }
      ++it;
    }
}

/**
 * This static methods checks recursively, whether the given CEvaluationNode constains any function calls
 * that can not be expressed in SBML like the random distribution
 * functions.
 */
void CSBMLExporter::checkForUnsupportedFunctionCalls(const CEvaluationNode& node,
    const std::set<CEvaluationNodeFunction::SubType>& unsupportedFunctions,
    std::vector<SBMLIncompatibility>& result, const std::string& objectName, const std::string& objectType)
{
  if (CEvaluationNode::type(node.getType()) == CEvaluationNode::FUNCTION)
    {
      CEvaluationNodeFunction::SubType subtype = (CEvaluationNodeFunction::SubType)CEvaluationNode::subType(node.getType());
      if (unsupportedFunctions.find(subtype) != unsupportedFunctions.end())
        {
          result.push_back(SBMLIncompatibility(2, node.getData().c_str(), objectType.c_str(), objectName.c_str()));
        }
    }
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(node.getChild());
  while (pChild != NULL)
    {
      checkForUnsupportedFunctionCalls(*pChild, unsupportedFunctions, result, objectType, objectName);
      pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
    }
}

/**
 * This method checks whether the given model contains any initial assignments.
 */
void CSBMLExporter::checkForInitialAssignments(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result)
{
  const CModel* pModel = dataModel.getModel();
  if (pModel != NULL)
    {
      // check for rules
      const CCopasiVectorNS<CCompartment>& compartments = pModel->getCompartments();
      CCopasiVectorNS<CCompartment>::const_iterator compIt = compartments.begin(), compEndit = compartments.end();
      while (compIt != compEndit)
        {
          if ((*compIt)->getInitialExpression() != "")
            {
              result.push_back(SBMLIncompatibility(5, "Compartment", (*compIt)->getObjectName().c_str()));
            }
          ++compIt;
        }

      const CCopasiVector<CMetab>& metabs = pModel->getMetabolites();
      CCopasiVector<CMetab>::const_iterator metabIt = metabs.begin(), metabEndit = metabs.end();
      while (metabIt != metabEndit)
        {
          if ((*metabIt)->getInitialExpression() != "")
            {
              result.push_back(SBMLIncompatibility(5, "Metabolite", (*metabIt)->getObjectName().c_str()));
            }
          ++metabIt;
        }

      const CCopasiVectorN<CModelValue>& parameters = pModel->getModelValues();
      CCopasiVectorN<CModelValue>::const_iterator mvIt = parameters.begin(), mvEndit = parameters.end();
      while (mvIt != mvEndit)
        {
          if ((*mvIt)->getInitialExpression() != "")
            {
              result.push_back(SBMLIncompatibility(5, "Parameter", (*mvIt)->getObjectName().c_str()));
            }
          ++mvIt;
        }
    }
}

/**
 * Create all function definitions.
 */
void CSBMLExporter::createFunctionDefinitions(CCopasiDataModel& dataModel)
{
  // make sure the list of used functions is filled before this is
  // called
  // make sure the mCOPASI2SBMLMap is up to date

  // find all indirectly called functions
  std::vector<CFunction*> usedFunctions = findUsedFunctions(this->mUsedFunctions, dataModel.getFunctionList());
  this->mUsedFunctions.clear();
  this->mUsedFunctions.insert(usedFunctions.begin(), usedFunctions.end());

  // remove the function calls that have been created by copasi solely for use
  // as a kinetic law term if it is no longer needed
  Model* pModel = this->mpSBMLDocument->getModel();
  assert(pModel);
  if (pModel == NULL) fatalError();
  std::map<SBase*, const CCopasiObject*> sbml2copasiMap;
  std::map<const CCopasiObject*, SBase*>::iterator mapIt = this->mCOPASI2SBMLMap.begin();
  std::map<const CCopasiObject*, SBase*>::iterator mapEndit = this->mCOPASI2SBMLMap.end();
  while (mapIt != mapEndit)
    {
      sbml2copasiMap.insert(std::make_pair(mapIt->second, mapIt->first));
      ++mapIt;
    }
  std::set<CFunction*> unusedFunctions;
  unsigned int i = 0, iMax = pModel->getNumFunctionDefinitions();
  std::map<SBase*, const CCopasiObject*>::iterator mapPos;
  std::set<std::string> toRemove;
  while (i < iMax)
    {
      FunctionDefinition* pFunDef = pModel->getFunctionDefinition(i);
      if (pFunDef != NULL)
        {
          mapPos = sbml2copasiMap.find(pFunDef);
          if (mapPos != sbml2copasiMap.end())
            {
              CFunction* pFun = dynamic_cast<CFunction*>(const_cast<CCopasiObject*>(mapPos->second));
              if (pFun != NULL && this->mUsedFunctions.find(pFun) == this->mUsedFunctions.end())
                {
                  // the function exists in the model, but it is not used in any
                  // expression
                  if (pFun->getObjectName().find("function_4_") == 0)
                    {
                      // store the function definition that is to be removed
                      toRemove.insert(pFunDef->getId());
                    }
                  else
                    {
                      // those need to be stored in a separate list since we also
                      // need to find indirectly called functions
                      unusedFunctions.insert(pFun);
                    }
                }
            }
        }
      ++i;
    }
  // find all indirectly called functions for the unused functions
  std::vector<CFunction*> functionsVect = findUsedFunctions(unusedFunctions, dataModel.getFunctionList());
  usedFunctions.insert(usedFunctions.end(), functionsVect.begin(), functionsVect.end());
  // reset the used functions set
  this->mUsedFunctions.clear();
  this->mUsedFunctions.insert(usedFunctions.begin(), usedFunctions.end());

  // now we remove the function definitions from the SBML model
  std::set<std::string>::iterator toRemoveIt = toRemove.begin();
  std::set<std::string>::iterator toRemoveEndit = toRemove.end();
  while (toRemoveIt != toRemoveEndit)
    {
      FunctionDefinition* pFunDef = pModel->getFunctionDefinition(*toRemoveIt);
      if (pFunDef != NULL)
        {
          mapPos = sbml2copasiMap.find(pFunDef);
          if (mapPos != sbml2copasiMap.end() &&
              this->mUsedFunctions.find(dynamic_cast<CFunction*>(const_cast<CCopasiObject*>(mapPos->second))) == this->mUsedFunctions.end())
            {
              pModel->getListOfFunctionDefinitions()->remove(*toRemoveIt);
            }
        }
      ++toRemoveIt;
    }

  // order the remaining function definitions
  // remove duplicates from the vector, always keep the last one
  std::vector<CFunction*>::reverse_iterator reverseIt = usedFunctions.rbegin(), reverseEndit = usedFunctions.rend();
  functionsVect.clear();
  while (reverseIt != reverseEndit)
    {
      if (std::find(functionsVect.begin(), functionsVect.end(), *reverseIt) == functionsVect.end())
        {
          functionsVect.insert(functionsVect.begin(), *reverseIt);
        }
      ++reverseIt;
    }

  // remove all existing function definitions from the list
  while (pModel->getNumFunctionDefinitions() != 0)
    {
      pModel->getListOfFunctionDefinitions()->remove(0);
    }

  std::vector<CFunction*>::iterator it = functionsVect.begin(), endit = functionsVect.end();
  while (it != endit)
    {
      if (*it != NULL)
        {
          createFunctionDefinition(**it, dataModel);
        }
      ++it;
    }
}

/**
 * Create the SBML function definition from the given COPASI function.
 */
void CSBMLExporter::createFunctionDefinition(CFunction& function, CCopasiDataModel& dataModel)
{
  // check the expression
  std::map<const CCopasiObject*, SBase*>::iterator pos = this->mCOPASI2SBMLMap.find(&function);
  FunctionDefinition* pFunDef = NULL;
  if (pos != this->mCOPASI2SBMLMap.end())
    {
      pFunDef = dynamic_cast<FunctionDefinition*>(pos->second);
      assert(pFunDef);
    }
  else
    {
      pFunDef = this->mpSBMLDocument->getModel()->createFunctionDefinition();
      pFunDef->setName(function.getObjectName());
      std::string id = function.getSBMLId();
      if (id.empty())
        {
          id = function.getObjectName();
          if (CSBMLExporter::isValidSId(id))
            {
              if (this->mIdMap.find(id) != this->mIdMap.end())
                {
                  id = CSBMLExporter::createUniqueId(this->mIdMap, id + "_");
                }
            }
          else
            {
              id = CSBMLExporter::createUniqueId(this->mIdMap, "function_");
            }
        }
      this->mIdMap.insert(std::make_pair(id, pFunDef));
      pFunDef->setId(id);
      function.setSBMLId(id);
      this->mCOPASI2SBMLMap[&function] = pFunDef;
    }
  if (function.getRoot() == NULL)
    {
      std::string errorMessage = std::string("Can not export function");
      errorMessage += function.getObjectName();
      errorMessage += std::string(". Function does not have a valid root node.");
      CCopasiMessage(CCopasiMessage::EXCEPTION, errorMessage.c_str());
    }
  else
    {
      std::vector<SBMLIncompatibility> result;
      CSBMLExporter::isExpressionSBMLCompatible(function, dataModel, this->mSBMLLevel, this->mSBMLVersion, result, function.getObjectName(), "function");
      if (result.empty())
        {
          ASTNode* pFunNode = this->convertToASTNode(function.getRoot(), dataModel);
          // go through the AST tree and replace all function call nodes with with a call to the sbml id
          ASTNode* pLambda = new ASTNode(AST_LAMBDA);
          // add the parameters to the function definition
          const CFunctionParameters& funParams = function.getVariables();
          unsigned int i, iMax = funParams.size();
          ASTNode* pParamNode = NULL;
          for (i = 0; i < iMax;++i)
            {
              pParamNode = new ASTNode(AST_NAME);
              pParamNode->setName(funParams[i]->getObjectName().c_str());
              pLambda->addChild(pParamNode);
            }
          pLambda->addChild(pFunNode);
          pFunDef->setMath(pLambda);
        }
      else
        {
          this->mIncompatibilities.insert(this->mIncompatibilities.end(), result.begin(), result.end());
          CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 28, function.getObjectName().c_str());
        }
    }
  CSBMLExporter::updateMIRIAMAnnotation(&function, pFunDef, this->mMetaIdMap);
}

/**
 * Export the model to SBML.
 * The SBML model is returned as a string. In case of an error, an
 * empty string is returned.
 */
const std::string CSBMLExporter::exportModelToString(CCopasiDataModel& dataModel, unsigned int sbmlLevel, unsigned int sbmlVersion)
{
  this->mSBMLLevel = sbmlLevel;
  this->mSBMLVersion = sbmlVersion;
  mHandledSBMLObjects.clear();
  createSBMLDocument(dataModel);
  // export the model to a string
  if (this->mpSBMLDocument == NULL) return std::string();
  removeUnusedObjects();
  SBMLWriter* writer = new SBMLWriter();

  writer->setProgramName("COPASI");
  writer->setProgramVersion(dataModel.getVersion()->getVersion().c_str());

  char* d = writer->writeToString(this->mpSBMLDocument);
  std::string returnValue = d;
  if (d) free(d);
  pdelete(writer);
  return returnValue;
}

void CSBMLExporter::createSBMLDocument(CCopasiDataModel& dataModel)
{
  const SBMLDocument* pOldSBMLDocument = dataModel.getCurrentSBMLDocument();
  if (pOldSBMLDocument == NULL)
    {
      this->mpSBMLDocument = new SBMLDocument();
    }
  else
    {
      this->mpSBMLDocument = dynamic_cast<SBMLDocument*>(pOldSBMLDocument->clone());
    }
  if (this->mpSBMLDocument == NULL) fatalError();
  // update the copasi2sbmlmap
  updateCOPASI2SBMLMap(dataModel);
  if (this->mpSBMLDocument->getModel() == NULL)
    {
      std::string id = CSBMLExporter::createUniqueId(this->mIdMap, "Model_");
      this->mpSBMLDocument->createModel(id);
      this->mIdMap.insert(std::make_pair(id, this->mpSBMLDocument->getModel()));
    }
  else
    {
      CSBMLExporter::collectIds(this->mpSBMLDocument->getModel(), this->mIdMap, this->mMetaIdMap);
    }
  // update the comments on the model
  const CModel* pModel = dataModel.getModel();
  assert(pModel != NULL);
  this->mpSBMLDocument->getModel()->setName(pModel->getObjectName());
  if (pModel != NULL && (!pModel->getComments().empty()) && !(pModel->getComments().find_first_not_of(" \n\t\r") == std::string::npos))
    {
      std::string comments = "<notes>" + pModel->getComments() + "</notes>";
      XMLNode* pNotes = XMLNode::convertStringToXMLNode(comments);
      if (pNotes != NULL)
        {
          this->mpSBMLDocument->getModel()->setNotes(pNotes);
          delete pNotes;
        }
    }
  // update the MIRIAM annotation on the model
  CSBMLExporter::updateMIRIAMAnnotation(pModel, this->mpSBMLDocument->getModel(), this->mMetaIdMap);

  // create units, compartments, species, parameters, reactions, initial
  // assignment, assignments, (event) and function definitions
  createUnits(dataModel);
  // try to find a parameter that represents avogadros number
  findAvogadro(dataModel);

  createCompartments(dataModel);
  createMetabolites(dataModel);
  createParameters(dataModel);

  // TODO here we should check the expressions but the function definitions
  // TODO have not been created yet, so we can't
  // TODO Maybe we don't have to do all checks here.
  // TODO it would probably be enough to check if the expressions are valid and
  // TODO to check the function calls later on when the functions are created.

  // only export initial assignments for Level 2 Version 2 and above
  if (this->mSBMLLevel != 1 && !(this->mSBMLLevel == 2 && this->mSBMLVersion == 1))
    {
      createInitialAssignments(dataModel);
    }
  else
    {
      checkForInitialAssignments(dataModel, this->mIncompatibilities);
    }
  createRules(dataModel);
  createReactions(dataModel);
  createEvents(dataModel);
  // find all used functions
  if (this->mSBMLLevel != 1)
    {
      createFunctionDefinitions(dataModel);
    }
  else
    {
      // do sbml Level1 Voodoo
      // e.g. replace some of the unsupported nodes with workarounds
      convertToLevel1();
    }
  this->mpSBMLDocument->setLevelAndVersion(this->mSBMLLevel, this->mSBMLVersion);
  // remove mpAvogadro from the model again
  if (this->mAvogadroCreated == true)
    {
      std::map<const CCopasiObject*, SBase*>::iterator pos = this->mCOPASI2SBMLMap.find(this->mpAvogadro);
      this->mCOPASI2SBMLMap.erase(pos);
      dataModel.getModel()->removeModelValue(this->mpAvogadro->getKey(), true);
    }
  unsigned int i, iMax = this->mIncompatibilities.size();
  for (i = 0;i < iMax;++i)
    {
      SBMLIncompatibility& incompat = this->mIncompatibilities[i];
      std::ostringstream os;
      os << incompat.getMessage() << "\n";
      os << incompat.getDetails() << "\n";
      if (incompat.minSBMLLevel() != 0 && incompat.minSBMLVersion() != 0)
        {
          os << "Please export to SBML Level " << incompat.minSBMLLevel();
          os << " Version " << incompat.minSBMLVersion() << " or higher.";
        }
      CCopasiMessage::CCopasiMessage(CCopasiMessage::RAW, os.str().c_str());
    }
  if (iMax > 0) CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, "Model incompatible with chosen version and/or level of SBML.");
}

const std::set<CEvaluationNodeFunction::SubType> CSBMLExporter::createUnsupportedFunctionTypeSet(unsigned int sbmlLevel)
{
  std::set<CEvaluationNodeFunction::SubType> unsupportedFunctionTypes;
  if (sbmlLevel == 1)
    {
      // check what to do with all the functions that are not supported by
      // SBML Level 1
      // Also take care of other unsupported nodes in L1
      // (inf,nan,pi,exponentiale)
      // most functions that are not supported by Level 1, but Level 2
      //  can not be converted to something that can be exported.
      // Roundtripping of those  will not succeed, but the results should stay
      // the same. The only function that can not be correctly converted
      // is ARCCOTH since we would need a piecewise for that which is not
      // supported in Level 1
      unsupportedFunctionTypes.insert(CEvaluationNodeFunction::ARCCOTH);
      unsupportedFunctionTypes.insert(CEvaluationNodeFunction::RNORMAL);
      unsupportedFunctionTypes.insert(CEvaluationNodeFunction::RUNIFORM);
    }
  else
    {
      unsupportedFunctionTypes.insert(CEvaluationNodeFunction::RNORMAL);
      unsupportedFunctionTypes.insert(CEvaluationNodeFunction::RUNIFORM);
    }
  return unsupportedFunctionTypes;
}

/**
 * Export the model to SBML.
 * The model is written to the file given by filename.
 * If the export fails, false is returned.
 */
bool CSBMLExporter::exportModel(CCopasiDataModel& dataModel, const std::string& filename, unsigned int sbmlLevel, unsigned int sbmlVersion, bool overwrite)
{
  bool success = true;
  /* create a string that represents the SBMLDocument */
  std::string str = this->exportModelToString(dataModel, sbmlLevel, sbmlVersion);
  if (!str.empty())
    {
      /* check if the file already exisits.
         If yes, write if overwrite is true,
         else create an appropriate  CCopasiMessage. */
      std::ifstream testInfile(utf8ToLocale(filename).c_str(), std::ios::in);
      if (testInfile && !overwrite)
        {
          // create a CCopasiMessage with the appropriate error
          CCopasiMessage(CCopasiMessage::ERROR, MCDirEntry + 1, filename.c_str());
          return false;
        }
      /* write the document to a file */
      std::ofstream outfile(utf8ToLocale(filename).c_str(), std::ios::out | std::ios::trunc);
      outfile << str;
      outfile.close();
    }
  else
    {
      /* if no SBMLDocument could be created return false */
      success = false;
    }
  return success;
}

/**
 * Checks whether the given data model can be exported to a certain version of SBML.
 * If it can be exported, the result vector will be empty, otherwise it will
 * contain a number of messages that specify why it can't be exported.
 */
const std::vector<SBMLIncompatibility> CSBMLExporter::isModelSBMLCompatible(const CCopasiDataModel& dataModel, int sbmlLevel, int sbmlVersion)
{
  const CModel* pModel = dataModel.getModel();
  std::vector<SBMLIncompatibility> result;
  if (pModel == NULL) return result;
  // general checks
  // check if there is a species with an ode rule that is in a nonfixed
  // compartment
  checkForODESpeciesInNonfixedCompartment(dataModel, result);

  // check if the model contains references to model entities that can not be
  // represented in SBML like the inital value of something as opposed to the
  // transient value
  // check if the model contains calls to functions that are not supported in
  // the given version of SBML
  CModelEntity::Status status;
  const CExpression* pExpression = NULL;
  std::set<std::string> usedFunctionNames;
  CCopasiVectorNS<CCompartment>::const_iterator compIt = pModel->getCompartments().begin();
  CCopasiVectorNS<CCompartment>::const_iterator compEndit = pModel->getCompartments().end();
  while (compIt != compEndit)
    {
      status = (*compIt)->getStatus();
      if (status == CModelEntity::ODE || status == CModelEntity::ASSIGNMENT)
        {
          pExpression = (*compIt)->getExpressionPtr();
          assert(pExpression != NULL);
          if (pExpression != NULL)
            {
              // check for unsupported object references and unsupported function
              // calls
              CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, (*compIt)->getObjectName(), "compartment");
              CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
            }
        }
      pExpression = (*compIt)->getInitialExpressionPtr();
      if (pExpression != NULL)
        {
          // check for unsupported object references and unsupported function
          // calls
          CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, (*compIt)->getObjectName(), "initial expression for compartment");
          CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
        }
      ++compIt;
    }

  CCopasiVector<CMetab>::const_iterator metabIt = pModel->getMetabolites().begin();
  CCopasiVector<CMetab>::const_iterator metabEndit = pModel->getMetabolites().end();
  while (metabIt != metabEndit)
    {
      status = (*metabIt)->getStatus();
      if (status == CModelEntity::ODE || status == CModelEntity::ASSIGNMENT)
        {
          pExpression = (*metabIt)->getExpressionPtr();
          assert(pExpression != NULL);
          if (pExpression != NULL)
            {
              // check for unsupported object references and unsupported function
              // calls
              CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, (*metabIt)->getObjectName(), "rule for compartment");
              CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
            }
        }
      pExpression = (*metabIt)->getInitialExpressionPtr();
      if (pExpression != NULL)
        {
          // check for unsupported object references and unsupported function
          // calls
          CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, (*metabIt)->getObjectName(), "initial expression for metabolite");
          CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
        }
      ++metabIt;
    }

  CCopasiVectorN<CModelValue>::const_iterator mvIt = pModel->getModelValues().begin();
  CCopasiVectorN<CModelValue>::const_iterator mvEndit = pModel->getModelValues().end();
  while (mvIt != mvEndit)
    {
      status = (*mvIt)->getStatus();
      if (status == CModelEntity::ODE || status == CModelEntity::ASSIGNMENT)
        {
          pExpression = (*mvIt)->getExpressionPtr();
          assert(pExpression != NULL);
          if (pExpression != NULL)
            {
              // check for unsupported object references and unsupported function
              // calls
              CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, (*mvIt)->getObjectName(), "rule for global parameter");
              CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
            }
        }
      pExpression = (*mvIt)->getInitialExpressionPtr();
      if (pExpression != NULL)
        {
          // check for unsupported object references and unsupported function
          // calls
          CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, (*mvIt)->getObjectName(), "initial expression for global parameter");
          CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
        }
      ++mvIt;
    }

  // since all kinetic laws in COPASI are simple function calls and the
  // arguments to the call can only be parameters or species, the expressions
  // in kinetic laws are always automatically valid for SBML export
  // However the functions that are called must not be valid

  // check all functions that are used if they contain invalid function calls

  // level dependent checks
  CCopasiVectorN<CEvent>::const_iterator eventIt, eventEndit;
  switch (sbmlLevel)
    {
    case 2:
      /*
      // check all events
      eventIt = pModel->getEvents().begin();
      eventEndit = pModel->getEvents().end();
      while (eventIt != eventEndit)
        {
          // TODO add code to check event expressions
          // TODO this has to be done once events are funktional
          ++eventIt;
        }
        */
      switch (sbmlVersion)
        {
        case 1:
          CSBMLExporter::isModelSBMLL2V1Compatible(dataModel, result);
          break;
        case 2:
        case 3:
          CSBMLExporter::isModelSBMLL2V3Compatible(dataModel, result);
          break;
        default:
          result.push_back(SBMLIncompatibility(6, sbmlLevel, sbmlVersion));
          break;
        }
      break;
    case 1:
      CSBMLExporter::isModelSBMLL1Compatible(dataModel, result);
      break;
    default:
      result.push_back(SBMLIncompatibility(6, sbmlLevel, sbmlVersion));
      break;
    }
  return result;
}

void CSBMLExporter::createEvents(CCopasiDataModel& dataModel)
{
  if (this->mSBMLLevel == 1)
    {
      CSBMLExporter::checkForEvents(dataModel, this->mIncompatibilities);
    }
  else
    {
      if (dataModel.getModel() == 0) return;
      const CCopasiVectorN<CEvent>& events = dataModel.getModel()->getEvents();
      CCopasiVectorN<CEvent>::const_iterator it = events.begin(), endit = events.end();
      while (it != endit)
        {
          createEvent(**it);
          ++it;
        }
    }
}

void CSBMLExporter::createEvent(CEvent& /*event*/)
{
  // TODO once events are functional, we create them here
  // TODO don't forget to call replaceSpeciesReferences
  // TODO on all mathematical expressions
}

void CSBMLExporter::checkForEvents(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result)
{
  if (dataModel.getModel() != NULL && dataModel.getModel()->getEvents().size() > 0)
    {
      result.push_back(SBMLIncompatibility(7));
    }
}

void CSBMLExporter::updateCOPASI2SBMLMap(const CCopasiDataModel& dataModel)
{
  // make sure the idMap is already uptodate
  // go through the existing map and create a new one with all SBML
  // objects updated with objects from the copied
  // model
  this->mCOPASI2SBMLMap.clear();
  std::map<CCopasiObject*, SBase*>::const_iterator it = const_cast<CCopasiDataModel&>(dataModel).getCopasi2SBMLMap().begin();
  std::map<CCopasiObject*, SBase*>::const_iterator endit = const_cast<CCopasiDataModel&>(dataModel).getCopasi2SBMLMap().end();
  while (it != endit)
    {
      std::map<std::string, const SBase*>::iterator pos = this->mIdMap.find(it->second->getId());
      if (pos != this->mIdMap.end())
        {
          this->mCOPASI2SBMLMap.insert(std::make_pair(it->first, const_cast<SBase*>(pos->second)));
        }
      ++it;
    }
}

KineticLaw* CSBMLExporter::createKineticLaw(CReaction& reaction, CCopasiDataModel& dataModel)
{
  KineticLaw* pKLaw = NULL;
  if (!pKLaw)
    {
      /* create a new KineticLaw */
      pKLaw = new KineticLaw();
    }
  // create the local parameters
  unsigned int i, iMax = reaction.getFunctionParameters().size();
  for (i = 0; i < iMax; ++i)
    {
      const CFunctionParameter* pPara = reaction.getFunctionParameters()[i];
      if (pPara->getUsage() == CFunctionParameter::PARAMETER)
        {
          // only create a parameter if it is a local parameter,
          // otherwise the parameter already has been created
          if (reaction.isLocalParameter(i))
            {
              Parameter* pSBMLPara = pKLaw->createParameter();

              pSBMLPara->setId(pPara->getObjectName().c_str());
              double value = reaction.getParameterValue(pPara->getObjectName());
              // if the value is NaN, leave the parameter value unset.
              if (!isnan(value))
                {
                  pSBMLPara->setValue(value);
                }
            }
        }
    }
  // the next few lines replace references to species depending on whether
  // it is a reference to an amount or a reference to a concentration.
  // Other factors that influence this replacement are if the model
  // contains variable volumes or if the quantity units are set to CModel::number
  CEvaluationNode* pExpression = CSBMLExporter::createKineticExpression(const_cast<CFunction*>(reaction.getFunction()), reaction.getParameterMappings());
  if (pExpression == NULL)
    {
      delete pKLaw;
      pKLaw = NULL;
    }
  else
    {
      /*
      ** If the reaction takes place in a single compartment, the rate law has
      ** to be converted from concentration/time to substance/time by
      ** multiplying the rate law with the volume of the compartment.
      */
      CEvaluationNode* pOrigNode = this->replaceSpeciesReferences(pExpression, dataModel);
      delete pExpression;
      assert(pOrigNode != NULL);
      ASTNode* pNode = this->convertToASTNode(pOrigNode, dataModel);
      delete pOrigNode;
      assert(pNode != NULL);
      if (reaction.getCompartmentNumber() == 1)
        {
          const CCompartment& compartment = (reaction.getChemEq().getSubstrates().size() != 0) ? (*reaction.getChemEq().getSubstrates()[0]->getMetabolite()->getCompartment()) : (*reaction.getChemEq().getProducts()[0]->getMetabolite()->getCompartment());
          // check if the importer has added a division by the volume
          // if so remove it instead of multiplying again
          ASTNode* pTNode = CSBMLExporter::isDividedByVolume(pNode, compartment.getSBMLId());
          if (pTNode)
            {
              if (pTNode->getNumChildren() == 0)
                {
                  fatalError();
                }
              if (pTNode->getNumChildren() == 1)
                {
                  ASTNode* pTmp = static_cast<ConverterASTNode*>(pTNode)->removeChild(0);
                  delete pTNode;
                  pTNode = pTmp;
                }
              delete pNode;
              pNode = pTNode;
            }
          else
            {
              pTNode = new ASTNode(AST_TIMES);
              ASTNode* pVNode = new ASTNode(AST_NAME);
              pVNode->setName(compartment.getSBMLId().c_str());
              pTNode->addChild(pVNode);
              pTNode->addChild(pNode);
              pNode = pTNode;
            }
        }
      pKLaw->setMath(pNode);
      delete pNode;
    }
  return pKLaw;
}

ASTNode* CSBMLExporter::isDividedByVolume(const ASTNode* pRootNode, const std::string& compartmentId)
{
  ASTNode* pResult = NULL;
  if (pRootNode->getType() == AST_DIVIDE || pRootNode->getType() == AST_TIMES)
    {
      ASTNode* pTmpResultNode = new ConverterASTNode(pRootNode->getType());
      unsigned int i, iMax = pRootNode->getNumChildren();
      bool found = false;
      for (i = 0; i < iMax;++i)
        {
          const ASTNode* pChild = pRootNode->getChild(i);
          if (pRootNode->getType() == AST_DIVIDE && pChild->getType() == AST_NAME && pChild->getName() == compartmentId)
            {
              found = true;
            }
          else if ((!found) && (pChild->getType() == AST_DIVIDE || pChild->getType() == AST_TIMES))
            {
              ASTNode* pSubResult = CSBMLExporter::isDividedByVolume(pChild, compartmentId);
              if (pSubResult != NULL)
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
                  pTmpResultNode->addChild(new ConverterASTNode(*pChild));
                }
            }
          else
            {
              pTmpResultNode->addChild(new ConverterASTNode(*pChild));
            }
        }
      if (found)
        {
          pResult = pTmpResultNode;
        }
      else
        {
          delete pTmpResultNode;
        }
    }
  return pResult;
}

CEvaluationNode* CSBMLExporter::createKineticExpression(CFunction* pFun, const std::vector<std::vector<std::string> >& arguments)
{
  if (!pFun || pFun->getVariables().size() != arguments.size()) fatalError();
  CEvaluationNode* pResult;
  if (pFun->getType() == CEvaluationTree::MassAction)
    {
      pResult = CSBMLExporter::createMassActionExpression(arguments, pFun->isReversible() == TriTrue);
    }
  else
    {
      std::string id = pFun->getSBMLId();
      if (id.empty())
        {
          id = pFun->getObjectName();
          if (CSBMLExporter::isValidSId(id))
            {
              if (this->mIdMap.find(id) != this->mIdMap.end())
                {
                  id = CSBMLExporter::createUniqueId(this->mIdMap, id + "_");
                }
            }
          else
            {
              id = CSBMLExporter::createUniqueId(this->mIdMap, "function_");
            }
          this->mIdMap.insert(std::make_pair(id, (const SBase*)NULL));
          pFun->setSBMLId(id);
        }
      CEvaluationNodeCall* pFunctionCall = new CEvaluationNodeCall(CEvaluationNodeCall::FUNCTION, pFun->getObjectName());
      this->mUsedFunctions.insert(pFun);
      unsigned int i, iMax = arguments.size();
      std::string cn;
      for (i = 0;i < iMax;++i)
        {
          if (arguments[i].size() != 1) fatalError(); // we can't have arrays here.
          const CCopasiObject* pObject = GlobalKeys.get(arguments[i][0]);
          if (!pObject) fatalError();
          if (dynamic_cast<const CModel*>(pObject) != NULL)
            {
              cn = "<" + pObject->getCN() + ",Reference=Time>";
            }
          else if (dynamic_cast<const CCompartment*>(pObject) != NULL)
            {
              cn = "<" + pObject->getCN() + ",Reference=Volume>";
            }
          else if (dynamic_cast<const CMetab*>(pObject) != NULL)
            {
              cn = "<" + pObject->getCN() + ",Reference=Concentration>";
            }
          else if (dynamic_cast<const CModelValue*>(pObject) != NULL)
            {
              cn = "<" + pObject->getCN() + ",Reference=Value>";
            }
          else if (dynamic_cast<const CReaction*>(pObject) != NULL)
            {
              cn = "<" + pObject->getCN() + ",Reference=Flux>";
            }
          else if (dynamic_cast<const CCopasiParameter*>(pObject) != NULL)
            {
              // local parameter of a reaction
              // must set the node content to the SBML id if the parameter
              cn = "<" + pObject->getCN() + ">";
            }
          else
            {
              cn = "<" + pObject->getCN() + ">";
            }
          pFunctionCall->addChild(new CEvaluationNodeObject(CEvaluationNodeObject::ANY, cn));
        }
      pResult = pFunctionCall;
    }
  return pResult;
}

/**
 * This method creates an ASTNode tree where all the species specified in
 * the given vector are multiplied. This is used to create the mass action
 * kinetic law.
 */
ASTNode* CSBMLExporter::createTimesTree(const CCopasiVector<CChemEqElement >& vect, unsigned int pos)
{
  ASTNode* pNode = NULL;
  double multiplicity = vect[pos]->getMultiplicity();
  if (pos == vect.size() - 1)
    {
      pNode = new ASTNode(AST_NAME);
      const CMetab* pMetab = vect[pos]->getMetabolite();
      assert(pMetab);

      pNode->setName(pMetab->getSBMLId().c_str());
      /* if the stoichiometry is not 1.0, we have to add it to the exponent */
      if (multiplicity != 1.0)
        {
          ASTNode* pTmpNode1 = new ASTNode(AST_POWER);
          ASTNode* pTmpNode2 = new ASTNode(AST_REAL);
          pTmpNode2->setValue(multiplicity);
          pTmpNode1->addChild(pNode);
          pTmpNode1->addChild(pTmpNode2);
          pNode = pTmpNode1;
        }
    }
  else
    {
      pNode = new ASTNode(AST_TIMES);
      ASTNode* pChild = new ASTNode(AST_NAME);
      const CMetab* pMetab = vect[pos]->getMetabolite();
      assert(pMetab);

      pChild->setName(pMetab->getSBMLId().c_str());

      /* if the stoichiometry is not 1.0, we have to add it to the exponent */
      if (multiplicity != 1.0)
        {
          ASTNode* pTmpNode1 = new ASTNode(AST_POWER);
          ASTNode* pTmpNode2 = new ASTNode(AST_REAL);
          pTmpNode2->setValue(multiplicity);
          pTmpNode1->addChild(pChild);
          pTmpNode1->addChild(pTmpNode2);
          pChild = pTmpNode1;
        }

      pNode->addChild(pChild);
      pNode->addChild(CSBMLExporter::createTimesTree(vect, pos + 1));
    }
  return pNode;
}

/**
 * Go through a CEvaluationNode base tree and add the names
 * of all functions directly called in this tree to the set.
 */
void CSBMLExporter::findDirectlyUsedFunctions(const CEvaluationNode* pRootNode, std::set<std::string>& result)
{
  if (pRootNode == NULL) return;
  if (CEvaluationNode::type(pRootNode->getType()) == CEvaluationNode::CALL)
    {
      result.insert(pRootNode->getData());
    }
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pRootNode->getChild());
  while (pChild != NULL)
    {
      CSBMLExporter::findDirectlyUsedFunctions(pChild, result);
      pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
    }
}

const std::vector<CFunction*> CSBMLExporter::findUsedFunctions(std::set<CFunction*>& functions, CFunctionDB* pFunctionDB)
{
  std::map<CFunction*, std::set<CFunction*> > functionDependencyMap;
  std::set<CFunction*>::iterator setit = functions.begin(), setendit = functions.end();
  // create the dependency map
  while (setit != setendit)
    {
      std::set<std::string> usedFunctionNames;
      CSBMLExporter::findDirectlyUsedFunctions(const_cast<CFunction*>(*setit)->getRoot(), usedFunctionNames);
      std::set<CFunction*> usedFunctions = CSBMLExporter::createFunctionSetFromFunctionNames(usedFunctionNames, pFunctionDB);
      functionDependencyMap[*setit] = usedFunctions;
      ++setit;
    }
  bool found = true;
  while (found)
    {
      found = false;
      std::map<CFunction*, std::set<CFunction*> >::iterator mapIt = functionDependencyMap.begin(), mapEndit = functionDependencyMap.end();
      while (mapIt != mapEndit)
        {
          setit = mapIt->second.begin(), setendit = mapIt->second.end();
          while (setit != setendit)
            {
              // check if we already have the dependencies for the function
              if (functionDependencyMap.find(*setit) == functionDependencyMap.end())
                {
                  found = true;
                  std::set<std::string> usedFunctionNames;
                  CSBMLExporter::findDirectlyUsedFunctions(const_cast<CFunction*>(*setit)->getRoot(), usedFunctionNames);
                  std::set<CFunction*> usedFunctions = CSBMLExporter::createFunctionSetFromFunctionNames(usedFunctionNames, pFunctionDB);
                  functionDependencyMap[*setit] = usedFunctions;
                }
              ++setit;
            }
          // if we changed the map, we have to stop the inner loop since the
          // map iterator is now invalid
          if (found)
            {
              break;
            }
          ++mapIt;
        }
    }
  bool removed = true;
  std::vector<CFunction*> functionVector;
  while (!functionDependencyMap.empty() && removed == true)
    {
      std::map<CFunction*, std::set<CFunction*> >::iterator mapIt = functionDependencyMap.begin(), mapEndit = functionDependencyMap.end();
      removed = false;
      // go through the map and find functions that have no dependencies
      while (mapIt != mapEndit)
        {
          if (mapIt->second.empty())
            {
              // set remove to true so that we know that at least one
              // function definition without dependencies has been found
              // otherwise we might end up in an endless loop
              removed = true;
              // add the function to the front
              functionVector.push_back(mapIt->first);
              // remove this function from the dependency list of all other
              // functions
              std::map<CFunction*, std::set<CFunction*> >::iterator mapIt2 = functionDependencyMap.begin(), mapEndit2 = functionDependencyMap.end();
              while (mapIt2 != mapEndit2)
                {
                  std::set<CFunction*>::iterator pos = mapIt2->second.find(mapIt->first);
                  if (pos != mapIt2->second.end())
                    {
                      mapIt2->second.erase(pos);
                    }
                  ++mapIt2;
                }
              // delete the entry of this function from the depenency map
              std::map<CFunction*, std::set<CFunction*> >::iterator pos = mapIt;
              ++mapIt;
              functionDependencyMap.erase(pos);
            }
          else
            {
              ++mapIt;
            }
        }
    }
  // check if the dependency map is empty. If not, there must be a dependency
  // loop
  if (!functionDependencyMap.empty())
    {
      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, "Dependency loop found in function definitions.");
    }
  return functionVector;
}

const std::set<CFunction*> CSBMLExporter::createFunctionSetFromFunctionNames(const std::set<std::string>& names, CFunctionDB* pFunDB)
{
  std::set<CFunction*> result;
  if (pFunDB != NULL)
    {
      std::set<std::string>::const_iterator it = names.begin();
      std::set<std::string>::const_iterator endit = names.end();
      CFunction* pFun = NULL;
      while (it != endit)
        {
          pFun = dynamic_cast<CFunction*>(pFunDB->findFunction(*it));
          if (pFun == NULL)
            {
              CCopasiMessage::CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 15, (*it).c_str());
            }
          else
            {
              result.insert(pFun);
            }
          ++it;
        }
    }
  return result;
}

std::vector<CModelEntity*> CSBMLExporter::orderRules(const CCopasiDataModel& dataModel)
{
  // make sure the vector of rules is filled
  std::map<CModelEntity*, std::set<const CModelEntity*> > dependencyMap;
  std::vector<CModelEntity*>::iterator it = this->mAssignmentVector.begin(), endit = this->mAssignmentVector.end();
  while (it != endit)
    {
      const CExpression* pExpr = (*it)->getExpressionPtr();
      assert(pExpr != NULL);
      std::set<const CModelEntity*> dependencies;
      CSBMLExporter::findModelEntityDependencies(pExpr->getRoot(), dataModel, dependencies);
      /*
      std::vector<CModelEntity*>::iterator it2 = this->mAssignmentVector.begin(), endit2 = this->mAssignmentVector.end();
      while (it2 != endit2)
        {
          std::set<const CModelEntity*>::iterator pos = dependencies.find(*it2);
          if (pos != dependencies.end())
            {
              dependencies.erase(pos);
            }
          ++it2;
        }
        */
      dependencyMap[*it] = dependencies;
      ++it;
    }
  // now sort the entities according to their dependencies
  bool error = false;
  std::vector<CModelEntity*> orderedRules;
  // remove all dependencies that don't have assignment rules themselves
  std::map<CModelEntity*, std::set<const CModelEntity*> > reducedDependencyMap;
  std::map<CModelEntity*, std::set<const CModelEntity*> >::iterator mapIt = dependencyMap.begin(), mapEndit = dependencyMap.end();
  while (mapIt != mapEndit)
    {
      std::set<const CModelEntity*> dependencies;
      std::set<const CModelEntity*>::const_iterator setIt = mapIt->second.begin(), setEndit = mapIt->second.end();
      while (setIt != setEndit)
        {
          if (dependencyMap.find(const_cast<CModelEntity*>(*setIt)) != dependencyMap.end())
            {
              dependencies.insert(*setIt);
            }
          ++setIt;
        }
      reducedDependencyMap[mapIt->first] = dependencies;
      ++mapIt;
    }
  while (error == false && !reducedDependencyMap.empty())
    {
      mapIt = reducedDependencyMap.begin(), mapEndit = reducedDependencyMap.end();
      // if we cant't remove anything in one round, we have a circular
      // dependency
      error = true;
      while (mapIt != mapEndit)
        {
          // if the dependency list of the item is not empty
          // we remove all entities that have been removed already
          if (!mapIt->second.empty())
            {
              std::vector<CModelEntity*>::iterator vIt = orderedRules.begin(), vEndit = orderedRules.end();
              while (vIt != vEndit)
                {
                  std::set<const CModelEntity*>::iterator pos = mapIt->second.find(*vIt);
                  if (pos != mapIt->second.end())
                    {
                      mapIt->second.erase(pos);
                    }
                  ++vIt;
                }
            }
          if (mapIt->second.empty())
            {
              // since the dependencies are empty, we can add the rule to be
              // exported
              orderedRules.push_back(mapIt->first);
              // now we know that we could remove something in this round
              error = false;
              break;
            }
          ++mapIt;
        }
      if (error == false)
        {
          reducedDependencyMap.erase(mapIt);
        }
    }
  return orderedRules;
}

void CSBMLExporter::findModelEntityDependencies(const CEvaluationNode* pNode, const CCopasiDataModel& dataModel, std::set<const CModelEntity*>& dependencies)
{
  if (pNode == NULL) return;
  if (CEvaluationNode::type(pNode->getType()) == CEvaluationNode::OBJECT)
    {
      const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
      assert(pObjectNode != NULL);
      if (pObjectNode != NULL)
        {
          const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(pObjectNode->getObjectCN());
          assert(pObject);
          if (pObject->isReference())
            {
              pObject = pObject->getObjectParent();
              assert(pObject != NULL);
            }
          const CModelEntity* pME = dynamic_cast<const CModelEntity*>(pObject);
          if (pME != NULL)
            {
              dependencies.insert(pME);
            }
        }
    }
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  while (pChild != NULL)
    {
      CSBMLExporter::findModelEntityDependencies(pChild, dataModel, dependencies);
      pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
    }
}

void CSBMLExporter::convertToLevel1()
{
  // expand all function calls in rules, events and
  // kinetic laws and delete the functions
  // initial assignments do not need to be considered since they can not be
  // exported to Level 1 anyway
  //
  // checking of the resulting expressions for piecewise functions
  // is done in the convertASTTreeToLevel1 method
  if (this->mpSBMLDocument == NULL) return;
  Model* pModel = this->mpSBMLDocument->getModel();
  Rule* pRule = NULL;
  Reaction* pReaction = NULL;
  KineticLaw* pLaw = NULL;
  unsigned int i, iMax = pModel->getNumRules();
  for (i = 0;i < iMax;++i)
    {
      pRule = pModel->getRule(i);
      assert(pRule != NULL);
      const ASTNode* pMath = pRule->getMath();
      assert(pMath != NULL);
      std::string message = "rule for object with id \"";
      message += pRule->getVariable();
      message += "\"";
      CSBMLExporter::convertASTTreeToLevel1(pMath, pModel, message);
    }
  /*
  Event* pEvent = NULL;
  iMax = pModel->getNumEvents();
  for (i = 0;i < iMax;++i)
    {
      pEvent = pModel->getEvent(i);
      assert(pEvent != NULL);
      const Trigger* pTrigger = pEvent->getTrigger();
      assert(pTrigger != NULL);
      const ASTNode* pMath = pTrigger->getMath();
      assert(pMath != NULL);
      std::string message = "event with id \"";
      message += pEvent->getId();
      message += "\"";
      pMath = CSBMLExporter::convertASTTreeToLevel1(pMath, pModel, message);
      if (pMath != NULL)
        {
          Trigger* pNewTrigger = new Trigger(pMath);
          delete pMath;
          pEvent->setTrigger(pNewTrigger);
          delete pNewTrigger;
        }
      else
        {
          fatalError();
        }
      unsigned int j, jMax = pEvent->getNumEventAssignments();
      const EventAssignment* pEA = NULL;
      for (j = 0;j < jMax;++j)
        {
          pEA = pEvent->getEventAssignment(i);
          assert(pEA != NULL);
          pMath = pEA->getMath();
          assert(pMath != NULL);
          message = "event assignment for variable with id \"";
          message += pEA->getVariable();
          message += "\" in event with id \"";
          message += pEvent->getId();
          message + "\"";
          pMath = CSBMLExporter::convertASTTreeToLevel1(pMath, pModel, message);
          if (pMath != NULL)
            {
              // delete the old event assignment and create a new one
              EventAssignment* pNewEA = new EventAssignment(*pEA);
              pNewEA->setMath(pMath);
              delete pMath;
              pEvent->getListOfEventAssignments()->remove(j);
              delete pEA;
              pEvent->addEventAssignment(pNewEA);
              delete pNewEA;
            }
          else
            {
              fatalError();
            }
        }
    }
    */
  iMax = pModel->getNumReactions();
  for (i = 0;i < iMax;++i)
    {
      pReaction = pModel->getReaction(i);
      assert(pReaction != NULL);
      pLaw = pReaction->getKineticLaw();
      // maybe we don't have a kinetic law for all reactions
      if (pLaw != NULL)
        {
          const ASTNode* pMath = pLaw->getMath();
          assert(pMath != NULL);
          std::string message = "kinetic law in reaction with id \"";
          message += pReaction->getId();
          message += "\"";
          pMath = CSBMLExporter::convertASTTreeToLevel1(pMath, pModel, message);
          if (pMath != NULL)
            {
              pLaw->setMath(pMath);
              delete pMath;
            }
          else
            {
              fatalError();
            }
        }
    }
}

ASTNode* CSBMLExporter::replaceL1IncompatibleNodes(const ASTNode* pNode)
{
  // replace all inf, pi, nan and exponentiale nodes
  // replace all unsupported functions calls: SEC,CSC, COT, SINH, COSH,
  // TANH, SECH, CSCH, COTH, ARCSINH, ARCCOSH, ARCTANH, ARCSECH, ARCSCSH,
  // ARCCOTH
  if (pNode == NULL) return NULL;
  ASTNode* pResult = NULL;
  ASTNode* pChild = NULL;
  unsigned int i, iMax;
  switch (pNode->getType())
    {
    case AST_FUNCTION_PIECEWISE:
      break;
    case AST_CONSTANT_E:
      // replace by exp(1)
      pResult = new ASTNode(AST_FUNCTION_EXP);
      pChild = new ASTNode(AST_REAL);
      pChild->setValue(1.0);
      pResult->addChild(pChild);
      break;
    case AST_CONSTANT_PI:
      // replace by 2*ASIN(1.0)
      pResult = new ASTNode(AST_TIMES);
      pChild = new ASTNode(AST_REAL);
      pChild->setValue(2.0);
      pResult->addChild(pChild);
      pResult->addChild(new ASTNode(AST_FUNCTION_ARCSIN));
      pChild = new ASTNode(AST_REAL);
      pChild->setValue(1.0);
      pResult->getChild(1)->addChild(pChild);
      break;
    case AST_FUNCTION_SEC:
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_SEC(pChild);
      // replace by 1/cos(X)
      delete pChild;
      break;
    case AST_FUNCTION_CSC:
      // replace by 1/sin(X)
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_CSC(pChild);
      delete pChild;
      break;
    case AST_FUNCTION_COT:
      // replace by 1/tan(X)
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_COT(pChild);
      delete pChild;
      break;
    case AST_FUNCTION_SINH:
      // replace by (e^X-e^(-X))/2
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_SINH(pChild);
      delete pChild;
      break;
    case AST_FUNCTION_COSH:
      // replace by (e^X+e^(-X))/2
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_COSH(pChild);
      delete pChild;
      break;
    case AST_FUNCTION_TANH:
      // replace by (e^X-e^(-X))/(e^X+e^(-X))
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_TANH(pChild);
      delete pChild;
      break;
    case AST_FUNCTION_SECH:
      // replace by 2/(e^X+e^(-X))
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_SECH(pChild);
      delete pChild;
      break;
    case AST_FUNCTION_CSCH:
      // replace by 2/(e^X-e^(-X))
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_CSCH(pChild);
      delete pChild;
      break;
    case AST_FUNCTION_COTH:
      // replace by (e^X+e^(-X))/(e^X-e^(-X))
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_COTH(pChild);
      delete pChild;
      break;
    case AST_FUNCTION_ARCSINH:
      // replace by log(X + sqrt(X^2 + 1))
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_ARCSINH(pChild);
      delete pChild;
      break;
    case AST_FUNCTION_ARCCOSH:
      // replace by log(X + sqrt(X-1) * sqrt(X+1))
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_ARCCOSH(pChild);
      delete pChild;
      break;
    case AST_FUNCTION_ARCTANH:
      // replace by 1/2 * (log(1+X) - log(1-X))
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_ARCTANH(pChild);
      delete pChild;
      break;
    case AST_FUNCTION_ARCSECH:
      // replace by log(sqrt((1/X)-1) * sqrt(1+(1/X)) + 1/X)
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_ARCSECH(pChild);
      delete pChild;
      break;
    case AST_FUNCTION_ARCCSCH:
      // replace by log(sqrt(1+ (1/ (X^2)))+(1/X))
      pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(0));
      assert(pChild);
      pResult = replace_ARCCSCH(pChild);
      delete pChild;
      break;
    case AST_FUNCTION_ARCCOTH:
      // this one is difficult since it would need a piecewise definition which
      // is not available in SBML Level 1
      fatalError();
      break;
    case AST_REAL:
      // for nan and inf
      if (pNode->getReal() != pNode->getReal()) // NaN
        {
          // replace by 0/0
          pResult = new ASTNode(AST_RATIONAL);
          pResult->setValue(0L, 0L);
        }
      else if (pNode->getReal() > DBL_MAX)
        {
          // replace by 1/0
          pResult = new ASTNode(AST_RATIONAL);
          pResult->setValue(1L, 0L);
        }
      else if (pNode->getReal() < - DBL_MAX)
        {
          // replace by -1/0
          pResult = new ASTNode(AST_RATIONAL);
          pResult->setValue(-1L, 0L);
        }
      else
        {
          pResult = new ASTNode(*pNode);
        }
      break;
    default:
      // copy the node
      pResult = new ASTNode(*pNode);
      iMax = pNode->getNumChildren();
      for (i = 0;i < iMax;++i)
        {
          pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(i));
          assert(pChild != NULL);
          if (pChild != NULL)
            {
              pResult->addChild(pChild);
            }
          break;
        }
    }
  return pResult;
}

ASTNode* CSBMLExporter::convertASTTreeToLevel1(const ASTNode* pNode, const Model* pModel, std::string& message)
{
  ASTNode* pExpanded = create_expression(pNode, pModel);
  if (pExpanded != NULL)
    {
      ASTNode* pReplaced = CSBMLExporter::replaceL1IncompatibleNodes(pExpanded);
      delete pExpanded;
      if (pReplaced == NULL)
        {
          CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 62, message.c_str());
        }
    }
  else
    {
      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 61, message.c_str());
    }
  return pExpanded;
}

void CSBMLExporter::checkForPiecewiseFunctions(const CCopasiDataModel& dataModel, std::vector<SBMLIncompatibility>& result)
{
  std::set<std::string> usedFunctionNames;
  const CModel* pModel = dataModel.getModel();
  if (pModel == NULL) return;
  // go through all model entities and check assignments
  // we don't have to check initial assignment since those can not be exported
  // anyway
  const CModelEntity* pME = NULL;
  const CCopasiVectorNS<CCompartment>& compartments = pModel->getCompartments();
  unsigned int i, iMax = compartments.size();
  for (i = 0;i < iMax;++i)
    {
      pME = compartments[i];
      if (pME->getStatus() == CModelEntity::ODE || pME->getStatus() == CModelEntity::ASSIGNMENT)
        {
          const CEvaluationTree* pTree = pME->getExpressionPtr();
          CSBMLExporter::findDirectlyUsedFunctions(pTree->getRoot(), usedFunctionNames);
          CSBMLExporter::checkForPiecewiseFunctions(*pTree->getRoot(), result, pME->getObjectName(), "rule for compartment");
        }
    }
  const CCopasiVector<CMetab>& metabolites = pModel->getMetabolites();
  iMax = metabolites.size();
  for (i = 0;i < iMax;++i)
    {
      pME = metabolites[i];
      if (pME->getStatus() == CModelEntity::ODE || pME->getStatus() == CModelEntity::ASSIGNMENT)
        {
          const CEvaluationTree* pTree = pME->getExpressionPtr();
          CSBMLExporter::findDirectlyUsedFunctions(pTree->getRoot(), usedFunctionNames);
          CSBMLExporter::checkForPiecewiseFunctions(*pTree->getRoot(), result, pME->getObjectName(), "rule for metabolite");
        }
    }
  const CCopasiVectorN<CModelValue>& modelvalues = pModel->getModelValues();
  iMax = modelvalues.size();
  for (i = 0;i < iMax;++i)
    {
      pME = modelvalues[i];
      if (pME->getStatus() == CModelEntity::ODE || pME->getStatus() == CModelEntity::ASSIGNMENT)
        {
          const CEvaluationTree* pTree = pME->getExpressionPtr();
          CSBMLExporter::findDirectlyUsedFunctions(pTree->getRoot(), usedFunctionNames);
          CSBMLExporter::checkForPiecewiseFunctions(*pTree->getRoot(), result, pME->getObjectName(), "rule for global parameter");
        }
    }
  // go through all reactions and check the function called in the kinetic
  // laws.
  CReaction* pReaction = NULL;
  const CCopasiVectorNS<CReaction>& reactions = pModel->getReactions();
  iMax = reactions.size();
  for (i = 0;i < iMax;++i)
    {
      pReaction = reactions[i];
      if (pReaction->getFunction() != NULL)
        {
          CSBMLExporter::findDirectlyUsedFunctions(pReaction->getFunction()->getRoot(), usedFunctionNames);
        }
    }
  // check indirectly called functions
  std::set<CFunction*> directlyUsedFunctions = CSBMLExporter::createFunctionSetFromFunctionNames(usedFunctionNames, const_cast<CCopasiDataModel&>(dataModel).getFunctionList());
  std::vector<CFunction*> functions = CSBMLExporter::findUsedFunctions(directlyUsedFunctions, const_cast<CCopasiDataModel&>(dataModel).getFunctionList());
  std::vector<CFunction*>::const_iterator it = functions.begin(), endit = functions.end();
  while (it != endit)
    {
      CSBMLExporter::checkForPiecewiseFunctions(*(*it)->getRoot(), result, (*it)->getObjectName(), "function");
      ++it;
    }
}

void CSBMLExporter::checkForPiecewiseFunctions(const CEvaluationNode& node, std::vector<SBMLIncompatibility>& result, const std::string& objectName, const std::string& objectType)
{

  // no need to go through the children.
  // one incompatibility warning is enough
  if (CEvaluationNode::type(node.getType()) == CEvaluationNode::CHOICE)
    {
      result.push_back(SBMLIncompatibility(8, objectType.c_str(), objectName.c_str()));
    }
  else
    {
      // store the old size
      // if one error has been found, we can stop looking at the other
      // children
      unsigned int size = result.size();
      const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(node.getChild());
      while (pChild != NULL && result.size() == size)
        {
          CSBMLExporter::checkForPiecewiseFunctions(*pChild, result, objectName, objectType);
          pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
        }
    }
}

/**
 * Remove all compartments, species, parameters and reactions and initial
 * assignments that did not end up in mHandledSBMLObjects during an export.
 */
void CSBMLExporter::removeUnusedObjects()
{
  if (this->mpSBMLDocument != NULL || this->mpSBMLDocument->getModel() == NULL)
    {
      Model* pModel = this->mpSBMLDocument->getModel();
      std::list<SBase*> removedObjects;
      SBase* pSBase = NULL;
      ListOf* pList = pModel->getListOfCompartments();
      unsigned int i;
      for (i = pList->size();i != 0;--i)
        {
          pSBase = pList->get(i - 1);
          if (this->mHandledSBMLObjects.find(pSBase) == this->mHandledSBMLObjects.end())
            {
              removedObjects.push_back(pList->remove(i - i));
            }
        }
      pList = pModel->getListOfSpecies();
      for (i = pList->size();i != 0;--i)
        {
          pSBase = pList->get(i - 1);
          if (this->mHandledSBMLObjects.find(pSBase) == this->mHandledSBMLObjects.end())
            {
              removedObjects.push_back(pList->remove(i - i));
            }
        }
      pList = pModel->getListOfParameters();
      for (i = pList->size();i != 0;--i)
        {
          pSBase = pList->get(i - 1);
          if (this->mHandledSBMLObjects.find(pSBase) == this->mHandledSBMLObjects.end())
            {
              removedObjects.push_back(pList->remove(i - i));
            }
        }
      pList = pModel->getListOfInitialAssignments();
      for (i = pList->size();i != 0;--i)
        {
          pSBase = pList->get(i - 1);
          if (this->mHandledSBMLObjects.find(pSBase) == this->mHandledSBMLObjects.end())
            {
              // we don't have to store the initial assignments since
              // there are no rules or events for initial assignments
              delete pList->remove(i - i);
            }
        }
      pList = pModel->getListOfReactions();
      for (i = pList->size();i != 0;--i)
        {
          pSBase = pList->get(i - 1);
          if (this->mHandledSBMLObjects.find(pSBase) == this->mHandledSBMLObjects.end())
            {
              // we don't have to store the reactions since
              // there are no rules or events for reactions
              delete pList->remove(i - i);
            }
        }
      // check each removed object, if there is a rule or an event in
      // the SBML model for this object
      std::list<SBase*>::iterator it = removedObjects.begin(), endit = removedObjects.end();
      pList = pModel->getListOfRules();
      ListOf* pEventList = pModel->getListOfEvents();
      ListOf* pInitialAssignmentList = pModel->getListOfInitialAssignments();
      Rule* pRule = NULL;
      Event* pEvent = NULL;
      InitialAssignment* pIA = NULL;
      unsigned int iMax;
      while (it != endit)
        {
          iMax = pList->size();
          for (i = 0;i < iMax;++i)
            {
              pRule = dynamic_cast<Rule*>(pList->get(i));
              if (pRule != NULL && pRule->isSetVariable() && pRule->getVariable() == (*it)->getId())
                {
                  delete pList->remove(i);
                  break;
                }
            }
          iMax = pInitialAssignmentList->size();
          for (i = 0;i < iMax;++i)
            {
              pIA = dynamic_cast<InitialAssignment*>(pInitialAssignmentList->get(i));
              if (pIA->isSetSymbol() && pIA->getSymbol() == (*it)->getId())
                {
                  delete pInitialAssignmentList->remove(i);
                  break;
                }
            }
          iMax = pEventList->size();
          for (i = 0;i < iMax;++i)
            {
              pEvent = dynamic_cast<Event*>(pEventList->get(i));
              if (pEvent != NULL)
                {
                  ListOfEventAssignments* pEAL = pEvent->getListOfEventAssignments();
                  EventAssignment* pEA = NULL;
                  unsigned int j, jMax = pEAL->size();
                  for (j = 0;j < jMax;++j)
                    {
                      pEA = pEvent->getEventAssignment(j);
                      if (pEA != NULL && pEA->getVariable() == (*it)->getId())
                        {
                          delete pEAL->remove(j);
                          break;
                        }
                    }
                  // if there are no more event assignments, we can delete the
                  // event
                  if (pEAL->size() == 0)
                    {
                      delete pEventList->remove(i);
                    }
                }
            }
          delete *it;
          ++it;
        }
    }
}

CEvaluationNode* CSBMLExporter::createMassActionExpression(const std::vector<std::vector<std::string> >& arguments, bool isReversible)
{
  assert((isReversible && arguments.size() == 4) || arguments.size() == 2);
  assert(arguments[0].size() == 1 && arguments[1].size() > 0);
  // create a multiplication of all items in arguments[1] and multiply that
  // with item arguments[0][0]
  std::set<std::string> finishedElements;
  std::vector<CEvaluationNode*> multiplicants;
  const CCopasiObject* pObject = GlobalKeys.get(arguments[0][0]);
  assert(pObject != NULL);
  multiplicants.push_back(new CEvaluationNodeObject(CEvaluationNodeObject::ANY, "<" + pObject->getCN() + ",Reference=Value>"));
  std::vector<std::string>::const_iterator it = arguments[1].begin(), endit = arguments[1].end();
  while (it != endit)
    {
      if (finishedElements.find(*it) == finishedElements.end())
        {
          unsigned int num = std::count(arguments[1].begin(), arguments[1].end(), *it);
          assert(num != 0);
          finishedElements.insert(*it);
          pObject = GlobalKeys.get(*it);
          assert(pObject != NULL);
          if (num == 1)
            {
              multiplicants.push_back(new CEvaluationNodeObject(CEvaluationNodeObject::ANY, "<" + pObject->getCN() + ",Reference=Concentration>"));
            }
          else
            {
              std::ostringstream os;
              os << num;
              CEvaluationNodeOperator* pOperator = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
              pOperator->addChild(new CEvaluationNodeObject(CEvaluationNodeObject::ANY, "<" + pObject->getCN() + ",Reference=Concentration>"));
              pOperator->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, os.str()));
              multiplicants.push_back(pOperator);
            }
        }
      ++it;
    }
  std::vector<CEvaluationNode*>::reverse_iterator rIt = multiplicants.rbegin(), rEndit = multiplicants.rend();
  CEvaluationNode* pResult = *rIt;
  ++rIt;
  CEvaluationNode* pTmpNode = NULL;
  if (rIt != rEndit)
    {
      --rEndit;
      while (rIt != rEndit)
        {
          pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
          pTmpNode->addChild(*rIt);
          pTmpNode->addChild(pResult);
          pResult = pTmpNode;
          ++rIt;
        }
    }
  pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
  pTmpNode->addChild(*rIt);
  pTmpNode->addChild(pResult);
  pResult = pTmpNode;
  if (isReversible)
    {
      std::vector<std::vector<std::string> > tmpV;
      tmpV.push_back(arguments[2]);
      tmpV.push_back(arguments[3]);
      pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
      pTmpNode->addChild(pResult);
      pTmpNode->addChild(CSBMLExporter::createMassActionExpression(tmpV, false));
      pResult = pTmpNode;
    }
  return pResult;
}

bool CSBMLExporter::isValidSId(const std::string& id)
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

/**
 * Remove the initial assignment for the entity with the given id
 * if there is any.
 */
void CSBMLExporter::removeInitialAssignment(const std::string& sbmlId)
{
  ListOfInitialAssignments* pList = this->mpSBMLDocument->getModel()->getListOfInitialAssignments();
  unsigned int i, iMax = pList->size();
  for (i = 0;i < iMax;++i)
    {
      InitialAssignment* pIA = dynamic_cast<InitialAssignment*>(pList->get(i));
      if (pIA->getSymbol() == sbmlId)
        {
          pList->remove(i);
          break;
        }
    }
}

/**
 * Remove the rule for the entity with the given id
 * if there is any.
 */
void CSBMLExporter::removeRule(const std::string& sbmlId)
{
  ListOfRules* pList = this->mpSBMLDocument->getModel()->getListOfRules();
  unsigned int i, iMax = pList->size();
  for (i = 0;i < iMax;++i)
    {
      Rule* pR = dynamic_cast<Rule*>(pList->get(i));
      if (pR->getVariable() == sbmlId)
        {
          pList->remove(i);
          break;
        }
    }
}

/**
 * Replaces references to species with reference to species divided by
 * volume if it is a reference to a concentration or by a reference to the
 * species times avogadros number if it is a reference to the amount.
 * The method also takes into consideration the substance units of the
 * model.
 */
CEvaluationNode* CSBMLExporter::replaceSpeciesReferences(const CEvaluationNode* pOrigNode, const CCopasiDataModel& dataModel)
{
  CEvaluationNode* pResult = NULL;
  double factor = dataModel.getModel()->getQuantity2NumberFactor();
  if (CEvaluationNodeObject::type(pOrigNode->getType()) == CEvaluationNodeObject::OBJECT)
    {
      std::vector<CCopasiContainer*> containers;
      containers.push_back(const_cast<CModel*>(dataModel.getModel()));
      const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(containers, dynamic_cast<const CEvaluationNodeObject*>(pOrigNode)->getObjectCN());
      assert(pObject);
      if (pObject->isReference())
        {
          const CCopasiObject* pParent = pObject->getObjectParent();
          // check if the parent is a metabolite
          const CMetab* pMetab = dynamic_cast<const CMetab*>(pParent);
          if (pMetab != NULL)
            {
              // check if the reference is to the concentration or to the
              // amount
              if (pObject->getObjectName() == "InitialConcentration" || pObject->getObjectName() == "Concentration")
                {
                  // the concentration nodes only need to be replaced if we
                  // are dealing with a model that has variable volumes
                  if (this->mVariableVolumes == true)
                    {
                      // replace the node by the concentration node divided the the volume of
                      // the (initial) volume of the node
                      // although this is semantically incorrect, the result when
                      // converted to SBML will be OK since the concentration ode
                      // is converted to a reference to the species id which will
                      // be interpreted as the amount due to the
                      // hasOnlySubstanceUnits flag being set
                      const CCompartment* pCompartment = pMetab->getCompartment();
                      assert(pCompartment != NULL);
                      pResult = new CEvaluationNodeOperator(CEvaluationNodeOperator::DIVIDE, "/");
                      // copy branch should be fine since the object node does
                      // not have children
                      pResult->addChild(pOrigNode->copyBranch());
                      if (pObject->getObjectName() == "InitialConcentration")
                        {
                          pResult->addChild(new CEvaluationNodeObject(CEvaluationNodeObject::ANY, "<" + pCompartment->getObject(CCopasiObjectName("Reference=InitialVolume"))->getCN() + ">"));
                        }
                      else
                        {
                          pResult->addChild(new CEvaluationNodeObject(CEvaluationNodeObject::ANY, "<" + pCompartment->getObject(CCopasiObjectName("Reference=Volume"))->getCN() + ">"));
                        }
                    }
                  else
                    {
                      // do nothing
                      pResult = pOrigNode->copyBranch();
                    }
                }
              else if (pObject->getObjectName() == "InitialParticleNumber" || pObject->getObjectName() == "ParticleNumber")
                {
                  // if the units are not set to particle numbers anyway,
                  // replace the node by the node times avogadros number
                  if (dataModel.getModel()->getQuantityUnitEnum() != CModel::number)
                    {
                      if (this->mpAvogadro == NULL)
                        {
                          this->mpAvogadro = const_cast<CModel*>(dataModel.getModel())->createModelValue("quantity to number factor", dataModel.getModel()->getQuantity2NumberFactor());
                          Parameter* pSBMLAvogadro = this->mpSBMLDocument->getModel()->createParameter();
                          pSBMLAvogadro->setName("quantity to number factor");
                          std::string sbmlId = CSBMLExporter::createUniqueId(this->mIdMap, "parameter_");
                          pSBMLAvogadro->setId(sbmlId);
                          const_cast<CModelValue*>(this->mpAvogadro)->setSBMLId(sbmlId);
                          this->mIdMap.insert(std::make_pair(sbmlId, pSBMLAvogadro));
                          pSBMLAvogadro->setConstant(true);
                          pSBMLAvogadro->setValue(dataModel.getModel()->getQuantity2NumberFactor());
                          this->mHandledSBMLObjects.insert(pSBMLAvogadro);
                          this->mCOPASI2SBMLMap[this->mpAvogadro] = pSBMLAvogadro;
                          this->mAvogadroCreated = true;
                        }
                      pResult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
                      // copyBranch should be save here since object nodes can't
                      // have children
                      pResult->addChild(pOrigNode->copyBranch());
                      pResult->addChild(new CEvaluationNodeObject(CEvaluationNodeObject::ANY, "<" + this->mpAvogadro->getCN() + ",Reference=InitialValue>"));
                    }
                  else
                    {
                      // the result is the same as the original node
                      pResult = pOrigNode->copyBranch();
                    }
                  if (this->mVariableVolumes == false)
                    {
                      // multiply by the volume as well
                      const CCompartment* pCompartment = pMetab->getCompartment();
                      CEvaluationNode* pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
                      pTmpNode->addChild(pResult);
                      if (pObject->getObjectName() == "InitialParticleNumber")
                        {
                          pTmpNode->addChild(new CEvaluationNodeObject(CEvaluationNodeObject::ANY, "<" + pCompartment->getObject(CCopasiObjectName("Reference=InitialVolume"))->getCN() + ">"));
                        }
                      else
                        {
                          pTmpNode->addChild(new CEvaluationNodeObject(CEvaluationNodeObject::ANY, "<" + pCompartment->getObject(CCopasiObjectName("Reference=Volume"))->getCN() + ">"));
                        }
                      pResult = pTmpNode;
                    }
                }
              else
                {
                  fatalError();
                }
            }
        }
    }
  // check if there is a division by avogadros number and if so, just
  // drop the division instead of introducing a new multiplication
  else if (CEvaluationNodeObject::type(pOrigNode->getType()) == CEvaluationNodeObject::OPERATOR && ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOrigNode->getType())) == CEvaluationNodeOperator::DIVIDE)
    {
      // check if one of the child nodes is a reference to a species
      const CEvaluationNode* pLeft = dynamic_cast<const CEvaluationNodeOperator*>(pOrigNode)->getLeft();
      const CEvaluationNode* pRight = dynamic_cast<const CEvaluationNodeOperator*>(pOrigNode)->getRight();
      if (CEvaluationNode::type(pLeft->getType()) == CEvaluationNode::OBJECT)
        {
          std::vector<CCopasiContainer*> containers;
          containers.push_back(const_cast<CModel*>(dataModel.getModel()));
          const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(containers, dynamic_cast<const CEvaluationNodeObject*>(pLeft)->getObjectCN());
          assert(pObject);
          if (pObject->isReference())
            {
              const CCopasiObject* pParent = pObject->getObjectParent();
              // check if the parent is a metabolite
              const CMetab* pMetab = dynamic_cast<const CMetab*>(pParent);
              if (pMetab != NULL)
                {
                  // check if pRight is a number or a parameter that
                  // corresponds to avogadros number
                  if (CEvaluationNode::type(pRight->getType()) == CEvaluationNode::NUMBER &&
                      (((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pRight->getType())) == CEvaluationNodeNumber::DOUBLE ||
                       ((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pRight->getType())) == CEvaluationNodeNumber::ENOTATION))
                    {
                      double value = dynamic_cast<const CEvaluationNodeNumber*>(pRight)->value();
                      if (fabs((factor - value) / factor) <= 1e-3)
                        {
                          // copyBranch should be OK since the node has no
                          // children anyway
                          pResult = pLeft->copyBranch();
                        }
                    }
                  else if (CEvaluationNode::type(pRight->getType()) == CEvaluationNode::OBJECT)
                    {
                      const CCopasiObject* pObject2 = CCopasiContainer::ObjectFromName(containers, dynamic_cast<const CEvaluationNodeObject*>(pRight)->getObjectCN());
                      assert(pObject2);
                      if (pObject2->isReference())
                        {
                          const CCopasiObject* pObjectParent2 = pObject2->getObjectParent();
                          const CModelValue* pMV = dynamic_cast<const CModelValue*>(pObjectParent2);
                          if (pMV != NULL && pMV->getStatus() == CModelEntity::FIXED)
                            {
                              double value = pMV->getValue();
                              if (fabs((factor - value) / factor) <= 1e-3)
                                {
                                  pResult = pLeft->copyBranch();
                                }
                            }
                        }
                    }
                }
              else
                {
                  // Check if pRight is an object node
                  if (CEvaluationNode::type(pRight->getType()) == CEvaluationNode::OBJECT)
                    {
                      // check if pRight is a reference to a species
                      const CCopasiObject* pObject2 = CCopasiContainer::ObjectFromName(containers, dynamic_cast<const CEvaluationNodeObject*>(pRight)->getObjectCN());
                      assert(pObject2);
                      if (pObject2->isReference())
                        {
                          const CCopasiObject* pParent2 = pObject2->getObjectParent();
                          // check if the parent is a metabolite
                          pMetab = dynamic_cast<const CMetab*>(pParent2);
                          if (pMetab != NULL)
                            {
                              // if yes, check if pLeft is a parameter that corresponds
                              // to avogadros number
                              if (CEvaluationNode::type(pLeft->getType()) == CEvaluationNode::OBJECT)
                                {
                                  const CCopasiObject* pObject2 = CCopasiContainer::ObjectFromName(containers, dynamic_cast<const CEvaluationNodeObject*>(pLeft)->getObjectCN());
                                  assert(pObject2);
                                  if (pObject2->isReference())
                                    {
                                      const CCopasiObject* pObjectParent2 = pObject2->getObjectParent();
                                      const CModelValue* pMV = dynamic_cast<const CModelValue*>(pObjectParent2);
                                      if (pMV != NULL && pMV->getStatus() == CModelEntity::FIXED)
                                        {
                                          double value = pMV->getValue();
                                          if (fabs((factor - value) / factor) <= 1e-3)
                                            {
                                              pResult = pRight->copyBranch();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
      else if (CEvaluationNode::type(pRight->getType()) == CEvaluationNode::OBJECT)
        {
          std::vector<CCopasiContainer*> containers;
          containers.push_back(const_cast<CModel*>(dataModel.getModel()));
          const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(containers, dynamic_cast<const CEvaluationNodeObject*>(pRight)->getObjectCN());
          assert(pObject);
          if (pObject->isReference())
            {
              const CCopasiObject* pParent = pObject->getObjectParent();
              // check if the parent is a metabolite
              const CMetab* pMetab = dynamic_cast<const CMetab*>(pParent);
              if (pMetab != NULL)
                {
                  // check if pLeft is a number node that
                  // corresponds to Avogadros number
                  if (CEvaluationNode::type(pLeft->getType()) == CEvaluationNode::NUMBER && (((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pLeft->getType())) == CEvaluationNodeNumber::DOUBLE || ((CEvaluationNodeNumber::SubType)CEvaluationNode::subType(pLeft->getType())) == CEvaluationNodeNumber::ENOTATION))
                    {
                      double value = dynamic_cast<const CEvaluationNodeNumber*>(pLeft)->value();
                      if ((factor - value) / factor <= 1e-3)
                        {
                          // copyBranch should be OK since the node has no
                          // children anyway
                          pResult = pRight->copyBranch();
                        }
                    }
                }
            }
        }
    }
  if (pResult == NULL)
    {
      pResult = pOrigNode->copyNode(NULL, NULL);
      const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pOrigNode->getChild());
      while (pChild != NULL)
        {
          CEvaluationNode* pNewChild = this->replaceSpeciesReferences(pChild, dataModel);
          assert(pNewChild != NULL);
          pResult->addChild(pNewChild);
          pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
        }
    }
  return pResult;
}

void CSBMLExporter::findAvogadro(const CCopasiDataModel& dataModel)
{
  double factor = dataModel.getModel()->getQuantity2NumberFactor();
  CCopasiVectorN<CModelValue>::const_iterator it = dataModel.getModel()->getModelValues().begin(), endit = dataModel.getModel()->getModelValues().end();
  while (it != endit)
    {
      if ((*it)->getStatus() == CModelEntity::FIXED)
        {
          double value = (*it)->getInitialValue();
          if (fabs((factor - value) / factor) <= 1e-3)
            {
              this->mpAvogadro = *it;
            }
        }
      ++it;
    }
}

bool CSBMLExporter::updateMIRIAMAnnotation(const CCopasiObject* pCOPASIObject, SBase* pSBMLObject, std::map<std::string, const SBase*>& metaIds)
{
  bool result = true;
  if (pCOPASIObject == NULL || pSBMLObject == NULL) return false;
  const CModel* pModel = dynamic_cast<const CModel*>(pCOPASIObject);
  const CCompartment* pCompartment = dynamic_cast<const CCompartment*>(pCOPASIObject);
  const CFunction* pFunction = dynamic_cast<const CFunction*>(pCOPASIObject);
  const CModelValue* pMV = dynamic_cast<const CModelValue*>(pCOPASIObject);
  const CReaction* pReaction = dynamic_cast<const CReaction*>(pCOPASIObject);
  const CMetab* pMetab = dynamic_cast<const CMetab*>(pCOPASIObject);
  std::string miriamAnnotation;
  if (pMetab != NULL)
    {
      miriamAnnotation = pMetab->getMiriamAnnotation();
    }
  else if (pMV != NULL)
    {
      miriamAnnotation = pMV->getMiriamAnnotation();
    }
  else if (pReaction != NULL)
    {
      miriamAnnotation = pReaction->getMiriamAnnotation();
    }
  else if (pCompartment != NULL)
    {
      miriamAnnotation = pCompartment->getMiriamAnnotation();
    }
  else if (pFunction != NULL)
    {
      miriamAnnotation = pFunction->getMiriamAnnotation();
    }
  else if (pModel != NULL)
    {
      miriamAnnotation = pModel->getMiriamAnnotation();
    }
  else
    {
      // we should never end up here
      fatalError();
    }
  // we have to check if the COPASI object has MIRIAM annotation
  // if not, we have to delete the MIRIAM annotation in the SBase
  // object
  // if it does, we have to check if the SBase object has a MIRIAM annotation
  // and we have to replace it
  // if the SBase object has no annotation we have to create one with the
  // miriam annotation
  // if the SBase object has an annotation but no MIRIAM annotation, we have
  // to add the MIRIAM annotation
  // we have to check if the SBase object has a meta id and if it doesn't we
  // have to create one
  // we have to change the meta ids within the MIRIAM annotation
  /* !!! DISABLED !!!
  XMLNode* pAnnotation = NULL;
  if (pSBMLObject->isSetAnnotation())
    {
      pAnnotation = new XMLNode(*pSBMLObject->getAnnotation());
      // delete any old rdf annotations
      // first delete all children
      pAnnotation->removeChildren();
      unsigned int i, iMax = pAnnotation->getNumChildren();
      for (i = 0;i < iMax;++i)
        {
          // readd the ones that are not from the rdf namespace
          if (pSBMLObject->getAnnotation()->getChild(i).getURI() != "http://www.w3.org/1999/02/22-rdf-syntax-ns#")
            {
              pAnnotation->addChild(pSBMLObject->getAnnotation()->getChild(i));
            }
        }
    }
  */
  if (miriamAnnotation.find_first_not_of("\t\r\n ") != std::string::npos)
    {
      /* !!! DISABLED !!!
      std::string metaId;
      if (pSBMLObject->isSetMetaId())
        {
          metaId = pSBMLObject->getMetaId();
        }
      else
        {
          CSBMLExporter::createUniqueId(metaIds, "metaid");
          metaIds.insert(std::make_pair(metaId, pSBMLObject));
          pSBMLObject->setMetaId(metaId);
        }
      // now we have to replace the metaid
      CRDFUtilities::fixLocalFileAboutReference(miriamAnnotation, metaId, pCOPASIObject->getKey());
      // the new annotation is not empty, so we have to convert it
      XMLNode* pMIRIAMNode = XMLNode::convertStringToXMLNode(miriamAnnotation);
      assert(pMIRIAMNode != NULL);
      if (pAnnotation == NULL)
        {
          pAnnotation = XMLNode::convertStringToXMLNode("<annotation/>");
          assert(pAnnotation != NULL);
        }
      pAnnotation->addChild(*pMIRIAMNode);
      // delete pMIRIAMNode since addChild made a copy
      delete pMIRIAMNode;
      */
      if (this->mMIRIAMWarning == false)
        {
          this->mMIRIAMWarning = true;
          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 69);
        }
    }
  /*  !!! DISABLED !!!
  if (pAnnotation != NULL)
    {
      pSBMLObject->setAnnotation(pAnnotation);
      // delete the old annotation since it has been copied by setAnnotation
      delete pAnnotation;
    }
  */
  return result;
}

/**
 * This method creates a copy of parent where the child with the given index is
 * replaced by the new child given as the second argument.
 * If index is greater than the number of children - 1, NULL is returned.
 */
XMLNode* CSBMLExporter::replaceChild(const XMLNode* pParent, const XMLNode* pNewChild, unsigned int index)
{
  XMLNode* pResult = NULL;
  if (index < pParent->getNumChildren())
    {
      // make a shallow copy of pParent
      pResult = new XMLNode(*pParent);
      unsigned int i, iMax = pParent->getNumChildren();
      for (i = 0;i < iMax;++i)
        {
          // make a deep copy of each child, but if the index of child is the
          // given index, we add pNewChild instead of making a copy of the
          // current child
          if (i == index)
            {
              pResult->addChild(*pNewChild);
            }
          else
            {
              pResult->addChild(pParent->getChild(i));
            }
        }
    }
  return pResult;
}

/**
 * This method goes through the given SBML model and collects all ids and
 * meta ids used in the model.
 */
void CSBMLExporter::collectIds(Model* pModel, std::map<std::string, const SBase*>& ids, std::map<std::string, const SBase*>& metaIds)
{
  if (pModel != NULL)
    {
      // the model itself
      SBase* pSBase = NULL;
      std::string id;
      if (pModel->isSetId())
        {
          id = pModel->getId();
          if (ids.find(id) == ids.end())
            {
              ids.insert(std::make_pair(id, pModel));
            }
          else
            {
              CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
            }
        }
      if (pModel->isSetMetaId())
        {
          id = pModel->getMetaId();
          if (metaIds.find(id) == metaIds.end())
            {
              metaIds.insert(std::make_pair(id, pModel));
            }
          else
            {
              CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
            }
        }
      // ListOfFunctionDefinitions
      pSBase = pModel->getListOfFunctionDefinitions();
      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();
              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }
          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();
              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }
          // all FunctionDefinitions
          unsigned int i, iMax = pModel->getListOfFunctionDefinitions()->size();
          for (i = 0;i < iMax;++i)
            {
              pSBase = pModel->getListOfFunctionDefinitions()->get(i);
              if (pSBase->isSetId())
                {
                  id = pSBase->getId();
                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }
              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();
                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }
      // ListOfUnitDefinition
      pSBase = pModel->getListOfUnitDefinitions();
      if (pSBase != NULL)
        {
          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();
              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }
          // all UnitDefinitions
          // for each UnitDefinition: ListOfUnits, each Unit in ListOfUnits
          unsigned int i, iMax = pModel->getListOfUnitDefinitions()->size();
          for (i = 0;i < iMax;++i)
            {
              /* UnitDefinitions have their ids in a different namespace
                 so we only consider meta ids.
                 */
              UnitDefinition* pUDef = pModel->getUnitDefinition(i);
              assert(pUDef != NULL);
              if (pUDef->isSetMetaId())
                {
                  id = pUDef->getMetaId();
                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::make_pair(id, pUDef));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
              ListOf* pList = pUDef->getListOfUnits();
              if (pList != NULL)
                {
                  if (pList->isSetMetaId())
                    {
                      id = pList->getMetaId();
                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::make_pair(id, pList));
                        }
                      else
                        {
                          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }
                  unsigned j, jMax = pList->size();
                  for (j = 0;j < jMax;++j)
                    {
                      pSBase = pList->get(j);
                      assert(pSBase != NULL);
                      if (pSBase->isSetMetaId())
                        {
                          id = pSBase->getMetaId();
                          if (metaIds.find(id) == metaIds.end())
                            {
                              metaIds.insert(std::make_pair(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                            }
                        }
                    }
                }
            }
        }
      // ListOfCompartmentTypes
      pSBase = pModel->getListOfCompartmentTypes();
      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();
              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }
          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();
              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }
          // each compartment type
          unsigned int i, iMax = pModel->getListOfCompartmentTypes()->size();
          for (i = 0;i < iMax;++i)
            {
              pSBase = pModel->getCompartmentType(i);
              assert(pSBase != NULL);
              if (pSBase->isSetId())
                {
                  id = pSBase->getId();
                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }
              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();
                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }
      // ListOfSpeciesTypes
      pSBase = pModel->getListOfSpeciesTypes();
      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();
              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }
          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();
              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }
          // each species type
          unsigned int i, iMax = pModel->getListOfSpeciesTypes()->size();
          for (i = 0;i < iMax;++i)
            {
              pSBase = pModel->getSpeciesType(i);
              assert(pSBase != NULL);
              if (pSBase->isSetId())
                {
                  id = pSBase->getId();
                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }
              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();
                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }
      // ListOfCompartments
      pSBase = pModel->getListOfCompartments();
      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();
              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }
          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();
              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }
          // all compartments
          unsigned int i, iMax = pModel->getListOfCompartments()->size();
          for (i = 0;i < iMax;++i)
            {
              pSBase = pModel->getCompartment(i);
              assert(pSBase != NULL);
              if (pSBase->isSetId())
                {
                  id = pSBase->getId();
                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }
              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();
                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }
      // ListOfSpecies
      pSBase = pModel->getListOfSpecies();
      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();
              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }
          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();
              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }
          // all species
          unsigned int i, iMax = pModel->getListOfSpecies()->size();
          for (i = 0;i < iMax;++i)
            {
              pSBase = pModel->getSpecies(i);
              assert(pSBase != NULL);
              if (pSBase->isSetId())
                {
                  id = pSBase->getId();
                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }
              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();
                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }
      // ListOfParameters
      pSBase = pModel->getListOfParameters();
      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();
              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }
          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();
              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }
          // each parameter
          unsigned int i, iMax = pModel->getListOfParameters()->size();
          for (i = 0;i < iMax;++i)
            {
              pSBase = pModel->getParameter(i);
              assert(pSBase != NULL);
              if (pSBase->isSetId())
                {
                  id = pSBase->getId();
                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }
              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();
                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }
      // ListOfInitialAssignments
      pSBase = pModel->getListOfInitialAssignments();
      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();
              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }
          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();
              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }
          // each initial assignment
          unsigned int i, iMax = pModel->getListOfInitialAssignments()->size();
          for (i = 0;i < iMax;++i)
            {
              pSBase = pModel->getInitialAssignment(i);
              assert(pSBase != NULL);
              // initial assignments have no ids
              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();
                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }
      // ListOfRules
      pSBase = pModel->getListOfRules();
      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();
              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }
          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();
              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }
          // each rule
          unsigned int i, iMax = pModel->getListOfRules()->size();
          for (i = 0;i < iMax;++i)
            {
              pSBase = pModel->getRule(i);
              assert(pSBase != NULL);
              // rules don't have ids
              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();
                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }
      // ListOfConstraints
      pSBase = pModel->getListOfConstraints();
      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();
              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }
          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();
              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }
          // each constraint
          unsigned int i, iMax = pModel->getListOfConstraints()->size();
          for (i = 0;i < iMax;++i)
            {
              pSBase = pModel->getConstraint(i);
              assert(pSBase != NULL);
              // constraints don't have ids
              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();
                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::make_pair(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }
      // ListOfReactions
      pSBase = pModel->getListOfReactions();
      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();
              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }
          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();
              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }
          // all reactions
          unsigned int i, iMax = pModel->getListOfReactions()->size();
          for (i = 0;i < iMax;++i)
            {
              Reaction* pReaction = pModel->getReaction(i);
              assert(pReaction != NULL);
              if (pReaction->isSetId())
                {
                  id = pReaction->getId();
                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::make_pair(id, pReaction));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }
              if (pReaction->isSetMetaId())
                {
                  id = pReaction->getMetaId();
                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::make_pair(id, pReaction));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
              // for each reaction: ListOfSubstrates, each substrate, ListOfProducts, each
              // Product, ListOfModifieres, each modifier, KineticLaw, ListOfparameters,
              // each parameter
              if (pReaction->getListOfReactants() != NULL)
                {
                  pSBase = pReaction->getListOfReactants();
                  if (pSBase->isSetMetaId())
                    {
                      id = pSBase->getMetaId();
                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::make_pair(id, pSBase));
                        }
                      else
                        {
                          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }
                  unsigned int j, jMax = pReaction->getListOfReactants()->size();
                  for (j = 0;j < jMax;++j)
                    {
                      pSBase = pReaction->getReactant(j);
                      assert(pSBase != NULL);
                      // since L2V2 species references can have ids
                      if (pSBase->isSetId())
                        {
                          id = pSBase->getId();
                          if (ids.find(id) == ids.end())
                            {
                              ids.insert(std::make_pair(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                            }
                        }
                      if (pSBase->isSetMetaId())
                        {
                          id = pSBase->getMetaId();
                          if (metaIds.find(id) == metaIds.end())
                            {
                              metaIds.insert(std::make_pair(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                            }
                        }
                    }
                }
              if (pReaction->getListOfProducts() != NULL)
                {
                  pSBase = pReaction->getListOfProducts();
                  if (pSBase->isSetMetaId())
                    {
                      id = pSBase->getMetaId();
                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::make_pair(id, pSBase));
                        }
                      else
                        {
                          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }
                  unsigned int j, jMax = pReaction->getListOfProducts()->size();
                  for (j = 0;j < jMax;++j)
                    {
                      pSBase = pReaction->getProduct(j);
                      assert(pSBase != NULL);
                      // since L2V2 species references can have ids
                      if (pSBase->isSetId())
                        {
                          id = pSBase->getId();
                          if (ids.find(id) == ids.end())
                            {
                              ids.insert(std::make_pair(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                            }
                        }
                      if (pSBase->isSetMetaId())
                        {
                          id = pSBase->getMetaId();
                          if (metaIds.find(id) == metaIds.end())
                            {
                              metaIds.insert(std::make_pair(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                            }
                        }
                    }
                }
              if (pReaction->getListOfModifiers() != NULL)
                {
                  pSBase = pReaction->getListOfModifiers();
                  if (pSBase->isSetMetaId())
                    {
                      id = pSBase->getMetaId();
                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::make_pair(id, pSBase));
                        }
                      else
                        {
                          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }
                  unsigned int j, jMax = pReaction->getListOfModifiers()->size();
                  for (j = 0;j < jMax;++j)
                    {
                      pSBase = pReaction->getModifier(j);
                      assert(pSBase != NULL);
                      // since L2V2 species references can have ids
                      if (pSBase->isSetId())
                        {
                          id = pSBase->getId();
                          if (ids.find(id) == ids.end())
                            {
                              ids.insert(std::make_pair(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                            }
                        }
                      if (pSBase->isSetMetaId())
                        {
                          id = pSBase->getMetaId();
                          if (metaIds.find(id) == metaIds.end())
                            {
                              metaIds.insert(std::make_pair(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                            }
                        }
                    }
                }
              KineticLaw* pKLaw = pReaction->getKineticLaw();
              if (pKLaw != NULL)
                {
                  if (pKLaw->isSetMetaId())
                    {
                      id = pKLaw->getMetaId();
                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::make_pair(id, pKLaw));
                        }
                      else
                        {
                          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }
                  pSBase = pKLaw->getListOfParameters();
                  if (pSBase != NULL)
                    {
                      if (pSBase->isSetMetaId())
                        {
                          id = pSBase->getMetaId();
                          if (metaIds.find(id) == metaIds.end())
                            {
                              metaIds.insert(std::make_pair(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                            }
                        }
                      unsigned int j, jMax = pKLaw->getListOfParameters()->size();
                      for (j = 0;j < jMax;++j)
                        {
                          pSBase = pKLaw->getParameter(j);
                          assert(pSBase != NULL);
                          // local parameters have their ids in a
                          // differerent namespace
                          if (pSBase->isSetMetaId())
                            {
                              id = pSBase->getMetaId();
                              if (metaIds.find(id) == metaIds.end())
                                {
                                  metaIds.insert(std::make_pair(id, pSBase));
                                }
                              else
                                {
                                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                                }
                            }
                        }
                    }
                }
            }
        }
      // ListOfEvents
      pSBase = pModel->getListOfEvents();
      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();
              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }
          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();
              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::make_pair(id, pModel));
                }
              else
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }
          // each event
          unsigned int i, iMax = pModel->getListOfEvents()->size();
          for (i = 0;i < iMax;++i)
            {
              Event* pEvent = pModel->getEvent(i);
              assert(pEvent != NULL);
              if (pEvent->isSetId())
                {
                  id = pEvent->getId();
                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::make_pair(id, pEvent));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }
              if (pEvent->isSetMetaId())
                {
                  id = pEvent->getMetaId();
                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::make_pair(id, pEvent));
                    }
                  else
                    {
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
              // in each event Trigger,Delay,ListOfEventAssignments, each event assignment
              if (pEvent->isSetTrigger())
                {
                  pSBase = pEvent->getTrigger();
                  assert(pSBase != NULL);
                  if (pSBase->isSetMetaId())
                    {
                      id = pSBase->getMetaId();
                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::make_pair(id, pSBase));
                        }
                      else
                        {
                          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }
                }
              if (pEvent->isSetDelay())
                {
                  pSBase = pEvent->getDelay();
                  assert(pSBase != NULL);
                  if (pSBase->isSetMetaId())
                    {
                      id = pSBase->getMetaId();
                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::make_pair(id, pSBase));
                        }
                      else
                        {
                          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }
                }
              if (pEvent->getListOfEventAssignments() != NULL)
                {
                  pSBase = pEvent->getListOfEventAssignments();
                  if (pSBase->isSetMetaId())
                    {
                      id = pSBase->getMetaId();
                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::make_pair(id, pSBase));
                        }
                      else
                        {
                          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }
                  unsigned int j, jMax = pEvent->getListOfEventAssignments()->size();
                  for (j = 0;j < jMax;++j)
                    {
                      pSBase = pEvent->getEventAssignment(j);
                      assert(pSBase != NULL);
                      if (pSBase->isSetMetaId())
                        {
                          id = pSBase->getMetaId();
                          if (metaIds.find(id) == metaIds.end())
                            {
                              metaIds.insert(std::make_pair(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                            }
                        }
                    }
                }
            }
        }
    }
}

ASTNode* CSBMLExporter::convertToASTNode(const CEvaluationNode* pOrig, CCopasiDataModel& dataModel)
{
  // first go through the tree and check that all function calls are to
  // functions that have an SBML id
  // if they don't, we have to set one
  this->setFunctionSBMLIds(pOrig, dataModel);
  ASTNode* pResult = pOrig->toAST();
  return pResult;
}

void CSBMLExporter::setFunctionSBMLIds(const CEvaluationNode* pNode, CCopasiDataModel& dataModel)
{
  if (CEvaluationNode::type(pNode->getType()) == CEvaluationNode::CALL && (CEvaluationNodeCall::SubType)CEvaluationNode::subType(pNode->getType()) != CEvaluationNodeCall::DELAY)
    {
      std::string funName = dynamic_cast<const CEvaluationNodeCall*>(pNode)->getData();
      CEvaluationTree* pFun = dataModel.getFunctionList()->findFunction(funName);
      assert(pFun != NULL);
      if (pFun == NULL) fatalError();

      if (pFun->getSBMLId() == "")
        {
          if (CSBMLExporter::isValidSId(funName))
            {
              if (this->mIdMap.find(funName) != this->mIdMap.end())
                {
                  funName = CSBMLExporter::createUniqueId(this->mIdMap, funName);
                }
            }
          else
            {
              funName = CSBMLExporter::createUniqueId(this->mIdMap, "function_");
            }
          this->mIdMap.insert(std::make_pair(funName, (const SBase*)NULL));
          pFun->setSBMLId(funName);
        }
    }
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  while (pChild != NULL)
    {
      this->setFunctionSBMLIds(pChild, dataModel);
      pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
    }
}
