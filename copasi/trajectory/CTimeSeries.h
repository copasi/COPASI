// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTimeSeries.h,v $
//   $Revision: 1.12.6.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/29 15:01:50 $
// End CVS Header

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

class CTimeSeries : public COutputInterface, protected CMatrix< C_FLOAT64 >
  {
  private:
    //since the assignment operator are not properly implemented
    //they should be inaccesible

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
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > listOfContainer);

    /**
     * Perform an output event for the current activity
     * @param const Activity & activity
     */
    virtual void output(const Activity & activity);

    /**
     * Introduce an additional seperator into the ouput
     * @param const Activity & activity
     */
    virtual void separate(const Activity & activity);

    /**
     * Finsh the output
     */
    virtual void finish();

    //**** put data into time series ***

  public:
    /**
     * The maximal number of recorded steps. This must be set before compiling
     * @param const unsigned C_INT32 & steps
     */
    void allocate(const unsigned C_INT32 & steps);

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
     * Retreive the number of time steps (rows)
     * @return const unsigned C_INT32 & recordedSteps
     */
    const unsigned C_INT32 & getRecordedSteps() const;

    /**
     * Retrieve the number of variables (columns)
     * @return unsigned C_INT32 & numVariables
     */
    const unsigned C_INT32 & getNumVariables() const;

    /**
     * Retrieve the data (particle number for species) for the indexed step and variable
     * @param const unsigned C_INT32 & step
     * @param const unsigned C_INT32 & variable
     * @return const C_FLOAT64 & data
     */
    const C_FLOAT64 & getData(const unsigned C_INT32 & step,
                              const unsigned C_INT32 & variable) const;

    /**
     * Retrieve the data (concentration for species) for the indexed step and variable
     * @param const unsigned C_INT32 & step
     * @param const unsigned C_INT32 & variable
     * @return const C_FLOAT64 & data
     */
    C_FLOAT64 getConcentrationData(const unsigned C_INT32 & step,
                                   const unsigned C_INT32 & variable) const;

    /**
     * Retrieve the title of the indexed variable (column)
     * @param const unsigned C_INT32 & variable
     * @return const std::string & title
     */
    const std::string & getTitle(const unsigned C_INT32 & variable) const;

    /**
     * Retrieve the key of the model entity of the indexed variable (column)
     * @param const unsigned C_INT32 & variable
     * @return const std::string & key
     */
    const std::string & getKey(const unsigned C_INT32 & variable) const;

    /**
     * get the id of the sbml object correspoding to column indexed by variable.
     * If there is no corresponding SBML object (e.g. if the model comes from a
     * COPASI file) the empty string is returned.
     * @param const unsigned C_INT32 & variable
     * @return const std::string SBMLId
     */
    std::string getSBMLId(const unsigned C_INT32 & variable) const;

  private:

    /**
     * The number of allocated steps
     */
    unsigned C_INT32 mAllocatedSteps;

    /**
     * The number of actually recorded steps
     */
    unsigned C_INT32 mRecordedSteps;

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
     * Vector of indexes pointing to the colum storing the volume of the containing
     * compartment for a species (C_INVALID_INDEX otherwise)
     */
    CVector< unsigned C_INT32 > mCompartment;

    /**
     * Pivot rearranging the columns to a more user friendly order
     */
    CVector< unsigned C_INT32 > mPivot;

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
