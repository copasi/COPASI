// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#ifndef COPASI_CConfigurationFile
#define COPASI_CConfigurationFile

#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/MIRIAM/CMIRIAMResource.h"
#include "copasi/xml/CCopasiXMLInterface.h"

class CMIRIAMResources;
class CVersion;

class CCheckForUpdates : public CCopasiParameterGroup
{
public:
  /**
   * Default constructor
   * @param const std::string & name (default: Check for Updates)
   * @param const CDataContainer * pParent (default: NULL)
   */
  CCheckForUpdates(const std::string & name = "Check for Updates",
                   const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param const CCheckForUpdate & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CCheckForUpdates(const CCheckForUpdates & src,
                   const CDataContainer * pParent);

  /**
   * Specific constructor
   * @param const CCopasiParameterGroup & group
   * @param const CDataContainer * pParent (default: NULL)
   */
  CCheckForUpdates(const CCopasiParameterGroup & group,
                   const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CCheckForUpdates();

  void setEnabled(bool enabled);

  bool isEnabled() const;

  void setConfirmedCheckForUpdate(bool flag);

  bool needToConfirmCheckForUpdate() const;

  bool skipVersion(const CVersion & version) const;

  bool checkRequired() const;

  void setSkipVersion(const CVersion & version);

  void setChecked();

private:
  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

  bool * mpEnabled;

  std::string * mpSkipVersion;

  std::string * mpLastChecked;

  unsigned C_INT32 * mpInterval;

  std::string * mpConfirmedCheck;
};

class CRecentFiles : public CCopasiParameterGroup
{
  // Operations
public:
  /**
   * Default constructor
   * @param const std::string & name (default: Recent Files)
   * @param const CDataContainer * pParent (default: NULL)
   */
  CRecentFiles(const std::string & name = "Recent Files",
               const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param const CRecentFiles & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CRecentFiles(const CRecentFiles & src,
               const CDataContainer * pParent);

  /**
   * Specific constructor
   * @param const CCopasiParameterGroup & group
   * @param const CDataContainer * pParent (default: NULL)
   */
  CRecentFiles(const CCopasiParameterGroup & group,
               const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CRecentFiles();

  /**
   * Add a file to the list of recent files
   * @param const std::string & file
   */
  void addFile(const std::string & file);

private:
  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

  // Attributes
private:
  /**
   * A pinter to the maximal number of recent files
   */
  unsigned C_INT32 * mpMaxFiles;

  /**
   * A pointer to the list of recent files.
   */
  CCopasiParameterGroup * mpRecentFiles;
};

class CConfigurationFile : public CCopasiParameterGroup
{
  // Operations
public:
  /**
   * Default constructor
   * @param const std::string & name (default: Configuration)
   * @param const CDataContainer * pParent (default: NULL)
   */
  CConfigurationFile(const std::string & name = "Configuration",
                     const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param const CConfigurationFile & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CConfigurationFile(const CConfigurationFile & src,
                     const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CConfigurationFile();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   * Save the configuration file.
   * @return bool success
   */
  virtual bool save();

  /**
   * Load the configuration file.
   * @return bool success
   */
  virtual bool load();

  /**
   * Assignment operator
   * @param const CCopasiParameterGroup & rhs
   * @return const CConfigurationFile & self
   */
  const CConfigurationFile & operator=(const CCopasiParameterGroup & rhs);

  const CConfigurationFile & operator=(const CConfigurationFile & rhs);

  /**
   * Retrieve the list of recent files
   * @return CRecentFiles & recentFiles
   */
  CRecentFiles & getRecentFiles();

  /**
   * Retrieve the list of recent SBML files
   * @return CRecentFiles & recentSBMLFiles
   */
  CRecentFiles & getRecentSBMLFiles();

  //TODO SEDML
  /**
   * Retrieve the list of recent SEDML files
   * @return CRecentFiles & recentSEDMLFiles
   */
  CRecentFiles & getRecentSEDMLFiles();

  /**
   * Retrieve the list of recent MIRIAM Resources
   * @return CMIRIAMResources & recentMIRIAMResources
   */
  CMIRIAMResources & getRecentMIRIAMResources();

  void setRecentMIRIAMResources(const CMIRIAMResources & miriamResources);

  /**
   * Retrieve the application font.
   * @return const std::string & applicationFont
   */
  const std::string getApplicationFont() const;

  /**
   * Set the applications font.
   * @param const std::string & applicationFont
   */
  void setApplicationFont(const std::string & applicationFont);

  /**
   * Always perform unit validation
   * @return a flag indicating whether unit validation should always be performed
   */
  bool validateUnits() const;

  /**
   * Set whether unit validation should always be performed or not.
   * @param bool validateUnits
   */
  void setValidateUnits(bool validateUnits);

  /**
   * Show item issues
   * @return a flag indicating whether an icon and tooltip should be
   * displayed for items.
   */
  bool showItemIssues(CIssue::eKind kind) const;

  /**
   * @return a flag on whether to use the open GL based rendering, or the Qt based one
   */
  bool useOpenGL() const;

  /**
   *  Set whether the openGL based rendering is to be used (true), or the Qt based one.
   */
  void setUseOpenGL(bool useOpenGL);

  /**
   * @return a flag on whether the sliders should react to keyboard input / mouse
   * interaction.
   */
  bool useAdvancedSliders() const;

  /**
   *  Set whether the sliders should react to keyboard input / mouse
   * interaction.
   */
  void setUseAdvancedSliders(bool useAdvancedSliders);

  /**
   * @return a flag on whether to use the advanced expression editing (i.e manually entering copasiobjects)
   */
  bool useAdvancedEditing() const;

  /**
   *  Set whether the  advanced expression editing (i.e manually entering copasiobjects) is to be used (true), or not
   */
  void setUseAdvancedEditing(bool useAdvancedEditing);

  /**
   * @return a flag on whether weights in Parameter Estimation should be normalized per experiment
   */
  bool normalizePerExperiment() const;

  /**
   *  Set whether weights in Parameter Estimation should be normalized per experiment
   */
  void setNormalizePerExperiment(bool flag);

  /**
   * @return a flag on whether to enable additional parameters in optimization methods
   */
  bool enableAdditionalOptimizationParameters() const;

  /**
   *  Set whether to enable additional parameters in optimization methods
   */
  void setEnableAdditionalOptimizationParameters(bool enableAdditionalOptimizationParameters);

  /**
  * @return a flag on whether populations should be displayed during optimization / parameter estimation
  */
  bool displayPopulations() const;

  /**
  *  Set whether weights in Parameter Estimation should be normalized per experiment
  */
  void setDisplayPopulations(bool flag);

  /**
   * @return a flag on whether the GUI should resize tables to contents
   */
  bool resizeToContents() const;

  /**
  *  Set whether the GUI should resize tables to contents
  */
  void setResizeToContents(bool flag);

  /**
   * Retrieve the working directory
   * @return const std::string & workingDirectory
   */
  const std::string getWorkingDirectory() const;

  /**
   * Set the working directory.
   * @param const std::string & workingDirectory
   */
  void setWorkingDirectory(const std::string & workingDirectory);

  /**
   * Retrieve the proxy server
   */
  const std::string getProxyServer() const;

  /**
   * Set the proxy server.
   * @param proxyServer the proxy server
   */
  void setProxyServer(const std::string & proxyServer);

  /**
   * Retrieve the proxy port
   */
  C_INT32 getProxyPort() const;

  /**
   * Set the proxy port.
   * @param proxyPort the proxy port
   */
  void setProxyPort(C_INT32 proxyPort);

  /**
   * Retrieve the proxy user name
   */
  const std::string getProxyUser() const;

  /**
   * Set the proxy user name.
   * @param proxyUser the proxy username
   */
  void setProxyUser(const std::string & proxyUser);

  /**
   * Retrieve the proxy user password
   */
  const std::string getProxyPassword() const;

  /**
   * Set the proxy user password.
   * @param proxyPassword the proxy password
   */
  void setProxyPassword(const std::string & proxyPassword);

  /**
     * Retrieve the Current Author GivenName
     * @return const std::string & CurrentAuthorGivenName
     */
  const std::string & getCurrentAuthorGivenName() const;

  /**
   * Set the Current Author Given Name.
   * @param const std::string & CurrentAuthorGivenName
   */
  void setCurrentAuthorGivenName(const std::string & CurrentAuthorGivenName);
  /**
   * Retrieve the Current Author Familyname
   * @return const std::string & CurrentAuthorFamilyName
   */
  const std::string & getCurrentAuthorFamilyName() const;
  /**
   * Set the Current Author  Familyname.
   * @param const std::string & CurrentAuthorFamilyName
   */
  void setCurrentAuthorFamilyName(const std::string & CurrentAuthorFamilyName);
  /**
   * Retrieve the Current Author Organization
   * @return const std::string & CurrentAuthorOrganization
   */
  const std::string & getCurrentAuthorOrganization() const;

  /**
   * Set the Current Author Organization.
   * @param const std::string & CurrentAuthorOrganization
   */
  void setCurrentAuthorOrganization(const std::string & CurrentAuthorOrganization);
  /**
   * Retrieve the Current Author Email
   * @return const std::string & CurrentAuthorEmail
   */
  const std::string & getCurrentAuthorEmail() const;

  /**
   * Set the Current Author Email.
   * @param const std::string & CurrentAuthorEmail
   */
  void setCurrentAuthorEmail(const std::string & CurrentAuthorEmail);

  /**
   * @return the double precision to be used when converting to string
   */
  C_INT32 getDoublePrecision() const;

  /**
   * sets the double precision to be used when converting numbers to
   * string
   */
  void setDoublePrecision(C_INT32 precision);

  /**
   * @return auto update settings
   */
  CCheckForUpdates & getCheckForUpdates();

  /**
   * Return whether JIT is disabled
   * @return bool disbaleJIT
   */
  bool getDisableJIT() const;

  /**
   * Sets the whether JIT compilation is diable
   * @param bool disableJIT
   */
  void setDisableJIT(bool disableJIT);

private:
  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

  // Attributes
private:
  /**
   * Class dealing with the loading and writing of the XML configuration
   * file.
   */
  class CXML : public CCopasiXMLInterface
  {
    // Operations
  public:
    /**
     * Constructor
     */
    CXML();

    /**
     * Destructor
     */
    ~CXML();

    /**
     * Save information to a given ostream.
     * @param std::ostream & os
     * @param const std::string & relativeTo
     * @return bool success
     */
    virtual bool save(std::ostream & os,
                      const std::string & relativeTo);

    /**
     * Load information from a given istream.
     * @param std::istream & is
     * @param const std::string & relativeTo
     * @return bool success
     */
    virtual bool load(std::istream & is,
                      const std::string & relativeTo);

    /**
     * Set the configuration contents
     * @param const CConfigurationFile & configuration
     */
    void setConfiguration(const CCopasiParameterGroup & configuration);

    /**
     * Retrieve the configuration contents
     * @return const CConfigurationFile & configuration
     */
    const CCopasiParameterGroup & getConfiguration() const;

    // Attributes
  private:
    /**
     * A pointer to the CCopasiParameterGroup containing the information
     */
    CCopasiParameterGroup mConfiguration;
  };

  /**
   * A pointer to the list of recent files
   */
  CRecentFiles * mpRecentFiles;

  /**
   * A pointer to the list of recent files
   */
  CRecentFiles * mpRecentSBMLFiles;

  //TODO SEDML
  /**
   * A pointer to the list of recent files
   */
  CRecentFiles * mpRecentSEDMLFiles;

  /**
   * A pointer to the list of MIRIAM Resources
   */
  CMIRIAMResources * mpRecentMIRIAMResources;

  /**
   * A pointer to the application font
   */
  std::string * mpApplicationFont;

  /**
   * A pointer indicating the severity level of issues
   * to be displayed.
   */
  CCopasiParameterGroup * mpDisplayIssueSeverity;

  /**
   * A pointer to a group indicating which kinds of issues
   * should be displayed.
   */
  CCopasiParameterGroup * mpDisplayIssueKinds;

  /**
   * A pointer indicating whether units will always be validated
   */
  bool * mpValidateUnits;

  /**
  * A pointer indicating whether to use the OpenGL rendering, or the Qt based one
   */
  bool *mpUseOpenGL;

  /**
  * A pointer indicating whether the sliders should react to keyboard input / mouse
   * interaction.
   */
  bool *mpUseAdvancedSliders;

  /**
   * A pointer indicating whether to use the advanced editing
   */
  bool *mpUseAdvancedEditing;

  /**
   * A pointer indicating whether to experiments should be normalized by default
   */
  bool *mpNormalizePerExperiment;

  /**
   * A pointer to a flag indicating whether to enable additional parameters in optimization methods
   */
  bool *mpEnableAdditionalOptimizationParameters;

  /**
  * A pointer indicating whether to display the population visualization window
  */
  bool *mpDisplayPopulations;

  /**
   * A pointer to the last used working directory of the GUI.
   */
  std::string * mpWorkingDirectory;

  /**
   * A pointer to the proxy server.
   */
  std::string * mpProxyServer;

  /**
   * A pointer to the proxy port.
   */
  C_INT32* mpProxyPort;

  /**
   * A pointer to the proxy user name.
   */
  std::string * mpProxyUser;

  /**
   * A pointer to the proxy password.
   */
  std::string * mpProxyPass;

  //This part is added by Peyman to keep current author information
  /**
   * A pointer to the Given name of the current author.
   */
  std::string * mpCurrentAuthorGivenName;
  /**
   * A pointer to the Familyname of the current author.
   */
  std::string * mpCurrentAuthorFamilyName;
  /**
   * A pointer to the Organization of the current author.
   */
  std::string * mpCurrentAuthorOrganization;
  /**
   * A pointer to the Email of the current author.
   */
  std::string * mpCurrentAuthorEmail;

  /**
   * a pointer to the double precision requested when converting numbers
   * to string
   */
  C_INT32* mpPrecision;

  /**
   * A pointer to the update check configuration
   */
  CCheckForUpdates * mpCheckForUpdates;

  /**
   * A pointer indicating whether the GUI should resize tables to contents
   */
  bool * mpResizeToContents;

  /**
   * A pointer indicating whether to disable JIT compilation even if it is available
   */
  bool * mpDisableJIT;
};

#endif // COPASI_CConfigurationFile
