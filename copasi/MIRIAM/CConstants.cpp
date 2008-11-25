// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CConstants.cpp,v $
//   $Revision: 1.10.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/25 16:49:07 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CConstants.h"
#include "CRDFGraph.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "commandline/CConfigurationFile.h"

//static
const CMIRIAMResources * CMIRIAMResourceObject::mpResources = NULL;

unsigned C_INT32 CMIRIAMResourceObject::getResource(const std::string & URI)
{return mpResources->getMIRIAMResourceIndex(URI);}

//static
const CMIRIAMResources & CMIRIAMResourceObject::getResourceList()
{return *mpResources;}

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
    mId(src.mId)
{}

bool CMIRIAMResourceObject::setId(const std::string & id)
{
  mId = id;

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
  extractId(URI);

  return isValid();
}

std::string CMIRIAMResourceObject::getURI() const
  {
    return (mpResources->getMIRIAMResource(mResource)).getMIRIAMURI() + ":" + mId;
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

void CMIRIAMResourceObject::extractId(const std::string & URI)
{
  mId = "";

  // Check whether the resource is known.
  if (mpResources == NULL ||
      mResource == C_INVALID_INDEX)
    return;

  const std::string & tmp = (mpResources->getMIRIAMResource(mResource)).getMIRIAMURI();
  if (URI.substr(0, tmp.length()) == tmp &&
      URI.length() > tmp.length())
    mId = URI.substr(tmp.length() + 1);

  if (mId != "")
    return;

  // We need to check for deprecated URIs
  const CCopasiParameterGroup * pDeprecated = &(mpResources->getMIRIAMResource(mResource)).getMIRIAMDeprecated();
  CCopasiParameterGroup::index_iterator itDeprecated = pDeprecated->beginIndex();
  CCopasiParameterGroup::index_iterator endDeprecated = pDeprecated->endIndex();

  for (; itDeprecated != endDeprecated; ++itDeprecated)
    if (URI.substr(0, (*itDeprecated)->getValue().pSTRING->length()) == *(*itDeprecated)->getValue().pSTRING &&
        URI.length() > (*itDeprecated)->getValue().pSTRING->length())
      {
        mId = URI.substr((*itDeprecated)->getValue().pSTRING->length() + 1);
        break;
      }
  return;
}

CMIRIAMResourceObject::~CMIRIAMResourceObject()
{}
