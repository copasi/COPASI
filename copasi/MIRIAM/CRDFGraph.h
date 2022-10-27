// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRDFGraph
#define COPASI_CRDFGraph

#include <map>
#include <vector>
#include <set>

#include "copasi/MIRIAM/CRDFTriplet.h"
#include "copasi/MIRIAM/CRDFNode.h"

class CRDFObject;
class CRDFSubject;

class CRDFGraph
{
public:
  typedef std::set< CRDFTriplet >::iterator iterator;
  typedef std::set< CRDFTriplet >::const_iterator const_iterator;

  typedef std::multimap< CRDFNode *, CRDFTriplet > Node2Triplet;
  typedef std::pair< Node2Triplet::iterator, Node2Triplet::iterator> Node2TripletRange;
  typedef std::pair< Node2Triplet::const_iterator, Node2Triplet::const_iterator> Node2TripletConstRange;

  typedef std::multimap< CRDFPredicate, CRDFTriplet > Predicate2Triplet;
  typedef std::pair< Predicate2Triplet::iterator, Predicate2Triplet::iterator> Predicate2TripletRange;
  typedef std::pair< Predicate2Triplet::const_iterator, Predicate2Triplet::const_iterator> Predicate2TripletConstRange;

  // Operations
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
   * Retrieve the vector of remote resource nodes
   * @return const std::vector< CRDFNode * > & remoteResourceNodes
   */
  const std::vector< CRDFNode * > & getRemoteResourceNodes() const;

  /**
   * Guess the graph root element. If a unique root element is found
   * true is returned other wise falls
   * @param const std::string & about (default: <space>)
   * @return bool success
   */
  bool guessGraphRoot(const std::string & about = " ");

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
   * @param const CRDFPredicate & predicate
   * @param const CRDFObject & object
   * @return CRDFTriplet triplet
   */
  CRDFTriplet addTriplet(const CRDFSubject & subject,
                         const CRDFPredicate & predicate,
                         const CRDFObject & object);

private:
  /**
   * Add a triplet to the graph. This method should only be used by CRDFNode
   * @param const CRDFTriplet & triplet
   * @return bool success
   */
  bool addTriplet(const CRDFTriplet & triplet);
  friend bool CRDFNode::addTripletToGraph(const CRDFTriplet & triplet) const;

public:
  /**
   * Remove triplet from the graph. Please note, this will also remove all unreferenced
   * local resources created by removing the edge.
   * @param CRDFNode * pSubject
   * @param const CRDFPredicate & predicate
   * @param CRDFNode * pObject
   * @return true, if an element was deleted, false otherwise
   */
  bool removeTriplet(CRDFNode * pSubject,
                     const CRDFPredicate & predicate,
                     CRDFNode * pObject);

  /**
   * Destroy a CRDFNode
   * @param CRDFNode * pNode
   * @return true, if an element was deleted, false otherwise
   */
  bool destroyUnreferencedNode(CRDFNode * pNode);

private:
  /**
   * Remove triplet from the graph. This method should only be used by CRDFNode
   * Please note, this will also remove all unreferenced
   * local resources created by removing the edge.
   * @param const CRDFTriplet & triplet
   * @return true, if an element was deleted, false otherwise
   */
  bool removeTriplet(const CRDFTriplet & triplet);
  friend bool CRDFNode::removeTripletFromGraph(const CRDFTriplet & triplet) const;

public:
  /**
   * Move a edge from one node to another
   * @param CRDFNode * pNewSubject
   * @param CRDFNode * const CRDFTriplet & triplet
   * @return CRDFGraph::CRDFTriplet triplet
   */
  CRDFTriplet moveTriplet(CRDFNode * pNewSubject, const CRDFTriplet & triplet);

  /**
   * Retrieve all triplets.
   * @return const std::set< CRDFTriplet > & triplets
   */
  const std::set< CRDFTriplet > & getTriplets() const;

  /**
   * Retrieve all triplets with the specified predicate, this will collapse
   * predicate.rdf:li to predicate.
   * @param const CRDFPredicate & predicate
   * @param const bool & expandBag (default: true)
   * @return std::set< CRDFTriplet > triplets
   */
  std::set< CRDFTriplet > getTriplets(const CRDFPredicate & predicate,
                                      const bool & expandBag = true) const;

  /**
   * Retrieve all triplets with the specified subject
   * @param const CRDFNode * pSubject
   * @return std::set< CRDFTriplet > triplets
   */
  std::set< CRDFTriplet > getTriplets(const CRDFNode * pSubject) const;

  /**
   * Retrieve all triplets with the specified subject and predicate
   * @param const CRDFNode * pSubject
   * @param const CRDFPredicate & predicate
   * @return std::set< CRDFTriplet > triplets
   */
  std::set< CRDFTriplet > getTriplets(const CRDFNode * pSubject,
                                      const CRDFPredicate & predicate) const;

  /**
   * Retrieve all triples pointing to the object
   * @param const CRDFNode * pObject
   * @return std::set< CRDFTriplet > triplets
   */
  std::set< CRDFTriplet > getIncomingTriplets(const CRDFNode * pObject) const;

  /**
   * Retrieve all parent subjects of the object
   * @param const CRDFNode * pObject
   * @return std::set< const CRDFNode * > nodes
   */
  std::set< const CRDFNode * > getParentSubjects(const CRDFNode * pObject) const;

  /**
   * Retrieve the predicate path to the ginve node.
   * @param const CRDFNode * pNode
   * @return CRDFPredicate::Path
   */
  CRDFPredicate::Path getPredicatePath(const CRDFNode * pNode);

public:
  /**
   * Generate a unique blank node id.
   * @param const std::string & existingId (default: "")
   * @return std::string blankNodeId
   */
  std::string generatedNodeId(const std::string & existingId = "");

  /**
   * If no about node exists a node is created with the attribute:
   * rdf:about="#key
   * @param const std::string & key
   * @return CRDFNode * pAbout
   */
  CRDFNode * createAboutNode(const std::string & key);

  /**
   * Removes empty blank nodes .
   * This should be called before CRDFWriter::xmlFromGraph
   */
  void clean();

  /**
   *  Removes all unused name spaces.
   */
  void updateNamespaces();

  /**
   * Check whether the graph is empty
   * bool empty
   */
  bool empty() const;

private:
  /**
   * Removes all empty blank nodes. It returns true if a node was removed
   * @return bool haveRemoved
   */
  bool removeEmptyNodes();

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

  /**
   * All the triplets of the graph
   */
  std::set< CRDFTriplet > mTriplets;

  /**
   *
   */
  Node2Triplet mSubject2Triplet;

  /**
   *
   */
  Node2Triplet mObject2Triplet;

  /**
   *
   */
  Predicate2Triplet mPredicate2Triplet;

  /**
   * Memory for generated Ids
   */
  std::set< unsigned int > mGeneratedIds;

  /**
   * Mapping from existing Ids to newly created ones.
   */
  std::map< std::string, std::string > mIdMap;
};

#endif // COPASI_CRDFGraph
