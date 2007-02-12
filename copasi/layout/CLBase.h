// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLBase.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/12 00:03:12 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CLBASE_H_
#define CLBASE_H_

#include <copasi.h>

/**
 * This class does nothing at all at the moment.
 * Is is the base of all classes that have an equivalent in the
 * libsbml layout extension
 */
class CLBase
  {};

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

    const C_FLOAT64 & X() const {return mX;};
    const C_FLOAT64 & Y() const {return mY;};

    C_FLOAT64 & X() {return mX;};
    C_FLOAT64 & Y() {return mY;};

    //void setX(const C_FLOAT64 & x) {mX = x;};
    //void setY(const C_FLOAT64 & y) {mY = y;};

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

    const C_FLOAT64 & width() const {return mWidth;};
    const C_FLOAT64 & height() const {return mHeight;};

    C_FLOAT64 & width() {return mWidth;};
    C_FLOAT64 & height() {return mHeight;};

    //void setWidth(const C_FLOAT64 & w) {mWidth = w;};
    //void setHeight(const C_FLOAT64 & h) {mHeight = h;};

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

    const CLPoint & position() const {return mPosition;};
    const CLDimensions & dimensions() const {return mDimensions;};

    CLPoint & position() {return mPosition;};
    CLDimensions & dimensions() {return mDimensions;};

    //void setPosition(const CLPoint & p) {mPosition = p;};
    //void setDimensions(const CLDimensions & d) {mDimensions = d;};

    /**
      * insert operator
      */
    friend std::ostream & operator<<(std::ostream &os, const CLBoundingBox & bb);
  };

#endif
