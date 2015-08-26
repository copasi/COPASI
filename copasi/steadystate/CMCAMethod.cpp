// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <cmath>
#include <limits>

#include "copasi.h"
#include "CMCAMethod.h"
#include "CMCAProblem.h"
#include "CSteadyStateTask.h"
#include "model/CModel.h"
#include "math/CMathContainer.h"
#include "utilities/CReadConfig.h"
#include "utilities/utility.h"
#include "utilities/CLinkMatrix.h"

#include "lapack/blaswrap.h"
#include "lapack/lapackwrap.h"

//TODO: put all matrix resizing and annotations creation in one place, so
// that it has to be done only once if several MCA are calculated (e.g. in a scan)

/**
 * Default constructor
 */
CMCAMethod::CMCAMethod(const CCopasiContainer * pParent,
                       const CTaskEnum::Method & methodType,
                       const CTaskEnum::Task & taskType):
  CCopasiMethod(pParent, methodType, taskType),
  mpUseReeder(NULL),
  mpUseSmallbone(NULL),
  mFactor(1.0e-9),
  mSteadyStateResolution(1.0e-9),
  mSSStatus(CSteadyStateMethod::notFound),
  mpSteadyStateTask(NULL),
  mLinkZero(),
  mReducedStoichiometry(),
  mElasticityDependencies()
{
  initializeParameter();
  initObjects();
}

CMCAMethod::CMCAMethod(const CMCAMethod & src,
                       const CCopasiContainer * pParent):
  CCopasiMethod(src, pParent),
  mpUseReeder(NULL),
  mpUseSmallbone(NULL),
  mFactor(src.mFactor),
  mSteadyStateResolution(src.mSteadyStateResolution),
  mSSStatus(CSteadyStateMethod::notFound),
  mpSteadyStateTask(NULL),
  mLinkZero(src.mLinkZero),
  mReducedStoichiometry(src.mReducedStoichiometry),
  mElasticityDependencies(src.mElasticityDependencies)
{
  initializeParameter();
  initObjects();
}

void CMCAMethod::initObjects()
{
  CArrayAnnotation *
  tmp = new CArrayAnnotation("Unscaled elasticities", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mUnscaledElasticities), true);
  tmp->setMode(CArrayAnnotation::VECTOR);
  tmp->setDescription("Unscaled elasticity matrix");
  tmp->setDimensionDescription(0, "Reactions (reduced system)");
  tmp->setDimensionDescription(1, "Species (reduced system)");
  mUnscaledElasticitiesAnn = tmp;

  tmp = new CArrayAnnotation("Unscaled concentration control coefficients", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mUnscaledConcCC), true);
  tmp->setMode(CArrayAnnotation::VECTOR);
  tmp->setDescription("Unscaled concentration control coefficients");
  tmp->setDimensionDescription(0, "Species (reduced system)");
  tmp->setDimensionDescription(1, "Reactions (reduced system)");
  mUnscaledConcCCAnn = tmp;

  tmp = new CArrayAnnotation("Unscaled flux control coefficients", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mUnscaledFluxCC), true);
  tmp->setMode(CArrayAnnotation::VECTOR);
  tmp->setDescription("Unscaled flux control coefficients");
  tmp->setDimensionDescription(0, "Reactions (reduced system)");
  tmp->setDimensionDescription(1, "Reactions (reduced system)");
  mUnscaledFluxCCAnn = tmp;

  tmp = new CArrayAnnotation("Scaled elasticities", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mScaledElasticities), true);
  tmp->setMode(CArrayAnnotation::VECTOR);
  tmp->setDescription("Scaled elasticity matrix");
  tmp->setDimensionDescription(0, "Reactions (reduced system)");
  tmp->setDimensionDescription(1, "Species (reduced system)");
  mScaledElasticitiesAnn = tmp;

  tmp = new CArrayAnnotation("Scaled concentration control coefficients", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mScaledConcCC), true);
  tmp->setMode(CArrayAnnotation::VECTOR);
  tmp->setDescription("Scaled concentration control coefficients");
  tmp->setDimensionDescription(0, "Species (reduced system)");
  tmp->setDimensionDescription(1, "Reactions (reduced system)");
  mScaledConcCCAnn = tmp;

  tmp = new CArrayAnnotation("Scaled flux control coefficients", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mScaledFluxCC), true);
  tmp->setMode(CArrayAnnotation::VECTOR);
  tmp->setDescription("Scaled flux control coefficients");
  tmp->setDimensionDescription(0, "Reactions (reduced system)");
  tmp->setDimensionDescription(1, "Reactions (reduced system)");
  mScaledFluxCCAnn = tmp;
}

/**
 * Deconstructor
 */
CMCAMethod::~CMCAMethod()
{
  DESTRUCTOR_TRACE;
  //delSsipvt();
}

void CMCAMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Modulation Factor", CCopasiParameter::UDOUBLE, 1.0e-009);

  if ((pParm = getParameter("MCA.ModulationFactor")) != NULL)
    {
      setValue("Modulation Factor", *pParm->getValue().pUDOUBLE);
      removeParameter("MCA.ModulationFactor");
    }

  mpUseReeder = assertParameter("Use Reeder", CCopasiParameter::BOOL, true)->getValue().pBOOL;
  mpUseSmallbone = assertParameter("Use Smallbone", CCopasiParameter::BOOL, true)->getValue().pBOOL;
}

bool CMCAMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

void CMCAMethod::resizeAllMatrices()
{
  const CModel & Model = mpContainer->getModel();

  mUnscaledElasticities.resize(mpContainer->getReactions().size(),
                               mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies());
  mUnscaledElasticitiesAnn->resize();
  mUnscaledElasticitiesAnn->setCopasiVector(0, &Model.getReactions());
  mUnscaledElasticitiesAnn->setCopasiVector(1, &Model.getMetabolitesX());

  mUnscaledConcCC.resize(mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies(),
                         mpContainer->getReactions().size());
  mUnscaledConcCCAnn->resize();
  mUnscaledConcCCAnn->setCopasiVector(0, &Model.getMetabolitesX());
  mUnscaledConcCCAnn->setCopasiVector(1, &Model.getReactions());

  mUnscaledFluxCC.resize(mpContainer->getReactions().size(), mpContainer->getReactions().size());
  mUnscaledFluxCCAnn->resize();
  mUnscaledFluxCCAnn->setCopasiVector(0, &Model.getReactions());
  mUnscaledFluxCCAnn->setCopasiVector(1, &Model.getReactions());

  mScaledElasticities.resize(mUnscaledElasticities.numRows(), mUnscaledElasticities.numCols());
  mScaledElasticitiesAnn->resize();
  mScaledElasticitiesAnn->setCopasiVector(0, &Model.getReactions());
  mScaledElasticitiesAnn->setCopasiVector(1, &Model.getMetabolitesX());

  // Reactions are columns, species are rows
  mScaledConcCC.resize(mUnscaledConcCC.numRows(), mUnscaledConcCC.numCols());
  mScaledConcCCAnn->resize();
  mScaledConcCCAnn->setCopasiVector(0, &Model.getMetabolitesX());
  mScaledConcCCAnn->setCopasiVector(1, &Model.getReactions());

  // Reactions are columns and rows
  mScaledFluxCC.resize(mUnscaledFluxCC.numRows(), mUnscaledFluxCC.numCols());
  mScaledFluxCCAnn->resize();
  mScaledFluxCCAnn->setCopasiVector(0, &Model.getReactions());
  mScaledFluxCCAnn->setCopasiVector(1, &Model.getReactions());

  mElasticityDependencies.resize(mUnscaledElasticities.numRows(), mUnscaledElasticities.numCols());
}

//this calculates the elasticities as d(particle flux)/d(particle number)
//which is the same as d(flux of substance)/d(amount of substance)
void CMCAMethod::calculateUnscaledElasticities(C_FLOAT64 /* res */)
{
  // We need the number of metabolites determined by reactions.
  size_t numMetabs = mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies();
  size_t FirstReactionSpeciesIndex = mpContainer->getTimeIndex() + mpContainer->getCountODEs();
  size_t numReacs = mpContainer->getParticleFluxes().size();

  // Calculate the dependencies of the elasticities this is helpful for scaling to determine
  // whether 0/0 is 0 or NaN
  const CMathDependencyGraph & TransientDependencies = mpContainer->getTransientDependencies();

  CMathObject * pParticleFluxObject = mpContainer->getMathObject(mpContainer->getParticleFluxes().array());
  CMathObject * pParticleFluxObjectEnd = pParticleFluxObject + numReacs;
  CMathObject * pSpeciesObjectStart = mpContainer->getMathObject(mpContainer->getState(false).array()) + FirstReactionSpeciesIndex;
  CMathObject * pSpeciesObjectEnd = pSpeciesObjectStart + numMetabs;
  CMathObject * pSpeciesObject;

  bool * pElasticityDependency = mElasticityDependencies.array();

  for (; pParticleFluxObject != pParticleFluxObjectEnd; ++pParticleFluxObject)
    {
      for (pSpeciesObject = pSpeciesObjectStart; pSpeciesObject != pSpeciesObjectEnd; ++pSpeciesObject, ++pElasticityDependency)
        {
          *pElasticityDependency = TransientDependencies.dependsOn(pParticleFluxObject, CMath::Default, pSpeciesObject);
        }
    }

  // mUnscaledElasticities.resize(numReacs, numMetabs);
  C_FLOAT64 * pElasticity;
  C_FLOAT64 * pElasticityEnd = mUnscaledElasticities.array() + mUnscaledElasticities.size();

  C_FLOAT64 Store, InvDelta;
  C_FLOAT64 X1, X2;

  // Arrays to store function value
  CVector< C_FLOAT64 > Y1(numReacs);
  C_FLOAT64 * pY1;
  CVector< C_FLOAT64 > Y2(numReacs);
  C_FLOAT64 * pY2;
  const CVectorCore< C_FLOAT64 > & ParticleFluxes = mpContainer->getParticleFluxes();

  C_FLOAT64 * pSpecies = (C_FLOAT64 *) pSpeciesObjectStart->getValuePointer();
  C_FLOAT64 * pSpeciesEnd = pSpecies + numMetabs;

  // calculate elasticities
  for (size_t j = 0; pSpecies != pSpeciesEnd; ++pSpecies, ++j)
    {
      Store = *pSpecies;

      // We only need to make sure that we do not have an underflow problem
      if (fabs(Store) < 100 * std::numeric_limits< C_FLOAT64 >::min())
        {
          X1 = 0.0;

          if (Store < 0.0)
            X2 = -200.0 * std::numeric_limits< C_FLOAT64 >::min();
          else
            X2 = 200.0 * std::numeric_limits< C_FLOAT64 >::min();;
        }
      else
        {
          X1 = Store * (1.0 + mFactor);
          X2 = Store * (1.0 - mFactor);
        }

      InvDelta = 1.0 / (X1 - X2);

      // let's take X+dx
      *pSpecies = X1;
      mpContainer->updateSimulatedValues(false); // TODO test if true or false should be used.

      // get the fluxes
      Y1 = ParticleFluxes;

      // now X-dx
      *pSpecies = X2;
      mpContainer->updateSimulatedValues(false); // TODO test if true or false should be used.

      // get the fluxes
      Y2 = ParticleFluxes;

      // set column j of Dxv
      pElasticity = mUnscaledElasticities.array() + j;
      pY1 = Y1.array();
      pY2 = Y2.array();

      for (; pElasticity < pElasticityEnd; pElasticity += numMetabs, ++pY1, ++pY2)
        * pElasticity = (*pY1 - *pY2) * InvDelta;

      // restore the value of the species
      *pSpecies = Store;
    }

  // make sure the fluxes are correct afterwards (needed for scaling of the MCA results)
  mpContainer->updateSimulatedValues(false);
}

bool CMCAMethod::calculateUnscaledConcentrationCC()
{
  // Calculate RedStoi * mUnscaledElasticities;
  // Note the columns of mUnscaledElasticities must be reordered

  mLinkZero.doColumnPivot(mUnscaledElasticities);

  // Initialize the unscaled concentration control coefficients to 0.0
  mUnscaledConcCC = 0.0;

  // aux1 := mUnscaledElasticities * L
  CMatrix<C_FLOAT64> aux1;
  mLinkZero.rightMultiply(1.0, mUnscaledElasticities, aux1);

  // We can now undo the column pivoting
  mLinkZero.undoColumnPivot(mUnscaledElasticities);

  assert(mReducedStoichiometry.numCols() == aux1.numRows());

  // aux2 := RedStoi * aux1
  // DGEMM (TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC)
  // C := alpha A B + beta C
  CMatrix<C_FLOAT64> aux2(mReducedStoichiometry.numRows(), aux1.numCols());

  char TRANSA = 'N';
  char TRANSB = 'N';
  C_INT M = (C_INT) aux2.numCols(); /* LDA, LDC */
  C_INT N = (C_INT) aux2.numRows();
  C_INT K = (C_INT) mReducedStoichiometry.numCols();
  C_FLOAT64 Alpha = 1.0;
  C_INT LDA = (C_INT) aux1.numCols();
  C_INT LDB = (C_INT) mReducedStoichiometry.numCols();
  C_FLOAT64 Beta = 0.0;
  C_INT LDC = (C_INT) aux2.numCols();

  dgemm_(&TRANSA, &TRANSB, &M, &N, &K, &Alpha, aux1.array(), &LDA,
         mReducedStoichiometry.array(), &LDB, &Beta, aux2.array(), &LDC);

  // Invert aux2
  C_INT info;
  CVector<C_INT> Ipiv(M);

  // LU decomposition of aux2 (for inversion)
  dgetrf_(&M, &M, aux2.array(), &M, Ipiv.array(), &info);

  if (info != 0) return false;

  C_INT lwork = -1; // Instruct dgetri_ to determine work array size.
  CVector< C_FLOAT64 > work(1);

  dgetri_(&M, aux2.array(), &M, Ipiv.array(), work.array(), &lwork, &info);

  lwork = (C_INT) work[0];
  work.resize(lwork);

  // now invert aux2 (result in aux2)
  dgetri_(&M, aux2.array(), &M, Ipiv.array(), work.array(), &lwork, &info);

  if (info != 0) return false;

  // aux1 := -1.0 * aux2 * RedStoi

  aux1.resize(aux2.numRows(), mReducedStoichiometry.numCols());

  M = (C_INT) aux1.numCols();
  N = (C_INT) aux1.numRows();
  K = (C_INT) aux2.numCols();
  Alpha = -1.0;
  LDA = (C_INT) mReducedStoichiometry.numCols();
  LDB = (C_INT) aux2.numCols();
  Beta = 0.0;
  LDC = (C_INT) aux1.numCols();

  // DGEMM (TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC)
  // C := alpha A B + beta C
  dgemm_(&TRANSA, &TRANSB, &M, &N, &K, &Alpha, mReducedStoichiometry.array(), &LDA,
         aux2.array(), &LDB, &Beta, aux1.array(), &LDC);

  // mUnscaledConcCC := L * aux1
  mLinkZero.leftMultiply(aux1, mUnscaledConcCC);

  // We need to swap the rows since they are with respect to reordered stoichiometry .
  mLinkZero.undoRowPivot(mUnscaledConcCC);

  return true;
}

bool CMCAMethod::calculateUnscaledFluxCC(const bool & status)
{
  //size_t i, j, k;

  // mUnscaledFluxCC := I + mUnscaledElasticities * mUnscaledConcCC

  char UPLO = 'A';
  C_INT M = mUnscaledFluxCC.numRows();
  C_FLOAT64 Alpha = 0.0;
  C_FLOAT64 Beta = 1.0;

  // Initialize mUnscaledFluxCC to the identity matrix;
  dlaset_(&UPLO, &M, &M, &Alpha, &Beta, mUnscaledFluxCC.array(), &M);

  if (status)
    {
      char TRANSA = 'N';
      char TRANSB = 'N';
      M = (C_INT) mUnscaledFluxCC.numCols(); /* LDA, LDC */
      C_INT N = (C_INT) mUnscaledFluxCC.numRows();
      C_INT K = (C_INT) mUnscaledElasticities.numCols();

      C_INT LDA = (C_INT) mUnscaledConcCC.numCols();
      C_INT LDB = (C_INT) mUnscaledElasticities.numCols();
      C_INT LDC = (C_INT) mUnscaledFluxCC.numCols();

      Alpha = 1.0;
      Beta = 1.0;

      dgemm_(&TRANSA, &TRANSB, &M, &N, &K, &Alpha, mUnscaledConcCC.array(), &LDA,
             mUnscaledElasticities.array(), &LDB, &Beta, mUnscaledFluxCC.array(), &LDC);
    }

  return status;
}

bool CMCAMethod::scaleMCA(const bool & status, C_FLOAT64 res)
{
  // We need the number of metabolites determined by reactions.
  size_t numMetabs = mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies();
  size_t FirstReactionSpeciesIndex = mpContainer->getTimeIndex() + mpContainer->getCountODEs();
  size_t numReacs = mpContainer->getParticleFluxes().size();

  CMathObject * pSpeciesObjectStart = mpContainer->getMathObject(mpContainer->getState(false).array()) + FirstReactionSpeciesIndex;
  CMathObject * pSpeciesObjectEnd = pSpeciesObjectStart + numMetabs;
  CMathObject * pSpeciesObject;

  const C_FLOAT64 * pParticleFlux = mpContainer->getParticleFluxes().array();
  const C_FLOAT64 * pFlux = mpContainer->getFluxes().array();
  const C_FLOAT64 * pFluxEnd = pFlux + mpContainer->getFluxes().size();

  // Scale Elasticities
  C_FLOAT64 * pUnscaled;
  C_FLOAT64 * pScaled;
  bool * pElasticityDependency;

  size_t col = 0;

  // Reactions are rows, species are columns
  for (pSpeciesObject = pSpeciesObjectStart; pSpeciesObject != pSpeciesObjectEnd; ++pSpeciesObject, ++col)
    {
      C_FLOAT64 VolumeInv = 1.0 / *(C_FLOAT64 *)mpContainer->getCompartment(pSpeciesObject)->getValuePointer();

      for (pFlux = mpContainer->getFluxes().array(),
           pParticleFlux = mpContainer->getParticleFluxes().array(),
           pUnscaled = mUnscaledElasticities.array() + col,
           pScaled = mScaledElasticities.array() + col,
           pElasticityDependency = mElasticityDependencies.array() + col;
           pFlux != pFluxEnd;
           ++pFlux,
           ++pParticleFlux,
           pUnscaled += numMetabs,
           pScaled += numMetabs,
           pElasticityDependency += numMetabs)
        {
          if (!*pElasticityDependency)
            {
              *pScaled = 0.0;
            }
          else if (fabs(*pFlux) * VolumeInv >= res)
            {
              *pScaled = *pUnscaled **(C_FLOAT64 *)pSpeciesObject->getValuePointer() / *pParticleFlux;
            }
          else
            {
              *pScaled = (*pFlux < 0.0) ? - std::numeric_limits<C_FLOAT64>::infinity() : std::numeric_limits<C_FLOAT64>::infinity();
            }
        }
    }

  //if we are not in a steady state we cannot calculate CCs
  if (mSSStatus != CSteadyStateMethod::found ||
      !status)
    {
      mScaledConcCC = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
      mScaledFluxCC = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

      return false;
    }

  // Scale ConcCC
  // Reactions are columns, species are rows
  pUnscaled = mUnscaledConcCC.array();
  pScaled = mScaledConcCC.array();

  // In rare occasions the concentration might not be updated
  mpContainer->updateTransientDataValues();

  for (pSpeciesObject = pSpeciesObjectStart; pSpeciesObject != pSpeciesObjectEnd; ++pSpeciesObject)
    {
      C_FLOAT64 alt = fabs(*(C_FLOAT64 *)pSpeciesObject->getCorrespondingProperty()->getValuePointer());

      for (pFlux = mpContainer->getFluxes().array(),
           pParticleFlux = mpContainer->getParticleFluxes().array();
           pFlux != pFluxEnd;
           ++pFlux,
           ++pParticleFlux,
           ++pUnscaled,
           ++pScaled)
        {
          if (alt >= res)
            *pScaled = *pUnscaled **pParticleFlux / *(C_FLOAT64 *)pSpeciesObject->getValuePointer();
          else
            *pScaled = *pUnscaled * std::numeric_limits<C_FLOAT64>::infinity();
        }
    }

  const CMathReaction * pReaction = mpContainer->getReactions().array();

  pUnscaled = mUnscaledFluxCC.array();
  pScaled = mScaledFluxCC.array();

  for (pFlux = mpContainer->getFluxes().array(); pFlux != pFluxEnd; ++pFlux, ++pReaction)
    {
      CMathObject * pCompartment = mpContainer->getLargestReactionCompartment(pReaction);
      C_FLOAT64 Resolution = (pCompartment != NULL) ?  res **(C_FLOAT64*)pCompartment->getValuePointer() : res;

      C_FLOAT64 Scale = *pFlux;
      C_FLOAT64 tmp = 0.0;
      C_FLOAT64 eq = 0.0;

      // We use the summation theorem to verify the scaling
      C_FLOAT64 *pSum = pUnscaled;
      C_FLOAT64 *pSumEnd = pSum + mScaledFluxCC.numCols();

      const C_FLOAT64 * pColFlux = mpContainer->getFluxes().array();

      for (pColFlux = mpContainer->getFluxes().array(); pSum != pSumEnd; ++pColFlux, ++pSum)
        {
          tmp += *pSum **pColFlux;
          eq += fabs(*pSum);
        }

      eq /= mScaledFluxCC.numCols();

      if (fabs(tmp) < Resolution && eq >= Resolution)
        {
          Scale = std::numeric_limits< C_FLOAT64 >::infinity();
        }

      tmp = 0.0;

      for (pColFlux = mpContainer->getFluxes().array(); pColFlux != pFluxEnd; ++pColFlux, ++pUnscaled, ++pScaled)
        {
          // In the diagonal the scaling factors cancel.
          if (eq < res)
            {
              *pScaled = (pColFlux != pFlux) ? 0.0  : 1.0;
            }
          else if (pColFlux == pFlux)
            {
              *pScaled = *pUnscaled;
            }
          else if (fabs(Scale) >= res)
            {
              *pScaled = *pUnscaled **pColFlux / Scale;
            }
          else
            {
              CMathObject * pCompartmentCol = mpContainer->getLargestReactionCompartment(pReaction);
              C_FLOAT64 ScaleCol = (pCompartmentCol != NULL) ?
                                   fabs(*pColFlux / * (C_FLOAT64*)pCompartmentCol->getValuePointer()) :
                                   fabs(*pColFlux);

              if (fabs(ScaleCol) <= res)
                {
                  *pScaled = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
                }
              else
                {
                  *pScaled = (*pFlux < 0.0) ?
                             - std::numeric_limits<C_FLOAT64>::infinity() :
                             std::numeric_limits<C_FLOAT64>::infinity();
                }
            }

          tmp += *pScaled;
        }
    }

  return true;
}

bool CMCAMethod::checkSummationTheorems(const C_FLOAT64 & resolution)
{
  bool success = true;

  C_FLOAT64 * pScaled = mScaledConcCC.array();
  C_FLOAT64 * pScaledRowEnd = pScaled + mScaledConcCC.numCols();
  C_FLOAT64 * pScaledEnd = pScaled + mScaledConcCC.size();

  CVector< C_FLOAT64 > Sum(mScaledConcCC.numRows());
  CVector< C_FLOAT64 > Max(mScaledConcCC.numRows());
  CVector< C_FLOAT64 > Error(mScaledConcCC.numRows());
  Sum = 0.0;
  Max = 0.0;
  C_FLOAT64 * pSum = Sum.array();
  C_FLOAT64 * pMax = Max.array();
  C_FLOAT64 * pError = Error.array();

  for (; pScaled != pScaledEnd; pScaledRowEnd += mScaledConcCC.numCols(), ++pSum, ++pMax, ++pError)
    {
      for (; pScaled != pScaledRowEnd; ++pScaled)
        {
          success &= !isnan(*pScaled);

          *pSum += *pScaled;
          *pMax = std::max(*pMax, fabs(*pScaled));
        }

      *pError = (*pMax > 100.0 * std::numeric_limits< C_FLOAT64 >::min()) ? fabs(*pSum) / *pMax : 0.0;
      success &= *pError < resolution;
    }

  pScaled = mScaledFluxCC.array();
  pScaledRowEnd = pScaled + mScaledFluxCC.numCols();
  pScaledEnd = pScaled + mScaledFluxCC.size();

  Sum.resize(mScaledFluxCC.numRows());
  Max.resize(mScaledFluxCC.numRows());
  Error.resize(mScaledFluxCC.numRows());
  Sum = 0.0;
  Max = 0.0;

  pSum = Sum.array();
  pMax = Max.array();
  pError = Error.array();

  for (; pScaled != pScaledEnd; pScaledRowEnd += mScaledConcCC.numCols(), ++pSum, ++pMax, ++pError)
    {
      for (; pScaled != pScaledRowEnd; ++pScaled)
        {
          success &= !isnan(*pScaled);

          *pSum += *pScaled;
          *pMax = std::max(*pMax, fabs(*pScaled));
        }

      *pError = (*pMax > 100.0 * std::numeric_limits< C_FLOAT64 >::min()) ? fabs(1.0 - *pSum) / *pMax : 0.0;
      success &= *pError < resolution;
    }

  return success;
}

/**
 * the steady state MCA entry point
 * @param ss_solution refer to steady-state solution
 * @param refer to the resolution
 */
bool CMCAMethod::CalculateMCA(C_FLOAT64 res)
{
  bool success = true;
  bool SummationTheoremsOK = false;

  calculateUnscaledElasticities(res);

  if (mSSStatus == CSteadyStateMethod::found)
    {
      if (*mpUseReeder)
        {
          createLinkMatrix();
          success &= calculateUnscaledConcentrationCC();
          success &= calculateUnscaledFluxCC(success);
          success &= scaleMCA(success, res);
          SummationTheoremsOK = checkSummationTheorems(res);
        }

      if (*mpUseSmallbone && !SummationTheoremsOK)
        {
          success = true;

          createLinkMatrix(true);
          success &= calculateUnscaledConcentrationCC();
          success &= calculateUnscaledFluxCC(success);
          success &= scaleMCA(success, res);
          SummationTheoremsOK = checkSummationTheorems(res);
        }

      if (!SummationTheoremsOK)
        {
          CCopasiMessage(CCopasiMessage::WARNING, MCMCA + 1);
        }
    }
  else
    {
      mUnscaledConcCC = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
      mUnscaledFluxCC = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
    }

  return success;
}

bool CMCAMethod::createLinkMatrix(const bool & useSmallbone)
{
  if (mpContainer == NULL ||
      mpSteadyStateTask == NULL)
    {
      return false;
    }

  if (useSmallbone)
    {
      mLinkZero.build(mpSteadyStateTask->getJacobian(), mpContainer->getModel().getNumIndependentReactionMetabs());
      mReducedStoichiometry = mpContainer->getModel().getStoi();
      mLinkZero.doRowPivot(mReducedStoichiometry);
      mReducedStoichiometry.resize(mLinkZero.getNumIndependent(), mReducedStoichiometry.numCols(), true);
    }
  else
    {
      mLinkZero = mpContainer->getModel().getL0();
      mReducedStoichiometry = mpContainer->getModel().getRedStoi();
    }

  return true;
}

/**
 * Read SSMCAUnscaled from configuration file
 */
C_INT32 CMCAMethod::load(CReadConfig & configBuffer)
{
  C_INT32 Fail = 0;

  if ((Fail = configBuffer.getVariable("SSMCAUnscaled", "C_INT16",
                                       (void *) & mSSReder,
                                       CReadConfig::LOOP)))
    return Fail;

  return Fail;
}

bool CMCAMethod::process()
{
  // check if current state is a steady state
  // if not, calculate TimeMCA only
  if (1 /*mIsSteadyState*/)
    {
      CalculateMCA(mSteadyStateResolution);
    }
  else
    {
      //   CalculateTimeMCA(mSteadyStateResolution);
    }

  return true;
}

void CMCAMethod::setSteadyStateTask(CSteadyStateTask * pSteadyStateTask)
{
  mpSteadyStateTask = pSteadyStateTask;

  if (mpSteadyStateTask != NULL)
    {
      mSSStatus = mpSteadyStateTask->getResult();
    }
  else
    {
      mSSStatus = CSteadyStateMethod::notFound;
    }
}

void CMCAMethod::setFactor(C_FLOAT64 factor)
{
  this->mFactor = factor;
}

void CMCAMethod::setSteadyStateResolution(C_FLOAT64 resolution)
{
  this->mSteadyStateResolution = resolution;
}

//virtual
bool CMCAMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CMCAProblem * pP = dynamic_cast<const CMCAProblem *>(pProblem);

  if (!pP)
    {
      //not a TrajectoryProblem
      CCopasiMessage(CCopasiMessage::ERROR, "Problem is not an MCA problem.");
      return false;
    }

  if (mpContainer->getCountODEs() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "MCA is not applicable for a system with explicit ODEs.");
      return false;
    }

  // Check if the model has a changing compartment size
  CCopasiVector< CCompartment >::const_iterator it = mpContainer->getModel().getCompartments().begin();
  CCopasiVector< CCompartment >::const_iterator end = mpContainer->getModel().getCompartments().end();
  CObjectInterface::ObjectSet Requested;

  for (; it != end; ++it)
    {
      Requested.insert(mpContainer->getMathObject((*it)->getValueReference()));
    }

  CObjectInterface::UpdateSequence UpdateSequence;

  mpContainer->getTransientDependencies().getUpdateSequence(UpdateSequence, CMath::Default, mpContainer->getStateObjects(false), Requested);

  if (Requested.size() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "MCA is not applicable for a system with changing volumes.");
      return false;
    }

  if (!*mpUseReeder && !*mpUseSmallbone)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "At least one of the algorithm Reeder or Smallbone must be selected.");
      return false;
    }

  return true;
}
