// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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
#include "copasi/utilities/CUnitDefinition.h"

class CUnitDefinitionDB: public CCopasiVectorN< CUnitDefinition >
{
public:

  // constructors
  // default
  CUnitDefinitionDB(const std::string & name = "NoName",
                    const CCopasiContainer * pParent = NULL);

  ~CUnitDefinitionDB() {}

  virtual bool add(const CUnitDefinition & src);
  virtual bool add(CUnitDefinition * src, bool adopt = false);
  virtual void remove(const size_t & index);
  virtual bool remove(CUnitDefinition *unitDef);
  virtual void remove(const std::string & name);

  bool containsSymbol(std::string symbol);
  const CUnitDefinition * CUnitDefinitionFromSymbol(std::string symbol);

private:

  std::map<std::string, CUnitDefinition *> mSymbolToUnitDefinitions;

};
#endif // CUNIT_DEFINITION_DB_H
