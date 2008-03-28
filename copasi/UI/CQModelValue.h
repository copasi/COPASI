// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQModelValue.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/03/28 20:45:06 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQModelValue.ui'
 **
 ** Created: Tue Nov 13 09:15:09 2007
 **      by: The User Interface Compiler ($Id: CQModelValue.h,v 1.10 2008/03/28 20:45:06 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQMODELVALUE_H
#define CQMODELVALUE_H

#include <qvariant.h>
#include <qpixmap.h>
#include <string>
#include "copasiWidget.h"

#include <qwidgetstack.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class CQExpressionWidget;
class QFrame;
class QPushButton;
class QComboBox;
class QLineEdit;
class QLabel;
class QCheckBox;
class QToolButton;
class CQExpressionWidget;
class CQExpressionMmlWidgetStack;
class FunctionWidget2;
//class Form1;
class CModelValue;
class CExpression;

class CQModelValue : public CopasiWidget
  {
    Q_OBJECT

  public:
    /// Constructor
    CQModelValue(QWidget* parent = 0, const char* name = 0);
    /// Destructor
    ~CQModelValue();

    QFrame* mpLine2;
    QPushButton* mpBtnCommit;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnNew;
    QPushButton* mpBtnDelete;
    QComboBox* mpComboBoxType;
    QLineEdit* mpEditName;
    QLabel* mpLblType;
    QLabel* mpLblName;
    QLabel* mpLblRate;
    QLineEdit* mpEditRate;
    QLabel* mpLblValue;
    QLineEdit* mpEditCurrentValue;
    QLabel* mpLblExpression;
    QFrame* mpLine1;
    QLabel* mpLblInitialValue;
    QLineEdit* mpEditInitialValue;
    QCheckBox* mpBoxUseInitialExpression;
    QLabel* mpLblInitialExpression;
    // CQExpressionWidget* mpEditInitialExpression;
    CQExpressionMmlWidgetStack *mpEditFcnInitialExpression;
    QToolButton* mpBtnInitialExpressionObject;
    QToolButton *mpBtnEditInitialExpression;
    // CQExpressionWidget* mpEditExpression;
    CQExpressionMmlWidgetStack *mpEditFcnExpression;
    QToolButton* mpBtnExpressionObject;
    QToolButton *mpBtnEditExpression;

    virtual bool enter(const std::string & key);
    virtual bool leave();
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  protected:
    QGridLayout* CQModelValueLayout;
    QSpacerItem* mpSpacer;
    QHBoxLayout* mpBtnLayout;
    QHBoxLayout* mpHBoxLayoutInitialExpression;
    QVBoxLayout* mpVBoxLayoutInitialExpression;
    QSpacerItem* mpSpacerObjectInitialExpression;
    QHBoxLayout* mpHBoxLayoutExpression;
    QVBoxLayout* mpVBoxLayoutExpression;
    QSpacerItem* mpSpacerExpressionObject;

  protected slots:
    virtual void languageChange();

  private:
    std::vector< int > mItemToType;
    CModelValue * mpModelValue;
    std::string mKey;
    bool mChanged;
    bool mExpressionValid;
    bool mInitialExpressionValid;

    QPixmap image0;
    QPixmap image1;

    /// Function to initialize any required values
    void init();
    /// Function to load any saved values
    void load();
    /// Function to save any inputs from user
    void save();
    /// Function to destroy any modifications
    void destroy();
    /// Function to show the correct buttons wrt Expression Widgets
    void showCorrectButtonsExpression();
    /// Function to show the correct buttons wrt Initial Expression Widgets
    void showCorrectButtonsInitialExpression();

  private slots:
    /// Slot for being activated whenever the Commit button is clicked
    void slotBtnCommit();
    /// Slot for being activated whenever the Revert button is clicked
    void slotBtnRevert();
    /// Slot for being activated whenever the New button is clicked
    void slotBtnNew();
    /// Slot for being activated whenever the Delete button is clicked
    void slotBtnDelete();
    /// Slot for being activated whenever the type of Simulation Type Combo Box is changed
    void slotTypeChanged(int type);
    /// Slot for being activated whenever the Use Initial Expression check box is checked
    void slotInitialTypeChanged(bool useInitialAssignment);
    /// Slot for being activated whenever
    void slotNameLostFocus();
    /// Slot for validating mathematical formula of Expression
    void slotExpressionValid(bool valid);
    /// Slot for validating mathematical formula of Initial Expression
    void slotInitialExpressionValid(bool valid);
    /// Slot for being activated whenever the Edit button of Expression is clicked
    void slotEditExpression();
    /// Slot for being activated whenever the Edit button of Initial Expression is clicked
    void slotEditInitialExpression();
  };

#endif // CQMODELVALUE_H
