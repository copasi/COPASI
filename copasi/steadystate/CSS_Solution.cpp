/**
 *  File name: CSS_Solution.cpp
 *
 *  Programmer: Yongqun He
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the .cpp file for the class CSS_Solution.
 *           It is to solve the steady state solution problem with different approaches,
 *           e.g., (1) Newton, (2) Integration (Trajectory), (3) Newton + Integration,
 *           (4) Backward Integration, (5) Backward integration if all else fails.
 */


#include <cmath>
#include <fstream>
#include <iostream>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CSS_Solution.h"
#include "model/CModel.h"
#include "utilities/CGlobals.h"

//don't consider CEigen class now, do it later
#include "CEigen.h"

//default constructor
CSS_Solution::CSS_Solution()
{
  CONSTRUCTOR_TRACE;
  mNewton = NULL;
  mModel = NULL;
  //  mEigen = NULL;
  mTraj = NULL;
  mJacob = NULL;
  mUseNewton = 1;
  mUseIntegration = 1;
  mUseBackIntegration = 1;

  mDerivFactor = 0.1;
  mSs_x = NULL;
  mSSOutput = NULL;  // wsun  03/20/02
}

//destructor
CSS_Solution::~CSS_Solution() {DESTRUCTOR_TRACE;}

// initialize pointers
void CSS_Solution::initialize()
{
  if (!mModel) fatalError();

  cleanup();

  if (mUseNewton)
    {
      mNewton = new CNewton();
      mNewton->setDerivFactor(mDerivFactor);
      mNewton->setSSRes(mSSRes);
      mNewton->setModel(*mModel);
      mNewton->initialize();
    }

  if (mUseIntegration || mUseBackIntegration)
    {
      mTraj = new CTrajectory();
      mTraj->setMethod(CTrajectory::CONTINUOUS_ODE);
      mTraj->setModel(mModel);
      mTraj->initialize();
    }

  //mEigen = new CEigen();
  mJacob = new CJacob();
  mJacob->setModel(mModel);

  unsigned C_INT32 dim = mModel->getIndMetab();
  mSs_dxdt.newsize(dim);

  mSSOutput = new COutputEvent(*this);
  if (mSSOutput)
    Copasi->OutputList.compile("Steady-state output", mModel, this);
}


// Clean up internal pointer variables
void CSS_Solution::cleanup(void)
{
  pcleanup(mNewton);
  pcleanup(mTraj);
  pdelete(mJacob);
  pdelete(mSs_x);
}

void CSS_Solution::setUseNewton(const C_INT32 & useNewton)
{
  mUseNewton = useNewton;
}

const C_INT32 & CSS_Solution::getUseNewton() const
{
  return mUseNewton;
}

void CSS_Solution::setUseIntegration(const C_INT32 & useIntegration)
{
  mUseIntegration = useIntegration;
}

const C_INT32 & CSS_Solution::getUseIntegration() const
{
  return mUseIntegration;
}

void CSS_Solution::setUseBackIntegration(const C_INT32 & useBackIntegration)
{
  mUseBackIntegration = useBackIntegration;
}

const C_INT32 & CSS_Solution::getUseBackIntegration() const
{
  return mUseBackIntegration;
}

//Yohe: 03/22/02
//set mSSRes
void CSS_Solution::setSSRes(C_FLOAT64 aDouble)
{
  mSSRes = aDouble;
}

//Yohe: 03/22/02
//get mSSRes
C_FLOAT64 CSS_Solution::getSSRes() const
{
  return mSSRes;
}

//get mNewton
CNewton * CSS_Solution::getNewton() const
{
  return mNewton;
}

//get mEigen
CEigen * CSS_Solution::getEigen() const
{
  return mEigen;
}

//set mModel
void CSS_Solution::setModel(CModel * aModel)
{
  mModel = aModel;
}

//get mNewton
CModel * CSS_Solution::getModel() const
{
  return mModel;
}

//get mTraj
CTrajectory *  CSS_Solution::getTrajectory() const
{
  return mTraj;
}

//get mJacob
CJacob * CSS_Solution::getJacob() const
{
  return mJacob;
}

/**
 *  get mSs_x
 *  @return mSs_x
 */
const C_FLOAT64 * CSS_Solution::getSs_x() const
{
  return mSs_x;
}

// get mSs_dxdt
const TNT::Vector < C_FLOAT64 > & CSS_Solution::getSs_dxdt() const
{
  return mSs_dxdt;
}

void CSS_Solution::load(CReadConfig & configbuffer)
{
  C_INT32 Option;
  C_INT32 SSBackInt;

  if (configbuffer.getVersion() < "4.0")
    {
      configbuffer.getVariable("SSStrategy", "C_INT32",
                               (void *) &Option, CReadConfig::LOOP);
      configbuffer.getVariable("SSBackIntegration", "C_INT32",
                               (void *) &SSBackInt);
      switch (Option)
        {
        case 0:
          mUseNewton = 1;
          mUseIntegration = 1;
          if (SSBackInt)
            mUseBackIntegration = 1;
          else
            mUseBackIntegration = 0;
          break;

        case 1:
          mUseNewton = 0;
          mUseIntegration = 1;
          mUseBackIntegration = 0;
          break;

        case 2:
          mUseNewton = 1;
          mUseIntegration = 0;
          mUseBackIntegration = 0;
          break;

        case 3:
          mUseNewton = 0;
          mUseIntegration = 0;
          mUseBackIntegration = 1;
          break;

        default:
          fatalError();
        }
    }
  else
    {
      configbuffer.getVariable("SSUseNewton", "C_INT32", &mUseNewton,
                               CReadConfig::LOOP);
      configbuffer.getVariable("SSUseIntegration", "C_INT32",
                               &mUseIntegration);
      configbuffer.getVariable("SSUseBackIntegration", "C_INT32",
                               &mUseBackIntegration);
    }

  configbuffer.getVariable("NewtonLimit", "C_INT32", &mNewtonLimit,
                           CReadConfig::SEARCH);

  //YH: to allow either "SSResoltion" or "SSResolution" format
  //"SSResoltion" is the default for use
  if (configbuffer.getVersion() < "4.0")
    configbuffer.getVariable("SSResoltion", "C_FLOAT64",
                             (void *) &mSSRes);
  else
    configbuffer.getVariable("SSResolution", "C_FLOAT64",
                             (void *) &mSSRes);

  configbuffer.getVariable("DerivationFactor", "C_FLOAT64",
                           (void *) &mDerivFactor,
                           CReadConfig::SEARCH);
}


void CSS_Solution::save(CWriteConfig & configbuffer)
{
  configbuffer.setVariable("SSUseNewton", "C_INT32", &mUseNewton);
  configbuffer.setVariable("SSUseIntegration", "C_INT32", &mUseIntegration);
  configbuffer.setVariable("SSUseBackIntegration", "C_INT32",
                           &mUseBackIntegration);
  configbuffer.setVariable("NewtonLimit", "C_INT32", &mNewtonLimit);
  configbuffer.setVariable("SSResolution", "C_FLOAT64", &mSSRes);
  configbuffer.setVariable("DerivationFactor", "C_FLOAT64", &mDerivFactor);

  // configbuffer.setVariable("Flux", "C_FLOAT64", &mFlux);
}

void CSS_Solution::process(ofstream &fout)
{
  C_FLOAT64 StartTime;
  C_FLOAT64 EndTime;

  mSs_solution = SS_NOT_FOUND;

  // use the damped Newton method
  if (mUseNewton)
    {
      mNewton->setNewtonLimit(mNewtonLimit);
      mNewton->setStartingPoint();
      mNewton->process();

      // if (mNewton->isSteadyState())
      if (mNewton->isSteadyState())
        {
          pdelete(mSs_x);
          mSs_x = mModel->getNumbers();
          afterFindSteadyState();
          mSs_solution = SS_FOUND;
        }
    }

  // use forward integration, or trajectory
  if (mUseIntegration && mSs_solution != SS_FOUND) // if newton failed
                                                   // or forward integration only
    {
      StartTime = 0;
      EndTime = 1;
      pdelete(mSs_x);
      mSs_x = mModel->getInitialNumbers();

      mTraj->setPoints(1);

      while (EndTime < 1.0e10 && mSs_solution != SS_FOUND)
        {
          EndTime *= 10;
          mTraj->setStartingPoint(StartTime, mSs_x);
          mTraj->setEndTime(EndTime);

          mTraj->process(fout);

          pdelete(mSs_x);
          mSs_x = mModel->getNumbers();

          if (isSteadyState()) afterFindSteadyState();

          // newton+integration (we use newton before recycling)
          if (mUseNewton && mSs_solution != SS_FOUND)
            {
              mNewton->setStartingPoint(mSs_x);
              mNewton->process();

              if (mNewton->isSteadyState())
                {
                  pdelete(mSs_x);
                  mSs_x = mModel->getNumbers();

                  if (isSteadyState()) afterFindSteadyState();
                }
            }
          StartTime = EndTime;
        }
    }

  //Backward trajectory until -10^10
  // use backwards integration
  // find the original lsods_incr, see how it works
  if (mUseBackIntegration && mSs_solution != SS_FOUND) //if others failed
    // or backwards integration only
    {
      StartTime = 0;
      EndTime = -1;
      pdelete(mSs_x);
      mSs_x = mModel->getInitialNumbers();
      mTraj->setPoints(1);

      while (EndTime > -1.0e10 && mSs_solution != SS_FOUND)
        {
          EndTime *= 10;
          mTraj->setStartingPoint(StartTime, mSs_x);
          mTraj->setEndTime(EndTime);

          mTraj->process(fout);

          pdelete(mSs_x);
          mSs_x = mModel->getNumbers();

          if (isSteadyState())
            {
              afterFindSteadyState();
            }

          // newton+integration (we use newton before recycling)
          if (mUseNewton && mSs_solution != SS_FOUND)
            {
              mNewton->setStartingPoint(mSs_x);
              mNewton->process();

              if (mNewton->isSteadyState())
                {
                  pdelete(mSs_x);
                  mSs_x = mModel->getNumbers();

                  if (isSteadyState()) afterFindSteadyState();
                }
            }
          StartTime = EndTime;
        }
    }
  mSSOutput->print(*this, Copasi->OutputList, fout);
}

C_INT32 CSS_Solution::isSteadyState()
{
  unsigned C_INT32 i, dim = mModel->getIndMetab();
  double maxrate;

  mSs_solution = SS_NOT_FOUND;
  for (i=0; i<dim; i++)
    if (mSs_x[i] < 0.0) return SS_NOT_FOUND;

  mModel->lSODAEval(dim, 0, mSs_x, &mSs_dxdt[0]);

  maxrate = xNorm(dim, &mSs_dxdt[0] - 1, 1);
  if (maxrate < mSSRes) mSs_solution = SS_FOUND;

  return mSs_solution;
}


// Process after the steady state is found
void CSS_Solution::afterFindSteadyState()
{

  //evaluate the jacobian
  mJacob->jacobEval(mSs_x, mDerivFactor, mSSRes);

  //calculate the eigenvalues of the jacobian
  //CEigen tmp = CEigen(mSSRes,  mJocob,
  //mEigen = tmp;

  /* don't consider Eigen class now, do it later  //yohe

  mEigen->setN(mModel->getIndMetab());
  mEigen->initialize();
  mEigen->CalcEigenvalues(mSSRes, mJacob->getJacob());

  */

  //copy the concentrations back to the model
  //mModel->setConcentrations(mSs_x);

  return;
}


/**
 *  get mSs_solution
 *  @return mSs_solutionWeiSun 03/27/02
 */
C_INT32 CSS_Solution::getSolution() const
{
  return mSs_solution;
}


/**
 * Get the pointer of SSRes for outputWeiSun 04/02/02
 */
void * CSS_Solution::getSSResAddr()
{
  return &mSSRes;
}

/**
 * Get the pointer of DerivFactor for outputWeiSun 04/02/02
 */
void * CSS_Solution::getDerivFactorAddr()
{
  return &mDerivFactor;
}
