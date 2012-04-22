// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/utility_classes.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2012/04/22 14:51:16 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "utility_classes.h"

#include <cmath>
#include <assert.h>
#include <string.h>

// includes from the layout extension
#include "copasi/layout/CLGraphicalObject.h"
#include "copasi/layout/CLGlyphs.h"
#include "copasi/layout/CLReactionGlyph.h"

CLLineStippleTexture::CLLineStippleTexture(const std::vector<unsigned int>& dasharray):
    mPatternLength(0),
    mTextureLength(0),
    mTextureName(0)
{
  if (!dasharray.empty())
    {
      std::vector<unsigned int>::const_iterator it = dasharray.begin(), endit = dasharray.end();

      while (it != endit)
        {
          this->mPatternLength += *it;
          ++it;
        }

      // we only need to create a texture if the pattern length is not 0
      if (this->mPatternLength != 0)
        {
          // the texture size should be a multiple of 2
          unsigned int exponent = (unsigned int)ceil(log((double)this->mPatternLength) / log(2.0));

          if (exponent <= 31)
            {
              this->mTextureLength = 1 << exponent;
              // make sure the texture name is really free
              this->mTextureName = 0;
              GLint w = -1;
              glTexImage1D(GL_PROXY_TEXTURE_1D, 0, GL_ALPHA, this->mTextureLength, 0, GL_ALPHA, GL_UNSIGNED_BYTE, NULL);
              glGetTexLevelParameteriv(GL_PROXY_TEXTURE_1D, 0, GL_TEXTURE_WIDTH, &w);

              if (w != 0)
                {
                  GLubyte* pTextureData = new GLubyte[this->mTextureLength];
                  // now we create the pattern
                  it = dasharray.begin();
                  unsigned int i;
                  bool gap = false;
                  unsigned int index = 0;

                  while (it != endit)
                    {
                      for (i = 0; i < *it; ++i)
                        {
                          // if it is a gap, we write 0, otherwise we write 255
                          pTextureData[index] = gap ? 0 : 255;
                          ++index;
                        }

                      gap = !gap;
                      ++it;
                    }

                  // fill the rest of the texture with 255
                  while (index < this->mTextureLength)
                    {
                      pTextureData[index++] = 70;
                    }

                  // now we load the texture data into OpenGL
                  glGenTextures(1, &this->mTextureName);
                  // make sure a new texture name has been created
                  assert(this->mTextureName != 0);
                  glBindTexture(GL_TEXTURE_1D, this->mTextureName);
                  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                  glTexImage1D(GL_TEXTURE_1D, 0, GL_ALPHA, this->mTextureLength, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pTextureData);
                  // delete the memory
                  delete[] pTextureData;
                }
              else
                {
                  std::cerr << "Line stipple texture of this size is not supported by the current OpenGL implementation." << std::endl;
                }
            }
          else
            {
              std::cerr << "texture to large." << std::endl;
            }
        }
    }
}

CLLineStippleTexture::~CLLineStippleTexture()
{
  if (this->mTextureName != 0)
    {
      glDeleteTextures(1, &this->mTextureName);
    }
}

bool compareGraphicalObjectsBySize::operator()(const CLGraphicalObject* pObject1, const CLGraphicalObject* pObject2) const
{
  const CLReactionGlyph* pRG1 = dynamic_cast<const CLReactionGlyph*>(pObject1);
  const CLReactionGlyph* pRG2 = dynamic_cast<const CLReactionGlyph*>(pObject2);
  const CLMetabReferenceGlyph* pSRG1 = dynamic_cast<const CLMetabReferenceGlyph*>(pObject1);
  const CLMetabReferenceGlyph* pSRG2 = dynamic_cast<const CLMetabReferenceGlyph*>(pObject2);
  bool result = false;

  if (!(((pRG1 && pRG1->getCurve().getNumCurveSegments() != 0) || (pSRG1 && pSRG1->getCurve().getNumCurveSegments() != 0)) && ((pRG2 && pRG2->getCurve().getNumCurveSegments() != 0) || (pSRG2 && pSRG2->getCurve().getNumCurveSegments() != 0))))
    {
      result = ((pObject1->getBoundingBox().getDimensions().getWidth() * pObject1->getBoundingBox().getDimensions().getHeight()) < (pObject2->getBoundingBox().getDimensions().getWidth() * pObject2->getBoundingBox().getDimensions().getHeight()));
    }

  return result;
}

/**
 * Constructor that fills all values with default attributes.
 */
CLGroupAttributes::CLGroupAttributes():
    mStroke("none"),
    mStrokeWidth(0.0),
    mStrokeDasharray(),
    mpTransform(NULL),
    mFill("none"),
    mFillRule(CLGraphicalPrimitive2D::NONZERO),
    mFontFamily("sans-serif"),
    mFontSize(CLRelAbsVector(0.0, 0.0)),
    mFontWeight(CLText::WEIGHT_NORMAL),
    mFontStyle(CLText::STYLE_NORMAL),
    mTextAnchor(CLText::ANCHOR_START),
    mVTextAnchor(CLText::ANCHOR_TOP),
    mStartHead("none"),
    mEndHead("none"),
    mX(0),
    mY(0),
    mZ(0),
    mWidth(0),
    mHeight(0)
{
  this->mpTransform = new double[12];
  memcpy(this->mpTransform, CLTransformation::getIdentityMatrix(), 12*sizeof(double));
}
/**
 * Destructor that deletes the memory used for the transformation
 * array.
 */
CLGroupAttributes::~CLGroupAttributes()
{
  if (this->mpTransform != NULL)
    {
      delete[] this->mpTransform;
    }
}

/**
 * Copy constructor.
 */
CLGroupAttributes::CLGroupAttributes(const CLGroupAttributes& src):
    mStroke(src.mStroke),
    mStrokeWidth(src.mStrokeWidth),
    mStrokeDasharray(src.mStrokeDasharray),
    mpTransform(NULL),
    mFill(src.mFill),
    mFillRule(src.mFillRule),
    mFontFamily(src.mFontFamily),
    mFontSize(src.mFontSize),
    mFontWeight(src.mFontWeight),
    mFontStyle(src.mFontStyle),
    mTextAnchor(src.mTextAnchor),
    mVTextAnchor(src.mVTextAnchor),
    mStartHead(src.mStartHead),
    mEndHead(src.mEndHead),
    mX(src.mX),
    mY(src.mY),
    mZ(src.mZ),
    mWidth(src.mWidth),
    mHeight(src.mHeight)
{
  this->mpTransform = new double[12];
  memcpy(this->mpTransform, src.mpTransform, 12*sizeof(double));
}

/**
 * Assignment operator.
 */
CLGroupAttributes& CLGroupAttributes::operator=(const CLGroupAttributes & src)
{
  if (&src != this)
    {
      this->mStroke = src.mStroke;
      this->mStrokeWidth = src.mStrokeWidth;
      this->mStrokeDasharray = src.mStrokeDasharray;

      if (!this->mpTransform)
        {
          this->mpTransform = new double[12];
        }

      // contains 12 double values
      memcpy(this->mpTransform, src.mpTransform, 12*sizeof(double));
      this->mFill = src.mFill;
      this->mFillRule = src.mFillRule;
      this->mFontFamily = src.mFontFamily;
      this->mFontSize = src.mFontSize;
      this->mFontWeight = src.mFontWeight;
      this->mFontStyle = src.mFontStyle;
      this->mTextAnchor = src.mTextAnchor;
      this->mVTextAnchor = src.mVTextAnchor;
      this->mStartHead = src.mStartHead;
      this->mEndHead = src.mEndHead;
      this->mX = src.mX;
      this->mY = src.mY;
      this->mZ = src.mZ;
      this->mWidth = src.mWidth;
      this->mHeight = src.mHeight;
    }

  return *this;
}

CLFontSpec::CLFontSpec():
    mFamily(""),
    mSize(0.0),
    mWeight(CLText::WEIGHT_UNSET),
    mStyle(CLText::STYLE_UNSET)
{
}

bool CLFontSpec::operator<(const CLFontSpec& right) const
{
  bool result = false;

  if (this->mFamily < right.mFamily)
    {
      result = true;
    }
  else if (this->mFamily == right.mFamily)
    {
      if (this->mSize < right.mSize)
        {
          result = true;
        }
      else if (this->mSize == right.mSize)
        {
          if (this->mWeight < right.mWeight)
            {
              result = true;
            }
          else if (this->mWeight == right.mWeight)
            {
              if (this->mStyle < right.mStyle)
                {
                  result = true;
                }
            }
        }
    }

  return result;
}
