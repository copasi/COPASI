// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CMIRIAMResource.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/30 18:17:54 $
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
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

    /**
     * Retrieve the list of MIRIAM Resource
     * @return CMIRIAMResource & MIRIAMResource
     */
    const CMIRIAMResource & getMIRIAMMIRIAMResource() const;

    void setMIRIAMDisplayName(const std::string & displayName);

    /**
     * Retrieve the Display Name of the MIRIAM Resource
     * @return std::string & DisplayName
     */
    const std::string & getMIRIAMDisplayName() const;

    void setMIRIAMURL(const std::string & URL);

    /**
     * Retrieve the URL of the MIRIAM Resource
     * @return std::string & URL
     */
    const std::string & getMIRIAMURL() const;

    void setMIRIAMURI(const std::string & URI);

    /**
     * Retrieve the URI of the MIRIAM Resource
     * @return std::string & URI
     */
    const std::string & getMIRIAMURI() const;

    void setMIRIAMPattern(const std::string & pattern);

    /**
     * Retrieve the Pattern of the MIRIAM Resource
     * @return std::string & Pattern
     */
    const std::string & getMIRIAMPattern() const;

    void setMIRIAMRegExp(const bool & regExp);

    /**
     * Retrieve the RegExp of the MIRIAM Resource
     * @return bool & RegExp
     */
    const bool & getMIRIAMRegExp() const;

    void setMIRIAMCitation(const bool & citation);

    /**
     * Retrieve the Citation of the MIRIAM Resource
     * @return bool & Citation
     */
    const bool & getMIRIAMCitation() const;

    void addDeprecatedURL(const std::string & URL);

    /**
     * Retrieve the deprecated of the MIRIAM Resource
     * @return CCopasiParameterGroup & Deprecated
     */
    const CCopasiParameterGroup & getMIRIAMDeprecated() const;

    //void printResource() const;

  private:
    //Attributes
    std::string * mpDisplayName;
    std::string * mpURL;
    std::string * mpURI;
    std::string * mpPattern;
    bool * mpRegExp;
    bool * mpCitation;
    CCopasiParameterGroup * mpDeprecated;

    //Operations
    /**
     * Allocates all group parameters and assures that they are
     * properly initialized.
     */
    void initializeParameter();
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
     * Retrieve the list of Last Update Day
     * @return C_INT32 & lastUpdateDay
     */
    const unsigned C_INT32 & getMIRIAMLastUpdateDate() const;

    /**
     * Retrieve the list of Update Frequency
     * @return C_INT32 & updateFrequency
     */
    const unsigned C_INT32 & getMIRIAMUpdateFrequency() const;

    void setMIRIAMUpdateFrequency(const unsigned C_INT32 updateFrequency);

    bool updateMIRIAMResources(CProcessReport * pProcessReport);

    bool autoUpdateMIRIAMResources(CProcessReport * pProcessReport);

    const CMIRIAMResource & getMIRIAMResource(const unsigned C_INT32 index) const;

    unsigned C_INT32 getMIRIAMResourceIndex(const std::string & URI) const;

    unsigned C_INT32 getResourceIndexFromDisplayName(const std::string & displayName) const;

    bool setURI(const std::string & URI);

    const CCopasiParameterGroup & getResourceList() const;

    /*      void printResources(const std::string & sourceClass,
                              const std::string & sourceFunction) const;*/

  private:
    //Attributes
    //in seconds
    unsigned C_INT32 * mpLastUpdateDate;
    unsigned C_INT32 * mpUpdateFrequency;
    CCopasiParameterGroup * mpMIRIAMResources;

    std::map< std::string, unsigned C_INT32 > mDisplayName2Resource;

    std::map< std::string, unsigned C_INT32 > mURI2Resource;

    //Operations
    /**
     * Allocates all group parameters and assures that they are
     * properly initialized.
     */
    void initializeParameter();

    void setMIRIAMLastUpdateDate();

    unsigned C_INT32 getActDateInSeconds();

    void createDisplayNameMap();

    void createURIMap();
  }; //class CMIRIAMResources

#endif // COPASI_CMIRIAMResource
