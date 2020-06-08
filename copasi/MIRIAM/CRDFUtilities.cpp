// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#include <algorithm>

#include "copasi/copasi.h"

#include "CRDFUtilities.h"

// static
unsigned C_INT32 CRDFUtilities::fixLocalFileAboutReference(std::string & rdfXml,
    const std::string & newId,
    const std::string & oldId)
{
  // Nothing to do
  if (newId == oldId || rdfXml == "")
    return 0;

  // Determine the name space qualifier for http://www.w3.org/1999/02/22-rdf-syntax-ns#
  std::string Qualifier =
    getNameSpaceQualifier(rdfXml, "http://www.w3.org/1999/02/22-rdf-syntax-ns#");

  // Find all Qualifier:Description elements where the Qualifier:about attribute is
  // "#oldId"
  std::string::size_type start = 0;
  std::string::size_type end = 0;
  unsigned C_INT32 count = 0;

  // Find the next Qualifier:Description element.
  while (findNextElement(rdfXml, Qualifier + "Description", start, end))
    {
      // Determine the end of the element, i.e, a > which is not enclosed in " or '
      std::string::size_type pos = start;

      // Check whether we have a Qualifier:about attribute
      pos = rdfXml.find(Qualifier + "about=", start);

      if (pos < end && pos != std::string::npos)
        {
          pos += Qualifier.length() + 6;
          const char Quote = rdfXml[pos];
          pos++; // advance past Quote

          // Check whether we have a local id indicate by #
          if (rdfXml[pos] == '#')
            {
              pos++; // advance past #
              std::string::size_type len = rdfXml.find(Quote, pos) - pos;

              // Check whether we have a local file reference to the old id
              // or the old id was not given
              if (oldId == "" ||
                  rdfXml.substr(pos, len) == oldId)
                {
                  rdfXml.replace(pos, len, newId);
                  count++;
                }
            }
        }
    }

  return count;
}

// static
unsigned C_INT32 CRDFUtilities::fixSBMLRdf(std::string & rdfXml)
{

  // Nothing to do
  if (rdfXml == "")
    return 0;

  std::string::size_type start = 0;
  std::string::size_type end = 0;
  std::string::size_type pos = 0;
  unsigned C_INT32 count = 0;

  // Fix broken SBML RDF:
  // <dc:creator rdf:parseType="Resource">
  //   <rdf:Bag>
  // It is not allowed to use the attribute rdf:parseType="Resource" and <rdf:Bag> simultaneously

  // Determine the rdf name space qualifier for:
  std::string RDFQualifier =
    getNameSpaceQualifier(rdfXml, "http://www.w3.org/1999/02/22-rdf-syntax-ns#");

  // We first look for all elements having the attribute rdf:parseType="Resource"
  while (findNextElement(rdfXml, "", start, end))
    {
      if ((pos = std::min(rdfXml.find(RDFQualifier + "parseType=\"Resource\"", start),
                          rdfXml.find(RDFQualifier + "parseType='Resource'", start))) > end)
        continue;

      // We found the attribute.
      // Check whether the next element is an rdf:Bag
      // Remember the current candidate
      std::string::size_type currentStart = start;
      std::string::size_type currentEnd = end;

      if (findNextElement(rdfXml, "", start, end) &&
          findNextElement(rdfXml, RDFQualifier + "Bag", currentStart, currentEnd) &&
          start == currentStart &&
          end == currentEnd)
        {
          // The next element is a bag element. We therefore have to remove the attribute.
          rdfXml.erase(pos, RDFQualifier.length() + 20);
          end -= RDFQualifier.length() + 20;

          count++;
        }
    }

  start = 0;
  end = 0;
  pos = 0;

  // Fix broken SBML RDF:
  // <vCard:ORG>
  //  <vCard:Orgname>ORGANIZATION_NAME</vCard:Orgname>
  // </vCard:ORG>
  // The <vCard:ORG> element must have the attribute rdf:parseType="Resource".

  // Determine the vcard name space qualifier for:
  std::string VCardQualifier =
    getNameSpaceQualifier(rdfXml, "http://www.w3.org/2001/vcard-rdf/3.0#");

  // We first look for all elements having the attribute rdf:parseType="Resource"
  while (findNextElement(rdfXml, VCardQualifier + "ORG", start, end))
    {
      // Check whether the attribute rdf:parseType="Resource" is present.
      if ((pos = std::min(rdfXml.find(RDFQualifier + "parseType=\"Resource\"", start),
                          rdfXml.find(RDFQualifier + "parseType='Resource'", start))) < end)
        continue;

      // The attribute is missing we insert it.
      rdfXml.insert(end, " " + RDFQualifier + "parseType=\"Resource\"");
      count++;
    }

  return count;
}

// static
std::string CRDFUtilities::getNameSpaceQualifier(const std::string & rdfXml,
    const std::string & nameSpace)
{
  std::string::size_type start = 0;
  std::string::size_type end = 0;

  while (true)
    {
      // Locate first name space declaration
      start = rdfXml.find("xmlns:", end);

      if (start == std::string::npos)
        break;

      start += 6;
      end = rdfXml.find("=", start);

      if (end == std::string::npos)
        break;

      if (rdfXml.compare(end + 1, nameSpace.length() + 2, "\"" + nameSpace + "\"") &&
          rdfXml.compare(end + 1, nameSpace.length() + 2, "'" + nameSpace + "'"))
        continue;

      // We have the qualifier
      return rdfXml.substr(start, end - start) + ":";
    }

  return "";
}

// static
bool CRDFUtilities::findNextElement(const std::string & rdfXml,
                                    const std::string & elementName,
                                    std::string::size_type & start,
                                    std::string::size_type & end)
{
  static std::string WhiteSpace = "\x20\x09\x0D\x0A";

  bool ignore = false;
  bool ignoreDouble = false;
  bool ignoreSingle = false;

  if (end >= rdfXml.length())
    return false;

  std::string::const_iterator it = rdfXml.begin() + end;
  std::string::const_iterator itEnd = rdfXml.end();

  if (*it == '>' && it < itEnd) ++it;

  start = std::string::npos;
  end = std::string::npos;

  while (true)
    {
      for (; it < itEnd && end == std::string::npos; ++it)
        {
          switch (*it)
            {
              case '\'':
                if (!ignoreDouble)
                  {
                    ignore = !ignore;
                    ignoreSingle = !ignoreSingle;
                  }

                break;

              case '\"':
                if (!ignoreSingle)
                  {
                    ignore = !ignore;
                    ignoreDouble = !ignoreDouble;
                  }

                break;

              case '<':
                if (!ignore)
                  start = it - rdfXml.begin();

                break;

              case '>':
                if (!ignore && start != std::string::npos)
                  end = it - rdfXml.begin();

                break;

              default:
                break;
            }
        }

      if (end == std::string::npos)
        return false;

      if (elementName == "")
        return true;

      std::string::size_type NameStart = rdfXml.find_first_not_of(WhiteSpace, start + 1);
      std::string::size_type NameEnd = rdfXml.find_first_of(WhiteSpace + "/>", NameStart);

      if (rdfXml.substr(NameStart, NameEnd - NameStart) == elementName)
        return true;

      start = std::string::npos;
      end = std::string::npos;
    }

  return false;
}

CRDFUtilities::CRDFUtilities()
{}

CRDFUtilities::~CRDFUtilities()
{}
