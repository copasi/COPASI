/**
 *  File name: COptAlgorithmParameter.cpp
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the implementation (.cpp file) of the 
 *           COptAlgorithmParameter class. 
 *           It contains an optimization algorithm parameter with its name
 *           and value
 */
#include <math.h>
#include "COptAlgorithmParameter.h"

   
//Default constructor
COptAlgorithmParameter::COptAlgorithmParameter()
{
  mName = "NameUnkown";
  mValue = 0.0;
}

// Destructor
COptAlgorithmParameter::~COptAlgorithmParameter()
{ }

// copy constructor
COptAlgorithmParameter::COptAlgorithmParameter(const COptAlgorithmParameter& source)
{
  mName = source.mName;
  mValue = source.mValue;
}

// Object assignment overloading,
COptAlgorithmParameter & COptAlgorithmParameter::operator = (const COptAlgorithmParameter& source)
{
  if (this != &source)
    {
      mName = source.mName;
      mValue = source.mValue;
    }
    
  return *this;
}


//set name
//param: aName a string to be set as mName
void COptAlgorithmParameter:: setName(string aName)
{
  mName = aName;
}

//get the private member mName
//return mName
string COptAlgorithmParameter::getName()
{
  return mName;
}

//set the value
//param aValue the double to be set as the private member mValue
void COptAlgorithmParameter::setValue(double aValue)
{
  mValue = aValue;
}


// get the private member mValue
//return the mValue, the private member
double COptAlgorithmParameter::getValue()
{
  return mValue;
}
