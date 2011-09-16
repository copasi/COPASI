// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/qwt3dBars.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/16 18:04:44 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef BARS_H
#define BARS_H

#include "qwt3d_plot.h"

class Bar : public Qwt3D::VertexEnrichment
{
public:
  Bar();
  Bar(double rad, double showColumn = -1, double showRow = -1);
  virtual ~Bar();

  Qwt3D::Enrichment* clone() const {return new Bar(*this);}

  void configure(double rad, double showColumn, double showRow);
  void drawBegin();
  void drawEnd();
  void draw(Qwt3D::Triple const&);
  void drawZero();
  double mShowColumn;
  double mShowRow;
private:
  double level_, radius_;
  double diag_;
};

class Label3D
{
public:
  void draw(Qwt3D::Triple const&, double w, double h);
};

#endif // BARS_H
