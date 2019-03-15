// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.


#include "CVCard.h"

CVCard::CVCard(const std::string & type)
  : VCard()
  , mType(type)
{}

CVCard::CVCard(XMLInputStream & stream, const XMLToken & current)
  : VCard()
  , mType()
{
  mType = current.getName();

  if (mType != "creator" &&
      mType != "contributor" &&
      mType != "publisher")
    {
      mType.clear();

      return;
    }

  VCard::operator = (VCard(stream, current));
}

CVCard::CVCard(const CVCard & src)
  : VCard(src)
  , mType(src.mType)
{}

CVCard::~CVCard()
{}

void CVCard::setType(const std::string & type)
{
  mType = type;
}

const std::string & CVCard::getType() const
{
  return mType;
}



XMLOutputStream & operator << (XMLOutputStream & xml, const CVCard & vcard)
{
  if (!vcard.isEmpty())
    {
      xml.startElement(vcard.getType(), "dcterms");
      xml.writeAttribute("parseType", "rdf", "Resource");

      if (!vcard.getFamilyName().empty() || !vcard.getGivenName().empty())
        {
          xml.startElement("hasName", "vCard");
          xml.writeAttribute("parseType", "rdf", "Resource");

          if (!vcard.getFamilyName().empty())
            {
              xml.startElement("family-name", "vCard");
              xml << vcard.getFamilyName();
              xml.endElement("family-name", "vCard");
            }

          if (!vcard.getGivenName().empty())
            {
              xml.startElement("given-name", "vCard");
              xml << vcard.getGivenName();
              xml.endElement("given-name", "vCard");
            }

          xml.endElement("hasName", "vCard");
        }

      if (!vcard.getEmail().empty())
        {
          xml.startElement("hasEmail", "vCard");
          xml.writeAttribute("resource", "rdf", vcard.getEmail());
          xml.endElement("hasEmail", "vCard");
        }

      if (!vcard.getOrganization().empty())
        {
          xml.startElement("organization-name", "vCard");
          xml << vcard.getOrganization();
          xml.endElement("organization-name", "vCard");
        }

      xml.endElement(vcard.getType(), std::string("dcterms"));
    }

  return xml;
}
