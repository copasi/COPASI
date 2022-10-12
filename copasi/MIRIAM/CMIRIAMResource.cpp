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

// These are treated as external includes and must appear first

// #include "WebServicesIssues/soapH.h"
// #include "WebServicesIssues/soapMiriamWebServicesSoapBindingProxy.h"
// #include "WebServicesIssues/MiriamWebServicesSoapBinding.nsmap"

#include "copasi/copasi.h"

#include "CMIRIAMResource.h"
#include "CConstants.h"
#include "CRDFTriplet.h"
#include "CRDFNode.h"

#include "copasi/utilities/CCopasiException.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"

#include <sbml/xml/XMLNode.h>
#include <sbml/xml/XMLAttributes.h>
#include <sbml/xml/XMLToken.h>
#include <sbml/xml/XMLInputStream.h>

// static
void CMIRIAMResources::isCitation(void * pData, void * /* pCallee */)
{
  std::pair< const CRDFTriplet *, bool > & Data = * reinterpret_cast< std::pair< const CRDFTriplet *, bool > * >(pData);
  std::set< CRDFTriplet > Triplets;

  if (Data.first->pObject->isBagNode())
    {
      Triplets = Data.first->pObject->getDescendantsWithPredicate(CRDFPredicate::rdf_li);
    }
  else
    {
      Triplets.insert(*Data.first);
    }

  std::set< CRDFTriplet >::const_iterator it = Triplets.begin();
  std::set< CRDFTriplet >::const_iterator end = Triplets.end();

  for (Data.second = false; it != end && !Data.second; ++it)
    {
      Data.second = isCitation(it->pObject->getObject().getResource());
    }
}

// static
bool CMIRIAMResources::isCitation(const std::string & uri)
{
  size_t Index = CRootContainer::getConfiguration()->getRecentMIRIAMResources().getMIRIAMResourceIndex(uri);

  if (Index != C_INVALID_INDEX &&
      CRootContainer::getConfiguration()->getRecentMIRIAMResources().getMIRIAMResource(Index).getMIRIAMCitation())
    {
      return true;
    }

  return false;
}

CMIRIAMResources::CMIRIAMResources(const std::string & name,
                                   const CDataContainer * pParent) :
  CCopasiParameterGroup(name, pParent),
  mpLastUpdateDate(NULL),
  mpUpdateFrequency(NULL),
  mpMIRIAMResources(NULL)
{initializeParameter();}

CMIRIAMResources::CMIRIAMResources(const CMIRIAMResources & src,
                                   const CDataContainer * pParent):
  CCopasiParameterGroup(src, pParent),
  mpLastUpdateDate(NULL),
  mpUpdateFrequency(NULL),
  mpMIRIAMResources(NULL)
{initializeParameter();}

CMIRIAMResources::CMIRIAMResources(const CCopasiParameterGroup & group,
                                   const CDataContainer * pParent):
  CCopasiParameterGroup(group, pParent),
  mpLastUpdateDate(NULL),
  mpUpdateFrequency(NULL),
  mpMIRIAMResources(NULL)
{initializeParameter();}

void CMIRIAMResources::initializeParameter()
{
  mpLastUpdateDate = assertParameter("LastUpdateDate", CCopasiParameter::Type::UINT,
                                     (unsigned C_INT32) getActDateInSeconds());
  mpUpdateFrequency = assertParameter("Frequency", CCopasiParameter::Type::UINT,
                                      (unsigned C_INT32) 604800);
  mpMIRIAMResources = assertGroup("Resources");

  elevateChildren();

  createDisplayNameMap();
  createURIMap();
}

void CMIRIAMResources::addMIRIAMResource(CMIRIAMResource * mimriamResource)
{
  mpMIRIAMResources->addParameter(mimriamResource);
}

const CMIRIAMResources & CMIRIAMResources::getMIRIAMResources() const
{return * this;}

const CCopasiParameterGroup & CMIRIAMResources::getResourceList() const
{return * mpMIRIAMResources;}

const unsigned C_INT32 & CMIRIAMResources::getMIRIAMLastUpdateDate() const
{return * mpLastUpdateDate;}

const unsigned C_INT32 & CMIRIAMResources::getMIRIAMUpdateFrequency() const
{return * mpUpdateFrequency;}

bool CMIRIAMResources::updateMIRIAMResourcesFromFile(CProcessReport * pProcessReport,
    const std::string& filename)
{
  bool success = true;

  CCopasiParameterGroup * pTmpCpyCMIRIAMResources = new CCopasiParameterGroup("Resources");
  CMIRIAMResource * pMIRIAMResource = NULL;
  std::string Name, URI, Deprecated, Pattern, IsDeprecated;
  int itNames = 0, itURIs = 0, sizeNames = 0, sizeURIs = 0;
  unsigned C_INT32 processStep = 0, processSteps = 1;

  size_t hUpdateStep;

  if (pProcessReport != NULL)
    hUpdateStep = pProcessReport->addItem("Parsing MIRIAM XML", processStep, &processSteps);

  // parse file into memory
  XMLInputStream stream(filename.c_str());

  if (stream.isError()) return false;

  XMLNode root(stream);

  ++processStep;

  if (pProcessReport != NULL)
    {
      if (!pProcessReport->progressItem(hUpdateStep))
        return false;

      pProcessReport->finishItem(hUpdateStep);
    }

  sizeNames = root.getNumChildren();
  processSteps = sizeNames + 2;

  if (pProcessReport != NULL)
    hUpdateStep = pProcessReport->addItem("Add Items", processStep, &processSteps);

  if (pProcessReport != NULL && !pProcessReport->progressItem(hUpdateStep))
    return false;

  // read all datatype elements
  for (itNames = 0; itNames < sizeNames; itNames++)
    {
      XMLNode dataType = root.getChild(itNames);

      // only parse dataType elements
      if (dataType.getName() != "datatype") continue;

      // extract name
      Name = dataType.getChild("name").getChild(0).getCharacters();
      pMIRIAMResource = new CMIRIAMResource(Name, NULL);

      XMLNode uris = dataType.getChild("uris");
      sizeURIs = uris.getNumChildren();

      // extract uri & deprecated uris
      URI.clear();

      if (sizeURIs != 0)
        {
          for (itURIs = 0; itURIs < sizeURIs; itURIs++)
            {
              XMLNode uri = uris.getChild(itURIs);

              if (URI.empty())
                URI = uri.getChild(0).getCharacters();

              Deprecated = uri.getAttrValue("deprecated");

              if (Deprecated == "true")
                pMIRIAMResource->addDeprecatedURL(uri.getChild(0).getCharacters());
            }
        }

      // set name
      pMIRIAMResource->setMIRIAMDisplayName(Name);

      if (URI.empty() || Name.empty())
        {
          // ignore invalid item
          delete pMIRIAMResource;
          continue;
        }

      pMIRIAMResource->setMIRIAMURI(URI);
      pMIRIAMResource->setMIRIAMPattern(dataType.getAttrValue("pattern"));
      pMIRIAMResource->setMIRIAMCitation(URI == "urn:miriam:arxiv" ||
                                         URI == "urn:miriam:doi" ||
                                         URI == "urn:miriam:pubmed" ||
                                         URI == "urn:miriam:isbn");
      pMIRIAMResource->setMIRIAMNamespaceEmbeddedInPattern(dataType.getAttrValue("namespaceEmbeddedInPattern") == "True");

      pTmpCpyCMIRIAMResources->addParameter(pMIRIAMResource);

      processStep++;

      if (pProcessReport != NULL && !pProcessReport->progressItem(hUpdateStep))
        return false;
    }

  processStep++;

  if (pProcessReport != NULL && !pProcessReport->progressItem(hUpdateStep))
    return false;

  if (success)
    {
      // TODO add a resource for local objects, i.e., within the current model.

      setMIRIAMLastUpdateDate();
      *mpMIRIAMResources = *pTmpCpyCMIRIAMResources;
      elevateChildren();
      createDisplayNameMap();
      createURIMap();
    }

  pdelete(pTmpCpyCMIRIAMResources);

  processStep++;

  if (pProcessReport != NULL)
    {
      if (!pProcessReport->progressItem(hUpdateStep))
        return false;

      pProcessReport->finishItem(hUpdateStep);
    }

  return success;
}

void CMIRIAMResources::setMIRIAMLastUpdateDate()
{*mpLastUpdateDate = getActDateInSeconds();}

void CMIRIAMResources::setMIRIAMUpdateFrequencyInDays(const size_t & days)
{*mpUpdateFrequency = (unsigned C_INT32)(days * 24 * 60 * 60);}

unsigned C_INT32 CMIRIAMResources::getActDateInSeconds()
{return (unsigned C_INT32) time(NULL);}

bool CMIRIAMResources::elevateChildren()
{
  bool success = true;

  CCopasiParameterGroup::index_iterator it = mpMIRIAMResources->beginIndex();
  CCopasiParameterGroup::index_iterator end = mpMIRIAMResources->endIndex();

  for (; it != end; ++it)
    *it = elevate<CMIRIAMResource, CCopasiParameterGroup>(*it);

  return success;
}

const CMIRIAMResources & CMIRIAMResources::operator=(const CCopasiParameterGroup & rhs)
{
  if (static_cast< CCopasiParameterGroup * >(this) == &rhs) return * this;

  CCopasiParameterGroup::operator=(rhs);
  initializeParameter();

  return *this;
}

void CMIRIAMResources::createDisplayNameMap()
{
  mDisplayName2Resource.clear();

  size_t Index = 0;

  CCopasiParameterGroup::index_iterator it = mpMIRIAMResources->beginIndex();
  CCopasiParameterGroup::index_iterator end = mpMIRIAMResources->endIndex();

  for (; it != end; ++it)
    {
      mDisplayName2Resource[getMIRIAMResource(Index).getMIRIAMDisplayName()] = Index;
      Index++;
    }
}

void CMIRIAMResources::createURIMap()
{
  mURI2Resource.clear();

  size_t Index = 0;
  CMIRIAMResource * pResource = NULL;

  CCopasiParameterGroup::index_iterator it = mpMIRIAMResources->beginIndex();
  CCopasiParameterGroup::index_iterator end = mpMIRIAMResources->endIndex();

  for (; it != end; ++it)
    {
      pResource = static_cast< CMIRIAMResource * >(*it);
      mURI2Resource[pResource->getMIRIAMURI() + ":" ] = Index;
      mURI2Resource[pResource->getIdentifiersOrgURL(true) + ":" ] = Index;
      mURI2Resource[pResource->getIdentifiersOrgURL(false) + "/" ] = Index;

      const CCopasiParameterGroup * pDeprecated = &pResource->getMIRIAMDeprecated();
      CCopasiParameterGroup::index_iterator itDeprecated = pDeprecated->beginIndex();
      CCopasiParameterGroup::index_iterator endDeprecated = pDeprecated->endIndex();

      for (; itDeprecated != endDeprecated; ++itDeprecated)
        {
          std::string Deprecated = (*itDeprecated)->getValue< std::string >();

          //Deprecated URL style URIs do not use the ':' separator.
          if (Deprecated[Deprecated.length() - 1] != '/')
            {
              Deprecated += ":";
            }

          mURI2Resource[Deprecated] = Index;
        }

      Index++;
    }
}

const CMIRIAMResource & CMIRIAMResources::getMIRIAMResource(const size_t index) const
{
  if (index >= mpMIRIAMResources->size())
    return CRootContainer::getUnknownMiriamResource();

  return * static_cast< CMIRIAMResource * >(mpMIRIAMResources->getGroup(index));
}

size_t CMIRIAMResources::getMIRIAMResourceIndex(const std::string & uri) const
{
  size_t index = C_INVALID_INDEX;

  std::string URI;

  if (uri.length() > 8 && uri.substr(0, 8) == "https://")
    URI = "http://" + uri.substr(8);
  else
    URI = uri;

  std::pair< std::map< std::string, size_t >::const_iterator, std::map< std::string, size_t >::const_iterator > range = mURI2Resource.equal_range(URI);

  if (range.first == mURI2Resource.begin())
    return index;

  range.first--;

  for (; range.first != range.second; ++range.first)
    {
      // Check whether the URI base of the candidate matches.
      if (URI.compare(0, range.first->first.length(), range.first->first) == 0)
        {
          index =  range.first->second;
          break;
        }
    }

  return index;
}

size_t CMIRIAMResources::getResourceIndexFromDisplayName(const std::string & displayName) const
{
  // Check if the display name is a know resource
  std::map< std::string, size_t>::const_iterator it =
    mDisplayName2Resource.find(displayName.c_str());

  // If we did not find the resource we set it to unknown
  if (it == mDisplayName2Resource.end())
    {
      // unknown is indicated by an invalid index.
      return C_INVALID_INDEX;
    }

  return it->second;
}

/*void CMIRIAMResources::printResources(const std::string & sourceClass,
                                      const std::string & sourceFunction) const
  {
    size_t Index = 0;

    CCopasiParameterGroup::index_iterator it = mpMIRIAMResources->beginIndex();
    CCopasiParameterGroup::index_iterator end = mpMIRIAMResources->endIndex();

    printf("\nClass: %s\n", sourceClass.c_str());
    printf("Function: %s\n", sourceFunction.c_str());
    printf("MIRIAM RESOURCES:\n");
    for (; it != end; ++it)
      {
        printf("Index: %ld\n", Index);
        getMIRIAMResource(Index).printResource();
        Index++;
        printf("\n");
      }
  }*/

CMIRIAMResources::~CMIRIAMResources()
{}

/////////////////////////////////////////////////////////////////////////////////////
CMIRIAMResource::CMIRIAMResource(const std::string & name,
                                 const CDataContainer * pParent)
  : CCopasiParameterGroup(name, pParent)
  , mpDisplayName(NULL)
  , mpURI(NULL)
  , mpCitation(NULL)
  , mpDeprecated(NULL)
  , mpNamespaceEmbeddedInPattern(NULL)
{
  initializeParameter();
}

CMIRIAMResource::CMIRIAMResource(const CMIRIAMResource & src,
                                 const CDataContainer * pParent)
  : CCopasiParameterGroup(src, pParent)
  , mpDisplayName(NULL)
  , mpURI(NULL)
  , mpCitation(NULL)
  , mpDeprecated(NULL)
  , mpNamespaceEmbeddedInPattern(NULL)
{
  initializeParameter();
}

CMIRIAMResource::CMIRIAMResource(const CCopasiParameterGroup & group,
                                 const CDataContainer * pParent)
  : CCopasiParameterGroup(group, pParent)
  , mpDisplayName(NULL)
  , mpURI(NULL)
  , mpCitation(NULL)
  , mpDeprecated(NULL)
  , mpNamespaceEmbeddedInPattern(NULL)
{
  initializeParameter();
}

void CMIRIAMResource::initializeParameter()
{
  mpDisplayName = assertParameter("DisplayName", CCopasiParameter::Type::STRING, (std::string) "");
  mpURI = assertParameter("URI", CCopasiParameter::Type::STRING, (std::string) "");
  mpPattern = assertParameter("Pattern", CCopasiParameter::Type::STRING, (std::string) "");
  mpCitation = assertParameter("Citation", CCopasiParameter::Type::BOOL, false);
  mpNamespaceEmbeddedInPattern = assertParameter("NamespaceEmbeddedInPattern", CCopasiParameter::Type::BOOL, false);
  mpDeprecated = assertGroup("Deprecated");
}

CMIRIAMResource::~CMIRIAMResource()
{}
/*
void CMIRIAMResource::printResource() const
  {
    printf("Name: %s\t\n\tURL: %s\t\n\tURI: %s\n",
           (*mpDisplayName).c_str(),
           (*mpURL).c_str(),
           (*mpURI).c_str());
    printf("\tDeprecated URLs:\n");
    CCopasiParameterGroup::index_iterator it = (*mpDeprecated).beginIndex();
    CCopasiParameterGroup::index_iterator end = (*mpDeprecated).endIndex();
    for (; it != end; ++it)
      {printf("\t\tURL: %s\n", (*(*it)->getValue().pSTRING).c_str());}

    printf("\tPattern: %s\n", (*mpPattern).c_str());

    if (*mpRegExp)
      {printf("\tRegExp: true\n\n");}
    else
      {printf("\tRegExp: false\n\n");}
  }*/

const CMIRIAMResource & CMIRIAMResource::getMIRIAMMIRIAMResource() const
{
  return *this;
}

void CMIRIAMResource::setMIRIAMDisplayName(const std::string & displayName)
{
  *mpDisplayName = displayName;
}

const std::string & CMIRIAMResource::getMIRIAMDisplayName() const
{
  return *mpDisplayName;
}

void CMIRIAMResource::setMIRIAMURI(const std::string & URI)
{
  *mpURI = URI;
}

const std::string & CMIRIAMResource::getMIRIAMURI() const
{
  return *mpURI;
}

std::string CMIRIAMResource::getIdentifiersOrgURL(const bool & compact) const
{
  if (!compact
      || !*mpNamespaceEmbeddedInPattern)
    return "http://identifiers.org/" + mpURI->substr(11);

  return "http://identifiers.org/" + extractNamespaceFromPattern();
}

std::string CMIRIAMResource::extractNamespaceFromPattern() const
{
  if (*mpNamespaceEmbeddedInPattern)
    {
      std::string::size_type start = mpPattern->find('^') + 1;
      return mpPattern->substr(start, mpPattern->find(':', start) - start);
    }

  return "";
}

void CMIRIAMResource::setMIRIAMPattern(const std::string & pattern)
{
  *mpPattern = pattern;
}

const std::string & CMIRIAMResource::getMIRIAMPattern() const
{
  return *mpPattern;
}

void CMIRIAMResource::setMIRIAMCitation(const bool & citation)
{
  *mpCitation = citation;
}

const bool & CMIRIAMResource::getMIRIAMCitation() const
{
  return *mpCitation;
}

void CMIRIAMResource::setMIRIAMNamespaceEmbeddedInPattern(const bool & namespaceEmbeddedInPattern)
{
  *mpNamespaceEmbeddedInPattern = namespaceEmbeddedInPattern;
}

const bool & CMIRIAMResource::getMIRIAMNamespaceEmbeddedInPattern() const
{
  return *mpNamespaceEmbeddedInPattern;
}

void CMIRIAMResource::addDeprecatedURL(const std::string & URL)
{
  mpDeprecated->addParameter("URL", CCopasiParameter::Type::STRING, URL);
}

const CCopasiParameterGroup & CMIRIAMResource::getMIRIAMDeprecated() const
{
  return *mpDeprecated;
}

std::string CMIRIAMResource::extractId(const std::string & uri) const
{
  std::string Id;
  std::string URI;

  if (uri.length() > 8 && uri.substr(0, 8) == "https://")
    URI = "http://" + uri.substr(8);
  else
    URI = uri;

  int offset;
  const std::string & Tmp = getMIRIAMURI();

  if (URI.substr(0, Tmp.length()) == Tmp &&
      URI.length() > Tmp.length())
    {
      offset = (Tmp.at(Tmp.length() - 1) == '/') ? 0 : 1;
      Id = URI.substr(Tmp.length() + offset);
    }

  if (Id == ""
      && *mpNamespaceEmbeddedInPattern)
    {
      std::string Tmp = getIdentifiersOrgURL(true);

      if (URI.substr(0, Tmp.length()) == Tmp &&
          URI.length() > Tmp.length())
        {
          offset = (Tmp[Tmp.length() - 1] == '/') ? 0 : 1;
          Id = extractNamespaceFromPattern() + ":" + URI.substr(Tmp.length() + offset);
        }
    }

  if (Id == "")
    {
      std::string Tmp = getIdentifiersOrgURL(false);

      if (URI.substr(0, Tmp.length()) == Tmp &&
          URI.length() > Tmp.length())
        {
          offset = (Tmp[Tmp.length() - 1] == '/') ? 0 : 1;
          Id = URI.substr(Tmp.length() + offset);
        }
    }

  if (Id == "")
    {
      // We need to check for deprecated URIs
      const CCopasiParameterGroup * pDeprecated = &getMIRIAMDeprecated();
      CCopasiParameterGroup::index_iterator itDeprecated = pDeprecated->beginIndex();
      CCopasiParameterGroup::index_iterator endDeprecated = pDeprecated->endIndex();

      for (; itDeprecated != endDeprecated; ++itDeprecated)
        {
          const std::string & Tmp = (*itDeprecated)->getValue< std::string >();

          if (URI.substr(0, Tmp.length()) == Tmp &&
              URI.length() > Tmp.length())
            {
              offset = (Tmp[Tmp.length() - 1] == '/') ? 0 : 1;
              Id = URI.substr(Tmp.length() + offset);
              break;
            }
        }
    }

  return Id;
}

std::string CMIRIAMResource::createIdentifiersOrgURL(const std::string id) const
{
  if (*mpNamespaceEmbeddedInPattern)
    return "http://identifiers.org/" + id;

  return getIdentifiersOrgURL(false) + "/" + id;
}
