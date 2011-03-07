// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTimeSeries.h,v $
//   $Revision: 1.16 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:34:13 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef TIMESERIES_H
#define TIMESERIES_H

#include <vector>

#include "model/CState.h"
#include "utilities/CVector.h"
#include "utilities/CMatrix.h"
#include "utilities/COutputHandler.h"

class CModel;
class CCopasiDataModel;

class CTimeSeries : public COutputInterface, protected CMatrix< C_FLOAT64 >
{
private:
  //since the assignment operator are not properly implemented
  //they should be inaccessible

  CTimeSeries & operator= (const CTimeSeries &);

public:
  /**
   * Default constructor
   */
  CTimeSeries();

  /**
   * Copy constructor
   * @param const CTimeSeries & src
   */
  CTimeSeries(const CTimeSeries & src);

  /**
   * Destructor
   */
  ~CTimeSeries();

public:
  /**
   * compile the object list from name vector
   * @param std::vector< CCopasiContainer * > listOfContainer
   * @param  const CCopasiDataModel* pDataModel
   * @return bool success
   */
  virtual bool compile(std::vector< CCopasiContainer * > listOfContainer, const CCopasiDataModel* pDataModel);

  /**
   * Perform an output event for the current activity
   * @param const Activity & activity
   */
  virtual void output(const Activity & activity);

  /**
   * Introduce an additional separator into the output
   * @param const Activity & activity
   */
  virtual void separate(const Activity & activity);

  /**
   * Finish the output
   */
  virtual void finish();

  //**** put data into time series ***

public:
  /**
   * The maximal number of recorded steps. This must be set before compiling
   * @param const size_t & steps
   */
  void allocate(const size_t & steps);

  /**
   * Clear the time series
   */
  void clear();

  /**
   * Save the time series to a file
   * @param const std::string & fileName
   * @param bool writeConcentrations (default: false)
   * @param const std::string& separator (default: "\t")
   * @return int retcode
   */
  int save(const std::string& fileName,
           bool writeConcentrations = false,
           const std::string& separator = "\t") const;

  /**
   * Retrieve the number of time steps (rows)
   * @return const size_t & recordedSteps
   */
  const size_t & getRecordedSteps() const;

  /**
   * Retrieve the number of variables (columns)
   * @return size_t & numVariables
   */
  const size_t & getNumVariables() const;

  /**
   * Retrieve the data (particle number for species) for the indexed step and variable
   * @param const size_t & step
   * @param const size_t & variable
   * @return const C_FLOAT64 & data
   */
  const C_FLOAT64 & getData(const size_t & step,
                            const size_t & variable) const;

  /**
   * Retrieve the data (concentration for species) for the indexed step and variable
   * @param const size_t & step
   * @param const size_t & variable
   * @return const C_FLOAT64 & data
   */
  C_FLOAT64 getConcentrationData(const size_t & step,
                                 const size_t & variable) const;

  /**
   * Retrieve the title of the indexed variable (column)
   * @param const size_t & variable
   * @return const std::string & title
   */
  const std::string & getTitle(const size_t & variable) const;

  /**
   * Retrieve the key of the model entity of the indexed variable (column)
   * @param const size_t & variable
   * @return const std::string & key
   */
  const std::string & getKey(const size_t & variable) const;

  /**
   * get the id of the SBML object corresponding to column indexed by variable.
   * If there is no corresponding SBML object (e.g. if the model comes from a
   * COPASI file) the empty string is returned.
   * @param const size_t & variable
   * @return const std::string SBMLId
   */
  std::string getSBMLId(const size_t & variable, const CCopasiDataModel* pDataModel) const;

private:

  /**
   * The number of allocated steps
   */
  size_t mAllocatedSteps;

  /**
   * The number of actually recorded steps
   */
  size_t mRecordedSteps;

  /**
   * Iterator pointing the next step (row) to be recorded
   */
  C_FLOAT64 * mpIt;

  /**
   * Iterator pointing beyond the last allocated step (row)
   */
  C_FLOAT64 * mpEnd;

  /**
   * Pointer to the state which has to be recorded.
   */
  const CState * mpState;

  /**
   * Vector of column titles.
   */
  std::vector< std::string > mTitles;

  /**
   * Vector of indexes pointing to the column storing the volume of the containing
   * compartment for a species (C_INVALID_INDEX otherwise)
   */
  CVector< size_t > mCompartment;

  /**
   * Pivot rearranging the columns to a more user friendly order
   */
  CVector< size_t > mPivot;

  /**
   * Vector storing the keys for the model entity represented by each column
   */
  std::vector< std::string > mKeys;

  /**
   * Conversion factor needed for computing concentration data
   */
  C_FLOAT64 mNumberToQuantityFactor;

  /**
   * Static empty string for performance reasons
   */
  static std::string mDummyString;

  /**
   * Static C_FLOAT64 0.0 for performance reasons
   */
  static C_FLOAT64 mDummyFloat;
};

#endif
