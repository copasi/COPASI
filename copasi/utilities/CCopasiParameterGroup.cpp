/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiParameterGroup.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/21 20:36:38 $
   End CVS Header */

/**
 *  CCopasiParameterGroup class.
 *  This class is used to describe parameters. This class is intended
 *  to be used with integration or optimization methods or reactions.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#include "copasi.h"

#include "CCopasiParameterGroup.h"
#include "CCopasiMessage.h"

CCopasiParameterGroup::CCopasiParameterGroup():
    CCopasiParameter("NoName", GROUP)
{}

CCopasiParameterGroup::CCopasiParameterGroup(const CCopasiParameterGroup & src,
    const CCopasiContainer * pParent):
    CCopasiParameter(src, pParent)
{createGroup(src.mValue.pGROUP);}

CCopasiParameterGroup::CCopasiParameterGroup(const std::string & name,
    const CCopasiContainer * pParent,
    const std::string & objectType):
    CCopasiParameter(name, CCopasiParameter::GROUP, NULL, pParent, objectType)
{createGroup();}

CCopasiParameterGroup::~CCopasiParameterGroup()
{deleteGroup();}

CCopasiParameterGroup & CCopasiParameterGroup::operator = (const CCopasiParameterGroup & rhs)
{
  setObjectName(rhs.getObjectName());
  createGroup(rhs.mValue.pGROUP);

  return *this;
}

void CCopasiParameterGroup::createGroup(const parameterGroup * pGroup)
{
  deleteGroup();

  mValue.pGROUP = new parameterGroup;
  mSize = sizeof(parameterGroup);

  if (!pGroup) return;

  index_iterator it = const_cast< parameterGroup * >(pGroup)->begin();
  index_iterator end = const_cast< parameterGroup * >(pGroup)->end();

  CCopasiParameter * pParameter;

  for (; it != end; ++it)
    {
      if ((*it)->getType() == GROUP)
        pParameter = new CCopasiParameterGroup(* (CCopasiParameterGroup *) * it);
      else
        pParameter = new CCopasiParameter(**it);

      addParameter(pParameter);
    }
}

void CCopasiParameterGroup::deleteGroup()
{
  if (!mValue.pGROUP) return;

  index_iterator it = mValue.pGROUP->begin();
  index_iterator end = mValue.pGROUP->end();

  for (; it != end; ++it) pdelete(*it);

  if (mValue.pGROUP)
    {
      delete mValue.pGROUP;
      mValue.pGROUP = NULL;
    }
}

bool CCopasiParameterGroup::addParameter(const CCopasiParameter & parameter)
{
  if (parameter.getType() == CCopasiParameter::GROUP)
    {
      CCopasiParameterGroup * pGroup =
        new CCopasiParameterGroup(*dynamic_cast<const CCopasiParameterGroup *>(&parameter));
      addParameter(pGroup);
    }
  else
    {
      CCopasiParameter * pParameter = new CCopasiParameter(parameter);
      addParameter(pParameter);
    }

  return true;
}

void CCopasiParameterGroup::addParameter(CCopasiParameter * pParameter)
{
  CCopasiContainer::add(pParameter, true);
  mValue.pGROUP->push_back(pParameter);
}

CCopasiParameterGroup::name_iterator CCopasiParameterGroup::beginName() const
  {return const_cast< CCopasiContainer::objectMap * >(&getObjects())->begin();}

CCopasiParameterGroup::name_iterator CCopasiParameterGroup::nameEnd() const
  {return const_cast< CCopasiContainer::objectMap * >(&getObjects())->end();}

CCopasiParameterGroup::index_iterator CCopasiParameterGroup::beginIndex() const
  {return mValue.pGROUP->begin();}

CCopasiParameterGroup::index_iterator CCopasiParameterGroup::endIndex() const
  {return mValue.pGROUP->end();}

bool CCopasiParameterGroup::addParameter(const std::string & name,
    const CCopasiParameter::Type type)
{
  CCopasiParameter * pParameter;

  if (type == GROUP)
    pParameter = new CCopasiParameterGroup(name);
  else
    pParameter = new CCopasiParameter(name, type);

  addParameter(pParameter);

  return true;
}

bool CCopasiParameterGroup::addGroup(const std::string & name)
{
  addParameter(new CCopasiParameterGroup(name));
  return true;
}

bool CCopasiParameterGroup::removeParameter(const std::string & name)
{
  unsigned C_INT32 index = getIndex(name);

  if (index != C_INVALID_INDEX)
    {
      index_iterator it =
        mValue.pGROUP->begin() + index;

      pdelete(*it);
      mValue.pGROUP->erase(it, it + 1);

      return true;
    }

  return false;
}

bool CCopasiParameterGroup::removeParameter(const unsigned C_INT32 & index)
{
  if (index < size())
    {
      index_iterator it =
        mValue.pGROUP->begin() + index;

      pdelete(*it);
      mValue.pGROUP->erase(it, it + 1);

      return true;
    }

  return false;
}

CCopasiParameter * CCopasiParameterGroup::getParameter(const std::string & name)
{
  std::pair < CCopasiContainer::objectMap::const_iterator,
  CCopasiContainer::objectMap::const_iterator > range =
    getObjects().equal_range(name);

  if (range.first == range.second) return NULL;

  return
  (CCopasiParameter *) (CCopasiContainer *)
  const_cast< CCopasiObject * >(range.first->second);
}

CCopasiParameter * CCopasiParameterGroup::getParameter(const unsigned C_INT32 & index)
{
  if (index < size())
    return * (mValue.pGROUP->begin() + index);

  return NULL;
}

const CCopasiParameter * CCopasiParameterGroup::getParameter(const unsigned C_INT32 & index) const
  {
    if (index < size())
      return * (mValue.pGROUP->begin() + index);

    return NULL;
  }

const CCopasiParameter::Value & CCopasiParameterGroup::getValue(const std::string & name) const
  {
    CCopasiParameter * pParameter =
      const_cast< CCopasiParameterGroup * >(this)->getParameter(name);

    if (!pParameter)
      fatalError();

    return pParameter->getValue();
  }

const CCopasiParameter::Value & CCopasiParameterGroup::getValue(const unsigned C_INT32 & index) const
  {
    CCopasiParameter * pParameter =
      const_cast< CCopasiParameterGroup * >(this)->getParameter(index);

    if (!pParameter)
      fatalError();

    return pParameter->getValue();
  }

CCopasiParameter::Value & CCopasiParameterGroup::getValue(const std::string & name)
{
  CCopasiParameter * pParameter = getParameter(name);

  if (!pParameter)
    fatalError();

  return pParameter->getValue();
}

CCopasiParameter::Value & CCopasiParameterGroup::getValue(const unsigned C_INT32 & index)
{
  CCopasiParameter * pParameter = getParameter(index);

  if (!pParameter)
    fatalError();

  return pParameter->getValue();
}

CCopasiParameter::Type CCopasiParameterGroup::getType(const std::string & name) const
  {
    CCopasiParameter * pParameter =
      const_cast< CCopasiParameterGroup * >(this)->getParameter(name);

    if (pParameter) return pParameter->getType();

    return CCopasiParameter::INVALID;
  }

CCopasiParameter::Type CCopasiParameterGroup::getType(const unsigned C_INT32 & index) const
  {
    CCopasiParameter * pParameter =
      const_cast< CCopasiParameterGroup * >(this)->getParameter(index);

    if (pParameter) return pParameter->getType();

    return CCopasiParameter::INVALID;
  }

std::string CCopasiParameterGroup::getKey(const std::string & name) const
  {
    CCopasiParameter * pParameter =
      const_cast< CCopasiParameterGroup * >(this)->getParameter(name);

    if (pParameter) return pParameter->getKey();

    return "Not Found";
  }

std::string CCopasiParameterGroup::getKey(const unsigned C_INT32 & index) const
  {
    CCopasiParameter * pParameter =
      const_cast< CCopasiParameterGroup * >(this)->getParameter(index);

    if (pParameter) return pParameter->getKey();

    return "Not Found";
  }

const std::string & CCopasiParameterGroup::getName(const unsigned C_INT32 & index) const
  {
    static std::string Invalid("Invalid Index");

    CCopasiParameter * pParameter =
      const_cast< CCopasiParameterGroup * >(this)->getParameter(index);

    if (pParameter) return pParameter->getObjectName();

    return Invalid;
  }

bool CCopasiParameterGroup::swap(const unsigned C_INT32 & iFrom,
                                 const unsigned C_INT32 & iTo)
{
  index_iterator from = beginIndex() + iFrom;
  index_iterator to = beginIndex() + iTo;

  return swap(from, to);
}

bool CCopasiParameterGroup::swap(index_iterator & from,
                                 index_iterator & to)
{
  if (from < beginIndex() || endIndex() <= from ||
      to < beginIndex() || endIndex() <= to)
    return false;

  CCopasiParameter *tmp = *from;
  *from = *to;
  *to = tmp;

  return true;
}

unsigned C_INT32 CCopasiParameterGroup::size() const
{return mValue.pGROUP->size();}

void CCopasiParameterGroup::clear() {createGroup();}

unsigned C_INT32 CCopasiParameterGroup::getIndex(const std::string & name) const
  {
    index_iterator it = mValue.pGROUP->begin();
    index_iterator end = mValue.pGROUP->end();

    for (unsigned C_INT32 i = 0; it != end; ++it, ++i)
      if (name == (*it)->getObjectName()) return i;;

    return C_INVALID_INDEX;
  }
