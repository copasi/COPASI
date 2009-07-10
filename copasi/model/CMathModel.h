// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMathModel.h,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/10 01:22:57 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMathModel
#define COPASI_CMathModel

#include "utilities/CVector.h"
#include "utilities/CMatrix.h"

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
   * Evaluate all root values for the current state of the model. If
   * ignoreDiscrete is true discrete roots evaluate to 1.0.
   * @param CVectorCore< double > & rootValues
   * @param const bool & ignoreDiscrete
   */
  void evaluateRoots(CVectorCore< C_FLOAT64 > & rootValues,
                     const bool & ignoreDiscrete);

  /**
   * Retreive the initial time
   * @return const C_FLOAT64 & initialTime
   */
  const C_FLOAT64 & getInitialTime() const;

  /**
   * Process events scheduled at the given which a are checked for
   * equality or not
   * @param const C_FLOAT64 & time
   * @param const bool & equality
   * @param CProcessQueue::resolveSimultaneousAssignments pResolveSimultaneousAssignments
   * @return bool stateChanged
   */
  bool processQueue(const C_FLOAT64 & time,
                    const bool & equality,
                    CProcessQueue::resolveSimultaneousAssignments pResolveSimultaneousAssignments);

  /**
   * Check whether the roots which have value 1 lead to firing of
   * events and schedule them if needed.
   * @param const C_FLOAT64 & time
   * @param const bool & equality
   * @param const CVector< C_INT > & roots
   */
  void processRoots(const C_FLOAT64 & time,
                    const bool & equality,
                    const CVector< C_INT > & roots);

  /**
   * Retrieve the next execution time scheduled in the process queue
   * @return const C_FLOAT64 & processQueueExecutionTime
   */
  const C_FLOAT64 & getProcessQueueExecutionTime() const;

  /**
   * Initialize all values of the math model with their initial values.
   */
  void applyInitialValues();

  /**
   * Retrieve the number of roots used in checking for discontinuities.
   * @return size_t numRoots
   */
  size_t getNumRoots() const;

  /**
   * Retrieve a vector of root finders
   * @return const CVector< CMathTrigger::CRootFinder * > & rootFinders
   */
  const CVector< CMathTrigger::CRootFinder * > & getRootFinders() const;

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

private:
  /**
   * Determine whether there are any initial roots and mark them.
   * @param CVector< C_INT > & foundRoots
   * @return bool found
   */
  bool determineInitialRoots(CVector< C_INT > & foundRoots);

  /**
   * Calculate the time derivative of all roots
   * @param CVector< C_FLOAT64 > & rootDerivatives
   */
  void calculateRootDerivatives(CVector< C_FLOAT64 > & rootDerivatives);

  /**
   * Calculate the Jacobian for the roots.
   * @param CMatrix< C_FLOAT64 > & jacobian
   */
  void calculateRootJacobian(CMatrix< C_FLOAT64 > & jacobian);

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
   * A vector indicating whether a root may only change during
   * discrete events.
   */
  CVector< bool > mRootDiscrete;

  /**
   * The sequence of refresh calls needed to calculate the current
   * root values.
   */
  std::vector< Refresh * > mRootRefreshes;

  /**
   * A map from the index of a root value to the associated event
   */
  CVector< CMathEvent * > mRootIndex2Event;

  /**
   * A map from the index of a root value to the associated root finder
   */
  CVector< CMathTrigger::CRootFinder * > mRootIndex2RootFinder;
};

#endif // COPASI_CMathModel
