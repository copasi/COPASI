// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CCreator.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/07/11 16:05:18 $
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

#include "copasi/MIRIAM/CRDFGraph.h"
#include "copasi/MIRIAM/CRDFPredicate.h"

#include "copasi/report/CCopasiContainer.h"

class CCreator : public CCopasiContainer
  {
    // Attributes
  private:
    /**
     * Triplet in the RDF graph representing the reference.
     */
    CRDFTriplet mTriplet;

    /**
     * The predicate path to the node.
     */
    CRDFPredicate::Path mNodePath;

    /**
     * The key of the object needed for the COPASI tables.
     */
    std::string mKey;

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & objectName
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCreator(const std::string & objectName,
             const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor
     * @param const CRDFTriplet & triplet
     * @param const std::string & objectName (default: "")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCreator(const CRDFTriplet & triplet,
             const std::string & objectName = "",
             const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CCreator & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCreator(const CCreator & src,
             const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CCreator();

    const CRDFTriplet & getTriplet() const;

    virtual const std::string & getKey() const;

    /**
     *  Add the given name to Last name to get the full Name.
     */
    const std::string & getFamilyName() const;

    const std::string & getGivenName() const;

    const std::string & getEmail() const;

    const std::string & getORG() const;

    void setFamilyName(const std::string & familyName);

    void setGivenName(const std::string & givenName);

    void setEmail(const std::string & Email);

    void setORG(const std::string & Orgname);
  };

#endif //COPASI_CCreator
