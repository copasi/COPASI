#include "ObjectBrowserItem.h"

long ObjectBrowserItem::KeySpace = 1;

ObjectBrowserItem::ObjectBrowserItem (QListView * parent, ObjectBrowserItem * after, CCopasiObject* mObject, objectList* pList)
    : QListViewItem(parent, after)
{
  //here is the ROOT
  setParent(NULL);
  setSibling(NULL);
  setChild(NULL);
  if (after != NULL)
    after->setSibling(this);
  pCopasiObject = mObject;
  pList->insert(this);

  nParam = 0;
  mChecked = new bool(false);
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
  pCopasiObject = mObject;
  pList->insert(this);

  nParam = 0;
  mChecked = new bool(false);
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
              if (condition == NOCHECKED)
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
      if (isChecked(0))
        condition = ALLCHECKED;
      else
        condition = NOCHECKED;
    }

  return condition;

  if (sibling() != NULL)
    {
      switch (sibling()->nUserChecked())
        {
        case ALLCHECKED:
          if (condition == NOCHECKED)
            condition = PARTCHECKED;
          break;
        case PARTCHECKED:
          if (condition == NOCHECKED)
            condition = PARTCHECKED;
          break;
        case NOCHECKED:
          if (condition == ALLCHECKED)
            condition = PARTCHECKED;
          break;
        }
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

bool ObjectBrowserItem::isChecked(unsigned int i) const
  {
    if (i > nParam)
      return mChecked[0];
    return mChecked[i];
  }

void ObjectBrowserItem::reverseChecked(unsigned int i)
{
  if (i > nParam)
    return;
  mChecked[i] = !mChecked[i];
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

objectListItem* objectList::pop()
{
  if (length == 0) return NULL;
  objectListItem* returnValue = root;
  root = root->pNext;
  length--;
  return returnValue;
}
