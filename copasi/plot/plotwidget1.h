/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/plotwidget1.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2003/10/29 15:25:38 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'plotwidget1.ui'
 **
 ** Created: Mon Sep 29 10:43:24 2003
 **      by: The User Interface Compiler ($Id: plotwidget1.h,v 1.4 2003/10/29 15:25:38 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef PLOTWIDGET1_H
#define PLOTWIDGET1_H

#include "CopasiUI/copasiWidget.h"

//#include <qapplication.h>
#include <vector>
#include <string>
#include <fstream>
#include <qvariant.h> 
//#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class CurveSpecScrollView;
class CurveGroupBox;

class PlotTaskSpec;
class PlotWindow;

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

    QLabel* titleLabel;
    QLineEdit* titleLineEdit;
    QFrame* line2;
    QLabel* curveSpecLabel;
    QPushButton* addCurveButton;
    QPushButton* deleteCurveButton;
    QFrame* line3;
    QPushButton* startPlotButton;
    QPushButton* deletePlotButton;
    QPushButton* addPlotButton;
    QPushButton* resetButton;

    CurveSpecScrollView* scrollView;

    // a vector with pointers to CurveGroupBox instances
    std::vector<CurveGroupBox*> cgrpboxes;

  protected:
    QGridLayout* PlotWidget1Layout;
    QVBoxLayout* layout20;
    QHBoxLayout* layout5;
    QVBoxLayout* layout19;
    QVBoxLayout* layout18;
    QHBoxLayout* layout17;
    QHBoxLayout* layout4;

    QVBoxLayout* layoutGrpBox;
    QVBoxLayout* layoutScrlView;

  protected slots:
    virtual void languageChange();

  public slots:

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

  private:
    // a vector of PlotTaskSpec instances - this should be incorporated into a CModel object or something similar
    // could be a dictionary of object keys and the pointers, etc.
    std::vector<PlotTaskSpec*> plotSpecVector;

    // a vector of pointers to windows that each contains a plot
    std::vector<PlotWindow*> plotWinVector;

    // a vector to hold indices of the keys of the deleted curves
    // when curves are inserted in the plot object, their indices correspond to those in the vector
    // of CurveSpec objects in PlotTaskSpec
    std::vector<int> deletedCurveIndices;

    //-------------------------------------------------------
    // the following might be incorporated elsewhere somehow

    // a vector of object keys - this is a dummy in the testing application
    // associates with pointers in plotSpecVector and plotWinVector through the vector subscripts
    std::vector<int> keys;

    // the name of the simulation output file - should be from the model
    std::string filename;

    // generates the key for a new plot
    int nextPlotKey;

    // the key of the current plot; -1 on entering the PlotWidget indicates this is a new plot.
    // also serves as the index into vectors plotSpecVector and plotWinVector
    int currentPlotKey;

    //-------------------------------------------------
    // temporary, all for the test application
    std::fstream targetfile;

    // the write position
    std::streampos pos;

    // the size of the increment
    int stepSize;

    // the count of the steps
    int count;

    void writeFile(int step);

  private slots:
    void appendData();
  };

#endif // PLOTWIDGET1_H
