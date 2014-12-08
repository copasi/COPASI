// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "UndoData.h"

class UndoEventAssignmentData;

class UndoEventData: public UndoData
{
public:
  enum Type
  {
    Assignment,
    Discontinuity,
    CutPlane
  };
  UndoEventData();
  virtual ~UndoEventData();
  std::string getDelayExpression() const;
  std::string getPriorityExpression() const;
  std::string getTriggerExpression() const;
  Type getType() const;
  bool isDelayAssignment() const;
  bool isFireAtInitialTime() const;
  bool isPersistentTrigger() const;
  void setDelayAssignment(bool delayAssignment);
  void setDelayExpression(const std::string &delayExpression);
  void setPriorityExpression(const std::string &priorityExpression);
  void setFireAtInitialTime(bool fireAtInitialTime);
  void setPersistentTrigger(bool persistentTrigger);
  void setTriggerExpression(const std::string &triggerExpression);
  void setType(Type &type);
  QList<UndoEventAssignmentData*> *getEventAssignmentData() const;
  void setEventAssignmentData(QList<UndoEventAssignmentData*> *eventAssignmentData);

private:
  /**
   * Event expression string.
   */
  std::string priorityExpression;
  /**
   * Event triger expression string.
   */
  std::string triggerExpression;
  /**
   * Event delay expression string.
   */
  std::string delayExpression;

  /**
   * Type of the event
   */
  Type type;

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
