/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/Attic/plotwidget1.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/08/06 12:57:12 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'plotwidget1.ui'
 **
 ** Created: Mon Sep 29 10:43:24 2003
 **      by: The User Interface Compiler ($Id: plotwidget1.h,v 1.11 2004/08/06 12:57:12 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef PLOTWIDGET1_H
#define PLOTWIDGET1_H

#include <vector>
#include <string>
#include <fstream>
#include <qvariant.h>

#include "CopasiUI/copasiWidget.h"
#include "plot/CPlotSpecification.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QTabWidget;
class QCheckBox;
class PlotWindow;
class Curve2DWidget;

class PlotWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    PlotWidget1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~PlotWidget1();

    // some methods according to the general guideline, mostly only stubs for now...
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected:
    bool loadFromPlotSpec(const CPlotSpecification *);
    bool saveToPlotSpec();
    void addCurveTab(const std::string & title,
                     const CPlotDataChannelSpec & x,
                     const CPlotDataChannelSpec & y);

    std::string objKey;

    //CPlotSpecification *mpPlotSpec;

    QGridLayout* PlotWidget1Layout;
    QVBoxLayout* layout20;
    QHBoxLayout* layout5;
    QVBoxLayout* layout19;
    QVBoxLayout* layout18;
    QHBoxLayout* layout17;
    QHBoxLayout* layout4;
    QVBoxLayout* layoutGrpBox;

    QLabel* titleLabel;
    QLineEdit* titleLineEdit;
    //QLabel* activeLabel;
    QCheckBox* activeCheckBox;
    QFrame* line2;
    QLabel* curveSpecLabel;
    QPushButton* addCurveButton;
    QPushButton* deleteCurveButton;
    QFrame* line3;
    QPushButton* startPlotButton;
    QPushButton* deletePlotButton;
    QPushButton* addPlotButton;
    QPushButton* resetButton;

    QTabWidget* tabs;

  protected slots:
    virtual void languageChange();

    /*
     * adds a CurveGroupBox
     */
    void addCurveGroupBox();

    /*
     * removes the CurveGroupBox in focus and delete the corresponding record
     */
    void removeCurveGroupBox();

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

    /*
     * this is called when the plot window is closed; it enables all the input fields and appropriate buttons
     */
    void plotFinished();
  };

#endif // PLOTWIDGET1_H
