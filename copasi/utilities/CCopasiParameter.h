/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiParameter.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/07 16:55:41 $
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
    enum Type
    {
      DOUBLE = 0,
      UDOUBLE,
      INT,
      UINT,
      BOOL,
      GROUP,
      STRING,
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
    template <class CType> bool setValue(const CType & value)
    {
      if (!isValidValue(value)) return false;

      * (CType *) mpValue = value;
      return true;
    }

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
     * @param const CType & value
     * @return bool isValidValue
     */
    template <class CType>
    bool isValidValue(const CType & C_UNUSED(value)) const
      {
        if (mSize != sizeof(CType)) return false;

        return true;
      }

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
  };

#endif // COPASI_CCopasiParameter
