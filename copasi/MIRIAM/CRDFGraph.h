// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraph.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/01/29 15:43:44 $
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
#include "MIRIAM/CRDFObject.h"

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
     * Add a triplet to the graph
     * @param const CRDFSubject & subject
     * @param const std::string & predicate
     * @param const CRDFObject & object
     * @return bool success
     */
    bool addTriplet(const CRDFSubject & subject,
                    const std::string & predicate,
                    const CRDFObject & object);

    /**
     * Get IDs of all nodes corresponding to a given
     * table name.
     * @param const std::string tableName
     * @param std::vector<std::string> & nodeIds
     * @param std::string & tableNodeID
        * @return bool success
     */
    bool getNodeIDsForTable(const std::string& tableName, std::vector<std::string>& nodeIds, std::string& tableNodeID);

    /**
     *Get the value of the field for a given fieldName.
     * @param const std::string& fieldName
     * @param const std::string& graphNodeID
        * @return std::string fieldValue
     */
    std::string CRDFGraph::getFieldValue(const std::string& fieldName, const std::string& graphNodeId);

    /**
     *Set the value of the field for a given fieldName.
     * @param const std::string& fieldName
     * @param const std::string& fieldValue
     * @param const std::string& graphNodeID
        * @return std::string success
     */
    bool setFieldValue(const std::string& fieldName, const std::string& graphNodeId, const std::string& fieldValue);

    /**
     * Add a child node to a table node.
      * @param const std::string tableName
     * @param std::string tableNodeID
     * @param const std::string childNodeID
     */
    void addObjectToTable(const std::string& tableName, std::string& tableNodeID, const std::string& childNodeID);

    /**
     * Remove a child node from a table node.
     * Both are assumed to be Blank nodes.
      * @param const std::string tableName
     * @param std::string tableNodeID
     * @param const std::string childNodeID
     * @return std::string success
     */
    bool removeObjectFromTable(const std::string& tableName, std::string& tableNodeID, const std::string& childNodeID);

    /**
     * Add a Bag node to a table node.
     * @param const std::string tableName
     * @param const std::string & tableGraphID
     * @return std::string success
     */
    bool addBagNodeToTable(const std::string& tableName, std::string& tableGraphID);

    /**
     * Remove a Bag node from a table node.
     * @param const std::string tableName
     * @param const std::string & tableGraphID
     * @return std::string success
     */
    bool removeBagNodeFromTable(const std::string& tableName, std::string& tableGraphID);

    bool printGraph();

    // Attributes
  private:
    /**
     * The subject node this RDF graph is about
     */
    CRDFNode * mpAbout;

    /**
     * A map of blank node ids to nodes of the graph.
     */
    std::map< std::string, CRDFNode * > mBlankNodeId2Node;

    /**
     * A map of resource URIs to local resource nodes of the graph
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

    static unsigned int nodeIDCounter;

  protected:
    void addNewCreatorNodes(const CRDFNode * pObjNode);
    std::string getNameSpaceURI(const std::string& lookupStr);
    std::string fieldName2Predicate(const std::string& fieldName);
    std::string tableName2Predicate(const std::string& tableName);
    CRDFNode* getNodeForPredicate(const std::string& predicate, const CRDFNode * startNode = NULL);
    bool removeNode(const std::string& nodeIdOrResourceOrLiteral, CRDFObject::eObjectType nodeType = CRDFObject::BLANK_NODE);
    bool isBagNode(const CRDFNode * pNode);
    std::string getGeneratedId();
    unsigned int getNoOfObjectsInTable(const CRDFNode * pTableNode);
  };

#endif // COPASI_CRDFGraph
