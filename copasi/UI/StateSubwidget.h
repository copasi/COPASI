// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/StateSubwidget.h,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/02 14:19:14 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'StateSubwidget.ui'
 **
 ** Created: Do Aug 2 16:13:44 2007
 **      by: The User Interface Compiler ($Id: StateSubwidget.h,v 1.15 2007/08/02 14:19:14 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef STATESUBWIDGET_H
#define STATESUBWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class CQArrayAnnotationsWidget;
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
    QTable* mpModelValueTable;
    QWidget* TabPage_3;
    QTable* tableFlux;
    QWidget* TabPage_4;
    QSplitter* splitter3;
    CQArrayAnnotationsWidget* mpJacobianAnnotationWidget;
    QLabel* textLabelJacobian;
    QTable* tableEigenValues;
    QLabel* textLabelEigenvalues;
    QWidget* TabPage_5;
    QSplitter* splitter3_2;
    CQArrayAnnotationsWidget* mpJacobianXAnnotationWidget;
    QLabel* textLabelJacobianX;
    QTable* tableEigenValuesX;
    QLabel* textLabelEigenvaluesX;
    QWidget* TabPage_6;
    QTextEdit* stabilityTextEdit;
    QWidget* TabPage_7;
    QTextEdit* protocolTextEdit;

    void displayOptimizationTab(bool display);
    virtual bool loadMetabolites(const CModel * model);
    virtual bool loadReactions(CModel * model);
    virtual void loadModelValues(const CModel * model);
    virtual bool loadAll(const CSteadyStateTask * task);
    bool clear();

  public slots:
    virtual void loadJacobian(const CSteadyStateTask * task);
    virtual void showUnits();

  protected:
    QVBoxLayout* StateSubwidgetLayout;
    QVBoxLayout* TabPageLayout;
    QVBoxLayout* tabLayout;
    QVBoxLayout* tabLayout_2;
    QHBoxLayout* TabPageLayout_2;
    QVBoxLayout* TabPageLayout_3;
    QGridLayout* TabPageLayout_4;
    QGridLayout* layoutJacobian;
    QSpacerItem* spacer3;
    QGridLayout* layoutEigenvalues;
    QSpacerItem* spacer4;
    QVBoxLayout* TabPageLayout_5;
    QGridLayout* layoutJacobianX;
    QSpacerItem* spacer3_2;
    QGridLayout* layoutEigenvaluesX;
    QSpacerItem* spacer4_2;
    QVBoxLayout* TabPageLayout_6;
    QGridLayout* TabPageLayout_7;

  protected slots:
    virtual void languageChange();

    virtual void init();

  private:
    QPixmap image0;
  };

#endif // STATESUBWIDGET_H
