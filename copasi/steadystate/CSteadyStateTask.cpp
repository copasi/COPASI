/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CSteadyStateTask.cpp,v $
   $Revision: 1.45 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/11 16:33:59 $
   End CVS Header */

/**
 * CSteadyStateTask class.
 *
 * This class implements a steady state task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting 
 * methods are done when initialized.
 *  
 * Created for Copasi by Stefan Hoops 2002
 */

#include "copasi.h"

#include "CSteadyStateTask.h"
#include "CSteadyStateProblem.h"
#include "CSteadyStateMethod.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "model/CMetabNameInterface.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#define XXXX_Reporting

CSteadyStateTask::CSteadyStateTask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::steadyState, pParent),
    mpSteadyState(NULL),
    mpSteadyStateX(NULL),
    mJacobian(),
    mJacobianX(),
    mEigenValues("Eigenvalues of Jacobian", this),
    mEigenValuesX("Eigenvalues of reduced system Jacobian", this)
{
  mpProblem = new CSteadyStateProblem(this);
  mpMethod =
    CSteadyStateMethod::createSteadyStateMethod(CCopasiMethod::Newton);
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);
  //((CSteadyStateMethod *) mpMethod)->setProblem((CSteadyStateProblem *) mpProblem);
}

CSteadyStateTask::CSteadyStateTask(const CSteadyStateTask & src,
                                   const CCopasiContainer * pParent):
    CCopasiTask(src, pParent),
    mpSteadyState(src.mpSteadyState),
    mpSteadyStateX(src.mpSteadyStateX),
    mJacobian(src.mJacobian),
    mJacobianX(src.mJacobianX),
    mEigenValues(src.mEigenValues, this),
    mEigenValuesX(src.mEigenValuesX, this)
{
  mpProblem =
    new CSteadyStateProblem(* (CSteadyStateProblem *) src.mpProblem, this);
  mpMethod =
    CSteadyStateMethod::createSteadyStateMethod(src.mpMethod->getSubType());
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);
  //((CSteadyStateMethod *) mpMethod)->setProblem((CSteadyStateProblem *) mpProblem);
}

CSteadyStateTask::~CSteadyStateTask()
{
  pdelete(mpSteadyState);
  pdelete(mpSteadyStateX);
}

void CSteadyStateTask::cleanup()
{}

void CSteadyStateTask::print(std::ostream * ostream) const {(*ostream) << (*this);}

void CSteadyStateTask::load(CReadConfig & configBuffer)
{
  configBuffer.getVariable("SteadyState", "bool", &mScheduled,
                           CReadConfig::LOOP);

  ((CSteadyStateProblem *) mpProblem)->load(configBuffer);

  ((CSteadyStateMethod *) mpMethod)->load(configBuffer);
}

//CState * CSteadyStateTask::getState()
//{return mpSteadyState;}

const CState * CSteadyStateTask::getState() const
  {return mpSteadyState;}

const CMatrix< C_FLOAT64 > & CSteadyStateTask::getJacobian() const
  {return mJacobian;}
const CMatrix< C_FLOAT64 > & CSteadyStateTask::getJacobianReduced() const
  {return mJacobianX;}

const CEigen & CSteadyStateTask::getEigenValues() const
  {
    return mEigenValues;
  }
const CEigen & CSteadyStateTask::getEigenValuesReduced() const
  {
    return mEigenValuesX;
  }

bool CSteadyStateTask::initialize(std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  CSteadyStateProblem* pProblem =
    dynamic_cast<CSteadyStateProblem *>(mpProblem);
  assert(pProblem);

  bool success = true;

  if (!mReport.open(pOstream)) success = false;
  if (!mReport.compile()) success = false;

  if (!pProblem->getModel()->compileIfNecessary()) success = false;
  pProblem->setInitialState(pProblem->getModel()->getInitialState());

  //init states
  pdelete(mpSteadyState);
  mpSteadyState = new CState(pProblem->getModel()->getInitialState());
  pdelete(mpSteadyStateX);
  mpSteadyStateX = new CStateX(pProblem->getModel()->getInitialStateX());

  mCalculateReducedSystem = (pProblem->getModel()->getNumDependentMetabs() != 0);

  //init jacobians
  mJacobian.resize(mpSteadyState->getVariableNumberSize(),
                   mpSteadyState->getVariableNumberSize());
  mJacobianX.resize(mpSteadyStateX->getVariableNumberSize(),
                    mpSteadyStateX->getVariableNumberSize());

  return success;
}

bool CSteadyStateTask::process()
{
  assert(/*mpProblem && */mpMethod);
  mpMethod->isValidProblem(mpProblem);

  CSteadyStateProblem* pProblem =
    dynamic_cast<CSteadyStateProblem *>(mpProblem);
  assert(pProblem);

  CSteadyStateMethod* pMethod =
    dynamic_cast<CSteadyStateMethod *>(mpMethod);
  assert(pMethod);

  mReport.printHeader();

  mResult = pMethod->process(mpSteadyState,
                             mpSteadyStateX,
                             pProblem,
                             mJacobian,
                             mJacobianX,
                             mEigenValues,
                             mEigenValuesX,
                             mpProgressHandler);

  mReport.printBody();
  mReport.printFooter();

  return (mResult != CSteadyStateMethod::notFound);
}

bool CSteadyStateTask::processForScan(bool useInitialConditions, bool doOutput)
{
  assert(/*mpProblem && */mpMethod);
  mpMethod->isValidProblem(mpProblem);

  CSteadyStateProblem* pProblem =
    dynamic_cast<CSteadyStateProblem *>(mpProblem);
  assert(pProblem);

  CSteadyStateMethod* pMethod =
    dynamic_cast<CSteadyStateMethod *>(mpMethod);
  assert(pMethod);

  CState store;
  if (!useInitialConditions)
    {
      store = pProblem->getInitialState();
      pProblem->setInitialState(pProblem->getModel()->getState());
    }

  mResult = pMethod->process(mpSteadyState,
                             mpSteadyStateX,
                             pProblem,
                             mJacobian,
                             mJacobianX,
                             mEigenValues,
                             mEigenValuesX,
                             mpProgressHandler);

  if (!useInitialConditions) pProblem->setInitialState(store);

  return (mResult != CSteadyStateMethod::notFound);
}

std::ostream &operator<<(std::ostream &os, const CSteadyStateTask &A)
{
  switch (A.getResult())
    {
    case CSteadyStateMethod::found:
      os << "A steady state with given resolution was found." << std::endl;
      break;

    case CSteadyStateMethod::notFound:
      os << "No steady state with given resolution was found!" << std::endl;
      os << "(below are the last unsuccessful trial values)" << std::endl;
      break;

    case CSteadyStateMethod::foundEquilibrium:
      os << "An equilibrium steady state (zero fluxes) was found." << std::endl;
      break;

    case CSteadyStateMethod::foundNegative:
      os << "An invalid steady state (negative concentrations) was found." << std::endl;
    }

  os << std::endl;

  // Update all necessary values.
  const CState * pState = A.getState();
  CModel * pModel = const_cast<CModel *>(pState->getModel());

  pModel->setState(pState);
  pModel->updateRates();

  // Metabolite Info: Name, Concentration, Concentration Rate, Particle Number, Particle Rate, Transition Time
  const CCopasiVector<CMetab> & Metabolites = pModel->getMetabolites();
  const CMetab * pMetab;

  unsigned C_INT32 i, imax = Metabolites.size();

  os << "Metabolite" << "\t";
  os << "Concentration (" << pModel->getQuantityUnit() << "/" << pModel->getVolumeUnit() << ")" << "\t";
  os << "Concentration Rate (" << pModel->getQuantityUnit() << "/(" << pModel->getVolumeUnit() << "*" << pModel->getTimeUnit() << "))" << "\t";
  os << "Particle Number" << "\t";
  os << "Particle Number Rate (1/" << pModel->getTimeUnit() << ")" << "\t";
  os << "Transition Time (" << pModel->getTimeUnit() << ")" << std::endl;

  for (i = 0; i < imax; ++i)
    {
      pMetab = Metabolites[i];
      os << CMetabNameInterface::getDisplayName(pModel, *pMetab) << "\t";
      os << pMetab->getConcentration() << "\t";
      os << pMetab->getConcentrationRate() << "\t";
      os << pMetab->getNumber() << "\t";
      os << pMetab->getNumberRate() << "\t";
      os << pMetab->getTransitionTime() << std::endl;
    }
  os << std::endl;

  // Reaction Info: Name, Flux, Particle Flux
  const CCopasiVector<CReaction>& Reactions = pModel->getReactions();
  const CReaction * pReaction;

  imax = Reactions.size();

  os << "Reaction" << "\t";
  os << "Flux (" << pModel->getQuantityUnit() << "/" << pModel->getTimeUnit() << ")" << "\t";
  os << "Particle Flux (1/" << pModel->getTimeUnit() << ")" << std::endl;

  for (i = 0; i < imax; ++i)
    {
      pReaction = Reactions[i];
      os << pReaction->getObjectName() << "\t";
      os << pReaction->getFlux() << "\t";
      os << pReaction->getParticleFlux() << std::endl;
    }
  os << std::endl;

  // if Jacobian Requested
  //    Jacobian
  //    Jacobian Reduced System
  if (static_cast<CSteadyStateProblem *>(A.mpProblem)->isJacobianRequested())
    {
      os << "Jacobian of the Complete System" << std::endl;
      os << A.mJacobian << std::endl;
      if (static_cast<CSteadyStateProblem *>(A.mpProblem)->isStabilityAnalysisRequested())
        {
          os << "Eigenvalues\treal\timaginary" << std::endl;
          imax = A.mEigenValues.getR().size();
          for (i = 0; i < imax; i++)
            os << "\t" << A.mEigenValues.getR()[i] << "\t" << A.mEigenValues.getI()[i] << std::endl;
          os << std::endl;
        }

      os << "Jacobian of the Reduced System" << std::endl;
      os << A.mJacobianX << std::endl;
      if (static_cast<CSteadyStateProblem *>(A.mpProblem)->isStabilityAnalysisRequested())
        {
          os << "Eigenvalues\treal\timaginary" << std::endl;
          imax = A.mEigenValuesX.getR().size();
          for (i = 0; i < imax; i++)
            os << "\t" << A.mEigenValuesX.getR()[i] << "\t" << A.mEigenValuesX.getI()[i] << std::endl;
          os << std::endl;
        }
    }
  // if Stability Analysis Requested
  //    Stability Analysis Reduced System

  if (static_cast<CSteadyStateProblem *>(A.mpProblem)->isStabilityAnalysisRequested())
    {
      os << "Stability Analysis of the Reduced System" << std::endl;
      os << A.mEigenValuesX << std::endl;
    }

  return os;
}
