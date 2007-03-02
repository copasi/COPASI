// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQGLNetworkPainter.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/03/02 10:56:33 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQGLNETWORKPAINTER_H_
#define  CQGLNETWORKPAINTER_H_

//#include<iostream>
#include <qgl.h>
// #include <GL/glut.h>
// #include <GL/gl.h>
#include <qpopupmenu.h>
#include <qaction.h>
#include <qevent.h>
#include <vector>
#include <string>

#include "copasi/layout/CLBase.h"
#include "copasi/layout/CLGlyphs.h"
#include "copasi/layout/CLCurve.h"
#include "copasi/layoutUI/CArrow.h"

class CLayout;

class CQGLNetworkPainter : public QGLWidget
  {

    Q_OBJECT        // must include this if you use Qt signals/slots

  public:
    CQGLNetworkPainter(QWidget *parent = 0, const char *name = 0);

    void setGraphSize(const CLPoint & min, const CLPoint & max);
    void createGraph(CLayout *lP); // create local data structures
    void drawGraph(); // create OpenGL display list with graph objects
    void drawNode(CLMetabGlyph &n);
    void drawEdge(CLLineSegment c);
    void drawLabel(CLTextGlyph l);
    // void drawStringAt(string s, double x, double y);
    void drawArrow(CArrow a);

  private slots:
    void zoomIn();
    void zoomOut();

  private:
    CLPoint mgraphMin;
    CLPoint mgraphMax;
    std::vector<CLMetabGlyph> viewerNodes;
    std::vector<CLLineSegment> viewerCurves;
    std::vector<CArrow> viewerArrows;
    std::vector<CLTextGlyph> viewerLabels;
    GLuint graphObjList;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    void createActions();
    void zoom(double zoomFactor);
    void renderBitmapString(double x, double y, std::string s, double w, double h);

  protected:

    void initializeGraphPainter();
    void draw();
    void contextMenuEvent(QContextMenuEvent *event);
    void testOpenGL();

    void initializeGL();

    void resizeGL(int w, int h);

    void paintGL();
  };

#endif /*GLGRAPHPAINTER_H_*/
