// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.h,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/03/29 03:07:07 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQMetabolite.ui'
 **
 ** Created: Tue Nov 13 09:42:48 2007
 **      by: The User Interface Compiler ($Id: CQMetabolite.h,v 1.12 2008/03/29 03:07:07 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQMETABOLITE_H
#define CQMETABOLITE_H

#include <qvariant.h>
#include <qpixmap.h>
#include <string>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLabel;
class QLineEdit;
class QComboBox;
class QFrame;
class QCheckBox;
class QToolButton;
class QListView;
class QListViewItem;
class CQExpressionWidget;
class CQExpressionMmlWidgetStack;
class CMetab;
class CCompartment;
class CExpression;

/*!
    \brief The class for user-friendly organising all values of a chosen metabolite (aka species).

 This class inherits CopasiWidget to provide an ability for editing and displaying
 all values of a chosen metabolite (aka species).
 */
class CQMetabolite : public CopasiWidget
  {
    Q_OBJECT

  public:
    /// Constructor
    CQMetabolite(QWidget* parent = 0, const char* name = 0);
    /// Destructor
    ~CQMetabolite();

    QPushButton* mpBtnCommit;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnNew;
    QPushButton* mpBtnDelete;
    QLabel* mpLblType;
    QLineEdit* mpEditName;
    QComboBox* mpComboBoxCompartment;
    QComboBox* mpComboBoxType;
    QLabel* mpLblCompartment;
    QLabel* mpLblName;
    QFrame* mpLine1;
    QLineEdit* mpEditInitialValue;
    QLabel* mpLblInitialExpression;
    QCheckBox* mpBoxUseInitialExpression;
    QLabel* mpLblInitialValue;

    CQExpressionMmlWidgetStack *mpEditInitialExpression;
    QToolButton* mpBtnObjectInitialExpression;
    QToolButton *mpBtnEditInitialExpression;
    QLabel* mpLblExpression;

    CQExpressionMmlWidgetStack *mpEditExpression;
    QToolButton* mpBtnObjectExpression;
    QToolButton *mpBtnEditExpression;
    QLabel* mpLblReactions;

    QListView* mpReactionTable;
    QLineEdit* mpEditCurrentValue;
    QLineEdit* mpEditRate;
    QLineEdit* mpEditTransitionTime;
    QLabel* mpLblValue;
    QLabel* mpLblTransitionTime;
    QLabel* mpLblRate;
    QFrame* mpLine2;

    virtual bool enter(const std::string & key);
    virtual bool leave();
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual void setFramework(int framework);

  protected:
    QGridLayout* CQMetaboliteLayout;
    QSpacerItem* mpSpacer;
    QHBoxLayout* mpBtnLayout;
    QHBoxLayout* mpHBoxLayoutInitialExpression;
    QVBoxLayout* mpVBoxLayoutInitialExpression;
    QSpacerItem* mpSpacerObjectInitialExpression;
    QHBoxLayout* mpHBoxLayoutExpression;
    QVBoxLayout* mpVBoxLayoutExpression;
    QSpacerItem* mpSpacerObjectExpression;

  protected slots:
    virtual void languageChange();

  private:
    bool mChanged;
    bool mInitialNumberLastChanged;
    std::string mKey;
    CMetab * mpMetab;
    const CCompartment * mpCurrentCompartment;
    std::vector< int > mItemToType;
    double mInitialNumber;
    double mInitialConcentration;
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
    /// Function to load the reaction table
    void loadReactionTable();

  private slots:
    /// Slot for being activated whenever the Commit button is clicked
    void slotBtnCommit();
    /// Slot for being activated whenever the Revert button is clicked
    void slotBtnRevert();
    /// Slot for being activated whenever the New button is clicked
    void slotBtnNew();
    /// Slot for being activated whenever the Delete button is clicked
    void slotBtnDelete();
    ///
    void slotCompartmentChanged(int compartment);
    /// Slot for being activated whenever the type of Simulation Type Combo Box is changed
    void slotTypeChanged(int type);
    /// Slot for being activated whenever the Use Initial Expression check box is checked
    void slotInitialTypeChanged(bool useInitialAssignment);
    /// Slot for being activated whenever the line edit mpEditName has lost focus
    void slotNameLostFocus();
    /// Slot for validating mathematical formula of Expression
    void slotExpressionValid(bool valid);
    /// Slot for validating mathematical formula of Initial Expression
    void slotInitialExpressionValid(bool valid);
    /// Slot for being activated whenever the Edit button of Expression is clicked
    void slotEditExpression();
    /// Slot for being activated whenever the Edit button of Initial Expression is clicked
    void slotEditInitialExpression();
    ///
    void slotReactionTableCurrentChanged(QListViewItem * pItem);
    ///
    void slotInitialValueLostFocus();
  };

#endif // CQMETABOLITE_H
