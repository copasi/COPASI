// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLCurve.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/16 10:13:26 $
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

  public:

    CLLineSegment()
        : mStart(), mEnd() {};

    CLLineSegment(const CLPoint & s, const CLPoint & e)
        : mStart(s), mEnd(e) {};

    /**
     * constructor from libsbml object
     */
    CLLineSegment(const LineSegment & ls);

    const CLPoint & getStart() const {return mStart;};
    const CLPoint & getEnd() const {return mEnd;};

    void setStart(const CLPoint & p) {mStart = p;};
    void setEnd(const CLPoint & p) {mEnd = p;};

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

    const std::vector<CLLineSegment> getCurveSegments() {return mCurveSegments;};

    C_INT32 getNumCurveSegments() const {return mCurveSegments.size();};

    void addCurveSegment(CLLineSegment & ls);
  };

#endif
