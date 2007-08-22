// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartment.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/08/22 12:59:17 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQCompartment.ui'
 **
 ** Created: Wed Aug 22 08:37:01 2007
 **      by: The User Interface Compiler ($Id: CQCompartment.h,v 1.1 2007/08/22 12:59:17 shoops Exp $)
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
class QLabel;
class QComboBox;
class QLineEdit;
class QListView;
class QListViewItem;
class QFrame;
class QToolButton;
class QPushButton;
class CQExpressionWidget;
class CCompartment;
class CExpression;

class CQCompartment : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQCompartment(QWidget* parent = 0, const char* name = 0);
    ~CQCompartment();

    QLabel* mpLblVolume;
    QComboBox* mpComboBoxType;
    QLineEdit* mpEditName;
    QLabel* mpLblMetabolites;
    QListView* mpMetaboliteTable;
    QLabel* mpLblType;
    QLineEdit* mpEditCurrentVolume;
    QFrame* mpLine1;
    QLabel* mpLblName;
    QLabel* mpLblRate;
    QLineEdit* mpEditInitialVolume;
    QComboBox* mpComboBoxInitialSelection;
    QLineEdit* mpEditRate;
    CQExpressionWidget* mpEditExpression;
    QToolButton* mpBtnObject;
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
    QVBoxLayout* CQCompartmentLayout;
    QSpacerItem* mpSpacer;
    QGridLayout* mpGridLayout;
    QVBoxLayout* mpLayoutInitialVolume;
    QHBoxLayout* mpHBoxLayout;
    QVBoxLayout* mpVBoxLayout;
    QSpacerItem* mpSpacerObject;
    QHBoxLayout* mpLayoutInitialValues;
    QHBoxLayout* mpBtnLayout;

  protected slots:
    virtual void languageChange();

  private:
    std::vector< int > mItemToType;
    CCompartment * mpCompartment;
    std::string mKey;
    bool mChanged;

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
    void slotInitialTypeChanged(int);
    void slotInitialAssignment(int);
    void slotNameLostFocus();
    void slotExpressionValid(bool valid);
    void slotMetaboliteTableCurrentChanged(QListViewItem * pItem);
  };

#endif // CQCOMPARTMENT_H
