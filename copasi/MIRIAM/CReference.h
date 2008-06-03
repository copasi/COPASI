// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CReference.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/03 13:20:02 $
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
    CRDFGraph::CTriplet mTriplet;

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
    CMIRIAMResource mPubMed;

    /**
     * MIRIAM resource for holding the DOI
     */
    CMIRIAMResource mDOI;

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
     * @param const CRDFGraph::CTriplet & triplet
     * @param const std::string & objectName (default: "")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CReference(const CRDFGraph::CTriplet & triplet,
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

    const CRDFGraph::CTriplet & getTriplet() const;

    virtual const std::string & getKey() const;

    const std::string & getPubmedId() const;

    const std::string & getDOI() const;

    const std::string & getDescription() const;

    void setPubmedId(const std::string &pubmedId);

    void setDOI(const std::string & DOI);

    void setDescription(const std::string & description);
  };

#endif //COPASI_CReference
