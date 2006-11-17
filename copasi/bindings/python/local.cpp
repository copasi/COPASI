/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/local.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/11/17 20:49:21 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "utilities/CCopasiMethod.h"
#include "utilities/CCopasiProblem.h"
#include "utilities/CCopasiTask.h"
#include "function/CEvaluationTree.h"
#include "function/CFunction.h"

#include <iostream>

/**
 * @return the most specific Swig type for the given Task object.
 */
struct swig_type_info*
      GetDowncastSwigTypeForTask (CCopasiTask* task)
  {
    if (task == NULL) return SWIGTYPE_p_CCopasiTask;

    struct swig_type_info* pInfo = SWIGTYPE_p_CCopasiTask;
    switch (task->getType())
      {
        /*
              case CCopasiTask::steadyState:
                pInfo=SWIGTYPE_p_CSteadyStateTask;
                break;
        */
      case CCopasiTask::timeCourse:
        pInfo = SWIGTYPE_p_CTrajectoryTask;
        break;
        /*
              case CCopasiTask::scan:
                pInfo=SWIGTYPE_p_CScanTask;
                break;
              case CCopasiTask::fluxMode:
                pInfo=SWIGTYPE_p_CEFMTask;
                break;
              case CCopasiTask::optimization:
                pInfo=SWIGTYPE_p_COptTask;
                break;
              case CCopasiTask::parameterFitting:
                pInfo=SWIGTYPE_p_CFitTask;
                break;
              case CCopasiTask::mca:
                pInfo=SWIGTYPE_p_CMCATask;
                break;
              case CCopasiTask::lyap:
                pInfo=SWIGTYPE_p_CLyapTask;
                break;
#ifdef COPASI_DEBUG
              case CCopasiTask::tss:
                pInfo=SWIGTYPE_p_CTSSTask;
                break;
              case CCopasiTask::sens:
                pInfo=SWIGTYPE_p_CSensTask;
                break;
#endif // COPASI_DEBUG
#ifdef COPASI_SSA
              case CCopasiTask::ssa:
                pInfo=SWIGTYPE_p_CSSATask;
                break;
#endif // COPASI_SSA
        */
      default:
        break;
      }
    return pInfo;
  }

/**
 * @return the most specific Swig type for the given Method object.
 */
struct swig_type_info*
      GetDowncastSwigTypeForMethod (CCopasiMethod* method)
  {
    if (method == NULL) return SWIGTYPE_p_CCopasiMethod;

    struct swig_type_info* pInfo = SWIGTYPE_p_CCopasiMethod;
    switch (method->getSubType())
      {
        /*
              case CCopasiMethod::RandomSearch:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::RandomSearchMaster:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::SimulatedAnnealing:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::GeneticAlgorithm:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::EvolutionaryProgram:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::SteepestDescent:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::HybridGASA:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::GeneticAlgorithmSR:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::HookeJeeves:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::LevenbergMarquart:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::NelderMead:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::SRES:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::Statistics:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::ParicleSwarm:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::Newton:
                pInfo=SWIGTYPE_p_;
                break;
        */
      case CCopasiMethod::deterministic:
        pInfo = SWIGTYPE_p_CTrajectoryMethod;
        //pInfo=SWIGTYPE_p_CLsodaMethod;
        break;
      case CCopasiMethod::LSODAR:
        pInfo = SWIGTYPE_p_CTrajectoryMethod;
        //pInfo=SWIGTYPE_p_CLsodarMethod;
        break;
      case CCopasiMethod::stochastic:
        pInfo = SWIGTYPE_p_CTrajectoryMethod;
        //pInfo=SWIGTYPE_p_CStochMethod;
        break;
      case CCopasiMethod::hybrid:
        pInfo = SWIGTYPE_p_CTrajectoryMethod;
        //pInfo=SWIGTYPE_p_CHybridMethod;
        break;
      case CCopasiMethod::hybridLSODA:
        pInfo = SWIGTYPE_p_CTrajectoryMethod;
        //pInfo=SWIGTYPE_p_CHybridMethodLSODA;
        break;
      case CCopasiMethod::tauLeap:
        pInfo = SWIGTYPE_p_CTrajectoryMethod;
        //pInfo=SWIGTYPE_p_CTauLeapMethod;
        break;
        /*
              case CCopasiMethod::mcaMethodReder:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::scanMethod:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::lyapWolf:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::tssMethod:
                pInfo=SWIGTYPE_p_;
                break;
              case CCopasiMethod::sensMethod:
                pInfo=SWIGTYPE_p_;
                break;
#ifdef COPASI_SSA
              case CCopasiMethod::ssaMethod:
                pInfo=SWIGTYPE_p_;
                break;
#endif // COPASI_SSA
#ifdef COPASI_EXTREMECURRENTS
              case CCopasiMethod::extremeCurrents:
                pInfo=SWIGTYPE_p_;
                break;
#endif // COPASI_EXTREMECURRENTS
              case CCopasiMethod::EFMAlgorithm:
                pInfo=SWIGTYPE_p_;
                break;
        */
      default:
        break;
      }
    return pInfo;
  }

/**
 * @return the most specific Swig type for the given Problem object.
 */
struct swig_type_info*
      GetDowncastSwigTypeForProblem (CCopasiProblem* problem)
  {
    if (problem == NULL) return SWIGTYPE_p_CCopasiProblem;

    struct swig_type_info* pInfo = SWIGTYPE_p_CCopasiProblem;
    switch (problem->getType())
      {
        /*
              case CCopasiTask::steadyState:
                pInfo=SWIGTYPE_p_CSteadyStateTask;
                break;
        */
      case CCopasiTask::timeCourse:
        pInfo = SWIGTYPE_p_CTrajectoryProblem;
        break;
        /*
              case CCopasiTask::scan:
                pInfo=SWIGTYPE_p_CScanProblem;
                break;
              case CCopasiTask::fluxMode:
                pInfo=SWIGTYPE_p_CEFMProblem;
                break;
              case CCopasiTask::optimization:
                pInfo=SWIGTYPE_p_COptProblem;
                break;
              case CCopasiTask::parameterFitting:
                pInfo=SWIGTYPE_p_CFitProblem;
                break;
              case CCopasiTask::mca:
                pInfo=SWIGTYPE_p_CMCAProblem;
                break;
              case CCopasiTask::lyap:
                pInfo=SWIGTYPE_p_CLyapProblem;
                break;
#ifdef COPASI_DEBUG
              case CCopasiTask::tss:
                pInfo=SWIGTYPE_p_CTSSProblem;
                break;
              case CCopasiTask::sens:
                pInfo=SWIGTYPE_p_CSensProblem;
                break;
#endif // COPASI_DEBUG
#ifdef COPASI_SSA
              case CCopasiTask::ssa:
                pInfo=SWIGTYPE_p_CSSAProblem;
                break;
#endif // COPASI_SSA
        */
      default:
        break;
      }
    return pInfo;
  }

/**
 * @return the most specific Swig type for the given CEvaluationTree object.
 */
struct swig_type_info*
      GetDowncastSwigTypeForCEvaluationTree (CEvaluationTree* tree)
  {
    if (tree == NULL) return SWIGTYPE_p_CEvaluationTree;

    struct swig_type_info* pInfo = SWIGTYPE_p_CEvaluationTree;
    if (dynamic_cast<CFunction*>(tree))
      {
        pInfo = SWIGTYPE_p_CFunction;
      }
    return pInfo;
  }
