// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionParameter.h,v $
//   $Revision: 1.35 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/03/09 09:54:42 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CFunctionParameter
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CFunctionParameter
#define COPASI_CFunctionParameter

#include <string>
#include <iostream>

#include "utilities/CReadConfig.h"
#include "report/CCopasiContainer.h"

/** @dia:pos 15.1888,24.6765 */
class CFunctionParameter : public CCopasiContainer
  {
  public:
    /**
     * A string representation of the data type
     */
    static const std::string DataTypeName[];

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
     *  The string representation of valid roles of a function parameter
     */
    static const std::string RoleNameXML[];
    static const std::string RoleNameDisplay[];

  public:

    /*
    static const std::string & convertDisplayRoleNameToInternal(const std::string & role);
    */
    static Role xmlRole2Enum(const std::string & role);

    /**
     *  Valid data type for a function parameter
     */
    enum DataType {INT32 = 0, FLOAT64, VINT32, VFLOAT64};

  private:
    /**
     * The key of the function parameter
     */
    std::string mKey;

    /**
     *  The data type of the parameter this may be one of INT16, INT32,
     *  UINT16, UINT32, FLOAT32, FLOAT64, VINT16, VINT32, VUINT16, VUINT32,
     *  VFLOAT32, VFLOAT64
     */
    CFunctionParameter::DataType mType;

    /**
     *  The usage or meaning of the parameter. This has no functional
     *  implication for CFunction but it might be used in derived classes.
     *  Possible usage is SUBSTRATE, PRODUCT, MODIFIER, or PARAMETER
     */
    Role mUsage;

  public:
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
     *  Cleanup
     */
    void cleanup();

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    virtual void load(CReadConfig & configbuffer,
                      CReadConfig::Mode mode = CReadConfig::NEXT);

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

    /**
     * insert operator
     */
    friend std::ostream& operator<<(std::ostream &os, const CFunctionParameter & d);
  };

#endif // COPASI_CFunctionParameter
