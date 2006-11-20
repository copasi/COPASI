/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingResultTab1.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/11/20 16:39:12 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingResultTab1.ui'
 **
 ** Created: Mon Nov 20 10:18:08 2006
 **      by: The User Interface Compiler ($Id: CQFittingResultTab1.h,v 1.3 2006/11/20 16:39:12 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQFITTINGRESULTTAB1_H
#define CQFITTINGRESULTTAB1_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLineEdit;
class QLabel;
class CFitProblem;

class CQFittingResultTab1 : public QWidget
  {
    Q_OBJECT

  public:
    CQFittingResultTab1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQFittingResultTab1();

    QLineEdit* mpEditRMS;
    QLineEdit* mpEditStdDeviation;
    QLabel* mpLblRMS;
    QLineEdit* mpEditEvaluations;
    QLabel* mpLblCPUTime;
    QLabel* mpLblCVObjectiveValue;
    QLabel* mpLblCVStdDeviation;
    QLabel* mpLblStdDeviation;
    QLabel* mpLblCVRMS;
    QLabel* mpLblEvaluations;
    QLineEdit* mpEditSpeed;
    QLineEdit* mpEditCPUTime;
    QLineEdit* mpEditCVObjectiveValue;
    QLabel* mpLblObjectiveValue;
    QLineEdit* mpEditCVRMS;
    QLineEdit* mpEditCVStdDeviation;
    QLineEdit* mpEditObjectiveValue;
    QLabel* mpLblSpeed;

    void load(const CFitProblem * pProblem);

  protected:
    QVBoxLayout* CQFittingResultTab1Layout;
    QSpacerItem* mpSpacer;
    QGridLayout* mpLayoutGrid;

  protected slots:
    virtual void languageChange();

  private:
    void init();
  };

#endif // CQFITTINGRESULTTAB1_H
