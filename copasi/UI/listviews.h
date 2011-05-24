// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/listviews.h,v $
//   $Revision: 1.170 $
//   $Name:  $
//   $Author: jpahle $
//   $Date: 2011/05/24 17:30:50 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include "UI/Tree.h"

class CTabWidget;

class Refresh;
class CCopasiObject;

class DataModelGUI;
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
class ReactionsWidget1;
class CQReactionsWidget;
class SteadyStateWidget;
class ScanWidget;
class SensitivitiesWidget;
class CQSensResultWidget;
class CQSteadyStateResult;
class CQTrajectoryWidget;
class CQReportsWidget;

#ifdef COPASI_TSS
class TSSWidget;
#endif // COPASI_TSS

class CQTSSAWidget;
class CQTSSAResultWidget;
class CQTSSAResultSubWidget;

#ifdef COPASI_NONLIN_DYN
class CQCrossSectionTaskWidget;
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
class TimeSeriesWidget;
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
  ListViews(QWidget *parent = 0, const char *name = 0);
  ~ListViews();

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
                  };

  void setDataModel(DataModelGUI* pDM);
  DataModelGUI* getDataModel() {return mpDataModelGUI;};
  void setFramework(int framework);

  void updateMIRIAMResourceContents();
  void commit();

  void switchToOtherWidget(C_INT32 id, const std::string & key);

  void storeCurrentItem();
  void restoreCurrentItem();
  size_t getCurrentItemId();
  CopasiWidget* findWidgetFromId(const size_t & id) const;

  // return current widget - added 02.07.08
  CopasiWidget* getCurrentWidget();

  //TODO these are convenience methods used by SliderDialog. They should be
  //replaced by something more generic when the listviews is updated for QT4
  CQTrajectoryWidget* getTrajectoryWidget();
  SteadyStateWidget* getSteadyStateWidget();
  ScanWidget* getScanWidget();
  CQMCAWidget* getMCAWidget();
  CQLNAWidget* getLNAWidget();

signals:
  void signalFolderChanged(const QModelIndex & index);


private:
  CopasiWidget* findWidgetFromIndex(const QModelIndex & index) const;

  void ConstructNodeWidgets();
  void buildExpandedMap(QMap<size_t, bool> &isExpandedMap, const IndexedNode *startNode);

private slots:
  void slotFolderChanged(const QModelIndex & index);
  void slotUpdateCompleteView();
  bool slotNotify(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");

private:

  DataModelGUI* mpDataModelGUI;

  CMathModel *mpMathModel;
  CopasiWidget* currentWidget;
  std::string lastKey;

  std::string mSaveObjectKey;
  size_t mSaveFolderID;

  bool updateCurrentWidget(ObjectType objectType, Action action, const std::string & key = "");

  void notifyChildWidgets(ObjectType objectType,
                          Action action,
                          const std::string & key);


  //the widgets
  QTreeView *mpTreeView;

  CMCAResultWidget* mpCMCAResultWidget;
  CQMCAWidget* mpCQMCAWidget;
  CQLNAWidget* mpCQLNAWidget;
  CLNAResultWidget* mpCLNAResultWidget;
  CQCompartmentsWidget *mpCompartmentsWidget;
  CTabWidget *compartmentsWidget1;
  CQSplashWidget *defaultWidget;
  CQDifferentialEquations *differentialEquations;
  CQEventsWidget *eventsWidget;
  CTabWidget *eventWidget1;
  CQFunctionsWidget *mpFunctionsWidget;
  CTabWidget *functionWidget1;
  CQLyapWidget *lyapWidget;
  CQLyapResultWidget *lyapResultWidget;
  CQSpeciesWidget *mpSpeciesWidget;
  CTabWidget *metabolitesWidget1;
  CTabWidget *modelWidget;
  CQGlobalQuantitiesWidget *mpGlobalQuantitiesWidget;
  CTabWidget *mpModelValueWidget;
  CQEFMWidget *mpEFMWidget;
  CQEFMResultWidget *mpEFMResultWidget;
  CQMoietiesTaskResult *mpMoietiesTaskResult;
  CQMoietiesTaskWidget *mpMoietiesTaskWidget;
  CQOptimizationWidget *optimizationWidget;
  CQOptimizationResult *optResultWidget;
  CQFittingWidget *paramFittingWidget;
  CQFittingResult *mpFittingResultWidget;
  ParametersWidget *parametersWidget;
  CQPlotsWidget *mpPlotsWidget;
  PlotSubwidget *mpPlotSubwidget;
  CQReactionsWidget *mpReactionsWidget;
  CTabWidget *reactionsWidget1;
  ScanWidget *scanWidget;
  SensitivitiesWidget *sensWidget;
  CQSensResultWidget *sensResultWidget;
  CQSteadyStateResult *stateWidget;
  SteadyStateWidget *steadystateWidget;
  CQReportsWidget *mpReportsWidget;
  CQReportDefinition *tableDefinition1;

#ifdef COPASI_TSS
  TSSWidget *tssWidget;
#endif // COPASI_TSS

  TimeSeriesWidget *timeSeriesWidget;
  CQTrajectoryWidget *trajectoryWidget;
  CQTSSAWidget *tssaWidget;
  CQTSSAResultWidget *tssaResultWidget;

#ifdef COPASI_NONLIN_DYN
  CQCrossSectionTaskWidget *crossSectionTaskWidget;
#endif

#ifdef COPASI_DEBUG
  CQUpdatesWidget *mpUpdatesWidget;
#endif // COPASI_DEBUG

  CQLayoutsWidget * mpLayoutsWidget;
  CQMathMatrixWidget * mpMathMatrixWidget;
};

#endif
