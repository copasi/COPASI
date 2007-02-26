// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQGLNetworkPainter.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/26 16:19:20 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQGLNETWORKPAINTER_H_
#define  CQGLNETWORKPAINTER_H_

//#include<iostream>
#include <qgl.h>
#include <GL/glut.h>
// #include <GL/gl.h>
#include <qpopupmenu.h>
#include <qaction.h>
#include <qevent.h>
#include "CArrow.h"
#include "layout/CLBase.h"
#include "layout/CLGlyphs.h"
#include "layout/CLCurve.h"
#include "layout/CLayout.h"
#include <vector>
#include <string>

class CQGLNetworkPainter : public QGLWidget
  {

    Q_OBJECT        // must include this if you use Qt signals/slots

  public:
    CQGLNetworkPainter(QWidget *parent = 0, const char *name = 0)
        : QGLWidget(parent, name) {initializeGraphPainter();}

    void setGraphSize(const CLPoint & min, const CLPoint & max);
    void createGraph(CLayout *lP); // create local data structures
    void drawGraph(); // create OpenGL display list with graph objects
    void drawNode(CLMetabGlyph &n);
    void drawEdge(CLLineSegment c);
    void drawLabel(CLTextGlyph l);
    // void drawStringAt(string s, double x, double y);
    void drawArrow(arrow a);

  private slots:
    void zoomIn();
    void zoomOut();

  private:
    CLPoint mgraphMin;
    CLPoint mgraphMax;
    std::vector<CLMetabGlyph> viewerNodes;
    std::vector<CLLineSegment> viewerCurves;
    std::vector<arrow> viewerArrows;
    std::vector<CLTextGlyph> viewerLabels;
    GLuint graphObjList;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    void createActions();
    void zoom(double zoomFactor);
    void renderBitmapString(double x, double y, std::string s, double w, double h);

  protected:

    void initializeGraphPainter()
    {
      mgraphMin = CLPoint(0.0, 0.0);
      mgraphMax = CLPoint(250.0, 250.0);
      createActions();
    }
    void draw();
    void contextMenuEvent(QContextMenuEvent *event);
    void testOpenGL();

    void initializeGL()
    {
      // Set up the rendering context, define display lists etc.:

      glClearColor(1.0, 1.0, 0.94, 0.0);  // background ivory
      //glEnable(GL_DEPTH_TEST);
      glShadeModel(GL_SMOOTH);
      //glClearDepth(1.0f);           // Depth Buffer Setup
      //glDepthFunc(GL_LEQUAL);       // The Type Of Depth Test To Do
      //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculation

      graphObjList = glGenLists(1);
      glNewList(graphObjList, GL_COMPILE);
      glEndList();
      int argc = 1;
      char *argv = "SimWiz";
      glutInit(&argc, &argv);
      glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    }

    void resizeGL(int w, int h)
    {
      // setup viewport, projection etc.:
      glViewport(0, 0, (GLint)w, (GLint)h);

      glMatrixMode(GL_PROJECTION);    // Select The Projection Matrix
      glLoadIdentity();             // Reset The Projection Matrix
      //gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
      // Calculate The Aspect Ratio Of The Window
      //gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
      //GLfloat x = (GLfloat)w / h;
      //glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
      gluOrtho2D((GLdouble)mgraphMin.getX(),
                 (GLdouble)mgraphMax.getX(),
                 (GLdouble)mgraphMax.getY(),
                 (GLdouble)mgraphMin.getY()); // y: 0.0 is bottom left instead of top left as in SBML
      glMatrixMode(GL_MODELVIEW);  // Select The Modelview Matrix
    }

    void paintGL()
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
      draw();
    }
  };

#endif /*GLGRAPHPAINTER_H_*/
