// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#ifdef WIN32
# ifndef _USE_MATH_DEFINES
# define _USE_MATH_DEFINES 1
# endif // _USE_MATH_DEFINES
#endif

#include <QtCore/QCoreApplication>
#include <QtCore/QEvent>
#include <QtCore/QFileInfo>
#include <QtCore/QList>
#include <QtCore/QPoint>
#include <QtCore/QRect>
#include <QtCore/QSize>
#include <QtCore/QString>
#include <QtCore/QTimer>

#include <QAction>
#include <QBitmap>
#include <QContextMenuEvent>
#include <QFontDatabase>
#include <QFontInfo>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QProgressDialog>
#include <QtOpenGL/QGLFramebufferObject>

#include <cmath>
#include <iostream>
#include <limits>
#include <utility>

#include "copasi/copasi.h"
#include "copasi/output/COutputHandler.h"

#include "FontChooser.h"

#if (defined WIN32 && !defined log2 && _MSC_VER < 1900)
C_FLOAT64 log2(const C_FLOAT64 __x)
{return log(__x) / M_LN2;}
#endif // WIN32

#include "CQGLNetworkPainter.h"
#include "CQLayoutMainWindow.h"

#include "copasi/core/CRootContainer.h"
#include "CQNewMainWindow.h"
#include "copasi/UI/qtUtilities.h"
#include "copasi/layout/CLayout.h"
#include "copasi/core/CDataVector.h"
#include "copasi/layoutUI/CVisParameters.h"
#include "copasi/layoutUI/CDataEntity.h"
#include "copasi/layoutUI/BezierCurve.h"

#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

// TODO check why the arrow heads are off when switching back from size
// animation to rectangular view
//
// TODO implement the possibility to make screenshots of the visible area as
// well as the whole network and let the user choose the resolution
//
// TODO improve zooming (no clue how to do that best)
//
// TODO fix arrow positioning problems in size animation

// TODO change the text rendering or the texture creation. Right now it seems
// to work reasonably well, but it could be improved since the text is
// sometimes longer or higher than reported by Qt.

// below species and speciesreference
const float CQGLNetworkPainter::COMPARTMENT_DEPTH = 0.001f;
const float CQGLNetworkPainter::COMPARTMENT_SHADOW_DEPTH = 0.0009f;
const float CQGLNetworkPainter::COMPARTMENT_FRAME_DEPTH = 0.0011f;

const float CQGLNetworkPainter::SPECIES_DEPTH = 0.005f;
const float CQGLNetworkPainter::SPECIES_SHADOW_DEPTH = 0.0049f;
const float CQGLNetworkPainter::SPECIES_FRAME_DEPTH = 0.0051f;

//below species
const float CQGLNetworkPainter::SPECIESREFERENCE_DEPTH = 0.003f;

const GLfloat CQGLNetworkPainter::MIRROR_X[] =
{
  1.0f, 0.0f, 0.0f, 0.0f
  , 0.0f, -1.0f, 0.0f, 0.0f
  , 0.0f, 0.0f, 1.0f, 0.0f
  , 0.0f, 0.0f, 0.0f, 1.0f
};

const GLfloat CQGLNetworkPainter::MIRROR_Y[] =
{
  -1.0f, 0.0f, 0.0f, 0.0f
    , 0.0f, 1.0f, 0.0f, 0.0f
    , 0.0f, 0.0f, 1.0f, 0.0f
    , 0.0f, 0.0f, 0.0f, 1.0f
  };

const C_INT32 CQGLNetworkPainter::MIN_HEIGHT = 10;

CQGLNetworkPainter::CQGLNetworkPainter(const QGLFormat &format, QWidget *parent)
  : QGLWidget(format, parent),
    mIsInitialized(false)
{
  initializeGraphPainter(parent);
}

CQGLNetworkPainter::~CQGLNetworkPainter()
{
  std::map< std::string, CCompartmentGraphNode * >::iterator itComp = compartmentNodeMap.begin();
  std::map< std::string, CCompartmentGraphNode * >::iterator endComp = compartmentNodeMap.end();

  for (; itComp != endComp; ++itComp)
    {
      pdelete(itComp->second);
    }

  std::map<std::string, RGTextureSpec *>::iterator it = labelTextureMap.begin(), endit = labelTextureMap.end();

  while (it != endit)
    {
      delete[] it->second->textureData;
      delete it->second;
      ++it;
    }

  // delete the node display list
  glDeleteLists(this->mDisplayLists, 17);
}

void CQGLNetworkPainter::initializeDisplayLists()
{
  glClearColor(mBackgroundColor[0], mBackgroundColor[1], mBackgroundColor[2], mBackgroundColor[3]);
  // convert the node into a display list that is created once and call once
  // for each node.
  // this might safe some cpu cycles, especially when the nodes get more fancy.
  this->mDisplayLists = glGenLists(17);
  // this list is for the rectangular nodes
  GLfloat compartmentColor_080[] = {mCompartmentColor[0] + (1.0f - mCompartmentColor[0]) * 0.8f, mCompartmentColor[1] + (1.0f - mCompartmentColor[1]) * 0.8f, mCompartmentColor[2] + (1.0f - mCompartmentColor[2]) * 0.8f};
  GLfloat speciesColor_080[] = {mSpeciesColor[0] + (1.0f - mSpeciesColor[0]) * 0.8f, mSpeciesColor[1] + (1.0f - mSpeciesColor[1]) * 0.8f, mSpeciesColor[2] + (1.0f - mSpeciesColor[2]) * 0.8f};
  glNewList(mDisplayLists, GL_COMPILE);
  // approximate a quarter circle by a triangle fan with 3 triangles
  glBegin(GL_TRIANGLE_FAN);
  glColor3fv(compartmentColor_080);
  glVertex3f(0.0f, 0.4f, COMPARTMENT_DEPTH);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(0.0f, 0.5f, COMPARTMENT_DEPTH);
  glColor3f(mCompartmentColor[0] + (1.0f - mCompartmentColor[0]) * 0.9f, mCompartmentColor[1] + (1.0f - mCompartmentColor[1]) * 0.9f, mCompartmentColor[2] + (1.0f - mCompartmentColor[2]) * 0.9f); // 90% value
  glVertex3f(0.05f, 0.4866f, COMPARTMENT_DEPTH);
  glColor3f(mCompartmentColor[0] + (1.0f - mCompartmentColor[0]) * 0.973f, mCompartmentColor[1] + (1.0f - mCompartmentColor[1]) * 0.973f, mCompartmentColor[2] + (1.0f - mCompartmentColor[2]) * 0.973f); // 97.32% value
  glVertex3f(0.0866f, 0.45f, COMPARTMENT_DEPTH);
  glColor3fv(compartmentColor_080);
  glVertex3f(0.1f, 0.4f, COMPARTMENT_DEPTH);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3fv(compartmentColor_080);
  glVertex3f(0.0f, 0.4f, COMPARTMENT_DEPTH);
  glVertex3f(0.1f, 0.4f, COMPARTMENT_DEPTH);
  glColor3fv(mCompartmentColor);
  glVertex3f(0.1f, 0.0f, COMPARTMENT_DEPTH);
  glVertex3f(0.0f, 0.0f, COMPARTMENT_DEPTH);
  glEnd();
  glColor4fv(mFrameColor);
  glLineWidth(1.0f);
  // raise the line strip a bit to circumvent clipping errors
  glDisable(GL_DEPTH_TEST);
  glBegin(GL_LINE_STRIP);
  glVertex3f(0.0f, 0.5f, COMPARTMENT_FRAME_DEPTH);
  glVertex3f(0.05f, 0.4866f, COMPARTMENT_FRAME_DEPTH);
  glVertex3f(0.0866f, 0.45f, COMPARTMENT_FRAME_DEPTH);
  glVertex3f(0.1f, 0.4f, COMPARTMENT_FRAME_DEPTH);
  glVertex3f(0.1f, 0.0f, COMPARTMENT_FRAME_DEPTH);
  glEnd();
  glEnable(GL_DEPTH_TEST);
  glEndList();
  // now copy the first call list and mirror the copy at the x-axis
  glNewList(mDisplayLists + 1, GL_COMPILE);
  glPushMatrix();
  glTranslatef(0.0f, 0.5f, 0.0f);
  glCallList(mDisplayLists);
  // mirror transformation
  glMultMatrixf(MIRROR_X);
  glCallList(mDisplayLists);
  glPopMatrix();
  glEndList();
  // next list is the center piece for the compartment glyph
  glNewList(mDisplayLists + 2, GL_COMPILE);
  glBegin(GL_POLYGON);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, COMPARTMENT_DEPTH);
  glVertex3f(1.0f, 1.0f, COMPARTMENT_DEPTH);
  glColor3fv(mCompartmentColor);
  glVertex3f(1.0f, 0.5f, COMPARTMENT_DEPTH);
  glVertex3f(0.0f, 0.5f, COMPARTMENT_DEPTH);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3fv(mCompartmentColor);
  glVertex3f(0.0f, 0.5f, COMPARTMENT_DEPTH);
  glVertex3f(1.0f, 0.5f, COMPARTMENT_DEPTH);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 0.0f, COMPARTMENT_DEPTH);
  glVertex3f(0.0f, 0.0f, COMPARTMENT_DEPTH);
  glEnd();
  glColor4fv(mFrameColor);
  glLineWidth(1.0f);
  // raise the lines  a bit to circumvent clipping errors
  glDisable(GL_DEPTH_TEST);
  glBegin(GL_LINES);
  glVertex3f(0.0f, 1.0f, COMPARTMENT_FRAME_DEPTH);
  glVertex3f(1.0f, 1.0f, COMPARTMENT_FRAME_DEPTH);
  glVertex3f(0.0f, 0.0f, COMPARTMENT_FRAME_DEPTH);
  glVertex3f(1.0f, 0.0f, COMPARTMENT_FRAME_DEPTH);
  glEnd();
  glEnable(GL_DEPTH_TEST);
  glEndList();
  // call lists for the species nodes
  glNewList(mDisplayLists + 3, GL_COMPILE);
  // approximate a quarter circle by a triangle fan with 3 triangles
  glBegin(GL_TRIANGLE_FAN);
  glColor3fv(speciesColor_080);
  glVertex3f(0.0f, 0.4f, SPECIES_DEPTH);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(0.0f, 0.5f, SPECIES_DEPTH);
  glColor3f(mSpeciesColor[0] + (1.0f - mSpeciesColor[0]) * 0.9f, mSpeciesColor[1] + (1.0f - mSpeciesColor[1]) * 0.9f, mSpeciesColor[2] + (1.0f - mSpeciesColor[2]) * 0.9f); // 90% value
  glVertex3f(0.05f, 0.4866f, SPECIES_DEPTH);
  glColor3f(mSpeciesColor[0] + (1.0f - mSpeciesColor[0]) * 0.973f, mSpeciesColor[1] + (1.0f - mSpeciesColor[1]) * 0.973f, mSpeciesColor[2] + (1.0f - mSpeciesColor[2]) * 0.973f); // 97.32% value
  glVertex3f(0.0866f, 0.45f, SPECIES_DEPTH);
  glColor3fv(speciesColor_080);
  glVertex3f(0.1f, 0.4f, SPECIES_DEPTH);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3fv(speciesColor_080);
  glVertex3f(0.0f, 0.4f, SPECIES_DEPTH);
  glVertex3f(0.1f, 0.4f, SPECIES_DEPTH);
  glColor4fv(mSpeciesColor);
  glVertex3f(0.1f, 0.0f, SPECIES_DEPTH);
  glVertex3f(0.0f, 0.0f, SPECIES_DEPTH);
  glEnd();
  glColor4fv(mFrameColor);
  glLineWidth(1.0f);
  // raise the line strip a bit to circumvent clipping errors
  glDisable(GL_DEPTH_TEST);
  glBegin(GL_LINE_STRIP);
  glVertex3f(0.0f, 0.5f, SPECIES_FRAME_DEPTH);
  glVertex3f(0.05f, 0.4866f, SPECIES_FRAME_DEPTH);
  glVertex3f(0.0866f, 0.45f, SPECIES_FRAME_DEPTH);
  glVertex3f(0.1f, 0.4f, SPECIES_FRAME_DEPTH);
  glVertex3f(0.1f, 0.0f, SPECIES_FRAME_DEPTH);
  glEnd();
  glEnable(GL_DEPTH_TEST);
  glEndList();
  // now copy the first call list and mirror the copy at the x-axis
  glNewList(mDisplayLists + 4, GL_COMPILE);
  glPushMatrix();
  glTranslatef(0.0f, 0.5f, 0.0f);
  glCallList(mDisplayLists + 3);
  // mirror transformation
  glMultMatrixf(MIRROR_X);
  glCallList(mDisplayLists + 3);
  glPopMatrix();
  glEndList();
  // next list is the center piece for the species glyph
  glNewList(mDisplayLists + 5, GL_COMPILE);
  glBegin(GL_POLYGON);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, SPECIES_DEPTH);
  glVertex3f(1.0f, 1.0f, SPECIES_DEPTH);
  glColor3fv(mSpeciesColor);
  glVertex3f(1.0f, 0.5f, SPECIES_DEPTH);
  glVertex3f(0.0f, 0.5f, SPECIES_DEPTH);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3fv(mSpeciesColor);
  glVertex3f(0.0f, 0.5f, SPECIES_DEPTH);
  glVertex3f(1.0f, 0.5f, SPECIES_DEPTH);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 0.0f, SPECIES_DEPTH);
  glVertex3f(0.0f, 0.0f, SPECIES_DEPTH);
  glEnd();
  glColor4fv(mFrameColor);
  glLineWidth(1.0f);
  // raise the lines  a bit to circumvent clipping errors
  glDisable(GL_DEPTH_TEST);
  glBegin(GL_LINES);
  glVertex3f(0.0f, 1.0f, SPECIES_FRAME_DEPTH);
  glVertex3f(1.0f, 1.0f, SPECIES_FRAME_DEPTH);
  glVertex3f(0.0f, 0.0f, SPECIES_FRAME_DEPTH);
  glVertex3f(1.0f, 0.0f, SPECIES_FRAME_DEPTH);
  glEnd();
  glEnable(GL_DEPTH_TEST);
  glEndList();
  // display lists for arrow heads (try to be SBGN like)
  // head for stimulation (unfilled arrow)
  glNewList(mDisplayLists + 6, GL_COMPILE);
  glColor4fv(mBackgroundColor);
  glBegin(GL_POLYGON);
  glVertex3f(0.0f, 0.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(2.0f, -5.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(0.0f, -3.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(-2.0f, -5.0f, SPECIESREFERENCE_DEPTH);
  glEnd();
  glDisable(GL_DEPTH_TEST);
  glLineWidth(2.0f);
  glColor4fv(mSpeciesReferenceColor);
  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0f, 0.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(2.0f, -5.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(0.0f, -3.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(-2.0f, -5.0f, SPECIESREFERENCE_DEPTH);
  glEnd();
  glLineWidth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glEndList();
  // head for transition (filled arrow head)
  glNewList(mDisplayLists + 7, GL_COMPILE);
  glBegin(GL_POLYGON);
  glVertex3f(0.0f, 0.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(2.0f, -5.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(0.0f, -3.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(-2.0f, -5.0f, SPECIESREFERENCE_DEPTH);
  glEnd();
  glEndList();
  // head for inhibition (perpendicular bar)
  glNewList(mDisplayLists + 8, GL_COMPILE);
  glBegin(GL_POLYGON);
  glVertex3f(-3.0f, 0.5f, SPECIESREFERENCE_DEPTH);
  glVertex3f(3.0f, 0.5f, SPECIESREFERENCE_DEPTH);
  glVertex3f(3.0f, -0.5f, SPECIESREFERENCE_DEPTH);
  glVertex3f(-3.0f, -0.5f, SPECIESREFERENCE_DEPTH);
  glEnd();
  glEndList();
  // head for modulation (unfilled diamond)
  glNewList(mDisplayLists + 9, GL_COMPILE);
  glColor4fv(mBackgroundColor);
  glBegin(GL_POLYGON);
  glVertex3f(0.0f, 0.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(2.0f, -3.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(0.0f, -6.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(-2.0f, -3.0f, SPECIESREFERENCE_DEPTH);
  glEnd();
  glDisable(GL_DEPTH_TEST);
  glColor4fv(mSpeciesReferenceColor);
  glLineWidth(2.0f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0f, 0.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(2.0f, -3.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(0.0f, -6.0f, SPECIESREFERENCE_DEPTH);
  glVertex3f(-2.0f, -3.0f, SPECIESREFERENCE_DEPTH);
  glEnd();
  glLineWidth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glEndList();
  // display lists for the shadows of the glyphs
  glNewList(mDisplayLists + 10, GL_COMPILE);
  // approximate a quarter circle by a triangle fan with 3 triangles
  glColor4fv(mShadowColor);
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(0.0f, 0.4f, 0.0f);
  glVertex3f(0.0f, 0.5f, 0.0f);
  glVertex3f(0.05f, 0.4866f, 0.0f);
  glVertex3f(0.0866f, 0.45f, 0.0f);
  glVertex3f(0.1f, 0.4f, 0.0f);
  glEnd();
  glBegin(GL_POLYGON);
  glVertex3f(0.0f, 0.4f, 0.0f);
  glVertex3f(0.1f, 0.4f, 0.0f);
  glVertex3f(0.1f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glEnd();
  glEndList();
  // now copy the first call list and mirror the copy at the x-axis
  glNewList(mDisplayLists + 11, GL_COMPILE);
  glPushMatrix();
  glTranslatef(0.0f, 0.5f, 0.0f);
  glCallList(mDisplayLists + 10);
  // mirror transformation
  glMultMatrixf(MIRROR_X);
  glCallList(mDisplayLists + 10);
  glPopMatrix();
  glEndList();
  // next list is the center piece for the shadow
  glNewList(mDisplayLists + 12, GL_COMPILE);
  glColor4fv(mShadowColor);
  glBegin(GL_POLYGON);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glEnd();
  glEndList();
  // display list to draw a circle with a triangle fan for the animated species
  glNewList(mDisplayLists + 13, GL_COMPILE);
  float lowerBound = 0.5;
  std::vector<std::pair<float, float> >::const_iterator it = mCirclePoints.begin(), endit = mCirclePoints.end();
  glBegin(GL_TRIANGLE_FAN);
  glColor4fv(mAnimatedSpeciesColor);
  glVertex3f(0.0f, 0.0f, SPECIES_DEPTH);
  // on the edge we have 50% of the color value
  glColor4f(mAnimatedSpeciesColor[0]*lowerBound, mAnimatedSpeciesColor[1]*lowerBound, mAnimatedSpeciesColor[2]*lowerBound, 1.0f);

  while (it != endit)
    {
      glVertex3f(it->first, it->second, SPECIES_DEPTH);
      ++it;
    }

  glEnd();
  glColor4fv(mFrameColor);
  glDisable(GL_DEPTH_TEST);
  it = mCirclePoints.begin();
  glBegin(GL_LINE_LOOP);

  while (it != endit)
    {
      glVertex3f(it->first, it->second, SPECIES_FRAME_DEPTH);
      ++it;
    }

  glEnd();
  glEnable(GL_DEPTH_TEST);
  glEndList();
  // gray circle with color gradient for deactivated species in animation
  glNewList(mDisplayLists + 14, GL_COMPILE);
  lowerBound = 0.5;
  it = mCirclePoints.begin(), endit = mCirclePoints.end();
  glBegin(GL_TRIANGLE_FAN);
  glColor4fv(mInanimatedSpeciesColor);
  glVertex3f(0.0f, 0.0f, SPECIES_DEPTH);
  // on the edge we have 50% of the color value
  glColor4f(mInanimatedSpeciesColor[0]*lowerBound, mInanimatedSpeciesColor[1]*lowerBound, mInanimatedSpeciesColor[2]*lowerBound, 1.0f);

  while (it != endit)
    {
      glVertex3f(it->first, it->second, SPECIES_DEPTH);
      ++it;
    }

  glEnd();
  glColor4fv(mFrameColor);
  glDisable(GL_DEPTH_TEST);
  it = mCirclePoints.begin();
  glBegin(GL_LINE_LOOP);

  while (it != endit)
    {
      glVertex3f(it->first, it->second, SPECIES_FRAME_DEPTH);
      ++it;
    }

  glEnd();
  glEnable(GL_DEPTH_TEST);
  glEndList();
  // gray circle for constant nodes in animation
  glNewList(mDisplayLists + 15, GL_COMPILE);
  lowerBound = 0.5;
  it = mCirclePoints.begin(), endit = mCirclePoints.end();
  glBegin(GL_TRIANGLE_FAN);
  glColor4fv(mConstantSpeciesColor);
  glVertex3f(0.0f, 0.0f, SPECIES_DEPTH);
  // on the edge we have 50% of the color value
  glColor4f(mConstantSpeciesColor[0]*lowerBound, mConstantSpeciesColor[1]*lowerBound, mConstantSpeciesColor[2]*lowerBound, 1.0f);

  while (it != endit)
    {
      glVertex3f(it->first, it->second, SPECIES_DEPTH);
      ++it;
    }

  glEnd();
  glColor4fv(mFrameColor);
  glDisable(GL_DEPTH_TEST);
  it = mCirclePoints.begin();
  glBegin(GL_LINE_LOOP);

  while (it != endit)
    {
      glVertex3f(it->first, it->second, SPECIES_FRAME_DEPTH);
      ++it;
    }

  glEnd();
  glEnable(GL_DEPTH_TEST);
  glEndList();
  // gray circle with transparency for circle shadows
  glNewList(mDisplayLists + 16, GL_COMPILE);
  it = mCirclePoints.begin(), endit = mCirclePoints.end();
  glBegin(GL_TRIANGLE_FAN);
  glColor4fv(mShadowColor);
  glVertex3f(0.0f, 0.0f, 0.0f);

  while (it != endit)
    {
      glVertex3f(it->first, it->second, 0.0f);
      ++it;
    }

  glEnd();
  glEndList();
}

void CQGLNetworkPainter::initializeGL()
{
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_ALPHA_TEST);
  // glEnable(GL_POINT_SMOOTH);
  // glEnable(GL_POLYGON_SMOOTH);
  glShadeModel(GL_SMOOTH);
  glGenTextures(1, textureNames);
  this->initializeDisplayLists();
  mIsInitialized = true;
}

void CQGLNetworkPainter::resizeGL(int w, int h)
{
  // setup viewport, projection etc.:
  glViewport(0, 0, (GLint)w, (GLint)h);
  glMatrixMode(GL_PROJECTION);    // Select The Projection Matrix
  glLoadIdentity();             // Reset The Projection Matrix
  gluOrtho2D((GLdouble)mCurrentPositionX,
             (GLdouble)(mCurrentPositionX + w / mCurrentZoom),
             (GLdouble)(mCurrentPositionY + h / mCurrentZoom),
             (GLdouble)mCurrentPositionY); // y: 0.0 is bottom left instead of top left as in SBML
  glMatrixMode(GL_MODELVIEW);  // Select The Modelview Matrix
}

void CQGLNetworkPainter::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
  draw();
  glFlush();
}

const CLPoint &CQGLNetworkPainter::getGraphMin()
{
  const CLPoint &mi = mgraphMin;
  return mi;
}

const CLPoint &CQGLNetworkPainter::getGraphMax()
{
  const CLPoint &ma = mgraphMax;
  return ma;
}

// set graph size and reset projection to fit new size
void CQGLNetworkPainter::setGraphSize(const CLPoint &min, const CLPoint &max)
{
  mgraphMin.setX(min.getX());
  mgraphMin.setY(min.getY());
  mgraphMax.setX(max.getX());
  mgraphMax.setY(max.getY());
}

void CQGLNetworkPainter::draw()
{
  glLoadIdentity();
  drawGraph();
}

void CQGLNetworkPainter::createGraph(CLayout *lP)
{
  std::map< std::string, CCompartmentGraphNode * >::iterator it = compartmentNodeMap.begin();
  std::map< std::string, CCompartmentGraphNode * >::iterator end = compartmentNodeMap.end();

  for (; it != end; ++it)
    {
      pdelete(it->second);
    }

  compartmentNodeMap.clear();
  keyMap.clear();
  nodeMap.clear();
  labelNodeMap.clear();
  nodeArrowMap.clear();
  nodeCurveMap.clear();
  viewerNodes.clear();
  viewerCurves.clear();
  viewerLabels.clear();
  curvesWithArrow.clear();
  int numberOfInvertedCurves = 0;
  // copy graph to local variables
  const CDataVector<CLCompartmentGlyph> &compartmentNodes = lP->getListOfCompartmentGlyphs();
  viewerCompartmentNodes = std::vector<std::string>();
  unsigned int i;

  for (i = 0; i < compartmentNodes.size(); i++)
    {
      std::string nKey = compartmentNodes[i].getKey();
      std::string oKey = compartmentNodes[i].getModelObjectKey();
      viewerCompartmentNodes.push_back(nKey);
      compartmentNodeMap.insert(std::make_pair(nKey, new CCompartmentGraphNode(compartmentNodes[i], NO_PARENT)));
      keyMap.insert(std::pair<std::string, std::string>
                    (oKey, nKey));
    }

  CDataVector<CLMetabGlyph> nodes;
  nodes = lP->getListOfMetaboliteGlyphs();
  viewerNodes = std::vector<std::string>();

  for (i = 0; i < nodes.size(); i++)
    {
      std::string nKey = nodes[i].getKey();
      std::string oKey = nodes[i].getModelObjectKey();
      viewerNodes.push_back(nKey);
      nodeMap.insert(std::pair<std::string, CGraphNode>
                     (nKey,
                      CGraphNode(nodes[i], NO_PARENT)));
      keyMap.insert(std::pair<std::string, std::string>
                    (oKey, nKey));
    }

  CDataVector<CLReactionGlyph> reactions;
  reactions = lP->getListOfReactionGlyphs();
  //now extract curves to draw from reaction
  viewerCurves = std::vector<CGraphCurve>();

  //first get reaction arrow
  for (i = 0; i < reactions.size(); i++)
    {
      CGraphCurve curveR = CGraphCurve(reactions[i].getCurve());
      viewerCurves.push_back(curveR);
      CDataVector<CLMetabReferenceGlyph> edgesToNodesOfReaction;
      edgesToNodesOfReaction = reactions[i].getListOfMetabReferenceGlyphs();
      unsigned int j2;

      for (j2 = 0; j2 < edgesToNodesOfReaction.size(); j2++)
        {
          CGraphCurve curve = CGraphCurve(edgesToNodesOfReaction[j2].getCurve());
          std::string nodeKey = "";

          if (edgesToNodesOfReaction[j2].getMetabGlyph() != NULL) // i.e. there is an associated node
            {
              nodeKey = std::string(edgesToNodesOfReaction[j2].getMetabGlyph()->getKey());
              std::map<std::string, CGraphNode>::iterator itNode;
              itNode = nodeMap.find(nodeKey);

              if (itNode != nodeMap.end())
                {
                  CLBoundingBox box = (*itNode).second.getBoundingBox();

                  if (this->checkCurve(&curve, curveR, box))
                    numberOfInvertedCurves++;
                }
            }

          CLMetabReferenceGlyph::Role r = edgesToNodesOfReaction[j2].getRole();
          curve.setRole(r);

          if (edgesToNodesOfReaction[j2].getMetabGlyph() != NULL)  // if there is an associated species node look whether an arrow has to be created
            {
              // if role is product or sideproduct, create arrow for line
              if ((r == CLMetabReferenceGlyph::PRODUCT) || (r == CLMetabReferenceGlyph::SIDEPRODUCT) || (r == CLMetabReferenceGlyph::ACTIVATOR) || (r == CLMetabReferenceGlyph::INHIBITOR) || (r == CLMetabReferenceGlyph::MODIFIER))
                {
                  // create arrows just for edges to products or sideproducts
                  std::vector<CLLineSegment> segments = curve.getCurveSegments();

                  if (! segments.empty())
                    {
                      CLLineSegment lastSeg = segments[segments.size() - 1];

                      if ((r == CLMetabReferenceGlyph::ACTIVATOR) || (r == CLMetabReferenceGlyph::INHIBITOR) || (r == CLMetabReferenceGlyph::MODIFIER))
                        {
                          lastSeg = segments[0];
                        }

                      CLPoint p = lastSeg.getEnd();
                      CArrow *ar;

                      if (lastSeg.isBezier())
                        {
                          CLPoint to = lastSeg.getBase2();
                          CLPoint p = lastSeg.getEnd();

                          // check if the second base point and the endpoint are identical
                          if (fabs(p.getX() - to.getX() + p.getY() - to.getY()) < 1e-8)
                            {
                              // if yes, take the first basepoint
                              to = lastSeg.getBase1();

                              // if they are still identical take the start point because
                              // it is a straight line
                              if (fabs(p.getX() - to.getX() + p.getY() - to.getY()) < 1e-8)
                                {
                                  to = lastSeg.getStart();
                                }
                            }

                          CLLineSegment segForArrow;

                          if ((r == CLMetabReferenceGlyph::ACTIVATOR) || (r == CLMetabReferenceGlyph::INHIBITOR) || (r == CLMetabReferenceGlyph::MODIFIER))
                            {
                              segForArrow = CLLineSegment(to, lastSeg.getEnd());
                            }
                          else
                            {
                              segForArrow = CLLineSegment(to, lastSeg.getEnd());
                            }

                          if ((r == CLMetabReferenceGlyph::ACTIVATOR) || (r == CLMetabReferenceGlyph::INHIBITOR) || (r == CLMetabReferenceGlyph::MODIFIER))
                            {
                              ar = new CArrow(segForArrow, lastSeg.getEnd().getX(), lastSeg.getEnd().getY(), this->mCurrentZoom);
                            }
                          else
                            {
                              ar = new CArrow(segForArrow, lastSeg.getEnd().getX(), lastSeg.getEnd().getY(), this->mCurrentZoom);
                            }
                        }
                      else
                        {
                          if ((r == CLMetabReferenceGlyph::ACTIVATOR) || (r == CLMetabReferenceGlyph::INHIBITOR) || (r == CLMetabReferenceGlyph::MODIFIER))
                            {
                              ar = new CArrow(lastSeg, p.getX(), p.getY(), this->mCurrentZoom);
                            }
                          else
                            {
                              ar = new CArrow(lastSeg, p.getX(), p.getY(), this->mCurrentZoom);
                            }
                        }

                      curve.setArrowP(true);
                      curve.setArrow(*ar);
                      delete ar;
                    }
                }

              if (nodeKey != "")
                {
                  nodeCurveMap.insert(std::pair<std::string, CGraphCurve>
                                      (nodeKey,
                                       curve));
                }
            }
          else
            {
              // if no species node is associated with the curve: just store curve
              viewerCurves.push_back(curve); // just collect curve in order to be shown within the graph
            }
        } // end j
    } // end i (reactions)

  CDataVector<CLTextGlyph> labels;
  labels = lP->getListOfTextGlyphs();
  viewerLabels = std::vector<CLabel>();
  std::map<std::string, CGraphNode>::iterator itNode;

  for (i = 0; i < labels.size(); i++)
    {
      labelNodeMap.insert(std::pair<std::string, std::string>
                          (labels[i].getKey(),
                           labels[i].getGraphicalObjectKey()));
      std::string s1 = labels[i].getKey();
      std::string s2 = labels[i].getGraphicalObjectKey();
      viewerLabels.push_back(CLabel(labels[i]));
      itNode = nodeMap.find(labels[i].getGraphicalObjectKey());

      if (itNode != nodeMap.end())
        {
          (*itNode).second.setLabelText(labels[i].getText());
        }
    }

  CLPoint p1 = CLPoint(0.0, 0.0);
  CLPoint p2 = CLPoint(lP->getDimensions().getWidth(), lP->getDimensions().getHeight());
  this->setGraphSize(p1, p2);
}

// decides whether the direction of the curve has to be inverted (meaning the order of the line segments, start and end points and base points have to be inverted
bool CQGLNetworkPainter::checkCurve(CGraphCurve *curve, CGraphCurve /* curveR */, CLBoundingBox box)
{
  bool inverted = false;
  // first checks whether the start point or the end point of the curve is closer to the center of the box defining the reactant node
  CLPoint center; // center of bounding box for node
  center.setX(box.getPosition().getX() + (box.getDimensions().getWidth() / 2.0));
  center.setY(box.getPosition().getY() + (box.getDimensions().getHeight() / 2.0));
  // get start and end point of curve (start point of first segment and end point of last segment)
  std::vector <CLPoint> points = curve->getListOfPoints();

  if (points.size() > 1)
    {
      // if there are at least 2 points
      CLPoint s = points[0];
      CLPoint e = points[points.size() - 1];
      // now compute the distances from these points to the center
      C_FLOAT64 dist1 = sqrt(((center.getX() - s.getX()) * (center.getX() - s.getX())) +
                             ((center.getY() - s.getY()) * (center.getY() - s.getY())));
      C_FLOAT64 dist2 = sqrt(((center.getX() - e.getX()) * (center.getX() - e.getX())) +
                             ((center.getY() - e.getY()) * (center.getY() - e.getY())));

      if (dist1 < dist2)
        {
          // if the start point of the curve is closer to the node than the end point
          // the curve direction should be TOWARDS the node, not away from it
          curve->invertOrderOfPoints(); // invert the order of the points in the curve
          inverted = true;
        }
    }

  return inverted;
}

void CQGLNetworkPainter::drawGraph()
{
  // create OpenGL display list
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  unsigned int i;

  if ((pParentLayoutWindow != NULL) && this->mLabelShape == CIRCLE &&
      (pParentLayoutWindow->getMappingMode() == CVisParameters::COLOR_MODE)) // draw color legend
    {
      drawColorLegend();
    } // end color mode

  // draw curves to (reactant) nodes and arrows and circular nodes when in appropriate mode
  std::map< std::string, CCompartmentGraphNode * >::const_iterator itCompartmentNode;
  std::map<std::string, CGraphNode>::iterator itNode;
  std::multimap<std::string, CGraphCurve>::iterator itCurve;
  std::multimap<std::string, CArrow>::iterator itArrow;
  std::pair<std::multimap<std::string, CGraphCurve>::iterator, std::multimap<std::string, CGraphCurve>::iterator> curveRangeIt;;
  std::pair<std::multimap<std::string, CArrow>::iterator, std::multimap<std::string, CArrow>::iterator> arrowRangeIt;

  for (i = 0; i < viewerCompartmentNodes.size(); i++)
    {
      itCompartmentNode = compartmentNodeMap.find(viewerCompartmentNodes[i]);

      // draw node as rectangle
      if (itCompartmentNode != compartmentNodeMap.end())
        {
          drawNode(*itCompartmentNode->second);
        }
    }

  for (i = 0; i < viewerNodes.size(); i++)
    {
      itNode = nodeMap.find(viewerNodes[i]);
      // draw curves of node
      curveRangeIt = nodeCurveMap.equal_range(viewerNodes[i]);
      itCurve = curveRangeIt.first;
      glColor4fv(mSpeciesReferenceColor);

      while (itCurve != curveRangeIt.second)
        {
          drawEdge((*itCurve).second);
          itCurve++;
        }

      //draw node as a circle
      if (itNode != nodeMap.end())
        {
          drawNode((*itNode).second);
        }
    }

  glColor4fv(mSpeciesReferenceColor);

  for (i = 0; i < viewerCurves.size(); i++) // draw edges that do not directly belong to a node (reaction curves)
    {
      drawEdge(viewerCurves[i]);
    }

  // NOW DRAW LABELS

  if (this->mLabelShape == RECTANGLE)
    {
      // debug: print font info
      this->mf.setPointSize(this->mFontsize);
      const QFont &mfRef = this->mf;
      QFontInfo fontInfo = QFontInfo(mfRef);

      // debug end
      for (i = 0; i < viewerLabels.size(); i++)
        {
          // only draw the text if there actually is text
          if (!viewerLabels[i].getText().empty())
            {
              RG_drawStringAt(viewerLabels[i].getText(), static_cast<C_INT32>(viewerLabels[i].getX()), static_cast<C_INT32>(viewerLabels[i].getY()), static_cast<C_INT32>(viewerLabels[i].getWidth()), static_cast<C_INT32>(viewerLabels[i].getHeight()));
            }
        }
    }
  else
    {
      // draw string next to circle (to the right) or in the center if there is enough space
      for (i = 0; i < viewerLabels.size(); i++)
        {
          if (!viewerLabels[i].getText().empty())
            {
              C_FLOAT64 tWid = getTextWidth(viewerLabels[i].getText(), mFontname, static_cast<int>(floor(viewerLabels[i].getHeight())));
              C_FLOAT64 nDiam = 0.0;
              C_FLOAT64 x, y;
              const std::string &nodeKey = viewerLabels[i].getGraphicalObjectKey();

              if (!nodeKey.empty())
                {
                  std::map<std::string, CGraphNode>::iterator itNodeObj;
                  itNodeObj = nodeMap.find(nodeKey);

                  if (itNodeObj != nodeMap.end())
                    nDiam = (*itNodeObj).second.getSize();

                  C_INT32 xNdCenter = (C_INT32)((*itNodeObj).second.getX() + ((*itNodeObj).second.getWidth() / 2.0));
                  C_INT32 yNdCenter = (C_INT32)(*itNodeObj).second.getY() + ((*itNodeObj).second.getHeight() / 2.0);

                  if (pParentLayoutWindow->getMappingMode() == CVisParameters::COLOR_MODE)
                    {
                      x = xNdCenter + (CVisParameters::DEFAULT_NODE_SIZE / 2.0 * this->mCurrentZoom) + 2.0 - ((viewerLabels[i].getWidth() - tWid) / 2.0); // node center + circle radius + 2.0 - texture window overhead
                      y = yNdCenter + (CVisParameters::DEFAULT_NODE_SIZE / 2.0 * this->mCurrentZoom) + 2.0 - ((viewerLabels[i].getHeight()) / 2.0);
                    }
                  else if ((tWid + 4) > nDiam)
                    {
                      // label wider (+ k=4 to avoid crossing circle borders) than size of circle-> place next to circle
                      x = xNdCenter + (nDiam / 2.0) + 2.0 - ((viewerLabels[i].getWidth() - tWid) / 2.0); // + nDiam / 2.0 - ((labelWWid - (*itNodeObj).second.getWidth()) / 2.0); // node center + circle radius - texture window overhead
                      y = yNdCenter + (nDiam / 2.0) + 2.0 - ((viewerLabels[i].getHeight()) / 2.0);
                    }
                  else
                    {
                      // place in center of circle
                      x = xNdCenter - (viewerLabels[i].getWidth() / 2.0); // - ((labelWWid - (*itNodeObj).second.getWidth()) / 2.0);
                      y = yNdCenter;
                    }
                }
              else
                {
                  // if there is no node associated, just take label position
                  x = viewerLabels[i].getX();
                  y = viewerLabels[i].getY();
                }

              RG_drawStringAt(viewerLabels[i].getText(), static_cast<C_INT32>(x), static_cast<C_INT32>(y), static_cast<C_INT32>(viewerLabels[i].getWidth()), static_cast<C_INT32>(viewerLabels[i].getHeight()));
            }
        }
    }
}

void CQGLNetworkPainter::drawColorLegend()
{
  C_INT32 sx = 40; //start at position (sx,sy)
  C_INT32 sy = 20;
  C_INT32 w = 120; // size of legend rectangle w x h
  C_INT32 h = 15;
  RG_drawStringAt("MIN", 7, sy + 3, 32, 16);
  RG_drawStringAt("MAX", 165, sy + 3, 32, 16);
  // the colors should go from RGB 0,0,0 to RGB 200,0,0 to RGB 200,200,0 to RGB
  // 255,255,0
  C_INT16 i;
  QColor col = QColor();
  // the color range has 456 steps and the legend has 120 pixels
  // so the step size is 455/120
  double ratio = 455 / 120;
  double val;

  for (i = 0; i <= w; i++)
    {
      val = i * ratio;

      if (val < 200.0)
        {
          col.setRgb(0, 0, (int)val);
        }
      else if (val < 400.0)
        {
          col.setRgb(0, (int)(val - 200.0), 200);
        }
      else
        {
          col.setRgb(0, 200 + (int)(val - 400.0), 200 + (int)(val - 400.0));
        }

      QGLWidget::qglColor(col);
      // draw colored line in rectangle
      glBegin(GL_LINES);
      glVertex2d(i + sx, sy);
      glVertex2d(i + sx, sy + h);
      glEnd();
    }
}

// draw compartment node as rectangle
void CQGLNetworkPainter::drawNode(const CCompartmentGraphNode &n)
{
  float width = n.getWidth();
  float height = n.getHeight();
  float x = n.getX();
  float y = n.getY();
  float translateX = 0.0f;
  float scaledWidth = width - (0.2f * height);

  if (mDrawShadows == true)
    {
      // first we draw the shadow which we move a bit to the left and somewhat up
      // and into the correct depth
      glPushMatrix();
      // draw one end
      glLoadIdentity();
      glTranslatef(mCompartmentShadowXOffset, mCompartmentShadowYOffset, COMPARTMENT_SHADOW_DEPTH);
      translateX = x;
      glPushMatrix();
      // additional translation 0.1*width needed because we mirror the
      // element
      glTranslatef(translateX + height * 0.1, y, 0.0f);
      glScalef(height, height, 1.0f);
      // mirror it at the y axis
      glMultMatrixf(MIRROR_Y);
      glCallList(mDisplayLists + 11);
      glPopMatrix();
      // draw the center
      // scale it to the correct width
      translateX += 0.1 * height;
      glTranslatef(translateX, y, 0.0f);
      // the scaling has to be different
      glScalef(scaledWidth, height, 1.0f);
      glCallList(mDisplayLists + 12);
      // draw the other end
      glLoadIdentity();
      glTranslatef(mCompartmentShadowXOffset, mCompartmentShadowYOffset, COMPARTMENT_SHADOW_DEPTH);
      translateX += scaledWidth;
      glTranslatef(translateX, y, 0.0f);
      glScalef(height, height, 1.0f);
      glCallList(mDisplayLists + 11);
      // scale the object the the correct size
      glPopMatrix();
    }

  // now draw the real glyph
  glPushMatrix();
  // draw one end
  glLoadIdentity();
  translateX = x;
  glPushMatrix();
  // additional translation 0.1*width needed because we mirror the
  // element
  glTranslatef(translateX + height * 0.1, y, 0.0f);
  glScalef(height, height, 1.0f);
  // mirror it at the y axis
  glMultMatrixf(MIRROR_Y);
  glCallList(mDisplayLists + 1);
  glPopMatrix();
  // draw the center
  // scale it to the correct width
  translateX += 0.1 * height;
  glTranslatef(translateX, y, 0.0f);
  // the scaling has to be different
  glScalef(scaledWidth, height, 1.0f);
  glCallList(mDisplayLists + 2);
  // draw the other end
  glLoadIdentity();
  translateX += scaledWidth;
  glTranslatef(translateX, y, 0.0f);
  glScalef(height, height, 1.0f);
  glCallList(mDisplayLists + 1);
  // scale the object the the correct size
  glPopMatrix();
}

// draw node as circle
void CQGLNetworkPainter::drawNode(CGraphNode &n) // draw node as filled circle
{
  if (this->mLabelShape == CIRCLE)
    {
      float scaledValue = CVisParameters::DEFAULT_NODE_SIZE * mCurrentZoom;
      CVisParameters::MAPPING_MODE mappingMode = CVisParameters::SIZE_DIAMETER_MODE;

      if (pParentLayoutWindow != NULL)
        {
          mappingMode = pParentLayoutWindow->getMappingMode();

          if ((mappingMode == CVisParameters::SIZE_DIAMETER_MODE) ||
              (mappingMode == CVisParameters::SIZE_AREA_MODE))
            {
              scaledValue = n.getSize(); // change of node size only for size mode
            }
        }

      glColor4fv(mAnimatedSpeciesColor); // red
      double tx = n.getX() + (n.getWidth() / 2.0);
      double ty = n.getY() + (n.getHeight() / 2.0);

      if ((mappingMode == CVisParameters::SIZE_DIAMETER_MODE) ||
          (mappingMode == CVisParameters::SIZE_AREA_MODE))
        {
          if (setOfConstantMetabolites.find(n.getOrigNodeKey()) == setOfConstantMetabolites.end())
            {
              if (setOfDisabledMetabolites.find(n.getOrigNodeKey()) == setOfDisabledMetabolites.end())
                {
                  // red as default color for all nodes in non-color modes
                  // which have a substantial range of values (max - min > epsilon)
                  // and which are not disabled
                  if (mDrawShadows == true)
                    {
                      glPushMatrix();
                      glTranslatef(tx + mSpeciesShadowXOffset, ty + mSpeciesShadowYOffset, SPECIES_SHADOW_DEPTH);
                      glScalef(scaledValue, scaledValue, 1.0f);
                      glCallList(mDisplayLists + 16);
                      glPopMatrix();
                    }

                  glPushMatrix();
                  glTranslatef(tx, ty, 0.0f);
                  glScalef(scaledValue, scaledValue, 1.0f);
                  glCallList(mDisplayLists + 13);
                  glPopMatrix();
                }
              else
                {
                  scaledValue = CVisParameters::DEFAULT_NODE_SIZE; // default node size

                  if (mDrawShadows == true)
                    {
                      glPushMatrix();
                      glTranslatef(tx + mSpeciesShadowXOffset, ty + mSpeciesShadowYOffset, SPECIES_SHADOW_DEPTH);
                      glScalef(scaledValue, scaledValue, 1.0f);
                      glCallList(mDisplayLists + 16);
                      glPopMatrix();
                    }

                  glPushMatrix();
                  glTranslatef(tx, ty, 0.0f);
                  glScalef(scaledValue, scaledValue, 1.0f);
                  glCallList(mDisplayLists + 14);
                  glPopMatrix();
                }
            }
          else
            {
              scaledValue = CVisParameters::DEFAULT_NODE_SIZE; // node size for disabled nodes

              if (mDrawShadows == true)
                {
                  glPushMatrix();
                  glTranslatef(tx + mSpeciesShadowXOffset, ty + mSpeciesShadowYOffset, SPECIES_SHADOW_DEPTH);
                  glScalef(scaledValue, scaledValue, 1.0f);
                  glCallList(mDisplayLists + 16);
                  glPopMatrix();
                }

              glPushMatrix();
              glTranslatef(tx, ty, 0.0f);
              glScalef(scaledValue, scaledValue, 1.0f);
              glCallList(mDisplayLists + 15);
              glPopMatrix();
            }
        }
      // are not scaled and marked in grey
      else
        {
          // color mapping
          GLfloat color[3] = {1.0f, 1.0f, 1.0f};

          if (setOfConstantMetabolites.find(n.getOrigNodeKey()) == setOfConstantMetabolites.end())
            {
              if (setOfDisabledMetabolites.find(n.getOrigNodeKey()) == setOfDisabledMetabolites.end())
                {
                  float v = (float)n.getSize() * 455.0f; // there are 456 colors in the current gradient and the node sizes are scaled from 0.0 to 1.0 in color mode

                  if (v < 200.0)
                    {
                      color[0] = 0.0f;
                      color[1] = 0.0f;
                      color[2] = v / 255.0f;
                    }
                  else if (v < 400)
                    {
                      color[0] = 0.0f;
                      color[1] = (v - 200.0f) / 255.0f;
                      color[2] = 200.0f / 255.0f;
                    }
                  else
                    {
                      color[0] = 0.0f;
                      color[1] = (200.0f + (v - 400.0f)) / 255.0f;
                      color[2] = (200.0f + (v - 400.0f)) / 255.0f;
                    }
                }
              // is disabled
              else
                {
                  // set color to white
                  color[0] = 1.0f;
                  color[1] = 1.0f;
                  color[2] = 1.0f;
                }
            }
          // is constant
          else
            {
              // set color to light gray
              color[0] = mConstantSpeciesColor[0];
              color[1] = mConstantSpeciesColor[1];
              color[2] = mConstantSpeciesColor[2];
            }

          if (mDrawShadows == true)
            {
              glPushMatrix();
              glTranslatef(tx + mSpeciesShadowXOffset, ty + mSpeciesShadowYOffset, SPECIES_SHADOW_DEPTH);
              glScalef(scaledValue, scaledValue, 1.0f);
              glCallList(mDisplayLists + 16);
              glPopMatrix();
            }

          // use out own circle points to draw the circle instead of using glut
          // this makes it easier to have color gradients.
          glPushMatrix();
          glTranslatef((float)tx, (float)ty, 0.0f);
          glScalef(scaledValue, scaledValue, 1.0f);
          float lowerBound = 0.5;
          std::vector<std::pair<float, float> >::const_iterator it = mCirclePoints.begin(), endit = mCirclePoints.end();
          glBegin(GL_TRIANGLE_FAN);
          glColor3fv(color);
          glVertex3f(0.0f, 0.0f, SPECIES_DEPTH);
          // on the edge we have 50% of the color value
          glColor4f(color[0]*lowerBound, color[1]*lowerBound, color[2]*lowerBound, 1.0f);

          while (it != endit)
            {
              glVertex3f(it->first, it->second, SPECIES_DEPTH);
              ++it;
            }

          glEnd();
          glColor4fv(mFrameColor);
          glDisable(GL_DEPTH_TEST);
          it = mCirclePoints.begin();
          glBegin(GL_LINE_LOOP);

          while (it != endit)
            {
              glVertex3f(it->first, it->second, SPECIES_FRAME_DEPTH);
              ++it;
            }

          glEnd();
          glPopMatrix();
        }
    }
  else
    {
      float width = n.getWidth();
      float height = n.getHeight();
      float x = n.getX();
      float y = n.getY();
      float scaledWidth = width - (0.2f * height);
      float translateX = 0.0f;

      // first draw shadow if enabled
      if (mDrawShadows == true)
        {
          // first we draw the shadow which we move a bit to the left and somewhat up
          // and into the correct depth
          glPushMatrix();
          // draw one end
          glLoadIdentity();
          glTranslatef(mSpeciesShadowXOffset, mSpeciesShadowYOffset, SPECIES_SHADOW_DEPTH);
          translateX = x;
          glPushMatrix();
          // additional translation 0.1*width needed because we mirror the
          // element
          glTranslatef(translateX + height * 0.1, y, 0.0f);
          glScalef(height, height, 1.0f);
          // mirror it at the y axis
          glMultMatrixf(MIRROR_Y);
          glCallList(mDisplayLists + 11);
          glPopMatrix();
          // draw the center
          // scale it to the correct width
          translateX += 0.1 * height;
          glTranslatef(translateX, y, 0.0f);
          // the scaling has to be different
          glScalef(scaledWidth, height, 1.0f);
          glCallList(mDisplayLists + 12);
          // draw the other end
          glLoadIdentity();
          glTranslatef(mSpeciesShadowXOffset, mSpeciesShadowYOffset, SPECIES_SHADOW_DEPTH);
          translateX += scaledWidth;
          glTranslatef(translateX, y, 0.0f);
          glScalef(height, height, 1.0f);
          glCallList(mDisplayLists + 11);
          // scale the object the the correct size
          glPopMatrix();
        }

      // now draw the real glyph
      glPushMatrix();
      // draw one end
      glLoadIdentity();
      translateX = x;
      glPushMatrix();
      // additional translation 0.1*width needed because we mirror the
      // element
      glTranslatef(translateX + height * 0.1, y, 0.0f);
      glScalef(height, height, 1.0f);
      // mirror it at the y axis
      glMultMatrixf(MIRROR_Y);
      glCallList(mDisplayLists + 4);
      glPopMatrix();
      // draw the center
      // scale it to the correct width
      translateX += 0.1 * height;
      glTranslatef(translateX, y, 0.0f);
      // the scaling has to be different
      glScalef(scaledWidth, height, 1.0f);
      glCallList(mDisplayLists + 5);
      // draw the other end
      glLoadIdentity();
      translateX += scaledWidth;
      glTranslatef(translateX, y, 0.0f);
      glScalef(height, height, 1.0f);
      glCallList(mDisplayLists + 4);
      // scale the object the the correct size
      glPopMatrix();
    }
}

// draw a curve: at the moment just a line from the start point to the end point (for each segment)
void CQGLNetworkPainter::drawEdge(CGraphCurve &c)
{
  glLineWidth(2.0);
  // Depth test has to be disabled when drawing lines,
  // especially if the lines have a thickness greater 1
  // otherwise they look ugly because break appear at the end of the lines and
  // they seem to be disconnected.
  // This seems to be a feature of OpenGL rather than a bug. (See
  // http://www.3dsource.de/faq/rasterization.htm)
  glDisable(GL_DEPTH_TEST);
  std::vector<CLLineSegment> segments = c.getCurveSegments();
  size_t i;

  for (size_t k = 0; k < c.getNumCurveSegments(); k++)
    {
      CLLineSegment seg = segments[k];
      CLPoint startPoint = seg.getStart();
      CLPoint endPoint = seg.getEnd();
      // for the moment do not take type of curve into account

      if (seg.isBezier())
        {
          CLPoint base1 = seg.getBase1();
          CLPoint base2 = seg.getBase2();
          //now paint Bezier as line strip
          // use an evaluator since this is probably a lot more efficient
          GLfloat controlPts[4][3] =
          {
            {static_cast<GLfloat>(startPoint.getX()), static_cast<GLfloat>(startPoint.getY()), SPECIESREFERENCE_DEPTH},
            {static_cast<GLfloat>(base1.getX()), static_cast<GLfloat>(base1.getY()), SPECIESREFERENCE_DEPTH},
            {static_cast<GLfloat>(base2.getX()), static_cast<GLfloat>(base2.getY()), SPECIESREFERENCE_DEPTH},
            {static_cast<GLfloat>(endPoint.getX()), static_cast<GLfloat>(endPoint.getY()), SPECIESREFERENCE_DEPTH}
          };
          // enable the evaluator to draw the cubic Bezier
          glMap1f(GL_MAP1_VERTEX_3, 0.0f, 20.0f, 3, 4, &controlPts[0][0]);
          glEnable(GL_MAP1_VERTEX_3);
          glBegin(GL_LINE_STRIP);

          for (i = 0; i <= 20; ++i)
            {
              // evaluate the function
              glEvalCoord1f((GLfloat)i);
            }

          glEnd();
          glDisable(GL_MAP1_VERTEX_3);
        }
      else
        {
          // just draw a straight line
          glBegin(GL_LINE_STRIP);
          glVertex3d(startPoint.getX(), startPoint.getY(), SPECIESREFERENCE_DEPTH);
          glVertex3d(endPoint.getX(), endPoint.getY(), SPECIESREFERENCE_DEPTH);
          glEnd();
        }
    }

  glLineWidth(1.0);

  if (c.hasArrowP())
    {
      drawArrow(c.getArrow(), c.getRole());
    }

  glEnable(GL_DEPTH_TEST);
}

double CQGLNetworkPainter::calculateAngle(const CLPoint &endPoint, const CLPoint &startPoint)
{
  double deltaX = endPoint.getX() - startPoint.getX();
  double deltaY = endPoint.getY() - startPoint.getY();
  double angle = 0.0;

  if (deltaY == 0.0)
    {
      if (deltaX == 0.0)
        {
          return std::numeric_limits<double>::quiet_NaN();
        }

      // we have a horizontal line
      if (deltaX < 0.0)
        {
          angle = 180.0;
        }
    }
  else if (deltaX == 0.0)
    {
      if (deltaY == 0.0)
        {
          return std::numeric_limits<double>::quiet_NaN();
        }

      // we have a vertical line
      if (deltaX < 0.0)
        {
          angle = 270.0;
        }
      else
        {
          angle = 90.0f;
        }
    }
  else
    {
      double slope = deltaY / deltaX;
      angle = 180.0 * atan(slope) / M_PI;

      if (angle < 0.0)
        {
          angle += 360.0;
        }

      // now we have to find out in which quadrant the angle really is
      if (deltaX < 0.0)
        {
          if (deltaY > 0.0) // 2.quadrant; subtract 180
            {
              angle -= 180;
            }
          else // 3. quadrant; add 180
            {
              angle += 180.0;
            }
        }
    }

  return angle;
}

void CQGLNetworkPainter::drawArrow(CArrow a, CLMetabReferenceGlyph::Role role)
{
  // here we draw the arrow heads depending on the passed in role, a different
  // head is drawn
  // Since right now the edge width is fixed to a value of 2.0 and does not
  // scale with the rest of the diagram, it probably does not make sense to
  // scale the arrow heads.
  // we need to calculate the slope of the line at the attachment point
  // first get the two points defining the line segment (curve)
  CLPoint p2 = a.getStartOfLine();
  CLPoint p1 = a.getEndOfLine();
  // p1 and p2 define a line where the arrow peak can be placed onto,
  // peak should be at p1, the arrow peak is just a triangle
  // calculate the angle of the line from the x axis
  // since all arrow heads go along the y axis, we have to subtract 90° from
  // the angle to get the correct rotation angle
  double angle;

  if ((role == CLMetabReferenceGlyph::PRODUCT) || (role == CLMetabReferenceGlyph::SIDEPRODUCT))
    {
      angle = calculateAngle(p1, p2);
    }
  else
    {
      angle = calculateAngle(p2, p1);
    }

  if (angle != angle)
    {
      return; // we got NaN
    }

  angle -= 90.0;
  // so we need to rotate the head by angle degrees and move it to
  // p1.getX(),p1.getY()
  // first compute parameters of equation of line and point on line where arrow intersects line
  // now draw polygon, using vertices from triangle
  // now create triangle;
  glPushMatrix();
  glColor4fv(mSpeciesReferenceColor);

  if ((role == CLMetabReferenceGlyph::PRODUCT) || (role == CLMetabReferenceGlyph::SIDEPRODUCT))
    {
      glTranslatef(p1.getX(), p1.getY(), 0.0f);
      glRotatef(angle, 0.0f, 0.0f, 1.0f);
      glScalef(3.0f, 3.0f, 1.0f);
      glCallList(mDisplayLists + 7);
    }
  else
    {
      if (role == CLMetabReferenceGlyph::MODIFIER)
        {
          glTranslatef(p2.getX(), p2.getY(), 0.0f);
          glRotatef(angle, 0.0f, 0.0f, 1.0f);
          glScalef(3.0f, 3.0f, 1.0f);
          glCallList(mDisplayLists + 9);
        }
      else if (role == CLMetabReferenceGlyph::ACTIVATOR)
        {
          glTranslatef(p2.getX(), p2.getY(), 0.0f);
          glRotatef(angle, 0.0f, 0.0f, 1.0f);
          glScalef(3.0f, 3.0f, 1.0f);
          glCallList(mDisplayLists + 6);
        }
      else if (role == CLMetabReferenceGlyph::INHIBITOR)
        {
          glTranslatef(p2.getX(), p2.getY(), 0.0f);
          glRotatef(angle, 0.0f, 0.0f, 1.0f);
          glScalef(3.0f, 3.0f, 1.0f);
          glCallList(mDisplayLists + 8);
        }
    }

  // reset the color since some of the call lists change the color
  glColor4fv(mSpeciesReferenceColor);
  glPopMatrix();
}

// uses QT

void CQGLNetworkPainter::RG_drawStringAt(std::string s, C_INT32 x, C_INT32 y, C_INT32 w, C_INT32 h)
{
  RGTextureSpec *texSpec = getTextureForText(s, mFontname, h);

  if (texSpec == NULL)
    {
      return;
    }

  glPushMatrix();
  glColor4fv(mTextColor);
  glEnable(GL_TEXTURE_2D);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glBindTexture(GL_TEXTURE_2D, textureNames[0]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_INTENSITY8, static_cast<int>(texSpec->textureWidth), static_cast<int>(texSpec->textureHeight), 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texSpec->textureData);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTranslated(x, y, 0.5);
  double xOffset = (w - texSpec->textWidth + 2) / 2.0;
  double yOffset = (h - texSpec->textHeight + texSpec->textYOffset + 2) / 2.0;
  xOffset = (xOffset < 0.0) ? 0.0 : xOffset;
  yOffset = (yOffset < 0.0) ? 0.0 : yOffset;
  double textureXRatio = ((texSpec->textWidth + 2) / texSpec->textureWidth) / ((w - xOffset) / w) * 1.02;
  double textureYRatio = ((texSpec->textHeight + 2) / texSpec->textureHeight) / ((h - 2 * yOffset) / h);
  glBegin(GL_POLYGON);
  glTexCoord2f(-xOffset / texSpec->textureWidth, -yOffset / texSpec->textureHeight);
  glVertex3f(0.0, 0.0, 0.0);
  glTexCoord2f(textureXRatio, -yOffset / texSpec->textureHeight);
  glVertex3f(w, 0.0, 0.0);
  glTexCoord2f(textureXRatio, textureYRatio);
  glVertex3f(w, h, 0.0);
  glTexCoord2f(-xOffset / texSpec->textureWidth, textureYRatio);
  glVertex3f(0.0, h, 0.0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

int CQGLNetworkPainter::getTextWidth(const std::string &text, const std::string &fontName, unsigned int fontSize)
{
  QFont font(QString(fontName.c_str()), fontSize);
  QFontMetrics fontMetrics = QFontMetrics(font);
  QRect rect = fontMetrics.boundingRect(QString(text.c_str()));
  int width = rect.width();
  return width;
}

int CQGLNetworkPainter::getLabelWindowWidth(int width)
{
  int exponent = static_cast<int>(ceil(log2(width + 2.0)));

  if (exponent < 6)
    {
      exponent = 6;
    }

  width = static_cast<int>(pow(2.0, exponent + 1));
  return width;
}

void CQGLNetworkPainter::createTextureForAllLabels()
{
  std::map<std::string, RGTextureSpec *>::iterator it = labelTextureMap.begin(), endit = labelTextureMap.end();

  while (it != endit)
    {
      delete[] it->second->textureData;
      delete it->second;
      ++it;
    }

  labelTextureMap.clear();
  unsigned int i = 0;

  for (i = 0; i < viewerLabels.size(); i++)
    {
      C_INT32 fontSize = mFontsize;
      RGTextureSpec *pTexture = RG_createTextureForText(viewerLabels[i].getText(), mFontname, fontSize);
      labelTextureMap.insert(std::pair<std::string, RGTextureSpec *>
                             (viewerLabels[i].getText(),
                              pTexture));
    }
}

RGTextureSpec *CQGLNetworkPainter::getTextureForText(const std::string &text, const std::string &fontName, unsigned int fontSize)
{
  std::map<std::string, RGTextureSpec *>::iterator it;
  it = labelTextureMap.find(text);
  RGTextureSpec *texSpec = NULL;

  if (it != labelTextureMap.end())
    {
      texSpec = ((*it).second);
    }
  else
    {
      texSpec = RG_createTextureForText(text, fontName, fontSize);
      labelTextureMap.insert(std::pair<std::string, RGTextureSpec *>(text, texSpec));
    }

  return texSpec;
}

RGTextureSpec *CQGLNetworkPainter::RG_createTextureForText(const std::string &text, const std::string &fontName, unsigned int fontSize)
{
  QFont font(QString(fontName.c_str()), fontSize);
  QFontMetrics fontMetrics = QFontMetrics(font);
  QRect rect = fontMetrics.boundingRect(QString(text.c_str()));
  int width = rect.width();
  int height = rect.height();
  int exponent = static_cast<int>(ceil(log2(width + 2.0)));

  if (exponent < 6)
    {
      exponent = 6;
    }

  width = static_cast<int>(pow(2.0, exponent + 1));
  exponent = static_cast<int>(ceil(log2(height + 2.0)));

  if (exponent < 6)
    {
      exponent = 6;
    }

  height = static_cast<int>(pow(2.0, exponent + 1));
  QPixmap pixmap(width, height);
  pixmap.fill(QColor(255, 255, 255));
  QGraphicsScene scene(0.0, 0.0, width, height);
  QGraphicsTextItem *pTextItem = scene.addText(FROM_UTF8(text), font);
  pTextItem->setDefaultTextColor(QColor(0, 0, 0));
  // also move one to the right and one down to generate one column
  // and one row of transparent pixels
  pTextItem->moveBy(1.0, 1.0);
  QPainter painter(&pixmap);
  scene.render(&painter);
  RGTextureSpec *texture = new RGTextureSpec();
  texture->textureData = new GLubyte[height * width];
  texture->textureWidth = width;
  texture->textureHeight = height;
  texture->textWidth = rect.width();
  texture->textHeight = rect.height();
  QImage image = pixmap.toImage(); // UR
  // write the texture to a file to check if they were created correctly
  //bool tmpRes=image.save(text+".png","PNG");
  //assert(tmpRes == true);
  int i, j;
  int firstWhitePixel = height;
  char pixelValue;
  QRgb pixel;

  for (i = 0; i < height; ++i)
    {
      for (j = 0; j < width; ++j)
        {
          pixel = image.pixel(j, i);
          pixelValue = static_cast<unsigned char>(255 - (qRed(pixel) + qGreen(pixel) + qBlue(pixel)) / 3);
          texture->textureData[i * width + j] = pixelValue;

          if (pixelValue != 0)
            {
              if (firstWhitePixel == height)
                {
                  firstWhitePixel = i;
                }
            }
        }
    }

  texture->textYOffset = firstWhitePixel;
  // write the actual texture to a file
  //texture->save(text+".tga");
  return texture;
}

void CQGLNetworkPainter::drawStringAt(std::string s, C_FLOAT64 x, C_FLOAT64 y, C_FLOAT64 w, C_FLOAT64 h, QColor bgCol)
{
  glColor4fv(mTextColor); // black
  QString str(FROM_UTF8(s));
  QFontMetrics mfm = QFontMetrics(mf);
  QRect bbox = mfm.boundingRect(FROM_UTF8(s)); // bounding rectangle for text in certain size
  int w2 = round2powN(bbox.width()); // look for smallest w2 = 2^^k with n > w2
  int h2 = round2powN(bbox.height() + 2); // look for smallest h2 = 2^^k with n > h2

  while (h2 > h)
    {
      // reduce font size in order to avoid problems with size of texture image
      this->mFontsize--;
      this->mFontsizeDouble = (double) this->mFontsize;
      mf.setPointSize(this->mFontsize);
      const QFont &mfRef = mf;
      QFontMetrics mfm = QFontMetrics(mfRef);
      bbox = mfm.boundingRect(FROM_UTF8(s));
      w2 = round2powN(bbox.width());
      h2 = round2powN(bbox.height() + 2);
    }

  QRect c(0, 0, w2, h2);
  QPixmap pm(w2, h2);
  pm.fill(bgCol);
  QPainter painter2(&pm);
  painter2.setPen(Qt::black);
  painter2.setFont(mf);
  painter2.drawText(c, Qt::AlignCenter, FROM_UTF8(s));
  painter2.end();
  QImage img = pm.toImage();
  QImage timg = QGLWidget::convertToGLFormat(img);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, timg.width(), timg.height(), 0,
               GL_RGBA, GL_UNSIGNED_BYTE, timg.bits());
  double xoff = (w - w2) / 2.0;
  double yoff = (h - h2) / 2.0;
  xoff = 0;
  yoff = 0;
  glRasterPos2f(x + xoff, y + h - yoff);
  glDrawPixels(w2, h2, GL_RGBA, GL_UNSIGNED_BYTE, timg.bits());
}

int CQGLNetworkPainter::round2powN(double d)
{
  int n = (int)(ceil(d));
  int p = 1;
  int maxP = 12; // max size of images 2*12

  while ((p <= maxP) && (n > pow(2.0, p)))
    p++;

  return (int)pow(2.0, p);
}

void CQGLNetworkPainter::setItemAnimated(std::string key, bool animatedP)
{
  if (!animatedP)
    {
      setOfDisabledMetabolites.insert(key);
      C_FLOAT64 midValue = (pParentLayoutWindow->getMinNodeSize() + pParentLayoutWindow->getMaxNodeSize()) / 2.0; // node size used here is set to mid between min and max node size (for reactants that are not animated)
      setConstantNodeSizeForAllSteps(key, midValue);
    }
  else
    {
      setOfDisabledMetabolites.erase(key);
      rescaleNode(key, pParentLayoutWindow->getMinNodeSize(), pParentLayoutWindow->getMaxNodeSize(), pParentLayoutWindow->getScalingMode());
    }

  this->showStep(pParentLayoutWindow->getCurrentStep());
}

void CQGLNetworkPainter::rescaleDataSetsWithNewMinMax(C_FLOAT64 /* oldMin */, C_FLOAT64 /* oldMax */, C_FLOAT64 newMin, C_FLOAT64 newMax, CVisParameters::SCALING_MODE scaleMode)
{
  unsigned int s; // step number
  C_FLOAT64 val, val_new;
  setOfConstantMetabolites.clear();

  for (s = 0; s < mDataSets.size(); s++) // for all steps
    {
      CDataEntity &dataSet = mDataSets[s];
      unsigned int i;

      for (i = 0; i < viewerNodes.size(); i++) // iterate over string values (node keys)
        {
          // get old value
          val = dataSet.getValueForSpecies(viewerNodes[i]);
          C_FLOAT64 a = 0.0, b = 1.0;

          if (pParentLayoutWindow != NULL)
            {
              if (scaleMode == CVisParameters::INDIVIDUAL_SCALING)
                {
                  a = pSummaryInfo->getMinForSpecies(viewerNodes[i]);
                  b = pSummaryInfo->getMaxForSpecies(viewerNodes[i]);
                }
              else // scaleMode == CVisParameters::GLOBAL_SCALING
                {
                  a = pSummaryInfo->getMinOverallConcentration();
                  b = pSummaryInfo->getMaxOverallConcentration();
                }
            }

          C_FLOAT64 val_orig;

          if ((b - a) > CVisParameters::EPSILON)
            {
              val_orig = dataSet.getOrigValueForSpecies(viewerNodes[i]); // get original value
              // now scale value
              val_new = newMin + ((val_orig - a) / (b - a) * (newMax - newMin));
            }
          else
            {
              // no scaling if differences are too small, just set mid value
              val_new = (newMax + newMin) / 2.0;

              if (s == 0) // only insert once into set
                setOfConstantMetabolites.insert(viewerNodes[i]);
            }

          dataSet.putValueForSpecies(viewerNodes[i], val_new);
        }
    }

  // if there is no time course data, we set all values to 0.0
  if (mDataSets.size() == 0)
    {
      CDataEntity dataSet;
      unsigned int i;

      for (i = 0; i < viewerNodes.size(); i++) // iterate over string values (node keys)
        {
          dataSet.putValueForSpecies(viewerNodes[i], 0.0);
        }

      mDataSets.push_back(dataSet);
    }
}

void CQGLNetworkPainter::rescaleNode(std::string key, C_FLOAT64 newMin, C_FLOAT64 newMax, CVisParameters::SCALING_MODE scaleMode)
{
  // this is called if a species which has been disabled in the animation is reenabled
  unsigned int s; // step number
  C_FLOAT64 val, val_new;
  setOfConstantMetabolites.clear();

  for (s = 0; s < mDataSets.size(); s++) // for all steps
    {
      CDataEntity &dataSet = mDataSets[s];
      // get old value
      val = dataSet.getValueForSpecies(key);
      C_FLOAT64 a = 0.0, b = 1.0;

      if (pParentLayoutWindow != NULL)
        {
          if (scaleMode == CVisParameters::INDIVIDUAL_SCALING)
            {
              a = pSummaryInfo->getMinForSpecies(key);
              b = pSummaryInfo->getMaxForSpecies(key);
            }
          else // scaleMode == CVisParameters::GLOBAL_SCALING
            {
              a = pSummaryInfo->getMinOverallConcentration();
              b = pSummaryInfo->getMaxOverallConcentration();
            }
        }

      C_FLOAT64 val_orig;

      if ((b - a) > CVisParameters::EPSILON)
        {
          val_orig = dataSet.getOrigValueForSpecies(key); // get original value
          // now scale value
          val_new = newMin + ((val_orig - a) / (b - a) * (newMax - newMin));
        }
      else
        {
          // no scaling if differences are too small, just set mid value
          val_new = (newMax + newMin) / 2.0;

          if (s == 0) // only insert once into set
            setOfConstantMetabolites.insert(key);
        }

      dataSet.putValueForSpecies(key, val_new);
    }
}

void CQGLNetworkPainter::setConstantNodeSizeForAllSteps(std::string key, C_FLOAT64 val)
{
  unsigned int s; // step number

  for (s = 0; s < mDataSets.size(); s++) // for all steps
    {
      CDataEntity &dataSet = mDataSets[s];
      dataSet.putValueForSpecies(key, val);
    }
}

void CQGLNetworkPainter::setConstantNodeSize(std::string key, C_FLOAT64 val)
{
  unsigned int s; // step number
  setOfConstantMetabolites.clear();

  for (s = 0; s < mDataSets.size(); s++) // for all steps
    {
      CDataEntity &dataSet = mDataSets[s];
      // get old value
      dataSet.putValueForSpecies(key, val);
    }
}

// INFO: to rescale an interval [a..b] to another interval [x..y] the following formula is used: (val_old in [a..b]
// val_new = x + ((val_old - a) * (y - x) / (b - a))

void CQGLNetworkPainter::rescaleDataSets(CVisParameters::SCALING_MODE scaleMode)
{
  unsigned int s; // step number
  C_FLOAT64 val, val_new;
  setOfConstantMetabolites.clear();

  for (s = 0; s < mDataSets.size(); s++)
    {
      CDataEntity &dataSet = mDataSets[s];
      unsigned int i;
      // try to get VisParameters from parent (CQLayoutMainWindow)
      C_FLOAT64 minNodeSize = 10;
      C_FLOAT64 maxNodeSize = 100;

      if (pParentLayoutWindow != NULL)
        {
          if (pParentLayoutWindow->getMappingMode() == CVisParameters::COLOR_MODE)
            {
              minNodeSize = 0.0;
              maxNodeSize = 1.0; // 456 color values from black to red to yellow
            }
          else
            {
              minNodeSize = pParentLayoutWindow->getMinNodeSize();
              maxNodeSize = pParentLayoutWindow->getMaxNodeSize();
            }
        }

      for (i = 0; i < viewerNodes.size(); i++) // iterate over string values (node keys)
        {
          // get old value
          val = dataSet.getValueForSpecies(viewerNodes[i]);

          if ((scaleMode == CVisParameters::INDIVIDUAL_SCALING) &&
              (pParentLayoutWindow != NULL))
            {
              // global mode -> individual mode
              // first get to original value
              C_FLOAT64 orig_value = dataSet.getOrigValueForSpecies(viewerNodes[i]);

              // recalculation of original value
              if ((pSummaryInfo->getMaxForSpecies(viewerNodes[i]) - pSummaryInfo->getMinForSpecies(viewerNodes[i])) > CVisParameters::EPSILON)
                {
                  // now rescale
                  val_new = ((orig_value - pSummaryInfo->getMinForSpecies(viewerNodes[i])) *
                             (maxNodeSize - minNodeSize) /
                             (pSummaryInfo->getMaxForSpecies(viewerNodes[i]) - pSummaryInfo->getMinForSpecies(viewerNodes[i])))
                            + minNodeSize;
                }
              else
                {
                  val_new = (maxNodeSize + minNodeSize) / 2.0;

                  if (s == 0) // only insert once into set
                    setOfConstantMetabolites.insert(viewerNodes[i]);
                }
            }
          else
            {
              // individual mode -> global mode
              C_FLOAT64 orig_value = dataSet.getOrigValueForSpecies(viewerNodes[i]);

              // first calculate original value
              if ((pSummaryInfo->getMaxOverallConcentration() - pSummaryInfo->getMinOverallConcentration()) > CVisParameters::EPSILON)
                {
                  // now rescale
                  val_new = ((orig_value - pSummaryInfo->getMinOverallConcentration()) *
                             (maxNodeSize - minNodeSize) /
                             (pSummaryInfo->getMaxOverallConcentration() - pSummaryInfo->getMinOverallConcentration()))
                            + minNodeSize;
                }
              else
                val_new = (maxNodeSize + minNodeSize) / 2.0;
            }

          dataSet.putValueForSpecies(viewerNodes[i], val_new);
        }
    }
}

//tries to load data from time series,
//if this is successful true is returned, else false
bool CQGLNetworkPainter::createDataSets()
{
  int counter = 0;
  bool loadDataSuccessful = false;
  CDataModel *pDataModel = CQNewMainWindow::dataModel(parent());

  if (pDataModel != NULL)
    {
      CTrajectoryTask *ptask = dynamic_cast< CTrajectoryTask * >(&pDataModel->getTaskList()->operator[]("Time-Course"));
      const CTimeSeries *pTimeSer = &ptask->getTimeSeries();
      CTimeSeries dummyTimeSeries;

      if (pTimeSer->getRecordedSteps() == 0)
        {
          // create a dummy time series from the current state
          dummyTimeSeries.allocate(1);
          CObjectInterface::ContainerList tmpV;
          tmpV.push_back(pDataModel);
          dummyTimeSeries.compile(tmpV);
          dummyTimeSeries.output(COutputInterface::DURING);
          pTimeSer = &dummyTimeSeries; // point to the dummy time series
        }

      if (pTimeSer->getNumVariables() > 0)
        {
          mDataSets.clear(); // remove old data sets
          pSummaryInfo = new CSimSummaryInfo(pTimeSer->getRecordedSteps(), pTimeSer->getNumVariables(),
                                             pTimeSer->getConcentrationData(pTimeSer->getRecordedSteps() - 1, 0) - pTimeSer->getConcentrationData(0, 0));
          unsigned int i;
          unsigned int t;
          C_FLOAT64 val;
          std::string name;
          std::string objKey;
          std::string ndKey;
          C_FLOAT64 minR;
          C_FLOAT64 maxR;
          C_FLOAT64 maxAll = 0.0;

          // now get some info about the data set such as the maximum concentration values for each reactant
          for (i = 0; i < pTimeSer->getNumVariables(); i++) // iterate on reactants
            {
              maxR = - std::numeric_limits< C_FLOAT64 >::max();
              minR = std::numeric_limits< C_FLOAT64 >::max();
              name = pTimeSer->getTitle(i);
              objKey = pTimeSer->getKey(i);
              std::map<std::string, std::string>::iterator iter = keyMap.find(objKey);

              if (iter != keyMap.end())
                {
                  // if there is a node (key)
                  ndKey = (keyMap.find(objKey))->second;

                  for (t = 0; t < pTimeSer->getRecordedSteps(); t++) // iterate on time steps t=0..n
                    {
                      val = pTimeSer->getConcentrationData(t, i);

                      if (val > maxR)
                        maxR = val;

                      if (val < minR)
                        minR = val;
                    }

                  pSummaryInfo->storeMax(ndKey, maxR);
                  pSummaryInfo->storeMin(ndKey, minR);

                  if (maxR > maxAll)
                    maxAll = maxR;
                }
            }

          pSummaryInfo->setMaxOverallConcentration(maxAll);
          // now create data sets for visualization/animation
          // try to get VisParameters from parent (CQLayoutMainWindow)
          C_FLOAT64 minNodeSize = 10;
          C_FLOAT64 maxNodeSize = 100;

          if (pParentLayoutWindow != NULL)
            {
              minNodeSize = pParentLayoutWindow->getMinNodeSize();
              maxNodeSize = pParentLayoutWindow->getMaxNodeSize();
            }

          for (t = 0; t < pTimeSer->getRecordedSteps(); t++)  // iterate on time steps t=0..n
            {
              CDataEntity dataSet;

              for (i = 0; i < pTimeSer->getNumVariables(); i++) // iterate on reactants
                {
                  objKey = pTimeSer->getKey(i); // object key os SBML species
                  std::map<std::string, std::string>::iterator iter = keyMap.find(objKey);

                  if (iter != keyMap.end())
                    {
                      // if there is a node (key)
                      ndKey = (keyMap.find(objKey))->second; // key of graphical node
                      val = pTimeSer->getConcentrationData(t, i); // get concentration of species i at time point t
                      C_FLOAT64 scaledVal;

                      // now scale value;
                      if (pParentLayoutWindow->getScalingMode() == CVisParameters::INDIVIDUAL_SCALING)
                        {
                          minR = pSummaryInfo->getMinForSpecies(ndKey);
                          maxR = pSummaryInfo->getMaxForSpecies(ndKey);
                        }
                      else
                        {
                          // == CVisParameters.GLOBAL_SCALING
                          minR = pSummaryInfo->getMinOverallConcentration();
                          maxR = pSummaryInfo->getMaxOverallConcentration();
                        }

                      if ((maxR - minR) > CVisParameters::EPSILON)
                        scaledVal = minNodeSize +
                                    (((maxNodeSize - minNodeSize) / (maxR - minR))
                                     * (val - minR));
                      else
                        scaledVal = (maxNodeSize + minNodeSize) / 2.0;

                      // put scaled value in data entity (collection of scaled values for one step)
                      dataSet.putValueForSpecies(ndKey, scaledVal);
                      dataSet.putOrigValueForSpecies(ndKey, val);
                    }
                }

              // now collect data set
              mDataSets.push_back(dataSet);
              counter++;
            }

          loadDataSuccessful = true;
        }
    }

  this->mDataPresentP = loadDataSuccessful;

  if (loadDataSuccessful)
    {
      // if loading was successful, parent should create data table to show it in its window
      if (!mDataSets.empty())
        {
          pParentLayoutWindow->insertValueTable(mDataSets[0]);
        }
    }

  return loadDataSuccessful;
}

size_t CQGLNetworkPainter::getNumberOfSteps() const
{
  return mDataSets.size();
}

size_t CQGLNetworkPainter::getCurrentStep() const
{
  return this->stepShown;
}

void CQGLNetworkPainter::runAnimation()
{
  this->mLabelShape = CIRCLE;

  if (mDataSets.empty())
    {
      this->createDataSets(); // load data if this was not done before
    }

  // try to get VisParameters from parent (CQLayoutMainWindow)
  C_INT16 stepsPerSecond = 10;

  if (pParentLayoutWindow != NULL)
    {
      pParentLayoutWindow->setAnimationRunning(true);
      stepsPerSecond = pParentLayoutWindow->getStepsPerSecond();
    }

  regularTimer->setSingleShot(false);
  regularTimer->start((int)(1000 / stepsPerSecond)); // emit signal in chosen frame rate
}

void CQGLNetworkPainter::triggerAnimationStep()
{
  size_t numberOfSteps = 100;
  bool animationRunning = true;

  if (pParentLayoutWindow != NULL)
    {
      //check whether animation is running
      animationRunning = pParentLayoutWindow->getAnimationRunning();
    }

  numberOfSteps = getNumberOfSteps();

  if ((stepShown <= numberOfSteps) &&
      (animationRunning))
    {
      // set value in slider
      emit stepChanged((int) stepShown);
      this->stepShown++;
    }
  else
    {
      regularTimer->stop();
      emit endOfAnimationReached();
    }
}

CDataEntity *CQGLNetworkPainter::getDataSetAt(size_t stepNumber)
{
  CDataEntity *pDataSet = NULL;

  if (stepNumber < mDataSets.size())
    {
      pDataSet = &(mDataSets[stepNumber]);
    }

  return pDataSet;
}

void CQGLNetworkPainter::showStep(size_t stepNumber)
{
  this->stepShown = stepNumber;

  if (this->mLabelShape != CIRCLE)
    this->mLabelShape = CIRCLE;

  if (stepNumber < mDataSets.size())
    {
      CDataEntity dataSet = mDataSets[stepNumber];
      unsigned int i;

      for (i = 0; i < viewerNodes.size(); i++)
        {
          if (pParentLayoutWindow != NULL)
            {
              double val = dataSet.getOrigValueForSpecies(viewerNodes[i]);
              // do the scaling here instead of elsewhere
              double a, b;

              if (mScaleMode == CVisParameters::INDIVIDUAL_SCALING)
                {
                  a = pSummaryInfo->getMinForSpecies(viewerNodes[i]);
                  b = pSummaryInfo->getMaxForSpecies(viewerNodes[i]);
                }
              else // mScaleMode == CVisParameters::GLOBAL_SCALING
                {
                  a = pSummaryInfo->getMinOverallConcentration();
                  b = pSummaryInfo->getMaxOverallConcentration();
                }

              if ((b - a) > CVisParameters::EPSILON)
                {
                  val = (val - a) / (b - a);
                }
              else
                {
                  // no scaling if differences are too small, just set mid value
                  val = 0.5;
                  setOfConstantMetabolites.insert(viewerNodes[i]);
                }

              if (pParentLayoutWindow->getMappingMode() != CVisParameters::COLOR_MODE)
                {
                  // no color mode
                  if (val != -std::numeric_limits< C_FLOAT64 >::max())
                    {
                      if (std::isnan(val)) // test for NaN
                        {
                          std::map<std::string, CGraphNode>::iterator itNodeObj = nodeMap.find(viewerNodes[i]);

                          if (itNodeObj != nodeMap.end())
                            {
                            }

                          setNodeSize(viewerNodes[i], CVisParameters::DEFAULT_NODE_SIZE);
                        }
                      else
                        {
                          if (setOfDisabledMetabolites.find(viewerNodes[i]) == setOfDisabledMetabolites.end())
                            {
                              double min = pParentLayoutWindow->getMinNodeSize();
                              double max = pParentLayoutWindow->getMaxNodeSize();
                              setNodeSize(viewerNodes[i], min + val * (max - min));
                            }
                          else
                            {
                              setNodeSize(viewerNodes[i], CVisParameters::DEFAULT_NODE_SIZE);
                            }
                        }
                    }
                }
              else // COLOR_MODE
                {
                  // TODO the call to setNodeSize should not be necessary since the nodes don't change in size during a color coded
                  // TODO animation, so the arrow heads don't have to be recalculated
                  setNodeSize(viewerNodes[i], CVisParameters::DEFAULT_NODE_SIZE);

                  if (val != -std::numeric_limits< C_FLOAT64 >::max())
                    {
                      if (std::isnan(val)) // test for NaN
                        {
                          setNodeSize(viewerNodes[i], CVisParameters::DEFAULT_NODE_SIZE);
                        }
                      else
                        {
                          setNodeSizeWithoutChangingCurves(viewerNodes[i], val);
                        }
                    }
                }
            }
        }
    }

  this->drawGraph();
}

void CQGLNetworkPainter::setNodeSizeWithoutChangingCurves(std::string key, C_FLOAT64 val)
{
  std::map<std::string, CGraphNode>::iterator nodeIt;
  nodeIt = nodeMap.find(key);

  if (nodeIt != nodeMap.end())
    (*nodeIt).second.setSize(val);
}

// set node sizes according to data set and change curves (meaning end points of curve segments) to nodes
void CQGLNetworkPainter::setNodeSize(std::string key, C_FLOAT64 val)
{
  // curves to nodes are changed, arrows are created newly
  nodeArrowMap.clear();
  std::map<std::string, CGraphNode>::iterator nodeIt;
  nodeIt = nodeMap.find(key);

  if (nodeIt != nodeMap.end())
    (*nodeIt).second.setSize(val);

  // now adaptCurves pointing to nodes
  std::pair<std::multimap<std::string, CGraphCurve>::iterator, std::multimap<std::string, CGraphCurve>::iterator> curveRangeIt;;
  curveRangeIt = nodeCurveMap.equal_range(key);
  std::multimap<std::string, CGraphCurve>::iterator curveIt;
  curveIt = curveRangeIt.first;

  while (curveIt != curveRangeIt.second)
    {
      CGraphCurve *pCurve = & (*curveIt).second;

      if (pCurve != NULL && pCurve->getNumCurveSegments() > 0)
        {
          CLLineSegment *pLastSeg = pCurve->getSegmentAt(pCurve->getNumCurveSegments() - 1); // get pointer to last segment
          // move end point of segment along the line from the circle center(=from) to the current end point of the last segment
          // so that it lies on the border of the circle
          CLPoint to;

          if (pLastSeg->isBezier())
            {
              to = pLastSeg->getBase2();
              CLPoint p = pLastSeg->getEnd();

              // check if the second base point and the endpoint are identical
              if (fabs(p.getX() - to.getX() + p.getY() - to.getY()) < 1e-8)
                {
                  // if yes, take the first basepoint
                  to = pLastSeg->getBase1();

                  // if they are still identical take the start point because
                  // it is a straight line
                  if (fabs(p.getX() - to.getX() + p.getY() - to.getY()) < 1e-8)
                    {
                      to = pLastSeg->getStart();
                    }
                }
            }
          else
            {
              to = pLastSeg->getStart();
            }

          CLPoint from = CLPoint((*nodeIt).second.getX() + ((*nodeIt).second.getWidth() / 2.0), (*nodeIt).second.getY() + ((*nodeIt).second.getHeight() / 2.0)); // center of bounding box and also of circle
          C_FLOAT64 distance = sqrt(((to.getX() - from.getX()) * (to.getX() - from.getX())) + ((to.getY() - from.getY()) * (to.getY() - from.getY())));
          C_FLOAT64 circleDist = ((*nodeIt).second.getSize() / 2.0) + 4.0; // near border
          C_FLOAT64 newX = from.getX() + ((to.getX() - from.getX()) / distance * circleDist);
          C_FLOAT64 newY = from.getY() + ((to.getY() - from.getY()) / distance * circleDist);
          pLastSeg->setEnd(CLPoint(newX, newY));
          // now insert new arrow in map
          CLPoint p = pLastSeg->getEnd();

          if (pCurve->hasArrowP())
            {
              CLLineSegment ls(to, pLastSeg->getEnd());
              CArrow *ar = new CArrow(ls, p.getX(), p.getY(), this->mCurrentZoom);
              nodeArrowMap.insert(std::pair<std::string, CArrow>
                                  (key, *ar));
              pCurve->setArrow(*ar);
              delete ar;
            }
        }

      curveIt++;
    }
}

void CQGLNetworkPainter::mapLabelsToRectangles()
{
  this->mLabelShape = RECTANGLE;
  nodeArrowMap.clear(); // map is filled with new arrows
  std::pair<std::multimap<std::string, CGraphCurve>::iterator, std::multimap<std::string, CGraphCurve>::iterator> rangeCurveIt;
  std::multimap<std::string, CGraphCurve>::iterator curveIt;
  unsigned int i;

  for (i = 0; i < viewerNodes.size(); i++)
    {
      rangeCurveIt = nodeCurveMap.equal_range(viewerNodes[i]);
      std::map<std::string, CGraphNode>::iterator nodeIt = nodeMap.find(viewerNodes[i]); // find all edges belonging to a node

      if (nodeIt != nodeMap.end())
        {
          curveIt = rangeCurveIt.first;

          while (curveIt != rangeCurveIt.second)
            {
              this->adaptCurveForRectangles(curveIt, (*nodeIt).second.getBoundingBox());
              curveIt++;
            }
        }
    }

  this->drawGraph(); // this function will draw the bounding box for each node
}

CLPoint CQGLNetworkPainter::getPointOnRectangle(CLBoundingBox r, CLPoint p)
{
  CLPoint onpoint;
  CLPoint q = r.getPosition();
  q.setX(r.getPosition().getX() + r.getDimensions().getWidth()); // q is now top right point of rectangle
  CLPoint center; // center of rectangle
  center.setX(r.getPosition().getX() + (r.getDimensions().getWidth() / 2.0));
  center.setY(r.getPosition().getY() + (r.getDimensions().getHeight() / 2.0)); //
  C_FLOAT64 qAngle = atan((q.getY() - center.getY()) / (q.getX() - center.getX()));
  C_FLOAT64 pAngle = atan((p.getY() - center.getY()) / (p.getX() - center.getX()));

  if (fabs(pAngle) < fabs(qAngle))
    {
      // intersection point is left or right side
      if (p.getX() > center.getX()) // right side
        onpoint = CLPoint(q.getX(), center.getY());
      else // left side
        onpoint = CLPoint(r.getPosition().getX(), center.getY());
    }
  else
    {
      //intersection point is top or bottom side
      if (p.getY() > center.getY()) // top side
        onpoint = CLPoint(center.getX(), r.getPosition().getY() + r.getDimensions().getHeight());
      else // bottom side
        onpoint = CLPoint(center.getX(), r.getPosition().getY());
    }

  return onpoint;
}

void CQGLNetworkPainter::mapLabelsToCircles()
{
  this->mLabelShape = CIRCLE;
  nodeArrowMap.clear(); // map is filled with new arrows
  std::pair<std::multimap<std::string, CGraphCurve>::iterator, std::multimap<std::string, CGraphCurve>::iterator> rangeCurveIt;
  std::multimap<std::string, CGraphCurve>::iterator curveIt;
  unsigned int i;

  for (i = 0; i < viewerNodes.size(); i++)
    {
      rangeCurveIt = nodeCurveMap.equal_range(viewerNodes[i]);
      std::map<std::string, CGraphNode>::iterator nodeIt = nodeMap.find(viewerNodes[i]); // find all edges belonging to a node

      if (nodeIt != nodeMap.end())
        {
          curveIt = rangeCurveIt.first;

          while (curveIt != rangeCurveIt.second)
            {
              this->adaptCurveForCircle(curveIt, (*nodeIt).second.getBoundingBox());
              curveIt++;
            }
        }
    }

  this->drawGraph();
}

// get Point on Circle border on the line from the center of the given rectangle to the given point p
CLPoint CQGLNetworkPainter::getPointOnCircle(CLBoundingBox r, CLPoint p)
{
  CLPoint center; // center of rectangle
  center.setX(r.getPosition().getX() + (r.getDimensions().getWidth() / 2.0));
  center.setY(r.getPosition().getY() + (r.getDimensions().getHeight() / 2.0));
  C_FLOAT64 distance = sqrt(((p.getX() - center.getX()) * (p.getX() - center.getX())) + ((p.getY() - center.getY()) * (p.getY() - center.getY())));
  C_FLOAT64 onPointX = center.getX() + ((p.getX() - center.getX()) / distance * CVisParameters::DEFAULT_NODE_SIZE / 2.0);
  C_FLOAT64 onPointY = center.getY() + ((p.getY() - center.getY()) / distance * CVisParameters::DEFAULT_NODE_SIZE / 2.0);
  return CLPoint(onPointX, onPointY);
}

// get Point  on the line from the center of the given rectangle to the given point p with the distance d to the circle border
CLPoint CQGLNetworkPainter::getPointNearCircle(CLBoundingBox r, CLPoint p, C_INT16 d)
{
  CLPoint center; // center of rectangle
  center.setX(r.getPosition().getX() + (r.getDimensions().getWidth() / 2.0));
  center.setY(r.getPosition().getY() + (r.getDimensions().getHeight() / 2.0));
  C_FLOAT64 distance = sqrt(((p.getX() - center.getX()) * (p.getX() - center.getX())) + ((p.getY() - center.getY()) * (p.getY() - center.getY())));
  C_FLOAT64 onPointX = center.getX() + ((p.getX() - center.getX()) / distance * ((CVisParameters::DEFAULT_NODE_SIZE / 2.0) + d));
  C_FLOAT64 onPointY = center.getY() + ((p.getY() - center.getY()) / distance * ((CVisParameters::DEFAULT_NODE_SIZE / 2.0) + d));
  return CLPoint(onPointX, onPointY);
}

// move one or two points of a curve, so that the end point of the curve ends at the circle given by the center of the bounding box (where the diagonals intersect) that is given in the parameters and that has the default size
void CQGLNetworkPainter::adaptCurveForCircle(std::multimap<std::string, CGraphCurve>::iterator it, CLBoundingBox box)
{
  CLLineSegment *pLastSeg = (*it).second.getSegmentAt((*it).second.getNumCurveSegments() - 1);
  CLPoint pointOnCircle;

  if (pLastSeg->isBezier())
    pointOnCircle = getPointNearCircle(box, pLastSeg->getBase2(), 1);
  else
    pointOnCircle = getPointNearCircle(box, pLastSeg->getStart(), 1);

  pLastSeg->setEnd(pointOnCircle);

  // create corresponding arrow, if necessary and insert it into map
  if (((*it).second).hasArrowP())
    {
      CLPoint p = pLastSeg->getEnd();
      CArrow *ar;

      if (pLastSeg->isBezier())
        {
          CLPoint to = pLastSeg->getBase2();
          CLPoint p = pLastSeg->getEnd();

          // check if the second base point and the endpoint are identical
          if (fabs(p.getX() - to.getX() + p.getY() - to.getY()) < 1e-8)
            {
              // if yes, take the first basepoint
              to = pLastSeg->getBase1();

              // if they are still identical take the start point because
              // it is a straight line
              if (fabs(p.getX() - to.getX() + p.getY() - to.getY()) < 1e-8)
                {
                  to = pLastSeg->getStart();
                }
            }

          CLLineSegment segForArrow = CLLineSegment(to, pLastSeg->getEnd());
          ar = new CArrow(segForArrow, pLastSeg->getEnd().getX(), pLastSeg->getEnd().getY(), this->mCurrentZoom);
        }
      else
        {
          ar = new CArrow(*pLastSeg, p.getX(), p.getY(), this->mCurrentZoom);
        }

      nodeArrowMap.insert(std::pair<std::string, CArrow>
                          ((*it).first, *ar));
      ((*it).second).setArrowP(true);
      ((*it).second).setArrow(*ar);
    }
}

// move one or two points of a curve, so that the end point of the curve ends at the box given in the parameters
void CQGLNetworkPainter::adaptCurveForRectangles(std::multimap<std::string, CGraphCurve>::iterator it, CLBoundingBox box)
{
  // while (it != nodeCurveMap.end()){
  CLLineSegment *pLastSeg = (*it).second.getSegmentAt((*it).second.getNumCurveSegments() - 1);
  CLPoint pointOnRect;

  if (pLastSeg->isBezier())
    pointOnRect = getPointOnRectangle(box, pLastSeg->getBase2());
  else
    pointOnRect = getPointOnRectangle(box, pLastSeg->getStart());

  pLastSeg->setEnd(pointOnRect);
  // create corresponding arrow, if necessary and insert it into map
  CLPoint p = pLastSeg->getEnd();

  if (((*it).second).hasArrowP())
    {
      CArrow *ar;

      if (pLastSeg->isBezier())
        {
          CLPoint to = pLastSeg->getBase2();
          CLPoint p = pLastSeg->getEnd();

          // check if the second base point and the endpoint are identical
          if (fabs(p.getX() - to.getX() + p.getY() - to.getY()) < 1e-8)
            {
              // if yes, take the first basepoint
              to = pLastSeg->getBase1();

              // if they are still identical take the start point because
              // it is a straight line
              if (fabs(p.getX() - to.getX() + p.getY() - to.getY()) < 1e-8)
                {
                  to = pLastSeg->getStart();
                }
            }

          CLLineSegment segForArrow = CLLineSegment(to, pLastSeg->getEnd());
          ar = new CArrow(segForArrow, pLastSeg->getEnd().getX(), pLastSeg->getEnd().getY(), this->mCurrentZoom);
        }
      else
        {
          ar = new CArrow(*pLastSeg, p.getX(), p.getY(), this->mCurrentZoom);
        }

      nodeArrowMap.insert(std::pair<std::string, CArrow>
                          ((*it).first, *ar));
      ((*it).second).setArrowP(true);
      ((*it).second).setArrow(*ar);
    }
}

// looks for the best point to make a line between a given point p and a rectangle r.
// The point to connect to should always lie on the border of the rectangle and, more specifically
// on the middle of one of the border lines

void CQGLNetworkPainter::createActions()
{
  zoomInAction = new QAction("Zoom in", this);
  zoomInAction->setShortcut(Qt::CTRL + Qt::Key_P);
  connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));
  zoomOutAction = new QAction("Zoom out", this);
  zoomOutAction->setShortcut(Qt::CTRL + Qt::Key_M);
  connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));
  setFontSizeAction = new QAction("Set Font Size", this);
  setFontSizeAction->setShortcut(Qt::CTRL + Qt::Key_F);
  connect(setFontSizeAction, SIGNAL(triggered()), this, SLOT(setFontSize()));
}

void CQGLNetworkPainter::setFontSize()
{
  FontChooser *fCh = new FontChooser(this);
  fCh->exec();
}

void CQGLNetworkPainter::zoomIn()
{
  emit signalZoomIn();
}

void CQGLNetworkPainter::zoomOut()
{
  emit signalZoomOut();
}

void CQGLNetworkPainter::zoomGraph(C_FLOAT64 zoomFactor)
{
  this->zoom(zoomFactor);
}

void CQGLNetworkPainter::zoom(C_FLOAT64 zoomFactor)
{
  this->mCurrentZoom *= zoomFactor;
  CLPoint cMax = CLPoint(this->mgraphMax.getX() * zoomFactor, this->mgraphMax.getY() * zoomFactor);

  if (pParentLayoutWindow != NULL)
    {
      C_FLOAT64 oldMin = pParentLayoutWindow->getMinNodeSize();
      C_FLOAT64 oldMax = pParentLayoutWindow->getMaxNodeSize();
      pParentLayoutWindow->setMinNodeSize(pParentLayoutWindow->getMinNodeSize() * zoomFactor);
      pParentLayoutWindow->setMaxNodeSize(pParentLayoutWindow->getMaxNodeSize() * zoomFactor);
      unsigned int i;

      if ((mDataPresentP) && (pParentLayoutWindow->getMappingMode() != CVisParameters::COLOR_MODE)) // only rescale data set values in size mode and when data to be rescaled is present
        {
          rescaleDataSetsWithNewMinMax(oldMin, oldMax, pParentLayoutWindow->getMinNodeSize(), pParentLayoutWindow->getMaxNodeSize(), pParentLayoutWindow->getScalingMode());
        }

      //scale node sizes if not in color mode
      for (i = 0; i < this->viewerNodes.size(); i++)
        {
          std::map<std::string, CGraphNode>::iterator nodeIt;
          nodeIt = nodeMap.find(viewerNodes[i]);

          if (nodeIt != nodeMap.end())
            (*nodeIt).second.scale(zoomFactor, (pParentLayoutWindow->getMappingMode() != CVisParameters::COLOR_MODE)); // change position in any way, but size only when not in color mode
        }

      //scale curves not directly pointing to a reactant/species node
      for (i = 0; i < viewerCurves.size(); i++)
        {
          this->viewerCurves[i].scale(zoomFactor);
        }

      //scale curves that are associated with a reactant/species node (i.e. directly points to it)
      for (i = 0; i < viewerNodes.size(); i++)
        {
          std::pair<std::multimap<std::string, CGraphCurve>::iterator, std::multimap<std::string, CGraphCurve>::iterator> curveRangeIt;
          std::multimap<std::string, CGraphCurve>::iterator curveIt;
          curveRangeIt = nodeCurveMap.equal_range(viewerNodes[i]);
          curveIt = curveRangeIt.first;

          while (curveIt != curveRangeIt.second)
            {
              ((*curveIt).second).scale(zoomFactor); // scale curve
              curveIt++;
            }
        }

      // common font name and size for all labels are stored in this class
      // each label size is always computed from the labels original size value
      // and scaled by currentZoom (which is the product of all zoomFactors applied so far)
      this->mFontsizeDouble = this->mFontsizeDouble * zoomFactor;
      this->mFontsize = (int)this->mFontsizeDouble;

      for (i = 0; i < viewerLabels.size(); i++)
        {
          if (!preserveMinLabelHeightP)
            this->viewerLabels[i].scale(mCurrentZoom);
          else
            {
              if ((this->viewerLabels[i].getOrigHeight() * mCurrentZoom) >= MIN_HEIGHT)
                this->viewerLabels[i].scale(mCurrentZoom);
              else
                {
                  this->mFontsizeDouble = (double) MIN_HEIGHT;
                  this->mFontsize = MIN_HEIGHT;
                  this->viewerLabels[i].adaptToHeight(MIN_HEIGHT);
                  this->viewerLabels[i].scalePosition(zoomFactor);
                }
            }
        }

      for (i = 0; i < viewerNodes.size(); i++)
        {
          std::pair<std::multimap<std::string, CArrow>::iterator, std::multimap<std::string, CArrow>::iterator> arrowRangeIt;
          std::multimap<std::string, CArrow>::iterator arrowIt;
          arrowRangeIt = nodeArrowMap.equal_range(viewerNodes[i]);
          arrowIt = arrowRangeIt.first;

          while (arrowIt != arrowRangeIt.second)
            {
              (*arrowIt).second.scale(zoomFactor); //scale arrow
              arrowIt++;
            }
        }
    }

  createTextureForAllLabels();
  this->drawGraph();
}

void CQGLNetworkPainter::setFontSizeForLabels(unsigned int fs)
{
  this->mFontsizeDouble = fs;
  this->mFontsize = (int)this->mFontsizeDouble;
  unsigned int i;

  for (i = 0; i < viewerLabels.size(); i++)
    {
      this->viewerLabels[i].adaptToHeight(fs);
    }

  createTextureForAllLabels();
  this->drawGraph();
  this->update();
}

QImage CQGLNetworkPainter::getImage()
{
  return this->grabFrameBuffer();
}

void CQGLNetworkPainter::contextMenuEvent(QContextMenuEvent *cme)
{
  QMenu *pContextMenu = new QMenu();
  pContextMenu->addAction(this->zoomInAction);
  pContextMenu->addAction(this->zoomOutAction);
  pContextMenu->addAction(this->setFontSizeAction);
  pContextMenu->popup(cme->globalPos());
  delete pContextMenu;
}

void CQGLNetworkPainter::testOpenGL()
{
  glLoadIdentity();
  glTranslatef(10.0f, 10.0f, -1.0f);
  glBegin(GL_TRIANGLES);          // Drawing Using Triangles
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 10.0f, 0.0f);    // Top
  glVertex3f(-10.0f, -10.0f, 0.0f);    // Bottom Left
  glVertex3f(10.0f, -10.0f, 0.0f);    // Bottom Right
  glEnd();
  glTranslatef(3.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);          // Draw A Quad
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-1.0f, 1.0f, 0.0f);    // Top Left
  glVertex3f(1.0f, 1.0f, 0.0f);    // Top Right
  glVertex3f(1.0f, -1.0f, 0.0f);    // Bottom Right
  glVertex3f(-1.0f, -1.0f, 0.0f);    // Bottom Left
  glEnd();       // Done Drawing The Quad
  glTranslatef(3.5f, 0.0f, 0.0f);
  glBegin(GL_POLYGON);     // Ein Polygon (in diesem Falle ein Achteck.)
  // jede Ecke bekommt eine andere Farbe
  glColor3f(1.0f, 0.0f, 0.0f); // rot
  glVertex3f(-0.5f, 1.5f, 0.0f); // obere Ecke links
  glVertex3f(0.5f, 1.5f, 0.0f); // obere Ecke rechts
  glColor3f(0.0f, 0.0f, 1.0f); // blau
  glVertex3f(1.5f, 0.5f, 0.0f); // rechte Ecke oben
  glVertex3f(1.5f, -0.5f, 0.0f); // rechte Ecke unten
  glColor3f(0.0f, 1.0f, 0.0f); // gruen
  glVertex3f(0.5f, -1.5f, 0.0f); // untere Ecke rechts
  glVertex3f(-0.5f, -1.5f, 0.0f); // untere Ecke links
  glColor3f(1.0f, 1.0f, 0.0f); // gelb
  glVertex3f(-1.5f, -0.5f, 0.0f); // linke Ecke unten
  glVertex3f(-1.5f, 0.5f, 0.0f); // linke Ecke oben
  glEnd(); // Zeichenaktion beenden
}

bool CQGLNetworkPainter::isCircleMode()
{
  if (this->mLabelShape == CIRCLE)
    {
      return true;
    }
  else
    {
      return false;
    }
}

void CQGLNetworkPainter::initializeGraphPainter(QWidget *parent)
{
  mScaleMode = CVisParameters::INDIVIDUAL_SCALING;
  mSpeciesColor[0] = 0.824f;
  mSpeciesColor[1] = 0.824f;
  mSpeciesColor[2] = 0.902f;
  mSpeciesColor[3] = 1.0f;
  mCompartmentColor[0] = 0.737f;
  mCompartmentColor[1] = 0.792f;
  mCompartmentColor[2] = 0.729f;
  mCompartmentColor[3] = 1.0f;
  mShadowColor[0] = 0.2f;
  mShadowColor[1] = 0.2f;
  mShadowColor[2] = 0.2f;
  mShadowColor[3] = 0.6f;
  mSpeciesReferenceColor[0] = 0.3f;
  mSpeciesReferenceColor[1] = 0.3f;
  mSpeciesReferenceColor[2] = 0.3f;
  mSpeciesReferenceColor[3] = 1.0f;
  mTextColor[0] = 0.0f;
  mTextColor[1] = 0.0f;
  mTextColor[2] = 0.0f;
  mTextColor[3] = 1.0f;
  mFrameColor[0] = 0.1f;
  mFrameColor[1] = 0.1f;
  mFrameColor[2] = 0.1f;
  mFrameColor[3] = 1.0f;
  mBackgroundColor[0] = 1.0f;
  mBackgroundColor[1] = 1.0f;
  mBackgroundColor[2] = 1.0f;
  mBackgroundColor[3] = 1.0f;
  mAnimatedSpeciesColor[0] = 1.0f;
  mAnimatedSpeciesColor[1] = 0.0f;
  mAnimatedSpeciesColor[2] = 0.0f;
  mAnimatedSpeciesColor[3] = 1.0f;
  mInanimatedSpeciesColor[0] = 0.75f;
  mInanimatedSpeciesColor[1] = 0.75f;
  mInanimatedSpeciesColor[2] = 1.0f;
  mInanimatedSpeciesColor[3] = 1.0f;
  mConstantSpeciesColor[0] = 0.7f;
  mConstantSpeciesColor[1] = 0.7f;
  mConstantSpeciesColor[2] = 0.7f;
  mConstantSpeciesColor[3] = 1.0f;
  mCompartmentShadowXOffset = 3.0f;
  mCompartmentShadowYOffset = 3.0f;
  // the species probably need a smaller shadow offset
  mSpeciesShadowXOffset = 2.0f;
  mSpeciesShadowYOffset = 2.0f;
  mDrawShadows = true;
  mNumCirclePoints = 30;
  mCirclePoints = calculateCirclePoints(mNumCirclePoints);
  std::vector<std::pair<float, float> > mCirclePoints;
  mCurrentZoom = 1.0;
  mCurrentPositionX = 0.0;
  mCurrentPositionY = 0.0;
  mLabelShape = RECTANGLE;
  mgraphMin = CLPoint(0.0, 0.0);
  mgraphMax = CLPoint(250.0, 250.0);
  //mFontname = "Helvetica";
  mFontname = "Arial";
  mFontsize = 12;
  mFontsizeDouble = 12.0; // to avoid rounding errors due to zooming in and out
  mDataPresentP = false;
  preserveMinLabelHeightP = true;
  mf = QFont(FROM_UTF8(mFontname));
  mf.setPointSize(this->mFontsize);
  const QFont &mfRef = mf;
  QFontMetrics mfm = QFontMetrics(mfRef);
  // parent structure: glPainter -> CQGLViewport -> splitter ->
  // vbox -> mainWindow
  QWidget *ancestor = parent->parentWidget();

  while (ancestor && dynamic_cast<CQLayoutMainWindow *>(ancestor) == NULL)
    {
      ancestor = ancestor->parentWidget();
    }

  assert(ancestor != NULL);
  connect(this, SIGNAL(stepChanged(int)), ancestor, SLOT(changeStepValue(int)));
  connect(this, SIGNAL(endOfAnimationReached()), ancestor, SLOT(endOfAnimationReached()));
  regularTimer = new QTimer(this);
  connect(regularTimer, SIGNAL(timeout()), this, SLOT(triggerAnimationStep()));
  CQLayoutMainWindow *tmp = dynamic_cast<CQLayoutMainWindow *>(ancestor);
  assert(tmp);

  if (tmp)
    pParentLayoutWindow = tmp;
  else
    pParentLayoutWindow = NULL;

  stepShown = 0;
  createActions();
}

void CQGLNetworkPainter::printNodeMap()
{
  std::map<std::string, CGraphNode>::iterator nodeIt;
  nodeIt = nodeMap.begin();

  while (nodeIt != nodeMap.end())
    {
      nodeIt++;
    }
}

void CQGLNetworkPainter::printNodeInfoForKey(std::string key)
{
  //std::map<std::string, CGraphNode>::iterator itNodeObj = nodeMap.find(key);
}

std::string CQGLNetworkPainter::getNameForNodeKey(std::string key)
{
  std::string s = "UNKNOWN";
  std::map<std::string, CGraphNode>::iterator itNodeObj = nodeMap.find(key);

  if (itNodeObj != nodeMap.end())
    s = (*itNodeObj).second.getLabelText();

  return s;
}

std::string CQGLNetworkPainter::getNodeNameEntry(int i)
{
  if (i < static_cast< int >(viewerNodes.size()))
    return viewerNodes[i];
  else
    return "";
}

void CQGLNetworkPainter::printAvailableFonts()
{
  QFontDatabase fdb;
  QStringList families = fdb.families();

  for (QStringList::Iterator f = families.begin(); f != families.end(); ++f)
    {
      QString family = *f;
      QStringList styles = fdb.styles(family);

      for (QStringList::Iterator s = styles.begin(); s != styles.end(); ++s)
        {
          QString style = *s;
          QString dstyle = "\t" + style + " (";
          QList<int> smoothies = fdb.smoothSizes(family, style);

          for (QList<int>::iterator points = smoothies.begin();
               points != smoothies.end(); ++points)
            {
              dstyle += QString::number(*points) + " ";
            }

          dstyle = dstyle.left(dstyle.length() - 1) + ")";
        }
    }
}

void CQGLNetworkPainter::setZoomFactor(C_FLOAT64 zoom)
{
  if (zoom != this->mCurrentZoom)
    {
      this->mCurrentZoom = zoom;

      if (this->isVisible())
        {
          this->updateGL();
        }
    }
}

C_FLOAT64 CQGLNetworkPainter::getZoomFactor() const
{
  return this->mCurrentZoom;
}

void CQGLNetworkPainter::setCurrentPosition(C_FLOAT64 x, C_FLOAT64 y)
{
  if (this->mCurrentPositionX != x || this->mCurrentPositionY != y)
    {
      this->mCurrentPositionX = x;
      this->mCurrentPositionY = y;
      this->update();
    }
}

void CQGLNetworkPainter::update()
{
  if (mIsInitialized)
    {
      this->resizeGL(this->width(), this->height());

      if (this->isVisible())
        {
          this->updateGL();
        }
    }
}

void CQGLNetworkPainter::setCurrentPositionX(C_FLOAT64 x)
{
  if (this->mCurrentPositionX != x)
    {
      this->mCurrentPositionX = x;
      this->update();
    }
}

void CQGLNetworkPainter::setCurrentPositionY(C_FLOAT64 y)
{
  if (this->mCurrentPositionY != y)
    {
      this->mCurrentPositionY = y;
      this->update();
    }
}

C_FLOAT64 CQGLNetworkPainter::getCurrentPositionX() const
{
  return this->mCurrentPositionX;
}

C_FLOAT64 CQGLNetworkPainter::getCurrentPositionY() const
{
  return this->mCurrentPositionY;
}

void CQGLNetworkPainter::resetView()
{
  this->setZoomFactor(1.0);
  this->setCurrentPosition(this->getGraphMin().getX(), this->getGraphMin().getY());
}

/**
 * Calculates the ratio that is needed to fit the diagram on the current viewport
 * and sets this as the zoom factor.
 * The new zoom factor is returned.
 */
double CQGLNetworkPainter::fitToScreen()
{
  double zoom = 1.0;
  const CLPoint &min = this->getGraphMin();
  const CLPoint &max = this->getGraphMax();
  double width = max.getX() - min.getX();
  double height = max.getY() - min.getY();
  GLint vp[4];
  glGetIntegerv(GL_VIEWPORT, vp);
  double wRatio = (vp[2] - vp[0]) / width;
  double hRatio = (vp[3] - vp[1]) / height;

  if (wRatio > hRatio)
    {
      zoom = hRatio;
    }
  else
    {
      zoom = wRatio;
    }

  this->setZoomFactor(zoom);
  this->setCurrentPosition(this->getGraphMin().getX(), this->getGraphMin().getY());
  return zoom;
}

void CQGLNetworkPainter::pauseAnimation()
{
  regularTimer->stop();
}

/**
 * Calculates a circle with n points.
 * The points are returned as pairs of x,y values in a vector.
 * The points are calculated for a circle with diameter 1.
 */
std::vector<std::pair<float, float> > CQGLNetworkPainter::calculateCirclePoints(unsigned int n)
{
  std::vector<std::pair<float, float> > result;
  unsigned int i;
  double angle;

  for (i = 0; i <= n; ++i)
    {
      angle = 2 * M_PI * i / n;
      result.push_back(std::pair<float, float>(float(cos(angle) * 0.5), float(sin(angle) * 0.5)));
    }

  return result;
}

/**
 * Sets the scaling mode to either global or individual scaling.
 */
void CQGLNetworkPainter::setScaleMode(CVisParameters::SCALING_MODE scaleMode)
{
  this->mScaleMode = scaleMode;
}

/**
 * New method for creating a bitmap from the animation window.
 * This method uses QPainter, QImage and QGLFrameBufferObject to draw
 * into a multisample buffer if availabel and if not, it will be single sample.
 * This way the implementation should work on more computers.
 * The image is rendered in tiles of size 128x128 which should be OK for even small
 * frame buffers and it is a multiple of 2 which is compliant with older versions of OpenGL.
 *
 * The methods get the region to be drawn and the size of the final image as parameters.
 * In addition to that, the user can specify a vectir of frame numbers to be rendered.
 * If no frame number is given, nothing is rendered.
 * If a frame number is outside the range of valid frame numbers, the last frame is rendered.
 * If the rendering was successfull, true is returned, otherwise false is returned.
 */
bool CQGLNetworkPainter::export_bitmap(double x, double y, double width, double height, unsigned int imageWidth, unsigned int imageHeight, const QString &filename, const std::vector<size_t> frames)
{
  bool result = true;

  if (!filename.isEmpty() && !frames.empty())
    {
      // set busy cursor
      QCursor oldCursor = this->cursor();
      this->setCursor(Qt::WaitCursor);
      // create a progress bar
      QProgressDialog *pProgress = new QProgressDialog("image export", "Cancel", 0, 100, this);
      QImage *pImage = NULL;
      // make the OpenGL context current
      this->makeCurrent();
      // draw tiles of size 128x128
      const unsigned int tileSize = 128;
      unsigned int numColumns = imageWidth / tileSize;
      unsigned int numRows = imageHeight / tileSize;
      //  save state
      double oldZoom = this->mCurrentZoom;
      this->mCurrentZoom = 1.0;
      double oldX = this->mCurrentPositionX;
      double oldY = this->mCurrentPositionY;
      GLint oldViewport[4];
      bool frameSet = false;
      // remember the current step
      size_t oldStep = this->stepShown;
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glMatrixMode(GL_MODELVIEW);  // Select The Modelview Matrix
      glPushMatrix();
      glGetIntegerv(GL_VIEWPORT, oldViewport);
      // create QGLFrameBufferObject and QPainter that draws into the framebuffer
      QGLFramebufferObject fbo(tileSize, tileSize, QGLFramebufferObject::CombinedDepthStencil);
      //QPainter fbopainter;
      fbo.bind();

      // create an instance of QImage and a QPainter that draws into the image
      if (fbo.isValid() && fbo.isBound())
        {
          try
            {
              pImage = new QImage(imageWidth, imageHeight, QImage::Format_RGB888);
            }
          catch (...)
            {
              pImage = NULL;
              result = false;
            }

          if (pImage->isNull())
            {
              delete pImage;
              pImage = NULL;
              result = false;
            }

          if (pImage != NULL)
            {
              QPainter p;
              // set the viewport
              glViewport(0, 0, (GLint)tileSize, (GLint)tileSize);
              //
              std::vector<size_t>::const_iterator it = frames.begin(), endit = frames.end();
              std::set<size_t> s;
              // cap frame
              size_t frame;

              while (it != endit)
                {
                  frame = *it;

                  if (frame >= mDataSets.size())
                    {
                      if (this->mDataSets.empty())
                        {
                          frame = 0;
                        }
                      else
                        {
                          frame = this->mDataSets.size();
                        }
                    }

                  s.insert(frame);
                  ++it;
                }

              pProgress->setMaximum(s.size());
              pProgress->show();
              // loop over the frames
              std::set<size_t>::const_iterator sit = s.begin(), sendit = s.end();
              unsigned int step = 0;

              while (sit != sendit)
                {
                  // the tile size doesn't change because the texture
                  // in the framebuffer should by a multiple of 2
                  // When we copy the pixels for the potential stripes on the right
                  // and at the bottom, we have to consider this
                  GLdouble xPos = (GLdouble)x, yPos = (GLdouble)y, w = (GLdouble)(width * (double)tileSize / (double)imageWidth), h = (GLdouble)height * (double)tileSize / (double)imageHeight;

                  if (pProgress->wasCanceled())
                    {
                      break;
                    }

                  // for each iteration, we need to reset the frameSet flag
                  frameSet = false;
                  p.begin(pImage);
                  frame = *sit;
                  // loop overs the rows and columns and render the tiles
                  unsigned int i, j;

                  for (i = 0; i < numRows; ++i, yPos += h, xPos = (GLdouble)x)
                    {
                      for (j = 0; j < numColumns; ++j)
                        {
                          // set the projection
                          glMatrixMode(GL_PROJECTION);    // Select The Projection Matrix
                          glLoadIdentity();             // Reset The Projection Matrix
                          gluOrtho2D((GLdouble)xPos,
                                     (GLdouble)(xPos + w),
                                     (GLdouble)(yPos + h),
                                     (GLdouble)yPos); // y: 0.0 is bottom left instead of top left as in SBML
                          glMatrixMode(GL_MODELVIEW);  // Select The Modelview Matrix

                          // create the tile
                          // If the correct frame has already been set, we only need to redraw, otherwise we
                          // need to update the frames
                          if (!frameSet)
                            {
                              this->showStep(frame);
                              frameSet = true;
                            }
                          else
                            {
                              this->drawGraph();
                            }

                          // render it into the image
                          p.drawImage(QPoint(j * tileSize, i * tileSize), fbo.toImage());
                          xPos += w;
                        }

                      if (imageWidth % tileSize != 0)
                        {
                          // there is a stripe on the right
                          // set the projection
                          glMatrixMode(GL_PROJECTION);    // Select The Projection Matrix
                          glLoadIdentity();             // Reset The Projection Matrix
                          gluOrtho2D((GLdouble)xPos,
                                     (GLdouble)(xPos + w),
                                     (GLdouble)(yPos + h),
                                     (GLdouble)yPos); // y: 0.0 is bottom left instead of top left as in SBML
                          glMatrixMode(GL_MODELVIEW);  // Select The Modelview Matrix

                          // create the tile
                          if (!frameSet)
                            {
                              this->showStep(frame);
                              frameSet = true;
                            }
                          else
                            {
                              this->drawGraph();
                            }

                          // render part of tile into the image
                          p.drawImage(QPoint(j * tileSize, i * tileSize), fbo.toImage(), QRect(QPoint(0, 0), QSize(imageWidth % tileSize, tileSize)));
                        }
                    }

                  if ((imageHeight % tileSize) != 0)
                    {
                      // create the stripe at the bottom
                      for (j = 0; j < numColumns; ++j, xPos += w)
                        {
                          // set the projection
                          glMatrixMode(GL_PROJECTION);    // Select The Projection Matrix
                          glLoadIdentity();             // Reset The Projection Matrix
                          gluOrtho2D((GLdouble)xPos,
                                     (GLdouble)(xPos + w),
                                     (GLdouble)(yPos + h),
                                     (GLdouble)yPos); // y: 0.0 is bottom left instead of top left as in SBML
                          glMatrixMode(GL_MODELVIEW);  // Select The Modelview Matrix

                          // create the tile
                          if (!frameSet)
                            {
                              this->showStep(frame);
                              frameSet = true;
                            }
                          else
                            {
                              this->drawGraph();
                            }

                          // render part of tile into the image
                          p.drawImage(QPoint(j * tileSize, i * tileSize), fbo.toImage(), QRect(QPoint(0, 0), QSize(tileSize, imageHeight % tileSize)));
                        }

                      if (imageWidth % tileSize != 0)
                        {
                          // there is a stripe on the right
                          // set the projection
                          glMatrixMode(GL_PROJECTION);    // Select The Projection Matrix
                          glLoadIdentity();             // Reset The Projection Matrix
                          gluOrtho2D((GLdouble)xPos,
                                     (GLdouble)(xPos + w),
                                     (GLdouble)(yPos + h),
                                     (GLdouble)yPos); // y: 0.0 is bottom left instead of top left as in SBML
                          glMatrixMode(GL_MODELVIEW);  // Select The Modelview Matrix

                          // create the tile
                          if (!frameSet)
                            {
                              this->showStep(frame);
                              frameSet = true;
                            }
                          else
                            {
                              this->drawGraph();
                            }

                          // render part of tile into the image
                          p.drawImage(QPoint(j * tileSize, i * tileSize), fbo.toImage(), QRect(QPoint(0, 0), QSize(imageWidth % tileSize, imageHeight % tileSize)));
                        }
                    }

                  p.end();
                  // create a new temporary filename
                  QString tmpfilename;

                  if (frames.size() > 1)
                    {
                      // add the frame number to the frame name
                      QFileInfo info(filename);
                      QString completeBaseName = info.completeBaseName();
                      QString suffix = info.suffix();
                      QString path = info.path();
                      assert(suffix == "png" || suffix == "PNG");
                      tmpfilename = path;
                      tmpfilename.append("/");
                      tmpfilename.append(completeBaseName);
                      // check how many decimals we need
                      // the largest number should be at the end of s
                      int length = ceil(log10((C_FLOAT64) * s.rbegin()) + 1);
                      tmpfilename.append(QString("%1").arg((uint)frame, (int)length, (int)10, QLatin1Char('0')));
                      tmpfilename.append(".");
                      tmpfilename.append(suffix);
                    }
                  else
                    {
                      tmpfilename = filename;
                    }

                  // save the image
                  pImage->save(tmpfilename, "PNG");
                  ++sit;
                  ++step;
                  pProgress->setValue(step);
                  QCoreApplication::processEvents();
                }

              fbo.release();
              // Reset the state
              // First we have to return to the old step
              this->mCurrentZoom = oldZoom;
              this->mCurrentPositionX = oldX;
              this->mCurrentPositionY = oldY;
              // reset the projection
              glViewport(oldViewport[0], oldViewport[1], oldViewport[2], oldViewport[3]);
              glMatrixMode(GL_MODELVIEW);  // Select The Modelview Matrix
              glPopMatrix();
              glMatrixMode(GL_PROJECTION);
              glPopMatrix();

              if (oldStep != frame)
                {
                  this->setVisible(false);
                  this->showStep(oldStep);
                  this->setVisible(true);
                  this->resizeGL(oldViewport[2], oldViewport[3]);
                }
              else
                {
                  this->resizeGL(oldViewport[2], oldViewport[3]);
                }

              delete pImage;
            }
          else
            {
              fbo.release();
            }
        }
      else
        {
          result = false;
        }

      // reset cursor
      this->setCursor(oldCursor);
      pProgress->close();
      delete pProgress;
    }
  else
    {
      result = false;
    }

  // return the result;
  return result;
}
