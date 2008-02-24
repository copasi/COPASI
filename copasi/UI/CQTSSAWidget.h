// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTSSAWidget.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/02/24 16:19:15 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTSSAWidget.ui'
 **
 ** Created: Sun Feb 24 16:58:46 2008
 **      by: The User Interface Compiler ($Id: CQTSSAWidget.h,v 1.5 2008/02/24 16:19:15 akoenig Exp $)
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
