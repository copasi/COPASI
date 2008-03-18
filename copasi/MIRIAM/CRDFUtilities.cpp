// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFUtilities.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/18 20:27:43 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CRDFUtilities.h"

// static
unsigned C_INT32 CRDFUtilities::fixLocalFileAboutReference(std::string & rdfXml,
    const std::string & newId,
    const std::string & oldId)
{
  // Nothing to do
  if (newId == oldId || rdfXml == "")
    return 0;

  // Determine the name space qualifier for:
  // http://www.w3.org/1999/02/22-rdf-syntax-ns#
  std::string::size_type start =
    rdfXml.find("http://www.w3.org/1999/02/22-rdf-syntax-ns#");

  // TODO this is acutally an error and we need to create a message
  if (start == std::string::npos)
    return 0;

  // We need to backtrack to find the qualifier
  std::string::size_type end = rdfXml.rfind('=', start);

  // TODO this is acutally an error and we need to create a message
  if (end == std::string::npos)
    return 0;

  start = rdfXml.rfind(':', end);

  // TODO this is acutally an error and we need to create a message
  if (start == std::string::npos)
    return 0;

  start++;
  std::string Qualifier = rdfXml.substr(start, end - start);

  // Find all Qualifier:Description elements where the Qualifier:about attribute is
  // "#oldId"
  start = 0;
  unsigned C_INT32 count = 0;
  // Find the next Qualifier:Description element.
  while ((start = rdfXml.find("<" + Qualifier + ":Description", start)) != std::string::npos)
    {
      // Determine the end of the element, i.e, a > which is not enclosed in " or '
      std::string::size_type pos = start;
      bool ignoreSingle = false;
      bool ignoreDouble = false;
      bool ignore = false;
      for (end = rdfXml.length(); pos < end; ++pos)
        {
          switch (rdfXml[pos])
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

            case '>':
              if (!ignore)
                end = pos;
              break;

            default:
              break;
            }
        }

      // Check whether we have a Qualifier:about attribute
      pos = rdfXml.find(Qualifier + ":about=", start);
      if (pos < end && pos != std::string::npos)
        {
          pos += Qualifier.length() + 7;
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

      start = end;
    }

  return count;
}

CRDFUtilities::CRDFUtilities()
{}

CRDFUtilities::~CRDFUtilities()
{}
