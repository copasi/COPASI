/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CCopasiXML.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/18 18:58:50 $
   End CVS Header */

/**
 * CCopasiXML class.
 * This class implements a CCopasiXMLInterface to the COPASI XML specified in
 * http://www.copasi.org/schema/copasi.xsd
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#ifndef COPASI_CCopasiXML
#define COPASI_CCopasiXML

#include "CCopasiXMLInterface.h"
#include "utilities/CVersion.h"

class CCopasiParameter;
class CCopasiParameterGroup;
class CCopasiObjectName;

class CCopasiXML : public CCopasiXMLInterface
  {
    // Operations
  public:
    /**
     * Constructor
     */
    CCopasiXML();

    /**
     * Destructor
     */
    ~CCopasiXML();

    /**
     * Save information to a given ostream.
     * @param std::ostream & os
     * @return bool success
     */
    virtual bool save(std::ostream & os);

    /**
     * Load information from a given istream.
     * @param std::istream & is
     * @return bool success
     */
    virtual bool load(std::istream & is);

    /**
     * Retrieve the version of the current XML file. 
     * Before any load operation this contains the COPASI schema version supported by
     * the writer. After load it contains the schema version of the loaded file.
     * @return const CVersion & version
     */
    const CVersion & getVersion() const;

  private:
    /**
     * Save the model.
     * @return bool success
     */
    bool saveModel();

    /**
     * Save the list of functions.
     * @return bool success
     */
    bool saveFunctionList();

    /**
     * Save the list of tasks.
     * @return bool success
     */
    bool saveTaskList();

    /**
     * Save the list of plots.
     * @return bool success
     */
    bool CCopasiXML::savePlotList();

    /**
     * Save the list of reports.
     * @return bool success
     */
    bool saveReportList();

    /**
     * Save a Parameter.
     * @param const CCopasiParameter & parameter
     * @return bool success
     */
    bool saveParameter(const CCopasiParameter & parameter);

    /**
     * Save a Parameter Group.
     * @param const CCopasiParameterGroup::parameterGroup & group
     * @return bool success
     */
    bool saveParameterGroup(const std::vector< CCopasiParameter * > & group);

    /**
     * Save a Report Section such as Header, Body or Footer.
     * @param const std::string & name
     * @param const std::vector <CCopasiObjectName> & section
     * @return bool success
     */
    bool saveReportSection(const std::string & name,
                           const std::vector <CCopasiObjectName> & section);

    /**
     * Build a list of functions.
     * @return bool success
     */
    bool buildFunctionList();

    // Attributes

    /**
     * The version of the COPASI XML Schema the current file adheres to.
     */
    CVersion mVersion;
  };

#endif // COPASI_CCopasiXML
