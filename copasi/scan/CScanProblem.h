// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

  enum struct OutputType
  {
    subTaskNone = 0,
    subTaskBefore,
    subTaskDuring,
    subTaskAfter,
    __SIZE
  };

  static const CEnumAnnotation< std::string, OutputType > OutputTypeName;
  typedef CFlags< OutputType > OutputFlags;

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
   * @param const CDataContainer * pParent (default: NULL)
   */
  CScanProblem(const CScanProblem & src,
               const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CScanProblem();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  bool elevateChildren() override;

  /**
   * Retrieve the optional sub task
   *
   * @return CCopasiTask* * pSubTask
   */
  CCopasiTask * getSubTask() const override;

  /**
   *  Set the type of the subtask.
   */
  void setSubtask(CTaskEnum::Task type);

  /**
   *  Get the type of the subtask.
   */
  CTaskEnum::Task getSubtask() const;

  /**
   * This function is here for backwards compatibility
   *
   * @return true, if output for subtask is set to during (old behavior)
   */
  bool getOutputInSubtask() const;

  /**
   * Returns the output specification for the subtask as CFlag enum
   *
   * @return the output specification for the subtask as CFlag enum
   */
  OutputFlags getOutputSpecification() const;

  /**
   * Get the Output Specification String
   *
   * This will be a `|` separated string of the output flags
   * for example: `none` or `subTaskBefore|subTaskDuring|subTaskAfter`
   *
   * @return std::string of the combined output flags
   */
  std::string getOutputSpecificationString() const;

  /**
   *  Set the output for the subtask to `subTaskDuring`, the method
   *  is here for backwards compatibility
   */
  void setOutputInSubtask(bool outputDuring);

  /**
   * sets the specification for output during the subtask execution
   *
   * @param outputSpecification flags
   */
  void setOutputSpecification(const OutputFlags & outputSpecification);

  /**
   * sets the specification for output during the subtask execution
   *
   * @param specification string of the form `none` or `subTaskBefore|subTaskDuring|subTaskAfter`
   */
  void setOutputSpecification(const std::string& specification);

  /**
   * sets the specification for output during the subtask execution
   *
   * @param specification vector of string specifying when to collect output from subtask.
   * Valid strings are `none`, `subTaskBefore`, `subTaskDuring`, `subTaskAfter`.
   */
  void setOutputSpecification(const std::vector< std::string > & specification);

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

  /**
   * @return number of scan items
   */
  size_t getNumberOfScanItems() const;

  /**
   * @return the scan item at the given index
   */
  const CCopasiParameterGroup* getScanItem(size_t index) const;

  /**
   * @return the scan item at the given index
   */
  CCopasiParameterGroup* getScanItem(size_t index);

  /**
   * add a scan item
   *
   * @param type the type of the scan item
   * @param steps number of steps
   * @param obj the object to change
   * @return CCopasiParameterGroup* the newly added parameter group
   */
  CCopasiParameterGroup* addScanItem(CScanProblem::Type type, size_t steps = 5, const CDataObject* obj = NULL);

  /**
   * remove a scan item
   *
   * @param index the index of the scan item to remove
   */
  bool removeScanItem(const size_t & index);

  /**
   * creates a new scan item
   *
   * @param type the type of the scan item
   * @param steps number of steps
   * @param obj the object to change
   * @return CCopasiParameterGroup* the newly created parameter group
   */
  static CCopasiParameterGroup* createScanItem(CScanProblem::Type type, size_t steps = 5, const CDataObject* obj = NULL);

  /**
   * removes all scan items
   */
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
  bool restore(const bool & updateModel) override;

private:
  /**
   * Initialize the method parameter
   */
  void initializeParameter();
};

#endif
