/*****************************************************************************
* PROGRAM NAME: CMca.cpp
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Implement the CMca Class, its value is updated in simulation running
*	       and outputed in Rep_MCA()			
*****************************************************************************/

#include <cmath>      //for fabs()
#include <limits.h>

#include "copasi.h"
#include "utilities/utilities.h"
#include "model/model.h"
#include "CMca.h"

#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif //DBL_MAX

/**
 * Defaulut constructor
 */
CMca::CMca()
{
}

/**
 * User defined constructor
 * @param refer to Model and factor
 */
CMca::CMca(CModel model, C_FLOAT64 factor)
{
  Model = model;

  mDxv.newsize(Model.getTotSteps(), Model.getIndMetab());
  mFcc.newsize(Model.getTotSteps(), Model.getTotSteps());
  mGamma.newsize(Model.getIndMetab(), Model.getTotSteps());
  mSsx.resize(Model.getIndMetab() + 1);

  mFactor = factor;
}

/**
 * Deconstructor
 */
CMca::~CMca()
{
  delSsipvt();
}

/**
 * Set the Model
 */
void CMca::setModel(CModel model)
{
  Model = model;
}

/**
 * return the mDxv matrix
 * @return Matrix
 */
TNT::Matrix < C_FLOAT64 > CMca::getDxv()
{
  return mDxv;
}

/**
 * return the mFCC matrix
 * @return Matrix
 */
TNT::Matrix < C_FLOAT64 > CMca::getFcc()
{
  return mFcc;
}

/**
 * return the mGamma matrix
 * @return Matrix
 */
TNT::Matrix < C_FLOAT64 > CMca::getGamma()
{
  return mGamma;
}

/**
 *	Clear Dxv with zeros
 */
void CMca::clearDxv()
{
  register int i, j;

  for(i = 0; i < mDxv.num_rows(); i++)
    for(j = 0; j < mDxv.num_cols(); j++ )
      mDxv[i][j] = 0.0;
}

/**
 * Initialize mDxv with the unscaled elasticities
 * @param src is newtown variable, (is ss_x in Gespasi project) 
 * @param res is the resolution of steady state
 */
void CMca::initDxv(C_FLOAT64 res)
{
  register int i, j;
  C_FLOAT64 store, temp, *f1, *f2;
  C_FLOAT64 K1, K2, K3;

  // constants for differentiation by finite differences
  K1 = 1 + mFactor;
  K2 = 1 - mFactor;
  K3 = 2 * mFactor;

  // Arrays to store function value
  f1 = new C_FLOAT64[mDxv.num_rows()];
  f2 = new C_FLOAT64[mDxv.num_rows()];
	
  // load Dxv with elasticities
  for (j = 0; j < mDxv.num_cols(); j++)  
    {
      /**
       * if src[i+1] (x_ss[i+1]) is zero, the derivative will be calculated at a small 
       * positive value (no point in considering negative values!). 
       * let's stick with res*K1 (SSRes)
       */	
      store = mSsx[j+1];
      if (store < res) temp = res * K1;
      else temp = store;

      // let's take X_dx
      mSsx[j+1] = temp * K1;
      // Calcualte the fluxes
      for (i = 0; i < mDxv.num_rows(); i++)
	f1[i] = Model.getReactions()[i].calculate();
      // now X-dx
      mSsx[j+1] = temp * K2;
      // calculate the fluxes
      for (i = 0; i < mDxv.num_rows(); i++)
	f2[i] = Model.getReactions()[i].calculate();

      // set column j of Dxv
      for( i = 0; i < mDxv.num_rows(); i++ )
	mDxv[i][j] = (f1[i]-f2[i])/(temp*K3);

      // restore the value of (src[i])ss_x[i]
      mSsx[j+1] = store;
    }

  // Clean up memory
  delete [] f1;
  delete [] f2;
}

/**
 *	Calculates the flux-control coefficients
 *  @param refer to the condition when calculating
 */
void CMca::CalcFCC(int condition)
{
  register int i, j, k;

  if (condition == MCA_SINGULAR)
    {
      for (i = 0; i < mFcc.num_rows(); i++)
	for (j = 0; j < mFcc.num_cols(); j++)
	  mFcc[i][j] = 0.0;
    }
  else {
    // mFcc = I + mDxv * mGamma
    for (i = 0; i < mFcc.num_rows(); i++)
      for (j = 0; j < mFcc.num_cols(); j++)
	{
	  mFcc[i][j] = (i == j) ? 1.0 :0.0;
	  for (k = 0; k < mDxv.num_cols(); k++)
	    mFcc[i][j] += mDxv[i][k] * mGamma[k][j];
	}
  }
}

/**
 * Calculates the concentration-control coefficients
 */
int CMca::CalcGamma()
{
  register int i, j, k;
  C_FLOAT64 **aux1, **aux2;
  int dim;
  C_INT32 info;

  // Create auxiliary matrices as big as needed
  if (Model.getIndMetab() > Model.getTotSteps())
    dim = Model.getIndMetab() + 1;
  else dim = Model.getTotSteps() + 1;

  // Create aux1 and aux2
  aux1 = (C_FLOAT64 **) malloc((dim) * sizeof(*aux1));
  aux2 = (C_FLOAT64 **) malloc((dim) * sizeof(*aux2));

  for (i = 0 ; i < dim ; i++)
    {
      aux1[i] = (C_FLOAT64 *) malloc((dim) * sizeof(C_FLOAT64));
      aux2[i] = (C_FLOAT64 *) malloc((dim) * sizeof(C_FLOAT64));
    }

  // set mGamma to zeros
  for (i = 0; i < mGamma.num_rows(); i++)
    for (j = 0; j < mGamma.num_cols(); i++)
      mGamma[i][j] = 0.0;

  // aux1 = rstoi * mDxv
  for (i = 0; i < Model.getIndMetab(); i++)
    for (j = 0; j < Model.getIndMetab(); j++)
      {
	aux1[i][j] = 0.0;
	for (k = 0; k < Model.getTotSteps(); k++)
	  aux1[i][j] += (C_FLOAT64) Model.getRedStoi()[i][k] * mDxv[k][j];
      }

  // aux2 = aux1 * m1 (shifting indices for dgefa)
  for (i = 0; i < Model.getIndMetab(); i++)
    for (j = 0; j < Model.getIndMetab(); j++)
      {
	aux2[i+1][j+1] = 0.0;
	for (k = 0; k < Model.getIndMetab(); k++)
	  aux2[i+1][j+1] += aux1[i][k] * Model.getL()(k+1,j+1); //???
      }

  // LU decomposition if aux2 (for inversion)
  //	dgefa -> luX??
  dgefa(aux2, Model.getIndMetab(), mSsipvt, &info);

  if (info != 0)
    {
      // matrix is singular
      // return now (mGamma[i][j] = 0)
      // delete matrices
      for(i = 0; i < dim; i++)
	{
	  free((void *) aux1[i]);
	  free((void *) aux2[i]);
	}
      free((void *) aux1);
      free((void *) aux2);

      return MCA_SINGULAR;
    }

  // set aux1 to the identity matrix (for inversion with dgesl)
  for (i = 0; i < Model.getIndMetab(); i++)
    for (j = 0; j < Model.getIndMetab(); j++)
      aux1[i+1][j+1] = (i == j)? 1.0 : 0.0;
	
  // now invert aux2 (result in aux1)
  for (i = 0; i < Model.getIndMetab(); i++)
    dgesl(aux2, Model.getIndMetab(), mSsipvt, aux1[i+1], 1);
  // aux2 = - ml * aux1 (shifting indeces back to 0 again)
  for (i = 0; i < Model.getIndMetab(); i++)
    for (j = 0; j < Model.getIndMetab(); j++)
      {
	aux2[i][j] = 0.0;
	for (k = 0; k < Model.getIndMetab(); k++)
	  aux2[i][j] -= (C_FLOAT64)Model.getmLU()[i][k] * aux1[k+1][j+1];
      }
	
  // mGamma = aux2 *RedStoi
  for (i = 0; i < Model.getIndMetab(); i++)
    for (j = 0; j < Model.getTotSteps(); j++)
      for (k = 0; k < Model.getIndMetab(); k++)
	mGamma[i][j] += aux2[i][k] * (C_FLOAT64) Model.getRedStoi()[k][j];

  // delete matrices
  for(i = 0; i < dim; i++)
    {
      free((void *) aux1[i]);
      free((void *) aux2[i]);
    }
  free((void *) aux1);
  free((void *) aux2);

  return MCA_OK;
}

/**
 * Initialize ss_ipvt
 */
void CMca::initSsipvt()
{
  mSsipvt = (C_INT32 *) malloc((Model.getIndMetab()) * sizeof(C_INT32));
}

/**
 * Deletet ss_ipvt
 */
void CMca::delSsipvt()
{
  free((void *) mSsipvt);
}


/**
 * Initialize the MCA matrices: mDxv, mFcc, mGamma
 */
void CMca::init()
{
  mDxv.newsize(Model.getTotSteps(), Model.getTotMetab());
  mFcc.newsize(Model.getTotSteps(), Model.getTotSteps());
  mGamma.newsize(Model.getIndMetab(), Model.getTotSteps());
  mSsx.resize(Model.getTotMetab() + 1);
}

/**
 * the steady state MCA entry point
 * @param ss_solution refer to steady-state solution
 * @param refer to the resolution 
 */
int CMca::CalculateMCA(int ss_solution, int res)
{
  int ret;

  // Initialize the ss_ipvt vector
  initSsipvt();

  // Create mDxv, mFcc, mGamma
  init();

  if (!ss_solution) initDxv(res);
  else clearDxv();

  ret = CalcGamma();
  CalcFCC(ret);
	
  if (!mSSReder) ScaleMCA(ret, res);

  return ret;
}

/** 
 * Read SSMCAUnscaled from configuration file
 */
C_INT32 CMca::load(CReadConfig & configBuffer)
{
  C_INT32	Fail = 0;

  if ((Fail = configBuffer.getVariable("SSMCAUnscaled", "C_INT16",
				       (void *) &mSSReder,
				       CReadConfig::LOOP)))
    return Fail;

  return Fail;
}

/**
 * Scales the coefficients (i.e. Kacser format, rather than Reder)
 * @param refer to the condition
 * @param refer to the resolution
 */	
void CMca::ScaleMCA(int condition, int res)
{
  register int i, j;

  // if previous calcutations failed return now
  if( condition != MCA_OK ) return;

  // Scale Dxv
  for(i = 0; i < Model.getTotSteps(); i++)
    for(j = 0; j < Model.getTotMetab(); j++)
      {
	// change the use of Col[] and Row[] to mStepsX and mMetabolitesX
	if( fabs( Model.getStepsX()[i]->getFlux() ) >= res )
	  {
	    mDxv[i][j] *=   *Model.getMetabolitesX()[j]->getConcentration()
	      * Model.getMetabolitesX()[j]->getCompartment()->getVolume()
	      / Model.getStepsX()[i]->getFlux();
	  }
	else mDxv[i][j] = DBL_MAX;
      }

  // Scale Gamma
  for(i = 0; i < Model.getIndMetab(); i++)
    for(j = 0; j < Model.getTotSteps(); j++)
      {
	if( fabs(*Model.getMetabolitesX()[i]->getConcentration()) >= res)
	  mGamma[i][j] *=   Model.getStepsX()[j]->getFlux() 
	    / (*Model.getMetabolitesX()[i]->getConcentration() 
	       *
	       Model.getMetabolitesX()[j]->getCompartment()->getVolume());
	else mGamma[i][j] = DBL_MAX;
      }

  // Scale FCC
  for(i = 0; i < Model.getTotSteps(); i++)
    for(j = 0; j < Model.getTotSteps(); j++)
      {
	if( fabs( Model.getStepsX()[i]->getFlux()  ) >= res )
	  mFcc[i][j] *=   Model.getStepsX()[j]->getFlux()  
	    / Model.getStepsX()[i]->getFlux();
	else mFcc[i][j] = DBL_MAX;
      }

}

/**
 * the time dependent MCA entry point
 * @param refer to the resolution
 */
void CMca::CalculateTimeMCA(int res)
{
  register int i, j;

  mSsx.resize(Model.getTotMetab());

  //copy concentrations to ss_x
  for(i = 0; i < Model.getTotMetab(); i++)
    mSsx[i+1] = *Model.getMetabolitesX()[i]->getConcentration() * 
      Model.getMetabolitesX()[i]->getCompartment()->getVolume();

  // calculate the elasticites
  initDxv(res);

  // scale the elasticities if needed
  if (mSSReder == 0)
    {
      for(i = 0; i < Model.getTotSteps(); i++)
	for(j = 0; j < Model.getTotMetab(); j++)
	  {
	    if( fabs( Model.getStepsX()[i]->getFlux() ) >= res )
	      mDxv[i][j] *= *Model.getMetabolitesX()[j]->getConcentration() / 
		Model.getStepsX()[i]->getFlux();
	    else mDxv[i][j] = DBL_MAX;
	  }

    }

}

/**
 * Return the mSSx vector for calculate time mca
 * @return vector <C_FLOAT64>
 */
vector <C_FLOAT64> CMca::getSsx()
{
  return mSsx;
}

/**
 *  Saves the SSReder of the object to a CWriteConfig object.
 *  @param pconfigbuffer reference to a CWriteConfig object.
 *  @return mFail
 *  @see mFail
 */
C_INT32 CMca::save(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;

  if ((Fail = configbuffer.setVariable("SSMCAUnscaled", "C_INT16",
				       &mSSReder)))
    return Fail;

  return Fail;
}
