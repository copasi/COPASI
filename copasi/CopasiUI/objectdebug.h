/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/objectdebug.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:50 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'objectdebug.ui'
 **
 ** Created: Tue Apr 1 19:46:57 2003
 **      by: The User Interface Compiler ($Id: objectdebug.h,v 1.1.1.1 2004/10/26 15:17:50 anuragr Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef OBJECTDEBUG_H
#define OBJECTDEBUG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QListView;
class QListViewItem;
class QPushButton;

class ObjectDebug : public QDialog
  {
    Q_OBJECT

  public:
    ObjectDebug(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~ObjectDebug();

    QPushButton* UpdateButton;
    QListView* ListOfObjects;

  public slots:
    void update();

  protected:
    QGridLayout* ObjectDebugLayout;

  protected slots:
    virtual void languageChange();
  private:
    void addObjectRecursive(QWidget * parent, void * ptr);
    void init();
  };

#endif // OBJECTDEBUG_H
