// CSate.cpp
//
// (C) Stefan Hoops 2002
//

#define  COPASI_TRACE_CONSTRUCTION

#include "tnt/tnt.h"
#include "tnt/cmat.h"

#include "copasi.h"
#include "CState.h"
#include "CModel.h"
#include "utilities/CGlobals.h"

/*************************/
/* Code for class CState */
/*************************/
CState::CState(const CModel * pModel):
    mpModel(NULL),
    mTime(0),
    mVolumeSize(0),
    mVolumes(NULL)
{if (pModel)
  setModel(pModel);}

CState::CState(const CState & state):
    mTime(0),
    mVolumeSize(0),
    mVolumes(NULL)
{*this = state;}

CState::CState(const CStateX & stateX):
    mTime(0),
    mVolumeSize(0),
    mVolumes(NULL)
{*this = stateX;}

CState::~CState() {cleanup();}

CState & CState::operator =(const CStateX & stateX)
{
  if (mpModel != stateX.getModel())
    setModel(stateX.getModel());

  mTime = stateX.getTime();

  if (mpModel)
    {
      unsigned C_INT32 i, iVariable, iTotal;
      iVariable = stateX.getVariableNumberSize();
      iTotal = iVariable + stateX.getDependentNumberSize();

      const vector <unsigned C_INT32> & Permutation =
        mpModel->getMetabolitePermutation();

      if (mVolumeSize)
        memcpy(mVolumes, stateX.getVolumeArray(), mVolumeSize * sizeof(double));

      for (i = 0; i < iVariable; i++)
        mVariableNumbers.set(Permutation[i], stateX.getVariableNumberDbl(i));

      for (; i < iTotal; i++)
        mVariableNumbers.set(Permutation[i],
                             stateX.getDependentNumberDbl(i - iVariable));

      mFixedNumbers.setArray(stateX.getFixedNumberArrayDbl());
    }

  return *this;
}

CState & CState::operator =(const CState & state)
{
  if (mpModel != state.getModel())
    setModel(state.getModel());

  mTime = state.getTime();

  if (mpModel)
    {
      if (mVolumeSize)
        memcpy(mVolumes, state.getVolumeArray(), mVolumeSize * sizeof(double));

      mVariableNumbers.setArray(state.getVariableNumberArrayDbl());
      mFixedNumbers.setArray(state.getFixedNumberArrayDbl());
    }

  return *this;
}

void CState::load(CReadConfig & configBuffer)
{
  string Tmp;
  C_FLOAT64 Dbl;
  C_INT32 Size;
  unsigned C_INT32 i;

  /* Make sure that the state fits the currently loaded model */
  configBuffer.getVariable("StateModel", "string", &Tmp);
  if (Tmp == Copasi->Model->getTitle())
    setModel(Copasi->Model);
  else
    fatalError();

  configBuffer.getVariable("StateTime", "C_FLOAT64", &mTime);

  configBuffer.getVariable("StateVolumeSize", "C_INT32", &Size);
  if ((unsigned C_INT32) Size != mVolumeSize)
    fatalError();

  for (i = 0; i < mVolumeSize; i++)
    {
      Tmp = StringPrint("StateVolume[%ld]", i);
      configBuffer.getVariable(Tmp, "C_FLOAT64", & mVolumes[i]);
    }

  configBuffer.getVariable("StateVariableNumberSize", "C_INT32", &Size);
  if ((unsigned C_INT32) Size != mVariableNumbers.size())
    fatalError();

  for (i = 0; i < mVariableNumbers.size(); i++)
    {
      Tmp = StringPrint("StateVariableNumber[%ld]", i);
      configBuffer.getVariable(Tmp, "C_FLOAT64", & Dbl);
      mVariableNumbers.set(i, Dbl);
    }

  configBuffer.getVariable("StateFixedNumberSize", "C_INT32", &Size);
  if ((unsigned C_INT32) Size != mFixedNumbers.size())
    fatalError();

  for (i = 0; i < mFixedNumbers.size(); i++)
    {
      Tmp = StringPrint("StateFixedNumber[%ld]", i);
      configBuffer.getVariable(Tmp, "C_FLOAT64", & Dbl);
      mFixedNumbers.set(i, Dbl);
    }

  return;
}

void CState::save(CWriteConfig & configBuffer)
{
  string Tmp;
  C_FLOAT64 Dbl;
  C_INT32 Size;
  unsigned C_INT32 i;

  Tmp = mpModel->getTitle();
  configBuffer.setVariable("StateModel", "string", &Tmp);

  configBuffer.setVariable("StateTime", "C_FLOAT64", &mTime);

  configBuffer.setVariable("StateVolumeSize", "C_INT32", &mVolumeSize);

  for (i = 0; i < mVolumeSize; i++)
    {
      Tmp = StringPrint("StateVolume[%ld]", i);
      configBuffer.setVariable(Tmp, "C_FLOAT64", &mVolumes[i]);
    }

  Size = mVariableNumbers.size();
  configBuffer.setVariable("StateVariableNumberSize", "C_INT32", &Size);

  for (i = 0; i < mVariableNumbers.size(); i++)
    {
      Dbl = mVariableNumbers.getDbl(i);
      Tmp = StringPrint("StateVariableNumber[%ld]", i);
      configBuffer.setVariable(Tmp, "C_FLOAT64", & Dbl);
    }

  Size = mFixedNumbers.size();
  configBuffer.setVariable("StateFixedNumberSize", "C_INT32", &Size);

  for (i = 0; i < mFixedNumbers.size(); i++)
    {
      Dbl = mFixedNumbers.getDbl(i);
      Tmp = StringPrint("StateFixedNumber[%ld]", i);
      configBuffer.setVariable(Tmp, "C_FLOAT64", & Dbl);
    }

  return;
}

void CState::setTime(const C_FLOAT64 & time) {mTime = time;}

const C_FLOAT64 & CState::getTime() const {return mTime;}

void CState::setModel(const CModel * pModel)
{
  cleanup();

  mpModel = pModel;
  if (mpModel)
    {
      mVolumeSize = mpModel->getCompartments().size();
      mVolumes = new double[mVolumeSize];

      mVariableNumbers.resize(mpModel->getIntMetab());
      mFixedNumbers.resize(mpModel->getTotMetab() - mpModel->getIntMetab());
    }
}

const CModel * CState::getModel() const {return mpModel;}

const C_FLOAT64 * CState::getFixedNumberArrayDbl() const
  {return mFixedNumbers.getDblArray();}

const C_INT32 * CState::getFixedNumberArrayInt() const
  {return mFixedNumbers.getIntArray();}

const C_FLOAT64 & CState::getFixedNumberDbl(const unsigned C_INT32 & index) const
  {return mFixedNumbers.getDbl(index);}

const C_INT32 & CState::getFixedNumberInt(const unsigned C_INT32 & index) const
  {return mFixedNumbers.getInt(index);}

const unsigned C_INT32 & CState::getFixedNumberSize () const
  {return mFixedNumbers.size();}

const C_FLOAT64 * CState::getVariableNumberArrayDbl() const
  {return mVariableNumbers.getDblArray();}

const C_INT32 * CState::getVariableNumberArrayInt() const
  {return mVariableNumbers.getIntArray();}

const C_FLOAT64 & CState::getVariableNumberDbl(const unsigned C_INT32 & index) const
  {return mVariableNumbers.getDbl(index);}

const C_INT32 & CState::getVariableNumberInt(const unsigned C_INT32 & index) const
  {return mVariableNumbers.getInt(index);}

const unsigned C_INT32 & CState::getVariableNumberSize () const
  {return mVariableNumbers.size();}

const C_FLOAT64 & CState::getVolume(const unsigned C_INT32 & index) const
  {return mVolumes[index];}

const C_FLOAT64 * CState::getVolumeArray() const {return mVolumes;}

const unsigned C_INT32 & CState::getVolumeSize() const
  {return mVolumeSize;}

void CState::setFixedNumber(const unsigned C_INT32 & index, const C_INT32 & value)
{mFixedNumbers.set(index, value);}

void CState::setFixedNumber(const unsigned C_INT32 & index, const C_FLOAT64 & value)
{mFixedNumbers.set(index, value);}

void CState::setFixedNumberArray(const C_INT32 * values)
{mFixedNumbers.setArray(values);}

void CState::setFixedNumberArray(const C_FLOAT64 * values)
{mFixedNumbers.setArray(values);}

void CState::setVariableNumber(const unsigned C_INT32 & index,
                               const C_INT32 & value)
{mVariableNumbers.set(index, value);}

void CState::setVariableNumber(const unsigned C_INT32 & index,
                               const C_FLOAT64 & value)
{mVariableNumbers.set(index, value);}

void CState::setVariableNumberArray(const C_INT32 * values)
{mVariableNumbers.setArray(values);}

void CState::setVariableNumberArray(const C_FLOAT64 * values)
{mVariableNumbers.setArray(values);}

void CState::setVolume(const unsigned C_INT32 & index, const C_FLOAT64 & value)
{mVolumes[index] = value;}

void CState::setVolumeArray(const C_FLOAT64 * values)
{memcpy(mVolumes, values, mVolumeSize * sizeof(double));}

void CState::getJacobian(C_FLOAT64 * jacobian,
                         const C_FLOAT64 & factor,
                         const C_FLOAT64 & resolution) const
  {
    CState tmp(*this);
    tmp.getJacobianProtected(jacobian, factor, resolution);
  }

void CState::cleanup()
{
  mTime = 0;
  mVolumeSize = 0;
  pdelete(mVolumes);

  mVariableNumbers.resize(0);
  mFixedNumbers.resize(0);
}

void CState::getJacobianProtected(C_FLOAT64 * jacobian,
                                  const C_FLOAT64 & factor,
                                  const C_FLOAT64 & resolution)
{
  unsigned C_INT32 i, j, dim = mVariableNumbers.size();
  C_FLOAT64 * x =
    const_cast<C_FLOAT64 *>(mVariableNumbers.getDblArray());

  // constants for differentiation by finite differences
  C_FLOAT64 K1 = 1 + factor;
  C_FLOAT64 K2 = 1 - factor;
  C_FLOAT64 K3 = 2 * factor;

  C_FLOAT64 store, temp;
  C_FLOAT64 * f1 = new C_FLOAT64 [dim];
  C_FLOAT64 * f2 = new C_FLOAT64 [dim];

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
        jacobian[j * dim + i] = (f1[j] - f2[j]) / (temp * K3);

      x[i] = store;
    }

  // We need this to reset the model (a bad hack)
  const_cast<CModel *>(mpModel)->getDerivatives(this, f2);

  delete [] f1;
  delete [] f2;

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

CStateX::~CStateX(){cleanup();}

CStateX & CStateX::operator =(const CState & state)
{
  if (mpModel != state.getModel())
    setModel(state.getModel());

  mTime = state.getTime();

  if (mpModel)
    {
      unsigned C_INT32 i, iVariable, iTotal;
      iVariable = mVariableNumbers.size();
      iTotal = state.getVariableNumberSize();

      const vector <unsigned C_INT32> & Permutation =
        mpModel->getMetabolitePermutation();

      if (mVolumeSize)
        memcpy(mVolumes, state.getVolumeArray(), mVolumeSize * sizeof(double));

      for (i = 0; i < iVariable; i++)
        mVariableNumbers.set(i, state.getVariableNumberDbl(Permutation[i]));

      for (; i < iTotal; i++)
        mDependentNumbers.set(i - iVariable,
                              state.getVariableNumberDbl(Permutation[i]));

      mFixedNumbers.setArray(state.getFixedNumberArrayDbl());
    }

  return *this;
}

CStateX & CStateX::operator =(const CStateX & stateX)
{
  if (mpModel != stateX.getModel())
    setModel(stateX.getModel());

  mTime = stateX.getTime();

  if (mpModel)
    {
      if (mVolumeSize)
        memcpy(mVolumes, stateX.getVolumeArray(), mVolumeSize * sizeof(double));

      mVariableNumbers.setArray(stateX.getVariableNumberArrayDbl());
      mDependentNumbers.setArray(stateX.getDependentNumberArrayDbl());
      mFixedNumbers.setArray(stateX.getFixedNumberArrayDbl());
    }

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
  cleanup();

  mpModel = pModel;
  if (mpModel)
    {
      mVolumeSize = mpModel->getCompartments().size();
      mVolumes = new double[mVolumeSize];

      mVariableNumbers.resize(mpModel->getIndMetab());
      mDependentNumbers.resize(mpModel->getDepMetab());
      mFixedNumbers.resize(mpModel->getTotMetab() - mpModel->getIntMetab());
    }
}

const C_FLOAT64 * CStateX::getDependentNumberArrayDbl() const
  {return mDependentNumbers.getDblArray();}

const C_INT32 * CStateX::getDependentNumberArrayInt() const
  {return mDependentNumbers.getIntArray();}

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

void CStateX::setDependentNumberArray(const C_INT32 * values)
{mDependentNumbers.setArray(values);}

void CStateX::setDependentNumberArray(const C_FLOAT64 * values)
{mDependentNumbers.setArray(values);}

void CStateX::getJacobian(C_FLOAT64 * jacobian,
                          const C_FLOAT64 & factor,
                          const C_FLOAT64 & resolution) const
  {
    CStateX tmp(*this);
    tmp.getJacobianProtected(jacobian, factor, resolution);
  }

void CStateX::cleanup()
{
  CState::cleanup();
  mDependentNumbers.resize(0);
}

void CStateX::updateDependentNumbers()
{mpModel->updateDepMetabNumbers(*this);}

void CStateX::getJacobianProtected(C_FLOAT64 * jacobian,
                                   const C_FLOAT64 & factor,
                                   const C_FLOAT64 & resolution)
{
  unsigned C_INT32 i, j, dim = mVariableNumbers.size();
  C_FLOAT64 * x =
    const_cast<C_FLOAT64 *>(mVariableNumbers.getDblArray());

  // constants for differentiation by finite differences
  C_FLOAT64 K1 = 1 + factor;
  C_FLOAT64 K2 = 1 - factor;
  C_FLOAT64 K3 = 2 * factor;

  C_FLOAT64 store, temp;
  C_FLOAT64 * f1 = new C_FLOAT64 [dim];
  C_FLOAT64 * f2 = new C_FLOAT64 [dim];

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
        jacobian[j * dim + i] = (f1[j] - f2[j]) / (temp * K3);

      x[i] = store;
    }

  // We need this to reset the model (a bad hack)
  const_cast<CModel *>(mpModel)->getDerivatives(this, f2);

  delete [] f1;
  delete [] f2;

  return;
}
