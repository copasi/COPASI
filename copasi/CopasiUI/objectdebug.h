/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/objectdebug.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/12/16 13:51:35 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'objectdebug.ui'
 **
 ** Created: Do Dez 16 10:00:20 2004
 **      by: The User Interface Compiler ($Id: objectdebug.h,v 1.4 2004/12/16 13:51:35 ssahle Exp $)
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
class QSpacerItem;
class QPushButton;
class QListView;
class QListViewItem;

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
    QSpacerItem* spacer5;

  protected slots:
    virtual void languageChange();

    virtual void action(QListViewItem * item, const QPoint & pnt, int col);

  private:
    void addObjectRecursive(QWidget * parent, void * ptr);
    void init();
  };

#endif // OBJECTDEBUG_H
