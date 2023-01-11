// Copyright (C) 2022 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef C_EXPRESSION_GENERATOR_H
#  define C_EXPRESSION_GENERATOR_H

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include <copasi/core/CDataObject.h>
class CModel;

class CExpressionGenerator : public CDataObject
{
public:
  struct sOperation
  {
    std::string join;
    std::string surroundStart;
    std::string surroundEnd;
    std::string entryStart;
    std::string entryEnd;
  };

private:
  std::string mType;
  std::string mSelection;
  std::string mOperation;

  static std::vector< std::string > mSupportedTypes;
  static std::map< std::string, sOperation > mOperations;

  static std::string escapeDisplayName(const CDataObject * pObject);

public:

  CExpressionGenerator(const std::string & type, const std::string & selection, const std::string & operation);

  static std::vector< std::string > getSupportedOperations();

  static bool isTypeSupported(const std::string& type);

  std::vector< const CDataObject * > getObjectsForSelection(const CModel * pModel) const;

  std::string generateExpressionFor(const CModel * pModel, bool useCn = false) const;

  void setType(const std::string & type);
  void setSelection(const std::string & selection);
  void setOperation(const std::string & operation);
};

#endif // C_EXPRESSION_GENERATOR_H
