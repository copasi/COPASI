// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraph.h,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/14 22:57:12 $
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
     * @return bool success
     */
    bool addTriplet(const CRDFSubject & subject,
                    const std::string & predicate,
                    const CRDFObject & object);

    /**
     * Get all objects corresponding to a given
     * table name.
     * @param const std::string& tableName
     * @param std::vector<std::string> & nodeIds
     * @param CRDFObject& tableObj
        * @return bool success
     */
    bool getNodeIDsForTable(const std::string& tableName, std::vector<CRDFObject>& objects, CRDFObject& tableObj);

    /**
     *Get the value of the field for a given fieldName.
     * @param const std::string& fieldName
     * @param const CRDFObject& obj
     * @return std::string fieldValue
     */
    std::string getFieldValue(const std::string& fieldName, const CRDFObject& obj);

    /**
     *Set the value of the field for a given fieldName.
     * @param const std::string& fieldName
     * @param const std::string& fieldValue
    * @param CRDFObject& obj
    * @param const bool& isResource
     * @return std::string success
     */
    bool setFieldValue(const std::string& fieldName, CRDFObject& obj, const std::string& fieldValue);

    /**
     * Add a child node to a table node.
     * @param const std::string tableName
     * @param CRDFObject& tableObj
     * @param const CRDFObject& childObj
     */
    void addRecordToTable(const std::string& tableName, CRDFObject& tableObj, const CRDFObject& childObj);

    /**
     * Remove a child node from a table node.
     * Both are assumed to be Blank nodes.
     * @param const std::string tableName
     * @param CRDFObject& tableObj
     * @param const CRDFObject& childObj
     * @return std::string success
     */
    bool removeRecordFromTable(const std::string& tableName, CRDFObject& tableObj, const CRDFObject& childObj);

    /**
    * Remove all empty Nodes from the graph;
    */
    void compressGraph();

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
    /**
        * Add a Bag node to a table node.
        * @param const std::string tableName
        * @param CRDFObject& tableObj
        * @return std::string success
        */
    bool addBagNodeToTable(const std::string& tableName, CRDFObject& tableObj);

    /**
     * Remove a Bag node from a table node.
     * @param const std::string tableName
     * @param CRDFObject& tableObj
     * @return std::string success
     */
    bool removeBagNodeFromTable(const std::string& tableName, CRDFObject& tableObj);

    void addObjectToBagNode(const std::string& tableName, CRDFNode* pTableNode, const CRDFObject& object);
    void buildCreatorRecord(const CRDFNode * pObjNode);
    void buildPublicationRecord(const CRDFNode * pObjNode);
    std::string getNameSpaceURI(const std::string& lookupStr);
    CRDFNode* findNodeFromObject(const CRDFObject& object);
    CRDFNode* findFieldNodeFromObject(const std::string& fieldName, const CRDFObject& obj);
    std::string fieldName2Predicate(const std::string& fieldName);
    std::string tableName2Predicate(const std::string& tableName);
    CRDFNode* getNodeForPredicate(const std::string& predicate, const CRDFNode * startNode = NULL);
    bool removeNode(CRDFNode * pNode);

    /**
    * Remove all nodes with empty values at
    * and below this node.
    * @param CRDFNode* pNode The node to compress
    * @return bool success
    */
    bool compressNode(CRDFNode* pNode);

    bool isBagNode(const CRDFNode * pNode);
    std::string getGeneratedId();
    unsigned int getNoOfObjectsInTable(const CRDFNode * pTableNode);
  };

#endif // COPASI_CRDFGraph
