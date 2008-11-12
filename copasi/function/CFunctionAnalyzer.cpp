// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionAnalyzer.cpp,v $
//   $Revision: 1.14.14.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/12 14:50:38 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CFunctionAnalyzer.h"

#include "CEvaluationNode.h"
//#include "CEvaluationNodeOperator.h"
#include "CFunction.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"

#ifdef WIN32
double trunc(double x)
{return (x < 0.0) ? -floor(fabs(x)) : floor(x);}
#endif

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

bool CFunctionAnalyzer::CValue::isPositive() const
  {
    if (mStatus == positive) return true;
    if ((mStatus == known) && (mDouble > 0.0)) return true;
    return false;
  }

bool CFunctionAnalyzer::CValue::containsPositive() const
  {
    if (mStatus & positive) return true;
    if ((mStatus & known) && (mDouble > 0.0)) return true;
    return false;
  }

bool CFunctionAnalyzer::CValue::isZero() const
  {
    if (mStatus == zero) return true;
    if ((mStatus == known) && (mDouble == 0.0)) return true;
    return false;
  }

bool CFunctionAnalyzer::CValue::containsZero() const
  {
    if (mStatus & zero) return true;
    if ((mStatus & known) && (mDouble == 0.0)) return true;
    return false;
  }

bool CFunctionAnalyzer::CValue::isNegative() const
  {
    if (mStatus == negative) return true;
    if ((mStatus == known) && (mDouble < 0.0)) return true;
    return false;
  }

bool CFunctionAnalyzer::CValue::containsNegative() const
  {
    if (mStatus & negative) return true;
    if ((mStatus & known) && (mDouble < 0.0)) return true;
    return false;
  }

bool CFunctionAnalyzer::CValue::isInvalid() const
  {
    if (mStatus == invalid) return true;
    return false;
  }

bool CFunctionAnalyzer::CValue::containsInvalid() const
  {
    if (mStatus & invalid) return true;
    return false;
  }

bool CFunctionAnalyzer::CValue::operator==(const CValue & rhs) const
  {
    if (mStatus != rhs.mStatus) return false;
    if ((mStatus & known) && (mDouble != rhs.mDouble)) return false;
    return true;
  }

//***********************************************************************************************

CFunctionAnalyzer::Result::Result()
    : mpFunction(NULL),
    mIrreversibleKineticsWithProducts(false),
    mReversibleNonSplitable(false)
{};

bool CFunctionAnalyzer::Result::writeResult(std::ostream & os, bool rt, bool verbose) const
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
        os << write(1, rt, "The kinetic function is marked as irreversible but at least one of its variables is labeled as product.\n", "");
        ret = true;
      }

    //interpret the CValues
    bool isReversible = (mpFunction->isReversible() == TriTrue);

    std::ostringstream tmpss;
    bool eee = mOriginalFunction.writeAnalysis(tmpss, rt, isReversible);
    if (eee) ret = true;
    if (eee || verbose)
      {
        os << tmpss.str();
        mOriginalFunction.writeTable(os, rt);
      }

    //deal with splitted reversible functions
    if (mReversibleNonSplitable)
      {
        os << write(1, rt, "Copasi is not able to split the reversible kinetic function into two irreversible functions.\n", "");
        ret = true;
      }
    else if (isReversible)
      {
        std::ostringstream tmpss1;
        bool eee1 = mFPart.writeAnalysis(tmpss1, rt, false);

        std::ostringstream tmpss2;
        bool eee2 = mBPart.writeAnalysis(tmpss2, rt, false);
        if (eee1 || eee2) ret = true;
        if (eee1 || eee2 || verbose)
          {
            os << "The function was split into forward and backwards parts. Forward part:\n";
            if (rt) os << "<br>";
            os << tmpss1.str();
            mFPart.writeTable(os, rt);
            os << " Backwards part:\n";
            if (rt) os << "<br>";
            os << tmpss2.str();
            mBPart.writeTable(os, rt);
          }
      }

    return ret;
  }

bool CFunctionAnalyzer::Result::FunctionInformation::writeAnalysis(std::ostream & os, bool rt, bool reversible /*const CFunction * pF*/) const
  {
    bool ret = false;

    if (reversible) //reversible function
      {
        //unchanged values
        assert(mUnchangedParameters.size() >= 2);

        //first for positive parameter values
        if (!mUnchangedParameters[1].containsPositive())
          {
            os << write(1, rt, "The kinetic function cannot take positive values for positive parameter values.\n",
                        "This means the reaction will never proceed in the forward direction.");
            ret = true;
          }

        if (!mUnchangedParameters[1].containsZero())
          {
            os << write(1, rt, "The kinetic function never equals zero for positive parameter values.\n",
                        "This is unexpected for reversible reactions.");
            ret = true;
          }

        if (!mUnchangedParameters[1].containsNegative())
          {
            os << write(1, rt, "The kinetic function cannot take negative values for positive parameter values.\n",
                        "This means the reaction will never proceed in the backwards direction.");
            ret = true;
          }

        if (mUnchangedParameters[1].isInvalid())
          {
            os << write(2, rt, "The kinetic function is always invalid for positive parameter values.\n", "");
            ret = true;
          }
        else if (mUnchangedParameters[1].containsInvalid())
          {
            os << write(1, rt, "The kinetic function can be invalid even if metabolite concentrations and parameter values are positive.\n", "");
            ret = true;
          }

        //now report if the result is different for the actual parameters values
        if ((mUnchangedParameters.size() > 2) && (!(mUnchangedParameters[1] == mUnchangedParameters[2])))
          {
            if (!mUnchangedParameters[2].containsPositive())
              {
                os << write(1, rt, "The kinetic function cannot take positive values for the actual parameter values.\n",
                            "This means the reaction will never proceed in the forward direction.");
                ret = true;
              }

            if (!mUnchangedParameters[2].containsZero())
              {
                os << write(1, rt, "The kinetic function never equals zero for the actual parameter values.\n",
                            "This is unexpected for reversible reactions.");
                ret = true;
              }

            if (!mUnchangedParameters[2].containsNegative())
              {
                os << write(1, rt, "The kinetic function cannot take negative values for the actual parameter values.\n",
                            "This means the reaction will never proceed in the backwards direction.");
                ret = true;
              }

            if (mUnchangedParameters[2].isInvalid())
              {
                os << write(2, rt, "The kinetic function is always invalid for the actual parameter values.\n", "");
                ret = true;
              }
            else if (mUnchangedParameters[2].containsInvalid())
              {
                os << write(1, rt, "The kinetic function can be invalid for the actual parameter values even if metabolite concentrations are positive.\n", "");
                ret = true;
              }
          }

        C_INT32 i, imax;

        // Substrate concentrations set to zero
        imax = mSubstrateZero.size();
        for (i = 0; i < imax; ++i)
          {
            assert(mSubstrateZero[i].second.size() >= 2);

            //first for positive parameter values
            if (mSubstrateZero[i].second[1].isNegative())
              {
                os << write(0, rt, "The kinetic function is always negative for positive parameter values if substrate \""
                            + mSubstrateZero[i].first.second //  pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" ,
                            "This is the expected behaviour for reversible reactions. Without substrates the reaction can only proceed backwards.");
              }
            else if (mSubstrateZero[i].second[1].containsNegative())
              {
                os << write(1, rt, "Copasi could not show that the kinetic function is always negative for positive parameter values if substrate \""
                            + mSubstrateZero[i].first.second //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" , "");
                ret = true;
              }
            else
              {
                os << write(2, rt, "The kinetic function is never negative for positive parameter values if substrate \""
                            + mSubstrateZero[i].first.second //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" ,
                            "This means the reaction never proceeds backwards even if no substrate is present. This is unexpected for a reversible reaction.");
                ret = true;
              }

            if (mSubstrateZero[i].second[1].isInvalid())
              {
                os << write(2, rt, "The kinetic function is always invalid for positive parameter values if substrate \""
                            + mSubstrateZero[i].first.second  //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" , "");
                ret = true;
              }
            else if (mSubstrateZero[i].second[1].containsInvalid())
              {
                os << write(1, rt, "The kinetic function can be invalid for positive parameter values if substrate \""
                            + mSubstrateZero[i].first.second //  pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" , "");
                ret = true;
              }

            //now report if the result is different for the actual parameters values
            if ((mSubstrateZero[i].second.size() > 2) && (!(mSubstrateZero[i].second[1] == mSubstrateZero[i].second[2])))
              {
                if (mSubstrateZero[i].second[2].isNegative())
                  {
                    os << write(0, rt, "The kinetic function is always negative for the actual parameter values if substrate \""
                                + mSubstrateZero[i].first.second //  pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" ,
                                "This is the expected behaviour for reversible reactions. Without substrates the reaction can only proceed backwards.");
                  }
                else if (mSubstrateZero[i].second[2].containsNegative())
                  {
                    os << write(1, rt, "Copasi could not show that the kinetic function is always negative for the actual parameter values if substrate \""
                                + mSubstrateZero[i].first.second //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" , "");
                    ret = true;
                  }
                else
                  {
                    os << write(2, rt, "The kinetic function is never negative for the actual parameter values if substrate \""
                                + mSubstrateZero[i].first.second //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" ,
                                "This means the reaction never proceeds backwards even if no substrate is present. This is unexpected for a reversible reaction.");
                    ret = true;
                  }

                if (mSubstrateZero[i].second[2].isInvalid())
                  {
                    os << write(2, rt, "The kinetic function is always invalid for the actual parameter values if substrate \""
                                + mSubstrateZero[i].first.second //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" , "");
                    ret = true;
                  }
                else if (mSubstrateZero[i].second[2].containsInvalid())
                  {
                    os << write(1, rt, "The kinetic function can be invalid for the actual parameter values if substrate \""
                                + mSubstrateZero[i].first.second //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" , "");
                    ret = true;
                  }
              }
          } //loop over substrates that are set to zero

        // Product concentrations set to zero
        imax = mProductZero.size();
        for (i = 0; i < imax; ++i)
          {
            assert(mProductZero[i].second.size() >= 2);

            //first for positive parameter values
            if (mProductZero[i].second[1].isPositive())
              {
                os << write(0, rt, "The kinetic function is always positive for positive parameter values if product \""
                            + mProductZero[i].first.second //  pF->getVariables()[mProductZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" ,
                            "This is the expected behaviour for reversible reactions. With products absent the reaction can only proceed forward.");
              }
            else if (mProductZero[i].second[1].containsPositive())
              {
                os << write(1, rt, "Copasi could not show that the kinetic function is always positive for positive parameter values if product \""
                            + mProductZero[i].first.second //pF->getVariables()[mProductZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" , "");
                ret = true;
              }
            else
              {
                os << write(2, rt, "The kinetic function is never positive for positive parameter values if product \""
                            + mProductZero[i].first.second //pF->getVariables()[mProductZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" ,
                            "This means the reaction never proceeds forward even if no product is present. This is unexpected for a reversible reaction.");
                ret = true;
              }

            if (mProductZero[i].second[1].isInvalid())
              {
                os << write(2, rt, "The kinetic function is always invalid for positive parameter values if product \""
                            + mProductZero[i].first.second  //pF->getVariables()[mProductZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" , "");
                ret = true;
              }
            else if (mProductZero[i].second[1].containsInvalid())
              {
                os << write(1, rt, "The kinetic function can be invalid for positive parameter values if product \""
                            + mProductZero[i].first.second //  pF->getVariables()[mProductZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" , "");
                ret = true;
              }

            //now report if the result is different for the actual parameters values
            if ((mProductZero[i].second.size() > 2) && (!(mProductZero[i].second[1] == mProductZero[i].second[2])))
              {
                if (mProductZero[i].second[2].isPositive())
                  {
                    os << write(0, rt, "The kinetic function is always positive for the actual parameter values if product \""
                                + mProductZero[i].first.second //  pF->getVariables()[mProductZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" ,
                                "This is the expected behaviour for reversible reactions. With products absent the reaction can only proceed forward.");
                  }
                else if (mProductZero[i].second[2].containsPositive())
                  {
                    os << write(1, rt, "Copasi could not show that the kinetic function is always positive for the actual parameter values if product \""
                                + mProductZero[i].first.second //pF->getVariables()[mProductZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" , "");
                    ret = true;
                  }
                else
                  {
                    os << write(2, rt, "The kinetic function is never positive for the actual parameter values if product \""
                                + mProductZero[i].first.second //pF->getVariables()[mProductZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" ,
                                "This means the reaction never proceeds forward even if no product is present. This is unexpected for a reversible reaction.");
                    ret = true;
                  }

                if (mProductZero[i].second[2].isInvalid())
                  {
                    os << write(2, rt, "The kinetic function is always invalid for the actual parameter values if substrate \""
                                + mProductZero[i].first.second //pF->getVariables()[mProductZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" , "");
                    ret = true;
                  }
                else if (mProductZero[i].second[2].containsInvalid())
                  {
                    os << write(1, rt, "The kinetic function can be invalid for the actual parameter values if substrate \""
                                + mProductZero[i].first.second //pF->getVariables()[mProductZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" , "");
                    ret = true;
                  }
              }
          } //loop over products that are set to zero
      }
    else //irreversible function
      {
        //unchanged values
        assert(mUnchangedParameters.size() >= 2);

        //first for positive parameter values
        if (mUnchangedParameters[1].isPositive())
          {
            os << write(0, rt, "The kinetic function is positive for positive parameter values.\n", "");
          }
        else
          {
            os << write(1, rt, "Copasi could not show that the kinetic function is positive for positive parameter values.\n", "");
            ret = true;
          }

        if (mUnchangedParameters[1].isZero())
          {
            os << write(2, rt, "The kinetic function is always zero for positive parameter values.\n", "");
            ret = true;
          }
        else if (mUnchangedParameters[1].containsZero())
          {
            os << write(1, rt, "The kinetic function can be zero even if substrate concentrations and parameter values are positive.\n", "");
            ret = true;
          }

        if (mUnchangedParameters[1].isNegative())
          {
            os << write(2, rt, "The kinetic function is always negative for positive parameter values.\n", "");
            ret = true;
          }
        else if (mUnchangedParameters[1].containsNegative())
          {
            os << write(1, rt, "The kinetic function can be negative even if substrate concentrations and parameter values are positive.\n", "");
            ret = true;
          }

        if (mUnchangedParameters[1].isInvalid())
          {
            os << write(2, rt, "The kinetic function is always invalid for positive parameter values.\n", "");
            ret = true;
          }
        else if (mUnchangedParameters[1].containsInvalid())
          {
            os << write(1, rt, "The kinetic function can be invalid even if substrate concentrations and parameter values are positive.\n", "");
            ret = true;
          }

        //now report if the result is different for the actual parameters values
        if ((mUnchangedParameters.size() > 2) && (!(mUnchangedParameters[1] == mUnchangedParameters[2])))
          {
            if (mUnchangedParameters[2].isPositive())
              {
                os << write(0, rt, "The kinetic function is positive for the actual parameter values.\n", "");
              }
            else
              {
                os << write(1, rt, "Copasi could not show that the kinetic function is positive for the actual parameter values.\n", "");
                ret = true;
              }

            if (mUnchangedParameters[2].isZero())
              {
                os << write(2, rt, "The kinetic function is always zero for the actual parameter values.\n", "");
                ret = true;
              }
            else if (mUnchangedParameters[2].containsZero())
              {
                os << write(1, rt, "The kinetic function can be zero for the actual parameter values even if substrate concentrations are positive.\n", "");
                ret = true;
              }

            if (mUnchangedParameters[2].isNegative())
              {
                os << write(2, rt, "The kinetic function is always negative for the actual parameter values.\n", "");
                ret = true;
              }
            else if (mUnchangedParameters[2].containsNegative())
              {
                os << write(1, rt, "The kinetic function can be negative for the actual parameter values even if substrate concentrations are positive.\n", "");
                ret = true;
              }

            if (mUnchangedParameters[2].isInvalid())
              {
                os << write(2, rt, "The kinetic function is always invalid for the actual parameter values.\n", "");
                ret = true;
              }
            else if (mUnchangedParameters[2].containsInvalid())
              {
                os << write(1, rt, "The kinetic function can be invalid for the actual parameter values even if substrate concentrations are positive.\n", "");
                ret = true;
              }
          }

        C_INT32 i, imax;

        // Substrate concentrations set to zero
        imax = mSubstrateZero.size();
        for (i = 0; i < imax; ++i)
          {
            assert(mSubstrateZero[i].second.size() >= 2);

            //first for positive parameter values
            if (mSubstrateZero[i].second[1].isZero())
              {
                os << write(0, rt, "The kinetic function is always zero for positive parameter values if substrate \""
                            + mSubstrateZero[i].first.second //  pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" , "");
              }
            else if (mSubstrateZero[i].second[1].containsZero())
              {
                os << write(1, rt, "Copasi could not show that the kinetic function is always zero for positive parameter values if substrate \""
                            + mSubstrateZero[i].first.second //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" , "");
                ret = true;
              }
            else
              {
                os << write(2, rt, "The kinetic function is never zero for positive parameter values if substrate \""
                            + mSubstrateZero[i].first.second //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" , "");
                ret = true;
              }

            if (mSubstrateZero[i].second[1].isInvalid())
              {
                os << write(2, rt, "The kinetic function is always invalid for positive parameter values if substrate \""
                            + mSubstrateZero[i].first.second  //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" , "");
                ret = true;
              }
            else if (mSubstrateZero[i].second[1].containsInvalid())
              {
                os << write(1, rt, "The kinetic function can be invalid for positive parameter values if substrate \""
                            + mSubstrateZero[i].first.second //  pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                            + "\" is set to zero.\n" , "");
                ret = true;
              }

            //now report if the result is different for the actual parameters values
            if ((mSubstrateZero[i].second.size() > 2) && (!(mSubstrateZero[i].second[1] == mSubstrateZero[i].second[2])))
              {
                if (mSubstrateZero[i].second[2].isZero())
                  {
                    os << write(0, rt, "The kinetic function is always zero for the actual parameter values if substrate \""
                                + mSubstrateZero[i].first.second //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" , "");
                  }
                else if (mSubstrateZero[i].second[2].containsZero())
                  {
                    os << write(1, rt, "Copasi could not show that the kinetic function is always zero for the actual parameter values if substrate \""
                                + mSubstrateZero[i].first.second //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" , "");
                    ret = true;
                  }
                else
                  {
                    os << write(2, rt, "The kinetic function is never zero for the actual parameter values if substrate \""
                                + mSubstrateZero[i].first.second //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" , "");
                    ret = true;
                  }

                if (mSubstrateZero[i].second[2].isInvalid())
                  {
                    os << write(2, rt, "The kinetic function is always invalid for the actual parameter values if substrate \""
                                + mSubstrateZero[i].first.second //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" , "");
                    ret = true;
                  }
                else if (mSubstrateZero[i].second[2].containsInvalid())
                  {
                    os << write(1, rt, "The kinetic function can be invalid for the actual parameter values if substrate \""
                                + mSubstrateZero[i].first.second //pF->getVariables()[mSubstrateZero[i].first]->getObjectName()
                                + "\" is set to zero.\n" , "");
                    ret = true;
                  }
              }
          } //loop over substrates that are set to zero
      } //irreversible

    //mUnchangedParameters
    //mSubstrateZero
    //mProductZero

    return ret;
  }

void CFunctionAnalyzer::Result::FunctionInformation::writeTable(std::ostream & os, bool rt) const
  {
    //if (!pF) return;

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
            os << "    <TD>Substrate \"" << mSubstrateZero[i].first.second /*pF->getVariables()[mSubstrateZero[i].first]->getObjectName()*/ << "\" set to 0:</TD>\n";

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
            os << "    <TD>Product \"" << mProductZero[i].first.second << "\" set to 0: </TD>\n";

            //CValue results
            unsigned int j, jmax = mProductZero[i].second.size();
            for (j = 0; j < jmax; ++j)
              os << "    <TD>" << mProductZero[i].second[j] << "</TD>\n";
            os << "  </TR>\n";
          }
        os << "</TABLE></font>\n";
      }
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
        case CFunctionParameter::TEMPORARY:
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
        case CFunctionParameter::TEMPORARY:
          callParameters[i] = CValue::unknown;
          break;
        }
    }
}

//static
CFunctionAnalyzer::CValue CFunctionAnalyzer::evaluateNode(const CEvaluationNode * node, const std::vector<CValue> & callParameters,
    Mode mode)
{
  const CEvaluationNodeOperator * pENO = dynamic_cast<const CEvaluationNodeOperator*>(node);
  if (pENO)
    {
      switch (CEvaluationNode::subType(pENO->getType()))
        {
        case CEvaluationNodeOperator::MULTIPLY:
          return evaluateNode(pENO->getLeft(), callParameters, mode) * evaluateNode(pENO->getRight(), callParameters, mode);
          break;

        case CEvaluationNodeOperator::DIVIDE:
          return evaluateNode(pENO->getLeft(), callParameters, mode) / evaluateNode(pENO->getRight(), callParameters, mode);
          break;

        case CEvaluationNodeOperator::PLUS:
          return evaluateNode(pENO->getLeft(), callParameters, mode) + evaluateNode(pENO->getRight(), callParameters, mode);
          break;

        case CEvaluationNodeOperator::MINUS:
          return evaluateNode(pENO->getLeft(), callParameters, mode) - evaluateNode(pENO->getRight(), callParameters, mode);
          break;

        case CEvaluationNodeOperator::POWER:
          return evaluateNode(pENO->getLeft(), callParameters, mode) ^ evaluateNode(pENO->getRight(), callParameters, mode);
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
      if (callParameters.size() < pENV->getIndex() + 1) return CValue::invalid;
      return callParameters[pENV->getIndex()];
    }

  const CEvaluationNodeFunction * pENF = dynamic_cast<const CEvaluationNodeFunction*>(node);
  if (pENF)
    {
      //TODO: implement at least the most important functions
      switch (CEvaluationNode::subType(pENF->getType()))
        {
        case CEvaluationNodeFunction::MINUS:
          return evaluateNode(pENF->getLeft(), callParameters, mode).invert();
          break;

        default:
          break;
        }
    }

  const CEvaluationNodeChoice * pENC = dynamic_cast<const CEvaluationNodeChoice*>(node);
  if (pENC)
    {
      //TODO: implement
    }

  const CEvaluationNodeCall * pENCall = dynamic_cast<const CEvaluationNodeCall*>(node);
  if (pENCall)
    {
      //some checks
      if (!pENCall->getCalledTree()) return CValue::invalid;
      const CFunction * tmpFunc = dynamic_cast<const CFunction*>(pENCall->getCalledTree());
      if (!tmpFunc) return CValue::invalid;
      if (!pENCall->getCalledTree()->getRoot()) return CValue::invalid;
      unsigned C_INT32 i, imax = tmpFunc->getVariables().size();
      if (imax != pENCall->getListOfChildNodes().size()) return CValue::invalid;

      std::vector<CValue> localCallParameters;
      localCallParameters.resize(imax);
      for (i = 0; i < imax; ++i)
        {
          localCallParameters[i] = evaluateNode(pENCall->getListOfChildNodes()[i], callParameters, mode);
        }
      return CFunctionAnalyzer::evaluateNode(pENCall->getCalledTree()->getRoot(), localCallParameters, mode);
    }

  const CEvaluationNodeObject * pENObject = dynamic_cast<const CEvaluationNodeObject*>(node);
  if (pENObject)
    {
      if (mode == NOOBJECT) return CValue::invalid;
      if (mode == POSITIVE) return CValue::positive;
      //TODO: implement GENERAL and ACTUAL
    }

  return CValue::unknown;
}

void CFunctionAnalyzer::checkKineticFunction(const CFunction * f, const CReaction * reaction)
{
  mResult.clear();
  mResult.mpFunction = f;
  //assume mass action is ok.
  if (dynamic_cast<const CMassAction*>(f)) return;

  //std::cout << "  Kinetic Function: " << f->getObjectName() << ";   ";
  //if ((f->isReversible() == TriFalse)) std::cout << "(irreversible)" << std::endl;
  //if ((f->isReversible() == TriTrue)) std::cout << "(reversible)" << std::endl;

  //if (f->isReversible() != TriFalse) return ret;

  if (f->isReversible() == TriFalse)
    if (f->getVariables().getNumberOfParametersByUsage(CFunctionParameter::PRODUCT) > 0)
      {
        //error
        //std::cout << "An irreversible kinetics should not depend on products." << std::endl;
        mResult.mIrreversibleKineticsWithProducts = true;
      }

  std::vector<CValue> callParameters;
  CValue tmpValue;

  //***** just the kinetic function *****
  //std::cout << "               : " ; // << std::endl;

  //construct call parameter vector
  constructCallParameters(f->getVariables(), callParameters, false);
  tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters, NOOBJECT);
  //std::cout << tmpValue << ", ";
  mResult.mOriginalFunction.mUnchangedParameters.push_back(tmpValue);

  //construct call parameter vector
  constructCallParameters(f->getVariables(), callParameters, true);
  tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters, NOOBJECT);
  //std::cout << tmpValue; // << std::endl;
  mResult.mOriginalFunction.mUnchangedParameters.push_back(tmpValue);

  if (reaction)
    {
      //construct call parameter vector
      constructCallParametersActualValues(callParameters, reaction);
      tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters, NOOBJECT);
      //std::cout << ", " << tmpValue << std::endl;
      mResult.mOriginalFunction.mUnchangedParameters.push_back(tmpValue);
    }
  else
    {
      //std::cout << std::endl;
    }

  //***** now the kinetic function with single substrates or products == zero ******
  std::vector<CValue> tmpValueVector;

  C_INT32 i, imax = f->getVariables().size();
  for (i = 0; i < imax; ++i)
    {
      if (f->getVariables()[i]->getUsage() == CFunctionParameter::SUBSTRATE)
        {
          //std::cout << "    Substrate=0: " << f->getVariables()[i]->getObjectName() << "  "; // << std::endl;
          tmpValueVector.clear();

          //construct call parameter vector
          constructCallParameters(f->getVariables(), callParameters, false);
          //set one substrate to zero
          callParameters[i] = CValue::zero;
          tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters, NOOBJECT);
          //std::cout << tmpValue << ", ";
          tmpValueVector.push_back(tmpValue);

          //construct call parameter vector
          constructCallParameters(f->getVariables(), callParameters, true);
          //set one substrate to zero
          callParameters[i] = CValue::zero;
          tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters, NOOBJECT);
          //std::cout << tmpValue; // << std::endl;
          tmpValueVector.push_back(tmpValue);

          if (reaction)
            {
              //construct call parameter vector
              constructCallParametersActualValues(callParameters, reaction);
              //set one substrate to zero
              callParameters[i] = CValue::zero;
              tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters, NOOBJECT);
              //test if result is indeed 0 (as is required)
              //std::cout << ", " << tmpValue << std::endl;
              tmpValueVector.push_back(tmpValue);
            }
          else
            {
              //std::cout << std::endl;
            }

          mResult.mOriginalFunction.mSubstrateZero.push_back(std::pair<std::pair<int, std::string>, std::vector<CValue> >(std::pair<int, std::string>(i, f->getVariables()[i]->getObjectName()), tmpValueVector));
        }

      if (f->getVariables()[i]->getUsage() == CFunctionParameter::PRODUCT)
        {
          //std::cout << "      Product=0: " << f->getVariables()[i]->getObjectName() << "  "; // << std::endl;
          tmpValueVector.clear();

          //construct call parameter vector
          constructCallParameters(f->getVariables(), callParameters, false);
          //set one product to zero
          callParameters[i] = CValue::zero;
          tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters, NOOBJECT);
          //std::cout << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters) << ", ";
          tmpValueVector.push_back(tmpValue);

          //construct call parameter vector
          constructCallParameters(f->getVariables(), callParameters, true);
          //set one substrate to zero
          callParameters[i] = CValue::zero;
          tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters, NOOBJECT);
          //std::cout << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters); // << std::endl;
          tmpValueVector.push_back(tmpValue);

          if (reaction)
            {
              //construct call parameter vector
              constructCallParametersActualValues(callParameters, reaction);
              //set one substrate to zero
              callParameters[i] = CValue::zero;
              tmpValue = CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters, NOOBJECT);
              //std::cout << ", " << CFunctionAnalyzer::evaluateNode(f->getRoot(), callParameters) << std::endl;
              tmpValueVector.push_back(tmpValue);
            }
          else
            {
              //std::cout << std::endl;
            }

          mResult.mOriginalFunction.mProductZero.push_back(std::pair<std::pair<int, std::string>, std::vector<CValue> >(std::pair<int, std::string>(i, f->getVariables()[i]->getObjectName()), tmpValueVector));

          //(std::pair<int, std::vector<CValue> >(i, tmpValueVector));
        }
    }

  //try to split reversible functions
  if ((f->isReversible() == TriTrue))
    {
      std::pair<CFunction *, CFunction *> tmp;
      tmp = f->splitFunction(NULL, "f", "b");

      if ((tmp.first == NULL) || (tmp.second == NULL))
        {
          mResult.mReversibleNonSplitable = true;
        }
      else
        {
          CFunctionAnalyzer fa1(tmp.first);
          mResult.mFPart = fa1.getResult().mOriginalFunction;

          CFunctionAnalyzer fa2(tmp.second);
          mResult.mBPart = fa2.getResult().mOriginalFunction;
        }

      pdelete(tmp.first);
      pdelete(tmp.second);
    }
}

//static
std::string CFunctionAnalyzer::write(int level, bool rt, const std::string & text, const std::string & longText)
{
  std::string color;
  switch (level)
    {
    case 0: color = "\"#008000\""; break;
    case 1: color = "\"#909000\""; break;
    case 2: color = "\"#800000\""; break;
    case 3: color = "\"#c04040\""; break;
    default: color = "\"#0000a0\""; break;
    }

  std::string ret;
  if (rt) ret += "<p><font color=" + color + ">";
  ret += (text + "\n");
  if (longText != "")
    {
      if (rt) ret += "<br>";
      ret += longText + "\n";
    }
  if (rt) ret += "</font></p>";

  return ret;
}
