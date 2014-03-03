// Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQPlotSubwidget_H
#define CQPlotSubwidget_H

#include <QtCore/QVariant>

#include "copasi/plotUI/ui_CQPlotSubwidget.h"

#include "plot/CPlotSpecification.h"

class QListWidgetItem;
class PlotWindow;
class Curve2DWidget;
class HistoWidget;
class CQPlotEditWidget;

#ifdef COPASI_BANDED_GRAPH
class BandedGraphWidget;
#endif

class CQPlotSubwidget : public CopasiWidget, public Ui::CQPlotSubwidget
{
  Q_OBJECT

private:
  Curve2DWidget *mpCurveWidget;
  HistoWidget *mpHistoWidget;
#ifdef COPASI_BANDED_GRAPH
  BandedGraphWidget* mpBandedGraphWidget;
#endif

  CQPlotEditWidget* selectControl(CPlotItem::Type type);

  void addPlotItem(CPlotItem* item);
  void selectPlotItem(CPlotItem* item);

  int getCurrentIndex();
  void setCurrentIndex(int index);
  void deleteCurve(int index);
  void deleteCurve(QListWidgetItem* item);
  int getRow(QListWidgetItem* item);
  void deleteCurves();

  QMap<QString, CPlotItem*> mList;
  CPlotItem *mLastItem;
  QList<QListWidgetItem*> mLastSelection;

  bool areOfSameType(QList<QListWidgetItem*>& items);

  void storeChanges();

  CPlotItem* updateItem(CPlotItem* item);

public:
  CQPlotSubwidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CQPlotSubwidget();

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

#ifdef COPASI_BANDED_GRAPH
  /**
   * creates banded graph widget and adds it to the tab bar
   */
  void addBandedGraphTab(const std::string & title,
                         const CPlotDataChannelSpec & x,
                         const CPlotDataChannelSpec & yone,
                         const CPlotDataChannelSpec & ytwo = CPlotDataChannelSpec());
#endif // COPASI_BANDED_GRAPH

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
#ifdef COPASI_BANDED_GRAPH
  void addBandedGraphSlot();
#endif // COPASI_BANDED_GRAPH
  void addHistoSlot();

  void  itemSelectionChanged();

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
   * copy a plot definition
   */
  void copyPlot();

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

#ifdef COPASI_BANDED_GRAPH
  /**
   * this specifically handles the creation of a banded graph. It is called when
   * the corresponding button is pressed and the plot is actually a banded graph.
   * The dialogs for choosing objects for the axes is called from here and one
   * or several banded graph descriptions are generated.
   */
  void addBandedGraph();
#endif // COPASI_BANDED_GRAPH

  /**
   * this specifically handles the creation of a histogram. It is called when
   * the corresponding button is pressed and the plot is actually 2D.
   * An empty histogram description is generated.
   */
  void addHisto1D();
};

#endif // PLOTWIDGET1_H
