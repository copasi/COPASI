// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/qwt3dPlot.h,v $
//   $Revision: 1.4.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/04/27 17:40:54 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef PLOT3D_H
#define PLOT3D_H

// #include <qlayout.h>
// #include <qslider.h>
// #include <qmenubar.h>
// #include <qcursor.h>

#include <QString>
#include <qwt3d_surfaceplot.h>

#include "copasi/barChart/qwt3dBaseWidget.h"
#include "copasi/barChart/qwt3dBars.h"

// #include <QContextMenuEvent>
// #include <QMessagebox>
// #include <QRegexp>

// #include "copasi/barChart/qwt3dScale.h"
// #include "copasi/barChart/qwt3dColor.h"
// #include "copasi/UI/CopasiFileDialog.h"
// #include "copasi/UI/qtUtilities.h"

class QGridLayout;

class Plot3d : public BaseWidget
{
  Q_OBJECT

public:

  struct Data
  {
    int columns;
    int rows;
    double faktor;
    double columnAxeLength;
    double rowAxeLength;
    int maxItems;
    double valueZone;
    double maxValue;
    double minValue;
  };

  Data mData;

  Plot3d(QWidget* parent = 0, const char* name = 0);
  virtual ~Plot3d();
  Qwt3D::SurfacePlot* mpPlot;
  Bar *mpBar;
  QGridLayout *mpGrid;
  QString mTitle;
  double** data;
  const std::vector<std::string> *mpColumnScale;
  const std::vector<std::string> *mpRowScale;
  bool mColorLegend;
  void setScale(const std::vector<std::string> *columnsDescript, const std::vector<std::string> *rowsDescript);
  void setColors(std::vector<QColor> mColors, double min, double max);
  void setData(double** data, int columns, int rows, double valueZone);
  virtual void sliderMoved(int column, int row);
  void setData();
  void setAxes();
  void setZoom();
  void plotData();
  void setLegend();
  void setSlider();
  void setPlotTitle();
  void emptyPlot();
  void resizeCoordSys();
  int getColSliderPos();
  int getRowSliderPos();

public slots:
  void saveDataToFile();
  void showLegend();
  void hotKeysMessage();

private:
  void contextMenuEvent(QContextMenuEvent *);

  //signals:
  //  void sliderPosition(int col, int row);
};

#endif //  PLOT3D_H
