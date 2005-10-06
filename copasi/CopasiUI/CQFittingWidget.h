/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingWidget.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/06 19:19:18 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingWidget.ui'
 **
 ** Created: Thu Oct 6 15:02:52 2005
 **      by: The User Interface Compiler ($Id: CQFittingWidget.h,v 1.2 2005/10/06 19:19:18 shoops Exp $)
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
    CScanContainerWidget * mpConstraints;
    QHBoxLayout * mpParameterPageLayout;
    CScanContainerWidget * mpParameters;
    QHBoxLayout * mpConstraintPageLayout;

    virtual bool loadTask();
    virtual bool saveTask();
    virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

    QVBoxLayout* CQFittingWidgetLayout;
    QGridLayout* mpGridLayout;
    QSpacerItem* mpSpacer;

  protected slots:
    virtual void languageChange();

  private:
    QPixmap image0;

    void init();
  };

#endif // CQFITTINGWIDGET_H
