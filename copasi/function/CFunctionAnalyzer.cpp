// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionAnalyzer.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/13 15:06:27 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CFunctionAnalyzer.h"

#include "CEvaluationNode.h"
//#include "CEvaluationNodeOperator.h"
#include "CFunction.h"

//static
// const std::string CFunctionAnalyzer::CValue::StatusName[] =
// {
//   "unknown",
//   "exactly zero",
//   "negative",
//   "not positive",
//   "positive",
//   "not negative",
//   "not zero",
//   "invalid",
//   "known"
// };

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

    std::cout << "      *: " << *this << " * " << rhs << " = " << ret << std::endl;

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

    std::cout << "      /: " << *this << " / " << rhs << " = " << ret << std::endl;

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
    else if (rhs.getStatus() & zero)
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

    std::cout << "      +: " << *this << " + " << rhs << " = " << ret << std::endl;

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

    std::cout << "      ^: " << *this << " ^ " << rhs << " = " << ret << std::endl;

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
void CFunctionAnalyzer::constructCallParameters(const CFunctionParameters & fp, std::vector<CValue> & callParameters)
{
  C_INT32 i, imax = fp.size();
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
          callParameters[i] = CValue::positive;
          break;
        }
    }
}

//static
void CFunctionAnalyzer::checkKineticFunction(const CFunction * f)
{
  if (f->isReversible() != TriFalse) return;
  if (dynamic_cast<const CMassAction*>(f)) return;

  std::cout << "  Kinetic Function: " << f->getObjectName() << std::endl;

  //check function:
  // irrev: no products should occur
  // irrev: if substr=0 -> kinetics=0

  std::vector<CValue> callParameters;

  C_INT32 i, imax = f->getVariables().size();
  for (i = 0; i < imax; ++i)
    {
      if (f->getVariables()[i]->getUsage() == CFunctionParameter::SUBSTRATE)
        {
          std::cout << "    Substrate: " << f->getVariables()[i]->getObjectName() << "  " << std::endl;

          //construct call parameter vector
          constructCallParameters(f->getVariables(), callParameters);

          //set one substrate to zero
          callParameters[i] = CValue::zero;

          //test if result is indeed 0 (as is required)
          std::cout << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters) << std::endl;
        }
    }
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

  return CValue::unknown;
}

//***********************************************************************************************

#include "model/CModel.h"

//static
void CModelAnalyzer::checkModel(const CModel* model)
{
  if (!model) return;

  C_INT32 i, imax = model->getTotSteps();
  for (i = 0; i < imax; ++i)
    {
      std::cout << "Reaction: " << model->getReactions()[i]->getObjectName() << std::endl;
      checkReaction(model->getReactions()[i]);
    }
}

//static
void CModelAnalyzer::checkReaction(const CReaction* reaction)
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

  //mapping
  unsigned C_INT32 i, imax;
  imax = reaction->getChemEq().getSubstrates().size();
  for (i = 0; i < imax; ++i)
    {
      std::string tmpkey = reaction->getChemEq().getSubstrates()[i]->getMetaboliteKey();

      //each substrate of the reaction needs to be mapped to a function parameter with role SUBSTRATE
    }

  //for reversible reactions each product of the reaction needs to be mapped to a function parameter with role PRODUCT
  //for irreversible?

  //for all function parameters
  //  substr: must be matched to a substr. of the reaction (copasi bug?)
  //  Product: must be matched to a product of the reaction (copasi bug?)
  //  modifier: must be matched to a modifier of the reaction (only warning?). Must be matched to a metab (copasi bug?)
  //  parameter: must be matched to a local or global parameter (copasi bug?)
  //  volume: copasi bug
  //  time: copasi bug
  //  variable: ???

  //check mapping:
  // are all reaction participants mapped to a corresponding function parameter?

  //check function:
  // irrev: no products should occur
  // irrev: if substr=0 -> kinetics=0
  CFunctionAnalyzer::checkKineticFunction(reaction->getFunction() /*, reaction*/);
}
