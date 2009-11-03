// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/14 11:09:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef PLOTSUBWIDGET_H
#define PLOTSUBWIDGET_H

#include "ui_PlotSubwidget.h"
/*
#include <vector>
#include <string>
#include <fstream>
#include <qvariant.h>
//Added by qt3to4:
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
//#include <Q3Frame>
#include <QFrame>

#include "UI/copasiWidget.h"
 */
#include "plot/CPlotSpecification.h"

/*
class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
 */
/*
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
 */
/*
class QSpacerItem;
class QComboBox;
class QLineEdit;
class QCheckBox;
class QLabel;
//class Q3Frame;
//class QFrame;
class QPushButton;
class QTabWidget;
class QWidget;
class QToolButton;
 */
class PlotWindow;
class Curve2DWidget;

class PlotSubwidget : public CopasiWidget, public Ui::PlotSubwidget
{
  Q_OBJECT

public:
  PlotSubwidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~PlotSubwidget();

  virtual bool update(ListViews::ObjectType objectType,
                      ListViews::Action action, const std::string & key);
  virtual bool leave();

  /**
   * creates tabs for histograms from a list of objects. objects[0] is skipped,
   * so objects.size()-1 histogram descriptions are generated.
   * incr is used for all of them.
   * This method is called from HistoWidget, so that when the user chooses several
   * objects from the object selection widget several histograms can be generated
   * accordingly.
   */
  void createHistograms(std::vector<const CCopasiObject* >objects, const C_FLOAT64 & incr);

protected:
  virtual bool enterProtected();
  bool loadFromPlotSpec(const CPlotSpecification *);
  bool saveToPlotSpec();

  /**
   * creates curve widget and adds it to the tab bar
   */
  void addCurveTab(const std::string & title,
                   const CPlotDataChannelSpec & x,
                   const CPlotDataChannelSpec & y);

  /**
   * creates histogram widget and adds it to the tab bar
   */
  void addHisto1DTab(const std::string & title,
                     const CPlotDataChannelSpec & x,
                     const C_FLOAT64 & incr);

  CPlotItem::Type mType;

  /*
    Q3GridLayout* PlotWidget1Layout;
    Q3HBoxLayout* layoutTitle;
    Q3HBoxLayout* layoutButtons;
    Q3HBoxLayout* layoutCurves;
  */
  /*
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
  //  Q3Frame* lineButtons;
    QFrame* lineButtons;
    QTabWidget* tabs;
    QLabel* labelCurves;
    QToolButton* addCurveButton;
    QToolButton* addHistoButton;
    QToolButton* deleteCurveButton;
  //  Q3Frame* line1;
    QFrame* line1;

    QPushButton* startPlotButton;
    QPushButton* deletePlotButton;
    QPushButton* addPlotButton;
    QPushButton* resetButton;
  */
protected slots:

  /**
   * slots that are connected to the buttons for adding curves/histograms
   */
  void addCurveSlot();
  void addHistoSlot();

  /**
   * deletes the current tab
   */
  void removeCurve();

  /**
   *
   */
  void commitPlot();

  /**
   * deletes the current plot spec.
   */
  void deletePlot();

  /**
   * create a new plot definition
   */
  void addPlot();

  /**
   * cancels changes to the plot definition
   */
  void resetPlot();

  void typeChanged();

protected:
  /**
   * this specifically handles the creation of a 2d curve. It is called when
   * the corresponding button is pressed and the plot is actually 2D.
   * The dialogs for choosing objects for the axes is called from here and one
   * or several curve descriptions are generated.
   */
  void addCurve2D();

  /**
   * this specifically handles the creation of a histogram. It is called when
   * the corresponding button is pressed and the plot is actually 2D.
   * An empty histogram description is generated.
   */
  void addHisto1D();

private:
//  Ui::PlotSubwidget ui;
  void init();
};

#endif // PLOTWIDGET1_H
