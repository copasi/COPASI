// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/*
 * CModelVersion.h
 *
 *  Created on: 21 Feb 2016
 *      Author: Peyman Zarrineh
 */

#ifndef COPASI_CModelVersionHierarchy
#define COPASI_CModelVersionHierarchy

#include "copasi/utilities/CCopasiNode.h"
#include "copasi/utilities/CNodeIterator.h"
#include "copasi/versioning/CModelVersion.h"
class CDataModel;

class CModelVersionHierarchy
{

public:
  typedef CCopasiNode < CModelVersion > NodeType;
  typedef CNodeIterator< NodeType > iterator;

private:
  /**
   * Default constructor
   */
  CModelVersionHierarchy();

public:
  /**
   * Specific constructor
   * @param CDataModel & dataModel
   */
  CModelVersionHierarchy(CDataModel & dataModel);

  /**
   * Destructor
   */
  ~CModelVersionHierarchy();

  /**
   * Clear CModelVersion data when a new session starts
   */
  void clear();

  /**
   * Retrieve the number of saved versions
   */
  size_t size() const;

  /**
   * Retrieve the Path to the versioning data files
   */
  std::string getDiretory() const;

  /**
   * Add a new version to Model Version Hierarchy data table
   * Set this new version as the parent of current version
   * Update Versioning Hierarchy XML file
   * Returns: 1 if the version is repeated
   *          2: if the version name is empty
   *          3: if the version name has added to table but XML file was not updated successfully
   *          0: for succes
   */
  int addVersion(std::string version,
                 std::string authorGivenName,
                 std::string authorFamilyName,
                 std::string authorOrganization,
                 std::string authorEmail,
                 std::string comment);

  /**
   * Delete a given version from Model Version Hierarchy data table
   * The root version of versioning hierarchy cannot be deleted in the existence of other versions
   * if 'version == parent of current version' then reset parent of current version to its parent
   * Update Versioning Hierarchy XML file
   * Returns:  1: if the Version is empty
   *           2: if the Version does not exist
   *           3: if the Version is the root version of versioning hierarchy and it is not the only saved version
   *           4: if the version name has been deleted from the table but XML file was not updated successfully
   *           0: success
   */
  int deleteVersion(std::string Version);

  /**
   * Restore a model with a given version name
   * Set the parent of current model as the given version
   * Update Versioning Hierarchy XML file
   * Returns:  1: if the Version is empty
   *           2: if the Version does not exist
   *           3: if the version name has been restored but XML file was not updated successfully
   *           0: success
   */
  int restoreVersion(std::string Version);

  /**
   * Read Versioning Hierarachy XML data file when a file with versioning is opened
   * Returns:  1: if the verioning hierarchy XML file does not exist
   *           2: if the file is parsed but some error(s) has occured
   *           3: if the file cannot be parsed
   *           0: success
   */
  int readVersionXML();

  /**
   * Restore the last saved Version as the parrent of current session before quiting the current session
   * Also XML file must be updated
   */
  void setCurrentVersion(std::string Version);

  CModelVersion & getVersion(const std::string & version);
  const CModelVersion & getVersion(const std::string & version) const;

  /**
   * Return Parent Version of a given Version
   */
  const CModelVersion & getParentVersion(const std::string & version) const;
  const CModelVersion & getParentVersion(const CModelVersion & version) const;

  /**
  *  Returns a list of Versions from the root to the Parent of Current Model
  *  In provenance all the edits from begining to the current model is needed
  */
  std::string getVersionDirectory(const std::string & version) const;
  std::string getVersionDirectory(const CModelVersion & version) const;

  /**
   * Retrieve the last created or restored version
   */
  const CModelVersion &  getCurrentVersion() const;

  /**
   * Retrieve a node iterator
   * @return iterator itNode
   */
  iterator getNodeIterator();

#ifdef COPASI_Provenance
  /**
   * Return all the children Versions of a given Version
   * If this version is deleted, its provenance edits are added to its children provenance edits
   */
  QList<std::string> getChildrenOfVersionForProvenanceXML(std::string Version);

  /**
  *  Returns a list of Versions from the root to the Parent of Current Model
  *  In provenance all the edits from begining to the current model is needed
  */
  QList<std::string> getVersionsPathToCurrentModel();
#endif

private:
  /**
   * Add a new version to Model Version Hierarchy data table
   * Set this new version as the parent of current version
   * Update Versioning Hierarchy XML file
   * Returns: 1 if the version is repeated
   *          2: if the version name is empty
   *          3: if the version name has added to table but XML file was not updated successfully
   *          0: for succes
   */
  int addVersion(const CModelVersion & version);

  static void addChild(NodeType * pParent, NodeType * pChild);

  CDataModel * mpDataModel;

  NodeType * mpRoot;

  NodeType * mpCurrentVersion;

  /**
   * A set to enforce unique version names
   */
  std::map< std::string, NodeType * > mVersionNames;

  /**
   * Returns true if Version exists in Model Versioning Hierarchy table
   */
  bool doesVersionExist(std::string Version);

  /**
   * Returns true if Version XML file updated successfully
   */
  bool updateVersionXML();
};

#endif // COPASI_CModelVersionHierarchy
