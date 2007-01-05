/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQRegistrationDialog.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/15 21:25:53 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQRegistrationDialog.ui'
 **
 ** Created: Fri Dec 15 13:33:32 2006
 **      by: The User Interface Compiler ($Id: CQRegistrationDialog.h,v 1.1 2006/12/15 21:25:53 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQREGISTRATIONDIALOG_H
#define CQREGISTRATIONDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QFrame;
class QPushButton;
class CRegistration;

class CQRegistrationDialog : public QDialog
  {
    Q_OBJECT

  public:
    CQRegistrationDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~CQRegistrationDialog();

    QLabel* mpLblDate;
    QLabel* mpLblEmail;
    QLineEdit* mpEditName;
    QLabel* mpLblName;
    QLabel* mpLblCode;
    QLineEdit* mpEditStatus;
    QFrame* mpLine;
    QLineEdit* mpEditEmail;
    QLineEdit* mpEditDate;
    QLineEdit* mpEditCode;
    QLabel* mpLblStatus;
    QPushButton* mpBtnValidate;
    QPushButton* mpBtnOk;
    QPushButton* mpBtnCancel;

  protected:
    QVBoxLayout* CQRegistrationDialogLayout;
    QSpacerItem* mpSpacerVertical;
    QGridLayout* mpLayoutValues;
    QHBoxLayout* mpLayoutBtn;
    QSpacerItem* mpSpacerBtn;

  protected slots:
    virtual void languageChange();

  private:
    CRegistration * mpRegistration;

    void init();
    void destroy();

  private slots:
    void slotBtnValidate();
    void slotBtnOk();
    void slotBtnCancel();
  };

#endif // CQREGISTRATIONDIALOG_H
