/********************************************************
   Author: Liang Xu
   Version : 1.xx  <first>
   Description: 
   Date: 04/03 
   Comment : Copasi Object Browser including:

  browserObject: A complex structure uiniquely map to a CopasiObject
  ObjectBrowserItem: A wraper to a broserObject, 
      there may exist multiply wrappers to one browserObject
  objectListItem
  objectList: A queue for all element: 
     The reason I dont use std:vector is
     for efficiency requirement for all 
     object browser item update
   Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#include "ObjectBrowserItem.h"

#include "report/CCopasiObject.h"
#include "report/CCopasiObjectName.h"
#include "report/CCopasiContainer.h"
#include "utilities/CCopasiVector.h"

long ObjectBrowserItem::KeySpace = 100000000;

browserObject::browserObject()
{
  referenceList = new objectList();
}

browserObject::~browserObject()
{
  delete referenceList;
}

ObjectBrowserItem::ObjectBrowserItem (QListView * parent, ObjectBrowserItem * after, CCopasiObject* mObject, objectList* pList)
    : QListViewItem(parent, after)
{
  //here is the ROOT
  setParent(NULL);
  setSibling(NULL);
  setChild(NULL);
  if (after != NULL)
    after->setSibling(this);

  if (mObject != NULL)
    {
      objectListItem* pTmp = pList->getRoot();
      while (pTmp != NULL)
        {
          if (pTmp->pItem->getObject()->pCopasiObject == mObject) // already be pointed in the list
            break;
          pTmp = pTmp->pNext;
        }
      if (pTmp && pTmp->pItem->getObject()->pCopasiObject == mObject) //exist already in list
        {
          pBrowserObject = pTmp->pItem->getObject();
          setChild(pTmp->pItem->child());
          //pBrowserObject->nRefer++;
          pBrowserObject->referenceList->insert(this);
        }
      else
        {
          browserObject* newBrowserObject = new browserObject();
          newBrowserObject->pCopasiObject = mObject;
          newBrowserObject->mChecked = false;
          //newBrowserObject->nRefer=1;
          pBrowserObject = newBrowserObject;
          pBrowserObject->referenceList->insert(this);
        }
    }
  else //this is not an ending node
    {
      browserObject* newBrowserObject = new browserObject();
      newBrowserObject->pCopasiObject = mObject;
      newBrowserObject->mChecked = false;
      //newBrowserObject->nRefer=1;
      pBrowserObject = newBrowserObject;
      pBrowserObject->referenceList->insert(this);
    }
  pList->insert(this);

  mKey = " ";
}

ObjectBrowserItem::ObjectBrowserItem (ObjectBrowserItem * parent, ObjectBrowserItem * after , CCopasiObject* mObject, objectList* pList)
    : QListViewItem(parent, after)
{
  setParent(parent);
  setSibling(NULL);
  setChild(NULL);
  if (parent && !parent->child())
    parent->setChild(this);
  if (after != NULL)
    after->setSibling(this);
  if (mObject != NULL)
    {
      objectListItem* pTmp = pList->getRoot();
      while (pTmp != NULL)
        {
          if (pTmp->pItem->getObject()->pCopasiObject == mObject)
            break;
          pTmp = pTmp->pNext;
        }
      if (pTmp && pTmp->pItem->getObject()->pCopasiObject == mObject) //exist already in list
        {
          pBrowserObject = pTmp->pItem->getObject();
          setChild(pTmp->pItem->child());
          //pBrowserObject->nRefer++;
          pBrowserObject->referenceList->insert(this);
        }
      else
        {
          browserObject* newBrowserObject = new browserObject();
          newBrowserObject->pCopasiObject = mObject;
          //newBrowserObject->nRefer=1;
          newBrowserObject->mChecked = false;
          pBrowserObject = newBrowserObject;
          pBrowserObject->referenceList->insert(this);
        }
    }
  else //this is not an ending node
    {
      browserObject* newBrowserObject = new browserObject();
      newBrowserObject->pCopasiObject = mObject;
      newBrowserObject->mChecked = false;
      //newBrowserObject->nRefer=1;
      pBrowserObject = newBrowserObject;
      pBrowserObject->referenceList->insert(this);
    }
  pList->insert(this);

  mKey = " ";
}

void ObjectBrowserItem::attachKey()
{
  mKey = QString::number(KeySpace++);
}

int ObjectBrowserItem::nUserChecked()
{
  int condition;
  if (child())
    {
      ObjectBrowserItem* pChild = child();
      condition = pChild->nUserChecked();

      for (; pChild != NULL; pChild = pChild->sibling())
        {
          switch (pChild->nUserChecked())
            {
            case ALLCHECKED:
              if (condition == NOCHECKED)
                condition = PARTCHECKED;
              break;
            case PARTCHECKED:
              if (condition == NOCHECKED || condition == ALLCHECKED)
                condition = PARTCHECKED;
              break;
            case NOCHECKED:
              if (condition == ALLCHECKED)
                condition = PARTCHECKED;
              break;
            }
        }
    }
  else //it has no child
    {
      if (isChecked())
        condition = ALLCHECKED;
      else
        condition = NOCHECKED;
    }
  return condition;
}

void ObjectBrowserItem::setParent(ObjectBrowserItem* parent)
{
  pParent = parent;
}

void ObjectBrowserItem::setChild(ObjectBrowserItem* child)
{
  pChild = child;
}

void ObjectBrowserItem::setSibling(ObjectBrowserItem* sibling)
{
  pSibling = sibling;
}

ObjectBrowserItem* ObjectBrowserItem::parent() const
  {
    return pParent;
  }

ObjectBrowserItem* ObjectBrowserItem::child() const
  {
    return pChild;
  }

ObjectBrowserItem* ObjectBrowserItem::sibling() const
  {
    return pSibling;
  }

bool ObjectBrowserItem::isChecked() const
  {
    return pBrowserObject->mChecked;
  }

void ObjectBrowserItem::reverseChecked()
{
  pBrowserObject->mChecked = !pBrowserObject->mChecked;
}

objectList::objectList()
{
  root = NULL;
  length = 0;
}

void objectList::insert(ObjectBrowserItem* pItem)
{
  int i = 0;
  objectListItem* pNewItem = new objectListItem(pItem, NULL, NULL);
  if (length == 0)
    {
      root = pNewItem;
      length++;
      return;
    }
  objectListItem* pCurrent = root;
  for (; i < length - 1; i++)
    pCurrent = pCurrent->pNext;
  pCurrent->pNext = pNewItem;
  pNewItem->pLast = pCurrent;
  length++;
}

objectListItem* objectList::getRoot()
{
  return root;
}

ObjectBrowserItem* objectList::pop()
{
  if (length == 0) return NULL;
  ObjectBrowserItem* returnValue = root->pItem;
  objectListItem* delNode = root;
  root = root->pNext;
  length--;
  delete delNode;
  return returnValue;
}

void objectList::delDuplicate()
{
  objectListItem* objectLast = getRoot();
  objectListItem* objectNext = objectLast->pNext;
  for (; objectNext != NULL; objectNext = objectNext->pNext)
    {
      if (objectLast->pItem->key(0, 0) == objectNext->pItem->key(0, 0)) //delete the current item
        {
          objectLast->pNext = objectNext->pNext;
          objectNext->pNext->pLast = objectLast;
          delete objectNext;
          length--;
          objectNext = objectLast;
        }
      else // objectLast.key<objectNext.Key
        objectLast = objectNext; //next step
    }
}

void objectList::sortList()
{
  if (len() <= 1) //sorted
    return;
  objectListItem* pHead = getRoot();
  objectListItem* pTail = pHead->pNext;
  for (; pHead->pNext != NULL; pHead = pHead->pNext)
    {
      for (pTail = pHead->pNext; pTail != NULL; pTail = pTail->pNext)
        if (pHead->pItem->key(0, 0) > pTail->pItem->key(0, 0))
          {
            ObjectBrowserItem * pTmp = pHead->pItem;
            pHead->pItem = pTail->pItem;
            pTail->pItem = pTmp;
          }
    }
}

//please do call createQuickIndex() first
bool objectList::sortListInsert(ObjectBrowserItem* pItem) //insert and keep the sort order
{
  if (pItem->key(0, 0) < getRoot()->pItem->key(0, 0)) //insert at the front
    {
      objectListItem* pNewItem = new objectListItem(pItem, root, NULL);
      root->pLast = pNewItem;
      root = pNewItem;
      length++;
      return true;
    }

  int begin = 0;
  int end = index_length;
  int comp;

  objectListItem* pHead;

  if (pItem->key(0, 0) < quickIndex[begin].mKey)
    pHead = quickIndex[begin].mIndex;
  else
    if (pItem->key(0, 0) > quickIndex[end].mKey)
      pHead = quickIndex[end].mIndex;
    else //do binary search
      {
        while (end - begin > 1)
          {
            comp = (end + begin) / 2;
            if (pItem->key(0, 0) < quickIndex[comp].mKey) //first half
              end = comp;
            else
              begin = comp;
          }
        pHead = quickIndex[begin].mIndex;
      }

  for (; (pHead != NULL) && (pItem->key(0, 0) > pHead->pItem->key(0, 0)); pHead = pHead->pNext)
;

  if (pHead && (pHead->pItem->key(0, 0) == pItem->key(0, 0))) //duplicate key
    return false;
  //else insert

  if (pHead == NULL) //insert at the end of the list
    {
      insert(pItem);
      return true;
    }

  length++;
  objectListItem* pNewItem = new objectListItem(pItem, pHead, pHead->pLast);
  pHead->pLast = pNewItem;
  pNewItem->pLast->pNext = pNewItem;
  return true;
}

void objectList::createQuickIndex()
{
  int step_size = int (len() / INDEXLENGTH) + 1;
  index_length = 0;

  for (objectListItem* pHead = getRoot(); pHead != NULL;)
    {
      quickIndex[index_length].mIndex = pHead;
      quickIndex[index_length].mKey = pHead->pItem->key(0, 0);
      for (int i = 0; i < step_size; i++)
        {
          if (pHead == NULL)
            break;
          pHead = pHead->pNext;
        }
      index_length++;
    }
  index_length--;
}
