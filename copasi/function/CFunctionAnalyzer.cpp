// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionAnalyzer.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/21 16:15:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CFunctionAnalyzer.h"

#include "CEvaluationNode.h"
//#include "CEvaluationNodeOperator.h"
#include "CFunction.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"

//this define specifies whether debug output is written to std::cout
//#define C_DBG_FA

std::ostream & operator<<(std::ostream &os, const CFunctionAnalyzer::CValue & v)
{
  os << "{";
  if (v.mStatus & CFunctionAnalyzer::CValue::negative) os << "- ";
  if (v.mStatus & CFunctionAnalyzer::CValue::zero) os << "0 ";
  if (v.mStatus & CFunctionAnalyzer::CValue::positive) os << "+ ";
  if (v.mStatus & CFunctionAnalyzer::CValue::invalid) os << "E ";
  if (v.mStatus & CFunctionAnalyzer::CValue::known) os << "v" << v.mDouble << " ";
  os << "}";

  return os;
}

CFunctionAnalyzer::CValue CFunctionAnalyzer::CValue::operator*(const CFunctionAnalyzer::CValue & rhs) const
  {
    CValue ret;

    //invalid
    if (this->getStatus()&invalid || rhs.getStatus()&invalid)
      ret.Or(invalid);

    const CValue* v1, *v2;
    v1 = this; v2 = &rhs;

    if ((v1->mStatus & negative) && (v2->mStatus & negative)) ret.Or(positive);
    if ((v1->mStatus & negative) && (v2->mStatus & zero)) ret.Or(zero);
    if ((v1->mStatus & negative) && (v2->mStatus & positive)) ret.Or(negative);

    if ((v1->mStatus & zero) && (v2->mStatus & negative)) ret.Or(zero);
    if ((v1->mStatus & zero) && (v2->mStatus & zero)) ret.Or(zero);
    if ((v1->mStatus & zero) && (v2->mStatus & positive)) ret.Or(zero);

    if ((v1->mStatus & positive) && (v2->mStatus & negative)) ret.Or(negative);
    if ((v1->mStatus & positive) && (v2->mStatus & zero)) ret.Or(zero);
    if ((v1->mStatus & positive) && (v2->mStatus & positive)) ret.Or(positive);

    //known values
    if ((this->mStatus & known) && (rhs.mStatus & known))
      ret.orValue(this->mDouble * rhs.mDouble);
    else if (this->mStatus & known)
      ret.Or(generalize(this->mDouble) * rhs);
    else if (rhs.mStatus & known)
      ret.Or(*this * generalize(rhs.mDouble));

#ifdef C_DBG_FA
    std::cout << "      *: " << *this << " * " << rhs << " = " << ret << std::endl;
#endif

    return ret;
  }

CFunctionAnalyzer::CValue CFunctionAnalyzer::CValue::operator/(const CFunctionAnalyzer::CValue & rhs) const
  {
    CValue ret;

    //invalid
    if (this->getStatus() & invalid || rhs.getStatus()&invalid)
      ret.Or(invalid);
    if (rhs.getStatus() & zero)
      ret.Or(invalid);

    const CValue* v1, *v2;
    v1 = this; v2 = &rhs;

    if ((v1->mStatus & negative) && (v2->mStatus & negative)) ret.Or(positive);
    if ((v1->mStatus & negative) && (v2->mStatus & positive)) ret.Or(negative);

    if ((v1->mStatus & zero) && (v2->mStatus & negative)) ret.Or(zero);
    if ((v1->mStatus & zero) && (v2->mStatus & positive)) ret.Or(zero);

    if ((v1->mStatus & positive) && (v2->mStatus & negative)) ret.Or(negative);
    if ((v1->mStatus & positive) && (v2->mStatus & positive)) ret.Or(positive);

    //known values
    if ((this->mStatus & known) && (rhs.mStatus & known))
      ret.orValue(this->mDouble / rhs.mDouble);
    else if (this->mStatus & known)
      ret.Or(generalize(this->mDouble) / rhs);
    else if (rhs.mStatus & known)
      ret.Or(*this / generalize(rhs.mDouble));

#ifdef C_DBG_FA
    std::cout << "      /: " << *this << " / " << rhs << " = " << ret << std::endl;
#endif

    return ret;
  }

CFunctionAnalyzer::CValue CFunctionAnalyzer::CValue::operator+(const CFunctionAnalyzer::CValue & rhs) const
  {
    CValue ret;

    //invalid
    if (this->getStatus()&invalid || rhs.getStatus()&invalid)
      ret.Or(invalid);

    //zero
    if (this->getStatus() & zero)
      ret.Or(rhs);
    if (rhs.getStatus() & zero)
      ret.Or(*this);

    //symmetry
    const CValue* v1, *v2;
    v1 = this; v2 = &rhs;

    if ((v1->mStatus & negative) && (v2->mStatus & negative)) ret.Or(negative);
    if ((v1->mStatus & negative) && (v2->mStatus & positive)) ret.Or(negative | zero | positive);

    if ((v1->mStatus & positive) && (v2->mStatus & negative)) ret.Or(negative | zero | positive);
    if ((v1->mStatus & positive) && (v2->mStatus & positive)) ret.Or(positive);

    //known values
    if ((this->mStatus & known) && (rhs.mStatus & known)) ret.orValue(this->mDouble + rhs.mDouble);

    if ((this->mStatus & negative) && (rhs.mStatus & known)) ret.Or(*this + generalize(rhs.mDouble));
    if ((this->mStatus & positive) && (rhs.mStatus & known)) ret.Or(*this + generalize(rhs.mDouble));

    if ((this->mStatus & known) && (rhs.mStatus & negative)) ret.Or(generalize(this->mDouble) + rhs);
    if ((this->mStatus & known) && (rhs.mStatus & positive)) ret.Or(generalize(this->mDouble) + rhs);

#ifdef C_DBG_FA
    std::cout << "      +: " << *this << " + " << rhs << " = " << ret << std::endl;
#endif

    return ret;
  }

CFunctionAnalyzer::CValue CFunctionAnalyzer::CValue::invert() const
  {
    CValue ret;
    ret.mStatus = Status(this->mStatus & (zero | invalid | known));
    if (this->mStatus & known) ret.mDouble = -this->mDouble;

    if (this->mStatus & positive) ret.Or(negative);
    if (this->mStatus & negative) ret.Or(positive);

    return ret;
  }

CFunctionAnalyzer::CValue CFunctionAnalyzer::CValue::operator-(const CFunctionAnalyzer::CValue & rhs) const
  {
    return *this + rhs.invert();
  }

CFunctionAnalyzer::CValue CFunctionAnalyzer::CValue::operator^(const CFunctionAnalyzer::CValue & rhs) const
  {
    CValue ret;

    //invalid
    if (this->getStatus()&invalid || rhs.getStatus()&invalid)
      ret.Or(invalid);

    const CValue* v1, *v2;
    v1 = this; v2 = &rhs;

    if ((v1->mStatus & negative) && (v2->mStatus & negative)) ret.Or(negative | positive | invalid);
    if ((v1->mStatus & negative) && (v2->mStatus & zero)) ret.orValue(1.0);
    if ((v1->mStatus & negative) && (v2->mStatus & positive)) ret.Or(negative | positive | invalid);

    if ((v1->mStatus & zero) && (v2->mStatus & negative)) ret.Or(invalid);
    if ((v1->mStatus & zero) && (v2->mStatus & zero)) ret.Or(invalid);
    if ((v1->mStatus & zero) && (v2->mStatus & positive)) ret.Or(zero);

    if ((v1->mStatus & positive) && (v2->mStatus & negative)) ret.Or(positive);
    if ((v1->mStatus & positive) && (v2->mStatus & zero)) ret.orValue(1.0);
    if ((v1->mStatus & positive) && (v2->mStatus & positive)) ret.Or(positive);

    //known values

    //base and exponent are known
    if ((this->mStatus & known) && (rhs.mStatus & known)) ret.orValue(pow(this->mDouble, rhs.mDouble));

    //base is known
    if ((this->mStatus & known) && ((rhs.mStatus & negative)
                                    || (rhs.mStatus & zero)
                                    || (rhs.mStatus & positive)))
      {
        if (this->mDouble == 1.0) // base is 1
          ret.orValue(1.0);
        else
          ret.Or(generalize(this->mDouble) ^ rhs);
      }

    //exponent is known
    if (((this->mStatus & negative)
         || (this->mStatus & zero)
         || (this->mStatus & positive)) && (rhs.mStatus & known))
      {
        if ((rhs.mDouble == trunc(rhs.mDouble)) && (rhs.mDouble != 0.0)) //exponent is integer but not 0
          {
            if (rhs.mDouble / 2.0 == trunc(rhs.mDouble / 2.0)) //exponent is even
              {
                if (this->mStatus & negative) ret.Or(positive);
                if (this->mStatus & zero) ret.Or(zero);
                if (this->mStatus & positive) ret.Or(positive);
              }
            else //uneven
              {
                if (this->mStatus & negative) ret.Or(negative);
                if (this->mStatus & zero) ret.Or(zero);
                if (this->mStatus & positive) ret.Or(positive);
              }
          }
        else
          ret.Or(*this ^ generalize(rhs.mDouble));
      }

#ifdef C_DBG_FA
    std::cout << "      ^: " << *this << " ^ " << rhs << " = " << ret << std::endl;
#endif

    return ret;
  }

// CFunctionAnalyzer::CValue CFunctionAnalyzer::CValue::generalize() const
// {
//   if (mStatus==known)
//     {
//       if (mDouble==0.0) return zero;
//       if (mDouble>0.0) return positive;
//       if (mDouble<0.0) return negative;
//       return invalid;
//}
//   else
//     return *this;
//}

//static
CFunctionAnalyzer::CValue CFunctionAnalyzer::CValue::generalize(const double & d)
{
  if (d == 0.0) return zero;
  else if (d > 0.0) return positive;
  else if (d < 0.0) return negative;
  else return invalid;
}

void CFunctionAnalyzer::CValue::Or(const CValue & v) //  {mStatus = Status(mStatus | s);};
{
  if ((this->mStatus & known) && (v.mStatus & known) && (this->mDouble != v.mDouble))
    {//the two CValues have different known values
      CValue tmp = generalize(this->mDouble);
      tmp.Or(generalize(v.mDouble));
      *this = tmp;
      return;
    }

  Or(v.mStatus);
  if (v.mStatus & known) this->mDouble = v.mDouble;
}

//***********************************************************************************************

//static
void CFunctionAnalyzer::constructCallParameters(const CFunctionParameters & fp, std::vector<CValue> & callParameters, bool posi)
{
  unsigned C_INT32 i, imax = fp.size();
  callParameters.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      CFunctionParameter::Role role = fp[i]->getUsage();
      switch (role)
        {
        case CFunctionParameter::SUBSTRATE:
        case CFunctionParameter::PRODUCT:
        case CFunctionParameter::MODIFIER:
        case CFunctionParameter::VOLUME:
          callParameters[i] = CValue::positive;
          break;

        case CFunctionParameter::TIME:
        case CFunctionParameter::PARAMETER:
        case CFunctionParameter::VARIABLE:
          callParameters[i] = posi ? CValue::positive : CValue::unknown;
          break;
        }
    }
}

//static
void CFunctionAnalyzer::constructCallParametersActualValues(std::vector<CValue> & callParameters, /*const CModel* model,*/ const CReaction* reaction)
{
  unsigned C_INT32 i, imax = reaction->getFunctionParameters().size();
  callParameters.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      const CModelEntity * pME;
      const CCopasiParameter * pCP;

      CFunctionParameter::Role role = reaction->getFunctionParameters()[i]->getUsage();
      switch (role)
        {
        case CFunctionParameter::SUBSTRATE:
        case CFunctionParameter::PRODUCT:
        case CFunctionParameter::MODIFIER:
        case CFunctionParameter::VOLUME:
        case CFunctionParameter::PARAMETER:
          callParameters[i] = CValue::unknown;
          pME = dynamic_cast<const CModelEntity*>(GlobalKeys.get(reaction->getParameterMappings()[i][0]));
          if (pME)
            {
              if (pME->getStatus() == CModelEntity::FIXED)
                callParameters[i] = CValue(pME->getValue());
              else
                callParameters[i] = CValue::positive;
            }

          pCP = dynamic_cast<const CCopasiParameter*>(GlobalKeys.get(reaction->getParameterMappings()[i][0]));
          if (pCP)
            {
              callParameters[i] = CValue(*pCP->getValue().pDOUBLE);
            }
          break;

        case CFunctionParameter::TIME:
        case CFunctionParameter::VARIABLE:
          callParameters[i] = CValue::unknown;
          break;
        }
    }
}

//static
CFunctionAnalyzer::Result CFunctionAnalyzer::checkKineticFunction(const CFunction * f, const CReaction * reaction, const CModel * model)
{
  Result ret;

  //assume mass action is ok.
  if (dynamic_cast<const CMassAction*>(f)) return ret;

  std::cout << "  Kinetic Function: " << f->getObjectName() << ";   ";
  if ((f->isReversible() == TriFalse)) std::cout << "(irreversible)" << std::endl;
  if ((f->isReversible() == TriTrue)) std::cout << "(reversible)" << std::endl;

  //if (f->isReversible() != TriFalse) return ret;

  if (f->isReversible() == TriFalse)
    if (f->getVariables().getNumberOfParametersByUsage(CFunctionParameter::PRODUCT) > 0)
      {
        //error
        std::cout << "An irreversible kinetics should not depend on products." << std::endl;
      }

  std::vector<CValue> callParameters;

  //***** just the kinetic function *****
  std::cout << "               : " ; // << std::endl;

  //construct call parameter vector
  constructCallParameters(f->getVariables(), callParameters, false);
  //test if result is indeed 0 (as is required)
  std::cout << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters) << ", ";

  //construct call parameter vector
  constructCallParameters(f->getVariables(), callParameters, true);
  //test if result is indeed 0 (as is required)
  std::cout << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters); // << std::endl;

  if (reaction && model)
    {
      //construct call parameter vector
      constructCallParametersActualValues(callParameters, reaction);
      //test if result is indeed 0 (as is required)
      std::cout << ", " << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters) << std::endl;
    }
  else
    {
      std::cout << std::endl;
    }

  //***** now the kinetic function with single substrates or products == zero ******
  C_INT32 i, imax = f->getVariables().size();
  for (i = 0; i < imax; ++i)
    {
      if (f->getVariables()[i]->getUsage() == CFunctionParameter::SUBSTRATE)
        {
          std::cout << "    Substrate=0: " << f->getVariables()[i]->getObjectName() << "  "; // << std::endl;

          //construct call parameter vector
          constructCallParameters(f->getVariables(), callParameters, false);
          //set one substrate to zero
          callParameters[i] = CValue::zero;
          //test if result is indeed 0 (as is required)
          std::cout << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters) << ", ";

          //construct call parameter vector
          constructCallParameters(f->getVariables(), callParameters, true);
          //set one substrate to zero
          callParameters[i] = CValue::zero;
          //test if result is indeed 0 (as is required)
          std::cout << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters); // << std::endl;

          if (reaction && model)
            {
              //construct call parameter vector
              constructCallParametersActualValues(callParameters, reaction);
              //set one substrate to zero
              callParameters[i] = CValue::zero;
              //test if result is indeed 0 (as is required)
              std::cout << ", " << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters) << std::endl;
            }
          else
            {
              std::cout << std::endl;
            }
        }

      if (f->getVariables()[i]->getUsage() == CFunctionParameter::PRODUCT)
        {
          std::cout << "      Product=0: " << f->getVariables()[i]->getObjectName() << "  "; // << std::endl;

          //construct call parameter vector
          constructCallParameters(f->getVariables(), callParameters, false);
          //set one substrate to zero
          callParameters[i] = CValue::zero;
          //test if result is indeed 0 (as is required)
          std::cout << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters) << ", ";

          //construct call parameter vector
          constructCallParameters(f->getVariables(), callParameters, true);
          //set one substrate to zero
          callParameters[i] = CValue::zero;
          //test if result is indeed 0 (as is required)
          std::cout << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters); // << std::endl;

          if (reaction && model)
            {
              //construct call parameter vector
              constructCallParametersActualValues(callParameters, reaction);
              //set one substrate to zero
              callParameters[i] = CValue::zero;
              //test if result is indeed 0 (as is required)
              std::cout << ", " << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters) << std::endl;
            }
          else
            {
              std::cout << std::endl;
            }
        }
    }

  return ret;
}

//static
CFunctionAnalyzer::CValue CFunctionAnalyzer::evaluateNode(const CEvaluationNode * node, const std::vector<CValue> & callParameters)
{
  const CEvaluationNodeOperator * pENO = dynamic_cast<const CEvaluationNodeOperator*>(node);
  if (pENO)
    {
      switch (CEvaluationNode::subType(pENO->getType()))
        {
        case CEvaluationNodeOperator::MULTIPLY:
          return evaluateNode(pENO->getLeft(), callParameters) * evaluateNode(pENO->getRight(), callParameters);
          break;

        case CEvaluationNodeOperator::DIVIDE:
          return evaluateNode(pENO->getLeft(), callParameters) / evaluateNode(pENO->getRight(), callParameters);
          break;

        case CEvaluationNodeOperator::PLUS:
          return evaluateNode(pENO->getLeft(), callParameters) + evaluateNode(pENO->getRight(), callParameters);
          break;

        case CEvaluationNodeOperator::MINUS:
          return evaluateNode(pENO->getLeft(), callParameters) - evaluateNode(pENO->getRight(), callParameters);
          break;

        case CEvaluationNodeOperator::POWER:
          return evaluateNode(pENO->getLeft(), callParameters) ^ evaluateNode(pENO->getRight(), callParameters);
          break;
          //
          //           case MODULUS:
          //             Value = (C_FLOAT64) (((C_INT32) mpLeft->value()) % ((C_INT32) mpRight->value()));
          //             break;
          //

        default:
          break;
        }
    }

  const CEvaluationNodeNumber * pENN = dynamic_cast<const CEvaluationNodeNumber*>(node);
  if (pENN)
    {
      return pENN->value();
    }

  const CEvaluationNodeVariable * pENV = dynamic_cast<const CEvaluationNodeVariable*>(node);
  if (pENV)
    {
      return callParameters[pENV->getIndex()];
    }

  const CEvaluationNodeFunction * pENF = dynamic_cast<const CEvaluationNodeFunction*>(node);
  if (pENF)
    {
      //TODO: implement at least the most important functions
    }

  const CEvaluationNodeChoice * pENC = dynamic_cast<const CEvaluationNodeChoice*>(node);
  if (pENC)
    {
      //TODO: implement
    }

  return CValue::unknown;
}

//***********************************************************************************************

//static
void CModelAnalyzer::checkModel(const CModel* model)
{
  if (!model) return;

  C_INT32 i, imax = model->getTotSteps();
  for (i = 0; i < imax; ++i)
    {
      std::cout << "Reaction: " << model->getReactions()[i]->getObjectName() << std::endl;
      checkReaction(model->getReactions()[i], model);
    }
}

//static
void CModelAnalyzer::checkReaction(const CReaction* reaction, const CModel* model)
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
  CFunctionAnalyzer::checkKineticFunction(reaction->getFunction() , reaction, model);
}
