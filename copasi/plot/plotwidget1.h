/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/plotwidget1.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/14 13:43:31 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'plotwidget1.ui'
 **
 ** Created: Mon Sep 29 10:43:24 2003
 **      by: The User Interface Compiler ($Id: plotwidget1.h,v 1.13 2005/02/14 13:43:31 ssahle Exp $)
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
class QSpacerItem;
class QComboBox;
class QLineEdit;
class QCheckBox;
class QLabel;
class QFrame;
class QPushButton;
class QTabWidget;
class QWidget;
class QToolButton;

class PlotWindow;
class Curve2DWidget;

#include <qtabwidget.h>
class MyQTabWidget : public QTabWidget
  {
    Q_OBJECT

  public:
    MyQTabWidget(QWidget * parent = 0, const char * name = 0, WFlags f = 0)
        : QTabWidget(parent, name, f)
    {
      ((QWidget*)(this->tabBar()))->setStyle("platinum");
    };
  };

class PlotWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    PlotWidget1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
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

    QGridLayout* PlotWidget1Layout;
    QHBoxLayout* layoutTitle;
    QHBoxLayout* layoutButtons;
    QHBoxLayout* layoutCurves;
    QSpacerItem* spacerCurves;

    QComboBox* comboType;
    QLineEdit* titleLineEdit;
    QCheckBox* activeCheckBox;
    QLabel* labelTitle;
    QLabel* labelType;
    QLabel* labelScale;
    QCheckBox* checkLogX;
    QCheckBox* checkLogY;
    QFrame* lineButtons;
    QTabWidget* tabs;
    //    QWidget* tab;
    //    QWidget* tab_2;
    QLabel* labelCurves;
    QToolButton* addCurveButton;
    QToolButton* addHistoButton;
    QToolButton* deleteCurveButton;
    QFrame* line1;

    QPushButton* startPlotButton;
    QPushButton* deletePlotButton;
    QPushButton* addPlotButton;
    QPushButton* resetButton;

    //MyQTabWidget* tabs;
    //QTabWidget* tabs;

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
