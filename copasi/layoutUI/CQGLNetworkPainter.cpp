// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQGLNetworkPainter.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/02/23 21:02:41 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#import <CQGLNetworkPainter.h>
#include <iostream>
#import <qfont.h>
#import <qstring.h>
//#include "FTFont.h"
//#include "FTGLPixmapFont.h"
//#include "FTGLPolygonFont.h"
#include <math.h>

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
  glLoadIdentity();
  glCallList(graphObjList);
  //testOpenGL();
}

//void CQGLNetworkPainter::createGraph(network *netP){
void CQGLNetworkPainter::createGraph(CLayout *lP)
{
  // copy graph to local variables
  //cout << "now create graph" << endl;
  CCopasiVector<CLMetabGlyph> nodes = lP->getListOfMetaboliteGlyphs();
  //viewerNodes.resize (nodes.size());
  viewerNodes = std::vector<CLMetabGlyph>();
  unsigned int i;
  for (i = 0;i < nodes.size();i++)
    {
      viewerNodes.push_back(*nodes[i]); // local vector of nodes contains objects, not pointers
      //viewerNodes[i].printObject();
    }
  CCopasiVector<CLReactionGlyph> reactions = lP->getListOfReactionGlyphs();

  //now extract curves to draw from reaction
  viewerCurves = std::vector<CLLineSegment>();
  //first get reaction arrow
  for (i = 0;i < reactions.size();i++)
    {
      CLCurve curve = (reactions[i])->getCurve();
      int j;
      std::vector<CLLineSegment> segments = curve.getCurveSegments();
      for (j = 0;j < curve.getNumCurveSegments();j++)
        {
          CLLineSegment seg = segments[i];
          viewerCurves.push_back(seg); // add copy of segment to vector
        }

      // now get curves to reactants

      CCopasiVector<CLMetabReferenceGlyph> edgesToNodesOfReaction = reactions[i]->getListOfMetabReferenceGlyphs();
      unsigned int j2;
      for (j2 = 0;j2 < edgesToNodesOfReaction.size();j2++)
        {
          const CLCurve curve = edgesToNodesOfReaction[j2]->getCurve();
          int k;
          std::vector<CLLineSegment> segments = curve.getCurveSegments();
          for (k = 0;k < curve.getNumCurveSegments();k++)
            {
              CLLineSegment seg = segments[k];
              viewerCurves.push_back(seg); // add copy of segment to vector
            }
          CLMetabReferenceGlyph::Role r = edgesToNodesOfReaction[j]->getRole();
          if ((r == CLMetabReferenceGlyph::PRODUCT) || (r == CLMetabReferenceGlyph::SIDEPRODUCT))
            {// create arrows just for edges to products or sideproducts
              CLLineSegment lastSeg = segments[curve.getNumCurveSegments() - 1];
              CLPoint p = lastSeg.getEnd();
              arrow *ar = new arrow(lastSeg, p.getX(), p.getY());
              viewerArrows.push_back(*ar);
            }
        } // end j
    } // end i (reactions)

  CCopasiVector<CLTextGlyph> labels = lP->getListOfTextGlyphs();
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
  CQGLNetworkPainter::drawGraph();
}

void CQGLNetworkPainter::drawGraph()
{
  // create OpenGL display list
  glNewList(graphObjList, GL_COMPILE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  unsigned int i;
  //for (i=0;i<viewerNodes.size();i++)
  // drawNode(viewerNodes[i]);
  for (i = 0;i < viewerCurves.size();i++)
    {
      drawEdge(viewerCurves[i]);
    }
  std::cout << "number of arrows: " << viewerArrows.size() << std::endl;
  for (i = 0;i < viewerArrows.size();i++)
    drawArrow(viewerArrows[i]);
  for (i = 0;i < viewerLabels.size();i++)
    drawLabel(viewerLabels[i]);
  //for (unsigned int i=0;i<edges.size();i++)
  // drawEdge(edges[i]);
  glEndList();
  //this->updateGL();
}

// draw node as circle
void CQGLNetworkPainter::drawNode(CLMetabGlyph &n)
{
  GLUquadricObj *qobj;
  qobj = gluNewQuadric();
  //cout << "draw node at: " << n.getX() <<  "  " << n.getY() << std::endl;
  glColor3f(0.0f, 0.0f, 1.0f); // blue
  glTranslatef((float)n.getX(), (float)n.getY(), 0.0f);
  gluDisk(qobj, 0.0, 10.0, 25, 2);
  glTranslatef(-(float)n.getX(), -(float)n.getY(), 0.0f);
}

void CQGLNetworkPainter::drawEdge(CLLineSegment c)
{
  //coordList *coordListP = c.getPoints();
  CLPoint startPoint = c.getStart();
  CLPoint endPoint = c.getEnd();
  // for the moment do not take type of curve into account

  //unsigned int numberOfPoints = c.getNumberOfPoints();
  //unsigned int i;
  C_FLOAT64 x, y;
  //glColor3f(0.0f,0.0f,1.0f); // blue
  //x = (*coordListP)[0].first;
  //y = (*coordListP)[0].second;
  glBegin(GL_LINE_STRIP);
  //cout << "number of points: " <<  numberOfPoints << endl;
  //  for (i=0;i<numberOfPoints;i++){
  //   x = (*coordListP)[i].first;
  //   y = (*coordListP)[i].second;
  //   glVertex2d(x,y);
  //}
  x = startPoint.getX();
  y = startPoint.getY();
  glVertex2d(x, y);
  x = endPoint.getX();
  y = endPoint.getY();
  glVertex2d(x, y);
  glEnd();
  // now draw edge arows to products

  //cout << e.getRole() << std::endl;
}

void CQGLNetworkPainter::drawArrow(arrow a)
{
  // first get the two points defining the line segment (curve)
  CLPoint p1 = a.getStartOfLine();
  CLPoint p2 = a.getEndOfLine();
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
  glColor3f(0.0f, 0.0f, 1.0f); // set arrow color: blue
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
  glColor3f(0.7f, 0.7f, 1.0f); // light blue
  // draw rectangle as background for text
  glBegin(GL_POLYGON);
  glVertex2d(l.getX(), l.getY());
  glVertex2d(l.getX() + l.getWidth(), l.getY());
  glVertex2d(l.getX() + l.getWidth(), l.getY() + l.getHeight());
  glVertex2d(l.getX(), l.getY() + l.getHeight());
  glEnd();
  // now draw text
  //drawStringAt(l.getText(),l.getX(),l.getY());
  renderBitmapString(l.getX(), l.getY(), l.getText(), l.getWidth(), l.getHeight());
}

void CQGLNetworkPainter::renderBitmapString(C_FLOAT64 x, C_FLOAT64 y, std::string text, C_FLOAT64 w, C_FLOAT64 h)
{
  //gl.glMaterialfv(GL.GL_FRONT_AND_BACK, GL.GL_AMBIENT_AND_DIFFUSE, fontColor, 0);
  glColor3f(0.0f, 0.0f, 0.0f); // black
  glPushMatrix();
  const char *cStr = text.c_str();
  int strLen = glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)cStr);
  C_FLOAT64 offsetX = (w - (C_FLOAT64)strLen) / 2.0;
  C_FLOAT64 offsetY = (h + 12) / 2.0; // depend on used font size (here 12 pt)
  glRasterPos2d(x + offsetX, y + offsetY - 2.0);
  //cout << "h: " << h << std::endl;
  //cout << "length of " << text << ":  " << strLen << std::endl;

  unsigned int i;
  for (i = 0;i < text.size();i++)
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
      //glutStrokeCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
  glPopMatrix();
}

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
  for (i = 0;i < this->viewerNodes.size();i++)
    {
      //this->viewerNodes[i].setX(this->viewerNodes[i].getX() * zoomFactor);
      //this->viewerNodes[i].setY(this->viewerNodes[i].getY() * zoomFactor);
      this->viewerNodes[i].scale(zoomFactor);
    }

  for (i = 0; i < viewerCurves.size();i++)
    {
      this->viewerCurves[i].scale(zoomFactor);
    }
  for (i = 0;i < viewerLabels.size();i++)
    {
      this->viewerLabels[i].scale(zoomFactor);
    }
  for (i = 0;i < viewerArrows.size();i++)
    {
      this->viewerArrows[i].zoom(zoomFactor);
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
