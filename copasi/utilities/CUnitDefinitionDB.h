// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// This class defines a "database" to collect
// unit definitions, and map them to unique
// symbols.

#ifndef CUNIT_DEFINITION_DB_H
#define CUNIT_DEFINITION_DB_H

//#include <unordered_map>
#include "copasi/utilities/CCopasiVector.h"
class CUnitDefinition;

class CUnitDefinitionDB: public CCopasiVectorN< CUnitDefinition >
{
public:

  // constructors
  // default
  CUnitDefinitionDB(const std::string & name = "NoName",
                    const CCopasiContainer * pParent = NO_PARENT);

  ~CUnitDefinitionDB() {}

  virtual bool add(const CUnitDefinition & src);
  virtual bool add(CUnitDefinition * src, bool adopt = false);
  virtual void remove(const size_t & index);
  virtual bool remove(CCopasiObject * pObject);
  virtual void remove(const std::string & name);

  bool containsSymbol(std::string symbol);
  const CUnitDefinition * getUnitDefFromSymbol(std::string symbol) const;

  bool changeSymbol(CUnitDefinition *pUnitDef, const std::string & symbol);

  std::string quoteSymbol(const std::string & symbol) const;

  std::vector< CUnit > getAllValidUnits(const std::string & expression,
                                        const C_FLOAT64 & exponent) const;

private:

  std::map<std::string, CUnitDefinition *> mSymbolToUnitDefinitions;
};
#endif // CUNIT_DEFINITION_DB_H
