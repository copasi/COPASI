/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiParameterGroup.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/12 16:44:57 $
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

CCopasiParameterGroup::CCopasiParameterGroup():
    CCopasiParameter("NoName", GROUP)
{}

CCopasiParameterGroup::CCopasiParameterGroup(const CCopasiParameterGroup & src,
    const CCopasiContainer * pParent):
    CCopasiParameter(src, pParent)
{createGroup((parameterGroup *) src.CCopasiParameter::getValue());}

CCopasiParameterGroup::CCopasiParameterGroup(const std::string & name,
    const CCopasiContainer * pParent,
    const std::string & objectType):
    CCopasiParameter(name, CCopasiParameter::GROUP, NULL, pParent, objectType)
{createGroup();}

CCopasiParameterGroup::~CCopasiParameterGroup()
{deleteGroup();}

void CCopasiParameterGroup::createGroup(const parameterGroup * pGroup)
{
  deleteGroup();

  mpValue = new parameterGroup;
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
  if (!mpValue) return;

  index_iterator it = ((parameterGroup *) mpValue)->begin();
  index_iterator end = ((parameterGroup *) mpValue)->end();

  for (; it != end; ++it) pdelete(*it);

  if (mpValue)
    {
      delete (parameterGroup *) mpValue;
      mpValue = NULL;
    }
}

void CCopasiParameterGroup::addParameter(CCopasiParameter * pParameter)
{
  CCopasiContainer::add(pParameter);
  ((parameterGroup *) mpValue)->push_back(pParameter);
}

CCopasiParameterGroup::name_iterator CCopasiParameterGroup::beginName() const
  {return const_cast< CCopasiContainer::objectMap * >(&getObjects())->begin();}

CCopasiParameterGroup::name_iterator CCopasiParameterGroup::nameEnd() const
  {return const_cast< CCopasiContainer::objectMap * >(&getObjects())->end();}

CCopasiParameterGroup::index_iterator CCopasiParameterGroup::beginIndex() const
  {return ((parameterGroup *) mpValue)->begin();}

CCopasiParameterGroup::index_iterator CCopasiParameterGroup::endIndex() const
  {return ((parameterGroup *) mpValue)->end();}

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
        ((parameterGroup *) mpValue)->begin() + getIndex(name);

      ((parameterGroup *) mpValue)->erase(it, it + 1);
      pdelete(*it);

      return true;
    }

  return false;
}

bool CCopasiParameterGroup::removeParameter(const unsigned C_INT32 & index)
{
  if (index < size())
    {
      index_iterator it =
        ((parameterGroup *) mpValue)->begin() + index;

      ((parameterGroup *) mpValue)->erase(it, it + 1);
      pdelete(*it);

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
    return * (((parameterGroup *) mpValue)->begin() + index);

  return NULL;
}

const void * CCopasiParameterGroup::getValue(const std::string & name) const
  {
    CCopasiParameter * pParameter =
      const_cast< CCopasiParameterGroup * >(this)->getParameter(name);

    if (pParameter) return pParameter->getValue();

    return NULL;
  }

const void * CCopasiParameterGroup::getValue(const unsigned C_INT32 & index) const
  {
    CCopasiParameter * pParameter =
      const_cast< CCopasiParameterGroup * >(this)->getParameter(index);

    if (pParameter) return pParameter->getValue();

    return NULL;
  }

void * CCopasiParameterGroup::getValue(const std::string & name)
{
  CCopasiParameter * pParameter = getParameter(name);

  if (pParameter) return pParameter->getValue();

  return NULL;
}

void * CCopasiParameterGroup::getValue(const unsigned C_INT32 & index)
{
  CCopasiParameter * pParameter = getParameter(index);

  if (pParameter) return pParameter->getValue();

  return NULL;
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

    if (pParameter) return pParameter->getName();

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
{return ((parameterGroup *) mpValue)->size();}

void CCopasiParameterGroup::clear() {createGroup();}

unsigned C_INT32 CCopasiParameterGroup::getIndex(const std::string & name) const
  {
    index_iterator it = ((parameterGroup *) mpValue)->begin();
    index_iterator end = ((parameterGroup *) mpValue)->end();

    for (unsigned C_INT32 i = 0; it != end; ++it, ++i)
      if (name == (*it)->getName()) return i;;

    return C_INVALID_INDEX;
  }
