// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/listviews.cpp,v $
//   $Revision: 1.280 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/11/03 12:40:09 $
// End CVS Header

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

#include "DataModelGUI.h"
#include "CQMessageBox.h"

#include "CQCompartmentsWidget.h"
#include "CQCompartment.h"
#ifdef COPASI_DEBUG
#include "CQEventsWidget.h"
#include "CQEventWidget1.h"
#endif // COAPSI_DEBUG
#include "CQFunctionsWidget.h"
#include "FunctionWidget1.h"
#ifdef HAVE_MML
# include "CQDifferentialEquations.h"
#endif // HAVE_MML
#include "CQLyapWidget.h"
#include "CQLyapResultWidget.h"
#include "CQSpeciesWidget.h"
#include "CQSpeciesDetail.h"
#include "ModelWidget.h"
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
#include "StateWidget.h"
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

/**------FolderListItem::FolderListItem(QListView *parent, Folder *f)---->
 **
 ** Parameters:- 1. QListView* :- The parameter for the root of the tree
 **              2. Folder* :- The folder that needs to be created
 **
 ** Returns  :- This is constructor so it does not return any thing
 ** Description:This is a 2 argument constructor with one argument for the base class
 **             This method creates a QListViewItem which the graphical display of the
 **             node of the tree with the name as specified in the name of the Folder
 **             and icon as per req..i.e whether its closed /locked..depending on
 **             whether the node has any children or not..
 *******************************************************************************************/
FolderListItem::FolderListItem(Q3ListView *parent, const IndexedNode *f, bool recurs):
    Q3ListViewItem(parent),
    mpFolder(f),
    mSortKey(f->getSortKey())
{
  setText(0, f->getName());

  if (recurs)
    createSubFolders();
}

/**--------FolderListItem::FolderListItem(FolderListItem *parent, Folder *f)----->
 **
 ** Parameters:- 1. FolderListItem* :- The parameter for one of the node of the tree
 **              2. Folder* :- The folder that needs to be created
 **
 ** Returns  :- This is constructor so it does not return any thing
 ** Description:This is a 2 argument constructor with one argument for the base class
 **             This method creates a QListViewItem which the graphical display of the
 **             node of the tree with the name as specified in the name of the Folder
 **             and icon as per req..i.e whether its closed /locked..depending on
 **             whether the node has any children or not..
 *******************************************************************************************/
FolderListItem::FolderListItem(FolderListItem *parent, const IndexedNode *f, bool recurs):
    Q3ListViewItem(parent),
    mpFolder(f),
    mSortKey(f->getSortKey())
{
  setText(0, f->getName());

  if (recurs)
    createSubFolders();
}

/** **************FolderListItem::insertSubFolders(const QObjectList *lst)******
 **
 ** Parameters:- 1. QObjectList* :- The list of the object as my children
 **
 ** Returns  :- void
 ** Description: This method is used to insert the sub folders of the folders. i.e. if the node
 **              has any children then this method is used to create those child nodes
 *******************************************************************************************/
void FolderListItem::createSubFolders()
{
  const std::vector<IndexedNode*> & children = mpFolder->children();

  std::vector<IndexedNode*>::const_iterator it, itEnd = children.end();

  for (it = children.begin(); it != itEnd; ++it)
    {
      new FolderListItem(this, *it, true);
    }
}

void FolderListItem::deleteSubFolders()
{
  Q3ListViewItem * tmp;

  for (tmp = firstChild(); tmp; tmp = firstChild())
    {
      delete tmp;
    }
}

bool FolderListItem::setFolder(const IndexedNode * folder)
{
  mpFolder = folder;
  mSortKey = mpFolder->getSortKey();
  return true;
}

const IndexedNode * FolderListItem::getFolder() const
{return mpFolder;}

QString FolderListItem::key(int, bool) const
{
  /*    if (mpFolder)
        return mpFolder->getSortKey();
      else
        return "";*/
  return mSortKey;
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
ListViews::ListViews(QWidget *parent, const char *name):

    QSplitter(Qt::Horizontal, parent, name),
    mpMathModel(NULL),
    mpCMCAResultWidget(NULL),
    mpCQMCAWidget(NULL),
    mpCompartmentsWidget(NULL),
    compartmentsWidget1(NULL),
    defaultWidget(NULL),
    differentialEquations(NULL),
#ifdef COPASI_DEBUG
    eventsWidget(NULL),
    eventWidget1(NULL),
#endif // COPASI_DEBUG
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
#ifdef COPASI_DEBUG
    mpUpdatesWidget(NULL),
#endif
    mpLayoutsWidget(NULL),
    mpMathMatrixWidget(NULL)
{

  this->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred, 1, 1));
  setChildrenCollapsible(false);

  // create a new QListview to be displayed on the screen..and set its property
  folders = new Q3ListView(this);
  //folders->header()->setClickEnabled(false);
  folders->header()->hide();
  //folders->setRootIsDecorated(true);
  folders->addColumn("Select");
  //  folders->setMinimumWidth(160);

  defaultWidget = new CQSplashWidget(this);

  addWidget(folders);
  addWidget(defaultWidget);
  setResizeMode(folders, QSplitter::KeepSize);

  if (!opaqueResize())
    setOpaqueResize();

  lastSelection = NULL;          // keeps track of the node that was selected last..to change the icon type
  currentWidget = defaultWidget; // keeps track of the currentWidget in use
  lastKey = "";

  // establishes the communication between the folders clicked and the routine called....
  connect(folders, SIGNAL(pressed(Q3ListViewItem*)),
          this, SLOT(slotFolderChanged(Q3ListViewItem*)));

  // Need to somehow signal folders to change when navigating using up and down arrows
  connect(folders, SIGNAL(returnPressed(Q3ListViewItem*)),
          this, SLOT(slotFolderChanged(Q3ListViewItem*)));

  attach();
}

ListViews::~ListViews()
{
  detach(); //TODO clean up
}

/************************ListViews::setDataModel(DataModel<Folder>* dm)----------->
 **
 ** Parameters:- DataModel<Folder>* :- pointer to the data model to be used by all the
 **              views
 ** Returns  :-  void(Nothing)
 ** Description:-This method is used to set the datamodel to be used by the
 ** listview class to extract the data from the data-model
 ************************************************************************************/
void ListViews::setDataModel(DataModelGUI* dm)
{
  dataModel = dm;

  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator ende = mListOfListViews.end();

  for (; it != ende; ++it)
    {
      (*it)->setupFolders();
      (*it)->ConstructNodeWidgets();
    }
}

/**
 *  duplicates the dataModel tree structure
 */
void ListViews::setupFolders()
{
  // first clear up any thing that was present earlier
  folders->clear();

  FolderListItem* tmp = new FolderListItem(folders, dataModel->getRootNode(), true);
  tmp->setText(0, "Copasi");
  tmp->setOpen(true);
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

#ifdef COPASI_DEBUG

  if (!eventsWidget) eventsWidget = new CQEventsWidget(this);

  eventsWidget->hide();

  if (!eventWidget1) eventWidget1 = new CQEventWidget1(this);

  eventWidget1->hide();
#endif // COPASI_DEBUG

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
    modelWidget = new CTabWidget(QString("Model"), new ModelWidget(this), this);

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

  if (!stateWidget) stateWidget = new StateWidget(this);

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
CopasiWidget* ListViews::findWidgetFromItem(FolderListItem* item) const
{
  // first try ID
  C_INT32 id = item->getFolder()->getId();
  CopasiWidget* pWidget = findWidgetFromId(id);

  if (pWidget != NULL)
    return pWidget;

  // then try parent id:
  FolderListItem* parent = (FolderListItem*)item->parent();

  if (!parent) return NULL;

  id = parent->getFolder()->getId();

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
#ifdef COPASI_DEBUG
      case 116:
        return eventWidget1;
        break;
#endif // COPASI_DEBUG
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
#ifdef COPASI_DEBUG
      case 116:
        return eventsWidget;
        break;
#endif // COPASI_DEBUG
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

FolderListItem* ListViews::findListViewItem(C_INT32 id, std::string key) //should always return a valid item
{
  FolderListItem * item = NULL;

  Q3ListViewItemIterator it(folders);

  for (; *it; ++it)
    {
      item = (FolderListItem*) * it;

      if (item->getFolder()->getId() == id)
        break;
    }

  //try finding the key in the whole tree
  if (!(*it)) return findListViewItem(0, key);

  if (key == "") return item;

  if (key == item->getFolder()->getObjectKey()) return item; //found right key already

  //now look for the right key
  FolderListItem * item2;
  Q3ListViewItemIterator it2(item->firstChild());
  Q3ListViewItem * itemEnd = item->nextSibling();

  for (; *it2 && (*it2 != itemEnd); ++it2)
    {
      item2 = (FolderListItem*) * it2;

      if (item2->getFolder()->getObjectKey() == key)
        break;

      //if (item2 == itemEnd) //not found
      //  break;
    }

  if (*it2 && (*it2 != itemEnd)) return (FolderListItem*)*it2; //key was found

  return item; //id was found, but key was not found
}

/************************ListViews::slotFolderChanged(QListViewItem *i)----------->
 **
 ** Parameters:- QListViewItem* :- pointer to the node that was selected by the user
 **
 ** Returns  :-  void(Nothing)
 ** Description:-This method is called whenever the user clicks on one of the
 ** tree view items...
 *************************************************************************************/
void ListViews::slotFolderChanged(Q3ListViewItem *i)
{
  bool changeWidget = true;

  if (!i) return;

  folders->setCurrentItem(i);
  folders->ensureItemVisible(i);

  // get the listview item in form of folderlistitem...
  FolderListItem *item = static_cast< FolderListItem * >(i); //TODO dynamic cast?

  // find the widget
  CopasiWidget* newWidget = findWidgetFromItem(item);

  if (!newWidget) return; //do nothing

  std::string itemKey = item->getFolder()->getObjectKey();

  if (newWidget == currentWidget)
    if (itemKey == lastKey) return; //do nothing

  // leave old widget
  if (currentWidget)
    {
      changeWidget = currentWidget->leave();

      if (!changeWidget) return;

      //item may point to an invalid ListViewItem now
      item = (FolderListItem*)folders->currentItem();
    }

  // find the widget again (it may have changed)
  newWidget = findWidgetFromItem(item);

  if (!newWidget) newWidget = defaultWidget; //should never happen

  itemKey = item->getFolder()->getObjectKey();

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
  slotFolderChanged(findListViewItem(id, key));
}

//**********************************************************************

// this reconstructs the children of the listViewItems in all listviews
bool ListViews::updateAllListviews(C_INT32 id) //static
{
  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator ende = mListOfListViews.end();

  FolderListItem* item;

  for (; it != ende; ++it)
    {
      (*it)->folders->blockSignals(true);

      item = (*it)->findListViewItem(id, "");

      item->deleteSubFolders();
      item->setFolder(dataModel->getNode(id));

      item->createSubFolders();

      (*it)->folders->blockSignals(false);
    }

  return true;
}

//********** some methods to store and restore the state of the listview ****

void ListViews::storeCurrentItem()
{
  //save the id and object key of the current ListViewItem
  FolderListItem* item = (FolderListItem*)folders->currentItem();
  mSaveObjectKey = item->getFolder()->getObjectKey();
  mSaveFolderID = item->getFolder()->getId();

  while (mSaveFolderID == -1)
    {
      item = (FolderListItem*)item->parent();
      mSaveFolderID = item->getFolder()->getId();
    }
}

void ListViews::restoreCurrentItem()
{
  //reset the item from the saved values
  FolderListItem* item = (FolderListItem*)findListViewItem(mSaveFolderID, mSaveObjectKey);
  folders->setCurrentItem(item);
  folders->setSelected(item, true);
}

//static
void ListViews::storeCurrentItemInAllListViews()
{
  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator ende = mListOfListViews.end();

  for (; it != ende; ++it)
    {(*it)->storeCurrentItem();}
}

//static
void ListViews::restoreCurrentItemInAllListViews()
{
  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator ende = mListOfListViews.end();

  for (; it != ende; ++it)
    {(*it)->restoreCurrentItem();}
}

//*******************************************************************************

bool ListViews::updateDataModelAndListviews(ObjectType objectType,
    Action action, const std::string & C_UNUSED(key)) //static
{
  bool success = true;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  //maintain the "changed" flag
  switch (objectType)
    {
      case METABOLITE:

        switch (action)
          {
            case CHANGE:
              break;
            case RENAME:
              break;
            case ADD:
              break;
            case DELETE:

              // check if it was the last metabolite, if yes,
              // make the metabolite table the current widget
              if (dataModel)
                {
                  unsigned int numMetabolites = pDataModel->getModel()->getMetabolites().size();

                  if (numMetabolites == 0)
                    {
                      ListViews::switchAllListViewsToWidget(112, "");
                    }
                }

              break;
            default:
              break;
          }

        break;
      case COMPARTMENT:

        switch (action)
          {
            case CHANGE:
              break;
            case RENAME:
              break;
            case ADD:
              break;
            case DELETE:

              // check if it was the last compartment, if yes,
              // make the compartment table the current widget
              if (dataModel)
                {
                  unsigned int numCompartments = pDataModel->getModel()->getCompartments().size();

                  if (numCompartments == 0)
                    {
                      ListViews::switchAllListViewsToWidget(111, "");
                    }
                }

              break;
            default:
              break;
          }

        break;
      case REACTION:

        switch (action)
          {
            case CHANGE:
              break;
            case RENAME:
              break;
            case ADD:
              break;
            case DELETE:

              // check if it was the last reaction, if yes,
              // make the reaction table the current widget
              if (dataModel)
                {
                  unsigned int numReactions = pDataModel->getModel()->getReactions().size();

                  if (numReactions == 0)
                    {
                      ListViews::switchAllListViewsToWidget(114, "");
                    }
                }

              break;
            default:
              break;
          }

        break;

      case MODELVALUE:

        switch (action)
          {
            case CHANGE:
              break;
            case RENAME:
              break;
            case ADD:
              break;
            case DELETE:

              // check if it was the last value, if yes,
              // make the model value table the current widget
              if (dataModel)
                {
                  unsigned int numValues = pDataModel->getModel()->getNumModelValues();

                  if (numValues == 0)
                    {
                      ListViews::switchAllListViewsToWidget(115, "");
                    }
                }

              break;
            default:
              break;
          }

        break;
        //case FUNCTION:

      case PLOT:

        switch (action)
          {
            case DELETE:

              if (dataModel)
                {
                  unsigned int numPlots = (pDataModel->getPlotDefinitionList())->size();

                  if (numPlots == 0)
                    {
                      ListViews::switchAllListViewsToWidget(42, "");
                    }
                }

              break;
            case CHANGE:
            case ADD:
            case RENAME:
              break;
          }

        if (dataModel) pDataModel->changed();

        break;

      case REPORT:

        switch (action)
          {
            case DELETE:

              if (dataModel)

                {
                  unsigned int numReports = ((pDataModel)->getReportDefinitionList())->size();

                  if (numReports == 0)
                    {
                      ListViews::switchAllListViewsToWidget(43, "");
                    }
                }

              pDataModel->changed();

              break;
            default :
              ;
          }

        break;

      case MODEL:

        switch (action)
          {
            case CHANGE:
            case RENAME:

              if (dataModel) pDataModel->changed();

              break;
            case ADD:
            case DELETE:

              if (dataModel) setDataModel(dataModel);

              break;
            default:
              break;
          }

        break;

      default:
        break;
    }

  storeCurrentItemInAllListViews();

  //just do everything.  Later we can decide from parameters what really needs to be done
  dataModel->updateCompartments();
  updateAllListviews(111);

  dataModel->updateMetabolites();
  updateAllListviews(112);

  dataModel->updateReactions();
  updateAllListviews(114);

  dataModel->updateModelValues();
  updateAllListviews(115);

#ifdef COPASI_DEBUG
  dataModel->updateEvents();
  updateAllListviews(116);
#endif // COPASI_DEBUG

  dataModel->updateFunctions();
  updateAllListviews(5);

  //  FolderListItem* item=(*(mListOfListViews.begin()))->findListViewItem(5,"");
  //  item->firstChild();

  dataModel->updateReportDefinitions();
  updateAllListviews(43);

  dataModel->updatePlots();
  updateAllListviews(42);

  //item may point to an invalid ListViewItem now
  restoreCurrentItemInAllListViews();

  return success;
}

//**************************************************************************************+***

//static members **************************

// static
std::set<ListViews *> ListViews::mListOfListViews;

// static
DataModelGUI* ListViews::dataModel;

// static
std::set< const CCopasiObject * > ListViews::mChangedObjects;

// static
std::vector< Refresh * > ListViews::mUpdateVector;

// static
int ListViews::mFramework;

bool ListViews::attach()
{
  return mListOfListViews.insert(this).second;
}

bool ListViews::detach()
{
  return (mListOfListViews.erase(this) > 0);
}

bool ListViews::notify(ObjectType objectType, Action action, const std::string & key) //static
{
  if (objectType != MODEL && action != ADD)
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
      std::set<ListViews *>::iterator it = mListOfListViews.begin();
      std::set<ListViews *>::iterator ende = mListOfListViews.end();

      for (; it != ende; ++it)
        {
          (*it)->mpLayoutsWidget->deleteLayoutWindows();
        }
    }

  // update all initial value
  if (action != RENAME)
    refreshInitialValues();

  //update the datamodel and the listviews trees
  if (!updateDataModelAndListviews(objectType, action, key)) success = false;

  //tell the listviews to notify the other widgets
  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator ende = mListOfListViews.end();

  for (; it != ende; ++it)
    {
      if (!(*it)->updateCurrentWidget(objectType, action, key)) success = false;
    }

  notifyAllChildWidgets(objectType, action, key);

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

//static
bool ListViews::commit()
{
  bool success = true;
  CopasiWidget * tmp;
  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator ende = mListOfListViews.end();

  for (; it != ende; ++it)
    {
      tmp = (*it)->currentWidget;

      if (tmp && !tmp->leave()) success = false;
    }

  return success;
}

//static
void ListViews::switchAllListViewsToWidget(C_INT32 id, const std::string & key)
{
  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator ende = mListOfListViews.end();

  for (; it != ende; ++it)
    {(*it)->switchToOtherWidget(id, key);}
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

// static
void ListViews::notifyAllChildWidgets(ObjectType objectType,
                                      Action action,
                                      const std::string & key)
{
  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator end = mListOfListViews.end();

  for (; it != end; ++it)
    (*it)->notifyChildWidgets(objectType, action, key);
}

void ListViews::setChildWidgetsFramework(int framework)
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

// static
void ListViews::updateMIRIAMResourceContents()
{
  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator end = mListOfListViews.end();

  for (; it != end; ++it)
    (*it)->updateBiologicalDescriptionContents();
}

void ListViews::updateBiologicalDescriptionContents()
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

// static
void ListViews::setFramework(int framework)
{
  mFramework = framework;

  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator end = mListOfListViews.end();

  for (; it != end; ++it)
    (*it)->setChildWidgetsFramework(framework);
}

// static
void ListViews::buildChangedObjects()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
  pModel->compileIfNecessary(NULL);

  mChangedObjects.clear();

  CModelEntity ** ppEntity = pModel->getStateTemplate().getEntities();
  CModelEntity ** ppEntityEnd = pModel->getStateTemplate().endFixed();

  CMetab * pMetab;
  std::set< const CCopasiObject * > Objects;

  // The objects which are changed are all initial values of of all model entities including
  // fixed and unused once. Additionally, all kinetic parameters are possibly changed.
  // This is basically all the parameters in the parameter overview whose value is editable.

  // :TODO: Theoretically, it is possible that also task parameters influence the initial
  // state of a model but that is currently not handled.

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
      // If we have an initial expression we have no initial values
      if ((*ppEntity)->getInitialExpression() != "" ||
          (*ppEntity)->getStatus() == CModelEntity::ASSIGNMENT)
        continue;

      // Metabolites have two initial values
      if (mFramework == 0 &&
          (pMetab = dynamic_cast< CMetab * >(*ppEntity)) != NULL)
        {
          // The concentration is assumed to be fix accept when this would lead to circular dependencies,
          // for the parent's compartment's initial volume.
          if (pMetab->isInitialConcentrationChangeAllowed())
            mChangedObjects.insert(pMetab->getInitialConcentrationReference());
          else
            mChangedObjects.insert(pMetab->getInitialValueReference());
        }
      else
        mChangedObjects.insert((*ppEntity)->getInitialValueReference());
    }

  // The reaction parameters
  CCopasiVector< CReaction >::const_iterator itReaction = pModel->getReactions().begin();
  CCopasiVector< CReaction >::const_iterator endReaction = pModel->getReactions().end();
  unsigned C_INT32 i, imax;

  for (; itReaction != endReaction; ++itReaction)
    {
      const CCopasiParameterGroup & Group = (*itReaction)->getParameters();

      for (i = 0, imax = Group.size(); i < imax; i++)
        mChangedObjects.insert(Group.getParameter(i)->getObject(CCopasiObjectName("Reference=Value")));
    }

  // Fix for Issue 1170: We need to add elements of the stoichiometry, reduced stoichiometry,
  // and link matrices.
  const CArrayAnnotation * pMatrix = NULL;
  pMatrix = dynamic_cast<const CArrayAnnotation *>(pModel->getObject(std::string("Array=Stoichiometry(ann)")));

  if (pMatrix != NULL)
    pMatrix->appendElementReferences(mChangedObjects);

  pMatrix = dynamic_cast<const CArrayAnnotation *>(pModel->getObject(std::string("Array=Reduced stoichiometry(ann)")));

  if (pMatrix != NULL)
    pMatrix->appendElementReferences(mChangedObjects);

  pMatrix = dynamic_cast<const CArrayAnnotation *>(pModel->getObject(std::string("Array=Link matrix(ann)")));

  if (pMatrix != NULL)
    pMatrix->appendElementReferences(mChangedObjects);

  try
    {
      mUpdateVector = pModel->buildInitialRefreshSequence(mChangedObjects);
    }

  catch (...)
    {
      QString Message = "Error while updating the initial values!\n\n";
      Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

      CQMessageBox::critical(NULL, QString("COPASI Error"), Message,
                             QMessageBox::Ok, QMessageBox::Ok);
      CCopasiMessage::clearDeque();

      mUpdateVector.clear();
      return;
    }
}

// static
void ListViews::refreshInitialValues()
{
  buildChangedObjects();

  std::vector< Refresh * >::iterator it = mUpdateVector.begin();
  std::vector< Refresh * >::iterator end = mUpdateVector.end();

  for (; it != end; ++it)
    (**it)();
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
