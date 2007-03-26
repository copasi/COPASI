// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLBase.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/03/26 10:55:06 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CLBASE_H_
#define CLBASE_H_

#include <copasi.h>

class SBase;

class BoundingBox;
class Dimensions;
class Point;

/**
 * This class does nothing at all at the moment.
 * Is is the base of all classes that have an equivalent in the
 * libsbml layout extension
 */
class CLBase
  {
  public:
    CLBase() {};
    CLBase(const CLBase &) {};
    CLBase(const SBase &) {};
  };

/**
 * This class describes a Point in a layout
 * It is 2-dimensional at the moment
 */
class CLPoint : public CLBase
  {
  protected:

    C_FLOAT64 mX, mY;

  public:

    CLPoint()
        : mX(0), mY(0) {};

    CLPoint(const C_FLOAT64 & x, const C_FLOAT64 & y)
        : mX(x), mY(y) {};

    /**
     * constructor from libsbml object
     */
    CLPoint(const Point& p);

    const C_FLOAT64 & getX() const {return mX;};
    const C_FLOAT64 & getY() const {return mY;};

    C_FLOAT64 & getX() {return mX;};
    C_FLOAT64 & getY() {return mY;};

    void setX(const C_FLOAT64 & x) {mX = x;};
    void setY(const C_FLOAT64 & y) {mY = y;};

    void scale (const double & scaleFactor){mX *= scaleFactor;mY *= scaleFactor;}

    bool operator==(const CLPoint & rhs) const
      {return (mX == rhs.mX) && (mY == rhs.mY);};

    // sort columnwise, point p1 is < point p2 if x-component is <, if x es are equal, check for y
    bool operator<(const CLPoint & rhs) const
      {
        if (mX == rhs.mX)
          return (mY < rhs.mY);
        else
          return (mX < rhs.mX);
      };

    /**
      * insert operator
      */
    friend std::ostream & operator<<(std::ostream &os, const CLPoint & p);
  };

/**
 * This class describes a size in a layout.
 * It is 2-dimensional at the moment.
 */
class CLDimensions : public CLBase
  {
  protected:

    C_FLOAT64 mWidth, mHeight;

  public:

    CLDimensions()
        : mWidth(0), mHeight(0) {};

    CLDimensions(const C_FLOAT64 & w, const C_FLOAT64 & h)
        : mWidth(w), mHeight(h) {};

    /**
     * constructor from libsbml object
     */
    CLDimensions(const Dimensions& d);

    const C_FLOAT64 & getWidth() const {return mWidth;};
    const C_FLOAT64 & getHeight() const {return mHeight;};

    C_FLOAT64 & getWidth() {return mWidth;};
    C_FLOAT64 & getHeight() {return mHeight;};

    void setWidth(const C_FLOAT64 & w) {mWidth = w;};
    void setHeight(const C_FLOAT64 & h) {mHeight = h;};

    void scale (const double & scaleFactor){mWidth *= scaleFactor;mHeight *= scaleFactor;}

    /**
      * insert operator
      */
    friend std::ostream & operator<<(std::ostream &os, const CLDimensions & d);
  };

/**
 * This class describes a bounding box.
 */
class CLBoundingBox : public CLBase
  {
  protected:

    CLPoint mPosition;

    CLDimensions mDimensions;

  public:

    CLBoundingBox()
        : mPosition(), mDimensions() {};

    CLBoundingBox(const CLPoint & p, const CLDimensions & d)
        : mPosition(p), mDimensions(d) {};

    /**
     * constructor from libsbml object
     */
    CLBoundingBox(const BoundingBox & bb);

    const CLPoint & getPosition() const {return mPosition;};
    const CLDimensions & getDimensions() const {return mDimensions;};

    CLPoint & getPosition() {return mPosition;};
    CLDimensions & getDimensions() {return mDimensions;};

    void setPosition(const CLPoint & p) {mPosition = p;};
    void setDimensions(const CLDimensions & d) {mDimensions = d;};

    void scale (const double & scaleFactor){mPosition.scale(scaleFactor);mDimensions.scale(scaleFactor);}

    /**
      * insert operator
      */
    friend std::ostream & operator<<(std::ostream &os, const CLBoundingBox & bb);
  };

#endif
