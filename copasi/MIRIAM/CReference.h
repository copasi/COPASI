// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CReference.h,v $
//   $Revision: 1.6.4.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/25 16:49:07 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CReference
#define COPASI_CReference

#include <string>

#include "copasi/MIRIAM/CRDFGraph.h"
#include "copasi/MIRIAM/CRDFPredicate.h"
#include "copasi/MIRIAM/CConstants.h"

#include "copasi/report/CCopasiContainer.h"

/**
 *  CReferences: Stores publication details such as PubMed Id and DOI.
 */
class CReference : public CCopasiContainer
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

    /**
     * Triplet in the RDF graph representing the reference.
     */
    CRDFTriplet mIdTriplet;

    /**
     * MIRIAM resource for holding database and Id.
     */
    CMIRIAMResourceObject mResource;

  public:
    // Operations
    /**
     * Default constructor
     * @param const std::string & objectName
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CReference(const std::string & objectName,
               const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor
     * @param const CRDFTriplet & triplet
     * @param const std::string & objectName (default: "")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CReference(const CRDFTriplet & triplet,
               const std::string & objectName = "",
               const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CReference &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CReference(const CReference & src,
               const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CReference();

    /**
     * Retrieve the RDF triplet holding the information for this reference.
     * @return const CRDFTriplet & triplet
     */
    const CRDFTriplet & getTriplet() const;

    /**
     * Retrieve the key for the object
     * @return const std::string & key
     */
    virtual const std::string & getKey() const;

    /**
     * Retrieve the MIRIAM resource for the reference.
     * @return std::string resource
     */
    std::string getResource() const;

    /**
     * Retrieve the id of the reference in the MIRIAM resource.
     * @return const std::string & id
     */
    const std::string & getId() const;

    /**
     * Retrieve the description for the reference.
     * @return std::string description
     */
    const std::string & getDescription() const;

    /**
     * Retrieve the URI (comprised of resource an id) specifying this reference.
     * @return std::string uri
     */
    std::string getURI() const;

    /**
     * Set the MIRIAM resource for the reference
     * @param const std::string & resource
     */
    void setResource(const std::string & resource);

    /**
     * Set the id of the reference in the MIRIAM resource.
     * @param const std::string & id
     */
    void setId(const std::string & id);

    /**
     * Set the description for the reference.
     * @param std::string description
     */
    void setDescription(const std::string & description);

    /**
     * Remove invalid combinations of resource and id
     */
    void clearInvalidEntries();
  };

#endif //COPASI_CReference
