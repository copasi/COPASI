// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartment.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/04/18 08:39:06 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQCompartment.ui'
 **
 ** Created: Fri Apr 18 10:09:27 2008
 **      by: The User Interface Compiler ($Id: CQCompartment.h,v 1.6 2008/04/18 08:39:06 pwilly Exp $)
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
class CQExpressionMmlWidget;
class QPushButton;
class QComboBox;
class QLineEdit;
class QLabel;
class QFrame;
class QCheckBox;
class QListView;
class QListViewItem;
class CQExpressionWidget;
class CCompartment;
class CExpression;

class CQCompartment : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQCompartment(QWidget* parent = 0, const char* name = 0);
    ~CQCompartment();

    QPushButton* mpBtnCommit;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnNew;
    QPushButton* mpBtnDelete;
    QComboBox* mpComboBoxType;
    QLineEdit* mpEditName;
    QLabel* mpLblType;
    QLabel* mpLblName;
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
    CQExpressionMmlWidget* mpInitialExpressionEMW;
    CQExpressionMmlWidget* mpExpressionEMW;
    QFrame* mpLine2;
    QListView* mpMetaboliteTable;

    virtual bool enter(const std::string & key);
    virtual bool leave();
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  protected:
    QGridLayout* CQCompartmentLayout;
    QSpacerItem* mpSpacer;
    QHBoxLayout* mpBtnLayout;

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
