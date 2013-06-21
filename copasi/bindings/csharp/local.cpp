// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "../common/local_common.cpp"
#include "plot/CPlotSpecification.h"
// Now we specify the definitions
// for the type determination methods

// Determine type CCopasiAbstractArray
int GetType_CCopasiAbstractArray(CCopasiAbstractArray* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CCopasiArray*>(pPointer))
        {
          // return a CCopasiArray
          result = CCopasiArray_Type;
        }
      else if (dynamic_cast<CCopasiMatrixInterface<CMatrix<C_FLOAT64> >*>(pPointer))
        {
          // return a AnnotatedFloatMatrix
          result = AnnotatedFloatMatrix_Type;
        }
      else
        {
          // return a CCopasiAbstractArray
          result = CCopasiAbstractArray_Type;
        }
    }

  return (int)result;
}

// Determine type for CCopasiContainer
int GetType_CCopasiContainer(CCopasiContainer* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CCopasiRootContainer*>(pPointer))
        {
          // return a CCopasiRootContainer
          result = CCopasiRootContainer_Type;
        }
      else if (dynamic_cast<CCopasiDataModel*>(pPointer))
        {
          // return a CCopasiDataModel
          result = CCopasiDataModel_Type;
        }
      else if (dynamic_cast<CChemEq*>(pPointer))
        {
          // return a CChemEq
          result = CChemEq_Type;
        }
      else if (dynamic_cast<CChemEqElement*>(pPointer))
        {
          // return a CChemEqElement
          result = CChemEqElement_Type;
        }
      else if (dynamic_cast<CReference*>(pPointer))
        {
          // return a CReference
          result = CReference_Type;
        }
      else if (dynamic_cast<CModification*>(pPointer))
        {
          // return a CModification
          result = CModification_Type;
        }
      else if (dynamic_cast<CCreator*>(pPointer))
        {
          // return a CCreator
          result = CCreator_Type;
        }
      else if (dynamic_cast<CBiologicalDescription*>(pPointer))
        {
          // return a CBiologicalDescription
          result = CBiologicalDescription_Type;
        }
      else if (dynamic_cast<CMIRIAMInfo*>(pPointer))
        {
          // return a CMIRIAMInfo
          result = CMIRIAMInfo_Type;
        }
      else if (dynamic_cast<CCopasiTask*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          return CCopasiTask_Type;
          //result = GetType_CCopasiTask((CCopasiTask*)pPointer);
        }
      else if (dynamic_cast<CCopasiParameter*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          result = CCopasiParameter_Type;
          //result = GetType_CCopasiParameter((CCopasiParameter*)pPointer);
        }
      else if (dynamic_cast<CEvaluationTree*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          result = CEvaluationTree_Type;
          //result = GetType_CEvaluationTree((CEvaluationTree*)pPointer);
        }
      else if (dynamic_cast<CFunctionDB*>(pPointer))
        {
          // return a CFunctionDB
          result = CFunctionDB_Type;
        }
      else if (dynamic_cast<CFunctionParameter*>(pPointer))
        {
          // return a CFunctionParameter
          result = CFunctionParameter_Type;
        }
      else if (dynamic_cast<CFunctionParameters*>(pPointer))
        {
          // return a CFunctionParameters
          result = CFunctionParameters_Type;
        }
      else if (dynamic_cast<CEvent*>(pPointer))
        {
          // return a CEvent
          result = CEvent_Type;
        }
      else if (dynamic_cast<CEventAssignment*>(pPointer))
        {
          // return a CEventAssignment
          result = CEventAssignment_Type;
        }
      else if (dynamic_cast<CModelEntity*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          result = CModelEntity_Type;
          //result = GetType_CModelEntity((CModelEntity*)pPointer);
        }
      else if (dynamic_cast<CMoiety*>(pPointer))
        {
          // return a CMoiety
          result = CMoiety_Type;
        }
      else if (dynamic_cast<CReaction*>(pPointer))
        {
          // return a CReaction
          result = CReaction_Type;
        }
      else if (dynamic_cast<CFittingPoint*>(pPointer))
        {
          // return a CFittingPoint
          result = CFittingPoint_Type;
        }
      else
        {
          if (pPointer->isVector())
            {
              if (dynamic_cast<CCopasiVector<CCopasiTask>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CCopasiTask>* >(pPointer))
                    {
                      // return a TaskVectorN
                      result = TaskVectorN_Type;
                    }
                  else
                    {
                      // return a TaskVector
                      result = TaskVector_Type;
                    }
                }
              else if (dynamic_cast<CCopasiVector<CModelValue>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CModelValue>* >(pPointer))
                    {
                      // return a ModelValueVectorN
                      result = ModelValueVectorN_Type;
                    }
                  else
                    {
                      // return a ModelValueVector
                      result = ModelValueVector_Type;
                    }
                }
              else if (dynamic_cast<CCopasiVector<CEvent>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CEvent>* >(pPointer))
                    {
                      // return a CEventVectorN
                      result = EventVectorN_Type;
                    }
                  else
                    {
                      // return a EventVector
                      result = EventVector_Type;
                    }
                }
              else if (dynamic_cast<CCopasiVector<CEventAssignment>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CEventAssignment>* >(pPointer))
                    {
                      // return a EventAssignmentVectorN
                      result = EventAssignmentVectorN_Type;
                    }
                  else
                    {
                      // return a EventAssignmentVector
                      result = EventAssignmentVector_Type;
                    }
                }
              else if (dynamic_cast<CCopasiVector<CReportDefinition>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CReportDefinition>* >(pPointer))
                    {
                      // return a ReportDefinitionVectorN
                      result = ReportDefinitionVectorN_Type;
                    }
                  else
                    {
                      // return a ReportDefinitionVector
                      result = ReportDefinitionVector_Type;
                    }
                }
              else if (dynamic_cast<CCopasiVector<CPlotSpecification>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CPlotSpecification>* >(pPointer))
                    {
                      // return a ReportDefinitionVectorN
                      result = OutputDefinitionVectorN_Type;
                    }
                  else
                    {
                      // return a ReportDefinitionVector
                      result = OutputDefinitionVector_Type;
                    }
                }
              else if (dynamic_cast<CCopasiVector<CMoiety>* >(pPointer))
                {
                  // return a MoietyVector
                  result = MoietyVector_Type;
                }
              else if (dynamic_cast<CCopasiVector<CMetab>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CMetab>* >(pPointer))
                    {
                      if (dynamic_cast<CCopasiVectorNS<CMetab>* >(pPointer))
                        {
                          // return a MetabVectorNS
                          result = MetabVectorNS_Type;
                        }
                      else
                        {
                          // return a MetabVectorN
                          result = MetabVectorN_Type;
                        }
                    }
                  else
                    {
                      // return a MetabVector
                      result = MetabVector_Type;
                    }
                }
              else if (dynamic_cast<CCopasiVector<CCompartment>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CCompartment>* >(pPointer))
                    {
                      if (dynamic_cast<CCopasiVectorNS<CCompartment>* >(pPointer))
                        {
                          // return a CompartmentVectorNS
                          result = CompartmentVectorNS_Type;
                        }
                      else
                        {
                          // return a CompartmentVectorN
                          result = CompartmentVectorN_Type;
                        }
                    }
                  else
                    {
                      // return a CompartmentVector
                      result = CompartmentVector_Type;
                    }
                }
              else if (dynamic_cast<CCopasiVector<CReaction>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CReaction>* >(pPointer))
                    {
                      if (dynamic_cast<CCopasiVectorNS<CReaction>* >(pPointer))
                        {
                          // return a ReactionVectorNS
                          result = ReactionVectorNS_Type;
                        }
                      else
                        {
                          // return a ReactionVectorN
                          result = ReactionVectorN_Type;
                        }
                    }
                  else
                    {
                      // return a ReactionVector
                      result = ReactionVector_Type;
                    }
                }
              else if (dynamic_cast<CCopasiVector<CEvaluationTree>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CEvaluationTree>* >(pPointer))
                    {
                      // return a CEvaluationTreeVectorN
                      result = CEvaluationTreeVectorN_Type;
                    }
                  else
                    {
                      // return a CEvaluationTreeVector
                      result = CEvaluationTreeVector_Type;
                    }
                }
              else if (dynamic_cast<CCopasiVector<CChemEqElement>* >(pPointer))
                {
                  // return a CChemEqElementVector
                  result = CChemEqElementVector_Type;
                }
            }
          else if (dynamic_cast<CArrayAnnotation*>(pPointer))
            {
              // return a CArrayAnnotation
              result = CArrayAnnotation_Type;
            }
          else
            {
              // return a CCopasiContainer
              result = CCopasiContainer_Type;
            }
        }
    }

  return (int)result;
}

// Determine type for CCopasiMethod
int GetType_CCopasiMethod(CCopasiMethod* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CTrajectoryMethod*>(pPointer))
        {
          // return a CTrajectoryMethod
          result = CTrajectoryMethod_Type;
        }
      else if (dynamic_cast<CNewtonMethod*>(pPointer))
        {
          // return a CNewtonMethod
          result = CNewtonMethod_Type;
        }
      else if (dynamic_cast<CSteadyStateMethod*>(pPointer))
        {
          // return a CSteadyStateMethod
          result = CSteadyStateMethod_Type;
        }
      else if (dynamic_cast<CMCAMethod*>(pPointer))
        {
          // return a CMCAMethod
          result = CMCAMethod_Type;
        }
      else if (dynamic_cast<CScanMethod*>(pPointer))
        {
          // return a CScanMethod
          result = CScanMethod_Type;
        }
      else if (dynamic_cast<COptMethod*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          result = COptMethod_Type;
          //result = GetType_COptMethod((COptMethod*)pPointer);
        }
      else if (dynamic_cast<CLyapMethod*>(pPointer))
        {
          // return a CLyapMethod
          result = CLyapMethod_Type;
        }
      else if (dynamic_cast<CSensMethod*>(pPointer))
        {
          // return a CSensMethod
          result = CSensMethod_Type;
        }
      else
        {
          // return a CCopasiMethod
          result = CCopasiMethod_Type;
        }
    }

  return (int)result;
}

// Determine type for CCopasiObject
int GetType_CCopasiObject(CCopasiObject* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CCopasiContainer*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          result = CCopasiContainer_Type;
          //result = GetType_CCopasiContainer((CCopasiContainer*)pPointer);
        }
      else if (dynamic_cast<CReportDefinition*>(pPointer))
        {
          // return a CReportDefinition
          result = CReportDefinition_Type;
        }
      else if (dynamic_cast<CCopasiParameter*>(pPointer))
        {
          // return a CCopasiParameter
          result = CCopasiParameter_Type;
        }
      else if (dynamic_cast<CCopasiStaticString*>(pPointer))
        {
          if (dynamic_cast<CCopasiReportSeparator*>(pPointer))
            {
              // return a CCopasiReportSeparator
              result = CCopasiReportSeparator_Type;
            }
          else
            {
              // return a CCopasiStaticString
              result = CCopasiStaticString_Type;
            }
        }
      else
        {
          // return a CCopasiObject
          result = CCopasiObject_Type;
        }
    }

  return (int)result;
}

// Determine type for CCopasiParameter
int GetType_CCopasiParameter(CCopasiParameter* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CCopasiParameterGroup*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          result = CCopasiParameterGroup_Type;
          //result = GetType_CCopasiParameterGroup((CCopasiParameterGroup*)pPointer);
        }
      else
        {
          // return a CCopasiParameter
          result = CCopasiParameter_Type;
        }
    }

  return (int)result;
}

// Determine type for CCopasiParameterGroup
int GetType_CCopasiParameterGroup(CCopasiParameterGroup* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CCopasiMethod*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          result = CCopasiMethod_Type;
          //result = GetType_CCopasiMethod((CCopasiMethod*)pPointer);
        }
      else if (dynamic_cast<CCopasiProblem*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          result = CCopasiProblem_Type;
          //result = GetType_CCopasiProblem((CCopasiProblem*)pPointer);
        }
      else if (dynamic_cast<COptItem*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          result = COptItem_Type;
          //result = GetType_COptItem((COptItem*)pPointer);
        }
      else if (dynamic_cast<CExperiment*>(pPointer))
        {
          // return a CExperiment
          result = CExperiment_Type;
        }
      else if (dynamic_cast<CExperimentSet*>(pPointer))
        {
          // return a CExperimentSet
          result = CExperimentSet_Type;
        }
      else if (dynamic_cast<CExperimentObjectMap*>(pPointer))
        {
          // return a CExperimentObjectMap
          result = CExperimentObjectMap_Type;
        }
      else
        {
          // return a CCopasiParameterGroup
          result = CCopasiParameterGroup_Type;
        }
    }

  return (int)result;
}

// Determine type for CCopasiProblem
int GetType_CCopasiProblem(CCopasiProblem* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CTrajectoryProblem*>(pPointer))
        {
          // return a CTrajectoryProblem
          result = CTrajectoryProblem_Type;
        }
      else if (dynamic_cast<CSteadyStateProblem*>(pPointer))
        {
          // return a CSteadyStateProblem
          result = CSteadyStateProblem_Type;
        }
      else if (dynamic_cast<CMCAProblem*>(pPointer))
        {
          // return a CMCAProblem
          result = CMCAProblem_Type;
        }
      else if (dynamic_cast<CScanProblem*>(pPointer))
        {
          // return a CScanProblem
          result = CScanProblem_Type;
        }
      else if (dynamic_cast<COptProblem*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          result = COptProblem_Type;
          //result = GetType_COptProblem((COptProblem*)pPointer);
        }
      else if (dynamic_cast<CLyapProblem*>(pPointer))
        {
          // return a CLyapProblem
          result = CLyapProblem_Type;
        }
      else if (dynamic_cast<CSensProblem*>(pPointer))
        {
          // return a CSensProblem
          result = CSensProblem_Type;
        }
      else
        {
          // return a CCopasiProblem
          result = CCopasiProblem_Type;
        }
    }

  return (int)result;
}

// Determine type for CCopasiTask
int GetType_CCopasiTask(CCopasiTask* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CTrajectoryTask*>(pPointer))
        {
          // return a CTrajectoryTask
          result = CTrajectoryTask_Type;
        }
      else if (dynamic_cast<CSteadyStateTask*>(pPointer))
        {
          // return a CSteadyStateTask
          result = CSteadyStateTask_Type;
        }
      else if (dynamic_cast<CMCATask*>(pPointer))
        {
          // return a CMCATask
          result = CMCATask_Type;
        }
      else if (dynamic_cast<CScanTask*>(pPointer))
        {
          // return a CScanTask
          result = CScanTask_Type;
        }
      else if (dynamic_cast<COptTask*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          result = COptTask_Type;
          //result = GetType_COptTask((COptTask*)pPointer);
        }
      else if (dynamic_cast<CLyapTask*>(pPointer))
        {
          // return a CLyapTask
          result = CLyapTask_Type;
        }
      else if (dynamic_cast<CSensTask*>(pPointer))
        {
          // return a CSensTask
          result = CSensTask_Type;
        }
      else
        {
          // return a CCopasiTask
          result = CCopasiTask_Type;
        }
    }

  return (int)result;
}

// Determine type for CEvaluationTree
int GetType_CEvaluationTree(CEvaluationTree* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CFunction*>(pPointer))
        {
          // return a CFunction
          result = CFunction_Type;
        }
      else
        {
          // return a CEvaluationTree
          result = CEvaluationTree_Type;
        }
    }

  return (int)result;
}

// Determine type for CFitItem
int GetType_CFitItem(CFitItem* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CFitConstraint*>(pPointer))
        {
          // return a CFitConstraint
          result = CFitConstraint_Type;
        }
      else
        {
          // return a CFitItem
          result = CFitItem_Type;
        }
    }

  return (int)result;
}

// Determine type for CModelEntity
int GetType_CModelEntity(CModelEntity* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CCompartment*>(pPointer))
        {
          // return a CCompartment
          result = CCompartment_Type;
        }
      else if (dynamic_cast<CMetab*>(pPointer))
        {
          // return a CMetab
          result = CMetab_Type;
        }
      else if (dynamic_cast<CModel*>(pPointer))
        {
          // return a CModel
          result = CModel_Type;
        }
      else if (dynamic_cast<CModelValue*>(pPointer))
        {
          // return a CModelValue
          result = CModelValue_Type;
        }
      else
        {
          // return a CModelEntity
          result = CModelEntity_Type;
        }
    }

  return (int)result;
}

// Determine type for COptItem
int GetType_COptItem(COptItem* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CFitItem*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          result = CFitItem_Type;
          //result = GetType_CFitItem((CFitItem*)pPointer);
        }
      else
        {
          // return a COptItem
          result = COptItem_Type;
        }
    }

  return (int)result;
}

// Determine type for COptMethod
int GetType_COptMethod(COptMethod* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CFitMethod*>(pPointer))
        {
          // return a CFitMethod
          result = CFitMethod_Type;
        }
      else
        {
          // return a COptMethod
          result = COptMethod_Type;
        }
    }

  return (int)result;
}

// Determine type for COptProblem
int GetType_COptProblem(COptProblem* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CFitProblem*>(pPointer))
        {
          // return a CFitProblem
          result = CFitProblem_Type;
        }
      else
        {
          // return a COptProblem
          result = COptProblem_Type;
        }
    }

  return (int)result;
}

// Determine type for COptTask
int GetType_COptTask(COptTask* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CFitTask*>(pPointer))
        {
          // return a CFitTask
          result = CFitTask_Type;
        }
      else
        {
          // return a COptTask
          result = COptTask_Type;
        }
    }

  return (int)result;
}

void initCopasi()
{
  CCopasiRootContainer::init(0, NULL, false);
}
