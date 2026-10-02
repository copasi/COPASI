// Copyright (C) 2022 - 2026 by Pedro Mendes, Rector and Visitors of the
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
class CExpressionGenerator;

class sOperation
{
private:
  std::string_view join;
  std::string_view surroundStart;
  std::string_view surroundEnd;
  std::string_view entryStart;
  std::string_view entryEnd;

public:
  friend class CExpressionGenerator;

  constexpr sOperation(std::string_view _join,
                       std::string_view _surroundStart,
                       std::string_view _surroundEnd,
                       std::string_view _entryStart,
                       std::string_view _entryEnd)
    : join(_join)
    , surroundStart(_surroundStart)
    , surroundEnd(_surroundEnd)
    , entryStart(_entryStart)
    , entryEnd(_entryEnd)
  {}

  void swap(sOperation & rhs)
  {
    join.swap(rhs.join);
    surroundStart.swap(rhs.surroundStart);
    surroundEnd.swap(rhs.surroundEnd);
    entryStart.swap(rhs.entryStart);
    entryEnd.swap(rhs.entryEnd);
  }

  constexpr bool operator==(const sOperation & rhs) const
  {
    return join == rhs.join
           && surroundStart == rhs.surroundStart
           && surroundEnd == rhs.surroundEnd
           && entryStart == rhs.entryStart
           && entryEnd == rhs.entryEnd;
  }

  constexpr bool operator<(const sOperation & rhs) const
  {
    if (join != rhs.join)
      return join < rhs.join;

    if (surroundStart != rhs.surroundStart)
      return surroundStart < rhs.surroundStart;

    if (surroundEnd != rhs.surroundEnd)
      return surroundEnd < rhs.surroundEnd;

    if (entryStart != rhs.entryStart)
      return entryStart < rhs.entryStart;

    return entryEnd < rhs.entryEnd;
  }
};

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

private:
  constexpr static CEnumAnnotationInstance _OperationNames{
    Operation::Sum,
    MapNode{Operation::Sum, "Sum"},
    MapNode{Operation::SumOfSquares, "Sum of Squares"},
    MapNode{Operation::SumOfAbsolutes, "Sum of Absolutes"},
    MapNode{Operation::Product, "Product"}};

public:
  constexpr static CEnumAnnotation< Operation, std::string_view > OperationNames{_OperationNames};

private:
  constexpr static CEnumAnnotationInstance _OperationParts{
    Operation::Sum,
    MapNode{Operation::Sum, sOperation(" + ", "", "", "", "")},
    MapNode{Operation::SumOfSquares, sOperation(" + ", "", "", "", "^2")},
    MapNode{Operation::SumOfAbsolutes, sOperation(" + ", "", "", "ABS(", ")")},
    MapNode{Operation::Product, sOperation(" * ", "", "", "", "")}};

public:
  constexpr static CEnumAnnotation< Operation, sOperation > OperationParts{_OperationParts};

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
