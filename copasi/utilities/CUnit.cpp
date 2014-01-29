// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include <math.h>

#include "copasi/utilities/CUnit.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"

#include <algorithm>

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
}

void CUnit::setSymbol(std::string symbol)
{
  mSymbol = symbol;
}

std::string CUnit::getSymbol() const
{
  return mSymbol;
}

// See if the component units cancel (divide to 1).
// The CUnitComponent::Kind enumerator uses only prime numbers.
// Multiplying all the components should give 1, if numerators and
// denominators have the same combination of units.
bool CUnit::isDimensionless() const
{
  // If the symbol string has been set to other than "dimensionless",
  // assume it has dimension, regardless of the components
  if(mSymbol != "dimensionless" || mSymbol != "")
    return false;

  std::vector< CUnitComponent >::const_iterator it = mComponents.begin();

  double reduction = 1;

  for (; it != mComponents.end(); it++)
    {
      reduction *= pow((double)(*it).getKind(), (*it).getExponent());
    }

  // If the vector is empy, it will loop 0 times, and the reduction
  // will remain ==1 (i.e. dimensionless if no components)
  return reduction == 1;
}

void CUnit::addComponent(const CUnitComponent & component)
{
  mComponents.push_back(component);
}

bool CUnit::simplifyComponents()
{
  if (mComponents.size() < 2)
    return false;

  std::vector< CUnitComponent > replacementVector;
  std::vector< CUnitComponent >::const_iterator it = mComponents.begin();
  CUnitComponent tempComponent;
  bool didSimplify = false;

  std::sort(mComponents.begin(), mComponents.end()); // make same Kinds adjacent

  for (; it != mComponents.end(); it++)
    {
      tempComponent = (*it);

      while (it != mComponents.end() && tempComponent.getKind() == (*(it + 1)).getKind())
        {
          tempComponent.setExponent((tempComponent.getExponent()) + (*(it + 1)).getExponent());
          tempComponent.setScale(tempComponent.getScale() + (*(it + 1)).getScale());
          tempComponent.setMultiplier(tempComponent.getMultiplier() * (*(it + 1)).getMultiplier());
          didSimplify = true;
          it++;
        }

      replacementVector.push_back(tempComponent);
    }

  if (didSimplify)
    {
      mComponents = replacementVector;
    }

  return didSimplify;
}
