// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLCurve.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/02/26 10:31:09 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CLCURVE_H_
#define CLCURVE_H_

#include <vector>

#include "CLBase.h"

class LineSegment;
class Curve;

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

    void setStart(const CLPoint & p) {mStart = p;};
    void setEnd(const CLPoint & p) {mEnd = p;};

    const CLPoint & getBase1() const {return mBase1;};
    const CLPoint & getBase2() const {return mBase2;};

    void setBase1(const CLPoint & p) {mBase1 = p;};
    void setBase2(const CLPoint & p) {mBase2 = p;};

    bool isBezier() const {return mIsBezier;};
    void setIsBezier(bool b) {mIsBezier = b;};

    void scale (const double & scaleFactor)
    {
      mStart.scale(scaleFactor);mEnd.scale(scaleFactor);
      if (mIsBezier) {mBase1.scale(scaleFactor);mBase2.scale(scaleFactor);}
    }
    /**
      * insert operator
      */
    friend std::ostream & operator<<(std::ostream &os, const CLLineSegment & ls);
  };

class CLCurve : public CLBase
  {
  protected:

    std::vector<CLLineSegment> mCurveSegments;

  public:

    CLCurve()
        : CLBase(), mCurveSegments() {};

    /**
     * copy constructor (should make deep copy)
     */
    CLCurve(const CLCurve & c);

    /**
     * constructor from libsbml object
     */
    CLCurve(const Curve & sbmlcurve);

    ~CLCurve();

    const std::vector<CLLineSegment> getCurveSegments() const {return mCurveSegments;};

    C_INT32 getNumCurveSegments() const {return mCurveSegments.size();};

    void addCurveSegment(CLLineSegment & ls);
    void addCurveSegment(CLLineSegment * pLs);

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

    void scale (const double & scaleFactor)
    {
      unsigned int i; // scale all segments
      for (i = 0;i < mCurveSegments.size();i++)
        {
          mCurveSegments[i].scale(scaleFactor);
        }
    }
    /**
      * insert operator
      */
    friend std::ostream & operator<<(std::ostream &os, const CLCurve & c);
  };

#endif
