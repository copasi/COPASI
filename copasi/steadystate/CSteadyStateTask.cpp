// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CSteadyStateTask.cpp,v $
//   $Revision: 1.72 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/09/05 19:56:01 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
    mJacobian(),
    mJacobianX(),
    mpJacobianAnn(NULL),
    mpJacobianXAnn(NULL),
    mEigenValues("Eigenvalues of Jacobian", this),
    mEigenValuesX("Eigenvalues of reduced system Jacobian", this)
{
  mpProblem = new CSteadyStateProblem(this);
  mpMethod =
    CSteadyStateMethod::createSteadyStateMethod(CCopasiMethod::Newton);
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);
  //((CSteadyStateMethod *) mpMethod)->setProblem((CSteadyStateProblem *) mpProblem);
  initObjects();
}

CSteadyStateTask::CSteadyStateTask(const CSteadyStateTask & src,
                                   const CCopasiContainer * pParent):
    CCopasiTask(src, pParent),
    mpSteadyState(src.mpSteadyState),
    mJacobian(src.mJacobian),
    mJacobianX(src.mJacobianX),
    mpJacobianAnn(NULL),
    mpJacobianXAnn(NULL),
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
  initObjects();
}

CSteadyStateTask::~CSteadyStateTask()
{
  pdelete(mpSteadyState);
}

void CSteadyStateTask::cleanup()
{}

void CSteadyStateTask::initObjects()
{
  mpJacobianAnn = new CArrayAnnotation("Jacobian (complete system)", this,
                                       new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mJacobian), true);
  mpJacobianAnn->setMode(CArrayAnnotation::OBJECTS);
  mpJacobianAnn->setDescription("");
  mpJacobianAnn->setDimensionDescription(0, "Variables of the system, including dependent species");
  mpJacobianAnn->setDimensionDescription(1, "Variables of the system, including dependent species");

  mpJacobianXAnn = new CArrayAnnotation("Jacobian (reduced system)", this,
                                        new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mJacobianX), true);
  mpJacobianXAnn->setMode(CArrayAnnotation::OBJECTS);
  mpJacobianXAnn->setDescription("");
  mpJacobianXAnn->setDimensionDescription(0, "Independent variables of the system");
  mpJacobianXAnn->setDimensionDescription(1, "Independent variables of the system");
}

void CSteadyStateTask::print(std::ostream * ostream) const {(*ostream) << (*this);}

void CSteadyStateTask::load(CReadConfig & configBuffer)
{
  configBuffer.getVariable("SteadyState", "bool", &mScheduled,
                           CReadConfig::LOOP);

  ((CSteadyStateProblem *) mpProblem)->load(configBuffer);

  ((CSteadyStateMethod *) mpMethod)->load(configBuffer);
}

const CState * CSteadyStateTask::getState() const
  {return mpSteadyState;}

const CMatrix< C_FLOAT64 > & CSteadyStateTask::getJacobian() const
  {return mJacobian;}
const CMatrix< C_FLOAT64 > & CSteadyStateTask::getJacobianReduced() const
  {return mJacobianX;}

const CArrayAnnotation * CSteadyStateTask::getJacobianAnnotated() const
  {
    return mpJacobianAnn;
  }

const CArrayAnnotation * CSteadyStateTask::getJacobianXAnnotated() const
  {
    return mpJacobianXAnn;
  }

const CEigen & CSteadyStateTask::getEigenValues() const
  {
    return mEigenValues;
  }
const CEigen & CSteadyStateTask::getEigenValuesReduced() const
  {
    return mEigenValuesX;
  }

bool CSteadyStateTask::initialize(const OutputFlag & of,
                                  COutputHandler * pOutputHandler,
                                  std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  if (!mpMethod->isValidProblem(mpProblem)) return false;

  bool success = true;

  success &= CCopasiTask::initialize(of, pOutputHandler, pOstream);

  //init states
  if (!mpProblem->getModel()) return false;

  pdelete(mpSteadyState);
  mpSteadyState = new CState(mpProblem->getModel()->getInitialState());

  mCalculateReducedSystem = (mpProblem->getModel()->getNumDependentReactionMetabs() != 0);

  //init jacobians
  unsigned C_INT32 sizeX = mpSteadyState->getNumIndependent();
  mJacobianX.resize(sizeX, sizeX);
  unsigned C_INT32 size = sizeX + mpSteadyState->getNumDependent();
  mJacobian.resize(size, size);

  //jacobian annotations
  CStateTemplate & StateTemplate = mpProblem->getModel()->getStateTemplate();

  mpJacobianAnn->resize();
  CModelEntity **ppEntities = StateTemplate.getEntities();
  const unsigned C_INT32 * pUserOrder = StateTemplate.getUserOrder().array();
  const unsigned C_INT32 * pUserOrderEnd = pUserOrder + StateTemplate.getUserOrder().size();

  pUserOrder++; // We skip the time which is the first.

  unsigned C_INT32 i, imax = size;
  for (i = 0; i < imax && pUserOrder != pUserOrderEnd; pUserOrder++)
    {
      const CModelEntity::Status & Status = ppEntities[*pUserOrder]->getStatus();
      if (Status == CModelEntity::ODE ||
          (Status == CModelEntity::REACTIONS && ppEntities[*pUserOrder]->isUsed()))
        {
          mpJacobianAnn->setAnnotationCN(0 , i, ppEntities[*pUserOrder]->getCN());
          mpJacobianAnn->setAnnotationCN(1 , i, ppEntities[*pUserOrder]->getCN());

          i++;
        }
    }

  mpJacobianXAnn->resize();

  ppEntities = StateTemplate.beginIndependent();
  imax = sizeX;
  for (i = 0; i < imax; ++i, ++ppEntities)
    {
      mpJacobianXAnn->setAnnotationCN(0 , i, (*ppEntities)->getCN());
      mpJacobianXAnn->setAnnotationCN(1 , i, (*ppEntities)->getCN());
    }

  CSteadyStateProblem* pProblem =
    dynamic_cast<CSteadyStateProblem *>(mpProblem);
  assert(pProblem);

  success &= pProblem->initialize();

  CSteadyStateMethod* pMethod =
    dynamic_cast<CSteadyStateMethod *>(mpMethod);
  assert(pMethod);

  success &= pMethod->initialize(pProblem);

  return success;
}

bool CSteadyStateTask::process(const bool & useInitialValues)
{
  if (useInitialValues)
    {
      mpProblem->getModel()->applyInitialValues();
    }

  *mpSteadyState = mpProblem->getModel()->getState();

  // A steady-state makes only sense in an autonomous model,
  // i.e., the time of the steady-state must not be changed
  // during simulation.
  C_FLOAT64 InitialTime = mpSteadyState->getTime();

  CSteadyStateMethod* pMethod =
    dynamic_cast<CSteadyStateMethod *>(mpMethod);
  assert(pMethod);

  CSteadyStateProblem* pProblem =
    dynamic_cast<CSteadyStateProblem *>(mpProblem);
  assert(pMethod);

  output(COutputInterface::BEFORE);

  //call the method
  mResult = pMethod->process(mpSteadyState,
                             mJacobianX,
                             mpCallBack);

  //debug
  //std::cout << pMethod->getMethodLog() << std::endl;

  if (mResult == CSteadyStateMethod::notFound)
    restore();

  //update jacobian
  if (pProblem->isJacobianRequested() ||
      pProblem->isStabilityAnalysisRequested())
    {
      pMethod->doJacobian(mJacobian, mJacobianX);
    }

  //mpProblem->getModel()->setState(mpSteadyState);
  //mpProblem->getModel()->updateRates();

  //calculate eigenvalues
  if (pProblem->isStabilityAnalysisRequested())
    {
      mEigenValues.calcEigenValues(mJacobian);
      mEigenValuesX.calcEigenValues(mJacobianX);

      mEigenValues.stabilityAnalysis(pMethod->getStabilityResolution());
      mEigenValuesX.stabilityAnalysis(pMethod->getStabilityResolution());
    }

  // Reset the time.
  mpSteadyState->setTime(InitialTime);

  output(COutputInterface::AFTER);

  return (mResult != CSteadyStateMethod::notFound);
}

bool CSteadyStateTask::restore()
{
  bool success = CCopasiTask::restore();

  if (mUpdateModel)
    {
      CModel * pModel = mpProblem->getModel();

      pModel->setState(*mpSteadyState);
      pModel->updateSimulatedValues(true);
      pModel->setInitialState(pModel->getState());
      pModel->updateInitialValues();
    }

  return success;
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
  CState * pState = const_cast<CState *>(A.getState());
  if (!pState) return os;
  CModel * pModel = A.mpProblem->getModel();
  if (!pModel) return os;

  pModel->setState(*pState);
  pModel->updateSimulatedValues(true);
  pModel->updateNonSimulatedValues();

  // Metabolite Info: Name, Concentration, Concentration Rate, Particle Number, Particle Rate, Transition Time
  const CCopasiVector<CMetab> & Metabolites = pModel->getMetabolites();
  const CMetab * pMetab;

  unsigned C_INT32 i, imax = Metabolites.size();

  os << "Species" << "\t";
  os << "Concentration (" << pModel->getConcentrationUnitName() << ")" << "\t";
  os << "Concentration Rate (" << pModel->getConcentrationRateUnitName() << ")" << "\t";
  os << "Particle Number" << "\t";
  os << "Particle Number Rate (1/" << pModel->getTimeUnitName() << ")" << "\t";
  os << "Transition Time (" << pModel->getTimeUnitName() << ")" << std::endl;

  for (i = 0; i < imax; ++i)
    {
      pMetab = Metabolites[i];
      os << CMetabNameInterface::getDisplayName(pModel, *pMetab) << "\t";
      os << pMetab->getConcentration() << "\t";
      os << pMetab->getConcentrationRate() << "\t";
      os << pMetab->getValue() << "\t";
      os << pMetab->getRate() << "\t";
      os << pMetab->getTransitionTime() << std::endl;
    }
  os << std::endl;

  // Reaction Info: Name, Flux, Particle Flux
  const CCopasiVector<CReaction>& Reactions = pModel->getReactions();
  const CReaction * pReaction;

  imax = Reactions.size();

  os << "Reaction" << "\t";
  os << "Flux (" << pModel->getQuantityRateUnitName() << ")" << "\t";
  os << "Particle Flux (1/" << pModel->getTimeUnitName() << ")" << std::endl;

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
      //os << "Jacobian of the Complete System" << std::endl;
      //os << A.mJacobian << std::endl;
      os << *A.mpJacobianAnn << std::endl;
      if (static_cast<CSteadyStateProblem *>(A.mpProblem)->isStabilityAnalysisRequested())
        {
          os << "Eigenvalues\treal\timaginary" << std::endl;
          imax = A.mEigenValues.getR().size();
          for (i = 0; i < imax; i++)
            os << "\t" << A.mEigenValues.getR()[i] << "\t" << A.mEigenValues.getI()[i] << std::endl;
          os << std::endl;
        }

      //os << "Jacobian of the Reduced System" << std::endl;
      //os << A.mJacobianX << std::endl;
      os << *A.mpJacobianXAnn << std::endl;
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
