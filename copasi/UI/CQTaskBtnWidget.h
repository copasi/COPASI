/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskBtnWidget.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:42 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTaskBtnWidget.ui'
 **
 ** Created: Fri Oct 7 14:23:55 2005
 **      by: The User Interface Compiler ($Id: CQTaskBtnWidget.h,v 1.5 2006/04/27 01:27:42 shoops Exp $)
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
    QPushButton* mpBtnAssistant;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnReport;

  protected:
    QVBoxLayout* CQTaskBtnWidgetLayout;
    QSpacerItem* mpSpacer;
    QGridLayout* mpGridLayout;

  protected slots:
    virtual void languageChange();
  };

#endif // CQTASKBTNWIDGET_H
