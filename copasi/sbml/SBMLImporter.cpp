/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLImporter.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/06/11 08:43:28 $
   End CVS Header */

#include <iostream>
#include <vector>
#include <sstream>
#include <map>

#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReaction.h"
#include "copasi/utilities/CGlobals.h"
#include "copasi/copasi.h"
#include "copasi/function/CNodeK.h"

#include "sbml/SBMLReader.hpp"
#include "sbml/SBMLDocument.hpp"
#include "sbml/Compartment.hpp"
#include "sbml/Species.hpp"
#include "sbml/Reaction.hpp"
#include "sbml/FormulaFormatter.h"
#include "sbml/Model.hpp"

#include "SBMLImporter.h"
#include "ConverterASTNode.h"

/**
 * Creates and returns a Copasi CModel from the SBMLDocument given as argument.
 */
CModel*
SBMLImporter::createCModelFromSBMLDocument(SBMLDocument* sbmlDocument) throw(StdException)
{
  Model* sbmlModel = sbmlDocument->getModel();
  /* Check if there are unit definitions and throw an exception if so. */
  /* Unit definitions will be implemented later. */
  if (sbmlModel->getNumUnitDefinitions() != 0)
    {
      throw StdException("Error. SBML Units not implemented.");
    }

  /* Create an empty model and set the title. */
  CModel* copasiModel = new CModel();
  std::string title = sbmlModel->getName();
  if (title == "")
    {
      title = "NoName";
    }
  copasiModel->setTitle(title.c_str());

  /* Set standard units to match the standard units of SBML files. */
  copasiModel->setVolumeUnit(CModel::l);
  copasiModel->setTimeUnit(CModel::s);
  copasiModel->setQuantityUnit(CModel::Mol);

  std::map<std::string, CCompartment*> compartmentMap;
  /* Create the compartments */
  unsigned int num = sbmlModel->getNumCompartments();
  for (unsigned int counter = 0; counter < num; counter++)
    {
      Compartment* sbmlCompartment = sbmlModel->getCompartment(counter);
      CCompartment* copasiCompartment = this->createCCompartmentFromCompartment(sbmlCompartment, copasiModel);
      compartmentMap[sbmlCompartment->getId()] = copasiCompartment;
    }

  /* Create all species */
  num = sbmlModel->getNumSpecies();
  for (unsigned int counter = num; counter > 0; counter--)
    {
      Species* sbmlSpecies = sbmlModel->getSpecies(counter - 1);
      CMetab* copasiMetabolite = this->createCMetabFromSpecies(sbmlSpecies, copasiModel, compartmentMap[sbmlSpecies->getCompartment()]);
      CCompartment* comp = compartmentMap[sbmlSpecies->getCompartment()];
      this->speciesMap[sbmlSpecies->getId()] = copasiMetabolite;
    }

  /* Create all reactions */
  num = sbmlModel->getNumReactions();
  for (unsigned int counter = 0; counter < num; counter++)
    {
      CReaction* copasiReaction = this->createCReactionFromReaction(sbmlModel->getReaction(counter), sbmlModel, copasiModel);
    }
  copasiModel->compile();
  return copasiModel;
}

/**
 * Creates and returns a Copasi CCompartment from the SBML Compartment
 * given as argument.
 */
CCompartment*
SBMLImporter::createCCompartmentFromCompartment(const Compartment* sbmlCompartment, CModel* copasiModel)
{
  std::string name = sbmlCompartment->getName();
  if (name == "")
    {
      name = sbmlCompartment->getId();
    }
  std::string appendix = "";
  unsigned int counter = 0;
  while (copasiModel->getCompartments().getIndex(name + appendix) != -1)
    {
      counter++;
      std::ostringstream numberStream;
      numberStream << "_" << counter;
      appendix = numberStream.str();
    }
  CCompartment* copasiCompartment = copasiModel->createCompartment(name + appendix, sbmlCompartment->getVolume());
  return copasiCompartment;
}

/**
 * Creates and returns a Copasi CMetab from the given SBML Species object.
 */
CMetab*
SBMLImporter::createCMetabFromSpecies(const Species* sbmlSpecies, CModel* copasiModel, CCompartment* copasiCompartment)
{
  std::string name = sbmlSpecies->getName();
  if (name == "")
    {
      name = sbmlSpecies->getId();
    }
  std::string appendix = "";
  unsigned int counter = 0;
  while (copasiCompartment->getMetabolites().getIndex(name + appendix) != -1)
    {
      counter++;
      std::ostringstream numberStream;
      numberStream << "_" << counter;
      appendix = numberStream.str();
    }

  CMetab* copasiMetabolite = copasiModel->createMetabolite(name + appendix, copasiCompartment->getObjectName());
  if (sbmlSpecies->getConstant() || sbmlSpecies->getBoundaryCondition())
    {
      copasiMetabolite->setStatus(CMetab::METAB_FIXED);
    }
  else
    {
      copasiMetabolite->setStatus(CMetab::METAB_VARIABLE);
    }
  if (sbmlSpecies->isSetInitialAmount())
    {
      copasiMetabolite->setInitialNumber(sbmlSpecies->getInitialAmount()*AVOGADRO); // CHECK UNITS !!!
    }
  else if (sbmlSpecies->isSetInitialConcentration())
    {
      copasiMetabolite->setInitialConcentration(sbmlSpecies->getInitialConcentration());      // CHECK UNITS !!!
    }
  return copasiMetabolite;
}

/**
 * Creates and returns a Copasi CReaction object from the given SBML
 * Reaction object.
 */
CReaction*
SBMLImporter::createCReactionFromReaction(const Reaction* sbmlReaction, const Model* sbmlModel, CModel* copasiModel) throw(StdException)
{
  /* Check if the name of the reaction is unique. */
  std::string name = sbmlReaction->getName();
  if (name == "")
    {
      name = sbmlReaction->getId();
    }
  std::string appendix = "";
  unsigned int counter = 0;
  while (copasiModel->getReactions().getIndex(name + appendix) != -1)
    {
      counter++;
      std::ostringstream numberStream;
      numberStream << "_" << counter;
      appendix = numberStream.str();
    }

  /* create a new reaction with the unique name */
  CReaction* copasiReaction = copasiModel->createReaction(name + appendix);
  /* Add all substrates to the reaction */
  unsigned int num = sbmlReaction->getNumReactants();
  for (unsigned int counter = 0; counter < num; counter++)
    {
      SpeciesReference* sr = sbmlReaction->getReactant(counter);
      float stoich = sr->getStoichiometry() / sr->getDenominator();
      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());
      if (pos == this->speciesMap.end())
        {
          std::cerr << "Error. Could not find CMetab for key " << sr->getSpecies() << "." << std::endl;

          exit(1);
        }
      copasiReaction->addSubstrate(pos->second->getKey(), stoich);
    }

  /* Add all products to the reaction */
  num = sbmlReaction->getNumProducts();
  for (unsigned int counter = 0; counter < num; counter++)
    {
      SpeciesReference* sr = sbmlReaction->getProduct(counter);
      float stoich = sr->getStoichiometry() / sr->getDenominator();
      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());
      if (pos == this->speciesMap.end())
        {
          std::cerr << "Error. Could not find CMetab for key " << sr->getSpecies() << "." << std::endl;
          exit(1);
        }
      copasiReaction->addProduct(pos->second->getKey(), stoich);
    }

  /* Add all modifiers to the reaction */
  num = sbmlReaction->getNumModifiers();
  for (unsigned int counter = 0; counter < num; counter++)
    {
      ModifierSpeciesReference* sr = sbmlReaction->getModifier(counter);
      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());
      if (pos == this->speciesMap.end())
        {
          std::cerr << "Error. Could not find CMetab for key " << sr->getSpecies() << "." << std::endl;
          exit(1);
        }
      copasiReaction->addModifier(pos->second->getKey());
    }

  /* replace substance names with something more meaningfull */
  /* in the newly created CFunction set the types for all parameters and
  ** either a mapping or a value */
  KineticLaw* kLaw = sbmlReaction->getKineticLaw();
  if (!kLaw->isSetMath())
    {
      kLaw->setMathFromFormula();
    }
  const ASTNode* kLawMath = kLaw->getMath();
  ASTNode* node = new ConverterASTNode(*kLawMath);
  node = this->replaceUserDefinedFunctions(node, sbmlModel);
  this->replaceSubstanceNames((ConverterASTNode*)node, sbmlReaction);

  /* Create a new user defined CKinFunction */
  CFunction* cFun = new CKinFunction();
  cFun->setDescription(SBML_formulaToString(node));
  cFun->setType(CFunction::UserDefined);
  cFun->setReversible(sbmlReaction->getReversible() ? TriTrue : TriFalse);
  std::vector<CNodeK*>& v = dynamic_cast<CKinFunction*>(cFun)->getNodes();
  for (unsigned int counter = 0; counter < v.size(); counter++)
    {
      /* assign a type and a mapping */
      CNodeK* node = v[counter];
      if (node->isIdentifier())
        {
          std::string nodeName = node->getName();
          /* if the name start with "substrate_" it is a substrate
             if it starts with product_ it is a product
             if it start with modifier_ it is a modifier
             else it is a parameter
             */
          if (nodeName.find("substrate_") == 0)
            {
              cFun->addParameter(nodeName, CFunctionParameter::FLOAT64, "SUBSTRATE");
            }
          else if (nodeName.find("product_") == 0)
            {
              cFun->addParameter(nodeName, CFunctionParameter::FLOAT64, "PRODUCT");
            }
          else if (nodeName.find("modifier_") == 0)
            {
              cFun->addParameter(nodeName, CFunctionParameter::FLOAT64, "MODIFIER");
            }
          else
            {
              bool found = false;
              /* first check if the parameter is defined in the reaction */
              for (unsigned int x = 0; x < sbmlReaction->getKineticLaw()->getNumParameters(); x++)
                {
                  Parameter* p = sbmlReaction->getKineticLaw()->getParameter(x);
                  if (p->getId() == nodeName)
                    {
                      found = true;
                      cFun->addParameter(nodeName, CFunctionParameter::FLOAT64, "PARAMETER");
                      break;
                    }
                }
              /* if the paramter was not defined in the reaction, check if it
               * is a global parameter */
              if (!found)
                {
                  for (unsigned int x = 0; x < sbmlModel->getNumParameters(); x++)
                    {
                      Parameter* parameter = sbmlModel->getParameter(x);
                      if (parameter->getId() == nodeName)
                        {
                          found = true;
                          cFun->addParameter(nodeName, CFunctionParameter::FLOAT64, "PARAMETER");
                          break;
                        }
                    }
                }
              /* If we have not found the parameter yet, we have a problem.
               * */
              if (!found)
                {
                  throw StdException("Error. Unknown SBML parameter " + nodeName + ".");
                }
            }
        }
    }

  /* create a unique function name by adding the unique reaction name to some
   * prefix */
  std::string functionName = "function_4_" + copasiReaction->getObjectName();
  cFun->setObjectName(functionName);
  copasiReaction->setFunction(cFun);
  /* do the mapping from reaction metabolites to the parameters of the
   * kinetic function */
  for (unsigned int counter = 0; counter < v.size(); counter++)
    {
      /* assign a type and a mapping */
      CNodeK* node = v[counter];
      if (node->isIdentifier())
        {
          std::string nodeName = node->getName();
          /* if the name start with "substrate_" it is a substrate
             if it starts with product_ it is a product
             if it start with modifier_ it is a modifier
             else it is a parameter
             */
          if (nodeName.find("substrate_") == 0)
            {
              std::string speciesKey = nodeName.substr(10);
              copasiReaction->setParameterMapping(nodeName, this->speciesMap[speciesKey]->getKey());
            }
          else if (nodeName.find("product_") == 0)
            {
              std::string speciesKey = nodeName.substr(8);
              copasiReaction->setParameterMapping(nodeName, this->speciesMap[speciesKey]->getKey());
            }
          else if (nodeName.find("modifier_") == 0)
            {
              std::string speciesKey = nodeName.substr(9);
              copasiReaction->setParameterMapping(nodeName, this->speciesMap[speciesKey]->getKey());
            }
          else
            {
              bool found = false;
              for (unsigned int x = 0; x < sbmlReaction->getKineticLaw()->getNumParameters(); x++)
                {
                  Parameter* p = sbmlReaction->getKineticLaw()->getParameter(x);
                  if (p->getId() == nodeName)
                    {
                      found = true;
                      copasiReaction->setParameterValue(nodeName, p->getValue());
                      break;
                    }
                }
              if (!found)
                {
                  for (unsigned int x = 0; x < sbmlModel->getNumParameters(); x++)
                    {
                      Parameter* parameter = sbmlModel->getParameter(x);
                      if (parameter->getId() == nodeName)
                        {
                          found = true;
                          copasiReaction->setParameterValue(nodeName, parameter->getValue());
                          break;
                        }
                    }
                }
              if (!found)
                {
                  throw StdException("Error. Unknown SBML parameter " + nodeName + ".");
                }
            }
        }
    }
  copasiReaction->setReversible(sbmlReaction->getReversible());
  return copasiReaction;
}

/**
 * Traverses the brach of the given AST node recursively and prefixes all substrate
 * parameters with "substrate_", all product parameters with "product_" and all modifier parameters with "modifier_".
 */
void
SBMLImporter::replaceSubstanceNames(ConverterASTNode* node, const Reaction* reaction)
{
  std::map<std::string, std::string> substances;
  for (unsigned int counter = 0; counter < reaction->getNumReactants(); counter++)
    {
      std::string name = reaction->getReactant(counter)->getSpecies();
      substances[name] = "substrate_" + name;
    }
  for (unsigned int counter = 0; counter < reaction->getNumProducts(); counter++)
    {
      std::string name = reaction->getProduct(counter)->getSpecies();
      substances[name] = "product_" + name;
    }
  for (unsigned int counter = 0; counter < reaction->getNumModifiers(); counter++)
    {
      std::string name = reaction->getModifier(counter)->getSpecies();
      substances[name] = "modifier_" + name;
    }
  this->replaceSubstanceNames(node, substances);
}

/**
 * Recursively replaces all parameter names in the branch of the given AST node
 * with the ones give in the map.
 */
void
SBMLImporter::replaceSubstanceNames(ConverterASTNode* node, std::map<std::string, std::string> substances)
{
  if (node->isName())
    {
      std::map<std::string, std::string>::iterator it = substances.find(node->getName());
      if (it != substances.end())
        {
          node->setName(it->second.c_str());
        }
    }
  else
    {
      for (unsigned int counter = 0; counter < node->getNumChildren(); counter++)
        {
          this->replaceSubstanceNames((ConverterASTNode*)node->getChild(counter), substances);
        }
    }
}

/**
 * Replaces SBML user defined functions with the actual funtcion definition.
 */
ConverterASTNode*
SBMLImporter::replaceUserDefinedFunctions(ASTNode* node, const Model* sbmlModel)
{
  /* copy the original node and make the list of children an empty list. */
  ConverterASTNode* newNode = new ConverterASTNode(*node);
  newNode->setChildren(new List());
  for (unsigned int counter = 0; counter < node->getNumChildren(); counter++)
    {
      ASTNode* child = node->getChild(counter);
      /* check if the child is a user defined function */
      if (child->getType() == AST_FUNCTION)
        {
          const std::string functionName = child->getName();
          /* try to find the actual function definition for that name */
          FunctionDefinition* uDefFun = this->getFunctionDefinitionForName(functionName, sbmlModel);
          if (uDefFun != NULL)
            {
              const ASTNode* uDefFunMath = uDefFun->getMath();
              std::map<std::string, ASTNode*> bvarMap = this->createBVarMap(uDefFunMath, child);
              /* create a new child node where the call to the function
               * definition and its children have been replaced by the actual
               * function definition */
              ConverterASTNode* temp = this->replaceBvars(uDefFunMath, bvarMap);
              newNode->addChild(temp);
            }
          else
            {
              throw StdException("Error. Unknown user defined function " + functionName + ".");
            }
        }
      else
        {
          newNode->addChild(this->replaceUserDefinedFunctions(child, sbmlModel));
        }
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
  std::map<std::string, ASTNode*> varMap;
  for (unsigned int counter = 0; counter < uDefFunction->getNumChildren() - 1; counter++)
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
  for (unsigned int counter = 0; counter < sbmlModel->getNumFunctionDefinitions(); counter++)
    {
      if (sbmlModel->getFunctionDefinition(counter)->getId() == name)
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
  ConverterASTNode* newNode = new ConverterASTNode(*node);
  if (node->isName())
    {
      /* check if name matches any in bvarMap */
      /* if yes, replace node with node in bvarMap */
      /* node needs to be set to be a deep copy of the replacement */
      if (bvarMap.find(node->getName()) != bvarMap.end())
        {
          newNode->setName(bvarMap[newNode->getName()]->getName());
        }
    }
  else
    {
      newNode->setChildren(new List());
      for (unsigned int counter = 0; counter < node->getNumChildren(); counter++)
        {
          newNode->addChild(this->replaceBvars(node->getChild(counter), bvarMap));
        }
    }
  return newNode;
}

/**
 * Constructor that initializes speciesMap und compartmentMap.
 */
SBMLImporter::SBMLImporter()
{
  this->speciesMap = std::map<std::string, CMetab*>();
}

/**
 * Destructor that does nothing
 */
SBMLImporter::~SBMLImporter()
{}

/**
 * Function reads an SBML file with libsbml and converts it to a Copasi CModel
 * object which is returned. Deletion of the returned pointer is up to the
 * caller.
 */
CModel*
SBMLImporter::readSBML(std::string filename)
{
  SBMLReader* reader = new SBMLReader(XML_SCHEMA_VALIDATION_NONE);
  SBMLDocument* sbmlDoc = reader->readSBML(filename);
  delete reader;
  CModel* model = this->createCModelFromSBMLDocument(sbmlDoc);
  delete sbmlDoc;
  return model;
}

/**
 * Constructor that sets the error message object to "Error."
 */
StdException::StdException() throw()
{
  this->message = "Error.";
}

/**
 * Constructor that sets the error message object to the string given.
 */
StdException::StdException(const std::string what) throw()
{
  this->message = what;
};

/**
 * Destructor that does nothing.
 */
StdException::~StdException() throw()
{}

/**
 * Returns the error message object as a character array.
 */
const char* StdException::what() const throw()
{
  return this->message.c_str();
}
