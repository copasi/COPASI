%{

#include "utilities/CCopasiParameter.h"

%}


class CCopasiParameter : public CCopasiContainer
{
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
      KEY,
      FILE,
      INVALID
    };

    /**
     * String literals for the GUI to display type names of parameters known
     * to COPASI.
     */
    static const std::string TypeName[];

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
     * Set the value of the parameter
     * @param const unsigned C_INT32 & value
     * @return bool isValidValue
     */
    template <class CType> bool setValue(const CType & value);

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
     * @return CCopasiParameter::Value & Value
     */
    //Value & getValue();

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


};


