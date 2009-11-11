// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CBitPatternTreeMethod.cpp,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/11/11 17:39:45 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CBitPatternTreeMethod.h"
#include "CEFMProblem.h"
#include "CEFMTask.h"
#include "CStepMatrix.h"
#include "CBitPatternTree.h"

#include "model/CModel.h"
#include "utilities/CProcessReport.h"
#include "report/CCopasiObjectReference.h"

#include "blaswrap.h"
#include "clapackwrap.h"

#define DEBUG_MATRIX

CBitPatternTreeMethod::CBitPatternTreeMethod(const CCopasiContainer * pParent):
    CEFMMethod(CCopasiTask::fluxMode, CCopasiMethod::EFMBitPatternTreeAlgorithm, pParent),
    mpModel(NULL),
    mProgressCounter(0),
    mProgressCounterMax(0),
    mhProgressCounter(0),
    mpStepMatrix(NULL),
    mpNullTree(NULL),
    mMinimumSetSize(0),
    mStep(0)
{
  initObjects();
}

CBitPatternTreeMethod::CBitPatternTreeMethod(const CCopasiMethod::SubType subType,
    const CCopasiContainer * pParent):
    CEFMMethod(CCopasiTask::fluxMode, subType, pParent),
    mpModel(NULL),
    mProgressCounter(0),
    mProgressCounterMax(0),
    mhProgressCounter(0),
    mpStepMatrix(NULL),
    mpNullTree(NULL),
    mMinimumSetSize(0),
    mStep(0)
{
  initObjects();
}

CBitPatternTreeMethod::CBitPatternTreeMethod(const CBitPatternTreeMethod & src,
    const CCopasiContainer * pParent):
    CEFMMethod(src, pParent),
    mpModel(src.mpModel),
    mProgressCounter(src.mProgressCounter),
    mProgressCounterMax(src.mProgressCounterMax),
    mhProgressCounter(src.mhProgressCounter),
    mpStepMatrix(src.mpStepMatrix),
    mpNullTree(src.mpNullTree),
    mMinimumSetSize(src.mMinimumSetSize),
    mStep(src.mStep)
{
  initObjects();
}

CBitPatternTreeMethod::~CBitPatternTreeMethod()
{
  pdelete(mpNullTree);
}

void CBitPatternTreeMethod::initObjects()
{
  addObjectReference("Current Step", mProgressCounter, CCopasiObject::ValueInt);
}

bool CBitPatternTreeMethod::initialize()
{
  pdelete(mpStepMatrix);
  mReactionForward.clear();
  mReorderedReactions.clear();
  mFluxModes.clear();

  CEFMTask * pTask = dynamic_cast< CEFMTask *>(getObjectParent());

  if (pTask == NULL) return false;

  mpModel = pTask->getProblem()->getModel();

  if (mpModel == NULL) return false;

  // We first build the kernel matrix
  CMatrix< C_INT32 > KernelMatrix;
  buildKernelMatrix(KernelMatrix);

  mMinimumSetSize = KernelMatrix.numRows() - KernelMatrix.numCols() - 2;

  // Now we create the initial step matrix
  mpStepMatrix = new CStepMatrix(KernelMatrix);

  mProgressCounter = 0;
  mProgressCounterMax = mpStepMatrix->getNumUnconvertedRows();

  if (mpCallBack)
    mhProgressCounter =
      mpCallBack->addItem("Current Step",
                          CCopasiParameter::UINT,
                          & mProgressCounter,
                          & mProgressCounterMax);

  return true;
}

bool CBitPatternTreeMethod::calculate()
{
  bool Continue = true;

  if (!initialize())
    {
      if (mpCallBack)
        mpCallBack->finish(mhProgressCounter);

      return false;
    }

  while (mpStepMatrix->getNumUnconvertedRows() > 0 &&
         Continue)
    {
      mStep = mpStepMatrix->getFirstUnconvertedRow();

      std::list< CStepMatrixColumn * > PositiveColumns;
      std::list< CStepMatrixColumn * > NegativeColumns;
      std::list< CStepMatrixColumn * > NullColumns;

      if (mpStepMatrix->splitColumns(PositiveColumns,
                                     NegativeColumns,
                                     NullColumns))
        {
          // Process each step.
          // We need to update the bit pattern tree.
          pdelete(mpNullTree);
          mpNullTree = new CBitPatternTree(NullColumns);

          // Bit pattern tree containing the positive columns
          CBitPatternTree PositiveTree(PositiveColumns);

          // Convert the negative columns into a bit pattern tree
          CBitPatternTree NegativeTree(NegativeColumns);

          // Iterate over all combinations and add/remove columns to the step matrix
          combine(PositiveTree.getRoot(), NegativeTree.getRoot());

          // We can now destroy all negative columns, which have already been removed from
          // the step matrix in splitColumns
          std::list< CStepMatrixColumn * >::iterator it = NegativeColumns.begin();
          std::list< CStepMatrixColumn * >::iterator end = NegativeColumns.end();

          for (; it != end; ++it)
            {
              delete *it;
            }

          // Remove columns of the step which are not extreme rays.
          removeInvalidColumns(NullColumns);

          // Now we can convert the processed row.
          mpStepMatrix->convertRow();
        }

      mProgressCounter = mProgressCounterMax - mpStepMatrix->getNumUnconvertedRows();

      if (mpCallBack)
        Continue &= mpCallBack->progress(mhProgressCounter);
    }

  buildFluxModes();

  if (mpCallBack)
    Continue &= mpCallBack->finish(mhProgressCounter);

  return true;
}

void CBitPatternTreeMethod::combine(const CBitPatternTreeNode * pPositive,
                                    const CBitPatternTreeNode * pNegative)
{
  CZeroSet Intersection = CZeroSet::intersection(pPositive->getZeroSet(),
                          pNegative->getZeroSet());

  // Adjacency test
  if (Intersection.getNumberOfSetBits() < mMinimumSetSize)
    return;

  const CStepMatrixColumn * pPositiveColumn = pPositive->getStepMatrixColumn();
  const CStepMatrixColumn * pNegativeColumn = pNegative->getStepMatrixColumn();

  // Both are leave nodes
  if (pPositiveColumn != NULL && pNegativeColumn != NULL)
    {
      // We need to check whether the existing matrix contains already a leaf which is a superset
      if (mpNullTree->isExtremeRay(Intersection))
        {
          mNewColumns.push_back(mpStepMatrix->addColumn(Intersection, pPositiveColumn, pNegativeColumn));
        }
    }
  else if (pPositiveColumn != NULL)
    {
      combine(pPositive, pNegative->getUnsetChild());
      combine(pPositive, pNegative->getSetChild());
    }
  else if (pNegativeColumn != NULL)
    {
      combine(pPositive->getUnsetChild(), pNegative);
      combine(pPositive->getSetChild(), pNegative);
    }
  else
    {
      combine(pPositive->getUnsetChild(), pNegative->getUnsetChild());
      combine(pPositive->getUnsetChild(), pNegative->getSetChild());
      combine(pPositive->getSetChild(), pNegative->getUnsetChild());
      combine(pPositive->getSetChild(), pNegative->getSetChild());
    }
}

void CBitPatternTreeMethod::removeInvalidColumns(const std::list< CStepMatrixColumn * > & nullColumns)
{
  if (mNewColumns.empty())
    {
      return;
    }

  // Convert the new columns into a bit pattern tree
  CBitPatternTree NewTree(mNewColumns);

  // Determine the columns which became invalid.
  std::vector< CStepMatrixColumn * > InvalidColumns;

  std::list< CStepMatrixColumn * >::const_iterator it = nullColumns.begin();
  std::list< CStepMatrixColumn * >::const_iterator end = nullColumns.end();

  for (; it != end; ++it)
    {
      if (!NewTree.isExtremeRay((*it)->getZeroSet()))
        {
          InvalidColumns.push_back(*it);
        }
    }

  mpStepMatrix->removeInvalidColumns(InvalidColumns);
  mNewColumns.clear();
}

void CBitPatternTreeMethod::buildKernelMatrix(CMatrix< C_INT32 > & kernelInt)
{
  // Calculate the kernel matrix
  // We apply the results of:
  //   Conservation analysis of large biochemical networks (Vallabhajosyula 2005)
  // to the transpose of the reduced stoichiometry matrix to get the kernel matrix for the:
  //   Nullspace Approach to Determine the Elementary Modes of Chemical Reaction Systems (Wagner 2004)

  CCopasiVector< CReaction >::const_iterator itReaction = mpModel->getReactions().begin();
  CCopasiVector< CReaction >::const_iterator endReaction = mpModel->getReactions().end();

  size_t ReactionCounter = 0;

  for (; itReaction != endReaction; ++itReaction, ++ReactionCounter)
    {
      if ((*itReaction)->isReversible())
        {
          // mReorderedReactions.push_back(*itReaction);
          mReactionForward.push_back(std::make_pair(ReactionCounter, false));
        }

      mReorderedReactions.push_back(*itReaction);
      mReactionForward.push_back(std::make_pair(ReactionCounter, true));
    }

  const CMatrix< C_FLOAT64 > & Stoi = mpModel->getRedStoi();

  size_t NumReactions = Stoi.numCols();

  C_INT NumExpandedReactions = mReactionForward.size();

  C_INT NumSpecies = Stoi.numRows();

  C_INT32 Dim = std::min(NumExpandedReactions, NumSpecies);

  if (Dim == 0)
    {
      return;
    }

  mExpandedStoiTranspose.resize(NumExpandedReactions, NumSpecies);

  const C_FLOAT64 *pStoi = Stoi.array();
  const C_FLOAT64 *pStoiEnd = pStoi + Stoi.size();
  const C_FLOAT64 *pStoiRowEnd;

  C_FLOAT64 *pExpandedStoiTranspose;
  C_FLOAT64 *pExpandedStoiTransposeColumn = mExpandedStoiTranspose.array();

  std::vector< const CReaction * >::const_iterator itReactionPivot;
  std::vector< const CReaction * >::const_iterator endReactionPivot;
  std::vector< std::pair< size_t, bool > >::const_iterator itReactionExpansion;

  for (; pStoi != pStoiEnd; ++pExpandedStoiTransposeColumn)
    {
      pStoiRowEnd = pStoi + NumReactions;
      pExpandedStoiTranspose = pExpandedStoiTransposeColumn;
      itReactionExpansion = mReactionForward.begin();

      for (; pStoi < pStoiRowEnd; ++pStoi, pExpandedStoiTranspose += NumSpecies, ++itReactionExpansion)
        {
          if (itReactionExpansion->second == false)
            {
              *pExpandedStoiTranspose = - *pStoi;

              // Advance the iterators
              ++itReactionExpansion;
              pExpandedStoiTranspose += NumSpecies;
            }

          *pExpandedStoiTranspose = *pStoi;
        }
    }

  CMatrix< C_FLOAT64 > ExpandedStoiTranspose = mExpandedStoiTranspose;

  C_INT LDA = std::max<C_INT>(1, NumSpecies);

  CVector< C_INT > JPVT(NumExpandedReactions);
  JPVT = 0;

  CVector< C_FLOAT64 > TAU(Dim);

  CVector< C_FLOAT64 > WORK(1);
  C_INT LWORK = -1;
  C_INT INFO;

  // QR factorization of the stoichiometry matrix
  /*
   *  -- LAPACK routine (version 3.0) --
   *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
   *     Courant Institute, Argonne National Lab, and Rice University
   *     June 30, 1999
   *
   *  Purpose
   *  =======
   *
   *  DGEQP3 computes a QR factorization with column pivoting of a
   *  matrix A:  A*P = Q*R  using Level 3 BLAS.
   *
   *  Arguments
   *  =========
   *
   *  M       (input) INTEGER
   *          The number of rows of the matrix A. M >= 0.
   *
   *  N       (input) INTEGER
   *          The number of columns of the matrix A.  N >= 0.
   *
   *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
   *          On entry, the M-by-N matrix A.
   *          On exit, the upper triangle of the array contains the
   *          min(M,N)-by-N upper trapezoidal matrix R; the elements below
   *          the diagonal, together with the array TAU, represent the
   *          orthogonal matrix Q as a product of min(M,N) elementary
   *          reflectors.
   *
   *  LDA     (input) INTEGER
   *          The leading dimension of the array A. LDA >= max(1,M).
   *
   *  JPVT    (input/output) INTEGER array, dimension (N)
   *          On entry, if JPVT(J).ne.0, the J-th column of A is permuted
   *          to the front of A*P (a leading column); if JPVT(J)=0,
   *          the J-th column of A is a free column.
   *          On exit, if JPVT(J)=K, then the J-th column of A*P was the
   *          the K-th column of A.
   *
   *  TAU     (output) DOUBLE PRECISION array, dimension (min(M,N))
   *          The scalar factors of the elementary reflectors.
   *
   *  WORK    (workspace/output) DOUBLE PRECISION array, dimension (LWORK)
   *          On exit, if INFO=0, WORK(1) returns the optimal LWORK.
   *
   *  LWORK   (input) INTEGER
   *          The dimension of the array WORK. LWORK >= 3*N+1.
   *          For optimal performance LWORK >= 2*N+(N+1)*NB, where NB
   *          is the optimal blocksize.
   *
   *          If LWORK = -1, then a workspace query is assumed; the routine
   *          only calculates the optimal size of the WORK array, returns
   *          this value as the first entry of the WORK array, and no error
   *          message related to LWORK is issued by XERBLA.
   *
   *  INFO    (output) INTEGER
   *          = 0: successful exit.
   *          < 0: if INFO = -i, the i-th argument had an illegal value.
   *
   *  Further Details
   *  ===============
   *
   *  The matrix Q is represented as a product of elementary reflectors
   *
   *     Q = H(1) H(2) . . . H(k), where k = min(m,n).
   *
   *  Each H(i) has the form
   *
   *     H(i) = I - tau * v * v'
   *
   *  where tau is a real/complex scalar, and v is a real/complex vector
   *  with v(1:i-1) = 0 and v(i) = 1; v(i+1:m) is stored on exit in
   *  A(i+1:m,i), and tau in TAU(i).
   *
   *  Based on contributions by
   *    G. Quintana-Orti, Depto. de Informatica, Universidad Jaime I, Spain
   *    X. Sun, Computer Science Dept., Duke University, USA
   *
   */

  dgeqp3_(&NumSpecies, &NumExpandedReactions, ExpandedStoiTranspose.array(), &LDA,
          JPVT.array(), TAU.array(), WORK.array(), &LWORK, &INFO);

  if (INFO < 0) fatalError();

  LWORK = (C_INT) WORK[0];
  WORK.resize(LWORK);

  dgeqp3_(&NumSpecies, &NumExpandedReactions, ExpandedStoiTranspose.array(), &LDA,
          JPVT.array(), TAU.array(), WORK.array(), &LWORK, &INFO);

  if (INFO < 0) fatalError();

  C_INT i;
  mQRPivot.resize(NumExpandedReactions);

  for (i = 0; i < NumExpandedReactions; i++)
    {
      mQRPivot[i] = JPVT[i] - 1;
    }

  /* to take care of differences between fortran's and c's memory  access,
     we need to take the transpose, i.e.,the upper triangular */
  char cL = 'U';
  char cU = 'N'; /* values in the diagonal of R */

  // Calculate Row Echelon form of R.
  // First invert R_1,1
  /* int dtrtri_(char *uplo,
   *             char *diag,
   *             integer *n,
   *             doublereal * A,
   *             integer *lda,
   *             integer *info);
   *  -- LAPACK routine (version 3.0) --
   *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
   *     Courant Institute, Argonne National Lab, and Rice University
   *     March 31, 1993
   *
   *  Purpose
   *  =======
   *
   *  DTRTRI computes the inverse of a real upper or lower triangular
   *  matrix A.
   *
   *  This is the Level 3 BLAS version of the algorithm.
   *
   *  Arguments
   *  =========
   *
   *  uplo    (input) CHARACTER*1
   *          = 'U':  A is upper triangular;
   *          = 'L':  A is lower triangular.
   *
   *  diag    (input) CHARACTER*1
   *          = 'N':  A is non-unit triangular;
   *          = 'U':  A is unit triangular.
   *
   *  n       (input) INTEGER
   *          The order of the matrix A.  n >= 0.
   *
   *  A       (input/output) DOUBLE PRECISION array, dimension (lda,n)
   *          On entry, the triangular matrix A.  If uplo = 'U', the
   *          leading n-by-n upper triangular part of the array A contains
   *          the upper triangular matrix, and the strictly lower
   *          triangular part of A is not referenced.  If uplo = 'L', the
   *          leading n-by-n lower triangular part of the array A contains
   *          the lower triangular matrix, and the strictly upper
   *          triangular part of A is not referenced.  If diag = 'U', the
   *          diagonal elements of A are also not referenced and are
   *          assumed to be 1.
   *          On exit, the (triangular) inverse of the original matrix, in
   *          the same storage format.
   *
   *  lda     (input) INTEGER
   *          The leading dimension of the array A.  lda >= max(1,n).
   *
   *  info    (output) INTEGER
   *          = 0: successful exit
   *          < 0: if info = -i, the i-th argument had an illegal value
   *          > 0: if info = i, A(i,i) is exactly zero.  The triangular
   *               matrix is singular and its inverse can not be computed.
   */
  dtrtri_(&cL, &cU, &NumSpecies, ExpandedStoiTranspose.array(), &LDA, &INFO);

  if (INFO < 0) fatalError();

  kernelInt.resize(NumExpandedReactions, NumExpandedReactions - NumSpecies);

  CMatrix< C_FLOAT64 > KernelDbl(NumExpandedReactions, NumExpandedReactions - NumSpecies);
  KernelDbl = 0;

  // Null space matrix identity part
  for (i = 0; i < NumExpandedReactions - NumSpecies; i++)
    {
      KernelDbl(NumSpecies + i, i) = 1.0;
    }

  C_INT j, k;
  C_FLOAT64 * pKernelDbl = KernelDbl.array();
  C_FLOAT64 * pDiagonal = ExpandedStoiTranspose.array();
  C_FLOAT64 * pInverse;
  C_FLOAT64 * pR12;

  for (i = 0; i < NumSpecies; ++i, pDiagonal += NumSpecies + 1)
    {
      for (j = NumSpecies; j < NumExpandedReactions; ++j, ++pKernelDbl)
        {
          pInverse = pDiagonal;
          pR12 = & ExpandedStoiTranspose(j, i);

          for (k = i; k < NumSpecies; ++k, pR12++, pInverse += NumSpecies)
            {
              // *pKernel -= ExpandedStoiTranspose(k, i) * ExpandedStoiTranspose(j, k);
              *pKernelDbl -= *pInverse * *pR12;
            }

          if (fabs(*pKernelDbl) < 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              *pKernelDbl = 0.0;
            }
        }
    }

  CVectorCore<C_FLOAT64> KernelValues(KernelDbl.size(), KernelDbl.array());
  convertToIntegers(KernelValues);

  pKernelDbl = KernelDbl.array();
  C_FLOAT64 * pKernelDblEnd = pKernelDbl + KernelDbl.size();

  C_INT32 * pKernelInt = kernelInt.array();

  for (; pKernelDbl != pKernelDblEnd; ++pKernelDbl, ++pKernelInt)
    {
      *pKernelInt = (C_INT32) floor(*pKernelDbl + .05);
    }

  return;
}

void CBitPatternTreeMethod::buildFluxModes()
{
  CStepMatrix::const_iterator it = mpStepMatrix->begin();
  CStepMatrix::const_iterator end = mpStepMatrix->end();

  CVector< size_t > Indexes;
  C_INT NumSpecies = mExpandedStoiTranspose.numCols();

  for (; it != end; ++it)
    {
      getUnsetBitIndexes(*it, Indexes);

      C_INT NumReactions = Indexes.size();

      // Remove trivial modes, i.e., reversible reactions
      if (NumReactions == 2 &&
          mReorderedReactions[mReactionForward[Indexes[0]].first] == mReorderedReactions[mReactionForward[Indexes[1]].first])
        {
          continue;
        }

      // Build the stoichiometry matrix reduced to the reactions participating in the current mode.
      CMatrix< C_FLOAT64 > A(NumReactions, NumSpecies);
      CVector< C_FLOAT64 > B(NumSpecies);

      size_t * pIndex = Indexes.array();
      size_t * pIndexEnd = pIndex + NumReactions;
      C_FLOAT64 * pARow = A.array();

      for (; pIndex != pIndexEnd; ++pIndex, pARow += NumSpecies)
        {
          memcpy(pARow, &mExpandedStoiTranspose(*pIndex, 0), NumSpecies * sizeof(C_FLOAT64));
        }

      C_INT LDA = std::max<C_INT>(1, NumSpecies);

      CVector< C_INT > JPVT(NumReactions);
      JPVT = 0;

      C_INT32 Dim = std::min(NumReactions, NumSpecies);

      CVector< C_FLOAT64 > TAU(Dim);

      CVector< C_FLOAT64 > WORK(1);
      C_INT LWORK = -1;
      C_INT INFO;

      dgeqp3_(&NumSpecies, &NumReactions, A.array(), &LDA,
              JPVT.array(), TAU.array(), WORK.array(), &LWORK, &INFO);

      if (INFO < 0) fatalError();

      LWORK = (C_INT) WORK[0];
      WORK.resize(LWORK);

      dgeqp3_(&NumSpecies, &NumReactions, A.array(), &LDA,
              JPVT.array(), TAU.array(), WORK.array(), &LWORK, &INFO);

      if (INFO < 0) fatalError();

      /* to take care of differences between fortran's and c's memory  access,
         we need to take the transpose, i.e.,the upper triangular */
      char cL = 'U';
      char cU = 'N'; /* values in the diagonal of R */

      C_INT DimInverse = std::min(NumSpecies, NumReactions - 1);

      dtrtri_(&cL, &cU, &DimInverse, A.array(), &LDA, &INFO);

      if (INFO < 0) fatalError();

      assert(NumReactions - DimInverse == 1);

      CVector< C_FLOAT64 > FluxMultiplierQR(DimInverse + 1);
      FluxMultiplierQR = 0;

      C_INT i, j, k;
      C_FLOAT64 * pFluxMultiplier = FluxMultiplierQR.array();
      C_FLOAT64 * pDiagonal = A.array();
      C_FLOAT64 * pInverse;
      C_FLOAT64 * pR12;

      for (i = 0; i < DimInverse; ++i, pDiagonal += NumSpecies + 1)
        {
          for (j = DimInverse; j < NumReactions; ++j, ++pFluxMultiplier)
            {
              pInverse = pDiagonal;
              pR12 = & A(j, i);

              for (k = i; k < DimInverse; ++k, pR12++, pInverse += NumSpecies)
                {
                  // *pCore -= A(k, i) * A(j, k);
                  *pFluxMultiplier -= *pInverse * *pR12;
                }

              if (fabs(*pFluxMultiplier) < 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
                {
                  *pFluxMultiplier = 0.0;
                }
            }
        }

      *pFluxMultiplier = 1.0;

      convertToIntegers(FluxMultiplierQR);

      // We need to apply the pivot of the QR factorization to the multipliers
      CVector< C_FLOAT64 > FluxMultiplier(DimInverse + 1);

      for (i = 0; i < DimInverse + 1; i++)
        {
          FluxMultiplier[JPVT[i] - 1] = FluxMultiplierQR[i];
        }

      // Now we create the flux mode as we have the multiplier and reaction indexes.
      // We need to invert the sign of the multiplier for reactions which are not forward.
      // A flux mode is reversible if all reactions are reversible;

      std::map< size_t, C_FLOAT64 > Reactions;

      bool Reversible = true;

      pIndex = Indexes.array();
      pFluxMultiplier = FluxMultiplier.array();

      for (; pIndex != pIndexEnd; ++pIndex, ++pFluxMultiplier)
        {
          std::pair< size_t, bool > & ReactionForward = mReactionForward[*pIndex];

          Reactions[ReactionForward.first] =
            (ReactionForward.second == true) ? *pFluxMultiplier : -*pFluxMultiplier;

          if (!mReorderedReactions[ReactionForward.first]->isReversible())
            {
              Reversible = false;
            }
        }

      addMode(CFluxMode(Reactions, Reversible));
    }
}

void CBitPatternTreeMethod::convertToIntegers(CVectorCore< C_FLOAT64 > & values)
{
  static const C_FLOAT64 limit = 10.0 / std::numeric_limits< C_INT32 >::max();

  size_t Size = values.size();

  unsigned C_INT32 m00, m01, m10, m11;
  unsigned C_INT32 maxden = 10000000;
  unsigned C_INT32 Multiplier = 1;
  unsigned C_INT32 GCD1, GCD2;
  unsigned C_INT32 ai;

  C_FLOAT64 * pValue = values.array();
  C_FLOAT64 * pValueEnd = pValue + Size;
  C_FLOAT64 x;

  for (; pValue != pValueEnd; ++pValue)
    {
      x = fabs(*pValue);

      if (x < 100 * std::numeric_limits< C_FLOAT64 >::epsilon())
        {
          continue;
        }

      /*
       * Find rational approximation to given real number
       * David Eppstein / UC Irvine / 8 Aug 1993
       *
       * With corrections from:
       *   Arno Formella, May 2008
       *   Stefan Hoops, Sept 2009
       *
       * Based on the theory of continued fractions
       * if x = a1 + 1/(a2 + 1/(a3 + 1/(a4 + ...)))
       * then best approximation is found by truncating this series
       * (with some adjustments in the last term).
       *
       * Note the fraction can be recovered as the first column of the matrix
       *  (a1 1 ) (a2 1 ) (a3 1 ) ...
       *  (1  0 ) (1  0 ) (1  0)
       * Instead of keeping the sequence of continued fraction terms,
       * we just keep the last partial product of these matrices.
       */

      /* initialize matrix */
      m00 = m11 = 1;
      m01 = m10 = 0;

      /* loop finding terms until denom gets too big */
      while (m10 *(ai = (unsigned C_INT32) x) + m11 <= maxden)
        {
          C_INT32 t;
          t = m00 * ai + m01;
          m01 = m00;
          m00 = t;

          t = m10 * ai + m11;
          m11 = m10;
          m10 = t;

          if (fabs(x - (C_FLOAT64) ai) < limit)
            break;     // SH: We reached the numerical precision of the machine;

          x = 1 / (x - (C_FLOAT64) ai);
        }

      if (fabs(fabs(*pValue) - ((C_FLOAT64) m00) / ((C_FLOAT64) m10)) > 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
        {
          ai = (maxden - m11) / m10;
          m00 = m00 * ai + m01;
          m10 = m10 * ai + m11;
        }

      // Find the greatest common divisor (GCD) of the multiplier and the current denominator.
      // Euclidean algorithm
      GCD1 = m10;
      GCD2 = Multiplier;

      while (GCD1 != GCD2)
        {
          if (GCD1 > GCD2)
            {
              GCD1 -= GCD2;
            }
          else
            {
              GCD2 -= GCD1;
            }
        }

      // Calculate the least common multiplier: LCM = v1 * v2 / GCD(v1, v2)
      Multiplier *= m10 / GCD1;
    }

  pValue = values.array();

  for (; pValue != pValueEnd; ++pValue)
    {
      *pValue *= Multiplier;
    }
}

void CBitPatternTreeMethod::getUnsetBitIndexes(const CStepMatrixColumn * pColumn,
    CVector< size_t > & indexes) const
{
  mpStepMatrix->getUnsetBitIndexes(pColumn, indexes);

  // Apply the QR pivot
  size_t * pIndex = indexes.array();
  size_t * pIndexEnd = pIndex + indexes.size();

  for (; pIndex != pIndexEnd; ++pIndex)
    {
      *pIndex = mQRPivot[*pIndex];
    }
}

// private
void CBitPatternTreeMethod::addMode(const CFluxMode & mode)
{
  std::vector< CFluxMode >::iterator itMode = mFluxModes.begin();
  std::vector< CFluxMode >::iterator endMode = mFluxModes.end();

  for (; itMode != endMode; ++itMode)
    {
      if (itMode->isReversed(mode))
        {
          return;
        }
    }

  mFluxModes.push_back(mode);
  return;
}
