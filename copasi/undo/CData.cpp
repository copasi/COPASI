// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include <sstream>

#include "copasi/copasi.h"

#include "CData.h"

#include "copasi/utilities/utility.h"
#include "copasi/utilities/Cmd5.h"

CData::CData():
  std::map< std::string, CDataValue >()
{}

CData::CData(const CData & src):
  std::map< std::string, CDataValue >(src)
{}

CData::~CData()
{}

CData & CData::operator = (const CData & rhs)
{
  if (this != &rhs)
    {
      std::map< std::string, CDataValue >::operator =(rhs);
    }

  return *this;
}

bool CData::operator == (const CData & rhs) const
{
  return *static_cast< const std::map< std::string, CDataValue > * >(this) == *static_cast< const std::map< std::string, CDataValue > * >(&rhs);
}

bool CData::operator != (const CData & rhs) const
{
  return *static_cast< const std::map< std::string, CDataValue > * >(this) != *static_cast< const std::map< std::string, CDataValue > * >(&rhs);
}

const CDataValue & CData::getProperty(const std::string & name) const
{
  static const CDataValue NotFound(CDataValue::INVALID);

  std::map< std::string, CDataValue >::const_iterator found = find(name);

  if (found != end())
    {
      return found->second;
    }

  return NotFound;
}

const CDataValue & CData::getProperty(const Property & property) const
{
  return getProperty(PropertyName[property]);
}

CDataValue & CData::getProperty(const std::string & name)
{
  static CDataValue NotFound(CDataValue::INVALID);

  std::map< std::string, CDataValue >::iterator found = find(name);

  if (found != end())
    {
      return found->second;
    }

  return NotFound;
}

CDataValue & CData::getProperty(const Property & property)
{
  return getProperty(PropertyName[property]);
}

bool CData::addProperty(const std::string & name, const CDataValue & value)
{
  std::map< std::string, CDataValue >::iterator found = find(name);

  if (found != end())
    {
      found->second = value;
      return false;
    }

  insert(std::make_pair(name, value));
  return true;
}

bool CData::addProperty(const Property & property, const CDataValue & value)
{
  return addProperty(PropertyName[property], value);
}

bool CData::appendData(const CData & data)
{
  bool success = true;

  const_iterator it = data.begin();
  const_iterator end = data.end();

  for (; it != end; ++it)
    {
      operator[](it->first) = it->second;
    }

  return success;
}

bool CData::removeProperty(const std::string & name)
{
  std::map< std::string, CDataValue >::iterator found = find(name);

  if (found != end())
    {
      erase(found);
      return true;
    }

  return false;
}

bool CData::removeProperty(const Property & property)
{
  return removeProperty(PropertyName[property]);
}

bool CData::isSetProperty(const std::string & name) const
{
  return find(name) != end();
}

bool CData::isSetProperty(const Property & property) const
{
  return isSetProperty(PropertyName[property]);
}

bool CData::empty() const
{
  return std::map< std::string, CDataValue >::empty();
}

void CData::clear()
{
  std::map< std::string, CDataValue >::clear();
}

std::string CData::hash() const
{
  std::stringstream Data;
  Data << *this;

  return Cmd5::digest(Data);
}

CData::const_iterator CData::begin() const
{
  return std::map< std::string, CDataValue >::begin();
}

CData::const_iterator CData::end() const
{
  return std::map< std::string, CDataValue >::end();
}

std::ostream & operator << (std::ostream & os, const CData & o)
{
  std::map< std::string, CDataValue >::const_iterator it = o.begin();
  std::map< std::string, CDataValue >::const_iterator end = o.end();

  for (; it != end; ++it)
    os << it->first << ": " << it->second << "\n";

  return os;
}

std::istream & operator >> (std::istream & is, const CData & /* i */)
{
  // TODO CRITICAL Implement me!
  return is;
}
