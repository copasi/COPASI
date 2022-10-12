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

#include "copasi/utilities/CUnitDefinitionDB.h"
#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/core/CRootContainer.h"

CUnitDefinitionDB::CUnitDefinitionDB(const std::string & name,
                                     const CDataContainer * pParent):
  CDataVectorN< CUnitDefinition >(name, pParent),
  mSymbolToUnitDefinitions()
{}

//virtual
bool CUnitDefinitionDB::add(const CUnitDefinition & src)
{
  // This form will construct a copy, before adding (inherited
  // from CDataVectorN). When the CUnitDefinition
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

  CDataVectorN< CUnitDefinition >::add(src, adopt);
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
bool CUnitDefinitionDB::remove(CDataObject * pObject)
{
  CUnitDefinition * pUnitDef = dynamic_cast< CUnitDefinition * >(pObject);

  if (pUnitDef)
    {
      mSymbolToUnitDefinitions.erase(pUnitDef->getSymbol());
    }

  return CDataVector< CUnitDefinition >::remove(pObject);
}

//virtual
void CUnitDefinitionDB::remove(const std::string & name)
{
  remove(&operator [](name));
}

bool CUnitDefinitionDB::containsSymbol(std::string symbol) const
{
  return (symbol == "?" ||
          mSymbolToUnitDefinitions.count(symbol) > 0);
}

const CUnitDefinition * CUnitDefinitionDB::getUnitDefFromSymbol(std::string symbol) const
{
  std::map<std::string, CUnitDefinition *>::const_iterator found = mSymbolToUnitDefinitions.find(unQuote(symbol));

  if (found != mSymbolToUnitDefinitions.end())
    {
      return found->second;
    }

  return NULL;
}

bool CUnitDefinitionDB::changeSymbol(CUnitDefinition *pUnitDef, const std::string & symbol)
{
  if (pUnitDef->getObjectParent() != this) return true;

  std::map<std::string, CUnitDefinition *>::iterator New = mSymbolToUnitDefinitions.find(symbol);
  std::map<std::string, CUnitDefinition *>::iterator Old = mSymbolToUnitDefinitions.find(pUnitDef->getSymbol());

  if (New == mSymbolToUnitDefinitions.end())
    {
      if (New != Old)
        {
          mSymbolToUnitDefinitions.insert(std::make_pair(symbol, pUnitDef));
          replaceSymbol(pUnitDef->getSymbol(), symbol);
          mSymbolToUnitDefinitions.erase(Old);

          return true;
        }
      else
        {
          mSymbolToUnitDefinitions.insert(std::make_pair(symbol, pUnitDef));

          return true;
        }
    }
  else
    {
      if (New == Old)
        {
          replaceSymbol(pUnitDef->getSymbol(), symbol);

          return true;
        }
      else
        {
          return false;
        }
    }

  return true;
}

std::string CUnitDefinitionDB::quoteSymbol(const std::string & symbol) const
{
  const CUnitDefinition * pUnitDef = getUnitDefFromSymbol(symbol);

  if (pUnitDef == NULL ||
      CUnit(symbol) == *pUnitDef) return symbol;

  return quote(" " + symbol).erase(1, 1);
}

void CUnitDefinitionDB::replaceSymbol(const std::string & oldSymbol,
                                      const std::string & newSymbol)
{
  iterator it = begin();
  iterator end = this->end();

  for (; it != end; ++it)
    {
      it->replaceSymbol(oldSymbol, newSymbol);
    }

  if (getObjectParent() == CRootContainer::getRoot())
    {
      CRootContainer::replaceSymbol(oldSymbol, newSymbol);
    }
}

std::vector< CUnit > CUnitDefinitionDB::getAllValidUnits(const std::string & symbol,
    const C_FLOAT64 & exponent) const
{
  std::vector< CUnit > ValidUnits;

  if (getUnitDefFromSymbol(symbol) == NULL)
    {
      return ValidUnits;
    }

  std::set< CUnit > ValidUnitSet;
  CUnit Base(symbol);
  CUnit Power = Base.exponentiate(exponent);

  // dimensionless is always valid
  ValidUnitSet.insert(CUnit(CBaseUnit::dimensionless));

  const_iterator it = begin();
  const_iterator itEnd = end();

  for (; it != itEnd; ++it)
    {
      if (it->isEquivalent(Power) ||
          it->isEquivalent(Base))
        {
          if ((it->getComponents().begin()->getMultiplier() == 1.0 ||
               it->getSymbol() == "l") &&
              !it->CUnit::operator==(CBaseUnit::item))
            {
              for (C_INT32 scale = CBaseUnit::yocto; scale <= CBaseUnit::yotta; scale += 3)
                {
                  CUnit Scale;
                  Scale.addComponent(CUnitComponent(CBaseUnit::dimensionless, 1.0, scale, 0));
                  CUnit ScaledUnit(Scale * CUnit(it->getSymbol()));

                  if (it->isEquivalent(Base))
                    {
                      ScaledUnit = ScaledUnit.exponentiate(exponent);
                    }

                  ScaledUnit.buildExpression();
                  ValidUnitSet.insert(ScaledUnit);
                }
            }
          else
            {
              CUnit ScaledUnit(it->getSymbol());

              if (it->isEquivalent(Base))
                {
                  ScaledUnit = ScaledUnit.exponentiate(exponent);
                }

              ScaledUnit.buildExpression();
              ValidUnitSet.insert(ScaledUnit);
            }
        }
    }

  ValidUnits.insert(ValidUnits.begin(), ValidUnitSet.begin(), ValidUnitSet.end());

  return ValidUnits;
}

bool CUnitDefinitionDB::appendDependentUnits(std::set< const CDataObject * > candidates,
    std::set< const CDataObject * > & dependentUnits) const
{
  std::set< std::string > DeletedSymbols;

  std::set< const CDataObject * >::const_iterator itCandidate = candidates.begin();
  std::set< const CDataObject * >::const_iterator endCandidate = candidates.end();

  for (; itCandidate != endCandidate; ++itCandidate)
    {
      const CUnitDefinition * pUnit = dynamic_cast< const CUnitDefinition * >(*itCandidate);

      if (pUnit)
        {
          DeletedSymbols.insert(pUnit->getSymbol());
        }
    }

  CDataVectorN< CUnitDefinition >::const_iterator it = begin();
  CDataVectorN< CUnitDefinition >::const_iterator itEnd = end();

  for (; it != itEnd; ++it)
    {
      std::set< std::string >::const_iterator itUsedSymbols = it->getUsedSymbols().begin();
      std::set< std::string >::const_iterator endUsedSymbols = it->getUsedSymbols().end();
      std::set< std::string >::const_iterator itDeletedSymbols = DeletedSymbols.begin();
      std::set< std::string >::const_iterator endDeletedSymbols = DeletedSymbols.end();

      while (itUsedSymbols != endUsedSymbols && itDeletedSymbols != endDeletedSymbols)
        {
          if (*itUsedSymbols < *itDeletedSymbols)
            {
              ++itUsedSymbols;
              continue;
            }

          if (*itDeletedSymbols < *itUsedSymbols)
            {
              ++itDeletedSymbols;
              continue;
            }

          dependentUnits.insert(&*it);

          break;
        }
    }

  return dependentUnits.size() > 0;
}
