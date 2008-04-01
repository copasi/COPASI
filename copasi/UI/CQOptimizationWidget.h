/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationWidget.h,v $
  $Revision: 1.10 $
  $Name:  $
  $Author: pwilly $
  $Date: 2008/04/01 00:12:02 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQOptimizationWidget.ui'
 **
 ** Created: Thu Jul 13 13:57:39 2006
 **      by: The User Interface Compiler ($Id: CQOptimizationWidget.h,v 1.10 2008/04/01 00:12:02 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQOPTIMIZATIONWIDGET_H
#define CQOPTIMIZATIONWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include "UI/TaskWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class CQExpressionWidget;
class CQExpressionMmlWidgetStack;
class QToolButton;
class QLabel;
class QButtonGroup;
class QRadioButton;
class QTabWidget;
class QWidget;
class CQFittingItemWidget;

/*!
    \brief The class for user-friendly handling the optimization task.

 This class inherits TaskWidget with specific efforts to handle the optimization process.
 */
class CQOptimizationWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    /// Constructor
    CQOptimizationWidget(QWidget* parent = 0, const char* name = 0);
    /// Destructor
    ~CQOptimizationWidget();

    //CQExpressionWidget* mpEditExpression;
    CQExpressionMmlWidgetStack *mpEditExpression;
    QToolButton* mpBtnObject;
    QToolButton *mpBtnEdit;
    QHBoxLayout *mpHBoxLayoutExpression;
    QVBoxLayout *mpVBoxLayoutExpression;
    QSpacerItem *mpSpacerExpressionObject;

    QLabel* mpLblType;
    QLabel* mpLblExpression;
    QButtonGroup* mpBtnGroup;
    QRadioButton* mpBtnSteadystate;
    QRadioButton* mpBtnTimeCourse;
    QTabWidget* mpTabWidget;
    QWidget* mpParametersPage;
    QWidget* mpConstraintsPage;

    virtual bool runTask();
    bool isSteadyState();

  public slots:
    void slotParameterNumberChanged(int number);
    void slotConstraintNumberChanged(int number);

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
    QSpacerItem* mpSpacer;
    QHBoxLayout* mpBtnGroupLayout;

  protected slots:
    virtual void languageChange();

    void slotPageChange(QWidget * currentPage);
    /// Slot for validating mathematical formula of Expression
    void slotExpressionValid(bool valid);
    /// Slot for being activated whenever the Edit button of Expression is clicked
    void slotEditExpression();

  private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;

    void init();
    void destroy();
  };

#endif // CQOPTIMIZATIONWIDGET_H
