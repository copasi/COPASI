// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CSensMethod class.
 */

#include <sstream>

#include "copasi/copasi.h"

//#include "copasi/core/CDataVector.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "CSensMethod.h"
#include "CSensProblem.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/utilities/CProcessReport.h"

/**
 *  Default constructor.
 */
CSensMethod::CSensMethod(const CDataContainer * pParent,
                         const CTaskEnum::Method & methodType,
                         const CTaskEnum::Task & taskType):
  CCopasiMethod(pParent, methodType, taskType),
  mpProblem(NULL),
  mLocalData(),
  mTargetValuePointers(),
  mpSubTask(NULL),
  mTargetValueSequence(),
  mpDeltaFactor(NULL),
  mpMinDelta(NULL),
  mStoreSubtasktUpdateFlag(false),
  mProgressHandler(C_INVALID_INDEX),
  mProgress(0),
  mCounter(0),
  mFailedCounter(0)
{
  mpDeltaFactor = assertParameter("Delta factor", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1e-3);
  mpMinDelta = assertParameter("Delta minimum", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1e-12);

  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CSensMethod &" src
 */
CSensMethod::CSensMethod(const CSensMethod & src,
                         const CDataContainer * pParent):
  CCopasiMethod(src, pParent),
  mpProblem(src.mpProblem),
  mLocalData(),
  mTargetValuePointers(),
  mpSubTask(NULL),
  mTargetValueSequence(),
  mpDeltaFactor(NULL),
  mpMinDelta(NULL),
  mStoreSubtasktUpdateFlag(false),
  mProgressHandler(C_INVALID_INDEX),
  mProgress(0),
  mCounter(0),
  mFailedCounter(0)
{
  mpDeltaFactor = assertParameter("Delta factor", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1e-3);
  mpMinDelta = assertParameter("Delta minimum", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1e-12);

  CONSTRUCTOR_TRACE;
}

/**
 *  Destructor.
 */
CSensMethod::~CSensMethod()
{DESTRUCTOR_TRACE;}

//***********************************************************************************

bool CSensMethod::do_target_calculation(size_t level,  CArray & result, bool /* first */)
{
  bool success = false;

  //perform the necessary updates
  mpContainer->applyUpdateSequence(mLocalData[level].mInitialSequences);

  //****** do subtask ******************
  if (mpSubTask != NULL)
    {
      success = mpSubTask->process(true);
      mCounter++;
    }
  else
    {
      mpContainer->applyInitialValues();
      success = true; // doing nothing should never fail.
    }

  // We need to make sure that the target value(s) are updated
  mpContainer->applyUpdateSequence(mTargetValueSequence);

  //****** retrieve results ************

  //resize results array
  CArray::index_type resultindex;
  size_t i, imax = mTargetValuePointers.size();

  if (imax > 1)
    resultindex.push_back(imax);

  result.resize(resultindex);

  //copy result
  if (success)
    {
      for (i = 0; i < imax; ++i)
        {
          if (imax > 1)
            resultindex[0] = i;

          result[resultindex] = *mTargetValuePointers[i];
        }
    }
  else
    {
      mFailedCounter++;

      for (i = 0; i < imax; ++i)
        {
          if (imax > 1)
            resultindex[0] = i;

          result[resultindex] = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
        }
    }

  //progress bar
  ++mProgress;

  if (mProcessReport)
    {
      bool tmp = mProcessReport.progressItem(mProgressHandler);
      return tmp;
    }

  return success;
}

C_FLOAT64 CSensMethod::do_variation(C_FLOAT64 & variable)
{
  C_FLOAT64 delta = fabs(variable) **mpDeltaFactor;

  if (delta < *mpMinDelta) delta = *mpMinDelta;

  variable += delta;

  return delta;
}

void CSensMethod::calculate_difference(size_t level, const C_FLOAT64 & delta,
                                       CArray & result, CArray::index_type & resultindex)
{
  assert(delta != 0.0);
  assert(mLocalData[level].tmp1.size() == mLocalData[level].tmp2.size());
  size_t dim = mLocalData[level].tmp1.dimensionality();
  assert(resultindex.size() >= dim);

  CArray::index_type indexmax = mLocalData[level].tmp1.size();

  //init index with zero
  CArray::index_type indexit; indexit.resize(dim);
  size_t i;

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
      size_t j;

      for (j = dim - 1; j != C_INVALID_INDEX; --j)
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

bool CSensMethod::calculate_one_level(size_t level, CArray & result)
{
  //do first calculation
  if (level == 0)
    {
      if (!do_target_calculation(level, mLocalData[level].tmp1, true)) return false;
    }
  else
    {
      if (!calculate_one_level(level - 1, mLocalData[level].tmp1)) return false;
    }

  //resize results array
  CArray::index_type resultindex; resultindex = mLocalData[level].tmp1.size();

  if (mLocalData[level].mInitialStateVariables.size() > 1)
    resultindex.push_back(mLocalData[level].mInitialStateVariables.size());

  result.resize(resultindex);

  //loop over all variables
  size_t i, imax = mLocalData[level].mInitialStateVariables.size();

  for (i = 0; i < imax; ++i)
    {
      C_FLOAT64 & Variable = * mLocalData[level].mInitialStateVariables[i];

      //store variable value
      C_FLOAT64 store = Variable;

      //change variable
      C_FLOAT64 delta = do_variation(Variable);

      //do second calculation
      if (level == 0)
        {
          if (!do_target_calculation(level, mLocalData[level].tmp2, false)) return false;
        }
      else
        {
          if (!calculate_one_level(level - 1, mLocalData[level].tmp2)) return false;
        }

      //restore variable
      //mLocalData[level].variables[i]->setObjectValue(store);
      Variable = store;

      //calculate derivative
      if (imax > 1)
        resultindex[resultindex.size() - 1] = i;

      calculate_difference(level, delta, result, resultindex);
    }

  return true;
}

//********** SCALING *************************************************************

void CSensMethod::scaling_targetfunction(const C_FLOAT64 & factor,
    CArray::index_type & resultindex)
{
  size_t dim = mLocalData[0].tmp1.dimensionality();
  assert(resultindex.size() >= dim);

  CArray::index_type indexmax = mLocalData[0].tmp1.size();
  //init index with zero
  CArray::index_type indexit; indexit.resize(dim);
  size_t i;

  for (i = 0; i < dim; ++i)
    indexit[i] = 0;

  //handle scalars separately
  if (dim == 0)
    {
      mpProblem->getScaledResult()[resultindex] = mpProblem->getResult()[resultindex] * factor / mLocalData[0].tmp1[indexit];
      return;
    }

  //now for all higher dimensionalities
  for (;;)
    {
      for (i = 0; i < dim; ++i)
        resultindex[i] = indexit[i];  //TODO: use stl algorithm

      mpProblem->getScaledResult()[resultindex] = mpProblem->getResult()[resultindex] * factor / mLocalData[0].tmp1[indexit];

      //increase index
      ++indexit[dim - 1];

      //check overflow
      size_t j;

      for (j = dim - 1; j != C_INVALID_INDEX; --j)
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

void CSensMethod::scaling_variables(size_t level, const C_FLOAT64 & factor,
                                    CArray::index_type & resultindex)
{
  //loop over all variables
  size_t i, imax = mLocalData[level].mInitialStateVariables.size();

  for (i = 0; i < imax; ++i)
    {
      //get Value
      C_FLOAT64 value = *mLocalData[level].mInitialStateVariables[i] * factor;

      //do recursive calculation
      if (imax > 1)
        resultindex[mLocalData[level].index] = i;

      if (level == 0)
        {
          scaling_targetfunction(value, resultindex);
        }
      else
        {
          scaling_variables(level - 1, value, resultindex);
        }
    }
}

void CSensMethod::do_scaling()
{
  CArray::index_type index;
  index.resize(mpProblem->getResult().dimensionality());
  scaling_variables(mLocalData.size() - 1, 1.0, index);
}

//****************************************************************************

C_FLOAT64 CSensMethod::do_collapsing_innerloop(CArray::index_type & fullindex)
{
  //fullindex[0]=0;
  //return mpProblem->getScaledResult()[fullindex];

  //assumes the sum is to be taken over the first dim of the scaled result array
  C_FLOAT64 tmpFloat, tmpSum = 0;
  size_t i, imax = mpProblem->getScaledResult().size()[0];

  for (i = 0; i < imax; ++i)
    {
      fullindex[0] = i;
      tmpFloat = mpProblem->getScaledResult()[fullindex];

      if (tmpFloat != tmpFloat) continue;

      if (fabs(tmpFloat) >= std::numeric_limits< C_FLOAT64 >::max()) continue;

      tmpSum += tmpFloat * tmpFloat;
    }

  return sqrt(tmpSum);
}

void CSensMethod::do_collapsing()
{
  if (mpProblem->collapsRequested())
    {
      CArray::index_type fullresultindex = mpProblem->getScaledResult().size();
      CArray::index_type collapsedresultindex = mpProblem->getCollapsedResult().size();

      size_t shift = fullresultindex.size() - collapsedresultindex.size();

      if (shift != 1) return; //only supported if target functions list is 1D

      //***** skalar ********
      if (collapsedresultindex.size() == 0)
        {
          mpProblem->getCollapsedResult()[collapsedresultindex] =
            do_collapsing_innerloop(fullresultindex);
          return;
        }

      //***** higher dimensions *********
      size_t i, dim = collapsedresultindex.size();
      CArray::index_type indexmax = mpProblem->getCollapsedResult().size();

      //set index to zero
      for (i = 0; i < dim; ++i) collapsedresultindex[i] = 0;

      for (;;)
        {
          fullresultindex[0] = 0;

          for (i = 0; i < dim; ++i)
            fullresultindex[i + shift] = collapsedresultindex[i];

          mpProblem->getCollapsedResult()[collapsedresultindex] =
            do_collapsing_innerloop(fullresultindex);

          //increase index
          ++collapsedresultindex[dim - 1];

          //check overflow
          size_t j;

          for (j = dim - 1; j != C_INVALID_INDEX; --j)
            {
              if (collapsedresultindex[j] >= indexmax[j])
                {
                  collapsedresultindex[j] = 0;

                  if (j > 0)
                    ++collapsedresultindex[j - 1];
                  else
                    return;
                }
              else
                break;
            }
        }
    }
  else
    {}
}

//****************************************************************************

bool CSensMethod::initialize(CSensProblem* problem)
{
  bool success = true;

  mpProblem = problem;
  assert(mpProblem);

  //initialize the target calculation
  mpSubTask = NULL;
  CDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);

  switch (mpProblem->getSubTaskType())
    {
      case CSensProblem::Evaluation:
        mpSubTask = NULL;
        break;

      case CSensProblem::SteadyState:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Steady-State"));
        break;

      case CSensProblem::TimeSeries:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Time-Course"));
        break;

      /*    case CSensProblem::LyapunovExp:
            mpSubTask = dynamic_cast<CCopasiTask*>
                        (&pDataModel->getTaskList()->operator[]("Lyapunov Exponents"));
            break;*/

      case CSensProblem::ParameterEstimation:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Parameter Estimation"));
        break;

      case CSensProblem::Optimization:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Optimization"));
        break;

      case CSensProblem::CrossSection:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    (&pDataModel->getTaskList()->operator[]("Cross Section"));
        break;
    }

  if (mpSubTask)
    {
      //the subtask should not change the initial state of the model
      mStoreSubtasktUpdateFlag = mpSubTask->isUpdateModel();

      mpSubTask->setMathContainer(mpContainer);
      mpSubTask->setCallBack(NULL);
      success &= mpSubTask->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
    }

  //initialize the variables pointers
  size_t i, imax = mpProblem->getNumberOfVariables();

  while (imax > 0)
    {
      if (mpProblem->getVariables(imax - 1).getListType() != CObjectLists::EMPTY_LIST) break;

      imax--;
    }

  mLocalData.resize(imax);
  CObjectInterface::ObjectSet IntialStateObjects;

  for (i = 0; i < imax; ++i)
    {
      std::vector< CDataObject * > DataObjects = mpProblem->getVariables(i).getVariablesPointerList(pDataModel);
      mLocalData[i].mInitialStateVariables.resize(DataObjects.size());

      C_FLOAT64** ppValue = mLocalData[i].mInitialStateVariables.array();
      C_FLOAT64** ppValueEnd = ppValue + mLocalData[i].mInitialStateVariables.size();
      std::vector< CDataObject * >::const_iterator itDataObject = DataObjects.begin();

      CObjectInterface::ObjectSet Changed;

      for (; ppValue != ppValueEnd; ++ppValue, ++itDataObject)
        {
          const CMathObject * pValueObject = mpContainer->getMathObject(*itDataObject);

          if (pValueObject != NULL)
            {
              *ppValue = (C_FLOAT64 *) pValueObject->getValuePointer();
              Changed.insert(pValueObject);
            }
          else
            {
              *ppValue = NULL;
            }
        }

      mpContainer->getInitialDependencies().getUpdateSequence(mLocalData[i].mInitialSequences,
          CCore::SimulationContext::UpdateMoieties,
          Changed,
          mpContainer->getInitialStateObjects());
    }

  //initialize the target function pointers
  std::vector< CDataObject * > DataObjects = mpProblem->getTargetFunctions().getVariablesPointerList(pDataModel);
  mTargetValuePointers.resize(DataObjects.size());

  C_FLOAT64** ppValue = mTargetValuePointers.array();
  C_FLOAT64** ppValueEnd = ppValue + mTargetValuePointers.size();
  std::vector< CDataObject * >::const_iterator itDataObject = DataObjects.begin();

  CObjectInterface::ObjectSet Requested;

  for (; ppValue != ppValueEnd; ++ppValue, ++itDataObject)
    {
      const CMathObject * pValueObject = mpContainer->getMathObject(*itDataObject);

      if (pValueObject != NULL)
        {
          *ppValue = (C_FLOAT64 *) pValueObject->getValuePointer();
          Requested.insert(pValueObject);
        }
      else
        {
          *ppValue = (C_FLOAT64 *)(*itDataObject)->getValuePointer();
        }
    }

  mpContainer->getTransientDependencies().getUpdateSequence(mTargetValueSequence,
      CCore::SimulationContext::Default,
      mpContainer->getStateObjects(false),
      Requested);

  //****** initialize result annotations ****************

  //determine dimensions of result
  CArray::index_type s;
  CArray::index_type sc; //size of collapsed result

  if (mTargetValuePointers.size() > 1)
    {
      s.push_back(mTargetValuePointers.size());
    }

  for (i = 0; i < imax; ++i)
    {
      if (mLocalData[i].mInitialStateVariables.size() > 1)
        {
          mLocalData[i].index = s.size();
          s.push_back(mLocalData[i].mInitialStateVariables.size());
          sc.push_back(mLocalData[i].mInitialStateVariables.size());
        }
      else
        mLocalData[i].index = C_INVALID_INDEX;
    }

  //resize result & annotations
  mpProblem->getResult().resize(s);
  mpProblem->getResultAnnotated()->resize();
  //mpProblem->getResultAnnotated()->setMode(CArrayAnnotation::OBJECTS);

  mpProblem->getScaledResult().resize(s);
  mpProblem->getScaledResultAnnotated()->resize();
  //mpProblem->getScaledResultAnnotated()->setMode(CArrayAnnotation::OBJECTS);

  if (mpProblem->collapsRequested())
    {
      mpProblem->getCollapsedResult().resize(sc);
      mpProblem->getCollapsedResultAnnotated()->resize();
      //mpProblem->getCollapsedResultAnnotated()->setMode(CArrayAnnotation::OBJECTS);
    }

  size_t dim = 0;
  size_t j;

  // target function annotations
  // TODO: only implemented for scalar and vector
  if (mTargetValuePointers.size() > 1)
    {
      std::ostringstream tmp;
      tmp << "Target functions, " << mpProblem->getTargetFunctions().getListTypeDisplayName();
      mpProblem->getResultAnnotated()->setDimensionDescription(dim, tmp.str());
      mpProblem->getScaledResultAnnotated()->setDimensionDescription(dim, tmp.str());

      std::vector< CDataObject * > DataObjects = mpProblem->getTargetFunctions().getVariablesPointerList(pDataModel);
      std::vector< CDataObject * >::const_iterator itDataObject = DataObjects.begin();

      for (j = 0; j < mTargetValuePointers.size(); ++j, ++itDataObject)
        {
          mpProblem->getResultAnnotated()->setAnnotation(dim, j, *itDataObject);
          mpProblem->getScaledResultAnnotated()->setAnnotation(dim, j, *itDataObject);
        }

      ++dim;
    }

  //variables annotiation
  size_t dim2 = 0; //for collapsed result

  for (i = 0; i < imax; ++i)
    {
      if (mLocalData[i].mInitialStateVariables.size() > 1)
        {
          std::ostringstream tmp;
          tmp << "Variables " << i + 1 << ", " << mpProblem->getVariables(i).getListTypeDisplayName();
          mpProblem->getResultAnnotated()->setDimensionDescription(dim, tmp.str());
          mpProblem->getScaledResultAnnotated()->setDimensionDescription(dim, tmp.str());

          if (mpProblem->collapsRequested())
            mpProblem->getCollapsedResultAnnotated()->setDimensionDescription(dim2, tmp.str());

          std::vector< CDataObject * > DataObjects = mpProblem->getVariables(i).getVariablesPointerList(pDataModel);
          std::vector< CDataObject * >::const_iterator itDataObject = DataObjects.begin();

          for (j = 0; j < mLocalData[i].mInitialStateVariables.size(); ++j, ++itDataObject)
            {
              mpProblem->getResultAnnotated()->setAnnotation(dim, j, *itDataObject);
              mpProblem->getScaledResultAnnotated()->setAnnotation(dim, j, *itDataObject);

              if (mpProblem->collapsRequested())
                mpProblem->getCollapsedResultAnnotated()->setAnnotation(dim2, j, *itDataObject);
            }

          ++dim;
          ++dim2;
        }
    }

  return success;
}

bool CSensMethod::restore(const bool & /* updateModel */)
{
  bool success = true;

  if (mpSubTask != NULL)
    {
      //the subtask should not change the initial state of the model
      success &= mpSubTask->restore(false);
    }

  return success;
}

size_t CSensMethod::getNumberOfSubtaskCalculations()
{
  size_t ret = 1;
  size_t i;

  for (i = 0; i < mLocalData.size(); ++i)
    {
      ret *= mLocalData[i].mInitialStateVariables.size() + 1;
    }

  return ret;
}

bool CSensMethod::process()
{
  // Reset the evaluation counter
  mCounter = 0;
  mFailedCounter = 0;

  if (!mLocalData.size()) return false;

  // initialize progress bar for the case that the task was not initialized prior to setCallBack
  if (mpSubTask)
    {
      mpSubTask->setCallBack(mProcessReport);
      mpSubTask->setUpdateModel(false);
    }

  if (mProcessReport)
    {
      mProcessReport.setName("performing sensitivities calculation...");
      unsigned C_INT32 max = (unsigned C_INT32) getNumberOfSubtaskCalculations();
      mProgress = 0;
      mProgressHandler = mProcessReport.addItem("Completion",
                         mProgress,
                         &max);
    }

  if (!calculate_one_level(mLocalData.size() - 1, mpProblem->getResult())) return false;

  do_scaling();

  do_collapsing();

  if (mProcessReport) mProcessReport.finishItem(mProgressHandler);

  if (mFailedCounter * 20 > mCounter) // > 5% failure rate
    CCopasiMessage(CCopasiMessage::WARNING, MCCopasiTask + 8, mFailedCounter, mCounter);

  if (mpSubTask)
    {
      mpSubTask->setCallBack(NULL);
      mpSubTask->setUpdateModel(mStoreSubtasktUpdateFlag);
    }

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

// virtual
bool CSensMethod::setCallBack(CProcessReportLevel callBack)
{
  bool success = CCopasiMethod::setCallBack(callBack);

  if (mpSubTask)
    success &= mpSubTask->setCallBack(mProcessReport);

  return success;
}
