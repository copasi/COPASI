/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/StateSubwidget.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: stupe $ 
   $Date: 2005/10/26 15:43:18 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'StateSubwidget.ui'
 **
 ** Created: Mon Oct 24 12:17:46 2005
 **      by: The User Interface Compiler ($Id: StateSubwidget.h,v 1.8 2005/10/26 15:43:18 stupe Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef STATESUBWIDGET_H
 #define STATESUBWIDGET_H

#include <qvariant.h>
 #include <qwidget.h>
 #include "model/CState.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QTabWidget;
class QTextEdit;
class QTable;
class QSplitter;
class CModel;
class CSteadyStateTask;

class StateSubwidget : public QWidget
  {
    Q_OBJECT

  public:
    StateSubwidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~StateSubwidget();

    QLabel* topLabel;
    QTabWidget* tabWidget;
    QWidget* TabPage;
    QTextEdit* optimizationResultText;
    QWidget* tab;
    QTable* concentrationsTable;
    QWidget* tab_2;
    QTable* numbersTable;
    QWidget* TabPage_2;
    QTable* tableFlux;
    QWidget* TabPage_3;
    QSplitter* splitterJacobian;
    QTable* tableJacobian;
    QLabel* textLabelJacobian;
    QTable* tableEigenValues;
    QLabel* textLabelEigenvalues;
    QWidget* TabPage_4;
    QSplitter* splitterJacobianX;
    QTable* tableJacobianX;
    QLabel* textLabelJacobianX;
    QTable* tableEigenValuesX;
    QLabel* textLabelEigenvaluesX;
    QWidget* TabPage_5;
    QTextEdit* stabilityTextEdit;

    virtual bool loadMetabolites(const CModel * model);
    virtual bool loadReactions(const CModel * model);
    virtual bool loadAll(const CSteadyStateTask * task);
    void displayOptimizationTab(bool display);
    bool clear();

  public slots:
    virtual void loadJacobian(const CSteadyStateTask * task);
    virtual void showUnits();

  protected:
    QVBoxLayout* StateSubwidgetLayout;
    QVBoxLayout* TabPageLayout;
    QVBoxLayout* tabLayout;
    QVBoxLayout* tabLayout_2;
    QVBoxLayout* TabPageLayout_2;
    QVBoxLayout* TabPageLayout_3;
    QGridLayout* layoutJacobian;
    QSpacerItem* spacer3;
    QGridLayout* layoutEigenvalues;
    QSpacerItem* spacer4;
    QVBoxLayout* TabPageLayout_4;
    QGridLayout* layoutJacobianX;
    QSpacerItem* spacer3_2;
    QGridLayout* layoutEigenvaluesX;
    QSpacerItem* spacer4_2;
    QVBoxLayout* TabPageLayout_5;

  protected slots:
    virtual void languageChange();

    virtual void init();
  };

#endif // STATESUBWIDGET_H
