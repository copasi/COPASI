/**
 *  CMethodParameterList class.
 *  This class is used to describe a list method paramters. This class is 
 *  intended to be used with integration or optimization methods.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#include <string>

#include "copasi.h"
#include "CMethodParameterList.h"
#include "CMethodParameter.h"

/**
 * Default constructor
 */
CMethodParameterList::CMethodParameterList():
    CCopasiVectorNS <CMethodParameter> (),
    mName("No Name"),
    mType("No Type")
{}

/**
 * Copy constructor
 * @param "const CMethodParameter &" src
 */
CMethodParameterList::CMethodParameterList(const CMethodParameterList & src):
    CCopasiVectorNS <CMethodParameter> (src),
    mName(src.mName),
    mType(src.mType)
{}

/**
 * Destructor
 */
CMethodParameterList::~CMethodParameterList() {cleanup(); }

/**
 * Get the size of the parameter list
 * @return "unsigned C_INT32" size
 */
unsigned C_INT32 CMethodParameterList::size() const
  {
    return CCopasiVector<CMethodParameter>::size();
  }

/**
 * Retrieve the name of the method
 * @return " const string &" name
 */
const string & CMethodParameterList::getName() const { return mName; }

/**
 * Set the name of the method
 * @param "const string &" name
 */
void CMethodParameterList::setName(const string & name) {mName = name; }

/**
 * Retrieve the type of the method
 * @return " const string &" type
 */
const string & CMethodParameterList::getType() const { return mType; }

/**
 * Set the type of the method
 * @param "const string &" type
 */
void CMethodParameterList::setType(const string & type) {mType = type; }

/**
 * Retrieve the name of the indexed parameter
 * @param "const unsigned C_INT32 &" index
 * @return "const string &" mName
 */
const string &
CMethodParameterList::getName(const unsigned C_INT32 & index) const
  {
    return (*(CCopasiVector<CMethodParameter>*)this)[index]->getName();
  }

/**
 * Set the value of the indexed parameter
 * @param "const unsigned C_INT32 &" index
 * @param "const double &" value
 */
void CMethodParameterList::setValue(const unsigned C_INT32 & index,
                                    const double & value)
{
  (*(CCopasiVector<CMethodParameter>*)this)[index]->setValue(value);
}

/**
 * Retrieve the value of the indexed parameter.
 * @param "const unsigned C_INT32 &" index
 * @return "const double & value
 */
const double &
CMethodParameterList::getValue(const unsigned C_INT32 & index) const
  {
    return (*(CCopasiVector<CMethodParameter>*)this)[index]->getValue();
  }

/**
 * Add a parameter to the list
 */

void CMethodParameterList::add
  (const CMethodParameter & parameter)
  {
    CCopasiVector<CMethodParameter>::add
      (parameter);
  }

/**
 * Load a list of parameters
 * @param "CReadConfig &" configBuffer
 */
void CMethodParameterList::load(CReadConfig & configBuffer)
{
  configBuffer.getVariable("MethodParameterListName", "string", &mName);
  configBuffer.getVariable("MethodParameterListType", "string", &mType);

  C_INT32 Size = 0;
  configBuffer.getVariable("MethodParameterListSize", "C_INT32", &Size);

  CCopasiVectorNS<CMethodParameter>::load(configBuffer, Size);
}

/**
 * Save a list of parameters
 * @param "CWriteConfig &" configBuffer
 */
void CMethodParameterList::save(CWriteConfig & configBuffer)
{
  configBuffer.setVariable("MethodParameterListName", "string", &mName);
  configBuffer.setVariable("MethodParameterListType", "string", &mType);

  C_INT32 Size = size();
  configBuffer.setVariable("MethodParameterListSize", "C_INT32", &Size);

  CCopasiVectorNS<CMethodParameter>::save(configBuffer);
}
