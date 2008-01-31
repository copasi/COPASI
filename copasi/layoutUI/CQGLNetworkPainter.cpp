// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQGLNetworkPainter.cpp,v $
//   $Revision: 1.90 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2008/01/31 13:13:23 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qstring.h>
#include <qbitmap.h>
#include <qpainter.h>
#include <qrect.h>
#include <qpoint.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qcolor.h>
#include <qtimer.h>
#include <qcanvas.h>

#include <qfontinfo.h>
#include <qfontdatabase.h>

//#include <Q3Canvas>
//#include <Q3CanvasText>
//#include <QPainter>
//#include <QFont>
//#include <QFontMetrics>
//#include <QString>

#include <iostream>
#include <math.h>
#include <float.h>
#include <utility>

#include "copasi.h"

#if (defined WIN32 && !defined log2)
C_FLOAT64 log2(const C_FLOAT64 & __x)
{return log(__x) / log(2.0);}
#endif // WIN32

#include "CQGLNetworkPainter.h"
#include "CQLayoutMainWindow.h"

#include "UI/qtUtilities.h"
#include "layout/CLayout.h"
#include "utilities/CCopasiVector.h"
#include "layoutUI/CVisParameters.h"
#include "layoutUI/CDataEntity.h"
#include "layoutUI/BezierCurve.h"

const C_FLOAT64 CQGLNetworkPainter::DEFAULT_NODE_SIZE = 20.0;

CQGLNetworkPainter::CQGLNetworkPainter(QWidget *parent, const char *name)
    : QGLWidget(parent, name)
{initializeGraphPainter(parent);}

CQGLNetworkPainter::~CQGLNetworkPainter()
{
  std::cout << "destroy network painter" << std::endl;
}

// set graph size and reset projection to fit new size
void CQGLNetworkPainter::setGraphSize(const CLPoint & min, const CLPoint & max)
{
  mgraphMin.setX(min.getX());
  mgraphMin.setY(min.getY());
  mgraphMax.setX(max.getX());
  mgraphMax.setY(max.getY());

  this->setFixedSize((int)max.getX(), (int)max.getY());
  // now adapt viewing "volume"
  glMatrixMode(GL_PROJECTION);        // Select The Projection Matrix
  glLoadIdentity();       // Reset The Projection Matrix
  gluOrtho2D((GLdouble)mgraphMin.getX(),
             (GLdouble)mgraphMax.getX(),
             (GLdouble)mgraphMax.getY(),
             (GLdouble)mgraphMin.getY());
  glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
  std::cout << "graph size: " << (mgraphMax.getX() - mgraphMin.getX()) << " x " << (mgraphMax.getY() - mgraphMin.getY()) << std::endl;
}

void CQGLNetworkPainter::draw()
{
  //std::cout << "draw" << std::endl;
  glLoadIdentity();

  glCallList(graphObjList);

  //  ******* test object *******
  //  glTranslatef(10.0f, 10.0f, 0.0f);
  //  glBegin(GL_TRIANGLES);          // Drawing Using Triangles
  //  glColor3f(0.0f, 0.0f, 1.0f);
  //  glVertex3f(100.0f, 100.0f, 0.0f);    // Top
  //  glVertex3f(0.0f, 0.0f, 0.0f);    // Bottom Left
  //  glVertex3f(200.0f, 0.0f, 0.0f);    // Bottom Right
  //  glEnd();
  //testOpenGL();
}

//void CQGLNetworkPainter::createGraph(network *netP){
void CQGLNetworkPainter::createGraph(CLayout *lP)
{
  // copy graph to local variables
  //cout << "now create graph" << endl;
  CCopasiVector<CLMetabGlyph> nodes;
  nodes = lP->getListOfMetaboliteGlyphs();
  //viewerNodes.resize (nodes.size());
  //viewerNodes = std::vector<CGraphNode>();
  viewerNodes = std::vector<std::string>();
  unsigned int i;
  for (i = 0;i < nodes.size();i++)
    {
      //viewerNodes.push_back(CGraphNode(*nodes[i])); // local vector of nodes contains objects, not pointers
      std::string nKey = (*nodes[i]).getKey();
      std::string oKey = (*nodes[i]).getModelObjectKey();
      viewerNodes.push_back(nKey);
      nodeMap.insert(std::pair<std::string, CGraphNode>
                     (nKey,
                      CGraphNode(*nodes[i])));
      keyMap.insert(std::pair<std::string, std::string>
                    (oKey, nKey));
      //std::cout << "insert " << nKey << "  " << *nodes[i] << std::endl;
      //std::cout << "key: " << (*nodes[i]).getModelObjectKey() << std::endl;
      //std::cout << "keys:  " << oKey << "  - " << nKey << std::endl;
      //viewerNodes[i].printObject();
    }
  CCopasiVector<CLReactionGlyph> reactions;
  reactions = lP->getListOfReactionGlyphs();

  std::cout << "number of reactions: " << reactions.size() << std::endl;

  //now extract curves to draw from reaction
  viewerCurves = std::vector<CGraphCurve>();
  //first get reaction arrow
  for (i = 0;i < reactions.size();i++)
    {
      CGraphCurve curveR = CGraphCurve((reactions[i])->getCurve());
      viewerCurves.push_back(curveR);

      CCopasiVector<CLMetabReferenceGlyph> edgesToNodesOfReaction;
      edgesToNodesOfReaction = reactions[i]->getListOfMetabReferenceGlyphs();
      //std::cout << "number of edges in reaction " << i << ": "<< edgesToNodesOfReaction.size() << std::endl;
      unsigned int j2;
      for (j2 = 0;j2 < edgesToNodesOfReaction.size();j2++)
        {
          CGraphCurve curve = CGraphCurve(edgesToNodesOfReaction[j2]->getCurve());
          std::string nodeKey = "";
          if (edgesToNodesOfReaction[j2]->getMetabGlyph() != NULL) // i.e. there is an associated node
            {
              nodeKey = std::string(edgesToNodesOfReaction[j2]->getMetabGlyph()->getKey());
              //std::cout << "node key: " << nodeKey << std::endl;
              std::map<std::string, CGraphNode>::iterator itNode;
              itNode = nodeMap.find(nodeKey);
              if (itNode != nodeMap.end())
                {
                  CLBoundingBox box = (*itNode).second.getBoundingBox();
                  this->checkCurve(&curve, curveR, box);
                }
            }

          //      std::cout << "null pointer " << std::endl;
          CLMetabReferenceGlyph::Role r = edgesToNodesOfReaction[j2]->getRole();
          curve.setRole(r);
          if (edgesToNodesOfReaction[j2]->getMetabGlyph() != NULL)  // if there is an associated scpecies node look, whether an arrow has to be created
            {
              // if role is product or sideproduct, create arrow for line
              if ((r == CLMetabReferenceGlyph::PRODUCT) || (r == CLMetabReferenceGlyph::SIDEPRODUCT) || (r == CLMetabReferenceGlyph::ACTIVATOR) || (r == CLMetabReferenceGlyph::INHIBITOR) || (r == CLMetabReferenceGlyph::MODIFIER))
                {// create arrows just for edges to products or sideproducts
                  std::vector<CLLineSegment> segments = curve.getCurveSegments();
                  if (! segments.empty())
                    {
                      CLLineSegment lastSeg = segments[curve.getNumCurveSegments() - 1];
                      //std::cout << "number of segments in curve: " << curve.getNumCurveSegments() << std::endl;
                      CLPoint p = lastSeg.getEnd();
                      CArrow *ar;
                      if (lastSeg.isBezier())
                        {
                          BezierCurve *bezier = new BezierCurve();
                          std::vector<CLPoint> pts = std::vector<CLPoint>();
                          pts.push_back(lastSeg.getStart());
                          pts.push_back(lastSeg.getBase1());
                          pts.push_back(lastSeg.getBase2());
                          pts.push_back(lastSeg.getEnd());
                          std::vector<CLPoint> bezierPts = bezier->curvePts(pts);
                          C_INT32 num = bezierPts.size();
                          CLLineSegment segForArrow = CLLineSegment(bezierPts[num - 2], bezierPts[num - 1]);
                          ar = new CArrow(segForArrow, bezierPts[num - 1].getX(), bezierPts[num - 1].getY(), this->currentZoom);
                        }
                      else
                        ar = new CArrow(lastSeg, p.getX(), p.getY(), this->currentZoom);
                      //std::cout << "arrow line: " << ar->getStartOfLine() << ar->getEndOfLine() << std::endl;
                      //                   nodeArrowMap.insert(std::pair<std::string, CArrow>
                      //                                       (nodeKey, *ar));

                      curve.setArrowP(true);
                      curve.setArrow(*ar);
                      //viewerArrows.push_back(*ar);
                      //storeCurveInCorrespondingNode(nodeKey, viewerCurves.size() - 1, viewerArrows.size() - 1); //store with arrow index, see below
                    }
                }
              if (nodeKey != "")
                nodeCurveMap.insert(std::pair<std::string, CGraphCurve>
                                    (nodeKey,
                                     curve));
            }
          else
            {// if no species node is associated with the curve: just store curve
              //std::string mGKey = edgesToNodesOfReaction[j2]->getKey();
              std::cout << "reaction with curve (MetabReferenceGlyph) found which has no associated node (MetabGlyph) " << std::endl;
              viewerCurves.push_back(curve); // just collect curve in order to be shown within the graph
            }
        } // end j
    } // end i (reactions)
  //for (i=0;i<viewerNodes.size();i++)
  // std::cout << "viewer node: " << viewerNodes[i] << std::endl;
  //std::cout << "number of curves: " << viewerCurves.size() << std::endl;

  CCopasiVector<CLTextGlyph> labels;
  labels = lP->getListOfTextGlyphs();
  std::cout << "number of labels " << labels.size() << std::endl;
  viewerLabels = std::vector<CLTextGlyph>();
  std::map<std::string, CGraphNode>::iterator itNode;
  for (i = 0;i < labels.size();i++)
    {
      //std::cout << "XXXXXXXXXX: " << labels[i]->getText() << std::endl;
      labelNodeMap.insert(std::pair<std::string, std::string>
                          (labels[i]->getKey(),
                           labels[i]->getGraphicalObjectKey()));
      std::string s1 = labels[i]->getKey();
      std::string s2 = labels[i]->getGraphicalObjectKey();
      //cout << labels[i] << std::endl;
      //labels[i]->printLabel();
      viewerLabels.push_back(*labels[i]);
      //std::cout << "label " << i << " : " << labels[i]->getGraphicalObjectKey() << std::endl;
      itNode = nodeMap.find(labels[i]->getGraphicalObjectKey());
      if (itNode != nodeMap.end())
        (*itNode).second.setLabelText(labels[i]->getText());
      //std::cout << "               " << labels[i]->getText() << std::endl;
    }
  CLPoint p1 = CLPoint(0.0, 0.0);
  CLPoint p2 = CLPoint(lP->getDimensions().getWidth(), lP->getDimensions().getHeight());
  this->setGraphSize(p1, p2);
  //CQGLNetworkPainter::drawGraph();
}

// decides whether the direction of the curve has to be inverted (meaning the order of the line segments, start and end points and base points have to be inverted
void CQGLNetworkPainter::checkCurve(CGraphCurve *curve, CGraphCurve curveR, CLBoundingBox box)
{
  // first checks whether the start point or the end point of the curve is closer to the center of the box defining the reactant node
  CLPoint center; // center of bounding box for node
  center.setX(box.getPosition().getX() + (box.getDimensions().getWidth() / 2.0));
  center.setY(box.getPosition().getY() + (box.getDimensions().getHeight() / 2.0));

  // get start and end point of curve (start point of first segment and end point of last segment)
  std::vector <CLPoint> points = curve->getListOfPoints();
  if (points.size() > 1)
    {// if there are at least 2 points
      CLPoint s = points[0];
      CLPoint e = points[points.size() - 1];
      // now compute the distances from these points to the center

      C_FLOAT64 dist1 = sqrt (((center.getX() - s.getX()) * (center.getX() - s.getX())) +
                              ((center.getY() - s.getY()) * (center.getY() - s.getY())));
      C_FLOAT64 dist2 = sqrt(((center.getX() - e.getX()) * (center.getX() - e.getX())) +
                             ((center.getY() - e.getY()) * (center.getY() - e.getY())));

      if (dist1 < dist2)
        {// if the start point of the curve is closer to the node than the end point
          // the curve direction should be TOWARDS the node, not away from it
          curve->invertOrderOfPoints(); // invert the order of the points in the curve
        }
    }
}

//void CQGLNetworkPainter::storeCurveInCorrespondingNode(std::string nodeKey, int indx)
//{
//  CGraphNode *nodeP = findNodeWithKey(nodeKey);
//  if (nodeP != NULL)
//    {
//      nodeP->addCurveIndex(indx);
//}
//}

//void CQGLNetworkPainter::storeCurveInCorrespondingNode(std::string nodeKey, int indx1, int indx2)
//{
//  CGraphNode *nodeP = findNodeWithKey(nodeKey);
//  if (nodeP != NULL)
//    {
//      nodeP->addCurveIndex(indx1);
//      nodeP->addArrowIndex(indx2);
//}
//}

// look for viewer node with key nodeKey and return this element
//CGraphNode* CQGLNetworkPainter::findNodeWithKey(std::string nodeKey)
//{
//  bool nodeFound = false;
//  int numNodes = viewerNodes.size();
//  int i = 0;
//  while (!nodeFound && (i < numNodes))
//    {
//      if (viewerNodes[i].getOrigNodeKey() == nodeKey)
//        nodeFound = true;
//      else
//        i++;
//}
//  if (nodeFound)
//    return &viewerNodes[i];
//  else
//    return NULL;
//}

// create display lists
void CQGLNetworkPainter::drawGraph()
{
  //std::cout << "draw graph" << std::endl;
  // create OpenGL display list
  glNewList(graphObjList, GL_COMPILE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  unsigned int i;

  if ((pParentLayoutWindow != NULL) &&
      (pParentLayoutWindow->getMappingMode() == CVisParameters::COLOR_MODE)) // draw color legend
    {

      C_INT32 sx = 40; //start at position (sx,sy)
      C_INT32 sy = 20;
      C_INT32 w = 120; // size of legend rectangle w x h
      C_INT32 h = 15;
      C_FLOAT64 dHue = 240.0 / w;
      C_FLOAT64 hue = 0.0;

      // QGLWidget::renderText (10, sy + 15, "MIN", mf, graphObjList);
      // QGLWidget::renderText (165, sy + 15, "MAX", mf, graphObjList);
      RG_drawStringAt("MIN", 7, sy + 3, 32, 16);
      RG_drawStringAt("MAX", 165, sy + 3, 32, 16);

      C_INT16 i;
      QColor col = QColor();
      for (i = sx;i <= (w + sx);i++)
        {
          col.setHsv((int)(240 - hue), 255, 255);
          //std::cout << "------------" << std::endl;
          //std::cout << "color hsv value: "  << (int) hue << std::endl;
          //std::cout << "r: " << col.red() << "   g: " << col.green() << "   b: " << col.blue() << std::endl;
          //glColor3d((C_FLOAT64)col.red(), (C_FLOAT64)col.green(), (C_FLOAT64)col.blue()); does not work properly
          QGLWidget::qglColor(col);
          // draw colored line in rectangle
          glBegin(GL_LINES);
          glVertex2d(i, sy);
          glVertex2d(i, sy + h);
          glEnd();

          hue += dHue;
        }
    } // end color mode

  // draw curves to (reactant) nodes and arrows and circular nodes when in appropriate mode

  //std::cout << "draw node in circle mode" << std::endl;
  std::map<std::string, CGraphNode>::iterator itNode;
  std::multimap<std::string, CGraphCurve>::iterator itCurve;
  std::multimap<std::string, CArrow>::iterator itArrow;
  std::pair<std::multimap<std::string, CGraphCurve>::iterator, std::multimap<std::string, CGraphCurve>::iterator> curveRangeIt;;
  std::pair<std::multimap<std::string, CArrow>::iterator, std::multimap<std::string, CArrow>::iterator> arrowRangeIt;
  //std::cout << nodeCurveMap.size() << " elements in nodeCurveMap" << std::endl;
  for (i = 0;i < viewerNodes.size();i++)
    {
      itNode = nodeMap.find(viewerNodes[i]);
      // draw curves of node
      //std::cout << "node: " << viewerNodes[i] << std::endl;
      curveRangeIt = nodeCurveMap.equal_range(viewerNodes[i]);
      //          std::multimap<std::string, CLCurve>::iterator lowerB;
      //          std::multimap<std::string, CLCurve>::iterator upperB;
      //          lowerB = nodeCurveMap.lower_bound(viewerNodes[i]);
      //          upperB = nodeCurveMap.upper_bound(viewerNodes[i]);
      //          itCurve = lowerB;
      //          while (itCurve != upperB){
      //          drawEdge((*itCurve).second);
      //          itCurve++;
      //}

      itCurve = curveRangeIt.first;
      glColor3f(0.0f, 0.0f, 0.5f); // edges in dark blue
      while (itCurve != curveRangeIt.second)
        {
          //for(itCurve = curveRangeIt.first;itCurve==curveRangeIt.second; ++itCurve){
          drawEdge((*itCurve).second);
          itCurve++;
        }

      // draw arrows of node
      //arrowRangeIt = nodeArrowMap.equal_range(viewerNodes[i]);
      //itArrow = arrowRangeIt.first;
      //       while (itArrow != arrowRangeIt.second)
      //         {
      //           //std::cout << "draw arrow " << std::endl;
      //           drawArrow((*itArrow).second);
      //           itArrow++;
      //}
      if (this->mLabelShape == CIRCLE)
        {
          //draw node as a circle
          if (itNode != nodeMap.end())
            drawNode((*itNode).second);
        }
    }

  glColor3f(0.0f, 0.0f, 0.5f); // edges in dark blue
  for (i = 0;i < viewerCurves.size();i++) // draw edges that do not directly belong to a node (reaction curves)
    {
      drawEdge(viewerCurves[i]);
    }
  //std::cout << "number of arrows: " << viewerArrows.size() << std::endl;

  //glColor3f(0.0f,0.0f,0.5f); // arrows in dark blue
  //  for (i = 0;i < viewerArrows.size();i++)
  //    drawArrow(viewerArrows[i]);

  if (this->mLabelShape == RECTANGLE)
    {
      // debug: print fonr info
      this->mf.setPointSize(this->mFontsize);
      const QFont& mfRef = this->mf;
      QFontInfo fontInfo = QFontInfo (mfRef);
      std::cout << "family: " << fontInfo.family();
      std::cout << "  size: " << fontInfo.pointSize();
      std::cout << std::endl;
      // debug end
      for (i = 0;i < viewerLabels.size();i++)
        drawLabel(viewerLabels[i]);
    }
  else
    {// draw string next to circle (to the right)
      for (i = 0;i < viewerLabels.size();i++)
        {
          C_FLOAT64 tWid = getTextWidth(viewerLabels[i].getText(), mFontname, static_cast<int>(floor(viewerLabels[i].getHeight())));
          int labelWWid = getLabelWindowWidth(tWid);
          C_FLOAT64 nDiam = 0.0;
          C_FLOAT64 x, y;
          //XXXXXXXXXXXX
          const std::string& nodeKey = viewerLabels[i].getGraphicalObjectKey();
          if (!nodeKey.empty())
            {
              //               std::map<std::string, std::string>::iterator itNode;
              //               itNode = labelNodeMap.find(labelKey);

              //               if (itNode != labelNodeMap.end()) {// node is corresponding graphical object
              std::map<std::string, CGraphNode>::iterator itNodeObj;
              //   std::string ndKey = (*itNode).second;
              itNodeObj = nodeMap.find(nodeKey);
              if (itNodeObj != nodeMap.end())
                nDiam = (*itNodeObj).second.getSize();
              //std::cout << "size of node: " << (*itNodeObj).second.getSize() << std::endl;
              //}

              //std::cout << viewerLabels[i].getText() << " node  key: " << nodeKey << std::endl;
              C_INT32 xNdCenter = (*itNodeObj).second.getX() + ((*itNodeObj).second.getWidth() / 2.0);
              C_INT32 yNdCenter = (*itNodeObj).second.getY(); // + ((*itNodeObj).second.getHeight() / 2.0);
              //C_INT32 xLabelStartOff = tWid / 2.0;
              //std::cout << viewerLabels[i].getText() << "  text width: " << tWid << "   diameter of circle: " << nDiam << std::endl;
              if ((tWid + 4) > nDiam)
                {// label wider (+ k=4 to avoid crossing circle borders) than size of circle-> place next to circle

                  x = xNdCenter + (nDiam / 2.0) + 2.0 - ((viewerLabels[i].getWidth() - tWid) / 2.0); // + nDiam / 2.0 - ((labelWWid - (*itNodeObj).second.getWidth()) / 2.0); // node center + circle radius - texture window overhead
                  y = yNdCenter;
                }
              else
                {// place in center of circle
                  x = xNdCenter - (viewerLabels[i].getWidth() / 2.0); // - ((labelWWid - (*itNodeObj).second.getWidth()) / 2.0);
                  y = yNdCenter;
                }
            }
          else
            {// if there is no node associated, just take label position
              x = viewerLabels[i].getX();
              y = viewerLabels[i].getY();
            }
          //std::cout << viewerLabels[i].getText() << "  x: " << x << "   y: " << y << std::endl;
          // drawStringAt(viewerLabels[i].getText(), x, y, viewerLabels[i].getWidth(), viewerLabels[i].getHeight(), QColor(219, 235, 255));
          RG_drawStringAt(viewerLabels[i].getText(), static_cast<C_INT32>(x), static_cast<C_INT32>(y), static_cast<C_INT32>(viewerLabels[i].getWidth()), static_cast<C_INT32>(viewerLabels[i].getHeight()));
        }
    }

  glEndList();
  //this->updateGL();
}

// draw node as circle
void CQGLNetworkPainter::drawNode(CGraphNode &n) // draw node as filled circle
{
  float scaledValue = DEFAULT_NODE_SIZE;
  C_INT16 mappingMode = CVisParameters::SIZE_DIAMETER_MODE;
  if (pParentLayoutWindow != NULL)
    {
      mappingMode = pParentLayoutWindow->getMappingMode();
      if ((mappingMode == CVisParameters::SIZE_DIAMETER_MODE) ||
          (mappingMode == CVisParameters::SIZE_AREA_MODE))
        scaledValue = n.getSize(); // change of node size only for size mode
    }
  //std::cout << "diameter of " << n.getOrigNodeKey() << ": " << diameter << std::endl;
  //std::map<std::string, float>::iterator iter = nodeSizeMap.find(n.getKey());
  //std::cout << "find: " << n.getKey() <<std::endl;;
  //  if (iter != nodeSizeMap.end())
  //    {
  //      std::string viewerNodeKey = n.getOrigNodeKey();
  //      diameter = n.getSize();
  //      //diameter = nodeSizeMap[viewerNodeKey];
  //      std::cout << "diameter of " << n.getOrigNodeKey() << ": " << diameter << std::endl;
  //}
  glColor3f(1.0f, 0.0f, 0.0f); // red
  GLUquadricObj *qobj;
  qobj = gluNewQuadric();
  //cout << "draw node at: " << n.getX() <<  "  " << n.getY() << std::endl;

  double tx = n.getX() + (n.getWidth() / 2.0);
  double ty = n.getY() + (n.getHeight() / 2.0);
  glTranslatef((float)tx, (float)ty, 0.0f);

  //std::cout << "mapping mode: " << CVisParameters::SIZE_DIAMETER_MODE << std::endl;

  if ((mappingMode == CVisParameters::SIZE_DIAMETER_MODE) ||
      (mappingMode == CVisParameters::SIZE_AREA_MODE))
    glColor3f(1.0f, 0.0f, 0.0f); // red as default color for all nodes
  else
    {// color mapping
      QColor col = QColor();
      //std::cout << "scaled color value: " <<  (int)n.getSize()<< std::endl;
      C_INT32 colVal = (int)(240 - n.getSize());
      col.setHsv(colVal, 255, 255);
      //glColor3f(col.red(), col.green(), col.blue());
      QGLWidget::qglColor(col);
      // std::cout << "scaled color value: " <<  (int)n.getSize()<< std::endl;
      //std::cout << "red: " << col.red() << "   green: "  << col.green()  << "   blue:  " << col.blue() << std::endl;
    }

  gluDisk(qobj, 0.0, scaledValue / 2.0, 25, 2);
  glColor3f(0.0f, 0.0f, 0.0f); // black
  gluDisk(qobj, scaledValue / 2.0 - 1.0, scaledValue / 2.0, 25, 2);
  glTranslatef(-(float)tx, -(float)ty, 0.0f);
}

// draw a curve: at the moment just a line from the start point to the end point (for each segment)
void CQGLNetworkPainter::drawEdge(CGraphCurve &c)
{
  std::vector<CLLineSegment> segments = c.getCurveSegments();
  for (int k = 0;k < c.getNumCurveSegments();k++)
    {
      CLLineSegment seg = segments[k];

      CLPoint startPoint = seg.getStart();
      CLPoint endPoint = seg.getEnd();
      // for the moment do not take type of curve into account

      C_FLOAT64 x, y;
      //glColor3f(0.0f,0.0f,1.0f); // blue

      if (seg.isBezier())
        {
          //std::cout << "Bezier curve found" << std::endl;
          std::vector<CLPoint> pts = std::vector<CLPoint>();
          pts.push_back(startPoint);
          pts.push_back(seg.getBase1());
          pts.push_back(seg.getBase2());
          pts.push_back(endPoint);
          BezierCurve *bezier = new BezierCurve();
          std::vector<CLPoint> bezierPts = bezier->curvePts(pts);
          //now paint bezier as line strip
          glBegin(GL_LINE_STRIP);
          x = startPoint.getX();
          y = startPoint.getY();
          glVertex2d(x, y);
          unsigned int i;
          for (i = 0;i < bezierPts.size();i++)
            {
              //std::cout << "i: " << i << "   " << std::endl;
              x = bezierPts[i].getX();
              y = bezierPts[i].getY();
              //std::cout << "     x: " << x << "   y: " << y << std::endl;
              glVertex2d(x, y);
            }
          x = endPoint.getX();
          y = endPoint.getY();
          //glVertex2d(x, y);
          glEnd();
        }
      else
        {// just draw a straight line
          glBegin(GL_LINE_STRIP);
          x = startPoint.getX();
          y = startPoint.getY();
          glVertex2d(x, y);
          x = endPoint.getX();
          y = endPoint.getY();
          glVertex2d(x, y);
          glEnd();
        }
    }
  if (c.hasArrowP())
    drawArrow(c.getArrow(), c.getRole());
}

void CQGLNetworkPainter::drawArrow(CArrow a, CLMetabReferenceGlyph::Role role)
{
  // first get the two points defining the line segment (curve)
  CLPoint p2 = a.getStartOfLine();
  CLPoint p1 = a.getEndOfLine();
  // p1 and p2 define a line where the arrow peak can be placed onto,
  // peak should be at p1, the arrow peak is just a triangle

  // first compute parameters of equation of line and point on line where arrow intersects line
  C_FLOAT64 d1 = p2.getX() - p1.getX();
  C_FLOAT64 d2 = p2.getY() - p1.getY();
  C_FLOAT64 norm = sqrt((d1 * d1) + (d2 * d2));
  C_FLOAT64 qX = p1.getX() + (a.getArrowLength() / norm * (p2.getX() - p1.getX()));
  C_FLOAT64 qY = p1.getY() + (a.getArrowLength() / norm * (p2.getY() - p1.getY()));

  // now compute second and third point of triangle
  // first compute direction vector of orthogonal line (= norm vector of line)
  // if (x2-x1,y2-y1) is the direction vector of the line, then (y1-y2,x2-x1) is a norm vector of the line
  // to get a certain length, use the unit norm vector
  C_FLOAT64 unX = (p1.getY() - p2.getY()) / norm;
  C_FLOAT64 unY = (p2.getX() - p1.getX()) / norm;

  // for second point of triangle: walk on line from (qX,qY) in direction of norm vector
  //C_FLOAT64 p3X = qX + (unX * a.getArrowWidth());
  //C_FLOAT64 p3Y = qY + (unY * a.getArrowWidth());

  // for last point of the triangle: just go into the other direction
  //C_FLOAT64 p4X = qX - (unX * a.getArrowWidth());
  //C_FLOAT64 p4Y = qY - (unY * a.getArrowWidth());
  // now draw polygon, using vertices from triangle
  //glColor3f(0.0f, 0.0f, 1.0f); // set arrow color: blue
  // now create triangle;
  //cout << "arrow triangle: " << std::endl;
  //cout << qX << "  " << qY << std::endl;
  //cout << p3X << "  " << p3Y << std::endl;
  //cout << p4X << "  " << p4Y << std::endl;
  if ((role == CLMetabReferenceGlyph::PRODUCT) || (role == CLMetabReferenceGlyph::SIDEPRODUCT))
    {
      glBegin(GL_POLYGON);
      glVertex2d(p1.getX(), p1.getY()); // peak of arrow
      glVertex2d(qX + (unX * a.getArrowWidth()), qY + (unY * a.getArrowWidth()));
      glVertex2d(qX - (unX * a.getArrowWidth()), qY - (unY * a.getArrowWidth()));
      glEnd();
    }
  else
    {
      GLfloat params[4];
      glGetFloatv(GL_CURRENT_COLOR, params);
      GLfloat lineWidth[1];
      glGetFloatv(GL_LINE_WIDTH, lineWidth);

      if (role == CLMetabReferenceGlyph::MODIFIER)
        {
          if (this->mLabelShape == CIRCLE)
            {
              glBegin(GL_LINES);
              glVertex2d(p1.getX() + (unX * a.getArrowWidth()),
                         p1.getY() + (unY * a.getArrowWidth()));
              glVertex2d(p1.getX() - (unX * a.getArrowWidth()),
                         p1.getY() - (unY * a.getArrowWidth()));
              glEnd();
            }
          else
            {
              glBegin(GL_LINES);
              glVertex2d(qX + (unX * a.getArrowWidth()),
                         qY + (unY * a.getArrowWidth()));
              glVertex2d(qX - (unX * a.getArrowWidth()),
                         qY - (unY * a.getArrowWidth()));
              glEnd();
            }
          glColor3f(params[0], params[1], params[2]);
        }
      else if (role == CLMetabReferenceGlyph::ACTIVATOR)
        {
          glColor3f(0.0f, 0.66f, 0.0f); // kind of green
          glLineWidth(2.0f);
          glBegin(GL_LINES);
          glVertex2d(p1.getX() + (unX * a.getArrowWidth()),
                     p1.getY() + (unY * a.getArrowWidth()));
          glVertex2d(p1.getX() - (unX * a.getArrowWidth()),
                     p1.getY() - (unY * a.getArrowWidth()));
          glEnd();

          glColor3f(params[0], params[1], params[2]);
          glLineWidth(lineWidth[0]);
        }
      else if (role == CLMetabReferenceGlyph::INHIBITOR)
        {
          glColor3f(1.0f, 0.0f, 0.0f); // red
          glLineWidth(2.0f);
          glBegin(GL_LINES);
          glVertex2d(p1.getX() + (unX * a.getArrowWidth()),
                     p1.getY() + (unY * a.getArrowWidth()));
          glVertex2d(p1.getX() - (unX * a.getArrowWidth()),
                     p1.getY() - (unY * a.getArrowWidth()));
          glLineWidth(lineWidth[0]);
          glEnd();
        }
    }
}

// draws label as a rectangular filled shape with a border and the text inside
void CQGLNetworkPainter::drawLabel(CLTextGlyph l)
{
  //glColor3f(0.5f, 1.0f, 0.69f); // label background color somehow green
  glColor3f(0.23f, 0.92f, 0.7f); // label background color (61,237,181)
  // draw rectangle as background for text
  glBegin(GL_POLYGON);
  glVertex2d(l.getX(), l.getY());
  glVertex2d(l.getX() + l.getWidth(), l.getY());
  glVertex2d(l.getX() + l.getWidth(), l.getY() + l.getHeight());
  glVertex2d(l.getX(), l.getY() + l.getHeight());
  glEnd();
  // draw frame for rectangle
  glColor3f(0.0f, 0.0f, 0.3f);
  glBegin(GL_LINE_LOOP);
  glVertex2d(l.getX(), l.getY());
  glVertex2d(l.getX() + l.getWidth(), l.getY());
  glVertex2d(l.getX() + l.getWidth(), l.getY() + l.getHeight());
  glVertex2d(l.getX(), l.getY() + l.getHeight());
  glEnd();
  //std::cout << "X: " << l.getX() << "  y: " << l.getY() << "  w: " << l.getWidth() << "  h: " << l.getHeight() << std::endl;
  // now draw text
  //drawStringAt(l.getText(), l.getX(), l.getY(), l.getWidth(), l.getHeight(), QColor(61, 237, 181, QColor::Rgb));
  RG_drawStringAt(l.getText(), static_cast<C_INT32>(l.getX()), static_cast<C_INT32>(l.getY()), static_cast<C_INT32>(l.getWidth()), static_cast<C_INT32>(l.getHeight()));
  //renderBitmapString(l.getX(), l.getY(), l.getText(), l.getWidth(), l.getHeight());
}

// uses GLUT to render string
//void CQGLNetworkPainter::renderBitmapString(C_FLOAT64 x, C_FLOAT64 y, std::string text, C_FLOAT64 w, C_FLOAT64 h)
//{
//  //gl.glMaterialfv(GL.GL_FRONT_AND_BACK, GL.GL_AMBIENT_AND_DIFFUSE, fontColor, 0);
//  glColor3f(0.0f, 0.0f, 0.0f); // black
//  glPushMatrix();
//  const char *cStr = text.c_str();
//  int strLen;
//  //  strlen = glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)cStr);
//  C_FLOAT64 offsetX = (w - (C_FLOAT64)strLen) / 2.0;
//  C_FLOAT64 offsetY = (h + 12) / 2.0; // depend on used font size (here 12 pt)
//  glRasterPos2d(x + offsetX, y + offsetY - 2.0);
//  //cout << "h: " << h << std::endl;
//  //cout << "length of " << text << ":  " << strLen << std::endl;
//
//  unsigned int i;
//  for (i = 0;i < text.size();i++)
//    {
//      //      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
//      //glutStrokeCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
//}
//  glPopMatrix();
//}

// uses QT

void CQGLNetworkPainter::RG_drawStringAt(std::string s, C_INT32 x, C_INT32 y, C_INT32 w, C_INT32 h)
{
  RGTextureSpec* texSpec = RG_createTextureForText(s, mFontname, h);
  if (texSpec == NULL)
    {
      return;
    }
  glPushMatrix();
  glColor3f(0.0, 0.0, 0.0);
  glEnable(GL_TEXTURE_2D);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  GLuint textureNames[1];
  glGenTextures(1, textureNames);
  glBindTexture(GL_TEXTURE_2D, textureNames[0]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_INTENSITY8, static_cast<int>(texSpec->textureWidth), static_cast<int>(texSpec->textureHeight), 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texSpec->textureData);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTranslated(x, y, 0.5);
  double xOffset = (w - texSpec->textWidth + 2) / 2.0;
  double yOffset = (h - texSpec->textHeight + 2) / 2.0;
  xOffset = (xOffset < 0.0) ? 0.0 : xOffset;
  yOffset = (yOffset < 0.0) ? 0.0 : yOffset;
  double textureXRatio = ((texSpec->textWidth + 2) / texSpec->textureWidth) / ((w - xOffset) / w);
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
  //   if((this->mMode==MODE_SELECT || this->mMode==MODE_LAYOUT_CIRCULAR) && std::find(this->mSelection.begin(),this->mSelection.end(),pTextGlyph)!=this->mSelection.end())
  //   {
  //      RectangleSpec* frame=this->mSelectionFrameDict[pTextGlyph->getId()];
  //      this->drawSelectionFrame(frame,this->mSelectionFrameDictHandles[frame]);
  //}
  delete[] texSpec->textureData;
  delete texSpec;
}

int CQGLNetworkPainter::getTextWidth(const std::string& text, const std::string& fontName, unsigned int fontSize)
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

RGTextureSpec* CQGLNetworkPainter::RG_createTextureForText(const std::string& text, const std::string& fontName, unsigned int fontSize)
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
  QCanvas canvas(width, height);
  QCanvasText canvasText(QString(text.c_str()), &canvas);
  canvasText.setFont(font);
  canvasText.setColor(QColor(0, 0, 0));
  // also move one to the right and one down to generate one column
  // and one row of transparent pixels
  canvasText.moveBy(1, 1);
  canvasText.show();
  QPainter painter(&pixmap);
  canvas.drawArea(canvas.rect(), &painter);

  RGTextureSpec* texture = new RGTextureSpec();
  texture->textureData = new GLubyte[height * width];
  texture->textureWidth = width;
  texture->textureHeight = height;
  texture->textWidth = rect.width();
  texture->textHeight = rect.height();
  //QImage image=pixmap.toImage();// RG
  QImage image = pixmap.convertToImage(); // UR
  //QImage timg = QGLWidget::convertToGLFormat(image); // UR
  int i;
  for (i = 0;i < height;++i)
    {
      int j;
      for (j = 0;j < width;++j)
        {
          QRgb pixel = image.pixel(j, i);
          texture->textureData[i*width + j] = static_cast<unsigned char>(255 - (qRed(pixel) + qGreen(pixel) + qBlue(pixel)) / 3);
          //if (qBlue(pixel) != 255)
          //  std::cout << "(" << i << " : " << j << ") " << "r: " << qRed(pixel) << "  g: " << qGreen(pixel) << "  b: " << qBlue(pixel) << std::endl;
          //texture->textureData[i*width + j] = (timg.bits())[i*width + j];// UR
        }
    }
  return texture;
}

void CQGLNetworkPainter::drawStringAt(std::string s, C_FLOAT64 x, C_FLOAT64 y, C_FLOAT64 w, C_FLOAT64 h, QColor bgCol)
{
  glColor3f(0.0f, 0.0f, 0.0f); // black
  //this->drawText((int)x,(int)y,QString(s));

  QString str(FROM_UTF8(s));
  //QRect c((int)x,(int)y,(int)w,(int)h);

  //QRect bbox = fm.boundingRect((int)x,(int)y,(int)w,(int)h,Qt::AlignCenter,s);
  QFontMetrics mfm = QFontMetrics(mf);
  QRect bbox = mfm.boundingRect(FROM_UTF8(s)); // bounding rectangle for text in certain size

  int w2 = round2powN(bbox.width()); // look for smallest w2 = 2^^k with n > w2
  int h2 = round2powN(bbox.height() + 2); // look for smallest h2 = 2^^k with n > h2
  //std::cout << "bbox w:" << w << "  h: " << h << std::endl;
  //std::cout << "bbox w2:" << w2 << "  h2: " << h2 << std::endl;
  while (h2 > h)
    {// reduce fontsize in order to avoid problems with size of texture image
      this->mFontsize--;
      mf.setPointSize(this->mFontsize);
      const QFont& mfRef = mf;
      QFontMetrics mfm = QFontMetrics(mfRef);
      bbox = mfm.boundingRect(FROM_UTF8(s));
      w2 = round2powN(bbox.width());
      h2 = round2powN(bbox.height() + 2);
    }

  QRect c(0, 0, w2, h2);

  //  QBitmap bm(w2,h2,true);
  //  QPainter painter(&bm);
  //  painter.setPen(color1);
  //  painter.setFont(f);
  //  painter.drawText(c,Qt::AlignCenter,s);
  //  painter.end();

  QPixmap pm(w2, h2);
  //pm.setMask(bm);
  //pm.fill(QColor(255, 0, 0));

  pm.fill(bgCol);
  QPainter painter2(&pm);
  painter2.setPen(Qt::black);
  painter2.setFont(mf);
  painter2.drawText(c, Qt::AlignCenter, FROM_UTF8(s));
  painter2.end();

  QImage img = pm.convertToImage();
  QImage timg = QGLWidget::convertToGLFormat(img);

  glTexImage2D(GL_TEXTURE_2D, 0, 3, timg.width(), timg.height(), 0,
               GL_RGBA, GL_UNSIGNED_BYTE, timg.bits());
  double xoff = (w - w2) / 2.0;
  double yoff = (h - h2) / 2.0;

  xoff = 0;
  yoff = 0;

  //std::cout << "w: " << w << "  w2: " << w2 << "   xoff: " << xoff << std::endl;
  //std::cout << "h: " << h << "  h2: " << h2 << "   yoff: " << yoff << std::endl;
  //std::cout << "bbox w:" << bbox.width() << "  h: " << bbox.height() << std::endl;

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
  //std::cout << "d: " << d << " p: " << p << std::endl;
  return (int)pow(2.0, p);
}

// uses FTGL
// void CQGLNetworkPainter::drawStringAt(string s, C_FLOAT64 x, C_FLOAT64 y){
//  glColor3f(0.0f,0.0f,0.0f); // black
// // QFont font = QFont(family,20);
// // this->renderText(x,y,0.0,qStr,font);
//  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // ???
//  glWindowPos2d(x,y);
//  //cout << "position of text: " << s << "  (" << x << "," << y <<")" << std::endl;
//     string fontFile = "/usr/share/fonts/truetype/freefont/FreeSans.ttf";
//     FTFont *font = new FTGLPolygonFont(fontFile.c_str());
//     if(font->Error())
//   {
//    cout << "Failed to open font " << fontFile << std::endl;
//    exit(1);
//}

//   if(!font->FaceSize(14))
//   {
//    cout << "Failed to set size" << std::endl;
//    exit(1);
//}

//  const char *cStr = s.c_str();
//  //cout << "cStr: " << cStr << std::endl;
//  font->UseDisplayList(false);
//  font->Render(cStr);
//}

// requires GLUT
//void CQGLNetworkPainter::drawStringAt(string s, C_FLOAT64 x, C_FLOAT64 y){
//   const char *cStr = s.c_str();
//   int len, i;
//   glRasterPos2f(x, y);
//   len = (int) strlen(cStr);
//   for (i = 0; i < len; i++)
//   {
//     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, cStr[i]);
//}
//}

void CQGLNetworkPainter::rescaleDataSetsWithNewMinMax(C_FLOAT64 oldMin, C_FLOAT64 oldMax, C_FLOAT64 newMin, C_FLOAT64 newMax, C_INT16 scaleMode)
{
  CDataEntity dataSet;
  unsigned int s; // step number
  C_FLOAT64 val, val_new;
  for (s = 0; s < dataSets.size(); s++) // for all steps
    {
      //std:: cout << "rescale step: " << s << std::endl;
      std::map<C_INT32, CDataEntity>::iterator iter = dataSets.find(s);
      if (iter != dataSets.end())
        {
          dataSet = (*iter).second;
          unsigned int i;
          for (i = 0; i < viewerNodes.size();i++) // iterate over string values (node keys)
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
                      a = pSummaryInfo->getMaxOverallConcentration();
                      b = pSummaryInfo->getMinOverallConcentration();
                    }
                }
              C_FLOAT64 val_orig = ((val - oldMin) / (oldMax - oldMin) * (b - a)) + a;
              val_new = newMin + ((val_orig - a) / (b - a) * (newMax - newMin));
              //std::cout << "----------- " << std::endl;

              //std::cout << "val_old: " << viewerNodes[i] << "  " << val << std::endl;

              //std::cout << "val_orig: " << viewerNodes[i] << "  " << val_orig << std::endl;
              //std::cout << "val_new: " << viewerNodes[i] << "  " << val_new << std::endl;
              dataSet.putValueForSpecies(viewerNodes[i], val_new);
            }
          dataSets.erase(s);
          dataSets.insert (std::pair<C_INT32, CDataEntity>
                           (s, dataSet));
        }
    }
}

// INFO: to rescale an inteval [a..b] to another interval [x..y] the following formula is used: (val_old in [a..b]
// val_new = x + ((val_old - a) * (y - x) / (b - a))

void CQGLNetworkPainter::rescaleDataSets(C_INT16 scaleMode)
{
  CDataEntity dataSet;
  unsigned int s; // step number
  C_FLOAT64 val, val_new;

  for (s = 0; s < dataSets.size(); s++)
    {
      std::map<C_INT32, CDataEntity>::iterator iter = dataSets.find(s);
      if (iter != dataSets.end())
        {
          dataSet = (*iter).second;
          unsigned int i;
          // try to get VisParameters from parent (CQLayoutMainWindow)
          C_FLOAT64 minNodeSize = 10;
          C_FLOAT64 maxNodeSize = 100;
          if (pParentLayoutWindow != NULL)
            {
              if (pParentLayoutWindow->getMappingMode() == CVisParameters::COLOR_MODE)
                {
                  minNodeSize = 0.0;
                  maxNodeSize = 240.0; // red to blue in HSV color value (hue) circle
                }
              else
                {
                  minNodeSize = pParentLayoutWindow->getMinNodeSize();
                  maxNodeSize = pParentLayoutWindow->getMaxNodeSize();
                }
            }
          for (i = 0; i < viewerNodes.size();i++) // iterate over string values (node keys)
            {
              // get old value
              val = dataSet.getValueForSpecies(viewerNodes[i]);
              //std::cout << "old value: " << val << std::endl;
              if ((scaleMode == CVisParameters::INDIVIDUAL_SCALING) &&
                  (pParentLayoutWindow != NULL))
                {// global mode -> individual mode

                  val_new =
                    ((val - minNodeSize) *
                     (pSummaryInfo->getMaxOverallConcentration() - pSummaryInfo->getMinOverallConcentration()) / (maxNodeSize - minNodeSize)) + pSummaryInfo->getMinOverallConcentration();
                  // now rescale
                  val_new = ((val_new - pSummaryInfo->getMinForSpecies(viewerNodes[i])) *
                             (maxNodeSize - minNodeSize) /
                             (pSummaryInfo->getMaxForSpecies(viewerNodes[i]) - pSummaryInfo->getMinForSpecies(viewerNodes[i])))
                            + minNodeSize;
                  std::cout << "new value: " << val_new << std::endl;
                }
              else
                {// individual mode -> global mode
                  // first calculate original value
                  val_new =
                    ((val - minNodeSize) *
                     (pSummaryInfo->getMaxForSpecies(viewerNodes[i]) - pSummaryInfo->getMinForSpecies(viewerNodes[i])) / (maxNodeSize - minNodeSize)) + pSummaryInfo->getMinForSpecies(viewerNodes[i]);
                  // now rescale
                  val_new = ((val_new - pSummaryInfo->getMinOverallConcentration()) *
                             (maxNodeSize - minNodeSize) /
                             (pSummaryInfo->getMaxOverallConcentration() - pSummaryInfo->getMinOverallConcentration()))
                            + minNodeSize;
                  //std::cout << "new value: " << val_new << std::endl;
                }
              dataSet.putValueForSpecies(viewerNodes[i], val_new);

              //calculate new value
              //             if (val != -DBL_MAX)
              //                setNodeSize(viewerNodes[i], val);
            }
          dataSets.erase(s);
          dataSets.insert (std::pair<C_INT32, CDataEntity>
                           (s, dataSet));
        }
    }
}

bool CQGLNetworkPainter::createDataSets()
{
  int counter = 0;
  bool loadDataSuccessful = false;
  if (CCopasiDataModel::Global != NULL)
    {
      CTrajectoryTask *ptask = dynamic_cast< CTrajectoryTask * >((*CCopasiDataModel::Global->getTaskList())["Time-Course"]);
      const CTimeSeries & timeSer = ptask->getTimeSeries();
      if (timeSer.getNumSteps() > 0)
        {
          if (timeSer.getNumVariables() > 0)
            {
              dataSets.clear(); // remove old data sets
              pSummaryInfo = new CSimSummaryInfo(timeSer.getNumSteps(), timeSer.getNumVariables(),
                                                 timeSer.getConcentrationData(timeSer.getNumSteps() - 1, 0) - timeSer.getConcentrationData(0, 0));
              //C_FLOAT64 tt = timeSer.getConcentrationData(timeSer.getNumSteps() - 1, 0) - timeSer.getConcentrationData(0, 0);
              //std::cout << "summary: no of steps: " << pSummaryInfo->getNumberOfSteps() << std::endl,
              //std::cout << "total time: " << tt << std::endl;
              //std::cout << "number of steps in time series: " << timeSer.getNumSteps() << std::endl;
              //std::cout << "number of variables: " << timeSer.getNumVariables() << std::endl;
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
              for (i = 0; i < timeSer.getNumVariables(); i++) // iterate on reactants
                {
                  maxR = - DBL_MAX;
                  minR = DBL_MAX;
                  name = timeSer.getTitle(i);
                  objKey = timeSer.getKey(i);
                  std::map<std::string, std::string>::iterator iter = keyMap.find(objKey);
                  if (iter != keyMap.end())
                    {// if there is a node (key)
                      ndKey = (keyMap.find(objKey))->second;
                      for (t = 0;t <= timeSer.getNumSteps();t++) // iterate on time steps t=0..n
                        {
                          val = timeSer.getConcentrationData(t, i);
                          if (val > maxR)
                            maxR = val;
                          if (val < minR)
                            minR = val;
                        }
                      //std::cout << name << " : " << key << " : " << val << std::endl;
                      pSummaryInfo->storeMax(ndKey, maxR);
                      pSummaryInfo->storeMin(ndKey, minR);
                      if (maxR > maxAll)
                        maxAll = maxR;
                    }
                }
              pSummaryInfo->setMaxOverallConcentration(maxAll);
              //std::cout << *pSummaryInfo;
              //this->printNodeMap();
              //dataSets.resize(timeSer.getNumSteps());
              // now create data sets for visualization/animation
              // try to get VisParameters from parent (CQLayoutMainWindow)
              C_FLOAT64 minNodeSize = 10;
              C_FLOAT64 maxNodeSize = 100;
              if (pParentLayoutWindow != NULL)
                {
                  minNodeSize = pParentLayoutWindow->getMinNodeSize();
                  maxNodeSize = pParentLayoutWindow->getMaxNodeSize();
                }
              for (t = 0; t < timeSer.getNumSteps(); t++)  // iterate on time steps t=0..n
                {
                  CDataEntity dataSet;
                  for (i = 0;i < timeSer.getNumVariables();i++) // iterate on reactants
                    {
                      //name = timeSer.getTitle(i);
                      objKey = timeSer.getKey(i); // object key os dbml species
                      std::map<std::string, std::string>::iterator iter = keyMap.find(objKey);
                      if (iter != keyMap.end())
                        {// if there is a node (key)
                          ndKey = (keyMap.find(objKey))->second; // key of graphical node
                          val = timeSer.getConcentrationData(t, i); // get concentration of species i at timepoint t
                          C_FLOAT64 scaledVal;
                          // now scale value;
                          if (pParentLayoutWindow->getScalingMode() == CVisParameters::INDIVIDUAL_SCALING)
                            {
                              minR = pSummaryInfo->getMinForSpecies(ndKey);
                              maxR = pSummaryInfo->getMaxForSpecies(ndKey);
                            }
                          else
                            {// == CVisParameters.GLOBAL_SCALING
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
                          //std::cout << timeSer.getTitle(i)  << " ndKey: " << ndKey << "  " << scaledVal << std::endl;
                          //std::cout << timeSer.getTitle(i) << ": " << val << " mapped  to  " << scaledVal << std::endl;
                        }
                    }
                  // now collect data set
                  //std::cout << "A: number of elements in data set: " << dataSet.getNumberOfElements() << std::endl;
                  //dataSets.push_back(dataSet);
                  dataSets.insert(std::pair<C_INT32, CDataEntity>
                                  (t, dataSet));
                  counter++;
                  //std::cout << "no of inserted elements: " << dataSets.size() << std::endl;
                  //std::cout << "t: " << t << "  time: " << dataSet.getTime() << std::endl;
                }
              loadDataSuccessful = true;
            }
          else
            std::cout << "empty time series: no variables present" << std::endl;
        }
      else
        std::cout << "no simulation steps found: you have to create a time course first" << std::endl;
    }
  //std::cout << *pSummaryInfo << std::endl;
  //std::cout << "number of data sets created: " << dataSets.size() << std::endl;
  this->mDataPresentP = loadDataSuccessful;
  return loadDataSuccessful;
}

C_INT32 CQGLNetworkPainter::getNumberOfSteps()
{
  //std::cout << "number of elements in data sets:" << dataSets.size() << std::endl;
  return dataSets.size();
}

void CQGLNetworkPainter::runAnimation()
{
  this->mLabelShape = CIRCLE;
  if (dataSets.size() == 0)
    this->createDataSets(); // load data if this was not done before

  // try to get VisParameters from parent (CQLayoutMainWindow)

  C_INT16 stepsPerSecond = 10;
  if (pParentLayoutWindow != NULL)
    {
      pParentLayoutWindow->setAnimationRunning(true);
      stepsPerSecond = pParentLayoutWindow->getStepsPerSecond();
    }

  //CVisParameters::animationRunning = true;

  regularTimer->start((int)(1000 / stepsPerSecond), false); // emit signal in chosen framerate

  //while ((stepShown <= CVisParameters::numberOfSteps) &&
  //       (CVisParameters::animationRunning))
  //  {// while process has not been stopped
  //    //QTimer::singleShot(1000, this, SLOT(triggerAnimationStep()));
  //    //this->stepShown++;
  //}
}

void CQGLNetworkPainter::triggerAnimationStep()
{
  C_INT32 numberOfSteps = 100;
  bool animationRunning = true;
  if (pParentLayoutWindow != NULL)
    {
      animationRunning = pParentLayoutWindow->getAnimationRunning();
      //numberOfSteps = pParentLayoutWindow->getNumberOfSteps();
    }

  numberOfSteps = getNumberOfSteps();
  if ((stepShown <= numberOfSteps) &&
      (animationRunning))
    {
      // set value in slider
      //std::cout << "step: " << stepShown << std::endl;
      emit stepChanged(stepShown);
      this->stepShown++;
    }
  else
    {
      regularTimer->stop();
      emit endOfAnimationReached();
    }
  //updateGL();
  //this->showStep(i);

  //this->drawGraph();
}

void CQGLNetworkPainter::showStep(C_INT32 stepNumber)
{
  this->stepShown = stepNumber;
  //std::cout << "show step " << i << std::endl;
  if (this->mLabelShape != CIRCLE)
    this->mLabelShape = CIRCLE;
  if ((0 <= stepNumber) && (static_cast<unsigned int>(stepNumber) < dataSets.size()))
    {
      //std::cout << "step: " << stepNumber << std::endl;
      //CDataEntity *dataSet = &(dataSets[stepNumber]);
      std::map<C_INT32, CDataEntity>::iterator iter = dataSets.find(stepNumber);
      if (iter != dataSets.end())
        {
          CDataEntity dataSet = (*iter).second;
          unsigned int i;
          for (i = 0; i < viewerNodes.size();i++)
            {
              if (pParentLayoutWindow != NULL)
                {
                  C_FLOAT64 val = dataSet.getValueForSpecies(viewerNodes[i]);
                  if (pParentLayoutWindow->getMappingMode() != CVisParameters::COLOR_MODE)
                    {// no color mode

                      //std::cout << "show " << viewerNodes[i] << "  " << dataSet->getValueForSpecies(viewerNodes[i]) << std::endl;
                      if (val != -DBL_MAX)
                        if (isnan(val)) // test for nan
                          {
                            std::cout << "nan value found" << std::endl;
                            setNodeSize(viewerNodes[i], DEFAULT_NODE_SIZE);
                          }
                        else
                          setNodeSize(viewerNodes[i], val);
                    }
                  else // COLOR_MODE
                    {
                      setNodeSize(viewerNodes[i], DEFAULT_NODE_SIZE);
                      //C_FLOAT64 val = dataSet.getValueForSpecies(viewerNodes[i]);
                      //std::cout << "node size value: " << val << std::endl;
                      if (val != -DBL_MAX)
                        if (isnan(val)) // test for nan
                          {
                            std::cout << "nan value found" << std::endl;
                            setNodeSize(viewerNodes[i], DEFAULT_NODE_SIZE);
                          }
                        else
                          setNodeSizeWithoutChangingCurves(viewerNodes[i], val);
                    }
                  //C_FLOAT64 v = dataSet.getOrigValueForSpecies(viewerNodes[i]);
                  //std::cout << "orig value for: " << viewerNodes[i] << ": " << v << std::endl;
                }
            }
        }
    }
  this->drawGraph();
}

void CQGLNetworkPainter::setNodeSizeWithoutChangingCurves(std::string key, C_FLOAT64 val)
{
  //int i;
  std::map<std::string, CGraphNode>::iterator nodeIt;
  nodeIt = nodeMap.find(key);
  if (nodeIt != nodeMap.end())
    (*nodeIt).second.setSize(val);
}

// set node sizes according to data set and change curves (meaning end points of curve segments) to nodes
void CQGLNetworkPainter::setNodeSize(std::string key, C_FLOAT64 val)
{
  //std::cout << "set " << key << "  to " << val << std::endl;
  //int i;
  // curves to nodes are changed, arrows are created newly
  nodeArrowMap.clear();
  // for (i = 0; i < viewerNodes.size(); i++)
  //   {
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
      if (pCurve != NULL)
        {
          CLLineSegment* pLastSeg = pCurve->getSegmentAt(pCurve->getNumCurveSegments() - 1); // get pointer to last segment
          // move end point of segment along the line from the circle center(=from) to the current end point of the last segment
          // so that it lies on the border of the circle
          //std::cout << "1. last segment: " << *pLastSeg << std::endl;
          CLPoint to;
          if (pLastSeg->isBezier())
            to = pLastSeg->getBase2();
          else
            to = pLastSeg->getStart();
          //std::cout << "node: " << (*nodeIt).second<< std::endl;
          CLPoint from = CLPoint((*nodeIt).second.getX() + ((*nodeIt).second.getWidth() / 2.0), (*nodeIt).second.getY() + ((*nodeIt).second.getHeight() / 2.0)); // center of bounding box and also of circle
          C_FLOAT64 distance = sqrt(((to.getX() - from.getX()) * (to.getX() - from.getX())) + ((to.getY() - from.getY()) * (to.getY() - from.getY())));
          //std::cout << "distance: " << distance << "  size: " << msize << std::endl;

          C_FLOAT64 circleDist = ((*nodeIt).second.getSize() / 2.0) + 4.0; // near border
          C_FLOAT64 newX = from.getX() + ((to.getX() - from.getX()) / distance * circleDist);
          C_FLOAT64 newY = from.getY() + ((to.getY() - from.getY()) / distance * circleDist);

          //C_FLOAT64 dx, dy;
          //dx = to.getX() - newX;
          //dy = to.getY() - newY;
          pLastSeg->setEnd(CLPoint(newX, newY));
          // std::cout << "2. last segment: " << *pLastSeg << std::endl;
          // now insert new arrow in map
          if (pLastSeg->isBezier())
            {// for bezier curves, move base points too
              //pLastSeg->setBase1(CLPoint(pLastSeg->getBase1().getX() + dx,pLastSeg->getBase1().getY() + dy));
              //pLastSeg->setBase2(CLPoint(pLastSeg->getBase2().getX() + dx,pLastSeg->getBase2().getY() + dy));
            }
          CLPoint p = pLastSeg->getEnd();
          if (pCurve->hasArrowP())
            {
              CArrow *ar = new CArrow(*pLastSeg, p.getX(), p.getY(), this->currentZoom);
              nodeArrowMap.insert(std::pair<std::string, CArrow>
                                  (key, *ar));
              pCurve->setArrow(*ar);
            }
        }
      curveIt++;
    }
  //}
}

//void CQGLNetworkPainter::changeNodeSize(std::string viewerNodeKey, double newSize)
//{
//  // first change size of node in viewerNodes
//  std::map<std::string, float>::iterator iter = nodeSizeMap.find(viewerNodeKey);
//  if (iter != nodeSizeMap.end())
//    {
//      nodeSizeMap[viewerNodeKey] = newSize;
//      // now get curve(s) that belong(s) to node and change end point(s)
//      //for(multimap<string, int>::iterator iter = m.begin(); iter != m.end(); ++iter) {
//      //cout << " Name: " << iter->first << ", ID #" << iter->second << endl;
//}
//}

void CQGLNetworkPainter::mapLabelsToRectangles()
{
  this->mLabelShape = RECTANGLE;
  nodeArrowMap.clear(); // map is filled with new arrows
  std::pair<std::multimap<std::string, CGraphCurve>::iterator, std::multimap<std::string, CGraphCurve>::iterator> rangeCurveIt;
  std::multimap<std::string, CGraphCurve>::iterator curveIt;
  unsigned int i;
  for (i = 0;i < viewerNodes.size();i++)
    {
      //curveIt = nodeCurveMap.find(viewerNodes[i]);
      rangeCurveIt = nodeCurveMap.equal_range(viewerNodes[i]);
      std::map<std::string, CGraphNode>::iterator nodeIt = nodeMap.find(viewerNodes[i]); // find all edges belonging to a node
      if (nodeIt != nodeMap.end())
        {
          //while (curveIt != nodeCurveMap.end()){
          curveIt = rangeCurveIt.first;
          while (curveIt != rangeCurveIt.second)
            {
              this->adaptCurveForRectangles(curveIt, (*nodeIt).second.getBoundingBox());
              curveIt++;
            }
        }
    }
  //viewerNodes[i].adaptCurvesForRectangles(&viewerCurves);
  this->drawGraph(); // this function will draw the bounding box for each node
  //this->draw();
  this->updateGL();
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

  //std::cout << "center: " << center << std::endl;
  //std::cout << "p: " << p << std::endl;
  //std::cout << "qangle: " << qAngle << "  pangle: " << pAngle << std::endl;

  if (fabs(pAngle) < fabs(qAngle))
    {// intersection point is left or right side
      if (p.getX() > center.getX()) // right side
        onpoint = CLPoint(q.getX(), center.getY());
      else // left side
        onpoint = CLPoint(r.getPosition().getX(), center.getY());
    }
  else
    {//intersection point is top or bottom side
      if (p.getY() > center.getY()) // top side
        onpoint = CLPoint(center.getX(), r.getPosition().getY() + r.getDimensions().getHeight());
      else // bottom side
        onpoint = CLPoint(center.getX(), r.getPosition().getY());
    }
  //std::cout << "onpoint: " << onpoint << std::endl;
  //std::cout << "-------------" << std::endl;
  return onpoint;
}

void CQGLNetworkPainter::mapLabelsToCircles()
{
  this->mLabelShape = CIRCLE;

  nodeArrowMap.clear(); // map is filled with new arrows
  std::pair<std::multimap<std::string, CGraphCurve>::iterator, std::multimap<std::string, CGraphCurve>::iterator> rangeCurveIt;
  std::multimap<std::string, CGraphCurve>::iterator curveIt;
  unsigned int i;
  for (i = 0;i < viewerNodes.size();i++)
    {
      //curveIt = nodeCurveMap.find(viewerNodes[i]);
      rangeCurveIt = nodeCurveMap.equal_range(viewerNodes[i]);
      std::map<std::string, CGraphNode>::iterator nodeIt = nodeMap.find(viewerNodes[i]); // find all edges belonging to a node
      if (nodeIt != nodeMap.end())
        {
          //while (curveIt != nodeCurveMap.end()){
          curveIt = rangeCurveIt.first;
          while (curveIt != rangeCurveIt.second)
            {
              this->adaptCurveForCircle(curveIt, (*nodeIt).second.getBoundingBox());
              curveIt++;
            }
        }
    }

  this->drawGraph();
  // this->draw();
  this->updateGL();
}

// get Point on Circle border on the line from the center of the given rectangle to the given point p
CLPoint CQGLNetworkPainter::getPointOnCircle(CLBoundingBox r, CLPoint p)
{
  CLPoint center; // center of rectangle
  center.setX(r.getPosition().getX() + (r.getDimensions().getWidth() / 2.0));
  center.setY(r.getPosition().getY() + (r.getDimensions().getHeight() / 2.0));

  C_FLOAT64 distance = sqrt(((p.getX() - center.getX()) * (p.getX() - center.getX())) + ((p.getY() - center.getY()) * (p.getY() - center.getY())));
  //std::cout << "distance: " << distance << "  size: " << msize << std::endl;

  C_FLOAT64 onPointX = center.getX() + ((p.getX() - center.getX()) / distance * DEFAULT_NODE_SIZE / 2.0);
  C_FLOAT64 onPointY = center.getY() + ((p.getY() - center.getY()) / distance * DEFAULT_NODE_SIZE / 2.0);

  return CLPoint(onPointX, onPointY);
}

// get Point  on the line from the center of the given rectangle to the given point p with the distance d to the circle border
CLPoint CQGLNetworkPainter::getPointNearCircle(CLBoundingBox r, CLPoint p, C_INT16 d)
{
  CLPoint center; // center of rectangle
  center.setX(r.getPosition().getX() + (r.getDimensions().getWidth() / 2.0));
  center.setY(r.getPosition().getY() + (r.getDimensions().getHeight() / 2.0));

  C_FLOAT64 distance = sqrt(((p.getX() - center.getX()) * (p.getX() - center.getX())) + ((p.getY() - center.getY()) * (p.getY() - center.getY())));
  //std::cout << "distance: " << distance << "  size: " << msize << std::endl;

  C_FLOAT64 onPointX = center.getX() + ((p.getX() - center.getX()) / distance * ((DEFAULT_NODE_SIZE / 2.0) + d));
  C_FLOAT64 onPointY = center.getY() + ((p.getY() - center.getY()) / distance * ((DEFAULT_NODE_SIZE / 2.0) + d));

  return CLPoint(onPointX, onPointY);
}

// move one or two points of a curve, so that the end point of the curve ends at the circle given by the center of the bounding box (where the diagonals intersect) that is given in the parameters and that has the default size
void CQGLNetworkPainter::adaptCurveForCircle(std::multimap<std::string, CGraphCurve>::iterator it, CLBoundingBox box)
{
  CLLineSegment* pLastSeg = (*it).second.getSegmentAt((*it).second.getNumCurveSegments() - 1);
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
          BezierCurve *bezier = new BezierCurve();
          std::vector<CLPoint> pts = std::vector<CLPoint>();
          pts.push_back(pLastSeg->getStart());
          pts.push_back(pLastSeg->getBase1());
          pts.push_back(pLastSeg->getBase2());
          pts.push_back(pLastSeg->getEnd());
          std::vector<CLPoint> bezierPts = bezier->curvePts(pts);
          C_INT32 num = bezierPts.size();
          CLLineSegment segForArrow = CLLineSegment(bezierPts[num - 2], bezierPts[num - 1]);
          ar = new CArrow(segForArrow, bezierPts[num - 1].getX(), bezierPts[num - 1].getY(), this->currentZoom);
        }
      else
        ar = new CArrow(*pLastSeg, p.getX(), p.getY(), this->currentZoom);

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
  CLLineSegment* pLastSeg = (*it).second.getSegmentAt((*it).second.getNumCurveSegments() - 1);
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
          BezierCurve *bezier = new BezierCurve();
          std::vector<CLPoint> pts = std::vector<CLPoint>();
          pts.push_back(pLastSeg->getStart());
          pts.push_back(pLastSeg->getBase1());
          pts.push_back(pLastSeg->getBase2());
          pts.push_back(pLastSeg->getEnd());
          std::vector<CLPoint> bezierPts = bezier->curvePts(pts);
          C_INT32 num = bezierPts.size();
          CLLineSegment segForArrow = CLLineSegment(bezierPts[num - 2], bezierPts[num - 1]);
          ar = new CArrow(segForArrow, bezierPts[num - 1].getX(), bezierPts[num - 1].getY(), this->currentZoom);
        }
      else
        ar = new CArrow(*pLastSeg, p.getX(), p.getY(), this->currentZoom);

      nodeArrowMap.insert(std::pair<std::string, CArrow>
                          ((*it).first, *ar));
      ((*it).second).setArrowP(true);
      ((*it).second).setArrow(*ar);
    }
  //  it++;
  //}
}

// looks for the best point to make a line between a given point p and a rectangle r.
// The point to connect to should always lie on the border of the rectangle and, more specifically
// on the middle of one of the border lines

void CQGLNetworkPainter::createActions()
{
  zoomInAction = new QAction ("zoom in",
                              "Zoom in",
                              CTRL + Key_P,
                              this);
  connect(zoomInAction, SIGNAL(activated()), this, SLOT(zoomIn()));

  zoomOutAction = new QAction ("zoom out",
                               "Zoom out",
                               CTRL + Key_M,
                               this);
  connect(zoomOutAction, SIGNAL(activated()), this, SLOT(zoomOut()));
}

void CQGLNetworkPainter::zoomIn()
{
  zoom(1.5);
}

void CQGLNetworkPainter::zoomOut()
{
  zoom(2.0 / 3.0);
}

void CQGLNetworkPainter::zoomGraph(C_FLOAT64 zoomFactor)
{
  this->zoom(zoomFactor);
}

void CQGLNetworkPainter::zoom(C_FLOAT64 zoomFactor)
{
  //cout << "zoom  "  << zoomFactor << std::endl;
  this->currentZoom *= zoomFactor;

  CLPoint cMax = CLPoint(this->mgraphMax.getX() * zoomFactor, this->mgraphMax.getY() * zoomFactor);
  this->setGraphSize(this->mgraphMin, cMax);

  if (pParentLayoutWindow != NULL)
    {
      C_FLOAT64 oldMin = pParentLayoutWindow->getMinNodeSize();
      C_FLOAT64 oldMax = pParentLayoutWindow->getMaxNodeSize();
      pParentLayoutWindow->setMinNodeSize(pParentLayoutWindow->getMinNodeSize() * zoomFactor);
      pParentLayoutWindow->setMaxNodeSize(pParentLayoutWindow->getMaxNodeSize() * zoomFactor);
      unsigned int i;

      if (mDataPresentP)
        {
          rescaleDataSetsWithNewMinMax(oldMin, oldMax, pParentLayoutWindow->getMinNodeSize(), pParentLayoutWindow->getMaxNodeSize(), pParentLayoutWindow->getScalingMode());
        }
      //else {// just scale nodes and curves in graph (and not the whole data set)
      //scale nodes
      for (i = 0;i < this->viewerNodes.size();i++)
        {
          std::map<std::string, CGraphNode>::iterator nodeIt;
          nodeIt = nodeMap.find(viewerNodes[i]);
          if (nodeIt != nodeMap.end())
            (*nodeIt).second.scale(zoomFactor);
          //this->viewerNodes[i].scale(zoomFactor);
        }
      //}

      //scale curves not directly pointing to a reactant/species node
      for (i = 0;i < viewerCurves.size();i++)
        {
          this->viewerCurves[i].scale(zoomFactor);
        }
      //scale curves that are associated with a reactant/species node (i.e. directly points to it)
      std::cout << "scale curves: " << std::endl;
      for (i = 0; i < viewerNodes.size();i++)
        {
          std::pair<std::multimap<std::string, CGraphCurve>::iterator, std::multimap<std::string, CGraphCurve>::iterator> curveRangeIt;
          std::multimap<std::string, CGraphCurve>::iterator curveIt;

          curveRangeIt = nodeCurveMap.equal_range(viewerNodes[i]);
          //curveIt = nodeCurveMap.find(viewerNodes[i]);
          curveIt = curveRangeIt.first;
          while (curveIt != curveRangeIt.second)
            {
              ((*curveIt).second).scale(zoomFactor); // scale curve
              curveIt++;
            }
        }
      // common fontname and size for all labels are stored in this class
      this->mFontsizeDouble = this->mFontsizeDouble * zoomFactor;
      this->mFontsize = (int)this->mFontsizeDouble;
      //std::cout << "new fontsize: " << this->mFontsize << std::endl;
      for (i = 0;i < viewerLabels.size();i++)
        {
          this->viewerLabels[i].scale(zoomFactor);
        }
      for (i = 0;i < viewerNodes.size();i++)
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

          //this->viewerArrows[i].scale(zoomFactor);
        }
      //}
    }
  this->drawGraph();
}

void CQGLNetworkPainter::contextMenuEvent(QContextMenuEvent *cme)
{
  QPopupMenu *contextMenu = new QPopupMenu(this);
  zoomInAction->addTo(contextMenu);
  zoomOutAction->addTo(contextMenu);
  contextMenu->exec(cme->globalPos());
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

  glColor3f(0.0f, 1.0f, 0.0f); // gr�n
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
    return true;
  else return false;
}

void CQGLNetworkPainter::initializeGraphPainter(QWidget *viewportWidget)
{
  currentZoom = 1.0;
  mLabelShape = RECTANGLE;
  mgraphMin = CLPoint(0.0, 0.0);
  mgraphMax = CLPoint(250.0, 250.0);
  //mFontname = "Helvetica";
  mFontname = "Arial";
  mFontsize = 12;
  mFontsizeDouble = 12.0; // to avoid rounding errors due to zooming in and out
  mDataPresentP = false;

  //mf(FROM_UTF8(this->mFontname));
  mf = QFont(FROM_UTF8(mFontname));
  mf.setPointSize(this->mFontsize);
  const QFont& mfRef = mf;
  QFontMetrics mfm = QFontMetrics(mfRef);

  // parent structure: glPainter -> viewport -> scrollView -> splitter -> mainWindow
  QWidget *ancestor = viewportWidget->parentWidget()->parentWidget()->parentWidget()->parentWidget();
  //CQLayoutMainWindow *mainWindow = (*CQLayoutMainWindow) ();
  //std::cout << "ancestor " << ancestor->className() << std::endl;
  connect(this, SIGNAL(stepChanged(C_INT32)), ancestor, SLOT(changeStepValue(C_INT32)));
  connect(this, SIGNAL(endOfAnimationReached()), ancestor, SLOT(endOfAnimationReached()));
  regularTimer = new QTimer(this);
  connect(regularTimer, SIGNAL(timeout()), this, SLOT(triggerAnimationStep()));

  CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(ancestor);
  assert(tmp);
  if (tmp)
    pParentLayoutWindow = tmp;
  else
    pParentLayoutWindow = NULL;

  stepShown = 0;
  createActions();
}

void CQGLNetworkPainter::initializeGL()
{
  //printAvailableFonts();
  //std::cout << "initialize GL" << std::endl;
  // Set up the rendering context, define display lists etc.:

  //glClearColor(1.0, 1.0, 0.94, 0.0);  // background ivory
  //glClearColor(QColor(255,255,240));
  //glClearColor(1.0f, 1.0f, 0.94f, 0.0f);  // background ivory
  qglClearColor(QColor(255, 255, 240, QColor::Rgb));
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glDisable(GL_ALPHA_TEST);

  //glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  //glClearDepth(1.0f);           // Depth Buffer Setup
  //glDepthFunc(GL_LEQUAL);       // The Type Of Depth Test To Do
  //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculation

  graphObjList = glGenLists(256);
  drawGraph(); // create display list with graph objects
  //glNewList(graphObjList, GL_COMPILE);
  //glEndList();

  // now init glut

  //int argc = 1;
  //char *argv = "SimWiz";
  //      glutInit(&argc, &argv);
  //      glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
}

void CQGLNetworkPainter::resizeGL(int w, int h)
{
  //std::cout << "resize GL" << std::endl;
  std::cout << "GL size:  w x h:    " << w << "  x  " << h << std::endl;
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

void CQGLNetworkPainter::paintGL()
{
  //std::cout << "paint GL" << std::endl;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
  draw();
}

void CQGLNetworkPainter::printNodeMap()
{
  std::cout << " node ids to label text mappings: " << std::endl;
  std::map<std::string, CGraphNode>::iterator nodeIt;
  nodeIt = nodeMap.begin();
  while (nodeIt != nodeMap.end())
    {
      std::cout << (*nodeIt).first << "  :  " << (*nodeIt).second.getLabelText() << std::endl;
      nodeIt++;
    }
}

void CQGLNetworkPainter::printAvailableFonts()
{
  QFontDatabase fdb;
  QStringList families = fdb.families();
  for (QStringList::Iterator f = families.begin(); f != families.end(); ++f)
    {
      QString family = *f;
      qDebug(family);
      QStringList styles = fdb.styles(family);
      for (QStringList::Iterator s = styles.begin(); s != styles.end(); ++s)
        {
          QString style = *s;
          QString dstyle = "\t" + style + " (";
          QValueList<int> smoothies = fdb.smoothSizes(family, style);
          for (QValueList<int>::Iterator points = smoothies.begin();
               points != smoothies.end(); ++points)
            {
              dstyle += QString::number(*points) + " ";
            }
          dstyle = dstyle.left(dstyle.length() - 1) + ")";
          qDebug(dstyle);
        }
    }
}
