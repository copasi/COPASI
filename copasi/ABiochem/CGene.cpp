/**
 *  CGene class.
 *  Written by Pedro Mendes September 2002.
 *  
 *  For representing a gene and all the elements needed for COPASI 
 *  to represent it in a model
 */

#ifdef WIN32
#pragma warning(disable : 4786)
#endif  // WIN32

#define  COPASI_TRACE_CONSTRUCTION
#include <iostream>
#include <string>
#include <vector>

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "ABiochem/CGene.h"

CGeneModifier::CGeneModifier(void)
{
  mModifier = NULL;
  mType = 0;
  mK = 1.0;
}

CGeneModifier::CGeneModifier(CGene * modf, C_INT32 type, C_FLOAT64 K, C_FLOAT64 n)
{
  mModifier = modf;
  if ((type >= 0) && (type < 2))
    mType = type;
  else
    type = 0;
  mK = K > 0.0 ? K : 1.0;
  mn = n > 0.0 ? n : 1.0;
}

CGeneModifier::~CGeneModifier()
{}

CGene * CGeneModifier::getModifier(void)
{
  return mModifier;
}

C_INT32 CGeneModifier::getType(void)
{
  return mType;
}

C_FLOAT64 CGeneModifier::getK(void)
{
  return mK;
}

C_FLOAT64 CGeneModifier::getn(void)
{
  return mn;
}

void CGeneModifier::cleanup()
{}

CGene::CGene()
{
  mInDegree = 0;
  mOutDegree = 0;
  mRate = 1.0;
  mDegradationRate = 1.0;
}

CGene::~CGene()
{}

void CGene::setName(const string & name)
{
  mName = name;
}

const string & CGene::getName() const
  {
    return mName;
  }

C_INT32 CGene::getModifierNumber()
{
  return mModifier.size();
}

CGene * CGene::getModifier(C_INT32 n)
{
  return mModifier[n]->getModifier();
}

void CGene::setRate(C_FLOAT64 rate)
{
  mRate = rate;
}

C_FLOAT64 CGene::getRate(void)
{
  return mRate;
}

void CGene::setDegradationRate(C_FLOAT64 rate)
{
  mDegradationRate = rate;
}

C_FLOAT64 CGene::getDegradationRate(void)
{
  return mDegradationRate;
}

void CGene::addModifier(CGene *modf, C_INT32 type, C_FLOAT64 K, C_FLOAT64 n)
{
  CGeneModifier *temp;
  temp = new CGeneModifier(modf, type, K, n);
  mModifier.add(temp);
  // increment the in-degree of this gene
  addInDegree();
  // and the out-degree of the modifier's
  modf->addOutDegree();
}

void CGene::removeModifier(CGene *modf)
{
  int i;

  for (i = 0; i < getModifierNumber(); i++)
    if (modf == getModifier(i))
      {
        // decrement the in-degree of this gene
        decreaseInDegree();
        // and the out-degree of the modifier's
        modf->decreaseOutDegree();
        mModifier.remove(i);
        return;
      }
}

C_INT32 CGene::getModifierType(C_INT32 n)
{
  return mModifier[n]->getType();
}

C_FLOAT64 CGene::getK(C_INT32 i)
{
  return mModifier[i]->getK();
}

C_FLOAT64 CGene::getn(C_INT32 i)
{
  return mModifier[i]->getn();
}

void CGene::cleanup()
{
  mModifier.cleanup();
}

C_INT32 CGene::getNegativeModifiers(void)
{
  C_INT32 i, n, s;
  s = mModifier.size();
  for (i = n = 0; i < s; i++)
    if (mModifier[i]->getType() == 0)
      n++;
  return n;
}

C_INT32 CGene::getPositiveModifiers(void)
{
  C_INT32 i, n, s;
  s = mModifier.size();
  for (i = n = 0; i < s; i++)
    if (mModifier[i]->getType() == 1)
      n++;
  return n;
}

C_INT32 CGene::getInDegree()
{
  return mInDegree;
}

void CGene::addInDegree()
{
  mInDegree++;
}

void CGene::decreaseInDegree()
{
  mInDegree--;
}

C_INT32 CGene::getOutDegree()
{
  return mOutDegree;
}

void CGene::addOutDegree()
{
  mOutDegree++;
}

void CGene::decreaseOutDegree()
{
  mOutDegree--;
}

C_INT32 CGene::getTotalDegree()
{
  return mOutDegree + mInDegree;
}
