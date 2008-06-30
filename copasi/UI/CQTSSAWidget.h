// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTSSAWidget.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2008/06/30 11:41:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTSSAWidget.ui'
 **
 ** Created: Fri Mar 7 12:59:59 2008
 **      by: The User Interface Compiler ($Id: CQTSSAWidget.h,v 1.6 2008/06/30 11:41:02 nsimus Exp $)
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
    QLabel* mpLbDeuflTol;
    QLineEdit* mpEditDuration;
    QLabel* mpLblIntervals;
    QLineEdit* mpEditDeufelTol;
    QLabel* mpLblDuration;
    QLabel* mpLblIntervalSize;
    QCheckBox* mpCheckSave;
    QFrame* line1;

    virtual bool runTask();

  public slots:
    void slotDuration();
    void slotIntervalSize();
    void slotIntervals();
    virtual void disableDeuflhard(int);

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
