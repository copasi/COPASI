/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CCopasiXML.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:36:25 $
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
     * Save the list of reports.
     * @return bool success
     */
    bool saveReportList();

    /**
     * Build a list of functions.
     * @return bool success
     */
    bool buildFunctionList();
  };

#endif // COPASI_CCopasiXML
