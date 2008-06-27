// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQPrintAsDialog.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/27 12:02:46 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQPrintAsDialog.ui'
 **
 ** Created: Thu Jun 26 14:26:44 2008
 **      by: The User Interface Compiler ($Id: CQPrintAsDialog.h,v 1.1 2008/06/27 12:02:46 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQPRINTASDIALOG_H
#define CQPRINTASDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QCheckBox;

class CQPrintAsDialog : public QDialog
  {
    Q_OBJECT

  public:
    CQPrintAsDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~CQPrintAsDialog();

    QFrame* mpFrame;
    QLabel* mpLabelType;
    QLineEdit* mpEditFileName;
    QPushButton* mpBtnBrowse;
    QLabel* mpLabelFileName;
    QCheckBox* mpCBPNG;
    QCheckBox* mpCBSVG;
    QPushButton* mpBtnConfirm;
    QPushButton* mpBtnCancel;

  protected:
    QVBoxLayout* CQPrintAsDialogLayout;
    QGridLayout* mpFrameLayout;
    QHBoxLayout* layout3;
    QHBoxLayout* layout5;
    QSpacerItem* spacer3;
    QHBoxLayout* layout6;

  protected slots:
    virtual void languageChange();

    void openFileDialog();
  };

#endif // CQPRINTASDIALOG_H
