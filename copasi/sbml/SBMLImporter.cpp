/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLImporter.cpp,v $
   $Revision: 1.25 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/06/23 17:46:45 $
   End CVS Header */

#include <iostream>
#include <vector>
#include <sstream>
#include <map>

#include "mathematics.h"

#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CMetab.h"
#include "model/CReaction.h"
#include "utilities/CGlobals.h"
#include "copasi.h"
#include "function/CNodeK.h"
#include "function/CFunctionDB.h"

#include "sbml/config.h"
#include "sbml/SBMLReader.hpp"
#include "sbml/SBMLDocument.hpp"
#include "sbml/Compartment.hpp"
#include "sbml/Species.hpp"
#include "sbml/Reaction.hpp"
#include "sbml/FormulaFormatter.h"
#include "sbml/Model.hpp"
#include "sbml/UnitKind.h"

#include "SBMLImporter.h"
#include "ConverterASTNode.h"

/**
 * Creates and returns a Copasi CModel from the SBMLDocument given as argument.
 */
CModel* SBMLImporter::createCModelFromSBMLDocument(SBMLDocument* sbmlDocument)
{
  Model* sbmlModel = sbmlDocument->getModel();
  /* Create an empty model and set the title. */
  //DebugFile << "Setting units." << std::endl;
  CModel* copasiModel = new CModel();
  copasiModel->setVolumeUnit(CModel::l);
  copasiModel->setTimeUnit(CModel::s);
  copasiModel->setQuantityUnit(CModel::Mol);

  if (sbmlModel->getNumUnitDefinitions() != 0)
    {
      for (unsigned int counter = 0; counter < sbmlModel->getNumUnitDefinitions(); counter++)
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

  std::string title = sbmlModel->getName();
  if (title == "")
    {
      title = "NoName";
    }
  copasiModel->setTitle(title.c_str());

  /* Set standard units to match the standard units of SBML files. */
  std::map<std::string, CCompartment*> compartmentMap;
  /* Create the compartments */
  //DebugFile << "Creating compartments." << std::endl;
  unsigned int num = sbmlModel->getNumCompartments();
  for (unsigned int counter = 0; counter < num; counter++)
    {
      Compartment* sbmlCompartment = sbmlModel->getCompartment(counter);
      if (sbmlCompartment == NULL)
        {
          //DebugFile << "Error. Expected SBML Compartment, got NULL pointer." << std::endl;
          throw StdException("Error. Expected SBML Compartment, got NULL pointer.");
        }
      CCompartment* copasiCompartment = this->createCCompartmentFromCompartment(sbmlCompartment, copasiModel);
      std::string key = sbmlCompartment->getId();
      if (!sbmlCompartment->isSetId())
        {
          key = sbmlCompartment->getName();
        }
      compartmentMap[key] = copasiCompartment;
      //DebugFile << "Added compartment with key " << key << " to compartmentMap." << std::endl;
    }

  /* Create all species */
  //DebugFile << "Creating Metabolites." << std::endl;
  num = sbmlModel->getNumSpecies();

  for (counter = num; counter > 0; counter--)
    {
      Species* sbmlSpecies = sbmlModel->getSpecies(counter - 1);
      if (sbmlSpecies == NULL)
        {
          //DebugFile << "Error. Expected SBML species, got NULL pointer." << std::endl;
          throw StdException("Error. Expected SBML species, got NULL pointer.");
        }
      CCompartment* copasiCompartment = compartmentMap[sbmlSpecies->getCompartment()];
      if (copasiCompartment != NULL)
        {
          CMetab* copasiMetabolite = this->createCMetabFromSpecies(sbmlSpecies, copasiModel, copasiCompartment);
          std::string key;
          if (!sbmlSpecies->isSetId())
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
          //DebugFile << "Error. Could not find compartment " << sbmlSpecies->getCompartment() << std::endl;
          throw StdException("Error. Could not find compartment " + sbmlSpecies->getCompartment() + ".");
        }
    }

  /* Create all reactions */
  //DebugFile << "Creating reactions." << std::endl;
  num = sbmlModel->getNumReactions();
  for (counter = 0; counter < num; counter++)
    {
      this->createCReactionFromReaction(sbmlModel->getReaction(counter), sbmlModel, copasiModel, compartmentMap);
    }
  copasiModel->compile2();
  return copasiModel;
}

/**
 * Creates and returns a Copasi CCompartment from the SBML Compartment
 * given as argument.
 */
CCompartment*
SBMLImporter::createCCompartmentFromCompartment(const Compartment* sbmlCompartment, CModel* copasiModel)
{
  if (sbmlCompartment->isSetUnits())
    {
      std::string cU = sbmlCompartment->getUnits();
      if (cU != "volume" && cU != "area" && cU != "length")
        {
          throw StdException("Error. Compartment unit other than \"volume\", \"area\" or \"length\" are not supported.");
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
  unsigned int counter = 0;
  while (copasiModel->getCompartments().getIndex(name + appendix) != static_cast < unsigned C_INT32
         > (-1))
    {
      counter++;
      std::ostringstream numberStream;
      numberStream << "_" << counter;
      appendix = numberStream.str();
    }
  CCompartment* copasiCompartment = copasiModel->createCompartment(name + appendix, sbmlCompartment->getVolume());
  //DebugFile << "Created Compartment: " << copasiCompartment->getObjectName() << std::endl;
  return copasiCompartment;
}

/**
 * Creates and returns a Copasi CMetab from the given SBML Species object.
 */
CMetab*
SBMLImporter::createCMetabFromSpecies(const Species* sbmlSpecies, CModel* copasiModel, CCompartment* copasiCompartment)
{
  if (sbmlSpecies->isSetSubstanceUnits())
    {
      std::string cU = sbmlSpecies->getSubstanceUnits();
      if (cU != "substance")
        {
          throw StdException("Error. Compartment unit other than \"substance\" are not supported.");
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
  unsigned int counter = 0;
  while (copasiCompartment->getMetabolites().getIndex(name + appendix) != static_cast<unsigned C_INT32>(-1))
    {
      counter++;
      std::ostringstream numberStream;
      numberStream << "_" << counter;
      appendix = numberStream.str();
    }

  CMetab* copasiMetabolite = copasiModel->createMetabolite(name + appendix, copasiCompartment->getObjectName());
  if (copasiMetabolite == NULL)
    {
      //DebugFile << "Could not create Copasi metabolite." << std::endl;
      throw StdException("Error. Could not create copasi metabolite.");
    }
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
  //DebugFile << "Created metabolite: " << copasiMetabolite->getObjectName() << std::endl;
  return copasiMetabolite;
}

/**
 * Creates and returns a Copasi CReaction object from the given SBML
 * Reaction object.
 */
CReaction*
SBMLImporter::createCReactionFromReaction(const Reaction* sbmlReaction, const Model* sbmlModel, CModel* copasiModel, std::map<std::string, CCompartment*> compartmentMap)
{
  /* Check if the name of the reaction is unique. */
  if (sbmlReaction == NULL)
    {
      //DebugFile << "createCReactionFromReaction get NULL pointer as first argument." << std::endl;
      throw StdException("Error. Function createCReactionFromReaction got NULL pointer as first argument.");
    }
  std::string name = sbmlReaction->getName();
  if (name == "")
    {
      name = sbmlReaction->getId();
    }
  std::string appendix = "";
  unsigned int counter = 0;
  while (copasiModel->getReactions().getIndex(name + appendix) != static_cast<unsigned C_INT32>(-1))
    {
      counter++;
      std::ostringstream numberStream;
      numberStream << "_" << counter;
      appendix = numberStream.str();
    }

  /* create a new reaction with the unique name */
  CReaction* copasiReaction = copasiModel->createReaction(name + appendix);
  if (copasiReaction == NULL)
    {
      //DebugFile << "Could not create Copasi reaction." << std::endl;
      throw StdException("Error. Could not create Copasi reaction.");
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
          //DebugFile << "Expected SpeciesReference, got NULL pointer." << std::endl;
          throw StdException("Error. Expected SpeciesReference, got NULL pointer.");
        }
      float stoich = sr->getStoichiometry() / sr->getDenominator();
      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());
      if (pos == this->speciesMap.end())
        {
          //DebugFile << "Error. Could not find CMetab for key " << sr->getSpecies() << "." << std::endl;
          throw StdException("Error. Could not find CMetab for key " + sr->getSpecies() + ".");

          //exit(1);
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
          //DebugFile << "Expected SpeciesReference, got NULL pointer." << std::endl;
          throw StdException("Error. Expected SpeciesReference, got NULL pointer.");
        }
      float stoich = sr->getStoichiometry() / sr->getDenominator();
      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());
      if (pos == this->speciesMap.end())
        {
          //DebugFile << "Error. Could not find CMetab for key " << sr->getSpecies() << "." << std::endl;
          throw StdException("Error. Could not find CMetab for key " + sr->getSpecies() + ".");
          //exit(1);
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
          //DebugFile << "Expected SpeciesReference, got NULL pointer." << std::endl;
          throw StdException("Error. Expected SpeciesReference, got NULL pointer.");
        }
      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());
      if (pos == this->speciesMap.end())
        {
          //DebugFile << "Error. Could not find CMetab for key " << sr->getSpecies() << "." << std::endl;
          throw StdException("Error. Could not find CMetab for key " + sr->getSpecies() + ".");
          //exit(1);
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

  /* replace substance names with something more meaningfull */
  /* in the newly created CFunction set the types for all parameters and
  ** either a mapping or a value */
  KineticLaw* kLaw = sbmlReaction->getKineticLaw();
  if (kLaw != NULL)
    {
      if (kLaw->isSetSubstanceUnits())
        {
          std::string cU = kLaw->getSubstanceUnits();
          if (cU != "substance")
            {
              throw StdException("Error. KineticLaw substance unit other than \"substance\" are not supported.");
            }
        }
      if (kLaw->isSetTimeUnits())
        {
          std::string cU = kLaw->getTimeUnits();
          if (cU != "time")
            {
              throw StdException("Error. KineticLaw time unit other than \"time\" are not supported.");
            }
        }

      if (!kLaw->isSetMath())
        {
          kLaw->setMathFromFormula();
        }
      const ASTNode* kLawMath = kLaw->getMath();
      if (kLawMath == NULL)
        {
          //DebugFile << "Expected ASTNode, got NULL pointer." << std::endl;
          throw StdException("Error. Expected ASTNode, got NULL pointer.");
        }
      //ConverterASTNode::printASTNode(kLawMath);
      ASTNode* node = new ConverterASTNode(*kLawMath);

      node = this->replaceUserDefinedFunctions(node, sbmlModel);
      if (node == NULL)
        {
          //DebugFile << "Replacing the user defined functions failed." << std::endl;
          throw StdException("Error. Replacing the user defined functions failed.");
        }
      this->replaceCompartmentNodes((ConverterASTNode*)node, compartmentMap);
      this->replaceSubstanceNames((ConverterASTNode*)node, sbmlReaction);
      this->replacePowerFunctionNodes(node);
      //ConverterASTNode::printASTNode(node);
      /* if it is a single compartment reaction, we have to devide the whole kinetic
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
                      //std::cerr << "Multiplying with volume: " << compartment->getInitialVolume() << std::endl;
                      tmpNode1->addChild(tmpNode2);
                      node = tmpNode1;
                    }
                }
            }
          else
            {
              //DebugFile << "Error. Could not determine compartment for single compartment reaction." << std::endl;
              throw StdException("Error. Could not determine compartment for single compartment reaction.");
            }
        }

      /* Create a new user defined CKinFunction */

      std::string functionName = "function_4_" + copasiReaction->getObjectName();

      appendix = "";
      counter = 0;
      /* create a unique function name by adding the unique reaction name to some
       * prefix */
      while (this->functionDB->findFunction(functionName + appendix) != NULL)
        {
          counter++;
          std::ostringstream numberStream;
          numberStream << "_" << counter;
          appendix = numberStream.str();
        }

      CFunction* cFun = this->functionDB->createFunction(functionName + appendix, CFunction::UserDefined);
      //ConverterASTNode::printASTNode(node);
      //DebugFile << "Kinetic Law: " << SBML_formulaToString(node) << std::endl;
      //std::cerr << "Kinetic Law: " << SBML_formulaToString(node) << std::endl;
      if (cFun == NULL)
        {
          //DebugFile << "Could not create function " << functionName << "." << std::endl;
          throw StdException("Error. Could not create function for name " + functionName + ".");
        }
      cFun->setDescription(SBML_formulaToString(node));
      cFun->setType(CFunction::UserDefined);
      cFun->setReversible(sbmlReaction->getReversible() ? TriTrue : TriFalse);
      //create parameters
      std::vector<CNodeK*>& v = dynamic_cast<CKinFunction*>(cFun)->getNodes();
      unsigned int counter;
      for (counter = 0; counter < v.size(); counter++)
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
                      Parameter* parameter = sbmlReaction->getKineticLaw()->getParameter(x);
                      std::string parameterName;
                      //DebugFile << "local parameter " << x << ": " << parameter << std::endl;
                      if (parameter == NULL)
                        {
                          //DebugFile << "Expected SBML parameter, got NULL pointer." << std::endl;
                          throw StdException("Error. Expected SBML parameter, got NULL pointer.");
                        }
                      if (parameter->isSetId())
                        {
                          parameterName = parameter->getId();
                        }
                      else
                        {
                          parameterName = parameter->getName();
                        }
                      if (parameter->isSetUnits())
                        {
                          /* !!! */
                          /* create a warning that the units will be ignored */
                        }
                      if (parameterName == nodeName)
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
                          //DebugFile << "global parameter " << x << ": " << parameter << std::endl;
                          if (parameter == NULL)
                            {
                              //DebugFile << "Expected SBML parameter, got NULL pointer." << std::endl;
                              throw StdException("Error. Expected SBML parameter, got NULL pointer.");
                            }
                          std::string parameterName;
                          if (parameter->isSetId())
                            {
                              parameterName = parameter->getId();
                            }
                          else
                            {
                              parameterName = parameter->getName();
                            }
                          if (parameter->isSetUnits())
                            {
                              /* !!! */
                              /* create a warning that the units will be ignored */
                            }
                          if (parameterName == nodeName)
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
                      if (nodeName == "Pi")
                        {
                          cFun->addParameter(nodeName, CFunctionParameter::FLOAT64, "PARAMETER");
                        }
                      else if (nodeName == "ExponentialE")
                        {
                          cFun->addParameter(nodeName, CFunctionParameter::FLOAT64, "PARAMETER");
                        }
                      else
                        {
                          //DebugFile << "Could not find parameter: " << nodeName << std::endl;
                          throw StdException("Error. Unknown SBML parameter " + nodeName + ".");
                        }
                    }
                }
            }
        }

      //for internal structures in the function that can only be set after defining the parameters
      static_cast<CKinFunction*>(cFun)->compile();
      copasiReaction->setFunction(cFun);

      /* do the mapping from reaction metabolites to the parameters of the
       * kinetic function */
      for (counter = 0; counter < v.size(); counter++)
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
                  CMetab* cM = this->speciesMap[speciesKey];
                  if (cM != NULL)
                    {
                      copasiReaction->setParameterMapping(nodeName, cM->getKey());
                    }
                  else
                    {
                      throw StdException("Error. Could not find CMetab for key " + speciesKey + ".");
                    }
                }
              else if (nodeName.find("product_") == 0)
                {
                  std::string speciesKey = nodeName.substr(8);
                  CMetab* cM = this->speciesMap[speciesKey];
                  if (cM != NULL)
                    {
                      copasiReaction->setParameterMapping(nodeName, cM->getKey());
                    }
                  else
                    {
                      throw StdException("Error. Could not find CMetab for key " + speciesKey + ".");
                    }
                }
              else if (nodeName.find("modifier_") == 0)
                {
                  std::string speciesKey = nodeName.substr(9);
                  CMetab* cM = this->speciesMap[speciesKey];
                  if (cM != NULL)
                    {
                      copasiReaction->setParameterMapping(nodeName, cM->getKey());
                    }
                  else
                    {
                      throw StdException("Error. Could not find CMetab for key " + speciesKey + ".");
                    }
                }
              else
                {
                  bool found = false;
                  for (unsigned int x = 0; x < sbmlReaction->getKineticLaw()->getNumParameters(); x++)
                    {
                      Parameter* parameter = sbmlReaction->getKineticLaw()->getParameter(x);
                      if (parameter == NULL)
                        {
                          //DebugFile << "Expected SBML parameter, got NULL pointer." << std::endl;
                          throw StdException("Error. Expected SBML parameter, got NULL pointer.");
                        }
                      std::string parameterName;
                      if (parameter->isSetId())
                        {
                          parameterName = parameter->getId();
                        }
                      else
                        {
                          parameterName = parameter->getName();
                        }
                      if (parameterName == nodeName)
                        {
                          found = true;
                          copasiReaction->setParameterValue(nodeName, parameter->getValue());
                          break;
                        }
                    }
                  if (!found)
                    {
                      for (unsigned int x = 0; x < sbmlModel->getNumParameters(); x++)
                        {
                          Parameter* parameter = sbmlModel->getParameter(x);
                          if (parameter == NULL)
                            {
                              //DebugFile << "Expected SBML parameter, got NULL pointer." << std::endl;
                              throw StdException("Error. Expected SBML parameter, got NULL pointer.");
                            }
                          std::string parameterName;
                          if (parameter->isSetId())
                            {
                              parameterName = parameter->getId();
                            }
                          else
                            {
                              parameterName = parameter->getName();
                            }
                          if (parameterName == nodeName)
                            {
                              found = true;
                              copasiReaction->setParameterValue(nodeName, parameter->getValue());
                              break;
                            }
                        }
                    }
                  if (!found)
                    {
                      if (nodeName == "Pi")
                        {
                          copasiReaction->setParameterValue(nodeName, M_PI);
                        }
                      else if (nodeName == "ExponentialE")
                        {
                          copasiReaction->setParameterValue(nodeName, M_E);
                        }
                      else
                        {
                          //DebugFile << "Could not find parameter: " << nodeName << std::endl;
                          throw StdException("Error. Unknown SBML parameter " + nodeName + ".");
                        }
                    }
                }
            }
        }
    }
  else
    {
      /* if no KineticLaw was defined for the reaction. */
      copasiReaction->setFunction(NULL);
    }
  copasiReaction->setReversible(sbmlReaction->getReversible());
  //DebugFile << "Created reaction: " << copasiReaction->getObjectName() << std::endl;
  return copasiReaction;
}

/**
 * Traverses the brach of the given AST node recursively and prefixes all substrate
 * parameters with "substrate_", all product parameters with "product_" and all modifier parameters with "modifier_".
 */
void
SBMLImporter::replaceSubstanceNames(ConverterASTNode* node, const Reaction* reaction)
{
  std::map< std::string, std::map<std::string, std::string> > substances;
  substances["substrates"] = std::map< std::string, std::string >();
  substances["products"] = std::map< std::string, std::string >();
  substances["modifiers"] = std::map< std::string, std::string >();
  unsigned int counter;
  for (counter = 0; counter < reaction->getNumReactants(); counter++)
    {
      std::string name = reaction->getReactant(counter)->getSpecies();
      if (name.find("substrate_") == 0)
        {
          substances["substrates"][name] = name;
        }
      else
        {
          substances["substrates"][name] = "substrate_" + name;
        }
    }
  for (counter = 0; counter < reaction->getNumProducts(); counter++)
    {
      std::string name = reaction->getProduct(counter)->getSpecies();
      if (name.find("product_") == 0)
        {
          substances["products"][name] = name;
        }
      else
        {
          substances["products"][name] = "product_" + name;
        }
    }
  for (counter = 0; counter < reaction->getNumModifiers(); counter++)
    {
      std::string name = reaction->getModifier(counter)->getSpecies();
      if (name.find("modifier_") == 0)
        {
          substances["modifiers"][name] = name;
        }
      else
        {
          substances["modifiers"][name] = "modifier_" + name;
        }
    }
  this->replaceSubstanceNames(node, substances, reaction->getReversible());
}

/**
 * Recursively replaces all parameter names in the branch of the given AST node
 * with the ones give in the map.
 */
void
SBMLImporter::replaceSubstanceNames(ConverterASTNode* node, std::map< std::string, std::map<std::string, std::string > > substMap, bool reversible)
{
  if (node->isName())
    {
      bool set = false;
      std::map<std::string, std::string> substances = substMap["products"];
      if (reversible)
        {
          std::map<std::string, std::string>::iterator it = substances.find(node->getName());
          if (it != substances.end())
            {
              node->setName(it->second.c_str());
              set = true;
            }
        }
      substances = substMap["substrates"];
      std::map<std::string, std::string>::iterator it = substances.find(node->getName());
      if (it != substances.end())
        {
          node->setName(it->second.c_str());
          set = true;
        }
      substances = substMap["modifiers"];
      it = substances.find(node->getName());
      if (it != substances.end())
        {
          node->setName(it->second.c_str());
          set = true;
        }
      /* if there was no replacement so far, it might still be a modifier that has not been specified in the listOfModifiers
       */
      if (!set)
        {
          std::map<std::string, CMetab*>::iterator pos = this->speciesMap.find(node->getName());
          if (pos != this->speciesMap.end())
            {
              std::string mName = node->getName();
              if (mName.find("modifier_") != 0)
                {
                  mName = "modifier_" + mName;
                }
              node->setName(mName.c_str());
            }
        }
    }
  else
    {
      for (unsigned int counter = 0; counter < node->getNumChildren(); counter++)
        {
          this->replaceSubstanceNames((ConverterASTNode*)node->getChild(counter), substMap, reversible);
        }
    }
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
  for (unsigned int counter = 0; counter < node->getNumChildren(); counter++)
    {
      ConverterASTNode* newChild = this->replaceUserDefinedFunctions(node->getChild(counter), sbmlModel);
      if (newChild == NULL)
        {
          throw StdException("Error. Could not replace user defined functions.");
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
          throw StdException((std::string("Error. Could not find user defined function with name ") + std::string(newNode->getName())).c_str());
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
      throw StdException("Error. The number of parameters to the function call " + functionName + " does not correspond to the number of parameters givven in the definition of the function.");
    }
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
      for (unsigned int counter = 0; counter < node->getNumChildren(); counter++)
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
      for (unsigned int counter = 0; counter < node->getNumChildren(); counter++)
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
SBMLImporter::readSBML(std::string filename, CFunctionDB* funDB)
{
  if (funDB != NULL)
    {
      try
        {
          this->functionDB = funDB;
          SBMLReader* reader = new SBMLReader(XML_SCHEMA_VALIDATION_NONE);
          SBMLDocument* sbmlDoc = reader->readSBML(filename);
          delete reader;
          //DebugFile << "Number of Compartments: " << sbmlDoc->getModel()->getNumCompartments() << std::endl;
          //DebugFile << "Number of Metabolites: "  << sbmlDoc->getModel()->getNumSpecies() << std::endl;
          //DebugFile << "Number of Reactions: "    << sbmlDoc->getModel()->getNumReactions()  << std::endl;

          CModel* model = this->createCModelFromSBMLDocument(sbmlDoc);
          delete sbmlDoc;
          return model;
        }
      catch (StdException ex)
        {
          //DebugFile << ex.what() << std::endl;
          throw ex;
        }
    }
  else
    {
      throw StdException("Error. readSBML needs a valid CFunctionDB object.");
    }
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
      throw StdException("Error. Argument to handleSubstanceUnit is NULL pointer.");
    }
  if (uDef->getNumUnits() == 1)
    {
      Unit* u = uDef->getUnit(0);
      if (u == NULL)
        {
          //DebugFile << "Expected Unit, got NULL pointer." << std::endl;
          throw StdException("Error. Expected Unit, got NULL pointer.");
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
              throw StdException("Error. Invalid SBML substance unit definition.");
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
              throw StdException("Error. Invalid SBML substance unit definition.");
            }
        }
      else
        {
          throw StdException("Error. Invalid SBML volume unit definition.");
        }
    }
  else
    {
      throw StdException("Error. Invalid SBML substance unit definition.");
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
      throw StdException("Error. Argument to handleTimeUnits is NULL pointer.");
    }
  if (uDef->getNumUnits() == 1)
    {
      Unit* u = uDef->getUnit(0);
      if (u == NULL)
        {
          //DebugFile << "Expected Unit, got NULL pointer." << std::endl;
          throw StdException("Error. Expected Unit, got NULL pointer.");
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
                  throw StdException("Error. Invalid SBML time unit definition.");
                }
            }
          else
            {
              throw StdException("Error. Invalid SBML time unit definition.");
            }
        }
      else
        {
          throw StdException("Error. Invalid SBML time unit definition.");
        }
    }
  else
    {
      throw StdException("Error. Invalid SBML time unit definition.");
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
      throw StdException("Error. Argument to handleVolumeUnit is NULL pointer.");
    }
  if (uDef->getNumUnits() == 1)
    {
      Unit* u = uDef->getUnit(0);
      if (u == NULL)
        {
          //DebugFile << "Expected Unit, got NULL pointer." << std::endl;
          throw StdException("Error. Expected Unit, got NULL pointer.");
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
              throw StdException("Error. Invalid SBML volume unit definition.");
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
              throw StdException("Error. Invalid SBML volume unit definition.");
            }
        }
      else
        {
          throw StdException("Error. Invalid SBML volume unit definition.");
        }
    }
  else
    {
      throw StdException("Error. Invalid SBML volume unit definition.");
    }
  return vUnit;
}

void SBMLImporter::replaceCompartmentNodes(ConverterASTNode* node, std::map<std::string, CCompartment*> compartmentMap)
{
  if (node->getType() == AST_NAME)
    {
      std::map<std::string, CCompartment*>::iterator pos = compartmentMap.find(node->getName());
      if (pos != compartmentMap.end())
        {
          node->setType(AST_REAL);
          node->setValue(pos->second->getInitialVolume());
        }
    }
  unsigned int num = node->getNumChildren();
  for (unsigned int counter = 0; counter < num; counter++)
    {
      this->replaceCompartmentNodes((ConverterASTNode*)(node->getChild(counter)), compartmentMap);
    }
}
