/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CParticleNumberList.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/18 16:53:11 $
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
    mDbl(size)
{}

CParticleNumberList::CParticleNumberList(const CParticleNumberList & src) :
    mSize(src.mSize),
    mDbl(src.mDbl)
{}

CParticleNumberList::~CParticleNumberList()
{}

CParticleNumberList &
CParticleNumberList::operator=(const CParticleNumberList & rhs)
{
  mSize = rhs.mSize;
  mDbl = rhs.mDbl;

  return *this;
}

const unsigned C_INT32 & CParticleNumberList::size() const
  {return mSize;}

void CParticleNumberList::resize(const unsigned C_INT32 & size)
{
  mSize = size;
  mDbl.resize(mSize);
}

const C_FLOAT64 &
CParticleNumberList::getDbl(const unsigned C_INT32 & index) const
  {return mDbl[index];}

const CVector< C_FLOAT64 > & CParticleNumberList::getVector() const
  {return mDbl;}

void CParticleNumberList::set(const unsigned C_INT32 & index,
                              const C_FLOAT64 & value)
{
  assert (mSize > index);

  mDbl[index] = value;
}

void CParticleNumberList::setVector(const CVector< C_FLOAT64 > & vector)
{
  assert (mSize == vector.size());
  mDbl = vector;
}

std::ostream & operator << (std::ostream & os,
                            const CParticleNumberList & A)
{
  os << "Particle List: " << A.mDbl << std::endl;

  return os;
}
