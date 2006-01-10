/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CState.cpp,v $
   $Revision: 1.53.2.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/10 14:12:07 $
   End CVS Header */

// CSate.cpp
//
// (C) Stefan Hoops 2002
//

#include "copasi.h"
#include "CState.h"
#include "CModel.h"
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
    mVariableNumbers(state.mVariableNumbers),
    mGlobalParameters(state.mGlobalParameters)
{}

CState::CState(const CStateX & stateX)
{*this = stateX;}

CState::~CState() {}

//******* assignment operators ***************

CState & CState::operator =(const CStateX & stateX)
{
#ifdef COPASI_DEBUG
  stateX.check("operator= rhs");
#endif

  mpModel = stateX.mpModel;
  mTime = stateX.mTime;
  mVolumes = stateX.mVolumes;
  mFixedNumbers = stateX.mFixedNumbers;
  mGlobalParameters = stateX.mGlobalParameters;

  if (mpModel)
    {
      mVariableNumbers.resize(mpModel->getNumVariableMetabs());

      const unsigned C_INT32 * pPermutation =
        mpModel->getMetabolitePermutation().array();

      C_FLOAT64 * pTo =
        const_cast< C_FLOAT64 * >(mVariableNumbers.array());

      const C_FLOAT64 * pIt = stateX.mVariableNumbers.array();
      const C_FLOAT64 * pEnd = pIt + stateX.mVariableNumbers.size();
      for (; pIt != pEnd; ++pIt, ++pPermutation)
        *(pTo + *pPermutation) = *pIt;

      pIt = stateX.mDependentNumbers.array();
      pEnd = pIt + stateX.mDependentNumbers.size();
      for (; pIt != pEnd; ++pIt, ++pPermutation)
        *(pTo + *pPermutation) = *pIt;
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
  state.check("operator= rhs");
#endif

  mpModel = state.mpModel;
  mTime = state.mTime;
  mVolumes = state.mVolumes;
  mFixedNumbers = state.mFixedNumbers;
  mVariableNumbers = state.mVariableNumbers;
  mGlobalParameters = state.mGlobalParameters;

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
      mGlobalParameters.resize(mpModel->getNumModelValues());
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

const CVector< C_FLOAT64 > & CState::getGlobalParameterVector() const
  {return mGlobalParameters;}

const C_FLOAT64 & CState::getGlobalParameter(const unsigned C_INT32 & index) const
  {return mGlobalParameters[index];}

unsigned C_INT32 CState::getGlobalParameterSize() const
  {return mGlobalParameters.size();}

void CState::setGlobalParameter(const unsigned C_INT32 & index, const C_FLOAT64 & value)
{mGlobalParameters[index] = value;}

void CState::setGlobalParameterVector(const CVector< C_FLOAT64 > & vektor)
{mGlobalParameters = vektor;}

//******

void CState::calculateJacobian(CMatrix< C_FLOAT64 > & jacobian,
                               const C_FLOAT64 & factor,
                               const C_FLOAT64 & resolution) const
  {
#ifdef COPASI_DEBUG
    this->check("calculate Jacobian");
#endif

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

void CState::calculateElasticityMatrix(CMatrix< C_FLOAT64 > & elasticityMatrix,
                                       const C_FLOAT64 & factor,
                                       const C_FLOAT64 & resolution) const
  {
#ifdef COPASI_DEBUG
    this->check("calculate Elasticity");
#endif
    const_cast<CModel *>(mpModel)->setState(this);

    unsigned C_INT32 i;
    const unsigned C_INT32 nCol = elasticityMatrix.numCols();

    C_FLOAT64 * itE;
    C_FLOAT64 * startE = const_cast<C_FLOAT64 *>(elasticityMatrix.array());

    CCopasiVector< CReaction >::const_iterator itReaction;
    CCopasiVector< CReaction >::const_iterator startReaction = mpModel->getReactions().begin();
    CCopasiVector< CReaction >::const_iterator endReaction = mpModel->getReactions().end();

    CCopasiVector< CMetab >::const_iterator itMetab;
    CCopasiVector< CMetab >::const_iterator startMetab = mpModel->getMetabolites().begin();
    CCopasiVector< CMetab >::const_iterator endMetab = startMetab + mpModel->getNumVariableMetabs();

    for (itMetab = startMetab, i = 0; itMetab != endMetab; ++itMetab, i++)
      {
        C_FLOAT64 & X = *const_cast<C_FLOAT64 *>(&(*itMetab)->getConcentration());
        const C_FLOAT64 & invVolume = (*itMetab)->getCompartment()->getVolumeInv();

        for (itReaction = startReaction, itE = startE + i;
             itReaction != endReaction;
             ++itReaction, itE += nCol)
          * itE = invVolume * (*itReaction)->calculatePartialDerivative(X, factor, resolution);
      }

    return;
  }

std::ostream & operator << (std::ostream & os, const CState & A)
{
  os << "State: " << std::endl;
  os << "  Time:       " << A.mTime << std::endl;
  os << "  Volumes:    " << A.mVolumes;
  os << "  Fixed:      " << A.mFixedNumbers;
  os << "  Variable:   " << A.mVariableNumbers << std::endl;
  os << "  Parameters: " << A.mGlobalParameters << std::endl;

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

    if (mFixedNumbers.size() != mpModel->getNumMetabs() - mpModel->getNumVariableMetabs())
    {std::cout << "CState: " << m << ": mismatch in fixedNumbers" << std::endl;}

    if (mVariableNumbers.size() != mpModel->getNumVariableMetabs())
    {std::cout << "CState: " << m << ": mismatch in variableNumbers" << std::endl;}

    if (mGlobalParameters.size() != mpModel->getNumModelValues())
    {std::cout << "CState: " << m << ": mismatch in globalParameters" << std::endl;}
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
  state.check("operator= rhs");
#endif

  mpModel = state.mpModel;
  mTime = state.mTime;
  mVolumes = state.mVolumes;
  mFixedNumbers = state.mFixedNumbers;
  mGlobalParameters = state.mGlobalParameters;

  if (mpModel)
    {
      mVariableNumbers.resize(mpModel->getNumIndependentMetabs());
      mDependentNumbers.resize(mpModel->getNumDependentMetabs());

      const unsigned C_INT32 * pPermutation =
        mpModel->getMetabolitePermutation().array();

      const C_FLOAT64 * pFrom =
        const_cast< C_FLOAT64 * >(state.mVariableNumbers.array());

      C_FLOAT64 * pIt = const_cast< C_FLOAT64 * >(mVariableNumbers.array());
      C_FLOAT64 * pEnd = pIt + mVariableNumbers.size();
      for (; pIt != pEnd; ++pIt, ++pPermutation)
        *pIt = *(pFrom + *pPermutation);

      pIt = const_cast< C_FLOAT64 * >(mDependentNumbers.array());
      pEnd = pIt + mDependentNumbers.size();
      for (; pIt != pEnd; ++pIt, ++pPermutation)
        *pIt = *(pFrom + *pPermutation);
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
  stateX.check("operator= rhs");
#endif

  mpModel = stateX.mpModel;
  mTime = stateX.mTime;
  mVolumes = stateX.mVolumes;
  mFixedNumbers = stateX.mFixedNumbers;
  mVariableNumbers = stateX.mVariableNumbers;
  mDependentNumbers = stateX.mDependentNumbers;
  mGlobalParameters = stateX.mGlobalParameters;

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
      mGlobalParameters.resize(mpModel->getNumModelValues());
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

  const_cast<CModel *>(mpModel)->setStateX(this);

  C_FLOAT64 * Tmp = mDependentNumbers.array();

  CCopasiVector< CMetab >::const_iterator it =
    mpModel->getMetabolitesX().begin() + mpModel->getNumIndependentMetabs();
  CCopasiVector< CMetab >::const_iterator end =
    it + mpModel->getNumDependentMetabs();

  for (; it != end; ++it, Tmp++)
    *Tmp = (*it)->getValue();
}

void CStateX::calculateElasticityMatrix(CMatrix< C_FLOAT64 > & elasticityMatrix,
                                        const C_FLOAT64 & factor,
                                        const C_FLOAT64 & resolution) const
  {
#ifdef COPASI_DEBUG
    this->check("calculate elasticities");
#endif

    const_cast<CModel *>(mpModel)->setStateX(this);

    unsigned C_INT32 i;
    const unsigned C_INT32 nCol = elasticityMatrix.numCols();

    C_FLOAT64 * itE;
    C_FLOAT64 * startE = const_cast<C_FLOAT64 *>(elasticityMatrix.array());

    CCopasiVector< CReaction >::const_iterator itReaction;
    CCopasiVector< CReaction >::const_iterator startReaction = mpModel->getReactions().begin();
    CCopasiVector< CReaction >::const_iterator endReaction = mpModel->getReactions().end();

    CCopasiVector< CMetab >::const_iterator itMetab;
    CCopasiVector< CMetab >::const_iterator startMetab = mpModel->getMetabolitesX().begin();
    CCopasiVector< CMetab >::const_iterator endMetab = startMetab + mpModel->getNumVariableMetabs();

    for (itMetab = startMetab, i = 0; itMetab != endMetab; ++itMetab, i++)
      {
        C_FLOAT64 & X = *const_cast<C_FLOAT64 *>(&(*itMetab)->getConcentration());
        const C_FLOAT64 & invVolume = (*itMetab)->getCompartment()->getVolumeInv();

        for (itReaction = startReaction, itE = startE + i;
             itReaction != endReaction;
             ++itReaction, itE += nCol)
          * itE = invVolume * (*itReaction)->calculatePartialDerivative(X, factor, resolution);
      }

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
  os << "  Parameters:  " << A.mGlobalParameters << std::endl;

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

    if (mGlobalParameters.size() != mpModel->getNumModelValues())
    {std::cout << "CState: " << m << ": mismatch in globalParameters" << std::endl;}
  }
#endif
