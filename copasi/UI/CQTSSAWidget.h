// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTSSAWidget.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/05/15 13:46:08 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTSSAWidget.ui'
 **
 ** Created: Tue May 15 09:22:44 2007
 **      by: The User Interface Compiler ($Id: CQTSSAWidget.h,v 1.2 2007/05/15 13:46:08 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQTSSAWIDGET_H
#define CQTSSAWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include "TaskWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLineEdit;
class QLabel;
class QCheckBox;
class QFrame;
class CTSSAProblem;
class CQValidatorInt;
class CQValidatorDouble;

class CQTSSAWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQTSSAWidget(QWidget* parent = 0, const char* name = 0);
    ~CQTSSAWidget();

    QLineEdit* mpEditIntervals;
    QLineEdit* mpEditIntervalSize;
    QLabel* mpLblDeltaT;
    QLineEdit* mpEditDuration;
    QLabel* mpLblIntervals;
    QCheckBox* mpCheckDelay;
    QLineEdit* mpEditDelay;
    QLabel* mpLblDuration;
    QLabel* mpLblIntervalSize;
    QCheckBox* mpCheckSave;
    QFrame* line1;

    virtual bool runTask();

  public slots:
    void slotDuration();
    void slotIntervalSize();
    void slotIntervals();
    virtual void slotOutputDelay(bool checked);

  protected:
    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

    QVBoxLayout* CQTSSAWidgetLayout;
    QGridLayout* mpGridLayout;

  protected slots:
    virtual void languageChange();

  private:
    CTSSAProblem * mpTSSAProblem;
    CQValidatorDouble * mpValidatorDuration;
    CQValidatorDouble * mpValidatorIntervalSize;
    CQValidatorDouble * mpValidatorDelay;
    CQValidatorInt * mpValidatorIntervals;

    QPixmap image0;

    void init();
    void destroy();
    void checkTimeSeries();
  };

#endif // CQTSSAWIDGET_H
