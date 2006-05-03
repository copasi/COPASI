/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commandline/CConfigurationFile.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/05/03 15:42:58 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CConfigurationFile.h"
#include "COptions.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CVersion.h"
#include "utilities/utility.h"
#include "utilities/CDirEntry.h"
#include "xml/CCopasiXMLParser.h"

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
    assertParameter("MaxFiles", CCopasiParameter::UINT, (unsigned C_INT32) 5)->getValue().pUINT;
  mpRecentFiles = assertGroup("Recent Files");
}

void CRecentFiles::addFile(const std::string & file)
{
  std::string FileName = file;

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
      ExistingFile = *(*it)->getValue().pSTRING;
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
    mpRecentFiles(NULL)
{initializeParameter();}

CConfigurationFile::CConfigurationFile(const CConfigurationFile & src,
                                       const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mpRecentFiles(NULL)
{initializeParameter();}

CConfigurationFile::CConfigurationFile(const CCopasiParameterGroup & group,
                                       const CCopasiContainer * pParent):
    CCopasiParameterGroup(group, pParent),
    mpRecentFiles(NULL)
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

  return success;
}

void CConfigurationFile::initializeParameter()
{
  assertGroup("Recent Files");
  assertGroup("Recent SBML Files");

  elevateChildren();
}

bool CConfigurationFile::save()
{
  std::string ConfigFile;
  COptions::getValue("ConfigFile", ConfigFile);

  CConfigurationFile::CXML XML;

  //  mpRecentFiles->addFile("laber");

  XML.setConfiguration(*this);

  bool success = XML.CCopasiXMLInterface::save(ConfigFile);

  return success;
}

bool CConfigurationFile::load()
{
  std::string ConfigFile;
  COptions::getValue("ConfigFile", ConfigFile);

  CConfigurationFile::CXML XML;

  bool success = XML.CCopasiXMLInterface::load(ConfigFile);

  if (success)
    {
      *this = XML.getConfiguration();
      initializeParameter();
    }

  return success;
}

CRecentFiles & CConfigurationFile::getRecentFiles()
{return *mpRecentFiles;}

CRecentFiles & CConfigurationFile::getRecentSBMLFiles()
{return *mpRecentSBMLFiles;}

CConfigurationFile::CXML::CXML():
    CCopasiXMLInterface(),
    mConfiguration("Configuration File")
{}

CConfigurationFile::CXML::~CXML()
{}

bool CConfigurationFile::CXML::save(std::ostream & os)
{
  os.imbue(std::locale::classic());
  os.precision(16);

  mpOstream = &os;
  bool success = true;

  *mpOstream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  << std::endl;

  *mpOstream << "<!-- generated with COPASI "
  << CCopasiDataModel::Global->getVersion()->getVersion()
  << " (http://www.copasi.org) at "
  << UTCTimeStamp()
  << " UTC -->"
  << std::endl;

  saveParameter(mConfiguration);

  return true;
}

bool CConfigurationFile::CXML::load(std::istream & is)
{
  is.imbue(std::locale::classic());
  is.precision(16);

  mpIstream = &is;
  bool success = true;
  bool done = false;

  CVersion Version;
  Version.setVersion(0, 0, 0);
  CCopasiXMLParser Parser(Version);

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
    mConfiguration = * Parser.getCurrentGroup();
  else
    mConfiguration.clear();

  return success;
}

void CConfigurationFile::CXML::setConfiguration(const CCopasiParameterGroup & configuration)
{mConfiguration = configuration;}

const CCopasiParameterGroup & CConfigurationFile::CXML::getConfiguration() const
  {return mConfiguration;}
