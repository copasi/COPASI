/**
 *  File name: CTrajactory.cpp
 *
 *  Research Programmer: Yongqun He
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the .cpp file for the class CTrajectory.
 *           It is to solve the trajectory time course problem of copasi
 */

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "CTrajectory.h"

using std::cout;

//default constructor
CTrajectory::CTrajectory()
{
  mPoints = 0;
  mEndTime = 0.0;
  mN = 0;
  mMethod = CTrajectory::UNDEFINED;

  mY = NULL;
  mModel = NULL;
  mStochSolver = NULL;

  mOutInit = NULL;
  mOutPoint = NULL;
  mOutEnd = NULL;
}

//destructor
CTrajectory::~CTrajectory()
{
  cout << "~CTrajectory " << endl;
}

void CTrajectory::initialize()
{
  cleanup();

  if (!mModel)
    fatalError();

  mN = mModel->getIndMetab();

  mY = mModel->getInitialNumbersDbl();

  mStartTime = 0;

  cout << "Method = " << mMethod << endl;

  switch (mMethod)
    {
    case CONTINUOUS_ODE:
      fatalError();
      break;

    case STOCH_DIRECT:
      // we're doing a stochastic simulation
      cout << "In trajectory: performing a stochastic simulation\n";
      mStochSolver = new CStochSolver(mMethod);
      cout << "Initializing the solver\n";
      mStochSolver->initialize(mModel, mStartTime);
      break;

    case STOCH_NEXTREACTION:
      // we're doing a stochastic simulation
      cout << "In trajectory: performing a stochastic simulation (next reaction)\n";
      mStochSolver = new CStochSolver(mMethod);
      cout << "Initializing the solver\n";
      mStochSolver->initialize(mModel, mStartTime);
      break;

    default:
      fatalError();
    }

  mOutInit = new COutputEvent(0);
  mOutPoint = new COutputEvent(1);
  mOutEnd = new COutputEvent(2);
  //  if (mOutInit || mOutPoint || mOutEnd)
  //      Copasi->OutputList.compile("Time-course output",mModel,this);

  return;
}

void CTrajectory::cleanup()
{
  if (mY)
    delete [] mY;

  mY = NULL;

  if (mStochSolver)
    {
      mStochSolver->cleanup();
      delete mStochSolver;
    }

  mStochSolver = NULL;
  return;
}

C_INT32 CTrajectory::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;

  if (configbuffer.getVersion() < "4.0")
    mMethod = CTrajectory::CONTINUOUS_ODE;
  else
    configbuffer.getVariable("TrajectoryMethod", "C_INT32", &mMethod,
                             CReadConfig::SEARCH);

  if ((Fail = configbuffer.getVariable("EndTime", "C_FLOAT64",
                                       (void *) & mEndTime,
                                       CReadConfig::LOOP)))
    return Fail;

  if ((Fail = configbuffer.getVariable("Points", "C_INT32",
                                       (void *) & mPoints)))
    return Fail;

  if ((Fail = configbuffer.getVariable("OutputTimeZero", "C_INT16",
                                       (void *) & mOutputTimeZero)))
    return Fail;

  return Fail;
}

C_INT32 CTrajectory::save(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;

  configbuffer.setVariable("TrajectoryMethod", "C_INT32", &mMethod);

  if ((Fail = configbuffer.setVariable("EndTime", "C_FLOAT64",
                                       (void *) & mEndTime)))
    return Fail;

  if ((Fail = configbuffer.setVariable("Points", "C_FLOAT64",
                                       (void *) & mPoints)))
    return Fail;

  if ((Fail = configbuffer.setVariable("OutputTimeZero", "C_INT16",
                                       (void *) & mOutputTimeZero)))
    return Fail;

  return Fail;
}

void CTrajectory::setModel(CModel * aModel)
{
  mModel = aModel;
}

CModel * CTrajectory::getModel() const
  {
    return mModel;
  }

void CTrajectory::setPoints(const C_INT32 anInt)
{
  mPoints = anInt;
}

C_INT32 CTrajectory::getPoints() const
  {
    return mPoints;
  }

void CTrajectory::setStartingPoint(const C_FLOAT64 & time,
                                   const C_FLOAT64 * particleNumbers)
{
  mStartTime = time;

  if (mY)
    delete [] mY;

  if (particleNumbers)
    {
      unsigned C_INT32 dim = mModel->getIndMetab();
      mY = new C_FLOAT64[dim];

      for (unsigned C_INT32 i = 0; i < dim; i++)
        mY[i] = particleNumbers[i];
    }
  else
    mY = mModel->getInitialNumbersDbl();
}

void CTrajectory::setMaxSteps(const C_INT32 max_steps)
{
  mMaxSteps = max_steps;
}

void CTrajectory::setEndTime(const C_FLOAT64 aDouble)
{
  mEndTime = aDouble;
}

const C_FLOAT64 & CTrajectory::getEndTime() const
  {
    return mEndTime;
  }

const C_FLOAT64 & CTrajectory::getTime() const
  {
    return mTime;
  }

void CTrajectory::setMethod(const CTrajectory::MethodType & anInt)
{
  mMethod = anInt;
}

const CTrajectory::MethodType & CTrajectory::getMethod() const
  {
    return mMethod;
  }

void dummy_out(CModel* model, double time)
{
  static int ccc = 0;

  if (100 == (ccc++))
    {
      ccc = 0;
      cout << " " << time << " ";

      for (int j = 0; j < 5; j++)
        cout << model->getMetabolites()[j]->getNumberInt() << "  ";

      cout << endl;
    }
}

void CTrajectory::process(ofstream &fout)
{
  mModel->setNumbersDblAndUpdateConcentrations(mY);

  //print for the initial time point

  if (mOutInit)
    mOutInit->print(Copasi->OutputList, fout);

  // The trajectory can be calculated using the ODE solver,
  // one of the stochastic solver, or a hybrid method (as yet unimplemented)
  if (mMethod == CONTINUOUS_ODE)
    {
      fatalError();
    }
  else if (mMethod == STOCH_DIRECT || mMethod == STOCH_NEXTREACTION)
    {
      C_FLOAT64 time = mStartTime;
      C_INT32 step = 0;

      while (step < mMaxSteps && time < mEndTime && time >= 0)
        {
          time = mStochSolver->getStochMethod()->doStep(time);
          dummy_out(mModel, time);
          step++;
        }
    }

  if (mOutEnd && !mOutPoint)
    mOutEnd->print(Copasi->OutputList, fout);
}
