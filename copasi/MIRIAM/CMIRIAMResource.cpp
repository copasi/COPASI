// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// These are treated as external includes and must appear first
#include "WebServicesIssues/soapH.h"
#include "WebServicesIssues/soapMiriamWebServicesSoapBindingProxy.h"
#include "WebServicesIssues/MiriamWebServicesSoapBinding.nsmap"

#include "copasi.h"

#include "CMIRIAMResource.h"
#include "CConstants.h"

#include "utilities/CCopasiException.h"
#include "report/CCopasiRootContainer.h"

CMIRIAMResources::CMIRIAMResources(const std::string & name,
                                   const CCopasiContainer * pParent) :
  CCopasiParameterGroup(name, pParent),
  mpLastUpdateDate(NULL),
  mpUpdateFrequency(NULL),
  mpMIRIAMResources(NULL)
{initializeParameter();}

CMIRIAMResources::CMIRIAMResources(const CMIRIAMResources & src,
                                   const CCopasiContainer * pParent):
  CCopasiParameterGroup(src, pParent),
  mpLastUpdateDate(NULL),
  mpUpdateFrequency(NULL),
  mpMIRIAMResources(NULL)
{initializeParameter();}

CMIRIAMResources::CMIRIAMResources(const CCopasiParameterGroup & group,
                                   const CCopasiContainer * pParent):
  CCopasiParameterGroup(group, pParent),
  mpLastUpdateDate(NULL),
  mpUpdateFrequency(NULL),
  mpMIRIAMResources(NULL)
{initializeParameter();}

void CMIRIAMResources::initializeParameter()
{
  mpLastUpdateDate = assertParameter("LastUpdateDate", CCopasiParameter::UINT,
                                     (unsigned C_INT32) getActDateInSeconds())->getValue().pUINT;
  mpUpdateFrequency = assertParameter("Frequency", CCopasiParameter::UINT,
                                      (unsigned C_INT32) 604800)->getValue().pUINT;
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

bool CMIRIAMResources::updateMIRIAMResources(CProcessReport * pProcessReport)
{
  if (pProcessReport)
    pProcessReport->setName("MIRIAM Resources Update...");

  bool success = true;
  MiriamWebServicesSoapBindingProxy * pProxy = new MiriamWebServicesSoapBindingProxy();

  CCopasiParameterGroup * pTmpCpyCMIRIAMResources = new CCopasiParameterGroup("Resources");

  CMIRIAMResource * pMIRIAMResource = NULL;
  std::string Name, URI, Deprecated, Pattern, IsDeprecated;
  int itNames = 0, itURIs = 0, sizeNames = 0, sizeURIs = 0;
  unsigned C_INT32 processStep = 0, processSteps;
  size_t hUpdateStep;
  struct ns2__getDataTypesNameResponse DataTypesName;

  if (pProxy->getDataTypesName(DataTypesName) == SOAP_OK)
    {
      sizeNames = DataTypesName.getDataTypesNameReturn->__size;
      processSteps = sizeNames + 2;
      hUpdateStep = pProcessReport->addItem("Update Process", processStep, &processSteps);

      if (pProcessReport && !pProcessReport->progressItem(hUpdateStep))
        return false;

      for (itNames = 0; itNames < sizeNames; itNames++)
        {
          struct ns2__getDataTypeURIsResponse DataTypeURIs;

          if (DataTypesName.getDataTypesNameReturn->__ptr[itNames] != "")
            Name = DataTypesName.getDataTypesNameReturn->__ptr[itNames];

          pMIRIAMResource = new CMIRIAMResource(Name, NULL);

          if ((pProxy->getDataTypeURI(Name, URI) == SOAP_OK)
              && (pProxy->getDataTypeURIs(Name, DataTypeURIs) == SOAP_OK)
              && (pProxy->getDataTypePattern(Name, Pattern) == SOAP_OK))
            {
              sizeURIs = DataTypeURIs._getDataTypeURIsReturn->__size;

              if (sizeURIs != 0)
                {
                  for (itURIs = 0; itURIs < sizeURIs; itURIs++)
                    {
                      Deprecated = DataTypeURIs._getDataTypeURIsReturn->__ptr[itURIs];

                      if (Deprecated != URI)
                        pMIRIAMResource->addDeprecatedURL(Deprecated);
                    }
                }

              pMIRIAMResource->setMIRIAMDisplayName(Name);
              pMIRIAMResource->setMIRIAMURI(URI);
              pMIRIAMResource->setMIRIAMPattern(Pattern);
              pMIRIAMResource->setMIRIAMCitation(URI == "urn:miriam:arxiv" ||
                                                 URI == "urn:miriam:doi" ||
                                                 URI == "urn:miriam:pubmed" ||
                                                 URI == "urn:miriam:isbn");

              pTmpCpyCMIRIAMResources->addParameter(pMIRIAMResource);
            }
          else
            success = false;

          processStep++;

          if (pProcessReport && !pProcessReport->progressItem(hUpdateStep))
            return false;
        }

      processStep++;

      if (pProcessReport && !pProcessReport->progressItem(hUpdateStep))
        return false;
    }
  else
    success = false;

  if (success)
    {
      // TODO add a resource for local objects, i.e., within the current model.

      setMIRIAMLastUpdateDate();
      *mpMIRIAMResources = *pTmpCpyCMIRIAMResources;
      elevateChildren();
      createDisplayNameMap();
      createURIMap();
    }
  else
    CCopasiMessage(CCopasiMessage::ERROR,
                   MCAnnotation + 3,
                   pProxy->soap_fault_string(),
                   pProxy->soap_fault_detail());

  pdelete(pTmpCpyCMIRIAMResources);

  processStep++;

  if (pProcessReport && !pProcessReport->progressItem(hUpdateStep)) return false;

  if (pProcessReport) pProcessReport->finishItem(hUpdateStep);

  pdelete(pProxy);

  return success;
}

void CMIRIAMResources::setMIRIAMLastUpdateDate()
{*mpLastUpdateDate = getActDateInSeconds();}

void CMIRIAMResources::setMIRIAMUpdateFrequencyInDays(const size_t & days)
{*mpUpdateFrequency = (unsigned C_INT32)(days * 24 * 60 * 60);}

unsigned C_INT32 CMIRIAMResources::getActDateInSeconds()
{return (unsigned C_INT32) time(NULL);}

bool CMIRIAMResources::autoUpdateMIRIAMResources(CProcessReport * pProcessReport)
{
  if ((*mpLastUpdateDate + *mpUpdateFrequency) <= getActDateInSeconds())
    {return updateMIRIAMResources(pProcessReport);}

  return false;
}

bool CMIRIAMResources::elevateChildren()
{
  bool success = true;

  CCopasiParameterGroup::index_iterator it = mpMIRIAMResources->beginIndex();
  CCopasiParameterGroup::index_iterator end = mpMIRIAMResources->endIndex();

  for (; it != end; ++it)
    *it = elevate<CMIRIAMResource, CCopasiParameterGroup>(*it);

  return success;
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
      mURI2Resource[pResource->getMIRIAMURI() + ":"] = Index;
      mURI2Resource[pResource->getIdentifiersOrgURL() + "/"] = Index;

      const CCopasiParameterGroup * pDeprecated = &pResource->getMIRIAMDeprecated();
      CCopasiParameterGroup::index_iterator itDeprecated = pDeprecated->beginIndex();
      CCopasiParameterGroup::index_iterator endDeprecated = pDeprecated->endIndex();

      for (; itDeprecated != endDeprecated; ++itDeprecated)
        {
          std::string Deprecated = *(*itDeprecated)->getValue().pSTRING;

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
    return CCopasiRootContainer::getUnknownMiriamResource();

  return * static_cast< CMIRIAMResource * >(mpMIRIAMResources->getGroup(index));
}

size_t CMIRIAMResources::getMIRIAMResourceIndex(const std::string & URI) const
{
  size_t index = C_INVALID_INDEX;

  std::map< std::string , size_t >::const_iterator it = mURI2Resource.lower_bound(URI);
  std::map< std::string , size_t >::const_iterator end = mURI2Resource.upper_bound(URI);

  if (it == mURI2Resource.begin())
    return index;

  it--;

  for (; it != end; ++it)
    {
      // Check whether the URI base of the candidate matches.
      if (URI.compare(0, it->first.length(), it->first) == 0)
        {
          index =  it->second;
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
                                 const CCopasiContainer * pParent) :
  CCopasiParameterGroup(name, pParent),
  mpDisplayName(NULL),
  mpURI(NULL),
  mpCitation(NULL),
  mpDeprecated(NULL)
{initializeParameter();}

CMIRIAMResource::CMIRIAMResource(const CMIRIAMResource & src,
                                 const CCopasiContainer * pParent):
  CCopasiParameterGroup(src, pParent),
  mpDisplayName(NULL),
  mpURI(NULL),
  mpCitation(NULL),
  mpDeprecated(NULL)
{initializeParameter();}

CMIRIAMResource::CMIRIAMResource(const CCopasiParameterGroup & group,
                                 const CCopasiContainer * pParent):
  CCopasiParameterGroup(group, pParent),
  mpDisplayName(NULL),
  mpURI(NULL),
  mpCitation(NULL),
  mpDeprecated(NULL)
{initializeParameter();}

void CMIRIAMResource::initializeParameter()
{
  mpDisplayName = assertParameter("DisplayName", CCopasiParameter::STRING,
                                  (std::string) "")->getValue().pSTRING;
  mpURI = assertParameter("URI", CCopasiParameter::STRING,
                          (std::string) "")->getValue().pSTRING;
  mpPattern = assertParameter("Pattern", CCopasiParameter::STRING,
                              (std::string) "")->getValue().pSTRING;
  mpCitation = assertParameter("Citation", CCopasiParameter::BOOL,
                               false)->getValue().pBOOL;
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
{return * this;}

void CMIRIAMResource::setMIRIAMDisplayName(const std::string & displayName)
{*mpDisplayName = displayName;}

const std::string & CMIRIAMResource::getMIRIAMDisplayName() const
{return *mpDisplayName;}

void CMIRIAMResource::setMIRIAMURI(const std::string & URI)
{*mpURI = URI;}

const std::string & CMIRIAMResource::getMIRIAMURI() const
{return * mpURI;}

std::string CMIRIAMResource::getIdentifiersOrgURL() const
{
  return "http://identifiers.org/" + mpURI->substr(11);
}

void CMIRIAMResource::setMIRIAMPattern(const std::string & pattern)
{*mpPattern = pattern;}

const std::string & CMIRIAMResource::getMIRIAMPattern() const
{return * mpPattern;}

void CMIRIAMResource::setMIRIAMCitation(const bool & citation)
{*mpCitation = citation;}

const bool & CMIRIAMResource::getMIRIAMCitation() const
{return * mpCitation;}

void CMIRIAMResource::addDeprecatedURL(const std::string & URL)
{mpDeprecated->addParameter("URL", CCopasiParameter::STRING, URL);}

const CCopasiParameterGroup & CMIRIAMResource::getMIRIAMDeprecated() const
{return * mpDeprecated;}
