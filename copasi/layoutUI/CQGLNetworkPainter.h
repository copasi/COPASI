// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQGLNetworkPainter.h,v $
//   $Revision: 1.66 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2008/05/28 11:57:09 $
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
#include "copasi/layoutUI/CVisParameters.h"
#include "copasi/layoutUI/RGTextureSpec.h"

#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/trajectory/CTrajectoryTask.h"

class CLayout;
class CQLayoutMainWindow;

class CQGLNetworkPainter : public QGLWidget
  {

    Q_OBJECT        // must include this if you use Qt signals/slots

  public:
    CQGLNetworkPainter(QWidget *parent = 0, const char *name = 0);
    ~CQGLNetworkPainter();

    CSimSummaryInfo *pSummaryInfo;

    void setGraphSize(const CLPoint & min, const CLPoint & max);
    const CLPoint& getGraphMin();
    const CLPoint& getGraphMax();
    void createGraph(CLayout *lP); // create local data structures
    void drawGraph(); // create OpenGL display list with graph objects
    void drawNode(CGraphNode &n);
    void drawEdge(CGraphCurve &c);
    void drawLabel(CLabel l);
    // void drawStringAt(string s, double x, double y);
    void drawArrow(CArrow a, CLMetabReferenceGlyph::Role role);

    bool createDataSets();
    bool mDataPresentP; // shows, whether time series data has been load before
    C_INT32 getNumberOfSteps();
    bool isCircleMode();

    void setNodeSize(std::string key, C_FLOAT64 val);
    void setNodeSizeWithoutChangingCurves(std::string key, C_FLOAT64 val);
    //void changeNodeSize(std::string viewerNodeKey, double newSize);

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

  private slots:
    void zoomIn();
    void zoomOut();
    void setFontSize();

  public slots:
    void triggerAnimationStep();

  signals:
    void stepChanged(C_INT32);
    void endOfAnimationReached ();

  private:
    static const C_FLOAT64 DEFAULT_NODE_SIZE;

    CLPoint mgraphMin;
    CLPoint mgraphMax;

    C_FLOAT64 currentZoom ; // current zoom factor
    bool preserveMinLabelHeightP;
    static const C_INT32 MIN_HEIGHT = 10; // min height for bounding boxes of labels (-> min font pt size)

    std::vector<std::string> viewerNodes; // contains node keys
    std::vector<CGraphCurve> viewerCurves; // contains curves defining a reaction (not directly associated with a node)
    //std::vector<CArrow> viewerArrows;
    //std::vector<CLTextGlyph> viewerLabels;
    std::vector<CLabel> viewerLabels;
    std::vector<CGraphCurve> curvesWithArrow;

    GLuint graphObjList;
    std::string mFontname;
    unsigned int mFontsize;
    double mFontsizeDouble;
    QFont mf;
    //QFontMetrics mfm;

    std::map<C_INT32, CDataEntity> dataSets;

    std::map<std::string, std::string> keyMap; // maps Copasi SBML object keys to layout node keys
    std::map<std::string, CGraphNode>nodeMap;
    std::map<std::string, std::string>labelNodeMap; // maps label keys to node keys

    std::map<std::string, RGTextureSpec*>labelTextureMap; // maps label texts to texture info
    //std::multimap<std::string, CLCurve*> curveMap; // maps mMetabGlyphKey of CLMetabReferenceGlyph to curve in reaction
    std::multimap<std::string, CGraphCurve> nodeCurveMap; // maps mKey of viewer node (CGraphNode, originally from CLMetabGlyph) to curves (stored in viewerCurves) that point to this node)
    std::multimap<std::string, CArrow> nodeArrowMap; // maps mKey of viewer node (CGraphNode, originally from CLMetabGlyph, to arrows (stored in viewerArrows) that point to thid node)
    //std::map<std::string, float> nodeSizeMap; // maps mKey of viewer node to size of this node in circular view

    std::set<std::string>setOfConstantMetabolites;
    std::set<std::string>setOfDisabledMetabolites;

    void addMetaboliteForAnimation(std::string key);
    void removeMetaboliteForAnimation(std::string key);

    //CGraphNode* findNodeWithKey(std::string nodeKey);
    //void storeCurveInCorrespondingNode(std::string nodeKey, int indx);
    //void storeCurveInCorrespondingNode(std::string nodeKey, int indx1, int indx2);

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
    //void renderBitmapString(double x, double y, std::string s, double w, double h);
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
    void resetGraphToLabelView();
    bool checkCurve(CGraphCurve *curve, CGraphCurve curveR, CLBoundingBox box);

    //bool checkCurveForArrow(CGraphCurve curve);

    enum shapeOfLabels {CIRCLE, RECTANGLE};
    shapeOfLabels mLabelShape;

    void printNodeMap();
    void printAvailableFonts();
    //CLDataSet getDataSet(C_INT32 t);
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
