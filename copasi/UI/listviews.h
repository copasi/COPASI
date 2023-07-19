// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
#include <QSplitter>
#include <QTreeView>
#include <QStackedWidget>

#include "copasi/copasi.h"

class CQTabWidget;
class CQBrowserPane;
class CQBrowserPaneDM;

class Refresh;
class CDataObject;

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
class CQParameterOverviewWidget;
class CQParameterSetsWidget;
class ReactionsWidget1;
class CQReactionsWidget;
class SteadyStateWidget;
class ScanWidget;
class SensitivitiesWidget;
class CQSensResultWidget;
class CQSteadyStateResult;
class CQTrajectoryWidget;
class CQReportsWidget;
class CQUnitsWidget;
class CQTSSAWidget;
class CQTSSAResultWidget;
class CQTSSAResultSubWidget;
class CQCrossSectionTaskWidget;
#ifdef WITH_ANALYTICS
class CQAnalyticsWidget;
#endif // WITH_ANALYTICS

#ifdef WITH_TIME_SENS
class CQTimeSensWidget;
#endif //WITH_TIME_SENS

#ifdef COPASI_NONLIN_DYN_OSCILLATION
class CQOscillationTaskWidget;
#endif

#ifdef COPASI_DEBUG
class CQUpdatesWidget;
#endif

class CQOptimizationWidget;
class CQOptimizationResult;
class CopasiWidget;
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

class CQPlotSubwidget;
class CDataModel;
class CUndoData;

#include "copasi/core/CRegisteredCommonName.h"

//********************************************************************************

class ListViews : public QSplitter
{
  Q_OBJECT

  friend class CopasiUI3Window;

public:
  static ListViews * ancestor(QObject * qObject);
  static CDataModel * dataModel(QObject * qObject);
  static void addUndoMetaData(QObject * qObject, CUndoData & undoData);

  ListViews(QWidget * parent, DataModelGUI * pDataModelGUI, CDataModel * pDataModel);
  virtual ~ListViews();

#ifdef DELETE
#undef DELETE
#endif
  // CHANGE does not include RENAME
  enum Action {CHANGE = 0, ADD, DELETE, RENAME};
  enum struct ObjectType
  {
    METABOLITE
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
    , MODELPARAMETERSET
    , TASK
    , RESULT
    , UNIT
    , VECTOR
    , PARAMETEROVERVIEW
    , __SIZE
  };

  static const CEnumAnnotation< std::string, ObjectType > ObjectTypeName;
  static const CEnumAnnotation< std::string, ObjectType > DataObjectType;

  enum struct WidgetType
  {
    NotFound
    , COPASI
    , Model
    , Biochemical
    , Compartments
    , CompartmentDetail
    , Species
    , SpeciesDetail
    , Reactions
    , ReactionDetail
    , GlobalQuantities
    , GlobalQuantityDetail
    , Events
    , EventDetail
    , ParameterOverview
    , ParameterSets
    , ParameterSetDetail
    , Mathematical
    , DifferentialEquations
    , Matrices
    , UpdateOrder
    , Diagrams
    , Tasks
    , SteadyState
    , SteadyStateResult
    , StoichiometricAnalysis
    , ElementaryModes
    , ElementaryModesResult
    , MassConservation
    , MassConservationResult
    , TimeCourse
    , TimeCourseResult
    , MetabolicControlAnalysis
    , MetabolicControlAnalysisResult
    , LyapunovExponents
    , LyapunovExponentsResult
    , TimeScaleSeparationAnalysis
    , TimeScaleSeparationAnalysisResult
    , TimeCourseSensitivities
    , TimeCourseSensitivitiesResult
    , CrossSection
    , CrossSectionResult
    , Analytics
    , AnalyticsResult
    , ParameterScan
    , Optimization
    , OptimizationResult
    , ParameterEstimation
    , ParameterEstimationResult
    , Sensitivities
    , SensitivitiesResult
    , LinearNoiseApproximation
    , LinearNoiseApproximationResult
    , Oscillation
    , OutputSpecifications
    , Plots
    , PlotDetail
    , ReportTemplates
    , ReportTemplateDetail
    , Functions
    , FunctionDetail
    , Units
    , UnitDetail
    , __SIZE
  };

  static const CEnumAnnotation< std::string, WidgetType > WidgetName;

  DataModelGUI * getDataModelGUI();
  CDataModel * getDataModel();

  void resetCache();

  void setFramework(int framework);

  void updateMIRIAMResourceContents();
  void commit();

  void switchToOtherWidget(const WidgetType & id, const CCommonName & cn, const int & tabIndex = -1);

  WidgetType getCurrentItemId();
  CopasiWidget* findWidgetFromId(const WidgetType & id) const;
  CopasiWidget* findTabWidgetFromId(const WidgetType & id) const;
  CopasiWidget * createWidgetFromIndex(const QModelIndex& index);
  CopasiWidget * createWidgetFromId(const ListViews::WidgetType & id);

  // return current widget - added 02.07.08
  CopasiWidget* getCurrentWidget();

  /*
   *
   */
  void clearCurrentWidget();

  const CCommonName & getCurrentItemCN() const;
  const CCommonName & getCurrentItemRegisteredCN() const;

  //TODO these are convenience methods used by SliderDialog. They should be
  //replaced by something more generic.
  CQTrajectoryWidget* getTrajectoryWidget();
  SteadyStateWidget* getSteadyStateWidget();
  ScanWidget* getScanWidget();
  CQMCAWidget* getMCAWidget();
  CQLNAWidget* getLNAWidget();
  CQFittingWidget* getFittingWidget();
  CQOptimizationWidget* getOptimizationWidget();

  CQCrossSectionTaskWidget* getCrossSectionWidget();
#ifdef WITH_ANALYTICS
  CQAnalyticsWidget* getAnalyticsWidget();
#endif // WITH_ANALYTICS

#ifdef WITH_TIME_SENS
  CQTimeSensWidget* getTimeSensWidget();
#endif // WITH_TIME_SENS

signals:
  void signalFolderChanged(const QModelIndex & index);
  void signalNotify(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  void signalResetCache();

private:
  CopasiWidget* findWidgetFromIndex(const QModelIndex & index) const;

  void ConstructNodeWidgets();

public slots:
  void slotFolderChanged(const QModelIndex & index);

private slots:
  bool slotNotify(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  void slotSort(const QModelIndex & index1, const QModelIndex & index2);
  void slotSwitchWidget(ListViews::WidgetType widgetType, const CCommonName & cn, int tabIndex);

private:
  bool updateCurrentWidget(ObjectType objectType, Action action, const CCommonName & cn);

  void notifyChildWidgets(ObjectType objectType,
                          Action action,
                          const CCommonName & cn);

  DataModelGUI * mpDataModelGUI;
  CDataModel * mpDataModel;

  CQBrowserPaneDM * mpTreeDM; // create the  object of the tree
  QSortFilterProxyModel * mpTreeSortDM;
  CMathModel *mpMathModel;
  CopasiWidget* mpCurrentWidget;
  CCommonName mCurrentItemCN;
  CRegisteredCommonName mCurrentItemRegisteredCN;

  //the widgets
  CQBrowserPane *mpTreeView;
  QStackedWidget *mpStackedWidget;

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
  CQParameterOverviewWidget * mpParameterOverviewWidget;
  CQParameterSetsWidget * mpParameterSetsWidget;
  CQTabWidget * mpParameterSetWidget;
  CQPlotsWidget *mpPlotsWidget;
  CQPlotSubwidget *mpPlotSubwidget;
  CQReactionsWidget *mpReactionsWidget;
  CQTabWidget *reactionsWidget1;
  ScanWidget *scanWidget;
  SensitivitiesWidget *sensWidget;
  CQSensResultWidget *sensResultWidget;
  CQSteadyStateResult *stateWidget;
  SteadyStateWidget *steadystateWidget;
  CQReportsWidget *mpReportsWidget;
  CQUnitsWidget *mpUnitsWidget;
  CQTabWidget *mpUnitDetail;
  CQReportDefinition *tableDefinition1;
  CQTimeSeriesWidget *timeSeriesWidget;
  CQTrajectoryWidget *trajectoryWidget;
  CQTSSAWidget *tssaWidget;
  CQTSSAResultWidget *tssaResultWidget;
  CQCrossSectionTaskWidget *crossSectionTaskWidget;
  CQTimeSeriesWidget *crossSectionTimeSeriesWidget;

#ifdef WITH_ANALYTICS
  CQAnalyticsWidget *analyticsWidget;
  CQTimeSeriesWidget *analyticsResultWidget;
#endif // WITH_ANALYTICS

#ifdef WITH_TIME_SENS
  CQTimeSensWidget *timeSensWidget;
  CQTimeSeriesWidget *timeSensResultWidget;
#endif // WITH_TIME_SENS

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
