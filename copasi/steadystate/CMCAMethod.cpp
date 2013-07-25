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

#include "blaswrap.h"
#include "clapackwrap.h"

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
  mReducedStoichiometry()
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
  mReducedStoichiometry(src.mReducedStoichiometry)
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
}

//this calculates the elasticities as d(particle flux)/d(particle number)
//which is the same as d(flux of substance)/d(amount of substance)
void CMCAMethod::calculateUnscaledElasticities(C_FLOAT64 /* res */)
{
  assert(mpModel);

  CCopasiVector<CMetab> & metabs = mpModel->getMetabolitesX();
  CCopasiVector<CReaction> & reacs = mpModel->getReactions();
  const CVector< C_FLOAT64 > & ParticleFlux = mpModel->getParticleFlux();

  size_t numReacs = reacs.size();

  // We need the number of metabolites determined by reactions.
  size_t numMetabs =
    mpModel->getNumIndependentReactionMetabs() + mpModel->getNumDependentReactionMetabs();

  //   mUnscaledElasticities.resize(numReacs, numMetabs);
  C_FLOAT64 * pElasticity;
  C_FLOAT64 * pElasticityEnd = mUnscaledElasticities.array() + mUnscaledElasticities.size();

  //update annotated matrix
  //   mUnscaledElasticitiesAnn->resize();
  //   mUnscaledElasticitiesAnn->setCopasiVector(0, &reacs);
  //   mUnscaledElasticitiesAnn->setCopasiVector(1, &metabs);

  size_t j;

  C_FLOAT64 Store, InvDelta;
  C_FLOAT64 X1, X2;

  // Arrays to store function value
  CVector< C_FLOAT64 > Y1(numReacs);
  C_FLOAT64 * pY1;
  CVector< C_FLOAT64 > Y2(numReacs);
  C_FLOAT64 * pY2;

  // calculate elasticities
  for (j = 0; j < numMetabs; j++)
    {
      Store = metabs[j]->getValue();

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
      metabs[j]->setValue(X1);
      mpModel->updateSimulatedValues(false); // TODO test if true or false should be used.

      // get the fluxes
      Y1 = ParticleFlux;

      // now X-dx
      metabs[j]->setValue(X2);
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
      metabs[j]->setValue(Store);
    }

  // make sure the fluxes are correct afterwards (needed for scaling of the MCA results)
  mpModel->updateSimulatedValues(false);
}

int CMCAMethod::calculateUnscaledConcentrationCC()
{
  assert(mpModel);
  const CMatrix< C_FLOAT64 > & redStoi = mpModel->getRedStoi();

  // Initialize the unscaled concentration control coefficients to 0.0
  mUnscaledConcCC = 0.0;

  C_INT32 i, j, k;
  //size_t dim;
  C_INT info;

  CMatrix<C_FLOAT64> aux1, aux2;

  char T = 'N';
  C_INT M = (C_INT) mLinkZero.getNumIndependent(); /* LDA, LDC */
  C_INT N = (C_INT) mUnscaledElasticities.numRows();
  C_INT K = (C_INT) mLinkZero.getNumDependent();
  C_INT LD = (C_INT) mUnscaledElasticities.numCols();

  C_FLOAT64 Alpha = 1.0;
  C_FLOAT64 Beta = 1.0;

  // TODO CRITICAL The columns of mUnscaledElasticities are not in the correct order

  // memcpy(aux1.array(), mUnscaledElasticities.array(), N * LD * sizeof(C_FLOAT64));

  // aux1 = (E1, E2) * (I, L0')' = E1 + E2 * L0
  // _GEMM (TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC)
  // C := alpha A B + beta C

  aux1 = mUnscaledElasticities;
  dgemm_(&T, &T, &M, &N, &K, &Alpha, const_cast< C_FLOAT64 * >(mLinkZero.getLinkZero().array()), &M,
         mUnscaledElasticities.array() + M, &LD, &Beta, aux1.array(), &LD);

  // Implementation without dgemm to avoid column swaps in aux1 and mUnscaledElasticities
  const CVector< size_t > & p = mLinkZero.getRowPivots();
  const CMatrix< C_FLOAT64 > L0 = mLinkZero.getLinkZero();

  CMatrix< C_FLOAT64 > a1(N, LD);

  for (i = 0; i < N; ++i)
    {
      for (j = 0; j < LD; ++j)
        {
          const size_t & pj = p[j];
          C_FLOAT64 & a = a1(i, pj);
          a = mUnscaledElasticities(i, pj);

          if (M <= pj)
            {
              continue;
            }

          for (k = 0; k < LD; ++k)
            {
              const size_t & pk = p[k];

              if (pk < M)
                {
                  continue;
                }

              a += mUnscaledElasticities(i, pk) * L0(pk - M, pj);
            }
        }
    }

  Beta = 0.0;
  aux2.resize(M, M);

  // aux2 = R * aux1
  dgemm_(&T, &T, &M, &M, &N, &Alpha, a1.array(), &LD,
         const_cast<C_FLOAT64 *>(redStoi.array()), &N, &Beta, aux2.array(), &M);

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

  if (info != 0)
    return MCA_SINGULAR;

  // M = independent species, K = dependent species
  aux1.resize(M + K, M);
  aux1 = 0.0;

  // aux1 = - L * aux2 = (I, L0')' * aux2 = -(aux2, (L0 * aux2)')'
  // Implementation without dgemm to avoid column swaps in aux1 and aux2
  for (i = 0; i < M + K; ++i)
    {
      const size_t & pi = p[i];

      for (j = 0; j < M; ++j)
        {

          if (pi < M)
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

  // mGamma = aux1 * RedStoi
  // :TODO: use dgemm

  // M = independent species, K = dependent species
  //  mUnscaledConcCC.resize(M + K, N);
  for (i = 0; i < M + K; i++)
    for (j = 0; j < N; j++)
      {
        C_FLOAT64 & c = mUnscaledConcCC(i, j);

        for (k = 0; k < M; k++)
          c += aux1(i, k) * redStoi(k, j);
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

  // Reactions are rows, species are columns
  for (col = 0; itSpecies != endSpecies; ++itSpecies, col++)
    {
      C_FLOAT64 VolumeInv = 1.0 / (*itSpecies)->getCompartment()->getValue();
      C_FLOAT64 Number = (*itSpecies)->getValue();

      for (itReaction = reacs.begin(),
           pUnscaled = mUnscaledElasticities.array() + col,
           pScaled = mScaledElasticities.array() + col;
           itReaction != endReaction;
           ++itReaction,
           pUnscaled += numSpeciesReaction,
           pScaled += numSpeciesReaction)
        {
          if (fabs((*itReaction)->getFlux() * VolumeInv) >= res)
            * pScaled =
              *pUnscaled * Number / (*itReaction)->getParticleFlux();
          else
            *pScaled =
              (((*itReaction)->getFlux() < 0.0) ? - std::numeric_limits<C_FLOAT64>::infinity() : std::numeric_limits<C_FLOAT64>::infinity());
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
      C_FLOAT64 Scale = (*itReaction)->getFlux() / (*itReaction)->getLargestCompartment().getValue();

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
          else if (fabs((*itReactionCol)->getFlux() / (*itReactionCol)->getLargestCompartment().getValue()) <= res)
            {
              *pScaled = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
            }
          else
            {
              *pScaled = (((*itReaction)->getFlux() < 0.0) ? - std::numeric_limits<C_FLOAT64>::infinity() : std::numeric_limits<C_FLOAT64>::infinity());
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

  mLinkZero.build(mpSteadyStateTask->getJacobian());

  mReducedStoichiometry = mpModel->getStoiReordered();
  mLinkZero.applyRowPivot(mReducedStoichiometry);
  mReducedStoichiometry.resize(mLinkZero.getNumIndependent(), mReducedStoichiometry.numCols());

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
