// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationResult.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/10/14 19:47:24 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQOptimizationResult.ui'
 **
 ** Created: Tue Oct 14 15:18:17 2008
 **      by: The User Interface Compiler ($Id: CQOptimizationResult.h,v 1.1.2.1 2008/10/14 19:47:24 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQOPTIMIZATIONRESULT_H
#define CQOPTIMIZATIONRESULT_H

#include <qvariant.h>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class QLineEdit;
class QTable;
class COptTask;
class COptProblem;

class CQOptimizationResult : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQOptimizationResult(QWidget* parent = 0, const char* name = 0);
    ~CQOptimizationResult();

    QLabel* mpLblResult;
    QPushButton* mpBtnUpdateModel;
    QPushButton* mpBtnSave;
    QLineEdit* mpEditCPUTime;
    QLineEdit* mpEditEvaluations;
    QLineEdit* mpEditSpeed;
    QLabel* mpLblSpeed;
    QLabel* mpLblEvaluations;
    QLabel* mpLblCPUTime;
    QLabel* mpLblObjectiveValue;
    QLineEdit* mpEditObjectiveValue;
    QTable* mpParameters;

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string &);

  protected:
    QVBoxLayout* CQOptimizationResultLayout;
    QSpacerItem* mpSpacer;
    QHBoxLayout* mpHBox;
    QGridLayout* mpGrid;

  protected slots:
    virtual void languageChange();

  private:
    const COptProblem * mpProblem;
    const COptTask * mpTask;

    void init();

  private slots:
    void slotSave(void);
    void slotUpdateModel();
  };

#endif // CQOPTIMIZATIONRESULT_H
