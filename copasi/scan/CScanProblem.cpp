/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanProblem.cpp,v $
   $Revision: 1.32 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/01/04 17:20:48 $
   End CVS Header */

/**
 *  CScanProblem class.
 *  
 */

#include <string>

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CScanProblem.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "utilities/CGlobals.h"

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CScanProblem::CScanProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::scan, pParent),
    mInitialState()
    //mEndState()
{
  addParameter("Subtask", CCopasiParameter::UINT, (unsigned C_INT32) CCopasiTask::steadyState);

  addGroup("ScanItems");
  mpScanItems = dynamic_cast<CCopasiParameterGroup*>(getParameter("ScanItems"));

  addParameter("Output in subtask", CCopasiParameter::BOOL, false);
  addParameter("Adjust initial conditions", CCopasiParameter::BOOL, true);

  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CScanProblem &" src
 */
CScanProblem::CScanProblem(const CScanProblem & src,
                           const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    mInitialState(src.mInitialState)
    //mEndState(src.mEndState)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CScanProblem::~CScanProblem()
{DESTRUCTOR_TRACE;}

/**
 * Set the model the problem is dealing with.
 * @param "CModel *" pModel
 */
bool CScanProblem::setModel(CModel * pModel)
{
  mpModel = pModel;
  mInitialState.setModel(mpModel);
  return true;
}

//***********************************

void CScanProblem::setSubtask(CCopasiTask::Type type)
{
  setValue("Subtask", (unsigned C_INT32)type);
}

CCopasiTask::Type CScanProblem::getSubtask() const
  {return * (CCopasiTask::Type *) getValue("Subtask");}

//************************************

void CScanProblem::setOutputInSubtask(bool ois)
{
  setValue("Output in subtask", ois);
}

const bool & CScanProblem::getOutputInSubtask() const
  {return * (bool *) getValue("Output in subtask");}

//************************************

void CScanProblem::setAdjustInitialConditions(bool aic)
{
  setValue("Adjust initial conditions", aic);
}

const bool & CScanProblem::getAdjustInitialConditions() const
  {return * (bool *) getValue("Adjust initial conditions");}

//************************************

/**
 * Set the initial state of the problem.
 * @param "const CState &" initialState
 */
void CScanProblem::setInitialState(const CState & initialState)
{
  mInitialState = initialState;
}

/**
 * Set the initial state of the problem.
 * @param "const CStateX &" initialState
 */
void CScanProblem::setInitialState(const CStateX & initialState)
{
  mInitialState = initialState;
}

/**
 * Retrieve the initial state of the problem.
 * @return "const CState *" pInitialState
 */
const CState & CScanProblem::getInitialState() const
  {return mInitialState;}

/**
 * Load a trajectory problem
 * @param "CReadConfig &" configBuffer
 */
void CScanProblem::load(CReadConfig & C_UNUSED(configBuffer),
                        CReadConfig::Mode C_UNUSED(mode))
{
  /*  C_FLOAT64 dbl;
    unsigned C_INT32 uint;
   
    if (configBuffer.getVersion() < "4.0")
      {
        mpModel = Copasi->pModel;
        configBuffer.getVariable("EndTime", "C_FLOAT64",
                                 & dbl,
                                 CReadConfig::LOOP);
        setValue("EndTime", dbl);
        configBuffer.getVariable("Points", "C_INT32",
                                 & uint);
        setValue("StepNumber", uint);
        mStepNumberSetLast = true;
        setValue("StartTime", (C_FLOAT64) 0.0);
        sync();
        mInitialState = mpModel->getInitialState();
      }*/
}

unsigned C_INT32 CScanProblem::getNumberOfScanItems() const
  {
    return mpScanItems->size();
  }

const CCopasiParameterGroup* CScanProblem::getScanItem(unsigned C_INT32 index) const
  {
    CCopasiParameter* tmp = mpScanItems->getParameter(index);
    if (tmp->getType() != CCopasiParameter::GROUP)
      {
        std::cout << "ERROR: not a parameter group!!!" << std::endl;
        return NULL;
      }
    return (CCopasiParameterGroup*)tmp;
  }

CCopasiParameterGroup* CScanProblem::getScanItem(unsigned C_INT32 index)
{
  CCopasiParameter* tmp = mpScanItems->getParameter(index);
  if (tmp->getType() != CCopasiParameter::GROUP)
    {
      std::cout << "ERROR: not a parameter group!!!" << std::endl;
      return NULL;
    }
  return (CCopasiParameterGroup*)tmp;
}

//CScanProblem::Type CScanProblem::getScanItemType(unsigned C_INT32 index);

CCopasiParameterGroup* CScanProblem::createScanItem(CScanProblem::Type type, unsigned C_INT32 steps, const CCopasiObject* obj)
{
  CCopasiParameterGroup* tmp;
  mpScanItems->addGroup("ScanItem");
  tmp = (CCopasiParameterGroup*)(mpScanItems->getParameter(getNumberOfScanItems() - 1));

  //create common parameters
  tmp->addParameter("Number of steps", CCopasiParameter::UINT, (unsigned C_INT32) steps);
  tmp->addParameter("Type", CCopasiParameter::UINT, (unsigned C_INT32) type);

  if (obj)
    tmp->addParameter("Object", CCopasiParameter::STRING, obj->getCN());
  else
    tmp->addParameter("Object", CCopasiParameter::STRING, std::string(""));

  //create specific parameters
  if ((type == SCAN_LINEAR))
    {
      tmp->addParameter("Minimum", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.0);
      tmp->addParameter("Maximum", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.0);
    }

  return tmp;
}

void CScanProblem::clearScanItems()
{
  mpScanItems->clear();
}

void CScanProblem::createDebugScan(CModel* model)
{
  if (model->getReactions().size() == 0) return;

  clearScanItems();
  setModel(model);

  CCopasiParameterGroup* tmp = createScanItem(SCAN_LINEAR, 5, model->getReactions()[0]->getParameters().getParameter(0));
  tmp->setValue("Minimum", 0.34);
  tmp->setValue("Maximum", 0.78);

  createScanItem(SCAN_REPEAT, 3);
}
