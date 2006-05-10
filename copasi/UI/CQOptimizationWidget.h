/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationWidget.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/05/10 13:06:38 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQOptimizationWidget.ui'
 **
 ** Created: Mi Mai 10 15:05:11 2006
 **      by: The User Interface Compiler ($Id: CQOptimizationWidget.h,v 1.6 2006/05/10 13:06:38 ssahle Exp $)
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
class CQExpressionWidget;
class QToolButton;
class QLabel;
class QButtonGroup;
class QRadioButton;
class QTabWidget;
class QWidget;
class CQFittingItemWidget;

class CQOptimizationWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQOptimizationWidget(QWidget* parent = 0, const char* name = 0);
    ~CQOptimizationWidget();

    CQExpressionWidget* mpEditExpression;
    QToolButton* mpBtnObject;
    QLabel* mpLblType;
    QLabel* mpLblExpression;
    QButtonGroup* mpBtnGroup;
    QRadioButton* mpBtnSteadystate;
    QRadioButton* mpBtnTimeCourse;
    QTabWidget* mpTabWidget;
    QWidget* mpParametersPage;
    QWidget* mpConstraintsPage;

    virtual bool runTask();
    virtual bool saveExpression();
    virtual bool loadExpression();
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
    std::vector<CCopasiObject *> * mpParseList;

    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

    QVBoxLayout* CQOptimizationWidgetLayout;
    QGridLayout* layout2;
    QSpacerItem* mpSpacer2;
    QSpacerItem* mpSpacer;
    QHBoxLayout* mpBtnGroupLayout;

  protected slots:
    virtual void languageChange();

    void slotPageChange(QWidget * currentPage);
    void slotExpression();
    void slotObjectSelect();

  private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;

    void init();
    void destroy();
  };

#endif // CQOPTIMIZATIONWIDGET_H
