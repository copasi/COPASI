/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/local.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/11/23 16:41:08 $
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
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "trajectory/CTrajectoryMethod.h"
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

enum CLASS_TYPE
{
  CHEMICALEQUATION
  , CHEMICALEQUATIONELEMENT
  , CHEMICALEQUATIONELEMENTVECTOR
  , COMPARTMENT
  , COMPARTMENTVECTOR
  , COMPARTMENTVECTORN
  , COMPARTMENTVECTORNS
  , CONTAINER
  , EVALUATIONTREE
  , EVALUATIONTREEVECTOR
  , EVALUATIONTREEVECTORN
  , FUNCTION
  , FUNCTIONDB
  , FUNCTIONPARAMETER
  , FUNCTIONPARAMETERS
  , METABOLITE
  , METABVECTOR
  , METABVECTORN
  , METABVECTORNS
  , METHOD
  , MODEL
  , MODELENTITY
  , MODELVALUE
  , MODELVALUEVECTOR
  , MODELVALUEVECTORN
  , MOIETY
  , MOIETYVECTOR
  , OBJECT
  , OBJECTNAME
  , PARAMETER
  , PARAMETERGROUP
  , PARAMETERVECTOR
  , PROBLEM
  , REACTION
  , REACTIONVECTOR
  , REACTIONVECTORN
  , REACTIONVECTORNS
  , REPORTDEFINITION
  , REPORTDEFINITIONVECTOR
  , REPORTDEFINITIONVECTORN
  , STATICSTRING
  , TASK
  , TASKVECTOR
  , TASKVECTORN
  , TRAJECTORYMETHOD
  , TRAJECTORYPROBLEM
  , TRAJECTORYTASK
};

CLASS_TYPE getClassTypeForCEvaluationTree(const CEvaluationTree* pTree)
{
  CLASS_TYPE type = EVALUATIONTREE;
  if (pTree)
    {
      if (dynamic_cast<const CFunction*>(pTree))
        {
          type = FUNCTION;
        }
    }
  return type;
}

CLASS_TYPE getClassTypeForMethod(const CCopasiMethod* pMethod)
{
  CLASS_TYPE type = METHOD;
  if (pMethod)
    {
      if (dynamic_cast<const CTrajectoryMethod*>(pMethod))
        {
          type = TRAJECTORYMETHOD;
        }
    }
  return type;
}

CLASS_TYPE getClassTypeForProblem(const CCopasiProblem* pProblem)
{
  CLASS_TYPE type = PROBLEM;
  if (pProblem)
    {
      if (dynamic_cast<const CTrajectoryProblem*>(pProblem))
        {
          type = TRAJECTORYPROBLEM;
        }
    }
  return type;
}

CLASS_TYPE getClassTypeForParameterGroup(const CCopasiParameterGroup* pGroup)
{
  CLASS_TYPE type = PARAMETERGROUP;
  if (pGroup)
    {
      if (dynamic_cast<const CCopasiMethod*>(pGroup))
        {
          type = getClassTypeForMethod(static_cast<const CCopasiMethod*>(pGroup));
        }
      else if (dynamic_cast<const CCopasiProblem*>(pGroup))
        {
          type = getClassTypeForProblem(static_cast<const CCopasiProblem*>(pGroup));
        }
    }
  return type;
}

CLASS_TYPE getClassTypeForParameter(const CCopasiParameter* pParameter)
{
  CLASS_TYPE type = PARAMETER;
  if (pParameter)
    {
      if (dynamic_cast<const CCopasiParameterGroup*>(pParameter))
        {
          type = getClassTypeForParameterGroup(static_cast<const CCopasiParameterGroup*>(pParameter));
        }
    }
  return type;
}

CLASS_TYPE getClassTypeForTask(const CCopasiTask* pTask)
{
  CLASS_TYPE type = TASK;
  if (pTask)
    {
      if (dynamic_cast<const CTrajectoryTask*>(pTask))
        {
          type = TRAJECTORYTASK;
        }
    }
  return type;
}

CLASS_TYPE getClassTypeForModelEntity(const CModelEntity* pEntity)
{
  CLASS_TYPE type = MODELENTITY;
  if (pEntity)
    {
      if (dynamic_cast<const CMetab*>(pEntity))
        {
          type = METABOLITE;
        }
      else if (dynamic_cast<const CCompartment*>(pEntity))
        {
          type = COMPARTMENT;
        }
      else if (dynamic_cast<const CModelValue*>(pEntity))
        {
          type = MODELVALUE;
        }
      else if (dynamic_cast<const CModel*>(pEntity))
        {
          type = MODEL;
        }
    }
  return type;
}

CLASS_TYPE getClassTypeForContainer(const CCopasiContainer* container)
{
  CLASS_TYPE type = CONTAINER;
  if (container)
    {
      if (dynamic_cast<const CModelEntity*>(container))
        {
          type = getClassTypeForModelEntity(static_cast<const CModelEntity*>(container));
        }
      else if (container->isNameVector())
        {
          if (dynamic_cast<const TaskVectorN*>(container))
            {
              type = TASKVECTORN;
            }
          else if (dynamic_cast<const ModelValueVectorN*>(container))
            {
              type = MODELVALUEVECTORN;
            }
          else if (dynamic_cast<const MetabVectorNS*>(container))
            {
              type = METABVECTORNS;
            }
          else if (dynamic_cast<const CompartmentVectorNS*>(container))
            {
              type = COMPARTMENTVECTORNS;
            }
          else if (dynamic_cast<const ReactionVectorNS*>(container))
            {
              type = REACTIONVECTORNS;
            }
          else if (dynamic_cast<const CEvaluationTreeVectorN*>(container))
            {
              type = EVALUATIONTREEVECTORN;
            }
        }
      else if (container->isVector())
        {
          if (dynamic_cast<const MoietyVector*>(container))
            {
              type = MOIETYVECTOR;
            }
          else if (dynamic_cast<const MetabVector*>(container))
            {
              type = METABVECTOR;
            }
          else if (dynamic_cast<const ParameterVector*>(container))
            {
              type = PARAMETERVECTOR;
            }
          else if (dynamic_cast<const CChemEqElementVector*>(container))
            {
              type = CHEMICALEQUATIONELEMENTVECTOR;
            }
        }
      else if (dynamic_cast<const CEvaluationTree*>(container))
        {
          type = getClassTypeForCEvaluationTree(static_cast<const CEvaluationTree*>(container));
        }
      else if (dynamic_cast<const CCopasiTask*>(container))
        {
          type = getClassTypeForTask(static_cast<const CCopasiTask*>(container));
        }
      else if (dynamic_cast<const CCopasiParameter*>(container))
        {
          type = getClassTypeForParameter(static_cast<const CCopasiParameter*>(container));
        }
      else if (dynamic_cast<const CChemEq*>(container))
        {
          type = CHEMICALEQUATION;
        }
      else if (dynamic_cast<const CChemEqElement*>(container))
        {
          type = CHEMICALEQUATIONELEMENT;
        }
      else if (dynamic_cast<const CFunctionDB*>(container))
        {
          type = FUNCTIONDB;
        }
      else if (dynamic_cast<const CFunctionParameter*>(container))
        {
          type = FUNCTIONPARAMETER;
        }
      else if (dynamic_cast<const CFunctionParameters*>(container))
        {
          type = FUNCTIONPARAMETERS;
        }
      else if (dynamic_cast<const CMoiety*>(container))
        {
          type = MOIETY;
        }
      else if (dynamic_cast<const CReaction*>(container))
        {
          type = REACTION;
        }
    }
  return type;
}

CLASS_TYPE getClassTypeForObject(const CCopasiObject* pObject)
{
  CLASS_TYPE type = OBJECT;
  if (pObject)
    {
      if (dynamic_cast<const CCopasiContainer*>(pObject))
        {
          type = getClassTypeForContainer(static_cast<const CCopasiContainer*>(pObject));
        }
      else if (dynamic_cast<const CCopasiStaticString*>(pObject))
        {
          type = STATICSTRING;
        }
      else if (dynamic_cast<const CReportDefinition*>(pObject))
        {
          type = REPORTDEFINITION;
        }
    }
  return type;
}
