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

CState & CState::operator =(const CStateX & stateX)
{
  if (mpModel != stateX.mpModel)
    {
      mpModel = stateX.mpModel;

      if (mpModel)
        mVariableNumbers.resize(mpModel->getIntMetab());
      else
        mVariableNumbers.resize(0);
    }

  mTime = stateX.mTime;
  mVolumes = stateX.mVolumes;
  mFixedNumbers = stateX.mFixedNumbers;

  if (mpModel)
    {
      unsigned C_INT32 i, iVariable, iTotal;

      iVariable = stateX.mVariableNumbers.size();
      iTotal = iVariable + stateX.mDependentNumbers.size();

      const CVector< unsigned C_INT32 > & Permutation =
        mpModel->getMetabolitePermutation();

      /* We have to set the Dbl and Int representation independently
         since we do not know which was the last updated one.
         In theory it should always suffice to use set method with Dbl. */

      C_FLOAT64 * Dbl =
        const_cast< C_FLOAT64 * >(mVariableNumbers.getVectorDbl().array());
      C_INT32 * Int =
        const_cast< C_INT32 * >(mVariableNumbers.getVectorInt().array());

      for (i = 0; i < iVariable; i++)
        {
          *(Dbl + Permutation[i]) = stateX.mVariableNumbers.getDbl(i);
          *(Int + Permutation[i]) = stateX.mVariableNumbers.getInt(i);
        }

      for (; i < iTotal; i++)
        {
          *(Dbl + Permutation[i]) =
            stateX.mDependentNumbers.getDbl(i - iVariable);
          *(Int + Permutation[i]) =
            stateX.mDependentNumbers.getInt(i - iVariable);
        }
    }

  return *this;
}

CState & CState::operator =(const CState & state)
{
  mpModel = state.mpModel;
  mTime = state.mTime;
  mVolumes = state.mVolumes;
  mFixedNumbers = state.mFixedNumbers;
  mVariableNumbers = state.mVariableNumbers;

  return *this;
}

void CState::load(CReadConfig & configBuffer)
{
  std::string Tmp;
  C_FLOAT64 Dbl;
  C_INT32 Size;
  unsigned C_INT32 i;

  /* Make sure that the state fits the currently loaded model */
  configBuffer.getVariable("State.Model", "string", &Tmp);
  if (Tmp == Copasi->pModel->getTitle())
    setModel(Copasi->pModel);
  else
    fatalError();

  configBuffer.getVariable("State.Time", "C_FLOAT64", &mTime);

  configBuffer.getVariable("State.VolumeSize", "C_INT32", &Size);
  if (mpModel->getCompartments().size() != (unsigned C_INT32) Size)
    fatalError();
  mVolumes.resize(Size);

  for (i = 0; i < (unsigned C_INT32) Size; i++)
    {
      Tmp = StringPrint("State.Volume[%ld]", i);
      configBuffer.getVariable(Tmp, "C_FLOAT64", & mVolumes[i]);
    }

  configBuffer.getVariable("State.FixedNumberSize", "C_INT32", &Size);
  if ((unsigned C_INT32) Size != mFixedNumbers.size()) fatalError();

  for (i = 0; i < mFixedNumbers.size(); i++)
    {
      Tmp = StringPrint("State.FixedNumber[%ld]", i);
      configBuffer.getVariable(Tmp, "C_FLOAT64", & Dbl);
      mFixedNumbers.set(i, Dbl);
    }

  configBuffer.getVariable("State.VariableNumberSize", "C_INT32", &Size);
  if ((unsigned C_INT32) Size != mVariableNumbers.size()) fatalError();

  for (i = 0; i < mVariableNumbers.size(); i++)
    {
      Tmp = StringPrint("State.VariableNumber[%ld]", i);
      configBuffer.getVariable(Tmp, "C_FLOAT64", & Dbl);
      mVariableNumbers.set(i, Dbl);
    }

  return;
}

void CState::save(CWriteConfig & configBuffer) const
  {
    std::string Tmp;
    C_FLOAT64 Dbl;
    C_INT32 Size;
    unsigned C_INT32 i;

    Tmp = mpModel->getTitle();
    configBuffer.setVariable("State.Model", "string", &Tmp);

    configBuffer.setVariable("State.Time", "C_FLOAT64", &mTime);

    Size = mVolumes.size();
    configBuffer.setVariable("State.VolumeSize", "C_INT32", &Size);

    for (i = 0; i < (unsigned C_INT32) Size; i++)
      {
        Tmp = StringPrint("State.Volume[%ld]", i);
        configBuffer.setVariable(Tmp, "C_FLOAT64", &mVolumes[i]);
      }

    Size = mFixedNumbers.size();
    configBuffer.setVariable("State.FixedNumberSize", "C_INT32", &Size);

    for (i = 0; i < mFixedNumbers.size(); i++)
      {
        Dbl = mFixedNumbers.getDbl(i);
        Tmp = StringPrint("State.FixedNumber[%ld]", i);
        configBuffer.setVariable(Tmp, "C_FLOAT64", & Dbl);
      }

    Size = mVariableNumbers.size();
    configBuffer.setVariable("State.VariableNumberSize", "C_INT32", &Size);

    for (i = 0; i < mVariableNumbers.size(); i++)
      {
        Dbl = mVariableNumbers.getDbl(i);
        Tmp = StringPrint("State.VariableNumber[%ld]", i);
        configBuffer.setVariable(Tmp, "C_FLOAT64", & Dbl);
      }

    return;
  }

void CState::setTime(const C_FLOAT64 & time) {mTime = time;}

const C_FLOAT64 & CState::getTime() const {return mTime;}

void CState::setModel(const CModel * pModel)
{
  mpModel = pModel;
  if (mpModel)
    {
      mVolumes.resize(mpModel->getCompartments().size());

      mFixedNumbers.resize(mpModel->getTotMetab() - mpModel->getIntMetab());
      mVariableNumbers.resize(mpModel->getIntMetab());
    }
}

const CModel * CState::getModel() const {return mpModel;}

const CVector< C_FLOAT64 > & CState::getFixedNumberVectorDbl() const
  {return mFixedNumbers.getVectorDbl();}

const CVector< C_INT32 > & CState::getFixedNumberVectorInt() const
  {return mFixedNumbers.getVectorInt();}

const C_FLOAT64 & CState::getFixedNumberDbl(const unsigned C_INT32 & index) const
  {return mFixedNumbers.getDbl(index);}

const C_INT32 & CState::getFixedNumberInt(const unsigned C_INT32 & index) const
  {return mFixedNumbers.getInt(index);}

const unsigned C_INT32 & CState::getFixedNumberSize () const
  {return mFixedNumbers.size();}

const CVector< C_FLOAT64 > & CState::getVariableNumberVectorDbl() const
  {return mVariableNumbers.getVectorDbl();}

const CVector< C_INT32 > & CState::getVariableNumberVectorInt() const
  {return mVariableNumbers.getVectorInt();}

const C_FLOAT64 & CState::getVariableNumberDbl(const unsigned C_INT32 & index) const
  {return mVariableNumbers.getDbl(index);}

const C_INT32 & CState::getVariableNumberInt(const unsigned C_INT32 & index) const
  {return mVariableNumbers.getInt(index);}

const unsigned C_INT32 & CState::getVariableNumberSize () const
  {return mVariableNumbers.size();}

const C_FLOAT64 & CState::getVolume(const unsigned C_INT32 & index) const
  {return mVolumes[index];}

const CVector< C_FLOAT64 > & CState::getVolumeVector() const {return mVolumes;}

unsigned C_INT32 CState::getVolumeSize() const
  {return mVolumes.size();}

void CState::setFixedNumber(const unsigned C_INT32 & index, const C_INT32 & value)
{mFixedNumbers.set(index, value);}

void CState::setFixedNumber(const unsigned C_INT32 & index, const C_FLOAT64 & value)
{mFixedNumbers.set(index, value);}

void CState::setFixedNumberVector(const CVector< C_INT32 > & vektor)
{mFixedNumbers.setVector(vektor);}

void CState::setFixedNumberVector(const CVector< C_FLOAT64 > & vektor)
{mFixedNumbers.setVector(vektor);}

void CState::setVariableNumber(const unsigned C_INT32 & index,
                               const C_INT32 & value)
{mVariableNumbers.set(index, value);}

void CState::setVariableNumber(const unsigned C_INT32 & index,
                               const C_FLOAT64 & value)
{mVariableNumbers.set(index, value);}

void CState::setVariableNumberVector(const CVector< C_INT32 > & vektor)
{mVariableNumbers.setVector(vektor);}

void CState::setVariableNumberVector(const CVector< C_FLOAT64 > & vektor)
{mVariableNumbers.setVector(vektor);}

void CState::setVolume(const unsigned C_INT32 & index, const C_FLOAT64 & value)
{mVolumes[index] = value;}

void CState::setVolumeVector(const CVector< C_FLOAT64 > & vektor)
{mVolumes = vektor;}

void CState::getJacobian(CMatrix< C_FLOAT64 > & jacobian,
                         const C_FLOAT64 & factor,
                         const C_FLOAT64 & resolution) const
  {
    const CMatrix< C_FLOAT64 > & Stoi = mpModel->getStoi();
    unsigned C_INT32 mNo = Stoi.numRows();
    unsigned C_INT32 rNo = Stoi.numCols();

    CMatrix< C_FLOAT64 > E(rNo, mNo);
    getElasticityMatrix(E, factor, resolution);

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

void CState::getJacobianProtected(CMatrix< C_FLOAT64 > & jacobian,
                                  const C_FLOAT64 & factor,
                                  const C_FLOAT64 & resolution)
{
  unsigned C_INT32 i, j, dim = mVariableNumbers.size();
  C_FLOAT64 * x =
    const_cast<C_FLOAT64 *>(mVariableNumbers.getVectorDbl().array());
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
      /** if y[i] is zero, the derivative will be calculated at a small
       *  positive value (no point in considering negative values!).
       *  let's stick with SSRes*(1.0+DerivFactor)
       */

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
}

void CState::getElasticityMatrix(CMatrix< C_FLOAT64 > & elasticityMatrix,
                                 const C_FLOAT64 & factor,
                                 const C_FLOAT64 & resolution) const
  {
    const_cast<CModel *>(mpModel)->setState(this);
    const CCopasiVectorNS< CReaction > & Reactions = mpModel->getReactions();
    unsigned C_INT32 i, imax = Reactions.size();

    const CCopasiVectorN< CMetab > & Metabolites = mpModel->getMetabolites();

    unsigned C_INT32 j, jmax = mpModel->getIntMetab();

    C_FLOAT64 * x;

    for (j = 0; j < jmax; j++)
      {
        x = const_cast< C_FLOAT64 * >(&Metabolites[j]->getConcentration());

        for (i = 0; i < imax; i++)
          elasticityMatrix(i, j) =
            Reactions[i]->calculatePartialDerivative(*x, factor, resolution);
      }

    return;
  }

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
  if (mpModel != state.mpModel)
    {
      mpModel = state.mpModel;

      if (mpModel)
        {
          mVariableNumbers.resize(mpModel->getIndMetab());
          mDependentNumbers.resize(mpModel->getDepMetab());
        }
      else
        {
          mVariableNumbers.resize(0);
          mDependentNumbers.resize(0);
        }
    }

  mTime = state.mTime;
  mVolumes = state.mVolumes;
  mFixedNumbers = state.mFixedNumbers;

  if (mpModel)
    {
      unsigned C_INT32 i, iVariable, iTotal;

      iVariable = mVariableNumbers.size();
      iTotal = iVariable + mDependentNumbers.size();

      const CVector< unsigned C_INT32 > & Permutation =
        mpModel->getMetabolitePermutation();

      /* We have to set the Dbl and Int representation independently
         since we do not know which was the last updated one.
         In theory it should always suffice to use set method with Dbl. */

      C_FLOAT64 * Dbl =
        const_cast< C_FLOAT64 * >(mVariableNumbers.getVectorDbl().array());
      C_INT32 * Int =
        const_cast< C_INT32 * >(mVariableNumbers.getVectorInt().array());

      for (i = 0; i < iVariable; i++, Dbl++, Int++)
        {
          *Dbl = state.mVariableNumbers.getDbl(Permutation[i]);
          *Int = state.mVariableNumbers.getInt(Permutation[i]);
        }

      Dbl = const_cast< C_FLOAT64 * >(mDependentNumbers.getVectorDbl().array());
      Int = const_cast< C_INT32 * >(mDependentNumbers.getVectorInt().array());

      for (i = iVariable; i < iTotal; i++, Dbl++, Int++)
        {
          *Dbl = state.mVariableNumbers.getDbl(Permutation[i]);
          *Int = state.mVariableNumbers.getInt(Permutation[i]);
        }
    }

  return *this;
}

CStateX & CStateX::operator =(const CStateX & stateX)
{
  mpModel = stateX.mpModel;
  mTime = stateX.mTime;
  mVolumes = stateX.mVolumes;
  mFixedNumbers = stateX.mFixedNumbers;
  mVariableNumbers = stateX.mVariableNumbers;
  mDependentNumbers = stateX.mDependentNumbers;

  return *this;
}

void CStateX::load(CReadConfig & configBuffer)
{
  CState State;
  State.load(configBuffer);
  *this = State;

  return;
}

void CStateX::save(CWriteConfig & configBuffer)
{
  CState State(*this);
  State.save(configBuffer);

  return;
}

void CStateX::setModel(const CModel * pModel)
{
  mpModel = pModel;
  if (mpModel)
    {
      mVolumes.resize(mpModel->getCompartments().size());

      mFixedNumbers.resize(mpModel->getTotMetab() - mpModel->getIntMetab());
      mVariableNumbers.resize(mpModel->getIndMetab());
      mDependentNumbers.resize(mpModel->getDepMetab());
    }
}

const CVector< C_FLOAT64 > & CStateX::getDependentNumberVectorDbl() const
  {return mDependentNumbers.getVectorDbl();}

const CVector< C_INT32 > & CStateX::getDependentNumberVectorInt() const
  {return mDependentNumbers.getVectorInt();}

const C_FLOAT64 & CStateX::getDependentNumberDbl(const unsigned C_INT32 & index) const
  {return mDependentNumbers.getDbl(index);}

const C_INT32 & CStateX::getDependentNumberInt(const unsigned C_INT32 & index) const
  {return mDependentNumbers.getInt(index);}

const unsigned C_INT32 & CStateX::getDependentNumberSize () const
  {return mDependentNumbers.size();}

void CStateX::setDependentNumber(const unsigned C_INT32 & index,
                                 const C_INT32 & value)
{mDependentNumbers.set(index, value);}

void CStateX::setDependentNumber(const unsigned C_INT32 & index,
                                 const C_FLOAT64 & value)
{mDependentNumbers.set(index, value);}

void CStateX::setDependentNumberVector(const CVector< C_INT32 > & vektor)
{mDependentNumbers.setVector(vektor);}

void CStateX::setDependentNumberVector(const CVector< C_FLOAT64 > & vektor)
{mDependentNumbers.setVector(vektor);}

void CStateX::getJacobian(CMatrix< C_FLOAT64 > & jacobian,
                          const C_FLOAT64 & factor,
                          const C_FLOAT64 & resolution) const
  {
    const CModel::CLinkMatrixView & L = mpModel->getL();
    unsigned C_INT32 mNo = L.numRows();
    unsigned C_INT32 iNo = L.numCols();

    const CMatrix< C_FLOAT64 > & redStoi = mpModel->getRedStoi();
    unsigned C_INT32 rNo = redStoi.numCols();

    CMatrix< C_FLOAT64 > E(rNo, mNo);
    getElasticityMatrix(E, factor, resolution);

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
{mpModel->updateDepMetabNumbers(*this);}

void CStateX::getJacobianProtected(CMatrix< C_FLOAT64 > & jacobian,
                                   const C_FLOAT64 & factor,
                                   const C_FLOAT64 & resolution)
{
  unsigned C_INT32 i, j, dim = mVariableNumbers.size();
  C_FLOAT64 * x =
    const_cast<C_FLOAT64 *>(mVariableNumbers.getVectorDbl().array());
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
      /** if x[i] is zero, the derivative will be calculated at a small
       *  positive value (no point in considering negative values!).
       *  let's stick with SSRes*(1.0+DerivFactor)
       */

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
}

void CStateX::getElasticityMatrix(CMatrix< C_FLOAT64 > & elasticityMatrix,
                                  const C_FLOAT64 & factor,
                                  const C_FLOAT64 & resolution) const
  {
    const_cast<CModel *>(mpModel)->setState(this);
    const CCopasiVector< CReaction > & Reactions = mpModel->getReactionsX();
    unsigned C_INT32 i, imax = Reactions.size();

    const CCopasiVectorN< CMetab > & Metabolites = mpModel->getMetabolitesX();
    unsigned C_INT32 j, jmax = mpModel->getIntMetab();

    C_FLOAT64 * x;

    for (j = 0; j < jmax; j++)
      {
        x = const_cast< C_FLOAT64 * >(&Metabolites[j]->getConcentration());

        for (i = 0; i < imax; i++)
          {
            elasticityMatrix(i, j) =
              Reactions[i]->calculatePartialDerivative(*x, factor, resolution);
          }
      }

    DebugFile << "Elasiticity Matrix: " << elasticityMatrix << std::endl;
    return;
  }
