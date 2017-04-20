// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CQGLNETWORKPAINTER_H_
#define CQGLNETWORKPAINTER_H_

//#include <QtOpenGL/qgl.h>
#include <QtOpenGL/QGLWidget>

#ifdef __APPLE__
#include "OpenGL/glu.h"
#else
#include "GL/glu.h"
#endif // __APPLE__

#include <QColor>
#include <QDialog> // for CQSimpleProgressDialog
#include <QFont>
#include <QImage>

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

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/trajectory/CTrajectoryTask.h"

class CLayout;
class CQLayoutMainWindow;
class QResizeEvent;
class QContextMenuEvent;
class QAction;
class QProgressBar;

class CQGLNetworkPainter : public QGLWidget
{

  Q_OBJECT        // must include this if you use Qt signals/slots

public:
  CQGLNetworkPainter(const QGLFormat &format, QWidget *parent = 0);
  ~CQGLNetworkPainter();

  CSimSummaryInfo *pSummaryInfo;

  void setZoomFactor(C_FLOAT64);
  C_FLOAT64 getZoomFactor() const;

  void setCurrentPosition(C_FLOAT64 x, C_FLOAT64 y);
  void setCurrentPositionX(C_FLOAT64 x);
  void setCurrentPositionY(C_FLOAT64 y);
  C_FLOAT64 getCurrentPositionX() const;
  C_FLOAT64 getCurrentPositionY() const;

  void setGraphSize(const CLPoint &min, const CLPoint &max);
  const CLPoint &getGraphMin();
  const CLPoint &getGraphMax();
  void createGraph(CLayout *lP); // create local data structures
  void drawGraph(); // create OpenGL display list with graph objects
  void drawNode(const CCompartmentGraphNode &n); // draw comaprtment node as a green rectangle
  void drawNode(CGraphNode &n);
  void drawEdge(CGraphCurve &c);
  void drawArrow(CArrow a, CLMetabReferenceGlyph::Role role);

  bool createDataSets();
  bool mDataPresentP; // shows, whether time series data has been load before
  size_t getNumberOfSteps() const;
  size_t getCurrentStep() const;
  bool isCircleMode();

  void setNodeSize(std::string key, C_FLOAT64 val);
  void setNodeSizeWithoutChangingCurves(std::string key, C_FLOAT64 val);

  std::string getNodeNameEntry(int i);
  std::string getNameForNodeKey(std::string key);

  size_t getNumberOfNodeEntries() {return viewerNodes.size();}
  CDataEntity *getDataSetAt(size_t stepNumber);

  void mapLabelsToRectangles();
  void mapLabelsToCircles();

  void runAnimation();
  void showStep(size_t i);

  void rescaleDataSets(CVisParameters::SCALING_MODE scaleMode);
  void rescaleDataSetsWithNewMinMax(C_FLOAT64 oldMin, C_FLOAT64 oldMax, C_FLOAT64 newMin, C_FLOAT64 newMax, CVisParameters::SCALING_MODE scaleMode);
  void rescaleNode(std::string key, C_FLOAT64 newMin, C_FLOAT64 newMax, CVisParameters::SCALING_MODE scaleMode);
  void setConstantNodeSizeForAllSteps(std::string key, C_FLOAT64 midValue);

  void setConstantNodeSize(std::string key, C_FLOAT64 val);

  void zoomGraph(C_FLOAT64 zoomFactor);
  QImage getImage();

  void setItemAnimated(std::string key, bool animatedP);

  void setFontSizeForLabels(unsigned int fs);
  C_INT16 getFontSize() {return mFontsize;}

  void update();

  void resetView();

  /**
   * Calculates the ratio that is needed to fit the diagram on the current viewport
   * and sets this as the zoom factor.
   * The new zoom factor is returned.
   */
  double fitToScreen();

  void pauseAnimation();

  /**
   * Sets the scaling mode to either global or individual scaling.
   */
  void setScaleMode(CVisParameters::SCALING_MODE scaleMode);

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
  bool export_bitmap(double x, double y, double width, double height, unsigned int imageWidth, unsigned int imageHeight, const QString &filename, const std::vector<size_t> frames);

private slots:
  void zoomIn();
  void zoomOut();
  void setFontSize();

public slots:
  void triggerAnimationStep();

signals:
  void stepChanged(int);
  void endOfAnimationReached();
  void signalZoomIn();
  void signalZoomOut();

private:
  static const C_FLOAT64 DEFAULT_NODE_SIZE;
  static const float COMPARTMENT_DEPTH;
  static const float COMPARTMENT_SHADOW_DEPTH;
  static const float COMPARTMENT_FRAME_DEPTH;

  static const float SPECIES_DEPTH;
  static const float SPECIES_SHADOW_DEPTH;
  static const float SPECIES_FRAME_DEPTH;

  static const float SPECIESREFERENCE_DEPTH;

  static const GLfloat MIRROR_X[16];
  static const GLfloat MIRROR_Y[16];

  GLfloat mSpeciesColor[4];
  GLfloat mCompartmentColor[4];
  GLfloat mShadowColor[4];
  GLfloat mSpeciesReferenceColor[4];
  GLfloat mTextColor[4];
  GLfloat mFrameColor[4];
  GLfloat mAnimatedSpeciesColor[4];
  GLfloat mInanimatedSpeciesColor[4];
  GLfloat mConstantSpeciesColor[4];
  GLclampf mBackgroundColor[4];

  // offset values for the shadows
  float mCompartmentShadowXOffset;
  float mCompartmentShadowYOffset;
  float mSpeciesShadowXOffset;
  float mSpeciesShadowYOffset;

  // determines if shadows are drawn or not
  bool mDrawShadows;

  unsigned int mNumCirclePoints;
  std::vector<std::pair<float, float> > mCirclePoints;

  CLPoint mgraphMin;
  CLPoint mgraphMax;

  C_FLOAT64 mCurrentZoom ; // current zoom factor
  C_FLOAT64 mCurrentPositionX;
  C_FLOAT64 mCurrentPositionY;
  bool preserveMinLabelHeightP;
  static const C_INT32 MIN_HEIGHT; // min height for bounding boxes of labels (-> min font pt size)

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

  std::vector<CDataEntity> mDataSets;

  std::map<std::string, std::string> keyMap; // maps Copasi SBML object keys to layout node keys
  std::map<std::string, CGraphNode>nodeMap;
  std::map< std::string, CCompartmentGraphNode * > compartmentNodeMap;
  std::map<std::string, std::string>labelNodeMap; // maps label keys to node keys

  std::map<std::string, RGTextureSpec *>labelTextureMap; // maps label texts to texture info
  std::multimap<std::string, CGraphCurve> nodeCurveMap; // maps mKey of viewer node (CGraphNode, originally from CLMetabGlyph) to curves (stored in viewerCurves) that point to this node)
  std::multimap<std::string, CArrow> nodeArrowMap; // maps mKey of viewer node (CGraphNode, originally from CLMetabGlyph, to arrows (stored in viewerArrows) that point to thid node)

  std::set<std::string> setOfConstantMetabolites;
  std::set<std::string> setOfDisabledMetabolites;

  void addMetaboliteForAnimation(std::string key);
  void removeMetaboliteForAnimation(std::string key);

  void drawColorLegend();

  size_t stepShown;
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
  RGTextureSpec *RG_createTextureForText(const std::string &text, const std::string &fontName, unsigned int fontSize);
  RGTextureSpec *getTextureForText(const std::string &text, const std::string &fontName, unsigned int fontSize);

  void createTextureForAllLabels();

  int getTextWidth(const std::string &text, const std::string &fontName, unsigned int fontSize);
  int getLabelWindowWidth(int width);

  void updateGraphWithNodeSizes();
  void updateEdge(CLLineSegment line);
  bool checkCurve(CGraphCurve *curve, CGraphCurve curveR, CLBoundingBox box);

  enum shapeOfLabels {CIRCLE, RECTANGLE};
  shapeOfLabels mLabelShape;

  void printNodeMap();
  void printAvailableFonts();
  GLuint textureNames[1];
  CVisParameters::SCALING_MODE mScaleMode;

  ///flag that indicates whether OpenGL was initialized
  bool mIsInitialized;

protected:
  /**
   * Calculates a circle with n points.
   * The points are returned as pairs of x,y values in a vector.
   * The points are calculated for a circle with diameter 1.
   */
  static std::vector<std::pair<float, float> > calculateCirclePoints(unsigned int n);

  /**
   * Calculates the angle of the given line and the positive x axis.
   * The returned value is in degrees.
   */
  static double calculateAngle(const CLPoint &endPoint, const CLPoint &startPoint);

  /**
   * This method creates all display lists and sets the clear color.
   * This should be called whenever a color is changed.
   */
  void initializeDisplayLists();
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
