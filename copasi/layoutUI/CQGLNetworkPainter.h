// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQGLNetworkPainter.h,v $
//   $Revision: 1.75 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/15 15:04:58 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include <qmainwindow.h>
#include <qfont.h>
#include <qfontmetrics.h>
#include <qimage.h>

#include <vector>
#include <string>
#include <map>
#include <set>

#include "copasi/layout/CLBase.h"
#include "copasi/layout/CLGlyphs.h"
#include "copasi/layout/CLCurve.h"

#include "copasi/layoutUI/CLabel.h"
#include "copasi/layoutUI/CArrow.h"
#include "copasi/layoutUI/CQLayoutMainWindow.h"
#include "copasi/layoutUI/CSimSummaryInfo.h"
#include "copasi/layoutUI/CVisParameters.h"
#include "copasi/layoutUI/CDataEntity.h"
#include "copasi/layoutUI/CGraphCurve.h"
#include "copasi/layoutUI/CGraphNode.h"
#include "copasi/layoutUI/CCompartmentGraphNode.h"
#include "copasi/layoutUI/CVisParameters.h"
#include "copasi/layoutUI/RGTextureSpec.h"

#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/trajectory/CTrajectoryTask.h"

class CLayout;
class CQLayoutMainWindow;
class QResizeEvent;

class CQGLNetworkPainter : public QGLWidget
  {

    Q_OBJECT        // must include this if you use Qt signals/slots

  public:
    CQGLNetworkPainter(const QGLFormat& format, QWidget *parent = 0, const char *name = 0);
    ~CQGLNetworkPainter();

    CSimSummaryInfo *pSummaryInfo;

    void setZoomFactor(C_FLOAT64);
    C_FLOAT64 getZoomFactor() const;

    void setCurrentPosition(C_FLOAT64 x, C_FLOAT64 y);
    void setCurrentPositionX(C_FLOAT64 x);
    void setCurrentPositionY(C_FLOAT64 y);
    C_FLOAT64 getCurrentPositionX() const;
    C_FLOAT64 getCurrentPositionY() const;

    void setGraphSize(const CLPoint & min, const CLPoint & max);
    const CLPoint& getGraphMin();
    const CLPoint& getGraphMax();
    void createGraph(CLayout *lP); // create local data structures
    void drawGraph(); // create OpenGL display list with graph objects
    void drawNode(CCompartmentGraphNode &n); // draw comaprtment node as a green rectangle
    void drawNode(CGraphNode &n);
    void drawEdge(CGraphCurve &c);
    void drawArrow(CArrow a, CLMetabReferenceGlyph::Role role);

    bool createDataSets();
    bool mDataPresentP; // shows, whether time series data has been load before
    C_INT32 getNumberOfSteps();
    bool isCircleMode();

    void setNodeSize(std::string key, C_FLOAT64 val);
    void setNodeSizeWithoutChangingCurves(std::string key, C_FLOAT64 val);

    std::string getNodeNameEntry(int i);
    std::string getNameForNodeKey(std::string key);

    int getNumberOfNodeEntries(){return viewerNodes.size();}
    CDataEntity* getDataSetAt(C_INT32 stepNumber);

    void mapLabelsToRectangles();
    void mapLabelsToCircles();

    void runAnimation();
    void showStep(C_INT32 i);

    void rescaleDataSets(C_INT16 scaleMode);
    void rescaleDataSetsWithNewMinMax(C_FLOAT64 oldMin, C_FLOAT64 oldMax, C_FLOAT64 newMin, C_FLOAT64 newMax, C_INT16 scaleMode);
    void rescaleNode(std::string key, C_FLOAT64 newMin, C_FLOAT64 newMax, C_INT16 scaleMode);
    void setConstantNodeSizeForAllSteps(std::string key, C_FLOAT64 midValue);

    void setConstantNodeSize(std::string key, C_FLOAT64 val);

    void zoomGraph(C_FLOAT64 zoomFactor);
    QImage getImage();

    void setItemAnimated(std::string key, bool animatedP);

    void setFontSizeForLabels(unsigned int fs);
    C_INT16 getFontSize(){return mFontsize;}

    void update();

    void resetView();

    void pauseAnimation();

  private slots:
    void zoomIn();
    void zoomOut();
    void setFontSize();

  public slots:
    void triggerAnimationStep();

  signals:
    void stepChanged(C_INT32);
    void endOfAnimationReached ();
    void signalZoomIn();
    void signalZoomOut();

  private:
    static const double PLANE_DEPTH;

    static const C_FLOAT64 DEFAULT_NODE_SIZE;

    CLPoint mgraphMin;
    CLPoint mgraphMax;

    C_FLOAT64 mCurrentZoom ; // current zoom factor
    C_FLOAT64 mCurrentPositionX;
    C_FLOAT64 mCurrentPositionY;
    bool preserveMinLabelHeightP;
    static const C_INT32 MIN_HEIGHT = 10; // min height for bounding boxes of labels (-> min font pt size)

    std::vector<std::string> viewerNodes; // contains node keys
    std::vector<std::string> viewerCompartmentNodes; // contains node keys
    std::vector<CGraphCurve> viewerCurves; // contains curves defining a reaction (not directly associated with a node)
    std::vector<CLabel> viewerLabels;
    std::vector<CGraphCurve> curvesWithArrow;

    GLuint graphObjList;
    GLuint mDisplayLists;
    std::string mFontname;
    unsigned int mFontsize;
    double mFontsizeDouble;
    QFont mf;

    std::map<C_INT32, CDataEntity> dataSets;

    std::map<std::string, std::string> keyMap; // maps Copasi SBML object keys to layout node keys
    std::map<std::string, CGraphNode>nodeMap;
    std::map<std::string, CCompartmentGraphNode> compartmentNodeMap;
    std::map<std::string, std::string>labelNodeMap; // maps label keys to node keys

    std::map<std::string, RGTextureSpec*>labelTextureMap; // maps label texts to texture info
    std::multimap<std::string, CGraphCurve> nodeCurveMap; // maps mKey of viewer node (CGraphNode, originally from CLMetabGlyph) to curves (stored in viewerCurves) that point to this node)
    std::multimap<std::string, CArrow> nodeArrowMap; // maps mKey of viewer node (CGraphNode, originally from CLMetabGlyph, to arrows (stored in viewerArrows) that point to thid node)

    std::set<std::string> setOfConstantMetabolites;
    std::set<std::string> setOfDisabledMetabolites;

    void addMetaboliteForAnimation(std::string key);
    void removeMetaboliteForAnimation(std::string key);

    void drawColorLegend();

    C_INT32 stepShown;
    QTimer *regularTimer;
    CQLayoutMainWindow *pParentLayoutWindow;

    void adaptCurveForRectangles(std::multimap<std::string, CGraphCurve>::iterator it, CLBoundingBox box);
    void adaptCurveForCircle(std::multimap<std::string, CGraphCurve>::iterator it, CLBoundingBox box);
    CLPoint getPointOnRectangle(CLBoundingBox r, CLPoint p);
    CLPoint getPointOnCircle(CLBoundingBox r, CLPoint p);
    CLPoint getPointNearCircle(CLBoundingBox r, CLPoint p, C_INT16 d);
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *setFontSizeAction;
    void createActions();
    void zoom(double zoomFactor);
    void drawStringAt(std::string s, C_FLOAT64 x, C_FLOAT64 y, C_FLOAT64 w, C_FLOAT64 h, QColor bgCol);
    int round2powN(double d);

    void RG_drawStringAt(std::string s, C_INT32 x, C_INT32 y, C_INT32 w, C_INT32 h);
    RGTextureSpec* RG_createTextureForText(const std::string& text, const std::string& fontName, unsigned int fontSize);
    RGTextureSpec* getTextureForText(const std::string& text, const std::string& fontName, unsigned int fontSize);

    void createTextureForAllLabels();

    int getTextWidth(const std::string& text, const std::string& fontName, unsigned int fontSize);
    int getLabelWindowWidth(int width);

    void updateGraphWithNodeSizes();
    void updateEdge(CLLineSegment line);
    bool checkCurve(CGraphCurve *curve, CGraphCurve curveR, CLBoundingBox box);

    enum shapeOfLabels {CIRCLE, RECTANGLE};
    shapeOfLabels mLabelShape;

    void printNodeMap();
    void printAvailableFonts();
    GLuint textureNames[1];

  protected:
    void initializeGraphPainter(QWidget *viewportWidget);
    void draw();
    void contextMenuEvent(QContextMenuEvent *event);
    void testOpenGL();

    void initializeGL();

    void resizeGL(int w, int h);

    void paintGL();

    void printNodeInfoForKey(std::string key); // just for debugging
  };

#endif /*GLGRAPHPAINTER_H_*/
