/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CHybridMethodLSODA.cpp,v $
   $Revision: 1.4.2.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/19 14:19:39 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *   CHybridMethodLSODA
 *
 *   This class implements an hybrid algorithm for the simulation of a
 *   biochemical system over time.
 *
 *   File name: CHybridMethodLSODA.cpp
 *   Author: Juergen Pahle
 *   Email: juergen.pahle@eml-r.villa-bosch.de
 *
 *   Last change: 09, May 2006
 *
 *   (C) European Media Lab 2003.
 */

/* DEFINE ********************************************************************/

#ifdef WIN32
#define min _cpp_min
#define max _cpp_max
#endif // WIN32

#include "mathematics.h" // pow(), floor()

#include "copasi.h"

#include "CHybridMethodLSODA.h"
#include "CTrajectoryProblem.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CReaction.h"
#include "model/CState.h"
#include "model/CChemEq.h"
#include "model/CChemEqElement.h"
#include "model/CCompartment.h"
#include "utilities/CVersion.h"
#include "utilities/CCopasiVector.h"
#include "utilities/CMatrix.h"
#include "utilities/CDependencyGraph.h"
#include "utilities/CIndexedPriorityQueue.h"
#include "randomGenerator/CRandom.h"

/**
 *   Default constructor.
 */
CHybridMethodLSODA::CHybridMethodLSODA(const CCopasiContainer * pParent):
    CTrajectoryMethod(CCopasiMethod::hybridLSODA, pParent)
{
  /* Set version number */
  mVersion.setVersion(1, 0, 102, "");
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
  initializeParameter();
}

CHybridMethodLSODA::CHybridMethodLSODA(const CHybridMethodLSODA & src,
                                       const CCopasiContainer * pParent):
    CTrajectoryMethod(src, pParent)
{
  /* Set version number */
  mVersion.setVersion(1, 0, 102, "");
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
  initializeParameter();
}

/**
 *   Destructor.
 */
CHybridMethodLSODA::~CHybridMethodLSODA()
{
  cleanup();
  DESTRUCTOR_TRACE;
}

void CHybridMethodLSODA::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) MAX_STEPS);
  assertParameter("Lower Limit", CCopasiParameter::DOUBLE, (C_FLOAT64) LOWER_STOCH_LIMIT);
  assertParameter("Upper Limit", CCopasiParameter::DOUBLE, (C_FLOAT64) UPPER_STOCH_LIMIT);

  assertParameter("Partitioning Interval", CCopasiParameter::UINT, (unsigned C_INT32) PARTITIONING_INTERVAL);
  assertParameter("Use Random Seed", CCopasiParameter::BOOL, (bool) USE_RANDOM_SEED);
  assertParameter("Random Seed", CCopasiParameter::UINT, (unsigned C_INT32) RANDOM_SEED);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("HYBRID.MaxSteps")) != NULL)
    {
      setValue("Max Internal Steps", *pParm->getValue().pUINT);
      removeParameter("HYBRID.MaxSteps");

      if ((pParm = getParameter("HYBRID.LowerStochLimit")) != NULL)
        {
          setValue("Lower Limit", *pParm->getValue().pDOUBLE);
          removeParameter("HYBRID.LowerStochLimit");
        }

      if ((pParm = getParameter("HYBRID.UpperStochLimit")) != NULL)
        {
          setValue("Upper Limit", *pParm->getValue().pDOUBLE);
          removeParameter("HYBRID.UpperStochLimit");
        }

      if ((pParm = getParameter("HYBRID.PartitioningInterval")) != NULL)
        {
          setValue("Partitioning Interval", *pParm->getValue().pUINT);
          removeParameter("HYBRID.PartitioningInterval");
        }

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

  /* LSODA ****************************************************************************/

  mDim[1] = (C_INT) (void *) this;

  addParameter("Partitioning Stepsize",
               CCopasiParameter::DOUBLE, (C_FLOAT64) PARTITIONING_STEPSIZE);

  addParameter("Relative Tolerance",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-006);

  addParameter("Use Default Absolute Tolerance",
               CCopasiParameter::BOOL, (bool) true);

  addParameter("Absolute Tolerance",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e009);

  addParameter("Adams Max Order",
               CCopasiParameter::UINT, (unsigned C_INT32) 12);

  addParameter("BDF Max Order",
               CCopasiParameter::UINT, (unsigned C_INT32) 5);

  addParameter("Max Internal Steps (LSODA)",
               CCopasiParameter::UINT, (unsigned C_INT32) 10000);
}

bool CHybridMethodLSODA::elevateChildren()
{
  initializeParameter();
  return true;
}

/**
 *   Creates a HybridMethodLSODA adequate for the problem.
 */
CHybridMethodLSODA *CHybridMethodLSODA::createHybridMethodLSODA(CTrajectoryProblem * C_UNUSED(pProblem))
{
  C_INT32 result = 1;
  CHybridMethodLSODA * method = NULL;

  switch (result)
    {
      /*    case - 3:        // non-integer stoichometry
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 1);
      break;
      case - 2:        // reversible reaction exists
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 2);
      break;

      case - 1:        // more than one compartment involved
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 3);
      break;*/
    case 1:
    default:
      // Everything alright: Hybrid simulation possible
      method = new CHybridNextReactionLSODAMethod();
      break;
    }
  return method;
}

void CHybridMethodLSODA::step(const double & deltaT)
{
  //outputDebug(std::cout, 0);
  // write the current state to the model
  //  mpProblem->getModel()->setState(mpCurrentState); // is that correct?

  // check for possible overflows
  unsigned C_INT32 i;
  unsigned C_INT32 imax;

  for (i = 0, imax = mpProblem->getModel()->getNumVariableMetabs(); i < imax; i++)
    if (mpProblem->getModel()->getMetabolitesX()[i]->getValue() >= mMaxIntBeforeStep)
      {
        // throw exception or something like that
      }

  // do several steps
  C_FLOAT64 time = mpProblem->getModel()->getTime();
  C_FLOAT64 endTime = time + deltaT;

  for (i = 0; ((i < mMaxSteps) && (time < endTime)); i++)
    {
      time = doSingleStep(time, endTime);
    }
  //mpCurrentState->setTime(time);

  // get back the particle numbers

  /* Set the variable metabolites */
  C_FLOAT64 * Dbl = mpCurrentState->beginIndependent();
  for (i = 0, imax = mpProblem->getModel()->getNumVariableMetabs(); i < imax; i++, Dbl++)
    *Dbl = mpProblem->getModel()->getMetabolitesX()[i]->getValue();

  //the task expects the result in mpCurrentState
  *mpCurrentState = mpProblem->getModel()->getState();

  mpCurrentState->setTime(time); //NATALIA

  return;
}

void CHybridMethodLSODA::start(const CState * initialState)
{
  //*mpCurrentState = *initialState;

  mpProblem->getModel()->setState(*initialState);
  mRestartLSODA = true;

  mpState = new CState (mpProblem->getModel()->getState());

  mpModel = mpProblem->getModel();
  assert(mpModel);

  if (mpModel->getModelType() == CModel::deterministic)
    mDoCorrection = true;
  else
    mDoCorrection = false;

  //mpProblem->getModel()->setState(*mpCurrentState);

  // call init of the simulation method, can be overloaded in derived classes
  // mDim[1] = (C_INT) (void *) this;
  initMethod(mpProblem->getModel()->getTime());

  return;
}

/* PROTECTED METHODS *********************************************************/

/**
 *  Initializes the solver and sets the model to be used.
 *
 *  @param model A reference to an instance of a CModel
 */
void CHybridMethodLSODA::initMethod(C_FLOAT64 start_time)
{
  mpReactions = &mpModel->getReactions();
  mAmu.clear();
  mAmu.resize(mpReactions->size());
  mAmuOld.clear();
  mAmuOld.resize(mpReactions->size());
  mpMetabolites = &(const_cast < CCopasiVector < CMetab > & > (mpModel->getMetabolitesX()));
  mNumVariableMetabs = mpModel->getNumVariableMetabs(); // ind + dep metabs, without fixed metabs

  temp.clear();
  temp.resize(mNumVariableMetabs);
  //currentState.clear();
  //currentState.resize(mNumVariableMetabs);

  /* get configuration data */
  mMaxSteps = * getValue("Max Internal Steps").pUINT;
  //std::cout << "HYBRID.MaxSteps: " << mMaxSteps << std::endl;
  mLowerStochLimit = * getValue("Lower Limit").pDOUBLE;
  //std::cout << "HYBRID.LowerStochLimit: " << mLowerStochLimit << std::endl;
  mUpperStochLimit = * getValue("Upper Limit").pDOUBLE;
  //std::cout << "HYBRID.UpperStochLimit: " << mUpperStochLimit << std::endl;
  mStepsize = * getValue("Partitioning Stepsize").pDOUBLE;
  //std::cout << "HYBRID.Partitioning Stepsize: " << mStepsize << std::endl;
  mPartitioningInterval = * getValue("Partitioning Interval").pUINT;
  //std::cout << "HYBRID.PartitioningInterval: " << mPartitioningInterval << std::endl;
  mUseRandomSeed = * getValue("Use Random Seed").pBOOL;
  //std::cout << "HYBRID.UseRandomSeed: " << mUseRandomSeed << std::endl;
  mRandomSeed = * getValue("Random Seed").pUINT;
  //std::cout << "HYBRID.RandomSeed: " << mRandomSeed << std::endl;
  if (mUseRandomSeed) mpRandomGenerator->initialize(mRandomSeed);
  mStoi = mpModel->getStoiReordered();
  mStepsAfterPartitionSystem = 0;
  mUpdateSet.clear();

  setupBalances(); // initialize mLocalBalances and mLocalSubstrates (has to be called first!)
  setupDependencyGraph(); // initialize mDG
  setupMetab2React(); // initialize mMetab2React
  setupPartition(); // initialize mReactionFlags
  setupPriorityQueue(start_time); // initialize mPQ

  //deprecated:  mOutputFileName = string(DEFAULT_OUTPUT_FILE);
  //deprecated:  mOutputFile.open(DEFAULT_OUTPUT_FILE); // DEFAULT_OUTPUT_FILE in CHybridMethod.h
  //deprecated:  mOutputCounter = OUTPUT_COUNTER; // OUTPUT_COUNTER in CHybridMethod.h

  //deprecated:  outputDebug(std::cout, 0); // DEBUG

  /* CONFIGURE LSODA ***********************************************************************/

  mDim[0] = mNumVariableMetabs;

  mYdot.resize(mDim[0]);

  mRtol = * getValue("Relative Tolerance").pUDOUBLE;

  mDefaultAtol = * getValue("Use Default Absolute Tolerance").pBOOL;

  if (mDefaultAtol)
    {
      mAtol = getDefaultAtol(mpProblem->getModel());
      setValue("Absolute Tolerance", mAtol);
    }
  else
    mAtol = * getValue("Absolute Tolerance").pUDOUBLE;

  mDWork.resize(22 + mDim[0] * std::max<C_INT>(16, mDim[0] + 9));
  mDWork[4] = mDWork[5] = mDWork[6] = mDWork[7] = mDWork[8] = mDWork[9] = 0.0;
  mIWork.resize(20 + mDim[0]);

  mIWork[4] = mIWork[6] = mIWork[9] = 0;
  mIWork[5] = * getValue("Max Internal Steps (LSODA)").pUINT;
  mIWork[7] = * getValue("Adams Max Order").pUINT;
  mIWork[8] = * getValue("BDF Max Order").pUINT;

  /***********************************************************************************/

  return;
}

C_FLOAT64 CHybridMethodLSODA::getDefaultAtol(const CModel * pModel) const
  {

    if (!pModel) return 1.0e009;

    const CCopasiVectorNS< CCompartment > & Compartment = pModel->getCompartments();
    unsigned C_INT32 i, imax;

    C_FLOAT64 Volume = DBL_MAX;

    for (i = 0, imax = Compartment.size(); i < imax; i++)
      if (Compartment[i]->getValue() < Volume) Volume = Compartment[i]->getValue();

    if (Volume == DBL_MAX) return 1.0e009;

    return Volume * pModel->getQuantity2NumberFactor() * 1.e-12;
  }

/**
 *  Cleans up memory, etc.
 */
void CHybridMethodLSODA::cleanup()
{
  delete mpRandomGenerator;
  mpRandomGenerator = NULL;
  mpModel = NULL;
  return;
}

/* DETERMINISTIC STUFF *******************************************************/

void CHybridMethodLSODA::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<CHybridMethodLSODA *>((void *) n[1])->evalF(t, y, ydot);}

void CHybridMethodLSODA::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  unsigned C_INT32 i;
  assert (y == mY);

  CModel * pModel = mpProblem->getModel();

  mpState->setTime(*t);

  pModel->setState(*mpState);

  pModel->applyAssignments();

  calculateDerivative(temp);

  for (i = 0; i < mNumVariableMetabs; i++)
    ydot[i] = temp[i];

  return;
}

/**
 *   Integrates the deterministic reactions of the system over the specified
 *   time interval.
 *
 *   @param ds A C_FLOAT64 specifying the stepsize.
 */

void CHybridMethodLSODA::integrateDeterministicPart(C_FLOAT64 deltaT)
{
  CHybridLSODAStochFlag * react = NULL;

  /* RESET LSODA **************************************************************/

  if (mRestartLSODA)
    {
      mRestartLSODA = false;
      mLsodaStatus = 1;
    }
  mState = 1;
  mJType = 2;

  mErrorMsg.str("");
  mLSODA.setOstream(mErrorMsg);

  C_INT one = 1;
  C_INT DSize = mDWork.size();
  C_INT ISize = mIWork.size();

  //mpState = new CState (mpProblem->getModel()->getState());
  *mpState = mpProblem->getModel()->getState();
  mY = mpState->beginIndependent();
  mTime = mpState->getTime();

  C_FLOAT64 EndTime = mTime + deltaT;

  //std::cout << "integrateDeterministicPart: " << std::endl;

  //std::cout << "mTime: " << mTime
  // << " EndTime: " << EndTime << " deltaT: " << deltaT  << std::endl; // DEBUG : last NATALIA

  C_FLOAT64 tdist , d__1, d__2, w0;
  tdist = fabs(deltaT);
  d__1 = fabs(mTime), d__2 = fabs(EndTime);
  w0 = std::max(d__1, d__2);
  if (tdist < DBL_EPSILON * 2. * w0) //just do nothing
    {
      //mTime = mTime + deltaT;
      //mpState->setTime(mTime);
      //*mpCurrentState = *mpState;
      mpProblem->getModel()->setTime(EndTime);

      return;
    }

  if (!mDim[0]) //just do nothing if there are no variables
    {
      //mTime = mTime + deltaT;
      mpProblem->getModel()->setTime(EndTime);
      //mpState->setTime(mTime);
      //*mpCurrentState = *mpState;

      return;
    }

  mLSODA(&EvalF ,          //  1. evaluate F
         mDim ,            //  2. number of variables
         mY ,             //  3. the array of current concentrations
         &mTime ,          //  4. the current time
         &EndTime ,        //  5. the final time
         &one ,            //  6. scalar error control
         &mRtol ,          //  7. relative tolerance array
         &mAtol ,          //  8. absolute tolerance array
         &mState ,         //  9. output by overshoot & interpolatation
         &mLsodaStatus ,   // 10. the state control variable
         &one ,            // 11. futher options (one)
         mDWork.array() ,  // 12. the double work array
         &DSize ,          // 13. the double work array size
         mIWork.array() ,  // 14. the int work array
         &ISize ,          // 15. the int work array size
         NULL ,            // 16. evaluate J (not given)
         &mJType);        // 17. the type of jacobian calculate (2)

  if (mLsodaStatus == -1) mLsodaStatus = 2;

  if ((mLsodaStatus != 1) && (mLsodaStatus != 2) && (mLsodaStatus != -1))
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }

  mpState->setTime(mTime);
  //*mpCurrentState = *mpState;
  mpProblem->getModel()->setState(*mpState);

  //pdelete(mpState);

  // find the set union of all reactions, which depend on one of the deterministic reactions. The propensities of the stochastic reactions in this set union will be updated later in the method updatePriorityQueue().

  for (react = mFirstReactionFlag; react != NULL; react = react->mpNext)
    {
      const std::set <C_INT32> & dependents = mDG.getDependents(react->mIndex);
      std::copy(dependents.begin(), dependents.end(),
                std::inserter(mUpdateSet, mUpdateSet.begin()));
    }
  return;
}

/**
 *   Calculates the derivative of the system and writes it into the vector
 *   deriv. Length of deriv must be mNumVariableMetabs.
 *   CAUTION: Only deterministic reactions are taken into account. That is,
 *   this is only the derivative of the deterministic part of the system.
 *
 *   @param deriv A vector reference of length mNumVariableMetabs, into
 *                which the derivative is written
 */
void CHybridMethodLSODA::calculateDerivative(std::vector <C_FLOAT64> & deriv)
{
  unsigned C_INT32 i;
  C_INT32 bal = 0;
  CHybridLSODAStochFlag * j;

  // Calculate all the needed kinetic functions of the deterministic reactions
  for (j = mFirstReactionFlag; j != NULL; j = j->mpNext)
    {
      (*mpReactions)[j->mIndex]->calculateParticleFlux();
    }

  // For each metabolite add up the contributions of the det. reactions
  // the number of rows in mStoi equals the number of non-fixed metabolites!
  //  for (i=0; i<mNumVariableMetabs; i++)
  for (i = 0; i < (unsigned C_INT32) mStoi.numRows(); i++)
    {
      deriv[i] = 0.0;
      for (j = mFirstReactionFlag; j != NULL; j = j->mpNext)
        {
          // juergen: +0.5 to get a rounding out of the static_cast
          bal = static_cast<C_INT32>(floor(mStoi[i][j->mIndex] + 0.5));
          deriv[i] += bal * (*mpReactions)[j->mIndex]->getParticleFlux(); //  balance * flux;
        }
    }
  /*
    for (; i < mNumVariableMetabs; i++) deriv[i] = 0.0; // important to get a correct deriv vector, because mStoi doesn't cover fixed metabolites
  */
  return;
}

/* STOCHASTIC STUFF **********************************************************/

/**
 *   Find the reaction index and the reaction time of the stochastic (!)
 *   reaction with the lowest reaction time.
 *
 *   @param ds A reference to a C_FLOAT64. The putative reaction time for the
 *             first stochastic reaction is written into this variable.
 *   @param rIndex A reference to a C_INT32. The index of the first
 *                 stochastic reaction is written into this variable.
 */
void CHybridMethodLSODA::getStochTimeAndIndex(C_FLOAT64 & ds, C_INT32 & rIndex)
{
  ds = mPQ.topKey();
  rIndex = mPQ.topIndex();
  return;
}

/**
 *   Executes the specified reaction in the system once.
 *
 *   @param rIndex A C_INT32 specifying the index of the reaction, which
 *                 will be fired.
 *   @param time   The current time
 */
void CHybridMethodLSODA::fireReaction(C_INT32 rIndex)
{
  // Change the particle numbers according to which step took place.
  // First, get the vector of balances in the reaction we've got.
  // (This vector expresses the number change of each metabolite
  // in the reaction.) Then step through each balance, using its
  // multiplicity to calculate a new value for the associated
  // metabolite. Finally, update the metabolite.

  unsigned C_INT32 i;
  C_FLOAT64 number, newNumber;

  for (i = 0; i < mLocalBalances[rIndex].size(); i++)
    {
      number = mLocalBalances[rIndex][i].mpMetabolite->getValue();
      newNumber = number + mLocalBalances[rIndex][i].mMultiplicity;
      mLocalBalances[rIndex][i].mpMetabolite->setValue(newNumber);
    }

  // insert all dependent reactions into the mUpdateSet
  const std::set <C_INT32> & dependents = mDG.getDependents(rIndex);
  std::copy(dependents.begin(), dependents.end(),
            std::inserter(mUpdateSet, mUpdateSet.begin()));

  mRestartLSODA = true;

  return;
}

/**
 *   Updates the priority queue.
 *
 *   @param rIndex A C_INT32 giving the index of the fired reaction (-1, if no
 *                 stochastic reaction has fired)
 *   @param time A C_FLOAT64 holding the current time
 */
void CHybridMethodLSODA::updatePriorityQueue(C_INT32 rIndex, C_FLOAT64 time)
{
  C_FLOAT64 newTime;
  C_INT32 index;
  std::set <C_INT32>::iterator iter, iterEnd;

  // iterate through the set of affected reactions and update the stochastic ones in the priority queue
  for (iter = mUpdateSet.begin(), iterEnd = mUpdateSet.end(); iter != iterEnd; iter++)
    {
      if (mReactionFlags[*iter].mpPrev == NULL) // reaction is stochastic!
        {
          index = *iter;
          mAmuOld[index] = mAmu[index];
          calculateAmu(index);
          if (*iter != rIndex) updateTauMu(index, time);
        }
    }

  // draw new random number and update the reaction just fired
  if ((rIndex != -1) && (mReactionFlags[rIndex].mpPrev == NULL))
    {// reaction is stochastic
      newTime = time + generateReactionTime(rIndex);
      mPQ.updateNode(rIndex, newTime);
    }

  // empty the mUpdateSet
  mUpdateSet.clear();
  return;
}

C_FLOAT64 CHybridMethodLSODA::generateReactionTime(C_INT32 rIndex)
{
  C_FLOAT64 rand2 = mpRandomGenerator->getRandomOO();
  return - 1 * log(rand2) / mAmu[rIndex];
}

/**
 *   Calculates an amu value for a given reaction.
 *
 *   @param rIndex A C_INT32 specifying the reaction to be updated
 */
void CHybridMethodLSODA::calculateAmu(C_INT32 rIndex)
{
  if (!mDoCorrection)
    {
      mAmu[rIndex] = (*mpReactions)[rIndex]->calculateParticleFlux();
      return;
    }

  // We need the product of the cmu and hmu for this step.
  // We calculate this in one go, as there are fewer steps to
  // perform and we eliminate some possible rounding errors.
  C_FLOAT64 amu = 1; // initially
  //C_INT32 total_substrates = 0;
  C_INT32 num_ident = 0;
  C_INT32 number = 0;
  C_INT32 lower_bound;
  // substrate_factor - The substrates, raised to their multiplicities,
  // multiplied with one another. If there are, e.g. m substrates of type m,
  // and n of type N, then substrate_factor = M^m * N^n.
  C_FLOAT64 substrate_factor = 1;
  // First, find the reaction associated with this index.
  // Keep a pointer to this.
  // Iterate through each substrate in the reaction
  const std::vector<CHybridLSODABalance> & substrates = mLocalSubstrates[rIndex];

  int flag = 0;

  for (unsigned C_INT32 i = 0; i < substrates.size(); i++)
    {
      num_ident = substrates[i].mMultiplicity;
      //std::cout << "Num ident = " << num_ident << std::endl;
      //total_substrates += num_ident;

      if (num_ident > 1)
        {
          flag = 1;
          number = static_cast<C_INT32>((*mpMetabolites)[substrates[i].mIndex]->getValue());
          lower_bound = number - num_ident;
          //std::cout << "Number = " << number << "  Lower bound = " << lower_bound << std::endl;
          substrate_factor = substrate_factor * pow((double) number, (int) num_ident - 1); //optimization
          //std::cout << "Substrate factor = " << substrate_factor << std::endl;

          number--; // optimization
          while (number > lower_bound)
            {
              amu *= number;
              number--;
            }
        }
    }

  if ((amu == 0) || (substrate_factor == 0))  // at least one substrate particle number is zero
    {
      mAmu[rIndex] = 0;
      return;
    }

  // rate_factor is the rate function divided by substrate_factor.
  // It would be more efficient if this was generated directly, since in effect we
  // are multiplying and then dividing by the same thing (substrate_factor)!
  C_FLOAT64 rate_factor = (*mpReactions)[rIndex]->calculateParticleFlux();

  if (flag)
    {
      //std::cout << "Rate factor = " << rate_factor << std::endl;
      amu *= rate_factor / substrate_factor;;
      mAmu[rIndex] = amu;
    }
  else
    {
      mAmu[rIndex] = rate_factor;
    }

  //std::cout << "Index = " << rIndex << "  Amu = " << amu << std::endl;
  return;

  // a more efficient way to calculate mass action kinetics could be included
}

/**
 *   Updates the putative reaction time of a stochastic reaction in the
 *   priority queue. The corresponding amu and amu_old must be set prior to
 *   the call of this method.
 *
 *   @param rIndex A C_INT32 specifying the index of the reaction
 */
void CHybridMethodLSODA::updateTauMu(C_INT32 rIndex, C_FLOAT64 time)
{
  C_FLOAT64 newTime;

  // One must make sure that the calculation yields reasonable results even in the cases where mAmu=0 or mAmuOld=0 or both =0. Therefore mAmuOld=0 is checked. If mAmuOld equals 0, then a new random number has to be drawn, because tau equals inf and the stoch. information is lost. If both values equal 0, then tau should remain inf and the update of the queue can be skipped!

  if (mAmuOld[rIndex] == 0.0)
    {
      if (mAmu[rIndex] != 0.0)
        {
          newTime = time + generateReactionTime(rIndex);
          mPQ.updateNode(rIndex, newTime);
        }
    }
  else
    {
      newTime = time + (mAmuOld[rIndex] / mAmu[rIndex]) * (mPQ.getKey(rIndex) - time);
      mPQ.updateNode(rIndex, newTime);
    }
  return;
}

/* TESTING THE MODEL AND SETTING UP THINGS ***********************************/

/**
 *   Test the model if it is proper to perform stochastic simulations on.
 *   Several properties are tested (e.g. integer stoichometry, all reactions
 *   take place in one compartment only, irreversibility...).
 *
 *   @return 0, if everything is ok; <0, if an error occured.
 */
C_INT32 CHybridMethodLSODA::checkModel(CModel * model)
{
  CCopasiVectorNS <CReaction> * mpReactions = &model->getReactions();
  CMatrix <C_FLOAT64> mStoi = model->getStoiReordered();
  C_INT32 i, multInt, numReactions = mpReactions->size();
  unsigned C_INT32 j;
  C_FLOAT64 multFloat;
  //  C_INT32 metabSize = mpMetabolites->size();

  for (i = 0; i < numReactions; i++) // for every reaction
    {
      // TEST getCompartmentNumber() == 1
      if ((*mpReactions)[i]->getCompartmentNumber() != 1) return - 1;

      // TEST isReversible() == 0
      if ((*mpReactions)[i]->isReversible() != 0) return - 2;

      // TEST integer stoichometry
      // Iterate through each the metabolites
      // juergen: the number of rows of mStoi equals the number of non-fixed metabs!
      //  for (j=0; i<metabSize; j++)
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
 *   Sets up an internal representation of the balances for each reaction.
 *   This is done in order to be able to deal with fixed metabolites and
 *   to avoid a time consuming search for the indices of metabolites in the
 *   model.
 */
void CHybridMethodLSODA::setupBalances()
{
  unsigned C_INT32 i, j;
  CHybridLSODABalance newElement;
  C_INT32 maxBalance = 0;
  unsigned C_INT32 numReactions;

  numReactions = mpReactions->size();
  mLocalBalances.clear();
  mLocalBalances.resize(numReactions);
  mLocalSubstrates.clear();
  mLocalSubstrates.resize(numReactions);

  for (i = 0; i < numReactions; i++)
    {
      const CCopasiVector <CChemEqElement> * balances =
        &(*mpReactions)[i]->getChemEq().getBalances();
      for (j = 0; j < balances->size(); j++)
        {
          newElement.mpMetabolite = const_cast < CMetab* > ((*balances)[j]->getMetabolite());
          newElement.mIndex = mpModel->getMetabolitesX().getIndex(newElement.mpMetabolite);
          // + 0.5 to get a rounding out of the static_cast to C_INT32!
          newElement.mMultiplicity = static_cast<C_INT32>(floor((*balances)[j]->getMultiplicity() + 0.5));
          if ((newElement.mpMetabolite->getStatus()) != CModelEntity::FIXED)
            {
              if (newElement.mMultiplicity > maxBalance) maxBalance = newElement.mMultiplicity;
              mLocalBalances[i].push_back(newElement); // element is copied for the push_back
            }
        }

      balances = &(*mpReactions)[i]->getChemEq().getSubstrates();
      for (j = 0; j < balances->size(); j++)
        {
          newElement.mpMetabolite = const_cast < CMetab* > ((*balances)[j]->getMetabolite());
          newElement.mIndex = mpModel->getMetabolitesX().getIndex(newElement.mpMetabolite);
          // + 0.5 to get a rounding out of the static_cast to C_INT32!
          newElement.mMultiplicity = static_cast<C_INT32>(floor((*balances)[j]->getMultiplicity() + 0.5));

          mLocalSubstrates[i].push_back(newElement); // element is copied for the push_back
        }
    }

  mMaxBalance = maxBalance; //std::cout << "mMaxBalance: " << mMaxBalance << std::endl;
  //mMaxIntBeforeStep= numeric_limits<C_INT32>::max() - mMaxSteps*mMaxBalance;
  mMaxIntBeforeStep = INT_MAX - 1 - mMaxSteps * mMaxBalance;

  return;
}

/**
 *   Sets up the dependency graph.
 */
void CHybridMethodLSODA::setupDependencyGraph()
{
  mDG.clear();
  std::vector< std::set<std::string>* > DependsOn;
  std::vector< std::set<std::string>* > Affects;
  unsigned C_INT32 numReactions = mpReactions->size();
  unsigned C_INT32 i, j;

  // Do for each reaction:
  for (i = 0; i < numReactions; i++)
    {
      // Get the set of metabolites  which affect the value of amu for this
      // reaction i.e. the set on which amu depends. This may be  more than
      // the set of substrates, since the kinetics can involve other
      // reactants, e.g. catalysts. We thus need to step through the
      // rate function and pick out every reactant which can vary.
      DependsOn.push_back(getDependsOn(i));
      // Get the set of metabolites which are affected when this reaction takes place
      Affects.push_back(getAffects(i));
    }

  // For each possible pair of reactions i and j, if the intersection of
  // Affects(i) with DependsOn(j) is non-empty, add a dependency edge from i to j.
  for (i = 0; i < numReactions; i++)
    {
      for (j = 0; j < numReactions; j++)
        {
          // Determine whether the intersection of these two sets is non-empty
          // Could also do this with set_intersection generic algorithm, but that
          // would require operator<() to be defined on the set elements.

          std::set<std::string>::iterator iter = Affects[i]->begin();
          for (; iter != Affects[i]->end(); iter++)
            {
              if (DependsOn[j]->count(*iter))
                {
                  // The set intersection is non-empty
                  mDG.addDependent(i, j);
                  break;
                }
            }
        }
      // Ensure that self edges are included
      //mDG.addDependent(i, i);
    }

  // Delete the memory allocated in getDependsOn() and getAffects()
  // since this is allocated in other functions.
  for (i = 0; i < numReactions; i++)
    {
      delete DependsOn[i];
      delete Affects[i];
    }
  return;
}

/**
 *   Creates for each metabolite a set of reaction indices. If the metabolite
 *   participates in a reaction as substrate or product (that means:
 *   balance != 0) this reaction is added to the corresponding set.
 */
void CHybridMethodLSODA::setupMetab2React()
{
  unsigned C_INT32 i, j;
  C_INT32 metaboliteIndex;

  // Resize mMetab2React and create an initial set for each metabolite
  mMetab2React.clear();
  mMetab2React.resize(mpMetabolites->size());

  // Iterate over all reactions
  for (i = 0; i < mLocalBalances.size(); i++)
    {
      // Get the set of metabolites which take part in this reaction
      for (j = 0; j < mLocalBalances[i].size(); j++)
        {
          // find metaboliteIndex and insert the reaction into the set
          metaboliteIndex = mLocalBalances[i][j].mIndex;
          mMetab2React[metaboliteIndex].insert(i);
        }
    }
  return;
}

/**
 *   Creates for each metabolite a set of reaction indices. If the metabolite
 *   participates in a reaction as substrate, product or modifier this
 *   reaction is added to the corresponding set.
 */
void CHybridMethodLSODA::setupMetab2ReactPlusModifier()
{
  std::vector< std::set<C_INT32>* > participatesIn;
  unsigned C_INT32 numReactions = mpReactions->size();
  unsigned C_INT32 i;

  // Resize mMetab2React and create an initial set for each metabolite
  mMetab2React.resize(mpMetabolites->size());

  // Do for each reaction:
  for (i = 0; i < numReactions; i++)
    {
      participatesIn.push_back(getParticipatesIn(i));
    }

  // Iterate over all reactions
  for (i = 0; i < numReactions; i++)
    {
      // Get the set of metabolites which take part in this reaction
      std::set<C_INT32>::iterator iter = participatesIn[i]->begin();
      for (; iter != participatesIn[i]->end(); iter++)
        mMetab2React[*iter].insert(i);
    }

  for (i = 0; i < numReactions; i++)
    {
      delete participatesIn[i];
    }
  return;
}

/**
 *   Creates for each metabolite a set of reaction indices. Each reaction is
 *   dependent on each metabolite resulting in a complete switch.
 */
void CHybridMethodLSODA::setupMetab2ReactComplete()
{
  unsigned C_INT32 i, j;

  // Resize mMetab2React and create an initial set for each metabolite
  mMetab2React.resize(mpMetabolites->size());

  // Iterate over all metabolites
  for (i = 0; i < mpMetabolites->size(); i++)
    {
      // Iterate over all reactions
      for (j = 0; j < mpReactions->size(); j++)
        {
          mMetab2React[i].insert(j);
        }
    }
  return;
}

/**
 *   Creates an initial partitioning of the system. Deterministic and
 *   stochastic reactions are determined. The vector mReactionFlags and
 *   the vector mMetabFlags are initialized.
 */
void CHybridMethodLSODA::setupPartition()
{
  unsigned C_INT32 i, j;
  CHybridLSODAStochFlag * prevFlag;
  C_FLOAT64 averageStochLimit = (mUpperStochLimit + mLowerStochLimit) / 2;

  // initialize vector mMetabFlags
  mMetabFlags.clear();
  mMetabFlags.resize(mNumVariableMetabs);
  for (i = 0; i < mMetabFlags.size(); i++)
    {
      if ((*mpMetabolites)[i]->getValue() < averageStochLimit)
        {
          mMetabFlags[i] = LOW;
          (*mpMetabolites)[i]->setValue(floor((*mpMetabolites)[i]->getValue()));
        }
      else
        mMetabFlags[i] = HIGH;
    }

  // initialize vector mReactionFlags
  mReactionFlags.clear();
  mReactionFlags.resize(mLocalBalances.size());
  for (i = 0; i < mLocalBalances.size(); i++)
    {
      mReactionFlags[i].mIndex = i;
      mReactionFlags[i].mValue = 0;
      for (j = 0; j < mLocalBalances[i].size(); j++)
        {
          if (mMetabFlags[mLocalBalances[i][j].mIndex] == LOW)
            {
              mReactionFlags[i].mValue++;
            }
        }
    }
  mFirstReactionFlag = NULL;
  prevFlag = NULL;
  for (i = 0; i < mLocalBalances.size(); i++)
    {
      if (mReactionFlags[i].mValue == 0)
        {
          if (mFirstReactionFlag != NULL)
            {
              prevFlag->mpNext = &mReactionFlags[i];
              mReactionFlags[i].mpPrev = prevFlag;
              prevFlag = &mReactionFlags[i];
            }
          else
            {
              mFirstReactionFlag = &mReactionFlags[i];
              mReactionFlags[i].mpPrev = &mReactionFlags[i]; // Important to distinguish between stochastic (prev == NULL) and deterministic (prev != NULL) reactions
              prevFlag = &mReactionFlags[i];
            }
        }
      else
        {
          mReactionFlags[i].mpPrev = NULL;
          mReactionFlags[i].mpNext = NULL;
        }
    }
  if (prevFlag != NULL)
    {
      prevFlag->mpNext = NULL;
    }
  //outputDebug(std::cout, 0);
  return;
}

/**
 *   Sets up the priority queue.
 *
 *   @param startTime The time at which the simulation starts.
 */
void CHybridMethodLSODA::setupPriorityQueue(C_FLOAT64 startTime)
{
  unsigned C_INT32 i;
  C_FLOAT64 time;

  mPQ.clear();
  mPQ.initializeIndexPointer(mpReactions->size());

  for (i = 0; i < mpReactions->size(); i++)
    {
      if (mReactionFlags[i].mpPrev == NULL) // Reaction is stochastic!
        {
          calculateAmu(i);
          time = startTime + generateReactionTime(i);
          mPQ.insertStochReaction(i, time);
          //std::cout << "time: " << mpCurrentState->getTime() << " rIndex: "
          //<< i << "      ->stoch" << std::endl; // DEBUG
        }
    }
  return;
}

/* HELPER METHODS ************************************************************/

/**
 *   Updates the partitioning of the system depending on the particle
 *   numbers present.
 */
void CHybridMethodLSODA::partitionSystem()
{
  unsigned C_INT32 i;
  std::set <C_INT32>::iterator iter, iterEnd;
  C_FLOAT64 key;

  for (i = 0; i < mNumVariableMetabs; i++)
    {
      if ((mMetabFlags[i] == LOW) && ((*mpMetabolites)[i]->getValue() >= mUpperStochLimit))
        {
          mRestartLSODA = true;
          mMetabFlags[i] = HIGH;
          // go through all corresponding reactions and update flags
          for (iter = mMetab2React[i].begin(), iterEnd = mMetab2React[i].end(); iter != iterEnd; iter++)
            {
              mReactionFlags[*iter].mValue--;
              // if reaction gets deterministic, insert it into the linked list of deterministic reactions
              if (mReactionFlags[*iter].mValue == 0)
                {
                  insertDeterministicReaction(*iter);
                  mPQ.removeStochReaction(*iter);
                  //std::cout << "time: " << mpCurrentState->getTime() << " rIndex: " << *iter
                  //<< " stoch->" << std::endl; // DEBUG
                }
            }
        }
      if ((mMetabFlags[i] == HIGH) && ((*mpMetabolites)[i]->getValue() < mLowerStochLimit))
        {
          mRestartLSODA = true;
          mMetabFlags[i] = LOW;
          (*mpMetabolites)[i]->setValue(floor((*mpMetabolites)[i]->getValue()));
          // go through all corresponding reactions and update flags
          for (iter = mMetab2React[i].begin(), iterEnd = mMetab2React[i].end(); iter != iterEnd; iter++)
            {
              if (mReactionFlags[*iter].mValue == 0)
                {
                  removeDeterministicReaction(*iter);
                  /*
                    mPQ.insertStochReaction(*iter, 1234567.8);  // juergen: have to beautify this, number has to be the biggest C_FLOAT64 !!!
                  */
                  calculateAmu(*iter);
                  mAmuOld[*iter] = mAmu[*iter];
                  //key = mpCurrentState->getTime() + generateReactionTime(*iter); NATALIA

                  key = mpProblem->getModel()->getTime() + generateReactionTime(*iter);

                  mPQ.insertStochReaction(*iter, key);
                  //std::cout << "time: " << mpCurrentState->getTime() << " rIndex: " << *iter
                  //<< "      ->stoch" << std::endl; // DEBUG
                }
              mReactionFlags[*iter].mValue++;
            }
        }
    }
  return;
}

/**
 *   Inserts a new deterministic reaction into the linked list in the
 *   array mReactionFlags.
 *
 *   @param rIndex A C_INT32 giving the index of the reaction to be inserted
 *                 into the list of deterministic reactions.
 */
void CHybridMethodLSODA::insertDeterministicReaction(C_INT32 rIndex)
{
  if (mReactionFlags[rIndex].mpPrev == NULL)
    // reaction is stochastic (avoids double insertions)
    {
      if (mFirstReactionFlag != NULL)
        // there are deterministic reactions already
        {
          mFirstReactionFlag->mpPrev = &mReactionFlags[rIndex];
          mReactionFlags[rIndex].mpNext = mFirstReactionFlag;
          mFirstReactionFlag = &mReactionFlags[rIndex];
          mFirstReactionFlag->mpPrev = mFirstReactionFlag;
        }
      else
        {
          // there are no deterministic reactions
          // Important to distinguish between stochastic (prev == NULL) and deterministic (prev != NULL) reactions
          mReactionFlags[rIndex].mpPrev = &mReactionFlags[rIndex];
          mFirstReactionFlag = &mReactionFlags[rIndex];
        }
      mAmu[rIndex] = 0.0;
      mAmuOld[rIndex] = 0.0;
    }
  return;
}

/**
 *   Removes a deterministic reaction from the linked list in the
 *   array mReactionFlags.
 *
 *   @param rIndex A C_INT32 giving the index of the reaction to be removed
 *                 from the list of deterministic reactions.
 */
void CHybridMethodLSODA::removeDeterministicReaction(C_INT32 rIndex)
{
  if (mReactionFlags[rIndex].mpPrev != NULL)
    // reaction is deterministic
    {
      if (&mReactionFlags[rIndex] != mFirstReactionFlag)
        // reactionFlag is not the first in the linked list
        {
          mReactionFlags[rIndex].mpPrev->mpNext = mReactionFlags[rIndex].mpNext;
          if (mReactionFlags[rIndex].mpNext != NULL)
            mReactionFlags[rIndex].mpNext->mpPrev = mReactionFlags[rIndex].mpPrev;
        }
      else
        // reactionFlag is the first in the linked list
        {
          if (mReactionFlags[rIndex].mpNext != NULL) // reactionFlag is not the only one in the linked list
            {
              mFirstReactionFlag = mReactionFlags[rIndex].mpNext;
              mFirstReactionFlag->mpPrev = mFirstReactionFlag;
            }
          else // reactionFlag is the only one in the linked list
            {
              mFirstReactionFlag = NULL;
            }
        }
    }
  mReactionFlags[rIndex].mpPrev = NULL;
  mReactionFlags[rIndex].mpNext = NULL;
  return;
}

/**
 *   Gets the set of metabolites on which a given reaction depends.
 *
 *   @param rIndex The index of the reaction being executed.
 *   @return The set of metabolites depended on.
 */
std::set<std::string> *CHybridMethodLSODA::getDependsOn(C_INT32 rIndex)
{
  std::set<std::string> *retset = new std::set<std::string>;

  unsigned C_INT32 i, imax = (*mpReactions)[rIndex]->getFunctionParameters().size();
  unsigned C_INT32 j, jmax;

  //std::vector <const CMetab*> metablist;
  //std::cout << rIndex << " depends on ";

  for (i = 0; i < imax; ++i)
    {
      if ((*mpReactions)[rIndex]->getFunctionParameters()[i]->getUsage() == CFunctionParameter::PARAMETER)
        continue;
      //metablist = (*mpReactions)[rIndex]->getParameterMappingMetab(i);
      const std::vector <std::string> & metabKeylist =
        (*mpReactions)[rIndex]->getParameterMappings()[i];
      jmax = metabKeylist.size();
      for (j = 0; j < jmax; ++j)
        {
          retset->insert(metabKeylist[j]);
          //std::cout << " " << metablist[j]->getObjectName() << ":" << metablist[j]->getKey();
        }
    }
  //std::cout << std::endl;
  return retset;
}

/**
 *   Gets the set of metabolites which change number when a given
 *   reaction is executed.
 *
 *   @param rIndex The index of the reaction being executed.
 *   @return The set of affected metabolites.
 */
std::set<std::string> *CHybridMethodLSODA::getAffects(C_INT32 rIndex)
{
  unsigned C_INT32 i;
  std::set<std::string> *retset = new std::set<std::string>;

  // Get the balances  associated with the reaction at this index
  // XXX We first get the chemical equation, then the balances, since the getBalances method in CReaction is unimplemented!

  //std::cout << rIndex << " affects ";
  for (i = 0; i < mLocalBalances[rIndex].size(); i++)
    {
      if (mLocalBalances[rIndex][i].mMultiplicity != 0)
        {
          retset->insert(mLocalBalances[rIndex][i].mpMetabolite->getKey());
          //std::cout << " " << mLocalBalances[rIndex][i].mpMetabolite->getObjectName() << ":" << mLocalBalances[rIndex][i].mpMetabolite->getKey();
        }
    }
  //std::cout << std::endl;
  return retset;
}

/**
 *   Gets the set of metabolites, which participate in the given
 *   reaction either as substrate, product or modifier.
 *
 *   @param rIndex The index of the reaction being executed.
 *   @return The set of participating metabolites.
 */
std::set<C_INT32> *CHybridMethodLSODA::getParticipatesIn(C_INT32 rIndex)
{
  std::set<C_INT32> *retset = new std::set<C_INT32>;
  /*
  CCopasiVector<CReaction::CId2Metab> & subst = (*mpReactions)[rIndex]->getId2Substrates();

  CCopasiVector<CReaction::CId2Metab> & prod = (*mpReactions)[rIndex]->getId2Products();

  CCopasiVector<CReaction::CId2Metab> & modif = (*mpReactions)[rIndex]->getId2Modifiers();

  unsigned C_INT32 i;

  for (i = 0; i < subst.size(); i++)
    {
      retset->insert(findMetab(subst[i]->getMetabolite()));
    }

  for (i = 0; i < prod.size(); i++)
    {
      retset->insert(findMetab(prod[i]->getMetabolite()));
    }
  for (i = 0; i < modif.size(); i++)
    {
      retset->insert(findMetab(modif[i]->getMetabolite()));
    }
  */ //TODO reac
  std::cout << "getParticipatesIn(" << rIndex << ") is broken!" << std::endl;
  return retset;
}

/**
 *   Prints out data on standard output. Deprecated.
 */
void CHybridMethodLSODA::outputData(std::ostream & os, C_INT32 mode)
{
  static C_INT32 counter = 0;
  unsigned C_INT32 i;

  switch (mode)
    {
    case 0:
      if (mOutputCounter == (counter++))
        {
          counter = 0;
          os << mpCurrentState->getTime() << " : ";
          for (i = 0; i < mpMetabolites->size(); i++)
            {
              os << (*mpMetabolites)[i]->getValue() << " ";
            }
          os << std::endl;
        }
      break;
    case 1:
      os << mpCurrentState->getTime() << " : ";
      for (i = 0; i < mpMetabolites->size(); i++)
        {
          os << (*mpMetabolites)[i]->getValue() << " ";
        }
      os << std::endl;
      break;
    default:
;
    }
  return;
}

/**
 *   Prints out various data on standard output for debugging purposes.
 */
void CHybridMethodLSODA::outputDebug(std::ostream & os, C_INT32 level)
{
  unsigned C_INT32 i, j;
  std::set <C_INT32>::iterator iter, iterEnd;

  os << "outputDebug(" << level << ") *********************************************** BEGIN" << std::endl;

  switch (level)
    {
    case 0:                              // Everything !!!
      os << "Version: " << mVersion.getVersion() << " Name: "
      << CCopasiParameter::getObjectName() << std::endl;
      os << "current time: " << mpCurrentState->getTime() << std::endl;
      os << "mNumVariableMetabs: " << mNumVariableMetabs << std::endl;
      os << "mMaxSteps: " << mMaxSteps << std::endl;
      os << "mMaxBalance: " << mMaxBalance << std::endl;
      os << "mMaxIntBeforeStep: " << mMaxIntBeforeStep << std::endl;
      os << "mpReactions.size(): " << mpReactions->size() << std::endl;
      for (i = 0; i < mpReactions->size(); i++)
        os << *(*mpReactions)[i] << std::endl;
      os << "mpMetabolites.size(): " << mpMetabolites->size() << std::endl;
      for (i = 0; i < mpMetabolites->size(); i++)
        os << *(*mpMetabolites)[i] << std::endl;
      os << "mStoi: " << std::endl;
      for (i = 0; i < (unsigned C_INT32) mStoi.numRows(); i++)
        {
          for (j = 0; j < (unsigned C_INT32) mStoi.numCols(); j++)
            os << mStoi[i][j] << " ";
          os << std::endl;
        }
      os << "temp: ";
      for (i = 0; i < mNumVariableMetabs; i++)
        os << temp[i] << " ";
      os << std::endl;

      os << "mReactionFlags: " << std::endl;
      for (i = 0; i < mLocalBalances.size(); i++)
        os << mReactionFlags[i];
      os << "mFirstReactionFlag: " << std::endl;
      if (mFirstReactionFlag == NULL) os << "NULL" << std::endl; else os << *mFirstReactionFlag;
      os << "mMetabFlags: " << std::endl;
      for (i = 0; i < mMetabFlags.size(); i++)
        {
          if (mMetabFlags[i] == LOW)
            os << "LOW ";
          else
            os << "HIGH ";
        }
      os << std::endl;
      os << "mLocalBalances: " << std::endl;
      for (i = 0; i < mLocalBalances.size(); i++)
        {
          for (j = 0; j < mLocalBalances[i].size(); j++)
            os << mLocalBalances[i][j];
          os << std::endl;
        }
      os << "mLocalSubstrates: " << std::endl;
      for (i = 0; i < mLocalSubstrates.size(); i++)
        {
          for (j = 0; j < mLocalSubstrates[i].size(); j++)
            os << mLocalSubstrates[i][j];
          os << std::endl;
        }
      os << "mLowerStochLimit: " << mLowerStochLimit << std::endl;
      os << "mUpperStochLimit: " << mUpperStochLimit << std::endl;
      //deprecated:      os << "mOutputCounter: " << mOutputCounter << endl;
      os << "mPartitioningInterval: " << mPartitioningInterval << std::endl;
      os << "mStepsAfterPartitionSystem: " << mStepsAfterPartitionSystem << std::endl;
      os << "mStepsize: " << mStepsize << std::endl;
      os << "mMetab2React: " << std::endl;
      for (i = 0; i < mMetab2React.size(); i++)
        {
          os << i << ": ";
          for (iter = mMetab2React[i].begin(), iterEnd = mMetab2React[i].end(); iter != iterEnd; ++iter)
            os << *iter << " ";
          os << std::endl;
        }
      os << "mAmu: " << std::endl;
      for (i = 0; i < mpReactions->size(); i++)
        os << mAmu[i] << " ";
      os << std::endl;
      os << "mAmuOld: " << std::endl;
      for (i = 0; i < mpReactions->size(); i++)
        os << mAmuOld[i] << " ";
      os << std::endl;
      os << "mUpdateSet: " << std::endl;
      for (iter = mUpdateSet.begin(), iterEnd = mUpdateSet.end(); iter != iterEnd; iter++)
        os << *iter;
      os << std::endl;
      os << "mpRandomGenerator: " << mpRandomGenerator << std::endl;
      os << "mDG: " << std::endl << mDG;
      os << "mPQ: " << std::endl << mPQ;
      os << "Particle numbers: " << std::endl;
      for (i = 0; i < mpMetabolites->size(); i++)
        {
          os << (*mpMetabolites)[i]->getValue() << " ";
        }
      os << std::endl;
      break;

    case 1:                               // Variable values only
      os << "current time: " << mpCurrentState->getTime() << std::endl;
      /*
      case 1:
      os << "mTime: " << mpCurrentState->getTime() << std::endl;
      os << "oldState: ";
      for (i = 0; i < mDim; i++)
        os << oldState[i] << " ";
      os << std::endl;
      os << "x: ";
      for (i = 0; i < mDim; i++)
        os << x[i] << " ";
      os << std::endl;
      os << "y: ";
      for (i = 0; i < mDim; i++)
        os << y[i] << " ";
      os << std::endl;
      os << "increment: ";
      for (i = 0; i < mDim; i++)
        os << increment[i] << " ";
      os << std::endl;*/
      os << "temp: ";
      for (i = 0; i < mNumVariableMetabs; i++)
        os << temp[i] << " ";
      os << std::endl;

      os << "mReactionFlags: " << std::endl;
      for (i = 0; i < mLocalBalances.size(); i++)
        os << mReactionFlags[i];
      os << "mFirstReactionFlag: " << std::endl;
      if (mFirstReactionFlag == NULL) os << "NULL" << std::endl; else os << *mFirstReactionFlag;
      os << "mMetabFlags: " << std::endl;
      for (i = 0; i < mMetabFlags.size(); i++)
        {
          if (mMetabFlags[i] == LOW)
            os << "LOW ";
          else
            os << "HIGH ";
        }
      os << std::endl;
      os << "mAmu: " << std::endl;
      for (i = 0; i < mpReactions->size(); i++)
        os << mAmu[i] << " ";
      os << std::endl;
      os << "mAmuOld: " << std::endl;
      for (i = 0; i < mpReactions->size(); i++)
        os << mAmuOld[i] << " ";
      os << std::endl;
      os << "mUpdateSet: " << std::endl;
      for (iter = mUpdateSet.begin(), iterEnd = mUpdateSet.end(); iter != iterEnd; iter++)
        os << *iter;
      os << std::endl;
      os << "mPQ: " << std::endl << mPQ;
      os << "Particle numbers: " << std::endl;
      for (i = 0; i < mpMetabolites->size(); i++)
        {
          os << (*mpMetabolites)[i]->getValue() << " ";
        }
      os << std::endl;
      break;

    case 2:
      break;

    default:
;
    }
  os << "outputDebug(" << level << ") ************************************************* END" << std::endl;
  return;
}

std::ostream & operator<<(std::ostream & os, const CHybridLSODAStochFlag & d)
{
  os << "CHybridLSODAStochFlag " << std::endl;
  os << "  mIndex: " << d.mIndex << " mValue: " << d.mValue << std::endl;
  if (d.mpPrev != NULL)
    os << "  prevIndex: " << d.mpPrev->mIndex << " prevPointer: " << d.mpPrev << std::endl;
  else
    os << "  prevPointer: NULL" << std::endl;
  if (d.mpNext != NULL)
    os << "  nextIndex: " << d.mpNext->mIndex << " nextPointer: " << d.mpNext << std::endl;
  else
    os << "  nextPointer: NULL" << std::endl;
  return os;
}

std::ostream & operator<<(std::ostream & os, const CHybridLSODABalance & d)
{
  os << "CHybridLSODABalance" << std::endl;
  os << "  mIndex: " << d.mIndex << " mMultiplicity: " << d.mMultiplicity
  << " mpMetabolite: " << d.mpMetabolite << std::endl;
  return os;
}

//virtual
bool CHybridMethodLSODA::isValidProblem(const CCopasiProblem * pProblem)
{
  //TODO: rewrite CModel::suitableForStochasticSimulation() to use
  //      CCopasiMessage
  if (!pProblem)
    {
      //no problem
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 7);
      return false;
    }

  const CTrajectoryProblem * pTP = dynamic_cast<const CTrajectoryProblem *>(pProblem);
  if (!pTP)
    {
      //not a TrajectoryProblem
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 8);
      return false;
    }

  if (pTP->getDuration() < 0.0)
    {
      //back integration not possible
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 9);
      return false;
    }

  std::string message = pTP->getModel()->suitableForStochasticSimulation();
  if (message != "")
    {
      //model not suitable, message describes the problem
      CCopasiMessage(CCopasiMessage::EXCEPTION, message.c_str());
      return false;
    }

  mLowerStochLimit = * getValue("Lower Limit").pDOUBLE;
  mUpperStochLimit = * getValue("Upper Limit").pDOUBLE;
  if (mLowerStochLimit > mUpperStochLimit)
    CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 4, mLowerStochLimit, mUpperStochLimit);

  return true;
}
