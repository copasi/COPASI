// CNodeK.cpp : classes for function tree
//
/////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdio.h>

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "utilities/utilities.h"
#include "utilities/CCopasiMessage.h"
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

CNodeK::CNodeK(const string & name)
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

C_INT32 CNodeK::save(CWriteConfig & configbuffer) const
  {
    C_INT32 Fail = 0;
#ifdef XXXX

    // the file has already been opened
    // we don't care about exceptions here.
    // They should be caught by the calling function
    // First the Type and subtype
    if ((Fail = configbuffer.setVariable("Node", "node", &mType, &mSubtype)))
      return Fail;

    // leave the Left & Right pointers out
    // value of the constant if one
    if (mType == N_NUMBER)
      {
        if ((Fail = configbuffer.setVariable("Value", "C_FLOAT64", &mConstant)))
          return Fail;
      }
    else if (isIdentifier())
      {
        if ((Fail = configbuffer.setVariable("Index", "C_INT32", &mIndex)))
          return Fail;
        if ((Fail = configbuffer.setVariable("Name", "string", &mName)))
          return Fail;
      }
#endif // XXXX
    return Fail;
  }

C_INT32 CNodeK::saveOld(CWriteConfig & configbuffer) const
  {
    C_INT32 Fail = 0;
    char dummy = N_NOP;

    if (isIdentifier())
      {
        if ((Fail = configbuffer.setVariable("Node", "node", &mSubtype, &dummy)))
          return Fail;
      }
    else
      {
        if ((Fail = configbuffer.setVariable("Node", "node", &mType, &mSubtype)))
          return Fail;
      }
    if (mType == N_NUMBER)
      {
        if ((Fail = configbuffer.setVariable("Value", "C_FLOAT64", &mConstant)))
          return Fail;
      }
    else if (isIdentifier())
      {
        if ((Fail = configbuffer.setVariable("Index", "C_INT32", &mOldIndex)))
          return Fail;
        if ((Fail = configbuffer.setVariable("Name", "string", &mName)))
          return Fail;
      }
    return Fail;
  }

string CNodeK::getExplicitFunctionString(const CCallParameters & callParameterNames, const string &r)
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
      FixSName(* (string *) callParameterNames[mIndex], mExplicitFunction);
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

string CNodeK::getName() const
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

void CNodeK::setName(const string & name)
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
        return TRUE;
      default:
        return FALSE;
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

C_FLOAT64 CNodeK::value(const CCallParameters & callParameters) const
  {
    // if it is a constant or an identifier just return its value
    if (isNumber())
      return mConstant;
    switch (mType)
      {
      case N_OBJECT:
        return 1;
        break;
      case N_IDENTIFIER :
        return * (C_FLOAT64 *) callParameters[mIndex];
        break;
      case N_OPERATOR:
        switch (mSubtype)
          {
          case '+':
            return mLeft->value(callParameters) + mRight->value(callParameters);
          case '-':
            return mLeft->value(callParameters) - mRight->value(callParameters);
          case '*':
            return mLeft->value(callParameters) * mRight->value(callParameters);
          case '/':
            return mLeft->value(callParameters) / mRight->value(callParameters);
          case '^':
            return pow(mLeft->value(callParameters), mRight->value(callParameters));
          default:
            fatalError();   // THROW EXCEPTION
            return 0.0;
          }
        break;
      case N_FUNCTION:
        switch (mSubtype)
          {
          case '+':
            return mLeft->value(callParameters);
          case '-':
            return - mLeft->value(callParameters);
          case N_EXP:
            return exp(mLeft->value(callParameters));
          case N_LOG:
            return log(mLeft->value(callParameters));
          case N_LOG10:
            return log10(mLeft->value(callParameters));
          case N_SIN:
            return sin(mLeft->value(callParameters));
          case N_COS:
            return cos(mLeft->value(callParameters));
          default:
            fatalError();   // THROW EXCEPTION
            return 0.0;
          }
        break;
      default:
        fatalError();   // THROW EXCEPTION
        return 0.0;
      }
    fatalError();   // THROW EXCEPTION
    return 0.0;
  }
