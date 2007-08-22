// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/08/22 19:52:19 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQMetabolite.ui'
 **
 ** Created: Wed Aug 22 15:27:05 2007
 **      by: The User Interface Compiler ($Id: CQMetabolite.h,v 1.4 2007/08/22 19:52:19 shoops Exp $)
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
class QLineEdit;
class QLabel;
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

    QLineEdit* mpEditName;
    QLabel* mpLblName;
    QComboBox* mpComboBoxCompartment;
    QLabel* mpLblCompartment;
    QLabel* mpLblType;
    QComboBox* mpComboBoxType;
    QLabel* mpLblInitialValue;
    QComboBox* mpComboBoxInitialType;
    QLabel* mpLblTransientValue;
    QLabel* mpLblConcentration;
    QLineEdit* mpEditCurrentConcentration;
    QLineEdit* mpEditInitialConcentration;
    QComboBox* mpComboBoxInitialSelection;
    QLabel* mpLblNumber;
    QLineEdit* mpEditInitialNumber;
    QLineEdit* mpEditCurrentNumber;
    QLineEdit* mpEditTransitionTime;
    QLabel* mpLblTransitionTime;
    QLineEdit* mpEditConcentrationRate;
    QLabel* mpLblConcentrationRate;
    CQExpressionWidget* mpEditExpression;
    QToolButton* mpBtnObject;
    QLabel* mpLblExpression;
    QLabel* mpLblReactions;
    QListView* mpReactionTable;
    QFrame* mpLine2;
    QPushButton* mpBtnCommit;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnNew;
    QPushButton* mpBtnDelete;
    QFrame* mpLine1;

    virtual bool enter(const std::string & key);
    virtual bool leave();
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  protected:
    QGridLayout* CQMetaboliteLayout;
    QSpacerItem* mpSpacer;
    QHBoxLayout* mpLayoutInitialValues;
    QVBoxLayout* mpLayoutInitialConcentration;
    QHBoxLayout* mpHBoxLayout;
    QVBoxLayout* mpVBoxLayout;
    QSpacerItem* mpSpacerObject;
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
    void slotInitialConcentrationLostFocus();
    void slotInitialNumberLostFocus();
  };

#endif // CQMETABOLITE_H
