/**
 *   CHybridMethod
 *
 *   This class implements an hybrid algorithm for the simulation of a
 *   biochemical system over time.
 *
 *   File name: CHybridMethod.cpp
 *   Author: Juergen Pahle
 *   Email: juergen.pahle@eml.villa-bosch.de
 *
 *   Last change: 24, Februar 2003
 *
 *   (C) European Media Lab 2003.
 */

/* DEFINE ********************************************************************/
#define  COPASI_TRACE_CONSTRUCTION

#ifdef WIN32
#define min _cpp_min
#define max _cpp_max
#endif // WIN32

/* HEADER FILE ***************************************************************/
#include "CHybridMethod.h"

/* INCLUDES ******************************************************************/
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
#include "math.h" // pow(), floor()
#include "randomGenerator/CRandom.h"

/* PUBLIC METHODS ************************************************************/

/**
 *   Destructor.
 */
CHybridMethod::~CHybridMethod()
{
  std::cout << "~CHybridMethod() " << getName() << std::endl;
  delete mRandomGenerator;
  mRandomGenerator = 0;
  cleanup();
}

/**
 *
 */
CHybridMethod *CHybridMethod::createHybridMethod(CTrajectoryProblem * pProblem)
{
  C_INT32 result = 1; // hybrid NextReactionRungeKutta method as default
  if (pProblem && pProblem->getModel())
    {
      result = checkModel(pProblem->getModel());
    }
  CHybridMethod * method = NULL;

  switch (result)
    {
    case - 3:      // non-integer stoichometry
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 1);
      break;
    case - 2:      // reversible reaction exists
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 2);
      break;
    case - 1:      // more than one compartment involved
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 3);
      break;
      // Error: Hybrid simulation impossible
      break;
    case 1:
    default:
      method = new CHybridNextReactionRKMethod();
      break;
    }
  return method;
}

const double CHybridMethod::step(const double & deltaT)
{
  // write the current state to the model
  mpProblem->getModel()->setState(mpCurrentState);

  // check for possible overflows
  unsigned C_INT32 i;
  unsigned C_INT32 imax;

  for (i = 0, imax = mpProblem->getModel()->getIntMetab(); i < imax; i++)
    if (mpProblem->getModel()->getMetabolites()[i]->getNumberInt() >= mMaxIntBeforeStep)
      {
        // throw exception or something like that
      }

  // do several steps
  C_FLOAT64 time = mpCurrentState->getTime();
  C_FLOAT64 endTime = time + deltaT;

  for (i = 0; ((i < mMaxSteps) && (time < endTime)); i++)
    {
      time = doSingleStep(time, endTime);
    }
  mpCurrentState->setTime(time);

  // get back the particle numbers

  /* Set the variable metabolites */
  C_FLOAT64 * Dbl = const_cast<C_FLOAT64 *>(mpCurrentState->getVariableNumberVectorDbl().array());
  for (i = 0, imax = mpProblem->getModel()->getIntMetab(); i < imax; i++, Dbl++)
    *Dbl = mpProblem->getModel()->getMetabolites()[i]->getNumberDbl();

#ifndef  COPASI_DEPRECATED
  C_INT32 * Int = const_cast<C_INT32 *>(mpCurrentState->getVariableNumberVectorInt().array());
  for (i = 0, imax = mpProblem->getModel()->getIntMetab(); i < imax; i++, Int++)
    *Int = mpProblem->getModel()->getMetabolites()[i]->getNumberInt();
#endif // COPASI_DEPRECATED

  return deltaT;
}

const double CHybridMethod::step(const double & deltaT,
                                 const CState * initialState)
{
  *mpCurrentState = *initialState;

  mpModel = mpProblem->getModel();
  mpProblem->getModel()->setState(mpCurrentState);

  // call init of the simulation method, can be overloaded in derived classes
  initMethod(mpCurrentState->getTime());

  return step(deltaT);
}

/* PROTECTED METHODS *********************************************************/

/**
 *   Default constructor.
 */
CHybridMethod::CHybridMethod():
    CTrajectoryMethod()
{
  setName("HYBRID");
  mTypeEnum = CTrajectoryMethod::hybrid;
  setType(CTrajectoryMethod::TypeName[mTypeEnum]);
  /* Set version number */
  mVersion.setVersion(1, 0, 101);

  add("HYBRID.MaxSteps", MAX_STEPS); // Max number of doSingleStep() per step()
  add("HYBRID.LowerStochLimit", LOWER_STOCH_LIMIT);
  add("HYBRID.UpperStochLimit", UPPER_STOCH_LIMIT);
  add("HYBRID.RungeKuttaStepsize", RUNGE_KUTTA_STEPSIZE);
  //deprecated:  add("HYBRID.OutputCounter", OUTPUT_COUNTER);
  add("HYBRID.IntEpsilon", INT_EPSILON);

  mRandomGenerator = CRandom::createGenerator(CRandom::r250);

  x = NULL;
  y = NULL;
  increment = NULL;
  temp = NULL;
  k1 = NULL;
  k2 = NULL;
  k3 = NULL;
  k4 = NULL;
  testState = NULL;
  oldState = NULL;
  mStochReactionFlags = NULL;
}

/**
 *  Initializes the solver and sets the model to be used.
 *
 *  @param model A reference to an instance of a CModel 
 */
void CHybridMethod::initMethod(C_FLOAT64 start_time)
{
  mReactions = &mpModel->getReactions();
  mAmu.resize(mReactions->size());
  mAmuOld.resize(mReactions->size());
  mMetabolites = &(const_cast < CCopasiVectorN < CMetab > & > (mpModel->getMetabolites()));
  //  mDim = static_cast<C_INT32>mpModel->getTotMetab();
  mDim = mMetabolites->size();
  delete[] x;
  delete[] y;
  delete[] increment;
  delete[] temp;
  delete[] k1;
  delete[] k2;
  delete[] k3;
  delete[] k4;
  delete[] testState;
  delete[] oldState;
  delete[] mStochReactionFlags;
  x = new C_FLOAT64[mDim];
  y = new C_FLOAT64[mDim];
  increment = new C_FLOAT64[mDim];
  temp = new C_FLOAT64[mDim];
  k1 = new C_FLOAT64[mDim];
  k2 = new C_FLOAT64[mDim];
  k3 = new C_FLOAT64[mDim];
  k4 = new C_FLOAT64[mDim];
  testState = new C_FLOAT64[mDim];
  oldState = new C_INT32[mDim];

  mMaxSteps = (unsigned C_INT32) getValue("HYBRID.MaxSteps");
  std::cout << "HYBRID.MaxSteps: " << mMaxSteps << std::endl;
  mLowerStochLimit = (C_INT32) getValue("HYBRID.LowerStochLimit");
  std::cout << "HYBRID.LowerStochLimit: " << mLowerStochLimit << std::endl;
  mUpperStochLimit = (C_INT32) getValue("HYBRID.UpperStochLimit");
  std::cout << "HYBRID.UpperStochLimit: " << mUpperStochLimit << std::endl;
  if (mLowerStochLimit > mUpperStochLimit)
    std::cerr << "CHybridMethod.initialize(): Error: mLowerStochLimit ("
    << mLowerStochLimit << ") is greater than mUpperStochLimit ("
    << mUpperStochLimit << ")." << std::endl;
  mStepsize = getValue("HYBRID.RungeKuttaStepsize");
  std::cout << "HYBRID.RungeKuttaStepsize: " << mStepsize << std::endl;
  mStoi = mpModel->getStoi();

  setupBalances(); // initialize mBalances (has to be called first!)
  setupDependencyGraph(); // initialize mDG
  setupMetab2React(); // initialize mMetab2React
  setupPartition(); // initialize mStochReactionFlags
  //  partitionSystem();
  setupPriorityQueue(start_time); // initialize mPQ

  //deprecated:  mOutputFileName = string(DEFAULT_OUTPUT_FILE);
  //deprecated:  mOutputFile.open(DEFAULT_OUTPUT_FILE); // DEFAULT_OUTPUT_FILE in CHybridMethod.h
  //deprecated:  mOutputCounter = OUTPUT_COUNTER; // OUTPUT_COUNTER in CHybridMethod.h

  //deprecated:  outputDebug(cout, 0); // DEBUG
  return;
}

/**
 *  Cleans up memory, etc.
 */
void CHybridMethod::cleanup()
{
  mpModel = NULL;
  mDim = 0;
  delete[] x;
  delete[] y;
  delete[] increment;
  delete[] temp;
  delete[] k1;
  delete[] k2;
  delete[] k3;
  delete[] k4;
  delete[] testState;
  delete[] oldState;
  delete[] mStochReactionFlags;
  //deprecated:      mOutputFile.close();

  return;
}

/* DETERMINISTIC STUFF *******************************************************/

/**
 *   Integrates the deterministic reactions of the system over the specified 
 *   time interval.
 *
 *   @param ds A C_FLOAT64 specifying the stepsize.
 */
void CHybridMethod::integrateDeterministicPart(C_FLOAT64 dt)
{
  C_FLOAT64 integrationTime = 0.0;
  StochFlag * react = NULL;

  // This method uses a 4th order RungeKutta-method to integrate the deterministic part of the system. Maybe a better numerical method (adaptive stepsize, lsoda, ...) should be introduced here later on

  while ((dt - integrationTime) > mStepsize)
    {
      getState(oldState);
      rungeKutta(mStepsize, 0); // for the deterministic part of the system
      changeState(increment, y, oldState);
      integrationTime += mStepsize;
    }
  getState(oldState);
  rungeKutta((dt - integrationTime), 0);
  changeState(increment, y, oldState);

  // find the set union of all reactions, which depend on one of the deterministic reactions. the propensities of the stochastic reactions in this set union will be updated later in the method updatePriorityQueue().
  for (react = mFirstFlag; react != NULL; react = react->next)
    {
      const std::set <C_INT32> & dependents = mDG.getDependents(react->index);
      std::copy(dependents.begin(), dependents.end(),
                std::inserter(mUpdateSet, mUpdateSet.begin()));
    }
  return;
}

/**
 *   Integrates the deterministic reactions of the system over the specified 
 *   time interval.
 *
 *   @param ds A C_FLOAT64 specifying the stepsize.
 */
void CHybridMethod::integrateDeterministicPartEuler(C_FLOAT64 dt)
{
  C_FLOAT64 integrationTime = 0.0;
  StochFlag * react = NULL;
  unsigned C_INT32 i;

  while ((dt - integrationTime) > mStepsize)
    {
      for (i = 0; i < mDim; i++)
        oldState[i] = (*mMetabolites)[i]->getNumberInt();
      for (i = 0; i < mDim; i++)
        x[i] = (*mMetabolites)[i]->getNumberDbl();
      calculateDerivative(temp);
      for (i = 0; i < mDim; i++)
        increment[i] = temp[i] * dt;
      for (i = 0; i < mDim; i++)
        y[i] = x[i] + increment[i];
      for (i = 0; i < mDim; i++)
        {
          if (increment[i] != 0.0)
            (*mMetabolites)[i]->setNumberDbl(y[i]);
          else
            (*mMetabolites)[i]->setNumberInt(oldState[i]);
        }
      integrationTime += mStepsize;
    }
  for (i = 0; i < mDim; i++)
    oldState[i] = (*mMetabolites)[i]->getNumberInt();
  for (i = 0; i < mDim; i++)
    x[i] = (*mMetabolites)[i]->getNumberDbl();
  calculateDerivative(temp);
  for (i = 0; i < mDim; i++)
    increment[i] = temp[i] * (dt - integrationTime);
  for (i = 0; i < mDim; i++)
    y[i] = x[i] + increment[i];
  for (i = 0; i < mDim; i++)
    {
      if (increment[i] != 0.0)
        (*mMetabolites)[i]->setNumberDbl(y[i]);
      else
        (*mMetabolites)[i]->setNumberInt(oldState[i]);
    }

  // find the set union of all reactions, which depend on one of the deterministic reactions. the propensities of the stochastic reactions in this set union will be updated later in the method updatePriorityQueue().
  for (react = mFirstFlag; react != NULL; react = react->next)
    {
      const std::set <C_INT32> & dependents = mDG.getDependents(react->index);
      std::copy(dependents.begin(), dependents.end(),
                std::inserter(mUpdateSet, mUpdateSet.begin()));
    }
  return;
}

/**
 *   Does one 4th order RungeKutta step to integrate the system numerically.
 *
 *   @param dt A C_FLOAT64 specifying the stepsize
 *   @param test A C_INT32 determining, if the result is stored in the array
 *               testState (test != 0) or in the array y (test == 0)
 */
void CHybridMethod::rungeKutta(C_FLOAT64 dt,
                               C_INT32 test)
{
  unsigned C_INT32 i;

  getState(x); // Save state of the system into array x
  /* k1 step: k1 = dt*f(x(n)) */
  calculateDerivative(temp); // systemState == x(n)
  for (i = 0; i < mDim; i++)
    {
      k1[i] = temp[i] * dt;
    }

  /* k2 step: k2 = dt*f(x(n) + k1/2) */
  for (i = 0; i < mDim; i++)
    {
      temp[i] = k1[i] / 2.0 + x[i];
    }
  setState(temp);
  calculateDerivative(temp); // systemState == x(n) + k1/2
  for (i = 0; i < mDim; i++)
    {
      k2[i] = temp[i] * dt;
    }

  /* k3 step: k3 = dt*f(x(n) + k2/2) */
  for (i = 0; i < mDim; i++)
    {
      temp[i] = k2[i] / 2.0 + x[i];
    }
  setState(temp);
  calculateDerivative(temp); // systemState == x(n) + k2/2
  for (i = 0; i < mDim; i++)
    {
      k3[i] = temp[i] * dt;
    }

  /* k4 step: k4 = dt*f(x(n) + k3); */
  for (i = 0; i < mDim; i++)
    {
      temp[i] = k3[i] + x[i];
    }
  setState(temp);
  calculateDerivative(temp); // systemState == x(n) + k3
  for (i = 0; i < mDim; i++)
    {
      k4[i] = temp[i] * dt;
    }

  /* Find next position: x(n+1) = x(n) + 1/6*(k1 + 2*k2 + 2*k3 + k4)  *
   * and put it into the vector k1                                    */
  for (i = 0; i < mDim; i++)
    {
      increment[i] = (1.0 / 6.0) * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]);
      y[i] = x[i] + increment[i];
    }

  if (test)
    {
      for (i = 0; i < mDim; i++)
        {
          testState[i] = y[i];
        }
    }
  return;
}

/**
 *   Calculates the derivative of the system and writes it into the array
 *   deriv. Length of deriv must be mDim. CAUTION: Only deterministic
 *   reactions are taken into account. That is, this is only the derivative
 *   of the deterministic part of the system.  
 *
 *   @param deriv An array of length mDim, into which the derivative is
 *                written
 */
void CHybridMethod::calculateDerivative(C_FLOAT64 * deriv)
{
  unsigned C_INT32 i;
  C_INT32 bal = 0;
  StochFlag * j;

  // Calculate all the needed kinetic functions of the deterministic reactions
  for (j = mFirstFlag; j != NULL; j = j->next)
    {
      (*mReactions)[j->index]->calculate();
    }

  // For each metabolite add up the contributions of the deterministic reactions
  // juergen: the number of rows in mStoi equals the number of non-fixed metabolites!
  //  for (i=0; i<mDim; i++)
  for (i = 0; i < (unsigned C_INT32) mStoi.numRows(); i++)
    {
      deriv[i] = 0.0;
      for (j = mFirstFlag; j != NULL; j = j->next)
        {
          // juergen: +0.5 to get a rounding out of the static_cast
          bal = static_cast<C_INT32>(floor(mStoi[i][j->index] + 0.5));
          deriv[i] += bal * (*mReactions)[j->index]->getScaledFlux(); //  balance * flux;
        }
    }
  for (; i < mDim; i++) deriv[i] = 0.0; // important to get a correct deriv vector, because mStoi doesn't cover fixed metabolites
  return;
}

/**
 *   Gathers the state of the system into the array target. Later on CState
 *   should be used for this. Length of the array target must be mDim.
 *
 *   @param target An array of C_FLOAT64s with length mDim, into which the
 *                 state of the system is written
 */
void CHybridMethod::getState(C_FLOAT64 * target)
{
  unsigned C_INT32 i;

  for (i = 0; i < mDim; i++)
    {
      target[i] = (*mMetabolites)[i]->getNumberDbl();
    }
  return;
}

/**
 *   Gathers the state of the system into the array target. Later on CState
 *   should be used for this. Length of the array target must be mDim.
 *
 *   @param target An array of C_INT32s with length mDim, into which the
 *                 state of the system is written
 */
void CHybridMethod::getState(C_INT32 * target)
{
  unsigned C_INT32 i;

  for (i = 0; i < mDim; i++)
    {
      target[i] = (*mMetabolites)[i]->getNumberInt();
    }
  return;
}

/**
 *   Writes the state specified in the array source into the model. Later on
 *   CState should be used for this. Length of the array source must be mDim
 *   (Total number of metabolites in the model).
 *
 *   @param source An array of C_FLOAT64s with length mDim, holding the
 *                 state of the system to be set in the model
 */
void CHybridMethod::setState(C_FLOAT64 * source)
{
  unsigned C_INT32 i;

  for (i = 0; i < mDim; i++)
    {
      (*mMetabolites)[i]->setNumberDbl(source[i]);
    }
  return;
}

/**
 *   Changes the state of the system by the values stored in the array
 *   increment. Later on CState should be used for this. Length of the array
 *   increment must be mDim (Total number of metabolites in the model).
 *   Important: Only particle numbers of metabolites i with increment[i]!=0
 *   are changed. That means, that no errors are introduced by converting the
 *   particle numbers into double and back into int.
 *
 *   @param increment An array of C_FLOAT64s with length mDim, holding the
 *                    increment of the state of the system
 *   @param y         An array of C_FLOAT64s with length mDim, holding the
 *                    new state of the system
 *   @param oldState  An array of C_INT32s with length mDim, holding the
 *                    old state of the system
 */
void CHybridMethod::changeState(C_FLOAT64 * increment,
                                C_FLOAT64 * y,
                                C_INT32 * oldState)
{
  unsigned C_INT32 i;

  for (i = 0; i < mDim; i++)
    {
      if (increment[i] != 0.0)
        (*mMetabolites)[i]->setNumberDbl(y[i]);
      else
        (*mMetabolites)[i]->setNumberInt(oldState[i]);
    }
  return;
}

/**
 *   Updates the partitioning depending on the change of the system state
 *   caused by numerical integration of the deterministic part of the
 *   system.
 *
 *   @param increment An array of C_FLOAT64s with length mDim, holding the
 *                    increment of the state of the system
 *   @param y         An array of C_FLOAT64s with length mDim, holding the
 *                    new state of the system
 */

void CHybridMethod::updatePartitionDet(C_FLOAT64 * increment,
                                       C_FLOAT64 * y,
                                       C_FLOAT64 time)
{
  unsigned C_INT32 i;
  std::set <C_INT32>::iterator iter, iterEnd;
  C_FLOAT64 key;

  for (i = 0; i < mDim; i++)
    {
      if (increment[i] != 0.0)
        {
          // Only metabolites with high particle numbers can have changed,
          // because the deterministic reactions per definition operate only on
          // metabolites with high particle numbers (otherwise they were
          // stochastic). Metabolites with low particle numbers shouldn't
          // change while integrating the deterministic part of the system.
          // Therefore one has to test the particle numbers only for lower than
          // StochLimit. Deterministic reactions can get stochastic, but not
          // vice versa.
          if (y[i] < mLowerStochLimit) // juergen: hysteresis; one can prevent reactions from changing from the deterministic part of the system to the stochastic part and vice versa by using 2 different limits
            {
              // iterate over all corresponding reactions
              for (iter = mMetab2React[i].begin(), iterEnd = mMetab2React[i].end(); iter != iterEnd; iter++)
                {
                  // if reaction gets stochastic, remove it from the linked list of deterministic reactions and insert it into the priority queue
                  if (mStochReactionFlags[*iter].value == 0)
                    {
                      removeDeterministicReaction(*iter);
                      calculateAmu(*iter);
                      mAmuOld[*iter] = mAmu[*iter];
                      key = time + generateReactionTime(*iter);
                      mPQ.insertStochReaction(*iter, key);
                      std::cerr << "time: " << time << " rIndex: " << *iter
                      << "      ->stoch" << std::endl; // DEBUG
                    }
                  mStochReactionFlags[*iter].value++;
                }
            }
        }
    }
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
void CHybridMethod::getStochTimeAndIndex(C_FLOAT64 & ds, C_INT32 & rIndex)
{
  ds = mPQ.topKey();
  rIndex = mPQ.topIndex();
  return;
}

/**
 *   Executes the specified reaction in the system once. Checks if by firing
 *   this reaction (that is changing particle numbers) any other
 *   deterministic reaction gets stochastic or vice versa and updates
 *   mStochReactionFlags accordingly. In addition every dependent reaction's
 *   amu is updated.
 *
 *   @param rIndex A C_INT32 specifying the index of the reaction, which 
 *                 will be fired.
 *   @param time   The current time
 */ 
// based on Carel's updateSystemState() method in the class CStochMethod
void CHybridMethod::fireReactionAndUpdatePartition(C_INT32 rIndex, C_FLOAT64 time)
{
  // Change the particle numbers according to which step took place.
  // First, get the vector of balances in the reaction we've got.
  // (This vector expresses the number change of each metabolite
  // in the reaction.) Then step through each balance, using its
  // multiplicity to calculate a new value for the associated
  // metabolite. Finally, update the metabolite.

  unsigned C_INT32 i;
  C_INT32 number, newNumber, metabIndex;
  std::set <C_INT32>::iterator iter, iterEnd;

  for (i = 0; i < mBalances[rIndex].size(); i++)
    {
      number = mBalances[rIndex][i].metabolitePointer->getNumberInt();
      newNumber = number + mBalances[rIndex][i].balance;
      metabIndex = mBalances[rIndex][i].index;

      // update partitioning
      if ((number < mUpperStochLimit) && (newNumber >= mUpperStochLimit))
        {
          // iterate over all corresponding reactions
          for (iter = mMetab2React[metabIndex].begin(), iterEnd = mMetab2React[metabIndex].end(); iter != iterEnd; iter++)
            {
              mStochReactionFlags[*iter].value--;
              // if reaction gets deterministic, insert it into the linked list of deterministic reactions
              if (mStochReactionFlags[*iter].value == 0)
                {
                  insertDeterministicReaction(*iter);
                  mPQ.removeStochReaction(*iter);
                  std::cerr << "time: " << time << " rIndex: " << *iter
                  << " stoch->" << std::endl; // DEBUG
                }
            }
        }
      if ((newNumber < mLowerStochLimit) && (number >= mLowerStochLimit))
        {
          // iterate over all corresponding reactions
          for (iter = mMetab2React[metabIndex].begin(), iterEnd = mMetab2React[metabIndex].end(); iter != iterEnd; iter++)
            {
              if (mStochReactionFlags[*iter].value == 0)
                {
                  removeDeterministicReaction(*iter);
                  mPQ.insertStochReaction(*iter, 1234567.8);  // juergen: have to beautify this, number has to be the biggest C_FLOAT64 !!!
                  std::cerr << "time: " << time << " rIndex: " << *iter
                  << "      ->stoch" << std::endl; // DEBUG
                }
              mStochReactionFlags[*iter].value++;
            }
        }
      // juergen: if new_num < schwelle, then mark reaction as stochastic; if new_num < schwelle for none of the metabolites, then mark reaction as deterministic

      // update particle number
      (*mMetabolites)[metabIndex]->setNumberInt(newNumber);
    }
  // insert all dependent reactions into the mUpdateSet
  const std::set <C_INT32> & dependents = mDG.getDependents(rIndex);
  std::copy(dependents.begin(), dependents.end(),
            std::inserter(mUpdateSet, mUpdateSet.begin()));

  return;
}

/**
 *   Updates the priority queue.
 *
 *   @param rIndex A C_INT32 giving the index of the fired reaction (-1, if no
 *                 stochastic reaction has fired)
 *   @param time A C_FLOAT64 holding the current time
 */ 
// juergen: based on Carel's Next Reaction Method
void CHybridMethod::updatePriorityQueue(C_INT32 rIndex, C_FLOAT64 time)
{
  C_FLOAT64 newTime;
  C_INT32 index;
  std::set <C_INT32>::iterator iter, iterEnd;

  // iterate through the set of affected reactions and update the stochastic ones in the priority queue
  for (iter = mUpdateSet.begin(), iterEnd = mUpdateSet.end(); iter != iterEnd; iter++)
    {
      if (mStochReactionFlags[*iter].prev == NULL) // reaction is stochastic!
        {
          index = *iter;
          mAmuOld[index] = mAmu[index];
          calculateAmu(index);
          if (*iter == rIndex)
            {
              // draw new random number and update the reaction just fired
              newTime = time + generateReactionTime(rIndex);
              mPQ.updateNode(rIndex, newTime);
            }
          else
            {
              updateTauMu(index, time);
            }
        }
    }
  // empty the mUpdateSet
  mUpdateSet.clear();
  return;
}

C_FLOAT64 CHybridMethod::generateReactionTime(C_INT32 rIndex)
{
  C_FLOAT32 rand2 = mRandomGenerator->getRandomOO();
  return - 1 * log(rand2) / mAmu[rIndex];
}

/**
 *   Calculates an amu value for a given reaction.
 *
 *   @param rIndex A C_INT32 specifying the reaction to be updated
 */ 
// juergen: based on Sven's Next Reaction Method
void CHybridMethod::calculateAmu(C_INT32 rIndex)
{
  // We need the product of the cmu and hmu for this step.
  // We calculate this in one go, as there are fewer steps to
  // perform and we eliminate some possible rounding errors.
  C_FLOAT32 amu = 1; // initially
  C_INT32 total_substrates = 0;
  C_INT32 num_ident = 0;
  C_INT32 number = 0;
  C_INT32 lower_bound;
  // substrate_factor - The substrates, raised to their multiplicities,
  // multiplied with one another. If there are, e.g. m substrates of type m,
  // and n of type N, then substrate_factor = M^m * N^n.
  C_FLOAT64 substrate_factor = 1;
  // First, find the reaction associated with this index.
  // Keep a pointer to this.
  const CChemEq *chemeq = &mpModel->getReactions()[rIndex]->getChemEq();
  // Iterate through each substrate in the reaction
  CCopasiVector < CChemEqElement > & substrates =
    const_cast < CCopasiVector < CChemEqElement > & > (chemeq->getSubstrates());

  for (unsigned C_INT32 i = 0; i < substrates.size(); i++)
    {
      num_ident = static_cast<C_INT32>(floor(substrates[i]->getMultiplicity() + 0.5)); // juergen: +0.5 to get a rounding out of the static_cast !
      //std::cout << "Num ident = " << num_ident << std::endl;
      total_substrates += num_ident;
      number = substrates[i]->getMetabolite().getNumberInt();
      lower_bound = number - num_ident;
      //cout << "Number = " << number << "  Lower bound = " << lower_bound << endl;
      substrate_factor = substrate_factor * pow(number, num_ident);
      //cout << "Substrate factor = " << substrate_factor << endl;

      while (number > lower_bound)
        {
          amu *= number;
          number--;
        }
    }

  if (amu == 0)  // at least one substrate particle number is zero
    {
      mAmu[rIndex] = 0;
      return;
    }

  // We assume that all substrates are in the same compartment.
  // If there are no substrates, then volume is irrelevant. Otherwise,
  // we can use the volume of the compartment for the first substrate.
  //if (substrates.size() > 0) //check again!!
  if (total_substrates > 1) //check again!!
    {
      C_FLOAT64 invvolumefactor = pow(
                                    substrates[0]->getMetabolite().getCompartment()->getVolumeInv()
                                    * substrates[0]->getMetabolite().getModel()->getNumber2QuantityFactor(),
                                    total_substrates - 1);
      amu *= invvolumefactor;
      substrate_factor *= invvolumefactor;
    }

  // rate_factor is the rate function divided by substrate_factor.
  // It would be more efficient if this was generated directly, since in effect we
  // are multiplying and then dividing by the same thing (substrate_factor)!
  mpModel->getReactions()[rIndex]->calculate();
  C_FLOAT64 rate_factor = mpModel->getReactions()[rIndex]->getScaledFlux() / substrate_factor;

  //cout << "Rate factor = " << rate_factor << endl;
  amu *= rate_factor;

  mAmu[rIndex] = amu;

  //cout << "Index = " << index << "  Amu = " << amu << endl;
  return;
}

/**
 *   Updates the putative reaction time of a stochastic reaction in the 
 *   priority queue. The corresponding amu and amu_old must be set prior to
 *   the call of this method.
 *
 *   @param rIndex A C_INT32 specifying the index of the reaction 
 */
void CHybridMethod::updateTauMu(C_INT32 rIndex, C_FLOAT64 time)
{
  C_FLOAT64 newTime;

  // One must make sure that the calculation yields reasonable results even in the cases where mAmu=0 or mAmuOld=0 or both =0. Therefore mAmuOld=0 is checked. If mAmuOld equals 0, then a new random number has to be drawn, because tau equals inf inf and the stoch. information is lost. If both values equal 0, then tau should remain inf and the update of the queue can be skipped!

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
 *   take place in one compartment only, ...).
 *
 *   @return 0, if everything is ok; !0, if an error occured.
 */
C_INT32 CHybridMethod::checkModel(CModel * model)
{
  CCopasiVectorNS <CReaction> * mReactions = &model->getReactions();
  CMatrix <C_FLOAT64> mStoi = model->getStoi();
  C_INT32 i, multInt, reactSize = mReactions->size();
  unsigned C_INT32 j;
  C_FLOAT64 multFloat;
  //  C_INT32 metabSize = mMetabolites->size();

  for (i = 0; i < reactSize; i++) // for every reaction
    {
      // TEST getCompartmentNumber() == 1
      if ((*mReactions)[i]->getCompartmentNumber() != 1) return - 1;

      // TEST isReversible() == 0
      if ((*mReactions)[i]->isReversible() != 0) return - 2;

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
void CHybridMethod::setupBalances()
{
  unsigned C_INT32 i, j;
  Balance newElement;
  C_INT32 maxBalance = 0;

  mBalances.resize(mReactions->size());
  for (i = 0; i < mReactions->size(); i++)
    {
      const CCopasiVector <CChemEqElement> & balances =
        (*mReactions)[i]->getChemEq().getBalances();
      for (j = 0; j < balances.size(); j++)
        {
          newElement.metabolitePointer = const_cast < CMetab* > (& balances[j]->getMetabolite());
          newElement.index = findMetab(newElement.metabolitePointer);
          // + 0.5 to get a rounding out of the static_cast to C_INT32!
          newElement.balance = static_cast<C_INT32>(floor(balances[j]->getMultiplicity() + 0.5));
          if ((newElement.metabolitePointer->getStatus()) != CMetab::METAB_FIXED)
            if (newElement.balance > maxBalance) maxBalance = newElement.balance;
          mBalances[i].push_back(newElement); // element is copied for the push_back
        }
    }

  mMaxBalance = maxBalance; std::cout << "maxbalance" << mMaxBalance << std::endl;
  //mMaxIntBeforeStep= numeric_limits<C_INT32>::max() - mMaxSteps*mMaxBalance;
  mMaxIntBeforeStep = INT_MAX - 1 - mMaxSteps * mMaxBalance;

  return;
}

/**
 *   Sets up the dependency graph.
 */ 
// juergen: based on Carel's Next Reaction Method
void CHybridMethod::setupDependencyGraph()
{
  mDG.clear();
  std::vector< std::set<std::string>* > DependsOn;
  std::vector< std::set<std::string>* > Affects;
  unsigned C_INT32 numReactions = mpModel->getReactions().size();
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
 *   participates in a reaction as substrate or product this reaction is
 *   added to the corresponding set. 
 */
void CHybridMethod::setupMetab2React()
{
  unsigned C_INT32 i, j;
  C_INT32 metaboliteIndex;

  // Resize mMetab2React and create an initial set for each metabolite
  mMetab2React.resize(mMetabolites->size());

  // Iterate over all reactions
  for (i = 0; i < mBalances.size(); i++)
    {
      // Get the set of metabolites which take part in this reaction
      for (j = 0; j < mBalances[i].size(); j++)
        {
          // find metaboliteIndex and insert the reaction into the set
          metaboliteIndex = mBalances[i][j].index;
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
void CHybridMethod::setupMetab2ReactPlusModifier()
{
  std::vector< std::set<C_INT32>* > participatesIn;
  unsigned C_INT32 numReactions = mReactions->size();
  unsigned C_INT32 i;

  // Resize mMetab2React and create an initial set for each metabolite
  mMetab2React.resize(mMetabolites->size());

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
void CHybridMethod::setupMetab2ReactComplete()
{
  unsigned C_INT32 i, j;

  // Resize mMetab2React and create an initial set for each metabolite
  mMetab2React.resize(mMetabolites->size());

  // Iterate over all metabolites
  for (i = 0; i < mMetabolites->size(); i++)
    {
      // Iterate over all reactions
      for (j = 0; j < mReactions->size(); j++)
        {
          mMetab2React[i].insert(j);
        }
    }
  return;
}

/**
 *   Creates an initial partitioning of the system. Deterministic and 
 *   stochastic reactions are determined. The array mStochReactions is
 *   initialized.
 */
void CHybridMethod::setupPartition()
{
  unsigned C_INT32 i, j;
  StochFlag * prevFlag;
  C_INT32 averageStochLimit = (mUpperStochLimit + mLowerStochLimit) / 2;

  mStochReactionFlags = new StochFlag[mBalances.size()];

  // Initialize array mStochReactionFlags
  for (i = 0; i < mBalances.size(); i++)
    {
      mStochReactionFlags[i].index = i;
      mStochReactionFlags[i].value = 0;
      for (j = 0; j < mBalances[i].size(); j++)
        {
          if ((mBalances[i][j].metabolitePointer->getNumberInt()) < averageStochLimit)
            {
              mStochReactionFlags[i].value++;
            }
        }
    }
  mFirstFlag = NULL;
  prevFlag = NULL;
  for (i = 0; i < mBalances.size(); i++)
    {
      if (mStochReactionFlags[i].value == 0)
        {
          if (mFirstFlag != NULL)
            {
              prevFlag->next = &mStochReactionFlags[i];
              mStochReactionFlags[i].prev = prevFlag;
              prevFlag = &mStochReactionFlags[i];
            }
          else
            {
              mFirstFlag = &mStochReactionFlags[i];
              mStochReactionFlags[i].prev = &mStochReactionFlags[i]; // Important to distinguish between stochastic (prev == NULL) and deterministic (prev != NULL) reactions
              prevFlag = &mStochReactionFlags[i];
            }
        }
      else
        {
          mStochReactionFlags[i].prev = NULL;
          mStochReactionFlags[i].next = NULL;
        }
    }
  if (prevFlag != NULL)
    {
      prevFlag->next = NULL;
    }
  return;
}

/**
 *   Sets up the priority queue.
 *
 *   @param startTime The time at which the simulation starts.
 */
void CHybridMethod::setupPriorityQueue(C_FLOAT64 startTime)
{
  unsigned C_INT32 i;
  C_FLOAT64 time;

  mPQ.initializeIndexPointer(mReactions->size());

  for (i = 0; i < mReactions->size(); i++)
    {
      if (mStochReactionFlags[i].prev == NULL) // Reaction is stochastic!
        {
          calculateAmu(i);
          time = startTime + generateReactionTime(i);
          mPQ.insertStochReaction(i, time);
          std::cerr << "time: " << mpCurrentState->getTime() << " rIndex: "
          << i << "      ->stoch" << std::endl; // DEBUG
        }
    }
  return;
}

/* HELPER METHODS ************************************************************/

/**
 *   Inserts a new deterministic reaction into the linked list in the
 *   array mStochReactionFlags.
 *
 *   @param rIndex A C_INT32 giving the index of the reaction to be inserted
 *                 into the list of deterministic reactions.
 */
void CHybridMethod::insertDeterministicReaction(C_INT32 rIndex)
{
  if (mStochReactionFlags[rIndex].prev == NULL)
    // reaction is stochastic (avoids double insertions)
    {
      if (mFirstFlag != NULL)
        // there are deterministic reactions already
        {
          mFirstFlag->prev = &mStochReactionFlags[rIndex];
          mStochReactionFlags[rIndex].next = mFirstFlag;
          mFirstFlag = &mStochReactionFlags[rIndex];
          mFirstFlag->prev = mFirstFlag;
        }
      else
        {
          // there are no deterministic reactions
          // Important to distinguish between stochastic (prev == NULL) and deterministic (prev != NULL) reactions
          mStochReactionFlags[rIndex].prev = &mStochReactionFlags[rIndex];
          mFirstFlag = &mStochReactionFlags[rIndex];
        }
      mAmu[rIndex] = 0.0;
      mAmuOld[rIndex] = 0.0;
    }
  return;
}

/**
 *   Removes a deterministic reaction from the linked list in the
 *   array mStochReactionFlags.
 *
 *   @param rIndex A C_INT32 giving the index of the reaction to be removed
 *                 from the list of deterministic reactions.
 */
void CHybridMethod::removeDeterministicReaction(C_INT32 rIndex)
{
  if (mStochReactionFlags[rIndex].prev != NULL)
    // reaction is deterministic
    {
      if (&mStochReactionFlags[rIndex] != mFirstFlag)
        // reactionFlag is not the first in the linked list
        {
          mStochReactionFlags[rIndex].prev->next = mStochReactionFlags[rIndex].next;
          if (mStochReactionFlags[rIndex].next != NULL)
            mStochReactionFlags[rIndex].next->prev = mStochReactionFlags[rIndex].prev;
        }
      else
        // reactionFlag is the first in the linked list
        {
          if (mStochReactionFlags[rIndex].next != NULL) // reactionFlag is not the only one in the linked list
            {
              mFirstFlag = mStochReactionFlags[rIndex].next;
              mFirstFlag->prev = mFirstFlag;
            }
          else // reactionFlag is the only one in the linked list
            {
              mFirstFlag = NULL;
            }
        }
    }
  mStochReactionFlags[rIndex].prev = NULL;
  mStochReactionFlags[rIndex].next = NULL;
  return;
}

/**
 *   Finds the index of a metabolite in the vector mMetabolites given the
 *   address.
 *   This method could be moved into the CModel later on.
 *
 *   @param metab A pointer to an instance of CMetab.
 *   @return A C_INT32 holding the index of the metabolite. Returns -1, if
 *           the metabolite is not in the vector.
 */
C_INT32 CHybridMethod::findMetab(const CMetab * metab)
{
  unsigned C_INT32 i;

  for (i = 0; i < mMetabolites->size(); i++)
    if ((*mMetabolites)[i] == metab) return i;

  return - 1;
}

/**
 *   Gets the set of metabolites on which a given reaction depends.
 *
 *   @param rIndex The index of the reaction being executed.
 *   @return The set of metabolites depended on.
 */ 
// juergen: based Carel's Next Reaction Method, adapted by Sven
std::set<std::string> *CHybridMethod::getDependsOn(C_INT32 reaction_index)
{
  std::set<std::string> *retset = new std::set<std::string>;

  unsigned C_INT32 i, imax = mpModel->getReactions()[reaction_index]->getFunctionParameters().size();
  unsigned C_INT32 j, jmax;

  std::vector <const CMetab*> metablist;

  for (i = 0; i < imax; ++i)
    {
      if (mpModel->getReactions()[reaction_index]->getFunctionParameters()[i]->getUsage() == "PARAMETER")
        continue;
      metablist = mpModel->getReactions()[reaction_index]->getParameterMappingMetab(i);
      jmax = metablist.size();
      for (j = 0; j < jmax; ++j)
      {retset->insert(metablist[j]->getKey());}
    }
  return retset;
}

/**
 *   Gets the set of metabolites which change number when a given
 *   reaction is executed.
 *
 *   @param rIndex The index of the reaction being executed.
 *   @return The set of affected metabolites.
 */ 
// juergen: based on Carel's Next Reaction Method
std::set<std::string> *CHybridMethod::getAffects(C_INT32 rIndex)
{
  std::set<std::string> *retset = new std::set<std::string>;

  // Get the balances  associated with the reaction at this index
  // XXX We first get the chemical equation, then the balances, since the getBalances method in CReaction is unimplemented!

  for (unsigned C_INT32 i = 0; i < mBalances[rIndex].size(); i++)
    {
      if (mBalances[rIndex][i].balance != 0)
        {
          retset->insert(mBalances[rIndex][i].metabolitePointer->getKey());
        }
    }
  return retset;
}

/**
 *   Gets the set of metabolites, which participate in the given
 *   reaction either as substrate, product or modifier.
 *
 *   @param rIndex The index of the reaction being executed.
 *   @return The set of participating metabolites.
 */
std::set<C_INT32> *CHybridMethod::getParticipatesIn(C_INT32 rIndex)
{
  std::set<C_INT32> *retset = new std::set<C_INT32>;
  /*
  CCopasiVector<CReaction::CId2Metab> & subst = (*mReactions)[rIndex]->getId2Substrates();

  CCopasiVector<CReaction::CId2Metab> & prod = (*mReactions)[rIndex]->getId2Products();

  CCopasiVector<CReaction::CId2Metab> & modif = (*mReactions)[rIndex]->getId2Modifiers();

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
  return retset;
}

/**
 *   Prints out data on standard output. Deprecated.
 */
void CHybridMethod::outputData(std::ostream & os, C_INT32 mode)
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
          for (i = 0; i < mMetabolites->size(); i++)
            {
              os << (*mMetabolites)[i]->getNumberInt() << " ";
            }
          os << std::endl;
        }
      break;
    case 1:
      os << mpCurrentState->getTime() << " : ";
      for (i = 0; i < mMetabolites->size(); i++)
        {
          os << (*mMetabolites)[i]->getNumberInt() << " ";
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
void CHybridMethod::outputDebug(std::ostream & os, C_INT32 level)
{
  unsigned C_INT32 i, j;
  std::set <C_INT32>::iterator iter, iterEnd;

  os << "outputDebug(" << level << ") *********************************************** BEGIN" << std::endl;

  switch (level)
    {
    case 0:      // Everything !!!
      os << "Version: " << mVersion.getVersion() << " Name: " << getName() << " Method: " /* << mMethod */ << std::endl;
      os << "mTime: " << mpCurrentState->getTime() << std::endl;
      os << "mDim: " << mDim << std::endl;
      os << "mReactions.size(): " << mReactions->size() << std::endl;
      for (i = 0; i < mReactions->size(); i++)
        os << *(*mReactions)[i] << std::endl;
      os << "mMetabolites.size(): " << mMetabolites->size() << std::endl;
      for (i = 0; i < mMetabolites->size(); i++)
        os << *(*mMetabolites)[i] << std::endl;
      os << "mStoi: " << std::endl;
      for (i = 0; i < (unsigned C_INT32) mStoi.numRows(); i++)
        {
          for (j = 0; j < (unsigned C_INT32) mStoi.numCols(); j++)
            os << mStoi[i][j] << " ";
          os << std::endl;
        }
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
      os << std::endl;
      os << "temp: ";
      for (i = 0; i < mDim; i++)
        os << temp[i] << " ";
      os << std::endl;
      os << "k1: ";
      for (i = 0; i < mDim; i++)
        os << k1[i] << " ";
      os << std::endl;
      os << "k2: ";
      for (i = 0; i < mDim; i++)
        os << k2[i] << " ";
      os << std::endl;
      os << "k3: ";
      for (i = 0; i < mDim; i++)
        os << k3[i] << " ";
      os << std::endl;
      os << "k4: ";
      for (i = 0; i < mDim; i++)
        os << k4[i] << " ";
      os << std::endl;
      os << "testState: ";
      for (i = 0; i < mDim; i++)
        os << testState[i] << " ";
      os << std::endl;
      os << "mStochReactionFlags: " << std::endl;
      for (i = 0; i < mBalances.size(); i++)
        os << mStochReactionFlags[i];
      os << "mFirstFlag: " << std::endl;
      if (mFirstFlag == NULL) os << "NULL" << std::endl; else os << *mFirstFlag;
      os << "mBalances: " << std::endl;
      for (i = 0; i < mBalances.size(); i++)
        {
          for (j = 0; j < mBalances[i].size(); j++)
            os << mBalances[i][j];
          os << std::endl;
        }
      os << "mLowerStochLimit: " << mLowerStochLimit << std::endl;
      os << "mUpperStochLimit: " << mUpperStochLimit << std::endl;
      //deprecated:      os << "mOutputCounter: " << mOutputCounter << endl;
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
      for (i = 0; i < mReactions->size(); i++)
        os << mAmu[i] << " ";
      os << std::endl;
      os << "mAmuOld: " << std::endl;
      for (i = 0; i < mReactions->size(); i++)
        os << mAmuOld[i] << " ";
      os << std::endl;
      os << "mUpdateSet: " << std::endl;
      for (iter = mUpdateSet.begin(), iterEnd = mUpdateSet.end(); iter != iterEnd; iter++)
        os << *iter;
      os << std::endl;
      os << "mRandomGenerator: " << mRandomGenerator << std::endl;
      os << "mFail: " << mFail << std::endl;
      os << "mDG: " << std::endl << mDG;
      os << "mPQ: " << std::endl << mPQ;
      os << "Particle numbers: " << std::endl;
      for (i = 0; i < mMetabolites->size(); i++)
        {
          os << (*mMetabolites)[i]->getNumberInt() << " ";
        }
      os << std::endl;
      break;

    case 1:       // Variable values only
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
      os << std::endl;
      os << "temp: ";
      for (i = 0; i < mDim; i++)
        os << temp[i] << " ";
      os << std::endl;
      os << "k1: ";
      for (i = 0; i < mDim; i++)
        os << k1[i] << " ";
      os << std::endl;
      os << "k2: ";
      for (i = 0; i < mDim; i++)
        os << k2[i] << " ";
      os << std::endl;
      os << "k3: ";
      for (i = 0; i < mDim; i++)
        os << k3[i] << " ";
      os << std::endl;
      os << "k4: ";
      for (i = 0; i < mDim; i++)
        os << k4[i] << " ";
      os << std::endl;
      os << "testState: ";
      for (i = 0; i < mDim; i++)
        os << testState[i] << " ";
      os << std::endl;
      os << "mStochReactionFlags: " << std::endl;
      for (i = 0; i < mBalances.size(); i++)
        os << mStochReactionFlags[i];
      os << "mFirstFlag: " << std::endl;
      if (mFirstFlag == NULL) os << "NULL" << std::endl; else os << *mFirstFlag;
      os << "mAmu: " << std::endl;
      for (i = 0; i < mReactions->size(); i++)
        os << mAmu[i] << " ";
      os << std::endl;
      os << "mAmuOld: " << std::endl;
      for (i = 0; i < mReactions->size(); i++)
        os << mAmuOld[i] << " ";
      os << std::endl;
      os << "mUpdateSet: " << std::endl;
      for (iter = mUpdateSet.begin(), iterEnd = mUpdateSet.end(); iter != iterEnd; iter++)
        os << *iter;
      os << std::endl;
      os << "mPQ: " << std::endl << mPQ;
      os << "Particle numbers: " << std::endl;
      for (i = 0; i < mMetabolites->size(); i++)
        {
          os << (*mMetabolites)[i]->getNumberInt() << " ";
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
