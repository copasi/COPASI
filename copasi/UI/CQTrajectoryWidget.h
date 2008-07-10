// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTrajectoryWidget.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/07/10 18:51:35 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTrajectoryWidget.ui'
 **
 ** Created: Thu Jul 10 13:34:09 2008
 **      by: The User Interface Compiler ($Id: CQTrajectoryWidget.h,v 1.5 2008/07/10 18:51:35 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQTRAJECTORYWIDGET_H
#define CQTRAJECTORYWIDGET_H

#include <qvariant.h>
#include "TaskWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QLineEdit;
class QLabel;
class QCheckBox;
class CTrajectoryProblem;
class CQValidatorInt;
class CQValidatorDouble;

class CQTrajectoryWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQTrajectoryWidget(QWidget* parent = 0, const char* name = 0);
    ~CQTrajectoryWidget();

    QFrame* line2;
    QLineEdit* mpEditDuration;
    QLineEdit* mpEditIntegrationInterval;
    QLabel* mpLblIntervals;
    QLineEdit* mpEditIntervals;
    QLabel* mpLblOutputInterval;
    QLabel* mpLblIntervalSize;
    QCheckBox* mpCheckDelay;
    QLineEdit* mpEditDelay;
    QLabel* mpLblDuration;
    QLabel* mpLblIntegrationInterval;
    QLineEdit* mpEditOutputInterval;
    QLineEdit* mpEditIntervalSize;
    QCheckBox* mpCheckSave;
    QFrame* line1;

    virtual bool runTask();

  public slots:
    void slotDuration();
    void slotIntervalSize();
    void slotIntervals();
    void updateIntervals();
    void slotOutputDelay(bool checked);

  protected:
    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

    QVBoxLayout* CQTrajectoryWidgetLayout;
    QGridLayout* layout6;
    QHBoxLayout* layout5;
    QSpacerItem* spacer1;

  protected slots:
    virtual void languageChange();

  private:
    CQValidatorInt * mpValidatorIntervals;
    CQValidatorDouble * mpValidatorDelay;
    CQValidatorDouble * mpValidatorIntervalSize;
    CQValidatorDouble * mpValidatorDuration;
    CTrajectoryProblem * mpTrajectoryProblem;

    void init();
    void destroy();
    void checkTimeSeries();
  };

#endif // CQTRAJECTORYWIDGET_H
