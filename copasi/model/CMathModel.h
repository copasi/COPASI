// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMathModel.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/24 19:27:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMathModel
#define COPASI_CMathModel

#include "utilities/CVector.h"

#include "copasi/model/CProcessQueue.h"
#include "copasi/model/CMathEvent.h"

class CModel;

class CMathModel
{
  // Operations
public:
  /**
   * Default constructor.
   */
  CMathModel();

  /**
   * Destructor.
   */
  ~CMathModel();

  /**
   * Compile the mathematical model based on given the model.
   * @param CModel & model
   * @return bool success
   */
  bool compile(CModel & model);

  /**
   * Prepare the mathematical model for simulation.
   * @return bool success
   */
  bool initialize();

  /**
   * Apply the events to the model.
   * bool return success
   */
  bool applyEvent(CMathEvent * pEvent);

  /**
   * Change the event status for the events which have value 1
   * @param CVector< C_INT > & events
   */
  void changeEventStatus(CVector< C_INT > & events);

  /**
   * Evaluate all trigger values for the current state of the model
   * @param CVector< double > & triggerValues
   */
  void evaluateTrigger(CVector< double > & triggerValues);

  // Attributes
private:
  /**
   * The model
   */
  CModel * mpModel;

  /**
   * The event process queue
   */
  CProcessQueue mProcessQueue;

  /**
   * List of events
   */
  std::vector< CMathEvent > mEvents;
};

#endif // COPASI_CMathModel
