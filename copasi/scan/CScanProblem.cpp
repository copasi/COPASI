/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanProblem.cpp,v $
   $Revision: 1.31 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/12/30 15:31:54 $
   End CVS Header */

/**
 *  CScanProblem class.
 *  
 */

#include <string>

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CScanProblem.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "utilities/CGlobals.h"

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CScanProblem::CScanProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::timeCourse, pParent),
    mInitialState()
    //mEndState()
{
  addParameter("StepNumber", CCopasiParameter::UINT, (unsigned C_INT32) 100);
  addParameter("StepSize", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.01);
  addParameter("StartTime", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.0);
  addParameter("EndTime", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.0);
  addParameter("TimeSeriesRequested", CCopasiParameter::BOOL, (bool) true);

  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CScanProblem &" src
 */
CScanProblem::CScanProblem(const CScanProblem & src,
                           const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    mInitialState(src.mInitialState)
    //mEndState(src.mEndState)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CScanProblem::~CScanProblem()
{DESTRUCTOR_TRACE;}

/**
 * Set the model the problem is dealing with.
 * @param "CModel *" pModel
 */
bool CScanProblem::setModel(CModel * pModel)
{
  mpModel = pModel;
  mInitialState.setModel(mpModel);
  //mEndState.setModel(mpModel);

  return true;
}

/**
 * Set the number of time steps the trajectory method should integrate.
 * @param "const unsigned C_INT32 &" stepNumber
 */
void CScanProblem::setStepNumber(const unsigned C_INT32 & stepNumber)
{
  setValue("StepNumber", stepNumber);
}

/**
 * Retrieve the number of time steps the trajectory method should integrate.
 * @return "const unsigned C_INT32 &" stepNumber
 */
const unsigned C_INT32 & CScanProblem::getStepNumber() const
  {return * (unsigned C_INT32 *) getValue("StepNumber");}

/**
 * Set the initial state of the problem.
 * @param "const CState &" initialState
 */
void CScanProblem::setInitialState(const CState & initialState)
{
  mInitialState = initialState;
}

/**
 * Set the initial state of the problem.
 * @param "const CStateX &" initialState
 */
void CScanProblem::setInitialState(const CStateX & initialState)
{
  mInitialState = initialState;
}

/**
 * Retrieve the initial state of the problem.
 * @return "const CState *" pInitialState
 */
const CState & CScanProblem::getInitialState() const
  {return mInitialState;}

/**
 * Load a trajectory problem
 * @param "CReadConfig &" configBuffer
 */
void CScanProblem::load(CReadConfig & configBuffer,
                        CReadConfig::Mode C_UNUSED(mode))
{
  /*  C_FLOAT64 dbl;
    unsigned C_INT32 uint;
   
    if (configBuffer.getVersion() < "4.0")
      {
        mpModel = Copasi->pModel;
        configBuffer.getVariable("EndTime", "C_FLOAT64",
                                 & dbl,
                                 CReadConfig::LOOP);
        setValue("EndTime", dbl);
        configBuffer.getVariable("Points", "C_INT32",
                                 & uint);
        setValue("StepNumber", uint);
        mStepNumberSetLast = true;
        setValue("StartTime", (C_FLOAT64) 0.0);
        sync();
        mInitialState = mpModel->getInitialState();
      }*/
}
