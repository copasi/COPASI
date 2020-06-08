// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CLBASE_H_
#define CLBASE_H_

#include "copasi/copasi.h"
#include <string>

LIBSBML_CPP_NAMESPACE_BEGIN
class SBase;
class BoundingBox;
class Dimensions;
class Point;
LIBSBML_CPP_NAMESPACE_END

class CLPoint;

/**
 * This class does nothing at all at the moment.
 * Is is the base of all classes that have an equivalent in the
 * libsbml layout extension
 */
class CLBase
{
public:
  CLBase() : mTag("") {};
  CLBase(const CLBase &b) : mTag(b.mTag)  {};
  CLBase(const SBase &) : mTag("") {};
  // make CLBase polymorphic so that we can dynamic cast from CLBase to
  // CLGraphicalObject
  virtual ~CLBase() {};
  virtual void moveBy(const CLPoint &) {};
  const std::string& getTag() const {return mTag;}
  void setTag(const std::string& tag) {mTag = tag;}
  bool hasTag() const {return mTag.empty();}
protected:
  std::string mTag;
};

/**
 * This class describes a Point in a layout
 * It is 2-dimensional at the moment
 */
class CLPoint : public CLBase
{
protected:

  C_FLOAT64 mX, mY;
  C_FLOAT64 mZ;

public:

  CLPoint():
    mX(0.0)
    , mY(0.0)
    , mZ(0.0)
  {};

  CLPoint(const C_FLOAT64 & x
          , const C_FLOAT64 & y
          , const C_FLOAT64 & z = 0.0
         ):
    mX(x)
    , mY(y)
    , mZ(z)
  {};

  /**
   * constructor from libsbml object
   */
  CLPoint(const Point& p);

  const C_FLOAT64 & getX() const {return mX;};
  const C_FLOAT64 & getY() const {return mY;};
  const C_FLOAT64 & getZ() const {return mZ;};

  C_FLOAT64 & getX() {return mX;};
  C_FLOAT64 & getY() {return mY;};
  C_FLOAT64 & getZ() {return mZ;};

  void setX(const C_FLOAT64 & x) {mX = x;};
  void setY(const C_FLOAT64 & y) {mY = y;};
  void setZ(const C_FLOAT64 & z) {mZ = z;};

  void scale(const double & scaleFactor) {mX *= scaleFactor; mY *= scaleFactor;}

  bool operator==(const CLPoint & rhs) const
  {
    bool result = (mX == rhs.mX) && (mY == rhs.mY);
    result &= mZ == rhs.mZ;
    return result;
  };

  CLPoint operator-(const CLPoint & rhs) const
  {
    return CLPoint(this->mX - rhs.mX,
                   this->mY - rhs.mY
                   , this->mZ - rhs.mZ
                  );
  };

  CLPoint operator+(const CLPoint & rhs) const
  {
    return CLPoint(this->mX + rhs.mX,
                   this->mY + rhs.mY
                   , this->mZ + rhs.mZ
                  );
  };

  virtual void moveBy(const CLPoint &p)
  {
    mX += p.mX;
    mY += p.mY;
    mZ += p.mZ;
  };

  CLPoint operator*(const double & rhs) const
  {
    return CLPoint(this->mX * rhs,
                   this->mY * rhs
                   , this->mZ * rhs
                  );
  };

  C_FLOAT64 dot(const CLPoint & rhs) const
  {
    return this->mX * rhs.mX + this->mY * rhs.mY
           + this->mZ * rhs.mZ
           ;
  };

  // sort columnwise, point p1 is < point p2 if x-component is <, if x es are equal, check for y
  bool operator<(const CLPoint & rhs) const
  {
    if (mX == rhs.mX)
      if (mY == rhs.mY)
        {
          return (mZ < rhs.mZ);
        }
      else
        {
          return (mY < rhs.mY);
        }
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
           && mZ == 0
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
  C_FLOAT64 mDepth;

public:

  CLDimensions() :
    mWidth(0.0)
    , mHeight(0.0)
    , mDepth(0.0)

  {};

  CLDimensions(const C_FLOAT64 & w
               , const C_FLOAT64 & h
               , const C_FLOAT64 & d = 0.0
              ):
    mWidth(w)
    , mHeight(h)
    , mDepth(d)
  {};

  /**
   * constructor from libsbml object
   */
  CLDimensions(const Dimensions& d);

  const C_FLOAT64 & getWidth() const {return mWidth;};
  const C_FLOAT64 & getHeight() const {return mHeight;};
  const C_FLOAT64 & getDepth() const {return mDepth;};

  C_FLOAT64 & getWidth() {return mWidth;};
  C_FLOAT64 & getHeight() {return mHeight;};
  C_FLOAT64 & getDepth() {return mDepth;};

  void setWidth(const C_FLOAT64 & w) {mWidth = w;};
  void setHeight(const C_FLOAT64 & h) {mHeight = h;};
  void setDepth(const C_FLOAT64 & d) {mDepth = d;};

  void scale(const double & scaleFactor)
  {
    mWidth *= scaleFactor;
    mHeight *= scaleFactor;
    mDepth *= scaleFactor;
  }

  bool isEmpty() const
  {
    return mWidth == 0
           && mHeight == 0
           && mDepth == 0
           ;
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

  const CLPoint & getPosition() const {return mPosition;}
  const CLDimensions & getDimensions() const {return mDimensions;}

  CLPoint & getPosition() {return mPosition;}
  CLPoint getCenter() const {return CLPoint(mPosition.getX() + 0.5 * mDimensions.getWidth(), mPosition.getY() + 0.5 * mDimensions.getHeight());}
  CLDimensions & getDimensions() {return mDimensions;}

  void setPosition(const CLPoint & p) {mPosition = p;}
  void setDimensions(const CLDimensions & d) {mDimensions = d;}

  bool isEmpty() const { return mPosition.isEmpty() && mDimensions.isEmpty();  }

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
