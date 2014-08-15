// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
    SCAN_BREAK
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
   *  Set whether the subtask should continue with its last result.
   */
  void setContinueFromCurrentState(bool aic);

  /**
   *  Retrieve whether the subtask should continue with its last result.
   */
  bool getContinueFromCurrentState() const;

  size_t getNumberOfScanItems() const;

  const CCopasiParameterGroup* getScanItem(size_t index) const;
  CCopasiParameterGroup* getScanItem(size_t index);

  CCopasiParameterGroup* addScanItem(CScanProblem::Type type, size_t steps = 5, const CCopasiObject* obj = NULL);

  bool removeScanItem(const size_t & index);

  static CCopasiParameterGroup* createScanItem(CScanProblem::Type type, size_t steps = 5, const CCopasiObject* obj = NULL);

  void clearScanItems();

  /**
   * Load a scan problem
   * @param "CReadConfig &" configBuffer
   * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
   */
  void load(CReadConfig & configBuffer,
            CReadConfig::Mode mode = CReadConfig::NEXT);

  /**
   * Fix files written with Version 4.12.81 and earlier, which wrote the exp(mean) and exp(std. deviation) for
   * normal random distributions in the scan task.
   */
  void fixBuild81();

private:
  /**
   * Initialize the method parameter
   */
  void initializeParameter();
};

#endif
