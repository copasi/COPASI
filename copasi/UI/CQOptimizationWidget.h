/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/14 16:27:00 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQOptimizationWidget.ui'
 **
 ** Created: Fri Oct 14 08:43:07 2005
 **      by: The User Interface Compiler ($Id: CQOptimizationWidget.h,v 1.1 2005/10/14 16:27:00 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQOPTIMIZATIONWIDGET_H
 #define CQOPTIMIZATIONWIDGET_H

#include <qvariant.h>
 #include <qpixmap.h>
 #include "TaskWidget.h"
 #include "CScanContainerWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QToolButton;
class QLabel;
class QTextEdit;
class QButtonGroup;
class QRadioButton;
class QPushButton;
class QTabWidget;
class QWidget;

class CQOptimizationWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQOptimizationWidget(QWidget* parent = 0, const char* name = 0);
    ~CQOptimizationWidget();

    QToolButton* mpBtnObject;
    QLabel* mpLblExpression;
    QTextEdit* mpEditExpression;
    QButtonGroup* mpBtnGroup;
    QRadioButton* mpBtnSteadystate;
    QRadioButton* mpBtnTimeCourse;
    QPushButton* mpBtnAdd;
    QTabWidget* mpTabWidget;
    QWidget* mpParametersPage;
    QWidget* mpConstraintsPage;

    virtual bool runTask();

  protected:
    CScanContainerWidget * mpCurrentList;
    CScanContainerWidget * mpConstraints;
    QHBoxLayout * mpParameterPageLayout;
    CScanContainerWidget * mpParameters;
    QHBoxLayout * mpConstraintPageLayout;
    QColor mChangedColor;
    QColor mSavedColor;
    bool mTypeChanged;

    virtual bool loadTask();
    virtual bool saveTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

    QVBoxLayout* CQOptimizationWidgetLayout;
    QGridLayout* mpGridLayout;
    QSpacerItem* mpSpacer;
    QVBoxLayout* mpBtnGroupLayout;

  protected slots:
    virtual void languageChange();

    void slotBtnAdd();
    void slotPageChange(QWidget * currentPage);
    void slotItemDeleted();
    void slotCopyItemWidget(int);
    void slotTypeChanged(bool);
    void slotExpression();

  private:
    QPixmap image0;

    void init();
  };

#endif // CQOPTIMIZATIONWIDGET_H
