// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPreferenceDialog.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/06/23 16:29:21 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQPreferenceDialog.ui'
 **
 ** Created: Sat Jun 23 12:19:36 2007
 **      by: The User Interface Compiler ($Id: CQPreferenceDialog.h,v 1.2 2007/06/23 16:29:21 aekamal Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQPREFERENCEDIALOG_H
#define CQPREFERENCEDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QListView;
class QListViewItem;

class CQPreferenceDialog : public QDialog
  {
    Q_OBJECT

  public:
    CQPreferenceDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~CQPreferenceDialog();

    QPushButton* mpBtnOk;
    QPushButton* mpBtnCancel;
    QListView* mpListView;

  protected:
    QHBoxLayout* Layout1;

  protected slots:
    virtual void languageChange();

    virtual void slotBtnOk();
    virtual void slotBtnCancel();
    virtual void editItem(QListViewItem*, const QPoint&, int);
    virtual void editItem(QListViewItem*);

  private slots:
    virtual void init();
  };

#endif // CQPREFERENCEDIALOG_H
