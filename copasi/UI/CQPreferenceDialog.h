// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPreferenceDialog.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/06/19 16:35:28 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQPreferenceDialog.ui'
 **
 ** Created: Wed Jun 13 16:56:15 2007
 **      by: The User Interface Compiler ($Id: CQPreferenceDialog.h,v 1.1 2007/06/19 16:35:28 aekamal Exp $)
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
class QListView;
class QListViewItem;
class QPushButton;

class CQPreferenceDialog : public QDialog
  {
    Q_OBJECT

  public:
    CQPreferenceDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~CQPreferenceDialog();

    QListView* mpListView;
    QPushButton* mpBtnOk;
    QPushButton* mpBtnCancel;

  protected:
    QHBoxLayout* Layout1;

  protected slots:
    virtual void languageChange();

    virtual void slotBtnOk();
    virtual void slotBtnCancel();

  private slots:
    virtual void init();
    virtual void destroy();
  };

#endif // CQPREFERENCEDIALOG_H
