// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 *   CHybridMethodODE45
 *
 *   This class implements an hybrid algorithm for the simulation of a
 *   biochemical system over time.
 *
 *   File name: CHybridMethodODE45.cpp
 *   Author: Shuo Wang
 *   Email: shuowang.learner@gmail.com
 *
 *   Last change: 11, Aug 2014
 *
 */

/* DEFINE ********************************************************************/

#ifdef WIN32
#if _MSC_VER < 1600
#define min _cpp_min
#define max _cpp_max
#endif // _MSC_VER
#endif // WIN32

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <new>
#include <cmath>
#include <fstream>

#include "copasi.h"
#include "CTrajectoryProblem.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CReaction.h"
#include "model/CState.h"
#include "model/CChemEq.h"
#include "model/CChemEqElement.h"
#include "model/CCompartment.h"
#include "utilities/CCopasiVector.h"
#include "utilities/CMatrix.h"
#include "utilities/CDependencyGraph.h"
#include "utilities/CIndexedPriorityQueue.h"
#include "utilities/CVersion.h"
#include "randomGenerator/CRandom.h"

#include "CExpRKMethod.h"
#include "CHybridMethodODE45.h"

//================Function for Class================
/**
 * Default constructor.
 */
CHybridMethodODE45::CHybridMethodODE45(const CCopasiContainer * pParent):
    CTrajectoryMethod(CCopasiMethod::hybridODE45, pParent)
{   
    assert((void *) &mData == (void *) &mData.dim);
    mData.pMethod = this;

    mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
    initializeParameter();
}

/**
 * Copy Constructor
 */
CHybridMethodODE45::CHybridMethodODE45(const CHybridMethodODE45 & src,
                                       const CCopasiContainer * pParent):
    CTrajectoryMethod(src, pParent)
{
    assert((void *) &mData == (void *) &mData.dim);
    mData.pMethod = this;

    mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
    initializeParameter();
}

/**
 * Destructor.
 */
CHybridMethodODE45::~CHybridMethodODE45()
{   
    cleanup();
    DESTRUCTOR_TRACE;
}

//================Function for System================

/**
 * This methods must be called to elevate subgroups to
 * derived objects. The default implementation does nothing.
 * @return bool success
 */
bool CHybridMethodODE45::elevateChildren()
{
    initializeParameter();
    return true;
}

/**
 * Check if the method is suitable for this problem
 * @return bool suitability of the method
 */
bool CHybridMethodODE45::isValidProblem(const CCopasiProblem * pProblem)
{
    if (!CTrajectoryMethod::isValidProblem(pProblem)) return false;

    const CTrajectoryProblem * pTP = dynamic_cast<const CTrajectoryProblem *>(pProblem);

    if (pTP->getDuration() < 0.0)
    {
        //back integration not possible
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 9);
        return false;
    }

    if (pTP->getModel()->getTotSteps() < 1)
    {
        //at least one reaction necessary
        CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 17);
        return false;
    }

    if (pTP->getModel()->getReactions().size() <= 0)
    {
        //No Metabolites
        CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 17); // todo next
        return false;
    }

    //events are not supported at the moment
    /*
    if (pTP->getModel()->getEvents().size() > 0)
    {
        CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 23);
        return false;
    }
    */
    return true;
}


/**
 * Intialize the method parameter
 */
void CHybridMethodODE45::initializeParameter()
{   
    CCopasiParameter *pParm;

    assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) MAX_STEPS_ODE);
    assertParameter("Use Random Seed", CCopasiParameter::BOOL, (bool) USE_RANDOM_SEED);
    assertParameter("Random Seed", CCopasiParameter::UINT, (unsigned C_INT32) RANDOM_SEED);

    // Check whether we have a method with the old parameter names
    if ((pParm = getParameter("HYBRID.MaxSteps")) != NULL)
    {
    
        setValue("Max Internal Steps", *pParm->getValue().pUINT);
        removeParameter("HYBRID.MaxSteps");
        
        if ((pParm = getParameter("UseRandomSeed")) != NULL)
        {
            setValue("Use Random Seed", *pParm->getValue().pBOOL);
            removeParameter("UseRandomSeed");
        }

        if ((pParm = getParameter("")) != NULL)
        {
            setValue("Random Seed", *pParm->getValue().pUINT);
            removeParameter("");
        }
    }

    if ((pParm = getParameter("Relative Tolerance")) == NULL)
    {
        addParameter("Relative Tolerance",
                     CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-006);
    }

    if ((pParm = getParameter("Absolute Tolerance")) == NULL)
    {
        addParameter("Absolute Tolerance",
                     CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-009);
    }
}


/**
 * This instructs the method to prepare for integration
 * starting with the initialState given.
 * @param "const CState *" initialState
 */
void CHybridMethodODE45::start(const CState * initialState)
{   
    //set the mpModel
    mpModel = mpProblem->getModel();
    assert(mpModel);

    //set inital state
    mpModel->setState(*initialState);

    //set mpState
    mpState = new CState(*initialState); 

    //set mDoCorrection
    if (mpModel->getModelType() == CModel::deterministic)
        mDoCorrection = true;
    else
        mDoCorrection = false;

    //set mHasAssignments
    mHasAssignments = modelHasAssignments(mpModel);

    // Call initMethod function
    initMethod(mpModel->getTime());

    return;
}


/**
 *  Initializes the solver and sets the model to be used.
 *  @param model A reference to an instance of a CModel
 */
void CHybridMethodODE45::initMethod(C_FLOAT64 start_time)
{ 
    //(1)----set attributes related with REACTIONS
    mpReactions   = &mpModel->getReactions();
    mNumReactions = mpReactions->size();
    
    setupReactionFlags();

    //(2)----set attributes related with METABS
    mpMetabolites = &(const_cast < CCopasiVector < CMetab > & >(mpModel->getMetabolitesX()));

    size_t numReactIndepMetabs = static_cast<size_t>(mpModel->getNumIndependentReactionMetabs());

    mNumReactMetabs = numReactIndepMetabs
        + mpModel->getNumDependentReactionMetabs();

    //one more for sum of propensities
    mData.dim = (size_t)(mpState->getNumIndependent()
                         + mpModel->getNumDependentReactionMetabs() + 1);  

    mReactMetabId = mpState->getNumIndependent() - numReactIndepMetabs;
    setupBalances();    //initialize mLocalBalances

    //set mFirstMetabIndex
    mFirstMetabIndex = mpModel->getStateTemplate().getIndex(mpModel->getMetabolitesX()[0]);

    //(4)----set attributes related with SYSTEM
    mTimeRecord = start_time;
    mMaxSteps   = * getValue("Max Internal Steps").pUINT;
    mRootCounter = 0;
    mMaxStepsReached = false;
    setupMethod(); 
    //=======Check Method Uses Here========
    if(mMethod == STOCHASTIC)
    {
        std::cerr << "At Least One Reaction should be set FAST" << std::endl;
        return; //need error massige here......
    }

    //(5)----set attributes related with STOCHASTIC
    mUseRandomSeed = * getValue("Use Random Seed").pBOOL;
    mRandomSeed    = * getValue("Random Seed").pUINT;

    if (mUseRandomSeed)
        mpRandomGenerator->initialize(mRandomSeed);

    //mStoi = mpModel->getStoiReordered();
    mStoi = mpModel->getStoi();

    //(6)----set attributes for ODE45
    mSysStatus = SYS_NEW;
    mODE45.mODEState = ODE_INIT;
    mODE45.mDim = &mData.dim;

    mODE45.mRelTol = * getValue("Relative Tolerance").pUDOUBLE;
    mODE45.mAbsTol = * getValue("Absolute Tolerance").pUDOUBLE;
    mODE45.mHybrid = true;
    mODE45.mStatis = false;

    // we don't want to directly record new results into mpState, since
    // the sum of slow reaction propensities is also recorded in mY
    mY = new C_FLOAT64[mData.dim];
    mODE45.mY = mY;
    mODE45.mDerivFunc = &CHybridMethodODE45::EvalF;

    //(7)----set attributes for Event Roots
    mRootNum        = mpModel->getNumRoots();
    mODE45.mRootNum = mRootNum;
    mRootMasking    = NONE;

    //================================
    if(mRootNum > 0)
    {
        mRoots.resize(mRootNum);
        for(size_t i=0; i<mRootNum; ++i)
            (mRoots.array())[i] = 0;

        mODE45.mEventFunc = &CHybridMethodODE45::EvalR;
        mpRT        = new C_FLOAT64[mRootNum];
      
        mDiscreteRoots.resize(mRootNum);
        CMathTrigger::CRootFinder *const*ppRootFinder    = mpModel->getRootFinders().array();
        CMathTrigger::CRootFinder *const*ppRootFinderEnd = ppRootFinder + mRootNum;
        bool * pDiscrete = mDiscreteRoots.array();
        for(; ppRootFinder != ppRootFinderEnd; ++ppRootFinder, ++pDiscrete)
            *pDiscrete = (*ppRootFinder)->isDiscrete();      
    }
    else
    {
        mODE45.mEventFunc = NULL;
        mpRT        = NULL;

        mRoots.resize(0);
        mDiscreteRoots.resize(0); 
    }

    mFactor = mpModel->getQuantity2NumberFactor();
    return;
}

/**
 *  Clean up memory, etc.
 */
void CHybridMethodODE45::cleanup()
{
    delete mpRandomGenerator;
    mpRandomGenerator = NULL;
    mpModel = NULL;

    if(mY)
    {
        delete [] mY;
        mY = NULL;
    }

    if (mpState)
    {
        delete mpState;
        mpState = NULL;
    }

    if(mpRT)
    {
        delete [] mpRT;
        mpRT = NULL;
    }

    return;
}

//================Function for Model================

/**
 * Check whether a function is fast or not.
 */
void CHybridMethodODE45::setupReactionFlags()
{
    mHasStoiReaction   = false;
    mHasDetermReaction = false;

    // check for ODE global quantity, compartment and species
    const CStateTemplate & StateTemplate = mpModel->getStateTemplate();
    CModelEntity *const* ppEntity = StateTemplate.beginIndependent();
    CModelEntity *const* ppEntityEnd = StateTemplate.endIndependent();

    for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
        if ((*ppEntity)->getStatus() == CModelEntity::ODE)
        {
            if (dynamic_cast<const CModelValue *>(*ppEntity) != NULL)
            {
                // global quantity ode rule found
                mHasDetermReaction = true;
                break;
            }
            else if (dynamic_cast<const CCompartment *>(*ppEntity) != NULL)
            {
                // compartment ode rule found
                mHasDetermReaction = true;
                break;
            }
            else
            {
                // species ode rule found
                mHasDetermReaction = true;
                break;
            }
        }
    }
    
    // Check reactions 
    mNumSlowReactions = 0;
    for (size_t rct = 0; rct < mNumReactions; rct++)
    { 
        if ((*mpReactions)[rct]->isFast())
            mHasDetermReaction = true;
        else
        {
            mNumSlowReactions++;
            mHasStoiReaction = true;
        }
    }

    // Record slow reactions
    size_t count = 0;
    mAmu.resize(mNumSlowReactions);
    mSlowIndex.resize(mNumSlowReactions);
    mSlowReactionPointer.resize(mNumSlowReactions);
    for (size_t rct = 0; rct < mNumReactions; rct++)
    { 
        if (!((*mpReactions)[rct]->isFast()))
        {
            mSlowReactionPointer[count] = (*mpReactions)[rct];
            mSlowIndex[count++] = rct;
        }
    }

    return;
}

/**
 * Setup mMethod, switching between Deterministic Method and 
 * Hybrid Method
 */
void CHybridMethodODE45::setupMethod()
{
    if (mHasStoiReaction && !mHasDetermReaction)
        mMethod = STOCHASTIC;
    else if(!mHasStoiReaction && mHasDetermReaction)
        mMethod = DETERMINISTIC;
    else
        mMethod = HYBRID;
    return;
}

/**
 * Sets up an internal representation of the balances for each reaction.
 * This is done in order to be able to deal with fixed metabolites and
 * to avoid a time consuming search for the indices of metabolites in the
 * model.
 */
void CHybridMethodODE45::setupBalances()
{
    size_t i, j;
    CHybridODE45Balance newElement;
    size_t maxBalance = 0;

    mLocalBalances.clear();
    mLocalBalances.resize(mNumReactions);

    for (i = 0; i < mNumReactions; i++)
    {
        const CCopasiVector <CChemEqElement> * balances =
            &(*mpReactions)[i]->getChemEq().getBalances();
     
        for (j = 0; j < balances->size(); j++)
        {
            newElement.mpMetabolite = const_cast < CMetab* >((*balances)[j]->getMetabolite());
            newElement.mIndex = mpModel->getMetabolitesX().getIndex(newElement.mpMetabolite);
            newElement.mMultiplicity = (*balances)[j]->getMultiplicity();

            if ((newElement.mpMetabolite->getStatus()) == CModelEntity::REACTIONS)
            {
                if (newElement.mMultiplicity > maxBalance) maxBalance = newElement.mMultiplicity;

                mLocalBalances[i].push_back(newElement); // element is copied for the push_back
            }
        }
        balances = &(*mpReactions)[i]->getChemEq().getSubstrates();
    }

    mMaxBalance = maxBalance;
    return;
}

//========Function for Simulation========
/**
 *  This instructs the method to calculate a time step of deltaT
 *  starting with the current state, i.e., the result of the previous
 *  step.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual timestep taken.
 *  @param "const double &" deltaT
 *  @return Status status
 */
CTrajectoryMethod::Status CHybridMethodODE45::step(const double & deltaT)
{
    // do several steps
    C_FLOAT64 time    = mpState->getTime();
    C_FLOAT64 endTime;

    if (time == mTimeRecord) //new time step
    {
        mTimeRecord  += deltaT;
        mRootCounter  = 0;
    }
    
    endTime = mTimeRecord;
    
    for (size_t i = 0; ((mRootCounter < mMaxSteps) && (time < endTime)); i++)
    {
        time = doSingleStep(endTime);
        
        if (mSysStatus == SYS_EVENT)
	{
            *mpCurrentState = mpModel->getState();
            mRootCounter++;
            return ROOT;
	}
        else if(mSysStatus == SYS_CONT)
            continue;
        else if(mSysStatus == SYS_ERR)
            return FAILURE;
    }
    
    // Warning Message
    if ((mRootCounter >= mMaxSteps) && (!mMaxStepsReached))
    {
        mMaxStepsReached = true; //only report this message once
        CCopasiMessage(CCopasiMessage::WARNING, "maximum number of reaction events was reached in at least one simulation step.\nThat means time intervals in the output may not be what you requested.");
    }

    *mpCurrentState = mpModel->getState(); 
    return NORMAL;
}

/**
 *  Simulates the system over the next interval of time. The new time after
 *  this step is returned.
 *
 *  @param  endTime A C_FLOAT64 specifying the endTime of the current step()
 *  @return A C_FLOAT giving the new time
 */
C_FLOAT64 CHybridMethodODE45::doSingleStep(C_FLOAT64 endTime)
{
    C_FLOAT64 ds     = 0.0;
    size_t    rIndex = 0; 
    
    integrateDeterministicPart(endTime);      
    ds = mODE45.mT;

    //<i> ~~~~ Doing things about mRootMasking
    if(mSysStatus==SYS_EVENT && mHasRoot)
    {
        if(mRootCounter > 0.99*mMaxSteps
           || mODE45.mT == mpCurrentState->getTime()) //oscillation around roots
        { 
            switch(mRootMasking)
            {
	        case NONE:
                case DISCRETE:
                {
                    *mpState  = *mpCurrentState;
                    createRootMask();
                    mSysStatus = SYS_NEW;
                    break;
                }
               case ALL:
               {
                   mSysStatus = SYS_CONT;
                   break;
               }
            }

            mRootCounter = 0;
        }
        else 
        {
            setRoot(mODE45.mRootId);
        }
    }
    else
    { 
        switch(mRootMasking)
	{
            case NONE:
    	    case DISCRETE:
                break;	  
	    case ALL:
            { 
                const bool *pDiscrete = mDiscreteRoots.array();
                bool *pMask = mRootMask.array();
                bool const * const pMaskEnd = pMask + mRootNum;
                bool destroy = true;

                for (; pMask != pMaskEnd; ++pMask, ++pDiscrete)
                {
                    if(*pMask)
                    {
                        if(*pDiscrete)
                            destroy = false;
                        else
                            *pMask = false;
                    }
                }
		
                if(destroy)
                    destroyRootMask();
                else
                    mRootMasking = DISCRETE;
	
                if(mSysStatus != SYS_ERR) //&& (mSysStatus != SYS_EVENT))
                    mSysStatus = SYS_CONT;
            }
	} //end switch
    } //end if

    //<ii> ~~~~ Check mSysStatus
    if((mSysStatus == SYS_EVENT) && mHasSlow) //only deal with system roots
    { 
        fireSlowReaction4Hybrid();
        
        //metab related to slow reactions have been updated,
        //then update ASSIGNMENT values
        mpModel->updateSimulatedValues(false);
        mSysStatus = SYS_NEW;
    }
    else if(mSysStatus == SYS_END)//finish this step
    {
        mSysStatus = SYS_NEW;
    }
    else if(mSysStatus != SYS_CONT && mSysStatus != SYS_EVENT && mSysStatus != SYS_NEW) 
    {
        std::cout << "mSysStatus " << mSysStatus << std::endl;
        std::cout << "mSysStatus Error happens, check the code..." << std::endl;
        mSysStatus = SYS_ERR;
    }

    return ds;
}


/**
 * Function called from TrajectoryMethod which update 
 * system state and inform ODE solver to restart
 * integration.
 */
void CHybridMethodODE45::stateChanged()
{
    *mpState = *mpCurrentState;
    mpModel->setState(*mpState);
    (mRoots.array())[mODE45.mRootId] = 0;
    mSysStatus = SYS_NEW;

    destroyRootMask();
    mRootMasking = NONE;
    return;
}

/**
 * Fire slow reaction and update populations and propensities
 * when Hybrid Method is used
 */
void CHybridMethodODE45::fireSlowReaction4Hybrid()
{
    size_t id;
    calculateAmu();
    
    id = getReactionIndex4Hybrid();
    fireReaction(id); //Directly update current state in global view
    *mpState = mpModel->getState();

    return;
}


//========Function for ODE45========
/**
 * Integrates the deterministic reactions of the system over
 * the specified time interval.
 *
 * @param ds A C_FLOAT64 specifying the stepsize.
 */
void CHybridMethodODE45::integrateDeterministicPart(C_FLOAT64 endTime)
{
    //1----Set Parameters for ODE45 solver
    //=(1)= solver error message
    mErrorMsg.str("");

    //=(2)= set state
    *mpState = mpModel->getState();

    //=(3)= set time and old time
    mODE45.mT    = mpState->getTime();
    mODE45.mTEnd = endTime;
 
    //=(4)= set y and ode status
    if(mSysStatus == SYS_NEW)
    {
        //only when starts a new step, we should copy state into ode solver
        C_FLOAT64 * stateY = mpState->beginIndependent();
        for (size_t i = 0; i < mData.dim - 1; i++)
            mY[i] = stateY[i];
      
        C_FLOAT64 randNum = mpRandomGenerator->getRandomOO();
        mY[mData.dim-1] = log(randNum);

        if(mODE45.mODEState != ODE_INIT)
            mODE45.mODEState = ODE_NEW;
    }
    else if((mSysStatus == SYS_EVENT) || (mSysStatus == SYS_CONT))
    {
        mODE45.mODEState = ODE_CONT;
    }
    else
    {
        std::cout << "Wrong mSysStatus = " << mSysStatus << std::endl;
    }
    
    //3----If time increment is too small, do nothing
    C_FLOAT64 tdist , d__1, d__2, w0;
    tdist = fabs(mODE45.mTEnd-mODE45.mT); //absolute time increment
    d__1  = fabs(mODE45.mT), d__2 = fabs(mODE45.mTEnd);
    w0 = std::max(d__1, d__2);

    if (tdist < std::numeric_limits< C_FLOAT64 >::epsilon() * 2. * w0) //just do nothing
    {
        mODE45.mT  = mODE45.mTEnd;
        mSysStatus = SYS_END;
        mpState->setTime(mODE45.mTEnd);
        mpModel->setState(*mpState);
        std::cout << "delta is too small" << std::endl;
        return;
    }

    //4----just do nothing if there are no variables
    if (!mData.dim)
    {
        mODE45.mT = mODE45.mTEnd;
        mSysStatus = SYS_END;
        mpModel->setTime(mODE45.mTEnd);
        return;
    }
    
    //5----do interpolation
    mODE45.integrate();
    
    //6----check status
    if(mODE45.mODEState == ODE_ERR)
    {
        mSysStatus = SYS_ERR;
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }
    else if(mODE45.mODEState == ODE_EVENT)
    {
        mHasSlow = false;
        mHasRoot = false;
        if(mODE45.mRootId == SLOW_REACT)
            mHasSlow = true;
        else
            mHasRoot = true;

        mSysStatus = SYS_EVENT;
    }
    else
        mSysStatus = SYS_END;

    //7----Record State to Model
    C_FLOAT64 *stateY = mpState->beginIndependent();
    for (size_t i = 0; i < mData.dim-1; i++)
        stateY[i] = mY[i]; //write result into mpState

    mpState->setTime(mODE45.mT);
    mpModel->setState(*mpState);
 
    //Dependent Reaction Metabs have been updated by ODE slover
    mpModel->updateSimulatedValues(false); 
    return;
}

/**
 * Function that sets (mRoot.array())[id]=1
 */
void CHybridMethodODE45::setRoot(const size_t id)
{
    assert(id<mRootNum && id>=0);
    for(size_t i=0; i<mRootNum; i++)
        (mRoots.array())[i] = 0;

    (mRoots.array())[id] = 1;
    return;
}

/**
 * Dummy f function for calculating derivative of y
 */
void CHybridMethodODE45::EvalF(const size_t * n, const C_FLOAT64 * t, const C_FLOAT64 * y, 
			       C_FLOAT64 * ydot)
{static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);}


/**
 * Dummy f function for calculating roots value
 */
void CHybridMethodODE45::EvalR(const size_t * n, const C_FLOAT64 * t, const C_FLOAT64 * y, 
			       const size_t * nr, C_FLOAT64 * r)
{static_cast<Data *>((void *) n)->pMethod->evalR(t, y, nr, r);}


/**
 * Derivative Calculation Function
 */
void CHybridMethodODE45::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
    size_t i;

    //========No need to record State, right?========
    //1====calculate propensities

    //(1)Put current time *t and independent values *y into model.
    // This step seemes necessary, since propensity calculation process
    // requires functions called from the model class.
    mpState->setTime(*t);
    C_FLOAT64 * tmpY = mpState->beginIndependent();//mpState is a local copy

    memcpy(tmpY, y, (mData.dim-1)*sizeof(C_FLOAT64));

    mpModel->setState(*mpState);
    mpModel->updateSimulatedValues(false); //update ASSIGNMENT values in model
  
    //(2) Calculate derivatives
    size_t reactID;
    mpModel->calculateDerivatives(ydot);
    ydot[mData.dim-1] = 0;

    //(3) Deal with slow reactions
    if (mMethod == HYBRID) 
    {
        C_FLOAT64 *pAmu = mAmu.array();
        calculateAmu();
        for (i = 0; i < mNumSlowReactions; i++, pAmu++) 
            ydot[mData.dim-1] += *pAmu;

        // Modify fast reactions
        // update derivatives
        // This part is based on the assumption that number of slow reactions is much less than 
        // fast reactions. If number of slow reactions is dominate, little difference is there
        // compared to previous version.
        std::vector <CHybridODE45Balance>::iterator metabIt;
        std::vector <CHybridODE45Balance>::iterator metabEndIt;
        size_t metabIndex;
        size_t    *pId  = mSlowIndex.array();


        pId  = mSlowIndex.array();
        pAmu = mAmu.array(); 
    
        for (i = 0; i < mNumSlowReactions; i++, pId++, pAmu++)
        {
            reactID    = *pId;
            metabIt    = mLocalBalances[reactID].begin();
            metabEndIt = mLocalBalances[reactID].end();

            for (; metabIt != metabEndIt; metabIt++)
            {
                metabIndex = metabIt->mIndex + mFirstMetabIndex - 1; // mReactMetabId;
                ydot[metabIndex] -= metabIt->mMultiplicity * (*pAmu);
            }
        }
    }
    return;
}

/**
 * Dummy Function for calculating roots value
 */
void CHybridMethodODE45::evalR(const C_FLOAT64 *t, const C_FLOAT64 *y,
			       const size_t *nr, C_FLOAT64 *r)
{
    assert(*nr == (C_INT)mRoots.size());

    mpState->setTime(*t);
    C_FLOAT64 *stateY = mpState->beginIndependent();
    memcpy(stateY, y, (mData.dim-1)*sizeof(C_FLOAT64));
   
    mpModel->setState(*mpState);

    mpModel->updateSimulatedValues(false); //really?  
    CVectorCore< C_FLOAT64 > rootValues(*nr, r);
    mpModel->evaluateRoots(rootValues, true);

    if(mRootMasking != NONE)
        maskRoots(rootValues);
        
    return;
}


//========Function for Stoichastic========
/**
 * Calculates amu values of all slow reactions.
 *
 */
void CHybridMethodODE45::calculateAmu()
{
    C_FLOAT64 *pAmu = mAmu.array();
    CReaction **pRct = mSlowReactionPointer.array();

    for (size_t id = 0; id < mNumSlowReactions; id++, pRct++, pAmu++)
        *pAmu = (*pRct)->calculateParticleFlux();
}


/**
 *   Executes the specified reaction in the system once.
 *
 *   @param rIndex A size_t specifying the index of the reaction, which
 *                 will be fired.
 */
void CHybridMethodODE45::fireReaction(size_t rIndex)
{
    // Change the particle numbers according to which step took place.
    // First, get the vector of balances in the reaction we've got.
    // (This vector expresses the number change of each metabolite
    // in the reaction.) Then step through each balance, using its
    // multiplicity to calculate a new value for the associated
    // metabolite. Finally, update the metabolite.

    size_t i;
    C_FLOAT64 newNumber;
    CMetab    *pMetab;

    for (i = 0; i < mLocalBalances[rIndex].size(); i++)
    {
        pMetab = mLocalBalances[rIndex][i].mpMetabolite;
        newNumber = pMetab->getValue() + mLocalBalances[rIndex][i].mMultiplicity;

        pMetab->setValue(newNumber);
        pMetab->refreshConcentration();
    }

    return;
}

/**
 * Calculate which slow reaction fires
 */
size_t CHybridMethodODE45::getReactionIndex4Hybrid()
{
    //calculate sum of amu
    C_FLOAT64 mAmuSum = 0.0;
    C_FLOAT64 *pAmu   = mAmu.array();
    size_t    *pId;
    for (int i = 0; i < mNumSlowReactions; i++, pAmu++)
            mAmuSum += *pAmu;

    //get the threshold
    C_FLOAT64 rand2 = mpRandomGenerator->getRandomOO();
    C_FLOAT64 threshold = mAmuSum * rand2;

    //get the reaction index
    C_FLOAT64 tmp = 0.0;

    //is there some algorithm that can get a log() complex?
    pAmu = mAmu.array();
    pId  = mSlowIndex.array();
    for (size_t i = 0; i < mNumSlowReactions; i++, pAmu++, pId++)
    {
        tmp += *pAmu;

        if (tmp >= threshold)
            return *pId;
    }
}

//========Root Masking========
void CHybridMethodODE45::maskRoots(CVectorCore<C_FLOAT64 > & rootValues)
{

    const bool *pMask    = mRootMask.array();
    const bool *pMaskEnd = pMask + mRootMask.size();

    C_FLOAT64 *pRoot = rootValues.array();
    for(; pMask!=pMaskEnd; ++pMask, ++pRoot)
    {
        if(*pMask)
            *pRoot = 1.0;
    }

    return;
}


void CHybridMethodODE45::createRootMask()
{
    double absoluteTolerance = 1.e-12;
    mRootMask.resize(mRootNum);
    CVector<C_FLOAT64> rootDerivatives;
    rootDerivatives.resize(mRootNum);

    mpModel->setState(*mpState);
    mpModel->calculateRootDerivatives(rootDerivatives);

    bool *pMask    = mRootMask.array();
    bool *pMaskEnd = pMask + mRootMask.size();

    C_FLOAT64 *pRootDerivative = rootDerivatives.array();
    for(; pMask!=pMaskEnd; ++pMask, ++pRootDerivative)
        *pMask = (fabs(*pRootDerivative) < absoluteTolerance) ? true : false;

    mRootMasking = ALL;
    return;
}

void CHybridMethodODE45::destroyRootMask()
{
    mRootMask.resize(0);
    mRootMasking = NONE;
}


//========Help Function========
/**
 * Test the model if it is proper to perform stochastic simulations on.
 * Several properties are tested (e.g. integer stoichometry, all reactions
 * take place in one compartment only, irreversibility...).
 *
 * @return 0, if everything is ok; <0, if an error occured.
 */
C_INT32 CHybridMethodODE45::checkModel(CModel * model)
{
    CCopasiVectorNS <CReaction> * mpReactions = &model->getReactions();
    //CMatrix <C_FLOAT64> mStoi = model->getStoiReordered();
    CMatrix <C_FLOAT64> mStoi = model->getStoi();
    C_INT32 multInt;
    size_t i, j, numReactions = mpReactions->size();
    C_FLOAT64 multFloat;
    //  size_t metabSize = mpMetabolites->size();

    for (i = 0; i < numReactions; i++) // for every reaction
    {
        // TEST getCompartmentNumber() == 1
        if ((*mpReactions)[i]->getCompartmentNumber() != 1) return - 1;

        // TEST isReversible() == 0
        if ((*mpReactions)[i]->isReversible() != 0) return - 2;

        // TEST integer stoichometry
        // Iterate through each the metabolites
        // juergen: the number of rows of mStoi equals the number of non-fixed metabs!

        for (j = 0; j < mStoi.numRows(); j++)
        {
            multFloat = mStoi[j][i];
            multInt = static_cast<C_INT32>(floor(multFloat + 0.5)); // +0.5 to get a rounding out of the static_cast to int!

            if ((multFloat - multInt) > INT_EPSILON) return - 3; // INT_EPSILON in CHybridMethod.h
        }
    }

    return 1; // Model is appropriate for hybrid simulation
}


/**
 *   Prints out data on standard output. Deprecated.
 */
void CHybridMethodODE45::outputData()
{
    std::cout << "============Boolean============" << std::endl;

    if (mDoCorrection)
        std::cout << "mDoCorrection: Yes" << std::endl;
    else
        std::cout << "mDoCorrection: No" << std::endl;


    std::cout << std::endl;

    std::cout << "============Metab============" << std::endl;

    std::cout << "~~~~mNumReactMetabs:~~~~ " << mNumReactMetabs << std::endl;

    std::cout << "============Reaction============" << std::endl;

    std::cout << "~~~~mNumReactions:~~~~ " << mNumReactions << std::endl;
    //for (size_t i=0; i<mNumReactions; ++i)
    //{
    //    std::cout << "Reaction #: " << i << " Flag: " << mReactionFlags[i] << std::endl;
    //}
    std::cout << "~~~~mLocalBalances:~~~~ " << std::endl;
    for (size_t i=0; i<mLocalBalances.size(); ++i)
    {
        std::cout << "Reaction: " << i << std::endl;

        for (size_t j = 0; j < mLocalBalances[i].size(); ++j)
        {
            std::cout << "Index: " << mLocalBalances[i][j].mIndex << std::endl;
            std::cout << "mMultiplicity: " << mLocalBalances[i][j].mMultiplicity << std::endl;
            std::cout << "mpMetablite: " << mLocalBalances[i][j].mpMetabolite << std::endl;
        }
    }

    if (mHasStoiReaction)
        std::cout << "mHasStoiReaction: Yes" << std::endl;
    else
        std::cout << "mHasStoiReaction: No" << std::endl;

    if (mHasDetermReaction)
        std::cout << "mHasDetermReaction: Yes" << std::endl;
    else
        std::cout << "mHasDetermReaction: No" << std::endl;

    getchar();
    return;
}

/**
 * Print State Data for Debug
 */
void CHybridMethodODE45::outputState(const CState* mpState)
{
    std::cout << "NumMetabs     " << mpModel->getNumMetabs() << std::endl;
    std::cout << "NumODEMetabs  " << mpModel->getNumODEMetabs() << std::endl;
    std::cout << "NumIndpMetabs " << mpModel->getNumIndependentReactionMetabs() << std::endl;
    std::cout << "NumDepnMetabs " << mpModel->getNumDependentReactionMetabs() << std::endl;
    std::cout << "NumAgnMetabs  " << mpModel->getNumAssignmentMetabs() << std::endl;
  
    C_FLOAT64 factor = mpModel->getQuantity2NumberFactor();
    size_t count = -1;

    count++;
    const C_FLOAT64 time = mpState->getTime();
    std::cout << "**State Output**" << std::endl;
    std::cout << "Time: " << time << std::endl;

    std::cout << "Indep #: " << mpState->getNumIndependent() << " Id: ";
    std::cout << std::endl;
    const C_FLOAT64 *pIt = mpState->beginIndependent();
    const C_FLOAT64 *pEnd = mpState->endIndependent();
    for (; pIt != pEnd; pIt++)
    {
        count++;
        if((count >= mFirstMetabIndex) && (count < mReactMetabId+1 + mNumReactMetabs))
            std::cout << "R " << (*pIt) / factor << " ";
        else
            std::cout << *pIt << " ";
    }
    std::cout << std::endl;

    std::cout << "Dep #: " << mpState->getNumDependent() << " Id: ";
    std::cout << std::endl;
    pIt = mpState->beginDependent();
    pEnd = mpState->endDependent();
    for (; pIt != pEnd; pIt++)
    {
        count++;
        if((count >= mFirstMetabIndex) && (count < mReactMetabId+1 + mNumReactMetabs))
            std::cout << "R " << (*pIt) / factor << " ";
        else
            std::cout << *pIt << " ";
    }
    std::cout << std::endl;

    std::cout << "Fix #: " << mpState->getNumIndependent() << " Id: ";
    std::cout << std::endl;
    pIt = mpState->beginFixed();
    pEnd = mpState->endFixed();
    for (; pIt != pEnd; pIt++)
        std::cout << *pIt << " ";
    std::cout << std::endl;

    getchar();
    return;
}

bool CHybridMethodODE45::modelHasAssignments(const CModel* pModel)
{
    size_t i, imax = pModel->getNumModelValues();

    for (i = 0; i < imax; ++i)
    {
        if (pModel->getModelValues()[i]->getStatus() == CModelEntity::ASSIGNMENT)
            if (pModel->getModelValues()[i]->isUsed())
            {
                //used assignment found
                return true;
            }
    }

    imax = pModel->getNumMetabs();

    for (i = 0; i < imax; ++i)
    {
        if (pModel->getMetabolites()[i]->getStatus() == CModelEntity::ASSIGNMENT)
            if (pModel->getMetabolites()[i]->isUsed())
            {
                //used assignment found
                return true;
            }
    }

    imax = pModel->getCompartments().size();

    for (i = 0; i < imax; ++i)
    {
        if (pModel->getCompartments()[i]->getStatus() == CModelEntity::ASSIGNMENT)
            if (pModel->getCompartments()[i]->isUsed())
            {
                //used assignment found
                return true;
            }
    }
    return false;
}

/**
 * Print out system state given in array y
 */
void CHybridMethodODE45::outputY(C_FLOAT64 *y)
{
    std::cout << "y " << std::endl;
    for(size_t i=0; i<=mData.dim-1; i++)
    {
        if(i>=mFirstMetabIndex-1 && i<(mReactMetabId+mNumReactMetabs))
            std::cout << y[i] / mFactor << " ";
        else
            std::cout << y[i] << " ";
    }
    std::cout << std::endl;
    getchar();
    return;
}
