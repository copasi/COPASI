// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQBarChart.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/06/20 16:07:07 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "UI/CQBarChart.h"

#include <iostream>

CQBarChart::CQBarChart(QWidget* parent, const char* name, Qt::WFlags fl)
    : QWidget(parent, fl)
{
  setObjectName(QString::fromUtf8(name));
  QBoxLayout * mpLayout = new QHBoxLayout(this);
  mpPlot = new Plot3d(this, "bar chart");
}

CQBarChart::~CQBarChart()
{}

void CQBarChart::emptyPlot()
{
  mpPlot->emptyPlot();
}

void CQBarChart::activateSlider()
{
  mpPlot->activateSlider();
}

void CQBarChart::setData(double** data, int columns, int rows, double valueDiff)
{
  mpPlot->setData(data, columns, rows, valueDiff);
}

void CQBarChart::setDescriptions(const std::vector<std::string>* columnsDes, const std::vector<std::string>* rowsDes)
{
  mpPlot->setScale(columnsDes, rowsDes);
}

void CQBarChart::setColors(std::vector<QColor> mColors, double min, double max)
{
  mpPlot->setColors(mColors, min, max);
}

void CQBarChart::plotData()
{
  mpPlot->plotData();
}

void CQBarChart::showColorLegend(bool CLegend)
{
  mpPlot->mColorLegend = CLegend;
}

void CQBarChart::setPlotTitle(QString title)
{
  mpPlot->mTitle = title;
}

bool CQBarChart::sliderActive()
{
  if (!mpPlot) return false;

  if (mpPlot->mpSlider)
    return true;
  else
    return false;
}
