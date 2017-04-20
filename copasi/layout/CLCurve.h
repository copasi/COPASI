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

#ifndef CLCURVE_H_
#define CLCURVE_H_

#include <vector>
#include <map>

#include "copasi/layout/CLBase.h"
#include "copasi/core/CDataObject.h"

class CDataObject;

LIBSBML_CPP_NAMESPACE_BEGIN
class LineSegment;
class Curve;
class CubicBezier;
class LineSegment;
LIBSBML_CPP_NAMESPACE_END

/**
 * This class describes a line segment.
 */
class CLLineSegment : public CLBase
{
protected:

  CLPoint mStart;
  CLPoint mEnd;

  CLPoint mBase1;
  CLPoint mBase2;

  bool mIsBezier;

public:

  CLLineSegment()
    : mStart(), mEnd(),
      mBase1(), mBase2(),
      mIsBezier(false) {};

  /**
   * Constructor for a straight line segment
   */
  CLLineSegment(const CLPoint & s, const CLPoint & e)
    : mStart(s), mEnd(e),
      mBase1(), mBase2(),
      mIsBezier(false) {};

  /**
   * Constructor for a bezier segment
   */
  CLLineSegment(const CLPoint & s, const CLPoint & e,
                const CLPoint & b1, const CLPoint & b2)
    : mStart(s), mEnd(e),
      mBase1(b1), mBase2(b2),
      mIsBezier(true) {};

  /**
   * constructor from libsbml object
   */
  CLLineSegment(const LineSegment & ls);

  const CLPoint & getStart() const {return mStart;};
  const CLPoint & getEnd() const {return mEnd;};
  CLPoint & getStart() {return mStart;};
  CLPoint & getEnd() {return mEnd;};

  void setStart(const CLPoint & p) {mStart = p;};
  void setEnd(const CLPoint & p) {mEnd = p;};

  const CLPoint & getBase1() const {return mBase1;};
  const CLPoint & getBase2() const {return mBase2;};
  CLPoint & getBase1() {return mBase1;};
  CLPoint & getBase2() {return mBase2;};

  void setBase1(const CLPoint & p) {mBase1 = p;};
  void setBase2(const CLPoint & p) {mBase2 = p;};

  bool isBezier() const {return mIsBezier;};
  void setIsBezier(bool b) {mIsBezier = b;};

  // if two lines are congruent, they are supposed to be ==
  bool operator==(const CLLineSegment & rhs) const
  {
    if (mIsBezier) return ((mStart == rhs.mStart) && (mEnd == rhs.mEnd) && (mBase1 == rhs.mBase1) && (mBase2 == rhs.mBase2));
    else return ((mStart == rhs.mStart) && (mEnd == rhs.mEnd));
  };

  // compare two line segments according to their start point (needed for use of line segment as a key in a map)
  bool operator<(const CLLineSegment & rhs) const
  {return (mStart < rhs.mStart);};

  void scale(const double & scaleFactor)
  {
    mStart.scale(scaleFactor); mEnd.scale(scaleFactor);

    if (mIsBezier) {mBase1.scale(scaleFactor); mBase2.scale(scaleFactor);}
  }

  /**
   * This method writes the information of the copasi layout object into the
   * corresponding sbml object. This is only guaranteed to work if
   * isBezier() is true.
   */
  void exportToSBMLBezier(CubicBezier * c, const std::map<const CDataObject*, SBase*> & copasimodelmap) const;

  /**
   * This method writes the information of the copasi layout object into the
   * corresponding sbml object. This is only guaranteed to work if
   * isBezier() is false.
   */
  void exportToSBMLLineSegment(LineSegment * l, const std::map<const CDataObject*, SBase*> & copasimodelmap) const;

  /**
    * insert operator
    */
  friend std::ostream & operator<<(std::ostream &os, const CLLineSegment & ls);
};

class CLCurve : public CLBase
{
protected:

  std::vector<CLLineSegment> mvCurveSegments;

public:

  CLCurve()
    : CLBase(), mvCurveSegments() {};

  /**
   * copy constructor (should make deep copy)
   */
  CLCurve(const CLCurve & c);

  /**
   * constructor from libsbml object
   */
  CLCurve(const Curve & sbmlcurve);

  ~CLCurve();

  const std::vector<CLLineSegment> & getCurveSegments() const {return mvCurveSegments;};

  const CLLineSegment* getSegmentAt(size_t i) const
  {
    if (i < mvCurveSegments.size())return &(mvCurveSegments[i]);
    else return NULL;
  }

  CLLineSegment* getSegmentAt(size_t i)
  {
    if (i < mvCurveSegments.size())return &(mvCurveSegments[i]);
    else return NULL;
  }

  size_t getNumCurveSegments() const {return mvCurveSegments.size();};

  void clear();

  /**
   * add a copy of the line segment to the curve
   */
  void addCurveSegment(const CLLineSegment & ls);

  /**
   * add a copy of the line segment to the curve
   */
  void addCurveSegment(const CLLineSegment * pLs);

  /**
   * this method tells whether the curve is a continuous
   * set of line segments, i.e. if the end point of one
   * line segment is identical to the starting point of the
   * following one.
   */
  bool isContinuous() const;

  /**
   * This method should only be called if isContinuous() is true.
   * It returns the curve as a list of points rather than a list
   * of line segments.
   */
  std::vector <CLPoint> getListOfPoints() const;

  /**
   * Two curves are supposed to be equal iff all there line segments
   * including their order are equal
   */
  bool operator==(const CLCurve & rhs) const
  {
    bool result = true;
    unsigned int i;

    for (i = 0; i < mvCurveSegments.size(); i++)
      {
        result = result && (mvCurveSegments[i] == rhs.mvCurveSegments[i]);
      }

    return result;
  }

  void scale(const double & scaleFactor)
  {
    unsigned int i; // scale all segments

    for (i = 0; i < mvCurveSegments.size(); i++)
      {
        mvCurveSegments[i].scale(scaleFactor);
      }
  }

  /**
   * This method writes the information of the copasi layout object into the
   * corresponding sbml object
   */
  void exportToSBML(Curve * c, const std::map<const CDataObject*, SBase*> & copasimodelmap) const;

  /**
   * Calculates the bounding box for the curve.
   * Basepoints for cubic beziers are considered to belong inside the bounding
   * box.
   */
  CLBoundingBox calculateBoundingBox() const;

  virtual void moveBy(const CLPoint &p);

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CLCurve & c);
};

#endif
