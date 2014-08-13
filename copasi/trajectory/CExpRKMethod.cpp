// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 *   CExpRKMethod
 *
 *   This class is the ODE solver in terms Ronge-Kutta Method ODE45.
 *   
 *   File name: CExpRKMethod.cpp
 *   Author: Shuo Wang
 *   Email: shuowang.learner@gmail.com
 *
 *   Last change: 07, July 2014
 *
 */

#include "CExpRKMethod.h"
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <string.h>


int compare(const void *r1, const void *r2)
{
    if((*(SRoot*)r1).t < (*(SRoot*)r2).t)
        return -1;
    else if((*(SRoot*)r1).t == (*(SRoot*)r2).t)
        return 0;
    else
        return 1;
}


//*********************************//
//* Constructor and Destructor    *//
//*********************************//

/*
 * Default Constructor
 */
CExpRKMethod::CExpRKMethod()
{  
    // Default error tolerances
    mAbsTol = 1e-12;
    mRelTol = 1e-10;

    // Default function pointers
    mDerivFunc = NULL;
    mEventFunc = NULL;
  
    // Default system state
    mDim     = NULL;
    mInitTCp = 0;
    mT       = 0;
    mTEnd    = 0;
    mTNew    = 0;
    mTOld    = 0;
    mY       = NULL;
    mYNew    = NULL;
    mYOld    = NULL;
    mK       = NULL;

    // Default coefficients
    mP       = 0;
    mStage   = 0;
    mOrderY  = 0;
    mOrderYp = 0;

    // Default step size related 
    mh         = 0;
    mhMin      = 0;
    mhMax      = 0;
    mFac       = 0;
    mFacMin    = 0;
    mFacMax    = 0;
    mFacMaxRej = 0;

    // Default solver status
    mStatis         = false;
    mhNoFailed      = false;
    mHasEvent       = false;
    mODEState       = 0;
    mODEStateRecord = 0;

    // Default root finder related
    mRootId       = -10;
    mRootNum      = 0;
    mRootValue    = NULL;
    mRootValueOld = NULL;
    mRootQueue    = NULL;
    mQueueLen     = 0;
    mQueueSite    = 0;
    mHasMultipleRoots = false;

    // Default statistic variables
    mStepNum   = 0;
    mAcceptNum = 0;
    mRejectNum = 0;
    mfEvalNum  = 0;
    mrEvalNum  = 0;

    // Default tempt variable
    mZ1 = NULL;
    mZ2 = NULL;
    mZ3 = NULL;
    mIn1 = NULL;
    mIn2 = NULL;
    mIn3 = NULL;
    mtArray = NULL;
    mFindRoots = false;
    mFindSlow  = false;
    return;
}

/*
 * Default Destructor
 */
CExpRKMethod::~CExpRKMethod()
{
    if (mDerivFunc)
        mDerivFunc = NULL;

    if (mEventFunc)
        mEventFunc = NULL;

    if (mYNew)
    {
        delete [] mYNew;
        mYNew = NULL;
    }

    if (mYOld)
    {
        delete [] mYOld;
        mYOld = NULL;
    }

    if(mK)
    {
        for(int i= (int)mStage; i>=0; i--)
            delete [] mK[i];
      
        delete [] mK;
        mK = NULL;
    }

    if(mRootQueue)
    {
        delete [] mRootQueue;
        mRootQueue = NULL;
    }


    if(mRootValueOld)
    {
        delete [] mRootValueOld;
        mRootValueOld = NULL;
    }

    if(mRootValue)
    {
        delete [] mRootValue;
        mRootValue = NULL;
    }


    if(mZ1)
    {
        delete [] mZ1;
        mZ1 = NULL;
    }

    if(mZ2)
    {
        delete [] mZ2;
        mZ2 = NULL;
    }

    if(mZ3)
    {
        delete [] mZ3;
        mZ3 = NULL;
    }

    if(mIn1)
    {
        delete [] mIn1;
        mIn1 = NULL;
    }

    if(mIn2)
    {
        delete [] mIn2;
        mIn2 = NULL;
    }

    if(mIn3)
    {
        delete [] mIn3;
        mIn3 = NULL;
    }

    if(mtArray)
    {
        delete [] mtArray;
        mtArray = NULL;
    }
    return;
}


//*************************//
//* Main Process Function *//
//*************************//

/**
 * Main function processing integration along time 
 */
void CExpRKMethod::integrate()
{
    //====================//
    // 1 check mODEstate  //
    //====================//
    checkODEState();
    if(mODEState == 1)//Restart
    {
        mInitTCp = mT;
        mTOld    = mT;
        /*
        for (size_t i = 0; i < *mDim; ++i)
            mYOld[i] = mY[i];
        */
        memcpy(mYOld, mY, (*mDim)*sizeof(C_FLOAT64));

        setInitialStepSize();
        mDerivFunc(mDim, &mTOld, mYOld, mK[0]);//record derivative to
 
        //Calculate root at initial time
        if(mHasEvent)
            (*mEventFunc)(mDim, &mTOld, mYOld, &mRootNum, mRootValueOld);

        mHasMultipleRoots = false;
    }
    else if (mODEState == 3) // has event
    {
        //If events queue isn't empty, deal with the next event, and return
        if (!queueIsEmpty())
	{ 
            calculateRootState();
            return;
	}
        else
	{ //no roots
            mODEState = 1;
            advanceStep();
            mHasMultipleRoots = false;    
	}
    }
    else if(mODEState == -2)//has error
        return;

    //=============//
    // 2 Main Loop //
    //=============//
    while(mTOld < mTEnd)
    {      
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
        // (1) Check Whether mT is close to mTEnd //
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
        if (1.1*mh >= (mTEnd-mTOld))
            mh = mTEnd - mTOld;

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
        // (2) Set Some Parameters before One Step //
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
        mhNoFailed = true;      

        //~~~~~~~~~~~~~~~~~~~~~~~//
        // (3) Continue One Step //
        //~~~~~~~~~~~~~~~~~~~~~~~//
        while(true)
	{
            // (i) Do One Single Step
            doOneStep();
	  
            // (ii) Update Statistic Record
            mfEvalNum += mStage;
	  
            // (iii) Estimate Error
            C_FLOAT64 error = estimateError();

            //(iv) Update step size mh
            if (error > 1.0) // Step Rejected
	    {
                mhNoFailed = false;
                mRejectNum++;
                mh *= 0.5; // Use half step size h

                if (mh < mhMin)
		{
                    mODEState = -2;
                    mODEStateRecord = mODEState;
                    std::cout << "Failure at t=" << mTOld << std::endl;
                    std::cout << "Unable to meet integration tolerances without reducing the step size below the smallest value!" << std::endl;
                    return;
		}
	    }
            else // Step Accept
	    {
                mhMin = deps(mTNew) * 16.0;
                mAcceptNum++;
	      
                C_FLOAT64 fac = pow(1/error, 1.0/(mP+1.0));
                if (!mhNoFailed) //previous step is rejected
                    mh *= dmin(mFacMaxRej, dmax(mFacMin, mFac*fac));
                else
                    mh *= dmin(mFacMax, dmax(mFacMin, mFac*fac));

                break;
	    }
	} // end while
        mStepNum++;

        //~~~~~~~~~~~~~~~~~~//
        // (4) Check Events //
        //~~~~~~~~~~~~~~~~~~//
        if(mHasEvent)
	{
            (*mEventFunc)(mDim, &mTNew, mYNew, &mRootNum, mRootValue);
            ++mrEvalNum;
	}

        checkRoots();

        if (mHasEvent && mFindRoots)
            findRoots();

        if (mHybrid && mFindSlow)
            findSlowReaction();

        if (!queueIsEmpty()) //has events
	{
            //do sorting
            if(mQueueLen >= 2)
	    {
                qsort(mRootQueue, mQueueLen, sizeof(SRoot), compare);
                shrinkQueue(); //remove the first root with duplicate id and roots following it 
	    }

            calculateRootState();
            return;
	}

        //~~~~~~~~~~~~~~~~~~~~~~//
        // (5) Advance New Step //
        //~~~~~~~~~~~~~~~~~~~~~~//
        advanceStep();
    } // end while

    //~~~~~~~~~~~~~~~~~~~~~~~~~~//
    //  Integration Finished    //
    //~~~~~~~~~~~~~~~~~~~~~~~~~~//

    mODEState = 4;
    mT = mTEnd;
    /*
    for(size_t i=0; i<*mDim; i++)
        mY[i] = mYNew[i];
    */
    memcpy(mY, mYNew, (*mDim)*sizeof(C_FLOAT64));

    return;
}


/**
 * Check the state attribute mODEState.
 * If mODEState=0, first call of this method, initialization are required 
 * If mODEState=1, restart this method, method key parameters should be checked
 * If mODEState=2, continue from last step which has an event (mODEState=3).
 *                 First check if events left. If not, continue, else return with next event
 * Else, method has error.
 */
void CExpRKMethod::checkODEState()
{
    if (mODEState == 0) // need initialization
    {
        // initialize coefficients, mY and mK, 
        // in case that dimension is updated 
        // for a new problem
        initialize();
        if (mODEState == -2)
	{
            mODEStateRecord = -2;
            return;
	}
    }
    else if (mODEState == 1)
    {
        // In such case, parameters must be changed by
        // users, such as error tolerance and mInitY, 
        // exept the dimension of system.
        checkParameter();
        if (mODEState == -2)
	{
            mODEStateRecord = -2;
            return;
	}
    }
    else if(mODEState == 2)
    {
        //Deal with errors 
        if (mODEStateRecord != 3) 
	{
            if (mODEStateRecord == -2)
                std::cout << "Errors happen when continuing integration. Parameters should be check!" << std::endl;

            if (mODEStateRecord == 4)
                std::cout << "Integration has been finished. Please restart this solver by setting new time span!" << std::endl;

            mODEState = -2;
            mODEStateRecord = mODEState;
            return;
	}
        else
	{
            mODEState = 3;
            mODEStateRecord = mODEState;
            return;
	}
    }
    else
    {
        std::cout << "mODEState should be set as 0, 1 or 2!" << std::endl;
        return;
    }

    return;
}


/*
 * doOneStep()
 * This is a virtual function for RK Method which calculates approximated derivatives,
 * new Y and new T.
 */
void CExpRKMethod::doOneStep()
{
    C_FLOAT64 t;
    // (1) Calculate mK[1] to mK[mStage-1]
    for(size_t s=1; s<mStage; s++)
    {
        t = mTOld + mh*mC[s];//tmp time
        memcpy(mZ1, mYOld, (*mDim)*sizeof(C_FLOAT64));

        for(size_t i=0; i<s; i++) //tmp Y + Yp*h
	{
            C_FLOAT64 a = mA[s][i] * mh;
            for (size_t j=0; j<*mDim; j++)
                mZ1[j] += mK[i][j] * a;
	}

        mDerivFunc(mDim, &t, mZ1, mK[s]);
    }

    // (2) New Time, mTNew
    size_t s = mStage-1;
    mTNew = mTOld + mh;
  
    // (3) New Y, mYNew
    memcpy(mYNew, mYOld, (*mDim)*sizeof(C_FLOAT64));

    for(size_t s=0; s<mStage; s++)
    {
        C_FLOAT64 b = mB[s] * mh;
        for (size_t i=0; i<*mDim; i++)
            mYNew[i] += b * mK[s][i];
    }

    // (4) New Yp, recording it into last row of mK
    mDerivFunc(mDim, &mTNew, mYNew, mK[mStage]);

    return;
}


/*
 * estimateError()
 * Function that calculate error in terms of algorithms in book ""
 * Chapter II, Automatic Step Size Control, pp 167-169.
 */
C_FLOAT64 CExpRKMethod::estimateError()
{
    // (1) Calculate |ynew - ynew*| in terms of mE
    for (size_t i=0; i<*mDim; i++)
        mZ2[i] = 0;

    for(size_t s=0; s<mStage+1; s++)
    {
        C_FLOAT64 e = mE[s] * mh;
        for(size_t i=0; i<*mDim; i++)
            mZ2[i] += e * mK[s][i];
    }


    // (2) Calculate Standard sc=Atol + max(|y|,|ynew|)*Rtol
    for(size_t i=0; i<*mDim; i++)
        mZ3[i] = mAbsTol + dmax(dabs(mYOld[i]), dabs(mYNew[i]))*mRelTol;

    // (3) Calculate Error
    C_FLOAT64 error = 0, tmp;
    for (size_t i=0; i<*mDim; i++)
    {
        tmp = mZ2[i]/mZ3[i];
        error += tmp*tmp;
    }

    error = sqrt(error/(*mDim));

    return error;
}



/*
 * advanceStep()
 * Set new mT, mY and mK[0]
 */
void CExpRKMethod::advanceStep()
{
    mTOld = mTNew;
    memcpy(mYOld, mYNew, (*mDim)*sizeof(C_FLOAT64));
    memcpy(mK[0], mK[mStage], (*mDim)*sizeof(C_FLOAT64));

    if(mEventFunc)
        memcpy(mRootValueOld, mRootValue, (mRootNum)*sizeof(C_FLOAT64));

    clearQueue();
    return;
}


//***************************************//
//* Functions for System Initialization *//
//***************************************//
/*
 * initialize()
 * Initialize statistic record variables, coefficients for RK method, mODEState 
 * and check event function mEventFunc.
 */
void CExpRKMethod::initialize()
{
    checkParameter();
    if (mODEState == -2)
        return;

    setStatRecord();
    setCoeff();

    mODEState = 1;

    if (!mEventFunc) //no event 
    {
        mHasEvent = false;
        mRootNum = 0;
    }
    else
    {
        mHasEvent = true;

        if (mRootValueOld)
            delete [] mRootValueOld;
        mRootValueOld = new C_FLOAT64[mRootNum];

        if (mRootValue)
            delete [] mRootValue;
        mRootValue    = new C_FLOAT64[mRootNum];

        clearQueue();
    }

    allocateSpace();

    return;
}

/**
 * Update time, results and other necessary stuff
 */
void CExpRKMethod::allocateSpace()
{  
    // ----(1)----
    //----Set mK----
    if(mK)
    {
        for(int i = (int)mStage; i >= 0; i--)
            delete [] mK[i];
      
        delete [] mK;
    }

    mK = new C_FLOAT64*[mStage+1];
    for (size_t r = 0; r < mStage+1; r++)
        mK[r] = new C_FLOAT64[*mDim];
    
    //----Set mYNew----
    if(mYNew)
        delete [] mYNew;

    mYNew = new C_FLOAT64[*mDim];

    //----Set mYCp----
    if(mYOld)
        delete [] mYOld;

    mYOld = new C_FLOAT64[*mDim];
        
    // ----(2)----
    size_t size = (*mDim>mRootNum) ? *mDim : mRootNum;
    size = (size>(MAX_STAGE+2)) ? size : (MAX_STAGE+2);
    if (mZ1)
        delete [] mZ1;
  
    mZ1 = new C_FLOAT64[size];

    if (mZ2)
        delete [] mZ2;
  
    mZ2 = new C_FLOAT64[size];

    if (mZ3)
        delete [] mZ3;
  
    mZ3 = new C_FLOAT64[size];

    if (mIn1)
        delete [] mIn1;
  
    mIn1 = new C_FLOAT64[size];

    if (mIn2)
        delete [] mIn2;
  
    mIn2 = new C_FLOAT64[size];

    if (mIn3)
        delete [] mIn3;
  
    mIn3 = new C_FLOAT64[size];

    if (mtArray)
        delete [] mtArray;

    mtArray = new C_FLOAT64[5];

    // ----(3)---- 
    size = 0;
    if(mEventFunc)
        size += mRootNum;

    if(mHybrid)
        ++size;

    if (mRootQueue)
        delete [] mRootQueue;
 
    mRootQueue = new SRoot[2*size+2];
    clearQueue();
    return;
}

/**
 * Set coefficients for ODE45
 */
void CExpRKMethod::setCoeff()
{
    mP       = 4;
    mStage   = 6;
    mOrderY  = 4;
    mOrderYp = 3;

    //----Set mA----
    C_FLOAT64 A[6][6] = {
        {          0,            0,           0,         0,            0,  0},
        {       1./5,            0,           0,         0,            0,  0},
        {      3./40,        9./40,           0,         0,            0,  0},
        {     44./45,      -56./15,       32./9,         0,            0,  0},
        {19372./6561, -25360./2187, 64448./6561, -212./729,            0,  0},
        { 9017./3168,     -355./33, 46732./5247,   49./176, -5103./18656,  0}
    };
  
    for(size_t r=0; r<mStage; r++)
    {
        for (size_t c=0; c<mStage; c++)
            mA[r][c] = A[r][c];
    }

    //----Set mC----
    C_FLOAT64 C[6] = {0, 1./5, 3./10, 4./5, 8./9, 1.};
    for(size_t c=0; c<mStage; c++)
        mC[c] = C[c];

    //----Set mB----
    C_FLOAT64 B[6] = {35./384, 0, 500./1113, 125./192, -2187./6784, 11./84};
    for(size_t c=0; c<mStage; c++)
        mB[c] = B[c];

    //----Set mE----
    C_FLOAT64 E[7] = {71./57600, 0, -71./16695, 71./1920, -17253./339200, 22./525, -1./40};
    for(size_t c=0; c<mStage+1; c++)
        mE[c] = E[c];

    //----Set mI----
    C_FLOAT64 I[7][4] = {
        {1.,  -183./64,     37./12,   -145./128},
        {0,          0,          0,           0},
        {0,  1500./371, -1000./159,   1000./371},
        {0,   -125./32,    125./12,    -375./64},
        {0, 9477./3392,  -729./106, 25515./6784},
        {0,     -11./7,      11./3,     -55./28},
        {0,       3./2,        -4.,        5./2}
    };

    for(size_t r=0; r<mStage+1; r++)
    {
        for(size_t c=0; c<mOrderY; c++)
            mI[r][c] = I[r][c];
    }

    return;
}


/*
 * setStatRecord()
 * Function is used to set statistc record related variables to be 0
 */
void CExpRKMethod::setStatRecord()
{
    mStepNum   = 0;
    mAcceptNum = 0;
    mRejectNum = 0;
    mfEvalNum  = 0;
    mrEvalNum  = 0;
    return;
}


/*
 * setInitialStepSize()
 * Function is used to set the initial step size mh. Algorithm which is applied 
 * is the one given in Book "Solving Ordinary Differential Equitions I", page
 * 169. Vector norm is the infinity norm picking the element having maximum 
 * absolute value.
 */
void CExpRKMethod::setInitialStepSize()
{
    // (1) First, set parameters, related step size control
    C_FLOAT64 absT   = dabs(mTOld);

    mhMin      = 16.0 * deps(mTOld);
    mhMax      = dabs(mTEnd-mTOld) / 10;
    mFac       = 0.8;
    mFacMin    = 0.1;
    mFacMax    = 4;
    mFacMaxRej = 1.0;
  
    C_FLOAT64 d0, d1, d2, h0, h1;
  
    // (2) Calculate h0
    d0 = infNorm(*mDim, mYOld);  
    mDerivFunc(mDim, &mTOld, mYOld, mZ1);//mZ1 is y'(t)
    d1 = infNorm(*mDim, mZ1);

    if ((d0<1.0e-5) || (d1<1.0e-5))
        h0 = 1.0e-6;
    else
        h0 = 0.01*(d0/d1);

    // (3) Calculate h1
    for(size_t i=0; i<*mDim; i++)
        mZ3[i] = mYOld[i] + h0*mZ1[i]; // mZ3 is y(t+h0)

    C_FLOAT64 tCp = mTOld;
    mTOld += h0;
    mDerivFunc(mDim, &mTOld, mZ3, mZ2);// mZ2 is y'(t+h0)
    for(size_t i=0; i<*mDim; i++)
        mZ3[i] = (mZ1[i]-mZ2[i])/h0;  // mZ3 is y''(t+h0)

    d2 = infNorm(*mDim, mZ3);

    C_FLOAT64 tmp = dmax(d1, d2);
    if (tmp <= 1.0e-15)
        h1 = dmax(1.0e-6, h0*1.0e-3);
    else
        h1 = pow(0.01/tmp, 1.0/(mP+1.0));

    // (4) Calculate h
    mh = dmin(100*h0, h1);

    mTOld = tCp;

    return;

}


//************************//
// Root Finder Functions *//
//************************//
/**
 * Set initial step size of integrator
 */
void CExpRKMethod::interpolation(const C_FLOAT64 tInterp, C_FLOAT64 *yInterp)
{
    C_FLOAT64 tmp = (tInterp-mTOld) / (mTNew-mTOld);
    C_FLOAT64 S[MAX_STAGE];

    //S[0] = tmp * (mTNew-mTOld);
    S[0] = tInterp - mTOld;
    for(size_t i = 1; i < mOrderY; i++)
        S[i] = S[i-1]*tmp;

    memcpy(yInterp, mYOld, (*mDim)*sizeof(C_FLOAT64));

    for (size_t s = 0; s < mStage+1; s++)
    {
        tmp = 0;
        for (size_t j = 0; j < mOrderY; j++)
            tmp += S[j] * mI[s][j];

        for (size_t d = 0; d < (*mDim); d++)            
            yInterp[d] += tmp * mK[s][d];
    }

    return;
}

/**
 * Check whether there is a root
 */
void CExpRKMethod::checkRoots()
{
    mFindRoots = false;
    mFindSlow  = false;

    if (mHasEvent)
    {
        C_FLOAT64 step = (mTNew-mTOld)/4;
        C_FLOAT64 *interY = mZ1;

        mtArray[0] = mTOld;
        mtArray[1] = mTOld+step;
        mtArray[2] = mTOld+2*step;
        mtArray[3] = mTOld+3*step;
        mtArray[4] = mTNew;
 
        //Caculate Root Interpolation Values at times of array tArray
        interpolation(mtArray[1], interY); 
        (*mEventFunc)(mDim, &mtArray[1], interY, &mRootNum, mIn1);
        interpolation(mtArray[2], interY);
        (*mEventFunc)(mDim, &mtArray[2], interY, &mRootNum, mIn2);
        interpolation(mtArray[3], interY);
        (*mEventFunc)(mDim, &mtArray[3], interY, &mRootNum, mIn3);
        mrEvalNum += 3;
  
        for(size_t r=0; r<mRootNum; ++r)
	{
            if(mRootValueOld[r]*mIn1[r]<=0 || mIn1[r]*mIn2[r]<=0 ||
               mIn2[r]*mIn3[r]<=0 || mIn3[r]*mRootValue[r]<=0)
	    {
                mFindRoots = true;
                break;
	    }
	}
    }

    if(mHybrid)
    {
        if(mYOld[*mDim-1]*mYNew[*mDim-1]<=0)
            mFindSlow = true;
    }

    return;
}

/**
 * Locate roots
 */
void CExpRKMethod::findRoots()
{
    SRoot root;
    int count;
    C_FLOAT64 tol = deps(dabs(mTOld)) * 128;
    C_FLOAT64 leftV, rightV, leftT, rightT;

    for (size_t r=0; r<mRootNum; ++r)
    {      
        count = 0;
        for (size_t s=0; s<4; ++s)
	{
            leftT = mtArray[s]; rightT = mtArray[s+1];
            switch(s)
	    {
	    case 0:
                leftV = mRootValueOld[r]; rightV = mIn1[r];
                break;
	    case 1:
                leftV = mIn1[r]; rightV = mIn2[r];
                break;
	    case 2:
                leftV = mIn2[r]; rightV = mIn3[r];
                break;
	    case 3:
                leftV = mIn3[r]; rightV = mRootValue[r];
                break;
	    }

            if ((leftV * rightV > 0) || (count >= 2))
                continue;
	  
            root.id = r;
            ++count;

            if(dabs(leftV) < deps(0)) //left value == 0
                root.t = leftT;
            else if(dabs(rightV) < deps(0)) //right value == 0
                root.t = rightT;
            else if(dabs(leftT - rightT) < tol) //interval is too small
	    {
                if(dabs(leftV) < dabs(rightV))
                    root.t = leftT;
                else
                    root.t = rightT;
	    }
            else
	    {
                C_FLOAT64 threshold = 1e-6, slope = dabs((rightV-leftV) / (rightT - leftT));

                if (slope > threshold)
                    root.t = rootFindBySecant(r, leftT, leftV, rightT, rightV);
                else
                    root.t = rootFindByFalsi(r, leftT, leftV, rightT, rightV);
	    }

            queuePush(root);
	}	
    }
    return;
}


/**
 * Locate roots in terms of Secant Method
 */
C_FLOAT64 CExpRKMethod::rootFindBySecant(const size_t id, 
					 const C_FLOAT64 leftT, const C_FLOAT64 leftV, 
					 const C_FLOAT64 rightT, const C_FLOAT64 rightV)
{
    int maxIter = 20;
    C_FLOAT64 tol = deps(dabs(leftT)) * 128;
    C_FLOAT64 *yTry = mZ1, *rArray = mZ2;
    C_FLOAT64 x1 = leftT, y1 = leftV, tTry;
    C_FLOAT64 delta, yp;

    tTry = x1 + dmax((rightT-leftT)/10.0, tol);
    interpolation(tTry, yTry);
    (*mEventFunc)(mDim, &tTry, yTry, &mRootNum, rArray);
    ++mrEvalNum;

    yp = (rArray[id]-y1) / (tTry-x1);

    for (int i=0; i<maxIter; ++i)
    {
        delta = -y1 / yp;
        tTry  =  x1 + delta;

        interpolation(tTry, yTry);
        (*mEventFunc)(mDim, &tTry, yTry, &mRootNum, rArray);
        ++mrEvalNum;

        if ((dabs(delta)<=tol) || (dabs(rArray[id])<deps(0)))
	{
            mrEvalNum += i+1;
            return tTry;
	}

        if((tTry>rightT) || (tTry<leftT))
            std::cout << "Secant Method is dealing with t out of range [mT, mTNew]" << std::endl;

        yp = (rArray[id]-y1) / delta;
        x1 = tTry; y1 = rArray[id];
    }

    std::cout << "Secant Method executed more than " << maxIter << " times!" << std::endl;
    return x1;
}

/**
 * Locate roots in terms of Bisection Method
 */
C_FLOAT64 CExpRKMethod::rootFindByBisection(const size_t id, 
					    const C_FLOAT64 leftT, const C_FLOAT64 leftV,
					    const C_FLOAT64 rightT, const C_FLOAT64 rightV)
{
    int maxIter = 50;
    C_FLOAT64 tol = deps(dabs(leftT)) * 128;
    C_FLOAT64 *yTry = mZ1, *rArray = mZ2;
    C_FLOAT64 x1 = leftT, y1 = leftV, x2 = rightT, y2 = rightV, tTry;

    for (int i=0; i<maxIter; ++i)
    {
        if (dabs(x1-x2) < tol)
	{
            mrEvalNum += i;
            return x1;
	}

        tTry = (x1 + x2) / 2.;

        interpolation(tTry, yTry);
        (*mEventFunc)(mDim, &tTry, yTry, &mRootNum, rArray);
     
        if(dabs(rArray[id]) <= deps(0))
	{
            mrEvalNum += i+1;
            return tTry;
	}
 
        if(rArray[id]*y1 >= 0)
	{
            x1 = tTry;
            y1 = rArray[id];
	}
        else
	{
            x2 = tTry;
            y2 = rArray[id];
	}
    }

    std::cout << "Bisection Method executed more than " << maxIter << " times!" << std::endl;
    return tTry;
}

/**
 * Locate roots in terms of Falsi Method
 */
C_FLOAT64 CExpRKMethod::rootFindByFalsi(const size_t id, 
					const C_FLOAT64 leftT, const C_FLOAT64 leftV,
					const C_FLOAT64 rightT, const C_FLOAT64 rightV)
{
    int maxIter = 50;
    C_FLOAT64 tol = deps(dabs(leftT)) * 128;
    C_FLOAT64 *yTry = mZ1, *rArray = mZ2;
    C_FLOAT64 x1 = leftT, y1 = leftV, x2 = rightT, y2 = rightV, tTry, tTry0;

    tTry0 = x1;
    for (int i=0; i<maxIter; ++i)
    {
        tTry = x1 - y1 *(x2-x1)/(y2-y1);
        interpolation(tTry, yTry);
        (*mEventFunc)(mDim, &tTry, yTry, &mRootNum, rArray);

        if ((dabs(tTry-tTry0)<tol) || (dabs(rArray[id])<deps(0)))
	{
            mrEvalNum += i+1;
            return tTry;
	}


        if(rArray[id]*y1 >= 0)
	{
            x1 = tTry;
            y1 = rArray[id];
	}
        else
	{
            x2 = tTry;
            y2 = rArray[id];
	}


        tTry0 = tTry;
    }

    std::cout << "Falsi Method executed more than " << maxIter << " times!" << std::endl;
    return tTry;
}


/**
 * Check whether a slow function fired in this step
 */
void CExpRKMethod::findSlowReaction()
{
    // Check slow reactin existance
    if (mYOld[*mDim-1]*mYNew[*mDim-1]>0)//no slow reaction
        return;

    C_FLOAT64 *tArray = mZ1;
    C_FLOAT64 *yArray = mZ2;
    C_FLOAT64 *yInter = mZ3;
    size_t cnt = 1;

    // Record t and y
    tArray[0] = mTOld;
    yArray[0] = mYOld[*mDim-1];
    for (size_t i=1; i<mStage; i++)
    {
        if (mC[i]>0 && mC[i]<1)
	{
            tArray[cnt] = mTOld + mC[i]*mh;
            interpolation(tArray[cnt], yInter);
            yArray[cnt] = yInter[*mDim-1];
            cnt++;
	}
    }
    tArray[cnt] = mTNew;
    yArray[cnt] = mYNew[*mDim-1];
    cnt++;

    // check whether yArray[i] is close to 0
    SRoot root;

    for(size_t i=0; i<cnt; ++i)
    {
        if(dabs(yArray[i]) < deps(0))
	{
            root.id = -1;
            root.t  = tArray[i];
            queuePush(root);
            return;
	}
    }

    // Do Inverse Interpolation
    C_FLOAT64 t = 0, localT;
    for(size_t i=0; i<cnt; i++)
    {
        localT = 1;
        for(size_t j=0; j<cnt; j++)
	{
            if(i != j)
                localT *= yArray[j] / (yArray[j]-yArray[i]);
	}

        t += localT * tArray[i]; 
    }

    root.id = -1;
    root.t  = t;
    queuePush(root);
    return;
}

/**
 * Interpolation system state at given root
 */
void CExpRKMethod::calculateRootState()
{
    if (queueIsEmpty())
    {
        std::cout << "No root in mRootQueue! Check Code......" << std::endl;
        mODEState = -2;
        return;
    }

    SRoot root = mRootQueue[mQueueSite];
    queuePop();

    mRootId = root.id;
    mT      = root.t;
    interpolation(mT, mY);

    mODEState = 3;
    mODEStateRecord = mODEState;

    //if (mRootId != -1)
    //    (*mEventFunc)(mDim, &mT, mY, &mRootNum, mZ2);

    return;
}



//*****************************//
//* Parameters Check Function *//
//*****************************//

/**
 * Check parameters used in the integration
 */
void CExpRKMethod::checkParameter()
{
    size_t state = mODEState;

    mODEState = -2;

    if(*mDim <= 0) //check dimension
    {
        std::cout << "Dimension of system should be POSITIVE" << std::endl;
        return;
    }

    if((mAbsTol<0) || (mRelTol<0) || (mAbsTol+mRelTol==0))
    {
        std::cout << "Error Tolerances should be nonnegativ and at least one should be positive" << std::endl;
        return;
    }

    if(mTEnd <= mT)
    {
        std::cout << "In this solver, we just support positive integration where stop time should be larger than start time!" << std::endl;
        return;
    }

    if(!mY)
    {
        std::cout << "mY should be set before integration!" << std::endl;
        return;
    }

    if(!mDerivFunc)
    {
        std::cout << "Function that calculates direvatives should be set!" << std::endl;
        return;
    }

    if(mEventFunc && (mRootNum<=0))
    {
        std::cout << "Root Number should be an positive integer!" << std::endl;
        return;
    }

    mODEState = state;
    return;

}


//***************************//
//* Other Helpful Functions *//
//***************************//

/**
 * Calculate infinity norm value
 */
C_FLOAT64 CExpRKMethod::infNorm(const size_t &len, const C_FLOAT64 *y)
{
    C_FLOAT64 result, tmp;
    result =(y[0]>=0)?y[0]:-y[0];

    for(size_t i=1; i<len; i++)
    {
        tmp = (y[i]>=0)?y[i]:-y[i];
        if(tmp>result)
            result = tmp;
    }

    return result;
}

/**
 * Calculate the maxinum element of an array
 */
inline C_FLOAT64 CExpRKMethod::dmax(const C_FLOAT64 &x1, const C_FLOAT64 &x2)
{
    return (x1>x2)?x1:x2;
}

/**
 * Calculate the minimum element of an array
 */
inline C_FLOAT64 CExpRKMethod::dmin(const C_FLOAT64 &x1, const C_FLOAT64 &x2)
{
    return (x1>x2)?x2:x1;
}

/**
 * Calculate absolute value
 */
inline C_FLOAT64 CExpRKMethod::dabs(const C_FLOAT64 &x)
{
    return (x>0)?x:(-1*x);
}

/**
 * Calculate eps of a given value
 */
inline C_FLOAT64 CExpRKMethod::deps(const C_FLOAT64 &x)
{
    return (x==0)? EPS0 : dabs(x)*EPS1;
}

/**
 * Clear queue that records roots
 */
inline void CExpRKMethod::clearQueue()
{
    mQueueLen = 0; mQueueSite = 0;
    return;
}

/**
 * Check whether a queue is empty
 */
inline bool CExpRKMethod::queueIsEmpty()
{
    return (mQueueSite >= mQueueLen);
}

/**
 * Pop the first element in the queue
 */
void CExpRKMethod::queuePop()
{
    if(queueIsEmpty())
    {
        std::cout << "mRootQueue is EMPTY, no elment to pop" << std::endl;
        return;
    }

    ++mQueueSite;
    if(queueIsEmpty() && (mQueueLen>0))
        clearQueue();

    return;
}

/**
 * Push an element into the queue
 */
inline void CExpRKMethod::queuePush(const SRoot &root)
{
    mRootQueue[mQueueLen++] = root;
    return;
}

/**
 * Shrink the queue which just contains only one root for
 * each event
 */
void CExpRKMethod::shrinkQueue()
{
    size_t count = 0;
    int id;

    for(size_t i = 0; i < mRootNum; ++i)
        mZ1[i] = 0;

    for(size_t i = 0; i < mQueueLen; ++i)
    {
        id = mRootQueue[i].id;
        if(id == -1)
            continue;

        if(mZ1[id] == 0)
	{
            mZ1[id] = 1;
            ++count;
	}
        else
	{
            mHasMultipleRoots = true;
            // Set next time and Y pointing to the state at
            // the last root before the first repeated one
            
            double new_time;
            new_time = 0.5*(mRootQueue[i-1].t + mRootQueue[i].t);
            interpolation(new_time, mZ3);

            mTNew = new_time;
            mDerivFunc(mDim, &mTNew, mZ3, mK[0]);

            (*mEventFunc)(mDim, &mTNew, mZ3, &mRootNum, mZ2);
            /*
            for(int i=0; i<mRootNum; i++)
                mRootValueOld[i] = mZ2[i];
            */
            memcpy(mRootValueOld, mZ2, mRootNum*sizeof(C_FLOAT64));


            for (size_t i = 0; i < *mDim; i++)
                mYNew[i] = mZ3[i];
            memcpy(mYNew, mZ3, (*mDim)*sizeof(C_FLOAT64));

            break;
	}

    }

    mQueueLen = count;
}
