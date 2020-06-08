// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include "CModelAnalyzer.h"

//#include "CEvaluationNode.h"
//#include "CEvaluationNodeOperator.h"
//#include "CFunction.h"
#include "CModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/function/CFunctionAnalyzer.h"
#include "copasi/core/CRootContainer.h"

CModelAnalyzer::CModelAnalyzer(const CModel* model)
{
  checkModel(model);
}

void CModelAnalyzer::checkModel(const CModel* model)
{
  if (!model) return;

  mpModel = model;

  size_t i, imax = model->getTotSteps();

  for (i = 0; i < imax; ++i)
    {
      mReactionResults.push_back(checkReaction(&model->getReactions()[i]));
    }
}

CReactionResult CModelAnalyzer::checkReaction(const CReaction* reaction)
{
  CReactionResult ret;

  if (!reaction) return ret;

  ret.mReactionName = reaction->getObjectName();

  //reversibility
  if (reaction->getFunction()->isReversible() == TriUnspecified)
    {
      //warning
      // Kinetics is of unspecified reversibility.
      ret.mKineticUnspecifiedReversibility = true;
    }
  else if (((reaction->getFunction()->isReversible() == TriTrue) && !reaction->isReversible())
           || ((reaction->getFunction()->isReversible() == TriFalse) && reaction->isReversible()))
    {
      //error; or COPASI error?
      // Reversibility of function and kinetics does not match.
      ret.mReversibilityMismatch = true;
    }
  else
    {
      //OK.
    }

  if (dynamic_cast<const CMassAction*>(reaction->getFunction())) return ret;

  //TODO special case mass action

  //********* mapping **********************

  size_t i, imax;
  imax = reaction->getChemEq().getSubstrates().size();

  for (i = 0; i < imax; ++i)
    {
      //each substrate of the reaction needs to be mapped to a function parameter with role SUBSTRATE
      std::string tmpkey = reaction->getChemEq().getSubstrates()[i].getMetaboliteKey();

      size_t j, jmax = reaction->getFunctionParameters().size();

      for (j = 0; j < jmax; ++j)
        {
          if ((reaction->getFunctionParameters()[j]->getUsage() == CFunctionParameter::Role::SUBSTRATE)
              && reaction->getParameterObjects(j)[0]->getKey() == tmpkey)
            break;
        }

      if (j == jmax)
        {
          //warning/error?
          // A substrate of this reaction is not mapped to a corresponding function parameter.
          const CMetab * pM = reaction->getChemEq().getSubstrates()[i].getMetabolite();

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
          std::string tmpkey = reaction->getChemEq().getProducts()[i].getMetaboliteKey();

          size_t j, jmax = reaction->getFunctionParameters().size();

          for (j = 0; j < jmax; ++j)
            {
              if ((reaction->getFunctionParameters()[j]->getUsage() == CFunctionParameter::Role::PRODUCT)
                  && reaction->getParameterObjects(j)[0]->getKey() == tmpkey)
                break;
            }

          if (j == jmax)
            {
              //warning/error?
              // A product of this reaction is not mapped to a corresponding function parameter.
              const CMetab * pM = reaction->getChemEq().getProducts()[i].getMetabolite();

              if (pM)
                ret.mChemEqProds.push_back(pM->getObjectName());
            }
        }
    }

  imax = reaction->getChemEq().getModifiers().size();

  for (i = 0; i < imax; ++i)
    {
      //each modifier of the reaction should be mapped to a function parameter with role MODIFIER
      std::string tmpkey = reaction->getChemEq().getModifiers()[i].getMetaboliteKey();

      size_t j, jmax = reaction->getFunctionParameters().size();

      for (j = 0; j < jmax; ++j)
        {
          if ((reaction->getFunctionParameters()[j]->getUsage() == CFunctionParameter::Role::MODIFIER)
              && reaction->getParameterObjects(j)[0]->getKey() == tmpkey)
            break;
        }

      if (j == jmax)
        {
          //warning
          // A modifier of this reaction is not mapped to a corresponding function parameter.
          const CMetab * pM = reaction->getChemEq().getModifiers()[i].getMetabolite();

          if (pM)
            ret.mChemEqMods.push_back(pM->getObjectName());
        }
    }

  size_t j, jmax;

  //loop over all function parameters
  imax = reaction->getFunctionParameters().size();

  for (i = 0; i < imax; ++i)
    {
      CFunctionParameter::Role role = reaction->getFunctionParameters()[i]->getUsage();

      // substr., product, modifier must be matched to a metab (COPASI bug!)
      if (role == CFunctionParameter::Role::SUBSTRATE
          || role == CFunctionParameter::Role::PRODUCT
          || role == CFunctionParameter::Role::MODIFIER)
        {
          if (!dynamic_cast< const CMetab * >(reaction->getParameterObjects(i)[0]))
            {
              //COPASI bug!
              // COPASI bug! Something that is not a metabolite is mapped to a (subs/prod/mod) function parameter.
              ret.mNotMetabolite.push_back(reaction->getFunctionParameters()[i]->getObjectName());
            }
        }

      switch (role)
        {
            //substrate must be matched to a substr. of the reaction (COPASI bug?)
          case CFunctionParameter::Role::SUBSTRATE:
            jmax = reaction->getChemEq().getSubstrates().size();

            for (j = 0; j < jmax; ++j)
              {
                if (reaction->getParameterObjects(i)[0] == reaction->getChemEq().getSubstrates()[j].getMetabolite())
                  break;
              }

            if (j == jmax)
              {
                //COPASI error?
                // A SUBSTRATE function parameter is not mapped to a substrate of the reaction.
                ret.mFunctionParametersSubs.push_back(reaction->getFunctionParameters()[i]->getObjectName());
              }

            break;

            //Product must be matched to a product of the reaction (COPASI bug?)
          case CFunctionParameter::Role::PRODUCT:
            jmax = reaction->getChemEq().getProducts().size();

            for (j = 0; j < jmax; ++j)
              {
                if (reaction->getParameterObjects(i)[0] == reaction->getChemEq().getProducts()[j].getMetabolite())
                  break;
              }

            if (j == jmax)
              {
                //COPASI error?
                // A PRODUCT function parameter is not mapped to a product of the reaction." << std::endl;
                ret.mFunctionParametersProds.push_back(reaction->getFunctionParameters()[i]->getObjectName());
              }

            break;

            //modifier should be matched to a modifier in the chemeq
          case CFunctionParameter::Role::MODIFIER:
            jmax = reaction->getChemEq().getModifiers().size();

            for (j = 0; j < jmax; ++j)
              {
                if (reaction->getParameterObjects(i)[0] == reaction->getChemEq().getModifiers()[j].getMetabolite())
                  break;
              }

            if (j == jmax)
              {
                //COPASI error?
                // A MODIFIER function parameter is not mapped to a modifier of the reaction.
                ret.mFunctionParametersMods.push_back(reaction->getFunctionParameters()[i]->getObjectName());
                //this is not a user error. The modifier should have been added to the chemeq automatically.
              }

            break;

            //parameter must be matched to a local or global parameter (COPASI bug)
          case CFunctionParameter::Role::PARAMETER:
            //first search in local parameters list
            jmax = reaction->getParameters().size();

            for (j = 0; j < jmax; ++j)
              {
                if (reaction->getParameterObjects(i)[0] == reaction->getParameters().getParameter(j))
                  break;
              }

            if (j == jmax) //not a local parameter
              {
                //now search in global value list
                jmax = mpModel->getModelValues().size();

                for (j = 0; j < jmax; ++j)
                  {
                    if (reaction->getParameterObjects(i)[0] == &mpModel->getModelValues()[j])
                      break;
                  }

                if (j == jmax) //not a global parameter
                  {
                    //COPASI bug
                    // A PARAMETER function parameter is mapped neither to a local parameter nor a global value.
                    ret.mFunctionParametersParams.push_back(reaction->getFunctionParameters()[i]->getObjectName());
                  }
              }

            break;

          case CFunctionParameter::Role::VOLUME:
            jmax = mpModel->getCompartments().size();

            for (j = 0; j < jmax; ++j)
              {
                if (reaction->getParameterObjects(i)[0] == &mpModel->getCompartments()[j])
                  break;
              }

            if (j == jmax)
              {
                //COPASI bug
                // A VOLUME function parameter is not mapped to a compartment.
                ret.mFunctionParametersVol.push_back(reaction->getFunctionParameters()[i]->getObjectName());
              }

            break;

          case CFunctionParameter::Role::TIME:

            if (reaction->getParameterObjects(i)[0] != mpModel)
              {
                //COPASI bug
                // Internal Copasi bug: TIME parameter not mapped correctly.
                ret.mFunctionParametersTime.push_back(reaction->getFunctionParameters()[i]->getObjectName());
              }

            break;

          case CFunctionParameter::Role::VARIABLE:
          case CFunctionParameter::Role::TEMPORARY:
          {
            //COPASI bug
            // Don't know what to do with a VARIABLE parameter here..."
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

  return ret;
}

//*********** Reporting **********************************

#define WRITE(__level, __text) os << CFunctionAnalyzer::write(__level, rt, __text, "");


CReactionResult::CReactionResult()
  : mKineticUnspecifiedReversibility(false)
  , mReversibilityMismatch(false)
{

}

CReactionResult::~CReactionResult()
{
}

bool CReactionResult::writeResult(std::ostream & os, bool rt, bool verbose, bool writeToStream /*= true*/) const
{
  bool ret = false;

  //reaction name
  if (writeToStream)
    {
      if (rt) os << "<h2>";

      os << mReactionName;

      if (rt) os << "</h2>";

      os << "\n";


      //reaction results
      if (mKineticUnspecifiedReversibility)
        os << CFunctionAnalyzer::write(1, rt, "The kinetic function has unspecified reversibility.",
                                       "This means that checking the kinetic function will be less strict.");

      if (mReversibilityMismatch)
        os << CFunctionAnalyzer::write(3, rt, "The reversibility of the reaction and the kinetic function doesn't match.", "");

    }

  size_t i, imax;
  imax = mChemEqSubs.size();

  for (i = 0; i < imax; ++i)
    {
      if (writeToStream)
        os << CFunctionAnalyzer::write(2, rt, "The reaction substrate \""
                                       + mChemEqSubs[i]
                                       + "\" is not mapped to a corresponding function parameter.", "");

      ret = true;
    }

  imax = mChemEqProds.size();

  for (i = 0; i < imax; ++i)
    {
      if (writeToStream)
        os << CFunctionAnalyzer::write(2, rt, "The reaction product \""
                                       + mChemEqProds[i]
                                       + "\" is not mapped to a corresponding function parameter.", "");

      ret = true;
    }

  imax = mChemEqMods.size();

  for (i = 0; i < imax; ++i)
    {
      if (writeToStream)
        os << CFunctionAnalyzer::write(1, rt, "The reaction modifier \""
                                       + mChemEqMods[i]
                                       + "\" is not mapped to a corresponding function parameter.", "");
    }

  imax = mNotMetabolite.size();

  for (i = 0; i < imax; ++i)
    {
      if (writeToStream)
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mNotMetabolite[i]
                                       + "\" which should be mapped to a metabolite is mapped to something else.", "");
    }

  imax = mFunctionParametersSubs.size();

  for (i = 0; i < imax; ++i)
    {
      if (writeToStream)
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mFunctionParametersSubs[i]
                                       + "\" is not mapped to a substrate of the reaction.", "");
    }

  imax = mFunctionParametersProds.size();

  for (i = 0; i < imax; ++i)
    {
      if (writeToStream)
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mFunctionParametersProds[i]
                                       + "\" is not mapped to a product of the reaction.", "");
    }

  imax = mFunctionParametersMods.size();

  for (i = 0; i < imax; ++i)
    {
      if (writeToStream)
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mFunctionParametersMods[i]
                                       + "\" is not mapped to a modifier of the reaction.", "");
    }

  imax = mFunctionParametersParams.size();

  for (i = 0; i < imax; ++i)
    {
      if (writeToStream)
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mFunctionParametersParams[i]
                                       + "\" is not mapped to local parameter or a global value.", "");
    }

  imax = mFunctionParametersVol.size();

  for (i = 0; i < imax; ++i)
    {
      if (writeToStream)
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mFunctionParametersVol[i]
                                       + "\" is not mapped to a compartment.", "");
    }

  imax = mFunctionParametersTime.size();

  for (i = 0; i < imax; ++i)
    {
      if (writeToStream)
        os << CFunctionAnalyzer::write(3, rt, "The function parameter \""
                                       + mFunctionParametersTime[i]
                                       + "\" is not correctly handled as model time.", "");
    }

  imax = mFunctionParametersVar.size();

  for (i = 0; i < imax; ++i)
    {
      if (writeToStream)
        os << CFunctionAnalyzer::write(1, rt, "The function parameter \""
                                       + mFunctionParametersVar[i]
                                       + "\" is marked as \"variable\". Not sure what this means.", "");
    }

  //function results
  std::ostringstream tmpss;
  bool eee = mFunctionResult.writeResult(tmpss, rt, verbose);

  if (eee) ret = true;

  if (eee || verbose)
    {
      os << tmpss.str();
    }

  return ret;
}

bool CReactionResult::hasIssue() const
{
  std::stringstream str;
  return writeResult(str, false, false, false);
}

std::string CReactionResult::getResultString(bool rt, bool verbose) const
{
  std::stringstream str;
  writeResult(str, rt, verbose);
  return str.str();
}


const std::string& CReactionResult::getName() const
{
  return mReactionName;
}

void CModelAnalyzer::writeReport(std::ostream & os, bool rt, bool verbose) const
{

  //reaction results
  size_t i, imax = mReactionResults.size();

  for (i = 0; i < imax; ++i)
    {
      //std::ostringstream tmpss;
      mReactionResults[i].writeResult(os, rt, verbose);
    }
}

const std::vector<CReactionResult>& CModelAnalyzer::getReactionResults() const
{
  return mReactionResults;
}
