/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/Tree.h,v $
   $Revision: 1.17.2.4 $
   $Name:  $
   $Author: shoops $
   $Date: 2010/09/27 17:49:37 $
   End CVS Header */

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 **  $ CopasiUI/Tree.h                 Modified on : 8th March, 2002
 **  $ Author  : Ankur Gupta
 **
 **  This file is a template code for tree generation.
 **  The tree that is generated through this code is a general tree with any numbers of
 **  childrens for a given node at any level.
 **
 **
 *****************************************************************************/

#ifndef TREE_H
#define TREE_H

/*********************************************************
 ** This class is a template class for the node that will
 ** hold informations such as the information and the
 ** links to its child,sibling and parent
 **
 ** The information can be in turn any object that the user
 ** wants to store
 *********************************************************/
#include <vector>
#include <string>
#include <qstring.h>
#include <limits>

#ifndef C_INVALID_INDEX
#define C_INVALID_INDEX (std::numeric_limits< size_t >::max())
#endif

class IndexedTree;

class IndexedNode
{
public:
  IndexedNode(size_t id = C_INVALID_INDEX, const QString & name = "",
              const std::string & key = "", const IndexedNode* pParentNode = NULL);

  IndexedNode(const IndexedNode & src, const IndexedNode* pParentNode = NULL);

private:
  IndexedNode & operator=(const IndexedNode&);

public:
  ~IndexedNode(); // destructor

  const std::vector<IndexedNode*>& children() const;

  void removeChildren();

  bool removeChild(const std::string & key);

  void addChild(size_t id, const QString & name, const std::string & key);

  size_t getId() const;

  //contents methods
  const QString & getName() const;
  void setName(const QString & name);
  const std::string & getObjectKey() const;
  void setObjectKey(const std::string & key);

  const QString & getSortKey() const;

  IndexedNode *child(int row);
  int childCount() const;
  int columnCount() const;
  int row() const;
  int column() const;
  const IndexedNode * parent() const;

private:
  size_t mId;
  const IndexedNode * mpParentNode;
  QString mSortKey;

  std::vector<IndexedNode*> mChildren;

  //contents
  QString mName;
  std::string mObjectKey;

  friend class IndexedTree;
};

//template <class T>
class IndexedTree
{
private:
  IndexedNode root; // declares the head of the tree

  IndexedNode * findNodeFromId(IndexedNode & node, size_t id) const;

  IndexedNode * findNodeFromKey(IndexedNode & node, const std::string& key) const;


public :

  IndexedTree();

  ~IndexedTree() {};

  void add(size_t parentId, size_t newId, const QString & name, const std::string & key);

  IndexedNode * findNodeFromId(size_t id);

  IndexedNode * findNodeFromKey(const std::string& key);

  IndexedNode * getRoot() {return &root;};
  const IndexedNode * getRoot() const {return &root;};
};

#endif
