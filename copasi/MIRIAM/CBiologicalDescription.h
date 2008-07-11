// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CBiologicalDescription.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/07/11 16:05:18 $
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
     * MIRIAM resource for holding the PubMed Id
     */
    CMIRIAMResource mResource;

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

    const CRDFTriplet & getTriplet() const;

    virtual const std::string & getKey() const;

    std::string getPredicate() const;

    std::string getResource() const;

    const std::string & getId() const;

    void setPredicate(const std::string & predicate);

    void setResource(const std::string & resource);

    void setId(const std::string & id);
  };

#endif //COPASI_CBiologicalDescription
