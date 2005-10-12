/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingWidget.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/12 20:23:31 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingWidget.ui'
 **
 ** Created: Wed Oct 12 16:03:46 2005
 **      by: The User Interface Compiler ($Id: CQFittingWidget.h,v 1.5 2005/10/12 20:23:31 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQFITTINGWIDGET_H
 #define CQFITTINGWIDGET_H

#include <qvariant.h>
 #include <qpixmap.h>
 #include "TaskWidget.h"
 #include "CScanContainerWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTabWidget;
class QWidget;

class CQFittingWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQFittingWidget(QWidget* parent = 0, const char* name = 0);
    ~CQFittingWidget();

    QPushButton* mpBtnExperiment;
    QPushButton* mpBtnAdd;
    QTabWidget* mpTabWidget;
    QWidget* mpParametersPage;
    QWidget* mpConstraintsPage;

    virtual bool runTask();

  protected:
    QHBoxLayout * mpConstraintPageLayout;
    CScanContainerWidget * mpParameters;
    QHBoxLayout * mpParameterPageLayout;
    CScanContainerWidget * mpConstraints;
    CScanContainerWidget * mpCurrentList;

    virtual bool loadTask();
    virtual bool saveTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

    QVBoxLayout* CQFittingWidgetLayout;
    QGridLayout* mpGridLayout;
    QSpacerItem* mpSpacer;

  protected slots:
    virtual void languageChange();

    void slotBtnAdd();
    void slotExperimentData();
    void slotPageChange(QWidget * currentPage);
    void slotItemDeleted();
    void slotCopyItemWidget(int);

  private:
    QPixmap image0;

    void init();
  };

#endif // CQFITTINGWIDGET_H
