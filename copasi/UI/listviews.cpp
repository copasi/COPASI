/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/listviews.cpp,v $
   $Revision: 1.142 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/07/02 13:47:47 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/listviews.cpp                 Modified on : 18th March, 2002
 **  $ Author  : Ankur Gupta
 **  $ Author  : Mudita Singhal
 **  $ Author  : Mrinmayee Kulkarni           Modified on : 17th Sept ,2002
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
#include "CompartmentSymbols.h"
#include "CompartmentsWidget.h"
#include "CompartmentsWidget1.h"
#include "ConstantSymbols.h"
#include "FixedMetaboliteSymbols.h"
#include "FunctionSymbols.h"
#include "FunctionWidget.h"
#include "FunctionWidget1.h"
#include "DifferentialEquations.h"
#include "MetaboliteSymbols.h"
#include "MetabolitesWidget.h"
#include "MetabolitesWidget1.h"
#include "ModelWidget.h"
#include "ModesWidget.h"
#include "MoietyWidget.h"
#include "MoietyWidget1.h"
#include "ReactionsWidget.h"
#include "ReactionsWidget1.h"
#include "SteadyStateWidget.h"
#include "ScanWidget.h"
#include "OptimizationWidget.h"
#include "TableDefinition.h"
#include "TableDefinition1.h"
#include "plot/plotwidget1.h"
#include "PlotWidget.h"
#include "CopasiDefaultWidget.h"
#include "plot/CPlotSpec.h"
#include "plot/CPlotSpecVector.h"
#include "report/CReportDefinition.h"
#include "report/CReportDefinitionVector.h"
#include "TrajectoryWidget.h"
#include "function/CFunctionDB.h"
#include "mathmodel/CMathModel.h"
#include "model/CModel.h"
#include "model/CMetabNameInterface.h"
#include "listviews.h"
#include "qtUtilities.h"
#include "utilities/CGlobals.h"

QPixmap *folderLocked = 0;   // to store the image of locked icon folder
QPixmap *folderClosed = 0;   // to store the image of closed icon folder
QPixmap *folderOpen = 0;     // to store the image of open icon folder

#include "./icons/folderclosed.xpm"
#include "./icons/folderopen.xpm"
#include "./icons/folderlocked.xpm"

//int Folder::mModifier = 0;

//////////////////////////////////////////////////////////////////////
// Definations of the FolderListItem  class declared in listviews.h
// -----------------------------------------------------------------

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
FolderListItem::FolderListItem(QListView *parent, Folder *f)
    : QListViewItem(parent)
{
  myFolder = f;
  setText(0, f->folderName());

  if (myFolder->children())
    {
      setPixmap(0, *folderClosed);
      insertSubFolders(myFolder->children());
    }
  else // if i am the last node than put my icon as locked...
    setPixmap(0, *folderLocked);
}

/*--------FolderListItem::FolderListItem(FolderListItem *parent, Folder *f)----->
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
FolderListItem::FolderListItem(FolderListItem *parent, Folder *f)
    : QListViewItem(parent)
{
  myFolder = f;
  setText(0, f->folderName());

  if (myFolder->children())
    {
      setPixmap(0, *folderClosed);
      insertSubFolders(myFolder->children());
    }
  else // if i am the last node than put my icon as locked...
    {
      parent->setPixmap(0, *folderClosed);
      setPixmap(0, *folderLocked);
    }
}

/***************FolderListItem::insertSubFolders(const QObjectList *lst)******
 **
 ** Parameters:- 1. QObjectList* :- The list of the object as my childrens
 **
 ** Returns  :- void
 ** Descripton:- This method is used to insert the sub folders of the folders. i.e. if the node
 **              has any childrens than this method is used to create those child nodes
 *******************************************************************************************/
void FolderListItem::insertSubFolders(const QObjectList *lst)
{
  if (!lst) return;

  Folder *f;

  for (f = (Folder*)((QObjectList*)lst)->first(); f; f = (Folder*)((QObjectList*)lst)->next())
    (void)new FolderListItem(this, f);
}

Folder * FolderListItem::folder() {return myFolder;}
QString FolderListItem::key(int, bool) const
  {return myFolder->getSortKey();}

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
    mpMathModel(NULL)
{
  setChildrenCollapsible(false);
  // creates the image to be displayed when folder is closed/locked/open
  folderLocked = new QPixmap((const char**)folderlocked);
  folderClosed = new QPixmap((const char**)folderclosed);
  folderOpen = new QPixmap((const char**)folderopen);

  // setting the parameter for the qptrlist...
  // lstFolders.setAutoDelete(false);

  // create a new QListview to be displayed on the screen..and set its property
  folders = new QListView(this);
  folders->header()->setClickEnabled(false);
  folders->setRootIsDecorated(true);
  folders->addColumn("Select");
  //  folders->setMinimumWidth(160);

  //  int c = folders->columnWidth(col_index);
  //  folders->setColumnWidth(col_index, c);
  // folders->setMaximumWidth(c);
  // folders->resize(180, 0);
  /*QSize *s = new QSize();
  *s = folders->baseSize();
  int w= s->width();
  int h = s->height(); */ 
  //s->setWidth(50);
  //folders->setMaximumSize(w,h);
  //folders->setFixedWidth(180);

  //  This sections intializes the components used in the display part

  //ConstructNodeWidgets();

  defaultWidget = new CopasiDefaultWidget(this);

  moveToFirst(folders);
  moveToLast(defaultWidget);
  setResizeMode(folders, QSplitter::KeepSize);
  if (!opaqueResize())
    setOpaqueResize();
  //  This section defines few of the variables that will be used in the code
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

  setupFolders();

  // create all the widgets
  ConstructNodeWidgets();

  //added by Liang Xu
  loadSteadyStateTaskNodes(dataModel->getSteadyStateTask());
  loadTrajectoryTaskNodes(dataModel->getTrajectoryTask());
}

/**
 * 
 */
void ListViews::setupFolders()
{
  // first clear up any thing that was present earlier
  folders->clear();

  // get the node from where u want to load the tree
  Node<Folder> *next = dataModel->getRoot();

  //skip root node
  if (next) next = next->child;

  if (next)
    for (; next != NULL; next = next->sibling)
      if (next->info->getID()) new FolderListItem(folders, next->info);

  //TODO: could that not be done by calling
}

/***********ListViews::ConstructNodeWidgets()---------------------------->
 **
 ** Parameters:- void(Nothing)
 ** Returns  :-  void(Nothing)
 ** Description:-This method is used to construct the node widgets to be
 **              displayed on the screen.....
 *************************************************************************/
void ListViews::ConstructNodeWidgets()
{
  // create the model widgets
  modelWidget = new ModelWidget(this);
  modelWidget->hide();

  compartmentsWidget = new CompartmentsWidget(this);
  compartmentsWidget->hide();

  metabolitesWidget = new MetabolitesWidget(this);
  metabolitesWidget->hide();

  reactionsWidget = new ReactionsWidget(this);
  reactionsWidget->hide();

  moietyWidget = new MoietyWidget(this);
  moietyWidget->hide();

  functionWidget = new FunctionWidget(this);
  functionWidget->hide();

  //*
  compartmentsWidget1 = new CompartmentsWidget1(this);
  compartmentsWidget1->hide();

  metabolitesWidget1 = new MetabolitesWidget1(this);
  metabolitesWidget1->hide();

  reactionsWidget1 = new ReactionsWidget1(this);
  reactionsWidget1->hide();

  moietyWidget1 = new MoietyWidget1(this);
  moietyWidget1->hide();

  functionWidget1 = new FunctionWidget1(this);
  functionWidget1->hide();

  //*
  metaboliteSymbols = new MetaboliteSymbols(this);
  metaboliteSymbols->hide();

  differentialEquations = new DifferentialEquations(this);
  differentialEquations->hide();

  fixedMetaboliteSymbols = new FixedMetaboliteSymbols(this);
  fixedMetaboliteSymbols->hide();

  compartmentSymbols = new CompartmentSymbols(this);
  compartmentSymbols->hide();

  constantSymbols = new ConstantSymbols(this);
  constantSymbols->hide();

  functionSymbols = new FunctionSymbols(this);
  functionSymbols->hide();

  //*
  tableDefinition = new TableDefinition(this);
  tableDefinition->hide();

  tableDefinition1 = new TableDefinition1(this);
  tableDefinition1->hide();

  plotWidget = new PlotWidget(this);
  plotWidget->hide();

  plotWidget1 = new PlotWidget1(this);
  plotWidget1->hide();

  steadystateWidget = new SteadyStateWidget(this);
  steadystateWidget->hide();

  scanWidget = new ScanWidget(this);
  scanWidget->hide();

  trajectoryWidget = new TrajectoryWidget(this);
  trajectoryWidget->hide();

  optimizationWidget = new OptimizationWidget(this);
  optimizationWidget->hide();

  modesWidget = new ModesWidget(this);
  modesWidget->hide();
}

/************************ListViews::addItem(QListViewItem* parent,Folder* child)------>
 **
 ** Parameters:- 1. QListViewItem* :- pointer to the parent node to which the new
 **                                    node would be added to.
 **    2. Folder* :- pointer to new node added to the tree
 **
 ** Returns  :-  Void(Nothing)
 ** Descripton:- This method is used to add new item to the parent list ie
 **              to add item to the any other level of the tree except the top level
 ****************************************************************************************/
void ListViews::addItem(QListViewItem* parent, Folder* child)
{
  FolderListItem *item = (FolderListItem*)parent;
  item->setPixmap(0, *folderClosed);
  (void)new FolderListItem(item, child);
}

void ListViews::addItem(Node<Folder>* child)
{
  if (child)
    {
      if (child->parent->info->getID() == 0)
        addItem(folders, child->info);
      else
        addItem(searchListViewItem(child->parent->info->getID()), child->info);
    }
}

/************************ListViews::addItem(QListView* parent,Folder* child)------>
 **
 ** Parameters:- 1. QListView* :- pointer to the parent node to which the new
 **                               node would be added to.(here it is the root node)
 **    2. Folder* :- pointer to new node added to the tree
 **
 ** Returns  :-  Void(Nothing)
 ** Description:- This method is used to add new item to the parent list ie
 **               to add item to the top level of the tree
 **********************************************************************************/
void ListViews::addItem(QListView* parent, Folder* child)
{
  (void)new FolderListItem(parent, child);
}

/************************ListViews::searchNode(QListViewItem* me)------------->
 **
 ** Parameters:- QListViewItem* :- pointer to node of the tree to be searched
 **
 ** Returns  :-   int :- 1-> if found; 0 if not found 
 ** Description:- This method is used to search a particular node in the 
 ** tree with input parameter as QListViewItem
 *****************************************************************************/
bool ListViews::existsListViewItem(QListViewItem* me)
{
  QListViewItemIterator it(folders);

  for (; it.current(); ++it)
    if (it.current() == me)
      return true;

  return false;
}

/************************ListViews::searchListViewItem(int id)---------->
 **
 ** Parameters:- int :- the id of the object to be searched
 **
 ** Returns  :-  QListViewItem* :- Pointer to the node searched for or null if nuthing is found 
 ** Description:-This method is used to search a particular node in the 
 **              tree with input parameter as id number
 ************************************************************/
QListViewItem* ListViews::searchListViewItem(int id)
{
  FolderListItem *item;
  QListViewItemIterator it(folders);

  for (; it.current(); ++it)
    {
      item = (FolderListItem*)it.current();

      if (item->folder()->getID() == id) //found...
        return it.current();
    }

  return NULL;
}

QListViewItem* ListViews::searchListViewItem(const std::string & key)
{
  FolderListItem *item;
  QListViewItemIterator it(folders);

  for (; it.current(); ++it)
    {
      item = (FolderListItem*)it.current();

      if (item->folder()->getObjectKey() == key) //found...
        return it.current();
    }

  return NULL;
}

/************************ListViews::searchListViewItem(const char* name)--------------------->
 **
 ** Parameters:- int :- the id of the object to be searched
 **
 ** Returns  :-  QListViewItem* :- Pointer to the node searched for or null if nuthing is found 
 ** Description:-This method is used to search a particular node in the 
 ** tree with input parameter as folder name
 ********************************************************************************/
QListViewItem* ListViews::searchListViewItem(const char* name)
{
  FolderListItem *item;
  QListViewItemIterator it(folders);

  for (; it.current(); ++it)
    {
      item = (FolderListItem*)it.current();
      int value = QString::compare(item->folder()->folderName(), name); // returns 0 for matching

      if (!value) //found...
        return it.current();
    }

  return NULL;
}

/************************ListViews::searchListViewItem(Folder* f)---------->
 **
 ** Parameters:- Folder* :- pointer to Folder to be searched
 **
 ** Returns  :-  QListViewItem* :- Pointer to the node searched for or null if nuthing is found
 ** Description:-this method is used to search a particular node in the
 **              tree with input parameter as folder ...
 ***************************************************************************************/
QListViewItem* ListViews::searchListViewItem(Folder* f)
{return searchListViewItem(f->getID());}

/**
 * tries to find the right hand side widget that belongs to an item of the tree view
 */
CopasiWidget* ListViews::findWidgetFromItem(FolderListItem* item) const
  {
    // first try ID
    C_INT32 id = item->folder()->getID();

    switch (id)
      {
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
      case 121:
        return compartmentSymbols;
        break;
      case 122:
        return functionSymbols;
        break;
      case 123:
        return constantSymbols;
        break;
      case 124:
        return fixedMetaboliteSymbols;
        break;
      case 125:
        return metaboliteSymbols;
        break;
      case 126:
        return differentialEquations;
        break;
      case 21:
        return steadystateWidget;
        break;
      case 221:
        return modesWidget;
        break;
      case 222:
        return moietyWidget;
        break;
      case 23:                                          //Time course
        return trajectoryWidget;
        break;
      case 31:
        return optimizationWidget;
        break;
      case 32:
        return scanWidget;
        break;
      case 43:                                         //Report
        return tableDefinition;
        break;
      case 42:                                         //Plots
        return plotWidget;
        break;
      case 5:
        return functionWidget;
        break;
      }

    // then try parent id:
    FolderListItem* parent = (FolderListItem*)item->parent();
    if (!parent) return NULL;
    id = parent->folder()->getID();

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
      case 222:
        return moietyWidget1;
        break;
      case 114:
        return reactionsWidget1;
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
    return defaultWidget;
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
  if (!i) return;

  //if (i->childCount() != 0)
  //  i->setPixmap(0, *folderOpen);

  // to change the status of the folder (closed/open)
  //if (lastSelection)
  //  if (lastSelection->childCount() == 0)
  //  {} // i was not expandable..than
  //  else
  //    lastSelection->setPixmap(0, *folderClosed);
  //lastSelection = i;

  // get the qlistview item in form of folderlistitem...
  FolderListItem *item = (FolderListItem*)i;

  //TODO: the fall back widget bifWidget should really be a CopasiWidget to avoid the typecasts that follow

  // find the widget

  CopasiWidget* newWidget;
  newWidget = findWidgetFromItem(item);
  std::string itemKey = item->folder()->getObjectKey();

  if (newWidget == currentWidget)
    if (itemKey == lastKey) return;

  // leave old widget
  if (currentWidget)
    {
      C_INT32 saveFolderID = item->folder()->getID();
      currentWidget->leave();
      item = (FolderListItem*)searchListViewItem(saveFolderID);
      if (item)
        folders->setCurrentItem(item);
      else
        {
          item = (FolderListItem*)searchListViewItem(itemKey);
          if (item)
            folders->setCurrentItem(item);
        }
    }

  // enter new widget
  if (newWidget)
    ((CopasiWidget*)newWidget)->enter(itemKey);

  // fall back
  if (!newWidget)
    {
      newWidget = defaultWidget;
      //bigWidget->setText("You Clicked On: " + item->folder()->folderName()); //TODO
    }

  if (currentWidget != newWidget)
    {
      if (currentWidget) currentWidget->hide();
      if (newWidget) newWidget->show();
    }

  currentWidget = newWidget;
  lastKey = itemKey;

  //Icon Synchronization implemented.
  //To show the folders Open or Close or locked -- By G
  QListViewItemIterator it(folders);
  for (; it.current(); ++it)
    {
      QPixmap *icon = (QPixmap *)it.current()->pixmap(0);
      QImage image1 = icon->convertToImage ();
      QImage image2 = folderOpen->convertToImage ();

      if (image1 == image2)
        it.current()->setPixmap(0, *folderClosed);
    }

  QPixmap *icon = (QPixmap *)item->pixmap(0);
  QImage image1 = icon->convertToImage ();
  QImage image2 = folderLocked->convertToImage ();

  if (image1 != image2)
    item->setPixmap(0, *folderOpen);
}

void ListViews::switchToOtherWidget(const std::string & key)
{
  slotFolderChanged(searchListViewItem(key));

  //TODO: update the active selection of the tree
}

/***********ListViews::clearParentItem(QListViewItem *i)--------------------->
 **
 ** Parameters:- 1. QListViewItem* :- The node whose items needs to be removed
 ** Returns  :-  void(Nothing)
 ** Description:-This method is used to delete the item from the tree
 ** this one is used for deleting the item if it one of the 
 ** top level items....
 *****************************************************************************/
void ListViews::clearParentItem(QListViewItem *i) // for the top level items to be cleared..
{
  QListViewItem * myParent = folders->firstChild();
  QListViewItem * nextChild = NULL;

  for (nextChild = myParent; myParent != NULL; myParent = myParent->nextSibling(), nextChild = myParent)
    if (nextChild == i)
      {
        FolderListItem * item = (FolderListItem*)i;
        Folder *f = item->folder();

        if (f->parent())
          f->parent()->removeChild(f);

        delete nextChild;

        break;
      }

  //i->setPixmap(0, *folderLocked);  // so i have no childrens now..
}

/***********ListViews::clearItem(QListViewItem * i)----------->
 **
 ** Parameters:- QListViewItem* :- The node whose items needs to be removed
 ** Returns  :-  void(Nothing)
 ** Description:-This method is used to delete the item from the tree
 ** this one is used for deleting the item 
 ************************************************************/
void ListViews::clearItem(QListViewItem * i)
{
  QListViewItem * myParent = i->parent();
  QListViewItem * nextChild, *parentStatus;
  parentStatus = myParent; // to keep track of the folder close/locked icon

  if (myParent != NULL)
    {
      myParent = myParent->firstChild();

      for (nextChild = myParent; myParent != NULL; myParent = myParent->nextSibling(), nextChild = myParent)
        if (nextChild == i)
          {
            FolderListItem * item = (FolderListItem*)nextChild;
            Folder *f = item->folder();

            if (f->parent())
              f->parent()->removeChild(f);

            delete nextChild;

            break;
          }

      //myParent->setPixmap(0, *folderLocked);  // so i have no childrens now..
      if (parentStatus->childCount() != 0)
        parentStatus->setPixmap(0, *folderClosed);
      else
        parentStatus->setPixmap(0, *folderLocked);
    }
}

void ListViews::deleteAllMyChildrens(QListViewItem* me)
{
  while (me->childCount())
    {
      delete (FolderListItem*) (me->firstChild());
    }
}

//**********************************************************************

void ListViews::setTheRightPixmap(QListViewItem* lvi)
{
  if (lvi->isSelected())
    if (lvi->childCount() != 0)
      lvi->setPixmap(0, *folderOpen);
}

// this deletes the children of the listviewitems referenced by id in all ListViews
bool ListViews::updateAllListviews1(C_INT32 id) //static
{
  bool success = true;

  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator ende = mListOfListViews.end();

  FolderListItem* item;

  for (; it != ende; ++it)
    {
      item = (FolderListItem*)(*it)->searchListViewItem(id);

      if (item) (*it)->deleteAllMyChildrens(item);
      else success = false;
    }

  return success;
}

// this reconstructs the childrens of the listViewItems in all listviews
bool ListViews::updateAllListviews2(C_INT32 id) //static
{
  bool success = true;

  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator ende = mListOfListViews.end();

  FolderListItem* item;

  for (; it != ende; ++it)
    {
      item = (FolderListItem*)(*it)->searchListViewItem(id);

      if (item) item->insertSubFolders(item->folder()->children());
      else success = false;
    }

  return success;
}

bool ListViews::updateDataModelAndListviews(ObjectType objectType,
    Action action, const std::string & C_UNUSED(key)) //static
{
  bool success = true;

  switch (objectType)
    {
    case METABOLITE:
    case COMPARTMENT:
    case REACTION:
    case FUNCTION:
    case REPORT:
    case PLOT:
      if (dataModel) dataModel->changed();
      break;

    case MODEL:
      switch (action)
        {
        case CHANGE:
        case RENAME:
          if (dataModel) dataModel->changed();
          break;
        case ADD:
        case DELETE:
        default:
          break;
        }
      break;

    default:
      break;
    }

  //just do everything. TODO: Later we can decide from parameters what really needs to be done

  updateAllListviews1(111);
  loadCompartmentsToDataModel();
  updateAllListviews2(111);

  updateAllListviews1(112);
  loadMetabolitesToDataModel();
  updateAllListviews2(112);

  updateAllListviews1(114);
  loadReactionsToDataModel();
  updateAllListviews2(114);

  //updateAllListviews1(113);
  updateAllListviews1(222);
  loadMoietiesToDataModel();
  //updateAllListviews2(113);
  updateAllListviews2(222);

  updateAllListviews1(5);
  loadFunctionsToDataModel();
  updateAllListviews2(5);

  updateAllListviews1(43);
  loadReportDefinition();
  updateAllListviews2(43);

  updateAllListviews1(42);
  loadPlotsToDataModel();
  updateAllListviews2(42);

  return success;
}

//**************************************************************************************+***

void ListViews::loadPlotsToDataModel()   //TODO
{
  Folder * parent = dataModel->searchFolderList(42);
  Folder * f;

  dataModel->removeAllChildren(parent);

  const CCopasiVector< CPlotSpec > * objects =
    dataModel->getPlotSpecVectorAddr();

  if (!objects) return;

  C_INT32 j, jmax = objects->size();

  CPlotSpec *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = (*objects)[j];
      f = new Folder(parent, FROM_UTF8(obj->getObjectName()));
      f->setID(parent->getID());
      f->setObjectKey(obj->getKey());
      dataModel->addData(parent, f);
    }
}

void ListViews::loadReportDefinition()
{
  Folder * parent = dataModel->searchFolderList(43);
  Folder * f;

  dataModel->removeAllChildren(parent);

  const CCopasiVector< CReportDefinition > * objects =
    dataModel->getReportDefinitionVectorAddr();

  if (!objects) return;

  C_INT32 j, jmax = objects->size();

  CReportDefinition *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = (*objects)[j];
      f = new Folder(parent, FROM_UTF8(obj->getObjectName()));
      f->setID(parent->getID());
      f->setObjectKey(obj->getKey());
      dataModel->addData(parent, f);
    }
}

void ListViews::loadCompartmentsToDataModel()
{
  Folder * parent = dataModel->searchFolderList(111);
  Folder * f;

  dataModel->removeAllChildren(parent);
  if (dataModel->getModel() == NULL) return;

  const CCopasiVectorN< CCompartment > & objects = dataModel->getModel()->getCompartments();
  C_INT32 j, jmax = objects.size();

  CCompartment *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      f = new Folder(parent, FROM_UTF8(obj->getObjectName()));
      f->setID(parent->getID());
      f->setObjectKey(obj->getKey());
      dataModel->addData(parent, f);
    }
}

void ListViews::loadMetabolitesToDataModel()
{
  Folder * parent = dataModel->searchFolderList(112); //Metabolites
  Folder * f;

  dataModel->removeAllChildren(parent);
  if (dataModel->getModel() == NULL) return;

  const CCopasiVector< CMetab > & metabolites = dataModel->getModel()->getMetabolites();
  C_INT32 noOfMetabolites = metabolites.size();

  CMetab *metab;
  C_INT32 j;
  for (j = 0; j < noOfMetabolites; j++)
    {
      metab = metabolites[j];

      //f = new Folder(parent, metab->getObjectName().);
      f = new Folder(parent, FROM_UTF8(CMetabNameInterface::getDisplayName(dataModel->getModel(), *metab)));
      f->setID(parent->getID());
      f->setObjectKey(metab->getKey());
      dataModel->addData(parent, f);
    }
}

void ListViews::loadReactionsToDataModel()
{
  Folder * parent = dataModel->searchFolderList(114); //Reactions
  Folder * f;

  dataModel->removeAllChildren(parent);
  if (dataModel->getModel() == NULL) return;

  const CCopasiVectorN< CReaction > & objects = dataModel->getModel()->getReactions();
  C_INT32 j, jmax = objects.size();

  CReaction *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      f = new Folder(parent, FROM_UTF8(obj->getObjectName()));
      f->setID(parent->getID());
      f->setObjectKey(obj->getKey());
      dataModel->addData(parent, f); // TODO: do we really want to add this to the datamodel here?
    }
}

void ListViews::loadMoietiesToDataModel()
{
  //Folder * parent = dataModel->searchFolderList(113); //Moiety
  Folder * parent = dataModel->searchFolderList(222); //Moiety
  Folder * f;

  dataModel->removeAllChildren(parent);
  if (dataModel->getModel() == NULL) return;

  const CCopasiVectorN< CMoiety > & objects = dataModel->getModel()->getMoieties();
  C_INT32 j, jmax = objects.size();

  CMoiety *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      f = new Folder(parent, FROM_UTF8(obj->getObjectName()));
      f->setID(parent->getID());
      f->setObjectKey(obj->getKey()); //TODO: give moieties a key
      dataModel->addData(parent, f);
    }
}

void ListViews::loadFunctionsToDataModel()
{
  Folder * parent = dataModel->searchFolderList(5); //Functions
  Folder * f;

  dataModel->removeAllChildren(parent);

  const CCopasiVectorN< CFunction > & objects = Copasi->pFunctionDB->loadedFunctions();
  C_INT32 j, jmax = objects.size();

  CFunction *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      f = new Folder(parent, FROM_UTF8(obj->getObjectName()));
      f->setID(parent->getID());
      f->setObjectKey(obj->getKey());
      dataModel->addData(parent, f);
    }
}

/***********ListViews::showMessage(QString caption,QString text)------------------------>
 **
 ** Parameters:- 1. QString :- The Title that needs to be displayed in message box
 **              2. QString :_ The Text that needs to be displayed in the message box
 ** Returns  :-  void(Nothing)
 ** Description:- This method is used to show the message box on the screen
 ****************************************************************************************/

/*void ListViews::showMessage(QString title, QString text)
{
  QMessageBox::about (this, title, text);
}*/

void ListViews::loadSteadyStateTaskNodes(CSteadyStateTask* steadystatetask)
{
  if (steadystatetask != NULL)
    {
      QListViewItem* loadNode; // to load the tree with that stuff

      // UPDATE THE METABOLITES STUFF..
      steadystateWidget->loadSteadyStateTask();
      loadNode = searchListViewItem("Steady-State");

      if (loadNode)
        {
          if (loadNode->isSelected())
            {
              currentWidget->hide();
              steadystateWidget->show();
              currentWidget = steadystateWidget;
            }
          loadNode = NULL;
        }
      //dataModel->setSteadyStateTaskUpdate(false);
    }
}

void ListViews::loadTrajectoryTaskNodes(CTrajectoryTask* trajectorytask)
{
  if (trajectorytask != NULL)
    {
      QListViewItem* loadNode; // to load the tree with that stuff

      // UPDATE THE METABOLITES STUFF..
      //trajectoryWidget->loadTrajectoryTask();
      loadNode = searchListViewItem("Trajectory");

      if (loadNode)
        {
          if (loadNode->isSelected())
            {
              currentWidget->hide();
              trajectoryWidget->show();
              currentWidget = trajectoryWidget;
            }
          loadNode = NULL;
        }
      //dataModel->setTrajectoryTaskUpdate(false);
    }
}

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
  std::set<ListViews *>::iterator it = mListOfListViews.begin();
  std::set<ListViews *>::iterator ende = mListOfListViews.end();

  std::cout << "notify: " << objectType << "  " << action << " " << key << std::endl;

  bool success = true;

  //update the datamodel and the listviews tree
  if (!updateDataModelAndListviews(objectType, action, key)) success = false;

  //tell the listviews to notify the other widgets
  for (; it != ende; ++it)
    if (! (*it)->update(objectType, action, key)) success = false;

  return success;
}

bool ListViews::update(ObjectType objectType, Action action, const std::string & key)
{
  bool success = true;

  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
    case ListViews::REACTION:
      dataModel->scheduleMathModelUpdate();
      break;
    default:;
    }

  if (currentWidget)
    currentWidget->update(objectType, action, key);

  //TODO: the following is special code to be executed when
  //a model is created or loaded or imported.
  //it needs to be reintroduced (?)
  /*
      if (action == ADD)
        {
          folders->clearSelection();
          folders->setSelected(searchListViewItem(1), true);
          slotFolderChanged(searchListViewItem(1));
        }
  */
  return success;
}

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

void ListViews::slotHideWidget()
{
  currentWidget->hide();
}

void ListViews::slotShowWidget()
{
  currentWidget->show();
}
