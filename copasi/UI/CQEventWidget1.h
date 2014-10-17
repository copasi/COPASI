// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

#ifndef CQEVENTWIDGET1_H
#define CQEVENTWIDGET1_H


#ifdef COPASI_UNDO
class UndoEventData;
#endif

#include <QtCore/QVariant>

#include "ui_CQEventWidget1.h"

#include "copasi/model/CEvent.h"
#include "copasi/utilities/CCopasiVector.h"

class CQExpressionWidget;
class CCompartment;
class CExpression;

class CQEventWidget1 : public CopasiWidget, public Ui::CQEventWidget1
{
  Q_OBJECT


#ifdef COPASI_UNDO
  friend class DeleteEventCommand;
  friend class CreateNewEventCommand;
#endif

public:
  CQEventWidget1(QWidget* parent = 0, const char* name = 0);
  ~CQEventWidget1();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected:
  virtual bool enterProtected();

protected slots:

private:
  bool mExpressionTriggerValid;
  bool mExpressionDelayValid;
  bool mExpressionEAValid;
  QString mEAName;
  bool mChanged;
  CEvent *mpEvent;
  std::string mAssignmentKey;
  size_t mCurrentTarget;
  CCopasiVector< CEventAssignment > mAssignments;

  void init();
  bool loadFromEvent();
  void saveToEvent();
  void showDelayExpression(bool display);
  std::string mKeyToCopy;

private slots:
  void slotBtnNew();
  void slotBtnCopy();
  void slotBtnDelete();
  void slotAddTarget();
  void slotDeleteTarget();
  void slotSelectObject();
  void slotActualizeAssignmentExpression(int index);
  void slotChooseDelay(int choice);

  //additional functions for UNDO framework
#ifdef COPASI_UNDO
  void deleteEvent();
  void addEvent(UndoEventData *pSData);
  void createNewEvent();
  void deleteEvent(UndoEventData *pSData);
  void eventTypeChanged(int type);
#endif
};

#endif // CQEVENTWIDGET1_H
