// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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
#include "MIRIAMUI/CQMiriamWidget.h"

#include "CQTabWidget.h"

#include "UI/CQLayoutsWidget.h"

#include "copasi.h"

#include "CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "report/CReportDefinitionVector.h"
#include "plot/COutputDefinitionVector.h"
#include "plotUI/CQPlotSubwidget.h"
#include "model/CModel.h"
#include "CQCrossSectionTaskWidget.h"

#ifdef WITH_ANALYTICS
# include "CQAnalyticsWidget.h"
#endif // WITH_ANALYTICS

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

/***********ListViews::ConstructNodeWidgets()---------------------------->
 ** Description:-This method is used to construct all the node widgets
 *************************************************************************/
void ListViews::ConstructNodeWidgets()
{

  // create the model widgets
  if (!mpCompartmentsWidget)
    {
      mpCompartmentsWidget = new CQCompartmentsWidget(this);
      mpStackedWidget->addWidget(mpCompartmentsWidget);
    }

  if (!compartmentsWidget1)
    {
      compartmentsWidget1 = new CQTabWidget(ListViews::ObjectType::COMPARTMENT, new CQCompartment(this), this);
      mpStackedWidget->addWidget(compartmentsWidget1);
    }

#ifdef HAVE_MML

  if (!differentialEquations)
    {
      differentialEquations = new CQDifferentialEquations(this);
      mpStackedWidget->addWidget(differentialEquations);
    }

#endif // HAVE_MML

  if (!eventsWidget)
    {
      eventsWidget = new CQEventsWidget(this);
      mpStackedWidget->addWidget(eventsWidget);
    }

  if (!eventWidget1)
    {
      eventWidget1 = new CQTabWidget(ListViews::ObjectType::EVENT, new CQEventWidget1(this), this);
      mpStackedWidget->addWidget(eventWidget1);
    }

  if (!mpFunctionsWidget)
    {
      mpFunctionsWidget = new CQFunctionsWidget(this);
      mpStackedWidget->addWidget(mpFunctionsWidget);
    }

  if (!functionWidget1)
    {
      functionWidget1 = new CQTabWidget(ListViews::ObjectType::FUNCTION, new FunctionWidget1(this), this);
      mpStackedWidget->addWidget(functionWidget1);
    }

  if (!lyapWidget)
    {
      lyapWidget = new CQLyapWidget(this);
      mpStackedWidget->addWidget(lyapWidget);
    }

  if (!lyapResultWidget)
    {
      lyapResultWidget = new CQLyapResultWidget(this);
      mpStackedWidget->addWidget(lyapResultWidget);
    }

  if (!mpSpeciesWidget)
    {
      mpSpeciesWidget = new CQSpeciesWidget(this);
      mpStackedWidget->addWidget(mpSpeciesWidget);
    }

  if (!metabolitesWidget1)
    {
      metabolitesWidget1 = new CQTabWidget(ListViews::ObjectType::METABOLITE, new CQSpeciesDetail(this), this);
      mpStackedWidget->addWidget(metabolitesWidget1);
    }

  if (!modelWidget)
    {
      modelWidget = new CQTabWidget(ListViews::ObjectType::MODEL, new CQModelWidget(this), this);
      mpStackedWidget->addWidget(modelWidget);
    }

  if (!mpModelValueWidget)
    {
      mpModelValueWidget = new CQTabWidget(ListViews::ObjectType::MODELVALUE, new CQModelValue(this), this);
      mpStackedWidget->addWidget(mpModelValueWidget);
    }

  if (!mpGlobalQuantitiesWidget)
    {
      mpGlobalQuantitiesWidget = new CQGlobalQuantitiesWidget(this);
      mpStackedWidget->addWidget(mpGlobalQuantitiesWidget);
    }

  if (!mpEFMWidget)
    {
      mpEFMWidget = new CQEFMWidget(this);
      mpStackedWidget->addWidget(mpEFMWidget);
    }

  if (!mpEFMResultWidget)
    {
      mpEFMResultWidget = new CQEFMResultWidget(this);
      mpStackedWidget->addWidget(mpEFMResultWidget);
    }

  if (!mpMoietiesTaskResult)
    {
      mpMoietiesTaskResult = new CQMoietiesTaskResult(this);
      mpStackedWidget->addWidget(mpMoietiesTaskResult);
    }

  if (!mpMoietiesTaskWidget)
    {
      mpMoietiesTaskWidget = new CQMoietiesTaskWidget(this);
      mpStackedWidget->addWidget(mpMoietiesTaskWidget);
    }

  if (!mpParameterOverviewWidget)
    {
      mpParameterOverviewWidget = new CQParameterOverviewWidget(this);
      mpStackedWidget->addWidget(mpParameterOverviewWidget);
    }

  if (!mpParameterSetsWidget)
    {
      mpParameterSetsWidget = new CQParameterSetsWidget(this);
      mpStackedWidget->addWidget(mpParameterSetsWidget);
    }

  if (!mpParameterSetWidget)
    {
      CQParameterOverviewWidget* overviewWidget = new CQParameterOverviewWidget(this);
      overviewWidget->setBtnGroupVisible(false);
      mpParameterSetWidget = new CQTabWidget(ListViews::ObjectType::MODELPARAMETERSET, overviewWidget, this);

      QPushButton* btn = new QPushButton("Save to File");
      connect(btn, SIGNAL(pressed()), overviewWidget, SLOT(slotBtnSaveToFile()));
      mpParameterSetWidget->getHeaderLayout()->addWidget(btn);

      mpStackedWidget->addWidget(mpParameterSetWidget);
    }

  if (!mpCMCAResultWidget)
    {
      mpCMCAResultWidget = new CMCAResultWidget(this);
      mpStackedWidget->addWidget(mpCMCAResultWidget);
    }

  if (!mpCQMCAWidget)
    {
      mpCQMCAWidget = new CQMCAWidget(this);
      mpStackedWidget->addWidget(mpCQMCAWidget);
    }

  if (!mpCLNAResultWidget)
    {
      mpCLNAResultWidget = new CLNAResultWidget(this);
      mpStackedWidget->addWidget(mpCLNAResultWidget);
    }

  if (!mpCQLNAWidget)
    {
      mpCQLNAWidget = new CQLNAWidget(this);
      mpStackedWidget->addWidget(mpCQLNAWidget);
    }

  if (!optimizationWidget)
    {
      optimizationWidget = new CQOptimizationWidget(this);
      mpStackedWidget->addWidget(optimizationWidget);
    }

  if (!optResultWidget)
    {
      optResultWidget = new CQOptimizationResult(this);
      mpStackedWidget->addWidget(optResultWidget);
    }

  if (!paramFittingWidget)
    {
      paramFittingWidget = new CQFittingWidget(this);
      mpStackedWidget->addWidget(paramFittingWidget);
    }

  if (!mpFittingResultWidget)
    {
      mpFittingResultWidget = new CQFittingResult(this);
      mpStackedWidget->addWidget(mpFittingResultWidget);
    }

  if (!mpPlotsWidget)
    {
      mpPlotsWidget = new CQPlotsWidget(this);
      mpStackedWidget->addWidget(mpPlotsWidget);
    }

  if (!mpPlotSubwidget)
    {
      mpPlotSubwidget = new CQPlotSubwidget(this);
      mpStackedWidget->addWidget(mpPlotSubwidget);
    }

  if (!mpReactionsWidget)
    {
      mpReactionsWidget = new CQReactionsWidget(this);
      mpStackedWidget->addWidget(mpReactionsWidget);
    }

  if (!reactionsWidget1)
    {
      reactionsWidget1 = new CQTabWidget(ListViews::ObjectType::REACTION, new ReactionsWidget1(this), this);
      mpStackedWidget->addWidget(reactionsWidget1);
    }

  if (!scanWidget)
    {
      scanWidget = new ScanWidget(this);
      mpStackedWidget->addWidget(scanWidget);
    }

  if (!stateWidget)
    {
      stateWidget = new CQSteadyStateResult(this);
      mpStackedWidget->addWidget(stateWidget);
    }

  if (!steadystateWidget)
    {
      steadystateWidget = new SteadyStateWidget(this);
      mpStackedWidget->addWidget(steadystateWidget);
    }

  if (!mpReportsWidget)
    {
      mpReportsWidget = new CQReportsWidget(this);
      mpStackedWidget->addWidget(mpReportsWidget);
    }

  if (!mpUnitsWidget)
    {
      mpUnitsWidget = new CQUnitsWidget(this);
      mpStackedWidget->addWidget(mpUnitsWidget);
    }

  if (!mpUnitDetail)
    {
      mpUnitDetail = new CQTabWidget(ListViews::ObjectType::UNIT, new CQUnitDetail(this), this);
      mpStackedWidget->addWidget(mpUnitDetail);
    }

  if (!tableDefinition1)
    {
      tableDefinition1 = new CQReportDefinition(this);
      mpStackedWidget->addWidget(tableDefinition1);
    }

  if (!sensWidget)
    {
      sensWidget = new SensitivitiesWidget(this);
      mpStackedWidget->addWidget(sensWidget);
    }

  if (!sensResultWidget)
    {
      sensResultWidget = new CQSensResultWidget(this);
      mpStackedWidget->addWidget(sensResultWidget);
    }

  if (!timeSeriesWidget)
    {
      timeSeriesWidget = new CQTimeSeriesWidget(this);
      mpStackedWidget->addWidget(timeSeriesWidget);
    }

  if (!trajectoryWidget)
    {
      trajectoryWidget = new CQTrajectoryWidget(this);
      mpStackedWidget->addWidget(trajectoryWidget);
    }

  if (!tssaWidget)
    {
      tssaWidget = new CQTSSAWidget(this);
      mpStackedWidget->addWidget(tssaWidget);
    }

  if (!tssaResultWidget)
    {
      tssaResultWidget = new CQTSSAResultWidget(this);
      mpStackedWidget->addWidget(tssaResultWidget);
    }

  if (!crossSectionTimeSeriesWidget)
    {
      crossSectionTimeSeriesWidget = new CQTimeSeriesWidget(this);
      mpStackedWidget->addWidget(crossSectionTimeSeriesWidget);
    }

  if (!crossSectionTaskWidget)
    {
      crossSectionTaskWidget = new CQCrossSectionTaskWidget(this);
      mpStackedWidget->addWidget(crossSectionTaskWidget);
    }

#ifdef WITH_ANALYTICS

  if (!analyticsResultWidget)
    {
      analyticsResultWidget = new CQTimeSeriesWidget(this);
      mpStackedWidget->addWidget(analyticsResultWidget);
    }

  if (!analyticsWidget)
    {
      analyticsWidget = new CQAnalyticsWidget(this);
      mpStackedWidget->addWidget(analyticsWidget);
    }

#endif // WITH_ANALYTICS

#ifdef COPASI_NONLIN_DYN_OSCILLATION

  if (!oscillationTaskWidget)
    {
      oscillationTaskWidget = new CQOscillationTaskWidget(this);
      mpStackedWidget->addWidget(oscillationTaskWidget);
    }

#endif

#ifdef COPASI_DEBUG

  if (!mpUpdatesWidget)
    {
      mpUpdatesWidget = new CQUpdatesWidget(this);
      mpStackedWidget->addWidget(mpUpdatesWidget);
    }

#endif // COPASI_DEBUG

  if (!mpMathMatrixWidget)
    {
      mpMathMatrixWidget = new CQMathMatrixWidget(this);
      mpStackedWidget->addWidget(mpMathMatrixWidget);
    }

  if (!mpLayoutsWidget)
    {
      mpLayoutsWidget = new CQLayoutsWidget(this);
      mpStackedWidget->addWidget(mpLayoutsWidget);
    }
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

  // we emit the signal after the old widget has saved
  // the changes
  emit signalFolderChanged(index);

  mpCurrentWidget = newWidget;
  mpStackedWidget->setCurrentWidget(mpCurrentWidget);

  mpTreeView->scrollTo(index);
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
