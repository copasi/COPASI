// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/core/CDataContainer.h"
#include "copasi/utilities/CReadConfig.h"

/** @dia:pos 15.1888,24.6765 */
class CFunctionParameter : public CDataContainer
{
public:
  enum struct Role
  {
    SUBSTRATE,
    PRODUCT,
    MODIFIER,
    PARAMETER,
    VOLUME,
    TIME,
    VARIABLE,
    TEMPORARY,
    __SIZE
  };

  /**
   *  The string representation of valid roles of a function parameter
   */
  static const CEnumAnnotation< std::string, Role > RoleNameXML;
  static const CEnumAnnotation< std::string, Role > RoleNameDisplay;

  /**
   *  Valid data type for a function parameter
   */
  enum struct DataType
  {
    INT32,
    FLOAT64,
    VINT32,
    VFLOAT64,
    __SIZE
  };

  static const CEnumAnnotation< std::string, DataType > DataTypeName;

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

  /**
   * Specifies whether the parameter is used in the function
   */
  bool mIsUsed;

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CDataObject * CFunctionParameter
   */
  static CFunctionParameter * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CFunctionParameter(const std::string & name = "NoName",
                     const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param "const CFunctionParameter" & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CFunctionParameter(const CFunctionParameter & src,
                     const CDataContainer * pParent);

  /**
   * Specified constructor, sets all member values at once
   * @param "const string &" name
   * @param "const CFunctionParameter::DataType &" type
   * @param "const string &" usage
   * @param const CDataContainer * pParent (default: NULL)
   */
  CFunctionParameter(const std::string & name,
                     const DataType & type,
                     Role usage,
                     const CDataContainer * pParent = NO_PARENT);

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
   * Set whether the parameter is used within a function
   * @param const bool & isUsed
   */
  void setIsUsed(const bool & isUsed);

  /**
   * Retrieve whether the parameter is used within a function
   * @return const bool & isUsed
   */
  const bool & isUsed() const;

  /**
   * insert operator
   */
  friend std::ostream& operator<<(std::ostream &os, const CFunctionParameter & d);
};

#endif // COPASI_CFunctionParameter
