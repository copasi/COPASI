// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensMethod.cpp,v $
//   $Revision: 1.36 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/09 18:50:09 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CSensMethod class.
 */

#include "copasi.h"

//#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "CSensMethod.h"
#include "CSensProblem.h"

#include "model/CModel.h"
#include "model/CState.h"
#include "utilities/CProcessReport.h"

CSensMethod *
CSensMethod::createMethod(CCopasiMethod::SubType subType)
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
    mpProblem(NULL),
    mLocalData(),
    mTargetfunctionPointers(),
    mpSubTask(NULL),
    mInitialRefreshes(),
    mpDeltaFactor(NULL),
    mpMinDelta(NULL),
    mProgressHandler(C_INVALID_INDEX),
    mProgress(0),
    mCounter(0),
    mFailedCounter(0)
{
  addParameter("Delta factor",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1e-3);
  mpDeltaFactor = (C_FLOAT64*)getValue("Delta factor").pUDOUBLE;

  addParameter("Delta minimum",
               CCopasiParameter::UDOUBLE, (C_FLOAT64) 1e-12);
  mpMinDelta = (C_FLOAT64*)getValue("Delta minimum").pUDOUBLE;

  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CSensMethod &" src
 */
CSensMethod::CSensMethod(const CSensMethod & src,
                         const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mpProblem(src.mpProblem),
    mLocalData(),
    mTargetfunctionPointers(),
    mpSubTask(NULL),
    mInitialRefreshes(),
    mpDeltaFactor(NULL),
    mpMinDelta(NULL),
    mProgressHandler(C_INVALID_INDEX),
    mProgress(0),
    mCounter(0),
    mFailedCounter(0)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CSensMethod::~CSensMethod()
{DESTRUCTOR_TRACE;}

//***********************************************************************************

bool CSensMethod::do_target_calculation(CCopasiArray & result, bool /* first */)
{
  bool success = false;

  //perform the necessary updates
  std::vector< Refresh * >::iterator it = mInitialRefreshes.begin();
  std::vector< Refresh * >::iterator end = mInitialRefreshes.end();

  while (it != end)
    (**it++)();

  //****** do subtask ******************
  if (mpSubTask != NULL)
    {
      success = mpSubTask->process(/*first*/true);
      mCounter++;
    }
  else
    {
      success = true; // doing nothing should never fail.
    }

  mpProblem->getModel()->updateSimulatedValues(true);
  mpProblem->getModel()->updateNonSimulatedValues();

  //****** retrieve results ************

  //resize results array
  CCopasiArray::index_type resultindex;
  size_t i, imax = mTargetfunctionPointers.size();

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

          result[resultindex] = *(C_FLOAT64 *)mTargetfunctionPointers[i]->getValuePointer();
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

  if (mpCallBack)
    {
      bool tmp = mpCallBack->progressItem(mProgressHandler);
      return tmp;
    }

  return success;
}

C_FLOAT64 CSensMethod::do_variation(CCopasiObject* variable)
{
  C_FLOAT64 value;
  value = *(C_FLOAT64*)variable->getValuePointer();
  C_FLOAT64 delta;
  delta = fabs(value) * *mpDeltaFactor;

  if (delta < *mpMinDelta) delta = *mpMinDelta;

  setValue(variable, delta + value);

  return delta;
}

void CSensMethod::setValue(CCopasiObject* variable, C_FLOAT64 value)
{
  variable->setObjectValue(value);

  if (variable->getObjectName() == "Concentration")
    {
      CMetab* pMetab = dynamic_cast<CMetab*>(variable->getObjectAncestor("Metabolite"));

      if (pMetab)
        {
          pMetab->setConcentration(value);
          pMetab->refreshNumber();
        }
    }
}

void CSensMethod::calculate_difference(size_t level, const C_FLOAT64 & delta,
                                       CCopasiArray & result, CCopasiArray::index_type & resultindex)
{
  assert(delta != 0.0);
  assert(mLocalData[level].tmp1.size() == mLocalData[level].tmp2.size());
  size_t dim = mLocalData[level].tmp1.dimensionality();
  assert(resultindex.size() >= dim);

  CCopasiArray::index_type indexmax = mLocalData[level].tmp1.size();

  //init index with zero
  CCopasiArray::index_type indexit; indexit.resize(dim);
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

bool CSensMethod::calculate_one_level(size_t level, CCopasiArray & result)
{
  //do first calculation
  if (level == 0)
    {
      if (!do_target_calculation(mLocalData[level].tmp1, true)) return false;
    }
  else
    {
      if (!calculate_one_level(level - 1, mLocalData[level].tmp1)) return false;
    }

  //resize results array
  CCopasiArray::index_type resultindex; resultindex = mLocalData[level].tmp1.size();

  if (mLocalData[level].variables.size() > 1)
    resultindex.push_back(mLocalData[level].variables.size());

  result.resize(resultindex);

  //loop over all variables
  size_t i, imax = mLocalData[level].variables.size();

  for (i = 0; i < imax; ++i)
    {
      //store variable value
      C_FLOAT64 store = *(C_FLOAT64 *)mLocalData[level].variables[i]->getValuePointer();

      //change variable
      C_FLOAT64 delta = do_variation(mLocalData[level].variables[i]);

      //do second calculation
      if (level == 0)
        {
          if (!do_target_calculation(mLocalData[level].tmp2, false)) return false;
        }
      else
        {
          if (!calculate_one_level(level - 1, mLocalData[level].tmp2)) return false;
        }

      //restore variable
      //mLocalData[level].variables[i]->setObjectValue(store);
      setValue(mLocalData[level].variables[i], store);

      //calculate derivative
      if (imax > 1)
        resultindex[resultindex.size() - 1] = i;

      calculate_difference(level, delta, result, resultindex);
    }

  return true;
}

//********** SCALING *************************************************************

void CSensMethod::scaling_targetfunction(const C_FLOAT64 & factor,
    CCopasiArray::index_type & resultindex)
{
  size_t dim = mLocalData[0].tmp1.dimensionality();
  assert(resultindex.size() >= dim);

  CCopasiArray::index_type indexmax = mLocalData[0].tmp1.size();
  //init index with zero
  CCopasiArray::index_type indexit; indexit.resize(dim);
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
                                    CCopasiArray::index_type & resultindex)
{
  //loop over all variables
  size_t i, imax = mLocalData[level].variables.size();

  for (i = 0; i < imax; ++i)
    {
      //get Value
      C_FLOAT64 value = *(C_FLOAT64 *)mLocalData[level].variables[i]->getValuePointer() * factor;

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
  CCopasiArray::index_type index;
  index.resize(mpProblem->getResult().dimensionality());
  scaling_variables(mLocalData.size() - 1, 1.0, index);
}

//****************************************************************************

C_FLOAT64 CSensMethod::do_collapsing_innerloop(CCopasiArray::index_type & fullindex)
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

      if (fabs(tmpFloat) >= DBL_MAX) continue;

      tmpSum += tmpFloat * tmpFloat;
    }

  return sqrt(tmpSum);
}

void CSensMethod::do_collapsing()
{
  if (mpProblem->collapsRequested())
    {
      CCopasiArray::index_type fullresultindex = mpProblem->getScaledResult().size();
      CCopasiArray::index_type collapsedresultindex = mpProblem->getCollapsedResult().size();

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
      CCopasiArray::index_type indexmax = mpProblem->getCollapsedResult().size();

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
    {}}

//****************************************************************************

bool CSensMethod::initialize(CSensProblem* problem)
{
  bool success = true;

  mpProblem = problem;
  assert(mpProblem);

  //initialize the target calculation
  mpSubTask = NULL;
  CCopasiDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);

  switch (mpProblem->getSubTaskType())
    {
      case CSensProblem::Evaluation:
        mpSubTask = NULL;
        break;

      case CSensProblem::SteadyState:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    ((*pDataModel->getTaskList())["Steady-State"]);
        break;

      case CSensProblem::TimeSeries:
        mpSubTask = dynamic_cast<CCopasiTask*>
                    ((*pDataModel->getTaskList())["Time-Course"]);
        break;

        /*    case CSensProblem::LyapunovExp:
              mpSubTask = dynamic_cast<CCopasiTask*>
                          ((*pDataModel->getTaskList())["Lyapunov Exponents"]);
              break;*/
    }

  if (mpSubTask)
    {
      mpSubTask->getProblem()->setModel(mpProblem->getModel());
      mpSubTask->setCallBack(NULL);
      success &= mpSubTask->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
    }

  //initialize the variables pointers
  std::set< const CCopasiObject * > ObjectSet;
  size_t i, imax = mpProblem->getNumberOfVariables();
  mLocalData.resize(imax);

  for (i = 0; i < imax; ++i)
    {
      mLocalData[i].variables = mpProblem->getVariables(i).getVariablesPointerList(pDataModel);

      ObjectSet.insert(mLocalData[i].variables.begin(), mLocalData[i].variables.end());
    }

  //determine which refreshes need to be called when the variables are changed
  ObjectSet.erase(NULL);
  mInitialRefreshes.clear();
  mInitialRefreshes = mpProblem->getModel()->buildInitialRefreshSequence(ObjectSet);

  //initialize the target function pointers
  mTargetfunctionPointers = mpProblem->getTargetFunctions().getVariablesPointerList(pDataModel);

  //****** initialize result annotations ****************

  //determine dimensions of result
  CCopasiArray::index_type s;
  CCopasiArray::index_type sc; //size of collapsed result

  if (mTargetfunctionPointers.size() > 1)
    {
      s.push_back(mTargetfunctionPointers.size());
    }

  for (i = 0; i < imax; ++i)
    {
      if (mLocalData[i].variables.size() > 1)
        {
          mLocalData[i].index = s.size();
          s.push_back(mLocalData[i].variables.size());
          sc.push_back(mLocalData[i].variables.size());
        }
      else
        mLocalData[i].index = -1;
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

  //target function annotations //TODO: only implemented for scalar and vector
  if (mTargetfunctionPointers.size() > 1)
    {
      std::ostringstream tmp;
      tmp << "Target functions, " << mpProblem->getTargetFunctions().getListTypeDisplayName();
      mpProblem->getResultAnnotated()->setDimensionDescription(dim, tmp.str());
      mpProblem->getScaledResultAnnotated()->setDimensionDescription(dim, tmp.str());

      for (j = 0; j < mTargetfunctionPointers.size(); ++j)
        {
          mpProblem->getResultAnnotated()->setAnnotationCN(dim, j, mTargetfunctionPointers[j]->getCN());
          mpProblem->getScaledResultAnnotated()->setAnnotationCN(dim, j, mTargetfunctionPointers[j]->getCN());
        }

      ++dim;
    }

  //variables annotiation
  size_t dim2 = 0; //for collapsed result

  for (i = 0; i < imax; ++i)
    {
      if (mLocalData[i].variables.size() > 1)
        {
          std::ostringstream tmp;
          tmp << "Variables " << i + 1 << ", " << mpProblem->getVariables(i).getListTypeDisplayName();
          mpProblem->getResultAnnotated()->setDimensionDescription(dim, tmp.str());
          mpProblem->getScaledResultAnnotated()->setDimensionDescription(dim, tmp.str());

          if (mpProblem->collapsRequested())
            mpProblem->getCollapsedResultAnnotated()->setDimensionDescription(dim2, tmp.str());

          for (j = 0; j < mLocalData[i].variables.size(); ++j)
            {
              mpProblem->getResultAnnotated()->setAnnotationCN(dim, j, mLocalData[i].variables[j]->getCN());
              mpProblem->getScaledResultAnnotated()->setAnnotationCN(dim, j, mLocalData[i].variables[j]->getCN());

              if (mpProblem->collapsRequested())
                mpProblem->getCollapsedResultAnnotated()->setAnnotationCN(dim2, j, mLocalData[i].variables[j]->getCN());
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
    success &= mpSubTask->restore();

  return success;
}

size_t CSensMethod::getNumberOfSubtaskCalculations()
{
  size_t ret = 1;
  size_t i;

  for (i = 0; i < mLocalData.size(); ++i)
    {
      ret *= mLocalData[i].variables.size() + 1;
    }

  return ret;
}

bool CSensMethod::process(CProcessReport * handler)
{
  // Reset the evaluation counter
  mCounter = 0;
  mFailedCounter = 0;

  if (!mLocalData.size()) return false;

  //initialize progress bar
  mpCallBack = handler;

  if (mpCallBack)
    {
      mpCallBack->setName("performing sensitivities calculation...");
      unsigned C_INT32 max = (unsigned C_INT32) getNumberOfSubtaskCalculations();
      mProgress = 0;
      mProgressHandler = mpCallBack->addItem("Completion",
                                             mProgress,
                                             &max);

      if (mpSubTask)
        mpSubTask->setCallBack(mpCallBack);
    }

  if (!calculate_one_level(mLocalData.size() - 1, mpProblem->getResult())) return false;

  do_scaling();

  do_collapsing();

  if (mpCallBack) mpCallBack->finishItem(mProgressHandler);

  if (mFailedCounter * 20 > mCounter) // > 5% failure rate
    CCopasiMessage(CCopasiMessage::WARNING, MCCopasiTask + 8, mFailedCounter, mCounter);

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
