/****************************************************************************
 ** Form interface generated from reading ui file '.\ObjectBrowser.ui'
 **
 ** Created: Mon Apr 21 14:10:30 2003
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
class QListView;
class QListViewItem;
class QPushButton;

class ObjectBrowser : public QWidget
  {
    Q_OBJECT

  public:
    ObjectBrowser(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ObjectBrowser();

    QPushButton* backButton;
    QPushButton* nextButton;
    QPushButton* cancelButton;
    QListView* ObjectList;

  protected:
    QGridLayout* ObjectBrowserLayout;
  };

#endif // OBJECTBROWSER_H
