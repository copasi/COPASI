// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CDataValue
#define COPASI_CDataValue

#include <string>
#include <vector>

class CData;

class CDataValue
{
public:
  enum Type
  {
    DOUBLE = 0,
    INT,
    UINT,
    BOOL,
    STRING,
    DATA,
    DATA_VALUES,
    DATA_VECTOR,
    VOID_POINTER,
    INVALID,
    __SIZE
  };

  static const CEnumAnnotation< std::string, Type > TypeName;

  friend std::ostream & operator << (std::ostream & os, const CDataValue & o);
  friend std::istream & operator >> (std::istream & is, CDataValue & i);

  CDataValue(const Type & type = INVALID);
  CDataValue(const CDataValue & src);

  CDataValue(const C_FLOAT64 & value);
  CDataValue(const C_INT32 & value);
  CDataValue(const unsigned C_INT32 & value);
#ifdef DATAVALUE_NEEDS_SIZE_T_MEMBERS
  CDataValue(const size_t & value);
#endif // DATAVALUE_NEEDS_SIZE_T_MEMBERS
  CDataValue(const bool & value);
  CDataValue(const std::string & value);
  CDataValue(const char * value);
  CDataValue(const CData & value);
  CDataValue(const std::vector< CDataValue > & value);
  CDataValue(const std::vector< CData > & value);
  CDataValue(const void * pVoidPointer);

  ~CDataValue();

  CDataValue & operator = (const CDataValue & rhs);
  CDataValue & operator = (const C_FLOAT64 & value);
  CDataValue & operator = (const C_INT32 & value);
  CDataValue & operator = (const unsigned C_INT32 & value);
#ifdef DATAVALUE_NEEDS_SIZE_T_MEMBERS
  CDataValue & operator = (const size_t & value);
#endif // DATAVALUE_NEEDS_SIZE_T_MEMBERS
  CDataValue & operator = (const bool & value);
  CDataValue & operator = (const std::string & value);
  CDataValue & operator = (const CData & value);
  CDataValue & operator = (const std::vector< CDataValue > & value);
  CDataValue & operator = (const std::vector< CData > & value);
  CDataValue & operator = (const void * pVoidPointer);

  const C_FLOAT64 & toDouble() const;
  const C_INT32 & toInt() const;
  const unsigned C_INT32 & toUint() const;
  size_t toSizeT() const;
  const bool & toBool() const;
  const std::string & toString() const;
  const CData & toData() const;
  const std::vector< CDataValue > & toDataValues() const;
  const std::vector< CData > & toDataVector() const;
  const void * toVoidPointer() const;
  const void * raw() const;

  const Type & getType() const;

  bool operator == (const CDataValue & rhs) const;
  bool operator != (const CDataValue & rhs) const;

private:

  void allocateData(const Type & type);
  void deleteData();

  void assignData(const CDataValue & rhs);
  void assignData(const C_FLOAT64 & value);
  void assignData(const C_INT32 & value);
  void assignData(const unsigned C_INT32 & value);
#ifdef DATAVALUE_NEEDS_SIZE_T_MEMBERS
  void assignData(const size_t & value);
#endif // DATAVALUE_NEEDS_SIZE_T_MEMBERS
  void assignData(const bool & value);
  void assignData(const std::string & value);
  void assignData(const CData & value);
  void assignData(const std::vector< CDataValue > & value);
  void assignData(const std::vector< CData > & value);
  void assignData(const void * pVoidPointer);

  Type mType;
  void * mpData;
};

#endif // COPASI_CDataValue
