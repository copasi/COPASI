// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQBarChart.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2007/11/20 08:23:12 $
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

/**
 * Interface class between QwtPlot3d plus extension and COPASI.
 * Main widget to create, set and plot a 3d bar graph. If there is require
 * to couple this bar graph to a value table use the (already prepared)
 * CQArrayAnnotationWidget.
 */
class CQBarChart : public QWidget
  {
    Q_OBJECT
  public:

    CQBarChart(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQBarChart();

    /**
    * Pointer to main widget in the COPASI-specific QwtPlot3d extension.
    */
    Plot3d* mpPlot;

    /**
    * This layoutwidget holds the above declared widgegt.
    */
    QHBoxLayout* mpLayout;

    /**
    * This method sets the main data you want the represent.
    *
    * - data: 2d array with numerical data
    * - columns: number of columns in data
    * - rows: number of rows in data
    * - valuDiff: difference between the max and min value in data
    */
    void setData(double** data, int columns, int rows, double valueDiff);

    /**
    * This method sets the user specified descriptions for the rows and columns.
    * All axes in bar graph will be marked with this description labels automaticaly.
    */
    void setDescriptions(const std::vector<std::string> *columnsDes, const std::vector<std::string> *rowsDes);

    /**
    * This method sets the user specified color vector for value section of relevant values.
    * Value section is defined from minimal and maximal
    *
    * - mColors: has to have 100 colors, evenly distributed over relevant print section.
    *            All elements in the vector are of class QColor.
    * - min, max: minimal and maximal value
    */
    void setColors(std::vector<QColor> mColors, double min, double max);

    /**
    * If necessary set the title in the middle over the bar graph.
    */
    void setPlotTitle(QString title);

    /**
    * Option to show or to hide the color legend.
    */
    void showColorLegend(bool CLegend);

    /**
    * Call this method to draw the bar graph.
    */
    void plotData();

    /**
    * This method discard whole data in bar graph.
    * After this call the screened widget is empty!
    */
    void emptyPlot();

    /**
    * This method activates 2 sliders. You can move sliders to change the actualy focus
    * on the data set. Horizontally slder represents the columns and vertically the rows.
    * If e.g. the slider for rows is moved to wished position, this row is marked and all
    * other rowdescription are hidden. The last position of a row slider means that all
    * descriptions are shown and none of rows is marked.
    */
    void activateSlider();

    /**
    * Find out whether the sliders are active or not.
    */
    bool sliderActive();
  };

#endif //BARCHART_H
