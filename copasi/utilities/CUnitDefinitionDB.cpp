// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "utilities/CUnitDefinitionDB.h"
#include "utilities/CUnitDefinition.h"
#include "utilities/CCopasiMessage.h"

CUnitDefinitionDB::CUnitDefinitionDB(const std::string & name,
                                     const CCopasiContainer * pParent):
  CCopasiVectorN< CUnitDefinition >(name, pParent),
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
  // If it's symbol is already present, this form will not add
  // a pointer to the src object, and will return false.

  if (containsSymbol(src.getSymbol()) ||
      getIndex(src.getObjectName()) != C_INVALID_INDEX)
    {
      return false;
    }

  CUnitDefinition * pCopy = NULL;

  try
    {
      pCopy = new CUnitDefinition(src, this);
    }

  catch (...)
    {
      return false;
    }

  return true;
}

//virtual
bool CUnitDefinitionDB::add(CUnitDefinition * src, bool adopt)
{

  // If it's symbol is already present, this form will not add
  // a pointer to the src object, and will return false.
  if (containsSymbol(src->getSymbol()) ||
      getIndex(src->getObjectName()) != C_INVALID_INDEX)
    {
      return false;
    }

  CCopasiVectorN< CUnitDefinition >::add(src, adopt);
  mSymbolToUnitDefinitions[src->getSymbol()] = src;

  if (src->getSymbol() == "\xCE\xA9")
    {
      mSymbolToUnitDefinitions["O"] = src;
    }

  return true;
}

//virtual
void CUnitDefinitionDB::remove(const size_t & index)
{
  remove(&operator [](index));
}

//virtual
bool CUnitDefinitionDB::remove(CCopasiObject * pObject)
{
  CUnitDefinition * pUnitDef = dynamic_cast< CUnitDefinition * >(pObject);

  if (pUnitDef)
    {
      mSymbolToUnitDefinitions.erase(pUnitDef->getSymbol());
    }

  return CCopasiVector< CUnitDefinition >::remove(pObject);
}

//virtual
void CUnitDefinitionDB::remove(const std::string & name)
{
  remove(&operator [](name));
}

bool CUnitDefinitionDB::containsSymbol(std::string symbol)
{
  if (mSymbolToUnitDefinitions.count(symbol))
    return true;
  else
    return false;
}

const CUnitDefinition * CUnitDefinitionDB::getUnitDefFromSymbol(std::string symbol) const
{
  std::map<std::string, CUnitDefinition *>::const_iterator found = mSymbolToUnitDefinitions.find(symbol);

  if (found != mSymbolToUnitDefinitions.end())
    {
      return found->second;
    }

  return NULL;
}

bool CUnitDefinitionDB::changeSymbol(CUnitDefinition *pUnitDef, const std::string & symbol)
{
  if (pUnitDef->getObjectParent() != this) return true;

  std::map<std::string, CUnitDefinition *>::iterator found = mSymbolToUnitDefinitions.find(symbol);

  if (found != mSymbolToUnitDefinitions.end() &&
      found->second != pUnitDef) return false;

  found = mSymbolToUnitDefinitions.find(pUnitDef->getSymbol());

  if (found != mSymbolToUnitDefinitions.end())
    {
      if (pUnitDef->getSymbol() == symbol) return true;

      if (found->second == pUnitDef)
        {
          mSymbolToUnitDefinitions.erase(found);
        }
    }

  mSymbolToUnitDefinitions.insert(std::make_pair(symbol, pUnitDef));

  return true;
}

std::set< CUnit > CUnitDefinitionDB::getAllValidUnits(const std::string & symbol,
    const std::string & exponent) const
{
  std::set< CUnit > ValidUnits;

  if (getUnitDefFromSymbol(symbol) == NULL)
    {
      ValidUnits;
    }

  std::string Exponent;

  if (exponent == "1")
    {
      Exponent = "";
    }
  else if (exponent == "2")
    {
      Exponent = "\xc2\xb2";
    }
  else if (exponent == "3")
    {
      Exponent = "\xc2\xb3";
    }
  else
    {
      Exponent = "^" + exponent;
    }

  CUnit Base(symbol);
  CUnit Power(symbol + Exponent);

  // dimensionless is always valid
  ValidUnits.insert(CUnit(CBaseUnit::dimensionless));

  const_iterator it = begin();
  const_iterator itEnd = end();

  for (; it != itEnd; ++it)
    {
      if (it->isEquivalent(Power))
        {
          if ((it->getComponents().begin()->getMultiplier() == 1.0 ||
               it->getComponents().begin()->getMultiplier() == CUnit::Avogadro ||
               it->getSymbol() == "l") &&
              !it->CUnit::operator==(CBaseUnit::item))
            {
              for (C_INT32 scale = -18; scale < 18; scale += 3)
                {
                  CUnit Scale;
                  Scale.addComponent(CUnitComponent(CBaseUnit::dimensionless, 1.0, scale, 0));
                  CUnit ScaledUnit = (Scale * CUnit(it->getSymbol()));
                  ScaledUnit.buildExpression();
                  ValidUnits.insert(ScaledUnit);
                }
            }
          else
            {
              ValidUnits.insert(it->getSymbol());
            }
        }
      else if (it->isEquivalent(Base))
        {
          if ((it->getComponents().begin()->getMultiplier() == 1.0 ||
               it->getComponents().begin()->getMultiplier() == CUnit::Avogadro ||
               it->getSymbol() == "l") &&
              !it->CUnit::operator==(CBaseUnit::item))
            {
              for (C_INT32 scale = -18; scale < 18; scale += 3)
                {
                  CUnit Scale;
                  Scale.addComponent(CUnitComponent(CBaseUnit::dimensionless, 1.0, scale, 0));
                  CUnit ScaledUnit = (Scale * CUnit(it->getSymbol()));
                  ScaledUnit.buildExpression();
                  ValidUnits.insert(ScaledUnit.getExpression() + Exponent);
                }
            }
          else
            {
              ValidUnits.insert(it->getSymbol());
            }
        }
    }

  return ValidUnits;
}
