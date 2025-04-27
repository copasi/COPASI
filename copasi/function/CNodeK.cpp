// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// CNodeK.cpp : classes for function tree
//
/////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "copasi/copasi.h"
#include "copasi/utilities/CReadConfig.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/utility.h"

#include "CNodeK.h"

CNodeK::CNodeK()
{
  CONSTRUCTOR_TRACE;
  mType = N_NOP;
  mSubtype = N_NOP;
  mLeft = NULL;
  mRight = NULL;
  mConstant = 0.0;
  mIndex = -1;
  mOldIndex = -1;
}

CNodeK::CNodeK(const CNodeK & src)
{
  CONSTRUCTOR_TRACE;
  mType = src.mType;
  mSubtype = src.mSubtype;
  mLeft = src.mLeft;
  mRight = src.mRight;
  mConstant = src.mConstant;
  mName = src.mName;
  mIndex = src.mIndex;
  mOldIndex = src.mOldIndex;
}

CNodeK::CNodeK(char type, char subtype)
{
  CONSTRUCTOR_TRACE;
  mType = type;
  mSubtype = subtype;
  mLeft = NULL;
  mRight = NULL;
  mConstant = 0.0;
  mIndex = -1;
  mOldIndex = -1;
}

CNodeK::CNodeK(const std::string & name)
{
  CONSTRUCTOR_TRACE;
  mType = N_IDENTIFIER;
  mSubtype = N_NOP;
  mLeft = NULL;
  mRight = NULL;
  mConstant = 0.0;
  mName = name;
  mIndex = -1;
  mOldIndex = -1;
}

CNodeK::CNodeK(C_FLOAT64 constant)
{
  CONSTRUCTOR_TRACE;
  mType = N_NUMBER;
  mSubtype = N_NOP;
  mLeft = NULL;
  mRight = NULL;
  mConstant = constant;
  mIndex = -1;
  mOldIndex = -1;
}

void CNodeK::cleanup()
{}

CNodeK::~CNodeK()
{
  DESTRUCTOR_TRACE;
}

C_INT32 CNodeK::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;

  if ((Fail = configbuffer.getVariable("Node", "node", &mType, &mSubtype,
                                       CReadConfig::SEARCH)))
    return Fail;

  /* This COPASI treats all these as identifiers */
  if (mType == N_SUBSTRATE ||
      mType == N_PRODUCT ||
      mType == N_MODIFIER ||
      mType == N_KCONSTANT)
    {
      mSubtype = mType;
      mType = N_IDENTIFIER;
    }

  // leave the Left & Right pointers out
  // value of the constant if one
  if (mType == N_NUMBER)
    {
      if ((Fail = configbuffer.getVariable("Value", "C_FLOAT64", &mConstant)))
        return Fail;
    }
  else if (mType == N_IDENTIFIER)
    {
      if ((Fail = configbuffer.getVariable("Index", "C_INT32", &mIndex)))
        return Fail;

      if ((Fail = configbuffer.getVariable("Name", "string", &mName)))
        return Fail;
    }

  return Fail;
}

/*
std::string CNodeK::getExplicitFunctionString(const std::vector< std::vector< std::string > > & callParameterNames,
    const std::string &r)
{
  char fstr[256];
  switch (mType)
    {
    case N_ROOT:
      return mLeft->getExplicitFunctionString(callParameterNames, r);
    case N_NUMBER:
      sprintf(fstr, "%-20g", mConstant);
      mExplicitFunction = fstr;
      break;
    case N_IDENTIFIER:
      FixSName(callParameterNames[mIndex][0], mExplicitFunction);
      if (mSubtype == N_KCONSTANT)
        mExplicitFunction += r;
      break;
    case N_OPERATOR:
      switch (mSubtype)
        {
        case '+':
          mExplicitFunction = mLeft->getExplicitFunctionString(callParameterNames, r) + "+"
                              + mRight->getExplicitFunctionString(callParameterNames, r);
          break;
        case '-':
          mExplicitFunction = mLeft->getExplicitFunctionString(callParameterNames, r) + "-"
                              + mRight->getExplicitFunctionString(callParameterNames, r);
          break;
        case '*':
          mExplicitFunction = "(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")*(" + mRight->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case '/':
          mExplicitFunction = "(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")/(" + mRight->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case '^':
          mExplicitFunction = "(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")^(" + mRight->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        default:
          mExplicitFunction.empty();
        }
      break;
    case N_FUNCTION:
      switch (mSubtype)
        {
        case '+':
          mExplicitFunction = "+(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case '-':
          mExplicitFunction = "-(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_EXP:
          mExplicitFunction = "e^(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_LOG:
          mExplicitFunction = "log10(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_LOG10:
          mExplicitFunction = "log(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_SIN:
          mExplicitFunction = "sin(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_COS:
          mExplicitFunction = "cos(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_TAN:
          mExplicitFunction = "tan(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_SEC:
          mExplicitFunction = "sec(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_CSC:
          mExplicitFunction = "csc(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_COT:
          mExplicitFunction = "cot(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_SINH:
          mExplicitFunction = "sinh(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_COSH:
          mExplicitFunction = "cosh(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_TANH:
          mExplicitFunction = "tanh(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_SECH:
          mExplicitFunction = "sech(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_CSCH:
          mExplicitFunction = "csch(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_COTH:
          mExplicitFunction = "coth(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_ARCSIN:
          mExplicitFunction = "arcsin(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_ARCCOS:
          mExplicitFunction = "arccos(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_ARCTAN:
          mExplicitFunction = "arctan(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_ARCSEC:
          mExplicitFunction = "arcsec(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_ARCCSC:
          mExplicitFunction = "arccsc(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_ARCCOT:
          mExplicitFunction = "arccot(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_ARCSINH:
          mExplicitFunction = "arcsinh(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_ARCCOSH:
          mExplicitFunction = "arccosh(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_ARCTANH:
          mExplicitFunction = "arctanh(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_ARCSECH:
          mExplicitFunction = "arcsech(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_ARCCSCH:
          mExplicitFunction = "arccsch(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_ARCCOTH:
          mExplicitFunction = "arccoth(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_ABS:
          mExplicitFunction = "abs(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_SQRT:
          mExplicitFunction = "sqrt(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        case N_GAUSS:
        case N_BOLTZ:
        case N_RND:
          mExplicitFunction = "(" + mLeft->getExplicitFunctionString(callParameterNames, r)
                              + ")";
          break;
        default:
          mExplicitFunction.empty();
        }
      break;
    default:
      mExplicitFunction.empty();
    }
  return mExplicitFunction;
}
 */

char CNodeK::getType() const
{
  return mType;
}

char CNodeK::getSubtype() const
{
  return mSubtype;
}

CNodeK & CNodeK::getLeft() const
{
  if (!mLeft)
    fatalError(); // Call LeftIsValid first to avoid this!

  return *mLeft;
}

CNodeK & CNodeK::getRight() const
{
  if (!mRight)
    fatalError(); // Call RightIsValid first to avoid this!

  return *mRight;
}

std::string CNodeK::getName() const
{
  return mName;
#ifdef XXXX

  static unsigned C_INT ctr = 0;
  char name[9];

  if (isIdentifier())
    return mName;
  else
    {
      sprintf(name, "%X", ctr++);
      return name;
    }

#endif // XXXX
}

C_FLOAT64 CNodeK::getConstant() const
{
  return mConstant;
}

C_INT32 CNodeK::getIndex() const
{
  return mIndex;
}

void CNodeK::setType(char type)
{
  mType = type;
}

void CNodeK::setSubtype(char subtype)
{
  mSubtype = subtype;
}

void CNodeK::setLeft(CNodeK & left)
{
  mLeft = &left;
}

void CNodeK::setLeft(CNodeK * pleft)
{
  mLeft = pleft;
}

void CNodeK::setRight(CNodeK & right)
{
  mRight = &right;
}

void CNodeK::setRight(CNodeK * pright)
{
  mRight = pright;
}

void CNodeK::setName(const std::string & name)
{
  mName = name;
}

void CNodeK::setConstant(C_FLOAT64 & constant)
{
  mConstant = constant;
}

void CNodeK::setIndex(C_INT32 index)
{
  mIndex = index;
}

void CNodeK::setOldIndex(C_INT32 oldindex)
{
  mOldIndex = oldindex;
}

C_INT16 CNodeK::isLeftValid() const
{
  return (mLeft != NULL);
}

C_INT16 CNodeK::isRightValid() const
{
  return (mRight != NULL);
}

C_INT16 CNodeK::isNumber() const
{
  return (mType == N_NUMBER);
}

C_INT16 CNodeK::isIdentifier() const
{
  switch (mType)
    {
      case N_OBJECT:
      case N_IDENTIFIER:
      case N_SUBSTRATE:
      case N_PRODUCT:
      case N_MODIFIER:
      case N_KCONSTANT:
      case N_VOLUME:
        return true;

      default:
        return false;
    }
}

C_INT16 CNodeK::isOperator() const
{
  return mType == N_OPERATOR;
}

C_INT16 CNodeK::leftPrecedence() const
{
  switch (mType)
    {
      case N_OBJECT:
      case N_NUMBER:
      case N_IDENTIFIER:
      case N_FUNCTION:
        return 5;
    }

  // if we got here then it is an operator
  switch (mSubtype)
    {
      case '+':
      case '-':
        return 1;

      case '*':
      case '/':
        return 3;

      case '(':
        return 6;

      case '^':
        return 5;

      case ')':
      case '%':
        return 0;
    }

  return 0;
}

C_INT16 CNodeK::rightPrecedence() const
{
  switch (mType)
    {
      case N_OBJECT:
      case N_NUMBER:
      case N_IDENTIFIER:
        return 6;

      case N_FUNCTION:
        return 4;
    }

  // if we got here then it is an operator
  switch (mSubtype)
    {
      case '+':
      case '-':
        return 2;

      case '*':
      case '/':
        return 4;

      case ')':
        return 6;

      case '^':
        return 4;

      case '(':
      case '%':
        return 0;
    }

  return 0;
}
