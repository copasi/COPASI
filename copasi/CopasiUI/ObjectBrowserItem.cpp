#include "ObjectBrowserItem.h"

ObjectBrowserItem::ObjectBrowserItem (QListView * parent, ObjectBrowserItem * after, CCopasiObject* mObject)
    : QListViewItem(parent, after)
{
  //here is the ROOT
  setParent(NULL);
  setSibling(NULL);
  setChild(NULL);
  if (after != NULL)
    after->setSibling(this);
  pCopasiObject = mObject;
  mChecked = false;
}

ObjectBrowserItem::ObjectBrowserItem (ObjectBrowserItem * parent, ObjectBrowserItem * after , CCopasiObject* mObject)
    : QListViewItem(parent, after)
{
  setParent(parent);
  setSibling(NULL);
  setChild(NULL);
  if (parent != NULL)
    parent->setChild(this);
  if (after != NULL)
    after->setSibling(this);
  pCopasiObject = mObject;
  mChecked = false;
}

int ObjectBrowserItem::UserChecked()
{
  int condition;
  if (isChecked())
    condition = ALLCHECKED;
  else
    condition = NOCHECKED;

  if (sibling() != NULL)
    {
      switch (sibling()->UserChecked())
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
  if (child() != NULL)
    {
      switch (child()->UserChecked())
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

ObjectBrowserItem::setParent(ObjectBrowserItem* parent)
{
  pParent = parent;
}

ObjectBrowserItem::setChild(ObjectBrowserItem* child)
{
  pChild = child;
}

ObjectBrowserItem::setSibling(ObjectBrowserItem* sibling)
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
    return mChecked;
  }

void ObjectBrowserItem::reverseChecked()
{
  mChecked = !mChecked;
}
