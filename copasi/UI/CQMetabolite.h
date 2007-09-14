// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/09/14 15:29:50 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQMetabolite.ui'
 **
 ** Created: Wed Sep 12 15:43:06 2007
 **      by: The User Interface Compiler ($Id: CQMetabolite.h,v 1.5 2007/09/14 15:29:50 shoops Exp $)
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
class QLabel;
class QLineEdit;
class QComboBox;
class QToolButton;
class QListView;
class QListViewItem;
class QFrame;
class QPushButton;
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

    QLabel* mpLblTransientValue;
    QLabel* mpLblName;
    QLabel* mpLblCompartment;
    QLineEdit* mpEditRate;
    QComboBox* mpComboBoxCompartment;
    QLabel* mpLblType;
    QLabel* mpLblInitialValue;
    QComboBox* mpComboBoxInitialType;
    QLabel* mpLblTransitionTime;
    QLabel* mpLblExpression;
    CQExpressionWidget* mpEditExpression;
    QToolButton* mpBtnObject;
    QListView* mpReactionTable;
    QFrame* mpLine1;
    QLabel* mpLblValue;
    QComboBox* mpComboBoxType;
    QLineEdit* mpEditName;
    QLineEdit* mpEditTransitionTime;
    QLabel* mpLblRate;
    QLabel* mpLblReactions;
    QPushButton* mpBtnToggle;
    QLineEdit* mpEditCurrentValue;
    QLineEdit* mpEditInitialValue;
    QComboBox* mpComboBoxInitialSelection;
    QFrame* mpLine2;
    QPushButton* mpBtnCommit;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnNew;
    QPushButton* mpBtnDelete;

    virtual bool enter(const std::string & key);
    virtual bool leave();
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  protected:
    QVBoxLayout* CQMetaboliteLayout;
    QSpacerItem* mpSpacer;
    QGridLayout* layout8;
    QHBoxLayout* mpLayoutInitialValues;
    QHBoxLayout* mpHBoxLayout;
    QVBoxLayout* mpVBoxLayout;
    QSpacerItem* mpSpacerObject;
    QVBoxLayout* mpLayoutInitialConcentration;
    QHBoxLayout* mpBtnLayout;

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
    bool mShowConcentration;

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
    void slotInitialTypeChanged(int);
    void slotInitialAssignment(int);
    void slotNameLostFocus();
    void slotExpressionValid(bool valid);
    void slotReactionTableCurrentChanged(QListViewItem * pItem);
    void slotInitialValueLostFocus();
    void slotToggleDisplay();
  };

#endif // CQMETABOLITE_H
