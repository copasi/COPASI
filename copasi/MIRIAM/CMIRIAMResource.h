// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CMIRIAMResource.h,v $
//   $Revision: 1.3.2.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/25 16:49:07 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
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

#include "utilities/CCopasiParameter.h"
#include "utilities/CCopasiParameterGroup.h"
#include <time.h>
#include <string>
#include "utilities/CProcessReport.h"
#include "utilities/utility.h"

class CProcessReport;

class CCopasiParameterGroup;

class CMIRIAMResource : public CCopasiParameterGroup
  {
    //Operations
  public:
    /**
       * Default constructor
       * @param const std::string & name (default: MIRIAM Resource)
       * @param const CCopasiContainer * pParent (default: NULL)
       */
    CMIRIAMResource(const std::string & name = "MIRIAM Resource",
                    const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CMIRIAMResource & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMIRIAMResource(const CMIRIAMResource & src,
                    const CCopasiContainer * pParent = NULL);
    /**
     * Specific constructor
     * @param const CCopasiParameterGroup & group
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMIRIAMResource(const CCopasiParameterGroup & group,
                    const CCopasiContainer * pParent = NULL);

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
     * Set the URL of the MIRIAM Resource.
     * @param const std::string & URL
     */
    void setMIRIAMURL(const std::string & URL);

    /**
     * Retrieve the URL of the MIRIAM Resource.
     * @return const std::string & URL
     */
    const std::string & getMIRIAMURL() const;

    /**
     * Set the URI of the MIRIAM Resource.
     * @param const std::string & URI
     */
    void setMIRIAMURI(const std::string & URI);

    /**
     * Retrieve the URI of the MIRIAM Resource.
     * @return const std::string & URI
     */
    const std::string & getMIRIAMURI() const;

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
     * Retrieve whether the pattern is a RegExp.
     * @param const bool & isRegExp
     */
    void setMIRIAMRegExp(const bool & isRegExp);

    /**
     * Retrieve whether the pattern is a RegExp.
     * @return bool & RegExp
     */
    const bool & getMIRIAMRegExp() const;

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
     * Add a deprecated URL to the MIRIAM Resource
     * @param const std::string & URL
     */
    void addDeprecatedURL(const std::string & URL);

    /**
     * Retrieve the deprecated URL of the MIRIAM Resource
     * @return const CCopasiParameterGroup & deprecatedURLs
     */
    const CCopasiParameterGroup & getMIRIAMDeprecated() const;

  private:
    /**
     * Allocates all group parameters and assures that they are
     * properly initialized.
     */
    void initializeParameter();

    //Attributes
    /**
     * The name used in the GUI
     */
    std::string * mpDisplayName;

    /**
     * A pointer to the URL
     */
    std::string * mpURL;

    /**
     * A pointer to the URI
     */
    std::string * mpURI;

    /**
     * A pointer to the pattern
     */
    std::string * mpPattern;

    /**
     * A pointer to a bool indicating that the pattern is a regexp
     */
    bool * mpRegExp;

    /**
     * A pointer to a bool indication the the resource an be used as reference
     */
    bool * mpCitation;

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
    /**
     * Default constructor
     * @param const std::string & name (default: MIRIAM Resources)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMIRIAMResources(const std::string & name = "MIRIAM Resources",
                     const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CMIRIAMResources & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMIRIAMResources(const CMIRIAMResources & src,
                     const CCopasiContainer * pParent = NULL);
    /**
     * Specific constructor
     * @param const CCopasiParameterGroup & group
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMIRIAMResources(const CCopasiParameterGroup & group,
                     const CCopasiContainer * pParent = NULL);

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
     * Set the of interval between updates
     * @param const unsigned C_INT32 & updateFrequency
     */
    void setMIRIAMUpdateFrequency(const unsigned C_INT32 updateFrequency);

    /**
     * Update the MIRIAM resources
     * @param CProcessReport * pProcessReport
     * @return bool success
     */
    bool updateMIRIAMResources(CProcessReport * pProcessReport);

    /**
     * Automatically update the resources when the last update is older than
     * the current date minus the update interval.
     * @param CProcessReport * pProcessReport
     * @return bool success
     */
    bool autoUpdateMIRIAMResources(CProcessReport * pProcessReport);

    /**
     * Retrieve the indexed resource
     * @param const unsigned C_INT32 index
     * @return const CMIRIAMResource & resource
     */
    const CMIRIAMResource & getMIRIAMResource(const unsigned C_INT32 index) const;

    /**
     * Retrieve the index of the resource with the given URI
     * @param const std::string & URI
     * @return unsigned C_INT32 index
     */
    unsigned C_INT32 getMIRIAMResourceIndex(const std::string & URI) const;

    /**
     * Retrieve the index of the resource with the given display name
     * @param const std::string & displayName
     * @return unsigned C_INT32 index
     */
    unsigned C_INT32 getResourceIndexFromDisplayName(const std::string & displayName) const;

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
     * Create a resource for all unknown MIRIAM resources
     */
    static void initializeUnkownResource();

    //Attributes
    static CMIRIAMResource * pUnknownResource;

    //in seconds
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
    std::map< std::string, unsigned C_INT32 > mDisplayName2Resource;

    /**
     * A map from URI to resource index
     */
    std::map< std::string, unsigned C_INT32 > mURI2Resource;
  }; //class CMIRIAMResources

#endif // COPASI_CMIRIAMResource
