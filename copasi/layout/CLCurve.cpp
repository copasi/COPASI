// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#define USE_LAYOUT 1

#include <sbml/packages/layout/sbml/Curve.h>
#include <sbml/packages/layout/sbml/CubicBezier.h>

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

void CLLineSegment::exportToSBMLBezier(CubicBezier * c, const std::map<const CDataObject*, SBase*> & copasimodelmap) const
{
  if (!c) return;

  //first the part that is inherited from line segment
  exportToSBMLLineSegment(c, copasimodelmap);

  //now the rest
  c->setBasePoint1(this->getBase1().getX(), this->getBase1().getY());
  c->setBasePoint2(this->getBase2().getX(), this->getBase2().getY());
}

void CLLineSegment::exportToSBMLLineSegment(LineSegment * l,
    const std::map<const CDataObject*, SBase*> & /* copasimodelmap */) const
{
  if (!l) return;

  l->setStart(this->getStart().getX(), this->getStart().getY());
  l->setEnd(this->getEnd().getX(), this->getEnd().getY());
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
    mvCurveSegments(c.mvCurveSegments)
{}

CLCurve::CLCurve(const Curve & sbmlcurve)
  : CLBase(sbmlcurve),
    mvCurveSegments()
{
  //TODO
  C_INT32 i, imax = sbmlcurve.getListOfCurveSegments()->size();

  for (i = 0; i < imax; ++i)
    {
      const LineSegment* tmp
        = dynamic_cast<const LineSegment*>(sbmlcurve.getListOfCurveSegments()->get(i));

      if (tmp)
        mvCurveSegments.push_back(CLLineSegment(*tmp));

      //addCurveSegment(CLLineSegment(*tmp));
    }
}

CLCurve::~CLCurve()
{}

void CLCurve::addCurveSegment(const CLLineSegment & ls)
{
  mvCurveSegments.push_back(ls);
}

void CLCurve::addCurveSegment(const CLLineSegment * pLs)
{
  if (pLs)
    mvCurveSegments.push_back(*pLs);
}

void CLCurve::clear()
{
  mvCurveSegments.clear();
}

bool CLCurve::isContinuous() const
{
  if (mvCurveSegments.size() <= 1) return true;

  size_t i, imax = mvCurveSegments.size() - 1;

  for (i = 0; i < imax; ++i)
    if (!(mvCurveSegments[i].getEnd() == mvCurveSegments[i + 1].getStart()))
      return false;

  return true;
}

std::vector <CLPoint> CLCurve::getListOfPoints() const
{
  std::vector <CLPoint> ret;

  if (mvCurveSegments.size() == 0) return ret;

  if (!isContinuous()) return ret;

  size_t i, imax = mvCurveSegments.size();

  for (i = 0; i < imax; ++i)
    ret.push_back(mvCurveSegments[i].getStart());

  ret.push_back(mvCurveSegments[i - 1].getEnd());

  return ret;
}

void CLCurve::exportToSBML(Curve * c, const std::map<const CDataObject*, SBase*> & copasimodelmap) const
{
  if (!c) return;

  //we will reconstruct the curve completely without checking the existing curve
  size_t i, imax = c->getListOfCurveSegments()->size();

  for (i = 0; i < imax; ++i) delete c->getListOfCurveSegments()->remove(0);

  //curve segments
  imax = mvCurveSegments.size();

  for (i = 0; i < imax; ++i)
    {
      if (mvCurveSegments[i].isBezier())
        {
          mvCurveSegments[i].exportToSBMLBezier(c->createCubicBezier(), copasimodelmap);
        }
      else
        {
          mvCurveSegments[i].exportToSBMLLineSegment(c->createLineSegment(), copasimodelmap);
        }
    }
}

std::ostream & operator<<(std::ostream &os, const CLCurve & c)
{
  if (c.getNumCurveSegments())
    {
      os << "      Curve:\n";
      size_t i, imax = c.getNumCurveSegments();

      for (i = 0; i < imax; ++i)
        os << "        " << c.getCurveSegments()[i] << "\n";
    }

  return os;
}

void CLCurve::moveBy(const CLPoint &p)
{
  CLLineSegment* pLS = NULL;
  CLPoint* pP = NULL;
  size_t i, iMax = this->getNumCurveSegments();

  for (i = 0; i < iMax; ++i)
    {
      pLS = this->getSegmentAt(i);
      pP = &pLS->getStart();
      pP->moveBy(p);

      pP = &pLS->getEnd();
      pP->moveBy(p);

      if (pLS->isBezier())
        {
          pP = &pLS->getBase1();
          pP->moveBy(p);

          pP = &pLS->getBase2();
          pP->moveBy(p);
        }
    }
}

/**
 * Calculates the bounding box for the curve.
 * Basepoints for cubic beziers are considered to belong inside the bounding
 * box.
 */
CLBoundingBox CLCurve::calculateBoundingBox() const
{
  double xMin = std::numeric_limits<double>::max();
  double yMin = xMin;
  double xMax = -xMin;
  double yMax = -xMin;
  double x, y;
  size_t i, iMax = this->getNumCurveSegments();
  const CLLineSegment* pLS = NULL;
  const CLPoint* pP = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pLS = this->getSegmentAt(i);
      pP = &pLS->getStart();
      x = pP->getX();
      y = pP->getY();
      xMin = (xMin < x) ? xMin : x;
      yMin = (yMin < y) ? yMin : y;
      xMax = (xMax > x) ? xMax : x;
      yMax = (yMax > y) ? yMax : y;
      pP = &pLS->getEnd();
      x = pP->getX();
      y = pP->getY();
      xMin = (xMin < x) ? xMin : x;
      yMin = (yMin < y) ? yMin : y;
      xMax = (xMax > x) ? xMax : x;
      yMax = (yMax > y) ? yMax : y;

      if (pLS->isBezier())
        {
          pP = &pLS->getBase1();
          x = pP->getX();
          y = pP->getY();
          xMin = (xMin < x) ? xMin : x;
          yMin = (yMin < y) ? yMin : y;
          xMax = (xMax > x) ? xMax : x;
          yMax = (yMax > y) ? yMax : y;
          pP = &pLS->getBase2();
          x = pP->getX();
          y = pP->getY();
          xMin = (xMin < x) ? xMin : x;
          yMin = (yMin < y) ? yMin : y;
          xMax = (xMax > x) ? xMax : x;
          yMax = (yMax > y) ? yMax : y;
        }
    }

  return CLBoundingBox(CLPoint(xMin, yMin), CLDimensions(xMax - xMin, yMax - yMin));
}
