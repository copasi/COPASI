// CParticleNumberList.cpp
//
// (C) Stefan Hoops 2002
//

#define  COPASI_TRACE_CONSTRUCTION

#include <string.h>

#include "copasi.h"
#include "CParticleNumberList.h"

CParticleNumberList::CParticleNumberList(unsigned C_INT32 size) :
    mSize(size),
    mDbl(size),
    mInt(size)
{}

CParticleNumberList::CParticleNumberList(const CParticleNumberList & src) :
    mSize(src.mSize),
    mDbl(src.mDbl),
    mInt(src.mInt)
{}

CParticleNumberList::~CParticleNumberList()
{}

const unsigned C_INT32 & CParticleNumberList::size () const
{return mSize;}

void CParticleNumberList::resize(const unsigned C_INT32 & size)
{
  mSize = size;
  mDbl.resize(mSize);
  mInt.resize(mSize);
}

const C_FLOAT64 &
CParticleNumberList::getDbl(const unsigned C_INT32 & index) const
{return mDbl[index];}

const CVector< C_FLOAT64 > & CParticleNumberList::getDblArray() const
{return mDbl;}

const C_INT32 &
CParticleNumberList::getInt(const unsigned C_INT32 & index) const
{return mInt[index];}

const CVector< C_INT32 > & CParticleNumberList::getIntArray() const
{return mInt;}

void CParticleNumberList::set(const unsigned C_INT32 & index,
                              const C_INT32 & value)
{
  assert (mSize > index);

  mInt[index] = value;
  mDbl[index] = (C_FLOAT64) value;
}

void CParticleNumberList::set(const unsigned C_INT32 & index,
                              const C_FLOAT64 & value)
{
  assert (mSize > index);

  mInt[index] = (C_INT32) value;
  mDbl[index] = value;
}

void CParticleNumberList::setArray(const CVector< C_INT32 > & values)
{
  assert (mSize == values.size());

  unsigned C_INT32 i;

  for (i = 0; i < mSize; i++)
    {
      mInt[i] = values[i];
      mDbl[i] = (C_FLOAT64) values[i];
    }
}

void CParticleNumberList::setArray(const CVector< C_FLOAT64 > & values)
{
  assert (mSize == values.size());

  unsigned C_INT32 i;

  for (i = 0; i < mSize; i++)
    {
      mInt[i] = (C_INT32) values[i];
      mDbl[i] = values[i];
    }
}
