/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLImporter.cpp,v $
   $Revision: 1.50 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/13 16:29:06 $
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
#include "function/CFunctionDB.h"

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
//#include "sbml/SBMLTypes.h"
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
      if (!sbmlCompartment->isSetId())
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
      this->createCReactionFromReaction(sbmlModel->getReaction(counter), sbmlModel, copasiModel, compartmentMap, copasi2sbmlmap);
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
          //throw StdException("Error. Compartment unit other than \"volume\", \"area\" or \"length\" are not supported.");
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
  unsigned int counter = 0;
  while (copasiModel->getCompartments().getIndex(name + appendix) != static_cast < unsigned C_INT32
         > (-1))
    {
      counter++;
      std::ostringstream numberStream;
      numberStream << "_" << counter;
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
      value = std::numeric_limits<C_FLOAT64>::signaling_NaN();
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
          //throw StdException("Error. Compartment unit other than \"substance\" are not supported.");
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
      //throw StdException("Error. Could not create copasi metabolite.");
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
      copasiMetabolite->setInitialNumber(sbmlSpecies->getInitialAmount()*AVOGADRO); // CHECK UNITS !!!
    }
  else if (sbmlSpecies->isSetInitialConcentration())
    {
      copasiMetabolite->setInitialConcentration(sbmlSpecies->getInitialConcentration());      // CHECK UNITS !!!
    }
  else
    {
      copasiMetabolite->setInitialConcentration(std::numeric_limits<C_FLOAT64>::signaling_NaN());      // CHECK UNITS !!!
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
SBMLImporter::createCReactionFromReaction(const Reaction* sbmlReaction, const Model* sbmlModel, CModel* copasiModel, std::map<std::string, CCompartment*> compartmentMap, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  /* Check if the name of the reaction is unique. */
  if (sbmlReaction == NULL)
    {
      //DebugFile << "createCReactionFromReaction get NULL pointer as first argument." << std::endl;
      //throw StdException("Error. Function createCReactionFromReaction got NULL pointer as first argument.");
      fatalError();
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
  copasi2sbmlmap[copasiReaction] = const_cast<Reaction*>(sbmlReaction);
  if (copasiReaction == NULL)
    {
      //DebugFile << "Could not create Copasi reaction." << std::endl;
      //throw StdException("Error. Could not create Copasi reaction.");
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
          //DebugFile << "Expected SpeciesReference, got NULL pointer." << std::endl;
          //throw StdException("Error. Expected SpeciesReference, got NULL pointer.");
          fatalError();
        }
      float stoich = sr->getStoichiometry() / sr->getDenominator();
      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());
      if (pos == this->speciesMap.end())
        {
          //DebugFile << "Error. Could not find CMetab for key " << sr->getSpecies() << "." << std::endl;
          //throw StdException("Error. Could not find CMetab for key " + sr->getSpecies() + ".");
          fatalError();

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
          //throw StdException("Error. Expected SpeciesReference, got NULL pointer.");
          fatalError();
        }
      float stoich = sr->getStoichiometry() / sr->getDenominator();
      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());
      if (pos == this->speciesMap.end())
        {
          //DebugFile << "Error. Could not find CMetab for key " << sr->getSpecies() << "." << std::endl;
          //throw StdException("Error. Could not find CMetab for key " + sr->getSpecies() + ".");
          fatalError();
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
          //throw StdException("Error. Expected SpeciesReference, got NULL pointer.");
          fatalError();
        }
      std::map<std::string, CMetab*>::iterator pos;
      pos = this->speciesMap.find(sr->getSpecies());
      if (pos == this->speciesMap.end())
        {
          //DebugFile << "Error. Could not find CMetab for key " << sr->getSpecies() << "." << std::endl;
          //throw StdException("Error. Could not find CMetab for key " + sr->getSpecies() + ".");
          fatalError();
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
              //throw StdException("Error. KineticLaw substance unit other than \"substance\" are not supported.");
              fatalError();
            }
        }
      if (kLaw->isSetTimeUnits())
        {
          std::string cU = kLaw->getTimeUnits();
          if (cU != "time")
            {
              //throw StdException("Error. KineticLaw time unit other than \"time\" are not supported.");
              fatalError();
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
          //throw StdException("Error. Expected ASTNode, got NULL pointer.");
          fatalError();
        }
      //ConverterASTNode::printASTNode(kLawMath);
      ASTNode* node = new ConverterASTNode(*kLawMath);

      node = this->replaceUserDefinedFunctions(node, sbmlModel);
      if (node == NULL)
        {
          //DebugFile << "Replacing the user defined functions failed." << std::endl;
          //throw StdException("Error. Replacing the user defined functions failed.");
          fatalError();
        }
      this->replaceCompartmentNodes((ConverterASTNode*)node, compartmentMap);
      this->replaceSubstanceNames((ConverterASTNode*)node, sbmlReaction);
      this->replacePowerFunctionNodes(node);
      this->replaceLog((ConverterASTNode*)node);
      this->replaceRoot((ConverterASTNode*)node);
      this->replaceFunnyOperatorCalls((ConverterASTNode*)node);
      //ConverterASTNode::printASTNode(node);
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
                      //std::cerr << "Multiplying with volume: " << compartment->getInitialVolume() << std::endl;
                      tmpNode1->addChild(tmpNode2);
                      node = tmpNode1;
                    }
                }
            }
          else
            {
              //DebugFile << "Error. Could not determine compartment for single compartment reaction." << std::endl;
              //throw StdException("Error. Could not determine compartment for single compartment reaction.");
              fatalError();
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
          //throw StdException("Error. Could not create function for name " + functionName + ".");
          fatalError();
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
                  unsigned int x;
                  for (x = 0; x < sbmlReaction->getKineticLaw()->getNumParameters(); x++)
                    {
                      Parameter* parameter = sbmlReaction->getKineticLaw()->getParameter(x);
                      std::string parameterName;
                      //DebugFile << "local parameter " << x << ": " << parameter << std::endl;
                      if (parameter == NULL)
                        {
                          //DebugFile << "Expected SBML parameter, got NULL pointer." << std::endl;
                          //throw StdException("Error. Expected SBML parameter, got NULL pointer.");
                          fatalError();
                        }
                      if (parameter->isSetId())
                        {
                          parameterName = parameter->getId();
                        }
                      else
                        {
                          // a parameter must have an id.
                          fatalError();
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
                      unsigned int x;
                      for (x = 0; x < sbmlModel->getNumParameters(); x++)
                        {
                          Parameter* parameter = sbmlModel->getParameter(x);
                          //DebugFile << "global parameter " << x << ": " << parameter << std::endl;
                          if (parameter == NULL)
                            {
                              //DebugFile << "Expected SBML parameter, got NULL pointer." << std::endl;
                              //throw StdException("Error. Expected SBML parameter, got NULL pointer.");
                              fatalError();
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
                          //throw StdException("Error. Unknown SBML parameter " + nodeName + ".");
                          fatalError();
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
                      //throw StdException("Error. Could not find CMetab for key " + speciesKey + ".");
                      fatalError();
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
                      //throw StdException("Error. Could not find CMetab for key " + speciesKey + ".");
                      fatalError();
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
                      //throw StdException("Error. Could not find CMetab for key " + speciesKey + ".");
                      fatalError();
                    }
                }
              else
                {
                  bool found = false;
                  unsigned int x;
                  for (x = 0; x < sbmlReaction->getKineticLaw()->getNumParameters(); x++)
                    {
                      Parameter* parameter = sbmlReaction->getKineticLaw()->getParameter(x);
                      if (parameter == NULL)
                        {
                          //DebugFile << "Expected SBML parameter, got NULL pointer." << std::endl;
                          //throw StdException("Error. Expected SBML parameter, got NULL pointer.");
                          fatalError();
                        }
                      std::string parameterName;
                      if (parameter->isSetId())
                        {
                          parameterName = parameter->getId();
                        }
                      else
                        {
                          // a parameter must have an id
                          fatalError();
                        }
                      if (parameterName == nodeName)
                        {
                          found = true;
                          if (parameter->isSetValue())
                            {
                              copasiReaction->setParameterValue(nodeName, parameter->getValue());
                            }
                          else
                            {
                              copasiReaction->setParameterValue(nodeName, std::numeric_limits<C_FLOAT64>::signaling_NaN());
                            }
                          break;
                        }
                    }
                  if (!found)
                    {
                      unsigned int x;
                      for (x = 0; x < sbmlModel->getNumParameters(); x++)
                        {
                          Parameter* parameter = sbmlModel->getParameter(x);
                          if (parameter == NULL)
                            {
                              //DebugFile << "Expected SBML parameter, got NULL pointer." << std::endl;
                              //throw StdException("Error. Expected SBML parameter, got NULL pointer.");
                              fatalError();
                            }
                          std::string parameterName;
                          if (parameter->isSetId())
                            {
                              parameterName = parameter->getId();
                            }
                          else
                            {
                              // does not make sense -> parameterName = parameter->getName();
                              // a parameter has to have an id.
                              fatalError();
                            }
                          if (parameterName == nodeName)
                            {
                              found = true;
                              // find the global parameter
                              CModelValue* value = NULL;
                              std::map<CCopasiObject*, SBase*>::iterator it = copasi2sbmlmap.begin();
                              std::map<CCopasiObject*, SBase*>::iterator endIt = copasi2sbmlmap.end();
                              while (it != endIt)
                                {
                                  Parameter* p = dynamic_cast<Parameter*>(it->second);
                                  if (p != NULL && p->getId() == parameterName)
                                    {
                                      value = (CModelValue*)(it->first);
                                      break;
                                    }
                                  ++it;
                                }
                              // if it is a global sbml parameter, there must be an entry in the map
                              // otherwise there is an error
                              if (value == NULL)
                                {
                                  fatalError();
                                }
                              //copasiReaction->setParameterValue(nodeName, parameter->getValue());
                              copasiReaction->setParameterMapping(nodeName, value->getKey());
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
                          //throw StdException("Error. Unknown SBML parameter " + nodeName + ".");
                          fatalError();
                        }
                    }
                }
            }
        }
    }
  else
    {
      /* if no KineticLaw was defined for the reaction. */
      // create a fatalError until copasi can handle NULL
      // functions
      copasiReaction->setFunction(NULL);
      //fatalError();
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
  KineticLaw* kLaw = reaction->getKineticLaw();
  std::vector<std::string> shadowedSubstances;
  for (counter = 0; counter < reaction->getNumReactants(); counter++)
    {
      std::string name = reaction->getReactant(counter)->getSpecies();
      bool isShadowed = false;
      unsigned int counter2;
      if (kLaw)
        {
          for (counter2 = 0; counter2 < kLaw->getNumParameters();++counter2)
            {
              Parameter* param = kLaw->getParameter(counter2);
              if (param->getId() == name)
                {
                  isShadowed = true;
                  shadowedSubstances.push_back(name);
                  break;
                }
            }
        }
      if (!isShadowed)
        {
          if (name.find("substrate_") == 0)
            {
              substances["substrates"][name] = name;
            }
          else
            {
              substances["substrates"][name] = "substrate_" + name;
            }
        }
    }
  for (counter = 0; counter < reaction->getNumProducts(); counter++)
    {
      std::string name = reaction->getProduct(counter)->getSpecies();
      bool isShadowed = false;
      unsigned int counter2;
      if (kLaw)
        {
          for (counter2 = 0; counter2 < kLaw->getNumParameters();++counter2)
            {
              Parameter* param = kLaw->getParameter(counter2);
              if (param->getId() == name)
                {
                  isShadowed = true;
                  shadowedSubstances.push_back(name);
                  break;
                }
            }
        }
      if (!isShadowed)
        {
          if (name.find("product_") == 0)
            {
              substances["products"][name] = name;
            }
          else
            {
              substances["products"][name] = "product_" + name;
            }
        }
    }
  for (counter = 0; counter < reaction->getNumModifiers(); counter++)
    {
      std::string name = reaction->getModifier(counter)->getSpecies();
      bool isShadowed = false;
      unsigned int counter2;
      if (kLaw)
        {
          for (counter2 = 0; counter2 < kLaw->getNumParameters();++counter2)
            {
              Parameter* param = kLaw->getParameter(counter2);
              if (param->getId() == name)
                {
                  isShadowed = true;
                  shadowedSubstances.push_back(name);
                  break;
                }
            }
        }
      if (!isShadowed)
        {
          if (name.find("modifier_") == 0)
            {
              substances["modifiers"][name] = name;
            }
          else
            {
              substances["modifiers"][name] = "modifier_" + name;
            }
        }
    }
  this->replaceSubstanceNames(node, substances, shadowedSubstances, reaction->getReversible());
}

/**
 * Recursively replaces all parameter names in the branch of the given AST node
 * with the ones give in the map.
 */
void
SBMLImporter::replaceSubstanceNames(ConverterASTNode* node, std::map< std::string, std::map<std::string, std::string > > substMap, const std::vector<std::string>& shadowedSubstances, bool reversible)
{
  if (node->isName() || node->isConstant() || node->isLogical())
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
              unsigned int i;
              bool isShadowed = false;
              for (i = 0; i < shadowedSubstances.size();++i)
                {
                  if (shadowedSubstances[i] == node->getName())
                    {
                      isShadowed = true;
                      break;
                    }
                }
              if (!isShadowed)
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
    }
  else
    {
      unsigned int counter;
      for (counter = 0; counter < node->getNumChildren(); counter++)
        {
          this->replaceSubstanceNames((ConverterASTNode*)node->getChild(counter), substMap, shadowedSubstances, reversible);
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
          //throw StdException((std::string("Error. Could not find user defined function with name ") + std::string(newNode->getName())).c_str());
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
      //throw StdException("Error. The number of parameters to the function call " + functionName + " does not correspond to the number of parameters givven in the definition of the function.");
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
      //throw StdException("Error. Argument to handleSubstanceUnit is NULL pointer.");
      fatalError();
    }
  if (uDef->getNumUnits() == 1)
    {
      Unit* u = uDef->getUnit(0);
      if (u == NULL)
        {
          //DebugFile << "Expected Unit, got NULL pointer." << std::endl;
          //throw StdException("Error. Expected Unit, got NULL pointer.");
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
              //throw StdException("Error. Invalid SBML substance unit definition.");
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
              //throw StdException("Error. Invalid SBML substance unit definition.");
              fatalError();
            }
        }
      else
        {
          //throw StdException("Error. Invalid SBML volume unit definition.");
          fatalError();
        }
    }
  else
    {
      //throw StdException("Error. Invalid SBML substance unit definition.");
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
      //throw StdException("Error. Argument to handleTimeUnits is NULL pointer.");
      fatalError();
    }
  if (uDef->getNumUnits() == 1)
    {
      Unit* u = uDef->getUnit(0);
      if (u == NULL)
        {
          //DebugFile << "Expected Unit, got NULL pointer." << std::endl;
          //throw StdException("Error. Expected Unit, got NULL pointer.");
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
                  //throw StdException("Error. Invalid SBML time unit definition.");
                  fatalError();
                }
            }
          else
            {
              //throw StdException("Error. Invalid SBML time unit definition.");
              fatalError();
            }
        }
      else
        {
          //throw StdException("Error. Invalid SBML time unit definition.");
          fatalError();
        }
    }
  else
    {
      //throw StdException("Error. Invalid SBML time unit definition.");
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
      //throw StdException("Error. Argument to handleVolumeUnit is NULL pointer.");
      fatalError();
    }
  if (uDef->getNumUnits() == 1)
    {
      Unit* u = uDef->getUnit(0);
      if (u == NULL)
        {
          //DebugFile << "Expected Unit, got NULL pointer." << std::endl;
          //throw StdException("Error. Expected Unit, got NULL pointer.");
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
              //throw StdException("Error. Invalid SBML volume unit definition.");
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
              //throw StdException("Error. Invalid SBML volume unit definition.");
              fatalError();
            }
        }
      else
        {
          //throw StdException("Error. Invalid SBML volume unit definition.");
          fatalError();
        }
    }
  else
    {
      //throw StdException("Error. Invalid SBML volume unit definition.");
      fatalError();
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
  unsigned int counter;
  for (counter = 0; counter < num; counter++)
    {
      this->replaceCompartmentNodes((ConverterASTNode*)(node->getChild(counter)), compartmentMap);
    }
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

void SBMLImporter::replaceFunnyOperatorCalls(ConverterASTNode* sourceNode)
{
  ASTNodeType_t type = sourceNode->getType();
  if ((type == AST_PLUS || type == AST_TIMES) && (sourceNode->getNumChildren() < 2))
    {
      if (type == AST_PLUS)
        {
          if (sourceNode->getNumChildren() == 0)
            {
              // make the node a 0 node because otherwise we would have to
              // see if we just made the parent operator have less then 2 arguments
              sourceNode->setType(AST_REAL);
              sourceNode->setValue(0.0);
            }
          else
            {
              ConverterASTNode* child = (ConverterASTNode*)sourceNode->getChild(0);
              List* l = new List();
              unsigned int i;
              for (i = 0; i < child->getNumChildren();++i)
                {
                  l->add(child->getChild(i));
                }
              sourceNode->setChildren(l);

              sourceNode->setType(child->getType());

              if (child->isReal())
                {
                  sourceNode->setValue(child->getReal());
                }
              else if (child->isRational())
                {
                  sourceNode->setValue(child->getNumerator(), child->getDenominator());
                }
              else if (child->isInteger())
                {
                  sourceNode->setValue(child->getInteger());
                }
              else if (child->isFunction() || child->isName())
                {
                  sourceNode->setName(child->getName());
                }

              delete child;
              for (i = 0; i < sourceNode->getNumChildren();++i)
                {
                  this->replaceFunnyOperatorCalls((ConverterASTNode*)sourceNode->getChild(i));
                }
            }
        }
      else
        {
          if (sourceNode->getNumChildren() == 0)
            {
              // make the node a 1.0 node because otherwise we would have to
              // see if we just made the parent operator have less then 2 arguments
              sourceNode->setType(AST_REAL);
              sourceNode->setValue(1.0);
            }
          else
            {
              ConverterASTNode* child = (ConverterASTNode*)sourceNode->getChild(0);
              List* l = new List();
              unsigned int i;
              for (i = 0; i < child->getNumChildren();++i)
                {
                  l->add(child->getChild(i));
                }
              sourceNode->setChildren(l);
              sourceNode->setType(child->getType());
              if (child->isReal())
                {
                  sourceNode->setValue(child->getReal());
                }
              else if (child->isRational())
                {
                  sourceNode->setValue(child->getNumerator(), child->getDenominator());
                }
              else if (child->isInteger())
                {
                  sourceNode->setValue(child->getInteger());
                }
              else if (child->isFunction() || child->isName())
                {
                  sourceNode->setName(child->getName());
                }
              delete child;
              for (i = 0; i < sourceNode->getNumChildren();++i)
                {
                  this->replaceFunnyOperatorCalls((ConverterASTNode*)sourceNode->getChild(i));
                }
            }
        }
    }
  else
    {
      unsigned int i;
      for (i = 0; i < sourceNode->getNumChildren();++i)
        {
          this->replaceFunnyOperatorCalls((ConverterASTNode*)sourceNode->getChild(i));
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
  unsigned int counter = 0;
  while (copasiModel->getModelValues().getIndex(name + appendix) != static_cast < unsigned C_INT32
         > (-1))
    {
      counter++;
      std::ostringstream numberStream;
      numberStream << "_" << counter;
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
      value = std::numeric_limits<C_FLOAT64>::signaling_NaN();
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
