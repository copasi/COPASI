/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/Attic/CMethodParameter.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:35:34 $
   End CVS Header */

/**
 *  CParameter class.
 *  This class is used to describe parameters. This class is intended
 *  to be used with integration or optimization methods or reactions.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CParameter
#define COPASI_CParameter

#include <string>

#include "report/CCopasiContainer.h"

class CReadConfig;
class CWriteConfig;

class CParameter: public CCopasiContainer
  {
    // Attributes
  public:
    static const std::string TypeName[];

    enum Type
    {
      DOUBLE = 0,
      INT,
      UINT,
      BOOL
    };

  private:
    /**
     *  key of the model
     */
    std::string mKey;

    /**
     *  The value of the attribute
     */
    C_FLOAT64 mValue;

    /**
     * The type of the parameter
     */
    CParameter::Type mType;

    // Operations

  public:

    /**
     * Default constructor
     * @param "const string &" name (Default = "")
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & objectType (default: "Parameter")
     */
    CParameter(const std::string & name = "NoName",
               const CCopasiContainer * pParent = NULL,
               const std::string & objectType = "Parameter");

    /**
     * Copy constructor
     * @param "const CParameter &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CParameter(const CParameter & src,
               const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor
     * @param const string & name
     * @param const C_FLOAT64 & value
     * @param const CParameter::Type & type
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & objectType (default: "Parameter")
     */
    CParameter(const std::string & name,
               const C_FLOAT64 & value,
               const Type & type,
               const CCopasiContainer * pParent = NULL,
               const std::string & objectType = "Parameter");

    /**
     * Destructor
     */
    ~CParameter();

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
     * @return "const C_FLOAT64 & value
     */
    const C_FLOAT64 & getValue() const;

    virtual const void * getObjectValueAddress() const;

    /**
     * Set the type of the parameter
     * @param const CParameter::Type & type
     */
    void setType(const CParameter::Type & type);

    /**
     * Retrieve the type of the parameter.
     * @return CParameter::Type & type
     */
    const CParameter::Type & getType() const;

    /**
     * Check whether the value corresponds to the type
     * @param const C_FLOAT64 & value
     * @return bool isValidValue
     */
    bool isValidValue(const C_FLOAT64 & value) const;

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
  };

#endif // COPASI_CParameter
