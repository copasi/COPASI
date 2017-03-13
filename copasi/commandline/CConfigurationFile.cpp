// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

#include "CConfigurationFile.h"
#include "COptions.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CVersion.h"
#include "utilities/utility.h"
#include "utilities/CDirEntry.h"
#include "MIRIAM/CConstants.h"

#ifdef WITH_NEW_PARSER
# include "xml/parser/CXMLParser.h"
#else
# include "xml/CCopasiXMLParser.h"
#endif

CRecentFiles::CRecentFiles(const std::string & name,
                           const CCopasiContainer * pParent):
  CCopasiParameterGroup(name, pParent),
  mpMaxFiles(NULL),
  mpRecentFiles(NULL)
{initializeParameter();}

CRecentFiles::CRecentFiles(const CRecentFiles & src,
                           const CCopasiContainer * pParent):
  CCopasiParameterGroup(src, pParent),
  mpMaxFiles(NULL),
  mpRecentFiles(NULL)
{initializeParameter();}

CRecentFiles::CRecentFiles(const CCopasiParameterGroup & group,
                           const CCopasiContainer * pParent):
  CCopasiParameterGroup(group, pParent),
  mpMaxFiles(NULL),
  mpRecentFiles(NULL)
{initializeParameter();}

CRecentFiles::~CRecentFiles()
{}

void CRecentFiles::initializeParameter()
{
  mpMaxFiles =
    assertParameter("MaxFiles", CCopasiParameter::UINT, (unsigned C_INT32) 5);
  mpRecentFiles = assertGroup("Recent Files");
  mpRecentFiles->setUserInterfaceFlag(~CCopasiParameter::basic);
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
    mpRecentFiles->addParameter("File", CCopasiParameter::STRING, NewFile);

  return;
}

CConfigurationFile::CConfigurationFile(const std::string & name,
                                       const CCopasiContainer * pParent):
  CCopasiParameterGroup(name, pParent),
  mpRecentFiles(NULL),
  mpRecentSBMLFiles(NULL),
  mpRecentSEDMLFiles(NULL),
  mpRecentMIRIAMResources(NULL),
  mpApplicationFont(NULL),
  mpValidateUnits(NULL),
  mpShowItemIssues(NULL),
  mpUseOpenGL(NULL),
  mpUseAdvancedSliders(NULL),
  mpUseAdvancedEditing(NULL),
  mpNormalizePerExperiment(NULL),
  mpDisplayPopulations(NULL),
  mpWorkingDirectory(NULL),
  mpProxyServer(NULL),
  mpProxyPort(NULL),
  mpProxyUser(NULL),
  mpProxyPass(NULL),
  mpCurrentAuthorGivenName(NULL),
  mpCurrentAuthorFamilyName(NULL),
  mpCurrentAuthorOrganization(NULL),
  mpCurrentAuthorEmail(NULL)
{initializeParameter();}

CConfigurationFile::CConfigurationFile(const CConfigurationFile & src,
                                       const CCopasiContainer * pParent):
  CCopasiParameterGroup(src, pParent),
  mpRecentFiles(NULL),
  mpRecentSBMLFiles(NULL),
  mpRecentSEDMLFiles(NULL),
  mpRecentMIRIAMResources(NULL),
  mpApplicationFont(NULL),
  mpValidateUnits(NULL),
  mpShowItemIssues(NULL),
  mpUseOpenGL(NULL),
  mpUseAdvancedSliders(NULL),
  mpUseAdvancedEditing(NULL),
  mpNormalizePerExperiment(NULL),
  mpDisplayPopulations(NULL),
  mpWorkingDirectory(NULL),
  mpProxyServer(NULL),
  mpProxyPort(NULL),
  mpProxyUser(NULL),
  mpProxyPass(NULL),
  mpCurrentAuthorGivenName(NULL),
  mpCurrentAuthorFamilyName(NULL),
  mpCurrentAuthorOrganization(NULL),
  mpCurrentAuthorEmail(NULL)
{initializeParameter();}

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

  mpRecentMIRIAMResources =
    elevate<CMIRIAMResources, CCopasiParameterGroup>(getGroup("MIRIAM Resources"));
  CMIRIAMResourceObject::setMIRIAMResources(mpRecentMIRIAMResources);

  if (!mpRecentMIRIAMResources) success = false;

  return success;
}

void CConfigurationFile::initializeParameter()
{
  assertGroup("Recent Files");
  assertGroup("Recent SBML Files");
  assertGroup("Recent SEDML Files");

  mpApplicationFont = assertParameter("Application Font", CCopasiParameter::STRING, std::string(""));
  getParameter("Application Font")->setUserInterfaceFlag(~CCopasiParameter::editable);

  assertGroup("MIRIAM Resources")->setUserInterfaceFlag(~CCopasiParameter::basic);

  mpValidateUnits = assertParameter("Validate Units", CCopasiParameter::BOOL, false);
  mpShowItemIssues = assertParameter("Show Item Issues", CCopasiParameter::BOOL, true);
  mpUseOpenGL = assertParameter("Use OpenGL", CCopasiParameter::BOOL, false);
  mpUseAdvancedSliders = assertParameter("Use Advanced Sliders", CCopasiParameter::BOOL, true);
  mpUseAdvancedEditing = assertParameter("Use Advanced Editing", CCopasiParameter::BOOL, false);
  mpNormalizePerExperiment = assertParameter("Normalize Weights per Experiment", CCopasiParameter::BOOL, true);
  mpDisplayPopulations = assertParameter("Display Populations during Optimization", CCopasiParameter::BOOL, false);
  mpWorkingDirectory = assertParameter("Working Directory", CCopasiParameter::STRING, std::string(""));
  getParameter("Working Directory")->setUserInterfaceFlag(~CCopasiParameter::editable);

  mpProxyServer = assertParameter("Proxy Server", CCopasiParameter::STRING, std::string(""));
  mpProxyPort = assertParameter("Proxy Port", CCopasiParameter::INT, 0);
  mpProxyUser = assertParameter("Proxy User", CCopasiParameter::STRING, std::string(""));
  mpProxyPass = assertParameter("Proxy Password", CCopasiParameter::STRING, std::string(""));

  mpCurrentAuthorGivenName = assertParameter("Given Name", CCopasiParameter::STRING, std::string("Anonymous"));
  mpCurrentAuthorFamilyName = assertParameter("Famliy Name", CCopasiParameter::STRING, std::string("Anonymous"));
  mpCurrentAuthorOrganization = assertParameter("Organization", CCopasiParameter::STRING, std::string(""));
  mpCurrentAuthorEmail = assertParameter("Email", CCopasiParameter::STRING, std::string("An.other@mailinator.com"));

  elevateChildren();
}

bool CConfigurationFile::save()
{
  std::string ConfigFile;
  COptions::getValue("ConfigFile", ConfigFile);

  CConfigurationFile::CXML XML;

  XML.setConfiguration(*this);

  bool success = XML.CCopasiXMLInterface::save(ConfigFile, ConfigFile);

  return success;
}

bool CConfigurationFile::load()
{
  std::string ConfigFile;
  COptions::getValue("ConfigFile", ConfigFile);

  CConfigurationFile::CXML XML;

  bool success = XML.CCopasiXMLInterface::load(ConfigFile, ConfigFile);

  if (success)
    {
      *this = XML.getConfiguration();
      initializeParameter();
    }

  if (mpRecentMIRIAMResources->getResourceList().size() == 0)
    {
      // We load the default MIRIAM resources, which are part of the COPASI installation.
      std::string MIRIAMResourceFile;
      COptions::getValue("DefaultConfigDir", MIRIAMResourceFile);
      MIRIAMResourceFile += CDirEntry::Separator + "MIRIAMResources.xml";

      CConfigurationFile::CXML XMLMIRIAMResource;

      if (XMLMIRIAMResource.CCopasiXMLInterface::load(MIRIAMResourceFile,
          MIRIAMResourceFile))
        {
          const CCopasiParameterGroup* group = XMLMIRIAMResource.getConfiguration().getGroup("MIRIAM Resoures");

          if (group == NULL) return false;

          *mpRecentMIRIAMResources = *group;
          mpRecentMIRIAMResources->initializeParameter();
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

CRecentFiles & CConfigurationFile::getRecentFiles()
{return *mpRecentFiles;}

CRecentFiles & CConfigurationFile::getRecentSBMLFiles()
{return *mpRecentSBMLFiles;}

//TODO SEDML
CRecentFiles & CConfigurationFile::getRecentSEDMLFiles()
{return *mpRecentSEDMLFiles;}

CMIRIAMResources & CConfigurationFile::getRecentMIRIAMResources()
{return *mpRecentMIRIAMResources;}

void CConfigurationFile::setRecentMIRIAMResources(const CMIRIAMResources & miriamResources)
{* mpRecentMIRIAMResources = miriamResources;}

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

bool CConfigurationFile::displayPopulations() const
{
  return *mpDisplayPopulations;
}

bool CConfigurationFile::validateUnits() const
{
  return *mpValidateUnits;
}

bool CConfigurationFile::showItemIssues() const
{
  return *mpShowItemIssues;
}

void CConfigurationFile::setDisplayPopulations(bool flag)
{
  *mpDisplayPopulations = flag;
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

void CConfigurationFile::setShowItemIssues(bool showItemIssues)
{
  *mpShowItemIssues = showItemIssues;
}

CConfigurationFile::CXML::CXML():
  CCopasiXMLInterface(),
  mConfiguration("Configuration")
{
  mConfiguration.assertGroup("Recent Files");
  mConfiguration.assertGroup("Recent SBML Files");
  mConfiguration.assertGroup("MIRIAM Resources");
  mConfiguration.assertGroup("Recent SEDML Files");
}

CConfigurationFile::CXML::~CXML()
{}

bool CConfigurationFile::CXML::save(std::ostream & os,
                                    const std::string & relativeTo)
{
  mPWD = relativeTo;

  os.imbue(std::locale::classic());
  os.precision(16);

  mpOstream = &os;

  *mpOstream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
             << std::endl;

  *mpOstream << "<!-- generated with COPASI "
             << CVersion::VERSION.getVersion()
             << " (http://www.copasi.org) at "
             << UTCTimeStamp()
             << " UTC -->"
             << std::endl;

  saveParameter(mConfiguration);

  return true;
}

bool CConfigurationFile::CXML::load(std::istream & is,
                                    const std::string & relativeTo)
{
  mPWD = relativeTo;

  is.imbue(std::locale::classic());
  is.precision(16);

  mpIstream = &is;
  bool success = true;
  bool done = false;

  CVersion Version;

#ifdef WITH_NEW_PARSER
  CXMLParser Parser(Version);
#else
  CCopasiXMLParser Parser(Version);
#endif

#define BUFFER_SIZE 0xfffe
  char * pBuffer = new char[BUFFER_SIZE + 1];

  while (!done)
    {
      mpIstream->get(pBuffer, BUFFER_SIZE, 0);

      if (mpIstream->eof()) done = true;

      if (mpIstream->fail() && !done)
        {
          std::string ConfigFile;
          COptions::getValue("ConfigFile", ConfigFile);
          CCopasiMessage Message(CCopasiMessage::WARNING, MCConfiguration + 2, ConfigFile.c_str());

          done = true;
          success = false;
        }

      if (!Parser.parse(pBuffer, -1, done))
        {
          CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 2,
                                 Parser.getCurrentLineNumber(),
                                 Parser.getCurrentColumnNumber(),
                                 Parser.getErrorString());
          done = true;
          success = false;
        }
    }

  delete [] pBuffer;
#undef BUFFER_SIZE

  if (success && Parser.getCurrentGroup() != NULL)
    {
      mConfiguration = * Parser.getCurrentGroup();
      mConfiguration.setObjectName("Configuration");

      delete Parser.getCurrentGroup();
    }
  else
    mConfiguration.clear();

  return success;
}

void CConfigurationFile::CXML::setConfiguration(const CCopasiParameterGroup & configuration)
{mConfiguration = configuration;}

const CCopasiParameterGroup & CConfigurationFile::CXML::getConfiguration() const
{return mConfiguration;}

// set and get for the current author added by Peyman
const std::string CConfigurationFile::getCurrentAuthorGivenName() const
{
  return *mpCurrentAuthorGivenName;
}
void CConfigurationFile::setCurrentAuthorGivenName(const std::string & CurrentAuthorGivenName)
{
  *mpCurrentAuthorGivenName = CurrentAuthorGivenName;
}
const std::string CConfigurationFile::getCurrentAuthorFamilyName() const
{
  return *mpCurrentAuthorFamilyName;
}
void CConfigurationFile::setCurrentAuthorFamilyName(const std::string & CurrentAuthorFamilyName)
{
  *mpCurrentAuthorFamilyName = CurrentAuthorFamilyName;
}
const std::string CConfigurationFile::getCurrentAuthorOrganization() const
{
  return *mpCurrentAuthorOrganization;
}
void CConfigurationFile::setCurrentAuthorOrganization(const std::string & CurrentAuthorOrganization)
{
  *mpCurrentAuthorOrganization = CurrentAuthorOrganization;
}
const std::string CConfigurationFile::getCurrentAuthorEmail() const
{
  return *mpCurrentAuthorEmail;
}
void CConfigurationFile::setCurrentAuthorEmail(const std::string & CurrentAuthorEmail)
{
  *mpCurrentAuthorEmail = CurrentAuthorEmail;
}
