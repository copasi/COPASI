// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include "copasi/utilities/CUnit.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"

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
CUnit::CUnit():
  CCopasiContainer("NoName", NULL, "Unit")
{
  mSymbol = "";
  setup();
}

CUnit::CUnit(VolumeUnit volEnum):
  CCopasiContainer("NoName", NULL, "Unit")
{
  mSymbol = VolumeUnitNames[volEnum];
  setup();
}

CUnit::CUnit(AreaUnit areaEnum):
  CCopasiContainer("NoName", NULL, "Unit")
{
  mSymbol = AreaUnitNames[areaEnum];
  setup();
}

CUnit::CUnit(LengthUnit lengthEnum):
  CCopasiContainer("NoName", NULL, "Unit")
{
  mSymbol = LengthUnitNames[lengthEnum];
  setup();
}

CUnit::CUnit(TimeUnit timeEnum):
  CCopasiContainer("NoName", NULL, "Unit")
{
  mSymbol = TimeUnitNames[timeEnum];
  setup();
}

CUnit::CUnit(QuantityUnit quantityEnum):
  CCopasiContainer("NoName", NULL, "Unit")
{
  mSymbol = QuantityUnitNames[quantityEnum];
  setup();
}

void CUnit::setup()
{
  mKey = CCopasiRootContainer::getKeyFactory()->add("Unit", this);

  mDimensionless = false; // reasonable default

  if (mSymbol == "dimensionless")  //TODO: base this on components analysis
    mDimensionless = true;
}

void CUnit::setSymbol(std::string symbol)
{
  mSymbol = symbol;
}

std::string CUnit::getSymbol() const
{
  return mSymbol;
}

bool CUnit::isDimensionless() const
{
  return mDimensionless;
}

//bool CUnit::componentsAreDimensionless() const
//{
//  will process the mKind enums of the components
//}
