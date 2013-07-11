// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CLBASE_H_
#define CLBASE_H_

#include "copasi.h"

class SBase;

class BoundingBox;
class Dimensions;
class Point;
class CLPoint;

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
  // make CLBase polymorphic so that we can dynamic cast from CLBase to
  // CLGraphicalObject
  virtual ~CLBase() {};
  virtual void moveBy(const CLPoint &p) {};
};

/**
 * This class describes a Point in a layout
 * It is 2-dimensional at the moment
 */
class CLPoint : public CLBase
{
protected:

  C_FLOAT64 mX, mY;
#ifdef USE_CRENDER_EXTENSION
  C_FLOAT64 mZ;
#endif // USE_CRENDER_EXTENSION

public:

  CLPoint():
    mX(0.0)
    , mY(0.0)
#ifdef USE_CRENDER_EXTENSION
    , mZ(0.0)
#endif // USE_CRENDER_EXTENSION
  {};

  CLPoint(const C_FLOAT64 & x
          , const C_FLOAT64 & y
#ifdef USE_CRENDER_EXTENSION
          , const C_FLOAT64 & z = 0.0
#endif // USE_CRENDER_EXTENSION
         ):
    mX(x)
    , mY(y)
#ifdef USE_CRENDER_EXTENSION
    , mZ(z)
#endif // USE_CRENDER_EXTENSION
  {};

  /**
   * constructor from libsbml object
   */
  CLPoint(const Point& p);

  const C_FLOAT64 & getX() const {return mX;};
  const C_FLOAT64 & getY() const {return mY;};
#ifdef USE_CRENDER_EXTENSION
  const C_FLOAT64 & getZ() const {return mZ;};
#endif // USE_CRENDER_EXTENSION

  C_FLOAT64 & getX() {return mX;};
  C_FLOAT64 & getY() {return mY;};
#ifdef USE_CRENDER_EXTENSION
  C_FLOAT64 & getZ() {return mZ;};
#endif // USE_CRENDER_EXTENSION

  void setX(const C_FLOAT64 & x) {mX = x;};
  void setY(const C_FLOAT64 & y) {mY = y;};
#ifdef USE_CRENDER_EXTENSION
  void setZ(const C_FLOAT64 & z) {mZ = z;};
#endif // USE_CRENDER_EXTENSION

  void scale(const double & scaleFactor) {mX *= scaleFactor; mY *= scaleFactor;}

  bool operator==(const CLPoint & rhs) const
  {
    bool result = (mX == rhs.mX) && (mY == rhs.mY);
#ifdef USE_CRENDER_EXTENSION
    result &= mZ == rhs.mZ;
#endif // USE_CRENDER_EXTENSION
    return result;
  };

  CLPoint operator-(const CLPoint & rhs) const
  {
    return CLPoint(this->mX - rhs.mX,
                   this->mY - rhs.mY
#ifdef USE_CRENDER_EXTENSION
                   , this->mZ - rhs.mZ
#endif // USE_CRENDER_EXTENSION
                  );
  };

  CLPoint operator+(const CLPoint & rhs) const
  {
    return CLPoint(this->mX + rhs.mX,
                   this->mY + rhs.mY
#ifdef USE_CRENDER_EXTENSION
                   , this->mZ + rhs.mZ
#endif // USE_CRENDER_EXTENSION
                  );
  };

  virtual void moveBy(const CLPoint &p)
  {
    mX += p.mX;
    mY += p.mY;
#ifdef USE_CRENDER_EXTENSION
    mZ += p.mZ;
#endif // USE_CRENDER_EXTENSION
  };

  CLPoint operator*(const double & rhs) const
  {
    return CLPoint(this->mX * rhs,
                   this->mY * rhs
#ifdef USE_CRENDER_EXTENSION
                   , this->mZ * rhs
#endif // USE_CRENDER_EXTENSION
                  );
  };

  C_FLOAT64 dot(const CLPoint & rhs) const
  {
    return this->mX * rhs.mX + this->mY * rhs.mY
#ifdef USE_CRENDER_EXTENSION
           + this->mZ * rhs.mZ
#endif // USE_CRENDER_EXTENSION
           ;
  };

  // sort columnwise, point p1 is < point p2 if x-component is <, if x es are equal, check for y
  bool operator<(const CLPoint & rhs) const
  {
    if (mX == rhs.mX)
#ifdef USE_CRENDER_EXTENSION
      if (mY == rhs.mY)
        {
          return (mZ < rhs.mZ);
        }
      else
        {
          return (mY < rhs.mY);
        }

#else
      return (mY < rhs.mY);
#endif // USE_CRENDER_EXTENSION
    else
      return (mX < rhs.mX);
  };

  /**
   * convert to sbml point
   */
  Point getSBMLPoint() const;

  bool isEmpty() const
  {
    return mX == 0
           && mY == 0
#ifdef USE_CRENDER_EXTENSION
           && mZ == 0
#endif // USE_CRENDER_EXTENSION
           ;
  }

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
#ifdef USE_CRENDER_EXTENSION
  C_FLOAT64 mDepth;
#endif // USE_CRENDER_EXTENSION

public:

  CLDimensions() :
    mWidth(0.0)
    , mHeight(0.0)
#ifdef USE_CRENDER_EXTENSION
    , mDepth(0.0)
#endif // USE_CRENDER_EXTENSION

  {};

  CLDimensions(const C_FLOAT64 & w
               , const C_FLOAT64 & h
#ifdef USE_CRENDER_EXTENSION
               , const C_FLOAT64 & d = 0.0
#endif // USE_CRENDER_EXTENSION
              ):
    mWidth(w)
    , mHeight(h)
#ifdef USE_CRENDER_EXTENSION
    , mDepth(d)
#endif // USE_CRENDER_EXTENSION
  {};

  /**
   * constructor from libsbml object
   */
  CLDimensions(const Dimensions& d);

  const C_FLOAT64 & getWidth() const {return mWidth;};
  const C_FLOAT64 & getHeight() const {return mHeight;};
#ifdef USE_CRENDER_EXTENSION
  const C_FLOAT64 & getDepth() const {return mDepth;};
#endif // USE_CRENDER_EXTENSION

  C_FLOAT64 & getWidth() {return mWidth;};
  C_FLOAT64 & getHeight() {return mHeight;};
#ifdef USE_CRENDER_EXTENSION
  C_FLOAT64 & getDepth() {return mDepth;};
#endif // USE_CRENDER_EXTENSION

  void setWidth(const C_FLOAT64 & w) {mWidth = w;};
  void setHeight(const C_FLOAT64 & h) {mHeight = h;};
#ifdef USE_CRENDER_EXTENSION
  void setDepth(const C_FLOAT64 & d) {mDepth = d;};
#endif // USE_CRENDER_EXTENSION

  void scale(const double & scaleFactor)
  {
    mWidth *= scaleFactor;
    mHeight *= scaleFactor;
#ifdef USE_CRENDER_EXTENSION
    mDepth *= scaleFactor;
#endif // USE_CRENDER_EXTENSION
  }

  /**
   * convert to sbml dimension
   */
  Dimensions getSBMLDimensions() const;

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
  CLPoint getCenter() {return CLPoint(mPosition.getX() + 0.5 * mDimensions.getWidth(), mPosition.getY() + 0.5 * mDimensions.getHeight());};
  CLDimensions & getDimensions() {return mDimensions;};

  void setPosition(const CLPoint & p) {mPosition = p;};
  void setDimensions(const CLDimensions & d) {mDimensions = d;};

  virtual void moveBy(const CLPoint &p)
  {
    mPosition.moveBy(p);
  };

  /**
   * convert to sbml bounding box
   */
  BoundingBox getSBMLBoundingBox() const;

  void scale(const double & scaleFactor) {mPosition.scale(scaleFactor); mDimensions.scale(scaleFactor);}

  /**
    * insert operator
    */
  friend std::ostream & operator<<(std::ostream &os, const CLBoundingBox & bb);
};

#endif
