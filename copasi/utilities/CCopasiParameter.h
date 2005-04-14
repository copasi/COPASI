/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiParameter.h,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/04/14 10:51:28 $
   End CVS Header */

#ifndef COPASI_CCopasiParameter
#define COPASI_CCopasiParameter

#include <string>
#include <vector>

#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"

class CCopasiParameterGroup;

class CReadConfig;
//class CWriteConfig;

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
    enum Type
    {
      DOUBLE = 0,
      UDOUBLE,
      INT,
      UINT,
      BOOL,
      GROUP,
      STRING,
      CN,
      INVALID
    };

    /**
     * String literals for the GUI to display type names of parameters known
     * to COPASI.
     */
    static const std::string TypeName[];

    /**
     * XML type names of parameters known to COPASI.
     */
    static const char* XMLType[];

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
    virtual const std::string & getKey() const;

    /**
     * Set name of the parameter
     * @param const string & name
     */ 
    //bool setName(const std::string & name);

    /**
     * Retrieve the name of the parameter
     * @return const string & mName
     */ 
    //const std::string & getName() const;

    /**
     * Set the value of the parameter
     * @param const unsigned C_INT32 & value
     * @return bool isValidValue
     */
    template <class CType> bool setValue(const CType & value)
    {
      if (!isValidValue(value)) return false;

      * (CType *) mpValue = value;
      return true;
    }

    /**
     * Set the value of the parameter when the origin is a parameter group.
     * This function is currently not implemented and creates a fatalError
     * when called.
     * @param const CCopasiParameter::parameterGroup& value
     * @return bool false
     */
    bool setValue(const std::vector< CCopasiParameter * > & value);

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
     * @param const C_FLOAT64 & value
     * @return bool isValidValue
     */
    bool isValidValue(const C_FLOAT64 & value) const;

    /**
     * Check whether the value corresponds to the type
     * @param const C_INT32 & value
     * @return bool isValidValue
     */
    bool isValidValue(const C_INT32 & value) const;

    /**
     * Check whether the value corresponds to the type
     * @param const unsigend C_INT32 & value
     * @return bool isValidValue
     */
    bool isValidValue(const unsigned C_INT32 & value) const;

    /**
     * Check whether the value corresponds to the type
     * @param const bool & value
     * @return bool isValidValue
     */
    bool isValidValue(const bool & value) const;

    /**
     * Check whether the value corresponds to the type
     * @param const std::string & value
     * @return bool isValidValue
     */
    bool isValidValue(const std::string & value) const;

    /**
     * Check whether the value corresponds to the type
     * @param const CRegisteredObjectName & value
     * @return bool isValidValue
     */
    bool isValidValue(const CCopasiObjectName & value) const;

    /**
     * Check whether the value corresponds to the type
     * @param const CCopasiParameterGroup::parameterGroup & value
     * @return bool isValidValue
     */
    bool isValidValue(const std::vector< CCopasiParameter * > & value) const;

    virtual void * getReference() const;

  private:
    /**
     * Create or copy the value
     * @param const void * pValue = NULL
     * @return void * pValue
     */
    void * createValue(const void * pValue = NULL);

    /**
     * Delete the value
     */
    void deleteValue();

    /**
     * Output stream operator
     * @param ostream & os
     * @param const CCopasiParameter & A
     * @return ostream & os
     */
    friend std::ostream & operator << (std::ostream & os, const CCopasiParameter & A)
    {
      os << A.getObjectName() << ": " << A.mType << " 0x" << A.mpValue << std::endl;

      return os;
    }
  };

#endif // COPASI_CCopasiParameter
