// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

class UndoEventData;
#include <copasi/undoFramework/CCopasiUndoCommand.h>

#include <QtCore/QVariant>

#include "ui_CQEventWidget1.h"

#include "copasi/model/CEvent.h"
#include "copasi/core/CDataVector.h"

class CQExpressionWidget;
class CCompartment;
class CExpression;

class CQEventWidget1 : public CopasiWidget, public Ui::CQEventWidget1
{
  Q_OBJECT

  friend class DeleteEventCommand;
  friend class CreateNewEventCommand;

public:
  CQEventWidget1(QWidget* parent = 0, const char* name = 0);
  ~CQEventWidget1();

  virtual bool leave();

  /**
   * finds the delay type index for the given event:
   *
   * * 0 -> no delay
   * * 1 -> delayed assignments
   * * 2 -> delayed calculation and assignment
   *
   * @param event the event to look at
   * @return the delay type index
   */
  static int getDelayTypeIndex(CEvent* event);

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);

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
  CDataVector< CEventAssignment > mAssignments;

  void init();
  bool loadFromEvent();
  void saveToEvent();
  void showDelayExpression(bool display);
  CCommonName mObjectCNToCopy;

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
  void deleteEvent();
  void addEvent(UndoEventData *pSData);
  void createNewEvent();
  void deleteEvent(UndoEventData *pSData);

public:
  bool changeValue(const std::string& key,
                   CCopasiUndoCommand::Type type,
                   const QVariant& newValue,
                   const std::string& expression = "");
};

#endif // CQEVENTWIDGET1_H
