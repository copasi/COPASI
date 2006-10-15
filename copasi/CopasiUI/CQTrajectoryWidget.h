/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQTrajectoryWidget.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 06:57:33 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTrajectoryWidget.ui'
 **
 ** Created: Fri May 5 22:14:49 2006
 **      by: The User Interface Compiler ($Id: CQTrajectoryWidget.h,v 1.2 2006/10/15 06:57:33 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQTRAJECTORYWIDGET_H
#define CQTRAJECTORYWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include "CopasiUI/TaskWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLineEdit;
class QLabel;
class QCheckBox;
class QFrame;
class CTrajectoryProblem;
class CQValidatorInt;
class CQValidatorDouble;

class CQTrajectoryWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQTrajectoryWidget(QWidget* parent = 0, const char* name = 0);
    ~CQTrajectoryWidget();

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

    QVBoxLayout* CQTrajectoryWidgetLayout;
    QGridLayout* mpGridLayout;

  protected slots:
    virtual void languageChange();

  private:
    CQValidatorInt * mpValidatorIntervals;
    CQValidatorDouble * mpValidatorDelay;
    CQValidatorDouble * mpValidatorIntervalSize;
    CQValidatorDouble * mpValidatorDuration;
    CTrajectoryProblem * mpTrajectoryProblem;

    QPixmap image0;

    void init();
    void destroy();
    void checkTimeSeries();
  };

#endif // CQTRAJECTORYWIDGET_H
