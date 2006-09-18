/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensMethod.cpp,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/09/18 12:58:07 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CSensMethod class.
 */

#include "copasi.h"

//#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "CSensMethod.h"
#include "CSensProblem.h"

#include "model/CModel.h"
#include "model/CState.h"

CSensMethod *
CSensMethod::createSensMethod(CCopasiMethod::SubType subType)
{
  CSensMethod * pMethod = NULL;

  switch (subType)
    {
    case unset:
    case sensMethod:
      pMethod = new CSensMethod(subType);
      break;

    default:
      fatalError();
    }

  return pMethod;
}

/**
 *  Default constructor.
 */
CSensMethod::CSensMethod(CCopasiMethod::SubType subType,
                         const CCopasiContainer * pParent):
    CCopasiMethod(CCopasiTask::sens, subType, pParent),
    mpProblem(NULL)
{CONSTRUCTOR_TRACE;}

/**
 *  Copy constructor.
 *  @param "const CSensMethod &" src
 */
CSensMethod::CSensMethod(const CSensMethod & src,
                         const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mpProblem(src.mpProblem)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CSensMethod::~CSensMethod()
{DESTRUCTOR_TRACE;}

//***********************************************************************************

void CSensMethod::do_target_calculation(CCopasiArray & result)
{
  //****** do subtask ******************
  if (mpSubTask)
    mpSubTask->process(true);
  else
    {
      mpProblem->getModel()->applyAssignments();
      mpProblem->getModel()->refreshRates();
    }

  //****** retrieve results ************

  //resize results array
  CCopasiArray::index_type resultindex;
  C_INT32 i, imax = mTargetfunctionPointers.size();
  if (imax > 1)
    resultindex.push_back(imax);
  result.resize(resultindex);

  //copy result
  for (i = 0; i < imax; ++i)
    {
      if (imax > 1)
        resultindex[0] = i;
      result[resultindex] = *(C_FLOAT64*)mTargetfunctionPointers[i]->getValuePointer();
      std::cout << *(C_FLOAT64*)mTargetfunctionPointers[i]->getValuePointer() << std::endl;
    }
}

C_FLOAT64 CSensMethod::do_variation(CCopasiObject* variable)
{
  C_FLOAT64 value;
  value = *(C_FLOAT64*)variable->getValuePointer();
  C_FLOAT64 delta;
  delta = fabs(value) * 1e-4;
  if (delta < 1e-12) delta = 1e-12;

  variable->setObjectValue(delta + value);

  //debug
  std::cout << variable->getObjectDisplayName() << "  " << value << " -> ";
  value = *(C_FLOAT64*)variable->getValuePointer();
  std::cout << value << std::endl;

  return delta;
}

void CSensMethod::calculate_difference(unsigned C_INT32 level, const C_FLOAT64 & delta,
                                       CCopasiArray & result, CCopasiArray::index_type & resultindex)
{
  assert (delta != 0.0);
  assert (mLocalData[level].tmp1.size() == mLocalData[level].tmp1.size());
  unsigned C_INT32 dim = mLocalData[level].tmp1.dimensionality();
  assert (resultindex.size() >= dim);

  CCopasiArray::index_type indexmax = mLocalData[level].tmp1.size();

  //init index with zero
  CCopasiArray::index_type indexit; indexit.resize(dim);
  unsigned C_INT32 i;
  for (i = 0; i < dim; ++i)
    indexit[i] = 0;

  //handle scalars separately
  if (dim == 0)
    {
      result[resultindex] = (mLocalData[level].tmp2[indexit] - mLocalData[level].tmp1[indexit]) / delta;
      return;
    }

  //now for all higher dimensionalities
  for (;;)
    {
      //do difference calculation
      for (i = 0; i < dim; ++i)
        resultindex[i] = indexit[i];  //TODO: use stl algorithm

      result[resultindex] = (mLocalData[level].tmp2[indexit] - mLocalData[level].tmp1[indexit]) / delta;

      //increase index
      ++indexit[dim - 1];

      //check overflow
      C_INT32 j;
      for (j = dim - 1; j >= 0; --j)
        {
          if (indexit[j] >= indexmax[j])
            {
              indexit[j] = 0;
              if (j > 0)
                ++indexit[j - 1];
              else
                return;
            }
          else
            break;
        }
    }
}

void CSensMethod::calculate_one_level(unsigned C_INT32 level, CCopasiArray & result)
{

  //do first calculation
  if (level == 0)
    {
      do_target_calculation(mLocalData[level].tmp1);
    }
  else
    {
      calculate_one_level(level - 1, mLocalData[level].tmp1);
    }

  //resize results array
  CCopasiArray::index_type resultindex; resultindex = mLocalData[level].tmp1.size();
  if (mLocalData[level].variables.size() > 1)
    resultindex.push_back(mLocalData[level].variables.size());
  result.resize(resultindex);

  //loop over all variables
  C_INT32 i, imax = mLocalData[level].variables.size();
  for (i = 0; i < imax; ++i)
    {
      //store variable value
      C_FLOAT64 store = *(C_FLOAT64 *)mLocalData[level].variables[i]->getValuePointer();

      //change variable
      C_FLOAT64 delta = do_variation(mLocalData[level].variables[i]);

      //do second calculation
      if (level == 0)
        {
          do_target_calculation(mLocalData[level].tmp2);
        }
      else
        {
          calculate_one_level(level - 1, mLocalData[level].tmp2);
        }

      //restore variable
      mLocalData[level].variables[i]->setObjectValue(store);

      //calculate derivative
      if (imax > 1)
        resultindex[resultindex.size() - 1] = i;
      calculate_difference(level, delta, result, resultindex);
    }
}

bool CSensMethod::initialize(CSensProblem* problem)
{
  mpProblem = problem; assert(mpProblem);

  //initialize the target calculation
  mpSubTask = NULL;

  switch (mpProblem->getSubTaskType())
    {
    case CSensProblem::unset:
    case CSensProblem::Evaluation:
      mpSubTask = NULL;
      break;

    case CSensProblem::SteadyState:
      mpSubTask = dynamic_cast<CCopasiTask*>
                  ((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);
      break;

    case CSensProblem::TimeSeries:
      mpSubTask = dynamic_cast<CCopasiTask*>
                  ((*CCopasiDataModel::Global->getTaskList())["Time-Course"]);
      break;

    case CSensProblem::LyapunovExp:
      mpSubTask = dynamic_cast<CCopasiTask*>
                  ((*CCopasiDataModel::Global->getTaskList())["Lyapunov Exponents"]);
      break;
    }

  if (mpSubTask)
    {
      mpSubTask->getProblem()->setModel(mpProblem->getModel());
      mpSubTask->setCallBack(NULL);
      mpSubTask->initialize(CCopasiTask::NO_OUTPUT, NULL);
    }

  //initialize the variables pointers
  C_INT32 i, imax = mpProblem->getNumberOfVariables();
  mLocalData.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      mLocalData[i].variables = mpProblem->getVariables(i).getVariablesPointerList(mpProblem->getModel());
    }

  //initialize the target function pointers
  mTargetfunctionPointers = mpProblem->getTargetFunctions().getVariablesPointerList(mpProblem->getModel());

  //****** initialize result annotations ****************

  //determine dimensions of result
  CCopasiArray::index_type s;
  if (mTargetfunctionPointers.size() > 1)
    {
      s.push_back(mTargetfunctionPointers.size());
    }
  for (i = 0; i < imax; ++i)
    {
      if (mLocalData[i].variables.size() > 1)
        {
          s.push_back(mLocalData[i].variables.size());
        }
    }

  //resize result & annotations
  mpProblem->getResult().resize(s);
  mpProblem->getResultAnnotated()->resize();

  unsigned C_INT32 dim = 0;
  unsigned C_INT32 j;
  //target function annotations //TODO: only implemented for scalar and vector
  if (mTargetfunctionPointers.size() > 1)
    {
      std::ostringstream tmp;
      tmp << "Target functions, " << mpProblem->getTargetFunctions().getListTypeDisplayName();
      mpProblem->getResultAnnotated()->setDimensionDescription(dim, tmp.str());
      for (j = 0; j < mTargetfunctionPointers.size(); ++j)
        mpProblem->getResultAnnotated()->setAnnotation(dim, j, mTargetfunctionPointers[j]->getCN());
      ++dim;
    }

  //variables annotiation
  for (i = 0; i < imax; ++i)
    {
      if (mLocalData[i].variables.size() > 1)
        {
          std::ostringstream tmp;
          tmp << "Variables " << i + 1 << ", " << mpProblem->getVariables(i).getListTypeDisplayName();
          mpProblem->getResultAnnotated()->setDimensionDescription(dim, tmp.str());
          for (j = 0; j < mLocalData[i].variables.size(); ++j)
            mpProblem->getResultAnnotated()->setAnnotation(dim, j, mLocalData[i].variables[j]->getCN());
          ++dim;
        }
    }

  return true;
}

bool CSensMethod::process(CProcessReport * handler)
{
  if (!mLocalData.size()) return false;
  calculate_one_level(mLocalData.size() - 1, mpProblem->getResult());
  return true;
}

//virtual
bool CSensMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CSensProblem * pP = dynamic_cast<const CSensProblem *>(pProblem);
  if (!pP)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not a sensitivities problem.");
      return false;
    }

  return true;

  //all sizes at least one

  //dimension of variables 0 or 1

  //if target is scan make sure the scan subtask is not sens.
}
