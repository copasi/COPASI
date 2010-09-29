// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/listviews.cpp,v $
//   $Revision: 1.290.2.7 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/09/29 19:28:46 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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

#include "DataModelGUI.h"
#include "CQMessageBox.h"

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
#include "CQModelWidget.h"
#include "CQGlobalQuantitiesWidget.h"
#include "CQModelValue.h"
#include "CQEFMWidget.h"
#include "CQEFMResultWidget.h"
#include "CQMoietiesTaskResult.h"
#include "CQMoietiesTaskWidget.h"
#include "ParametersWidget.h"
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
#include "TimeSeriesWidget.h"
#include "CQTSSAWidget.h"
#include "CQTSSAResultWidget.h"
#ifdef COPASI_DEBUG
#include "CQUpdatesWidget.h"
#endif //COPASI_DEBUG
#ifdef COPASI_TSS
# include "TSSWidget.h"
#endif
#include "listviews.h"
#include "qtUtilities.h"
#include "CQFittingWidget.h"
#include "CQFittingResult.h"
#include "CQMCAWidget.h"
#include "CMCAResultWidget.h"
#include "CQReportDefinition.h"
#include "CQPlotsWidget.h"
#include "CQMathMatrixWidget.h"
#include "MIRIAMUI/CQMiriamWidget.h"

#include "CTabWidget.h"

#include "UI/CQLayoutsWidget.h"

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "report/CReportDefinitionVector.h"
#include "plot/COutputDefinitionVector.h"
#include "plotUI/PlotSubwidget.h"
#include "model/CModel.h"

#ifdef COPASI_NONLIN_DYN
#include "CQCrossSectionTaskWidget.h"
#endif

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
    mpMathModel(NULL),
    currentWidget(NULL),
    lastKey(),
    mSaveObjectKey(),
    mSaveFolderID(C_INVALID_INDEX),
    mpCMCAResultWidget(NULL),
    mpCQMCAWidget(NULL),
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
    parametersWidget(NULL),
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
#ifdef COPASI_TSS
    tssWidget(NULL),
#endif
    timeSeriesWidget(NULL),
    trajectoryWidget(NULL),
    tssaWidget(NULL),
    tssaResultWidget(NULL),
#ifdef COPASI_NONLIN_DYN
    crossSectionTaskWidget(NULL),
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
  mpTreeView = new QTreeView(this);
  mpTreeView->header()->hide();
  mpTreeView->setRootIsDecorated(false);

  defaultWidget = new CQSplashWidget(this);

  addWidget(mpTreeView);
  addWidget(defaultWidget);
  setResizeMode(mpTreeView, QSplitter::KeepSize);

  if (!opaqueResize())
    setOpaqueResize();

  currentWidget = defaultWidget; // keeps track of the currentWidget in use
  lastKey = "";

  mSaveObjectKey = "";
  mSaveFolderID = -1;

  // establishes the communication between the mpTreeView clicked and the routine called....
  connect(mpTreeView, SIGNAL(pressed(const QModelIndex &)),
          this, SLOT(slotFolderChanged(const QModelIndex &)));

  // Need to somehow signal mpTreeView to change when navigating using up and down arrows
  connect(mpTreeView, SIGNAL(activated(const QModelIndex &)),
          this, SLOT(slotFolderChanged(const QModelIndex &)));

}

ListViews::~ListViews()
{
  //TODO clean up
}

void ListViews::slotUpdateCompleteView()
{
  restoreCurrentItem();
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
  if (mpDataModelGUI != NULL)
    {
      disconnect(mpDataModelGUI, SIGNAL(updateCompleteView()), this, SLOT(slotUpdateCompleteView()));
      disconnect(mpDataModelGUI, SIGNAL(notifyView(ListViews::ObjectType, ListViews::Action, const std::string&)),
                 this, SLOT(slotNotify(ListViews::ObjectType, ListViews::Action, const std::string&)));
    }

  mpDataModelGUI = pDM;

  //update the tree nodes with single widgets.
  mpDataModelGUI->updateAllEntities();

  mpTreeView->setModel(NULL);
  mpTreeView->setModel(mpDataModelGUI);
  mpTreeView->expand(mpDataModelGUI->findIndexFromId(0));

  ConstructNodeWidgets();

  //Now Connect updateCompleteView() and notifyView() from DataModelGUI
  if (mpDataModelGUI != NULL)
    {
      connect(mpDataModelGUI, SIGNAL(updateCompleteView()), this, SLOT(slotUpdateCompleteView()));
      connect(mpDataModelGUI, SIGNAL(notifyView(ListViews::ObjectType, ListViews::Action, const std::string&)),
              this, SLOT(slotNotify(ListViews::ObjectType, ListViews::Action, const std::string&)));
    }
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
    compartmentsWidget1 = new CTabWidget(QString("Compartment"), new CQCompartment(this), this);

  compartmentsWidget1->hide();

#ifdef HAVE_MML

  if (!differentialEquations) differentialEquations = new CQDifferentialEquations(this);

  differentialEquations->hide();
#endif // HAVE_MML

  if (!eventsWidget) eventsWidget = new CQEventsWidget(this);

  eventsWidget->hide();

  if (!eventWidget1) eventWidget1 = new CTabWidget(QString("Event"), new CQEventWidget1(this), this);

  eventWidget1->hide();

  if (!mpFunctionsWidget) mpFunctionsWidget = new CQFunctionsWidget(this);

  mpFunctionsWidget->hide();

  if (!functionWidget1)
    functionWidget1 = new CTabWidget(QString("Function"), new FunctionWidget1(this), this);

  functionWidget1->hide();

  if (!lyapWidget) lyapWidget = new CQLyapWidget(this);

  lyapWidget->hide();

  if (!lyapResultWidget) lyapResultWidget = new CQLyapResultWidget(this);

  lyapResultWidget->hide();

  if (!mpSpeciesWidget) mpSpeciesWidget = new CQSpeciesWidget(this);

  mpSpeciesWidget->hide();

  if (!metabolitesWidget1)
    metabolitesWidget1 = new CTabWidget(QString("Species"), new CQSpeciesDetail(this), this);

  metabolitesWidget1->hide();

  if (!modelWidget)
    modelWidget = new CTabWidget(QString("Model"), new CQModelWidget(this), this);

  modelWidget->hide();

  if (!mpModelValueWidget)
    mpModelValueWidget = new CTabWidget(QString("ModelValue"), new CQModelValue(this), this);

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

  if (!parametersWidget) parametersWidget = new ParametersWidget(this);

  parametersWidget->hide();

  if (!mpCMCAResultWidget) mpCMCAResultWidget = new CMCAResultWidget(this);

  mpCMCAResultWidget->hide();

  if (!mpCQMCAWidget) mpCQMCAWidget = new CQMCAWidget(this);

  mpCQMCAWidget->hide();

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

  if (!mpPlotSubwidget) mpPlotSubwidget = new PlotSubwidget(this);

  mpPlotSubwidget->hide();

  if (!mpReactionsWidget) mpReactionsWidget = new CQReactionsWidget(this);

  mpReactionsWidget->hide();

  if (!reactionsWidget1)
    reactionsWidget1 = new CTabWidget(QString("Reaction"), new ReactionsWidget1(this), this);

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

#ifdef COPASI_TSS

  if (!tssWidget) tssWidget = new TSSWidget(this);

  tssWidget->hide();
#endif

  if (!sensWidget) sensWidget = new SensitivitiesWidget(this);

  sensWidget->hide();

  if (!sensResultWidget) sensResultWidget = new CQSensResultWidget(this);

  sensResultWidget->hide();

  if (!timeSeriesWidget) timeSeriesWidget = new TimeSeriesWidget(this);

  timeSeriesWidget->hide();

  if (!trajectoryWidget) trajectoryWidget = new CQTrajectoryWidget(this);

  trajectoryWidget->hide();

  if (!tssaWidget) tssaWidget = new CQTSSAWidget(this);

  tssaWidget->hide();

  if (!tssaResultWidget) tssaResultWidget = new CQTSSAResultWidget(this);

  tssaResultWidget->hide();

#ifdef COPASI_NONLIN_DYN

  if (!crossSectionTaskWidget) crossSectionTaskWidget = new CQCrossSectionTaskWidget(this);

  crossSectionTaskWidget->hide();
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
  C_INT32 id = mpDataModelGUI->getId(index);
  CopasiWidget* pWidget = findWidgetFromId(id);

  if (pWidget != NULL)
    return pWidget;

  // then try parent id:
  QModelIndex parentIndex = mpDataModelGUI->parent(index);

  if (!parentIndex.isValid()) return NULL;

  id = mpDataModelGUI->getId(parentIndex);

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

CopasiWidget* ListViews::findWidgetFromId(const C_INT32 & id) const
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
      case 117:
        return parametersWidget;
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
#ifdef COPASI_TSS
      case 25:
        return tssWidget;
        break;
#endif
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

  mpTreeView->setCurrentIndex(index);

  // find the widget
  CopasiWidget* newWidget = findWidgetFromIndex(index);

  if (!newWidget) return; //do nothing

  std::string itemKey = mpDataModelGUI->getKey(index);

  if (newWidget == currentWidget)
    if (itemKey == lastKey) return; //do nothing

  // leave old widget
  if (currentWidget)
    {
      changeWidget = currentWidget->leave();

      if (!changeWidget) return;

      //item may point to an invalid ListViewItem now
      QModelIndex newIndex = mpTreeView->currentIndex();

      // find the widget again (it may have changed)
      newWidget = findWidgetFromIndex(newIndex);
    }

  if (!newWidget) newWidget = defaultWidget; //should never happen

  // enter new widget
  if (newWidget)
    ((CopasiWidget*)newWidget)->enter(itemKey);

  // fall back
  if (!newWidget)
    {newWidget = defaultWidget;}

  if (currentWidget != newWidget)
    {
      if (currentWidget) currentWidget->hide();

      if (newWidget) newWidget->show();
    }

  currentWidget = newWidget;
  lastKey = itemKey;
}

void ListViews::switchToOtherWidget(C_INT32 id, const std::string & key)
{
  if (!mpDataModelGUI) return;

  QModelIndex index;

  if (key == "")
    index = mpDataModelGUI->findIndexFromId(id);
  else
    index = mpDataModelGUI->findIndexFromKey(key);

  slotFolderChanged(index);
}

//********** some methods to store and restore the state of the listview ****

void ListViews::storeCurrentItem()
{
  //save the id and object key of the current ListViewItem
  QModelIndex index = mpTreeView->currentIndex();

  if (!index.isValid() || !mpDataModelGUI)
    return;

  mSaveObjectKey = mpDataModelGUI->getKey(index);
  mSaveFolderID = mpDataModelGUI->getId(index);

  while (mSaveObjectKey == "" && mSaveFolderID == C_INVALID_INDEX)
    {
      index = mpDataModelGUI->parent(index);
      mSaveObjectKey = mpDataModelGUI->getKey(index);
      mSaveFolderID = mpDataModelGUI->getId(index);
    }
}

void ListViews::restoreCurrentItem()
{
  //reset the item from the saved values
  if (!mpDataModelGUI) return;

  if (mSaveObjectKey == "" && mSaveFolderID == C_INVALID_INDEX) return;

  QModelIndex index;

  //First try restoring with the key.
  if (mSaveObjectKey.length() > 0)
    index = mpDataModelGUI->findIndexFromKey(mSaveObjectKey);

  //if not successful then try the ID.
  if (!index.isValid())
    index = mpDataModelGUI->findIndexFromId(mSaveFolderID);

  if (index.isValid())
    {
      //Build Map with expanded values of all nodes without children.
      QMap<int, bool> isExpandedMap;
      buildExpandedMap(isExpandedMap, mpDataModelGUI->getNode(0));

      //Refresh View
      mpTreeView->setModel(NULL);
      mpTreeView->setModel(mpDataModelGUI);

      //Set Nodes to original expanded value
      QMap<int, bool>::iterator it, itEnd = isExpandedMap.end();

      for (it = isExpandedMap.begin(); it != itEnd; ++it)
        {
          QModelIndex i = mpDataModelGUI->findIndexFromId(it.key());
          mpTreeView->setExpanded(i, it.value());
        }

      mpTreeView->setCurrentIndex(index);
      slotFolderChanged(index);
    }
}

void ListViews::buildExpandedMap(QMap<int, bool> &isExpandedMap, const IndexedNode *startNode)
{
  if (startNode->childCount() == 0 || startNode->getId() == C_INVALID_INDEX)
    return;

  QModelIndex index = mpDataModelGUI->findIndexFromId(startNode->getId());

  if (index.isValid() && mpTreeView->isExpanded(index))
    isExpandedMap[startNode->getId()] = mpTreeView->isExpanded(index);

  const std::vector<IndexedNode*> & children = startNode->children();
  std::vector<IndexedNode*>::const_iterator it, itEnd = children.end();

  for (it = children.begin(); it != itEnd; ++it)
    {
      buildExpandedMap(isExpandedMap, *it);
    }
}

int ListViews::getCurrentItemId()
{
  QModelIndex index = mpTreeView->currentIndex();

  if (!index.isValid() || !mpDataModelGUI)
    return -1;

  return mpDataModelGUI->getId(index);
}

//**************************************************************************************+***

//static members **************************

bool ListViews::slotNotify(ObjectType objectType, Action action, const std::string & key)
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

bool ListViews::updateCurrentWidget(ObjectType objectType, Action action, const std::string & key)
{
  bool success = true;

  if (currentWidget)
    currentWidget->update(objectType, action, key);

  return success;
}

CopasiWidget* ListViews::getCurrentWidget()
{return this->currentWidget;}

void ListViews::commit()
{
  if (currentWidget != NULL)
    currentWidget->leave();
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

