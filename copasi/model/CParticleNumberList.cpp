/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CParticleNumberList.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/03 20:47:23 $
   End CVS Header */

// CParticleNumberList.cpp
//
// (C) Stefan Hoops 2002
//

#define  COPASI_TRACE_CONSTRUCTION

#include <string.h>

#include "copasi.h"
#include "CParticleNumberList.h"

CParticleNumberList::CParticleNumberList(const unsigned C_INT32 & size) :
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

CParticleNumberList &
CParticleNumberList::operator=(const CParticleNumberList & rhs)
{
  mSize = rhs.mSize;
  mDbl = rhs.mDbl;
  mInt = rhs.mInt;

  return *this;
}

const unsigned C_INT32 & CParticleNumberList::size() const
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

const CVector< C_FLOAT64 > & CParticleNumberList::getVectorDbl() const
  {return mDbl;}

const C_INT32 &
CParticleNumberList::getInt(const unsigned C_INT32 & index) const
  {return mInt[index];}

const CVector< C_INT32 > & CParticleNumberList::getVectorInt() const
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

void CParticleNumberList::setVector(const CVector< C_INT32 > & vector)
{
  assert (mSize == vector.size());

  unsigned C_INT32 i;

  for (i = 0; i < mSize; i++)
    {
      mInt[i] = vector[i];
      mDbl[i] = (C_FLOAT64) vector[i];
    }
}

void CParticleNumberList::setVector(const CVector< C_FLOAT64 > & vector)
{
  assert (mSize == vector.size());

  unsigned C_INT32 i;

  for (i = 0; i < mSize; i++)
    {
      mInt[i] = (C_INT32) vector[i];
      mDbl[i] = vector[i];
    }
}

std::ostream & operator << (std::ostream & os,
                            const CParticleNumberList & A)
{
  os << "Particle List: " << std::endl;
  os << "  Dbl: " << A.mDbl << std::endl;
  os << "  Int: " << A.mInt << std::endl;

  return os;
}
