// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CMIRIAMResource.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/17 18:55:57 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMIRIAMResource.h"
#include "WebServicesIssues/soapH.h"
#include "WebServicesIssues/soapMiriamWebServicesSoapBindingProxy.h"
#include "WebServicesIssues/MiriamWebServicesSoapBinding.nsmap"
#include "MIRIAM/CConstants.h"

#include "utilities/CCopasiException.h"

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
                                     getActDateInSeconds())->getValue().pUINT;
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
  char *pURI, *pName, *pURL, *pURL2, *pIsDeprecated, *pPattern, *pRegExp;
  int itNames = 0, itURLs = 0, sizeNames = 0, sizeURLs = 0;
  unsigned C_INT32 processStep = 0, processSteps, hUpdateStep;
  struct ns2__getDataTypesNameResponse * pDataTypesName = new ns2__getDataTypesNameResponse();
  struct ns2__getDataTypeURLsResponse * pDataTypeURLs = NULL;

  if (pProxy->getDataTypesName(*pDataTypesName) == SOAP_OK)
    {
      sizeNames = pDataTypesName->getDataTypesNameReturn->__size;
      processSteps = sizeNames + 2;
      hUpdateStep = pProcessReport->addItem("Update Process",
                                            CCopasiParameter::UINT, &processStep, &processSteps);
      if (pProcessReport && !pProcessReport->progress(hUpdateStep)) return false;

      for (itNames = 0; itNames < sizeNames; itNames++)
        {
          pName = "", pURL = "";
          pDataTypeURLs = new ns2__getDataTypeURLsResponse();

          if (pDataTypesName->getDataTypesNameReturn->__ptr[itNames])
          {pName = pDataTypesName->getDataTypesNameReturn->__ptr[itNames];}
          pMIRIAMResource = new CMIRIAMResource(pName, NULL);

          if ((pProxy->getDataTypeURI(NULL, &*pName, *&pURI) == SOAP_OK)
              && (pProxy->getDataTypeURLs(&*pName, *pDataTypeURLs) == SOAP_OK)
              && (pProxy->getDataTypePattern(&*pName, *&pPattern) == SOAP_OK)
              && (pProxy->checkRegExp(&*pName, NULL, *&pRegExp) == SOAP_OK))
            {
              sizeURLs = pDataTypeURLs->_getDataTypeURLsReturn->__size;
              if (sizeURLs != 0)
                {
                  pURL = pDataTypeURLs->_getDataTypeURLsReturn->__ptr[0];
                  for (itURLs = 0; itURLs < sizeURLs; itURLs++)
                    {
                      pURL2 = pDataTypeURLs->_getDataTypeURLsReturn->__ptr[itURLs];

                      if (pProxy->isDeprecated(&*pURL2, *&pIsDeprecated) == SOAP_OK)
                        {
                          if (strcmp(pIsDeprecated, "true") == 0)
                          {pMIRIAMResource->addDeprecatedURL(pURL2);}
                        }
                      else
                      {success = false;}
                    }
                }

              pMIRIAMResource->setMIRIAMDisplayName(pName);
              pMIRIAMResource->setMIRIAMURL(pURL);
              pMIRIAMResource->setMIRIAMURI(pURI);
              pMIRIAMResource->setMIRIAMPattern(pPattern);
              pMIRIAMResource->setMIRIAMRegExp(strcmp(pRegExp, "true") == 0);
              pMIRIAMResource->setMIRIAMCitation(false);

              pTmpCpyCMIRIAMResources->addParameter(pMIRIAMResource);
            }
          else
          {success = false;}
          processStep++;
          if (pProcessReport && !pProcessReport->progress(hUpdateStep)) return false;
        }
      pdelete(pDataTypesName);
      processStep++;
      if (pProcessReport && !pProcessReport->progress(hUpdateStep)) return false;
    }
  else
  {success = false;}

  if (!success)
    {
      CCopasiMessage(CCopasiMessage::ERRoR,
                     "Connection to MIRIRAM Web Services failed.\n%s\n%s",
                     pProxy->soap_fault_string(),
                     pProxy->soap_fault_detail());
    }
  else
    {
      setMIRIAMLastUpdateDate();
      *mpMIRIAMResources = *pTmpCpyCMIRIAMResources;
      elevateChildren();
      createDisplayNameMap();
      createURIMap();
    }

  pdelete(pTmpCpyCMIRIAMResources);

  processStep++;
  if (pProcessReport && !pProcessReport->progress(hUpdateStep)) return false;
  if (pProcessReport) pProcessReport->finish(hUpdateStep);
  pProxy->~MiriamWebServicesSoapBindingProxy();

  return success;
}

void CMIRIAMResources::setMIRIAMLastUpdateDate()
{*mpLastUpdateDate = getActDateInSeconds();}

void CMIRIAMResources::setMIRIAMUpdateFrequency(const unsigned C_INT32 updateFrequency)
{*mpUpdateFrequency = updateFrequency * 24 * 60 * 60;}

unsigned C_INT32 CMIRIAMResources::getActDateInSeconds()
{return time(NULL);}

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

  unsigned C_INT32 Index = 0;

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

  unsigned C_INT32 Index = 0;
  CMIRIAMResource * pResource = NULL;

  CCopasiParameterGroup::index_iterator it = mpMIRIAMResources->beginIndex();
  CCopasiParameterGroup::index_iterator end = mpMIRIAMResources->endIndex();

  for (; it != end; ++it)
    {
      pResource = static_cast< CMIRIAMResource * >(*it);
      mURI2Resource[pResource->getMIRIAMURI()] = Index;

      const CCopasiParameterGroup * pDeprecated = &pResource->getMIRIAMDeprecated();
      CCopasiParameterGroup::index_iterator itDeprecated = pDeprecated->beginIndex();
      CCopasiParameterGroup::index_iterator endDeprecated = pDeprecated->endIndex();

      for (; itDeprecated != endDeprecated; ++itDeprecated)
      {mURI2Resource[*(*itDeprecated)->getValue().pSTRING] = Index;}

      Index++;
    }
}

const CMIRIAMResource & CMIRIAMResources::getMIRIAMResource(const unsigned C_INT32 index) const
  {
    assert(index < mpMIRIAMResources->size());
    return * static_cast< CMIRIAMResource * >(mpMIRIAMResources->getGroup(index));
  }

unsigned C_INT32 CMIRIAMResources::getMIRIAMResourceIndex(const std::string & URI) const
  {
    // Since the URI contains always an id this will always point past the actual element.
    std::map< std::string , unsigned C_INT32 >::const_iterator it = mURI2Resource.upper_bound(URI);

    // we have an unknown URI
    if (it == mURI2Resource.begin())
      return C_INVALID_INDEX;

    // it-- is defined for end as long as x exist with x++ = end, i.e., the map is not empty.
    it--;

    const CMIRIAMResource * pResource = &getMIRIAMResource(it->second);

    // Check whether the URI base of the candidate matches.
    if (URI.substr(0, pResource->getMIRIAMURI().length()) == pResource->getMIRIAMURI())
    {return it->second;}

    // We need to check for deprecated URIs
    const CCopasiParameterGroup * pDeprecated = &pResource->getMIRIAMDeprecated();
    CCopasiParameterGroup::index_iterator itDeprecated = pDeprecated->beginIndex();
    CCopasiParameterGroup::index_iterator endDeprecated = pDeprecated->endIndex();

    for (; itDeprecated != endDeprecated; ++itDeprecated)
      if (URI.substr(0, (*itDeprecated)->getValue().pSTRING->length()) == *(*itDeprecated)->getValue().pSTRING)
      {return it->second;}

    return C_INVALID_INDEX;
  }

unsigned C_INT32 CMIRIAMResources::getResourceIndexFromDisplayName(const std::string & displayName) const
  {
    // Check if the display name is a know resource
    std::map< std::string, unsigned C_INT32>::const_iterator it =
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
    unsigned C_INT32 Index = 0;

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
    mpURL(NULL),
    mpURI(NULL),
    mpRegExp(NULL),
    mpCitation(NULL),
    mpDeprecated(NULL)
{initializeParameter();}

CMIRIAMResource::CMIRIAMResource(const CMIRIAMResource & src,
                                 const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mpDisplayName(NULL),
    mpURL(NULL),
    mpURI(NULL),
    mpRegExp(NULL),
    mpCitation(NULL),
    mpDeprecated(NULL)
{initializeParameter();}

CMIRIAMResource::CMIRIAMResource(const CCopasiParameterGroup & group,
                                 const CCopasiContainer * pParent):
    CCopasiParameterGroup(group, pParent),
    mpDisplayName(NULL),
    mpURL(NULL),
    mpURI(NULL),
    mpRegExp(NULL),
    mpCitation(NULL),
    mpDeprecated(NULL)
{initializeParameter();}

void CMIRIAMResource::initializeParameter()
{
  mpDisplayName = assertParameter("DisplayName", CCopasiParameter::STRING,
                                  (std::string) "")->getValue().pSTRING;
  mpURL = assertParameter("URL", CCopasiParameter::STRING,
                          (std::string) "")->getValue().pSTRING;
  mpURI = assertParameter("URI", CCopasiParameter::STRING,
                          (std::string) "")->getValue().pSTRING;
  mpPattern = assertParameter("Pattern", CCopasiParameter::STRING,
                              (std::string) "")->getValue().pSTRING;
  mpRegExp = assertParameter("RegExp", CCopasiParameter::BOOL,
                             false)->getValue().pBOOL;
  mpCitation = assertParameter("Citation", CCopasiParameter::BOOL,
                               false)->getValue().pBOOL;
  mpDeprecated = assertGroup("Deprecated");
}

bool CMIRIAMResource::elevateChildren()
{
  bool success = true;

  mpDeprecated =
    elevate<CCopasiParameterGroup, CCopasiParameterGroup>(getGroup("Deprecated"));
  if (!mpDeprecated) success = false;

  return success;
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

void CMIRIAMResource::setMIRIAMURL(const std::string & URL)
{*mpURL = URL;}

const std::string & CMIRIAMResource::getMIRIAMURL() const
  {return * mpURL;}

void CMIRIAMResource::setMIRIAMURI(const std::string & URI)
{*mpURI = URI;}

const std::string & CMIRIAMResource::getMIRIAMURI() const
  {return * mpURI;}

void CMIRIAMResource::setMIRIAMPattern(const std::string & pattern)
{*mpPattern = pattern;}

const std::string & CMIRIAMResource::getMIRIAMPattern() const
  {return * mpPattern;}

void CMIRIAMResource::setMIRIAMRegExp(const bool & regExp)
{*mpRegExp = regExp;}

const bool & CMIRIAMResource::getMIRIAMRegExp() const
  {return * mpRegExp;}

void CMIRIAMResource::setMIRIAMCitation(const bool & citation)
{*mpCitation = citation;}

const bool & CMIRIAMResource::getMIRIAMCitation() const
  {return * mpCitation;}

void CMIRIAMResource::addDeprecatedURL(const std::string & URL)
{mpDeprecated->addParameter("URL", CCopasiParameter::STRING, URL);}

const CCopasiParameterGroup & CMIRIAMResource::getMIRIAMDeprecated() const
  {return * mpDeprecated;}
