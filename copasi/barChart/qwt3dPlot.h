// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/qwt3dPlot.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2007/11/23 10:23:43 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef PLOT3D_H
#define PLOT3D_H

#include <qlayout.h>
#include <qslider.h>
#include <qmenubar.h>
#include <qcursor.h>

#include "qwt3d_surfaceplot.h"
#include "copasi/barChart/qwt3dBars.h"
#include "copasi/barChart/qwt3dScale.h"
#include "copasi/barChart/qwt3dColor.h"
#include "copasi/barChart/qwt3dBaseWidget.h"
#include "../UI/CopasiFileDialog.h"
#include "UI/qtUtilities.h"
#include "copasi.h"
#include "qmessagebox.h"
#include "qregexp.h"

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
    void contextMenuEvent (QContextMenuEvent *);

    //signals:
    //  void sliderPosition(int col, int row);
  };

#endif //  PLOT3D_H
