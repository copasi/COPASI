// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTimeSeries.h,v $
//   $Revision: 1.12.6.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/21 19:12:55 $
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

class CModel;

class CTimeSeries : protected CMatrix< C_FLOAT64 >
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

    //**** put data into time series ***

    /**
     * initialization
     * @param n prospective number of steps
     * @param pState the CState from which the date should be taken
     * @return success
     */
    bool init(C_INT32 n, CModel * pModel);

    bool add();

    bool finish();

    int save(const std::string& fileName, bool writeConcentrations = false, const std::string& separator = "\t") const;

    //**** get data from time series ***

    unsigned C_INT32 getNumSteps() const;
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
    unsigned C_INT32 mNumSteps;
    C_FLOAT64 * mpIt;
    C_FLOAT64 * mpEnd;

    const CState * mpState;
    std::vector< std::string > mTitles;
    CVector< C_FLOAT64 > mFactors;
    CVector< unsigned C_INT32 > mPivot;
    std::vector< std::string > mKeys;

    static std::string mDummyString;
    static C_FLOAT64 mDummyFloat;
  };

#endif
