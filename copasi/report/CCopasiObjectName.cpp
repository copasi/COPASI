/**
 * Class CCopasiObjectName
 *
 * This class is the class for handling Copasi object names.
 *
 * Copyright Stefan Hoops 2002
 */

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

CCopasiObjectName::~CCopasiObjectName() {}

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
    std::string::size_type pos = findEx("=");

    if (pos == std::string::npos) return "";

    CCopasiObjectName tmp = Primary.substr(pos + 1);
    return CCopasiObjectName::unescape(tmp.substr(0, tmp.findEx("[")));
  }

unsigned C_INT32
CCopasiObjectName::getIndex(const unsigned C_INT32 & pos) const
  {
    std::string Index = getName(pos);
    std::stringstream tmp(Index);

    unsigned C_INT32 index = C_INVALID_INDEX;

    tmp >> index;
    if (tmp.fail()) return C_INVALID_INDEX;

    tmp << index;
    if (Index != tmp.str()) return C_INVALID_INDEX;

    return index;
  }

std::string CCopasiObjectName::getName(const unsigned C_INT32 & pos) const
  {
    CCopasiObjectName Primary = getPrimary();

    std::string::size_type open = findEx("[");
    for (unsigned C_INT32 i = 0; i < pos && open != std::string::npos; i++)
      open = findEx("[", open + 1);

    std::string::size_type close = findEx("]", open + 1);

    if (open == std::string::npos || close == std::string::npos) return "";

    return CCopasiObjectName::unescape(Primary.substr(open + 1,
                                       close - open - 1));
  }

std::string CCopasiObjectName::escape(const std::string & name)
{
#define toBeEscaped "\\[]=,"
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
