// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/StateSubwidget.h,v $
//   $Revision: 1.17 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/12/05 20:16:26 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'StateSubwidget.ui'
 **
 ** Created: Wed Dec 5 13:31:55 2007
 **      by: The User Interface Compiler ($Id: StateSubwidget.h,v 1.17 2007/12/05 20:16:26 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef STATESUBWIDGET_H
#define STATESUBWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class CQArrayAnnotationsWidget;
class QLabel;
class QTabWidget;
class QWidget;
class QTextEdit;
class QTable;
class QSplitter;
class CModel;
class CSteadyStateTask;

class StateSubwidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    StateSubwidget(QWidget* parent = 0, const char* name = 0);
    ~StateSubwidget();

    QLabel* topLabel;
    QTabWidget* mpTabWidget;
    QWidget* mpOptimizationPage;
    QTextEdit* optimizationResultText;
    QWidget* mpMetabolitesPage;
    QTable* mpTblMetabolites;
    QWidget* mpCompartmentsPage;
    QTable* mpTblCompartments;
    QWidget* mpModelQuantitiesPage;
    QTable* mpTblModelValues;
    QWidget* mpReactionsPage;
    QTable* mpTblReactions;
    QWidget* mpJacobianPage;
    QSplitter* splitter3;
    CQArrayAnnotationsWidget* mpJacobianAnnotationWidget;
    QLabel* textLabelJacobian;
    QTable* tableEigenValues;
    QLabel* textLabelEigenvalues;
    QWidget* mpReducedJacobianPage;
    QSplitter* splitter3_2;
    CQArrayAnnotationsWidget* mpJacobianXAnnotationWidget;
    QLabel* textLabelJacobianX;
    QTable* tableEigenValuesX;
    QLabel* textLabelEigenvaluesX;
    QWidget* mpStabilityPage;
    QTextEdit* stabilityTextEdit;
    QWidget* mpProtocolPage;
    QTextEdit* protocolTextEdit;

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual void setFramework(int framework);
    void displayOptimizationTab(bool displayOptTab);
    virtual bool loadAll(const CSteadyStateTask * pTask);
    void clear();

  protected:
    const CSteadyStateTask * mpTask;
    CModel * mpModel;

    virtual void init();
    void loadMetabolites();
    void loadCompartments();
    void loadReactions();
    void loadModelValues();
    void loadJacobian();
    void showUnits();

    QVBoxLayout* StateSubwidgetLayout;
    QVBoxLayout* mpOptimizationPageLayout;
    QVBoxLayout* mpMetabolitesPageLayout;
    QVBoxLayout* mpCompartmentsPageLayout;
    QHBoxLayout* mpModelQuantitiesPageLayout;
    QVBoxLayout* mpReactionsPageLayout;
    QGridLayout* mpJacobianPageLayout;
    QGridLayout* layoutJacobian;
    QSpacerItem* spacer3;
    QGridLayout* layoutEigenvalues;
    QSpacerItem* spacer4;
    QVBoxLayout* mpReducedJacobianPageLayout;
    QGridLayout* layoutJacobianX;
    QSpacerItem* spacer3_2;
    QGridLayout* layoutEigenvaluesX;
    QSpacerItem* spacer4_2;
    QVBoxLayout* mpStabilityPageLayout;
    QGridLayout* mpProtocolPageLayout;

  protected slots:
    virtual void languageChange();

  private:
    QPixmap image0;
  };

#endif // STATESUBWIDGET_H
