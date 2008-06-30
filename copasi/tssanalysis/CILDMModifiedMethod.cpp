// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CILDMModifiedMethod.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2008/06/30 11:42:18 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CILDMModifiedMethod.h"
#include "CTSSAProblem.h"

//#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CMetab.h"
//#include "model/CState.h"
//#include "utilities/CMatrix.h"
//#include "utilities/CAnnotatedMatrix.h"
//#include "report/CCopasiObjectReference.h"

#include "clapackwrap.h"        // CLAPACK
#include "blaswrap.h"           // BLAS

CILDMModifiedMethod::CILDMModifiedMethod(const CCopasiContainer * pParent):
    CTSSAMethod(CCopasiMethod::tssILDMModified, pParent) //,
    // mpState(NULL),
    // mY(NULL)
{
  //  assert((void *) &mData == (void *) &mData.dim);

  //  addObjectReference("Number of slow variables", mSlow, CCopasiObject::ValueInt);
  //  addMatrixReference("Contribution of Metabolites to Slow Space", mVslow, CCopasiObject::ValueDbl);

  mData.pMethod = this;
  initializeParameter();
}

CILDMModifiedMethod::CILDMModifiedMethod(const CILDMModifiedMethod & src,
    const CCopasiContainer * pParent):
    CTSSAMethod(src, pParent) //,
    //mpState(NULL),
    //mY(NULL)
{
  //  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CILDMModifiedMethod::~CILDMModifiedMethod()
{
  pdelete(mpState);
}

void CILDMModifiedMethod::initializeParameter()
{
  addObjectReference("Number of slow variables", mSlow, CCopasiObject::ValueInt);
  addMatrixReference("Contribution of Metabolites to Slow Space", mVslow, CCopasiObject::ValueDbl);

  initializeIntegrationsParameter();

  createAnnotationsM();
  emptyVectors();
}

void CILDMModifiedMethod::start(const CState * initialState)
{

  integrationMethodStart(initialState);

  /* ILDM related staff  */

  mDtol = mpProblem->getDeufelhardTol();

  mVslow.resize(mData.dim, mData.dim);
  mVslow_metab.resize(mData.dim, mData.dim);
  mVslow_space.resize(mData.dim);
  mVfast_space.resize(mData.dim);

  return;
}

void CILDMModifiedMethod::step(const double & deltaT)
{

  C_INT dim = mData.dim;
  C_INT fast = 0;
  C_INT slow = dim - fast;

  C_INT slow2, fast2;

  slow2 = dim;
  fast2 = dim - slow2;

  C_INT i, j;

  mY_initial.resize(dim);
  mJacobian_initial.resize(dim, dim);
  mQ.resize(dim, dim);
  mR.resize(dim, dim);
  mTd.resize(dim, dim);
  mTdInverse.resize(dim, dim);
  mQz.resize(dim, dim);

  mTd_save.resize(dim, dim);

  //CMatrix<C_FLOAT64> TdInverse_save;
  mTdInverse_save.resize(dim, dim);

  mpModel->updateSimulatedValues(mReducedModel);
  // TO REMOVE : mpModel->applyAssignments();
  mpModel->calculateJacobianX(mJacobian, 1e-6, 1e-12);

  std::cout << std::endl;
  std::cout << "****************************************************************" << std::endl;
  std::cout << "****************************************************************" << std::endl;
  std::cout << "Next step t=: " << mTime << std::endl;
  std::cout << "****************************************************************" << std::endl;
  std::cout << "****************************************************************" << std::endl;

  C_INT flag_jacob;
  flag_jacob = 1;  // Set flag_jacob=0 to print Jacobian

  if (flag_jacob == 0)
    {
      std::cout << "Jacobian-initial:" << std::endl;
      std::cout << mJacobian << std::endl;
    }

  C_FLOAT64 number2conc = mpModel->getNumber2QuantityFactor()
                          / mpModel->getCompartments()[0]->getInitialValue();

  //this is an ugly hack that only makes sense if all metabs are in the same compartment
  //at the moment is is the only case the algorithm deals with

  CVector<C_FLOAT64> Xconc; //current state converted to concentrations
  Xconc.resize(dim);

  for (i = 0; i < dim; ++i)
    Xconc[i] = mY[i] * number2conc;

  for (i = 0; i < dim; i++)
    mY_initial[i] = mY[i];

  CVector<C_FLOAT64> Xconc_initial; //current state converted to concentrations
  Xconc_initial.resize(dim);

  for (i = 0; i < dim; ++i)
    Xconc_initial[i] = mY_initial[i] * number2conc;

  // save initial  Jacobian before next time step
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      mJacobian_initial(i, j) = mJacobian(i, j);

  // Next time step
  integrationStep(deltaT);

  mpModel->updateSimulatedValues(mReducedModel);
  // TO REMOVE : mpModel->applyAssignments();

  // Calculate Jacobian for time step control
  mpModel->calculateJacobianX(mJacobian, 1e-6, 1e-12);

  if (flag_jacob == 0)
    {
      std::cout << "Jacobian_next:" << std::endl;
      std::cout << mJacobian << std::endl;
    }

  //CMatrix<C_FLOAT64> mTd_save;
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      {
        mTd_save(i, j) = 0;
        mTdInverse_save(i, j) = 0;
      }

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      {
        mTd(i, j) = 0;
        mTdInverse(i, j) = 0;
      }

  /** Schur  Decomposition of Jacobian (reordered).
  Output:  mQ - transformation matrix mR - block upper triangular matrix (with ordered eigenvalues) */

  C_INT failed = 0;
  C_INT info_schur = 0;

  C_INT number, k;
  C_INT failed_while = 0;

  C_INT flag_deufl;
  flag_deufl = 1;

  C_FLOAT64 max = 0.;

  //C_FLOAT64 max = 0;
  CVector<C_FLOAT64> re;
  CVector<C_FLOAT64> dxdt_relax;
  CVector<C_FLOAT64> x_relax;
  CVector<C_FLOAT64> x_help;
  CVector<C_FLOAT64> dxdt;

  CVector<C_FLOAT64> x_zero;

  CVector<C_FLOAT64> dxdt_zero;

  CVector<C_FLOAT64> dxdt_real;

  CVector<C_FLOAT64> help;

  CVector<C_INT> index;
  CVector<C_INT> index_temp;
  CMatrix<C_FLOAT64> orthog_prove;
  orthog_prove.resize(dim, dim);

  C_INT flag_orthog = 1;   // set flag_orthog = 0 to print the prove of orthogonality of matrix mQ
  C_INT info;

  CVector<C_INT> index_metab;
  index_metab.resize(dim);

  /** Schur transformation of Jacobian */
  schur(info_schur);

  std::cout << "info_schur: " << info_schur << std::endl;

  if (info_schur)
    {
      std::cout << " There are problems with calculation of Jacobi matrix. Please check  the problem is specified suitable. " << std::endl;
      goto integration;
    }

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      {
        mTdInverse(i, j) = mQ(j, i);
      }

  // Prove of orthogonality of mQ
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      {
        orthog_prove(i, j) = orthog(i, j);
      }

  if (flag_orthog == 0)
    std::cout << "Proof of  matrix Q:" << orthog_prove << std::endl;

  C_INT flag_schur;

  flag_schur = 1;  // set flag_schur = 0 to print Schur decomposition of jacobian (matrices mR and transformation mQ)

  if (flag_schur == 0)
    {
      std::cout << "Schur Decomposition" << std::endl;
      std::cout << "mR - block upper triangular matrix :" << std::endl;
      std::cout << mR << std::endl;
      std::cout << "mQ - transformation matrix" << std::endl;
      std::cout << mQ << std::endl;
    }

  mY_cons.resize(dim);  // consistent initial vector for DAE

  /* If complex eigenvalues */
  //BUG 873
  if (mR(dim - 1, dim - 1) == mR(dim - 2 , dim - 2))
    {
      if (dim == 2)
        {
          slow = dim;
          goto integration;
        }
      else
        {
          //  fast = fast + 1;
          //  slow = dim - fast;
        }
    }

  // If positive eigenvalues

  if (mR(dim - 1, dim - 1) >= 0)
    {
      slow = dim;
      fast = 0;
      std::cout << "positive eigenvalues" << std::endl;
      failed = 1;
      goto integration;
    }

  /** till this point the ILDM and ILDMModified are similar
       The difference is in the type of iterations to define slow modes */

  /** Begin of block %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  */

  std::cout << std::endl;
  std::cout << "Prove every metabolite for DAE" << std::endl;
  std::cout << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;

  C_INT temp;
  temp = dim - 1;

  // Mode Analysis to find the dominant metabolites in the modes
  mat_anal_mod(temp);

  //index_metab = -1, if there is no dominant metabolites in corresponding mode, and is equal
  // to the number of dominant metabolite in opposite case

  for (j = 0; j < dim; j++)
    index_metab[j] = -1;

  for (i = 0; i < dim ; i ++)
    for (j = 0; j < dim; j++)
      {
        if (mVslow(dim - i - 1, j) > 70)
          index_metab[i] = j;
      }

  std::cout << "Dominance of metabolites in the mode:" << std::endl;

  for (i = 0; i < dim; i++)
    {
      j = index_metab[i];
      std::cout << " Mode number: " << dim - i << " TS: " << - 1 / mR(dim - i - 1, dim - i - 1) << " : ";
      if (j > - 1)
        std::cout << "  Metabolite : " << mpModel->getMetabolitesX()[j]->getObjectName() << std::endl;
      else
        std::cout << "   There is no dominant metabolite in this mode" << std::endl;
    }

  C_FLOAT64 y_cons;

  info = 0;
  k = 0;
  number = index_metab[k];

  if (number > - 1)
    {
      newton_for_timestep(number, y_cons, info);
      //  std::cout << "y_cons for metabolite number " << number << ": " << y_cons << std::endl;
    }
  else
    std::cout << "The are no dominant metabolites in  fastest mode" << std::endl;

  while (k < dim - 1)
    {
      if (number > -1)
        {
          dxdt.resize(dim);
          for (j = 0; j < dim; j++)
            dxdt[j] = 0.;

          //CVector<C_FLOAT64> x_help;
          x_help.resize(dim);

          for (j = 0; j < dim; j++)
            {
              x_help[j] = mY_initial[j] * number2conc;
              if (flag_deufl == 0)
                std::cout << "x_help: " << x_help[j] << std::endl;
            }

          // mpModel->calculateDerivativesX(dxdt.array());
          calculateDerivativesX(x_help.array(), dxdt.array());

          info = 0;

          //NEWTON: Looking for consistent initial value for DAE system
          //Output:  y_cons, info

          newton_for_timestep(number, y_cons, info);

          if (info)
            {
              // TODO
              std::cout << "info: newton iteration stop" << std::endl;
            }

          if (info == 0)
            {
              // CVector<C_FLOAT64> x_relax;
              x_relax.resize(dim);

              for (i = 0; i < dim; i ++)
                {
                  if (i == number)
                    x_relax[i] = y_cons;
                  else
                    x_relax[i] = x_help[i];
                }

              //CVector<C_FLOAT64> dxdt_relax;
              dxdt_relax.resize(dim);

              if (flag_deufl == 0)
                for (i = 0; i < dim; i++)
                  {
                    std::cout << "x_relax[" << i << "] = " << x_relax[i] << std::endl;
                    std::cout << std::endl;
                  }

              calculateDerivativesX(x_relax.array(), dxdt_relax.array());

              if (flag_deufl == 0)
                {
                  std::cout << "Two right hand side for deuflhard " << std::endl;
                  for (i = 0; i < dim; i++)
                    {
                      std::cout << "dxdt_relax[" << i << "]: " << dxdt_relax[i] << std::endl;
                      std::cout << "dxdt[" << i << "]: " << dxdt[i] << std::endl;
                    }
                  std::cout << std::endl;
                }

              //CVector<C_FLOAT64> re;
              re.resize(dim);

              C_FLOAT64 eps;
              eps = 1 / fabs(mR(dim - k - 1 , dim - k - 1));
              std::cout << "Time Scale corresponding to metabolite " << mpModel->getMetabolitesX()[number]->getObjectName() << ": " << eps << std::endl;

              // stop criterion for slow reaction modes

              for (i = 0; i < dim; i++)
                {
                  if (i == number)
                    re[i] = 0;
                  else
                    {
                      re[i] = fabs(dxdt_relax[i] - dxdt[i]);
                      re[i] = re[i] * eps;
                    }
                  if (flag_deufl == 0)
                    std::cout << " re[" << i << "] = " << re[i] << std::endl;
                }

              //C_FLOAT64 max = 0.;
              for (i = 0; i < dim; i++)
                if (max < re[i])
                  max = re[i];

              if (max >= mDtol)
                info = 1;
              else
                info = 0;

              std::cout << "Prove of Deuflhard criterium for metabolite  " << mpModel->getMetabolitesX()[number]->getObjectName() << " : ";

              if (info == 0)
                {
                  std::cout << "IS SATISFIED" << std::endl;
                  std::cout << " max error of slow metabolites : " << max << " with user defined tolerance: " << mDtol << std::endl;
                }
              else
                {
                  std::cout << "NOT SATISFIED." << std::endl;
                  std::cout << " max error of slow metabolites : " << max << " with user defined tolerance: " << mDtol << std::endl;
                }
              std::cout << std::endl;
            }
        }
      k = k + 1;
      number = index_metab[k];
      max = 0;
    }

  std::cout << "********** end of block to prove every metabolite for DAE" << std::endl;
  std::cout << std::endl;

  /** end of the of block %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  */
  /** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  */

  /** Begin of block %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  */
  std::cout << std::endl;
  std::cout << "Begin of deuflhard iterations" << std::endl;
  std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;

  // Iterations to determine the number of slow metabolites

  while ((slow2 > 1))
    {
      slow2 = slow2 - 1;
      fast2 = dim - slow2;
      if (mR(dim - fast2, dim - fast2) >= 0)
        {
          std::cout << "there are positive eigenvalues " << mR(dim - fast2, dim - fast2) << " for slow = " << slow2 << std::endl;
          failed = 1;
          goto integration;
        }
      deuflhard_metab(slow2, info);

      if (info)
        {
          std::cout << "The last metabolite does not satisfy the Deuflhard criterium" << std::endl;
          failed_while = 1;
          goto integration;
        }

      std::cout << "slow2 = " << slow2 << std::endl;
      std::cout << std::endl;
    }

  //end of iterations to determine the number of slow metabolites

  /** end of the block %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  */
  /** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  */

integration:

  slow = slow2;
  fast = fast2;

  if ((failed == 1) || (failed_while == 1))
    {
      if (slow < dim)
        {
          fast = fast - 1;
          slow = dim - fast;
          if ((fast >= 1) && (mR(slow - 1, slow - 1) == mR(slow , slow)))
            fast = fast - 1;
          slow = dim - fast;
        }
    }

  mSlow = slow;

  std::cout << "slow " << mSlow << std::endl;
  std::cout << "fast " << fast << std::endl;

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      mTd(i, j) = mQ(i, j);

  // Flag for print Tabs

  C_INT flag_tab;
  flag_tab = 1;    //change flag_tab=0 to print the Analysis Tabs  in the file

  mat_anal_mod(slow);
  mat_anal_metab(slow);
  mat_anal_mod_space(slow);
  mat_anal_fast_space(slow);

  if (flag_tab == 0)
    {
      for (i = 0 ; i < dim; i++)
        {
          std::cout << "Contribution to slow space:" << mpModel->getMetabolitesX()[i]->getObjectName() << "  " << mVslow_space[i] << std::endl;
        }
      std::cout << std::endl;

      for (i = 0 ; i < dim; i++)
        {
          std::cout << "Contribution to mode number " << i + 1 << ". Time scale: " << -(1 / mR(i, i)) << std::endl;
          for (j = 0; j < dim; j++)
            std::cout << mpModel->getMetabolitesX()[j]->getObjectName() << "  " << mVslow(i, j) << std::endl;
          std::cout << std::endl;
        }

      std::cout << std::endl;

      for (i = 0 ; i < dim; i++)
        {
          std::cout << "Metabolite: " << mpModel->getMetabolitesX()[i]->getObjectName() << std::endl;
          for (j = 0; j < dim; j++)
            std::cout << "Mode number" << j + 1 << ": " << mVslow_metab(i, j) << std::endl;
          std::cout << std::endl;
        }

      for (i = 0 ; i < dim; i++)
        std::cout << "Contribution to fast space:" << mpModel->getMetabolitesX()[i]->getObjectName() << "  " << mVfast_space[i] << std::endl;

      std::cout << std::endl;
    }

  if (slow == dim)
    {
      std::cout << "No reduction is possible at this time point " << std::endl;
      std::cout << std::endl;
    }

  C_INT flag_Td;

  flag_Td = 1;  // set flag_Td = 0 to print transforation matrices mTd and mTdInverse

  if (flag_Td == 0)
    {
      std::cout << "Transformation matrix mTd: " << std::endl;
      std::cout << mTd << std::endl;
      std::cout << std::endl;
      std::cout << "Inverse of transformation matrix: mTdInvesre: " << std::endl;
      std::cout << mTdInverse << std::endl;
      std::cout << std::endl;
    }

  mpModel->updateSimulatedValues(mReducedModel);
  // TO REMOVE : mpModel->applyAssignments();

  // Calculate Jacobian for time step control

  mpModel->calculateJacobianX(mJacobian, 1e-6, 1e-12);

  // new entry for every entry contains the current data of currently step
  setVectors(slow);

  // set the stepcounter
  mCurrentStep += 1;

  return;
}

/**
 EVALSORT for vector sorting
 */

void CILDMModifiedMethod::evalsort(C_FLOAT64 *reval, C_INT *index, const C_INT & dim)
{
  C_INT i, j, min, tmp_ind;
  C_FLOAT64 tmp1r;
  // CVector<C_INT> index;
  //index.resize(dim);

  //for (i = 0; i < dim; i++)
  // index[i] = i;

  for (i = 0; i < dim - 1; i++)
    {
      min = i;
      for (j = i + 1; j < dim; j++)
        {
          if (reval[j] <= reval[min])
            min = j;
        }
      //std::cout << "min from evalsort [" << i << "]: " << min << std::endl;
      tmp1r = reval[min];
      tmp_ind = index[min];
      reval[min] = reval[i];
      index[min] = index[i];
      reval[i] = tmp1r;
      index[i] = tmp_ind;

      //for (j = 0; j < dim; j++)
      //   std::cout << index[j] << std::endl;
    }

  //std::cout << "re_sort:" << std::endl;

  //for (i = 0; i < dim; i++)
  // std::cout << reval[i] << std::endl;

  // std::cout << std::endl;

  //std::cout << "index:" << std::endl;

  //for (i = 0; i < dim; i++)
  //std::cout << index[i] << std::endl;

  // std::cout << std::endl;

  return;
}

/**
  Deuflhard Iteration:  Prove Deuflhard criteria, find consistent initial value for DAE
  output:  info - if Deuflhard is satisfied
 */
void CILDMModifiedMethod::deuflhard_metab(C_INT & slow, C_INT & info)
{
  C_INT i, j, info_newton;
  C_INT dim = mData.dim;
  C_INT fast = dim - slow;

  C_INT flag_deufl;

  flag_deufl = 1;  // set flag_deufl=0  to print temporaly steps for this function

  C_FLOAT64 max = 0;
  CVector<C_FLOAT64> re;
  CVector<C_FLOAT64> dxdt_relax;
  CVector<C_FLOAT64> x_relax;
  CVector<C_FLOAT64> x_help;
  CVector<C_FLOAT64> dxdt;

  CVector<C_FLOAT64> help;
  help.resize(dim);
  CVector<C_INT> index;
  index.resize(dim);
  CVector<C_INT> index_temp;
  index_temp.resize(dim);

  C_FLOAT64 eps;
  eps = 1 / fabs(mR(dim - fast , dim - fast));

  if (flag_deufl == 0)
    {
      std::cout << "slow fast from deuflhard_metab " << slow << "," << fast << std::endl;
      std::cout << "EPS: " << eps << std::endl;
      std::cout << std::endl;
    }

  mat_anal_fast_space(slow);

  for (i = 0; i < dim; i++)
    {
      index[i] = i;
      index_temp[i] = i;
    }

  for (i = 0; i < dim; i++)
    {
      help[i] = mVfast_space[i];
      if (flag_deufl == 0)
        std::cout << "mVfast[ " << i << "]: " << mVfast_space[i] << std::endl;
    }

  evalsort(help.array(), index.array(), dim);

  for (i = 0; i < dim; i++)
    index_temp[i] = index[i];

  if (flag_deufl == 0)
    {
      std::cout << std::endl;
      std::cout << "index after evalsort" << std::endl;
    }
  for (i = 0; i < dim; i++)
    {
      index[i] = index_temp[dim - i - 1];
      if (flag_deufl == 0)
        std::cout << "index[" << i << "]: " << index[i] << std::endl;
    }

  C_FLOAT64 number2conc = mpModel->getNumber2QuantityFactor() / mpModel->getCompartments()[0]->getInitialValue();

  dxdt.resize(dim);

  for (j = 0; j < dim; j++)
    dxdt[j] = 0.;

  //CVector<C_FLOAT64> x_help;
  x_help.resize(dim);

  for (j = 0; j < dim; j++)
    {
      x_help[j] = mY_initial[j] * number2conc;
      if (flag_deufl == 0)
        std::cout << "x_help: " << x_help[j] << std::endl;
    }

  // mpModel->calculateDerivativesX(dxdt.array());
  calculateDerivativesX(x_help.array(), dxdt.array());

  info_newton = 0;

  newton_new(index.array(), slow, info_newton);

  if (info_newton)
    {
      // TODO
      info = 1;
      std::cout << "info: newton iteration stop" << std::endl;
      if (info_newton == 1)
        std::cout << "Newton does not converge" << std::endl;
      else
        {
          if (info_newton == 2)
            std::cout << "Problems with inverse of Jacobian " << std::endl;
          else
            std::cout << " The are no dominant metabolites " << std::endl;
        }
      return;
    }

  x_relax.resize(dim);

  for (i = 0; i < dim; i++)
    x_relax[i] = mY_cons[i];

  //CVector<C_FLOAT64> dxdt_relax;
  dxdt_relax.resize(dim);

  if (flag_deufl == 0)
    for (i = 0; i < dim; i++)
      std::cout << "x_relax[" << i << "] = " << x_relax[i] << std::endl;

  calculateDerivativesX(x_relax.array(), dxdt_relax.array());

  if (flag_deufl == 0)
    {
      std::cout << "Two right hand side for deuflhard " << std::endl;
      for (i = 0; i < dim; i++)
        {
          std::cout << "dxdt_relax[" << i << "]: " << dxdt_relax[i] << std::endl;
          std::cout << "dxdt[" << i << "]: " << dxdt[i] << std::endl;
        }
      std::cout << std::endl;
    }

  //CVector<C_FLOAT64> re;
  re.resize(dim);

  // stop criterion for slow reaction modes

  for (i = 0; i < dim; i++)
    {
      re[i] = fabs(dxdt_relax[i] - dxdt[i]);
      re[i] = re[i] * eps;
      for (j = 0; j < fast; j ++)
        if (i == index[j])
          re[i] = 0;
      if (flag_deufl == 0)
        std::cout << " re[" << i << "] = " << re[i] << std::endl;
    }

  for (i = 0; i < dim; i++)
    if (max < re[i])
      max = re[i];

  if (max >= mDtol)
    info = 1;
  else
    info = 0;

  std::cout << std::endl;

  return;
}

void CILDMModifiedMethod::newton_new(C_INT *index_metab, C_INT & slow, C_INT & info)
{
  C_INT i, j, k, m, iter, iterations, itermax;
  C_INT nrhs, ok, fast, flag_newton;

  flag_newton = 1;  // set flag_newton=1  to print temporaly steps of newton iterations

  C_FLOAT64 tol, err;
  C_INT dim = mData.dim;

  fast = dim - slow;

  CVector<C_INT> ipiv;
  ipiv.resize(fast);

  CVector<C_FLOAT64> s_22_array;
  s_22_array.resize(fast*fast);

  CVector<C_FLOAT64> gf_newton;
  gf_newton.resize(fast);

  CVector<C_FLOAT64> d_yf;
  d_yf.resize(dim);

  CVector<C_FLOAT64> y_newton;
  y_newton.resize(dim);

  CVector<C_FLOAT64> yf_newton;
  yf_newton.resize(fast);

  CVector<C_FLOAT64> dydt_newton;
  dydt_newton.resize(dim);

  CVector<C_FLOAT64> g_newton;
  g_newton.resize(dim);

  CMatrix<C_FLOAT64> Jac_fast;
  Jac_fast.resize(fast, fast);

  mY_cons.resize(dim);

  nrhs = 1;
  tol = 1e-6;
  err = 10.0;
  iter = 0;

  itermax = 150;
  iterations = 0;

  info = 0;

  C_FLOAT64 number2conc = mpModel->getNumber2QuantityFactor() / mpModel->getCompartments()[0]->getInitialValue();

  std::cout << "Candidates for fast metabolites" << std::endl;

  for (i = 0; i < fast; i++)
    {
      m = index_metab[i];
      std::cout << mpModel->getMetabolitesX()[m]->getObjectName() << ", ";
      for (j = 0; j < fast; j++)
        {
          k = index_metab[ j];
          if ((m > -1) & (k > -1))
            Jac_fast(i, j) = mJacobian_initial(m, k);
          else
            {
              info = 3;
              return;
            }
        }
    }

  std::cout << std::endl;

  if (flag_newton == 0)
    {
      for (i = 0; i < fast; i++)
        for (j = 0; j < fast; j++)
          std::cout << "Jac_fast(" << i << "," << j << "): " << Jac_fast(i, j) << std::endl;
    }

  for (i = 0; i < dim; i++)
    y_newton[i] = mY_initial[i] * number2conc;

  for (i = 0; i < fast; i++)
    for (j = 0; j < fast; j++)
      s_22_array[j + fast*i] = Jac_fast(j, i);

  for (i = 0; i < dim; i++)
    d_yf[i] = 0.;

  while (err > tol)
    {
      iter ++;

      if (iter > itermax)
        {
          info = 1;
          std::cout << "iter > itermax" << iter << std::endl;
          return;
        }

      for (i = 0; i < dim; i++)
        y_newton[i] = y_newton[i] + d_yf[i];

      calculateDerivativesX(y_newton.array(), dydt_newton.array());

      for (i = 0; i < fast; i++)
        {
          j = index_metab[i];
          gf_newton[i] = -1. * dydt_newton[j];
          // std::cout << "gf_newton[" << i << "]: " << gf_newton[i] << std::endl;
        }

      /*       int dgesv_(integer *n, integer *nrhs, doublereal *a, integer
       * *lda, integer *ipiv, doublereal *b, integer *ldb, integer *info)
       *
       *  -- LAPACK driver routine (version 3.0) --
       *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
       *     Courant Institute, Argonne National Lab, and Rice University
       *     March 31, 1993
       *
       *
       *  Purpose
       *  =======
       *
       *  DGESV computes the solution to a real system of linear equations
       *     A * X = B,
       *  where A is an N-by-N matrix and X and B are N-by-NRHS matrices.
       *
       *  The LU decomposition with partial pivoting and row interchanges is
       *  used to factor A as
       *     A = P * L * U,
       *  where P is a permutation matrix, L is unit lower triangular, and U is
       *  upper triangular.  The factored form of A is then used to solve the
       *  system of equations A * X = B.
       *
       *  Arguments
       *  =========
       *
       *  N       (input) INTEGER
       *          The number of linear equations, i.e., the order of the
       *          matrix A.  N >= 0.
       *
       *  NRHS    (input) INTEGER
       *          The number of right hand sides, i.e., the number of columns
       *          of the matrix B.  NRHS >= 0.
       *
       *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
       *          On entry, the N-by-N coefficient matrix A.
       *          On exit, the factors L and U from the factorization
       *          A = P*L*U; the unit diagonal elements of L are not stored.
       *
       *  LDA     (input) INTEGER
       *          The leading dimension of the array A.  LDA >= max(1,N).
       *
       *  IPIV    (output) INTEGER array, dimension (N)
       *          The pivot indices that define the permutation matrix P;
       *          row i of the matrix was interchanged with row IPIV(i).
       *
       *  B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS)
       *          On entry, the N-by-NRHS matrix of right hand side matrix B.
       *          On exit, if INFO = 0, the N-by-NRHS solution matrix X.
       *
       *  LDB     (input) INTEGER
       *          The leading dimension of the array B.  LDB >= max(1,N).
       *
       *
       * INFO    (output) INTEGER
       *          = 0:  successful exit
       *          < 0:  if INFO = -i, the i-th argument had an illegal value
       *          > 0:  if INFO = i, U(i,i) is exactly zero.  The factorization
       *                has been completed, but the factor U is exactly
       *                singular, so the solution could not be computed.
       */

      dgesv_(&fast, &nrhs, s_22_array.array(), &fast, ipiv.array(), gf_newton.array(), &fast, &ok);

      if (ok != 0)
        {
          info = 2;
          std::cout << "info : dgesv_ ok != 0" << std::endl;
          return;
        }

      for (i = 0; i < fast; i++)
        d_yf[i] = 0;

      for (j = 0; j < fast; j++)
        {
          k = index_metab[j];
          for (i = 0; i < dim; i ++)
            {
              if (i == k)
                d_yf[k] = gf_newton[j];
            }
        }

      err = -10.;
      for (i = 0; i < fast; i++)
        {
          gf_newton[i] = fabs(gf_newton[i]);
          if (err < gf_newton[i])
            err = gf_newton[i];
        }

      iterations = iterations + 1;

      // stop criterion of newton method

      C_FLOAT64 g1, g2;
      if (iter == 1)
        g1 = 3.0 * err;
      else
        g1 = g2;

      g2 = err;

      if (g2 / g1 > 1.0)
        {
          info = 1;
          std::cout << "info : newton stop criterion" << std::endl;
          return;
        }
    } /* end while */

  if (flag_newton == 0)
    {
      for (i = 0; i < dim; i++)
        {
          std::cout << "dyf[" << i << "]: " << d_yf[i] << std::endl;
          std::cout << "y_newton[ " << i << "]: " << y_newton[i] << std::endl;
        }
      std::cout << " end of Newton" << std::endl;
      std::cout << std::endl;
    }

  for (i = 0; i < dim; i++)
    mY_cons[i] = y_newton[i];

  info = 0;

  return;
}

/**
NEWTON for "postprove": Prove of "fast" varibles
Output:  y_consistent, info
 */

void CILDMModifiedMethod::newton_for_timestep(C_INT metabolite_number, C_FLOAT64 & y_consistent, C_INT & info)
{
  C_INT i, iter, itermax, flag_newton;
  iter = 0;
  itermax = 150;

  flag_newton = 1;  // set flag_newton=0 to print the iteration steps

  C_FLOAT64 tol, err;
  tol = 1e-6;
  err = 10.0;

  C_INT dim = mData.dim;

  C_FLOAT64 d_y, deriv;
  d_y = 0;
  deriv = mJacobian_initial(metabolite_number, metabolite_number);

  if (flag_newton == 0)
    {
      std::cout << mpModel->getMetabolitesX()[metabolite_number]->getObjectName() << " - metabolite number: " << metabolite_number << std::endl;
      std::cout << "corresponding term in Jacobian:" << deriv << std::endl;
    }

  if (deriv == 0)
    {
      //  y_consistent = y_newton[metabolite_number];
      std::cout << "Metabolite: " << mpModel->getMetabolitesX()[metabolite_number]->getObjectName() << " seems to be constant " << std::endl;
      return;
    }

  info = 0;

  C_FLOAT64 number2conc = mpModel->getNumber2QuantityFactor()
                          / mpModel->getCompartments()[0]->getInitialValue();

  //this is an ugly hack that only makes sense if all metabs are in the same compartment
  //at the moment is is the only case the algorithm deals with

  CVector<C_FLOAT64> y_newton; //current state converted to concentrations
  y_newton.resize(dim);

  for (i = 0; i < dim; ++i)
    y_newton[i] = mY_initial[i] * number2conc;

  CVector<C_FLOAT64> dydt;
  dydt.resize(dim);

  while (err > tol)
    {
      iter ++;

      if (iter > itermax)
        {
          info = 1;
          std::cout << "iter > itermax " << iter << std::endl;
          break;
        }

      y_newton[metabolite_number] = y_newton[metabolite_number] + d_y;

      calculateDerivativesX(y_newton.array(), dydt.array());

      d_y = - 1 / deriv * dydt[metabolite_number];

      if (flag_newton == 0)
        std::cout << "iteration number: " << iter << " d_y = " << d_y << std::endl;

      if (err > fabs(d_y))
        err = fabs(d_y);
    }

  y_consistent = y_newton[metabolite_number];

  return;
}

/**
 * Empty every vector to be able to fill them with new values for a new calculation.
 * Also nullify the step counter.
 **/
void CILDMModifiedMethod::emptyVectors()
{
  mCurrentStep = 0;
  mVec_mVslow.erase(mVec_mVslow.begin(), mVec_mVslow.end());
  mVec_TimeScale.erase(mVec_TimeScale.begin(), mVec_TimeScale.end());
  mVec_mVslowMetab.erase(mVec_mVslowMetab.begin(), mVec_mVslowMetab.end());
  mVec_mVslowSpace.erase(mVec_mVslowSpace.begin(), mVec_mVslowSpace.end());
  mVec_SlowModes.erase(mVec_SlowModes.begin(), mVec_SlowModes.end());
}

/**
 *upgrade all vectors with values from actually calculalion for current step
 **/
void CILDMModifiedMethod::setVectors(int slowMode)
{
  mVec_mVslow.push_back(mCurrentStep);
  mVec_mVslow[mCurrentStep].resize(mData.dim, mData.dim);
  mVec_mVslow[mCurrentStep] = mVslow;

  mVec_TimeScale.push_back(mCurrentStep);
  mVec_TimeScale[mCurrentStep].resize(mData.dim);
  int i;
  for (i = 0; i < mData.dim; i++)
    mVec_TimeScale[mCurrentStep][i] = -1 / mR(i, i);

  mVec_mVslowMetab.push_back(mCurrentStep);
  mVec_mVslowMetab[mCurrentStep].resize(mData.dim, mData.dim);
  mVec_mVslowMetab[mCurrentStep] = mVslow_metab;

  mVec_mVslowSpace.push_back(mCurrentStep);
  mVec_mVslowSpace[mCurrentStep].resize(mData.dim);
  mVec_mVslowSpace[mCurrentStep] = mVslow_space;

  mVec_mVfastSpace.push_back(mCurrentStep);
  mVec_mVfastSpace[mCurrentStep].resize(mData.dim);
  mVec_mVfastSpace[mCurrentStep] = mVfast_space;

  mVec_SlowModes.push_back(mCurrentStep);
  mVec_SlowModes[mCurrentStep] = slowMode;

  mCurrentTime.push_back(mCurrentStep);
  mCurrentTime[mCurrentStep] = mTime;
}

/**
 * Create the CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget.
 * Input for each CArraAnnotations is a seperate CMatrix.
 **/
void CILDMModifiedMethod::createAnnotationsM()
{
  CArrayAnnotation *
  pTmp1 = new CArrayAnnotation("Unscaled elasticities", this,
                               new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mVslowPrint));
  pTmp1->setMode(0, pTmp1->STRINGS);
  pTmp1->setMode(1, pTmp1->VECTOR);
  pTmp1->setDescription("mVslowPrintAnn matrix");
  //pTmp1->setDimensionDescription(0, "contribution to each mode corresponding to timescale");
  pTmp1->setDimensionDescription(0, "contribution to  mode (TS - corresponding timescale)");
  pTmp1->setDimensionDescription(1, "metabolites");
  pVslowPrintAnn = pTmp1;

  CArrayAnnotation *
  pTmp2 = new CArrayAnnotation("mVslowMetabPrint", this,
                               new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mVslowMetabPrint));
  pTmp2->setMode(1, pTmp2->STRINGS);
  pTmp2->setMode(0, pTmp2->VECTOR);
  pTmp2->setDescription("mVslowMetabPrint matrix");
  pTmp2->setDimensionDescription(0, "mode distribution for each metabolite");
  //pTmp2->setDimensionDescription(1, "modes corresponding to timescale");
  pTmp2->setDimensionDescription(1, "modes (TS - corresponding  timescale)");
  pVslowMetabPrintAnn = pTmp2;

  CArrayAnnotation *
  pTmp3 = new CArrayAnnotation("mVslowSpacePrint", this,
                               new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mVslowSpacePrint));
  pTmp3->setMode(1, pTmp3->STRINGS);
  pTmp3->setMode(0, pTmp3->VECTOR);
  pTmp3->setDescription("mVslowSpacePrint matrix");
  pTmp3->setDimensionDescription(0, "metabolites");
  pTmp3->setDimensionDescription(1, "contribution to slow space");
  pVslowSpacePrintAnn = pTmp3;

  CArrayAnnotation *
  pTmp4 = new CArrayAnnotation("mVfastSpacePrint", this,
                               new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mVfastSpacePrint));
  pTmp4->setMode(1, pTmp4->STRINGS);
  pTmp4->setMode(0, pTmp4->VECTOR);
  pTmp4->setDescription("mVfastSpacePrint matrix");
  pTmp4->setDimensionDescription(0, "metabolites");
  pTmp4->setDimensionDescription(1, "contribution to fast space");
  pVfastSpacePrintAnn = pTmp4;
}
/**
 * Set the every CArrayAnnotation for the requested step.
 * Set also the desription of CArayAnnotation for both dimensions:
 *    - dimension description could consists of some std::srings
 *      some strings contain the Time Scale values for requested step
 *    - dimension description could consists of arrays of CommonNames
 **/
void CILDMModifiedMethod::setAnnotationM(int step)
{
  if (!step) return;
  step -= 1;
  double timeScale;
  std::string str;
  std::stringstream sstr;
  sstr.str("");
  sstr.clear();
  int i;

  mVslowPrint.resize(mData.dim, mData.dim);
  mVslowPrint = mVec_mVslow[step];
  pVslowPrintAnn->resize();
  pVslowPrintAnn->setCopasiVector(1, &mpModel->getMetabolitesX());
  for (i = 0; i < mData.dim; i++)
    {
      timeScale = mVec_TimeScale[step][i];
      if (i < mVec_SlowModes[step])
        sstr << "Slow: ";
      else
        sstr << "Fast: ";
      sstr << timeScale;
      str = sstr.str();
      pVslowPrintAnn->setAnnotationString(0, i, str);
      sstr.str("");
      sstr.clear();
    }

  mVslowMetabPrint.resize(mData.dim, mData.dim);
  mVslowMetabPrint = mVec_mVslowMetab[step];
  pVslowMetabPrintAnn->resize();
  pVslowMetabPrintAnn->setCopasiVector(0, &mpModel->getMetabolitesX());
  for (i = 0; i < mData.dim; i++)
    {
      timeScale = mVec_TimeScale[step][i];
      if (i < mVec_SlowModes[step])
        sstr << "Slow: ";
      else
        sstr << "Fast: ";
      sstr << timeScale;
      str = sstr.str();
      pVslowMetabPrintAnn->setAnnotationString(1, i, str);
      sstr.str("");
      sstr.clear();
    }

  sstr << mVec_SlowModes[step];
  // if (mVec_SlowModes[step] > 1)
  // sstr << " slow modes";
  //else
  // sstr << " slow mode";
  sstr << " slow; ";

  C_INT dim = mData.dim;
  sstr << dim - mVec_SlowModes[step];
  sstr << " fast";

  str = sstr.str();
  mVslowSpacePrint.resize(mData.dim, 1);
  for (i = 0; i < mData.dim; i++)
    mVslowSpacePrint(i, 0) = mVec_mVslowSpace[step][i];
  pVslowSpacePrintAnn->resize();
  pVslowSpacePrintAnn->setCopasiVector(0, &mpModel->getMetabolitesX());
  pVslowSpacePrintAnn->setAnnotationString(1, 0, str);

  mVfastSpacePrint.resize(mData.dim, 1);
  for (i = 0; i < mData.dim; i++)
    mVfastSpacePrint(i, 0) = mVec_mVfastSpace[step][i];
  pVfastSpacePrintAnn->resize();
  pVfastSpacePrintAnn->setCopasiVector(0, &mpModel->getMetabolitesX());
  pVfastSpacePrintAnn->setAnnotationString(1, 0, str);
}
