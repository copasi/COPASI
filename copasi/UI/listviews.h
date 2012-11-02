// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 **  $ CopasiUI/listviews.h                Modified on : 8th March, 2002
 **  $ Author  : Ankur Gupta
 *****************************************************************************/
#ifndef LISTVIEWS_H
#define LISTVIEWS_H

#include <set>
#include <qsplitter.h>
#include <QTreeView>

#include "copasi.h"

class CQTabWidget;
class CQBrowserPane;
class CQBrowserPaneDM;

class Refresh;
class CCopasiObject;

class DataModelGUI;
class QSortFilterProxyModel;
class CQCompartment;
class CQCompartmentsWidget;
class CQDifferentialEquations;
class CQEventsWidget;
class CQEventWidget1;
class FunctionWidget1;
class CQFunctionsWidget;
class CMathModel;
class CQSpeciesDetail;
class CQSpeciesWidget;
class CQEFMWidget;
class CQEFMResultWidget;
class CQGlobalQuantitiesWidget;
class CQMoietiesTaskResult;
class CQMoietiesTaskWidget;
class ParametersWidget;
class CQParameterOverviewWidget;
class ReactionsWidget1;
class CQReactionsWidget;
class SteadyStateWidget;
class ScanWidget;
class SensitivitiesWidget;
class CQSensResultWidget;
class CQSteadyStateResult;
class CQTrajectoryWidget;
class CQReportsWidget;

class CQTSSAWidget;
class CQTSSAResultWidget;
class CQTSSAResultSubWidget;

#ifdef COPASI_NONLIN_DYN
class CQCrossSectionTaskWidget;
#endif
#ifdef COPASI_NONLIN_DYN_OSCILLATION
class CQOscillationTaskWidget;
#endif

#ifdef COPASI_DEBUG
class CQUpdatesWidget;
#endif

class CQOptimizationWidget;
class CQOptimizationResult;
class CopasiWidget;
class PlotSubwidget;
class CQPlotsWidget;
class CQSplashWidget;
class CQTimeSeriesWidget;
class CQFittingWidget;
class CQFittingResult;
class CQMCAWidget;
class CMCAResultWidget;
class CQLNAWidget;
class CLNAResultWidget;
class CQReportDefinition;
class CQLyapWidget;
class CQLyapResultWidget;
class CQModelValue;
class CQMathMatrixWidget;
class CQLayoutsWidget;

//********************************************************************************

class ListViews : public QSplitter
{
  Q_OBJECT

  friend class CopasiUI3Window;

public:
  static const std::string ObjectTypeName[];

  ListViews(QWidget *parent = 0, const char *name = 0);
  virtual ~ListViews();

#ifdef DELETE
#undef DELETE
#endif
  // CHANGE does not include RENAME
  enum Action {CHANGE = 0, ADD, DELETE, RENAME};
  enum ObjectType {METABOLITE = 0
                                , COMPARTMENT
                   , REACTION
                   , FUNCTION
                   , MODEL
                   , STATE
                   , REPORT
                   , PLOT
                   , MODELVALUE
                   , EVENT
                   , MIRIAM
                   , LAYOUT
                   , PARAMETERSET
                  };

  void setDataModel(DataModelGUI* pDM);
  DataModelGUI* getDataModel() {return mpDataModelGUI;};
  void setFramework(int framework);

  void updateMIRIAMResourceContents();
  void commit();

  void switchToOtherWidget(const size_t & id, const std::string & key);

  size_t getCurrentItemId();
  CopasiWidget* findWidgetFromId(const size_t & id) const;

  // return current widget - added 02.07.08
  CopasiWidget* getCurrentWidget();

  //TODO these are convenience methods used by SliderDialog. They should be
  //replaced by something more generic.
  CQTrajectoryWidget* getTrajectoryWidget();
  SteadyStateWidget* getSteadyStateWidget();
  ScanWidget* getScanWidget();
  CQMCAWidget* getMCAWidget();
  CQLNAWidget* getLNAWidget();
  CQFittingWidget* getFittingWidget();
  CQOptimizationWidget* getOptimizationWidget();

signals:
  void signalFolderChanged(const QModelIndex & index);

private:
  CopasiWidget* findWidgetFromIndex(const QModelIndex & index) const;

  void ConstructNodeWidgets();

public slots:
  void slotFolderChanged(const QModelIndex & index);

private slots:
  bool slotNotify(ListViews::ObjectType objectType, ListViews::Action action, std::string key = "");
  void slotSort(const QModelIndex & index1, const QModelIndex & index2);

private:
  bool updateCurrentWidget(ObjectType objectType, Action action, const std::string & key = "");

  void notifyChildWidgets(ObjectType objectType,
                          Action action,
                          const std::string & key);

  DataModelGUI* mpDataModelGUI;
  CQBrowserPaneDM * mpTreeDM; // create the  object of the tree
  QSortFilterProxyModel * mpTreeSortDM;
  CMathModel *mpMathModel;
  CopasiWidget* mpCurrentWidget;
  std::string mCurrentItemKey;

  //the widgets
  CQBrowserPane *mpTreeView;

  CMCAResultWidget* mpCMCAResultWidget;
  CQMCAWidget* mpCQMCAWidget;
  CQLNAWidget* mpCQLNAWidget;
  CLNAResultWidget* mpCLNAResultWidget;
  CQCompartmentsWidget *mpCompartmentsWidget;
  CQTabWidget *compartmentsWidget1;
  CQSplashWidget *defaultWidget;
  CQDifferentialEquations *differentialEquations;
  CQEventsWidget *eventsWidget;
  CQTabWidget *eventWidget1;
  CQFunctionsWidget *mpFunctionsWidget;
  CQTabWidget *functionWidget1;
  CQLyapWidget *lyapWidget;
  CQLyapResultWidget *lyapResultWidget;
  CQSpeciesWidget *mpSpeciesWidget;
  CQTabWidget *metabolitesWidget1;
  CQTabWidget *modelWidget;
  CQGlobalQuantitiesWidget *mpGlobalQuantitiesWidget;
  CQTabWidget *mpModelValueWidget;
  CQEFMWidget *mpEFMWidget;
  CQEFMResultWidget *mpEFMResultWidget;
  CQMoietiesTaskResult *mpMoietiesTaskResult;
  CQMoietiesTaskWidget *mpMoietiesTaskWidget;
  CQOptimizationWidget *optimizationWidget;
  CQOptimizationResult *optResultWidget;
  CQFittingWidget *paramFittingWidget;
  CQFittingResult *mpFittingResultWidget;
  ParametersWidget *parametersWidget;
  CQTabWidget * mpParameterOverviewWidget;
  CQPlotsWidget *mpPlotsWidget;
  PlotSubwidget *mpPlotSubwidget;
  CQReactionsWidget *mpReactionsWidget;
  CQTabWidget *reactionsWidget1;
  ScanWidget *scanWidget;
  SensitivitiesWidget *sensWidget;
  CQSensResultWidget *sensResultWidget;
  CQSteadyStateResult *stateWidget;
  SteadyStateWidget *steadystateWidget;
  CQReportsWidget *mpReportsWidget;
  CQReportDefinition *tableDefinition1;

  CQTimeSeriesWidget *timeSeriesWidget;
  CQTrajectoryWidget *trajectoryWidget;
  CQTSSAWidget *tssaWidget;
  CQTSSAResultWidget *tssaResultWidget;

#ifdef COPASI_NONLIN_DYN
  CQCrossSectionTaskWidget *crossSectionTaskWidget;
  CQTimeSeriesWidget *crossSectionTimeSeriesWidget;
#endif
#ifdef COPASI_NONLIN_DYN_OSCILLATION
  CQOscillationTaskWidget *oscillationTaskWidget;
#endif

#ifdef COPASI_DEBUG
  CQUpdatesWidget *mpUpdatesWidget;
#endif // COPASI_DEBUG

  CQLayoutsWidget * mpLayoutsWidget;
  CQMathMatrixWidget * mpMathMatrixWidget;
};

#endif
