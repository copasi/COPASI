// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQBarChart.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2007/11/12 17:10:09 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef BARCHART_H
#define BARCHART_H

#include <qapplication.h>
#include <qlayout.h>
#include <qcolor.h>
#include "../barChart/qwt3dPlot.h"

class CQBarChart : public QWidget
  {
    Q_OBJECT
  public:

    CQBarChart(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQBarChart();
    Plot3d* mpPlot;
    QHBoxLayout* mpLayout;
    std::vector<std::string> descript;
    void emptyPlot();
    void activateSlider();
    void setData(double** data, int columns, int rows, double maxValue);
    void setDescriptions(const std::vector<std::string> *columnsDes, const std::vector<std::string> *rowsDes);
    void setColors(std::vector<QColor> mColors, double min, double max);
    //zusätzliche Einstellungen
    void showColorLegend(bool CLegend);
    void setPlotTitle(QString title);
    void plotData();
  };
#endif //BARCHART_H
