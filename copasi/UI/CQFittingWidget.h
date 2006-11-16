/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingWidget.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/11/16 15:45:13 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingWidget.ui'
 **
 ** Created: Thu Nov 9 10:10:22 2006
 **      by: The User Interface Compiler ($Id: CQFittingWidget.h,v 1.11 2006/11/16 15:45:13 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQFITTINGWIDGET_H
#define CQFITTINGWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include "TaskWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTabWidget;
class QWidget;
class CExperimentSet;
class CQFittingItemWidget;
class CCrossValidationSet;

class CQFittingWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQFittingWidget(QWidget* parent = 0, const char* name = 0);
    ~CQFittingWidget();

    QPushButton* mpBtnCrossValidation;
    QTabWidget* mpTabWidget;
    QWidget* mpParametersPage;
    QWidget* mpConstraintsPage;
    QPushButton* mpBtnExperiment;

    virtual bool runTask();

  public slots:
    void slotParameterNumberChanged(int number);
    void slotConstraintNumberChanged(int number);

  protected:
    CQFittingItemWidget * mpCurrentList;
    CQFittingItemWidget * mpConstraints;
    QHBoxLayout * mpParameterPageLayout;
    CQFittingItemWidget * mpParameters;
    QHBoxLayout * mpConstraintPageLayout;
    CExperimentSet * mpExperimentSet;
    std::map<std::string, std::string> mExperimentKeyMap;
    CCrossValidationSet * mpCrossValidationSet;
    std::map<std::string, std::string> mCrossValidationKeyMap;

    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

    QVBoxLayout* CQFittingWidgetLayout;
    QGridLayout* mpGridLayout;
    QSpacerItem* mpSpacer;

  protected slots:
    virtual void languageChange();

    void slotExperimentData();
    void slotPageChange(QWidget * currentPage);
    void slotCrossValidationData();

  private:
    QPixmap image0;

    void init();
    void destroy();
  };

#endif // CQFITTINGWIDGET_H
