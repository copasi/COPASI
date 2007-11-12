// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/12 21:06:47 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQMetabolite.ui'
 **
 ** Created: Mon Nov 12 15:15:21 2007
 **      by: The User Interface Compiler ($Id: CQMetabolite.h,v 1.10 2007/11/12 21:06:47 shoops Exp $)
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
class CQExpressionWidget;
class QFrame;
class QPushButton;
class QLabel;
class QLineEdit;
class QComboBox;
class QCheckBox;
class QToolButton;
class QListView;
class QListViewItem;
class CQExpressionWidget;
class CMetab;
class CCompartment;
class CExpression;

class CQMetabolite : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQMetabolite(QWidget* parent = 0, const char* name = 0);
    ~CQMetabolite();

    QFrame* mpLine2;
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
    CQExpressionWidget* mpEditInitialExpression;
    QToolButton* mpBtnObjectInitialExpression;
    QLabel* mpLblExpression;
    CQExpressionWidget* mpEditExpression;
    QToolButton* mpBtnObjectExpression;
    QLabel* mpLblReactions;
    QListView* mpReactionTable;
    QLabel* mpLblValue;
    QLineEdit* mpEditCurrentValue;
    QLabel* mpLblRate;
    QLabel* mpLblTransitionTime;
    QLineEdit* mpEditTransitionTime;
    QLineEdit* mpEditRate;

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
    QGridLayout* layout9;

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

    void init();
    void load();
    void save();
    void destroy();
    void loadReactionTable();

  private slots:
    void slotBtnCommit();
    void slotBtnRevert();
    void slotBtnNew();
    void slotBtnDelete();
    void slotCompartmentChanged(int compartment);
    void slotTypeChanged(int type);
    void slotInitialTypeChanged(bool useInitialExpression);
    void slotNameLostFocus();
    void slotExpressionValid(bool valid);
    void slotInitialExpressionValid(bool valid);
    void slotReactionTableCurrentChanged(QListViewItem * pItem);
    void slotInitialValueLostFocus();
  };

#endif // CQMETABOLITE_H
