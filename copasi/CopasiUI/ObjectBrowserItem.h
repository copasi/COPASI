#ifndef OBJECT_BROWSER_ITEM_H
#define OBJECT_BROWSER_ITEM_H

#include "qlistview.h"

class QListViewItem;
class QListView;
class CCopasiObject;

#define NOCHECKED -1
#define ALLCHECKED 1
#define PARTCHECKED 0

class ObjectBrowserItem : public QListViewItem
  {
  private:
    CCopasiObject* pCopasiObject;
    ObjectBrowserItem* pParent;
    ObjectBrowserItem* pChild;
    ObjectBrowserItem* pBrother;
    bool mchecked;
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

    void reverseChecked();
    bool isChecked() const;

    //-1 if this is no user checked
    //0 if this is only partly checked
    //1 if this is full checked
    int UserChecked(ObjectBrowserItem* pCurrent);
  };

#endif
