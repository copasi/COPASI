/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiParameter.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/30 17:59:18 $
   End CVS Header */

#ifndef COPASI_CCopasiParameter
#define COPASI_CCopasiParameter

#include <string>

#include "report/CCopasiContainer.h"

class CReadConfig;
class CWriteConfig;

/**
 *  CCopasiParameter class.
 *  This class is used to describe parameters. This class is intended
 *  to be used with integration or optimization methods or reactions.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */
class CCopasiParameter: public CCopasiContainer
  {
    // Attributes
  public:
    static const std::string TypeName[];

    enum Type
    {
      DOUBLE = 0,
      INT,
      UINT,
      BOOL,
      GROUP,
      STRING,
      INVALID = -1
    };

  private:
    /**
     * The key of the parameter.
     */
    std::string mKey;

    /**
     * The type of the parameter
     */
    CCopasiParameter::Type mType;

  protected:
    /**
     *  The size alloactaed for the value of the parameter.
     */
    unsigned C_INT32 mSize;

    /**
     *  A pointer to the value of the parameter.
     */
    void * mpValue;

    // Operations

  private:
    /**
     * Default constructor
     */
    CCopasiParameter();

  public:
    /**
     * Copy constructor
     * @param const CCopasiParameter & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiParameter(const CCopasiParameter & src,
                     const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor
     * @param const string & name
     * @param const CCopasiParameter::Type & type
     * @param const void * pValue (default: NULL)
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & objectType (default: "Parameter")
     */
    CCopasiParameter(const std::string & name,
                     const Type & type,
                     const void * pValue = NULL,
                     const CCopasiContainer * pParent = NULL,
                     const std::string & objectType = "Parameter");

    /**
     * Destructor
     */
    virtual ~CCopasiParameter();

    /**
     * Return the key of this model
     * @return string key
     */
    std::string getKey() const;

    /**
     * Set name of the parameter
     * @param const string & name
     */
    bool setName(const std::string & name);

    /**
     * Retrieve the name of the parameter
     * @return const string & mName
     */
    const std::string & getName() const;

    /**
     * Set the value of the parameter
     * @param const unsigned C_INT32 & value
     * @return bool is ValidValue
     */
    template <class CType> bool setValue(const CType & value);

    /**
     * Retrieve the private value of the parameter.
     * @return const void * pValue
     */
    const void * getValue() const;

    /**
     * Retrieve the private value of the parameter.
     * @return void * pValue
     */
    void * getValue();

    /**
     * Retrieve the type of the parameter.
     * @return CCopasiParameter::Type & type
     */
    const CCopasiParameter::Type & getType() const;

    /**
     * Check whether the value corresponds to the type
     * @param const CType & value
     * @return bool isValidValue
     */
    template <class CType> bool isValidValue(const CType & value) const;

  private:
    void * createValue(const void * pValue = NULL);
    void deleteValue();
  };

template <class CType>
bool CCopasiParameter::isValidValue(const CType & C_UNUSED(value)) const
  {
    if (mSize != sizeof(CType)) return false;
    return true;
  }

template <class CType>
bool CCopasiParameter::setValue(const CType & value)
{
  if (!isValidValue(value)) return false;

  * (CType *) mpValue = value;
  return true;
}

#endif // COPASI_CCopasiParameter
