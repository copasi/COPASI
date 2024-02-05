// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// These are the downcast rules for the non Java languages
// Out of some reason, Java does it differently

// here we add the declaration in alphabetic order so that we can use all function in
// other functions below without having to worry about the order

#include <copasi/plot/CPlotItem.h>
#include <copasi/optimization/COptMethodCoranaWalk.h>
#include <copasi/optimization/COptMethodDE.h>
#include <copasi/optimization/COptMethodEP.h>
#include <copasi/optimization/COptMethodGA.h>
#include <copasi/optimization/COptMethodGASR.h>
#include <copasi/optimization/COptMethodHookeJeeves.h>
#include <copasi/optimization/COptMethodLevenbergMarquardt.h>
#include <copasi/optimization/COptMethodNelderMead.h>
#include <copasi/optimization/COptMethodPraxis.h>
#include <copasi/optimization/COptMethodPS.h>
#include <copasi/optimization/COptMethodSA.h>
#include <copasi/optimization/COptMethodSRES.h>
#include <copasi/optimization/COptMethodSS.h>
#include <copasi/optimization/COptMethodStatistics.h>
#include <copasi/optimization/COptMethodSteepestDescent.h>
#include <copasi/optimization/CRandomSearch.h>
#include <copasi/optimization/COptMethodTruncatedNewton.h>

#include <copasi/model/CModelParameter.h>
#include <copasi/model/CModelParameterSet.h>

#include <copasi/utilities/CopasiTime.h>

#include <copasi/CopasiTaskTypes.h>

// CArrayInterface
struct swig_type_info*
GetDowncastSwigTypeForCArrayInterface(CArrayInterface* array);

// CDataContainer
struct swig_type_info*
GetDowncastSwigTypeForCDataContainer(CDataContainer* container);

// CCopasiMethod
struct swig_type_info*
GetDowncastSwigTypeForMethod(CCopasiMethod* method);

// CDataObject
struct swig_type_info*
GetDowncastSwigTypeForCDataObject(CDataObject* object);

// CObjectInterface
struct swig_type_info*
GetDowncastSwigTypeForCObjectInterface(CObjectInterface* objectInterface);

// CCopasiParameter
struct swig_type_info*
GetDowncastSwigTypeForCCopasiParameter(CCopasiParameter* parameter);

// CCopasiParameterGroup
struct swig_type_info*
GetDowncastSwigTypeForCCopasiParameterGroup(CCopasiParameterGroup* group);

// CCopasiProblem
struct swig_type_info*
GetDowncastSwigTypeForProblem(CCopasiProblem* problem);

// CCopasiTask
struct swig_type_info*
GetDowncastSwigTypeForTask(CCopasiTask* task);

// CEvaluationTree
struct swig_type_info*
GetDowncastSwigTypeForCEvaluationTree(CEvaluationTree* tree);

// CFitItem
struct swig_type_info*
GetDowncastSwigTypeForCFitItem(CFitItem* fitItem);

// CModelEntity
struct swig_type_info*
GetDowncastSwigTypeForCModelEntity(CModelEntity* entity);

// COptItem
struct swig_type_info*
GetDowncastSwigTypeForCOptItem(COptItem* optItem);

// COptMethod
struct swig_type_info*
GetDowncastSwigTypeForCOptMethod(COptMethod* optMethod);

// COptProblem
struct swig_type_info*
GetDowncastSwigTypeForCOptProblem(COptProblem* optProblem);

// COptTask
struct swig_type_info*
GetDowncastSwigTypeForCOptTask(COptTask* optTask);

// CModelParameter
struct swig_type_info*
GetDowncastSwigTypeForCModelParameter(CModelParameter* param);

/**
 * @return the most specific Swig type for the given CModelParameter object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCModelParameter(CModelParameter* param)
{
  if (param == NULL) return SWIGTYPE_p_CModelParameter;

  if (dynamic_cast<CModelParameterSet*>(param))
    return SWIGTYPE_p_CModelParameterSet;

  if (dynamic_cast<CModelParameterGroup*>(param))
    return SWIGTYPE_p_CModelParameterGroup;

  if (dynamic_cast<CModelParameterSpecies*>(param))
    return SWIGTYPE_p_CModelParameterSpecies;

  if (dynamic_cast<CModelParameterCompartment*>(param))
    return SWIGTYPE_p_CModelParameterCompartment;

  if (dynamic_cast<CModelParameterSpecies*>(param))
    return SWIGTYPE_p_CModelParameterSpecies;

  if (dynamic_cast<CModelParameterReactionParameter*>(param))
    return SWIGTYPE_p_CModelParameterReactionParameter;

  return SWIGTYPE_p_CModelParameter;
}

/**
 * @return the most specific Swig type for the given CArrayInterface object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCArrayInterface(CArrayInterface* array)
{
  if (array == NULL) return SWIGTYPE_p_CArrayInterface;

  struct swig_type_info* pInfo = SWIGTYPE_p_CArrayInterface;

  if (dynamic_cast<CArray*>(array))
    {
      pInfo = SWIGTYPE_p_CArray;
    }

  /* The following code no longer compiles out of some reason
  else if (dynamic_cast<CCopasiMatrixInterface<CMatrix<C_FLOAT64> >*>(array))
    {
      pInfo = SWIGTYPE_p_CCopasiMatrixInterfaceTCMatrixTdouble_t_t;
    }
    */
  return pInfo;
}

struct swig_type_info*
GetDowncastSwigTypeForCDataContainer(const CDataContainer* object)
{
  return GetDowncastSwigTypeForCDataContainer(const_cast< CDataContainer* >(object));
}

/**
 * @return the most specific Swig type for the given CDataContainer object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCDataContainer(CDataContainer* container)
{
  if (container == NULL) return SWIGTYPE_p_CDataContainer;

  struct swig_type_info* pInfo = SWIGTYPE_p_CDataContainer;

  if (dynamic_cast<CRootContainer*>(container))
    {
      pInfo = SWIGTYPE_p_CRootContainer;
    }
  else if (dynamic_cast<CDataModel*>(container))
    {
      pInfo = SWIGTYPE_p_CDataModel;
    }
  else if (dynamic_cast<CModelEntity*>(container))
    {
      pInfo = GetDowncastSwigTypeForCModelEntity(static_cast<CModelEntity*>(container));
    }
  else if (dynamic_cast<CCopasiParameter*>(container))
    {
      pInfo = GetDowncastSwigTypeForCCopasiParameter(static_cast<CCopasiParameter*>(container));
    }
  else if (dynamic_cast<CEvent*>(container))
    {
      pInfo = SWIGTYPE_p_CEvent;
    }
  else if (dynamic_cast<CEventAssignment*>(container))
    {
      pInfo = SWIGTYPE_p_CEventAssignment;
    }
  else if (dynamic_cast<CModelParameterSet*>(container))
    {
      pInfo = SWIGTYPE_p_CModelParameterSet;
    }
  else if (dynamic_cast<CReference*>(container))
    {
      pInfo = SWIGTYPE_p_CReference;
    }
  else if (dynamic_cast<CBiologicalDescription*>(container))
    {
      pInfo = SWIGTYPE_p_CBiologicalDescription;
    }
  else if (dynamic_cast<CModification*>(container))
    {
      pInfo = SWIGTYPE_p_CModification;
    }
  else if (dynamic_cast<CCreator*>(container))
    {
      pInfo = SWIGTYPE_p_CCreator;
    }
  /*else if (dynamic_cast<CScanItem*>(container))
    {
      pInfo = SWIGTYPE_p_CScanItem;
    }
  else if (dynamic_cast<CPlotItem*>(container))
    {
      pInfo = SWIGTYPE_p_CPlotItem;
    }*/
  else if (dynamic_cast<CMIRIAMInfo*>(container))
    {
      pInfo = SWIGTYPE_p_CMIRIAMInfo;
    }
  else if (dynamic_cast<CDataModelVectorN*>(container))
    {
      pInfo = SWIGTYPE_p_CDataVectorT_CDataModel_t;
    }
  else if (dynamic_cast<TaskVectorN*>(container))
    {
      pInfo = SWIGTYPE_p_CDataVectorNT_CCopasiTask_t;
    }
  else if (dynamic_cast<ModelValueVectorN*>(container))
    {
      pInfo = SWIGTYPE_p_CDataVectorNT_CModelValue_t;
    }
  else if (dynamic_cast<MetabVectorNS*>(container))
    {
      pInfo = SWIGTYPE_p_CDataVectorNST_CMetab_t;
    }
  else if (dynamic_cast<CompartmentVectorNS*>(container))
    {
      pInfo = SWIGTYPE_p_CDataVectorNST_CCompartment_t;
    }
  else if (dynamic_cast<ReactionVectorNS*>(container))
    {
      pInfo = SWIGTYPE_p_CDataVectorNST_CReaction_t;
    }
  else if (dynamic_cast<CEvaluationTreeVectorN*>(container))
    {
      pInfo = SWIGTYPE_p_CDataVectorNT_CEvaluationTree_t;
    }
  else if (dynamic_cast<EventVectorN*>(container))
    {
      pInfo = SWIGTYPE_p_CDataVectorNT_CEvent_t;
    }
  else if (dynamic_cast<EventAssignmentVectorN*>(container))
    {
      pInfo = SWIGTYPE_p_CDataVectorNT_CEventAssignment_t;
    }

  else if (dynamic_cast<MoietyVector*>(container))
    {
      pInfo = SWIGTYPE_p_CDataVectorT_CMoiety_t;
    }
  else if (dynamic_cast<MetabVector*>(container))
    {
      pInfo = SWIGTYPE_p_CDataVectorT_CMetab_t;
    }
  else if (dynamic_cast<ReportItemVector*>(container))
    {
#if defined(SWIGPERL) || SWIG_VERSION >= 0x040200
      pInfo = SWIGTYPE_p_std__vectorT_CRegisteredCommonName_t;
#else
      pInfo = SWIGTYPE_p_std__vectorT_CRegisteredCommonName_std__allocatorT_CRegisteredCommonName_t_t;
#endif // SWIGPERL
    }
  else if (dynamic_cast<ParameterVector*>(container))
    {
#if defined(SWIGPERL) || SWIG_VERSION >= 0x040200
      pInfo = SWIGTYPE_p_std__vectorT_CCopasiParameter_p_t;
#else
      pInfo = SWIGTYPE_p_std__vectorT_CCopasiParameter_p_std__allocatorT_CCopasiParameter_p_t_t;
#endif // SWIGPERL
    }
  else if (dynamic_cast<CFunctionStdVector*>(container))
    {
#if defined(SWIGPERL) || SWIG_VERSION >= 0x040200
      pInfo = SWIGTYPE_p_std__vectorT_CFunction_p_t;
#else
      pInfo = SWIGTYPE_p_std__vectorT_CFunction_p_std__allocatorT_CFunction_p_t_t;
#endif // SWIGPERL
    }
  else if (dynamic_cast<CChemEqElementVector*>(container))
    {
      pInfo = SWIGTYPE_p_CDataVectorT_CChemEqElement_t;
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
  else if (dynamic_cast<CDataArray*>(container))
    {
      pInfo = SWIGTYPE_p_CDataArray;
    }
  else if (dynamic_cast<CFittingPoint*>(container))
    {
      pInfo = SWIGTYPE_p_CFittingPoint;
    }

  return pInfo;
}

/**
 * @return the most specific Swig type for the given CCopasiMethod object.
 */
struct swig_type_info*
GetDowncastSwigTypeForMethod(CCopasiMethod* method)
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
  else if (dynamic_cast<CMCAMethod*>(method))
    {
      pInfo = SWIGTYPE_p_CMCAMethod;
    }
  else if (dynamic_cast<CLyapMethod*>(method))
    {
      pInfo = SWIGTYPE_p_CLyapMethod;
    }
  else if (dynamic_cast<CSensMethod*>(method))
    {
      pInfo = SWIGTYPE_p_CSensMethod;
    }

  return pInfo;
}

/**
 * @return the most specific Swig type for the given CDataObject object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCDataObject(CDataObject* object)
{
  if (object == NULL) return SWIGTYPE_p_CDataObject;

  struct swig_type_info* pInfo = SWIGTYPE_p_CDataObject;

  if (dynamic_cast<CDataContainer*>(object))
    {
      pInfo = GetDowncastSwigTypeForCDataContainer(static_cast<CDataContainer*>(object));
    }
  else if (dynamic_cast<CCopasiTimer*>(object))
    {
      pInfo = SWIGTYPE_p_CCopasiTimer;
    }
  else if (dynamic_cast<CReportDefinition*>(object))
    {
      pInfo = SWIGTYPE_p_CReportDefinition;
    }
  else if (dynamic_cast<CDataString*>(object))
    {
      if (dynamic_cast<CCopasiReportSeparator*>(object))
        {
          pInfo = SWIGTYPE_p_CCopasiReportSeparator;
        }
      else
        {
          pInfo = SWIGTYPE_p_CDataString;
        }
    }

  return pInfo;
}

struct swig_type_info*
GetDowncastSwigTypeForCDataObject(const CDataObject* object)
{
  return GetDowncastSwigTypeForCDataObject(const_cast< CDataObject* >(object));
}

// CObjectInterface
struct swig_type_info*
GetDowncastSwigTypeForCObjectInterface(CObjectInterface* objectInterface)
{
  if (objectInterface == NULL) return SWIGTYPE_p_CObjectInterface;

  struct swig_type_info* pInfo = SWIGTYPE_p_CObjectInterface;

  if (dynamic_cast<CDataObject*>(objectInterface))
    {
      pInfo = GetDowncastSwigTypeForCDataObject(static_cast<CDataObject*>(objectInterface));
    }

  return pInfo;
}

/**
 * @return the most specific Swig type for the given CCopasiParameter object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCCopasiParameter(CCopasiParameter* parameter)
{
  if (parameter == NULL) return SWIGTYPE_p_CCopasiParameter;

  struct swig_type_info* pInfo = SWIGTYPE_p_CCopasiParameter;

  if (dynamic_cast<CCopasiParameterGroup*>(parameter))
    {
      pInfo = GetDowncastSwigTypeForCCopasiParameterGroup(static_cast<CCopasiParameterGroup*>(parameter));
    }

  return pInfo;
}

/**
 * @return the most specific Swig type for the given CCopasiParameterGroup object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCCopasiParameterGroup(CCopasiParameterGroup* group)
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

/**
 * @return the most specific Swig type for the given Problem object.
 */
struct swig_type_info*
GetDowncastSwigTypeForProblem(CCopasiProblem* problem)
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
  else if (dynamic_cast<CMCAProblem*>(problem))
    {
      pInfo = SWIGTYPE_p_CMCAProblem;
    }
  else if (dynamic_cast<CLyapProblem*>(problem))
    {
      pInfo = SWIGTYPE_p_CLyapProblem;
    }
  else if (dynamic_cast<CSensProblem*>(problem))
    {
      pInfo = SWIGTYPE_p_CSensProblem;
    }

  return pInfo;
}

/**
 * @return the most specific Swig type for the given Task object.
 */
struct swig_type_info*
GetDowncastSwigTypeForTask(CCopasiTask* task)
{
  if (task == NULL) return SWIGTYPE_p_CCopasiTask;

  struct swig_type_info* pInfo = SWIGTYPE_p_CCopasiTask;

  if (dynamic_cast<COptTask*>(task))
    {
      pInfo = GetDowncastSwigTypeForCOptTask(static_cast<COptTask*>(task));
    }
  else if (dynamic_cast<CCrossSectionTask*>(task))
    {
      pInfo = SWIGTYPE_p_CCrossSectionTask;
    }
  else if (dynamic_cast<CEFMTask*>(task))
    {
      pInfo = SWIGTYPE_p_CEFMTask;
    }
  else if (dynamic_cast<CLNATask*>(task))
    {
      pInfo = SWIGTYPE_p_CLNATask;
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
  else if (dynamic_cast<CMCATask*>(task))
    {
      pInfo = SWIGTYPE_p_CMCATask;
    }
  else if (dynamic_cast<CLyapTask*>(task))
    {
      pInfo = SWIGTYPE_p_CLyapTask;
    }
  else if (dynamic_cast<CSensTask*>(task))
    {
      pInfo = SWIGTYPE_p_CSensTask;
    }

  return pInfo;
}

/**
 * @return the most specific Swig type for the given CEvaluationTree object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCEvaluationTree(CEvaluationTree* tree)
{
  if (tree == NULL) return SWIGTYPE_p_CEvaluationTree;

  struct swig_type_info* pInfo = SWIGTYPE_p_CEvaluationTree;

  if (dynamic_cast<CFunction*>(tree))
    {
      pInfo = SWIGTYPE_p_CFunction;
    }

  return pInfo;
}

/**
 * @return the most specific Swig type for the given CFitItem object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCFitItem(CFitItem* fitItem)
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
 * @return the most specific Swig type for the given CModelEntity object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCModelEntity(CModelEntity* entity)
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

/**
 * @return the most specific Swig type for the given COptItem object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCOptItem(COptItem* optItem)
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
 * @return the most specific Swig type for the given COptMethod object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCOptMethod(COptMethod* optMethod)
{
  if (dynamic_cast<COptMethodCoranaWalk*>(optMethod))
    return SWIGTYPE_p_COptMethodCoranaWalk;

  if (dynamic_cast<COptMethodDE*>(optMethod))
    return SWIGTYPE_p_COptMethodDE;

  if (dynamic_cast<COptMethodEP*>(optMethod))
    return SWIGTYPE_p_COptMethodEP;

  if (dynamic_cast<COptMethodGA*>(optMethod))
    return SWIGTYPE_p_COptMethodGA;

  if (dynamic_cast<COptMethodGASR*>(optMethod))
    return SWIGTYPE_p_COptMethodGASR;

  if (dynamic_cast<COptMethodHookeJeeves*>(optMethod))
    return SWIGTYPE_p_COptMethodHookeJeeves;

  if (dynamic_cast<COptMethodLevenbergMarquardt*>(optMethod))
    return SWIGTYPE_p_COptMethodLevenbergMarquardt;

  if (dynamic_cast<COptMethodNelderMead*>(optMethod))
    return SWIGTYPE_p_COptMethodNelderMead;

  if (dynamic_cast<COptMethodPraxis*>(optMethod))
    return SWIGTYPE_p_COptMethodPraxis;

  if (dynamic_cast<COptMethodSA*>(optMethod))
    return SWIGTYPE_p_COptMethodSA;

  if (dynamic_cast<COptMethodSRES*>(optMethod))
    return SWIGTYPE_p_COptMethodSRES;

  if (dynamic_cast<COptMethodSS*>(optMethod))
    return SWIGTYPE_p_COptMethodSS;

  if (dynamic_cast<COptMethodStatistics*>(optMethod))
    return SWIGTYPE_p_COptMethodStatistics;

  if (dynamic_cast<COptMethodSteepestDescent*>(optMethod))
    return SWIGTYPE_p_COptMethodSteepestDescent;

  if (dynamic_cast<CRandomSearch*>(optMethod))
    return SWIGTYPE_p_CRandomSearch;

  if (dynamic_cast<COptMethodTruncatedNewton*>(optMethod))
    return SWIGTYPE_p_COptMethodTruncatedNewton;

  return SWIGTYPE_p_COptMethod;
}

/**
 * @return the most specific Swig type for the given COptProblem object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCOptProblem(COptProblem* optProblem)
{
  if (dynamic_cast<CFitProblem*>(optProblem))
    return SWIGTYPE_p_CFitProblem;

  return SWIGTYPE_p_COptProblem;
}

/**
 * @return the most specific Swig type for the given COptTask object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCOptTask(COptTask* optTask)
{
  if (optTask == NULL) return SWIGTYPE_p_COptTask;

  struct swig_type_info* pInfo = SWIGTYPE_p_COptTask;

  if (dynamic_cast<CFitTask*>(optTask))
    {
      pInfo = SWIGTYPE_p_CFitTask;
    }

  return pInfo;
}
