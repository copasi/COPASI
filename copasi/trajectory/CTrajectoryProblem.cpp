/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryProblem.cpp,v $
   $Revision: 1.29 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/04/25 11:23:47 $
   End CVS Header */

/**
 *  CTrajectoryProblem class.
 *  This class describes the trajectory problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#include <math.h>
#include <string>

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CTrajectoryProblem.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "CopasiDataModel/CCopasiDataModel.h"

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CTrajectoryProblem::CTrajectoryProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::timeCourse, pParent),
    mStepNumberSetLast(true),
    mInitialState()
    //mEndState()
{
  addParameter("StepNumber", CCopasiParameter::UINT, (unsigned C_INT32) 100);
  addParameter("StepSize", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.01);
  addParameter("StartTime", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.0);
  addParameter("EndTime", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.0);
  addParameter("TimeSeriesRequested", CCopasiParameter::BOOL, (bool) true);
  addParameter("OutputStartTime", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.0);

  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CTrajectoryProblem &" src
 */
CTrajectoryProblem::CTrajectoryProblem(const CTrajectoryProblem & src,
                                       const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    mStepNumberSetLast(src.mStepNumberSetLast),
    mInitialState(src.mInitialState)
    //mEndState(src.mEndState)
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Destructor.
 */
CTrajectoryProblem::~CTrajectoryProblem()
{DESTRUCTOR_TRACE;}

void CTrajectoryProblem::initObjects()
{
  const_cast<CCopasiObject *>(getParameter("StepNumber")
                              ->getObject(CCopasiObjectName("Reference=Value")))
  ->setUpdateMethod(this,
                    (bool (CTrajectoryProblem::*)(const C_INT32 &)) &CTrajectoryProblem::setStepNumber);
  const_cast<CCopasiObject *>(getParameter("StepSize")
                              ->getObject(CCopasiObjectName("Reference=Value")))
  ->setUpdateMethod(this, &CTrajectoryProblem::setStepSize);
  const_cast<CCopasiObject *>(getParameter("StartTime")
                              ->getObject(CCopasiObjectName("Reference=Value")))
  ->setUpdateMethod(this, &CTrajectoryProblem::setStartTime);
  const_cast<CCopasiObject *>(getParameter("EndTime")
                              ->getObject(CCopasiObjectName("Reference=Value")))
  ->setUpdateMethod(this, &CTrajectoryProblem::setEndTime);
}

/**
 * Set the model the problem is dealing with.
 * @param "CModel *" pModel
 */
bool CTrajectoryProblem::setModel(CModel * pModel)
{
  mpModel = pModel;
  mInitialState.setModel(mpModel);
  //mEndState.setModel(mpModel);

  return true;
}

/**
 * Set the number of time steps the trajectory method should integrate.
 * @param "const unsigned C_INT32 &" stepNumber
 */
bool CTrajectoryProblem::setStepNumber(const unsigned C_INT32 & stepNumber)
{
  setValue("StepNumber", stepNumber);
  mStepNumberSetLast = true;
  return sync();
}

/**
 * Retrieve the number of time steps the trajectory method should integrate.
 * @return "const unsigned C_INT32 &" stepNumber
 */
const unsigned C_INT32 & CTrajectoryProblem::getStepNumber() const
  {return * (unsigned C_INT32 *) getValue("StepNumber");}

/**
 * Set the size a integration step the trajectory method should do.
 * @param "const C_FLOAT64 &" stepSize
 */
bool CTrajectoryProblem::setStepSize(const C_FLOAT64 & stepSize)
{
  setValue("StepSize", stepSize);
  mStepNumberSetLast = false;
  return sync();
}

/**
 * Retrieve the size a integration step the trajectory method should do.
 * @return "const C_FLOAT64 &" stepSize
 */
const C_FLOAT64 & CTrajectoryProblem::getStepSize() const
  {return * (C_FLOAT64 *) getValue("StepSize");}

/**
 * Set the start time.
 * @param "const C_FLOAT64 &" startTime
 */
bool CTrajectoryProblem::setStartTime(const C_FLOAT64 & startTime)
{
  setValue("StartTime", startTime);
  mInitialState.setTime(startTime);

  return sync();
}

/**
 * Retrieve the start time.
 * @return "const C_FLOAT64 &" startTime
 */
const C_FLOAT64 & CTrajectoryProblem::getStartTime() const
  {return * (C_FLOAT64 *) getValue("StartTime");}

/**
 * Set the end time.
 * @param "const C_FLOAT64 &" endTime
 * @parem bool success
 */
bool CTrajectoryProblem::setEndTime(const C_FLOAT64 & endTime)
{
  setValue("EndTime", endTime);
  return sync();
}

/**
 * Retrieve the end time.
 * @return "const C_FLOAT64 &" endTime
 */
const C_FLOAT64 & CTrajectoryProblem::getEndTime() const
  {return * (C_FLOAT64 *) getValue("EndTime");}

void CTrajectoryProblem::setOutputStartTime(const C_FLOAT64 & startTime)
{
  setValue("OutputStartTime", startTime);
}

const C_FLOAT64 & CTrajectoryProblem::getOutputStartTime() const
  {return * (C_FLOAT64 *) getValue("OutputStartTime");}

void CTrajectoryProblem::setTimeSeriesRequested(bool flag)
{
  setValue("TimeSeriesRequested", flag);
}

bool CTrajectoryProblem::timeSeriesRequested() const
  {return * (bool *) getValue("TimeSeriesRequested");}

/**
 * Set the initial state of the problem.
 * @param "const CState &" initialState
 */
void CTrajectoryProblem::setInitialState(const CState & initialState)
{
  mInitialState = initialState;
  mInitialState.setTime(getStartTime());
  //setStartTime(mInitialState.getTime());
  mpModel = const_cast<CModel*>(mInitialState.getModel());
}

/**
 * Set the initial state of the problem.
 * @param "const CStateX &" initialState
 */
void CTrajectoryProblem::setInitialState(const CStateX & initialState)
{
  mInitialState = initialState;
  mInitialState.setTime(getStartTime());
  //setStartTime(mInitialState.getTime());
  mpModel = const_cast<CModel*>(mInitialState.getModel());
}

/**
 * Retrieve the initial state of the problem.
 * @return "const CState *" pInitialState
 */
const CState & CTrajectoryProblem::getInitialState() const
  {return mInitialState;}

/**
 * Set the end state of the problem.
 * @param "const CState *" pEndState
 */ 
//void CTrajectoryProblem::setEndState(const CState * pEndState)
//{mEndState = *pEndState;}

/**
 * Set the end state of the problem.
 * @param "const CStateX *" pEndState
 */ 
//void CTrajectoryProblem::setEndState(const CStateX * pEndState)
//{mEndState = *pEndState;}

/**
 * Retrieve the end state of the problem.
 * @return "const CState &" pEndState
 */ 
//const CState & CTrajectoryProblem::getEndState() const
//  {return mEndState;}

/**
 * Load a trajectory problem
 * @param "CReadConfig &" configBuffer
 */
void CTrajectoryProblem::load(CReadConfig & configBuffer,
                              CReadConfig::Mode C_UNUSED(mode))
{
  C_FLOAT64 dbl;
  unsigned C_INT32 uint;

  if (configBuffer.getVersion() < "4.0")
    {
      mpModel = CCopasiDataModel::Global->getModel();
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
    }
}

/**
 * This function synchronizes step size and number
 */
bool CTrajectoryProblem::sync()
{
  C_FLOAT64 Tmp = getEndTime() - getStartTime();

  if (mStepNumberSetLast)
    setValue("StepSize", Tmp / (C_FLOAT64) getStepNumber());
  else
    {
      /* Assure that the step size has the appropriate sign. */
      setValue("StepSize", (Tmp < 0.0) ? - fabs(getStepSize()) : fabs(getStepSize()));

      setValue("StepNumber", (unsigned C_INT32) ceil(Tmp / getStepSize()));
    }

  return true;
}

//virtual
std::vector<CDefaultPlotDescription> CTrajectoryProblem::getListOfDefaultPlotDescriptions() const
  {
    std::vector<CDefaultPlotDescription> ret;
    if (!mpModel) return ret;
    CDefaultPlotDescription tmp;

    //concentrations plot
    tmp.id = 0;
    tmp.name = "Concentrations plot";
    tmp.description = "A plot of the variable metabolite concentrations vs. time.\nIt does not contain the concentrations of fixed metabolites.";
    tmp.isPlot = true;
    ret.push_back(tmp);

    //particle numbers plot
    tmp.id = 1;
    tmp.name = "Particle numbers plot";
    tmp.description = "A plot of the variable metabolite particle numbers vs. time.\nIt does not contain the particle numbers of fixed metabolites.";
    tmp.isPlot = true;
    ret.push_back(tmp);

    //offer some plots only if there are fixed metabs
    bool fixedMetab = false;
    const CCopasiVector< CMetab > & metabs = mpModel->getMetabolites();
    C_INT32 i, imax = metabs.size();
    for (i = 0; i < imax; ++i)
      if (metabs[i]->getStatus() == CMetab::METAB_FIXED)
      {fixedMetab = true; break;}

    if (fixedMetab)
      {
        //complete concentrations plot
        tmp.id = 2;
        tmp.name = "Complete concentrations plot";
        tmp.description = "A plot of all the metabolite concentrations vs. time (including fixed metabolites).";
        tmp.isPlot = true;
        ret.push_back(tmp);

        //complete particle numbers plot
        tmp.id = 3;
        tmp.name = "Complete particle numbers plot";
        tmp.description = "A plot of all the metabolite particle numbers vs. time (including fixed metabolites).";
        tmp.isPlot = true;
        ret.push_back(tmp);
      }

    //empty plot
    tmp.id = 99;
    tmp.name = "Empty plot";
    tmp.description = "A plot with nothing in it.";
    tmp.isPlot = true;
    ret.push_back(tmp);

    return ret;
  }

#include "plot/COutputDefinitionVector.h" 
//#include "plot/CPlotItem.h"

//virtual
bool CTrajectoryProblem::createDefaultPlot(C_INT32 id) const
  {
    //std::cout << id << std::endl;
    if (!mpModel) return false;

    std::string bname;
    switch (id)
      {
      case 0:
        bname = "Concentrations plot";
        break;
      case 1:
        bname = "Particle numbers plot";
        break;
      case 2:
        bname = "Complete concentrations plot";
        break;
      case 3:
        bname = "Complete particle numbers plot";
        break;
      case 99:
        bname = "Empty plot";
        break;
      default:
        return false;
      }

    //TODO this part of this method is propably the  same for all problems. Could be moved elsewhere
    unsigned C_INT32 i = 0;
    CPlotSpecification* pPl;
    std::ostringstream nname;
    nname << bname;
    while (!(pPl = CCopasiDataModel::Global->getPlotDefinitionList()->createPlotSpec(nname.str(), CPlotItem::plot2d)))
      {
        i++;
        nname.str("");
        nname << bname << "_" << i;
      }

    //empty plot
    if (id == 99) return true;

    //id 0,1,2,3
    CPlotItem * plItem;
    std::string itemTitle;
    CPlotDataChannelSpec name2;
    const CCopasiObject * tmp;

    CPlotDataChannelSpec name1 = mpModel->getObject(CCopasiObjectName("Reference=Time"))->getCN();

    bool allMetabs = (id == 2) || (id == 3);

    unsigned C_INT32 imax = mpModel->getMetabolites().size();
    for (i = 0; i < imax; ++i)
      {
        if ((mpModel->getMetabolites()[i]->getStatus() != CMetab::METAB_FIXED) || allMetabs)
          {
            if ((id == 0) || (id == 2))
              tmp = mpModel->getMetabolites()[i]->getObject(CCopasiObjectName("Reference=Concentration"));
            else
              tmp = mpModel->getMetabolites()[i]->getObject(CCopasiObjectName("Reference=ParticleNumber"));

            name2 = tmp->getCN();
            itemTitle = tmp->getObjectDisplayName();
            //std::cout << itemTitle << " : " << name2 << std::endl;

            plItem = pPl->createItem(itemTitle, CPlotItem::curve2d);
            plItem->addChannel(name1);
            plItem->addChannel(name2);
          }
      }
    return true;
  }
