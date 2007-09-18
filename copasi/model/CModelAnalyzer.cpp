// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelAnalyzer.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/09/18 00:14:54 $
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

CModelAnalyzer::CModelAnalyzer(const CModel* model)
{
  checkModel(model);
}

void CModelAnalyzer::checkModel(const CModel* model)
{
  if (!model) return;

  mpModel = model;

  C_INT32 i, imax = model->getTotSteps();
  for (i = 0; i < imax; ++i)
    {
      std::cout << "Reaction: " << model->getReactions()[i]->getObjectName() << std::endl;
      mReactionResults.push_back(checkReaction(model->getReactions()[i]));
    }
}

CModelAnalyzer::ReactionResult CModelAnalyzer::checkReaction(const CReaction* reaction)
{
  ReactionResult ret;

  if (!reaction) return ret;

  ret.mReactionName = reaction->getObjectName();

  //reversibility
  if (reaction->getFunction()->isReversible() == TriUnspecified)
    {
      //warning
      std::cout << "Kinetics is of unspecified reversibility." << std::endl;
      ret.mKineticUnspecifiedReversibility = true;
    }
  else if (((reaction->getFunction()->isReversible() == TriTrue) && !reaction->isReversible())
           || ((reaction->getFunction()->isReversible() == TriFalse) && reaction->isReversible()))
    {
      //error; or copasi error?
      std::cout << "Reversibility of function and kinetics does not match." << std::endl;
      ret.mReversibilityMismatch = true;
    }
  else
    {
      //OK.
    }

  if (dynamic_cast<const CMassAction*>(reaction->getFunction())) return ret;
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
          const CMetab * pM = reaction->getChemEq().getSubstrates()[i]->getMetabolite();
          if (pM)
            ret.mChemEqSubs.push_back(pM->getObjectName());
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
              const CMetab * pM = reaction->getChemEq().getProducts()[i]->getMetabolite();
              if (pM)
                ret.mChemEqProds.push_back(pM->getObjectName());
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
          const CMetab * pM = reaction->getChemEq().getModifiers()[i]->getMetabolite();
          if (pM)
            ret.mChemEqMods.push_back(pM->getObjectName());
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
              ret.mNotMetabolite.push_back(reaction->getFunctionParameters()[i]->getObjectName());
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
              ret.mFunctionParametersSubs.push_back(reaction->getFunctionParameters()[i]->getObjectName());
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
              ret.mFunctionParametersProds.push_back(reaction->getFunctionParameters()[i]->getObjectName());
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
              ret.mFunctionParametersMods.push_back(reaction->getFunctionParameters()[i]->getObjectName());
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
              jmax = mpModel->getModelValues().size();
              for (j = 0; j < jmax; ++j)
                {
                  if (reaction->getParameterMappings()[i][0]
                      == mpModel->getModelValues()[j]->getKey())
                    break;
                }
              if (j == jmax) //not a global parameter
                {
                  //copasi bug
                  std::cout << "A PARAMETER function parameter is mapped neither to a local parameter nor a global value." << std::endl;
                  ret.mFunctionParametersParams.push_back(reaction->getFunctionParameters()[i]->getObjectName());
                }
            }
          break;

        case CFunctionParameter::VOLUME:
          jmax = mpModel->getCompartments().size();
          for (j = 0; j < jmax; ++j)
            {
              if (reaction->getParameterMappings()[i][0]
                  == mpModel->getCompartments()[j]->getKey())
                break;
            }
          if (j == jmax)
            {
              //copasi bug
              std::cout << "A VOLUME function parameter is not mapped to a compartment." << std::endl;
              ret.mFunctionParametersVol.push_back(reaction->getFunctionParameters()[i]->getObjectName());
            }
          break;

        case CFunctionParameter::TIME:
          if (reaction->getParameterMappings()[i][0] != mpModel->getKey())
            {
              //copasi bug
              std::cout << "Internal Copasi bug: TIME parameter not mapped correctly." << std::endl;
              ret.mFunctionParametersTime.push_back(reaction->getFunctionParameters()[i]->getObjectName());
            }
          break;

        case CFunctionParameter::VARIABLE:
          {
            //copasi bug
            std::cout << "Don't know what to do with a VARIABLE parameter here..." << std::endl;
            ret.mFunctionParametersVar.push_back(reaction->getFunctionParameters()[i]->getObjectName());
          }
          break;
        }
    }

  //check function:
  // irrev: no products should occur
  // irrev: if substr=0 -> kinetics=0
  CFunctionAnalyzer fa(reaction->getFunction() , reaction);
  ret.mFunctionResult = fa.getResult();

  //fa.getResult().writeResult(os, true, true);
  //fa.getResult().writeTable(os, true);

  return ret;
}

//*********** Reporting **********************************

#define WRITE(__level, __text) os << CFunctionAnalyzer::write(__level, rt, __text, "");

bool CModelAnalyzer::ReactionResult::writeResult(std::ostream & os, bool rt, bool verbose) const
  {
    bool ret = false;

    //reaction name
    if (rt) os << "<h2>";
    os << mReactionName;
    if (rt) os << "</h2>";
    os << "\n";

    //reaction results
    if (mKineticUnspecifiedReversibility)
      os << CFunctionAnalyzer::write(1, rt, "The kinetic function has unspecified reversibility.", "");

    if (mReversibilityMismatch)
      os << CFunctionAnalyzer::write(3, rt, "The reversibility of the reaction and the kinetic function doesn't match.", "");

    unsigned int i, imax;
    imax = mChemEqSubs.size();
    for (i = 0; i < imax; ++i)
      {
        os << CFunctionAnalyzer::write(2, rt, "The reaction substrate \""
                                       + mChemEqSubs[i]
                                       + "\" is not mapped to a corresponding function parameter.", "");
      }

    imax = mChemEqProds.size();
    for (i = 0; i < imax; ++i)
      {
        os << CFunctionAnalyzer::write(2, rt, "The reaction product \""
                                       + mChemEqProds[i]
                                       + "\" is not mapped to a corresponding function parameter.", "");
      }

    imax = mChemEqMods.size();
    for (i = 0; i < imax; ++i)
      {
        os << CFunctionAnalyzer::write(1, rt, "The reaction modifier \""
                                       + mChemEqMods[i]
                                       + "\" is not mapped to a corresponding function parameter.", "");
      }

    imax = mNotMetabolite.size();
    for (i = 0; i < imax; ++i)
      {
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mNotMetabolite[i]
                                       + "\" which should be mapped to a metabolite is mapped to something else.", "");
      }

    imax = mFunctionParametersSubs.size();
    for (i = 0; i < imax; ++i)
      {
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mFunctionParametersSubs[i]
                                       + "\" is not mapped to a substrate of the reaction.", "");
      }

    imax = mFunctionParametersProds.size();
    for (i = 0; i < imax; ++i)
      {
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mFunctionParametersProds[i]
                                       + "\" is not mapped to a product of the reaction.", "");
      }

    imax = mFunctionParametersMods.size();
    for (i = 0; i < imax; ++i)
      {
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mFunctionParametersMods[i]
                                       + "\" is not mapped to a modifier of the reaction.", "");
      }

    imax = mFunctionParametersParams.size();
    for (i = 0; i < imax; ++i)
      {
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mFunctionParametersParams[i]
                                       + "\" is not mapped to local parameter or a global value.", "");
      }

    imax = mFunctionParametersVol.size();
    for (i = 0; i < imax; ++i)
      {
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mFunctionParametersVol[i]
                                       + "\" is not mapped to a compartment.", "");
      }

    imax = mFunctionParametersTime.size();
    for (i = 0; i < imax; ++i)
      {
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mFunctionParametersTime[i]
                                       + "\" is not correctly handled as model time.", "");
      }

    imax = mFunctionParametersVar.size();
    for (i = 0; i < imax; ++i)
      {
        os << CFunctionAnalyzer::write(1, rt, "The function parameter \""
                                       + mFunctionParametersVar[i]
                                       + "\" is marked as \"variable\". Not sure what this means.", "");
      }

    //function results
    mFunctionResult.writeResult(os, rt, verbose);

    //     mFunctionResult.mOriginalFunction.writeTable(os, rt);
    //     if (rt) os << "<p>\n";
    //     mFunctionResult.mFPart.writeTable(os, rt);
    //     if (rt) os << "<p>\n";
    //     mFunctionResult.mBPart.writeTable(os, rt);

    return ret;
  }

void CModelAnalyzer::writeReport(std::ostream & os, bool rt, bool verbose) const
  {

    //reaction results
    unsigned i, imax = mReactionResults.size();
    for (i = 0; i < imax; ++i)
      {
        mReactionResults[i].writeResult(os, rt, verbose);
      }
  }
