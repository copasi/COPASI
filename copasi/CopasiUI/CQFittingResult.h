/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingResult.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 06:57:33 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingResult.ui'
 **
 ** Created: Wed Mar 22 11:31:14 2006
 **      by: The User Interface Compiler ($Id: CQFittingResult.h,v 1.3 2006/10/15 06:57:33 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQFITTINGRESULT_H
#define CQFITTINGRESULT_H

#include <qvariant.h>
#include "CopasiUI/copasiWidget.h"
#include "CopasiUI/CQFittingResultTab1.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTabWidget;
class CQFittingResultTab1;
class QTable;
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
    QTable* mpCorrelations;
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
