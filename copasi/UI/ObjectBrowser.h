/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ObjectBrowser.h,v $
   $Revision: 1.40 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:57 $
   End CVS Header */

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
#include <qdialog.h>
#include <vector>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QPushButton;
class QListView;
class QTextEdit;
class ObjectBrowserItem;
class ObjectList;
class QListViewItem;
class QFrame;
class CCopasiContainer;
class CCopasiObject;
class CopasiUI3Window;

enum pageIndex {LISTVIEWPAGE = 0, SELECTEDITEMPAGE};

class ObjectBrowser : public QDialog
  {
    Q_OBJECT
  private:
    pageIndex currentPage;
    CopasiUI3Window* mparent;
    std::vector<CCopasiObject*>* mOutputObjectVector;

  public:
    ObjectList* objectItemList;
    ObjectList* refreshList;
    ObjectBrowser(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ObjectBrowser();
    void cleanup();

    QPushButton* cancelButton;
    QPushButton* nextButton;
    QPushButton* backButton;
    QListView* ObjectListView;
    QFrame* Line1;
    QTextEdit* ObjectItemText;

    //Each Function calls the output shall be responsible to delete the list
    //    ObjectList* outputList();

    void eXport(ObjectBrowserItem* pCurrent, std::vector<CCopasiObject*>* outputVector);

    void setCheck(ObjectBrowserItem* pCurrent);
    void setUncheck(ObjectBrowserItem* pCurrent);
    void clickToReverseCheck(ObjectBrowserItem* pCurrent);
    void setCheckMark(ObjectBrowserItem* pCurrent);

    void loadData();
    void loadChild(ObjectBrowserItem* parent, CCopasiContainer * copaParent, bool nField);
    void loadField(ObjectBrowserItem* parent, CCopasiContainer * copaParent);

    CCopasiObject* getFieldCopasiObject(CCopasiContainer * pCurrent, const char* name);
    void setOutputVector(std::vector<CCopasiObject*>* pObjectVector);

    void updateUI();
    void loadUI();

  public slots:
    virtual void cancelClicked();
    virtual void listviewChecked(QListViewItem*);
    virtual void backClicked();
    virtual void nextClicked();

  protected:
    void closeEvent (QCloseEvent * e);
    QGridLayout* ObjectBrowserLayout;
  };
#endif // OBJECTBROWSER_H
