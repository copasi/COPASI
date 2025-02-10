// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"

#include "CConfigurationFile.h"
#include "COptions.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CVersion.h"
#include "copasi/utilities/utility.h"
#include "copasi/utilities/CDirEntry.h"

#include "copasi/xml/parser/CXMLParser.h"
#include "copasi/xml/CGroupXML.h"

CRecentFiles::CRecentFiles(const std::string & name,
                           const CDataContainer * pParent):
  CCopasiParameterGroup(name, pParent),
  mpMaxFiles(NULL),
  mpRecentFiles(NULL)
{initializeParameter();}

CRecentFiles::CRecentFiles(const CRecentFiles & src,
                           const CDataContainer * pParent):
  CCopasiParameterGroup(src, pParent),
  mpMaxFiles(NULL),
  mpRecentFiles(NULL)
{initializeParameter();}

CRecentFiles::CRecentFiles(const CCopasiParameterGroup & group,
                           const CDataContainer * pParent):
  CCopasiParameterGroup(group, pParent),
  mpMaxFiles(NULL),
  mpRecentFiles(NULL)
{initializeParameter();}

CRecentFiles::~CRecentFiles()
{}

void CRecentFiles::initializeParameter()
{
  mpMaxFiles =
    assertParameter("MaxFiles", CCopasiParameter::Type::UINT, (unsigned C_INT32) 5);
  mpRecentFiles = assertGroup("Recent Files");
  mpRecentFiles->setUserInterfaceFlag(mpRecentFiles->getUserInterfaceFlag() & ~CCopasiParameter::UserInterfaceFlag(CCopasiParameter::eUserInterfaceFlag::basic));
}

void CRecentFiles::addFile(const std::string & file)
{
  std::string FileName = CDirEntry::normalize(file);

#ifdef WIN32
  std::string::size_type pos = FileName.find('\\');

  while (pos != std::string::npos)
    {
      FileName[pos] = '/';
      pos = FileName.find('\\', pos);
    }

#endif

  std::string PWD;
  COptions::getValue("PWD", PWD);

  if (CDirEntry::isRelativePath(FileName) &&
      !CDirEntry::makePathAbsolute(FileName, PWD))
    FileName = CDirEntry::fileName(FileName);

  CCopasiParameterGroup::index_iterator it = mpRecentFiles->beginIndex();
  CCopasiParameterGroup::index_iterator end = mpRecentFiles->endIndex();

  std::string NewFile = FileName;
  std::string ExistingFile;

  for (; it != end; ++it)
    {
      ExistingFile = (*it)->getValue< std::string >();
      (*it)->setValue(NewFile);

      if (ExistingFile == FileName) return;

      NewFile = ExistingFile;
    }

  if (mpRecentFiles->size() < *mpMaxFiles)
    mpRecentFiles->addParameter("File", CCopasiParameter::Type::STRING, NewFile);

  return;
}

CConfigurationFile::CConfigurationFile(const std::string & name,
                                       const CDataContainer * pParent)
  : CCopasiParameterGroup(name, pParent)
  , mpRecentFiles(NULL)
  , mpRecentSBMLFiles(NULL)
  , mpRecentSEDMLFiles(NULL)
  , mpApplicationFont(NULL)
  , mpValidateUnits(NULL)
  , mpDisplayIssueSeverity(NULL)
  , mpDisplayIssueKinds(NULL)
  , mpUseOpenGL(NULL)
  , mpUseAdvancedSliders(NULL)
  , mpUseAdvancedEditing(NULL)
  , mpNormalizePerExperiment(NULL)
  , mpEnableAdditionalOptimizationParameters(NULL)
  , mpDisplayPopulations(NULL)
  , mpWorkingDirectory(NULL)
  , mpProxyServer(NULL)
  , mpProxyPort(NULL)
  , mpProxyUser(NULL)
  , mpProxyPass(NULL)
  , mpCurrentAuthorGivenName(NULL)
  , mpCurrentAuthorFamilyName(NULL)
  , mpCurrentAuthorOrganization(NULL)
  , mpCurrentAuthorEmail(NULL)
  , mpPrecision(NULL)
  , mpCheckForUpdates(NULL)
  , mpResizeToContents(NULL)
  , mpDisableJIT(NULL)
{
  initializeParameter();
}

CConfigurationFile::CConfigurationFile(const CConfigurationFile & src,
                                       const CDataContainer * pParent)
  : CCopasiParameterGroup(src, pParent)
  , mpRecentFiles(NULL)
  , mpRecentSBMLFiles(NULL)
  , mpRecentSEDMLFiles(NULL)
  , mpApplicationFont(NULL)
  , mpValidateUnits(NULL)
  , mpDisplayIssueSeverity(NULL)
  , mpDisplayIssueKinds(NULL)
  , mpUseOpenGL(NULL)
  , mpUseAdvancedSliders(NULL)
  , mpUseAdvancedEditing(NULL)
  , mpNormalizePerExperiment(NULL)
  , mpEnableAdditionalOptimizationParameters(NULL)
  , mpDisplayPopulations(NULL)
  , mpWorkingDirectory(NULL)
  , mpProxyServer(NULL)
  , mpProxyPort(NULL)
  , mpProxyUser(NULL)
  , mpProxyPass(NULL)
  , mpCurrentAuthorGivenName(NULL)
  , mpCurrentAuthorFamilyName(NULL)
  , mpCurrentAuthorOrganization(NULL)
  , mpCurrentAuthorEmail(NULL)
  , mpPrecision(NULL)
  , mpCheckForUpdates(NULL)
  , mpResizeToContents(NULL)
  , mpDisableJIT(NULL)
{
  initializeParameter();
}

CConfigurationFile::~CConfigurationFile()
{}

bool CConfigurationFile::elevateChildren()
{
  bool success = true;

  mpRecentFiles =
    elevate<CRecentFiles, CCopasiParameterGroup>(getGroup("Recent Files"));

  if (!mpRecentFiles) success = false;

  mpRecentSBMLFiles =
    elevate<CRecentFiles, CCopasiParameterGroup>(getGroup("Recent SBML Files"));

  if (!mpRecentSBMLFiles) success = false;

  mpRecentSEDMLFiles =
    elevate<CRecentFiles, CCopasiParameterGroup>(getGroup("Recent SEDML Files"));

  if (!mpRecentSEDMLFiles) success = false;

  mpCheckForUpdates =
    elevate<CCheckForUpdates, CCopasiParameterGroup>(getGroup("Check for Updates"));

  if (!mpCheckForUpdates) success = false;

  // We need to make sure that the contained group "MIRIAM Resources" is converted to CRootContainer::getMiriamResources()
  CCopasiParameterGroup *pMIRIAMResources = getGroup("MIRIAM Resources");

  if (CRootContainer::getMiriamResources().getResourceList().size() == 0
      && pMIRIAMResources != nullptr)
    {
      CRootContainer::getMiriamResources() = *pMIRIAMResources;
      removeParameter(pMIRIAMResources);
    }

  return success;
}

void CConfigurationFile::initializeParameter()
{
  assertGroup("Recent Files");
  assertGroup("Recent SBML Files");
  assertGroup("Recent SEDML Files");
  mpUseOpenGL = assertParameter("Use OpenGL", CCopasiParameter::Type::BOOL, false);
  mpUseAdvancedSliders = assertParameter("Use Advanced Sliders", CCopasiParameter::Type::BOOL, true);
  mpUseAdvancedEditing = assertParameter("Use Advanced Editing", CCopasiParameter::Type::BOOL, false);
  mpNormalizePerExperiment = assertParameter("Normalize Weights per Experiment", CCopasiParameter::Type::BOOL, true);
  mpEnableAdditionalOptimizationParameters = assertParameter("Enable additional optimization parameters", CCopasiParameter::Type::BOOL, false);
  mpDisplayPopulations = assertParameter("Display Populations during Optimization", CCopasiParameter::Type::BOOL, false);
  mpResizeToContents = assertParameter("Resize Tables to Content", CCopasiParameter::Type::BOOL, true);
  mpPrecision = assertParameter("Double Precision for String Conversion", CCopasiParameter::Type::INT, 10);

  mpApplicationFont = assertParameter("Application Font", CCopasiParameter::Type::STRING, std::string(""));

  CCopasiParameter* pParm = getParameter("Application Font");
  pParm->setUserInterfaceFlag(pParm->getUserInterfaceFlag() & ~CCopasiParameter::UserInterfaceFlag(CCopasiParameter::eUserInterfaceFlag::editable));

  mpDisplayIssueSeverity = assertGroup("Display Issue Severity");
  mpDisplayIssueKinds = assertGroup("Display Issue Kinds");
  mpValidateUnits = assertParameter("Validate Units", CCopasiParameter::Type::BOOL, false);

  // Remove display issue kinds which can no longer be mapped;
  CCopasiParameterGroup::elements::const_iterator itKind = mpDisplayIssueKinds->beginIndex();
  CCopasiParameterGroup::elements::const_iterator endKind = mpDisplayIssueKinds->endIndex();
  std::vector< CCopasiParameter * > ToBeRemoved;

  for (; itKind != endKind; ++itKind)
    if (CIssue::kindNames.toEnum((*itKind)->getObjectName(), CIssue::eKind::__SIZE) == CIssue::eKind::__SIZE)
      {
        ToBeRemoved.push_back(*itKind);
      }

  std::vector< CCopasiParameter * >::const_iterator itToBeRemoved = ToBeRemoved.begin();
  std::vector< CCopasiParameter * >::const_iterator endToBeRemoved = ToBeRemoved.end();

  for (; itToBeRemoved != endToBeRemoved; ++itToBeRemoved)
    {
      mpDisplayIssueKinds->removeParameter(*itToBeRemoved);
    }

  for (size_t i = 1; i < CIssue::severityNames.size(); i++) //skip the "success" flag
    {
      mpDisplayIssueSeverity->assertParameter(std::string(CIssue::severityNames[i]), CCopasiParameter::Type::BOOL, true);
    }

  for (size_t i = 0; i < CIssue::kindNames.size(); i++)
    {
      mpDisplayIssueKinds->assertParameter(std::string(CIssue::kindNames[i]), CCopasiParameter::Type::BOOL, true);
    }

  mpWorkingDirectory = assertParameter("Working Directory", CCopasiParameter::Type::STRING, std::string(""));
  pParm = getParameter("Working Directory");
  pParm->setUserInterfaceFlag(pParm->getUserInterfaceFlag() & ~CCopasiParameter::UserInterfaceFlag(CCopasiParameter::eUserInterfaceFlag::editable));

  mpProxyServer = assertParameter("Proxy Server", CCopasiParameter::Type::STRING, std::string(""));
  mpProxyPort = assertParameter("Proxy Port", CCopasiParameter::Type::INT, 0);
  mpProxyUser = assertParameter("Proxy User", CCopasiParameter::Type::STRING, std::string(""));
  mpProxyPass = assertParameter("Proxy Password", CCopasiParameter::Type::STRING, std::string(""));

  mpCurrentAuthorGivenName = assertParameter("Given Name", CCopasiParameter::Type::STRING, std::string("Anonymous"));
  mpCurrentAuthorFamilyName = assertParameter("Family Name", CCopasiParameter::Type::STRING, std::string("Anonymous"));

  if (getParameter("Famliy Name") != NULL)
    {
      CCopasiParameter *pParameter = getParameter("Famliy Name");

      if (*mpCurrentAuthorFamilyName == "Anonymous")
        *mpCurrentAuthorFamilyName = pParameter->getValue< std::string >();

      delete pParameter;
    }

  mpCurrentAuthorOrganization = assertParameter("Organization", CCopasiParameter::Type::STRING, std::string(""));
  mpCurrentAuthorEmail = assertParameter("Email", CCopasiParameter::Type::STRING, std::string("An.other@mailinator.com"));

  assertGroup("Check for Updates");

  mpDisableJIT = assertParameter("Disable JIT Compilation", CCopasiParameter::Type::BOOL, false);

  elevateChildren();
}

bool CConfigurationFile::save(bool saveMiriam)
{
  std::string ConfigFile;
  COptions::getValue("ConfigFile", ConfigFile);

  std::string miriamConfigFile = ConfigFile + std::string(".miriam");
  saveMiriam |= (!CDirEntry::exist(miriamConfigFile)
                 && CRootContainer::getMiriamResources().getResourceList().size() > 0);

  if (saveMiriam)
    {
      CGroupXML(CRootContainer::getMiriamResources()).CCopasiXMLInterface::save(miriamConfigFile, CDirEntry::dirName(ConfigFile));
    }

  bool success = CGroupXML(*this).CCopasiXMLInterface::save(ConfigFile, CDirEntry::dirName(ConfigFile));

  return success;
}

bool CConfigurationFile::load()
{
  std::string ConfigFile;
  COptions::getValue("ConfigFile", ConfigFile);

  CCopasiParameterGroup Configuration("Configuration");
  bool success = CGroupXML(Configuration).CCopasiXMLInterface::load(ConfigFile, ConfigFile);

  if (success)
    *this = Configuration;

  std::string configMIRIAMResourceFile(ConfigFile + std::string(".miriam"));
  bool haveConfigMiriam = CDirEntry::exist(configMIRIAMResourceFile);

  if (haveConfigMiriam)
    {
      CCopasiParameterGroup MIRIAMResources("MIRIAM Resources");

      if (CGroupXML(MIRIAMResources).CCopasiXMLInterface::load(configMIRIAMResourceFile, configMIRIAMResourceFile))
        CRootContainer::getMiriamResources() = MIRIAMResources;
      else
        return false;
    }

  if (CRootContainer::getMiriamResources().getResourceList().size() == 0)
    {
      // We load the default MIRIAM resources, which are part of the COPASI installation.
      std::string MIRIAMResourceFile;
      COptions::getValue("DefaultConfigDir", MIRIAMResourceFile);
      MIRIAMResourceFile += CDirEntry::Separator + "MIRIAMResources.xml";

      CCopasiParameterGroup Configuration("Configuration");

      if (CGroupXML(Configuration).CCopasiXMLInterface::load(MIRIAMResourceFile,
                                                             MIRIAMResourceFile))
        {
          const CCopasiParameterGroup *pGroup = Configuration.getGroup("MIRIAM Resources");

          if (pGroup == nullptr)
            return false;

          CRootContainer::getMiriamResources() = *pGroup;

          if (!haveConfigMiriam)
            {
              CGroupXML(CRootContainer::getMiriamResources()).CCopasiXMLInterface::save(configMIRIAMResourceFile, configMIRIAMResourceFile);
            }
        }
      else
        success = false;
    }

  return success;
}

const CConfigurationFile & CConfigurationFile::operator=(const CCopasiParameterGroup & rhs)
{
  if (static_cast< CCopasiParameterGroup * >(this) == &rhs) return * this;

  CCopasiParameterGroup::operator=(rhs);
  initializeParameter();

  return *this;
}

const CConfigurationFile & CConfigurationFile::operator=(const CConfigurationFile & rhs)
{
  return CConfigurationFile::operator=(static_cast<const CCopasiParameterGroup&>(rhs));
}

CRecentFiles & CConfigurationFile::getRecentFiles()
{
  return *mpRecentFiles;
}

CRecentFiles & CConfigurationFile::getRecentSBMLFiles()
{
  return *mpRecentSBMLFiles;
}

//TODO SEDML
CRecentFiles & CConfigurationFile::getRecentSEDMLFiles()
{
  return *mpRecentSEDMLFiles;
}

const std::string CConfigurationFile::getApplicationFont() const
{
  return *mpApplicationFont;
}

void CConfigurationFile::setApplicationFont(const std::string & applicationFont)
{
  *mpApplicationFont = applicationFont;
}

bool CConfigurationFile::useOpenGL() const
{
  return *mpUseOpenGL;
}

void CConfigurationFile::setUseOpenGL(bool useOpenGL)
{
  *mpUseOpenGL = useOpenGL;
}

bool CConfigurationFile::useAdvancedSliders() const
{
  return *mpUseAdvancedSliders;
}

void CConfigurationFile::setUseAdvancedSliders(bool useAdvancedSliders)
{
  *mpUseAdvancedSliders = useAdvancedSliders;
}

bool CConfigurationFile::useAdvancedEditing() const
{
  return *mpUseAdvancedEditing;
}

void CConfigurationFile::setUseAdvancedEditing(bool useAdvancedEditing)
{
  *mpUseAdvancedEditing = useAdvancedEditing;
}

bool CConfigurationFile::normalizePerExperiment() const
{
  return *mpNormalizePerExperiment;
}

void CConfigurationFile::setNormalizePerExperiment(bool flag)
{
  *mpNormalizePerExperiment = flag;
}

bool CConfigurationFile::enableAdditionalOptimizationParameters() const
{
  return *mpEnableAdditionalOptimizationParameters;
}

void CConfigurationFile::setEnableAdditionalOptimizationParameters(bool enableAdditionalOptimizationParameters)
{
  *mpEnableAdditionalOptimizationParameters = enableAdditionalOptimizationParameters;
}

bool CConfigurationFile::displayPopulations() const
{
  return *mpDisplayPopulations;
}

bool CConfigurationFile::validateUnits() const
{
  return *mpValidateUnits;
}

bool CConfigurationFile::showItemIssues(CIssue::eKind kind) const
{
  return mpDisplayIssueKinds->getParameter(static_cast< size_t>(kind))->getValue< bool >();
}

void CConfigurationFile::setDisplayPopulations(bool flag)
{
  *mpDisplayPopulations = flag;
}

bool CConfigurationFile::resizeToContents() const
{
  return *mpResizeToContents;
}

void CConfigurationFile::setResizeToContents(bool flag)
{
  *mpResizeToContents = flag;
}

const std::string CConfigurationFile::getWorkingDirectory() const
{
  return *mpWorkingDirectory;
}

void CConfigurationFile::setWorkingDirectory(const std::string & workingDirectory)
{
  *mpWorkingDirectory = workingDirectory;
}

const std::string CConfigurationFile::getProxyServer() const
{
  return *mpProxyServer;
}

void CConfigurationFile::setProxyServer(const std::string &proxyServer)
{
  *mpProxyServer = proxyServer;
}

C_INT32 CConfigurationFile::getProxyPort() const
{
  return *mpProxyPort;
}

void CConfigurationFile::setProxyPort(C_INT32 proxyPort)
{
  *mpProxyPort = proxyPort;
}

const std::string CConfigurationFile::getProxyUser() const
{
  return *mpProxyUser;
}

void CConfigurationFile::setProxyUser(const std::string &proxyUser)
{
  *mpProxyUser = proxyUser;
}

const std::string CConfigurationFile::getProxyPassword() const
{
  return *mpProxyPass;
}

void CConfigurationFile::setProxyPassword(const std::string &proxyPassword)
{
  *mpProxyPass = proxyPassword;
}

void CConfigurationFile::setValidateUnits(bool validateUnits)
{
  *mpValidateUnits = validateUnits;
}

// set and get for the current author added by Peyman
const std::string & CConfigurationFile::getCurrentAuthorGivenName() const
{
  return *mpCurrentAuthorGivenName;
}
void CConfigurationFile::setCurrentAuthorGivenName(const std::string & CurrentAuthorGivenName)
{
  *mpCurrentAuthorGivenName = CurrentAuthorGivenName;
}
const std::string & CConfigurationFile::getCurrentAuthorFamilyName() const
{
  return *mpCurrentAuthorFamilyName;
}
void CConfigurationFile::setCurrentAuthorFamilyName(const std::string & CurrentAuthorFamilyName)
{
  *mpCurrentAuthorFamilyName = CurrentAuthorFamilyName;
}
const std::string & CConfigurationFile::getCurrentAuthorOrganization() const
{
  return *mpCurrentAuthorOrganization;
}
void CConfigurationFile::setCurrentAuthorOrganization(const std::string & CurrentAuthorOrganization)
{
  *mpCurrentAuthorOrganization = CurrentAuthorOrganization;
}
const std::string & CConfigurationFile::getCurrentAuthorEmail() const
{
  return *mpCurrentAuthorEmail;
}
void CConfigurationFile::setCurrentAuthorEmail(const std::string & CurrentAuthorEmail)
{
  *mpCurrentAuthorEmail = CurrentAuthorEmail;
}

C_INT32 CConfigurationFile::getDoublePrecision() const
{
  return *mpPrecision;
}

void CConfigurationFile::setDoublePrecision(C_INT32 precision)
{
  *mpPrecision = precision;
}

bool CConfigurationFile::getDisableJIT() const
{
  return *mpDisableJIT;
}

void CConfigurationFile::setDisableJIT(bool disableJIT)
{
  *mpDisableJIT = disableJIT;
}

CCheckForUpdates & CConfigurationFile::getCheckForUpdates()
{
  return *mpCheckForUpdates;
}

CCheckForUpdates::CCheckForUpdates(const std::string & name, const CDataContainer * pParent)
  : CCopasiParameterGroup(name, pParent)
  , mpEnabled(NULL)
  , mpSkipVersion(NULL)
  , mpLastChecked(NULL)
  , mpInterval(NULL)
  , mpConfirmedCheck(NULL)
{
  initializeParameter();
}

CCheckForUpdates::CCheckForUpdates(const CCheckForUpdates & src,
                                   const CDataContainer * pParent)
  : CCopasiParameterGroup(src, pParent)
  , mpEnabled(NULL)
  , mpSkipVersion(NULL)
  , mpLastChecked(NULL)
  , mpInterval(NULL)
  , mpConfirmedCheck(NULL)
{
  initializeParameter();
}

CCheckForUpdates::CCheckForUpdates(const CCopasiParameterGroup & src,
                                   const CDataContainer * pParent)
  : CCopasiParameterGroup(src, pParent)
  , mpEnabled(NULL)
  , mpSkipVersion(NULL)
  , mpLastChecked(NULL)
  , mpInterval(NULL)
  , mpConfirmedCheck(NULL)
{
  initializeParameter();
}

// virtual
CCheckForUpdates::~CCheckForUpdates() {}

void CCheckForUpdates::initializeParameter()
{
  mpEnabled = assertParameter("Enabled", CCopasiParameter::Type::BOOL, true);
  mpSkipVersion = assertParameter("Skip Version", CCopasiParameter::Type::STRING, std::string(""));
  mpLastChecked = assertParameter("Last Checked", CCopasiParameter::Type::STRING, std::string("0000-00-00T00:00:00Z"));
  mpInterval = assertParameter("Interval", CCopasiParameter::Type::UINT, (unsigned C_INT32) 7);
  mpConfirmedCheck = assertParameter("Confirmed Check for Update", CCopasiParameter::Type::STRING, std::string(""));

  getParameter("Confirmed Check for Update")->setUserInterfaceFlag(CCopasiParameter::UserInterfaceFlag::None);
}

bool CCheckForUpdates::isEnabled() const
{
  return *mpEnabled;
}

void CCheckForUpdates::setConfirmedCheckForUpdate(bool flag)
{
  *mpConfirmedCheck = flag ? CVersion::VERSION.getVersion() : "";
}

bool CCheckForUpdates::needToConfirmCheckForUpdate() const
{
  return (CVersion().setVersion(*mpConfirmedCheck) < CVersion::VERSION);
}

void CCheckForUpdates::setEnabled(bool enabled)
{
  *mpEnabled = enabled;
}

bool CCheckForUpdates::skipVersion(const CVersion & version) const
{
  return (version <= CVersion().setVersion(*mpSkipVersion));
}

bool CCheckForUpdates::checkRequired() const
{
  if (*mpEnabled && CVersion::VERSION.mayBeUpdated())
    {
      // Compare current time with mpLastChecked + mpInterval days
      time_t lastChecked = timeFromUTC(*mpLastChecked);
      time_t now = timeFromUTC(UTCTimeStamp());

      return difftime(now, lastChecked) > *mpInterval * 86400;
    }

  return false;
}

void CCheckForUpdates::setSkipVersion(const CVersion & version)
{
  *mpSkipVersion = version.getVersion();
}

void CCheckForUpdates::setChecked()
{
  *mpLastChecked = UTCTimeStamp();
}
