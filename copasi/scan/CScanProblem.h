// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanProblem.h,v $
//   $Revision: 1.29.24.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/12 19:06:14 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CScanProblem class.
 */

#ifndef COPASI_CScanProblem
#define COPASI_CScanProblem

#include <string>

#include "utilities/CCopasiProblem.h"
#include "utilities/CReadConfig.h"
//#include "model/CState.h"

//class CModel;

class CScanProblem : public CCopasiProblem
{
public:
  enum Type
  {
    SCAN_REPEAT = 0,
    SCAN_LINEAR,
    SCAN_RANDOM,
    SCAN_BREAK,
    SD_UNIFORM,
    SD_GAUSS,
    SD_BOLTZ,
    SD_REGULAR
  };

private:

  /**
   *  This holds the scan items
   */
  CCopasiParameterGroup * mpScanItems;

public:

  /**
   * Default constructor.
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CScanProblem(const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor.
   * @param const CTrajectoryProblem & src
   * @paramconst CCopasiContainer * pParent (default: NULL)
   */
  CScanProblem(const CScanProblem & src,
               const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CScanProblem();

  /**
   *  Set the type of the subtask.
   */
  void setSubtask(CCopasiTask::Type type);

  /**
   *  Get the type of the subtask.
   */
  CCopasiTask::Type getSubtask() const;

  /**
   *  Set if output should be done after every step of the subtask.
   */
  void setOutputInSubtask(bool ois);

  /**
   *  Ask if output should be done after every step of the subtask.
   */
  const bool & getOutputInSubtask() const;

  /**
   *  Set if initial conditions should be set to the result of the previous run.
   */
  void setAdjustInitialConditions(bool aic);

  /**
   *  Ask if initial conditions should be set to the result of the previous run.
   */
  const bool & getAdjustInitialConditions() const;

  size_t getNumberOfScanItems() const;

  const CCopasiParameterGroup* getScanItem(size_t index) const;
  CCopasiParameterGroup* getScanItem(size_t index);

  CScanProblem::Type getScanItemType(size_t index);

  CCopasiParameterGroup* createScanItem(CScanProblem::Type type, size_t steps = 5, const CCopasiObject* obj = NULL);

  void clearScanItems();

  /**
   * Load a scan problem
   * @param "CReadConfig &" configBuffer
   * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
   */
  void load(CReadConfig & configBuffer,
            CReadConfig::Mode mode = CReadConfig::NEXT);
};

#endif
