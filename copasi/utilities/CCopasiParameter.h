/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiParameter.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/21 20:32:46 $
   End CVS Header */

/**
 *  CCopasiParameter class.
 *  This class is used to describe parameters. This class is intended
 *  to be used with integration or optimization methods or reactions.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CCopasiParameter
#define COPASI_CCopasiParameter

#include <string>

#include "report/CCopasiContainer.h"

class CReadConfig;
class CWriteConfig;

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
      GROUP
    };

  private:
    /**
     *  key of the parameter
     */
    std::string mKey;

    /**
     * The type of the parameter
     */
    CCopasiParameter::Type mType;

    /**
     *  A pointer to the value of the attribute
     */
    void * mpValue;

    // Operations

  public:

    /**
     * Default constructor
     * @param "const string &" name (Default = "")
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & objectType (default: "Parameter")
     */
    CCopasiParameter(const std::string & name = "NoName",
                     const CCopasiContainer * pParent = NULL,
                     const std::string & objectType = "Parameter");

    /**
     * Copy constructor
     * @param "const CCopasiParameter &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiParameter(const CCopasiParameter & src,
                     const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor
     * @param const string & name
     * @param const void * pValue
     * @param const CCopasiParameter::Type & type
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & objectType (default: "Parameter")
     */
    CCopasiParameter(const std::string & name,
                     const void * pValue,
                     const Type & type,
                     const CCopasiContainer * pParent = NULL,
                     const std::string & objectType = "Parameter");

    /**
     * Destructor
     */
    ~CCopasiParameter();

    /**
     * Return the key of this model
     * @return string key
     */
    std::string getKey() const;

    /**
     * Set name of the parameter
     * @param "const string &" name
     */
    bool setName(const std::string & name);

    /**
     * Retrieve the name of the parameter
     * @return "const string &" mName
     */
    const std::string & getName() const;

    /**
     * Set the value of the parameter
     * @param "const C_FLOAT64 &" value
     * @return bool is ValidValue
     */
    bool setValue(const C_FLOAT64 & value);

    /**
     * Set the value of the parameter
     * @param "const C_INT32 &" value
     * @return bool is ValidValue
     */
    bool setValue(const C_INT32 & value);

    /**
     * Set the value of the parameter
     * @param "const bool &" value
     * @return bool is ValidValue
     */
    bool setValue(const bool & value);

    /**
     * Set the value of the parameter
     * @param "const unsigned C_INT32 &" value
     * @return bool is ValidValue
     */
    bool setValue(const unsigned C_INT32 & value);

    /**
     * Retrieve the private value of the parameter.
     * @return const void * pValue
     */
    const void * getValue() const;

    /**
     * Set the type of the parameter
     * @param const CCopasiParameter::Type & type
     */
    void setType(const CCopasiParameter::Type & type);

    /**
     * Retrieve the type of the parameter.
     * @return CCopasiParameter::Type & type
     */
    const CCopasiParameter::Type & getType() const;

    /**
     * Check whether the value corresponds to the type
     * @param (const void *pValue
     * @return bool isValidValue
     */
    bool isValidValue(const void *pValue) const;

    /**
     * Load a list of parameters
     * @param "CReadConfig &" configBuffer
     */
    void load(CReadConfig & configBuffer);

    /**
     * Save a list of parameters
     * @param "CWriteConfig &" configBuffer
     */
    void save(CWriteConfig & configBuffer) const;

    /**
     * Clean up
     */
    void cleanup();

  private:
    void * createValue(const void * pValue = NULL);
    void deleteValue();
  };

#endif // COPASI_CCopasiParameter
