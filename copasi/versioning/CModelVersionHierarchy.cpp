// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/*
 * CModelVersion.cpp
 *
 *  Created on: 21 Feb 2016
 *      Author: Peyman Zarrineh
 */

#include "CModelVersionHierarchy.h"

#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLOutputStream.h>
#include <sbml/xml/XMLErrorLog.h>

#include "copasi/utilities/CDirEntry.h"
#include "copasi/utilities/utility.h"
#include "copasi/utilities/CNodeIterator.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/utilities/CVersion.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/commandline/COptions.h"

CModelVersionHierarchy::CModelVersionHierarchy()
  : mpDataModel(NULL)
  , mpRoot(new NodeType())
  , mpCurrentVersion(NULL)
  , mVersionNames()
{
  mpCurrentVersion = mpRoot;
  mVersionNames[mpCurrentVersion->getData().getName()] = mpCurrentVersion;
}

CModelVersionHierarchy::CModelVersionHierarchy(CDataModel & dataModel)
  : mpDataModel(& dataModel)
  , mpRoot(new NodeType())
  , mpCurrentVersion(NULL)
  , mVersionNames()
{
  mpCurrentVersion = mpRoot;
  mVersionNames[mpCurrentVersion->getData().getName()] = mpCurrentVersion;
}

CModelVersionHierarchy::~CModelVersionHierarchy()
{}

void CModelVersionHierarchy::clear()
{}

size_t CModelVersionHierarchy::size() const
{
  size_t count = C_INVALID_INDEX;
  iterator itNode(mpRoot);

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      ++count;
    }

  return count;
}

CModelVersionHierarchy::iterator CModelVersionHierarchy::getNodeIterator()
{
  iterator itNode(mpRoot);
  itNode.setProcessingModes(CNodeIteratorMode::Before);
  itNode.next();

  return itNode;
}

const CModelVersion &  CModelVersionHierarchy::getCurrentVersion() const
{
  return mpCurrentVersion->getData();
}

std::string CModelVersionHierarchy::getDiretory() const
{
  return mpDataModel->getReferenceDirectory();
}

bool CModelVersionHierarchy::doesVersionExist(std::string Version)
{
  return mVersionNames.find(Version) != mVersionNames.end();
}

int CModelVersionHierarchy::addVersion(const CModelVersion & version)
{
  if (version.getName().empty())
    {
      return (2);
    }

  if (doesVersionExist(version.getName()))
    {
      return (1);
    }

  std::map< std::string, NodeType * >::iterator found = mVersionNames.find(version.getParentName());

  if (found == mVersionNames.end())
    {
      return (2);
    }

  NodeType * pNewVersion = new NodeType();
  pNewVersion->setData(version);

  NodeType * pParent = found->second;
  addChild(found->second, pNewVersion);
  mVersionNames[pNewVersion->getData().getName()] = pNewVersion;

  return (0);
}

// static
void CModelVersionHierarchy::addChild(NodeType * pParent, NodeType * pChild)
{
  // We order the children according to UTC Time
  NodeType * pSibling = pParent->getChild();

  while (pSibling != NULL)
    {
      NodeType * pNext = pSibling->getSibling();

      if (pNext != NULL &&
          pNext->getData().getUTCTimeStamp() > pChild->getData().getUTCTimeStamp())
        {
          break;
        }

      pSibling = pNext;
    }

  pParent->addChild(pChild, pSibling);
}

int CModelVersionHierarchy::addVersion(std::string version,
                                       std::string authorGivenName,
                                       std::string authorFamilyName,
                                       std::string authorOrganization,
                                       std::string authorEmail,
                                       std::string comment)
{
  CModelVersion NewVersion(version, mpCurrentVersion->getData().getName(), authorGivenName, authorFamilyName, authorOrganization,
                           authorEmail, comment, UTCTimeStamp());

  int i = addVersion(NewVersion);

  if (i != 0)
    return i;

  // TODO CRITICAL we need to create the version directory and copy the files to the combine archive
  std::string Directory = getVersionDirectory(NewVersion.getName());
  CDirEntry::createDir(CDirEntry::fileName(Directory), CDirEntry::dirName(Directory));
  CDirEntry::copy(mpDataModel->getFileName(), Directory + "/model.cps");

  setCurrentVersion(NewVersion.getName());

  // TODO CRITICAL If provenance is enabled we need to move the provenance information and create a new one.

  if (updateVersionXML())
    {
      return (0);
    }
  else
    {
      return (3); //If Versioning Hierarchy xml file was not updated properly
    }
}

int CModelVersionHierarchy::deleteVersion(std::string Version)
{
  if (Version.empty())
    {
      return (1);
    }

  std::map< std::string, NodeType * >::iterator found = mVersionNames.find(Version);

  if (found == mVersionNames.end())
    {
      return (2);
    }

  if (found->second == mpCurrentVersion)
    {
      mpCurrentVersion = mpCurrentVersion->getParent();
    }

  // TODO CRITICAL If provenance is enabled we need to merge the provenance information into the children.

  // TODO CRITICAL We need to remove the directory and the contained files from the combine archive.
  std::string Directory = getVersionDirectory(Version);
  CDirEntry::removeFiles("*", Directory);
  CDirEntry::remove(Directory);

  // All children need to be moved to the parent
  NodeType * pParent = found->second->getParent();
  NodeType * pChild = NULL;

  while ((pChild = found->second->getChild()) != NULL)
    {
      found->second->removeChild(pChild);

      pChild->getData().mParentName = pParent->getData().getParentName();
      addChild(pParent, pChild);
    }

  delete found->second;
  mVersionNames.erase(found);

  if (updateVersionXML())
    {
      return (0);
    }
  else
    {
      return (3); //If Versioning Hierarchy xml file was not updated properly
    }
}

int CModelVersionHierarchy::restoreVersion(std::string Version)
{
  if (Version.empty())
    {
      return (1);
    }

  std::map< std::string, NodeType * >::iterator found = mVersionNames.find(Version);

  if (found == mVersionNames.end())
    {
      return (2);
    }

  mpCurrentVersion = found->second;

  // TODO CRITICAL we need to copy the files to the combine archive
  std::string Directory = getVersionDirectory(mpCurrentVersion->getData().getName());
  CDirEntry::copy(Directory + "/model.cps", mpDataModel->getFileName());

  // TODO CRITICAL Handle provenance.

  if (updateVersionXML())
    {
      return (0);
    }
  else
    {
      return (3); //If Versioning Hierarchy xml file was not updated properly
    }
}
bool CModelVersionHierarchy::updateVersionXML()
{
  bool success = true;
  // We are first writing to a temporary file to prevent accidental
  // destruction of an existing file in case the save command fails.
  std::string TmpFileName;
  COptions::getValue("Tmp", TmpFileName);
  TmpFileName = CDirEntry::createTmpName(TmpFileName, ".xml");

  try
    {
      std::ofstream os(CLocaleString::fromUtf8(TmpFileName).c_str(), std::ios::out);

      if (os.fail())
        {
          CDirEntry::remove(TmpFileName);
          return false;
        }

      XMLOutputStream XML(os, "UTF-8", true, "COPASI", CVersion::VERSION.getVersion());

      os << "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiVersionHierarchy.rng\" type=\"xml\"?>" << std::endl;

      XML.startElement("VersionHierarchy");
      XML.writeAttribute("xmlns", "http://www.copasi.org/static/schema");
      XML.writeAttribute("versionMajor", CVersion::VERSION.getVersionMajor());
      XML.writeAttribute("versionMinor", CVersion::VERSION.getVersionMinor());
      XML.writeAttribute("versionDevel", CVersion::VERSION.getVersionDevel());
      XML.writeAttribute("copasiSourcesModified", CVersion::VERSION.isSourceModified());

      XML.startElement("listOfVersions");

      iterator itNode = getNodeIterator();

      while (itNode.next() != itNode.end())
        {
          if (*itNode == NULL ||
              *itNode == mpRoot)
            {
              continue;
            }

          XML << itNode->getData();
        }

      XML.endElement("listOfVersions");

      XML.startElement("currentVersion");
      XML.writeAttribute("name", mpCurrentVersion->getData().getName());
      XML.endElement("currentVersion");
      XML.endElement("VersionHierarchy");
    }

  catch (...)
    {
      CDirEntry::remove(TmpFileName);
      return false;
    }

  //XMLErrorLog log;
  std::string dataFile = getDiretory();

  if (dataFile.empty())
    {
      dataFile = "VersionHierarchy.xml";
    }
  else
    {
      dataFile += "/VersionHierarchy.xml";
    }

  if (success && !CDirEntry::move(TmpFileName, dataFile))
    success = false;

  return success;
}

int CModelVersionHierarchy::readVersionXML()
{
  // error log for logging errors while reading
  XMLErrorLog log;

  std::string dataFile = getDiretory();

  if (dataFile.empty())
    {
      dataFile = "VersionHierarchy.xml";
    }
  else
    {
      dataFile += "/VersionHierarchy.xml";
    }

  if (!CDirEntry::exist(dataFile))
    {
      return (1);
    }

  XMLInputStream stream(dataFile.c_str(), true, "", &log);
  stream.skipText();

  // Check whether we have the correct file format
  if (!(stream.peek().isStart()) ||
      stream.peek().getName() != "VersionHierarchy")
    {
      return (3);
    }

  // Save the current hierarchy
  NodeType * pOldRoot = mpRoot;
  NodeType * pOldCurrentVersion = mpCurrentVersion;
  std::map< std::string, NodeType * > OldVersionNames = mVersionNames;

  mVersionNames.clear();
  mpRoot = new NodeType();
  mpCurrentVersion = mpRoot;
  mVersionNames[mpCurrentVersion->getData().getName()] = mpCurrentVersion;

  XMLToken VersionHierarchy = stream.next();

  // now read as long as we have something
  while (stream.isGood())
    {

      stream.skipText();

      // grab the next element
      XMLToken current = stream.next();

      // if we reached the end table element, we stop
      if (current.isEndFor(VersionHierarchy))
        break;

      if (!current.isStart()) continue;

      if (current.getName() == "listOfVersions")
        {
          // Do nothing
        }
      else if (current.getName() == "version")
        {
          addVersion(CModelVersion(stream, current));
        }
      else if (current.getName() == "currentVersion")
        {
          setCurrentVersion(current.getAttrValue("name"));
        }
    }

  if (log.getNumErrors() > 0)
    {
      log.printErrors();

      // Restore the old state;
      delete mpRoot;

      mpRoot = pOldRoot;
      mpCurrentVersion = pOldCurrentVersion;
      mVersionNames = OldVersionNames;

      return (2);
    }

  // Clear the old version
  delete pOldRoot;

  return (0);
}

#ifdef COPASI_Provenance
QList<std::string>  CModelVersionHierarchy::getChildrenOfVersionForProvenanceXML(std::string Version)
{
  int i;
  QList<std::string>  ChildrenVersions;

  //Check if the Version has any child - add them to list
  for (i = 0; i < mNRow; i++)
    {
      if ((std::string::compare(mpModelVersionHierarchy->item(i, 1)->text(), Version, Qt::CaseInsensitive)) == 0)
        {
          ChildrenVersions.append(mpModelVersionHierarchy->item(i, 0)->text());
        }
    }

  return (ChildrenVersions);
}

std::string getVersionDirectory(const std::string & version) const
{
  QList<std::string> ReversePath, DirectPath;

// Fill the Version path to a QList from the current version to the root verison
  ReversePath.append(mParentOfCurrentModel);
  bool HasParent = true;
  std::string Version = mParentOfCurrentModel;
  std::string parentVersion;

  while (HasParent)
    {
      int i = 0;
      HasParent = false;

      for (i = 0; i < mNRow; i++)
        {
          if ((std::string::compare(mpModelVersionHierarchy->item(i, 0)->text(), Version, Qt::CaseInsensitive)) == 0)
            {
              parentVersion = mpModelVersionHierarchy->item(i, 1)->text();
              HasParent = true;
              break;
            }
        }

      if (HasParent)
        {
          ReversePath.append(parentVersion);
          Version = parentVersion;
        }
    }

// Reverse the QList to have the Version path from root version to the current version
  if (!ReversePath.isEmpty())
    {
      int j;

      for (j = 0; j < ReversePath.size(); ++j)
        {
          DirectPath.append(ReversePath.at(ReversePath.size() - (j + 1)));
        }
    }

  return (DirectPath);
}
#endif

void CModelVersionHierarchy::setCurrentVersion(std::string Version)
{
  if (Version.empty())
    {
      return;
    }

  std::map< std::string, NodeType * >::iterator found = mVersionNames.find(Version);

  if (found == mVersionNames.end())
    {
      return;
    }

  mpCurrentVersion = found->second;
}

CModelVersion & CModelVersionHierarchy::getVersion(const std::string & version)
{
  std::map< std::string, NodeType * >::const_iterator found = mVersionNames.find(version);

  if (found != mVersionNames.end())
    {
      return found->second->getData();
    }

  static CModelVersion Invalid;
  return Invalid;
}

const CModelVersion & CModelVersionHierarchy::getVersion(const std::string & version) const
{
  std::map< std::string, NodeType * >::const_iterator found = mVersionNames.find(version);

  if (found != mVersionNames.end())
    {
      return found->second->getData();
    }

  static CModelVersion Invalid;
  return Invalid;
}

const CModelVersion & CModelVersionHierarchy::getParentVersion(const std::string & version) const
{
  std::map< std::string, NodeType * >::const_iterator found = mVersionNames.find(version);

  if (found != mVersionNames.end() &&
      found->second->getParent() != NULL)
    {
      return found->second->getParent()->getData();
    }

  static CModelVersion Invalid;
  return Invalid;
}

const CModelVersion & CModelVersionHierarchy::getParentVersion(const CModelVersion & version) const
{
  return getParentVersion(version.getName());
}

std::string CModelVersionHierarchy::getVersionDirectory(const std::string & version) const
{
  std::string Directory = getDiretory();

  if (version == mpRoot->getData().getName())
    {
      return Directory;
    }

  std::map< std::string, NodeType * >::const_iterator found = mVersionNames.find(version);

  if (found != mVersionNames.end())
    {
      return Directory + "/" + version;
    }

  return "";
}

std::string CModelVersionHierarchy::getVersionDirectory(const CModelVersion & version) const
{
  return getVersionDirectory(version.getName());
}
