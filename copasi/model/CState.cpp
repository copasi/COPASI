/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CState.cpp,v $
   $Revision: 1.65 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/07 19:27:09 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// CSate.cpp
//
// (C) Stefan Hoops 2002
//

#include "copasi.h"

#include "CState.h"
#include "CModelValue.h"
#include "CModel.h"

//**********************************************************************
//          CStateTemplate
//**********************************************************************

CStateTemplate::CStateTemplate(CModel & model, CState & initialState, CState & currentState):
    mModel(model),
    mInitialState(initialState),
    mCurrentState(currentState),
    mpEntities(NULL),
    mSize(0),
    mpBeginIndependent(NULL),
    mpBeginDependent(NULL),
    mpBeginFixed(NULL),
    mpEnd(NULL),
    mInsert(0),
    mIndexMap(),
    mUserOrder(0),
    mpInitialValues(NULL),
    mpCurrentValues(NULL)
{}

CStateTemplate::~CStateTemplate() {}

void CStateTemplate::add(CModelEntity * entity)
{
  if (mIndexMap.count(entity))
    return;

  if (mInsert == mSize) resize();

  mpEntities[mInsert] = entity;

  entity->setInitialValuePtr(mpInitialValues + mInsert);
  entity->setValuePtr(mpCurrentValues + mInsert);

  mIndexMap[entity] = mInsert++;

  mModel.setCompileFlag(true);
}

void CStateTemplate::remove(CModelEntity * entity)
{
  std::map< CModelEntity *, unsigned C_INT32 >::iterator it =
    mIndexMap.find(entity);

  if (it == mIndexMap.end())
    return;

  entity->setInitialValuePtr(NULL);
  entity->setValuePtr(NULL);

  mpEntities[it->second] = NULL;

  mIndexMap.erase(it);

  mModel.setCompileFlag(true);
}

void CStateTemplate::reorder(const CVector< CModelEntity * > & entitiesX)
{
  assert(entitiesX.size() + 1 == mIndexMap.size());

  // Update mpEntities to reflect the new order;

  memcpy(mpEntities + 1, entitiesX.array(), sizeof(CModelEntity *) * entitiesX.size());
  mInsert = entitiesX.size() + 1;

  std::map< CModelEntity *, unsigned C_INT32 >::iterator found;
  CVector<C_FLOAT64> InitialValues(entitiesX.size());
  CVector<C_FLOAT64> CurrentValues(entitiesX.size());

  CModelEntity *const*it = entitiesX.array();
  CModelEntity *const*end = it + entitiesX.size();

  unsigned C_INT32 i;
  unsigned C_INT32 Independent, Dependent, Fixed;
  Independent = Dependent = Fixed = 0;

  for (i = 1; it != end; ++it, i++)
    {
      found = mIndexMap.find(*it);
      assert (found != mIndexMap.end());

      // Build new order
      InitialValues[i - 1] = *(mpInitialValues + found->second);
      CurrentValues[i - 1] = *(mpCurrentValues + found->second);

      // Update pointer if necessary
      if (i != found->second)
        {
          found->second = i;
          found->first->setInitialValuePtr(mpInitialValues + found->second);
          found->first->setValuePtr(mpCurrentValues + found->second);
        }

      // Count numbers for each status type;
      if ((*it)->isUsed())
        switch ((*it)->getStatus())
          {
          case CModelEntity::FIXED:
            Fixed++;
            break;

          case CModelEntity::REACTIONS:
            if (static_cast< CMetab * >(*it)->isDependent())
              {
                assert (Fixed == 0);
                Dependent++;
              }
            else
              {
                assert (Dependent == 0);
                Independent++;
              }
            break;

          case CModelEntity::ODE:
            assert (Dependent == 0);
            Independent++;
            break;

          case CModelEntity::ASSIGNMENT:
            assert (Fixed == 0);
            Dependent++;
            break;

          case CModelEntity::TIME:
            assert (false);
            break;
          }
      else
        Fixed++;
    }

  mpBeginIndependent = mpEntities + 1;
  mpBeginDependent = mpBeginIndependent + Independent;
  mpBeginFixed = mpBeginDependent + Dependent;
  mpEnd = mpBeginFixed + Fixed;

  memcpy(mpInitialValues + 1, InitialValues.array(), sizeof(C_FLOAT64) * entitiesX.size());
  memcpy(mpCurrentValues + 1, CurrentValues.array(), sizeof(C_FLOAT64) * entitiesX.size());

  // Update the iterators of the states
  mInitialState.updateIterator(Independent, Dependent, Fixed);
  mCurrentState.updateIterator(Independent, Dependent, Fixed);
}

void CStateTemplate::setUserOrder(const CVector< CModelEntity * > & entities)
{
  mUserOrder.resize(entities.size() + 1);
  unsigned C_INT32 * pUserOrder = mUserOrder.array();
  *pUserOrder++ = 0; // for time

  CModelEntity *const *it = entities.array();
  CModelEntity *const *end = it + entities.size();

  while (it != end) *pUserOrder++ = getIndex(*it++);
}

const CVector<unsigned C_INT32> & CStateTemplate::getUserOrder() const
{return mUserOrder;}

CModelEntity ** CStateTemplate::getEntities()
{return mpEntities;}

CModelEntity ** getEntities();
CModelEntity ** CStateTemplate::beginIndependent() {return mpBeginIndependent;}
CModelEntity ** CStateTemplate::endIndependent() {return mpBeginDependent;}
CModelEntity ** CStateTemplate::beginDependent() {return mpBeginDependent;}
CModelEntity ** CStateTemplate::endDependent() {return mpBeginFixed;}
CModelEntity ** CStateTemplate::beginFixed() {return mpBeginFixed;}
CModelEntity ** CStateTemplate::endFixed() {return mpEnd;}

CModelEntity *const* CStateTemplate::beginIndependent() const {return mpBeginIndependent;}
CModelEntity **const CStateTemplate::endIndependent() const {return mpBeginDependent;}
CModelEntity **const CStateTemplate::beginDependent() const {return mpBeginDependent;}
CModelEntity **const CStateTemplate::endDependent() const {return mpBeginFixed;}
CModelEntity **const CStateTemplate::beginFixed() const {return mpBeginFixed;}
CModelEntity **const CStateTemplate::endFixed() const {return mpEnd;}

unsigned C_INT32 CStateTemplate::getNumIndependent() const
  {return mpBeginDependent - mpBeginIndependent;}
unsigned C_INT32 CStateTemplate::getNumDependent() const
  {return mpBeginFixed - mpBeginDependent;}
unsigned C_INT32 CStateTemplate::getNumVariable() const
  {return mpBeginFixed - mpBeginIndependent;}
unsigned C_INT32 CStateTemplate::getNumFixed() const
  {return mpEnd - mpBeginFixed;}

unsigned C_INT32 CStateTemplate::getIndex(CModelEntity * entity) const
  {
    std::map< CModelEntity *, unsigned C_INT32 >::const_iterator found = mIndexMap.find(entity);
    if (found != mIndexMap.end())
      return found->second;

    return C_INVALID_INDEX;
  }

const unsigned C_INT32 & CStateTemplate::size() const
{return mInsert;}

void CStateTemplate::resize()
{
  unsigned C_INT32 OldSize = mSize;

  if (mSize)
    mSize *= 2;
  else
    mSize = 16;

  // Resize the entities array.
  CModelEntity ** pTmp = mpEntities;
  mpEntities = new CModelEntity * [mSize];
  memcpy(mpEntities, pTmp, sizeof(CModelEntity *) * OldSize);
  pdeletev(pTmp);

  // Resize the states
  C_FLOAT64 * pInitialValues = mpInitialValues = mInitialState.resize(mSize);
  C_FLOAT64 * pCurrentValues = mpCurrentValues = mCurrentState.resize(mSize);

  // Update all pointers in the entities
  pTmp = mpEntities;
  CModelEntity ** pEnd = pTmp + mInsert;

  for (; pTmp != pEnd; ++pTmp, ++pInitialValues, ++pCurrentValues)
    if (*pTmp != NULL)
      {
        (*pTmp)->setInitialValuePtr(pInitialValues);
        (*pTmp)->setValuePtr(pCurrentValues);
      }
}

/*************************/
/* Code for class CState */
/*************************/
CState::CState():
    mpValues(NULL),
    mSize(0),
    mpBeginIndependent(NULL),
    mpBeginDependent(NULL),
    mpBeginFixed(NULL),
    mpEnd(NULL),
    mUpdateDependentRequired(false)
{}

CState::CState(const CState & src):
    mpValues(new C_FLOAT64[src.mSize]),
    mSize(src.mSize),
    mpBeginIndependent(mpValues + (src.mpBeginIndependent - src.mpValues)),
    mpBeginDependent(mpValues + (src.mpBeginDependent - src.mpValues)),
    mpBeginFixed(mpValues + (src.mpBeginFixed - src.mpValues)),
    mpEnd(mpValues + (src.mpEnd - src.mpValues)),
    mUpdateDependentRequired(src.mUpdateDependentRequired)
{
  memcpy(mpValues, src.mpValues, sizeof(C_FLOAT64) * mSize);
}

CState::~CState() {pdeletev(mpValues);}

CState & CState::operator=(const CState & rhs)
{
  if (this != &rhs)
    {
      if (mSize != rhs.mSize)
        {
          pdeletev(mpValues);
          mpValues = new C_FLOAT64[rhs.mSize];
          mSize = rhs.mSize;
        }

      memcpy(mpValues, rhs.mpValues, sizeof(C_FLOAT64) * mSize);
      mpBeginIndependent = mpValues + (rhs.mpBeginIndependent - rhs.mpValues);
      mpBeginDependent = mpValues + (rhs.mpBeginDependent - rhs.mpValues);
      mpBeginFixed = mpValues + (rhs.mpBeginFixed - rhs.mpValues);
      mpEnd = mpValues + (rhs.mpEnd - rhs.mpValues);
      mUpdateDependentRequired = rhs.mUpdateDependentRequired;
    }

  return *this;
}

const C_FLOAT64 & CState::getTime() const {return *mpValues;}
void CState::setTime(const C_FLOAT64 & time) {*mpValues = time;}

C_FLOAT64 * CState::beginIndependent() {return mpBeginIndependent;}
C_FLOAT64 * CState::endIndependent() {return mpBeginDependent;}
C_FLOAT64 * CState::beginDependent() {return mpBeginDependent;}
C_FLOAT64 * CState::endDependent() {return mpBeginFixed;}
C_FLOAT64 * CState::beginFixed() {return mpBeginFixed;}
C_FLOAT64 * CState::endFixed() {return mpEnd;}

const C_FLOAT64 * CState::beginIndependent() const {return mpBeginIndependent;}
const C_FLOAT64 * CState::endIndependent() const {return mpBeginDependent;}
const C_FLOAT64 * CState::beginDependent() const {return mpBeginDependent;}
const C_FLOAT64 * CState::endDependent() const {return mpBeginFixed;}
const C_FLOAT64 * CState::beginFixed() const {return mpBeginFixed;}
const C_FLOAT64 * CState::endFixed() const {return mpEnd;}

unsigned C_INT32 CState::getNumIndependent() const
  {return mpBeginDependent - mpBeginIndependent;}
unsigned C_INT32 CState::getNumDependent() const
  {return mpBeginFixed - mpBeginDependent;}
unsigned C_INT32 CState::getNumVariable() const
  {return mpBeginFixed - mpBeginIndependent;}
unsigned C_INT32 CState::getNumFixed() const
  {return mpEnd - mpBeginFixed;}

void CState::setUpdateDependentRequired(const bool & required)
{mUpdateDependentRequired = required;}
const bool & CState::isUpdateDependentRequired() const
  {return mUpdateDependentRequired;}

C_FLOAT64 * CState::resize(const unsigned C_INT32 & size)
{
  if (mSize != size)
    {
      C_FLOAT64 * pTmp = mpValues;

      if (size > 0)
        {
          mpValues = new C_FLOAT64[size];
          memcpy(mpValues, pTmp, sizeof(C_FLOAT64) * std::min(mSize, size));
        }
      else
        mpValues = NULL;

      pdeletev(pTmp);
      mSize = size;
    }

  updateIterator(getNumIndependent(), getNumDependent(), getNumFixed());

  return mpValues;
}

void CState::updateIterator(const unsigned C_INT32 & numIndependent,
                            const unsigned C_INT32 & numDependent,
                            const unsigned C_INT32 & numFixed)
{
  mpBeginIndependent = mpValues + 1; // One for Time
  mpBeginDependent = mpBeginIndependent + numIndependent;
  mpBeginFixed = mpBeginDependent + numDependent;
  mpEnd = mpBeginFixed + numFixed;
}
