// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/Attic/CAuthor.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/01/29 15:43:44 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CAuthors: Stores author name, email and other (vCard) details.
 *
 *
 */

#ifndef COPASI_CAUTHOR
#define COPASI_CAUTHOR

#include <string>

#include "report/CCopasiContainer.h"

class CAuthor : public CCopasiContainer
  {
    // Attributes
  private:

    std::string mKey;

    /** ID in RDF Graph corresponding to this object.*/
    std::string mRDFGraphNodeID;

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & objectName
    * @param const std::string & RDFGraphNodeID
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CAuthor(const std::string & objectName, const CCopasiContainer * pParent = NULL,
            const std::string & RDFGraphNodeID = "");

    /**
     * Copy constructor
     * @param "const CAuthor &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CAuthor(const CAuthor & src,
            const CCopasiContainer * pParent = NULL);

    ~CAuthor();
    void initObjects();

    /** Add the given name to Last name to get the full Name.
         *
         */

    const std::string getFamilyName() const;

    const std::string getGivenName() const;

    const std::string getEmail() const;

    const std::string getORG() const;

    void setFamilyName(const std::string familyName);

    void setGivenName(const std::string givenName);

    void setEmail(const std::string Email);

    void setORG(const std::string Orgname);

    std::string getRDFGraphNodeID();

    const std::string getObjectName() const;

    /**
        *  Returns a string with the name of this Author.
        *  @return std::string key
        */
    virtual const std::string & getKey() const;
  };

#endif //COPASI_CAUTHOR
