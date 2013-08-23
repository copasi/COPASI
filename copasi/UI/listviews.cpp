// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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
#include <qobject.h>
#include <qimage.h>
#include <QMap>
#include <QtGui/QSortFilterProxyModel>

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

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "report/CReportDefinitionVector.h"
#include "plot/COutputDefinitionVector.h"
#ifdef USE_NEW_PLOTSUBWIDGET
#include "plotUI/CQPlotSubwidget.h"
#else
#include "plotUI/PlotSubwidget.h"
#endif
#include "model/CModel.h"

#ifdef COPASI_NONLIN_DYN
#include "CQCrossSectionTaskWidget.h"
#endif

#ifdef COPASI_NONLIN_DYN_OSCILLATION
#include "CQOscillationTaskWidget.h"
#endif

// static
const std::string ListViews::ObjectTypeName[] =
{
  "Species", // METABOLITE
  "Compartment", // COMPARTMENT
  "Reaction", // REACTION
  "Function", // FUNCTION
  "Model", // MODEL
  "State", // STATE
  "Report", // REPORT
  "Plot", // PLOT
  "Global Quantity", // MODELVALUE
  "Event", // EVENT
  "Annotation", //  MIRIAM
  "Layout", // LAYOUT
  "Parameter Overview", // PARAMETEROVERVIEW
  "Parameter Set", // MODELPARAMETERSET
  ""
};

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
ListViews::ListViews(QWidget *parent, const char *name):

  QSplitter(Qt::Horizontal, parent, name),
  mpDataModelGUI(NULL),
  mpTreeDM(NULL),
  mpTreeSortDM(NULL),
  mpMathModel(NULL),
  mpCurrentWidget(NULL),
  mCurrentItemKey(),
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
  tableDefinition1(NULL),
  timeSeriesWidget(NULL),
  trajectoryWidget(NULL),
  tssaWidget(NULL),
  tssaResultWidget(NULL),
#ifdef COPASI_NONLIN_DYN
  crossSectionTaskWidget(NULL),
  crossSectionTimeSeriesWidget(NULL),
#endif
#ifdef COPASI_NONLIN_DYN_OSCILLATION
  oscillationTaskWidget(NULL),
#endif
#ifdef COPASI_DEBUG
  mpUpdatesWidget(NULL),
#endif
  mpLayoutsWidget(NULL),
  mpMathMatrixWidget(NULL)
{

  this->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred, 1, 1));
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

  defaultWidget = new CQSplashWidget(this);

  addWidget(mpTreeView);
  addWidget(defaultWidget);
  setResizeMode(mpTreeView, QSplitter::KeepSize);

  if (!opaqueResize())
    setOpaqueResize();

  mpCurrentWidget = defaultWidget; // keeps track of the mpCurrentWidget in use
  mCurrentItemKey = "";

  // establishes the communication between the mpTreeView clicked and the routine called....
  connect(mpTreeDM, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(slotSort(const QModelIndex &, const QModelIndex &)));
}

ListViews::~ListViews()
{
  //TODO clean up
}

/************************ListViews::setDataModel(DataModel<Folder>* dm)----------->
 **
 ** Parameters:- DataModel<Folder>* :- pointer to the data model to be used by all the
 **              views
 ** Returns  :-  void(Nothing)
 ** Description:-This method is used to set the datamodel to be used by the
 ** listview class to extract the data from the data-model
 ************************************************************************************/
void ListViews::setDataModel(DataModelGUI* pDM)
{
  //First Disconnect updateCompleteView() and notifyView() from DataModelGUI
  if (mpDataModelGUI)
    {
      disconnect(mpDataModelGUI, SIGNAL(notifyView(ListViews::ObjectType, ListViews::Action, std::string)),
                 this, SLOT(slotNotify(ListViews::ObjectType, ListViews::Action, std::string)));
    }

  mpDataModelGUI = pDM;
  mpTreeDM->setGuiDM(mpDataModelGUI);

  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  //Set Model for the TableView
  mpTreeDM->setCopasiDM(pDataModel);
  mpTreeView->expand(mpTreeSortDM->mapFromSource(mpTreeDM->index(0, 0, QModelIndex())));

  if (mpDataModelGUI)
    {
      connect(mpDataModelGUI, SIGNAL(notifyView(ListViews::ObjectType, ListViews::Action, const std::string &)),
              this, SLOT(slotNotify(ListViews::ObjectType, ListViews::Action, const std::string &)));
    }

  ConstructNodeWidgets();
}

/***********ListViews::ConstructNodeWidgets()---------------------------->
 ** Description:-This method is used to construct all the node widgets
 *************************************************************************/
void ListViews::ConstructNodeWidgets()
{
  // create the model widgets
  if (!mpCompartmentsWidget) mpCompartmentsWidget = new CQCompartmentsWidget(this);

  mpCompartmentsWidget->hide();

  if (!compartmentsWidget1)
    compartmentsWidget1 = new CQTabWidget(ListViews::COMPARTMENT, new CQCompartment(this), this);

  compartmentsWidget1->hide();

#ifdef HAVE_MML

  if (!differentialEquations) differentialEquations = new CQDifferentialEquations(this);

  differentialEquations->hide();
#endif // HAVE_MML

  if (!eventsWidget) eventsWidget = new CQEventsWidget(this);

  eventsWidget->hide();

  if (!eventWidget1) eventWidget1 = new CQTabWidget(ListViews::EVENT, new CQEventWidget1(this), this);

  eventWidget1->hide();

  if (!mpFunctionsWidget) mpFunctionsWidget = new CQFunctionsWidget(this);

  mpFunctionsWidget->hide();

  if (!functionWidget1)
    functionWidget1 = new CQTabWidget(ListViews::FUNCTION, new FunctionWidget1(this), this);

  functionWidget1->hide();

  if (!lyapWidget) lyapWidget = new CQLyapWidget(this);

  lyapWidget->hide();

  if (!lyapResultWidget) lyapResultWidget = new CQLyapResultWidget(this);

  lyapResultWidget->hide();

  if (!mpSpeciesWidget) mpSpeciesWidget = new CQSpeciesWidget(this);

  mpSpeciesWidget->hide();

  if (!metabolitesWidget1)
    metabolitesWidget1 = new CQTabWidget(ListViews::METABOLITE, new CQSpeciesDetail(this), this);

  metabolitesWidget1->hide();

  if (!modelWidget)
    modelWidget = new CQTabWidget(ListViews::MODEL, new CQModelWidget(this), this);

  modelWidget->hide();

  if (!mpModelValueWidget)
    mpModelValueWidget = new CQTabWidget(ListViews::MODELVALUE, new CQModelValue(this), this);

  mpModelValueWidget->hide();

  if (!mpGlobalQuantitiesWidget) mpGlobalQuantitiesWidget = new CQGlobalQuantitiesWidget(this);

  mpGlobalQuantitiesWidget->hide();

  if (!mpEFMWidget) mpEFMWidget = new CQEFMWidget(this);

  mpEFMWidget->hide();

  if (!mpEFMResultWidget) mpEFMResultWidget = new CQEFMResultWidget(this);

  mpEFMResultWidget->hide();

  if (!mpMoietiesTaskResult)
    mpMoietiesTaskResult = new CQMoietiesTaskResult(this);

  mpMoietiesTaskResult->hide();

  if (!mpMoietiesTaskWidget)
    mpMoietiesTaskWidget = new CQMoietiesTaskWidget(this);

  mpMoietiesTaskWidget->hide();

  if (!mpParameterOverviewWidget)
    mpParameterOverviewWidget = new CQParameterOverviewWidget(this);

  mpParameterOverviewWidget->hide();

  if (!mpParameterSetsWidget)
    mpParameterSetsWidget = new CQParameterSetsWidget(this);

  mpParameterSetsWidget->hide();

  if (!mpParameterSetWidget)
    mpParameterSetWidget = new CQTabWidget(ListViews::MODELPARAMETERSET, new CQParameterOverviewWidget(this), this);

  mpParameterSetWidget->hide();

  if (!mpCMCAResultWidget) mpCMCAResultWidget = new CMCAResultWidget(this);

  mpCMCAResultWidget->hide();

  if (!mpCQMCAWidget) mpCQMCAWidget = new CQMCAWidget(this);

  mpCQMCAWidget->hide();

  if (!mpCLNAResultWidget) mpCLNAResultWidget = new CLNAResultWidget(this);

  mpCLNAResultWidget->hide();

  if (!mpCQLNAWidget) mpCQLNAWidget = new CQLNAWidget(this);

  mpCQLNAWidget->hide();

  if (!optimizationWidget) optimizationWidget = new CQOptimizationWidget(this);

  optimizationWidget->hide();

  if (!optResultWidget) optResultWidget = new CQOptimizationResult(this);

  optResultWidget->hide();

  if (!paramFittingWidget) paramFittingWidget = new CQFittingWidget(this);

  paramFittingWidget->hide();

  if (!mpFittingResultWidget) mpFittingResultWidget = new CQFittingResult(this);

  mpFittingResultWidget->hide();

  if (!mpPlotsWidget) mpPlotsWidget = new CQPlotsWidget(this);

  mpPlotsWidget->hide();

#ifdef USE_NEW_PLOTSUBWIDGET

  if (!mpPlotSubwidget) mpPlotSubwidget = new CQPlotSubwidget(this);

#else

  if (!mpPlotSubwidget) mpPlotSubwidget = new PlotSubwidget(this);

#endif

  mpPlotSubwidget->hide();

  if (!mpReactionsWidget) mpReactionsWidget = new CQReactionsWidget(this);

  mpReactionsWidget->hide();

  if (!reactionsWidget1)
    reactionsWidget1 = new CQTabWidget(ListViews::REACTION, new ReactionsWidget1(this), this);

  reactionsWidget1->hide();

  if (!scanWidget) scanWidget = new ScanWidget(this);

  scanWidget->hide();

  if (!stateWidget) stateWidget = new CQSteadyStateResult(this);

  stateWidget->hide();

  if (!steadystateWidget) steadystateWidget = new SteadyStateWidget(this);

  steadystateWidget->hide();

  if (!mpReportsWidget) mpReportsWidget = new CQReportsWidget(this);

  mpReportsWidget->hide();

  if (!tableDefinition1) tableDefinition1 = new CQReportDefinition(this);

  tableDefinition1->hide();

  if (!sensWidget) sensWidget = new SensitivitiesWidget(this);

  sensWidget->hide();

  if (!sensResultWidget) sensResultWidget = new CQSensResultWidget(this);

  sensResultWidget->hide();

  if (!timeSeriesWidget) timeSeriesWidget = new CQTimeSeriesWidget(this);

  timeSeriesWidget->hide();

  if (!trajectoryWidget) trajectoryWidget = new CQTrajectoryWidget(this);

  trajectoryWidget->hide();

  if (!tssaWidget) tssaWidget = new CQTSSAWidget(this);

  tssaWidget->hide();

  if (!tssaResultWidget) tssaResultWidget = new CQTSSAResultWidget(this);

  tssaResultWidget->hide();

#ifdef COPASI_NONLIN_DYN

  if (!crossSectionTimeSeriesWidget) crossSectionTimeSeriesWidget = new CQTimeSeriesWidget(this);

  crossSectionTimeSeriesWidget->hide();

  if (!crossSectionTaskWidget) crossSectionTaskWidget = new CQCrossSectionTaskWidget(this);

  crossSectionTaskWidget->hide();

#endif
#ifdef COPASI_NONLIN_DYN_OSCILLATION

  if (!oscillationTaskWidget) oscillationTaskWidget = new CQOscillationTaskWidget(this);

  oscillationTaskWidget->hide();
#endif

#ifdef COPASI_DEBUG

  if (!mpUpdatesWidget) mpUpdatesWidget = new CQUpdatesWidget(this);

  mpUpdatesWidget->hide();
#endif // COPASI_DEBUG

  if (!mpMathMatrixWidget) mpMathMatrixWidget = new CQMathMatrixWidget(this);

  mpMathMatrixWidget->hide();

  if (!mpLayoutsWidget) mpLayoutsWidget = new CQLayoutsWidget(this);

  mpLayoutsWidget->hide();
}

/**
 * tries to find the right hand side widget that belongs to an item of the tree view
 */
CopasiWidget* ListViews::findWidgetFromIndex(const QModelIndex & index) const
{
  if (!index.isValid() || !mpDataModelGUI)
    return NULL;

  // first try ID
  size_t id = mpTreeDM->getIdFromIndex(index);

  if (id != C_INVALID_INDEX)
    {

      return findWidgetFromId(id);
    }

  // then try parent id:
  id = mpTreeDM->getIdFromIndex(mpTreeDM->parent(index));

  switch (id)
    {
      case 111:
        return compartmentsWidget1;
        break;

      case 112:
        return metabolitesWidget1;
        break;

      case 114:
        return reactionsWidget1;
        break;

      case 115:
        return mpModelValueWidget;
        break;

      case 116:
        return eventWidget1;
        break;

      case 119:
        return mpParameterSetWidget;
        break;

      case 43:
        return tableDefinition1;
        break;

      case 42:
        return mpPlotSubwidget;
        break;

      case 5:
        return functionWidget1;
        break;
    }

  //give up
  return NULL;
}

CopasiWidget* ListViews::findWidgetFromId(const size_t & id) const
{
  switch (id)
    {
      case - 1:
        break; //continue with parent id

      case 0:
        return defaultWidget;
        break;

      case 1:
        return modelWidget;
        break;

      case 111:
        return mpCompartmentsWidget;
        break;

      case 112:
        return mpSpeciesWidget;
        break;

      case 114:
        return mpReactionsWidget;
        break;

      case 115:
        return mpGlobalQuantitiesWidget;
        break;

      case 116:
        return eventsWidget;
        break;

      case 118:
        return mpParameterOverviewWidget;
        break;

      case 119:
        return mpParameterSetsWidget;
        break;

        //case 122:
        //  return functionSymbols;
        //  break;
#ifdef HAVE_MML

      case 126:
        return differentialEquations;
        break;
#endif // HAVE_MML

      case 127:
        return mpMathMatrixWidget;
        break;
#ifdef COPASI_DEBUG

      case 128:
        return mpUpdatesWidget;
        break;
#endif

      case 13:
        return mpLayoutsWidget;
        break;

      case 21:
        return steadystateWidget;
        break;

      case 211:
        return stateWidget;
        break;

      case 221:
        return mpEFMWidget;
        break;

      case 2211:
        return mpEFMResultWidget;
        break;

      case 222:
        return mpMoietiesTaskWidget;
        break;

      case 2221:
        return mpMoietiesTaskResult;
        break;

      case 23:
        return trajectoryWidget;
        break;

      case 231:
        return timeSeriesWidget;
        break;

      case 24:
        return mpCQMCAWidget;
        break;

      case 241:
        return mpCMCAResultWidget;
        break;

      case 26:
        return lyapWidget;
        break;

      case 261:
        return lyapResultWidget;
        break;

      case 27:
        return tssaWidget;
        break;

      case 271:
        return tssaResultWidget;
        break;
#ifdef COPASI_NONLIN_DYN

      case 28:
        return crossSectionTaskWidget;
        break;

      case 281:
        return crossSectionTimeSeriesWidget;
#endif
#ifdef COPASI_NONLIN_DYN_OSCILLATION

      case 29:
        return oscillationTaskWidget;
        break;
#endif

      case 31:
        return scanWidget;
        break;

      case 32:
        return optimizationWidget;
        break;

      case 321:
        return optResultWidget;
        break;

      case 33:
        return paramFittingWidget;
        break;

      case 331:
        return mpFittingResultWidget;
        break;

      case 34:
        return sensWidget;
        break;

      case 341:
        return sensResultWidget;
        break;

      case 35:
        return mpCQLNAWidget;
        break;

      case 351:
        return mpCLNAResultWidget;
        break;

      case 43:                                         //Report
        return mpReportsWidget;
        break;

      case 42:
        return mpPlotsWidget;
        break;

      case 5:
        return mpFunctionsWidget;
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

  if (!index.isValid() || !mpDataModelGUI) return;

  // find the widget
  CopasiWidget* newWidget = findWidgetFromIndex(index);

  if (!newWidget) return; //do nothing

  std::string itemKey = mpTreeDM->getKeyFromIndex(index);

  if (newWidget == mpCurrentWidget)
    if (itemKey == mCurrentItemKey) return; //do nothing

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
    ((CopasiWidget*)newWidget)->enter(itemKey);

  // fall back
  if (!newWidget)
    {newWidget = defaultWidget;}

  if (mpCurrentWidget != newWidget)
    {
      QRect size;

      if (mpCurrentWidget)
        {
          size = mpCurrentWidget->geometry();
          mpCurrentWidget->hide();
        }

      if (newWidget)
        {
          if (mpCurrentWidget)
            newWidget->setGeometry(size);

          newWidget->show();
        }
    }

  // we emit the signal after the old widget has saved
  // the changes
  emit signalFolderChanged(index);

  mpCurrentWidget = newWidget;
  mCurrentItemKey = itemKey;

  mpTreeView->scrollTo(index);
}

void ListViews::switchToOtherWidget(const size_t & id, const std::string & key)
{
  if (!mpDataModelGUI) return;

  QModelIndex Index = mpTreeDM->index(id, key);
  QModelIndex SortIndex = mpTreeSortDM->mapFromSource(Index);

  mpTreeView->setCurrentIndex(SortIndex);
}

//********** some methods to store and restore the state of the listview ****

size_t ListViews::getCurrentItemId()
{
  QModelIndex index = mpTreeView->currentIndex();

  if (!index.isValid() || !mpDataModelGUI)
    return C_INVALID_INDEX;

  return mpTreeDM->getIdFromIndex(index);
}

//**************************************************************************************+***

//static members **************************

bool ListViews::slotNotify(ObjectType objectType, Action action, std::string key)
{
  if (objectType != MODEL &&
      objectType != STATE &&
      action != ADD)
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      (*CCopasiRootContainer::getDatamodelList())[0]->changed();
    }

  bool success = true;

  // delete the layout windows when the current model is added
  // actually it would have been better to do this when a model is deleted, but
  // the deletion notification is only sent to the listviews if the deleted
  // model had been changed.
  if (objectType == MODEL && action == DELETE)
    {
      mpLayoutsWidget->deleteLayoutWindows();
    }

  if (!updateCurrentWidget(objectType, action, key)) success = false;

  notifyChildWidgets(objectType, action, key);

  return success;
}

void ListViews::slotSort(const QModelIndex & /* index1 */, const QModelIndex & /* index2 */)
{
  mpTreeView->sortByColumn(0, Qt::AscendingOrder);
}

bool ListViews::updateCurrentWidget(ObjectType objectType, Action action, const std::string & key)
{
  bool success = true;

  if (mpCurrentWidget)
    mpCurrentWidget->update(objectType, action, key);

  return success;
}

CopasiWidget* ListViews::getCurrentWidget()
{return this->mpCurrentWidget;}

void ListViews::commit()
{
  if (mpCurrentWidget != NULL)
    mpCurrentWidget->leave();
}

void ListViews::notifyChildWidgets(ObjectType objectType,
                                   Action action,
                                   const std::string & key)
{
  QList <CopasiWidget *> widgets = findChildren<CopasiWidget *>();
  QListIterator<CopasiWidget *> it(widgets); // iterate over the CopasiWidgets
  CopasiWidget * pCopasiWidget;

  while (it.hasNext())
    {
      if ((pCopasiWidget = it.next()) != NULL)
        {
          pCopasiWidget->update(objectType, action, key);
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

#ifdef COPASI_NONLIN_DYN
CQCrossSectionTaskWidget* ListViews::getCrossSectionWidget()
{
  return crossSectionTaskWidget;
}
#endif
