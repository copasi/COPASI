/*****************************************************************************
* PROGRAM NAME: CNodeO.cpp
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Implement the node object in user defined function
*****************************************************************************/

#include <math.h>
#include <iostream>

#include "copasi.h"
#include "CDatum.h"
#include "CNodeO.h"

/**
 * Default constructor
 */
CNodeO::CNodeO()
{
//	mDatumType = 0;
//	mTitle = "";
//	mI = "";
//	mJ = "";
	mDatum = NULL;
}

/**
 * Constructor for operator
 * @param "const char" type
 * @param "const char" subtype
 */
CNodeO::CNodeO(CDatum &datum)
{
//	mDatumType = type;
//	mTitle = title;
//	mI = i_str;
//	mJ = j_str;
	mDatum = &datum;
}

/**
 * Destructor
 */
CNodeO::~CNodeO()
{
#if 0
 // if this is an identifier delete the CDatum
 if( (getType()==N_IDENTIFIER) && mDatum != NULL )
 {
  delete mDatum;
  mDatum = NULL;
 }
#endif
}

/**
 * Delete
 */
void CNodeO::cleanup()
{
}

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

  if (isIdentifier() && getType() != N_IDENTIFIER)
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

	  mDatum = new CDatum;
	  mDatum->load(configbuffer);
    }

	return Fail;


}

/**
 *  Saves the contents of the object to a CWriteConfig object.
 *  (Which usually has a file attached but may also have socket)
 *  @param pconfigbuffer reference to a CWriteConfig object.
 *  @return Fail
 */
C_INT32 CNodeO::save(CWriteConfig & configbuffer) const
{
	C_INT32 Fail = 0;
    char Type, Subtype;
	
	Type = getType();
	Subtype = getSubtype();

	if ((Fail = configbuffer.setVariable("Node", "node", &Type, &Subtype)))
		return Fail;
	// leave the Left & Right pointers out
	// value of the constant if one
	if (Type==N_NUMBER)
    {
		C_FLOAT64 Constant = getConstant();
		if ((Fail = configbuffer.setVariable("Value", "C_FLOAT64", &Constant)))
			return Fail;
    }
	else if (isIdentifier())
    {
		mDatum->save(configbuffer);
    }
	
	return Fail;

}

	
/**
 * Calculates the value of this sub-tree
 */
C_FLOAT64 CNodeO::value(CModel *model) 
{
	char NodeType, NodeSubtype;

	NodeType = getType();
	NodeSubtype = getSubtype();

	// if it is a constant or a variable just return its value
	if(NodeType == N_NUMBER) 
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

			mDatum->compileDatum(model, NULL);
			Type = mDatum->getType();
			switch (Type)
			{
				case 1:
					Value1 = (C_INT16 *)mDatum->getValue();
					Value = (C_FLOAT64) *Value1;
					break;
				case 2:
					Value2 = (C_INT32 *)mDatum->getValue();
					Value = (C_FLOAT64) *Value2;
					break;
				case 3:
					Value3 = (C_FLOAT32 *)mDatum->getValue();
					Value = (C_FLOAT64) *Value3;
					break;
				case 4:
					Value4 = (C_FLOAT64 *)mDatum->getValue();
					Value = (C_FLOAT64) *Value4;
					break;
			}
			return Value;
			break;
        
    case N_OPERATOR:
				switch (NodeSubtype)
				{
					case '+':
						return mLeft->value(model) + mRight->value(model);

					case '-': 
						return mLeft->value(model) - mRight->value(model);

					case '*': 
						return mLeft->value(model) * mRight->value(model);
        
					case '/': 
						return mLeft->value(model) / mRight->value(model);
        
					case '^': 
						return pow(mLeft->value(model), mRight->value(model));
        
					default: 
						fatalError();   // THROW EXCEPTION
						return 0.0;
				}
				break;

    case N_FUNCTION:
				switch (NodeSubtype)
				{
					case '+': 
						return mLeft->value(model);

					case '-': 
						return - mLeft->value(model);

					case N_EXP: 
						return exp(mLeft->value(model));

					case N_LOG: 
						return log(mLeft->value(model));

					case N_LOG10: 
						return log10(mLeft->value(model));

					case N_SIN: 
						return sin(mLeft->value(model));

					case N_COS: 
						return cos(mLeft->value(model));

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


/**
 * Return Datum in each node
 */
CDatum * CNodeO::getDatum()
{
	return mDatum;
}

C_INT16 CNodeO::isLeftValid() const {return (C_INT16) mLeft;}

C_INT16 CNodeO::isRightValid() const {return (C_INT16) mRight;}
