#include "ObjectBrowserItem.h"

ObjectBrowserItem::ObjectBrowserItem (QListView * parent, ObjectBrowserItem * after, CCopasiObject* mObject)
    : QListViewItem(parent, after)
{
  //here is the ROOT
  setParent(NULL);
  setBrother(NULL);
  setChild(NULL);
  if (after != NULL)
    after->setBrother(this);
  pCopasiObject = mObject;
}

ObjectBrowserItem::ObjectBrowserItem (ObjectBrowserItem * parent, ObjectBrowserItem * after , CCopasiObject* mObject)
    : QListViewItem(parent, after)
{
  setParent(parent);
  setBrother(NULL);
  setChild(NULL);
  if (parent != NULL)
    parent->setChild(this);
  if (after != NULL)
    after->setBrother(this);
  pCopasiObject = mObject;
}

ObjectBrowserItem::setParent(ObjectBrowserItem* parent)
{
  pParent = parent;
}

ObjectBrowserItem::setChild(ObjectBrowserItem* child)
{
  pChild = child;
}

ObjectBrowserItem::setBrother(ObjectBrowserItem* brother)
{
  pBrother = brother;
}

ObjectBrowserItem* ObjectBrowserItem::parent() const
  {
    return pParent;
  }

ObjectBrowserItem* ObjectBrowserItem::child() const
  {
    return pChild;
  }

ObjectBrowserItem* ObjectBrowserItem::brother() const
  {
    return pBrother;
  }
