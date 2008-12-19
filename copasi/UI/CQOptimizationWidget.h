// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationWidget.h,v $
//   $Revision: 1.12.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/04 16:22:38 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQOptimizationWidget.ui'
 **
 ** Created: Thu Dec 4 11:12:42 2008
 **      by: The User Interface Compiler ($Id: CQOptimizationWidget.h,v 1.12.4.1 2008/12/04 16:22:38 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQOPTIMIZATIONWIDGET_H
#define CQOPTIMIZATIONWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include <map>
#include <string>
#include "TaskWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class CQExpressionMmlWidget;
class QLabel;
class QComboBox;
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

    QLabel* mpLblType;
    QLabel* mpLblExpression;
    CQExpressionMmlWidget* mpExpressionEMW;
    QComboBox* mpBoxSubtask;
    QButtonGroup* mpBtnGroup;
    QRadioButton* mpBtnMaximize;
    QRadioButton* mpBtnMinimize;
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
    std::map< std::string, C_INT32 > mSubtaskMap;

    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

    QVBoxLayout* CQOptimizationWidgetLayout;
    QGridLayout* mpGridLayout;
    QSpacerItem* mpSpacer;

  protected slots:
    virtual void languageChange();

    void slotPageChange(QWidget * currentPage);
    void slotExpressionValid(bool valid);
    void slotSubtaskChanged(const QString & subtask);

  private:
    QPixmap image0;
    QPixmap image1;

    void init();
    void destroy();
  };

#endif // CQOPTIMIZATIONWIDGET_H
