/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLImporter.cpp,v $
   $Revision: 1.110 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/11/15 23:01:52 $
   End CVS Header */

#include "copasi.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <limits>

#include "mathematics.h"

#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CMetab.h"
#include "model/CReaction.h"
#include "model/CModelValue.h"
#include "copasi.h"
#include "function/CNodeK.h"
#include "function/CKinFunction.h"
#include "function/CFunctionDB.h"
#include "function/CEvaluationTree.h"
#include "report/CCopasiObjectReference.h"
#include "utilities/CCopasiTree.h"
#include "CopasiDataModel/CCopasiDataModel.h"

#include "sbml/SBMLReader.h"
#include "sbml/SBMLDocument.h"
#include "sbml/Compartment.h"
#include "sbml/Species.h"
#include "sbml/SpeciesReference.h"
#include "sbml/ModifierSpeciesReference.h"
#include "sbml/Reaction.h"
#include "sbml/KineticLaw.h"
#include "sbml/math/FormulaFormatter.h"
#include "sbml/Model.h"
#include "sbml/UnitKind.h"
#include "sbml/Unit.h"
#include "sbml/Parameter.h"
#include "sbml/FunctionDefinition.h"
#include "sbml/xml/ParseMessage.h"

#include "SBMLImporter.h"
#include "ConverterASTNode.h"
#include "utilities/CProcessReport.h"

#include "utilities/CCopasiMessage.h"

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
              this->mpCopasiModel->setQuantityUnit(this->handleSubstanceUnit(uDef));
            }
          else if (unitId == "time")
            {
              this->mpCopasiModel->setTimeUnit(this->handleTimeUnit(uDef));
            }
          else if (unitId == "volume")
            {
              this->mpCopasiModel->setVolumeUnit(this->handleVolumeUnit(uDef));
            }
          else if ((unitId == "area") || (unitId == "length"))
            {
              /* do nothing, but do not throw an exception either */
            }
          else
            {
              /* Dont' throw an exception any more because individual objects
              ** are tested for unit usage and warning will be created there.
              */ 
              //throw StdException("Error. SBML Units other than \"substance\", \"time\" and \"volume\" not implemented.");
            }
        }
    }

  std::string title, comment;

  comment = sbmlModel->getNotes();

  this->mpCopasiModel->setComments(comment);
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

  // now go through the temporary function db and replace all call nodes with the name of the
  // copasi function.
  if (mpImportHandler)
    {
      mpImportHandler->finish(hStep);
      mImportStep = 2;
      if (!mpImportHandler->progress(mhImportStep)) return false;
      step = 0;
      totalSteps = num;
      hStep = mpImportHandler->addItem("Replacing function call names...",
                                       CCopasiParameter::UINT,
                                       & step,
                                       &totalSteps);
    }
  functions = &(pTmpFunctionDB->loadedFunctions());
  num = (*functions).size();
  for (counter = 0; counter < num; ++counter)
    {
      this->replaceCallNodeNames((*functions)[counter]->getRoot());
      (*functions)[counter]->updateTree();
      ++step;
      if (mpImportHandler && !mpImportHandler->progress(hStep)) return false;
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
      CCompartment* copasiCompartment = this->createCCompartmentFromCompartment(sbmlCompartment, this->mpCopasiModel, copasi2sbmlmap);
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
          CMetab* copasiMetabolite = this->createCMetabFromSpecies(sbmlSpecies, this->mpCopasiModel, copasiCompartment, copasi2sbmlmap);
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

  /* Create all reactions */
  num = sbmlModel->getNumReactions();
  if (mpImportHandler)
    {
      mpImportHandler->finish(hStep);
      mImportStep = 6;
      if (!mpImportHandler->progress(mhImportStep)) return false;
      step = 0;
      totalSteps = num;
      hStep = mpImportHandler->addItem("Importing reactions...",
                                       CCopasiParameter::UINT,
                                       & step,
                                       &totalSteps);
    }
  for (counter = 0; counter < num; counter++)
    {
      this->createCReactionFromReaction(sbmlModel->getReaction(counter), sbmlModel, this->mpCopasiModel, copasi2sbmlmap, pTmpFunctionDB);
      ++step;
      if (mpImportHandler && !mpImportHandler->progress(hStep)) return false;
    }
  this->mpCopasiModel->setCompileFlag();
  if (sbmlModel->getNumRules() > 0)
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
      mImportStep = 7;
      if (!mpImportHandler->progress(mhImportStep)) return false;
    }

  this->removeUnusedFunctions(pTmpFunctionDB);

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
      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 14, sbmlFunction->getId().c_str());
    }
  return pTmpFunction;
}

CFunction* SBMLImporter::createCFunctionFromFunctionTree(const FunctionDefinition* pSBMLFunction)
{
  CFunction* pFun = NULL;
  if (pSBMLFunction->isSetMath())
    {
      const ASTNode* root = pSBMLFunction->getMath();
      if (root->getType() == AST_LAMBDA)
        {
          // get the number of children.
          // the first n-1 children are the parameters for the function
          // the last child is the actual function
          pFun = new CFunction();
          unsigned int i, iMax = root->getNumChildren() - 1;
          for (i = 0; i < iMax;++i)
            {
              ASTNode* pVarNode = root->getChild(i);
              if (pVarNode->getType() != AST_NAME)
                {
                  delete pFun;
                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 12, pSBMLFunction->getId().c_str());
                }
              pFun->addVariable(pVarNode->getName());
            }
          pFun->setTree(*root->getRightChild());
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
          pFun->compile();
          if (pFun->getRoot() == NULL)
            {
              delete pFun;
              CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 13, pSBMLFunction->getId().c_str());
            }
        }
      else
        {
          CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 11, pSBMLFunction->getId().c_str());
        }
    }
  return pFun;
}

/**
 * Creates and returns a Copasi CCompartment from the SBML Compartment
 * given as argument.
 */
CCompartment*
SBMLImporter::createCCompartmentFromCompartment(const Compartment* sbmlCompartment, CModel* copasiModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  if (sbmlCompartment->isSetUnits())
    {
      std::string cU = sbmlCompartment->getUnits();
      if (cU != "volume" && cU != "area" && cU != "length")
        {
          fatalError();
        }
      else if (cU == "area" || cU == "length")
        {
          /* !!!! create a warning that the units will be ignored. */
        }
    }
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
  if (sbmlCompartment->isSetVolume())
    {
      value = sbmlCompartment->getVolume();
    }
  else
    {
      // Set value to NaN and create a warning if it is the first time
      // this happend
      value = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      if (!this->mIncompleteModel)
        {
          this->mIncompleteModel = true;
          CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 7);
        }
    }

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
SBMLImporter::createCMetabFromSpecies(const Species* sbmlSpecies, CModel* copasiModel, CCompartment* copasiCompartment, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  if (sbmlSpecies->isSetSubstanceUnits())
    {
      std::string cU = sbmlSpecies->getSubstanceUnits();
      if (cU != "substance")
        {
          fatalError();
        }
    }
  if (sbmlSpecies->isSetSpatialSizeUnits())
    {
      const std::string szU = sbmlSpecies->getSpatialSizeUnits();
      if (szU != "volume")
        {
          /* !!!! create a warning that the spatialSizeUnits will be ignored */
          CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 19, sbmlSpecies->getId().c_str());
        }
    }
  if (sbmlSpecies->getHasOnlySubstanceUnits() == true)
    {
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 18, sbmlSpecies->getId().c_str());
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
  if (sbmlSpecies->isSetInitialAmount())
    {
      copasiMetabolite->setInitialNumber(sbmlSpecies->getInitialAmount()*copasiModel->getQuantity2NumberFactor()); // CHECK UNITS !!!
    }
  else if (sbmlSpecies->isSetInitialConcentration())
    {
      copasiMetabolite->setInitialConcentration(sbmlSpecies->getInitialConcentration());      // CHECK UNITS !!!
    }
  else
    {
      copasiMetabolite->setInitialConcentration(std::numeric_limits<C_FLOAT64>::quiet_NaN());      // CHECK UNITS !!!
      if (!this->mIncompleteModel)
        {
          this->mIncompleteModel = true;
          CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 7);
        }
    }
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
SBMLImporter::createCReactionFromReaction(const Reaction* sbmlReaction, const Model* C_UNUSED(sbmlModel), CModel* copasiModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, CFunctionDB* pTmpFunctionDB)
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
  copasi2sbmlmap[copasiReaction] = const_cast<Reaction*>(sbmlReaction);
  if (copasiReaction == NULL)
    {
      fatalError();
    }
  /* Add all substrates to the reaction */
  unsigned int num = sbmlReaction->getNumReactants();
  bool singleCompartment = true;
  const CCompartment* compartment = NULL;
  for (counter = 0; counter < num; counter++)
    {
      SpeciesReference* sr = sbmlReaction->getReactant(counter);
      if (sr == NULL)
        {
          delete copasiReaction;
          fatalError();
        }
      if (sr->isSetStoichiometryMath())
        {
          delete copasiReaction;
          CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 10);
        }
      float stoich = sr->getStoichiometry() / sr->getDenominator();
      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());
      if (pos == this->speciesMap.end())
        {
          delete copasiReaction;
          fatalError();
        }
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
      SpeciesReference* sr = sbmlReaction->getProduct(counter);
      if (sr == NULL)
        {
          delete copasiReaction;
          fatalError();
        }
      if (sr->isSetStoichiometryMath())
        {
          delete copasiReaction;
          CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 10);
        }
      float stoich = sr->getStoichiometry() / sr->getDenominator();
      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());
      if (pos == this->speciesMap.end())
        {
          delete copasiReaction;
          fatalError();
        }
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
      ModifierSpeciesReference* sr = sbmlReaction->getModifier(counter);
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
  KineticLaw* kLaw = sbmlReaction->getKineticLaw();
  if (kLaw != NULL)
    {
      if (kLaw->isSetSubstanceUnits())
        {
          std::string cU = kLaw->getSubstanceUnits();
          if (cU != "substance")
            {
              delete copasiReaction;
              fatalError();
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

      if (!kLaw->isSetMath())
        {
          kLaw->setMathFromFormula();
        }

      for (counter = 0; counter < kLaw->getNumParameters();++counter)
        {
          Parameter* pSBMLParameter = kLaw->getParameter(counter);
          std::string id;
          if (this->mLevel == 1)
            {
              id = pSBMLParameter->getName();
            }
          else
            {
              id = pSBMLParameter->getId();
            }
          copasiReaction->getParameters().addParameter(id, CCopasiParameter::DOUBLE, pSBMLParameter->getValue());
        }

      const ASTNode* kLawMath = kLaw->getMath();
      if (kLawMath == NULL)
        {
          fatalError();
        }
      ASTNode* node = new ConverterASTNode(*kLawMath);

      if (node == NULL)
        {
          delete copasiReaction;
          fatalError();
        }

      this->replacePowerFunctionNodes(node);
      this->replaceLog((ConverterASTNode*)node);
      this->replaceRoot((ConverterASTNode*)node);
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
              ASTNode* tmpNode1 = this->isMultipliedByVolume(node, compartment->getSBMLId());
              if (tmpNode1)
                {
                  delete node;
                  node = tmpNode1;
                  if (node->getType() == AST_DIVIDE && node->getNumChildren() != 2)
                    {
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
                  if (!this->mDivisionByCompartmentWarning && compartment->getInitialVolume() == 1.0)
                    {
                      this->mDivisionByCompartmentWarning = true;
                      if (node->getChild(0)->getType() == AST_FUNCTION && (!this->containsVolume(node->getChild(0), compartment->getSBMLId())))
                        {
                          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 17);
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
      if (!sbmlId2CopasiCN(node, copasi2sbmlmap, copasiReaction->getParameters())) fatalError();
      CEvaluationNode* pExpressionTreeRoot = CEvaluationTree::convertASTNode(*node);
      this->replaceCallNodeNames(pExpressionTreeRoot);
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
              std::vector<CEvaluationNodeObject*> v = this->isMassAction(tree, copasiReaction->getChemEq(), static_cast<const CEvaluationNodeCall*>(pExpressionTreeRoot));
              if (!v.empty())
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
                  unsigned int i, iMax = v.size();
                  for (i = 0;i < iMax;++i)
                    {
                      pCallNode->addChild(v[i]);
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
                      if (copasiReaction->getFunction().getType() == CEvaluationTree::UserDefined)
                        {
                          pTmpFunctionDB->add(&const_cast<CFunction&>(copasiReaction->getFunction()), false);
                          this->mUsedFunctions.insert(copasiReaction->getFunction().getObjectName());
                        }
                    }
                }
            }
          else
            {
              std::vector<CEvaluationNodeObject*> v = this->isMassAction(pTmpTree, copasiReaction->getChemEq());
              if (!v.empty())
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
                  unsigned int i, iMax = v.size();
                  for (i = 0;i < iMax;++i)
                    {
                      pCallNode->addChild(v[i]);
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
                      CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 9, copasiReaction->getObjectName().c_str());
                    }
                  else
                    {
                      if (copasiReaction->getFunction().getType() == CEvaluationTree::UserDefined)
                        {
                          pTmpFunctionDB->add(&const_cast<CFunction&>(copasiReaction->getFunction()), false);
                          this->mUsedFunctions.insert(copasiReaction->getFunction().getObjectName());
                        }
                    }
                }
            }
          // delete the temporary tree and all the nodes
          delete pTmpTree;
        }
      else
        {
          // error message
          CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 8, copasiReaction->getObjectName().c_str());
        }
    }
  else
    {
      /* if no KineticLaw was defined for the reaction. */
      copasiReaction->setFunction(NULL);
    }
  //DebugFile << "Created reaction: " << copasiReaction->getObjectName() << std::endl;
  if (this->mLevel == 1)
    {
      copasiReaction->setSBMLId(sbmlReaction->getName());
    }
  else
    {
      copasiReaction->setSBMLId(sbmlReaction->getId());
    }
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
FunctionDefinition*
SBMLImporter::getFunctionDefinitionForName(const std::string name, const Model* sbmlModel)
{
  FunctionDefinition* fDef = NULL;
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
  this->mDivisionByCompartmentWarning = false;
  this->mpImportHandler = NULL;
}

/**
 * Destructor that does nothing. 
 */
SBMLImporter::~SBMLImporter()
{}

/**
 * This function replaces the AST_FUNCTION_POWER ASTNodes in a ASTNode tree
 * with the AST_POWER node.
 */
void SBMLImporter::replacePowerFunctionNodes(ASTNode* node)
{
  if (node != NULL)
    {
      if (node->getType() == AST_FUNCTION_POWER)
        {
          //node->setType(AST_POWER);
          node->setCharacter('^');
        }
      unsigned int counter;
      for (counter = 0; counter < node->getNumChildren(); counter++)
        {
          this->replacePowerFunctionNodes(node->getChild(counter));
        }
    }
}

/**
 * Function reads an SBML file with libsbml and converts it to a Copasi CModel
 * object which is returned. Deletion of the returned pointer is up to the
 * caller.
 */
CModel*
SBMLImporter::readSBML(std::string filename, CFunctionDB* funDB, SBMLDocument *& pSBMLDocument, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  this->mpCopasiModel = NULL;
  if (funDB != NULL)
    {
      this->functionDB = funDB;
      SBMLReader* reader = new SBMLReader(XML_SCHEMA_VALIDATION_NONE);

      mImportStep = 0;
      if (mpImportHandler)
        {
          mpImportHandler->setName("Importing SBML file...");
          mTotalSteps = 7;
          mhImportStep = mpImportHandler->addItem("Step",
                                                  CCopasiParameter::UINT,
                                                  & mImportStep,
                                                  &mTotalSteps);
        }

      SBMLDocument* sbmlDoc = reader->readSBML(filename);
      sbmlDoc->validate();
      if (sbmlDoc->getNumFatals() > 0)
        {
          ParseMessage * pSBMLMessage = sbmlDoc->getFatal(0);

          CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 2,
                                 pSBMLMessage->getLine(),
                                 pSBMLMessage->getColumn(),
                                 pSBMLMessage->getMessage().c_str());

          if (mpImportHandler) mpImportHandler->finish(mhImportStep);
          return NULL;
        }
      else if (sbmlDoc->getNumErrors() > 0)
        {
          ParseMessage * pSBMLMessage = sbmlDoc->getError(0);
          /* some level 1 files have an annotation in the wrong place
           * This is considered an error by libsbml, but
           * it does not really affect the model, so we try to
           * read it anyway.
           */
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
      if (sbmlDoc->getModel() == NULL)
        {
          CCopasiMessage Message(CCopasiMessage::ERROR, MCSBML + 2);
          if (mpImportHandler) mpImportHandler->finish(mhImportStep);
          return NULL;
        }

      delete reader;
      pSBMLDocument = sbmlDoc;
      this->mLevel = pSBMLDocument->getLevel();
      if (mLevel == 1)
        {
          pSBMLDocument->setLevel(2);
          mLevel = pSBMLDocument->getLevel();
        }

      this->mpCopasiModel = this->createCModelFromSBMLDocument(sbmlDoc, copasi2sbmlmap);
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
CModel::QuantityUnit
SBMLImporter::handleSubstanceUnit(const UnitDefinition* uDef)
{
  CModel::QuantityUnit qUnit = CModel::Mol;
  if (uDef == NULL)
    {
      //DebugFile << "Argument to handleSubstanceUnit is NULL pointer." << std::endl;
      fatalError();
    }
  if (uDef->getNumUnits() == 1)
    {
      Unit* u = uDef->getUnit(0);
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
                  break;
                case - 3:
                  qUnit = CModel::mMol;
                  break;
                case - 6:
                  qUnit = CModel::microMol;
                  break;
                case - 9:
                  qUnit = CModel::nMol;
                  break;
                case - 12:
                  qUnit = CModel::pMol;
                  break;
                case - 15:
                  qUnit = CModel::fMol;
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
          if ((u->getExponent() == 1) && (u->getMultiplier() == 1) && (u->getScale() == 0))
            {
              qUnit = CModel::number;
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
  return qUnit;
}

/**
 * Returns the copasi TimeUnit corresponding to the given SBML Time
 *  UnitDefinition.
 */
CModel::TimeUnit
SBMLImporter::handleTimeUnit(const UnitDefinition* uDef)
{
  CModel::TimeUnit tUnit = CModel::s;
  if (uDef == NULL)
    {
      //DebugFile << "Argument to handleTimeUnit is NULL pointer." << std::endl;
      fatalError();
    }
  if (uDef->getNumUnits() == 1)
    {
      Unit* u = uDef->getUnit(0);
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
                      break;
                    case - 3:
                      tUnit = CModel::ms;
                      break;
                    case - 6:
                      tUnit = CModel::micros;
                      break;
                    case - 9:
                      tUnit = CModel::ns;
                      break;
                    case - 12:
                      tUnit = CModel::ps;
                      break;
                    case - 15:
                      tUnit = CModel::fs;
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
                }
              else if (u->getMultiplier() == 3600.0)
                {
                  tUnit = CModel::h;
                }
              else if (u->getMultiplier() == 86400.0)
                {
                  tUnit = CModel::d;
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
  return tUnit;
}

/**
 * Returns the copasi VolumeUnit corresponding to the given SBML Volume
 *  UnitDefinition.
 */
CModel::VolumeUnit
SBMLImporter::handleVolumeUnit(const UnitDefinition* uDef)
{
  CModel::VolumeUnit vUnit = CModel::l;
  if (uDef == NULL)
    {
      //DebugFile << "Argument to handleVolumeUnit is NULL pointer." << std::endl;
      fatalError();
    }
  if (uDef->getNumUnits() == 1)
    {
      Unit* u = uDef->getUnit(0);
      if (u == NULL)
        {
          //DebugFile << "Expected Unit, got NULL pointer." << std::endl;
          fatalError();
        }
      if ((u->getKind() == UNIT_KIND_LITER) || (u->getKind() == UNIT_KIND_LITRE))
        {
          if ((u->getExponent() == 1) && (u->getMultiplier() == 1) && ((u->getScale() % 3) == 0) && (u->getScale() < 1) && (u->getScale() > -16))
            {
              switch (u->getScale())
                {
                case 0:
                  vUnit = CModel::l;
                  break;
                case - 3:
                  vUnit = CModel::ml;
                  break;
                case - 6:
                  vUnit = CModel::microl;
                  break;
                case - 9:
                  vUnit = CModel::nl;
                  break;
                case - 12:
                  vUnit = CModel::pl;
                  break;
                case - 15:
                  vUnit = CModel::fl;
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
          if ((u->getExponent() == 3) && (u->getMultiplier() == 1) && (u->getScale() == 0))
            {
              vUnit = CModel::m3;
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
  return vUnit;
}

void SBMLImporter::replaceLog(ConverterASTNode* sourceNode)
{
  if (sourceNode->getType() == AST_FUNCTION_LOG && sourceNode->getNumChildren() == 2)
    {
      List* l = new List();
      ConverterASTNode* child1 = (ConverterASTNode*)sourceNode->getChild(0);
      ConverterASTNode* child2 = (ConverterASTNode*)sourceNode->getChild(1);
      ConverterASTNode* logNode1 = new ConverterASTNode(AST_FUNCTION_LOG);
      l->add(child1);
      logNode1->setChildren(l);
      ConverterASTNode* logNode2 = new ConverterASTNode(AST_FUNCTION_LOG);
      l = new List();
      l->add(child2);
      logNode2->setChildren(l);
      l = new List();
      l->add(logNode2);
      l->add(logNode1);
      sourceNode->setChildren(l);
      sourceNode->setType(AST_DIVIDE);
      // go down the children and replace logs
      this->replaceLog(child1);
      this->replaceLog(child2);
    }
  else
    {
      // go down to the children and replace logs
      unsigned int i;
      for (i = 0; i < sourceNode->getNumChildren();++i)
        {
          this->replaceLog((ConverterASTNode*)sourceNode->getChild(i));
        }
    }
}

void SBMLImporter::replaceRoot(ConverterASTNode* sourceNode)
{
  if (sourceNode->getType() == AST_FUNCTION_ROOT && sourceNode->getNumChildren() == 2)
    {
      ConverterASTNode* child1 = (ConverterASTNode*)sourceNode->getChild(0);
      ConverterASTNode* child2 = (ConverterASTNode*)sourceNode->getChild(1);
      ConverterASTNode* divideNode = new ConverterASTNode(AST_DIVIDE);
      ConverterASTNode* oneNode = new ConverterASTNode(AST_REAL);
      oneNode->setValue(1.0);
      List* l = new List();
      l->add(divideNode);
      divideNode->addChild(oneNode);
      divideNode->addChild(child1);

      List* l2 = new List();
      l2->add(child2);
      l2->add(divideNode);

      sourceNode->setChildren(l2);
      sourceNode->setType(AST_POWER);
      // go down the children and replace root functions
      this->replaceRoot(child1);
      this->replaceRoot(child2);
    }
  else
    {
      // go down to the children and replace root functions
      unsigned int i;
      for (i = 0; i < sourceNode->getNumChildren();++i)
        {
          this->replaceRoot((ConverterASTNode*)sourceNode->getChild(i));
        }
    }
}

CModelValue* SBMLImporter::createCModelValueFromParameter(const Parameter* sbmlParameter, CModel* copasiModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  if (sbmlParameter->isSetUnits())
    {
      std::string cU = sbmlParameter->getUnits();
      if (cU != "volume" && cU != "area" && cU != "length")
        {
          fatalError();
        }
      else if (cU == "area" || cU == "length")
        {
          /* !!!! create a warning that the units will be ignored. */
        }
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
  double value;
  if (sbmlParameter->isSetValue())
    {
      value = sbmlParameter->getValue();
    }
  else
    {
      // Set value to NaN and create a warning if it is the first time
      // this happend
      value = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      if (!this->mIncompleteModel)
        {
          this->mIncompleteModel = true;
          CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 7);
        }
    }
  CModelValue* pMV = copasiModel->createModelValue(name + appendix, value);
  copasi2sbmlmap[pMV] = const_cast<Parameter*>(sbmlParameter);
  if (this->mLevel == 1)
    {
      pMV->setSBMLId(sbmlParameter->getName());
    }
  else
    {
      pMV->setSBMLId(sbmlParameter->getId());
    }
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
                    }
                  break;
                default:
                  break;
                }
              ++it;
            }
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

void SBMLImporter::printMap(const std::map<CCopasiObject*, SBase*>& map)
{
  std::map<CCopasiObject*, SBase*>::const_iterator it = map.begin();
  std::map<CCopasiObject*, SBase*>::const_iterator end = map.end();
  std::cout << "Number of elements: " << map.size() << std::endl;
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

void SBMLImporter::replaceCallNodeNames(CEvaluationNode* node)
{
  if (node)
    {
      CEvaluationNodeCall* pCallNode = dynamic_cast<CEvaluationNodeCall*>(node);
      if (pCallNode)
        {
          std::map<std::string, std::string>::const_iterator pos = this->mFunctionNameMapping.find(pCallNode->getData());

          if (pos == this->mFunctionNameMapping.end())
            {
              fatalError();
            }
          std::string newName = pos->second;
          pCallNode->setData(newName);
          this->mUsedFunctions.insert(newName);
        }
      CEvaluationNode* pChildNode = static_cast<CEvaluationNode*>(node->getChild());
      while (pChildNode)
        {
          this->replaceCallNodeNames(pChildNode);
          pChildNode = static_cast<CEvaluationNode*>(pChildNode->getSibling());
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
  CCopasiVector<CFunction>* functions = this->functionDB->suitableFunctions(pCopasiReaction->getChemEq().getSubstrates().size(), pCopasiReaction->getChemEq().getProducts().size(), (TriLogic)pCopasiReaction->isReversible());
  unsigned int i, iMax = functions->size();
  for (i = 0; i < iMax;++i)
    {
      CFunction* pFun = ((*functions)[i]);
      // make sure the function is not compared to itself since it can already
      // be in the database if it has been used a call in another function
      // don't compare the mass action kinetics
      if ((pFun != tree) && (!dynamic_cast<CMassAction*>(pFun)) && this->areEqualFunctions(pFun, tree))
        {
          pCorrespondingFunction = pFun;
          break;
        }
    }
  delete functions;
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

std::vector<CEvaluationNodeObject*> SBMLImporter::isMassAction(const CEvaluationTree* pTree, const CChemEq& chemicalEquation, const CEvaluationNodeCall* pCallNode)
{
  CEvaluationTree::Type type = pTree->getType();
  std::vector< std::vector< std::string > > functionArgumentCNs;
  const CEvaluationNode* pChildNode = NULL;
  std::string str;
  std::vector<CEvaluationNodeObject*> result;
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

std::vector<CEvaluationNodeObject*> SBMLImporter::isMassActionExpression(const CEvaluationNode* pRootNode, const CChemEq& chemicalEquation)
{
  bool result = true;
  std::vector<CEvaluationNodeObject*> v;
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
                  result = !v.empty();
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
                          std::vector<CEvaluationNodeObject*> v2 = this->isMassActionExpression(pChildNode, tmpEq2);
                          result = !v2.empty();
                          if (result)
                            {
                              v.push_back(v2[0]);
                            }
                        }
                    }
                }
            }
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
              assert(pObject);
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
                      v.push_back(new CEvaluationNodeObject((CEvaluationNodeObject::SubType)(CEvaluationNode::subType(pNode->getType())), pNode->getData()));
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
                  v.push_back(new CEvaluationNodeObject((CEvaluationNodeObject::SubType)(CEvaluationNode::subType(pNode->getType())), pNode->getData()));
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
                          if (pChildNode->getType() == CEvaluationNode::NUMBER)
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
      if (result)
        {
          const CCopasiVector<CChemEqElement>& substrates = chemicalEquation.getSubstrates();
          unsigned i, iMax = substrates.size();
          for (i = 0;i < iMax && result;++i)
            {
              if (fabs(multiplicityMap[&substrates[i]->getMetabolite()] - substrates[i]->getMultiplicity()) >= 0.01)
                {
                  result = false;
                  break;
                }
            }
        }
      if (!result) v.clear();
    }
  return v;
}

std::vector<CEvaluationNodeObject*> SBMLImporter::isMassActionFunction(const CFunction* pFun, const CChemEq& chemicalEquation, const std::vector<std::vector< std::string > >& functionArgumentCNs)
{
  // create an expression from the function and call isMassActionExpression
  CEvaluationTree* pExpressionTree = this->createExpressionFromFunction(pFun, functionArgumentCNs);
  if (!pExpressionTree) fatalError();
  std::vector<CEvaluationNodeObject*> v = this->isMassActionExpression(pExpressionTree->getRoot(), chemicalEquation);
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
      CFunctionParameter* pFunParam = const_cast<CFunctionParameter*>(pCopasiReaction->getFunction().getVariables()[parameterIndex]);

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
                          pFunParam->setUsage("SUBSTRATE");
                          break;
                        case CChemEq::PRODUCT:
                          // it is a product
                          pFunParam->setUsage("PRODUCT");
                          break;
                        case CChemEq::MODIFIER:
                          // it is a modifier
                          pFunParam->setUsage("MODIFIER");
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
              pFunParam->setUsage("VARIABLE");
            }
          else if (dynamic_cast<const CCompartment*>(object))
            {
              // it is a volume
              pFunParam->setUsage("VOLUME");
            }
          else
            {
              fatalError()
            }
        }
      else
        {
          // it is a local parameter
          pFunParam->setUsage("PARAMETER");
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
  if (dynamic_cast<const CMassAction*>(&pCopasiReaction->getFunction()))
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
      for (i = 0;i < iMax;++i)
        {
          pCopasiReaction->addParameterMapping("substrate", (*metabolites)[i]->getMetaboliteKey());
        }

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
          for (i = 0;i < iMax;++i)
            {
              pCopasiReaction->addParameterMapping("product", (*metabolites)[i]->getMetaboliteKey());
            }
        }
    }
  else
    {
      unsigned int i, iMax = pCopasiReaction->getFunction().getVariables().size();
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

ASTNode* SBMLImporter::isMultipliedByVolume(const ASTNode* node, const std::string& compartmentSBMLId)
{
  ASTNode* result = NULL;
  if (node->getType() == AST_TIMES || node->getType() == AST_DIVIDE)
    {
      ASTNode* pTmpResultNode = new ConverterASTNode(node->getType());
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

bool SBMLImporter::removeUnusedFunctions(CFunctionDB* pTmpFunctionDB)
{
  if (pTmpFunctionDB)
    {
      unsigned C_INT32 step, totalSteps, hStep;
      unsigned C_INT32 i, iMax = this->mpCopasiModel->getReactions().size();
      if (mpImportHandler)
        {
          step = 0;
          totalSteps = iMax;
          hStep = mpImportHandler->addItem("Searching used functions...",
                                           CCopasiParameter::UINT,
                                           & step,
                                           &totalSteps);
        }
      std::set<std::string> functionNameSet;
      for (i = 0;i < iMax;++i)
        {
          const CEvaluationTree* pTree = &this->mpCopasiModel->getReactions()[i]->getFunction();
          if (functionNameSet.find(pTree->getObjectName()) == functionNameSet.end())
            {
              functionNameSet.insert(pTree->getObjectName());
              this->findFunctionCalls(pTree->getRoot(), functionNameSet);
            }
          ++step;
          if (mpImportHandler && !mpImportHandler->progress(hStep)) return false;
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
      while (pTmpFunctionDB->loadedFunctions().size() != 0)
        {
          CEvaluationTree* pTree = pTmpFunctionDB->loadedFunctions()[0];
          pTmpFunctionDB->removeFunction(pTree->getKey());
          if (functionNameSet.find(pTree->getObjectName()) == functionNameSet.end())
            {
              this->mUsedFunctions.erase(pTree->getObjectName());
              //std::cout << "removing " << pTree->getObjectName() << std::endl;
              pFunctionDB->removeFunction(pTree->getKey());
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
