// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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
#include "copasi/core/CDataVector.h"
class CUnitDefinition;

class CUnitDefinitionDB: public CDataVectorN< CUnitDefinition >
{
public:

  // constructors
  // default
  CUnitDefinitionDB(const std::string & name = "NoName",
                    const CDataContainer * pParent = NO_PARENT);

  ~CUnitDefinitionDB() {}

  virtual bool add(const CUnitDefinition & src);
  virtual bool add(CUnitDefinition * src, bool adopt = false);
  virtual void remove(const size_t & index);
  virtual bool remove(CDataObject * pObject);
  virtual void remove(const std::string & name);

  bool containsSymbol(std::string symbol) const;
  const CUnitDefinition * getUnitDefFromSymbol(std::string symbol) const;

  bool changeSymbol(CUnitDefinition *pUnitDef, const std::string & symbol);

  std::string quoteSymbol(const std::string & symbol) const;

  std::vector< CUnit > getAllValidUnits(const std::string & expression,
                                        const C_FLOAT64 & exponent) const;

  /**
   * Appends pointers to units, which are dependent on any of the candidates
   * to the list dependentUnits.
   * @param std::set< const CDataObject * > candidates
   * @param std::set< const CDataObject * > & dependentUnits
   * @return bool unitsAppended
   */
  bool appendDependentUnits(std::set< const CDataObject * > candidates,
                            std::set< const CDataObject * > & dependentUnits) const;

private:
  /**
   * Replace all old symbols with new symbols in the unit definition DB
   * @param const std::string & oldSymbol
   * @param const std::string & newSymbol
   */
  void replaceSymbol(const std::string & oldSymbol,
                     const std::string & newSymbol);

  std::map<std::string, CUnitDefinition *> mSymbolToUnitDefinitions;
};
#endif // CUNIT_DEFINITION_DB_H
