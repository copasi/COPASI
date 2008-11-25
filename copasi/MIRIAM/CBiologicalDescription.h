// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CBiologicalDescription.h,v $
//   $Revision: 1.5.4.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/25 16:49:07 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CBiologicalDescription
#define COPASI_CBiologicalDescription

#include <string>

#include "copasi/MIRIAM/CRDFGraph.h"
#include "copasi/MIRIAM/CRDFPredicate.h"
#include "copasi/MIRIAM/CConstants.h"

#include "copasi/report/CCopasiContainer.h"

class CBiologicalDescription : public CCopasiContainer
  {
    // Attributes
  private:
    /**
     * Triplet in the RDF graph representing the description.
     */
    CRDFTriplet mTriplet;

    /**
     * The key of the object needed for the COPASI tables.
     */
    std::string mKey;

    /**
     * MIRIAM resource for holding the database and Id.
     */
    CMIRIAMResourceObject mResource;

  public:
    // Operations
    /**
     * Default constructor
     * @param const std::string & objectName
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CBiologicalDescription(const std::string & objectName,
                           const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor
     * @param const CRDFTriplet & triplet
     * @param const std::string & objectName (default: "")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CBiologicalDescription(const CRDFTriplet & triplet,
                           const std::string & objectName = "",
                           const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CBiologicalDescription &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CBiologicalDescription(const CBiologicalDescription & src,
                           const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CBiologicalDescription();

    /**
     * Retrieve the RDF triplet holding the description.
     * @return const CRDFTriplet & triplet
     */
    const CRDFTriplet & getTriplet() const;

    /**
     * Retrieve the key of the object.
     * @return const std::string & key
     */
    virtual const std::string & getKey() const;

    /**
     * Retrieve the predicate, i.e. the relationship between the subject.
     * and the MIRIAM resource.
     * @return std::string predicate
     */
    std::string getPredicate() const;

    /**
     * Retrieve the MIRIAM resource (database) describing the subject.
     * @return std::string resource
     */
    std::string getResource() const;

    /**
     * Retrieve the identifier of the subject in the MIRIAM resource.
     * @return const std::string id
     */
    const std::string & getId() const;

    /**
     * Retrieve the URI comprised of MIRIAM resource and id.
     * @return std::string uri
     */
    std::string getURI() const;

    /**
     * Set the predicate, i.e., relationship between the subject and the
     * MIRIAM resource.
     * @param const std::string & predicate
     */
    void setPredicate(const std::string & predicate);

    /**
     * Set the MIRIAM resource (database) describing the subject.
     * @param const std::string & predicate
     */
    void setResource(const std::string & resource);

    /**
     * Set the identifier of the subject in the MIRIAM resource.
     * @param const std::string & id
     */
    void setId(const std::string & id);

    /**
     * Convenience method removing invalid predicate, resource, and id combinations
     */
    void clearInvalidEntries();
  };

#endif //COPASI_CBiologicalDescription
