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
  };

#endif // COPASI_CCopasiXML
