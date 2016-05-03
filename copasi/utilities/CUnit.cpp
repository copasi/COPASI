// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <math.h>
#include <string.h>
#include <algorithm>

#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/utilities/CUnit.h"
#include "copasi/utilities/CUnitParser.h"
#include "copasi/model/CModel.h"
#include "copasi/xml/CCopasiXMLInterface.h"
#include "copasi/utilities/CUnitParser.h"

#include "CCopasiException.h"

// static
C_FLOAT64 CUnit::Avogadro(6.022140857e23); // http://physics.nist.gov/cgi-bin/cuu/Value?na (Thu Feb 11 09:57:27 EST 2016)

const char * CUnit::VolumeUnitNames[] =
{"dimensionless", "m\xc2\xb3", "l", "ml", "\xc2\xb5l", "nl", "pl", "fl", NULL};

const char * CUnit::AreaUnitNames[] =
{"dimensionless", "m\xc2\xb2", "dm\xc2\xb2", "cm\xc2\xb2", "mm\xc2\xb2", "\xc2\xb5m\xc2\xb2", "nm\xc2\xb2", "pm\xc2\xb2", "fm\xc2\xb2", NULL};

const char * CUnit::LengthUnitNames[] =
{"dimensionless", "m", "dm", "cm", "mm", "\xc2\xb5m", "nm", "pm", "fm", NULL};

const char * CUnit::TimeUnitNames[] =
{"dimensionless", "d", "h", "min", "s", "ms", "\xc2\xb5s", "ns", "ps", "fs", NULL};

// "mol" is the correct name, however in the COPASI XML files "Mol" is used
// up to build 18

const char * CUnit::QuantityUnitOldXMLNames[] =
{"dimensionless", "Mol", "mMol", "\xc2\xb5Mol", "nMol", "pMol", "fMol", "#", NULL};

const char * CUnit::QuantityUnitNames[] =
{"dimensionless", "mol", "mmol", "\xc2\xb5mol", "nmol", "pmol", "fmol", "#", NULL};

// static
std::string CUnit::replaceSymbol(const std::string & expression,
                                 const std::string & oldSymbol,
                                 const std::string & newSymbol)
{
  if (oldSymbol == newSymbol)
    return expression;

  std::istringstream buffer(expression);

  CUnitParser Parser(&buffer);
  Parser.setAvogadro(CUnit::Avogadro);
  Parser.replaceSymbol(oldSymbol, newSymbol);

  return (Parser.yyparse() == 0) ? Parser.getReplacedExpression() : expression;
}

// constructors
// default
CUnit::CUnit():
  mExpression(""),
  mComponents(),
  mUsedSymbols()
{
}

// expression
CUnit::CUnit(std::string expression,
             const C_FLOAT64 & avogadro):
  mExpression(""),
  mComponents(),
  mUsedSymbols()
{
  setExpression(expression, avogadro);
}

// kind
CUnit::CUnit(const CBaseUnit::Kind & kind):
  mExpression(CBaseUnit::getSymbol(kind)),
  mComponents(),
  mUsedSymbols()
{
  mComponents.insert(CUnitComponent(kind));
  consolidateDimensionless();
}

// copy constructor
CUnit::CUnit(const CUnit & src):
  mExpression(src.mExpression),
  mComponents(src.mComponents),
  mUsedSymbols(src.mUsedSymbols)
{
  consolidateDimensionless();
}

CUnit::~CUnit()
{}

bool CUnit::setExpression(const std::string & expression,
                          const C_FLOAT64 & avogadro)
{
  mExpression = expression;

  if (expression.empty())
    {
      mComponents.clear();
      return true;
    }

  return compile(avogadro);
}

bool CUnit::compile(const C_FLOAT64 & avogadro)
{
  mComponents.clear();
  mUsedSymbols.clear();

  std::istringstream buffer(mExpression);
  CUnitParser Parser(&buffer);
  Parser.setAvogadro(avogadro);

  bool success = (Parser.yyparse() == 0);

  if (success)
    {
      mComponents = Parser.getComponents();
      mUsedSymbols = Parser.getSymbols();
    }

  return success;
}

std::string CUnit::getExpression() const
{
  return mExpression;
}

const std::set< std::string > & CUnit::getUsedSymbols() const
{
  return mUsedSymbols;
}

bool CUnit::isDimensionless() const
{
  // Components are a set of unique Kinds.
  // consolodateDimensionless() should ensure any zero-exponent
  // components are integrated into a single, dimensionless, one.
  // So the following should work to retrieve if a unit is dimensionless,
  // but not undefined (no components).
  if (mComponents.size() == 1 &&
      (*mComponents.begin()).getKind() == CBaseUnit::dimensionless)
    return true;
  else
    return false;
}

bool CUnit::isUndefined() const
{
  return mComponents.empty();
}

void CUnit::addComponent(const CUnitComponent & component)
{
  std::set< CUnitComponent >::iterator it = mComponents.find(component);

  if (it != mComponents.end())
    {
      CUnitComponent * pComponent = const_cast< CUnitComponent * >(&*it);

      pComponent->setScale(pComponent->getScale() + component.getScale());
      pComponent->setMultiplier(pComponent->getMultiplier() * component.getMultiplier());

      if (pComponent->getKind() != CBaseUnit::dimensionless)
        {
          pComponent->setExponent(pComponent->getExponent() + component.getExponent());
        }
    }
  else
    {
      mComponents.insert(component);
    }

  consolidateDimensionless();
}

const std::set< CUnitComponent > & CUnit::getComponents() const
{
  return mComponents;
}

CUnit CUnit::exponentiate(double exp) const
{
  CUnit Unit(*this);

  std::set< CUnitComponent >::const_iterator it = Unit.getComponents().begin();
  std::set< CUnitComponent >::const_iterator end = Unit.getComponents().end();

  for (; it != end; it++)
    {
      CUnitComponent * pComponent = const_cast< CUnitComponent * >(&*it);

      pComponent->setMultiplier(pow(pComponent->getMultiplier(), exp));
      pComponent->setScale(pComponent->getScale() * exp);

      if (pComponent->getKind() != CBaseUnit::dimensionless)
        {
          pComponent->setExponent(pComponent->getExponent() * exp);
        }
    }

  return Unit;
}

// Putting units next to each other implies multiplying them.
CUnit  CUnit::operator*(const CUnit & rightSide) const
{
  CUnit Unit(*this); // Make a copy of the first CUnit

  std::set< CUnitComponent >::const_iterator it = rightSide.mComponents.begin();
  std::set< CUnitComponent >::const_iterator end = rightSide.mComponents.end();

  for (; it != end; ++it)
    {
      Unit.addComponent(*it);
    }

  Unit.mUsedSymbols.insert(rightSide.mUsedSymbols.begin(), rightSide.mUsedSymbols.end());

  return Unit; // The calling code might want to call simplifyComponents() on the returned unit.
}

bool CUnit::operator==(const CUnit & rightSide) const
{
  return (mExpression == rightSide.mExpression);
}

bool CUnit::operator<(const CUnit & rightSide) const
{
  if (mComponents.size() != rightSide.mComponents.size()) // RS has more components
    return mComponents.size() < rightSide.mComponents.size();

  // same (non-zero) number of components
  std::set< CUnitComponent >::const_iterator itLS = mComponents.begin(),
                                             itRS = rightSide.mComponents.begin();

  for (; itLS != mComponents.end(); ++itLS, ++itRS)
    {
      if (itLS->getKind() != itRS->getKind())
        {
          return itLS->getKind() < itRS->getKind();
        }

      if (itLS->getMultiplier() != itRS->getMultiplier())
        {
          return itLS->getMultiplier() < itRS->getMultiplier();
        }

      if (itLS->getScale() != itRS->getScale())
        {
          return itLS->getScale() < itRS->getScale();
        }
    }

  return mExpression < rightSide.mExpression;
}

bool CUnit::isEquivalent(const CUnit & rightSide) const
{
  if (mComponents.size() != rightSide.mComponents.size())
    {
      return false;
    }

  std::set< CUnitComponent >::const_iterator it = mComponents.begin(),
                                             end = mComponents.end(),
                                             itRhs = rightSide.mComponents.begin();

  for (; it != end; ++it, ++itRhs)
    {
      if ((it->getKind() == CBaseUnit::dimensionless &&
           itRhs->getKind() == CBaseUnit::dimensionless) ||
          *it == *itRhs)
        {
          continue;
        }

      return false;
    }

  return true;
}

// static
C_INT32 CUnit::getExponentOfSymbol(const std::string & symbol, CUnit & unit)
{
  // We ignore base units
  if (CBaseUnit::fromSymbol(symbol) != CBaseUnit::undefined) return 0;

  const CUnitDefinition * pUnitDef = CCopasiRootContainer::getUnitDefFromSymbol(symbol);

  if (pUnitDef == NULL) return 0;

  C_INT32 Exponent = 0;

  // First try multiplication
  while (true)
    {
      CUnit Tmp = unit **pUnitDef;

      // Compare components to determine whether this simplified the unit
      if (Tmp.getComponents().size() < unit.getComponents().size())
        {
          unit = Tmp;
          Exponent++;

          continue;
        }

      std::set< CUnitComponent >::const_iterator itOld = unit.getComponents().begin();
      std::set< CUnitComponent >::const_iterator endOld = unit.getComponents().end();
      std::set< CUnitComponent >::const_iterator itNew = Tmp.getComponents().begin();
      std::set< CUnitComponent >::const_iterator endNew = Tmp.getComponents().end();

      int improvement = 0;

      while (itOld != endOld && itNew != endNew)
        {
          if (itNew->getKind() > itOld->getKind())
            {
              improvement += fabs(itOld->getExponent());
              ++itOld;
            }
          else if (itNew->getKind() < itOld->getKind())
            {
              improvement -= fabs(itNew->getExponent());
              ++itNew;
            }
          else
            {
              // The kind is the same.
              if ((fabs(1.0 - itOld->getMultiplier()) < 100 * std::numeric_limits< C_FLOAT64 >::epsilon() &&
                   fabs(1.0 - itNew->getMultiplier()) >= 100 * std::numeric_limits< C_FLOAT64 >::epsilon()) ||
                  (itOld->getMultiplier() < 1.0 && itNew->getMultiplier() < itOld->getMultiplier()) ||
                  (itOld->getMultiplier() > 1.0 && itNew->getMultiplier() > itOld->getMultiplier()))
                {
                  improvement -= 100;
                }

              improvement += fabs(itOld->getExponent()) - fabs(itNew->getExponent());
              ++itOld;
              ++itNew;
            }
        }

      for (; itNew != endNew; ++itNew)
        {
          improvement -= fabs(itNew->getExponent());
        }

      for (; itOld != endOld; ++itOld)
        {
          improvement += fabs(itOld->getExponent());
        }

      if (improvement > 0)
        {
          unit = Tmp;
          Exponent++;

          continue;
        }

      break;
    }

  if (Exponent > 0) return -Exponent;

  // Now try division
  CUnit Inverse = pUnitDef->exponentiate(-1.0);

  while (true)
    {
      CUnit Tmp = unit * Inverse;

      // Compare symbols to determine whether this simplified the unit
      if (Tmp.getComponents().size() < unit.getComponents().size())
        {
          unit = Tmp;
          Exponent++;

          continue;
        }

      std::set< CUnitComponent >::const_iterator itOld = unit.getComponents().begin();
      std::set< CUnitComponent >::const_iterator endOld = unit.getComponents().end();
      std::set< CUnitComponent >::const_iterator itNew = Tmp.getComponents().begin();
      std::set< CUnitComponent >::const_iterator endNew = Tmp.getComponents().end();

      int improvement = 0;

      while (itOld != endOld && itNew != endNew)
        {
          if (itNew->getKind() > itOld->getKind())
            {
              improvement += fabs(itOld->getExponent());
              ++itOld;
            }
          else if (itNew->getKind() < itOld->getKind())
            {
              improvement -= fabs(itNew->getExponent());
              ++itNew;
            }
          else
            {
              // The kind is the same.
              if ((fabs(1.0 - itOld->getMultiplier()) < 100 * std::numeric_limits< C_FLOAT64 >::epsilon() &&
                   fabs(1.0 - itNew->getMultiplier()) >= 100 * std::numeric_limits< C_FLOAT64 >::epsilon()) ||
                  (itOld->getMultiplier() < 1.0 && itNew->getMultiplier() < itOld->getMultiplier()) ||
                  (itOld->getMultiplier() > 1.0 && itNew->getMultiplier() > itOld->getMultiplier()))
                {
                  improvement -= 100;
                }

              // The kind is the same.
              improvement += fabs(itOld->getExponent()) - fabs(itNew->getExponent());
              ++itOld;
              ++itNew;
            }
        }

      for (; itNew != endNew; ++itNew)
        {
          improvement -= fabs(itNew->getExponent());
        }

      for (; itOld != endOld; ++itOld)
        {
          improvement += fabs(itOld->getExponent());
        }

      if (improvement > 0)
        {
          unit = Tmp;
          Exponent++;

          continue;
        }

      break;
    }

  return Exponent;
}

std::vector< CUnit::SymbolComponent > CUnit::getSymbolComponents() const
{
  std::vector< SymbolComponent > SymbolComponents;
  size_t FirstNumeratorIndex = C_INVALID_INDEX;
  size_t FirstDenominatorIndex = C_INVALID_INDEX;
  int FirstNumeratorExponent = 0;
  int FirstDenominatorExponent = 0;

  SymbolComponent Component;

  Component.symbol = "1"; // default dimensionless
  Component.multiplier = 1.0;
  Component.scale = 0;
  Component.exponent = 0;

  CUnit Tmp(*this);
  Tmp.consolidateDimensionless();

  std::set< std::string > UsedSymbols = mUsedSymbols;
  size_t Index = 0;

  while (true)
    {
      std::set< std::string >::const_iterator itSymbol = UsedSymbols.begin();
      std::set< std::string >::const_iterator endSymbol = UsedSymbols.end();

      for (; itSymbol != endSymbol; ++itSymbol)
        {
          C_INT32 Exponent = getExponentOfSymbol(*itSymbol, Tmp);

          if (Exponent == 0) continue;

          Component.symbol = *itSymbol;
          Component.exponent = Exponent;

          SymbolComponents.push_back(Component);

          if (Exponent > 0 &&
              FirstNumeratorIndex == C_INVALID_INDEX)
            {
              FirstNumeratorIndex = Index;
              FirstNumeratorExponent = Exponent;
            }
          else if (Exponent < 0 &&
                   FirstDenominatorIndex == C_INVALID_INDEX)
            {
              FirstDenominatorIndex = Index;
              FirstDenominatorExponent = -Exponent;
            }

          Index++;
          break;
        }

      if (itSymbol == endSymbol) break;

      UsedSymbols.erase(itSymbol);
    }

  std::set< CUnitComponent >::const_iterator it = Tmp.getComponents().begin();
  std::set< CUnitComponent >::const_iterator end = Tmp.getComponents().end();

  // Find the dimensionless component, and the/a first components
  // which can in the numerator and denominator
  std::set< CUnitComponent >::const_iterator itDimensionless = end;

  for (; it != end; ++it)
    {
      if (itDimensionless == end &&
          it->getKind() == CBaseUnit::dimensionless)
        {
          itDimensionless = it;
          continue;
        }

      C_INT32 Exponent = it->getExponent();

      Component.symbol = CBaseUnit::getSymbol(it->getKind());
      Component.exponent = Exponent;

      SymbolComponents.push_back(Component);

      if (Exponent > 0 &&
          FirstNumeratorIndex == C_INVALID_INDEX)
        {
          FirstNumeratorIndex = Index;
          FirstNumeratorExponent = Exponent;
        }
      else if (Exponent < 0 &&
               FirstDenominatorIndex == C_INVALID_INDEX)
        {
          FirstDenominatorIndex = Index;
          FirstDenominatorExponent = -Exponent;
        }

      Index++;
    }

  double exponent = 1;

  if (FirstNumeratorExponent > 0)
    exponent = FirstNumeratorExponent;
  else if (FirstDenominatorExponent > 0)
    exponent = FirstDenominatorExponent;

  double multiplier = itDimensionless != end ? fabs(itDimensionless->getMultiplier()) * pow(10.0, itDimensionless->getScale()) : 1.0;
  int scale = 0;

  // Only one, if either, of the
  // following loops should run,
  // to ensure the multiplier is
  // from 1 up to 1000
  while (multiplier >= (1.0 - 100 * std::numeric_limits< double >::epsilon()) * pow(1000, exponent) && scale < 15)
    {
      multiplier /= pow(1000, exponent);
      scale += 3;
    }

  if (multiplier <= 1.0)
    {
      multiplier = 1.0 / multiplier;

      while (multiplier >= (1.0 - 100 * std::numeric_limits< double >::epsilon()) * pow(1000, exponent) && scale > -18)
        {
          multiplier /= pow(1000, exponent);
          scale -= 3;
        }

      multiplier = 1.0 / multiplier;
    }

  if (itDimensionless != end)
    {
      if (FirstNumeratorIndex != C_INVALID_INDEX &&
          SymbolComponents[FirstNumeratorIndex].symbol != "#")
        {
          SymbolComponents[FirstNumeratorIndex].multiplier = multiplier;
          SymbolComponents[FirstNumeratorIndex].scale = scale;
        }
      else if (FirstDenominatorIndex != C_INVALID_INDEX &&
               SymbolComponents[FirstDenominatorIndex].symbol != "#")
        {
          SymbolComponents[FirstDenominatorIndex].multiplier = multiplier;
          SymbolComponents[FirstDenominatorIndex].scale = -scale;
        }
      else
        {
          Component.multiplier = multiplier;
          Component.scale = scale;
          SymbolComponents.push_back(Component);
        }
    }

  return SymbolComponents;
}

void CUnit::buildExpression()
{
  std::vector< SymbolComponent > Components = getSymbolComponents();

  if (Components.empty())
    {
      mExpression = "";
      return;
    }

  std::ostringstream numerator, denominator;
  numerator.str("");
  denominator.str("");

  std::vector< SymbolComponent >::const_iterator it = Components.begin();
  std::vector< SymbolComponent >::const_iterator end = Components.end();

  size_t NumeratorCount = 0;
  size_t DenominatorCount = 0;

  for (; it != end; ++it)
    {
      if (it->exponent > 0)
        {
          if (NumeratorCount > 0)
            {
              numerator << "*";
            }
          else if (fabs(1.0 - it->multiplier) > 100 * std::numeric_limits< double >::epsilon())
            {
              numerator << it->multiplier << "*";
            }

          numerator << CBaseUnit::prefixFromScale(it->scale) << it->symbol;

          if (it->exponent > 1.0)
            {
              numerator << "^" << it->exponent;
            }

          NumeratorCount++;
        }
      else if (it->exponent < 0)
        {
          if (DenominatorCount > 0)
            {
              denominator << "*";
            }
          else if (fabs(1.0 - it->multiplier) > 100 * std::numeric_limits< double >::epsilon())
            {
              denominator << it->multiplier << "*";
              DenominatorCount++;
            }

          denominator << CBaseUnit::prefixFromScale(it->scale) << it->symbol;

          if (it->exponent < -1.0)
            {
              denominator << "^" << -it->exponent;
            }

          DenominatorCount++;
        }
      else
        {
          if (fabs(1.0 - it->multiplier) > 100 * std::numeric_limits< double >::epsilon())
            {
              numerator << it->multiplier << "*";
            }

          numerator << CBaseUnit::prefixFromScale(it->scale) << it->symbol;
          NumeratorCount++;
        }
    }

  mExpression = "";

  if (NumeratorCount == 0 &&
      DenominatorCount > 0)
    {
      numerator << 1.0;
      NumeratorCount++;
    }

  if (NumeratorCount > 0)
    {
      mExpression += numerator.str();
    }

  if (DenominatorCount > 1)
    {
      mExpression += "/(" + denominator.str() + ")";
    }
  else if (DenominatorCount > 0)
    {
      mExpression += "/" + denominator.str();
    }

  stringReplace(mExpression, "^2", "\xc2\xb2");
  stringReplace(mExpression, "^3", "\xc2\xb3");
}

bool CUnit::isUnitType(UnitType type) const
{
  CBaseUnit::Kind kind = CBaseUnit::undefined;
  int exponent;

  switch (type)
    {
      case time:
        kind = CBaseUnit::second;
        exponent = 1;
        break;

      case quantity:
        kind = CBaseUnit::item;
        exponent = 1;
        break;

      case volume:
        kind = CBaseUnit::meter;
        exponent = 3;
        break;

      case area:
        kind = CBaseUnit::meter;
        exponent = 2;
        break;

      case length:
        kind = CBaseUnit::meter;
        exponent = 1;
        break;

      default:
        return false;
    }

  std::set< CUnitComponent >::const_iterator lastComponent = mComponents.end();
  --lastComponent; // (because end points to one after the last one)

  if (mComponents.size() >= 1 && // has to be one or two components
      mComponents.size() <= 2 &&
      ((lastComponent->getKind() == CBaseUnit::dimensionless &&
        getExpression() == "1") || // Include dimensionless, but not rad, sr, etc.
       (lastComponent->getKind() == kind &&
        lastComponent->getExponent() == double(exponent))))
    return true;
  else // includes 0 exponents (undefined)
    return false;
}

void CUnit::consolidateDimensionless()
{
  // nothing to consolidate
  if (mComponents.empty()) return;

  std::set< CUnitComponent >::iterator it = mComponents.begin(),
                                       itEnd; //initialized later

  // logical default
  CUnitComponent tmpDimensionlessComponent = CUnitComponent(CBaseUnit::dimensionless);

  // If a dimensionless component already exists, it will be the first element
  // (set is ordered by Kind) and we should copy that one to the temporary one.
  if ((*it).getKind() == CBaseUnit::dimensionless)
    {
      tmpDimensionlessComponent = *it;
      mComponents.erase(it); // can't modify in-place, so may as well erase now
    }

  it = mComponents.begin(); // in case the previous *it was erased
  itEnd = mComponents.end();

  while (it != itEnd)
    {
      if ((*it).getExponent() == 0)
        {
          tmpDimensionlessComponent.setScale(tmpDimensionlessComponent.getScale() + (*it).getScale());
          tmpDimensionlessComponent.setMultiplier(tmpDimensionlessComponent.getMultiplier() * (*it).getMultiplier());
          mComponents.erase(it++); // Increment after erasing current one. This should be safe (C++ Standard 23.1.2.8)
        }
      else
        ++it;
    }

  mComponents.insert(tmpDimensionlessComponent);
}

// friend
std::ostream &operator<<(std::ostream &os, const CUnit & o)
{
  os << "Expression: " << o.mExpression << std::endl;
  os << "Components: " << std::endl;

  std::set< CUnitComponent >::const_iterator it = o.mComponents.begin();
  std::set< CUnitComponent >::const_iterator end = o.mComponents.end();

  for (; it != end; ++it)
    {
      os << *it;
    }

  return os;
}
