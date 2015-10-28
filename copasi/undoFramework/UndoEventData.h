// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoEventData.h
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#ifndef UNDOEVENTDATA_H_
#define UNDOEVENTDATA_H_

#include <set>
#include <QList>

#include <copasi/model/CEvent.h>
#include <copasi/undoFramework/UndoData.h>

class UndoEventAssignmentData;
class CModel;

class UndoEventData: public UndoData
{
public:


  UndoEventData(const std::string &key = "",
                const std::string &name = "",
                const std::string &type = "");

  UndoEventData(const CEvent* pEvent);

  virtual ~UndoEventData();

  /**
   * creates a new event in the given model, with
   * all the data contained in this undo data.
   *
   * @param model the model to create the event in
   * @return the newly created event
   */
  CEvent* createEventFromData(CModel* model);

  const std::string& getDelayExpression() const;

  void setDelayExpression(const std::string &mDelayExpression);

  const std::string& getPriorityExpression() const;

  void setPriorityExpression(const std::string &mPriorityExpression);

  const std::string& getTriggerExpression() const;

  void setTriggerExpression(const std::string &mTriggerExpression);

  CEvent::Type getType() const;
  void setType(CEvent::Type &mType);

  bool isDelayAssignment() const;
  void setDelayAssignment(bool delayAssignment);

  bool isFireAtInitialTime() const;
  void setFireAtInitialTime(bool fireAtInitialTime);

  bool isPersistentTrigger() const;
  void setPersistentTrigger(bool persistentTrigger);

  QList<UndoEventAssignmentData*> *getEventAssignmentData() const;

  void appendEventAssignmentData(UndoEventAssignmentData *eventAssignData);

private:
  /**
   * Event expression string.
   */
  std::string mPriorityExpression;

  /**
   * Event triger expression string.
   */
  std::string mTriggerExpression;

  /**
   * Event delay expression string.
   */
  std::string mDelayExpression;

  /**
   * Type of the event
   */
  CEvent::Type mType;

  /**
   * A Boolean flag indicating whether the calculation or the assignment should be delayed
   * in the case that a delay is present.
   */
  bool mDelayAssignment;

  /**
   * A Boolean flag indicating whether the trigger may fire at the initial time
   * if the trigger expression is true;
   */
  bool mFireAtInitialTime;

  /**
   * A Boolean flag indicating whether the trigger expression must remain true between
   * firing and executing the event.
   */
  bool mPersistentTrigger;

  /**
   * A list of assignments expressions which specify the changes made by the event.
   */
  QList < UndoEventAssignmentData *> *mEventAssignmentData;
};

#endif /* UNDOEVENTDATA_H_ */
