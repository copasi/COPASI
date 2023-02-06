// Copyright (C) 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef C_EXPRESSION_GENERATOR_H
#define C_EXPRESSION_GENERATOR_H

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include "copasi/core/CDataObject.h"
#include "copasi/core/CEnumAnnotation.h"

class CModel;

class CExpressionGenerator : public CDataObject
{
public:
  enum class Operation
  {
    Sum,
    SumOfSquares,
    SumOfAbsolutes,
    Product,
    __SIZE
  };

  static const CEnumAnnotation< std::string, Operation > OperationNames;

private:
  struct sOperation
  {
    std::string join;
    std::string surroundStart;
    std::string surroundEnd;
    std::string entryStart;
    std::string entryEnd;

    sOperation(const std::string & _join,
               const std::string & _surroundStart,
               const std::string & _surroundEnd,
               const std::string & _entryStart,
               const std::string & _entryEnd)
      : join(_join)
      , surroundStart(_surroundStart)
      , surroundEnd(_surroundEnd)
      , entryStart(_entryStart)
      , entryEnd(_entryEnd)
    {}

    bool operator < (const sOperation & rhs) const
    {
      if (this != &rhs)
        return join + surroundStart + surroundEnd + entryStart + entryEnd < rhs.join + rhs.surroundStart + rhs.surroundEnd + rhs.entryStart + rhs.entryEnd;

      return false;
    }
  };

  static const CEnumAnnotation< sOperation, Operation > OperationParts;

  std::string mType;
  std::string mSelection;
  Operation mOperation;

  static std::vector< std::string > mSupportedTypes;

  static std::string escapeDisplayName(const CDataObject * pObject);

public:
  static std::string generate(Operation operation, const std::vector< const CDataObject * > & objects, bool useCn = false);

  CExpressionGenerator(const std::string & type, const std::string & selection, const std::string & operation);

  static std::vector< std::string > getSupportedOperations();

  static bool isTypeSupported(const std::string & type);

  std::vector< const CDataObject * > getObjectsForSelection(const CModel * pModel) const;

  std::string generateExpressionFor(const CModel * pModel, bool useCn = false) const;

  void setType(const std::string & type);
  void setSelection(const std::string & selection);
  void setOperation(const std::string & operation);
};

#endif // C_EXPRESSION_GENERATOR_H
