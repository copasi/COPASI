// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Sven Sahle and University of Heidelberg
// All rights reserved.

#include "CSBMLunit.h"
#include <assert.h>

CSBMLunit::CSBMLunit(unsigned int sbmlLevel, unsigned int sbmlVersion)
  : mUD(UnitDefinition(sbmlLevel, sbmlVersion)),
    mSymExp(),
    mSymExpExp(0)
{
  Unit *tmp = mUD.createUnit();
  tmp->setKind(UNIT_KIND_DIMENSIONLESS);

  tmp->initDefaults();
}

CSBMLunit::CSBMLunit(const CSBMLunit & src)
  : mUD(src.mUD),
    mSymExp(src.mSymExp),
    mSymExpExp(src.mSymExpExp)
{
  //TODO verify that this does indeed do a deep copy
}

CSBMLunit::CSBMLunit(const UnitDefinition* ud)
  : mUD(*ud),
    mSymExp(),
    mSymExpExp(0)
{
}

CSBMLunit::~CSBMLunit()
{
}

std::string CSBMLunit::getDisplayString() const
{
  if (mSymExpExp == 0)
    {
      return UnitDefinition::printUnits(&mUD, true);
    }
  else if (mSymExpExp == 1)
    {
      return "(" + UnitDefinition::printUnits(&mUD, true) + ")^" + mSymExp.mID;
    }
  else
    {
      return "(" + UnitDefinition::printUnits(&mUD, true) + ")^" + mSymExp.mID + "^someExponent";
    }
}

bool CSBMLunit::multiply(const CSBMLunit & unit)
{
  if (unit.isDimensionless())
    return true;

  if (isDimensionless())
    {
      mUD = unit.mUD;
      mSymExp = unit.mSymExp;
      mSymExpExp = unit.mSymExpExp;
      return true;
    }

  if ((mSymExpExp == 0 && unit.mSymExpExp == 0)
      || ((mSymExpExp == unit.mSymExpExp) && (mSymExp.isEqual(unit.mSymExp))))
    {
      UnitDefinition tmp = unit.mUD;
      UnitDefinition * tmpPointerUD = UnitDefinition::combine(&this->mUD, &tmp);
      mUD = *tmpPointerUD;
      delete tmpPointerUD;
      return true;
    }

  // could not multiply units because of symbolic exponent !!!

  return false;
}

void CSBMLunit::invert()
{
  if (isDimensionless())
    return;

  if (mSymExpExp != 0)
    {
      // could not invert units because of symbolic exponent !!!
    }

  unsigned int i, imax = mUD.getNumUnits();

  for (i = 0; i < imax; ++i)
    mUD.getUnit(i)->setExponent(-mUD.getUnit(i)->getExponent());
}

void CSBMLunit::applyExponent(double exp)
{
  if (isDimensionless())
    return;

  if (mSymExpExp != 0)
    {
      // could not apply numeric exponent because of symbolic exponent !!!
    }

  unsigned int i, imax = mUD.getNumUnits();

  for (i = 0; i < imax; ++i)
    {
      mUD.getUnit(i)->setExponent(floor(0.5 + exp * (double)mUD.getUnit(i)->getExponent()));
    }
}

void CSBMLunit::applyExponent(const std::string& id, size_t frame)
{
  if (isDimensionless())
    return;

  if ((mSymExpExp == 0) || mSymExp.isEqual(SymbolicExponent(id, frame)))
    {
      // applied symbolic exponent
      ++mSymExpExp;
      mSymExp = SymbolicExponent(id, frame);
    }
  else
    {
      // could not apply symbolic exponent !!!
      assert(false);
    }
}

void CSBMLunit::applyInverseExponent(const std::string& id, size_t frame)
{
  if (isDimensionless())
    return;

  if ((mSymExpExp == 0) || mSymExp.isEqual(SymbolicExponent(id, frame)))
    {
      // applied inverse symbolic exponent
      --mSymExpExp;
      mSymExp = SymbolicExponent(id, frame);
    }
  else
    {
      // could not apply inverse symbolic exponent !!!
      assert(false);
    }
}

//static
bool CSBMLunit::isEqual(const CSBMLunit & unit1, const CSBMLunit & unit2)
{
  if (unit1.isDimensionless() && unit2.isDimensionless())
    return true;

  if (((unit1.mSymExpExp == 0) && (unit2.mSymExpExp == 0))
      || (unit1.mSymExp.isEqual(unit2.mSymExp) && (unit1.mSymExpExp == unit2.mSymExpExp)))
    {
      return UnitDefinition::areEquivalent(&unit1.mUD, &unit2.mUD);
    }
  else
    {
      return false;
    }
}

bool CSBMLunit::isDimensionless() const
{
  return mUD.isVariantOfDimensionless();
}

//************************************************

CSBMLunitInformation::CSBMLunitInformation(unsigned int sbmlLevel, unsigned int sbmlVersion)
  : CSBMLunit(sbmlLevel, sbmlVersion),
    mInfo(UNKNOWN),
    mConflict(false)
{
}

CSBMLunitInformation::CSBMLunitInformation(unsigned int sbmlLevel, unsigned int sbmlVersion, INFO info, bool conflict)
  : CSBMLunit(sbmlLevel, sbmlVersion),
    mInfo(info),
    mConflict(conflict)
{
}

CSBMLunitInformation::CSBMLunitInformation(const CSBMLunit& u, INFO info, bool conflict)
  : CSBMLunit(u),
    mInfo(info),
    mConflict(conflict)
{
}

CSBMLunitInformation::CSBMLunitInformation(const UnitDefinition* ud, INFO info, bool conflict)
  : CSBMLunit(ud),
    mInfo(info),
    mConflict(conflict)
{
}

std::string CSBMLunitInformation::getDisplayString() const
{
  std::string sss;

  switch (mInfo)
    {
      case UNKNOWN:
        sss += "unknown";
        break;

      case DEFAULT:
        sss += "default:  " + CSBMLunit::getDisplayString();
        break;

      case GLOBAL:
        sss += "global:  " + CSBMLunit::getDisplayString();
        break;

      case PROVIDED:
        sss += "provided:  " + CSBMLunit::getDisplayString();
        break;

      case DERIVED:
        sss += "derived:  " + CSBMLunit::getDisplayString();
        break;
    };

  if (mConflict)
    sss  += "!!!Conflict!!!";

  return sss;
}

//static
bool CSBMLunitInformation::isEqual(const CSBMLunitInformation & unit1, const CSBMLunitInformation & unit2)
{
  if (unit1.mInfo == unit2.mInfo && unit1.mConflict == unit2.mConflict)
    return CSBMLunit::isEqual(unit1, unit2);
  else
    return false;
}
