// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationWidget.h,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/12 18:04:11 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQOptimizationWidget.ui'
 **
 ** Created: Wed Sep 10 13:29:52 2008
 **      by: The User Interface Compiler ($Id: CQOptimizationWidget.h,v 1.12 2008/09/12 18:04:11 shoops Exp $)
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
class QCheckBox;
class QLabel;
class QComboBox;
class QTabWidget;
class QWidget;
class CQFittingItemWidget;

class CQOptimizationWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQOptimizationWidget(QWidget* parent = 0, const char* name = 0);
    ~CQOptimizationWidget();

    QCheckBox* mpCheckMaximize;
    CQExpressionMmlWidget* mpExpressionEMW;
    QLabel* mpLblExpression;
    QComboBox* mpBoxSubtask;
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
    std::map< std::string, C_INT32 > mSubtaskMap;

    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

    QVBoxLayout* CQOptimizationWidgetLayout;
    QGridLayout* mpGridLayout;
    QSpacerItem* mpSpacer;
    QSpacerItem* mpSpacer_2;

  protected slots:
    virtual void languageChange();

    void slotPageChange(QWidget * currentPage);
    void slotExpressionValid(bool valid);
    void slotSubtaskChanged(const QString & subtask);

  private:
    QPixmap image0;

    void init();
    void destroy();
  };

#endif // CQOPTIMIZATIONWIDGET_H
