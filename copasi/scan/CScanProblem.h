// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
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

#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/utilities/CReadConfig.h"
//#include "copasi/model/CState.h"

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
    SCAN_PARAMETER_SET
  };

private:

  /**
   *  This holds the scan items
   */
  CCopasiParameterGroup * mpScanItems;

public:

  /**
   * Default constructor.
   * @param const CDataContainer * pParent (default: NULL)
   */
  CScanProblem(const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor.
   * @param const CTrajectoryProblem & src
   * @paramconst CDataContainer * pParent (default: NULL)
   */
  CScanProblem(const CScanProblem & src,
               const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CScanProblem();

  /**
   * Retrieve the optional sub task
   *
   * @return CCopasiTask* * pSubTask
   */
  virtual CCopasiTask * getSubTask() const override;

  /**
   *  Set the type of the subtask.
   */
  void setSubtask(CTaskEnum::Task type);

  /**
   *  Get the type of the subtask.
   */
  CTaskEnum::Task getSubtask() const;

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

  /**
   *  Retrieve whether the subtask should continue when an error occurs.
   */
  bool getContinueOnError() const;
  /**
   *  Set whether the subtask should continue when error occurs.
   */
  void setContinueOnError(bool coe);

  size_t getNumberOfScanItems() const;

  const CCopasiParameterGroup* getScanItem(size_t index) const;
  CCopasiParameterGroup* getScanItem(size_t index);

  CCopasiParameterGroup* addScanItem(CScanProblem::Type type, size_t steps = 5, const CDataObject* obj = NULL);

  bool removeScanItem(const size_t & index);

  static CCopasiParameterGroup* createScanItem(CScanProblem::Type type, size_t steps = 5, const CDataObject* obj = NULL);

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

  /**
   * Do all necessary restore procedures so that the
   * model is in the same state as before
   * @param const bool & updateModel
   * @result bool success
   */
  virtual bool restore(const bool & updateModel) override;

private:
  /**
   * Initialize the method parameter
   */
  void initializeParameter();
};

#endif
