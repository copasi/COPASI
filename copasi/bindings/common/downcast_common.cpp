// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/common/downcast_common.cpp,v $
//   $Revision: 1.1.2.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/08/03 09:33:38 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// These are the downcast rules for the non Java languages
// Out of some reason, Java does it differently

// here we add the declaration in alphabetic order so that we can use all function in
// other functions below without having to worry about the order

// CCopasiAbstractArray
struct swig_type_info*
GetDowncastSwigTypeForCCopasiAbstractArray(CCopasiAbstractArray* array);

// CCopasiContainer
struct swig_type_info*
GetDowncastSwigTypeForCCopasiContainer(CCopasiContainer* container);

// CCopasiMethod
struct swig_type_info*
GetDowncastSwigTypeForMethod(CCopasiMethod* method);

// CCopasiObject
struct swig_type_info*
GetDowncastSwigTypeForCCopasiObject(CCopasiObject* object);

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



/**
 * @return the most specific Swig type for the given CCopasiAbstractArray object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCCopasiAbstractArray(CCopasiAbstractArray* array)
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
 * @return the most specific Swig type for the given CCopasiContainer object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCCopasiContainer(CCopasiContainer* container)
{
  if (container == NULL) return SWIGTYPE_p_CCopasiContainer;

  struct swig_type_info* pInfo = SWIGTYPE_p_CCopasiContainer;

  if (dynamic_cast<CCopasiRootContainer*>(container))
    {
      pInfo = SWIGTYPE_p_CCopasiRootContainer;
    }
  else if (dynamic_cast<CCopasiDataModel*>(container))
    {
      pInfo = SWIGTYPE_p_CCopasiDataModel;
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
  else if (dynamic_cast<CMIRIAMInfo*>(container))
    {
      pInfo = SWIGTYPE_p_CMIRIAMInfo;
    }
  else if (container->isNameVector())
    {
      if (dynamic_cast<CCopasiDataModelVectorN*>(container))
        {
          pInfo = SWIGTYPE_p_CCopasiVectorT_CCopasiDataModel_t;
        }
      else if (dynamic_cast<TaskVectorN*>(container))
        {
          pInfo = SWIGTYPE_p_CCopasiVectorNT_CCopasiTask_t;
        }
      else if (dynamic_cast<ModelValueVectorN*>(container))
        {
          pInfo = SWIGTYPE_p_CCopasiVectorNT_CModelValue_t;
        }
      else if (dynamic_cast<MetabVectorNS*>(container))
        {
          pInfo = SWIGTYPE_p_CCopasiVectorNST_CMetab_t;
        }
      else if (dynamic_cast<CompartmentVectorNS*>(container))
        {
          pInfo = SWIGTYPE_p_CCopasiVectorNST_CCompartment_t;
        }
      else if (dynamic_cast<ReactionVectorNS*>(container))
        {
          pInfo = SWIGTYPE_p_CCopasiVectorNST_CReaction_t;
        }
      else if (dynamic_cast<CEvaluationTreeVectorN*>(container))
        {
          pInfo = SWIGTYPE_p_CCopasiVectorNT_CEvaluationTree_t;
        }
      else if (dynamic_cast<EventVectorN*>(container))
        {
          pInfo = SWIGTYPE_p_CCopasiVectorNT_CEvent_t;
        }
      else if (dynamic_cast<EventAssignmentVectorN*>(container))
        {
          pInfo = SWIGTYPE_p_CCopasiVectorNT_CEventAssignment_t;
        }
    }
  else if (container->isVector())
    {
      if (dynamic_cast<MoietyVector*>(container))
        {
          pInfo = SWIGTYPE_p_CCopasiVectorT_CMoiety_t;
        }
      else if (dynamic_cast<MetabVector*>(container))
        {
          pInfo = SWIGTYPE_p_CCopasiVectorT_CMetab_t;
        }
      else if (dynamic_cast<ReportItemVector*>(container))
        {
#ifdef SWIGPERL
          pInfo = SWIGTYPE_p_std__vectorT_CRegisteredObjectName_t;
#else
          pInfo = SWIGTYPE_p_std__vectorT_CRegisteredObjectName_std__allocatorT_CRegisteredObjectName_t_t;
#endif // SWIGPERL
        }
      else if (dynamic_cast<ParameterVector*>(container))
        {
#ifdef SWIGPERL
          pInfo = SWIGTYPE_p_std__vectorT_CCopasiParameter_p_t;
#else
          pInfo = SWIGTYPE_p_std__vectorT_CCopasiParameter_p_std__allocatorT_CCopasiParameter_p_t_t;
#endif // SWIGPERL
        }
      else if (dynamic_cast<CFunctionStdVector*>(container))
        {
#ifdef SWIGPERL
          pInfo = SWIGTYPE_p_std__vectorT_CFunction_p_t;
#else
          pInfo = SWIGTYPE_p_std__vectorT_CFunction_p_std__allocatorT_CFunction_p_t_t;
#endif // SWIGPERL
        }
      else if (dynamic_cast<CChemEqElementVector*>(container))
        {
          pInfo = SWIGTYPE_p_CCopasiVectorT_CChemEqElement_t;
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
 * @return the most specific Swig type for the given CCopasiObject object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCCopasiObject(CCopasiObject* object)
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
  if (optMethod == NULL) return SWIGTYPE_p_COptMethod;

  struct swig_type_info* pInfo = SWIGTYPE_p_COptMethod;

  if (dynamic_cast<CFitMethod*>(optMethod))
    {
      pInfo = SWIGTYPE_p_CFitMethod;
    }

  return pInfo;
}


/**
 * @return the most specific Swig type for the given COptProblem object.
 */
struct swig_type_info*
GetDowncastSwigTypeForCOptProblem(COptProblem* optProblem)
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


