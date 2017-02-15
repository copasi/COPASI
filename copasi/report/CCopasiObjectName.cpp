// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * Class CCopasiObjectName
 *
 * This class is the class for handling Copasi object names.
 *
 * Copyright Stefan Hoops 2002
 */

//TODO what does getName() vs. getObjectName do?

#include <sstream>

#include "copasi.h"
#include "CCopasiObjectName.h"

using std::string;

CCopasiObjectName::CCopasiObjectName():
  string()
{}

CCopasiObjectName::CCopasiObjectName(const std::string & name):
  string(name)
{}

CCopasiObjectName::CCopasiObjectName(const CCopasiObjectName & src):
  string(src)
{}

CCopasiObjectName::~CCopasiObjectName()
{}

CCopasiObjectName CCopasiObjectName::getPrimary() const
{return substr(0, findEx(","));}

CCopasiObjectName CCopasiObjectName::getRemainder() const
{
  std::string::size_type pos = findEx(",");

  if (pos == std::string::npos) return CCopasiObjectName();

  return substr(pos + 1);
}

std::string CCopasiObjectName::getObjectType() const
{
  CCopasiObjectName Primary(getPrimary());

  return CCopasiObjectName::unescape(Primary.substr(0, Primary.findEx("=")));
}

std::string CCopasiObjectName::getObjectName() const
{
  CCopasiObjectName Primary = getPrimary();
  std::string::size_type pos = Primary.findEx("=");

  if (pos == std::string::npos) return "";

  CCopasiObjectName tmp = Primary.substr(pos + 1);

  if (getObjectType() != "String")
    {
      tmp = tmp.substr(0, tmp.findEx("["));
    }

  return CCopasiObjectName::unescape(tmp);
}

size_t
CCopasiObjectName::getElementIndex(const size_t & pos) const
{
  std::string Index = getElementName(pos);
  std::stringstream tmp(Index);

  size_t index = C_INVALID_INDEX;

  tmp >> index;

  if (tmp.fail()) return C_INVALID_INDEX;

  tmp << index;

  if (Index != tmp.str()) return C_INVALID_INDEX;

  return index;
}

std::string CCopasiObjectName::getElementName(const size_t & pos,
    const bool & unescape) const
{
  CCopasiObjectName Primary = getPrimary();

  std::string::size_type open = Primary.findEx("[");
  size_t i;

  for (i = 0; i < pos && open != std::string::npos; i++)
    open = Primary.findEx("[", open + 1);

  std::string::size_type close = Primary.findEx("]", open + 1);

  if (open == std::string::npos || close == std::string::npos) return "";

  if (unescape)
    return CCopasiObjectName::unescape(Primary.substr(open + 1,
                                       close - open - 1));

  return Primary.substr(open + 1, close - open - 1);
}

std::string CCopasiObjectName::escape(const std::string & name)
{
#define toBeEscaped "\\[]=,>"
  std::string Escaped(name);
  std::string::size_type pos = Escaped.find_first_of(toBeEscaped);

  while (pos != std::string::npos)
    {
      Escaped.insert(pos, "\\");
      pos += 2;
      pos = Escaped.find_first_of(toBeEscaped, pos);
    }

  return Escaped;
#undef toBeEscaped
}

std::string CCopasiObjectName::unescape(const std::string & name)
{
  std::string Unescaped(name);
  std::string::size_type pos = Unescaped.find("\\");

  while (pos != std::string::npos)
    {
      Unescaped.erase(pos, 1);
      pos++;
      pos = Unescaped.find("\\", pos);
    }

  return Unescaped;
}

std::string::size_type
CCopasiObjectName::findEx(const std::string & toFind,
                          const std::string::size_type & pos) const
{
  std::string::size_type where = find_first_of(toFind, pos);

  std::string::size_type tmp;

  while (where && where != std::string::npos)
    {
      tmp = find_last_not_of("\\", where - 1);

      if ((where - tmp) % 2)
        return where;

      where = find_first_of(toFind, where + 1);
    }

  return where;
}

//********** CRegisteredObjectName ***************

std::set<CRegisteredObjectName*> CRegisteredObjectName::mSet;

CRegisteredObjectName::CRegisteredObjectName():
  CCopasiObjectName()
{
  mSet.insert(this);
}

CRegisteredObjectName::CRegisteredObjectName(const std::string & name):
  CCopasiObjectName(name)
{
  mSet.insert(this);
}

CRegisteredObjectName::CRegisteredObjectName(const CRegisteredObjectName & src):
  CCopasiObjectName(src)
{
  mSet.insert(this);
}

CRegisteredObjectName::~CRegisteredObjectName()
{
  mSet.erase(this);
}
