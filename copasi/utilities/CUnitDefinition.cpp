// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <math.h>
#include <string.h>
//#include <algorithm>

#include "copasi/utilities/CUnitDefinition.h"
//#include "copasi/utilities/CUnitParser.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"
//#include "copasi/model/CModel.h"
#include "copasi/xml/CCopasiXMLInterface.h"

//#include "CCopasiException.h"

// SI Name, Symbol, Definition
struct SIUnit
{
  const char * name;
  const char * symbol;
  const char * expression;
};

SIUnit SIUnits[] =
{
  //SI base
  {"meter",      "m",        "m"},
  {"gram",       "g",        "g"},
  {"second",     "s",        "s"},
  {"ampere",     "A",        "A"},
  {"kelvin",     "K",        "K"},
  {"candela",    "cd",       "cd"},

  //SI derived
  {"Avogadro",   "Avogadro", "Avogadro"},
  {"becquerel",  "Bq",       "s^-1"},
  {"coulomb",    "C",        "s*A"},
  {"farad",      "F",        "m^-2*kg^-1*s^4*A^2"},
  {"gray",       "Gy",       "m^2*s^-2"},
  {"henry",      "H",        "m^2*kg*s^-2*A^-2"},
  {"hertz",      "Hz",       "s^-1"},
  {"joule",      "J",        "m^2*kg*s^-2"},
  {"katal",      "kat",      "s^-1*mol"},
  {"liter",      "l",        "0.001*m^3"},
  {"lumen",      "lm",       "cd"},
  {"lux",        "lx",       "m^-2*cd"},
  {"mole",       "mol",      "Avogadro*#"},
  {"newton",     "N",        "m*kg*s^-2"},
  {"ohm",        "\xCE\xA9", "m^2*kg*s^-3*A^-2"},
  {"pascal",     "Pa",       "m^-1*kg*s^-2"},
  {"rad",        "rad",      "m*m^-1"},
  {"siemens",    "S",        "m^-2*kg^-1*s^3*A^2"},
  {"sievert",    "Sv",       "m^2*s^-2"},
  {"steradian",  "sr",       "m^2*m^-2"},
  {"tesla",      "T",        "kg*s^-2*A^-1"},
  {"volt",       "V",        "m^2*kg*s^-3*A^-1"},
  {"watt",       "W",        "m^2*kg*s^-3"},
  {"weber",      "Wb",       "m^2*kg*s^-2*A^-1"},

  // Fill in some COPASI default unit options
  {"dimensionless",     "1",                 "1"},
  {"item",              "#",                 "#"},
  {"minute",            "min",               "60*s"},
  {"hour",              "h",                 "3600*s"},
  {"day",               "d",                 "86400*s"},

  // This must be the last element of the SI unit list! Do not delete!
  {NULL,         NULL,        NULL}
};

// static
CUnit CUnitDefinition::getSIUnit(const std::string & symbol)
{
  CUnit SIunit = CUnit();

  SIUnit * pSIUnit = SIUnits;

  while (pSIUnit->symbol && strcmp(pSIUnit->symbol, symbol.c_str()) != 0)
    ++pSIUnit;

  if (pSIUnit->name)
    {
      SIunit.setExpression(pSIUnit->expression);
    }

  return SIunit;
}

// static
void CUnitDefinition::updateSIUnitDefinitions(CUnitDefinitionDB * Units)
{
  SIUnit * pSIUnit = SIUnits;

  while (pSIUnit->name)
    {
      CUnitDefinition * pUnitDef = NULL;
      size_t Index = Units->getIndex(pSIUnit->name);

      if (Index != C_INVALID_INDEX)
        {
          pUnitDef = &Units->operator [](Index);
        }
      else
        {
          pUnitDef = new CUnitDefinition(pSIUnit->name, Units);
          pUnitDef->setSymbol(pSIUnit->symbol);
        }

      pUnitDef->setExpression(pSIUnit->expression);

      pSIUnit++;
    }
}

// constructors
// default
CUnitDefinition::CUnitDefinition(const std::string & name,
                                 const CCopasiContainer * pParent):
  CCopasiContainer(name, pParent, "Unit"),
  CUnit(),
  CAnnotation(),
  mSymbol("symbol")
{
  setup();
}

// kind
CUnitDefinition::CUnitDefinition(const CBaseUnit::Kind & kind,
                                 const CCopasiContainer * pParent):
  CCopasiContainer(CBaseUnit::Name[kind], pParent, "Unit"),
  CUnit(kind),
  CAnnotation(),
  mSymbol(CBaseUnit::getSymbol(kind))
{
  setup();
}

// copy
CUnitDefinition::CUnitDefinition(const CUnitDefinition &src,
                                 const CCopasiContainer * pParent):
  CCopasiContainer(src, pParent),
  CUnit(src),
  CAnnotation(src),
  mSymbol(src.mSymbol)
{
  setup();
}

CUnitDefinition::~CUnitDefinition()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);

  CCopasiContainer * pParent = getObjectParent();

  if (pParent != NULL)
    {
      pParent->remove(this);
    }
}

void CUnitDefinition::setup()
{
  CCopasiContainer * pParent = getObjectParent();

  if (pParent != NULL)
    {
      pParent->add(this, true);
    }

  mKey = CCopasiRootContainer::getKeyFactory()->add("Unit", this);

  // The following ought to trigger the exception for
  // a symbol already in the CUnitDefinitionDB
  std::ostringstream Symbol;

  Symbol.str(mSymbol.c_str());
  int i = 1;

  while (!setSymbol(Symbol.str()))
    {
      Symbol.str("");
      Symbol << mSymbol << "_" << i++;
    }
}

// virtual
const std::string & CUnitDefinition::getKey() const
{
  return CAnnotation::getKey();
}

bool CUnitDefinition::setSymbol(const std::string & symbol)
{
  CUnitDefinitionDB * pUnitDefinitionDB = dynamic_cast < CUnitDefinitionDB * >(getObjectParent());

  if (pUnitDefinitionDB == NULL ||
      pUnitDefinitionDB->changeSymbol(this, symbol))
    {
      mSymbol = symbol;

      return true;
    }

  CCopasiMessage(CCopasiMessage::ERROR, MCUnitDefinition + 2, symbol.c_str());

  return false;
}

const std::string & CUnitDefinition::getSymbol() const
{
  return mSymbol;
}

CUnitDefinition & CUnitDefinition::operator=(const CUnitDefinition & src)
{
  if (this == &src) return *this;

  // All CUnitDefinition symbols in a CUnitDefinitionDB should be unique
  // This should protect that for cases like this:
  // *aCunitDefDB[i] = someCunitDef;

  CUnitDefinitionDB * pDB = dynamic_cast < CUnitDefinitionDB * >(getObjectParent());

  if (pDB != NULL &&
      pDB->containsSymbol(src.getSymbol()) &&
      pDB->getIndex(src.getObjectName()) != C_INVALID_INDEX)
    CCopasiMessage ex(CCopasiMessage::EXCEPTION, MCUnitDefinition + 2);

  CUnit::operator = (src);

  setObjectName(src.getObjectName());
  setSymbol(src.mSymbol);

  return *this;
}

//static
bool CUnitDefinition::isBuiltinUnitSymbol(std::string symbol)
{
  SIUnit * pSIUnit = SIUnits;

  while (pSIUnit->symbol && strcmp(pSIUnit->symbol, symbol.c_str()) != 0)
    ++pSIUnit;

  return (pSIUnit->symbol != NULL);
}

bool CUnitDefinition::isReadOnly() const
{
  SIUnit * pSIUnit = SIUnits;

  while (pSIUnit->name && getObjectName() != pSIUnit->name)
    ++pSIUnit;

  return (pSIUnit->name != NULL);
}

// friend
std::ostream &operator<<(std::ostream &os, const CUnitDefinition & o)
{
  os << "Object Name: " << o.getObjectName() << ", ";
  os << "Symbol: " << o.mSymbol << ", ";
  os << static_cast< CUnit >(o);

  return os;
}
