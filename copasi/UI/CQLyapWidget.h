// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLyapWidget.h,v $
//   $Revision: 1.5.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/07 15:28:56 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQLyapWidget.ui'
 **
 ** Created: Tue Feb 6 14:32:59 2007
 **      by: The User Interface Compiler ($Id: CQLyapWidget.h,v 1.5.2.1 2007/02/07 15:28:56 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQLYAPWIDGET_H
#define CQLYAPWIDGET_H

#include <qvariant.h>
#include "TaskWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QCheckBox;
class QLineEdit;
class QLabel;

class CQLyapWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQLyapWidget(QWidget* parent = 0, const char* name = 0);
    ~CQLyapWidget();

    QFrame* mpLine;
    QCheckBox* mpCheckDelay;
    QLineEdit* mpEditDelay;
    QLineEdit* mpEditExponent;
    QCheckBox* mpCheckDivergence;
    QLabel* mpLblExponents;

    virtual bool runTask();

  protected:
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);
    virtual bool loadTask();
    virtual bool saveTask();

    QVBoxLayout* CQLyapWidgetLayout;
    QGridLayout* mpGridLayout;
    QHBoxLayout* mpLayoutDelay;

  protected slots:
    virtual void languageChange();

    void slotDelayChecked();

  private:
    void init();
  };

#endif // CQLYAPWIDGET_H
