// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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



#include "../common/local_common.cpp"
#include "copasi/plot/CPlotSpecification.h"

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

// Now we specify the definitions
// for the type determination methods


int GetType_CModelParameter(CModelParameter* pPointer)
{
  CLASS_TYPE result = CModelParameter_Type;

  if (pPointer == NULL) return result;

  if (dynamic_cast<CModelParameterSet*>(pPointer))
    return CModelParameterSet_Type;

  if (dynamic_cast<CModelParameterGroup*>(pPointer))
    return CModelParameterGroup_Type;

  if (dynamic_cast<CModelParameterSpecies*>(pPointer))
    return CModelParameterSpecies_Type;

  if (dynamic_cast<CModelParameterCompartment*>(pPointer))
    return CModelParameterCompartment_Type;

  if (dynamic_cast<CModelParameterReactionParameter*>(pPointer))
    return CModelParameterReactionParameter_Type;

  return CModelParameter_Type;
}

// Determine type CArrayInterface
int GetType_CArrayInterface(CArrayInterface* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CArray*>(pPointer))
        {
          // return a CArray
          result = CArray_Type;
        }
      else if (dynamic_cast<CMatrixInterface<CMatrix<C_FLOAT64> >*>(pPointer))
        {
          // return a AnnotatedFloatMatrix
          result = AnnotatedFloatMatrix_Type;
        }
      else
        {
          // return a CArrayInterface
          result = CArrayInterface_Type;
        }
    }

  return (int)result;
}

// Determine type for CDataContainer
int GetType_CDataContainer(CDataContainer* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CRootContainer*>(pPointer))
        {
          // return a CRootContainer
          result = CRootContainer_Type;
        }
      else if (dynamic_cast<CDataModel*>(pPointer))
        {
          // return a CDataModel
          result = CDataModel_Type;
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
      else if (dynamic_cast<CPlotItem*>(pPointer))
        {
          // return a CScanItem
          result = CPlotItem_Type;
        }
      else if (dynamic_cast<CScanItem*>(pPointer))
        {
          // return a CScanItem
          result = CScanItem_Type;
        }
      else if (dynamic_cast<CMIRIAMInfo*>(pPointer))
        {
          // return a CMIRIAMInfo
          result = CMIRIAMInfo_Type;
        }
      else if (dynamic_cast<CModelParameterSet*>(pPointer))
        {
          // return a CModelParameterSet
          result = CModelParameterSet_Type;
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

          if (dynamic_cast<CDataVector<CCopasiTask>* >(pPointer))
            {
              if (dynamic_cast<CDataVectorN<CCopasiTask>* >(pPointer))
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
          else if (dynamic_cast<CDataVector<CModelValue>* >(pPointer))
            {
              if (dynamic_cast<CDataVectorN<CModelValue>* >(pPointer))
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
          else if (dynamic_cast<CDataVector<CEvent>* >(pPointer))
            {
              if (dynamic_cast<CDataVectorN<CEvent>* >(pPointer))
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
          else if (dynamic_cast<CDataVector<CEventAssignment>* >(pPointer))
            {
              if (dynamic_cast<CDataVectorN<CEventAssignment>* >(pPointer))
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
          else if (dynamic_cast<CDataVector<CReportDefinition>* >(pPointer))
            {
              if (dynamic_cast<CDataVectorN<CReportDefinition>* >(pPointer))
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
          else if (dynamic_cast<CDataVector<CPlotSpecification>* >(pPointer))
            {
              if (dynamic_cast<CDataVectorN<CPlotSpecification>* >(pPointer))
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
          else if (dynamic_cast<CDataVector<CMoiety>* >(pPointer))
            {
              // return a MoietyVector
              result = MoietyVector_Type;
            }
          else if (dynamic_cast<CDataVector<CMetab>* >(pPointer))
            {
              if (dynamic_cast<CDataVectorN<CMetab>* >(pPointer))
                {
                  if (dynamic_cast<CDataVectorNS<CMetab>* >(pPointer))
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
          else if (dynamic_cast<CDataVector<CCompartment>* >(pPointer))
            {
              if (dynamic_cast<CDataVectorN<CCompartment>* >(pPointer))
                {
                  if (dynamic_cast<CDataVectorNS<CCompartment>* >(pPointer))
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
          else if (dynamic_cast<CDataVector<CReaction>* >(pPointer))
            {
              if (dynamic_cast<CDataVectorN<CReaction>* >(pPointer))
                {
                  if (dynamic_cast<CDataVectorNS<CReaction>* >(pPointer))
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
          else if (dynamic_cast<CDataVector<CEvaluationTree>* >(pPointer))
            {
              if (dynamic_cast<CDataVectorN<CEvaluationTree>* >(pPointer))
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
          else if (dynamic_cast<CDataVector<CChemEqElement>* >(pPointer))
            {
              // return a CChemEqElementVector
              result = CChemEqElementVector_Type;
            }

          if (dynamic_cast<CDataArray*>(pPointer))
            {
              // return a CDataArray
              result = CDataArray_Type;
            }
          else
            {
              // return a CDataContainer
              result = CDataContainer_Type;
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
          result = (CLASS_TYPE)GetType_COptMethod((COptMethod*)pPointer);
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

// Determine type for CDataObject
int GetType_CDataObject(CDataObject* pPointer)
{
  CLASS_TYPE result = UNDEFINED_CLASS_TYPE;

  if (pPointer != NULL)
    {
      if (dynamic_cast<CDataContainer*>(pPointer))
        {
          // If we are not to specific here, the typecasting code in csharp.i
          // actually gets a lot easier to maintain.
          result = CDataContainer_Type;
          //result = GetType_CDataContainer((CDataContainer*)pPointer);
        }
      else if (dynamic_cast<CReportDefinition*>(pPointer))
        {
          // return a CReportDefinition
          result = CReportDefinition_Type;
        }
      else if (dynamic_cast<CCopasiTimer*>(pPointer))
        {
          // return a CReportDefinition
          result = CCopasiTimer_Type;
        }
      else if (dynamic_cast<CCopasiParameter*>(pPointer))
        {
          // return a CCopasiParameter
          result = CCopasiParameter_Type;
        }
      else if (dynamic_cast<CDataString*>(pPointer))
        {
          if (dynamic_cast<CCopasiReportSeparator*>(pPointer))
            {
              // return a CCopasiReportSeparator
              result = CCopasiReportSeparator_Type;
            }
          else
            {
              // return a CDataString
              result = CDataString_Type;
            }
        }
      else
        {
          // return a CDataObject
          result = CDataObject_Type;
        }
    }

  return (int)result;
}

int GetType_ConstCDataObject(const CDataObject* pPointer)
{
  return GetType_CDataObject(const_cast<CDataObject*>(pPointer));
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
          result = (CLASS_TYPE)GetType_CCopasiMethod((CCopasiMethod*)pPointer);
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
int GetType_COptMethod(COptMethod* optMethod)
{
  if (dynamic_cast<COptMethodCoranaWalk*>(optMethod))
    return COptMethodCoranaWalk_Type;

  if (dynamic_cast<COptMethodDE*>(optMethod))
    return COptMethodDE_Type;

  if (dynamic_cast<COptMethodEP*>(optMethod))
    return COptMethodEP_Type;

  if (dynamic_cast<COptMethodGA*>(optMethod))
    return COptMethodGA_Type;

  if (dynamic_cast<COptMethodGASR*>(optMethod))
    return COptMethodGASR_Type;

  if (dynamic_cast<COptMethodHookeJeeves*>(optMethod))
    return COptMethodHookeJeeves_Type;

  if (dynamic_cast<COptMethodLevenbergMarquardt*>(optMethod))
    return COptMethodLevenbergMarquardt_Type;

  if (dynamic_cast<COptMethodNelderMead*>(optMethod))
    return COptMethodNelderMead_Type;

  if (dynamic_cast<COptMethodPraxis*>(optMethod))
    return COptMethodPraxis_Type;

  if (dynamic_cast<COptMethodSA*>(optMethod))
    return COptMethodSA_Type;

  if (dynamic_cast<COptMethodSRES*>(optMethod))
    return COptMethodSRES_Type;

  if (dynamic_cast<COptMethodSS*>(optMethod))
    return COptMethodSS_Type;

  if (dynamic_cast<COptMethodStatistics*>(optMethod))
    return COptMethodStatistics_Type;

  if (dynamic_cast<COptMethodSteepestDescent*>(optMethod))
    return COptMethodSteepestDescent_Type;

  if (dynamic_cast<CRandomSearch*>(optMethod))
    return CRandomSearch_Type;

  if (dynamic_cast<COptMethodTruncatedNewton*>(optMethod))
    return COptMethodTruncatedNewton_Type;

  return COptMethod_Type;
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
  CRootContainer::init(0, NULL, false);
}
