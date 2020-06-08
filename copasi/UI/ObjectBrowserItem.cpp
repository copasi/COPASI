// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description:
Date: 04/03
Comment : Copasi Object Browser including:

CBrowserObject: A complex structure uiniquely map to a CopasiObject
ObjectBrowserItem: A wraper to a broserObject,
there may exist multiply wrappers to one CBrowserObject
ObjectListItem
ObjectList: A queue for all element:
The reason I dont use std:vector is
for efficiency requirement for all
object browser item update
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#include <QTreeWidget>
#include "ObjectBrowserItem.h"

#include "copasi/core/CDataObject.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/core/CDataVector.h"

long ObjectBrowserItem::KeySpace = KEYBASE;

CBrowserObject::CBrowserObject():
  pCopasiObject(NULL),
  mChecked(false),
  referenceList(NULL)  //keep pointer to all its referenced items for later update
{
  referenceList = new ObjectList();
}

CBrowserObject::~CBrowserObject()
{
  ObjectListItem* currentItem = referenceList->getRoot();

  for (; currentItem != NULL; currentItem = currentItem->pNext)
    currentItem->pItem->setBrowserObject(NULL);

  pdelete(referenceList);
}

/**
 *   Constructs a new ObjectBrowserItem
 */
ObjectBrowserItem::ObjectBrowserItem(QTreeWidget * parent, ObjectBrowserItem * after, const CDataObject* mObject, ObjectList* pList)
  : QTreeWidgetItem(parent, after)
  , pBrowserObject(NULL)
  , mType(FIELDATTR)
  , mKey()
{
  if (mObject != NULL)
    {
      /* To change
      ObjectListItem* pTmp = pList->getRoot();
      while (pTmp != NULL)
        {
          if (pTmp->pItem->getObject()->pCopasiObject == mObject) // already be pointed in the list
            break;
          pTmp = pTmp->pNext;
        }
      if (pTmp && pTmp->pItem->getObject()->pCopasiObject == mObject) //exist already in list
        {
          pBrowserObject = pTmp->pItem->getObject();
          pBrowserObject->referenceList->insert(this);
        }
      else
         To change */
      {
        CBrowserObject* newBrowserObject = new CBrowserObject();
        newBrowserObject->pCopasiObject = mObject;
        newBrowserObject->mChecked = false;
        pBrowserObject = newBrowserObject;
        pBrowserObject->referenceList->insert(this);
      }
    }
  else //this is not an ending node
    {
      CBrowserObject* newBrowserObject = new CBrowserObject();
      newBrowserObject->pCopasiObject = mObject;
      newBrowserObject->mChecked = false;
      pBrowserObject = newBrowserObject;
      pBrowserObject->referenceList->insert(this);
    }

  if (pList)
    pList->insert(this);

  mKey = " ";
}

ObjectBrowserItem::ObjectBrowserItem(ObjectBrowserItem * parent, ObjectBrowserItem * after , const CDataObject* mObject, ObjectList* pList)
  : QTreeWidgetItem(parent, after)
  , pBrowserObject(NULL)
  , mType(FIELDATTR)
  , mKey()
{
  if (mObject != NULL)
    {
      /* To change
      ObjectListItem* pTmp = pList->getRoot();
      while (pTmp != NULL)
        {
          if (pTmp->pItem->getObject()->pCopasiObject == mObject)
            break;
          pTmp = pTmp->pNext;
        }
      if (pTmp && pTmp->pItem->getObject()->pCopasiObject == mObject) //exist already in list
        {
          pBrowserObject = pTmp->pItem->getObject();
          pBrowserObject->referenceList->insert(this);
        }
      else
         To change */
      {
        CBrowserObject* newBrowserObject = new CBrowserObject();
        newBrowserObject->pCopasiObject = mObject;
        newBrowserObject->mChecked = false;
        pBrowserObject = newBrowserObject;
        pBrowserObject->referenceList->insert(this);
      }
    }
  else //this is not an ending node
    {
      CBrowserObject* newBrowserObject = new CBrowserObject();
      newBrowserObject->pCopasiObject = mObject;
      newBrowserObject->mChecked = false;
      pBrowserObject = newBrowserObject;
      pBrowserObject->referenceList->insert(this);
    }

  if (pList)
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

  if (child(0))
    {
      ObjectBrowserItem* pChild = (ObjectBrowserItem *)child(0);
      condition = pChild->nUserChecked();

      for (; pChild != NULL; pChild = (ObjectBrowserItem *)pChild->nextSibling())
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

bool ObjectBrowserItem::isChecked() const
{
  return pBrowserObject->mChecked;
}

void ObjectBrowserItem::reverseChecked()
{
  pBrowserObject->mChecked = !pBrowserObject->mChecked;
}

QTreeWidgetItem* ObjectBrowserItem::nextSibling()
{
  if (this->parent() == NULL)
    return NULL;
  else
    {
      int indexOfThisChild = this->parent()->indexOfChild(this);

      if (this->parent()->child(indexOfThisChild + 1))
        return this->parent()->child(indexOfThisChild + 1);
    }

  return NULL;
}

ObjectList::ObjectList():
  quickIndex(NULL),
  pointerList(NULL),
  index_length(0),
  root(NULL),
  length(0)
{}

void ObjectList::insert(ObjectBrowserItem* pItem)
{
  int i = 0;
  ObjectListItem* pNewItem = new ObjectListItem(pItem, NULL, NULL);

  if (length == 0)
    {
      root = pNewItem;
      length++;
      return;
    }

  ObjectListItem* pCurrent = root;

  for (; i < length - 1; i++)
    pCurrent = pCurrent->pNext;

  pCurrent->pNext = pNewItem;
  pNewItem->pLast = pCurrent;
  length++;
}

ObjectListItem* ObjectList::getRoot()
{
  return root;
}

ObjectBrowserItem* ObjectList::pop()
{
  if (length == 0) return NULL;

  ObjectBrowserItem* returnValue = root->pItem;
  ObjectListItem* delNode = root;
  root = root->pNext;

  if (root)
    root->pLast = NULL;

  length--;
  pdelete(delNode);
  return returnValue;
}

/* Caution: ObjectList must be sorted already for this function to work */
void ObjectList::delDuplicate()
{
  ObjectListItem* objectLast = getRoot();
  ObjectListItem* objectNext = (objectLast != NULL) ? objectLast->pNext : NULL;

  for (; objectNext != NULL; objectNext = objectNext->pNext)
    {
      if (objectLast->pItem->key(0, 0) == objectNext->pItem->key(0, 0)) //delete the current item
        {
          objectLast->pNext = objectNext->pNext;

          if (objectNext->pNext) objectNext->pNext->pLast = objectLast;

          pdelete(objectNext);
          length--;
          objectNext = objectLast;
        }
      else // objectLast.key<objectNext.Key
        objectLast = objectNext; //next step
    }
}

void ObjectList::sortList()
{
  if (len() <= 1) //sorted
    return;

  ObjectListItem* pHead = getRoot();
  ObjectListItem* pTail = pHead->pNext;

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
bool ObjectList::sortListInsert(ObjectBrowserItem* pItem) //insert and keep the sort order
{
  if (getRoot() == NULL) //list is empty
    {
      ObjectListItem* pNewItem = new ObjectListItem(pItem, NULL, NULL);
      root = pNewItem;
      length++;
      return true;
    }

  if (pItem->key(0, 0) < getRoot()->pItem->key(0, 0)) //insert at the front
    {
      ObjectListItem* pNewItem = new ObjectListItem(pItem, root, NULL);
      root->pLast = pNewItem;
      root = pNewItem;
      length++;
      return true;
    }

  ObjectListItem* pHead = getRoot();

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
  ObjectListItem* pNewItem = new ObjectListItem(pItem, pHead, pHead->pLast);
  pHead->pLast = pNewItem;
  pNewItem->pLast->pNext = pNewItem;
  return true;
}

void ObjectList::createBucketIndex(int max)
{
  index_length = max;
  quickIndex = new bool[max];
  pointerList = new ObjectBrowserItem * [max];
  int i = 0;

  for (; i < max; i++)
    quickIndex[i] = false;

  int tmpIndex;
  ObjectListItem* pDel;

  for (ObjectListItem* pHead = getRoot(); pHead != NULL;)
    {
      tmpIndex = pHead->pItem->key(0, 0).toInt() - KEYBASE;

      if (quickIndex[tmpIndex]) //delete
        {
          pDel = pHead;

          if (pHead->pLast) pHead->pLast->pNext = pHead->pNext; else root = pHead->pNext;

          if (pHead->pNext)
            pHead->pNext->pLast = pHead->pLast;

          pHead = pHead->pNext;
          pdelete(pDel);
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

void ObjectList::insertBucket(ObjectBrowserItem* pItem)
{
  int tmpIndex = pItem->key(0, 0).toInt() - KEYBASE;
  quickIndex[tmpIndex] = true;
  pointerList[tmpIndex] = pItem;
}

ObjectBrowserItem* ObjectList::bucketPop(int& cursor)
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

void ObjectList::destroyBucket()
{
  delete[] quickIndex;
  delete[] pointerList;

  for (ObjectBrowserItem* pHead = pop(); pHead != NULL; pHead = pop());

  index_length = 0;
}
