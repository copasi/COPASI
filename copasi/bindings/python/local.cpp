// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/local.cpp,v $
//   $Revision: 1.8.6.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/11/24 17:05:42 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CopasiDataModel/CCopasiDataModel.h"
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
#include "utilities/CAnnotatedMatrix.h"
#include "utilities/CMatrix.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "steadystate/CSteadyStateMethod.h"
#include "steadystate/CNewtonMethod.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "trajectory/CTrajectoryMethod.h"
#include "scan/CScanTask.h"
#include "scan/CScanProblem.h"
#include "scan/CScanMethod.h"
#include "lyap/CLyapTask.h"
#include "lyap/CLyapProblem.h"
#include "lyap/CLyapMethod.h"
#include "optimization/COptItem.h"
#include "optimization/COptTask.h"
#include "optimization/COptProblem.h"
#include "optimization/COptMethod.h"
#include "parameterFitting/CExperiment.h"
#include "parameterFitting/CExperimentFileInfo.h"
#include "parameterFitting/CExperimentObjectMap.h"
#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CFitItem.h"
#include "parameterFitting/CFitMethod.h"
#include "parameterFitting/CFitProblem.h"
#include "parameterFitting/CFitTask.h"

//#include <iostream>

typedef CCopasiVector<CCopasiTask> TaskVector;
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

typedef CCopasiVector<CModelValue> ModelValueVector;
typedef CCopasiVectorN<CReportDefinition> CReportDefinitionVectorN;
typedef CCopasiVectorN<CMetab> MetabVectorN;
typedef CCopasiVector<CCompartment> CompartmentVector;
typedef CCopasiVectorN<CCompartment> CompartmentVectorN;
typedef CCopasiVectorN<CReaction> ReactionVectorN;
typedef CCopasiVector<CReaction> ReactionVector;
typedef CCopasiVector<CEvaluationTree> CEvaluationTreeVector;

typedef CCopasiMatrixInterface<CMatrix<C_FLOAT64> > AnnotatedFloatMatrix;

/**
 * @return the most specific Swig type for the given CExperimentSet object.
struct swig_type_info*
      GetDowncastSwigTypeForCExperimentSet (CExperimentSet* experimentSet)
  {
    if (array == NULL) return SWIGTYPE_p_CExperimentSet;

    struct swig_type_info* pInfo = SWIGTYPE_p_CExperimentSet;
    if (dynamic_cast<CCrossValidationSet*>(experimentSet))
      {
        pInfo = SWIGTYPE_p_CCrossValidationSet;
      }
    return pInfo;
  }
 */

/**
 * @return the most specific Swig type for the given CFitItem object.
 */
struct swig_type_info*
      GetDowncastSwigTypeForCFitItem (CFitItem* fitItem)
  {
    if (fitItem == NULL) return SWIGTYPE_p_CFitItem;

    struct swig_type_info* pInfo = SWIGTYPE_p_CFitItem;
    if (dynamic_cast<CFitConstraint*>(fitItem))
      {
        pInfo = SWIGTYPE_p_CFitConstraint;
      }
    return pInfo;
  }

/**
 * @return the most specific Swig type for the given COptItem object.
 */
struct swig_type_info*
      GetDowncastSwigTypeForCOptItem (COptItem* optItem)
  {
    if (optItem == NULL) return SWIGTYPE_p_COptItem;

    struct swig_type_info* pInfo = SWIGTYPE_p_COptItem;
    if (dynamic_cast<CFitItem*>(optItem))
      {
        pInfo = GetDowncastSwigTypeForCFitItem(static_cast<CFitItem*>(optItem));
      }
    return pInfo;
  }

/**
 * @return the most specific Swig type for the given COptProblem object.
 */
struct swig_type_info*
      GetDowncastSwigTypeForCOptProblem (COptProblem* optProblem)
  {
    if (optProblem == NULL) return SWIGTYPE_p_COptProblem;

    struct swig_type_info* pInfo = SWIGTYPE_p_COptProblem;
    if (dynamic_cast<CFitProblem*>(optProblem))
      {
        pInfo = SWIGTYPE_p_CFitProblem;
      }
    return pInfo;
  }

/**
 * @return the most specific Swig type for the given COptMethod object.
 */
struct swig_type_info*
      GetDowncastSwigTypeForCOptMethod (COptMethod* optMethod)
  {
    if (optMethod == NULL) return SWIGTYPE_p_COptMethod;

    struct swig_type_info* pInfo = SWIGTYPE_p_COptMethod;
    if (dynamic_cast<CFitMethod*>(optMethod))
      {
        pInfo = SWIGTYPE_p_CFitMethod;
      }
    return pInfo;
  }

/**
 * @return the most specific Swig type for the given COptTask object.
 */
struct swig_type_info*
      GetDowncastSwigTypeForCOptTask (COptTask* optTask)
  {
    if (optTask == NULL) return SWIGTYPE_p_COptTask;

    struct swig_type_info* pInfo = SWIGTYPE_p_COptTask;
    if (dynamic_cast<CFitTask*>(optTask))
      {
        pInfo = SWIGTYPE_p_CFitTask;
      }
    return pInfo;
  }

/**
 * @return the most specific Swig type for the given CCopasiAbstractArray object.
 */
struct swig_type_info*
      GetDowncastSwigTypeForCCopasiAbstractArray (CCopasiAbstractArray* array)
  {
    if (array == NULL) return SWIGTYPE_p_CCopasiAbstractArray;

    struct swig_type_info* pInfo = SWIGTYPE_p_CCopasiAbstractArray;
    if (dynamic_cast<CCopasiArray*>(array))
      {
        pInfo = SWIGTYPE_p_CCopasiArray;
      }
    /* The following code no longer compiles out of some reason
    else if (dynamic_cast<CCopasiMatrixInterface<CMatrix<C_FLOAT64> >*>(array))
      {
        pInfo = SWIGTYPE_p_CCopasiMatrixInterfaceTCMatrixTdouble_t_t;
      }
      */
    return pInfo;
  }

/**
 * @return the most specific Swig type for the given Task object.
 */
struct swig_type_info*
      GetDowncastSwigTypeForTask (CCopasiTask* task)
  {
    if (task == NULL) return SWIGTYPE_p_CCopasiTask;

    struct swig_type_info* pInfo = SWIGTYPE_p_CCopasiTask;
    if (dynamic_cast<COptTask*>(task))
      {
        pInfo = GetDowncastSwigTypeForCOptTask(static_cast<COptTask*>(task));
      }
    else if (dynamic_cast<CTrajectoryTask*>(task))
      {
        pInfo = SWIGTYPE_p_CTrajectoryTask;
      }
    else if (dynamic_cast<CScanTask*>(task))
      {
        pInfo = SWIGTYPE_p_CScanTask;
      }
    else if (dynamic_cast<CSteadyStateTask*>(task))
      {
        pInfo = SWIGTYPE_p_CSteadyStateTask;
      }
    else if (dynamic_cast<CLyapTask*>(task))
      {
        pInfo = SWIGTYPE_p_CLyapTask;
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
    if (dynamic_cast<COptMethod*>(method))
      {
        pInfo = GetDowncastSwigTypeForCOptMethod(static_cast<COptMethod*>(method));
      }
    else if (dynamic_cast<CTrajectoryMethod*>(method))
      {
        pInfo = SWIGTYPE_p_CTrajectoryMethod;
      }
    else if (dynamic_cast<CScanMethod*>(method))
      {
        pInfo = SWIGTYPE_p_CScanMethod;
      }
    else if (dynamic_cast<CSteadyStateMethod*>(method))
      {
        pInfo = SWIGTYPE_p_CSteadyStateMethod;
      }
    else if (dynamic_cast<CLyapMethod*>(method))
      {
        pInfo = SWIGTYPE_p_CLyapMethod;
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
    if (dynamic_cast<COptProblem*>(problem))
      {
        pInfo = GetDowncastSwigTypeForCOptProblem(static_cast<COptProblem*>(problem));
      }
    else if (dynamic_cast<CTrajectoryProblem*>(problem))
      {
        pInfo = SWIGTYPE_p_CTrajectoryProblem;
      }
    else if (dynamic_cast<CScanProblem*>(problem))
      {
        pInfo = SWIGTYPE_p_CScanProblem;
      }
    else if (dynamic_cast<CSteadyStateProblem*>(problem))
      {
        pInfo = SWIGTYPE_p_CSteadyStateProblem;
      }
    else if (dynamic_cast<CLyapProblem*>(problem))
      {
        pInfo = SWIGTYPE_p_CLyapProblem;
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
    else if (dynamic_cast<CExperiment*>(group))
      {
        pInfo = SWIGTYPE_p_CExperiment;
      }
    else if (dynamic_cast<CExperimentObjectMap*>(group))
      {
        pInfo = SWIGTYPE_p_CExperimentObjectMap;
      }
    else if (dynamic_cast<CExperimentSet*>(group))
      {
        pInfo = SWIGTYPE_p_CExperimentSet; //GetDowncastSwigTypeForCExperimentSet(static_cast<CExperimentSet*>(group));
      }
    else if (dynamic_cast<COptItem*>(group))
      {
        pInfo = GetDowncastSwigTypeForCOptItem(static_cast<COptItem*>(group));
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
    else if (dynamic_cast<CArrayAnnotation*>(container))
      {
        pInfo = SWIGTYPE_p_CArrayAnnotation;
      }
    else if (dynamic_cast<CFittingPoint*>(container))
      {
        pInfo = SWIGTYPE_p_CFittingPoint;
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
