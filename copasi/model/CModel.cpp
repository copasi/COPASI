/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModel.cpp,v $
   $Revision: 1.287 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/06 17:41:48 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifdef SunOS
# include <ieeefp.h>
#else
# include <float.h>
#endif

#include "copasi.h"

#include <string>
#include <vector>
#include <limits.h>
#include <float.h>
#include <cmath>
#include <algorithm>

// #define DEBUG_MATRIX

#include "CCompartment.h"
#include "CMetab.h"
#include "CModel.h"
#include "CState.h"
#include "CModelValue.h"
#include "function/CFunctionDB.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiException.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CVector.h"
#include "utilities/CluX.h"
#include "utilities/utility.h"
#include "utilities/CProcessReport.h"
#include "CReactionInterface.h"
#include "utilities/CAnnotatedMatrix.h"

#include "blaswrap.h"
#include "clapackwrap.h"

#ifdef COPASI_DEBUG
#define CCHECK {check();}
#else
#define CCHECK
#endif

const char * CModel::VolumeUnitNames[] =
  {"m\xc2\xb3", "l", "ml", "\xc2\xb5l", "nl", "pl", "fl", NULL};

const char * CModel::TimeUnitNames[] =
  {"d", "h", "min", "s", "ms", "\xc2\xb5s", "ns", "ps", "fs", NULL};

const char * CModel::QuantityUnitNames[] =
  {"Mol", "mMol", "\xc2\xb5Mol", "nMol", "pMol", "fMol", "#", NULL};

const char * CModel::ModelTypeNames[] =
  {"deterministic", "stochastic", NULL};

CModel::CModel():
    CModelEntity("New Model", &RootContainer, "Model"),
    mInitialState(),
    mCurrentState(),
    mStateTemplate(*this, this->mInitialState, this->mCurrentState),
    mComments(),
    mVolumeUnit(ml),
    mTimeUnit(s),
    mQuantityUnit(mMol),
    mType(deterministic),
    mCompartments("Compartments", this),
    mMetabolites("Metabolites", this),
    mMetabolitesX("Reduced Model Metabolites", this),
    mSteps("Reactions", this),
    mParticleFluxes(),
    mValues("Values", this),
    mTransitionTime(0.0),
    mMoieties("Moieties", this),
    mStoi(),
    mStoiReordered(),
    mRedStoi(),
    mNumMetabolitesUnused(0),
    mNumMetabolitesODE(0),
    mNumMetabolitesReaction(0),
    mNumMetabolitesAssignment(0),
    mNumMetabolitesIndependent(0),
    mL(),
    mLView(mL, mNumMetabolitesIndependent),
    mQuantity2NumberFactor(1.0),
    mNumber2QuantityFactor(1.0),
    mpCompileHandler(NULL)
{
  initObjects();

  setStatus(TIME);

  *mpIValue = 0.0;
  *mpValueAccess = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  unsigned C_INT32 i, imax = mSteps.size();

  for (i = 0; i < imax; i++)
    mSteps[i]->compile(/*mCompartments*/);

  initializeMetabolites();

  forceCompile();

  /* This following 2 lines added by Liang Xu
  Becaues of the failure to initialize the parameter when creating a new models
  */
  setQuantityUnit(mQuantityUnit); // set the factors
  setVolumeUnit(mVolumeUnit); // set the factors

  CONSTRUCTOR_TRACE;
}

CModel::CModel(const CModel & src):
    CModelEntity(src),
    mInitialState(),
    mCurrentState(),
    mStateTemplate(*this, this->mInitialState, this->mCurrentState),
    mComments(src.mComments),
    mVolumeUnit(src.mVolumeUnit),
    mTimeUnit(src.mTimeUnit),
    mQuantityUnit(src.mQuantityUnit),
    mType(src.mType),
    mCompartments(src.mCompartments, this),
    mMetabolites(src.mMetabolites, this),
    mMetabolitesX(src.mMetabolitesX, this),
    mSteps(src.mSteps, this),
    mParticleFluxes(src.mParticleFluxes),
    mValues(src.mValues, this),
    mTransitionTime(src.mTransitionTime),
    mMoieties(src.mMoieties, this),
    mStoi(src.mStoi),
    mStoiReordered(src.mStoiReordered),
    mRedStoi(src.mRedStoi),
    mNumMetabolitesUnused(src.mNumMetabolitesUnused),
    mNumMetabolitesODE(src.mNumMetabolitesODE),
    mNumMetabolitesReaction(src.mNumMetabolitesReaction),
    mNumMetabolitesAssignment(src.mNumMetabolitesAssignment),
    mNumMetabolitesIndependent(src.mNumMetabolitesIndependent),
    mL(src.mL),
    mLView(mL, mNumMetabolitesIndependent),
    mQuantity2NumberFactor(src.mQuantity2NumberFactor),
    mNumber2QuantityFactor(src.mNumber2QuantityFactor),
    mpCompileHandler(NULL)
{
  CONSTRUCTOR_TRACE;
  initObjects();

  unsigned C_INT32 i, imax = mSteps.size();

  for (i = 0; i < imax; i++)
    mSteps[i]->compile(/*mCompartments*/);

  initializeMetabolites();

  forceCompile();
}

CModel::~CModel()
{
  mpIValue = NULL;
  mpValueData = NULL;

  GlobalKeys.remove(mKey);
  //cleanup();
  DESTRUCTOR_TRACE;
}

void CModel::cleanup()
{
  /* The real objects */
  mCompartments.cleanup();
  mSteps.cleanup();
  mMoieties.cleanup();

  /* The references */
  //mStepsInd.resize(0);
  mMetabolites.resize(0);
  mMetabolitesX.resize(0);
  mParticleFluxes.resize(0);
}

C_INT32 CModel::load(CReadConfig & configBuffer)
{
  C_INT32 Size = 0;
  C_INT32 Fail = 0;
  unsigned C_INT32 i;
  std::string tmp;

  // For old Versions we must read the list of Metabolites beforehand
  if ((Fail = configBuffer.getVariable("TotalMetabolites", "C_INT32",
                                       &Size, CReadConfig::LOOP)))
    return Fail;

  // :TODO: Remove OldMetabolites as part of the data model.
  CCopasiDataModel::Global->pOldMetabolites->load(configBuffer, Size);

  if ((Fail = configBuffer.getVariable("Title", "string", &tmp,
                                       CReadConfig::LOOP)))
    return Fail;
  setObjectName(tmp);

  try
    {
      Fail = configBuffer.getVariable("Comments", "multiline", &mComments,
                                      CReadConfig::SEARCH);
    }

  catch (CCopasiException Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
        mComments = "";
      else
        throw Exception;
    }

  try
    {
      Fail = configBuffer.getVariable("TimeUnit", "string", &tmp,
                                      CReadConfig::LOOP);
    }
  catch (CCopasiException Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
        tmp = ""; //unknown?
      else
        throw Exception;
    }

  setTimeUnit(tmp); // set the factors

  try
    {
      Fail = configBuffer.getVariable("ConcentrationUnit", "string", &tmp,
                                      CReadConfig::LOOP);
    }
  catch (CCopasiException Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
        tmp = "";  //unknown?
      else
        throw Exception;
    }

  setQuantityUnit(tmp); // set the factors

  try
    {
      Fail = configBuffer.getVariable("VolumeUnit", "string", &tmp,
                                      CReadConfig::LOOP);
    }
  catch (CCopasiException Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
        tmp = ""; //unknown?
      else
        throw Exception;
    }

  setVolumeUnit(tmp); // set the factors

  *mpIValue = 0;

  if ((Fail = configBuffer.getVariable("TotalCompartments", "C_INT32", &Size,
                                       CReadConfig::LOOP)))
    return Fail;

  mCompartments.load(configBuffer, Size);

  // Create the correct compartment / metabolite relationships
  CMetab *pMetabolite;

  for (i = 0; i < CCopasiDataModel::Global->pOldMetabolites->size(); i++)
    {
      pMetabolite = new CMetab;
      mCompartments[(*CCopasiDataModel::Global->pOldMetabolites)[i]->getIndex()]->
      addMetabolite(pMetabolite);

      (*pMetabolite) = *(*CCopasiDataModel::Global->pOldMetabolites)[i];
    }

  //DebugFile << mCompartments;       //debug

  initializeMetabolites();

  if ((Fail = CCopasiDataModel::Global->getFunctionList()->load(configBuffer))) // slow
    return Fail;

  if ((Fail = configBuffer.getVariable("TotalSteps", "C_INT32", &Size,
                                       CReadConfig::LOOP)))
    return Fail;

  mSteps.load(configBuffer, Size); // slow

  // DebugFile << std::endl << mSteps << std::endl;  //debug

  for (i = 0; i < mSteps.size(); i++)
    mSteps[i]->compile(/*mCompartments*/);

  // DebugFile << "After compiling " << std::endl << mSteps << std::endl;   //debug

  CCopasiDataModel::Global->pOldMetabolites->cleanup();

  setCompileFlag();
  return Fail;
}

bool CModel::compile()
{
  CMatrix< C_FLOAT64 > LU;

  unsigned C_INT32 CompileStep = 0;
  unsigned C_INT32 hCompileStep;
  if (mpCompileHandler)
    {
      mpCompileHandler->setName("Compiling model...");
      unsigned C_INT32 totalSteps = 7;
      hCompileStep = mpCompileHandler->addItem("Step",
                     CCopasiParameter::UINT,
                     & CompileStep,
                     &totalSteps);
    }

  CompileStep = 0;
  if (mpCompileHandler && !mpCompileHandler->progress(hCompileStep)) return false;

  buildStoi();
  CompileStep = 1;
  if (mpCompileHandler && !mpCompileHandler->progress(hCompileStep)) return false;

  buildLinkZero();
  CompileStep = 2;
  if (mpCompileHandler && !mpCompileHandler->progress(hCompileStep)) return false;

  buildRedStoi();
  CompileStep = 3;
  if (mpCompileHandler && !mpCompileHandler->progress(hCompileStep)) return false;

  buildMoieties();
  CompileStep = 4;
  if (mpCompileHandler && !mpCompileHandler->progress(hCompileStep)) return false;

  buildStateTemplate();
  CompileStep = 5;
  if (mpCompileHandler && !mpCompileHandler->progress(hCompileStep)) return false;

  buildConstantSequence();
  buildApplySequence();
  CompileStep = 6;
  if (mpCompileHandler && !mpCompileHandler->progress(hCompileStep)) return false;

  buildUserOrder();
  if (mpCompileHandler) mpCompileHandler->finish(hCompileStep);

  mCompileIsNecessary = false;
  return true;
}

void CModel::setCompileFlag(bool flag)
{
  mCompileIsNecessary = flag;
  //if (flag) std::cout << "* model dirty flag set. " << std::endl;

  // We need to move this and do not do this automatically
  // if (flag) initializeMetabolites();
}

bool CModel::compileIfNecessary()
{
  /*
  std::cout << "** compiling a CModel is requested. ";
  if (mCompileIsNecessary)
    std::cout << "It will be done...." << std::endl;
  else
    std::cout << " " << std::endl;
  */

  if (mCompileIsNecessary)
    return compile();
  return true;
}

bool CModel::forceCompile()
{
  setCompileFlag();
  return compileIfNecessary();
}

void CModel::buildStoi()
{
  unsigned C_INT32 i;

  initializeMetabolites();

  unsigned C_INT32 numRows, numCols;
  numRows = mNumMetabolitesReaction;
  numCols = mSteps.size();

  mParticleFluxes.resize(numCols);
  mStoi.resize(numRows, numCols);
  mStoi = 0.0;

  unsigned C_INT32 hProcess;
  if (mpCompileHandler)
    {
      i = 0;
      hProcess = mpCompileHandler->addItem("Building Stoichiometry",
                                           CCopasiParameter::UINT,
                                           &i,
                                           &numCols);
    }

  C_FLOAT64 * pCol, *pColEnd;
  pCol = mStoi.array();
  pColEnd = mStoi.array() + numCols;

  C_FLOAT64 * pRow, *pRowEnd;
  pRowEnd = mStoi.array() + numRows * numCols;

  CCopasiVector< CReaction >::iterator itStep = mSteps.begin();
  CCopasiVector< CMetab >::const_iterator itMetab;

  for (; pCol < pColEnd; ++pCol, ++itStep, ++i)
    {
      if (mpCompileHandler && !mpCompileHandler->progress(hProcess)) return;

      const CCopasiVector< CChemEqElement > & Balance =
        (*itStep)->getChemEq().getBalances();
      CCopasiVector< CChemEqElement >::const_iterator itBalance = Balance.begin();
      CCopasiVector< CChemEqElement >::const_iterator endBalance = Balance.end();

      for (; itBalance != endBalance; ++itBalance)
        {
          const std::string & key = (*itBalance)->getMetaboliteKey();

          for (pRow = pCol, itMetab = mMetabolitesX.begin() + mNumMetabolitesODE; pRow < pRowEnd; pRow += numCols, ++itMetab)
            if ((*itMetab)->getKey() == key)
              {
                *pRow = (*itBalance)->getMultiplicity();
                break;
              }
        }
    }

  // We need to have all unused and fixed metabolites at the end of mMetabolites.
  // However we can only detect unused metabolites after building the
  // stoichiometry matrix.
  handleUnusedMetabolites();

#ifdef DEBUG_MATRIX
  DebugFile << "Stoichiometry Matrix" << std::endl;
  DebugFile << mStoi << std::endl;
#endif

  if (mpCompileHandler)
    mpCompileHandler->finish(hProcess);

  return;
}

bool CModel::handleUnusedMetabolites()
{
  unsigned C_INT32 numRows, numCols;
  numRows = mStoi.numRows();
  numCols = mStoi.numCols();

  C_FLOAT64 * pStoi, *pStoiEnd, *pRowEnd;
  pStoi = mStoi.array();
  pStoiEnd = mStoi.array() + numRows * numCols;

  unsigned C_INT32 i, NumUnused;
  C_FLOAT64 tmp;
  std::vector< unsigned C_INT32 > Unused;

  for (i = 0; pStoi < pStoiEnd; i++)
    {
      tmp = 0;

      for (pRowEnd = pStoi + numCols; pStoi < pRowEnd; ++pStoi)
        tmp += fabs(*pStoi);

      if (tmp < DBL_MIN) Unused.push_back(i);
    }

  NumUnused = Unused.size();
  if (NumUnused == 0) return false;

  // We treat unused variables in the same way as fixed, i.e.
  // they will be sorted to the end of the metabolite list.

  numRows -= NumUnused;

  CMatrix< C_FLOAT64 > NewStoi(numRows, numCols);
  C_FLOAT64 * pNewStoi = NewStoi.array();
  std::vector< CMetab * > UsedMetabolites(numRows);
  std::vector< CMetab * >::iterator itUsedMetabolites = UsedMetabolites.begin();
  std::vector< CMetab * > UnusedMetabolites(NumUnused);
  std::vector< CMetab * >::iterator itUnusedMetabolites = UnusedMetabolites.begin();
  std::vector< unsigned C_INT32 >::const_iterator itUnused = Unused.begin();
  std::vector< unsigned C_INT32 >::const_iterator endUnused = Unused.end();
  CMetab * pMetab;
  CCopasiVector< CMetab >::iterator itMetab = mMetabolitesX.begin() + mNumMetabolitesODE;
  CCopasiVector< CMetab >::iterator endMetab = itMetab + mNumMetabolitesReaction;

  // Build new stoichiometry Matrix
  pStoi = mStoi.array();
  for (i = 0; itMetab != endMetab; ++itMetab, i++, pStoi += numCols)
    {
      if (itUnused != endUnused && i == *itUnused)
        {
          (*itMetab)->setUsed(false);
          *itUnusedMetabolites = (*itMetab);

          ++itUnusedMetabolites;
          ++itUnused;
        }
      else
        {
          (*itMetab)->setUsed(true);
          *itUsedMetabolites = (*itMetab);
          ++itUsedMetabolites;

          // The row needs to be copied to the new stoichiometry matrix
          memcpy(pNewStoi, pStoi, sizeof(C_FLOAT64) * numCols);
          pNewStoi += numCols;
        }
    }

  // Reorder metabolites
  // Skip the metabolites determined by ODE
  itMetab = mMetabolitesX.begin() + mNumMetabolitesODE;

  // Handle the metabolites determined by actually determined by reactions
  itUsedMetabolites = UsedMetabolites.begin();
  std::vector< CMetab * >::iterator itMetabolitesEnd = UsedMetabolites.end();
  for (; itUsedMetabolites != itMetabolitesEnd; ++itUsedMetabolites, ++itMetab)
    *itMetab = *itUsedMetabolites;

  // Handle metabolites determined by assignement and marked as fixed
  // This is just a shift of NumUnused.
  endMetab = itMetab + mNumMetabolitesAssignment + mNumMetabolitesUnused;
  mNumMetabolitesUnused += NumUnused;
  for (; itMetab != endMetab; ++itMetab)
    *itMetab = *(itMetab + NumUnused);

  // Handle newly marked unused metabolites
  itUnusedMetabolites = UnusedMetabolites.begin();
  itMetabolitesEnd = UnusedMetabolites.end();
  for (; itUnusedMetabolites != itMetabolitesEnd; ++itUnusedMetabolites, ++itMetab)
    *itMetab = *itUnusedMetabolites;

  // Now its time to update the number of metabolites determined by reactions
  // and the one being unused.
  mNumMetabolitesReaction -= NumUnused;
  mNumMetabolitesUnused += NumUnused;

  // Update stoichiometry matrix
  mStoi = NewStoi;

  return true;
}

void CModel::buildRedStoi()
{
  C_INT32 i;
  C_INT32 numCols = mStoi.numCols();

  mRedStoi.resize(mNumMetabolitesIndependent, numCols);
  mStoiReordered.resize(mStoi.numRows(), numCols);

  C_FLOAT64 * pStoi = mStoi.array();
  C_FLOAT64 * pRedStoi = mRedStoi.array();
  C_FLOAT64 * pStoiReordered = mStoiReordered.array();
  unsigned C_INT32 * pRow = mRowLU.array();

  // Create a temporary copy of the metabolites determined by reactions to reorder them
  // accordingly.
  CCopasiVector< CMetab >::iterator itMetabX = mMetabolitesX.begin() + mNumMetabolitesODE;
  CCopasiVector< CMetab >::iterator endMetabX = itMetabX + mNumMetabolitesReaction;
  std::vector< CMetab * > MetabolitesReaction;
  MetabolitesReaction.resize(mNumMetabolitesReaction);
  std::vector< CMetab * >::iterator itMetabolitesReaction = MetabolitesReaction.begin();

  for (; itMetabX != endMetabX; ++itMetabX, ++itMetabolitesReaction)
    *itMetabolitesReaction = *itMetabX;

  /* just have to swap rows */
  itMetabX = mMetabolitesX.begin() + mNumMetabolitesODE;
  for (i = 0; i < mNumMetabolitesIndependent; i++, pRow++, pRedStoi += numCols, pStoiReordered += numCols, itMetabX++)
    {
      memcpy(pRedStoi, mStoi[*pRow], sizeof(C_FLOAT64) * numCols);
      memcpy(pStoiReordered, mStoi[*pRow], sizeof(C_FLOAT64) * numCols);
      *itMetabX = MetabolitesReaction[*pRow];
    }

  for (; i < mNumMetabolitesReaction; i++, pRow++, pStoiReordered += numCols, itMetabX++)
    {
      memcpy(pStoiReordered, mStoi[*pRow], sizeof(C_FLOAT64) * numCols);
      *itMetabX = MetabolitesReaction[*pRow];
    }

#ifdef DEBUG_MATRIX
  DebugFile << "Reduced Stoichiometry Matrix" << std::endl;
  DebugFile << mRedStoi << std::endl;
#endif

  return;
}

void CModel::buildL(const CMatrix< C_FLOAT64 > & LU)
{
  C_INT N = mNumMetabolitesIndependent;
  C_INT LDA = std::max((C_INT) 1, N);
  C_INT Info;

  unsigned C_INT32 i, imin, imax;
  unsigned C_INT32 j, jmax;
  unsigned C_INT32 k;
  C_FLOAT64 * sum;

  CMatrix< C_FLOAT64 > R(N, N);

  for (i = 1; i < (unsigned C_INT32) N; i++)
    for (j = 0; j < i; j++)
      R(i, j) = LU(i, j);

#ifdef DEBUG_MATRIX
  DebugFile << "L" << std::endl;
  DebugFile << R << std::endl;
#endif

  /* to take care of differences between fortran's and c's memory  acces,
     we need to take the transpose, i.e.,the upper triangular */
  char cL = 'U';
  char cU = 'U'; /* 1 in the diaogonal of R */

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
  dtrtri_(&cL, &cU, &N, R.array(), &LDA, &Info);
  if (Info) fatalError();

#ifdef DEBUG_MATRIX
  DebugFile << "L inverse" << std::endl;
  DebugFile << R << std::endl;
#endif

  mL.resize(mNumMetabolitesReaction - mNumMetabolitesIndependent, mNumMetabolitesIndependent);

  imin = mNumMetabolitesIndependent, imax = getNumVariableMetabs();
  jmax = mNumMetabolitesIndependent;

  // Construct L_0
  for (i = imin; i < imax; i++)
    for (j = 0; j < jmax; j++)
      {
        sum = & mL(i - imin, j);
        *sum = LU(i, j);

        for (k = j + 1; k < jmax; k++)
          *sum += LU(i, k) * R(k, j);

        if (fabs(*sum) < DBL_EPSILON) *sum = 0.0;
      }

#ifdef DEBUG_MATRIX
  DebugFile << "Link Matrix:" << std::endl;
  DebugFile << mLView << std::endl;
#endif // DEBUG_MATRIX
}

void CModel::updateMoietyValues()
{
  CCopasiVector< CMoiety >::iterator it = mMoieties.begin();
  CCopasiVector< CMoiety >::iterator end = mMoieties.end();
  for (; it != end; ++it)
    (*it)->setInitialValue();
}

void CModel::buildMoieties()
{
  unsigned C_INT32 i, imax = mNumMetabolitesReaction - mNumMetabolitesIndependent;
  unsigned C_INT32 j;

  CCopasiVector< CMetab >::iterator it =
    mMetabolitesX.begin() + mNumMetabolitesODE + mNumMetabolitesIndependent;
  C_FLOAT64 * pFactor = mL.array();

  CMoiety *pMoiety;

  mMoieties.cleanup();

  for (i = 0; i < imax; i++, ++it)
    {
      pMoiety = new CMoiety;
      pMoiety->setObjectName((*it)->getObjectName());
      pMoiety->add(1.0, *it);

      for (j = 0; j < mNumMetabolitesIndependent; j++, pFactor++)
        if (fabs(*pFactor) > DBL_EPSILON)
          pMoiety->add(- *pFactor, mMetabolitesX[j + mNumMetabolitesODE]);

      mMoieties.add(pMoiety, true);
    }

  updateMoietyValues();
  return;
}

#ifdef WIN32
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

void CModel::setTransitionTimes()
{
  unsigned C_INT32 i, imax = mMetabolites.size();
  unsigned C_INT32 j, jmax = mSteps.size();

  // Since some metabolites are unused we need to keep track of
  // the row of the stoichiometry matrix intependently.
  unsigned C_INT32 k;

  C_FLOAT64 TotalFlux_p, TotalFlux_n, min_flux, PartialFlux;
  C_FLOAT64 TransitionTime;

  mTransitionTime = 0.0;

  for (i = 0, k = 0; i < imax; i++)
    {
      if (mMetabolites[i]->isFixed() ||
          !mMetabolites[i]->isUsed())
        {
          mMetabolites[i]->setTransitionTime(2 * DBL_MAX);
        }
      else
        {
          TotalFlux_p = 0.0;
          TotalFlux_n = 0.0;

          for (j = 0; j < jmax; j++)
            {
              PartialFlux = mStoi(k, j) * mParticleFluxes[j];

              if (PartialFlux > 0.0)
                TotalFlux_p += PartialFlux;
              else
                TotalFlux_n -= PartialFlux;
            }

          k++; // The next row in the stoichiometry matrix;

          if (TotalFlux_p < TotalFlux_n)
            min_flux = TotalFlux_p;
          else
            min_flux = TotalFlux_n;

          if (min_flux == 0.0)
            TransitionTime = 2 * DBL_MAX;
          else
            TransitionTime = mMetabolites[i]->getValue() / min_flux;

          mMetabolites[i]->setTransitionTime(TransitionTime);
          //mMetabolites[i]->setNumberRate(TotalFlux);

          if (!finite(TransitionTime))
            mTransitionTime = TransitionTime;
          else
            mTransitionTime += TransitionTime;
        }
    }
}

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif

//this is supposed to be so fast it can be called often to be kept up to date
//all the time. At the moment it creates the mMetabolites and sorts the fixed
//metabs to the end
void CModel::initializeMetabolites()
{
  // Create a vector of pointers to all metabolites.
  // Note, the metabolites physically exist in the compartments.
  mMetabolites.resize(0);

  CCopasiVector< CCompartment >::iterator itCompartment = mCompartments.begin();
  CCopasiVector< CCompartment >::iterator endCompartment = mCompartments.end();
  CCopasiVector< CMetab >::iterator itMetab;
  CCopasiVector< CMetab >::iterator endMetab;

  for (; itCompartment != endCompartment; ++itCompartment)
    {
      itMetab = (*itCompartment)->getMetabolites().begin();
      endMetab = (*itCompartment)->getMetabolites().end();

      for (; itMetab != endMetab; ++itMetab)
        {
          (*itMetab)->clearMoieties();
          (*itMetab)->setUsed(!(*itMetab)->isFixed());

          mMetabolites.add(*itMetab);
        }
    }

  // We sort the metabolites by type
  itMetab = mMetabolites.begin();
  endMetab = mMetabolites.end();

  std::vector< CMetab *> ODEMetabs;
  std::vector< CMetab *> ReactionMetabs;
  std::vector< CMetab *> AssignmentMetabs;
  std::vector< CMetab *> FixedMetabs;

  for (; itMetab != endMetab; ++itMetab)
    switch ((*itMetab)->getStatus())
      {
      case CModelEntity::FIXED:
        FixedMetabs.push_back(*itMetab);
        (*itMetab)->setUsed(false);
        break;

      case CModelEntity::ASSIGNMENT:
        AssignmentMetabs.push_back(*itMetab);
        (*itMetab)->setUsed(true);
        break;

      case CModelEntity::ODE:
        ODEMetabs.push_back(*itMetab);
        (*itMetab)->setUsed(true);
        break;

      case CModelEntity::REACTIONS:
        ReactionMetabs.push_back(*itMetab);
        (*itMetab)->setUsed(true);
        break;

      default:
        fatalError();
      }

  // Update mMetabolitesX to reflect the reordering.
  // We need to to this to allow the use of the full model for simulation.
  mMetabolitesX.resize(mMetabolites.size(), false);

  mNumMetabolitesODE = ODEMetabs.size();
  itMetab = mMetabolitesX.begin();
  std::vector< CMetab *>::const_iterator itSorted = ODEMetabs.begin();
  std::vector< CMetab *>::const_iterator endSorted = ODEMetabs.end();
  for (;itSorted != endSorted; ++itSorted, ++itMetab)
    *itMetab = *itSorted;

  mNumMetabolitesReaction = ReactionMetabs.size();
  itSorted = ReactionMetabs.begin();
  endSorted = ReactionMetabs.end();
  for (;itSorted != endSorted; ++itSorted, ++itMetab)
    *itMetab = *itSorted;

  mNumMetabolitesAssignment = AssignmentMetabs.size();
  itSorted = AssignmentMetabs.begin();
  endSorted = AssignmentMetabs.end();
  for (;itSorted != endSorted; ++itSorted, ++itMetab)
    *itMetab = *itSorted;

  mNumMetabolitesUnused = FixedMetabs.size();
  itSorted = FixedMetabs.begin();
  endSorted = FixedMetabs.end();
  for (;itSorted != endSorted; ++itSorted, ++itMetab)
    *itMetab = *itSorted;
}

//**********************************************************************

CCopasiVectorNS < CReaction > & CModel::getReactions()
{return mSteps;}

const CCopasiVectorNS < CReaction > & CModel::getReactions() const
  {return mSteps;}

CCopasiVector< CMetab > & CModel::getMetabolites()
{return mMetabolites;}

const CCopasiVector< CMetab > & CModel::getMetabolites() const
  {return mMetabolites;}

CCopasiVector< CMetab > & CModel::getMetabolitesX()
{CCHECK return mMetabolitesX;}

const CCopasiVector< CMetab > & CModel::getMetabolitesX() const
  {CCHECK return mMetabolitesX;}

const CCopasiVectorN< CModelValue > & CModel::getModelValues() const
  {return mValues;}

CCopasiVectorN< CModelValue > & CModel::getModelValues()
{return mValues;}

//********

unsigned C_INT32 CModel::getNumMetabs() const
  {return mMetabolites.size();}

unsigned C_INT32 CModel::getNumVariableMetabs() const
  {return mNumMetabolitesReaction;}

unsigned C_INT32 CModel::getNumODEMetabs() const
  {CCHECK return mNumMetabolitesODE;}

unsigned C_INT32 CModel::getNumIndependentMetabs() const
  {CCHECK return mNumMetabolitesIndependent;}

unsigned C_INT32 CModel::getNumDependentMetabs() const
  {CCHECK return mNumMetabolitesReaction - mNumMetabolitesIndependent;}

unsigned C_INT32 CModel::getTotSteps() const
  {return mSteps.size();}

unsigned C_INT32 CModel::getNumModelValues() const
  {return mValues.size();}

const std::string & CModel::getComments() const
  {return mComments;}

const std::string & CModel::getKey() const
  {return mKey;}

CCopasiVectorNS < CCompartment > & CModel::getCompartments()
{return mCompartments;}

const CCopasiVectorNS < CCompartment > & CModel::getCompartments() const
  {return mCompartments;}

/**
 *  Get the Reduced Stoichiometry Matrix of this Model
 */
const CMatrix < C_FLOAT64 >& CModel::getRedStoi() const
  {CCHECK return mRedStoi;}

/**
 *  Get the Stoichiometry Matrix of this Model
 */
const CMatrix < C_FLOAT64 >& CModel::getStoi() const
  {CCHECK return mStoi;}

/**
 *  Get the reordered stoichiometry matrix of this model
 */
const CMatrix < C_FLOAT64 >& CModel::getStoiReordered() const
  {CCHECK return mStoiReordered;}

const CCopasiVector < CMoiety > & CModel::getMoieties() const
  {return mMoieties;}

const CModel::CLinkMatrixView & CModel::getL() const
  {CCHECK return mLView;}

const CMatrix< C_FLOAT64 > & CModel::getL0() const
  {return mL;}

CStateTemplate & CModel::getStateTemplate()
{CCHECK return mStateTemplate;}

std::set< const CCopasiObject * > & CModel::getUpToDateObjects()
{CCHECK return mApplyUpToDateObjects;}

bool CModel::setTitle(const std::string &title)
{
  if (title == "")
    return setObjectName("NoTitle");
  return setObjectName(title);
}

void CModel::setComments(const std::string &comments)
{mComments = comments;}

void CModel::setInitialTime(const C_FLOAT64 & time)
{*mpIValue = time;}

const C_FLOAT64 & CModel::getInitialTime() const
  {return *mpIValue;}

void CModel::setTime(const C_FLOAT64 & time)
{*mpValueAccess = time;}

const C_FLOAT64 & CModel::getTime() const
  {return *mpValueAccess;}

const CVector<unsigned C_INT32> & CModel::getMetabolitePermutation() const
  {CCHECK return mRowLU;}

//**********************************************************************

/**
 *        Returns the index of the metab
 */
C_INT32 CModel::findMetabByName(const std::string & Target) const
  {
    unsigned C_INT32 i, s;
    std::string name;

    s = mMetabolites.size();
    for (i = 0; i < s; i++)
      {
        name = mMetabolites[i]->getObjectName();
        if (name == Target)
          return i;
      }
    return - 1;
  }

/**
 *        Returns the index of the Moiety
 */
C_INT32 CModel::findMoiety(std::string &Target) const
  {
    unsigned C_INT32 i, s;
    std::string name;

    s = mMoieties.size();
    for (i = 0; i < s; i++)
      {
        name = mMoieties[i]->getObjectName();
        if (name == Target)
          return i;
      }
    return - 1;
  }

//**********************************************************************

void CModel::applyInitialValues()
{
  // Copy the initial state to the current state,
  setState(mInitialState);

  // Update all "constant" dependend values.
  // Here "constant" means do not change during simulation.
  std::vector< Refresh * >::const_iterator itRefresh = mConstantRefreshes.begin();
  std::vector< Refresh * >::const_iterator endRefresh = mConstantRefreshes.end();
  while (itRefresh != endRefresh)
    (**itRefresh++)();

  // Update all dependend objects needed for simulation.
  applyAssignments();
}

bool CModel::buildStateTemplate()
{
  CVector<CModelEntity *> Entities(mMetabolitesX.size() + mCompartments.size() + mValues.size());
  CModelEntity ** ppEntity = Entities.array();

  CCopasiVector< CModelValue >::iterator itValue = mValues.begin();
  CCopasiVector< CModelValue >::iterator endValue = mValues.end();
  for (; itValue != endValue; ++itValue)
    if ((*itValue)->getStatus() == CModelEntity::ODE)
      {
        *ppEntity = *itValue;
        (*ppEntity++)->setUsed(true);
      }

  CCopasiVector< CCompartment >::iterator itCompartment = mCompartments.begin();
  CCopasiVector< CCompartment >::iterator endCompartment = mCompartments.end();
  for (; itCompartment != endCompartment; ++itCompartment)
    if ((*itCompartment)->getStatus() == CModelEntity::ODE)
      {
        *ppEntity = *itCompartment;
        (*ppEntity++)->setUsed(true);
      }

  CCopasiVector< CMetab >::iterator itMetab = mMetabolitesX.begin();
  CCopasiVector< CMetab >::iterator endMetab = mMetabolitesX.end();
  for (; itMetab != endMetab; ++itMetab)
    {
      if (!(*itMetab)->isUsed()) break;
      *ppEntity++ = *itMetab;
    }

  itValue = mValues.begin();
  for (; itValue != endValue; ++itValue)
    if ((*itValue)->getStatus() == CModelEntity::ASSIGNMENT)
      {
        *ppEntity = *itValue;
        (*ppEntity++)->setUsed(true);
      }

  itCompartment = mCompartments.begin();
  for (; itCompartment != endCompartment; ++itCompartment)
    if ((*itCompartment)->getStatus() == CModelEntity::ASSIGNMENT)
      {
        *ppEntity = *itCompartment;
        (*ppEntity++)->setUsed(true);
      }

  for (; itMetab != endMetab; ++itMetab)
    *ppEntity++ = *itMetab;

  itValue = mValues.begin();
  for (; itValue != endValue; ++itValue)
    if ((*itValue)->isFixed())
      *ppEntity++ = *itValue;

  itCompartment = mCompartments.begin();
  for (; itCompartment != endCompartment; ++itCompartment)
    if ((*itCompartment)->isFixed())
      *ppEntity++ = *itCompartment;

  mStateTemplate.reorder(Entities);
  mReorderNeeded = false;

  // Now all entities and reactions can be compiled
  ppEntity = mStateTemplate.beginIndependent();
  CModelEntity ** ppEntityEnd = mStateTemplate.endDependent();
  for (; ppEntity != ppEntityEnd; ++ppEntity)
    (*ppEntity)->compile();

  ppEntityEnd = mStateTemplate.endFixed();
  for (; ppEntity != ppEntityEnd; ++ppEntity)
    (*ppEntity)->compile();

  CCopasiVector< CReaction >::iterator itReaction = mSteps.begin();
  CCopasiVector< CReaction >::iterator endReaction = mSteps.end();
  for (; itReaction != endReaction; ++itReaction)
    (*itReaction)->compile();

  return true;
}

bool CModel::buildUserOrder()
{
  CVector<CModelEntity *> Entities(mMetabolitesX.size() + mCompartments.size() + mValues.size());
  CModelEntity ** ppEntity = Entities.array();

  CCopasiVector< CMetab >::iterator itMetab = mMetabolites.begin();
  CCopasiVector< CMetab >::iterator endMetab = mMetabolites.end();
  for (; itMetab != endMetab; ++itMetab)
    *ppEntity++ = *itMetab;;

  CCopasiVector< CCompartment >::iterator itCompartment = mCompartments.begin();
  CCopasiVector< CCompartment >::iterator endCompartment = mCompartments.end();
  for (; itCompartment != endCompartment; ++itCompartment)
    *ppEntity++ = *itCompartment;

  CCopasiVector< CModelValue >::iterator itValue = mValues.begin();
  CCopasiVector< CModelValue >::iterator endValue = mValues.end();

  for (; itValue != endValue; ++itValue)
    *ppEntity++ = *itValue;

  mStateTemplate.setUserOrder(Entities);

  mJacobianPivot.resize(mStateTemplate.getNumIndependent() - mNumMetabolitesIndependent + mNumMetabolitesReaction);

  const unsigned C_INT32 * pUserOrder = mStateTemplate.getUserOrder().array();
  const unsigned C_INT32 * pUserOrderEnd = pUserOrder + mStateTemplate.getUserOrder().size();
  ppEntity = mStateTemplate.getEntities();

  for (unsigned C_INT32 i = 0; pUserOrder != pUserOrderEnd; ++pUserOrder)
    {
      const CModelEntity::Status & Status = ppEntity[*pUserOrder]->getStatus();
      if (Status == CModelEntity::ODE ||
          (Status == CModelEntity::REACTIONS && ppEntity[*pUserOrder]->isUsed()))
        mJacobianPivot[i++] = *pUserOrder - 1;
    }

  return true;
}

bool CModel::buildApplySequence()
{
  // We need to add each used model entity to the objects which need to be updated.
  std::set< const CCopasiObject * > Objects;
  CModelEntity **ppEntity = mStateTemplate.beginIndependent();
  CModelEntity **ppEntityEnd = mStateTemplate.endDependent();

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    Objects.insert(*ppEntity);

  // Further more all reaction fluxes have to be calculated too
  CCopasiVector< CReaction >::iterator itReaction = mSteps.begin();
  CCopasiVector< CReaction >::iterator endReaction = mSteps.end();
  for (; itReaction != endReaction; ++itReaction)
    Objects.insert(*itReaction);

  // We now detect unused assignments, i.e., the result of an assignment is not
  // used during applyAssignments except for itself or another unused assignment.
  bool UnusedFound = true;

  std::set<const CCopasiObject * > Candidate;
  std::set< const CCopasiObject * >::iterator it;
  std::set< const CCopasiObject * >::iterator end = Objects.end();

  while (UnusedFound)
    {
      UnusedFound = false;
      ppEntity = mStateTemplate.beginDependent() + mNumMetabolitesReaction - mNumMetabolitesIndependent;

      for (; ppEntity != ppEntityEnd; ++ppEntity)
        if ((*ppEntity)->isUsed())
          {
            Candidate.insert(*ppEntity);

            for (it = Objects.begin(); it != end; ++it)
              if (*it != *ppEntity &&
                  (*it)->hasCircularDependencies(Candidate))
                break;

            if (it == end)
              {
                UnusedFound = true;
                mReorderNeeded = true;
                (*ppEntity)->setUsed(false);
                Objects.erase(*ppEntity);
              }

            Candidate.erase(*ppEntity);
          }
    }

  if (mReorderNeeded)
    {
      CVector< CModelEntity * > Reorder(mStateTemplate.size() - 1);
      CModelEntity ** ppReorder = Reorder.array();
      ppEntity = mStateTemplate.beginIndependent();
      ppEntityEnd = mStateTemplate.beginDependent() + mNumMetabolitesReaction - mNumMetabolitesIndependent;

      for (; ppEntity != ppEntityEnd; ++ppEntity, ++ppReorder)
        *ppReorder = *ppEntity;

      // :TODO: This must be enhanced as the mMetaboliteX and the state template may get out of sync
      // when we use assignments for metabolites.
      ppEntityEnd = mStateTemplate.endDependent();
      for (; ppEntity != ppEntityEnd; ++ppEntity)
        if ((*ppEntity)->isUsed())
          *ppReorder++ = *ppEntity;

      ppEntity = mStateTemplate.beginDependent() + mNumMetabolitesReaction - mNumMetabolitesIndependent;
      for (; ppEntity != ppEntityEnd; ++ppEntity)
        if (!(*ppEntity)->isUsed())
          *ppReorder++ = *ppEntity;

      ppEntityEnd = mStateTemplate.endFixed();
      for (; ppEntity != ppEntityEnd; ++ppEntity, ++ppReorder)
        *ppReorder = *ppEntity;

      mStateTemplate.reorder(Reorder);
      mReorderNeeded = false;

      // We need to recompile as pointers to values may have changed
      ppEntity = mStateTemplate.beginIndependent();
      ppEntityEnd = mStateTemplate.endFixed();
      for (; ppEntity != ppEntityEnd; ++ppEntity)
        (*ppEntity)->compile();

      itReaction = mSteps.begin();
      endReaction = mSteps.end();
      for (; itReaction != endReaction; ++itReaction)
        (*itReaction)->compile();
    }

  mApplyUpToDateObjects.clear();
  mApplyRefreshes = CCopasiObject::buildUpdateSequence(Objects, this);

  // We have to remove the refresh calls already covered by mConstantRefreshes
  std::vector< Refresh * >::const_iterator itInitialRefresh = mConstantRefreshes.begin();
  std::vector< Refresh * >::const_iterator endInitialRefresh = mConstantRefreshes.end();

  std::vector< Refresh * >::iterator itRefresh;
  std::vector< Refresh * >::iterator endRefresh;

  for (; itInitialRefresh != endInitialRefresh; ++itInitialRefresh)
    {
      itRefresh = mApplyRefreshes.begin();
      endRefresh = mApplyRefreshes.end();

      for (; itRefresh != endRefresh; ++itRefresh)
        if ((*itRefresh)->isEqual(*itInitialRefresh))
          {
            mApplyRefreshes.erase(itRefresh);
            break;
          }
    }

  return true;
}

bool CModel::buildConstantSequence()
{
  // Now find all model entities which are assignments and which do
  // not depend on simulated values, i.e., on model entities of type
  // time, ode, reaction
  std::set< const CCopasiObject * > Dependencies;
  std::set< const CCopasiObject * >::const_iterator itDepend;
  std::set< const CCopasiObject * >::const_iterator endDepend;
  const CModelEntity * pEntity;
  std::set< const CCopasiObject * > Objects;

  CModelEntity ** ppEntity =
    mStateTemplate.beginDependent() - mNumMetabolitesIndependent + mNumMetabolitesReaction;
  CModelEntity ** ppEntityEnd = mStateTemplate.endDependent();
  for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
      Dependencies.clear();
      (*ppEntity)->getAllDependencies(Dependencies);

      itDepend = Dependencies.begin();
      endDepend = Dependencies.end();

      for (; itDepend != endDepend; ++itDepend)
        if ((pEntity = dynamic_cast< const CModelEntity * >(*itDepend)) != NULL &&
            (pEntity->getStatus() != CModelEntity::ASSIGNMENT &&
             pEntity->getStatus() != CModelEntity::FIXED))
          break;

      if (itDepend == endDepend)
        {
          mReorderNeeded = true;
          (*ppEntity)->setUsed(false);
          (*ppEntity)->setUsedOnce(true);
          Objects.insert(*ppEntity);
        }
      else
        (*ppEntity)->setUsedOnce(false);
    }

  mApplyUpToDateObjects.clear();
  mConstantRefreshes = CCopasiObject::buildUpdateSequence(Objects, this);

  return true;
}

const CState & CModel::getInitialState() const
{return mInitialState;}

const CState & CModel::getState() const
  {return mCurrentState;}

void CModel::setInitialState(const CState & state)
{
  // The situation where the state has the updateDependentRequired flag
  // set is currently not handled.

  assert (!state.isUpdateDependentRequired());

  // To prevent triggering the above assertion please use:
  //   setState(state);
  //   applyAssignements();
  //   setInititalState(getState());
  //
  // This is not done automatically since it changes the current state of
  // the model.

  mInitialState = state;

  // We have to update the moieties
  CCopasiVector< CMoiety >::iterator itMoiety = mMoieties.begin();
  CCopasiVector< CMoiety >::iterator endMoiety = mMoieties.end();

  for (; itMoiety != endMoiety; ++itMoiety)
    (*itMoiety)->setInitialValue();

  // The concentrations for the metabolites need to be updated
  CCopasiVector< CMetab >::iterator itMetab = mMetabolites.begin();
  CCopasiVector< CMetab >::iterator endMetab = mMetabolites.end();

  for (; itMetab != endMetab; ++itMetab)
    (*itMetab)->refreshInitialConcentration();

  return;
}

void CModel::setState(const CState & state)
{
  mCurrentState = state;

  return;
}

void CModel::applyAssignments(void)
{
  // Depending on which model we are using we need to update
  // the particle numbers for the dependent metabolites.
  if (mCurrentState.isUpdateDependentRequired())
    {
      C_FLOAT64 * pDependent = mCurrentState.beginDependent();
      CCopasiVector< CMoiety >::iterator itMoiety = mMoieties.begin();
      CCopasiVector< CMoiety >::iterator endMoiety = mMoieties.end();

      for (; itMoiety != endMoiety; ++itMoiety, ++pDependent)
        *pDependent = (*itMoiety)->dependentNumber();

      mCurrentState.setUpdateDependentRequired(false);
    }

  std::vector< Refresh * >::const_iterator itRefresh = mApplyRefreshes.begin();
  std::vector< Refresh * >::const_iterator endRefresh = mApplyRefreshes.end();

  while (itRefresh != endRefresh)
    (**itRefresh++)();

  // Store the particle fluxes for further calculations
  CCopasiVector< CReaction >::iterator it = mSteps.begin();
  CCopasiVector< CReaction >::iterator end = mSteps.end();

  C_FLOAT64 * pFlux = mParticleFluxes.array();

  for (;it != end; ++it, ++pFlux)
    *pFlux = (*it)->getParticleFlux();
}

void CModel::calculateDerivatives(C_FLOAT64 * derivatives)
{
  C_FLOAT64 * pTmp = derivatives;

  // First retreive derivatives of quantities determined by ODE
  // The offset 1 is for the model time which is always the first
  // state variable.
  CModelEntity ** ppIt = mStateTemplate.getEntities() + 1;
  CModelEntity ** ppEnd =
    ppIt + mStateTemplate.getNumIndependent() - mNumMetabolitesIndependent;

  for (; ppIt != ppEnd; ++ppIt, ++pTmp)
    *pTmp = (*ppIt)->getRate();

  // Now calculate derivatives of all metabolites determined by reactions
  char T = 'N';
  C_INT M = 1;
  C_INT N = mNumMetabolitesReaction;
  C_INT K = mSteps.size();
  C_FLOAT64 Alpha = 1.0;
  C_FLOAT64 Beta = 0.0;

  dgemm_(&T, &T, &M, &N, &K, &Alpha, mParticleFluxes.array(), &M,
         mStoiReordered.array(), &K, &Beta, pTmp, &M);
}

void CModel::calculateDerivativesX(C_FLOAT64 * derivativesX)
{
  C_FLOAT64 * pTmp = derivativesX;

  // First retreive derivatives of quantities determined by ODE
  // The offset 1 is for the model time which is always the first
  // state variable.
  CModelEntity ** ppIt = mStateTemplate.getEntities() + 1;
  CModelEntity ** ppEnd =
    ppIt + mStateTemplate.getNumIndependent() - mNumMetabolitesIndependent;

  for (; ppIt != ppEnd; ++ppIt, ++pTmp)
    *pTmp = (*ppIt)->getRate();

  // Now calculate derivatives of the independent metabolites determined by reactions
  char T = 'N';
  C_INT M = 1;
  C_INT N = mNumMetabolitesIndependent;
  C_INT K = mSteps.size();
  C_FLOAT64 Alpha = 1.0;
  C_FLOAT64 Beta = 0.0;

  dgemm_(&T, &T, &M, &N, &K, &Alpha, mParticleFluxes.array(), &M,
         mRedStoi.array(), &K, &Beta, pTmp, &M);
}

void CModel::refreshRates()
{
  CVector< C_FLOAT64 > Rates(mStateTemplate.getNumIndependent() - mNumMetabolitesIndependent + mNumMetabolitesReaction);
  C_FLOAT64 * pRate = Rates.array();
  calculateDerivatives(pRate);

  // The offset 1 is for the model time which is always the first
  // state variable.
  CModelEntity ** ppIt =
    mStateTemplate.getEntities() + 1 + mStateTemplate.getNumIndependent() - mNumMetabolitesIndependent;

  CModelEntity ** ppEnd = ppIt + mNumMetabolitesReaction;
  pRate += mStateTemplate.getNumIndependent() - mNumMetabolitesIndependent;

  for (; ppIt != ppEnd; ++ppIt, ++pRate)
    (*ppIt)->setRate(*pRate);
}

void CModel::calculateElasticityMatrix(const C_FLOAT64 & factor,
                                       const C_FLOAT64 & resolution)
{
  unsigned C_INT32 Col;
  unsigned C_INT32 nCol = mElasticities.numCols();

  C_FLOAT64 * itE;
  C_FLOAT64 * beginE = mElasticities.array();

  CCopasiVector< CReaction >::const_iterator itReaction;
  CCopasiVector< CReaction >::const_iterator beginReaction = mSteps.begin();
  CCopasiVector< CReaction >::const_iterator endReaction = mSteps.end();

  CModelEntity ** itEntity;
  CModelEntity ** beginEntity = mStateTemplate.beginIndependent();
  CModelEntity ** endEntity = mStateTemplate.endDependent();

  for (itEntity = beginEntity, Col = 0; itEntity != endEntity; ++itEntity, ++Col)
    {
      // :TODO: This only works for entities of type metabolites.
      //        The scaling factor for other entites should be 1.
      const C_FLOAT64 invVolume =
        1.0 / static_cast<CMetab *>(*itEntity)->getCompartment()->getValue();
      C_FLOAT64 * pX =
        const_cast<C_FLOAT64 *>(&static_cast<CMetab *>(*itEntity)->getConcentration());

      for (itReaction = beginReaction, itE = beginE + Col;
           itReaction != endReaction;
           ++itReaction, itE += nCol)
        * itE = invVolume * (*itReaction)->calculatePartialDerivative(pX, factor, resolution);
    }

  // DebugFile << "CModel::calculateElasticityMatrix()" << std::endl;
  // DebugFile << mElasticities << std::endl;

  return;
}

void CModel::calculateJacobian(CMatrix< C_FLOAT64 > & jacobian,
                               const C_FLOAT64 & derivationFactor,
                               const C_FLOAT64 & resolution)
{
  if (mCurrentState.isUpdateDependentRequired())
    {
      C_FLOAT64 * pDependent = mCurrentState.beginDependent();
      CCopasiVector< CMoiety >::iterator itMoiety = mMoieties.begin();
      CCopasiVector< CMoiety >::iterator endMoiety = mMoieties.end();

      for (; itMoiety != endMoiety; ++itMoiety, ++pDependent)
        *pDependent = (*itMoiety)->dependentNumber();

      mCurrentState.setUpdateDependentRequired(false);
    }

  unsigned C_INT32 Dim =
    mCurrentState.getNumIndependent() + mNumMetabolitesReaction - mNumMetabolitesIndependent;
  unsigned C_INT32 Col;

  jacobian.resize(Dim, Dim);
  CMatrix< C_FLOAT64 > Jacobian(Dim, Dim);

  C_FLOAT64 Store;
  C_FLOAT64 X1;
  C_FLOAT64 X2;
  C_FLOAT64 InvDelta;

  CVector< C_FLOAT64 > Y1(Dim);
  CVector< C_FLOAT64 > Y2(Dim);

  C_FLOAT64 * pY1;
  C_FLOAT64 * pY2;

  C_FLOAT64 * pX = mCurrentState.beginIndependent();
  C_FLOAT64 * pXEnd = pX + Dim;

  C_FLOAT64 * pJacobian;
  C_FLOAT64 * pJacobianEnd = Jacobian.array() + Dim * Dim;

  for (Col = 0; pX != pXEnd; ++pX, ++Col)
    {
      Store = *pX;

      if (fabs(Store * 2.0 * derivationFactor) < resolution)
        {
          X1 = resolution;
          X2 = -resolution;
        }
      else
        {
          X1 = Store * (1.0 + derivationFactor);
          X2 = Store * (1.0 - derivationFactor);
        }
      InvDelta = 1.0 / (X2 - X1);

      *pX = X1;
      applyAssignments();
      calculateDerivatives(Y1.array());

      *pX = X2;
      applyAssignments();
      calculateDerivatives(Y2.array());

      *pX = Store;

      pJacobian = Jacobian.array() + Col;
      pY1 = Y1.array();
      pY2 = Y2.array();

      for (; pJacobian < pJacobianEnd; pJacobian += Dim, ++pY1, ++pY2)
        * pJacobian = (*pY2 - *pY1) * InvDelta;
    }

  applyAssignments();

  //  jacobian = Jacobian;
  //  return;

  // :TODO: this can be incorporated into the above avoiding a temporary matrix.

  // We need to bring the jacobian into the expected order, i.e.,
  // convert it to the user defined order
  unsigned C_INT32 * pPermRow = mJacobianPivot.array();
  unsigned C_INT32 * pPermEnd = pPermRow + mJacobianPivot.size();
  unsigned C_INT32 * pPermCol;

  C_FLOAT64 * pTo;
  pTo = jacobian.array();

  for (; pPermRow < pPermEnd; ++pPermRow)
    {
      pJacobian = Jacobian.array() + *pPermRow * Dim;

      for (pPermCol = mJacobianPivot.array(); pPermCol < pPermEnd; ++pPermCol, ++pTo)
        *pTo = *(pJacobian + *pPermCol);
    }

  // DebugFile << jacobian << std::endl;
}

void CModel::calculateJacobianX(CMatrix< C_FLOAT64 > & jacobianX,
                                const C_FLOAT64 & derivationFactor,
                                const C_FLOAT64 & resolution)
{
  unsigned C_INT32 Dim = mCurrentState.getNumIndependent();
  unsigned C_INT32 Col;

  jacobianX.resize(Dim, Dim);

  C_FLOAT64 Store;
  C_FLOAT64 X1;
  C_FLOAT64 X2;
  C_FLOAT64 InvDelta;

  CVector< C_FLOAT64 > Y1(Dim);
  CVector< C_FLOAT64 > Y2(Dim);

  C_FLOAT64 * pY1;
  C_FLOAT64 * pY2;

  C_FLOAT64 * pX = mCurrentState.beginIndependent();
  C_FLOAT64 * pXEnd = pX + Dim;

  C_FLOAT64 * pJacobian;
  C_FLOAT64 * pJacobianEnd = jacobianX.array() + Dim * Dim;

  for (Col = 0; pX != pXEnd; ++pX, ++Col)
    {
      Store = *pX;

      if (fabs(Store * 2.0 * derivationFactor) < resolution)
        {
          X1 = resolution;
          X2 = -resolution;
        }
      else
        {
          X1 = Store * (1.0 + derivationFactor);
          X2 = Store * (1.0 - derivationFactor);
        }
      InvDelta = 1.0 / (X2 - X1);

      *pX = X1;
      mCurrentState.setUpdateDependentRequired(true);
      applyAssignments();
      calculateDerivativesX(Y1.array());

      *pX = X2;
      mCurrentState.setUpdateDependentRequired(true);
      applyAssignments();
      calculateDerivativesX(Y2.array());

      *pX = Store;

      pJacobian = jacobianX.array() + Col;
      pY1 = Y1.array();
      pY2 = Y2.array();

      for (; pJacobian < pJacobianEnd; pJacobian += Dim, ++pY1, ++pY2)
        * pJacobian = (*pY2 - *pY1) * InvDelta;
    }

  mCurrentState.setUpdateDependentRequired(true);
  applyAssignments();
}

C_FLOAT64 CModel::calculateDivergence() const
  {
    fatalError(); //not yet implemented
    return 0.0;
  }

bool CModel::setVolumeUnit(const std::string & name)
{
  int unit = toEnum(name.c_str(), VolumeUnitNames);

  if (-1 == unit)
    return setVolumeUnit(ml);
  else
    return setVolumeUnit((CModel::VolumeUnit) unit);
}

bool CModel::setVolumeUnit(const CModel::VolumeUnit & unit)
{
  mVolumeUnit = unit;
  return true;
}

std::string CModel::getVolumeUnitName() const
  {
    return VolumeUnitNames[mVolumeUnit];
  }

CModel::VolumeUnit CModel::getVolumeUnitEnum() const
  {
    return mVolumeUnit;
  }

//****

bool CModel::setTimeUnit(const std::string & name)
{
  int unit = toEnum(name.c_str(), TimeUnitNames);

  if (-1 == unit)
    return setTimeUnit(s);
  else
    return setTimeUnit((CModel::TimeUnit) unit);
}

bool CModel::setTimeUnit(const CModel::TimeUnit & unit)
{
  mTimeUnit = unit;
  return true;
}

std::string CModel::getTimeUnitName() const
  {
    return TimeUnitNames[mTimeUnit];
  }

CModel::TimeUnit CModel::getTimeUnitEnum() const
  {
    return mTimeUnit;
  }

//****

bool CModel::setQuantityUnit(const std::string & name)
{
  int unit = toEnum(name.c_str(), QuantityUnitNames);

  if (-1 == unit)
    return setQuantityUnit(mMol);
  else
    return setQuantityUnit((CModel::QuantityUnit) unit);
}

bool CModel::setQuantityUnit(const CModel::QuantityUnit & unit)
{
  bool success = true;
  mQuantityUnit = unit;

  switch (unit)
    {
    case Mol:
      mQuantity2NumberFactor = AVOGADRO;
      break;

    case mMol:
      mQuantity2NumberFactor = AVOGADRO * 1E-3;
      break;

    case microMol:
      mQuantity2NumberFactor = AVOGADRO * 1E-6;
      break;

    case nMol:
      mQuantity2NumberFactor = AVOGADRO * 1E-9;
      break;

    case pMol:
      mQuantity2NumberFactor = AVOGADRO * 1E-12;
      break;

    case fMol:
      mQuantity2NumberFactor = AVOGADRO * 1E-15;
      break;

    case number:
      mQuantity2NumberFactor = 1.0;
      break;

    default:
      mQuantityUnit = number;
      mQuantity2NumberFactor = 1.0;
      success = false;
    }

  mNumber2QuantityFactor = 1.0 / mQuantity2NumberFactor;

  //adapt particle numbers
  C_INT32 i, imax = mMetabolites.size();
  for (i = 0; i < imax; ++i)
    {
      //update particle numbers
      mMetabolites[i]->setInitialConcentration(mMetabolites[i]->getInitialConcentration());
      mMetabolites[i]->setConcentration(mMetabolites[i]->getConcentration());
    }

  return success;
}

std::string CModel::getQuantityUnitName() const
  {
    return QuantityUnitNames[mQuantityUnit];
  }

CModel::QuantityUnit CModel::getQuantityUnitEnum() const
  {
    return mQuantityUnit;
  }

void CModel::setModelType(const CModel::ModelType & modelType)
{mType = modelType;}

const CModel::ModelType & CModel::getModelType() const
  {return mType;}

const C_FLOAT64 & CModel::getQuantity2NumberFactor() const
  {return mQuantity2NumberFactor;}

const C_FLOAT64 & CModel::getNumber2QuantityFactor() const
  {return mNumber2QuantityFactor;}

//*****

std::string CModel::getConcentrationUnitName() const
  {
    return getQuantityUnitName() + "/" + getVolumeUnitName();
  }

std::string CModel::getConcentrationRateUnitName() const
  {
    return getQuantityUnitName()
    + "/(" + getVolumeUnitName()
    + "*" + getTimeUnitName() + ")";
  }

std::string CModel::getQuantityRateUnitName() const
  {
    return getQuantityUnitName()
    + "/" + getTimeUnitName();
  }

//**********************************************************************

std::set<std::string> CModel::listReactionsDependentOnFunction(const std::string & key)
{
  std::set<std::string> reacKeys;
  std::set<std::string>::iterator it, end;

  const CCopasiVectorN<CReaction> & Reactions = getReactions();
  C_INT32 j, jmax = Reactions.size();

  for (j = 0; j < jmax; j++)
    {
      if (key == Reactions[j]->getFunction()->getKey())
        reacKeys.insert(Reactions[j]->getKey());
    }

  return reacKeys;
}

void CModel::appendDependentReactions(std::set< const CCopasiObject * > candidates,
                                      std::set< const CCopasiObject * > & dependentReactions) const
  {
    CCopasiVectorN< CReaction >::const_iterator it = mSteps.begin();
    CCopasiVectorN< CReaction >::const_iterator end = mSteps.end();

    for (; it != end; ++it)
      if ((*it)->hasCircularDependencies(candidates))
        dependentReactions.insert((*it));

    return;
  }

void CModel::appendDependentMetabolites(std::set< const CCopasiObject * > candidates,
                                        std::set< const CCopasiObject * > & dependentMetabolites) const
  {
    CCopasiVectorN< CCompartment >::const_iterator itComp = mCompartments.begin();
    CCopasiVectorN< CCompartment >::const_iterator endComp = mCompartments.end();

    CCopasiVectorN< CMetab >::const_iterator it;
    CCopasiVectorN< CMetab >::const_iterator end;

    for (; itComp != endComp; ++itComp)
      {
        it = (*itComp)->getMetabolites().begin();
        end = (*itComp)->getMetabolites().end();

        for (; it != end; ++it)
          if (candidates.find((*it)->getCompartment()->getObject(CCopasiObjectName("Reference=Volume"))) != candidates.end() ||
              (*it)->hasCircularDependencies(candidates))
            dependentMetabolites.insert((*it));
      }

    return;
  }

void CModel::appendDependentCompartments(std::set< const CCopasiObject * > candidates,
    std::set< const CCopasiObject * > & dependentCompartments) const
  {
    CCopasiVectorN< CCompartment >::const_iterator it = mCompartments.begin();
    CCopasiVectorN< CCompartment >::const_iterator end = mCompartments.end();

    for (; it != end; ++it)
      if ((*it)->hasCircularDependencies(candidates))
        dependentCompartments.insert((*it));

    return;
  }

void CModel::appendDependentModelValues(std::set< const CCopasiObject * > candidates,
                                        std::set< const CCopasiObject * > & dependentModelValues) const
  {
    CCopasiVectorN< CModelValue >::const_iterator it = mValues.begin();
    CCopasiVectorN< CModelValue >::const_iterator end = mValues.end();

    for (; it != end; ++it)
      if ((*it)->hasCircularDependencies(candidates))
        dependentModelValues.insert((*it));

    return;
  }

//**********************************************************************

CMetab* CModel::createMetabolite(const std::string & name,
                                 const std::string & compartment,
                                 const C_FLOAT64 & iconc,
                                 const CMetab::Status & status)
{
  unsigned C_INT32 Index;

  if (mCompartments.size() == 0)
    return NULL;

  if (compartment == "")
    Index = 0;
  else if ((Index = mCompartments.getIndex(compartment)) == C_INVALID_INDEX)
    return NULL;

  if (mCompartments[Index]->getMetabolites().getIndex(name) != C_INVALID_INDEX)
    return NULL;

  CMetab * pMetab = new CMetab(name);

  if (!mCompartments[Index]->addMetabolite(pMetab))
    {
      delete pMetab;
      return NULL;
    }

  pMetab->setStatus(status);
  pMetab->setInitialConcentration(iconc);

  if (!mMetabolites.add(pMetab))
    return NULL;

  setCompileFlag();

  return pMetab;
}
bool CModel::removeMetabolite(const std::string & key,
                              const bool & recursive)
{
  CMetab* pMetabolite =
    dynamic_cast<CMetab *>(GlobalKeys.get(key));

  if (!pMetabolite)
    return false;

  if (recursive)
    {
      /* Before deleting  delete all the objects that are dependent */
      std::set< const CCopasiObject * > ToBeDeleted;
      std::set< const CCopasiObject * >::const_iterator it, end;

      appendDependentReactions(pMetabolite->getDeletedObjects(), ToBeDeleted);
      for (it = ToBeDeleted.begin(), end = ToBeDeleted.end(); it != end; ++it)
        removeReaction((*it)->getKey(), false);

      ToBeDeleted.clear();
      appendDependentMetabolites(pMetabolite->getDeletedObjects(), ToBeDeleted);
      for (it = ToBeDeleted.begin(), end = ToBeDeleted.end(); it != end; ++it)
        removeMetabolite((*it)->getKey(), false);

      ToBeDeleted.clear();
      appendDependentCompartments(pMetabolite->getDeletedObjects(), ToBeDeleted);
      for (it = ToBeDeleted.begin(), end = ToBeDeleted.end(); it != end; ++it)
        removeCompartment((*it)->getKey(), false);

      ToBeDeleted.clear();
      appendDependentModelValues(pMetabolite->getDeletedObjects(), ToBeDeleted);
      for (it = ToBeDeleted.begin(), end = ToBeDeleted.end(); it != end; ++it)
        removeModelValue((*it)->getKey(), false);
    }

  /* Check if metabolite with that name exists */
  unsigned C_INT32 index = mMetabolites.getIndex(pMetabolite);
  if (index == C_INVALID_INDEX)
    return false;

  mMetabolites.remove(index);

  pdelete(pMetabolite);

  setCompileFlag();

  return true;
}

CCompartment* CModel::createCompartment(const std::string & name,
                                        const C_FLOAT64 & volume)
{
  // check if there is already a volume with this name
  if (mCompartments.getIndex(name) != C_INVALID_INDEX)
    return NULL;

  CCompartment * cpt = new CCompartment(name);

  cpt->setInitialValue(volume);
  //cpt->setVolume(volume);

  if (!mCompartments.add(cpt, true))
    {
      delete cpt;
      return NULL;
    }

  return cpt;
}

bool CModel::removeCompartment(const std::string & key,
                               const bool & recursive)
{
  CCompartment *pCompartment =
    dynamic_cast< CCompartment * >(GlobalKeys.get(key));

  if (!pCompartment)
    return false;

  if (recursive)
    {
      /* Before deleting  delete all the objects that are dependent */
      std::set< const CCopasiObject * > ToBeDeleted;
      std::set< const CCopasiObject * >::const_iterator it, end;

      appendDependentReactions(pCompartment->getDeletedObjects(), ToBeDeleted);
      for (it = ToBeDeleted.begin(), end = ToBeDeleted.end(); it != end; ++it)
        removeReaction((*it)->getKey(), false);

      ToBeDeleted.clear();
      appendDependentMetabolites(pCompartment->getDeletedObjects(), ToBeDeleted);
      for (it = ToBeDeleted.begin(), end = ToBeDeleted.end(); it != end; ++it)
        removeMetabolite((*it)->getKey(), false);

      ToBeDeleted.clear();
      appendDependentCompartments(pCompartment->getDeletedObjects(), ToBeDeleted);
      for (it = ToBeDeleted.begin(), end = ToBeDeleted.end(); it != end; ++it)
        removeCompartment((*it)->getKey(), false);

      ToBeDeleted.clear();
      appendDependentModelValues(pCompartment->getDeletedObjects(), ToBeDeleted);
      for (it = ToBeDeleted.begin(), end = ToBeDeleted.end(); it != end; ++it)
        removeModelValue((*it)->getKey(), false);
    }

  //Check if Compartment with that name exists
  unsigned C_INT32 index =
    mCompartments.CCopasiVector< CCompartment >::getIndex(pCompartment);
  if (index == C_INVALID_INDEX)
    return false;

  mCompartments.CCopasiVector< CCompartment >::remove(index);

  //compile();

  return true;
}

CReaction* CModel::createReaction(const std::string & name)
{
  if (mSteps.getIndex(name) != C_INVALID_INDEX)
    return NULL;

  CReaction * pReaction = new CReaction(name);

  if (!mSteps.add(pReaction, true))
    {
      delete pReaction;
      return NULL;
    }

  setCompileFlag();
  return pReaction;
}

bool CModel::removeReaction(const std::string & key,
                            const bool & recursive)
{
  CReaction * pReaction =
    dynamic_cast< CReaction * >(GlobalKeys.get(key));

  if (!pReaction)
    return false;

  //Check if Reaction exists
  unsigned C_INT32 index =
    mSteps.CCopasiVector< CReaction >::getIndex(pReaction);

  if (index == C_INVALID_INDEX)
    return false;

  mSteps.CCopasiVector< CReaction >::remove(index);

  setCompileFlag();
  mMoieties.resize(0);

  return true;
}

CModelValue* CModel::createModelValue(const std::string & name,
                                      const C_FLOAT64 & value)
{
  // check if there is already a value with this name
  if (mValues.getIndex(name) != C_INVALID_INDEX)
    return NULL;

  CModelValue * cmv = new CModelValue(name);

  cmv->setInitialValue(value);
  cmv->setValue(value);

  if (!mValues.add(cmv, true))
    {
      delete cmv;
      return NULL;
    }

  //compile();
  mStateTemplate.add(cmv);

  return cmv;
}

bool CModel::removeModelValue(const std::string & key,
                              const bool & recursive)
{
  CModelValue *pModelValue =
    dynamic_cast< CModelValue * >(GlobalKeys.get(key));

  if (!pModelValue)
    return false;

  if (recursive)
    {
      /* Before deleting  delete all the objects that are dependent */
      std::set< const CCopasiObject * > ToBeDeleted;
      std::set< const CCopasiObject * >::const_iterator it, end;

      appendDependentReactions(pModelValue->getDeletedObjects(), ToBeDeleted);
      for (it = ToBeDeleted.begin(), end = ToBeDeleted.end(); it != end; ++it)
        removeReaction((*it)->getKey(), false);

      ToBeDeleted.clear();
      appendDependentMetabolites(pModelValue->getDeletedObjects(), ToBeDeleted);
      for (it = ToBeDeleted.begin(), end = ToBeDeleted.end(); it != end; ++it)
        removeMetabolite((*it)->getKey(), false);

      ToBeDeleted.clear();
      appendDependentCompartments(pModelValue->getDeletedObjects(), ToBeDeleted);
      for (it = ToBeDeleted.begin(), end = ToBeDeleted.end(); it != end; ++it)
        removeCompartment((*it)->getKey(), false);

      ToBeDeleted.clear();
      appendDependentModelValues(pModelValue->getDeletedObjects(), ToBeDeleted);
      for (it = ToBeDeleted.begin(), end = ToBeDeleted.end(); it != end; ++it)
        removeModelValue((*it)->getKey(), false);
    }

  //Check if Value with that name exists
  unsigned C_INT32 index =
    mValues.CCopasiVector< CModelValue >::getIndex(pModelValue);
  if (index == C_INVALID_INDEX)
    return false;

  mValues.CCopasiVector< CModelValue >::remove(index);

  //compile();

  return true;
}

bool CModel::convert2NonReversible()
{
  //TODO check if there are any reversible reactions
  //TODO warn the user
  //TODO tell the gui about changes
  //TODO generate report ?

  bool ret = true;

  std::vector<std::string> reactionsToDelete;

  CReaction *reac0, *reac1, *reac2;
  CReactionInterface ri1(this), ri2(this);
  std::string fn, rn1, rn2;

  //CModel* model = dynamic_cast< CModel * >(GlobalKeys.get(objKey));
  //if (!model) return false;

  CCopasiVectorN< CReaction > & steps = this->getReactions();

  unsigned C_INT32 i, imax = steps.size();
  for (i = 0; i < imax; ++i)
    if (steps[i]->isReversible())
      {
        ret = false;
        reac0 = steps[i];
        //std::cout << i << "  ";

        //create the two new reactions
        rn1 = reac0->getObjectName() + " (forward)";
        reac1 = createReaction(rn1);
        //reac1 = new CReaction(/* *reac0, &steps*/);
        //reac1->setObjectName(rn1);
        //steps.add(reac1);

        rn2 = reac0->getObjectName() + " (backward)";
        reac2 = createReaction(rn2);
        //reac2 = new CReaction(/* *reac0, &steps*/);
        //reac2->setObjectName(rn2);
        //steps.add(reac2);

        ri1.initFromReaction(reac0->getKey());
        ri1.setReactionName(rn1);

        ri2.initFromReaction(reac0->getKey());
        ri2.setReactionName(rn2);

        //set the new function
        fn = reac0->getFunction()->getObjectName();
        //std::cout << fn << "  " << std::endl;

        if (fn == "Mass action (reversible)")
          {
            ri1.setReversibility(false, "Mass action (irreversible)");
            ri2.reverse(false, "Mass action (irreversible)");
          }
        else if (fn == "Constant flux (reversible)")
          {
            ri1.setReversibility(false, "Constant flux (irreversible)");
            ri2.reverse(false, "Constant flux (irreversible)");
          }
        else
          {
            //ri1.setReversibility(false);
            ri2.reverse(false, "Mass action (irreversible)");
          }

        ri1.writeBackToReaction(reac1);
        ri2.writeBackToReaction(reac2);

        //set the kinetic parameters

        if (fn == "Mass action (reversible)")
          {
            if (reac0->isLocalParameter("k1"))
              reac1->setParameterValue("k1", reac0->getParameterValue("k1"));
            else
              reac1->setParameterMapping("k1", reac0->getParameterMapping("k1")[0]);

            if (reac0->isLocalParameter("k2"))
              reac2->setParameterValue("k1", reac0->getParameterValue("k2"));
            else
              reac2->setParameterMapping("k1", reac0->getParameterMapping("k2")[0]);

            ret = true;
          }
        else
          {
            reac2->setParameterValue("k1", 0);
          }

        //remove the old reaction
        reactionsToDelete.push_back(reac0->getObjectName());
      }

  imax = reactionsToDelete.size();
  for (i = 0; i < imax; ++i)
    steps.remove(reactionsToDelete[i]);

  //protectedNotify(ListViews::MODEL, ListViews::CHANGE, objKey);

  return ret;
}

//**********************************************************************

void CModel::initObjects()
{
  mKey = GlobalKeys.add("Model", this);

  // The regular CModelEntity mechanism does not work since
  // CModel is created before mStateTemplate :(
  C_FLOAT64 InitialValue = *mpIValue;
  C_FLOAT64 Value = *mpValueAccess;
  pdelete(mpIValue);
  pdelete(mpValueData);
  mStateTemplate.add(this);
  *mpIValue = InitialValue;
  *mpValueAccess = Value;

  mpIValueReference->setObjectName("Initial Time");
  mpValueReference->setObjectName("Time");

  addObjectReference("Comments", mComments);

  // These are broken since they contain pointers to values :(
  //  addVectorReference("Fluxes", mFluxes, CCopasiObject::ValueDbl);
  //  addVectorReference("Particle Fluxes", mParticleFluxes, CCopasiObject::ValueDbl);

  addMatrixReference("Stoichiometry", mStoi, CCopasiObject::ValueDbl);
  addMatrixReference("Reduced Model Stoichiometry", mRedStoi, CCopasiObject::ValueDbl);

  addMatrixReference("Link Matrix", mLView, CCopasiObject::ValueDbl);
  addObjectReference("Quantity Unit", mQuantityUnit);
  addObjectReference("Quantity Conversion Factor", mQuantity2NumberFactor, CCopasiObject::ValueDbl);

  CArrayAnnotation * tmp = new CArrayAnnotation("Stoichiometry(ann)", this, new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mStoi));
  tmp->setOnTheFly(true);
  tmp->setDescription("Stoichiometry Matrix");
  tmp->setDimensionDescription(0, "Metabolites");
  tmp->setDimensionDescription(1, "Reactions");
  tmp->setCopasiVector(0, &mMetabolites);
  tmp->setCopasiVector(1, &mSteps);

  tmp = new CArrayAnnotation("Reduced stoichiometry(ann)", this, new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mRedStoi));
  tmp->setOnTheFly(true);
  tmp->setDescription("Reduced stoichiometry Matrix");
  tmp->setDimensionDescription(0, "Metabolites");
  tmp->setDimensionDescription(1, "Reactions");
  tmp->setCopasiVector(0, &mMetabolitesX);
  tmp->setCopasiVector(1, &mSteps);

  tmp = new CArrayAnnotation("Link matrix(ann)", this, new CCopasiMatrixInterface<CLinkMatrixView>(&mLView));
  tmp->setOnTheFly(true);
  tmp->setDescription("Link matrix");
  tmp->setDimensionDescription(0, "Metabolites (full system)");
  tmp->setDimensionDescription(1, "Metabolites (reduced system)");
  tmp->setCopasiVector(0, &mMetabolites);
  tmp->setCopasiVector(1, &mMetabolitesX);
}

bool CModel::hasReversibleReaction() const
  {
    unsigned C_INT32 i, imax = mSteps.size();
    for (i = 0; i < imax; ++i) if (mSteps[i]->isReversible()) return true;

    return false;
  }

void CModel::setCompileHandler(CProcessReport* pHandler)
{mpCompileHandler = pHandler;}

CProcessReport* CModel::getCompileHandlerAddr()
{return mpCompileHandler;}

//**********************************************************************
//                   CLinkMatrixView
//**********************************************************************

const CModel::CLinkMatrixView::elementType CModel::CLinkMatrixView::mZero = 0.0;
const CModel::CLinkMatrixView::elementType CModel::CLinkMatrixView::mUnit = 1.0;

CModel::CLinkMatrixView::CLinkMatrixView(const CMatrix< C_FLOAT64 > & A,
    const unsigned C_INT32 & numIndependent):
    mA(A),
    mNumIndependent(numIndependent)
{CONSTRUCTOR_TRACE;}

CModel::CLinkMatrixView::~CLinkMatrixView()
{DESTRUCTOR_TRACE;}

CModel::CLinkMatrixView &
CModel::CLinkMatrixView::operator = (const CModel::CLinkMatrixView & rhs)
{
  const_cast< CMatrix< C_FLOAT64 > &>(mA) = rhs.mA;
  const_cast< unsigned C_INT32 & >(mNumIndependent) = rhs.mNumIndependent;

  return *this;
}

unsigned C_INT32 CModel::CLinkMatrixView::numRows() const
  {return mNumIndependent + mA.numRows();}

unsigned C_INT32 CModel::CLinkMatrixView::numCols() const
  {return mA.numCols();}

std::ostream &operator<<(std::ostream &os,
                         const CModel::CLinkMatrixView & A)
{
  unsigned C_INT32 i, imax = A.numRows();
  unsigned C_INT32 j, jmax = A.numCols();
  os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

  for (i = 0; i < imax; i++)
    {
      for (j = 0; j < jmax; j++)
        os << "\t" << A(i, j);
      os << std::endl;
    }
  return os;
}

std::string CModel::suitableForStochasticSimulation() const
  {
    unsigned C_INT32 i, reactSize = mSteps.size();
    C_INT32 multInt;
    unsigned C_INT32 j;
    C_FLOAT64 multFloat;
    //  C_INT32 metabSize = mMetabolites->size();

    for (i = 0; i < reactSize; i++) // for every reaction
      {
        // TEST getCompartmentNumber() == 1
        //if (mSteps[i]->getCompartmentNumber() != 1) return - 1;

        // TEST isReversible() == 0
        if (mSteps[i]->isReversible() != 0)
          return "At least one reaction is reversible. That means stochastic simulation is not possible. \nYou can try \"Tools|Convert to irreversible\" which will split the reversible reactions \n into two irreversible reactions. However you will have to fix the kinetics afterwards.";

        // TEST integer stoichometry
        // Iterate through each the metabolites
        // juergen: the number of rows of mStoi equals the number of non-fixed metabs!
        //  for (j=0; i<metabSize; j++)
        for (j = 0; j < mStoi.numRows(); j++)
          {
            multFloat = mStoi(j, i);
            multInt = static_cast<C_INT32>(floor(multFloat + 0.5)); // +0.5 to get a rounding out of the static_cast to int!
            if ((multFloat - multInt) > 0.01)
              return "Not all stoichiometries are integer numbers. \nThat means that discrete simulation is not possible.";
          }
      }

    for (i = 0; i < mMetabolites.size(); ++i)
      {
        if (mMetabolites[i]->getInitialValue() > LLONG_MAX)
          return "At least one particle number in the inial state is too big.";
      }

    return ""; // Model is appropriate for hybrid simulation
  }

#ifdef COPASI_DEBUG
void CModel::check() const
  {
    if (mCompileIsNecessary)
    {std::cout << "******** compile should have been called" << std::endl;}
  }
#endif

void CModel::buildLinkZero()
{
  // Prior to a call to buildLinkZero the stoichiometry matrix mStoi must
  // have been constructed.

  mRedStoi = mStoi;

  C_INT M = mRedStoi.numCols();
  C_INT N = mRedStoi.numRows();
  C_INT LDA = std::max<C_INT>(1, M);

  CVector< C_INT > JPVT(N);
  JPVT = 0;

  unsigned C_INT32 Dim = std::min(M, N);

  if (Dim == 0)
    {
      unsigned C_INT32 i;
      mRowLU.resize(N);

      for (i = 0; i < N; i++)
        mRowLU[i] = i;

      mNumMetabolitesIndependent = 0;
      mL.resize(N - 0, 0);

      return;
    }

  CVector< C_FLOAT64 > TAU(Dim);

  CVector< C_FLOAT64 > WORK(1);
  C_INT LWORK = -1;
  C_INT INFO;

  // QR factorization of the stoichimetry matrix
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

#ifdef DEBUG_MATRIX
  DebugFile << CTransposeView< CMatrix< C_FLOAT64 > >(mRedStoi) << std::endl;
#endif

  dgeqp3_(&M, &N, mRedStoi.array(), &LDA,
          JPVT.array(), TAU.array(), WORK.array(), &LWORK, &INFO);
  if (INFO < 0) fatalError();

  LWORK = WORK[0];
  WORK.resize(LWORK);

  dgeqp3_(&M, &N, mRedStoi.array(), &LDA,
          JPVT.array(), TAU.array(), WORK.array(), &LWORK, &INFO);
  if (INFO < 0) fatalError();

  unsigned C_INT32 i;
  mRowLU.resize(N);
  for (i = 0; i < N; i++)
    mRowLU[i] = JPVT[i] - 1;

#ifdef DEBUG_MATRIX
  DebugFile << "QR Factorization:" << std::endl;
  DebugFile << "Row permutation:\t" << mRowLU << std::endl;
  DebugFile << CTransposeView< CMatrix< C_FLOAT64 > >(mRedStoi) << std::endl;
#endif

  C_INT independent = 0;
  while (independent < Dim &&
         fabs(mRedStoi(independent, independent)) > 100 * DBL_EPSILON) independent++;

  // Resize mL
  mNumMetabolitesIndependent = independent;
  mL.resize(N - independent, independent);
  if (N == independent || independent == 0) return;

  /* to take care of differences between fortran's and c's memory  acces,
     we need to take the transpose, i.e.,the upper triangular */
  char cL = 'U';
  char cU = 'N'; /* 1 in the diaogonal of R */

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
  dtrtri_(&cL, &cU, &independent, mRedStoi.array(), &LDA, &INFO);
  if (INFO < 0) fatalError();

#ifdef DEBUG_MATRIX
  DebugFile << "Invert R_1,1:" << std::endl;
  DebugFile << CTransposeView< CMatrix< C_FLOAT64 > >(mRedStoi) << std::endl;
#endif

  unsigned C_INT32 j, k;

  // Compute Link_0 = inverse(R_1,1) * R_1,2
  // :TODO: Use dgemm
  C_FLOAT64 * pTmp1 = &mL(0, 0);
  C_FLOAT64 * pTmp2;
  C_FLOAT64 * pTmp3;

  for (j = 0; j < N - independent; j++)
    for (i = 0; i < independent; i++, pTmp1++)
      {
        pTmp2 = &mRedStoi(j + independent, i);
        pTmp3 = &mRedStoi(i, i);

        // assert(&mL(j, i) == pTmp3);
        *pTmp1 = 0.0;

        for (k = i; k < independent; k++, pTmp2++, pTmp3 += M)
          {
            // assert(&mRedStoi(j + independent, k) == pTmp2);
            // assert(&mRedStoi(k, i) == pTmp3);

            *pTmp1 += *pTmp3 * *pTmp2;
          }

        if (fabs(*pTmp1) < 100 * DBL_EPSILON) *pTmp1 = 0.0;
      }

#ifdef DEBUG_MATRIX
  DebugFile << "Link Zero Matrix:" << std::endl;
  DebugFile << mL << std::endl;
#endif // DEBUG_MATRIX

  return;
}

bool CModel::isAutonomous() const
  {
    const CKinFunction * pFunction;

    std::vector< CReaction * >::const_iterator it = getReactions().begin();
    std::vector< CReaction * >::const_iterator end = getReactions().end();

    for (; it != end; ++it)
      if ((pFunction =
             dynamic_cast<const CKinFunction * >((*it)->getFunction())) != NULL &&
          pFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::TIME))
        {
          return false;
        }

    return true;
  }
