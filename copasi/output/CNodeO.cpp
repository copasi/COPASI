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
CNodeO::CNodeO() : CNodeK() {}

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
      mDatum.load(configbuffer);
    }

  return Fail;
}


const CDatum & CNodeO::getDatum() const {return mDatum;}

	
