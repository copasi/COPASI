// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

class UndoEventAssignmentData: public UndoData
{
public:
  UndoEventAssignmentData();
  virtual ~UndoEventAssignmentData();
  std::string getTargetKey() const;
  void setTargetKey(const std::string & targetKey);
  std::string getExpression() const;
  void setExpression(const std::string &expression);
private:
  /**
  * Event assignment targey key string.
  */
  std::string mTargetKey;
  /**
  * Event assignment expression string.
  */
  std::string mExpression;
};

#endif /* UNDOEVENTASSIGNMENTDATA_H_ */
