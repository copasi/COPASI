// CNodeK.cpp : classes for function tree
//
/////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdio.h>

#include "copasi.h"
#include "utilities/CCopasiMessage.h"
#include "CNodeK.h"

CNodeK::CNodeK()
{
  mType     = N_NOP;
  mSubtype  = N_NOP;
  mLeft     = NULL;
  mRight    = NULL;
  mConstant = 0.0;
  mIndex    = -1;
}

CNodeK::CNodeK(char type, char subtype)
{
  mType     = type;
  mSubtype  = subtype;
  mLeft     = NULL;
  mRight    = NULL;
  mConstant = 0.0;
  mIndex    = -1;
}

CNodeK::CNodeK(const string & name)
{
  mType     = N_IDENTIFIER;
  mSubtype  = N_NOP;
  mLeft     = NULL;
  mRight    = NULL;
  mConstant = 0.0;
  mName     = name;
  mIndex    = -1;
}

CNodeK::CNodeK(C_FLOAT64 constant)
{
  mType     = N_NUMBER;
  mSubtype  = N_NOP;
  mLeft     = NULL;
  mRight    = NULL;
  mConstant = constant;
  mIndex    = -1;
}

void CNodeK::cleanup() {}
    
CNodeK::~CNodeK() {}

C_INT32 CNodeK::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;
    
  if ((Fail = configbuffer.getVariable("Node", "node", &mType, &mSubtype,
				       CReadConfig::SEARCH)))
    return Fail;
    
  if (isIdentifier() && mType != N_IDENTIFIER)
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
    
  // the file has already been opened
  // we don't care about exceptions here.
  // They should be caught by the calling function
  // First the Type and subtype
  if ((Fail = configbuffer.setVariable("Node", "node", &mType, &mSubtype)))
    return Fail;
    
  // leave the Left & Right pointers out
  // value of the constant if one
  if (mType==N_NUMBER)
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
  return Fail;
}

char CNodeK::getType() const {return mType;}

char CNodeK::getSubtype() const {return mSubtype;}

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
  static unsigned C_INT ctr = 0;
  char name[9];
    
  if (isIdentifier()) return mName;
  else 
    {
      sprintf(name, "%X", ctr++);
      return name;
    }
}

C_FLOAT64 CNodeK::getConstant() const {return mConstant;}

C_INT32 CNodeK::getIndex() const {return mIndex;}

void CNodeK::setType(char type) {mType = type;}

void CNodeK::setSubtype(char subtype) {mSubtype = subtype;}

void CNodeK::setLeft(CNodeK & left) {mLeft = &left;}

void CNodeK::setLeft(CNodeK * pleft) {mLeft = pleft;}

void CNodeK::setRight(CNodeK & right) {mRight = &right;}

void CNodeK::setRight(CNodeK * pright) {mRight = pright;}

void CNodeK::setName(const string & name) {mName = name;}

void CNodeK::setConstant(C_FLOAT64 & constant) {mConstant = constant;}

void CNodeK::setIndex(C_INT32 index) {mIndex = index;}

C_INT16 CNodeK::isLeftValid() const {return (C_INT16) mLeft;}

C_INT16 CNodeK::isRightValid() const {return (C_INT16) mRight;}

C_INT16 CNodeK::isNumber() const {return mType == N_NUMBER;}

C_INT16 CNodeK::isIdentifier() const
{
  switch (mType)
    {
    case N_IDENTIFIER:
    case N_SUBSTRATE:
    case N_PRODUCT:
    case N_MODIFIER:
    case N_KCONSTANT: return TRUE;
    default: return FALSE;
    }
}

C_INT16 CNodeK::isOperator() const {return mType == N_OPERATOR;}

C_INT16 CNodeK::leftPrecedence() const
{
  switch (mType)
    {
    case N_NUMBER:
    case N_IDENTIFIER:
    case N_FUNCTION:   return 5;
    }
  // if we got here then it is an operator
  switch (mSubtype)
    {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 3;
    case '(': return 6;
    case '^': return 5;
    case ')':
    case '%': return 0;
    }
  return 0;
}

C_INT16 CNodeK::rightPrecedence() const
{
  switch (mType)
    {
    case N_NUMBER:
    case N_IDENTIFIER: return 6;
    case N_FUNCTION:   return 4;
    }

  // if we got here then it is an operator
  switch (mSubtype)
    {
    case '+':
    case '-': return 2;
    case '*':
    case '/': return 4;
    case ')': return 6;
    case '^': return 4;
    case '(':
    case '%': return 0;
    }
  return 0;
}

C_FLOAT64 CNodeK::value(vector < void * > & identifiers) const
{
  // if it is a constant or an identifier just return its value
  if (isNumber()) return mConstant;

  switch (mType)
    {
    case N_IDENTIFIER :
      return  *(C_FLOAT64 *)identifiers[mIndex];
      break;
        
    case N_OPERATOR:
      switch (mSubtype)
	{
        case '+':
	  return mLeft->value(identifiers) + mRight->value(identifiers);

        case '-': 
	  return mLeft->value(identifiers) - mRight->value(identifiers);

        case '*': 
	  return mLeft->value(identifiers) * mRight->value(identifiers);
        
        case '/': 
	  return mLeft->value(identifiers) / mRight->value(identifiers);
        
        case '^': 
	  return pow(mLeft->value(identifiers), mRight->value(identifiers));
        
        default: 
	  fatalError();   // THROW EXCEPTION
	  return 0.0;
	}
      break;

    case N_FUNCTION:
      switch (mSubtype)
	{
        case '+': 
	  return mLeft->value(identifiers);

        case '-': 
	  return - mLeft->value(identifiers);

        case N_EXP: 
	  return exp(mLeft->value(identifiers));

        case N_LOG: 
	  return log(mLeft->value(identifiers));

        case N_LOG10: 
	  return log10(mLeft->value(identifiers));

        case N_SIN: 
	  return sin(mLeft->value(identifiers));

        case N_COS: 
	  return cos(mLeft->value(identifiers));

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
