// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/local.cpp,v $
//   $Revision: 1.10.14.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/11/15 20:47:01 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include "report/CReportDefinitionVector.h"
#include "utilities/CAnnotatedMatrix.h"
#include "utilities/CMatrix.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "steadystate/CSteadyStateMethod.h"
#include "steadystate/CNewtonMethod.h"
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

#include "CopasiDataModel/CCopasiDataModel.h"

void initCopasi()
{
  CCopasiContainer::init();
  CCopasiDataModel::Global = new CCopasiDataModel();
  // !!! TODO !!! initialize COptions
}

jobject DownCast_COptTask(JNIEnv* jenv, COptTask* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CFitTask*>(pPointer))
    {
      // return a CFitTask
      jclass clazz = jenv->FindClass("org/COPASI/CFitTask");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CFitTask**)&cptr = static_cast<CFitTask*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else
    {// return a COptTask
      jclass clazz = jenv->FindClass("org/COPASI/COptTask");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(COptTask**)&cptr = static_cast<COptTask*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}

jobject DownCast_COptProblem(JNIEnv* jenv, COptProblem* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CFitProblem*>(pPointer))
    {
      // return a CFitProblem
      jclass clazz = jenv->FindClass("org/COPASI/CFitProblem");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CFitProblem**)&cptr = static_cast<CFitProblem*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else
    {// return a COptProblem
      jclass clazz = jenv->FindClass("org/COPASI/COptProblem");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(COptProblem**)&cptr = static_cast<COptProblem*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}

jobject DownCast_COptMethod(JNIEnv* jenv, COptMethod* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CFitMethod*>(pPointer))
    {
      // return a CFitMethod
      jclass clazz = jenv->FindClass("org/COPASI/CFitMethod");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CFitMethod**)&cptr = static_cast<CFitMethod*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else
    {// return a COptMethod
      jclass clazz = jenv->FindClass("org/COPASI/COptMethod");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(COptMethod**)&cptr = static_cast<COptMethod*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}

/*
jobject DownCast_CExperimentSet(JNIEnv* jenv, CExperimentSet* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CCrossValidationSet*>(pPointer))
  {
    // return a CCrossValidationSet
    jclass clazz = jenv->FindClass("org/COPASI/CCrossValidationSet");
    if (clazz)
    {
      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
      if (mid)
      {
        jlong cptr = 0;
        *(CCrossValidationSet**)&cptr = static_cast<CCrossValidationSet*>(pPointer);
        result = jenv->NewObject(clazz, mid, cptr, false);
      }
    }
  }
  else
  {// return a CExperimentSet
    jclass clazz = jenv->FindClass("org/COPASI/CExperimentSet");
    if (clazz)
    {
      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
      if (mid)
      {
        jlong cptr = 0;
        *(CExperimentSet**)&cptr = static_cast<CExperimentSet*>(pPointer);
        result = jenv->NewObject(clazz, mid, cptr, false);
      }
    }
  }
  return result;
}
 */

jobject DownCast_CFitItem(JNIEnv* jenv, CFitItem* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CFitConstraint*>(pPointer))
    {
      // return a CFitConstraint
      jclass clazz = jenv->FindClass("org/COPASI/CFitConstraint");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CFitConstraint**)&cptr = static_cast<CFitConstraint*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else
    {// return a CFitItem
      jclass clazz = jenv->FindClass("org/COPASI/CFitItem");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CFitItem**)&cptr = static_cast<CFitItem*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}

jobject DownCast_COptItem(JNIEnv* jenv, COptItem* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CFitItem*>(pPointer))
    {
      if (dynamic_cast<CFitConstraint*>(pPointer))
        {
          // return a CFitConstraint
          jclass clazz = jenv->FindClass("org/COPASI/CFitConstraint");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CFitConstraint**)&cptr = static_cast<CFitConstraint*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else
        {// return a CFitItem
          jclass clazz = jenv->FindClass("org/COPASI/CFitItem");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CFitItem**)&cptr = static_cast<CFitItem*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  else
    {
      // return a COptItem
      jclass clazz = jenv->FindClass("org/COPASI/COptItem");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(COptItem**)&cptr = static_cast<COptItem*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}

jobject DownCast_CCopasiAbstractArray(JNIEnv* jenv, CCopasiAbstractArray* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CCopasiArray*>(pPointer))
    {
      // return a CCopasiArray
      jclass clazz = jenv->FindClass("org/COPASI/CCopasiArray");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CCopasiArray**)&cptr = static_cast<CCopasiArray*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CCopasiMatrixInterface<CMatrix<C_FLOAT64> >*>(pPointer))
    {
      // return a CCopasiArray
      jclass clazz = jenv->FindClass("org/COPASI/AnnotatedFloatArray");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CCopasiMatrixInterface<CMatrix<C_FLOAT64> >**)&cptr = static_cast<CCopasiMatrixInterface<CMatrix<C_FLOAT64> >*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else
    {
      // return a CCopasiAbstractArray
      jclass clazz = jenv->FindClass("org/COPASI/CCopasiAbstractArray");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CCopasiAbstractArray**)&cptr = static_cast<CCopasiAbstractArray*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}

jobject DownCast_CModelEntity(JNIEnv* jenv, CModelEntity* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CCompartment*>(pPointer))
    {
      // return a CCompartment
      jclass clazz = jenv->FindClass("org/COPASI/CCompartment");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CCompartment**)&cptr = static_cast<CCompartment*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CMetab*>(pPointer))
    {
      // return a CMetab
      jclass clazz = jenv->FindClass("org/COPASI/CMetab");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CMetab**)&cptr = static_cast<CMetab*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CModel*>(pPointer))
    {
      // return a CModel
      jclass clazz = jenv->FindClass("org/COPASI/CModel");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CModel**)&cptr = static_cast<CModel*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CModelValue*>(pPointer))
    {
      // return a CModelValue
      jclass clazz = jenv->FindClass("org/COPASI/CModelValue");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CModelValue**)&cptr = static_cast<CModelValue*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else
    {
      // return a CModelEntity
      jclass clazz = jenv->FindClass("org/COPASI/CModelEntity");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CModelEntity**)&cptr = static_cast<CModelEntity*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}

jobject DownCast_CEvaluationTree(JNIEnv* jenv, CEvaluationTree* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CFunction*>(pPointer))
    {
      // return a CFunction
      jclass clazz = jenv->FindClass("org/COPASI/CFunction");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CFunction**)&cptr = static_cast<CFunction*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else
    {
      // return a CEvaluationTree
      jclass clazz = jenv->FindClass("org/COPASI/CEvaluationTree");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CEvaluationTree**)&cptr = static_cast<CEvaluationTree*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}

jobject DownCast_CCopasiTask(JNIEnv* jenv, CCopasiTask* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CTrajectoryTask*>(pPointer))
    {
      // return a CTrajectoryTask
      jclass clazz = jenv->FindClass("org/COPASI/CTrajectoryTask");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CTrajectoryTask**)&cptr = static_cast<CTrajectoryTask*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CSteadyStateTask*>(pPointer))
    {
      // return a CSteadyStateTask
      jclass clazz = jenv->FindClass("org/COPASI/CSteadyStateTask");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CSteadyStateTask**)&cptr = static_cast<CSteadyStateTask*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CScanTask*>(pPointer))
    {
      // return a CScanTask
      jclass clazz = jenv->FindClass("org/COPASI/CScanTask");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CScanTask**)&cptr = static_cast<CScanTask*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<COptTask*>(pPointer))
    {
      if (dynamic_cast<CFitTask*>(pPointer))
        {
          // return a CFitTask
          jclass clazz = jenv->FindClass("org/COPASI/CFitTask");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CFitTask**)&cptr = static_cast<CFitTask*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else
        {
          // return a COptTask
          jclass clazz = jenv->FindClass("org/COPASI/COptTask");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(COptTask**)&cptr = static_cast<COptTask*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  else if (dynamic_cast<CLyapTask*>(pPointer))
    {
      // return a CLyapTask
      jclass clazz = jenv->FindClass("org/COPASI/CLyapTask");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CLyapTask**)&cptr = static_cast<CLyapTask*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else
    {
      // return a CCopasiTask
      jclass clazz = jenv->FindClass("org/COPASI/CCopasiTask");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CCopasiTask**)&cptr = static_cast<CCopasiTask*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}

jobject DownCast_CCopasiMethod(JNIEnv* jenv, CCopasiMethod* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CTrajectoryMethod*>(pPointer))
    {
      // return a CTrajectoryMethod
      jclass clazz = jenv->FindClass("org/COPASI/CTrajectoryMethod");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CTrajectoryMethod**)&cptr = static_cast<CTrajectoryMethod*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CNewtonMethod*>(pPointer))
    {
      // return a CNewtonMethod
      jclass clazz = jenv->FindClass("org/COPASI/CNewtonMethod");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CNewtonMethod**)&cptr = static_cast<CNewtonMethod*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CSteadyStateMethod*>(pPointer))
    {
      // return a CSteadyStateMethod
      jclass clazz = jenv->FindClass("org/COPASI/CSteadyStateMethod");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CSteadyStateMethod**)&cptr = static_cast<CSteadyStateMethod*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CScanMethod*>(pPointer))
    {
      // return a CScanMethod
      jclass clazz = jenv->FindClass("org/COPASI/CScanMethod");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CScanMethod**)&cptr = static_cast<CScanMethod*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<COptMethod*>(pPointer))
    {
      if (dynamic_cast<CFitMethod*>(pPointer))
        {
          // return a CFitMethod
          jclass clazz = jenv->FindClass("org/COPASI/CFitMethod");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CFitMethod**)&cptr = static_cast<CFitMethod*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else
        {// return a COptMethod
          jclass clazz = jenv->FindClass("org/COPASI/COptMethod");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(COptMethod**)&cptr = static_cast<COptMethod*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  else if (dynamic_cast<CLyapMethod*>(pPointer))
    {
      // return a CLyapMethod
      jclass clazz = jenv->FindClass("org/COPASI/CLyapMethod");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CLyapMethod**)&cptr = static_cast<CLyapMethod*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else
    {
      // return a CCopasiMethod
      jclass clazz = jenv->FindClass("org/COPASI/CCopasiMethod");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CCopasiMethod**)&cptr = static_cast<CCopasiMethod*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}

jobject DownCast_CCopasiProblem(JNIEnv* jenv, CCopasiProblem* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CTrajectoryProblem*>(pPointer))
    {
      // return a CTrajectoryProblem
      jclass clazz = jenv->FindClass("org/COPASI/CTrajectoryProblem");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CTrajectoryProblem**)&cptr = static_cast<CTrajectoryProblem*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CSteadyStateProblem*>(pPointer))
    {
      // return a CSteadyStateProblem
      jclass clazz = jenv->FindClass("org/COPASI/CSteadyStateProblem");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CSteadyStateProblem**)&cptr = static_cast<CSteadyStateProblem*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CScanProblem*>(pPointer))
    {
      // return a CScanProblem
      jclass clazz = jenv->FindClass("org/COPASI/CScanProblem");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CScanProblem**)&cptr = static_cast<CScanProblem*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<COptProblem*>(pPointer))
    {
      if (dynamic_cast<CFitProblem*>(pPointer))
        {
          // return a CFitProblem
          jclass clazz = jenv->FindClass("org/COPASI/CFitProblem");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CFitProblem**)&cptr = static_cast<CFitProblem*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else
        {
          // return a COptProblem
          jclass clazz = jenv->FindClass("org/COPASI/COptProblem");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(COptProblem**)&cptr = static_cast<COptProblem*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  else if (dynamic_cast<CLyapProblem*>(pPointer))
    {
      // return a CLyapProblem
      jclass clazz = jenv->FindClass("org/COPASI/CLyapProblem");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CLyapProblem**)&cptr = static_cast<CLyapProblem*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else
    {
      // return a CCopasiProblem
      jclass clazz = jenv->FindClass("org/COPASI/CCopasiProblem");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CCopasiProblem**)&cptr = static_cast<CCopasiProblem*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}

jobject DownCast_CCopasiParameterGroup(JNIEnv* jenv, CCopasiParameterGroup* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CCopasiMethod*>(pPointer))
    {
      if (dynamic_cast<CTrajectoryMethod*>(pPointer))
        {
          // return a CTrajectoryMethod
          jclass clazz = jenv->FindClass("org/COPASI/CTrajectoryMethod");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CTrajectoryMethod**)&cptr = static_cast<CTrajectoryMethod*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CNewtonMethod*>(pPointer))
        {
          // return a CNewtonMethod
          jclass clazz = jenv->FindClass("org/COPASI/CNewtonMethod");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CNewtonMethod**)&cptr = static_cast<CNewtonMethod*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CSteadyStateMethod*>(pPointer))
        {
          // return a CSteadyStateMethod
          jclass clazz = jenv->FindClass("org/COPASI/CSteadyStateMethod");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CSteadyStateMethod**)&cptr = static_cast<CSteadyStateMethod*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CScanMethod*>(pPointer))
        {
          // return a CScanMethod
          jclass clazz = jenv->FindClass("org/COPASI/CScanMethod");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CScanMethod**)&cptr = static_cast<CScanMethod*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<COptMethod*>(pPointer))
        {
          if (dynamic_cast<CFitMethod*>(pPointer))
            {
              // return a CFitMethod
              jclass clazz = jenv->FindClass("org/COPASI/CFitMethod");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CFitMethod**)&cptr = static_cast<CFitMethod*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else
            {
              // return a COptMethod
              jclass clazz = jenv->FindClass("org/COPASI/COptMethod");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(COptMethod**)&cptr = static_cast<COptMethod*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
      else if (dynamic_cast<CLyapMethod*>(pPointer))
        {
          // return a CLyapMethod
          jclass clazz = jenv->FindClass("org/COPASI/CLyapMethod");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CLyapMethod**)&cptr = static_cast<CLyapMethod*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else
        {
          // return a CCopasiMethod
          jclass clazz = jenv->FindClass("org/COPASI/CCopasiMethod");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CCopasiMethod**)&cptr = static_cast<CCopasiMethod*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  else if (dynamic_cast<CCopasiProblem*>(pPointer))
    {
      if (dynamic_cast<CTrajectoryProblem*>(pPointer))
        {
          // return a CTrajectoryProblem
          jclass clazz = jenv->FindClass("org/COPASI/CTrajectoryProblem");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CTrajectoryProblem**)&cptr = static_cast<CTrajectoryProblem*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CSteadyStateProblem*>(pPointer))
        {
          // return a CSteadyStateProblem
          jclass clazz = jenv->FindClass("org/COPASI/CSteadyStateProblem");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CSteadyStateProblem**)&cptr = static_cast<CSteadyStateProblem*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CScanProblem*>(pPointer))
        {
          // return a CScanProblem
          jclass clazz = jenv->FindClass("org/COPASI/CScanProblem");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CScanProblem**)&cptr = static_cast<CScanProblem*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<COptProblem*>(pPointer))
        {
          if (dynamic_cast<CFitProblem*>(pPointer))
            {
              // return a CFitProblem
              jclass clazz = jenv->FindClass("org/COPASI/CFitProblem");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CFitProblem**)&cptr = static_cast<CFitProblem*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else
            {// return a COptProblem
              jclass clazz = jenv->FindClass("org/COPASI/COptProblem");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(COptProblem**)&cptr = static_cast<COptProblem*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
      else if (dynamic_cast<CLyapProblem*>(pPointer))
        {
          // return a CLyapProblem
          jclass clazz = jenv->FindClass("org/COPASI/CLyapProblem");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CLyapProblem**)&cptr = static_cast<CLyapProblem*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else
        {
          // return a CCopasiProblem
          jclass clazz = jenv->FindClass("org/COPASI/CCopasiProblem");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CCopasiProblem**)&cptr = static_cast<CCopasiProblem*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  else if (dynamic_cast<COptItem*>(pPointer))
    {
      if (dynamic_cast<CFitItem*>(pPointer))
        {
          if (dynamic_cast<CFitConstraint*>(pPointer))
            {
              // return a CFitConstraint
              jclass clazz = jenv->FindClass("org/COPASI/CFitConstraint");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CFitConstraint**)&cptr = static_cast<CFitConstraint*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else
            {// return a CFitItem
              jclass clazz = jenv->FindClass("org/COPASI/CFitItem");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CFitItem**)&cptr = static_cast<CFitItem*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
      else
        {// return a COptItem
          jclass clazz = jenv->FindClass("org/COPASI/COptItem");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(COptItem**)&cptr = static_cast<COptItem*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  else if (dynamic_cast<CExperiment*>(pPointer))
    {
      // return a CExperiment
      jclass clazz = jenv->FindClass("org/COPASI/CExperiment");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CExperiment**)&cptr = static_cast<CExperiment*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CExperimentSet*>(pPointer))
    {
      /*
      if (dynamic_cast<CCrossValidationSet*>(pPointer))
      {
        // return a CCrossValidationSet
        jclass clazz = jenv->FindClass("org/COPASI/CCrossValidationSet");
        if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
          {
            jlong cptr = 0;
            *(CCrossValidationSet**)&cptr = static_cast<CCrossValidationSet*>(pPointer);
            result = jenv->NewObject(clazz, mid, cptr, false);
          }
        }
      }
      else
      {*/
      // return a CExperimentSet
      jclass clazz = jenv->FindClass("org/COPASI/CExperimentSet");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CExperimentSet**)&cptr = static_cast<CExperimentSet*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
      /*}*/
    }
  else if (dynamic_cast<CExperimentObjectMap*>(pPointer))
    {
      // return a CExperimentObjectMap
      jclass clazz = jenv->FindClass("org/COPASI/CExperimentObjectMap");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CExperimentObjectMap**)&cptr = static_cast<CExperimentObjectMap*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else
    {
      // return a CCopasiParameterGroup
      jclass clazz = jenv->FindClass("org/COPASI/CCopasiParameterGroup");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CCopasiParameterGroup**)&cptr = static_cast<CCopasiParameterGroup*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}

jobject DownCast_CCopasiParameter(JNIEnv* jenv, CCopasiParameter* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CCopasiParameterGroup*>(pPointer))
    {
      if (dynamic_cast<CCopasiMethod*>(pPointer))
        {
          if (dynamic_cast<CTrajectoryMethod*>(pPointer))
            {
              // return a CTrajectoryMethod
              jclass clazz = jenv->FindClass("org/COPASI/CTrajectoryMethod");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CTrajectoryMethod**)&cptr = static_cast<CTrajectoryMethod*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<CNewtonMethod*>(pPointer))
            {
              // return a CNewtonMethod
              jclass clazz = jenv->FindClass("org/COPASI/CNewtonMethod");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CNewtonMethod**)&cptr = static_cast<CNewtonMethod*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<CSteadyStateMethod*>(pPointer))
            {
              // return a CSteadyStateMethod
              jclass clazz = jenv->FindClass("org/COPASI/CSteadyStateMethod");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CSteadyStateMethod**)&cptr = static_cast<CSteadyStateMethod*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<CScanMethod*>(pPointer))
            {
              // return a CScanMethod
              jclass clazz = jenv->FindClass("org/COPASI/CScanMethod");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CScanMethod**)&cptr = static_cast<CScanMethod*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<COptMethod*>(pPointer))
            {
              if (dynamic_cast<CFitMethod*>(pPointer))
                {
                  // return a CFitMethod
                  jclass clazz = jenv->FindClass("org/COPASI/CFitMethod");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CFitMethod**)&cptr = static_cast<CFitMethod*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else
                {
                  // return a COptMethod
                  jclass clazz = jenv->FindClass("org/COPASI/COptMethod");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(COptMethod**)&cptr = static_cast<COptMethod*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<CLyapMethod*>(pPointer))
            {
              // return a CLyapMethod
              jclass clazz = jenv->FindClass("org/COPASI/CLyapMethod");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CLyapMethod**)&cptr = static_cast<CLyapMethod*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else
            {
              // return a CCopasiMethod
              jclass clazz = jenv->FindClass("org/COPASI/CCopasiMethod");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CCopasiMethod**)&cptr = static_cast<CCopasiMethod*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
      else if (dynamic_cast<CCopasiProblem*>(pPointer))
        {
          if (dynamic_cast<CTrajectoryProblem*>(pPointer))
            {
              // return a CTrajectoryProblem
              jclass clazz = jenv->FindClass("org/COPASI/CTrajectoryProblem");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CTrajectoryProblem**)&cptr = static_cast<CTrajectoryProblem*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<CSteadyStateProblem*>(pPointer))
            {
              // return a CSteadyStateProblem
              jclass clazz = jenv->FindClass("org/COPASI/CSteadyStateProblem");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CSteadyStateProblem**)&cptr = static_cast<CSteadyStateProblem*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<CScanProblem*>(pPointer))
            {
              // return a CScanProblem
              jclass clazz = jenv->FindClass("org/COPASI/CScanProblem");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CScanProblem**)&cptr = static_cast<CScanProblem*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<COptProblem*>(pPointer))
            {
              if (dynamic_cast<CFitProblem*>(pPointer))
                {
                  // return a CFitProblem
                  jclass clazz = jenv->FindClass("org/COPASI/CFitProblem");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CFitProblem**)&cptr = static_cast<CFitProblem*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else
                {
                  // return a COptProblem
                  jclass clazz = jenv->FindClass("org/COPASI/COptProblem");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(COptProblem**)&cptr = static_cast<COptProblem*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<CLyapProblem*>(pPointer))
            {
              // return a CLyapProblem
              jclass clazz = jenv->FindClass("org/COPASI/CLyapProblem");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CLyapProblem**)&cptr = static_cast<CLyapProblem*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else
            {
              // return a CCopasiProblem
              jclass clazz = jenv->FindClass("org/COPASI/CCopasiProblem");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CCopasiProblem**)&cptr = static_cast<CCopasiProblem*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
      else if (dynamic_cast<COptItem*>(pPointer) != NULL)
        {
          if (dynamic_cast<CFitItem*>(pPointer))
            {
              if (dynamic_cast<CFitConstraint*>(pPointer))
                {
                  // return a CFitConstraint
                  jclass clazz = jenv->FindClass("org/COPASI/CFitConstraint");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CFitConstraint**)&cptr = static_cast<CFitConstraint*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else
                {// return a CFitItem
                  jclass clazz = jenv->FindClass("org/COPASI/CFitItem");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CFitItem**)&cptr = static_cast<CFitItem*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else
            {
              // return a COptItem
              jclass clazz = jenv->FindClass("org/COPASI/COptItem");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(COptItem**)&cptr = static_cast<COptItem*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
      else if (dynamic_cast<CExperimentSet*>(pPointer))
        {
          /*
          if (dynamic_cast<CCrossValidationSet*>(pPointer))
          {
            // return a CCrossValidationSet
            jclass clazz = jenv->FindClass("org/COPASI/CCrossValidationSet");
            if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
              {
                jlong cptr = 0;
                *(CCrossValidationSet**)&cptr = static_cast<CCrossValidationSet*>(pPointer);
                result = jenv->NewObject(clazz, mid, cptr, false);
              }
            }
          }
          else
          {*/
          // return a CExperimentSet
          jclass clazz = jenv->FindClass("org/COPASI/CExperimentSet");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CExperimentSet**)&cptr = static_cast<CExperimentSet*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
          /*}*/
        }
      else if (dynamic_cast<CExperimentObjectMap*>(pPointer))
        {
          // return a CExperimentObjectMap
          jclass clazz = jenv->FindClass("org/COPASI/CExperimentObjectMap");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CExperimentObjectMap**)&cptr = static_cast<CExperimentObjectMap*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CExperiment*>(pPointer))
        {
          // return a CExperiment
          jclass clazz = jenv->FindClass("org/COPASI/CExperiment");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CExperiment**)&cptr = static_cast<CExperiment*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else
        {
          // return a CCopasiParameterGroup
          jclass clazz = jenv->FindClass("org/COPASI/CCopasiParameterGroup");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CCopasiParameterGroup**)&cptr = static_cast<CCopasiParameterGroup*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  else
    {
      // return a CCopasiParameter
      jclass clazz = jenv->FindClass("org/COPASI/CCopasiParameter");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CCopasiParameter**)&cptr = static_cast<CCopasiParameter*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}

jobject DownCast_CCopasiContainer(JNIEnv* jenv, CCopasiContainer* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CChemEq*>(pPointer))
    {
      // return a CChemEq
      jclass clazz = jenv->FindClass("org/COPASI/CChemEq");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CChemEq**)&cptr = static_cast<CChemEq*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CChemEqElement*>(pPointer))
    {
      // return a CChemEqElement
      jclass clazz = jenv->FindClass("org/COPASI/CChemEqElement");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CChemEqElement**)&cptr = static_cast<CChemEqElement*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CCopasiTask*>(pPointer))
    {
      if (dynamic_cast<CTrajectoryTask*>(pPointer))
        {
          // return a CTrajectoryTask
          jclass clazz = jenv->FindClass("org/COPASI/CTrajectoryTask");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CTrajectoryTask**)&cptr = static_cast<CTrajectoryTask*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CSteadyStateTask*>(pPointer))
        {
          // return a CSteadyStateTask
          jclass clazz = jenv->FindClass("org/COPASI/CSteadyStateTask");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CSteadyStateTask**)&cptr = static_cast<CSteadyStateTask*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CScanTask*>(pPointer))
        {
          // return a CScanTask
          jclass clazz = jenv->FindClass("org/COPASI/CScanTask");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CScanTask**)&cptr = static_cast<CScanTask*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<COptTask*>(pPointer))
        {
          if (dynamic_cast<CFitTask*>(pPointer))
            {
              // return a CFitTask
              jclass clazz = jenv->FindClass("org/COPASI/CFitTask");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CFitTask**)&cptr = static_cast<CFitTask*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else
            {
              // return a COptTask
              jclass clazz = jenv->FindClass("org/COPASI/COptTask");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(COptTask**)&cptr = static_cast<COptTask*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
      else if (dynamic_cast<CLyapTask*>(pPointer))
        {
          // return a CLyapTask
          jclass clazz = jenv->FindClass("org/COPASI/CLyapTask");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CLyapTask**)&cptr = static_cast<CLyapTask*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else
        {
          // return a CCopasiTask
          jclass clazz = jenv->FindClass("org/COPASI/CCopasiTask");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CCopasiTask**)&cptr = static_cast<CCopasiTask*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  else if (dynamic_cast<CCopasiParameter*>(pPointer))
    {
      if (dynamic_cast<CCopasiParameterGroup*>(pPointer))
        {
          if (dynamic_cast<CCopasiMethod*>(pPointer))
            {
              if (dynamic_cast<CTrajectoryMethod*>(pPointer))
                {
                  // return a CTrajectoryMethod
                  jclass clazz = jenv->FindClass("org/COPASI/CTrajectoryMethod");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CTrajectoryMethod**)&cptr = static_cast<CTrajectoryMethod*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else if (dynamic_cast<CNewtonMethod*>(pPointer))
                {
                  // return a CNewtonMethod
                  jclass clazz = jenv->FindClass("org/COPASI/CNewtonMethod");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CNewtonMethod**)&cptr = static_cast<CNewtonMethod*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else if (dynamic_cast<CSteadyStateMethod*>(pPointer))
                {
                  // return a CSteadyStateMethod
                  jclass clazz = jenv->FindClass("org/COPASI/CSteadyStateMethod");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CSteadyStateMethod**)&cptr = static_cast<CSteadyStateMethod*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else if (dynamic_cast<CScanMethod*>(pPointer))
                {
                  // return a CScanMethod
                  jclass clazz = jenv->FindClass("org/COPASI/CScanMethod");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CScanMethod**)&cptr = static_cast<CScanMethod*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else if (dynamic_cast<COptMethod*>(pPointer))
                {
                  if (dynamic_cast<CFitMethod*>(pPointer))
                    {
                      // return a CFitMethod
                      jclass clazz = jenv->FindClass("org/COPASI/CFitMethod");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CFitMethod**)&cptr = static_cast<CFitMethod*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else
                    {
                      // return a COptMethod
                      jclass clazz = jenv->FindClass("org/COPASI/COptMethod");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(COptMethod**)&cptr = static_cast<COptMethod*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else if (dynamic_cast<CLyapMethod*>(pPointer))
                {
                  // return a CLyapMethod
                  jclass clazz = jenv->FindClass("org/COPASI/CLyapMethod");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CLyapMethod**)&cptr = static_cast<CLyapMethod*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else
                {
                  // return a CCopasiMethod
                  jclass clazz = jenv->FindClass("org/COPASI/CCopasiMethod");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CCopasiMethod**)&cptr = static_cast<CCopasiMethod*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<CCopasiProblem*>(pPointer))
            {
              if (dynamic_cast<CTrajectoryProblem*>(pPointer))
                {
                  // return a CTrajectoryProblem
                  jclass clazz = jenv->FindClass("org/COPASI/CTrajectoryProblem");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CTrajectoryProblem**)&cptr = static_cast<CTrajectoryProblem*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else if (dynamic_cast<CSteadyStateProblem*>(pPointer))
                {
                  // return a CSteadyStateProblem
                  jclass clazz = jenv->FindClass("org/COPASI/CSteadyStateProblem");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CSteadyStateProblem**)&cptr = static_cast<CSteadyStateProblem*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else if (dynamic_cast<CScanProblem*>(pPointer))
                {
                  // return a CScanProblem
                  jclass clazz = jenv->FindClass("org/COPASI/CScanProblem");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CScanProblem**)&cptr = static_cast<CScanProblem*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else if (dynamic_cast<COptProblem*>(pPointer))
                {
                  if (dynamic_cast<CFitProblem*>(pPointer))
                    {
                      // return a CFitProblem
                      jclass clazz = jenv->FindClass("org/COPASI/CFitProblem");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CFitProblem**)&cptr = static_cast<CFitProblem*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else
                    {
                      // return a COptProblem
                      jclass clazz = jenv->FindClass("org/COPASI/COptProblem");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(COptProblem**)&cptr = static_cast<COptProblem*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else if (dynamic_cast<CLyapProblem*>(pPointer))
                {
                  // return a CLyapProblem
                  jclass clazz = jenv->FindClass("org/COPASI/CScanProblem");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CLyapProblem**)&cptr = static_cast<CLyapProblem*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else
                {
                  // return a CCopasiProblem
                  jclass clazz = jenv->FindClass("org/COPASI/CCopasiProblem");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CCopasiProblem**)&cptr = static_cast<CCopasiProblem*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<COptItem*>(pPointer) != NULL)
            {
              if (dynamic_cast<CFitItem*>(pPointer))
                {
                  if (dynamic_cast<CFitConstraint*>(pPointer))
                    {
                      // return a CFitConstraint
                      jclass clazz = jenv->FindClass("org/COPASI/CFitConstraint");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CFitConstraint**)&cptr = static_cast<CFitConstraint*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else
                    {// return a CFitItem
                      jclass clazz = jenv->FindClass("org/COPASI/CFitItem");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CFitItem**)&cptr = static_cast<CFitItem*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else
                {
                  // return a COptItem
                  jclass clazz = jenv->FindClass("org/COPASI/COptItem");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(COptItem**)&cptr = static_cast<COptItem*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<CExperimentSet*>(pPointer))
            {
              /*
              if (dynamic_cast<CCrossValidationSet*>(pPointer))
              {
                // return a CCrossValidationSet
                jclass clazz = jenv->FindClass("org/COPASI/CCrossValidationSet");
                if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                  {
                    jlong cptr = 0;
                    *(CCrossValidationSet**)&cptr = static_cast<CCrossValidationSet*>(pPointer);
                    result = jenv->NewObject(clazz, mid, cptr, false);
                  }
                }
              }
              else
              {*/
              // return a CExperimentSet
              jclass clazz = jenv->FindClass("org/COPASI/CExperimentSet");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CExperimentSet**)&cptr = static_cast<CExperimentSet*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
              /*}*/
            }
          else if (dynamic_cast<CExperimentObjectMap*>(pPointer))
            {
              // return a CExperimentObjectMap
              jclass clazz = jenv->FindClass("org/COPASI/CExperimentObjectMap");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CExperimentObjectMap**)&cptr = static_cast<CExperimentObjectMap*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<CExperiment*>(pPointer))
            {
              // return a CExperiment
              jclass clazz = jenv->FindClass("org/COPASI/CExperiment");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CExperiment**)&cptr = static_cast<CExperiment*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else
            {
              // return a CCopasiParameterGroup
              jclass clazz = jenv->FindClass("org/COPASI/CCopasiParameterGroup");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CCopasiParameterGroup**)&cptr = static_cast<CCopasiParameterGroup*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
      else
        {
          // return a CCopasiParameter
          jclass clazz = jenv->FindClass("org/COPASI/CCopasiParameter");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CCopasiParameter**)&cptr = static_cast<CCopasiParameter*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  else if (dynamic_cast<CEvaluationTree*>(pPointer))
    {
      if (dynamic_cast<CFunction*>(pPointer))
        {
          // return a CFunction
          jclass clazz = jenv->FindClass("org/COPASI/CFunction");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CFunction**)&cptr = static_cast<CFunction*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else
        {
          // return a CEvaluationTree
          jclass clazz = jenv->FindClass("org/COPASI/CEvaluationTree");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CEvaluationTree**)&cptr = static_cast<CEvaluationTree*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  else if (dynamic_cast<CFunctionDB*>(pPointer))
    {
      // return a CFunctionDB
      jclass clazz = jenv->FindClass("org/COPASI/CFunctionDB");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CFunctionDB**)&cptr = static_cast<CFunctionDB*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CFunctionParameter*>(pPointer))
    {
      // return a CFunctionParameter
      jclass clazz = jenv->FindClass("org/COPASI/CFunctionParameter");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CFunctionParameter**)&cptr = static_cast<CFunctionParameter*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CFunctionParameters*>(pPointer))
    {
      // return a CFunctionParameters
      jclass clazz = jenv->FindClass("org/COPASI/CFunctionParameters");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CFunctionParameters**)&cptr = static_cast<CFunctionParameters*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CModelEntity*>(pPointer))
    {
      if (dynamic_cast<CCompartment*>(pPointer))
        {
          // return a CCompartment
          jclass clazz = jenv->FindClass("org/COPASI/CCompartment");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CCompartment**)&cptr = static_cast<CCompartment*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CMetab*>(pPointer))
        {
          // return a CMetab
          jclass clazz = jenv->FindClass("org/COPASI/CMetab");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CMetab**)&cptr = static_cast<CMetab*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CModel*>(pPointer))
        {
          // return a CModel
          jclass clazz = jenv->FindClass("org/COPASI/CModel");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CModel**)&cptr = static_cast<CModel*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CModelValue*>(pPointer))
        {
          // return a CModelValue
          jclass clazz = jenv->FindClass("org/COPASI/CModelValue");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CModelValue**)&cptr = static_cast<CModelValue*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else
        {
          // return a CModelEntity
          jclass clazz = jenv->FindClass("org/COPASI/CModelEntity");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CModelEntity**)&cptr = static_cast<CModelEntity*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  else if (dynamic_cast<CMoiety*>(pPointer))
    {
      // return a CMoiety
      jclass clazz = jenv->FindClass("org/COPASI/CMoiety");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CMoiety**)&cptr = static_cast<CMoiety*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CReaction*>(pPointer))
    {
      // return a CReaction
      jclass clazz = jenv->FindClass("org/COPASI/CReaction");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CReaction**)&cptr = static_cast<CReaction*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CReport*>(pPointer))
    {
      // return a CReport
      jclass clazz = jenv->FindClass("org/COPASI/CReport");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CReport**)&cptr = static_cast<CReport*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CFittingPoint*>(pPointer))
    {
      // return a CFittingPoint
      jclass clazz = jenv->FindClass("org/COPASI/CFittingPoint");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CFittingPoint**)&cptr = static_cast<CFittingPoint*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
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
                  jclass clazz = jenv->FindClass("org/COPASI/TaskVectorN");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(TaskVectorN**)&cptr = static_cast<TaskVectorN*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else
                {
                  // return a TaskVector
                  jclass clazz = jenv->FindClass("org/COPASI/TaskVector");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(TaskVector**)&cptr = static_cast<TaskVector*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<CCopasiVector<CModelValue>* >(pPointer))
            {
              if (dynamic_cast<CCopasiVectorN<CModelValue>* >(pPointer))
                {
                  // return a ModelValueVectorN
                  jclass clazz = jenv->FindClass("org/COPASI/ModelValueVectorN");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(ModelValueVectorN**)&cptr = static_cast<ModelValueVectorN*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else
                {
                  // return a ModelValueVector
                  jclass clazz = jenv->FindClass("org/COPASI/ModelValueVector");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(ModelValueVector**)&cptr = static_cast<ModelValueVector*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<CCopasiVector<CReportDefinition>* >(pPointer))
            {
              if (dynamic_cast<CCopasiVectorN<CReportDefinition>* >(pPointer))
                {
                  // return a CCReportDefinitionVectorN
                  jclass clazz = jenv->FindClass("org/COPASI/CReportDefinitionVectorN");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CReportDefinitionVectorN**)&cptr = static_cast<CReportDefinitionVectorN*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else
                {
                  // return a CReportDefinitionVector
                  jclass clazz = jenv->FindClass("org/COPASI/CReportDefinitionVector");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CReportDefinitionVector**)&cptr = static_cast<CReportDefinitionVector*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<CCopasiVector<CMoiety>* >(pPointer))
            {
              // return a MoietyVector
              jclass clazz = jenv->FindClass("org/COPASI/MoietyVector");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(MoietyVector**)&cptr = static_cast<MoietyVector*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<CCopasiVector<CMetab>* >(pPointer))
            {
              if (dynamic_cast<CCopasiVectorN<CMetab>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorNS<CMetab>* >(pPointer))
                    {
                      // return a MetabVectorNS
                      jclass clazz = jenv->FindClass("org/COPASI/MetabVectorNS");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(MetabVectorNS**)&cptr = static_cast<MetabVectorNS*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else
                    {
                      // return a MetabVectorN
                      jclass clazz = jenv->FindClass("org/COPASI/MetabVectorN");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(MetabVectorN**)&cptr = static_cast<MetabVectorN*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else
                {
                  // return a MetabVector
                  jclass clazz = jenv->FindClass("org/COPASI/MetabVector");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(MetabVector**)&cptr = static_cast<MetabVector*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<CCopasiVector<CCompartment>* >(pPointer))
            {
              if (dynamic_cast<CCopasiVectorN<CCompartment>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorNS<CCompartment>* >(pPointer))
                    {
                      // return a CompartmentVectorNS
                      jclass clazz = jenv->FindClass("org/COPASI/CompartmentVectorNS");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CompartmentVectorNS**)&cptr = static_cast<CompartmentVectorNS*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else
                    {
                      // return a CompartmentVectorN
                      jclass clazz = jenv->FindClass("org/COPASI/CompartmentVectorN");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CompartmentVectorN**)&cptr = static_cast<CompartmentVectorN*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else
                {
                  // return a CompartmentVector
                  jclass clazz = jenv->FindClass("org/COPASI/CompartmentVector");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CompartmentVector**)&cptr = static_cast<CompartmentVector*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<CCopasiVector<CReaction>* >(pPointer))
            {
              if (dynamic_cast<CCopasiVectorN<CReaction>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorNS<CReaction>* >(pPointer))
                    {
                      // return a ReactionVectorNS
                      jclass clazz = jenv->FindClass("org/COPASI/ReactionVectorNS");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(ReactionVectorNS**)&cptr = static_cast<ReactionVectorNS*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else
                    {
                      // return a ReactionVectorN
                      jclass clazz = jenv->FindClass("org/COPASI/ReactionVectorN");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(ReactionVectorN**)&cptr = static_cast<ReactionVectorN*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else
                {
                  // return a ReactionVector
                  jclass clazz = jenv->FindClass("org/COPASI/ReactionVector");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(ReactionVector**)&cptr = static_cast<ReactionVector*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<CCopasiVector<CEvaluationTree>* >(pPointer))
            {
              if (dynamic_cast<CCopasiVectorN<CEvaluationTree>* >(pPointer))
                {
                  // return a CEvaluationTreeVectorN
                  jclass clazz = jenv->FindClass("org/COPASI/CEvaluationTreeVectorN");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CEvaluationTreeVectorN**)&cptr = static_cast<CEvaluationTreeVectorN*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else
                {
                  // return a CEvaluationTreeVector
                  jclass clazz = jenv->FindClass("org/COPASI/CEvaluationTreeVector");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CEvaluationTreeVector**)&cptr = static_cast<CEvaluationTreeVector*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<CCopasiVector<CChemEqElement>* >(pPointer))
            {
              // return a CChemEqElementVector
              jclass clazz = jenv->FindClass("org/COPASI/CChemEqElementVector");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CChemEqElementVector**)&cptr = static_cast<CChemEqElementVector*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
      else if (dynamic_cast<CArrayAnnotation*>(pPointer))
        {
          // return a CArrayAnnotation
          jclass clazz = jenv->FindClass("org/COPASI/CArrayAnnotation");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CArrayAnnotation**)&cptr = static_cast<CArrayAnnotation*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else
        {
          // return a CCopasiContainer
          jclass clazz = jenv->FindClass("org/COPASI/CCopasiContainer");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CCopasiContainer**)&cptr = static_cast<CCopasiContainer*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  return result;
}

jobject DownCast_CCopasiObject(JNIEnv* jenv, CCopasiObject* pPointer)
{
  jobject result = NULL;
  if (dynamic_cast<CCopasiContainer*>(pPointer))
    {
      if (dynamic_cast<CChemEq*>(pPointer))
        {
          // return a CChemEq
          jclass clazz = jenv->FindClass("org/COPASI/CChemEq");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CChemEq**)&cptr = static_cast<CChemEq*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CChemEqElement*>(pPointer))
        {
          // return a CChemEqElement
          jclass clazz = jenv->FindClass("org/COPASI/CChemEqElement");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CChemEqElement**)&cptr = static_cast<CChemEqElement*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CCopasiTask*>(pPointer))
        {
          if (dynamic_cast<CTrajectoryTask*>(pPointer))
            {
              // return a CTrajectoryTask
              jclass clazz = jenv->FindClass("org/COPASI/CTrajectoryTask");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CTrajectoryTask**)&cptr = static_cast<CTrajectoryTask*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<CSteadyStateTask*>(pPointer))
            {
              // return a CSteadyStateTask
              jclass clazz = jenv->FindClass("org/COPASI/CSteadyStateTask");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CSteadyStateTask**)&cptr = static_cast<CSteadyStateTask*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<CScanTask*>(pPointer))
            {
              // return a CScanTask
              jclass clazz = jenv->FindClass("org/COPASI/CScanTask");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CScanTask**)&cptr = static_cast<CScanTask*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<COptTask*>(pPointer))
            {
              if (dynamic_cast<CFitTask*>(pPointer))
                {
                  // return a CFitTask
                  jclass clazz = jenv->FindClass("org/COPASI/CFitTask");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CFitTask**)&cptr = static_cast<CFitTask*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else
                {
                  // return a COptTask
                  jclass clazz = jenv->FindClass("org/COPASI/COptTask");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(COptTask**)&cptr = static_cast<COptTask*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<CLyapTask*>(pPointer))
            {
              // return a CLyapTask
              jclass clazz = jenv->FindClass("org/COPASI/CLyapTask");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CLyapTask**)&cptr = static_cast<CLyapTask*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else
            {
              // return a CCopasiTask
              jclass clazz = jenv->FindClass("org/COPASI/CCopasiTask");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CCopasiTask**)&cptr = static_cast<CCopasiTask*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
      else if (dynamic_cast<CCopasiParameter*>(pPointer))
        {
          if (dynamic_cast<CCopasiParameterGroup*>(pPointer))
            {
              if (dynamic_cast<CCopasiMethod*>(pPointer))
                {
                  if (dynamic_cast<CTrajectoryMethod*>(pPointer))
                    {
                      // return a CTrajectoryMethod
                      jclass clazz = jenv->FindClass("org/COPASI/CTrajectoryMethod");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CTrajectoryMethod**)&cptr = static_cast<CTrajectoryMethod*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else if (dynamic_cast<CNewtonMethod*>(pPointer))
                    {
                      // return a CNewtonMethod
                      jclass clazz = jenv->FindClass("org/COPASI/CNewtonMethod");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CNewtonMethod**)&cptr = static_cast<CNewtonMethod*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else if (dynamic_cast<CSteadyStateMethod*>(pPointer))
                    {
                      // return a CSteadyStateMethod
                      jclass clazz = jenv->FindClass("org/COPASI/CSteadyStateMethod");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CSteadyStateMethod**)&cptr = static_cast<CSteadyStateMethod*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else if (dynamic_cast<CScanMethod*>(pPointer))
                    {
                      // return a CScanMethod
                      jclass clazz = jenv->FindClass("org/COPASI/CScanMethod");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CScanMethod**)&cptr = static_cast<CScanMethod*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else if (dynamic_cast<COptMethod*>(pPointer))
                    {
                      if (dynamic_cast<CFitMethod*>(pPointer))
                        {
                          // return a CFitMethod
                          jclass clazz = jenv->FindClass("org/COPASI/CFitMethod");
                          if (clazz)
                            {
                              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                              if (mid)
                                {
                                  jlong cptr = 0;
                                  *(CFitMethod**)&cptr = static_cast<CFitMethod*>(pPointer);
                                  result = jenv->NewObject(clazz, mid, cptr, false);
                                }
                            }
                        }
                      else
                        {
                          // return a COptMethod
                          jclass clazz = jenv->FindClass("org/COPASI/COptMethod");
                          if (clazz)
                            {
                              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                              if (mid)
                                {
                                  jlong cptr = 0;
                                  *(COptMethod**)&cptr = static_cast<COptMethod*>(pPointer);
                                  result = jenv->NewObject(clazz, mid, cptr, false);
                                }
                            }
                        }
                    }
                  else if (dynamic_cast<CLyapMethod*>(pPointer))
                    {
                      // return a CLyapMethod
                      jclass clazz = jenv->FindClass("org/COPASI/CLyapMethod");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CLyapMethod**)&cptr = static_cast<CLyapMethod*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else
                    {
                      // return a CCopasiMethod
                      jclass clazz = jenv->FindClass("org/COPASI/CCopasiMethod");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CCopasiMethod**)&cptr = static_cast<CCopasiMethod*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else if (dynamic_cast<CCopasiProblem*>(pPointer))
                {
                  if (dynamic_cast<CTrajectoryProblem*>(pPointer))
                    {
                      // return a CTrajectoryProblem
                      jclass clazz = jenv->FindClass("org/COPASI/CTrajectoryProblem");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CTrajectoryProblem**)&cptr = static_cast<CTrajectoryProblem*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else if (dynamic_cast<CSteadyStateProblem*>(pPointer))
                    {
                      // return a CSteadyStateProblem
                      jclass clazz = jenv->FindClass("org/COPASI/CSteadyStateProblem");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CSteadyStateProblem**)&cptr = static_cast<CSteadyStateProblem*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else if (dynamic_cast<CScanProblem*>(pPointer))
                    {
                      // return a CScanProblem
                      jclass clazz = jenv->FindClass("org/COPASI/CScanProblem");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CScanProblem**)&cptr = static_cast<CScanProblem*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else if (dynamic_cast<COptProblem*>(pPointer))
                    {
                      if (dynamic_cast<CFitProblem*>(pPointer))
                        {
                          // return a CFitProblem
                          jclass clazz = jenv->FindClass("org/COPASI/CFitProblem");
                          if (clazz)
                            {
                              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                              if (mid)
                                {
                                  jlong cptr = 0;
                                  *(CFitProblem**)&cptr = static_cast<CFitProblem*>(pPointer);
                                  result = jenv->NewObject(clazz, mid, cptr, false);
                                }
                            }
                        }
                      else
                        {
                          // return a COptProblem
                          jclass clazz = jenv->FindClass("org/COPASI/COptProblem");
                          if (clazz)
                            {
                              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                              if (mid)
                                {
                                  jlong cptr = 0;
                                  *(COptProblem**)&cptr = static_cast<COptProblem*>(pPointer);
                                  result = jenv->NewObject(clazz, mid, cptr, false);
                                }
                            }
                        }
                    }
                  else if (dynamic_cast<CLyapProblem*>(pPointer))
                    {
                      // return a CLyapProblem
                      jclass clazz = jenv->FindClass("org/COPASI/CLyapProblem");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CLyapProblem**)&cptr = static_cast<CLyapProblem*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else
                    {
                      // return a CCopasiProblem
                      jclass clazz = jenv->FindClass("org/COPASI/CCopasiProblem");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CCopasiProblem**)&cptr = static_cast<CCopasiProblem*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else if (dynamic_cast<COptItem*>(pPointer))
                {
                  if (dynamic_cast<CFitItem*>(pPointer))
                    {
                      if (dynamic_cast<CFitConstraint*>(pPointer))
                        {
                          // return a CFitConstraint
                          jclass clazz = jenv->FindClass("org/COPASI/CFitConstraint");
                          if (clazz)
                            {
                              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                              if (mid)
                                {
                                  jlong cptr = 0;
                                  *(CFitConstraint**)&cptr = static_cast<CFitConstraint*>(pPointer);
                                  result = jenv->NewObject(clazz, mid, cptr, false);
                                }
                            }
                        }
                      else
                        {// return a CFitItem
                          jclass clazz = jenv->FindClass("org/COPASI/CFitItem");
                          if (clazz)
                            {
                              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                              if (mid)
                                {
                                  jlong cptr = 0;
                                  *(CFitItem**)&cptr = static_cast<CFitItem*>(pPointer);
                                  result = jenv->NewObject(clazz, mid, cptr, false);
                                }
                            }
                        }
                    }
                  else
                    {
                      // return a COptItem
                      jclass clazz = jenv->FindClass("org/COPASI/COptItem");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(COptItem**)&cptr = static_cast<COptItem*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else if (dynamic_cast<CExperimentSet*>(pPointer))
                {
                  /*
                  if (dynamic_cast<CCrossValidationSet*>(pPointer))
                  {
                    // return a CCrossValidationSet
                    jclass clazz = jenv->FindClass("org/COPASI/CCrossValidationSet");
                    if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                      {
                        jlong cptr = 0;
                        *(CCrossValidationSet**)&cptr = static_cast<CCrossValidationSet*>(pPointer);
                        result = jenv->NewObject(clazz, mid, cptr, false);
                      }
                    }
                  }
                  else
                  {*/
                  // return a CExperimentSet
                  jclass clazz = jenv->FindClass("org/COPASI/CExperimentSet");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CExperimentSet**)&cptr = static_cast<CExperimentSet*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                  /*}*/
                }
              else if (dynamic_cast<CExperimentObjectMap*>(pPointer))
                {
                  // return a CExperimentObjectMap
                  jclass clazz = jenv->FindClass("org/COPASI/CExperimentObjectMap");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CExperimentObjectMap**)&cptr = static_cast<CExperimentObjectMap*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else if (dynamic_cast<CExperiment*>(pPointer))
                {
                  // return a CExperiment
                  jclass clazz = jenv->FindClass("org/COPASI/CExperiment");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CExperiment**)&cptr = static_cast<CExperiment*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else
                {
                  // return a CCopasiParameterGroup
                  jclass clazz = jenv->FindClass("org/COPASI/CCopasiParameterGroup");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CCopasiParameterGroup**)&cptr = static_cast<CCopasiParameterGroup*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else
            {
              // return a CCopasiParameter
              jclass clazz = jenv->FindClass("org/COPASI/CCopasiParameter");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CCopasiParameter**)&cptr = static_cast<CCopasiParameter*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
      else if (dynamic_cast<CEvaluationTree*>(pPointer))
        {
          if (dynamic_cast<CFunction*>(pPointer))
            {
              // return a CFunction
              jclass clazz = jenv->FindClass("org/COPASI/CFunction");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CFunction**)&cptr = static_cast<CFunction*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else
            {
              // return a CEvaluationTree
              jclass clazz = jenv->FindClass("org/COPASI/CEvaluationTree");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CEvaluationTree**)&cptr = static_cast<CEvaluationTree*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
      else if (dynamic_cast<CFunctionDB*>(pPointer))
        {
          // return a CFunctionDB
          jclass clazz = jenv->FindClass("org/COPASI/CFunctionDB");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CFunctionDB**)&cptr = static_cast<CFunctionDB*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CFunctionParameter*>(pPointer))
        {
          // return a CFunctionParameter
          jclass clazz = jenv->FindClass("org/COPASI/CFunctionParameter");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CFunctionParameter**)&cptr = static_cast<CFunctionParameter*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CFunctionParameters*>(pPointer))
        {
          // return a CFunctionParameters
          jclass clazz = jenv->FindClass("org/COPASI/CFunctionParameters");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CFunctionParameters**)&cptr = static_cast<CFunctionParameters*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CModelEntity*>(pPointer))
        {
          if (dynamic_cast<CCompartment*>(pPointer))
            {
              // return a CCompartment
              jclass clazz = jenv->FindClass("org/COPASI/CCompartment");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CCompartment**)&cptr = static_cast<CCompartment*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<CMetab*>(pPointer))
            {
              // return a CMetab
              jclass clazz = jenv->FindClass("org/COPASI/CMetab");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CMetab**)&cptr = static_cast<CMetab*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<CModel*>(pPointer))
            {
              // return a CModel
              jclass clazz = jenv->FindClass("org/COPASI/CModel");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CModel**)&cptr = static_cast<CModel*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else if (dynamic_cast<CModelValue*>(pPointer))
            {
              // return a CModelValue
              jclass clazz = jenv->FindClass("org/COPASI/CModelValue");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CModelValue**)&cptr = static_cast<CModelValue*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else
            {
              // return a CModelEntity
              jclass clazz = jenv->FindClass("org/COPASI/CModelEntity");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CModelEntity**)&cptr = static_cast<CModelEntity*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
      else if (dynamic_cast<CMoiety*>(pPointer))
        {
          // return a CMoiety
          jclass clazz = jenv->FindClass("org/COPASI/CMoiety");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CMoiety**)&cptr = static_cast<CMoiety*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CReaction*>(pPointer))
        {
          // return a CReaction
          jclass clazz = jenv->FindClass("org/COPASI/CReaction");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CReaction**)&cptr = static_cast<CReaction*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CReport*>(pPointer))
        {
          // return a CReport
          jclass clazz = jenv->FindClass("org/COPASI/CReport");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CReport**)&cptr = static_cast<CReport*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else if (dynamic_cast<CFittingPoint*>(pPointer))
        {
          // return a CFittingPoint
          jclass clazz = jenv->FindClass("org/COPASI/CFittingPoint");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CFittingPoint**)&cptr = static_cast<CFittingPoint*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
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
                      jclass clazz = jenv->FindClass("org/COPASI/TaskVectorN");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(TaskVectorN**)&cptr = static_cast<TaskVectorN*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else
                    {
                      // return a TaskVector
                      jclass clazz = jenv->FindClass("org/COPASI/TaskVector");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(TaskVector**)&cptr = static_cast<TaskVector*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else if (dynamic_cast<CCopasiVector<CModelValue>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CModelValue>* >(pPointer))
                    {
                      // return a ModelValueVectorN
                      jclass clazz = jenv->FindClass("org/COPASI/ModelValueVectorN");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(ModelValueVectorN**)&cptr = static_cast<ModelValueVectorN*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else
                    {
                      // return a ModelValueVector
                      jclass clazz = jenv->FindClass("org/COPASI/ModelValueVector");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(ModelValueVector**)&cptr = static_cast<ModelValueVector*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else if (dynamic_cast<CCopasiVector<CReportDefinition>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CReportDefinition>* >(pPointer))
                    {
                      // return a CCReportDefinitionVectorN
                      jclass clazz = jenv->FindClass("org/COPASI/CReportDefinitionVectorN");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CReportDefinitionVectorN**)&cptr = static_cast<CReportDefinitionVectorN*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else
                    {
                      // return a CReportDefinitionVector
                      jclass clazz = jenv->FindClass("org/COPASI/CReportDefinitionVector");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CReportDefinitionVector**)&cptr = static_cast<CReportDefinitionVector*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else if (dynamic_cast<CCopasiVector<CMoiety>* >(pPointer))
                {
                  // return a MoietyVector
                  jclass clazz = jenv->FindClass("org/COPASI/MoietyVector");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(MoietyVector**)&cptr = static_cast<MoietyVector*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
              else if (dynamic_cast<CCopasiVector<CMetab>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CMetab>* >(pPointer))
                    {
                      if (dynamic_cast<CCopasiVectorNS<CMetab>* >(pPointer))
                        {
                          // return a MetabVectorNS
                          jclass clazz = jenv->FindClass("org/COPASI/MetabVectorNS");
                          if (clazz)
                            {
                              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                              if (mid)
                                {
                                  jlong cptr = 0;
                                  *(MetabVectorNS**)&cptr = static_cast<MetabVectorNS*>(pPointer);
                                  result = jenv->NewObject(clazz, mid, cptr, false);
                                }
                            }
                        }
                      else
                        {
                          // return a MetabVectorN
                          jclass clazz = jenv->FindClass("org/COPASI/MetabVectorN");
                          if (clazz)
                            {
                              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                              if (mid)
                                {
                                  jlong cptr = 0;
                                  *(MetabVectorN**)&cptr = static_cast<MetabVectorN*>(pPointer);
                                  result = jenv->NewObject(clazz, mid, cptr, false);
                                }
                            }
                        }
                    }
                  else
                    {
                      // return a MetabVector
                      jclass clazz = jenv->FindClass("org/COPASI/MetabVector");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(MetabVector**)&cptr = static_cast<MetabVector*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else if (dynamic_cast<CCopasiVector<CCompartment>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CCompartment>* >(pPointer))
                    {
                      if (dynamic_cast<CCopasiVectorNS<CCompartment>* >(pPointer))
                        {
                          // return a CompartmentVectorNS
                          jclass clazz = jenv->FindClass("org/COPASI/CompartmentVectorNS");
                          if (clazz)
                            {
                              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                              if (mid)
                                {
                                  jlong cptr = 0;
                                  *(CompartmentVectorNS**)&cptr = static_cast<CompartmentVectorNS*>(pPointer);
                                  result = jenv->NewObject(clazz, mid, cptr, false);
                                }
                            }
                        }
                      else
                        {
                          // return a CompartmentVectorN
                          jclass clazz = jenv->FindClass("org/COPASI/CompartmentVectorN");
                          if (clazz)
                            {
                              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                              if (mid)
                                {
                                  jlong cptr = 0;
                                  *(CompartmentVectorN**)&cptr = static_cast<CompartmentVectorN*>(pPointer);
                                  result = jenv->NewObject(clazz, mid, cptr, false);
                                }
                            }
                        }
                    }
                  else
                    {
                      // return a CompartmentVector
                      jclass clazz = jenv->FindClass("org/COPASI/CompartmentVector");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CompartmentVector**)&cptr = static_cast<CompartmentVector*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else if (dynamic_cast<CCopasiVector<CReaction>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CReaction>* >(pPointer))
                    {
                      if (dynamic_cast<CCopasiVectorNS<CReaction>* >(pPointer))
                        {
                          // return a ReactionVectorNS
                          jclass clazz = jenv->FindClass("org/COPASI/ReactionVectorNS");
                          if (clazz)
                            {
                              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                              if (mid)
                                {
                                  jlong cptr = 0;
                                  *(ReactionVectorNS**)&cptr = static_cast<ReactionVectorNS*>(pPointer);
                                  result = jenv->NewObject(clazz, mid, cptr, false);
                                }
                            }
                        }
                      else
                        {
                          // return a ReactionVectorN
                          jclass clazz = jenv->FindClass("org/COPASI/ReactionVectorN");
                          if (clazz)
                            {
                              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                              if (mid)
                                {
                                  jlong cptr = 0;
                                  *(ReactionVectorN**)&cptr = static_cast<ReactionVectorN*>(pPointer);
                                  result = jenv->NewObject(clazz, mid, cptr, false);
                                }
                            }
                        }
                    }
                  else
                    {
                      // return a ReactionVector
                      jclass clazz = jenv->FindClass("org/COPASI/ReactionVector");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(ReactionVector**)&cptr = static_cast<ReactionVector*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else if (dynamic_cast<CCopasiVector<CEvaluationTree>* >(pPointer))
                {
                  if (dynamic_cast<CCopasiVectorN<CEvaluationTree>* >(pPointer))
                    {
                      // return a CEvaluationTreeVectorN
                      jclass clazz = jenv->FindClass("org/COPASI/CEvaluationTreeVectorN");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CEvaluationTreeVectorN**)&cptr = static_cast<CEvaluationTreeVectorN*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                  else
                    {
                      // return a CEvaluationTreeVector
                      jclass clazz = jenv->FindClass("org/COPASI/CEvaluationTreeVector");
                      if (clazz)
                        {
                          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                          if (mid)
                            {
                              jlong cptr = 0;
                              *(CEvaluationTreeVector**)&cptr = static_cast<CEvaluationTreeVector*>(pPointer);
                              result = jenv->NewObject(clazz, mid, cptr, false);
                            }
                        }
                    }
                }
              else if (dynamic_cast<CCopasiVector<CChemEqElement>* >(pPointer))
                {
                  // return a CChemEqElementVector
                  jclass clazz = jenv->FindClass("org/COPASI/CChemEqElementVector");
                  if (clazz)
                    {
                      jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                      if (mid)
                        {
                          jlong cptr = 0;
                          *(CChemEqElementVector**)&cptr = static_cast<CChemEqElementVector*>(pPointer);
                          result = jenv->NewObject(clazz, mid, cptr, false);
                        }
                    }
                }
            }
          else if (dynamic_cast<CArrayAnnotation*>(pPointer))
            {
              // return a CArrayAnnotation
              jclass clazz = jenv->FindClass("org/COPASI/CArrayAnnotation");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CArrayAnnotation**)&cptr = static_cast<CArrayAnnotation*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
          else
            {
              // return a CCopasiContainer
              jclass clazz = jenv->FindClass("org/COPASI/CCopasiContainer");
              if (clazz)
                {
                  jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
                  if (mid)
                    {
                      jlong cptr = 0;
                      *(CCopasiContainer**)&cptr = static_cast<CCopasiContainer*>(pPointer);
                      result = jenv->NewObject(clazz, mid, cptr, false);
                    }
                }
            }
        }
    }
  else if (dynamic_cast<CReportDefinition*>(pPointer))
    {
      // return a CReportDefinition
      jclass clazz = jenv->FindClass("org/COPASI/CReportDefinition");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CReportDefinition**)&cptr = static_cast<CReportDefinition*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  else if (dynamic_cast<CCopasiStaticString*>(pPointer))
    {
      if (dynamic_cast<CCopasiReportSeparator*>(pPointer))
        {
          // return a CCopasiReportSeparator
          jclass clazz = jenv->FindClass("org/COPASI/CCopasiReportSeparator");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CCopasiReportSeparator**)&cptr = static_cast<CCopasiReportSeparator*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
      else
        {
          // return a CCopasiStaticString
          jclass clazz = jenv->FindClass("org/COPASI/CCopasiStaticString");
          if (clazz)
            {
              jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
              if (mid)
                {
                  jlong cptr = 0;
                  *(CCopasiStaticString**)&cptr = static_cast<CCopasiStaticString*>(pPointer);
                  result = jenv->NewObject(clazz, mid, cptr, false);
                }
            }
        }
    }
  else
    {
      // return a CCopasiObject
      jclass clazz = jenv->FindClass("org/COPASI/CCopasiObject");
      if (clazz)
        {
          jmethodID mid = jenv->GetMethodID(clazz, "<init>", "(JZ)V");
          if (mid)
            {
              jlong cptr = 0;
              *(CCopasiObject**)&cptr = static_cast<CCopasiObject*>(pPointer);
              result = jenv->NewObject(clazz, mid, cptr, false);
            }
        }
    }
  return result;
}
