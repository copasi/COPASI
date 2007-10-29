// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLCurve.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/10/29 13:17:17 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#define USE_LAYOUT 1

#include <sbml/layout/Curve.h>
#include <sbml/layout/CubicBezier.h>

#include "CLCurve.h"

CLLineSegment::CLLineSegment(const LineSegment & ls)
    : CLBase(ls),
    mStart(*ls.getStart()),
    mEnd(*ls.getEnd()),
    mBase1(),
    mBase2(),
    mIsBezier(false)
{
  //handle bezier
  const CubicBezier * cb = dynamic_cast<const CubicBezier *>(&ls);
  if (cb)
    {
      mIsBezier = true;
      mBase1 = CLPoint(*cb->getBasePoint1());
      mBase2 = CLPoint(*cb->getBasePoint2());
    }
}

std::ostream & operator<<(std::ostream &os, const CLLineSegment & ls)
{
  os << "[" << ls.mStart << "->" << ls.mEnd << "]";
  if (ls.mIsBezier)
    os << "  " << ls.mBase1 << ", " << ls.mBase2;
  return os;
}

//****************************************************

CLCurve::CLCurve(const CLCurve & c)
    : CLBase(c),
    mCurveSegments(c.mCurveSegments)
{}

CLCurve::CLCurve(const Curve & sbmlcurve)
    : CLBase(sbmlcurve),
    mCurveSegments()
{
  //TODO
  C_INT32 i, imax = sbmlcurve.getListOfCurveSegments()->size();
  for (i = 0; i < imax; ++i)
    {
      const LineSegment* tmp
      = dynamic_cast<const LineSegment*>(sbmlcurve.getListOfCurveSegments()->get(i));
      if (tmp)
        addCurveSegment(new CLLineSegment(*tmp));
    }
}

std::vector<CLLineSegment*> mCurveSegments;

CLCurve::~CLCurve()
{}

void CLCurve::addCurveSegment(CLLineSegment & ls)
{
  mCurveSegments.push_back(ls);
}

void CLCurve::addCurveSegment(CLLineSegment * pLs)
{
  if (pLs)
    mCurveSegments.push_back(*pLs);
}

void CLCurve::clear()
{
  mCurveSegments.clear();
}

bool CLCurve::isContinuous() const
  {
    if (mCurveSegments.size() <= 1) return true;

    C_INT32 i, imax = mCurveSegments.size() - 1;
    for (i = 0; i < imax; ++i)
      if (!(mCurveSegments[i].getEnd() == mCurveSegments[i + 1].getStart()))
        return false;
    return true;
  }

std::vector <CLPoint> CLCurve::getListOfPoints() const
  {
    std::vector <CLPoint> ret;
    if (mCurveSegments.size() == 0) return ret;
    if (!isContinuous()) return ret;

    C_INT32 i, imax = mCurveSegments.size();
    for (i = 0; i < imax; ++i)
      ret.push_back(mCurveSegments[i].getStart());
    ret.push_back(mCurveSegments[i - 1].getEnd());

    return ret;
  }

std::ostream & operator<<(std::ostream &os, const CLCurve & c)
{
  if (c.getNumCurveSegments())
    {
      os << "      Curve:\n";
      C_INT32 i, imax = c.getNumCurveSegments();
      for (i = 0; i < imax; ++i)
        os << "        " << c.getCurveSegments()[i] << "\n";
    }
  return os;
}
