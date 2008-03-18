// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFUtilities.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/18 19:48:05 $
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
    static
    unsigned C_INT32 fixLocalFileAboutReference(std::string & rdfXml,
        const std::string & newId,
        const std::string & oldId);
  };

#endif // COPASI_CRDFUtilities
