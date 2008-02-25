// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTimeSeries.h,v $
//   $Revision: 1.12.6.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/25 21:15:15 $
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

    int save(const std::string& fileName, bool writeConcentrations = false, const std::string& separator = "\t") const;

    //**** get data from time series ***

    unsigned C_INT32 getRecordedSteps() const;
    unsigned C_INT32 getNumVariables() const;
    const C_FLOAT64 & getData(const unsigned C_INT32 & step, const unsigned C_INT32 & var) const;
    C_FLOAT64 getConcentrationData(const unsigned C_INT32 & step, const unsigned C_INT32 & var) const;
    const std::string & getTitle(const unsigned C_INT32 & var) const;

    /**
     * get the key of the object correspoding to column indexed by var
     */
    const std::string & getKey(const unsigned C_INT32 & var) const;

    /**
     * get the id of the sbml object correspoding to column indexed by var.
     * If there is no corresponding SBML object (e.g. if the model comes from a
     * COPASI file) the empty string is returned.
     */
    std::string getSBMLId(const unsigned C_INT32 & var) const;

  private:
    unsigned C_INT32 mAllocatedSteps;
    unsigned C_INT32 mRecordedSteps;
    C_FLOAT64 * mpIt;
    C_FLOAT64 * mpEnd;

    const CState * mpState;
    std::vector< std::string > mTitles;
    CVector< unsigned C_INT32 > mCompartment;
    CVector< unsigned C_INT32 > mPivot;
    std::vector< std::string > mKeys;
    C_FLOAT64 mNumberToQuantityFactor;

    static std::string mDummyString;
    static C_FLOAT64 mDummyFloat;
  };

#endif
