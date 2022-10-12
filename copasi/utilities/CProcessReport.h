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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CProcessReport
#define COPASI_CProcessReport

#include <string>
#include <map>

#include "copasi/core/CVector.h"
#include "copasi/utilities/CCopasiParameter.h"

class CCopasiTimeVariable;

class CProcessReportItem: public CCopasiParameter
{
  // Operations
private:
  CProcessReportItem();

public:
  /**
   * Specific constructor
   * @param const string & name
   * @param const CCopasiParameter::Type & type
   * @param const void * pValue
   * @param const void * pEndValue (default: NULL)
   */
  CProcessReportItem(const std::string & name,
                     const CCopasiParameter::Type & type,
                     const void * pValue,
                     const void * pEndValue = NULL);

  /**
   * Copy Constructor
   * @param const CProcessReportItem & src
   */
  CProcessReportItem(const CProcessReportItem & src);

  /**
   * Destructor
   */
  ~CProcessReportItem();

  /**
   * Retrieve the private end value of the parameter. This method
   * returns NULL if no end value has been set.
   * @return const CCopasiParameter::Value & endValue
   */
  template < class CType > const CType & getEndValue() const
  {return static_cast< const CType >(mpEndValue);}

  /**
   * Retrieve the private end value of the parameter.
   * @return CCopasiParameter::Value & endValue
   */
  template < class CType > CType & getEndValue()
  {return static_cast< CType >(mpEndValue);}

  /**
   * Retrieve the raw pointer to the end value
   */
  void * getEndValuePointer();

  /**
   * Retrieve whether the item has an end value.
   * @return const bool & hasEndValue
   */
  const bool & hasEndValue() const;

  // Attributes
private:
  /**
   *  A pointer to the value of the parameter.
   */
  void * mpEndValue;

  /**
   * Indicator whether an endvalue has been provided
   */
  bool mHasEndValue;
};

class CProcessReport
{
protected:
  enum struct ProccessingInstruction
  {
    Continue,
    Pause,
    Stop,
    Kill
  };

  // Operations
public:
  /**
   * Default Constructor
   * @param const unsigned int & maxTime (Default: 0)
   */
  CProcessReport(const unsigned int & maxTime = 0);

  /**
   * Destructor
   */
  virtual ~CProcessReport();

  /**
   * Report process on all items. If the return value is false the calling
   * process must halt execution and return.
   * @param bool continue
   */
  virtual bool progress();

  /**
   * Report process on item handle. If the return value is false the calling
   * process must halt execution and return.
   * @param const size_t & handle
   * @param bool continue
   */
  virtual bool progressItem(const size_t & handle);

  /**
   * Check whether processing shall proceed. If the return value is false
   * the calling process must halt execution and return. This method is
   * provided so that lengthy processing without advances in any of the
   * reporting items can check whether continuation is requested.
   * @param bool continue
   */
  virtual bool proceed();

  /**
   * Reset all item handle. This means that the values of the items have changed
   * but not as part of a continuous process. If you run multiple processes
   * call reset between them. If the return value is false the calling
   * process must halt execution and return.
   * @param bool continue
   */
  virtual bool reset();

  /**
   * Reset item handle. This means that the value of the item has changed
   * but not as part of a continuous process. If you run multiple processes
   * call reset between them. If the return value is false the calling
   * process must halt execution and return.
   * @param const size_t & handle
   * @param bool continue
   */
  virtual bool resetItem(const size_t & handle);

  /**
   * Indicate that all items are finished reporting. All item handles loose
   * their validity. If the return value is false the calling
   * process must halt execution and return.
   * @param bool continue
   */
  virtual bool finish();

  /**
   * Add a process report item to to the list of reporting items.
   * The return value is the handle of the item and can be used to
   * indicate process, finish, or reset the item. If the method fails
   * C_INVALID_INDEX is returned.
   * @param const std::string & name
   * @param const CCopasiParameter::Type & type
   * @param const void * pValue
   * @param const void * pEndValue = NULL
   * @return size_t handle
   */
  virtual size_t addItem(const std::string & name,
                         const CCopasiParameter::Type & type,
                         const void * pValue,
                         const void * pEndValue = NULL);

  /**
   * Add a process report item to to the list of reporting items.
   * The return value is the handle of the item and can be used to
   * indicate process, finish, or reset the item. If the method fails
   * C_INVALID_INDEX is returned.
   * @param const std::string & name
   * @param const std::string & value
   * @param const std::string * pEndValue = NULL
   * @return size_t handle
   */
  size_t addItem(const std::string & name,
                 const std::string & value,
                 const std::string * pEndValue = NULL);

  /**
   * Add a process report item to to the list of reporting items.
   * The return value is the handle of the item and can be used to
   * indicate process, finish, or reset the item. If the method fails
   * C_INVALID_INDEX is returned.
   * @param const std::string & name
   * @param const C_INT32 & value
   * @param const C_INT32 * pEndValue = NULL
   * @return size_t handle
   */
  size_t addItem(const std::string & name,
                 const C_INT32 & value,
                 const C_INT32 * pEndValue = NULL);

  /**
   * Add a process report item to to the list of reporting items.
   * The return value is the handle of the item and can be used to
   * indicate process, finish, or reset the item. If the method fails
   * C_INVALID_INDEX is returned.
   * @param const std::string & name
   * @param const unsigned C_INT32 & value
   * @param const unsigned C_INT32 * pEndValue = NULL
   * @return size_t handle
   */
  size_t addItem(const std::string & name,
                 const unsigned C_INT32 & value,
                 const unsigned C_INT32 * pEndValue = NULL);

  /**
   * Add a process report item to to the list of reporting items.
   * The return value is the handle of the item and can be used to
   * indicate process, finish, or reset the item. If the method fails
   * C_INVALID_INDEX is returned.
   * @param const std::string & name
   * @param const C_FLOAT64 & value
   * @param const C_FLOAT64 * pEndValue = NULL
   * @return size_t handle
   */
  size_t addItem(const std::string & name,
                 const C_FLOAT64 & value,
                 const C_FLOAT64 * pEndValue = NULL);

  /**
   * Indicate that item handle is finished reporting. The handle of that
   * item is no longer valid after the call. If the return value is false
   * the calling process must halt execution and return.
   * @param const size_t & handle
   * @param bool continue
   */
  virtual bool finishItem(const size_t & handle);

  /**
   * Check whether the handle is valid, i.e., usable in progress, reset and finish.
   */
  virtual bool isValidHandle(const size_t handle) const;

  /**
   * Set the name of the process.
   * @param const std::string & name
   * @return success
   */
  virtual bool setName(const std::string & name);

  /**
   * Set whether to ignore stop when determining to proceed.
   * @param const bool & ignoreStop (default: true)
   */
  void setIgnoreStop(const bool & ignoreStop = true);

  /**
   * Retrieve whether to ignore stop when determining to proceed.
   * @return const bool & ignoreStop
   */
  const bool & getIgnoreStop() const;

  // Attributes
protected:
  /**
   * The current processing instructions
   */
  ProccessingInstruction mProccessingInstruction;

  /**
   * Flag indicating whether to continue processing after stop instruction
   */
  bool mIgnoreStop;

  /**
   * The list process report items.
   */
  CVector< CProcessReportItem * > mProcessReportItemList;

  /**
   * The name of the process.
   */
  std::string mName;

  /**
   * The time the process should stop.
   */
  CCopasiTimeVariable * mpEndTime;
};

class CProcessReportLevel
{
public:
  /**
   * Specific Constructor
   * @param CProcessReport * pInterface
   */
  CProcessReportLevel(CProcessReport * pInterface = NULL);

  /**
   * Destructor
   */
  ~CProcessReportLevel();

  /**
   * Check whether we actually have an active interface
   * @return bool haveInterface
   */
  operator bool() const;

  /**
   * Increase the level of the progress report
   * @return CProcessReport *
   */
  CProcessReportLevel operator++();

  /**
   * Retrieve a pointer to the process report if valid (level < maxDisplayLevel)
   * @return CProcessReport * pProcessReport
   */
  CProcessReport * toProcessReportPtr();

  /**
   * Report process on all items. If the return value is false the calling
   * process must halt execution and return.
   * @param bool continue
   */
  bool progress();

  /**
  * Report process on item handle. If the return value is false the calling
  * process must halt execution and return.
  * @param const size_t & handle
  * @param bool continue
  */
  bool progressItem(const size_t & handle);

  /**
   * Reset item handle. This means that the value of the item has changed
   * but not as part of a continuous process. If you run multiple processes
   * call reset between them. If the return value is false the calling
   * process must halt execution and return.
   * @param const size_t & handle
   * @param bool continue
   */
  bool resetItem(const size_t & handle);

  /**
   * Indicate that all items are finished reporting. All item handles loose
   * their validity. If the return value is false the calling
   * process must halt execution and return.
   * @param bool continue
   */
  bool finish();

  /**
   * Indicate that item handle is finished reporting. The handle of that
   * item is no longer valid after the call. If the return value is false
   * the calling process must halt execution and return.
   * @param const size_t & handle
   * @param bool continue
   */
  bool finishItem(const size_t & handle);

  /**
   * Check whether processing shall proceed. If the return value is false
   * the calling process must halt execution and return. This method is
   * provided so that lengthy processing without advances in any of the
   * reporting items can check whether continuation is requested.
   * @param bool continue
   */
  bool proceed();

  /**
   * Set the name of the process.
   * @param const std::string & name
   * @return success
   */
  bool setName(const std::string & name);

  /**
   * Add a process report item to to the list of reporting items.
   * The return value is the handle of the item and can be used to
   * indicate process, finish, or reset the item. If the method fails
   * C_INVALID_INDEX is returned.
   * @param const std::string & name
   * @param const std::string & value
   * @param const std::string * pEndValue = NULL
   * @return size_t handle
   */
  size_t addItem(const std::string & name,
                 const std::string & value,
                 const std::string * pEndValue = NULL);

  /**
   * Add a process report item to to the list of reporting items.
   * The return value is the handle of the item and can be used to
   * indicate process, finish, or reset the item. If the method fails
   * C_INVALID_INDEX is returned.
   * @param const std::string & name
   * @param const C_INT32 & value
   * @param const C_INT32 * pEndValue = NULL
   * @return size_t handle
   */
  size_t addItem(const std::string & name,
                 const C_INT32 & value,
                 const C_INT32 * pEndValue = NULL);

  /**
   * Add a process report item to to the list of reporting items.
   * The return value is the handle of the item and can be used to
   * indicate process, finish, or reset the item. If the method fails
   * C_INVALID_INDEX is returned.
   * @param const std::string & name
   * @param const unsigned C_INT32 & value
   * @param const unsigned C_INT32 * pEndValue = NULL
   * @return size_t handle
   */
  size_t addItem(const std::string & name,
                 const unsigned C_INT32 & value,
                 const unsigned C_INT32 * pEndValue = NULL);

  /**
   * Add a process report item to to the list of reporting items.
   * The return value is the handle of the item and can be used to
   * indicate process, finish, or reset the item. If the method fails
   * C_INVALID_INDEX is returned.
   * @param const std::string & name
   * @param const C_FLOAT64 & value
   * @param const C_FLOAT64 * pEndValue = NULL
   * @return size_t handle
   */
  size_t addItem(const std::string & name,
                 const C_FLOAT64 & value,
                 const C_FLOAT64 * pEndValue = NULL);

  /**
   * Set whether to ignore stop when determining to proceed.
   * @param const bool & ignoreStop (default: true)
   */
  void setIgnoreStop(const bool & ignoreStop = true);

private:
  CProcessReport * mpInterface;

  size_t mLevel;

  size_t mMaxDisplayLevel;
};
#endif // COPASI_CProcessReport
