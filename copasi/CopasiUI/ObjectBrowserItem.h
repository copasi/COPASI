#ifndef OBJECT_BROWSER_ITEM_H
#define OBJECT_BROWSER_ITEM_H

#include "qlistview.h"

class QListViewItem;
class QListView;
class CCopasiObject;

#define NOCHECKED -1
#define ALLCHECKED 1
#define PARTCHECKED 0

class objectList;

class ObjectBrowserItem : public QListViewItem
  {
  private:
    CCopasiObject* pCopasiObject;
    ObjectBrowserItem* pParent;
    ObjectBrowserItem* pChild;
    ObjectBrowserItem* pSibling;
    bool mChecked;
  public:
    ObjectBrowserItem (QListView * parent, ObjectBrowserItem * after, CCopasiObject* mObject, objectList* pList);
    ObjectBrowserItem (ObjectBrowserItem * parent, ObjectBrowserItem * after, CCopasiObject* mObject, objectList* pList);
    ~ObjectBrowserItem() {}

    void setParent(ObjectBrowserItem* parent);
    void setChild(ObjectBrowserItem* child);
    void setSibling(ObjectBrowserItem* sibling);

    ObjectBrowserItem* parent() const;
    ObjectBrowserItem* child() const;
    ObjectBrowserItem* sibling() const;

    void reverseChecked();
    bool isChecked() const;

    //-1 if this is no user checked
    //0 if this is only partly checked
    //1 if this is full checked
    int nUserChecked();
  };

struct objectListItem
  {
    objectListItem(ObjectBrowserItem* item, objectListItem* next)
    {
      pItem = item;
      pNext = next;
    }
    ObjectBrowserItem* pItem;
    objectListItem* pNext;
  };

class objectList
  {
  private:
    objectListItem* root;
    int length;
  public:
    objectList();
    void insert(ObjectBrowserItem* pItem);
    objectListItem* getRoot();
  };

#endif
