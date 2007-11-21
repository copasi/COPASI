// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraph.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/21 16:15:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRDFGraph
#define COPASI_CRDFGraph

#include <map>

#include "MIRIAM/CRDFNode.h"

class CRDFGraph
  {
    // Operations
  public:
    /**
     * Default Constructor
     */
    CRDFGraph();

    /**
     * Destructor
     */
    ~CRDFGraph();

    /**
     * Add a triplet to the graph
     * @param const CRDFSubject & subject
     * @param const std::string & predicate
     * @param const CRDFObject & object
     * @return bool success
     */
    bool addTriplet(const CRDFSubject & subject,
                    const std::string & predicate,
                    const CRDFObject & object);

    // Attributes
  private:
    /**
     * The subject node this RDF graph is about
     */
    CRDFNode * mpAbout;

    /**
     * A map of blank node ids to nodes in the graph.
     */
    std::map< std::string, CRDFNode * > mBlankNodeId2Node;

    /**
     * A map of resource URIs to nodes in the graph
     */
    std::map< std::string, CRDFNode * > mResource2Node;

    /**
     * A vector of all literal nodes of the graph
     */
    std::vector< CRDFNode * > mLiteralNodes;
  };

#endif // COPASI_CRDFGraph
