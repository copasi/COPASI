// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFUtilities.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/01/07 18:58:54 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CRDFUtilities
#define COPASI_CRDFUtilities

#include <string>

class CRDFUtilities
  {
  public:
    /**
     * Constructor
     */
    CRDFUtilities();

    /**
     * Destructor
     */
    virtual ~CRDFUtilities();

    /**
     * Fix local rdf:about attributes of the rdf:Description element. It returned the
     * number of replacements made.
     * @param std::string & rdfXml
     * @param const std::string & newId
     * @param const std::string & oldId
     * @return unsigned C_INT32 replacements
     */
    static unsigned C_INT32 fixLocalFileAboutReference(std::string & rdfXml,
        const std::string & newId,
        const std::string & oldId);

    /**
     * Fix broken SBML RDF:
     * <dc:creator rdf:parseType="Resource">
     *   <rdf:Bag>
     * It is not allowed to use the attribute rdf:parseType="Resource" and <rdf:Bag> simultaneously
     * @param std::string & rdfXml
     * @return unsigned C_INT32 corrections
     */
    static unsigned C_INT32 fixSBMLRdf(std::string & rdfXml);

    /**
     * Find the qualifier for the given name space. Please note the qualifier if found has a ':'
     * already appended.
     * @param const std::string & rdfXml
     * @param const std::string & nameSpace
     * @return std::string qualifier
     */
    static std::string getNameSpaceQualifier(const std::string & rdfXml,
        const std::string & nameSpace);

    /**
     * Find the the next XML element with the given name (either start or end).
     * @param const std::string & rdfXml
     * @param const std::string & elementName
     * @param std::string::size_type & start
     * @param std::string::size_type & end
     * @return bool found
     */
    static bool findNextElement(const std::string & rdfXml,
                                const std::string & elementName,
                                std::string::size_type & start,
                                std::string::size_type & end);
  };

#endif // COPASI_CRDFUtilities
