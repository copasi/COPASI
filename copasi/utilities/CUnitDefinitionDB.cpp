// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/utilities/CUnitDefinitionDB.h"
#include "utilities/CCopasiMessage.h"

//CCopasiVectorN(const std::string & name = "NoName",
//               const CCopasiContainer * pParent = NULL):

CUnitDefinitionDB::CUnitDefinitionDB(const std::string & name,
                                     const CCopasiContainer * pParent):
  CCopasiVectorN(name, pParent),
  mSymbolToUnitDefinitions()
{

}

//virtual
bool CUnitDefinitionDB::add(const CUnitDefinition & src)
{
  // This form will construct a copy, before adding (inherited
  // from CCopasiVectorN). When the CUnitDefinition
  // copy constructor is called, an exception will be thrown if
  // the symbol is already in use.
  CCopasiVectorN::add(src);
  mSymbolToUnitDefinitions[src.getSymbol()] = mRecentElement;

  return true;
}

//virtual
bool CUnitDefinitionDB::add(CUnitDefinition * src, bool adopt)
{

  // If it's symbol is already present, this form will not add
  // a pointer to the src object, and will return false.
  bool success = false;

  if (containsSymbol(src->getSymbol()))
    success = false;
  else
  {
    CCopasiVectorN::add(src, adopt);
    mSymbolToUnitDefinitions[src->getSymbol()] = mRecentElement;
    success = true;
  }

  return success;
}

//virtual
void CUnitDefinitionDB::remove(const size_t & index)
{
  mSymbolToUnitDefinitions.erase(operator [](index)->getSymbol());
  CCopasiVector::remove(index);
}

//virtual
bool CUnitDefinitionDB::remove(CUnitDefinition * unitDef)
{
  mSymbolToUnitDefinitions.erase(unitDef->getSymbol());
  CCopasiVector::remove(unitDef);
}

//virtual
void CUnitDefinitionDB::remove(const std::string & name)
{
  mSymbolToUnitDefinitions.erase(operator [](name)->getSymbol());
  CCopasiVectorN::remove(name);
}

bool CUnitDefinitionDB::containsSymbol(std::string symbol)
{
  if(mSymbolToUnitDefinitions.count(symbol))
    return true;
  else
    return false;
}

const CUnitDefinition * CUnitDefinitionDB::CUnitDefinitionFromSymbol(std::string symbol)
{
  return mSymbolToUnitDefinitions[symbol];
}
