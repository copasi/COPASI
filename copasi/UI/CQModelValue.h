// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQModelValue.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/09 06:05:18 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQModelValue.ui'
 **
 ** Created: Mon Apr 21 11:34:57 2008
 **      by: The User Interface Compiler ($Id: CQModelValue.h,v 1.14 2008/06/09 06:05:18 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQMODELVALUE_H
#define CQMODELVALUE_H

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
class QComboBox;
class QLineEdit;
class QLabel;
class QCheckBox;
class QFrame;
class CQExpressionWidget;
class CModelValue;
class CExpression;

class CQModelValue : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQModelValue(QWidget* parent = 0, const char* name = 0);
    ~CQModelValue();

    QPushButton* mpBtnCommit;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnNew;
    QPushButton* mpBtnDelete;
    QComboBox* mpComboBoxType;
    QLineEdit* mpEditName;
    QLabel* mpLblType;
    QLabel* mpLblName;
    QLabel* mpLblRate;
    QLabel* mpLblValue;
    QLineEdit* mpEditCurrentValue;
    QLabel* mpLblExpression;
    QLabel* mpLblInitialValue;
    QLineEdit* mpEditInitialValue;
    QCheckBox* mpBoxUseInitialExpression;
    QLabel* mpLblInitialExpression;
    QFrame* mpLine1;
    QLineEdit* mpEditRate;
    QFrame* mpLine2;
    CQExpressionMmlWidget* mpInitialExpressionEMW;
    CQExpressionMmlWidget* mpExpressionEMW;

    virtual bool leave();
    virtual bool enter(const std::string & key);
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  protected:
    QGridLayout* CQModelValueLayout;
    QSpacerItem* mpSpacer;
    QHBoxLayout* mpBtnLayout;

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

    void init();
    void destroy();
    void load();
    void save();

  private slots:
    void slotBtnCommit();
    void slotBtnRevert();
    void slotBtnNew();
    void slotBtnDelete();
    void slotTypeChanged(int type);
    void slotExpressionValid(bool valid);
    void slotInitialExpressionValid(bool valid);
    void slotNameLostFocus();
    void slotInitialTypeChanged(bool useInitialAssignment);
  };

#endif // CQMODELVALUE_H
