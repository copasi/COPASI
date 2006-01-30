/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitProblem.cpp,v $
   $Revision: 1.21.2.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/30 14:55:34 $
   End CVS Header */

#include "copasi.h"

#include "CFitProblem.h"
#include "CFitItem.h"
#include "CFitTask.h"
#include "CExperimentSet.h"
#include "CExperiment.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "utilities/CProcessReport.h"

#include "clapackwrap.h"        //use CLAPACK

//  Default constructor
CFitProblem::CFitProblem(const CCopasiTask::Type & type,
                         const CCopasiContainer * pParent):
    COptProblem(type, pParent),
    mpExperimentSet(NULL),
    mpTrajectoryProblem(NULL),
    mpInitialState(NULL),
    mDependentValues(0),
    mResiduals(0),
    mStoreResults(false)
{initializeParameter();}

// copy constructor
CFitProblem::CFitProblem(const CFitProblem& src,
                         const CCopasiContainer * pParent):
    COptProblem(src, pParent),
    mpExperimentSet(NULL),
    mpTrajectoryProblem(NULL),
    mpInitialState(NULL),
    mDependentValues(src.mDependentValues),
    mResiduals(src.mResiduals),
    mStoreResults(src.mStoreResults)
{initializeParameter();}

// Destructor
CFitProblem::~CFitProblem()
{
  pdelete(mpTrajectoryProblem);
  pdelete(mpInitialState);
}

void CFitProblem::initializeParameter()
{
  removeParameter("ObjectiveFunction");
  removeParameter("Maximize");

  CCopasiVectorN< CCopasiTask > * pTasks = NULL;
  if (CCopasiDataModel::Global)
    pTasks = CCopasiDataModel::Global->getTaskList();
  if (!pTasks)
    pTasks = dynamic_cast<CCopasiVectorN< CCopasiTask > *>(getObjectAncestor("Vector"));

  if (pTasks)
    {
      unsigned C_INT32 i, imax = pTasks->size();

      if (*mpParmSteadyStateKey == "")
        for (i = 0; i < imax; i++)
          if ((*pTasks)[i]->getType() == CCopasiTask::steadyState)
            {
              *mpParmSteadyStateKey = (*pTasks)[i]->getKey();
              break;
            }

      if (*mpParmTimeCourseKey == "")
        for (i = 0; i < imax; i++)
          if ((*pTasks)[i]->getType() == CCopasiTask::timeCourse)
            {
              *mpParmTimeCourseKey = (*pTasks)[i]->getKey();
              break;
            }
    }

  assertGroup("Experiment Set");

  elevateChildren();
}

bool CFitProblem::elevateChildren()
{
  // This call is necessarry since CFitProblem is derived from COptProblem.
  if (!COptProblem::elevateChildren()) return false;

  std::map<std::string, std::string> KeyMap;

  std::vector<CCopasiParameter *> * pExperiments =
    getGroup("Experiment Set")->CCopasiParameter::getValue().pGROUP;
  std::vector<CCopasiParameter *>::iterator itExp;
  std::vector<CCopasiParameter *>::iterator endExp;

  for (itExp = pExperiments->begin(), endExp = pExperiments->end(); itExp != endExp; ++itExp)
    if (static_cast<CCopasiParameterGroup *>(*itExp)->getValue("Key").pKEY)
      KeyMap[*static_cast<CCopasiParameterGroup *>(*itExp)->getValue("Key").pKEY] =
        (*itExp)->getObjectName();

  mpExperimentSet =
    elevate<CExperimentSet, CCopasiParameterGroup>(getGroup("Experiment Set"));
  if (!mpExperimentSet) return false;

  std::map<std::string, std::string>::iterator itMap;
  std::map<std::string, std::string>::iterator endMap;
  CExperiment * pExperiment;
  for (itMap = KeyMap.begin(), endMap = KeyMap.end(); itMap != endMap; ++itMap)
    {
      pExperiment = mpExperimentSet->getExperiment(itMap->second);
      itMap->second = pExperiment->CCopasiParameter::getKey();
      pExperiment->setValue("Key", itMap->second);
    }

  std::vector<COptItem * >::iterator it = mpOptItems->begin();
  std::vector<COptItem * >::iterator end = mpOptItems->end();

  for (; it != end; ++it)
    {
      if (!((*it) = elevate<CFitItem, COptItem>(*it)))
        return false;

      pExperiments =
        (*it)->getParameter("Affected Experiments")->getValue().pGROUP;

      for (itExp = pExperiments->begin(), endExp = pExperiments->end(); itExp != endExp; ++itExp)
        (*itExp)->setValue(KeyMap[*(*itExp)->getValue().pKEY]);
    }

  it = mpConstraintItems->begin();
  end = mpConstraintItems->end();

  for (; it != end; ++it)
    {
      if (!((*it) = elevate<CFitItem, COptItem>(*it)))
        return false;

      pExperiments =
        (*it)->getParameter("Affected Experiments")->getValue().pGROUP;

      for (itExp = pExperiments->begin(), endExp = pExperiments->end(); itExp != endExp; ++itExp)
        (*itExp)->setValue(KeyMap[*(*itExp)->getValue().pKEY]);
    }

  return true;
}

bool CFitProblem::setModel(CModel * pModel)
{return COptProblem::setModel(pModel);}

bool CFitProblem::setCallBack(CProcessReport * pCallBack)
{return COptProblem::setCallBack(pCallBack);}

bool CFitProblem::initialize()
{
  if (!COptProblem::initialize())
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCOptimization + 5)
        return false;
      else
        CCopasiMessage::getLastMessage();
    }

  std::vector< CCopasiContainer * > ContainerList;
  ContainerList.push_back(mpModel);

  CFitTask * pTask = dynamic_cast<CFitTask *>(getObjectParent());
  if (pTask)
    {
      ContainerList.push_back(pTask);
      ContainerList.push_back(mpSteadyState);
      ContainerList.push_back(mpTrajectory);
    }

  if (!mpExperimentSet->compile(ContainerList)) return false;

  // Build a matrix of experiment and experiment local items.
  mExperimentUpdateMethods.resize(mpExperimentSet->size(),
                                  mpOptItems->size());
  mExperimentUpdateMethods = NULL;

  std::vector<COptItem * >::iterator it = mpOptItems->begin();
  std::vector<COptItem * >::iterator end = mpOptItems->end();

  std::vector<COptItem * >::iterator itTmp;

  CFitItem * pItem;
  unsigned C_INT32 i, imax;
  unsigned C_INT32 j;
  unsigned C_INT32 Index;

  for (j = 0; it != end; ++it, j++)
    {
      pItem = static_cast<CFitItem *>(*it);
      pItem->updateBounds(mpOptItems->begin());

      imax = pItem->getExperimentCount();
      if (imax == 0)
        {
          for (i = 0, imax = mpExperimentSet->size(); i < imax; i++)
            mExperimentUpdateMethods(i, j) = pItem->COptItem::getUpdateMethod();
        }
      else
        {
          for (i = 0; i < imax; i++)
            {
              if ((Index = mpExperimentSet->keyToIndex(pItem->getExperiment(i))) == C_INVALID_INDEX)
                return false;
              mExperimentUpdateMethods(Index, j) = pItem->COptItem::getUpdateMethod();
            };
        }
    }

  pdelete(mpTrajectoryProblem);
  mpTrajectoryProblem =
    new CTrajectoryProblem(*static_cast<CTrajectoryProblem *>(mpTrajectory->getProblem()));

  static_cast<CTrajectoryProblem *>(mpTrajectory->getProblem())->setStepNumber(1);

  pdelete(mpInitialState);
  mpInitialState = new CState(mpModel->getInitialState());

  mDependentValues.resize(mpExperimentSet->getDataPointCount());

  return true;
}

bool CFitProblem::restoreTrajectoryProblem()
{
  if (mpTrajectoryProblem)
    *mpTrajectory->getProblem() = *mpTrajectoryProblem;

  pdelete(mpTrajectoryProblem);
  pdelete(mpInitialState);

  return true;
}

bool CFitProblem::calculate()
{
  mCounter += 1;
  bool Continue = true;

  unsigned i, imax = mpExperimentSet->size();
  unsigned j, jmax = mpOptItems->size();
  unsigned kmax;
  mCalculateValue = 0.0;

  CExperiment * pExp = NULL;

  C_FLOAT64 * Residuals = mResiduals.array();
  C_FLOAT64 * DependentValues = mDependentValues.array();
  UpdateMethod ** pUpdate = mExperimentUpdateMethods.array();
  std::vector<COptItem *>::iterator itItem;
  std::vector<COptItem *>::iterator endItem = mpOptItems->end();

  try
    {
      for (i = 0; i < imax && Continue; i++) // For each experiment
        {
          pExp = mpExperimentSet->getExperiment(i);

          mpModel->setInitialState(mpInitialState);

          // set the global and experiment local fit item values.
          for (itItem = mpOptItems->begin(); itItem != endItem; itItem++, pUpdate++)
            if (*pUpdate)
              (**pUpdate)(static_cast<CFitItem *>(*itItem)->getLocalValue());

          kmax = pExp->getNumDataRows();

          switch (pExp->getExperimentType())
            {
            case CCopasiTask::steadyState:
              // set independent data
              for (j = 0; j < kmax && Continue; j++) // For each data row;
                {
                  pExp->updateModelWithIndependentData(j);
                  Continue = mpSteadyState->process(true);

                  if (!Continue)
                    {
                      mCalculateValue = DBL_MAX;
                      break;
                    }

                  mCalculateValue += pExp->sumOfSquares(j, DependentValues, Residuals);
                  if (mStoreResults) pExp->storeCalculatedValues(j);
                }
              break;

            case CCopasiTask::timeCourse:
              for (j = 0; j < kmax && Continue; j++) // For each data row;
                {
                  if (j)
                    {
                      Continue = mpTrajectory->processStep(pExp->getTimeData()[j]);
                    }
                  else
                    {
                      // set independent data
                      pExp->updateModelWithIndependentData(j);
                      mpTrajectory->processStart(true);

                      if (pExp->getTimeData()[0] != mpModel->getInitialTime())
                        {
                          Continue = mpTrajectory->processStep(pExp->getTimeData()[0]);
                        }
                    }

                  mCalculateValue += pExp->sumOfSquares(j, DependentValues, Residuals);
                  if (mStoreResults) pExp->storeCalculatedValues(j);
                }
              break;

            default:
              break;
            }

          // restore independent data
          pExp->restoreModelIndependentData();

          switch (pExp->getExperimentType())
            {
            case CCopasiTask::steadyState:
              mpSteadyState->restore();
              break;

            case CCopasiTask::timeCourse:
              mpTrajectory->restore();
              break;

            default:
              break;
            }
        }
    }

  catch (...)
    {
      mCalculateValue = DBL_MAX;
      if (pExp) pExp->restoreModelIndependentData();
    }

  if (mpCallBack) return mpCallBack->progress(mhCounter);

  return true;
}

bool CFitProblem::restore(const bool & updateModel)
{
  bool success = COptProblem::restore(updateModel);

  if (!updateModel) return success;

  std::vector<COptItem * >::iterator it = mpOptItems->begin();
  std::vector<COptItem * >::iterator end = mpOptItems->end();
  C_FLOAT64 * pTmp = mSolutionVariables.array();

  for (; it != end; ++it, pTmp++)
    success &= static_cast<CFitItem *>(*it)->setSavedValue(*pTmp);

  return success;
}

void CFitProblem::print(std::ostream * ostream) const
{*ostream << *this;}

void CFitProblem::printResult(std::ostream * ostream) const
  {
    std::ostream & os = *ostream;

    if (mSolutionVariables.numSize() == 0)
      {
        return;
      }

    os << "Objective Function Value:\t" << mSolutionValue << std::endl;
    os << "Standard Deviation:\t" << mSD << std::endl;

    CCopasiTimeVariable CPUTime = const_cast<CFitProblem *>(this)->mCPUTime.getElapsedTime();

    os << "Function Evaluations:\t" << mCounter << std::endl;
    os << "CPU Time [s]:\t"
    << CCopasiTimeVariable::LL2String(CPUTime.getSeconds(), 1) << "."
    << CCopasiTimeVariable::LL2String(CPUTime.getMilliSeconds(true), 3) << std::endl;
    os << "Evaluations/Second [1/s]:\t" << mCounter / (C_FLOAT64) (CPUTime.getMilliSeconds() / 1e3) << std::endl;
    os << std::endl;

    std::vector< COptItem * >::const_iterator itItem =
      mpOptItems->begin();
    std::vector< COptItem * >::const_iterator endItem =
      mpOptItems->end();

    CFitItem * pFitItem;
    CExperiment * pExperiment;

    unsigned C_INT32 i, j;

    os << "\tParameter\tValue\tGradient\tStandard Deviation" << std::endl;
    for (i = 0; itItem != endItem; ++itItem, i++)
      {
        os << "\t" << (*itItem)->getObjectDisplayName();
        pFitItem = static_cast<CFitItem *>(*itItem);

        if (pFitItem->getExperimentCount() != 0)
          {
            os << " (";

            for (j = 0; j < pFitItem->getExperimentCount(); j++)
              {
                if (j) os << ", ";

                pExperiment =
                  dynamic_cast< CExperiment * >(GlobalKeys.get(pFitItem->getExperiment(j)));

                if (pExperiment)
                  os << pExperiment->getObjectName();
              }

            os << ")";
          }

        os << ":\t" << mSolutionVariables[i];
        os << "\t" << mGradient[i];
        os << "\t" << mParameterSD[i];
        os << std::endl;
      }

    os << std::endl;
    os << "Parameter Interdependence:" << std::endl;
    os << "  " << mFisher << std::endl;

    unsigned C_INT32 k, kmax = mpExperimentSet->size();

    for (k = 0; k < kmax; k++)
      {
        mpExperimentSet->getExperiment(k)->printResult(ostream);
        os << std::endl;
      }
  }

std::ostream &operator<<(std::ostream &os, const CFitProblem & o)
{
  os << "Problem Description:" << std::endl;

  os << "Subtask: " << std::endl;

  if (o.mpSteadyState)
    o.mpSteadyState->getDescription().print(&os);

  if (o.mpTrajectory)
    o.mpTrajectory->getDescription().print(&os);

  if (!o.mpTrajectory && !o.mpSteadyState)
    os << "No Subtask specified.";

  os << std::endl;

  os << "List of Fitting Items:" << std::endl;

  std::vector< COptItem * >::const_iterator itItem =
    o.mpOptItems->begin();
  std::vector< COptItem * >::const_iterator endItem =
    o.mpOptItems->end();

  for (; itItem != endItem; ++itItem)
    os << "    " << *static_cast<CFitItem *>(*itItem) << std::endl;

  itItem = o.mpConstraintItems->begin();
  endItem = o.mpConstraintItems->end();

  for (; itItem != endItem; ++itItem)
    os << "    " << *static_cast<CFitItem *>(*itItem) << std::endl;

  return os;
}

bool CFitProblem::createObjectiveFunction()
{return true;}

const CVector< C_FLOAT64 > & CFitProblem::getDependentValues() const
  {return mDependentValues;}

bool CFitProblem::setResidualsRequired(const bool & required)
{
  if (required)
    mResiduals.resize(mpExperimentSet->getDataPointCount());
  else
    mResiduals.resize(0);

  return true;
}

const CVector< C_FLOAT64 > & CFitProblem::getResiduals() const
{return mResiduals;}

bool CFitProblem::calculateStatistics(const C_FLOAT64 & factor,
                                      const C_FLOAT64 & resolution)
{
  // Set the current values to the solution values.
  unsigned C_INT32 i, imax = mSolutionVariables.size();
  unsigned C_INT32 j, jmax = mDependentValues.size();
  unsigned C_INT32 l;
  unsigned C_INT32 k, kmax = mpExperimentSet->size();

  for (i = 0; i < imax; i++)
    (*mUpdateMethods[i])(mSolutionVariables[i]);

  mStoreResults = true;
  calculate();
  mStoreResults = false;

  for (k = 0; k < kmax; k++)
    mpExperimentSet->getExperiment(k)->calculateStatistics();

  // Keep the results
  C_FLOAT64 SumOfSquares = mCalculateValue;
  CVector< C_FLOAT64 > DependentValues = mDependentValues;

  mSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  mParameterSD.resize(imax);
  mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  if (jmax > imax)
    mSD = sqrt(SumOfSquares / jmax);

  mFisher.resize(imax, imax);

  mGradient.resize(imax);

  CMatrix< C_FLOAT64 > dyp;
  dyp.resize(imax, jmax);

  C_FLOAT64 Current;
  C_FLOAT64 Delta;

  // Calculate the gradient
  for (i = 0; i < imax; i++)
    {
      Current = mSolutionVariables[i];

      if (fabs(Current) > resolution)
        {
          (*mUpdateMethods[i])(Current * (1.0 + factor));
          Delta = 1.0 / (Current * factor);
        }
      else
        {
          (*mUpdateMethods[i])(resolution);
          Delta = 1.0 / resolution;
        }

      calculate();

      mGradient[i] = (mCalculateValue - SumOfSquares) * Delta;

      for (j = 0; j < jmax; j++)
        dyp(i, j) = (mDependentValues[j] - DependentValues[j]) * Delta;

      // Restore the value
      (*mUpdateMethods[i])(Current);
    }

  // Construct the fisher information matrix
  for (i = 0; i < imax; i++)
    for (l = 0; l <= i; l++)
      {
        C_FLOAT64 & tmp = mFisher(i, l);

        tmp = 0.0;

        for (j = 0; j < jmax; j++)
          tmp += dyp(i, j) * dyp(l, j);

        tmp *= 2.0;

        //        if (l != i)
        //          mFisher(l, i) = tmp;
      }

  /* We use dsytrf_ and dsytri_ to invert the symmetric fisher information matrix */

  /* int dsytrf_(char *uplo,
   *             integer *n, 
   *             doublereal *a, 
   *             integer * lda, 
   *             integer *ipiv, 
   *             doublereal *work, 
   *             integer *lwork, 
   *             integer *info);
   *
   *  -- LAPACK routine (version 3.0) --
   *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
   *     Courant Institute, Argonne National Lab, and Rice University
   *     June 30, 1999
   *
   *  Purpose
   *  =======
   *
   *  DSYTRF computes the factorization of a real symmetric matrix A using
   *  the Bunch-Kaufman diagonal pivoting method.  The form of the
   *  factorization is
   *
   *     A = U*D*U**T  or  A = L*D*L**T
   *
   *  where U (or L) is a product of permutation and unit upper (lower)
   *  triangular matrices, and D is symmetric and block diagonal with
   *  1-by-1 and 2-by-2 diagonal blocks.
   *
   *  This is the blocked version of the algorithm, calling Level 3 BLAS.
   *
   *  Arguments
   *  =========
   *
   *  UPLO    (input) CHARACTER*1
   *          = 'U':  Upper triangle of A is stored;
   *          = 'L':  Lower triangle of A is stored.
   *
   *  N       (input) INTEGER
   *          The order of the matrix A.  N >= 0.
   *
   *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
   *          On entry, the symmetric matrix A.  If UPLO = 'U', the leading
   *          N-by-N upper triangular part of A contains the upper
   *          triangular part of the matrix A, and the strictly lower
   *          triangular part of A is not referenced.  If UPLO = 'L', the
   *          leading N-by-N lower triangular part of A contains the lower
   *          triangular part of the matrix A, and the strictly upper
   *          triangular part of A is not referenced.
   *
   *          On exit, the block diagonal matrix D and the multipliers used
   *          to obtain the factor U or L (see below for further details).
   *
   *  LDA     (input) INTEGER
   *          The leading dimension of the array A.  LDA >= max(1,N).
   *
   *  IPIV    (output) INTEGER array, dimension (N)
   *          Details of the interchanges and the block structure of D.
   *          If IPIV(k) > 0, then rows and columns k and IPIV(k) were
   *          interchanged and D(k,k) is a 1-by-1 diagonal block.
   *          If UPLO = 'U' and IPIV(k) = IPIV(k-1) < 0, then rows and
   *          columns k-1 and -IPIV(k) were interchanged and D(k-1:k,k-1:k)
   *          is a 2-by-2 diagonal block.  If UPLO = 'L' and IPIV(k) =
   *          IPIV(k+1) < 0, then rows and columns k+1 and -IPIV(k) were
   *          interchanged and D(k:k+1,k:k+1) is a 2-by-2 diagonal block.
   *
   *  WORK    (workspace/output) DOUBLE PRECISION array, dimension (LWORK)
   *          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
   *
   *  LWORK   (input) INTEGER
   *          The length of WORK.  LWORK >=1.  For best performance
   *          LWORK >= N*NB, where NB is the block size returned by ILAENV.
   *
   *          If LWORK = -1, then a workspace query is assumed; the routine
   *          only calculates the optimal size of the WORK array, returns
   *          this value as the first entry of the WORK array, and no error
   *          message related to LWORK is issued by XERBLA.
   *
   *  INFO    (output) INTEGER
   *          = 0:  successful exit
   *          < 0:  if INFO = -i, the i-th argument had an illegal value
   *          > 0:  if INFO = i, D(i,i) is exactly zero.  The factorization
   *                has been completed, but the block diagonal matrix D is
   *                exactly singular, and division by zero will occur if it
   *                is used to solve a system of equations.
   *
   *  Further Details
   *  ===============
   *
   *  If UPLO = 'U', then A = U*D*U', where
   *     U = P(n)*U(n)* ... *P(k)U(k)* ...,
   *  i.e., U is a product of terms P(k)*U(k), where k decreases from n to
   *  1 in steps of 1 or 2, and D is a block diagonal matrix with 1-by-1
   *  and 2-by-2 diagonal blocks D(k).  P(k) is a permutation matrix as
   *  defined by IPIV(k), and U(k) is a unit upper triangular matrix, such
   *  that if the diagonal block D(k) is of order s (s = 1 or 2), then
   *
   *             (I    v    0)   k-s
   *     U(k) =  (0    I    0)   s
   *             (0    0    I)   n-k
   *                k-s   s   n-k
   *
   *  If s = 1, D(k) overwrites A(k,k), and v overwrites A(1:k-1,k).
   *  If s = 2, the upper triangle of D(k) overwrites A(k-1,k-1), A(k-1,k),
   *  and A(k,k), and v overwrites A(1:k-2,k-1:k).
   *
   *  If UPLO = 'L', then A = L*D*L', where
   *     L = P(1)*L(1)* ... *P(k)*L(k)* ...,
   *  i.e., L is a product of terms P(k)*L(k), where k increases from 1 to
   *  n in steps of 1 or 2, and D is a block diagonal matrix with 1-by-1
   *  and 2-by-2 diagonal blocks D(k).  P(k) is a permutation matrix as
   *  defined by IPIV(k), and L(k) is a unit lower triangular matrix, such
   *  that if the diagonal block D(k) is of order s (s = 1 or 2), then
   *
   *             (I    0     0)  k-1
   *     L(k) =  (0    I     0)  s
   *             (0    v     I)  n-k-s+1
   *                k-1   s  n-k-s+1
   *
   *  If s = 1, D(k) overwrites A(k,k), and v overwrites A(k+1:n,k).
   *  If s = 2, the lower triangle of D(k) overwrites A(k,k), A(k+1,k),
   *  and A(k+1,k+1), and v overwrites A(k+2:n,k:k+1).
   *
   */

  char U = 'U';
  C_INT info = 0;
  C_INT N = imax;

  CVector< C_INT > ipiv;
  ipiv.resize(imax);

  C_INT lwork = -1; // Instruct dsytrf_ to determine work array size.
  CVector< C_FLOAT64 > work;
  work.resize(1);

  dsytrf_(&U, &N, mFisher.array(), &N, ipiv.array(), work.array(), &lwork, &info);
  if (info)
    {
      mFisher = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

      return false; // :TODO: create error message
    }

  lwork = (C_INT) work[0];
  work.resize(lwork);

  dsytrf_(&U, &N, mFisher.array(), &N, ipiv.array(), work.array(), &lwork, &info);
  if (info)
    {
      mFisher = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 2, info);

      return false;
    }

  /* int dsytri_(char *uplo,
   *             integer *n, 
   *             doublereal *a,
   *             integer * lda,
   *             integer *ipiv,
   *             doublereal *work,
   *             integer *info);
   *
   *  -- LAPACK routine (version 3.0) --
   *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
   *     Courant Institute, Argonne National Lab, and Rice University
   *     March 31, 1993
   *
   *  Purpose
   *  =======
   *
   *  DSYTRI computes the inverse of a real symmetric indefinite matrix
   *  A using the factorization A = U*D*U**T or A = L*D*L**T computed by
   *  DSYTRF.
   *
   *  Arguments
   *  =========
   *
   *  UPLO    (input) CHARACTER*1
   *          Specifies whether the details of the factorization are stored
   *          as an upper or lower triangular matrix.
   *          = 'U':  Upper triangular, form is A = U*D*U**T;
   *          = 'L':  Lower triangular, form is A = L*D*L**T.
   *
   *  N       (input) INTEGER
   *          The order of the matrix A.  N >= 0.
   *
   *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
   *          On entry, the block diagonal matrix D and the multipliers
   *          used to obtain the factor U or L as computed by DSYTRF.
   *
   *          On exit, if INFO = 0, the (symmetric) inverse of the original
   *          matrix.  If UPLO = 'U', the upper triangular part of the
   *          inverse is formed and the part of A below the diagonal is not
   *          referenced; if UPLO = 'L' the lower triangular part of the
   *          inverse is formed and the part of A above the diagonal is
   *          not referenced.
   *
   *  LDA     (input) INTEGER
   *          The leading dimension of the array A.  LDA >= max(1,N).
   *
   *  IPIV    (input) INTEGER array, dimension (N)
   *          Details of the interchanges and the block structure of D
   *          as determined by DSYTRF.
   *
   *  WORK    (workspace) DOUBLE PRECISION array, dimension (N)
   *
   *  INFO    (output) INTEGER
   *          = 0: successful exit
   *          < 0: if INFO = -i, the i-th argument had an illegal value
   *          > 0: if INFO = i, D(i,i) = 0; the matrix is singular and its
   *               inverse could not be computed.
   *
   */
  dsytri_(&U, &N, mFisher.array(), &N, ipiv.array(), work.array(), &info);
  if (info)
    return false; // :TODO: create error message

  // rescale the lower bound of the covariant matrix to have unit diagonal
  for (i = 0; i < imax; i++)
    {
      C_FLOAT64 & tmp = mFisher(i, i);

      tmp = sqrt(tmp);
      mParameterSD[i] = mSD * tmp;
    }

  for (i = 0; i < imax; i++)
    for (l = 0; l < i; l++)
      {
        mFisher(i, l) /= mFisher(i, i) * mFisher(l, l);
        mFisher(l, i) = mFisher(i, l);
      }

  for (i = 0; i < imax; i++)
    mFisher(i, i) = 1.0;

  return true;
}
