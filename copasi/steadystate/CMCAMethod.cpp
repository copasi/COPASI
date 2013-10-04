// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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
#include "utilities/CReadConfig.h"
#include "utilities/utility.h"
#include "utilities/CLinkMatrix.h"

#include "lapack/blaswrap.h"
#include "lapack/lapackwrap.h"

//TODO: put all matrix resizing and annotations creation in one place, so
// that it has to be done only once if several MCA are calculated (e.g. in a scan)

// static
CMCAMethod * CMCAMethod::createMethod(CCopasiMethod::SubType /* subType */)
{
  return new CMCAMethod();
}

/**
 * Default constructor
 */
CMCAMethod::CMCAMethod(const CCopasiContainer* pParent):
  CCopasiMethod(CCopasiTask::mca, CCopasiMethod::mcaMethodReder, pParent),
  mpModel(NULL),
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
  mpModel(NULL),
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
}

bool CMCAMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

void CMCAMethod::resizeAllMatrices()
{
  if (!mpModel) return;

  mUnscaledElasticities.resize(mpModel->getTotSteps(),
                               mpModel->getNumIndependentReactionMetabs() + mpModel->getNumDependentReactionMetabs());
  mUnscaledElasticitiesAnn->resize();
  mUnscaledElasticitiesAnn->setCopasiVector(0, &mpModel->getReactions());
  mUnscaledElasticitiesAnn->setCopasiVector(1, &mpModel->getMetabolitesX());

  mUnscaledConcCC.resize(mpModel->getNumIndependentReactionMetabs() + mpModel->getNumDependentReactionMetabs(),
                         mpModel->getTotSteps());
  mUnscaledConcCCAnn->resize();
  mUnscaledConcCCAnn->setCopasiVector(0, &mpModel->getMetabolitesX());
  mUnscaledConcCCAnn->setCopasiVector(1, &mpModel->getReactions());

  mUnscaledFluxCC.resize(mpModel->getTotSteps(), mpModel->getTotSteps());
  mUnscaledFluxCCAnn->resize();
  mUnscaledFluxCCAnn->setCopasiVector(0, &mpModel->getReactions());
  mUnscaledFluxCCAnn->setCopasiVector(1, &mpModel->getReactions());

  mScaledElasticities.resize(mUnscaledElasticities.numRows(), mUnscaledElasticities.numCols());
  mScaledElasticitiesAnn->resize();
  mScaledElasticitiesAnn->setCopasiVector(0, &mpModel->getReactions());
  mScaledElasticitiesAnn->setCopasiVector(1, &mpModel->getMetabolitesX());

  // Reactions are columns, species are rows
  mScaledConcCC.resize(mUnscaledConcCC.numRows(), mUnscaledConcCC.numCols());
  mScaledConcCCAnn->resize();
  mScaledConcCCAnn->setCopasiVector(0, &mpModel->getMetabolitesX());
  mScaledConcCCAnn->setCopasiVector(1, &mpModel->getReactions());

  // Reactions are columns and rows
  mScaledFluxCC.resize(mUnscaledFluxCC.numRows(), mUnscaledFluxCC.numCols());
  mScaledFluxCCAnn->resize();
  mScaledFluxCCAnn->setCopasiVector(0, &mpModel->getReactions());
  mScaledFluxCCAnn->setCopasiVector(1, &mpModel->getReactions());

  mElasticityDependencies.resize(mUnscaledElasticities.numRows(), mUnscaledElasticities.numCols());
}

//this calculates the elasticities as d(particle flux)/d(particle number)
//which is the same as d(flux of substance)/d(amount of substance)
void CMCAMethod::calculateUnscaledElasticities(C_FLOAT64 /* res */)
{
  assert(mpModel);

  // We need the number of metabolites determined by reactions.
  size_t numMetabs =
    mpModel->getNumIndependentReactionMetabs() + mpModel->getNumDependentReactionMetabs();

  CCopasiVector< CMetab >::iterator itSpecies = mpModel->getMetabolitesX().begin();
  CCopasiVector< CMetab >::iterator endSpecies = itSpecies + numMetabs;

  // Calculate the dependencies of the elasticities this is helpful for scaling to determine
  // whether 0/0 is 0 or NaN

  bool * pElasticityDependency = mElasticityDependencies.array();
  CCopasiVector< CReaction >::const_iterator itReac = mpModel->getReactions().begin();
  CCopasiVector< CReaction >::const_iterator endReac = mpModel->getReactions().end();

  for (; itReac != endReac; ++itReac)
    {
      CCopasiObject::DataObjectSet ReactionDependencies;
      (*itReac)->getParticleFluxReference()->getAllDependencies(ReactionDependencies, DataObjectSet());

      itSpecies = mpModel->getMetabolitesX().begin();

      for (; itSpecies != endSpecies; ++itSpecies, ++pElasticityDependency)
        {
          *pElasticityDependency = (ReactionDependencies.find((*itSpecies)->getValueReference()) != ReactionDependencies.end());
        }
    }

  std::cout << mElasticityDependencies << std::endl;

  const CVector< C_FLOAT64 > & ParticleFlux = mpModel->getParticleFlux();

  //   mUnscaledElasticities.resize(numReacs, numMetabs);
  C_FLOAT64 * pElasticity;
  C_FLOAT64 * pElasticityEnd = mUnscaledElasticities.array() + mUnscaledElasticities.size();

  C_FLOAT64 Store, InvDelta;
  C_FLOAT64 X1, X2;

  // Arrays to store function value
  size_t numReacs = mpModel->getReactions().size();
  CVector< C_FLOAT64 > Y1(numReacs);
  C_FLOAT64 * pY1;
  CVector< C_FLOAT64 > Y2(numReacs);
  C_FLOAT64 * pY2;

  // calculate elasticities
  itSpecies = mpModel->getMetabolitesX().begin();

  for (size_t j = 0; itSpecies != endSpecies; ++itSpecies, ++j)
    {
      Store = (*itSpecies)->getValue();

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
      (*itSpecies)->setValue(X1);
      mpModel->updateSimulatedValues(false); // TODO test if true or false should be used.

      // get the fluxes
      Y1 = ParticleFlux;

      // now X-dx
      (*itSpecies)->setValue(X2);
      mpModel->updateSimulatedValues(false); // TODO test if true or false should be used.

      // get the fluxes
      Y2 = ParticleFlux;

      // set column j of Dxv
      pElasticity = mUnscaledElasticities.array() + j;
      pY1 = Y1.array();
      pY2 = Y2.array();

      for (; pElasticity < pElasticityEnd; pElasticity += numMetabs, ++pY1, ++pY2)
        * pElasticity = (*pY1 - *pY2) * InvDelta;

      // restore the value of the species
      (*itSpecies)->setValue(Store);
    }

  std::cout << mUnscaledElasticities << std::endl;

  // make sure the fluxes are correct afterwards (needed for scaling of the MCA results)
  mpModel->updateSimulatedValues(false);
}

int CMCAMethod::calculateUnscaledConcentrationCC()
{
  assert(mpModel);

  // TODO CRITICAL We must not use the reduced stoichiometry matrix
  // Instead use N * mLinkZero
  CMatrix< C_FLOAT64 > RedStoi = mpModel->getStoi();
  mLinkZero.applyRowPivot(RedStoi);
  RedStoi.resize(mLinkZero.getNumIndependent(), RedStoi.numCols(), true);

  // Calculate RedStoi * mUnscaledElasticities;
  // Note the columns of mUnscaledElasticities must be reordered
  mLinkZero.applyColumnPivot(mUnscaledElasticities);
  std::cout << mUnscaledElasticities << std::endl;

  // Initialize the unscaled concentration control coefficients to 0.0
  mUnscaledConcCC = 0.0;

  // aux1 := mUnscaledElasticities * L
  CMatrix<C_FLOAT64> aux1;
  mLinkZero.rightMultiply(1.0, mUnscaledElasticities, aux1);
  std::cout << aux1 << std::endl;

  assert(RedStoi.numCols() == aux1.numRows());

  // aux2 := RedStoi * aux1
  // DGEMM (TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC)
  // C := alpha A B + beta C
  CMatrix<C_FLOAT64> aux2(RedStoi.numRows(), aux1.numCols());

  char TRANSA = 'N';
  char TRANSB = 'N';
  C_INT M = (C_INT) aux2.numRows(); /* LDA, LDC */
  C_INT N = (C_INT) aux2.numCols();
  C_INT K = (C_INT) aux1.numRows();
  C_FLOAT64 Alpha = 1.0;
  C_INT LDA = (C_INT) aux1.numCols();
  C_INT LDB = (C_INT) RedStoi.numCols();
  C_FLOAT64 Beta = 0.0;
  C_INT LDC = (C_INT) aux2.numCols();

  dgemm_(&TRANSA, &TRANSB, &M, &N, &K, &Alpha, aux1.array(), &LDA,
         RedStoi.array(), &LDB, &Beta, aux2.array(), &LDC);
  std::cout << aux2 << std::endl;

  // Invert aux2
  C_INT info;
  CVector<C_INT> Ipiv(M);

  // LU decomposition of aux2 (for inversion)
  dgetrf_(&M, &M, aux2.array(), &M, Ipiv.array(), &info);

  if (info != 0) return MCA_SINGULAR;

  C_INT lwork = -1; // Instruct dgetri_ to determine work array size.
  CVector< C_FLOAT64 > work(1);

  dgetri_(&M, aux2.array(), &M, Ipiv.array(), work.array(), &lwork, &info);

  lwork = (C_INT) work[0];
  work.resize(lwork);

  // now invert aux2 (result in aux2)
  dgetri_(&M, aux2.array(), &M, Ipiv.array(), work.array(), &lwork, &info);

  if (info != 0) return MCA_SINGULAR;

  std::cout << aux2 << std::endl;

  // mUnscaledConcCC := -1.0 * L * aux2
  mLinkZero.leftMultiply(-1.0, aux2, mUnscaledConcCC);
  std::cout << mUnscaledConcCC << std::endl;

  // M = independent species, K = dependent species
  aux1.resize(M + K, M);
  aux1 = 0.0;

  C_INT i, j, k;

#ifdef XXXX

  // aux1 = - L * aux2 = (I, L0')' * aux2 = -(aux2, (L0 * aux2)')'
  // Implementation without dgemm to avoid column swaps in aux1 and aux2
  for (i = 0; i < M + K; ++i)
    {
      const size_t & pi = p[i];

      for (j = 0; j < M; ++j)
        {

          if (pi < (size_t)M)
            {
              aux1(pi, j) = - aux2(pi, j);
              continue;
            }

          C_FLOAT64 & a = aux1(pi, j);
          a = 0.0;

          for (k = 0; k < M; ++k)
            {
              a -= L0(i - M, k) * aux2(k, j);
            }
        }
    }

#endif // XXXX

  // mGamma = aux1 * RedStoi
  // :TODO: use dgemm

  // M = independent species, K = dependent species
  //  mUnscaledConcCC.resize(M + K, N);
  for (i = 0; i < M + K; i++)
    for (j = 0; j < N; j++)
      {
        C_FLOAT64 & c = mUnscaledConcCC(i, j);

        for (k = 0; k < M; k++)
          c += aux1(i, k) * RedStoi(k, j);
      }

  //update annotations
  //   mUnscaledConcCCAnn->resize();
  //   mUnscaledConcCCAnn->setCopasiVector(0, &mpModel->getMetabolitesX());
  //   mUnscaledConcCCAnn->setCopasiVector(1, &mpModel->getReactions());

  return MCA_OK;
}

void CMCAMethod::calculateUnscaledFluxCC(int condition)
{
  assert(mpModel);
  size_t i, j, k;

  //  mUnscaledFluxCC.resize(mpModel->getTotSteps(), mpModel->getTotSteps());

  for (i = 0; i < mUnscaledFluxCC.numRows(); i++)
    for (j = 0; j < mUnscaledFluxCC.numCols(); j++)
      mUnscaledFluxCC(i, j) = (i == j) ? 1.0 : 0.0;

  if (condition != MCA_SINGULAR)
    {
      // unscaledFluxCC = I + unscaledElasticities * unscaledConcCC
      for (i = 0; i < mUnscaledFluxCC.numRows(); i++)
        for (j = 0; j < mUnscaledFluxCC.numCols(); j++)
          {
            C_FLOAT64 & c = mUnscaledFluxCC(i, j);

            for (k = 0; k < mUnscaledConcCC.numRows(); k++)
              c += mUnscaledElasticities(i, k) * mUnscaledConcCC(k, j);
          }
    }

  //update annotations
  /*  mUnscaledFluxCCAnn->resize();
    mUnscaledFluxCCAnn->setCopasiVector(0, &mpModel->getReactions());
    mUnscaledFluxCCAnn->setCopasiVector(1, &mpModel->getReactions());*/
}

void CMCAMethod::scaleMCA(int condition, C_FLOAT64 res)
{
  assert(mpModel);
  // The number of metabs determined by reaction.
  size_t numSpeciesReaction =
    mpModel->getNumIndependentReactionMetabs() + mpModel->getNumDependentReactionMetabs();
  CCopasiVector< CMetab > & metabs = mpModel->getMetabolitesX();
  CCopasiVector< CMetab >::const_iterator itSpecies = metabs.begin();
  CCopasiVector< CMetab >::const_iterator endSpecies = itSpecies + numSpeciesReaction;

  CCopasiVector< CReaction > & reacs = mpModel->getReactions();
  CCopasiVector< CReaction >::const_iterator itReaction;
  CCopasiVector< CReaction >::const_iterator endReaction = reacs.end();

  size_t col;

  // Scale Elasticities
  //  mScaledElasticities.resize(mUnscaledElasticities.numRows(), mUnscaledElasticities.numCols());

  C_FLOAT64 * pUnscaled;
  C_FLOAT64 * pScaled;
  bool * pElasticityDependency;

  // Reactions are rows, species are columns
  for (col = 0; itSpecies != endSpecies; ++itSpecies, col++)
    {
      C_FLOAT64 VolumeInv = 1.0 / (*itSpecies)->getCompartment()->getValue();
      C_FLOAT64 Number = (*itSpecies)->getValue();

      for (itReaction = reacs.begin(),
           pUnscaled = mUnscaledElasticities.array() + col,
           pScaled = mScaledElasticities.array() + col,
           pElasticityDependency = mElasticityDependencies.array() + col;
           itReaction != endReaction;
           ++itReaction,
           pUnscaled += numSpeciesReaction,
           pScaled += numSpeciesReaction,
           pElasticityDependency += numSpeciesReaction)
        {
          if (!*pElasticityDependency)
            {
              *pScaled = 0.0;
            }
          else if (fabs((*itReaction)->getFlux() * VolumeInv) >= res)
            {
              *pScaled = *pUnscaled * Number / (*itReaction)->getParticleFlux();
            }
          else
            {
              *pScaled = (((*itReaction)->getFlux() < 0.0) ? - std::numeric_limits<C_FLOAT64>::infinity() : std::numeric_limits<C_FLOAT64>::infinity());
            }
        }
    }

  //update annotated matrix
  //   mScaledElasticitiesAnn->resize();
  //   mScaledElasticitiesAnn->setCopasiVector(0, &reacs);
  //   mScaledElasticitiesAnn->setCopasiVector(1, &metabs);

  //if we are not in a steady state we cannot calculate CCs
  if (mSSStatus != CSteadyStateMethod::found ||
      condition != MCA_OK)
    {
      mScaledConcCC = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
      mScaledFluxCC = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

      return;
    }

  // Scale ConcCC
  // Reactions are columns, species are rows
  //   mScaledConcCC.resize(mUnscaledConcCC.numRows(), mUnscaledConcCC.numCols());

  itSpecies = metabs.begin();
  pUnscaled = mUnscaledConcCC.array();
  pScaled = mScaledConcCC.array();

  for (; itSpecies != endSpecies; ++itSpecies)
    {
      C_FLOAT64 alt = fabs((*itSpecies)->getConcentration());

      for (itReaction = reacs.begin(); itReaction != endReaction; ++itReaction, ++pUnscaled, ++pScaled)
        {
          if (alt >= res)
            *pScaled =
              *pUnscaled * (*itReaction)->getParticleFlux() / (*itSpecies)->getValue();
          else
            *pScaled = std::numeric_limits<C_FLOAT64>::infinity();
        }
    }

  CCopasiVector< CReaction >::const_iterator itReactionCol;
  itReaction = reacs.begin();
  pUnscaled = mUnscaledFluxCC.array();
  pScaled = mScaledFluxCC.array();

  for (; itReaction != endReaction; ++itReaction)
    {
      const CCompartment * pCompartment = (*itReaction)->getLargestCompartment();
      C_FLOAT64 Scale = (pCompartment == NULL) ?
                        fabs((*itReaction)->getFlux()) :
                        fabs((*itReaction)->getFlux() / pCompartment->getValue());

      if (fabs(Scale) < res)
        {
          Scale = 0.0;

          // We use the summation theorem to scale
          C_FLOAT64 *pSum = pUnscaled;
          C_FLOAT64 *pSumEnd = pSum + mScaledFluxCC.numCols();

          for (itReactionCol = reacs.begin(); pSum != pSumEnd; ++itReactionCol, ++pSum)
            {
              Scale += *pSum * (*itReactionCol)->getFlux();
            }
        }

      if (fabs(Scale) < res)
        {
          Scale = std::numeric_limits< C_FLOAT64 >::infinity();
        }

      for (itReactionCol = reacs.begin(); itReactionCol != endReaction; ++itReactionCol, ++pUnscaled, ++pScaled)
        {
          // In the diagonal the scaling factors cancel.
          if (itReactionCol == itReaction)
            {
              *pScaled = *pUnscaled;
            }
          else if (fabs(Scale) >= res)
            {
              *pScaled = *pUnscaled * (*itReactionCol)->getFlux() / Scale;
            }
          else
            {
              const CCompartment * pCompartmentCol = (*itReactionCol)->getLargestCompartment();
              C_FLOAT64 ScaleCol = (pCompartmentCol == NULL) ?
                                   fabs((*itReactionCol)->getFlux()) :
                                   fabs((*itReactionCol)->getFlux() / pCompartmentCol->getValue());

              if (fabs(ScaleCol) <= res)
                {
                  *pScaled = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
                }
              else
                {
                  *pScaled = (((*itReaction)->getFlux() < 0.0) ?
                              - std::numeric_limits<C_FLOAT64>::infinity() :
                              std::numeric_limits<C_FLOAT64>::infinity());
                }
            }
        }
    }
}

/**
 * Set the Model
 */
void CMCAMethod::setModel(CModel* model)
{
  mpModel = model;
}

/**
 * the steady state MCA entry point
 * @param ss_solution refer to steady-state solution
 * @param refer to the resolution
 */
int CMCAMethod::CalculateMCA(C_FLOAT64 res)
{
  assert(mpModel);
  int ret = MCA_OK;

  calculateUnscaledElasticities(res);

  if (mSSStatus == CSteadyStateMethod::found)
    {
      createLinkMatrix();

      ret = calculateUnscaledConcentrationCC();
      calculateUnscaledFluxCC(ret);
    }
  else
    {
      mUnscaledConcCC = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
      mUnscaledFluxCC = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
    }

  scaleMCA(ret, res);

  return ret;
}

bool CMCAMethod::createLinkMatrix()
{
  if (mpModel == NULL ||
      mpSteadyStateTask == NULL)
    {
      return false;
    }

  std::cout << mpSteadyStateTask->getJacobian() << std::endl;

  mLinkZero.build(mpSteadyStateTask->getJacobian());

  mReducedStoichiometry = mpModel->getStoi();
  mLinkZero.applyRowPivot(mReducedStoichiometry);
  mReducedStoichiometry.resize(mLinkZero.getNumIndependent(), mReducedStoichiometry.numCols(), true);

  std::cout << CLinkMatrixView(mLinkZero) << std::endl;

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

const CModel* CMCAMethod::getModel() const
{
  return this->mpModel;
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

  CModel * pModel = pP->getModel();

  if (pModel == NULL)
    return false;

  // Check if the model contains an ODE.
  size_t NumODE =
    pModel->getStateTemplate().endIndependent() - pModel->getStateTemplate().beginIndependent();

  if (pModel->getNumIndependentReactionMetabs() < NumODE)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "MCA is not applicable for a system with explicit ODEs.");
      return false;
    }

  // Check if the model has a compartment with an assignment
  CCopasiVector< CCompartment >::const_iterator it = pModel->getCompartments().begin();
  CCopasiVector< CCompartment >::const_iterator end = pModel->getCompartments().end();

  for (; it != end; ++it)
    if ((*it)->getStatus() == CModelEntity::ASSIGNMENT)
      {
        CCopasiMessage(CCopasiMessage::ERROR, "MCA is not applicable for a system with changing volumes.");
        return false;
      }

  return true;
}
