// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/qwt3dBars.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2007/11/16 14:42:05 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qbitmap.h>

#include "qwt3d_color.h"
#include "qwt3d_plot.h"
#include "qwt3dBars.h"
//#include <iostream>

Bar::Bar()
{
  configure(0, -1, -1);
}

Bar::Bar(double rad, double showColumn, double showRow)
{
  configure(rad, showColumn, showRow);
}

void Bar::configure(double rad, double showColumn, double showRow)
{
  plot = 0;
  radius_ = rad;
  mShowColumn = showColumn;
  mShowRow = showRow;
}

void Bar::drawBegin()
{
  drawZero();
  diag_ = radius_;
  glLineWidth(0);
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1, 1);
}

void Bar::drawEnd()
{}

void Bar::draw(Qwt3D::Triple const& pos)
{
  Qwt3D::GLStateBewarer sb(GL_LINE_SMOOTH, true);
  sb.turnOn();

  //an option to add further labels
  //  if ((pos.x == mShowColumn) || (pos.y == mShowRow))
  //  {
  //    Label3D lb;
  //    lb.draw(pos, diag_, diag_ * 2);
  //}

  // set the zero level
  GLdouble minz = 0; //plot->hull().minVertex.z;

  Qwt3D::RGBA mTo = (*plot->dataColor())(pos);
  Qwt3D::RGBA mFrom = (*plot->dataColor())(pos.x, pos.y, minz);

  glBegin(GL_QUADS);

  if (((int)(100*pos.x) == (int)(100*mShowColumn)) || ((int)(100*pos.y) == (int)(100*mShowRow)))
    glColor3d(0.71, 0.835, 1); //(1, 0, 0);
  else
    glColor4d(mFrom.r, mFrom.g, mFrom.b, mFrom.a);
  glVertex3d(pos.x - diag_, pos.y - diag_, minz);
  glVertex3d(pos.x + diag_, pos.y - diag_, minz);
  glVertex3d(pos.x + diag_, pos.y + diag_, minz);
  glVertex3d(pos.x - diag_, pos.y + diag_, minz);

  if (((int)(100*pos.x) == (int)(100*mShowColumn)) || ((int)(100*pos.y) == (int)(100*mShowRow)))
    glColor3d(0.71, 0.835, 1); //(1, 0, 0);
  else
    glColor4d(mTo.r, mTo.g, mTo.b, mTo.a);
  glVertex3d(pos.x - diag_, pos.y - diag_, pos.z);
  glVertex3d(pos.x + diag_, pos.y - diag_, pos.z);
  glVertex3d(pos.x + diag_, pos.y + diag_, pos.z);
  glVertex3d(pos.x - diag_, pos.y + diag_, pos.z);

  glColor4d(mFrom.r, mFrom.g, mFrom.b, mFrom.a);
  glVertex3d(pos.x - diag_, pos.y - diag_, minz);
  glVertex3d(pos.x + diag_, pos.y - diag_, minz);
  glColor4d(mTo.r, mTo.g, mTo.b, mTo.a);
  glVertex3d(pos.x + diag_, pos.y - diag_, pos.z);
  glVertex3d(pos.x - diag_, pos.y - diag_, pos.z);

  glColor4d(mFrom.r, mFrom.g, mFrom.b, mFrom.a);
  glVertex3d(pos.x - diag_, pos.y + diag_, minz);
  glVertex3d(pos.x + diag_, pos.y + diag_, minz);
  glColor4d(mTo.r, mTo.g, mTo.b, mTo.a);
  glVertex3d(pos.x + diag_, pos.y + diag_, pos.z);
  glVertex3d(pos.x - diag_, pos.y + diag_, pos.z);

  glColor4d(mFrom.r, mFrom.g, mFrom.b, mFrom.a);
  glVertex3d(pos.x - diag_, pos.y - diag_, minz);
  glVertex3d(pos.x - diag_, pos.y + diag_, minz);
  glColor4d(mTo.r, mTo.g, mTo.b, mTo.a);
  glVertex3d(pos.x - diag_, pos.y + diag_, pos.z);
  glVertex3d(pos.x - diag_, pos.y - diag_, pos.z);

  glColor4d(mFrom.r, mFrom.g, mFrom.b, mFrom.a);
  glVertex3d(pos.x + diag_, pos.y - diag_, minz);
  glVertex3d(pos.x + diag_, pos.y + diag_, minz);
  glColor4d(mTo.r, mTo.g, mTo.b, mTo.a);
  glVertex3d(pos.x + diag_, pos.y + diag_, pos.z);
  glVertex3d(pos.x + diag_, pos.y - diag_, pos.z);
  glEnd();

  glColor3d(0, 0, 0);
  glBegin(GL_LINES);
  glVertex3d(pos.x - diag_, pos.y - diag_, minz); glVertex3d(pos.x + diag_, pos.y - diag_, minz);
  glVertex3d(pos.x - diag_, pos.y - diag_, pos.z); glVertex3d(pos.x + diag_, pos.y - diag_, pos.z);
  glVertex3d(pos.x - diag_, pos.y + diag_, pos.z); glVertex3d(pos.x + diag_, pos.y + diag_, pos.z);
  glVertex3d(pos.x - diag_, pos.y + diag_, minz); glVertex3d(pos.x + diag_, pos.y + diag_, minz);

  glVertex3d(pos.x - diag_, pos.y - diag_, minz); glVertex3d(pos.x - diag_, pos.y + diag_, minz);
  glVertex3d(pos.x + diag_, pos.y - diag_, minz); glVertex3d(pos.x + diag_, pos.y + diag_, minz);
  glVertex3d(pos.x + diag_, pos.y - diag_, pos.z); glVertex3d(pos.x + diag_, pos.y + diag_, pos.z);
  glVertex3d(pos.x - diag_, pos.y - diag_, pos.z); glVertex3d(pos.x - diag_, pos.y + diag_, pos.z);

  glVertex3d(pos.x - diag_, pos.y - diag_, minz); glVertex3d(pos.x - diag_, pos.y - diag_, pos.z);
  glVertex3d(pos.x + diag_, pos.y - diag_, minz); glVertex3d(pos.x + diag_, pos.y - diag_, pos.z);
  glVertex3d(pos.x + diag_, pos.y + diag_, minz); glVertex3d(pos.x + diag_, pos.y + diag_, pos.z);
  glVertex3d(pos.x - diag_, pos.y + diag_, minz); glVertex3d(pos.x - diag_, pos.y + diag_, pos.z);
  glEnd();
}

void Bar::drawZero()
{
  glColor3d(0, 0, 0);
  glBegin(GL_LINE_LOOP);
  glVertex3d(plot->hull().minVertex.x, plot->hull().minVertex.y, 0);
  glVertex3d(plot->hull().maxVertex.x, plot->hull().minVertex.y, 0);
  glVertex3d(plot->hull().maxVertex.x, plot->hull().maxVertex.y, 0);
  glVertex3d(plot->hull().minVertex.x, plot->hull().maxVertex.y, 0);
  glEnd();
}

void Label3D::draw(Qwt3D::Triple const& pos, double w, double h)
{
  double gap = 0.3;
  double posZ;
  if (pos.z < 0)
    posZ = 0;
  else
    posZ = pos.z;

  glColor3d(1, 1, 1);
  glBegin(GL_QUADS);
  glVertex3d(pos.x - w, pos.y, posZ + gap);
  glVertex3d(pos.x + w, pos.y, posZ + gap);
  glVertex3d(pos.x + w, pos.y, posZ + gap + h);
  glVertex3d(pos.x - w, pos.y, posZ + gap + h);
  glEnd();
  glColor3d(0.4, 0, 0);
  glBegin(GL_LINE_LOOP);
  glVertex3d(pos.x - w, pos.y, posZ + gap);
  glVertex3d(pos.x + w, pos.y, posZ + gap);
  glVertex3d(pos.x + w, pos.y, posZ + gap + h);
  glVertex3d(pos.x - w, pos.y, posZ + gap + h);
  glEnd();
  glBegin(GL_LINES);
  glVertex3d(pos.x, pos.y, posZ);
  glVertex3d(pos.x, pos.y, posZ + gap);
  glEnd();
}
