// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQModelValue.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/03/26 02:51:56 $
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
 **      by: The User Interface Compiler ($Id: CQModelValue.h,v 1.9 2008/03/26 02:51:56 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQMODELVALUE_H
#define CQMODELVALUE_H

#include <qvariant.h>
#include <qpixmap.h>
#include <string>
#include "copasiWidget.h"
#include "CQExpressionMmlWidgetStack.h"

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
class FunctionWidget2;
//class Form1;
class CModelValue;
class CExpression;

class CQModelValue : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQModelValue(QWidget* parent = 0, const char* name = 0);
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
    CQExpressionWidget* mpEditInitialExpression;
    QToolButton* mpBtnInitialExpressionObject;
    //    CQExpressionWidget* mpEditExpression;
    //    QTextEdit* mpEditFcnExpression;
    /*
        QWidgetStack* mpEditFcnExpression;
        QTextEdit *mpTextEditExpression;
    */
    // FunctionWidget2 *mpEditFcnExpression;
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

    void init();
    void load();
    void save();
    void destroy();

  private slots:
    /// Slot for being activated whenever the Commit button is clicked
    void slotBtnCommit();
    ///
    void slotBtnRevert();
    ///
    void slotBtnNew();
    ///
    void slotBtnDelete();
    ///
    void slotTypeChanged(int type);
    ///
    void slotInitialTypeChanged(bool useInitialAssignment);
    ///
    void slotNameLostFocus();
    ///
    void slotExpressionValid(bool valid);
    ///
    void slotInitialExpressionValid(bool valid);
    ///
    void slotEditExpression();
  };

#endif // CQMODELVALUE_H
