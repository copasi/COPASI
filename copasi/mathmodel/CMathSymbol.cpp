/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/mathmodel/Attic/CMathSymbol.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:24:29 $
   End CVS Header */

/**
 *  CMathSymbol class.
 *  The class CMathSymbol associates a symbol with a CCopasiObject assuring
 *  that the symbol name is unique.
 *  Symbols are used to enhance redability of mathematical expresions.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */
#include <sstream>

#include "copasi.h"
#include "CMathSymbol.h"

std::map< std::string, CMathSymbol * > CMathSymbol::mList;

std::string & CMathSymbol::alternateName(std::string & name)
{
  unsigned C_INT32 count = 1;
  std::stringstream tmpName;
  tmpName << name;

  while (mList.count(tmpName.str()))
    {
      tmpName.seekp(0);
      tmpName << name << "_" << count++;
    }

  return name = tmpName.str();
}

CMathSymbol * CMathSymbol::find(const CCopasiObject * pObject)
{
  std::map< std::string, CMathSymbol * >::iterator it = mList.begin();
  std::map< std::string, CMathSymbol * >::iterator end = mList.end();

  while (it != end && it->second->getObject() != pObject) it++;

  if (it == end) return NULL;
  else return it->second;
}

CMathSymbol::CMathSymbol():
    mName(),
    mCN(),
    mpObject(NULL)
{}

CMathSymbol::CMathSymbol(std::string & name):
    mName(alternateName(name)),
    mCN(),
    mpObject(NULL)
{mList[mName] = this;}

CMathSymbol::CMathSymbol(const CCopasiObject * pObject):
    mName(pObject->getObjectName()),
    mCN(pObject->getCN()),
    mpObject(const_cast< CCopasiObject * >(pObject))
{
  alternateName(mName);
  mList[mName] = this;
}

CMathSymbol::CMathSymbol(const CMathSymbol & src):
    mName("copy of " + src.mName),
    mCN(src.mCN),
    mpObject(src.mpObject)
{
  alternateName(mName);
  mList[mName] = this;
}

CMathSymbol::~CMathSymbol()
{
  mList.erase(mName);
}

bool CMathSymbol::setName(std::string & name)
{
  bool Success = true;

  mList.erase(mName);

  mName = name;
  if (alternateName(mName) == name) Success = true;
  else Success = false;
  name = mName;

  mList[mName] = this;

  return Success;
}

const std::string & CMathSymbol::getName() const {return mName;}

bool CMathSymbol::setCN(const CCopasiObjectName & cn,
                        const CCopasiContainer * pContainer)
{
  mCN = cn;
  mpObject = const_cast<CCopasiObject *>(const_cast<CCopasiContainer *>(pContainer)->getObject(mCN));
  if (mpObject)
    return true;
  else
    return false;
}

const CCopasiObjectName & CMathSymbol::getCN() const {return mCN;}

bool CMathSymbol::setObject(CCopasiObject * pObject)
{
  mpObject = pObject;
  return true;
}

const CCopasiObject * CMathSymbol::getObject() const {return mpObject;}

CCopasiObject * CMathSymbol::getObject() {return mpObject;}
