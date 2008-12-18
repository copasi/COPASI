// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/Attic/plotwidget1.h,v $
//   $Revision: 1.18 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:04:22 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'plotwidget1.ui'
 **
 ** Created: Mon Sep 29 10:43:24 2003
 **      by: The User Interface Compiler ($Id: plotwidget1.h,v 1.18 2008/12/18 19:04:22 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef PLOTWIDGET1_H
#define PLOTWIDGET1_H

#include <vector>
#include <string>
#include <fstream>
#include <qvariant.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>
#include <Q3Frame>

#include "UI/copasiWidget.h"
#include "plot/CPlotSpecification.h"

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class QSpacerItem;
class QComboBox;
class QLineEdit;
class QCheckBox;
class QLabel;
class Q3Frame;
class QPushButton;
class QTabWidget;
class QWidget;
class QToolButton;

class PlotWindow;
class Curve2DWidget;

class PlotWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    PlotWidget1(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
    ~PlotWidget1();

    virtual bool update(ListViews::ObjectType objectType,
                        ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected:
    bool loadFromPlotSpec(const CPlotSpecification *);
    bool saveToPlotSpec();
    void addCurveTab(const std::string & title,
                     const CPlotDataChannelSpec & x,
                     const CPlotDataChannelSpec & y);
    void addHisto1DTab(const std::string & title,
                       const CPlotDataChannelSpec & x);

    std::string objKey;

    CPlotItem::Type mType;

    //CPlotSpecification *mpPlotSpec;

    Q3GridLayout* PlotWidget1Layout;
    Q3HBoxLayout* layoutTitle;
    Q3HBoxLayout* layoutButtons;
    Q3HBoxLayout* layoutCurves;
    QSpacerItem* spacerCurves;

    QComboBox* comboType;
    QLineEdit* titleLineEdit;
    QCheckBox* activeCheckBox;
    QLabel* labelTitle;
    QLabel* labelType;
    QLabel* labelScale;
    QCheckBox* checkLogX;
    QCheckBox* checkLogY;
    Q3Frame* lineButtons;
    QTabWidget* tabs;
    //    QWidget* tab;
    //    QWidget* tab_2;
    QLabel* labelCurves;
    QToolButton* addCurveButton;
    QToolButton* addHistoButton;
    QToolButton* deleteCurveButton;
    Q3Frame* line1;

    QPushButton* startPlotButton;
    QPushButton* deletePlotButton;
    QPushButton* addPlotButton;
    QPushButton* resetButton;

  protected slots:

    /*
     * adds a CurveGroupBox
     */
    void addCurveSlot();
    void addHistoSlot();

    /*
     * removes the CurveGroupBox in focus and delete the corresponding record
     */
    void removeCurve();

    /*
     * if a new plot (window) is specified, a call to the method creates a new PlotTaskSpec object
     * and starts the plot. otherwise, it reloads/restarts the specified plot.
     */
    void startPlot();

    /*
     * deletes the current plot spec.
     */
    void deletePlot();

    /*
     * presents a blank form to accept user input for a new plot spec
     */
    void addPlot();

    /*
     * this method resets the plot specification to that as saved in the model...
     */
    void resetPlot();

    void typeChanged();

    /*
     * this is called when the plot window is closed; it enables all the input fields and appropriate buttons
     */
    void plotFinished();

  protected:
    void addCurve2D();
    void addHisto1D();
  };

#endif // PLOTWIDGET1_H
