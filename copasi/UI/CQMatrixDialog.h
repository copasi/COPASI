// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMatrixDialog.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/08/18 09:09:47 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQMatrixDialog.ui'
 **
 ** Created: Fri Aug 8 13:10:00 2008
 **      by: The User Interface Compiler ($Id: CQMatrixDialog.h,v 1.2 2008/08/18 09:09:47 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQMATRIXDIALOG_H
#define CQMATRIXDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QComboBox;
class QFrame;
class QPushButton;
class CArrayAnnotation;

class CQMatrixDialog : public QDialog
  {
    Q_OBJECT

  public:
    CQMatrixDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~CQMatrixDialog();

    QLabel* mpLabelRow;
    QComboBox* mpCBRow;
    QLabel* mpLabelColumn;
    QComboBox* mpCBColumn;
    QLabel* mpLabelDim3;
    QComboBox* mpCBDim3;
    QFrame* line1;
    QPushButton* mpOKBtn;
    QPushButton* mpCancelBtn;

  public slots:
    virtual void setArray(const CArrayAnnotation * tmp);

  protected:
    QVBoxLayout* CQMatrixDialogLayout;
    QSpacerItem* spacer1;
    QHBoxLayout* layout1;

  protected slots:
    virtual void languageChange();
  };

#endif // CQMATRIXDIALOG_H
