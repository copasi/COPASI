// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLLayoutRenderer.cpp,v $
//   $Revision: 1.5.2.15 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/04/26 15:15:33 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <limits>
#include <math.h>
#include <stdio.h>
#include <cctype>
#include <algorithm>

#include <sbml/layout/render/Transformation.h>

// this define is needed so that the glFogCoordf function is found
// in linux
#define GL_GLEXT_PROTOTYPES
#include "CLLayoutRenderer.h"
#include "copasi/layout/CLBase.h"
#include "copasi/layout/CLGradientStops.h"
#include "copasi/layout/CLDefaultStyles.h"
#include "copasi/layout/CLFontRendererBase.h"
#include "copasi/layout/CLRenderResolver.h"
#include "copasi/layout/CLRGBAColor.h"
#include "copasi/layout/CLRelAbsVector.h"
#include "copasi/layout/CLTransformation.h"
#include "copasi/layout/CLGraphicalPrimitive1D.h"
#include "copasi/layout/CLGraphicalPrimitive2D.h"
#include "copasi/layout/CLGroup.h"
#include "copasi/layout/CLLocalRenderInformation.h"
#include "copasi/layout/CLGlobalRenderInformation.h"
#include "copasi/layout/CLStyle.h"
#include "copasi/layout/CLLocalStyle.h"
#include "copasi/layout/CLGlobalStyle.h"
#include "copasi/layout/CLRenderPoint.h"
#include "copasi/layout/CLRenderCubicBezier.h"
#include "copasi/layout/CLRenderCurve.h"
#include "copasi/layout/CLEllipse.h"
#include "copasi/layout/CLImage.h"
#include "copasi/layout/CLImageTexturizer.h"
#include "copasi/layout/CLRectangle.h"
#include "copasi/layout/CLPolygon.h"
#include "copasi/layout/CLText.h"
#include "copasi/layout/CLCurve.h"
#include "copasi/layout/CLayout.h"
#include "copasi/layout/CLGraphicalObject.h"
#include "copasi/layout/CLGlyphs.h"
#include "copasi/layout/CLReactionGlyph.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CReaction.h"

// opengl includes
#ifdef _WIN32
# include "windows.h" // Needed for OpenGL
# define _USE_MATH_DEFINES // without the following define, M_PI will not be declared under windows
// disable warning about unsafe fopen
# pragma warning(disable : 4996)
#endif // _WIN32


#ifdef __APPLE__
#ifdef COPASI_DEBUG
#include <string>
#include <stdlib.h>
#include <mach-o/dyld.h>
#endif // COPASI_DEBUG
# include "OpenGL/gl.h"
# include "OpenGL/glu.h"
#else
# include "GL/gl.h"
# include "GL/glu.h"
# include "GL/glext.h"
# ifndef _WIN32
#  define GLX_GLXEXT_PROTOTYPES
#  include "GL/glx.h"
# endif // _WIN32
#endif // __APPLE__

// specifies how many segments are used to approximate the rounded
// corners of a rectangle
const unsigned int CLLayoutRenderer::NUM_CORNER_SEGMENTS = 10;

// specifies how many segments are used to draw circles and ellipses
const unsigned int CLLayoutRenderer::NUM_CIRCLE_SEGMENTS = 60;

// specifies how many points to calculate for a cubic bezier curve
const unsigned int CLLayoutRenderer::NUM_BEZIER_POINTS = 20;

// a constant that is considered to be zero
const double CLLayoutRenderer::ALMOST_ZERO = 1e-12;

// a constant that determines the maximal size of a gradient texture
const unsigned int CLLayoutRenderer::GRADIENT_TEXTURE_SIZE_LIMIT = 512;

// a constant that determines the maximal size of a gradient texture
const double CLLayoutRenderer::SELECTION_FRAME_WIDTH = 3.0;

/**
 * constructor for global render information
 */
CLLayoutRenderer::CLLayoutRenderer(CLayout* pLayout, const CLGlobalRenderInformation* pRenderInformation, const CCopasiVector<CLGlobalRenderInformation>* pGlobalRenderInformationList, const CModel* pModel, const std::string& baseDir):
    mStateList(),
    mCurrentAttributes(),
    mpModel(pModel),
    mpLayout(pLayout),
    mpResolver(NULL),
    mBaseDir(baseDir),
    mZoomFactor(1.0),
    mAspect(1.0),
    mX(0.0),
    mY(0.0),
    mpGlobalRenderInfoList(pGlobalRenderInformationList),
    mpFontRenderer(NULL),
    mDeduceSpeciesReferenceRoles(false),
    mpSelectionBox(NULL),
    mpImageTexturizer(NULL)
#ifdef COPASI_DEBUG
    , mHighlight(true)
    , mGLFunctionsInitialized(false)
    , mpGlFogCoordfEXT(NULL)
#endif // COPASI_DEBUG
{
#ifdef COPASI_DEBUG
  this->mHighlightColor[0] = 0.5;
  this->mHighlightColor[1] = 0.0;
  this->mHighlightColor[2] = 0.0;
  this->mHighlightColor[3] = 1.0;
  this->mFogColor[0] = 0.5;
  this->mFogColor[1] = 0.5;
  this->mFogColor[2] = 0.5;
  this->mFogColor[3] = 1.0;
#endif // COPASI_DEBUG
  this->change_style(pRenderInformation);
}


/**
 * constructor for local render information
 */
CLLayoutRenderer::CLLayoutRenderer(CLayout* pLayout, const CLLocalRenderInformation* pRenderInformation, const CCopasiVector<CLGlobalRenderInformation>* pGlobalRenderInformationList, const CModel* pModel, const std::string& baseDir):
    mStateList(),
    mCurrentAttributes(),
    mpModel(pModel),
    mpLayout(pLayout),
    mpResolver(NULL),
    mBaseDir(baseDir),
    mZoomFactor(1.0),
    mAspect(1.0),
    mX(0.0),
    mY(0.0),
    mpGlobalRenderInfoList(pGlobalRenderInformationList),
    mpFontRenderer(NULL),
    mDeduceSpeciesReferenceRoles(false),
    mpSelectionBox(NULL)
#ifdef COPASI_DEBUG
    , mHighlight(true)
    , mGLFunctionsInitialized(false)
    , mpGlFogCoordfEXT(NULL)
#endif // COPASI_DEBUG
{
#ifdef COPASI_DEBUG
  this->mHighlightColor[0] = 0.5;
  this->mHighlightColor[0] = 0.0;
  this->mHighlightColor[0] = 0.0;
  this->mHighlightColor[0] = 1.0;
  this->mFogColor[0] = 0.5;
  this->mFogColor[1] = 0.5;
  this->mFogColor[2] = 0.5;
  this->mFogColor[3] = 1.0;
  this->initialize_gl_extension_functions();
#endif // COPASI_DEBUG
  this->change_style(pRenderInformation);
}

void CLLayoutRenderer::change_style(const CLGlobalRenderInformation* pRenderInformation, bool defaultStyle)
{
  if (this->mpResolver != NULL)
    {
      delete this->mpResolver;
      this->mpResolver = NULL;
    }

  if (pRenderInformation)
    {
      this->mpResolver = new CLRenderResolver(*pRenderInformation, *this->mpGlobalRenderInfoList);
    }

  if (defaultStyle == true)
    {
      this->setDeduceSpeciesReferenceRoles(true);
    }

  this->clear_cached_data();

  if (this->mpFontRenderer != NULL)
    {
      this->analyse_render_information(mX, mY, mX + mW / this->mZoomFactor, mY + mH / this->mZoomFactor);
    }

  if (this->mDeduceSpeciesReferenceRoles)
    {
      this->mpResolver->setDeducedObjectRoles(this->mSpeciesReferencesWithDeducedRole);
    }
}

void CLLayoutRenderer::change_style(const CLLocalRenderInformation* pRenderInformation)
{
  if (this->mpResolver != NULL)
    {
      delete this->mpResolver;
      this->mpResolver = NULL;
    }

  if (pRenderInformation)
    {
      this->mpResolver = new CLRenderResolver(*pRenderInformation, this->mpLayout->getListOfLocalRenderInformationObjects(), *this->mpGlobalRenderInfoList);
    }

  this->clear_cached_data();

  if (this->mpFontRenderer != NULL)
    {
      this->analyse_render_information(mX, mY, mX + mW / this->mZoomFactor, mY + mH / this->mZoomFactor);
    }

  if (this->mDeduceSpeciesReferenceRoles)
    {
      this->mpResolver->setDeducedObjectRoles(this->mSpeciesReferencesWithDeducedRole);
    }
}

/**
 * destructor.
 */
CLLayoutRenderer::~CLLayoutRenderer()
{
  if (mpResolver != NULL) delete mpResolver;

  // delete the data in all the maps
  this->clear_cached_data();

  if (this->mpFontRenderer)
    {
      delete this->mpFontRenderer;
    }

  if (this->mpSelectionBox != NULL)
    {
      delete this->mpSelectionBox;
    }
}

/**
 * Extracts the group attributes from the outermost group of a style.
 */
void CLLayoutRenderer::extract_group_attributes(const CLStyle* pStyle, CLGroupAttributes* attributes)
{
  CLLayoutRenderer::extract_group_attributes(pStyle->getGroup(), attributes);
}

/**
 * Method that draws a line with the given start and end points.
 * All the other parameter like color, linewidth etc. have to be set
 * before.
 */
void CLLayoutRenderer::draw_line_segment(double x1, double y1, double z1, double x2, double y2, double z2, double line_width, bool texture, double s1, double s2)
{
  // calculate the 4 points of the rectangle considering the line width
  // actually the correct thing to do would be to draw a tube, but right now
  // this is takes to many ressources, so we draw a rectangle and use the same
  // mapping as for the line endings.
  // calculate the direction vector
  double vx1 = x2 - x1;
  double vy1 = y2 - y1;
  double vz1 = z2 - z1;
  double length = sqrt(vx1 * vx1 + vy1 * vy1 + vz1 * vz1);

  // calculate the normal to this vector
  double vx2 = 0.0;
  double vy2 = 0.0;
  double vz2 = 0.0;
  double half_width = line_width / 2.0;

  if (fabs(vx1) < ALMOST_ZERO && vz1 < ALMOST_ZERO)
    {
      // scale by the line_width
      vx2 = -vy1 / length * half_width;
      vy2 = 0.0;
      vz2 = 0.0;
    }
  else
    {
      // scale by the line_width
      double normY = vy1 / length;
      vx2 = -normY * vx1 / length * half_width;
      vy2 = (1 - normY * normY) * half_width;
      vz2 = -normY * vz1 / length * half_width;
      double normLength = half_width / sqrt(vx2 * vx2 + vy2 * vy2 + vz2 * vz2);
      vx2 *= normLength;
      vy2 *= normLength;
      vz2 *= normLength;
    }

  // calculate the 4 points
  GLfloat* pDatapoints = new GLfloat[12];
  pDatapoints[0] = (GLfloat)(x1 + vx2);
  pDatapoints[1] = (GLfloat)(y1 + vy2);
  pDatapoints[2] = (GLfloat)(z1 + vz2);
  pDatapoints[3] = (GLfloat)(x1 - vx2);
  pDatapoints[4] = (GLfloat)(y1 - vy2);
  pDatapoints[5] = (GLfloat)(z1 - vz2);
  pDatapoints[6] = (GLfloat)(x2 + vx2);
  pDatapoints[7] = (GLfloat)(y2 + vy2);
  pDatapoints[8] = (GLfloat)(z2 + vz2);
  pDatapoints[9] = (GLfloat)(x2 - vx2);
  pDatapoints[10] = (GLfloat)(y2 - vy2);
  pDatapoints[11] = (GLfloat)(z2 - vz2);
  // enable the line stippling texture if necessary
  GLfloat* pTextureCoordinates = NULL;

  if (texture)
    {
      pTextureCoordinates = new GLfloat[4];
      pTextureCoordinates[0] = (GLfloat)s1;
      pTextureCoordinates[1] = (GLfloat)s1;
      pTextureCoordinates[2] = (GLfloat)s2;
      pTextureCoordinates[3] = (GLfloat)s2;
      // create an array for texture coordinates
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(1, GL_FLOAT, 0, pTextureCoordinates);
    }

  // just draw as a triangle strip
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, pDatapoints);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisableClientState(GL_VERTEX_ARRAY);

  // disable the line stippleling texture if necessary
  if (texture)
    {
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      delete[] pTextureCoordinates;
    }

  delete[] pDatapoints;
}

/**
 * Method that draws a curve from the layout extension.
 * All the other parameter like color, linewidth etc. have to be set
 * before.
 */
void CLLayoutRenderer::draw_curve(const CLCurve* pCurve, bool drawBasepoints)
{
  // set some attributes from mCurrentAttributes (stroke, stroke_width,
  // stroke_dasharray)
  std::map<std::string, CLRGBAColor>::const_iterator pos = this->mColorMap.find(mCurrentAttributes.mStroke);
  assert(pos != this->mColorMap.end());
  const CLRGBAColor& c = pos->second;
  glColor4ub(c.mR, c.mG, c.mB, c.mA);
  size_t i, iMax = pCurve->getNumCurveSegments();
  const CLLineSegment* pLineSegment = NULL;
  // apply the current transformation
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  if (memcmp(mCurrentAttributes.mpTransform, CLTransformation::getIdentityMatrix(), 12*sizeof(double)))
    {
      // move back to the current offset
      glTranslated(this->mCurrentAttributes.mX, this->mCurrentAttributes.mY, this->mCurrentAttributes.mZ);
      GLdouble* matrix = new GLdouble[16];
      CLLayoutRenderer::createGLMatrix(mCurrentAttributes.mpTransform, matrix);
      glMultMatrixd(matrix);
      delete[] matrix;
      // move to 0.0,0.0,0.0
      glTranslated(-this->mCurrentAttributes.mX, -this->mCurrentAttributes.mY, -this->mCurrentAttributes.mZ);
    }

  // calculate the data points
  std::vector<simple_point> v;
  simple_point p;
  const CLPoint* pP;
  const CLPoint* pP2, *pP3, *pP4;
  GLdouble* pData = NULL;
  CLPoint lastEnd;
  double delta_phi = 2 * M_PI / NUM_CIRCLE_SEGMENTS;
  double phi = 0.0;
  GLdouble* pCircleData = NULL;

  // if we need to draw the basepoints of a curve,
  // we calculate the circle points here.
  // TODO We could actually move this code somewhere else and
  // TODO calculate it only once at startup, but for now this works well enough
  if (drawBasepoints == true)
    {
      pCircleData = new GLdouble[3*(NUM_CIRCLE_SEGMENTS+2)];
      pCircleData[0] = 0.0;
      pCircleData[1] = 0.0;
      pCircleData[2] = 0.0;

      for (i = 1; i <= NUM_CIRCLE_SEGMENTS; ++i)
        {
          phi = i * delta_phi;
          pCircleData[i*3] = cos(phi);
          pCircleData[i*3+1] = sin(phi);
          pCircleData[i*3+2] = 0.0;
        }

      // close the circle
      pCircleData[i*3] = pCircleData[0];
      pCircleData[i*3+1] = pCircleData[1];
      pCircleData[i*3+2] = pCircleData[2];
    }

  for (i = 0; i < iMax; ++i)
    {
      pLineSegment = pCurve->getSegmentAt(i);

      if (pLineSegment->isBezier())
        {
          pP = &pLineSegment->getStart();

          // check if we have a break in the line
          if (i != 0 && !((*pP) == lastEnd))
            {
              // draw the lines the are currently in v and clear v
              iMax = v.size();

              if (iMax > 1)
                {
                  pData = new GLdouble[3*iMax];
                  size_t index = 0;
                  const simple_point* pSimple = NULL;

                  for (i = 0; i < iMax; ++i)
                    {
                      pSimple = &v[i];
                      pData[index++] = pSimple->mX;
                      pData[index++] = pSimple->mY;
                      pData[index++] = pSimple->mZ;
                    }

                  // draw the line
                  this->draw_line(iMax, pData);
                  delete[] pData;
                }

              v.clear();
            }

          pP2 = &pLineSegment->getEnd();
          lastEnd = *pP2;
          pP3 = &pLineSegment->getBase1();
          pP4 = &pLineSegment->getBase2();
          pData = new GLdouble[3*NUM_BEZIER_POINTS];
          CLLayoutRenderer::calculate_cubicbezier(pP->getX(), pP->getY(), pP->getZ(),
                                                  pP3->getX(), pP3->getY(), pP3->getZ(),
                                                  pP4->getX(), pP4->getY(), pP4->getZ(),
                                                  pP2->getX(), pP2->getY(), pP2->getZ(),
                                                  NUM_BEZIER_POINTS, pData);
          size_t j;
          size_t index = 0;

          for (j = 0; j < NUM_BEZIER_POINTS; ++j)
            {
              p.mX = pData[index++];
              p.mY = pData[index++];
              p.mZ = pData[index++];
              v.push_back(p);
            }

          delete[] pData;

          // draw the base points if requested
          if (drawBasepoints == true)
            {
              // we have to draw four circles in the same color as the line,
              // but a little wider
              if (mCurrentAttributes.mStroke != "none" && mCurrentAttributes.mStrokeWidth > 0.0)
                {
                  size_t j;
                  std::map<std::string, CLRGBAColor>::const_iterator pos = this->mColorMap.find(mCurrentAttributes.mStroke);
                  const CLRGBAColor& c = pos->second;
                  glColor4ub(c.mR, c.mG, c.mB, c.mA);
                  glPushMatrix();
                  glTranslated(pP->getX(), pP->getY(), pP->getZ());
                  glScaled(mCurrentAttributes.mStrokeWidth*2.0, mCurrentAttributes.mStrokeWidth*2.0, 1.0);
                  glBegin(GL_TRIANGLE_FAN);
                  glVertex3f(0.0, 0.0, 0.0);

                  for (j = 0; j <= NUM_CIRCLE_SEGMENTS; ++j)
                    {
                      glVertex3d(pCircleData[3*j], pCircleData[3*j+1], pCircleData[3*j+2]);
                    }

                  glEnd();
                  glPopMatrix();
                  glPushMatrix();
                  glTranslated(pP2->getX(), pP2->getY(), pP2->getZ());
                  glScaled(mCurrentAttributes.mStrokeWidth*2.0, mCurrentAttributes.mStrokeWidth*2.0, 1.0);
                  glBegin(GL_TRIANGLE_FAN);
                  glVertex3d(0.0, 0.0, 0.0);

                  for (j = 0; j <= NUM_CIRCLE_SEGMENTS; ++j)
                    {
                      glVertex3d(pCircleData[3*j], pCircleData[3*j+1], pCircleData[3*j+2]);
                    }

                  glEnd();
                  glPopMatrix();
                  glPushMatrix();
                  glTranslated(pP3->getX(), pP3->getY(), pP3->getZ());
                  glScaled(mCurrentAttributes.mStrokeWidth*2.0, mCurrentAttributes.mStrokeWidth*2.0, 1.0);
                  glBegin(GL_TRIANGLE_FAN);
                  glVertex3d(0.0, 0.0, 0.0);

                  for (j = 0; j <= NUM_CIRCLE_SEGMENTS; ++j)
                    {
                      glVertex3d(pCircleData[3*j], pCircleData[3*j+1], pCircleData[3*j+2]);
                    }

                  glEnd();
                  glPopMatrix();
                  glPushMatrix();
                  glTranslated(pP4->getX(), pP4->getY(), pP4->getZ());
                  glScaled(mCurrentAttributes.mStrokeWidth*2.0, mCurrentAttributes.mStrokeWidth*2.0, 1.0);
                  glBegin(GL_TRIANGLE_FAN);
                  glVertex3d(0.0, 0.0, 0.0);

                  for (j = 0; j <= NUM_CIRCLE_SEGMENTS; ++j)
                    {
                      glVertex3d(pCircleData[3*j], pCircleData[3*j+1], pCircleData[3*j+2]);
                    }

                  glEnd();
                  glPopMatrix();
                }
            }
        }
      else
        {
          const CLPoint* pP = &pLineSegment->getStart();

          if (i != 0 && !((*pP) == lastEnd))
            {
              // draw the lines that are currently in v and clear v
              iMax = v.size();

              if (iMax > 1)
                {
                  pData = new GLdouble[3*iMax];
                  size_t index = 0;
                  const simple_point* pSimple = NULL;

                  for (i = 0; i < iMax; ++i)
                    {
                      pSimple = &v[i];
                      pData[index++] = pSimple->mX;
                      pData[index++] = pSimple->mY;
                      pData[index++] = pSimple->mZ;
                    }

                  // draw the line
                  this->draw_line(iMax, pData);
                  delete[] pData;
                }
            }

          p.mX = pP->getX();
          p.mY = pP->getY();
          p.mZ = pP->getZ();
          v.push_back(p);

          if (drawBasepoints == true)
            {
              // we have to draw four circles in the same color as the line,
              // but a little wider
              if (mCurrentAttributes.mStroke != "none" && mCurrentAttributes.mStrokeWidth > 0.0)
                {
                  std::map<std::string, CLRGBAColor>::const_iterator pos = this->mColorMap.find(mCurrentAttributes.mStroke);
                  const CLRGBAColor& c = pos->second;
                  glColor4ub(c.mR, c.mG, c.mB, c.mA);
                  glPushMatrix();
                  glTranslated(pP->getX(), pP->getY(), pP->getZ());
                  glScaled(mCurrentAttributes.mStrokeWidth*2.0, mCurrentAttributes.mStrokeWidth*2.0, 1.0);
                  glBegin(GL_TRIANGLE_FAN);
                  glVertex3d(0.0, 0.0, 0.0);
                  size_t j;

                  for (j = 0; j <= NUM_CIRCLE_SEGMENTS; ++j)
                    {
                      glVertex3d(pCircleData[3*j], pCircleData[3*j+1], pCircleData[3*j+2]);
                    }

                  glEnd();
                  glPopMatrix();
                }
            }

          pP = &pLineSegment->getEnd();
          lastEnd = *pP;
          p.mX = pP->getX();
          p.mY = pP->getY();
          p.mZ = pP->getZ();
          v.push_back(p);

          if (drawBasepoints == true)
            {
              // we have to draw four circles in the same color as the line,
              // but a little wider
              if (mCurrentAttributes.mStroke != "none" && mCurrentAttributes.mStrokeWidth > 0.0)
                {
                  std::map<std::string, CLRGBAColor>::const_iterator pos = this->mColorMap.find(mCurrentAttributes.mStroke);
                  const CLRGBAColor& c = pos->second;
                  glColor4ub(c.mR, c.mG, c.mB, c.mA);
                  glPushMatrix();
                  glTranslated(pP->getX(), pP->getY(), pP->getZ());
                  glScaled(mCurrentAttributes.mStrokeWidth*2.0, mCurrentAttributes.mStrokeWidth*2.0, 1.0);
                  glBegin(GL_TRIANGLE_FAN);
                  glVertex3d(0.0, 0.0, 0.0);
                  size_t j;

                  for (j = 0; j <= NUM_CIRCLE_SEGMENTS; ++j)
                    {
                      glVertex3d(pCircleData[3*j], pCircleData[3*j+1], pCircleData[3*j+2]);
                    }

                  glEnd();
                  glPopMatrix();
                }
            }
        }
    }

  iMax = v.size();

  if (iMax > 1)
    {
      pData = new GLdouble[3*iMax];
      size_t index = 0;
      const simple_point* pSimple = NULL;

      for (i = 0; i < iMax; ++i)
        {
          pSimple = &v[i];
          pData[index++] = pSimple->mX;
          pData[index++] = pSimple->mY;
          pData[index++] = pSimple->mZ;
        }

      // draw the line
      this->draw_line(iMax, pData);
      delete[] pData;

      if (drawBasepoints == true)
        {
          // we have to draw four circles in the same color as the line,
          // but a little wider
          if (mCurrentAttributes.mStroke != "none" && mCurrentAttributes.mStrokeWidth > 0.0)
            {
              std::map<std::string, CLRGBAColor>::const_iterator pos = this->mColorMap.find(mCurrentAttributes.mStroke);
              const CLRGBAColor& c = pos->second;
              glColor4ub(c.mR, c.mG, c.mB, c.mA);
              glPushMatrix();
              glTranslated(pSimple->mX, pSimple->mY, pSimple->mZ);
              glScaled(mCurrentAttributes.mStrokeWidth, mCurrentAttributes.mStrokeWidth, 1.0);
              glBegin(GL_TRIANGLE_FAN);
              glVertex3d(0.0, 0.0, 0.0);
              size_t j;

              for (j = 0; j <= NUM_CIRCLE_SEGMENTS; ++j)
                {
                  glVertex3d(pCircleData[3*j], pCircleData[3*j+1], pCircleData[3*j+2]);
                }

              glEnd();
              glPopMatrix();
            }
        }
    }

  if (pCircleData != NULL) delete[] pCircleData;

  if (!mCurrentAttributes.mStartHead.empty() && mCurrentAttributes.mStartHead != "none")
    {
      const CLLineSegment* pLS = pCurve->getSegmentAt(0);
      const CLPoint* pP = &pLS->getStart();
      CLPoint v;

      if (!pLS->isBezier())
        {
          v = CLPoint(pLS->getStart().getX() - pLS->getEnd().getX(), pLS->getStart().getY() - pLS->getEnd().getY(), pLS->getStart().getZ() - pLS->getEnd().getZ());
        }
      else
        {
          v = CLPoint(pLS->getStart().getX() - pLS->getBase1().getX(), pLS->getStart().getY() - pLS->getBase1().getY(), pLS->getStart().getZ() - pLS->getBase1().getZ());
        }

      this->map_arrow_head(*pP, v, mCurrentAttributes.mStartHead);
    }

  if (!mCurrentAttributes.mEndHead.empty() && mCurrentAttributes.mEndHead != "none")
    {
      const CLLineSegment* pLS = pCurve->getSegmentAt(pCurve->getNumCurveSegments() - 1);
      const CLPoint* pP = &pLS->getEnd();
      CLPoint v;

      if (!pLS->isBezier())
        {
          v = CLPoint(pLS->getEnd().getX() - pLS->getStart().getX(), pLS->getEnd().getY() - pLS->getStart().getY(), pLS->getEnd().getZ() - pLS->getStart().getZ());
        }
      else
        {
          v = CLPoint(pLS->getEnd().getX() - pLS->getBase2().getX(), pLS->getEnd().getY() - pLS->getBase2().getY(), pLS->getEnd().getZ() - pLS->getBase2().getZ());
        }

      this->map_arrow_head(*pP, v, mCurrentAttributes.mEndHead);
    }

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

/**
 * Method that draws a curve from the render extension.
 * All the other parameter like color, linewidth etc. have to be set
 * before.
 */
void CLLayoutRenderer::draw_curve(const CLRenderCurve* pCurve, const CLBoundingBox* pBB)
{
  if (!pBB || !pCurve || pCurve->getNumElements() <= 0) return;

  this->save_current_attributes();
  CLLayoutRenderer::extract_1d_attributes(pCurve, &mCurrentAttributes);
  CLLayoutRenderer::extract_arrowhead_information(pCurve, &mCurrentAttributes);
  // apply the current transformation
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  if (memcmp(mCurrentAttributes.mpTransform, CLTransformation::getIdentityMatrix(), 12*sizeof(double)))
    {
      // move back to the current offset
      glTranslated(this->mCurrentAttributes.mX, this->mCurrentAttributes.mY, this->mCurrentAttributes.mZ);
      GLdouble* matrix = new GLdouble[16];
      CLLayoutRenderer::createGLMatrix(mCurrentAttributes.mpTransform, matrix);
      glMultMatrixd(matrix);
      delete[] matrix;
      // move to 0.0,0.0,0.0
      glTranslated(-this->mCurrentAttributes.mX, -this->mCurrentAttributes.mY, -this->mCurrentAttributes.mZ);
    }

  // set some attributes from mCurrentAttributes (stroke, stroke_width,
  // stroke_dasharray)
  if (this->mCurrentAttributes.mStroke != "none")
    {
      std::map<std::string, CLRGBAColor>::const_iterator pos = this->mColorMap.find(mCurrentAttributes.mStroke);
      assert(pos != this->mColorMap.end());
      const CLRGBAColor& c = pos->second;
      glColor4ub(c.mR, c.mG, c.mB, c.mA);
      size_t i, iMax = pCurve->getNumElements();
      CLRenderPoint start, end, bp1, bp2;
      CLPoint p1, p2, p3, p4;
      const CLRenderPoint* pP = NULL;
      const CLRenderCubicBezier* pCB = NULL;
      // the first one has to be a point
      const CLRenderPoint* pStart = pCurve->getCurveElement(0);
      p1 = convert_to_absolute(pStart, pBB);
      std::vector<simple_point> v;
      // there are going to be at least iMax elements in the vector
      v.reserve(iMax);
      simple_point p;
      p.mX = p1.getX();
      p.mY = p1.getY();
      p.mZ = p1.getZ();
      v.push_back(p);
      GLdouble* pData = NULL;

      for (i = 1; i < iMax; ++i)
        {
          pP = pCurve->getCurveElement(i);
          pCB = dynamic_cast<const CLRenderCubicBezier*>(pP);

          if (pCB != NULL)
            {
              end = CLRenderPoint(pCB->x(), pCB->y(), pCB->z());
              bp1 = CLRenderPoint(pCB->basePoint1_X(), pCB->basePoint1_Y(), pCB->basePoint1_Z());
              bp2 = CLRenderPoint(pCB->basePoint2_X(), pCB->basePoint2_Y(), pCB->basePoint2_Z());
              p2 = convert_to_absolute(&end, pBB);
              p3 = convert_to_absolute(&bp1, pBB);
              p4 = convert_to_absolute(&bp2, pBB);
              pData = new GLdouble[3*NUM_BEZIER_POINTS];
              CLLayoutRenderer::calculate_cubicbezier(p1.getX(), p1.getY(), p1.getZ(),
                                                      p3.getX(), p3.getY(), p3.getZ(),
                                                      p4.getX(), p4.getY(), p4.getZ(),
                                                      p2.getX(), p2.getY(), p2.getZ(),
                                                      NUM_BEZIER_POINTS, pData);
              size_t j;
              size_t index = 0;

              for (j = 0; j < NUM_BEZIER_POINTS; ++j)
                {
                  p.mX = pData[index++];
                  p.mY = pData[index++];
                  p.mZ = pData[index++];
                  v.push_back(p);
                }

              delete[] pData;
            }
          else
            {
              end = CLRenderPoint(pP->x(), pP->y(), pP->z());
              p2 = convert_to_absolute(&end, pBB);
              p.mX = p2.getX();
              p.mY = p2.getY();
              p.mZ = p2.getZ();
              v.push_back(p);
            }

          // this end is the next start
          p1 = p2;
        }

      iMax = v.size();

      if (iMax > 1)
        {
          pData = new GLdouble[3*iMax];
          size_t index = 0;
          const simple_point* pSimple = NULL;

          for (i = 0; i < iMax; ++i)
            {
              pSimple = &v[i];
              pData[index++] = pSimple->mX;
              pData[index++] = pSimple->mY;
              pData[index++] = pSimple->mZ;
            }

          // draw the line
          this->draw_line(iMax, pData);
          delete[] pData;
        }

      // map arrow heads
      if (!mCurrentAttributes.mStartHead.empty() && mCurrentAttributes.mStartHead != "none")
        {
          assert(pCurve->getNumElements() > 1);
          const CLRenderPoint* pStart = pCurve->getCurveElement(0);
          const CLPoint start = convert_to_absolute(pStart, pBB);
          CLPoint v;
          const CLRenderPoint* pEnd = pCurve->getCurveElement(1);
          const CLRenderCubicBezier* pCB = dynamic_cast<const CLRenderCubicBezier*>(pEnd);

          if (!pCB)
            {
              const CLPoint end = convert_to_absolute(pEnd, pBB);
              v = CLPoint(start.getX() - end.getX(), start.getY() - end.getY(), start.getZ() - end.getZ());
            }
          else
            {
              const CLRenderPoint* pEnd = new CLRenderPoint(pCB->basePoint1_X(), pCB->basePoint1_Y(), pCB->basePoint1_Z());
              const CLPoint end = convert_to_absolute(pEnd, pBB);
              delete pEnd;
              v = CLPoint(start.getX() - end.getX(), start.getY() - end.getY(), start.getZ() - end.getZ());
            }

          // we have to clear the arrow head attributes before we call the mapping
          // function.
          // If we don't do that and the line ending contains a curve, it will try
          // to map itself to the curve again which is an endless loop.
          this->save_current_attributes();
          std::string headId = mCurrentAttributes.mStartHead;
          this->map_arrow_head(start, v, headId);
          // set the old attributes again
          this->restore_current_attributes();
        }

      if (!mCurrentAttributes.mEndHead.empty() && mCurrentAttributes.mEndHead != "none")
        {
          const CLRenderPoint* pEnd = pCurve->getCurveElement(pCurve->getNumElements() - 1);
          const CLPoint end = convert_to_absolute(pEnd, pBB);

          const CLRenderCubicBezier* pCB = dynamic_cast<const CLRenderCubicBezier*>(pEnd);
          CLPoint v;

          if (!pCB)
            {
              const CLRenderPoint* pStart = pCurve->getCurveElement(pCurve->getNumElements() - 2);
              const CLPoint start = convert_to_absolute(pStart, pBB);
              v = CLPoint(end.getX() - start.getX(), end.getY() - start.getY(), end.getZ() - start.getZ());
            }
          else
            {
              const CLRenderPoint* pStart = new CLRenderPoint(pCB->basePoint2_X(), pCB->basePoint2_Y(), pCB->basePoint2_Z());
              const CLPoint start = convert_to_absolute(pStart, pBB);
              delete pStart;
              v = CLPoint(end.getX() - start.getX(), end.getY() - start.getY(), end.getZ() - start.getZ());
            }

          // we have to clear the arrow head attributes before we call the mapping
          // function.
          // If we don't do that and the line ending contains a curve, it will try
          // to map itself to the curve again which is an endless loop.
          this->save_current_attributes();
          std::string headId = mCurrentAttributes.mEndHead;
          this->map_arrow_head(end, v, headId);
          // set the old attributes again
          this->restore_current_attributes();
        }
    }

  this->restore_current_attributes();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

/**
 * Converts a given CLRenderPoint which can have relative values into a
 * layout CLPoint with only absolute values.
 * Even the absolute values of the point which are relative to the bounding box
 * are translated into absolute coordinates.
 */
const CLPoint CLLayoutRenderer::convert_to_absolute(const CLRenderPoint* pRenderPoint, const CLBoundingBox* pBB)
{
  const CLRelAbsVector& x = pRenderPoint->x();
  const CLRelAbsVector& y = pRenderPoint->y();
  const CLRelAbsVector& z = pRenderPoint->z();
  const CLPoint* pPosition = &pBB->getPosition();
  const CLDimensions* pDimensions = &pBB->getDimensions();
  return CLPoint((x.getAbsoluteValue() + pDimensions->getWidth()*x.getRelativeValue() / 100.0) + pPosition->getX(),
                 (y.getAbsoluteValue() + pDimensions->getHeight()*y.getRelativeValue() / 100.0) + pPosition->getY(),
                 (z.getAbsoluteValue() + pDimensions->getDepth()*z.getRelativeValue() / 100.0) + pPosition->getZ());
}

/**
 * Method to draw a given layout with a given render resolver.
 */
void CLLayoutRenderer::draw_layout()
{
  // first we need to clear the screen
  // with the background color
  glDisable(GL_POLYGON_SMOOTH);
#ifdef COPASI_DEBUG

  if (this->mGLFunctionsInitialized == false)
    {
      this->initialize_gl_extension_functions();
    }

  glFogi(GL_FOG_MODE, GL_EXP);

  if (this->mHighlight == true)
    {
      glFogfv(GL_FOG_COLOR, this->mHighlightColor);
    }
  else
    {
      glFogfv(GL_FOG_COLOR, this->mFogColor);
    }

  glFogf(GL_FOG_DENSITY, 0.5);
  glHint(GL_FOG_HINT, GL_FASTEST);
  glFogi(GL_FOG_COORD_SRC, GL_FOG_COORD);
  glEnable(GL_FOG);
  GLfloat highlight = (GLfloat)this->mHighlight;
  GLfloat notHighlight = (GLfloat)(!this->mHighlight);
#endif // COPASI_DEBUG

  if (this->mpResolver)
    {
      //std::cout << "Drawing layout." << std::endl;
      const CLColorDefinition* pBackgroundColor = this->mpResolver->getBackgroundColor();
      GLfloat red = (GLfloat)(pBackgroundColor->getRed() / 255.0);
      GLfloat green = (GLfloat)(pBackgroundColor->getGreen() / 255.0);
      GLfloat blue = (GLfloat)(pBackgroundColor->getBlue() / 255.0);
      GLfloat alpha = (GLfloat)(pBackgroundColor->getAlpha() / 255.0);
#ifdef COPASI_DEBUG

      if (this->mHighlight == false)
        {
          // we have to generate fog on the background ourselfes
          red = (GLfloat)((red + this->mFogColor[0]) * 0.5);
          green = (GLfloat)((green + this->mFogColor[1]) * 0.5);
          blue = (GLfloat)((blue + this->mFogColor[2]) * 0.5);
          alpha = (GLfloat)((alpha + this->mFogColor[3]) * 0.5);
        }

#endif // COPASI_DEBUG
      glClearColor((GLclampf)red,
                   (GLclampf)green,
                   (GLclampf)blue,
                   (GLclampf)alpha);
      glClear(GL_COLOR_BUFFER_BIT);
      glPushMatrix();
      this->mCurrentAttributes.mX = 0.0;
      this->mCurrentAttributes.mY = 0.0;
      this->mCurrentAttributes.mZ = 0.0;
      this->mCurrentAttributes.mWidth = this->mpLayout->getDimensions().getWidth();
      this->mCurrentAttributes.mHeight = this->mpLayout->getDimensions().getHeight();
      const CLReactionGlyph* pRG = NULL;
      const CLMetabReferenceGlyph* pSRG = NULL;
      const CLTextGlyph* pTG = NULL;
      std::vector<const CLGraphicalObject*>::iterator it = this->mDrawables.begin(), endit = this->mDrawables.end();
      const CCopasiObject* pModelObject = NULL;
#ifdef COPASI_DEBUG
// this is needed to highlight or fog certain elements in the diagram
      std::set<const CCopasiObject*>::const_iterator end = this->mHighlightedModelObjects.end();
#endif // COPASI_DEBUG      

      while (it != endit)
        {
#ifdef COPASI_DEBUG
// this is needed to highlight or fog certain elements in the diagram
          pModelObject = (*it)->getModelObject();

          if (this->mpGlFogCoordfEXT != NULL)
            {
              if (pModelObject != NULL && this->mHighlightedModelObjects.find(pModelObject) != end)
                {
                  (*(this->mpGlFogCoordfEXT))(highlight);
                }
              else
                {
                  (*(this->mpGlFogCoordfEXT))(notHighlight);
                }
            }

#endif //COPASI_DEBUG
          pRG = dynamic_cast<const CLReactionGlyph*>(*it);
          pSRG = dynamic_cast<const CLMetabReferenceGlyph*>(*it);
          pTG = dynamic_cast<const CLTextGlyph*>(*it);
          std::map<const CLGraphicalObject*, const CLStyle*>::const_iterator styleIt;
          styleIt = this->mStyleMap.find(*it);

          if (styleIt == this->mStyleMap.end() || styleIt->second == NULL)
            {
              ++it;
              continue;
            }

          if ((pSRG != NULL && pSRG->getCurve().getNumCurveSegments() != 0))
            {
              // draw the layout curve
              // we need to set the state of the OpenGL state machine
              // save the curent state
              this->save_current_attributes();
              CLLayoutRenderer::extract_group_attributes(styleIt->second, &mCurrentAttributes);

              // only draw the line if the stroke width is a positive value
              // greater zero and if there is a stroke color defined
              if (mCurrentAttributes.mStrokeWidth > 0.0 && mCurrentAttributes.mStroke != "none")
                {
                  bool drawBasepoints = false;

                  if (this->mSelection.size() == 1 && (*this->mSelection.begin()) == pSRG)
                    {
                      drawBasepoints = true;
                    }

                  this->draw_curve(&pSRG->getCurve(), drawBasepoints);
                }

              this->restore_current_attributes();

              // if the curve is the only selected item, we draw the base points,
              // otherwise we only draw the selection frame
              if (this->mSelection.find(const_cast<CLGraphicalObject*>(*it)) != this->mSelection.end())
                {
                  CLBoundingBox* pBB = getCurveBoundingBox(&pSRG->getCurve());
                  this->drawSelectionBox(pBB->getPosition().getX(), pBB->getPosition().getY(),
                                         pBB->getDimensions().getWidth(), pBB->getDimensions().getHeight(), this->mSelection.size() == 1);
                  delete pBB;
                }
            }
          else if (pRG != NULL && pRG->getCurve().getNumCurveSegments() != 0)
            {
              // draw the layout curve
              // we need to set the state of the OpenGL state machine
              // save the curent state
              this->save_current_attributes();
              CLLayoutRenderer::extract_group_attributes(styleIt->second, &mCurrentAttributes);

              // only do something if the stroke width is a positive value
              // greater 0 and if there is a stroke color defined
              if (mCurrentAttributes.mStrokeWidth > 0.0 && mCurrentAttributes.mStroke != "none")
                {// set the state
                  bool drawBasepoints = false;

                  if (this->mSelection.size() == 1 && (*this->mSelection.begin()) == pRG)
                    {
                      drawBasepoints = true;
                    }

                  this->draw_curve(&pRG->getCurve(), drawBasepoints);
                  // reset the original state
                }

              this->restore_current_attributes();

              // if the curve is the only selected item, we draw the base points,
              // otherwise we only draw the selection frame
              if (this->mSelection.find(const_cast<CLGraphicalObject*>(*it)) != this->mSelection.end())
                {
                  CLBoundingBox* pBB = getCurveBoundingBox(&pRG->getCurve());
                  this->drawSelectionBox(pBB->getPosition().getX(), pBB->getPosition().getY(),
                                         pBB->getDimensions().getWidth(), pBB->getDimensions().getHeight(), this->mSelection.size() == 1);
                  delete pBB;
                }
            }
          else if (pTG != NULL)
            {
              //std::cout << "Drawing CLText*Glyph: " << pTG->getId() << std::endl;
              std::map<const CLTextGlyph*, const CLTextTextureSpec*>::const_iterator pos = this->mTextGlyphMap.find(pTG);
              assert(pos != this->mTextGlyphMap.end());

              if (pos->second != NULL && pos->second->mTextureName != 0)
                {
                  //std::cout <<  "Texture for text glyph found." << std::endl;
                  // in order to position text glyphs corectly, we have to move them up by their mAscent
                  CLBoundingBox bb = pTG->getBoundingBox();
                  CLPoint* pP = &bb.getPosition();
                  bb.setPosition(*pP);
                  this->draw_text(styleIt->second, &bb, pos->second);

                  // draw the selection frame
                  // if it is the only selected element, we also draw the resize handles
                  if (this->mSelection.find(const_cast<CLGraphicalObject*>(*it)) != this->mSelection.end())
                    {
                      // we need to adjust the bounding box the same way we adjust the text glyphs
                      this->drawSelectionBox(bb.getPosition().getX(), bb.getPosition().getY() + pos->second->mAscent,
                                             bb.getDimensions().getWidth(), bb.getDimensions().getHeight(), this->mSelection.size() == 1);
                    }
                }
            }
          else
            {
              const CLBoundingBox* pBB = &(*it)->getBoundingBox();
              this->draw_object(styleIt->second, pBB);

              // draw the selection frame
              // if it is the only selected element, we also draw the resize handles
              if (this->mSelection.find(const_cast<CLGraphicalObject*>(*it)) != this->mSelection.end())
                {
                  this->drawSelectionBox(pBB->getPosition().getX(), pBB->getPosition().getY(),
                                         pBB->getDimensions().getWidth(), pBB->getDimensions().getHeight(), this->mSelection.size() == 1);
                }
            }

          ++it;
        }

      // flush the GL queue
      glPopMatrix();
      // draw the selection box
      this->draw_selection_box();
      glFlush();
      //std::cout << "Drawing finished." << std::endl << std::endl;
    }

  glDisable(GL_FOG);
}

/**
 * Method to draw a text object specified by it's bounding box
 * and the style with which it should be drawn as well as the actual
 * string.
 */
void CLLayoutRenderer::draw_text(const CLStyle* pStyle, const CLBoundingBox* pBB, const CLTextTextureSpec* pTexture)
{
  // set the attributes
  this->save_current_attributes();
  // for text elements, only the 1d attributes and the special text
  // attributes are relevant
  CLLayoutRenderer::extract_1d_attributes(pStyle->getGroup(), &mCurrentAttributes);
  CLLayoutRenderer::extract_text_attributes(pStyle->getGroup(), &mCurrentAttributes);

  // we only draw the text if there is a stroke color to draw it with
  if (!mCurrentAttributes.mStroke.empty() && mCurrentAttributes.mStroke != "none")
    {
      // with the new interpretation of the text alignment attributes,
      // we have to specify different offset attributes
      // if the horizontal laignment is middle, we specify the middle of the box
      // as x offset and if the alignment is end, we specify the end as the x offset
      // likewise for the vertical alignment and the y offset
      double xOffset = 0.0;
      double yOffset = 0.0;

      if (this->mCurrentAttributes.mTextAnchor == CLText::ANCHOR_MIDDLE)
        {
          xOffset = pBB->getDimensions().getWidth() * 0.5;;
        }
      else if (this->mCurrentAttributes.mTextAnchor == CLText::ANCHOR_END)
        {
          xOffset = pBB->getDimensions().getWidth();
        }

      if (this->mCurrentAttributes.mVTextAnchor == CLText::ANCHOR_MIDDLE)
        {
          yOffset = pBB->getDimensions().getHeight() * 0.5;
          std::cout << "middle" << std::endl;
        }
      else if (this->mCurrentAttributes.mVTextAnchor == CLText::ANCHOR_BOTTOM)
        {
          yOffset = pBB->getDimensions().getHeight();
          std::cout << "bottom" << std::endl;
        }

      this->draw_text(pTexture, xOffset, yOffset, 0.0, pBB);
    }

  //restore the attributes
  this->restore_current_attributes();
}

/**
 * Method to resolve the text that belongs to a text glyph.
 */
const std::string CLLayoutRenderer::resolve_text(const CLTextGlyph* pTextGlyph)
{
  // CLTextGlyph already knows how to reslve the text
  return pTextGlyph->getText();
}

/**
 * Method to draw an arbitrary object specified by it's bounding box
 * and the style with which it should be drawn.
 */
void CLLayoutRenderer::draw_object(const CLStyle* pStyle, const CLBoundingBox* pBB)
{
  this->draw_group(pStyle->getGroup(), pBB);
}

/**
 * Method to draw an arbitrary object specified by it's bounding box
 * and the style with which it should be drawn.
 */
void CLLayoutRenderer::draw_group(const CLGroup* pGroup, const CLBoundingBox* pBB)
{
  // set the group attributes
  this->save_current_attributes();
  CLLayoutRenderer::extract_group_attributes(pGroup, &mCurrentAttributes);
  mCurrentAttributes.mX = pBB->getPosition().getX();
  mCurrentAttributes.mY = pBB->getPosition().getY();
  mCurrentAttributes.mZ = pBB->getPosition().getZ();
  mCurrentAttributes.mWidth = pBB->getDimensions().getWidth();
  mCurrentAttributes.mHeight = pBB->getDimensions().getHeight();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // apply the current transformation
  if (memcmp(mCurrentAttributes.mpTransform, Transformation::getIdentityMatrix(), 12*sizeof(double)))
    {
      // move back to the current offset
      glTranslated(this->mCurrentAttributes.mX, this->mCurrentAttributes.mY, this->mCurrentAttributes.mZ);
      GLdouble* matrix = new GLdouble[16];
      CLLayoutRenderer::createGLMatrix(mCurrentAttributes.mpTransform, matrix);
      glMultMatrixd(matrix);
      delete[] matrix;
      // move to 0.0,0.0,0.0
      glTranslated(-this->mCurrentAttributes.mX, -this->mCurrentAttributes.mY, -this->mCurrentAttributes.mZ);
    }

  // draw each element
  const CCopasiObject* pObject = NULL;
  size_t i, iMax = pGroup->getNumElements();

  for (i = 0; i < iMax; ++i)
    {
      pObject = pGroup->getElement(i);
      assert(pObject != NULL);
      // find out what kind of element it is
      const CLEllipse* pEllipse = dynamic_cast<const CLEllipse*>(pObject);

      if (pEllipse != NULL)
        {
          CLLayoutRenderer::draw_ellipse(pEllipse, pBB);
        }
      else
        {
          const CLGroup* pRenderGroup = dynamic_cast<const CLGroup*>(pObject);

          if (pRenderGroup != NULL)
            {
              CLLayoutRenderer::draw_group(pRenderGroup, pBB);
            }
          else
            {
              const CLImage* pImage = dynamic_cast<const CLImage*>(pObject);

              if (pImage != NULL)
                {
                  CLLayoutRenderer::draw_image(pImage, pBB);
                }
              else
                {
                  const CLPolygon* pPolygon = dynamic_cast<const CLPolygon*>(pObject);

                  if (pPolygon != NULL)
                    {
                      CLLayoutRenderer::draw_polygon(pPolygon, pBB);
                    }
                  else
                    {
                      const CLRectangle* pRectangle = dynamic_cast<const CLRectangle*>(pObject);

                      if (pRectangle != NULL)
                        {
                          CLLayoutRenderer::draw_rectangle(pRectangle, pBB);
                        }
                      else
                        {
                          const CLRenderCurve* pCurve = dynamic_cast<const CLRenderCurve*>(pObject);

                          if (pCurve != NULL)
                            {
                              CLLayoutRenderer::draw_curve(pCurve, pBB);
                            }
                          else
                            {
                              const CLText* pText = dynamic_cast<const CLText*>(pObject);

                              if (pText != NULL)
                                {
                                  CLLayoutRenderer::draw_text(pText, pBB);
                                }
                              else
                                {
                                  throw pObject;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

  // restore the attributes
  this->restore_current_attributes();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

/**
 * Resize method that is called whenever the GL window is resized.
 */
void CLLayoutRenderer::resize(GLsizei w, GLsizei h)
{
  // setup viewport, projection etc.:
  this->mW = w;
  this->mH = h;
  glViewport(0, 0, (GLint)w, (GLint)h);
  glMatrixMode(GL_PROJECTION);    // Select The Projection Matrix
  glLoadIdentity();             // Reset The Projection Matrix
  this->analyse_render_information(mX, mY, mX + mW / this->mZoomFactor, mY + mH / this->mZoomFactor);
  gluOrtho2D((GLdouble)mX,
             (GLdouble)(mX + w / this->mZoomFactor * this->mAspect),
             (GLdouble)(mY + h / this->mZoomFactor),
             (GLdouble)mY); // y: 0.0 is bottom left instead of top left as in SBML
  glMatrixMode(GL_MODELVIEW);  // Select The Modelview Matrix
}

/**
 * Method that converts a color value or a color id into a color array for
 * OpenGL.
 */
void CLLayoutRenderer::resolve_color(const std::string& color, GLubyte array[4])
{
  if (!color.empty() && color != "none")
    {
      if (color[0] == '#')
        {
          CLColorDefinition cd;
          cd.setColorValue(color);
          array[0] = (GLubyte)cd.getRed();
          array[1] = (GLubyte)cd.getGreen();
          array[2] = (GLubyte)cd.getBlue();
          array[3] = (GLubyte)cd.getAlpha();
        }
      else
        {
          const CLColorDefinition* pColor = this->mpResolver->getColorDefinition(color);

          if (!pColor)
            {
              // TODO actually this is an error and should lead to an
              // exception
              throw 0;
            }
          else
            {
              array[0] = (GLubyte)pColor->getRed();
              array[1] = (GLubyte)pColor->getGreen();
              array[2] = (GLubyte)pColor->getBlue();
              array[3] = (GLubyte)pColor->getAlpha();
            }
        }
    }
  else
    {
      array[0] = 0;
      array[1] = 0;
      array[2] = 0;
      array[3] = 0;
    }
}

/**
 * Method to draw a render text object.
 */
void CLLayoutRenderer::draw_text(const CLText* pText, const CLBoundingBox* pBB)
{
  if (pText->isSetText())
    {
      // set the attributes
      this->save_current_attributes();
      // for text elements, only the 1d attributes and the special text
      // attributes are relevant
      CLLayoutRenderer::extract_1d_attributes(pText, &mCurrentAttributes);
      CLLayoutRenderer::extract_text_attributes(pText, &mCurrentAttributes);
      // draw the string
      double x = pText->getX().getAbsoluteValue() + pText->getX().getRelativeValue() / 100.0 * pBB->getDimensions().getWidth();
      double y = pText->getY().getAbsoluteValue() + pText->getY().getRelativeValue() / 100.0 * pBB->getDimensions().getHeight();
      double z = pText->getZ().getAbsoluteValue() + pText->getZ().getRelativeValue() / 100.0 * pBB->getDimensions().getDepth();
      std::map<const CLText*, const CLTextTextureSpec*>::const_iterator pos = this->mTextMap.find(pText);
      assert(pos != this->mTextMap.end());

      if (pos->second != NULL && pos->second->mTextureName != 0)
        {
          //std::cout << "Drawing text \"" << pText->getText() << "\"." << std::endl;
          CLLayoutRenderer::draw_text(pos->second, x, y, z, pBB);
        }

      //restore the attributes
      this->restore_current_attributes();
    }
}

/**
 * Method to draw a string at the given position within the given bounding box.
 */
void CLLayoutRenderer::draw_text(const CLTextTextureSpec* pTexture, double x, double y, double z, const CLBoundingBox* pBB)
{
  //std::cout << "Drawing text with texture at " << pTexture << std::endl;
  if (pTexture != NULL && pBB != NULL)
    {
      // create a texture for the text.
      // map the origin of the texture to x,y,z
      // map the texture point at textwidth, textheight to x+textwidth,
      // y+textheight
      // This might lead to text that goes beyone the dimensions of the bounding
      // box, but since the user has asked for a text of this size, we just draw
      // it
      std::map<std::string, CLRGBAColor>::const_iterator pos = this->mColorMap.find(mCurrentAttributes.mStroke);
      assert(pos != this->mColorMap.end());
      const CLRGBAColor& c = pos->second;
      glColor4ub(c.mR, c.mG, c.mB, c.mA);
      double xOffset = x + pBB->getPosition().getX();
      double yOffset = y + pBB->getPosition().getY();
      double zOffset = z + pBB->getPosition().getZ();

      // position the text according to how the anchor is set
      if (mCurrentAttributes.mTextAnchor == CLText::ANCHOR_MIDDLE)
        {
          // the new interpretation is that the horizontal center of the text is at xOffset,yOffset
          xOffset -= pTexture->mTextWidth / (2.0 * this->mZoomFactor);
        }
      else if (mCurrentAttributes.mTextAnchor == CLText::ANCHOR_END)
        {
          // the new interpretation is that xOffset specifies the horizontal end of the text, so
          // the start has to be placed at xOffset-pTexture->mTextWidth / this->mZoomFactor
          xOffset -= pTexture->mTextWidth / this->mZoomFactor;
        }

      // do vertical positioning
      if (mCurrentAttributes.mVTextAnchor == CLText::ANCHOR_MIDDLE)
        {
          // the text is vertically centered in the box
          yOffset -= pTexture->mTextHeight / (2.0 * this->mZoomFactor);
        }
      else if (mCurrentAttributes.mVTextAnchor == CLText::ANCHOR_BOTTOM)
        {
          // the lower edge of the text is located at the top edge of the box
          // since heigher y values are downward, this alligns the text at
          // the lower end of the box
          yOffset -= pTexture->mTextHeight / this->mZoomFactor;
        }

      // the yOffset has to consider the mAscent of the text because the
      // placement of the text should be relative to the baseline
      //std::cout << "current bounding box position: " << pBB->getPosition().getX() << "," << pBB->getPosition().getY() << std::endl;
      //std::cout << "texture size: " << pTexture->textureWidth << "x" << pTexture->textureHeight << std::endl;
      //std::cout << "text size: " << pTexture->textWidth << "x" << pTexture->textHeight << std::endl;
      //std::cout << "text mAscent: " << pTexture->mAscent << std::endl;
      //std::cout << "y offset at: " << y << std::endl;
      //std::cout << "placing baseline at: " << yOffset << std::endl;
      //std::cout << "the upper side of the textured box will be located at: " << yOffset << std::endl;

      //
      // we draw a rectangle in the current stroke color. At places where the texture is black, the underlying color should be seen.
      // load the texture
      // enable 2D texturing
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, pTexture->mTextureName);
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glTranslated(xOffset, yOffset, zOffset);

      // apply the current transformation
      if (memcmp(mCurrentAttributes.mpTransform, Transformation::getIdentityMatrix(), 12*sizeof(double)))
        {
          // move back to the current offset
          glTranslated(this->mCurrentAttributes.mX, this->mCurrentAttributes.mY, this->mCurrentAttributes.mZ);
          GLdouble* matrix = new GLdouble[16];
          CLLayoutRenderer::createGLMatrix(mCurrentAttributes.mpTransform, matrix);
          glMultMatrixd(matrix);
          delete[] matrix;
          // move to 0.0,0.0,0.0
          glTranslated(-this->mCurrentAttributes.mX, -this->mCurrentAttributes.mY, -this->mCurrentAttributes.mZ);
        }

      //std::cout << "zoom factor: " << this->mZoomFactor << std::endl;
      //std::cout << "Drawing texture " << pTexture->mTextureName << " with:" << std::endl;
      //std::cout << "text height: "  << pTexture->mTextHeight << " text width: " << pTexture->mTextWidth << std::endl;
      //std::cout << "texture height: "  << pTexture->mTextureHeight << " texture width: " << pTexture->mTextureWidth << std::endl;
      //std::cout << "texture scale: " << pTexture->mScale << std::endl;
      double widthRatio = pTexture->mTextWidth /** pTexture->mScale*/ / pTexture->mTextureWidth;
      //std::cout << "width ratio: " << widthRatio << std::endl;
      double heightRatio = pTexture->mTextHeight /** pTexture->mScale*/ / pTexture->mTextureHeight;
      //std::cout << "height ratio: " << heightRatio << std::endl;
      glBegin(GL_POLYGON);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(0.0, 0.0, 0.0);
      glTexCoord2d(0.0, 1.0 - heightRatio);
      glVertex3d(0.0, pTexture->mTextHeight / pTexture->mScale, 0.0);
      glTexCoord2d(widthRatio, 1.0 - heightRatio);
      glVertex3d(pTexture->mTextWidth / pTexture->mScale, pTexture->mTextHeight / pTexture->mScale, 0.0);
      glTexCoord2d(widthRatio, 1.0);
      glVertex3d(pTexture->mTextWidth / pTexture->mScale, 0.0, 0.0);
      glEnd();
      glPopMatrix();
      // disable the 2D texture again
      glDisable(GL_TEXTURE_2D);
    }
}

/**
 * Method to draw a render ellipse object.
 */
void CLLayoutRenderer::draw_ellipse(const CLEllipse* pEllipse, const CLBoundingBox* pBB)
{
  // store and change the attributes
  this->save_current_attributes();
  CLLayoutRenderer::extract_2d_attributes(pEllipse, &mCurrentAttributes);
  // draw the ellipse
  // first we calculate the data points for the ellipse
  double x = pBB->getPosition().getX() + pEllipse->getCX().getAbsoluteValue() + pEllipse->getCX().getRelativeValue() / 100.0 * pBB->getDimensions().getWidth();
  double y = pBB->getPosition().getY() + pEllipse->getCY().getAbsoluteValue() + pEllipse->getCY().getRelativeValue() / 100.0 * pBB->getDimensions().getHeight();
  double z = pBB->getPosition().getZ() + pEllipse->getCZ().getAbsoluteValue() + pEllipse->getCZ().getRelativeValue() / 100.0 * pBB->getDimensions().getDepth();
  double rx = pEllipse->getRX().getAbsoluteValue() + pEllipse->getRX().getRelativeValue() / 100.0 * pBB->getDimensions().getWidth();
  double ry = pEllipse->getRY().getAbsoluteValue() + pEllipse->getRY().getRelativeValue() / 100.0 * pBB->getDimensions().getHeight();
  // we add an additional datapoint to close the loop. This way we don't need
  // the draw_loop method, but all is handled in draw_line
  // this also makes line stippling easier for OpenGL < 2.0
  GLdouble* pData = new GLdouble[3*(NUM_CIRCLE_SEGMENTS+1)];
  unsigned int i;
  double delta_phi = 2 * M_PI / NUM_CIRCLE_SEGMENTS;
  double phi = 0.0;
  size_t index = 0;

  for (i = 0; i < NUM_CIRCLE_SEGMENTS; ++i)
    {
      // TODO it would be enough to calculate only one quadrant
      phi = i * delta_phi;
      pData[index++] = rx * rx * cos(phi) / sqrt(rx * rx * pow(cos(phi), 2) + ry * ry * pow(sin(phi), 2));
      pData[index++] = ry * ry * sin(phi) / sqrt(rx * rx * pow(cos(phi), 2) + ry * ry * pow(sin(phi), 2));
      pData[index++] = 0.0;
    }

  // close the loop
  pData[index++] = pData[0];
  pData[index++] = pData[1];
  pData[index] = pData[2];
  this->draw_datapoints(pData, NUM_CIRCLE_SEGMENTS + 1, pBB, false, (GLfloat)x, (GLfloat)y, (GLfloat)z);
  delete[] pData;
  // restore the attributes
  this->restore_current_attributes();
}

/**
 * Method to draw a render image object.
 */
void CLLayoutRenderer::draw_image(const CLImage* pImage, const CLBoundingBox* pBB)
{
  // the ransformation attributes are the only ones that influence the
  // drawing of an image
  this->save_current_attributes();
  CLLayoutRenderer::extract_transformation_attributes(pImage, &mCurrentAttributes);
  // draw the actual image
  const CLTextureSpec* pTexture = NULL;

  if (pImage->isSetImageReference())
    {
      std::string reference = pImage->getImageReference();
      std::map<std::string, const CLTextureSpec*>::const_iterator pos = this->mImageMap.find(reference);

      if (pos == this->mImageMap.end())
        {
          // we need to create the texture
          if (this->mpImageTexturizer != NULL)
            {
              pTexture = (*this->mpImageTexturizer)(reference, this->mBaseDir);
              this->mImageMap[reference] = pTexture;
              pos = this->mImageMap.find(reference);
              assert(pos != this->mImageMap.end());
            }
        }

      assert(pos != this->mImageMap.end());
      pTexture = pos->second;
      //assert(pTexture);
    }

  if (pTexture)
    {
      // draw the texture in the correct place
      // load the texture
      assert(pTexture->mTextureName != 0);
      glBindTexture(GL_TEXTURE_2D, pTexture->mTextureName);
      const CLDimensions* d = &pBB->getDimensions();
      double width = pImage->getWidth().getAbsoluteValue() + pImage->getWidth().getRelativeValue() / 100.0 * d->getWidth();
      double height = pImage->getHeight().getAbsoluteValue() + pImage->getHeight().getRelativeValue() / 100.0 * d->getHeight();
      CLRenderPoint p(pImage->getX(), pImage->getY());
      CLPoint point = CLLayoutRenderer::convert_to_absolute(&p, pBB);
      // apply the current transformation
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();

      if (memcmp(mCurrentAttributes.mpTransform, Transformation::getIdentityMatrix(), 12*sizeof(double)))
        {
          // move back to the current offset
          glTranslated(this->mCurrentAttributes.mX, this->mCurrentAttributes.mY, this->mCurrentAttributes.mZ);
          GLdouble* matrix = new GLdouble[16];
          CLLayoutRenderer::createGLMatrix(mCurrentAttributes.mpTransform, matrix);
          glMultMatrixd(matrix);
          delete[] matrix;
          // move to 0.0,0.0,0.0
          glTranslated(-this->mCurrentAttributes.mX, -this->mCurrentAttributes.mY, -this->mCurrentAttributes.mZ);
        }

      // enable 2D texturing
      glEnable(GL_TEXTURE_2D);
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glTranslated(point.getX(), point.getY(), point.getZ());
      glBegin(GL_POLYGON);
      glTexCoord2d(0.0, 0.0);
      glVertex3d(0.0, 0.0, 0.0);
      glTexCoord2d(0.0, 1.0);
      glVertex3d(0.0, height, 0.0);
      glTexCoord2d(1.0, 1.0);
      glVertex3d(width, height, 0.0);
      glTexCoord2d(1.0, 0.0);
      glVertex3d(width, 0.0, 0.0);
      glEnd();
      glPopMatrix();
      // disable the 2D texture again
      glDisable(GL_TEXTURE_2D);
    }
  else
    {
      // TODO at least create some kind of error message
    }

  // restore the attributes
  this->restore_current_attributes();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

/**
 * Method to draw a render polygon object.
 */
void CLLayoutRenderer::draw_polygon(const CLPolygon* pPolygon, const CLBoundingBox* pBB)
{
  /*
   * Old code to draw the polygon when it consists of only straight lines.
      size_t numPoints=pPolygon->getNumElements()+1;
  if(numPoints>1)
  {
    // store and change the attributes
    this->save_current_attributes();
    CLLayoutRenderer::extract_2d_attributes(pPolygon,&mCurrentAttributes);
    // create the data points
    GLdouble* pData=new GLdouble[3*numPoints];
    size_t i,iMax=numPoints-1;
    CLPoint p;
    const CLRenderPoint* pP;
    size_t index=0;
    for(i=0;i<iMax;++i)
    {
      pP=pPolygon->getElement(i);
      assert(pP);
      p=CLLayoutRenderer::convert_to_absolute(pP,pBB);
      pData[index++]=p.getX();
      pData[index++]=p.getY();
      pData[index++]=p.getZ();
    }
    pData[index++]=pData[0];
    pData[index++]=pData[1];
    pData[index]=pData[2];
    */

  // the first one has to be a point
  // store and change the attributes
  if (pPolygon->getNumElements() > 1)
    {
      this->save_current_attributes();
      CLLayoutRenderer::extract_2d_attributes(pPolygon, &mCurrentAttributes);
      const CLRenderPoint* pStart = pPolygon->getElement(0);
      CLRenderPoint end, bp1, bp2;
      CLPoint p1 = convert_to_absolute(pStart, pBB);
      CLPoint p2, p3, p4;
      std::vector<simple_point> v;
      // there are going to be at least iMax elements in the vector
      size_t i, iMax = pPolygon->getNumElements();
      v.reserve(iMax);
      simple_point p;
      p.mX = p1.getX();
      p.mY = p1.getY();
      p.mZ = p1.getZ();
      v.push_back(p);
      GLdouble* pData = NULL;
      const CLRenderPoint* pP;
      const CLRenderCubicBezier* pCB;

      for (i = 1; i < iMax; ++i)
        {
          pP = pPolygon->getElement(i);
          pCB = dynamic_cast<const CLRenderCubicBezier*>(pP);

          if (pCB != NULL)
            {
              end = CLRenderPoint(pCB->x(), pCB->y(), pCB->z());
              bp1 = CLRenderPoint(pCB->basePoint1_X(), pCB->basePoint1_Y(), pCB->basePoint1_Z());
              bp2 = CLRenderPoint(pCB->basePoint2_X(), pCB->basePoint2_Y(), pCB->basePoint2_Z());
              p2 = convert_to_absolute(&end, pBB);
              p3 = convert_to_absolute(&bp1, pBB);
              p4 = convert_to_absolute(&bp2, pBB);
              pData = new GLdouble[3*NUM_BEZIER_POINTS];
              CLLayoutRenderer::calculate_cubicbezier(p1.getX(), p1.getY(), p1.getZ(),
                                                      p3.getX(), p3.getY(), p3.getZ(),
                                                      p4.getX(), p4.getY(), p4.getZ(),
                                                      p2.getX(), p2.getY(), p2.getZ(),
                                                      NUM_BEZIER_POINTS, pData);
              size_t j;
              size_t index = 0;

              for (j = 0; j < NUM_BEZIER_POINTS; ++j)
                {
                  p.mX = pData[index++];
                  p.mY = pData[index++];
                  p.mZ = pData[index++];
                  v.push_back(p);
                }

              delete[] pData;
            }
          else
            {
              end = CLRenderPoint(pP->x(), pP->y(), pP->z());
              p2 = convert_to_absolute(&end, pBB);
              p.mX = p2.getX();
              p.mY = p2.getY();
              p.mZ = p2.getZ();
              v.push_back(p);
            }

          // this end is the next start
          p1 = p2;
        }

      iMax = v.size();

      if (iMax > 1)
        {
          pData = new GLdouble[3*(iMax+1)];
          size_t index = 0;
          const simple_point* pSimple = NULL;

          for (i = 0; i < iMax; ++i)
            {
              pSimple = &v[i];
              pData[index++] = pSimple->mX;
              pData[index++] = pSimple->mY;
              pData[index++] = pSimple->mZ;
            }

          pData[index++] = pData[0];
          pData[index++] = pData[1];
          pData[index] = pData[2];
          // draw the polygon
          this->draw_datapoints(pData, iMax + 1, pBB, true);
          delete[] pData;
        }

      // restore the attributes
      this->restore_current_attributes();
    }
}

/**
 * Method to draw a render rectangle object.
 */
void CLLayoutRenderer::draw_rectangle(const CLRectangle* pRectangle, const CLBoundingBox* pBB)
{
  // store and change the attributes
  this->save_current_attributes();
  CLLayoutRenderer::extract_2d_attributes(pRectangle, &mCurrentAttributes);
  // draw the rectangle
  // first we calculate the points of the rectangle
  CLRenderPoint rp(pRectangle->getX(), pRectangle->getY(), pRectangle->getZ());
  CLPoint p = CLLayoutRenderer::convert_to_absolute(&rp, pBB);
  CLRelAbsVector v = pRectangle->getWidth();
  double width = v.getAbsoluteValue() + (v.getRelativeValue() / 100.0) * pBB->getDimensions().getWidth();
  v = pRectangle->getHeight();
  double height = v.getAbsoluteValue() + (v.getRelativeValue() / 100.0) * pBB->getDimensions().getHeight();
  v = pRectangle->getRadiusX();
  double rx = v.getAbsoluteValue() + (v.getRelativeValue() / 100.0) * width;
  v = pRectangle->getRadiusY();
  double ry = v.getAbsoluteValue() + (v.getRelativeValue() / 100.0) * height;

  // make sure rx and ry are not greater than half the width or height of the
  // rectangle.
  if (rx > width / 2.0) rx = width / 2.0;

  if (ry > height / 2.0) ry = height / 2.0;

  size_t numPoints = 4;

  if (rx > 0.0 && ry > 0.0)
    {
      // we have four corners
      // plus 4 points for the straight lines
      numPoints = 4 * (NUM_CORNER_SEGMENTS + 1);
    }

  // we need to reserve space for all data points and each point has three
  // values
  // we add an additonal data point to close the loop
  GLdouble* pData = new GLdouble[(numPoints+1)*3];
  double x = p.getX();
  double y = p.getY();
  double z = p.getZ();
  // now we fill the data array
  size_t index = 0;

  if (rx > 0.0 && ry > 0.0)
    {
      size_t i = 0;
      pData[i++] = 0.0;
      pData[i++] = ry;
      pData[i++] = 0.0;
      pData[i++] = 0.0;
      pData[i++] = height - ry;
      pData[i++] = 0.0;
      i += (NUM_CORNER_SEGMENTS - 1) * 3;
      pData[i++] = rx;
      pData[i++] = height;
      pData[i++] = 0.0;
      pData[i++] = width - rx;
      pData[i++] = height;
      pData[i++] = 0.0;
      i += (NUM_CORNER_SEGMENTS - 1) * 3;
      pData[i++] = width;
      pData[i++] = height - ry;
      pData[i++] = 0.0;
      pData[i++] = width;
      pData[i++] = ry;
      pData[i++] = 0.0;
      i += (NUM_CORNER_SEGMENTS - 1) * 3;
      pData[i++] = width - rx;
      pData[i++] = 0.0;
      pData[i++] = 0.0;
      pData[i++] = rx;
      pData[i++] = 0.0;
      pData[i] = 0.0;
      double delta = M_PI / (2.0 * NUM_CORNER_SEGMENTS);
      double phi = delta;
      double dx, dy, dx_inv, dy_inv;
      index = 0;

      for (i = 0; i < NUM_CORNER_SEGMENTS - 1; ++i)
        {
          index = (2 + i) * 3;
          dx = rx * sin(phi);
          dy = ry * cos(phi);
          dx_inv = rx * sin(M_PI / 2.0 - phi);
          dy_inv = ry * cos(M_PI / 2.0 - phi);
          // the first corner is mirrored, so we switch dx and dy
          pData[index] = rx - dx_inv;
          pData[index+1] = height - ry + dy_inv;
          pData[index+2] = 0.0;
          // the second corner is actually the one, we calculate
          index += (NUM_CORNER_SEGMENTS + 1) * 3;
          pData[index] = width - rx + dx;
          pData[index+1] = height - ry + dy;
          pData[index+2] = 0.0;
          // third corner is again mirrored
          index += (NUM_CORNER_SEGMENTS + 1) * 3;
          pData[index] = width - rx + dx_inv;
          pData[index+1] = ry - dy_inv;
          pData[index+2] = 0.0;
          // the fourth corner
          index += (NUM_CORNER_SEGMENTS + 1) * 3;
          pData[index] = rx - dx;
          pData[index+1] = ry - dy;
          pData[index+2] = 0.0;
          phi += delta;
        }
    }
  else
    {
      // first corner
      pData[0] = 0.0;
      pData[1] = 0.0;
      pData[2] = 0.0;
      // second corner
      pData[3] = 0.0;
      pData[4] = height;
      pData[5] = 0.0;
      // third corner
      pData[6] = width;
      pData[7] = height;
      pData[8] = 0.0;
      // fourth corner
      pData[9] = width;
      pData[10] = 0.0;
      pData[11] = 0.0;
    }

  index = 3 * numPoints;
  // we close the loop
  pData[index++] = pData[0];
  pData[index++] = pData[1];
  pData[index] = pData[2];
  this->draw_datapoints(pData, numPoints + 1, pBB, false, (GLfloat)x, (GLfloat)y, (GLfloat)z);
  // delete the data again
  delete[] pData;
  //
  // restore the attributes
  this->restore_current_attributes();
}

/**
 * Extracts the group attributes from the given group.
 */
void CLLayoutRenderer::extract_group_attributes(const CLGroup* pGroup, CLGroupAttributes* attributes)
{
  CLLayoutRenderer::extract_2d_attributes(pGroup, attributes);
  CLLayoutRenderer::extract_text_attributes(pGroup, attributes);
  CLLayoutRenderer::extract_arrowhead_information(pGroup, attributes);
}

/**
 * Extracts the attributes from the given one dimensional object.
 */
void CLLayoutRenderer::extract_1d_attributes(const CLGraphicalPrimitive1D* pObject, CLGroupAttributes* attributes)
{
  extract_transformation_attributes(pObject, attributes);

  if (pObject->isSetStroke())
    {
      attributes->mStroke = pObject->getStroke();
    }

  if (pObject->isSetStrokeWidth())
    {
      attributes->mStrokeWidth = pObject->getStrokeWidth();
    }

  if (pObject->isSetDashArray())
    {
      attributes->mStrokeDasharray = pObject->getDashArray();
    }
}

/**
 * Extracts the attributes from the given two dimensional object.
 */
void CLLayoutRenderer::extract_2d_attributes(const CLGraphicalPrimitive2D* pObject, CLGroupAttributes* attributes)
{
  CLLayoutRenderer::extract_1d_attributes(pObject, attributes);

  if (pObject->isSetFill())
    {
      attributes->mFill = pObject->getFillColor();
    }

  if (pObject->isSetFillRule())
    {
      attributes->mFillRule = pObject->getFillRule();
    }
}

/**
 * Extracts the attributes from the given transformation object.
 */
void CLLayoutRenderer::extract_transformation_attributes(const CLTransformation* pObject, CLGroupAttributes* attributes)
{
  attributes->mpTransform = new double[12];

  if (pObject->isSetMatrix())
    {
      memcpy(attributes->mpTransform, pObject->getMatrix(), 12*sizeof(double));
    }
  else
    {
      memcpy(attributes->mpTransform, Transformation::getIdentityMatrix(), 12*sizeof(double));
    }
}

/**
 * This method calculates a texture for a given gradient definition and a
 * given size.
 * The data object has to be a vector that can store RGBA values for a rectangle
 * of the given size. The memory has to be allocated before calling the method.
 * The scale specifies by how much the original box has been scaled.
 */
void CLLayoutRenderer::create_gradient_texture(unsigned int size, GLubyte* pData, const CLGradientBase* pGradient, double z_value)
{
  if (pGradient)
    {
      const CLLinearGradient* pLG = dynamic_cast<const CLLinearGradient*>(pGradient);

      if (pLG != NULL)
        {
          CLLayoutRenderer::create_linear_gradient_texture(size, pData, pLG, z_value);
        }
      else
        {
          const CLRadialGradient* pRG = dynamic_cast<const CLRadialGradient*>(pGradient);

          if (pRG != NULL)
            {
              CLLayoutRenderer::create_radial_gradient_texture(size, pData, pRG, z_value);
            }
          else
            {
              throw 0;
            }
        }
    }
}

/**
 * This method calculates a texture for a given linear gradient definition
 * and a given size.
 * The data object has to be a vector that can store RGBA values for a rectangle
 * of the given size. The memory has to be allocated before calling the method.
 * The scale specifies by how much the original box has been scaled.
 */
void CLLayoutRenderer::create_linear_gradient_texture(unsigned int size, GLubyte* pData, const CLLinearGradient* pGradient, double /*z_value*/)
{
  // first calculate the gradient vector
  // we need to consider the scale
  CLGradientStops stops(pGradient, this->mColorMap);
  double x1 = pGradient->getXPoint1().getAbsoluteValue() * this->mZoomFactor + (pGradient->getXPoint1().getRelativeValue() / 100.0 * size);
  double y1 = pGradient->getYPoint1().getAbsoluteValue() * this->mZoomFactor + (pGradient->getYPoint1().getRelativeValue() / 100.0 * size);
  double z1 = pGradient->getZPoint1().getAbsoluteValue() * this->mZoomFactor + (pGradient->getZPoint1().getRelativeValue() / 100.0 * 0.0);
  double x2 = pGradient->getXPoint2().getAbsoluteValue() * this->mZoomFactor + (pGradient->getXPoint2().getRelativeValue() / 100.0 * size);
  double y2 = pGradient->getYPoint2().getAbsoluteValue() * this->mZoomFactor + (pGradient->getYPoint2().getRelativeValue() / 100.0 * size);
  double z2 = pGradient->getZPoint2().getAbsoluteValue() * this->mZoomFactor + (pGradient->getZPoint2().getRelativeValue() / 100.0 * 0.0);
  // for each point we need to calculate the distance from p1 along the
  // vector v(p1,p2)
  // first we need the plane that is perpendicular to the vector v(p1,p2)
  // the we need to calculate the distance of a plane from that range of
  // planes to p1 and normalize it with the length of v(p1,p2)
  // the distance can be positive or negative, this makes a difference for
  // the gradient calculation

  // rel_distance is the distance with respect to the original gradient vector
  // that is, a value of 1.0 means that the point is exactly as far from the
  // plane as the gradient vector is long
  double deltax = x2 - x1;
  double deltay = y2 - y1;
  double deltaz = z2 - z1;
  double length = sqrt(deltax * deltax + deltay * deltay + deltaz * deltaz);

  // line through x1,y1 that is perpendicular to v(p1,p2)
  if (fabs(deltax) < ALMOST_ZERO)
    {
      // the gradient is along the y axis
      unsigned int i, j, iMax = size, jMax = size;
      double rel_distance = 0.0;
      unsigned int index = 0;

      for (i = 0; i < iMax; ++i)
        {
          for (j = 0; j < jMax; ++j)
            {
              rel_distance = (double)(i - y1) / length;
              stops.update_color(rel_distance);
              pData[index] = stops.color().mR;
              pData[++index] = stops.color().mG;
              pData[++index] = stops.color().mB;
              pData[++index] = stops.color().mA;
              ++index;
            }
        }
    }
  else if (fabs(deltay) < ALMOST_ZERO)
    {
      // the gradient is along the x axis
      unsigned int i, j, iMax = size, jMax = size;
      double rel_distance = 0.0;
      unsigned int index = 0;

      for (i = 0; i < iMax; ++i)
        {
          for (j = 0; j < jMax; ++j)
            {
              rel_distance = (double)(j - x1) / length;
              stops.update_color(rel_distance);
              pData[index] = stops.color().mR;
              pData[++index] = stops.color().mG;
              pData[++index] = stops.color().mB;
              pData[++index] = stops.color().mA;
              ++index;
            }
        }
    }
  else
    {
      double slope = deltay / deltax;
      double inv_slope = -deltax / deltay;
      double c_inv = y1 - inv_slope * x1;
      double c;
      // y=s*x+c;
      // intersection of line
      unsigned int i, j, iMax = size, jMax = size;
      double rel_distance = 0.0;
      double px, py;
      double r = inv_slope - slope;
      unsigned int index = 0;

      for (i = 0; i < iMax; ++i)
        {
          for (j = 0; j < jMax; ++j)
            {
              c = i - slope * j;
              // x*slope+c=x*inv_slope+inv_c
              // x*slope-x*inv_slope=inv_c-c
              // x= (inv_c-c)/(slope-inv_slope)
              px = (c - c_inv) / r;
              py = slope * px + c;
              rel_distance = sqrt((j - px) * (j - px) + (i - py) * (i - py)) / length;

              // check if the distance is actually negative
              if ((j - px)*deltax + (i - py)*deltay <= 0)
                {
                  rel_distance = -rel_distance;
                }

              stops.update_color(rel_distance);
              pData[index] = stops.color().mR;
              pData[++index] = stops.color().mG;
              pData[++index] = stops.color().mB;
              pData[++index] = stops.color().mA;
              ++index;
            }
        }
    }
}

/**
 * This method calculates a texture for a given radial gradient
 * definition and a given size.
 * The data object has to be a vector that can store RGBA values for a rectangle
 * of the given size. The memory has to be allocated before calling the method.
 * The scale specifies by how much the original box has been scaled.
 */
void CLLayoutRenderer::create_radial_gradient_texture(unsigned int size, GLubyte* pData, const CLRadialGradient* pGradient, double /*z_value*/)
{
  // experiments with the focal point in firefox
  // - the radius seems to be aplied to the x and the y axis, so if a radius
  // of 50% is used in a rectangle, the circle is not a circle, but an
  // ellipse

  // spreadMethod Pad:
  // if the focal point is on the circle, everything that
  // is outside the circle and on the outside of the tangent with the circle
  // and the focal point is the stop color at 0%, everythin outside the
  // circle on the inside of the tangent is black, the color in the ellipse
  // depends on the distance from the focal point and the circle edge
  // in Inkscape this is different, everything outside the circle is the
  // color of the 100% stop, everything else is patterned
  // if the focal point is within the circle/ellipse, the whole shape has a
  // pattern where everything outside the circle/ellipse has the color of the
  // 100% stop

  // spreadMethod reflect:
  // if the focal point is on the circle, everything has the color at 0% stop
  // in Inkscape this is different, everything outside the tangent is the
  // color of the 100% stop, everything else is patterned
  // if the focal point is within the circle/ellipse, the whole shape has a
  // pattern

  // spreadMethod repeat:
  // if the focal point is on the circle, everything has the color at 0% stop
  // in Inkscape this is different, everything outside the tangent is the
  // color of the 100% stop, everything else is patterned
  // if the focal point is within the circle/ellipse, the whole shape has a
  // pattern

  CLGradientStops stops(pGradient, this->mColorMap);
  double cx = pGradient->getCenterX().getAbsoluteValue() * this->mZoomFactor + pGradient->getCenterX().getRelativeValue() / 100.0 * size;
  double cy = pGradient->getCenterY().getAbsoluteValue() * this->mZoomFactor + pGradient->getCenterY().getRelativeValue() / 100.0 * size;
  double fx = pGradient->getFocalPointX().getAbsoluteValue() * this->mZoomFactor + pGradient->getFocalPointX().getRelativeValue() / 100.0 * size;
  double fy = pGradient->getFocalPointY().getAbsoluteValue() * this->mZoomFactor + pGradient->getFocalPointY().getRelativeValue() / 100.0 * size;
  double rx = pGradient->getRadius().getAbsoluteValue() * this->mZoomFactor + pGradient->getRadius().getRelativeValue() / 100.0 * size;
  double ry = pGradient->getRadius().getAbsoluteValue() * this->mZoomFactor + pGradient->getRadius().getRelativeValue() / 100.0 * size;
  // TODO create an error if the radius is negative

  // TODO correct the focal point if it is outside the circle

  double delta_x, delta_y, slope, A, B, C, a;
  unsigned int i, j;
  // ellipse (x-cx)^2 / rx^2 + (y-cy)^2 / ry^2 = 1
  // -> x=+- sqrt(1-((x-cx)/rx)^2)*ry+cx
  // -> y=+- sqrt(1-((y-cy)/ry)^2)*rx+cy
  // for horizontal and vertical lines through the focal point fx,fy
  // we can already precalculate the value under the square root
  // which determines the number of solutions
  // for vertical lines (x=fx) it is
  const double s = 1 - pow((fx - cx) / rx, 2);
  // for horizontal lines (y=fy) it is
  const double t = 1 - pow((fy - cy) / ry, 2);
  double u = 0.0, solution1x = 0.0, solution1y = 0.0, solution2x = 0.0, solution2y = 0.0;
  unsigned int index = 0;

  for (i = 0; i < size; ++i)
    {
      for (j = 0; j < size; ++j)
        {
          delta_x = j - fx;
          delta_y = i - fy;
          double rel_distance = 1.0;

          if (fabs(delta_x) < ALMOST_ZERO && fabs(delta_y) < ALMOST_ZERO)
            {
              // we are on the focal point, so the rel_distance is 0.0
              rel_distance = 0.0;
            }
          else if (fabs(delta_x) < ALMOST_ZERO)
            {
              // use s
              if (s > 0.0)
                {
                  // there are two crossing points
                  solution1x = fx;
                  // -> y=+- sqrt(s)*ry+cy
                  solution1y = sqrt(s) * ry + cy;
                  solution2x = fx;
                  solution2y = -sqrt(s) * ry + cy;
                  // we have to find out which one is the correct one
                  // the correct one is not necessarily the one that is
                  // closer, but the one that lies on the same side of the
                  // focal point f(fx,fy) as the point we are looking at P(j,i)
                  // so if the dot product is positive, we have the correct
                  // value
                  double dotProduct = ((double)j - fx) * (solution1x - fx) + ((double)i - fy) * (solution1y - fy);

                  if (dotProduct <= 0)
                    {
                      assert(((double)j - fx)*(solution2x - fx) + ((double)i - fy)*(solution2y - fy) > 0);
                      solution1x = solution2x;
                      solution1y = solution2y;
                    }
                }
              else if (fabs(s) < ALMOST_ZERO)
                {
                  // there is only a tangent, so the focal points is directly
                  // on the circle
                  solution1x = fx;
                  // -> y=+- sqrt(s)*rx+cy
                  solution1y = cy;
                }
              else
                {
                  // there is no crossing between the line and the circle,
                  // since the focal points is always within the circle, this
                  // should be impossible
                  throw 0;
                }
            }
          else if (fabs(delta_y) < ALMOST_ZERO)
            {
              // use t
              if (t > 0.0)
                {
                  // there are two crossing points
                  solution1y = fy;
                  // -> x=+- sqrt(t)*rx+cx
                  solution1x = sqrt(t) * rx + cx;
                  solution2y = fy;
                  solution2x = -sqrt(t) * rx + cx;
                  // we have to find out which one is the correct one
                  // the correct one is not necessarily the one that is
                  // closer, but the one that lies on the same side of the
                  // focal point f(fx,fy) as the point we are looking at P(j,i)
                  // so if the dot product is positive, we have the correct
                  // value
                  double dotProduct = ((double)j - fx) * (solution1x - fx) + ((double)i - fy) * (solution1y - fy);

                  if (dotProduct < 0)
                    {
                      assert(((double)j - fx)*(solution2x - fx) + ((double)i - fy)*(solution2y - fy) > 0);
                      solution1x = solution2x;
                      solution1y = solution2y;
                    }
                }
              else if (fabs(t) < ALMOST_ZERO)
                {
                  // there is only a tangent, so the focal points is directly
                  // on the circle
                  solution1y = fy;
                  // -> x=+- sqrt(t)*ry+cx
                  solution1x = cx;
                }
              else
                {
                  // there is no crossing between the line and the circle,
                  // since the focal points is always within the circle, this
                  // should be impossible
                  throw 0;
                }
            }
          else
            {
              slope = delta_y / delta_x;
              // for the general case, we have to calculate the value under
              // the square root for every single point
              // a=fy-slope*fx;
              // u=B^2-4*A*C
              // u=(-2*cx*(ry)^2+2*rx^2*slope*(a-cy))^2-4*(ry^2+rx^2*slope^2)*(ry^2*cx^2+rx^2*(a-cy)^2-rx^2*ry^2)
              // u=(-2*cx*(ry)^2+2*rx^2*slope*(fy-slope*fx-cy))^2-4*(ry^2+rx^2*slope^2)*(ry^2*cx^2+rx^2*(fy-slope*fx-cy)^2-rx^2*ry^2)
              a = fy - slope * fx;
              A = ry * ry + rx * rx * slope * slope;
              B = -2 * cx * ry * ry + 2 * rx * rx * slope * (a - cy);
              C = ry * ry * cx * cx + rx * rx * pow(a - cy, 2) - rx * rx * ry * ry;
              u = B * B - 4 * A * C;

              if (u > 0.0)
                {
                  // two solutions
                  solution1x = (-B + sqrt(u)) / (2 * A);
                  solution2x = (-B - sqrt(u)) / (2 * A);
                  solution1y = solution1x * slope + a;
                  solution2y = solution2x * slope + a;
                  // we have to find out which one is the correct one
                  // the correct one is not necessarily the one that is
                  // closer, but the one that lies on the same side of the
                  // focal point f(fx,fy) as the point we are looking at P(j,i)
                  // so if the dot product is positive, we have the correct
                  // value
                  double dotProduct = ((double)j - fx) * (solution1x - fx) + ((double)i - fy) * (solution1y - fy);

                  if (dotProduct < 0)
                    {
                      assert(((double)j - fx)*(solution2x - fx) + ((double)i - fy)*(solution2y - fy) > 0);
                      solution1x = solution2x;
                      solution1y = solution2y;
                    }
                }
              else if (fabs(u) < ALMOST_ZERO)
                {
                  // one solution, the focal point is on the circle
                  solution1x = (-2 * slope * (fy - slope * fx) + cy) / (2 * (ry * ry + rx * rx * slope * slope));
                  solution1y = solution1x * slope + (fy - slope * fx);
                }
              else
                {
                  // no solution. Since the focal point is always in or on
                  // the circle, this should be impossible
                  throw 0;
                }
            }

          // now we have the correct crosing point in solution1x and
          // solution1y
          // we have to find out if the solution coincides with the focal
          // point
          // TODO, actually this could simplify the code above. If we get
          // only one solution, we actually know that it must be the focal
          // point
          if (fabs(solution1x - fx) >= ALMOST_ZERO || fabs(solution1y - fx) >= ALMOST_ZERO)
            {
              // we calculate the distance from the focal point to the
              // current point
              // and we calculate the distance from the focal point to the
              // crossing point
              // TODO we can save one square root calculation if we only
              // calculate the square root of the rel_distance
              double distance_f_c = sqrt(pow((solution1x - fx), 2) + pow((solution1y - fy), 2));
              double distance_f_p = sqrt(pow((j - fx), 2) + pow((i - fy), 2));
              rel_distance = distance_f_p / distance_f_c;
            }

          stops.update_color(rel_distance);
          pData[index] = stops.color().mR;
          pData[++index] = stops.color().mG;
          pData[++index] = stops.color().mB;
          pData[++index] = stops.color().mA;
          ++index;
        }
    }
}

/**
 * Maps the relative distance to a color and set the color as an rgb value in
 * pData. pData has to be the pointer where 4 GLfloat values are going to be
 * stored.
 */
void CLLayoutRenderer::map_gradient_color(double rel_distance, const CLGradientBase* pGradient, GLubyte* pData)
{
  if (rel_distance < 0.0)
    {
      switch (pGradient->getSpreadMethod())
        {
          case CLGradientBase::PAD:
            rel_distance = 0.0;
            break;
          case CLGradientBase::REFLECT:
            // if the part of the distance before the decimal point
            // is devisible by 2, we just remove it
            // otherwise, we remove it and subtract the result from
            // 1.0
            rel_distance = fabs(rel_distance);

            if (((unsigned int)floor(rel_distance)) % 2 != 0)
              {
                rel_distance = 1.0 - (rel_distance - floor(rel_distance));
              }
            else
              {
                rel_distance = rel_distance - floor(rel_distance);
              }

            break;
          case CLGradientBase::REPEAT:
            // we only need everything after the decimal point
            // and we need to subtract from 1.0
            rel_distance = rel_distance - floor(rel_distance);
            break;
        }
    }

  if (rel_distance > 1.0)
    {
      switch (pGradient->getSpreadMethod())
        {
          case CLGradientBase::PAD:
            rel_distance = 1.0;
            break;
          case CLGradientBase::REFLECT:

            // if the part of the distance before the decimal point
            // is devisible by 2, we just remove it
            // otherwise, we remove it and subtract the result from
            // 1.0
            if (((unsigned int)floor(rel_distance)) % 2 != 0)
              {
                rel_distance = 1.0 - (rel_distance - floor(rel_distance));
              }
            else
              {
                rel_distance = rel_distance - floor(rel_distance);
              }

            break;
          case CLGradientBase::REPEAT:
            // we only need everything after the decimal point
            rel_distance = rel_distance - floor(rel_distance);
            break;
        }
    }

  // we need to find the stop that has an offset lower than the
  // rel_distance and we need to find the stop that has an offset
  // larget than rel_distance
  assert(pGradient->getNumGradientStops() >= 2);
  const CLGradientStop *lower = NULL, *higher = NULL, *current = NULL;
  size_t k, kMax = pGradient->getNumGradientStops();

  for (k = 0; k < kMax; ++k)
    {
      current = pGradient->getGradientStop(k);

      if (current->getOffset().getRelativeValue() / 100.0 <= rel_distance)
        {
          lower = current;
        }

      if (!higher && current->getOffset().getRelativeValue() / 100.0 >= rel_distance)
        {
          higher = current;
          break;
        }
    }

  // check if we have a stop lower and one higher
  GLubyte* pColorData1 = new GLubyte[4];
  std::map<std::string, CLRGBAColor>::const_iterator pos;

  if (lower && higher)
    {
      if (lower == higher)
        {
          pos = this->mColorMap.find(lower->getStopColor());
          assert(pos != this->mColorMap.end());
          pColorData1[0] = pos->second.mR;
          pColorData1[1] = pos->second.mG;
          pColorData1[2] = pos->second.mB;
          pColorData1[3] = pos->second.mA;
        }
      else
        {
          GLfloat* pColorData2 = new GLfloat[4];
          pos = this->mColorMap.find(lower->getStopColor());
          assert(pos != this->mColorMap.end());
          pColorData1[0] = pos->second.mR;
          pColorData1[1] = pos->second.mG;
          pColorData1[2] = pos->second.mB;
          pColorData1[3] = pos->second.mA;
          pos = this->mColorMap.find(higher->getStopColor());
          assert(pos != this->mColorMap.end());
          pColorData2[0] = pos->second.mR;
          pColorData2[1] = pos->second.mG;
          pColorData2[2] = pos->second.mB;
          pColorData2[3] = pos->second.mA;
          // calculate the correct value
          GLfloat ratio = (GLfloat)((rel_distance - lower->getOffset().getRelativeValue() / 100.0) / ((higher->getOffset().getRelativeValue() - lower->getOffset().getRelativeValue()) / 100.0));
          pColorData1[0] = (GLubyte)(pColorData1[0] + ratio * (GLfloat)(pColorData2[0] - pColorData1[0]));
          pColorData1[1] = (GLubyte)(pColorData1[1] + ratio * (GLfloat)(pColorData2[1] - pColorData1[1]));
          pColorData1[2] = (GLubyte)(pColorData1[2] + ratio * (GLfloat)(pColorData2[2] - pColorData1[2]));
          pColorData1[3] = (GLubyte)(pColorData1[3] + ratio * (GLfloat)(pColorData2[3] - pColorData1[3]));
          delete[] pColorData2;
        }
    }
  else if (lower)
    {
      pos = this->mColorMap.find(lower->getStopColor());
      assert(pos != this->mColorMap.end());
      pColorData1[0] = pos->second.mR;
      pColorData1[1] = pos->second.mG;
      pColorData1[2] = pos->second.mB;
      pColorData1[3] = pos->second.mA;
    }
  else if (higher)
    {
      pos = this->mColorMap.find(higher->getStopColor());
      assert(pos != this->mColorMap.end());
      pColorData1[0] = pos->second.mR;
      pColorData1[1] = pos->second.mG;
      pColorData1[2] = pos->second.mB;
      pColorData1[3] = pos->second.mA;
    }

  pData[0] = pColorData1[0];
  pData[1] = pColorData1[1];
  pData[2] = pColorData1[2];
  pData[3] = pColorData1[3];
  delete[] pColorData1;
}

/**
 * Method to draw a render polygon from a set of datapoints
 */
void CLLayoutRenderer::draw_datapoints(GLdouble* pData, size_t numPoints, const CLBoundingBox* pBB, bool doTesselation, float xOffset, float yOffset, float zOffset)
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(xOffset, yOffset, zOffset);

  // apply the current transformation
  if (memcmp(mCurrentAttributes.mpTransform, Transformation::getIdentityMatrix(), 12*sizeof(double)))
    {
      // move back to the current offset
      glTranslated(this->mCurrentAttributes.mX, this->mCurrentAttributes.mY, this->mCurrentAttributes.mZ);
      GLdouble* matrix = new GLdouble[16];
      CLLayoutRenderer::createGLMatrix(mCurrentAttributes.mpTransform, matrix);
      glMultMatrixd(matrix);
      delete[] matrix;
      // move to 0.0,0.0,0.0
      glTranslated(-this->mCurrentAttributes.mX, -this->mCurrentAttributes.mY, -this->mCurrentAttributes.mZ);
    }

  // draw the rectangle
  // first we draw the filled part
  if (this->mCurrentAttributes.mFillRule != CLGraphicalPrimitive2D::UNSET && this->mCurrentAttributes.mFill != "none")
    {

      // tesselate the polygon to make sure that it is drawn correctly by
      // OpenGL
      GLUtesselator* pTess = NULL;

      if (doTesselation)
        {
          pTess = gluNewTess();
        }

      bool singleColor = true;
      // set the stepsize for the datapoints to 3
      // which means that the data array only contains vertex information
      // if we have a gradient, we have to set it to 5 later on
      // because the data now contains texture coordinates as well
      unsigned int stepsize = 3;
      GLdouble* pOrigData = pData;
      GLdouble* pNewData = NULL;
      std::map<std::string, CLRGBAColor>::const_iterator pos = this->mColorMap.find(mCurrentAttributes.mFill);

      if (pos != this->mColorMap.end())
        {
          const CLRGBAColor& c = pos->second;
          glColor4ub(c.mR, c.mG, c.mB, c.mA);
        }
      else
        {
          singleColor = false;
          // enable tesselation if a gradient is specified
          pTess = gluNewTess();
          // it could be a gradient
          std::map<std::string, std::pair<const CLGradientBase*, CLTextureSpec*> >::const_iterator pos = this->mGradientMap.find(mCurrentAttributes.mFill);
          assert(pos != this->mGradientMap.end());
          const CLTextureSpec* pTexSpec = pos->second.second;
          assert(pTexSpec != NULL);
          unsigned int i;
#ifdef _WIN32
          gluTessCallback(pTess, GLU_TESS_BEGIN, (GLvoid(__stdcall *)())glBegin);
          gluTessCallback(pTess, GLU_TESS_END, glEnd);
          gluTessCallback(pTess, GLU_TESS_VERTEX, (GLvoid(__stdcall *)())CLLayoutRenderer::VERTEX_CALLBACK_GRADIENT);
          gluTessCallback(pTess, GLU_TESS_COMBINE, (GLvoid(__stdcall *)())CLLayoutRenderer::COMBINE_CALLBACK_GRADIENT);
#else
          gluTessCallback(pTess, GLU_TESS_BEGIN, (GLvoid(*)())glBegin);
          gluTessCallback(pTess, GLU_TESS_END, glEnd);
          gluTessCallback(pTess, GLU_TESS_VERTEX, (GLvoid(*)())CLLayoutRenderer::VERTEX_CALLBACK_GRADIENT);
          gluTessCallback(pTess, GLU_TESS_COMBINE, (GLvoid(*)())CLLayoutRenderer::COMBINE_CALLBACK_GRADIENT);
#endif // _WIN32
          stepsize = 5;
          pNewData = new GLdouble[5*numPoints];
          // assign the texture coordinates
          double width = pBB->getDimensions().getWidth();
          double height = pBB->getDimensions().getHeight();

          for (i = 0; i < numPoints; ++i)
            {
              pNewData[5*i] = pData[3*i];
              pNewData[5*i+1] = pData[3*i+1];
              pNewData[5*i+2] = pData[3*i+2];
              pNewData[5*i+3] = (pData[3*i] + xOffset - pBB->getPosition().getX()) / width;
              pNewData[5*i+4] = (pData[3*i+1] + yOffset - pBB->getPosition().getY()) / height;
            }

          pData = pNewData;

          // load the texture
          if (pTexSpec->mTextureName != 0)
            {
              glBindTexture(GL_TEXTURE_2D, pTexSpec->mTextureName);
              // enable 2D texturing
              glEnable(GL_TEXTURE_2D);
            }

          /*
          else
          {
              std::cerr << "Texture not bound." << std::endl;
          }
          */
        }

      if (pTess && singleColor)
        {
          // we don't need to do anythong special during the tesselation since
          // the whole object only has one color
#ifdef _WIN32
          gluTessCallback(pTess, GLU_TESS_BEGIN, (GLvoid(__stdcall *)())glBegin);
          gluTessCallback(pTess, GLU_TESS_END, (GLvoid(__stdcall *)())glEnd);
          gluTessCallback(pTess, GLU_TESS_VERTEX, (GLvoid(__stdcall *)())glVertex3dv);
          gluTessCallback(pTess, GLU_TESS_COMBINE, (GLvoid(__stdcall *)())CLLayoutRenderer::COMBINE_CALLBACK);
#else
          gluTessCallback(pTess, GLU_TESS_BEGIN, (GLvoid(*)())glBegin);
          gluTessCallback(pTess, GLU_TESS_END, (GLvoid(*)())glEnd);
          gluTessCallback(pTess, GLU_TESS_VERTEX, (GLvoid(*)())glVertex3dv);
          gluTessCallback(pTess, GLU_TESS_COMBINE, (GLvoid(*)())CLLayoutRenderer::COMBINE_CALLBACK);
#endif // _WIN32
        }

      if (pTess)
        {
          // specify the fill rule to the tesselator EVENODD, NONZERO
          switch (this->mCurrentAttributes.mFillRule)
            {
              case CLGraphicalPrimitive2D::UNSET:
                // this should not happen
                std::cerr << "No fill rule specified." << std::endl;
                exit(1);
                break;
              case CLGraphicalPrimitive2D::NONZERO:
                gluTessProperty(pTess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_NONZERO);
                break;
              case CLGraphicalPrimitive2D::EVENODD:
                gluTessProperty(pTess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ODD);
                break;
              case CLGraphicalPrimitive2D::INHERIT:
                // this should not happen
                // inherit has to be replaced by something meaningfull
                std::cerr << "fill rule \"INHERIT\" specified." << std::endl;
                exit(1);
                break;
            }

#ifdef _WIN32
          gluTessCallback(pTess, GLU_TESS_ERROR, (GLvoid(__stdcall *)())CLLayoutRenderer::TESS_ERROR);
#else
          gluTessCallback(pTess, GLU_TESS_ERROR, (GLvoid(*)())CLLayoutRenderer::TESS_ERROR);
#endif // _WIN32
          gluTessBeginPolygon(pTess, NULL);
          gluTessBeginContour(pTess);
          // specify the actual vertex data
          size_t j = 0, jMax = numPoints - 1;

          while (j < jMax)
            {
              gluTessVertex(pTess, &pData[j*stepsize], &pData[j*stepsize]);
              ++j;
            }

          gluTessEndContour(pTess);
          gluTessEndPolygon(pTess);
          gluDeleteTess(pTess);
          pData = pOrigData;

          if (pNewData)
            {
              delete[] pNewData;
            }
        }
      else
        {
          // it must be a single colored object, so we just draw the vertex array
          glEnableClientState(GL_VERTEX_ARRAY);
          glVertexPointer(3, GL_DOUBLE, 0, pData);
          glDrawArrays(GL_POLYGON, 0, (GLsizei)(numPoints - 1));
          glDisableClientState(GL_VERTEX_ARRAY);
        }

      if (!singleColor)
        {
          // disable texturing again
          glDisable(GL_TEXTURE_2D);
        }
    }

  //
  // next we draw the edge
  //
  if (this->mCurrentAttributes.mStrokeWidth > 0.0 && this->mCurrentAttributes.mStroke != "none")
    {
      std::map<std::string, CLRGBAColor>::const_iterator pos = this->mColorMap.find(mCurrentAttributes.mStroke);
      assert(pos != this->mColorMap.end());
      const CLRGBAColor& c = pos->second;
      glColor4ub(c.mR, c.mG, c.mB, c.mA);
      this->draw_line(numPoints, pData);
      // draw the final cap
      size_t index = (numPoints - 2) * 3;
      draw_cap(pData[index], pData[index+1], pData[index+2], pData[0], pData[1], pData[2], pData[3], pData[4], pData[5], mCurrentAttributes.mStrokeWidth);
    }

  glPopMatrix();
}

/**
 * Maps the given arrow head to the given line segment.
 */
void CLLayoutRenderer::map_arrow_head(const CLPoint& mapTo, const CLPoint& direction, const std::string& headId)
{
  // the line ending that is to be drawn is identified by headId
  // the origin of the line ending has to be mapped to mapTo
  // the line ending might have to be rotated to fit the vector called
  // direction
  //
  // first we get the line ending
  if (headId != "" && headId != "none")
    {
      const CLLineEnding* pLineEnding = this->mpResolver->getLineEnding(headId);
      assert(pLineEnding);
      // TODO create an error if the line ending was not found
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();
      glTranslated(mapTo.getX(), mapTo.getY(), mapTo.getZ());

      // now we need to figure out the rotation
      if (pLineEnding->getIsEnabledRotationalMapping())
        {
          //std::cout << "direction: " << "(" << direction.getX() << "," << direction.getY() << "," << direction.getZ() << ")" << std::endl;
          double length = sqrt(direction.getX() * direction.getX() + direction.getY() * direction.getY() + direction.getZ() * direction.getZ());
          //std::cout << "length: " << length << std::endl;
          CLPoint normDirection(direction.getX() / length, direction.getY() / length, direction.getZ() / length);
          //std::cout << "norm direction: " << "(" << normDirection.getX() << "," << normDirection.getY() << "," << normDirection.getZ() << ")" << std::endl;
          double x_2 = 0.0;
          double y_2 = 0.0;
          double z_2 = 0.0;

          if (fabs(direction.getX()) < ALMOST_ZERO && direction.getZ() < ALMOST_ZERO)
            {
              x_2 = -normDirection.getY();
              y_2 = 0.0;
              z_2 = 0.0;
            }
          else
            {
              x_2 = -normDirection.getY() * normDirection.getX();
              y_2 = 1 - normDirection.getY() * normDirection.getY();
              z_2 = -normDirection.getY() * normDirection.getZ();
            }

          length = sqrt(x_2 * x_2 + y_2 * y_2 + z_2 * z_2);
          x_2 /= length;
          y_2 /= length;
          z_2 /= length;
          //std::cout << "second vector: " << "(" << x_2 << "," << y_2 << "," << z_2 << ")" << std::endl;
          //std::cout << std::endl;
          //std::cout << std::endl;
          GLdouble matrix[16] = {normDirection.getX(), normDirection.getY(), normDirection.getZ(), 0.0, x_2, y_2, z_2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0};
          glMultMatrixd(matrix);
        }

      this->save_current_attributes();
      // transformations in line endings are relative to the line endings
      // viewport
      mCurrentAttributes.mX = 0.0;
      mCurrentAttributes.mY = 0.0;
      mCurrentAttributes.mZ = 0.0;
      mCurrentAttributes.mWidth = pLineEnding->getBoundingBox()->getDimensions().getWidth();
      mCurrentAttributes.mHeight = pLineEnding->getBoundingBox()->getDimensions().getHeight();
      // clear the current arrow head information to avoid an endless loop
      mCurrentAttributes.mStartHead = "none";
      mCurrentAttributes.mEndHead = "none";
      // clear the transformation information since it does not belong to the
      // information that is inherited.
      memcpy(mCurrentAttributes.mpTransform, Transformation::getIdentityMatrix(), 12*sizeof(double));
      // draw the line ending
      this->draw_group(pLineEnding->getGroup(), pLineEnding->getBoundingBox());
      // restore the matrix
      this->restore_current_attributes();
      glPopMatrix();
    }
}

void CLLayoutRenderer::TESS_ERROR(GLenum error)
{
  const char *szError = (const char*)gluErrorString(error);
  std::cerr << "tesselation error: " << szError << std::endl;
  exit(1);
}

void CLLayoutRenderer::COMBINE_CALLBACK(GLdouble coords[3], GLdouble** /*vertex_data[4]*/, GLfloat* /*weight[4]*/, GLdouble** dataOut)
{
  GLdouble* vertex;
  //int i;
  vertex = new GLdouble[3];
  vertex[0] = coords[0];
  vertex[1] = coords[1];
  vertex[2] = coords[2];
  *dataOut = vertex;
}

void CLLayoutRenderer::COMBINE_CALLBACK_GRADIENT(GLdouble coords[3], GLdouble* vertex_data[4], GLfloat weight[4], GLdouble** dataOut)
{
  GLdouble* vertex;
  vertex = new GLdouble[5];
  vertex[0] = coords[0];
  vertex[1] = coords[1];
  vertex[2] = coords[2];
  vertex[3] = weight[0] * vertex_data[0][3]
              + weight[1] * vertex_data[1][3]
              + weight[2] * vertex_data[2][3]
              + weight[3] * vertex_data[3][3];
  vertex[4] = weight[0] * vertex_data[0][4]
              + weight[1] * vertex_data[1][4]
              + weight[2] * vertex_data[2][4]
              + weight[3] * vertex_data[3][4];
  *dataOut = vertex;
}

void CLLayoutRenderer::VERTEX_CALLBACK_GRADIENT(GLvoid* vertex)
{
  const GLdouble* pointer = (GLdouble*)vertex;
  // the last two are the texture coordinates
  glTexCoord2dv(pointer + 3);
  // the first three double values are the vertex coordiantes
  glVertex3dv(pointer);
}

void CLLayoutRenderer::setZoomFactor(double zoomFactor)
{
  this->mZoomFactor = zoomFactor;
}

double CLLayoutRenderer::getZoomFactor() const
{
  return this->mZoomFactor;
}

/**
 * Calculates the points for a cubic bezier curve.
 * The algorithm calculates numPoints and stores them in pData. pData
 * has to be an array with enough space for numPoints*3 GLfloat items.
 */
void CLLayoutRenderer::calculate_cubicbezier(double sx, double sy, double sz, double p1x, double p1y, double p1z, double p2x, double p2y, double p2z, double ex, double ey, double ez, unsigned int numPoints, GLdouble* pData)
{
  unsigned int index = 0;
  pData[index++] = sx;
  pData[index++] = sy;
  pData[index++] = sz;
  unsigned int i, iMax = numPoints - 1;
  double stepSize = 1.0 / (float)(iMax);
  double t = 0.0;
  double t_square = 0.0;
  double t_cube = 0.0;
  double oneMinusT = 0.0;
  double oneMinusT_square = 0.0;
  double oneMinusT_cube = 0.0;
  double a, b;

  for (i = 1; i < iMax; ++i)
    {
      t = i * stepSize;
      oneMinusT = 1.0 - t;
      oneMinusT_square = oneMinusT * oneMinusT;
      oneMinusT_cube = oneMinusT * oneMinusT_square;
      t_square = t * t;;
      t_cube = t_square * t;
      a = 3 * t * oneMinusT_square;
      b = 3 * t_square * oneMinusT;
      pData[index++] = sx * oneMinusT_cube + p1x * a + p2x * b + ex * t_cube;
      pData[index++] = sy * oneMinusT_cube + p1y * a + p2y * b + ey * t_cube;
      pData[index++] = sz * oneMinusT_cube + p1z * a + p2z * b + ez * t_cube;
    }

  pData[index++] = ex;
  pData[index++] = ey;
  pData[index++] = ez;
}

/**
 * Method to draw a line made up of a set of points.
 */
void CLLayoutRenderer::draw_line(size_t numPoints, GLdouble* pData)
{
  // a line has to have more than one point
  if (numPoints > 1)
    {
      // create the texture for line stippling
      const CLLineStippleTexture* pTexture = NULL;
      std::map<const std::vector<unsigned int>, const CLLineStippleTexture*>::const_iterator pos = this->mLinestippleMap.find(this->mCurrentAttributes.mStrokeDasharray);

      if (pos != this->mLinestippleMap.end())
        {
          pTexture = pos->second;
        }

      GLfloat* pTextureCoordinates = NULL;
      GLdouble* pOrigData = pData;
      size_t iMax = numPoints;

      if (pTexture != NULL)
        {
          // segment the
          // datapoints into pieces that fit the texture pattern
          // and create the texture coordinates
          std::vector<simple_point> v;
          // we need at least numPoints elements in the vector
          v.reserve(numPoints);
          this->segment_data(pTexture->mPatternLength, (double)pTexture->mPatternLength / (double)pTexture->mTextureLength, numPoints, pData, v);

          if (v.size() != numPoints)
            {
              iMax = (unsigned int)v.size();
              // we have to create a new dataset
              pData = new GLdouble[3*iMax];
              pTextureCoordinates = new GLfloat[iMax];
              std::vector<simple_point>::const_iterator it = v.begin(), endit = v.end();
              unsigned int index = 0;
              unsigned int index2 = 0;

              while (it != endit)
                {
                  pData[index++] = it->mX;
                  pData[index++] = it->mY;
                  pData[index++] = it->mZ;
                  pTextureCoordinates[index2++] = (GLfloat)it->mS;
                  ++it;
                }
            }
          else
            {
              // create an array for the texture coordinates
              pTextureCoordinates = new GLfloat[iMax];
              std::vector<simple_point>::const_iterator it = v.begin(), endit = v.end();
              unsigned int index = 0;

              while (it != endit)
                {
                  pTextureCoordinates[index++] = (GLfloat)it->mS;
                  ++it;
                }
            }

          if (pTexture->mTextureName != 0)
            {
              glBindTexture(GL_TEXTURE_1D, pTexture->mTextureName);
              // enable 1D texturing
              glEnable(GL_TEXTURE_1D);
            }
        }

      unsigned int i;
      // the loop does not go to the very last point, but stops one before that
      --iMax;
      unsigned int index = 0;

      for (i = 0; i < iMax; ++i)
        {
          if (pTextureCoordinates)
            {
              draw_line_segment(pData[index], pData[index+1], pData[index+2], pData[index+3], pData[index+4], pData[index+5], mCurrentAttributes.mStrokeWidth, true, 0.0, pTextureCoordinates[i+1]);
            }
          else
            {
              draw_line_segment(pData[index], pData[index+1], pData[index+2], pData[index+3], pData[index+4], pData[index+5], mCurrentAttributes.mStrokeWidth);
            }

          index += 3;

          // don't draw a cap after the last segment
          if (i != iMax - 1)
            {
              draw_cap(pData[index-3], pData[index-2], pData[index-1], pData[index], pData[index+1], pData[index+2], pData[index+3], pData[index+4], pData[index+5], mCurrentAttributes.mStrokeWidth);
            }
        }

      // if we created new datapoints, we have to delete them again
      if (pOrigData != pData)
        {
          delete[] pData;
          pData = pOrigData;
        }

      // delete any texture coordinates we have created
      if (pTextureCoordinates != NULL)
        {
          delete[] pTextureCoordinates;
          glDisable(GL_TEXTURE_1D);
        }
    }
}

void CLLayoutRenderer::createGLMatrix(const double* const matrix, GLdouble* glMatrix)
{
  glMatrix[0] = matrix[0];
  glMatrix[1] = matrix[1];
  glMatrix[2] = matrix[2];
  glMatrix[3] = 0.0;
  glMatrix[4] = matrix[3];
  glMatrix[5] = matrix[4];
  glMatrix[6] = matrix[5];
  glMatrix[7] = 0.0;
  glMatrix[8] = matrix[6];
  glMatrix[9] = matrix[7];
  glMatrix[10] = matrix[8];
  glMatrix[11] = 0.0;
  glMatrix[12] = matrix[9];
  glMatrix[13] = matrix[10];
  glMatrix[14] = matrix[11];
  glMatrix[15] = 1.0;
}

/**
 * Creates a 1D texture for the line stippling.
 * The caller is responsible for deleting the returned object.
 * If the dasharray does not contain a valid stipple pattern NULL is
 * returned.
 */
CLLineStippleTexture* CLLayoutRenderer::createLineStippleTexture(const std::vector<unsigned int>& dasharray)
{
  return new CLLineStippleTexture(dasharray);
}

void CLLayoutRenderer::segment_data(double length, double ratio, size_t numPoints, GLdouble* pData, std::vector<simple_point>& v)
{
  double current_distance = 0.0;
  size_t i, iMax = numPoints;
  simple_point start = {pData[0], pData[1], pData[2], 0.0};
  // add the first point
  v.push_back(start);
  double vx, vy, vz, l;
  double current_repeat, end_repeat;
  size_t current_repeat_i, end_repeat_i;
  simple_point p;
  simple_point end;
  size_t index = 3;

  for (i = 1; i < iMax; ++i)
    {
      end.mX = pData[index++];
      end.mY = pData[index++];
      end.mZ = pData[index++];
      vx = end.mX - start.mX;
      vy = end.mY - start.mY;
      vz = end.mZ - start.mZ;
      l = sqrt(vx * vx + vy * vy + vz * vz);
      current_repeat = current_distance / length;
      current_repeat_i = (unsigned int)floor(current_repeat);
      end_repeat = (current_distance + l) / length;
      end_repeat_i = (unsigned int)floor(end_repeat);

      if (current_repeat_i == end_repeat_i)
        {
          // we don't need an additonal data point,
        }
      else
        {
          // normalize v to the langth of the pattern
          double factor = length / l;
          vx *= factor;
          vy *= factor;
          vz *= factor;
          // we need additional data points
          current_repeat = (double)current_repeat_i;
          current_repeat += 1.0;
          unsigned int step = 1;

          while (current_repeat < end_repeat)
            {
              // new datapoint at start+step*v with texture coordinate
              // current_repeat
              p.mX = step * vx + start.mX;
              p.mY = step * vy + start.mY;
              p.mZ = step * vz + start.mZ;
              p.mS = ratio;
              current_repeat += 1.0;
              v.push_back(p);
              step += 1;
            }
        }

      // we add the end point to the list
      // and set the texture coordinate for it
      end.mS = (end_repeat - floor(end_repeat));

      if (fabs(end.mS) < ALMOST_ZERO)
        {
          end.mS = ratio;
        }
      else
        {
          end.mS *= ratio;
        }

      v.push_back(end);
      start = end;
      current_distance += length;
    }
}

/**
 * Sets a function that is able to generate a texture spec from
 * some given font settings and a piece of text.
 */
void CLLayoutRenderer::set_font_renderer(CLFontRendererBase* pFontRenderer)
{
  this->mpFontRenderer = pFontRenderer;
}

/**
 * Analyses the render information and creates some of the textures.
 * First it determines which object are drawn based on the viewport
 * coordinates that are passed in.
 * Next it resolves the styles for all the objects that are to be drawn
 * and it determines the size of the textures.
 * Last it creates all textures.
 */
void CLLayoutRenderer::analyse_render_information(double lx, double ly, double rx, double ry)
{
  // go through the complete render information and resolve all colors
  // go through the list of gradients and create CLText*ureSpec objects for each
  // one and put it in a map
  // go through the complete layout and find the largest usage of any
  // gradient
  // Create the gradients
  // go through the layout and find all line stipple patterns and create the
  // textures placeholders for them

  // store the styles that have already been processed so that we process
  // each style only once
  if (rx - lx > ALMOST_ZERO && ry - ly > ALMOST_ZERO)
    {
      this->update_drawables(lx, ly, rx, ry);
      this->update_style_information();
      this->update_textures_and_colors();
    }
}

/**
 * This method goes through all layout objects and checks them if they
 * are within the current viewport. If they are, they are added to the list of objects that are drawn.
 * An object is within the viewport if it's bounding box or parts of it
 * are within the viewport.
 * For curves, each start, end and base point is checked and if any
 * of those is within the viewport, the curve is added to the list.
 * The viewport is specified by its lower left (lx,ly) and upper right
 * point (rx,ry).
 */
void CLLayoutRenderer::update_drawables(double lx, double ly, double rx, double ry)
{
  this->mDrawables.clear();
  std::vector<CLGraphicalObject*> v = this->getObjectsInBoundingBox(lx, ly, rx, ry);
  std::vector<CLGraphicalObject*>::iterator it = v.begin(), endit = v.end();

  while (it != endit)
    {
      this->mDrawables.push_back(*it);
      ++it;
    }

  // update the association maps
  // we store which species reference glyph is associated with which species glyph
  // and which text glyph is associated with which graphical object
  this->update_associations();
}

/**
 * This method goes throught the list of all drawables and tries to resolve the
 * style for each object.
 */
void CLLayoutRenderer::update_style_information()
{
  this->mStyleMap.clear();

  if (this->mpResolver != NULL)
    {
      std::vector<const CLGraphicalObject*>::const_iterator it = this->mDrawables.begin();
      std::vector<const CLGraphicalObject*>::const_iterator endit = this->mDrawables.end();
      const CLStyle* pStyle = NULL;

      while (it != endit)
        {
          pStyle = this->mpResolver->resolveStyle(*it);

          if (pStyle)
            {
              this->mStyleMap[*it] = pStyle;
            }

          ++it;
        }
    }
}

/**
 * This method goes through all styles that are used by the current drawables
 * and figures out which gradients, colors and line stipples are used and
 * creates them.
 */
void CLLayoutRenderer::update_textures_and_colors()
{
  // only update the textures and colors for the current drawables that actually have a
  // style
  std::map<const CLGraphicalObject*, const CLStyle*>::const_iterator it = this->mStyleMap.begin();
  std::map<const CLGraphicalObject*, const CLStyle*>::const_iterator endit = this->mStyleMap.end();
  const CLReactionGlyph* pRG = NULL;
  const CLMetabReferenceGlyph* pSRG = NULL;
  const CLTextGlyph* pTG = NULL;
  double maxDimension = 0.0;
  const CLBoundingBox* pBB = NULL;

  while (it != endit)
    {
      assert(it->first != NULL);
      assert(it->second != NULL);
      pRG = dynamic_cast<const CLReactionGlyph*>(it->first);
      pSRG = dynamic_cast<const CLMetabReferenceGlyph*>(it->first);
      pTG = dynamic_cast<const CLTextGlyph*>(it->first);
      pBB = &it->first->getBoundingBox();

      if ((pRG != NULL && pRG->getCurve().getNumCurveSegments() != 0) || (pSRG != NULL && pSRG->getCurve().getNumCurveSegments() != 0))
        {
          // we set the maxDimension to 0 so that we don't calculate
          // gradients for the objects where the curve from the layout is
          // drawn anyway
          maxDimension = 0.0;
        }
      else if (pTG != NULL)
        {
          // it is a text glyph, so there can't be a gradient or line
          // stipple, but we need to create a texture for the font
          maxDimension = 0.0;
          std::string text = CLLayoutRenderer::resolve_text(pTG);
          // get the font spec for the group
          CLFontSpec fontSpec = this->getFontSpec(it->second->getGroup(), pBB->getDimensions().getHeight(), CLFontSpec());
          std::map<CLFontSpec, std::map<std::string, CLTextTextureSpec*> >::iterator pos = this->mFontTextureMap.find(fontSpec);

          if (pos == this->mFontTextureMap.end())
            {
              std::map<std::string, CLTextTextureSpec*> m;
              this->mFontTextureMap[fontSpec] = m;
              pos = this->mFontTextureMap.find(fontSpec);
              assert(pos != this->mFontTextureMap.end());
            }

          std::map<std::string, CLTextTextureSpec*>::iterator pos2 = pos->second.find(text);

          if (pos2 == pos->second.end() || pos2->second->mTextureName == 0)
            {
              // add the texture although it might be NULL
              //std::cout << "Creating new texture for text glyph: " << pTG->getId() << std::endl;
              std::pair<CLTextTextureSpec*, GLubyte*> texture = (*this->mpFontRenderer)(fontSpec.mFamily, fontSpec.mSize, text, fontSpec.mWeight, fontSpec.mStyle, this->mZoomFactor);

              //std::cout << "Created texture at " << pTexture << " for text \"" << text << "\"" << std::endl;
              //std::cout << "texture id: " << pTexture->mTextureName << std::endl;
              if (texture.first != NULL && texture.second != NULL)
                {
                  glGenTextures(1, &texture.first->mTextureName);
                  assert(texture.first->mTextureName != 0);
                  glBindTexture(GL_TEXTURE_2D, texture.first->mTextureName);
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                  glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, texture.first->mTextureWidth, texture.first->mTextureHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, texture.second);
                  delete[] texture.second;
                }

              pos->second[text] = texture.first;
              this->mTextGlyphMap[pTG] = texture.first;
            }
          else
            {
              // check if the texture has the correct scale and if not, rescale it
              std::pair<double, double> size = this->mpFontRenderer->getTextureSize(fontSpec, text);
              CLTextTextureSpec* pTexture = pos2->second;

              //std::cout << "Existing texture found: " << pTexture->mTextureName;
              if (pTexture != NULL && pTexture->mScale != this->mZoomFactor)
                {
                  //std::cout << "Need to rescale texture." << std::endl;
                  // we create a new larger texture
                  double newScale = pTexture->mMaxScale;

                  if (pTexture->mTextureName != 0)
                    {
                      glDeleteTextures(1, &pTexture->mTextureName);
                    }

                  delete pTexture;
                  pos2->second = NULL;

                  if (fabs(newScale + 1.0) < ALMOST_ZERO)
                    {
                      newScale = this->mZoomFactor;
                    }

                  std::pair<CLTextTextureSpec*, GLubyte*> texture = (*this->mpFontRenderer)(fontSpec.mFamily, fontSpec.mSize, text, fontSpec.mWeight, fontSpec.mStyle, newScale);

                  // check if the texture has a size that is supported
                  //std::cout << "Created texture at " << pTexture << " for text \"" << text << "\"" << std::endl;
                  //std::cout << "texture id: " << pTexture->mTextureName << std::endl;
                  if (texture.first != NULL && texture.second != NULL)
                    {
                      glGenTextures(1, &texture.first->mTextureName);
                      assert(texture.first->mTextureName != 0);
                      glBindTexture(GL_TEXTURE_2D, texture.first->mTextureName);
                      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                      glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, texture.first->mTextureWidth, texture.first->mTextureHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, texture.second);
                      delete[] texture.second;
                    }

                  pos2->second = texture.first;
                  //std::cout << "rescaled texture id: " << pTexture->mTextureName << std::endl;
                  this->mTextGlyphMap[pTG] = texture.first;
                }
              else
                {
                  //std::cout << "Using texture as is." << std::endl;
                  this->mTextGlyphMap[pTG] = pos2->second;
                }
            }
        }
      else
        {
          maxDimension = (pBB->getDimensions().getWidth() > pBB->getDimensions().getHeight()) ? pBB->getDimensions().getWidth() : pBB->getDimensions().getHeight();
          // we also have to consider the zoom factor
          // if we do it here, we only have to multiply once
          maxDimension *= this->mZoomFactor;
        }

      this->update_textures_and_colors(it->second->getGroup(), maxDimension, pBB->getDimensions().getHeight());
      ++it;
    }

  // go through all line endings and find the colors and update the textures
  // line endings can contain images, gradients and/or text elements
  std::map<std::string, const CLLineEnding*>::const_iterator lineendingIt = this->mLineEndingMap.begin(), lineendingEndit = this->mLineEndingMap.end();
  double w = 0.0;
  double h = 0.0;
  const CLLineEnding* pLE = NULL;

  while (lineendingIt != lineendingEndit)
    {
      pLE = lineendingIt->second;
      w = pLE->getBoundingBox()->getDimensions().getWidth();
      h = pLE->getBoundingBox()->getDimensions().getHeight();
      this->update_textures_and_colors(pLE->getGroup(), ((w > h) ? w : h), h);
      ++lineendingIt;
    }

  // actually create the gradient textures
  //std::cout << "Creating gradient textures." << std::endl;
  std::map<std::string, std::pair<const CLGradientBase*, CLTextureSpec*> >::iterator textureIt = this->mGradientMap.begin(), textureEndit = this->mGradientMap.end();
  CLTextureSpec* pSpec = NULL;
  const CLGradientBase* pGradient = NULL;

  while (textureIt != textureEndit)
    {
      pSpec = textureIt->second.second;

      if (pSpec->mTextureName == 0)
        {
          pGradient = textureIt->second.first;
          //std::cout << "Creating texture for gradient: " << pGradient->getId() << std::endl;
          unsigned int exponent = (unsigned int)ceil(log(pSpec->mTextWidth) / log(2.0));
          // make sure a texture of this size is supported, else we lower the size
          unsigned int val = (1 << exponent);
          GLint width = 0;
          glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_RGBA, val, val, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
          glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);

          while (width == 0 && val > 1)
            {
              // divide the size by two in each direction
              val = (val >> 1);
              glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_RGBA, val, val, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
              glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
            }

          if (width == 0)
            {
              // delete the texture since we can not draw it anyway
              //std::cout << "Could not create a texture." << std::endl;
              pSpec->mTextureName = 0;
            }
          else
            {
              if (val < (unsigned int)(1 << exponent))
                {
                  // create a warning that the texture had to be scaled down
                  std::cerr << "Gradient texture to large for current openGL implementation. Scaling down." << std::endl;
                }

              // create the texture
              pSpec->mTextureWidth = val;
              pSpec->mTextureHeight = val;
              pSpec->mTextWidth = val;
              pSpec->mTextHeight = val;
              pSpec->mTextureName = 0;
              GLubyte* textureData = NULL;

              try
                {
                  glGenTextures(1, &pSpec->mTextureName);
                  // make sure a usable texture name ha been created
                  assert(pSpec->mTextureName != 0);
                  val = (val > GRADIENT_TEXTURE_SIZE_LIMIT) ? GRADIENT_TEXTURE_SIZE_LIMIT : val;
                  GLubyte* textureData = new GLubyte[4*val*val];
                  create_gradient_texture(val, textureData, pGradient);
                  glBindTexture(GL_TEXTURE_2D, pSpec->mTextureName);
                  assert(pSpec->mTextureName != 0);
                  //std::cout << "new texture created with id: " << pSpec->mTextureName << std::endl;
                  //std::cout << "size: " << val << std::endl;
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, val, val, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
                  delete[] textureData;
                }
              catch (...)
                {
                  if (textureData != NULL)
                    {
                      delete[] textureData;
                    }
                }
            }
        }

      ++textureIt;
    }
}

/**
 * Goes through all render objects in the given group and updates the color
 * map and gradients.
 * The maxDimension parameter is the maximum of the width and the height of the
 * corresponding layout object. This value is needed to determine the size of gradient textures.
 */
void CLLayoutRenderer::update_textures_and_colors(const CLGroup* pGroup, double maxDimension, double height, const std::string& parentFill, CLFontSpec parentFontSpec)
{
  std::string strokeId;
  std::string fillId;
  std::string newParentFill = parentFill;
  CLFontSpec newParentFontSpec = this->getFontSpec(pGroup, height, parentFontSpec);
  std::string gradientId;
  const std::vector<unsigned int>* pDashArray;
  GLubyte colorA[4];

  if (pGroup->isSetFill())
    {
      fillId = pGroup->getFillColor();

      // the fill id can actually be the id of a gradient
      // try to resolve the color and add it to the map
      // if it can't be resolved it might be a gradient, so resolve the
      // gradient and create a CLText*ureSpec for it
      // if there already is a CLText*ureSpec object for this gradient, we might
      // have to update the size
      if (this->mColorMap.find(fillId) == this->mColorMap.end())
        {
          try
            {
              this->resolve_color(fillId, colorA);
              CLRGBAColor c = {colorA[0], colorA[1], colorA[2], colorA[3]};
              this->mColorMap[fillId] = c;
            }
          catch (...)
            {
              // it could be a gradient
              if (this->mGradientMap.find(fillId) == this->mGradientMap.end())
                {
                  const CLGradientBase* pGradient = mpResolver->getGradientBase(fillId);
                  assert(pGradient);
                  // add all colors in the gradient base to the color map
                  this->update_colors(pGradient);
                  CLTextureSpec* pSpec = new CLTextureSpec();
                  pSpec->mTextureName = 0;
                  pSpec->mTextWidth = pSpec->mTextHeight = 0;
                  this->mGradientMap[fillId] = std::pair<const CLGradientBase*, CLTextureSpec*>(pGradient, pSpec);
                  newParentFill = fillId;
                }
            }
        }
    }

  if (pGroup->isSetStroke())
    {
      strokeId = pGroup->getStroke();

      // this must be a color string or a color id
      // resolve the color and add it to the map
      if (this->mColorMap.find(strokeId) == this->mColorMap.end())
        {
          this->resolve_color(strokeId, colorA);
          CLRGBAColor c = {colorA[0], colorA[1], colorA[2], colorA[3]};
          this->mColorMap[strokeId] = c;
        }
    }

  if (pGroup->isSetDashArray())
    {
      pDashArray = &(pGroup->getDashArray());
      // create the 1D texture for it if necessary
      std::map<const std::vector<unsigned int>, const CLLineStippleTexture*>::const_iterator pos = this->mLinestippleMap.find(*pDashArray);

      if (pos == this->mLinestippleMap.end())
        {
          const CLLineStippleTexture* pTexture = this->createLineStippleTexture(*pDashArray);
          this->mLinestippleMap[*pDashArray] = pTexture;
        }
    }

  if (pGroup->isSetStartHead())
    {
      std::string headId = pGroup->getStartHead();

      if (this->mLineEndingMap.find(headId) == this->mLineEndingMap.end())
        {
          const CLLineEnding* pLineEnding = this->mpResolver->getLineEnding(headId);
          assert(pLineEnding != NULL);
          this->mLineEndingMap[headId] = pLineEnding;
        }
    }

  if (pGroup->isSetEndHead())
    {
      std::string headId = pGroup->getEndHead();

      if (this->mLineEndingMap.find(headId) == this->mLineEndingMap.end())
        {
          const CLLineEnding* pLineEnding = this->mpResolver->getLineEnding(headId);
          assert(pLineEnding != NULL);
          this->mLineEndingMap[headId] = pLineEnding;
        }
    }

  const CLGraphicalPrimitive1D* pP1D = NULL;

  const CLGraphicalPrimitive2D* pP2D = NULL;

  const CLText* pText = NULL;

  const CLGroup* pChildGroup = NULL;

  const CLRenderCurve* pCurve = NULL;

  size_t i, iMax = pGroup->getNumElements();

  for (i = 0; i < iMax; ++i)
    {
      // if elements don't set their own stroke or fill color, the inherit it
      // from their parent group
      // the same is true for the line stipple
      pP1D = dynamic_cast<const CLGraphicalPrimitive1D*>(pGroup->getElement(i));

      if (pP1D != NULL)
        {
          // the object can have a stroke color and a line stipple
          pP2D = dynamic_cast<const CLGraphicalPrimitive2D*>(pP1D);
          pText = dynamic_cast<const CLText*>(pP1D);
          pCurve = dynamic_cast<const CLRenderCurve*>(pP1D);

          if (pP2D != NULL)
            {
              pChildGroup = dynamic_cast<const CLGroup*>(pP2D);

              if (pChildGroup != NULL)
                {
                  // recursively call this method
                  this->update_textures_and_colors(pChildGroup, maxDimension, height, newParentFill);
                }
              else
                {
                  if (pP2D->isSetStroke())
                    {
                      strokeId = pP2D->getStroke();

                      // this must be a color string or a color id
                      // resolve the color and add it to the map
                      if (this->mColorMap.find(strokeId) == this->mColorMap.end())
                        {
                          this->resolve_color(strokeId, colorA);
                          CLRGBAColor c = {colorA[0], colorA[1], colorA[2], colorA[3]};
                          this->mColorMap[strokeId] = c;
                        }
                    }

                  if (pP2D->isSetDashArray())
                    {
                      pDashArray = &pP2D->getDashArray();
                      // create the 1D texture for it if necessary
                      std::map<const std::vector<unsigned int>, const CLLineStippleTexture*>::const_iterator pos = this->mLinestippleMap.find(*pDashArray);

                      if (pos == this->mLinestippleMap.end())
                        {
                          const CLLineStippleTexture* pTexture = this->createLineStippleTexture(*pDashArray);
                          this->mLinestippleMap[*pDashArray] = pTexture;
                        }
                    }

                  if (pP2D->isSetFill())
                    {
                      fillId = pP2D->getFillColor();

                      // the fill id can actually be the id of a gradient
                      // try to resolve the color and add it to the map
                      // if it can't be resolved it might be a gradient, so resolve the
                      // gradient and create a CLText*ureSpec for it
                      // if there already is a CLText*ureSpec object for this gradient, we might
                      // have to update the size
                      if (this->mColorMap.find(fillId) == this->mColorMap.end())
                        {
                          try
                            {
                              this->resolve_color(fillId, colorA);
                              CLRGBAColor c = {colorA[0], colorA[1], colorA[2], colorA[3]};
                              this->mColorMap[fillId] = c;
                            }
                          catch (...)
                            {
                              // it could be a gradient
                              std::map<std::string, std::pair<const CLGradientBase*, CLTextureSpec*> >::iterator pos = this->mGradientMap.find(fillId);

                              if (pos == this->mGradientMap.end())
                                {
                                  // we have to create a new CLText*ureSpec
                                  const CLGradientBase* pGradient = mpResolver->getGradientBase(fillId);
                                  assert(pGradient);
                                  // add all colors in the gradient base to the color map
                                  this->update_colors(pGradient);
                                  CLTextureSpec* pSpec = new CLTextureSpec();
                                  pSpec->mTextureName = 0;
                                  pSpec->mTextWidth = pSpec->mTextHeight = maxDimension;
                                  this->mGradientMap[fillId] = std::pair<const CLGradientBase*, CLTextureSpec*>(pGradient, pSpec);
                                }
                              else
                                {
                                  if (maxDimension > pos->second.second->mTextWidth)
                                    {
                                      // update the dimensions of the texture
                                      pos->second.second->mTextWidth = pos->second.second->mTextHeight = maxDimension;

                                      // delete the old data if necessary
                                      if (pos->second.second->mTextureName != 0)
                                        {
                                          glDeleteTextures(1, &pos->second.second->mTextureName);
                                          pos->second.second->mTextureName = 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                  else if (!newParentFill.empty())
                    {
                      // we might have inherited a fillId from the parent
                      // group so we might have to update the size of the
                      // texture
                      std::map<std::string, std::pair<const CLGradientBase*, CLTextureSpec*> >::iterator pos = this->mGradientMap.find(fillId);

                      if (pos != this->mGradientMap.end() && maxDimension > pos->second.second->mTextWidth)
                        {
                          pos->second.second->mTextWidth = pos->second.second->mTextHeight = maxDimension;

                          if (pos->second.second->mTextureName != 0)
                            {
                              glDeleteTextures(1, &pos->second.second->mTextureName);
                              pos->second.second->mTextureName = 0;
                            }
                        }
                    }
                }
            }
          else if (pText != NULL)
            {
              if (pText->isSetStroke())
                {
                  strokeId = pText->getStroke();

                  // this must be a color string or a color id
                  // resolve the color and add it to the map
                  if (this->mColorMap.find(strokeId) == this->mColorMap.end())
                    {
                      this->resolve_color(strokeId, colorA);
                      CLRGBAColor c = {colorA[0], colorA[1], colorA[2], colorA[3]};
                      this->mColorMap[strokeId] = c;
                    }
                }

              std::string text = pText->getText();
              // get the font spec for the group
              CLFontSpec fontSpec = this->getFontSpec(pText, height, newParentFontSpec);
              std::map<CLFontSpec, std::map<std::string, CLTextTextureSpec*> >::iterator pos = this->mFontTextureMap.find(fontSpec);

              if (pos == this->mFontTextureMap.end())
                {
                  std::map<std::string, CLTextTextureSpec*> s;
                  this->mFontTextureMap[fontSpec] = s;
                  pos = this->mFontTextureMap.find(fontSpec);
                  assert(pos != this->mFontTextureMap.end());
                }

              std::map<std::string, CLTextTextureSpec*>::iterator pos2 = pos->second.find(text);

              if (pos2 == pos->second.end())
                {
                  // add the texture although it might be NULL
                  std::pair<CLTextTextureSpec*, GLubyte*> texture = (*this->mpFontRenderer)(fontSpec.mFamily, fontSpec.mSize, text, fontSpec.mWeight, fontSpec.mStyle, this->mZoomFactor);

                  //std::cout << "No texture found. Created texture at " << pTexture << " for text \"" << text << "\"" << std::endl;
                  //std::cout << "texture id: " << pTexture->mTextureName << std::endl;
                  if (texture.first != NULL && texture.second != NULL)
                    {
                      glGenTextures(1, &texture.first->mTextureName);
                      assert(texture.first->mTextureName != 0);
                      glBindTexture(GL_TEXTURE_2D, texture.first->mTextureName);
                      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                      glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, texture.first->mTextureWidth, texture.first->mTextureHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, texture.second);
                      delete[] texture.second;
                    }

                  pos->second[text] = texture.first;
                  this->mTextMap[pText] = texture.first;
                }
              else
                {
                  // check if the texture is large enough
                  std::pair<double, double> size = this->mpFontRenderer->getTextureSize(fontSpec, text);
                  CLTextTextureSpec* pTexture = pos2->second;

                  if (pTexture != NULL && pTexture->mScale != this->mZoomFactor)
                    {
                      //std::cout << "We create a larger texture for texture at " << pTexture << "." << std::endl;
                      // we create a new larger texture
                      double newScale = pTexture->mMaxScale;

                      if (pTexture->mTextureName != 0)
                        {
                          //std::cout << "We delete the current OpenGL texture:" << pTexture->mTextureName << std::endl;
                          glDeleteTextures(1, &pTexture->mTextureName);
                        }

                      delete pTexture;
                      pTexture = NULL;
                      pos2->second = NULL;

                      if (fabs(newScale + 1.0) < ALMOST_ZERO)
                        {
                          newScale = this->mZoomFactor;
                        }

                      std::pair<CLTextTextureSpec*, GLubyte*> texture = (*this->mpFontRenderer)(fontSpec.mFamily, fontSpec.mSize, text, fontSpec.mWeight, fontSpec.mStyle, newScale);

                      //std::cout << "Created texture at " << pTexture << " for text \"" << text << "\"" << std::endl;
                      //std::cout << "texture id: " << pTexture->mTextureName << std::endl;
                      if (texture.first != NULL && texture.second != NULL)
                        {
                          glGenTextures(1, &texture.first->mTextureName);
                          assert(texture.first->mTextureName != 0);
                          glBindTexture(GL_TEXTURE_2D, texture.first->mTextureName);
                          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                          glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                          glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, texture.first->mTextureWidth, texture.first->mTextureHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, texture.second);
                          delete[] texture.second;
                        }

                      pos2->second = texture.first;
                      this->mTextMap[pText] = texture.first;
                    }
                  else
                    {
                      //std::cout << "We are reusing the texture at " << pos2->second << std::endl;
                      this->mTextMap[pText] = pos2->second;
                    }
                }
            }
          else
            {
              if (pP1D->isSetStroke())
                {
                  strokeId = pP1D->getStroke();

                  // this must be a color string or a color id
                  // resolve the color and add it to the map
                  if (this->mColorMap.find(strokeId) == this->mColorMap.end())
                    {
                      this->resolve_color(strokeId, colorA);
                      CLRGBAColor c = {colorA[0], colorA[1], colorA[2], colorA[3]};
                      this->mColorMap[strokeId] = c;
                    }
                }

              if (pP1D->isSetDashArray())
                {
                  pDashArray = &pP1D->getDashArray();
                  // create the 1D texture for it if necessary
                  std::map<const std::vector<unsigned int>, const CLLineStippleTexture*>::const_iterator pos = this->mLinestippleMap.find(*pDashArray);

                  if (pos == this->mLinestippleMap.end())
                    {
                      const CLLineStippleTexture* pTexture = this->createLineStippleTexture(*pDashArray);
                      this->mLinestippleMap[*pDashArray] = pTexture;
                    }
                }

              if (pCurve != NULL)
                {
                  if (pCurve->isSetStartHead())
                    {
                      std::string headId = pCurve->getStartHead();

                      if (this->mLineEndingMap.find(headId) == this->mLineEndingMap.end())
                        {
                          const CLLineEnding* pLineEnding = this->mpResolver->getLineEnding(headId);
                          assert(pLineEnding != NULL);
                          this->mLineEndingMap[headId] = pLineEnding;
                        }
                    }

                  if (pCurve->isSetEndHead())
                    {
                      std::string headId = pCurve->getEndHead();

                      if (this->mLineEndingMap.find(headId) == this->mLineEndingMap.end())
                        {
                          const CLLineEnding* pLineEnding = this->mpResolver->getLineEnding(headId);
                          assert(pLineEnding != NULL);
                          this->mLineEndingMap[headId] = pLineEnding;
                        }
                    }
                }
            }
        }
    }
}

/**
 * This method creates a FontSpec object from the font attributes in the given
 * group.
 * The height that is passed to the method is the height for the bounding box
 * and it used to calculate the font size if it has a relative component.
 */
CLFontSpec CLLayoutRenderer::getFontSpec(const CLGroup* pGroup, double boxHeight, const CLFontSpec& parentFontSpec)
{
  CLFontSpec spec(parentFontSpec);

  if (pGroup->isSetFontFamily())
    {
      spec.mFamily = pGroup->getFontFamily();
    }

  if (pGroup->isSetFontSize())
    {
      spec.mSize = pGroup->getFontSize().getAbsoluteValue() + pGroup->getFontSize().getRelativeValue() / 100.0 * boxHeight;
    }

  if (pGroup->isSetFontWeight())
    {
      spec.mWeight = pGroup->getFontWeight();
    }

  if (pGroup->isSetFontStyle())
    {
      spec.mStyle = pGroup->getFontStyle();
    }

  return spec;
}

/**
 * This method creates a FontSpec object from the font attributes in the given
 * text element.
 * The height that is passed to the method is the height for the bounding box
 * and it used to calculate the font size if it has a relative component.
 */
CLFontSpec CLLayoutRenderer::getFontSpec(const CLText* pText, double boxHeight, const CLFontSpec& parentFontSpec)
{
  CLFontSpec spec(parentFontSpec);

  if (pText->isSetFontFamily())
    {
      spec.mFamily = pText->getFontFamily();
    }

  if (pText->isSetFontSize())
    {
      spec.mSize = pText->getFontSize().getAbsoluteValue() + pText->getFontSize().getRelativeValue() / 100.0 * boxHeight;
    }

  if (pText->isSetFontWeight())
    {
      spec.mWeight = pText->getFontWeight();
    }

  if (pText->isSetFontStyle())
    {
      spec.mStyle = pText->getFontStyle();
    }

  return spec;
}

/**
 * This method sets the left edge of the viewport.
 */
void CLLayoutRenderer::setX(double x)
{
  this->mX = x;
}

/**
 * This method sets the upper edge of the viewport.
 */
void CLLayoutRenderer::setY(double y)
{
  this->mY = y;
}

/**
 * This methods extracts all colors from the given gradient and adds them to the
 * color map.
 */
void CLLayoutRenderer::update_colors(const CLGradientBase* pGradient)
{
  GLubyte colorA[4];
  size_t i, iMax = pGradient->getNumGradientStops();
  const CLGradientStop* pStop = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pStop = pGradient->getGradientStop(i);
      std::string colorString = pStop->getStopColor();

      if (!colorString.empty())
        {
          this->resolve_color(colorString, colorA);
          CLRGBAColor c = {colorA[0], colorA[1], colorA[2], colorA[3]};
          this->mColorMap[colorString] = c;
        }
    }
}

void CLLayoutRenderer::save_current_attributes()
{
  this->mStateList.push(this->mCurrentAttributes);
}

void CLLayoutRenderer::restore_current_attributes()
{
  this->mCurrentAttributes = this->mStateList.top();
  this->mStateList.pop();
}

void CLLayoutRenderer::draw_cap(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double stroke_width)
{
  // calculate the direction vector
  double vx1 = x2 - x1;
  double vy1 = y2 - y1;
  double vz1 = z2 - z1;
  double length = sqrt(vx1 * vx1 + vy1 * vy1 + vz1 * vz1);

  double normLength1, normLength2;

  // calculate the normal to this vector
  double vx2 = 0.0;
  double vy2 = 0.0;
  double vz2 = 0.0;
  double half_width = stroke_width / 2.0;

  if (fabs(vx1) < ALMOST_ZERO && vz1 < ALMOST_ZERO)
    {
      // scale by the stroke_width
      vx2 = -vy1 / length * half_width;
      vy2 = 0.0;
      vz2 = 0.0;
    }
  else
    {
      // scale by the stroke_width
      double normY = vy1 / length;
      vx2 = -normY * vx1 / length * half_width;
      vy2 = (1 - normY * normY) * half_width;
      vz2 = -normY * vz1 / length * half_width;
      normLength1 = half_width / sqrt(vx2 * vx2 + vy2 * vy2 + vz2 * vz2);
      vx2 *= normLength1;
      vy2 *= normLength1;
      vz2 *= normLength1;
    }

  // calculate the direction vector
  double vx3 = x3 - x2;
  double vy3 = y3 - y2;
  double vz3 = z3 - z2;
  double length2 = sqrt(vx3 * vx3 + vy3 * vy3 + vz3 * vz3);

  // calculate the normal to this vector
  double vx4 = 0.0;
  double vy4 = 0.0;
  double vz4 = 0.0;

  if (fabs(vx3) < ALMOST_ZERO && vz3 < ALMOST_ZERO)
    {
      // scale by the stroke_width
      vx4 = -vy3 / length2 * half_width;
      vy4 = 0.0;
      vz4 = 0.0;
    }
  else
    {
      // scale by the stroke_width
      double normY = vy3 / length2;
      vx4 = -normY * vx3 / length2 * half_width;
      vy4 = (1 - normY * normY) * half_width;
      vz4 = -normY * vz3 / length2 * half_width;
      normLength2 = half_width / sqrt(vx4 * vx4 + vy4 * vy4 + vz4 * vz4);
      vx4 *= normLength2;
      vy4 *= normLength2;
      vz4 *= normLength2;
    }

  double length3 = sqrt(pow(x3 - x1, 2) + pow(y3 - y1, 2) + pow(z3 - z1, 2));
  double angle = (vx2 * vx4 + vy2 * vy4 + vz2 * vz4) / (sqrt(vx2 * vx2 + vy2 * vy2 + vz2 * vz2) * sqrt(vx4 * vx4 + vy4 * vy4 + vz4 * vz4));
  angle = acos(angle);

  // if the angle is not +/-0 or +/-180°
  if ((fabs(angle) > ALMOST_ZERO) && (fabs((fabs(angle) - M_PI)) / M_PI > ALMOST_ZERO))
    {
      // if the angle is greater 0, the gap is at the lower edge
      // else the gap is at the upper edge
      // calculate the center of the first line segment box
      // in order to draw the cap, we have to find the box point at the start
      // edge of the second segment that is not inside the box determined by the first segment.
      // This is the point that is further away from the center of the first box.
      double xx = (x2 + x1) / 2.0;
      double yy = (y2 + y1) / 2.0;
      double zz = (z2 + z1) / 2.0;
      double x21 = x2 + vx4;
      double y21 = y2 + vy4;
      double z21 = z2 + vz4;
      double x22 = x2 - vx4;
      double y22 = y2 - vy4;
      double z22 = z2 - vz4;
      double distance1 = sqrt(pow(x21 - xx, 2) + pow(y21 - yy, 2) + pow(z21 - zz, 2));

      if (distance1 > sqrt(pow(x22 - xx, 2) + pow(y22 - yy, 2) + pow(z22 - zz, 2)))
        {
          xx = (x3 + x2) / 2.0;
          yy = (y3 + y2) / 2.0;
          zz = (y3 + y2) / 2.0;
          double x23 = x2 + vx2;
          double y23 = y2 + vy2;
          double z23 = z2 + vz2;
          x22 = x2 - vx2;
          y22 = y2 - vy2;
          z22 = z2 - vz2;
          double distance1 = sqrt(pow(x23 - xx, 2) + pow(y23 - yy, 2) + pow(z23 - zz, 2));

          if (distance1 > sqrt(pow(x22 - xx, 2) + pow(y22 - yy, 2) + pow(z22 - zz, 2)))
            {
              if (angle < M_PI / 2.0 && (length3 > length && length3 > length2))
                {
                  glBegin(GL_TRIANGLES);
                  glVertex3d(x2, y2, z2);
                  glVertex3d(x21, y21, z21);
                  glVertex3d(x23, y23, z23);
                  glEnd();
                }
              else
                {
                  // we need to draw two triangles
                  const CLPoint* pP = CLLayoutRenderer::calculate_intersection(x21, y21, z21, vx3, vy3, vz3, x23, y23, z23, vx1, vy1, vz1);
                  glBegin(GL_TRIANGLE_FAN);
                  glVertex3d(pP->getX(), pP->getY(), pP->getZ());
                  glVertex3d(x21, y21, z21);
                  glVertex3d(x2, y2, z2);
                  glVertex3d(x23, y23, z23);
                  glEnd();
                  delete pP;
                }
            }
          else
            {
              if (angle < M_PI / 2.0 && (length3 > length && length3 > length2))
                {
                  glBegin(GL_TRIANGLES);
                  glVertex3d(x2, y2, z2);
                  glVertex3d(x21, y21, z21);
                  glVertex3d(x22, y22, z22);
                  glEnd();
                }
              else
                {
                  // we need to draw two triangles
                  const CLPoint* pP = CLLayoutRenderer::calculate_intersection(x21, y21, z21, vx3, vy3, vz3, x22, y22, z22, vx1, vy1, vz1);
                  glBegin(GL_TRIANGLE_FAN);
                  glVertex3d(pP->getX(), pP->getY(), pP->getZ());
                  glVertex3d(x21, y21, z21);
                  glVertex3d(x2, y2, z2);
                  glVertex3d(x22, y22, z22);
                  glEnd();
                  delete pP;
                }
            }
        }
      else
        {
          xx = (x3 + x2) / 2.0;
          yy = (y3 + y2) / 2.0;
          zz = (y3 + y2) / 2.0;
          double x23 = x2 + vx2;
          double y23 = y2 + vy2;
          double z23 = z2 + vz2;
          x21 = x2 - vx2;
          y21 = y2 - vy2;
          z21 = z2 - vz2;
          double distance1 = sqrt(pow(x23 - xx, 2) + pow(y23 - yy, 2) + pow(z23 - zz, 2));

          if (distance1 > sqrt(pow(x21 - xx, 2) + pow(y21 - yy, 2) + pow(z21 - zz, 2)))
            {
              if (angle < M_PI / 2.0 && length3 > length && length3 > length2)
                {
                  glBegin(GL_TRIANGLES);
                  glVertex3d(x2, y2, z2);
                  glVertex3d(x22, y22, z22);
                  glVertex3d(x23, y23, z23);
                  glEnd();
                }
              else
                {
                  // we need to draw two triangles
                  const CLPoint* pP = CLLayoutRenderer::calculate_intersection(x22, y22, z22, vx3, vy3, vz3, x23, y23, z23, vx1, vy1, vz1);
                  glBegin(GL_TRIANGLE_FAN);
                  glVertex3d(pP->getX(), pP->getY(), pP->getZ());
                  glVertex3d(x22, y22, z22);
                  glVertex3d(x2, y2, z2);
                  glVertex3d(x23, y23, z23);
                  glEnd();
                  delete pP;
                }
            }
          else
            {
              if (angle < M_PI / 2.0 && length3 > length && length3 > length2)
                {
                  glBegin(GL_TRIANGLES);
                  glVertex3d(x2, y2, z2);
                  glVertex3d(x22, y22, z22);
                  glVertex3d(x21, y21, z21);
                  glEnd();
                }
              else
                {
                  // we need to draw two triangles
                  const CLPoint* pP = CLLayoutRenderer::calculate_intersection(x22, y22, z22, vx3, vy3, vz3, x21, y21, z21, vx1, vy1, vz1);
                  glBegin(GL_TRIANGLE_FAN);
                  glVertex3d(pP->getX(), pP->getY(), pP->getZ());
                  glVertex3d(x22, y22, z22);
                  glVertex3d(x2, y2, z2);
                  glVertex3d(x21, y21, z21);
                  glEnd();
                  delete pP;
                }
            }
        }
    }
}

void CLLayoutRenderer::clear_cached_data()
{
  std::map<std::string, std::pair<const CLGradientBase*, CLTextureSpec*> >::iterator it1 = this->mGradientMap.begin(), endit1 = this->mGradientMap.end();

  while (it1 != endit1)
    {
      if (it1->second.second != NULL)
        {
          if (it1->second.second->mTextureName != 0)
            {
              glDeleteTextures(1, &it1->second.second->mTextureName);
            }

          delete it1->second.second;
        }

      ++it1;
    }

  this->mGradientMap.clear();
  std::map<CLFontSpec, std::map<std::string, CLTextTextureSpec*> >::iterator it2 = this->mFontTextureMap.begin(), endit2 = this->mFontTextureMap.end();

  while (it2 != endit2)
    {
      std::map<std::string, CLTextTextureSpec*>::const_iterator it3 = it2->second.begin(), endit3 = it2->second.end();

      while (it3 != endit3)
        {
          if (it3->second != NULL)
            {
              if (it3->second->mTextureName != 0)
                {
                  glDeleteTextures(1, &it3->second->mTextureName);
                }

              delete it3->second;
            }

          ++it3;
        }

      it2->second.clear();
      ++it2;
    }

  this->mFontTextureMap.clear();
  std::map<const std::vector<unsigned int>, const CLLineStippleTexture*>::const_iterator it3 = this->mLinestippleMap.begin(), endit3 = this->mLinestippleMap.end();

  while (it3 != endit3)
    {
      if (it3->second != NULL)
        {
          delete it3->second;
        }

      ++it3;
    }

  this->mLinestippleMap.clear();
  // delete all image textures
  std::map<std::string, const CLTextureSpec*>::iterator it4 = this->mImageMap.begin(), endit4 = this->mImageMap.end();

  while (it4 != endit4)
    {
      if (it4->second != NULL)
        {
          if (it4->second->mTextureName != 0)
            {
              glDeleteTextures(1, &it4->second->mTextureName);
            }

          delete it4->second;
        }

      ++it4;
    }

  this->mImageMap.clear();
  this->mColorMap.clear();
  this->mStyleMap.clear();
  this->mDrawables.clear();
  this->mLineEndingMap.clear();
  this->mTextGlyphMap.clear();
  this->mTextMap.clear();
}

CLPoint* CLLayoutRenderer::calculate_intersection(double p1x, double p1y, double p1z, double sx, double sy, double sz,
    double p2x, double p2y, double p2z, double tx, double ty, double tz)
{
  CLPoint* pP = NULL;

  if (fabs(sx) > ALMOST_ZERO)
    {
      double m = (p1y - p2y + ((p2x / sx) - (p1x / sx)) * sy) / (ty - tx * sy / sx);
      double n = (p2x + m * tx - p1x) / sx;
      pP = new CLPoint(p2x + m*tx, p2y + m*ty, p2z + m*tz);
      CLPoint* pP2 = new CLPoint(p1x + n*sx, p1y + n*sy, p1z + n*sz);

      if (fabs(pP->getX()) > ALMOST_ZERO)
        {
          assert(fabs((pP->getX() - pP2->getX()) / pP->getX()) < 1e-6);
        }
      else
        {
          assert(fabs(pP2->getX()) < ALMOST_ZERO);
        }

      if (fabs(pP->getY()) > ALMOST_ZERO)
        {
          assert(fabs((pP->getY() - pP2->getY()) / pP->getY()) < 1e-6);
        }
      else
        {
          assert(fabs(pP2->getY()) < ALMOST_ZERO);
        }

      if (fabs(pP->getZ()) > ALMOST_ZERO)
        {
          assert(fabs((pP->getZ() - pP2->getZ()) / pP->getZ()) < 1e-6);
        }
      else
        {
          assert(fabs(pP2->getZ()) < ALMOST_ZERO);
        }

      delete pP2;
    }
  else if (fabs(tx) > ALMOST_ZERO)
    {
      // first line is in the yz plane or a plane parallel to it
      // the intersection must be at p2x=p1x
      double m = (p1x - p2x) / tx;
      pP = new CLPoint(p2x + m*tx, p2y + m*ty, p2z + m*tz);

      if (fabs(sy) > ALMOST_ZERO)
        {
          double n = (pP->getY() - p1y) / sy;
          CLPoint* pP2 = new CLPoint(p1x + n*sx, p1y + n*sy, p1z + n*sz);

          if (fabs(pP->getX()) > ALMOST_ZERO)
            {
              assert(fabs((pP->getX() - pP2->getX()) / pP->getX()) < 1e-6);
            }
          else
            {
              assert(fabs(pP2->getX()) < ALMOST_ZERO);
            }

          if (fabs(pP->getY()) > ALMOST_ZERO)
            {
              assert(fabs((pP->getY() - pP2->getY()) / pP->getY()) < 1e-6);
            }
          else
            {
              assert(fabs(pP2->getY()) < ALMOST_ZERO);
            }

          if (fabs(pP->getZ()) > ALMOST_ZERO)
            {
              assert(fabs((pP->getZ() - pP2->getZ()) / pP->getZ()) < 1e-6);
            }
          else
            {
              assert(fabs(pP2->getZ()) < ALMOST_ZERO);
            }

          delete pP2;
        }
      else if (fabs(sz) > ALMOST_ZERO)
        {
          double n = (pP->getZ() - p1z) / sz;
          CLPoint* pP2 = new CLPoint(p1x + n*sx, p1y + n*sy, p1z + n*sz);

          if (fabs(pP->getX()) > ALMOST_ZERO)
            {
              assert(fabs((pP->getX() - pP2->getX()) / pP->getX()) < 1e-6);
            }
          else
            {
              assert(fabs(pP2->getX()) < ALMOST_ZERO);
            }

          if (fabs(pP->getY()) > ALMOST_ZERO)
            {
              assert(fabs((pP->getY() - pP2->getY()) / pP->getY()) < 1e-6);
            }
          else
            {
              assert(fabs(pP2->getY()) < ALMOST_ZERO);
            }

          if (fabs(pP->getZ()) > ALMOST_ZERO)
            {
              assert(fabs((pP->getZ() - pP2->getZ()) / pP->getZ()) < 1e-6);
            }
          else
            {
              assert(fabs(pP2->getZ()) < ALMOST_ZERO);
            }

          delete pP2;
        }
    }
  else
    {
      // both lines don't have a component in the x direction, so both must
      // lie in the yz plane or a plane parallel to it
      // there can only be an intersection if the x values are the same
      if (fabs(p1x - p2x) < ALMOST_ZERO)
        {
          // they are in the same plane
          if (fabs(sy) > ALMOST_ZERO)
            {
              double m = (p1z - p2z + (p2y / sy) * sz) / (tz - ty / sy * sz);
              double n = (p2y + m * ty) / sy;
              pP = new CLPoint(p2x + m*tx, p2y + m*ty, p2z + m*tz);
              CLPoint* pP2 = new CLPoint(p1x + n*sx, p1y + n*sy, p1z + n*sz);

              if (fabs(pP->getX()) > ALMOST_ZERO)
                {
                  assert(fabs((pP->getX() - pP2->getX()) / pP->getX()) < 1e-6);
                }
              else
                {
                  assert(fabs(pP2->getX()) < ALMOST_ZERO);
                }

              if (fabs(pP->getY()) > ALMOST_ZERO)
                {
                  assert(fabs((pP->getY() - pP2->getY()) / pP->getY()) < 1e-6);
                }
              else
                {
                  assert(fabs(pP2->getY()) < ALMOST_ZERO);
                }

              if (fabs(pP->getZ()) > ALMOST_ZERO)
                {
                  assert(fabs((pP->getZ() - pP2->getZ()) / pP->getZ()) < 1e-6);
                }
              else
                {
                  assert(fabs(pP2->getZ()) < ALMOST_ZERO);
                }

              delete pP2;
            }
          else if (fabs(ty) > ALMOST_ZERO)
            {
              double n = (p2z - p1z + (p2y / ty) * tz) / (sz - sy / ty * tz);
              double m = (p1y + n * sy) / ty;
              pP = new CLPoint(p2x + m*tx, p2y + m*ty, p2z + m*tz);
              CLPoint* pP2 = new CLPoint(p1x + n*sx, p1y + n*sy, p1z + n*sz);

              if (fabs(pP->getX()) > ALMOST_ZERO)
                {
                  assert(fabs((pP->getX() - pP2->getX()) / pP->getX()) < 1e-6);
                }
              else
                {
                  assert(fabs(pP2->getX()) < ALMOST_ZERO);
                }

              if (fabs(pP->getY()) > ALMOST_ZERO)
                {
                  assert(fabs((pP->getY() - pP2->getY()) / pP->getY()) < 1e-6);
                }
              else
                {
                  assert(fabs(pP2->getY()) < ALMOST_ZERO);
                }

              if (fabs(pP->getZ()) > ALMOST_ZERO)
                {
                  assert(fabs((pP->getZ() - pP2->getZ()) / pP->getZ()) < 1e-6);
                }
              else
                {
                  assert(fabs(pP2->getZ()) < ALMOST_ZERO);
                }

              delete pP2;
            }
          else if (fabs(sz) > ALMOST_ZERO)
            {
              double m = (p1y - p2y + (p2z / sz) * sy) / (ty - tz / sz * sy);
              double n = (p2z + m * tz) / sz;
              pP = new CLPoint(p2x + m*tx, p2y + m*ty, p2z + m*tz);
              CLPoint* pP2 = new CLPoint(p1x + n*sx, p1y + n*sy, p1z + n*sz);

              if (fabs(pP->getX()) > ALMOST_ZERO)
                {
                  assert(fabs((pP->getX() - pP2->getX()) / pP->getX()) < 1e-6);
                }
              else
                {
                  assert(fabs(pP2->getX()) < ALMOST_ZERO);
                }

              if (fabs(pP->getY()) > ALMOST_ZERO)
                {
                  assert(fabs((pP->getY() - pP2->getY()) / pP->getY()) < 1e-6);
                }
              else
                {
                  assert(fabs(pP2->getY()) < ALMOST_ZERO);
                }

              if (fabs(pP->getZ()) > ALMOST_ZERO)
                {
                  assert(fabs((pP->getZ() - pP2->getZ()) / pP->getZ()) < 1e-6);
                }
              else
                {
                  assert(fabs(pP2->getZ()) < ALMOST_ZERO);
                }

              delete pP2;
            }
        }
    }

  return pP;
}

/**
 * Sets whether the render extension is to deduce specie reference roles from associated
 * model objects if there are any.
 */
void CLLayoutRenderer::setDeduceSpeciesReferenceRoles(bool deduce)
{
  if (deduce != this->mDeduceSpeciesReferenceRoles)
    {
      this->mDeduceSpeciesReferenceRoles = deduce;

      if (this->mDeduceSpeciesReferenceRoles == true)
        {
          // try to deduce the roles and maybe update the style map
          if (this->mpLayout != NULL)
            {
              size_t i, iMax = this->mpLayout->getListOfReactionGlyphs().size();

              if (iMax > 0)
                {
                  CLReactionGlyph* pRG = NULL;
                  CLMetabReferenceGlyph* pSRG = NULL;
                  std::set<CLMetabReferenceGlyph*> speciesReferenceGlyphs;
                  size_t j, jMax;

                  for (i = 0; i < iMax; ++i)
                    {
                      pRG = this->mpLayout->getListOfReactionGlyphs()[i];
                      jMax = pRG->getListOfMetabReferenceGlyphs().size();

                      for (j = 0; j < jMax; ++j)
                        {
                          pSRG = pRG->getListOfMetabReferenceGlyphs()[j];

                          if (pSRG->getObjectRole().empty() && !pSRG->getModelObjectKey().empty())
                            {
                              speciesReferenceGlyphs.insert(pSRG);
                            }
                        }
                    }

                  if (!speciesReferenceGlyphs.empty())
                    {
                      // collect all the species references with their putative role
                      if (this->mpModel != NULL)
                        {
                          iMax = this->mpModel->getReactions().size();

                          if (iMax > 0)
                            {
                              const CReaction* pReaction = NULL;
                              const CChemEqElement* pSSR = NULL;
                              std::map<std::string, std::string> speciesReferenceRoles;

                              for (i = 0; i < iMax; ++i)
                                {
                                  pReaction = this->mpModel->getReactions()[i];
                                  jMax = pReaction->getChemEq().getSubstrates().size();

                                  for (j = 0; j < jMax; ++j)
                                    {
                                      pSSR = pReaction->getChemEq().getSubstrates()[j];

                                      if (pReaction->isReversible())
                                        {
                                          speciesReferenceRoles[pSSR->getKey()] = "product";
                                        }
                                      else
                                        {
                                          speciesReferenceRoles[pSSR->getKey()] = "substrate";
                                        }
                                    }

                                  jMax = pReaction->getChemEq().getProducts().size();

                                  for (j = 0; j < jMax; ++j)
                                    {
                                      pSSR = pReaction->getChemEq().getProducts()[j];
                                      speciesReferenceRoles[pSSR->getKey()] = "product";
                                    }

                                  jMax = pReaction->getChemEq().getModifiers().size();

                                  for (j = 0; j < jMax; ++j)
                                    {
                                      pSSR = pReaction->getChemEq().getModifiers()[j];
                                      speciesReferenceRoles[pSSR->getKey()] = "modifier";
                                    }
                                }

                              if (!speciesReferenceRoles.empty())
                                {
                                  std::set<CLMetabReferenceGlyph*>::iterator it = speciesReferenceGlyphs.begin(), endit = speciesReferenceGlyphs.end();
                                  std::map<std::string, std::string>::const_iterator pos, mapEnd = speciesReferenceRoles.end();

                                  // now we assign roles to the species reference glyphs
                                  while (it != endit)
                                    {
                                      pos = speciesReferenceRoles.find((*it)->getModelObjectKey());

                                      if (pos != mapEnd)
                                        {
                                          this->mSpeciesReferencesWithDeducedRole[*it] = pos->second;
                                        }

                                      ++it;
                                    }

                                  // check if we have to update the style mapping
                                  if (!this->mSpeciesReferencesWithDeducedRole.empty())
                                    {
                                      this->clear_cached_data();

                                      if (this->mpFontRenderer != NULL)
                                        {
                                          this->analyse_render_information(mX, mY, mX + mW / this->mZoomFactor, mY + mH / this->mZoomFactor);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
      else
        {
          // clear all deduced roles and update the style map
          if (!this->mSpeciesReferencesWithDeducedRole.empty())
            {
              this->mSpeciesReferencesWithDeducedRole.clear();
              // update the style mapping
              this->clear_cached_data();

              if (this->mpFontRenderer != NULL)
                {
                  this->analyse_render_information(mX, mY, mX + mW / this->mZoomFactor, mY + mH / this->mZoomFactor);
                }
            }
        }
    }
}

/**
 * Returns true or false depending on whether the render extension
 * deduces specie reference roles from associated
 * model objects if there are any.
 */
bool CLLayoutRenderer::isSetDeduceSpeciesReferenceRoles() const
{
  return this->mDeduceSpeciesReferenceRoles;
}

/**
 * This method adds a graphical object to the set of selected objects.
 */
void CLLayoutRenderer::addToSelection(CLGraphicalObject* pObject)
{
  assert(pObject != NULL);

  if (this->mSelection.insert(pObject).second == true)
    {
      this->draw_layout();
    }
}

/**
 * This method removes the given object from the selection if
 * it is selected.
 */
void CLLayoutRenderer::removeFromSelection(CLGraphicalObject* pObject)
{
  std::set<CLGraphicalObject*>::iterator pos = this->mSelection.find(pObject);

  if (pos != this->mSelection.end())
    {
      this->mSelection.erase(pos);
      this->draw_layout();
    }
}

/**
 * This method returns a reference to the set of selected objects.
 */
std::set<CLGraphicalObject*>& CLLayoutRenderer::getSelection()
{
  return this->mSelection;
}

/**
 * This method returns a const reference to the set of selected objects.
 */
const std::set<CLGraphicalObject*>& CLLayoutRenderer::getSelection() const
{
  return this->mSelection;
}

/**
 * This method returns true if the given object is part of the selection and false otherwise.
 */
bool CLLayoutRenderer::isSelected(const CLGraphicalObject* pObject) const
{
  return (this->mSelection.find(const_cast<CLGraphicalObject*>(pObject)) != this->mSelection.end());
}

/**
 * This method clears the selection.
 */
void CLLayoutRenderer::clearSelection()
{
  if (!this->mSelection.empty())
    {
      this->mSelection.clear();
    }
}

/**
 * This method returns all objects at the given 2D model coordinates.
 * The depth value is ignored.
 */
std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize> CLLayoutRenderer::getObjectsAt(double x, double y)
{
  // if the given point is within the current viewport, we only have to check the current drawbles
  // else we have to look at all layout elements.
  std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize> hits;

  if ((x >= this->mX) && (x <= (this->mX + this->mW / this->mZoomFactor)) &&
      (y >= this->mY) && (y <= (this->mY + this->mH / this->mZoomFactor)))
    {
      std::vector<const CLGraphicalObject*>::const_iterator it = this->mDrawables.begin(), endit = this->mDrawables.end();
      const CLReactionGlyph* pRG = NULL;
      const CLMetabReferenceGlyph* pSRG = NULL;
      const CLBoundingBox* pBB = NULL;
      const CLCurve* pCurve = NULL;
      const CLLineSegment* pLS = NULL;
      double bbx, bby, bbwidth, bbheight;
      double toleranceRadius = 5.0 / this->mZoomFactor;

      while (it != endit)
        {
          pSRG = dynamic_cast<const CLMetabReferenceGlyph*>(*it);
          pRG = dynamic_cast<const CLReactionGlyph*>(*it);

          if (pSRG != NULL && pSRG->getCurve().getNumCurveSegments() != 0)
            {
              pCurve = &pSRG->getCurve();
              assert(pCurve != NULL);
              size_t i, iMax = pCurve->getNumCurveSegments();

              for (i = 0; i < iMax; ++i)
                {
                  pLS = pCurve->getSegmentAt(i);
                  assert(pLS != NULL);

                  if (isSegmentHit(pLS, x, y, toleranceRadius))
                    {
                      hits.insert(const_cast<CLGraphicalObject*>(*it));
                      break;
                    }
                }
            }
          else if (pRG != NULL && pRG->getCurve().getNumCurveSegments())
            {
              pCurve = &pRG->getCurve();
              assert(pCurve != NULL);
              size_t i, iMax = pCurve->getNumCurveSegments();

              for (i = 0; i < iMax; ++i)
                {
                  pLS = pCurve->getSegmentAt(i);
                  assert(pLS != NULL);

                  if (isSegmentHit(pLS, x, y, toleranceRadius))
                    {
                      hits.insert(const_cast<CLGraphicalObject*>(*it));
                      break;
                    }
                }
            }
          else
            {
              pBB = &(*it)->getBoundingBox();
              bbx = pBB->getPosition().getX();
              bby = pBB->getPosition().getY();
              bbwidth = pBB->getDimensions().getWidth();
              bbheight = pBB->getDimensions().getHeight();

              if (x >= bbx && y >= bby && x <= (bbx + bbwidth) && y <= (bby + bbheight))
                {
                  hits.insert(const_cast<CLGraphicalObject*>(*it));
                }
            }

          ++it;
        }
    }
  else
    {
      if (this->mpLayout)
        {
          CLGraphicalObject* pGO = NULL;
          CLReactionGlyph* pRG = NULL;
          CLMetabReferenceGlyph* pSRG = NULL;
          const CLCurve* pCurve = NULL;
          const CLLineSegment* pLS = NULL;
          const CLBoundingBox* pBB = NULL;
          size_t k, kMax;
          size_t j, jMax;
          double bbx, bby, bbwidth, bbheight;
          double toleranceRadius = 5.0 / this->mZoomFactor;
          size_t i, iMax = this->mpLayout->getListOfCompartmentGlyphs().size();

          for (i = 0; i < iMax; ++i)
            {
              pGO = this->mpLayout->getListOfCompartmentGlyphs()[i];
              pBB = &pGO->getBoundingBox();
              bbx = pBB->getPosition().getX();
              bby = pBB->getPosition().getY();
              bbwidth = pBB->getDimensions().getWidth();
              bbheight = pBB->getDimensions().getHeight();

              if (x >= bbx && y >= bby && x <= (bbx + bbwidth) && y <= (bby + bbheight))
                {
                  hits.insert(pGO);
                }
            }

          iMax = this->mpLayout->getListOfMetaboliteGlyphs().size();

          for (i = 0; i < iMax; ++i)
            {
              pGO = this->mpLayout->getListOfMetaboliteGlyphs()[i];
              pBB = &pGO->getBoundingBox();
              bbx = pBB->getPosition().getX();
              bby = pBB->getPosition().getY();
              bbwidth = pBB->getDimensions().getWidth();
              bbheight = pBB->getDimensions().getHeight();

              if (x >= bbx && y >= bby && x <= (bbx + bbwidth) && y <= (bby + bbheight))
                {
                  hits.insert(pGO);
                }
            }

          iMax = this->mpLayout->getListOfReactionGlyphs().size();

          for (i = 0; i < iMax; ++i)
            {
              pRG = this->mpLayout->getListOfReactionGlyphs()[i];
              assert(pRG != NULL);

              // we have to look at all points of the curve if there is one
              if (pRG->getCurve().getNumCurveSegments() != 0)
                {
                  pCurve = &pRG->getCurve();
                  assert(pCurve != NULL);
                  kMax = pCurve->getNumCurveSegments();

                  for (k = 0; k < kMax; ++k)
                    {
                      pLS = pCurve->getSegmentAt(k);
                      assert(pLS != NULL);

                      if (isSegmentHit(pLS, x, y, toleranceRadius))
                        {
                          hits.insert(pRG);
                          break;
                        }
                    }
                }
              else
                {
                  pBB = &pRG->getBoundingBox();
                  bbx = pBB->getPosition().getX();
                  bby = pBB->getPosition().getY();
                  bbwidth = pBB->getDimensions().getWidth();
                  bbheight = pBB->getDimensions().getHeight();

                  if (x >= bbx && y >= bby && x <= (bbx + bbwidth) && y <= (bby + bbheight))
                    {
                      hits.insert(pRG);
                    }
                }

              jMax = pRG->getListOfMetabReferenceGlyphs().size();

              for (j = 0; j < jMax; ++j)
                {
                  pSRG = pRG->getListOfMetabReferenceGlyphs()[j];
                  assert(pSRG != NULL);

                  // we have to look at all points of the curve if there is one
                  if (pSRG->getCurve().getNumCurveSegments() != 0)
                    {
                      pCurve = &pSRG->getCurve();
                      assert(pCurve != NULL);
                      kMax = pCurve->getNumCurveSegments();
                      bool drawn = false;

                      for (k = 0; k < kMax && !drawn; ++k)
                        {
                          pLS = pCurve->getSegmentAt(k);

                          if (isSegmentHit(pLS, x, y, toleranceRadius))
                            {
                              hits.insert(pSRG);
                              break;
                            }
                        }
                    }
                  else
                    {
                      pBB = &pSRG->getBoundingBox();
                      bbx = pBB->getPosition().getX();
                      bby = pBB->getPosition().getY();
                      bbwidth = pBB->getDimensions().getWidth();
                      bbheight = pBB->getDimensions().getHeight();

                      if (x >= bbx && y >= bby && x <= (bbx + bbwidth) && y <= (bby + bbheight))
                        {
                          hits.insert(pSRG);
                        }
                    }
                }
            }

          iMax = this->mpLayout->getListOfTextGlyphs().size();

          for (i = 0; i < iMax; ++i)
            {
              pGO = this->mpLayout->getListOfTextGlyphs()[i];
              pBB = &pGO->getBoundingBox();
              bbx = pBB->getPosition().getX();
              bby = pBB->getPosition().getY();
              bbwidth = pBB->getDimensions().getWidth();
              bbheight = pBB->getDimensions().getHeight();

              if (x >= bbx && y >= bby && x <= (bbx + bbwidth) && y <= (bby + bbheight))
                {
                  hits.insert(pGO);
                }
            }

          iMax = this->mpLayout->getListOfGraphicalObjects().size();

          for (i = 0; i < iMax; ++i)
            {
              pGO = this->mpLayout->getListOfGraphicalObjects()[i];
              pBB = &pGO->getBoundingBox();
              bbx = pBB->getPosition().getX();
              bby = pBB->getPosition().getY();
              bbwidth = pBB->getDimensions().getWidth();
              bbheight = pBB->getDimensions().getHeight();

              if (x >= bbx && y >= bby && x <= (bbx + bbwidth) && y <= (bby + bbheight))
                {
                  hits.insert(pGO);
                }
            }
        }
    }

  return hits;
}

/**
 * This method returns all objects at the given 2D screen coordinates.
 * The depth value is ignored.
 */
std::multiset<CLGraphicalObject*, compareGraphicalObjectsBySize> CLLayoutRenderer::getObjectsAtViewportPosition(unsigned int x, unsigned int y)
{
  // first we convert the viewport position to model coordinates
  std::pair<double, double> coords = this->convert_to_model_space(x, y);
  return this->getObjectsAt(coords.first, coords.second);
}

/**
 * Calculates if the point given as x,y is close enough to the given line segment
 * to count as a hit.
 */
bool CLLayoutRenderer::isSegmentHit(const CLLineSegment* pLS, double x, double y, double toleranceRadius)
{
  bool result = false;

  if (pLS->isBezier())
    {
      // check if the point is within an extended bounding box
      double x1, x2, x3, x4, y1, y2, y3, y4;
      x1 = pLS->getStart().getX();
      x2 = pLS->getBase1().getX();
      x3 = pLS->getBase2().getX();
      x4 = pLS->getEnd().getX();
      y1 = pLS->getStart().getY();
      y2 = pLS->getBase1().getY();
      y3 = pLS->getBase2().getY();
      y4 = pLS->getEnd().getY();
      double maxX = (x1 > x2) ? x1 : x2;
      maxX = (maxX > x3) ? maxX : x3;
      maxX = (maxX > x4) ? maxX : x4;
      double maxY = (y1 > y2) ? y1 : y2;
      maxY = (maxY > y3) ? maxY : y3;
      maxY = (maxY > y4) ? maxY : y4;
      double minX = (x1 < x2) ? x1 : x2;
      minX = (minX < x3) ? minX : x3;
      minX = (minX < x4) ? minX : x4;
      double minY = (y1 < y2) ? y1 : y2;
      minY = (minY < y3) ? minY : y3;
      minY = (minY < y4) ? minY : y4;
      minX -= toleranceRadius;
      minY -= toleranceRadius;
      maxX += toleranceRadius;
      maxY += toleranceRadius;

      if (x >= minX && y >= minY && x <= maxX && y <= maxY)
        {
          // calculate points to get line segments and check each one for a hit
          GLdouble* pData = new GLdouble[3*NUM_BEZIER_POINTS];
          CLLayoutRenderer::calculate_cubicbezier(x1, y1, 0.0, x2, y2, 0.0, x3, y3, 0.0, x4, y4, 0.0, NUM_BEZIER_POINTS, pData);
          size_t i;
          double distance = 0.0;

          for (i = 1; i < NUM_BEZIER_POINTS && !result; ++i)
            {
              distance = distancePointLineSegment(x, y, pData[(i-1)*3], pData[(i-1)*3+1], pData[i*3], pData[i*3+1]);
              result = (distance == distance && distance <= toleranceRadius);
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      double distance = distancePointLineSegment(x, y, pLS->getStart().getX(), pLS->getStart().getY(), pLS->getEnd().getX(), pLS->getEnd().getY());
      result = (distance == distance && distance <= toleranceRadius);
    }

  return result;
}

double CLLayoutRenderer::distancePointLineSegment(double x, double y, double lx1, double ly1, double lx2, double ly2)
{
  double dx = lx2 - lx1;
  double dy = ly2 - ly1;
  double distance = std::numeric_limits<double>::quiet_NaN();

  if (fabs(dx) <= 1e-9)
    {
      if (fabs(dy) > 1e-9)
        {
          if (y >= ((ly1 < ly2) ? ly1 : ly2) && y <= ((ly1 > ly2) ? ly1 : ly2))
            {
              distance = fabs(lx1 - x);
            }
        }
    }
  else if (fabs(dy) <= 1e-9)
    {
      if (x >= ((lx1 < lx2) ? lx1 : lx2) && x <= ((lx1 > lx2) ? lx1 : lx2))
        {
          distance = fabs(ly1 - y);
        }
    }
  else
    {
      double slope = dy / dx;
      double invslope = -1.0 * dx / dy;
      double xCross = (-invslope * x + slope * lx1 + y - ly1) / (slope - invslope);

      if ((xCross >= ((lx1 < lx2) ? lx1 : lx2)) && (xCross <= (((lx1 > lx2) ? lx1 : lx2))))
        {
          double yCross = slope * (xCross - lx1) + ly1;

          if ((yCross >= ((ly1 < ly2) ? ly1 : ly2)) && (yCross <= (((ly1 > ly2) ? ly1 : ly2))))
            {
              distance = sqrt(pow(x - xCross, 2) + pow(y - yCross, 2));
            }
          else
            {
              if (fabs(lx1 - xCross) < fabs(lx2 - xCross))
                {
                  // the distance to lx2.ly2 is smaller
                  distance = sqrt(pow(x - lx2, 2) + pow(y - ly2, 2));
                }
              else
                {
                  distance = sqrt(pow(x - lx1, 2) + pow(y - ly1, 2));
                }
            }
        }
      else
        {
          if (fabs(lx1 - xCross) < fabs(lx2 - xCross))
            {
              // the distance to lx2.ly2 is smaller
              distance = sqrt(pow(x - lx2, 2) + pow(y - ly2, 2));
            }
          else
            {
              distance = sqrt(pow(x - lx1, 2) + pow(y - ly1, 2));
            }
        }
    }

  return distance;
}

/**
 * Calculates the bounding box of the curve by looking at all the basepoints.
 * The returned boundingbox object has to be deleted by the caller.
 */
CLBoundingBox* CLLayoutRenderer::getCurveBoundingBox(const CLCurve* pCurve)
{
#ifdef _WIN32
// windows seems to declare a macro called max which clashes with the
// call to mac from numeric limits
#undef max
#endif // _WIN32
  double xMin = std::numeric_limits<double>::max();
  double yMin = xMin;
  double xMax = -xMin;
  double yMax = xMax;
  size_t i, iMax = pCurve->getNumCurveSegments();
  const CLLineSegment* pLS = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pLS = pCurve->getSegmentAt(i);
      xMin = (xMin <= pLS->getStart().getX()) ? xMin : pLS->getStart().getX();
      yMin = (yMin <= pLS->getStart().getY()) ? yMin : pLS->getStart().getY();
      xMax = (xMax >= pLS->getStart().getX()) ? xMax : pLS->getStart().getX();
      yMax = (yMax >= pLS->getStart().getY()) ? yMax : pLS->getStart().getY();
      xMin = (xMin <= pLS->getEnd().getX()) ? xMin : pLS->getEnd().getX();
      yMin = (yMin <= pLS->getEnd().getY()) ? yMin : pLS->getEnd().getY();
      xMax = (xMax >= pLS->getEnd().getX()) ? xMax : pLS->getEnd().getX();
      yMax = (yMax >= pLS->getEnd().getY()) ? yMax : pLS->getEnd().getY();

      if (pLS->isBezier())
        {
          xMin = (xMin <= pLS->getBase1().getX()) ? xMin : pLS->getBase1().getX();
          yMin = (yMin <= pLS->getBase1().getY()) ? yMin : pLS->getBase1().getY();
          xMax = (xMax >= pLS->getBase1().getX()) ? xMax : pLS->getBase1().getX();
          yMax = (yMax >= pLS->getBase1().getY()) ? yMax : pLS->getBase1().getY();
          xMin = (xMin <= pLS->getBase2().getX()) ? xMin : pLS->getBase2().getX();
          yMin = (yMin <= pLS->getBase2().getY()) ? yMin : pLS->getBase2().getY();
          xMax = (xMax >= pLS->getBase2().getX()) ? xMax : pLS->getBase2().getX();
          yMax = (yMax >= pLS->getBase2().getY()) ? yMax : pLS->getBase2().getY();
        }
    }

  return new CLBoundingBox(CLPoint(xMin, yMin), CLDimensions(xMax - xMin, yMax - yMin));
}

/**
 * Draw the selection frame around an graphical objects bounding object box.
 * If drawHandles is true, resize handles are drawn as well,
 * else only the box is drawn.
 * If the curve is given, the basepoints of the curve are also drawn
 * as small circles.
 */
void CLLayoutRenderer::drawSelectionBox(double x, double y, double width, double height, bool /*drawHandles*/)
{
  // first we draw the actual box
  // and we use a stippled line of width 2
  // if the OpenGL implementation does not support different line width,
  // we don't care, it will probably just look better if it does.
  glPushMatrix();
  glTranslated(x - SELECTION_FRAME_WIDTH, y - SELECTION_FRAME_WIDTH, 0.0);
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(10, 0x5555);
  glLineWidth(2.0);
  // first we draw a box with a black line and line stippling
  // we have to extend the box a bit to have a small space between the object and the frame
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINE_LOOP);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(width + 2*SELECTION_FRAME_WIDTH, 0.0, 0.0);
  glVertex3d(width + 2*SELECTION_FRAME_WIDTH, height + 2*SELECTION_FRAME_WIDTH, 0.0);
  glVertex3d(0.0, height + 2*SELECTION_FRAME_WIDTH, 0.0);
  glEnd();
  // now we draw the same box again, but in white and with reversed line stippling
  glColor3f(1.0, 1.0, 1.0);
  glLineStipple(10, ~0x5555);
  glBegin(GL_LINE_LOOP);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(width + 2*SELECTION_FRAME_WIDTH, 0.0, 0.0);
  glVertex3d(width + 2*SELECTION_FRAME_WIDTH, height + 2*SELECTION_FRAME_WIDTH, 0.0);
  glVertex3d(0.0, height + 2*SELECTION_FRAME_WIDTH, 0.0);
  glEnd();
  glDisable(GL_LINE_STIPPLE);
  /*
   * For now we disable handle drawing until we make the handles functional.
  if(drawHandles == true)
  {
      // draw the handles
      // we draw 8 handles, one on each corner
      // and one on each side
      GLdouble* pArrowData=new GLdouble[3*7];
      // point 1
      pArrowData[0]=8.0;
      pArrowData[1]=3.0;
      pArrowData[2]=0.0;

      // point 2
      pArrowData[3]=0.0;
      pArrowData[4]=3.0;
      pArrowData[5]=0.0;
       // point 3
      pArrowData[6]=0.0;
      pArrowData[7]=-3.0;
      pArrowData[8]=0.0;

      // point 4
      pArrowData[9]=8.0;
      pArrowData[10]=-3.0;
      pArrowData[11]=0.0;

      // point 5
      pArrowData[12]=6.0;
      pArrowData[13]=-6.0;
      pArrowData[14]=0.0;

      // point 6
      pArrowData[15]=14.0;
      pArrowData[16]=0.0;
      pArrowData[17]=0.0;

      // point 7
      pArrowData[18]=6.0;
      pArrowData[19]=6.0;
      pArrowData[20]=0.0;

      size_t i;
      // right
      glPushMatrix();
      glTranslatef(width + 2 * SELECTION_FRAME_WIDTH + 3, (height + 2 * SELECTION_FRAME_WIDTH)/ 2.0 ,0.0);
      // white polygon
      glColor3f(1.0,1.0,1.0);
      glBegin(GL_POLYGON);
      for(i=0;i<4;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glBegin(GL_POLYGON);
      for(i=4;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glVertex3f(pArrowData[0],pArrowData[1],pArrowData[2]);
      glEnd();
      // with black border
      glColor3f(0.0,0.0,0.0);
      glBegin(GL_LINE_LOOP);
      for(i=0;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glPopMatrix();
      //
      // bottom
      glPushMatrix();
      glTranslatef((width + 2 * SELECTION_FRAME_WIDTH ) / 2.0 , height + 2 * SELECTION_FRAME_WIDTH + 3.0,0.0);
      glRotatef(90,0.0,0.0,1.0);
      // white polygon
      glColor3f(1.0,1.0,1.0);
      glBegin(GL_POLYGON);
      for(i=0;i<4;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glBegin(GL_POLYGON);
      for(i=4;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glVertex3f(pArrowData[0],pArrowData[1],pArrowData[2]);
      glEnd();
      // with black border
      glColor3f(0.0,0.0,0.0);
      glBegin(GL_LINE_LOOP);
      for(i=0;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glPopMatrix();
      //
      // left
      glPushMatrix();
      glTranslatef(- 3, (height + 2 * SELECTION_FRAME_WIDTH)/ 2.0 ,0.0);
      glRotatef(180,0.0,0.0,1.0);
      // white polygon
      glColor3f(1.0,1.0,1.0);
      glBegin(GL_POLYGON);
      for(i=0;i<4;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glBegin(GL_POLYGON);
      for(i=4;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glVertex3f(pArrowData[0],pArrowData[1],pArrowData[2]);
      glEnd();
      // with black border
      glColor3f(0.0,0.0,0.0);
      glBegin(GL_LINE_LOOP);
      for(i=0;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glPopMatrix();
      // top
      glPushMatrix();
      glTranslatef((width + 2 * SELECTION_FRAME_WIDTH) / 2.0 , -3.0,0.0);
      glRotatef(-90,0.0,0.0,1.0);
      // white polygon
      glColor3f(1.0,1.0,1.0);
      glBegin(GL_POLYGON);
      for(i=0;i<4;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glBegin(GL_POLYGON);
      for(i=4;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glVertex3f(pArrowData[0],pArrowData[1],pArrowData[2]);
      glEnd();
      // with black border
      glColor3f(0.0,0.0,0.0);
      glBegin(GL_LINE_LOOP);
      for(i=0;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glPopMatrix();

      //
      // left top corner
      glPushMatrix();
      glTranslatef(-3.0, -3.0,0.0);
      glRotatef(225,0.0,0.0,1.0);
      // white polygon
      glColor3f(1.0,1.0,1.0);
      glBegin(GL_POLYGON);
      for(i=0;i<4;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glBegin(GL_POLYGON);
      for(i=4;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glVertex3f(pArrowData[0],pArrowData[1],pArrowData[2]);
      glEnd();
      // with black border
      glColor3f(0.0,0.0,0.0);
      glBegin(GL_LINE_LOOP);
      for(i=0;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glPopMatrix();
      //
      // right top corner
      glPushMatrix();
      glTranslatef((width + 2 * SELECTION_FRAME_WIDTH) + 3.0, - 3.0,0.0);
      glRotatef(315,0.0,0.0,1.0);
      // white polygon
      glColor3f(1.0,1.0,1.0);
      glBegin(GL_POLYGON);
      for(i=0;i<4;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glBegin(GL_POLYGON);
      for(i=4;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glVertex3f(pArrowData[0],pArrowData[1],pArrowData[2]);
      glEnd();
      // with black border
      glColor3f(0.0,0.0,0.0);
      glBegin(GL_LINE_LOOP);
      for(i=0;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glPopMatrix();
      //
      // right bottom corner
      glPushMatrix();
      glTranslatef(width + 2 * SELECTION_FRAME_WIDTH + 3.0, (height + 2 * SELECTION_FRAME_WIDTH) + 3.0,0.0);
      glRotatef(45,0.0,0.0,1.0);
      // white polygon
      glColor3f(1.0,1.0,1.0);
      glBegin(GL_POLYGON);
      for(i=0;i<4;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glBegin(GL_POLYGON);
      for(i=4;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glVertex3f(pArrowData[0],pArrowData[1],pArrowData[2]);
      glEnd();
      // with black border
      glColor3f(0.0,0.0,0.0);
      glBegin(GL_LINE_LOOP);
      for(i=0;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glPopMatrix();
      //
      // left bottom corner
      glPushMatrix();
      glTranslatef(-3.0 ,(height + 2 * SELECTION_FRAME_WIDTH) + 3.0,0.0);
      glRotatef(135,0.0,0.0,1.0);
      // white polygon
      glColor3f(1.0,1.0,1.0);
      glBegin(GL_POLYGON);
      for(i=0;i<4;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glBegin(GL_POLYGON);
      for(i=4;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glVertex3f(pArrowData[0],pArrowData[1],pArrowData[2]);
      glEnd();
      // with black border
      glColor3f(0.0,0.0,0.0);
      glBegin(GL_LINE_LOOP);
      for(i=0;i<7;++i)
      {
          glVertex3f(pArrowData[i*3],pArrowData[i*3+1],pArrowData[i*3+2]);
      }
      glEnd();
      glPopMatrix();
      delete[] pArrowData;
  }
  */
  glLineWidth(1.0);
  glPopMatrix();
}

/**
 * Returns all objects that are within a given bounding box.
 */
std::vector<CLGraphicalObject*> CLLayoutRenderer::getObjectsInBoundingBox(double lx, double ly, double rx, double ry, bool partial)
{
  std::vector<CLGraphicalObject*> result;

  if (this->mpLayout)
    {
      CLGraphicalObject* pGO = NULL;
      CLReactionGlyph* pRG = NULL;
      CLMetabReferenceGlyph* pSRG = NULL;
      const CLCurve* pCurve = NULL;
      const CLLineSegment* pLS = NULL;
      const CLBoundingBox* pBB = NULL;
      size_t k, kMax;
      size_t j, jMax;
      double x, y;
      size_t i, iMax = this->mpLayout->getListOfCompartmentGlyphs().size();

      for (i = 0; i < iMax; ++i)
        {
          pGO = this->mpLayout->getListOfCompartmentGlyphs()[i];
          pBB = &pGO->getBoundingBox();
          x = pBB->getPosition().getX();
          y = pBB->getPosition().getY();

          // if the upper left is right of or below the current viewport, the
          // object is not drawn
          if (partial)
            {
              if (!(x > rx || y > ry))
                {
                  // or if the lower right is left of or above the current viewport
                  // the object is also not drawn
                  x += pBB->getDimensions().getWidth();
                  y += pBB->getDimensions().getHeight();

                  if (!(x < lx || y < ly))
                    {
                      result.push_back(pGO);
                    }
                }
            }
          else
            {
              // the object has to completly within the box
              if (x >= lx && y >= ly)
                {
                  x += pBB->getDimensions().getWidth();
                  y += pBB->getDimensions().getHeight();

                  if ((x <= rx && y <= ry))
                    {
                      result.push_back(pGO);
                    }
                }
            }
        }

      iMax = this->mpLayout->getListOfMetaboliteGlyphs().size();

      for (i = 0; i < iMax; ++i)
        {
          pGO = this->mpLayout->getListOfMetaboliteGlyphs()[i];
          pBB = &pGO->getBoundingBox();
          x = pBB->getPosition().getX();
          y = pBB->getPosition().getY();

          // if the upper left is right of or below the current viewport, the
          // object is not drawn
          if (partial)
            {
              if (!(x > rx || y > ry))
                {
                  // or if the lower right is left of or above the current viewport
                  // the object is also not drawn
                  x += pBB->getDimensions().getWidth();
                  y += pBB->getDimensions().getHeight();

                  if (!(x < lx || y < ly))
                    {
                      result.push_back(pGO);
                    }
                }
            }
          else
            {
              // the object has to completly within the box
              if (x >= lx && y >= ly)
                {
                  x += pBB->getDimensions().getWidth();
                  y += pBB->getDimensions().getHeight();

                  if ((x <= rx && y <= ry))
                    {
                      result.push_back(pGO);
                    }
                }
            }
        }

      iMax = this->mpLayout->getListOfReactionGlyphs().size();

      for (i = 0; i < iMax; ++i)
        {
          pRG = this->mpLayout->getListOfReactionGlyphs()[i];
          assert(pRG != NULL);

          // we have to look at all points of the curve if there is one
          if (pRG->getCurve().getNumCurveSegments() != 0)
            {
              pCurve = &pRG->getCurve();
              assert(pCurve != NULL);
              kMax = pCurve->getNumCurveSegments();
              bool drawn = false;

              if (!partial)
                {
                  drawn = true;
                }

              for (k = 0; k < kMax; ++k)
                {
                  pLS = pCurve->getSegmentAt(k);
                  assert(pLS != NULL);
                  x = pLS->getStart().getX();
                  y = pLS->getStart().getY();

                  if (partial)
                    {
                      // if the point is in the viewport, we draw the whole curve
                      if (x >= lx && x <= rx && y >= ly && y <= ry)
                        {
                          drawn = true;
                          break;
                        }
                    }
                  else
                    {
                      if (x < lx || y < ly || x > rx || y > ry)
                        {
                          drawn = false;
                          break;
                        }
                    }

                  x = pLS->getEnd().getX();
                  y = pLS->getEnd().getY();

                  if (partial)
                    {
                      // if the point is in the viewport, we draw the whole curve
                      if (x >= lx && x <= rx && y >= ly && y <= ry)
                        {
                          drawn = true;
                          break;
                        }
                    }
                  else
                    {
                      if (x < lx || y < ly || x > rx || y > ry)
                        {
                          drawn = false;
                          break;
                        }
                    }

                  if (pLS->isBezier())
                    {
                      x = pLS->getBase1().getX();
                      y = pLS->getBase1().getY();

                      if (partial)
                        {
                          // if the point is in the viewport, we draw the whole curve
                          if (x >= lx && x <= rx && y >= ly && y <= ry)
                            {
                              drawn = true;
                              break;
                            }
                        }
                      else
                        {
                          if (x < lx || y < ly || x > rx || y > ry)
                            {
                              drawn = false;
                              break;
                            }
                        }

                      x = pLS->getBase2().getX();
                      y = pLS->getBase2().getY();

                      if (partial)
                        {
                          // if the point is in the viewport, we draw the whole curve
                          if (x >= lx && x <= rx && y >= ly && y <= ry)
                            {
                              drawn = true;
                              break;
                            }
                        }
                      else
                        {
                          if (x < lx || y < ly || x > rx || y > ry)
                            {
                              drawn = false;
                              break;
                            }
                        }
                    }
                }

              if (drawn)
                {
                  result.push_back(pRG);
                }
            }
          else
            {
              pBB = &pRG->getBoundingBox();
              x = pBB->getPosition().getX();
              y = pBB->getPosition().getY();

              if (partial)
                {
                  // if the upper left is right of or below the current viewport, the
                  // object is not drawn
                  if (!(x > rx || y > ry))
                    {
                      // or if the lower right is left of or above the current viewport
                      // the object is also not drawn
                      x += pBB->getDimensions().getWidth();
                      y += pBB->getDimensions().getHeight();

                      if (!(x < lx || y < ly))
                        {
                          result.push_back(pRG);
                        }
                    }
                }
              else
                {
                  // the object has to completly within the box
                  if (x >= lx && y >= ly)
                    {
                      x += pBB->getDimensions().getWidth();
                      y += pBB->getDimensions().getHeight();

                      if ((x <= rx && y <= ry))
                        {
                          result.push_back(pGO);
                        }
                    }
                }
            }

          jMax = pRG->getListOfMetabReferenceGlyphs().size();

          for (j = 0; j < jMax; ++j)
            {
              pSRG = pRG->getListOfMetabReferenceGlyphs()[j];
              assert(pSRG != NULL);

              // we have to look at all points of the curve if there is one
              if (pSRG->getCurve().getNumCurveSegments() != 0)
                {
                  pCurve = &pSRG->getCurve();
                  assert(pCurve != NULL);
                  kMax = pCurve->getNumCurveSegments();
                  bool drawn = false;

                  if (!partial)
                    {
                      drawn = true;
                    }

                  for (k = 0; k < kMax; ++k)
                    {
                      pLS = pCurve->getSegmentAt(k);
                      assert(pLS != NULL);
                      x = pLS->getStart().getX();
                      y = pLS->getStart().getY();

                      if (partial)
                        {
                          // if the point is in the viewport, we draw the whole curve
                          if (x >= lx && x <= rx && y >= ly && y <= ry)
                            {
                              drawn = true;
                              break;
                            }
                        }
                      else
                        {
                          if (x < lx || y < ly || x > rx || y > ry)
                            {
                              drawn = false;
                              break;
                            }
                        }

                      x = pLS->getEnd().getX();
                      y = pLS->getEnd().getY();

                      if (partial)
                        {
                          // if the point is in the viewport, we draw the whole curve
                          if (x >= lx && x <= rx && y >= ly && y <= ry)
                            {
                              drawn = true;
                              break;
                            }
                        }
                      else
                        {
                          if (x < lx || y < ly || x > rx || y > ry)
                            {
                              drawn = false;
                              break;
                            }
                        }

                      if (pLS->isBezier())
                        {
                          x = pLS->getBase1().getX();
                          y = pLS->getBase1().getY();

                          if (partial)
                            {
                              // if the point is in the viewport, we draw the whole curve
                              if (x >= lx && x <= rx && y >= ly && y <= ry)
                                {
                                  drawn = true;
                                  break;
                                }
                            }
                          else
                            {
                              if (x < lx || y < ly || x > rx || y > ry)
                                {
                                  drawn = false;
                                  break;
                                }
                            }

                          x = pLS->getBase2().getX();
                          y = pLS->getBase2().getY();

                          // if the point is in the viewport, we draw the whole curve
                          if (partial)
                            {
                              if (x >= lx && x <= rx && y >= ly && y <= ry)
                                {
                                  drawn = true;
                                  break;
                                }
                            }
                          else
                            {
                              if (x < lx || y < ly || x > rx || y > ry)
                                {
                                  drawn = false;
                                  break;
                                }
                            }
                        }
                    }

                  if (drawn)
                    {
                      result.push_back(pSRG);
                    }
                }
              else
                {
                  pBB = &pSRG->getBoundingBox();
                  x = pBB->getPosition().getX();
                  y = pBB->getPosition().getY();

                  if (partial)
                    {
                      // if the upper left is right of or below the current viewport, the
                      // object is not drawn
                      if (!(x > rx || y > ry))
                        {
                          // or if the lower right is left of or above the current viewport
                          // the object is also not drawn
                          x += pBB->getDimensions().getWidth();
                          y += pBB->getDimensions().getHeight();

                          if (!(x < lx || y < ly))
                            {
                              result.push_back(pSRG);
                            }
                        }
                    }
                  else
                    {
                      // the object has to completly within the box
                      if (x >= lx && y >= ly)
                        {
                          x += pBB->getDimensions().getWidth();
                          y += pBB->getDimensions().getHeight();

                          if ((x <= rx && y <= ry))
                            {
                              result.push_back(pGO);
                            }
                        }
                    }
                }
            }
        }

      iMax = this->mpLayout->getListOfTextGlyphs().size();

      for (i = 0; i < iMax; ++i)
        {
          pGO = this->mpLayout->getListOfTextGlyphs()[i];
          pBB = &pGO->getBoundingBox();
          x = pBB->getPosition().getX();
          y = pBB->getPosition().getY();

          // if the upper left is right of or below the current viewport, the
          // object is not drawn
          if (partial)
            {
              if (!(x > rx || y > ry))
                {
                  // or if the lower right is left of or above the current viewport
                  // the object is also not drawn
                  x += pBB->getDimensions().getWidth();
                  y += pBB->getDimensions().getHeight();

                  if (!(x < lx || y < ly))
                    {
                      result.push_back(pGO);
                    }
                }
            }
          else
            {
              // the object has to completly within the box
              if (x >= lx && y >= ly)
                {
                  x += pBB->getDimensions().getWidth();
                  y += pBB->getDimensions().getHeight();

                  if ((x <= rx && y <= ry))
                    {
                      result.push_back(pGO);
                    }
                }
            }
        }

      iMax = this->mpLayout->getListOfGraphicalObjects().size();

      for (i = 0; i < iMax; ++i)
        {
          pGO = this->mpLayout->getListOfGraphicalObjects()[i];
          pBB = &pGO->getBoundingBox();
          x = pBB->getPosition().getX();
          y = pBB->getPosition().getY();

          if (partial)
            {
              // if the upper left is right of or below the current viewport, the
              // object is not drawn
              if (!(x > rx || y > ry))
                {
                  // or if the lower right is left of or above the current viewport
                  // the object is also not drawn
                  x += pBB->getDimensions().getWidth();
                  y += pBB->getDimensions().getHeight();

                  if (!(x < lx || y < ly))
                    {
                      result.push_back(pGO);
                    }
                }
            }
          else
            {
              // the object has to completly within the box
              if (x >= lx && y >= ly)
                {
                  x += pBB->getDimensions().getWidth();
                  y += pBB->getDimensions().getHeight();

                  if ((x <= rx && y <= ry))
                    {
                      result.push_back(pGO);
                    }
                }
            }
        }
    }

  return result;
}

/**
 * Sets the current selection box.
 * Setting the Box to NULL means that no selection box is drawn.
 */
void CLLayoutRenderer::setSelectionBox(const CLBoundingBox* pBox)
{
  if (this->mpSelectionBox != NULL)
    {
      delete this->mpSelectionBox;
    }

  if (pBox == NULL)
    {
      this->mpSelectionBox = NULL;
    }
  else
    {
      this->mpSelectionBox = new CLBoundingBox(*pBox);
    }
}

/**
 * returns a point to the current selection box.
 */
CLBoundingBox* CLLayoutRenderer::getSelectionBox()
{
  return this->mpSelectionBox;
}

/**
 * returns a const point to the current selection box.
 */
const CLBoundingBox* CLLayoutRenderer::getSelectionBox() const
{
  return this->mpSelectionBox;
}

/**
 * draws the selection box if there is one
 */
void CLLayoutRenderer::draw_selection_box() const
{
  if (this->mpSelectionBox != NULL)
    {
      // draw four semi transparent rectangles around the
      // bounding box
      double width = this->mW / this->mZoomFactor;
      double height = this->mH / this->mZoomFactor;
      double lx = this->mpSelectionBox->getPosition().getX();
      double ly = this->mpSelectionBox->getPosition().getY();
      double rx = lx + this->mpSelectionBox->getDimensions().getWidth();
      double ry = ly + this->mpSelectionBox->getDimensions().getHeight();
      glColor4f(0.5, 0.5, 0.5, 0.5);
      // top
      glBegin(GL_POLYGON);
      glVertex3d(this->mX, this->mY, 0.1);
      glVertex3d(this->mX + width, this->mY, 0.1);
      glVertex3d(this->mX + width, ly, 0.1);
      glVertex3d(this->mX, ly, 0.1);
      glEnd();
      // bottom
      glBegin(GL_POLYGON);
      glVertex3d(this->mX, ry, 0.1);
      glVertex3d(this->mX + width, ry, 0.1);
      glVertex3d(this->mX + width, this->mY + height, 0.1);
      glVertex3d(this->mX, this->mY + height, 0.1);
      glEnd();
      // left
      glBegin(GL_POLYGON);
      glVertex3d(this->mX, ly, 0.1);
      glVertex3d(lx, ly, 0.1);
      glVertex3d(lx, ry, 0.1);
      glVertex3d(this->mX, ry, 0.1);
      glEnd();
      // right
      glBegin(GL_POLYGON);
      glVertex3d(rx, ly, 0.1);
      glVertex3d(this->mX + width, ly, 0.1);
      glVertex3d(this->mX + width, ry, 0.1);
      glVertex3d(rx, ry, 0.1);
      glEnd();
    }
}

/**
 * converts the given coordinates from viewport space into model space.
 */
std::pair<double, double> CLLayoutRenderer::convert_to_model_space(double x, double y) const
{
  double modelX = this->mX + (double)x / this->mZoomFactor;
  double modelY = this->mY + (double)y / this->mZoomFactor;
  return std::pair<double, double>(modelX, modelY);
}

/**
 * Updates the associations of species reference glyphs
 * and text glyphs.
 */
void CLLayoutRenderer::update_associations()
{
  mTextGlyphToGraphicalObjectMap.clear();
  mTextGlyphToGraphicalObjectMap.clear();
  // maps that store the associations for species reference glyphs
  mSpeciesReferenceToSpeciesMap.clear();
  mSpeciesToSpeciesReferenceMap.clear();
  mSpeciesReferenceToReactionMap.clear();
  mReactionToSpeciesReferenceMap.clear();

  std::map<std::string, CLGraphicalObject*> idMap;

  if (this->mpLayout)
    {
      // first we have to create a map that specifies for each speciesreference with an id
      // whether it is a modifier or not
      size_t j, jMax;
      size_t i, iMax = this->mpModel->getReactions().size();
      const CReaction* pReaction = NULL;
      std::map<std::string, bool> modifierMap;

      for (i = 0; i < iMax; ++i)
        {
          pReaction = this->mpModel->getReactions()[i];
          jMax = pReaction->getChemEq().getSubstrates().size();

          for (j = 0; j < jMax; ++j)
            {
              modifierMap[pReaction->getChemEq().getSubstrates()[j]->getKey()] = false;
            }

          jMax = pReaction->getChemEq().getProducts().size();

          for (j = 0; j < jMax; ++j)
            {
              modifierMap[pReaction->getChemEq().getProducts()[j]->getKey()] = false;
            }

          jMax = pReaction->getChemEq().getModifiers().size();

          for (j = 0; j < jMax; ++j)
            {
              modifierMap[pReaction->getChemEq().getModifiers()[j]->getKey()] = true;
            }
        }

      // remove the empty string again in case a species reference did not have an id
      std::map<std::string, bool>::iterator pos = modifierMap.find("");

      if (pos != modifierMap.end())
        {
          modifierMap.erase(pos);
        }

      CLGraphicalObject* pGO = NULL;
      CLReactionGlyph* pRG = NULL;
      CLMetabReferenceGlyph* pSRG = NULL;
      iMax = this->mpLayout->getListOfCompartmentGlyphs().size();

      for (i = 0; i < iMax; ++i)
        {
          pGO = this->mpLayout->getListOfCompartmentGlyphs()[i];
          idMap[pGO->getKey()] = pGO;
        }

      iMax = this->mpLayout->getListOfMetaboliteGlyphs().size();

      for (i = 0; i < iMax; ++i)
        {
          pGO = this->mpLayout->getListOfMetaboliteGlyphs()[i];
          idMap[pGO->getKey()] = pGO;
        }

      iMax = this->mpLayout->getListOfReactionGlyphs().size();

      for (i = 0; i < iMax; ++i)
        {
          pRG = this->mpLayout->getListOfReactionGlyphs()[i];
          idMap[pRG->getKey()] = pRG;
          this->mReactionToSpeciesReferenceMap[pRG] = std::set<std::pair<CLMetabReferenceGlyph*, bool> >();
          jMax = pRG->getListOfMetabReferenceGlyphs().size();

          for (j = 0; j < jMax; ++j)
            {
              pSRG = pRG->getListOfMetabReferenceGlyphs()[j];
              assert(pSRG != NULL);
              idMap[pSRG->getKey()] = pSRG;
              bool modifier = false;

              if (!pSRG->getMetabGlyphKey().empty())
                {
                  // we have to find out if this species reference represents a modifier or not
                  if (!pSRG->getModelObjectKey().empty())
                    {
                      if (modifierMap.find(pSRG->getModelObjectKey()) != modifierMap.end())
                        {
                          modifier = modifierMap[pSRG->getModelObjectKey()];
                        }
                    }

                  this->mReactionToSpeciesReferenceMap[pRG].insert(std::pair<CLMetabReferenceGlyph*, bool>(pSRG, modifier));
                  std::map<std::string, CLGraphicalObject*>::iterator pos = idMap.find(pSRG->getMetabGlyphKey());

                  if (pos != idMap.end())
                    {
                      CLMetabGlyph* pSG = dynamic_cast<CLMetabGlyph*>(pos->second);
                      assert(pSG != NULL);
                      this->mSpeciesReferenceToSpeciesMap[pSRG] = std::pair<CLMetabGlyph*, bool>(pSG, modifier);
                      std::map<CLMetabGlyph*, std::set<std::pair<CLMetabReferenceGlyph*, bool> > >::iterator pos2 = this->mSpeciesToSpeciesReferenceMap.find(pSG);

                      if (pos2 == this->mSpeciesToSpeciesReferenceMap.end())
                        {
                          this->mSpeciesToSpeciesReferenceMap[pSG] = std::set<std::pair<CLMetabReferenceGlyph*, bool> >();
                        }

                      this->mSpeciesToSpeciesReferenceMap[pSG].insert(std::pair<CLMetabReferenceGlyph*, bool>(pSRG, modifier));
                    }
                  else
                    {
                      std::cerr << "Error. species glyph with id \"" << pSRG->getMetabGlyphKey() << "\" referenced in species reference glyph \"" << pSRG->getKey() << "\", but no species glyph with that id exists." << std::endl;
                    }
                }
              else
                {
                  // now we check if one end of the species reference curve is on top of one endpoint of the reaction
                  // if not, we assume it is a modifier
                  // if yes, we check which end it is that hits the reaction and set the modifier flag accordingly
                  if (pSRG->getCurve().getNumCurveSegments() != 0 && pRG->getCurve().getNumCurveSegments() != 0)
                    {
                      const CLPoint* pSRGFirstPoint = &pSRG->getCurve().getSegmentAt(0)->getStart();
                      const CLPoint* pSRGLastPoint = &pSRG->getCurve().getSegmentAt(pSRG->getCurve().getNumCurveSegments() - 1)->getEnd();
                      const CLPoint* pRGFirstPoint = &pRG->getCurve().getSegmentAt(0)->getStart();
                      const CLPoint* pRGLastPoint = &pRG->getCurve().getSegmentAt(pRG->getCurve().getNumCurveSegments() - 1)->getEnd();

                      if (distance(*pSRGFirstPoint, *pRGFirstPoint) < 1e-9)
                        {
                          // it probably is a substrate
                          modifier = false;
                        }
                      else if (distance(*pSRGFirstPoint, *pRGLastPoint) < 1e-9)
                        {
                          // it probably is a product
                          modifier = false;
                        }
                      else if (distance(*pSRGLastPoint, *pRGFirstPoint) < 1e-9)
                        {
                          // it probably is a substrate pointing the wrong direction
                          modifier = true;
                        }
                      else if (distance(*pSRGLastPoint, *pRGLastPoint) < 1e-9)
                        {
                          // it probably is a product pointing the wrong direction
                          modifier = true;
                        }
                      else
                        {
                          // it probably is a modifier, but we still don't know whether it is pointing in the right direction
                          // for now we just assume it is
                          modifier = true;
                        }
                    }

                  this->mReactionToSpeciesReferenceMap[pRG].insert(std::pair<CLMetabReferenceGlyph*, bool>(pSRG, modifier));
                }

              this->mSpeciesReferenceToReactionMap[pSRG] = std::pair<CLReactionGlyph*, bool>(pRG, modifier);
            }
        }

      iMax = this->mpLayout->getListOfGraphicalObjects().size();

      for (i = 0; i < iMax; ++i)
        {
          pGO = this->mpLayout->getListOfGraphicalObjects()[i];
          idMap[pGO->getKey()] = pGO;
        }

      iMax = this->mpLayout->getListOfTextGlyphs().size();

      for (i = 0; i < iMax; ++i)
        {
          pGO = this->mpLayout->getListOfTextGlyphs()[i];
          idMap[pGO->getKey()] = pGO;
        }

      CLTextGlyph* pTG = NULL;

      for (i = 0; i < iMax; ++i)
        {
          pTG = this->mpLayout->getListOfTextGlyphs()[i];

          if (!pTG->getGraphicalObjectKey().empty())
            {
              if (pTG->getGraphicalObjectKey() == pTG->getKey())
                {
                  std::cerr << "Error. CLText* glyph \"" << pTG->getKey() << "\" is referencing itself." << std::endl;
                }

              std::map<std::string, CLGraphicalObject*>::iterator pos = idMap.find(pTG->getGraphicalObjectKey());

              if (pos != idMap.end())
                {
                  mTextGlyphToGraphicalObjectMap[pTG] = pos->second;

                  if (this->mGraphicalObjectToTextGlyphMap.find(pos->second) == this->mGraphicalObjectToTextGlyphMap.end())
                    {
                      this->mGraphicalObjectToTextGlyphMap[pos->second] = std::set<CLTextGlyph*>();
                    }

                  this->mGraphicalObjectToTextGlyphMap[pos->second].insert(pTG);
                }
              else
                {
                  std::cerr << "Error. Layout object with id \"" << pTG->getGraphicalObjectKey() << "\" referenced from text glyph does not exist." << std::endl;
                }
            }
        }
    }
}

/**
 * Moves a given graphical object by a given vector.
 */
void CLLayoutRenderer::move_graphical_object(CLGraphicalObject* pObject, double dx, double dy)
{
  pObject->getBoundingBox().getPosition().setX(pObject->getBoundingBox().getPosition().getX() + dx);
  pObject->getBoundingBox().getPosition().setY(pObject->getBoundingBox().getPosition().getY() + dy);
}

/**
 * Moves a given curve object by a given vector.
 * Optionally the method can leave the start and/or the
 * endpoint of the curve where it is.
 */
void CLLayoutRenderer::move_curve_object(CLCurve* pCurve, double dx, double dy, bool leaveStartPoint, bool leaveEndpoint)
{
  size_t i, iMax = pCurve->getNumCurveSegments();
  CLLineSegment* pLS = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pLS = pCurve->getSegmentAt(i);

      if (i != 0 || (i == 0 && !leaveStartPoint))
        {
          pLS->getStart().setX(pLS->getStart().getX() + dx);
          pLS->getStart().setY(pLS->getStart().getY() + dy);
        }

      if (i != iMax || (i == iMax - 1 && !leaveEndpoint))
        {
          pLS->getEnd().setX(pLS->getEnd().getX() + dx);
          pLS->getEnd().setY(pLS->getEnd().getY() + dy);
        }

      if (pLS->isBezier())
        {
          pLS->getBase1().setX(pLS->getBase1().getX() + dx);
          pLS->getBase1().setY(pLS->getBase1().getY() + dy);
          pLS->getBase2().setX(pLS->getBase2().getX() + dx);
          pLS->getBase2().setY(pLS->getBase2().getY() + dy);
        }
    }
}

/**
 * Moves the given Species glyph by the given vector.
 * The endpoints of all associated species reference glyphs are moved as well
 * if they are represented by curves.
 * Also all associated text glyphs are moved.
 */
void CLLayoutRenderer::move_species_glyph(CLMetabGlyph* pSG, double dx, double dy, bool moveSelectedAssociations)
{
  move_graphical_object(pSG, dx, dy);
  std::set<std::pair<CLMetabReferenceGlyph*, bool> >& specrefs = this->mSpeciesToSpeciesReferenceMap[pSG];
  std::set<std::pair<CLMetabReferenceGlyph*, bool> >::iterator it = specrefs.begin(), endit = specrefs.end();

  while (it != endit)
    {
      if (moveSelectedAssociations == true || this->mSelection.find(it->first) == this->mSelection.end())
        {
          if (it->first->getCurve().getNumCurveSegments() != 0)
            {
              if (it->second == false)
                {
                  CLLineSegment* pLS = it->first->getCurve().getSegmentAt(it->first->getCurve().getNumCurveSegments() - 1);
                  assert(pLS != NULL);
                  pLS->getEnd().setX(pLS->getEnd().getX() + dx);
                  pLS->getEnd().setY(pLS->getEnd().getY() + dy);
                }
              else
                {
                  CLLineSegment* pLS = it->first->getCurve().getSegmentAt(0);
                  assert(pLS != NULL);
                  pLS->getStart().setX(pLS->getStart().getX() + dx);
                  pLS->getStart().setY(pLS->getStart().getY() + dy);
                }
            }
        }

      ++it;
    }

  std::set<CLTextGlyph*>& tgs = this->mGraphicalObjectToTextGlyphMap[pSG];
  std::set<CLTextGlyph*>::iterator it2 = tgs.begin(), endit2 = tgs.end();

  while (it2 != endit2)
    {
      if (moveSelectedAssociations == true || this->mSelection.find(*it2) == this->mSelection.end())
        {
          move_graphical_object(*it2, dx, dy);
        }

      ++it2;
    }
}

/**
 * Moves the given reaction glyph by the given vector.
 * The startpoints of all associated species reference glyphs are moved as well
 * if they are represented by curves otherwise the comple species reference glyph
 * is moved.
 * Also all associated text glyphs are moved.
 */
void CLLayoutRenderer::move_reaction_glyph(CLReactionGlyph* pRG, double dx, double dy, bool moveSelectedAssociations)
{
  if (pRG->getCurve().getNumCurveSegments() != 0)
    {
      move_curve_object(&pRG->getCurve(), dx, dy);
    }
  else
    {
      move_graphical_object(pRG, dx, dy);
    }

  std::set<std::pair<CLMetabReferenceGlyph*, bool> >& specrefs = this->mReactionToSpeciesReferenceMap[pRG];
  std::set<std::pair<CLMetabReferenceGlyph*, bool> >::iterator it = specrefs.begin(), endit = specrefs.end();

  while (it != endit)
    {
      if (moveSelectedAssociations == true || this->mSelection.find(it->first) == this->mSelection.end())
        {
          if (it->first->getCurve().getNumCurveSegments() != 0)
            {
              if (it->second == false)
                {
                  CLLineSegment* pLS = it->first->getCurve().getSegmentAt(0);
                  assert(pLS != NULL);
                  pLS->getStart().setX(pLS->getStart().getX() + dx);
                  pLS->getStart().setY(pLS->getStart().getY() + dy);
                }
              else
                {
                  CLLineSegment* pLS = it->first->getCurve().getSegmentAt(it->first->getCurve().getNumCurveSegments() - 1);
                  assert(pLS != NULL);
                  pLS->getEnd().setX(pLS->getEnd().getX() + dx);
                  pLS->getEnd().setY(pLS->getEnd().getY() + dy);
                }
            }
          else
            {
              move_graphical_object(it->first, dx, dy);
            }
        }

      ++it;
    }

  std::set<CLTextGlyph*>& tgs = this->mGraphicalObjectToTextGlyphMap[pRG];
  std::set<CLTextGlyph*>::iterator it2 = tgs.begin(), endit2 = tgs.end();

  while (it2 != endit2)
    {
      if (moveSelectedAssociations == true || this->mSelection.find(*it2) == this->mSelection.end())
        {
          move_graphical_object(*it2, dx, dy);
        }

      ++it2;
    }
}

/**
 * Moves the given text glyph by the given vector.
 * For now, we do not move any associated object becuase it is difficult to
 * create a behaviour that makes sense. E.g. if the associated object is a species
 * glyph, all species reference glyphs might have to be moved.
 * So for now, it is easier to only move the text and if the user wants to move the text
 * with the associated object, he/she needs to move the object instead.
 */
void CLLayoutRenderer::move_text_glyph(CLTextGlyph* pTG, double dx, double dy)
{
  move_graphical_object(pTG, dx, dy);
}

/**
 * Moves the species reference glyph.
 * If the glpyh is represented by a curve,
 * the curves start and endpoint are left as they are.
 */
void CLLayoutRenderer::move_species_reference_glyph(CLMetabReferenceGlyph* pSRG, double dx, double dy)
{
  if (pSRG->getCurve().getNumCurveSegments() != 0)
    {
      move_curve_object(&pSRG->getCurve(), dx, dy, true, true);
    }
  else
    {
      move_graphical_object(pSRG, dx, dy);
    }
}

/**
 * Moves the current selection.
 * If the moveAssociations falg is set to true,
 * associated objects that are not selected are
 * moved as well.
 * In the case of associated species reference glyphs
 * this means that the start and/or endpoint is moved.
 */
void CLLayoutRenderer::move_selection(double dx, double dy, bool moveAssociated)
{
  std::set<CLGraphicalObject*>::iterator it = this->mSelection.begin(), endit = this->mSelection.end();
  CLMetabGlyph* pSG = NULL;
  CLReactionGlyph* pRG = NULL;
  CLTextGlyph* pTG = NULL;
  CLMetabReferenceGlyph* pSRG = NULL;

  while (it != endit)
    {
      pSG = dynamic_cast<CLMetabGlyph*>(*it);

      if (pSG != NULL)
        {
          if (moveAssociated == true)
            {
              move_species_glyph(pSG, dx, dy, false);
            }
          else
            {
              move_graphical_object(*it, dx, dy);
            }
        }
      else
        {
          pTG = dynamic_cast<CLTextGlyph*>(*it);

          if (pTG != NULL)
            {
              if (moveAssociated == true)
                {
                  move_text_glyph(pTG, dx, dy);
                }
              else
                {
                  move_graphical_object(*it, dx, dy);
                }
            }
          else
            {
              pSRG = dynamic_cast<CLMetabReferenceGlyph*>(*it);

              if (pSRG != NULL)
                {
                  if (moveAssociated == true)
                    {
                      move_species_reference_glyph(pSRG, dx, dy);
                    }
                  else
                    {
                      if (pSRG->getCurve().getNumCurveSegments() != 0)
                        {
                          move_curve_object(&pSRG->getCurve(), dx, dy, false, false);
                        }
                      else
                        {
                          move_graphical_object(*it, dx, dy);
                        }
                    }
                }
              else
                {
                  pRG = dynamic_cast<CLReactionGlyph*>(*it);

                  if (pRG != NULL)
                    {
                      if (moveAssociated == true)
                        {
                          move_reaction_glyph(pRG, dx, dy, false);
                        }
                      else
                        {
                          if (pRG->getCurve().getNumCurveSegments() != 0)
                            {
                              move_curve_object(&pRG->getCurve(), dx, dx, false, false);
                            }
                          else
                            {
                              move_graphical_object(*it, dx, dy);
                            }
                        }
                    }
                  else
                    {
                      move_graphical_object(*it, dx, dy);
                    }
                }
            }
        }

      ++it;
    }
}

/**
 * reverts the direction of the given curve.
 * The result is returned as a new curve object and
 * the caller has to make sure that the memory for the
 * new curve is freed.
 */
CLCurve* CLLayoutRenderer::revert_curve(const CLCurve* pCurve)
{
  CLCurve* pC = new CLCurve();
  size_t i, iMax = pCurve->getNumCurveSegments();
  const CLLineSegment* pLS = NULL;
  CLLineSegment* pNewLS = NULL;

  for (i = iMax; i > 0; --i)
    {
      pLS = pCurve->getSegmentAt(i - 1);
      pNewLS = new CLLineSegment(pLS->getEnd(), pLS->getStart());

      if (pLS->isBezier())
        {
          // revert the two basepoints
          pNewLS->setBase1(pLS->getBase2());
          pNewLS->setBase2(pLS->getBase1());
          pNewLS->setIsBezier(true);
        }

      pC->addCurveSegment(pNewLS);
      delete pNewLS;
    }

  return pC;
}

/**
 * calculates the distance between two layout points.
 */
double CLLayoutRenderer::distance(const CLPoint& p1, const CLPoint& p2)
{
  return sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
}

/**
 * Returns the current aspect.
 */
double CLLayoutRenderer::getAspect() const
{
  return this->mAspect;
}

/**
 * Sets the aspect.
 */
void CLLayoutRenderer::setAspect(double aspect)
{
  this->mAspect = aspect;
}

/**
 * Sets the class that can create textures from a given image file.
 */
void CLLayoutRenderer::setImageTexturizer(CLImageTexturizer* pTexturizer)
{
  this->mpImageTexturizer = pTexturizer;
}

#ifdef COPASI_DEBUG

/**
 * Sets the list of model objects that are to be highlighted in the diagram.
 */
void CLLayoutRenderer::setHighlightedModelObjects(const std::set<const CCopasiObject*>& highlightedObjects)
{
  this->mHighlightedModelObjects = highlightedObjects;
}

/**
 * Returns a const reference to the set of highlighted model objects.
 */
const std::set<const CCopasiObject*>& CLLayoutRenderer::getHighlightedModelObjects() const
{
  return this->mHighlightedModelObjects;
}

/**
 * Returns a reference to the set of highlighted model objects.
 */
std::set<const CCopasiObject*>& CLLayoutRenderer::getHighlightedModelObjects()
{
  return this->mHighlightedModelObjects;
}


/**
 * Sets the highlight color.
 */
void CLLayoutRenderer::setHighlightColor(const GLfloat c[4])
{
  this->mHighlightColor[0] = c[0];
  this->mHighlightColor[1] = c[1];
  this->mHighlightColor[2] = c[2];
  this->mHighlightColor[3] = c[3];
}

/**
 * Returns a const pointer to the highlight color.
 * The array has a size of 4 elements.
 */
const GLfloat* CLLayoutRenderer::getHighlightColor() const
{
  return this->mHighlightColor;
}

/**
 * Sets the fog color.
 */
void CLLayoutRenderer::setFogColor(const GLfloat c[4])
{
  this->mFogColor[0] = c[0];
  this->mFogColor[1] = c[1];
  this->mFogColor[2] = c[2];
  this->mFogColor[3] = c[3];
}

/**
 * Returns a const pointer to the fog color.
 * The array has a size of 4 elements.
 */
const GLfloat* CLLayoutRenderer::getFogColor() const
{
  return this->mFogColor;
}


/**
 * Toggles the flag that determines if highlighted objects
 * are actually highlighted or if the rest is fogged out.
 */
void CLLayoutRenderer::toggleHighlightFlag()
{
  this->mHighlight = !this->mHighlight;
}

/**
 * Toggles the flag that determines if highlighted objects
 * are actually highlighted or if the rest is fogged out.
 */
void CLLayoutRenderer::setHighlightFlag(bool flag)
{
  this->mHighlight = flag;
}

/**
 * Returns the highlight flag.
 */
bool CLLayoutRenderer::getHighlightFlag() const
{
  return this->mHighlight;
}

/**
 * On non apple systems, we need to get the pointers to extension functions.
 */
void CLLayoutRenderer::initialize_gl_extension_functions()
{
  const char* extensionsString = (const char*)glGetString(GL_EXTENSIONS);

  if (extensionsString == NULL) return;

  // TODO this method of testing if the extension is supported is not very safe, we should check if there is
  // a whitespace character or npos after the position
  if (std::string(extensionsString).find("GL_EXT_fog_coord") == std::string::npos) return;

#ifdef _WIN32
  mpGlFogCoordfEXT = (void(*)(GLfloat)) wglGetProcAddress("glFogCoordfEXT");
#else
#ifdef __APPLE__
  mpGlFogCoordfEXT = (void(*)(GLfloat)) MyNSGLGetProcAddress("glFogCoordfEXT");
#else
  mpGlFogCoordfEXT = (void(*)(GLfloat)) glXGetProcAddressARB((const GLubyte*)"glFogCoordfEXT");
#endif // __APPLE__
#endif // _WIN32
  mGLFunctionsInitialized = true;
}

#ifdef __APPLE__
void * CLLayoutRenderer::MyNSGLGetProcAddress(const char *name)
{
  NSSymbol symbol;
  char *symbolName;
  symbolName = (char*)malloc(strlen(name) + 2);

  strcpy(symbolName + 1, name);

  symbolName[0] = '_';
  symbol = NULL;

//  if (NSIsSymbolNameDefined(symbolName))
  {
    const struct mach_header* header = NSAddImage("/System/Library/Frameworks/OpenGL.framework/Versions/A/OpenGL", NSADDIMAGE_OPTION_RETURN_ON_ERROR);
    // we should always find the OpenGL library
    assert(header != NULL);
    symbol = NSLookupSymbolInImage(header, symbolName, NSLOOKUPSYMBOLINIMAGE_OPTION_BIND | NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR);
    //symbol = NSLookupAndBindSymbol(symbolName);
  }

  free(symbolName);

  return symbol ? NSAddressOfSymbol(symbol) : NULL;
}
#endif // __APPLE__

#endif // COPASI_DEBUG


