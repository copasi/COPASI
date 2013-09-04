// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CCopasiMethod class.
 *  This class is used to describe a task in COPASI. This class is
 *  intended to be used as the parent class for all methods whithin COPASI.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"

#include "CCopasiMethod.h"
#include "CCopasiMessage.h"
#include "CCopasiProblem.h"
#include "model/CModel.h"

const std::string CCopasiMethod::SubTypeName[] =
{
  "Not set",
  "Random Search",
  "Random Search (PVM)",
  "Simulated Annealing",
  "Corana Random Walk",
  "Differential Evolution",
  "Genetic Algorithm",
  "Evolutionary Programming",
  "Steepest Descent",
  "Hybrid GA/SA",
  "Genetic Algorithm SR",
  "Hooke & Jeeves",
  "Levenberg - Marquardt",
  "Nelder - Mead",
  "Evolution Strategy (SRES)",
  "Current Solution Statistics",
  "Particle Swarm",
  "Praxis",
  "Truncated Newton",
  "Enhanced Newton",
  "Deterministic (LSODA)",
  "Deterministic (LSODAR)",
  "Stochastic (Direct method)",
  "Stochastic (Gibson + Bruck)",
  "Stochastic (\xcf\x84-Leap)",
  "Stochastic (Adaptive SSA/\xcf\x84-Leap)",
  "Hybrid (Runge-Kutta)",
  "Hybrid (LSODA)",
  "Hybrid (ODE45)",
  "Hybrid (DSA-LSODAR)",
  "ILDM (LSODA,Deuflhard)",
  "ILDM (LSODA,Modified)",
  "CSP (LSODA)",
  "MCA Method (Reder)",
  "Scan Framework",
  "Wolf Method",
  "Sensitivities Method",
#ifdef COPASI_SSA
  "Stoichiometric Stability Analysis",
#endif // COPASI_SSA
  "EFM Algorithm",
  "Bit Pattern Tree Algorithm",
  "Bit Pattern Algorithm",
  "Householder Reduction",
  "Cross Section Finder",
  "Linear Noise Approximation",
  ""
};

const char * CCopasiMethod::XMLSubType[] =
{
  "NotSet",
  "RandomSearch",
  "RandomSearch(PVM)",
  "SimulatedAnnealing",
  "CoranaRandomWalk",
  "DifferentialEvolution",
  "GeneticAlgorithm",
  "EvolutionaryProgram",
  "SteepestDescent",
  "HybridGASA",
  "GeneticAlgorithmSR",
  "HookeJeeves",
  "LevenbergMarquardt",
  "NelderMead",
  "EvolutionaryStrategySR",
  "CurrentSolutionStatistics",
  "ParticleSwarm",
  "Praxis",
  "TruncatedNewton",
  "EnhancedNewton",
  "Deterministic(LSODA)",
  "Deterministic(LSODAR)",
  "Stochastic",
  "DirectMethod",
  "TauLeap",
  "AdaptiveSA",
  "Hybrid",
  "Hybrid (LSODA)",
  "Hybrid (DSA-ODE45"
  "Hybrid (DSA-LSODAR)",
  "TimeScaleSeparation(ILDM,Deuflhard)",
  "TimeScaleSeparation(ILDM,Modified)",
  "TimeScaleSeparation(CSP)",
  "MCAMethod(Reder)",
  "ScanFramework",
  "WolfMethod",
  "SensitivitiesMethod",
#ifdef COPASI_SSA
  "StoichiometricStabilityAnalysis",
#endif // COPASI_SSA
  "EFMAlgorithm",
  "EFMBitPatternTreeMethod",
  "EFMBitPatternMethod",
  "Householder",
  "crossSectionMethod",
  "LinearNoiseApproximation",
  NULL
};

CCopasiMethod::CCopasiMethod():
  CCopasiParameterGroup("NoName", NULL, "Method"),
  mType(CCopasiTask::unset),
  mSubType(unset),
  mpCallBack(NULL)
  //mpReport(NULL)
{setObjectName(SubTypeName[mType]);}

CCopasiMethod::CCopasiMethod(const CCopasiTask::Type & type,
                             const CCopasiMethod::SubType & subType,
                             const CCopasiContainer * pParent):
  CCopasiParameterGroup(CCopasiTask::TypeName[type], pParent, "Method"),
  mType(type),
  mSubType(subType),
  mpCallBack(NULL)
  //mpReport(NULL)
{setObjectName(SubTypeName[mSubType]);}

CCopasiMethod::CCopasiMethod(const CCopasiMethod & src,
                             const CCopasiContainer * pParent):
  CCopasiParameterGroup(src, pParent),
  mType(src.mType),
  mSubType(src.mSubType),
  mpCallBack(src.mpCallBack)
  //mpReport(src.mpReport)
{}

CCopasiMethod::~CCopasiMethod() {}

bool CCopasiMethod::setCallBack(CProcessReport * pCallBack)
{
  mpCallBack = pCallBack;
  return true;
}

const CCopasiTask::Type & CCopasiMethod::getType() const {return mType;}

// void CCopasiMethod::setType(const CCopasiTask::Type & type) {mType = type;}

const CCopasiMethod::SubType & CCopasiMethod::getSubType() const
{return mSubType;}

// void CCopasiMethod::setSubType(const CCopasiMethod::SubType & subType)
// {mSubType = subType;}

//virtual
bool CCopasiMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!pProblem)
    {
      //no problem
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCCopasiMethod + 2);
      return false;
    }

  if (! pProblem->getModel())
    {
      //no model
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCCopasiMethod + 3);
      return false;
    }

  if (pProblem->getModel()->getEvents().size())
    {
      if (mType == CCopasiTask::lyap)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCCopasiMethod + 4, "Lyapunov Exponents");
          return false;
        }

      if (mType == CCopasiTask::tssAnalysis)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCCopasiMethod + 4, "Time Scale Separation Analysis");
          return false;
        }

      if (mType == CCopasiTask::lna)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCCopasiMethod + 4, "Linear Noise Approximation");
          return false;
        }
    }

  return true;
}

void CCopasiMethod::load(CReadConfig & /* configBuffer */,
                         CReadConfig::Mode /* mode */)
{fatalError();}

void CCopasiMethod::print(std::ostream * ostream) const
{*ostream << *this;}

std::ostream &operator<<(std::ostream &os, const CCopasiMethod & o)
{
  os << "Method: " << o.getObjectName() << std::endl;

  CCopasiParameterGroup::parameterGroup::const_iterator it =
    o.CCopasiParameter::getValue().pGROUP->begin();
  CCopasiParameterGroup::parameterGroup::const_iterator end =
    o.CCopasiParameter::getValue().pGROUP->end();

  for (; it != end; ++it)
    {
      (*it)->print(&os);
      os << std::endl;
    }

  return os;
}

void CCopasiMethod::printResult(std::ostream * ostream) const
{*ostream << " Not implemented.";}
