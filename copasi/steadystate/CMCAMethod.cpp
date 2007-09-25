// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CMCAMethod.cpp,v $
//   $Revision: 1.41.2.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/09/25 22:33:40 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mUnscaledElasticities));
  tmp->setMode(CArrayAnnotation::VECTOR);
  tmp->setDescription("Unscaled elasticity matrix");
  tmp->setDimensionDescription(0, "Reactions (reduced system)");
  tmp->setDimensionDescription(1, "Metabolites (reduced system)");
  mUnscaledElasticitiesAnn = tmp;

  tmp = new CArrayAnnotation("Unscaled concentration control coefficients", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mUnscaledConcCC));
  tmp->setMode(CArrayAnnotation::VECTOR);
  tmp->setDescription("Unscaled concentration control coefficients");
  tmp->setDimensionDescription(0, "Metabolites (reduced system)");
  tmp->setDimensionDescription(1, "Reactions (reduced system)");
  mUnscaledConcCCAnn = tmp;

  tmp = new CArrayAnnotation("Unscaled flux control coefficients", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mUnscaledFluxCC));
  tmp->setMode(CArrayAnnotation::VECTOR);
  tmp->setDescription("Unscaled flux control coefficients");
  tmp->setDimensionDescription(0, "Reactions (reduced system)");
  tmp->setDimensionDescription(1, "Reactions (reduced system)");
  mUnscaledFluxCCAnn = tmp;

  tmp = new CArrayAnnotation("Scaled elasticities", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mScaledElasticities));
  tmp->setMode(CArrayAnnotation::VECTOR);
  tmp->setDescription("Scaled elasticity matrix");
  tmp->setDimensionDescription(0, "Reactions (reduced system)");
  tmp->setDimensionDescription(1, "Metabolites (reduced system)");
  mScaledElasticitiesAnn = tmp;

  tmp = new CArrayAnnotation("Scaled concentration control coefficients", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mScaledConcCC));
  tmp->setMode(CArrayAnnotation::VECTOR);
  tmp->setDescription("Scaled concentration control coefficients");
  tmp->setDimensionDescription(0, "Metabolites (reduced system)");
  tmp->setDimensionDescription(1, "Reactions (reduced system)");
  mScaledConcCCAnn = tmp;

  tmp = new CArrayAnnotation("Scaled flux control coefficients", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mScaledFluxCC));
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
void CMCAMethod::calculateUnscaledElasticities(C_FLOAT64 res)
{
  assert(mpModel);

  CCopasiVector<CMetab> & metabs = mpModel->getMetabolitesX();
  CCopasiVector<CReaction> & reacs = mpModel->getReactions();

  //mUnscaledElasticities.setup(reacs, metabs);
  unsigned C_INT32 numReacs = reacs.size();
  unsigned C_INT32 numMetabs = metabs.size();
  mUnscaledElasticities.resize(numReacs, numMetabs);

  //update annotated matrix
  mUnscaledElasticitiesAnn->resize();
  mUnscaledElasticitiesAnn->setCopasiVector(0, &reacs);
  mUnscaledElasticitiesAnn->setCopasiVector(1, &metabs);

  unsigned C_INT32 i, j;
  C_FLOAT64 store, temp;
  C_FLOAT64 K1, K2, K3;

  // constants for differentiation by finite differences
  K1 = 1 + mFactor;
  K2 = 1 - mFactor;
  K3 = 2 * mFactor;

  // Arrays to store function value
  std::vector<C_FLOAT64> f1; f1.resize(numReacs);
  std::vector<C_FLOAT64> f2; f2.resize(numReacs);

  // calculate elasticities
  for (j = 0; j < numMetabs; j++)
    {
      /**
       * if src[i+1] (x_ss[i+1]) is zero, the derivative will be calculated at a small
       * positive value (no point in considering negative values!).
       * let's stick with res*K1 (SSRes)
       */
      store = metabs[j]->getValue();

      if (store < res)
        temp = res * K1;
      else
        temp = store;

      // let's take X_dx
      metabs[j]->setValue(temp * K1);
      mpModel->updateSimulatedValues(false); //TODO test if true or false shoudl be used
      //mpModel->updateNonSimulatedValues();

      // get the fluxes
      for (i = 0; i < numReacs; i++)
        //f1[i] = reacs[i]->calculateParticleFlux();
        f1[i] = reacs[i]->getParticleFlux();

      // now X-dx
      metabs[j]->setValue(temp * K2);
      mpModel->updateSimulatedValues(false); //TODO test if true or false shoudl be used
      //mpModel->updateNonSimulatedValues();

      // get the fluxes
      for (i = 0; i < numReacs; i++)
        //f2[i] = reacs[i]->calculateParticleFlux();
        f2[i] = reacs[i]->getParticleFlux();

      // set column j of Dxv
      for (i = 0; i < numReacs; i++)
        mUnscaledElasticities[i][j] = (f1[i] - f2[i]) / (temp * K3); //TODO optimize

      // restore the value of (src[i])ss_x[i]
      metabs[j]->setValue(store);
    }

  // make shure the fluxes are correct afterwords (needed for scaling of the MCA results)
  for (i = 0; i < numReacs; i++)
  {reacs[i]->calculateParticleFlux();}

  //std::cout << "elasticities" << std::endl;
  //std::cout << (CMatrix<C_FLOAT64>)mUnscaledElasticities << std::endl;
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
  C_INT M = mpModel->getNumIndependentMetabs(); /* LDA, LDC */
  C_INT N = mUnscaledElasticities.numRows();
  C_INT K = mpModel->getNumDependentMetabs();
  C_INT LD = mUnscaledElasticities.numCols();

  C_FLOAT64 Alpha = 1.0;
  C_FLOAT64 Beta = 1.0;

  aux1.resize(N, LD);

  memcpy(aux1.array(), mUnscaledElasticities.array(), N * LD * sizeof(C_FLOAT64));

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

  // :TODO: Bug 774: This assumes that the number of variable metabs is the number
  // of metabs determined by reaction.
  aux1.resize(mpModel->getNumVariableMetabs(), M);
  aux1 = 0.0;

  // aux1 = - L * aux2 = (I, L0) * aux2 = (aux2, (L0 * aux2))
  // :TODO: use memcpy and dgemm
  for (i = 0; i < M; i++)
    for (j = 0; j < M; j++)
      aux1[i][j] = - aux2[i][j];

  // :TODO: Bug 774: This assumes that the number of variable metabs is the number
  // of metabs determined by reaction.
  for (i = M ; i < (C_INT32)mpModel->getNumVariableMetabs(); i++)
    for (j = 0; j < M; j++)
      {
        aux1[i][j] = 0.0;
        for (k = 0; k < M; k++)
          aux1[i][j] -= (C_FLOAT64)mpModel->getL()(i, k) * aux2[k][j];
      }

  // mGamma = aux1 * RedStoi
  // :TODO: use dgemm
  // :TODO: Bug 774: This assumes that the number of variable metabs is the number
  // of metabs determined by reaction.
  mUnscaledConcCC.resize(mpModel->getNumVariableMetabs(), N);
  for (i = 0; i < (C_INT32)mpModel->getNumVariableMetabs(); i++)
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
  // if previous calcutations failed return now
  if (condition != MCA_OK)
    return;

  unsigned C_INT32 i, j;

  // Scale Elasticities
  mScaledElasticities.resize(mUnscaledElasticities.numRows(), mUnscaledElasticities.numCols());
  for (j = 0; j < mpModel->getNumMetabs(); j++)
    {
      C_FLOAT64 VolumeInv = 1.0 / mpModel->getMetabolitesX()[j]->getCompartment()->getValue();
      C_FLOAT64 Number = mpModel->getMetabolitesX()[j]->getValue();

      for (i = 0; i < mpModel->getTotSteps(); i++)
        {
          // change the use of Col[] and Row[] to mSteps and mMetabolites
          // change the use of ICol[] and IRow[] to mStepsX and mMetabolitesX

          if (fabs(mpModel->getReactions()[i]->getFlux() * VolumeInv) >= res)
            {
              mScaledElasticities[i][j] = mUnscaledElasticities[i][j] * Number
                                          / mpModel->getReactions()[i]->getParticleFlux();
              //                                        * mpModel->getMetabolites()[j]->getConcentration()
              //                                        * mpModel->getMetabolites()[j]->getCompartment()->getValue()
              //                                        / mpModel->getReactions()[i]->getFlux();
            }
          else
            mScaledElasticities[i][j] = ((mpModel->getReactions()[i]->getFlux() < 0.0) ? -2.0 : 2.0) * DBL_MAX;
        }
    }

  //update annotated matrix
  mScaledElasticitiesAnn->resize();
  mScaledElasticitiesAnn->setCopasiVector(0, &mpModel->getReactions());
  mScaledElasticitiesAnn->setCopasiVector(1, &mpModel->getMetabolitesX());

  //std::cout << "scElas " << std::endl;
  //std::cout << (CMatrix<C_FLOAT64>)mScaledElasticities << std::endl;
  if (mSSStatus != CSteadyStateMethod::found) return;

  // Scale ConcCC
  mScaledConcCC.resize(mUnscaledConcCC.numRows(), mUnscaledConcCC.numCols());
  // :TODO: Bug 774: This assumes that the number of variable metabs is the number
  // of metabs determined by reaction.
  for (i = 0; i < mpModel->getNumVariableMetabs(); i++)
    for (j = 0; j < mpModel->getTotSteps(); j++)
      {
        if (fabs(mpModel->getMetabolitesX()[i]->getConcentration()) >= res)
          mScaledConcCC[i][j] = mUnscaledConcCC[i][j]
                                * mpModel->getReactions()[j]->getParticleFlux()
                                / mpModel->getMetabolitesX()[i]->getValue();
        //                                * mpModel->getReactions()[j]->getFlux()
        //                                / (mpModel->getMetabolites()[i]->getConcentration()
        //                                   *mpModel->getMetabolites()[j]->getCompartment()->getValue());
        else
          mScaledConcCC[i][j] = 2.0 * DBL_MAX;
      }
  //std::cout << "scConcCC " << std::endl;
  //std::cout << (CMatrix<C_FLOAT64>)mScaledConcCC << std::endl;

  //update annotations
  mScaledConcCCAnn->resize();
  mScaledConcCCAnn->setCopasiVector(0, &mpModel->getMetabolitesX());
  mScaledConcCCAnn->setCopasiVector(1, &mpModel->getReactions());

  // Scale FluxCC
  mScaledFluxCC.resize(mUnscaledFluxCC.numRows(), mUnscaledFluxCC.numCols());
  for (i = 0; i < mpModel->getTotSteps(); i++)
    for (j = 0; j < mpModel->getTotSteps(); j++)
      {
        C_FLOAT64 tmp = 1.0 / mpModel->getReactions()[i]->getLargestCompartment().getValue();

        if (fabs(mpModel->getReactions()[i]->getFlux()*tmp) >= res)
          mScaledFluxCC[i][j] = mUnscaledFluxCC[i][j]
                                * mpModel->getReactions()[j]->getFlux()
                                / mpModel->getReactions()[i]->getFlux();
        else
          mScaledFluxCC[i][j] = ((mpModel->getReactions()[i]->getFlux() < 0.0) ? -2.0 : 2.0) * DBL_MAX;
      }
  //std::cout << "scFluxCC " << std::endl;
  //std::cout << (CMatrix<C_FLOAT64>)mScaledFluxCC << std::endl;

  //update annotations
  mScaledFluxCCAnn->resize();
  mScaledFluxCCAnn->setCopasiVector(0, &mpModel->getReactions());
  mScaledFluxCCAnn->setCopasiVector(1, &mpModel->getReactions());
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

  return true;
}
