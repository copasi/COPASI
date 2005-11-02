/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiParameterGroup.cpp,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/02 15:08:58 $
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
{
  if (!mValue.pGROUP)
    {
      mValue.pGROUP = new parameterGroup;
      mSize = sizeof(parameterGroup);
    }

  *this = src;
}

CCopasiParameterGroup::CCopasiParameterGroup(const std::string & name,
    const CCopasiContainer * pParent,
    const std::string & objectType):
    CCopasiParameter(name, CCopasiParameter::GROUP, NULL, pParent, objectType)
{
  if (!mValue.pGROUP)
    {
      mValue.pGROUP = new parameterGroup;
      mSize = sizeof(parameterGroup);
    }
}

CCopasiParameterGroup::~CCopasiParameterGroup()
{
  clear();
  pdelete(mValue.pGROUP);
}

bool CCopasiParameterGroup::elevateChildren() {return true;}

CCopasiParameterGroup & CCopasiParameterGroup::operator = (const CCopasiParameterGroup & rhs)
{
  if (getObjectName() != rhs.getObjectName())
    setObjectName(rhs.getObjectName());

  parameterGroup::const_iterator itRHS = rhs.mValue.pGROUP->begin();
  parameterGroup::const_iterator endRHS = rhs.mValue.pGROUP->end();

  parameterGroup::iterator itLHS = mValue.pGROUP->begin();
  parameterGroup::iterator endLHS = mValue.pGROUP->end();

  for (; itRHS != endRHS && itLHS != endLHS; ++itRHS, ++itLHS)
    **itLHS = **itRHS;

  CCopasiParameter * pParameter;

  for (; itRHS != endRHS; ++itRHS)
    {
      if ((*itRHS)->getType() == GROUP)
        pParameter = new CCopasiParameterGroup(* (CCopasiParameterGroup *) * itRHS);
      else
        pParameter = new CCopasiParameter(**itRHS);

      addParameter(pParameter);
    }

  if (itLHS != endLHS)
    {
      parameterGroup::iterator itTmp;
      for (itTmp = itLHS; itTmp != endLHS; ++itTmp)
        pdelete(*itTmp);

      mValue.pGROUP->erase(itLHS, endLHS);
    }

  return *this;
}

void CCopasiParameterGroup::print(std::ostream * ostream) const
{*ostream << *this;}

std::ostream &operator<<(std::ostream &os, const CCopasiParameterGroup & o)
{
  os << "<<< Parameter Group: " << o.getObjectName() << std::endl;

  CCopasiParameterGroup::parameterGroup::const_iterator it =
    o.CCopasiParameter::getValue().pGROUP->begin();
  CCopasiParameterGroup::parameterGroup::const_iterator end =
    o.CCopasiParameter::getValue().pGROUP->end();

  for (; it != end; ++it)
    {
      (*it)->print(&os);
      os << std::endl;
    }

  os << ">>> Parameter Group: " << o.getObjectName() << std::endl;
  return os;
}

bool operator==(const CCopasiParameterGroup & lhs,
                const CCopasiParameterGroup & rhs)
{
  if (lhs.getObjectName() != rhs.getObjectName()) return false;
  if (lhs.mValue.pGROUP->size() != rhs.mValue.pGROUP->size()) return false;

  CCopasiParameterGroup::parameterGroup::const_iterator itLhs =
    lhs.mValue.pGROUP->begin();
  CCopasiParameterGroup::parameterGroup::const_iterator endLhs =
    lhs.mValue.pGROUP->end();

  CCopasiParameterGroup::parameterGroup::const_iterator itRhs =
    rhs.mValue.pGROUP->begin();

  for (; itLhs != endLhs; ++itLhs, ++itRhs)
    if (!(**itLhs == **itRhs)) return false;

  return true;
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

CCopasiParameterGroup * CCopasiParameterGroup::assertGroup(const std::string & name)
{
  CCopasiParameterGroup * pGrp = getGroup(name);
  if (pGrp) return pGrp;

  removeParameter(name);

  addGroup(name);
  return getGroup(name);
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
  dynamic_cast<CCopasiParameter *>(const_cast< CCopasiObject * >(range.first->second));
}

const CCopasiParameter * CCopasiParameterGroup::getParameter(const std::string & name) const
  {
    std::pair < CCopasiContainer::objectMap::const_iterator,
    CCopasiContainer::objectMap::const_iterator > range =
      getObjects().equal_range(name);

    if (range.first == range.second) return NULL;

    return
    dynamic_cast<CCopasiParameter *>(range.first->second);
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

CCopasiParameterGroup * CCopasiParameterGroup::getGroup(const std::string & name)
{return dynamic_cast<CCopasiParameterGroup *>(getParameter(name));}

const CCopasiParameterGroup * CCopasiParameterGroup::getGroup(const std::string & name) const
  {return dynamic_cast<const CCopasiParameterGroup *>(getParameter(name));}

CCopasiParameterGroup * CCopasiParameterGroup::getGroup(const unsigned C_INT32 & index)
{return dynamic_cast<CCopasiParameterGroup *>(getParameter(index));}

const CCopasiParameterGroup * CCopasiParameterGroup::getGroup(const unsigned C_INT32 & index) const
  {return dynamic_cast<const CCopasiParameterGroup *>(getParameter(index));}

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

void CCopasiParameterGroup::clear()
{
  if (mValue.pGROUP)
    {
      index_iterator it = mValue.pGROUP->begin();
      index_iterator end = mValue.pGROUP->end();

      for (; it != end; ++it) pdelete(*it);

      mValue.pGROUP->clear();
    }
}

unsigned C_INT32 CCopasiParameterGroup::getIndex(const std::string & name) const
  {
    index_iterator it = mValue.pGROUP->begin();
    index_iterator end = mValue.pGROUP->end();

    for (unsigned C_INT32 i = 0; it != end; ++it, ++i)
      if (name == (*it)->getObjectName()) return i;;

    return C_INVALID_INDEX;
  }
