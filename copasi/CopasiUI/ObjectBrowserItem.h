#ifndef OBJECT_BROWSER_ITEM_H
#define OBJECT_BROWSER_ITEM_H

class QListViewItem;
class QListView;
class CCopasiObject;

class ObjectBrowserItem
  {
  private:
    CCopasiObject* pCopasiObject;
    QListViewItem* pListViewItem;
    ObjectBrowserItem* pParent;
    ObjectBrowserItem* pChild;
    ObjectBrowserItem* pBrother;

  public:
    ObjectBrowserItem (QListView * parent, ObjectBrowserItem * after);
    ObjectBrowserItem (ObjectBrowserItem * parent, ObjectBrowserItem * after);
    ~ObjectBrowserItem() {delete pListViewItem;}

    setParent(ObjectBrowserItem* parent);
    setChild(ObjectBrowserItem* child);
    setBrother(ObjectBrowserItem* brother);

    ObjectBrowserItem* parent() const;
    ObjectBrowserItem* child() const;
    ObjectBrowserItem* brother() const;
    QListViewItem* listviewitem() const;
  };

#endif
