// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraph.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/15 17:45:38 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
     * Retrieve the about/top node of the graph.
     * @return const CRDFNode * pAboutNode
     */
    const CRDFNode * getAboutNode() const;

    /**
     * Retrieve the map of IDs to blank nodes
     * @return const std::map< std::string, CRDFNode * > & blankNodeMap
     */
    const std::map< std::string, CRDFNode * > & getBlankNodeMap() const;

    /**
     * Retrieve the map of URIs to resource nodes
     * @return const std::map< std::string, CRDFNode * > & resourceNodeMap
     */
    const std::map< std::string, CRDFNode * > & getResourceNodeMap() const;

    /**
     * Guess the graph root element. If a unique root element is found
     * true is returned other wise falls
     * @return bool success
     */
    bool guessGraphRoot();

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
