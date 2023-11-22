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
 **  $ CopasiUI/listviews.cpp
 **  $ Author  : Ankur Gupta
 **  $ Author  : Mudita Singhal
 **  $ Author  : Mrinmayee Kulkarni
 **
 ** This file contains the definition of the routines declared in listviews.h header
 ** file.
 **
 ** This file is used to create the visual tree based on the information obtained from the data
 ** model about the tree
 **********************************************************************/
#include <QtCore/QObject>
#include <QImage>
#include <QtCore/QMap>
#include <QSortFilterProxyModel>

#include "DataModelGUI.h"
#include "CQMessageBox.h"
#include "CQBrowserPane.h"
#include "CQBrowserPaneDM.h"

#include "CQModelWidget.h"
#include "CQCompartmentsWidget.h"
#include "CQCompartment.h"
#include "CQEventsWidget.h"
#include "CQEventWidget1.h"
#include "CQFunctionsWidget.h"
#include "FunctionWidget1.h"
#ifdef HAVE_MML
# include "CQDifferentialEquations.h"
#endif // HAVE_MML
#include "CQLyapWidget.h"
#include "CQLyapResultWidget.h"
#include "CQSpeciesWidget.h"
#include "CQSpeciesDetail.h"
#include "CQGlobalQuantitiesWidget.h"
#include "CQModelValue.h"
#include "CQParameterSetsWidget.h"
#include "CQEFMWidget.h"
#include "CQEFMResultWidget.h"
#include "CQMoietiesTaskResult.h"
#include "CQMoietiesTaskWidget.h"
#include "CQParameterOverviewWidget.h"
#include "CQReactionsWidget.h"
#include "ReactionsWidget1.h"
#include "SteadyStateWidget.h"
#include "CQSteadyStateResult.h"
#include "ScanWidget.h"
#include "SensitivitiesWidget.h"
#include "CQSensResultWidget.h"
#include "CQOptimizationWidget.h"
#include "CQOptimizationResult.h"
#include "CQReportsWidget.h"
#include "CQUnitsWidget.h"
#include "CQUnitDetail.h"
#include "CQSplashWidget.h"
#include "CQTrajectoryWidget.h"
#include "CQTimeSeriesWidget.h"
#include "CQTSSAWidget.h"
#include "CQTSSAResultWidget.h"
#ifdef COPASI_DEBUG
#include "CQUpdatesWidget.h"
#endif //COPASI_DEBUG
#undef DELETE
#include "listviews.h"
#include "qtUtilities.h"
#include "CQFittingWidget.h"
#include "CQFittingResult.h"
#include "CQMCAWidget.h"
#include "CMCAResultWidget.h"
#include "CQLNAWidget.h"
#include "CLNAResultWidget.h"
#include "CQReportDefinition.h"
#include "CQPlotsWidget.h"
#include "CQMathMatrixWidget.h"
#include "copasi/MIRIAMUI/CQMiriamWidget.h"

#include "CQTabWidget.h"

#include "copasi/UI/CQLayoutsWidget.h"

#include "copasi/copasi.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/plot/COutputDefinitionVector.h"
#include "copasi/plotUI/CQPlotSubwidget.h"
#include "copasi/model/CModel.h"
#include "CQCrossSectionTaskWidget.h"

#ifdef WITH_ANALYTICS
# include "CQAnalyticsWidget.h"
#endif // WITH_ANALYTICS

#ifdef WITH_TIME_SENS
# include "CQTimeSensWidget.h"
#endif // WITH_TIME_SENS

#ifdef COPASI_NONLIN_DYN_OSCILLATION
#include "CQOscillationTaskWidget.h"
#endif

// static
const CEnumAnnotation< std::string, ListViews::ObjectType > ListViews::ObjectTypeName(
{
  "Species" // METABOLITE
  , "Compartment" // COMPARTMENT
  , "Reaction" // REACTION
  , "Function" // FUNCTION
  , "Model" // MODEL
  , "State" // STATE
  , "Report" // REPORT
  , "Plot" // PLOT
  , "Global Quantity" // MODELVALUE
  , "Event" // EVENT
  , "Annotation" //  MIRIAM
  , "Layout" // LAYOUT
  , "Parameter Set" // MODELPARAMETERSET
  , "Task" // TASK
  , "Result" //RESULT
  , "Unit" //UNIT
  , "Vector" // VECTOR
  , "Parameter Overview" // PARAMETEROVERVIEW
});

// static
const CEnumAnnotation< std::string, ListViews::ObjectType > ListViews::DataObjectType(
{
  "Metabolite" // METABOLITE
  , "Compartment" // COMPARTMENT
  , "Reaction" // REACTION
  , "Function" // FUNCTION
  , "Model" // MODEL
  , "State" // STATE (Such an object does not exist)
  , "ReportDefinition" // REPORT
  , "PlotItem" // PLOT
  , "ModelValue" // MODELVALUE
  , "Event" // EVENT
  , "CMIRIAMInfo" // MIRIAM (These are several different objects which will be handled through there parent)
  , "Layout" // LAYOUT
  , "ModelParameterSet" // MODELPARAMETERSET
  , "Task" // TASK
  , "Result" //RESULT
  , "Unit" // UNIT
  , "Vector" // VECTOR
  , "ParameterOverView" // PARAMETEROVERVIEW (Such an object does not exist)
});

// static
const CEnumAnnotation< std::string, ListViews::WidgetType > ListViews::WidgetName(
{
  "NotFound"
  , "COPASI"
  , "Model"
  , "Biochemical"
  , "Compartments"
  , "Compartment Detail"
  , "Species"
  , "Species Detail"
  , "Reactions"
  , "Reaction Detail"
  , "Global Quantities"
  , "GlobalQuantity Detail"
  , "Events"
  , "Event Detail"
  , "Parameter Overview"
  , "Parameter Sets"
  , "Parameter Set Detail"
  , "Mathematical"
  , "Differential Equations"
  , "Matrices"
  , "Update Order"
  , "Diagrams"
  , "Tasks"
  , "Steady-State"
  , "Steady-State Result"
  , "Stoichiometric Analysis"
  , "Elementary Modes"
  , "Elementary Modes Result"
  , "Mass Conservation"
  , "Mass Conservation Result"
  , "Time Course"
  , "Time Course Result"
  , "Metabolic Control Analysis"
  , "Metabolic Control Analysis Result"
  , "Lyapunov Exponents"
  , "Lyapunov Exponents Result"
  , "Time Scale Separation Analysis"
  , "Time Scale Separation Analysis Result"
  , "Time Course Sensitivities"
  , "Time Course Sensitivities Result"
  , "Cross Section"
  , "Cross Section Result"
  , "Analytics"
  , "Analytics Result"
  , "Parameter Scan"
  , "Optimization"
  , "Optimization Result"
  , "Parameter Estimation"
  , "Parameter Estimation Result"
  , "Sensitivities"
  , "Sensitivities Result"
  , "Linear Noise Approximation"
  , "Linear Noise Approximation Result"
  , "Oscillation"
  , "Output Specifications"
  , "Plots"
  , "Plot Detail"
  , "Report Templates"
  , "Report Template Detail"
  , "Functions"
  , "Function Detail"
  , "Units"
  , "Unit Detail"
});

// static
ListViews * ListViews::ancestor(QObject * qObject)
{
  QObject * pParent = qObject;

  while (pParent != NULL)
    {
      if (pParent->inherits("ListViews"))
        return static_cast< ListViews * >(pParent);

      pParent = pParent->parent();
    }

  return NULL;
}

// static
CDataModel * ListViews::dataModel(QObject * qObject)
{
  ListViews * pListView = ancestor(qObject);

  if (pListView != NULL)
    return pListView->getDataModel();

  return NULL;
}

// static
void ListViews::addUndoMetaData(QObject * qObject, CUndoData & undoData)
{
  ListViews * pListView = ListViews::ancestor(qObject);

  if (pListView != NULL)
    {
      undoData.addMetaDataProperty("Widget Type", ListViews::WidgetName[pListView->getCurrentItemId()]);

      CQTabWidget *pTabWidget = dynamic_cast<CQTabWidget *>(pListView->getCurrentWidget());

      if (pTabWidget != NULL)
        {
          undoData.addMetaDataProperty("Widget Tab", pTabWidget->getSelectedTab());
        }

      undoData.addMetaDataProperty("Widget Object CN (before)", pListView->getCurrentItemCN());
      undoData.addMetaDataProperty("Widget Object CN (after)", pListView->getCurrentItemRegisteredCN());

      if (pListView->getCurrentItemId() != WidgetType::SpeciesDetail)
        {
          undoData.addMetaDataProperty("Widget Object Name (before)", CCommonName::nameFromCN(pListView->getCurrentItemCN()));
          undoData.addMetaDataProperty("Widget Object Name (after)", CCommonName::nameFromCN(pListView->getCurrentItemRegisteredCN()));
        }
      else
        {
          undoData.addMetaDataProperty("Widget Object Name (before)", CCommonName::nameFromCN(pListView->getCurrentItemCN()) + "{" + CCommonName::compartmentNameFromCN(pListView->getCurrentItemCN()) + "}");
          undoData.addMetaDataProperty("Widget Object Name (after)", CCommonName::nameFromCN(pListView->getCurrentItemRegisteredCN()) + "{" + CCommonName::compartmentNameFromCN(pListView->getCurrentItemRegisteredCN()) + "}");
        }
    }
}

// -----------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
// Definitions of the ListViews class as declared in listviews.h
/////////////////////////////////////////////////////////////////////////

/*********ListViews::ListViews(QWidget *parent, const char *name)************
 **
 ** Parameters:- 1. QWidget* :- The parameter needed by the base class i.e QSplitter
 **              2. char* :- The name parameter needed by the base class, i.e., QSplitter
 ** Returns  :-  It does not return anything size its 2 argument constructor
 ** Description:- This is the constructor of the ListViews and is used to
 **               set up all the requirement and initialization of the
 **               components in the code.
 ************************************************************/
ListViews::ListViews(QWidget *parent,
                     DataModelGUI * pDataModelGUI,
                     CDataModel * pDataModel):

  QSplitter(Qt::Horizontal, parent),
  mpDataModelGUI(pDataModelGUI),
  mpDataModel(pDataModel),
  mpTreeDM(NULL),
  mpTreeSortDM(NULL),
  mpMathModel(NULL),
  mpCurrentWidget(NULL),
  mCurrentItemCN(),
  mCurrentItemRegisteredCN(),
  mpCMCAResultWidget(NULL),
  mpCQMCAWidget(NULL),
  mpCQLNAWidget(NULL),
  mpCLNAResultWidget(NULL),
  mpCompartmentsWidget(NULL),
  compartmentsWidget1(NULL),
  defaultWidget(NULL),
  differentialEquations(NULL),
  eventsWidget(NULL),
  eventWidget1(NULL),
  mpFunctionsWidget(NULL),
  functionWidget1(NULL),
  lyapWidget(NULL),
  lyapResultWidget(NULL),
  mpSpeciesWidget(NULL),
  metabolitesWidget1(NULL),
  modelWidget(NULL),
  mpGlobalQuantitiesWidget(NULL),
  mpModelValueWidget(NULL),
  mpEFMWidget(NULL),
  mpEFMResultWidget(NULL),
  mpMoietiesTaskResult(NULL),
  mpMoietiesTaskWidget(NULL),
  optimizationWidget(NULL),
  optResultWidget(NULL),
  paramFittingWidget(NULL),
  mpFittingResultWidget(NULL),
  mpParameterOverviewWidget(NULL),
  mpParameterSetsWidget(NULL),
  mpParameterSetWidget(NULL),
  mpPlotsWidget(NULL),
  mpPlotSubwidget(NULL),
  mpReactionsWidget(NULL),
  reactionsWidget1(NULL),
  scanWidget(NULL),
  sensWidget(NULL),
  sensResultWidget(NULL),
  stateWidget(NULL),
  steadystateWidget(NULL),
  mpReportsWidget(NULL),
  mpUnitsWidget(NULL),
  mpUnitDetail(NULL),
  tableDefinition1(NULL),
  timeSeriesWidget(NULL),
  trajectoryWidget(NULL),
  tssaWidget(NULL),
  tssaResultWidget(NULL),
  crossSectionTaskWidget(NULL),
  crossSectionTimeSeriesWidget(NULL),
#ifdef WITH_ANALYTICS
  analyticsWidget(NULL),
  analyticsResultWidget(NULL),
#endif // WITH_ANALYTICS
#ifdef WITH_TIME_SENS
  timeSensWidget(NULL),
  timeSensResultWidget(NULL),
#endif // WITH_TIME_SENS

#ifdef COPASI_NONLIN_DYN_OSCILLATION
  oscillationTaskWidget(NULL),
#endif
#ifdef COPASI_DEBUG
  mpUpdatesWidget(NULL),
#endif
  mpLayoutsWidget(NULL),
  mpMathMatrixWidget(NULL)
{
  // Sanity check
  assert(mpDataModelGUI != NULL);
  assert(mpDataModel != NULL);

  // Qt3 support to Qt4 reference states . . .
  // "Use the QSizePolicy() constructor and call the setHorizontalStretch(), setVerticalStretch(), and setHeightForWidth() functions instead."
  // The stretch was set at "1 ,1", before, but maybe it doesn't need to be explicitly set now.
  this->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));

  setChildrenCollapsible(false);

  // create a new QListview to be displayed on the screen..and set its property
  mpTreeView = new CQBrowserPane(this);
  mpTreeDM = new CQBrowserPaneDM(this);
  mpTreeSortDM = new QSortFilterProxyModel(this);

  mpTreeSortDM->setSourceModel(mpTreeDM);
  mpTreeSortDM->setSortRole(Qt::EditRole);
  mpTreeSortDM->setSortCaseSensitivity(Qt::CaseInsensitive);
  // pSortModel->sort(0, Qt::AscendingOrder);

  mpTreeView->setModel(mpTreeSortDM);
  mpTreeView->sortByColumn(0, Qt::AscendingOrder);

  mpStackedWidget = new QStackedWidget(this);
  addWidget(mpTreeView);
  addWidget(mpStackedWidget);

  if (!opaqueResize())
    setOpaqueResize();

  defaultWidget = new CQSplashWidget(this);
  mpStackedWidget->addWidget(defaultWidget);

  mpCurrentWidget = defaultWidget; // keeps track of the mpCurrentWidget in use
  mCurrentItemCN.clear();
  mCurrentItemRegisteredCN.clear();
  mpStackedWidget->setCurrentWidget(defaultWidget);

  QList<int> Sizes = sizes();
  Sizes[0] = 240;
  Sizes[1] = 560;
  setSizes(Sizes);

  ConstructNodeWidgets();

  // establishes the communication between the mpTreeView clicked and the routine called....
  connect(mpTreeDM, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(slotSort(const QModelIndex &, const QModelIndex &)));
  connect(mpDataModelGUI, SIGNAL(signalSwitchWidget(ListViews::WidgetType, const CCommonName &, int)),
          this, SLOT(slotSwitchWidget(ListViews::WidgetType, const CCommonName &, int)));
}

ListViews::~ListViews()
{
  //TODO clean up
  if (mpLayoutsWidget != NULL)
    mpLayoutsWidget->deleteLayoutWindows();
}

void ListViews::resetCache()
{
  //First Disconnect updateCompleteView() and notifyView() from DataModelGUI
  disconnect(mpDataModelGUI, SIGNAL(notifyView(ListViews::ObjectType, ListViews::Action, const CCommonName &)),
             this, SLOT(slotNotify(ListViews::ObjectType, ListViews::Action, const CCommonName &)));

  mpTreeDM->setGuiDM(mpDataModelGUI);
  mpTreeDM->setCopasiDM(mpDataModel);
  mpTreeView->expand(mpTreeSortDM->mapFromSource(mpTreeDM->index(0, 0, QModelIndex())));

  emit signalResetCache();

  connect(mpDataModelGUI, SIGNAL(notifyView(ListViews::ObjectType, ListViews::Action, const CCommonName &)),
          this, SLOT(slotNotify(ListViews::ObjectType, ListViews::Action, const CCommonName &)));
}

#define CREATE_WIDGET(variable, stackwidget, Type, parent)\
  if (!variable)\
    {\
      variable = new Type(parent);\
      stackwidget->addWidget(variable);\
    }

#define CREATE_TAB_WIDGET(variable, stackwidget, objectType, Type, parent)\
  if (!variable)\
    {\
      variable = new CQTabWidget(objectType, new Type(parent), parent);\
      stackwidget->addWidget(variable);\
    }

/***********ListViews::ConstructNodeWidgets()---------------------------->
 ** Description:-This method is used to construct all the node widgets
 *************************************************************************/
void ListViews::ConstructNodeWidgets()
{
  // construct widgets that we definitely always need, like the model widget,
  // since that will be automatically activated after startup:
  CREATE_TAB_WIDGET(modelWidget, mpStackedWidget, ListViews::ObjectType::MODEL, CQModelWidget, this);

  // we also need the optimization and parameter estimation widget, as those
  // strangely fly in from the side otherwise.
  CREATE_WIDGET(optimizationWidget, mpStackedWidget, CQOptimizationWidget, this);

  CREATE_WIDGET(paramFittingWidget, mpStackedWidget, CQFittingWidget, this);
}

CopasiWidget* ListViews::createWidgetFromId(const ListViews::WidgetType& id)
{
  switch (id)
    {
      case WidgetType::Model:
        CREATE_TAB_WIDGET(modelWidget, mpStackedWidget, ListViews::ObjectType::MODEL, CQModelWidget, this);
        return modelWidget;
        break;

      case WidgetType::Compartments:
        CREATE_WIDGET(mpCompartmentsWidget, mpStackedWidget, CQCompartmentsWidget, this);
        return mpCompartmentsWidget;
        break;

      case WidgetType::CompartmentDetail:
        CREATE_TAB_WIDGET(compartmentsWidget1, mpStackedWidget, ListViews::ObjectType::COMPARTMENT, CQCompartment, this);

        return compartmentsWidget1;
        break;

      case WidgetType::Species:
        CREATE_WIDGET(mpSpeciesWidget, mpStackedWidget, CQSpeciesWidget, this);
        return mpSpeciesWidget;
        break;

      case WidgetType::SpeciesDetail:
        CREATE_TAB_WIDGET(metabolitesWidget1, mpStackedWidget, ListViews::ObjectType::METABOLITE, CQSpeciesDetail, this);
        return metabolitesWidget1;
        break;

      case WidgetType::Reactions:
        CREATE_WIDGET(mpReactionsWidget, mpStackedWidget, CQReactionsWidget, this);
        return mpReactionsWidget;
        break;

      case WidgetType::ReactionDetail:
        CREATE_TAB_WIDGET(reactionsWidget1, mpStackedWidget, ListViews::ObjectType::REACTION, ReactionsWidget1, this);
        return reactionsWidget1;
        break;

      case WidgetType::GlobalQuantities:
        CREATE_WIDGET(mpGlobalQuantitiesWidget, mpStackedWidget, CQGlobalQuantitiesWidget, this);
        return mpGlobalQuantitiesWidget;
        break;

      case WidgetType::GlobalQuantityDetail:
        CREATE_TAB_WIDGET(mpModelValueWidget, mpStackedWidget, ListViews::ObjectType::MODELVALUE, CQModelValue, this);
        return mpModelValueWidget;
        break;

      case WidgetType::Events:
        CREATE_WIDGET(eventsWidget, mpStackedWidget, CQEventsWidget, this);
        return eventsWidget;
        break;

      case WidgetType::EventDetail:
        CREATE_TAB_WIDGET(eventWidget1, mpStackedWidget, ListViews::ObjectType::EVENT, CQEventWidget1, this);
        return eventWidget1;
        break;

      case WidgetType::ParameterOverview:
        CREATE_WIDGET(mpParameterOverviewWidget, mpStackedWidget, CQParameterOverviewWidget, this);
        return mpParameterOverviewWidget;
        break;

      case WidgetType::ParameterSets:
        CREATE_WIDGET(mpParameterSetsWidget, mpStackedWidget, CQParameterSetsWidget, this);
        return mpParameterSetsWidget;
        break;

      case WidgetType::ParameterSetDetail:
        if (!mpParameterSetWidget)
          {
            CQParameterOverviewWidget * overviewWidget = new CQParameterOverviewWidget(this);
            overviewWidget->setBtnGroupVisible(false);
            mpParameterSetWidget = new CQTabWidget(ListViews::ObjectType::MODELPARAMETERSET, overviewWidget, this);

            QPushButton * btn = new QPushButton("Save to File");
            connect(btn, SIGNAL(pressed()), overviewWidget, SLOT(slotBtnSaveToFile()));
            mpParameterSetWidget->getHeaderLayout()->addWidget(btn);

            mpStackedWidget->addWidget(mpParameterSetWidget);
          }

        return mpParameterSetWidget;
        break;

#  ifdef HAVE_MML

      case WidgetType::DifferentialEquations:
        CREATE_WIDGET(differentialEquations, mpStackedWidget, CQDifferentialEquations, this);
        return differentialEquations;
        break;
#  endif // HAVE_MML

      case WidgetType::Matrices:
        CREATE_WIDGET(mpMathMatrixWidget, mpStackedWidget, CQMathMatrixWidget, this);
        return mpMathMatrixWidget;
        break;

#  ifdef COPASI_DEBUG

      case WidgetType::UpdateOrder:
        CREATE_WIDGET(mpUpdatesWidget, mpStackedWidget, CQUpdatesWidget, this);
        return mpUpdatesWidget;
        break;
#  endif

      case WidgetType::Diagrams:
        CREATE_WIDGET(mpLayoutsWidget, mpStackedWidget, CQLayoutsWidget, this);
        return mpLayoutsWidget;
        break;

      case WidgetType::SteadyState:
        CREATE_WIDGET(steadystateWidget, mpStackedWidget, SteadyStateWidget, this);
        return steadystateWidget;
        break;

      case WidgetType::SteadyStateResult:
        CREATE_WIDGET(stateWidget, mpStackedWidget, CQSteadyStateResult, this);
        return stateWidget;
        break;

      case WidgetType::ElementaryModes:
        CREATE_WIDGET(mpEFMWidget, mpStackedWidget, CQEFMWidget, this);
        return mpEFMWidget;
        break;

      case WidgetType::ElementaryModesResult:
        CREATE_WIDGET(mpEFMResultWidget, mpStackedWidget, CQEFMResultWidget, this);
        return mpEFMResultWidget;
        break;

      case WidgetType::MassConservation:
        CREATE_WIDGET(mpMoietiesTaskWidget, mpStackedWidget, CQMoietiesTaskWidget, this);
        return mpMoietiesTaskWidget;
        break;

      case WidgetType::MassConservationResult:
        CREATE_WIDGET(mpMoietiesTaskResult, mpStackedWidget, CQMoietiesTaskResult, this);
        return mpMoietiesTaskResult;
        break;

      case WidgetType::TimeCourse:
        CREATE_WIDGET(trajectoryWidget, mpStackedWidget, CQTrajectoryWidget, this);
        return trajectoryWidget;
        break;

      case WidgetType::TimeCourseResult:
        CREATE_WIDGET(timeSeriesWidget, mpStackedWidget, CQTimeSeriesWidget, this);
        return timeSeriesWidget;
        break;

      case WidgetType::MetabolicControlAnalysis:
        CREATE_WIDGET(mpCQMCAWidget, mpStackedWidget, CQMCAWidget, this);
        return mpCQMCAWidget;
        break;

      case WidgetType::MetabolicControlAnalysisResult:
        CREATE_WIDGET(mpCMCAResultWidget, mpStackedWidget, CMCAResultWidget, this);
        return mpCMCAResultWidget;
        break;

      case WidgetType::LyapunovExponents:
        CREATE_WIDGET(lyapWidget, mpStackedWidget, CQLyapWidget, this);
        return lyapWidget;
        break;

      case WidgetType::LyapunovExponentsResult:
        CREATE_WIDGET(lyapResultWidget, mpStackedWidget, CQLyapResultWidget, this);
        return lyapResultWidget;
        break;

      case WidgetType::TimeScaleSeparationAnalysis:
        CREATE_WIDGET(tssaWidget, mpStackedWidget, CQTSSAWidget, this);
        return tssaWidget;
        break;

      case WidgetType::TimeScaleSeparationAnalysisResult:
        CREATE_WIDGET(tssaResultWidget, mpStackedWidget, CQTSSAResultWidget, this);
        return tssaResultWidget;
        break;

      case WidgetType::CrossSection:
        CREATE_WIDGET(crossSectionTaskWidget, mpStackedWidget, CQCrossSectionTaskWidget, this);
        return crossSectionTaskWidget;
        break;

      case WidgetType::CrossSectionResult:
        CREATE_WIDGET(crossSectionTimeSeriesWidget, mpStackedWidget, CQTimeSeriesWidget, this);
        return crossSectionTimeSeriesWidget;
        break;

#  ifdef WITH_ANALYTICS

      case WidgetType::Analysis:
        return analyticsWidget;
        break;

      case WidgetType::AnalysisResult:
        return analyticsResultWidget;
        break;
#  endif // WITH_ANALYTICS

#  ifdef WITH_TIME_SENS

      case ListViews::WidgetType::TimeCourseSensitivities:
        CREATE_WIDGET(timeSensWidget, mpStackedWidget, CQTimeSensWidget, this);
        return timeSensWidget;
        break;

      case ListViews::WidgetType::TimeCourseSensitivitiesResult:
        CREATE_WIDGET(timeSensResultWidget, mpStackedWidget, CQTimeSeriesWidget, this);
        return timeSensResultWidget;
        break;
#  endif // WITH_TIME_SENS

#  ifdef COPASI_NONLIN_DYN_OSCILLATION

      case WidgetType::Oscillation:
        return oscillationTaskWidget;
        break;
#  endif

      case WidgetType::ParameterScan:
        CREATE_WIDGET(scanWidget, mpStackedWidget, ScanWidget, this);
        return scanWidget;
        break;

      case WidgetType::Optimization:
        CREATE_WIDGET(optimizationWidget, mpStackedWidget, CQOptimizationWidget, this);
        return optimizationWidget;
        break;

      case WidgetType::OptimizationResult:
        CREATE_WIDGET(optResultWidget, mpStackedWidget, CQOptimizationResult, this);
        return optResultWidget;
        break;

      case WidgetType::ParameterEstimation:
        CREATE_WIDGET(paramFittingWidget, mpStackedWidget, CQFittingWidget, this);
        return paramFittingWidget;
        break;

      case WidgetType::ParameterEstimationResult:
        CREATE_WIDGET(mpFittingResultWidget, mpStackedWidget, CQFittingResult, this);
        return mpFittingResultWidget;
        break;

      case WidgetType::Sensitivities:
        CREATE_WIDGET(sensWidget, mpStackedWidget, SensitivitiesWidget, this);
        return sensWidget;
        break;

      case WidgetType::SensitivitiesResult:
        CREATE_WIDGET(sensResultWidget, mpStackedWidget, CQSensResultWidget, this);
        return sensResultWidget;
        break;

      case WidgetType::LinearNoiseApproximation:
        CREATE_WIDGET(mpCQLNAWidget, mpStackedWidget, CQLNAWidget, this);
        return mpCQLNAWidget;
        break;

      case WidgetType::LinearNoiseApproximationResult:
        CREATE_WIDGET(mpCLNAResultWidget, mpStackedWidget, CLNAResultWidget, this);
        return mpCLNAResultWidget;
        break;

      case WidgetType::ReportTemplates:
        CREATE_WIDGET(mpReportsWidget, mpStackedWidget, CQReportsWidget, this);
        return mpReportsWidget;
        break;

      case WidgetType::ReportTemplateDetail:
        CREATE_WIDGET(tableDefinition1, mpStackedWidget, CQReportDefinition, this);
        return tableDefinition1;
        break;

      case WidgetType::Plots:
        CREATE_WIDGET(mpPlotsWidget, mpStackedWidget, CQPlotsWidget, this);
        return mpPlotsWidget;
        break;

      case WidgetType::PlotDetail:
        CREATE_WIDGET(mpPlotSubwidget, mpStackedWidget, CQPlotSubwidget, this);
        return mpPlotSubwidget;
        break;

      case WidgetType::Functions:
        CREATE_WIDGET(mpFunctionsWidget, mpStackedWidget, CQFunctionsWidget, this);
        return mpFunctionsWidget;
        break;

      case WidgetType::FunctionDetail:
        CREATE_TAB_WIDGET(functionWidget1, mpStackedWidget, ListViews::ObjectType::FUNCTION, FunctionWidget1, this);
        return functionWidget1;
        break;

      case WidgetType::Units:
        CREATE_WIDGET(mpUnitsWidget, mpStackedWidget, CQUnitsWidget, this);
        return mpUnitsWidget;
        break;

      case WidgetType::UnitDetail:
        CREATE_TAB_WIDGET(mpUnitDetail, mpStackedWidget, ListViews::ObjectType::UNIT, CQUnitDetail, this);
        return mpUnitDetail;
        break;
    }

  //give up
  return NULL;
}

CopasiWidget * ListViews::createWidgetFromIndex(const QModelIndex & index)
{
  if (!index.isValid())
    return NULL;

  // first try ID
  WidgetType id = mpTreeDM->getIdFromIndex(index);

  if (id != WidgetType::NotFound)
    {
      return createWidgetFromId(id);
    }

  // then try parent id:
  id = mpTreeDM->getIdFromIndex(mpTreeDM->parent(index));

  return createWidgetFromId(id);
}

CopasiWidget* ListViews::findTabWidgetFromId(const ListViews::WidgetType & id) const
{
  switch (id)
    {
      case WidgetType::Compartments:
        return compartmentsWidget1;
        break;

      case WidgetType::Species:
        return metabolitesWidget1;
        break;

      case WidgetType::Reactions:
        return reactionsWidget1;
        break;

      case WidgetType::GlobalQuantities:
        return mpModelValueWidget;
        break;

      case WidgetType::Events:
        return eventWidget1;
        break;

      case WidgetType::ParameterSets:
        return mpParameterSetWidget;
        break;

      case WidgetType::ReportTemplates:
        return tableDefinition1;
        break;

      case WidgetType::Plots:
        return mpPlotSubwidget;
        break;

      case WidgetType::Functions:
        return functionWidget1;
        break;

      case WidgetType::Units:
        return mpUnitDetail;
        break;
    }

  //give up
  return NULL;
}

/**
 * tries to find the right hand side widget that belongs to an item of the tree view
 */
CopasiWidget* ListViews::findWidgetFromIndex(const QModelIndex & index) const
{
  if (!index.isValid()) return NULL;

  // first try ID
  WidgetType id = mpTreeDM->getIdFromIndex(index);

  if (id != WidgetType::NotFound)
    {

      return findWidgetFromId(id);
    }

  // then try parent id:
  id = mpTreeDM->getIdFromIndex(mpTreeDM->parent(index));

  return findTabWidgetFromId(id);
}

CopasiWidget* ListViews::findWidgetFromId(const ListViews::WidgetType & id) const
{
  switch (id)
    {
      case WidgetType::NotFound:
        break; //continue with parent id

      case WidgetType::COPASI:
        return defaultWidget;
        break;

      case WidgetType::Model:
        return modelWidget;
        break;

      case WidgetType::Compartments:
        return mpCompartmentsWidget;
        break;

      case WidgetType::CompartmentDetail:
        return compartmentsWidget1;
        break;

      case WidgetType::Species:
        return mpSpeciesWidget;
        break;

      case WidgetType::SpeciesDetail:
        return metabolitesWidget1;
        break;

      case WidgetType::Reactions:
        return mpReactionsWidget;
        break;

      case WidgetType::ReactionDetail:
        return reactionsWidget1;
        break;

      case WidgetType::GlobalQuantities:
        return mpGlobalQuantitiesWidget;
        break;

      case WidgetType::GlobalQuantityDetail:
        return mpModelValueWidget;
        break;

      case WidgetType::Events:
        return eventsWidget;
        break;

      case WidgetType::EventDetail:
        return eventWidget1;
        break;

      case WidgetType::ParameterOverview:
        return mpParameterOverviewWidget;
        break;

      case WidgetType::ParameterSets:
        return mpParameterSetsWidget;
        break;

      case WidgetType::ParameterSetDetail:
        return mpParameterSetWidget;
        break;

#ifdef HAVE_MML

      case WidgetType::DifferentialEquations:
        return differentialEquations;
        break;
#endif // HAVE_MML

      case WidgetType::Matrices:
        return mpMathMatrixWidget;
        break;
#ifdef COPASI_DEBUG

      case WidgetType::UpdateOrder:
        return mpUpdatesWidget;
        break;
#endif

      case WidgetType::Diagrams:
        return mpLayoutsWidget;
        break;

      case WidgetType::SteadyState:
        return steadystateWidget;
        break;

      case WidgetType::SteadyStateResult:
        return stateWidget;
        break;

      case WidgetType::ElementaryModes:
        return mpEFMWidget;
        break;

      case WidgetType::ElementaryModesResult:
        return mpEFMResultWidget;
        break;

      case WidgetType::MassConservation:
        return mpMoietiesTaskWidget;
        break;

      case WidgetType::MassConservationResult:
        return mpMoietiesTaskResult;
        break;

      case WidgetType::TimeCourse:
        return trajectoryWidget;
        break;

      case WidgetType::TimeCourseResult:
        return timeSeriesWidget;
        break;

      case WidgetType::MetabolicControlAnalysis:
        return mpCQMCAWidget;
        break;

      case WidgetType::MetabolicControlAnalysisResult:
        return mpCMCAResultWidget;
        break;

      case WidgetType::LyapunovExponents:
        return lyapWidget;
        break;

      case WidgetType::LyapunovExponentsResult:
        return lyapResultWidget;
        break;

      case WidgetType::TimeScaleSeparationAnalysis:
        return tssaWidget;
        break;

      case WidgetType::TimeScaleSeparationAnalysisResult:
        return tssaResultWidget;
        break;

      case WidgetType::CrossSection:
        return crossSectionTaskWidget;
        break;

      case WidgetType::CrossSectionResult:
        return crossSectionTimeSeriesWidget;
        break;

#ifdef WITH_ANALYTICS

      case WidgetType::Analysis:
        return analyticsWidget;
        break;

      case WidgetType::AnalysisResult:
        return analyticsResultWidget;
        break;
#endif // WITH_ANALYTICS

#ifdef WITH_TIME_SENS

      case ListViews::WidgetType::TimeCourseSensitivities:
        return timeSensWidget;
        break;

      case ListViews::WidgetType::TimeCourseSensitivitiesResult:
        return timeSensResultWidget;
        break;
#endif // WITH_TIME_SENS

#ifdef COPASI_NONLIN_DYN_OSCILLATION

      case WidgetType::Oscillation:
        return oscillationTaskWidget;
        break;
#endif

      case WidgetType::ParameterScan:
        return scanWidget;
        break;

      case WidgetType::Optimization:
        return optimizationWidget;
        break;

      case WidgetType::OptimizationResult:
        return optResultWidget;
        break;

      case WidgetType::ParameterEstimation:
        return paramFittingWidget;
        break;

      case WidgetType::ParameterEstimationResult:
        return mpFittingResultWidget;
        break;

      case WidgetType::Sensitivities:
        return sensWidget;
        break;

      case WidgetType::SensitivitiesResult:
        return sensResultWidget;
        break;

      case WidgetType::LinearNoiseApproximation:
        return mpCQLNAWidget;
        break;

      case WidgetType::LinearNoiseApproximationResult:
        return mpCLNAResultWidget;
        break;

      case WidgetType::ReportTemplates:
        return mpReportsWidget;
        break;

      case WidgetType::ReportTemplateDetail:
        return tableDefinition1;
        break;

      case WidgetType::Plots:
        return mpPlotsWidget;
        break;

      case WidgetType::PlotDetail:
        return mpPlotSubwidget;
        break;

      case WidgetType::Functions:
        return mpFunctionsWidget;
        break;

      case WidgetType::FunctionDetail:
        return functionWidget1;
        break;

      case WidgetType::Units:
        return mpUnitsWidget;
        break;

      case WidgetType::UnitDetail:
        return mpUnitDetail;
        break;
    }

  return NULL;
}

/************************ListViews::slotFolderChanged(QListViewItem *i)----------->
 **
 ** Parameters:- index :- pointer to the node that was selected by the user
 **
 ** Returns  :-  void(Nothing)
 ** Description:-This method is called whenever the user clicks on one of the
 ** tree view items...
 *************************************************************************************/
void ListViews::slotFolderChanged(const QModelIndex & index)
{
  bool changeWidget = true;

  if (!index.isValid()) return;

  // find the widget
  CopasiWidget* newWidget = findWidgetFromIndex(index);

  if (!newWidget)
    newWidget = createWidgetFromIndex(index);

  if (!newWidget) return; //do nothing

  const CCommonName & itemCN = mpTreeDM->getCNFromIndex(index);

  if (newWidget == mpCurrentWidget &&
      itemCN == mCurrentItemRegisteredCN)
    {
      mCurrentItemCN = mCurrentItemRegisteredCN;
      return; //do nothing
    }

  // leave old widget
  if (mpCurrentWidget)
    {
      //item may point to an invalid ListViewItem now
      QModelIndex newIndex = mpTreeView->currentIndex();

      // find the widget again (it may have changed)
      newWidget = findWidgetFromIndex(newIndex);

      changeWidget = mpCurrentWidget->leave();

      if (!changeWidget) return;
    }

  if (!newWidget) newWidget = defaultWidget; //should never happen

  // enter new widget
  if (newWidget)
    ((CopasiWidget*)newWidget)->enter(itemCN);

  // fall back
  if (!newWidget)
    {newWidget = defaultWidget;}

  mCurrentItemCN = itemCN;
  mCurrentItemRegisteredCN = itemCN;
  mpCurrentWidget = newWidget;
  mpStackedWidget->setCurrentWidget(mpCurrentWidget);

  mpTreeView->scrollTo(index);

  // we emit the signal after the old widget has saved
  // the changes
  emit signalFolderChanged(index);
}

void ListViews::switchToOtherWidget(const ListViews::WidgetType & id, const CCommonName & cn, const int & tabIndex)
{
  // do not switch if we are there already
  if (!cn.empty() &&
      cn == mCurrentItemRegisteredCN)
    {
      mCurrentItemCN = mCurrentItemRegisteredCN;
      return;
    }

  QModelIndex Index = mpTreeDM->index(id, cn);
  QModelIndex SortIndex = mpTreeSortDM->mapFromSource(Index);

  mpTreeView->setCurrentIndex(SortIndex);

  CQTabWidget *pTabWidget = dynamic_cast<CQTabWidget *>(mpCurrentWidget);

  if (pTabWidget != NULL &&
      tabIndex != -1)
    pTabWidget->selectTab(tabIndex);
}

//********** some methods to store and restore the state of the listview ****

ListViews::WidgetType ListViews::getCurrentItemId()
{
  QModelIndex index = mpTreeView->currentIndex();

  if (!index.isValid()) return WidgetType::NotFound;

  return mpTreeDM->getIdFromIndex(index);
}

//**************************************************************************************+***

//static members **************************

bool ListViews::slotNotify(ObjectType objectType, Action action, const CCommonName & cn)
{
  if (objectType != ObjectType::MODEL
      && objectType != ObjectType::STATE
      //&&  action != ADD
     )
    {
      assert(mpDataModel != NULL);
      mpDataModel->changed();
    }

  bool success = true;

  // delete the layout windows when the current model is added
  // actually it would have been better to do this when a model is deleted, but
  // the deletion notification is only sent to the listviews if the deleted
  // model had been changed.
  if (objectType == ObjectType::MODEL && action == DELETE)
    {
      if (mpLayoutsWidget)
        mpLayoutsWidget->deleteLayoutWindows();
    }

  if (!updateCurrentWidget(objectType, action, cn)) success = false;

  notifyChildWidgets(objectType, action, cn);
  emit signalNotify(objectType, action, cn);

  return success;
}

void ListViews::slotSort(const QModelIndex & /* index1 */, const QModelIndex & /* index2 */)
{
  mpTreeView->sortByColumn(0, Qt::AscendingOrder);
}

void ListViews::slotSwitchWidget(ListViews::WidgetType widgetType, const CCommonName & cn, int tabIndex)
{
  switchToOtherWidget(widgetType, cn, tabIndex);
}

bool ListViews::updateCurrentWidget(ObjectType objectType, Action action, const CCommonName & cn)
{
  bool success = true;

  if (mpCurrentWidget)
    mpCurrentWidget->update(objectType, action, cn);

  return success;
}

CopasiWidget* ListViews::getCurrentWidget()
{return this->mpCurrentWidget;}

void ListViews::clearCurrentWidget()
{
  mpCurrentWidget = NULL;
}

const CCommonName & ListViews::getCurrentItemCN() const
{
  return mCurrentItemCN;
}

const CCommonName & ListViews::getCurrentItemRegisteredCN() const
{
  return mCurrentItemRegisteredCN;
}

void ListViews::commit()
{
  if (mpCurrentWidget != NULL)
    mpCurrentWidget->leave();
}

void ListViews::notifyChildWidgets(ObjectType objectType,
                                   Action action,
                                   const CCommonName & cn)
{
  QList <CopasiWidget *> widgets = findChildren<CopasiWidget *>();
  QListIterator<CopasiWidget *> it(widgets); // iterate over the CopasiWidgets
  CopasiWidget * pCopasiWidget;

  while (it.hasNext())
    {
      if ((pCopasiWidget = it.next()) != NULL)
        {
          pCopasiWidget->update(objectType, action, cn);
        }
    }
}

void ListViews::updateMIRIAMResourceContents()
{
  QList <CQMiriamWidget *> widgets = findChildren<CQMiriamWidget *>();
  QListIterator<CQMiriamWidget *> it(widgets); // iterate over the CQMiriamWidgets
  CQMiriamWidget * pWidget;

  while (it.hasNext())
    {
      pWidget = it.next();

      if (dynamic_cast<CQMiriamWidget* >(pWidget))
        dynamic_cast<CQMiriamWidget* >(pWidget)->updateResourcesList();
    }
}

DataModelGUI * ListViews::getDataModelGUI()
{
  return mpDataModelGUI;
}

CDataModel * ListViews::getDataModel()
{
  return mpDataModel;
}

void ListViews::setFramework(int framework)
{
  QList <CopasiWidget *> widgets = findChildren<CopasiWidget *>();
  QListIterator<CopasiWidget *> it(widgets); // iterate over the CopasiWidgets
  CopasiWidget * pCopasiWidget;

  while (it.hasNext())
    {
      if ((pCopasiWidget = it.next()) != NULL)
        pCopasiWidget->setFramework(framework);
    }
}

CQTrajectoryWidget* ListViews::getTrajectoryWidget()
{
  return trajectoryWidget;
}

SteadyStateWidget* ListViews::getSteadyStateWidget()
{
  return steadystateWidget;
}

ScanWidget* ListViews::getScanWidget()
{
  return scanWidget;
}

CQMCAWidget* ListViews::getMCAWidget()
{
  return mpCQMCAWidget;
}

CQLNAWidget* ListViews::getLNAWidget()
{
  return mpCQLNAWidget;
}

CQFittingWidget* ListViews::getFittingWidget()
{
  return paramFittingWidget;
}

CQOptimizationWidget* ListViews::getOptimizationWidget()
{
  return optimizationWidget;
}

CQCrossSectionTaskWidget* ListViews::getCrossSectionWidget()
{
  return crossSectionTaskWidget;
}

#ifdef WITH_TIME_SENS
CQTimeSensWidget* ListViews::getTimeSensWidget()
{
  return timeSensWidget;
}
#endif // WITH_TIME_SENS
