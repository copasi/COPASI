/*****************************************************************************
 * PROGRAM NAME: CJacob.cpp
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: Implement the CJacob Class, its value is updated in steadyState()
 *        and output in Rep_Stability()
 *****************************************************************************/

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "model/model.h"
#include "CJacob.h"

/**
 * Default constructor
 */
CJacob::CJacob()
{
  CONSTRUCTOR_TRACE;
  mNfunction = 0;
  mNjacob = 0;
}

/**
 * User defined constructor
 * @param rows is the max row number of Jacob Matrix
 * @param cols is the max column number of Jacob Matrix
 */
CJacob::CJacob(int rows, int cols)
{
  CONSTRUCTOR_TRACE;
  mNfunction = 0;
  mNjacob = 0;

  mJacob.newsize(rows, cols);
}

/**
 * Destructor
 */
CJacob::~CJacob() {DESTRUCTOR_TRACE;}

/**
 * evaluates the Jacobian matrix
 * @param src is the pointer of an array used for evaluating
 * the Jacob Matrix
 * @param factor is modulation factor for finite differences derivation
 * @param res is the resolution of steady state
 */
void CJacob::jacobEval(const C_FLOAT64 *src, C_FLOAT64 factor, C_FLOAT64 res)
{
  C_FLOAT64 K1, K2, K3;
  C_FLOAT64 *Src, *f1, *f2, store, temp;
  int i, j, dim = mModel->getIndMetab();

  // constants for differentiation by finite differences
  K1 = 1 + factor;
  K2 = 1 - factor;
  K3 = 2 * factor;

  // Arrays to store function value
  Src = new C_FLOAT64[dim];
  for (i=0; i<dim; i++)
    Src[i] = src[i];

  f1 = new C_FLOAT64[dim];
  f2 = new C_FLOAT64[dim];

  // iterate over all metabolites
  for (i = 0; i < dim; i++)
    {
      /** if y[i] is zero, the derivative will be calculated at a small
       *  positive value (no point in considering negative values!).
       *  let's stick with SSRes*(1.0+DerivFactor)
       */

      store = Src[i];

      if (store < res) temp = res * K1;
      else temp = store;

      Src[i] = temp * K1;
      mModel->lSODAEval(dim, 0, Src, f1);
      mNfunction++;

      Src[i] = temp * K2;
      mModel->lSODAEval(dim, 0, Src, f2);
      mNfunction++;

      for (j = 0; j < dim; j++)
        mJacob[j][i] = (f1[j] - f2[j]) / (temp * K3);

      Src[i] = store;
    }

  // We have to reset the model
  mModel->lSODAEval(dim, 0, Src, f2);

  // clear memory
  delete [] Src;
  delete [] f1;
  delete [] f2;

  mNjacob++;
}

/**
 * return the Jacobian matrix
 */
TNT::Matrix < C_FLOAT64 > CJacob::getJacob()
{
  return mJacob;
}

/**
 * Set the Jacobian Matrix
 */
void CJacob::setJacob(int rows, int cols)
{
  mJacob.newsize(rows, cols);
}

/**
 * return the counter of func. evals
 */
C_INT32 CJacob::getNfunction()
{
  return mNfunction;
}

/**
 * return counter of jacob. evals
 */
C_INT32 CJacob::getNjacob()
{
  return mNjacob;
}

/**
 * Set the counter of func. evals
 */
void CJacob::setNfunction(C_INT32 func)
{
  mNfunction = func;
}

/**
 * Set the counter of func. evals
 */
void CJacob::setNjacob(C_INT32 jacob)
{
  mNjacob = jacob;
}

/**
 * Set the Model
 */
void CJacob::setModel(CModel * model)  // wsun  03/19/02
{
  /* :TODO: we need a copy constructor here */
  mModel = model;

  unsigned C_INT32 dim = mModel->getIndMetab();
  mJacob.newsize(dim,dim);
}
