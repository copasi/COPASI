// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQGLNetworkPainter.cpp,v $
//   $Revision: 1.23 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/05/04 09:49:28 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>
#include <math.h>
#include <utility>

#include <qfont.h>
#include <qstring.h>
#include <qfontmetrics.h>
#include <qbitmap.h>
#include <qpainter.h>
#include <qrect.h>
#include <qpoint.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qcolor.h>

//#include "FTFont.h"
//#include "FTGLPixmapFont.h"
//#include "FTGLPolygonFont.h"
#include "copasi.h"

#include "CQGLNetworkPainter.h"
#include "UI/qtUtilities.h"
#include "layout/CLayout.h"
#include "utilities/CCopasiVector.h"

CQGLNetworkPainter::CQGLNetworkPainter(QWidget *parent, const char *name)
    : QGLWidget(parent, name)
{initializeGraphPainter();}

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
      viewerNodes.push_back(nKey);
      nodeMap.insert(std::pair<std::string, CGraphNode>
                     (nKey,
                      CGraphNode(*nodes[i])));
      //std::cout << "insert " << nKey << "  " << *nodes[i] << std::endl;
      //viewerNodes[i].printObject();
    }
  CCopasiVector<CLReactionGlyph> reactions;
  reactions = lP->getListOfReactionGlyphs();

  std::cout << "number of reactions: " << reactions.size() << std::endl;

  //now extract curves to draw from reaction
  viewerCurves = std::vector<CLCurve>();
  //first get reaction arrow
  for (i = 0;i < reactions.size();i++)
    {
      CLCurve curve = (reactions[i])->getCurve();
      viewerCurves.push_back(curve);

      CCopasiVector<CLMetabReferenceGlyph> edgesToNodesOfReaction;
      edgesToNodesOfReaction = reactions[i]->getListOfMetabReferenceGlyphs();
      //std::cout << "number of edges in reaction " << i << ": "<< edgesToNodesOfReaction.size() << std::endl;
      unsigned int j2;
      for (j2 = 0;j2 < edgesToNodesOfReaction.size();j2++)
        {
          const CLCurve curve = edgesToNodesOfReaction[j2]->getCurve();

          //viewerCurves.push_back(curve);
          //std::cout << "curve: " << curve << std::endl;
          //           int k;
          //         std::vector<CLLineSegment> segments = curve.getCurveSegments();
          //          for (k = 0;k < curve.getNumCurveSegments();k++)
          //            {
          //              CLLineSegment seg = segments[k];
          //              viewerCurves.push_back(seg); // add copy of segment to vector
          //}
          CLMetabReferenceGlyph::Role r = edgesToNodesOfReaction[j2]->getRole();
          std::string nodeKey = std::string(edgesToNodesOfReaction[j2]->getMetabGlyph()->getKey());
          nodeCurveMap.insert(std::pair<std::string, CLCurve>
                              (nodeKey,
                               curve));
          //std::cout << "insert " << nodeKey << "  " << curve << std::endl;
          //          curveMap.insert(std::pair<std::string, CLCurve*>
          //                          (std::string(edgesToNodesOfReaction[j2]->getMetabGlyphKey()),
          //                           &(edgesToNodesOfReaction[j2]->getCurve())));
          //          nodeSizeMap.insert(std::pair<std::string, float>
          //                             (nodeKey, edgesToNodesOfReaction[j2]->getMetabGlyph()->getHeight())); // initial node diameter is height of glyph bounding box
          //          std::cout << nodeKey << " : " << edgesToNodesOfReaction[j2]->getMetabGlyph()->getHeight() << std::endl;
          //          viewerNodeMap.insert(std::pair<std::string, CLMetabGlyph>
          //                  (std::string(nodeKey),
          //                  *findNodeWithKey(viewerNodes,nodeKey))
          //);
          //std::cout << "role : " << r << std::endl;
          //storeCurveInCorrespondingNode(nodeKey, viewerCurves.back()); // use reference to last curve put into the vector viewerCurves
          //storeCurveInCorrespondingNode(nodeKey, viewerCurves.size() - 1); //index of curve derived from the fact that the curve currently is the last element of the vector
          if ((r == CLMetabReferenceGlyph::PRODUCT) || (r == CLMetabReferenceGlyph::SIDEPRODUCT))
            {// create arrows just for edges to products or sideproducts
              std::vector<CLLineSegment> segments = curve.getCurveSegments();
              CLLineSegment lastSeg = segments[curve.getNumCurveSegments() - 1];
              //std::cout << "number of segments in curve: " << curve.getNumCurveSegments() << std::endl;
              CLPoint p = lastSeg.getEnd();
              //std::cout << "end:   " << p << std::endl;
              CArrow *ar = new CArrow(lastSeg, p.getX(), p.getY());
              nodeArrowMap.insert(std::pair<std::string, CArrow>
                                  (nodeKey, *ar));
              //viewerArrows.push_back(*ar);
              //storeCurveInCorrespondingNode(nodeKey, viewerCurves.size() - 1, viewerArrows.size() - 1); //store with arrow index, see below
            }
          //else // store without arrow
          //storeCurveInCorrespondingNode(nodeKey, viewerCurves.size() - 1); //index of curve derived from the fact that the curve currently is the last element of the vector
        } // end j
    } // end i (reactions)
  //for (i=0;i<viewerNodes.size();i++)
  // std::cout << "viewer node: " << viewerNodes[i] << std::endl;
  //std::cout << "number of curves: " << viewerCurves.size() << std::endl;

  CCopasiVector<CLTextGlyph> labels;
  labels = lP->getListOfTextGlyphs();
  std::cout << "number of labels " << labels.size() << std::endl;
  viewerLabels = std::vector<CLTextGlyph>();
  for (i = 0;i < labels.size();i++)
    {
      //cout << labels[i] << std::endl;
      //labels[i]->printLabel();
      viewerLabels.push_back(*labels[i]);
    }
  CLPoint p1 = CLPoint(0.0, 0.0);
  CLPoint p2 = CLPoint(lP->getDimensions().getWidth(), lP->getDimensions().getHeight());
  this->setGraphSize(p1, p2);
  //CQGLNetworkPainter::drawGraph();
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

void CQGLNetworkPainter::drawGraph()
{
  //std::cout << "draw graph" << std::endl;
  // create OpenGL display list
  glNewList(graphObjList, GL_COMPILE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  unsigned int i;

  // draw curves to (reactant) nodes and arrows and circular nodes when in appropriate mode

  //std::cout << "draw node in circle mode" << std::endl;
  std::map<std::string, CGraphNode>::iterator itNode;
  std::multimap<std::string, CLCurve>::iterator itCurve;
  std::multimap<std::string, CArrow>::iterator itArrow;
  std::pair<std::multimap<std::string, CLCurve>::iterator, std::multimap<std::string, CLCurve>::iterator> curveRangeIt;;
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
      arrowRangeIt = nodeArrowMap.equal_range(viewerNodes[i]);
      itArrow = arrowRangeIt.first;
      while (itArrow != arrowRangeIt.second)
        {
          //std::cout << "draw arrow " << std::endl;
          drawArrow((*itArrow).second);
          itArrow++;
        }
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
      for (i = 0;i < viewerLabels.size();i++)
        drawLabel(viewerLabels[i]);
    }
  else
    {// draw string next to circle (to the right)
      for (i = 0;i < viewerLabels.size();i++)
        {
          // xPosition of text: start from middle of label and advance to the right by the assumed size of the corresponding circle
          C_FLOAT64 x = viewerLabels[i].getX() + (viewerLabels[i].getWidth() / 2.0) + (viewerLabels[i].getHeight() / 2.0);
          C_FLOAT64 y = viewerLabels[i].getY();
          drawStringAt(viewerLabels[i].getText(), x, y, viewerLabels[i].getWidth(), viewerLabels[i].getHeight(), QColor(219, 235, 255));
        }
    }

  glEndList();
  //this->updateGL();
}

// draw node as circle
void CQGLNetworkPainter::drawNode(CGraphNode &n) // draw node as filled circle
{
  float diameter = 20.0;
  diameter = n.getSize();
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
  glColor3f(1.0f, 0.0f, 0.0f); // red
  gluDisk(qobj, 0.0, diameter / 2.0, 25, 2);
  glColor3f(0.0f, 0.0f, 0.0f); // black
  gluDisk(qobj, diameter / 2.0 - 1.0, diameter / 2.0, 25, 2);
  glTranslatef(-(float)tx, -(float)ty, 0.0f);
}

// draw a curve: at the moment just a line from the start point to the end point (for each segment)
void CQGLNetworkPainter::drawEdge(CLCurve c)
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

void CQGLNetworkPainter::drawArrow(CArrow a)
{
  // first get the two points defining the line segment (curve)
  CLPoint p2 = a.getStartOfLine();
  CLPoint p1 = a.getEndOfLine();
  // p1 and p2 define a line where the arrow peak can be placed onto
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
  C_FLOAT64 p3X = qX + (unX * a.getArrowWidth());
  C_FLOAT64 p3Y = qY + (unY * a.getArrowWidth());

  // for last point of the triangle: just go into the orther direction
  C_FLOAT64 p4X = qX - (unX * a.getArrowWidth());
  C_FLOAT64 p4Y = qY - (unY * a.getArrowWidth());
  // now draw polygon, using vertices from triangle
  //glColor3f(0.0f, 0.0f, 1.0f); // set arrow color: blue
  // now create triangle;
  //cout << "arrow triangle: " << std::endl;
  //cout << qX << "  " << qY << std::endl;
  //cout << p3X << "  " << p3Y << std::endl;
  //cout << p4X << "  " << p4Y << std::endl;
  glBegin(GL_POLYGON);
  glVertex2d(p1.getX(), p1.getY());
  glVertex2d(p3X, p3Y);
  glVertex2d(p4X, p4Y);
  glEnd();
}

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
  drawStringAt(l.getText(), l.getX(), l.getY(), l.getWidth(), l.getHeight(), QColor(61, 237, 181, QColor::Rgb));
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

void CQGLNetworkPainter::drawStringAt(std::string s, C_FLOAT64 x, C_FLOAT64 y, C_FLOAT64 w, C_FLOAT64 h, QColor bgCol)
{
  glColor3f(0.0f, 0.0f, 0.0f); // black
  //this->drawText((int)x,(int)y,QString(s));

  QFont f(FROM_UTF8(this->mFontname));
  f.setPointSize(this->mFontsize);
  QFontMetrics fm(f);
  QString str(FROM_UTF8(s));
  //QRect c((int)x,(int)y,(int)w,(int)h);

  //QRect bbox = fm.boundingRect((int)x,(int)y,(int)w,(int)h,Qt::AlignCenter,s);
  QRect bbox = fm.boundingRect(FROM_UTF8(s)); // bounding rectangle for text in certain size

  int w2 = round2powN(bbox.width()); // look for smallest w2 = 2^^k with n > w2
  int h2 = round2powN(bbox.height() + 2); // look for smallest h2 = 2^^k with n > h2
  //std::cout << "bbox w:" << w << "  h: " << h << std::endl;
  //std::cout << "bbox w2:" << w2 << "  h2: " << h2 << std::endl;
  while (h2 > h)
    {// reduce fontsize in order to avoid problems with size of texture image
      this->mFontsize--;
      f.setPointSize(this->mFontsize);
      fm = QFontMetrics(f);
      bbox = fm.boundingRect(FROM_UTF8(s));
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
  painter2.setFont(f);
  painter2.drawText(c, Qt::AlignCenter, FROM_UTF8(s));
  painter2.end();

  QImage img = pm.convertToImage();
  QImage timg = QGLWidget::convertToGLFormat(img);

  //glTexImage2D(GL_TEXTURE_2D, 0, 3, timg.width(), timg.height(), 0,
  //                  GL_RGBA, GL_UNSIGNED_BYTE, timg.bits());
  double xoff = (w - w2) / 2.0;
  double yoff = (h - h2) / 2.0;

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
  while ((p <= maxP) && (n > pow(2, p)))
    p++;
  //std::cout << "d: " << d << " p: " << p << std::endl;
  return (int)pow(2, p);
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

// set node sizes according to data set
void CQGLNetworkPainter::setNodeSizes()
{
  // test: set all node to certain size
  int i;
  // curves to nodes are changed, arrows are created newly
  nodeArrowMap.clear();
  for (i = 0;i < viewerNodes.size();i++)
    {
      std::map<std::string, CGraphNode>::iterator nodeIt;
      nodeIt = nodeMap.find(viewerNodes[i]);
      if (nodeIt != nodeMap.end())
        (*nodeIt).second.setSize(50.0); // set to test size
      // now adaptCurves pointing to nodes
      std::pair<std::multimap<std::string, CLCurve>::iterator, std::multimap<std::string, CLCurve>::iterator> curveRangeIt;;
      curveRangeIt = nodeCurveMap.equal_range(viewerNodes[i]);
      std::multimap<std::string, CLCurve>::iterator curveIt;
      curveIt = curveRangeIt.first;
      while (curveIt != curveRangeIt.second)
        {
          CLCurve *pCurve = & (*curveIt).second;
          if (pCurve != NULL)
            {
              //std::cout << "curve in node: " << this->morigNodeKey << std::endl;
              CLLineSegment* pLastSeg = pCurve->getSegmentAt(pCurve->getNumCurveSegments() - 1); // get pointer to last segment
              // move end point of segment along the line from the circle center(=from) to either the start point (line segment) or the second base point (bezier) (=to)
              // so that it lies on the border of the circle
              //std::cout << "1. last segment: " << *pLastSeg << std::endl;
              CLPoint to;
              if (pLastSeg->isBezier())
                to = pLastSeg->getBase2();
              else
                to = pLastSeg->getEnd();
              //std::cout << "node: " << (*nodeIt).second<< std::endl;
              CLPoint from = CLPoint((*nodeIt).second.getX() + ((*nodeIt).second.getWidth() / 2.0), (*nodeIt).second.getY() + ((*nodeIt).second.getHeight() / 2.0)); // center of bounding box and also of circle
              C_FLOAT64 distance = sqrt(((to.getX() - from.getX()) * (to.getX() - from.getX())) + ((to.getY() - from.getY()) * (to.getY() - from.getY())));
              //std::cout << "distance: " << distance << "  size: " << msize << std::endl;
              pLastSeg->setEnd(CLPoint(from.getX() + ((to.getX() - from.getX()) / distance * (*nodeIt).second.getSize() / 2.0),
                                       from.getY() + ((to.getY() - from.getY()) / distance * (*nodeIt).second.getSize() / 2.0)));
              // std::cout << "2. last segment: " << *pLastSeg << std::endl;
              // now insert new arrow in map
              CLPoint p = pLastSeg->getEnd();
              CArrow *ar = new CArrow(*pLastSeg, p.getX(), p.getY());
              nodeArrowMap.insert(std::pair<std::string, CArrow>
                                  (viewerNodes[i], *ar));
            }
          curveIt++;
        }
    }
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
  std::pair<std::multimap<std::string, CLCurve>::iterator, std::multimap<std::string, CLCurve>::iterator> rangeCurveIt;
  std::multimap<std::string, CLCurve>::iterator curveIt;
  for (int i = 0;i < viewerNodes.size();i++)
    {
      //curveIt = nodeCurveMap.find(viewerNodes[i]);
      rangeCurveIt = nodeCurveMap.equal_range(viewerNodes[i]);
      std::map<std::string, CGraphNode>::iterator nodeIt = nodeMap.find(viewerNodes[i]);
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
  this->drawGraph();
  //this->draw();
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
  this->setNodeSizes();
  this->mLabelShape = CIRCLE;
  this->drawGraph();
  //this->draw();
}

void CQGLNetworkPainter::adaptCurveForRectangles(std::multimap<std::string, CLCurve>::iterator it, CLBoundingBox box)
{
  // while (it != nodeCurveMap.end()){
  CLLineSegment* pLastSeg = (*it).second.getSegmentAt((*it).second.getNumCurveSegments() - 1);
  CLPoint pointOnRect = getPointOnRectangle(box, pLastSeg->getStart());
  pLastSeg->setEnd(pointOnRect);

  // create corresponding arrow and insert it into map
  CLPoint p = pLastSeg->getEnd();
  CArrow *ar = new CArrow(*pLastSeg, p.getX(), p.getY());
  nodeArrowMap.insert(std::pair<std::string, CArrow>
                      ((*it).first, *ar));
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

void CQGLNetworkPainter::zoom(C_FLOAT64 zoomFactor)
{
  //cout << "zoom  "  << zoomFactor << std::endl;

  CLPoint cMax = CLPoint(this->mgraphMax.getX() * zoomFactor, this->mgraphMax.getY() * zoomFactor);
  this->setGraphSize(this->mgraphMin, cMax);

  unsigned int i;
  //scale nodes
  for (i = 0;i < this->viewerNodes.size();i++)
    {
      std::map<std::string, CGraphNode>::iterator nodeIt;
      nodeIt = nodeMap.find(viewerNodes[i]);
      if (nodeIt != nodeMap.end())
        (*nodeIt).second.scale(zoomFactor);
      //this->viewerNodes[i].scale(zoomFactor);
    }

  //scale curves not directly pointing to a reactant/species node
  for (i = 0;i < viewerCurves.size();i++)
    {
      this->viewerCurves[i].scale(zoomFactor);
    }
  //scale curves that are associated with a reactant/species node (i.e. directly points to it)
  for (i = 0; i < viewerNodes.size();i++)
    {
      std::pair<std::multimap<std::string, CLCurve>::iterator, std::multimap<std::string, CLCurve>::iterator> curveRangeIt;
      std::multimap<std::string, CLCurve>::iterator curveIt;

      curveRangeIt = nodeCurveMap.equal_range(viewerNodes[i]);
      //curveIt = nodeCurveMap.find(viewerNodes[i]);
      curveIt = curveRangeIt.first;
      while (curveIt != curveRangeIt.second)
        {
          CLLineSegment *seg;
          int numSegs = (*curveIt).second.getNumCurveSegments();

          for (int k = 0;k < numSegs;k++)
            {
              seg = (*curveIt).second.getSegmentAt(k);
              if (seg != NULL)
                seg->scale(zoomFactor);
            }
          curveIt++;
        }
    }
  // common fontname and size for all labels are stored in this class
  this->mFontsizeDouble = this->mFontsizeDouble * zoomFactor;
  this->mFontsize = (int)this->mFontsizeDouble;
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
          (*arrowIt).second.scale(zoomFactor);
          arrowIt++;
        }

      //this->viewerArrows[i].scale(zoomFactor);
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

  glColor3f(0.0f, 1.0f, 0.0f); // grün
  glVertex3f(0.5f, -1.5f, 0.0f); // untere Ecke rechts
  glVertex3f(-0.5f, -1.5f, 0.0f); // untere Ecke links

  glColor3f(1.0f, 1.0f, 0.0f); // gelb
  glVertex3f(-1.5f, -0.5f, 0.0f); // linke Ecke unten
  glVertex3f(-1.5f, 0.5f, 0.0f); // linke Ecke oben
  glEnd(); // Zeichenaktion beenden
}

void CQGLNetworkPainter::initializeGraphPainter()
{
  mLabelShape = RECTANGLE;
  mgraphMin = CLPoint(0.0, 0.0);
  mgraphMax = CLPoint(250.0, 250.0);
  mFontname = "Helvetica";
  mFontsize = 12;
  mFontsizeDouble = 12.0; // to avoid rounding errors due to zooming in and out
  createActions();
}

void CQGLNetworkPainter::initializeGL()
{
  //std::cout << "initialize GL" << std::endl;
  // Set up the rendering context, define display lists etc.:

  //glClearColor(1.0, 1.0, 0.94, 0.0);  // background ivory
  //glClearColor(QColor(255,255,240));
  //glClearColor(1.0f, 1.0f, 0.94f, 0.0f);  // background ivory
  qglClearColor(QColor(255, 255, 240, QColor::Rgb));

  //glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  //glClearDepth(1.0f);           // Depth Buffer Setup
  //glDepthFunc(GL_LEQUAL);       // The Type Of Depth Test To Do
  //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculation

  graphObjList = glGenLists(1);
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
