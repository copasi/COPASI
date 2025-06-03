// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <cmath>

#define USE_LAYOUT 1

#include "CSBMLExporter.h"
#include "SBMLUtils.h"

#include "SBMLImporter.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/CUnit.h"
#include "sbml/SBMLDocument.h"
#include "sbml/Compartment.h"
#include "sbml/LocalParameter.h"

#include <sbml/packages/layout/extension/LayoutModelPlugin.h>
#include <sbml/packages/layout/extension/LayoutExtension.h>
#include <sbml/conversion/ConversionProperties.h>

#include "copasi/layout/CLDefaultStyles.h"
#include <sbml/packages/render/extension/RenderExtension.h>
#include <sbml/packages/render/extension/RenderListOfLayoutsPlugin.h>
#include <sbml/packages/render/sbml/GlobalRenderInformation.h>

#define INIT_DEFAULTS(element) \
  {\
    element.initDefaults();\
  }

#include "sbml/Model.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/Reaction.h"
#include "sbml/KineticLaw.h"
#include "sbml/SBMLWriter.h"
#include "sbml/SpeciesReference.h"
#include "sbml/math/ASTNode.h"
#include "sbml/annotation/ModelHistory.h"
#include "sbml/annotation/CVTerm.h"
#include "sbml/SBMLErrorLog.h"
#include "sbml/SBMLError.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "SBMLIncompatibility.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CEvent.h"
#include "copasi/model/CMetab.h"
#include "copasi/function/CExpression.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/model/CAnnotation.h"
#include "copasi/model/CReaction.h"
#include "copasi/utilities/CCopasiParameter.h"
#include "copasi/model/CModelValue.h"
#include "copasi/function/CFunction.h"
#include "copasi/report/CKeyFactory.h"
#include "ConverterASTNode.h"
#include "copasi/utilities/CCopasiTree.h"
#include "copasi/model/CChemEqElement.h"
#include "copasi/utilities/CVersion.h"
#include "sbml/Trigger.h"
#include "sbml/Event.h"
#include "sbml/EventAssignment.h"
#include <sbml/xml/XMLInputStream.h>
#include "copasi/compareExpressions/compare_utilities.h"
#include "copasi/MIRIAM/CRDFUtilities.h"
#include "copasi/MIRIAM/CModelMIRIAMInfo.h"
#include "copasi/MIRIAM/CReference.h"
#include "copasi/MIRIAM/CBiologicalDescription.h"
#include "copasi/MIRIAM/CConstants.h"
#include "copasi/MIRIAM/CCreator.h"
#include "copasi/MIRIAM/CModified.h"
#include "copasi/MIRIAM/CRDFPredicate.h"
#include "copasi/MIRIAM/CRDFParser.h"
#include "copasi/layout/CListOfLayouts.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/utilities/CVersion.h"
#include "copasi/commandline/CLocaleString.h"

// helper functions for function definitions

std::string hasFunctionDefinitionForURI(SBMLDocument* pSBMLDocument,
                                        const std::string& sNamespace,
                                        const std::string& elementName,
                                        const std::string& definition)
{
  if (pSBMLDocument == NULL || pSBMLDocument->getModel() == NULL) return "";

  for (unsigned int i = 0; i < pSBMLDocument->getModel()->getNumFunctionDefinitions(); ++i)
    {
      FunctionDefinition* current = pSBMLDocument->getModel()->getFunctionDefinition(i);

      if (current == NULL) continue;

      if (!current->isSetAnnotation()) continue;

      const XMLNode* element = current->getAnnotation();

      if (element == NULL) continue;

      for (unsigned int j = 0 ; j < element->getNumChildren(); ++j)
        {
          const XMLNode& annot = element->getChild(j);

          if (annot.getURI() == sNamespace &&
              annot.getName() == elementName &&
              annot.getAttrValue("definition") == definition)
            {
              return current->getId();
            }
        }
    }

  return "";
}

std::string createFunctionDefinitonForURI(SBMLDocument* pSBMLDocument,
    std::map<std::string, const SBase*>& idMap,
    const char* id,
    const std::string& sNamespace,
    const std::string& elementName,
    const std::string& definition,
    const std::string& lambda)
{
  if (pSBMLDocument == NULL || pSBMLDocument->getModel() == NULL) return id;

  std::string newId = CSBMLExporter::createUniqueId(idMap, id, false);

  FunctionDefinition *def = pSBMLDocument->getModel()->createFunctionDefinition();
  def -> setId(newId);
  def -> setMath(SBML_parseFormula(lambda.c_str()));

  std::stringstream annotation;
  std::string annotElement = pSBMLDocument->getLevel() == 1 ? "annotations" : "annotation";
  annotation << "<" << annotElement << "> <" << elementName
             << " xmlns='" << sNamespace
             << "' definition='" << definition
             << "' /> </" << annotElement << ">";

  def->setAnnotation(annotation.str());

  return newId;
}

std::string addRateOfIfItDoesNotExist(SBMLDocument* pSBMLDocument,
                                      std::map<std::string, const SBase*>& idMap,
                                      const char* id)
{
  // don't add for l3v2
  if (!pSBMLDocument || (pSBMLDocument->getLevel() == 3 && pSBMLDocument->getVersion() > 1))
    return "";

  std::string newId = hasFunctionDefinitionForURI(pSBMLDocument,
                      "http://sbml.org/annotations/symbols",
                      "symbols",
                      "http://en.wikipedia.org/wiki/Derivative");

  if (!newId.empty()) return newId;

  newId = createFunctionDefinitonForURI(
            pSBMLDocument,
            idMap,
            id,
            "http://sbml.org/annotations/symbols",
            "symbols",
            "http://en.wikipedia.org/wiki/Derivative",
            "lambda(a,NaN)"
          );
  return newId;
}

std::string getUserDefinedFuctionForName(SBMLDocument* pSBMLDocument,
    std::map<std::string, const SBase*>& idMap,
    const char* id)
{
  std::string newId;

  if (id == std::string("RNORMAL"))
    {
      newId = hasFunctionDefinitionForURI(pSBMLDocument,
                                          "http://sbml.org/annotations/distribution",
                                          "distribution",
                                          "http://www.uncertml.org/distributions/normal");

      if (!newId.empty()) return newId;

      newId = createFunctionDefinitonForURI(
                pSBMLDocument,
                idMap,
                id,
                "http://sbml.org/annotations/distribution",
                "distribution",
                "http://www.uncertml.org/distributions/normal",
                "lambda(m,s,m)"
              );
      return newId;
    }

  if (id == std::string("RUNIFORM"))
    {
      newId = hasFunctionDefinitionForURI(pSBMLDocument,
                                          "http://sbml.org/annotations/distribution",
                                          "distribution",
                                          "http://www.uncertml.org/distributions/uniform");

      if (!newId.empty()) return newId;

      newId = createFunctionDefinitonForURI(
                pSBMLDocument,
                idMap,
                id,
                "http://sbml.org/annotations/distribution",
                "distribution",
                "http://www.uncertml.org/distributions/uniform",
                "lambda(a,b,(a+b)/2)"
              );
      return newId;
    }

  if (id == std::string("RGAMMA"))
    {
      newId = hasFunctionDefinitionForURI(pSBMLDocument,
                                          "http://sbml.org/annotations/distribution",
                                          "distribution",
                                          "http://www.uncertml.org/distributions/gamma");

      if (!newId.empty()) return newId;

      newId = createFunctionDefinitonForURI(
                pSBMLDocument,
                idMap,
                id,
                "http://sbml.org/annotations/distribution",
                "distribution",
                "http://www.uncertml.org/distributions/gamma",
                "lambda(a,b,a*b)"
              );
      return newId;
    }

  if (id == std::string("RPOISSON"))
    {
      newId = hasFunctionDefinitionForURI(pSBMLDocument,
                                          "http://sbml.org/annotations/distribution",
                                          "distribution",
                                          "http://www.uncertml.org/distributions/poisson");

      if (!newId.empty()) return newId;

      newId = createFunctionDefinitonForURI(
                pSBMLDocument,
                idMap,
                id,
                "http://sbml.org/annotations/distribution",
                "distribution",
                "http://www.uncertml.org/distributions/poisson",
                "lambda(mu,mu)"
              );
      return newId;
    }

  if (id == std::string("MAX"))
    {
      newId = hasFunctionDefinitionForURI(pSBMLDocument,
                                          "http://sbml.org/annotations/function",
                                          "function",
                                          "http://sbml.org/annotations/function/max");

      if (!newId.empty()) return newId;

      newId = createFunctionDefinitonForURI(
                pSBMLDocument,
                idMap,
                id,
                "http://sbml.org/annotations/function",
                "function",
                "http://sbml.org/annotations/function/max",
                "lambda(a,b,piecewise(a,geq(a,b),b))"
              );
      return newId;
    }

  if (id == std::string("MIN"))
    {
      newId = hasFunctionDefinitionForURI(pSBMLDocument,
                                          "http://sbml.org/annotations/function",
                                          "function",
                                          "http://sbml.org/annotations/function/min");

      if (!newId.empty()) return newId;

      newId = createFunctionDefinitonForURI(
                pSBMLDocument,
                idMap,
                id,
                "http://sbml.org/annotations/function",
                "function",
                "http://sbml.org/annotations/function/min",
                "lambda(a,b,piecewise(a,leq(a,b),b))"
              );
      return newId;
    }

  if (id == std::string("rateOf"))
    {
      return addRateOfIfItDoesNotExist(pSBMLDocument, idMap, id);
    }

  return id;
}

void
CSBMLExporter::setHandler(CProcessReport * pProcessReport)
{
  mpProcessReport = pProcessReport;
}

const CProcessReport * CSBMLExporter::getCallBack() const
{
  return mpProcessReport;
}

void CSBMLExporter::clearCallBack()
{
  setHandler(NULL);
}

bool
CSBMLExporter::reportCurrentProgressOrStop()
{
  if (mpProcessReport == NULL) return false;

  return !mpProcessReport->progressItem(mCurrentStepHandle);
}

void
CSBMLExporter::finishCurrentStep()
{
  if (mpProcessReport == NULL || mCurrentStepHandle == C_INVALID_INDEX)  return;

  mpProcessReport->finishItem(mCurrentStepHandle);
  mCurrentStepHandle = C_INVALID_INDEX;
}

void
CSBMLExporter::finishExport()
{
  if (mpProcessReport == NULL)  return;

  finishCurrentStep();

  mpProcessReport->finishItem(mGlobalStepHandle);
}

bool
CSBMLExporter::createProgressStepOrStop(unsigned C_INT32 globalStep,
                                        unsigned C_INT32 currentTotal,
                                        const std::string& title)
{
  if (mpProcessReport == NULL) return false;

  if (mCurrentStepHandle != C_INVALID_INDEX)
    mpProcessReport->finishItem(mCurrentStepHandle);

  mGlobalStepCounter = globalStep;

  if (!mpProcessReport->progressItem(mGlobalStepHandle)) return true;

  mCurrentStepCounter = 0;
  mCurrentStepTotal = currentTotal;
  mCurrentStepHandle = mpProcessReport->addItem(title,
                       mCurrentStepCounter,
                       &mCurrentStepTotal);

  return false;
}

CSBMLExporter::CSBMLExporter()
  : mpSBMLDocument(NULL)
  , mSBMLLevel(2)
  , mSBMLVersion(4)
  , mIncompleteExport(false)
  , mVariableVolumes(false)
  , mpAvogadro(NULL)
  , mAvogadroCreated(false)
  , mMIRIAMWarning(false)
  , mDocumentDisowned(false)
  , mExportCOPASIMIRIAM(false)
  , mExportedFunctions(2, 1)
  , mpProcessReport(NULL)
  , mGlobalStepHandle(C_INVALID_INDEX)
  , mGlobalStepCounter(0)
  , mGlobalStepTotal(0)
  , mCurrentStepHandle(C_INVALID_INDEX)
  , mCurrentStepCounter(0)
  , mCurrentStepTotal(0)
{
}

CSBMLExporter::~CSBMLExporter()
{
  if (this->mDocumentDisowned == false)
    {
      pdelete(mpSBMLDocument);
    }
}

SBMLDocument *
CSBMLExporter::getSBMLDocument()
{
  return this->mpSBMLDocument;
}

/**
 * Creates the units for the SBML model.
 */
void CSBMLExporter::createUnits(const CDataModel& dataModel)
{
  createLengthUnit(dataModel);
  createAreaUnit(dataModel);
  createVolumeUnit(dataModel);
  createTimeUnit(dataModel);
  createSubstanceUnit(dataModel);
}

/**
 * Creates the time unit for the SBML model.
 */
void CSBMLExporter::createTimeUnit(const CDataModel& dataModel)
{
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL) return;

  Model * pSBMLModel = this->mpSBMLDocument->getModel();
  UnitDefinition * uDef = pSBMLModel->removeUnitDefinition("time");

  // drop existing unit
  pdelete(uDef);

  // create new one
  uDef = createUnitDefinitionFor(CUnit(dataModel.getModel()->getTimeUnit()));
  uDef->setId("time");
  uDef->setName("time");

  // set it
  pSBMLModel->setTimeUnits(uDef->getId());
}

/**
 * Creates the volume unit for the SBML model.
 */
void CSBMLExporter::createVolumeUnit(const CDataModel& dataModel)
{
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL) return;

  Model * pSBMLModel = this->mpSBMLDocument->getModel();
  UnitDefinition * uDef = pSBMLModel->removeUnitDefinition("volume");

  // drop existing volume unit
  pdelete(uDef);

  // create new one
  uDef = createUnitDefinitionFor(CUnit(dataModel.getModel()->getVolumeUnit()));
  uDef->setId("volume");
  uDef->setName("volume");

  // set it
  pSBMLModel->setVolumeUnits(uDef->getId());
}

/**
 * Creates the substance unit for the SBML model.
 */
void CSBMLExporter::createSubstanceUnit(const CDataModel& dataModel)
{
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL) return;

  Model * pSBMLModel = this->mpSBMLDocument->getModel();
  UnitDefinition * uDef = pSBMLModel->removeUnitDefinition("substance");

  // drop existing unit
  pdelete(uDef);

  // create new one
  uDef = createUnitDefinitionFor(CUnit(dataModel.getModel()->getQuantityUnit()));
  uDef->setId("substance");
  uDef->setName("substance");

  // set it
  pSBMLModel->setSubstanceUnits(uDef->getId());

  // here we also set the extent unit to the same unit as the substance unit
  // because COPASI does not know about different extent units
  if (this->mSBMLLevel > 2)
    pSBMLModel->setExtentUnits(uDef->getId());
}

/**
 * Creates the length unit for the SBML model.
 */
void CSBMLExporter::createLengthUnit(const CDataModel& dataModel)
{
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL) return;

  Model * pSBMLModel = this->mpSBMLDocument->getModel();
  UnitDefinition * uDef = pSBMLModel->removeUnitDefinition("length");

  // drop existing unit
  pdelete(uDef);

  // create new one
  uDef = createUnitDefinitionFor(CUnit(dataModel.getModel()->getLengthUnit()));
  uDef->setId("length");
  uDef->setName("length");

  // set it
  pSBMLModel->setLengthUnits(uDef->getId());
}

/**
 * Creates the area unit for the SBML model.
 */
void CSBMLExporter::createAreaUnit(const CDataModel& dataModel)
{
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL) return;

  Model * pSBMLModel = this->mpSBMLDocument->getModel();
  UnitDefinition * uDef = pSBMLModel->removeUnitDefinition("area");

  // drop existing unit
  pdelete(uDef);

  // create new one
  uDef = createUnitDefinitionFor(CUnit(dataModel.getModel()->getAreaUnit()));
  uDef->setId("area");
  uDef->setName("area");

  // set it
  pSBMLModel->setAreaUnits(uDef->getId());
}

/**
 * Creates the compartments for the model.
 */
bool CSBMLExporter::createCompartments(CDataModel& dataModel)
{
  // make sure the SBML Document already exists and that it has a Model set
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL)
    return false;

  CDataVectorNS<CCompartment>::const_iterator it = dataModel.getModel()->getCompartments().begin(), endit = dataModel.getModel()->getCompartments().end();

  while (it != endit)
    {
      createCompartment(*it);
      ++it;

      ++mCurrentStepCounter;

      if (reportCurrentProgressOrStop())
        return false;
    }

  return true;
}

/**
 * Creates the compartment for the given COPASI compartment.
 */
void CSBMLExporter::createCompartment(const CCompartment& compartment)
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
      sbmlId = CSBMLExporter::createUniqueId(this->mIdMap, compartment.getObjectName(), false);
      compartment.setSBMLId(sbmlId);
      pSBMLCompartment->setId(sbmlId);
    }

  INIT_DEFAULTS((*pSBMLCompartment));

  this->mIdMap.insert(std::pair<const std::string, const SBase*>(sbmlId, pSBMLCompartment));
  this->mHandledSBMLObjects.insert(pSBMLCompartment);

  // don't call setName on level 1 objects because this will also
  // change the id
  if (this->mpSBMLDocument->getLevel() > 1)
    {
      pSBMLCompartment->setName(compartment.getObjectName());
    }

  pSBMLCompartment->setSpatialDimensions((unsigned int)compartment.getDimensionality());
  double value = compartment.getInitialValue();

  // if the value is NaN, unset the initial volume
  if (!std::isnan(value))
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

  if (status == CModelEntity::Status::ASSIGNMENT)
    {

      this->mAssignmentVector.push_back(&compartment);
      pSBMLCompartment->setConstant(false);
      removeInitialAssignment(pSBMLCompartment->getId());
    }
  else if (status == CModelEntity::Status::ODE)
    {
      this->mODEVector.push_back(&compartment);
      pSBMLCompartment->setConstant(false);

      if (!compartment.getInitialExpression().empty())
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
      // do this explicitly since we might handle an existing object from an
      // earlier import that had it attribute set already
      if (this->mSBMLLevel != 1)
        {
          pSBMLCompartment->setConstant(true);
        }
      else
        {
          // Level 1 does not know the constant flag and libsbml does not drop
          // it automatically
          pSBMLCompartment->setConstant(false);
        }

      removeRule(pSBMLCompartment->getId());

      // fill initial assignment set
      if (!compartment.getInitialExpression().empty())
        {
          this->mInitialAssignmentVector.push_back(&compartment);
        }
      else
        {
          removeInitialAssignment(pSBMLCompartment->getId());
        }
    }

  if (pSBMLCompartment != NULL)
    {
      CSBMLExporter::setSBMLNotes(pSBMLCompartment, &compartment);
    }

  if (pSBMLCompartment != NULL && mSBMLLevel == 3)
    {
      pSBMLCompartment->setUnits("volume");
    }

  CSBMLExporter::updateMIRIAMAnnotation(&compartment, pSBMLCompartment, this->mMetaIdMap);
}

/**
 * Creates the compartments for the model.
 */
bool
CSBMLExporter::createMetabolites(CDataModel& dataModel)
{
  // make sure the SBML Document already exists and that it has a Model set
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL)
    return false;

  if (this->mSBMLLevel > 2 || (this->mSBMLLevel == 2 && this->mSBMLVersion >= 3))
    {
      SBMLUnitSupport::checkForSpatialSizeUnits(dataModel, this->mIncompatibilities);
    }

  CDataVector<CMetab>::const_iterator it = dataModel.getModel()->getMetabolites().begin(), endit = dataModel.getModel()->getMetabolites().end();
  this->mSpatialSizeUnitsSpecies.clear();

  while (it != endit)
    {
      createMetabolite(*it);
      ++it;

      ++mCurrentStepCounter;

      if (reportCurrentProgressOrStop())
        return false;
    }

  if (!this->mSpatialSizeUnitsSpecies.empty())
    {
      std::ostringstream os;
      std::set<std::string>::const_iterator sit = this->mSpatialSizeUnitsSpecies.begin(), sendit = this->mSpatialSizeUnitsSpecies.end();

      while (sit != sendit)
        {
          os << *sit << ", ";
          ++sit;
        }

      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 84, os.str().substr(0, os.str().size() - 2).c_str());
    }

  return true;
}

/**
 * Creates the species for the given COPASI metabolite.
 */
void CSBMLExporter::createMetabolite(const CMetab& metab)
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
      else
        {
          if (this->mSBMLLevel > 2)
            {
              pSBMLSpecies->unsetConversionFactor();
              // we have to remove the conversionFactor because on import we multiplied the stoichiometries
              // with this factor
            }

          // clear the spatialSizeUnits attribute if there is any
          if (this->mSBMLLevel > 2 || (this->mSBMLLevel == 2 && this->mSBMLVersion >= 3))
            {
              if (pSBMLSpecies->isSetSpatialSizeUnits())
                {
                  pSBMLSpecies->unsetSpatialSizeUnits();
                  this->mSpatialSizeUnitsSpecies.insert(pSBMLSpecies->getId());
                }
            }
        }
    }
  else
    {
      pSBMLSpecies = this->mpSBMLDocument->getModel()->createSpecies();
      this->mCOPASI2SBMLMap[&metab] = pSBMLSpecies;
      sbmlId = CSBMLExporter::createUniqueId(this->mIdMap, metab.getObjectDisplayName(), false);
      metab.setSBMLId(sbmlId);
      pSBMLSpecies->setId(sbmlId);
    }

  INIT_DEFAULTS((*pSBMLSpecies));

  this->mIdMap.insert(std::pair<const std::string, const SBase*>(sbmlId, pSBMLSpecies));
  this->mHandledSBMLObjects.insert(pSBMLSpecies);

  // don't call setName on level 1 objects because this will also
  // change the id
  if (this->mpSBMLDocument->getLevel() > 1)
    {
      pSBMLSpecies->setName(metab.getObjectName());
    }

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
  if (!std::isnan(value))
    {
      // if we set the concentration on a species that had the amount
      // set, the meaning of the model is different when the user changed
      // to size of the corresponding compartment
      // So if the amount had been set, we try to keep this.
      // we also have to set the initial amount if the model has variable
      // volumes since those models export all species with the
      // hasOnlySubstanceUnits flag set to true
      //
      // libsbml 4 does not set the initial concentration on a species any more
      // so we also have to set the initial amount
      if (pSBMLSpecies->isSetInitialAmount() || this->mVariableVolumes == true || pSBMLSpecies->getLevel() == 1)
        {
          pSBMLSpecies->setInitialAmount(value * metab.getCompartment()->getInitialValue());
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
  if (status == CModelEntity::Status::ASSIGNMENT)
    {
      this->mAssignmentVector.push_back(&metab);
      pSBMLSpecies->setConstant(false);
      pSBMLSpecies->setBoundaryCondition(true);
      removeInitialAssignment(pSBMLSpecies->getId());
    }
  else if (status == CModelEntity::Status::ODE)
    {
      this->mODEVector.push_back(&metab);
      pSBMLSpecies->setConstant(false);
      pSBMLSpecies->setBoundaryCondition(true);

      if (!metab.getInitialExpression().empty())
        {
          this->mInitialAssignmentVector.push_back(&metab);
        }
      else
        {
          removeInitialAssignment(pSBMLSpecies->getId());
        }
    }
  else if (status == CModelEntity::Status::FIXED)
    {
      // do this explicitly since we might handle an existing object from an
      // earlier import that had it attribute set already
      if (this->mSBMLLevel != 1)
        {
          pSBMLSpecies->setConstant(true);
        }
      else
        {
          // Level 1 doesn't have the constant attribute and libSBML 3.2.0 does
          // not drop it automatically
          pSBMLSpecies->setConstant(false);
        }

      pSBMLSpecies->setBoundaryCondition(true);
      removeRule(pSBMLSpecies->getId());

      // fill initial assignment set
      if (!metab.getInitialExpression().empty())
        {
          this->mInitialAssignmentVector.push_back(&metab);
        }
      else
        {
          removeInitialAssignment(pSBMLSpecies->getId());
        }
    }
  else if (status == CModelEntity::Status::REACTIONS)
    {
      pSBMLSpecies->setConstant(false);
      pSBMLSpecies->setBoundaryCondition(false);

      if (!metab.getInitialExpression().empty())
        {
          this->mInitialAssignmentVector.push_back(&metab);
        }
    }

  if (pSBMLSpecies != NULL)
    {
      CSBMLExporter::setSBMLNotes(pSBMLSpecies, &metab);
    }

  if (pSBMLSpecies != NULL && mSBMLLevel == 3)
    {
      // for l3 the unit needs to be set explicitly to substance,
      pSBMLSpecies->setSubstanceUnits("substance");
    }

  CSBMLExporter::updateMIRIAMAnnotation(&metab, pSBMLSpecies, this->mMetaIdMap);
}

/**
 * Creates the parameters for the model.
 */
bool CSBMLExporter::createParameters(CDataModel& dataModel)
{
  // make sure the SBML Document already exists and that it has a Model set
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL)
    return false;

  CDataVectorN<CModelValue>::const_iterator it = dataModel.getModel()->getModelValues().begin(), endit = dataModel.getModel()->getModelValues().end();

  while (it != endit)
    {
      createParameter(*it);
      ++it;

      ++mCurrentStepCounter;

      if (reportCurrentProgressOrStop())
        return false;
    }

  return true;
}

/**
 * Creates the parameter for the given COPASI parameter.
 */
void CSBMLExporter::createParameter(const CModelValue& modelValue)
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
      sbmlId = CSBMLExporter::createUniqueId(this->mIdMap, modelValue.getObjectName(), false);
      modelValue.setSBMLId(sbmlId);
      pParameter->setId(sbmlId);
    }

  INIT_DEFAULTS((*pParameter));

  this->mIdMap.insert(std::pair<const std::string, const SBase*>(sbmlId, pParameter));
  this->mHandledSBMLObjects.insert(pParameter);

  // don't call setName on level 1 objects because this will also
  // change the id
  if (this->mpSBMLDocument->getLevel() > 1)
    {
      pParameter->setName(modelValue.getObjectName());
    }

  double value = modelValue.getInitialValue();

  // if the value is NaN, unset the parameters value
  if (!std::isnan(value))
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

  if (status == CModelEntity::Status::ASSIGNMENT)
    {
      this->mAssignmentVector.push_back(&modelValue);
      pParameter->setConstant(false);
      removeInitialAssignment(pParameter->getId());
    }
  else if (status == CModelEntity::Status::ODE)
    {
      this->mODEVector.push_back(&modelValue);
      pParameter->setConstant(false);

      if (!modelValue.getInitialExpression().empty())
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
      // do this explicitly since we might handle an existing object from an
      // earlier import that had it attribute set already
      if (this->mSBMLLevel != 1)
        {
          pParameter->setConstant(true);
        }
      else
        {
          // Level 1 does not have a constant flag
          // and libsbml does not drop it automatically
          pParameter->setConstant(false);
        }

      // fill initial assignment set
      removeRule(pParameter->getId());

      if (!modelValue.getInitialExpression().empty())
        {
          this->mInitialAssignmentVector.push_back(&modelValue);
        }
      else
        {
          removeInitialAssignment(pParameter->getId());
        }
    }

  if (!modelValue.getUnitExpression().empty())
    {
      exportAndAssignUnit(CUnit(modelValue.getUnitExpression()), pParameter);
    }

  if (pParameter != NULL)
    {
      CSBMLExporter::setSBMLNotes(pParameter, &modelValue);
    }

  CSBMLExporter::updateMIRIAMAnnotation(&modelValue, pParameter, this->mMetaIdMap);
}

/**
 * Creates the reactions for the model.
 */
bool CSBMLExporter::createReactions(CDataModel& dataModel)
{
  // make sure the SBML Document already exists and that it has a Model set
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL)
    return false;

  CDataVectorNS<CReaction>::const_iterator it = dataModel.getModel()->getReactions().begin(), endit = dataModel.getModel()->getReactions().end();

  while (it != endit)
    {
      createReaction(*it, dataModel);
      ++it;

      ++mCurrentStepCounter;

      if (reportCurrentProgressOrStop())
        return false;
    }

  return true;
}

/**
 * Creates the reaction for the given COPASI reaction.
 */
void CSBMLExporter::createReaction(const CReaction& reaction, CDataModel& dataModel)
{
  // make sure the mCOPASI2SBMLMap is already updated
  Reaction* pSBMLReaction = NULL;

  // if the reaction has nothing set but the name, we don't do anything
  // This is mandated since SBML Level 2 Version 2. A reactions has to have either
  // a substrate or a product.
  if (reaction.getChemEq().getSubstrates().empty() &&
      reaction.getChemEq().getProducts().empty()) return;

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

      // maybe this id was assigned by assignSBMLIdstoReactions and there is no object associated with it
      // If this is the case, we associate the object here.
      std::map<std::string, const SBase*>::const_iterator pos = this->mIdMap.find(sbmlId);

      if (pos == mIdMap.end() || pos->second == NULL)
        {
          mIdMap[sbmlId] = pSBMLReaction;
        }
    }
  else
    {
      pSBMLReaction = this->mpSBMLDocument->getModel()->createReaction();
      this->mCOPASI2SBMLMap[&reaction] = pSBMLReaction;
      sbmlId = CSBMLExporter::createUniqueId(this->mIdMap, reaction.getObjectName(), false);
      reaction.setSBMLId(sbmlId);
      pSBMLReaction->setId(sbmlId);
    }

  INIT_DEFAULTS((*pSBMLReaction));

  this->mIdMap.insert(std::pair<const std::string, const SBase*>(sbmlId, pSBMLReaction));
  this->mHandledSBMLObjects.insert(pSBMLReaction);

  // don't call setName on level 1 objects because this will also
  // change the id
  if (this->mpSBMLDocument->getLevel() > 1)
    {
      pSBMLReaction->setName(reaction.getObjectName());
    }

  pSBMLReaction->setReversible(reaction.isReversible());
  const CChemEq& chemicalEquation = reaction.getChemEq();
  /* Add all substrates */
  unsigned int counter;
  std::set<std::string> usedReferences;

  for (counter = 0; counter < chemicalEquation.getSubstrates().size(); counter++)
    {
      const CChemEqElement* element = &chemicalEquation.getSubstrates()[counter];
      const CMetab* pMetabolite = element->getMetabolite();
      assert(pMetabolite);
      SpeciesReference* sRef = NULL;

      if (!(sRef = pSBMLReaction->getReactant(pMetabolite->getSBMLId())))
        {
          sRef = pSBMLReaction->createReactant();
          sRef->setSpecies(pMetabolite->getSBMLId());
        }

      INIT_DEFAULTS((*sRef));

      if (this->mSBMLLevel > 2)
        sRef->setConstant(true);

      sRef->setStoichiometry(element->getMultiplicity());
      sRef->setDenominator(1);
      usedReferences.insert(sRef->getSpecies());
    }

  ListOf* l = pSBMLReaction->getListOfReactants();

  for (counter = l->size(); counter > 0; --counter)
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
      const CChemEqElement* element = &chemicalEquation.getProducts()[counter];
      const CMetab* pMetabolite = element->getMetabolite();
      assert(pMetabolite);
      SpeciesReference* sRef = NULL;

      if (!(sRef = pSBMLReaction->getProduct(pMetabolite->getSBMLId())))
        {
          sRef = pSBMLReaction->createProduct();
          sRef->setSpecies(pMetabolite->getSBMLId());
        }

      INIT_DEFAULTS((*sRef));

      if (this->mSBMLLevel > 2)
        sRef->setConstant(true);

      sRef->setStoichiometry(element->getMultiplicity());
      sRef->setDenominator(1);
      usedReferences.insert(sRef->getSpecies());
    }

  l = pSBMLReaction->getListOfProducts();

  for (counter = l->size(); counter > 0; --counter)
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
      const CChemEqElement* element = &chemicalEquation.getModifiers()[counter];
      const CMetab* pMetabolite = element->getMetabolite(); assert(pMetabolite);
      ModifierSpeciesReference* sRef = NULL;

      if (!(sRef = pSBMLReaction->getModifier(pMetabolite->getSBMLId())))
        {
          if (pSBMLReaction->getLevel() > 1)
            {
              sRef = pSBMLReaction->createModifier();
              assert(sRef != NULL);
              sRef->setSpecies(pMetabolite->getSBMLId());
            }
        }

      if (pSBMLReaction->getLevel() > 1)
        {
          usedReferences.insert(sRef->getSpecies());
        }
    }

  l = pSBMLReaction->getListOfModifiers();

  for (counter = l->size(); counter > 0; --counter)
    {
      if (usedReferences.find(static_cast<SimpleSpeciesReference*>(l->get(counter - 1))->getSpecies()) == usedReferences.end())
        {
          l->remove(counter - 1);
        }
    }

  /* create the kinetic law */

  /* if there is one on COPASI */
  if ((reaction.getFunction()) != CRootContainer::getUndefinedFunction())
    {
      // make sure the creaated kinetic law has the same level and version as the reaction
      // we intend to add it to, otherwise the setKineticLaw function of libsbml 4 will fail
      // to set the kinetic law
      KineticLaw* pKineticLaw = this->createKineticLaw(reaction, dataModel, pSBMLReaction->getLevel(), pSBMLReaction->getVersion());

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
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 8, reaction.getObjectName().c_str());
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

  if (pSBMLReaction != NULL)
    {
      CSBMLExporter::setSBMLNotes(pSBMLReaction, &reaction);
    }

  CSBMLExporter::updateMIRIAMAnnotation(&reaction, pSBMLReaction, this->mMetaIdMap);
}

/**
 * Creates the initial assignments for the model.
 */
bool CSBMLExporter::createInitialAssignments(CDataModel& dataModel)
{
  // make sure the mInitialAssignmentVector has been filled already

  // create the initial assignments
  size_t i, iMax = this->mInitialAssignmentVector.size();
  const CModelEntity* pME = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pME = mInitialAssignmentVector[i];
      assert(pME != NULL);

      if (pME != NULL)
        {
          createInitialAssignment(*pME, dataModel);

          if (reportCurrentProgressOrStop())
            return false;
        }
    }

  return true;
}

/**
 * Creates the initial assignment for the given COPASI model entity.
 */
void CSBMLExporter::createInitialAssignment(const CModelEntity& modelEntity, CDataModel& dataModel)
{
  // check the expression
  std::vector<SBMLIncompatibility> result;
  isExpressionSBMLCompatible(*modelEntity.getInitialExpressionPtr()
                             , dataModel
                             , this->mSBMLLevel
                             , this->mSBMLVersion
                             , result
                             , mIdMap
                             , std::string("initial expression for object named \"" + modelEntity.getObjectName() + "\"")
                             , true
                             , &mInitialValueMap);

  // collect directly used functions
  if (result.empty())
    {
      std::set<std::string> directlyUsedFunctionNames;
      CSBMLExporter::findDirectlyUsedFunctions(modelEntity.getInitialExpressionPtr()->getRoot(), directlyUsedFunctionNames);
      std::set<CFunction*> usedFunctions = CSBMLExporter::createFunctionSetFromFunctionNames(directlyUsedFunctionNames, CRootContainer::getFunctionList());

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

      if (pOrigNode->mainType() == CEvaluationNode::MainType::INVALID)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 70, "initial assignment", modelEntity.getObjectType().c_str(), modelEntity.getObjectName().c_str());
        }

      // the next few lines replace references to species depending on whether
      // it is a reference to an amount or a reference to a concentration.
      // Other factors that influence this replacement are if the model
      // contains variable volumes or if the quantity units are set to CUnit::number
      pOrigNode = this->replaceSpeciesReferences(pOrigNode, dataModel);
      assert(pOrigNode != NULL);

      // check if the rule is for an amount species
      // if this is the case, we have to multiply the expression by the volume
      // of the compartment the species is in
      // create the actual rule
      const CMetab* pMetab = dynamic_cast<const CMetab*>(&modelEntity);

      if (pMetab != NULL)
        {
          std::map<const CDataObject*, SBase*>::const_iterator pos = this->mCOPASI2SBMLMap.find(&modelEntity);
          assert(pos != this->mCOPASI2SBMLMap.end());

          if (dynamic_cast<const Species*>(pos->second)->getHasOnlySubstanceUnits() == true)
            {
              const CCompartment* pCompartment = pMetab->getCompartment();

              CEvaluationNode* pNode = CSBMLExporter::multiplyByObject(pOrigNode, pCompartment->getInitialValueReference());
              assert(pNode != NULL);

              if (pNode != NULL)
                {
                  delete pOrigNode;
                  pOrigNode = pNode;
                }
            }
        }

      ASTNode* pNode = this->convertToASTNode(pOrigNode, dataModel);
      delete pOrigNode;
      // convert local parameters that are referenced in an expression to global
      // parameters
      this->replace_local_parameters(pNode, dataModel);

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
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 60, "initial assignment", modelEntity.getObjectType().c_str(), modelEntity.getObjectName().c_str());
            }
        }
    }
  else
    {
      this->mIncompatibilities.insert(this->mIncompatibilities.end(), result.begin(), result.end());

      if (!this->mIncompleteExport)
        {
          this->outputIncompatibilities();
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 60, "initial assignment", modelEntity.getObjectType().c_str(), modelEntity.getObjectName().c_str());
        }
    }
}

/*
 * This function replaces all references to initial values, volumes and concentrations with the
 * name of the global parameter that will be created.
 */
std::string convertExpression(const std::string& expression, const std::map<const std::string, Parameter*>& initialValueMap)
{
  if (initialValueMap.empty())
    return expression;

  std::string result = expression;
  std::map<const std::string, Parameter*>::const_iterator it;

  for (it = initialValueMap.begin(); it != initialValueMap.end(); ++it)
    {
      size_t length = it->first.length();
      size_t start;

      while ((start = result.find(it->first)) != std::string::npos)
        {
          result.replace(start, length, it->second->getId());
        }
    }

  return result;
}

/**
 * Creates the rules for the model.
 */
bool CSBMLExporter::createRules(CDataModel& dataModel)
{
  // make sure the mAssignmentVector has been filled already
  // make sure the mODEVector has been filled already
  // order the rules for Level 1 export
  // rules in Level 2 are not ordered.
  //if (this->mSBMLLevel == 1 || (this->mSBMLLevel == 2 && this->mSBMLVersion == 1))
  //  {
  std::vector<const CModelEntity*> orderedAssignmentRules = orderRules(dataModel);
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

  if (reportCurrentProgressOrStop())
    return false;

  // create the rules
  const CModelEntity* pME = NULL;
  size_t i, iMax = orderedAssignmentRules.size();

  for (i = 0; i < iMax; ++i)
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

  if (reportCurrentProgressOrStop())
    return false;

  iMax = mODEVector.size();

  for (i = 0; i < iMax; ++i)
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

  if (reportCurrentProgressOrStop())
    return false;

  // delete the remaining rules
  std::map<std::string, Rule*>::iterator mapIt = ruleMap.begin(), mapEndit = ruleMap.end();

  while (mapIt != mapEndit)
    {
      delete mapIt->second;
      ++mapIt;
    }

  ruleMap.clear();
  return true;
}

/**
 * Creates the rule for the given COPASI model entity.
 */
void CSBMLExporter::createRule(const CModelEntity& modelEntity, CDataModel& dataModel, Rule* pOldRule)
{
  // check the expression
  std::vector<SBMLIncompatibility> result;
  CSBMLExporter::isExpressionSBMLCompatible(*modelEntity.getExpressionPtr()
      , dataModel
      , this->mSBMLLevel
      , this->mSBMLVersion
      , result
      , mIdMap
      , std::string("rule for object named \"" + modelEntity.getObjectName() + "\"")
      , false
      , &mInitialValueMap);

  // collect directly used functions
  if (result.empty())
    {
      std::set<std::string> directlyUsedFunctionNames;
      CSBMLExporter::findDirectlyUsedFunctions(modelEntity.getExpressionPtr()->getRoot(), directlyUsedFunctionNames);
      std::set<CFunction*> usedFunctions = CSBMLExporter::createFunctionSetFromFunctionNames(directlyUsedFunctionNames, CRootContainer::getFunctionList());

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
      const CMetab* pMetab = dynamic_cast<const CMetab*>(&modelEntity);

      if (pOldRule == NULL)
        {
          if (modelEntity.getStatus() == CModelEntity::Status::ASSIGNMENT)
            {
              pOldRule = this->mpSBMLDocument->getModel()->createAssignmentRule();
            }
          else
            {
              if (pMetab != NULL)
                {
                  // check if the compartment is fixed
                  if (pMetab->getCompartment()->getStatus() != CModelEntity::Status::FIXED)
                    {
                      CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 52, pMetab->getObjectName().c_str());
                    }
                }

              pOldRule = this->mpSBMLDocument->getModel()->createRateRule();
            }

          pOldRule->setVariable(modelEntity.getSBMLId());
        }
      else
        {
          // Read the rule to the model
          this->mpSBMLDocument->getModel()->getListOfRules()->appendAndOwn(pOldRule);
        }

      // set the math

      const std::string& changedExpression = convertExpression(modelEntity.getExpression(), mInitialValueMap);
      CEvaluationTree tree;
      tree.setInfix(changedExpression);
      const CEvaluationNode* pOrigNode = tree.getRoot();

      if (pOrigNode == NULL || pOrigNode->mainType() == CEvaluationNode::MainType::INVALID)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 70, "assignment", modelEntity.getObjectType().c_str(), modelEntity.getObjectName().c_str());
          return;
        }

      // the next few lines replace references to species depending on whether
      // it is a reference to an amount or a reference to a concentration.
      // Other factors that influence this replacement are if the model
      // contains variable volumes or if the quantity units are set to CUnit::number
      pOrigNode = this->replaceSpeciesReferences(pOrigNode, dataModel);
      assert(pOrigNode != NULL);

      // check if the rule is for an amount species
      // if this is the case, we have to multiply the expression by the volume
      // of the compartment the species is in
      if (pMetab != NULL)
        {
          std::map<const CDataObject*, SBase*>::const_iterator pos = this->mCOPASI2SBMLMap.find(&modelEntity);
          assert(pos != this->mCOPASI2SBMLMap.end());

          if (dynamic_cast<const Species*>(pos->second)->getHasOnlySubstanceUnits() == true)
            {
              const CCompartment* pCompartment = pMetab->getCompartment();

              CEvaluationNode* pNode = CSBMLExporter::multiplyByObject(pOrigNode, pCompartment->getValueReference());
              assert(pNode != NULL);

              if (pNode != NULL)
                {
                  delete pOrigNode;
                  pOrigNode = pNode;
                }
            }
        }

      ASTNode* pNode = this->convertToASTNode(pOrigNode, dataModel);
      this->replace_local_parameters(pNode, dataModel);
      delete pOrigNode;

      if (pNode != NULL)
        {
          pOldRule->setMath(pNode);
          delete pNode;
        }
      else
        {
          if (this->mIncompleteExport != true)
            {
              CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 60, "rule", modelEntity.getObjectType().c_str(), modelEntity.getObjectName().c_str());
              return;
            }
        }
    }
  else
    {
      this->mIncompatibilities.insert(this->mIncompatibilities.end(), result.begin(), result.end());

      if (!this->mIncompleteExport)
        {
          this->outputIncompatibilities();
          CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 60, "rule", modelEntity.getObjectType().c_str(), modelEntity.getObjectName().c_str());
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
      idMap.insert(std::pair<const std::string, const SBase*>(sbmlModel.getId(), &sbmlModel));
    }

  if (sbmlModel.getListOfFunctionDefinitions()->isSetId())
    {
      idMap.insert(std::pair<const std::string, const SBase*>(sbmlModel.getListOfFunctionDefinitions()->getId(), sbmlModel.getListOfFunctionDefinitions()));
    }

  iMax = sbmlModel.getNumFunctionDefinitions();

  for (i = 0; i < iMax; ++i)
    {
      idMap.insert(std::pair<const std::string, const SBase*>(sbmlModel.getFunctionDefinition(i)->getId(), sbmlModel.getFunctionDefinition(i)));
    }

  if (sbmlModel.getListOfCompartments()->isSetId())
    {
      idMap.insert(std::pair<const std::string, const SBase*>(sbmlModel.getListOfCompartments()->getId(), sbmlModel.getListOfCompartments()));
    }

  iMax = sbmlModel.getNumCompartments();

  for (i = 0; i < iMax; ++i)
    {
      idMap.insert(std::pair<const std::string, const SBase*>(sbmlModel.getCompartment(i)->getId(), sbmlModel.getCompartment(i)));
    }

  if (sbmlModel.getListOfSpecies()->isSetId())
    {
      idMap.insert(std::pair<const std::string, const SBase*>(sbmlModel.getListOfSpecies()->getId(), sbmlModel.getListOfSpecies()));
    }

  iMax = sbmlModel.getNumSpecies();

  for (i = 0; i < iMax; ++i)
    {
      idMap.insert(std::pair<const std::string, const SBase*>(sbmlModel.getSpecies(i)->getId(), sbmlModel.getSpecies(i)));
    }

  if (sbmlModel.getListOfParameters()->isSetId())
    {
      idMap.insert(std::pair<const std::string, const SBase*>(sbmlModel.getListOfParameters()->getId(), sbmlModel.getListOfParameters()));
    }

  iMax = sbmlModel.getNumParameters();

  for (i = 0; i < iMax; ++i)
    {
      idMap.insert(std::pair<const std::string, const SBase*>(sbmlModel.getParameter(i)->getId(), sbmlModel.getParameter(i)));
    }

  if (sbmlModel.getListOfReactions()->isSetId())
    {
      idMap.insert(std::pair<const std::string, const SBase*>(sbmlModel.getListOfReactions()->getId(), sbmlModel.getListOfReactions()));
    }

  iMax = sbmlModel.getNumReactions();

  for (i = 0; i < iMax; ++i)
    {
      const Reaction* pReaction = sbmlModel.getReaction(i);

      if (pReaction != NULL)
        {
          idMap.insert(std::pair<const std::string, const SBase*>(pReaction->getId(), pReaction));

          if (pReaction->getListOfReactants()->isSetId())
            {
              idMap.insert(std::pair<const std::string, const SBase*>(pReaction->getListOfReactants()->getId(), pReaction->getListOfReactants()));
            }

          unsigned int j, jMax = pReaction->getNumReactants();
          const SpeciesReference* pSRef = NULL;

          for (j = 0; j < jMax; ++j)
            {
              pSRef = pReaction->getReactant(j);

              if (pSRef->isSetId())
                {
                  idMap.insert(std::pair<const std::string, const SBase*>(pSRef->getId(), pSRef));
                }
            }

          if (pReaction->getListOfProducts()->isSetId())
            {
              idMap.insert(std::pair<const std::string, const SBase*>(pReaction->getListOfProducts()->getId(), pReaction->getListOfProducts()));
            }

          jMax = pReaction->getNumProducts();

          for (j = 0; j < jMax; ++j)
            {
              pSRef = pReaction->getProduct(j);

              if (pSRef->isSetId())
                {
                  idMap.insert(std::pair<const std::string, const SBase*>(pSRef->getId(), pSRef));
                }
            }

          if (pReaction->getListOfModifiers()->isSetId())
            {
              idMap.insert(std::pair<const std::string, const SBase*>(pReaction->getListOfModifiers()->getId(), pReaction->getListOfModifiers()));
            }

          jMax = pReaction->getNumModifiers();
          const ModifierSpeciesReference* pModSRef;

          for (j = 0; j < jMax; ++j)
            {
              pModSRef = pReaction->getModifier(j);

              if (pModSRef->isSetId())
                {
                  idMap.insert(std::pair<const std::string, const SBase*>(pModSRef->getId(), pModSRef));
                }
            }
        }
    }

  if (sbmlModel.getListOfEvents()->isSetId())
    {
      idMap.insert(std::pair<const std::string, const SBase*>(sbmlModel.getListOfEvents()->getId(), sbmlModel.getListOfEvents()));
    }

  iMax = sbmlModel.getNumEvents();

  for (i = 0; i < iMax; ++i)
    {
      idMap.insert(std::pair<const std::string, const SBase*>(sbmlModel.getEvent(i)->getId(), sbmlModel.getEvent(i)));
    }

  // if COPASI is compiled with layout, we have to add those ids as well
  const LayoutModelPlugin* lmPlugin = (LayoutModelPlugin*)sbmlModel.getPlugin("layout");

  if (lmPlugin != NULL)
    {
      if (lmPlugin->getListOfLayouts()->isSetId())
        {
          idMap.insert(std::pair<const std::string, const SBase*>(lmPlugin->getListOfLayouts()->getId(), lmPlugin->getListOfLayouts()));
        }

      iMax = lmPlugin->getListOfLayouts()->size();

      for (i = 0; i < iMax; ++i)
        {
          const Layout* pLayout = lmPlugin->getLayout(i);

          if (pLayout != NULL)
            {
              if (pLayout->isSetId())
                {
                  idMap.insert(std::pair<const std::string, const SBase*>(pLayout->getId(), pLayout));
                }
            }
        }
    }

  return idMap;
}

/**
 * Create a unique id for an SBML object.
 * I can't just take the COPASI key of the object since this might conflict
 * with an already existing SBML id which came from the sbmlid attribute in a
 * COPASI file or directly by importing an SBML file.
 */
const std::string CSBMLExporter::createUniqueId(const std::map < std::string, const SBase* > & idMap,
    const std::string& prefix,
    bool addIndexForFirst,
    const std::string & separator)
{
  std::string Prefix = nameToSbmlId(prefix);

  unsigned int i = 0;
  std::ostringstream Id;

  if (addIndexForFirst)
    {
      Id << Prefix << separator << i++;
    }
  else
    {
      Id << Prefix;
    }

  while (idMap.find(Id.str()) != idMap.end())
    {
      Id.str("");
      Id << Prefix << separator << i++;
    }

  return Id.str();
}

/**
 * Checks all assignments (initial and transient) for references to objects
 * that can not be exported to SBML.
 */
void CSBMLExporter::checkForUnsupportedObjectReferences(const CDataModel& dataModel, unsigned int sbmlLevel, unsigned int sbmlVersion, std::vector<SBMLIncompatibility>& result)
{
  // check all metabolites,parameters and compartments
  const CModel* pModel = dataModel.getModel();
  assert(pModel);

  if (pModel == NULL) return;

  size_t i, iMax = this->mAssignmentVector.size();
  const CModelEntity* pME;

  for (i = 0; i < iMax; ++i)
    {
      pME = this->mAssignmentVector[i];
      assert(pME != NULL);

      if (pME != NULL)
        {
          checkForUnsupportedObjectReferences(*pME->getExpressionPtr(), dataModel, sbmlLevel, sbmlVersion, result, mIdMap, false, &mInitialValueMap);
        }
    }

  // check ode rules
  iMax = this->mODEVector.size();

  for (i = 0; i < iMax; ++i)
    {
      pME = this->mODEVector[i];
      assert(pME != NULL);

      if (pME != NULL)
        {
          checkForUnsupportedObjectReferences(*pME->getExpressionPtr(), dataModel, sbmlLevel, sbmlVersion, result, mIdMap, false, &mInitialValueMap);
        }
    }

  // check initial assignments
  iMax = this->mInitialAssignmentVector.size();

  for (i = 0; i < iMax; ++i)
    {
      pME = this->mInitialAssignmentVector[i];
      assert(pME != NULL);

      if (pME != NULL)
        {
          checkForUnsupportedObjectReferences(*pME->getInitialExpressionPtr(), dataModel, sbmlLevel, sbmlVersion, result, mIdMap, false, &mInitialValueMap);
        }
    }
}

std::string getAnnotationStringFor(const CDataObject * pObjectParent, const std::string & type)
{
  std::stringstream str;
  str << "<initialValue xmlns='http://copasi.org/initialValue' ";
  str << "parent='" << ((CModelEntity *) pObjectParent)->getSBMLId() << "' ";
  str << "type='" << type << "' />";
  return str.str();
}

/*
 * Adds the given object to the initialMap, and creates a new parameter
 * for it.
 */
void addToInitialValueMap(std::map<const std::string, Parameter*>* initialMap
                          , std::map<std::string, const SBase*>& idMap
                          , const CDataObject* pObject
                          , const CDataObject* pObjectParent
                          , int sbmlLevel
                          , int sbmlVersion)
{
  if (initialMap == NULL || pObject == NULL || pObjectParent == NULL)
    return;

  const std::string& cn = pObject->getStringCN();

  if ((*initialMap)[cn] != NULL)
    {
      // already have the initial assignment no need to add another one
      return;
    }

  Parameter* initial = new Parameter(sbmlLevel, sbmlVersion);
  initial->setAnnotation(getAnnotationStringFor(pObjectParent, pObject->getObjectName()));
  initial->initDefaults();
  initial->setId(CSBMLExporter::createUniqueId(idMap, pObjectParent->getKey(), false));
  initial->setName("Initial for " + pObjectParent->getObjectName());

  if (pObject->hasFlag(CDataObject::ValueDbl))
    initial->setValue(*((const C_FLOAT64*) pObject->getValuePointer()));

  idMap.insert(std::pair<const std::string, const SBase*>(initial->getId(), initial));

  (*initialMap) [cn] = initial;
}

/*
 * Adds the initial particle number to the initialMap, and creates a new parameter
 * and initial assignment for it.
 */
void addParticleNumberToInitialValueMap(std::map< const std::string, Parameter * > * initialMap,
                                        std::map< std::string, const SBase * > & idMap,
                                        const CMetab * pMetab, int sbmlLevel, int sbmlVersion)
{
  if (initialMap == NULL || pMetab == NULL || pMetab->getCompartment() == NULL)
    return;

  auto cn = pMetab->getInitialValueReference()->getStringCN();

  if ((*initialMap)[cn] != NULL)
    {
      // already have the initial assignment no need to add another one
      return;
    }

  auto * pDM = pMetab->getObjectDataModel();
  auto factor = pDM->getModel()->getQuantity2NumberFactor();

  Parameter * initial = new Parameter(sbmlLevel, sbmlVersion);
  initial->setAnnotation(getAnnotationStringFor(pMetab, pMetab->getInitialValueReference()->getObjectName()));
  initial->initDefaults();
  initial->setId(CSBMLExporter::createUniqueId(idMap, pMetab->getKey(), false));
  initial->setName("Initial for " + pMetab->getObjectName());
  initial->setValue(pMetab->getInitialValue() * factor * pMetab->getCompartment()->getInitialValue());

  idMap.insert(std::pair< const std::string, const SBase * >(initial->getId(), initial));

  (*initialMap)[cn] = initial;
}

void CSBMLExporter::checkForUnsupportedObjectReferences(
  const CEvaluationTree& expr
  , const CDataModel& dataModel
  , unsigned int sbmlLevel
  , unsigned int sbmlVersion
  , std::vector<SBMLIncompatibility>& result
  , std::map<std::string, const SBase*>& idMap
  , bool initialExpression /*= false*/
  , std::map<const std::string, Parameter*>* initialMap /*= NULL*/)
{
  // SBML Level 1 and Level 2 Version 1 can have references to transient values of
  // compartments, metabolites and global parameters as well as time (model)

  // SBML Level 2 Version 2 and above can have the same references as level 1 plus references to
  // reaction fluxes.

  // Starting with COPASI Build 30 references to local parameters are allowed
  // as well because they are converted to global parameters
  const std::vector<CEvaluationNode*>& objectNodes = expr.getNodeList();
  size_t j, jMax = objectNodes.size();

  for (j = 0; j < jMax; ++j)
    {
      const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(objectNodes[j]);

      if (pObjectNode == NULL ||
          pObjectNode->mainType() != CEvaluationNode::MainType::OBJECT) continue;

      const CDataObject* pObject = CObjectInterface::DataObject(dataModel.getObjectFromCN(pObjectNode->getObjectCN()));

      if (pObject == NULL) // the above fails to resolve imported avogadro references
        pObject = CObjectInterface::DataObject(dataModel.getModel()->getObject(pObjectNode->getObjectCN()));

      if (!pObject)
        {
          CCopasiMessage(CCopasiMessage::WARNING, "Could not resolve the CN '%s'", pObjectNode->getObjectCN().c_str());
          continue;
        }

      if (pObject->hasFlag(CDataObject::Reference))
        {
          const CDataObject* pObjectParent = pObject->getObjectParent();
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
                  if (pObject->getObjectName() == "InitialVolume"
                      && initialMap != NULL
                      && (sbmlLevel > 2 || (sbmlLevel == 2 && sbmlVersion > 1)))
                    {
                      // add new parameter for the initial value
                      addToInitialValueMap(initialMap, idMap, pObject, pObjectParent, sbmlLevel, sbmlVersion);
                    }
                  else if (pObject->getObjectName() != "Volume"
                           && pObject->getObjectName() != "Rate")
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
                  if (pObject->getObjectName() == "InitialConcentration"
                      && initialMap != NULL
                      && (sbmlLevel > 2 || (sbmlLevel == 2 && sbmlVersion > 1)))
                    {
                      // add new parameter for the initial value
                      addToInitialValueMap(initialMap, idMap, pObject, pObjectParent, sbmlLevel, sbmlVersion);
                    }
                  else if (pObject->getObjectName() == "InitialParticleNumber"
                           && initialMap != NULL
                           && (sbmlLevel > 2 || (sbmlLevel == 2 && sbmlVersion > 1)))
                    {
                      addParticleNumberToInitialValueMap(initialMap, idMap, dynamic_cast< const CMetab * >(pObjectParent), sbmlLevel, sbmlVersion);
                    }
                  else if (pObject->getObjectName() != "Concentration"
                           && pObject->getObjectName() != "ParticleNumber"
                           && pObject->getObjectName() != "Rate")
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
                  if (pObject->getObjectName() == "InitialValue"
                      && initialMap != NULL
                      && (sbmlLevel > 2 || (sbmlLevel == 2 && sbmlVersion > 1)))
                    {
                      // add new parameter for the initial value
                      addToInitialValueMap(initialMap, idMap, pObject, pObjectParent, sbmlLevel, sbmlVersion);
                    }
                  else if (pObject->getObjectName() != "Value"
                           && pObject->getObjectName() != "Rate")
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

                  if (pObject->getObjectName() == "Avogadro Constant")
                    {
                      if (sbmlLevel < 3) // l3 supports avogadro as csymbol
                        {
                          Parameter* param = (*initialMap)[pObject->getStringCN()];

                          if (!param)
                            {
                              param = new Parameter(sbmlLevel, sbmlVersion);
                              param->initDefaults();
                              param->setId(CSBMLExporter::createUniqueId(idMap, "Avogadro", false));
                              param->setAnnotation("<avogadro xmlns='http://copasi.org/constant' />");
                              param->setName(pObject->getObjectName());
                              param->setValue(*((double*)pObject->getValuePointer()));
                              idMap.insert(std::pair<const std::string, const SBase*>(param->getId(), param));

                              (*initialMap)[pObject->getStringCN()] = param;
                            }
                        }
                    }
                  else if (pObject->getObjectName() == "Quantity Conversion Factor")
                    {
                      Parameter* param = (*initialMap)[pObject->getStringCN()];

                      if (!param)
                        {
                          param = new Parameter(sbmlLevel, sbmlVersion);
                          param->initDefaults();
                          param->setId(CSBMLExporter::createUniqueId(idMap, "QuantityConversionFactor", false));
                          param->setAnnotation("<quantityConversionFactor xmlns='http://copasi.org/constant' />");
                          param->setName(pObject->getObjectName());
                          param->setValue(*((double*)pObject->getValuePointer()));
                          idMap.insert(std::pair<const std::string, const SBase*>(param->getId(), param));

                          (*initialMap)[pObject->getStringCN()] = param;
                        }
                    }
                  else
                    {
                      result.push_back(SBMLIncompatibility(1, pObject->getObjectName().c_str(), "model", pObjectParent->getObjectName().c_str()));
                    }
                }
            }
          else if (typeString == "Parameter")
            {
              // must be a local parameter
              if (pObject->getObjectName() != "Value")
                {
                  result.push_back(SBMLIncompatibility(1, pObject->getObjectName().c_str(), "local parameter", pObjectParent->getObjectName().c_str()));
                }
            }
          else
            {
              if (sbmlLevel == 1 || (sbmlLevel == 2 && sbmlVersion == 1))
                {
                  result.push_back(SBMLIncompatibility(10, pObject->getObjectName().c_str(), typeString.c_str(), pObjectParent->getObjectName().c_str()));
                }
              else
                {
                  if (typeString == "Reaction")
                    {
                      if (pObject->getObjectName() != "Flux")
                        {
                          result.push_back(SBMLIncompatibility(1, pObject->getObjectName().c_str(), "reaction", pObjectParent->getObjectName().c_str()));
                        }
                    }
                }
            }
        }
      else
        {
          // normally local parameters are referenced via their value and
          // not directly, so this code should never be called
          const CCopasiParameter* pLocalParameter = dynamic_cast<const CCopasiParameter*>(pObject);

          if (pLocalParameter == NULL)
            {
              result.push_back(SBMLIncompatibility(1, "value", pObject->getObjectType().c_str(), pObject->getObjectName().c_str()));
            }
        }
    }
}

/**
 * Checks whether the given data model can be exported to SBML Level1
 * If it can be exported, the result vector will be empty, otherwise it will
 * contain a number of messages that specify why it can't be exported.
 */
void CSBMLExporter::isModelSBMLL1Compatible(const CDataModel& dataModel, std::vector<SBMLIncompatibility>& result)
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
void CSBMLExporter::isModelSBMLL2V1Compatible(const CDataModel& dataModel, std::vector<SBMLIncompatibility>& result)
{
  // check for initial assignments
  CSBMLExporter::checkForInitialAssignments(dataModel, result);
}

/**
 * Checks whether the given data model can be exported to SBML Level2 Version3.
 * If it can be exported, the result vector will be empty, otherwise it will
 * contain a number of messages that specify why it can't be exported.
 */
void CSBMLExporter::isModelSBMLL2V3Compatible(const CDataModel& dataModel, std::vector<SBMLIncompatibility>& result)
{
  // if there is an SBML model, which means the model was imported from SBML,
  // we have to check for spatial size units on species in the SBML model
  // because those are not allowed in SBMLLl2V3 and above
  SBMLUnitSupport::checkForSpatialSizeUnits(dataModel, result);
}

/**
 * Checks whether the model contains a metabolite that is defined by an ODE
 * expression and that is located in a variable volume. Since COPASI
 * interprets the expression differently from SBML, we can not correctly
 * export this yet. See Bug 903.
 */
void CSBMLExporter::checkForODESpeciesInNonfixedCompartment(const CDataModel& dataModel, std::vector<SBMLIncompatibility> result)
{
  const CModel* pModel = dataModel.getModel();
  const CDataVector<CMetab>& metabolites = pModel->getMetabolites();
  CDataVector<CMetab>::const_iterator it = metabolites.begin(), endit = metabolites.end();

  while (it != endit)
    {
      if (it->getStatus() == CModelEntity::Status::ODE)
        {
          const CCompartment* pCompartment = it->getCompartment();
          assert(pCompartment != NULL);

          if (pCompartment->getStatus() != CModelEntity::Status::FIXED)
            {
              result.push_back(SBMLIncompatibility(3, it->getObjectName().c_str(), pCompartment->getObjectName().c_str()));
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
void CSBMLExporter::isExpressionSBMLCompatible(const CEvaluationTree& expr
    , const CDataModel& dataModel
    , int sbmlLevel
    , int sbmlVersion
    , std::vector<SBMLIncompatibility>& result
    , std::map<std::string, const SBase*>& idMap
    , const std::string& objectDescription
    , bool initialExpression /* = false */
    , std::map<const std::string, Parameter*>* initialMap /* = NULL */)
{
  checkForUnsupportedObjectReferences(expr, dataModel, sbmlLevel, sbmlVersion, result, idMap, initialExpression, initialMap);
  std::set<CEvaluationNode::SubType> unsupportedFunctionTypes = CSBMLExporter::createUnsupportedFunctionTypeSet(sbmlLevel);

  if (expr.getRoot() != NULL)
    checkForUnsupportedFunctionCalls(*expr.getRoot(), unsupportedFunctionTypes, result, objectDescription);
}

/**
 * This static methods checks, whether the model uses any function calls
 * that can not be expressed in SBML like the random distribution
 * functions.
 */
void CSBMLExporter::checkForUnsupportedFunctionCalls(const CDataModel& /*dataModel*/,
    unsigned int sbmlLevel, unsigned int /*sbmlVersion*/, std::vector<SBMLIncompatibility>& result)
{
  // Fill the set of unsupported functions depending on the level and
  // version
  std::set<CEvaluationNode::SubType> unsupportedFunctionTypes = CSBMLExporter::createUnsupportedFunctionTypeSet(sbmlLevel);
  // check all metabolites,parameters and compartments
  // make sure the list of assignments and initial assignments is filled
  // before this function is called
  size_t i, iMax = mAssignmentVector.size();
  const CModelEntity* pME = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pME = mAssignmentVector[i];
      assert(pME != NULL);

      if (pME != NULL)
        {
          checkForUnsupportedFunctionCalls(*pME->getExpressionPtr()->getRoot(), unsupportedFunctionTypes, result, std::string(pME->getObjectType() + " called \"" + pME->getObjectName() + "\""));
        }
    }

  // check ode rules
  iMax = mODEVector.size();

  for (i = 0; i < iMax; ++i)
    {
      pME = mODEVector[i];
      assert(pME != NULL);

      if (pME != NULL)
        {
          checkForUnsupportedFunctionCalls(*pME->getExpressionPtr()->getRoot(), unsupportedFunctionTypes, result, std::string(pME->getObjectType() + " called \"" + pME->getObjectName() + "\""));
        }
    }

  // check initial assignments
  iMax = mInitialAssignmentVector.size();

  for (i = 0; i < iMax; ++i)
    {
      pME = mInitialAssignmentVector[i];
      assert(pME != NULL);

      if (pME != NULL)
        {
          checkForUnsupportedFunctionCalls(*pME->getInitialExpressionPtr()->getRoot(), unsupportedFunctionTypes, result, std::string(pME->getObjectType() + " called \"" + pME->getObjectName() + "\""));
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
          checkForUnsupportedFunctionCalls(*(*it)->getRoot(), unsupportedFunctionTypes, result, std::string("function called \"" + (*it)->getObjectName() + "\""));
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
    const std::set<CEvaluationNode::SubType>& unsupportedFunctions,
    std::vector<SBMLIncompatibility>& result, const std::string& objectDescription)
{
  if (node.mainType() == CEvaluationNode::MainType::FUNCTION)
    {
      CEvaluationNode::SubType subtype = node.subType();

      if (unsupportedFunctions.find(subtype) != unsupportedFunctions.end())
        {
          result.push_back(SBMLIncompatibility(2, node.getData().c_str(), objectDescription.c_str()));
        }
    }

  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(node.getChild());

  while (pChild != NULL)
    {
      checkForUnsupportedFunctionCalls(*pChild, unsupportedFunctions, result, objectDescription);
      pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
    }
}

/**
 * This method checks whether the given model contains any initial assignments.
 */
void CSBMLExporter::checkForInitialAssignments(const CDataModel& dataModel, std::vector<SBMLIncompatibility>& result)
{
  const CModel* pModel = dataModel.getModel();

  if (pModel != NULL)
    {
      // check for rules
      const CDataVectorNS<CCompartment>& compartments = pModel->getCompartments();
      CDataVectorNS<CCompartment>::const_iterator compIt = compartments.begin(), compEndit = compartments.end();

      while (compIt != compEndit)
        {
          if (!compIt->getInitialExpression().empty())
            {
              result.push_back(SBMLIncompatibility(5, "Compartment", compIt->getObjectName().c_str()));
            }

          ++compIt;
        }

      const CDataVector<CMetab>& metabs = pModel->getMetabolites();

      CDataVector<CMetab>::const_iterator metabIt = metabs.begin(), metabEndit = metabs.end();

      while (metabIt != metabEndit)
        {
          if (!metabIt->getInitialExpression().empty())
            {
              result.push_back(SBMLIncompatibility(5, "Metabolite", metabIt->getObjectName().c_str()));
            }

          ++metabIt;
        }

      const CDataVectorN<CModelValue>& parameters = pModel->getModelValues();

      CDataVectorN<CModelValue>::const_iterator mvIt = parameters.begin(), mvEndit = parameters.end();

      while (mvIt != mvEndit)
        {
          if (!mvIt->getInitialExpression().empty())
            {
              result.push_back(SBMLIncompatibility(5, "Parameter", mvIt->getObjectName().c_str()));
            }

          ++mvIt;
        }
    }
}

/**
 * Create all function definitions.
 */
bool CSBMLExporter::createFunctionDefinitions(CDataModel& dataModel)
{
  this->mExportedFunctions.clear(true);
  this->mFunctionMap.clear();
  // make sure the list of used functions is filled before this is
  // called
  // make sure the mCOPASI2SBMLMap is up to date

  // find all indirectly called functions
  std::vector<CFunction*> usedFunctions = findUsedFunctions(this->mUsedFunctions, CRootContainer::getFunctionList());
  this->mUsedFunctions.clear();
  this->mUsedFunctions.insert(usedFunctions.begin(), usedFunctions.end());

  // remove the function calls that have been created by copasi solely for use
  // as a kinetic law term if it is no longer needed
  Model* pModel = this->mpSBMLDocument->getModel();
  assert(pModel);

  if (pModel == NULL) fatalError();

  std::map<SBase*, const CDataObject*> sbml2copasiMap;
  std::map<const CDataObject*, SBase*>::iterator mapIt = this->mCOPASI2SBMLMap.begin();
  std::map<const CDataObject*, SBase*>::iterator mapEndit = this->mCOPASI2SBMLMap.end();

  while (mapIt != mapEndit)
    {
      sbml2copasiMap.insert(std::make_pair(mapIt->second, mapIt->first));
      ++mapIt;
    }

  std::set<CFunction*> unusedFunctions;
  unsigned int i = 0, iMax = pModel->getNumFunctionDefinitions();
  std::map<SBase*, const CDataObject*>::iterator mapPos;
  std::set<std::string> toRemove;

  while (i < iMax)
    {
      FunctionDefinition* pFunDef = pModel->getFunctionDefinition(i);

      if (pFunDef != NULL)
        {
          mapPos = sbml2copasiMap.find(pFunDef);

          if (mapPos != sbml2copasiMap.end())
            {
              CFunction* pFun = dynamic_cast<CFunction*>(const_cast<CDataObject*>(mapPos->second));

              if (pFun != NULL && this->mUsedFunctions.find(pFun) == this->mUsedFunctions.end())
                {
                  // the function exists in the model, but it is not used in any
                  // expression
                  if (pFun->getObjectName().find("function_4_") == 0 || pFun->getObjectName().find("Function for ") == 0)
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

  if (reportCurrentProgressOrStop())
    return false;

  // find all indirectly called functions for the unused functions
  std::vector<CFunction*> functionsVect = findUsedFunctions(unusedFunctions, CRootContainer::getFunctionList());
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
              this->mUsedFunctions.find(dynamic_cast<CFunction*>(const_cast<CDataObject*>(mapPos->second))) == this->mUsedFunctions.end())
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
  // and remove their entries from the copasi2sbmlmap
  iMax = pModel->getNumFunctionDefinitions();

  for (unsigned int i = 0; i < iMax; ++i)
    {
      mapIt = this->mCOPASI2SBMLMap.begin();
      mapEndit = this->mCOPASI2SBMLMap.end();

      while (mapIt != mapEndit)
        {
          if (mapIt->second == pModel->getFunctionDefinition(i))
            {
              this->mCOPASI2SBMLMap.erase(mapIt->first);
              break;
            }

          ++mapIt;
        }
    }

  // don't want to remove the new custom function definitions if present
  // pModel->getListOfFunctionDefinitions()->clear(true);
  for (int i = ((int)pModel->getNumFunctionDefinitions()) - 1; i >= 0; --i)
    {
      FunctionDefinition* current = pModel->getFunctionDefinition(i);

      if (current != NULL &&
          current->isSetAnnotation() &&
          current->getAnnotation()->getNumChildren() == 1 &&
          current->getAnnotation()->getChild(0).getURI().find("http://sbml.org/annotations/") != std::string::npos)
        continue;

      // if we are here it is not one of the custom ones, so delete it
      FunctionDefinition* toDelete = pModel->removeFunctionDefinition(i);
      delete toDelete;
    }

  std::vector<CFunction*>::iterator it = functionsVect.begin(), endit = functionsVect.end();

  while (it != endit)
    {
      if (*it != NULL)
        {
          createFunctionDefinition(**it, dataModel);
        }

      ++it;

      if (reportCurrentProgressOrStop())
        return false;
    }

  return true;
}

/**
 * function going through all children of pFunNode, and renaming elements if they are in the rename list
 */
void renameAstNodes(ASTNode* pFunNode, const std::map<std::string, std::string>& renameList)
{
  if (pFunNode == NULL || renameList.empty())
    return;

  if (pFunNode->getType() == AST_NAME)
    {
      std::map<std::string, std::string>::const_iterator it = renameList.find(pFunNode->getName());

      if (it != renameList.end())
        {
          pFunNode->setName(it->second.c_str());
        }
    }

  unsigned int iMax = pFunNode->getNumChildren();

  for (unsigned int i = 0; i < iMax; ++i)
    {
      renameAstNodes(pFunNode->getChild(i), renameList);
    }
}

/**
 * Create the SBML function definition from the given COPASI function.
 */
void CSBMLExporter::createFunctionDefinition(CFunction& function, CDataModel& dataModel)
{
  // check the expression
  std::map<const CDataObject*, SBase*>::iterator pos = this->mCOPASI2SBMLMap.find(&function);
  FunctionDefinition* pFunDef = NULL;

  // the entry could be NULL when exporting to L2 first and then to L3 because the
  // SBMLExporter::collectIds will add a NULL entry into the id table which will be
  // transferred to the COPASI2SBMLMap.
  if (pos != this->mCOPASI2SBMLMap.end() && pos->second != NULL)
    {
      pFunDef = dynamic_cast<FunctionDefinition*>(pos->second);
      assert(pFunDef);
      this->mpSBMLDocument->getModel()->getListOfFunctionDefinitions()->appendAndOwn(pFunDef);
    }
  else
    {
      if (this->mpSBMLDocument->getLevel() == 1)
        {
          pFunDef = new FunctionDefinition(2, 4);
        }
      else
        {
          pFunDef = new FunctionDefinition(this->mpSBMLDocument->getLevel(), this->mpSBMLDocument->getVersion());
        }

      this->mFunctionMap[pFunDef] = &function;
      pFunDef->setName(function.getObjectName());
      std::string id = function.getSBMLId();

      if (id.empty())
        {
          id = function.getObjectName();

          if (CSBMLExporter::isValidSId(id))
            {
              if (this->mIdMap.find(id) != this->mIdMap.end())
                {
                  id = CSBMLExporter::createUniqueId(this->mIdMap, id, true);
                }
            }
          else
            {
              id = CSBMLExporter::createUniqueId(this->mIdMap, function.getObjectName(), false);
            }
        }

      this->mIdMap.insert(std::pair<const std::string, const SBase*>(id, pFunDef));
      pFunDef->setId(id);
      function.setSBMLId(id);
      this->mCOPASI2SBMLMap[&function] = pFunDef;
    }

  if (function.getRoot() == NULL)
    {
      std::string errorMessage = std::string("Can not export function '");
      errorMessage += function.getObjectName();
      errorMessage += std::string("'. Function does not have a valid root node.");
      CCopasiMessage(CCopasiMessage::EXCEPTION, errorMessage.c_str());
    }
  else
    {
      std::vector<SBMLIncompatibility> result;
      CSBMLExporter::isExpressionSBMLCompatible(function,
          dataModel,
          this->mSBMLLevel,
          this->mSBMLVersion,
          result,
          mIdMap,
          std::string("function with name \"" + function.getObjectName() + "\"")
                                               );

      if (result.empty())
        {
          ASTNode* pFunNode = this->convertToASTNode(function.getRoot(), dataModel);
          // go through the AST tree and replace all function call nodes with with a call to the sbml id
          ASTNode* pLambda = new ASTNode(AST_LAMBDA);
          // add the parameters to the function definition
          const CFunctionParameters& funParams = function.getVariables();
          size_t i, iMax = funParams.size();
          ASTNode* pParamNode = NULL;

          std::map<std::string, std::string> renameList;

          for (i = 0; i < iMax; ++i)
            {
              pParamNode = new ASTNode(AST_NAME);
              std::string name = funParams[i]->getObjectName();

              if (!isValidSId(name))
                {
                  std::string newName = nameToSbmlId(name);
                  renameList[name] = newName;
                  name = newName;
                }

              pParamNode->setName(name.c_str());
              pLambda->addChild(pParamNode);
            }

          if (!renameList.empty())
            renameAstNodes(pFunNode, renameList);

          pLambda->addChild(pFunNode);

          if (pFunDef->setMath(pLambda) != LIBSBML_OPERATION_SUCCESS)
            {
              CCopasiMessage(CCopasiMessage::WARNING,
                             "The function '%s' uses an invalid expression '%s' that cannot be exported to SBML, the function definition is not exported."
                             , function.getObjectName().c_str()
                             , function.getInfix().c_str());
            }

          this->mExportedFunctions.appendAndOwn(pFunDef);
          delete pLambda;
        }
      else
        {
          this->mIncompatibilities.insert(this->mIncompatibilities.end(), result.begin(), result.end());
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 28, function.getObjectName().c_str());
        }
    }

  if (pFunDef != NULL)
    {
      CSBMLExporter::setSBMLNotes(pFunDef, &function);
    }

  CSBMLExporter::updateMIRIAMAnnotation(&function, pFunDef, this->mMetaIdMap);
}

size_t convertBaseUnit(CBaseUnit::Kind unit)
{
  switch (unit)
    {
      case CBaseUnit::dimensionless:
        return UNIT_KIND_DIMENSIONLESS;

      case CBaseUnit::meter:
        return UNIT_KIND_METRE;

      case CBaseUnit::gram:
        return UNIT_KIND_GRAM;

      case CBaseUnit::second:
        return UNIT_KIND_SECOND;

      case CBaseUnit::ampere:
        return UNIT_KIND_AMPERE;

      case CBaseUnit::kelvin:
        return UNIT_KIND_KELVIN;

      case CBaseUnit::item:
        return UNIT_KIND_ITEM;

      case CBaseUnit::candela:
        return UNIT_KIND_CANDELA;

      case CBaseUnit::avogadro:
        return UNIT_KIND_AVOGADRO;

      case CBaseUnit::undefined:
      default:
        return C_INVALID_INDEX;
    }
}

size_t convertSymbol(const std::string& unit)
{
  if (unit == "A")
    return UNIT_KIND_AMPERE;

  if (unit == "Avogadro")
    return UNIT_KIND_AVOGADRO;

  if (unit == "Bq")
    return UNIT_KIND_BECQUEREL;

  if (unit == "cd")
    return UNIT_KIND_CANDELA;

  if (unit == "C")
    return UNIT_KIND_COULOMB;

  if (unit == "d")
    return C_INVALID_INDEX;            // unsupported

  if (unit == "1")
    return UNIT_KIND_DIMENSIONLESS;

  if (unit == "F")
    return UNIT_KIND_FARAD;

  if (unit == "g")
    return UNIT_KIND_GRAM;

  if (unit == "Gy")
    return UNIT_KIND_GRAY;

  if (unit == "H")
    return UNIT_KIND_HENRY;

  if (unit == "Hz")
    return UNIT_KIND_HERTZ;

  if (unit == "h")                     // unsupported
    return C_INVALID_INDEX;

  if (unit == "#")
    return UNIT_KIND_ITEM;

  if (unit == "J")
    return UNIT_KIND_JOULE;

  if (unit == "kat")
    return UNIT_KIND_KATAL;

  if (unit == "K")
    return UNIT_KIND_KELVIN;

  if (unit == "l")
    return UNIT_KIND_LITRE;

  if (unit == "lm")
    return UNIT_KIND_LUMEN;

  if (unit == "lx")
    return UNIT_KIND_LUX;

  if (unit == "m")
    return UNIT_KIND_METRE;

  if (unit == "min")                   // unsupported
    return C_INVALID_INDEX;

  if (unit == "mol")
    return UNIT_KIND_MOLE;

  if (unit == "N")
    return UNIT_KIND_NEWTON;

  if (unit == "ohm" || unit == "\xCE\xA9")
    return UNIT_KIND_OHM;

  if (unit == "Pa")
    return UNIT_KIND_PASCAL;

  if (unit == "rad")
    return UNIT_KIND_RADIAN;

  if (unit == "s")
    return UNIT_KIND_SECOND;

  if (unit == "S")
    return UNIT_KIND_SIEMENS;

  if (unit == "Sv")
    return UNIT_KIND_SIEVERT;

  if (unit == "sr")
    return UNIT_KIND_STERADIAN;

  if (unit == "T")
    return UNIT_KIND_TESLA;

  if (unit == "V")
    return UNIT_KIND_VOLT;

  if (unit == "W")
    return UNIT_KIND_WATT;

  if (unit == "Wb")
    return UNIT_KIND_WEBER;

  return C_INVALID_INDEX;
}

Unit* addCUnitComponentToUnitDefinition(UnitDefinition* result, const CUnitComponent &component, const std::string& unitExpression)
{
  Unit* pUnit = result->createUnit();

  pUnit->setExponent(component.getExponent());
  pUnit->setScale((int)component.getScale());
  pUnit->setMultiplier(component.getMultiplier());

  size_t unitKind = convertBaseUnit(component.getKind());

  if (unitKind == C_INVALID_INDEX)
    {
      std::stringstream str;
      str << "An unsupported UnitKind was encountered while exporting '"
          << unitExpression
          << "', it was replaced by dimensionless.";
      CCopasiMessage(CCopasiMessage::WARNING, str.str().c_str());
      pUnit->setKind(UNIT_KIND_DIMENSIONLESS);
    }
  else
    {
      pUnit->setKind(static_cast<UnitKind_t>(unitKind));
    }

  return pUnit;
}

void addSymbolComponentToUnitDefinition(UnitDefinition* result, CUnit::SymbolComponent& component, const std::string& unitExpression)
{
  std::string symbol = component.symbol;

  if (symbol.empty())
    return;

  double multiplier = component.multiplier;
  std::string possibleScale = symbol.substr(0, 1);
  std::string possibleUnit = symbol.substr(1);

  if (possibleScale[0] == '\xc2')
    {
      possibleScale = symbol.substr(0, 2);
      possibleUnit = symbol.substr(2);
    }

  bool use_d_prefix = true;

  // need to deal with unsupported time units differently
  // just replace them by their multiplier * s
  if (symbol == "h" || possibleUnit == "h")
    {
      multiplier *= 3600;
      symbol = "s";
      possibleUnit = "s";
      use_d_prefix = false;
    }
  else if (symbol == "min" || possibleUnit == "min")
    {
      multiplier *= 60;
      symbol = "s";
      possibleUnit = "s";
    }
  else if (symbol == "d" || possibleUnit == "d")
    {
      multiplier *= 86400;
      symbol = "s";
      possibleUnit = "s";
      use_d_prefix = false;
    }

  int unitKind = convertSymbol(possibleUnit);
  int scale = 0;

  if (unitKind != C_INVALID_INDEX && use_d_prefix)
    scale = static_cast<int>(CBaseUnit::scaleFromPrefix(possibleScale));
  else
    unitKind = convertSymbol(symbol);

  if (unitKind == C_INVALID_INDEX)
    {
      // no compound unitkind exists, so use the basic ones

      CUnit unit = CUnit(symbol);
      std::set< CUnitComponent >::const_iterator it = unit.getComponents().begin();

      for (; it != unit.getComponents().end(); ++it)
        {
          CUnitComponent baseComponent = *it;

          if (component.exponent != 1.0)
            baseComponent.setExponent(baseComponent.getExponent()*component.exponent);

          if (component.scale != 0.0)
            baseComponent.setScale(baseComponent.getScale() + component.scale);

          if (component.multiplier != 1.0)
            {
              baseComponent.setMultiplier(baseComponent.getMultiplier()*multiplier);
            }

          addCUnitComponentToUnitDefinition(result, baseComponent, unitExpression);
        }
    }
  else
    {
      Unit* pUnit = result->createUnit();
      pUnit->setExponent(component.exponent);
      pUnit->setScale((int)component.scale + scale);
      pUnit->setMultiplier(multiplier);
      pUnit->setKind(static_cast<UnitKind_t>(unitKind));
    }
}

UnitDefinition *CSBMLExporter::createUnitDefinitionFor(const CUnit &unit)
{
  if (mpSBMLDocument == NULL || unit.isUndefined()) return NULL;

  Model* pModel = mpSBMLDocument->getModel();

  if (pModel == NULL) return NULL;

  UnitDefinition* result = NULL;

  // look whether we created the unit before
  for (size_t i = 0; i < pModel->getNumUnitDefinitions(); ++i)
    {
      result = pModel->getUnitDefinition(i);

      if (result->getName() == unit.getExpression())
        return result;
    }

  // otherwise create a new one
  result = pModel->createUnitDefinition();

  std::string id("unit_0");
  int count = 0;

  while (pModel->getUnitDefinition(id) != NULL)
    {
      std::stringstream str; str << "unit_" << ++count;
      id = str.str();
    }

  result->setId(id);
  mIdMap.insert(std::make_pair(result->getId(), result));
  std::string unitExpression = unit.getExpression();
  result->setName(unitExpression);

  std::vector< CUnit::SymbolComponent > symbolComponents = unit.getSymbolComponents();

  std::vector<CUnit::SymbolComponent >::iterator symbolIt = symbolComponents.begin();

  for (; symbolIt != symbolComponents.end(); ++symbolIt)
    {
      CUnit::SymbolComponent& current = *symbolIt;
      addSymbolComponentToUnitDefinition(result, current, unitExpression);
    }

#if 0
  // while this code works, it does write out base units only, that won't help our users
  // much ... moreover, since avogadro is only supported starting with SBML Level 3,
  // we would have to prohibit all previous versions of SBML export with units
  std::set< CUnitComponent >::const_iterator it = unit.getComponents().begin();

  for (; it != unit.getComponents().end(); ++it)
    {
      const CUnitComponent& component = *it;
      addCUnitComponentToUnitDefinition(result, component, unitExpression);
    }

#endif

  return result;
}

void CSBMLExporter::exportAndAssignUnit(const CUnit &unit, SBase *sbmlElement)
{
  if (sbmlElement == NULL || mpSBMLDocument == NULL || unit.isUndefined()) return;

  Model* pModel = mpSBMLDocument->getModel();

  if (pModel == NULL) return;

  UnitDefinition* pUnit = createUnitDefinitionFor(unit);

  if (pUnit == NULL) return;

  Parameter* pParameter = dynamic_cast<Parameter*>(sbmlElement);

  if (pParameter != NULL)
    {
      pParameter->setUnits(pUnit->getId());
      return;
    }

  Species* pSpecies = dynamic_cast<Species*>(sbmlElement);

  if (pSpecies != NULL)
    {
      pSpecies->setUnits(pUnit->getId());
      return;
    }

  Compartment* pCompartment = dynamic_cast<Compartment*>(sbmlElement);

  if (pCompartment != NULL)
    {
      pCompartment->setUnits(pUnit->getId());
      return;
    }
}

/*
 * Some parameters and initial assignments that are only needed for the export
 * are tagged so as not to be removed. This function removes that tag and is to
 * be called after the export has been completed.
 */
void removeStickyTagFromElements(SBMLDocument *pSBMLDocument)
{
  if (pSBMLDocument == NULL || pSBMLDocument->getModel() == NULL)
    return;

  // reset sticky parameters
  for (unsigned int i = 0; i < pSBMLDocument->getModel()->getNumParameters(); ++i)
    pSBMLDocument->getModel()->getParameter(i)->setUserData(NULL);

  // reset sticky initial assignments
  for (unsigned int i = 0; i < pSBMLDocument->getModel()->getNumInitialAssignments(); ++i)
    pSBMLDocument->getModel()->getInitialAssignment(i)->setUserData(NULL);
}

/**
 * Export the model to SBML.
 * The SBML model is returned as a string. In case of an error, an
 * empty string is returned.
 */
bool
CSBMLExporter::exportLayout(unsigned int sbmlLevel, CDataModel& dataModel)
{
  if (createProgressStepOrStop(12, 1, "Exporting layout..."))
    {
      finishExport();
      return false;
    }

  if (this->mpSBMLDocument && this->mpSBMLDocument->getModel())
    {
      LayoutModelPlugin* lmPlugin = static_cast<LayoutModelPlugin*>(this->mpSBMLDocument->getModel()->getPlugin("layout"));

      if (lmPlugin != NULL && sbmlLevel > 1)
        {
          // the layout can only be exported for Level 2 or Level 3
          dataModel.getListOfLayouts()->exportToSBML(lmPlugin->getListOfLayouts(),
              this->mCOPASI2SBMLMap, mIdMap, this->mpSBMLDocument->getLevel(), this->mpSBMLDocument->getVersion());

          // also ensure ther is one global render information object
          if (lmPlugin->getNumLayouts() > 0 && getNumDefaultStyles() > 0)
            {
              RenderListOfLayoutsPlugin* plugin = static_cast<RenderListOfLayoutsPlugin *>(lmPlugin->getListOfLayouts()->getPlugin("render"));

              if (plugin != NULL)
                {
                  // iterate through all layouts and find the last used
                  // render information objects
                  std::set<std::string> mRenderKeys;
                  for (int i = 0; i < dataModel.getListOfLayouts()->size(); i++)
                    {
                      CLayout& layout = dataModel.getListOfLayouts()->operator[](i);
                      std::string renderKey = layout.getLastUsedRenderInformation();
                      if (!renderKey.empty())
                        {
                          mRenderKeys.insert(renderKey);
                        }
                    }

                    // now go through all keys and add them to the plugin
                    for (auto& key : mRenderKeys)
                      {
                        auto* defaultStyle = getDefaultStyle(key);
                        if (defaultStyle && plugin->getRenderInformation(defaultStyle->getKey()) == NULL)
                          {
                            GlobalRenderInformation* info = plugin->createGlobalRenderInformation();
                            defaultStyle->toSBML(info, this->mpSBMLDocument->getLevel(), this->mpSBMLDocument->getVersion());
                          }
                      }

                  // if we still dont have a render information object
                  // save the first one
                  if (plugin->getNumGlobalRenderInformationObjects() == 0)
                    {
                      GlobalRenderInformation* info = plugin->createGlobalRenderInformation();
                      getDefaultStyle(0)->toSBML(info, this->mpSBMLDocument->getLevel(), this->mpSBMLDocument->getVersion());
                    }
                }
            }
        }
    }

  return true;
}

const std::string
CSBMLExporter::exportModelToString(CDataModel& dataModel,
                                   unsigned int sbmlLevel,
                                   unsigned int sbmlVersion)
{
  this->mSBMLLevel = sbmlLevel;
  this->mSBMLVersion = sbmlVersion;
  mHandledSBMLObjects.clear();

  if (mpProcessReport != NULL)
    {
      std::stringstream str;
      str << "Exporting SBML L" << sbmlLevel << "V" << sbmlVersion << "...";
      mpProcessReport->setName(str.str());
      mGlobalStepTotal = 16;
      mGlobalStepHandle = mpProcessReport->addItem("Step",
                          mGlobalStepCounter,
                          &mGlobalStepTotal);
    }

  if (!createSBMLDocument(dataModel))
    return "";

  if (!exportLayout(sbmlLevel, dataModel))
    return "";

  // export the model to a string
  if (this->mpSBMLDocument == NULL) return std::string();

  if (createProgressStepOrStop(14,
                               1,
                               "Remove unused elements..."))
    {
      finishExport();
      return "";
    }

  removeUnusedObjects();

  if (createProgressStepOrStop(15,
                               1,
                               "Writing document..."))
    {
      finishExport();
      return "";
    }

  SBMLWriter* writer = new SBMLWriter();

  writer->setProgramName("COPASI");
  writer->setProgramVersion(CVersion::VERSION.getVersion());

  std::string returnValue = writer->writeSBMLToStdString(this->mpSBMLDocument);

  pdelete(writer);

  // mark some temporary objects as no longer needed
  removeStickyTagFromElements(mpSBMLDocument);

  // the workaround is no longer necessary, as the libSBML > 5.11.4 will include
  // a converter that not only converts to l1v1 but also inlines the compartment
  // sizes and changes pow implementation as needed by Gepasi

  finishExport();

  return returnValue;
}

/*
 * Adds all created parameters to the model and sets them as initial assignments
 * to the originating elements.
 */
void
CSBMLExporter::addInitialAssignmentsToModel(const CDataModel &dataModel)
{
  if (mpSBMLDocument == NULL || mpSBMLDocument->getModel() == NULL || mInitialValueMap.empty())
    return;

  auto* model = mpSBMLDocument->getModel();
  std::map<const std::string, Parameter*>::const_iterator it;

  for (it = mInitialValueMap.begin(); it != mInitialValueMap.end(); ++it)
    {
      Parameter* param = it->second;
      // add parameter to model
      int result = model->addParameter(param);
      model->getParameter(param->getId())->setUserData((void *) "1");

      const CDataObject *obj = static_cast<const CDataObject *>(dataModel.getObject(it->first));
      const std::string &sbmlId = (static_cast<const CModelEntity*>(obj->getObjectParent()))->getSBMLId();

      // create an initial assignment for the newly created initial quantity
      // to synchronize it with the original element.
      if (!sbmlId.empty())
        {
          bool isInitialParticleNumber = param->getAnnotationString().find("type=\"InitialParticleNumber\"") != std::string::npos;
          auto * pMetab = dynamic_cast< const CMetab * >(obj->getObjectParent());
          auto * pComp = pMetab == NULL ? NULL : pMetab->getCompartment();

          if (isInitialParticleNumber && mAvogadroId.empty())
            createAvogadroIfNeeded(dataModel);

          InitialAssignment * ia = model->createInitialAssignment();
          ia->setSymbol(it->second->getId());

          if (isInitialParticleNumber && pMetab && pComp)
            {
              std::stringstream math;
              math << sbmlId << " * "
                   << mAvogadroId << " * "
                   << pComp->getSBMLId();
              ASTNode * pNode = SBML_parseFormula(math.str().c_str());
              ia->setMath(pNode);
              pdelete(pNode);
            }
          else
            {
              ASTNode * pNode = SBML_parseFormula(sbmlId.c_str());
              ia->setMath(pNode);
              pdelete(pNode);
            }

          ia->setUserData((void*)"1");
        }

      delete param;
    }
}

bool CSBMLExporter::createSBMLDocument(CDataModel& dataModel)
{
  const SBMLDocument* pOldSBMLDocument = dataModel.getCurrentSBMLDocument();
  const CModel* pModel = dataModel.getModel();

  SBMLNamespaces targetNs(mSBMLLevel, mSBMLVersion); // use reference, as the ns gets cloned

  if (pOldSBMLDocument == NULL)
    {
      try
        {
          this->mpSBMLDocument = new SBMLDocument(this->mSBMLLevel, this->mSBMLVersion);
        }
      catch (const SBMLConstructorException& ex)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, ex.what());
        }
      catch (...)
        {
          fatalError();
        }
    }
  else
    {
      this->mpSBMLDocument = dynamic_cast<SBMLDocument*>(pOldSBMLDocument->clone());

      if (mpSBMLDocument->getLevel() < mSBMLLevel)
        {
          ConversionProperties prop(&targetNs);
          prop.addOption("strict", false);
          prop.addOption("setLevelAndVersion", true);
          prop.addOption("ignorePackages", true);

          mpSBMLDocument->convert(prop);
        }
    }

  if (this->mpSBMLDocument == NULL) fatalError();

  const std::string uri = (this->mSBMLLevel < 3 ? LayoutExtension::getXmlnsL2() : LayoutExtension::getXmlnsL3V1V1());
  this->mpSBMLDocument->enablePackage(uri, "layout", true);

  if (this->mSBMLLevel > 2)
    this->mpSBMLDocument->setPackageRequired("layout", false);

  const std::string renderuri = (this->mSBMLLevel < 3 ? RenderExtension::getXmlnsL2() : RenderExtension::getXmlnsL3V1V1());
  this->mpSBMLDocument->enablePackage(renderuri, "render", true);

  if (this->mSBMLLevel > 2)
    this->mpSBMLDocument->setPackageRequired("render", false);

  if (this->mpSBMLDocument->getModel() == NULL)
    {
      // there might still be COPASI object that have an SBML id, we have to
      // collect those as well
      CSBMLExporter::collectIds(dataModel, this->mIdMap);
      std::string id = pModel->getSBMLId();

      if (id.empty())
        {
          id = CSBMLExporter::createUniqueId(this->mIdMap, pModel->getObjectName(), false);
          this->mIdMap.insert(std::pair<const std::string, const SBase*>(id, this->mpSBMLDocument->getModel()));
        }

      this->mpSBMLDocument->createModel(id);
    }
  else
    {
      SBMLUtils::collectIds(this->mpSBMLDocument->getModel(), this->mIdMap, this->mMetaIdMap);
    }

  this->mFunctionIdMap.clear();
  // update the copasi2sbmlmap
  updateCOPASI2SBMLMap(dataModel);
  // update the comments on the model
  this->mpSBMLDocument->getModel()->setName(pModel->getObjectName());

  if (createProgressStepOrStop(1, 1, "Exporting notes/annotations..."))
    {
      finishExport();
      return false;
    }

  if (pModel != NULL && this->mpSBMLDocument->getModel() != NULL)
    {
      CSBMLExporter::setSBMLNotes(this->mpSBMLDocument->getModel(), pModel);
    }

  // update the MIRIAM annotation on the model
  CSBMLExporter::updateMIRIAMAnnotation(pModel, this->mpSBMLDocument->getModel(), this->mMetaIdMap);

  if (this->mSBMLLevel > 2)
    {
      // we have to remove the conversionFactor because on import we multiplied the stoichiometries
      // with this factor
      this->mpSBMLDocument->getModel()->unsetConversionFactor();
    }

  // create units, compartments, species, parameters, reactions, initial
  // assignment, assignments, (event) and function definitions
  if (createProgressStepOrStop(2, 1, "Exporting units..."))
    {
      finishExport();
      return false;
    }

  createUnits(dataModel);
  // try to find a parameter that represents Avogadros number
  findAvogadro(dataModel);

  // check if there is an assignment to a volume
  // in that case we has to export all species with the
  // hasOnlySubstanceUnits flag set to true
  this->mVariableVolumes = this->hasVolumeAssignment(dataModel);

  if (createProgressStepOrStop(3,
                               dataModel.getModel()->getCompartments().size(),
                               "Exporting compartments..."))
    {
      finishExport();
      return false;
    }

  if (!createCompartments(dataModel))
    return false;

  if (createProgressStepOrStop(4,
                               dataModel.getModel()->getMetabolites().size(),
                               "Exporting species..."))
    {
      finishExport();
      return false;
    }

  if (!createMetabolites(dataModel))
    return false;

  if (createProgressStepOrStop(5,
                               dataModel.getModel()->getModelValues().size(),
                               "Exporting parameters..."))
    {
      finishExport();
      return false;
    }

  if (!createParameters(dataModel))
    return false;

  // TODO here we should check the expressions but the function definitions
  // TODO have not been created yet, so we can't
  // TODO Maybe we don't have to do all checks here.
  // TODO it would probably be enough to check if the expressions are valid and
  // TODO to check the function calls later on when the functions are created.

  // only export initial assignments for Level 2 Version 2 and above
  if (this->mSBMLLevel != 1 && !(this->mSBMLLevel == 2 && this->mSBMLVersion == 1))
    {
      if (createProgressStepOrStop(6,
                                   1,
                                   "Exporting initial assignments..."))
        {
          finishExport();
          return false;
        }

      if (!createInitialAssignments(dataModel))
        {
          finishExport();
          return false;
        }
    }
  else
    {
      checkForInitialAssignments(dataModel, this->mIncompatibilities);
    }

  // since the flux of a reaction can be referenced in an assignment,
  // we have to make sure that all reactions do have SBML Ids prior to creating the rules
  // and events
  assignSBMLIdsToReactions(dataModel.getModel());

  if (createProgressStepOrStop(7,
                               1,
                               "Exporting rules..."))
    {
      finishExport();
      return false;
    }

  if (!createRules(dataModel))
    {
      finishExport();
      return false;
    }

  if (createProgressStepOrStop(8,
                               dataModel.getModel()->getEvents().size(),
                               "Exporting events..."))
    {
      finishExport();
      return false;
    }

  if (!createEvents(dataModel))
    {
      finishExport();
      return false;
    }

  // we have to export the reactions after all other entities that have
  // expressions since an expression could contain a local parameter
  // If it did, it would have to be converted to a global parameter and that
  // has to be taken into consideration when creating the reactions
  if (createProgressStepOrStop(9,
                               dataModel.getModel()->getReactions().size(),
                               "Exporting reactions..."))
    {
      finishExport();
      return false;
    }

  if (!createReactions(dataModel))
    {
      finishExport();
      return false;
    }

  // find all used functions
  if (createProgressStepOrStop(10,
                               1,
                               "Exporting functions..."))
    {
      finishExport();
      return false;
    }

  if (!createFunctionDefinitions(dataModel))
    {
      finishExport();
      return false;
    }

  if (this->mSBMLLevel == 1)
    {
      // do SBML Level1 Voodoo
      // e.g. replace some of the unsupported nodes with workarounds
      convertToLevel1();
      // delete all function definitions since L1 does not have functions
      Model* pSBMLModel = this->mpSBMLDocument->getModel();
      assert(pSBMLModel != NULL);
      int i = pSBMLModel->getListOfFunctionDefinitions()->size();

      std::map<const CDataObject*, SBase*>::iterator it = this->mCOPASI2SBMLMap.begin(),
                                                     endit = this->mCOPASI2SBMLMap.end();

      while (i > 0)
        {
          --i;
          // fix for bug 1086
          // remove the object from the COPASI2SBML Map

          while (it != endit)
            {
              if (it->second == pSBMLModel->getFunctionDefinition(i))
                {
                  this->mCOPASI2SBMLMap.erase(it);
                  break;
                }

              ++it;
            }

          delete pSBMLModel->getListOfFunctionDefinitions()->remove(i);
        }

      // remove other functions:

      bool needAnotherLoop = true;

      while (needAnotherLoop)
        {
          it = mCOPASI2SBMLMap.begin();
          endit = mCOPASI2SBMLMap.end();
          needAnotherLoop = false;

          for (; it != endit; ++it)
            {
              const CFunction* fun = dynamic_cast<const CKinFunction*>(it->first);

              if (fun == NULL) continue;

              mCOPASI2SBMLMap.erase(it);
              needAnotherLoop = true;
              break;
            }
        }
    }
  else
    {
      // add all function definitions to the model
      Model* pSBMLModel = this->mpSBMLDocument->getModel();
      assert(pSBMLModel != NULL);

      if (pSBMLModel != NULL)
        {
          unsigned int i = 0, iMax = this->mExportedFunctions.size();
          int result;
          FunctionDefinition* pFunDef = NULL;
          std::map<const FunctionDefinition*, const CDataObject*>::const_iterator funPos;

          while (i < iMax)
            {
              pFunDef = this->mExportedFunctions.get(i);
              assert(pFunDef != NULL);
              // match the namespaces to those of the model
              pFunDef->setSBMLNamespaces(pSBMLModel->getSBMLNamespaces());
              // add methods only return a value starting with libsbml 4
              result = pSBMLModel->addFunctionDefinition(pFunDef);
              assert(result == LIBSBML_OPERATION_SUCCESS);
              // now we need to add the newly created FunctionDefinition to the copasi2sbml map
              funPos = this->mFunctionMap.find(pFunDef);
              assert(funPos != this->mFunctionMap.end());
              pFunDef = pSBMLModel->getFunctionDefinition(pFunDef->getId());
              assert(pFunDef != NULL);
              this->mCOPASI2SBMLMap[funPos->second] = pFunDef;
              ++i;
            }

          //the assert below no longer holds, as we export uniform / normal as functiondefinitions
          //assert(pSBMLModel->getNumFunctionDefinitions() == this->mExportedFunctions.size());
        }
    }

  // In case the document is just a clone of an old model, we have to set the level and version
  if (this->mpSBMLDocument->getLevel() != this->mSBMLLevel
      || this->mpSBMLDocument->getVersion() != this->mSBMLVersion)
    {
      if (createProgressStepOrStop(11,
                                   1,
                                   "Converting document..."))
        {
          finishExport();
          return false;
        }

      if (mSBMLLevel == 1 && mSBMLVersion == 1)
        {
          // l1v1 export tailor made to suit GEPASI, with pow -> ^ notation and
          // inlining of compartment sizes in kinetics.

          ConversionProperties prop(&targetNs);
          prop.addOption("convertToL1V1", true,
                         "convert the document to SBML Level 1 Version 1");
          prop.addOption("changePow", true,
                         "change pow expressions to the (^) hat notation");
          prop.addOption("inlineCompartmentSizes", true,
                         "if true, occurrences of compartment ids in expressions will be replaced with their initial size");

          mpSBMLDocument->convert(prop);
        }
      else
        {

          ConversionProperties prop(&targetNs);
          prop.addOption("strict", false);
          prop.addOption("setLevelAndVersion", true);
          prop.addOption("ignorePackages", true);

          mpSBMLDocument->convert(prop);
        }
    }

  if (this->mpSBMLDocument->getLevel() != this->mSBMLLevel || this->mpSBMLDocument->getVersion() != this->mSBMLVersion)
    {
      unsigned int i, iMax = this->mpSBMLDocument->getNumErrors();
      std::string message("libSBML could not convert the model to the requested level and/or version. The reason(s) given were:");

      for (i = 0; i < iMax ; ++i)
        {
          const XMLError* pSBMLError = this->mpSBMLDocument->getError(i);
          message += "\n";
          message += pSBMLError->getMessage();
        }

      CCopasiMessage(CCopasiMessage::EXCEPTION, message.c_str());
    }

  // remove mpAvogadro from the model again
  if (this->mAvogadroCreated == true)
    {
      std::map<const CDataObject*, SBase*>::iterator pos = this->mCOPASI2SBMLMap.find(this->mpAvogadro);
      this->mCOPASI2SBMLMap.erase(pos);
      dataModel.getModel()->removeModelValue(this->mpAvogadro->getKey(), true);
    }

  this->outputIncompatibilities();

  // if the model is incompatible with SBML export, throw an exception
  if (!this->mIncompatibilities.empty() && !this->mIncompleteExport)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Model incompatible with chosen version and/or level of SBML.");
    }

  // if initial assignments were used we will have to add them to the document
  addInitialAssignmentsToModel(dataModel);
  mInitialValueMap.clear();

  // delete all temporary function definitions
  // and the function map
  this->mExportedFunctions.clear(true);
  this->mFunctionMap.clear();

  return true;
}

const std::set<CEvaluationNode::SubType> CSBMLExporter::createUnsupportedFunctionTypeSet(unsigned int sbmlLevel)
{
  std::set<CEvaluationNode::SubType> unsupportedFunctionTypes;

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
      unsupportedFunctionTypes.insert(CEvaluationNode::SubType::ARCCOTH);
      //unsupportedFunctionTypes.insert(CEvaluationNode::S_RNORMAL);
      //unsupportedFunctionTypes.insert(CEvaluationNode::S_RUNIFORM);
      unsupportedFunctionTypes.insert(CEvaluationNode::SubType::MAX);
      unsupportedFunctionTypes.insert(CEvaluationNode::SubType::MIN);
    }
  else
    {
      //unsupportedFunctionTypes.insert(CEvaluationNode::S_RNORMAL);
      //unsupportedFunctionTypes.insert(CEvaluationNode::S_RUNIFORM);
      //unsupportedFunctionTypes.insert(CEvaluationNode::S_MAX);
      //unsupportedFunctionTypes.insert(CEvaluationNode::S_MIN);
    }

  return unsupportedFunctionTypes;
}

/**
 * Export the model to SBML.
 * The model is written to the file given by filename.
 * If the export fails, false is returned.
 */
bool
CSBMLExporter::exportModel(CDataModel& dataModel,
                           const std::string& filename,
                           unsigned int sbmlLevel,
                           unsigned int sbmlVersion,
                           bool overwrite)
{
  bool success = true;
  /* create a string that represents the SBMLDocument */
  std::string str = this->exportModelToString(dataModel, sbmlLevel, sbmlVersion);

  if (!str.empty())
    {
      /* check if the file already exists.
         If yes, write if overwrite is true,
         else create an appropriate  CCopasiMessage. */
      std::ifstream testInfile(CLocaleString::fromUtf8(filename).c_str(), std::ios::in);

      if (testInfile && !overwrite)
        {
          // create a CCopasiMessage with the appropriate error
          CCopasiMessage(CCopasiMessage::ERROR, MCDirEntry + 1, filename.c_str());
          return false;
        }

      /* write the document to a file */
      std::ofstream outfile(CLocaleString::fromUtf8(filename).c_str(), std::ios::out | std::ios::trunc);
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
const std::vector<SBMLIncompatibility> CSBMLExporter::isModelSBMLCompatible(
  const CDataModel& dataModel,
  int sbmlLevel,
  int sbmlVersion,
  std::map<std::string, const SBase*>& idMap)
{
  const CModel* pModel = dataModel.getModel();
  std::vector<SBMLIncompatibility> result;

  if (pModel == NULL) return result;

  // general checks
  // check if there is a species with an ode rule that is in a nonfixed
  // compartment
  checkForODESpeciesInNonfixedCompartment(dataModel, result);

  // check if the model contains references to model entities that can not be
  // represented in SBML like the initial value of something as opposed to the
  // transient value
  // check if the model contains calls to functions that are not supported in
  // the given version of SBML
  CModelEntity::Status status;
  const CExpression* pExpression = NULL;
  std::set<std::string> usedFunctionNames;
  CDataVectorNS<CCompartment>::const_iterator compIt = pModel->getCompartments().begin();
  CDataVectorNS<CCompartment>::const_iterator compEndit = pModel->getCompartments().end();

  while (compIt != compEndit)
    {
      status = compIt->getStatus();

      if (status == CModelEntity::Status::ODE || status == CModelEntity::Status::ASSIGNMENT)
        {
          pExpression = compIt->getExpressionPtr();
          assert(pExpression != NULL);

          if (pExpression != NULL)
            {
              // check for unsupported object references and unsupported function
              // calls
              usedFunctionNames.clear();
              CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, idMap, std::string("compartment with name \"" + compIt->getObjectName() + "\""));
              CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
            }
        }

      pExpression = compIt->getInitialExpressionPtr();

      if (pExpression != NULL)
        {
          // check for unsupported object references and unsupported function
          // calls
          CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, idMap, std::string("initial expression for compartment named \"" + compIt->getObjectName() + "\""));
          usedFunctionNames.clear();
          CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
        }

      ++compIt;
    }

  CDataVector<CMetab>::const_iterator metabIt = pModel->getMetabolites().begin();
  CDataVector<CMetab>::const_iterator metabEndit = pModel->getMetabolites().end();

  while (metabIt != metabEndit)
    {
      status = metabIt->getStatus();

      if (status == CModelEntity::Status::ODE || status == CModelEntity::Status::ASSIGNMENT)
        {
          pExpression = metabIt->getExpressionPtr();
          assert(pExpression != NULL);

          if (pExpression != NULL)
            {
              // check for unsupported object references and unsupported function
              // calls
              CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, idMap, std::string("rule for species named \"" + metabIt->getObjectName() + "\""));
              usedFunctionNames.clear();
              CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
            }
        }

      pExpression = metabIt->getInitialExpressionPtr();

      if (pExpression != NULL)
        {
          // check for unsupported object references and unsupported function
          // calls
          CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, idMap, std::string("initial species for metabolite named \"" + metabIt->getObjectName() + "\""));
          usedFunctionNames.clear();
          CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
        }

      ++metabIt;
    }

  CDataVectorN<CModelValue>::const_iterator mvIt = pModel->getModelValues().begin();
  CDataVectorN<CModelValue>::const_iterator mvEndit = pModel->getModelValues().end();

  while (mvIt != mvEndit)
    {
      status = mvIt->getStatus();

      if (status == CModelEntity::Status::ODE || status == CModelEntity::Status::ASSIGNMENT)
        {
          pExpression = mvIt->getExpressionPtr();
          assert(pExpression != NULL);

          if (pExpression != NULL)
            {
              // check for unsupported object references and unsupported function
              // calls
              CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, idMap, std::string("rule for global parameter named \"" + mvIt->getObjectName() + "\""));
              usedFunctionNames.clear();
              CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
            }
        }

      pExpression = mvIt->getInitialExpressionPtr();

      if (pExpression != NULL)
        {
          // check for unsupported object references and unsupported function
          // calls
          CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, idMap, std::string("initial expression for global parameter named \"" + mvIt->getObjectName() + "\""));
          usedFunctionNames.clear();
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
  CDataVectorN<CEvent>::const_iterator eventIt, eventEndit;

  switch (sbmlLevel)
    {
      case 2:
        // check all events
        eventIt = pModel->getEvents().begin();
        eventEndit = pModel->getEvents().end();

        while (eventIt != eventEndit)
          {
            CSBMLExporter::isEventSBMLCompatible(eventIt, dataModel, sbmlLevel, sbmlVersion, result, idMap);
            ++eventIt;
          }

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

bool CSBMLExporter::createEvents(CDataModel& dataModel)
{
  if (this->mSBMLLevel == 1)
    {
      // only fail if we have an event!
      bool result = CSBMLExporter::checkForEvents(dataModel, this->mIncompatibilities);

      if (!result)
        CCopasiMessage(CCopasiMessage::ERROR, "This model uses events that cannot be exported to SBML Level 1.");

      return true;
    }

  // bail early
  if (dataModel.getModel() == NULL)
    return false;

  Model* pSBMLModel = this->mpSBMLDocument->getModel();

  if (pSBMLModel == NULL)
    return false;

  // remove all events from the SBML model and put them in a set
  std::set<Event*> eventSet;

  while (pSBMLModel->getNumEvents() != 0)
    {
      Event* pEvent = pSBMLModel->getListOfEvents()->remove(pSBMLModel->getNumEvents() - 1);
      assert(pEvent != NULL);
      eventSet.insert(pEvent);
    }

  const CDataVectorN<CEvent>& events = dataModel.getModel()->getEvents();

  CDataVectorN<CEvent>::const_iterator it = events.begin(), endit = events.end();

  Event* pSBMLEvent = NULL;

  std::map<const CDataObject*, SBase*>::const_iterator pos;

  while (it != endit)
    {
      // find the old event if there is one
      pos = this->mCOPASI2SBMLMap.find(it);

      if (pos != this->mCOPASI2SBMLMap.end())
        {
          pSBMLEvent = dynamic_cast<Event*>(pos->second);
        }
      else
        {
          pSBMLEvent = NULL;
        }

      // remove the event from the set
      if (pSBMLEvent) eventSet.erase(pSBMLEvent);

      this->createEvent(*it, pSBMLEvent, dataModel);
      ++it;

      ++mCurrentStepCounter;

      if (reportCurrentProgressOrStop())
        return false;
    }

  // make sure events that have already been deleted do not get
  // exported
  std::set<Event*>::iterator it2 = eventSet.begin(), endit2 = eventSet.end();

  while (it2 != endit2)
    {
      delete *it2;
      ++it2;
    }

  return true;
}

void CSBMLExporter::createEvent(const CEvent& event, Event* pSBMLEvent, CDataModel& dataModel)
{
  // once events are functional, we create them here
  // don't forget to call replaceSpeciesReferences
  // on all mathematical expressions

  // first check if we already have a corresponding event from an earlier
  // import or export
  // if none is found, we create a new event object
  if (pSBMLEvent == NULL)
    {
      pSBMLEvent = this->mpSBMLDocument->getModel()->createEvent();
    }
  else
    {
      // Read the event to the model
      if (this->mpSBMLDocument->getModel()->getListOfEvents()->appendAndOwn(pSBMLEvent) != LIBSBML_OPERATION_SUCCESS)
        {
          // the existing event is not valid and cannot be added to the model, delete and create a new one instead
          delete pSBMLEvent;
          pSBMLEvent = this->mpSBMLDocument->getModel()->createEvent();
        }
    }

  if (pSBMLEvent == NULL)
    {
      std::stringstream str; str << "The event: '" << event.getObjectName() << "' could not be exported";
      CCopasiMessage(CCopasiMessage::ERROR, str.str().c_str());
      return;
    }

  // add the object to the COPASI2SBMLMap
  this->mCOPASI2SBMLMap[&event] = pSBMLEvent;

  // a)  we set the name and the id
  if (!pSBMLEvent->isSetId())
    {
      std::string sbmlId = CSBMLExporter::createUniqueId(this->mIdMap, event.getObjectName(), false);
      this->mIdMap.insert(std::pair<const std::string, const SBase*>(sbmlId, pSBMLEvent));
      pSBMLEvent->setId(sbmlId);
      event.setSBMLId(sbmlId);
    }

  // The attribute 'useValuesfromTriggerTime' is mandatory in L3V1
  if (this->mSBMLLevel > 2)
    {
      pSBMLEvent->setUseValuesFromTriggerTime(event.getDelayAssignment());
    }

  // if the event came from an SBML L3 model, we have to make sure that the
  // priority is not set when we export the event, otherwise the exported model
  // and the COPASI model will not behave the same.
  if (this->mSBMLLevel > 2)
    {
      pSBMLEvent->setPriority(NULL);
    }

  // if the name doesn't consists of whitespace only, we set the name
  if (event.getObjectName().find_first_not_of("\t\r\n ") != std::string::npos)
    {
      pSBMLEvent->setName(event.getObjectName());
    }

  // b) we check the trigger expression and export the trigger
  const CExpression* pExpression = event.getTriggerExpressionPtr();
  assert(pExpression != NULL);
  std::vector<SBMLIncompatibility> result;
  CSBMLExporter::isExpressionSBMLCompatible(*pExpression
      , dataModel
      , this->mSBMLLevel
      , this->mSBMLVersion
      , result
      , mIdMap
      , std::string("event trigger for event with id\"+" + event.getSBMLId() + "\"")
      , false
      , &mInitialValueMap);

  // collect directly used functions
  if (result.empty())
    {
      std::set<std::string> directlyUsedFunctionNames;
      CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), directlyUsedFunctionNames);
      std::set<CFunction*> usedFunctions = CSBMLExporter::createFunctionSetFromFunctionNames(directlyUsedFunctionNames, CRootContainer::getFunctionList());

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
    }
  else
    {
      this->mIncompatibilities.insert(this->mIncompatibilities.end(), result.begin(), result.end());

      if (!this->mIncompleteExport)
        {
          this->outputIncompatibilities();
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 60, "trigger expression", "event", event.getObjectName().c_str());
        }
    }

  const std::string& changedExpression = convertExpression(pExpression->getInfix(), mInitialValueMap);

  CEvaluationTree tree;

  tree.setInfix(changedExpression);

  const CEvaluationNode* pOrigNode = tree.getRoot();

  //const CEvaluationNode* pOrigNode = pExpression->getRoot();

  if (pOrigNode->mainType() == CEvaluationNode::MainType::INVALID)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 70, "trigger", "event", event.getObjectName().c_str());
    }

  // the next few lines replace references to species depending on whether
  // it is a reference to an amount or a reference to a concentration.
  // Other factors that influence this replacement are if the model
  // contains variable volumes or if the quantity units are set to CUnit::number
  pOrigNode = this->replaceSpeciesReferences(pOrigNode, dataModel);
  assert(pOrigNode != NULL);
  ASTNode* pNode = this->convertToASTNode(pOrigNode, dataModel);
  delete pOrigNode;
  // convert local parameters that are referenced in an expression to global
  // parameters
  this->replace_local_parameters(pNode, dataModel);

  if (pNode != NULL)
    {
      Trigger* pTrigger = pSBMLEvent->createTrigger();
      pTrigger->setMath(pNode);

      // we need to make sure that the initial value of the trigger is set to true
      // as well as the persistent flag
      // for L3 event because otherwise the exported model will not do the same as
      // the model in COPASI
      if (this->mSBMLLevel > 2)
        {
          pTrigger->setInitialValue(!event.getFireAtInitialTime());
          pTrigger->setPersistent(event.getPersistentTrigger());
        }

      delete pNode;
    }
  else
    {
      if (this->mIncompleteExport != true)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 60, "trigger", "event", event.getObjectName().c_str());
        }
    }

  // c) we check the delay expression and export it if it is set
  pExpression = event.getDelayExpressionPtr();
  const std::string delayInfix = pExpression == NULL ? "" : pExpression->getInfix();

  if (!delayInfix.empty())
    {
      result.clear();
      CSBMLExporter::isExpressionSBMLCompatible(*pExpression
          , dataModel
          , this->mSBMLLevel
          , this->mSBMLVersion
          , result
          , mIdMap
          , std::string("event delay for event with id\"+" + event.getSBMLId() + "\"")
          , false
          , &mInitialValueMap);

      // collect directly used functions
      if (result.empty())
        {
          std::set<std::string> directlyUsedFunctionNames;
          CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), directlyUsedFunctionNames);
          std::set<CFunction*> usedFunctions = CSBMLExporter::createFunctionSetFromFunctionNames(directlyUsedFunctionNames, CRootContainer::getFunctionList());

# if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
          {
            it = usedFunctions.begin();
            usedFunctions.end();

            for (; it != end; ++it)
              this->mUsedFunctions.insert(*it);
          }
#else
          this->mUsedFunctions.insert(usedFunctions.begin(), usedFunctions.end());
#endif
        }
      else
        {
          this->mIncompatibilities.insert(this->mIncompatibilities.end(), result.begin(), result.end());

          if (!this->mIncompleteExport)
            {
              this->outputIncompatibilities();
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 60, "delay expression", "event", event.getObjectName().c_str());
            }
        }

      //pOrigNode = pExpression->getRoot();
      const std::string& changedExpression = convertExpression(pExpression->getInfix(), mInitialValueMap);
      CEvaluationTree tree;
      tree.setInfix(changedExpression);
      const CEvaluationNode* pOrigNode = tree.getRoot();

      if (pOrigNode->mainType() == CEvaluationNode::MainType::INVALID)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 70, "delay", "event", event.getObjectName().c_str());
        }

      // the next few lines replace references to species depending on whether
      // it is a reference to an amount or a reference to a concentration.
      // Other factors that influence this replacement are if the model
      // contains variable volumes or if the quantity units are set to CUnit::number
      pOrigNode = this->replaceSpeciesReferences(pOrigNode, dataModel);
      assert(pOrigNode != NULL);
      pNode = this->convertToASTNode(pOrigNode, dataModel);
      delete pOrigNode;
      // convert local parameters that are referenced in an expression to global
      // parameters
      this->replace_local_parameters(pNode, dataModel);

      if (pNode != NULL)
        {
          Delay* pDelay = new Delay(this->mSBMLLevel, this->mSBMLVersion);
          pDelay->setMath(pNode);
          pSBMLEvent->setDelay(pDelay);
          delete pNode;
          delete pDelay;

          if (this->mSBMLLevel == 2 && this->mSBMLVersion >= 4)
            {
              pSBMLEvent->setUseValuesFromTriggerTime(event.getDelayAssignment());
            }
          // if the delayAssignment is set to false, we have a problem
          // because the model semantic changes on export
          else if (event.getDelayAssignment() == false &&
                   this->mSBMLLevel <= 2 &&
                   this->mSBMLVersion <= 3)
            {
              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 77, event.getObjectName().c_str(), this->mSBMLLevel, this->mSBMLVersion);
            }
        }
      else
        {
          if (this->mIncompleteExport != true)
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 60, "delay", "event", event.getObjectName().c_str());
            }
        }
    }

  // export all event assignments
  this->exportEventAssignments(event, pSBMLEvent, dataModel);

  // check if the event has event assignments, if not, we have to delete
  // the event and create an error message (for SBML Levels < 3)
  if (pSBMLEvent->getNumEventAssignments() == 0 && mpSBMLDocument->getLevel() < 3)
    {
      unsigned int i, iMax = this->mpSBMLDocument->getModel()->getNumEvents();

      // the following code does not check if the correct pointer is found
      // but this should not be a problem
      for (i = 0; i < iMax; ++i)
        {
          if (this->mpSBMLDocument->getModel()->getEvent(i) == pSBMLEvent)
            {
              this->mpSBMLDocument->getModel()->getListOfEvents()->remove(i);
            }
        }

      delete pSBMLEvent;
      this->mCOPASI2SBMLMap.erase(&event);
      pSBMLEvent = NULL;

      CCopasiMessage(CCopasiMessage::WARNING, "The event '%s' contained no event assignments, this is only supported for SBML Level 3 onwards. The event has not been exported.", event.getObjectName().c_str());
    }

  if (pSBMLEvent != NULL)
    {
      CSBMLExporter::setSBMLNotes(pSBMLEvent, &event);
      CSBMLExporter::updateMIRIAMAnnotation(&event, pSBMLEvent, this->mMetaIdMap);
    }
}

void CSBMLExporter::exportEventAssignments(const CEvent& event, Event* pSBMLEvent, CDataModel& dataModel)
{
  //  we export all event assignments
  //    i) delete all event assignments and add them to a vector (see rules)
  std::map<std::string, EventAssignment*> assignmentMap;

  while (pSBMLEvent->getNumEventAssignments() != 0)
    {
      EventAssignment* pAssignment = pSBMLEvent->getEventAssignment(pSBMLEvent->getNumEventAssignments() - 1);
      assert(pAssignment != NULL);
      assignmentMap[pAssignment->getVariable()] = pAssignment;
      pSBMLEvent->getListOfEventAssignments()->remove(pSBMLEvent->getNumEventAssignments() - 1);
    }

  CDataVectorN< CEventAssignment >::const_iterator itAssignment = event.getAssignments().begin();
  CDataVectorN< CEventAssignment >::const_iterator endAssignment = event.getAssignments().end();

  for (; itAssignment != endAssignment; ++itAssignment)
    {
      //        now we have to get the object for the key, check if the object is a
      //        compartment, species or global parameter,
      const CDataObject* pObject = CObjectInterface::DataObject(event.getObjectDataModel()->getObject(itAssignment->getTargetCN()));
      const CDataObject * pObjectReference = NULL;
      std::string objectType = pObject->getObjectType();

      if (objectType == "Reference")
        {
          pObjectReference = pObject;
          pObject = pObject->getObjectParent();
          objectType = pObject->getObjectType();
        }

      if (objectType != "Compartment" && objectType != "Metabolite" && objectType != "ModelValue")
        {
          // create an error message that only compartment, species and
          // global parameters can be used in an event assignment
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 32, std::string("event assignment for event called \"" + event.getObjectName() + "\"").c_str(), pObject->getObjectName().c_str());
        }

      std::map<const CDataObject*, SBase*>::const_iterator pos = this->mCOPASI2SBMLMap.find(pObject);

      if (pos == this->mCOPASI2SBMLMap.end())
        {
          // create a general error message that the export of an event
          // assignment failed and continue
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 73, std::string("event assignment for object called \"" + pObject->getObjectName() + "\" in evend named \"" + event.getObjectName() + "\"").c_str(), "event assignment");
          continue;
        }

      //  iii) for each assignment, check if the object that variable points to has been exported
      SBase* pSBase = pos->second;
      assert(pSBase != NULL);

      if (this->mHandledSBMLObjects.find(pSBase) == this->mHandledSBMLObjects.end())
        {
          // create an error message that the event assignment is for an object
          // that is no longer part of the model
          // ignore it and continue
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 57, std::string("event assignment in event called \"" + event.getObjectName() + "\"").c_str(), pSBase->getId().c_str());
          continue;
        }

      // set the constant flag to false
      Compartment* pSBMLCompartment = NULL;
      Species* pSBMLSpecies = NULL;
      Parameter* pSBMLParameter = NULL;

      switch (pSBase->getTypeCode())
        {
          case SBML_COMPARTMENT:
            pSBMLCompartment = dynamic_cast<Compartment*>(pSBase);
            assert(pSBMLCompartment != NULL);

            if (pSBMLCompartment->getConstant() == true)
              {
                pSBMLCompartment->setConstant(false);
              }

            break;

          case SBML_SPECIES:
            pSBMLSpecies = dynamic_cast<Species*>(pSBase);
            assert(pSBMLSpecies != NULL);

            if (pSBMLSpecies->getConstant() == true)
              {
                pSBMLSpecies->setConstant(false);
              }

            break;

          case SBML_PARAMETER:
            pSBMLParameter = dynamic_cast<Parameter*>(pSBase);
            assert(pSBMLParameter != NULL);

            if (pSBMLParameter->getConstant() == true)
              {
                pSBMLParameter->setConstant(false);
              }

            break;

          default:
            fatalError();
            break;
        }

      std::string sbmlId = pSBase->getId();
      assert(sbmlId.find_first_not_of("\t\r\n ") != std::string::npos);
      std::map<std::string, EventAssignment*>::iterator pos2 = assignmentMap.find(sbmlId);
      EventAssignment* pAssignment = NULL;

      if (pos2 != assignmentMap.end())
        {
          pAssignment = dynamic_cast<EventAssignment*>(pos2->second);
          assert(pAssignment != NULL);
          pSBMLEvent->getListOfEventAssignments()->appendAndOwn(pAssignment);
          // remove the entry from the event assignment map
          assignmentMap.erase(pos2);
        }

      if (pAssignment == NULL)
        {
          pAssignment = pSBMLEvent->createEventAssignment();
        }

      pAssignment->setVariable(sbmlId);
      //    iv) for each assignment, check the assignment expression if it is valid
      const CExpression * pExpression = itAssignment->getExpressionPtr();

      if (pExpression != NULL)
        {
          std::vector<SBMLIncompatibility> result;
          CSBMLExporter::isExpressionSBMLCompatible(
            *pExpression
            , dataModel
            , this->mSBMLLevel
            , this->mSBMLVersion
            , result
            , mIdMap
            , std::string("event assignment for variable \"" + sbmlId + "\" in event with id\"+" + event.getSBMLId() + "\"")
            , false
            , &mInitialValueMap);

          // collect directly used functions
          if (result.empty())
            {
              std::set<std::string> directlyUsedFunctionNames;
              CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), directlyUsedFunctionNames);
              std::set<CFunction*> usedFunctions = CSBMLExporter::createFunctionSetFromFunctionNames(directlyUsedFunctionNames, CRootContainer::getFunctionList());

# if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
              {
                it = usedFunctions.begin();
                usedFunctions.end();

                for (; it != end; ++it)
                  this->mUsedFunctions.insert(*it);
              }
#else
              this->mUsedFunctions.insert(usedFunctions.begin(), usedFunctions.end());
#endif
            }
          else
            {
              this->mIncompatibilities.insert(this->mIncompatibilities.end(), result.begin(), result.end());

              if (!this->mIncompleteExport)
                {
                  this->outputIncompatibilities();
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 60, std::string("event assignment for variable with id \"" + sbmlId + "\"").c_str(), "event", event.getObjectName().c_str());
                }
            }

          //const CEvaluationNode* pOrigNode = pExpression->getRoot();
          const std::string& changedExpression = convertExpression(pExpression->getInfix(), mInitialValueMap);
          CEvaluationTree tree;
          tree.setInfix(changedExpression);
          const CEvaluationNode* pOrigNode = tree.getRoot();

          if (pOrigNode->mainType() == CEvaluationNode::MainType::INVALID)
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 70, std::string("event assignment for variable with id \"" + sbmlId + "\"").c_str(), "event", event.getObjectName().c_str());
            }

          // the next few lines replace references to species depending on whether
          // it is a reference to an amount or a reference to a concentration.
          // Other factors that influence this replacement are if the model
          // contains variable volumes or if the quantity units are set to CUnit::number
          pOrigNode = this->replaceSpeciesReferences(pOrigNode, dataModel);
          assert(pOrigNode != NULL);
          // check if the assignment belongs to an amount species
          // if so, multiply the expression be the volume of the compartment that
          // the species belongs to.

          const CMetab* pMetab = dynamic_cast<const CMetab*>(pObject);

          if (pMetab != NULL)
            {
              std::map<const CDataObject*, SBase*>::const_iterator pos = this->mCOPASI2SBMLMap.find(pObject);
              assert(pos != this->mCOPASI2SBMLMap.end());

              if (dynamic_cast<const Species*>(pos->second)->getHasOnlySubstanceUnits() == true)
                {
                  const CCompartment* pCompartment = pMetab->getCompartment();

                  CEvaluationNode* pNode = CSBMLExporter::multiplyByObject(pOrigNode, pCompartment->getValueReference());
                  assert(pNode != NULL);

                  if (pNode != NULL)
                    {
                      delete pOrigNode;
                      pOrigNode = pNode;
                    }
                }
            }

          ASTNode* pNode = this->convertToASTNode(pOrigNode, dataModel);
          delete pOrigNode;
          // convert local parameters that are referenced in an expression to global
          // parameters
          this->replace_local_parameters(pNode, dataModel);

          if (pNode != NULL)
            {

              if (pMetab && pObjectReference && pObjectReference == pMetab->getValueReference())
                {
                  // mark assignment as particle number assignment
                  pAssignment->setAnnotation("<particleNumber xmlns=\"http://copasi.org/eventAssignment\" />");

                  // divide by the compartment volume and the avogadro number
                  ASTNode* pDivide = new ASTNode(AST_DIVIDE);
                  ASTNode * pTimes = new ASTNode(AST_TIMES);
                  auto * name = new ASTNode(AST_NAME);
                  name->setName(pMetab->getCompartment()->getSBMLId().c_str());
                  pTimes->addChild(name);
                  ASTNode * pFactor = new ASTNode(AST_REAL);
                  pFactor->setValue(dataModel.getModel()->getQuantity2NumberFactor());
                  pTimes->addChild(pFactor);
                  pDivide->addChild(pNode);
                  pDivide->addChild(pTimes);

                  // and use adjusted expression below
                  pNode = pDivide;
                }

              if (pAssignment->setMath(pNode) != LIBSBML_OPERATION_SUCCESS)
                CCopasiMessage(CCopasiMessage::WARNING, "event assignment for variable with id '%s' (in event '%s') with expression '%s' could not be set.", sbmlId.c_str(), event.getObjectName().c_str(), pExpression->getInfix().c_str());

              delete pNode;
            }
          else
            {
              if (this->mIncompleteExport != true)
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 60, std::string("event assignment for variable with id \"" + sbmlId + "\"").c_str(), "event", event.getObjectName().c_str());
                }
            }
        }
      else
        {
          // create an error message that the event assignment could not be
          // created and continue
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 73, std::string("event assignment for variable with id \"" + sbmlId + "\"").c_str(), "event assignment");
          continue;
        }
    }

  //    v) delete the old unused assignments
  std::map<std::string, EventAssignment*>::iterator it = assignmentMap.begin(), endit = assignmentMap.end();

  while (it != endit)
    {
      delete it->second;
      ++it;
    }
}

bool CSBMLExporter::checkForEvents(const CDataModel & dataModel,
                                   std::vector< SBMLIncompatibility > & result)
{
  if (dataModel.getModel() != NULL && !dataModel.getModel()->getEvents().empty())
    {
      result.push_back(SBMLIncompatibility(7));
      return false;
    }

  return true;
}

void CSBMLExporter::updateCOPASI2SBMLMap(const CDataModel& dataModel)
{
  // make sure the idMap is already up to date
  // go through the existing map and create a new one with all SBML
  // objects updated with objects from the copied
  // model
  this->mCOPASI2SBMLMap.clear();
  std::map<const CDataObject*, SBase*>& modelMap = const_cast<CDataModel&>(dataModel).getCopasi2SBMLMap();
  std::map<const CDataObject*, SBase*>::const_iterator it = modelMap.begin();
  std::map<const CDataObject*, SBase*>::const_iterator endit = modelMap.end();

  while (it != endit)
    {
      const SBase* element = it->second;
      std::string elementId = element == NULL ? "" :
                              element->getLevel() == 1 ? element->getName()
                              : element->getId();

      std::map<std::string, const SBase*>::iterator pos = elementId.empty() ? mIdMap.end() :  this->mIdMap.find(elementId);

      if (pos != this->mIdMap.end())
        {
          this->mCOPASI2SBMLMap.insert(std::pair<const CDataObject * const, SBase*>(it->first, const_cast<SBase*>(pos->second)));
        }

      ++it;
    }
}

KineticLaw* CSBMLExporter::createKineticLaw(const CReaction& reaction, CDataModel& dataModel, unsigned int level, unsigned int version)
{
  KineticLaw* pKLaw = NULL;

  if (!pKLaw)
    {
      /* create a new KineticLaw */
      pKLaw = new KineticLaw(level, version);
    }

  // create the local parameters
  size_t i, iMax = reaction.getFunctionParameters().size();

  for (i = 0; i < iMax; ++i)
    {
      const CFunctionParameter* pPara = reaction.getFunctionParameters()[i];
      // if the reaction calls a general function, all call parameters have a usage of VARIABLE
      // So local parameters will also have a usage of VARIABLE instead of PARAMETER

      if (pPara->getUsage() == CFunctionParameter::Role::PARAMETER ||
          (reaction.getFunction() != NULL &&
           reaction.getFunction()->isReversible() == TriUnspecified &&
           pPara->getUsage() == CFunctionParameter::Role::VARIABLE))
        {
          // only create a parameter if it is a local parameter,
          // and if it is not in the replacement map
          // otherwise the parameter already has been created
          if (reaction.isLocalParameter(i))
            {
              std::vector< const CDataObject * > v = reaction.getParameterObjects(pPara->getObjectName());
              assert(v.size() == 1);
              const CDataObject * pTmpObject = v[0];
              assert(pTmpObject != NULL);
              const CCopasiParameter * pLocalParameter = dynamic_cast< const CCopasiParameter * >(pTmpObject);
              assert(pLocalParameter != NULL);

              if (this->mParameterReplacementMap.find(pLocalParameter->getStringCN()) == this->mParameterReplacementMap.end())
                {
                  // starting with SBML Level 3, the parameters of a kinetic law are expressed in
                  // libsbml 4.1 does not handle this in a nice way,
                  // so way have to distinguish between the levels we export
                  // Actually here we could probably have gotten away with the old code, but
                  // better safe than sorry
                  Parameter* pSBMLPara = NULL;

                  if (this->mSBMLLevel > 2)
                    {
                      pSBMLPara = pKLaw->createLocalParameter();
                    }
                  else
                    {
                      pSBMLPara = pKLaw->createParameter();
                    }

                  pSBMLPara->setId(pPara->getObjectName());

                  // don't call setName on level 1 objects because this will also
                  // change the id
                  if (this->mpSBMLDocument->getLevel() > 1)
                    {
                      pSBMLPara->setName(pPara->getObjectName());
                    }

                  double value = reaction.getParameterValue(pPara->getObjectName());

                  // if the value is NaN, leave the parameter value unset.
                  if (!std::isnan(value))
                    {
                      pSBMLPara->setValue(value);
                    }
                }
            }
        }
    }

  // the next few lines replace references to species depending on whether
  // it is a reference to an amount or a reference to a concentration.
  // Other factors that influence this replacement are if the model
  // contains variable volumes or if the quantity units are set to CUnit::number
  CEvaluationNode* pExpression = CSBMLExporter::createKineticExpression(const_cast<CFunction*>(reaction.getFunction()), reaction.getParameterObjects());

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
      // since toAST in CEvaluationNodeObject sets the CN of local parameters
      // as the name of the node, we have to go and replace all node names
      // that have a common name that is the CN of a local parameter
      this->restore_local_parameters(pNode, dataModel);
      delete pOrigNode;
      assert(pNode != NULL);

      if (reaction.getEffectiveKineticLawUnitType() == CReaction::KineticLawUnit::ConcentrationPerTime)
        {
          const CCompartment* compartment = reaction.getScalingCompartment() != NULL ? reaction.getScalingCompartment() :
                                            (!reaction.getChemEq().getSubstrates().empty()) ? (reaction.getChemEq().getSubstrates()[0].getMetabolite()->getCompartment()) : (reaction.getChemEq().getProducts()[0].getMetabolite()->getCompartment());

          // check if the importer has added a division by the volume
          // if so remove it instead of multiplying again
          ASTNode* pTNode = CSBMLExporter::isDividedByVolume(pNode, compartment->getSBMLId());

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
              pVNode->setName(compartment->getSBMLId().c_str());
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

      for (i = 0; i < iMax; ++i)
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

CEvaluationNode* CSBMLExporter::createKineticExpression(CFunction* pFun, const std::vector<std::vector<const CDataObject *> >& arguments)
{
  if (!pFun || pFun->getVariables().size() != arguments.size()) fatalError();

  CEvaluationNode* pResult;

  if (pFun->getType() == CEvaluationTree::MassAction)
    {
      pResult = CSBMLExporter::createMassActionExpression(arguments, pFun->isReversible() == TriTrue);
    }
  else
    {
      CEvaluationNodeCall* pFunctionCall = new CEvaluationNodeCall(CEvaluationNode::SubType::FUNCTION, pFun->getObjectName());
      this->mUsedFunctions.insert(pFun);
      size_t i, iMax = arguments.size();
      std::string cn;

      for (i = 0; i < iMax; ++i)
        {
          if (arguments[i].size() != 1) fatalError(); // we can't have arrays here.

          const CDataObject* pObject = arguments[i][0];

          if (!pObject) fatalError();

          if (dynamic_cast<const CModel*>(pObject) != NULL)
            {
              cn = "<" + pObject->getStringCN() + ",Reference=Time>";
            }
          else if (dynamic_cast<const CCompartment*>(pObject) != NULL)
            {
              cn = "<" + pObject->getStringCN() + ",Reference=Volume>";
            }
          else if (dynamic_cast<const CMetab*>(pObject) != NULL)
            {
              cn = "<" + pObject->getStringCN() + ",Reference=Concentration>";
            }
          else if (dynamic_cast<const CModelValue*>(pObject) != NULL)
            {
              cn = "<" + pObject->getStringCN() + ",Reference=Value>";
            }
          else if (dynamic_cast<const CReaction*>(pObject) != NULL)
            {
              cn = "<" + pObject->getStringCN() + ",Reference=Flux>";
            }
          else if (dynamic_cast<const CCopasiParameter*>(pObject) != NULL)
            {
              // local parameter of a reaction
              // must set the node content to the SBML id if the parameter
              cn = "<" + pObject->getStringCN() + ">";
            }
          else
            {
              cn = "<" + pObject->getStringCN() + ">";
            }

          pFunctionCall->addChild(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, cn));
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
ASTNode* CSBMLExporter::createTimesTree(const CDataVector<CChemEqElement >& vect, unsigned int pos)
{
  ASTNode* pNode = NULL;
  double multiplicity = vect[pos].getMultiplicity();

  if (pos == vect.size() - 1)
    {
      pNode = new ASTNode(AST_NAME);
      const CMetab* pMetab = vect[pos].getMetabolite();
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
      const CMetab* pMetab = vect[pos].getMetabolite();
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

  if (pRootNode->mainType() == CEvaluationNode::MainType::CALL)
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
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Dependency loop found in function definitions.");
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
              CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 15, (*it).c_str());
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

std::vector<const CModelEntity*> CSBMLExporter::orderRules(const CDataModel& dataModel)
{
  // make sure the vector of rules is filled
  std::map<const CModelEntity*, std::set<const CModelEntity*> > dependencyMap;
  std::vector<const CModelEntity*>::iterator it = this->mAssignmentVector.begin();
  std::vector<const CModelEntity*>::iterator endit = this->mAssignmentVector.end();

  while (it != endit)
    {
      const CExpression* pExpr = (*it)->getExpressionPtr();
      assert(pExpr != NULL);
      std::set<const CModelEntity*> dependencies;

      try
        {
          CSBMLExporter::findModelEntityDependencies(pExpr->getRoot(), dataModel, dependencies);
        }
      catch (...)
        {
          std::stringstream str;
          str << "The rule for '" << (*it)->getObjectName()
              << "' cannot be exported, as its expression is invalid.";
          throw CCopasiMessage(CCopasiMessage::EXCEPTION, str.str().c_str());
        }

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
  std::vector<const CModelEntity*> orderedRules;
  // remove all dependencies that don't have assignment rules themselves
  std::map<const CModelEntity*, std::set<const CModelEntity*> > reducedDependencyMap;
  std::map<const CModelEntity*, std::set<const CModelEntity*> >::iterator mapIt = dependencyMap.begin(), mapEndit = dependencyMap.end();

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
              std::vector<const CModelEntity*>::iterator vIt = orderedRules.begin(), vEndit = orderedRules.end();

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

void CSBMLExporter::findModelEntityDependencies(const CEvaluationNode* pNode, const CDataModel& dataModel, std::set<const CModelEntity*>& dependencies)
{
  if (pNode == NULL) return;

  if (pNode->mainType() == CEvaluationNode::MainType::OBJECT)
    {
      const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
      assert(pObjectNode != NULL);

      if (pObjectNode != NULL)
        {
          const CDataObject* pObject = CObjectInterface::DataObject(dataModel.getObjectFromCN(pObjectNode->getObjectCN()));

          if (!pObject)
            {
              fatalError();
            }

          if (pObject->hasFlag(CDataObject::Reference))
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

  for (i = 0; i < iMax; ++i)
    {
      pRule = pModel->getRule(i);
      assert(pRule != NULL);
      const ASTNode* pMath = pRule->getMath();
      assert(pMath != NULL);
      std::string message = "rule for object with id \"";
      message += pRule->getVariable();
      message += "\"";
      ASTNode* pNewMath = CSBMLExporter::convertASTTreeToLevel1(pMath, this->mExportedFunctions, message);
      assert(pNewMath != NULL);

      if (pNewMath != NULL)
        {
          pRule->setMath(pNewMath);
          delete pNewMath;
        }
    }

  iMax = pModel->getNumReactions();

  for (i = 0; i < iMax; ++i)
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
          ASTNode* pNewMath = CSBMLExporter::convertASTTreeToLevel1(pMath, this->mExportedFunctions, message);
          assert(pNewMath != NULL);

          if (pNewMath != NULL)
            {
              pLaw->setMath(pNewMath);
              delete pNewMath;
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
        else if (pNode->getReal() > std::numeric_limits< C_FLOAT64 >::max())
          {
            // replace by 1/0
            pResult = new ASTNode(AST_RATIONAL);
            pResult->setValue(1L, 0L);
          }
        else if (pNode->getReal() < - std::numeric_limits< C_FLOAT64 >::max())
          {
            // replace by -1/0
            pResult = new ASTNode(AST_RATIONAL);
            pResult->setValue(-1L, 0L);
          }
        else
          {
            pResult = pNode->deepCopy();
          }

        break;

      default:
        // copy the node
        pResult = ConverterASTNode::shallowCopy(pNode);
        iMax = pNode->getNumChildren();

        for (i = 0; i < iMax; ++i)
          {
            pChild = CSBMLExporter::replaceL1IncompatibleNodes(pNode->getChild(i));

            if (pChild != NULL)
              {
                pResult->addChild(pChild);
              }
            else
              {
                delete pResult;
                pResult = NULL;
              }
          }

        break;
    }

  return pResult;
}

ASTNode* CSBMLExporter::convertASTTreeToLevel1(const ASTNode* pNode, const ListOfFunctionDefinitions& functions, std::string& message)
{
  ASTNode* pExpanded = create_expression(pNode, &functions);

  if (pExpanded != NULL)
    {
      ASTNode* pReplaced = CSBMLExporter::replaceL1IncompatibleNodes(pExpanded);
      delete pExpanded;

      if (pReplaced == NULL)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 62, message.c_str());
        }

      pExpanded = pReplaced;
    }
  else
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 61, message.c_str());
    }

  return pExpanded;
}

void CSBMLExporter::checkForPiecewiseFunctions(const CDataModel& dataModel, std::vector<SBMLIncompatibility>& result)
{
  std::set<std::string> usedFunctionNames;
  const CModel* pModel = dataModel.getModel();

  if (pModel == NULL) return;

  // go through all model entities and check assignments
  // we don't have to check initial assignment since those can not be exported
  // anyway
  const CModelEntity* pME = NULL;
  const CDataVectorNS<CCompartment>& compartments = pModel->getCompartments();
  size_t i, iMax = compartments.size();

  for (i = 0; i < iMax; ++i)
    {
      pME = &compartments[i];

      if (pME->getStatus() == CModelEntity::Status::ODE || pME->getStatus() == CModelEntity::Status::ASSIGNMENT)
        {
          const CEvaluationTree* pTree = pME->getExpressionPtr();
          CSBMLExporter::findDirectlyUsedFunctions(pTree->getRoot(), usedFunctionNames);
          CSBMLExporter::checkForPiecewiseFunctions(*pTree->getRoot(), result, pME->getObjectName(), "rule for compartment");
        }
    }

  const CDataVector<CMetab>& metabolites = pModel->getMetabolites();

  iMax = metabolites.size();

  for (i = 0; i < iMax; ++i)
    {
      pME = &metabolites[i];

      if (pME->getStatus() == CModelEntity::Status::ODE || pME->getStatus() == CModelEntity::Status::ASSIGNMENT)
        {
          const CEvaluationTree* pTree = pME->getExpressionPtr();
          CSBMLExporter::findDirectlyUsedFunctions(pTree->getRoot(), usedFunctionNames);
          CSBMLExporter::checkForPiecewiseFunctions(*pTree->getRoot(), result, pME->getObjectName(), "rule for metabolite");
        }
    }

  const CDataVectorN<CModelValue>& modelvalues = pModel->getModelValues();

  iMax = modelvalues.size();

  for (i = 0; i < iMax; ++i)
    {
      pME = &modelvalues[i];

      if (pME->getStatus() == CModelEntity::Status::ODE || pME->getStatus() == CModelEntity::Status::ASSIGNMENT)
        {
          const CEvaluationTree* pTree = pME->getExpressionPtr();
          CSBMLExporter::findDirectlyUsedFunctions(pTree->getRoot(), usedFunctionNames);
          CSBMLExporter::checkForPiecewiseFunctions(*pTree->getRoot(), result, pME->getObjectName(), "rule for global parameter");
        }
    }

  // go through all reactions and check the function called in the kinetic
  // laws.
  const CReaction* pReaction = NULL;
  const CDataVectorNS<CReaction>& reactions = pModel->getReactions();
  iMax = reactions.size();

  for (i = 0; i < iMax; ++i)
    {
      pReaction = &reactions[i];

      if (pReaction->getFunction() != NULL)
        {
          CSBMLExporter::findDirectlyUsedFunctions(pReaction->getFunction()->getRoot(), usedFunctionNames);
        }
    }

  // check indirectly called functions
  std::set<CFunction*> directlyUsedFunctions = CSBMLExporter::createFunctionSetFromFunctionNames(usedFunctionNames, CRootContainer::getFunctionList());
  std::vector<CFunction*> functions = CSBMLExporter::findUsedFunctions(directlyUsedFunctions, CRootContainer::getFunctionList());
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
  if (node.mainType() == CEvaluationNode::MainType::CHOICE)
    {
      result.push_back(SBMLIncompatibility(8, objectType.c_str(), objectName.c_str()));
    }
  else
    {
      // store the old size
      // if one error has been found, we can stop looking at the other
      // children
      size_t size = result.size();
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
  if (this->mpSBMLDocument != NULL && this->mpSBMLDocument->getModel() != NULL)
    {
      // we need to reverse the COPASI2SBMLMap so that we can remove objects
      // from the map if we delete them
      std::map<const SBase*, const CDataObject*> reverseCOPASI2SBMLMap;
      std::map<const CDataObject*, SBase*>::const_iterator it = this->mCOPASI2SBMLMap.begin(), endit = this->mCOPASI2SBMLMap.end();

      while (it != endit)
        {
          reverseCOPASI2SBMLMap.insert(std::pair<const SBase*, const CDataObject*>(it->second, it->first));
          ++it;
        }

      Model* pModel = this->mpSBMLDocument->getModel();
      std::list<SBase*> removedObjects;
      SBase* pSBase = NULL;
      ListOf* pList = pModel->getListOfCompartments();
      unsigned int i;
      std::map<const SBase*, const CDataObject*>::const_iterator pos;
      std::map<const CDataObject*, SBase*>::iterator pos2;

      for (i = pList->size(); i != 0; --i)
        {
          pSBase = pList->get(i - 1);

          if (this->mHandledSBMLObjects.find(pSBase) == this->mHandledSBMLObjects.end())
            {
              removedObjects.push_back(pList->remove(i - 1));
            }
        }

      pList = pModel->getListOfSpecies();

      for (i = pList->size(); i != 0; --i)
        {
          pSBase = pList->get(i - 1);

          if (this->mHandledSBMLObjects.find(pSBase) == this->mHandledSBMLObjects.end())
            {
              removedObjects.push_back(pList->remove(i - 1));
            }
        }

      pList = pModel->getListOfParameters();

      for (i = pList->size(); i != 0; --i)
        {
          pSBase = pList->get(i - 1);

          // skip all specially marked items
          if (pSBase->getUserData() != NULL && strcmp((const char*)pSBase->getUserData(), "1") == 0)
            continue;

          if (this->mHandledSBMLObjects.find(pSBase) == this->mHandledSBMLObjects.end())
            {
              removedObjects.push_back(pList->remove(i - 1));
            }
        }

      pList = pModel->getListOfInitialAssignments();

      for (i = pList->size(); i != 0; --i)
        {
          pSBase = pList->get(i - 1);

          // skip all specially marked items
          if (pSBase->getUserData() != NULL && strcmp((const char*)pSBase->getUserData(), "1") == 0)
            continue;

          if (this->mHandledSBMLObjects.find(pSBase) == this->mHandledSBMLObjects.end())
            {
              // remove the item from the COPASI2SBMLmap
              pos = reverseCOPASI2SBMLMap.find(pSBase);

              if (pos != reverseCOPASI2SBMLMap.end() && pos->second != NULL)
                {
                  pos2 = this->mCOPASI2SBMLMap.find(pos->second);

                  if (pos2 != this->mCOPASI2SBMLMap.end())
                    {
                      this->mCOPASI2SBMLMap.erase(pos2);
                    }
                }

              // we don't have to store the initial assignments since
              // there are no rules or events for initial assignments
              delete pList->remove(i - 1);
            }
        }

      pList = pModel->getListOfReactions();

      for (i = pList->size(); i != 0; --i)
        {
          pSBase = pList->get(i - 1);

          if (this->mHandledSBMLObjects.find(pSBase) == this->mHandledSBMLObjects.end())
            {
              // remove the item from the COPASI2SBMLmap
              pos = reverseCOPASI2SBMLMap.find(pSBase);

              if (pos != reverseCOPASI2SBMLMap.end() && pos->second != NULL)
                {
                  pos2 = this->mCOPASI2SBMLMap.find(pos->second);

                  if (pos2 != this->mCOPASI2SBMLMap.end())
                    {
                      this->mCOPASI2SBMLMap.erase(pos2);
                    }
                }

              // we don't have to store the reactions since
              // there are no rules or events for reactions
              delete pList->remove(i - 1);
            }
        }

      // check each removed object, if there is a rule or an event in
      // the SBML model for this object
      std::list<SBase*>::iterator it2 = removedObjects.begin(), endit2 = removedObjects.end();
      pList = pModel->getListOfRules();
      ListOf* pEventList = pModel->getListOfEvents();
      ListOf* pInitialAssignmentList = pModel->getListOfInitialAssignments();
      Rule* pRule = NULL;
      Event* pEvent = NULL;
      InitialAssignment* pIA = NULL;
      unsigned int iMax;

      while (it2 != endit2)
        {
          iMax = pList->size();

          for (i = 0; i < iMax; ++i)
            {
              pRule = dynamic_cast<Rule*>(pList->get(i));

              if (pRule != NULL && pRule->isSetVariable() && pRule->getVariable() == (*it2)->getId())
                {
                  // remove the item from the COPASI2SBMLmap
                  pos = reverseCOPASI2SBMLMap.find(pRule);

                  if (pos != reverseCOPASI2SBMLMap.end() && pos->second != NULL)
                    {
                      pos2 = this->mCOPASI2SBMLMap.find(pos->second);

                      if (pos2 != this->mCOPASI2SBMLMap.end())
                        {
                          this->mCOPASI2SBMLMap.erase(pos2);
                        }
                    }

                  delete pList->remove(i);
                  break;
                }
            }

          iMax = pInitialAssignmentList->size();

          for (i = 0; i < iMax; ++i)
            {
              pIA = dynamic_cast<InitialAssignment*>(pInitialAssignmentList->get(i));

              if (pIA->isSetSymbol() && pIA->getSymbol() == (*it2)->getId())
                {
                  // remove the item from the COPASI2SBMLmap
                  pos = reverseCOPASI2SBMLMap.find(pIA);

                  if (pos != reverseCOPASI2SBMLMap.end() && pos->second != NULL)
                    {
                      pos2 = this->mCOPASI2SBMLMap.find(pos->second);

                      if (pos2 != this->mCOPASI2SBMLMap.end())
                        {
                          this->mCOPASI2SBMLMap.erase(pos2);
                        }
                    }

                  delete pInitialAssignmentList->remove(i);
                  break;
                }
            }

          iMax = pEventList->size();

          for (i = 0; i < iMax; ++i)
            {
              pEvent = dynamic_cast<Event*>(pEventList->get(i));

              if (pEvent != NULL)
                {
                  ListOfEventAssignments* pEAL = pEvent->getListOfEventAssignments();
                  EventAssignment* pEA = NULL;
                  unsigned int j, jMax = pEAL->size();

                  for (j = 0; j < jMax; ++j)
                    {
                      pEA = pEvent->getEventAssignment(j);

                      if (pEA != NULL && pEA->getVariable() == (*it2)->getId())
                        {
                          // remove the item from the COPASI2SBMLmap
                          pos = reverseCOPASI2SBMLMap.find(pEA);

                          if (pos != reverseCOPASI2SBMLMap.end() && pos->second != NULL)
                            {
                              pos2 = this->mCOPASI2SBMLMap.find(pos->second);

                              if (pos2 != this->mCOPASI2SBMLMap.end())
                                {
                                  this->mCOPASI2SBMLMap.erase(pos2);
                                }
                            }

                          delete pEAL->remove(j);
                          break;
                        }
                    }

                  // if there are no more event assignments, we can delete the
                  // event
                  if (pEAL->size() == 0)
                    {
                      // remove the item from the COPASI2SBMLmap
                      pos = reverseCOPASI2SBMLMap.find(pEvent);

                      if (pos != reverseCOPASI2SBMLMap.end() && pos->second != NULL)
                        {
                          pos2 = this->mCOPASI2SBMLMap.find(pos->second);

                          if (pos2 != this->mCOPASI2SBMLMap.end())
                            {
                              this->mCOPASI2SBMLMap.erase(pos2);
                            }
                        }

                      delete pEventList->remove(i);
                    }
                }
            }

          // remove the item from the COPASI2SBMLmap
          pos = reverseCOPASI2SBMLMap.find(*it2);

          if (pos != reverseCOPASI2SBMLMap.end() && pos->second != NULL)
            {
              pos2 = this->mCOPASI2SBMLMap.find(pos->second);

              if (pos2 != this->mCOPASI2SBMLMap.end())
                {
                  this->mCOPASI2SBMLMap.erase(pos2);
                }
            }

          delete *it2;
          ++it2;
        }
    }
}

CEvaluationNode* CSBMLExporter::createMassActionExpression(const std::vector<std::vector<const CDataObject *> >& arguments, bool isReversible)
{
  assert((isReversible && arguments.size() == 4) || arguments.size() == 2);
  assert(arguments[0].size() == 1 && arguments[1].size() > 0);
  // create a multiplication of all items in arguments[1] and multiply that
  // with item arguments[0][0]
  std::set<const CDataObject *> finishedElements;
  std::vector<CEvaluationNode*> multiplicants;
  const CDataObject* pObject = arguments[0][0];
  assert(pObject != NULL);
  multiplicants.push_back(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pObject->getStringCN() + ",Reference=Value>"));
  std::vector<const CDataObject *>::const_iterator it = arguments[1].begin(), endit = arguments[1].end();

  while (it != endit)
    {
      if (finishedElements.find(*it) == finishedElements.end())
        {
#ifdef __SUNPRO_CC
          // replaced count call with  "old" count call
          // to compile on Sun Compiler
          unsigned int num = 0;
          std::count(arguments[1].begin(), arguments[1].end(), *it, num);
#else
          size_t num = std::count(arguments[1].begin(), arguments[1].end(), *it);
#endif  // __SUNPRO_CC
          assert(num != 0);
          finishedElements.insert(*it);
          pObject = *it;
          assert(pObject != NULL);

          if (num == 1)
            {
              multiplicants.push_back(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pObject->getStringCN() + ",Reference=Concentration>"));
            }
          else
            {
              std::ostringstream os;
              os << num;
              CEvaluationNodeOperator* pOperator = new CEvaluationNodeOperator(CEvaluationNode::SubType::POWER, "^");
              pOperator->addChild(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pObject->getStringCN() + ",Reference=Concentration>"));
              pOperator->addChild(new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, os.str()));
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
          pTmpNode = new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
          pTmpNode->addChild(*rIt);
          pTmpNode->addChild(pResult);
          pResult = pTmpNode;
          ++rIt;
        }
    }

  pTmpNode = new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
  pTmpNode->addChild(*rIt);
  pTmpNode->addChild(pResult);
  pResult = pTmpNode;

  if (isReversible)
    {
      std::vector<std::vector<const CDataObject *> > tmpV;
      tmpV.push_back(arguments[2]);
      tmpV.push_back(arguments[3]);
      pTmpNode = new CEvaluationNodeOperator(CEvaluationNode::SubType::MINUS, "-");
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
      size_t i, iMax = id.length();

      for (i = 1; (i < iMax) && result; ++i)
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

  for (i = 0; i < iMax; ++i)
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

  for (i = 0; i < iMax; ++i)
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
CEvaluationNode* CSBMLExporter::replaceSpeciesReferences(const CEvaluationNode* pOrigNode, const CDataModel& dataModel)
{
  CEvaluationNode* pResult = NULL;
  double factor = dataModel.getModel()->getQuantity2NumberFactor();

  if (pOrigNode->mainType() == CEvaluationNode::MainType::OBJECT)
    {
      const CDataObject* pObject = CObjectInterface::DataObject(dataModel.getObjectFromCN(dynamic_cast<const CEvaluationNodeObject*>(pOrigNode)->getObjectCN()));

      if (pObject == NULL)
        {
          // this will be the object from the mInitialValueMap
          pResult = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, pOrigNode->getData());
          return pResult;
        }

      if (pObject->hasFlag(CDataObject::Reference))
        {
          const CDataObject* pParent = pObject->getObjectParent();
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
                      pResult = new CEvaluationNodeOperator(CEvaluationNode::SubType::DIVIDE, "/");
                      // copy branch should be fine since the object node does
                      // not have children
                      pResult->addChild(pOrigNode->copyBranch());

                      if (pObject->getObjectName() == "InitialConcentration")
                        {
                          pResult->addChild(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pCompartment->getObject(CCommonName("Reference=InitialVolume"))->getStringCN() + ">"));
                        }
                      else
                        {
                          pResult->addChild(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pCompartment->getObject(CCommonName("Reference=Volume"))->getStringCN() + ">"));
                        }
                    }
                  else
                    {
                      // do nothing
                      pResult = pOrigNode->copyBranch();
                    }
                }
              else if (pObject->getObjectName() == "Rate")
                {
                  std::string id = addRateOfIfItDoesNotExist(mpSBMLDocument, mIdMap, "rateOf");
                  pResult = new CEvaluationNodeObject(CEvaluationNode::SubType::INVALID, "<rateOf>");
                  pResult->addChild(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pMetab->getConcentrationReference()->getStringCN() + ">"));
                  pResult->addChild(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + id + ">"));
                }
              else if (pObject->getObjectName() == "InitialParticleNumber" || pObject->getObjectName() == "ParticleNumber")
                {
                  // if the units are not set to particle numbers anyway,
                  // replace the node by the node times avogadros number
                  if (dataModel.getModel()->getQuantityUnit() != "#")
                    {
                      createAvogadroIfNeeded(dataModel);

                      pResult = new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
                      // copyBranch should be save here since object nodes can't
                      // have children
                      pResult->addChild(pOrigNode->copyBranch());
                      pResult->addChild(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + this->mpAvogadro->getStringCN() + ",Reference=InitialValue>"));
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

                      CEvaluationNode* pTmpNode = new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
                      pTmpNode->addChild(pResult);

                      if (pObject->getObjectName() == "InitialParticleNumber")
                        {
                          pTmpNode->addChild(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pCompartment->getObject(CCommonName("Reference=InitialVolume"))->getStringCN() + ">"));
                        }
                      else
                        {
                          pTmpNode->addChild(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pCompartment->getObject(CCommonName("Reference=Volume"))->getStringCN() + ">"));
                        }

                      pResult = pTmpNode;
                    }
                }
              else
                {
                  fatalError();
                }
            }

          else
            {
              const CModelEntity *pEntity = dynamic_cast<const CModelEntity*>(pParent);

              if (pEntity != NULL && pObject->getObjectName() == "Rate")
                {
                  std::string id = addRateOfIfItDoesNotExist(mpSBMLDocument, mIdMap, "rateOf");
                  pResult = new CEvaluationNodeObject(CEvaluationNode::SubType::INVALID, "<rateOf>");
                  pResult->addChild(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pEntity->getValueReference()->getStringCN() + ">"));
                  pResult->addChild(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + id + ">"));
                }
            }
        }
    }
  // check if there is a division by avogadros number and if so, just
  // drop the division instead of introducing a new multiplication
  else if (pOrigNode->mainType() == CEvaluationNode::MainType::OPERATOR && (pOrigNode->subType()) == CEvaluationNode::SubType::DIVIDE)
    {
      // check if one of the child nodes is a reference to a species

      const CEvaluationNode* pLeft = dynamic_cast<const CEvaluationNode*>(pOrigNode->getChild());
      const CEvaluationNode* pRight = dynamic_cast<const CEvaluationNode*>(pLeft->getSibling());
      assert(pLeft != NULL);
      assert(pRight != NULL);

      if (pLeft->mainType() == CEvaluationNode::MainType::OBJECT)
        {
          const CDataObject* pObject = CObjectInterface::DataObject(dataModel.getObjectFromCN(dynamic_cast<const CEvaluationNodeObject*>(pLeft)->getObjectCN()));

          if (pObject != NULL && pObject->hasFlag(CDataObject::Reference))
            {
              const CDataObject* pParent = pObject->getObjectParent();
              // check if the parent is a metabolite
              const CMetab* pMetab = dynamic_cast<const CMetab*>(pParent);

              if (pMetab != NULL)
                {
                  // check if pRight is a number or a parameter that
                  // corresponds to avogadros number
                  if (pRight->mainType() == CEvaluationNode::MainType::NUMBER &&
                      ((pRight->subType()) == CEvaluationNode::SubType::DOUBLE ||
                       (pRight->subType()) == CEvaluationNode::SubType::ENOTATION))
                    {
                      double value = *dynamic_cast<const CEvaluationNodeNumber*>(pRight)->getValuePointer();

                      if (fabs((factor - value) / factor) <= 1e-3)
                        {
                          // copyBranch should be OK since the node has no
                          // children anyway
                          pResult = pLeft->copyBranch();
                        }
                    }
                  else if (pRight->mainType() == CEvaluationNode::MainType::OBJECT)
                    {
                      const CDataObject* pObject2 = CObjectInterface::DataObject(dataModel.getObjectFromCN(dynamic_cast<const CEvaluationNodeObject*>(pRight)->getObjectCN()));

                      if (pObject2 != NULL && pObject2->hasFlag(CDataObject::Reference))
                        {
                          const CDataObject* pObjectParent2 = pObject2->getObjectParent();
                          const CModelValue* pMV = dynamic_cast<const CModelValue*>(pObjectParent2);

                          if (pMV != NULL && pMV->getStatus() == CModelEntity::Status::FIXED)
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
                  if (pRight->mainType() == CEvaluationNode::MainType::OBJECT)
                    {
                      // check if pRight is a reference to a species
                      const CDataObject* pObject2 = CObjectInterface::DataObject(dataModel.getObjectFromCN(dynamic_cast<const CEvaluationNodeObject*>(pRight)->getObjectCN()));

                      if (pObject2 != NULL && pObject2->hasFlag(CDataObject::Reference))
                        {
                          const CDataObject* pParent2 = pObject2->getObjectParent();
                          // check if the parent is a metabolite
                          pMetab = dynamic_cast<const CMetab*>(pParent2);

                          if (pMetab != NULL)
                            {
                              // if yes, check if pLeft is a parameter that corresponds
                              // to Avogadros number
                              if (pLeft->mainType() == CEvaluationNode::MainType::OBJECT)
                                {
                                  const CDataObject* pObject2 = CObjectInterface::DataObject(dataModel.getObjectFromCN(dynamic_cast<const CEvaluationNodeObject*>(pLeft)->getObjectCN()));

                                  if (pObject2 != NULL && pObject2->hasFlag(CDataObject::Reference))
                                    {
                                      const CDataObject* pObjectParent2 = pObject2->getObjectParent();
                                      const CModelValue* pMV = dynamic_cast<const CModelValue*>(pObjectParent2);

                                      if (pMV != NULL && pMV->getStatus() == CModelEntity::Status::FIXED)
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

void CSBMLExporter::createAvogadroIfNeeded(const CDataModel & dataModel)
{
  if (this->mpAvogadro != NULL)
    return;

  this->mpAvogadro = const_cast<CModel*>(dataModel.getModel())->createModelValue("quantity to number factor", dataModel.getModel()->getQuantity2NumberFactor());
  Parameter* pSBMLAvogadro = this->mpSBMLDocument->getModel()->createParameter();
  pSBMLAvogadro->setName("quantity to number factor");
  mAvogadroId = CSBMLExporter::createUniqueId(this->mIdMap, mpAvogadro->getObjectName(), false);
  pSBMLAvogadro->setId(mAvogadroId);
  const_cast< CModelValue * >(this->mpAvogadro)->setSBMLId(mAvogadroId);
  this->mIdMap.insert(std::pair< const std::string, const SBase * >(mAvogadroId, pSBMLAvogadro));
  pSBMLAvogadro->setConstant(true);
  pSBMLAvogadro->setValue(dataModel.getModel()->getQuantity2NumberFactor());
  this->mHandledSBMLObjects.insert(pSBMLAvogadro);
  this->mCOPASI2SBMLMap[this->mpAvogadro] = pSBMLAvogadro;
  this->mAvogadroCreated = true;
}

void CSBMLExporter::findAvogadro(const CDataModel& dataModel)
{
  double factor = dataModel.getModel()->getQuantity2NumberFactor();
  CDataVectorN<CModelValue>::const_iterator it = dataModel.getModel()->getModelValues().begin(), endit = dataModel.getModel()->getModelValues().end();

  while (it != endit)
    {
      if (it->getStatus() == CModelEntity::Status::FIXED)
        {
          double value = it->getInitialValue();

          if (fabs((factor - value) / factor) <= 1e-3)
            {
              this->mpAvogadro = it;
            }
        }

      ++it;
    }
}

/**
 * This method updates the MIRIAM annotation on different model entities like
 * the model itself, compartments, species, reactions, functions and global
 * parameters
 */
bool CSBMLExporter::updateMIRIAMAnnotation(const CDataObject* pCOPASIObject, SBase* pSBMLObject, std::map<std::string, const SBase*>& metaIds)
{
  bool result = true;

  if (pCOPASIObject == NULL || pSBMLObject == NULL) return false;

  const CAnnotation * pAnnotation = CAnnotation::castObject(pCOPASIObject);

  if (pAnnotation == NULL) return false;

  CMIRIAMInfo miriamInfo;
  miriamInfo.load(dynamic_cast< CDataContainer * >(const_cast< CDataObject * >(pCOPASIObject)));

  std::string miriamAnnotationString = miriamInfo.empty() ? "" : pAnnotation->getMiriamAnnotation();

  // first we clear the old CVTerms on the object
  pSBMLObject->unsetCVTerms();
  // now we have to set the CVTerms on the SBML object
  // the MIRIAM elements that are valid for all entities are the references (IS
  // DECRIBED BY) and the biological descriptions
  const CDataVector<CBiologicalDescription>& descriptions = miriamInfo.getBiologicalDescriptions();
  size_t i, iMax = descriptions.size();
  const CBiologicalDescription* pDescription = NULL;
  CVTerm cvTerm;
  // COPASI only uses Biological Qualifiers
  cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);

  std::string sboTerm;

  for (i = 0; i < iMax; ++i)
    {
      pDescription = &descriptions[i];
      assert(pDescription != NULL);

      switch (pDescription->getTriplet().Predicate.getType())
        {
          case CRDFPredicate::bqbiol_encodes:
          case CRDFPredicate::copasi_encodes:
            cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_UNKNOWN);
            cvTerm.setBiologicalQualifierType(BQB_ENCODES);
            break;

          case CRDFPredicate::bqbiol_hasPart:
          case CRDFPredicate::copasi_hasPart:
            cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_UNKNOWN);
            cvTerm.setBiologicalQualifierType(BQB_HAS_PART);
            break;

          case CRDFPredicate::bqbiol_hasVersion:
          case CRDFPredicate::copasi_hasVersion:
            cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_UNKNOWN);
            cvTerm.setBiologicalQualifierType(BQB_HAS_VERSION);
            break;

          case CRDFPredicate::bqbiol_is:
          case CRDFPredicate::copasi_is:
            cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_UNKNOWN);
            cvTerm.setBiologicalQualifierType(BQB_IS);

            if (pDescription->getResource() == "Systems Biology Ontology")
              sboTerm = pDescription->getId();

            break;

          case CRDFPredicate::bqmodel_isDerivedFrom:
            cvTerm.setQualifierType(MODEL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_IS_DERIVED_FROM);
            cvTerm.setBiologicalQualifierType(BQB_UNKNOWN);
            break;

          // IS DESCRIBED BY is handled in the references below
          //case bqbiol_isDescribedBy:
          //    break;
          case CRDFPredicate::bqbiol_isEncodedBy:
          case CRDFPredicate::copasi_isEncodedBy:
            cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_UNKNOWN);
            cvTerm.setBiologicalQualifierType(BQB_IS_ENCODED_BY);
            break;

          case CRDFPredicate::bqbiol_isHomologTo:
          case CRDFPredicate::copasi_isHomologTo:
            cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_UNKNOWN);
            cvTerm.setBiologicalQualifierType(BQB_IS_HOMOLOG_TO);
            break;

          case CRDFPredicate::bqbiol_isPartOf:
          case CRDFPredicate::copasi_isPartOf:
            cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_UNKNOWN);
            cvTerm.setBiologicalQualifierType(BQB_IS_PART_OF);
            break;

          case CRDFPredicate::bqbiol_isVersionOf:
          case CRDFPredicate::copasi_isVersionOf:
            cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_UNKNOWN);
            cvTerm.setBiologicalQualifierType(BQB_IS_VERSION_OF);
            break;

          // This qualifier is supported in libsbml 4.1
          case CRDFPredicate::bqbiol_occursIn:
          case CRDFPredicate::copasi_occursIn:
            cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_UNKNOWN);
            cvTerm.setBiologicalQualifierType(BQB_OCCURS_IN);
            break;

          case CRDFPredicate::bqmodel_is:
            cvTerm.setQualifierType(MODEL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setBiologicalQualifierType(BQB_UNKNOWN);
            cvTerm.setModelQualifierType(BQM_IS);

            if (pDescription->getResource() == "Systems Biology Ontology")
              sboTerm = pDescription->getId();

            break;

          case CRDFPredicate::bqbiol_hasProperty:
            cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_UNKNOWN);
            cvTerm.setBiologicalQualifierType(BQB_HAS_PROPERTY);
            break;

          case CRDFPredicate::bqbiol_isPropertyOf:
            cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_UNKNOWN);
            cvTerm.setBiologicalQualifierType(BQB_IS_PROPERTY_OF);
            break;

          case CRDFPredicate::bqbiol_hasTaxon:
            cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_UNKNOWN);
            cvTerm.setBiologicalQualifierType(BQB_HAS_TAXON);
            break;

          case CRDFPredicate::bqmodel_isInstanceOf:
            cvTerm.setQualifierType(MODEL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setBiologicalQualifierType(BQB_UNKNOWN);
            cvTerm.setModelQualifierType(BQM_IS_INSTANCE_OF);
            break;

          case CRDFPredicate::bqmodel_hasInstance:
            cvTerm.setQualifierType(MODEL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setBiologicalQualifierType(BQB_UNKNOWN);
            cvTerm.setModelQualifierType(BQM_HAS_INSTANCE);
            break;

          // IS DESCRIBED BY is handled in the references below
          //case bqmodel_isDescribedBy:
          //    break;
          default:
            // there are many qualifiers that start e.g. with copasi_ which are
            // not handled
            cvTerm.setQualifierType(UNKNOWN_QUALIFIER);
            break;
        }

      if (cvTerm.getQualifierType() != UNKNOWN_QUALIFIER)
        {
          // now we set the resources
          // TODO In COPASI there is only one resource per CBiologicalDescription
          // TODO object, I will have to check if libsbml puts all resources with the
          // TODO same predicate into one resource object since in libsbml a CVTerm
          // TODO can have several resources.
          // TODO If this isn't handled automatically by libsbml, I will have to add
          // TODO code that does this.
          cvTerm.addResource(pDescription->getMIRIAMResourceObject().getIdentifiersOrgURL());

          // before we set the CVTerm, we should make sure that the object has
          // a meta id
          if (!pSBMLObject->isSetMetaId())
            {
              std::string metaId = CSBMLExporter::createUniqueId(metaIds, "COPASI", true, "");
              metaIds.insert(std::pair<const std::string, const SBase*>(metaId, pSBMLObject));
              pSBMLObject->setMetaId(metaId);
            }

          pSBMLObject->addCVTerm(&cvTerm, true);
        }
    }

  // set SBO Term if we found it and have no SBO Term on the object
  if (!pSBMLObject->isSetSBOTerm() && !sboTerm.empty())
    pSBMLObject->setSBOTerm(sboTerm);

  const CDataVector<CReference>& references = miriamInfo.getReferences();

  const CReference* pReference = NULL;

  iMax = references.size();

  for (i = 0; i < iMax; ++i)
    {
      pReference = &references[i];
      assert(pReference != NULL);

      CRDFPredicate::ePredicateType Predicates[] =
      {
        CRDFPredicate::copasi_isDescribedBy,
        CRDFPredicate::bqbiol_isDescribedBy,
        CRDFPredicate::bqmodel_isDescribedBy,
        CRDFPredicate::end
      };

      std::set< CRDFTriplet > Triples;
      CRDFTriplet IdTriplet;
      CRDFPredicate::ePredicateType * pPredicate = Predicates;
      std::set< CRDFTriplet >::iterator it;

      for (; *pPredicate != CRDFPredicate::end; ++pPredicate)
        {
          Triples = pReference->getTriplet().pObject->getDescendantsWithPredicate(*pPredicate);
          it = Triples.begin();

          if (it != Triples.end())
            IdTriplet = *it;
        }

      if (!IdTriplet)
        continue;

      switch (IdTriplet.Predicate.getType())
        {
          case CRDFPredicate::bqbiol_isDescribedBy:
          case CRDFPredicate::copasi_isDescribedBy:
            cvTerm.setQualifierType(BIOLOGICAL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setModelQualifierType(BQM_UNKNOWN);
            cvTerm.setBiologicalQualifierType(BQB_IS_DESCRIBED_BY);
            break;

          case CRDFPredicate::bqmodel_isDescribedBy:
            cvTerm.setQualifierType(MODEL_QUALIFIER);
            // libsbml does not reset the model qualifier type and the
            // biological qualifier type if the qualifier type is set
            cvTerm.setBiologicalQualifierType(BQB_UNKNOWN);
            cvTerm.setModelQualifierType(BQM_IS_DESCRIBED_BY);
            break;

          default:
            cvTerm.setQualifierType(UNKNOWN_QUALIFIER);
            break;
        }

      // set the resources which consist of the pubmed id and the DOI
      if (cvTerm.getQualifierType() != UNKNOWN_QUALIFIER)
        {
          // now we set the resources
          // TODO In COPASI there is only one resource per CBiologicalDescription
          // TODO object, I will have to check if libsbml puts all resources with the
          // TODO same predicate into one resource object since in libsbml a CVTerm
          // TODO can have several resources.
          // TODO If this isn't handled automatically by libsbml, I will have to add
          // TODO code that does this.
          cvTerm.addResource(pReference->getMIRIAMResourceObject().getIdentifiersOrgURL());

          // before we set the CVTerm, we should make sure that the object has
          // a meta id
          if (!pSBMLObject->isSetMetaId())
            {
              std::string metaId = CSBMLExporter::createUniqueId(metaIds, "COPASI", true, "");
              metaIds.insert(std::pair<const std::string, const SBase*>(metaId, pSBMLObject));
              pSBMLObject->setMetaId(metaId);
            }

          pSBMLObject->addCVTerm(&cvTerm, true);
        }
    }

  // starting with SBML L3 all model elements that are derived from SBase can have
  // a model history
  //
  // if it is the model, we have to set the model history
  // in addition to the normal CVTerms
  const CModel* pModel = dynamic_cast<const CModel*>(pCOPASIObject);

  if ((pModel != NULL && this->mSBMLLevel < 3)
      || this->mSBMLLevel > 2
     )
    {
      // the model history consists of the creators, the creation time and the
      // modification time
      // create a model history instance
      bool modified = false;
      ModelHistory modelHistory;
      // first we add all creators
      const CDataVector<CCreator>& creators = miriamInfo.getCreators();
      size_t i, iMax = creators.size();
      const CCreator* pCreator = NULL;
      ModelCreator modelCreator;

      if (iMax > 0)
        {
          modified = true;
        }

      for (i = 0; i < iMax; ++i)
        {
          pCreator = &creators[i];
          assert(pCreator != NULL);
          // a model creator can have a family name, a given name, and email
          // address and an organization
          modelCreator.setFamilyName(pCreator->getFamilyName());
          modelCreator.setGivenName(pCreator->getGivenName());
          modelCreator.setEmail(pCreator->getEmail());
          modelCreator.setOrganisation(pCreator->getORG());
          modelHistory.addCreator(&modelCreator);
        }

      // now set the creation date
      std::string creationDateString = miriamInfo.getCreatedDT();

      if (!creationDateString.empty())
        {
          Date creationDate = Date(creationDateString);
          modelHistory.setCreatedDate(&creationDate);
          modified = true;
        }

      const CDataVector <CModification> & modifications = miriamInfo.getModifications();
      iMax = modifications.size();

      for (i = 0; i < iMax; ++i)
        {
          modified = true;
          const CModification* pModification = &modifications[i];

          if (!pModification)
            continue;

          std::string dateString = pModification->getDate();

          if (dateString.empty())
            continue;

          Date modifiedDate(dateString);
          modelHistory.addModifiedDate(&modifiedDate);
        }

      if (iMax == 0 && modelHistory.isSetCreatedDate())
        {
          // a model history is only valid if it has a modifiedData
          modelHistory.setModifiedDate(modelHistory.getCreatedDate());
        }

      // make sure the element has a meta id
      if (!pSBMLObject->isSetMetaId())
        {
          std::string metaId = CSBMLExporter::createUniqueId(metaIds, "COPASI", true, "");
          metaIds.insert(std::pair<const std::string, const SBase*>(metaId, pSBMLObject));
          pSBMLObject->setMetaId(metaId);
        }

      if (modified == true)
        {
          if (pSBMLObject->setModelHistory(&modelHistory) != LIBSBML_OPERATION_SUCCESS)
            {
#if LIBSBML_VERSION >= 52000

              // setting the history failed, probably since we have an incomplete object.
              // so instead we just set the dates
              if (modelHistory.isSetCreatedDate())
                pSBMLObject->setCreatedDate(modelHistory.getCreatedDate());

              // if we have already modified dates on the object remove
              pSBMLObject->unsetModifiedDates();

              // then add all modified dates from current element
              for (unsigned int i = 0; i < modelHistory.getNumModifiedDates(); ++i)
                {
                  pSBMLObject->addModifiedDate(modelHistory.getModifiedDate(i));
                }

#endif // LIBSBML_VERSION >= 52000
            }
        }
    }

  if (this->mExportCOPASIMIRIAM == true)
    {
      // add the COPASI RDF stuff as an annotation in the COPASI namespace
      XMLNode* pCOPASIAnnotation = NULL;
      XMLNode* pAnnotation = NULL;
      int COPASIAnnotationIndex = -1;
      int oldRDFAnnotationIndex = -1;

      if (pSBMLObject->isSetAnnotation())
        {
          pAnnotation = pSBMLObject->getAnnotation();
          unsigned int i, iMax = pAnnotation->getNumChildren();

          // find the COPASI annotation if there is one
          for (i = 0; i < iMax; ++i)
            {
              if (pAnnotation->getChild(i).getURI() == "http://www.copasi.org/static/sbml")
                {
                  if (pAnnotation->getChild(i).getPrefix().empty())
                    {
                      pCOPASIAnnotation = XMLNode::convertStringToXMLNode("<copasi:COPASI xmlns:copasi=\"http://www.copasi.org/static/sbml\"></copasi:COPASI>");
                      pCOPASIAnnotation->unsetEnd();

                      // Copy existing children
                      const XMLNode & Existing = pAnnotation->getChild(i);
                      unsigned int j, jMax = Existing.getNumChildren();

                      for (j = 0; j < jMax; ++j)
                        {
                          pCOPASIAnnotation->addChild(Existing.getChild(j));
                        }
                    }
                  else
                    {
                      pCOPASIAnnotation = pSBMLObject->getAnnotation()->getChild(i).clone();
                    }

                  COPASIAnnotationIndex = i;
                  unsigned int j, jMax = pCOPASIAnnotation->getNumChildren();

                  // find the index of the RDF subtree if there is one
                  for (j = 0; j < jMax; ++j)
                    {
                      if (pCOPASIAnnotation->getChild(j).getURI() == "http://www.w3.org/1999/02/22-rdf-syntax-ns#")
                        {
                          oldRDFAnnotationIndex = j;
                          break;
                        }
                    }

                  break;
                }
            }
        }

      // replace the meta ids in the MIRIAM annotation string
      if (miriamAnnotationString.find_first_not_of("\t\r\n ") != std::string::npos)
        {
          std::string metaId;

          if (pSBMLObject->isSetMetaId())
            {
              metaId = pSBMLObject->getMetaId();
            }
          else
            {
              metaId = CSBMLExporter::createUniqueId(metaIds, "COPASI", true, "");
              metaIds.insert(std::pair<const std::string, const SBase*>(metaId, pSBMLObject));
              pSBMLObject->setMetaId(metaId);
            }

          // now we have to replace the metaid
          CRDFUtilities::fixLocalFileAboutReference(miriamAnnotationString, metaId, pCOPASIObject->getKey());
          // the new annotation is not empty, so we have to convert it
          // the root of the returned tree is a dummy node, so the actual
          // RDF element is the first child of the returned value

          // the convertStringToXMLNode has changed behavior between libsbml 3 and libsbml 4
          // in libsbml it creates a dummy node and in libsbml 4 it doesn't
          XMLNamespaces ns;
          ns.add("http://www.copasi.org/RDF/MiriamTerms#", "CopasiMT");
          ns.add("http://purl.org/dc/terms/", "dcterms");
          ns.add("http://www.w3.org/1999/02/22-rdf-syntax-ns#", "rdf");
          ns.add("http://www.w3.org/2001/vcard-rdf/3.0#", "vCard");
          ns.add("http://biomodels.net/biology-qualifiers/", "bqbiol");
          ns.add("http://biomodels.net/model-qualifiers/", "bqmodel");

          XMLNode* pMIRIAMNode = XMLNode::convertStringToXMLNode(miriamAnnotationString, &ns);
          if (pMIRIAMNode == NULL)
          {
            return false;
          }

          if (pCOPASIAnnotation == NULL)
            {
              // create a new COPASI annotation
              // the root of the returned tree is a dummy node, so the actual
              // COPASI is the first child of the returned value

              // the convertStringToXMLNode has changed behavior between libsbml 3 and libsbml 4
              // in libsbml it creates a dummy node and in libsbml 4 it doesn't
              pCOPASIAnnotation = XMLNode::convertStringToXMLNode("<copasi:COPASI xmlns:copasi=\"http://www.copasi.org/static/sbml\"></copasi:COPASI>");
              // calling unsetEnd is necessary for libsbml 3.1.1 and 3.2.0,
              // otherwise libsbml will write the opening COPASI element as a
              // closing element and add another closing element later on which is
              // incorrect XML
              pCOPASIAnnotation->unsetEnd();
              assert(pCOPASIAnnotation != NULL);
              // add the RDF stuff
              // we add the first child of the MIRIAM node since it was created
              // with convertStrngToXMLNode which creates a dummy node as the
              // root node
              pCOPASIAnnotation->addChild(*pMIRIAMNode);
              // delete the MIRIAM node since addChild made a copy
              delete pMIRIAMNode;
            }
          else
            {
              // replace the old RDF annotation from the COPASI subtree if there
              // is one, else add the new one
              if (oldRDFAnnotationIndex != -1)
                {
                  //
                  XMLNode* pNewCOPASIAnnotation = CSBMLExporter::replaceChild(pCOPASIAnnotation, pMIRIAMNode, oldRDFAnnotationIndex);
                  // delete the old copy of the COPASI node
                  delete pCOPASIAnnotation;
                  pCOPASIAnnotation = pNewCOPASIAnnotation;
                  // delete the MIRIAM node since replaceChild made a copy
                  delete pMIRIAMNode;
                }
              else
                {
                  // we add the first child of the MIRIAM node since it was created
                  // with convertStrngToXMLNode which creates a dummy node as the
                  // root node
                  pCOPASIAnnotation->addChild(pMIRIAMNode->getChild(0));
                  // delete the MIRIAM node since addChild made a copy
                  delete pMIRIAMNode;
                }
            }

          // I don't think that getAnnotation will every return NULL because it is
          // created on the fly by libsbml if there isn't one already.
          // This is just a safety net in cast the libsbml API changes
          if (pSBMLObject->getAnnotation() == NULL)
            {
              // the convertStringToXMLNode has changed behavior between libsbml 3 and libsbml 4
              // in libsbml it creates a dummy node and in libsbml 4 it doesn't
              pAnnotation = XMLNode::convertStringToXMLNode("<annotation></annotation>");
              // the libsbml convertStringToXMLNode doesn't seem to work in the
              // same way when we create an annotation node as opposed to the
              // COPASI node above.
              // For the COPASI node, we get a dummy node as the root whereas here
              // we don't
              assert(pAnnotation != NULL);
              // add the COPASI annotation
              // if we created the COPASI element with convertStringTOXMLNode, we
              // have to use the first child since the root is a dummy node
              pAnnotation->addChild(*pCOPASIAnnotation);
              // pCOPASIAnnotation is always a copy, so we have to delete it
              delete pCOPASIAnnotation;
              pSBMLObject->setAnnotation(pAnnotation);
              delete pAnnotation;
            }
          else
            {
              // if there is a COPASI node, if yes replace it else add it
              if (COPASIAnnotationIndex != -1)
                {
                  // we have to call getAnnotation on the SBML object instead of resulting
                  // the annotation we got above because libsbml deletes the annotation
                  //  object when it syncs the annotation. So the annotation object we
                  //  got above is most likely deleted already
                  pAnnotation = CSBMLExporter::replaceChild(pSBMLObject->getAnnotation(), pCOPASIAnnotation, COPASIAnnotationIndex);
                  // we have to delete pCOPASIAnnotation since replaceChild makes a copy
                  delete pCOPASIAnnotation;
                  pSBMLObject->setAnnotation(pAnnotation);
                  delete pAnnotation;
                }
              else
                {
                  // we have to call getAnnotation on the SBML object instead of resulting
                  // the annotation we got above because libsbml deletes the annotation
                  //  object when it syncs the annotation. So the annotation object we
                  //  got above is most likely deleted already
                  pSBMLObject->getAnnotation()->addChild(*pCOPASIAnnotation);
                  // we have to delete pCOPASIAnnotation since replaceChild made a copy
                  delete pCOPASIAnnotation;
                }
            }
        }
      else
        {
          // if there is an RDF annotation in the COPASI annotation already, we
          // have to delete it.
          // if this rdf annotation is the only child of the COPASI annotation,
          // we delete the whole COPASI annotation
          if (pSBMLObject->getAnnotation() != NULL && COPASIAnnotationIndex != -1 && oldRDFAnnotationIndex != -1)
            {
              if (pCOPASIAnnotation->getNumChildren() == 1)
                {
                  // we have to call getAnnotation on the SBML object instead of reusing
                  // the annotation we got above because libsbml deletes the annotation
                  //  object when it syncs the annotation. So the annotation object we
                  //  got above is most likely deleted already
                  if (pSBMLObject->getAnnotation()->getNumChildren() == 1)
                    {
                      // delete the complete annotation
                      pSBMLObject->unsetAnnotation();
                    }
                  else
                    {
                      // only delete the COPASI subtree
                      // we have to call getAnnotation on the SBML object instead of reusing
                      // the annotation we got above because libsbml deletes the annotation
                      //  object when it syncs the annotation. So the annotation object we
                      //  got above is most likely deleted already
                      pAnnotation = CSBMLExporter::replaceChild(pSBMLObject->getAnnotation(), NULL, COPASIAnnotationIndex);
                      assert(pAnnotation != NULL);
                      pSBMLObject->setAnnotation(pAnnotation);
                      // delete the annotation object since it has been created by
                      // replaceChild and setAnnotation made a copy
                      delete pAnnotation;
                    }
                }
              else
                {
                  // delete the RDF annotation from the COPASI tree
                  // replace the COPASI tree in pAnnotation
                  pCOPASIAnnotation = CSBMLExporter::replaceChild(pCOPASIAnnotation, NULL, oldRDFAnnotationIndex);
                  assert(pCOPASIAnnotation != NULL);
                  // we have to call getAnnotation on the SBML object instead of reusing
                  // the annotation we got above because libsbml deletes the annotation
                  //  object when it syncs the annotation. So the annotation object we
                  //  got above is most likely deleted already
                  pAnnotation = CSBMLExporter::replaceChild(pSBMLObject->getAnnotation(), pCOPASIAnnotation, COPASIAnnotationIndex);
                  // delete pCOPASIAnnotation since replaceChild made a copy
                  delete pCOPASIAnnotation;
                  pSBMLObject->setAnnotation(pAnnotation);
                  // delete the annotation object since it has been created by
                  // replaceChild and setAnnotation made a copy
                  delete pAnnotation;
                }
            }
        }
    }

  return result;
}

/**
 * This method creates a copy of parent where the child with the given index is
 * replaced by the new child given as the second argument.
 * If index is greater than the number of children - 1, NULL is returned.
 * If the new child is a null pointer, this method deleted the old node at
 * the given index.
 */
XMLNode* CSBMLExporter::replaceChild(const XMLNode* pParent, const XMLNode* pNewChild, unsigned int index)
{
  XMLNode* pResult = NULL;

  if (index < pParent->getNumChildren())
    {
      // make a shallow copy of pParent
      // The copy constructor makes a deep copy, so we have to use the
      // constructor that takes an XMLToken
      pResult = new XMLNode(XMLToken(*pParent));
      unsigned int i, iMax = pParent->getNumChildren();

      for (i = 0; i < iMax; ++i)
        {
          // make a deep copy of each child, but if the index of child is the
          // given index, we add pNewChild instead of making a copy of the
          // current child
          if (i == index && pNewChild != NULL)
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

void adjustNames(ASTNode* node, SBMLDocument* pSBMLDocument, std::map<std::string, const SBase*>& idMap)
{
  if (node == NULL)
    return;

  if (node->isNumber() || node->isConstant() || node->isName())
    return;

  if (node->getType() == AST_FUNCTION)
    {
      std::string adjustedName = getUserDefinedFuctionForName(
                                   pSBMLDocument,
                                   idMap,
                                   node->getName()
                                 );
      node->setName(adjustedName .c_str());
    }

  for (unsigned int i = 0; i < node->getNumChildren(); ++i)
    {
      adjustNames(node->getChild(i), pSBMLDocument, idMap);
    }
}

ASTNode* CSBMLExporter::convertToASTNode(const CEvaluationNode* pOrig, CDataModel& dataModel)
{
  // first go through the tree and check that all function calls are to
  // functions that have an SBML id
  // if they don't, we have to set one
  this->setFunctionSBMLIds(pOrig, dataModel);
  ASTNode* pResult = pOrig->toAST(&dataModel, mSBMLLevel, mSBMLVersion);

  adjustNames(pResult, mpSBMLDocument, mIdMap);

  return pResult;
}

void CSBMLExporter::setFunctionSBMLIds(const CEvaluationNode* pNode, CDataModel& dataModel)
{
  if (pNode->mainType() == CEvaluationNode::MainType::CALL)
    {
      std::string funName = dynamic_cast<const CEvaluationNodeCall*>(pNode)->getData();
      CFunction* pFun = CRootContainer::getFunctionList()->findFunction(funName);
      assert(pFun != NULL);

      if (pFun == NULL) fatalError();

      std::string id = pFun->getSBMLId();

      if (id.empty())
        {
          if (CSBMLExporter::isValidSId(funName))
            {
              if (this->mIdMap.find(funName) != this->mIdMap.end())
                {
                  id = CSBMLExporter::createUniqueId(this->mIdMap, funName, true);
                }
              else
                {
                  id = funName;
                }
            }
          else
            {
              id = CSBMLExporter::createUniqueId(this->mIdMap, funName, false);
            }

          this->mIdMap.insert(std::make_pair(id, (const SBase*)NULL));
          pFun->setSBMLId(id);
          // add the id,pointer pair to the function id map so that we know
          // that this id has been used for that function
          this->mFunctionIdMap.insert(std::pair<std::string, const CEvaluationTree*>(id, pFun));
        }
      else
        {
          // check if there is an entry in the function id map for that id
          std::map<std::string, const CEvaluationTree*>::iterator pos = this->mFunctionIdMap.find(id);

          if (pos == this->mFunctionIdMap.end())
            {
              // reserve this function name
              this->mIdMap.insert(std::pair<std::string, const SBase*>(id, (SBase*)NULL));
              this->mFunctionIdMap.insert(std::pair<std::string, const CEvaluationTree*>(id, pFun));
            }
          else
            {
              if (pos->second != pFun)
                {
                  // mark the id as taken
                  this->mIdMap.insert(std::pair<std::string, const SBase*>(id, (SBase*)NULL));
                  id = CSBMLExporter::createUniqueId(this->mIdMap, pFun->getObjectName(), false);
                  pFun->setSBMLId(id);
                }
            }
        }
    }

  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pNode->getChild());

  while (pChild != NULL)
    {
      this->setFunctionSBMLIds(pChild, dataModel);
      pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
    }
}

void CSBMLExporter::outputIncompatibilities() const
{
  size_t i, iMax = this->mIncompatibilities.size();

  for (i = 0; i < iMax; ++i)
    {
      const SBMLIncompatibility* pIncompat = &this->mIncompatibilities[i];
      std::ostringstream os;
      os << pIncompat->getMessage() << "\n";
      os << pIncompat->getDetails() << "\n";

      if (pIncompat->minSBMLLevel() != 0 && pIncompat->minSBMLVersion() != 0)
        {
          os << "Please export to SBML Level " << pIncompat->minSBMLLevel();
          os << " Version " << pIncompat->minSBMLVersion() << " or higher.";
        }

      CCopasiMessage(CCopasiMessage::RAW, os.str().c_str());
    }
}

void CSBMLExporter::disownSBMLDocument()
{
  this->mDocumentDisowned = true;
}

const std::map<const CDataObject*, SBase*>& CSBMLExporter::getCOPASI2SBMLMap() const
{
  return this->mCOPASI2SBMLMap;
}

bool CSBMLExporter::isSetExportCOPASIMIRIAM() const
{
  return this->mExportCOPASIMIRIAM;
}

void CSBMLExporter::setExportCOPASIMIRIAM(bool exportMiriam)
{
  this->mExportCOPASIMIRIAM = exportMiriam;
}

void CSBMLExporter::isEventSBMLCompatible(
  const CEvent* pEvent,
  const CDataModel& dataModel,
  unsigned int sbmlLevel,
  unsigned int sbmlVersion,
  std::vector<SBMLIncompatibility>& result,
  std::map<std::string, const SBase*>& idMap)
{
  if (pEvent == NULL) return;

  // check if the trigger and the delay expression only reference allowed
  // model entities
  // make sure no two event assignments assign to the same variable
  std::set<std::string> usedFunctionNames;
  const CExpression* pExpression = pEvent->getTriggerExpressionPtr();

  if (pExpression != NULL)
    {
      // check for unsupported object references and unsupported function
      // calls
      CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, idMap, std::string("trigger expression for event named \"" + pEvent->getObjectName() + "\""));
      usedFunctionNames.clear();
      CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
    }

  pExpression = pEvent->getDelayExpressionPtr();

  if (pExpression != NULL)
    {
      // check for unsupported object references and unsupported function
      // calls
      CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, idMap, std::string("delay expression for event named \"" + pEvent->getObjectName() + "\""));
      usedFunctionNames.clear();
      CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
    }

  std::set<std::string> objectCNs;
  std::set<std::string> nonUniqueObjectCNs;

  CDataVectorN< CEventAssignment >::const_iterator itAssignment = pEvent->getAssignments().begin();
  CDataVectorN< CEventAssignment >::const_iterator endAssignment = pEvent->getAssignments().end();

  for (; itAssignment != endAssignment; ++itAssignment)
    {
      std::string CN = itAssignment->getTargetCN();
      const CDataObject * pObject = CObjectInterface::DataObject(dataModel.getObject(CN));

      if (objectCNs.find(CN) == objectCNs.end())
        {
          objectCNs.insert(CN);
        }
      else
        {
          // This should never happen since I assume that COPASI will have
          // the same restriction as SBML with respect to unique assignments
          // within an event
          if (nonUniqueObjectCNs.find(CN) == nonUniqueObjectCNs.end())
            {
              nonUniqueObjectCNs.insert(CN);
              assert(pObject != NULL);
              CCopasiMessage(CCopasiMessage::RAW, std::string("Error. Event called \"" + pEvent->getObjectName() + "\" has several assignments to the same object called \"" + pObject->getObjectName() + "\".").c_str());
            }
        }

      CSBMLExporter::isEventAssignmentSBMLCompatible(pObject, itAssignment->getExpressionPtr(),
          dataModel, sbmlLevel, sbmlVersion, pEvent->getObjectName(), result, idMap);
    }
}

void CSBMLExporter::isEventAssignmentSBMLCompatible(
  const CDataObject * pTarget,
  const CExpression* pExpression,
  const CDataModel& dataModel,
  unsigned int sbmlLevel,
  unsigned int sbmlVersion,
  const std::string& eventName,
  std::vector<SBMLIncompatibility>& result,
  std::map<std::string, const SBase*>& idMap)
{
  assert(pTarget != NULL);
  const CModelEntity* pME = dynamic_cast<const CModelEntity*>(pTarget);

  if (pME == NULL)
    {
      // create an error message since the object is not a
      // compartment, species or model value
    }
  else
    {
      std::string objectType = pME->getObjectType();

      if (objectType != "Compartment" && objectType != "Metabolite" && objectType != "ModelValue")
        {
          // create an error message since the object is not a
          // compartment, species or model value
          result.push_back(SBMLIncompatibility(9, pTarget->getObjectName().c_str(), std::string("event called \"" + eventName + "\"").c_str()));
        }
      else
        {
          // make sure the component that is assigned to is not constant
          if (pME->getStatus() == CModelEntity::Status::FIXED)
            {
              // create an nerror message since the entity may not be
              // constant
              // This is a raw message since I do expect COPASI to have the same
              // restriction as SBML, so this should never happen
              CCopasiMessage(CCopasiMessage::RAW, std::string("Error. Event assignment to constant object named \"" + pTarget->getObjectName() + "\" in event named \"" + eventName + "\".").c_str());
            }
          // make sure there is no assignment rule for the variable
          else if (pME->getStatus() == CModelEntity::Status::ASSIGNMENT)
            {
              // create an nerror message since the entity may not be
              // determined by an assignment
              // This is a raw message since I do expect COPASI to have the same
              // restriction as SBML, so this should never happen
              CCopasiMessage(CCopasiMessage::RAW, std::string("Error. Event assignment to object called \"" + pTarget->getObjectName() + "\" in event named \"" + eventName + "\", which is determined by an assignment rule.").c_str());
            }

          // check if the expression only references allowed model entities
          if (pExpression != NULL && pExpression->getRoot()->mainType() != CEvaluationNode::MainType::INVALID)
            {

              std::set<std::string> usedFunctionNames;
              CSBMLExporter::isExpressionSBMLCompatible(*pExpression, dataModel, sbmlLevel, sbmlVersion, result, idMap, std::string("assignment expression for variable named \"" + pTarget->getObjectName() + "\" in event named \"" + eventName + "\"").c_str());
              CSBMLExporter::findDirectlyUsedFunctions(pExpression->getRoot(), usedFunctionNames);
            }
          else
            {
              // This is a raw message since I do expect COPASI to always have
              // an assignment expression
              CCopasiMessage(CCopasiMessage::RAW, std::string("Error. No expression set for event assignment to object called \"" + pTarget->getObjectName() + "\" in event named \"" + eventName + "\".").c_str());
            }
        }
    }
}

/**
 * Goes through the expression tree and tries to find occurences of local
 * parameters. If one is found, a global parameter is created and all
 * references to the local parameters are substituted.
 */
void CSBMLExporter::replace_local_parameters(ASTNode* pOrigNode, const CDataModel& dataModel)
{
  //  go through the expression and check if it contains a local reaction
  //  parameter, if it does, we have to create a global parameter to replace it
  //  the replacement has to be recorded in same data structure so that we can
  //  consider it when the reactions are created later on
  //  In the end, we need to use this map to create a warning message.
  if (pOrigNode != NULL)
    {
      // the new id for the global parameter should contain the reaction name and
      // the parameter name
      if (pOrigNode->getType() == AST_NAME)
        {
          std::string objectName = pOrigNode->getName();
          const CDataObject* pObject = CObjectInterface::DataObject(dataModel.getObjectFromCN(objectName));

          if (pObject != NULL)
            {
              const CCopasiParameter* pLocalParameter = dynamic_cast<const CCopasiParameter*>(pObject);

              if (pLocalParameter != NULL)
                {
                  // it must be a local parameter
                  std::map<std::string, Parameter*>::iterator pos = this->mParameterReplacementMap.find(pLocalParameter->getStringCN());

                  if (pos == this->mParameterReplacementMap.end())
                    {
                      // not found, so we create a new global parameter
                      const CDataObject* pParent = pLocalParameter->getObjectParent();

                      // find the reaction
                      while (pParent != NULL && dynamic_cast<const CReaction*>(pParent) == NULL)
                        {
                          pParent = pParent->getObjectParent();
                        }

                      assert(pParent);
                      // now we create a new global parameter with a unique name
                      std::string name = pParent->getObjectName() + "_" + pLocalParameter->getObjectName();
                      std::string sbmlId = CSBMLExporter::createUniqueId(this->mIdMap, name, false);
                      Parameter* pParameter = this->mpSBMLDocument->getModel()->createParameter();

                      // don't call setName on level 1 objects because this will also
                      // change the id
                      if (this->mpSBMLDocument->getLevel() > 1)
                        {
                          pParameter->setName(name);
                        }

                      pParameter->setId(sbmlId);
                      this->mIdMap.insert(std::pair<std::string, SBase*>(sbmlId, pParameter));
                      pParameter->setValue(pLocalParameter->getValue< C_FLOAT64 >());
                      this->mParameterReplacementMap[pLocalParameter->getStringCN()] = pParameter;
                      pOrigNode->setName(sbmlId.c_str());
                      this->mHandledSBMLObjects.insert(pParameter);
                    }
                  else
                    {
                      // we set the node name to the existing parameter name
                      pOrigNode->setName(pos->second->getId().c_str());
                    }
                }
            }
        }

      unsigned int i = 0, iMax = pOrigNode->getNumChildren();

      while (i < iMax)
        {
          this->replace_local_parameters(pOrigNode->getChild(i), dataModel);
          ++i;
        }
    }
}

/**
 * This method goes through the expression tree and tries to find node
 * names that correspond to common names of local parameters.
 * If the common name also occurs in the replacement map, the node name has
 * to be set to the id of the corresponding global parameter, otherwise the name
 * has to be set to the object name of the parameter.
 */
void CSBMLExporter::restore_local_parameters(ASTNode* pOrigNode, const CDataModel& dataModel)
{
  if (pOrigNode != NULL)
    {
      if (pOrigNode->getType() == AST_NAME)
        {
          // check if the common name is in the replacement map
          std::string objectName = pOrigNode->getName();
          std::map<std::string, Parameter*>::iterator pos = this->mParameterReplacementMap.find(objectName);

          if (pos != this->mParameterReplacementMap.end())
            {
              // it was in the map, so we know that the local parameter has
              // been replaced by a global parameter and we need to set the
              // id of the global parameter as the new name of the node
              pOrigNode->setName(pos->second->getId().c_str());
            }
          else
            {
              // we need to reset the node name to the id of the local
              // parameter which is the object name
              const CDataObject* pObject = CObjectInterface::DataObject(dataModel.getObjectFromCN(objectName));

              if (pObject != NULL)
                {
                  const CCopasiParameter* pLocalParameter = dynamic_cast<const CCopasiParameter*>(pObject);

                  if (pLocalParameter != NULL)
                    {
                      // we set the node name to the existing parameter name
                      pOrigNode->setName(pLocalParameter->getObjectName().c_str());
                    }
                }
            }
        }

      unsigned int i = 0, iMax = pOrigNode->getNumChildren();

      while (i < iMax)
        {
          this->restore_local_parameters(pOrigNode->getChild(i), dataModel);
          ++i;
        }
    }
}

/**
 * This method goes through the given datamodel and collects all SBML ids.
 */
void CSBMLExporter::collectIds(const CDataModel& dataModel, std::map<std::string, const SBase*>& idMap)
{
  size_t i, iMax = CRootContainer::getFunctionList()->loadedFunctions().size();
  std::string id;

  for (i = 0; i < iMax; ++i)
    {
      const CFunction* pFun = &CRootContainer::getFunctionList()->loadedFunctions()[i];
      id = pFun->getSBMLId();

      if (!id.empty())
        {
          idMap.insert(std::pair<const std::string, const SBase*>(id, (const SBase*)NULL));
        }
    }

  const CModel* pModel = dataModel.getModel();

  id = pModel->getSBMLId();

  if (!id.empty())
    {
      idMap.insert(std::pair<const std::string, const SBase*>(id, (const SBase*)NULL));
    }

  iMax = pModel->getCompartments().size();

  for (i = 0; i < iMax; ++i)
    {
      const CCompartment* pObj = &pModel->getCompartments()[i];
      id = pObj->getSBMLId();

      if (!id.empty())
        {
          idMap.insert(std::pair<const std::string, const SBase*>(id, (const SBase*)NULL));
        }
    }

  iMax = pModel->getMetabolites().size();

  for (i = 0; i < iMax; ++i)
    {
      const CMetab* pObj = &pModel->getMetabolites()[i];
      id = pObj->getSBMLId();

      if (!id.empty())
        {
          idMap.insert(std::pair<const std::string, const SBase*>(id, (const SBase*)NULL));
        }
    }

  iMax = pModel->getModelValues().size();

  for (i = 0; i < iMax; ++i)
    {
      const CModelValue* pObj = &pModel->getModelValues()[i];
      id = pObj->getSBMLId();

      if (!id.empty())
        {
          idMap.insert(std::pair<const std::string, const SBase*>(id, (const SBase*)NULL));
        }
    }

  iMax = pModel->getReactions().size();

  for (i = 0; i < iMax; ++i)
    {
      const CReaction* pObj = &pModel->getReactions()[i];
      id = pObj->getSBMLId();

      if (!id.empty())
        {
          idMap.insert(std::pair<const std::string, const SBase*>(id, (const SBase*)NULL));
        }
    }

  iMax = pModel->getEvents().size();

  for (i = 0; i < iMax; ++i)
    {
      const CEvent* pObj = &pModel->getEvents()[i];
      id = pObj->getSBMLId();

      if (!id.empty())
        {
          idMap.insert(std::pair<const std::string, const SBase*>(id, (const SBase*)NULL));
        }
    }
}

void CSBMLExporter::assignSBMLIdsToReactions(CModel* pModel)
{
  std::string sbmlId;
  CDataVectorNS<CReaction>::const_iterator it = pModel->getReactions().begin(), endit = pModel->getReactions().end();

  while (it != endit)
    {
      if (it->getSBMLId().empty())
        {
          sbmlId = CSBMLExporter::createUniqueId(this->mIdMap, it->getObjectName(), false);
          it->setSBMLId(sbmlId);
          this->mIdMap.insert(std::pair<const std::string, const SBase*>(sbmlId, (const SBase*)NULL));
        }

      ++it;
    }
}

/**
 * This method goes through all compartments and events and checks if
 * there is an assignment to a volume.
 */
bool CSBMLExporter::hasVolumeAssignment(const CDataModel& dataModel)
{
  bool result = false;

  // make sure the SBML Document already exists and that it has a Model set
  if (dataModel.getModel() == NULL || this->mpSBMLDocument == NULL || this->mpSBMLDocument->getModel() == NULL) return false;

  CDataVectorNS<CCompartment>::const_iterator it = dataModel.getModel()->getCompartments().begin(), endit = dataModel.getModel()->getCompartments().end();
  CModelEntity::Status status;

  while (it != endit && result == false)
    {
      status = it->getStatus();

      if (status == CModelEntity::Status::ASSIGNMENT || status == CModelEntity::Status::ODE)
        {
          result = true;
        }

      if (!it->getInitialExpression().empty() && result == false)
        {
          if (this->mSBMLLevel > 2 || (this->mSBMLLevel == 2 && this->mSBMLVersion >= 2))
            {
              result = true;
            }
        }

      ++it;
    }

  CDataVectorN<CEvent>::const_iterator eit = dataModel.getModel()->getEvents().begin(), eendit = dataModel.getModel()->getEvents().end();

  std::string CN;
  const CDataObject* pObject = NULL;
  std::string objectType;

  while (eit != eendit && result == false)
    {
      CDataVectorN< CEventAssignment >::const_iterator itAssignment = eit->getAssignments().begin();
      CDataVectorN< CEventAssignment >::const_iterator endAssignment = eit->getAssignments().end();

      while (itAssignment != endAssignment && result == false)
        {
          CN = itAssignment->getTargetCN();

          //        now we have to get the object for the key, check if the object is a
          //        compartment, species or global parameter,
          pObject = CObjectInterface::DataObject(dataModel.getObject(CN));
          assert(pObject != NULL);
          objectType = pObject->getObjectType();

          if (objectType == "Reference")
            {
              pObject = pObject->getObjectParent();
              assert(pObject != NULL);
              objectType = pObject->getObjectType();
            }

          if (objectType == "Compartment")
            {
              result = true;
            }

          ++itAssignment;
        }

      ++eit;
    }

  return result;
}

/**
 * This method multiplies a given expression by the given object.
 * The caller is responsible for freeing the memory for the new expression.
 */
CEvaluationNode* CSBMLExporter::multiplyByObject(const CEvaluationNode* pOrigNode, const CDataObject* pObject)
{
  bool reverse = false;
  CEvaluationNode* pResult = NULL;
  assert(pOrigNode != NULL);
  assert(pObject != NULL);

  if (pOrigNode != NULL && pObject != NULL)
    {
      // first we check if this is thie reverse operation with the object
      // if so, we just drop the reverse operation, otherwise we apply the operation with the
      // object
      if (pOrigNode->mainType() == CEvaluationNode::MainType::OPERATOR &&
          pOrigNode->subType() == CEvaluationNode::SubType::DIVIDE)
        {
          // only the second child can be the object
          const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pOrigNode->getChild()->getSibling());

          if (pChild->mainType() == CEvaluationNode::MainType::OBJECT && dynamic_cast<const CEvaluationNodeObject*>(pChild)->getData() == std::string("<" + pObject->getStringCN() + ">"))
            {

              pResult = dynamic_cast<const CEvaluationNode*>(pOrigNode->getChild())->copyBranch();
              reverse = true;
            }
        }

      if (reverse == false)
        {
          CEvaluationNodeObject* pVolumeNode = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pObject->getStringCN() + ">");
          pResult = new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
          pResult->addChild(pOrigNode->copyBranch());
          pResult->addChild(pVolumeNode);
        }
    }

  return pResult;
}

/**
 * This is a general method to set the notes of an SBase object based on a COPASI
 * Annotation.
 * This will allow us to export notes on objects other than just the model.
 */
bool CSBMLExporter::setSBMLNotes(SBase* pSBase, const CAnnotation* pAnno)
{
  bool result = true;

  if (pSBase == NULL || pAnno == NULL)
    return false;

  if ((!pAnno->getNotes().empty()) && !(pAnno->getNotes().find_first_not_of(" \n\t\r") == std::string::npos))
    {
      // the new method to create notes does not add the notes tag around the notes any
      // more because libsbml 4 checks if it is there and adds it if it isn't
      XMLNode* pNotes = CSBMLExporter::createSBMLNotes(pAnno->getNotes());

      if (pNotes != NULL)
        {
          int notes_result = pSBase->setNotes(pNotes);

          if (notes_result != LIBSBML_OPERATION_SUCCESS)
            {
              // issue some warning
              std::string target;

              switch (pSBase->getTypeCode())
                {
                  case SBML_MODEL:
                    target = "the SBML model";
                    break;

                  case SBML_COMPARTMENT:
                    target = " compartment \"";
                    target += pSBase->getName();
                    target += "\"";
                    break;

                  case SBML_SPECIES:
                    target =
                      target = "species \"";
                    target += pSBase->getName();
                    target += "\"";
                    break;

                  case SBML_PARAMETER:
                    target =
                      target = "parameter \"";
                    target += pSBase->getName();
                    target += "\"";
                    break;

                  case SBML_REACTION:
                    target = "reaction \"";
                    target += pSBase->getName();
                    target += "\"";
                    break;

                  case SBML_EVENT:
                    target = "event \"";
                    target += pSBase->getName();
                    target += "\"";
                    break;

                  default:
                    target = "object \"";
                    target += pSBase->getName();
                    target += "\"";
                    break;
                }

              std::string warning = "Warning, notes could not be set on ";
              warning += target;
              warning += ", please consider reporting this to the COPASI developers.";
              CCopasiMessage(CCopasiMessage::WARNING, warning.c_str());
              result = false;
            }

          delete pNotes;
        }
      else
        {
          std::string target;

          switch (pSBase->getTypeCode())
            {
              case SBML_MODEL:
                target = "the SBML model";
                break;

              case SBML_COMPARTMENT:
                target = " compartment \"";
                target += pSBase->getName();
                target += "\"";
                break;

              case SBML_SPECIES:
                target =
                  target = "species \"";
                target += pSBase->getName();
                target += "\"";
                break;

              case SBML_PARAMETER:
                target =
                  target = "parameter \"";
                target += pSBase->getName();
                target += "\"";
                break;

              case SBML_REACTION:
                target = "reaction \"";
                target += pSBase->getName();
                target += "\"";
                break;

              case SBML_EVENT:
                target = "event \"";
                target += pSBase->getName();
                target += "\"";
                break;

              default:
                target = "object \"";
                target += pSBase->getName();
                target += "\"";
                break;
            }

          std::string warning = "Warning, notes could not be set on ";
          warning += target;
          warning += ", please consider reporting this to the COPASI developers.";
          CCopasiMessage(CCopasiMessage::WARNING, warning.c_str());
          result = false;
        }
    }

  const std::map<std::string, std::string>& map = pAnno->getUnsupportedAnnotations();

  if (!map.empty())
    {
      std::map<std::string, std::string>::const_iterator iter;

      for (iter = map.begin(); iter != map.end(); ++iter)
        pSBase->appendAnnotation(XMLNode::convertStringToXMLNode((*iter).second));
    }

  return result;
}

/**
 * Method to create a valid XHTML node from a CModels comments string.
 */
XMLNode* CSBMLExporter::createSBMLNotes(const std::string& notes_string)
{
  XMLNode* pResult = NULL;
  // check if the notes string starts with a "<"
  size_t pos = notes_string.find_first_not_of(" \n\t\r");

  if (pos != std::string::npos)
    {
      if (notes_string[pos] == '<')
        {
          // create an XMLNode
          XMLNode* pNotes = XMLNode::convertStringToXMLNode(notes_string);

          assert(pNotes != NULL);

          if (pNotes != NULL)
            {
              size_t pos2 = notes_string.find_first_of(" \t\n\r>");

              if (pos2 != std::string::npos)
                {
                  // check if the XML node is a dummy node
                  std::string elementName = notes_string.substr(pos + 1, pos2 - pos - 1);

                  if (elementName == pNotes->getName())
                    {
                      pResult = pNotes;

                      // make sure the namespace is set
                      if (pResult->getURI() != "http://www.w3.org/1999/xhtml")
                        {
                          std::string prefix = pResult->getPrefix();
                          std::string ns = "http://www.w3.org/1999/xhtml";

                          if (!prefix.empty())
                            {
                              ns = prefix + ":" + ns;
                            }

                          pResult->setTriple(XMLTriple(pResult->getName(), ns, prefix));
                          int tmp = pResult->addNamespace("http://www.w3.org/1999/xhtml", prefix);
                          assert(tmp == LIBSBML_OPERATION_SUCCESS);
                        }

                      // If it is a html element assure that we have a head.
                      if (elementName == "html")
                        {
                          if (!pResult->hasChild("head"))
                            {
                              // Add a head and title element
                              std::string Head = "<head xmlns=\"http://www.w3.org/1999/xhtml\"><title xmlns=\"http://www.w3.org/1999/xhtml\"></title></head>";
                              XMLNode * pHead = XMLNode::convertStringToXMLNode(Head);

                              pResult->insertChild(0, *pHead);
                              delete pHead;
                            }
                          else
                            {
                              XMLNode Head = pResult->getChild("head");

                              if (!Head.hasChild("title"))
                                {
                                  // Add a title element
                                  std::string Title = "<title xmlns=\"http://www.w3.org/1999/xhtml\"></title>";
                                  XMLNode * pTitle = XMLNode::convertStringToXMLNode(Title);

                                  Head.insertChild(0, *pTitle);
                                  delete pTitle;

                                  XMLNode * pRemove = pResult->removeChild(pResult->getIndex("head"));
                                  pdelete(pRemove);

                                  pResult->insertChild(0, Head);
                                }
                            }
                        }
                    }
                  else
                    {
                      // the top level node is a dummy node
                      // we replace the dummy node by a body tag
                      // libSBML seems to create a dummy node which is considered
                      // an EOF node
                      if (pNotes->isEOF())
                        {
                          XMLAttributes attr;
                          XMLNamespaces xmlns;
                          pResult = new XMLNode(XMLTriple("body", "http://www.w3.org/1999/xhtml", ""), attr, xmlns);
                          // copy all children from  pNotes to pResult
                          unsigned int i, iMax = pNotes->getNumChildren();

                          for (i = 0; i < iMax; ++i)
                            {
                              pResult->addChild(pNotes->getChild(i));
                            }

                          delete pNotes;

                          pResult->unsetEnd();
                          assert(pResult->isEnd() == false);
                        }
                      else
                        {
                          pResult = pNotes;
                          pResult->setTriple(XMLTriple("body", "http://www.w3.org/1999/xhtml", ""));
                          assert(pResult->isElement() == true);
                          assert(pResult->getNumChildren() == 0 || pResult->isEnd() == false);
                        }

                      int tmp = pResult->addNamespace("http://www.w3.org/1999/xhtml", "");
                      assert(tmp == LIBSBML_OPERATION_SUCCESS);
                    }
                }
              else
                {
                  // put the complete string in a pre tag
                  std::string new_notes = "<pre xmlns=\"http://www.w3.org/1999/xhtml\">" + notes_string + "</pre>";
                  pResult = XMLNode::convertStringToXMLNode(new_notes);
                  assert(pResult != NULL);
                  assert(pResult->getName() == "pre");
                  assert(pResult->getURI() == "http://www.w3.org/1999/xhtml");
                  assert(pResult->getNumChildren() != 0);
                }
            }
        }
      else
        {
          // put the complete notes string into a body tag
          // check if the string contains "</" or "/>" in that case
          // we assume that the string contains markup
          //
          std::string new_notes;

          if (notes_string.find("</") != std::string::npos || notes_string.find("/>") != std::string::npos)
            {
              new_notes = "<body xmlns=\"http://www.w3.org/1999/xhtml\">" + notes_string + "</body>";
            }
          else
            {
              new_notes = "<body xmlns=\"http://www.w3.org/1999/xhtml\"><pre>" + notes_string + "</pre></body>";
            }

          pResult = XMLNode::convertStringToXMLNode(new_notes);
          assert(pResult != NULL);
          assert(pResult->getName() == "body");
          assert(pResult->getURI() == "http://www.w3.org/1999/xhtml");
          assert(pResult->getNumChildren() != 0);
        }
    }
  else
    {
      // create an empty pre element
      std::string new_notes = "<pre xmlns=\"http://www.w3.org/1999/xhtml\"/>";
      pResult = XMLNode::convertStringToXMLNode(new_notes);
      assert(pResult != NULL);
      assert(pResult->getName() == "pre");
      assert(pResult->getURI() == "http://www.w3.org/1999/xhtml");
      assert(pResult->getNumChildren() == 0);
    }

  return pResult;
}

/**
 * Converts the SBML model given in SBML Level 1 Version 2 format to SBML Level 1 Version 1.
 * The method basically removes the namespace attribute on the sbml element
 * and changes the version from 2 to 1.
 * It also renames all "species" elements to "specie".
 * All other changes between SBML Level 1 Version 2 and Level 1 Version 1 should not be relevant here.
 */
void CSBMLExporter::convert_to_l1v1(std::string& l1v2_string)
{
  size_t start_pos = 0, end_pos = 0;
  // find the sbml tag
  start_pos = l1v2_string.find("<sbml ");

  if (start_pos == std::string::npos)
    {
      // throw an exception
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Error. Could not find <sbml> element in string. Can't convert string to SBML Level 1 Version 1.");
    }

  // find the following closing >
  end_pos = l1v2_string.find(">", start_pos);

  if (end_pos == std::string::npos)
    {
      // throw an exception
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Error. Could not find closing bracket for sbml tag. Can't convert string to SBML Level 1 Version 1.");
    }

  // in that range check for the namespace attribute
  size_t pos = l1v2_string.find("http://www.sbml.org/sbml/level1");

  if (pos == std::string::npos || pos >= end_pos)
    {
      // throw an exception
      // Actually we could ignore this and hope that everything is OK, but fact is that this should not happen,
      // so we stop.
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Error. Could not find find namespace attribute for sbml element. Can't convert string to SBML Level 1 Version 1.");
    }

  // remove the namespace attribute
  size_t pos2 = l1v2_string.find("\"", pos);

  if (pos2 == std::string::npos || pos2 >= end_pos)
    {
      // throw an exception
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Error. Could not find find closing quotation mark for namespace value. Can't convert string to SBML Level 1 Version 1.");
    }

  pos = l1v2_string.rfind("xmlns", pos);

  if (pos == std::string::npos || pos <= start_pos)
    {
      // throw an exception
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Error. Could not find find xmlns attribute for namespace. Can't convert string to SBML Level 1 Version 1.");
    }

  // remove everything between pos and pos2, including pos2
  l1v2_string.erase(pos, pos2 - pos + 1);
  // update the end marker
  // since we have deleted pos2-pos+1 characters, the end_marker has
  // to be shifted as many characters left
  end_pos -= pos2 - pos + 1;
  // find the version attribute in that range
  pos = l1v2_string.find("version", start_pos);

  if (pos == std::string::npos || pos >= end_pos)
    {
      // throw an exception
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Error. Could not find version attribute. Can't convert string to SBML Level 1 Version 1.");
    }

  pos = l1v2_string.find("\"", pos);

  if (pos == std::string::npos || pos >= end_pos)
    {
      // throw an exception
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Error. Could not find opening quotation mark for version attribute value. Can't convert string to SBML Level 1 Version 1.");
    }

  pos2 = l1v2_string.find("\"", pos + 1);

  if (pos2 == std::string::npos || pos2 >= end_pos)
    {
      // throw an exception
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Error. Could not find opening quotation mark for version attribute value. Can't convert string to SBML Level 1 Version 1.");
    }

  // change the version from 2 to 1
  // in between pos and pos2 there needs to be the number 2 and maybe some whitespace.
  // We don't want to make this to complicated and just assume that there is only one character in between the two quotation marks
  // Actually the 1 is already set in the rest of the exporting routines, so this is just there to be save
  if (pos2 != pos + 2 || (l1v2_string[pos + 1] != '2' && l1v2_string[pos + 1] != '1'))
    {
      // throw an exception
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Error. Version attribute value not what we expected. Can't convert string to SBML Level 1 Version 1.");
    }

  l1v2_string[pos + 1] = '1';
  //
  // change all species elements to specie
  start_pos = l1v2_string.find("<species ");

  while (start_pos != std::string::npos)
    {
      // just change start_pos + 7 to a space
      start_pos += 7;
      l1v2_string[start_pos] = ' ';
      ++start_pos;
      start_pos = l1v2_string.find("<species ", start_pos);
    }

  // we also have to replace the closing tag
  // for this we assume that the closing tag does
  // not contain any whitespaces
  start_pos = l1v2_string.find("</species>");

  while (start_pos != std::string::npos)
    {
      // just change start_pos + 8 to a >
      // and start_pos + 9 to a space
      start_pos += 8;
      l1v2_string[start_pos] = '>';
      ++start_pos;
      l1v2_string[start_pos] = ' ';
      ++start_pos;
      start_pos = l1v2_string.find("</species>", start_pos);
    }
}
