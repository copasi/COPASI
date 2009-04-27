// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEventWidget1.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/27 00:03:17 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEVENTWIDGET1_H
#define CQEVENTWIDGET1_H

#include <qvariant.h>

#include "ui_CQEventWidget1.h"

class CQExpressionWidget;
class CCompartment;
class CExpression;
class CEvent;
class CEventAssignment;

class CQEventWidget1 : public CopasiWidget, public Ui::CQEventWidget1
{
  Q_OBJECT

public:
  CQEventWidget1(QWidget* parent = 0, const char* name = 0);
  ~CQEventWidget1();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool enter(const std::string & key);
  virtual bool leave();

protected slots:
  virtual void languageChange();

private:
  bool mExpressionTriggerValid;
  bool mExpressionDelayValid;
  bool mExpressionEAValid;
  QString mEAName;
  bool mChanged;
  CEvent *mpEvent;
  std::string mEventKey;
  std::string mAssignmentKey;
  unsigned C_INT32 mCurrentTarget;
  std::vector< CEventAssignment > mAssignments;

  void init();
  bool loadFromEvent();
  void saveToEvent();

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
  void slotSelectObject();
  void slotActualizeAssignmentExpression(int index);
  void slotApplyDelay(bool display);
};

#endif // CQEVENTWIDGET1_H
