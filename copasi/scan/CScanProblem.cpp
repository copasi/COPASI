/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanProblem.cpp,v $
   $Revision: 1.26 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/13 13:19:19 $
   End CVS Header */

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
CScanProblem::CScanProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::scan, pParent),
    mpScanParameterList(NULL),
    mpTrajectory(NULL),
    mpSteadyState(NULL),
    mMapping(),
    mStartValues()
{
  addGroup("ScanItemList");
  mpScanParameterList = (CCopasiParameterGroup *) getParameter("ScanItemList");

  addParameter("ProcessTrajectory", CCopasiParameter::BOOL, false);
  addParameter("ProcessSteadyState", CCopasiParameter::BOOL, false);

  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CTrajectoryProblem &" src
 */
CScanProblem::CScanProblem(const CScanProblem & src,
                           const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    mpScanParameterList(NULL),
    mpTrajectory(src.mpTrajectory),
    mpSteadyState(src.mpSteadyState),
    mMapping(),
    mStartValues()
{
  mpScanParameterList = (CCopasiParameterGroup *) getParameter("ScanItemList");
  CONSTRUCTOR_TRACE;
}

/**
 *  Destructor.
 */
CScanProblem::~CScanProblem()
{DESTRUCTOR_TRACE;}

/**
 *  Size of the scanItem vector
 */
unsigned C_INT32 CScanProblem::getListSize() const
  {return mpScanParameterList->size();}

bool CScanProblem::addScanItem(const std::string & name)
{return mpScanParameterList->addGroup(name);}

/**
 * Remove a parameter from the list
 */
void CScanProblem::removeScanItem(const std::string & name)
{mpScanParameterList->removeParameter(name);}

/*
  Swap
 */
void CScanProblem::swapScanItem(unsigned C_INT32 indexFrom, unsigned C_INT32 indexTo)
{mpScanParameterList->swap(indexFrom, indexTo);}

/**
 *  Get a Scan Item from the vector ScanItem
 * @param "C_INT32" itemNumber
 */
CCopasiParameterGroup * CScanProblem::getScanItem(C_INT32 itemNumber)
{
  return
  (CCopasiParameterGroup *) mpScanParameterList->getParameter(itemNumber);
}

/**
 *  Add a parameter to a scan item
 * @param "const C_INT32" itemNumber
 * @param "const std::string &" name
 * @param "const double &" value
 */
void CScanProblem::addScanItemParameter(const C_INT32 itemNumber,
                                        const std::string & name,
                                        const double & value)
{
  ((CCopasiParameterGroup *)
   mpScanParameterList->getParameter(itemNumber))
  ->addParameter(name, CCopasiParameter::DOUBLE, value);
}

/**
 * Get a parameter from a scan item
 * @param "const C_INT32" itemNumber
 * @param "const std::string &" name
 */
void * CScanProblem::getScanItemParameter(const C_INT32 itemNumber,
    const std::string & name)
{
  return
  ((CCopasiParameterGroup *)
   mpScanParameterList->getParameter(itemNumber))
  ->getValue(name);
}

/**
 * Load a trajectory problem
 * @param "CReadConfig &" configBuffer
 */

void CScanProblem::load(CReadConfig & configBuffer,
                        CReadConfig::Mode C_UNUSED(mode))
{
  /* :TODO: How important is it to read old scan problems? */
  /*        This is realated to to the reading of old report definitions. */

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

bool CScanProblem::processTrajectory() const
  {return * (bool *) getValue("ProcessTrajectory");}

bool CScanProblem::setProcessTrajectory(const bool & processTrajectory)
{return setValue("ProcessTrajectory", processTrajectory);}

bool CScanProblem::processSteadyState() const
  {return * (bool *) getValue("ProcessSteadyState");}

bool CScanProblem::setProcessSteadyState(const bool & processSteadyState)
{return setValue("ProcessSteadyState", processSteadyState);}

bool CScanProblem::setModel(CModel * pModel)
{
  mpModel = pModel;

  return true;
}

bool CScanProblem::initialize()
{
  unsigned C_INT32 Size = getListSize();
  mCalculateVariables.resize(Size);
  mMapping.resize(Size);
  mStartValues.resize(Size);
  mCalculateResults.resize(1);
  CCopasiObject * pObject;

  InitScan();

  std::vector< CCopasiContainer * > ListOfContainer;

  unsigned C_INT32 i;
  for (i = 0; i < Size; i++)
    {
      pObject = CCopasiContainer::ObjectFromName(ListOfContainer,
                ((CCopasiParameter *) getScanItem(i))->getObjectName());
      if (!pObject) fatalError();
      if (!pObject->isValueDbl()) fatalError();

      mStartValues[i] = *(mMapping[i] = (C_FLOAT64 *) pObject->getReference());
    }

  return true;
}

bool CScanProblem::calculate()
{
  unsigned C_INT32 i, imax = mMapping.size();
  for (i = 0; i < imax; i ++)
    *mMapping[i] = mCalculateVariables[i];

  if ((mpSteadyState != NULL) && processSteadyState())
    {
      // std::cout << "COptProblem: mpSteadyState";
      ((CSteadyStateProblem *) getSteadyStateTask()->getProblem())->
      setInitialState(getSteadyStateTask()->getProblem()->getModel()
                      ->getInitialState());
      mpSteadyState->process();
    }

  if ((mpTrajectory != NULL) && processTrajectory())
    {
      ((CTrajectoryProblem *) getTrajectoryTask()->getProblem())->
      setInitialState(getTrajectoryTask()->getProblem()->getModel()
                      ->getInitialState());

      mpTrajectory->process();
    }

  return true;
}

bool CScanProblem::restore()
{
  unsigned C_INT32 i, imax = mMapping.size();
  for (i = 0; i < imax; i ++)
    *mMapping[i] = mStartValues[i];

  return true;
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
  unsigned C_INT32 i, density;
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
  if (* (unsigned C_INT32 *) getScanItemParameter(0, "density") < 2)
    setScanItemParameter(0, "density", (unsigned C_INT32) 2);

  unsigned C_INT32 TotIteration = 1;
  for (i = 0, density = 2; i < scanDimension; i++)
    {
      // if this item is slave keep the density of the master
      if (* (bool *) getScanItemParameter(i, "indp"))
        {
          density = * (unsigned C_INT32 *) getScanItemParameter(i, "density");
          TotIteration *= density;
        }

      // calculate the amplitude
      if (* (bool *) getScanItemParameter(i, "log"))
        {
          if ((* (C_FLOAT64 *) getScanItemParameter(i, "min") <= 0) ||
              (* (C_FLOAT64 *) getScanItemParameter(i, "max") <= 0))
            {
              // logarithmic scanning requires positive arguments!
              // user should be warned, but this should never happen!
              setScanItemParameter(i, "min", (C_FLOAT64) 1.0);
              setScanItemParameter(i, "max", (C_FLOAT64) 2.0);
            }
          setScanItemParameter(i, "ampl",
                               (C_FLOAT64) (log10(* (C_FLOAT64 *)
                                                  getScanItemParameter(i, "max"))
                                            - log10(* (C_FLOAT64 *)
                                                    getScanItemParameter(i, "min"))));
        }
      else
        setScanItemParameter(i, "ampl",
                             (C_FLOAT64) (* (C_FLOAT64 *)
                                          getScanItemParameter(i, "max")
                                          - * (C_FLOAT64 *)
                                          getScanItemParameter(i, "min")));
      // calculate the increment
      setScanItemParameter(i, "incr",
                           (C_FLOAT64) (* (C_FLOAT64 *)
                                        getScanItemParameter(i, "ampl")
                                        / (* (unsigned C_INT32 *)
                                           getScanItemParameter(i, "density")
                                           - 1)));
    }
}

// this function counts the number of iterations to execute
unsigned C_INT32 CScanProblem::CountScan(void)
{
  unsigned C_INT32 i;
  unsigned C_INT32 TotIteration = 1;
  unsigned C_INT32 scanDimension = getListSize();
  for (i = 0; i < scanDimension; i++)
    if (getScanItemParameter(i, "indp"))
      TotIteration *= (unsigned C_INT32) getScanItemParameter(i, "density");
  return TotIteration;
}

CSteadyStateTask* CScanProblem::getSteadyStateTask() {return mpSteadyState;}
CTrajectoryTask* CScanProblem::getTrajectoryTask() {return mpTrajectory;}

/**
 * check if an object already exists in the list
 */
bool CScanProblem::bExisted(const std::string & name)
{return (mpScanParameterList->getIndex(name) != C_INVALID_INDEX);}
