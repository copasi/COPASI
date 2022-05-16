// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

#include <stdlib.h>

#include "copasi/copasi.h"

#include "CConstants.h"
#include "CRDFGraph.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/commandline/CConfigurationFile.h"

//static
const CMIRIAMResources * CMIRIAMResourceObject::mpResources = NULL;

size_t CMIRIAMResourceObject::getResource(const std::string & URI)
{return mpResources->getMIRIAMResourceIndex(URI);}

//static
const CMIRIAMResources & CMIRIAMResourceObject::getResourceList()
{return *mpResources;}

// static
void CMIRIAMResourceObject::unescapeId(std::string & id)
{
  // We have to convert all %[0-9a-fA-F][0-9a-fA-F] character sequences to utf8 characters.
  std::string::size_type pos;

  for (pos = 0; pos < id.length(); pos++)
    if (id[pos] == '%' &&
        id.find_first_not_of("0123456789abcdefABCDEF", pos + 1) > pos + 2)
      {
        char ascii[2];
        ascii[0] = (unsigned char) strtol(id.substr(pos + 1, 2).c_str(), NULL, 16);
        ascii[1] = 0x0;
        id.replace(pos, 3, CCopasiXMLInterface::utf8(ascii));
      }
}

// static
std::string CMIRIAMResourceObject::trimId(const std::string & id)
{
  std::string Id = id;

  /* Trim leading and trailing whitespaces from the string */
  std::string::size_type begin = Id.find_first_not_of("\x20\x09\x0d\x0a");

  if (begin == std::string::npos)
    {
      Id = "";
    }
  else
    {
      std::string::size_type end = id.find_last_not_of("\x20\x09\x0d\x0a");

      if (end == std::string::npos)
        Id = id.substr(begin);
      else
        Id = id.substr(begin, end - begin + 1);
    }

  return Id;
}

CMIRIAMResourceObject::CMIRIAMResourceObject(CRDFNode * pNode):
  mId(),
  mpNode(pNode)
{
  if (mpNode != NULL)
    setURI(mpNode->getObject().getResource());
}

//static
void CMIRIAMResourceObject::setMIRIAMResources(const CMIRIAMResources * pResources)
{
  mpResources = pResources;
}

CMIRIAMResourceObject::CMIRIAMResourceObject(const std::string & displayName, const std::string & id):
  mResource(C_INVALID_INDEX),
  mId(),
  mpNode(NULL)
{
  setDisplayName(displayName);
  mId = id;
}

CMIRIAMResourceObject::CMIRIAMResourceObject(const CMIRIAMResourceObject & src):
  mResource(src.mResource),
  mId(src.mId),
  mpNode(NULL)
{}

bool CMIRIAMResourceObject::setId(const std::string & id)
{
  mId = trimId(id);

  // Empty IDs are not allowed.
  if (mId == "")
    return false;

  // Check whether the resource is known.
  if (mResource == C_INVALID_INDEX)
    return true;

  return isValid();
}

const std::string & CMIRIAMResourceObject::getId() const
{return mId;}

bool CMIRIAMResourceObject::setURI(const std::string & URI)
{
  mResource = getResource(URI);

  if (mResource == C_INVALID_INDEX &&
      !URI.empty())
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCAnnotation + 4, URI.c_str());
    }

  extractId(URI);

  return isValid();
}

std::string CMIRIAMResourceObject::getURI() const
{
  return (mpResources->getMIRIAMResource(mResource)).getMIRIAMURI() + ":" + mId;
}

std::string CMIRIAMResourceObject::getIdentifiersOrgURL() const
{

  std::string URL = mpResources->getMIRIAMResource(mResource).createIdentifiersOrgURL(mId);

  if (URL.find("http://identifiers.org/unknown") != std::string::npos)
    {
      return mId;
    }

  return URL;
}

bool CMIRIAMResourceObject::setNode(CRDFNode * pNode)
{
  mpNode = pNode;

  if (mpNode != NULL)
    return setURI(mpNode->getObject().getResource());

  return true;
}

CRDFNode * CMIRIAMResourceObject::getNode() const
{return mpNode;}

bool CMIRIAMResourceObject::setDisplayName(const std::string & displayName)
{
  mResource = mpResources->getResourceIndexFromDisplayName(displayName);

  if (mResource == C_INVALID_INDEX)
    return false;

  return true;
}

std::string CMIRIAMResourceObject::getDisplayName() const
{
  // Check whether the resource is known.
  if (mResource == C_INVALID_INDEX)
    return "";

  return (mpResources->getMIRIAMResource(mResource)).getMIRIAMDisplayName();
}

bool CMIRIAMResourceObject::isValid() const
{
  // Check whether the resource is known.
  if (mResource == C_INVALID_INDEX)
    return false;

  // Empty IDs are not allowed.
  if (mId == "")
    return false;

  // TODO Check whether the Id matches the regular expression.
  return true;
}

bool CMIRIAMResourceObject::isValid(const std::string & URI) const
{
  if (mpResources->getMIRIAMResourceIndex(URI) != mResource ||
      mResource == C_INVALID_INDEX)
    return false;

  return true;
}

void CMIRIAMResourceObject::extractId(const std::string & uri)
{
  mId = uri;

  // Check whether the resource is known.
  if (mpResources == NULL ||
      mResource == C_INVALID_INDEX)
    {
      return;
    }

  mId = mpResources->getMIRIAMResource(mResource).extractId(uri);

  unescapeId(mId);

  return;
}

CMIRIAMResourceObject::~CMIRIAMResourceObject()
{}
