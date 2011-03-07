/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CProcessReport.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $
   $Date: 2011/03/07 19:34:54 $
   End CVS Header */

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CProcessReport
#define COPASI_CProcessReport

#include <string>
#include <map>

#include "utilities/CCopasiParameter.h"

#include "utilities/CVector.h"

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
                     const Type & type,
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
  const CCopasiParameter::Value & getEndValue() const;

  /**
   * Retrieve whether the item has an end value.
   * @return const bool & hasEndValue
   */
  const bool & hasEndValue() const;

  /**
   * Retrieve the private end value of the parameter.
   * @return CCopasiParameter::Value & endValue
   */
  CCopasiParameter::Value & getEndValue();

  // Attributes
private:
  /**
   *  A pointer to the value of the parameter.
   */
  CCopasiParameter::Value mEndValue;

  /**
   * Indicator whether an endvalue has been provided
   */
  bool mHasEndValue;
};

class CProcessReport
{
  // Operations
public:
  /**
   * Default Constructor
   */
  CProcessReport();

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

protected:
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

public:
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

  // Attributes
protected:
  /**
   * The list process report items.
   */
  CVector< CProcessReportItem * > mProcessReportItemList;

  /**
   * The name of the process.
   */
  std::string mName;
};

#endif // COPASI_CProcessReport
