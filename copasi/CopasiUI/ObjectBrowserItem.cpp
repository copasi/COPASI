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

long ObjectBrowserItem::KeySpace = KEYBASE;

browserObject::browserObject()
{
  referenceList = new objectList();
}

browserObject::~browserObject()
{
  // QT DELETE THIS POINTER
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
          pBrowserObject->referenceList->insert(this);
        }
      else
        {
          browserObject* newBrowserObject = new browserObject();
          newBrowserObject->pCopasiObject = mObject;
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
          pBrowserObject->referenceList->insert(this);
        }
      else
        {
          browserObject* newBrowserObject = new browserObject();
          newBrowserObject->pCopasiObject = mObject;
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
  index_length = 0;
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

  objectListItem* pHead = getRoot();
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

void objectList::createBucketIndex(int max)
{
  index_length = max;
  quickIndex = new bool[max];
  pointerList = new pObjectBrowserItem[max];
  int i = 0;
  for (; i < max; i++)
    quickIndex[i] = false;
  int tmpIndex;
  objectListItem* pDel;
  for (objectListItem* pHead = getRoot(); pHead != NULL;)
    {
      tmpIndex = pHead->pItem->key(0, 0).toInt() - KEYBASE;
      if (quickIndex[tmpIndex]) //delete
        {
          pDel = pHead;
          pHead->pLast->pNext = pHead->pNext;
          if (pHead->pNext)
            pHead->pNext->pLast = pHead->pLast;
          pHead = pHead->pNext;
          delete pDel;
          length--;
        }
      else //
        {
          quickIndex[tmpIndex] = true;
          pointerList[tmpIndex] = pHead->pItem;
          pHead = pHead->pNext;
        }
    }
}

void objectList::insertBucket(ObjectBrowserItem* pItem)
{
  int tmpIndex = pItem->key(0, 0).toInt() - KEYBASE;
  quickIndex[tmpIndex] = true;
  pointerList[tmpIndex] = pItem;
}

ObjectBrowserItem* objectList::bucketPop(int& cursor)
{
  for (; cursor < index_length; cursor++)
    if (quickIndex[cursor])
      {
        cursor++;
        return pointerList[cursor - 1];
      }
  //nothing avaiable in list
  return NULL;
}

void objectList::destroyBucket()
{
  delete[] quickIndex;
  delete[] pointerList;
  for (ObjectBrowserItem* pHead = pop(); pHead != NULL; pHead = pop());
  quickIndex = 0;
}
