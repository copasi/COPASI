// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartment.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/13 14:46:02 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQCompartment.ui'
 **
 ** Created: Tue Nov 13 09:15:08 2007
 **      by: The User Interface Compiler ($Id: CQCompartment.h,v 1.4 2007/11/13 14:46:02 shoops Exp $)
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
class CQExpressionWidget;
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
class CCompartment;
class CExpression;

class CQCompartment : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQCompartment(QWidget* parent = 0, const char* name = 0);
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
    CQExpressionWidget* mpEditInitialExpression;
    QToolButton* mpBtnInitialExpressionObject;
    CQExpressionWidget* mpEditExpression;
    QToolButton* mpBtnExpressionObject;

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

    void init();
    void load();
    void save();
    void destroy();
    void loadMetaboliteTable();

  private slots:
    void slotBtnCommit();
    void slotBtnRevert();
    void slotBtnNew();
    void slotBtnDelete();
    void slotTypeChanged(int type);
    void slotInitialTypeChanged(bool useInitialAssignment);
    void slotNameLostFocus();
    void slotExpressionValid(bool valid);
    void slotInitialExpressionValid(bool valid);
    void slotMetaboliteTableCurrentChanged(QListViewItem * pItem);
  };

#endif // CQCOMPARTMENT_H
