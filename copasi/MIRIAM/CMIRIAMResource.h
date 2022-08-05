// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

/**
 *  CMIRIAMResource class.
 *  This class is used to describe parameters. This class is C_INT32ended
 *  to be used with C_INT32egration or optimization methods or reactions.
 *
 *  Created for COPASI by Anton Ruff 2008
 */

#ifndef COPASI_CMIRIAMResource
#define COPASI_CMIRIAMResource

#include "copasi/utilities/CCopasiParameter.h"
#include "copasi/utilities/CCopasiParameterGroup.h"
#include <time.h>
#include <string>
#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/utility.h"

class CProcessReport;

class CCopasiParameterGroup;

class CMIRIAMResource : public CCopasiParameterGroup
{
  //Operations
public:
  /**
     * Default constructor
     * @param const std::string & name (default: MIRIAM Resource)
     * @param const CDataContainer * pParent (default: NULL)
     */
  CMIRIAMResource(const std::string & name = "MIRIAM Resource",
                  const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param const CMIRIAMResource & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMIRIAMResource(const CMIRIAMResource & src,
                  const CDataContainer * pParent);

  /**
   * Specific constructor
   * @param const CCopasiParameterGroup & group
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMIRIAMResource(const CCopasiParameterGroup & group,
                  const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CMIRIAMResource();

  /**
   * Retrieve the list of MIRIAM Resource.
   * @return const CMIRIAMResource & MIRIAMResource
   */
  const CMIRIAMResource & getMIRIAMMIRIAMResource() const;

  /**
   * Set the Display Name of the MIRIAM Resource.
   * @param const std::string & DisplayName
   */
  void setMIRIAMDisplayName(const std::string & displayName);

  /**
   * Retrieve the Display Name of the MIRIAM Resource.
   * @return const std::string & DisplayName
   */
  const std::string & getMIRIAMDisplayName() const;

  /**
   * Set the URI of the MIRIAM Resource.
   * (this is expected to be of the legacy format (urn:miriam:...))
   *
   * @param const std::string & URI
   *
   */
  void setMIRIAMURI(const std::string & URI);

  /**
   * Retrieve the URI of the MIRIAM Resource.
   * @return const std::string & URI
   */
  const std::string & getMIRIAMURI() const;

  /**
   * Retrieve the identifiers.org URL of the MIRIAM Resource.
   * @param const bool & compact
   * @return std::string URL
   */
  std::string getIdentifiersOrgURL(const bool & compact) const;

  /**
   * Create the URL for the provided Id
   * @param const std::string id
   * @return std::string IdentifiersOrgURL
   */
  std::string  createIdentifiersOrgURL(const std::string id) const;

  /**
   * Set the Pattern of the MIRIAM Resource.
   * @param const std::string & Pattern
   */
  void setMIRIAMPattern(const std::string & pattern);

  /**
   * Retrieve the Pattern of the MIRIAM Resource.
   * @return std::string & Pattern
   */
  const std::string & getMIRIAMPattern() const;

  /**
   * Set whether the resource can be used as reference.
   * @param const bool & isCitation
   */
  void setMIRIAMCitation(const bool & isCitation);

  /**
   * Retrieve whether the resource can be used as reference.
   * @return const bool & isCitation
   */
  const bool & getMIRIAMCitation() const;

  /**
   * Set whether the namespace is embedded in the pattern.
   * @param const bool & isNamespaceEmbeddedInPattern
   */
  void setMIRIAMNamespaceEmbeddedInPattern(const bool & isNamespaceEmbeddedInPattern);

  /**
   * Retrieve whether the resource can be used as reference.
   * @return const bool & isCitation
   */
  const bool & getMIRIAMNamespaceEmbeddedInPattern() const;

  /**
   * Add a deprecated URL to the MIRIAM Resource
   * @param const std::string & URL
   */
  void addDeprecatedURL(const std::string & URL);

  /**
   * Retrieve the deprecated URL of the MIRIAM Resource
   * @return const CCopasiParameterGroup & deprecatedURLs
   */
  const CCopasiParameterGroup & getMIRIAMDeprecated() const;

  /**
   * Extract the ID from the given URI
   * @param const std::string & uri
   * @return std::string ID
   */
  std::string extractId(const std::string & uri) const;

private:
  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

  /**
   * Extract the embedded namespace from the pattern
   * @return std::string namespace
   */
  std::string extractNamespaceFromPattern() const;

  //Attributes
  /**
   * The name used in the GUI
   */
  std::string * mpDisplayName;

  /**
   * A pointer to the URI
   */
  std::string * mpURI;

  /**
   * A pointer to the pattern
   */
  std::string * mpPattern;

  /**
   * A pointer to a bool indication the the resource an be used as reference
   */
  bool * mpCitation;

  /**
   * A pointer to a bool indication the the resource an be used as reference
   */
  bool * mpNamespaceEmbeddedInPattern;

  /**
   * A parameter group holding all deprecated URIs
   */
  CCopasiParameterGroup * mpDeprecated;
}; //class CMIRIAMResource

/////////////////////////////////////////////////////////////////////////////////////////

class CMIRIAMResources : public CCopasiParameterGroup
{
  //Operations
public:
  static void isCitation(void * pData, void * pCallee);
  static bool isCitation(const std::string & uri);

  /**
   * Default constructor
   * @param const std::string & name (default: MIRIAM Resources)
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMIRIAMResources(const std::string & name = "MIRIAM Resources",
                   const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param const CMIRIAMResources & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMIRIAMResources(const CMIRIAMResources & src,
                   const CDataContainer * pParent);
  /**
   * Specific constructor
   * @param const CCopasiParameterGroup & group
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMIRIAMResources(const CCopasiParameterGroup & group,
                   const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CMIRIAMResources();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   * Assignment operator
   * @param const CCopasiParameterGroup & rhs
   * @return const CMIRIAMResources & self
   */
  const CMIRIAMResources & operator=(const CCopasiParameterGroup & rhs);

  /**
   * Add a MIRIAM Resource to the list of MIRIAM Resources
   * @param CMIRIAMResource * pMIRIAMResource
   */
  void addMIRIAMResource(CMIRIAMResource * pMIRIAMResource);

  /**
   * Retrieve the list of MIRIAM Resources
   * @return CMIRIAMResources & MIRIAMResources
   */
  const CMIRIAMResources & getMIRIAMResources() const;

  /**
   * Retrieve the day the resources where last updated
   * @return const unsigned C_INT32 & lastUpdateDay
   */
  const unsigned C_INT32 & getMIRIAMLastUpdateDate() const;

  /**
   * Retrieve the of interval between updates
   * @return const unsigned C_INT32 & updateFrequency
   */
  const unsigned C_INT32 & getMIRIAMUpdateFrequency() const;

  /**
   * Set the days between updates
   * @param const size_t & days
   */
  void setMIRIAMUpdateFrequencyInDays(const size_t & days);

  /**
  * Update the MIRIAM resources using a local filename
  * @param CProcessReport * pProcessReport
  * @return bool success
  */
  bool updateMIRIAMResourcesFromFile(CProcessReport * pProcessReport,
                                     const std::string& filename);

  /**
   * Retrieve the indexed resource
   * @param const size_t index
   * @return const CMIRIAMResource & resource
   */
  const CMIRIAMResource & getMIRIAMResource(const size_t index) const;

  /**
   * Retrieve the index of the resource with the given URI
   * @param const std::string & URI
   * @return size_t index
   */
  size_t getMIRIAMResourceIndex(const std::string & URI) const;

  /**
   * Retrieve the index of the resource with the given display name
   * @param const std::string & displayName
   * @return size_t index
   */
  size_t getResourceIndexFromDisplayName(const std::string & displayName) const;

  //    bool setURI(const std::string & URI);

  /**
   * Retrieve the list of MIRIAM resource as a CCopasiParameterGroup
   * @return const CCopasiParameterGroup & resourceList
   */
  const CCopasiParameterGroup & getResourceList() const;

  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

private:
  //Operations
  /**
   * Set the last update date to the current time
   */
  void setMIRIAMLastUpdateDate();

  /**
   * Retrieve the current date ins seconds
   */
  unsigned C_INT32 getActDateInSeconds();

  /**
   * Initialize the display name to resource index map
   */
  void createDisplayNameMap();

  /**
   * Initialize the URI to resource index map
   */
  void createURIMap();

  /**
   * A pointer to the last update date.
   */
  unsigned C_INT32 * mpLastUpdateDate;

  /**
   * A pointer to the update interval.
   */
  unsigned C_INT32 * mpUpdateFrequency;

  /**
   * A pointer to the group of MIRIAM resources
   */
  CCopasiParameterGroup * mpMIRIAMResources;

  /**
   * A map from display name to resource index
   */
  std::map< std::string, size_t > mDisplayName2Resource;

  /**
   * A map from URI to resource index
   */
  std::map< std::string, size_t > mURI2Resource;
}; //class CMIRIAMResources

#endif // COPASI_CMIRIAMResource
