/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 04/03 
Comment : Copasi Object Browser including:

browserObject: A complex structure uiniquely map to a CopasiObject
ObjectBrowserItem: A wraper to a broserObject, 
there may exist multiply wrappers to one browserObject
ObjectListItem
ObjectList: A queue for all element: 
The reason I dont use std:vector is
for efficiency requirement for all 
object browser item update
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#ifndef OBJECT_BROWSER_ITEM_H
#define OBJECT_BROWSER_ITEM_H

#include "copasi.h"
#include "qlistview.h"

class QListViewItem;
class QListView;
class CCopasiObject;

#define NOCHECKED -1
#define ALLCHECKED 1
#define PARTCHECKED 0

#define KEYBASE 100000000

enum objectType {FIELDATTR = 0, OBJECTATTR, CONTAINERATTR};

class ObjectList;

struct browserObject
  {
    CCopasiObject* pCopasiObject;
    bool mChecked;
    ObjectList* referenceList;
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

    void setObject(browserObject* pNewObject)
    {
      pBrowserObject = pNewObject;
    }

    virtual QString key (int column, bool ascending) const
      {
        return mKey;
      }

    // inline const QString & getKey() const {return mKey;}

    ObjectBrowserItem (QListView * parent = NULL, ObjectBrowserItem * after = NULL, CCopasiObject* mObject = NULL, ObjectList* pList = NULL);
    ObjectBrowserItem (ObjectBrowserItem * parent, ObjectBrowserItem * after = NULL, CCopasiObject* mObject = NULL, ObjectList* pList = NULL);
    ~ObjectBrowserItem()
    {
      if (getType() != FIELDATTR) //To avoid cross reference/multi deletion
        pdelete(pBrowserObject);
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

struct ObjectListItem
  {
    ObjectListItem(ObjectBrowserItem* item, ObjectListItem* next, ObjectListItem* last)
    {
      pItem = item;
      pNext = next;
      pLast = last;
    }
    ObjectBrowserItem* pItem;
    ObjectListItem* pNext;
    ObjectListItem* pLast;
  };

class ObjectList
  {
  private:
    bool* quickIndex;
    ObjectBrowserItem* *pointerList;
    int index_length;

    ObjectListItem* root;
    int length;
  public:
    ObjectList();
    ~ObjectList()
    {
      if (index_length != 0)
        {
          delete [] quickIndex;
          delete [] pointerList;
        }
      while (length > 0)
        pop();
    }
    void insert(ObjectBrowserItem* pItem); //insert at the first position
    ObjectListItem* getRoot();
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
