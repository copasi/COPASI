// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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
private:
  CDataValue();

public:
  enum Type
  {
    DOUBLE = 0,
    INT,
    UINT,
    BOOL,
    STRING,
    DATA_VECTOR,
    INVALID
  };

  CDataValue(const Type & type);
  CDataValue(const CDataValue & src);

  CDataValue(const C_FLOAT64 & value);
  CDataValue(const C_INT32 & value);
  CDataValue(const unsigned C_INT32 & value);
  CDataValue(const bool & value);
  CDataValue(const std::string & value);
  CDataValue(const std::vector< CData > & value);

  ~CDataValue();

  CDataValue & operator = (const CDataValue & rhs);
  CDataValue & operator = (const C_FLOAT64 & value);
  CDataValue & operator = (const C_INT32 & value);
  CDataValue & operator = (const unsigned C_INT32 & value);
  CDataValue & operator = (const bool & value);
  CDataValue & operator = (const std::string & value);
  CDataValue & operator = (const std::vector< CData > & value);

  const C_FLOAT64 & toDouble() const;
  const C_INT32 & toInt() const;
  const unsigned C_INT32 & toUint() const;
  const bool & toBool() const;
  const std::string & toString() const;
  const std::vector< CData > toDataVector() const;

  const Type & getType() const;

private:

  void allocateData(const Type & type);
  void deleteData();

  void assignData(const CDataValue & rhs);
  void assignData(const C_FLOAT64 & value);
  void assignData(const C_INT32 & value);
  void assignData(const unsigned C_INT32 & value);
  void assignData(const bool & value);
  void assignData(const std::string & value);
  void assignData(const std::vector< CData > & value);

  Type mType;
  void * mpData;
};

#endif // COPASI_CDataValue
