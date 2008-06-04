// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraph.h,v $
//   $Revision: 1.22 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/04 14:17:03 $
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

#include "copasi/MIRIAM/CRDFPredicate.h"

class CRDFNode;
class CRDFObject;
class CRDFSubject;
class CRDFEdge;

class CRDFGraph
  {
  public:
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
    CTriplet addTriplet(const CRDFSubject & subject,
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
    CTriplet moveEdge(CRDFNode * pFrom, CRDFNode * pTo, const CRDFEdge & Edge);

    /**
     * Retreive all triplets with the specified predicate
     * @param const CRDFPredicate::ePredicateType & predicate
     * @return std::set< CTriplet > triplets
     */
    std::set< CTriplet > getTripletsWithPredicate(const CRDFPredicate::ePredicateType & predicate) const;

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
     * Add a child node to a table node.
     * @param const std::string tableName
     * @param const CRDFObject& childObj
     */
    // void addRecordToTable(const std::string& tableName, const CRDFObject& childObj);

    /**
     * Remove a child node from a table node.
     * Both are assumed to be Blank nodes.
     * @param const std::string tableName
     * @param const CRDFObject& childObj
     * @return std::string success
     */
    // bool removeRecordFromTable(const std::string& tableName, const CRDFObject& childObj);

    /**
     * Get all objects corresponding to a given
     * table name.
     * @param const std::string& tableName
     * @param std::vector<std::string> & nodeIds
     * @return bool success
     */
    // bool getNodeIDsForTable(const std::string& tableName, std::vector<CRDFObject>& objects);

    /**
     *Get the value of the field for a given fieldName.
     * @param const std::string& fieldName
     * @param const CRDFObject& obj
     * @return std::string fieldValue
     */
    // std::string getFieldValue(const std::string& fieldName, const CRDFObject& obj);

    /**
     *Set the value of the field for a given fieldName.
     * @param const std::string& fieldName
     * @param const std::string& fieldValue
    * @param CRDFObject& obj
     * @return std::string success
     */
    // bool setFieldValue(const std::string& fieldName, CRDFObject& obj, const std::string& fieldValue);

    // CRDFGraph* loadGraph(CCopasiObject* pEntity);
    // bool saveGraph(CCopasiObject* pEntity);
    // bool isChanged();

    // Attributes
  private:
    /**
     * The subject node this RDF graph is about
     */
    CRDFNode * mpAbout;

    /**Flag to track if the original graph changed from last save.*/
    bool mChanged;

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
