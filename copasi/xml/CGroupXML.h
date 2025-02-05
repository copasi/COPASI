// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CGroupXML
#define COPASI_CGroupXML

#include "copasi/utilities/CCopasiParameter.h"
#include "copasi/xml/CCopasiXMLInterface.h"

/**
   * Class dealing with the loading and writing of the XML configuration
   * file.
   */
  class CGroupXML : public CCopasiXMLInterface
  {
    // Operations
  public:
    /**
     * Constructor
     */
    CGroupXML() = delete;

    CGroupXML(CCopasiParameterGroup & group);

    /**
     * Destructor
     */
    ~CGroupXML();

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

    // Attributes
  private:
    /**
     * A reference to the CCopasiParameterGroup containing the information
     */
    CCopasiParameterGroup & mConfiguration;
  };

#endif // CGroupXML
