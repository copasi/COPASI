// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/utilities/CUnitDefinitionDB.h"
#include "utilities/CCopasiMessage.h"

//CCopasiVectorN(const std::string & name = "NoName",
//               const CCopasiContainer * pParent = NULL):

CUnitDefinitionDB::CUnitDefinitionDB(const std::string & name,
                                     const CCopasiContainer * pParent):
  CCopasiVectorN< CUnitDefinition >(name, pParent),
  mSymbolToUnitDefinitions()
{
}

//virtual
bool CUnitDefinitionDB::add(const CUnitDefinition & src)
{
  if (containsSymbol(src.getSymbol())) return false;

  // This form will construct a copy, before adding (inherited
  // from CCopasiVectorN). When the CUnitDefinition
  // copy constructor is called, an exception will be thrown if
  // the symbol is already in use.
  CUnitDefinition * pCopy = NULL;

  try
    {
      pCopy = new CUnitDefinition(src, CUnit::Avogadro, this);
    }

  catch (...)
    {
      return false;
    }

  return add(pCopy, true);
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
      CCopasiVectorN< CUnitDefinition >::add(src, adopt);
      mSymbolToUnitDefinitions[src->getSymbol()] = src;

      if (src->getSymbol() == "\xCE\xA9")
        {
          mSymbolToUnitDefinitions["O"] = src;
        }

      success = true;
    }

  return success;
}

//virtual
void CUnitDefinitionDB::remove(const size_t & index)
{
  mSymbolToUnitDefinitions.erase(operator [](index)->getSymbol());
  CCopasiVector< CUnitDefinition >::remove(index);
}

//virtual
bool CUnitDefinitionDB::remove(CUnitDefinition * unitDef)
{
  mSymbolToUnitDefinitions.erase(unitDef->getSymbol());
  return CCopasiVector< CUnitDefinition >::remove(unitDef);
}

//virtual
void CUnitDefinitionDB::remove(const std::string & name)
{
  mSymbolToUnitDefinitions.erase(operator [](name)->getSymbol());
  CCopasiVectorN< CUnitDefinition >::remove(name);
}

bool CUnitDefinitionDB::containsSymbol(std::string symbol)
{
  if (mSymbolToUnitDefinitions.count(symbol))
    return true;
  else
    return false;
}

const CUnitDefinition * CUnitDefinitionDB::getUnitDefFromSymbol(std::string symbol)
{
  std::map<std::string, CUnitDefinition *>::const_iterator found = mSymbolToUnitDefinitions.find(symbol);

  if (found != mSymbolToUnitDefinitions.end())
    {
      return found->second;
    }

  return NULL;
}
