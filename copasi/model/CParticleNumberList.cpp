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
    mDbl(NULL),
    mInt(NULL)
{
  if (mSize)
    {
      mDbl = new C_FLOAT64 [mSize];
      mInt = new C_INT32 [mSize];
    }
}

CParticleNumberList::CParticleNumberList(const CParticleNumberList & src) :
    mSize(src.mSize),
    mDbl(NULL),
    mInt(NULL)
{
  if (mSize)
    {
      mDbl = new C_FLOAT64 [mSize];
      mInt = new C_INT32 [mSize];

      memcpy(mDbl, src.mDbl, mSize * sizeof(C_FLOAT64));
      memcpy(mInt, src.mInt, mSize * sizeof(C_INT32));
    }
}

CParticleNumberList::~CParticleNumberList()
{
  pdelete(mDbl);
  pdelete(mInt);
}

const unsigned C_INT32 & CParticleNumberList::size () const
  { return mSize; }

void CParticleNumberList::resize(const unsigned C_INT32 & size)
{
  unsigned C_INT32 OldSize = mSize;
  C_FLOAT64 * OldDbl = mDbl;
  C_INT32 * OldInt = mInt;

  mDbl = NULL;
  mInt = NULL;

  mSize = size;
  if (mSize)
    {
      mDbl = new C_FLOAT64 [mSize];
      mInt = new C_INT32 [mSize];
      if (OldSize)
        {
          memcpy(mDbl, OldDbl, OldSize * sizeof(C_FLOAT64));
          memcpy(mInt, OldInt, OldSize * sizeof(C_INT32));
        }
    }

  pdelete(OldDbl);
  pdelete(OldInt);
}

const C_FLOAT64 &
CParticleNumberList::getDbl(const unsigned C_INT32 & index) const
  { return *(mDbl + index); }

const C_FLOAT64 * CParticleNumberList::getDblArray() const
  { return mDbl; }

const C_INT32 &
CParticleNumberList::getInt(const unsigned C_INT32 & index) const
  { return *(mInt + index); }

const C_INT32 * CParticleNumberList::getIntArray() const
  { return mInt; }

void CParticleNumberList::set (const unsigned C_INT32 & index,
   const C_INT32 & value)
  {
    *(mInt + index) = value;
    *(mDbl + index) = (C_FLOAT64) value;
  }

void CParticleNumberList::set (const unsigned C_INT32 & index,
   const C_FLOAT64 & value)
  {
    *(mInt + index) = (C_INT32) value;
    *(mDbl + index) = value;
  }

void CParticleNumberList::setArray(const C_INT32 * values)
{
  unsigned C_INT32 i;

  for (i = 0; i < mSize; i++, values++)
    {
      *(mInt + i) = *values;
      *(mDbl + i) = (C_FLOAT64) * values;
    }
}

void CParticleNumberList::setArray(const C_FLOAT64 * values)
{
  unsigned C_INT32 i;

  for (i = 0; i < mSize; i++, values++)
    {
      *(mInt + i) = (C_INT32) * values;
      *(mDbl + i) = *values;
    }
}
