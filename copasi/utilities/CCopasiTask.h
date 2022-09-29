// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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
 *  CCopasiTask class.
 *  This class is used to describe a task in COPASI. This class is
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiTask
#define COPASI_CCopasiTask

#include <string>

#include "copasi/utilities/CTaskEnum.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/output/COutputHandler.h"
#include "copasi/core/CVector.h"

#include "copasi/core/CDataContainer.h"
#include "copasi/report/CReport.h"

class CCopasiProblem;
class CCopasiMethod;
class CCopasiParameterGroup;
class CProcessReportLevel;

class CCopasiTask : public CDataContainer
{
public:
  /**
   * Check whether the given method is in the list of valid methods
   * This list must end with CCopasiMethod::unset
   * @param const CTaskEnum::Method & method
   * @param const CTaskEnum::Method * validMethods
   * @return bool isValid
   */
  static bool isValidMethod(const CTaskEnum::Method & method,
                            const CTaskEnum::Method * validMethods);

  enum eOutputFlagBase
  {
    INITIALIZE = 0x01,
    STREAM = 0x02,
    FINISH = 0x04,
    REPORT = 0x10,
    PLOT = 0x20,
    TIME_SERIES = 0x40
  };

  enum OutputFlag
  {
    //do no output
    NO_OUTPUT = 0,
    OUTPUT_BEFORE = INITIALIZE,
    OUTPUT_DURING = STREAM,
    OUTPUT_AFTER = FINISH,
    //do output except time series, but do not initialize/finish
    OUTPUT = REPORT | PLOT | STREAM,
    //do output, including initialization and closing
    OUTPUT_SE = REPORT | PLOT | INITIALIZE | STREAM | FINISH,
    OUTPUT_UI = REPORT | PLOT | TIME_SERIES | INITIALIZE | STREAM | FINISH,
    // only do time series
    ONLY_TIME_SERIES = TIME_SERIES | INITIALIZE | STREAM | FINISH
  };

  class CDescription: public CDataObject
  {
  protected:
    CDescription(const CDescription & src);

  public:
    /**
     * Default constructor
     */
    CDescription(const CDataContainer * pParent = NO_PARENT);

    /**
     * Copy constructor
     * @param const CDescription & src
     * @param const CDataContainer * pParent (default: NULL)
     */
    CDescription(const CDescription & src,
                 const CDataContainer * pParent);

    /**
     * Destructor
     */
    virtual ~CDescription();

    /**
     * This is the output method for any object. The default implementation
     * provided with CDataObject uses the ostream operator<< of the object
     * to print the object.To overide this default behaviour one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

    /**
     * Output stream operator
     * @param ostream & os
     * @param const CDescription & A
     * @return ostream & os
     */
    friend std::ostream &operator<<(std::ostream &os, const CDescription & o);
  };

  class CResult: public CDataObject
  {
  protected:
    CResult(const CResult & src);

  public:
    /**
     * Default constructor
     */
    CResult(const CDataContainer * pParent = NO_PARENT);

    /**
     * Copy constructor
     * @param const CResult & src
     * @param const CDataContainer * pParent (default: NULL)
     */
    CResult(const CResult & src,
            const CDataContainer * pParent);

    /**
     * Destructor
     */
    virtual ~CResult();

    /**
     * This is the output method for any object. The default implementation
     * provided with CDataObject uses the ostream operator<< of the object
     * to print the object.To overide this default behaviour one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

    /**
     * Output stream operator
     * @param ostream & os
     * @param const CResult & A
     * @return ostream & os
     */
    friend std::ostream &operator<<(std::ostream &os, const CResult & o);
  };

private:
  /**
   * Default constructor
   */
  CCopasiTask();

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CCopasiTask * pDataObject
   */
  static CCopasiTask * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & type,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const;

  /**
   * Specific constructor
   * @param const Type & taskType
   * @param const CDataContainer * pParent
   * @param const std::string & type (default: "Task")
   */
  CCopasiTask(const CDataContainer * pParent,
              const CTaskEnum::Task & taskType,
              const std::string & type = "Task");

  /**
   * Copy constructor
   * @param const CCopasiTask & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CCopasiTask(const CCopasiTask & src,
              const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CCopasiTask();

  /**
   * Retrieve the type of the task
   * @return CTaskEnum::Task type
   */
  CTaskEnum::Task getType() const;

  /**
   * Set the type of the task
   * @param CTaskEnum::Task & type
   */
  void setType(const CTaskEnum::Task & type);

  /**
   * Retrieve the key for the task.
   * @return std::string key
   */
  virtual const std::string & getKey() const;

  /**
   * Set whether the task is scheduled
   * @param const bool & scheduled
   */
  void setScheduled(const bool & scheduled);

  /**
   * Check whether the task is scheduled
   * @return const bool & scheduled
   */
  const bool & isScheduled() const;

  /**
   * Set whether the task must update the model
   * @param const bool & updateModel
   */
  virtual void setUpdateModel(const bool & updateModel);

  /**
   * Check whether the task must update the model
   * @return const bool & updateModel
   */
  const bool & isUpdateModel() const;

  /**
   * Set whether the task shall ignoew problem data
   * @param const bool & ignoreProblemData
   */
  void setIgnoreProblemData(const bool & ignoreProblemData);

  /**
   * Set the pointer to container used for calculations
   * @param CMathContainer * pContainer
   */
  void setMathContainer(CMathContainer * pContainer);

  /**
   * Retrieve the pointer to the container used for calculations
   * @return CMathContainer * pContainer
   */
  CMathContainer * getMathContainer() const;

  /**
   * Set the call back of the task
   * @param CProcessReport & callBack
   * @result bool success
   */
  virtual bool setCallBack(CProcessReportLevel callBack);

  /**
   * @return the currently set callback
   */
  const CProcessReportLevel & getCallBack() const;

  /**
   * resets the currently set callback by calling setCallBack(NULL)
   */
  virtual void clearCallBack();

  /**
   * Resizes result matrices and updates array annotations for a specific task.
   * For now this will be hard coded in the respective derived classes.
   * We may introduce a more generic mechanism for this in the future.
   * This is used when we need to know about the data structures of a task result
   * without actually performing the task, e.g. when selecting objects for output.
   * For now we assume that this functionality is also performed when
   * initialize() is called.
   */
  virtual bool updateMatrices() {return true;};

  /**
   * Initialize the task. If an ostream is given this ostream is used
   * instead of the target specified in the report. This allows nested
   * tasks to share the same output device.
   * @param const OutputFlag & of
   * @param COutputHandler * pOutputHandler
   * @param std::ostream * pOstream (default: NULL)
   * @return bool success
   */
  virtual bool initialize(const OutputFlag & of,
                          COutputHandler * pOutputHandler,
                          std::ostream * pOstream);

  /**
   * Process the task with or without initializing to the initial state.
   * @param const bool & useInitialValues
   * @return bool success
   */
  virtual bool process(const bool & useInitialValues);

  /**
   * Perform necessary cleanup procedures
   * @param const bool & updateModel (default: true)
   */
  virtual bool restore(const bool & updateModel = true);

#ifndef SWIG

  /**
   * Retrieve the list of valid methods
   * @return const CTaskEnum::Method * pValidMethods
   */
  virtual const CTaskEnum::Method * getValidMethods() const;
#endif

  /**
   * Retrieve the problem
   */
  CCopasiProblem * getProblem();

  /**
   * Retrieve the problem
   */
  const CCopasiProblem * getProblem() const;

  /**
   * Set the method type applied to solve the task
   * @param const CTaskEnum::Method & type
   * @return bool success
   */
  bool setMethodType(const CTaskEnum::Method & type);

  /**
   * Retrieve the method
   */
  CCopasiMethod * getMethod();

  /**
   * Retrieve the method
   */
  const CCopasiMethod * getMethod() const;

  /**
   * Retrieve the report
   */
  CReport & getReport();

  /**
   * Retrieve the report
   */
  const CReport & getReport() const;

  /**
   * Retrieve the description
   */
  const CDescription & getDescription() const;

  /**
   * Retrieve the result
   */
  const CResult & getResult() const;

  /**
   * Cleanup function
   **/
  void cleanup();

  /**
   * Retrieve a pointer to the group of sliders.
   * @return CCopasiParameterGroup * pSliders
   */
  CCopasiParameterGroup * getSliders();

  //the following methods are wrappers for doing output. They are intended
  //to hide the fact that output is done using different mechanisms, e.g. reports and plots

  /**
   * Perform an output event for the current activity
   * @param const Activity & activity
   */
  virtual void output(const COutputInterface::Activity & activity);

  /**
   * Introduce an additional separator into the output
   * @param const Activity & activity
   */
  virtual void separate(const COutputInterface::Activity & activity);

  inline const OutputFlag & getOutputMode() const
  {return mDoOutput;};

  COutputHandler* getOutputHandler() const;

protected:
  /**
   * Signal that the math container has changed
   */
  virtual void signalMathContainerChanged();

  /**
   * Signal that the method has changed
   */
  virtual void signalMethodChanged();

  /**
   * Check whether the task definition is valid
   *
   * @return bool isValid
   */
  bool isTaskValid() const;

private:
  void initObjects();

  // Attributes
protected:
  /**
   * The type of the task
   */
  CTaskEnum::Task mType;

  /**
   * The key of the task
   */
  std::string mKey;

  /**
   * The description of the task.
   */
  CDescription mDescription;

  /**
   * The result of the task.
   */
  CResult mResult;

  /**
   * Tells whether the task is scheduled for execution
   */
  bool mScheduled;

  /**
   * Tells whether the task shall update the model with the result.
   * The restore method must act accordingly.
   */
  bool mUpdateModel;

  /**
   *
   */
  bool mIgnoreProblemData;

  /**
   * The problem of the task
   */
  CCopasiProblem * mpProblem;

  /**
   * The method used to solve the problem.
   */
  CCopasiMethod * mpMethod;

  /**
   * The report that belongs to this specific task
   */
  CReport mReport;

  /**
   * A pointer to the math container used for calculation
   */
  CMathContainer * mpContainer;

  /**
   * The state of the model before execution of the task. If mUpdateModel
   * is false this state is restored.
   */
  CVector< C_FLOAT64 > mInitialState;

  /**
   * progress bar handler
   */
  CProcessReportLevel mProcessReport;

  /**
   * Pointer to group of sliders associated with the task.
   */
  CCopasiParameterGroup * mpSliders;

  OutputFlag mDoOutput;
  COutputHandler * mpOutputHandler;
  unsigned C_INT32 mOutputCounter;

#ifndef SWIG
  // used by language bindings to hold last process warnings / errors
  //   however, swig stumbles over this if it sees it here
public:
  std::string Error;
  std::string Warning;
#endif // SWIG
};

#endif // COPASI_CCopasiTask
