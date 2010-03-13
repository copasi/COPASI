// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/04/11 15:21:36 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Sven Sahle and University of Heidelberg
// All rights reserved.

#include "CUnit.h"
#include <assert.h>

CUnit::CUnit(unsigned int sbmlLevel, unsigned int sbmlVersion)
    : mUD(UnitDefinition(sbmlLevel, sbmlVersion)),
    mSymExp(),
    mSymExpExp(0)
{
  Unit *tmp = mUD.createUnit();
  tmp->setKind(UNIT_KIND_DIMENSIONLESS);
}

CUnit::CUnit(const CUnit & src)
    : mUD(src.mUD),
    mSymExp(src.mSymExp),
    mSymExpExp(src.mSymExpExp)
{
  //TODO verify that this does indeed do a deep copy
}

CUnit::CUnit(const UnitDefinition* ud)
    : mUD(*ud),
    mSymExp(),
    mSymExpExp(0)
{
}

CUnit::~CUnit()
{
}

std::string CUnit::getDisplayString() const
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

bool CUnit::multiply(const CUnit & unit)
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

void CUnit::invert()
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

void CUnit::applyExponent(double exp)
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
      mUD.getUnit(i)->setExponent(floor(0.5 + exp*(double)mUD.getUnit(i)->getExponent()));
    }
}

void CUnit::applyExponent(const std::string& id, int frame)
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

void CUnit::applyInverseExponent(const std::string& id, int frame)
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
bool CUnit::isEqual(const CUnit & unit1, const CUnit & unit2)
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

bool CUnit::isDimensionless() const
{
  return mUD.isVariantOfDimensionless();
}

//************************************************

CUnitInformation::CUnitInformation(unsigned int sbmlLevel, unsigned int sbmlVersion)
    : CUnit(sbmlLevel, sbmlVersion),
    mInfo(UNKNOWN),
    mConflict(false)
{
}

CUnitInformation::CUnitInformation(unsigned int sbmlLevel, unsigned int sbmlVersion, INFO info, bool conflict)
    : CUnit(sbmlLevel, sbmlVersion),
    mInfo(info),
    mConflict(conflict)
{
}

CUnitInformation::CUnitInformation(const CUnit& u, INFO info, bool conflict)
    : CUnit(u),
    mInfo(info),
    mConflict(conflict)
{
}

CUnitInformation::CUnitInformation(const UnitDefinition* ud, INFO info, bool conflict)
    : CUnit(ud),
    mInfo(info),
    mConflict(conflict)
{
}

std::string CUnitInformation::getDisplayString() const
{
  std::string sss;

  switch (mInfo)
    {
      case UNKNOWN:
        sss += "unknown";
        break;
      case DEFAULT:
        sss += "default:  " + CUnit::getDisplayString();
        break;
      case GLOBAL:
        sss += "global:  " + CUnit::getDisplayString();
        break;
      case PROVIDED:
        sss += "provided:  " + CUnit::getDisplayString();
        break;
      case DERIVED:
        sss += "derived:  " + CUnit::getDisplayString();
        break;
    };

  if (mConflict)
    sss  += "!!!Conflict!!!";

  return sss;
}

//static
bool CUnitInformation::isEqual(const CUnitInformation & unit1, const CUnitInformation & unit2)
{
  if (unit1.mInfo == unit2.mInfo && unit1.mConflict == unit2.mConflict)
    return CUnit::isEqual(unit1, unit2);
  else
    return false;
}
