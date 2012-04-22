// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLayoutEngine.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2012/04/22 14:51:16 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <cmath>
#include <iostream>
#include "copasi.h"
#include "CLayoutEngine.h"
#include "CAbstractLayoutInterface.h"



CLayoutEngine::CLayoutEngine(CAbstractLayoutInterface * l, bool /* so */)
    : mpLayout(l),
    mSecondOrder(false)
{
  if (!mpLayout) return;


  mVariables = mpLayout->getInitialValues();

  if (mSecondOrder) mVariables.resize(mVariables.size()*2, 0);

  mRhs.resize(mVariables.size(), 0);

  //for RK4
  mRhsA.resize(mVariables.size(), 0);
  mRhsB.resize(mVariables.size(), 0);
  mRhsC.resize(mVariables.size(), 0);
  mVar2.resize(mVariables.size(), 0);

  //init LSODA
  mLsodaStatus = 1;
  //mState = 1;
  //mJType = 2;
  mErrorMsg.str("");

  mData.pMethod = this;
  mData.dim = mVariables.size();
  //mAtol = mpModel->initializeAtolVector(*mpAbsoluteTolerance, *mpReducedModel);
  //mY = mpState->beginIndependent();

  //mRtol = *mpRelativeTolerance;

  mTime = 0;

  mDWork.resize(22 + mData.dim * std::max<C_INT>(16, mData.dim + 9) + 3 * 0);
  mDWork[4] = mDWork[5] = mDWork[6] = mDWork[7] = mDWork[8] = mDWork[9] = 0.0;
  mDWork[7] = 0; //minstep
  mIWork.resize(20 + mData.dim);
  mIWork[4] = mIWork[6] = mIWork[9] = 0;

  mIWork[5] = 100; //*mpMaxInternalSteps;
  mIWork[7] = 12;
  mIWork[8] = 5;
  mLSODA.setOstream(mErrorMsg);

}

void CLayoutEngine::calcRHS(std::vector<double> & state, double* rhs)
{
  std::vector<double> forces; forces.resize(mpLayout->getNumVariables());
  calcForces(state, forces);

  unsigned int i, imax = mpLayout->getNumVariables();

  for (i = 0; i < imax; ++i)
    {
      if (mSecondOrder)
        {
          rhs[i+imax] = (forces[i] * 0.04 - state[i+imax] * 0.05) / mpLayout->getMassVector()[i];
          rhs[i] = state[i+imax];
        }
      else
        {
          //first order
          rhs[i] = forces[i] / mpLayout->getMassVector()[i];
        }
    }
}

void CLayoutEngine::calcForces(std::vector<double> & state, std::vector<double> & forces)
{
  if (!mpLayout) return;

  //do numerical derivations...
  mpLayout->setState(state);

  //assymmetric algorithm
  /*double pot0 = mpLayout->getPotential();

  double store, newpot;
  unsigned int i, imax = mpLayout->getNumVariables();
  for (i=0; i<imax; ++i)
  {
    store = mVariables[i];
    mVariables[i]+=1.0;
    mpLayout->setState(mVariables);
    newpot = mpLayout->getPotential();
    mVariables[i] = store;
    mForce[i] = pot0-newpot;
  }*/

  //symmetric algorithm
  double pot0;
  double store, newpot;
  unsigned int i, imax = mpLayout->getNumVariables();

  for (i = 0; i < imax; ++i)
    {
      store = state[i];
      //std::cout << "var " << store;
      state[i] -= 0.5;
      mpLayout->setState(state);
      pot0 = mpLayout->getPotential();
      //std::cout << "pot0 " << pot0 << std::endl;
      state[i] += 1.0;
      mpLayout->setState(state);
      newpot = mpLayout->getPotential();
      state[i] = store;
      forces[i] = pot0 - newpot;
      //std::cout << "force " << i << " = " << forces[i] << std::endl;
    }

}



double CLayoutEngine::step()
{
  if (!mpLayout) return -1.0;

  unsigned int i, imax = mVariables.size();

  //Euler

  mpLayout->setState(mVariables);
  double pot = mpLayout->getPotential();

  calcRHS(mVariables, &mRhs[0]);

  double dt = 3;

  for (i = 0; i < imax; ++i)
    {
      mVariables[i] += mRhs[i] * dt;
    }


  double newpot;

  for (;;)
    {
      mpLayout->setState(mVariables);
      newpot = mpLayout->getPotential();

      if (newpot < pot) break;

      if (dt < 1e-3) break;

      //step back
      dt *= 0.5;

      for (i = 0; i < imax; ++i)
        {
          mVariables[i] -= mRhs[i] * dt;
        }

    }

  //std::cout << dt << "   " << newpot << std::endl;
  return newpot;

}

void CLayoutEngine::stepIntegration()
{
  if (!mpLayout) return;

  const double dt = 0.2;


  unsigned int i, imax = mVariables.size();

  //Euler
  /*calcRHS(mVariables, &mRhs[0]);

  for (i = 0; i < imax; ++i)
    {
      mVariables[i] += mRhs[i] * 0.05;
    }*/

  //RK4
  calcRHS(mVariables, &mRhs[0]);

  for (i = 0; i < imax; ++i)
    {
      mVar2[i] = mVariables[i] + mRhs[i] * 0.5 * dt;
    }

  calcRHS(mVar2, &mRhsA[0]);

  for (i = 0; i < imax; ++i)
    {
      mVar2[i] = mVariables[i] + mRhsA[i] * 0.5 * dt;
    }

  calcRHS(mVar2, &mRhsB[0]);

  for (i = 0; i < imax; ++i)
    {
      mVar2[i] = mVariables[i] + mRhsB[i] * dt;
    }

  calcRHS(mVar2, &mRhsC[0]);

  for (i = 0; i < imax; ++i)
    {
      mVariables[i] += dt / 6 * (mRhs[i] + 2 * mRhsA[i] + 2 * mRhsB[i] + mRhsC[i]);
    }

  //LSODA
  /*

    C_FLOAT64 EndTime = mTime + dt;
    C_INT ITOL = 1; // mRtol scalar, mAtol scalar
    C_INT one = 1;
    long int two = 2;
    long int three = 3;
    double reltol = 0.1;
    double abstol = 0.5;

    C_INT DSize = mDWork.size();
    C_INT ISize = mIWork.size();

    //std::cout << "jhhjk" << &mVariables[0] << std::endl;

    mLSODA(&EvalF, //  1. evaluate F
           &mData.dim, //  2. number of variables
           &mVariables[0], //  3. the array of current concentrations
           &mTime, //  4. the current time
           &EndTime, //  5. the final time
           &ITOL, //  6. error control
           &reltol, //  7. relative tolerance array
           &abstol, //  8. absolute tolerance array
           &two, //  9. output by overshoot & interpolation
           &mLsodaStatus, // 10. the state control variable
           &one, // 11. further options (one)
           &mDWork[0], // 12. the double work array
           &DSize, // 13. the double work array size
           &mIWork[0], // 14. the int work array
           &ISize, // 15. the int work array size
           NULL, // 16. evaluate J (not given)
           &two);        // 17. the type of jacobian calculate (2)

    if (mLsodaStatus != 2)
      std::cout << mLsodaStatus << std::endl;
  */

  mpLayout->setState(mVariables);
}

void CLayoutEngine::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);}

void CLayoutEngine::evalF(const C_FLOAT64 * /* t */, const C_FLOAT64 * /* y */, C_FLOAT64 * ydot)
{
  //std::cout << *t << "  " << y << " " << &mVariables[0] << std::endl;

// assert(y == &mVariables[0]);

  calcRHS(mVariables, ydot);

  return;
}
