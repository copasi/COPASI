#ifndef OBJECT_BROWSER_ITEM_H
#define OBJECT_BROWSER_ITEM_H

#include "qlistview.h"

class QListViewItem;
class QListView;
class CCopasiObject;

class ObjectBrowserItem : public QListViewItem
  {
  private:
    CCopasiObject* pCopasiObject;
    ObjectBrowserItem* pParent;
    ObjectBrowserItem* pChild;
    ObjectBrowserItem* pBrother;

  public:
    ObjectBrowserItem (QListView * parent, ObjectBrowserItem * after, CCopasiObject* mObject);
    ObjectBrowserItem (ObjectBrowserItem * parent, ObjectBrowserItem * after, CCopasiObject* mObject);
    ~ObjectBrowserItem() {}

    setParent(ObjectBrowserItem* parent);
    setChild(ObjectBrowserItem* child);
    setBrother(ObjectBrowserItem* brother);

    ObjectBrowserItem* parent() const;
    ObjectBrowserItem* child() const;
    ObjectBrowserItem* brother() const;
  };

#endif
