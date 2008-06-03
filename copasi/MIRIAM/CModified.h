// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModified.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/03 13:20:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/**
 *  CModified: Stores Modification dates.
 */

#ifndef COPASI_CMODIFIED
#define COPASI_CMODIFIED

#include <string>

#include "copasi/MIRIAM/CRDFGraph.h"
#include "copasi/MIRIAM/CRDFPredicate.h"
#include "copasi/report/CCopasiContainer.h"

class CModification : public CCopasiContainer
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

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & objectName
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CModification(const std::string & objectName,
                  const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor
     * @param const CRDFGraph::CTriplet & triplet
     * @param const std::string & objectName (default: "")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CModification(const CRDFGraph::CTriplet & triplet,
                  const std::string & objectName = "",
                  const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CModification &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CModification(const CModification & src,
                  const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CModification();

    const CRDFGraph::CTriplet & getTriplet() const;

    virtual const std::string & getKey() const;

    void setDate(const std::string & date);

    const std::string & getDate() const;
  };

#endif //COPASI_CMODIFIED
