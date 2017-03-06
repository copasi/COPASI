// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef UTILITY_CLASSES_H__
#define UTILITY_CLASSES_H__

// opengl includes
#ifdef WIN32
# ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
# endif // WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif // WIN32

#ifdef __APPLE__
#include "OpenGL/gl.h"
#else
#include "GL/gl.h"
#endif // __APPLE__

// stl includes
#include <string>
#include <vector>

// render extension includes
#include "copasi/layout/CLGraphicalPrimitive2D.h"
#include "copasi/layout/CLRelAbsVector.h"
#include "copasi/layout/CLText.h"

class CLGraphicalObject;

/**
 * structure to store the texture for a TextGlyph
 */
struct CLTextureSpec
{
  double mTextureWidth;
  double mTextureHeight;
  double mTextWidth;
  double mTextHeight;
  unsigned int mNumComponents;
  GLuint mTextureName;
};

/**
 * structure to store the texture for a TextGlyph
 */
struct CLTextTextureSpec: CLTextureSpec
{
  double mScale;
  double mMaxScale;
  double mAscent;
};

struct CLFontSpec
{
  std::string mFamily;
  double mSize;
  CLText::FONT_WEIGHT mWeight;
  CLText::FONT_STYLE mStyle;

  CLFontSpec();

  bool operator<(const CLFontSpec& right) const;
};

struct simple_point
{
  GLdouble mX;
  GLdouble mY;
  GLdouble mZ;
  // texture coordinate
  GLdouble mS;
};

struct CLLineStippleTexture
{
  unsigned int mPatternLength;
  unsigned int mTextureLength;
  GLuint mTextureName;

  CLLineStippleTexture(const std::vector<unsigned int>& dasharray);

  ~CLLineStippleTexture();
};

class compareGraphicalObjectsBySize
{
public:
  bool operator()(const CLGraphicalObject* pObject1, const CLGraphicalObject* pObject2) const;
};

struct CLGroupAttributes
{
public:
  std::string mStroke;
  double mStrokeWidth;
  std::vector<unsigned int> mStrokeDasharray;
  // contains 12 double values
  double* mpTransform;
  std::string mFill;
  CLGraphicalPrimitive2D::FILL_RULE mFillRule;
  std::string mFontFamily;
  CLRelAbsVector mFontSize;
  CLText::FONT_WEIGHT mFontWeight;
  CLText::FONT_STYLE mFontStyle;
  CLText::TEXT_ANCHOR mTextAnchor;
  CLText::TEXT_ANCHOR mVTextAnchor;
  std::string mStartHead;
  std::string mEndHead;
  double mX;
  double mY;
  double mZ;
  double mWidth;
  double mHeight;

  /**
   * Constructor that fills all values with default attributes.
   */
  CLGroupAttributes();

  /**
   * Destructor that deletes the memory used for the transformation
   * array.
   */
  ~CLGroupAttributes();

  /**
   * Copy constructor.
   */
  CLGroupAttributes(const CLGroupAttributes& src);

  /**
   * Assignment operator.
   */
  CLGroupAttributes& operator=(const CLGroupAttributes& src);
};

#endif // UTILITY_CLASSES_H__
