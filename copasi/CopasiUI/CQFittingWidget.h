/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/05 16:24:07 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingWidget.ui'
 **
 ** Created: Wed Oct 5 12:16:35 2005
 **      by: The User Interface Compiler ($Id: CQFittingWidget.h,v 1.1 2005/10/05 16:24:07 shoops Exp $)
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
class CScanContainerWidget;
class QFrame;
class QTable;
class QLabel;
class QTabWidget;
class QWidget;
class QComboBox;
class QPushButton;

class CQFittingWidget : public TaskWidget
  {
    Q_OBJECT

  public:
    CQFittingWidget(QWidget* parent = 0, const char* name = 0);
    ~CQFittingWidget();

    QFrame* mpLine;
    QTable* mpTblParameter;
    QLabel* mpLblMethod;
    QTabWidget* mpTabWidget;
    QWidget* mpParametersPage;
    CScanContainerWidget* cScanContainerWidget3;
    QWidget* mpConstraintsPage;
    CScanContainerWidget* cScanContainerWidget4;
    QComboBox* mpBoxMethod;
    QPushButton* mpBtnAdd;
    QLabel* mpLblParameter;
    QPushButton* mpBtnExperiment;

    virtual bool runTask();

  protected:
    virtual bool loadTask();
    virtual bool saveTask();

    QVBoxLayout* CQFittingWidgetLayout;
    QGridLayout* mpGridLayout;
    QSpacerItem* spacer8;

  protected slots:
    virtual void languageChange();

  private:
    QPixmap image0;

    void init();
  };

#endif // CQFITTINGWIDGET_H
