// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/CopasiDataModel/CInfo.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/core/CDataTimer.h"
#include "copasi/utilities/CVersion.h"

CInfo::CInfo(const CDataModel * pParent)
  : CDataContainer("Information", pParent)
  , mpCopasiVersion(NULL)
  , mpGivenName(NULL)
  , mpFamilyName(NULL)
  , mpOrganization(NULL)
  , mpEmail(NULL)
  , mpFileName(NULL)
  , mpCurrentTime(NULL)
{
  update();
}

CInfo::~CInfo()
{}

void CInfo::update()
{
  if (mpCopasiVersion == NULL)
    {
      mpCopasiVersion =
        new CDataObjectReference< std::string >("COPASI Version", this,
            * const_cast< std::string * >(&CVersion::VERSION.getVersion()));
    }

  if (mpGivenName == NULL)
    {
      mpGivenName =
        new CDataObjectReference< std::string >("User Given Name", this,
            * const_cast< std::string * >(&CRootContainer::getConfiguration()->getCurrentAuthorGivenName()));
    }

  if (mpFamilyName == NULL)
    {
      mpFamilyName =
        new CDataObjectReference< std::string >("User Family Name", this,
            * const_cast< std::string * >(&CRootContainer::getConfiguration()->getCurrentAuthorFamilyName()));
    }

  if (mpOrganization == NULL)
    {
      mpOrganization =
        new CDataObjectReference< std::string >("User Organization", this,
            * const_cast< std::string * >(&CRootContainer::getConfiguration()->getCurrentAuthorOrganization()));
    }

  if (mpEmail == NULL)
    {
      mpEmail =
        new CDataObjectReference< std::string >("User Email", this,
            * const_cast< std::string * >(&CRootContainer::getConfiguration()->getCurrentAuthorEmail()));
    }

  if (mpCurrentTime == NULL)
    {
      mpCurrentTime = new CCopasiTimer(CCopasiTimer::Type::CURRENT, this);
    }

  if (mpFileName != NULL)
    {
      delete mpFileName;
      mpFileName = NULL;
    }

  CDataModel * pDataModel = dynamic_cast< CDataModel * >(getObjectParent());

  if (pDataModel != NULL)
    {
      mpFileName = new CDataObjectReference< std::string >("File Name", this,
          * const_cast< std::string * >(&pDataModel->getFileName()));
    }
}
