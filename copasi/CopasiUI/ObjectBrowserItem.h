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
    ObjectBrowserItem* pSibling;
    bool mChecked;
  public:
    ObjectBrowserItem (QListView * parent, ObjectBrowserItem * after, CCopasiObject* mObject);
    ObjectBrowserItem (ObjectBrowserItem * parent, ObjectBrowserItem * after, CCopasiObject* mObject);
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
    int UserChecked();
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
    objectList()
    {
      root = NULL;
      length = 0;
    }
    void insert(ObjectBrowserItem* pItem)
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
      for (; i < length; i++)
        pCurrent = pCurrent->pNext;
      pCurrent->pNext = pNewItem;
      length++;
    }
  };

#endif
