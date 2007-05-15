// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/CQFittingResult.h,v $
//   $Revision: 1.6.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/04/24 15:05:10 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingResult.ui'
 **
 ** Created: Mon Apr 23 18:00:02 2007
 **      by: The User Interface Compiler ($Id: CQFittingResult.h,v 1.6.4.1 2007/04/24 15:05:10 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQFITTINGRESULT_H
#define CQFITTINGRESULT_H

#include <qvariant.h>
#include "copasiWidget.h"
#include "CQFittingResultTab1.h"
#include "CQArrayAnnotationsWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTabWidget;
class CQFittingResultTab1;
class QTable;
class CQArrayAnnotationsWidget;
class QPushButton;
class QLabel;
class CFitTask;
class CFitProblem;

class CQFittingResult : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQFittingResult(QWidget* parent = 0, const char* name = 0);
    ~CQFittingResult();

    QTabWidget* mpTabWidget;
    CQFittingResultTab1* mpMain;
    QTable* mpParameters;
    QTable* mpExperiments;
    QTable* mpValues;
    CQArrayAnnotationsWidget* mpCorrelations;
    CQArrayAnnotationsWidget* mpFisherInformation;
    QTable* mpCrossValidations;
    QTable* mpCrossValidationValues;
    QPushButton* mpBtnSave;
    QLabel* mpLblResult;

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key);

  protected:
    QGridLayout* CQFittingResultLayout;

  protected slots:
    virtual void languageChange();

  private:
    const CFitTask * mpTask;
    const CFitProblem * mpProblem;

    void init();

  private slots:
    void slotSave();
  };

#endif // CQFITTINGRESULT_H
