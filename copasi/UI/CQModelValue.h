/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQModelValue.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/10 15:45:55 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQModelValue.ui'
 **
 ** Created: Thu Aug 10 11:17:13 2006
 **      by: The User Interface Compiler ($Id: CQModelValue.h,v 1.2 2006/08/10 15:45:55 shoops Exp $)
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
class QLabel;
class CQExpressionWidget;
class QToolButton;
class QLineEdit;
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

    QLabel* mpLblName;
    CQExpressionWidget* mpEditExpression;
    QToolButton* mpBtnObject;
    QLabel* mpLblInitialValue;
    QLabel* mpLblType;
    QLineEdit* mpEditInitialValue;
    QComboBox* mpComboBoxType;
    QFrame* mpLine1;
    QLineEdit* mpEditName;
    QLabel* mpLblExpression;
    QLabel* mpLblCurrentValue;
    QLineEdit* mpEditCurrentValue;
    QFrame* mpLine2;
    QPushButton* mpBtnCommit;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnNew;
    QPushButton* mpBtnDelete;

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected:
    bool mChanged;
    std::string mKey;
    CModelValue * mpModelValue;
    std::vector< unsigned int > mItemToType;

    QVBoxLayout* CQModelValueLayout;
    QSpacerItem* mpSpacer;
    QGridLayout* layout8;
    QHBoxLayout* mpHBoxLayout;
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
  };

#endif // CQMODELVALUE_H
