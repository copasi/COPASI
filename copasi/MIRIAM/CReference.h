// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CReference.h,v $
//   $Revision: 1.6.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/10/27 13:55:41 $
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

    const CRDFTriplet & getTriplet() const;

    virtual const std::string & getKey() const;

    std::string getResource() const;

    const std::string & getId() const;

    const std::string & getDescription() const;

    std::string getURI() const;

    void setResource(const std::string & resource);

    void setId(const std::string & id);

    void setDescription(const std::string & description);
  };

#endif //COPASI_CReference
