// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/StateSubwidget.h,v $
//   $Revision: 1.19 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/07/03 09:11:46 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'StateSubwidget.ui'
 **
 ** Created: Thu Jul 3 11:06:28 2008
 **      by: The User Interface Compiler ($Id: StateSubwidget.h,v 1.19 2008/07/03 09:11:46 pwilly Exp $)
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
class QFrame;
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
    CQArrayAnnotationsWidget* mpJacobianAnnotationWidget;
    QLabel* textLabelJacobian;
    QFrame* line1;
    QTable* tableEigenValues;
    QLabel* textLabelEigenvalues;
    QWidget* mpReducedJacobianPage;
    CQArrayAnnotationsWidget* mpJacobianXAnnotationWidget;
    QLabel* textLabelJacobianX;
    QFrame* line2;
    QTable* tableEigenValuesX;
    QLabel* textLabelEigenvaluesX;
    QWidget* mpStabilityPage;
    QTextEdit* stabilityTextEdit;
    QWidget* mpProtocolPage;
    QTextEdit* protocolTextEdit;

    void displayOptimizationTab(bool displayOptTab);
    virtual bool loadAll(const CSteadyStateTask * pTask);
    void clear();
    virtual void setFramework(int framework);
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

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
    QVBoxLayout* mpJacobianPageLayout;
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
