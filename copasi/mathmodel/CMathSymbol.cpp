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
    tmpName << name << "_" << count++;

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

CMathSymbol::~CMathSymbol() {mList.erase(mName);}

bool CMathSymbol::setName(std::string & name)
{
  mList.erase(mName);

  mName = name;
  if (alternateName(mName) == name)
    {
      mList[mName] = this;
      return true;
    }
  else
    {
      mList[mName] = this;
      return false;
    }
}

const std::string & CMathSymbol::getName() const {return mName;}

bool CMathSymbol::setCN(const CCopasiObjectName & cn,
                        const CCopasiContainer * pContainer)
{
  mCN = cn;
  mpObject = const_cast<CCopasiContainer *>(pContainer)->getObject(mCN);
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
