// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoEventAssignmentData.h
 *
 *  Created on: 20 Nov 2014
 *      Author: dada
 */

#ifndef UNDOEVENTASSIGNMENTDATA_H_
#define UNDOEVENTASSIGNMENTDATA_H_

#include "UndoData.h"

class CModel;
class CEvent;

class UndoEventAssignmentData: public UndoData
{
public:
  UndoEventAssignmentData();

  virtual ~UndoEventAssignmentData();

  const std::string& getExpression() const;

  void setExpression(const std::string &expression);

  /**
   * Adds the event assignment to the given event
   * @param pEvent the event to add the assignment to
   * @param pModel the model that contains the references
   */
  void addToEvent(CEvent* pEvent, CModel* pModel) const;

private:
  /**
  * Event assignment expression string.
  */
  std::string mExpression;
};

#endif /* UNDOEVENTASSIGNMENTDATA_H_ */
