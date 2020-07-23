// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.


#ifndef COPASI_CDataHandler
#define COPASI_CDataHandler

#include <string>
#include <vector>
#include <iostream>

#include "copasi/core/CDataContainer.h"
#include "copasi/core/CRegisteredCommonName.h"

#include "copasi/output/COutputHandler.h"


/**
 * CDataHandler implements an output handler, that captures float
 * for later.
 */
class CDataHandler : public COutputHandler
{

protected:

  std::vector< CRegisteredCommonName > mCNsBefore;
  std::vector< CRegisteredCommonName > mCNsDuring;
  std::vector< CRegisteredCommonName > mCNsAfter;

  std::vector< CObjectInterface * > mBeforeObjectList;
  std::vector< CObjectInterface * > mDuringObjectList;
  std::vector< CObjectInterface * > mAfterObjectList;

  std::vector< C_FLOAT64 > mBeforeData;
  std::vector< std::vector< C_FLOAT64 > > mDuringData;
  std::vector< C_FLOAT64 > mAfterData;

  bool mSeparate;

public:
  /**
   * Constructor
   *
   * @param separate boolean indicate whether NaN / empty vectors
   *        are added on calls to separate.
   *
   */
  CDataHandler(bool separate = false);

  /**
   * Copy constructor.
   * @param const CDataHandler & src
   */
  CDataHandler(const CDataHandler & src);

  /**
   * cleanup
   */
  void cleanup();

  /**
   *  Destructor.
   */
  ~CDataHandler();

  /**
   * Adds the registered name to the list of names to be collected on
   * Activity::BEFORE.
   *
   * @param name a registered name to a float value reference.
   *
   */
  void addBeforeName(const CRegisteredCommonName & name);

  /**
   * Adds the registered name to the list of names to be collected on
   * Activity::DURING.
   *
   * @param name a registered name to a float value reference.
   *
   */
  void addDuringName(const CRegisteredCommonName & name);

  /**
   * Adds the registered name to the list of names to be collected on
   * Activity::AFTER.
   *
   * @param name a registered name to a float value reference.
   *
   */
  void addAfterName(const CRegisteredCommonName & name);

  /**
   * Adds the registered name to the list of names with the specified activity.
   *
   * @param name the registered name to a float value reference
   * @param activity the activity to collect
   *
   * @return true, in case the name could be stored, false otherwise
   */
  bool addName(const CRegisteredCommonName & name, const Activity & activity);

  /**
   * Returns the list of names registered for the given activity
   *
   * @param activity the activity for which to return the names
   *
   * @return a pointer to the registered names, or NULL
   */
  std::vector< CRegisteredCommonName >* getNames(const Activity & activity);

  /**
   * empties the list of names for the specified activity
   *
   * @param activity the activity for which to clear the list of names
   */
  void clearNames(const Activity & activity);

  /**
   * @return the data collected for Activity::BEFORE
   */
  const std::vector< C_FLOAT64 >& getBeforeData() const;

  /**
   * @return the data collected for Activity::DURING
   */
  const std::vector< std::vector< C_FLOAT64 > >& getDuringData() const;

  /**
   * @return the data collected for Activity::AFTER
   */
  const std::vector< C_FLOAT64 >& getAfterData() const;

  /**
   * @return the boolean, indicating whether calls to separate will add
   *          NaN values (for BEFORE / AFTER), empty vector (DURING)
   */
  bool getSeparate() const;

  /**
   * Sets what will happen on a call to separate
   *
   * @param separate the value to set, true will add NaN values for
   *        separate(BEFORE) / separate(AFTER) and an empty vector on
   *        separate(DURING).
   */
  void setSeparate(bool separate);

  /**
   * compile the object list from name vector
   * @param CObjectInterface::ContainerList listOfContainer
   * @return bool success
   */
  virtual bool compile(CObjectInterface::ContainerList listOfContainer);

  /**
   * Perform an output event for the current activity
   * @param const Activity & activity
   */
  virtual void output(const Activity & activity);

  /**
   * Introduce an additional separator into the output
   * @param const Activity & activity
   */
  virtual void separate(const Activity & /* activity */);

  /**
   * Finish the output
   */
  virtual void finish();


private:
  void storeDataBefore();
  void storeDataDuring();
  void storeDataAfter();

  /**
   * transfer every individual object list from name vector
   */
  bool generateObjectsFromName(const CObjectInterface::ContainerList & listOfContainer,
                               std::vector< CObjectInterface * > & objectList,
                               const std::vector< CRegisteredCommonName > * nameVector);

};

#endif
