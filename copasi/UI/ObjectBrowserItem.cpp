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
  objectListItem* pNewItem = new objectListItem(pItem, NULL);
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
