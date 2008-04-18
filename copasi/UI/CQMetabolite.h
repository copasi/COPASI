// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.h,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/04/18 08:38:22 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQMetabolite.ui'
 **
 ** Created: Fri Apr 18 10:02:22 2008
 **      by: The User Interface Compiler ($Id: CQMetabolite.h,v 1.13 2008/04/18 08:38:22 pwilly Exp $)
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
class CQExpressionMmlWidget;
class QPushButton;
class QLabel;
class QLineEdit;
class QComboBox;
class QFrame;
class QCheckBox;
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
    QLabel* mpLblExpression;
    QLabel* mpLblReactions;
    QListView* mpReactionTable;
    QLineEdit* mpEditCurrentValue;
    QLineEdit* mpEditRate;
    QLineEdit* mpEditTransitionTime;
    QLabel* mpLblValue;
    QLabel* mpLblTransitionTime;
    QLabel* mpLblRate;
    QFrame* mpLine2;
    CQExpressionMmlWidget* mpExpressionEMW;
    CQExpressionMmlWidget* mpInitialExpressionEMW;

    virtual bool enter(const std::string & key);
    virtual bool leave();
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual void setFramework(int framework);

  protected:
    QGridLayout* CQMetaboliteLayout;
    QSpacerItem* mpSpacer;
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
    bool mExpressionValid;
    bool mInitialExpressionValid;

    QPixmap image0;

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
