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
#include "ModesWidget.h"
#include "MoietyWidget.h"
#include "MoietyWidget1.h"
#include "ReactionsWidget.h"
#include "ReactionsWidget1.h"
#include "SteadyStateWidget.h"
#include "TrajectoryWidget.h"
#include "function/CFunctionDB.h"
#include "mathmodel/CMathModel.h"
#include "listviews.h"

QPixmap *folderLocked = 0;   // to store the image of locked icon folder
QPixmap *folderClosed = 0;   // to store the image of closed icon folder
QPixmap *folderOpen = 0;     // to store the image of open icon folder

#include "./icons/folderclosed.xpm"
#include "./icons/folderopen.xpm"
#include "./icons/folderlocked.xpm"

int Folder::mModifier = 0;

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
    setPixmap(0, *folderLocked);
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
  Folder *f;

  for (f = (Folder*)((QObjectList*)lst)->first(); f; f = (Folder*)((QObjectList*)lst)->next())
    (void)new FolderListItem(this, f);
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
    mpMathModel(NULL)
{
  // creates the image to be displayed when folder is closed/locked/open
  folderLocked = new QPixmap((const char**)folderlocked);
  folderClosed = new QPixmap((const char**)folderclosed);
  folderOpen = new QPixmap((const char**)folderopen);

  // setting the parameter for the qptrlist...
  lstFolders.setAutoDelete(false);

  //  create a new QListview to be displayed on the screen..and set its property
  folders = new QListView(this);
  folders->header()->setClickEnabled(false);
  int col_index = folders->addColumn("Select ");
  int c = folders->columnWidth(col_index);
  folders->setColumnWidth(col_index, c);
  folders->setRootIsDecorated(true);
  //folders->setMaximumWidth(c);
  //folders->resize(50,0);
  /*QSize *s = new QSize();
  *s = folders->baseSize();
  int w= s->width();
  int h = s->height(); */ 
  //this->setResizeMode(folders, QSplitter::KeepSize);
  //s->setWidth(50);
  //folders->setMaximumSize(w,h);
  folders->setFixedWidth(180);

  //  This sections intializes the components used in the display part
  bigWidget = new QMultiLineEdit(this);
  bigWidget->setText("This widget will get all the remaining space");
  bigWidget->setFrameStyle(QFrame::Panel | QFrame::Plain);
  bigWidget->setReadOnly(false);
  QSize *s = new QSize();
  *s = bigWidget->size();
  //  int w = s->width();
  //  int h = s->height();
  //bigWidget->setFixedWidth(620);
  this->moveToFirst(folders);
  this->moveToLast(bigWidget);
  //  This section defines few of the variables that will be used in the code
  lastSelection = NULL;          // keeps track of the node that was selected last..to change the icon type
  currentWidget = bigWidget; // keeps track of the currentWidget in use
  lastWidget = bigWidget; // keeps track of the lastWidget that was used
  mModel = NULL;             // keeps track of the model that is used..
  mSteadyStateTask = NULL;
  mTrajectoryTask = NULL;

  // establishes the communication betweent the folders clicked and the routine called....
  connect(folders, SIGNAL(pressed(QListViewItem*)),
          this, SLOT(slotFolderChanged(QListViewItem*)));
}

/****************************ListViews::initFolders()**************************
 ** Parameters:- Void(Nothing)
 ** Returns  :-  Void(Nothing)
 ** Descripton:- This method is used to load the information from the 
 **              tree structure in the vector stuff to be used later
 **              by the setupfolders to create the visual display 
 ************************************************************/
void ListViews::initFolders()
{
  // first clear up any thing that was present earlier
  this->lstFolders.clear();

  // get the node from where u want to load the tree
  Node<Folder> *next = dataModel->getRoot();

  //  dataModel->g

  //this is needed because when the tree is created the root is not needed in this
  // visual display
  // than append all the information in the vector to be used later by setup folder

  if (next)
    for (next = next->child; next != NULL; next = next->sibling)
      if (next->info->getID()) lstFolders.append(next->info);
}

/************************ListViews::setupFolders()*****************************
 ** Parameters:- Void(Nothing)
 ** Returns  :-  Void(Nothing)
 ** Descripton:- This method is used to create the visual display of the 
 **              objects on the screen 
 ************************************************************/
void ListViews::setupFolders()
{
  folders->clear();
  Folder* f;
  for (f = lstFolders.first(); f; f = lstFolders.next())
    (void)new FolderListItem(folders, f);
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

/************************ListViews::searchNode(Folder* f)---------->
 **
 ** Parameters:- Folder* :- pointer to Folder to be searched
 **
 ** Returns  :-  QListViewItem* :- Pointer to the node searched for or null if nuthing is found 
 ** Description:-this method is used to search a particular node in the 
 **              tree with input parameter as folder ...
 ***************************************************************************************/
QListViewItem* ListViews::searchNode(Folder* f)
{
  FolderListItem *item;
  QListViewItemIterator it(folders);

  for (; it.current(); ++it)
    {
      item = (FolderListItem*)it.current();

      if (item->folder()->getID() == f->getID()) //found...
        return it.current();
    }

  return NULL;
}

/************************ListViews::searchNode(QListViewItem* me)------------->
 **
 ** Parameters:- QListViewItem* :- pointer to node of the tree to be searched
 **
 ** Returns  :-   int :- 1-> if found; 0 if not found 
 ** Description:- This method is used to search a particular node in the 
 ** tree with input parameter as QListViewItem
 *****************************************************************************/
int ListViews::searchNode(QListViewItem* me)
{
  QListViewItemIterator it(folders);

  for (; it.current(); ++it)
    if (it.current() == me)
      return 1;

  return 0;
}

/************************ListViews::searchNode(int id)---------->
 **
 ** Parameters:- int :- the id of the object to be searched
 **
 ** Returns  :-  QListViewItem* :- Pointer to the node searched for or null if nuthing is found 
 ** Description:-This method is used to search a particular node in the 
 **              tree with input parameter as id number
 ************************************************************/
QListViewItem* ListViews::searchNode(int id)
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

/************************ListViews::searchNode(const char* name)--------------------->
 **
 ** Parameters:- int :- the id of the object to be searched
 **
 ** Returns  :-  QListViewItem* :- Pointer to the node searched for or null if nuthing is found 
 ** Description:-This method is used to search a particular node in the 
 ** tree with input parameter as folder name
 ********************************************************************************/
QListViewItem* ListViews::searchNode(const char* name)
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
  // to show the folders open or close or locked..
  if (!i) return;

  if (i->childCount() != 0)
    i->setPixmap(0, *folderOpen);

  // to change the status of the folder (closed/open)
  if (lastSelection)
    if (lastSelection->childCount() == 0)
    {} // i was not expandable..than
    else
      lastSelection->setPixmap(0, *folderClosed);

  lastSelection = i;

  // get the qlistview item in form of folderlistitem...
  FolderListItem *item = (FolderListItem*)i;

  bigWidget->setText("You Clicked On: " + item->folder()->folderName());

  //char * fName=item->folder()->folderName();

  QListViewItem* i1 = i->parent();

  // get the qlistview item in form of folderlistitem...
  FolderListItem *item1 = (FolderListItem*)i1;

  int value = QString::compare(item->folder()->folderName(), "Metabolites");

  if (!value)
    {
      currentWidget = metabolitesWidget;
      metabolitesWidget->repaint_table();
    }
  else if (! (value = QString::compare(item->folder()->folderName(), "Metabolite Symbols")))
    currentWidget = metaboliteSymbols;
  else if (! (value = QString::compare(item->folder()->folderName(), "Differential Equations")))
    currentWidget = differentialEquations;
  else if (! (value = QString::compare(item->folder()->folderName(), "Fixed Metabolite Symbols")))
    currentWidget = fixedMetaboliteSymbols;
  else if (! (value = QString::compare(item->folder()->folderName(), "Reactions")))
    {
      currentWidget = reactionsWidget;
      reactionsWidget->repaint_table();
    }
  else if (! (value = QString::compare(item->folder()->folderName(), "Compartments")))
    {
      currentWidget = compartmentsWidget;
      compartmentsWidget->repaint_table();
    }
  else if (! (value = QString::compare(item->folder()->folderName(), "Compartment Symbols")))
    currentWidget = compartmentSymbols;
  else if (! (value = QString::compare(item->folder()->folderName(), "Constant Symbols")))
    currentWidget = constantSymbols;
  else if (! (value = QString::compare(item->folder()->folderName(), "Function Symbols")))
    currentWidget = functionSymbols;
  else if (! (value = QString::compare(item->folder()->folderName(), "Moiety")))
    currentWidget = moietyWidget;
  else if (! (value = QString::compare(item->folder()->folderName(), "Functions")))
    {
      currentWidget = functionWidget;
      functionWidget->repaint_table();
    }
  else if (! (value = QString::compare(item->folder()->folderName(), "Steady-State")))
    currentWidget = steadystateWidget;
  else if (! (value = QString::compare(item->folder()->folderName(), "Time Course")))
    currentWidget = trajectoryWidget;
  else if (! (value = QString::compare(item->folder()->folderName(), "Mass Conservation")))
    currentWidget = moietyWidget;
  else if (! (value = QString::compare(item->folder()->folderName(), "Elementary Modes")))
    currentWidget = modesWidget;
  else if (item1)
    {
      if (! (value = QString::compare(item1->folder()->folderName(), "Compartments")))
        {
          if (compartmentsWidget1->isName(item->folder()->folderName()) == 1)
            {
              currentWidget = compartmentsWidget1;
            }
        }

      else if (! (value = QString::compare(item1->folder()->folderName(), "Reactions")))
        {
          if (reactionsWidget1->isName(item->folder()->folderName()) == 1)
            {
              currentWidget = reactionsWidget1;
            }
        }

      else if (! (value = QString::compare(item1->folder()->folderName(), "Metabolites")))
        {
          if (metabolitesWidget1->isName(item->folder()->folderName()) == 1)
            {
              currentWidget = metabolitesWidget1;
            }
        }
      else if (! (value = QString::compare(item1->folder()->folderName(), "Moiety")))
        {
          if (moietyWidget1->isName(item->folder()->folderName()) == 1)
            {
              currentWidget = moietyWidget1;
            }
        }
      else if (! (value = QString::compare(item1->folder()->folderName(), "Functions")))
        {
          if (functionWidget1->isName(item->folder()->folderName()) == 1)
            {
              currentWidget = functionWidget1;
            }
        }

      else if (! (value = QString::compare(item1->folder()->folderName(), "Mass Conservation")))
        {
          if (moietyWidget1->isName(item->folder()->folderName()) == 1)
            {
              currentWidget = moietyWidget1;
            }
        }
    }
  else
    currentWidget = bigWidget;

  // this is used to hide and show the necessary widget on the screen
  if (lastWidget)
    lastWidget->hide();

  if (currentWidget)
    currentWidget->show();

  lastWidget = currentWidget;
}

/************************ListViews::setDataModel(DataModel<Folder>* dm)----------->
 **
 ** Parameters:- DataModel<Folder>* :- pointer to the data model to be used by all the
 **              views
 ** Returns  :-  void(Nothing)
 ** Description:-This method is used to set the datamodel to be used by the
 ** listview class to extract the data from the data-model
 ************************************************************************************/
void ListViews::setDataModel(DataModel<Folder>* dm)
{
  // get the dataModel
  dataModel = dm;
  dataModel->attach(this);
  initFolders();
  setupFolders();

  dataModel->setModelUpdate(true);

  // get the model information and than construct the nodes and load them
  mModel = dataModel->getModel();
  this->ConstructNodeWidgets();
  this->loadModelNodes(mModel);
  loadFunction();
  dataModel->setModelUpdate(false);

  //added by Liang Xu
  mSteadyStateTask = dataModel->getSteadyStateTask();
  mTrajectoryTask = dataModel->getTrajectoryTask();
  this->loadSteadyStateTaskNodes(mSteadyStateTask);
  this->loadTrajectoryTaskNodes(mTrajectoryTask);
}

/***********ListViews::update(Subject* theChangedSubject,int status)----------->
 **
 ** Parameters:- 1. Subject* :- Pointer to the subject object used in doc/view kind of 
 **                             arch.
 **              2. int :- the status of wht data has been changed in the data model
 **                        may it be addition of new data/deletion of data/or change of 
 **                        model itself
 ** Returns  :-  void(Nothing)
 ** Description:-This routine is called whenever there is any change in the datamodel
 ** to update itself based on the change
 ************************************************************/
void ListViews::update(Subject* theChangedSubject, int status)
{
  if (theChangedSubject == dataModel)
    {
      // get the status of what change has been done...
      //int STATUS=dataModel->getStatus();
      //int STATUS=st;
      QListViewItem* it = NULL;
      Node<Folder> * node = NULL;

      switch (status)
        {
          // WHEN THE STATUS IS 1 IE. WHEN A NEW DATA IS ADDED IN THE TREE
          // ADD DEFINED IN DATAMODEL.H
        case ADD:
          if ((node = dataModel->getData()) != NULL)
            {
              /* This routines were used to draw from the node again...which was not
                 //effecient so the other one only the takes the node that is added
                        initFolders(node);
               if(it=searchNode(node->info))
                  setupFolders(it);
              */ 
              // chech first that am i one of the top level nodes if so than
              // showMessage("Ankur","It comes in Add");

              if (node->parent->info->getID() == 0)
                addItem(folders, node->info);
              else
                addItem(searchNode(node->parent->info->getID()), node->info);
            }

          break;

          // WHEN ANY DATA IS DELETED FROM THE TREE
        case DELETE:
          if ((node = dataModel->getData()) != NULL)
            // check if the node that is requested to be deleted is present or not
            // if present than check whether it is the top level node or child of one of
            // the top level node
            // if topleve node than call clearParentItem else call clearItem
            if ((it = searchNode(node->info->getID())))
              (node->parent->info->getID() == 0) ? clearParentItem(it) : clearItem(it);

          break;

          // new model is loaded.
        case MODEL:
          // if new model is loaded than get the new model and reload the widgets again
          //   showMessage("Ankur","It comes in model ");
          mModel = dataModel->getModel();
          this->loadModelNodes(mModel);
          break;

        case STEADYSTATETASK:
          mSteadyStateTask = dataModel->getSteadyStateTask();
          this->loadSteadyStateTaskNodes(mSteadyStateTask);
          break;

        case TRAJECTORYTASK:
          mTrajectoryTask = dataModel->getTrajectoryTask();
          this->loadTrajectoryTaskNodes(mTrajectoryTask);
          break;
        }
    }
  else
    QMessageBox::about(this, "Update Application",
                       "Error in updating the stuff");
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

/***********ListViews::deleteAllMyChildrens(QListViewItem* me)-------->
 **
 ** Parameters:- QListViewItem* :- The node whose items needs to be removed
 ** Returns  :-  void(Nothing)
 ** Description:-This method is used to delete all my childrens..
 **              from datamodel 
 ********************************************************************/
void ListViews::deleteAllMyChildrens(QListViewItem* me)
{
  QListViewItem *myChild = me->firstChild();
  QListViewItem * nextChild = myChild;

  FolderListItem* item;

  while (myChild)
    {
      if (myChild == lastSelection)
        lastSelection = NULL;

      nextChild = myChild;
      myChild = myChild->nextSibling();
      // first delete that item...
      item = (FolderListItem*)nextChild;
      // send the message to remove this particular folder from the list..
      dataModel->removeData(item->folder());
    }
}

void ListViews::loadCompartmentsNodes(CModel *model)
{
  compartmentsWidget->loadCompartments(model);
  compartmentsWidget1->loadCompartments(model);
  QListViewItem* loadNode; // to load the tree with that stuff
  // UPDATE THE METABOLITES STUFF..
  loadNode = searchNode("Compartments");
  if (loadNode)
    {
      this->loadCompartments(loadNode);

      if (loadNode->isSelected())
        if (loadNode->childCount() != 0)
          loadNode->setPixmap(0, *folderOpen);

      loadNode = NULL;
    }
}
void ListViews::loadReactionsNodes(CModel* model)
{
  reactionsWidget->loadReactions(model);
  reactionsWidget1->loadReactions(model);
  QListViewItem* loadNode; // to load the tree with that stuff
  // UPDATE THE METABOLITES STUFF..
  loadNode = searchNode("Reactions");
  if (loadNode)
    {
      this->loadReactions(loadNode);

      if (loadNode->isSelected())
        if (loadNode->childCount() != 0)
          loadNode->setPixmap(0, *folderOpen);

      loadNode = NULL;
    }
}
void ListViews::loadMetabolitesNodes(CModel* model)
{
  metabolitesWidget->loadMetabolites(model);
  metabolitesWidget1->loadMetabolites(model);
  QListViewItem* loadNode; // to load the tree with that stuff
  // UPDATE THE METABOLITES STUFF..
  loadNode = searchNode("Metabolites");
  if (loadNode)
    {
      this->loadMetabolites(loadNode);

      if (loadNode->isSelected())
        if (loadNode->childCount() != 0)
          loadNode->setPixmap(0, *folderOpen);
      loadNode = NULL;
    }
}

void ListViews::loadMoietiesNodes(CModel* model)
{
  moietyWidget->loadMoieties(model);
  moietyWidget1->loadMoieties(model);
  QListViewItem* loadNode; // to load the tree with that stuff
  // UPDATE THE METABOLITES STUFF..

  loadNode = searchNode("Moiety");
  if (loadNode)
    {
      this->loadMoieties(loadNode);

      if (loadNode->isSelected())
        if (loadNode->childCount() != 0)
          loadNode->setPixmap(0, *folderOpen);

      loadNode = NULL;
    }
}

/***********ListViews::loadNodes(CModel *model)-------->
 **
 ** Parameters:- CModel* :- The model that needs to be loaded by the widgets
 ** Returns  :-  void(Nothing)
 ** Description:-This method is used to load the nodes with the information
 ***********************************************************/
void ListViews::loadModelNodes(CModel *model)
{
  if (model != NULL)
    {
      QListViewItem* loadNode; // to load the tree with that stuff
      // UPDATE THE METABOLITES STUFF..

      pdelete(mpMathModel);
      mpMathModel = new CMathModel;
      mpMathModel->setModel(model);

      fixedMetaboliteSymbols->loadFixedMetaboliteSymbols(mpMathModel);
      metaboliteSymbols->loadMetaboliteSymbols(mpMathModel);
      functionSymbols->loadFunctionSymbols(mpMathModel);
      constantSymbols->loadConstantSymbols(mpMathModel);
      compartmentSymbols->loadCompartmentSymbols(mpMathModel);
      differentialEquations->loadDifferentialEquations(mpMathModel);

      loadMetabolitesNodes(model);
      // UPDATE THE REACTIONS STUFF..
      loadReactionsNodes(model);
      // UPDATE THE COMPARTMENTS STUFF..
      loadCompartmentsNodes(model);
      // UPDATE THE MOIETIES STUFF..
      loadMoietiesNodes(model);

      // UPDATE THE FUNCTIONS STUFF..
      this->loadFunction();

      // Load the Elementary Modes
      modesWidget->loadModes(model);
      //second level of mass conservation
      loadNode = searchNode("Mass Conservation");

      if (loadNode)
        {
          this->loadMoieties(loadNode);

          if (loadNode->isSelected())
            if (loadNode->childCount() != 0)
              loadNode->setPixmap(0, *folderOpen);

          loadNode = NULL;
        }
    }
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
  // if (mModel != NULL)
  {
    //Constructing the Reactions Widget
    reactionsWidget = new ReactionsWidget(this);
    reactionsWidget->hide();

    //Constructing the Metabolites Widget
    metabolitesWidget = new MetabolitesWidget(this);
    metabolitesWidget->hide();

    //Constructing the Constant Symbols
    metaboliteSymbols = new MetaboliteSymbols(this);
    metaboliteSymbols->hide();

    //Constructing the Constant Symbols
    differentialEquations = new DifferentialEquations(this);
    differentialEquations->hide();

    //Constructing the Constant Symbols
    fixedMetaboliteSymbols = new FixedMetaboliteSymbols(this);
    fixedMetaboliteSymbols->hide();

    //Constructing the Compartments Widget
    compartmentsWidget = new CompartmentsWidget(this);
    compartmentsWidget->hide();

    //Constructing the Compartments Symbols
    compartmentSymbols = new CompartmentSymbols(this);
    compartmentSymbols->hide();

    //Constructing the Constant Symbols
    constantSymbols = new ConstantSymbols(this);
    constantSymbols->hide();

    //Constructing the Moieties Widget
    moietyWidget = new MoietyWidget(this);
    moietyWidget->hide();

    //Constructing the Function Widget
    functionWidget = new FunctionWidget(this);
    functionWidget->hide();

    //Constructing the Constant Symbols
    functionSymbols = new FunctionSymbols(this);
    functionSymbols->hide();

    //Constructing the SteadyStateTask Widget
    steadystateWidget = new SteadyStateWidget(this);
    steadystateWidget->hide();

    trajectoryWidget = new TrajectoryWidget(this);
    trajectoryWidget->hide();

    //Constructing the Reactions Widget1
    reactionsWidget1 = new ReactionsWidget1(this);
    reactionsWidget1->hide();

    //Constructing the Moiety Widget1
    moietyWidget1 = new MoietyWidget1(this);
    moietyWidget1->hide();

    //Constructing the Compartments Widget1
    compartmentsWidget1 = new CompartmentsWidget1(this);
    compartmentsWidget1->hide();

    //Constructing the Metabolites Widget1
    metabolitesWidget1 = new MetabolitesWidget1(this);
    metabolitesWidget1->hide();

    //Constructing the Function Widget1
    functionWidget1 = new FunctionWidget1(this);
    functionWidget1->hide();

    //Constructing the Elementary Modes Widget1
    modesWidget = new ModesWidget(this);
    modesWidget->hide();
  }
}

/***********ListViews::loadMetabolites(QListViewItem* i)---------------------------->
 **
 ** Parameters:- QListViewItem* :- The node where these new nodes should be added to
 ** Returns  :-  void(Nothing)
 ** Description:-This method is used to load the metabolites nodes to the 
 **              i node as obtained by the parameter
 *************************************************************************/
void ListViews::loadMetabolites(QListViewItem* i)
{
  if (mModel == NULL)
    return;

  if (!dataModel->getModelUpdate())
    return; // if the model is not updated than return

  //   showMessage("Ankur","This is duplicate call");
  FolderListItem *item = (FolderListItem*)i;

  if (i->childCount() != 0)
    deleteAllMyChildrens(i); // is used if u want to delete all mychildrens

  Folder* p, *f;

  p = item->folder();

  int myId = item->folder()->getID();

  // multiply myId by 1000000 and than add these items with seq nu..of that id..
  // myId = 10 * myId;

  CCopasiVectorN< CMetab > metabolites = mModel->getMetabolites();

  C_INT32 noOfMetabolitesRows = metabolites.size();

  //Now filling the table.
  CMetab *metab;
  C_INT32 j;
  for (j = 0; j < noOfMetabolitesRows; j++)
    {
      metab = metabolites[j];
      f = new Folder(p, metab->getName().c_str());
      f->setID(myId);
      dataModel->addData(p, f);
    }
}

void ListViews::loadMoieties(QListViewItem* i)
{
  if (mModel == NULL)
    return;

  if (!dataModel->getModelUpdate())
    return; // if the model is not updated than return

  //   showMessage("Ankur","This is duplicate call");
  FolderListItem *item = (FolderListItem*)i;

  if (i->childCount() != 0)
    deleteAllMyChildrens(i); // is used if u want to delete all mychildrens

  Folder* p, *f;

  p = item->folder();

  int myId = item->folder()->getID();

  // multiply myId by 1000000 and than add these items with seq nu..of that id..
  //  myId = 10 * myId;

  const CCopasiVectorN < CMoiety > * moieties = &mModel->getMoieties();

  //Now filling the table.
  CMoiety *moiety;
  unsigned C_INT32 j;
  for (j = 0; j < moieties->size(); j++)
    {
      moiety = (*moieties)[j];
      f = new Folder(p, moiety->getName().c_str());
      f->setID(myId);
      dataModel->addData(p, f);
    }
}

void ListViews::loadReactions(QListViewItem* i)
{
  if (mModel == NULL)
    return;

  if (!dataModel->getModelUpdate())
    return; // if the model is not updated than return

  FolderListItem *item = (FolderListItem*)i;

  if (i->childCount() != 0)
    deleteAllMyChildrens(i); // is used if u want to delete all mychildrens

  Folder* p, *f;

  p = item->folder();

  int myId = item->folder()->getID();

  // multiply myId by 1000000 and than add these items with seq nu..of that id..
  //  myId = 10 * myId;

  CCopasiVectorNS < CReaction > * reactions = &mModel->getReactions();

  //Now filling the table.
  CReaction *reactn;
  unsigned C_INT32 j;
  for (j = 0; j < reactions->size(); j++)
    {
      reactn = (*reactions)[j];
      f = new Folder(p, reactn->getName().c_str());
      f->setID(myId);
      dataModel->addData(p, f);
    }
}

void ListViews::loadCompartments(QListViewItem* i)
{
  if (mModel == NULL)
    return;

  if (!dataModel->getModelUpdate())
    return; // if the model is not updated than return

  //   showMessage("Ankur","This is duplicate call");
  FolderListItem *item = (FolderListItem*)i;

  if (i->childCount() != 0)
    deleteAllMyChildrens(i); // is used if u want to delete all mychildrens

  Folder* p, *f;

  p = item->folder();

  int myId = item->folder()->getID();

  // multiply myId by 1000000 and than add these items with seq nu..of that id..
  //  myId = 10 * myId;

  const CCopasiVectorNS < CCompartment > & compartments = mModel->getCompartments();

  C_INT32 noOfCompartmentsRows = compartments.size();

  //Now filling the table.
  const CCompartment *compartn;
  C_INT32 j;
  for (j = 0; j < noOfCompartmentsRows; j++)
    {
      compartn = compartments[j];
      f = new Folder(p, compartn->getName().c_str());
      f->setID(myId);
      dataModel->addData(p, f);
    }
}

/***********ListViews::loadFunction(QListViewItem* i)---------------------------->
 **
 ** Parameters:- QListViewItem* :- The node where these new nodes should be added to
 ** Returns  :-  void(Nothing)
 ** Description:-This method is used to load the function nodes to the 
 **              i node as obtained by the parameter
 *************************************************************************/
void ListViews::loadFunction()
{
  functionWidget->loadFunction();

  // If the model is not updated or "Functions" node does not exist than return.
  QListViewItem * i = searchNode("Functions");
  if (!dataModel->getModelUpdate() || !i)
    return;

  FolderListItem *item = (FolderListItem*)i;
  if (i->childCount() != 0)
    deleteAllMyChildrens(i); // is used if u want to delete all mychildrens

  Folder* p, *f;

  p = item->folder();
  int myId = item->folder()->getID();
  // multiply myId by 1000000 and than add these items with seq nu..of that id..
  //  myId = 10 * myId;

  CCopasiVectorNS< CFunction > & Functions = Copasi->pFunctionDB->loadedFunctions();
  C_INT32 noOfFunctionsRows = Functions.size();

  //Now filling the table.
  CFunction *funct;
  C_INT32 j;
  for (j = 0; j < noOfFunctionsRows; j++)
    {
      funct = Functions[j];
      f = new Folder(p, funct->getName().c_str());
      f->setID(myId);
      dataModel->addData(p, f);
    }

  if (i->isSelected())
    if (i->childCount() != 0)
      i->setPixmap(0, *folderOpen);
  dataModel->setModelUpdate(false);
}

/***********ListViews::showMessage(QString caption,QString text)------------------------>
 **
 ** Parameters:- 1. QString :- The Title that needs to be displayed in message box
 **              2. QString :_ The Text that needs to be displayed in the message box
 ** Returns  :-  void(Nothing)
 ** Description:- This method is used to show the message box on the screen
 ****************************************************************************************/

void ListViews::showMessage(QString title, QString text)
{
  QMessageBox::about (this, title, text);
}

void ListViews::slotCompartmentTableChanged(const QString &s)
{
  compartmentsWidget1->isName(s);
  //QMessageBox::information(this, "Compartments Widget","kk");
  currentWidget = compartmentsWidget1;

  if (lastWidget)
    lastWidget->hide();

  if (currentWidget)
    currentWidget->show();

  lastWidget = currentWidget;
}

void ListViews::slotMetaboliteTableChanged(const QString &s)
{
  metabolitesWidget1->isName(s);
  //QMessageBox::information(this, "Metabolites Widget","kk");
  currentWidget = metabolitesWidget1;

  if (lastWidget)
    lastWidget->hide();

  if (currentWidget)
    currentWidget->show();

  lastWidget = currentWidget;
}

void ListViews::slotMoietyTableChanged(const QString &s)
{
  moietyWidget1->isName(s);
  //QMessageBox::information(this, "Metabolites Widget","kk");
  currentWidget = moietyWidget1;

  if (lastWidget)
    lastWidget->hide();

  if (currentWidget)
    currentWidget->show();

  lastWidget = currentWidget;
}

void ListViews::slotReactionTableChanged(const QString &s)
{
  reactionsWidget1->isName(s);
  //QMessageBox::information(this, "Metabolites Widget","kk");
  currentWidget = reactionsWidget1;

  if (lastWidget)
    lastWidget->hide();

  if (currentWidget)
    currentWidget->show();

  lastWidget = currentWidget;
}

void ListViews::slotFunctionTableChanged(const QString &s)
{
  functionWidget1->isName(s);
  currentWidget = functionWidget1;

  if (lastWidget)
    lastWidget->hide();

  if (currentWidget)
    currentWidget->show();

  lastWidget = currentWidget;
}

void ListViews::slotNewReaction()
{
  //Constructing the Reactions Widget1
  //reactionsWidget1 = new ReactionsWidget1(this);
  reactionsWidget->slotTableCurrentChanged(reactionsWidget->numTableRows() - 1, 0, 0, QPoint());
  //
  reactionsWidget1->isName("R1");
  currentWidget = reactionsWidget1;

  if (lastWidget)
    lastWidget->hide();

  if (currentWidget)
    currentWidget->show();
  lastWidget = currentWidget;
}

void ListViews::loadSteadyStateTaskNodes(CSteadyStateTask* steadystatetask)
{
  if (steadystatetask != NULL)
    {
      QListViewItem* loadNode; // to load the tree with that stuff

      // UPDATE THE METABOLITES STUFF..
      steadystateWidget->loadSteadyStateTask(steadystatetask);
      loadNode = searchNode("Steady-State");

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
      dataModel->setSteadyStateTaskUpdate(false);
    }
}

void ListViews::loadTrajectoryTaskNodes(CTrajectoryTask* trajectorytask)
{
  if (trajectorytask != NULL)
    {
      QListViewItem* loadNode; // to load the tree with that stuff

      // UPDATE THE METABOLITES STUFF..
      trajectoryWidget->loadTrajectoryTask(trajectorytask);
      loadNode = searchNode("Trajectory");

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
      dataModel->setTrajectoryTaskUpdate(false);
    }
}

void ListViews::dataModelUpdated()
{
  dataModel->setModelUpdate(true);
}
