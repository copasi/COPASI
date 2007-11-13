// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLImporter.cpp,v $
//   $Revision: 1.182 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/13 13:48:30 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#ifdef WITH_LAYOUT
# define USE_LAYOUT 1
#endif // WITH_LAYOUT

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
#include <sbml/KineticLaw.h>
#include <sbml/math/FormulaFormatter.h>
#include <sbml/Model.h>
#include <sbml/UnitKind.h>
#include <sbml/Unit.h>
#include <sbml/Parameter.h>
#include <sbml/Rule.h>
#include <sbml/FunctionDefinition.h>
#include <sbml/units/Utils_UnitDefinition.h>

#include "copasi.h"

#include "mathematics.h"

#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CMetab.h"
#include "model/CReaction.h"
#include "model/CModelValue.h"
#include "copasi.h"
#include "function/CNodeK.h"
#include "function/CFunctionDB.h"
#include "function/CEvaluationTree.h"
#include "function/CExpression.h"
#include "report/CCopasiObjectReference.h"
#include "utilities/CCopasiTree.h"
#include "CopasiDataModel/CCopasiDataModel.h"

#include "SBMLImporter.h"
#include "ConverterASTNode.h"
#include "utilities/CProcessReport.h"

#ifdef WITH_LAYOUT
# include "layout/SBMLDocumentLoader.h"
# include "layout/CListOfLayouts.h"
#endif

#include "utilities/CCopasiMessage.h"

/**
 * This determines the relative difference two SBML Units can have for their
 * multiplier to be recognized as identical if everything else is the same.
 */
const double SBMLImporter::UNIT_MULTIPLIER_TOLERANCE = 1e-9;

/**
 * Creates and returns a Copasi CModel from the SBMLDocument given as argument.
 */
CModel* SBMLImporter::createCModelFromSBMLDocument(SBMLDocument* sbmlDocument, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  Model* sbmlModel = sbmlDocument->getModel();

  /* Create an empty model and set the title. */
  this->mpCopasiModel = new CModel();
  copasi2sbmlmap[this->mpCopasiModel] = sbmlModel;
  this->mpCopasiModel->setVolumeUnit(CModel::l);
  this->mpCopasiModel->setTimeUnit(CModel::s);
  this->mpCopasiModel->setQuantityUnit(CModel::Mol);
  /* Set standard units to match the standard units of SBML files. */

  if (sbmlModel->getNumUnitDefinitions() != 0)
    {
      unsigned int counter;
      for (counter = 0; counter < sbmlModel->getNumUnitDefinitions(); counter++)
        {
          UnitDefinition* uDef = sbmlModel->getUnitDefinition(counter);
          std::string unitId = uDef->getId();
          if (unitId == "substance")
            {
              this->mpCopasiModel->setQuantityUnit(this->handleSubstanceUnit(uDef).first);
            }
          else if (unitId == "time")
            {
              this->mpCopasiModel->setTimeUnit(this->handleTimeUnit(uDef).first);
            }
          else if (unitId == "volume")
            {
              this->mpCopasiModel->setVolumeUnit(this->handleVolumeUnit(uDef).first);
            }
          else if ((unitId == "area") || (unitId == "length"))
            {
              /* do nothing, but do not throw an exception either */
            }
        }
    }
  // go through all compartments and species and check if the units are
  // consistent
  checkElementUnits(sbmlModel, this->mpCopasiModel, mLevel, mVersion);
  std::string title;
  if (this->isStochasticModel(sbmlModel))
    {
      this->mpCopasiModel->setModelType(CModel::stochastic);
    }
  else
    {
      this->mpCopasiModel->setModelType(CModel::deterministic);
    }
  const XMLNode* comment = sbmlModel->getNotes();
  if (comment != NULL)
    {
      std::ostringstream stream;
      XMLOutputStream o(stream);
      o << * comment;
      this->mpCopasiModel->setComments(stream.str());
    }
  title = sbmlModel->getName();
  if (title == "")
    {
      title = "NoName";
    }
  this->mpCopasiModel->setTitle(title.c_str());

  /* import the functions */
  unsigned int counter;
  CCopasiVectorN< CEvaluationTree >* functions = &(this->functionDB->loadedFunctions());

  unsigned int num = (*functions).size();
  unsigned C_INT32 step = 0, totalSteps, hStep;
  if (mpImportHandler)
    {
      mImportStep = 1;
      if (!mpImportHandler->progress(mhImportStep)) return false;
      totalSteps = num;
      hStep = mpImportHandler->addItem("Importing function definitions",
                                       CCopasiParameter::UINT,
                                       & step,
                                       &totalSteps);
    }

  this->sbmlIdMap.clear();
  for (counter = 0; counter < num; ++counter)
    {
      CEvaluationTree* tree = (*functions)[counter];
      if (!tree->getSBMLId().empty())
        {
          this->sbmlIdMap[tree] = tree->getSBMLId();
          tree->setSBMLId("");
        }
    }

  num = sbmlModel->getNumFunctionDefinitions();

  CFunctionDB* pTmpFunctionDB = new CFunctionDB();
  for (counter = 0; counter < num;++counter)
    {
      FunctionDefinition* pSBMLFunDef = sbmlModel->getFunctionDefinition(counter);
      CFunction* pFun = this->createCFunctionFromFunctionDefinition(pSBMLFunDef, pTmpFunctionDB);
      copasi2sbmlmap[pFun] = pSBMLFunDef;
      this->mFunctionNameMapping[pSBMLFunDef->getId()] = pFun->getObjectName();
      ++step;
      if (mpImportHandler && !mpImportHandler->progress(hStep)) return false;
    }
  // now we go through all initial assignments, rules, constraints, kinetic
  // laws and events and replace function calls to functions in mExplicitelyTimeDependentFunctionDefinitions
  // by a call with the extra parameter that is the time.
  if (mExplicitelyTimeDependentFunctionDefinitions.size() != 0)
    {
      std::ostringstream sstream;
      std::set<std::string>::const_iterator it = mExplicitelyTimeDependentFunctionDefinitions.begin(), endit = mExplicitelyTimeDependentFunctionDefinitions.end();
      while (it != endit)
        {
          sstream << ", " << *it;
          ++it;
        }
      std::string reactionNames = sstream.str();
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 46 , reactionNames.substr(2, reactionNames.size()).c_str());
      ASTNode* pMathNode = NULL;
      if (sbmlDocument->getLevel() == 2 && sbmlDocument->getVersion() > 1)
        {
          num = sbmlModel->getNumInitialAssignments();
          for (counter = 0;counter < num;++counter)
            {
              pMathNode = const_cast<ASTNode*>(sbmlModel->getInitialAssignment(counter)->getMath());
              this->replaceTimeDependentFunctionCalls(pMathNode);
            }
          num = sbmlModel->getNumConstraints();
          for (counter = 0;counter < num;++counter)
            {
              pMathNode = const_cast<ASTNode*>(sbmlModel->getConstraint(counter)->getMath());
              this->replaceTimeDependentFunctionCalls(pMathNode);
            }
        }
      num = sbmlModel->getNumRules();
      for (counter = 0;counter < num;++counter)
        {
          pMathNode = const_cast<ASTNode*>(sbmlModel->getRule(counter)->getMath());
          this->replaceTimeDependentFunctionCalls(pMathNode);
        }
      num = sbmlModel->getNumReactions();
      for (counter = 0;counter < num;++counter)
        {
          KineticLaw* kLaw = sbmlModel->getReaction(counter)->getKineticLaw();
          if (kLaw)
            {
              pMathNode = const_cast<ASTNode*>(kLaw->getMath());
              this->replaceTimeDependentFunctionCalls(pMathNode);
            }
        }
      num = sbmlModel->getNumEvents();
      for (counter = 0;counter < num;++counter)
        {
          Event* pEvent = sbmlModel->getEvent(counter);
          const Trigger* pTrigger = pEvent->getTrigger();
          if (pTrigger != NULL)
            {
              pMathNode = const_cast<ASTNode*>(pTrigger->getMath());
              this->replaceTimeDependentFunctionCalls(pMathNode);
            }
          EventAssignment* pEventAssignment = NULL;
          unsigned int j, jMax = pEvent->getNumEventAssignments();
          for (j = 0;j < jMax;++j)
            {
              pEvent->getEventAssignment(j);
              if (pEventAssignment != NULL)
                {
                  pMathNode = const_cast<ASTNode*>(pEventAssignment->getMath());
                  this->replaceTimeDependentFunctionCalls(pMathNode);
                }
            }
        }
    }

  std::map<std::string, CCompartment*> compartmentMap;

  /* Create the compartments */
  num = sbmlModel->getNumCompartments();
  if (mpImportHandler)
    {
      mpImportHandler->finish(hStep);
      mImportStep = 3;
      if (!mpImportHandler->progress(mhImportStep)) return false;
      step = 0;
      totalSteps = num;
      hStep = mpImportHandler->addItem("Importing compartments...",
                                       CCopasiParameter::UINT,
                                       & step,
                                       &totalSteps);
    }

  for (counter = 0; counter < num; counter++)
    {
      Compartment* sbmlCompartment = sbmlModel->getCompartment(counter);
      if (sbmlCompartment == NULL)
        {
          fatalError();
        }
      CCompartment* copasiCompartment = this->createCCompartmentFromCompartment(sbmlCompartment, this->mpCopasiModel, copasi2sbmlmap, sbmlModel);
      std::string key = sbmlCompartment->getId();
      if (mLevel == 1)
        {
          key = sbmlCompartment->getName();
        }
      compartmentMap[key] = copasiCompartment;
      ++step;
      if (mpImportHandler && !mpImportHandler->progress(hStep)) return false;
    }

  /* Create all species */
  num = sbmlModel->getNumSpecies();
  if (mpImportHandler)
    {
      mpImportHandler->finish(hStep);
      mImportStep = 4;
      if (!mpImportHandler->progress(mhImportStep)) return false;
      step = 0;
      totalSteps = num;
      hStep = mpImportHandler->addItem("Importing species...",
                                       CCopasiParameter::UINT,
                                       & step,
                                       &totalSteps);
    }

  for (counter = 0; counter < num; ++counter)
    {
      Species* sbmlSpecies = sbmlModel->getSpecies(counter);
      if (sbmlSpecies == NULL)
        {
          fatalError();
        }
      CCompartment* copasiCompartment = compartmentMap[sbmlSpecies->getCompartment()];
      if (copasiCompartment != NULL)
        {
          CMetab* copasiMetabolite = this->createCMetabFromSpecies(sbmlSpecies, this->mpCopasiModel, copasiCompartment, copasi2sbmlmap, sbmlModel);
          std::string key;
          if (this->mLevel == 1)
            {
              key = sbmlSpecies->getName();
            }
          else
            {
              key = sbmlSpecies->getId();
            }
          this->speciesMap[key] = copasiMetabolite;
        }
      else
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 5 , sbmlSpecies->getCompartment().c_str(), sbmlSpecies->getId().c_str());
        }
      ++step;
      if (mpImportHandler && !mpImportHandler->progress(hStep)) return false;
    }

  /* Create the global Parameters */
  num = sbmlModel->getNumParameters();
  if (mpImportHandler)
    {
      mpImportHandler->finish(hStep);
      mImportStep = 5;
      if (!mpImportHandler->progress(mhImportStep)) return false;
      step = 0;
      totalSteps = num;
      hStep = mpImportHandler->addItem("Importing global parameters...",
                                       CCopasiParameter::UINT,
                                       & step,
                                       &totalSteps);
    }
  for (counter = 0; counter < num; ++counter)
    {
      Parameter* sbmlParameter = sbmlModel->getParameter(counter);
      if (sbmlParameter == NULL)
        {
          fatalError();
        }
      this->createCModelValueFromParameter(sbmlParameter, this->mpCopasiModel, copasi2sbmlmap);
      ++step;
      if (mpImportHandler && !mpImportHandler->progress(hStep)) return false;
    }
  if (sbmlModel->getNumInitialAssignments() > 0)
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 48);
    }

  /* Create the rules */
  this->areRulesUnique(sbmlModel);
  num = sbmlModel->getNumRules();
  if (mpImportHandler)
    {
      mpImportHandler->finish(hStep);
      mImportStep = 6;
      if (!mpImportHandler->progress(mhImportStep)) return false;
      step = 0;
      totalSteps = num;
      hStep = mpImportHandler->addItem("Importing global parameters...",
                                       CCopasiParameter::UINT,
                                       & step,
                                       &totalSteps);
    }
  for (counter = 0; counter < num; ++counter)
    {
      Rule* sbmlRule = sbmlModel->getRule(counter);
      if (sbmlRule == NULL)
        {
          fatalError();
        }
      this->importSBMLRule(sbmlRule, copasi2sbmlmap);
      ++step;
      if (mpImportHandler && !mpImportHandler->progress(hStep)) return false;
    }

  if (sbmlModel->getNumConstraints() > 0)
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 49);
    }
  /* Create all reactions */
  num = sbmlModel->getNumReactions();
  if (mpImportHandler)
    {
      mpImportHandler->finish(hStep);
      mImportStep = 7;
      if (!mpImportHandler->progress(mhImportStep)) return false;
      step = 0;
      totalSteps = num;
      hStep = mpImportHandler->addItem("Importing reactions...",
                                       CCopasiParameter::UINT,
                                       & step,
                                       &totalSteps);
    }
  this->mDivisionByCompartmentReactions.clear();
  for (counter = 0; counter < num; counter++)
    {
      this->createCReactionFromReaction(sbmlModel->getReaction(counter), sbmlModel, this->mpCopasiModel, copasi2sbmlmap, pTmpFunctionDB);
      ++step;
      if (mpImportHandler && !mpImportHandler->progress(hStep)) return false;
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
  this->mpCopasiModel->setCompileFlag();
  if (this->mUnsupportedRuleFound)
    {
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 3);
    }
  if (sbmlModel->getNumEvents() > 0)
    {
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 4);
    }

  if (mpImportHandler)
    {
      mpImportHandler->finish(hStep);
      mImportStep = 8;
      if (!mpImportHandler->progress(mhImportStep)) return false;
    }

  this->removeUnusedFunctions(pTmpFunctionDB, copasi2sbmlmap);

  // unset the hasOnlySubstanceUnits flag on all such species
  std::map<Species*, Compartment*>::iterator it = this->mSubstanceOnlySpecies.begin();
  std::map<Species*, Compartment*>::iterator endIt = this->mSubstanceOnlySpecies.end();
  while (it != endIt)
    {
      it->first->setHasOnlySubstanceUnits(false);
      ++it;
    }
  setInitialValues(this->mpCopasiModel, copasi2sbmlmap);

  delete pTmpFunctionDB;

  return this->mpCopasiModel;
}

CFunction* SBMLImporter::createCFunctionFromFunctionDefinition(const FunctionDefinition* sbmlFunction, CFunctionDB* pTmpFunctionDB)
{

  CFunction* pTmpFunction = this->createCFunctionFromFunctionTree(sbmlFunction);
  if (pTmpFunction)
    {
      pTmpFunction->setSBMLId(sbmlFunction->getId());
      std::string functionName = sbmlFunction->getName();
      if (functionName == "")
        {
          functionName = sbmlFunction->getId();
        }
      unsigned int counter = 2;
      std::ostringstream numberStream;
      std::string appendix = "";
      while (this->functionDB->findFunction(functionName + appendix))
        {
          numberStream.str("");
          numberStream << "_" << counter;
          counter++;
          appendix = numberStream.str();
        }
      pTmpFunction->setObjectName(functionName + appendix);
      pTmpFunctionDB->add(pTmpFunction, false);
      this->functionDB->add(pTmpFunction, true);
    }
  else
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 14, sbmlFunction->getId().c_str());
    }
  return pTmpFunction;
}

CFunction* SBMLImporter::createCFunctionFromFunctionTree(const FunctionDefinition* pSBMLFunction)
{
  CFunction* pFun = NULL;
  if (pSBMLFunction->isSetMath())
    {
      ConverterASTNode root(*pSBMLFunction->getMath());
      this->preprocessNode(&root);
      if (root.getType() == AST_LAMBDA)
        {
          // get the number of children.
          // the first n-1 children are the parameters for the function
          // the last child is the actual function
          pFun = new CKinFunction();
          unsigned int i, iMax = root.getNumChildren() - 1;
          std::set<std::string> variableNames;
          for (i = 0; i < iMax;++i)
            {
              ASTNode* pVarNode = root.getChild(i);
              if (pVarNode->getType() != AST_NAME)
                {
                  delete pFun;
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 12, pSBMLFunction->getId().c_str());
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
              pFun->addVariable(timeVariableName);
              this->mExplicitelyTimeDependentFunctionDefinitions.insert(pSBMLFunction->getId());
            }

          pFun->setTree(*root.getChild(iMax));
          CCopasiTree<CEvaluationNode>::iterator treeIt = pFun->getRoot();
          // if the root node already is an object node, this has to be dealt with separately
          if (dynamic_cast<CEvaluationNodeObject*>(&(*treeIt)))
            {
              CEvaluationNodeVariable* pVariableNode = new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, (*treeIt).getData().substr(1, (*treeIt).getData().length() - 2));
              pFun->setRoot(pVariableNode);
            }
          else
            {
              while (treeIt != NULL)
                {
                  if (dynamic_cast<CEvaluationNodeObject*>(&(*treeIt)))
                    {
                      CEvaluationNodeVariable* pVariableNode = new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, (*treeIt).getData().substr(1, (*treeIt).getData().length() - 2));
                      if ((*treeIt).getParent())
                        {
                          (*treeIt).getParent()->addChild(pVariableNode, &(*treeIt));
                          (*treeIt).getParent()->removeChild(&(*treeIt));
                        }
                      delete &(*treeIt);
                      treeIt = pVariableNode;
                    }
                  ++treeIt;
                }
            }
          pFun->updateTree();
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
        }
      else
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 11, pSBMLFunction->getId().c_str());
        }
    }
  return pFun;
}

/**
 * Creates and returns a Copasi CCompartment from the SBML Compartment
 * given as argument.
 */
CCompartment*
SBMLImporter::createCCompartmentFromCompartment(const Compartment* sbmlCompartment, CModel* copasiModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, const Model* /*pSBMLModel*/)
{
  if (sbmlCompartment->isSetUnits())
    {
      std::string cU = sbmlCompartment->getUnits();
      // this is now check in checkElementUnits
      //if (cU != "volume" /* && cU != "area" && cU != "length" */)
      //  {
      //    //fatalError();
      //    CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 24, sbmlCompartment->getId().c_str());
      //    const_cast<Compartment*>(sbmlCompartment)->unsetUnits();
      //}
      //else if (cU == "area" || cU == "length")
      //  {
      //    /* !!!! create a warning that the units will be ignored. */
      //    CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 22, sbmlCompartment->getId().c_str());
      //}
    }
  /* those are now checked in checkElementUnits
  if (sbmlCompartment->getSpatialDimensions() == 0)
    {
      CCopasiMessage Message(CCopasiMessage::EXCEPTION, MCSBML + 23, sbmlCompartment->getId().c_str());
    }
  if (sbmlCompartment->getSpatialDimensions() != 3)
    {
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 22, sbmlCompartment->getId().c_str());
    }
   */
  std::string name = sbmlCompartment->getName();
  if (name == "")
    {
      name = sbmlCompartment->getId();
    }
  std::string appendix = "";
  unsigned int counter = 2;
  std::ostringstream numberStream;
  while (copasiModel->getCompartments().getIndex(name + appendix) != static_cast < unsigned C_INT32
         > (-1))
    {
      numberStream.str("");
      numberStream << "_" << counter;
      counter++;
      appendix = numberStream.str();
    }
  double value;
  /*
  if (mLevel == 1)
    {
      value = sbmlCompartment->getVolume();
    }
  else
    {
      if (sbmlCompartment->isSetSize() && sbmlCompartment->getSize() == sbmlCompartment->getSize()) // make sure it is not set to NaN
        {
          value = sbmlCompartment->getSize();
        }
      else
        {
          // check if the size of the compartment is determined by a rule
          std::string sbmlId = sbmlCompartment->getId();
          bool ruleFound = false;
          unsigned int k, kMax = pSBMLModel->getNumRules();
          for (k = 0;k < kMax && !ruleFound;++k)
            {
              const Rule* pRule = pSBMLModel->getRule(k);
              switch (pRule->getTypeCode())
                {
                case SBML_ASSIGNMENT_RULE:
                  if (dynamic_cast<const AssignmentRule*>(pRule)->getVariable() == sbmlId)
                    {
                      ruleFound = true;
                      break;
                    }
                  break;
                case SBML_RATE_RULE:
                  if (dynamic_cast<const RateRule*>(pRule)->getVariable() == sbmlId)
                    {
                      ruleFound = true;
                      break;
                    }
                  break;
                case SBML_ALGEBRAIC_RULE:
                  break;
                default:
                  fatalError();
                  break;
                }
            }
          if (!ruleFound)
            {
              // go through all species of the model and check if the ones that are
              // in this compartment have the hasOnlySubstanceUnits flag set.
              const SBMLDocument* pSBMLDocument = sbmlCompartment->getSBMLDocument();
              assert(pSBMLDocument != NULL);
              const Model* pSBMLModel = pSBMLDocument->getModel();
              assert(pSBMLModel != NULL);
              bool onlySubstanceCompartment = true;
              unsigned int i, iMax = pSBMLModel->getNumSpecies();
              for (i = 0;i < iMax;++i)
                {
                  const Species* pSpecies = pSBMLModel->getSpecies(i);
                  if (pSpecies->getCompartment() == sbmlCompartment->getId() && pSpecies->getHasOnlySubstanceUnits() == false)
                    {
                      onlySubstanceCompartment = false;
                      break;
                    }
                }
              // Set value to NaN and create a warning if it is the first time
              // this happend
              if (onlySubstanceCompartment)
                {
                  value = 1.0;
                  CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 45, sbmlCompartment->getId().c_str());
                }
              else
                {
                  value = std::numeric_limits<C_FLOAT64>::quiet_NaN();
                  if (!this->mIncompleteModel)
                    {
                      this->mIncompleteModel = true;
                      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 7, sbmlCompartment->getId().c_str());
                    }
                }
            }
        }
    }
  */

  CCompartment* copasiCompartment = copasiModel->createCompartment(name + appendix, value);
  if (this->mLevel == 1)
    {
      copasiCompartment->setSBMLId(sbmlCompartment->getName());
    }
  else
    {
      copasiCompartment->setSBMLId(sbmlCompartment->getId());
    }
  //DebugFile << "Created Compartment: " << copasiCompartment->getObjectName() << std::endl;
  copasi2sbmlmap[copasiCompartment] = const_cast<Compartment*>(sbmlCompartment);
  return copasiCompartment;
}

/**
 * Creates and returns a Copasi CMetab from the given SBML Species object.
 */
CMetab*
SBMLImporter::createCMetabFromSpecies(const Species* sbmlSpecies, CModel* copasiModel, CCompartment* copasiCompartment, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, const Model* /*pSBMLModel*/)
{
  if (sbmlSpecies->isSetSubstanceUnits())
    {
      std::string cU = sbmlSpecies->getSubstanceUnits();
      /* this is now checked in checkElementUnits
      if (cU != "substance")
        {
          //fatalError();
          CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 25, sbmlSpecies->getId().c_str());
          const_cast<Species*>(sbmlSpecies)->unsetUnits();
        }
        */
    }
  std::map<CCopasiObject*, SBase*>::iterator it = copasi2sbmlmap.find(copasiCompartment);
  if (it == copasi2sbmlmap.end())
    {
      fatalError();
    }
  Compartment* pSBMLCompartment = (Compartment*)it->second;
  if (sbmlSpecies->getHasOnlySubstanceUnits() == true)
    {
      this->mSubstanceOnlySpecies.insert(std::make_pair(const_cast<Species*>(sbmlSpecies), pSBMLCompartment));
    }
  std::string name = sbmlSpecies->getName();
  if (name == "")
    {
      name = sbmlSpecies->getId();
    }
  std::string appendix = "";
  unsigned int counter = 2;
  std::ostringstream numberStream;
  while (copasiCompartment->getMetabolites().getIndex(name + appendix) != static_cast<unsigned C_INT32>(-1))
    {
      numberStream.str("");
      numberStream << "_" << counter;
      counter++;
      appendix = numberStream.str();
    }

  CMetab* copasiMetabolite = copasiModel->createMetabolite(name + appendix, copasiCompartment->getObjectName());
  if (copasiMetabolite == NULL)
    {
      //DebugFile << "Could not create Copasi metabolite." << std::endl;
      fatalError();
    }
  if (sbmlSpecies->getConstant() || sbmlSpecies->getBoundaryCondition())
    {
      copasiMetabolite->setStatus(CModelEntity::FIXED);
    }
  else
    {
      copasiMetabolite->setStatus(CModelEntity::REACTIONS);
    }
  // also check if the compartment has a spatialSize of 0 because this also implies hasOnlySubstanceUnits for the species in this compartment
  if (pSBMLCompartment->getSpatialDimensions() == 0)
    {
      this->mSubstanceOnlySpecies.insert(std::make_pair(const_cast<Species*>(sbmlSpecies), pSBMLCompartment));
    }

  /* The initial values are now set by a new routine after all other things
   * have been done.
  if (sbmlSpecies->isSetInitialAmount() && sbmlSpecies->getInitialAmount() == sbmlSpecies->getInitialAmount()) // make sure it's not set to NaN
    {
      if (sbmlSpecies->getInitialAmount() != 0.0)
        {
          copasiMetabolite->setInitialValue(sbmlSpecies->getInitialAmount()*copasiModel->getQuantity2NumberFactor()); // CHECK UNITS !!!
        }
      else
        {
          copasiMetabolite->setInitialConcentration(0.0);
        }
    }
  else if (sbmlSpecies->isSetInitialConcentration() && sbmlSpecies->getInitialConcentration() == sbmlSpecies->getInitialConcentration()) // make sure it is not set to NaN
    {
      if (sbmlSpecies->getHasOnlySubstanceUnits())
        {
          pdelete(copasiMetabolite);
          CCopasiMessage Message(CCopasiMessage::EXCEPTION, MCSBML + 20, sbmlSpecies->getId().c_str());
        }
      if (pSBMLCompartment->getSpatialDimensions() == 0)
        {
          pdelete(copasiMetabolite);
          CCopasiMessage Message(CCopasiMessage::EXCEPTION, MCSBML + 21, sbmlSpecies->getId().c_str());
        }
      copasiMetabolite->setInitialConcentration(sbmlSpecies->getInitialConcentration());      // CHECK UNITS !!!
    }
  else
    {
      copasiMetabolite->setInitialConcentration(std::numeric_limits<C_FLOAT64>::quiet_NaN());      // CHECK UNITS !!!
      std::string sbmlId = sbmlSpecies->getId();
      bool ruleFound = false;
      unsigned int k, kMax = pSBMLModel->getNumRules();
      for (k = 0;k < kMax && !ruleFound;++k)
        {
          const Rule* pRule = pSBMLModel->getRule(k);
          switch (pRule->getTypeCode())
            {
            case SBML_ASSIGNMENT_RULE:
              if (dynamic_cast<const AssignmentRule*>(pRule)->getVariable() == sbmlId)
                {
                  ruleFound = true;
                  break;
                }
              break;
            case SBML_RATE_RULE:
              if (dynamic_cast<const RateRule*>(pRule)->getVariable() == sbmlId)
                {
                  ruleFound = true;
                  break;
                }
              break;
            case SBML_ALGEBRAIC_RULE:
              break;
            default:
              fatalError();
              break;
            }
        }
      if (!this->mIncompleteModel && !ruleFound)
        {
          this->mIncompleteModel = true;
          CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 41, sbmlSpecies->getId().c_str());
        }
    }
    */
  //DebugFile << "Created metabolite: " << copasiMetabolite->getObjectName() << std::endl;
  copasi2sbmlmap[copasiMetabolite] = const_cast<Species*>(sbmlSpecies);
  if (this->mLevel == 1)
    {
      copasiMetabolite->setSBMLId(sbmlSpecies->getName());
    }
  else
    {
      copasiMetabolite->setSBMLId(sbmlSpecies->getId());
    }
  return copasiMetabolite;
}

/**
 * Creates and returns a Copasi CReaction object from the given SBML
 * Reaction object.
 */
CReaction*
SBMLImporter::createCReactionFromReaction(const Reaction* sbmlReaction, const Model* C_UNUSED(pSBMLModel), CModel* copasiModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, CFunctionDB* pTmpFunctionDB)
{
  if (sbmlReaction == NULL)
    {
      fatalError();
    }
  std::string name = sbmlReaction->getName();
  if (name == "")
    {
      name = sbmlReaction->getId();
    }
  /* Check if the name of the reaction is unique. */
  std::string appendix = "";
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
  if (copasiReaction == NULL)
    {
      fatalError();
    }
  if (sbmlReaction->isSetFast())
    {
      const_cast<Reaction*>(sbmlReaction)->setFast(false);
      if (!this->mFastReactionsEncountered)
        {
          this->mFastReactionsEncountered = true;
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 29);
        }
    }
  /* Add all substrates to the reaction */
  unsigned int num = sbmlReaction->getNumReactants();
  bool singleCompartment = true;
  const CCompartment* compartment = NULL;
  bool hasOnlySubstanceUnitPresent = false;
  for (counter = 0; counter < num; counter++)
    {
      const SpeciesReference* sr = sbmlReaction->getReactant(counter);
      if (sr == NULL)
        {
          delete copasiReaction;
          fatalError();
        }
      if (sr->isSetStoichiometryMath())
        {
          delete copasiReaction;
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 10);
        }
      float stoich = sr->getStoichiometry() / sr->getDenominator();
      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());
      if (pos == this->speciesMap.end())
        {
          delete copasiReaction;
          fatalError();
        }
      std::map<CCopasiObject*, SBase*>::const_iterator spos = copasi2sbmlmap.find(pos->second);
      assert(spos != copasi2sbmlmap.end());
      Species* pSBMLSpecies = dynamic_cast<Species*>(spos->second);
      assert(pSBMLSpecies != NULL);
      hasOnlySubstanceUnitPresent = (hasOnlySubstanceUnitPresent | (pSBMLSpecies->getHasOnlySubstanceUnits() == true));
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
      copasiReaction->addSubstrate(pos->second->getKey(), stoich);
    }

  /* Add all products to the reaction */
  num = sbmlReaction->getNumProducts();
  for (counter = 0; counter < num; counter++)
    {
      const SpeciesReference* sr = sbmlReaction->getProduct(counter);
      if (sr == NULL)
        {
          delete copasiReaction;
          fatalError();
        }
      if (sr->isSetStoichiometryMath())
        {
          delete copasiReaction;
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 10);
        }
      float stoich = sr->getStoichiometry() / sr->getDenominator();
      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());
      if (pos == this->speciesMap.end())
        {
          delete copasiReaction;
          fatalError();
        }
      std::map<CCopasiObject*, SBase*>::const_iterator spos = copasi2sbmlmap.find(pos->second);
      assert(spos != copasi2sbmlmap.end());
      Species* pSBMLSpecies = dynamic_cast<Species*>(spos->second);
      assert(pSBMLSpecies != NULL);
      hasOnlySubstanceUnitPresent = (hasOnlySubstanceUnitPresent | (pSBMLSpecies->getHasOnlySubstanceUnits() == true));
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
      copasiReaction->addProduct(pos->second->getKey(), stoich);
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
          delete copasiReaction;
          fatalError();
        }
      std::map<CCopasiObject*, SBase*>::const_iterator spos = copasi2sbmlmap.find(pos->second);
      assert(spos != copasi2sbmlmap.end());
      Species* pSBMLSpecies = dynamic_cast<Species*>(spos->second);
      assert(pSBMLSpecies != NULL);
      hasOnlySubstanceUnitPresent = (hasOnlySubstanceUnitPresent | (pSBMLSpecies->getHasOnlySubstanceUnits() == true));
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
      copasiReaction->addModifier(pos->second->getKey());
    }

  /* in the newly created CFunction set the types for all parameters and
   * either a mapping or a value
   */
  const KineticLaw* kLaw = sbmlReaction->getKineticLaw();
  if (kLaw != NULL)
    {
      /* this is now done in checkElementUnits
      if (kLaw->isSetSubstanceUnits())
        {
          std::string cU = kLaw->getSubstanceUnits();
          if (cU != "substance")
            {
              delete copasiReaction;
              CCopasiMessage Message(CCopasiMessage::EXCEPTION, MCSBML + 44, sbmlReaction->getId().c_str());
            }
        }
      if (kLaw->isSetTimeUnits())
        {
          std::string cU = kLaw->getTimeUnits();
          if (cU != "time")
            {
              delete copasiReaction;
              fatalError();
            }
        }
        */

      for (counter = 0; counter < kLaw->getNumParameters();++counter)
        {
          const Parameter* pSBMLParameter = kLaw->getParameter(counter);
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
              // this happend
              value = std::numeric_limits<C_FLOAT64>::quiet_NaN();
              if (!this->mIncompleteModel)
                {
                  this->mIncompleteModel = true;
                  CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 42, pSBMLParameter->getId().c_str());
                }
            }
          copasiReaction->getParameters().addParameter(id, CCopasiParameter::DOUBLE, value);
        }

      const ASTNode* kLawMath = kLaw->getMath();
      if (kLawMath == NULL)
        {
          fatalError();
        }
      else if (kLawMath->getType() == AST_UNKNOWN)
        {
          copasiReaction->setFunction(NULL);
          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 56, sbmlReaction->getId().c_str());
        }
      else
        {
          ConverterASTNode* node = new ConverterASTNode(*kLawMath);
          this->preprocessNode(node);

          if (node == NULL)
            {
              delete copasiReaction;
              fatalError();
            }

          this->replaceSubstanceOnlySpeciesNodes(node, mSubstanceOnlySpecies);

          /* if it is a single compartment reaction, we have to divide the whole kinetic
          ** equation by the compartment because copasi expects
          ** kinetic laws that specify concentration/time for single compartment
          ** reactions.
          */
          if (singleCompartment)
            {
              if (compartment != NULL)
                {
                  // check if the root node is a multiplication node and it's first child
                  // is a compartment node, if so, drop those two and make the second child
                  // new new root node
                  ConverterASTNode* tmpNode1 = this->isMultipliedByVolume(node, compartment->getSBMLId());
                  if (tmpNode1)
                    {
                      delete node;
                      node = tmpNode1;
                      if (node->getType() == AST_DIVIDE && node->getNumChildren() != 2)
                        {
                          delete tmpNode1;
                          fatalError();
                        }
                    }
                  else
                    {
                      tmpNode1 = new ConverterASTNode();
                      tmpNode1->setType(AST_DIVIDE);
                      tmpNode1->addChild(node);
                      ConverterASTNode* tmpNode2 = new ConverterASTNode();
                      tmpNode2->setType(AST_NAME);
                      tmpNode2->setName(compartment->getSBMLId().c_str());
                      tmpNode1->addChild(tmpNode2);
                      node = tmpNode1;
                      if (!hasOnlySubstanceUnitPresent && compartment->getInitialValue() == 1.0)
                        {
                          // we have to check if all species used in the reaction
                          // have the hasOnlySubstance flag set

                          if (node->getChild(0)->getType() == AST_FUNCTION && (!this->containsVolume(node->getChild(0), compartment->getSBMLId())))
                            {
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
          if (!sbmlId2CopasiCN(node, copasi2sbmlmap, copasiReaction->getParameters()))
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 27, copasiReaction->getObjectName().c_str());
            }
          CEvaluationNode* pExpressionTreeRoot = CEvaluationTree::convertASTNode(*node);
          delete node;
          node = NULL;
          if (pExpressionTreeRoot)
            {
              CEvaluationTree* pTmpTree = CEvaluationTree::create(CEvaluationTree::Expression);
              pTmpTree->setRoot(pExpressionTreeRoot);
              // check if the root node is a simple function call
              if (this->isSimpleFunctionCall(pExpressionTreeRoot))
                {
                  // if yes, we check if it corresponds to an already existing function
                  std::string functionName = pExpressionTreeRoot->getData();
                  CFunction* tree = dynamic_cast<CFunction*>(pTmpFunctionDB->findFunction(functionName));
                  assert(tree);
                  std::vector<CEvaluationNodeObject*>* v = this->isMassAction(tree, copasiReaction->getChemEq(), static_cast<const CEvaluationNodeCall*>(pExpressionTreeRoot));
                  if (!v)
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 27, copasiReaction->getObjectName().c_str());
                    }
                  if (!v->empty())
                    {
                      CFunction* pFun = NULL;
                      if (copasiReaction->isReversible())
                        {
                          pFun = static_cast<CFunction*>(this->functionDB->findFunction("Mass action (reversible)"));
                        }
                      else
                        {
                          pFun = static_cast<CFunction*>(this->functionDB->findFunction("Mass action (irreversible)"));
                        }
                      if (!pFun)
                        {
                          fatalError();
                        }
                      // do the mapping
                      CEvaluationNodeCall* pCallNode = new CEvaluationNodeCall(CEvaluationNodeCall::EXPRESSION, "dummy_call");
                      unsigned int i, iMax = v->size();
                      for (i = 0;i < iMax;++i)
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
                      CFunction* pExistingFunction = this->findCorrespondingFunction(tree, copasiReaction);
                      // if it does, we set the existing function for this reaction
                      if (pExistingFunction)
                        {
                          copasiReaction->setFunction(pExistingFunction);
                          // do the mapping
                          this->doMapping(copasiReaction, dynamic_cast<const CEvaluationNodeCall*>(pExpressionTreeRoot));
                        }
                      // else we take the function from the pTmpFunctionDB, copy it and set the usage correctly
                      else
                        {
                          // replace the variable nodes in tree with  nodes from
                          std::map<std::string, std::string > arguments;
                          const CFunctionParameters& funParams = tree->getVariables();
                          const CEvaluationNode* pTmpNode = static_cast<const CEvaluationNode*>(pExpressionTreeRoot->getChild());
                          unsigned int i, iMax = funParams.size();
                          for (i = 0;(i < iMax) && pTmpNode;++i)
                            {
                              if (!(pTmpNode->getType() == CEvaluationNode::OBJECT)) fatalError();
                              arguments[funParams[i]->getObjectName()] = pTmpNode->getData().substr(1, pTmpNode->getData().length() - 2);
                              pTmpNode = static_cast<const CEvaluationNode*>(pTmpNode->getSibling());
                            }
                          assert((i == iMax) && pTmpNode == NULL);
                          CEvaluationNode* pTmpExpression = this->variables2objects(tree->getRoot(), arguments);

                          CEvaluationTree* pTmpTree2 = CEvaluationTree::create(CEvaluationTree::Expression);
                          pTmpTree2->setRoot(pTmpExpression);
                          copasiReaction->setFunctionFromExpressionTree(pTmpTree2, copasi2sbmlmap, this->functionDB);
                          delete pTmpTree2;
                          if (copasiReaction->getFunction()->getType() == CEvaluationTree::UserDefined)
                            {
                              pTmpFunctionDB->add(const_cast<CFunction*>(copasiReaction->getFunction()), false);
                              this->mUsedFunctions.insert(copasiReaction->getFunction()->getObjectName());
                            }
                        }
                    }
                  pdelete(v);
                }
              else
                {
                  std::vector<CEvaluationNodeObject*>* v = this->isMassAction(pTmpTree, copasiReaction->getChemEq());
                  if (!v)
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 27, copasiReaction->getObjectName().c_str());
                    }
                  if (!v->empty())
                    {
                      CFunction* pFun = NULL;
                      if (copasiReaction->isReversible())
                        {
                          pFun = static_cast<CFunction*>(this->functionDB->findFunction("Mass action (reversible)"));
                        }
                      else
                        {
                          pFun = static_cast<CFunction*>(this->functionDB->findFunction("Mass action (irreversible)"));
                        }
                      if (!pFun)
                        {
                          fatalError();
                        }
                      // do the mapping
                      CEvaluationNodeCall* pCallNode = new CEvaluationNodeCall(CEvaluationNodeCall::EXPRESSION, "dummy_call");
                      unsigned int i, iMax = v->size();
                      for (i = 0;i < iMax;++i)
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
                      if (!copasiReaction->setFunctionFromExpressionTree(pTmpTree, copasi2sbmlmap, this->functionDB))
                        {
                          // error message
                          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 9, copasiReaction->getObjectName().c_str());
                        }
                      else
                        {
                          if (copasiReaction->getFunction()->getType() == CEvaluationTree::UserDefined)
                            {
                              pTmpFunctionDB->add(const_cast<CFunction*>(copasiReaction->getFunction()), false);
                              this->mUsedFunctions.insert(copasiReaction->getFunction()->getObjectName());
                            }
                        }
                    }
                  pdelete(v);
                }
              // delete the temporary tree and all the nodes
              delete pTmpTree;
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
SBMLImporter::getFunctionDefinitionForName(const std::string name, const Model* sbmlModel)
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

/**
 * Constructor that initializes speciesMap and the FunctionDB object
 */
SBMLImporter::SBMLImporter()
{
  this->speciesMap = std::map<std::string, CMetab*>();
  this->functionDB = NULL;
  this->mIncompleteModel = false;
  this->mUnsupportedRuleFound = false;
  this->mUnsupportedRateRuleFound = false;
  this->mUnsupportedAssignmentRuleFound = false;
  this->mpImportHandler = NULL;
  this->mFastReactionsEncountered = false;
  this->mIgnoredSBMLMessages.insert(10501);
  this->mIgnoredSBMLMessages.insert(10512);
  this->mIgnoredSBMLMessages.insert(10513);
  this->mIgnoredSBMLMessages.insert(10533);
  this->mIgnoredSBMLMessages.insert(10541);
  this->mIgnoredSBMLMessages.insert(10551);
  this->mIgnoredSBMLMessages.insert(10562);
}

/**
 * Destructor that does nothing.
 */
SBMLImporter::~SBMLImporter()
{}

/**
 * This functions replaces all species nodes for species that are in the substanceOnlySpeciesVector.
 * With the node multiplied by the volume of the species compartment.
 */
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

/**
 * Function reads an SBML file with libsbml and converts it to a Copasi CModel
 */
CModel* SBMLImporter::readSBML(std::string filename,
                               CFunctionDB* funDB,
                               SBMLDocument*& pSBMLDocument,
                               std::map<CCopasiObject*, SBase*>& copasi2sbmlmap
#ifdef WITH_LAYOUT
                               , CListOfLayouts *& prLol
#endif
)
{
  // convert filename to the locale encoding
  std::ifstream file(utf8ToLocale(filename).c_str());
  if (!file)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 50, filename.c_str());
    }
  std::ostringstream stringStream;
  char c;
  while (file.get(c))
    {
      stringStream << c;
    }
  file.clear();
  file.close();
  return this->parseSBML(stringStream.str(), funDB,
                         pSBMLDocument, copasi2sbmlmap
#ifdef WITH_LAYOUT
                         , prLol
#endif
);
}

/**
 * Function parses an SBML document with libsbml and converts it to a Copasi CModel
 * object which is returned. Deletion of the returned pointer is up to the
 * caller.
 */
CModel*
SBMLImporter::parseSBML(const std::string& sbmlDocumentText,
                        CFunctionDB* funDB,
                        SBMLDocument *& pSBMLDocument,
                        std::map<CCopasiObject*, SBase*>& copasi2sbmlmap
#ifdef WITH_LAYOUT
                        , CListOfLayouts *& prLol
#endif
)
{
  this->mFastReactionsEncountered = false;
  this->mpCopasiModel = NULL;
  if (funDB != NULL)
    {
      this->functionDB = funDB;
      SBMLReader* reader = new SBMLReader();

      mImportStep = 0;
      if (mpImportHandler)
        {
          mpImportHandler->setName("Importing SBML file...");
          mTotalSteps = 8;
          mhImportStep = mpImportHandler->addItem("Step",
                                                  CCopasiParameter::UINT,
                                                  & mImportStep,
                                                  &mTotalSteps);
        }

      SBMLDocument* sbmlDoc = reader->readSBMLFromString(sbmlDocumentText);
      if (sbmlDoc->checkConsistency() != 0)
        {
          int fatal = -1;
          unsigned int i, iMax = sbmlDoc->getNumErrors();
          for (i = 0;(i < iMax) && (fatal == -1);++i)
            {
              const XMLError* pSBMLError = sbmlDoc->getError(i);
              CCopasiMessage::Type messageType = CCopasiMessage::RAW;
              switch (pSBMLError->getSeverity())
                {
                case XMLError::Info:

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
                case XMLError::Warning:
                  if (mIgnoredSBMLMessages.find(pSBMLError->getErrorId()) != mIgnoredSBMLMessages.end())
                    {
                      messageType = CCopasiMessage::WARNING_FILTERED;
                    }
                  else
                    {
                      messageType = CCopasiMessage::WARNING;
                    }
                  CCopasiMessage(messageType, MCSBML + 40, "WARNING", pSBMLError->getErrorId(), pSBMLError->getLine(), pSBMLError->getColumn(), pSBMLError->getMessage().c_str());
                  break;
                case XMLError::Error:
                  if (mIgnoredSBMLMessages.find(pSBMLError->getErrorId()) != mIgnoredSBMLMessages.end())
                    {
                      messageType = CCopasiMessage::ERROR_FILTERED;
                    }
                  CCopasiMessage(messageType, MCSBML + 40, "ERROR", pSBMLError->getErrorId(), pSBMLError->getLine(), pSBMLError->getColumn(), pSBMLError->getMessage().c_str());
                  break;
                case XMLError::Fatal:
                  // treat unknown as fatal
                default:
                  //CCopasiMessage(CCopasiMessage::TRACE, MCSBML + 40,"FATAL",pSBMLError->getLine(),pSBMLError->getColumn(),pSBMLError->getMessage().c_str());
                  fatal = i;
                  break;
                }
              //std::cerr << pSBMLError->getMessage() << std::endl;
            }

          if (fatal != -1)
            {
              const XMLError* pSBMLError = sbmlDoc->getError(fatal);
              CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 2,
                                     pSBMLError->getLine(),
                                     pSBMLError->getColumn(),
                                     pSBMLError->getMessage().c_str());
              if (mpImportHandler) mpImportHandler->finish(mhImportStep);
              return NULL;
            }
        }
      /*
      else if (sbmlDoc->getNumErrors() > 0)
          {
          ParseMessage * pSBMLMessage = sbmlDoc->getError(0);
          // some level 1 files have an annotation in the wrong place
          // This is considered an error by libsbml, but
          // it does not really affect the model, so we try to
          // read it anyway.
          //
          if ((sbmlDoc->getNumErrors() > 1) ||
              (strncmp(pSBMLMessage->getMessage().c_str(),
                      "The <sbml> element cannot contain an <annotation>.  Use the <model> element instead."
                      , 85) != 0))
              {
              CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 2,
                                      pSBMLMessage->getLine(),
                                      pSBMLMessage->getColumn(),
                                      pSBMLMessage->getMessage().c_str());

              if (mpImportHandler) mpImportHandler->finish(mhImportStep);
              return NULL;
              }
          else
              {
              CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 6);
              }
          }
      */
      if (sbmlDoc->getModel() == NULL)
        {
          CCopasiMessage Message(CCopasiMessage::ERROR, MCSBML + 2);
          if (mpImportHandler) mpImportHandler->finish(mhImportStep);
          return NULL;
        }

      delete reader;
      pSBMLDocument = sbmlDoc;
      this->mLevel = pSBMLDocument->getLevel();
      this->mVersion = pSBMLDocument->getVersion();
      if (mLevel == 1)
        {
          unsigned int i, iMax = pSBMLDocument->getModel()->getNumCompartments();
          for (i = 0;i < iMax;++i)
            {
              Compartment* pCompartment = pSBMLDocument->getModel()->getCompartment(i);
              pCompartment->setSize(pCompartment->getVolume());
            }
          pSBMLDocument->setLevelAndVersion(2, 1);
          mLevel = pSBMLDocument->getLevel();
        }

      this->mpCopasiModel = this->createCModelFromSBMLDocument(sbmlDoc, copasi2sbmlmap);

#ifdef WITH_LAYOUT
      prLol = new CListOfLayouts();
      Model* sbmlmodel = pSBMLDocument->getModel();
      if (sbmlmodel && prLol)
        SBMLDocumentLoader::readListOfLayouts(*prLol,
                                              *sbmlmodel->getListOfLayouts(),
                                              copasi2sbmlmap);
#endif
    }
  else
    {
      //throw StdException("Error. readSBML needs a valid CFunctionDB object.");
      if (mpImportHandler) mpImportHandler->finish(mhImportStep);
      fatalError();
    }
  if (mpImportHandler) mpImportHandler->finish(mhImportStep);
  return this->mpCopasiModel;
}

/**
 * Returns the copasi QuantityUnit corresponding to the given SBML
 *  Substance UnitDefinition.
 */
std::pair<CModel::QuantityUnit, bool>
SBMLImporter::handleSubstanceUnit(const UnitDefinition* uDef)
{
  bool result = false;
  CModel::QuantityUnit qUnit = CModel::Mol;
  if (uDef == NULL)
    {
      //DebugFile << "Argument to handleSubstanceUnit is NULL pointer." << std::endl;
      fatalError();
    }
  if (uDef->getNumUnits() == 1)
    {
      const Unit* u = uDef->getUnit(0);
      if (u == NULL)
        {
          //DebugFile << "Expected Unit, got NULL pointer." << std::endl;
          fatalError();
        }
      if ((u->getKind() == UNIT_KIND_MOLE))
        {
          if ((u->getExponent() == 1) && (u->getMultiplier() == 1) && ((u->getScale() % 3) == 0) && (u->getScale() < 1) && (u->getScale() > -16))
            {
              switch (u->getScale())
                {
                case 0:
                  qUnit = CModel::Mol;
                  result = true;
                  break;
                case - 3:
                  qUnit = CModel::mMol;
                  result = true;
                  break;
                case - 6:
                  qUnit = CModel::microMol;
                  result = true;
                  break;
                case - 9:
                  qUnit = CModel::nMol;
                  result = true;
                  break;
                case - 12:
                  qUnit = CModel::pMol;
                  result = true;
                  break;
                case - 15:
                  qUnit = CModel::fMol;
                  result = true;
                  break;
                default:
                  //DebugFile << "Error. This value should never have been reached for the scale of the liter unit." << std::endl;
                  exit(1);
                  break;
                }
            }
          else
            {
              fatalError();
            }
        }
      else if ((u->getKind() == UNIT_KIND_ITEM))
        {
          if ((u->getExponent() == 1) && (u->getMultiplier() == 1) && (u->getScale() == 0 || u->getScale() == 1))
            {
              if (u->getScale() == 1)
                {
                  CCopasiMessage Message(CCopasiMessage::ERROR, MCSBML + 30);
                }
              else
                {
                  result = true;
                  qUnit = CModel::number;
                }
            }
          else
            {
              fatalError();
            }
        }
      else
        {
          fatalError();
        }
    }
  else
    {
      fatalError();
    }
  return std::make_pair(qUnit, result);
}

/**
 * Returns the copasi TimeUnit corresponding to the given SBML Time
 *  UnitDefinition.
 */
std::pair<CModel::TimeUnit, bool>
SBMLImporter::handleTimeUnit(const UnitDefinition* uDef)
{
  bool result = false;
  CModel::TimeUnit tUnit = CModel::s;
  if (uDef == NULL)
    {
      //DebugFile << "Argument to handleTimeUnit is NULL pointer." << std::endl;
      fatalError();
    }
  if (uDef->getNumUnits() == 1)
    {
      const Unit* u = uDef->getUnit(0);
      if (u == NULL)
        {
          //DebugFile << "Expected Unit, got NULL pointer." << std::endl;
          fatalError();
        }
      if ((u->getKind() == UNIT_KIND_SECOND))
        {
          if ((u->getExponent() == 1) && ((u->getScale() % 3) == 0) && (u->getScale() < 1) && (u->getScale() > -16))
            {
              if (u->getMultiplier() == 1.0)
                {
                  switch (u->getScale())
                    {
                    case 0:
                      tUnit = CModel::s;
                      result = true;
                      break;
                    case - 3:
                      tUnit = CModel::ms;
                      result = true;
                      break;
                    case - 6:
                      tUnit = CModel::micros;
                      result = true;
                      break;
                    case - 9:
                      tUnit = CModel::ns;
                      result = true;
                      break;
                    case - 12:
                      tUnit = CModel::ps;
                      result = true;
                      break;
                    case - 15:
                      tUnit = CModel::fs;
                      result = true;
                      break;
                    default:
                      //DebugFile << "Error. This value should never have been reached for the scale of the time unit." << std::endl;
                      exit(1);
                      break;
                    }
                }
              else if (u->getMultiplier() == 60.0)
                {
                  tUnit = CModel::min;
                  result = true;
                }
              else if (u->getMultiplier() == 3600.0)
                {
                  tUnit = CModel::h;
                  result = true;
                }
              else if (u->getMultiplier() == 86400.0)
                {
                  tUnit = CModel::d;
                  result = true;
                }
              else
                {
                  fatalError();
                }
            }
          else
            {
              fatalError();
            }
        }
      else
        {
          fatalError();
        }
    }
  else
    {
      fatalError();
    }
  return std::make_pair(tUnit, result);
}

/**
 * Returns the copasi VolumeUnit corresponding to the given SBML Volume
 *  UnitDefinition.
 */
std::pair<CModel::VolumeUnit, bool>
SBMLImporter::handleVolumeUnit(const UnitDefinition* uDef)
{
  // TODO maybe we should simplify the Unitdefiniton first if this normalizes
  // the scale and the multiplier
  bool result = false;
  const double TOLERANCE = 1e-25;
  CModel::VolumeUnit vUnit = CModel::l;
  if (uDef == NULL)
    {
      //DebugFile << "Argument to handleVolumeUnit is NULL pointer." << std::endl;
      fatalError();
    }
  if (uDef->getNumUnits() == 1)
    {
      const Unit* u = uDef->getUnit(0);
      if (u == NULL)
        {
          //DebugFile << "Expected Unit, got NULL pointer." << std::endl;
          fatalError();
        }
      if ((u->getKind() == UNIT_KIND_LITER) || (u->getKind() == UNIT_KIND_LITRE))
        {
          if ((u->getExponent() == 1) && (u->getMultiplier() - 1.0 < TOLERANCE) && ((u->getScale() % 3) == 0) && (u->getScale() < 1) && (u->getScale() > -16))
            {
              switch (u->getScale())
                {
                case 0:
                  vUnit = CModel::l;
                  result = true;
                  break;
                case - 3:
                  vUnit = CModel::ml;
                  result = true;
                  break;
                case - 6:
                  vUnit = CModel::microl;
                  result = true;
                  break;
                case - 9:
                  vUnit = CModel::nl;
                  result = true;
                  break;
                case - 12:
                  vUnit = CModel::pl;
                  result = true;
                  break;
                case - 15:
                  vUnit = CModel::fl;
                  result = true;
                  break;
                default:
                  //DebugFile << "Error. This value should never have been reached for the scale of the liter unit." << std::endl;
                  exit(1);
                  break;
                }
            }
          else
            {
              fatalError();
            }
        }
      else if ((u->getKind() == UNIT_KIND_METER) || (u->getKind() == UNIT_KIND_METRE))
        {
          if (u->getExponent() == 3)
            {
              if ((fabs(u->getMultiplier()) - 1.0 < TOLERANCE) &&
                  (u->getScale() == 0))
                {
                  vUnit = CModel::m3;
                  result = true;
                }
              else
                {
                  // try to convert to liter
                  Unit* pLitreUnit = convertSBMLCubicmetresToLitres(u);
                  if (pLitreUnit != NULL &&
                      pLitreUnit->getExponent() == 1 &&
                      (pLitreUnit->getScale() % 3 == 0) &&
                      (pLitreUnit->getScale() < 1) &&
                      (pLitreUnit->getScale() > -16) &&
                      fabs(pLitreUnit->getMultiplier()) - 1.0 < TOLERANCE)
                    {
                      switch (pLitreUnit->getScale())
                        {
                        case 0:
                          vUnit = CModel::l;
                          result = true;
                          break;
                        case - 3:
                          vUnit = CModel::ml;
                          result = true;
                          break;
                        case - 6:
                          vUnit = CModel::microl;
                          result = true;
                          break;
                        case - 9:
                          vUnit = CModel::nl;
                          result = true;
                          break;
                        case - 12:
                          vUnit = CModel::pl;
                          result = true;
                          break;
                        case - 15:
                          vUnit = CModel::fl;
                          result = true;
                          break;
                        default:
                          CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 54, uDef->getId().c_str());
                          break;
                        }
                    }
                  delete pLitreUnit;
                }
            }
          else
            {
              CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 54, uDef->getId().c_str());
            }
        }
      else
        {
          CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 54, uDef->getId().c_str());
        }
    }
  else
    {
      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 54, uDef->getId().c_str());
    }
  return std::make_pair(vUnit, result);
}

CModelValue* SBMLImporter::createCModelValueFromParameter(const Parameter* sbmlParameter, CModel* copasiModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  if (sbmlParameter->isSetUnits())
    {
      /* !!!! create a warning that the units will be ignored. */
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 26, sbmlParameter->getId().c_str());
      const_cast<Parameter*>(sbmlParameter)->unsetUnits();
    }
  std::string name = sbmlParameter->getName();
  if (!sbmlParameter->isSetName())
    {
      name = sbmlParameter->getId();
    }
  std::string appendix = "";
  unsigned int counter = 2;
  std::ostringstream numberStream;
  while (copasiModel->getModelValues().getIndex(name + appendix) != static_cast < unsigned C_INT32
         > (-1))
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
  /*
  double value;
  if (sbmlParameter->isSetValue() && sbmlParameter->getValue() == sbmlParameter->getValue()) // make sure it is not set to NaN
      {
      value = sbmlParameter->getValue();
      }
  else
      {
      // check if there is an assignment rule for this entity
      std::map<CCopasiObject*, SBase*>::iterator pos = copasi2sbmlmap.find(copasiModel);
      if (pos == copasi2sbmlmap.end()) fatalError();
      bool ruleFound = false;
      Model* pSBMLModel = dynamic_cast<Model*>(pos->second);
      unsigned int k, kMax = pSBMLModel->getNumRules();
      for (k = 0;k < kMax && !ruleFound;++k)
          {
          Rule* pRule = pSBMLModel->getRule(k);
          switch (pRule->getTypeCode())
              {
              case SBML_ASSIGNMENT_RULE:
              if (dynamic_cast<AssignmentRule*>(pRule)->getVariable() == sbmlId)
                  {
                  ruleFound = true;
                  break;
                  }
              break;
              case SBML_RATE_RULE:
              if (dynamic_cast<RateRule*>(pRule)->getVariable() == sbmlId)
                  {
                  ruleFound = true;
                  break;
                  }
              break;
              case SBML_ALGEBRAIC_RULE:
              break;
              default:
              fatalError();
              break;
              }
          }

      // Set value to NaN and create a warning if it is the first time
      // this happend
      value = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      if ((!ruleFound) && (!this->mIncompleteModel))
          {
          this->mIncompleteModel = true;
          CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 43, sbmlParameter->getId().c_str());
          }
      }
      */
  CModelValue* pMV = copasiModel->createModelValue(name + appendix, /*value*/ 0.0);
  copasi2sbmlmap[pMV] = const_cast<Parameter*>(sbmlParameter);
  pMV->setSBMLId(sbmlId);
  return pMV;
}

bool SBMLImporter::sbmlId2CopasiCN(ASTNode* pNode, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, CCopasiParameterGroup& pParamGroup)
{
  bool success = true;
  unsigned int i, iMax = pNode->getNumChildren();
  if (pNode->getType() == AST_NAME)
    {
      Compartment* pSBMLCompartment = NULL;
      Species* pSBMLSpecies = NULL;
      Reaction* pSBMLReaction = NULL;
      Parameter* pSBMLParameter = NULL;
      std::string sbmlId;
      CCopasiParameter* pParam = pParamGroup.getParameter(pNode->getName());
      if (pParam)
        {
          pNode->setName(pParam->getCN().c_str());
        }
      else
        {
          std::map<CCopasiObject*, SBase*>::iterator it = copasi2sbmlmap.begin();
          std::map<CCopasiObject*, SBase*>::iterator endIt = copasi2sbmlmap.end();
          bool found = false;
          while (it != endIt)
            {
              SBMLTypeCode_t type = it->second->getTypeCode();
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
                      pNode->setName(dynamic_cast<CCompartment*>(it->first)->getObject(CCopasiObjectName("Reference=InitialVolume"))->getCN().c_str());
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
                      pNode->setName(dynamic_cast<CMetab*>(it->first)->getObject(CCopasiObjectName("Reference=InitialConcentration"))->getCN().c_str());
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
                      pNode->setName(dynamic_cast<CReaction*>(it->first)->getObject(CCopasiObjectName("Reference=ParticleFlux"))->getCN().c_str());
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
                      pNode->setName(dynamic_cast<CModelValue*>(it->first)->getObject(CCopasiObjectName("Reference=Value"))->getCN().c_str());
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
  for (i = 0; i < iMax;++i)
    {
      if (!this->sbmlId2CopasiCN(pNode->getChild(i), copasi2sbmlmap, pParamGroup))
        {
          success = false;
          break;
        }
    }
  return success;
}

void SBMLImporter::printMap(const std::map<CCopasiObject*, SBase*> & copasi2sbml)
{
  std::map<CCopasiObject*, SBase*>::const_iterator it = copasi2sbml.begin();
  std::map<CCopasiObject*, SBase*>::const_iterator end = copasi2sbml.end();
  std::cout << "Number of elements: " << copasi2sbml.size() << std::endl;
  while (it != end)
    {
      std::cout << "(@" << it->first << ")" << it->first->getObjectName() << " : " << "(@" << it->second << ")" << it->second->getTypeCode() << std::endl;
      ++it;
    }
  std::cout << std::endl;
}

void SBMLImporter::restoreFunctionDB()
{
  // set all the old sbml ids
  std::map<CEvaluationTree*, std::string>::iterator it = this->sbmlIdMap.begin();
  std::map<CEvaluationTree*, std::string>::iterator endIt = this->sbmlIdMap.end();
  while (it != endIt)
    {
      it->first->setSBMLId(it->second);
      ++it;
    }

  // remove all the functions that were added during import
  std::set<std::string>::iterator it2 = this->mUsedFunctions.begin();
  std::set<std::string>::iterator endIt2 = this->mUsedFunctions.end();
  while (it2 != endIt2)
    {
      CEvaluationTree* pTree = this->functionDB->findFunction(*it2);
      assert(pTree);
      this->functionDB->removeFunction(pTree->getKey());
      ++it2;
    }
}

void SBMLImporter::preprocessNode(ConverterASTNode* pNode)
{
  // this function goes through the tree three times.
  // this can probably be handled more intelligently
  this->isDelayFunctionUsed(pNode);
  this->replaceCallNodeNames(pNode);
  this->replaceTimeNodeNames(pNode);
}

void SBMLImporter::isDelayFunctionUsed(ConverterASTNode* pNode)
{
  if (!pNode) return;
  if (pNode->getType() == AST_FUNCTION_DELAY)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 36);
    }
  else
    {
      // go through all children and replace the time nodes names
      unsigned int i, iMax = pNode->getNumChildren();
      for (i = 0;i < iMax;++i)
        {
          this->isDelayFunctionUsed(dynamic_cast<ConverterASTNode*>(pNode->getChild(i)));
        }
    }
}

void SBMLImporter::replaceTimeNodeNames(ConverterASTNode* pNode)
{
  if (!pNode) return;
  if (pNode->getType() == AST_NAME_TIME)
    {
      pNode->setName(this->mpCopasiModel->getCN().c_str());
    }
  else
    {
      // go through all children and replace the time nodes names
      unsigned int i, iMax = pNode->getNumChildren();
      for (i = 0;i < iMax;++i)
        {
          this->replaceTimeNodeNames(dynamic_cast<ConverterASTNode*>(pNode->getChild(i)));
        }
    }
}

void SBMLImporter::replaceCallNodeNames(ConverterASTNode* pNode)
{
  if (pNode)
    {
      if (pNode->getType() == AST_FUNCTION)
        {
          std::map<std::string, std::string>::const_iterator pos = this->mFunctionNameMapping.find(pNode->getName());

          if (pos == this->mFunctionNameMapping.end())
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 47, pNode->getName());
            }
          std::string newName = pos->second;
          pNode->setName(newName.c_str());
          this->mUsedFunctions.insert(newName);
        }
      // go through all children and also replace the call node names
      unsigned int i, iMax = pNode->getNumChildren();
      for (i = 0;i < iMax;++i)
        {
          this->replaceCallNodeNames(dynamic_cast<ConverterASTNode*>(pNode->getChild(i)));
        }
    }
}

/**
 * The methods gets a function where all the parameters have a usage of "PARAMETER".
 * In addition it get the root node of a call to that function which is an expression
 * and contains the acutal objects with which the function is called in a certain reaction.
 * From this expression we can determine if there already is a function in the database
 * that does the same. Or we can find out if this function is a Mass Action kinetic.
 */
CFunction* SBMLImporter::findCorrespondingFunction(const CFunction* tree, const CReaction* pCopasiReaction)
{
  CFunction* pCorrespondingFunction = NULL;
  std::vector<CFunction*> functions = this->functionDB->suitableFunctions(
                                        pCopasiReaction->getChemEq().getSubstrates().size(),
                                        pCopasiReaction->getChemEq().getProducts().size(),
                                        pCopasiReaction->isReversible() ? TriTrue : TriFalse);
  unsigned int i, iMax = functions.size();
  for (i = 0; i < iMax;++i)
    {
      CFunction* pFun = (functions[i]);
      // make sure the function is not compared to itself since it can already
      // be in the database if it has been used a call in another function
      // don't compare the mass action kinetics
      if ((pFun != tree) && (!dynamic_cast<CMassAction*>(pFun)) && this->areEqualFunctions(pFun, tree))
        {
          pCorrespondingFunction = pFun;
          break;
        }
    }
  return pCorrespondingFunction;
}

bool SBMLImporter::areEqualFunctions(const CFunction* pFun, const CFunction* pFun2)
{
  bool result = true;
  const CFunctionParameters& funParams1 = pFun->getVariables();
  const CFunctionParameters& funParams2 = pFun2->getVariables();
  if (funParams1.size() == funParams2.size())
    {
      unsigned int i, iMax = funParams1.size();
      for (i = 0; i < iMax;++i)
        {
          const CFunctionParameter* pFunParam1 = funParams1[i];
          const CFunctionParameter* pFunParam2 = funParams2[i];
          if (pFunParam1->getObjectName() != pFunParam2->getObjectName())
            {
              result = false;
              break;
            }
        }
      if (result == true)
        {
          const CEvaluationNode* pNodeFun1 = static_cast<const CEvaluationNode*>(pFun->getRoot());
          const CEvaluationNode* pNodeFun2 = static_cast<const CEvaluationNode*>(pFun2->getRoot());
          result = this->areEqualSubtrees(pNodeFun1, pNodeFun2);
        }
    }
  else
    {
      result = false;
    }
  return result;
}

bool SBMLImporter::areEqualSubtrees(const CEvaluationNode* pNode1, const CEvaluationNode* pNode2)
{
  bool result = ((pNode1->getType() == pNode2->getType()) && (pNode1->getData() == pNode2->getData()));
  const CEvaluationNode* pChild1 = static_cast<const CEvaluationNode*>(pNode1->getChild());
  const CEvaluationNode* pChild2 = static_cast<const CEvaluationNode*>(pNode2->getChild());
  while (result && pChild1 && pChild2)
    {
      result = this->areEqualSubtrees(pChild1, pChild2);
      pChild1 = static_cast<const CEvaluationNode*>(pChild1->getSibling());
      pChild2 = static_cast<const CEvaluationNode*>(pChild2->getSibling());
    }
  result = (result && !pChild1 && !pChild2);
  return result;
}

std::vector<CEvaluationNodeObject*>* SBMLImporter::isMassAction(const CEvaluationTree* pTree, const CChemEq& chemicalEquation, const CEvaluationNodeCall* pCallNode)
{
  CEvaluationTree::Type type = pTree->getType();
  std::vector< std::vector< std::string > > functionArgumentCNs;
  const CEvaluationNode* pChildNode = NULL;
  std::string str;
  std::vector<CEvaluationNodeObject*>* result = NULL;
  switch (type)
    {
    case CEvaluationTree::Function:
    case CEvaluationTree::UserDefined:
      pChildNode = static_cast<const CEvaluationNode*>(pCallNode->getChild());
      while (pChildNode)
        {
          if (pChildNode->getType() == CEvaluationNode::OBJECT)
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
      // the root node must be a minus operator
      // the two children must be irreversible mass action terms
      result = (CEvaluationNode::type(pRootNode->getType()) == CEvaluationNode::OPERATOR && (CEvaluationNodeOperator::SubType)(CEvaluationNode::subType(pRootNode->getType())) == CEvaluationNodeOperator::MINUS);
      if (result)
        {
          const CEvaluationNode* pChildNode = static_cast<const CEvaluationNode*>(pRootNode->getChild());
          result = (pChildNode != NULL);
          if (result)
            {
              CChemEq tmpEq;
              const CCopasiVector<CChemEqElement>* metabolites = &chemicalEquation.getSubstrates();
              unsigned int i, iMax = metabolites->size();
              result = (iMax > 0);
              if (result)
                {
                  for (i = 0;i < iMax;++i)
                    {
                      const CChemEqElement* element = (*metabolites)[i];
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
                          for (i = 0;i < iMax;++i)
                            {
                              const CChemEqElement* element = (*metabolites)[i];
                              tmpEq2.addMetabolite(element->getMetaboliteKey(), element->getMultiplicity(), CChemEq::SUBSTRATE);
                            }
                          std::vector<CEvaluationNodeObject*>* v2 = this->isMassActionExpression(pChildNode, tmpEq2);
                          if (!v2)
                            {
                              fatalError();
                            }
                          result = !v2->empty();
                          if (result)
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
    }
  else
    {
      // the expression must contain exactly one global or local parameter
      // the expression must contain each substrate in the CChemicalReaction
      std::vector<const CEvaluationNode*> arguments;
      std::map<const CMetab*, C_FLOAT64> multiplicityMap;
      this->separateProductArguments(pRootNode, arguments);
      unsigned int numParameters = 0, i, iMax = arguments.size();
      v = new std::vector<CEvaluationNodeObject*>;
      if (iMax != 0)
        {
          std::vector<CCopasiContainer*> listOfContainers;
          listOfContainers.push_back(this->mpCopasiModel);
          for (i = 0;(i < iMax) && (numParameters < 2);++i)
            {
              const CEvaluationNode* pNode = arguments[i];
              // the node can either be an object node
              // or it can be a power function node
              if (pNode->getType() == CEvaluationNode::OBJECT)
                {
                  // it can be a global or a local parameter or an metabolite
                  std::string objectCN = pNode->getData().substr(1, pNode->getData().length() - 2);
                  const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
                  if (!pObject)
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 39, objectCN.c_str());
                    }
                  if (pObject->isReference())
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
                          v->push_back(new CEvaluationNodeObject((CEvaluationNodeObject::SubType)(CEvaluationNode::subType(pNode->getType())), pNode->getData()));
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
                      v->push_back(new CEvaluationNodeObject((CEvaluationNodeObject::SubType)(CEvaluationNode::subType(pNode->getType())), pNode->getData()));
                    }
                  else
                    {
                      result = false;
                      break;
                    }
                }
              else if (pNode->getType() == CEvaluationNode::OPERATOR && (CEvaluationNodeOperator::SubType)(CEvaluationNode::subType(pNode->getType())) == CEvaluationNodeOperator::POWER)
                {
                  // the two children must be a metabolite node and a number node in this order
                  const CEvaluationNode* pChildNode = static_cast<const CEvaluationNode*>(pNode->getChild());
                  if (pChildNode->getType() == CEvaluationNode::OBJECT)
                    {
                      std::string objectCN = pChildNode->getData().substr(1, pChildNode->getData().length() - 2);
                      const CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
                      assert(pObject);
                      if (pObject->isReference())
                        {
                          pObject = pObject->getObjectParent();
                          if (dynamic_cast<const CMetab*>(pObject))
                            {
                              pChildNode = static_cast<const CEvaluationNode*>(pChildNode->getSibling());
                              assert(pChildNode);
                              if (CEvaluationNode::type(pChildNode->getType()) == CEvaluationNode::NUMBER)
                                {
                                  const CMetab* pMetab = static_cast<const CMetab*>(pObject);
                                  if (multiplicityMap.find(pMetab) != multiplicityMap.end())
                                    {
                                      multiplicityMap[pMetab] = multiplicityMap[pMetab] + pChildNode->value();
                                    }
                                  else
                                    {
                                      multiplicityMap[pMetab] = pChildNode->value();
                                    }
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
          const CCopasiVector<CChemEqElement>& metabolites = chemicalEquation.getSubstrates();
          unsigned i, iMax = metabolites.size();
          // all metabolites must occur in the muliplicityMap so they have to have the same size
          if (iMax != multiplicityMap.size()) result = false;
          for (i = 0;i < iMax && result;++i)
            {
              // the metabolite has to be present in the multiplicityMap, otherwise it is not a mass action
              // the stoichiometry also has to fit
              std::map<const CMetab*, C_FLOAT64>::iterator pos = multiplicityMap.find(metabolites[i]->getMetabolite());
              if (pos == multiplicityMap.end() ||
                  fabs(pos->second - metabolites[i]->getMultiplicity()) >= 0.01)
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
      std::map<std::string , std::string> variable2CNMap;
      unsigned int i, iMax = pFunParams.size();
      for (i = 0;i < iMax;++i)
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
  const CEvaluationNodeOperator* pMultiplyNode = dynamic_cast<const CEvaluationNodeOperator*>(pRootNode);
  if (pMultiplyNode && (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pMultiplyNode->getType())) == CEvaluationNodeOperator::MULTIPLY))
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
          else if (pOperatorNode && (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pOperatorNode->getType())) == CEvaluationNodeOperator::POWER))
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
  std::vector<CCopasiContainer*> listOfContainers = std::vector<CCopasiContainer*>();
  listOfContainers.push_back(this->mpCopasiModel);
  CChemEq& pChemEq = pCopasiReaction->getChemEq();
  std::map<const CChemEqElement*, CChemEq::MetaboliteRole> v;
  const CCopasiVector<CChemEqElement>* pV = &pChemEq.getSubstrates();
  unsigned int i, iMax = pV->size();
  for (i = 0; i < iMax;++i)
    {
      v[(*pV)[i]] = CChemEq::SUBSTRATE;
    }
  pV = &pChemEq.getProducts();
  iMax = pV->size();
  for (i = 0; i < iMax;++i)
    {
      v[(*pV)[i]] = CChemEq::PRODUCT;
    }
  pV = &pChemEq.getModifiers();
  iMax = pV->size();
  for (i = 0; i < iMax;++i)
    {
      v[(*pV)[i]] = CChemEq::MODIFIER;
    }
  unsigned int parameterIndex = 0;
  while (pChildNode)
    {
      const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pChildNode);
      if (!pObjectNode)
        {
          fatalError();
        }
      const CCopasiObject* object = CCopasiContainer::ObjectFromName(listOfContainers, pObjectNode->getData().substr(1, pObjectNode->getData().length() - 2));
      if (!object)
        {
          fatalError();
        }
      CFunctionParameter* pFunParam = const_cast<CFunctionParameter*>(pCopasiReaction->getFunction()->getVariables()[parameterIndex]);

      if (dynamic_cast<const CCopasiObjectReference<C_FLOAT64>*>(object))
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
                          pFunParam->setUsage(CFunctionParameter::SUBSTRATE);
                          break;
                        case CChemEq::PRODUCT:
                          // it is a product
                          pFunParam->setUsage(CFunctionParameter::PRODUCT);
                          break;
                        case CChemEq::MODIFIER:
                          // it is a modifier
                          pFunParam->setUsage(CFunctionParameter::MODIFIER);
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
              pFunParam->setUsage(CFunctionParameter::PARAMETER);
            }
          else if (dynamic_cast<const CCompartment*>(object))
            {
              // it is a volume
              pFunParam->setUsage(CFunctionParameter::VOLUME);
            }
          else
            {
              fatalError()
            }
        }
      else
        {
          // it is a local parameter
          pFunParam->setUsage(CFunctionParameter::PARAMETER);
        }
      pChildNode = static_cast<const CEvaluationNode*>(pChildNode->getSibling());
      ++parameterIndex;
    }
}

void SBMLImporter::doMapping(CReaction* pCopasiReaction, const CEvaluationNodeCall* pCallNode)
{
  // map the first argument of the call node to the first variable of the function of the reaction
  // and so on
  if (!pCallNode)
    {
      fatalError();
    }
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(this->mpCopasiModel);
  if (dynamic_cast<const CMassAction*>(pCopasiReaction->getFunction()))
    {
      const CEvaluationNodeObject* pChild = dynamic_cast<const CEvaluationNodeObject*>(pCallNode->getChild());
      std::string objectCN = pChild->getData();
      objectCN = objectCN.substr(1, objectCN.length() - 2);
      CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
      assert(pObject);
      if (pObject->isReference())
        {
          pObject = pObject->getObjectParent();
          assert(pObject);
        }
      const std::string& objectKey = pObject->getKey();
      pCopasiReaction->setParameterMapping("k1", objectKey);
      const CCopasiVector<CChemEqElement>* metabolites = &pCopasiReaction->getChemEq().getSubstrates();
      unsigned int i, iMax = metabolites->size();
      unsigned int j, jMax;
      for (i = 0; i < iMax; ++i)
        for (j = 0, jMax = static_cast<int>(fabs((*metabolites)[i]->getMultiplicity())); j < jMax; j++)
          pCopasiReaction->addParameterMapping("substrate", (*metabolites)[i]->getMetaboliteKey());

      if (pCopasiReaction->isReversible())
        {
          pChild = dynamic_cast<const CEvaluationNodeObject*>(pChild->getSibling());
          std::string objectCN = pChild->getData();
          objectCN = objectCN.substr(1, objectCN.length() - 2);
          CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
          assert(pObject);
          if (pObject->isReference())
            {
              pObject = pObject->getObjectParent();
              assert(pObject);
            }
          const std::string& objectKey = pObject->getKey();
          pCopasiReaction->setParameterMapping("k2", objectKey);
          const CCopasiVector<CChemEqElement>* metabolites = &pCopasiReaction->getChemEq().getProducts();
          iMax = metabolites->size();
          for (i = 0; i < iMax; ++i)
            for (j = 0, jMax = static_cast<int>(fabs((*metabolites)[i]->getMultiplicity())); j < jMax; j++)
              pCopasiReaction->addParameterMapping("product", (*metabolites)[i]->getMetaboliteKey());
        }
    }
  else
    {
      unsigned int i, iMax = pCopasiReaction->getFunction()->getVariables().size();
      const CEvaluationNodeObject* pChild = dynamic_cast<const CEvaluationNodeObject*>(pCallNode->getChild());
      for (i = 0; i < iMax;++i)
        {
          if (!pChild)
            {
              fatalError();
            }
          std::string objectCN = pChild->getData();
          objectCN = objectCN.substr(1, objectCN.length() - 2);
          CCopasiObject* pObject = CCopasiContainer::ObjectFromName(listOfContainers, objectCN);
          assert(pObject);
          if (pObject->isReference())
            {
              pObject = pObject->getObjectParent();
              assert(pObject);
            }
          const std::string& objectKey = pObject->getKey();
          pCopasiReaction->setParameterMapping(i, objectKey);
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

ConverterASTNode* SBMLImporter::isMultipliedByVolume(const ASTNode* node, const std::string& compartmentSBMLId)
{
  ConverterASTNode* result = NULL;
  if (node->getType() == AST_TIMES || node->getType() == AST_DIVIDE)
    {
      ConverterASTNode* pTmpResultNode = new ConverterASTNode(node->getType());
      unsigned int i, iMax = node->getNumChildren();
      bool found = false;
      for (i = 0; i < iMax;++i)
        {
          const ASTNode* child = node->getChild(i);
          if (node->getType() == AST_TIMES && child->getType() == AST_NAME && child->getName() == compartmentSBMLId)
            {
              found = true;
            }
          else if ((!found) && (child->getType() == AST_TIMES || child->getType() == AST_DIVIDE))
            {
              ASTNode* pSubResult = this->isMultipliedByVolume(child, compartmentSBMLId);
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

CEvaluationNode* SBMLImporter::variables2objects(const CEvaluationNode* pOrigNode, const std::map<std::string, std::string>& replacementMap)
{
  CEvaluationNode* pResultNode = NULL;
  if (dynamic_cast<const CEvaluationNodeVariable*>(pOrigNode))
    {
      std::map<std::string , std::string>::const_iterator pos = replacementMap.find(pOrigNode->getData());
      if (pos == replacementMap.end()) fatalError();
      pResultNode = new CEvaluationNodeObject(CEvaluationNodeObject::ANY, "<" + pos->second + ">");
    }
  else
    {
      pResultNode = CEvaluationNode::create(pOrigNode->getType(), pOrigNode->getData());
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
  std::vector<CCopasiContainer*> v;
  v.push_back(this->mpCopasiModel);
  CEvaluationNodeObject* pObjectNode = dynamic_cast<CEvaluationNodeObject*>(pCallNode->getChild());
  assert(pObjectNode);
  CCopasiObjectName objectName = CCopasiObjectName(pObjectNode->getData().substr(1, pObjectNode->getData().length() - 2));
  CCopasiObject* pObject = CCopasiContainer::ObjectFromName(v, objectName);
  assert(pObject);
  if (dynamic_cast<CCopasiParameter*>(pObject))
    {
      pObject->setObjectName("k1");
      pObjectNode->setData("<" + pObject->getCN() + ">");
    }
  pObjectNode = dynamic_cast<CEvaluationNodeObject*>(pObjectNode->getSibling());
  if (pObjectNode)
    {
      objectName = CCopasiObjectName(pObjectNode->getData().substr(1, pObjectNode->getData().length() - 2));
      pObject = CCopasiContainer::ObjectFromName(v, objectName);
      assert(pObject);
      if (dynamic_cast<CCopasiParameter*>(pObject))
        {
          pObject->setObjectName("k2");
          pObjectNode->setData("<" + pObject->getCN() + ">");
        }
    }
}

bool SBMLImporter::containsVolume(const ASTNode* pNode, const std::string& compartmentSBMLId)
{
  bool result = false;
  unsigned int i, iMax = pNode->getNumChildren();
  for (i = 0;i < iMax;++i)
    {
      if (pNode->getChild(i)->getType() == AST_NAME && pNode->getChild(i)->getName() == compartmentSBMLId)
        {
          result = true;
          break;
        }
    }
  return result;
}

void SBMLImporter::setImportHandler(CProcessReport* pHandler)
{mpImportHandler = pHandler;}

CProcessReport* SBMLImporter::getImportHandlerAddr()
{return mpImportHandler;}

bool SBMLImporter::removeUnusedFunctions(CFunctionDB* pTmpFunctionDB, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  if (pTmpFunctionDB)
    {
      unsigned C_INT32 step, totalSteps, hStep;
      unsigned C_INT32 i, iMax = this->mpCopasiModel->getReactions().size();
      if (mpImportHandler)
        {
          step = 0;
          totalSteps = iMax + this->mpCopasiModel->getCompartments().size() + this->mpCopasiModel->getMetabolites().size() + this->mpCopasiModel->getModelValues().size();
          hStep = mpImportHandler->addItem("Searching used functions...",
                                           CCopasiParameter::UINT,
                                           & step,
                                           &totalSteps);
        }
      std::set<std::string> functionNameSet;
      for (i = 0;i < iMax;++i)
        {
          const CEvaluationTree* pTree = this->mpCopasiModel->getReactions()[i]->getFunction();
          if (functionNameSet.find(pTree->getObjectName()) == functionNameSet.end())
            {
              functionNameSet.insert(pTree->getObjectName());
              this->findFunctionCalls(pTree->getRoot(), functionNameSet);
            }
          ++step;
          if (mpImportHandler && !mpImportHandler->progress(hStep)) return false;
        }

      iMax = this->mpCopasiModel->getCompartments().size();
      for (i = 0;i < iMax;++i)
        {
          CModelEntity* pME = this->mpCopasiModel->getCompartments()[i];
          if (pME->getStatus() != CModelEntity::FIXED)
            {
              const CEvaluationTree* pTree = pME->getExpressionPtr();
              if (pTree != NULL)
                {
                  this->findFunctionCalls(pTree->getRoot(), functionNameSet);
                }
            }
          if (pME->getStatus() != CModelEntity::ASSIGNMENT)
            {
              const CEvaluationTree* pTree = pME->getInitialExpressionPtr();
              if (pTree != NULL)
                {
                  this->findFunctionCalls(pTree->getRoot(), functionNameSet);
                }
            }
          ++step;
        }

      iMax = this->mpCopasiModel->getMetabolites().size();
      for (i = 0;i < iMax;++i)
        {
          CModelEntity* pME = this->mpCopasiModel->getMetabolites()[i];
          if (pME->getStatus() != CModelEntity::FIXED)
            {
              const CEvaluationTree* pTree = pME->getExpressionPtr();
              if (pTree != NULL)
                {
                  this->findFunctionCalls(pTree->getRoot(), functionNameSet);
                }
            }
          if (pME->getStatus() != CModelEntity::ASSIGNMENT)
            {
              const CEvaluationTree* pTree = pME->getInitialExpressionPtr();
              if (pTree != NULL)
                {
                  this->findFunctionCalls(pTree->getRoot(), functionNameSet);
                }
            }
          ++step;
        }

      iMax = this->mpCopasiModel->getModelValues().size();
      for (i = 0;i < iMax;++i)
        {
          CModelEntity* pME = this->mpCopasiModel->getModelValues()[i];
          if (pME->getStatus() != CModelEntity::FIXED)
            {
              const CEvaluationTree* pTree = pME->getExpressionPtr();
              if (pTree != NULL)
                {
                  this->findFunctionCalls(pTree->getRoot(), functionNameSet);
                }
            }
          if (pME->getStatus() != CModelEntity::ASSIGNMENT)
            {
              const CEvaluationTree* pTree = pME->getInitialExpressionPtr();
              if (pTree != NULL)
                {
                  this->findFunctionCalls(pTree->getRoot(), functionNameSet);
                }
            }
          ++step;
        }

      CFunctionDB* pFunctionDB = CCopasiDataModel::Global->getFunctionList();
      if (mpImportHandler)
        {
          mpImportHandler->finish(hStep);
          step = 0;
          totalSteps = pTmpFunctionDB->loadedFunctions().size();
          hStep = mpImportHandler->addItem("Removing unused functions...",
                                           CCopasiParameter::UINT,
                                           & step,
                                           &totalSteps);
        }
      /*
      std::set<std::string>::iterator it=functionNameSet.begin();
      std::cout << "used functions: " << std::endl;
      while(it!=functionNameSet.end())
      {
          std::cout << (*it) << std::endl;
          ++it;
      }
      */
      // here we could have a dialog asking the user if unused functions should
      // be removed.
      while (pTmpFunctionDB->loadedFunctions().size() != 0)
        {
          CEvaluationTree* pTree = pTmpFunctionDB->loadedFunctions()[0];
          pTmpFunctionDB->removeFunction(pTree->getKey());
          if (functionNameSet.find(pTree->getObjectName()) == functionNameSet.end())
            {
              this->mUsedFunctions.erase(pTree->getObjectName());
              //std::cout << "removing " << pTree->getObjectName() << std::endl;
              pFunctionDB->removeFunction(pTree->getKey());
              // delete the entry from the copasi2sbmlmap.
              std::map<CCopasiObject*, SBase*>::iterator pos = copasi2sbmlmap.find(pTree);
              assert(pos != copasi2sbmlmap.end());
              copasi2sbmlmap.erase(pos);
            }
          ++step;
          if (mpImportHandler && !mpImportHandler->progress(hStep)) return false;
        }
      if (mpImportHandler)
        {
          mpImportHandler->finish(hStep);
        }
    }
  return true;
}

void SBMLImporter::findFunctionCalls(const CEvaluationNode* pNode, std::set<std::string>& functionNameSet)
{
  if (pNode)
    {
      CFunctionDB* pFunctionDB = CCopasiDataModel::Global->getFunctionList();
      CCopasiTree<const CEvaluationNode>::iterator treeIt = pNode;
      while (treeIt != NULL)
        {
          if (CEvaluationNode::type((*treeIt).getType()) == CEvaluationNode::CALL)
            {
              // unQuote not necessary since getIndex in CCopasiVector takes care of this.
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

void SBMLImporter::importSBMLRule(const Rule* sbmlRule, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  // so far we only support assignment rules and rate rules
  SBMLTypeCode_t type = sbmlRule->getTypeCode();
  if (type == SBML_ASSIGNMENT_RULE)
    {
      const AssignmentRule* pAssignmentRule = dynamic_cast<const AssignmentRule*>(sbmlRule);
      if (pAssignmentRule && pAssignmentRule->isSetVariable())
        {
          this->importRule(pAssignmentRule, CModelEntity::ASSIGNMENT, copasi2sbmlmap);
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
          this->importRule(pRateRule, CModelEntity::ODE, copasi2sbmlmap);
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

void SBMLImporter::importRule(const Rule* rule, CModelEntity::Status ruleType, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
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
  // find out to what kind of object the id belongs
  SBMLTypeCode_t type = SBML_UNKNOWN;
  bool found = false;
  Compartment* pC;
  Species* pS;
  Parameter* pP;
  CCopasiObject* pObject = NULL;
  std::map<CCopasiObject*, SBase*>::iterator it = copasi2sbmlmap.begin();
  std::map<CCopasiObject*, SBase*>::iterator endit = copasi2sbmlmap.end();
  while (it != endit)
    {
      switch (it->second->getTypeCode())
        {
        case SBML_COMPARTMENT:
          pC = dynamic_cast<Compartment*>(it->second);
          if (pC->getId() == sbmlId)
            {
              if (pC->getConstant())
                {
                  if (ruleType == CModelEntity::ASSIGNMENT)
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 34 , "AssignmentRule", "Compartment", sbmlId.c_str());
                    }
                  else if (ruleType == CModelEntity::ODE)
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 34 , "RateRule", "Compartment", sbmlId.c_str());
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
              if (pS->getConstant())
                {
                  if (ruleType == CModelEntity::ASSIGNMENT)
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 34 , "AssignmentRule", "Metabolite", sbmlId.c_str());
                    }
                  else if (ruleType == CModelEntity::ODE)
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 34 , "RateRule", "Metabolite", sbmlId.c_str());
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
              if (pP->getConstant())
                {
                  if (ruleType == CModelEntity::ASSIGNMENT)
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 34 , "AssignmentRule", "Parameter", sbmlId.c_str());
                    }
                  else if (ruleType == CModelEntity::ODE)
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 34 , "RateRule", "Parameter", sbmlId.c_str());
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
      CModelEntity* pME;
      switch (type)
        {
        case SBML_PARAMETER:
          // activate the next two lines if rules for compartments and
          // metabolites should be imported.
        case SBML_SPECIES:
        case SBML_COMPARTMENT:
          // check if it really is a global parameter, a metabolite or a
          // compartment
          pME = dynamic_cast<CModelValue*>(pObject);
          // activate the next two lines if rules for compartments and
          // metabolites should be imported.
          if (!pME) pME = dynamic_cast<CCompartment*>(pObject);
          if (!pME) pME = dynamic_cast<CMetab*>(pObject);
          if (!pME)
            {
              if (ruleType == CModelEntity::ASSIGNMENT)
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 33, "AssigmentRule", sbmlId.c_str());
                }
              else if (ruleType == CModelEntity::ODE)
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 33, "RateRule", sbmlId.c_str());
                }
              else
                {
                  // should never happen
                  fatalError();
                }
            }
          this->importRuleForModelEntity(rule, pME, ruleType, copasi2sbmlmap);
          break;
        default:
          // now that compartments, metabolites and global parameters are
          // supported, everything else should produce a fatal error.
          fatalError();

          // remove the rest of this block and activate the code above if rules
          // for metabolites and compartments are supported.
          /*
          if (ruleType == CModelEntity::ASSIGNMENT)
              {
              mUnsupportedAssignmentRuleFound = true;
              }
          else if (ruleType == CModelEntity::ODE)
              {
              mUnsupportedRateRuleFound = true;
              }
          else
              {
              // should never happen
              fatalError();
              }
          */
          break;
        }
    }
  else
    {
      // issue a warning
      if (ruleType == CModelEntity::ASSIGNMENT)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 32, "AssignmentRule" , sbmlId.c_str());
        }
      else if (ruleType == CModelEntity::ODE)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 32, "RateRule" , sbmlId.c_str());
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
  for (i = 0;i < iMax;++i)
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
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 35);
              break;
            }
        }
    }
}

void SBMLImporter::importRuleForModelEntity(const Rule* rule, CModelEntity* pME, CModelEntity::Status status, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  if (rule->getTypeCode() == SBML_ASSIGNMENT_RULE)
    {
      this->checkRuleMathConsistency(rule, copasi2sbmlmap);
    }
  ConverterASTNode tmpNode(*rule->getMath());
  // replace all the nodes that represent species with the
  // hasOnlySubstanceUnits flag set with the node divided by the volume
  replaceSubstanceOnlySpeciesNodes(&tmpNode, mSubstanceOnlySpecies);
  this->preprocessNode(&tmpNode);
  // replace the object names
  this->replaceObjectNames(&tmpNode, copasi2sbmlmap);
  // now we convert the node to a CEvaluationNode
  CExpression* pExpression = new CExpression;
  pExpression->setTree(tmpNode);
  if (dynamic_cast<CMetab*>(pME) != NULL)
    {
      std::map<CCopasiObject*, SBase*>::iterator pos = copasi2sbmlmap.find(pME);
      assert(pos != copasi2sbmlmap.end());
      Species* pSBMLSpecies = dynamic_cast<Species*>(pos->second);
      assert(pSBMLSpecies != NULL);
      // check if the compartment is fixed
      const CCompartment* pCompartment = static_cast<CMetab*>(pME)->getCompartment();
      assert(pCompartment != NULL);
      if (pCompartment->getStatus() == CModelValue::FIXED)
        {
          if (pSBMLSpecies->getHasOnlySubstanceUnits() == true)
            {
              // divide the expression by the volume
              CEvaluationNodeObject* pVolumeNode = new CEvaluationNodeObject(CEvaluationNodeObject::ANY, "<" + pCompartment->getValueReference()->getCN() + ">");
              CEvaluationNodeOperator* pOperatorNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::DIVIDE, "/");
              pOperatorNode->addChild(pExpression->getRoot()->copyBranch());
              pOperatorNode->addChild(pVolumeNode);
              pExpression->setRoot(pOperatorNode);
            }
        }
      else
        {
          if (pSBMLSpecies->getHasOnlySubstanceUnits() == true)
            {
              // if it is an divide by the volume
              CEvaluationNodeObject* pVolumeNode = new CEvaluationNodeObject(CEvaluationNodeObject::ANY, "<" + pCompartment->getValueReference()->getCN() + ">");
              CEvaluationNodeOperator* pOperatorNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::DIVIDE, "/");
              pOperatorNode->addChild(pExpression->getRoot()->copyBranch());
              pOperatorNode->addChild(pVolumeNode);
              pExpression->setRoot(pOperatorNode);
            }
          else
            {
              // if it is an assignment rule we do nothing, if it is an ode rule,
              // we need to issue a warning or an error
              CCopasiMessage::CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 51 , pSBMLSpecies->getId().c_str());
            }
        }
    }
  pME->setStatus(status);
  pME->setExpressionPtr(pExpression);
}

void SBMLImporter::checkRuleMathConsistency(const Rule* pRule, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  // only check if Level2 Version1 ?????
  //if(this->mLevel==2 && this->mVersion==1)
  {
    // check if no nodes with ids of objects are used in an assignmet that are
    // set in another assignment rule later on
    std::set<std::string> idSet;
    const ASTNode* pNode = pRule->getMath();
    this->getIdsFromNode(pNode, idSet);
    Model* sbmlModel = dynamic_cast<Model*>(copasi2sbmlmap[mpCopasiModel]);
    if (!sbmlModel) fatalError();
    unsigned int i, iMax = sbmlModel->getNumRules();
    for (i = 0;i < iMax;++i)
      {
        if (sbmlModel->getRule(i) == pRule)
          {
            break;
          }
      }
    Rule* pR;
    SBMLTypeCode_t type;
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
  }
}

void SBMLImporter::getIdsFromNode(const ASTNode* pNode, std::set<std::string>& idSet)
{
  if (!pNode) return;
  if (pNode->getType() == AST_NAME)
    {
      idSet.insert(pNode->getName());
    }
  unsigned int i, iMax = pNode->getNumChildren();
  for (i = 0;i < iMax;++i)
    {
      this->getIdsFromNode(pNode->getChild(i), idSet);
    }
}

void SBMLImporter::replaceObjectNames(ASTNode* pNode, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  if (pNode->getType() == AST_NAME)
    {
      std::string name = pNode->getName();
      // the id can either belong to a compartment, a species, a reaction or a
      // global parameter
      std::map<CCopasiObject*, SBase*>::iterator it = copasi2sbmlmap.begin();
      std::map<CCopasiObject*, SBase*>::iterator endit = copasi2sbmlmap.end();
      CReaction* pReaction;
      CModelEntity* pModelEntity;
      while (it != endit)
        {
          CCopasiObject* pObject = it->first;
          pReaction = dynamic_cast<CReaction*>(pObject);
          pModelEntity = dynamic_cast<CModelEntity*>(pObject);
          std::string sbmlId;
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
              // make sure it is only one of the allowed types
              switch (it->second->getTypeCode())
                {
                case SBML_COMPARTMENT:
                  pNode->setName((pObject->getCN() + ",Reference=Volume").c_str());
                  break;
                case SBML_SPECIES:
                  // !!!! Check if this is always correct. Maybe if
                  // hasOnlySubstanceUnits is set we have to use the amount
                  // instead. !!!!
                  pNode->setName((pObject->getCN() + ",Reference=Concentration").c_str());
                  break;
                  //case SBML_REACTION:
                case SBML_PARAMETER:
                  pNode->setName((pObject->getCN() + ",Reference=Value").c_str());
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
      if (it == endit) fatalError();
    }
  else
    {
      unsigned int i, iMax = pNode->getNumChildren();
      for (i = 0;i < iMax;++i)
        {
          this->replaceObjectNames(pNode->getChild(i), copasi2sbmlmap);
        }
    }
}

/**
 * For function definitions that use the time symbol we have to make this a
 * variable that is passed to the function instead.
 * The function recursively goes through the AST tree rooted in root and
 * changs all time nodes to variable nodes with name newNodeName.
 * Additionally all function calls to functions in mExplicitelyTimeDependentFunctionDefinitions
 * have to be changed to contain the added parameter.
 * If a time node has been found, the function return true, otherwise false
 * is returned.
 */
bool SBMLImporter::replaceTimeNodesInFunctionDefinition(ASTNode* root, std::string newNodeName)
{
  bool timeFound = false;
  if (root->getType() == AST_NAME_TIME)
    {
      timeFound = true;
      root->setType(AST_NAME);
      root->setName(newNodeName.c_str());
    }
  else
    {
      if (root->getType() == AST_FUNCTION && mExplicitelyTimeDependentFunctionDefinitions.find(root->getName()) != mExplicitelyTimeDependentFunctionDefinitions.end())
        {
          // add a new child to this child node
          ASTNode* pParameterNode = new ASTNode(AST_NAME);
          pParameterNode->setName(newNodeName.c_str());
          root->addChild(pParameterNode);
          timeFound = timeFound || true;
        }
    }
  unsigned int i, iMax = root->getNumChildren();
  for (i = 0;i < iMax;++i)
    {
      ASTNode* child = root->getChild(i);
      timeFound = timeFound || this->replaceTimeNodesInFunctionDefinition(child, newNodeName);
    }
  return timeFound;
}

void SBMLImporter::replaceTimeDependentFunctionCalls(ASTNode* root)
{
  if (root == NULL) return;
  if (root->getType() == AST_FUNCTION && mExplicitelyTimeDependentFunctionDefinitions.find(root->getName()) != mExplicitelyTimeDependentFunctionDefinitions.end())
    {
      // add a new child to this child node
      ASTNode* pTimeNode = new ASTNode(AST_NAME_TIME);
      pTimeNode->setName("TIME");
      root->addChild(pTimeNode);
    }
  unsigned int i, iMax = root->getNumChildren();
  for (i = 0;i < iMax;++i)
    {
      this->replaceTimeDependentFunctionCalls(root->getChild(i));
    }
}

bool SBMLImporter::setInitialValues(CModel* pModel, const std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  // go through the CCopasiDataModel and set the initial values on all
  // compartments, metabolites and model values if they were given in the sbml
  // model.
  // if no initial value was given for an entity, check if the value is set
  // by another means (rule, initialAssignment) and if not, create an error
  // message
  std::map<CCopasiObject*, SBase*>::const_iterator pos;
  std::set<const CCopasiObject*> changedObjects;
  CCopasiVectorNS<CCompartment>::iterator compartmentIt = pModel->getCompartments().begin();
  CCopasiVectorNS<CCompartment>::iterator compartmentEndit = pModel->getCompartments().end();
  while (compartmentIt != compartmentEndit)
    {
      pos = copasi2sbmlmap.find(*compartmentIt);
      assert(pos != copasi2sbmlmap.end());
      Compartment* pSBMLCompartment = dynamic_cast<Compartment*>(pos->second);
      assert(pSBMLCompartment != NULL);
      // for level 1 models we have to use isSetVolume to determine if the
      // volume has been set since in level 1, compartments had different
      // defaults
      if ((this->mLevel == 1 && pSBMLCompartment->isSetVolume()) || pSBMLCompartment->isSetSize())
        {
          // set the initial value
          // here we can safely use getSize() regardless of the level of the
          // sbml model
          (*compartmentIt)->setInitialValue(pSBMLCompartment->getSize());
          changedObjects.insert(*compartmentIt);
        }
      else
        {
          // if the entity has a status of FIXED or ODE,
          // check if there is an initial assignment, else it is an
          // error
          if (((*compartmentIt)->getStatus() == CModelValue::FIXED || (*compartmentIt)->getStatus() == CModelValue::ODE) && (*compartmentIt)->getInitialExpressionPtr() == NULL)
            {
              this->mIncompleteModel = true;
              (*compartmentIt)->setInitialValue(1.0);
              changedObjects.insert(*compartmentIt);
              CCopasiMessage::CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 45, pSBMLCompartment->getId().c_str());
            }
        }
      ++compartmentIt;
    }
  CCopasiVectorNS<CMetab>::iterator metabIt = pModel->getMetabolites().begin();
  CCopasiVectorNS<CMetab>::iterator metabEndit = pModel->getMetabolites().end();
  while (metabIt != metabEndit)
    {
      pos = copasi2sbmlmap.find(*metabIt);
      assert(pos != copasi2sbmlmap.end());
      Species* pSBMLSpecies = dynamic_cast<Species*>(pos->second);
      assert(pSBMLSpecies != NULL);
      // check if the initial concentration or the initial amount has been set
      if (pSBMLSpecies->isSetInitialConcentration())
        {
          if (pSBMLSpecies->getHasOnlySubstanceUnits() == true)
            {
              CCopasiMessage Message(CCopasiMessage::ERROR, MCSBML + 20, pSBMLSpecies->getId().c_str());
            }
          // set the initial value
          // here we can safely use getSize() regardless of the level of the
          // sbml model
          (*metabIt)->setInitialConcentration(pSBMLSpecies->getInitialConcentration());
          changedObjects.insert(*metabIt);
        }
      /*
      else if(pSBMLSpecies->getHasOnlySubstanceUnits() && pSBMLSpecies->isSetInitialAmount())
      {
          if (sbmlSpecies->getInitialAmount() != 0.0)
          {
              copasiMetabolite->setInitialValue(sbmlSpecies->getInitialAmount()*pModel->getQuantity2NumberFactor()); // CHECK UNITS !!!
          }
          else
          {
              copasiMetabolite->setInitialConcentration(0.0);
          }
      }
      */
      else if (pSBMLSpecies->isSetInitialAmount())
        {
          if (pSBMLSpecies->getInitialAmount() != 0.0)
            {
              (*metabIt)->setInitialValue(pSBMLSpecies->getInitialAmount()*pModel->getQuantity2NumberFactor()); // CHECK UNITS !!!
              changedObjects.insert(*metabIt);
            }
          else
            {
              (*metabIt)->setInitialConcentration(0.0);
              changedObjects.insert(*metabIt);
            }
        }
      else
        {
          // if the entity has a status of FIXED, REACTION or ODE,
          // check if there is an initial assignment, else it is an
          // error
          if (((*metabIt)->getStatus() == CModelValue::FIXED || (*metabIt)->getStatus() == CModelValue::REACTIONS || (*metabIt)->getStatus() == CModelValue::ODE) && (*metabIt)->getInitialExpressionPtr() == NULL)
            {
              (*metabIt)->setInitialConcentration(1.0);
              changedObjects.insert(*metabIt);
              this->mIncompleteModel = true;
              CCopasiMessage::CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 41, pSBMLSpecies->getId().c_str());
            }
        }
      ++metabIt;
    }
  CCopasiVectorN<CModelValue>::iterator mvIt = pModel->getModelValues().begin();
  CCopasiVectorN<CModelValue>::iterator mvEndit = pModel->getModelValues().end();
  while (mvIt != mvEndit)
    {
      pos = copasi2sbmlmap.find(*mvIt);
      assert(pos != copasi2sbmlmap.end());
      Parameter* pSBMLParameter = dynamic_cast<Parameter*>(pos->second);
      assert(pSBMLParameter != NULL);
      // check if the initial concentration or the initial amount has been set
      if (pSBMLParameter->isSetValue())
        {
          // set the initial value
          // here we can safely use getSize() regardless of the level of the
          // sbml model
          (*mvIt)->setInitialValue(pSBMLParameter->getValue());
          changedObjects.insert(*mvIt);
        }
      else
        {
          // if the entity has a status of FIXED or ODE,
          // check if there is an initial assignment, else it is an
          // error
          if (((*mvIt)->getStatus() == CModelValue::FIXED || (*mvIt)->getStatus() == CModelValue::ODE) && (*mvIt)->getInitialExpressionPtr() == NULL)
            {
              (*metabIt)->setInitialValue(1.0);
              changedObjects.insert(*mvIt);
              this->mIncompleteModel = true;
              CCopasiMessage::CCopasiMessage(CCopasiMessage::ERROR, MCSBML + 43, pSBMLParameter->getId().c_str());
            }
        }
      ++mvIt;
    }
  std::vector<Refresh*> refreshes = pModel->buildInitialRefreshSequence(changedObjects);
  std::vector<Refresh*>::iterator refreshIt = refreshes.begin(), refreshEndit = refreshes.end();
  while (refreshIt != refreshEndit)
    {
      (**refreshIt)();
      ++refreshIt;
    }
  return true;
}

void SBMLImporter::checkElementUnits(const Model* pSBMLModel, CModel* pCopasiModel, int level, int version)
{
  unsigned int i, iMax = pSBMLModel->getNumCompartments();
  std::vector<std::string> nonDefaultCompartments;
  std::vector<std::string> nonDefaultSpecies;
  std::vector<std::string> nonDefaultKineticTime;
  std::vector<std::string> nonDefaultKineticSubstance;
  const Compartment* pCompartment;
  const Species* pSpecies;
  const Reaction* pReaction;
  const KineticLaw* pKineticLaw;
  UnitDefinition* pVolumeUnits = getSBMLUnitDefinitionForId("volume", pSBMLModel);
  UnitDefinition* pTimeUnits = getSBMLUnitDefinitionForId("time", pSBMLModel);
  UnitDefinition* pSubstanceUnits = getSBMLUnitDefinitionForId("substance", pSBMLModel);
  std::string lastUnit = "";
  bool inconsistentUnits = false;
  for (i = 0;i < iMax;++i)
    {
      pCompartment = pSBMLModel->getCompartment(i);
      if (pCompartment->getSpatialDimensions() != 3)
        {
          if (pCompartment->getSpatialDimensions() == 0)
            {
              // MCSBML + 23, ERROR, compartment id
              CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 23, pCompartment->getId().c_str());
            }
          else
            {
              // this can not have a dimension we know in copasi
              // warn the user
              // MCSBML + 22, compartment id
              CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 22, pCompartment->getId().c_str());
            }
          lastUnit = "volume";
        }
      else
        {
          if (pCompartment->isSetUnits())
            {
              std::string unitId = pCompartment->getUnits();
              UnitDefinition* pUdef1 = getSBMLUnitDefinitionForId(unitId, pSBMLModel);
              if (pUdef1 == NULL)
                {
                  // error message
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 55, unitId.c_str(), "units", "compartment", pCompartment->getId().c_str());
                }
              if (unitId != "volume" && !areSBMLUnitDefinitionsIdentical(pVolumeUnits, pUdef1))
                {
                  nonDefaultCompartments.push_back(pCompartment->getId());
                }
              if (lastUnit == "")
                {
                  lastUnit = unitId;
                }
              else if (unitId != lastUnit)
                {
                  // check if the two units have identical definitions
                  UnitDefinition* pUdef2 = getSBMLUnitDefinitionForId(lastUnit, pSBMLModel);
                  assert(pUdef2 != NULL);
                  if (!areSBMLUnitDefinitionsIdentical(pUdef1, pUdef2))
                    {
                      inconsistentUnits = true;
                    }
                  delete pUdef2;
                }
              delete pUdef1;
            }
          else if (lastUnit == "")
            {
              lastUnit = "volume";
            }
        }
    }
  if (!inconsistentUnits && lastUnit != "volume")
    {
      // try to set the default volume unit to the unit defined by lastUnit
      const UnitDefinition* pUdef = pSBMLModel->getUnitDefinition(lastUnit);
      assert(pUdef != NULL);
      std::pair<CModel::VolumeUnit, bool> volume = this->handleVolumeUnit(pUdef);
      if (volume.second == true)
        {
          // set the default volume unit
          pCopasiModel->setVolumeUnit(volume.first);
          delete pVolumeUnits;
          pVolumeUnits = dynamic_cast<UnitDefinition*>(pUdef->clone());
        }
      else
        {
          inconsistentUnits = true;
        }
    }
  if (inconsistentUnits)
    {
      // warn about inconsistent units and that they have been ignored and
      // report the actual units used
      // one warning for every entry in nonDefaultCompartment
      std::vector<std::string>::iterator errorIt = nonDefaultCompartments.begin(), errorEndit = nonDefaultCompartments.end();
      while (errorIt != errorEndit)
        {
          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 24, (*errorIt).c_str());
          ++errorIt;
        }
    }
  inconsistentUnits = false;
  lastUnit = "";
  iMax = pSBMLModel->getNumSpecies();
  for (i = 0;i < iMax;++i)
    {
      pSpecies = pSBMLModel->getSpecies(i);
      if (level < 2 || (level == 2 && version < 3))
        {
          // check the isSetSpatialSizeUnits flag for models prior to L2V3.
          if (pSpecies->isSetSpatialSizeUnits() == true)
            {
              // check if the spatialSizeUnits is consistent with the
              // pVolumeUnits
              std::string spatialSizeUnits = pSpecies->getSpatialSizeUnits();
              UnitDefinition* pTmpUdef2 = getSBMLUnitDefinitionForId(spatialSizeUnits, pSBMLModel);
              if (pTmpUdef2 == NULL)
                {
                  // error message
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 55, spatialSizeUnits.c_str(), "spatialSizeUnits", "species", pSpecies->getId().c_str());
                }
              if (!areSBMLUnitDefinitionsIdentical(pVolumeUnits, pTmpUdef2))
                {
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 19, pSpecies->getId().c_str());
                }
              delete pTmpUdef2;
            }
        }
      if (pSpecies->isSetUnits())
        {
          std::string unitId = pSpecies->getUnits();
          UnitDefinition* pUdef1 = getSBMLUnitDefinitionForId(unitId, pSBMLModel);
          if (pUdef1 == NULL)
            {
              // error message
              CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 55, unitId.c_str(), "substanceUnits", "species", pSpecies->getId().c_str());
            }
          if (unitId != "substance" && !areSBMLUnitDefinitionsIdentical(pSubstanceUnits, pUdef1))
            {
              nonDefaultSpecies.push_back(pSpecies->getId());
            }
          if (lastUnit == "")
            {
              lastUnit = unitId;
            }
          else if (unitId != lastUnit)
            {
              // check if the two units have identical definitions
              UnitDefinition* pUdef2 = getSBMLUnitDefinitionForId(lastUnit, pSBMLModel);
              assert(pUdef2 != NULL);
              if (!areSBMLUnitDefinitionsIdentical(pUdef1, pUdef2))
                {
                  inconsistentUnits = true;
                }
              delete pUdef2;
            }
          delete pUdef1;
        }
      else if (lastUnit == "")
        {
          lastUnit = "substance";
        }
    }
  bool inconsistentTimeUnits = false;
  std::string lastTimeUnits = "";
  iMax = pSBMLModel->getNumReactions();
  for (i = 0;i < iMax;++i)
    {
      pReaction = pSBMLModel->getReaction(i);
      pKineticLaw = pReaction->getKineticLaw();
      if (pKineticLaw != NULL)
        {
          std::string unitId;
          if (pKineticLaw->isSetSubstanceUnits())
            {
              unitId = pKineticLaw->getSubstanceUnits();
              UnitDefinition* pUdef1 = getSBMLUnitDefinitionForId(unitId, pSBMLModel);
              if (pUdef1 == NULL)
                {
                  // error message
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 55, unitId.c_str(), "substanceUnits", "kinetic law of the reaction", pReaction->getId().c_str());
                }
              if (unitId != "substance" && !areSBMLUnitDefinitionsIdentical(pSubstanceUnits, pUdef1))
                {
                  nonDefaultKineticSubstance.push_back(pReaction->getId());
                }
              if (lastUnit == "")
                {
                  lastUnit = unitId;
                }
              else if (unitId != lastUnit)
                {
                  // check if the two units have identical definitions
                  UnitDefinition* pUdef2 = getSBMLUnitDefinitionForId(lastUnit, pSBMLModel);
                  assert(pUdef2 != NULL);
                  if (!areSBMLUnitDefinitionsIdentical(pUdef1, pUdef2))
                    {
                      inconsistentUnits = true;
                    }
                  delete pUdef2;
                }
              delete pUdef1;
            }
          else if (lastUnit == "")
            {
              lastUnit = "substance";
            }
          if (pKineticLaw->isSetTimeUnits())
            {
              unitId = pKineticLaw->getTimeUnits();
              UnitDefinition* pUdef1 = getSBMLUnitDefinitionForId(unitId, pSBMLModel);
              if (pUdef1 == NULL)
                {
                  // error message
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 55, unitId.c_str(), "timeUnits", "kinetic law of the reaction", pReaction->getId().c_str());
                }
              if (unitId != "time" && !areSBMLUnitDefinitionsIdentical(pTimeUnits, pUdef1))
                {
                  nonDefaultKineticTime.push_back(pReaction->getId());
                }
              if (lastTimeUnits == "")
                {
                  lastTimeUnits = unitId;
                }
              else if (unitId != lastTimeUnits)
                {
                  // check if the two units have identical definitions
                  UnitDefinition* pUdef2 = getSBMLUnitDefinitionForId(lastTimeUnits, pSBMLModel);
                  assert(pUdef2 != NULL);
                  if (!areSBMLUnitDefinitionsIdentical(pUdef1, pUdef2))
                    {
                      inconsistentTimeUnits = true;
                    }
                  delete pUdef2;
                }
              delete pUdef1;
            }
          else if (lastTimeUnits == "") // set the last time unit to time
            {
              lastTimeUnits = "time";
            }
        }
    }
  if (!inconsistentUnits && lastUnit != "" && lastUnit != "substance")
    {
      // try to set the default substance unit to the unit defined by lastUnit
      UnitDefinition* pUdef = getSBMLUnitDefinitionForId(lastUnit, pSBMLModel);
      assert(pUdef != NULL);
      std::pair<CModel::QuantityUnit, bool> quantity = this->handleSubstanceUnit(pUdef);
      delete pUdef;
      if (quantity.second == true)
        {
          // set the default volume unit
          pCopasiModel->setQuantityUnit(quantity.first);
        }
      else
        {
          inconsistentUnits = true;
        }
    }
  if (inconsistentUnits)
    {
      // warn about inconsistent units and that they have been ignored
      // one warning SBML + 25 for each species in nonDefaultSpecies
      // and one for each KineticLaw in nonDefaultKineticSubstance
      std::vector<std::string>::iterator errorIt = nonDefaultSpecies.begin(), errorEndit = nonDefaultSpecies.end();
      while (errorIt != errorEndit)
        {
          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 25, (*errorIt).c_str());
          ++errorIt;
        }
      errorIt = nonDefaultKineticSubstance.begin(), errorEndit = nonDefaultKineticSubstance.end();
      while (errorIt != errorEndit)
        {
          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 44, (*errorIt).c_str());
          ++errorIt;
        }
    }
  if (!inconsistentTimeUnits && lastTimeUnits != "" && lastTimeUnits != "time")
    {
      // try to set the default time units
      UnitDefinition* pUdef = getSBMLUnitDefinitionForId(lastTimeUnits, pSBMLModel);
      assert(pUdef != NULL);
      std::pair<CModel::TimeUnit, bool> time = this->handleTimeUnit(pUdef);
      delete pUdef;
      if (time.second == true)
        {
          // set the default volume unit
          pCopasiModel->setTimeUnit(time.first);
        }
      else
        {
          inconsistentTimeUnits = true;
        }
    }
  if (inconsistentTimeUnits)
    {
      // warn about inconsistent time unit
      // one error for each entry in nonDefaultKineticTime
      std::vector<std::string>::iterator errorIt = nonDefaultKineticTime.begin(), errorEndit = nonDefaultKineticTime.end();
      while (errorIt != errorEndit)
        {
          CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 53, (*errorIt).c_str());
          ++errorIt;
        }
    }
  // delete the units we created
  delete pTimeUnits;
  delete pSubstanceUnits;
  delete pVolumeUnits;
}

/**
 * Enhanced method to identify identical sbml unit definitions.
 * The method first converts the unit definitions to SI units and simplifies
 * them, only then they are compared.
 */
bool SBMLImporter::areSBMLUnitDefinitionsIdentical(const UnitDefinition* pUdef1, const UnitDefinition* pUdef2)
{
  UnitDefinition* pTmpUdef1 = convertToSI(pUdef1);
  simplifyUnitDefinition(pTmpUdef1);
  UnitDefinition* pTmpUdef2 = convertToSI(pUdef2);
  simplifyUnitDefinition(pTmpUdef2);
  bool result = areIdentical(pUdef1, pUdef2);
  if (result == false)
    {
      // check if maybe everything is the same, only the multipliers are
      // somewhat off due to rounding errors
      bool newResult = true;
      if (pTmpUdef1->getNumUnits() == pTmpUdef2->getNumUnits())
        {
          orderUnitDefinition(pTmpUdef1);
          orderUnitDefinition(pTmpUdef2);
          unsigned int i = 0, iMax = pTmpUdef1->getNumUnits();
          const Unit *pU1, *pU2;
          while (newResult == true && i != iMax)
            {
              pU1 = pTmpUdef1->getUnit(i);
              pU2 = pTmpUdef2->getUnit(i);
              if (pU1->getKind() != pU2->getKind() ||
                  pU1->getExponent() != pU2->getExponent() ||
                  pU1->getScale() != pU2->getScale() ||
                  fabs((pU2->getMultiplier() - pU1->getMultiplier()) / pU1->getMultiplier()) > UNIT_MULTIPLIER_TOLERANCE)
                {
                  newResult = false;
                }
              ++i;
            }
          result = newResult;
        }
    }
  delete pTmpUdef1;
  delete pTmpUdef2;
  return result;
}

Unit* SBMLImporter::convertSBMLCubicmetresToLitres(const Unit* pU)
{
  Unit* pResult = NULL;
  if (pU != NULL)
    {
      if ((pU->getKind() == UNIT_KIND_METER || pU->getKind() == UNIT_KIND_METRE) && pU->getExponent() % 3 == 0)
        {
          pResult = dynamic_cast<Unit*>(pU->clone());
          assert(pResult != NULL);
          removeScale(pResult);
          pResult->setExponent(pResult->getExponent() / 3);
          pResult->setKind(UNIT_KIND_LITRE);
          pResult->setMultiplier(pow(pResult->getMultiplier(), 3));
          normalizeSBMLUnit(pResult);
        }
    }
  return pResult;
}

/**
 * This funktion normalizes the multiplier to be within the range 1.0 <=
 * multiplier < 10.0.
 */
void SBMLImporter::normalizeSBMLUnit(Unit* pU)
{
  if (pU != NULL)
    {
      double log10Multiplier = log10(pU->getMultiplier());
      pU->setScale(pU->getScale() + (C_INT32) floor(log10Multiplier));
      pU->setMultiplier(pow(10.0, log10Multiplier - floor(log10Multiplier)));
    }
}

/**
 * This method takes the id of a unit as it can appear in an SBML file, and
 * returns a new UnitDefinition object for that id.
 */
UnitDefinition* SBMLImporter::getSBMLUnitDefinitionForId(const std::string& unitId, const Model* pSBMLModel)
{
  UnitDefinition* pUnitDefinition = NULL;
  const UnitDefinition* pTmpUnitDefinition = pSBMLModel->getUnitDefinition(unitId);
  if (pTmpUnitDefinition != NULL) // there was a unit definition with that id
    {
      pUnitDefinition = dynamic_cast<UnitDefinition*>(pTmpUnitDefinition->clone());
      assert(pUnitDefinition != NULL);
    }
  else
    {
      if (unitId == "volume" || unitId == "litre")
        {
          pUnitDefinition = new UnitDefinition("dummy_volume");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_LITRE);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "substance" || unitId == "mole")
        {
          pUnitDefinition = new UnitDefinition("dummy_substance");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_MOLE);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "time" || unitId == "second")
        {
          pUnitDefinition = new UnitDefinition("dummy_time");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_SECOND);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "area")
        {
          pUnitDefinition = new UnitDefinition("area");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_METRE);
          pUnit->setExponent(2);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "length")
        {
          pUnitDefinition = new UnitDefinition("length");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_METRE);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "ampere")
        {
          pUnitDefinition = new UnitDefinition("dummy_ampere");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_AMPERE);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "farad")
        {
          pUnitDefinition = new UnitDefinition("dummy_farad");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_FARAD);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "joule")
        {
          pUnitDefinition = new UnitDefinition("dummy_joule");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_JOULE);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "lux")
        {
          pUnitDefinition = new UnitDefinition("dummy_lux");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_LUX);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "radian")
        {
          pUnitDefinition = new UnitDefinition("dummy_radian");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_RADIAN);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "volt")
        {
          pUnitDefinition = new UnitDefinition("dummy_volt");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_VOLT);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "becquerel")
        {
          pUnitDefinition = new UnitDefinition("dummy_becquerel");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_BECQUEREL);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "gram")
        {
          pUnitDefinition = new UnitDefinition("dummy_gram");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_GRAM);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "katal")
        {
          pUnitDefinition = new UnitDefinition("dummy_katal");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_KATAL);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "metre")
        {
          pUnitDefinition = new UnitDefinition("dummy_metre");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_METRE);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "candela")
        {
          pUnitDefinition = new UnitDefinition("dummy_candela");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_CANDELA);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "gray")
        {
          pUnitDefinition = new UnitDefinition("dummy_gray");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_GRAY);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "kelvin")
        {
          pUnitDefinition = new UnitDefinition("dummy_kelvin");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_KELVIN);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "siemens")
        {
          pUnitDefinition = new UnitDefinition("dummy_siemens");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_SIEMENS);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "weber")
        {
          pUnitDefinition = new UnitDefinition("dummy_weber");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_WEBER);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "Celsius")
        {
          pUnitDefinition = new UnitDefinition("dummy_celsius");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_CELSIUS);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "henry")
        {
          pUnitDefinition = new UnitDefinition("dummy_henry");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_HENRY);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "kilogram")
        {
          pUnitDefinition = new UnitDefinition("dummy_kilogram");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_KILOGRAM);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "newton")
        {
          pUnitDefinition = new UnitDefinition("dummy_newton");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_NEWTON);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "sievert")
        {
          pUnitDefinition = new UnitDefinition("dummy_sievert");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_SIEVERT);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "coulomb")
        {
          pUnitDefinition = new UnitDefinition("dummy_coulomb");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_COULOMB);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "hertz")
        {
          pUnitDefinition = new UnitDefinition("dummy_hertz");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_HERTZ);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "ohm")
        {
          pUnitDefinition = new UnitDefinition("dummy_ohm");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_OHM);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "steradian")
        {
          pUnitDefinition = new UnitDefinition("dummy_steradian");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_STERADIAN);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "dimensionless")
        {
          pUnitDefinition = new UnitDefinition("dummy_dimensionless");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_DIMENSIONLESS);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "item")
        {
          pUnitDefinition = new UnitDefinition("dummy_item");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_ITEM);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "lumen")
        {
          pUnitDefinition = new UnitDefinition("dummy_lumen");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_LUMEN);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "pascal")
        {
          pUnitDefinition = new UnitDefinition("dummy_pascal");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_PASCAL);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
      else if (unitId == "tesla")
        {
          pUnitDefinition = new UnitDefinition("dummy_tesla");
          Unit* pUnit = pUnitDefinition->createUnit();
          pUnit->setKind(UNIT_KIND_TESLA);
          pUnit->setExponent(1);
          pUnit->setMultiplier(1.0);
          pUnit->setScale(0);
        }
    }
  return pUnitDefinition;
}
