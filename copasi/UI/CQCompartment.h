// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartment.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/03/29 02:01:18 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQCompartment.ui'
 **
 ** Created: Tue Nov 13 09:15:08 2007
 **      by: The User Interface Compiler ($Id: CQCompartment.h,v 1.5 2008/03/29 02:01:18 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQCOMPARTMENT_H
#define CQCOMPARTMENT_H

#include <qvariant.h>
#include <qpixmap.h>
#include <string>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QPushButton;
class QComboBox;
class QLineEdit;
class QLabel;
class QListView;
class QListViewItem;
class QCheckBox;
class QToolButton;
class CQExpressionWidget;
class CQExpressionMmlWidgetStack;
class CCompartment;
class CExpression;

/*!
    \brief The class for user-friendly organising all values of a chosen compartment.

 This class inherits CopasiWidget to provide an ability for editing and displaying
 all values of a chosen compartment.
 */
class CQCompartment : public CopasiWidget
  {
    Q_OBJECT

  public:
    /// Constructor
    CQCompartment(QWidget* parent = 0, const char* name = 0);
    /// Destructor
    ~CQCompartment();

    QFrame* mpLine2;
    QPushButton* mpBtnCommit;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnNew;
    QPushButton* mpBtnDelete;
    QComboBox* mpComboBoxType;
    QLineEdit* mpEditName;
    QLabel* mpLblType;
    QLabel* mpLblName;
    QListView* mpMetaboliteTable;
    QLabel* mpLblMetabolites;
    QLabel* mpLblRate;
    QLineEdit* mpEditRate;
    QLabel* mpLblVolume;
    QLineEdit* mpEditCurrentVolume;
    QLabel* mpLblExpression;
    QFrame* mpLine1;
    QLabel* mpLblInitialValue;
    QLineEdit* mpEditInitialVolume;
    QCheckBox* mpBoxUseInitialExpression;
    QLabel* mpLblInitialExpression;

    //CQExpressionWidget* mpEditInitialExpression;
    CQExpressionMmlWidgetStack *mpEditInitialExpression;
    QToolButton* mpBtnInitialExpressionObject;
    QToolButton* mpBtnEditInitialExpression;

    //CQExpressionWidget* mpEditExpression;
    CQExpressionMmlWidgetStack *mpEditExpression;
    QToolButton* mpBtnExpressionObject;
    QToolButton *mpBtnEditExpression;

    virtual bool enter(const std::string & key);
    virtual bool leave();
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  protected:
    QGridLayout* CQCompartmentLayout;
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
    CCompartment * mpCompartment;
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
    /// Function to load the metabolite (aka. species) table
    void loadMetaboliteTable();

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
    /// Slot for being activated whenever a metabolite (aka species) in the table is double clicked.
    void slotMetaboliteTableCurrentChanged(QListViewItem * pItem);
  };

#endif // CQCOMPARTMENT_H
