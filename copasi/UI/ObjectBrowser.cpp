/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ObjectBrowser.cpp,v $
   $Revision: 1.81 $
   $Name:  $
   $Author: lixu1 $ 
   $Date: 2003/12/15 23:07:33 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 04/03 
Comment : Copasi Object Browser: 
Contact: Please contact lixu1@vt.edu.
 *********************************************************/
#include "copasi.h"
#include "ObjectBrowser.h"
#include "ObjectBrowserItem.h"
#include "copasiui3window.h"

#include <qmessagebox.h>
#include <qvariant.h>
#include <qheader.h>
#include <qlistview.h>
#include <qtextedit.h>
#include <qlistbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qsimplerichtext.h>

#include "./icons/objectAll.xpm"
#include "./icons/objectParts.xpm"
#include "./icons/objectNone.xpm"

#include "report/CCopasiObject.h"
#include "report/CCopasiObjectName.h"
#include "report/CCopasiContainer.h"
#include "utilities/CCopasiVector.h"

QPixmap *pObjectAll = 0;   // to store the image of locked icon folder
QPixmap *pObjectParts = 0;   // to store the image of closed icon folder
QPixmap *pObjectNone = 0;     // to store the image of open icon folder

/*
 *  Constructs a ObjectBrowser which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ObjectBrowser::ObjectBrowser(QWidget* parent, const char* name, WFlags fl)
    : QDialog(NULL, name, parent == NULL, fl)
{
  if (!name)
    setName("ObjectBrowser");
  resize(420, 460);
  setCaption(trUtf8("Object Browser"));
  ObjectBrowserLayout = new QGridLayout(this, 1, 1, 11, 6, "ObjectBrowserLayout");

  ObjectListView = new QListView(this, "ObjectListView");
  ObjectListView->addColumn(trUtf8("Object Browser"));
  ObjectListView->header()->setClickEnabled(FALSE, ObjectListView->header()->count() - 1);
  ObjectListView->setAcceptDrops(FALSE);
  ObjectListView->setResizeMode(QListView::LastColumn);
  ObjectListView->setTreeStepSize(19);

  ObjectItemText = new QTextEdit(this, "ObjectItemText");
  ObjectItemText ->hide();

  ObjectBrowserLayout->addMultiCellWidget(ObjectListView, 0, 0, 0, 3);
  ObjectBrowserLayout->addMultiCellWidget(ObjectItemText, 0, 0, 0, 3);

  Line1 = new QFrame(this, "Line1");
  Line1->setFrameShape(QFrame::HLine);
  Line1->setFrameShadow(QFrame::Sunken);
  Line1->setFrameShape(QFrame::HLine);

  ObjectBrowserLayout->addMultiCellWidget(Line1, 1, 1, 0, 3);

  cancelButton = new QPushButton(this, "cancelButton");
  cancelButton->setText(trUtf8("Cancel"));

  if (parent)
    ObjectBrowserLayout->addWidget(cancelButton, 2, 0);
  else
    ObjectBrowserLayout->addWidget(cancelButton, 2, 2);

  nextButton = new QPushButton(this, "nextButton");
  if (parent)
    nextButton->setText(trUtf8("Next >"));
  else
    nextButton->setText(trUtf8("OK"));

  ObjectBrowserLayout->addWidget(nextButton, 2, 3);

  if (parent)
    {
      backButton = new QPushButton(this, "backButton");
      backButton->setText(trUtf8("< Back"));
      ObjectBrowserLayout->addWidget(backButton, 2, 2);
      QSpacerItem* spacer = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);
      ObjectBrowserLayout->addItem(spacer, 2, 1);
    }

  // tab order
  setTabOrder(ObjectListView, cancelButton);
  if (parent)
    {
      setTabOrder(cancelButton, backButton);
      setTabOrder(backButton, nextButton);
    }
  else
    setTabOrder(cancelButton, nextButton);

  pObjectAll = new QPixmap((const char**)ptrObjectAll);
  pObjectNone = new QPixmap((const char**)ptrObjectNone);
  pObjectParts = new QPixmap((const char**)ptrObjectParts);

  // signals and slots connections
  if (parent)
    connect(backButton, SIGNAL(clicked()), this, SLOT(backClicked()));
  connect(nextButton, SIGNAL(clicked()), this, SLOT(nextClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
  connect(ObjectListView, SIGNAL(clicked(QListViewItem*)), this, SLOT(listviewChecked(QListViewItem*)));

  mparent = (CopasiUI3Window*)parent;
  if (mparent)
    mparent->disable_object_browser_menu();

  objectItemList = new ObjectList();
  refreshList = new ObjectList();
  ObjectBrowserItem::resetKeySpace();
  loadData();
  currentPage = LISTVIEWPAGE;
  mOutputObjectVector = NULL;
}

/*
 *  Destroys the object and frees any allocated resources
 */
void ObjectBrowser::closeEvent (QCloseEvent * e)
{
  QWidget::closeEvent(e);
  if (mparent)
    {
      //if not a model dialog, it shall incur this function, when close
      // it shall enable the browser menu
      mparent->enabled_object_browser_menu();
      mOutputObjectVector = NULL;
      mparent = NULL;
      cleanup();
    }
}

ObjectBrowser::~ObjectBrowser()
{
  cleanup();
}

void ObjectBrowser::cleanup()
{
  pdelete(objectItemList);
  pdelete(refreshList);
  // no need to delete child widgets, Qt does it all for us
}

void ObjectBrowser::cancelClicked()
{
  close();
  qWarning("ObjectBrowser::cancelClicked(): Not implemented yet!");
}

void ObjectBrowser::listviewChecked(QListViewItem* pCurrent)
{
  if (pCurrent == NULL)
    return;
  clickToReverseCheck((ObjectBrowserItem*)pCurrent);
  updateUI();
  //loadUI();
}

void ObjectBrowser::clickToReverseCheck(ObjectBrowserItem* pCurrent)
{
  refreshList->insert(pCurrent);

  ObjectBrowserItem* pTmp = pCurrent;
  while (pTmp->parent() != NULL)
    {
      pTmp = pTmp->parent();
      refreshList->insert(pTmp);
    }

  if (pCurrent->isChecked() == ALLCHECKED)
    {
      if (pCurrent->isChecked())
        pCurrent->reverseChecked();
      setUncheck(pCurrent->child());
      return;
    }
  //else no check or partly checked
  if (!pCurrent->isChecked())
    pCurrent->reverseChecked();
  setCheck(pCurrent->child());
  return;
}

void ObjectBrowser::setUncheck(ObjectBrowserItem* pCurrent)
{
  if (pCurrent == NULL)
    return;

  refreshList->insert(pCurrent);

  if (pCurrent->isChecked())
    pCurrent->reverseChecked();

  if (pCurrent->child() != NULL)
    setUncheck(pCurrent->child());

  if (pCurrent->sibling() != NULL)
    setUncheck(pCurrent->sibling());
}

void ObjectBrowser::setCheck(ObjectBrowserItem* pCurrent)
{
  if (pCurrent == NULL)
    return;
  refreshList->insert(pCurrent);

  if (!pCurrent->isChecked())
    pCurrent->reverseChecked();

  if (pCurrent->child() != NULL)
    setCheck(pCurrent->child());

  if (pCurrent->sibling() != NULL)
    setCheck(pCurrent->sibling());
}

void ObjectBrowser::backClicked()
{
  switch (currentPage)
    {
    case LISTVIEWPAGE:
      //last page
      break;
    case SELECTEDITEMPAGE:
      currentPage = LISTVIEWPAGE;
      ObjectListView->show();
      ObjectItemText->hide();
      break;
    }
}

//need to delete the list outside the funciton
/*
ObjectList* ObjectBrowser::outputList()
{
  ObjectList* outputList;
  ObjectBrowserItem* rootItem;
  if (object
  rootItem = objectItemList->getRoot()->pItem;
  outputList = new ObjectList();
  eXport(rootItem, outputList);
  if (outputList->len() <= 0)
    {
      delete outputList;
      return NULL;
    }
  else
    return outputList;
}
 */

void ObjectBrowser::setOutputVector(std::vector<CCopasiObject*>* pObjectVector)
{
  mOutputObjectVector = pObjectVector;
}

void ObjectBrowser::nextClicked()
{
  if (!mparent)
    {
      ObjectBrowserItem* rootItem;
      rootItem = objectItemList->getRoot()->pItem;
      eXport(rootItem, mOutputObjectVector);
      mOutputObjectVector = NULL;
      cleanup();
      QDialog::done(QDialog::Accepted);
      return;
    }

  std::vector<CCopasiObject*>* outputVector;
  ObjectBrowserItem* rootItem;
  int i;
  switch (currentPage)
    {
    case LISTVIEWPAGE:
      ObjectListView->hide(); //last page
      ObjectItemText->show();
      rootItem = objectItemList->getRoot()->pItem;
      outputVector = new std::vector<CCopasiObject*>();
      eXport(rootItem, outputVector);
      //      QMessageBox::information(this, "Output object list done!", "Selected CopasiObject list done!");
      //   ObjectListItem* pHead;
      ObjectItemText->clear();

      for (i = 0; i < outputVector->size(); i++)
        {
          if (double(i) / 2 == int(i / 2))
            ObjectItemText->setColor(red);
          else
            ObjectItemText->setColor(blue);
          if ((*outputVector)[i])
            {
              //ObjectItemText->insertParagraph(pHead->pItem->getObject()->pCopasiObject->getCN().c_str(), -1);
              ObjectItemText->insertParagraph((*outputVector)[i]->getObjectType().c_str(), -1);
            }
        }
      /*
            for (pHead = outputVector->getRoot(), i = 1; pHead != NULL; pHead = pHead->pNext)
              {
                if (double(i) / 2 == int(i / 2))
                  ObjectItemText->setColor(red);
                else
                  ObjectItemText->setColor(blue);
                if (pHead->pItem->getObject()->pCopasiObject)
                  {
                    //ObjectItemText->insertParagraph(pHead->pItem->getObject()->pCopasiObject->getCN().c_str(), -1);
                    ObjectItemText->insertParagraph(pHead->pItem->getObject()->pCopasiObject->getObjectType().c_str(), -1);
                    i++;
                  }
              }
      */
      pdelete(outputVector);
      currentPage = SELECTEDITEMPAGE;
      break;
    case SELECTEDITEMPAGE:
      // show();
      // ->hide();
      break;
    }
}

void ObjectBrowser::eXport(ObjectBrowserItem* pCurrent, std::vector<CCopasiObject*>* outputVector)
{
  if (pCurrent->child())
    {
      ObjectBrowserItem* pChild = pCurrent->child();
      for (; pChild != NULL; pChild = pChild->sibling())
        if (pChild->getType() != FIELDATTR)
          eXport(pChild, outputVector);
    }
  else //it has no child
    {
      if (pCurrent->isChecked() && (pCurrent->getType() != FIELDATTR))
        {
          if (pCurrent->getObject())
            //   ObjectBrowserItem* pCopyCurrent = new ObjectBrowserItem((ObjectBrowserItem*)(NULL), 0, pCurrent->getObject()->pCopasiObject,outputList);
            outputVector->push_back(pCurrent->getObject()->pCopasiObject);
        }
      // else skip current item
    }
}

void swap(int first_pos, int second_pos, ObjectBrowserItem** array)
{
  ObjectBrowserItem* tmp = array[first_pos];
  array[first_pos] = array[second_pos];
  array[second_pos] = tmp;
}

int partition(int split_pos, int start_pos, int end_pos, ObjectBrowserItem** quick_sort_array)
{
  void* tmp = quick_sort_array[split_pos]->getObject()->pCopasiObject;
  if (split_pos != start_pos)
    swap(split_pos, start_pos, quick_sort_array);
  split_pos = start_pos;
  end_pos++;
  while (start_pos < end_pos)
    {
      while ((++start_pos < end_pos) && (quick_sort_array[start_pos]->getObject()->pCopasiObject <= tmp));

      while ((--end_pos > start_pos) && (quick_sort_array[end_pos]->getObject()->pCopasiObject > tmp));

      if (start_pos < end_pos)
        swap(start_pos, end_pos, quick_sort_array);
      else
        break;
    }
  start_pos--;
  if (split_pos != start_pos)
    swap(split_pos, start_pos, quick_sort_array);
  return start_pos;
}

void quick_sort(int m, int n, ObjectBrowserItem** quick_sort_array)
{
  if (m < n)
    {
      int medium = (m + n) / 2;
      medium = partition(medium, m, n, quick_sort_array);
      if (m < medium - 1)
        quick_sort(m, medium - 1, quick_sort_array);
      if (medium + 1 < n)
        quick_sort(medium + 1, n, quick_sort_array);
    }
}

void ObjectBrowser::loadData()
{
  CCopasiContainer * root = CCopasiContainer::Root;
  ObjectBrowserItem * itemRoot = new ObjectBrowserItem(ObjectListView, NULL, root, objectItemList);
  itemRoot->attachKey();
  itemRoot->setObjectType(CONTAINERATTR);
  itemRoot->setText(0, root->getName().c_str());
  itemRoot->setOpen(true);
  loadChild(itemRoot, root, true);
  removeDuplicate(objectItemList);
  loadUI();
}

void ObjectBrowser::removeDuplicate(ObjectList* objectItemList)
{
  int length = objectItemList->len();
  ObjectBrowserItem** bufferVector = new ObjectBrowserItem * [length];

  // copy out the list
  ObjectListItem* pCurrent = objectItemList->getRoot();
  for (int i = 0; i < length; i++)
    {
      bufferVector[i] = pCurrent->pItem;
      pCurrent = pCurrent->pNext;
    }
  // sort list according to CCopasiObject
  quick_sort(0, length - 1, bufferVector);

  int index;
  CBrowserObject* pBrowserObject = NULL;
  ObjectBrowserItem* pBrowserItem = NULL;

  for (index = 0; (index < length) && (!bufferVector[index]->getObject()->pCopasiObject); index++);

  pBrowserObject = bufferVector[index++]->getObject();

  for (; index < length; index++)
    {
      if (bufferVector[index]->getObject()->pCopasiObject == pBrowserObject->pCopasiObject) //duplicate point
        {
          pBrowserItem = bufferVector[index]->getObject()->referenceList->pop();
          pBrowserObject->referenceList->insert(pBrowserItem);
          pBrowserItem->setBrowserObject(pBrowserObject);
        }
      else
        pBrowserObject = bufferVector[index]->getObject();
    }
}

void ObjectBrowser::loadChild(ObjectBrowserItem* parent,
                              CCopasiContainer* copaParent, bool nField)
{
  ObjectBrowserItem* last = NULL;
  CCopasiObject* current = NULL;

  ObjectList* childStack = new ObjectList();

  const CCopasiContainer::objectMap * pObjectList = & copaParent->getObjects();
  CCopasiContainer::objectMap::const_iterator it = pObjectList->begin();
  CCopasiContainer::objectMap::const_iterator end = pObjectList->end();

  while (it != end)
    {
      current = it->second;
      ObjectBrowserItem* currentItem = new ObjectBrowserItem(parent, last, current, objectItemList);
      last = currentItem;
      currentItem->setText(0, current->getObjectName().c_str());
      if (current->isContainer())
        {
          currentItem->setObjectType(CONTAINERATTR);
          currentItem->attachKey();
          if (!current->isVector())
            loadChild(currentItem, (CCopasiContainer*) current, nField);
          else
            {
              ObjectBrowserItem* objectChild = currentItem;
              if (nField) // divide into attribute and object lists
                {
                  loadChild(objectChild, (CCopasiContainer *) current, false);
                  objectChild->attachKey();

                  /* this change is due to the poor performance of loadField
                  * to change replace the part inside the if(nField) with the following statements

                  objectChild = new ObjectBrowserItem(currentItem, NULL, NULL, objectItemList);
                  objectChild->setObjectType(OBJECTATTR);
                  objectChild->setText(0, "Object list");
                  loadChild(objectChild, (CCopasiContainer *) current, false);
                  ObjectBrowserItem* fieldChild = new ObjectBrowserItem(currentItem, objectChild, NULL, objectItemList);
                  fieldChild->setObjectType(FIELDATTR);
                  fieldChild->setText(0, "Attribute list");
                  loadField(fieldChild, (CCopasiContainer*) current);
                  fieldChild->attachKey();
                  objectChild->attachKey();
                  * end of change */
                }
              else
                loadChild(objectChild, (CCopasiContainer *) current, nField);
            }
        }
      else
        {
          currentItem->setObjectType(OBJECTATTR);
          childStack->insert(currentItem);  //attach the key later
        }

      it++;
    }

  ObjectBrowserItem* pCurrent;
  while (childStack->len() > 0)
    {
      pCurrent = childStack->pop();
      pCurrent->attachKey();
    }
}

void ObjectBrowser::loadField(ObjectBrowserItem* parent, CCopasiContainer * copaParent)
{
  ObjectBrowserItem* lastField = NULL;
  CCopasiObject* currentField = NULL;
  ObjectBrowserItem* last = NULL;
  CCopasiObject* current = NULL;

  const CCopasiContainer::objectMap * pObjectList = & copaParent->getObjects();
  CCopasiContainer::objectMap::const_iterator it = pObjectList->begin();
  CCopasiContainer::objectMap::const_iterator end = pObjectList->end();
  CCopasiContainer::objectMap::const_iterator pFirstObject = it;

  if (it == end) return; //empty list

  while (it != end) // find all missing reference attribute
    {
      currentField = it->second;
      if (!currentField->isContainer())
        {
          ObjectBrowserItem* currentItemField = new ObjectBrowserItem(parent, lastField, currentField, objectItemList);
          currentItemField->attachKey();
          currentItemField->setObjectType(FIELDATTR);
          currentItemField->setText(0, currentField->getObjectName().c_str());
          lastField = currentItemField;
        }
      it++;
    }

  it = pFirstObject; //reset to the beginning
  while (it != end)
    {
      if (it->second->isContainer())
        break;
      it++;
    }

  if (it == end) return; //no container found

  const CCopasiContainer::objectMap * pFieldList =
    &(((CCopasiContainer *) it->second)->getObjects());

  CCopasiContainer::objectMap::const_iterator fieldIt = pFieldList->begin();
  CCopasiContainer::objectMap::const_iterator fieldEnd = pFieldList->end();

  while (fieldIt != fieldEnd)
    {
      currentField = fieldIt->second;
      ObjectBrowserItem* currentItemField = new ObjectBrowserItem(parent, lastField, NULL, objectItemList);
      currentItemField->attachKey();
      currentItemField->setObjectType(FIELDATTR);
      currentItemField->setText(0, currentField->getObjectName().c_str());
      lastField = currentItemField;
      it = pFirstObject;
      last = NULL;

      while (it != end)
        {
          CCopasiObject* pSubField;
          current = it->second;

          if (current->isContainer())
            pSubField =
              getFieldCopasiObject((CCopasiContainer *) current,
                                   currentField->getObjectName().c_str());
          else
            pSubField = NULL; // this shall be an exception error

          ObjectBrowserItem* currentItem = new ObjectBrowserItem(currentItemField, last, pSubField, objectItemList);
          currentItem->setText(0, current->getObjectName().c_str());
          currentItem->setObjectType(FIELDATTR);
          currentItem->attachKey();

          if (pSubField)
            if (pSubField->isContainer()) //container field recursively to find all possible items
              {
                loadChild(currentItem, (CCopasiContainer *)pSubField, false); // wont show the attribute and field list
              }

          last = currentItem;
          it++;
        }
      fieldIt++;
    }
}

void ObjectBrowser::updateUI()
{
  //refresh List stores all affected items,

  refreshList->createBucketIndex(objectItemList->len()); //construct index to do binary search
  for (ObjectListItem* pCurrent = refreshList->getRoot(); pCurrent != NULL; pCurrent = pCurrent->pNext)
    {
      ObjectListItem * pHead = pCurrent->pItem->getObject()->referenceList->getRoot();
      while (pHead != NULL)
        {
          ObjectBrowserItem * pCurrentLevel = pHead->pItem;
          if (pCurrent != pHead)
            for (; (pCurrentLevel != NULL); pCurrentLevel = pCurrentLevel->parent())
              refreshList->insertBucket(pCurrentLevel);
          pHead = pHead->pNext;
        }
    }

  int cursor = 0;
  for (ObjectBrowserItem* pUpdate = refreshList->bucketPop(cursor); pUpdate != NULL; pUpdate = refreshList->bucketPop(cursor))
    setCheckMark(pUpdate);

  refreshList->destroyBucket();
}

void ObjectBrowser::setCheckMark(ObjectBrowserItem* pCurrent)
{
  switch (pCurrent->nUserChecked())
    {
    case NOCHECKED:
      pCurrent->setPixmap(0, *pObjectNone);
      break;
    case ALLCHECKED:
      pCurrent->setPixmap(0, *pObjectAll);
      break;
    case PARTCHECKED:
      pCurrent->setPixmap(0, *pObjectParts);
      break;
    }
}

void ObjectBrowser::loadUI()
{
  ObjectListItem* pCurrent = objectItemList->getRoot();
  setCheckMark(pCurrent->pItem);
  for (; pCurrent != NULL; pCurrent = pCurrent->pNext)
    setCheckMark(pCurrent->pItem);
}

CCopasiObject* ObjectBrowser::getFieldCopasiObject(CCopasiContainer * pCurrent, const char* name)
{
  const CCopasiContainer::objectMap * pObjectList = & pCurrent->getObjects();
  CCopasiContainer::objectMap::const_iterator it = pObjectList->begin();
  CCopasiContainer::objectMap::const_iterator end = pObjectList->end();

  /*
    if (it != end)
      return it->second;
    else
      return NULL;
  */

  //#ifdef XXXX
  //  std::map< const std::string, CCopasiObject *>::const_iterator it = pObjectList->begin();
  //  std::map< const std::string, CCopasiObject *>::const_iterator end = pObjectList->end();

  CCopasiObject* pResult;
  while (it != end)
    {
      if (it->second->isContainer())
        {
          pResult = getFieldCopasiObject((CCopasiContainer *)it->second, name);
          if (pResult)
            return pResult;
        }
      if (QString(it->second->getObjectName().c_str()) == name)
        return it->second;
      it++;
    }

  return NULL;
  //#endif // XXXX
}
