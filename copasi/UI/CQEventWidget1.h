// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEventWidget1.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/06 11:55:37 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQEventWidget1.ui'
 **
 ** Created: Mon Jun 2 11:10:24 2008
 **      by: The User Interface Compiler ($Id: CQEventWidget1.h,v 1.2 2008/06/06 11:55:37 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQEVENTWIDGET1_H
#define CQEVENTWIDGET1_H

#include <qvariant.h>
#include <qpixmap.h>
#include <string>
#include <vector>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class CQExpressionMmlWidget;
class MyLineEdit;
class QLabel;
class QPushButton;
class QFrame;
class QComboBox;
class QToolButton;
class CQExpressionWidget;
class CCompartment;
class CExpression;
class CEvent;

class CQEventWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQEventWidget1(QWidget* parent = 0, const char* name = 0);
    ~CQEventWidget1();

    QLabel* mpLabelTrigger;
    QLabel* mpLabelEventName;
    CQExpressionMmlWidget* mpExpressionTrigger;
    CQExpressionMmlWidget* mpExpressionDelay;
    QLabel* mpLabelDelay;
    MyLineEdit* mpLineEditName;
    QLabel* mpLabelEA;
    QLabel* mpLabelTarget;
    QPushButton* mpBtnCommit;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnNew;
    QPushButton* mpBtnDelete;
    QFrame* mpLine1;
    QFrame* mpLine2;
    CQExpressionMmlWidget* mpExpressionEA;
    QComboBox* mpCBTarget;
    QToolButton* mpBtnSelectObject;
    QToolButton* mpBtnAddTarget;
    QToolButton* mpBtnDeleteTarget;
    QToolButton* mpBtnSaveTarget;

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool enter(const std::string & key);
    virtual bool leave();

  protected:
    bool loadFromEvent(const CEvent * pEvent);
    bool loadFromEvent();
    void saveToEvent();
    void enableBtnCommit();

    QGridLayout* CQEventWidget1Layout;
    QHBoxLayout* mpBtnLayout;
    QHBoxLayout* layout3;
    QSpacerItem* mpSpacerOnTarget;

  protected slots:
    virtual void languageChange();

  private:
    bool mExpressionTriggerValid;
    bool mExpressionDelayValid;
    bool mExpressionEAValid;
    bool mObjectOK;
    QString mEAName;
    bool mChanged;
    CEvent *mpEvent;
    std::string mEventKey;
    std::string mAssignmentKey;
    CCompartment *mpCompartment;
    unsigned C_INT32 mPosDelete;
    std::vector< int > mItemToType;
    std::vector<std::pair<std::string, CExpression> > mCurrentAssignment;
    std::vector<std::pair<std::string, std::string> > mObjectKeyDisplayName;
    std::pair<unsigned C_INT32, std::string> mDeletedAssign;
    std::vector<std::string> mTargetList;

    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;

    void init();
    void writeExpressionAsText();
    std::string takeObjectName(QString text);

  private slots:
    void slotBtnCommitClicked();
    void slotBtnDeleteClicked();
    void slotBtnNewClicked();
    void slotBtnRevertClicked();
    virtual void slotNameChanged();
    void slotExpressionDelayValid(bool valid);
    void slotExpressionTriggerValid(bool valid);
    void slotExpressionEAValid(bool valid);
    void slotAddTarget();
    void slotDeleteTarget();
    void slotSaveTarget();
    void slotSelectObject();
    void slotActualizeAssignmentExpression(int index);
  };

#endif // CQEVENTWIDGET1_H
