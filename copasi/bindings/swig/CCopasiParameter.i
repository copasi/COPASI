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

    %extend
    {
      C_FLOAT64 getDblValue()
      {
        return *self->getValue().pDOUBLE;
      }

      C_FLOAT64 getUDblValue()
      {
        return *self->getValue().pUDOUBLE;
      }

      C_INT32 getIntValue()
      {
        return *self->getValue().pINT;
      }

      unsigned C_INT32 getUIntValue()
      {
        return *self->getValue().pUINT;
      }

      bool getBoolValue()
      {
        return *self->getValue().pBOOL;
      }

      std::vector<CCopasiParameter*> getGroupValue()
      {
        return *self->getValue().pGROUP;
      }

      std::string getStringValue()
      {
        return *self->getValue().pSTRING;
      }

      CRegisteredObjectName getCNValue()
      {
        return *self->getValue().pCN;
      }

      std::string getKeyValue()
      {
        return *self->getValue().pKEY;
      }

      std::string getFileValue()
      {
        return *self->getValue().pFILE;
      }

      void* getVoidValue()
      {
        return self->getValue().pVOID;
      }

      bool setDblValue(const C_FLOAT64& v)
      {
        return self->setValue(v);
      }

      bool setUDblValue(const C_FLOAT64& v)
      {
        return self->setValue(v);
      }

      bool setUIntValue(const unsigned C_INT32& v)
      {
        return self->setValue(v);
      }

      bool setIntValue(const C_INT32& v)
      {
        return self->setValue(v);
      }

      bool setBoolValue(const bool& v)
      {
        return self->setValue(v);
      }

      bool setGroupValue(const std::vector<CCopasiParameter*>& v)
      {
        return self->setValue(v);
      }

      bool setStringValue(const std::string& v)
      {
        return self->setValue(v);
      }

      bool setCNValue(const CRegisteredObjectName& v)
      {
        return self->setValue(v);
      }

      bool setKeyValue(const std::string& v)
      {
        return self->setValue(v);
      }

      bool setFileValue(const std::string& v)
      {
        return self->setValue(v);
      }

    }
};


