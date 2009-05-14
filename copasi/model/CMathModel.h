// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMathModel.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/05/14 18:49:40 $
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
   * @param std::vector< CCopasiContainer * > listOfContainer
   * @return bool success
   */
  bool compile(CModel * pModel,
               std::vector< CCopasiContainer * > listOfContainer);

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
   * Change the root status for the roots which have value 1
   * @param CVector< C_INT > & events
   */
  void changeRootStatus(CVector< C_INT > & roots);

  /**
   * Evaluate all root values for the current state of the model
   * @param CVector< double > & triggerValues
   */
  void evaluateRoots(CVector< double > & rootValues);

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
};

#endif // COPASI_CMathModel
