// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// CSate.cpp
//
// (C) Stefan Hoops 2002
//

#include <string.h>
#include <cmath>

#include "copasi/copasi.h"

#include "CState.h"
#include "CModelValue.h"
#include "CModel.h"

//**********************************************************************
//          CStateTemplate
//**********************************************************************

CStateTemplate::CStateTemplate(CModel & model):
  mModel(model),
  mEntities(),
  mSize(0),
  mpBeginIndependent(NULL),
  mpBeginDependent(NULL),
  mpBeginFixed(NULL),
  mpEnd(NULL),
  mInsert(0),
  mIndexMap(),
  mUserOrder(0)
{}

CStateTemplate::~CStateTemplate()
{}

void CStateTemplate::add(const CModelEntity * entity)
{
  if (mIndexMap.count(entity))
    return;

  if (mInsert == mSize) resize();

  mEntities[mInsert] = entity;

  mIndexMap[entity] = mInsert++;

  mModel.setCompileFlag(true);
}

void CStateTemplate::remove(const CModelEntity * entity)
{
  std::map< const CModelEntity *, size_t >::iterator it =
    mIndexMap.find(entity);

  if (it == mIndexMap.end())
    return;

  mEntities[it->second] = NULL;

  mIndexMap.erase(it);

  mModel.setCompileFlag(true);
}

void CStateTemplate::reorder(const CVector< CModelEntity * > & entitiesX)
{

  assert(entitiesX.size() + 1 == mIndexMap.size());


  // Update mpEntities to reflect the new order;

  if (entitiesX.array() != NULL)
    memcpy(mEntities.array() + 1, entitiesX.array(), sizeof(CModelEntity *) * entitiesX.size());

  mInsert = entitiesX.size() + 1;

  const CModelEntity *const* ppEntity = entitiesX.array();
  const CModelEntity *const* ppEntityEnd = ppEntity + entitiesX.size();

  size_t i;
  size_t Independent, Dependent, Fixed;
  Independent = Dependent = Fixed = 0;

  for (i = 1; ppEntity != ppEntityEnd; ++ppEntity, i++)
    {
      mIndexMap[*ppEntity] = i;

      // Count numbers for each status type;
      if ((*ppEntity)->isUsed())
        switch ((*ppEntity)->getStatus())
          {
            case CModelEntity::Status::FIXED:
              Fixed++;
              break;

            case CModelEntity::Status::REACTIONS:

              if (static_cast< const CMetab * >(*ppEntity)->isDependent())
                {
                  assert(Fixed == 0);
                  Dependent++;
                }
              else
                {
                  assert(Dependent == 0);
                  Independent++;
                }

              break;

            case CModelEntity::Status::ODE:
              assert(Dependent == 0);
              Independent++;
              break;

            case CModelEntity::Status::ASSIGNMENT:
              assert(Fixed == 0);
              Dependent++;
              break;

            case CModelEntity::Status::TIME:
              assert(false);
              break;

            case CModelEntity::Status::__SIZE:
              break;
          }
      else
        Fixed++;
    }

  mpBeginIndependent = mEntities.array() + 1;
  mpBeginDependent = mpBeginIndependent + Independent;
  mpBeginFixed = mpBeginDependent + Dependent;
  mpEnd = mpBeginFixed + Fixed;
}

void CStateTemplate::setUserOrder(const CVector< const CModelEntity * > & entities)
{
  mUserOrder.resize(entities.size() + 1);
  size_t * pUserOrder = mUserOrder.array();
  *pUserOrder++ = 0; // for time

  const CModelEntity *const *it = entities.array();
  const CModelEntity *const *end = it + entities.size();

  while (it != end) *pUserOrder++ = getIndex(*it++);
}

const CVector<size_t> & CStateTemplate::getUserOrder() const
{return mUserOrder;}

const CVector< const CModelEntity *> & CStateTemplate::getEntities() const {return mEntities;}

const CModelEntity *const* CStateTemplate::beginIndependent() const {return mpBeginIndependent;}
const CModelEntity *const* CStateTemplate::endIndependent() const {return mpBeginDependent;}
const CModelEntity *const* CStateTemplate::beginDependent() const {return mpBeginDependent;}
const CModelEntity *const* CStateTemplate::endDependent() const {return mpBeginFixed;}
const CModelEntity *const* CStateTemplate::beginFixed() const {return mpBeginFixed;}
const CModelEntity *const* CStateTemplate::endFixed() const {return mpEnd;}

size_t CStateTemplate::getNumIndependent() const
{return mpBeginDependent - mpBeginIndependent;}
size_t CStateTemplate::getNumDependent() const
{return mpBeginFixed - mpBeginDependent;}
size_t CStateTemplate::getNumVariable() const
{return mpBeginFixed - mpBeginIndependent;}
size_t CStateTemplate::getNumFixed() const
{return mpEnd - mpBeginFixed;}

size_t CStateTemplate::getIndex(const CModelEntity * pEntity) const
{
  std::map< const CModelEntity *, size_t >::const_iterator found = mIndexMap.find(pEntity);

  if (found != mIndexMap.end())
    return found->second;

  return C_INVALID_INDEX;
}

const size_t & CStateTemplate::size() const
{return mInsert;}

void CStateTemplate::resize()
{
  if (mSize)
    mSize *= 2;
  else
    mSize = 16;

  // Resize the entities array.
  mEntities.resize(mSize, true);
}
