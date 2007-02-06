// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskBtnWidget.h,v $
//   $Revision: 1.5.8.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/06 16:23:47 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTaskBtnWidget.ui'
 **
 ** Created: Tue Feb 6 11:11:39 2007
 **      by: The User Interface Compiler ($Id: CQTaskBtnWidget.h,v 1.5.8.1 2007/02/06 16:23:47 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQTASKBTNWIDGET_H
#define CQTASKBTNWIDGET_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;

class CQTaskBtnWidget : public QWidget
  {
    Q_OBJECT

  public:
    CQTaskBtnWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQTaskBtnWidget();

    QPushButton* mpBtnRun;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnReport;
    QPushButton* mpBtnAssistant;

  protected:
    QVBoxLayout* CQTaskBtnWidgetLayout;
    QSpacerItem* mpSpacerVertical;
    QHBoxLayout* mpBtnLayout;
    QSpacerItem* mpSpacerHorizontal;

  protected slots:
    virtual void languageChange();
  };

#endif // CQTASKBTNWIDGET_H
