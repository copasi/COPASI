// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMathModel.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/05/21 15:34:38 $
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

class CMathModel : public CCopasiContainer
{
  // Operations
public:
  /**
   * Default constructor
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CMathModel(const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param "const CMathModel &" src
   * @param "const CCopasiContainer * pParent (default: NULL)
   */
  CMathModel(const CMathModel & src,
             const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~CMathModel();

  /**
   * Compile the mathematical model based on given the model.
   * @param CModel * pModel
   * @return bool success
   */
  bool compile(CModel * pModel);

  /**
   * Prepare the mathematical model for simulation.
   * @return bool success
   */
  bool initialize();

  /**
   * Evaluate all root values for the current state of the model
   * @param CVector< double > & triggerValues
   */
  void evaluateRoots(CVector< double > & rootValues);

  /**
   * Process events scheduled at the given which a are checked for
   * equality or not
   * @param const C_FLOAT64 & time
   * @param const bool & equality
   */
  void processQueue(const C_FLOAT64 & time, const bool & equality);

  /**
  * Check whether the roots which have value 1 lead to firing of
  * events and schedule them if needed.
  * @param const CVector< C_INT > & roots
  */
  void processRoots(const CVector< C_INT > & roots);

  /**
   * Retrieve the next execution time scheduled in the process queue
   * @return const C_FLOAT64 & processQueueExecutionTime
   */
  const C_FLOAT64 & getProcessQueueExecutionTime() const;

  /**
   * Build a list of refresh calls needed to assure that required objects
   * are up to date.
   * @param const std::set< const CCopasiObject * > & requiredObjects
   * @return std::vector< Refresh * > refreshList
   */
  std::vector< Refresh * > buildRequiredRefreshList(const std::set< const CCopasiObject * > & requiredObjects) const;

  /**
   * Build a list of refresh calls needed to assure that all objects
   * depending on the changed objects are up to date.
   * @param const std::set< const CCopasiObject * > & changedObjects
   * @return std::vector< Refresh * > refreshList
   */
  std::vector< Refresh * > buildDependendRefreshList(const std::set< const CCopasiObject * > & changedObjects) const;

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
  CCopasiVector< CMathEvent > mEvents;

  /**
   * A vector of pointers to the current root finder values
   */
  CVector< C_FLOAT64 *> mRootValues;

  /**
   * The sequence of refresh calls needed to calculate the current
   * root values.
   */
  std::vector< Refresh * > mRootRefreshes;

  /**
   * A map from the index of a root value to the associated event
   */
  CVector< CMathEvent * > mRootIndex2Event;
};

#endif // COPASI_CMathModel
