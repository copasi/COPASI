/****************************************************************************
 **  $ CopasiUI/listviews.cpp                 Modified on : 18th March, 2002
 **  $ Author  : Ankur Gupta
 **  
 ** This file contains the defination of the routines declared in listviews.h header
 ** file. 
 **
 ** This file is used to create the visual tree based on the information obtained from the data
 ** model about the tree
 **********************************************************************/

#include "listviews.h"

QPixmap *folderLocked = 0;   // to store the image of locked icon folder
QPixmap *folderClosed = 0;   // to store the image of closed icon folder
QPixmap *folderOpen = 0;     // to store the image of open icon folder

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
ListViews::ListViews(QWidget *parent, const char *name)
    : QSplitter(Qt::Horizontal, parent, name)
{
  // creates the image to be displayed when folder is closed/locked/open
  folderLocked = new QPixmap((const char**)folderlocked);
  folderClosed = new QPixmap((const char**)folderclosed);
  folderOpen = new QPixmap((const char**)folderopen);

  // setting the parameter for the qptrlist...
  lstFolders.setAutoDelete(FALSE);

  //  create a new QListview to be displayed on the screen..and set its property
  folders = new QListView(this);
  folders->header()->setClickEnabled(FALSE);
  folders->addColumn("Select ");
  folders->setRootIsDecorated(TRUE);

  //  This sections intializes the components used in the display part
  bigWidget = new QMultiLineEdit(this);
  bigWidget->setText("This widget will get all the remaining space");
  bigWidget->setFrameStyle(QFrame::Panel | QFrame::Plain);
  bigWidget->setReadOnly(FALSE);

  //  This section defines few of the variables that will be used in the code
  lastSelection = NULL;          // keeps track of the node that was selected last..to change the icon type
  currentWidget = bigWidget; // keeps track of the currentWidget in use
  lastWidget = bigWidget; // keeps track of the lastWidget that was used
  mModel = NULL;             // keeps track of the model that is used..

  // establishes the communication betweent the folders clicked and the routine called....
  connect(folders, SIGNAL(selectionChanged (QListViewItem*)),
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

  //this is needed because when the tree is created the root is not needed in this
  // visual display
  // than append all the information in the vector to be used later by setup folder

  if (next)
    for (next = next->child; next != NULL; next = next->sibling)
      lstFolders.append(next->info);
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

  for (Folder* f = lstFolders.first(); f; f = lstFolders.next())
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
 ** Returns  :-   int :- 1-> if found ; 0 if not found 
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

/************************ListViews::searchNode(char* name)--------------------->
 **
 ** Parameters:- int :- the id of the object to be searched
 **
 ** Returns  :-  QListViewItem* :- Pointer to the node searched for or null if nuthing is found 
 ** Description:-This method is used to search a particular node in the 
 ** tree with input parameter as folder name
 ********************************************************************************/
QListViewItem* ListViews::searchNode(char* name)
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

  QListViewItem* i1 = i->parent () ;

  // get the qlistview item in form of folderlistitem...
  FolderListItem *item1 = (FolderListItem*)i1;

  int value = QString::compare(item->folder()->folderName(), "Metabolites");

  if (!value)
    currentWidget = metabolitesWidget;

  else if (! (value = QString::compare(item->folder()->folderName(), "Reactions")))
    {
      currentWidget = reactionsWidget;
    }

  else if (! (value = QString::compare(item->folder()->folderName(), "Compartments")))
    currentWidget = compartmentsWidget;
  else if (! (value = QString::compare(item->folder()->folderName(), "Moiety")))
    currentWidget = moietyWidget;

  else if (! (value = QString::compare(item1->folder()->folderName(), "Compartments")))
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

  else
    {
      switch (item->folder()->getID())
        {
        case 21 :    // for showing addition...of new components..

          // deleteAllMyChildrens(i); //is used if u want to delete all mychildrens

          /*if(this->searchNode(215) == NULL)
          {
           str = QString("1");
                 p=item->folder();
                 f = new Folder(0,str);
                 f->setID(215);

          dataModel->addData(dataModel->getRoot()->info,f);
           dataModel->notifyAll();
          }*/
          currentWidget = bigWidget;
          break;

        case 41:
          //this used to show how the data is removed..
          /*item=(FolderListItem*)this->searchNode(42);
          if(item){
           dataModel->removeData(item->folder());
           dataModel->notifyAll();
          }*/
          currentWidget = bigWidget;
          break;

        default:
          currentWidget = bigWidget;
        }
    }

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

  // get the model information and than construct the nodes and load them
  mModel = dataModel->getModel();
  this->ConstructNodeWidgets();
  this->loadNodes(mModel);
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
        case ADD:     // WHEN THE STATUS IS 1 IE. WHEN A NEW DATA IS ADDED IN THE TREE
          // ADD DEFINED IN DATAMODEL.H

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

        case DELETE:   // WHEN ANY DATA IS DELETED FROM THE TREE
          // showMessage("Ankur","It comes in delete");

          if ((node = dataModel->getData()) != NULL)
            // check if the node that is requested to be deleted is present or not
            // if present than check whether it is the top level node or child of one of
            // the top level node
            // if topleve node than call clearParentItem else call clearItem
            if (it = searchNode(node->info->getID()))
              (node->parent->info->getID() == 0) ? clearParentItem(it) : clearItem(it);

          break;

        case MODEL:     // new model is loaded.
          // if new model is loaded than get the new model and reload the widgets again
          //   showMessage("Ankur","It comes in model ");
          mModel = dataModel->getModel();

          this->loadNodes(mModel);
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
      nextChild = myChild;
      myChild = myChild->nextSibling();
      // first delete that item...
      item = (FolderListItem*)nextChild;
      // send the message to remove this particular folder from the list..
      dataModel->removeData(item->folder());
    }
}

/***********ListViews::loadNodes(CModel *model)-------->
 **
 ** Parameters:- CModel* :- The model that needs to be loaded by the widgets
 ** Returns  :-  void(Nothing)
 ** Description:-This method is used to load the nodes with the information
 ***********************************************************/
void ListViews::loadNodes(CModel *model)
{
  if (model != NULL)
    {
      QListViewItem* loadNode; // to load the tree with that stuff
      // UPDATE THE METABOLITES STUFF..
      metabolitesWidget->loadMetabolites(model);
      metabolitesWidget1->loadMetabolites(model);
      loadNode = searchNode("Metabolites");

      if (loadNode)
        {
          this->loadMetabolites(loadNode);

          if (loadNode->isSelected())
            if (loadNode->childCount() != 0)
              loadNode->setPixmap(0, *folderOpen);

          loadNode = NULL;
        }

      // UPDATE THE REACTIONS STUFF..
      reactionsWidget->loadReactions(model);

      reactionsWidget1->loadReactions(model);

      loadNode = searchNode("Reactions");

      if (loadNode)
        {
          this->loadReactions(loadNode);

          if (loadNode->isSelected())
            if (loadNode->childCount() != 0)
              loadNode->setPixmap(0, *folderOpen);

          loadNode = NULL;
        }

      // UPDATE THE COMPARTMENTS STUFF..
      compartmentsWidget->loadCompartments(model);

      compartmentsWidget1->loadCompartments(model);

      loadNode = searchNode("Compartments");

      if (loadNode)
        {
          this->loadCompartments(loadNode);

          if (loadNode->isSelected())
            if (loadNode->childCount() != 0)
              loadNode->setPixmap(0, *folderOpen);

          loadNode = NULL;
        }

      // UPDATE THE MOIETIES STUFF..
      moietyWidget->loadMoieties(model);

      moietyWidget1->loadMoieties(model);

      loadNode = searchNode("Moiety");

      if (loadNode)
        {
          this->loadMoieties(loadNode);

          if (loadNode->isSelected())
            if (loadNode->childCount() != 0)
              loadNode->setPixmap(0, *folderOpen);

          loadNode = NULL;
        }

      // AT THE END... SET THE UPDATE FALSE SO THAT NO OTHER VIEW IS ABLE TO REPEAT THE
      // SAME STUFF AGAIN..
      dataModel->setModelUpdate(false);
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

    //Constructing the Compartments Widget
    compartmentsWidget = new CompartmentsWidget(this);
    compartmentsWidget->hide();

    //Constructing the Moieties Widget
    moietyWidget = new MoietyWidget(this);
    moietyWidget->hide();

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
    return ;

  if (!dataModel->getModelUpdate())
    return ; // if the model is not updated than return

  //   showMessage("Ankur","This is duplicate call");
  FolderListItem *item = (FolderListItem*)i;

  if (i->childCount() != 0)
    deleteAllMyChildrens(i); // is used if u want to delete all mychildrens

  Folder* p, *f;

  p = item->folder();

  int myId = item->folder()->getID();

  // multiply myId by 10 and than add these items with seq nu..of that id..
  myId = 10 * myId;

  vector < CMetab * > metabolites = mModel->getMetabolites();

  C_INT32 noOfMetabolitesRows = metabolites.size();

  //Now filling the table.
  CMetab *metab;

  for (C_INT32 j = 0; j < noOfMetabolitesRows; j++)
    {
      metab = metabolites[j];
      f = new Folder(p, metab->getName().c_str());
      f->setID(myId + j + 1);
      dataModel->addData(p, f);
    }
}

void ListViews::loadMoieties(QListViewItem* i)
{
  if (mModel == NULL)
    return ;

  if (!dataModel->getModelUpdate())
    return ; // if the model is not updated than return

  //   showMessage("Ankur","This is duplicate call");
  FolderListItem *item = (FolderListItem*)i;

  if (i->childCount() != 0)
    deleteAllMyChildrens(i); // is used if u want to delete all mychildrens

  Folder* p, *f;

  p = item->folder();

  int myId = item->folder()->getID();

  // multiply myId by 10 and than add these items with seq nu..of that id..
  myId = 10 * myId;

  /*CCopasiVectorN < CMoiety >  &moieties = mModel->getMoieties();

   C_INT32 noOfMoietyRows = moieties.size();

   
    //Now filling the table.
   CMoiety *moiety;
   for (C_INT32  j = 0; j < noOfMoietyRows; j++)
   {
    moiety = moieties[j];
             f=new Folder(p,moiety->getName().c_str());
    f->setID(myId+j+1);
    dataModel->addData(p,f);
    
   }*/

  CCopasiVectorN < CMoiety > * moieties = &mModel->getMoieties();

  //Now filling the table.
  CMoiety *moiety;

  for (C_INT32 j = 0; j < moieties->size(); j++)
    {
      moiety = (*moieties)[j];
      f = new Folder(p, moiety->getName().c_str());
      f->setID(myId + j + 1);
      dataModel->addData(p, f);
    }
}

void ListViews::loadReactions(QListViewItem* i)
{
  if (mModel == NULL)
    return ;

  if (!dataModel->getModelUpdate())
    return ; // if the model is not updated than return

  //   showMessage("Ankur","This is duplicate call");
  FolderListItem *item = (FolderListItem*)i;

  if (i->childCount() != 0)
    deleteAllMyChildrens(i); // is used if u want to delete all mychildrens

  Folder* p, *f;

  p = item->folder();

  int myId = item->folder()->getID();

  // multiply myId by 10 and than add these items with seq nu..of that id..
  myId = 10 * myId;

  CCopasiVectorNS < CReaction > & reactions = mModel->getReactions();

  C_INT32 noOfReactionsRows = reactions.size();

  //Now filling the table.
  CReaction *reactn;

  for (C_INT32 j = 0; j < noOfReactionsRows; j++)
    {
      reactn = reactions[j];
      f = new Folder(p, reactn->getName().c_str());
      f->setID(myId + j + 1);
      dataModel->addData(p, f);
    }
}

void ListViews::loadCompartments(QListViewItem* i)
{
  if (mModel == NULL)
    return ;

  if (!dataModel->getModelUpdate())
    return ; // if the model is not updated than return

  //   showMessage("Ankur","This is duplicate call");
  FolderListItem *item = (FolderListItem*)i;

  if (i->childCount() != 0)
    deleteAllMyChildrens(i); // is used if u want to delete all mychildrens

  Folder* p, *f;

  p = item->folder();

  int myId = item->folder()->getID();

  // multiply myId by 10 and than add these items with seq nu..of that id..
  myId = 10 * myId;

  CCopasiVectorNS < CCompartment > & compartments = mModel->getCompartments();

  C_INT32 noOfCompartmentsRows = compartments.size();

  //Now filling the table.
  CCompartment *compartn;

  for (C_INT32 j = 0; j < noOfCompartmentsRows; j++)
    {
      compartn = compartments[j];
      f = new Folder(p, compartn->getName().c_str());
      f->setID(myId + j + 1);
      dataModel->addData(p, f);
    }
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

void ListViews::slotCompartmentSelected(const QString &s)
{
  compartmentsWidget1->isName(s);
  currentWidget = compartmentsWidget1;

  if (lastWidget)
    lastWidget->hide();

  if (currentWidget)
    currentWidget->show();

  lastWidget = currentWidget;
}

void ListViews::slotMetaboliteSelected(const QString &s)
{
  metabolitesWidget1->isName(s);
  currentWidget = metabolitesWidget1;

  if (lastWidget)
    lastWidget->hide();

  if (currentWidget)
    currentWidget->show();

  lastWidget = currentWidget;
}

/*void  ListViews::slotCompartmentTableChanged(int row, int col)
{
  compartmentsWidget1->isName(s);
  currentWidget = compartmentsWidget1;
 
  if (lastWidget)
    lastWidget->hide();
 
  if (currentWidget)
    currentWidget->show();
 
  lastWidget = currentWidget;
}
 */
