/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/local.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: gauges $
   $Date: 2007/01/09 16:33:06 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "utilities/CCopasiMethod.h"
#include "utilities/CCopasiProblem.h"
#include "utilities/CCopasiTask.h"
#include "function/CEvaluationTree.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "function/CFunctionParameter.h"
#include "function/CFunctionParameters.h"
#include "model/CModelValue.h"
#include "model/CMetab.h"
#include "model/CModel.h"
#include "model/CChemEq.h"
#include "model/CChemEqElement.h"
#include "model/CReaction.h"
#include "model/CMoiety.h"
#include "report/CCopasiStaticString.h"
#include "report/CReportDefinition.h"

//#include <iostream>

typedef CCopasiVectorN<CCopasiTask> TaskVectorN;

typedef CCopasiVectorN<CModelValue> ModelValueVectorN;

typedef CCopasiVector<CMoiety> MoietyVector;

typedef CCopasiVector<CMetab> MetabVector;
typedef CCopasiVectorNS<CMetab> MetabVectorNS;

typedef CCopasiVectorNS<CCompartment> CompartmentVectorNS;

typedef CCopasiVectorNS<CReaction> ReactionVectorNS;

typedef std::vector<CRegisteredObjectName> ReportItemVector;
typedef std::vector<CCopasiParameter*> ParameterVector;

typedef CCopasiVectorN<CEvaluationTree> CEvaluationTreeVectorN;

typedef std::vector<CFunction> CFunctionStdVector;

typedef CCopasiVector<CChemEqElement> CChemEqElementVector;

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

struct swig_type_info*
      GetDowncastSwigTypeForCCopasiParameterGroup (CCopasiParameterGroup* group)
  {
    if (group == NULL) return SWIGTYPE_p_CCopasiParameterGroup;

    struct swig_type_info* pInfo = SWIGTYPE_p_CCopasiParameterGroup;
    if (dynamic_cast<CCopasiMethod*>(group))
      {
        pInfo = GetDowncastSwigTypeForMethod(static_cast<CCopasiMethod*>(group));
      }
    else if (dynamic_cast<CCopasiProblem*>(group))
      {
        pInfo = GetDowncastSwigTypeForProblem(static_cast<CCopasiProblem*>(group));
      }
    return pInfo;
  }

struct swig_type_info*
      GetDowncastSwigTypeForCCopasiParameter (CCopasiParameter* parameter)
  {
    if (parameter == NULL) return SWIGTYPE_p_CCopasiParameter;

    struct swig_type_info* pInfo = SWIGTYPE_p_CCopasiParameter;
    if (dynamic_cast<CCopasiParameterGroup*>(parameter))
      {
        pInfo = GetDowncastSwigTypeForCCopasiParameterGroup(static_cast<CCopasiParameterGroup*>(parameter));
      }
    return pInfo;
  }

struct swig_type_info*
      GetDowncastSwigTypeForCModelEntity (CModelEntity* entity)
  {
    if (entity == NULL) return SWIGTYPE_p_CModelEntity;

    struct swig_type_info* pInfo = SWIGTYPE_p_CModelEntity;
    if (dynamic_cast<CCompartment*>(entity))
      {
        pInfo = SWIGTYPE_p_CCompartment;
      }
    else if (dynamic_cast<CMetab*>(entity))
      {
        pInfo = SWIGTYPE_p_CMetab;
      }
    else if (dynamic_cast<CModelValue*>(entity))
      {
        pInfo = SWIGTYPE_p_CModelValue;
      }
    else if (dynamic_cast<CModel*>(entity))
      {
        pInfo = SWIGTYPE_p_CModel;
      }
    return pInfo;
  }

struct swig_type_info*
      GetDowncastSwigTypeForCCopasiContainer (CCopasiContainer* container)
  {
    if (container == NULL) return SWIGTYPE_p_CCopasiContainer;

    struct swig_type_info* pInfo = SWIGTYPE_p_CCopasiContainer;
    if (dynamic_cast<CModelEntity*>(container))
      {
        pInfo = GetDowncastSwigTypeForCModelEntity(static_cast<CModelEntity*>(container));
      }
    else if (dynamic_cast<CCopasiParameter*>(container))
      {
        pInfo = GetDowncastSwigTypeForCCopasiParameter(static_cast<CCopasiParameter*>(container));
      }
    else if (container->isNameVector())
      {
        if (dynamic_cast<TaskVectorN*>(container))
          {
            pInfo = SWIGTYPE_p_CCopasiVectorNTCCopasiTask_t;
          }
        else if (dynamic_cast<ModelValueVectorN*>(container))
          {
            pInfo = SWIGTYPE_p_CCopasiVectorNTCModelValue_t;
          }
        else if (dynamic_cast<MetabVectorNS*>(container))
          {
            pInfo = SWIGTYPE_p_CCopasiVectorNSTCMetab_t;
          }
        else if (dynamic_cast<CompartmentVectorNS*>(container))
          {
            pInfo = SWIGTYPE_p_CCopasiVectorNSTCCompartment_t;
          }
        else if (dynamic_cast<ReactionVectorNS*>(container))
          {
            pInfo = SWIGTYPE_p_CCopasiVectorNSTCReaction_t;
          }
        else if (dynamic_cast<CEvaluationTreeVectorN*>(container))
          {
            pInfo = SWIGTYPE_p_CCopasiVectorNTCEvaluationTree_t;
          }
      }
    else if (container->isVector())
      {
        if (dynamic_cast<MoietyVector*>(container))
          {
            pInfo = SWIGTYPE_p_CCopasiVectorTCMoiety_t;
          }
        else if (dynamic_cast<MetabVector*>(container))
          {
            pInfo = SWIGTYPE_p_CCopasiVectorTCMetab_t;
          }
        else if (dynamic_cast<ReportItemVector*>(container))
          {
            pInfo = SWIGTYPE_p_std__vectorTCRegisteredObjectName_std__allocatorTCRegisteredObjectName_t_t;
          }
        else if (dynamic_cast<ParameterVector*>(container))
          {
            pInfo = SWIGTYPE_p_std__vectorTCCopasiParameter_p_std__allocatorTCCopasiParameter_p_t_t;
          }
        else if (dynamic_cast<CFunctionStdVector*>(container))
          {
            pInfo = SWIGTYPE_p_std__vectorTCFunction_p_std__allocatorTCFunction_p_t_t;
          }
        else if (dynamic_cast<CChemEqElementVector*>(container))
          {
            pInfo = SWIGTYPE_p_CCopasiVectorTCChemEqElement_t;
          }
      }
    else if (dynamic_cast<CEvaluationTree*>(container))
      {
        pInfo = GetDowncastSwigTypeForCEvaluationTree(static_cast<CEvaluationTree*>(container));
      }
    else if (dynamic_cast<CCopasiTask*>(container))
      {
        pInfo = GetDowncastSwigTypeForTask(static_cast<CCopasiTask*>(container));
      }
    else if (dynamic_cast<CChemEq*>(container))
      {
        pInfo = SWIGTYPE_p_CChemEq;
      }
    else if (dynamic_cast<CChemEqElement*>(container))
      {
        pInfo = SWIGTYPE_p_CChemEqElement;
      }
    else if (dynamic_cast<CFunctionDB*>(container))
      {
        pInfo = SWIGTYPE_p_CFunctionDB;
      }
    else if (dynamic_cast<CFunctionParameter*>(container))
      {
        pInfo = SWIGTYPE_p_CFunctionParameter;
      }
    else if (dynamic_cast<CFunctionParameters*>(container))
      {
        pInfo = SWIGTYPE_p_CFunctionParameters;
      }
    else if (dynamic_cast<CMoiety*>(container))
      {
        pInfo = SWIGTYPE_p_CMoiety;
      }
    else if (dynamic_cast<CReaction*>(container))
      {
        pInfo = SWIGTYPE_p_CReaction;
      }
    else if (dynamic_cast<CReport*>(container))
      {
        pInfo = SWIGTYPE_p_CReport;
      }
    return pInfo;
  }

struct swig_type_info*
      GetDowncastSwigTypeForCCopasiObject (CCopasiObject* object)
  {
    if (object == NULL) return SWIGTYPE_p_CCopasiObject;

    struct swig_type_info* pInfo = SWIGTYPE_p_CCopasiObject;
    if (dynamic_cast<CCopasiContainer*>(object))
      {
        pInfo = GetDowncastSwigTypeForCCopasiContainer(static_cast<CCopasiContainer*>(object));
      }
    else if (dynamic_cast<CReportDefinition*>(object))
      {
        pInfo = SWIGTYPE_p_CReportDefinition;
      }
    else if (dynamic_cast<CCopasiStaticString*>(object))
      {
        if (dynamic_cast<CCopasiReportSeparator*>(object))
          {
            pInfo = SWIGTYPE_p_CCopasiReportSeparator;
          }
        else
          {
            pInfo = SWIGTYPE_p_CCopasiStaticString;
          }
      }
    return pInfo;
  }
