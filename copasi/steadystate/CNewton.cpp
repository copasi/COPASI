/**
 *  File name: CNewton.cpp
 *
 *  Programmer: Yongqun He
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the .cpp file for the class CNewton.
 *           It is an important approach to solve the steady state solution problem
 *
 */

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CNewton.h"
#include "tnt/lu.h"

//include clapack.h for eigenvalue calculations0
extern "C"
  {
    //#ifdef __cplusplus
    //#define __old__cplusplus __cplusplus
    //#undef __cplusplus
    //#endif
#include "clapack.h"       //use CLAPACK
    //#ifdef __old__cplusplus
    //#define __cplusplus __old__cplusplus
    //#undef __old__cplusplus
    //#endif
  }

#ifdef WIN32
#define max(a , b)  ((a) > (b) ? (a) : (b))
#define min(a , b)  ((a) < (b) ? (a) : (b))
#endif // WIN32

//default constructor
CNewton::CNewton()
{
  CONSTRUCTOR_TRACE;
  mModel = NULL;

  mNewtonLimit = DefaultNewtonLimit;
  mSs_nfunction = 0;

  mSs_solution = 0;

  mSs_x = NULL;
  mSs_xnew = NULL;
  //  mSs_dxdt = NULL;
  mSs_h = NULL;
  // initialize();
}

//destructor
CNewton::~CNewton() {cleanup(); DESTRUCTOR_TRACE; }

// initialize pointers
void CNewton::initialize()
{
  cleanup();
  unsigned C_INT32 dim = mModel->getIndMetab();

  mSs_xnew = new C_FLOAT64[dim];
  mSs_dxdt.newsize(dim);
  mSs_h = new C_FLOAT64[dim];
  mSs_jacob.setModel(mModel);
}

//Y.H.
//set up mSs_x and mSs_x's default values
//they should come from steady state class, though
void CNewton::setStartingPoint(const C_FLOAT64 * particleNumbers)
{
  pdelete(mSs_x);

  if (particleNumbers)
    {
      unsigned C_INT32 dim = mModel->getIndMetab();
      mSs_x = new C_FLOAT64[dim];

      for (unsigned C_INT32 i = 0; i < dim; i++)
        mSs_x[i] = particleNumbers[i];
    }
  else
    mSs_x = mModel->getInitialNumbers();
}

//set mModel
void CNewton::setModel(CModel & model)
{
  mModel = &model;

  initialize();
}

//get mModel
CModel * CNewton::getModel() const
  {
    return mModel;
  }

// set mSSRes
void CNewton::setSSRes(C_FLOAT64 aDouble)
{
  mSSRes = aDouble;
}

//get mSSRes
C_FLOAT64 CNewton::getSSRes() const
  {
    return mSSRes;
  }

// get mSs_xnew
const C_FLOAT64 * CNewton::getSs_xnew() const
  {
    return mSs_xnew;
  }

// get mSs_dxdt
const TNT::Vector < C_FLOAT64 > & CNewton::getSs_dxdt() const
  {
    return mSs_dxdt;
  }

// set mDerivFactor
void CNewton::setDerivFactor(C_FLOAT64 aDouble)
{
  mDerivFactor = aDouble;
}

// get mDerivFactor
C_FLOAT64 CNewton::getDerivFactor() const
  {
    return mDerivFactor;
  }
void CNewton::setNewtonLimit(C_INT32 limit) {mNewtonLimit = limit; }
C_INT32 CNewton::getNewtonLimit() const { return mNewtonLimit; }

// set mSs_nfunction
void CNewton::setSs_nfunction(C_INT32 aInt)
{
  mSs_nfunction = aInt;
}

// get mDerivFactor
C_INT32 CNewton::getSs_nfunction() const
  {
    return mSs_nfunction;
  }

// finds out if current state is a valid steady state
C_INT32 CNewton::getSs_solution(void) const
  {
    if (mSs_solution == SS_FOUND)
      return SS_FOUND;
    else
      return SS_NOT_FOUND;
  }

// finds out if current state is a valid steady state
C_INT32 CNewton::isSteadyState(void)
{
  return mSs_solution == SS_FOUND;
}

//similar to SS_Newton() in gepasi except a few modification
//
void CNewton::process(void)
{
  unsigned C_INT32 i, j, k;
  C_FLOAT64 maxrate, nmaxrate;
  C_INT32 info;
  mSs_solution = SS_NOT_FOUND;

  //by Yongqun He
  //get the dimensions of the matrix
  unsigned C_INT32 dim = mModel->getIndMetab();

  mModel->lSODAEval(dim, 0, mSs_x, &mSs_dxdt[0]);
  mSs_nfunction++;

  maxrate = xNorm(dim, &mSs_dxdt[0] - 1, 1);

  // Check whether we have already a steady state

  if (maxrate < mSSRes)
    mSs_solution = SS_FOUND;

  if (mSs_solution == SS_FOUND)
    {
      for (i = 0; i < dim; i++)
        if (mSs_x[i] < 0.0)
          {
            mSs_solution = SS_NOT_FOUND;
            break;
          }
    }

  if (mSs_solution == SS_FOUND)
    return ;

  // Start the iterations
  for (k = 0; k < mNewtonLimit && maxrate > mSSRes; k++)
    {
      mSs_jacob.jacobEval(mSs_x, min(mDerivFactor, maxrate), mSSRes);

      TNT::Matrix < C_FLOAT64 > LU = mSs_jacob.getJacob();
      TNT::Vector < unsigned C_INT32 > rowLU(dim);

      // LU decomposition of Jacobian
      info = TNT::LU_factor(LU, rowLU);
      // Gepasi: dgefa(mSs_jacob, dim, mSs_ipvt, &info);
      // COPASI: dgetrf(???) to get rid of TNT for performance reasons

      if (info != 0)
        {
          // jacobian is singular
          mSs_solution = SS_SINGULAR_JACOBIAN;

          return ;
        }

      // solve mSs_jacob . x = mSs_h for x (result in mSs_dxdt) ????
      TNT::LU_solve(LU, rowLU, mSs_dxdt);

      // Gepasi: dgesl(mSs_jacob, mModel->getIndMetab(), mSs_ipvt, mSs_dxdt, 0);
      // COPASI: dgetrf(???) to get rid of TNT for performance reasons

      nmaxrate = maxrate * 1.001;

      // copy values of increment to mSs_h
      for (i = 0; i < dim; i++)
        mSs_h[i] = mSs_dxdt[i];

      for (i = 0; (i < 32) && (nmaxrate > maxrate); i++)
        {
          for (j = 0; j < dim; j++)
            {
              mSs_xnew[j] = mSs_x[j] - mSs_h[j];
              mSs_h[j] /= 2;
            }

          mModel->lSODAEval(dim, 0, mSs_xnew, &mSs_dxdt[0]);
          mSs_nfunction++;
          nmaxrate = xNorm(dim, &mSs_dxdt[0] - 1, 1);
        }

      if (i == 32)
        {
          if (maxrate < mSSRes)
            {
              mSs_solution = SS_FOUND;
              // check if solution is valid

              for (i = 0; i < mModel->getIntMetab(); i++)
                if (mSs_x[i] < 0.0)
                  {
                    mSs_solution = SS_NOT_FOUND;
                    break;
                  }
            }
          else
            {
              mSs_solution = SS_DAMPING_LIMIT;
            }

          return ;
        }

      for (i = 0; i < dim; i++)
        mSs_x[i] = mSs_xnew[i];

      maxrate = nmaxrate;
    }

  if (maxrate < mSSRes)
    {
      mSs_solution = SS_FOUND;
      // check if solution is valid

      for (i = 0; i < dim; i++)
        if (mSs_x[i] < 0.0)
          {
            mSs_solution = SS_NOT_FOUND;
            break;
          }
    }
  else
    {
      mSs_solution = SS_ITERATION_LIMIT;
    }

  return ;
}

// Clean up internal pointer variables
void CNewton::cleanup(void)
{
  pdelete(mSs_x);
  pdelete(mSs_xnew);
  pdelete(mSs_h);
}
