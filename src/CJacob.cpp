/*****************************************************************************
* PROGRAM NAME: CJacob.cpp
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Implement the CJacob Class, its value is updated in steadyState()
*	       and output in Rep_Stability()			
*****************************************************************************/

#include "CJacob.h"

/**
 * Defaulut constructor
 */
CJacob::CJacob()
{
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
	mNfunction = 0;
	mNjacob = 0;

	mJacob.newsize(rows, cols);
}

/**
 * Deconstructor
 */
CJacob::~CJacob()
{
}

/**
 * evaluates the Jacobian matrix
 * @param src is the pointer of an array used for evaluating 
 * the Jacob Matrix
 * @param factor is modulation factor for finite differences derivation
 * @param res is the resolution of steady state
 */
void CJacob::jacobEval(C_FLOAT64 *src, C_FLOAT64 factor, C_FLOAT64 res)
{
	C_FLOAT64 K1, K2, K3;
	C_FLOAT64 *f1, *f2, store, temp;
	int i, j;

	// constants for differentiation by finite differences
	K1 = 1 + factor;
	K2 = 1 - factor;
	K3 = 2 * factor;

	// Arrays to store function value
	f1 = new C_FLOAT64[mJacob.num_rows()];
	f2 = new C_FLOAT64[mJacob.num_rows()];
	
	// iterate over all metabolites
	for (i = 0; i < mJacob.num_rows(); i++)
	{
		/** if y[i] is zero, the derivative will be calculated at a small 
		 *  positive value (no point in considering negative values!). 
		 *  let's stick with SSRes*(1.0+DerivFactor)
		 */
		
		store = src[i];

		if (store < res) temp = res * K1;
		else temp = store;
		
		src[i] = temp * K1;
		mModel.lSODAEval(0, 0, src, f1);
			
		mNfunction++;

		src[i] = temp * K2;
		mModel.lSODAEval(0, 0, src, f1);
		mNfunction++;

		for (j = 0; j < mJacob.num_rows(); j++) 
			mJacob[i][j] = (f1[j] - f2[j]) / (temp * K3);
		
		src[i] = store;
	}

	// clear memory
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
void CJacob::setModel(CModel model)
{
	mModel = model;
}
