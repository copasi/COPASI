/*****************************************************************************
 * PROGRAM NAME: CNodeO.cpp
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: Implement the node object in user defined function
 *****************************************************************************/

#include <math.h>
#include <iostream>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CDatum.h"
#include "CNodeO.h"
#include "utilities/CGlobals.h"

/**
 * Default constructor
 */
CNodeO::CNodeO() : CNodeK() {}

CNodeO::CNodeO(char type, char subtype)
{
  CONSTRUCTOR_TRACE;
  setType(type);
  setSubtype(subtype);
  mLeft = NULL;
  mRight = NULL;
  //setConstant(0.0);
  setIndex(-1);
}

CNodeO::CNodeO(const std::string & name)
{
  CONSTRUCTOR_TRACE;
  setType(N_IDENTIFIER);
  setSubtype(N_NOP);
  mLeft = NULL;
  mRight = NULL;
  //setConstant(0);
  setName(name);
  setIndex(-1);
}

CNodeO::CNodeO(C_FLOAT64 constant)
{
  CONSTRUCTOR_TRACE;
  setType(N_NUMBER);
  setSubtype(N_NOP);
  mLeft = NULL;
  mRight = NULL;
  setConstant(constant);
  setIndex(-1);
}

/**
 * Constructor for operator
 * @param "const char" type
 * @param "const char" subtype
 */

/**
 * Destructor
 */
CNodeO::~CNodeO() {}

/**
 *  Loads an object with data coming from a CReadConfig object.
 *  (CReadConfig object reads an input stream)
 *  @param pconfigbuffer reference to a CReadConfig object.
 *  @return Fail
 */
C_INT32 CNodeO::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;
  char Type, Subtype;
  C_FLOAT64 Constant;

  if ((Fail = configbuffer.getVariable("Node", "node", &Type, &Subtype,
                                       CReadConfig::SEARCH)))
    return Fail;

  setType(Type);
  setSubtype(Subtype);

  /* This COPASI treats all these as identifiers */
  if (Type == N_SUBSTRATE ||
      Type == N_PRODUCT ||
      Type == N_MODIFIER ||
      Type == N_KCONSTANT)
    {
      setSubtype(getType());
      setType(N_IDENTIFIER);
    }

  // leave the Left & Right pointers out
  // value of the constant if one
  if (getType() == N_NUMBER)
    {
      if ((Fail = configbuffer.getVariable("Value", "C_FLOAT64", &Constant)))
        return Fail;
      setConstant(Constant);
    }
  else if (getType() == N_IDENTIFIER)
    {
      mDatum.load(configbuffer);
    }

  return Fail;
}
const CDatum & CNodeO::getDatum() const {return mDatum;}

/**
 * Calculates the value of this sub-tree
 */
C_FLOAT64 CNodeO::value()
{
  char NodeType, NodeSubtype;

  NodeType = getType();
  NodeSubtype = getSubtype();

  // if it is a constant or a variable just return its value
  if (NodeType == N_NUMBER)
    return getConstant();

  switch (NodeType)
    {
    case N_IDENTIFIER :
      C_INT32 Type;
      C_INT16 *Value1;
      C_INT32 *Value2;
      C_FLOAT32 *Value3;
      C_FLOAT64 *Value4;
      C_FLOAT64 Value;

      mDatum.compileDatum(Copasi->Model, NULL, NULL);
      Type = mDatum.getType();
      switch (Type)
        {
        case 1:
          Value1 = (C_INT16 *)mDatum.getValue();
          Value = (C_FLOAT64) * Value1;
          break;
        case 2:
          Value2 = (C_INT32 *)mDatum.getValue();
          Value = (C_FLOAT64) * Value2;
          break;
        case 3:
          Value3 = (C_FLOAT32 *)mDatum.getValue();
          Value = (C_FLOAT64) * Value3;
          break;
        case 4:
          Value4 = (C_FLOAT64 *)mDatum.getValue();
          Value = (C_FLOAT64) * Value4;
          break;
        }
      return Value;
      break;

    case N_OPERATOR:
      switch (NodeSubtype)
        {
        case '+':
          return mLeft->value() + mRight->value();

        case '-':
          return mLeft->value() - mRight->value();

        case '*':
          return mLeft->value() * mRight->value();

        case '/':
          return mLeft->value() / mRight->value();

        case '^':
          return pow(mLeft->value(), mRight->value());

        default:
          fatalError();   // THROW EXCEPTION
          return 0.0;
        }
      break;

    case N_FUNCTION:
      switch (NodeSubtype)
        {
        case '+':
          return mLeft->value();

        case '-':
          return - mLeft->value();

        case N_EXP:
          return exp(mLeft->value());

        case N_LOG:
          return log(mLeft->value());

        case N_LOG10:
          return log10(mLeft->value());

        case N_SIN:
          return sin(mLeft->value());

        case N_COS:
          return cos(mLeft->value());

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
C_INT16 CNodeO::isLeftValid() const {return (mLeft != NULL);}
C_INT16 CNodeO::isRightValid() const {return (mRight != NULL);}

/**
 * Retrieving mLeft the left branch of a node
 * @return CNodeO
 */
CNodeO & CNodeO::getLeft() const
{
  if (!mLeft)
  fatalError(); // Call LeftIsValid first to avoid this!
  return *mLeft;
}

/**
 * Retrieving mRight the left branch of a node
 * @return CNodeO
 */
CNodeO & CNodeO::getRight() const
  {
    if (!mRight)
    fatalError(); // Call RightIsValid first to avoid this!
    return *mRight;
  }

  /**
   * Setting mLeft the pointer to the left branch
   * @param CNodeO &left
   */
  void CNodeO::setLeft(CNodeO & left)
    {
      mLeft = &left;
    }

/**
 * Setting mLeft the pointer to the left branch
 * @param CNodeO *pleft
 */
void CNodeO::setLeft(CNodeO * pleft)
{
  mLeft = pleft;
}

/**
 * Setting mRight the pointer to the right branch
 * @param CNodeO &right
 */
void CNodeO::setRight(CNodeO & right)
{
  mRight = &right;
}

/**
 * Setting mRight the pointer to the right branch
 * @param CNodeO *pright
 */
void CNodeO::setRight(CNodeO * pright)
{
  mRight = pright;
}
