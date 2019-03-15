// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CModelVersion.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: shoops
 */

#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLOutputStream.h>
#include <sbml/xml/XMLErrorLog.h>

#include "CModelVersion.h"

CModelVersion::CModelVersion()
  : CAnnotation()
  , CVCard("creator")
  , mName()
  , mParentName()
  , mUTCTimeStamp()
{}

CModelVersion::CModelVersion(const CModelVersion & src)
  : CAnnotation(src)
  , CVCard(src)
  , mName(src.mName)
  , mParentName(src.mParentName)
  , mUTCTimeStamp(src.mUTCTimeStamp)
{}

CModelVersion::CModelVersion(const std::string & version,
                             const std::string &  parentName,
                             const std::string &  authorGivenName,
                             const std::string &  authorFamilyName,
                             const std::string &  authorOrganization,
                             const std::string &  authorEmail,
                             const std::string &  comments,
                             const std::string &  time)
  : CAnnotation()
  , CVCard("creator")
  , mName(version)
  , mParentName(parentName)
  , mUTCTimeStamp(time)
{
  setNotes(comments);
  setGivenName(authorGivenName);
  setFamilyName(authorFamilyName);
  setOrganization(authorOrganization);
  setEmail(authorEmail);
}

CModelVersion::CModelVersion(XMLInputStream & stream, const XMLToken & current)
  : CAnnotation()
  , CVCard()
  , mName()
  , mParentName()
  , mUTCTimeStamp()
{
  if (current.getName() != "version") return;

  mName = current.getAttrValue("name");
  mParentName = current.getAttrValue("derivedFrom");

  while (stream.isGood())
    {
      stream.skipText();

      // grab the next element
      XMLToken Current = stream.next();

      // if we reached the end table element, we stop
      if (Current.isEndFor(current))
        break;

      if (!Current.isStart()) continue;

      const std::string & CurrentName = Current.getName();

      if (CurrentName == "RDF" ||
          CurrentName == "Description" ||
          CurrentName == "created")
        {
          // We do nothing
        }
      else if (CurrentName == "description")
        {
          setNotes(stream.next().getCharacters());
        }
      else if (CurrentName == "W3CDTF")
        {
          mUTCTimeStamp = stream.next().getCharacters();
        }
      else if (CurrentName == "creator")
        {
          CVCard::operator = (CVCard(stream, Current));
        }
      else if (stream.getErrorLog() != NULL)
        {
          stream.getErrorLog()->add(XMLError(MissingXMLElements, "unexpected element in 'version' element"));
        }
    }
}

CModelVersion::~CModelVersion()
{}

XMLOutputStream & operator << (XMLOutputStream & xml, const CModelVersion & version)
{
  xml.startElement("version");
  xml.writeAttribute("name", version.mName);
  xml.writeAttribute("derivedFrom", version.mParentName);

  xml.startElement("RDF", "rdf");
  xml.writeAttribute("rdf", "xmlns", "http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  xml.writeAttribute("dcterms", "xmlns", "http://purl.org/dc/terms/");
  xml.writeAttribute("vCard", "xmlns", "http://www.w3.org/2006/vcard/ns#");

  xml.startElement("Description", "rdf");
  xml.writeAttribute("about", "rdf", "#" + version.mName);

  xml.startElement("description", "dcterms");
  xml << version.getNotes();
  xml.endElement("description", "dcterms");

  xml.startElement("created", "dcterms");

  xml.startElement("W3CDTF", "dcterms");
  xml << version.mUTCTimeStamp;
  xml.endElement("W3CDTF", "dcterms");

  xml.endElement("created", "dcterms");

  xml << *static_cast< const CVCard * >(& version);
  xml.endElement("Description", "rdf");

  xml.endElement("RDF", "rdf");

  xml.endElement("version");

  return xml;
}

const std::string & CModelVersion::getName() const
{
  return mName;
}

const std::string & CModelVersion::getParentName() const
{
  return mParentName;
}

const std::string & CModelVersion::getUTCTimeStamp() const
{
  return mUTCTimeStamp;
}
