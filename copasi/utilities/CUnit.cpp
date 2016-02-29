// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <math.h>
#include <string.h>
#include <algorithm>

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
CUnit::CUnit(std::string expression):
  mExpression(""),
  mComponents(),
  mUsedSymbols()
{
  setExpression(expression, Avogadro);
}

// kind
CUnit::CUnit(const CBaseUnit::Kind & kind):
  mExpression(CBaseUnit::getSymbol(kind)),
  mComponents(),
  mUsedSymbols()
{
  mComponents.insert(CUnitComponent(kind));
}

// copy constructor
CUnit::CUnit(const CUnit & src,
             const C_FLOAT64 & avogadro):
  mExpression(),
  mComponents(),
  mUsedSymbols()
{
  setExpression(src.mExpression, avogadro);
}

CUnit::~CUnit()
{
}

void CUnit::fromEnum(VolumeUnit volEnum)
{
  mComponents.clear();

  mExpression = VolumeUnitNames[volEnum];

  if (volEnum == CUnit::dimensionlessVolume)
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::meter);
  tmpComponent.setExponent(3);

  switch (volEnum)
    {
      case CUnit::m3:  //default scale = 0
        break;

      case CUnit::l:
        tmpComponent.setScale(-3);
        break;

      case CUnit::ml:
        tmpComponent.setScale(-6);
        break;

      case CUnit::microl:
        tmpComponent.setScale(-9);
        break;

      case CUnit::nl:
        tmpComponent.setScale(-12);
        break;

      case CUnit::pl:
        tmpComponent.setScale(-15);
        break;

      case CUnit::fl:
        tmpComponent.setScale(-18);
        break;

      default:
        return; // just to silence compiler warning
    }

  addComponent(tmpComponent);
}

void CUnit::fromEnum(AreaUnit areaEnum)
{
  mComponents.clear();

  mExpression = AreaUnitNames[areaEnum];

  if (areaEnum == CUnit::dimensionlessArea)
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::meter);
  tmpComponent.setExponent(2);

  switch (areaEnum)
    {
      case CUnit::m2:  //default scale = 0
        break;

      case CUnit::dm2:
        tmpComponent.setScale(-2);
        break;

      case CUnit::cm2:
        tmpComponent.setScale(-4);
        break;

      case CUnit::mm2:
        tmpComponent.setScale(-6);
        break;

      case CUnit::microm2:
        tmpComponent.setScale(-12);
        break;

      case CUnit::nm2:
        tmpComponent.setScale(-18);
        break;

      case CUnit::pm2:
        tmpComponent.setScale(-24);
        break;

      case CUnit::fm2:
        tmpComponent.setScale(-30);
        break;

      default:
        return; // just to silence compiler warning
    }

  addComponent(tmpComponent);
}

void CUnit::fromEnum(LengthUnit lengthEnum)
{
  mComponents.clear();

  mExpression = LengthUnitNames[lengthEnum];

  if (lengthEnum == CUnit::dimensionlessLength)
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::meter);

  switch (lengthEnum)
    {
      case CUnit::m:  //default scale = 0
        break;

      case CUnit::dm:
        tmpComponent.setScale(-1);
        break;

      case CUnit::cm:
        tmpComponent.setScale(-2);
        break;

      case CUnit::mm:
        tmpComponent.setScale(-3);
        break;

      case CUnit::microm:
        tmpComponent.setScale(-6);
        break;

      case CUnit::nm:
        tmpComponent.setScale(-9);
        break;

      case CUnit::pm:
        tmpComponent.setScale(-12);
        break;

      case CUnit::fm:
        tmpComponent.setScale(-15);
        break;

      default:
        return; // just to silence compiler warning
    }

  addComponent(tmpComponent);
}

void CUnit::fromEnum(TimeUnit timeEnum)
{
  mComponents.clear();

  mExpression = TimeUnitNames[timeEnum];

  if (timeEnum == CUnit::dimensionlessTime)
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::second);

  switch (timeEnum)
    {
      case CUnit::d:
        tmpComponent.setMultiplier(60 * 60 * 24);
        break;

      case CUnit::h:
        tmpComponent.setMultiplier(60 * 60);
        break;

      case CUnit::min:
      case CUnit::OldMinute:
        tmpComponent.setMultiplier(60);
        break;

      case CUnit::s:  // defaults are appropriate
        break;

      case CUnit::micros:
        tmpComponent.setScale(-6);
        break;

      case CUnit::ns:
        tmpComponent.setScale(-9);
        break;

      case CUnit::ps:
        tmpComponent.setScale(-12);
        break;

      case CUnit::fs:
        tmpComponent.setScale(-15);
        break;

      default:
        return; // just to silence compiler warning
    }

  addComponent(tmpComponent);
}

void CUnit::fromEnum(QuantityUnit quantityEnum, C_FLOAT64 avogadro)
{
  mComponents.clear();

  mExpression = QuantityUnitNames[quantityEnum];

  if (quantityEnum == CUnit::dimensionlessQuantity)
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::item);

  tmpComponent.setMultiplier(avogadro);

  //   enum QuantityUnit {dimensionlessQuantity = 0, Mol, mMol, microMol, nMol, pMol, fMol, number, OldXML};

  switch (quantityEnum)
    {
      case CUnit::Mol:
        break;

      case CUnit::mMol:
        tmpComponent.setScale(-3);
        break;

      case CUnit::microMol:
        tmpComponent.setScale(-6);
        break;

      case CUnit::nMol:
        tmpComponent.setScale(-9);
        break;

      case CUnit::pMol:
        tmpComponent.setScale(-12);
        break;

      case CUnit::fMol:
        tmpComponent.setScale(-15);
        break;

      case CUnit::number:
      case CUnit::OldXML:
        tmpComponent.setMultiplier(1);
        break;

      default:
        return; // just to silence compiler warning
    }

  addComponent(tmpComponent);
}

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

  // parse the expression into a linked node tree
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

  consolodateDimensionless();
}

const std::set< CUnitComponent > & CUnit::getComponents() const
{
  return mComponents;
}

CUnit & CUnit::exponentiate(double exp)
{
  std::set< CUnitComponent >::iterator it = mComponents.begin();

  for (; it != mComponents.end(); it++)
    {
      CUnitComponent * pComponent = const_cast< CUnitComponent * >(&*it);

      pComponent->setMultiplier(pow(pComponent->getMultiplier(), exp));
      pComponent->setScale(pComponent->getScale() * exp);

      if (pComponent->getKind() != CBaseUnit::dimensionless)
        {
          pComponent->setExponent(pComponent->getExponent() * exp);
        }
    }

  consolodateDimensionless();

  return *this;
}

// Putting units next to each other implies multiplying them.
CUnit CUnit::operator*(const CUnit & rhs) const
{
  std::set< CUnitComponent >::const_iterator it = rhs.mComponents.begin();
  std::set< CUnitComponent >::const_iterator end = rhs.mComponents.end();

  CUnit combined_unit = *this; // Make a copy of the first CUnit

  for (; it != end; ++it)
    {
      combined_unit.addComponent(*it);
    }

  return combined_unit; // The calling code might want to call simplifyComponents() on the returned unit.
}

bool CUnit::operator==(const CUnit & rhs) const
{
  return (mExpression == rhs.mExpression);
}

bool CUnit::isEquivalent(const CUnit & rhs) const
{
  if (mComponents.size() != rhs.mComponents.size())
    {
      return false;
    }

  std::set< CUnitComponent >::const_iterator it = mComponents.begin();
  std::set< CUnitComponent >::const_iterator end = mComponents.end();
  std::set< CUnitComponent >::const_iterator itRhs = rhs.mComponents.begin();

  for (; it != end; ++it, ++itRhs)
    {
      if (*it == *itRhs)
        {
          continue;
        }
      else
        return false;
    }

  return true;
}

void CUnit::consolodateDimensionless()
{
  // nothing to consolodate
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

  for (it; it != itEnd;)
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
  os << "Expression: " << o.mExpression << ", ";
  os << "Components: " << std::endl;

  std::set< CUnitComponent >::const_iterator it = o.mComponents.begin();
  std::set< CUnitComponent >::const_iterator end = o.mComponents.end();

  for (; it != end; ++it)
    {
      os << *it;
    }

  return os;
}
