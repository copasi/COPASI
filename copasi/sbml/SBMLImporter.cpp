// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#define USE_LAYOUT 1

#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <limits>
#include <cmath>

#include <sbml/SBMLReader.h>
#include <sbml/SBMLDocument.h>
#include <sbml/Compartment.h>
#include <sbml/Species.h>
#include <sbml/SpeciesReference.h>
#include <sbml/Reaction.h>
#include <sbml/LocalParameter.h>

#include <sbml/SBMLTransforms.h>
#include "IdList.h" // this file is missing from the libSBML distribution!
#include <sbml/conversion/ConversionProperties.h>
#include <sbml/packages/layout/extension/LayoutModelPlugin.h>
#define INIT_DEFAULTS(element) \
  {\
    element.initDefaults();\
  }

#include <sbml/KineticLaw.h>
#include <sbml/math/FormulaFormatter.h>
#include <sbml/Model.h>
#include <sbml/UnitKind.h>
#include <sbml/Unit.h>
#include <sbml/Parameter.h>
#include <sbml/InitialAssignment.h>
#include <sbml/Rule.h>
#include <sbml/FunctionDefinition.h>
#include <sbml/UnitDefinition.h>

#include "copasi/copasi.h"

#include "copasi/report/CKeyFactory.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CEvent.h"
#include "copasi/function/CNodeK.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CExpression.h"
#include "copasi/function/CFunctionParameters.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/utilities/CCopasiTree.h"
#include "copasi/utilities/CUnit.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/MIRIAM/CRDFGraphConverter.h"
#include "copasi/compareExpressions/CEvaluationNodeNormalizer.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/commandline/COptions.h"

#include "SBMLImporter.h"
#include "SBMLUtils.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/commandline/CConfigurationFile.h"

#include "copasi/layout/SBMLDocumentLoader.h"
#include "copasi/layout/CListOfLayouts.h"

#include "copasi/utilities/CCopasiMessage.h"

#include <copasi/MIRIAM/CBiologicalDescription.h>
#include <copasi/MIRIAM/CModelMIRIAMInfo.h>

#if LIBSBML_HAS_PACKAGE_COMP

#include <sbml/util/PrefixTransformer.h>
#include <sbml/packages/comp/extension/CompModelPlugin.h>

class CPrefixNameTransformer : public PrefixTransformer
{
public:
  CPrefixNameTransformer() {}

  static void replaceStringInPlace(std::string& subject, const std::string& search,
                                   const std::string& replace)
  {
    size_t pos = 0;

    while ((pos = subject.find(search, pos)) != std::string::npos)
      {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
      }
  }

  static inline std::string &rtrim(std::string &str)
  {
    size_t endpos = str.find_last_not_of(" \t");

    if (std::string::npos != endpos)
      {
        str = str.substr(0, endpos + 1);
      }

    return str;
  }

  const std::string& cleanName(std::string& prefix)
  {
    std::replace(prefix.begin(), prefix.end(), '_', ' ');
    replaceStringInPlace(prefix, "  ", " ");
    rtrim(prefix);
    return prefix;
  }

  virtual int transform(SBase* element)
  {
    if (element == NULL || getPrefix().empty())
      return LIBSBML_OPERATION_SUCCESS;

    // set up ids
    PrefixTransformer::transform(element);

    // skip local parameters, as they are not renamed
    if (element->getTypeCode() == SBML_LOCAL_PARAMETER)
      return LIBSBML_OPERATION_SUCCESS;

    // setup names
    if (element->isSetName())
      {
        std::stringstream newName;
        std::string prefix = getPrefix();
        newName << element->getName() << " (" << cleanName(prefix) << ")";
        element->setName(newName.str());
      }

    return LIBSBML_OPERATION_SUCCESS;
  }
};

#endif

#if LIBSBML_VERSION >= 51801

#include <sbml/util/CallbackRegistry.h>

class SbmlProgressCallback : public Callback
{
public:
  SbmlProgressCallback(CProcessReport * pProcessReport)
    : mpProcessReport(pProcessReport)
  {}

  virtual int process(SBMLDocument* doc)
  {
    if (mpProcessReport != NULL
        && !mpProcessReport->progress())
      {
        CCopasiMessage(CCopasiMessage::WARNING, "The operation was interrupted.");
        return LIBSBML_OPERATION_FAILED;
      }

    return LIBSBML_OPERATION_SUCCESS;
  }

private:
  CProcessReport * mpProcessReport;
};

#else

class SbmlProgressCallback
{
  SbmlProgressCallback(CProcessReport*) {}
};

#endif

// static
C_FLOAT64 SBMLImporter::round(const C_FLOAT64 & x)
{
  return
    x < 0.0 ? -floor(-x + 0.5) : floor(x + 0.5);
}

// static
bool SBMLImporter::areApproximatelyEqual(const double & x, const double & y, const double & t)
{
  double Scale =
    (fabs(x) + fabs(y)) * t;

  // Avoid underflow
  if (Scale < 100.0 * std::numeric_limits< C_FLOAT64 >::min())
    return true;

  return 2 * fabs(x - y) < Scale;
}

std::string getOriginalSBMLId(Parameter* parameter, std::string& type)
{
  type = "";

  if (parameter == NULL) return "";

  if (!parameter->isSetAnnotation()) return "";

  XMLNode* node = parameter->getAnnotation();

  if (node->getNumChildren() < 1) return "";

  for (unsigned int i = 0; i < node->getNumChildren(); ++i)
    {
      const XMLNode& current = node->getChild(i);

      if (current.getNamespaces().containsUri("http://copasi.org/initialValue"))
        {
          type = current.getAttrValue("type");
          return current.getAttrValue("parent");
        }
    }

  return "";
}

std::string getInitialCNForSBase(SBase* sbase, std::map<const CDataObject*, SBase*>& copasi2sbmlmap, const std::string& type)
{
  std::map<const CDataObject*, SBase*>::const_iterator it;

  for (it = copasi2sbmlmap.begin(); it != copasi2sbmlmap.end(); ++it)
    {
      if (it->second != sbase)
        continue;

      if (!type.empty())
        {
          auto obj = it->first->getObject(std::string("Reference=") + type);

          if (obj)
            return obj->getStringCN();
        }

      const CMetab *metab = dynamic_cast<const CMetab*>(it->first);

      if (metab != NULL)
        return metab->getInitialConcentrationReference()->getStringCN();

      const CCompartment *comp = dynamic_cast<const CCompartment*>(it->first);

      if (comp != NULL)
        return comp->getInitialValueReference()->getStringCN();

      const CModelValue *param = dynamic_cast<const CModelValue*>(it->first);

      if (param != NULL)
        return param->getInitialValueReference()->getStringCN();
    }

  return "";
}

/**
 * Creates and returns a Copasi CModel from the SBMLDocument given as argument.
 */
bool
SBMLImporter::reportCurrentProgressOrStop()
{
  if (mpProcessReport == NULL) return false;

  return !mpProcessReport->progressItem(mCurrentStepHandle);
}

void
SBMLImporter::finishCurrentStep()
{
  if (mpProcessReport == NULL || mCurrentStepHandle == C_INVALID_INDEX)  return;

  mpProcessReport->finishItem(mCurrentStepHandle);
  mCurrentStepHandle = C_INVALID_INDEX;
}

void
SBMLImporter::finishImport()
{
  if (mpProcessReport == NULL)  return;

  finishCurrentStep();

  mpProcessReport->finishItem(mGlobalStepHandle);
}

bool
SBMLImporter::createProgressStepOrStop(unsigned C_INT32 globalStep,
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

CModel* SBMLImporter::createCModelFromSBMLDocument(SBMLDocument* sbmlDocument, std::map<const CDataObject*, SBase*>& copasi2sbmlmap)
{
  Model* sbmlModel = sbmlDocument->getModel();

  /* Create an empty model and set the title. */
  this->mpCopasiModel = new CModel(mpDataModel);
  copasi2sbmlmap[this->mpCopasiModel] = sbmlModel;
  this->mpCopasiModel->setLengthUnit("m");
  this->mpCopasiModel->setAreaUnit("m^2");
  this->mpCopasiModel->setVolumeUnit("l");
  this->mpCopasiModel->setTimeUnit("s");
  this->mpCopasiModel->setQuantityUnit("mol", CCore::Framework::Concentration);
  this->mpCopasiModel->setSBMLId(sbmlModel->getId());

  mCurrentStepHandle = C_INVALID_INDEX;
  mCurrentStepCounter = 0;
  mCurrentStepTotal = 0;

  if (createProgressStepOrStop(3, 1, "Importing notes/annotations..."))
    return NULL;

  SBMLImporter::importMIRIAM(sbmlModel, this->mpCopasiModel);
  SBMLImporter::importNotes(this->mpCopasiModel, sbmlModel);

  if (createProgressStepOrStop(4, 1, "Importing units..."))
    return NULL;

  importUnitsFromSBMLDocument(sbmlModel, mpCopasiModel);

  if (this->isStochasticModel(sbmlModel))
    {
      this->mpCopasiModel->setModelType(CModel::ModelType::stochastic);
    }
  else
    {
      this->mpCopasiModel->setModelType(CModel::ModelType::deterministic);
    }

  std::string title = sbmlModel->getName();

  if (isEmptyOrWhiteSpace(title))
    {
      title = "NoName";
    }

  size_t idCount = 0;

  while (mpDataModel->getObject("Model=" + title) != NULL)
    {
      std::stringstream str; str << sbmlModel->getName() << "_" << ++idCount;
      title = str.str();
    }

  this->mpCopasiModel->setObjectName(title);

  // fill the set of SBML species reference ids because
  // we need this to check for references to species references in all expressions
  // as long as we do not support these references
  SBMLImporter::updateSBMLSpeciesReferenceIds(sbmlModel, this->mSBMLSpeciesReferenceIds);

  /* import the functions */
  unsigned int counter;
  size_t num;

  CDataVectorN< CFunction > & functions = CRootContainer::getFunctionList()->loadedFunctions();

  num = functions.size();

  if (createProgressStepOrStop(5, num, "Importing function definitions..."))
    return NULL;

  this->sbmlIdMap.clear();

  for (counter = 0; counter < num; ++counter)
    {
      CFunction* tree = &functions[counter];

      if (!tree->getSBMLId().empty())
        {
          this->sbmlIdMap[tree] = tree->getSBMLId();
          tree->setSBMLId("");
        }
    }

  this->importFunctionDefinitions(sbmlModel, copasi2sbmlmap);

  // try to find global parameters that represent Avogadro's number
  this->findAvogadroConstant(sbmlModel, this->mpCopasiModel->getQuantity2NumberFactor());

  mCompartmentMap.clear();

  /* Create the compartments */
  num = sbmlModel->getNumCompartments();

  if (createProgressStepOrStop(6, num, "Importing compartments..."))
    return NULL;

  for (counter = 0; counter < num; counter++)
    {
      Compartment* sbmlCompartment = sbmlModel->getCompartment(counter);

      if (sbmlCompartment == NULL)
        {
          fatalError();
        }

      CCompartment* pCopasiCompartment = NULL;

      try
        {
          pCopasiCompartment = this->createCCompartmentFromCompartment(sbmlCompartment, this->mpCopasiModel, copasi2sbmlmap, sbmlModel);
        }
      catch (...)
        {
          std::ostringstream os;
          os << "Error while importing compartment \"";
          os << sbmlCompartment->getId() << "\".";

          // check if the last message on the stack is an exception
          // and if so, add the message text to the current exception
          if (CCopasiMessage::peekLastMessage().getType() == CCopasiMessage::EXCEPTION)
            {
              // we only want the message, not the timestamp line
              std::string text = CCopasiMessage::peekLastMessage().getText();
              os << text.substr(text.find("\n"));
            }

          CCopasiMessage(CCopasiMessage::EXCEPTION, os.str().c_str());
        }

      std::string key = sbmlCompartment->getId();

      if (mLevel == 1)
        {
          key = sbmlCompartment->getName();
        }

      mCompartmentMap[key] = pCopasiCompartment;
      ++mCurrentStepCounter;

      if (reportCurrentProgressOrStop())
        return NULL;
    }

  // set the hasOnlySubstanceUnits flag on all species with zero compartment spatial dimension
  std::map<Species*, Compartment*>::iterator it = this->mSubstanceOnlySpecies.begin();
  std::map<Species*, Compartment*>::iterator endIt = this->mSubstanceOnlySpecies.end();

  while (it != endIt)
    {
      it->first->setHasOnlySubstanceUnits(true);
      ++it;
    }

  /* Create all species */
  num = sbmlModel->getNumSpecies();

  if (createProgressStepOrStop(7, num, "Importing species..."))
    return NULL;

  for (counter = 0; counter < num; ++counter)
    {
      Species* sbmlSpecies = sbmlModel->getSpecies(counter);

      if (sbmlSpecies == NULL)
        {
          fatalError();
        }

      CCompartment* pCopasiCompartment = mCompartmentMap[sbmlSpecies->getCompartment()];

      if (pCopasiCompartment != NULL)
        {
          CMetab* pCopasiMetabolite = NULL;

          try
            {
              pCopasiMetabolite = this->createCMetabFromSpecies(sbmlSpecies, this->mpCopasiModel, pCopasiCompartment, copasi2sbmlmap, sbmlModel);
            }
          catch (...)
            {
              std::ostringstream os;
              os << "Error while importing species \"";
              os << sbmlSpecies->getId() << "\".";

              // check if the last message on the stack is an exception
              // and if so, add the message text to the current exception
              if (CCopasiMessage::peekLastMessage().getType() == CCopasiMessage::EXCEPTION)
                {
                  // we only want the message, not the timestamp line
                  std::string text = CCopasiMessage::peekLastMessage().getText();
                  os << text.substr(text.find("\n"));
                }

              CCopasiMessage(CCopasiMessage::EXCEPTION, os.str().c_str());
            }

          std::string key;

          if (this->mLevel == 1)
            {
              key = sbmlSpecies->getName();
            }
          else
            {
              key = sbmlSpecies->getId();
            }

          this->speciesMap[key] = pCopasiMetabolite;
        }
      else
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 5, sbmlSpecies->getCompartment().c_str(), sbmlSpecies->getId().c_str());
        }

      ++mCurrentStepCounter;

      if (reportCurrentProgressOrStop())
        return NULL;
    }

  /* Create the global Parameters */
  num = sbmlModel->getNumParameters();

  if (createProgressStepOrStop(8, num, "Importing global parameters..."))
    return NULL;

  for (counter = 0; counter < num; ++counter)
    {
      Parameter* sbmlParameter = sbmlModel->getParameter(counter);

      if (sbmlParameter == NULL)
        {
          continue;
        }

      try
        {
          std::string type;
          std::string sbmlId = getOriginalSBMLId(sbmlParameter, type);

          // don't import parameter if it is one of our special ones instead get the cn to the target
          if (mImportInitialValues  && !sbmlId.empty())
            {
              Species* species = sbmlModel->getSpecies(sbmlId);

              if (species != NULL)
                {
                  mKnownInitalValues[sbmlParameter->getId()] = getInitialCNForSBase(species, copasi2sbmlmap, type);
                  continue;
                }

              Compartment *comp = sbmlModel->getCompartment(sbmlId);

              if (comp != NULL)
                {
                  mKnownInitalValues[sbmlParameter->getId()] = getInitialCNForSBase(comp, copasi2sbmlmap, type);
                  continue;
                }

              Parameter* param = sbmlModel->getParameter(sbmlId);

              if (param != NULL)
                {
                  mKnownInitalValues[sbmlParameter->getId()] = getInitialCNForSBase(param, copasi2sbmlmap, type);
                  continue;
                }
            }

          this->createCModelValueFromParameter(sbmlParameter, this->mpCopasiModel, copasi2sbmlmap);
        }
      catch (...)
        {
          std::ostringstream os;
          os << "Error while importing parameter \"";
          os << sbmlParameter->getId() << "\".";

          // check if the last message on the stack is an exception
          // and if so, add the message text to the current exception
          if (CCopasiMessage::peekLastMessage().getType() == CCopasiMessage::EXCEPTION)
            {
              // we only want the message, not the timestamp line
              std::string text = CCopasiMessage::peekLastMessage().getText();
              os << text.substr(text.find("\n"));
            }

          CCopasiMessage(CCopasiMessage::EXCEPTION, os.str().c_str());
        }

      ++mCurrentStepCounter;

      if (reportCurrentProgressOrStop())
        return NULL;
    }

  // the information that is collected here is used in the creation of the reactions to
  // adjust the stoichiometry of substrates and products with the conversion factors from
  // the SBML model

  // now that all parameters have been imported, we can check if the model
  // defines a global conversion factor
  if (this->mLevel > 2 && sbmlModel->isSetConversionFactor())
    {
      this->mConversionFactorFound = true;
      std::string id = sbmlModel->getConversionFactor();
      assert(id != "");
      std::map<std::string, const CModelValue*>::const_iterator pos = this->mSBMLIdModelValueMap.find(id);
      assert(pos != this->mSBMLIdModelValueMap.end());

      if (pos != this->mSBMLIdModelValueMap.end())
        {
          this->mpModelConversionFactor = pos->second;
        }
      else
        {
          fatalError();
        }
    }

  // we need to go through all species again and find conversion factors
  // right now I don't want to change the order of importing model values
  // and species since I am not sure what implications that would have
  if (this->mLevel > 2)
    {
      num = sbmlModel->getNumSpecies();

      for (counter = 0; counter < num; ++counter)
        {
          Species* sbmlSpecies = sbmlModel->getSpecies(counter);

          if (sbmlSpecies->isSetConversionFactor())
            {
              this->mConversionFactorFound = true;
              std::map<std::string, const CModelValue*>::const_iterator pos = this->mSBMLIdModelValueMap.find(sbmlSpecies->getConversionFactor());

              if (pos != this->mSBMLIdModelValueMap.end())
                {
                  this->mSpeciesConversionParameterMap[sbmlSpecies->getId()] = pos->second;
                }
            }
        }
    }

  if (!this->mIgnoredParameterUnits.empty())
    {
      std::ostringstream os;
      std::vector<std::string>::iterator errorIt = this->mIgnoredParameterUnits.begin();

      while (errorIt != this->mIgnoredParameterUnits.end())
        {
          os << *errorIt << ", ";
          ++errorIt;
        }

      std::string s = os.str();
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 26, s.substr(0, s.size() - 2).c_str());
    }

  /* Create all reactions */
  num = sbmlModel->getNumReactions();

  if (createProgressStepOrStop(9, num, "Importing reactions..."))
    return NULL;

  this->mDivisionByCompartmentReactions.clear();
  this->mFastReactions.clear();
  this->mReactions.clear();
  this->mReactionsWithReplacedLocalParameters.clear();
  this->mParameterFluxMap.clear();

  for (counter = 0; counter < num; counter++)
    {
      Reaction* current = sbmlModel->getReaction(counter);

      if (current->isSetId())
        mReactions.insert(current->getId());
    }

  for (counter = 0; counter < num; counter++)
    {
      try
        {
          Reaction* reaction = sbmlModel->getReaction(counter);

          if (reaction->getNumReactants() + reaction->getNumProducts() == 0)
            {
              if (reaction->isSetId()
                  &&  reaction->isSetKineticLaw()
                  && reaction->getKineticLaw()->isSetMath())
                {
                  // create a an ode rule for that reaction instead
                  std::string id = reaction->getId();
                  reaction->setId(std::string("unused_") + id);
                  Parameter* param = sbmlModel->createParameter();
                  param->setId(id);
                  param->setValue(0);

                  //
                  AssignmentRule *rule = sbmlModel->createAssignmentRule();
                  rule->setVariable(id);
                  rule->setMath(reaction->getKineticLaw()->getMath());

                  // create copasi model value for it
                  createCModelValueFromParameter(param, mpCopasiModel, copasi2sbmlmap);
                }

              continue;
            }

          this->createCReactionFromReaction(reaction, sbmlModel, this->mpCopasiModel, copasi2sbmlmap);
        }
      catch (...)
        {
          std::ostringstream os;
          os << "Error while importing reaction \"";
          os << sbmlModel->getReaction(counter)->getId() << "\".";

          // check if the last message on the stack is an exception
          // and if so, add the message text to the current exception
          if (CCopasiMessage::peekLastMessage().getType() == CCopasiMessage::EXCEPTION)
            {
              // we only want the message, not the timestamp line
              std::string text = CCopasiMessage::peekLastMessage().getText();
              os << text.substr(text.find("\n"));
            }

          CCopasiMessage(CCopasiMessage::EXCEPTION, os.str().c_str());
        }

      ++mCurrentStepCounter;

      if (reportCurrentProgressOrStop())
        return NULL;
    }

  if (!this->mDivisionByCompartmentReactions.empty())
    {
      // create the error message
      std::string idList;
      std::set<std::string>::const_iterator it = this->mDivisionByCompartmentReactions.begin();
      std::set<std::string>::const_iterator endit = this->mDivisionByCompartmentReactions.end();

      while (it != endit)
        {
          idList += (*it);
          idList += ", ";
          ++it;
        }

      idList = idList.substr(0, idList.length() - 2);
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 17, idList.c_str());
    }

  if (!this->mFastReactions.empty())
    {
      // create the error message
      std::string idList;
      std::set<std::string>::const_iterator it = this->mFastReactions.begin();
      std::set<std::string>::const_iterator endit = this->mFastReactions.end();

      while (it != endit)
        {
          idList += (*it);
          idList += ", ";
          ++it;
        }

      idList = idList.substr(0, idList.length() - 2);
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 29, idList.c_str());
    }

  if (!this->mReactionsWithReplacedLocalParameters.empty())
    {
      // create the error message
      std::string idList;
      std::set<std::string>::const_iterator it = this->mReactionsWithReplacedLocalParameters.begin();
      std::set<std::string>::const_iterator endit = this->mReactionsWithReplacedLocalParameters.end();

      while (it != endit)
        {
          idList += (*it);
          idList += ", ";
          ++it;
        }

      idList = idList.substr(0, idList.length() - 2);
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 87, idList.c_str());
    }

  if (!this->mParameterFluxMap.empty())
    {
      CDataVectorNS < CReaction >::iterator reactionIt = mpCopasiModel->getReactions().begin();

      for (; reactionIt != mpCopasiModel->getReactions().end(); ++reactionIt)
        {
          CReaction& reaction = *reactionIt;
          std::map < std::string, CModelValue* >::iterator it =
            mParameterFluxMap.find(reaction.getSBMLId());

          if (it == mParameterFluxMap.end())
            continue;

          it->second->setExpression("<" + reaction.getFluxReference()->getStringCN() + ">");
        }
    }

  // import the initial assignments
  // we do this after the reactions since initial assignments can reference reaction ids.

  if (createProgressStepOrStop(10, sbmlModel->getNumInitialAssignments(), "Importing initial assignments..."))
    return NULL;

  importInitialAssignments(sbmlModel, copasi2sbmlmap, this->mpCopasiModel);

  // import all rules
  // we have to import them after the reactions since they can reference a reaction
  // id which has to be known when importing the rule

  /* Create the rules */
  // rules should be imported after reactions because we use the mSBMLSpeciesReferenceIds to determine if a
  // rule changes a species reference (stoichiometry
  // Since COPASI does not support this, we need to ignore the rule
  this->areRulesUnique(sbmlModel);
  num = sbmlModel->getNumRules();

  if (createProgressStepOrStop(11, num, "Importing Rules..."))
    return NULL;

  for (counter = 0; counter < num; ++counter)
    {
      Rule* sbmlRule = sbmlModel->getRule(counter);

      if (sbmlRule == NULL)
        {
          fatalError();
        }

      // improve the error message a bit.
      try
        {
          this->importSBMLRule(sbmlRule, copasi2sbmlmap, sbmlModel);
        }
      catch (...)
        {
          std::ostringstream os;
          os << "Error while importing rule for variable \"";
          os << sbmlRule->getVariable() << "\".";

          // check if the last message on the stack is an exception
          // and if so, add the message text to the current exception
          if (CCopasiMessage::peekLastMessage().getType() == CCopasiMessage::EXCEPTION)
            {
              // we only want the message, not the time stamp line
              std::string text = CCopasiMessage::peekLastMessage().getText();
              os << text.substr(text.find("\n"));
            }

          CCopasiMessage(CCopasiMessage::EXCEPTION, os.str().c_str());
        }

      ++mCurrentStepCounter;

      if (reportCurrentProgressOrStop())
        return NULL;
    }

  if (sbmlModel->getNumConstraints() > 0)
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 49);
    }

  // TODO Create all constraints
  // TODO Since we don't have constraints yet, there is no code here.
  // TODO When implementing import of constraints, don't forget to replace calls to
  // TODO explicitly time dependent functions in the constraints math expression.

  // import all events
  // events should be imported after reactions because we use the mSBMLSpeciesReferenceIds to determine if an
  // event assignment changes a species reference (stoichiometry
  // Since COPASI does not support this, we need to ignore the event assignment

  if (createProgressStepOrStop(12, sbmlModel->getNumEvents(), "Importing events..."))
    return NULL;

  this->importEvents(sbmlModel, this->mpCopasiModel, copasi2sbmlmap);

  if (this->mUnsupportedRuleFound)
    {
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 3);
    }

  if (this->mRateRuleForSpeciesReferenceIgnored == true)
    {
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 94, "Rate rule", "Rate rule");
    }

  if (this->mEventAssignmentForSpeciesReferenceIgnored == true)
    {
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 94, "Event assignment", "event assignment");
    }

  if (this->mConversionFactorFound == true)
    {
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 100);
    }

  // unset the hasOnlySubstanceUnits flag on all species that had it set
  it = this->mSubstanceOnlySpecies.begin();
  endIt = this->mSubstanceOnlySpecies.end();

  while (it != endIt)
    {
      it->first->setHasOnlySubstanceUnits(false);
      ++it;
    }

  // Before we set anything we compile the model.
  if (createProgressStepOrStop(13,
                               4,
                               "Setting initial values..."
                              ))
    return NULL;

  if (!mpCopasiModel->compileIfNecessary(mpProcessReport))
    {
      CCopasiMessage Message(CCopasiMessage::ERROR,
                             "The SBML file could not be imported.");
      return NULL;
    }

  ++mCurrentStepCounter;

  if (reportCurrentProgressOrStop())
    return NULL;

  // All initial values must be properly set so that we can compute the
  // stoichiometric expressions.
  setInitialValues(this->mpCopasiModel, copasi2sbmlmap);
  ++mCurrentStepCounter;

  if (reportCurrentProgressOrStop())
    return NULL;

  // evaluate and apply the initial expressions
  this->applyStoichiometricExpressions(copasi2sbmlmap, sbmlModel);
  ++mCurrentStepCounter;

  if (reportCurrentProgressOrStop())
    return NULL;

  // now we apply the conversion factors
  if (this->mLevel > 2)
    {
      this->applyConversionFactors();
      ++mCurrentStepCounter;

      if (reportCurrentProgressOrStop())
        return NULL;
    }

  if (createProgressStepOrStop(14,
                               (unsigned C_INT32)(mpCopasiModel->getReactions().size()
                                   + this->mpCopasiModel->getCompartments().size()
                                   + this->mpCopasiModel->getMetabolites().size()
                                   + this->mpCopasiModel->getModelValues().size()),
                               "Searching unused functions..."
                              ))
    return NULL;

  this->removeUnusedFunctions(copasi2sbmlmap);

  // remove the temporary avogadro parameter if one was created
  if (this->mAvogadroCreated == true)
    {
      const Parameter* pParameter = *this->mPotentialAvogadroNumbers.begin();

      std::string sbmlId;

      // We need to remove unused quantities in COPASI too.
      if (this->mLevel == 1)
        {
          sbmlId = pParameter->getName();
        }
      else
        {
          sbmlId = pParameter->getId();
        }

      CDataVectorN< CModelValue >::const_iterator itMV = mpCopasiModel->getModelValues().begin();
      CDataVectorN< CModelValue >::const_iterator endMV = mpCopasiModel->getModelValues().end();

      for (; itMV != endMV; ++itMV)
        {
          if (itMV->getSBMLId() == sbmlId)
            {
              CDataObject::DataObjectSet Functions;
              CDataObject::DataObjectSet Reactions;
              CDataObject::DataObjectSet Metabolites;
              CDataObject::DataObjectSet Values;
              CDataObject::DataObjectSet Compartments;
              CDataObject::DataObjectSet Events;
              CDataObject::DataObjectSet EventAssignments;
              CDataObject::DataObjectSet Tasks;

              if (!mpCopasiModel->appendAllDependents(*itMV, Reactions, Metabolites, Compartments, Values, Events, EventAssignments))
                {
                  mpCopasiModel->removeModelValue(itMV, false);

                  std::map<const CDataObject*, SBase*>::iterator found = copasi2sbmlmap.find(itMV);

                  if (found != copasi2sbmlmap.end())
                    {
                      copasi2sbmlmap.erase(found);
                    }
                }

              break;
            }
        }

      ListOf* pList = sbmlModel->getListOfParameters();
      unsigned i, iMax = pList->size();

      for (i = 0; i < iMax; ++i)
        {
          if (pList->get(i)->getId() == pParameter->getId())
            {
              pList->remove(i);
              break;
            }
        }
    }

  // create a warning if the delay function is used in the model
  if (this->mDelayFound)
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 36);
    }

  // give a warning that units on pure number as allowed in SBML L3 and above
  // are ignored by COPASI
  if (this->mLevel > 2 && this->mUnitOnNumberFound)
    {
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 93);
    }

  // this->mpCopasiModel->forceCompile(this->mpProcessReport);
  // mpCopasiModel->updateInitialValues(mChangedObjects);

  return this->mpCopasiModel;
}

std::string isKnownCustomFunctionDefinition(const FunctionDefinition* sbmlFunction,
    const std::string& sNamespace,
    const std::string& elementName,
    const std::string& definition)
{
  FunctionDefinition* current = const_cast<FunctionDefinition*>(sbmlFunction);

  if (current == NULL) return "";

  if (!current->isSetAnnotation()) return "";

  const XMLNode* element = current->getAnnotation();

  if (element == NULL) return "";

  for (unsigned int i = 0 ; i < element->getNumChildren(); ++i)
    {
      const XMLNode& annot = element->getChild(i);

      if (annot.getURI() == sNamespace &&
          annot.getName() == elementName &&
          annot.getAttrValue("definition") == definition)
        {
          return current->getId();
        }
    }

  return "";
}

bool addToKnownFunctionToMap(std::map<std::string, std::string>& map, const FunctionDefinition* sbmlFunction)
{
  if (!sbmlFunction->isSetAnnotation())
    return false;

  std::string id = isKnownCustomFunctionDefinition(sbmlFunction,
                   "http://sbml.org/annotations/symbols",
                   "symbols",
                   "http://en.wikipedia.org/wiki/Derivative");

  if (!id.empty())
    {
      map[id] = "RATE";
      return true;
    }

  id = isKnownCustomFunctionDefinition(sbmlFunction,
                                       "http://sbml.org/annotations/distribution",
                                       "distribution",
                                       "http://www.uncertml.org/distributions/normal");

  if (!id.empty())
    {
      map[id] = "RNORMAL";
      return true;
    }

  id = isKnownCustomFunctionDefinition(sbmlFunction,
                                       "http://sbml.org/annotations/distribution",
                                       "distribution",
                                       "http://www.uncertml.org/distributions/uniform");

  if (!id.empty())
    {
      map[id] = "RUNIFORM";
      return true;
    }

  id = isKnownCustomFunctionDefinition(sbmlFunction,
                                       "http://sbml.org/annotations/distribution",
                                       "distribution",
                                       "http://www.uncertml.org/distributions/gamma");

  if (!id.empty())
    {
      map[id] = "RGAMMA";
      return true;
    }

  id = isKnownCustomFunctionDefinition(sbmlFunction,
                                       "http://sbml.org/annotations/distribution",
                                       "distribution",
                                       "http://www.uncertml.org/distributions/poisson");

  if (!id.empty())
    {
      map[id] = "RPOISSON";
      return true;
    }

  return false;
}

bool hasCopasiAnnotation(const SBase* sbmlObject, const std::string & sNamespace)
{
  if (sbmlObject == NULL)
    return false;

  if (!sbmlObject->isSetAnnotation())
    return false;

  const XMLNode * element = sbmlObject->getAnnotation();

  if (element == NULL)
    return false;

  for (unsigned int i = 0; i < element->getNumChildren(); ++i)
    {
      const XMLNode & annot = element->getChild(i);

      if (annot.getURI() == sNamespace)
        {
          return true;
        }
    }

  return false;
}

int
AstStrCmp(const void *s1, const void *s2)
{
  const char* a = static_cast<const ASTNode *>(s1)->getName();
  const char* b = static_cast<const ASTNode *>(s2)->getName();

  if (a == NULL && b == NULL) return  0;

  if (a == NULL && b != NULL) return -1;

  if (a != NULL && b == NULL) return  1;

  return strcmp(
           a,
           b);
}

/**
 * This function checks the function definition for unused arguments (that would not
 * be properly displayed in the CopasiUI). If found, the function body will be replaced
 * with one including all arguments.
 */
void ensureAllArgsAreBeingUsedInFunctionDefinition(const FunctionDefinition* sbmlFunction)
{
  if (sbmlFunction == NULL || sbmlFunction->getNumArguments() == 0 || sbmlFunction->getBody() == NULL) return;

  // get all variables
  List *variables = sbmlFunction->getBody()->getListOfNodes(ASTNode_isName);

  // find unused ones
  std::vector<std::string> unused;

  for (unsigned int i = 0; i < sbmlFunction->getNumArguments(); ++i)
    {
      const ASTNode *arg = sbmlFunction->getArgument(i);

      if (variables->find(arg, AstStrCmp) == NULL)
        {
          if (arg->getName() != NULL)
            unused.push_back(arg->getName());
        }
    }

  // get rid of the list
  delete variables;

  // let us hope this is empty
  if (unused.empty())
    return;

  // it is not, so modify the function definition to include all of them
  std::stringstream str;
  str << "lambda(";

  for (unsigned int i = 0; i < sbmlFunction->getNumArguments(); ++i)
    str << sbmlFunction->getArgument(i)->getName() << ", ";

  char* formula = SBML_formulaToL3String(sbmlFunction->getBody());
  str << formula;

  std::vector<std::string>::iterator it;

  for (it = unused.begin(); it != unused.end(); ++it)
    str << " + 0*" << *it;

  str << ")";

  // update the function definition
  const_cast<FunctionDefinition*>(sbmlFunction)->setMath(SBML_parseL3Formula(str.str().c_str()));

  // free the formula
  free(formula);
}

CFunction* SBMLImporter::createCFunctionFromFunctionDefinition(const FunctionDefinition* sbmlFunction, Model* pSBMLModel, std::map<const CDataObject*, SBase*>& copasi2sbmlmap)
{

  ensureAllArgsAreBeingUsedInFunctionDefinition(sbmlFunction);

  addToKnownFunctionToMap(mKnownCustomUserDefinedFunctions, sbmlFunction);

  CFunction* pTmpFunction = this->createCFunctionFromFunctionTree(sbmlFunction, pSBMLModel, copasi2sbmlmap);

  if (pTmpFunction == NULL)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 14, sbmlFunction->getId().c_str());
      return NULL;
    }

  std::string sbmlId = sbmlFunction->getId();
  pTmpFunction->setSBMLId(sbmlId);
  // check if the id is already taken by another function definition, maybe
  // from an earlier import, if this is the case, delete the id on the old
  // function definition
  // if we don't do this, two functions might have the same SBML id during
  // export which makes the exporter code so much more difficult
  size_t i, iMax = CRootContainer::getFunctionList()->loadedFunctions().size();

  for (i = 0; i < iMax; ++i)
    {
      CFunction* pFun = &CRootContainer::getFunctionList()->loadedFunctions()[i];

      if (pFun->getSBMLId() == sbmlId)
        {
          pFun->setSBMLId("");
        }
    }

  std::string functionName = sbmlFunction->getName();

  if (isEmptyOrWhiteSpace(functionName))
    {
      functionName = sbmlFunction->getId();
    }

  unsigned int counter = 1;
  std::ostringstream numberStream;
  std::string appendix;
  CFunction * pExistingFunction = NULL;

  while ((pExistingFunction = CRootContainer::getFunctionList()->findFunction(functionName + appendix)))
    {
      if (areEqualFunctions(pExistingFunction, pTmpFunction))
        {
          pdelete(pTmpFunction);
          pTmpFunction = pExistingFunction;

          break;
        }

      // We need to check whether the functions are identical.
      numberStream.str("");
      numberStream << "_" << counter;
      counter++;
      appendix = numberStream.str();
    }

  if (pTmpFunction != pExistingFunction)
    {
      pTmpFunction->setObjectName(functionName + appendix);
      CRootContainer::getFunctionList()->add(pTmpFunction, true);
      mCreatedFunctions.insert(pTmpFunction->getObjectName());
    }

  if (pTmpFunction->getType() == CEvaluationTree::UserDefined)
    {
      SBMLImporter::importMIRIAM(sbmlFunction, pTmpFunction);
      SBMLImporter::importNotes(pTmpFunction, sbmlFunction);
    }

  return pTmpFunction;
}

CFunction* SBMLImporter::createCFunctionFromFunctionTree(const FunctionDefinition* pSBMLFunction, Model* pSBMLModel, std::map<const CDataObject*, SBase*>& copasi2sbmlmap)
{
  CFunction* pFun = NULL;

  if (!pSBMLFunction->isSetMath())
    return NULL;

  ConverterASTNode root(*pSBMLFunction->getMath());

  if (SBMLImporter::isDelayOrRateFunctionUsed(&root))
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 85, pSBMLFunction->getId().c_str());
    }

  this->preprocessNode(&root, pSBMLModel, copasi2sbmlmap);

  if (root.getType() != AST_LAMBDA)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 11, pSBMLFunction->getId().c_str());
      return NULL;
    }

  // get the number of children.
  // the first n-1 children are the parameters for the function
  // the last child is the actual function
  pFun = new CKinFunction();
  unsigned int i, iMax = root.getNumChildren() - 1;
  std::set<std::string> variableNames;

  for (i = 0; i < iMax; ++i)
    {
      ASTNode* pVarNode = root.getChild(i);

      if (pVarNode->getType() != AST_NAME)
        {
          // while this is wrong, there is no reason to reject the model, we will catch it later
          std::string functionname = isEmptyOrWhiteSpace(pSBMLFunction->getName()) ?
                                     pSBMLFunction->getId() : pSBMLFunction->getName();
          CCopasiMessage::Type type = pVarNode->getName() != NULL ? CCopasiMessage::ERROR :
                                      CCopasiMessage::EXCEPTION;

          if (type == CCopasiMessage::EXCEPTION)
            delete pFun;

          CCopasiMessage(type, MCSBML + 12, functionname.c_str());
        }

      pFun->addVariable(pVarNode->getName());
      variableNames.insert(pVarNode->getName());
    }

  // now we check if the AST tree has a node that represents the time
  // object
  // find a unique name for the time variable
  std::ostringstream sstream;
  std::string timeVariableName = "time";
  unsigned int postfix = 1;

  while (variableNames.find(timeVariableName) != variableNames.end())
    {
      sstream.str("");
      sstream << "time_" << postfix;
      timeVariableName = sstream.str();
      ++postfix;
    }

  if (this->replaceTimeNodesInFunctionDefinition(root.getChild(iMax), timeVariableName))
    {
      // add another variable to the function
      ASTNode* pVarNode = new ASTNode(AST_NAME);
      pVarNode->setName(timeVariableName.c_str());
      ASTNode* pTmpNode = root.removeChild(iMax);
      root.addChild(pVarNode);
      root.addChild(pTmpNode);
      // increase iMax since we now have one more child
      ++iMax;
      pFun->addVariable(timeVariableName);
      this->mExplicitelyTimeDependentFunctionDefinitions.insert(pSBMLFunction->getId());
    }

  pFun->setTree(*root.getChild(iMax), true);

  if (!pFun->compile())
    {
      delete pFun;
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 28, pSBMLFunction->getId().c_str());
    }

  if (pFun->getRoot() == NULL)
    {
      delete pFun;
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 13, pSBMLFunction->getId().c_str());
    }

  return pFun;
}

CFunction* getFunctionForKey(CDataVectorN<CFunction> &functionDb, const std::string& key)
{
  CFunction* pFunc = NULL;
  CDataVectorN<CFunction>::iterator it = functionDb.begin(), endit = functionDb.end();

  while (it != endit)
    {
      if (it->getKey() == key)
        {
          pFunc = it;
          break;
        }

      ++it;
    }

  return pFunc;
}

/**
 * Creates and returns a COPASI CCompartment from the SBML Compartment
 * given as argument.
 */
CCompartment*
SBMLImporter::createCCompartmentFromCompartment(const Compartment* sbmlCompartment,
    CModel* copasiModel,
    std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
    const Model* /*pSBMLModel*/)
{
  if (sbmlCompartment->isSetUnits())
    {
      std::string cU = sbmlCompartment->getUnits();
    }

  unsigned int dimensionality = 3;

  if (sbmlCompartment->isSetSpatialDimensions())
    {
      dimensionality = sbmlCompartment->getSpatialDimensions();

      // starting with SBML Level 3, the spatial dimensions of a compartment can be
      // any rational number
      double dDimensionality = sbmlCompartment->getSpatialDimensions();

      if (this->mLevel > 2)
        {
          dDimensionality = sbmlCompartment->getSpatialDimensionsAsDouble();
        }

      // check if the unsigned int dimensionality corresponds to the double
      // dimensionality, otherwise give an error message
      // Actually if we wanted to be correct, we would have to check if the
      // part before the komma also matches and maybe have a separate error message if not
      dDimensionality -= dimensionality;

      if (fabs(dDimensionality) > 1e-9)
        {
          CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 89, sbmlCompartment->getId().c_str());
          dimensionality = 3;
        }
    }
  else
    {
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 90, sbmlCompartment->getId().c_str());
      dimensionality = 3;
    }

  if (dimensionality > 3)
    {
      CCopasiMessage Message(CCopasiMessage::WARNING,
                             "The compartment with id \"%s\" has dimensions of %d, this is not supported by COPASI. COPASI will assume that the compartment is three dimensional."
                             , sbmlCompartment->getId().c_str(), dimensionality);
      dimensionality = 3;
      //fatalError();
    }

  std::string name = sbmlCompartment->getName();

  if (isEmptyOrWhiteSpace(name))
    {
      name = sbmlCompartment->getId();
    }

  std::string appendix;
  unsigned int counter = 2;
  std::ostringstream numberStream;

  while (copasiModel->getCompartments().getIndex(name + appendix) != C_INVALID_INDEX)
    {
      numberStream.str("");
      numberStream << "_" << counter;
      counter++;
      appendix = numberStream.str();
    }

  CCompartment* copasiCompartment = copasiModel->createCompartment(name + appendix, std::numeric_limits< C_FLOAT64 >::quiet_NaN());

  if (this->mLevel == 1)
    {
      copasiCompartment->setSBMLId(sbmlCompartment->getName());
    }
  else
    {
      copasiCompartment->setSBMLId(sbmlCompartment->getId());
    }

  // set the dimension of the compartment
  copasiCompartment->setDimensionality(dimensionality);

  //DebugFile << "Created Compartment: " << copasiCompartment->getObjectName() << std::endl;
  SBMLImporter::importMIRIAM(sbmlCompartment, copasiCompartment);
  SBMLImporter::importNotes(copasiCompartment, sbmlCompartment);
  copasi2sbmlmap[copasiCompartment] = const_cast<Compartment*>(sbmlCompartment);
  return copasiCompartment;
}

/**
 * Creates and returns a Copasi CMetab from the given SBML Species object.
 */
CMetab*
SBMLImporter::createCMetabFromSpecies(const Species* sbmlSpecies, CModel* copasiModel, CCompartment* copasiCompartment, std::map<const CDataObject*, SBase*>& copasi2sbmlmap, const Model* /*pSBMLModel*/)
{
  if (sbmlSpecies->isSetSubstanceUnits())
    {
      std::string cU = sbmlSpecies->getSubstanceUnits();
    }

  std::map<const CDataObject*, SBase*>::iterator it = copasi2sbmlmap.find(copasiCompartment);

  if (it == copasi2sbmlmap.end())
    {
      fatalError();
    }

  Compartment* pSBMLCompartment = static_cast<Compartment*>(it->second);

  if (sbmlSpecies->getHasOnlySubstanceUnits() == true)
    {
      this->mSubstanceOnlySpecies.insert(std::make_pair(const_cast<Species*>(sbmlSpecies), pSBMLCompartment));
    }

  std::string name = sbmlSpecies->getName();

  if (isEmptyOrWhiteSpace(name))
    {
      name = sbmlSpecies->getId();
    }

  std::string appendix;
  unsigned int counter = 2;
  std::ostringstream numberStream;

  while (copasiCompartment->getMetabolites().getIndex(name + appendix) != C_INVALID_INDEX)
    {
      numberStream.str("");
      numberStream << "_" << counter;
      counter++;
      appendix = numberStream.str();
    }

  CMetab* copasiMetabolite = copasiModel->createMetabolite(name + appendix, copasiCompartment->getObjectName());

  if (copasiMetabolite == NULL)
    {
      //DebugFile << "Could not create Copasi species." << std::endl;
      fatalError();
    }

  if (sbmlSpecies->getConstant() || sbmlSpecies->getBoundaryCondition())
    {
      copasiMetabolite->setStatus(CModelEntity::Status::FIXED);
    }
  else
    {
      copasiMetabolite->setStatus(CModelEntity::Status::REACTIONS);
    }

  // also check if the compartment has a spatialSize of 0 because this also implies hasOnlySubstanceUnits for the species in this compartment
  // In Level 3 files this no longer seems to be the case however, so we only
  // do this for L1 and L2 files
  if (pSBMLCompartment->isSetSpatialDimensions() && pSBMLCompartment->getSpatialDimensions() == 0 && this->mLevel < 3)
    {
      this->mSubstanceOnlySpecies.insert(std::make_pair(const_cast<Species*>(sbmlSpecies), pSBMLCompartment));
    }

  //DebugFile << "Created species: " << copasiMetabolite->getObjectName() << std::endl;
  copasi2sbmlmap[copasiMetabolite] = const_cast<Species*>(sbmlSpecies);

  if (this->mLevel == 1)
    {
      copasiMetabolite->setSBMLId(sbmlSpecies->getName());
    }
  else
    {
      copasiMetabolite->setSBMLId(sbmlSpecies->getId());
    }

  SBMLImporter::importMIRIAM(sbmlSpecies, copasiMetabolite);
  SBMLImporter::importNotes(copasiMetabolite, sbmlSpecies);
  return copasiMetabolite;
}

CFunction* findFunction(CDataVectorN < CFunction > &  db, const CFunction* func)
{
  size_t i, iMax = db.size();

  for (i = 0; i < iMax; ++i)
    {
      CFunction* pFun = &db[i];

      if (*pFun == *func)
        return pFun;
    }

  return NULL;
}

/**
 * This function replaces any local parameters of the
 * kinetic law that references another reaction with
 * an altered name.
 *
 * @param kLaw the kinetic law
 * @param pSBMLModel the model to search for conflicting reactions
 * @param prefix the prefix to use when modifying the id.
 */
void renameShadowingFluxReferences(KineticLaw* kLaw,
                                   Model* pSBMLModel,
                                   const std::string& prefix)
{
  if (!kLaw->isSetMath()) return;

  ASTNode* pMath = const_cast<ASTNode*>(kLaw->getMath());

  std::set<std::string> toBeRenamed;
  std::set<std::string> viableIds;

  for (int i = 0; i < (int)kLaw->getNumParameters(); ++i)
    {
      Parameter* current = kLaw->getParameter(i);

      if (current == NULL || !current->isSetId())
        continue;

      std::string currentId = current->getId();
      viableIds.insert(currentId);

      Reaction* other = pSBMLModel->getReaction(currentId);

      if (other == NULL)
        continue;

      toBeRenamed.insert(currentId);
    }

  if (!toBeRenamed.empty())
    {
      std::set<std::string>::iterator it = toBeRenamed.begin();

      while (it != toBeRenamed.end())
        {
          std::string newId = prefix
                              + std::string("_")
                              + *it;
          pMath->renameSIdRefs(*it, newId);

          Parameter* parameter = kLaw->getParameter(*it);

          if (parameter != NULL)
            parameter->setId(newId);
          else
            {
              parameter = kLaw->getLocalParameter(*it);

              if (parameter != NULL)
                parameter->setId(newId);
            }

          ++it;
        }
    }
}

/**
 * Creates and returns a COPASI CReaction object from the given SBML
 * Reaction object.
 */
CReaction*
SBMLImporter::createCReactionFromReaction(Reaction* sbmlReaction, Model* pSBMLModel, CModel* copasiModel, std::map<const CDataObject*, SBase*>& copasi2sbmlmap)
{
  if (sbmlReaction == NULL)
    {
      fatalError();
    }

  std::string name = sbmlReaction->getName();

  if (isEmptyOrWhiteSpace(name))
    {
      name = sbmlReaction->getId();
    }

  /* Check if the name of the reaction is unique. */
  std::string appendix;
  unsigned int counter = 2;
  std::ostringstream numberStream;

  while (copasiModel->getReactions().getIndex(name + appendix) != C_INVALID_INDEX)
    {
      numberStream.str("");
      numberStream << "_" << counter;
      counter++;
      appendix = numberStream.str();
    }

  /* create a new reaction with the unique name */
  CReaction* copasiReaction = copasiModel->createReaction(name + appendix);

  if (copasiReaction == NULL)
    {
      fatalError();
    }

  copasiReaction->setReversible(sbmlReaction->getReversible());

  if (this->mLevel == 1)
    {
      copasiReaction->setSBMLId(sbmlReaction->getName());
    }
  else
    {
      copasiReaction->setSBMLId(sbmlReaction->getId());
    }

  copasi2sbmlmap[copasiReaction] = const_cast<Reaction*>(sbmlReaction);

  if (sbmlReaction->isSetFast() && sbmlReaction->getFast() == true)
    {
      const_cast<Reaction*>(sbmlReaction)->setFast(false);
      this->mFastReactions.insert(sbmlReaction->getId());
    }

  // store if the reaction involves species that need a conversion factor
  bool mConversionFactorNeeded = false;

  /* Add all substrates to the reaction */
  unsigned int num = sbmlReaction->getNumReactants();
  bool singleCompartment = true;
  const CCompartment* compartment = NULL;
  bool hasOnlySubstanceUnitPresent = false;
  bool ignoreMassAction = false;

  for (counter = 0; counter < num; counter++)
    {
      const SpeciesReference* sr = sbmlReaction->getReactant(counter);

      if (sr == NULL)
        {
          delete copasiReaction;
          fatalError();
        }

      C_FLOAT64 stoi = 1.0;

      if (this->mLevel < 3)
        {
          // We may not use Mass Action kinetics if we do not know the actual stoichiometry.
          if (sr->isSetStoichiometryMath())
            {
              ignoreMassAction = true;
            }
          else
            {
              stoi = sr->getStoichiometry() / sr->getDenominator();
            }
        }
      else
        {
          // We may not use Mass Action kinetics if we do not know the actual stoichiometry.
          ignoreMassAction = pSBMLModel->getRule(sr->getId()) != NULL;

          if (sr->isSetStoichiometry())
            {
              stoi = sr->getStoichiometry();

              if (stoi != stoi)
                stoi = 1.0;
            }
        }

      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());

      // check if we have a conversion factor
      if (pos == this->speciesMap.end())
        {
          delete copasiReaction;
          std::stringstream os;
          os << "There exists no species for the specified species reference '" << sr->getSpecies() << "'.";
          CCopasiMessage(CCopasiMessage::EXCEPTION, os.str().c_str());
        }
      else
        {
          // check if there is a conversion factor on the species
          if (this->mpModelConversionFactor != NULL || this->mSpeciesConversionParameterMap.find(pos->second->getSBMLId()) != this->mSpeciesConversionParameterMap.end())
            {
              mConversionFactorNeeded = true;
            }
        }

      std::map<const CDataObject*, SBase*>::const_iterator spos = copasi2sbmlmap.find(pos->second);
      assert(spos != copasi2sbmlmap.end());
      Species* pSBMLSpecies = dynamic_cast<Species*>(spos->second);
      assert(pSBMLSpecies != NULL);
      hasOnlySubstanceUnitPresent = hasOnlySubstanceUnitPresent || (pSBMLSpecies->getHasOnlySubstanceUnits() == true);

      if (compartment == NULL)
        {
          compartment = pos->second->getCompartment();
        }
      else
        {
          if (singleCompartment && compartment != pos->second->getCompartment())
            {
              singleCompartment = false;
            }
        }

      hasOnlySubstanceUnitPresent = hasOnlySubstanceUnitPresent ||
                                    (compartment != NULL && compartment->getDimensionality() == 0);

      copasiReaction->addSubstrate(pos->second->getKey(), stoi);

      // we need to store the id of the species reference if it is set because SBML Level 3 allows
      // references to species references and if we want to support his, we need the id to import
      // expressions that reference a species reference
      if (this->mLevel > 2)
        {
          CDataVector<CChemEqElement>::const_iterator it = copasiReaction->getChemEq().getSubstrates().begin(), endit = copasiReaction->getChemEq().getSubstrates().end();
          const CChemEqElement* pElement = NULL;

          while (it != endit)
            {
              if (it->getMetaboliteKey() == pos->second->getKey())
                {
                  pElement = it;
                  break;
                }

              ++it;
            }

          assert(pElement != NULL);

          if (pElement != NULL)
            {
              copasi2sbmlmap[pElement] = const_cast<SpeciesReference*>(sr);

              this->mChemEqElementSpeciesIdMap[pElement] = std::pair<std::string, CChemEq::MetaboliteRole>(sr->getSpecies(), CChemEq::SUBSTRATE);
            }
        }

      // find the CChemEqElement that belongs to the added substrate
      if (this->mLevel < 3 && sr->isSetStoichiometryMath())
        {
          CChemEq& chemEq = copasiReaction->getChemEq();
          CDataVector < CChemEqElement >::const_iterator it = chemEq.getSubstrates().begin();
          CDataVector < CChemEqElement >::const_iterator end = chemEq.getSubstrates().end();
          const CChemEqElement* pChemEqElement = NULL;

          while (it != end)
            {
              if (it->getMetabolite() == pos->second)
                {
                  pChemEqElement = it;
                  break;
                }

              ++it;
            }

          assert(pChemEqElement != NULL);
          mStoichiometricExpressionMap.insert(std::make_pair(sr->getStoichiometryMath()->getMath(), pChemEqElement));
        }
    }

  /* Add all products to the reaction */
  num = sbmlReaction->getNumProducts();

  for (counter = 0; counter < num; counter++)
    {
      SpeciesReference* sr = sbmlReaction->getProduct(counter);

      if (sr == NULL)
        {
          delete copasiReaction;
          fatalError();
        }

      C_FLOAT64 stoi = 1.0;

      if (this->mLevel < 3)
        {
          if (sr->isSetStoichiometryMath())
            {
              ignoreMassAction = true;
            }
          else
            {
              stoi = sr->getStoichiometry() / sr->getDenominator();
            }
        }
      else
        {
          // We may not use Mass Action kinetics if we do not know the actual stoichiometry.
          ignoreMassAction = pSBMLModel->getRule(sr->getId()) != NULL;

          if (sr->isSetStoichiometry())
            {
              stoi = sr->getStoichiometry();

              if (stoi != stoi)
                stoi = 1.0;
            }
        }

      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());

      if (pos == this->speciesMap.end())
        {
          delete copasiReaction;
          std::stringstream os;
          os << "There exists no species for the specified species reference '" << sr->getSpecies() << "'.";
          CCopasiMessage(CCopasiMessage::EXCEPTION, os.str().c_str());
        }
      else
        {
          // check if there is a conversion factor on the species
          if (this->mpModelConversionFactor != NULL || this->mSpeciesConversionParameterMap.find(pos->second->getSBMLId()) != this->mSpeciesConversionParameterMap.end())
            {
              mConversionFactorNeeded = true;
            }
        }

      std::map<const CDataObject*, SBase*>::const_iterator spos = copasi2sbmlmap.find(pos->second);
      assert(spos != copasi2sbmlmap.end());
      Species* pSBMLSpecies = dynamic_cast<Species*>(spos->second);
      assert(pSBMLSpecies != NULL);
      hasOnlySubstanceUnitPresent = hasOnlySubstanceUnitPresent || (pSBMLSpecies->getHasOnlySubstanceUnits() == true);

      if (compartment == NULL)
        {
          compartment = pos->second->getCompartment();
        }
      else
        {
          if (singleCompartment && compartment != pos->second->getCompartment())
            {
              singleCompartment = false;
            }
        }

      hasOnlySubstanceUnitPresent = hasOnlySubstanceUnitPresent ||
                                    (compartment != NULL && compartment->getDimensionality() == 0);

      copasiReaction->addProduct(pos->second->getKey(), stoi);

      // we need to store the id of the species reference if it is set because SBML Level 3 allows
      // references to species references and if we want to support his, we need the id to import
      // expressions that reference a species reference
      if (this->mLevel > 2)
        {
          CDataVector<CChemEqElement>::const_iterator it = copasiReaction->getChemEq().getProducts().begin(), endit = copasiReaction->getChemEq().getProducts().end();
          const CChemEqElement* pElement = NULL;

          while (it != endit)
            {
              if (it->getMetaboliteKey() == pos->second->getKey())
                {
                  pElement = it;
                  break;
                }

              ++it;
            }

          assert(pElement != NULL);

          if (pElement != NULL)
            {
              copasi2sbmlmap[pElement] = const_cast<SpeciesReference*>(sr);
              this->mChemEqElementSpeciesIdMap[pElement] = std::pair<std::string, CChemEq::MetaboliteRole>(sr->getSpecies(), CChemEq::PRODUCT);
            }
        }

      if (sr->isSetStoichiometryMath())
        {
          CChemEq& chemEq = copasiReaction->getChemEq();
          CDataVector < CChemEqElement >::const_iterator it = chemEq.getProducts().begin();
          CDataVector < CChemEqElement >::const_iterator end = chemEq.getProducts().end();
          const CChemEqElement* pChemEqElement = NULL;

          while (it != end)
            {
              if (it->getMetabolite() == pos->second)
                {
                  pChemEqElement = it;
                  break;
                }

              ++it;
            }

          assert(pChemEqElement != NULL);
          mStoichiometricExpressionMap.insert(std::make_pair(sr->getStoichiometryMath()->getMath(), pChemEqElement));
        }
    }

  /* Add all modifiers to the reaction */
  num = sbmlReaction->getNumModifiers();

  for (counter = 0; counter < num; counter++)
    {
      const ModifierSpeciesReference* sr = sbmlReaction->getModifier(counter);

      if (sr == NULL)
        {
          delete copasiReaction;
          fatalError();
        }

      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());

      if (pos == this->speciesMap.end())
        {
          //delete copasiReaction;
          // modifiers are not as necessary and can be ignored
          std::stringstream os;
          os << "There exists no species for the specified modifier '" << sr->getSpecies() << "'.";
          CCopasiMessage(CCopasiMessage::WARNING, os.str().c_str());

          continue;
        }

      std::map<const CDataObject*, SBase*>::const_iterator spos = copasi2sbmlmap.find(pos->second);
      assert(spos != copasi2sbmlmap.end());
      Species* pSBMLSpecies = dynamic_cast<Species*>(spos->second);
      assert(pSBMLSpecies != NULL);
      hasOnlySubstanceUnitPresent = hasOnlySubstanceUnitPresent || (pSBMLSpecies->getHasOnlySubstanceUnits() == true);
      copasiReaction->addModifier(pos->second->getKey());

      if (compartment == NULL)
        {
          compartment = pos->second->getCompartment();
        }
      else
        {
          if (singleCompartment && compartment != pos->second->getCompartment())
            {
              singleCompartment = false;
            }
        }

      hasOnlySubstanceUnitPresent = hasOnlySubstanceUnitPresent ||
                                    (compartment != NULL && compartment->getDimensionality() == 0);

      // we need to store the id of the species reference if it is set because SBML Level 3 allows
      // references to species references and if we want to support his, we need the id to import
      // expressions that reference a species reference
      if (this->mLevel > 2)
        {

          CDataVector<CChemEqElement>::const_iterator it = copasiReaction->getChemEq().getModifiers().begin(), endit = copasiReaction->getChemEq().getModifiers().end();
          const CChemEqElement* pElement = NULL;

          while (it != endit)
            {
              if (it->getMetaboliteKey() == pos->second->getKey())
                {
                  pElement = it;
                  break;
                }

              ++it;
            }

          assert(pElement != NULL);

          if (pElement != NULL)
            {
              copasi2sbmlmap[pElement] = const_cast<ModifierSpeciesReference*>(sr);
            }
        }
    }

  /* in the newly created CFunction set the types for all parameters and
   * either a mapping or a value
   */
  KineticLaw* kLaw = sbmlReaction->getKineticLaw();

  if (kLaw != NULL)
    {

      // issue 2407: ensure that no reaction ids are shadowed
      // by local parameters
      renameShadowingFluxReferences(kLaw, pSBMLModel,
                                    copasiReaction->getObjectName());

      const ListOfParameters* pParamList = NULL;

      if (this->mLevel > 2)
        {
          pParamList = kLaw->getListOfLocalParameters();
        }
      else
        {
          pParamList = kLaw->getListOfParameters();
        }

      for (counter = 0; counter < pParamList->size(); ++counter)
        {
          const Parameter* pSBMLParameter = pParamList->get(counter);
          std::string id;

          if (this->mLevel == 1)
            {
              id = pSBMLParameter->getName();
            }
          else
            {
              id = pSBMLParameter->getId();
            }

          double value;

          if (pSBMLParameter->isSetValue() && pSBMLParameter->getValue() == pSBMLParameter->getValue()) // make sure it is not set to NaN
            {
              value = pSBMLParameter->getValue();
            }
          else
            {
              // Set value to NaN and create a warning if it is the first time
              // this happened
              value = std::numeric_limits<C_FLOAT64>::quiet_NaN();

              if (!this->mIncompleteModel)
                {
                  this->mIncompleteModel = true;
                  CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 42, pSBMLParameter->getId().c_str());
                }
            }

          copasiReaction->getParameters().addParameter(id, CCopasiParameter::Type::DOUBLE, value);
        }

      ASTNode* kLawMath = const_cast<ASTNode*>(kLaw->getMath());

      if (kLawMath == NULL || kLawMath->getType() == AST_UNKNOWN)
        {
          copasiReaction->setFunction(NULL);
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 56, sbmlReaction->getId().c_str());
        }
      else
        {
          // check for references to species references in the expression because we don't support them yet
          if (!SBMLImporter::findIdInASTTree(kLawMath, this->mSBMLSpeciesReferenceIds).empty())
            {
              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 95);
            }

          std::string reactionId;

          while (!(reactionId = SBMLImporter::findIdInASTTree(kLawMath, mReactions)).empty())
            {
              std::string newParameterId = "rateOf_" + reactionId;

              Parameter* sbmlParameter = pSBMLModel->createParameter();
              sbmlParameter->setId(newParameterId);
              sbmlParameter->setValue(0);

              CModelValue* parameter = this->mpCopasiModel->createModelValue(newParameterId);
              parameter->setSBMLId(newParameterId);
              parameter->setStatus(CModelEntity::Status::ASSIGNMENT);
              parameter->setInitialExpression("0");

              mParameterFluxMap[reactionId] = parameter;

              copasi2sbmlmap[parameter] = sbmlParameter;

              std::map<std::string, std::string> map;
              map[reactionId] = newParameterId;
              replace_name_nodes(kLawMath, map);
            }

          ConverterASTNode* node = new ConverterASTNode(*kLawMath);
          preprocessNode(node, pSBMLModel, copasi2sbmlmap, sbmlReaction, true);

          if (node == NULL)
            {
              delete copasiReaction;
              fatalError();
            }

          /* if it is a single compartment reaction, we have to divide the whole kinetic
          ** equation by the compartment because COPASI expects
          ** kinetic laws that specify concentration/time for single compartment
          ** reactions.
          */
          if (singleCompartment)
            {

              if (compartment != NULL)
                {
                  // check if the division by volume can be done symbolically in the tree.
                  bool wasRemoved = this->divideByVolume(node, compartment->getSBMLId());

                  // if not, we have to do it manually
                  if (!wasRemoved)
                    {
                      ConverterASTNode* tmpNode1 = new ConverterASTNode();
                      tmpNode1->setType(AST_DIVIDE);
                      tmpNode1->addChild(node);
                      ConverterASTNode* tmpNode2 = new ConverterASTNode();
                      tmpNode2->setType(AST_NAME);
                      tmpNode2->setName(compartment->getSBMLId().c_str());
                      tmpNode1->addChild(tmpNode2);
                      node = tmpNode1;
                      std::map<const CDataObject*, SBase*>::const_iterator pos = copasi2sbmlmap.find(compartment);
                      assert(pos != copasi2sbmlmap.end());
                      Compartment* pSBMLCompartment = dynamic_cast<Compartment*>(pos->second);
                      assert(pSBMLCompartment != NULL);

                      if (!hasOnlySubstanceUnitPresent && ((this->mLevel == 1 && pSBMLCompartment->isSetVolume()) || (this->mLevel >= 2 && pSBMLCompartment->isSetSize())) && pSBMLCompartment->getSize() == 1.0)
                        {
                          // we have to check if all species used in the reaction
                          // have the hasOnlySubstance flag set

                          if (node->getChild(0)->getType() == AST_FUNCTION && (!this->containsVolume(node->getChild(0), compartment->getSBMLId())))
                            {
                              // add the id of the reaction to the set so that we can create an error message later.
                              this->mDivisionByCompartmentReactions.insert(sbmlReaction->getId());
                            }
                        }
                    }
                }
              else
                {
                  delete node;
                  delete copasiReaction;
                  fatalError();
                }
            }

          /* Create a new user defined CKinFunction */
          if (!sbmlId2CopasiCN(node, copasi2sbmlmap, copasiReaction->getParameters(), sbmlReaction))
            {
              CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 27, copasiReaction->getObjectName().c_str());
            }

          CEvaluationNode* pExpressionTreeRoot = CEvaluationTree::fromAST(node, false);
          delete node;
          node = NULL;

          if (pExpressionTreeRoot != NULL)
            {
              CExpression KineticLawExpression;
              KineticLawExpression.setRoot(pExpressionTreeRoot);

              // check if the expression is constant flux
              const CDataObject* pParamObject = SBMLImporter::isConstantFlux(pExpressionTreeRoot, copasiModel);

              if (pParamObject != NULL)
                {
                  // assert that the object really is a local or global
                  // parameter
                  assert(dynamic_cast<const CCopasiParameter*>(pParamObject) || dynamic_cast<const CModelValue*>(pParamObject));
                  std::string functionName;

                  if (copasiReaction->isReversible())
                    {
                      // set the function to Constant flux (reversible)
                      functionName = "Constant flux (reversible)";
                    }
                  else
                    {
                      // set the function to Constant flux (irreversible)
                      functionName = "Constant flux (irreversible)";
                    }

                  CFunction* pCFFun = dynamic_cast< CFunction * >(CRootContainer::getFunctionList()->findFunction(functionName));
                  assert(pCFFun != NULL);
                  CEvaluationNodeCall* pCallNode = NULL;

                  if (pExpressionTreeRoot->mainType() == CEvaluationNode::MainType::OBJECT)
                    {
                      pCallNode = new CEvaluationNodeCall(CEvaluationNode::SubType::EXPRESSION, "dummy_call");
                      // add the parameter
                      pCallNode->addChild(pExpressionTreeRoot->copyBranch());
                    }
                  else
                    {
                      pCallNode = dynamic_cast<CEvaluationNodeCall*>(pExpressionTreeRoot->copyBranch());
                      assert(pCallNode != NULL);
                    }

                  if (pParamObject->getObjectType() == "Parameter")
                    {
                      const_cast< CDataObject * >(pParamObject)->setObjectName("v");
                      dynamic_cast<CEvaluationNode*>(pCallNode->getChild())->setData("<" + pParamObject->getStringCN() + ">");
                    }

                  copasiReaction->setFunction(pCFFun);
                  // map the parameter
                  this->doMapping(copasiReaction, pCallNode);
                  delete pCallNode;
                }
              else
                {
                  // check if the root node is a simple function call
                  if (this->isSimpleFunctionCall(pExpressionTreeRoot))
                    {
                      // if yes, we check if it corresponds to an already existing function
                      std::string functionName = pExpressionTreeRoot->getData();
                      CFunction* pImportedFunction = dynamic_cast< CFunction * >(CRootContainer::getFunctionList()->findFunction(functionName));
                      assert(pImportedFunction);
                      std::vector<CEvaluationNodeObject*>* v = NULL;

                      // only check for mass action if there is no conversion factor involved
                      // for any of the species involved in the reaction (substrates and products)
                      if (!mConversionFactorNeeded && !ignoreMassAction)
                        {
                          v = this->isMassAction(pImportedFunction, copasiReaction->getChemEq(), static_cast<const CEvaluationNodeCall*>(pExpressionTreeRoot));

                          if (!v)
                            {
                              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 27, copasiReaction->getObjectName().c_str());
                            }
                        }

                      if (v && !v->empty())
                        {
                          CFunction* pFun = NULL;

                          if (copasiReaction->isReversible())
                            {
                              pFun = static_cast< CFunction * >(CRootContainer::getFunctionList()->findFunction("Mass action (reversible)"));
                            }
                          else
                            {
                              pFun = static_cast< CFunction * >(CRootContainer::getFunctionList()->findFunction("Mass action (irreversible)"));
                            }

                          if (!pFun)
                            {
                              fatalError();
                            }

                          // do the mapping
                          CEvaluationNodeCall* pCallNode = new CEvaluationNodeCall(CEvaluationNode::SubType::EXPRESSION, "dummy_call");
                          size_t i, iMax = v->size();

                          for (i = 0; i < iMax; ++i)
                            {
                              pCallNode->addChild((*v)[i]);
                            }

                          this->renameMassActionParameters(pCallNode);
                          copasiReaction->setFunction(pFun);
                          this->doMapping(copasiReaction, pCallNode);
                          delete pCallNode;
                        }
                      else
                        {
                          // find corresponding reaction does *not* return the function if it is already in the function db
                          // we better change this to return this instance.
                          CFunction* pExistingFunction = findCorrespondingFunction(&KineticLawExpression, copasiReaction);

                          // if it does, we set the existing function for this reaction
                          if (pExistingFunction)
                            {
                              copasiReaction->setFunction(pExistingFunction);
                              // do the mapping
                              doMapping(copasiReaction, dynamic_cast<const CEvaluationNodeCall*>(pExpressionTreeRoot));
                            }
                          // else we take the function from the pTmpFunctionDB, copy it and set the usage correctly
                          else
                            {
                              // replace the variable nodes in pImportedFunction with  nodes from
                              std::map<std::string, std::string > arguments;
                              const CFunctionParameters& funParams = pImportedFunction->getVariables();
                              const CEvaluationNode* pTmpNode = static_cast<const CEvaluationNode*>(pExpressionTreeRoot->getChild());
                              size_t i, iMax = funParams.size();

                              for (i = 0; (i < iMax) && pTmpNode; ++i)
                                {
                                  if (!(pTmpNode->mainType() == CEvaluationNode::MainType::OBJECT)) fatalError();

                                  arguments[funParams[i]->getObjectName()] = pTmpNode->getData().substr(1, pTmpNode->getData().length() - 2);
                                  pTmpNode = static_cast<const CEvaluationNode*>(pTmpNode->getSibling());
                                }

                              assert((i == iMax) && pTmpNode == NULL);

                              CEvaluationNode* pTmpExpression = variables2objects(pImportedFunction->getRoot()->copyBranch(), arguments);

                              CExpression TmpTree2;
                              TmpTree2.setRoot(pTmpExpression);

                              // code to fix bug 1874
                              // since this is a user defined function, we want to retain the original name
                              // next setFunctionFromExpressionTree will take this name if it is not 'Expression'
                              // (the default)
                              TmpTree2.setObjectName(functionName);

                              size_t ExistingFunctions = CRootContainer::getFunctionList()->loadedFunctions().size();
                              CFunction * pNewFunction = copasiReaction->setFunctionFromExpressionTree(TmpTree2, copasi2sbmlmap);

                              if (pNewFunction != NULL &&
                                  pNewFunction->getType() == CEvaluationTree::UserDefined)
                                {
                                  // code to fix Bug 1015
                                  if (!pNewFunction->isSuitable(copasiReaction->getChemEq().getSubstrates().size(),
                                                                copasiReaction->getChemEq().getProducts().size(),
                                                                copasiReaction->isReversible() ? TriTrue : TriFalse))
                                    {
                                      pNewFunction->setReversible(TriUnspecified);
                                    }

                                  if (CRootContainer::getFunctionList()->loadedFunctions().size() < ExistingFunctions)
                                    mCreatedFunctions.insert(pNewFunction->getObjectName());
                                }
                            }
                        }

                      pdelete(v);
                    }
                  else
                    {
                      std::vector<CEvaluationNodeObject*>* v = NULL;

                      // only check for mass action if there is no conversion factor involved
                      // for any of the species involved in the reaction (substrates and products)
                      if (!mConversionFactorNeeded && !ignoreMassAction)
                        {
                          v = this->isMassAction(&KineticLawExpression, copasiReaction->getChemEq());

                          if (!v)
                            {
                              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 27, copasiReaction->getObjectName().c_str());
                            }
                        }

                      if (v && !v->empty())
                        {
                          CFunction* pFun = NULL;

                          if (copasiReaction->isReversible())
                            {
                              pFun = static_cast<CFunction*>(CRootContainer::getFunctionList()->findFunction("Mass action (reversible)"));
                            }
                          else
                            {
                              pFun = static_cast<CFunction*>(CRootContainer::getFunctionList()->findFunction("Mass action (irreversible)"));
                            }

                          if (!pFun)
                            {
                              fatalError();
                            }

                          // do the mapping
                          CEvaluationNodeCall* pCallNode = new CEvaluationNodeCall(CEvaluationNode::SubType::EXPRESSION, "dummy_call");
                          size_t i, iMax = v->size();

                          for (i = 0; i < iMax; ++i)
                            {
                              pCallNode->addChild((*v)[i]);
                            }

                          // rename the function parameters to k1 and k2
                          this->renameMassActionParameters(pCallNode);
                          copasiReaction->setFunction(pFun);
                          this->doMapping(copasiReaction, pCallNode);
                          delete pCallNode;
                        }
                      else
                        {
                          size_t ExistingFunctions = CRootContainer::getFunctionList()->loadedFunctions().size();
                          CFunction* pNonconstFun = copasiReaction->setFunctionFromExpressionTree(KineticLawExpression, copasi2sbmlmap);

                          if (pNonconstFun != NULL &&
                              pNonconstFun->getType() == CEvaluationTree::UserDefined)
                            {
                              // code to fix Bug 1015
                              if (!pNonconstFun->isSuitable(copasiReaction->getChemEq().getSubstrates().size(),
                                                            copasiReaction->getChemEq().getProducts().size(),
                                                            copasiReaction->isReversible() ? TriTrue : TriFalse))
                                {
                                  pNonconstFun->setReversible(TriUnspecified);

                                  if (pNonconstFun->getInfix() == "@")
                                    {
                                      // set infix to something more usable which even though 
                                      // invalid, may help others to fix this
                                      pNonconstFun->setInfix(SBML_formulaToL3String(kLawMath));
                                    }
                                }

                              if (CRootContainer::getFunctionList()->loadedFunctions().size() > ExistingFunctions)
                                mCreatedFunctions.insert(pNonconstFun->getObjectName());
                            }
                        }

                      pdelete(v);
                    }
                }
            }
          else
            {
              // error message
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 8, copasiReaction->getObjectName().c_str());
            }
        }
    }
  else
    {
      /* if no KineticLaw was defined for the reaction. */
      copasiReaction->setFunction(NULL);
    }

  //DebugFile << "Created reaction: " << copasiReaction->getObjectName() << std::endl;
  SBMLImporter::importMIRIAM(sbmlReaction, copasiReaction);
  SBMLImporter::importNotes(copasiReaction, sbmlReaction);

  return copasiReaction;
}

/**
 * Creates a map of each parameter of the function definition and its
 * corresponding parameter in the function call.
 */
std::map<std::string, ASTNode*>
SBMLImporter::createBVarMap(const ASTNode* uDefFunction, const ASTNode* function)
{
  /* the first n-1 children, where n is the number of children, of a function definition ASTnode are the
   * arguments to the function. These correspond to the m=n-1 children of the
   * function call.
   */
  if (uDefFunction->getNumChildren() != function->getNumChildren() + 1)
    {
      std::string functionName = uDefFunction->getName();
      fatalError();
    }

  std::map<std::string, ASTNode*> varMap;
  unsigned int counter;

  for (counter = 0; counter < uDefFunction->getNumChildren() - 1; counter++)
    {
      varMap[uDefFunction->getChild(counter)->getName()] = function->getChild(counter);
    }

  return varMap;
}

/**
 * Returns the user defined SBML function definition that belongs to the given
 * name, or NULL if none can be found.
 */
const FunctionDefinition*
SBMLImporter::getFunctionDefinitionForName(const std::string& name, const Model* sbmlModel)
{
  const FunctionDefinition* fDef = NULL;
  unsigned int counter;

  for (counter = 0; counter < sbmlModel->getNumFunctionDefinitions(); counter++)
    {
      std::string functionName = sbmlModel->getFunctionDefinition(counter)->getName();

      if (sbmlModel->getFunctionDefinition(counter)->isSetId())
        {
          functionName = sbmlModel->getFunctionDefinition(counter)->getId();
        }

      if (functionName == name)
        {
          fDef = sbmlModel->getFunctionDefinition(counter);
          break;
        }
    }

  return fDef;
}

#ifdef XXXX
/**
 * Replaces the variables in a function definition with the actual function
 * parameters that were used when the function was called. The function returns
 * a pointer to the ConverterAST node with the replaced variables.
 */
ConverterASTNode*
SBMLImporter::replaceBvars(const ASTNode* node, std::map<std::string, ASTNode*> bvarMap)
{
  ConverterASTNode* newNode = NULL;

  if (node->isName())
    {
      /* check if name matches any in bvarMap */
      /* if yes, replace node with node in bvarMap */
      /* node needs to be set to be a deep copy of the replacement */
      if (bvarMap.find(node->getName()) != bvarMap.end())
        {
          newNode = new ConverterASTNode(*bvarMap[node->getName()]);
        }
    }
  else
    {
      newNode = new ConverterASTNode(*node);
      newNode->setChildren(new List());
      unsigned int counter;

      for (counter = 0; counter < node->getNumChildren(); counter++)
        {
          newNode->addChild(this->replaceBvars(node->getChild(counter), bvarMap));
        }
    }

  return newNode;
}
#endif // XXXX

/**
 * Constructor that initializes speciesMap and the FunctionDB object
 */
SBMLImporter::SBMLImporter()
  : SBMLUnitSupport()
  , mIgnoredSBMLMessages()
  , speciesMap()
  , mIncompleteModel(false)
  , mUnsupportedRuleFound(false)
  , mUnsupportedRateRuleFound(false)
  , mUnsupportedAssignmentRuleFound(false)
  , mUnitOnNumberFound(false)
  , mAssignmentToSpeciesReferenceFound(false)
  , mOriginalLevel(0)
  , sbmlIdMap()
  , mCreatedFunctions()
  , mpDataModel(NULL)
  , mpCopasiModel(NULL)
  , mFunctionNameMapping()
  , mDivisionByCompartmentReactions()
  , mpProcessReport(NULL)
  , mGlobalStepHandle(C_INVALID_INDEX)
  , mGlobalStepCounter(0)
  , mGlobalStepTotal(0)
  , mCurrentStepHandle(C_INVALID_INDEX)
  , mCurrentStepCounter(0)
  , mCurrentStepTotal(0)
  , mSubstanceOnlySpecies()
  , mFastReactions()
  , mReactions()
  , mReactionsWithReplacedLocalParameters()
  , mExplicitelyTimeDependentFunctionDefinitions()
  , mIgnoredParameterUnits()
  , mStoichiometricExpressionMap()
  , mDelayFound(false)
  , mPotentialAvogadroNumbers()
  , mAvogadroCreated(false)
  , mImportCOPASIMIRIAM(true)
  , mDelayNodeMap()
  , mReplacedRates()
  , mUsedSBMLIds()
  , mUsedSBMLIdsPopulated(false)
  , mKnownCustomUserDefinedFunctions()
  , mpModelConversionFactor(NULL)
  , mChemEqElementSpeciesIdMap()
  , mSpeciesConversionParameterMap()
  , mSBMLIdModelValueMap()
  , mSBMLSpeciesReferenceIds()
  , mRateRuleForSpeciesReferenceIgnored(false)
  , mEventAssignmentForSpeciesReferenceIgnored(false)
  , mConversionFactorFound(false)
  , mCompartmentMap()
  , mParameterFluxMap()
  , mChangedObjects()
  , mpSbmlCallback(NULL)
{
  this->speciesMap = std::map<std::string, CMetab*>();
  this->mIncompleteModel = false;
  this->mUnsupportedRuleFound = false;
  this->mUnsupportedRateRuleFound = false;
  this->mUnsupportedAssignmentRuleFound = false;
  this->mUnitOnNumberFound = false;
  this->mAssignmentToSpeciesReferenceFound = false;
  this->mpProcessReport = NULL;
  this->mDelayFound = false;
  this->mAvogadroCreated = false;
  // these data structures are used to handle the new conversion factores in
  // SBML L3 models and references to species references
  this->mpModelConversionFactor = NULL;
  this->mChemEqElementSpeciesIdMap.clear();
  this->mSpeciesConversionParameterMap.clear();
  this->mSBMLIdModelValueMap.clear();
  this->mRateRuleForSpeciesReferenceIgnored = false;
  this->mEventAssignmentForSpeciesReferenceIgnored = false;
  this->mConversionFactorFound = false;

  this->mIgnoredSBMLMessages.insert(10501);
  this->mIgnoredSBMLMessages.insert(10512);
  this->mIgnoredSBMLMessages.insert(10513);
  this->mIgnoredSBMLMessages.insert(10522);
  this->mIgnoredSBMLMessages.insert(10533);
  this->mIgnoredSBMLMessages.insert(10541);
  this->mIgnoredSBMLMessages.insert(10551);
  this->mIgnoredSBMLMessages.insert(10562);
  this->mIgnoredSBMLMessages.insert(80701);
  this->mIgnoredSBMLMessages.insert(99505);
}

/**
 * Destructor that does nothing.
 */
SBMLImporter::~SBMLImporter()
{
  if (mpSbmlCallback != NULL)
    {
#if LIBSBML_VERSION >= 51801
      CallbackRegistry::removeCallback(mpSbmlCallback);
      pdelete(mpSbmlCallback);
#endif
    }
}

/**
 * This functions replaces all species nodes for species that are in the substanceOnlySpeciesVector.
 * With the node multiplied by the volume of the species compartment.
void SBMLImporter::replaceSubstanceOnlySpeciesNodes(ConverterASTNode* node, const std::map<Species*, Compartment*>& substanceOnlySpecies)
{
  if (node != NULL)
    {
      if (node->getType() == AST_NAME)
        {
          std::map<Species*, Compartment*>::const_iterator it = substanceOnlySpecies.begin();
          std::map<Species*, Compartment*>::const_iterator endIt = substanceOnlySpecies.end();
          while (it != endIt)
            {
              if (it->first->getId() == node->getName())
                {
                  // replace node
                  List* l = new List();
                  ConverterASTNode* child1 = new ConverterASTNode(AST_NAME);
                  child1->setName(node->getName());
                  ConverterASTNode* child2 = new ConverterASTNode(AST_NAME);
                  child2->setName(it->second->getId().c_str());
                  l->add(child1);
                  l->add(child2);
                  node->setChildren(l);
                  node->setType(AST_TIMES);
                  break;
                }
              ++it;
            }
        }
      else
        {
          unsigned int counter;
          for (counter = 0;counter < node->getNumChildren();counter++)
            {
              this->replaceSubstanceOnlySpeciesNodes((ConverterASTNode*)node->getChild(counter), substanceOnlySpecies);
            }
        }
    }
}
 */

/**
 * Function reads an SBML file with libsbml and converts it to a Copasi CModel
 */
CModel* SBMLImporter::readSBML(std::string filename,
                               SBMLDocument*& pSBMLDocument,
                               std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
                               CListOfLayouts *& prLol,
                               CDataModel* pDataModel)
{
  // convert filename to the locale encoding
  std::ifstream file(CLocaleString::fromUtf8(filename).c_str());

  if (!file)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 50, filename.c_str());
    }

  std::ostringstream stringStream;

  // check for BOM
  char a, b, c;
  a = file.get();
  b = file.get();
  c = file.get();

  if (a != (char)0xEF || b != (char)0xBB || c != (char)0xBF)
    {
      file.seekg(0); // if BOM not found reset stream
    }

  while (file.get(c))
    {
      stringStream << c;
    }

  file.clear();
  file.close();
  return this->parseSBML(stringStream.str(), pSBMLDocument, copasi2sbmlmap, prLol, pDataModel);
}

bool SBMLImporter::checkValidityOfSourceDocument(SBMLDocument* sbmlDoc)
{
  if (CRootContainer::getConfiguration()->validateUnits())
    sbmlDoc->setApplicableValidators(AllChecksON & SBOCheckOFF);
  else
    sbmlDoc->setApplicableValidators(AllChecksON & UnitsCheckOFF & SBOCheckOFF);

  // libSBML is validating comp models after 5.8.0 this would throw an
  // error in case external references can't be resolved.
  sbmlDoc->setLocationURI(mpDataModel->getReferenceDirectory());

  unsigned int checkResult = sbmlDoc->getNumErrors(LIBSBML_SEV_ERROR);

  try
    {
      checkResult += sbmlDoc->checkConsistency();
    }
  catch (...)
    {
    }

  sbmlDoc->setLocationURI(mpDataModel->getReferenceDirectory());

  // the new libsbml includes complete layout validation, and flags many
  // things as errors, that would cause COPASI to reject the model (even
  // though the layout code has been written to anticipate all these possible
  // error sources). Thus downgrade these error messages
  sbmlDoc->getErrorLog()->changeErrorSeverity(LIBSBML_SEV_ERROR, LIBSBML_SEV_WARNING, "layout");

  if (checkResult != 0)
    {
      int fatal = -1;
      unsigned int i, iMax = sbmlDoc->getNumErrors();

      for (i = 0; (i < iMax) && (fatal == -1); ++i)
        {
          const XMLError* pSBMLError = sbmlDoc->getError(i);

          // we check if the model contained a required package
          if (sbmlDoc->getLevel() > 2 && pSBMLError->getErrorId() == 99107)
            {
              std::stringstream str;
              str << sbmlDoc->getUnknownPackagePrefix(0);

              for (int k = 1; k < sbmlDoc->getNumUnknownPackages(); ++k)
                str << ", " << sbmlDoc->getUnknownPackagePrefix(k);

              CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 96, str.str().c_str());
            }

          // we check for unsupported SBML version
          if (pSBMLError->getErrorId() == 99101)
            {
              CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 102, sbmlDoc->getLevel(), sbmlDoc->getVersion());
            }

          CCopasiMessage::Type messageType = CCopasiMessage::RAW;

          switch (pSBMLError->getSeverity())
            {
              case LIBSBML_SEV_INFO:

                if (mIgnoredSBMLMessages.find(pSBMLError->getErrorId()) != mIgnoredSBMLMessages.end())
                  {
                    messageType = CCopasiMessage::WARNING_FILTERED;
                  }
                else
                  {
                    messageType = CCopasiMessage::WARNING;
                  }

                CCopasiMessage(messageType, MCSBML + 40, "INFO", pSBMLError->getErrorId(), pSBMLError->getLine(), pSBMLError->getColumn(), pSBMLError->getMessage().c_str());
                break;

              case LIBSBML_SEV_WARNING:

                // filter layout warnings always
                if (pSBMLError->getPackage() == "layout")
                  messageType = CCopasiMessage::WARNING_FILTERED;
                else if (mIgnoredSBMLMessages.find(pSBMLError->getErrorId()) != mIgnoredSBMLMessages.end())
                  {
                    messageType = CCopasiMessage::WARNING_FILTERED;
                  }
                else
                  {
                    messageType = CCopasiMessage::WARNING;
                  }

                CCopasiMessage(messageType, MCSBML + 40, "WARNING", pSBMLError->getErrorId(), pSBMLError->getLine(), pSBMLError->getColumn(), pSBMLError->getMessage().c_str());
                break;

              case LIBSBML_SEV_ERROR:

                if (mIgnoredSBMLMessages.find(pSBMLError->getErrorId()) != mIgnoredSBMLMessages.end())
                  {
                    messageType = CCopasiMessage::ERROR_FILTERED;
                  }

                CCopasiMessage(messageType, MCSBML + 40, "ERROR", pSBMLError->getErrorId(), pSBMLError->getLine(), pSBMLError->getColumn(), pSBMLError->getMessage().c_str());
                break;

              case LIBSBML_SEV_FATAL:

              // treat unknown as fatal
              default:

                //CCopasiMessage(CCopasiMessage::TRACE, MCSBML + 40,"FATAL",pSBMLError->getLine(),pSBMLError->getColumn(),pSBMLError->getMessage().c_str());
                if (pSBMLError->getErrorId() == 10804)
                  {
                    // this error indicates a problem with a notes element
                    // although libsbml flags this as fatal, we would still
                    // like to read the model
                    CCopasiMessage(messageType, MCSBML + 40, "ERROR", pSBMLError->getErrorId(), pSBMLError->getLine(), pSBMLError->getColumn(), pSBMLError->getMessage().c_str());
                  }
                else
                  {
                    fatal = i;
                  }

                break;
            }

          //std::cerr << pSBMLError->getMessage() << std::endl;
        }

      if (fatal != -1)
        {
          const XMLError* pSBMLError = sbmlDoc->getError(fatal);
          CCopasiMessage Message(CCopasiMessage::EXCEPTION, MCXML + 2,
                                 pSBMLError->getLine(),
                                 pSBMLError->getColumn(),
                                 pSBMLError->getMessage().c_str());

          finishImport();

          return true;
        }
    }
  else
    {
      if (sbmlDoc->getLevel() > 2)
        {
          // we check if the model contained a required package
          unsigned int i, iMax = sbmlDoc->getNumErrors();

          for (i = 0; i < iMax ; ++i)
            {
              const XMLError* pSBMLError = sbmlDoc->getError(i);

              if (pSBMLError->getErrorId() == 99107)
                {
                  if (pSBMLError->getMessage().find("'spatial'") != std::string::npos)
                    {
                      CCopasiMessage(CCopasiMessage::ERROR,
                                     "The model you tried to open requires the SBML spatial package. "
                                     "This version of COPASI does not support spatial models.");
                    }
                  else
                    {
                      std::stringstream str;
                      str << sbmlDoc->getUnknownPackagePrefix(0);

                      for (int k = 1; k < sbmlDoc->getNumUnknownPackages(); ++k)
                        str << ", " << sbmlDoc->getUnknownPackagePrefix(k);

                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 96, str.str().c_str());
                    }
                }
            }
        }
    }

  if (sbmlDoc->getPlugin("comp") != NULL && sbmlDoc->isSetPackageRequired("comp"))
    {

      if (sbmlDoc->getNumErrors(LIBSBML_SEV_ERROR) > 0)
        {
          std::string message =
            "The SBML model you are trying to import uses the Hierarchical Modeling extension. "
            "In order to import this model in COPASI, it has to be flattened, however flattening is "
            "not possible because of the following errors:\n" + sbmlDoc->getErrorLog()->toString();

          // escape potential percent signs that would lead to an error when passed to CCopasiMessage
          CPrefixNameTransformer::replaceStringInPlace(message, "%", "%%");

          CCopasiMessage(CCopasiMessage::EXCEPTION, message.c_str());
        }

#if LIBSBML_HAS_PACKAGE_COMP
      // apply the name transformer
      CompModelPlugin* mPlug = dynamic_cast<CompModelPlugin*>(sbmlDoc->getModel()->getPlugin("comp"));
      CPrefixNameTransformer trans;

      if (mPlug != NULL)
        {
          mPlug->setTransformer(&trans);
        }

#endif //LIBSBML_HAS_PACKAGE_COMP

      // the sbml comp package is used, and the required flag is set, so it stands to reason
      // that we need to flatten the document
      sbmlDoc->getErrorLog()->clearLog();

      ConversionProperties props;
      props.addOption("flatten comp");
      props.addOption("leavePorts", false);
      props.addOption("basePath", mpDataModel->getReferenceDirectory());

      if (sbmlDoc->convert(props) != LIBSBML_OPERATION_SUCCESS)
        {
          std::string message =
            "The SBML model you are trying to import uses the Hierarchical Modeling extension. "
            "In order to import this model in COPASI, it has to be flattened, however flattening failed";

          if (sbmlDoc->getNumErrors() == 0)
            message += ".";
          else
            message += " with the following errors:\n" + sbmlDoc->getErrorLog()->toString();

          CCopasiMessage(CCopasiMessage::EXCEPTION, message.c_str());
        }
    }

  finishCurrentStep();
  return false;
}

/**
 * Function parses an SBML document with libsbml and converts it to a COPASI CModel
 * object which is returned. Deletion of the returned pointer is up to the
 * caller.
 */
CModel*
SBMLImporter::parseSBML(const std::string& sbmlDocumentText,
                        SBMLDocument *& pSBMLDocument,
                        std::map<const CDataObject*, SBase*>& copasi2sbmlmap,
                        CListOfLayouts *& prLol,
                        CDataModel* pDataModel)
{
  this->mUsedSBMLIdsPopulated = false;
  this->mAvogadroSet = false;
  mpDataModel = pDataModel;
  assert(mpDataModel != NULL);

  this->mpCopasiModel = NULL;

  SBMLReader* reader = new SBMLReader();

  mGlobalStepCounter = 0;

  if (mpProcessReport != NULL)
    {
      mpProcessReport->setName("Importing SBML file...");
      mGlobalStepTotal = 16;
      mGlobalStepHandle = mpProcessReport->addItem("Step",
                          mGlobalStepCounter,
                          &mGlobalStepTotal);

      mCurrentStepCounter = 0;
      mCurrentStepTotal = 1;
      mCurrentStepHandle = mpProcessReport->addItem("Reading SBML file...",
                           mCurrentStepCounter,
                           &mCurrentStepTotal);
    }

  SBMLDocument* sbmlDoc = reader->readSBMLFromString(sbmlDocumentText);

  if (createProgressStepOrStop(2, 1, "Checking consistency..."))
    {
      finishImport();
      return NULL;
    }

  if (checkValidityOfSourceDocument(sbmlDoc))
    {
      finishImport();
      return NULL;
    }

  if (sbmlDoc->getModel() == NULL)
    {
      CCopasiMessage Message(CCopasiMessage::ERROR, MCSBML + 2);

      finishImport();
      return NULL;
    }

  delete reader;
  pSBMLDocument = sbmlDoc;
  this->mLevel = pSBMLDocument->getLevel();
  // remember the original level of the document because we convert Level 1 documents to Level 2
  // For the import of rules, we need to remember that is was actually a level 1 document
  // because otherwise we throw error messages on rules on parameters since the parameters
  //  have been set to constant by the conversation to Level 2
  this->mOriginalLevel = this->mLevel;
  this->mVersion = pSBMLDocument->getVersion();

  if (mLevel == 1)
    {
      unsigned int i, iMax = pSBMLDocument->getModel()->getNumCompartments();

      for (i = 0; i < iMax; ++i)
        {
          Compartment* pCompartment = pSBMLDocument->getModel()->getCompartment(i);
          pCompartment->setSize(pCompartment->getVolume());
        }

      pSBMLDocument->setLevelAndVersion(2, 1);
      mLevel = pSBMLDocument->getLevel();
    }

  this->mpCopasiModel = this->createCModelFromSBMLDocument(sbmlDoc, copasi2sbmlmap);

  if (createProgressStepOrStop(16, 1, "Importing layout ..."))
    {
      finishImport();
      return NULL;
    }

  prLol = new CListOfLayouts("ListOfLayouts", mpDataModel);
  Model* sbmlmodel = pSBMLDocument->getModel();

  if (sbmlmodel && prLol)
    {
      LayoutModelPlugin *lmPlugin = (LayoutModelPlugin*)sbmlmodel->getPlugin("layout");

      if (lmPlugin != NULL)
        SBMLDocumentLoader::readListOfLayouts(*prLol,
                                              *lmPlugin->getListOfLayouts(),
                                              copasi2sbmlmap);
    }

  finishImport();

  return this->mpCopasiModel;
}

CModelValue* SBMLImporter::createCModelValueFromParameter(const Parameter* sbmlParameter, CModel* copasiModel, std::map<const CDataObject*, SBase*>& copasi2sbmlmap)
{

  std::string name = sbmlParameter->getName();

  if (isEmptyOrWhiteSpace(name))
    {
      name = sbmlParameter->getId();
    }

  std::string appendix;
  unsigned int counter = 2;
  std::ostringstream numberStream;

  while (copasiModel->getModelValues().getIndex(name + appendix) != C_INVALID_INDEX)
    {
      numberStream.str("");
      numberStream << "_" << counter;
      counter++;
      appendix = numberStream.str();
    }

  std::string sbmlId;

  if (this->mLevel == 1)
    {
      sbmlId = sbmlParameter->getName();
    }
  else
    {
      sbmlId = sbmlParameter->getId();
    }

  CModelValue* pMV = copasiModel->createModelValue(name + appendix, 0.0);
  copasi2sbmlmap[pMV] = const_cast<Parameter*>(sbmlParameter);
  pMV->setSBMLId(sbmlId);
  SBMLImporter::importMIRIAM(sbmlParameter, pMV);
  SBMLImporter::importNotes(pMV, sbmlParameter);

  if (this->mLevel > 2)
    {
      this->mSBMLIdModelValueMap[sbmlId] = pMV;
    }

  if (sbmlParameter->isSetUnits())
    {
      const SUnitInfo & UnitInfo = importUnit(sbmlParameter->getModel()->getUnitDefinition(sbmlParameter->getUnits()), false);

      if (UnitInfo.valid)
        {
          pMV->setUnitExpression(UnitInfo.expression);
        }
      else
        {
          // chances are that it is one of the default units.
          UnitKind_t kind = UnitKind_forName(sbmlParameter->getUnits().c_str());

          if (kind != UNIT_KIND_INVALID)
            pMV->setUnitExpression(unitKindToString(kind));
        }
    }

  return pMV;
}

bool SBMLImporter::sbmlId2CopasiCN(ASTNode* pNode, std::map<const CDataObject*, SBase*>& copasi2sbmlmap, CCopasiParameterGroup& pParamGroup,
                                   SBase* pParentObject)
{
  // TODO CRITICAL We need to use a node iterator

  bool success = true;
  unsigned int i, iMax = pNode->getNumChildren();

  if (pNode->getType() == AST_NAME)
    {
      Reaction* pParentReaction = dynamic_cast<Reaction*>(pParentObject);
      Compartment* pSBMLCompartment = NULL;
      Species* pSBMLSpecies = NULL;
      Reaction* pSBMLReaction = NULL;
      Parameter* pSBMLParameter = NULL;
      std::string sbmlId;
      std::string name = pNode->getName();
      CCopasiParameter* pParam = pParamGroup.getParameter(name);

      std::map<std::string, double>::const_iterator speciesReference = mSBMLSpeciesReferenceIds.find(name);

      // replace species references only in case we don't have a local parameter
      // that shadows it
      if (speciesReference  != mSBMLSpeciesReferenceIds.end()
          && (pParentReaction == NULL
              || pParentReaction->getKineticLaw() == NULL
              || pParentReaction->getKineticLaw()->getParameter(name) == NULL))
        {
          // replace the name with the value
          pNode->setType(AST_REAL);
          pNode->setValue(speciesReference->second);
        }
      else if (pParam)
        {
          pNode->setName(pParam->getStringCN().c_str());
        }
      else
        {
          std::map<const CDataObject*, SBase*>::iterator it = copasi2sbmlmap.begin();
          std::map<const CDataObject*, SBase*>::iterator endIt = copasi2sbmlmap.end();
          bool found = false;

          while (it != endIt)
            {
              int type = it->second->getTypeCode();

              switch (type)
                {
                  case SBML_COMPARTMENT:
                    pSBMLCompartment = dynamic_cast<Compartment*>(it->second);

                    if (this->mLevel == 1)
                      {
                        sbmlId = pSBMLCompartment->getName();
                      }
                    else
                      {
                        sbmlId = pSBMLCompartment->getId();
                      }

                    if (sbmlId == pNode->getName())
                      {
                        pNode->setName(dynamic_cast<const CCompartment*>(it->first)->getObject(CCommonName("Reference=InitialVolume"))->getStringCN().c_str());
                        found = true;
                      }

                    break;

                  case SBML_SPECIES:
                    pSBMLSpecies = dynamic_cast<Species*>(it->second);

                    if (this->mLevel == 1)
                      {
                        sbmlId = pSBMLSpecies->getName();
                      }
                    else
                      {
                        sbmlId = pSBMLSpecies->getId();
                      }

                    if (sbmlId == pNode->getName())
                      {
                        pNode->setName(dynamic_cast<const CMetab*>(it->first)->getObject(CCommonName("Reference=InitialConcentration"))->getStringCN().c_str());
                        found = true;
                      }

                    break;

                  case SBML_REACTION:
                    pSBMLReaction = dynamic_cast<Reaction*>(it->second);

                    if (this->mLevel == 1)
                      {
                        sbmlId = pSBMLReaction->getName();
                      }
                    else
                      {
                        sbmlId = pSBMLReaction->getId();
                      }

                    if (sbmlId == pNode->getName())
                      {
                        pNode->setName(dynamic_cast<const CReaction*>(it->first)->getObject(CCommonName("Reference=ParticleFlux"))->getStringCN().c_str());
                        found = true;
                      }

                    break;

                  case SBML_PARAMETER:
                    pSBMLParameter = dynamic_cast<Parameter*>(it->second);

                    if (this->mLevel == 1)
                      {
                        sbmlId = pSBMLParameter->getName();
                      }
                    else
                      {
                        sbmlId = pSBMLParameter->getId();
                      }

                    if (sbmlId == pNode->getName())
                      {
                        pNode->setName(dynamic_cast<const CModelValue*>(it->first)->getValueReference()->getStringCN().c_str());
                        found = true;
                      }

                    break;

                  default:
                    break;
                }

              ++it;
            }

          if (!found) success = false;
        }
    }

  for (i = 0; i < iMax; ++i)
    {
      if (!this->sbmlId2CopasiCN(pNode->getChild(i), copasi2sbmlmap, pParamGroup, pParentObject))
        {
          success = false;
          break;
        }
    }

  return success;
}

#ifdef COPASI_DEBUG
void SBMLImporter::printMap(const std::map<CDataObject*, SBase*> & copasi2sbml)
{
  std::map<CDataObject*, SBase*>::const_iterator it = copasi2sbml.begin();
  std::map<CDataObject*, SBase*>::const_iterator end = copasi2sbml.end();
  std::cout << "Number of elements: " << copasi2sbml.size() << std::endl;

  while (it != end)
    {
      std::cout << "(@" << it->first << ")" << it->first->getObjectName() << " : " << "(@" << it->second << ")" << it->second->getTypeCode() << std::endl;
      ++it;
    }

  std::cout << std::endl;
}
#endif // COPASI_DEBUG

void SBMLImporter::restoreFunctionDB()
{
  // set all the old sbml ids
  std::map<CFunction*, std::string>::iterator it = this->sbmlIdMap.begin();
  std::map<CFunction*, std::string>::iterator endIt = this->sbmlIdMap.end();

  while (it != endIt)
    {
      it->first->setSBMLId(it->second);
      ++it;
    }

  // remove all the functions that were added during import
  std::set<std::string>::iterator it2 = this->mCreatedFunctions.begin();
  std::set<std::string>::iterator endIt2 = this->mCreatedFunctions.end();

  while (it2 != endIt2)
    {
      CEvaluationTree* pTree = CRootContainer::getFunctionList()->findFunction(*it2);

      if (pTree != NULL && pTree->getType() == CEvaluationTree::UserDefined)
        {
          CRootContainer::getFunctionList()->removeFunction(pTree->getKey());
        }

      ++it2;
    }
}

void
SBMLImporter::preprocessNode(ConverterASTNode * pNode, Model * pSBMLModel,
                             std::map< const CDataObject *, SBase * > & copasi2sbmlmap,
                             Reaction * pSBMLReaction, bool ignoreRate /*= false*/)
{
  // this function goes through the tree several times.
  // this can probably be handled more intelligently
  // maybe we should use some kind of visitor schema
  //
  // check if there are units on pure numbers
  // so that we can create a warning that they have been ignored

  if (this->mLevel > 2 && !this->mUnitOnNumberFound)
    {
      this->mUnitOnNumberFound = SBMLImporter::checkForUnitsOnNumbers(pNode);
    }

  // first replace the calls to explicitly time dependent functions
  this->replaceTimeDependentFunctionCalls(pNode);

  if (!this->mDelayFound || pSBMLReaction != NULL)
    {
      bool result = isDelayOrRateFunctionUsed(pNode);

      if (pSBMLReaction != NULL && result)
        {
          // if this is the first delay we find, we have to populate the id set
          // in order to be able to create new global parameters with unique ids
          if (!this->mUsedSBMLIdsPopulated)
            {
              std::map<std::string, const SBase*> idMap;
              std::map<std::string, const SBase*> metaIdMap;
              // this is overkill, but better than writing yet another function to
              // collect ids
              SBMLUtils::collectIds(pSBMLModel, idMap, metaIdMap);
              std::map<std::string, const SBase*>::iterator it = idMap.begin(), endit = idMap.end();

              while (it != endit)
                {
                  this->mUsedSBMLIds.insert(it->first);
                  ++it;
                }

              this->mUsedSBMLIdsPopulated = true;
              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 86);
            }

          // we need a map to store the replacements for local parameters
          // which occur within delay calls
          std::map<std::string, std::string> replacementMap;
          replaceDelayAndRateOfInReaction(pNode, pSBMLModel, copasi2sbmlmap, pSBMLReaction, replacementMap);

          if (!replacementMap.empty())
            {
              // replace all local parameter nodes which have been converted to global parameters
              // and that were not in delay calls
              replace_name_nodes(pNode, replacementMap);

              // delete the local parameters that have been replaced from the
              // reaction
              std::map<std::string, std::string>::const_iterator it = replacementMap.begin(), endit = replacementMap.end();

              // starting with SBML Level 3, the parameters of a kinetic law are expressed in
              // terms of a new class called LocalParameter instead of Parameter
              // Unfortunately libsbml 4.1 uses separate data structures for
              // the Parameters and the LocalParameters which mandates a small
              // code change to be on the safe side
              ListOfParameters* pList = NULL;

              if (this->mLevel > 2)
                {
                  pList = pSBMLReaction->getKineticLaw()->getListOfLocalParameters();
                }
              else
                {
                  pList = pSBMLReaction->getKineticLaw()->getListOfParameters();
                }

              Parameter* pParam = NULL;

              while (it != endit)
                {
                  pParam = pList->remove(it->first);
                  assert(pParam != NULL);
                  pdelete(pParam);
                  ++it;
                }

              mReactionsWithReplacedLocalParameters.insert(pSBMLReaction->getId());
            }
        }

      this->mDelayFound = result;
    }

  this->replaceCallNodeNames(pNode);
  this->replaceTimeAndAvogadroNodeNames(pNode);

  if (pSBMLReaction != NULL && !this->mSubstanceOnlySpecies.empty())
    {
      this->multiplySubstanceOnlySpeciesByVolume(pNode);
    }

  if (!this->mSubstanceOnlySpecies.empty()
      && this->mpCopasiModel->getQuantityUnit() != "#"
      && pSBMLReaction == NULL)
    {
      this->replaceAmountReferences(pNode, pSBMLModel, this->mpCopasiModel->getQuantity2NumberFactor(), copasi2sbmlmap);
    }
}

/**
 * This method replaces references to the id of species which have the
 * hasOnlySubstanceUnits flag set with the reference divided by avogadros
 * number.
 */
void SBMLImporter::replaceAmountReferences(ConverterASTNode* pASTNode, Model* pSBMLModel, double factor, std::map<const CDataObject*, SBase*>& copasi2sbmlmap)
{
  CNodeIterator< ConverterASTNode > itNode(pASTNode);
  itNode.setProcessingModes(CNodeIteratorMode::Before);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      // check if there is already a multiplication with the avogadro number
      // if so, we just replace that multiplication instead of adding an additional division
      //
      // we only do this, if there are two children to the multiplication because otherwise we would have to do sophisticated checks
      // whether the multiplication is really only between a certain species and the avogadro number
      if (itNode->getType() == AST_TIMES && itNode->getNumChildren() == 2)
        {
          std::set<const Parameter*>::const_iterator avoIt = this->mPotentialAvogadroNumbers.begin();
          std::set<const Parameter*>::const_iterator avoEndit = this->mPotentialAvogadroNumbers.end();
          // check if one of the potential avogradro numbers is a child to this multiplication
          ASTNode* pChild1 = itNode->getChild(0);
          ASTNode* pChild2 = itNode->getChild(1);
          assert(pChild1 != NULL);
          assert(pChild2 != NULL);

          if (pChild1->getType() == AST_NAME && pChild2->getType() == AST_NAME)
            {
              std::string id1 = pChild1->getName();
              std::string id2 = pChild2->getName();
              ASTNode *pAvogadro = NULL, *pSpecies = NULL;

              if (pChild1 != NULL && pChild2 != NULL)
                {
                  while (avoIt != avoEndit)
                    {
                      if (id1 == (*avoIt)->getId())
                        {
                          pAvogadro = pChild1;
                          pSpecies = pChild2;
                          // store the id of the species in id1 for use below
                          id1 = id2;
                          break;
                        }

                      if (id2 == (*avoIt)->getId())
                        {
                          pAvogadro = pChild2;
                          pSpecies = pChild1;
                          break;
                        }

                      ++avoIt;
                    }

                  if (pAvogadro != NULL)
                    {
                      // check if the potential species node is really a substance only species
                      //
                      std::map<Species*, Compartment*>::const_iterator it = this->mSubstanceOnlySpecies.begin();
                      std::map<Species*, Compartment*>::const_iterator endit = this->mSubstanceOnlySpecies.end();

                      while (it != endit)
                        {
                          if (it->first->getId() == id1)
                            {
                              // delete the two children
                              itNode->removeChild(1);
                              itNode->removeChild(0);
                              pdelete(pChild1);
                              pdelete(pChild2);
                              // now we know that we can change the current node
                              // to represent the species
                              itNode->setType(AST_NAME);
                              itNode->setName(id1.c_str());
                              itNode.skipChildren();
                              break;
                            }

                          ++it;
                        }
                    }
                }
            }
          else if ((pChild1->getType() == AST_NAME && (pChild2->getType() == AST_REAL || pChild2->getType() == AST_REAL_E)) ||
                   (pChild2->getType() == AST_NAME && (pChild1->getType() == AST_REAL || pChild1->getType() == AST_REAL_E)))
            {
              double value = 0.0;
              std::string id;

              if (pChild1->getType() == AST_NAME)
                {
                  value = pChild2->getMantissa() * pow(10.0, (double)pChild2->getExponent());
                  id = pChild1->getName();
                }
              else
                {
                  value = pChild1->getMantissa() * pow(10.0, (double)pChild1->getExponent());
                  id = pChild2->getName();
                }

              if (areApproximatelyEqual(factor, value, 1e-3))
                {
                  std::map<Species*, Compartment*>::const_iterator it = this->mSubstanceOnlySpecies.begin();
                  std::map<Species*, Compartment*>::const_iterator endit = this->mSubstanceOnlySpecies.end();

                  while (it != endit)
                    {
                      if (it->first->getId() == id)
                        {
                          // delete the two children
                          itNode->removeChild(1);
                          itNode->removeChild(0);
                          pdelete(pChild1);
                          pdelete(pChild2);
                          // now we know that we can change the current node
                          // to represent the species
                          itNode->setType(AST_NAME);
                          itNode->setName(id.c_str());
                          itNode.skipChildren();
                          break;
                        }

                      ++it;
                    }
                }
            }
        }
      else if (itNode->getType() == AST_NAME)
        {
          // check if pNode is a reference to a hasOnlySubstance species
          std::string id = itNode->getName();
          std::map<Species*, Compartment*>::const_iterator it = this->mSubstanceOnlySpecies.begin();
          std::map<Species*, Compartment*>::const_iterator endit = this->mSubstanceOnlySpecies.end();

          while (it != endit)
            {
              if (it->first->getId() == id)
                {
                  break;
                }

              ++it;
            }

          if (it != endit)
            {
              // replace pNode by a division by the quantity to number
              // factor
              if (this->mPotentialAvogadroNumbers.empty())
                {
                  this->createHasOnlySubstanceUnitFactor(pSBMLModel, factor, copasi2sbmlmap);
                }

              itNode->setType(AST_DIVIDE);
              itNode->setCharacter('/');
              char * userData = static_cast< char * >(itNode->getUserData());
              itNode->setUserData(NULL);
              ConverterASTNode * pChild = new ConverterASTNode(AST_NAME);
              pChild->setName(id.c_str());
              pChild->setUserData(userData);
              itNode->addChild(pChild);
              id = (*this->mPotentialAvogadroNumbers.begin())->getId();
              pChild = new ConverterASTNode(AST_NAME);
              pChild->setName(id.c_str());
              itNode->addChild(pChild);
            }
        }
    }
}

bool SBMLImporter::isDelayOrRateFunctionUsed(ConverterASTNode* pASTNode)
{
  bool result = false;
  CNodeIterator< ConverterASTNode > itNode(pASTNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      if (itNode->getType() == AST_FUNCTION_DELAY || itNode->getType() == AST_FUNCTION_RATE_OF)
        {
          result = true;
          break;
        }
    }

  return result;
}

void SBMLImporter::replaceTimeAndAvogadroNodeNames(ASTNode* pASTNode)
{
  CNodeIterator< ASTNode > itNode(pASTNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      if (itNode->getType() == AST_NAME_TIME)
        {
          itNode->setName(this->mpCopasiModel->getObject(CCommonName("Reference=Time"))->getStringCN().c_str());
        }
      else if (itNode->getType() == AST_NAME_AVOGADRO)
        {
          itNode->setName(this->mpCopasiModel->getObject(CCommonName("Reference=Avogadro Constant"))->getStringCN().c_str());
        }
    }
}

void SBMLImporter::replaceCallNodeNames(ASTNode* pASTNode)
{
  CNodeIterator< ASTNode > itNode(pASTNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      if (itNode->getType() == AST_FUNCTION)
        {
          std::map<std::string, std::string>::const_iterator pos = this->mFunctionNameMapping.find(itNode->getName());

          std::map<std::string, std::string>::const_iterator knownPos = mKnownCustomUserDefinedFunctions.find(itNode->getName());

          if (pos == this->mFunctionNameMapping.end())
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 47, itNode->getName());
            }

          if (knownPos != mKnownCustomUserDefinedFunctions.end() &&
              (knownPos->second == "RATE" && itNode->getNumChildren() == 1))
            {
              // replace the known function with the correct calls.
              // replace rateOf with the rate of whatever is inside
              std::string symbol = itNode->getChild(0)->getName();
              itNode->removeChild(0);
              itNode->setType(AST_NAME);
              itNode->setName(symbol.c_str());
              itNode->setUserData(strdup("RATE"));
            }
          else
            {
              std::string newName = pos->second;
              itNode->setName(newName.c_str());
              this->mCreatedFunctions.insert(newName);
            }
        }
      else if (itNode->getType() == AST_FUNCTION_RATE_OF && itNode->getNumChildren() == 1)
        {
          std::string symbol = itNode->getChild(0)->getName();
          itNode->removeChild(0);
          itNode->setType(AST_NAME);
          itNode->setName(symbol.c_str());
          itNode->setUserData(strdup("RATE"));
        }
    }
}

/**
 * The methods gets a function where all the parameters have a usage of "PARAMETER".
 * In addition it get the root node of a call to that function which is an expression
 * and contains the actual objects with which the function is called in a certain reaction.
 * From this expression we can determine if there already is a function in the database
 * that does the same. Or we can find out if this function is a Mass Action kinetic.
 */
CFunction* SBMLImporter::findCorrespondingFunction(const CExpression * pExpression, const CReaction* pCopasiReaction)
{
  // We are certain at this point that pExpression is a simple function call.

  // Check whether a function with the name exists in COPASI and whether it is suitable
  CFunction* pCorrespondingFunction = NULL;

  std::string Name = pExpression->getRoot()->getData();
  pCorrespondingFunction = CRootContainer::getFunctionList()->findFunction(Name);

  if (pCorrespondingFunction != NULL)
    {
      const CFunctionParameters & Variables = pCorrespondingFunction->getVariables();

      for (size_t i = 0; i < Variables.size(); ++i)
        {
          // This fails for global parameters but those are handled in a second attempt
          if (pCopasiReaction->getParameterIndex(Variables[i]->getObjectName()) == C_INVALID_INDEX)
            {
              pCorrespondingFunction = NULL;
              break;
            }
        }
    }

  if (pCorrespondingFunction != NULL)
    {
      return pCorrespondingFunction;
    }

  // TODO This has never worked
#ifdef XXXX
  // Check for suitable functions which have a different name but have the same call tree as
  std::vector< CFunction * > functions = functionDB->suitableFunctions(pCopasiReaction->getChemEq().getSubstrates().size(),
                                         pCopasiReaction->getChemEq().getProducts().size(),
                                         pCopasiReaction->isReversible() ? TriTrue : TriFalse);
  size_t i, iMax = functions.size();

  for (i = 0; i < iMax; ++i)
    {
      pCorrespondingFunction = (functions[i]);

      // make sure the function is not compared to itself since it can already
      // be in the database if it has been used a call in another function
      // don't compare the mass action kinetics
      if ((pCorrespondingFunction != tree) && (!dynamic_cast<CMassAction*>(pCorrespondingFunction)) && areEqualFunctions(pCorrespondingFunction, tree))
        {
          const CFunctionParameters & Variables = pFun->getVariables();

          for (size_t i = 0; i < Variables.size(); ++i)
            {
              if (pCopasiReaction->getParameterIndex(Variables[i]->getObjectName()) == C_INVALID_INDEX)
                {
                  pCorrespondingFunction = NULL;
                  break;
                }
            }

          pCorrespondingFunction = pFun;
          break;
        }
    }

#endif // XXXX

  return pCorrespondingFunction;
}

// static
bool SBMLImporter::areEqualFunctions(const CFunction* pFun, const CFunction* pFun2)
{
  bool result = true;
  const CFunctionParameters& funParams1 = pFun->getVariables();
  const CFunctionParameters& funParams2 = pFun2->getVariables();

  if (funParams1.size() == funParams2.size())
    {
      size_t i, iMax = funParams1.size();

      for (i = 0; i < iMax; ++i)
        {
          const CFunctionParameter* pFunParam1 = funParams1[i];
          const CFunctionParameter* pFunParam2 = funParams2[i];

          // Compare paramemeter types if assigned
          if (pFunParam1->getObjectName() != pFunParam2->getObjectName()
              || (pFunParam1->getUsage() != CFunctionParameter::Role::VARIABLE
                  && pFunParam1->getUsage() != pFunParam2->getUsage()))
            {
              result = false;
              break;
            }
        }

      if (result == true)
        {
          const CEvaluationNode* pNodeFun1 = static_cast<const CEvaluationNode*>(pFun->getRoot());
          const CEvaluationNode* pNodeFun2 = static_cast<const CEvaluationNode*>(pFun2->getRoot());
          result = areEqualSubtrees(pNodeFun1, pNodeFun2);
        }
    }
  else
    {
      result = false;
    }

  return result;
}

bool SBMLImporter::isEmptyOrWhiteSpace(const std::string & name)
{
  if (name.empty())
    return true;

  return name.find_first_not_of(" \t\r\n") == std::string::npos;
}

// static
bool SBMLImporter::areEqualSubtrees(const CEvaluationNode* pNode1, const CEvaluationNode* pNode2)
{
  // TODO CRITICAL We need to use a node iterator
  bool result = ((pNode1->mainType() == pNode2->mainType()) &&
                 (pNode1->subType() == pNode2->subType()) &&
                 (pNode1->getData() == pNode2->getData()));

  const CEvaluationNode* pChild1 = static_cast<const CEvaluationNode*>(pNode1->getChild());
  const CEvaluationNode* pChild2 = static_cast<const CEvaluationNode*>(pNode2->getChild());

  while (result && pChild1 && pChild2)
    {
      result = areEqualSubtrees(pChild1, pChild2);
      pChild1 = static_cast<const CEvaluationNode*>(pChild1->getSibling());
      pChild2 = static_cast<const CEvaluationNode*>(pChild2->getSibling());
    }

  result = (result && !pChild1 && !pChild2);
  return result;
}

std::vector<CEvaluationNodeObject*>* SBMLImporter::isMassAction(const CEvaluationTree* pTree, const CChemEq& chemicalEquation, const CEvaluationNodeCall* pCallNode)
{
  // TODO CRITICAL We need to use a node iterator
  CEvaluationTree::Type type = pTree->getType();
  std::vector< std::vector< std::string > > functionArgumentCNs;
  const CEvaluationNode* pChildNode = NULL;
  std::string str;
  std::vector<CEvaluationNodeObject*>* result = NULL;

  switch (type)
    {
      case CEvaluationTree::Function:
      case CEvaluationTree::UserDefined:
      case CEvaluationTree::PreDefined:
        pChildNode = static_cast<const CEvaluationNode*>(pCallNode->getChild());

        while (pChildNode)
          {
            if (pChildNode->mainType() == CEvaluationNode::MainType::OBJECT)
              {
                str = pChildNode->getData().substr(1, pChildNode->getData().length() - 2);
                functionArgumentCNs.push_back(std::vector<std::string>());
                functionArgumentCNs[functionArgumentCNs.size() - 1].push_back(str);
                pChildNode = static_cast<const CEvaluationNode*>(pChildNode->getSibling());
              }
            else
              {
                fatalError();
              }
          }

        result = this->isMassActionFunction(dynamic_cast<const CFunction*>(pTree), chemicalEquation, functionArgumentCNs);
        break;

      case CEvaluationTree::Expression:
        result = this->isMassActionExpression(pTree->getRoot(), chemicalEquation);
        break;

      default:
        fatalError();
        break;
    }

  return result;
}

std::vector<CEvaluationNodeObject*>* SBMLImporter::isMassActionExpression(const CEvaluationNode* pRootNode, const CChemEq& chemicalEquation)
{
  bool result = true;
  std::vector<CEvaluationNodeObject*>* v = NULL;

  if (chemicalEquation.getReversibility())
    {
#ifdef COPASI_DEBUG
      CEvaluationNode* pTmpNode = pRootNode->copyBranch();
//      CEvaluationNode* pTmpNode = CEvaluationNodeNormalizer::normalize(pRootNode);
#else
      CEvaluationNode* pTmpNode = pRootNode->copyBranch();
#endif /* COPASI_DEBUG */
      assert(pTmpNode != NULL);
      // the root node must be a minus operator
      // the two children must be irreversible mass action terms
      result = (pTmpNode->mainType() == CEvaluationNode::MainType::OPERATOR && (pTmpNode->subType()) == CEvaluationNode::SubType::MINUS);

      if (result)
        {
          const CEvaluationNode* pChildNode = static_cast<const CEvaluationNode*>(pTmpNode->getChild());
          result = (pChildNode != NULL);

          if (result)
            {
              CChemEq tmpEq;
              const CDataVector<CChemEqElement>* metabolites = &chemicalEquation.getSubstrates();
              size_t i, iMax = metabolites->size();
              result = (iMax > 0);

              if (result)
                {
                  for (i = 0; i < iMax; ++i)
                    {
                      const CChemEqElement* element = &metabolites->operator[](i);
                      tmpEq.addMetabolite(element->getMetaboliteKey(), element->getMultiplicity(), CChemEq::SUBSTRATE);
                    }

                  v = this->isMassActionExpression(pChildNode, tmpEq);

                  if (!v)
                    {
                      fatalError();
                    }

                  result = !v->empty();

                  if (result)
                    {
                      pChildNode = static_cast<const CEvaluationNode*>(pChildNode->getSibling());
                      result = (pChildNode != NULL);

                      if (result)
                        {
                          CChemEq tmpEq2;
                          metabolites = &chemicalEquation.getProducts();
                          iMax = metabolites->size();
                          result = (iMax > 0);

                          for (i = 0; i < iMax; ++i)
                            {
                              const CChemEqElement* element = &metabolites->operator[](i);
                              tmpEq2.addMetabolite(element->getMetaboliteKey(), element->getMultiplicity(), CChemEq::SUBSTRATE);
                            }

                          std::vector<CEvaluationNodeObject*>* v2 = this->isMassActionExpression(pChildNode, tmpEq2);

                          if (!v2)
                            {
                              fatalError();
                            }

                          result = !v2->empty();

                          if (result &&
                              (*v)[0]->getData() != (*v2)[0]->getData())
                            {
                              v->push_back((*v2)[0]);
                            }
                          else
                            {
                              v->clear();
                            }

                          pdelete(v2);
                        }
                    }
                }
              else
                {
                  v = new std::vector<CEvaluationNodeObject*>;
                }
            }
        }
      else
        {
          v = new std::vector<CEvaluationNodeObject*>;
        }

      pdelete(pTmpNode);
    }
  else
    {
      // the expression must contain exactly one global or local parameter
      // the expression must contain each substrate in the CChemicalReaction
      std::vector<const CEvaluationNode*> arguments;
      std::map<const CMetab*, C_FLOAT64> multiplicityMap;
      this->separateProductArguments(pRootNode, arguments);
      size_t numParameters = 0, i, iMax = arguments.size();
      v = new std::vector<CEvaluationNodeObject*>;

      if (iMax != 0)
        {
          for (i = 0; (i < iMax) && (numParameters < 2); ++i)
            {
              const CEvaluationNode* pNode = arguments[i];

              // the node can either be an object node
              // or it can be a power function node
              if (pNode->mainType() == CEvaluationNode::MainType::OBJECT)
                {
                  // it can be a global or a local parameter or an metabolite
                  std::string objectCN = pNode->getData().substr(1, pNode->getData().length() - 2);
                  const CDataObject* pObject = CObjectInterface::DataObject(mpCopasiModel->getObjectFromCN(objectCN));

                  if (!pObject)
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 39, objectCN.c_str());
                    }

                  if (pObject->hasFlag(CDataObject::Reference))
                    {
                      pObject = pObject->getObjectParent();

                      if (dynamic_cast<const CMetab*>(pObject))
                        {
                          const CMetab* pMetab = static_cast<const CMetab*>(pObject);

                          if (multiplicityMap.find(pMetab) != multiplicityMap.end())
                            {
                              multiplicityMap[pMetab] = multiplicityMap[pMetab] + 1.0;
                            }
                          else
                            {
                              multiplicityMap[pMetab] = 1.0;
                            }
                        }
                      else if (dynamic_cast<const CModelValue*>(pObject))
                        {
                          ++numParameters;
                          v->push_back(new CEvaluationNodeObject((pNode->subType()), pNode->getData()));
                        }
                      else
                        {
                          result = false;
                          break;
                        }
                    }
                  else if (dynamic_cast<const CCopasiParameter*>(pObject))
                    {
                      ++numParameters;
                      v->push_back(new CEvaluationNodeObject((pNode->subType()), pNode->getData()));
                    }
                  else
                    {
                      result = false;
                      break;
                    }
                }
              else if (pNode->mainType() == CEvaluationNode::MainType::OPERATOR && pNode->subType() == CEvaluationNode::SubType::POWER)
                {
                  // the two children must be a metabolite node and a number node in this order
                  const CEvaluationNode* pChildNode = static_cast<const CEvaluationNode*>(pNode->getChild());

                  if (pChildNode->mainType() == CEvaluationNode::MainType::OBJECT)
                    {
                      std::string objectCN = pChildNode->getData().substr(1, pChildNode->getData().length() - 2);
                      const CDataObject* pObject = CObjectInterface::DataObject(mpCopasiModel->getObjectFromCN(objectCN));
                      assert(pObject);

                      if (pObject->hasFlag(CDataObject::Reference))
                        {
                          pObject = pObject->getObjectParent();

                          if (dynamic_cast<const CMetab*>(pObject))
                            {
                              pChildNode = static_cast<const CEvaluationNode*>(pChildNode->getSibling());
                              assert(pChildNode);

                              CEvaluationNode::MainType type = pChildNode->mainType();

                              if (type == CEvaluationNode::MainType::NUMBER)
                                {
                                  const CMetab* pMetab = static_cast<const CMetab*>(pObject);

                                  if (multiplicityMap.find(pMetab) != multiplicityMap.end())
                                    {
                                      multiplicityMap[pMetab] = multiplicityMap[pMetab] + *pChildNode->getValuePointer();
                                    }
                                  else
                                    {
                                      multiplicityMap[pMetab] = *pChildNode->getValuePointer();
                                    }
                                }
                              else if (type == CEvaluationNode::MainType::FUNCTION &&
                                       pChildNode->subType() == CEvaluationNode::SubType::MINUS &&
                                       static_cast< const CEvaluationNode * >(pChildNode->getChild())->mainType() == CEvaluationNode::MainType::NUMBER)
                                {
                                  const CMetab* pMetab = static_cast<const CMetab*>(pObject);
                                  multiplicityMap[pMetab] = -1 * *static_cast< const CEvaluationNodeNumber * >(pChildNode->getChild())->getValuePointer();
                                }
                              else
                                {
                                  // not a math action
                                }
                            }
                        }
                      else
                        {
                          result = false;
                          break;
                        }
                    }
                  else
                    {
                      result = false;
                      break;
                    }
                }
              else
                {
                  result = false;
                  break;
                }
            }
        }

      if (numParameters != 1)
        {
          result = false;
        }

      if (result)
        {
          const CDataVector<CChemEqElement>& metabolites = chemicalEquation.getSubstrates();
          size_t i, iMax = metabolites.size();

          // all metabolites must occur in the muliplicityMap so they have to have the same size
          // and a mass action must have at least one metabolite
          if (iMax == 0 || iMax != multiplicityMap.size()) result = false;

          for (i = 0; i < iMax && result; ++i)
            {
              // the metabolite has to be present in the multiplicityMap, otherwise it is not a mass action
              // the stoichiometry also has to fit
              std::map<const CMetab*, C_FLOAT64>::iterator pos = multiplicityMap.find(metabolites[i].getMetabolite());

              if (pos == multiplicityMap.end() ||
                  !areApproximatelyEqual(pos->second, metabolites[i].getMultiplicity(), 0.01))
                {
                  result = false;
                  break;
                }
            }
        }

      if (!result)
        {
          v->clear();
        }
    }

  return v;
}

std::vector<CEvaluationNodeObject*>* SBMLImporter::isMassActionFunction(const CFunction* pFun, const CChemEq& chemicalEquation, const std::vector<std::vector< std::string > >& functionArgumentCNs)
{
  // create an expression from the function and call isMassActionExpression
  CEvaluationTree* pExpressionTree = this->createExpressionFromFunction(pFun, functionArgumentCNs);

  if (!pExpressionTree)
    {
      return NULL;
    }

  std::vector<CEvaluationNodeObject*>* v = this->isMassActionExpression(pExpressionTree->getRoot(), chemicalEquation);

  delete pExpressionTree;
  return v;
}

CEvaluationTree* SBMLImporter::createExpressionFromFunction(const CFunction* pFun, const std::vector<std::vector<std::string > >& functionArgumentCNs)
{
  CEvaluationTree* pTree = NULL;
  const CFunctionParameters& pFunParams = pFun->getVariables();
  std::string str;

  if (pFunParams.size() == functionArgumentCNs.size())
    {
      std::map<std::string, std::string> variable2CNMap;
      size_t i, iMax = pFunParams.size();

      for (i = 0; i < iMax; ++i)
        {
          // vectors should not occur here
          assert(functionArgumentCNs[i].size() == 1);
          variable2CNMap[pFunParams[i]->getObjectName()] = functionArgumentCNs[i][0];
        }

      CEvaluationNode* pTmpNode = this->variables2objects(pFun->getRoot(), variable2CNMap);
      assert(pTmpNode);
      pTree = CEvaluationTree::create(CEvaluationTree::Expression);
      pTree->setRoot(pTmpNode);
    }

  return pTree;
}

void SBMLImporter::separateProductArguments(const CEvaluationNode* pRootNode, std::vector<const CEvaluationNode*>& arguments)
{
  // TODO CRITICAL We need to use a node iterator
  const CEvaluationNodeOperator* pMultiplyNode = dynamic_cast<const CEvaluationNodeOperator*>(pRootNode);

  if (pMultiplyNode && ((pMultiplyNode->subType()) == CEvaluationNode::SubType::MULTIPLY))
    {
      // check if one if the children is an object node or a power operator, if so,
      // add the node to the vector
      // the nodes not one of those two are passed to this function recursively.
      const CEvaluationNode* pChildNode = static_cast<const CEvaluationNode*>(pMultiplyNode->getChild());

      while (pChildNode)
        {
          const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pChildNode);
          const CEvaluationNodeOperator* pOperatorNode = dynamic_cast<const CEvaluationNodeOperator*>(pChildNode);

          if (pObjectNode)
            {
              arguments.push_back(pObjectNode);
            }
          else if (pOperatorNode && ((pOperatorNode->subType()) == CEvaluationNode::SubType::POWER))
            {
              arguments.push_back(pOperatorNode);
            }
          else
            {
              this->separateProductArguments(pChildNode, arguments);

              if (arguments.empty())
                {
                  // it is not a mass action kinetic, so we can stop here
                  break;
                }
            }

          pChildNode = static_cast<const CEvaluationNode*>(pChildNode->getSibling());
        }
    }
  else
    {
      arguments.clear();
    }
}

void SBMLImporter::setCorrectUsage(CReaction* pCopasiReaction, const CEvaluationNodeCall* pCallNode)
{
  // find out what type each argument in the call node has.
  // it can be a local parameter, a global parameter, a compartment or a metabolite
  // if it is a metabolite, try to find out if it is a substrate, product, or modifier
  if (!pCallNode)
    {
      fatalError();
    }

  const CEvaluationNode* pChildNode = static_cast<const CEvaluationNode*>(pCallNode->getChild());

  CChemEq& pChemEq = pCopasiReaction->getChemEq();

  std::map<const CChemEqElement*, CChemEq::MetaboliteRole> v;

  const CDataVector<CChemEqElement>* pV = &pChemEq.getSubstrates();

  size_t i, iMax = pV->size();

  for (i = 0; i < iMax; ++i)
    {
      v[&pV->operator[](i)] = CChemEq::SUBSTRATE;
    }

  pV = &pChemEq.getProducts();
  iMax = pV->size();

  for (i = 0; i < iMax; ++i)
    {
      v[&pV->operator[](i)] = CChemEq::PRODUCT;
    }

  pV = &pChemEq.getModifiers();
  iMax = pV->size();

  for (i = 0; i < iMax; ++i)
    {
      v[&pV->operator[](i)] = CChemEq::MODIFIER;
    }

  size_t parameterIndex = 0;

  while (pChildNode)
    {
      const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pChildNode);

      if (!pObjectNode)
        {
          fatalError();
        }

      const CDataObject* object = CObjectInterface::DataObject(mpCopasiModel->getObjectFromCN(pObjectNode->getData().substr(1, pObjectNode->getData().length() - 2)));

      if (!object)
        {
          fatalError();
        }

      CFunctionParameter* pFunParam = const_cast<CFunctionParameter*>(pCopasiReaction->getFunction()->getVariables()[parameterIndex]);

      if (dynamic_cast<const CDataObjectReference<C_FLOAT64>*>(object))
        {
          object = object->getObjectParent();

          if (dynamic_cast<const CMetab*>(object))
            {
              std::map<const CChemEqElement*, CChemEq::MetaboliteRole>::iterator it = v.begin();
              std::map<const CChemEqElement*, CChemEq::MetaboliteRole>::iterator endIt = v.end();

              while (it != endIt)
                {
                  if (it->first == object)
                    {
                      // get the role of the metabolite
                      switch (it->second)
                        {
                          case CChemEq::SUBSTRATE:
                            // it is a substrate
                            pFunParam->setUsage(CFunctionParameter::Role::SUBSTRATE);
                            break;

                          case CChemEq::PRODUCT:
                            // it is a product
                            pFunParam->setUsage(CFunctionParameter::Role::PRODUCT);
                            break;

                          case CChemEq::MODIFIER:
                            // it is a modifier
                            pFunParam->setUsage(CFunctionParameter::Role::MODIFIER);
                            break;

                          default:
                            fatalError();
                            break;
                        }
                    }

                  ++it;
                }

              if (it == endIt)
                {
                  fatalError();
                }
            }
          else if (dynamic_cast<const CModelValue*>(object))
            {
              // it is a global parameter
              pFunParam->setUsage(CFunctionParameter::Role::PARAMETER);
            }
          else if (dynamic_cast<const CCompartment*>(object))
            {
              // it is a volume
              pFunParam->setUsage(CFunctionParameter::Role::VOLUME);
            }
          else
            {
              fatalError()
            }
        }
      else
        {
          // it is a local parameter
          pFunParam->setUsage(CFunctionParameter::Role::PARAMETER);
        }

      pChildNode = static_cast<const CEvaluationNode*>(pChildNode->getSibling());
      ++parameterIndex;
    }
}

bool containsKey(const CDataVector < CChemEqElement >& list, const std::string& key)
{
  CDataVector < CChemEqElement >::const_iterator it = list.begin();
  CDataVector < CChemEqElement >::const_iterator end = list.end();

  for (; it != end; ++it)
    {
      if (it->getMetaboliteKey() == key)
        {
          return true;
        }
    }

  return false;
}

void SBMLImporter::doMapping(CReaction* pCopasiReaction, const CEvaluationNodeCall* pCallNode)
{
  // map the first argument of the call node to the first variable of the function of the reaction
  // and so on
  if (!pCallNode)
    {
      fatalError();
    }

  if (dynamic_cast<const CMassAction*>(pCopasiReaction->getFunction()))
    {
      const CEvaluationNodeObject* pChild = dynamic_cast<const CEvaluationNodeObject*>(pCallNode->getChild());
      std::string objectCN = pChild->getData();
      objectCN = objectCN.substr(1, objectCN.length() - 2);
      const CDataObject* pObject = CObjectInterface::DataObject(mpCopasiModel->getObjectFromCN(objectCN));

      if (!pObject)
        {
          fatalError();
        }

      if (pObject->hasFlag(CDataObject::Reference))
        {
          pObject = pObject->getObjectParent();
        }

      std::vector< const CDataObject * > Objects(1, pObject);

      pCopasiReaction->setParameterObjects("k1", Objects);
      Objects.clear();

      const CDataVector<CChemEqElement>* metabolites = &pCopasiReaction->getChemEq().getSubstrates();

      size_t i, iMax = metabolites->size();

      size_t j, jMax;

      for (i = 0; i < iMax; ++i)
        for (j = 0, jMax = static_cast<int>(fabs((*metabolites)[i].getMultiplicity())); j < jMax; j++)
          Objects.push_back(metabolites->operator[](i).getMetabolite());

      pCopasiReaction->setParameterObjects("substrate", Objects);
      Objects.clear();

      if (pCopasiReaction->isReversible())
        {
          pChild = dynamic_cast<const CEvaluationNodeObject*>(pChild->getSibling());
          std::string objectCN = pChild->getData();
          objectCN = objectCN.substr(1, objectCN.length() - 2);
          const CDataObject* pObject = CObjectInterface::DataObject(mpCopasiModel->getObjectFromCN(objectCN));

          if (!pObject)
            {
              fatalError();
            }

          if (pObject->hasFlag(CDataObject::Reference))
            {
              pObject = pObject->getObjectParent();
            }

          Objects.push_back(pObject);

          pCopasiReaction->setParameterObjects("k2", Objects);
          Objects.clear();

          const CDataVector<CChemEqElement>* metabolites = &pCopasiReaction->getChemEq().getProducts();

          iMax = metabolites->size();

          for (i = 0; i < iMax; ++i)
            for (j = 0, jMax = static_cast<int>(fabs(metabolites->operator[](i).getMultiplicity())); j < jMax; j++)
              Objects.push_back(metabolites->operator[](i).getMetabolite());

          pCopasiReaction->setParameterObjects("product", Objects);
          Objects.clear();
        }
    }
  else
    {
      const CFunctionParameters & Variables = pCopasiReaction->getFunction()->getVariables();
      size_t i, iMax = Variables.size();
      const CEvaluationNodeObject* pChild = dynamic_cast<const CEvaluationNodeObject*>(pCallNode->getChild());

      for (i = 0; i < iMax; ++i)
        {
          if (!pChild)
            {
              fatalError();
            }

          std::string objectCN = pChild->getData();
          objectCN = objectCN.substr(1, objectCN.length() - 2);
          const CDataObject* pObject = CObjectInterface::DataObject(mpCopasiModel->getObjectFromCN(objectCN));

          if (!pObject)
            {
              fatalError();
            }

          if (pObject->hasFlag(CDataObject::Reference))
            {
              pObject = pObject->getObjectParent();
            }

          std::vector< const CDataObject * > Objects(1, pObject);
          pCopasiReaction->setParameterObjects(i, Objects);
          Objects.clear();

          const CChemEq& eqn = pCopasiReaction->getChemEq();

          bool reversible = eqn.getReversibility();

          // We guess what the role of a variable of newly imported function is:
          if (Variables[i]->getUsage() == CFunctionParameter::Role::VARIABLE)
            {
              CFunctionParameter::Role Role = CFunctionParameter::Role::PARAMETER;

              if (pObject->getObjectType() == "Metabolite")
                {
                  if (containsKey(eqn.getSubstrates(), pObject->getKey()))
                    Role = CFunctionParameter::Role::SUBSTRATE;

                  if (Role == CFunctionParameter::Role::PARAMETER &&
                      containsKey(eqn.getProducts(), pObject->getKey()))
                    {
                      // Fix for Bug 1882: if not reversible, only mark as product if it does
                      // not appear in the list of modifiers
                      if (!reversible && containsKey(eqn.getModifiers(), pObject->getKey()))
                        Role =  CFunctionParameter::Role::MODIFIER;
                      else
                        Role =  CFunctionParameter::Role::PRODUCT;
                    }

                  // It is not a substrate and not a product therefore we must have a modifier
                  if (Role == CFunctionParameter::Role::PARAMETER)
                    {
                      Role = CFunctionParameter::Role::MODIFIER;
                    }
                }
              else if (pObject->getObjectType() == "Model")
                {
                  Role = CFunctionParameter::Role::TIME;
                }
              else if (pObject->getObjectType() == "Compartment")
                {
                  Role = CFunctionParameter::Role::VOLUME;
                }

              const_cast< CFunctionParameter * >(Variables[i])->setUsage(Role);
            }

          pChild = dynamic_cast<const CEvaluationNodeObject*>(pChild->getSibling());
        }
    }
}

bool SBMLImporter::isSimpleFunctionCall(const CEvaluationNode* pRootNode)
{
  // it is a simple function call if it is a CEvaluationNodeCall object and all
  // its arguments are object nodes.
  bool result = true;

  if (dynamic_cast<const CEvaluationNodeCall*>(pRootNode))
    {
      const CEvaluationNode* pChildNode = static_cast<const CEvaluationNode*>(pRootNode->getChild());

      // I guess it must have at least one child to qualify.
      if (!pChildNode)
        {
          result = false;
        }

      while (pChildNode)
        {
          if (!dynamic_cast<const CEvaluationNodeObject*>(pChildNode))
            {
              result = false;
              break;
            }

          pChildNode = static_cast<const CEvaluationNode*>(pChildNode->getSibling());
        }
    }
  else
    {
      result = false;
    }

  return result;
}

bool SBMLImporter::divideByVolume(ASTNode* node, const std::string& compartmentSBMLId)
{
  ASTNode* nodeIt = node;
  bool finished = false;
  bool found = false;
  std::vector<ASTNode*> nodeStack;
  std::vector<int> intStack;

  do
    {

      //check for compartment hit
      if (nodeIt->getType() == AST_NAME && nodeIt->getName() == compartmentSBMLId)
        {
          found = true;
          break;
        }

      //now iterate...
      if ((nodeIt->getType() == AST_TIMES || nodeIt->getType() == AST_DIVIDE) && nodeIt->getNumChildren() > 0)
        {
          //go down in the tree
          nodeStack.push_back(nodeIt);
          intStack.push_back(0);
          nodeIt = nodeIt->getChild(0);
        }
      else
        {
          while (nodeStack.size())
            {
              nodeIt = nodeStack[nodeStack.size() - 1];

              if (nodeIt->getType() == AST_TIMES && (int)nodeIt->getNumChildren() > intStack[intStack.size() - 1] + 1)
                {
                  //go to sibling
                  nodeIt = nodeIt->getChild(intStack[intStack.size() - 1] + 1);
                  intStack[intStack.size() - 1]++;
                  break;
                }
              else
                {
                  //go up in tree
                  nodeStack.pop_back();
                  intStack.pop_back();
                }
            }

          //if we reach the top again we are done (it means we could not go to a sibling)
          if (nodeStack.size() == 0)
            finished = true;
        }
    }
  while (!finished);

  if (!found)
    return false;

  //now we know the location of the node that needs to be removed.

  // for now, ignore the case of the root node
  if (nodeStack.size() == 0)
    return false;

  //that means a parent should exist.
  ASTNode* parentNode = nodeStack.back();

  //the case where the parent is TIMES and has at least 2 children: just remove the node
  //  (accepting that it may result in a multiplication with one child)
  if (parentNode->getType() == AST_TIMES && parentNode->getNumChildren() > 1)
    {
      int childIndex = intStack.back();
      ASTNode* childNode = parentNode->getChild(childIndex);
      parentNode->removeChild(childIndex);
      delete childNode;
      return true;
    }

  //TODO: cases that could be implemented:
  //
  // - TIMES nodes with only one child can be removed
  // - TIMES nodes that had only one child before should be removed (although technically correct?)
  // - Volume node in nominator of DIVIDE node can be replaced by "1"
  // - (Volume node at top level can be replaced by "1", this cannot be implemented within this method)

  return false;
}

CEvaluationNode* SBMLImporter::variables2objects(const CEvaluationNode* pOrigNode, const std::map<std::string, std::string>& replacementMap)
{
  // TODO CRITICAL We need to use a node iterator
  CEvaluationNode* pResultNode = NULL;

  if (dynamic_cast<const CEvaluationNodeVariable*>(pOrigNode))
    {
      std::map<std::string, std::string>::const_iterator pos = replacementMap.find(pOrigNode->getData());

      if (pos == replacementMap.end()) fatalError();

      pResultNode = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pos->second + ">");
    }
  else
    {
      pResultNode = CEvaluationNode::create(pOrigNode->mainType(), pOrigNode->subType(), pOrigNode->getData());
      const CEvaluationNode* pChildNode = static_cast<const CEvaluationNode*>(pOrigNode->getChild());

      while (pChildNode)
        {
          pResultNode->addChild(this->variables2objects(pChildNode, replacementMap));
          pChildNode = static_cast<const CEvaluationNode*>(pChildNode->getSibling());
        }
    }

  return pResultNode;
}

void SBMLImporter::renameMassActionParameters(CEvaluationNodeCall* pCallNode)
{
  CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(pCallNode->getChild());
  assert(pObjectNode);
  CCommonName objectName = CCommonName(pObjectNode->getData().substr(1, pObjectNode->getData().length() - 2));
  CDataObject* pObject = const_cast< CDataObject *>(CObjectInterface::DataObject(mpCopasiModel->getObjectFromCN(objectName)));
  assert(pObject);

  if (dynamic_cast<CCopasiParameter*>(pObject))
    {
      pObject->setObjectName("k1");
      pObjectNode->setData("<" + pObject->getStringCN() + ">");
    }

  pObjectNode = dynamic_cast<CEvaluationNodeObject*>(pObjectNode->getSibling());

  if (pObjectNode)
    {
      objectName = CCommonName(pObjectNode->getData().substr(1, pObjectNode->getData().length() - 2));
      pObject = const_cast< CDataObject *>(CObjectInterface::DataObject(mpCopasiModel->getObjectFromCN(objectName)));
      assert(pObject);

      if (dynamic_cast<CCopasiParameter*>(pObject))
        {
          pObject->setObjectName("k2");
          pObjectNode->setData("<" + pObject->getStringCN() + ">");
        }
    }
}

bool SBMLImporter::containsVolume(const ASTNode* pNode, const std::string& compartmentSBMLId)
{
  bool result = false;
  unsigned int i, iMax = pNode->getNumChildren();

  for (i = 0; i < iMax; ++i)
    {
      if (pNode->getChild(i)->getType() == AST_NAME &&
          pNode->getChild(i)->getName() == compartmentSBMLId)
        {
          result = true;
          break;
        }
    }

  return result;
}

void SBMLImporter::setImportHandler(CProcessReport * pProcessReport)
{
  mpProcessReport = pProcessReport;

#if LIBSBML_VERSION >= 51801

  if (mpSbmlCallback != NULL)
    {
      CallbackRegistry::removeCallback(mpSbmlCallback);
      pdelete(mpSbmlCallback);
    }

  if (mpProcessReport != NULL)
    {
      mpSbmlCallback = new SbmlProgressCallback(mpProcessReport);
      CallbackRegistry::addCallback(mpSbmlCallback);
    }

#endif
}

const CProcessReport * SBMLImporter::getProcessReport() const
{
  return mpProcessReport;
}

void SBMLImporter::clearCallBack()
{
  setImportHandler(NULL);
}

bool SBMLImporter::removeUnusedFunctions(std::map<const CDataObject*, SBase*>& copasi2sbmlmap)
{
  size_t i, iMax = this->mpCopasiModel->getReactions().size();

  std::set<std::string> functionNameSet;

  for (i = 0; i < iMax; ++i)
    {
      const CFunction* pTree = this->mpCopasiModel->getReactions()[i].getFunction();

      // this is a hack, but if we changed stoichiometries in reactions, we can no longer be sure that the
      // kinetic function fits the reaction, so in this case it is probably better to set all functions used
      // in directions to general
      // If we don't do this, the user will not be able to use the function in the reaction in the GUI if he
      // changed it once.
      // TODO only set those functions to general that really contain modified stoichiometries
      if (this->mConversionFactorFound)
        {
          // TODO another const_cast that should disappear
          // TODO because there is probably a better place to do this
          // TODO but this means rewriting the code that modifies the
          // TODO stoichiometries of reactions and put it all in one place.
          const_cast<CFunction*>(pTree)->setReversible(TriUnspecified);
        }

      if (functionNameSet.find(pTree->getObjectName()) == functionNameSet.end())
        {
          functionNameSet.insert(pTree->getObjectName());
          this->findFunctionCalls(pTree->getRoot(), functionNameSet);
        }

      ++mCurrentStepCounter;

      if (reportCurrentProgressOrStop())
        return false;
    }

  iMax = this->mpCopasiModel->getCompartments().size();

  for (i = 0; i < iMax; ++i)
    {
      CModelEntity* pME = &this->mpCopasiModel->getCompartments()[i];

      if (pME->getStatus() != CModelEntity::Status::FIXED)
        {
          const CEvaluationTree* pTree = pME->getExpressionPtr();

          if (pTree != NULL)
            {
              this->findFunctionCalls(pTree->getRoot(), functionNameSet);
            }
        }

      if (pME->getStatus() != CModelEntity::Status::ASSIGNMENT)
        {
          const CEvaluationTree* pTree = pME->getInitialExpressionPtr();

          if (pTree != NULL)
            {
              this->findFunctionCalls(pTree->getRoot(), functionNameSet);
            }
        }

      ++mCurrentStepCounter;
    }

  iMax = this->mpCopasiModel->getMetabolites().size();

  for (i = 0; i < iMax; ++i)
    {
      CModelEntity* pME = &this->mpCopasiModel->getMetabolites()[i];

      if (pME->getStatus() != CModelEntity::Status::FIXED)
        {
          const CEvaluationTree* pTree = pME->getExpressionPtr();

          if (pTree != NULL)
            {
              this->findFunctionCalls(pTree->getRoot(), functionNameSet);
            }
        }

      if (pME->getStatus() != CModelEntity::Status::ASSIGNMENT)
        {
          const CEvaluationTree* pTree = pME->getInitialExpressionPtr();

          if (pTree != NULL)
            {
              this->findFunctionCalls(pTree->getRoot(), functionNameSet);
            }
        }

      ++mCurrentStepCounter;
    }

  iMax = this->mpCopasiModel->getModelValues().size();

  for (i = 0; i < iMax; ++i)
    {
      CModelEntity* pME = &this->mpCopasiModel->getModelValues()[i];

      if (pME->getStatus() != CModelEntity::Status::FIXED)
        {
          const CEvaluationTree* pTree = pME->getExpressionPtr();

          if (pTree != NULL)
            {
              this->findFunctionCalls(pTree->getRoot(), functionNameSet);
            }
        }

      if (pME->getStatus() != CModelEntity::Status::ASSIGNMENT)
        {
          const CEvaluationTree* pTree = pME->getInitialExpressionPtr();

          if (pTree != NULL)
            {
              this->findFunctionCalls(pTree->getRoot(), functionNameSet);
            }
        }

      ++mCurrentStepCounter;
    }

  // find the used function in events
  iMax = this->mpCopasiModel->getEvents().size();

  for (i = 0; i < iMax; ++i)
    {
      CEvent* pEvent = &this->mpCopasiModel->getEvents()[i];
      assert(pEvent != NULL);
      const CEvaluationTree* pTree = pEvent->getTriggerExpressionPtr();
      // an event has to have a trigger
      assert(pTree != NULL);

      if (pTree != NULL)
        {
          this->findFunctionCalls(pTree->getRoot(), functionNameSet);
        }

      // handle the delay
      pTree = pEvent->getDelayExpressionPtr();

      if (pTree != NULL)
        {
          this->findFunctionCalls(pTree->getRoot(), functionNameSet);
        }

      // handle all assignments
      size_t j, jMax = pEvent->getAssignments().size();

      for (j = 0; j < jMax; ++j)
        {
          CEventAssignment* pEventAssignment = &pEvent->getAssignments()[j];
          assert(pEventAssignment != NULL);

          if (pEventAssignment != NULL)
            {
              pTree = pEventAssignment->getExpressionPtr();
              // each event assignment has to have an expression
              assert(pTree != NULL);

              if (pTree != NULL)
                {
                  this->findFunctionCalls(pTree->getRoot(), functionNameSet);
                }
            }
        }
    }

  CRootContainer::getFunctionList();

  if (createProgressStepOrStop(15,
                               (unsigned C_INT32) mCreatedFunctions.size(),
                               "Removing unused functions..."
                              ))
    return false;

  // here we could have a dialog asking the user if unused functions should
  // be removed.

  std::set< std::string >::const_iterator it = mCreatedFunctions.begin();
  std::set< std::string >::const_iterator end = mCreatedFunctions.end();

  for (; it != end; ++it)
    {
      if (functionNameSet.find(*it) == functionNameSet.end())
        {
          CFunction & Function = CRootContainer::getFunctionList()->loadedFunctions()[*it];

          // delete the entry from the copasi2sbmlmap.
          std::map<const CDataObject*, SBase*>::iterator pos = copasi2sbmlmap.find(&Function);
          assert(pos != copasi2sbmlmap.end());
          copasi2sbmlmap.erase(pos);

          CRootContainer::getFunctionList()->loadedFunctions().remove(*it);
        }

      ++mCurrentStepCounter;

      if (reportCurrentProgressOrStop())
        return false;
    }

  finishCurrentStep();

  return true;
}

void SBMLImporter::findFunctionCalls(const CEvaluationNode* pNode, std::set<std::string>& functionNameSet)
{
  if (pNode)
    {
      CFunctionDB* pFunctionDB = CRootContainer::getFunctionList();
      CCopasiTree<const CEvaluationNode>::iterator treeIt = pNode;

      while (treeIt != NULL)
        {
          if (treeIt->mainType() == CEvaluationNode::MainType::CALL)
            {
              // unQuote not necessary since getIndex in CDataVector takes care of this.
              CEvaluationTree* pTree = pFunctionDB->findFunction((*treeIt).getData());

              if (functionNameSet.find(pTree->getObjectName()) == functionNameSet.end())
                {
                  functionNameSet.insert(pTree->getObjectName());
                  this->findFunctionCalls(pTree->getRoot(), functionNameSet);
                }
            }

          ++treeIt;
        }
    }
}

bool SBMLImporter::isStochasticModel(const Model* pSBMLModel)
{
  bool stochastic = false;
  unsigned int i;
  const UnitDefinition* pUD = pSBMLModel->getUnitDefinition("substance");

  if (pUD)
    {
      stochastic = (pUD->getNumUnits() == 1 &&
                    pUD->getUnit(0)->getKind() == UNIT_KIND_ITEM);

      for (i = 0; (stochastic == true) && (i < pSBMLModel->getNumReactions()); ++i)
        {
          stochastic = !pSBMLModel->getReaction(i)->getReversible();
        }
    }

  return stochastic;
}

void SBMLImporter::importSBMLRule(const Rule* sbmlRule, std::map<const CDataObject*, SBase*>& copasi2sbmlmap, Model* pSBMLModel)
{
  // so far we only support assignment rules and rate rules
  int type = sbmlRule->getTypeCode();

  if (type == SBML_ASSIGNMENT_RULE)
    {
      const AssignmentRule* pAssignmentRule = dynamic_cast<const AssignmentRule*>(sbmlRule);

      if (pAssignmentRule && pAssignmentRule->isSetVariable())
        {
          this->importRule(pAssignmentRule, CModelEntity::Status::ASSIGNMENT, copasi2sbmlmap, pSBMLModel);
        }
      else
        {
          fatalError();
        }
    }
  else if (type == SBML_RATE_RULE)
    {
      const RateRule* pRateRule = dynamic_cast<const RateRule*>(sbmlRule);

      if (pRateRule && pRateRule->isSetVariable())
        {
          this->importRule(pRateRule, CModelEntity::Status::ODE, copasi2sbmlmap, pSBMLModel);
        }
      else
        {
          fatalError();
        }
    }
  else
    {
      this->mUnsupportedRuleFound = true;
    }
}

void SBMLImporter::importRule(const Rule* rule, CModelEntity::Status ruleType, std::map<const CDataObject*, SBase*>& copasi2sbmlmap, Model* pSBMLModel)
{
  std::string sbmlId;
  const AssignmentRule* pARule = dynamic_cast<const AssignmentRule*>(rule);

  if (pARule)
    {
      sbmlId = pARule->getVariable();
    }
  else
    {
      const RateRule* pRRule = dynamic_cast<const RateRule*>(rule);

      if (pRRule)
        {
          sbmlId = pRRule->getVariable();
        }
      else
        {
          // should never happen
          fatalError();
        }
    }

  // if the id occurs in mSBMLSpeciesReferenceIds, we have an assignment to a species reference which is not supported
  if (this->mLevel > 2 && this->mSBMLSpeciesReferenceIds.find(sbmlId) != this->mSBMLSpeciesReferenceIds.end())
    {
      // we can't import rate rules on species references
      if (pARule == NULL)
        {
          this->mRateRuleForSpeciesReferenceIgnored = true;
          return;
        }

      // starting with sbml level 3 this could actually be an initial assignment to
      // a species reference which we can't store in COPASI
      // So we treat this the same way as the stoichiometryMath in SBML level 2

      // find the chemical equation element
      std::map<const CDataObject*, SBase*>::const_iterator it = copasi2sbmlmap.begin(), endit = copasi2sbmlmap.end();

      while (it != endit)
        {
          if (it->second->getId() == sbmlId)
            {
              break;
            }

          ++it;
        }

      assert(it != endit);
      const CChemEqElement* pChemEqElement = dynamic_cast<const CChemEqElement*>(it->first);

      if (this->mLevel > 2 &&  pChemEqElement != NULL && rule->getMath() != NULL)
        {
          // store the expression for the stoichiometry in the stoichiometric expression map
          // this has been tested and should work
          this->mStoichiometricExpressionMap.insert(std::make_pair(rule->getMath(), pChemEqElement));
          // issue a warning that stoichiometries that change over time are not supported
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 101, sbmlId.c_str());

          return;
        }
    }

  // find out to what kind of object the id belongs
  SBMLTypeCode_t type = SBML_UNKNOWN;
  bool found = false;
  Compartment* pC;
  Species* pS;
  Parameter* pP;
  const CDataObject* pObject = NULL;
  std::map<const CDataObject*, SBase*>::iterator it = copasi2sbmlmap.begin();
  std::map<const CDataObject*, SBase*>::iterator endit = copasi2sbmlmap.end();

  while (it != endit)
    {
      switch (it->second->getTypeCode())
        {
          case SBML_COMPARTMENT:
            pC = dynamic_cast<Compartment*>(it->second);

            if (pC->getId() == sbmlId)
              {
                // On import we convert L1 files to L2V1 files to simplify things.
                // This means that suddenly all parameters are set to constant by libsbml
                // since the constant flag did not exist prior to L2
                // If we find a rule on a constant object, this is only an error
                // if the file is not a level 1 file
                if (this->mOriginalLevel > 1 && pC->getConstant())
                  {
                    if (ruleType == CModelEntity::Status::ASSIGNMENT)
                      {
                        CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 34, "AssignmentRule", "Compartment", sbmlId.c_str());
                      }
                    else if (ruleType == CModelEntity::Status::ODE)
                      {
                        CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 34, "RateRule", "Compartment", sbmlId.c_str());
                      }
                    else
                      {
                        // should never happen
                        fatalError();
                      }
                  }

                type = SBML_COMPARTMENT;
                pObject = it->first;
                found = true;
              }

            break;

          case SBML_SPECIES:
            pS = dynamic_cast<Species*>(it->second);

            if (pS->getId() == sbmlId)
              {
                // make sure the species is not declared constant
                // On import we convert L1 files to L2V1 files to simplify things.
                // This means that suddenly all parameters are set to constant by libsbml
                // since the constant flag did not exist prior to L2
                // If we find a rule on a constant object, this is only an error
                // if the file is not a level 1 file
                if (this->mOriginalLevel > 1 && pS->getConstant())
                  {
                    if (ruleType == CModelEntity::Status::ASSIGNMENT)
                      {
                        CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 34, "AssignmentRule", "Species", sbmlId.c_str());
                      }
                    else if (ruleType == CModelEntity::Status::ODE)
                      {
                        CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 34, "RateRule", "Species", sbmlId.c_str());
                      }
                    else
                      {
                        // should never happen
                        fatalError();
                      }
                  }

                type = SBML_SPECIES;
                pObject = it->first;
                found = true;
              }

            break;

          case SBML_PARAMETER:
            pP = dynamic_cast<Parameter*>(it->second);

            if (pP->getId() == sbmlId)
              {
                // make sure the parameter is not declared constant
                // On import we convert L1 files to L2V1 files to simplify things.
                // This means that suddenly all parameters are set to constant by libsbml
                // since the constant flag did not exist prior to L2
                // If we find a rule on a constant object, this is only an error
                // if the file is not a level 1 file
                if (this->mOriginalLevel > 1 && pP->getConstant())

                  {
                    if (ruleType == CModelEntity::Status::ASSIGNMENT)
                      {
                        CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 34, "AssignmentRule", "Parameter", sbmlId.c_str());
                      }
                    else if (ruleType == CModelEntity::Status::ODE)
                      {
                        CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 34, "RateRule", "Parameter", sbmlId.c_str());
                      }
                    else
                      {
                        // should never happen
                        fatalError();
                      }
                  }

                type = SBML_PARAMETER;
                pObject = it->first;
                found = true;
              }

            break;

          default:
            break;
        }

      if (found) break;

      ++it;
    }

  if (found)
    {
      const CModelEntity* pME;

      switch (type)
        {
          case SBML_PARAMETER:
          case SBML_SPECIES:
          case SBML_COMPARTMENT:
            // check if it really is a global parameter, a metabolite or a
            // compartment
            pME = dynamic_cast<const CModelValue*>(pObject);

            // activate the next two lines if rules for compartments and
            // metabolites should be imported.
            if (!pME) pME = dynamic_cast<const CCompartment*>(pObject);

            if (!pME) pME = dynamic_cast<const CMetab*>(pObject);

            if (!pME)
              {
                if (ruleType == CModelEntity::Status::ASSIGNMENT)
                  {
                    CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 33, "AssigmentRule", sbmlId.c_str());
                  }
                else if (ruleType == CModelEntity::Status::ODE)
                  {
                    CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 33, "RateRule", sbmlId.c_str());
                  }
                else
                  {
                    // should never happen
                    fatalError();
                  }
              }

            this->importRuleForModelEntity(rule, pME, ruleType, copasi2sbmlmap, pSBMLModel);
            break;

          default:
            // now that compartments, metabolites and global parameters are
            // supported, everything else should produce a fatal error.
            fatalError();
            break;
        }
    }
  else
    {
      // issue a warning
      if (ruleType == CModelEntity::Status::ASSIGNMENT)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 32, "AssignmentRule", sbmlId.c_str());
        }
      else if (ruleType == CModelEntity::Status::ODE)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 32, "RateRule", sbmlId.c_str());
        }
      else
        {
          // should never happen
          fatalError();
        }
    }
}

void SBMLImporter::areRulesUnique(const Model* sbmlModel)
{
  std::set<std::string> idSet;

  // go through the rules and check that no id is used in more than one rule
  unsigned int i, iMax = sbmlModel->getNumRules();

  for (i = 0; i < iMax; ++i)
    {
      const Rule* pRule = sbmlModel->getRule(i);
      std::string id;

      switch (pRule->getTypeCode())
        {
          case SBML_ASSIGNMENT_RULE:
            id = dynamic_cast<const AssignmentRule*>(pRule)->getVariable();
            break;

          case SBML_RATE_RULE:
            id = dynamic_cast<const RateRule*>(pRule)->getVariable();
            break;

          default:
            break;
        }

      if (!id.empty())
        {
          if (!idSet.insert(id).second)
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 35, id.c_str());
              break;
            }
        }
    }
}

void SBMLImporter::importRuleForModelEntity(const Rule* rule, const CModelEntity* pME, CModelEntity::Status status, std::map<const CDataObject*, SBase*>& copasi2sbmlmap, Model* pSBMLModel)
{
  CModelEntity * pModelEntity = const_cast< CModelEntity * >(pME);

  if (!rule->isSetMath())
    {
      std::map<const CDataObject*, SBase*>::const_iterator pos = copasi2sbmlmap.find(pModelEntity);
      assert(pos != copasi2sbmlmap.end());
      std::string id = "@";

      if (pos != copasi2sbmlmap.end())
        {
          id = pos->second->getId();
        }

      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 58, "rule", id.c_str());
      return;
    }

  // check for references to species references in the expression because we don't support them yet
  if (!SBMLImporter::findIdInASTTree(rule->getMath(), this->mSBMLSpeciesReferenceIds).empty())
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 95);
    }

  if (rule->getTypeCode() == SBML_ASSIGNMENT_RULE)
    {
      this->checkRuleMathConsistency(rule, copasi2sbmlmap);
    }

  ConverterASTNode tmpNode(*rule->getMath());
  // replace all the nodes that represent species with the
  // hasOnlySubstanceUnits flag set with the node multiplied by the volume
  //replaceSubstanceOnlySpeciesNodes(&tmpNode, mSubstanceOnlySpecies);

  this->preprocessNode(&tmpNode, pSBMLModel, copasi2sbmlmap);
  // replace the object names
  this->replaceObjectNames(&tmpNode, copasi2sbmlmap);
  // now we convert the node to a CEvaluationNode
  CExpression* pExpression = new CExpression;
  pExpression->setTree(tmpNode, false);

  if (dynamic_cast<CMetab*>(pModelEntity) != NULL)
    {
      std::map<const CDataObject*, SBase*>::iterator pos = copasi2sbmlmap.find(pModelEntity);
      assert(pos != copasi2sbmlmap.end());
      Species* pSBMLSpecies = dynamic_cast<Species*>(pos->second);
      assert(pSBMLSpecies != NULL);
      // check if the compartment is fixed
      const CCompartment* pCompartment = static_cast<CMetab*>(pModelEntity)->getCompartment();
      assert(pCompartment != NULL);

      if (pSBMLSpecies->getHasOnlySubstanceUnits() == true || pCompartment->getDimensionality() == 0)
        {

          CEvaluationNode* pOrigNode = pExpression->getRoot();
          assert(pOrigNode != NULL);
          CEvaluationNode* pNode = SBMLImporter::divideByObject(pOrigNode, pCompartment->getValueReference());
          assert(pNode != NULL);

          if (pNode != NULL)
            {
              pExpression->setRoot(pNode);
            }
          else
            {
              fatalError();
            }
        }

      if (pCompartment->getStatus() != CModelEntity::Status::FIXED && pModelEntity->getStatus() == CModelEntity::Status::ODE)
        {
          // if it is an assignment rule we do nothing, if it is an ode rule,
          // we need to issue a warning or an error
          CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 51, pSBMLSpecies->getId().c_str());
        }
    }

  pModelEntity->setStatus(status);

  bool result = pModelEntity->setExpressionPtr(pExpression);

  if (result == false)
    {
      if (pModelEntity->getExpressionPtr() != pExpression)
        {
          delete pExpression;
        }

      pModelEntity->setStatus(CModelEntity::Status::FIXED);
      std::string m = "Some error occurred while importing the rule for object with id \"" + rule->getVariable() + "\".";
      CCopasiMessage(CCopasiMessage::RAW, m.c_str());
    }
}

void SBMLImporter::setDataModel(CDataModel * pDM)
{
  mpDataModel = pDM;
  mpCopasiModel = pDM->getModel();
}

void SBMLImporter::checkRuleMathConsistency(const Rule* pRule, std::map<const CDataObject*, SBase*>& copasi2sbmlmap)
{
  // only check if Level2 Version1
  if (this->mLevel == 2 && this->mVersion == 1)
    {
      // check if no nodes with ids of objects are used in an assignment that are
      // set in another assignment rule later on
      std::set<std::string> idSet;
      const ASTNode* pNode = pRule->getMath();
      this->getIdsFromNode(pNode, idSet);
      Model* sbmlModel = dynamic_cast<Model*>(copasi2sbmlmap[mpCopasiModel]);

      if (!sbmlModel) fatalError();

      unsigned int i, iMax = sbmlModel->getNumRules();

      for (i = 0; i < iMax; ++i)
        {
          if (sbmlModel->getRule(i) == pRule)
            {
              break;
            }
        }

      Rule* pR;
      int type;

      while (i < iMax)
        {
          pR = sbmlModel->getRule(i);
          type = pR->getTypeCode();

          if (type == SBML_ASSIGNMENT_RULE)
            {
              if (idSet.find(dynamic_cast<AssignmentRule*>(pR)->getVariable()) != idSet.end())
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 37, dynamic_cast<AssignmentRule*>(pR)->getVariable().c_str());
                }
            }

          ++i;
        }

      // Check if there is a reference to a reaction in the expression
      // This is not allowed for L2V1
      const ASTNode* pMath = pRule->getMath();

      if (pMath != NULL)
        {

          std::string id = SBMLImporter::findIdInASTTree(pMath, mReactions);

          if (!id.empty())
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 81, id.c_str());
            }
        }
    }

  // In SBML Level 3 documents,
  if (this->mLevel == 3)
    {
      // TODO we need to check if we have a species reference as the target of
      // TODO a rule because COPASI currently can not handle this and we have
      // TODO to warn the user that we will ignore the rule
      //
      // TODO Likewise we have to check if the id of a species reference is reference in the
      // TODO expression of the rule because this is also not implemented in COPASI yet and
      // TODO we ignore the rule
    }
}

/**
 * This method takes an AST node and a set of ids and returns the first id
 * from the set it finds in the AST tree.
 * This is e.g. used to check if expression in L2V1 contain references to reaction ids.
 */
std::string SBMLImporter::findIdInASTTree(const ASTNode* pASTNode, const std::map<std::string, double>& reactionIds)
{
  std::string id;
  CNodeIterator< const ASTNode > itNode(pASTNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      if (itNode->getType() == AST_NAME)
        {
          if (reactionIds.find(itNode->getName()) != reactionIds.end())
            {
              id = itNode->getName();
              break;
            }
        }
    }

  return id;
}
std::string SBMLImporter::findIdInASTTree(const ASTNode* pASTNode, const std::set<std::string>& reactionIds)
{
  std::string id;
  CNodeIterator< const ASTNode > itNode(pASTNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      if (itNode->getType() == AST_NAME)
        {
          if (reactionIds.find(itNode->getName()) != reactionIds.end())
            {
              id = itNode->getName();
              break;
            }
        }
    }

  return id;
}

void SBMLImporter::getIdsFromNode(const ASTNode* pASTNode, std::set<std::string>& idSet)
{
  CNodeIterator< const ASTNode > itNode(pASTNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      if (itNode->getType() == AST_NAME)
        {
          idSet.insert(itNode->getName());
        }
    }
}

void SBMLImporter::replaceObjectNames(ASTNode* pNode, const std::map<const CDataObject*, SBase*>& copasi2sbmlmap, bool initialExpression)
{
  CNodeIterator< ASTNode > itNode(pNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode != NULL)
        {
          if (itNode->getType() == AST_NAME)
            {
              std::string name = itNode->getName();
              bool haveData = itNode->getUserData() != NULL;
              // the id can either belong to a compartment, a species, a reaction or a
              // global parameter
              std::map<const CDataObject*, SBase*>::const_iterator it = copasi2sbmlmap.begin();
              std::map<const CDataObject*, SBase*>::const_iterator endit = copasi2sbmlmap.end();
              const CReaction* pReaction;
              const CModelEntity* pModelEntity;

              std::map<std::string, std::string>::const_iterator knownit = mKnownInitalValues.find(name);

              if (knownit != mKnownInitalValues.end())
                {
                  itNode->setName(knownit->second.c_str());
                  continue;
                }

              std::map<std::string, double>::const_iterator speciesReference = mSBMLSpeciesReferenceIds.find(name);

              if (speciesReference  != mSBMLSpeciesReferenceIds.end())
                {
                  // replace the name with the value
                  itNode->setType(AST_REAL);
                  itNode->setValue(speciesReference->second);
                  continue;
                }

              while (it != endit)
                {
                  const CDataObject* pObject = it->first;
                  pReaction = dynamic_cast<const CReaction*>(pObject);
                  pModelEntity = dynamic_cast<const CModelEntity*>(pObject);
                  Species* pSpecies = dynamic_cast<Species*>(it->second);
                  bool hasOnlySubstance = pSpecies && mSubstanceOnlySpecies.find(pSpecies) != mSubstanceOnlySpecies.end();
                  std::string sbmlId;
                  haveData = haveData || itNode->getUserData() != NULL;

                  if (pReaction)
                    {
                      sbmlId = pReaction->getSBMLId();
                    }
                  else if (pModelEntity)
                    {
                      sbmlId = pModelEntity->getSBMLId();
                    }

                  if (!sbmlId.empty() && sbmlId == name)
                    {
                      if (haveData)
                        {
                          if (hasOnlySubstance)
                            itNode->setName((pObject->getStringCN() + ",Reference=ParticleNumberRate").c_str());
                          else
                            itNode->setName((pObject->getStringCN() + ",Reference=Rate").c_str());

                          break;
                        }

                      // make sure it is only one of the allowed types
                      switch (it->second->getTypeCode())
                        {
                          case SBML_COMPARTMENT:
                            if (!initialExpression)
                              {
                                itNode->setName((pObject->getStringCN() + ",Reference=Volume").c_str());
                              }
                            else
                              {
                                itNode->setName((pObject->getStringCN() + ",Reference=InitialVolume").c_str());
                              }

                            break;

                          case SBML_SPECIES:
                            // !!!! Check if this is always correct. Maybe if
                            // hasOnlySubstanceUnits is set we have to use the amount
                            // instead. !!!!
                            assert(pSpecies != NULL);

                            if (!hasOnlySubstance)
                              {
                                if (!initialExpression)
                                  {
                                    itNode->setName((pObject->getStringCN() + ",Reference=Concentration").c_str());
                                  }
                                else
                                  {
                                    itNode->setName((pObject->getStringCN() + ",Reference=InitialConcentration").c_str());
                                  }
                              }
                            else
                              {
                                if (!initialExpression)
                                  {
                                    itNode->setName((pObject->getStringCN() + ",Reference=ParticleNumber").c_str());
                                  }
                                else
                                  {
                                    itNode->setName((pObject->getStringCN() + ",Reference=InitialParticleNumber").c_str());
                                  }
                              }

                            break;

                          case SBML_REACTION:

                            if (((const Reaction*)it->second)->getKineticLaw() == NULL)
                              {
                                CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 80, sbmlId.c_str());
                              }

                            itNode->setName((pObject->getStringCN() + ",Reference=Flux").c_str());
                            break;

                          case SBML_PARAMETER:

                            if (!initialExpression)
                              {
                                itNode->setName((pObject->getStringCN() + ",Reference=Value").c_str());
                              }
                            else
                              {
                                itNode->setName((pObject->getStringCN() + ",Reference=InitialValue").c_str());
                              }

                            break;

                          default:
                            fatalError();
                            break;
                        }

                      break;
                    }

                  ++it;
                }

              // not found
              if (it == endit)
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 74, name.c_str());
                }
            }
        }
    }
}

/**
 * For function definitions that use the time symbol we have to make this a
 * variable that is passed to the function instead.
 * The function recursively goes through the AST tree rooted in root and
 * changes all time nodes to variable nodes with name newNodeName.
 * Additionally all function calls to functions in mExplicitelyTimeDependentFunctionDefinitions
 * have to be changed to contain the added parameter.
 * If a time node has been found, the function returns true, otherwise false
 * is returned.
 */
bool SBMLImporter::replaceTimeNodesInFunctionDefinition(ASTNode* pASTNode, std::string newNodeName)
{
  bool timeFound = false;
  CNodeIterator< ASTNode > itNode(pASTNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      if (itNode->getType() == AST_NAME_TIME)
        {
          timeFound = true;
          itNode->setType(AST_NAME);
          itNode->setName(newNodeName.c_str());
        }
      else
        {
          if (itNode->getType() == AST_FUNCTION &&
              mExplicitelyTimeDependentFunctionDefinitions.find(itNode->getName()) != mExplicitelyTimeDependentFunctionDefinitions.end())
            {
              // add a new child to this child node
              ASTNode* pParameterNode = new ASTNode(AST_NAME);
              pParameterNode->setName(newNodeName.c_str());
              itNode->addChild(pParameterNode);
              timeFound = timeFound || true;
            }
        }
    }

  return timeFound;
}

void SBMLImporter::replaceTimeDependentFunctionCalls(ASTNode* pASTNode)
{
  CNodeIterator< ASTNode > itNode(pASTNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      if (itNode->getType() == AST_FUNCTION &&
          mExplicitelyTimeDependentFunctionDefinitions.find(itNode->getName()) != mExplicitelyTimeDependentFunctionDefinitions.end())
        {
          // add a new child to this child node
          ASTNode* pTimeNode = new ASTNode(AST_NAME_TIME);
          pTimeNode->setName("TIME");
          itNode->addChild(pTimeNode);
        }
    }
}

bool SBMLImporter::setInitialValues(CModel* pModel, const std::map<const CDataObject*, SBase*>& copasi2sbmlmap)
{
  // go through the CDataModel and set the initial values on all
  // compartments, metabolites and model values if they were given in the sbml
  // model.
  // if no initial value was given for an entity, check if the value is set
  // by another means (rule, initialAssignment) and if not, create an error
  // message
  std::map<const CDataObject*, SBase*>::const_iterator pos;
  mChangedObjects.clear();
  CDataVectorNS<CCompartment>::iterator compartmentIt = pModel->getCompartments().begin();
  CDataVectorNS<CCompartment>::iterator compartmentEndit = pModel->getCompartments().end();

  while (compartmentIt != compartmentEndit)
    {
      // We cannot change the initial value if we have an assignment rule
      // or an initial expression.
      if (compartmentIt->getStatus() == CModelEntity::Status::ASSIGNMENT ||
          !compartmentIt->getInitialExpression().empty())
        {
          ++compartmentIt;
          continue;
        }

      pos = copasi2sbmlmap.find(compartmentIt);
      assert(pos != copasi2sbmlmap.end());
      Compartment* pSBMLCompartment = dynamic_cast<Compartment*>(pos->second);
      assert(pSBMLCompartment != NULL);

      // for level 1 models we have to use isSetVolume to determine if the
      // volume has been set since in level 1, compartments had different
      // defaults
      if ((this->mLevel == 1 && pSBMLCompartment->isSetVolume()) ||
          pSBMLCompartment->isSetSize())
        {
          // set the initial value
          // here we can safely use getSize() regardless of the level of the
          // sbml model
          compartmentIt->setInitialValue(pSBMLCompartment->getSize());
          mChangedObjects.insert(compartmentIt->getInitialValueReference());
        }
      else
        {
          // if the entity has a status of FIXED or ODE,
          // check if there is an initial assignment, else it is an
          // error
          if ((compartmentIt->getStatus() == CModelEntity::Status::FIXED ||
               compartmentIt->getStatus() == CModelEntity::Status::ODE) &&
              compartmentIt->getInitialExpressionPtr() == NULL)
            {
              this->mIncompleteModel = true;
              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 45, pSBMLCompartment->getId().c_str());

              compartmentIt->setInitialValue(1.0);
              mChangedObjects.insert(compartmentIt->getInitialValueReference());
            }
        }

      ++compartmentIt;
    }

  CDataVectorNS<CMetab>::iterator metabIt = pModel->getMetabolites().begin();
  CDataVectorNS<CMetab>::iterator metabEndit = pModel->getMetabolites().end();

  while (metabIt != metabEndit)
    {
      // We cannot change the initial value if we have an assignment rule
      // or an initial expression.
      if (metabIt->getStatus() == CModelEntity::Status::ASSIGNMENT ||
          !metabIt->getInitialExpression().empty())
        {
          ++metabIt;
          continue;
        }

      pos = copasi2sbmlmap.find(metabIt);
      assert(pos != copasi2sbmlmap.end());
      Species* pSBMLSpecies = dynamic_cast<Species*>(pos->second);
      assert(pSBMLSpecies != NULL);

      // check if the initial concentration or the initial amount has been set
      if (pSBMLSpecies->isSetInitialConcentration())
        {
          if (pSBMLSpecies->getHasOnlySubstanceUnits() == true)
            {
              CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 20, pSBMLSpecies->getId().c_str());
            }

          // set the initial value
          // here we can safely use getSize() regardless of the level of the
          // sbml model
          metabIt->setInitialConcentration(pSBMLSpecies->getInitialConcentration());
          mChangedObjects.insert(metabIt->getInitialConcentrationReference());
        }
      else if (pSBMLSpecies->isSetInitialAmount())
        {
          metabIt->setInitialValue(pSBMLSpecies->getInitialAmount()*pModel->getQuantity2NumberFactor()); // CHECK UNITS !!!
          mChangedObjects.insert(metabIt->getInitialValueReference());
        }
      else
        {
          // if the entity has a status of FIXED, REACTION or ODE,
          // check if there is an initial assignment, else it is an
          // error
          if ((metabIt->getStatus() == CModelEntity::Status::FIXED ||
               metabIt->getStatus() == CModelEntity::Status::REACTIONS ||
               metabIt->getStatus() == CModelEntity::Status::ODE) &&
              metabIt->getInitialExpressionPtr() == NULL)
            {
              this->mIncompleteModel = true;
              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 41, pSBMLSpecies->getId().c_str());

              metabIt->setInitialConcentration(1.0);
              mChangedObjects.insert(metabIt->getInitialConcentrationReference());
            }
        }

      ++metabIt;
    }

  CDataVectorN<CModelValue>::iterator mvIt = pModel->getModelValues().begin();
  CDataVectorN<CModelValue>::iterator mvEndit = pModel->getModelValues().end();

  while (mvIt != mvEndit)
    {
      // We cannot change the initial value if we have an assignment rule
      // or an initial expression.
      if (mvIt->getStatus() == CModelEntity::Status::ASSIGNMENT ||
          !mvIt->getInitialExpression().empty())
        {
          ++mvIt;
          continue;
        }

      pos = copasi2sbmlmap.find(mvIt);
      assert(pos != copasi2sbmlmap.end());
      Parameter* pSBMLParameter = dynamic_cast<Parameter*>(pos->second);
      assert(pSBMLParameter != NULL);

      // check if the initial concentration or the initial amount has been set
      if (pSBMLParameter->isSetValue())
        {
          // set the initial value
          // here we can safely use getSize() regardless of the level of the
          // sbml model
          mvIt->setInitialValue(pSBMLParameter->getValue());
          mChangedObjects.insert(mvIt->getInitialValueReference());
        }
      else
        {
          // if the entity has a status of FIXED or ODE,
          // check if there is an initial assignment, else it is an
          // error
          if ((mvIt->getStatus() == CModelEntity::Status::FIXED ||
               mvIt->getStatus() == CModelEntity::Status::ODE) &&
              mvIt->getInitialExpressionPtr() == NULL)
            {
              this->mIncompleteModel = true;
              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 43, pSBMLParameter->getId().c_str());

              mvIt->setInitialValue(1.0);
              mChangedObjects.insert(mvIt->getInitialValueReference());
            }
        }

      ++mvIt;
    }

  //CDataVectorNS < CReaction >::iterator reactIt = pModel->getReactions().begin();
  //CDataVectorNS < CReaction >::iterator reactEndit = pModel->getReactions().end();

  //while (reactIt != reactEndit)
  //  {
  //    const std::vector<std::vector<std::string> >& parameterMappings = (*reactIt)->getParameterMappings();
  //    std::vector<std::vector<std::string> >::const_iterator parameterMappingsIt = parameterMappings.begin();
  //    std::vector<std::vector<std::string> >::const_iterator parameterMappingsEndit = parameterMappings.end();
  //    CCopasiParameter* pLocalParameter = NULL;

  //    while (parameterMappingsIt != parameterMappingsEndit)
  //      {
  //        std::vector<std::string>::const_iterator keyIt = (*parameterMappingsIt).begin();
  //        std::vector<std::string>::const_iterator keyEndit = (*parameterMappingsIt).end();

  //        while (keyIt != keyEndit)
  //          {
  //            pLocalParameter = dynamic_cast<CCopasiParameter*>(CRootContainer::getKeyFactory()->get(*keyIt));

  //            if (pLocalParameter != NULL)
  //              {
  //                // it is a local parameter and it is being used
  //                mChangedObjects.insert(pLocalParameter->getValueReference());
  //}

  //            ++keyIt;
  //}

  //        ++parameterMappingsIt;
  //}

  //    ++reactIt;
  //}

  // The Avogadro Constant and the quantity conversion factor may have changed and all expressions depending on it must be updated;
  mChangedObjects.insert(CObjectInterface::DataObject(pModel->getObject(std::string("Reference=Avogadro Constant"))));
  mChangedObjects.insert(CObjectInterface::DataObject(pModel->getObject(std::string("Reference=Quantity Conversion Factor"))));

  pModel->updateInitialValues(mChangedObjects);

  return true;
}

void SBMLImporter::importInitialAssignments(Model* pSBMLModel, std::map<const CDataObject*, SBase*>& copasi2sbmlMap, const CModel* pCopasiModel)
{
  unsigned int i, iMax = pSBMLModel->getNumInitialAssignments();
  std::map<std::string, const CDataObject*> id2copasiMap;
  std::map<const CDataObject*, SBase*>::const_iterator it = copasi2sbmlMap.begin(), endit = copasi2sbmlMap.end();

  while (it != endit)
    {
      id2copasiMap[it->second->getId()] = it->first;
      ++it;
    }

  for (i = 0; i < iMax; ++i)
    {
      const InitialAssignment* pInitialAssignment = pSBMLModel->getInitialAssignment(i);

      if (pInitialAssignment != NULL)
        {
          std::string symbol = pInitialAssignment->getSymbol();
          std::map<std::string, std::string>::const_iterator knownit = mKnownInitalValues.find(symbol);

          if (knownit != mKnownInitalValues.end())
            {
              continue;
            }

          // species reference ids already handled
          if (mSBMLSpeciesReferenceIds.find(symbol) != mSBMLSpeciesReferenceIds.end())
            continue;

          std::map<std::string, const CDataObject*>::iterator pos = id2copasiMap.find(symbol);

          if (pos != id2copasiMap.end())
            {
              if (!pInitialAssignment->isSetMath())
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 58, "Initialassignment", symbol.c_str());
                }
              else
                {
                  const ASTNode* pMath = pInitialAssignment->getMath();
                  assert(pMath != NULL);

                  try
                    {
                      // create a CEvaluationNode based tree from the math
                      // expression
                      ConverterASTNode tmpNode(*pMath);
                      this->preprocessNode(&tmpNode, pSBMLModel, copasi2sbmlMap);
                      // replace the object names
                      this->replaceObjectNames(&tmpNode, copasi2sbmlMap, true);
                      // replace time with initial time
                      this->replace_time_with_initial_time(&tmpNode, pCopasiModel);

                      // starting with sbml level 3 this could actually be an initial assignment to
                      // a species reference which we can't store in COPASI
                      // So we treat this the same way as the stoichiometryMath in SBML level 2
                      const CChemEqElement* pChemEqElement = dynamic_cast<const CChemEqElement*>(pos->second);

                      if (this->mLevel > 2 &&  pChemEqElement != NULL)
                        {
                          // store the expression for the stoichiometry in the stoichiometric expression map
                          // this has been tested and should work
                          this->mStoichiometricExpressionMap.insert(std::make_pair(pMath, pChemEqElement));

                          // go to the next iteration
                          if (reportCurrentProgressOrStop())
                            return;

                          continue;
                        }

                      // now we convert the node to a CEvaluationNode
                      CExpression* pExpression = new CExpression();
                      pExpression->setTree(tmpNode, false);
                      CDataObject * pObject = const_cast< CDataObject * >(pos->second);

                      if (dynamic_cast<CMetab*>(pObject) != NULL)
                        {
                          CMetab* pMetab = dynamic_cast<CMetab*>(pObject);
                          std::map<const CDataObject*, SBase*>::const_iterator pos2 = copasi2sbmlMap.find(pMetab);
                          assert(pos2 != copasi2sbmlMap.end());
                          Species* pSBMLSpecies = dynamic_cast<Species*>(pos2->second);
                          assert(pSBMLSpecies != NULL);
                          const CCompartment* pCompartment = pMetab->getCompartment();
                          assert(pCompartment != NULL);

                          if (pSBMLSpecies->getHasOnlySubstanceUnits() == true || pCompartment->getDimensionality() == 0)
                            {
                              CEvaluationNode* pOrigNode = pExpression->getRoot();
                              assert(pOrigNode != NULL);
                              // divide the expression by the volume
                              CEvaluationNode* pNode = SBMLImporter::divideByObject(pOrigNode, pCompartment->getInitialValueReference());
                              assert(pNode != NULL);

                              if (pNode != NULL)
                                {
                                  pExpression->setRoot(pNode);
                                }
                              else
                                {
                                  fatalError();
                                }
                            }

                          bool r = pMetab->setInitialExpressionPtr(pExpression);

                          if (r == false)
                            {
                              if (pMetab->getInitialExpressionPtr() != pExpression)
                                {
                                  delete pExpression;
                                }

                              CCopasiMessage(CCopasiMessage::RAW, "Some error occurred while importing the initial expression for species with id \"", pInitialAssignment->getSymbol().c_str(), "\".");
                            }
                        }
                      else if (dynamic_cast<CCompartment*>(pObject) != NULL ||
                               dynamic_cast<CModelValue*>(pObject) != NULL)
                        {
                          CModelEntity* pME = dynamic_cast<CModelEntity * >(pObject);
                          bool r = pME->setInitialExpressionPtr(pExpression);

                          if (r == false)
                            {
                              if (pME->getInitialExpressionPtr() != pExpression)
                                {
                                  delete pExpression;
                                }

                              if (dynamic_cast<CCompartment*>(pObject))
                                {
                                  CCopasiMessage(CCopasiMessage::RAW, "Some error occurred while importing the initial expression for compartment with id \"", pInitialAssignment->getSymbol().c_str(), "\".");
                                }
                              else
                                {
                                  CCopasiMessage(CCopasiMessage::RAW, "Some error occurred while importing the initial expression for parameter with id \"", pInitialAssignment->getSymbol().c_str(), "\".");
                                }
                            }
                        }
                      else
                        {
                          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 59, symbol.c_str());
                        }
                    }
                  catch (...)
                    {
                      std::ostringstream os;
                      os << "Error while importing initial assignment for symbol \"";
                      os << symbol << "\".";

                      // check if the last message on the stack is an exception
                      // and if so, add the message text to the current exception
                      if (CCopasiMessage::peekLastMessage().getType() == CCopasiMessage::EXCEPTION)
                        {
                          // we only want the message, not the timestamp line
                          std::string text = CCopasiMessage::peekLastMessage().getText();
                          os << "\n" << text.substr(text.find("\n") + 1);
                        }

                      finishCurrentStep();

                      CCopasiMessage(CCopasiMessage::EXCEPTION, os.str().c_str());
                    }
                }
            }
          else
            {
              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 57, "InitialAssignment", symbol.c_str());
            }
        }

      if (reportCurrentProgressOrStop())
        return;
    }
}

void SBMLImporter::applyStoichiometricExpressions(std::map<const CDataObject*, SBase*>& copasi2sbmlmap, Model* pSBMLModel)
{
  bool warningDone = false;
  std::map<const ASTNode*, const CChemEqElement* >::iterator it = this->mStoichiometricExpressionMap.begin(), end = this->mStoichiometricExpressionMap.end();
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(this->mpCopasiModel);

  while (it != end)
    {
      assert(it->second != NULL);
      const CChemEqElement* pChemEqElement = it->second;
      ConverterASTNode* pNode = new ConverterASTNode(*it->first);
      this->preprocessNode(pNode, pSBMLModel, copasi2sbmlmap);
      this->replaceObjectNames(pNode, copasi2sbmlmap, true);
      CExpression* pExpr = new CExpression("", mpDataModel);
      pExpr->setTree(*pNode, false);
      pExpr->compile(listOfContainers);
      delete pNode;

      if (pExpr->getRoot() == NULL)
        {
          const CReaction* pR = dynamic_cast<const CReaction*>(pChemEqElement->getObjectParent()->getObjectParent()->getObjectParent());
          std::string id = pChemEqElement->getMetabolite()->getSBMLId();
          // create an error message that some stoichiometric expression
          // could not be evaluated that the value for the stoichiometry has
          // been set to 1.0
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 65, id.c_str(), pR->getSBMLId().c_str());
        }
      else
        {
          double value = pExpr->calcValue();
          value -= pChemEqElement->getMultiplicity();
          // find out if the metabolite is a substrate or a product
          delete pExpr;
          CChemEq* pChemEq = dynamic_cast<CChemEq*>(pChemEqElement->getObjectParent()->getObjectParent());
          assert(pChemEq != NULL);

          if (pChemEq != NULL)
            {
              CDataVector < CChemEqElement >::const_iterator iit = pChemEq->getSubstrates().begin(), iendit = pChemEq->getSubstrates().end();

              while (iit != iendit)
                {
                  if (iit == pChemEqElement)
                    {
                      break;
                    }

                  ++iit;
                }

              if (iit != iendit)
                {
                  pChemEq->addMetabolite(pChemEqElement->getMetaboliteKey(), value, CChemEq::SUBSTRATE);
                }
              else
                {
                  pChemEq->addMetabolite(pChemEqElement->getMetaboliteKey(), value, CChemEq::PRODUCT);
                }

              // give a warning that an stoichiometric expression has been
              // converted into a constant
              if (!warningDone && !this->mStoichiometricExpressionMap.empty())
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 64);
                  warningDone = true;
                }
            }
          else
            {
              fatalError();
            }
        }

      ++it;
    }
}

void SBMLImporter::findAvogadroConstant(Model* pSBMLModel, double factor)
{
  unsigned int i, iMax = pSBMLModel->getListOfParameters()->size();

  for (i = 0; i < iMax; ++i)
    {
      const Parameter* pParameter = dynamic_cast<const Parameter*>(pSBMLModel->getListOfParameters()->get(i));

      if (pParameter->getConstant() == true && pParameter->isSetValue() == true)
        {
          double value = pParameter->getValue();

          if (areApproximatelyEqual(factor, value, 1e-3))
            {
              this->mPotentialAvogadroNumbers.insert(pParameter);
            }
        }
    }

  //  if (this->mPotentialAvogadroNumbers.empty())
  //    {
  //      // find an ID that is unique at least within the list of parameters
  //      // since we remove this created parameter after import, it does not
  //      // have to be unique within the whole model
  //      std::set<std::string> ids;
  //      for (i = 0;i < iMax;++i)
  //        {
  //          ids.insert(pSBMLModel->getListOfParameters()->get(i)->getId());
  //}
  //      std::ostringstream os;
  //      i = 1;
  //      os << "parameter_" << i;
  //      while (ids.find(os.str()) != ids.end())
  //        {
  //          ++i;
  //          os.str("");
  //          os << "parameter_" << i;
  //}
  //      Parameter *pParameter = pSBMLModel->createParameter();
  //      pParameter->setId(os.str());
  //      pParameter->setName("amount to particle factor");
  //      pParameter->setConstant(true);
  //      pParameter->setValue(factor);
  //      this->mAvogadroCreated = true;
  //      this->mPotentialAvogadroNumbers.insert(pParameter);
  //}
}

void SBMLImporter::createHasOnlySubstanceUnitFactor(Model* pSBMLModel, double factor, std::map<const CDataObject*, SBase*>& copasi2sbmlmap)
{
  // find an ID that is unique at least within the list of parameters
  // since we remove this created parameter after import, it does not
  // have to be unique within the whole model
  std::set<std::string> ids;
  unsigned int i, iMax = pSBMLModel->getListOfParameters()->size();

  for (i = 0; i < iMax; ++i)
    {
      ids.insert(pSBMLModel->getListOfParameters()->get(i)->getId());
    }

  std::ostringstream os;
  i = 1;
  os << "parameter_" << i;

  while (ids.find(os.str()) != ids.end())
    {
      ++i;
      os.str("");
      os << "parameter_" << i;
    }

  Parameter *pParameter = pSBMLModel->createParameter();
  pParameter->setId(os.str());
  pParameter->setName("amount to particle factor");
  pParameter->setConstant(true);
  pParameter->setValue(factor);
  this->mAvogadroCreated = true;
  this->mPotentialAvogadroNumbers.insert(pParameter);
  CModelValue * pModelValue = this->createCModelValueFromParameter(pParameter, this->mpCopasiModel, copasi2sbmlmap);

  if (pModelValue != NULL)
    {
      pModelValue->setInitialValue(factor);
    }
}

void SBMLImporter::multiplySubstanceOnlySpeciesByVolume(ConverterASTNode* pASTNode)
{
  CNodeIterator< ConverterASTNode > itNode(pASTNode);
  itNode.setProcessingModes(CNodeIteratorMode::Before);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      std::map<Species*, Compartment*>::iterator it = this->mSubstanceOnlySpecies.begin(), endit = this->mSubstanceOnlySpecies.end();

      if (itNode->getType() == AST_DIVIDE)
        {
          // check if the first child is a has only substance species and the second
          // is the compartment the species belongs to
          // in that case, we just change the node to being the species node
          assert(itNode->getNumChildren() == 2);

          if (itNode->getNumChildren() == 2)
            {
              const ASTNode* pChild1 = itNode->getChild(0);
              const ASTNode* pChild2 = itNode->getChild(1);

              if (pChild1->getType() == AST_NAME && pChild2->getType() == AST_NAME)
                {
                  std::string id = pChild1->getName();

                  while (it != endit)
                    {
                      if (it->first->getId() == id)
                        {
                          break;
                        }

                      ++it;
                    }

                  if (it != endit && pChild2->getName() == it->second->getId())
                    {
                      // delete the children
                      itNode->removeChild(1);
                      itNode->removeChild(0);
                      pdelete(pChild1);
                      pdelete(pChild2);
                      // change the current node to represent the species
                      itNode->setType(AST_NAME);
                      itNode->setName(id.c_str());
                      itNode.skipChildren();
                    }
                }
            }
        }
      else if (itNode->getType() == AST_NAME)
        {
          std::string id = itNode->getName();

          while (it != endit)
            {
              if (it->first->getId() == id)
                {
                  break;
                }

              ++it;
            }

          if (it != endit)
            {
              ConverterASTNode* pChild1 = new ConverterASTNode();
              pChild1->setType(AST_NAME);
              pChild1->setName(itNode->getName());
              ConverterASTNode* pChild2 = new ConverterASTNode();
              pChild2->setType(AST_NAME);
              pChild2->setName(it->second->getId().c_str());
              itNode->setType(AST_TIMES);
              itNode->addChild(pChild1);
              itNode->addChild(pChild2);
            }
        }
    }
}

bool SBMLImporter::importMIRIAM(const SBase* pSBMLObject, CDataObject* pCOPASIObject)
{
  bool result = true;

  if (pSBMLObject == NULL || pCOPASIObject == NULL) return false;

  // search for the MIRIAM annotation
  const XMLNode* pMIRIAMNode = NULL;
  const XMLNode* pCOPASIMIRIAMNode = NULL;
  // this const cast is needed because getAnnotation only works on non-const
  // objects.
  const XMLNode* pAnnotation = const_cast<SBase*>(pSBMLObject)->getAnnotation();

  if (pAnnotation != NULL)
    {
      unsigned int i, iMax = pAnnotation->getNumChildren();
      // the top level MIRIAM node must be a direct child to the annotation
      // node and since there can be only one in a valid SBML file, we can
      // stop after we found one
      std::string nameSpace;

      for (i = 0; i < iMax; ++i)
        {
          if (pAnnotation->getChild(i).getURI() == "http://www.w3.org/1999/02/22-rdf-syntax-ns#")
            {
              pMIRIAMNode = &pAnnotation->getChild(i);
              break;
            }

          // maybe import the COPASI MIRIAM annotation
          if (pAnnotation->getChild(i).getURI() == "http://www.copasi.org/static/sbml" && this->mImportCOPASIMIRIAM == true)
            {
              const XMLNode* pCOPASINode = &pAnnotation->getChild(i);
              unsigned int j, jMax = pCOPASINode->getNumChildren();

              for (j = 0; j < jMax; ++j)
                {
                  if (pCOPASINode->getChild(j).getURI() == "http://www.w3.org/1999/02/22-rdf-syntax-ns#")
                    {
                      pCOPASIMIRIAMNode = &pCOPASINode->getChild(j);
                      break;
                    }
                }
            }
        }

      // If the COPASI MIRIAM annotation was found, import it before the SBML
      // MIRIAM annotation so that the SBML MIRIAM annotation can overwrite
      // things from the COPASI MIRIAM annotation.
      if (pCOPASIMIRIAMNode != NULL)
        {
          std::string metaid;

          if (pSBMLObject->isSetMetaId())
            {
              metaid = pSBMLObject->getMetaId();
            }

          std::string miriamString = XMLNode::convertXMLNodeToString(pCOPASIMIRIAMNode);

          switch (pSBMLObject->getTypeCode())
            {
              case SBML_MODEL:
              case SBML_COMPARTMENT:
              case SBML_SPECIES:
              case SBML_PARAMETER:
              {
                assert(dynamic_cast< const Model * >(pSBMLObject) != NULL ||
                       dynamic_cast< const Compartment * >(pSBMLObject) != NULL ||
                       dynamic_cast< const Species * >(pSBMLObject) != NULL ||
                       dynamic_cast< const Parameter * >(pSBMLObject) != NULL);
                assert(dynamic_cast< CModelEntity * >(pCOPASIObject) != NULL);

                CModelEntity * pEntity = static_cast< CModelEntity * >(pCOPASIObject);
                pEntity->setMiriamAnnotation(miriamString,
                                             pEntity->getKey(),
                                             metaid);
              }
              break;

              case SBML_REACTION:
              {
                assert(dynamic_cast<const Reaction*>(pSBMLObject) != NULL);
                assert(dynamic_cast<CReaction*>(pCOPASIObject) != NULL);

                CReaction * pReaction = static_cast<CReaction*>(pCOPASIObject);
                pReaction->setMiriamAnnotation(miriamString, pReaction->getKey(), metaid);
              }
              break;

              case SBML_FUNCTION_DEFINITION:
              {
                assert(dynamic_cast<const FunctionDefinition*>(pSBMLObject) != NULL);
                assert(dynamic_cast<CFunction*>(pCOPASIObject) != NULL);

                CFunction * pFunction = static_cast<CFunction*>(pCOPASIObject);
                pFunction->setMiriamAnnotation(miriamString, pFunction->getKey(), metaid);
              }
              break;

              default:
                result = false;
                break;
            }
        }

      if (pMIRIAMNode != NULL)
        {
          std::string metaid;

          if (pSBMLObject->isSetMetaId())
            metaid = pSBMLObject->getMetaId();

          XMLNode* node = const_cast<XMLNode*>(pMIRIAMNode);

          // BUG 1919: add all namespaces from the document, in case they will be used
          // in the miriam element. (It is valid XML to declare a namespace, but not to
          // use it, while on the other hand it is invalid to *not* define a namespace
          // for a prefix).
          if (pSBMLObject->getSBMLDocument() != NULL &&
              pSBMLObject->getSBMLDocument()->getSBMLNamespaces() != NULL &&
              pSBMLObject->getSBMLDocument()->getSBMLNamespaces()->getNamespaces() != NULL)
            {
              XMLNamespaces* ns = pSBMLObject->getSBMLDocument()->getSBMLNamespaces()->getNamespaces();

              for (int i = 0; i < ns->getNumNamespaces(); ++i)
                {
                  const std::string prefix = ns->getPrefix(i);

                  // don't add the default ns
                  if (prefix.empty())
                    continue;

                  // If the prefix is already defined we do not need to add it.
                  if (node->getNamespaceIndexByPrefix(ns->getPrefix(i)) != -1)
                    {
                      continue;
                    }

                  node->addNamespace(ns->getURI(i), ns->getPrefix(i));
                }
            }

          std::string miriamString = XMLNode::convertXMLNodeToString(pMIRIAMNode);
          CRDFGraphConverter::SBML2Copasi(miriamString);

          switch (pSBMLObject->getTypeCode())
            {
              case SBML_MODEL:
              case SBML_COMPARTMENT:
              case SBML_SPECIES:
              case SBML_PARAMETER:
              {
                assert(dynamic_cast< const Model * >(pSBMLObject) != NULL ||
                       dynamic_cast< const Compartment * >(pSBMLObject) != NULL ||
                       dynamic_cast< const Species * >(pSBMLObject) != NULL ||
                       dynamic_cast< const Parameter * >(pSBMLObject) != NULL);
                assert(dynamic_cast< CModelEntity * >(pCOPASIObject) != NULL);

                CModelEntity * pEntity = static_cast< CModelEntity * >(pCOPASIObject);
                pEntity->setMiriamAnnotation(miriamString,
                                             pEntity->getKey(),
                                             metaid);
              }
              break;

              case SBML_REACTION:
              {
                assert(dynamic_cast<const Reaction*>(pSBMLObject) != NULL);
                assert(dynamic_cast<CReaction*>(pCOPASIObject) != NULL);

                CReaction * pReaction = static_cast<CReaction*>(pCOPASIObject);
                pReaction->setMiriamAnnotation(miriamString, pReaction->getKey(), metaid);
              }
              break;

              case SBML_FUNCTION_DEFINITION:
              {
                assert(dynamic_cast<const FunctionDefinition*>(pSBMLObject) != NULL);
                assert(dynamic_cast<CFunction*>(pCOPASIObject) != NULL);

                CFunction * pFunction = static_cast<CFunction*>(pCOPASIObject);
                pFunction->setMiriamAnnotation(miriamString, pFunction->getKey(), metaid);
              }
              break;

              default:
                result = false;
                break;
            }
        }
    }

  if (pSBMLObject->isSetSBOTerm())
    {
      // import it by adding it to the miriam information
      CAnnotation* annotation = CAnnotation::castObject(pCOPASIObject);
      std::string uri = pSBMLObject->getSBOTermAsURL();
      std::string miriamString = annotation->getMiriamAnnotation();

      if (miriamString.empty())
        {
          std::stringstream str;

          str << "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' xmlns:dc='http://purl.org/dc/elements/1.1/' xmlns:dcterms='http://purl.org/dc/terms/' xmlns:vCard='http://www.w3.org/2001/vcard-rdf/3.0#' xmlns:bqbiol='http://biomodels.net/biology-qualifiers/' xmlns:bqmodel='http://biomodels.net/model-qualifiers/'>"
              << "  <rdf:Description rdf:about='#COPASI0'>\n"
              << "    <bqmodel:is>\n"
              << "      <rdf:Bag>\n"
              << "        <rdf:li rdf:resource='" << uri << "' />\n"
              << "      </rdf:Bag>\n"
              << "    </bqmodel:is>\n"
              << "  </rdf:Description>\n"
              << "</rdf:RDF>";

          miriamString = str.str();

          annotation->setMiriamAnnotation(miriamString, annotation->getKey(), "");
        }
      else
        {
          std::string sboTerm = pSBMLObject->getSBOTermID();
          // load miriam info
          CMIRIAMInfo info;
          info.load(dynamic_cast< CDataContainer * >(pCOPASIObject));

          // check whether term is already there
          CDataVector <CBiologicalDescription>& descriptons = info.getBiologicalDescriptions();
          CDataVector <CBiologicalDescription>::const_iterator it = descriptons.begin()
              , end = descriptons.end();

          bool found = false;

          for (; it != end; ++it)
            {
              if (it->getId() == sboTerm)
                {
                  found = true;
                  break;
                }
            }

          // add if it wasn't there
          if (!found)
            {
              CBiologicalDescription* bqBiol = info.createBiologicalDescription();
              bqBiol->setPredicate("is");
              bqBiol->setResource("Systems Biology Ontology");
              bqBiol->setId(sboTerm);
              info.save();
            }
        }
    }

  return result;
}

const CDataObject* SBMLImporter::isConstantFlux(const CEvaluationNode* pRoot, CModel* pModel)
{
  const CDataObject* pObject = NULL;
  CRegisteredCommonName name;
  CEvaluationNode::MainType MainType = pRoot->mainType();

  switch (MainType)
    {
      case CEvaluationNode::MainType::CALL:
      {
        // the function call may only have one child
        // which must be o object node
        if (pRoot->getChild() != NULL &&
            pRoot->getChild()->getSibling() == NULL &&
            dynamic_cast<const CEvaluationNode*>(pRoot->getChild())->mainType() == CEvaluationNode::MainType::OBJECT)
          {
            const CEvaluationTree* pTree = CRootContainer::getFunctionList()->findFunction(pRoot->getData());

            // the function may only have one node which must be the
            // variable
            if (pTree != NULL &&
                pTree->getRoot() != NULL &&
                pTree->getRoot()->getChild() == NULL &&
                pTree->getRoot()->mainType() == CEvaluationNode::MainType::VARIABLE)
              {
                name = dynamic_cast<const CEvaluationNodeObject*>(pRoot->getChild())->getObjectCN();
                assert(!name.empty());
                // TODO remove this function from the usedFunctions list
                // if it is still in there
              }
          }
      }
      break;

      case CEvaluationNode::MainType::OBJECT:
        name = dynamic_cast<const CEvaluationNodeObject*>(pRoot)->getObjectCN();
        assert(!name.empty());
        break;

      default:
        break;
    }

  if (name.empty())
    return NULL;

  // check if the object is a local or global parameter
  pObject = CObjectInterface::DataObject(pModel->getObjectFromCN(name));

  if (pObject != NULL && pObject->hasFlag(CDataObject::Reference))
    {
      pObject = pObject->getObjectParent();
    }

  if (!(dynamic_cast< const CModelValue * >(pObject) || dynamic_cast< const CCopasiParameter * >(pObject)))
    {
      pObject = NULL;
    }

  return pObject;
}

/**
 * Returns the flag that determines whether COPASI MIRIAM annotation is
 * imported if it is present.
 */
bool SBMLImporter::getImportCOPASIMIRIAM() const
{
  return this->mImportCOPASIMIRIAM;
}

/**
 * Sets the flag that determines whether COPASI MIRIAM annotation is
 * imported if it is present.
 */
void SBMLImporter::setImportCOPASIMIRIAM(bool import)
{
  this->mImportCOPASIMIRIAM = import;
}
/**
 * If an initial expression uses time, we have to import it as initial time
 * instead.
 * This method takes an AST node and converts all time nodes to object nodes
 * that have the common name of the time as the name.
 */
void SBMLImporter::replace_time_with_initial_time(ASTNode* pASTNode, const CModel* pCopasiModel)
{
  CNodeIterator< ASTNode > itNode(pASTNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      if (itNode->getType() == AST_NAME_TIME)
        {
          itNode->setType(AST_NAME);
          const CDataObject* pReference = pCopasiModel->getInitialValueReference();
          assert(pReference);
          itNode->setName(pReference->getStringCN().c_str());
        }
    }
}

void SBMLImporter::setImportInitialValueAnnotation(bool parseInitialValues)
{
  mImportInitialValues = parseInitialValues;
}

void SBMLImporter::importEvents(Model * pSBMLModel, CModel * pCopasiModel, std::map< const CDataObject *, SBase * > & copasi2sbmlmap)
{
  unsigned int i, iMax = pSBMLModel->getNumEvents();

  for (i = 0; i < iMax; ++i)
    {
      try
        {
          this->importEvent(pSBMLModel->getEvent(i), pSBMLModel, pCopasiModel, copasi2sbmlmap);
        }
      catch (...)
        {
          std::ostringstream os;
          os << "Error while importing event ";
          os << i + 1 << ".";

          // check if the last message on the stack is an exception
          // and if so, add the message text to the current exception
          if (CCopasiMessage::peekLastMessage().getType() == CCopasiMessage::EXCEPTION)
            {
              // we only want the message, not the timestamp line
              std::string text = CCopasiMessage::peekLastMessage().getText();
              os << "\n" << text.substr(text.find("\n") + 1);
            }

          finishCurrentStep();

          CCopasiMessage(CCopasiMessage::EXCEPTION, os.str().c_str());
        }

      if (reportCurrentProgressOrStop())
        return;
    }
}

void SBMLImporter::importEvent(const Event* pEvent, Model* pSBMLModel, CModel* pCopasiModel, std::map<const CDataObject*, SBase*>& copasi2sbmlmap)
{
  if (pEvent == NULL) return;

  // no point including an event without trigger element
  if (!pEvent->isSetTrigger())
    {
      CCopasiMessage(CCopasiMessage::WARNING, "Encountered event without trigger element, this event cannot be imported and is skipped.");
      return;
    }

  // no point including an event without trigger math
  if (!pEvent->getTrigger()->isSetMath())
    {
      CCopasiMessage(CCopasiMessage::WARNING, "Encountered event without trigger expression, this event cannot be imported and is skipped.");
      return;
    }

  /* Check if the name of the reaction is unique. */
  std::string eventName = pEvent->getName();

  if (isEmptyOrWhiteSpace(eventName))
    {
      eventName = pEvent->getId();

      if (isEmptyOrWhiteSpace(eventName))
        {
          eventName = "Event";
        }
    }

  std::string appendix;
  unsigned int counter = 2;
  std::ostringstream numberStream;

  while (pCopasiModel->getEvents().getIndex(eventName + appendix) != C_INVALID_INDEX)
    {
      numberStream.str("");
      numberStream << "_" << counter;
      counter++;
      appendix = numberStream.str();
    }

  CEvent* pCOPASIEvent = pCopasiModel->createEvent(eventName + appendix);
  assert(pCOPASIEvent != NULL);

  if (pEvent->isSetId())
    {
      pCOPASIEvent->setSBMLId(pEvent->getId());
    }

  // import the trigger
  const Trigger* pTrigger = pEvent->getTrigger();

  if (pTrigger->isSetInitialValue())
    {
      pCOPASIEvent->setFireAtInitialTime(!pTrigger->getInitialValue());
    }
  else
    {
      pCOPASIEvent->setFireAtInitialTime(false);
    }

  if (pTrigger->isSetPersistent())
    {
      pCOPASIEvent->setPersistentTrigger(pTrigger->getPersistent());
    }
  else
    {
      pCOPASIEvent->setPersistentTrigger(true);
    }

  if (!pTrigger->isSetMath())
    {
      fatalError();
    }

  const ASTNode* pMath = pTrigger->getMath();

  assert(pMath != NULL);

  // check for references to species references in the expression because we don't support them yet
  if (!SBMLImporter::findIdInASTTree(pMath, this->mSBMLSpeciesReferenceIds).empty())
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 95);
    }

  // convert and set math expression
  ConverterASTNode* pTmpNode = new ConverterASTNode(*pMath);

  this->preprocessNode(pTmpNode, pSBMLModel, copasi2sbmlmap);

  // replace the object names
  this->replaceObjectNames(pTmpNode, copasi2sbmlmap);

  // now we convert the node to a CEvaluationNode
  CExpression* pExpression = dynamic_cast<CExpression*>(CEvaluationTree::create(CEvaluationTree::Expression));

  pExpression->setIsBoolean(true);

  pExpression->setTree(*pTmpNode, false);

  delete pTmpNode;

  pCOPASIEvent->setTriggerExpressionPtr(pExpression);

  // import the priority
  if (pEvent->isSetPriority() && pEvent->getPriority()->isSetMath())
    {
      const Priority * pPriority = pEvent->getPriority();

      if (!pPriority->isSetMath())
        {
          fatalError();
        }

      pMath = pPriority->getMath();
      assert(pMath != NULL);

      // check for references to species references in the expression because we don't support them yet
      if (!SBMLImporter::findIdInASTTree(pMath, this->mSBMLSpeciesReferenceIds).empty())
        {
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 95);
        }

      // convert and set math expression
      pTmpNode = new ConverterASTNode(*pMath);
      this->preprocessNode(pTmpNode, pSBMLModel, copasi2sbmlmap);
      // replace the object names
      this->replaceObjectNames(pTmpNode, copasi2sbmlmap);
      // now we convert the node to a CEvaluationNode
      CExpression* pExpression = new CExpression;
      pExpression->setTree(*pTmpNode, false);
      delete pTmpNode;
      pCOPASIEvent->setPriorityExpressionPtr(pExpression);
    }

  // import the delay
  bool haveDelay = pEvent->isSetDelay() && pEvent->getDelay()->isSetMath();
  pCOPASIEvent->setDelayAssignment(pEvent->getUseValuesFromTriggerTime());

  if (haveDelay)
    {
      const Delay* pDelay = pEvent->getDelay();

      pMath = pDelay->getMath();
      assert(pMath != NULL);

      // check for references to species references in the expression because we don't support them yet
      if (!SBMLImporter::findIdInASTTree(pMath, this->mSBMLSpeciesReferenceIds).empty())
        {
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 95);
        }

      // convert and set math expression
      pTmpNode = new ConverterASTNode(*pMath);
      this->preprocessNode(pTmpNode, pSBMLModel, copasi2sbmlmap);
      // replace the object names
      this->replaceObjectNames(pTmpNode, copasi2sbmlmap);
      // now we convert the node to a CEvaluationNode
      CExpression* pExpression = new CExpression;
      pExpression->setTree(*pTmpNode, false);
      delete pTmpNode;
      pCOPASIEvent->setDelayExpressionPtr(pExpression);
    }

  // import all assignments
  std::map<std::string, const CDataObject*> id2copasiMap;
  std::map<const CDataObject*, SBase*>::const_iterator it = copasi2sbmlmap.begin(), endit = copasi2sbmlmap.end();

  while (it != endit)
    {
      id2copasiMap[it->second->getId()] = it->first;
      ++it;
    }

  unsigned int i, iMax = pEvent->getNumEventAssignments();

  for (i = 0; i < iMax; ++i)
    {
      const EventAssignment* pEventAssignment = pEvent->getEventAssignment(i);

      if (!pEventAssignment->isSetVariable())
        {
          CCopasiMessage(CCopasiMessage::WARNING, "EventAssignment without variable defined for event '%s', ignoring.", pEvent->getId().c_str());
          continue;
        }

      // the COPASI object that corresponds to the variable
      const std::string& variable = pEventAssignment->getVariable();

      // if the id occurs in mSBMLSpeciesReferenceIds, we have an assignment to a species reference which is not supported
      if (this->mLevel > 2 && this->mSBMLSpeciesReferenceIds.find(variable) != this->mSBMLSpeciesReferenceIds.end())
        {
          this->mEventAssignmentForSpeciesReferenceIgnored = true;
          // next iteration
          continue;
        }

      std::map<std::string, const CDataObject*>::iterator pos = id2copasiMap.find(variable);

      if (pos == id2copasiMap.end())
        {
          //  issue an error message and ignore the assignment
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 57, "Eventassignment", variable.c_str());
          continue;
        }

      const CDataObject* pObject = pos->second;

      if (pObject->getObjectType() != "Compartment" && pObject->getObjectType() != "Metabolite" && pObject->getObjectType() != "ModelValue")
        {
          // issue an error and ignore the assignment
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 72, "Eventassignment", variable.c_str());
          continue;
        }

      // import the assignment math expression
      if (!pEventAssignment->isSetMath())
        {
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 58, "Eventassignment", variable.c_str());
          continue;
        }

      CExpression* pExpression = NULL;
      CEventAssignment* pAssignment = NULL;
      pMath = pEventAssignment->getMath();
      bool isEventAssignmentToParticleNumber = hasCopasiAnnotation(pEventAssignment, "http://copasi.org/eventAssignment");
      assert(pMath != NULL);

      if (isEventAssignmentToParticleNumber && pMath)
        {
          if (pMath->getType() == AST_DIVIDE && pMath->getNumChildren() == 2)
            {
              // drop the division
              pMath = pMath->getChild(0);
            }
        }

      // check for references to species references in the expression because we don't support them yet
      if (!SBMLImporter::findIdInASTTree(pMath, this->mSBMLSpeciesReferenceIds).empty())
        {
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 95);
        }

      try
        {
          // convert and set math expression
          pTmpNode = new ConverterASTNode(*pMath);
          this->preprocessNode(pTmpNode, pSBMLModel, copasi2sbmlmap);
          // replace the object names
          this->replaceObjectNames(pTmpNode, copasi2sbmlmap);
          // check if the model entity is a species and if it has the
          // hasOnlySubstanceUnits flag set
          // if so, we have to divide the expression by the volume of the species
          // compartment
          // now we convert the node to a CEvaluationNode
          std::map<const CDataObject*, SBase*>::const_iterator pos2 = copasi2sbmlmap.find(pObject);

          // we should always end up with an object, otherwise there is something
          // wrong
          if (pos2 == copasi2sbmlmap.end()) fatalError();

          pExpression = new CExpression;
          pExpression->setTree(*pTmpNode, false);
          delete pTmpNode;

          const CMetab * pMetab = dynamic_cast< const CMetab * >(pObject);

          if (pos2->second->getTypeCode() == SBML_SPECIES && dynamic_cast< const Species * >(pos2->second)->getHasOnlySubstanceUnits() == true)
            {
              // divide the expression by the volume
              // check if the top level node is a multiplication and one
              // of the children is the volume of the compartment the species
              // is in. If this is the case, just drop the multiplication
              // instead of dividing
              assert(pMetab != NULL);
              const CCompartment* pCompartment = pMetab->getCompartment();

              CEvaluationNode* pOrigNode = pExpression->getRoot();
              assert(pOrigNode != NULL);
              CEvaluationNode* pNode = SBMLImporter::divideByObject(pOrigNode, pCompartment->getValueReference());
              assert(pNode != NULL);

              if (pNode != NULL)
                {
                  pExpression->setRoot(pNode);
                }
              else
                {
                  fatalError();
                }
            }

          std::string target = pObject->getKey();

          if (isEventAssignmentToParticleNumber && pMetab)
            target = pMetab->getValueReference()->getStringCN();

          pAssignment = new CEventAssignment(target, pCOPASIEvent);
          pAssignment->setExpressionPtr(pExpression);
        }
      catch (...)
        {
          pdelete(pAssignment);
          std::ostringstream os;
          os << "Error while importing event assignment for variable \"";
          os << variable << "\".";

          // check if the last message on the stack is an exception
          // and if so, add the message text to the current exception
          if (CCopasiMessage::peekLastMessage().getType() == CCopasiMessage::EXCEPTION)
            {
              // we only want the message, not the timestamp line
              std::string text = CCopasiMessage::peekLastMessage().getText();
              os << "\n" << text.substr(text.find("\n") + 1);
            }

          CCopasiMessage(CCopasiMessage::EXCEPTION, os.str().c_str());
        }

      assert(pAssignment != NULL);
      pCOPASIEvent->getAssignments().add(pAssignment, true);
    }

  copasi2sbmlmap[pCOPASIEvent] = const_cast<Event*>(pEvent);
  SBMLImporter::importMIRIAM(pEvent, pCOPASIEvent);
  SBMLImporter::importNotes(pCOPASIEvent, pEvent);
}

/**
 * Starting with SBML Level 2 Version 4, function definitions no longer need to
 * be ordered, i.e. a function definition may refer to another function
 * definition that is defined somewhere further down in the file.
 * So we have to import the function definitions in the correct order.
 */
void SBMLImporter::importFunctionDefinitions(Model* pSBMLModel, std::map<const CDataObject*, SBase*>& copasi2sbmlmap)
{
  std::map<const FunctionDefinition*, std::set<std::string> > directFunctionDependencies;
  unsigned int i = 0, iMax = pSBMLModel->getNumFunctionDefinitions();

  // first we find all direct function dependencies for a function definition
  for (; i < iMax; ++i)
    {
      SBMLImporter::findDirectDependencies(pSBMLModel->getFunctionDefinition(i), directFunctionDependencies);
    }

  std::map<const FunctionDefinition*, std::set<std::string> >::iterator it = directFunctionDependencies.begin(), endit = directFunctionDependencies.end();

  while (it != endit)
    {
      // now we import all function definitions that do not have any dependencies
      if (it->second.empty())
        {
          CFunction* pFun = NULL;

          try
            {
              pFun = this->createCFunctionFromFunctionDefinition(it->first, pSBMLModel, copasi2sbmlmap);
            }
          catch (...)
            {
              std::ostringstream os;
              os << "Error while importing function definition \"";
              os << it->first->getId() << "\".";

              // check if the last message on the stack is an exception
              // and if so, add the message text to the current exception
              if (CCopasiMessage::peekLastMessage().getType() == CCopasiMessage::EXCEPTION)
                {
                  // we only want the message, not the timestamp line
                  std::string text = CCopasiMessage::peekLastMessage().getText();
                  os << "\n" << text.substr(text.find("\n") + 1);
                }

              CCopasiMessage(CCopasiMessage::EXCEPTION, os.str().c_str());
            }

          assert(pFun != NULL);

          std::map<std::string, std::string>::const_iterator pos = mKnownCustomUserDefinedFunctions.find(it->first->getId());

          if (pos != mKnownCustomUserDefinedFunctions.end())
            {
              if (pos->second == "RUNIFORM")
                {
                  // replace call to function with call to uniform
                  pFun->setInfix("UNIFORM(a, b)");
                  pFun->compile();
                }
              else if (pos->second == "RNORMAL")
                {
                  // replace call to function with call to normal
                  pFun->setInfix("NORMAL(a, b)");
                  pFun->compile();
                }
              else if (pos->second == "RPOISSON")
                {
                  // replace call to function with call to normal
                  pFun->setInfix("POISSON(a)");
                  pFun->compile();
                }
              else if (pos->second == "RGAMMA")
                {
                  // replace call to function with call to normal
                  pFun->setInfix("GAMMA(a, b)");
                  pFun->compile();
                }
            }

          copasi2sbmlmap[pFun] = const_cast<FunctionDefinition*>(it->first);
          this->mFunctionNameMapping[it->first->getId()] = pFun->getObjectName();
          // next we delete the imported function definitions from the dependencies of
          // the other function definitions
          std::string id = it->first->getId();
          directFunctionDependencies.erase(it);
          // here we change the iterators !!!!
          it = directFunctionDependencies.begin(), endit = directFunctionDependencies.end();

          while (it != endit)
            {
              it->second.erase(id);
              ++it;
            }

          // start from the beginning
          it = directFunctionDependencies.begin();
          continue;
        }

      ++it;
    }

  // if the dependency list is not empty by now we have a problem
  if (!directFunctionDependencies.empty())
    {
      std::string nameList;
      it = directFunctionDependencies.begin(), endit = directFunctionDependencies.end();

      while (it != endit)
        {
          nameList += "\"" + it->first->getId() + "\",\n";
          ++it;
        }

      nameList = nameList.substr(0, nameList.size() - 2);
      // clean up the temporary function database
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 76, nameList.c_str());
    }

  return;
}

/**
 * static method that finds all direct function dependencies of a given
 * function definition.
 */
void SBMLImporter::findDirectDependencies(const FunctionDefinition* pFunDef, std::map<const FunctionDefinition*, std::set<std::string> >& dependencies)
{
  // if we don't have math, we don't have dependencies
  if (pFunDef == NULL || !pFunDef->isSetMath() || pFunDef->getMath()->getNumChildren() == 0)
    return;

  assert(pFunDef != NULL);
  std::set<std::string> deps;
  SBMLImporter::findDirectDependencies(pFunDef->getMath()->getChild(pFunDef->getMath()->getNumChildren() - 1), deps);
  dependencies.insert(std::pair<const FunctionDefinition*, std::set<std::string> >(pFunDef, deps));
}

/**
 * static method that recursively finds all direct function dependencies of the
 * expression rooted at the given node.
 */
void SBMLImporter::findDirectDependencies(const ASTNode* pNode, std::set<std::string>& dependencies)
{
  // TODO CRITICAL We need to use a node iterator
  assert(pNode != NULL);

  if (pNode->getType() == AST_FUNCTION)
    {
      // found a function call
      dependencies.insert(pNode->getName());
    }

  unsigned int i = 0, iMax = pNode->getNumChildren();

  for (; i < iMax; ++i)
    {
      SBMLImporter::findDirectDependencies(pNode->getChild(i), dependencies);
    }
}

/**
 * This function replaces calls to the delay function in an ASTNode tree
 * by a node that references a new global parameter which the function
 * creates. The global parameter gets an expression which corresponds to the
 * delay call.
 * This is necessary because all kinetic laws in COPASI are function calls and
 * function definitions should not contain a call to delay.
 */
void SBMLImporter::replaceDelayAndRateOfInReaction(ConverterASTNode * pASTNode, Model * pModel, std::map< const CDataObject *, SBase * > & copasi2sbmlmap, Reaction * pSBMLReaction, std::map< std::string, std::string > & localReplacementMap)
{
  if (pModel == NULL || mpCopasiModel == NULL)
    {
      fatalError();
    }

  CNodeIterator< ConverterASTNode > itNode(pASTNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      if (itNode->getType() == AST_FUNCTION_DELAY)
        {
          std::string prefix = "delay_replacement_parameter_";
          std::map< std::string, std::string > & map = this->mDelayNodeMap;
          replaceUnsupportedNodeInKinetic(itNode, map, prefix, pModel, copasi2sbmlmap, pSBMLReaction, localReplacementMap);
        }
      else if (itNode->getType() == AST_FUNCTION_RATE_OF)
        {
          std::string prefix = "rateOf_";
          std::map< std::string, std::string > & map = this->mReplacedRates;
          replaceUnsupportedNodeInKinetic(itNode, map, prefix, pModel, copasi2sbmlmap, pSBMLReaction, localReplacementMap);
        }
    }
}

void SBMLImporter::replaceUnsupportedNodeInKinetic(CNodeIterator< ConverterASTNode >& itNode, std::map< std::string, std::string > & map, std::string prefix, Model * pModel, std::map< const CDataObject *, SBase * > & copasi2sbmlmap, Reaction * pSBMLReaction, std::map< std::string, std::string > & localReplacementMap)
{
  std::string formula = SBML_formulaToL3String(*itNode);
  std::map< std::string, std::string >::const_iterator pos = map.find(formula);
  std::string replacementId;

  if (pos == map.end())
    {
      // create a new global parameter and a rule for it
      unsigned int index = 0;
      std::ostringstream os;
      os << prefix;
      os << index;

      while (this->mUsedSBMLIds.find(os.str()) != this->mUsedSBMLIds.end())
        {
          os.str("");
          os << prefix;
          ++index;
          os << index;
        }

      Parameter * pParameter = pModel->createParameter();
      assert(pParameter != NULL);

      if (pParameter == NULL)
        {
          fatalError();
        }

      // mark the id as used
      pParameter->setId(os.str());
      pParameter->setName(os.str());
      pParameter->setConstant(false);
      replacementId = pParameter->getId();
      this->mUsedSBMLIds.insert(replacementId);

      // now we need to import that parameter
      try
        {
          assert(mpCopasiModel);
          this->createCModelValueFromParameter(pParameter, mpCopasiModel, copasi2sbmlmap);
        }
      catch (...)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, "An unknown error has occurred while replacing a delay call in a kinetic law expression. Please report this to the authors of COPASI.");
        }

      // now we create the rule
      AssignmentRule * pARule = pModel->createAssignmentRule();
      assert(pARule != NULL);

      if (pARule == NULL)
        {
          fatalError();
        }

      pARule->setVariable(pParameter->getId());

      // we have to make sure that there is no local parameter referenced
      // in the tree for the rule.
      // If there is a local parameter, we have to convert it to a global
      // parameter
      // starting with SBML Level 3, the parameters of a kinetic law are expressed in
      // terms of a new class called LocalParameter instead of Parameter
      ListOfParameters * pList = NULL;

      if (this->mLevel > 2)
        {
          pList = pSBMLReaction->getKineticLaw()->getListOfLocalParameters();
        }
      else
        {
          pList = pSBMLReaction->getKineticLaw()->getListOfParameters();
        }

      unsigned int i, iMax = pList->size();

      if (iMax > 0)
        {
          std::set< std::string > localIds;
          // first we fill the local id set
          const Parameter * pParam = NULL;

          for (i = 0; i < iMax; ++i)
            {
              pParam = pList->get(i);
              assert(pParam != NULL);
              localIds.insert(pParam->getId());
            }

          // this has to be a two step process because we first have to identify
          // all local parameters that are used in a delay
          // Next we have to go over the tree again and replace all occurrences of
          // those parameters with the global parameters, independent of whether
          // they are used in a delay expression or not
          this->find_local_parameters_in_delay(*itNode, pSBMLReaction, pModel, localReplacementMap, localIds, copasi2sbmlmap);

          // now we have to at least replace the ones that appear in delays here already because otherwise
          // the import of the rule that was created for the delay replacement will fail because it can't resolve
          // the name of the local parameter in the rule
          if (!localReplacementMap.empty())
            {
              this->replace_name_nodes(*itNode, localReplacementMap);
            }
        }

      pARule->setMath(*itNode);

      // and we need to import this rule
      try
        {
          this->importSBMLRule(pARule, copasi2sbmlmap, pModel);
        }
      catch (...)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, "An unknown error has occurred while replacing a delay call in a kinetic law expression. Please report this to the authors of COPASI.");
        }

      // and we add the formula id pair to the map so that we can reuse it if
      // the same expression comes up again
      map.insert(std::pair< std::string, std::string >(formula, pParameter->getId()));
    }
  else
    {
      replacementId = pos->second;
    }

  itNode->setType(AST_NAME);
  itNode->setName(replacementId.c_str());

  while (itNode->getNumChildren() > 0)
    {
      itNode->removeChild(0);
    }
}

/**
 * If we replace delay nodes within kinetic laws, we have to make sure that
 * there is no reference to a local parameter within the replaced
 * delay node because that would mean that we end up with a reference to a
 * local parameter in the rule for the delay replacement which is not allowed
 * in SBML.
 * Therefore we have to convert all local parameters which occur within a
 * delay call into global parameters.
 */
void SBMLImporter::find_local_parameters_in_delay(ASTNode* pASTNode, Reaction* pSBMLReaction, Model* pModel, std::map<std::string, std::string>& localReplacementMap, const std::set<std::string>& localIds, std::map<const CDataObject*, SBase*>& copasi2sbmlmap)
{
  CNodeIterator< ASTNode > itNode(pASTNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      if (itNode->getType() == AST_NAME)
        {
          // check it this is the name of a local parameter

          // maybe there already is a replacement for this
          std::map<std::string, std::string>::const_iterator pos = localReplacementMap.find(itNode->getName());

          if (pos == localReplacementMap.end())
            {
              // now we check if this is a reference to a local parameter
              if (localIds.find(itNode->getName()) != localIds.end())
                {
                  // we need to create a new global parameter with a unique name
                  // the name should laso be unique within the localId set so we surely won't run
                  // into problems
                  //
                  unsigned int index = 0;
                  std::ostringstream os;
                  os << pSBMLReaction->getId() << "_local_";
                  std::string prefix(os.str());
                  os << index;

                  while (this->mUsedSBMLIds.find(os.str()) != this->mUsedSBMLIds.end() || localIds.find(os.str()) != localIds.end())
                    {
                      os.str("");
                      os << prefix;
                      ++index;
                      os << index;
                    }

                  // create the global parameter
                  if (pModel == NULL)
                    {
                      fatalError();
                    }

                  Parameter* pParameter = pModel->createParameter();
                  assert(pParameter != NULL);

                  if (pParameter == NULL)
                    {
                      fatalError();
                    }

                  const Parameter* pOldParam = pSBMLReaction->getKineticLaw()->getParameter(itNode->getName());

                  assert(pOldParam != NULL);

                  if (pOldParam == NULL)
                    {
                      fatalError();
                    }

                  // make a copy, we he hopefully don't loose important annotations
                  (*pParameter) = (*pOldParam);

                  if (!pOldParam->isSetValue())
                    {
                      pParameter->setValue(std::numeric_limits<C_FLOAT64>::quiet_NaN());
                    }

                  // mark the id as used
                  pParameter->setId(os.str());
                  pParameter->setName(os.str());
                  pParameter->setConstant(true);
                  localReplacementMap.insert(std::pair<std::string, std::string>(itNode->getName(), pParameter->getId()));
                  this->mUsedSBMLIds.insert(pParameter->getId());

                  // now we need to import that parameter
                  try
                    {
                      assert(mpCopasiModel != NULL);
                      this->createCModelValueFromParameter(pParameter, mpCopasiModel, copasi2sbmlmap);
                    }
                  catch (...)
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, "An unknown error has occurred while converting a local reaction parameter to a global parameter. Please report this to the authors of COPASI.");
                    }
                }
            }
        }
    }
}

/**
 * This method gets an ASTNode and a map between old node names and new node
 * names. All AST_NAME nodes with an "old" name are replaced by a node with
 * the "new" name.
 */
void SBMLImporter::replace_name_nodes(ASTNode* pASTNode, const std::map<std::string, std::string>& replacementMap)
{
  CNodeIterator< ASTNode > itNode(pASTNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      if (itNode->getType() == AST_NAME)
        {
          std::map<std::string, std::string>::const_iterator pos = replacementMap.find(itNode->getName());

          if (pos != replacementMap.end())
            {
              itNode->setName(pos->second.c_str());
            }
        }
    }
}

/**
 * This method check if a unit has been set on a number node.
 * If such a node is found in the tree, true is returned.
 */
bool SBMLImporter::checkForUnitsOnNumbers(const ASTNode* pASTNode)
{
  bool result = false;
  CNodeIterator< const ASTNode > itNode(pASTNode);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      switch (itNode->getType())
        {
          case AST_INTEGER:
          case AST_REAL:
          case AST_REAL_E:
          case AST_RATIONAL:

            if (itNode->isSetUnits())
              {
                result = true;
                break;
              }

            break;

          default:
            break;
        }
    }

  return result;
}

/**
 * This method checks if there are conversion factors that need to be applied to
 * ChemicalEquationElements and applies them.
 */
void SBMLImporter::applyConversionFactors()
{
  std::map<const CChemEqElement*, std::pair<std::string, CChemEq::MetaboliteRole> >::iterator it = this->mChemEqElementSpeciesIdMap.begin();
  std::map<const CChemEqElement*, std::pair<std::string, CChemEq::MetaboliteRole> >::iterator endit = this->mChemEqElementSpeciesIdMap.end();
  std::map<std::string, const CModelValue*>::const_iterator pos, endpos = this->mSpeciesConversionParameterMap.end();
  const CModelValue* pModelValue = NULL;
  double v;
  const CMetab* pMetab = NULL;;
  CChemEq* pChemEq = NULL;
  const CChemEqElement* pE = NULL;

  while (it != endit)
    {
      pE = it->first;
      pos = this->mSpeciesConversionParameterMap.find(it->second.first);

      if (pos != endpos)
        {
          pModelValue = pos->second;
          assert(pModelValue != NULL);
        }
      else
        {
          if (this->mpModelConversionFactor != NULL)
            {
              pModelValue = this->mpModelConversionFactor;
            }
          else
            {
              pModelValue = NULL;
            }
        }

      if (pModelValue != NULL)
        {
          v = pModelValue->getInitialValue();
          v *= it->first->getMultiplicity();
          // we need the ChemEq for the element
          // and the species key
          assert(it->first->getObjectParent() != NULL);

          if (it->first->getObjectParent() != NULL)
            {
              pChemEq = dynamic_cast<CChemEq*>(it->first->getObjectParent()->getObjectParent());
              assert(pChemEq != NULL);
              pMetab = it->first->getMetabolite();
              assert(pMetab != NULL);

              if (pChemEq != NULL && pMetab != NULL)
                {
                  pChemEq->setMultiplicity(pMetab, v, it->second.second);
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, "Error handling a conversion factor. Please report this problem to the COPASI developers.");
                }
            }
          else
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, "Error handling a conversion factor. Please report this problem to the COPASI developers.");
            }
        }

      ++it;
    }
}

/**
 * Goes through all SBML reactions and collects the ids of all species references.
 */
void SBMLImporter::updateSBMLSpeciesReferenceIds(Model* pModel, std::map<std::string, double>& ids)
{
  ids.clear();

  if (pModel == NULL) return;

  unsigned int i, iMax = pModel->getNumReactions();
  unsigned int j, jMax;
  Reaction* pReaction = NULL;
  SpeciesReference* pSpeciesReference = NULL;

  SBMLTransforms::mapComponentValues(pModel);

  for (i = 0; i < iMax; ++i)
    {
      // we only need to care about substrates and products
      // because modifiers do not have stoichiometry, so it doesn't make sense to
      // assign something to them or reference them in a mathematical expression
      pReaction = pModel->getReaction(i);
      assert(pReaction != NULL);

      if (pReaction != NULL)
        {
          // first the substrates
          jMax = pReaction->getNumReactants();

          for (j = 0; j < jMax; ++j)
            {
              pSpeciesReference = pReaction->getReactant(j);
              assert(pSpeciesReference != NULL);

              if (pSpeciesReference == NULL || !pSpeciesReference->isSetId())
                continue;

              // make sure all ids are unique
              assert(ids.find(pSpeciesReference->getId()) == ids.end());

              double stoichiometry = SBMLTransforms::evaluateASTNode(SBML_parseFormula(pSpeciesReference->getId().c_str()), pModel);
              ids.insert(std::pair<std::string, double>(pSpeciesReference->getId(),
                         stoichiometry));
              // update stoichiometry
              pSpeciesReference->setStoichiometry(stoichiometry);
            }

          // same for the products
          jMax = pReaction->getNumProducts();

          for (j = 0; j < jMax; ++j)
            {
              pSpeciesReference = pReaction->getProduct(j);
              assert(pSpeciesReference != NULL);

              if (pSpeciesReference == NULL || !pSpeciesReference->isSetId())
                continue;

              // make sure all ids are unique
              assert(ids.find(pSpeciesReference->getId()) == ids.end());

              double stoichiometry = SBMLTransforms::evaluateASTNode(SBML_parseFormula(pSpeciesReference->getId().c_str()), pModel);
              ids.insert(std::pair<std::string, double>(pSpeciesReference->getId(),
                         stoichiometry));
              // update stoichiometry
              pSpeciesReference->setStoichiometry(stoichiometry);
            }
        }
    }
}

/**
 * This method divides the given expression by the given object and returns a new expression.
 * The caller is responsible for freeing the memory for the new expression.
 */
CEvaluationNode* SBMLImporter::divideByObject(const CEvaluationNode* pOrigNode, const CDataObject* pObject)
{
  bool reverse = false;
  CEvaluationNode* pResult = NULL;
  assert(pOrigNode != NULL);
  assert(pObject != NULL);

  if (pOrigNode != NULL && pObject != NULL)
    {
      // first we check if this is thie reverse operation with the object
      // if so, we just drop the reverse operaqtion, otherwise we apply the operation with the
      // object
      if (pOrigNode->mainType() == CEvaluationNode::MainType::OPERATOR &&
          pOrigNode->subType() == CEvaluationNode::SubType::MULTIPLY)
        {
          // either child can be the object
          const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pOrigNode->getChild());

          if (pChild->mainType() == CEvaluationNode::MainType::OBJECT && dynamic_cast<const CEvaluationNodeObject*>(pChild)->getData() == std::string("<" + pObject->getStringCN() + ">"))
            {

              pResult = dynamic_cast<const CEvaluationNode*>(pOrigNode->getChild())->copyBranch();
              reverse = true;
            }

          if (reverse == false)
            {
              pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());

              if (pChild->mainType() == CEvaluationNode::MainType::OBJECT && dynamic_cast<const CEvaluationNodeObject*>(pChild)->getData() == std::string("<" + pObject->getStringCN() + ">"))
                {

                  pResult = dynamic_cast<const CEvaluationNode*>(pOrigNode->getChild())->copyBranch();
                  reverse = true;
                }
            }
        }

      if (reverse == false)
        {
          CEvaluationNodeObject* pVolumeNode = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + pObject->getStringCN() + ">");
          pResult = new CEvaluationNodeOperator(CEvaluationNode::SubType::DIVIDE, "/");
          pResult->addChild(pOrigNode->copyBranch());
          pResult->addChild(pVolumeNode);
        }
    }

  return pResult;
}
/**
 * This method reads the notes from an arbitrate SBase object
 * and set them on the given CAnnotation instance.
 */
bool SBMLImporter::importNotes(CAnnotation* pAnno, const SBase* pSBase)
{
  bool result = true;

  if (pAnno == NULL || pSBase == NULL)
    return result;

  if (pSBase->isSetNotes())
    {

      std::string s = const_cast<SBase*>(pSBase)->getNotesString();
      size_t pos = s.find_first_not_of(" \n\t\r");

      if (pos != std::string::npos)
        {
          // the getNotesString method from libsbml seems to add the
          // <notes> tag to the string as well which is not OK, so we
          // have to remove it again.
          if (s.substr(pos, 6) == "<notes")
            {
              // find the closing bracket
              size_t pos2 = s.find(">", pos);
              assert(pos2 != std::string::npos);

              if (pos2 != std::string::npos && pos2 != (s.length() - 1))
                {
                  s = s.substr(pos2 + 1);
                }
              else
                {
                  return false;
                }

              // also remove the closing </notes> tag
              pos = s.rfind("</notes>");
              assert(pos != std::string::npos);

              if (pos != std::string::npos)
                {
                  s = s.substr(0, pos);
                }
              else
                {
                  return false;
                }
            }
          else if (s.substr(pos, 8) == "<notes/>")
            {
              // the notes element is empty
              return true;
            }
        }

      pAnno->setNotes(s);
    }

  const XMLNode* node = const_cast<SBase*>(pSBase)->getAnnotation();

  // more efficient to just check for NULL
  if (node == NULL)
    return result;

  for (unsigned int i = 0; i < node->getNumChildren(); ++i)
    {
      const XMLNode& current = node->getChild(i);

      // skip over all miriam and RDF stuff as that is handled elsewhere
      if (current.getName() == "RDF" || current.getName() == "COPASI")
        continue;

      const std::string & prefix = current.getPrefix();
      std::string nsUri = current.getNamespaceURI(prefix);

      if (nsUri.empty() && !prefix.empty())
        {
          // this is bad, libSBML really should let me know where the namespace is defined
          // it could be defined anywhere upwards of this xml element
          nsUri = node->getNamespaceURI(prefix);

          if (nsUri.empty() && pSBase->getSBMLDocument() != NULL)
            nsUri = pSBase->getSBMLDocument()->getSBMLNamespaces()->getNamespaces()->getURI(prefix);

          if (!nsUri.empty())
            {
              // we need to store the prefix on the element, as the COPASI object structure
              // does not support the annotation without prefix
              const_cast<XMLNode&>(current).addNamespace(nsUri, prefix);
            }
        }

      pAnno->addUnsupportedAnnotation(nsUri, current.toXMLString());
    }

  return result;
}

void SBMLImporter::deleteCopasiModel()
{
  if (this->mpCopasiModel != NULL)
    {
      delete this->mpCopasiModel;
      this->mpCopasiModel = NULL;
    }
}
