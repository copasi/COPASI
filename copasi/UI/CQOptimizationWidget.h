/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationWidget.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/08 19:01:10 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQOptimizationWidget.ui'
 **
 ** Created: Wed Mar 8 13:42:29 2006
 **      by: The User Interface Compiler ($Id: CQOptimizationWidget.h,v 1.2 2006/03/08 19:01:10 shoops Exp $)
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
class QTextEdit;
class QToolButton;
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

    QTextEdit* mpEditExpression;
    QToolButton* mpBtnObject;
    QButtonGroup* mpBtnGroup;
    QRadioButton* mpBtnSteadystate;
    QRadioButton* mpBtnTimeCourse;
    QLabel* mpLblType;
    QLabel* mpLblExpression;
    QTabWidget* mpTabWidget;
    QWidget* mpParametersPage;
    QWidget* mpConstraintsPage;

    virtual bool runTask();
    virtual bool saveExpression();

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
    QGridLayout* mpLayoutGrid;
    QSpacerItem* mpSpacer;
    QSpacerItem* mpSpacer2;
    QHBoxLayout* mpBtnGroupLayout;

  protected slots:
    virtual void languageChange();

    void slotPageChange(QWidget * currentPage);
    void slotTypeChanged(bool steadystate);
    void slotExpression();
    void slotObjectSelect();

  private:
    QPixmap image0;
    QPixmap image1;

    void init();
    void destroy();
  };

#endif // CQOPTIMIZATIONWIDGET_H
