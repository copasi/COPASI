// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelAnalyzer.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/22 16:53:54 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CModelAnalyzer.h"

//#include "CEvaluationNode.h"
//#include "CEvaluationNodeOperator.h"
//#include "CFunction.h"
#include "CModel.h"
#include "report/CKeyFactory.h"
#include "function/CFunctionAnalyzer.h"

//this define specifies whether debug output is written to std::cout
//#define C_DBG_FA

//static
void CModelAnalyzer::checkModel(std::ostream & os, const CModel* model)
{
  if (!model) return;

  C_INT32 i, imax = model->getTotSteps();
  for (i = 0; i < imax; ++i)
    {
      std::cout << "Reaction: " << model->getReactions()[i]->getObjectName() << std::endl;
      checkReaction(os, model->getReactions()[i], model);
    }
}

//static
void CModelAnalyzer::checkReaction(std::ostream & os, const CReaction* reaction, const CModel* model)
{
  if (!reaction) return;

  //reversibility
  if (reaction->getFunction()->isReversible() == TriUnspecified)
    {
      //warning
      std::cout << "Kinetics is of unspecified reversibility." << std::endl;
    }
  else if (((reaction->getFunction()->isReversible() == TriTrue) && !reaction->isReversible())
           || ((reaction->getFunction()->isReversible() == TriFalse) && reaction->isReversible()))
    {
      //error; or copasi error?
      std::cout << "Reversibility of function and kinetics does not match." << std::endl;
    }
  else
    {
      //OK.
    }

  if (dynamic_cast<const CMassAction*>(reaction->getFunction())) return;
  //TODO special case mass action

  //********* mapping **********************

  unsigned C_INT32 i, imax;
  imax = reaction->getChemEq().getSubstrates().size();
  for (i = 0; i < imax; ++i)
    {
      //each substrate of the reaction needs to be mapped to a function parameter with role SUBSTRATE
      std::string tmpkey = reaction->getChemEq().getSubstrates()[i]->getMetaboliteKey();

      unsigned C_INT32 j, jmax = reaction->getFunctionParameters().size();
      for (j = 0; j < jmax; ++j)
        {
          if ((reaction->getFunctionParameters()[j]->getUsage() == CFunctionParameter::SUBSTRATE)
              && reaction->getParameterMappings()[j][0] == tmpkey)
            break;
        }
      if (j == jmax)
        {
          //warning/error?
          std::cout << "A substrate of this reaction is not mapped to a corresponding function parameter" << std::endl;
        }
    }

  //for reversible reactions each product of the reaction needs to be mapped to a function parameter with role PRODUCT
  if (reaction->getFunction()->isReversible() == TriTrue)
    {
      imax = reaction->getChemEq().getProducts().size();
      for (i = 0; i < imax; ++i)
        {
          std::string tmpkey = reaction->getChemEq().getProducts()[i]->getMetaboliteKey();

          unsigned C_INT32 j, jmax = reaction->getFunctionParameters().size();
          for (j = 0; j < jmax; ++j)
            {
              if ((reaction->getFunctionParameters()[j]->getUsage() == CFunctionParameter::PRODUCT)
                  && reaction->getParameterMappings()[j][0] == tmpkey)
                break;
            }
          if (j == jmax)
            {
              //warning/error?
              std::cout << "A product of this reaction is not mapped to a corresponding function parameter" << std::endl;
            }
        }
    }

  imax = reaction->getChemEq().getModifiers().size();
  for (i = 0; i < imax; ++i)
    {
      //each modifier of the reaction should be mapped to a function parameter with role MODIFIER
      std::string tmpkey = reaction->getChemEq().getModifiers()[i]->getMetaboliteKey();

      unsigned C_INT32 j, jmax = reaction->getFunctionParameters().size();
      for (j = 0; j < jmax; ++j)
        {
          if ((reaction->getFunctionParameters()[j]->getUsage() == CFunctionParameter::MODIFIER)
              && reaction->getParameterMappings()[j][0] == tmpkey)
            break;
        }
      if (j == jmax)
        {
          //warning
          std::cout << "A modifier of this reaction is not mapped to a corresponding function parameter" << std::endl;
        }
    }

  unsigned C_INT32 j, jmax;

  //loop over all function parameters
  imax = reaction->getFunctionParameters().size();
  for (i = 0; i < imax; ++i)
    {
      CFunctionParameter::Role role = reaction->getFunctionParameters()[i]->getUsage();

      // substr., product, modifier must be matched to a metab (copasi bug!)
      if (role == CFunctionParameter::SUBSTRATE
          || role == CFunctionParameter::PRODUCT
          || role == CFunctionParameter::MODIFIER)
        {
          if (!dynamic_cast<CMetab*>(GlobalKeys.get(reaction->getParameterMappings()[i][0])))
            {
              //copasi bug!
              std::cout << "Copasi bug! Something that is not a metabolite is mapped to a (subs/prod/mod) function parameter." << std::endl;
            }
        }

      switch (role)
        {
          //substrate must be matched to a substr. of the reaction (copasi bug?)
        case CFunctionParameter::SUBSTRATE:
          jmax = reaction->getChemEq().getSubstrates().size();
          for (j = 0; j < jmax; ++j)
            {
              if (reaction->getParameterMappings()[i][0]
                  == reaction->getChemEq().getSubstrates()[j]->getMetaboliteKey())
                break;
            }
          if (j == jmax)
            {
              //copasi error?
              std::cout << "A SUBSTRATE function parameter is not mapped to a substrate of the reaction." << std::endl;
            }
          break;

          //Product must be matched to a product of the reaction (copasi bug?)
        case CFunctionParameter::PRODUCT:
          jmax = reaction->getChemEq().getProducts().size();
          for (j = 0; j < jmax; ++j)
            {
              if (reaction->getParameterMappings()[i][0]
                  == reaction->getChemEq().getProducts()[j]->getMetaboliteKey())
                break;
            }
          if (j == jmax)
            {
              //copasi error?
              std::cout << "A PRODUCT function parameter is not mapped to a product of the reaction." << std::endl;
            }
          break;

          //modifier should be matched to a modifier in the chemeq
        case CFunctionParameter::MODIFIER:
          jmax = reaction->getChemEq().getModifiers().size();
          for (j = 0; j < jmax; ++j)
            {
              if (reaction->getParameterMappings()[i][0]
                  == reaction->getChemEq().getModifiers()[j]->getMetaboliteKey())
                break;
            }
          if (j == jmax)
            {
              //copasi error?
              std::cout << "A MODIFIER function parameter is not mapped to a modifier of the reaction." << std::endl;
              //this is not a user error. The modifier should have been added to the chemeq automatically.
            }
          break;

          //parameter must be matched to a local or global parameter (copasi bug)
        case CFunctionParameter::PARAMETER:
          //first search in local parameters list
          jmax = reaction->getParameters().size();
          for (j = 0; j < jmax; ++j)
            {
              if (reaction->getParameterMappings()[i][0]
                  == reaction->getParameters().getParameter(j)->getKey())
                break;
            }
          if (j == jmax) //not a local parameter
            {
              //now search in global value list
              jmax = model->getModelValues().size();
              for (j = 0; j < jmax; ++j)
                {
                  if (reaction->getParameterMappings()[i][0]
                      == model->getModelValues()[j]->getKey())
                    break;
                }
              if (j == jmax) //not a global parameter
                {
                  //copasi bug
                  std::cout << "A PARAMETER function parameter is mapped neither to a local parameter nor a global value." << std::endl;
                }
            }
          break;

        case CFunctionParameter::VOLUME:
          jmax = model->getCompartments().size();
          for (j = 0; j < jmax; ++j)
            {
              if (reaction->getParameterMappings()[i][0]
                  == model->getCompartments()[j]->getKey())
                break;
            }
          if (j == jmax)
            {
              //copasi bug
              std::cout << "A VOLUME function parameter is not mapped to a compartment." << std::endl;
            }
          break;

        case CFunctionParameter::TIME:
          if (reaction->getParameterMappings()[i][0] != model->getKey())
            {
              //copasi bug
              std::cout << "Internal Copasi bug: TIME parameter not mapped correctly." << std::endl;
            }
          break;

        case CFunctionParameter::VARIABLE:
          {
            //copasi bug
            std::cout << "Don't know what to do with a VARIABLE parameter here..." << std::endl;
          }
          break;
        }
    }

  //check function:
  // irrev: no products should occur
  // irrev: if substr=0 -> kinetics=0
  CFunctionAnalyzer fa(reaction->getFunction() , reaction);
  fa.getResult().writeResult(os, true, true);
  fa.getResult().writeTable(os, true);
}
