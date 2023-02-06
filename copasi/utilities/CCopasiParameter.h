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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CCopasiParameter
#define COPASI_CCopasiParameter

#include <string>
#include <vector>

#include "copasi/copasi.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/core/CFlags.h"

class CCopasiParameterGroup;

class CReadConfig;

/**
 *  CCopasiParameter class.
 *  This class is used to describe parameters. This class is intended
 *  to be used with integration or optimization methods or reactions.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */
class CCopasiParameter: public CDataContainer
{

  // Attributes
public:
  enum struct Type
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
    EXPRESSION,
    INVALID,
    __SIZE
  };

  enum struct eUserInterfaceFlag
  {
    editable,
    basic,
    unsupported,
    __SIZE
  };

  typedef CFlags< eUserInterfaceFlag > UserInterfaceFlag;

  /**
   * String literals for the GUI to display type names of parameters known
   * to COPASI.
   */
  static const CEnumAnnotation< std::string, Type > TypeName;

  /**
   * XML type names of parameters known to COPASI.
   */
  static const CEnumAnnotation< std::string, Type > XMLType;

  static void allocateValue(const Type & type, void *& pValue);
  static void assignValue(const Type & type, void *& pValue, const void * pNewValue);
  static void deleteValue(const Type & type, void *& pValue);
  static void allocateValidValues(const Type & type, void *& pValidValues);
  static void deleteValidValues(const Type & type, void *& pValidValues);

protected:
  /**
   * The key of the parameter.
   */
  std::string mKey;

private:
  /**CCopasiParameter
   * The type of the parameter
   */
  CCopasiParameter::Type mType;

protected:
  /**
   *  A pointer to the value of the parameter.
   */
  void * mpValue;

  /**
   * A pointer to the object reference for  the value
   */
  mutable CDataObject * mpValueReference;

  /**
   * A pointer to the valid values;
   */
  void * mpValidValues;

  void * mpDefault;

  // Operations
  CCopasiParameter(const CCopasiParameter & src);

  UserInterfaceFlag mUserInterfaceFlag;

private:
  /**
   * Default constructor
   */
  CCopasiParameter();

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CCopasiParameter * pDataObject
   */
  static CCopasiParameter * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const override;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes) override;

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & type,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const override;

  /**
   * Copy constructor
   * @param const CCopasiParameter & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CCopasiParameter(const CCopasiParameter & src,
                   const CDataContainer * pParent);

  /**
   * Specific constructor
   * @param const string & name
   * @param const CCopasiParameter::Type & type
   * @param const void * pValue (default: NULL)
   * @param const CDataContainer * pParent (default: NULL)
   * @param const std::string & objectType (default: "Parameter")
   */
  CCopasiParameter(const std::string & name,
                   const Type & type,
                   const void * pValue = NULL,
                   const CDataContainer * pParent = NO_PARENT,
                   const std::string & objectType = "Parameter");

  /**
   * Destructor
   */
  virtual ~CCopasiParameter();

  virtual bool setObjectParent(const CDataContainer * pParent) override;

  /**
   * Assignment operator
   * @param const CCopasiParameter & rhs
   * @return CCopasiParameter & lhs
   */
  CCopasiParameter & operator = (const CCopasiParameter & rhs);

  /**
   * Return the key of this model
   * @return string key
   */
  virtual const std::string & getKey() const override;

  /**
   * Set the value of the parameter
   * @param const const CType & value
   * @return bool isValidValue
   */
  template <class CType> bool setValue(const CType & value)
  {
    if (!isValidValue(value)) return false;

    *static_cast< CType * >(mpValue) = value;
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

  template < class CType > const CType & getValue() const
  {
    return * static_cast< const CType * >(mpValue);
  }

  template < class CType > CType & getValue()
  {
    return * static_cast< CType * >(mpValue);
  }

  /**
   * Set the value of the parameter
   * @param const const CType & defaultValue
   * @return bool isValidValue
   */
  template <class CType> bool setDefault(const CType & defaultValue)
  {
    if (!isValidValue(defaultValue)) return false;

    assignDefault(&defaultValue);
    return true;
  }

  /**
   * Set the value of the parameter when the origin is a parameter group.
   * This function is currently not implemented and creates a fatalError
   * when called.
   * @param const CCopasiParameter::parameterGroup& defaultValue
   * @return bool false
   */
  bool setDefault(const std::vector< CCopasiParameter * > & defaultValue);

  template < class CType > const CType & getDefault() const
  {
    return * static_cast< const CType * >(mpDefault);
  }

  /**
   * Retrieve the object which represents the value of the parameter
   * @return CDataObject * pValueReference
   */
  CDataObject * getValueReference() const;

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
   * @param const unsigned C_INT32 & value
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
   * @param const CRegisteredCommonName & value
   * @return bool isValidValue
   */
  bool isValidValue(const CCommonName & value) const;

  /**
   * Check whether the value corresponds to the type
   * @param const CCopasiParameterGroup::parameterGroup & value
   * @return bool isValidValue
   */
  bool isValidValue(const std::vector< CCopasiParameter * > & value) const;

  /**
   * All other value types are not supported
   */
  template < class CType > bool isValidValue(const CType & /* value */) const
  {
    return false;
  }

  /**
   * Check whether valid values are specified
   * @return bool haveValidValues
   */
  bool hasValidValues() const;

  /**
   * Set the valid values
   * @param const std::vector< std::pair < CType, CType > > & validValues
   * @return success
   */
  template < class CType > bool setValidValues(const std::vector< std::pair < CType, CType > > & validValues)
  {
    if (!isValidValue(CType())) return false;

    assignValidValues(&validValues);
    return true;
  }

  template < class CType, class Enum> bool setValidValues(const CEnumAnnotation< CType, Enum> & validValues)
  {
    if (!isValidValue(CType())) return false;

    std::vector< std::pair < CType, CType > > ValidValues;

    for (size_t i = 0; i < validValues.size(); i++)
      {
        ValidValues.push_back(std::make_pair(validValues[i], validValues[i]));
      }

    assignValidValues(&ValidValues);
    return true;
  }

  /**
   * Retrieve the list of valid values. Note the returned object is only valid if
   * haveValidValues returns true;
   * @return const std::vector< std::pair < CType, CType > > & validValues
   */
  template < class CType > const std::vector< std::pair < CType, CType > > & getValidValues() const
  {
    return *static_cast< const std::vector< std::pair < CType, CType > > * >(mpValidValues);
  }

  /**
   * Retrieve the list of valid values. Note the returned object is only valid if
   * haveValidValues returns true;
   * @return std::vector< std::pair < CType, CType > > & validValues
   */
  template < class CType > std::vector< std::pair < CType, CType > > & getValidValues()
  {
    return *static_cast< std::vector< std::pair < CType, CType > > * >(mpValidValues);
  }

  /**
   * This is the output method for any object. The default implementation
   * provided with CDataObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const override;

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CCopasiParameter & A
   * @return ostream & os
   */
  friend std::ostream &operator<<(std::ostream &os, const CCopasiParameter & o);

  /**
   * Comparison operator
   * @param const CCopasiParameter & lhs
   * @param const CCopasiParameter & rhs
   * @return bool equal
   */
  friend bool operator==(const CCopasiParameter & lhs, const CCopasiParameter & rhs);

  /**
   * Retrieve the CN of the math container
   * The math container provides values for the numerical values of model objects.
   * For the CN mechanism to work properly it has to pretend to be the model.
   * @return CCommonName
   */
  virtual CCommonName getCN() const override;

  virtual void * getValuePointer() const override;

  void * getValidValuesPointer() const;
  /**
   *  Overload display name. Special treatment for reaction parameters
   *  to provide a shorter display.
   */
  virtual std::string getObjectDisplayName() const override;

  virtual void setUserInterfaceFlag(const UserInterfaceFlag & flag);

  const UserInterfaceFlag & getUserInterfaceFlag() const;

  bool isEditable() const;

  bool isBasic() const;

  bool isUnsupported() const;

  bool isDefault() const;

private:
  /**
   * Create or copy the value
   * @param const void * pValue
   */
  void createValue();

  void assignValue(const void * pValue);

  void assignValidValues(const void * pValidValues);

  void assignDefault(const void * pDefault);

  template < class CType > bool inValidValues(const CType & value) const
  {
    if (!hasValidValues()) return true;

    typename std::vector< std::pair< CType, CType > >::const_iterator it =
      static_cast< std::vector< std::pair< CType, CType > > * >(mpValidValues)->begin();
    typename std::vector< std::pair< CType, CType > >::const_iterator end =
      static_cast< std::vector< std::pair< CType, CType > > * >(mpValidValues)->end();

    for (; it != end; ++it)
      if (it->first <= value && value <= it->second) return true;

    return false;
  }
};

template < class CType >
bool compareValues(const CCopasiParameter & lhs, const CCopasiParameter & rhs)
{
  if (*static_cast< CType * >(lhs.getValuePointer()) != *static_cast< CType * >(rhs.getValuePointer()))
    {
      return false;
    }

  std::vector< std::pair< CType, CType > > * pLeft =
    static_cast< std::vector< std::pair< CType, CType > > * >(lhs.getValidValuesPointer());
  std::vector< std::pair< CType, CType > > * pRight =
    static_cast< std::vector< std::pair< CType, CType > > * >(rhs.getValidValuesPointer());

  if (pLeft != NULL && pRight != NULL)
    {
      if (pLeft->size() != pRight->size())
        return false;

      typename std::vector< std::pair< CType, CType > >::const_iterator itLeft = pLeft->begin();
      typename std::vector< std::pair< CType, CType > >::const_iterator endLeft = pLeft->end();
      typename std::vector< std::pair< CType, CType > >::const_iterator itRight = pRight->begin();

      for (; itLeft != endLeft; ++itLeft, ++itRight)
        {
          if (itLeft->first != itRight->first || itLeft->second != itRight->second)
            return false;
        }
    }
  else if (pLeft != NULL || pRight != NULL)
    {
      return false;
    }

  return true;
}

#endif // COPASI_CCopasiParameter
