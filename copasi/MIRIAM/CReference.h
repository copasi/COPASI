// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CReference.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/01 18:08:05 $
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
     * The key of the object needed for the copasi tables.
     */
    std::string mKey;

    /**
     * MIRIAM resource for holding the PubMed Id
     */
    CMIRIAMResourceObject mPubMed;

    /**
     * MIRIAM resource for holding the DOI
     */
    CMIRIAMResourceObject mDOI;

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

    const std::string & getPubmedId() const;

    const std::string & getDOI() const;

    const std::string & getDescription() const;

    void setPubmedId(const std::string &pubmedId);

    void setDOI(const std::string & DOI);

    void setDescription(const std::string & description);
  };

#endif //COPASI_CReference
