/**
 *  CTrajectoryProblem class.
 *  This class describes the trajectory problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *
 *  Created for Copasi by Stefan Hoops 2002
 */

#include <string>

//#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "utilities/CGlobals.h"
#include "utilities/CReadConfig.h"
#include "utilities/CWriteConfig.h"
#include "CScanProblem.h"
#include "math.h"
#include "randomGenerator/CRandom.h"
#include "randomGenerator/Cr250.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h" 
/**
 *  Default constructor.
 *
 */
CScanProblem::CScanProblem():
    mpModel(NULL),
    mProcessTrajectory(false),
    mpTrajectory(NULL),
    mProcessSteadyState(false),
    mpSteadyState(NULL),
    mScanItemList()
{
  CRandom *pRandomGenerator = CRandom::createGenerator();
  Cr250* pCr250Generator = (Cr250*)(CRandom::createGenerator(CRandom::r250));
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CTrajectoryProblem &" src
 */
CScanProblem::CScanProblem(const CScanProblem & src):
    mpModel(src.mpModel),
    mProcessTrajectory(src.mProcessTrajectory),
    mpTrajectory(src.mpTrajectory),
    mProcessSteadyState(src.mProcessSteadyState),
    mpSteadyState(src.mpSteadyState),
    mScanItemList(src.mScanItemList)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CScanProblem::~CScanProblem()
{DESTRUCTOR_TRACE;}

/**
 *  Size of the scanItem vector
 */
unsigned C_INT32 CScanProblem::getListSize() const
  {return mScanItemList.size();}

/**
 *  Add a Scan Item to the vector ScanItem
 * @param const CMethodParameterList & Item
 */
void CScanProblem::addScanItem(const CMethodParameterList & Item)
{mScanItemList.add(Item);}

/*
  Remove a parameter from the list
 */
void CScanProblem::removeScanItem(const std::string & name)
{
  mScanItemList.remove(name);
}

/*
  Swap
 */
void CScanProblem::swapScanItem(unsigned C_INT32 indexFrom, unsigned C_INT32 indexTo)
{
  mScanItemList.swap(indexFrom, indexTo);
}

/**
 *  Get a Scan Item from the vector ScanItem
 * @param "C_INT32" itemNumber
 */
CMethodParameterList * CScanProblem::getScanItem(C_INT32 itemNumber)
{return mScanItemList[itemNumber];}

/**
 *  Add a parameter to a scan item
 * @param "const C_INT32" itemNumber
 * @param "const std::string &" name
 * @param "const double &" value
 */
void CScanProblem::addScanItemParameter(const C_INT32 itemNumber,
                                        const std::string & name,
                                        const double & value)
{mScanItemList[itemNumber]->add(name, value);}

/**
 *  Get a parameter from a scan item
 * @param "const C_INT32" itemNumber
 * @param "const std::string &" name
 */
const double & CScanProblem::getScanItemParameter(const C_INT32 itemNumber,
    const std::string & name)
{return mScanItemList[itemNumber]->getValue(name);}

/**
 *  Set the value of a parameter in a scan item
 * @param "const C_INT32" itemNumber
 * @param "const std::string &" name
 * @param "const double &" value
 */
void CScanProblem::setScanItemParameter(const C_INT32 itemNumber,
                                        const std::string & name,
                                        const double & value)
{mScanItemList[itemNumber]->setValue(name, value);}

/**
 * Load a trajectory problem
 * @param "CReadConfig &" configBuffer
 */

void CScanProblem::load(CReadConfig & configBuffer,
                        CReadConfig::Mode mode)
{
  /*  if (configBuffer.getVersion() < "4.0")
      {
        mpModel = Copasi->Model;
        configBuffer.getVariable("EndTime", "C_FLOAT64",
                                 (void *) & mEndTime,
                                 CReadConfig::LOOP);
        configBuffer.getVariable("Points", "C_INT32",
                                 (void *) & mStepNumber);
        mStepNumberSetLast = true;
        mStartTime = 0.0;
        sync();
        mpInitialState = mpModel->getInitialState();
      }
    else
      {
        string Tmp;
   
        configBuffer.getVariable("TrajectoryProblemModel", "string", &Tmp, mode);
        if (Tmp == Copasi->Model->getTitle())
          mpModel = Copasi->Model;
        else
          fatalError();
   
        configBuffer.getVariable("TrajectoryProblemStepNumber",
                                 "C_INT32", &mStepNumber);
        configBuffer.getVariable("TrajectoryProblemStepSize",
                                 "C_FLOAT64", &mStepSize);
        configBuffer.getVariable("TrajectoryProblemSetLast",
                                 "bool", &mStepNumberSetLast);
        configBuffer.getVariable("TrajectoryProblemStartTime",
                                 "C_FLOAT64", &mStartTime);
        configBuffer.getVariable("TrajectoryProblemEndTime",
                                 "C_FLOAT64", &mEndTime);
        mpInitialState = new CState;
        mpInitialState->load(configBuffer);
      }
  */
  mpSteadyState->load(configBuffer);
  mpTrajectory->load(configBuffer);
}

/**
 * Save a trajectory problem
 * @param "CWriteConfig &" configBuffer
 */

void CScanProblem::save(CWriteConfig & configBuffer) const
  {
    /*
        string Tmp = mpModel->getTitle();
        configBuffer.setVariable("TrajectoryProblemModel", "string", &Tmp);
     
        configBuffer.setVariable("TrajectoryProblemStepNumber",
                                 "C_INT32", &mStepNumber);
        configBuffer.setVariable("TrajectoryProblemStepSize",
                                 "C_FLOAT64", &mStepSize);
        configBuffer.setVariable("TrajectoryProblemSetLast",
                                 "bool", &mStepNumberSetLast);
        configBuffer.setVariable("TrajectoryProblemStartTime",
                                 "C_FLOAT64", &mStartTime);
        configBuffer.setVariable("TrajectoryProblemEndTime",
                                 "C_FLOAT64", &mEndTime);
        mpInitialState->save(configBuffer);
    */
    mpSteadyState->save(configBuffer);
    mpTrajectory->save(configBuffer);
  }

bool CScanProblem::processTrajectory() const {return mProcessTrajectory;}

bool CScanProblem::setProcessTrajectory(const bool & processTrajectory)
{
  mProcessTrajectory = processTrajectory;
  return true;
}

bool CScanProblem::processSteadyState() const {return mProcessSteadyState;}

bool CScanProblem::setProcessSteadyState(const bool & processSteadyState)
{
  mProcessSteadyState = processSteadyState;
  return true;
}

void CScanProblem::setModel(CModel * pModel) {mpModel = pModel;}

CModel * CScanProblem::getModel() const {return mpModel;}

void CScanProblem::calculate()
{
  if ((mpSteadyState != NULL) && mProcessSteadyState)
    {
      // std::cout << "COptProblem: mpSteadyState";
      mpSteadyState->getProblem()->getModel()->compile();
      mpSteadyState->getProblem()->
      setInitialState(mpSteadyState->getProblem()->getModel()->getInitialState());
      mpSteadyState->process();
    }
  if ((mpTrajectory != NULL) && mProcessTrajectory)
    {
      // std::cout << "COptProblem: mpTrajectory";
      mpTrajectory->getProblem()->getModel()->compile();
      mpTrajectory->getProblem()->
      setInitialState(mpTrajectory->getProblem()->getModel()->getInitialState());
      mpTrajectory->getProblem()->
      setStartTime(mpTrajectory->getProblem()->getStartTime());
      mpTrajectory->process();
    }
}

void CScanProblem::setSteadyStateTask(CSteadyStateTask* pSteadyStateTask)
{
  mpSteadyState = pSteadyStateTask;
}

void CScanProblem::setTrajectoryTask(CTrajectoryTask* pTrajectoryTask)
{
  mpTrajectory = pTrajectoryTask;
}

void CScanProblem::InitScan(void)
{
  int i, density;
  unsigned C_INT32 scanDimension = getListSize();
  // do nothing if ScanDimension is smaller than 1
  if (scanDimension < 1)
    {
      scanDimension = 0;
      return;
    }
  // ensure that that the first item is a master
  setScanItemParameter(0, "indp", true);
  // and that its density is >= 2
  if (getScanItemParameter(0, "density") < 2)
    setScanItemParameter(0, "density", 2);

  unsigned C_INT32 TotIteration = 1;
  for (i = 0, density = 2; i < scanDimension; i++)
    {
      // if this item is slave keep the density of the master
      if (getScanItemParameter(i, "indp"))
        {
          density = getScanItemParameter(i, "density");
          TotIteration *= density;
        }

      // calculate the amplitude
      if (getScanItemParameter(i, "log"))
        {
          if ((getScanItemParameter(i, "min") <= 0) ||
              (getScanItemParameter(i, "max") <= 0))
            {
              // logarithmic scanning requires positive arguments!
              // user should be warned, but this should never happen!
              setScanItemParameter(i, "min", 1.0);
              setScanItemParameter(i, "max", 2.0);
            }
          setScanItemParameter(i, "ampl",
                               log10(getScanItemParameter(i, "max"))
                               - log10(getScanItemParameter(i, "min")));
        }
      else
        setScanItemParameter(i, "ampl",
                             getScanItemParameter(i, "max")
                             - getScanItemParameter(i, "min"));
      // calculate the increment
      setScanItemParameter(i, "incr", getScanItemParameter(i, "ampl") / (getScanItemParameter(i, "density") - 1));
    }
}

/**
 *  set the values master and all slave parameters
 * @param "C_INT32 i" initial value
 * @param "C_INT32 first" first parameter (master)
 * @param "C_INT32 last" last slave parameter
 */

void CScanProblem::setScanParameterValue(unsigned C_INT32 i,
    unsigned C_INT32 first,
    unsigned C_INT32 last)
{
  unsigned C_INT32 j;
  double min, max, incr, ampl;
  for (j = first; j < last; j++)
    {
      // making a copy of the min and max parameters of the scanItem j
      min = getScanItemParameter(j, "min");
      max = getScanItemParameter(j, "max");
      ampl = getScanItemParameter(j, "ampl");
      incr = getScanItemParameter(j, "incr");

      // switch the grid type and set values accordingly
      switch ((int)getScanItemParameter(j, "gridType"))
        {
        case SD_UNIFORM:
          if (getScanItemParameter(j, "log"))
            setScanItemParameter(j, "value", min* pow(10, ampl * pCr250Generator->getRandomCO())); //dr250()
          else
            setScanItemParameter(j, "value", min + ampl * pCr250Generator->getRandomCO()); //dr250()
          break;
        case SD_GAUSS:
          if (getScanItemParameter(j, "log"))
            //CRandom::getRandomNormalLog(const C_FLOAT64 & mean, const C_FLOAT64 & sd)
            setScanItemParameter(j, "value", pRandomGenerator->getRandomNormalLog(min, max));
          else
            setScanItemParameter(j, "value", pRandomGenerator->getRandomNormal(min, max));
          break;
        case SD_BOLTZ:
          if (getScanItemParameter(j, "log"))
            setScanItemParameter(j, "value", pRandomGenerator->getRandomNormalLog(min, max));
          else
            setScanItemParameter(j, "value", pRandomGenerator->getRandomNormalPositive(min, max));
          break;
        case SD_REGULAR:
          // log scale
          if (getScanItemParameter(j, "log"))
            setScanItemParameter(j, "value", (min*pow(10, incr*i)));
          // non-log scale
          else
            setScanItemParameter(j, "value", (min + incr*i));
          break;
        }
    }
}

// this function counts the number of iterations to execute
unsigned C_INT32 CScanProblem::CountScan(void)
{
  int i;
  unsigned C_INT32 TotIteration = 1;
  unsigned C_INT32 scanDimension = getListSize();
  for (i = 0; i < scanDimension; i++)
    if (getScanItemParameter(i, "indp"))
      TotIteration *= (unsigned C_INT32) getScanItemParameter(i, "density");
  return TotIteration;
}
