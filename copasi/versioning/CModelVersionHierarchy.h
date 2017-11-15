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
#include "copasi/utilities/CCopasiTree.h"
#include "copasi/versioning/CModelVersion.h"

class CModelVersionHierarchy : protected CCopasiTree< CCopasiNode < CModelVersion > >
{

public:

  /**
   * Default constructor
   * initiate 100 rows for Model Version Hierarchy data table
   * set parent of current version and pthe to the versioning data files to empty string
   * set the number of saved version 0
   */
  CModelVersionHierarchy();

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
  int getNumberOfVersions() const;

  /**
   * Retrieve the last created or restored version
   */
  std::string getParentOfCurrentModel() const;

  /**
   * Retrieve the Path to the versioning data files
   */
  std::string getPathFile();

  /**
   * Set the Path to the versioning data files
   * This path is set by the COMBINE Archive when a session starts
   * Return true if the path exist otherwise false
   */
  bool setPathFile(std::string PathFile);

  /**
   * Add a new version to Model Version Hierarchy data table
   * Set this new version as the parent of current version
   * Update Versioning Hierarchy XML file
   * Returns: 1 if the version is repeated
   *          2: if the version name is empty
   *          3: if the version name has added to table but XML file was not updated successfully
   *          0: for succes
   */
  int addNewVersion(std::string Version, std::string AuthorGivenName, std::string AuthorFamilyName, std::string AuthorOrganization, std::string AuthorEmail, std::string Comments);

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
  void restoreLastSavedVersioningHierarchy(std::string Version);

  /**
   * Return Parent Version of a given Version
   */
  std::string getParentVersion(std::string Version);

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
  CCopasiNode< CModelVersion > * mpCurrentVersion;

  /**
   * Path to the XML file containing version information
   */
  std::string  mVersionXMLFile;

  /**
   * A set to enforce unique version names
   */
  std::set< std::string > mVersionNames;

  /**
   * Returns true if Version exists in Model Versioning Hierarchy table
   */
  bool isVersionRepeated(std::string Version);

  /**
   * When the last row of Model Versioning Hierarchy table is reached reallocate 100 rows more
   */
  void reallocateModelVersionHierarchyTable(int Nrow);

  /**
   * Returns true if Version XML file updated successfully
   */
  bool updateVersionXML();

  /**
   * Add one row to Model Versioning Hierarchy table with the given data
   */
  void versionToTable(std::string Version, std::string DerivedFrom, std::string AuthorGivenName, std::string AuthorFamilyName, std::string AuthorOrganization, std::string AuthorEmail, std::string Comments, std::string Time);
};

#endif // COPASI_CModelVersionHierarchy
