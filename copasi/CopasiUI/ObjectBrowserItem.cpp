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
  mchecked = true;
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
  mchecked = true;
}

int ObjectBrowserItem::UserChecked(ObjectBrowserItem* pCurrent)
{
  int condition;
  if (pCurrent->isChecked())
    condition = ALLCHECKED;
  else
    condition = NOCHECKED;

  if (pCurrent->brother() != NULL)
    {
      switch (UserChecked(pCurrent->brother()))
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
  if (pCurrent->child() != NULL)
    {
      switch (UserChecked(pCurrent->child()))
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

bool ObjectBrowserItem::isChecked() const
  {
    return mchecked;
  }

void ObjectBrowserItem::reverseChecked()
{
  mchecked = !mchecked;
}
