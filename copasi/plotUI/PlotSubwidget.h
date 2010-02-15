// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/14 11:09:51 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef PLOTSUBWIDGET_H
#define PLOTSUBWIDGET_H

#include "ui_PlotSubwidget.h"

#include "plot/CPlotSpecification.h"

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
};

#endif // PLOTWIDGET1_H
