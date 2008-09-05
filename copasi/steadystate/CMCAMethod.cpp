// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CMCAMethod.cpp,v $
//   $Revision: 1.46 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/09/05 19:56:01 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <cmath>
#include <limits>
#include <float.h>

#include "copasi.h"
#include "utilities/CReadConfig.h"
#include "utilities/utility.h"
#include "model/CModel.h"
#include "utilities/CCopasiTask.h"
#include "CMCAMethod.h"
#include "CMCAProblem.h"

#include "blaswrap.h"
#include "clapackwrap.h"

//TODO: put all matrix resizing and annotations creation in one place, so
// that it has to be done only once if several MCA are calculated (e.g. in a scan)

/**
 * Default constructor
 */
CMCAMethod::CMCAMethod(const CCopasiContainer* pParent):
    CCopasiMethod(CCopasiTask::mca, CCopasiMethod::mcaMethodReder, pParent),
    mpModel(NULL),
    mFactor(1.0e-9),
    mSteadyStateResolution(1.0e-9),
    mSSStatus(CSteadyStateMethod::notFound)
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
    mSSStatus(CSteadyStateMethod::notFound)
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

//that caclulates the elasticities as d(particle flux)/d(particle number)
//which is the same as d(flux of substance)/d(amount of substance)
void CMCAMethod::calculateUnscaledElasticities(C_FLOAT64 /* res */)
{
  assert(mpModel);

  CCopasiVector<CMetab> & metabs = mpModel->getMetabolitesX();
  CCopasiVector<CReaction> & reacs = mpModel->getReactions();
  const CVector< C_FLOAT64 > & ParticleFlux = mpModel->getParticleFlux();

  unsigned C_INT32 numReacs = reacs.size();

  // We need the number of metabolites determined by reactions.
  unsigned C_INT32 numMetabs =
    mpModel->getNumIndependentReactionMetabs() + mpModel->getNumDependentReactionMetabs();

  mUnscaledElasticities.resize(numReacs, numMetabs);
  C_FLOAT64 * pElasticity;
  C_FLOAT64 * pElasticityEnd = mUnscaledElasticities.array() + mUnscaledElasticities.size();

  //update annotated matrix
  mUnscaledElasticitiesAnn->resize();
  mUnscaledElasticitiesAnn->setCopasiVector(0, &reacs);
  mUnscaledElasticitiesAnn->setCopasiVector(1, &metabs);

  unsigned C_INT32 j;

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
      if (fabs(Store) < 100 * DBL_MIN)
        {
          X1 = 0.0;
          if (Store < 0.0)
            X2 = -200.0 * DBL_MIN;
          else
            X2 = 200.0 * DBL_MIN;;
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

  C_INT32 i, j, k;
  //unsigned C_INT32 dim;
  C_INT info;

  CMatrix<C_FLOAT64> aux1, aux2;

  const CMatrix< C_FLOAT64 > & L = mpModel->getL0();
  const CMatrix< C_FLOAT64 > & redStoi = mpModel->getRedStoi();

  char T = 'N';
  C_INT M = mpModel->getNumIndependentReactionMetabs(); /* LDA, LDC */
  C_INT N = mUnscaledElasticities.numRows();
  C_INT K = mpModel->getNumDependentReactionMetabs();
  C_INT LD = mUnscaledElasticities.numCols();

  C_FLOAT64 Alpha = 1.0;
  C_FLOAT64 Beta = 1.0;

  aux1 = mUnscaledElasticities;
  // aux1.resize(N, LD);
  // memcpy(aux1.array(), mUnscaledElasticities.array(), N * LD * sizeof(C_FLOAT64));

  // aux1 = (E1, E2) (I, L0')' = E1 + E2 * L0
  dgemm_(&T, &T, &M, &N, &K, &Alpha, const_cast<C_FLOAT64 *>(L.array()), &M,
         mUnscaledElasticities.array() + M, &LD, &Beta, aux1.array(), &LD);

  Beta = 0.0;

  aux2.resize(M, M);

  // aux2 = R * aux1
  dgemm_(&T, &T, &M, &M, &N, &Alpha, aux1.array(), &LD,
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

  // aux1 = - L * aux2 = (I, L0) * aux2 = (aux2, (L0 * aux2))
  // :TODO: use memcpy and dgemm
  for (i = 0; i < M; i++)
    for (j = 0; j < M; j++)
      aux1[i][j] = - aux2[i][j];

  // M = independent species, K = dependent species
  for (i = M ; i < M + K; i++)
    for (j = 0; j < M; j++)
      {
        aux1[i][j] = 0.0;
        for (k = 0; k < M; k++)
          aux1[i][j] -= (C_FLOAT64)mpModel->getL()(i, k) * aux2[k][j];
      }

  // mGamma = aux1 * RedStoi
  // :TODO: use dgemm
  // M = independent species, K = dependent species
  mUnscaledConcCC.resize(M + K, N);
  for (i = 0; i < M + K; i++)
    for (j = 0; j < N; j++)
      {
        mUnscaledConcCC[i][j] = 0;
        for (k = 0; k < M; k++)
          mUnscaledConcCC[i][j] += aux1[i][k] * (C_FLOAT64) mpModel->getRedStoi()[k][j];
      }

  //update annotations
  mUnscaledConcCCAnn->resize();
  mUnscaledConcCCAnn->setCopasiVector(0, &mpModel->getMetabolitesX());
  mUnscaledConcCCAnn->setCopasiVector(1, &mpModel->getReactions());

  return MCA_OK;
}

void CMCAMethod::calculateUnscaledFluxCC(int condition)
{
  assert(mpModel);
  unsigned C_INT32 i, j, k;

  mUnscaledFluxCC.resize(mpModel->getTotSteps(), mpModel->getTotSteps());

  if (condition == MCA_SINGULAR)
    {
      for (i = 0; i < mUnscaledFluxCC.numRows(); i++)
        for (j = 0; j < mUnscaledFluxCC.numCols(); j++)
          mUnscaledFluxCC[i][j] = 0.0;
    }
  else
    {
      // unscaledFluxCC = I + unscaledElasticities * unscaledConcCC
      for (i = 0; i < mUnscaledFluxCC.numRows(); i++)
        for (j = 0; j < mUnscaledFluxCC.numCols(); j++)
          {
            mUnscaledFluxCC[i][j] = (i == j) ? 1.0 : 0.0;

            for (k = 0; k < mUnscaledConcCC.numRows(); k++)
              mUnscaledFluxCC[i][j] += mUnscaledElasticities[i][k] * mUnscaledConcCC[k][j];
          }
    }

  //update annotations
  mUnscaledFluxCCAnn->resize();
  mUnscaledFluxCCAnn->setCopasiVector(0, &mpModel->getReactions());
  mUnscaledFluxCCAnn->setCopasiVector(1, &mpModel->getReactions());
}

#ifdef WIN32
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

void CMCAMethod::scaleMCA(int condition, C_FLOAT64 res)
{
  assert(mpModel);
  // The number of metabs determined by reaction.
  unsigned C_INT32 numSpeciesReaction =
    mpModel->getNumIndependentReactionMetabs() + mpModel->getNumDependentReactionMetabs();
  CCopasiVector< CMetab > & metabs = mpModel->getMetabolitesX();
  CCopasiVector< CMetab >::const_iterator itSpecies = metabs.begin();
  CCopasiVector< CMetab >::const_iterator endSpecies = itSpecies + numSpeciesReaction;

  CCopasiVector< CReaction > & reacs = mpModel->getReactions();
  CCopasiVector< CReaction >::const_iterator itReaction;
  CCopasiVector< CReaction >::const_iterator endReaction = reacs.end();

  unsigned C_INT32 col;

  // Scale Elasticities
  mScaledElasticities.resize(mUnscaledElasticities.numRows(), mUnscaledElasticities.numCols());

  C_FLOAT64 * pUnscaled;
  C_FLOAT64 * pScaled;
  // Reactions are rows, species are columnss
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
              (((*itReaction)->getFlux() < 0.0) ? -2.0 : 2.0) * DBL_MAX;
        }
    }

  //update annotated matrix
  mScaledElasticitiesAnn->resize();
  mScaledElasticitiesAnn->setCopasiVector(0, &reacs);
  mScaledElasticitiesAnn->setCopasiVector(1, &metabs);

  //if we are not in a steady state we cannot calculate CCs
  if (mSSStatus != CSteadyStateMethod::found) return;

  // if previous calcutations failed return now
  if (condition != MCA_OK)
    return;

  // Scale ConcCC
  // Reactions are columns, species are rows
  mScaledConcCC.resize(mUnscaledConcCC.numRows(), mUnscaledConcCC.numCols());

  for (itSpecies = metabs.begin(),
       pUnscaled = mUnscaledConcCC.array(),
       pScaled = mScaledConcCC.array();
       itSpecies != endSpecies;
       ++itSpecies)
    for (itReaction = reacs.begin();
         itReaction != endReaction;
         ++itReaction, ++pUnscaled, ++pScaled)
      {
        if (fabs((*itSpecies)->getConcentration()) >= res)
          *pScaled =
            *pUnscaled * (*itReaction)->getParticleFlux() / (*itSpecies)->getValue();
        else
          *pScaled = 2.0 * DBL_MAX;
      }
  //std::cout << "scConcCC " << std::endl;
  //std::cout << (CMatrix<C_FLOAT64>)mScaledConcCC << std::endl;

  //update annotations
  mScaledConcCCAnn->resize();
  mScaledConcCCAnn->setCopasiVector(0, &metabs);
  mScaledConcCCAnn->setCopasiVector(1, &reacs);

  // Scale FluxCC
  // Reactions are columns and rows
  mScaledFluxCC.resize(mUnscaledFluxCC.numRows(), mUnscaledFluxCC.numCols());

  CCopasiVector< CReaction >::const_iterator itReactionCol;

  for (itReaction = reacs.begin(),
       pUnscaled = mUnscaledFluxCC.array(),
       pScaled = mScaledFluxCC.array();
       itReaction != endReaction;
       ++itReaction)
    {
      C_FLOAT64 tmp =
        fabs((*itReaction)->getFlux() / (*itReaction)->getLargestCompartment().getValue());

      for (itReactionCol = reacs.begin();
           itReactionCol != endReaction;
           ++itReactionCol, ++pUnscaled, ++pScaled)
        {
          if (tmp >= res)
            *pScaled =
              *pUnscaled * (*itReactionCol)->getFlux() / (*itReaction)->getFlux();
          else
            *pScaled = (((*itReaction)->getFlux() < 0.0) ? -2.0 : 2.0) * DBL_MAX;
        }
    }

  //update annotations
  mScaledFluxCCAnn->resize();
  mScaledFluxCCAnn->setCopasiVector(0, &reacs);
  mScaledFluxCCAnn->setCopasiVector(1, &reacs);
}

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif

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
int CMCAMethod::CalculateMCA(CSteadyStateMethod::ReturnCode C_UNUSED(status), C_FLOAT64 res)
{
  assert(mpModel);
  int ret = MCA_OK;

  calculateUnscaledElasticities(res);

  if (mSSStatus == CSteadyStateMethod::found)
    {
      ret = calculateUnscaledConcentrationCC();
      calculateUnscaledFluxCC(ret);
    }

  scaleMCA(ret, res);

  return ret;
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
      CalculateMCA(mSSStatus, mSteadyStateResolution);
    }
  else
    {
      //   CalculateTimeMCA(mSteadyStateResolution);
    }
  return true;
}

/*bool CMCAMethod::isSteadyState() const
  {
    return this->mIsSteadyState;
  }*/

void CMCAMethod::setSteadyStateStatus(CSteadyStateMethod::ReturnCode SSStatus)
{
  mSSStatus = SSStatus;
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
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not an MCA problem.");
      return false;
    }

  CModel * pModel = pP->getModel();

  if (pModel == NULL)
    return false;

  // Check if the model contains an ODE.
  unsigned C_INT32 NumODE =
    pModel->getStateTemplate().endIndependent() - pModel->getStateTemplate().beginIndependent();

  if (pModel->getNumIndependentReactionMetabs() < NumODE)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, "MCA is not applicable for a system with explicit ODEs.");
      return false;
    }

  // Check if the model has a compartment with an assignment
  CCopasiVector< CCompartment >::const_iterator it = pModel->getCompartments().begin();
  CCopasiVector< CCompartment >::const_iterator end = pModel->getCompartments().end();

  for (; it != end; ++it)
    if ((*it)->getStatus() == CModelEntity::ASSIGNMENT)
      {
        CCopasiMessage(CCopasiMessage::EXCEPTION, "MCA is not applicable for a system with changing volumes.");
        return false;
      }

  return true;
}
