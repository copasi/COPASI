/****************************************************************************
 ** Form interface generated from reading ui file '.\ObjectBrowser.ui'
 **
 ** Created: Tue Apr 22 13:27:37 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
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

class ObjectBrowser : public QWidget
  {
    Q_OBJECT

  public:
    ObjectBrowser(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ObjectBrowser();

    QPushButton* cancelButton;
    QPushButton* nextButton;
    QPushButton* backButton;
    QListView* ObjectListView;

  public slots:
    virtual void cancelClicked();
    virtual void listviewChecked(ObjectBrowserItem*);
    virtual void backClicked();
    virtual void nextClicked();

  protected:
    QGridLayout* ObjectBrowserLayout;
  };
#endif // OBJECTBROWSER_H
