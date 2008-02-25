// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CCreator.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/25 20:37:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/**
 *  CCreators: Stores author name, email and other (vCard) details.
 *
 *
 */

#ifndef COPASI_CCreator
#define COPASI_CCreator

#include <string>

#include "report/CCopasiContainer.h"

#include "CRDFObject.h"

class CCreator : public CCopasiContainer
  {
    // Attributes
  private:

    std::string mKey;

    /** Object in RDF Graph corresponding to this Creator.*/
    CRDFObject* mpRDFObj;

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & objectName
     * @param CRDFObject * pRDFObj
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCreator(const std::string & objectName, const CCopasiContainer * pParent = NULL,
             CRDFObject * pRDFObj = NULL);

    /**
     * Copy constructor
     * @param "const CCreator &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCreator(const CCreator & src,
             const CCopasiContainer * pParent = NULL);

    ~CCreator();
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

    CRDFObject& getRDFObject();

    const std::string getObjectName() const;
    bool setObjectName(const std::string & name);

    /**
        *  Returns a string with the name of this Creator.
        *  @return std::string key
        */
    virtual const std::string & getKey() const;
  };

#endif //COPASI_CCreator
