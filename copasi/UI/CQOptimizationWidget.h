// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationWidget.h,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/04/18 09:13:10 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQOptimizationWidget.ui'
 **
 ** Created: Fri Apr 18 08:34:09 2008
 **      by: The User Interface Compiler ($Id: CQOptimizationWidget.h,v 1.11 2008/04/18 09:13:10 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQOPTIMIZATIONWIDGET_H
#define CQOPTIMIZATIONWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include "TaskWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class CQExpressionMmlWidget;
class QButtonGroup;
class QRadioButton;
class QLabel;
class QTabWidget;
class QWidget;
class CQFittingItemWidget;

class CQOptimizationWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQOptimizationWidget(QWidget* parent = 0, const char* name = 0);
    ~CQOptimizationWidget();

    CQExpressionMmlWidget* mpExpressionEMW;
    QButtonGroup* mpBtnGroup;
    QRadioButton* mpBtnSteadystate;
    QRadioButton* mpBtnTimeCourse;
    QLabel* mpLblExpression;
    QLabel* mpLblType;
    QTabWidget* mpTabWidget;
    QWidget* mpParametersPage;
    QWidget* mpConstraintsPage;

    virtual bool runTask();
    bool isSteadyState();

  public slots:
    void slotParameterNumberChanged(int number);
    void slotConstraintNumberChanged(int number);
    virtual void slotEditExpression();

  protected:
    CQFittingItemWidget * mpCurrentList;
    CQFittingItemWidget * mpConstraints;
    CQFittingItemWidget * mpParameters;
    QColor mChangedColor;
    QColor mSavedColor;
    bool mTypeChanged;
    QHBoxLayout * mpConstraintPageLayout;
    QHBoxLayout * mpParameterPageLayout;

    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

    QVBoxLayout* CQOptimizationWidgetLayout;
    QGridLayout* mpGridLayout;
    QSpacerItem* mpSpacer2;
    QHBoxLayout* mpBtnGroupLayout;

  protected slots:
    virtual void languageChange();

    void slotPageChange(QWidget * currentPage);
    void slotExpressionValid(bool valid);

  private:
    QPixmap image0;
    QPixmap image1;

    void init();
    void destroy();
  };

#endif // CQOPTIMIZATIONWIDGET_H
