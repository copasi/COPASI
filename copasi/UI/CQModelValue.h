// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQModelValue.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/09/14 15:29:50 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQModelValue.ui'
 **
 ** Created: Wed Sep 12 16:05:40 2007
 **      by: The User Interface Compiler ($Id: CQModelValue.h,v 1.6 2007/09/14 15:29:50 shoops Exp $)
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
class QLineEdit;
class QLabel;
class CQExpressionWidget;
class QToolButton;
class QComboBox;
class QFrame;
class QPushButton;
class CQExpressionWidget;
class CExpression;
class CModelValue;

class CQModelValue : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQModelValue(QWidget* parent = 0, const char* name = 0);
    ~CQModelValue();

    QLineEdit* mpEditRate;
    QLabel* mpLblRate;
    QLabel* mpLblCurrentValue;
    QLabel* mpLblExpression;
    QLabel* mpLblType;
    QLineEdit* mpEditName;
    QLineEdit* mpEditInitialValue;
    QLabel* mpLblName;
    QLabel* mpLblInitialValue;
    QLabel* mpLblValue;
    CQExpressionWidget* mpEditExpression;
    QToolButton* mpBtnObject;
    QLineEdit* mpEditCurrentValue;
    QComboBox* mpComboBoxType;
    QFrame* mpLine1;
    QFrame* mpLine2;
    QPushButton* mpBtnCommit;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnNew;
    QPushButton* mpBtnDelete;

    virtual bool leave();
    virtual bool enter(const std::string & key = "");
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  protected:
    bool mChanged;
    std::string mKey;
    CModelValue * mpModelValue;
    std::vector< unsigned int > mItemToType;

    QVBoxLayout* CQModelValueLayout;
    QSpacerItem* mpSpacer;
    QGridLayout* layout7;
    QHBoxLayout* layout6;
    QVBoxLayout* mpVBoxLayout;
    QSpacerItem* mpSpacerObject;
    QHBoxLayout* mpBtnLayout;

  protected slots:
    virtual void languageChange();

  private:
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
    void slotNameLostFocus();
  };

#endif // CQMODELVALUE_H
