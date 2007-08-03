// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/08/03 13:46:40 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQMetabolite.ui'
 **
 ** Created: Fri Aug 3 09:33:09 2007
 **      by: The User Interface Compiler ($Id: CQMetabolite.h,v 1.1 2007/08/03 13:46:40 shoops Exp $)
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
class QComboBox;
class QLineEdit;
class QTable;
class QFrame;
class QToolButton;
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

    QLabel* mpLblConcentration;
    QComboBox* mpComboBoxType;
    QLineEdit* mpEditName;
    QLabel* mpLblReactions;
    QTable* mpReactionTable;
    QLabel* mpLblType;
    QLineEdit* mpEditCurrentConcentration;
    QLabel* mpLblTransitionTime;
    QLineEdit* mpEditInitialNumber;
    QFrame* mpLine1;
    QComboBox* mpComboBoxCompartment;
    QLabel* mpLblName;
    QLabel* mpLblCompartment;
    QLabel* mpLblConcentrationRate;
    QLineEdit* mpEditInitialConcentration;
    QComboBox* mpComboBoxInitialSelection;
    QLineEdit* mpEditCurrentNumber;
    QLineEdit* mpEditTransitionTime;
    QLineEdit* mpEditConcentrationRate;
    CQExpressionWidget* mpEditExpression;
    QToolButton* mpBtnObject;
    QLabel* mpLblNumber;
    QLabel* mpLblInitialValue;
    QComboBox* mpComboBoxInitialType;
    QLabel* mpLblTransientValue;
    QLabel* mpLblExpression;
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
    QGridLayout* mpGridLayout;
    QVBoxLayout* mpLayoutInitialConcentration;
    QHBoxLayout* mpHBoxLayout;
    QVBoxLayout* mpVBoxLayout;
    QSpacerItem* mpSpacerObject;
    QHBoxLayout* mpLayoutInitialValues;
    QHBoxLayout* mpBtnLayout;

  protected slots:
    virtual void languageChange();

  private:
    bool mChanged;
    bool mInitialNumberLastChanged;
    bool mIgnoreSignal;
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
    void slotInitialTypeChanged(int initialType);
    void slotInitialAssignment(int initialAssignment);
    void slotNameLostFocus();
    void slotExpressionValid(bool valid);
    void slotReactionTableCurrentChanged(int, int, int, const QPoint &);
    void slotInitialConcentrationChanged(const QString & newValue);
    void slotInitialNumberChanged(const QString & newValue);
  };

#endif // CQMETABOLITE_H
