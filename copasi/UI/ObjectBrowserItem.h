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

#ifndef OBJECT_BROWSER_ITEM_H
#define OBJECT_BROWSER_ITEM_H

#include "qlistview.h"

class QListViewItem;
class QListView;
class CCopasiObject;

#define NOCHECKED -1
#define ALLCHECKED 1
#define PARTCHECKED 0

#define KEYBASE 100000000

enum objectType {FIELDATTR = 0, OBJECTATTR, CONTAINERATTR};

class objectList;

struct browserObject
  {
    CCopasiObject* pCopasiObject;
    bool mChecked;
    objectList* referenceList;
    browserObject();
    ~browserObject();
  };

class ObjectBrowserItem : public QListViewItem
  {
  private:
    static long KeySpace;
    browserObject* pBrowserObject;
    ObjectBrowserItem* pParent;
    ObjectBrowserItem* pChild;
    ObjectBrowserItem* pSibling;
    objectType mType;
    QString mKey;

  public:
    static void resetKeySpace()
    {
      KeySpace = KEYBASE;
    }
    browserObject* getObject()
    {
      return pBrowserObject;
    }

    virtual QString key (int column, bool ascending) const
      {
        return mKey;
      }

    // inline const QString & getKey() const {return mKey;}

    ObjectBrowserItem (QListView * parent, ObjectBrowserItem * after, CCopasiObject* mObject, objectList* pList);
    ObjectBrowserItem (ObjectBrowserItem * parent, ObjectBrowserItem * after, CCopasiObject* mObject, objectList* pList);
    ~ObjectBrowserItem()
    {
      delete pBrowserObject;
    }

    void attachKey();
    void setParent(ObjectBrowserItem* parent);
    void setChild(ObjectBrowserItem* child);
    void setSibling(ObjectBrowserItem* sibling);

    ObjectBrowserItem* parent() const;
    ObjectBrowserItem* child() const;
    ObjectBrowserItem* sibling() const;

    void reverseChecked();
    bool isChecked() const;

    void setObjectType(objectType newType)
    {
      mType = newType;
    }

    objectType getType()
    {
      return mType;
    }

    //-1 if this is no user checked
    //0 if this is only partly checked
    //1 if this is full checked
    int nUserChecked();
  };

typedef ObjectBrowserItem* pObjectBrowserItem;

struct objectListItem
  {
    objectListItem(ObjectBrowserItem* item, objectListItem* next, objectListItem* last)
    {
      pItem = item;
      pNext = next;
      pLast = last;
    }
    ObjectBrowserItem* pItem;
    objectListItem* pNext;
    objectListItem* pLast;
  };

class objectList
  {
  private:
    bool* quickIndex;
    ObjectBrowserItem* *pointerList;
    int index_length;

    objectListItem* root;
    int length;
  public:
    objectList();
    ~objectList()
    {
      while (length > 0)
        pop();
    }
    void insert(ObjectBrowserItem* pItem); //insert at the first position
    objectListItem* getRoot();
    ObjectBrowserItem* pop();
  inline int len() {return length;};

    void sortList();
    void delDuplicate();
    bool sortListInsert(ObjectBrowserItem* pItem); //insert and keep the sort order

    void createBucketIndex(int max);
    void insertBucket(ObjectBrowserItem* pItem);
    ObjectBrowserItem* bucketPop(int& cursor);
    void destroyBucket();
  };

#endif
