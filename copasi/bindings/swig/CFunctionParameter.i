// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "function/CFunctionParameter.h"

%}

class CFunctionParameter : public CCopasiContainer
{
  public:
    enum Role
    {
      SUBSTRATE = 0,
      PRODUCT,
      MODIFIER,
      PARAMETER,
      VOLUME,
      TIME,
      VARIABLE
    };

    /**
     *  Valid data type for a function parameter
     */
    enum DataType {INT32 = 0, FLOAT64, VINT32, VFLOAT64};

    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFunctionParameter(const std::string & name = "NoName",
                       const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CFunctionParameter" & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFunctionParameter(const CFunctionParameter & src,
                       const CCopasiContainer * pParent = NULL);

    /**
     * Specified constuctor, sets all member values at once
     * @param "const string &" name
     * @param "const CFunctionParameter::DataType &" type
     * @param "const string &" usage
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFunctionParameter(const std::string & name,
                       const DataType & type,
                       Role usage,
                       const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    virtual ~CFunctionParameter();

    /**
     *  Retrieves the key of the function parameter.
     *  @return std::string name
     */
    virtual const std::string & getKey() const;

    /**
     *  Retrieves the data type of the parameter
     *  @return "const CFunctionParameter::DataType" & type
     */
    const CFunctionParameter::DataType & getType() const;

    /**
     *  Sets the data type of the parameter
     *  @param "const CFunctionParameter::DataType" & type
     */
    void setType(const CFunctionParameter::DataType & type);

    /**
     *  Retrieves the usage of the parameter
     *  @return "const string" & usage
     */
    Role getUsage() const;

    /**
     *  Sets the usage of the parameter
     *  @param "const string" & usage
     */
    void setUsage(Role usage);

};


