#include "QlistView.h"
#include "ObjectBrowserItem.h"

ObjectBrowserItem::ObjectBrowserItem (QListView * parent, ObjectBrowserItem * after)
{
  pListViewItem = new QListViewItem(parent, after->listviewitem());
}

ObjectBrowserItem::ObjectBrowserItem (ObjectBrowserItem * parent, ObjectBrowserItem * after)
{
  pListViewItem = new QListViewItem(parent->listviewitem(), after->listviewitem());
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

QListViewItem* ObjectBrowserItem::listviewitem() const
  {
    return pListViewItem;
  }
