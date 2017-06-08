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

#ifndef PLOT3D_H
#define PLOT3D_H

#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

#include <QtCore/QString>
#include <qwt3d_surfaceplot.h>

#include "copasi/barChart/CQBaseWidget.h"
#include "copasi/barChart/qwt3dBars.h"



class QGridLayout;

class CQBarChart : public CQBaseWidget
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

  CQBarChart(QWidget* parent = 0, const char* name = 0);
  virtual ~CQBarChart();
  Bar *mpBar;
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

  /**
  * This method sets the user specified descriptions for the rows and columns.
  * All axes in bar graph will be marked with this description labels automatically.
  */
  void setDescriptions(const std::vector<std::string> *columnsDes, const std::vector<std::string> *rowsDes);

  /**
  * If necessary set the title in the middle over the bar graph.
  */
  void setPlotTitle(QString title);

  /**
  * Option to show or to hide the color legend.
  */
  void showColorLegend(bool CLegend);
  void showEvent(QShowEvent * event);

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
