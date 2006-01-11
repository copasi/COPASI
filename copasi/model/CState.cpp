/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CState.cpp,v $
   $Revision: 1.53.2.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/11 16:45:38 $
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

#include "blaswrap.h"

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
    static CMatrix< C_FLOAT64 > E;
    const CMatrix< C_FLOAT64 > & Stoi = mpModel->getStoi();

    char T = 'N';
    C_INT M = Stoi.numRows(); /* LDA, LDC, N */
    C_INT K = Stoi.numCols(); /* LDB */

    C_FLOAT64 Alpha = 1.0;
    C_FLOAT64 Beta = 0.0;

    E.resize(K, M);

    calculateElasticityMatrix(E, factor, resolution);

    /*     SUBROUTINE DGEMM (TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB,
     *                        BETA, C, LDC)
     *     .. Scalar Arguments ..
     *     CHARACTER*1        TRANSA, TRANSB
     *      INTEGER            M, N, K, LDA, LDB, LDC
     *      DOUBLE PRECISION   ALPHA, BETA
     *     .. Array Arguments ..
     *      DOUBLE PRECISION   A(LDA, *), B(LDB, *), C(LDC, *)
     *     ..
     *
     *  Purpose
     *  =======
     *
     *  DGEMM  performs one of the matrix-matrix operations
     *
     *     C := alpha*op(A)*op(B) + beta*C,
     *
     *  where  op(X) is one of
     *
     *     op(X) = X   or   op(X) = X',
     *
     *  alpha and beta are scalars, and A, B and C are matrices, with op(A)
     *  an m by k matrix,  op(B)  a  k by n matrix and  C an m by n matrix.
     *
     *  Parameters
     *  ==========
     *
     *  TRANSA - CHARACTER*1.
     *           On entry, TRANSA specifies the form of op(A) to be used in
     *           the matrix multiplication as follows:
     *
     *              TRANSA = 'N' or 'n',  op(A) = A.
     *
     *              TRANSA = 'T' or 't',  op(A) = A'.
     *
     *              TRANSA = 'C' or 'c',  op(A) = A'.
     *
     *           Unchanged on exit.
     *
     *  TRANSB - CHARACTER*1.
     *           On entry, TRANSB specifies the form of op(B) to be used in
     *           the matrix multiplication as follows:
     *
     *              TRANSB = 'N' or 'n',  op(B) = B.
     *
     *              TRANSB = 'T' or 't',  op(B) = B'.
     *
     *              TRANSB = 'C' or 'c',  op(B) = B'.
     *
     *           Unchanged on exit.
     *
     *  M      - INTEGER.
     *           On entry,  M  specifies  the number  of rows  of the  matrix
     *           op(A)  and of the  matrix  C.  M  must  be at least  zero.
     *           Unchanged on exit.
     *
     *  N      - INTEGER.
     *           On entry,  N  specifies the number  of columns of the matrix
     *           op(B) and the number of columns of the matrix C. N must be
     *           at least zero.
     *           Unchanged on exit.
     *
     *  K      - INTEGER.
     *           On entry,  K  specifies  the number of columns of the matrix
     *           op(A) and the number of rows of the matrix op(B). K must
     *           be at least  zero.
     *           Unchanged on exit.
     *
     *  ALPHA  - DOUBLE PRECISION.
     *           On entry, ALPHA specifies the scalar alpha.
     *           Unchanged on exit.
     *
     *  A      - DOUBLE PRECISION array of DIMENSION (LDA, ka), where ka is
     *           k  when  TRANSA = 'N' or 'n',  and is  m  otherwise.
     *           Before entry with  TRANSA = 'N' or 'n',  the leading  m by k
     *           part of the array  A  must contain the matrix  A,  otherwise
     *           the leading  k by m  part of the array  A  must contain  the
     *           matrix A.
     *           Unchanged on exit.
     *
     *  LDA    - INTEGER.
     *           On entry, LDA specifies the first dimension of A as declared
     *           in the calling (sub) program. When  TRANSA = 'N' or 'n' then
     *           LDA must be at least  max(1, m), otherwise  LDA must be at
     *           least  max(1, k).
     *           Unchanged on exit.
     *
     *  B      - DOUBLE PRECISION array of DIMENSION (LDB, kb), where kb is
     *           n  when  TRANSB = 'N' or 'n',  and is  k  otherwise.
     *           Before entry with  TRANSB = 'N' or 'n',  the leading  k by n
     *           part of the array  B  must contain the matrix  B,  otherwise
     *           the leading  n by k  part of the array  B  must contain  the
     *           matrix B.
     *           Unchanged on exit.
     *
     *  LDB    - INTEGER.
     *           On entry, LDB specifies the first dimension of B as declared
     *           in the calling (sub) program. When  TRANSB = 'N' or 'n' then
     *           LDB must be at least  max(1, k), otherwise  LDB must be at
     *           least  max(1, n).
     *           Unchanged on exit.
     *
     *  BETA   - DOUBLE PRECISION.
     *           On entry,  BETA  specifies the scalar  beta.  When  BETA  is
     *           supplied as zero then C need not be set on input.
     *           Unchanged on exit.
     *
     *  C      - DOUBLE PRECISION array of DIMENSION (LDC, n).
     *           Before entry, the leading  m by n  part of the array  C must
     *           contain the matrix  C,  except when  beta  is zero, in which
     *           case C need not be set on entry.
     *           On exit, the array  C  is overwritten by the  m by n  matrix
     *           (alpha*op(A)*op(B) + beta*C).
     *
     *  LDC    - INTEGER.
     *           On entry, LDC specifies the first dimension of C as declared
     *           in  the  calling  (sub)  program.   LDC  must  be  at  least
     *           max(1, m).
     *           Unchanged on exit.
     *
     *
     *  Level 3 Blas routine.
     */
    dgemm_(&T, &T, &M, &M, &K, &Alpha, E.array(), &M,
           const_cast<C_FLOAT64 *>(Stoi.array()), &K, &Beta, jacobian.array(), &M);
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
    static CMatrix< C_FLOAT64 > E;
    static CMatrix< C_FLOAT64 > tmp;

    const CMatrix< C_FLOAT64 > & L = mpModel->getL0();
    const CMatrix< C_FLOAT64 > & redStoi = mpModel->getRedStoi();

    char T = 'N';
    C_INT M = mpModel->getNumIndependentMetabs(); /* LDA, LDC */
    C_INT N = redStoi.numCols();
    C_INT K = mpModel->getNumDependentMetabs();
    C_INT LD = mpModel->getNumVariableMetabs();

    C_FLOAT64 Alpha = 1.0;
    C_FLOAT64 Beta = 1.0;

    E.resize(N, LD);
    tmp.resize(N, LD);

    calculateElasticityMatrix(E, factor, resolution);

    memcpy(tmp.array(), E.array(), N * LD * sizeof(C_FLOAT64));

    /*     SUBROUTINE DGEMM (TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB,
     *                        BETA, C, LDC)
     *     .. Scalar Arguments ..
     *     CHARACTER*1        TRANSA, TRANSB
     *      INTEGER            M, N, K, LDA, LDB, LDC
     *      DOUBLE PRECISION   ALPHA, BETA
     *     .. Array Arguments ..
     *      DOUBLE PRECISION   A(LDA, *), B(LDB, *), C(LDC, *)
     *     ..
     *
     *  Purpose
     *  =======
     *
     *  DGEMM  performs one of the matrix-matrix operations
     *
     *     C := alpha*op(A)*op(B) + beta*C,
     *
     *  where  op(X) is one of
     *
     *     op(X) = X   or   op(X) = X',
     *
     *  alpha and beta are scalars, and A, B and C are matrices, with op(A)
     *  an m by k matrix,  op(B)  a  k by n matrix and  C an m by n matrix.
     *
     *  Parameters
     *  ==========
     *
     *  TRANSA - CHARACTER*1.
     *           On entry, TRANSA specifies the form of op(A) to be used in
     *           the matrix multiplication as follows:
     *
     *              TRANSA = 'N' or 'n',  op(A) = A.
     *
     *              TRANSA = 'T' or 't',  op(A) = A'.
     *
     *              TRANSA = 'C' or 'c',  op(A) = A'.
     *
     *           Unchanged on exit.
     *
     *  TRANSB - CHARACTER*1.
     *           On entry, TRANSB specifies the form of op(B) to be used in
     *           the matrix multiplication as follows:
     *
     *              TRANSB = 'N' or 'n',  op(B) = B.
     *
     *              TRANSB = 'T' or 't',  op(B) = B'.
     *
     *              TRANSB = 'C' or 'c',  op(B) = B'.
     *
     *           Unchanged on exit.
     *
     *  M      - INTEGER.
     *           On entry,  M  specifies  the number  of rows  of the  matrix
     *           op(A)  and of the  matrix  C.  M  must  be at least  zero.
     *           Unchanged on exit.
     *
     *  N      - INTEGER.
     *           On entry,  N  specifies the number  of columns of the matrix
     *           op(B) and the number of columns of the matrix C. N must be
     *           at least zero.
     *           Unchanged on exit.
     *
     *  K      - INTEGER.
     *           On entry,  K  specifies  the number of columns of the matrix
     *           op(A) and the number of rows of the matrix op(B). K must
     *           be at least  zero.
     *           Unchanged on exit.
     *
     *  ALPHA  - DOUBLE PRECISION.
     *           On entry, ALPHA specifies the scalar alpha.
     *           Unchanged on exit.
     *
     *  A      - DOUBLE PRECISION array of DIMENSION (LDA, ka), where ka is
     *           k  when  TRANSA = 'N' or 'n',  and is  m  otherwise.
     *           Before entry with  TRANSA = 'N' or 'n',  the leading  m by k
     *           part of the array  A  must contain the matrix  A,  otherwise
     *           the leading  k by m  part of the array  A  must contain  the
     *           matrix A.
     *           Unchanged on exit.
     *
     *  LDA    - INTEGER.
     *           On entry, LDA specifies the first dimension of A as declared
     *           in the calling (sub) program. When  TRANSA = 'N' or 'n' then
     *           LDA must be at least  max(1, m), otherwise  LDA must be at
     *           least  max(1, k).
     *           Unchanged on exit.
     *
     *  B      - DOUBLE PRECISION array of DIMENSION (LDB, kb), where kb is
     *           n  when  TRANSB = 'N' or 'n',  and is  k  otherwise.
     *           Before entry with  TRANSB = 'N' or 'n',  the leading  k by n
     *           part of the array  B  must contain the matrix  B,  otherwise
     *           the leading  n by k  part of the array  B  must contain  the
     *           matrix B.
     *           Unchanged on exit.
     *
     *  LDB    - INTEGER.
     *           On entry, LDB specifies the first dimension of B as declared
     *           in the calling (sub) program. When  TRANSB = 'N' or 'n' then
     *           LDB must be at least  max(1, k), otherwise  LDB must be at
     *           least  max(1, n).
     *           Unchanged on exit.
     *
     *  BETA   - DOUBLE PRECISION.
     *           On entry,  BETA  specifies the scalar  beta.  When  BETA  is
     *           supplied as zero then C need not be set on input.
     *           Unchanged on exit.
     *
     *  C      - DOUBLE PRECISION array of DIMENSION (LDC, n).
     *           Before entry, the leading  m by n  part of the array  C must
     *           contain the matrix  C,  except when  beta  is zero, in which
     *           case C need not be set on entry.
     *           On exit, the array  C  is overwritten by the  m by n  matrix
     *           (alpha*op(A)*op(B) + beta*C).
     *
     *  LDC    - INTEGER.
     *           On entry, LDC specifies the first dimension of C as declared
     *           in  the  calling  (sub)  program.   LDC  must  be  at  least
     *           max(1, m).
     *           Unchanged on exit.
     *
     *
     *  Level 3 Blas routine.
     */

    // tmp = (E1, E2) (I, L0')' = E1 + E2 * L0
    dgemm_(&T, &T, &M, &N, &K, &Alpha, const_cast<C_FLOAT64 *>(L.array()), &M,
           E.array() + M, &LD, &Beta, tmp.array(), &LD);

    Beta = 0.0;

    // j = R * tmp
    dgemm_(&T, &T, &M, &M, &N, &Alpha, tmp.array(), &LD,
           const_cast<C_FLOAT64 *>(redStoi.array()), &N, &Beta, jacobian.array(), &M);
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
