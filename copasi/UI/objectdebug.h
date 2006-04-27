/* Begin CVS Header
   $Source: /home/cvs/copasi_dev/copasi/CopasiUI/objectdebug.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: ssahle $
   $Date: 2005/11/10 09:33:59 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'objectdebug.ui'
 **
 ** Created: Mi Nov 9 01:31:48 2005
 **      by: The User Interface Compiler ($Id: objectdebug.h,v 1.5 2005/11/10 09:33:59 ssahle Exp $)
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
