/********************************************************
    Author: Liang Xu
    Version : 1.xx  <first>
    Description: 
    Date: 04/03 
    Comment : Copasi Object Browser: 
    Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#ifndef OBJECTBROWSER_H
#define OBJECTBROWSER_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QPushButton;
class QListView;
class ObjectBrowserItem;
class objectList;
class QListViewItem;
class CCopasiContainer;
class CCopasiObject;
class ObjectBrowser : public QWidget
  {
    Q_OBJECT

  public:
    objectList* objectItemList;
    objectList* refreshList;
    ObjectBrowser(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ObjectBrowser();

    QPushButton* cancelButton;
    QPushButton* nextButton;
    QPushButton* backButton;
    QListView* ObjectListView;

    void export(ObjectBrowserItem* pCurrent, objectList* outputList);

    void setCheck(ObjectBrowserItem* pCurrent);
    void setUncheck(ObjectBrowserItem* pCurrent);
    void clickToReverseCheck(ObjectBrowserItem* pCurrent);
    void setCheckMark(ObjectBrowserItem* pCurrent);

    void loadData();
    void loadChild(ObjectBrowserItem* parent, CCopasiContainer * copaParent, bool nField);
    void loadField(ObjectBrowserItem* parent, CCopasiContainer * copaParent);

    CCopasiObject* getFieldCopasiObject(CCopasiObject* pCurrent, const char* name);

    void updateUI();
    void loadUI();

  public slots:
    virtual void cancelClicked();
    virtual void listviewChecked(QListViewItem*);
    virtual void backClicked();
    virtual void nextClicked();

  protected:
    QGridLayout* ObjectBrowserLayout;
  };
#endif // OBJECTBROWSER_H
