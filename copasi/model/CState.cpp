/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CState.cpp,v $
   $Revision: 1.50 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/12/20 17:42:39 $
   End CVS Header */

// CSate.cpp
//
// (C) Stefan Hoops 2002
//

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CState.h"
#include "CModel.h"
#include "utilities/CGlobals.h"
#include "utilities/CVector.h"
#include "utilities/utility.h"

/*************************/
/* Code for class CState */
/*************************/

CState::CState(const CModel * pModel):
    mpModel(pModel),
    mTime(0)
{setModel(pModel);}

CState::CState(const CState & state):
    mpModel(state.mpModel),
    mTime(state.mTime),
    mVolumes(state.mVolumes),
    mFixedNumbers(state.mFixedNumbers),
    mVariableNumbers(state.mVariableNumbers)
{}

CState::CState(const CStateX & stateX)
{*this = stateX;}

CState::~CState() {}

//******* assignment operators ***************

CState & CState::operator =(const CStateX & stateX)
{
#ifdef COPASI_DEBUG
  //this->check("operator= lhs");
  stateX.check("operator= rhs");
#endif

  mpModel = stateX.mpModel;
  mTime = stateX.mTime;
  mVolumes = stateX.mVolumes;
  mFixedNumbers = stateX.mFixedNumbers;

  if (mpModel)
    {
      mVariableNumbers.resize(mpModel->getNumVariableMetabs());

      unsigned C_INT32 i, iVariable, iTotal;

      iVariable = stateX.mVariableNumbers.size();
      iTotal = iVariable + stateX.mDependentNumbers.size();

      if (mVariableNumbers.size() != iTotal)
        {
          std::cout << "In CState assignment: Inconsistent src state" << std::endl;
          mVariableNumbers.resize(0);
          return *this;
        }

      const CVector< unsigned C_INT32 > & Permutation =
        mpModel->getMetabolitePermutation();

      C_FLOAT64 * Dbl =
        const_cast< C_FLOAT64 * >(mVariableNumbers.array());

      for (i = 0; i < iVariable; i++)
        {
          *(Dbl + Permutation[i]) = stateX.mVariableNumbers[i];
        }

      for (; i < iTotal; i++)
        {
          *(Dbl + Permutation[i]) =
            stateX.mDependentNumbers[i - iVariable]; //TODO use ptr increments
        }
    }
  else
    {
      mVariableNumbers.resize(0);
    }

  return *this;
}

CState & CState::operator =(const CState & state)
{
#ifdef COPASI_DEBUG
  //this->check("operator= lhs");
  state.check("operator= rhs");
#endif

  mpModel = state.mpModel;
  mTime = state.mTime;
  mVolumes = state.mVolumes;
  mFixedNumbers = state.mFixedNumbers;
  mVariableNumbers = state.mVariableNumbers;

  return *this;
}

//****** set/get methods *******************************

void CState::setTime(const C_FLOAT64 & time) {mTime = time;}

const C_FLOAT64 & CState::getTime() const {return mTime;}

void CState::setModel(const CModel * pModel)
{
  mpModel = pModel;
  if (mpModel)
    {
      mVolumes.resize(mpModel->getCompartments().size());

      mFixedNumbers.resize(mpModel->getNumMetabs() - mpModel->getNumVariableMetabs());
      mVariableNumbers.resize(mpModel->getNumVariableMetabs());
    }
}

const CModel * CState::getModel() const {return mpModel;}

const CVector< C_FLOAT64 > & CState::getFixedNumberVector() const
  {return mFixedNumbers;}

const C_FLOAT64 & CState::getFixedNumber(const unsigned C_INT32 & index) const
  {return mFixedNumbers[index];}

unsigned C_INT32 CState::getFixedNumberSize () const
  {return mFixedNumbers.size();}

const CVector< C_FLOAT64 > & CState::getVariableNumberVector() const
  {return mVariableNumbers;}

const C_FLOAT64 & CState::getVariableNumber(const unsigned C_INT32 & index) const
  {return mVariableNumbers[index];}

unsigned C_INT32 CState::getVariableNumberSize () const
  {return mVariableNumbers.size();}

const C_FLOAT64 & CState::getVolume(const unsigned C_INT32 & index) const
  {return mVolumes[index];}

const CVector< C_FLOAT64 > & CState::getVolumeVector() const {return mVolumes;}

unsigned C_INT32 CState::getVolumeSize() const
  {return mVolumes.size();}

void CState::setFixedNumber(const unsigned C_INT32 & index, const C_FLOAT64 & value)
{mFixedNumbers[index] = value;}

void CState::setFixedNumberVector(const CVector< C_FLOAT64 > & vektor)
{mFixedNumbers = vektor;}

void CState::setVariableNumber(const unsigned C_INT32 & index,
                               const C_FLOAT64 & value)
{mVariableNumbers[index] = value;}

void CState::setVariableNumberVector(const CVector< C_FLOAT64 > & vektor)
{mVariableNumbers = vektor;}

void CState::setVolume(const unsigned C_INT32 & index, const C_FLOAT64 & value)
{mVolumes[index] = value;}

void CState::setVolumeVector(const CVector< C_FLOAT64 > & vektor)
{mVolumes = vektor;}

void CState::calculateJacobian(CMatrix< C_FLOAT64 > & jacobian,
                               const C_FLOAT64 & factor,
                               const C_FLOAT64 & resolution) const
  {
#ifdef COPASI_DEBUG
    this->check("calculate Jacobian");
#endif
    //std::cout << "calculateJacobian" << std::endl;
    const CMatrix< C_FLOAT64 > & Stoi = mpModel->getStoi();
    unsigned C_INT32 mNo = Stoi.numRows();
    unsigned C_INT32 rNo = Stoi.numCols();

    CMatrix< C_FLOAT64 > E(rNo, mNo);
    calculateElasticityMatrix(E, factor, resolution);

    unsigned C_INT32 i, j, k;
    C_FLOAT64 * sum;

    for (i = 0; i < mNo; i++)
      for (j = 0; j < mNo; j++)
        {
          sum = &jacobian(i, j);
          *sum = 0.0;

          for (k = 0; k < rNo; k++)
            *sum += Stoi(i, k) * E(k, j);
        }
  }

/*void CState::getJacobianProtected(CMatrix< C_FLOAT64 > & jacobian,
                                  const C_FLOAT64 & factor,
                                  const C_FLOAT64 & resolution)
{
  unsigned C_INT32 i, j, dim = mVariableNumbers.size();
  C_FLOAT64 * x =
    const_cast<C_FLOAT64 *>(mVariableNumbers.array());
  jacobian.resize(dim, dim);
 
  // constants for differentiation by finite differences
  C_FLOAT64 K1 = 1 + factor;
  C_FLOAT64 K2 = 1 - factor;
  C_FLOAT64 K3 = 2 * factor;
 
  C_FLOAT64 store, temp;
  CVector< C_FLOAT64 > f1(dim);
  CVector< C_FLOAT64 > f2(dim);
 
  for (i = 0; i < dim; i++)
    {
      // if y[i] is zero, the derivative will be calculated at a small
      //  positive value (no point in considering negative values!).
      //  let's stick with SSRes*(1.0+DerivFactor)
 
      store = x[i];
 
      if (store < resolution)
        temp = resolution * K1;
      else
        temp = store;
 
      x[i] = temp * K1;
      const_cast<CModel *>(mpModel)->getDerivatives(this, f1);
 
      x[i] = temp * K2;
      const_cast<CModel *>(mpModel)->getDerivatives(this, f2);
 
      for (j = 0; j < dim; j++)
        jacobian[j][i] = (f1[j] - f2[j]) / (temp * K3);
 
      x[i] = store;
    }
 
  // We need this to reset the model (a bad hack)
  const_cast<CModel *>(mpModel)->getDerivatives(this, f2);
 
  return;
}*/

void CState::calculateElasticityMatrix(CMatrix< C_FLOAT64 > & elasticityMatrix,
                                       const C_FLOAT64 & factor,
                                       const C_FLOAT64 & resolution) const
  {
#ifdef COPASI_DEBUG
    this->check("calculate Elasticity");
#endif
    const_cast<CModel *>(mpModel)->setState(this);
    const CCopasiVectorNS< CReaction > & Reactions = mpModel->getReactions();
    unsigned C_INT32 i, imax = Reactions.size();

    const CCopasiVector< CMetab > & Metabolites = mpModel->getMetabolites();

    unsigned C_INT32 j, jmax = mpModel->getNumVariableMetabs();

    C_FLOAT64 * x;
    C_FLOAT64 invVolume;

    for (j = 0; j < jmax; j++)
      {
        x = const_cast< C_FLOAT64 * >(&Metabolites[j]->getConcentration());
        invVolume = Metabolites[j]->getCompartment()->getVolumeInv();

        for (i = 0; i < imax; i++)
          elasticityMatrix(i, j) = invVolume *    // * UnitFactor/UnitFactor
                                   Reactions[i]->calculatePartialDerivative(*x, factor, resolution);
      }

    return;
  }

std::ostream & operator << (std::ostream & os, const CState & A)
{
  os << "State: " << std::endl;
  os << "  Time:     " << A.mTime << std::endl;
  os << "  Volumes:  " << A.mVolumes;
  os << "  Fixed:    " << A.mFixedNumbers;
  os << "  Variable: " << A.mVariableNumbers << std::endl;

  return os;
}

#ifdef COPASI_DEBUG
void CState::check(const std::string & m) const
  {
    if (!mpModel)
      {
        std::cout << "CState: " << m << ": mpModel==NULL" << std::endl;
        return;
      }

    //mpModel->check();

    if (mFixedNumbers.size() != mpModel->getNumMetabs() - mpModel->getNumVariableMetabs())
    {std::cout << "CState: " << m << ": mismatch in fixedNumbers" << std::endl;}

    if (mVariableNumbers.size() != mpModel->getNumVariableMetabs())
    {std::cout << "CState: " << m << ": mismatch in variableNumbers" << std::endl;}
  }
#endif

//*****************************************************************************

/**************************/
/* Code for class CStateX */
/**************************/
CStateX::CStateX(const CModel * pModel):
    CState()
{setModel(pModel);}

CStateX::CStateX(const CState & state):
    CState()
{*this = state;}

CStateX::CStateX(const CStateX & stateX):
    CState()
{*this = stateX;}

CStateX::~CStateX(){}

CStateX & CStateX::operator =(const CState & state)
{
#ifdef COPASI_DEBUG
  //this->check("operator= lhs");
  state.check("operator= rhs");
#endif
  mpModel = state.mpModel;
  mTime = state.mTime;
  mVolumes = state.mVolumes;
  mFixedNumbers = state.mFixedNumbers;

  if (mpModel)
    {
      mVariableNumbers.resize(mpModel->getNumIndependentMetabs());
      mDependentNumbers.resize(mpModel->getNumDependentMetabs());

      unsigned C_INT32 i, iVariable, iTotal;

      iVariable = mVariableNumbers.size();
      iTotal = iVariable + mDependentNumbers.size();

      if (state.mVariableNumbers.size() != iTotal)
        {
          std::cout << "In CXState assignment: Inconsistent src state" << std::endl;
          mVariableNumbers.resize(0);
          mDependentNumbers.resize(0);
          return *this;
        }

      const CVector< unsigned C_INT32 > & Permutation =
        mpModel->getMetabolitePermutation();

      C_FLOAT64 * Dbl =
        const_cast< C_FLOAT64 * >(mVariableNumbers.array());

      for (i = 0; i < iVariable; i++, Dbl++)
        {
          *Dbl = state.mVariableNumbers[Permutation[i]];
        }

      Dbl = const_cast< C_FLOAT64 * >(mDependentNumbers.array());

      for (i = iVariable; i < iTotal; i++, Dbl++)
        {
          *Dbl = state.mVariableNumbers[Permutation[i]];
        }
    }
  else
    {
      mVariableNumbers.resize(0);
      mDependentNumbers.resize(0);
    }

  return *this;
}

CStateX & CStateX::operator =(const CStateX & stateX)
{
#ifdef COPASI_DEBUG
  //this->check("operator= lhs");
  stateX.check("operator= rhs");
#endif
  mpModel = stateX.mpModel;
  mTime = stateX.mTime;
  mVolumes = stateX.mVolumes;
  mFixedNumbers = stateX.mFixedNumbers;
  mVariableNumbers = stateX.mVariableNumbers;
  mDependentNumbers = stateX.mDependentNumbers;

  return *this;
}

//*****************************************************************

void CStateX::setModel(const CModel * pModel)
{
  mpModel = pModel;
  if (mpModel)
    {
      mVolumes.resize(mpModel->getCompartments().size());

      mFixedNumbers.resize(mpModel->getNumMetabs() - mpModel->getNumVariableMetabs());
      mVariableNumbers.resize(mpModel->getNumIndependentMetabs());
      mDependentNumbers.resize(mpModel->getNumDependentMetabs());
    }
}

const CVector< C_FLOAT64 > & CStateX::getDependentNumberVector() const
  {return mDependentNumbers;}

const C_FLOAT64 & CStateX::getDependentNumber(const unsigned C_INT32 & index) const
  {return mDependentNumbers[index];}

unsigned C_INT32 CStateX::getDependentNumberSize () const
  {return mDependentNumbers.size();}

void CStateX::setDependentNumber(const unsigned C_INT32 & index,
                                 const C_FLOAT64 & value)
{mDependentNumbers[index] = value;}

void CStateX::setDependentNumberVector(const CVector< C_FLOAT64 > & vektor)
{mDependentNumbers = vektor;}

void CStateX::calculateJacobian(CMatrix< C_FLOAT64 > & jacobian,
                                const C_FLOAT64 & factor,
                                const C_FLOAT64 & resolution) const
  {
#ifdef COPASI_DEBUG
    this->check("calculate Jacobian");
#endif
    //std::cout << "calculateJacobianX" << std::endl;
    const CModel::CLinkMatrixView & L = mpModel->getL();
    unsigned C_INT32 mNo = L.numRows();
    unsigned C_INT32 iNo = L.numCols();

    const CMatrix< C_FLOAT64 > & redStoi = mpModel->getRedStoi();
    unsigned C_INT32 rNo = redStoi.numCols();

    CMatrix< C_FLOAT64 > E(rNo, mNo);
    calculateElasticityMatrix(E, factor, resolution);

    CMatrix< C_FLOAT64 > tmp(rNo, iNo);

    unsigned C_INT32 i, j, k;
    C_FLOAT64 * sum;

    for (i = 0; i < rNo; i++)
      for (j = 0; j < iNo; j++)
        {
          sum = &tmp(i, j);
          *sum = E(i, j);

          for (k = iNo; k < mNo; k++)
            *sum += E(i, k) * L(k, j);
        }

    for (i = 0; i < iNo; i++)
      for (j = 0; j < iNo; j++)
        {
          sum = &jacobian(i, j);
          *sum = 0.0;

          for (k = 0; k < rNo; k++)
            *sum += redStoi(i, k) * tmp(k, j);
        }
  }

void CStateX::updateDependentNumbers()
{
#ifdef COPASI_DEBUG
  this->check("update dependent numbers");
#endif

  mpModel->updateDepMetabNumbers(*this);
}

/*void CStateX::getJacobianProtected(CMatrix< C_FLOAT64 > & jacobian,
                                   const C_FLOAT64 & factor,
                                   const C_FLOAT64 & resolution)
{
  unsigned C_INT32 i, j, dim = mVariableNumbers.size();
  C_FLOAT64 * x =
    const_cast<C_FLOAT64 *>(mVariableNumbers.array());
  jacobian.resize(dim, dim);
 
  // constants for differentiation by finite differences
  C_FLOAT64 K1 = 1 + factor;
  C_FLOAT64 K2 = 1 - factor;
  C_FLOAT64 K3 = 2 * factor;
 
  C_FLOAT64 store, temp;
  CVector< C_FLOAT64 > f1(dim);
  CVector< C_FLOAT64 > f2(dim);
 
  for (i = 0; i < dim; i++)
    {
      // if x[i] is zero, the derivative will be calculated at a small
      // positive value (no point in considering negative values!).
      // let's stick with SSRes*(1.0+DerivFactor)
      store = x[i];
 
      if (store < resolution)
        temp = resolution * K1;
      else
        temp = store;
 
      x[i] = temp * K1;
      const_cast<CModel *>(mpModel)->getDerivatives(this, f1);
 
      x[i] = temp * K2;
      const_cast<CModel *>(mpModel)->getDerivatives(this, f2);
 
      for (j = 0; j < dim; j++)
        jacobian[j][i] = (f1[j] - f2[j]) / (temp * K3);
 
      x[i] = store;
    }
 
  // We need this to reset the model (a bad hack)
  const_cast<CModel *>(mpModel)->getDerivatives(this, f2);
 
  return;
}*/

void CStateX::calculateElasticityMatrix(CMatrix< C_FLOAT64 > & elasticityMatrix,
                                        const C_FLOAT64 & factor,
                                        const C_FLOAT64 & resolution) const
  {
#ifdef COPASI_DEBUG
    this->check("calculate elasticities");
#endif
    const_cast<CModel *>(mpModel)->setStateX(this);
    const CCopasiVector< CReaction > & Reactions = mpModel->getReactionsX();
    unsigned C_INT32 i, imax = Reactions.size();

    const CCopasiVector< CMetab > & Metabolites = mpModel->getMetabolitesX();
    unsigned C_INT32 j, jmax = mpModel->getNumVariableMetabs();

    C_FLOAT64 * x;
    C_FLOAT64 invVolume;

    for (j = 0; j < jmax; j++)
      {
        x = const_cast< C_FLOAT64 * >(&Metabolites[j]->getConcentration());
        invVolume = Metabolites[j]->getCompartment()->getVolumeInv();

        for (i = 0; i < imax; i++)
          {
            elasticityMatrix(i, j) = invVolume *    // * UnitFactor/UnitFactor
                                     Reactions[i]->calculatePartialDerivative(*x, factor, resolution);
          }
      }

    //    DebugFile << "Elasiticity Matrix: " << elasticityMatrix << std::endl;
    return;
  }

std::ostream & operator << (std::ostream & os, const CStateX & A)
{
  os << "StateX" << std::endl;
  os << "  Time:        " << A.mTime << std::endl;
  os << "  Volumes:     " << A.mVolumes;
  os << "  Fixed:       " << A.mFixedNumbers;
  os << "  Independend: " << A.mVariableNumbers;
  os << "  Dependend:   " << A.mDependentNumbers << std::endl;

  return os;
}

#ifdef COPASI_DEBUG
void CStateX::check(const std::string & m) const
  {
    if (!mpModel)
      {
        std::cout << "CStateX: " << m << ": mpModel==NULL" << std::endl;
        return;
      }

    mpModel->check();

    if (mFixedNumbers.size() != mpModel->getNumMetabs() - mpModel->getNumVariableMetabs())
    {std::cout << "CStateX: " << m << ": mismatch in fixedNumbers" << std::endl;}

    if (mVariableNumbers.size() != mpModel->getNumIndependentMetabs())
    {std::cout << "CStateX: " << m << ": mismatch in independentNumbers" << std::endl;}

    if (mDependentNumbers.size() != mpModel->getNumDependentMetabs())
    {std::cout << "CStateX: " << m << ": mismatch in dependentNumbers" << std::endl;}
  }
#endif
