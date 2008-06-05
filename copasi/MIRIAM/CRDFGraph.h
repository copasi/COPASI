// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraph.h,v $
//   $Revision: 1.23 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/05 15:34:56 $
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
#include <vector>
#include <set>

#include "copasi/MIRIAM/CRDFTriplet.h"

class CRDFNode;
class CRDFObject;
class CRDFSubject;
class CRDFEdge;

class CRDFGraph
  {
  public:
#ifdef XXXX
    class CTriplet
      {
      public:
        CRDFNode * pSubject;
        CRDFPredicate::ePredicateType Predicate;
        CRDFNode * pObject;

        CTriplet(CRDFNode * pSubject = NULL,
                 const CRDFPredicate::ePredicateType & predicate = CRDFPredicate::end,
                 CRDFNode * pObject = NULL);

        bool operator < (const CTriplet & rhs) const;
        bool operator ! () const;
      };
#endif // XXXX

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
     * Retrieve the map of prefixes to namespaces
     * @return const std::map< std::string, std::string > & nameSpaceMap
     */
    const std::map< std::string, std::string > & getNameSpaceMap() const;

    /**
     * Retrieve the map of IDs to blank nodes
     * @return const std::map< std::string, CRDFNode * > & blankNodeMap
     */
    const std::map< std::string, CRDFNode * > & getBlankNodeMap() const;

    /**
     * Retrieve the map of URIs to local resource nodes
     * @return const std::map< std::string, CRDFNode * > & localResourceNodeMap
     */
    const std::map< std::string, CRDFNode * > & getLocalResourceNodeMap() const;

    /**
     * Retreive the vector of remote resource nodes
     * @return const std::vector< CRDFNode * > & remoteResourceNodes
     */
    const std::vector< CRDFNode * > & getRemoteResourceNodes() const;

    /**
     * Guess the graph root element. If a unique root element is found
     * true is returned other wise falls
     * @return bool success
     */
    bool guessGraphRoot();

    /**
     * Add a name space including prefix to the graph. It returns false if the
     * prefix was already used with another namespace
     * @param const std::string & prefix
     * @param const std::string & namespace
     * @return bool success;
     */
    bool addNameSpace(const std::string & prefix, const std::string & uri);

    /**
     * Add a triplet to the graph
     * @param const CRDFSubject & subject
     * @param const std::string & predicate
     * @param const CRDFObject & object
     * @return CTriplet triplet
     */
    CRDFTriplet addTriplet(const CRDFSubject & subject,
                           const std::string & predicate,
                           const CRDFObject & object);

    /**
     * Remove triplet from the graph. Please note, this will also remove all unreferenced
     * local resources created by removing the edge.
     * @param bCRDFNode * pSubject
     * @param const std::string & predicate
     * @param const CRDFNode * pObject
     * @return bool success
     */
    bool removeTriplet(CRDFNode * pSubject,
                       const std::string & predicate,
                       const CRDFNode * pObject);

    /**
     * Destroy a CRDFNode
     * @param CRDFNode * pNode
     */
    void destroyNode(CRDFNode * pNode);

  private:
    /**
     * Remove triplet from the graph. Please note, this will also remove all unreferenced
     * local resources created by removing the edge.
     * @param CRDFNode * pNode
     * @param const CRDFEdge & Edge
     * @return bool success
     */
    bool removeTriplet(CRDFNode * pNode, const CRDFEdge & Edge);

  public:
    /**
     * Move a edge from one node to another
     * @param CRDFNode * pFrom
     * @param CRDFNode * pTo
     * @param const CRDFEdge & Edge
     * @return CRDFGraph::CTriplet triplet
     */
    CRDFTriplet moveEdge(CRDFNode * pFrom, CRDFNode * pTo, const CRDFEdge & Edge);

    /**
     * Retreive all triplets with the specified predicate
     * @param const CRDFPredicate::ePredicateType & predicate
     * @return std::set< CTriplet > triplets
     */
    std::set< CRDFTriplet > getTripletsWithPredicate(const CRDFPredicate::ePredicateType & predicate) const;

  public:
    /**
     * Retreive the predicate path to the ginve node.
     * @param const CRDFNode * pNode
     * @return CRDFPredicate::Path
     */
    CRDFPredicate::Path getPredicatePath(const CRDFNode * pNode);

  private:
    /**
     * Retreive the predicate path to the ginve node. The set visited should be empty on the initial call.
     * @param const CRDFNode * pNode
     * @param const CRDFNode * pCurrent
     * @param CRDFPredicate::Path & path
     * @param std::set< const CRDFNode * > & visited
     * @return bool found;
     */
    bool getPredicatePath(const CRDFNode * pNode,
                          const CRDFNode * pCurrent,
                          CRDFPredicate::Path & path,
                          std::set< const CRDFNode * > & visited);

  public:
    /**
     * Generate a unique blank node id.
     * @return std::string blankNodeId
     */
    std::string generatedBlankNodeId() const;

    /**
     * If no about node exists a node is created with the attribute:
     * rdf:about="#key
     * @param const std::string & key
     * @return CRDFNode * pAbout
     */
    CRDFNode * createAboutNode(const std::string & key);

    /**
     * Removes empty blank nodes and unused name space declarations.
     * This should be called before CRDFWriter::xmlFromGraph
     */
    void clean();

  private:
    /**
     * Removes all empty blank nodes. It returns true if a node was removed
     * @return bool haveRemoved
     */
    bool removeEmptyNodes();

    /**
     *  Removes all unused name spaces.
     */
    void removeUnusedNamespaces();

    /**
     * Recursively finds all used namespaces.
     */
    void findUsedNamespaces(const CRDFNode * pCurrent,
                            std::vector< bool > & used,
                            std::set< const CRDFNode * > & visited);

    // Attributes
  private:
    /**
     * The subject node this RDF graph is about
     */
    CRDFNode * mpAbout;

    /**
     * A map of prefixes to namespaces
     */
    std::map< std::string, std::string > mPrefix2Namespace;

    /**
     * A map of blank node ids to nodes of the graph.
     */
    std::map< std::string, CRDFNode * > mBlankNodeId2Node;

    /**
     * A map of resource URIs to local resource nodes of the graph, i
     */
    std::map< std::string, CRDFNode * > mLocalResource2Node;

    /**
     * A vector of all remote resource nodes of the graph
     */
    std::vector< CRDFNode * > mRemoteResourceNodes;

    /**
     * A vector of all literal nodes of the graph
     */
    std::vector< CRDFNode * > mLiteralNodes;
  };

#endif // COPASI_CRDFGraph
