// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionAnalyzer.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/22 23:59:00 $
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

CFunctionAnalyzer::Result::Result()
    : mpFunction(NULL),
    mIrreversibleKineticsWithProducts(false)
{};

bool CFunctionAnalyzer::Result::writeResult(std::ostream & os, bool rt, bool longText) const
  {
    bool ret = false;

    if (!mpFunction) return false;

    //function name
    if (rt) os << "<h3>";
    os << mpFunction->getObjectName();
    if (rt) os << "</h3>";
    os << "\n";

    if (mIrreversibleKineticsWithProducts)
      {
        os << "The kinetic function is marked as irreversible but at least one of its variables is labeled as product.\n";
      }

    return ret;
  }

void CFunctionAnalyzer::Result::writeTable(std::ostream & os, bool rt) const
  {
    if (!mpFunction) return;

    unsigned int i, imax;
    if (rt)
      {
        os << "<font color=\"#505080\"><TABLE>\n";

        os << "  <TR>\n";
        os << "    <TD></TD>\n";
        //CValue results
        unsigned int j, jmax = mUnchangedParameters.size();
        for (j = 0; j < jmax; ++j)
          os << "    <TD>" << mUnchangedParameters[j] << "</TD>\n";
        os << "  </TR>\n";

        imax = mSubstrateZero.size();
        for (i = 0; i < imax; ++i)
          {
            os << "  <TR>\n";
            //parameter name
            os << "    <TD>Substrate \"" << mpFunction->getVariables()[mSubstrateZero[i].first]->getObjectName() << "\" set to 0:</TD>\n";

            //CValue results
            unsigned int j, jmax = mSubstrateZero[i].second.size();
            for (j = 0; j < jmax; ++j)
              os << "    <TD>" << mSubstrateZero[i].second[j] << "</TD>\n";
            os << "  </TR>\n";
          }
        imax = mProductZero.size();
        for (i = 0; i < imax; ++i)
          {
            os << "  <TR>\n";
            //parameter name
            os << "    <TD>Product \"" << mpFunction->getVariables()[mProductZero[i].first]->getObjectName() << "\" set to 0: </TD>\n";

            //CValue results
            unsigned int j, jmax = mProductZero[i].second.size();
            for (j = 0; j < jmax; ++j)
              os << "    <TD>" << mProductZero[i].second[j] << "</TD>\n";
            os << "  </TR>\n";
          }
        os << "</TABLE></font>\n";
      }
  }

//     os << "<TABLE CELLSPACING=\"0\">\n";
//     os << "  <TR><TD COLSPAN=\"4\">" << ptr->getObjectDisplayName() << "</TD></TR>\n";
//     os << "  <TR>\n";
//     os << "    <TD " << (flagUM ? "BGCOLOR=\"red\"" : " ") << "><FONT POINT-SIZE=\"7.0\">UM</FONT>" << "" << "</TD>\n";
//     os << "    <TD " << (flagRM ? "BGCOLOR=\"green\"" : " ") << "><FONT POINT-SIZE=\"7.0\">RM</FONT>" << "" << "</TD>\n";
//     os << "    <TD " << (flagInUpToDateList ? "BGCOLOR=\"blue\"" : " ") << "><FONT POINT-SIZE=\"7.0\">UtD</FONT>" << "" << "</TD>\n";
//     os << "    <TD><FONT POINT-SIZE=\"7.0\">" << oss.str() << " </FONT></TD>\n";
//     os << "  </TR>\n";
//     os << "</TABLE>\n";

//         const CFunction * mpFunction;
//         bool mIrreversibleKineticsWithProducts;
//         std::vector<CValue> mUnchangedParameters;
//         std::vector<std::pair<int, std::vector<CValue> > > mSubstrateZero;
//         std::vector<std::pair<int, std::vector<CValue> > > mProductZero;

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

void CFunctionAnalyzer::checkKineticFunction(const CFunction * f, const CReaction * reaction)
{
  mResult.clear();
  mResult.mpFunction = f;
  //assume mass action is ok.
  if (dynamic_cast<const CMassAction*>(f)) return;

  std::cout << "  Kinetic Function: " << f->getObjectName() << ";   ";
  if ((f->isReversible() == TriFalse)) std::cout << "(irreversible)" << std::endl;
  if ((f->isReversible() == TriTrue)) std::cout << "(reversible)" << std::endl;

  //if (f->isReversible() != TriFalse) return ret;

  if (f->isReversible() == TriFalse)
    if (f->getVariables().getNumberOfParametersByUsage(CFunctionParameter::PRODUCT) > 0)
      {
        //error
        std::cout << "An irreversible kinetics should not depend on products." << std::endl;
        mResult.mIrreversibleKineticsWithProducts = true;
      }

  std::vector<CValue> callParameters;
  CValue tmpValue;

  //***** just the kinetic function *****
  std::cout << "               : " ; // << std::endl;

  //construct call parameter vector
  constructCallParameters(f->getVariables(), callParameters, false);
  tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters);
  std::cout << tmpValue << ", ";
  mResult.mUnchangedParameters.push_back(tmpValue);

  //construct call parameter vector
  constructCallParameters(f->getVariables(), callParameters, true);
  tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters);
  std::cout << tmpValue; // << std::endl;
  mResult.mUnchangedParameters.push_back(tmpValue);

  if (reaction)
    {
      //construct call parameter vector
      constructCallParametersActualValues(callParameters, reaction);
      tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters);
      std::cout << ", " << tmpValue << std::endl;
      mResult.mUnchangedParameters.push_back(tmpValue);
    }
  else
    {
      std::cout << std::endl;
    }

  //***** now the kinetic function with single substrates or products == zero ******
  std::vector<CValue> tmpValueVector;

  C_INT32 i, imax = f->getVariables().size();
  for (i = 0; i < imax; ++i)
    {
      if (f->getVariables()[i]->getUsage() == CFunctionParameter::SUBSTRATE)
        {
          std::cout << "    Substrate=0: " << f->getVariables()[i]->getObjectName() << "  "; // << std::endl;
          tmpValueVector.clear();

          //construct call parameter vector
          constructCallParameters(f->getVariables(), callParameters, false);
          //set one substrate to zero
          callParameters[i] = CValue::zero;
          tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters);
          std::cout << tmpValue << ", ";
          tmpValueVector.push_back(tmpValue);

          //construct call parameter vector
          constructCallParameters(f->getVariables(), callParameters, true);
          //set one substrate to zero
          callParameters[i] = CValue::zero;
          tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters);
          std::cout << tmpValue; // << std::endl;
          tmpValueVector.push_back(tmpValue);

          if (reaction)
            {
              //construct call parameter vector
              constructCallParametersActualValues(callParameters, reaction);
              //set one substrate to zero
              callParameters[i] = CValue::zero;
              tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters);
              //test if result is indeed 0 (as is required)
              std::cout << ", " << tmpValue << std::endl;
              tmpValueVector.push_back(tmpValue);
            }
          else
            {
              std::cout << std::endl;
            }

          mResult.mSubstrateZero.push_back(std::pair<int, std::vector<CValue> >(i, tmpValueVector));
        }

      if (f->getVariables()[i]->getUsage() == CFunctionParameter::PRODUCT)
        {
          std::cout << "      Product=0: " << f->getVariables()[i]->getObjectName() << "  "; // << std::endl;
          tmpValueVector.clear();

          //construct call parameter vector
          constructCallParameters(f->getVariables(), callParameters, false);
          //set one product to zero
          callParameters[i] = CValue::zero;
          tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters);
          std::cout << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters) << ", ";
          tmpValueVector.push_back(tmpValue);

          //construct call parameter vector
          constructCallParameters(f->getVariables(), callParameters, true);
          //set one substrate to zero
          callParameters[i] = CValue::zero;
          tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters);
          std::cout << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters); // << std::endl;
          tmpValueVector.push_back(tmpValue);

          if (reaction)
            {
              //construct call parameter vector
              constructCallParametersActualValues(callParameters, reaction);
              //set one substrate to zero
              callParameters[i] = CValue::zero;
              tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters);
              std::cout << ", " << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters) << std::endl;
              tmpValueVector.push_back(tmpValue);
            }
          else
            {
              std::cout << std::endl;
            }

          mResult.mProductZero.push_back(std::pair<int, std::vector<CValue> >(i, tmpValueVector));
        }
    }
}

//static
std::string CFunctionAnalyzer::write(int level, bool rt, const std::string & text, const std::string & longText)
{
  std::string ret;
  if (rt) ret += "<p>";
  ret += (text + "\n");
  if (longText != "")
    {
      if (rt) ret += "<br>";
      ret += longText + "\n";
    }
  if (rt) ret += "</p>";

  return ret;
}
