// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <math.h>
#include <string.h>
#include <algorithm>

#include "copasi/utilities/CUnit.h"
#include "copasi/utilities/CUnitParser.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/xml/CCopasiXMLInterface.h"
#include "copasi/utilities/CUnitParser.h"

#include "CCopasiException.h"

// static
CUnit CUnit::EmptyUnit("empty_unit");

// static
C_FLOAT64 CUnit::Avogadro(6.02214129e23); // http://physics.nist.gov/cgi-bin/cuu/Value?na (Wed Jan 29 18:33:36 EST 2014)

// SI Name, Symbol, Definition
struct SIUnit
{
  const char * name;
  const char * symbol;
  const char * definition;
};

SIUnit SIUnits[] =
{
  {"becquerel",  "Bq",       "s^-1"},
  {"coulomb",    "C",        "s*A"},
  {"farad",      "F",        "m^-2*kg^-1*s^4*A^2"},
  {"gray",       "Gy",       "m^2*s^-2"},
  {"henry",      "H",        "m^2*kg*s^-2*A^-2"},
  {"hertz",      "Hz",       "s^-1"},
  {"joule",      "J",        "m^2*kg*s^-2"},
  {"katal",      "ka",       "s^-1*mol"},
  {"liter",      "l",        "0.001*m^3"},
  {"lumen",      "lm",       "cd"},
  {"lux",        "lx",       "m^-2*cd"},
  {"mole",       "mol",      "Avogadro*#"},
  {"newton",     "N",        "m*kg*s^-2"},
  {"ohm",        "\xCE\xA9", "m^2*kg*s^-3*A^-2"},
  {"pascal",     "Pa",       "m^-1*kg*s^-2"},
  {"siemens",    "S",        "m^-2*kg^-1*s^3*A^2"},
  {"sievert",    "Sv",       "m^2*s^-2"},
  {"tesla",      "T",        "kg*s^-2*A^-1"},
  {"volt",       "V",        "m^2*kg*s^-3*A^-1"},
  {"watt",       "W",        "m^2*kg*s^-3"},
  {"weber",      "Wb",       "m^2*kg*s^-2*A^-1"},

  {"minute",     "min",      "60*s"},
  {"hour",       "h",        "3600*s"},
  {"day",        "d",        "86400*s"},

  // This must be the last element of the SI unit list! Do not delete!
  {NULL,         NULL,        NULL}
};

// static

CUnit CUnit::getSIUnit(const std::string & si,
                       const C_FLOAT64 & avogadro)
{
  SIUnit * pSIUnit = SIUnits;

  while (pSIUnit->name && strcmp(pSIUnit->symbol, si.c_str()) != 0)
    ++pSIUnit;

  if (!pSIUnit->name)
    fatalError();

  std::ostringstream buffer;

  if (strcmp(pSIUnit->symbol, "mol"))
    {
      buffer << pSIUnit->definition;
    }
  else
    {
      buffer << CCopasiXMLInterface::DBL(avogadro) << "*#";
    }

  CUnit SIunit = CUnit();

  SIunit.setObjectName(pSIUnit->name);
  SIunit.setSymbol(pSIUnit->symbol);
  SIunit.setDefinition(buffer.str(), avogadro);

  return SIunit;
}

// static
void CUnit::updateSIUnits(CCopasiVectorN< CUnit > & Units,
                          const C_FLOAT64 & avogadro)
{
  SIUnit * pSIUnit = SIUnits;

  while (pSIUnit->name)
    {
      CUnit * pUnit = NULL;
      size_t Index = Units.getIndex(pSIUnit->name);

      if (Index != C_INVALID_INDEX)
        {
          pUnit = Units[Index];
        }
      else
        {
          pUnit = new CUnit();

          pUnit->setObjectName(pSIUnit->name);
          pUnit->setSymbol(pSIUnit->symbol);
          Units.add(pUnit, true);
        }

      std::ostringstream buffer;

      if (strcmp(pSIUnit->symbol, "mol"))
        {
          buffer << pSIUnit->definition;
        }
      else
        {
          buffer << CCopasiXMLInterface::DBL(avogadro) << "*#";
        }

      pUnit->setDefinition(buffer.str(), avogadro);

      pSIUnit++;
    }
}

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

// constructors
CUnit::CUnit(const std::string & name,
             const CCopasiContainer * pParent):
  CCopasiContainer(name, pParent, "Unit"),
  mSymbol("none"),
  mDefinition(),
  mComponents(),
  mUsedSymbols()
{
  setup();
}

CUnit::CUnit(const CBaseUnit::Kind & kind,
             const CCopasiContainer * pParent):
  CCopasiContainer(CBaseUnit::Name[kind], pParent, "Unit"),
  mSymbol(CBaseUnit::getSymbol(kind)),
  mDefinition(CBaseUnit::getSymbol(kind)),
  mComponents(),
  mUsedSymbols()
{
  mComponents.insert(CUnitComponent(kind));
  setup();
}

// copy constructor
CUnit::CUnit(const CUnit & src,
             const C_FLOAT64 & avogadro,
             const CCopasiContainer * pParent):
  CCopasiContainer(src, pParent),
  mSymbol(src.mSymbol),
  mDefinition(),
  mComponents(),
  mUsedSymbols()
{
  setup();
  setDefinition(src.mDefinition, avogadro);
}

CUnit::~CUnit()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
}

void CUnit::setup()
{
  if(this->getObjectName() != "empty_unit")
    mKey = CCopasiRootContainer::getKeyFactory()->add("Unit", this);
}

// virtual
const std::string & CUnit::getKey() const
{
  return CAnnotation::getKey();
}

void CUnit::fromEnum(VolumeUnit volEnum)
{
  mComponents.clear();

  mSymbol = VolumeUnitNames[volEnum];

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

  mSymbol = AreaUnitNames[areaEnum];

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

  mSymbol = LengthUnitNames[lengthEnum];

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

  mSymbol = TimeUnitNames[timeEnum];

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

void CUnit::fromEnum(QuantityUnit quantityEnum)
{
  mComponents.clear();

  mSymbol = QuantityUnitNames[quantityEnum];

  if (quantityEnum == CUnit::dimensionlessQuantity)
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::item);

  const CModel * pModel = dynamic_cast<const CModel *>(getObjectAncestor("Model"));

  C_FLOAT64 usedAvogadro;

  if (pModel != NULL)
    usedAvogadro = pModel->getAvogadro();
  else
    usedAvogadro = Avogadro;

  tmpComponent.setMultiplier(usedAvogadro);

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

void CUnit::setSymbol(const std::string & symbol)
{
  mSymbol = symbol;
}

std::string CUnit::getSymbol() const
{
  return mSymbol;
}

bool CUnit::setDefinition(const std::string & definition,
                          const C_FLOAT64 & avogadro)
{
  mDefinition = definition;

  return compile(avogadro);
}

bool CUnit::compile(const C_FLOAT64 & avogadro)
{
  // parse the definition into a linked node tree
  std::istringstream buffer(mDefinition);
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

std::string CUnit::getDefinition() const
{
  return mDefinition;
}

const std::set< std::string > & CUnit::getUsedSymbols() const
{
  return mUsedSymbols;
}

// See if the component units cancel (divide to 1).
// The CUnitComponent::Kind enumerator uses only prime numbers.
// Multiplying all the components should give 1, if numerators and
// denominators have the same combination of units.
bool CUnit::isDimensionless() const
{
  // If the symbol string has been set to other than "dimensionless",
  // assume it has dimension, regardless of the components
  if (mSymbol != "dimensionless" || mSymbol != "")
    return false;

  std::set< CUnitComponent >::const_iterator it = mComponents.begin();

  double reduction = 1;

  for (; it != mComponents.end(); it++)
    {
      reduction *= pow((double)(*it).getKind(), (*it).getExponent());
    }

  // If the vector is empty, it will loop 0 times, and the reduction
  // will remain ==1 (i.e. dimensionless if no components)
  return reduction == 1;
}

void CUnit::addComponent(const CUnitComponent & component)
{
  std::set< CUnitComponent >::iterator it = mComponents.find(component);

  if (it != mComponents.end())
    {
      CUnitComponent * pComponent = const_cast< CUnitComponent * >(&*it);

      pComponent->setExponent(pComponent->getExponent() + component.getExponent());
      pComponent->setScale(pComponent->getScale() + component.getScale());
      pComponent->setMultiplier(pComponent->getMultiplier() * component.getMultiplier());
    }
  else
    {
      mComponents.insert(component);
    }
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

      pComponent->setMultiplier(pow(pComponent->getExponent(), exp));
      pComponent->setExponent(pComponent->getExponent() * exp);
    }

  return *this;
}

std::string CUnit::prefixFromScale(int scale)
{
  switch (scale)
    {
      case 3:
        return "k";  // kilo

      case 2:
        return "h";  // hecto

      case 1:
        return "da"; // deca

      case -1:
        return "d";  // deci

      case -2:
        return "c";  // centi

      case -3:
        return "m";  // milli

      case -6:
        return "\xc2\xb5";  // micro

      case -9:
        return "n";  // nano

      case -12:
        return "p";  // pico

      case -15:
        return "f";  // femto

      default:
        return "";  // anything else, including scale = 0
    }
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
  return (mSymbol == rhs.mSymbol &&
          mDefinition == rhs.mDefinition);
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

      return false;
    }

  return true;
}

// friend
std::ostream &operator<<(std::ostream &os, const CUnit & o)
{
  os << "Name: " << o.getObjectName() << ", ";
  os << "Symbol: " << o.mSymbol << ", ";
  os << "Definition: " << o.mDefinition << ", ";
  os << "Components: " << std::endl;

  std::set< CUnitComponent >::const_iterator it = o.mComponents.begin();
  std::set< CUnitComponent >::const_iterator end = o.mComponents.end();

  for (; it != end; ++it)
    {
      os << *it;
    }

  return os;
}
