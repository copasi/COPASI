/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLImporter.cpp,v $
   $Revision: 1.68 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/07/11 15:42:29 $
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

#include "utilities/CCopasiMessage.h"

/**
 * Creates and returns a Copasi CModel from the SBMLDocument given as argument.
 */
CModel* SBMLImporter::createCModelFromSBMLDocument(SBMLDocument* sbmlDocument, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  Model* sbmlModel = sbmlDocument->getModel();

  /* Create an empty model and set the title. */
  CModel* copasiModel = new CModel();
  copasi2sbmlmap[copasiModel] = sbmlModel;
  copasiModel->setVolumeUnit(CModel::l);
  copasiModel->setTimeUnit(CModel::s);
  copasiModel->setQuantityUnit(CModel::Mol);

  if (sbmlModel->getNumUnitDefinitions() != 0)
    {
      unsigned int counter;
      for (counter = 0; counter < sbmlModel->getNumUnitDefinitions(); counter++)
        {
          UnitDefinition* uDef = sbmlModel->getUnitDefinition(counter);
          std::string unitId = uDef->getId();
          if (unitId == "substance")
            {
              copasiModel->setQuantityUnit(this->handleSubstanceUnit(uDef));
            }
          else if (unitId == "time")
            {
              copasiModel->setTimeUnit(this->handleTimeUnit(uDef));
            }
          else if (unitId == "volume")
            {
              copasiModel->setVolumeUnit(this->handleVolumeUnit(uDef));
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

  copasiModel->setComments(comment);
  title = sbmlModel->getName();
  if (title == "")
    {
      title = "NoName";
    }
  copasiModel->setTitle(title.c_str());

  /* Set standard units to match the standard units of SBML files. */
  std::map<std::string, CCompartment*> compartmentMap;
  /* Create the compartments */
  unsigned int num = sbmlModel->getNumCompartments();
  unsigned int counter;
  for (counter = 0; counter < num; counter++)
    {
      Compartment* sbmlCompartment = sbmlModel->getCompartment(counter);
      if (sbmlCompartment == NULL)
        {
          fatalError();
        }
      CCompartment* copasiCompartment = this->createCCompartmentFromCompartment(sbmlCompartment, copasiModel, copasi2sbmlmap);
      std::string key = sbmlCompartment->getId();
      if (mLevel == 1)
        {
          key = sbmlCompartment->getName();
        }
      compartmentMap[key] = copasiCompartment;
    }

  /* Create all species */
  num = sbmlModel->getNumSpecies();

  for (counter = num; counter > 0; counter--)
    {
      Species* sbmlSpecies = sbmlModel->getSpecies(counter - 1);
      if (sbmlSpecies == NULL)
        {
          fatalError();
        }
      CCompartment* copasiCompartment = compartmentMap[sbmlSpecies->getCompartment()];
      if (copasiCompartment != NULL)
        {
          CMetab* copasiMetabolite = this->createCMetabFromSpecies(sbmlSpecies, copasiModel, copasiCompartment, copasi2sbmlmap);
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
    }

  /* Create the global Parameters */
  num = sbmlModel->getNumParameters();
  for (counter = 0; counter < num; ++counter)
    {
      Parameter* sbmlParameter = sbmlModel->getParameter(counter);
      if (sbmlParameter == NULL)
        {
          fatalError();
        }
      this->createCModelValueFromParameter(sbmlParameter, copasiModel, copasi2sbmlmap);
    }

  /* Create all reactions */
  num = sbmlModel->getNumReactions();
  for (counter = 0; counter < num; counter++)
    {
      this->createCReactionFromReaction(sbmlModel->getReaction(counter), sbmlModel, copasiModel, copasi2sbmlmap);
    }
  copasiModel->setCompileFlag();
  if (sbmlModel->getNumRules() > 0)
    {
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 3);
    }
  if (sbmlModel->getNumEvents() > 0)
    {
      CCopasiMessage Message(CCopasiMessage::WARNING, MCSBML + 4);
    }

  return copasiModel;
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
      if (szU == "volume")
        {
          /* !!!! create a warning that the spatialSizeUnits will be ignored */
        }
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
  return copasiMetabolite;
}

/**
 * Creates and returns a Copasi CReaction object from the given SBML
 * Reaction object.
 */
CReaction*
SBMLImporter::createCReactionFromReaction(const Reaction* sbmlReaction, const Model* sbmlModel, CModel* copasiModel, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  /* Check if the name of the reaction is unique. */
  if (sbmlReaction == NULL)
    {
      fatalError();
    }
  std::string name = sbmlReaction->getName();
  if (name == "")
    {
      name = sbmlReaction->getId();
    }
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

      node = this->replaceUserDefinedFunctions(node, sbmlModel);
      if (node == NULL)
        {
          delete copasiReaction;
          fatalError();
        }

      this->replacePowerFunctionNodes(node);
      this->replaceLog((ConverterASTNode*)node);
      this->replaceRoot((ConverterASTNode*)node);
      // handling of funny operator calls should now also be
      // handled by the new expression tree conversion functions
      /* if it is a single compartment reaction, we have to divide the whole kinetic
      ** equation by the volume of the compartment because copasi expects
      ** kinetic laws that specify concentration/time for single compartment
      ** reactions.
      */
      if (singleCompartment)
        {
          if (compartment != NULL)
            {
              /* only divide if the volume is not 1 */
              if (compartment->getVolume() != 1.0)
                {
                  /* if the whole function has been multiplied by the same volume
                  ** already, drop one level instead of adding one.
                  */
                  /*
                  if(node->getLeftChild()->isReal()){
                     std::cerr << "isReal: " << node->getLeftChild()->getReal() << std::endl;
                     if(node->getLeftChild()->getType()==AST_REAL_E){
                         std::cerr << "Mantissa: " << node->getLeftChild()->getMantissa() << std::endl;
                         std::cerr << "Exponent: " << node->getLeftChild()->getExponent() << std::endl;
                     }
                     else if(node->getLeftChild()->getType()==AST_REAL){
                         std::cerr << "Real: " << node->getLeftChild()->getReal() << std::endl;                        
                     }
                     else if(node->getLeftChild()->getType()==AST_RATIONAL){
                         std::cerr << "Numerator: " << node->getLeftChild()->getNumerator() << std::endl;
                         std::cerr << "Denominator: " << node->getLeftChild()->getDenominator() << std::endl;
                         
                     }
                   }*/

                  if ((node->getType() == AST_TIMES) && (node->getLeftChild()->isReal() && (node->getLeftChild()->getReal() == compartment->getInitialVolume())))
                    {
                      node = node->getRightChild();
                    }
                  else
                    {
                      ConverterASTNode* tmpNode1 = new ConverterASTNode();
                      tmpNode1->setType(AST_DIVIDE);
                      tmpNode1->addChild(node);
                      ConverterASTNode* tmpNode2 = new ConverterASTNode();
                      tmpNode2->setValue(compartment->getInitialVolume());
                      tmpNode1->addChild(tmpNode2);
                      node = tmpNode1;
                    }
                }
            }
          else
            {
              delete copasiReaction;
              fatalError();
            }
        }

      /* Create a new user defined CKinFunction */
      if (!sbmlId2CopasiCN(node, copasi2sbmlmap, copasiReaction->getParameters())) fatalError();
      CEvaluationNode* pExpressionTreeRoot = CEvaluationTree::convertASTNode(*node);
      if (pExpressionTreeRoot)
        {
          CEvaluationTree* pTmpTree = CEvaluationTree::create(CEvaluationTree::Expression);
          pTmpTree->setRoot(pExpressionTreeRoot);
          if (!copasiReaction->setFunctionFromExpressionTree(pTmpTree, copasi2sbmlmap, this->functionDB))
            {
              // error message
              CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 9, copasiReaction->getObjectName().c_str());
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
  return copasiReaction;
}

/**
 * Replaces SBML user defined functions with the actual function definition.
 */
ConverterASTNode*
SBMLImporter::replaceUserDefinedFunctions(ASTNode* node, const Model* sbmlModel)
{
  ConverterASTNode* newNode = new ConverterASTNode(*node);
  newNode->setChildren(new List());
  /* make the replacement recursively, depth first */
  unsigned int counter;
  for (counter = 0; counter < node->getNumChildren(); counter++)
    {
      ConverterASTNode* newChild = this->replaceUserDefinedFunctions(node->getChild(counter), sbmlModel);
      if (newChild == NULL)
        {
          //throw StdException("Error. Could not replace user defined functions.");
          fatalError();
        }
      newNode->addChild(newChild);
    }
  /* if the new node if a user defined function */
  if (newNode->getType() == AST_FUNCTION)
    {
      /* see if there is a corresponding user defined function */
      FunctionDefinition* funDef = this->getFunctionDefinitionForName(newNode->getName(), sbmlModel);
      if (funDef == NULL)
        {
          fatalError();
        }
      /* make a map that maps every parameter of the function definition to a
      ** node in the actual function call. */
      std::map<std::string, ASTNode*> map = this->createBVarMap(funDef->getMath()->getRightChild(), newNode);
      /* make a new node that replaces all call parameters with the actual
      ** parameters used in the function call. */
      newNode = this->replaceBvars(funDef->getMath()->getRightChild(), map);
    }
  return newNode;
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
SBMLImporter::readSBML(std::string filename, CFunctionDB* funDB, SBMLDocument* pSBMLDocument, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  CModel* pModel = NULL;
  if (funDB != NULL)
    {
      this->functionDB = funDB;
      SBMLReader* reader = new SBMLReader(XML_SCHEMA_VALIDATION_NONE);
      SBMLDocument* sbmlDoc = reader->readSBML(filename);
      sbmlDoc->validate();
      if (sbmlDoc->getNumFatals() > 0)
        {
          ParseMessage * pSBMLMessage = sbmlDoc->getFatal(0);

          CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 2,
                                 pSBMLMessage->getLine(),
                                 pSBMLMessage->getColumn(),
                                 pSBMLMessage->getMessage().c_str());

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
          return NULL;
        }

      delete reader;
      //DebugFile << "Number of Compartments: " << sbmlDoc->getModel()->getNumCompartments() << std::endl;
      //DebugFile << "Number of Metabolites: "  << sbmlDoc->getModel()->getNumSpecies() << std::endl;
      //DebugFile << "Number of Reactions: "    << sbmlDoc->getModel()->getNumReactions()  << std::endl;
      pSBMLDocument = sbmlDoc;
      this->mLevel = pSBMLDocument->getLevel();
      if (mLevel == 1)
        {
          pSBMLDocument->setLevel(2);
          mLevel = pSBMLDocument->getLevel();
        }

      pModel = this->createCModelFromSBMLDocument(sbmlDoc, copasi2sbmlmap);
    }
  else
    {
      //throw StdException("Error. readSBML needs a valid CFunctionDB object.");
      fatalError();
    }
  return pModel;
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
                  tUnit = CModel::m;
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
