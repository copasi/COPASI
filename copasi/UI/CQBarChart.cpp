// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQBarChart.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2007/11/13 17:08:51 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "UI/CQBarChart.h"

#include <iostream>

CQBarChart::CQBarChart(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  QBoxLayout * mpLayout = new QHBoxLayout(this);
  mpLayout->setAutoAdd(TRUE);
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

void CQBarChart::setData(double** data, int columns, int rows, double maxValue)
{
  mpPlot->setData(data, columns, rows, maxValue);
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
  if (mpPlot->mpSlider)
    return true;
  else
    return false;
}
