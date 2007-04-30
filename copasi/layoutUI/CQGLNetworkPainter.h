// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQGLNetworkPainter.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/04/30 11:00:56 $
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
#include <qcolor.h>
#include <vector>
#include <string>
#include <map>

#include "copasi/layout/CLBase.h"
#include "copasi/layout/CLGlyphs.h"
#include "copasi/layout/CLCurve.h"
#include "copasi/layoutUI/CArrow.h"

#include "copasi/layoutUI/CGraphNode.h"

class CLayout;

class CQGLNetworkPainter : public QGLWidget
  {

    Q_OBJECT        // must include this if you use Qt signals/slots

  public:
    CQGLNetworkPainter(QWidget *parent = 0, const char *name = 0);

    void setGraphSize(const CLPoint & min, const CLPoint & max);
    void createGraph(CLayout *lP); // create local data structures
    void drawGraph(); // create OpenGL display list with graph objects
    void drawNode(CGraphNode &n);
    void drawEdge(CLCurve c);
    void drawLabel(CLTextGlyph l);
    // void drawStringAt(string s, double x, double y);
    void drawArrow(CArrow a);

    void setNodeSizes();
    //void changeNodeSize(std::string viewerNodeKey, double newSize);

    void mapLabelsToRectangles();
    void mapLabelsToCircles();

  private slots:
    void zoomIn();
    void zoomOut();

  private:
    CLPoint mgraphMin;
    CLPoint mgraphMax;
    std::vector<CGraphNode> viewerNodes;
    std::vector<CLCurve> viewerCurves;
    std::vector<CArrow> viewerArrows;
    std::vector<CLTextGlyph> viewerLabels;
    GLuint graphObjList;
    std::string mFontname;
    int mFontsize;
    double mFontsizeDouble;

    //std::multimap<std::string, CLCurve*> curveMap; // maps mMetabGlyphKey of CLMetabReferenceGlyph to curve in reaction
    std::multimap<std::string, CLCurve> nodeCurveMap; // maps mKey of viewer node (CGraphNode, originally from CLMetabGlyph, to curves (stored in viewerCurves) that point to thid node)
    std::multimap<std::string, CArrow> nodeArrowMap; // maps mKey of viewer node (CGraphNode, originally from CLMetabGlyph, to arrows (stored in viewerArrows) that point to thid node)
    //std::map<std::string, float> nodeSizeMap; // maps mKey of viewer node to size of this node in circular view

    CGraphNode* findNodeWithKey(std::string nodeKey);
    void storeCurveInCorrespondingNode(std::string nodeKey, int indx);
    void storeCurveInCorrespondingNode(std::string nodeKey, int indx1, int indx2);

    QAction *zoomInAction;
    QAction *zoomOutAction;
    void createActions();
    void zoom(double zoomFactor);
    //void renderBitmapString(double x, double y, std::string s, double w, double h);
    void drawStringAt(std::string s, C_FLOAT64 x, C_FLOAT64 y, C_FLOAT64 w, C_FLOAT64 h, QColor bgCol);
    int round2powN(double d);
    void updateGraphWithNodeSizes();
    void updateEdge(CLLineSegment line);
    void resetGraphToLabelView();

    enum shapeOfLabels {CIRCLE, RECTANGLE};
    shapeOfLabels mLabelShape;
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
