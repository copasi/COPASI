// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/listviews.cpp,v $
//   $Revision: 1.217 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/08/03 13:46:40 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 **  $ CopasiUI/listviews.cpp
 **  $ Author  : Ankur Gupta
 **  $ Author  : Mudita Singhal
 **  $ Author  : Mrinmayee Kulkarni
 **
 ** This file contains the defination of the routines declared in listviews.h header
 ** file.
 **
 ** This file is used to create the visual tree based on the information obtained from the data
 ** model about the tree
 **********************************************************************/
#include <qobjectlist.h>
#include <qimage.h>

#include "DataModelGUI.h"
#include "CompartmentsWidget.h"
#include "CompartmentsWidget1.h"
#include "FunctionSymbols.h"
#include "FunctionWidget.h"
#include "FunctionWidget1.h"
#ifdef HAVE_MML
# include "DifferentialEquations.h"
#endif // HAVE_MML
#include "CQLyapWidget.h"
#include "CQLyapResultWidget.h"
#include "MetabolitesWidget.h"
#include "CQMetabolite.h"
#include "ModelWidget.h"
#include "ModelValuesWidget.h"
#include "CQModelValue.h"
#include "CQEFMWidget.h"
#include "MoietyWidget.h"
#include "MoietyWidget1.h"
#ifdef COPASI_SSA
#include "SSAWidget.h"
#endif
#include "ParametersWidget.h"
#include "ReactionsWidget.h"
#include "ReactionsWidget1.h"
#include "SteadyStateWidget.h"
#include "StateWidget.h"
#include "ScanWidget.h"
#include "SensitivitiesWidget.h"
#include "CQSensResultWidget.h"
#include "CQOptimizationWidget.h"
#include "OptimizationResultWidget.h"
#include "TableDefinition.h"
#include "CQSplashWidget.h"
#include "CQTrajectoryWidget.h"
#include "TimeSeriesWidget.h"
#ifdef COPASI_DEBUG
#include "CQTSSAWidget.h"
#include "CQTSSAResultWidget.h"
#endif // COPASI_DEBUG
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
#include "PlotWidget.h"
#include "CQMathMatrixWidget.h"

#ifdef WITH_LAYOUT
#include "layoutUI/CQCopasiLayoutWidget.h"
#endif

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CReportDefinitionVector.h"
#include "plot/COutputDefinitionVector.h"
#include "plotUI/plotwidget1.h"
#include "model/CModel.h"

/**------FolderListItem::FolderListItem(QListView *parent, Folder *f)---->
 **
 ** Parameters:- 1. QListView* :- The parameter for the root of the tree
 **              2. Folder* :- The folder that needs to be created
 **
 ** Returns  :- This is constructor so it does not return any thing
 ** Descripton:- This is a 2 argument constructor with one argument for the base class
 **             This method creates a QListViewItem which the graphical display of the
 **             node of the tree with the name as specified in the name of the Folder
 **             and icon as per req..i.e whether its closed /locked..depending on
 **             whether the node has any childrens or not..
 *******************************************************************************************/
FolderListItem::FolderListItem(QListView *parent, const IndexedNode *f, bool recurs):
    QListViewItem(parent),
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
 ** Descripton:- This is a 2 argument constructor with one argument for the base class
 **             This method creates a QListViewItem which the graphical display of the
 **             node of the tree with the name as specified in the name of the Folder
 **             and icon as per req..i.e whether its closed /locked..depending on
 **             whether the node has any childrens or not..
 *******************************************************************************************/
FolderListItem::FolderListItem(FolderListItem *parent, const IndexedNode *f, bool recurs):
    QListViewItem(parent),
    mpFolder(f),
    mSortKey(f->getSortKey())
{
  setText(0, f->getName());

  if (recurs)
    createSubFolders();
}

/** **************FolderListItem::insertSubFolders(const QObjectList *lst)******
 **
 ** Parameters:- 1. QObjectList* :- The list of the object as my childrens
 **
 ** Returns  :- void
 ** Descripton:- This method is used to insert the sub folders of the folders. i.e. if the node
 **              has any childrens then this method is used to create those child nodes
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
  QListViewItem * tmp;
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
// Definations of the ListViews class as declared in listviews.h
/////////////////////////////////////////////////////////////////////////

/*********ListViews::ListViews(QWidget *parent, const char *name)************
 **
 ** Parameters:- 1. QWidget* :- The parameter needed by the base class i.e QSplitter
 **              2. char* :- The name parameter needed by the base class ie QSplitter
 ** Returns  :-  It does not return anything sice its 2 argument constructor
 ** Descripton:-  This is the constructor of the ListViews and is used to
 **               set up all the requirement and intialization of the
 **               components in the code.
 ************************************************************/
ListViews::ListViews(QWidget *parent, const char *name):
    QSplitter(Qt::Horizontal, parent, name),
    mpMathModel(NULL),
    mpCMCAResultWidget(NULL),
    mpCQMCAWidget(NULL),
    compartmentsWidget(NULL),
    compartmentsWidget1(NULL),
    defaultWidget(NULL),
    differentialEquations(NULL),
    functionSymbols(NULL),
    functionWidget(NULL),
    functionWidget1(NULL),
    lyapWidget(NULL),
    lyapResultWidget(NULL),
    metabolitesWidget(NULL),
    metabolitesWidget1(NULL),
    modelWidget(NULL),
    modelValuesWidget(NULL),
    mpModelValueWidget(NULL),
    modesWidget(NULL),
    moietyWidget(NULL),
    moietyWidget1(NULL),
    optimizationWidget(NULL),
    optResultWidgetS(NULL),
    optResultWidgetT(NULL),
    paramFittingWidget(NULL),
    mpFittingResultWidget(NULL),
    parametersWidget(NULL),
    plotWidget(NULL),
    plotWidget1(NULL),
    reactionsWidget(NULL),
    reactionsWidget1(NULL),
    scanWidget(NULL),
    sensWidget(NULL),
    sensResultWidget(NULL),
    stateWidget(NULL),
    steadystateWidget(NULL),
    tableDefinition(NULL),
    tableDefinition1(NULL),
#ifdef COPASI_TSS
    tssWidget(NULL),
#endif
    timeSeriesWidget(NULL),
    trajectoryWidget(NULL),
#ifdef COPASI_DEBUG
    tssaWidget(NULL),
    tssaResultWidget(NULL),
#endif
#ifdef COPASI_SSA
    mSSAWidget(NULL),
#endif
#ifdef WITH_LAYOUT
    mpCopasiLayoutWidget(NULL),
#endif
    mpMathMatrixWidget(NULL)
{
  this->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred, 1, 1));
  setChildrenCollapsible(false);

  // create a new QListview to be displayed on the screen..and set its property
  folders = new QListView(this);
  //folders->header()->setClickEnabled(false);
  folders->header()->hide();
  //folders->setRootIsDecorated(true);
  folders->addColumn("Select");
  //  folders->setMinimumWidth(160);

  defaultWidget = new CQSplashWidget(this);

  moveToFirst(folders);
  moveToLast(defaultWidget);
  setResizeMode(folders, QSplitter::KeepSize);
  if (!opaqueResize())
    setOpaqueResize();

  lastSelection = NULL;          // keeps track of the node that was selected last..to change the icon type
  currentWidget = defaultWidget; // keeps track of the currentWidget in use
  lastKey = "";

  // establishes the communication betweent the folders clicked and the routine called....
  connect(folders, SIGNAL(pressed(QListViewItem*)),
          this, SLOT(slotFolderChanged(QListViewItem*)));

  // Need to somehow signal folders to change when navigating using up and down arrows
  connect(folders, SIGNAL(returnPressed(QListViewItem*)),
          this, SLOT(slotFolderChanged(QListViewItem*)));

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
  //  if (!compartmentSymbols) compartmentSymbols = new CompartmentSymbols(this);
  //  compartmentSymbols->hide();

  if (!compartmentsWidget) compartmentsWidget = new CompartmentsWidget(this);
  compartmentsWidget->hide();

  if (!compartmentsWidget1) compartmentsWidget1 = new CompartmentsWidget1(this);
  compartmentsWidget1->hide();

  //  if (!constantSymbols) constantSymbols = new ConstantSymbols(this);
  //  constantSymbols->hide();

#ifdef HAVE_MML
  if (!differentialEquations) differentialEquations = new DifferentialEquations(this);
  differentialEquations->hide();
#endif // HAVE_MML

  //  if (!fixedMetaboliteSymbols) fixedMetaboliteSymbols = new FixedMetaboliteSymbols(this);
  //  fixedMetaboliteSymbols->hide();

  if (!functionSymbols) functionSymbols = new FunctionSymbols(this);
  functionSymbols->hide();

  if (!functionWidget) functionWidget = new FunctionWidget(this);
  functionWidget->hide();

  if (!functionWidget1) functionWidget1 = new FunctionWidget1(this);
  functionWidget1->hide();

  if (!lyapWidget) lyapWidget = new CQLyapWidget(this);
  lyapWidget->hide();

  if (!lyapResultWidget) lyapResultWidget = new CQLyapResultWidget(this);
  lyapResultWidget->hide();

  //  if (!metaboliteSymbols) metaboliteSymbols = new MetaboliteSymbols(this);
  //  metaboliteSymbols->hide();

  if (!metabolitesWidget) metabolitesWidget = new MetabolitesWidget(this);
  metabolitesWidget->hide();

  if (!metabolitesWidget1) metabolitesWidget1 = new CQMetabolite(this);
  metabolitesWidget1->hide();

  if (!modelWidget) modelWidget = new ModelWidget(this);
  modelWidget->hide();

  if (!mpModelValueWidget) mpModelValueWidget = new CQModelValue(this);
  mpModelValueWidget->hide();

  if (!modelValuesWidget) modelValuesWidget = new ModelValuesWidget(this);
  modelValuesWidget->hide();

  if (!modesWidget) modesWidget = new CQEFMWidget(this);
  modesWidget->hide();

  if (!moietyWidget) moietyWidget = new MoietyWidget(this);
  moietyWidget->hide();

  if (!moietyWidget1) moietyWidget1 = new MoietyWidget1(this);
  moietyWidget1->hide();

#ifdef COPASI_SSA
  if (!mSSAWidget) mSSAWidget = new SSAWidget(this);
  mSSAWidget->hide();
#endif // COPASI_SSA

  if (!parametersWidget) parametersWidget = new ParametersWidget(this);
  parametersWidget->hide();

  if (!mpCMCAResultWidget) mpCMCAResultWidget = new CMCAResultWidget(this);
  mpCMCAResultWidget->hide();

  if (!mpCQMCAWidget) mpCQMCAWidget = new CQMCAWidget(this);
  mpCQMCAWidget->hide();

  if (!optimizationWidget) optimizationWidget = new CQOptimizationWidget(this);
  optimizationWidget->hide();

  if (!optResultWidgetS) optResultWidgetS = new OptimizationResultWidget(this);
  optResultWidgetS->hide();

  if (!optResultWidgetT) optResultWidgetT = new OptimizationResultWidget(this, 0, 0, 1);
  optResultWidgetT->hide();

  if (!paramFittingWidget) paramFittingWidget = new CQFittingWidget(this);
  paramFittingWidget->hide();

  if (!mpFittingResultWidget) mpFittingResultWidget = new CQFittingResult(this);
  mpFittingResultWidget->hide();

  if (!plotWidget) plotWidget = new PlotWidget(this);
  plotWidget->hide();

  if (!plotWidget1) plotWidget1 = new PlotWidget1(this);
  plotWidget1->hide();

  if (!reactionsWidget) reactionsWidget = new ReactionsWidget(this);
  reactionsWidget->hide();

  if (!reactionsWidget1) reactionsWidget1 = new ReactionsWidget1(this);
  reactionsWidget1->hide();

  if (!scanWidget) scanWidget = new ScanWidget(this);
  scanWidget->hide();

  if (!stateWidget) stateWidget = new StateWidget(this);
  stateWidget->hide();

  if (!steadystateWidget) steadystateWidget = new SteadyStateWidget(this);
  steadystateWidget->hide();

  if (!tableDefinition) tableDefinition = new TableDefinition(this);
  tableDefinition->hide();

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

#ifdef COPASI_DEBUG
  if (!tssaWidget) tssaWidget = new CQTSSAWidget(this);
  tssaWidget->hide();

  if (!tssaResultWidget) tssaResultWidget = new CQTSSAResultWidget(this);
  tssaResultWidget->hide();
#endif

  if (!mpMathMatrixWidget) mpMathMatrixWidget = new CQMathMatrixWidget(this);
  mpMathMatrixWidget->hide();

#ifdef WITH_LAYOUT
  if (!mpCopasiLayoutWidget) mpCopasiLayoutWidget = new CQCopasiLayoutWidget(this);
  mpCopasiLayoutWidget->hide();
#endif
}

/**
 * tries to find the right hand side widget that belongs to an item of the tree view
 */
CopasiWidget* ListViews::findWidgetFromItem(FolderListItem* item) const
  {
    // first try ID
    C_INT32 id = item->getFolder()->getId();
    CopasiWidget * pWidget = findWidgetFromId(id);

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
      case 113:
        return moietyWidget1;
        break;
      case 114:
        return reactionsWidget1;
        break;
      case 115:
        return mpModelValueWidget;
        break;
      case 222:
        return moietyWidget1;
        break;
      case 43:
        return tableDefinition1;
        break;
      case 42:
        return plotWidget1;
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
        return compartmentsWidget;
        break;
      case 112:
        return metabolitesWidget;
        break;
      case 113:
        return moietyWidget;
        break;
      case 114:
        return reactionsWidget;
        break;
      case 115:
        return modelValuesWidget;
        break;
      case 116:
        return parametersWidget;
        break;
      case 122:
        return functionSymbols;
        break;
#ifdef HAVE_MML
      case 126:
        return differentialEquations;
        break;
#endif // HAVE_MML
      case 127:
        return mpMathMatrixWidget;
        break;
#ifdef WITH_LAYOUT
      case 131:
        return mpCopasiLayoutWidget;
        break;
#endif
      case 21:
        return steadystateWidget;
        break;
      case 211:
        return stateWidget;
        break;
      case 221:
        return modesWidget;
        break;
      case 222:
        return moietyWidget;
        break;
#ifdef COPASI_SSA
      case 223:
        return mSSAWidget;
        break;
#endif // COPASI_SSA
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
#ifdef COPASI_DEBUG
      case 27:
        return tssaWidget;
        break;
      case 271:
        return tssaResultWidget;
        break;
#endif
      case 31:
        return scanWidget;
        break;
      case 32:
        return optimizationWidget;
        break;
      case 321:
        if (optimizationWidget->isSteadyState())
          return optResultWidgetS;
        else
          return optResultWidgetT;
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
      case 43:                                        //Report
        return tableDefinition;
        break;
      case 42:
        return plotWidget;
        break;
      case 5:
        return functionWidget;
        break;
      }

    return NULL;
  }

FolderListItem* ListViews::findListViewItem(C_INT32 id, std::string key) //should always return a valid item
{
  FolderListItem * item;

  QListViewItemIterator it(folders);
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
  QListViewItemIterator it2(item->firstChild());
  QListViewItem * itemEnd = item->nextSibling();
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
void ListViews::slotFolderChanged(QListViewItem *i)
{
  bool changeWidget = true;
  if (!i) return;

  folders->setCurrentItem(i);
  folders->ensureItemVisible(i);

  // get the qlistview item in form of folderlistitem...
  FolderListItem *item = (FolderListItem*)i; //TODO dynamic cast?

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

// this reconstructs the childrens of the listViewItems in all listviews
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
  //std::cout << "ListViews::updateDataModelAndListviews " << std::endl;

  bool success = true;

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
              unsigned int numMetabolites = CCopasiDataModel::Global->getModel()->getMetabolites().size();
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
          // check if it was the last comaprtment, if yes,
          // make the compartment table the current widget
          if (dataModel)
            {
              unsigned int numCompartments = CCopasiDataModel::Global->getModel()->getCompartments().size();
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
              unsigned int numReactions = CCopasiDataModel::Global->getModel()->getReactions().size();
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
              unsigned int numValues = CCopasiDataModel::Global->getModel()->getNumModelValues();
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
              unsigned int numPlots = (CCopasiDataModel::Global->getPlotDefinitionList())->size();
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

      if (dataModel) CCopasiDataModel::Global->changed();

      break;

    case REPORT:
      switch (action)
        {
        case DELETE:

          if (dataModel)

            {
              unsigned int numReports = ((CCopasiDataModel::Global)->getReportDefinitionList())->size();
              if (numReports == 0)
                {
                  ListViews::switchAllListViewsToWidget(43, "");
                }
            }

          CCopasiDataModel::Global->changed();

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
          if (dataModel) CCopasiDataModel::Global->changed();
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

  dataModel->updateMoieties();
  updateAllListviews(222);

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

std::set<ListViews *> ListViews::mListOfListViews;
DataModelGUI* ListViews::dataModel;

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
  //std::cout << "notify: " << objectType << "  " << action << " " << key << std::endl;
  if (objectType != MODEL && action != ADD)
    CCopasiDataModel::Global->changed();

  bool success = true;

  //update the datamodel and the listviews trees
  if (!updateDataModelAndListviews(objectType, action, key)) success = false;

  //tell the listviews to notify the other widgets
  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator ende = mListOfListViews.end();
  for (; it != ende; ++it)
    if (! (*it)->updateCurrentWidget(objectType, action, key)) success = false;

  notifyAllChildWidgets(2, objectType, action, key); // Tasks
  notifyAllChildWidgets(3, objectType, action, key); // Multiple Tasks

  return success;
}

bool ListViews::updateCurrentWidget(ObjectType objectType, Action action, const std::string & key)
{
  bool success = true;

  if (currentWidget)
    currentWidget->update(objectType, action, key);

  return success;
}

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

void ListViews::notifyChildWidgets(FolderListItem * pItem,
                                   ObjectType objectType,
                                   Action action,
                                   const std::string & key)
{
  FolderListItem * pChild = static_cast<FolderListItem * >(pItem->firstChild());

  while (pChild)
    {
      notifyChildWidgets(pChild, objectType, action, key);

      CopasiWidget * pWidget = findWidgetFromItem(pChild);
      if (pWidget)
        pWidget->update(objectType, action, key);

      pChild = static_cast<FolderListItem * >(pChild->nextSibling());
    }
}

// static
void ListViews::notifyAllChildWidgets(C_INT32 id,
                                      ObjectType objectType,
                                      Action action,
                                      const std::string & key)
{
  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator ende = mListOfListViews.end();
  for (; it != ende; ++it)
    {
      FolderListItem * pItem = (*it)->findListViewItem(id, "");
      if (pItem)
        (*it)->notifyChildWidgets(pItem, objectType, action, key);
    }
}
