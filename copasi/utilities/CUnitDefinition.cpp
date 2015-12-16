// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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

#include "CCopasiException.h"

// SI Name, Symbol, Definition
struct SIUnit
{
  const char * name;
  const char * symbol;
  const char * expression;
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

CUnitDefinition CUnitDefinition::getSIUnitDefinition(const std::string & symbol,
                       const C_FLOAT64 & avogadro)
{
  SIUnit * pSIUnit = SIUnits;

  while (pSIUnit->name && strcmp(pSIUnit->symbol, symbol.c_str()) != 0)
    ++pSIUnit;

  if (!pSIUnit->name)
    fatalError();

  std::ostringstream buffer;

  if (strcmp(pSIUnit->symbol, "mol"))
    {
      buffer << pSIUnit->expression;
    }
  else
    {
      buffer << CCopasiXMLInterface::DBL(avogadro) << "*#";
    }

  CUnitDefinition SIunit = CUnitDefinition();

  SIunit.setObjectName(pSIUnit->name);
  SIunit.setSymbol(pSIUnit->symbol);
  SIunit.setExpression(buffer.str(), avogadro);

  return SIunit;
}

// static
void CUnitDefinition::updateSIUnitDefinitions(CCopasiVectorN< CUnitDefinition > & Units,
                          const C_FLOAT64 & avogadro)
{
  SIUnit * pSIUnit = SIUnits;

  while (pSIUnit->name)
    {
      CUnitDefinition * pUnitDef = NULL;
      size_t Index = Units.getIndex(pSIUnit->name);

      if (Index != C_INVALID_INDEX)
        {
          pUnitDef = Units[Index];
        }
      else
        {
          pUnitDef = new CUnitDefinition();

          pUnitDef->setObjectName(pSIUnit->name);
          pUnitDef->setSymbol(pSIUnit->symbol);
          Units.add(pUnitDef, true);
        }

      std::ostringstream buffer;

      if (strcmp(pSIUnit->symbol, "mol"))
        {
          buffer << pSIUnit->expression;
        }
      else
        {
          buffer << CCopasiXMLInterface::DBL(avogadro) << "*#";
        }

      pUnitDef->setExpression(buffer.str(), avogadro);

      pSIUnit++;
    }
}

// constructors
// default
CUnitDefinition::CUnitDefinition(const std::string & name,
             const CCopasiContainer * pParent):
  CCopasiContainer(name, pParent, "Unit"),
  mSymbol("none")
{
  setup();
}

// kind
CUnitDefinition::CUnitDefinition(const CBaseUnit::Kind & kind,
             const CCopasiContainer * pParent):
  CCopasiContainer(CBaseUnit::Name[kind], pParent, "Unit"),
  mSymbol(CBaseUnit::getSymbol(kind)),
  CUnit(kind)
{
  setup();
}

// copy
CUnitDefinition::CUnitDefinition(const CUnitDefinition &src,
             const C_FLOAT64 & avogadro,
             const CCopasiContainer * pParent):
  CUnit(src, avogadro),
  CCopasiContainer(src, pParent),
  mSymbol(src.mSymbol)
{
  setup();
}

CUnitDefinition::~CUnitDefinition()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
}

void CUnitDefinition::setup()
{
  mKey = CCopasiRootContainer::getKeyFactory()->add("Unit", this);
}

// virtual
const std::string & CUnitDefinition::getKey() const
{
  return CAnnotation::getKey();
}

void CUnitDefinition::setSymbol(const std::string & symbol)
{
  mSymbol = symbol;
}

std::string CUnitDefinition::getSymbol() const
{
  return mSymbol;
}
