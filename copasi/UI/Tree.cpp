/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/Tree.cpp,v $
  $Revision: 1.9.2.4 $
  $Name:  $
  $Author: shoops $
  $Date: 2010/09/29 15:51:31 $
  End CVS Header */

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <assert.h>
#include <iostream>

#include "copasi.h"

#include "Tree.h"

IndexedNode::IndexedNode(size_t id, const QString & name, const std::string & key,
                         const IndexedNode* pParentNode):
    mId(id),
    mpParentNode(pParentNode),
    mSortKey(),
    mChildren(),
    mName(name),
    mObjectKey(key)
{
  if (mId != C_INVALID_INDEX)
    {
      mSortKey.setNum(id);
      mSortKey += "_" + mName;
    }
  else
    {
      mSortKey = mName;
    }
};

IndexedNode::IndexedNode(const IndexedNode & src,
                         const IndexedNode* pParentNode):
    mId(src.mId),
    mpParentNode(pParentNode),
    mSortKey(src.mSortKey),
    mChildren(),
    mName(src.mName),
    mObjectKey(src.mObjectKey)
{
  std::cout << "IndexedNode copy constructor called" << std::endl;

  std::vector<IndexedNode*>::const_iterator it, itEnd = src.mChildren.end();

  for (it = src.mChildren.begin(); it != itEnd; ++it)
    mChildren.push_back(new IndexedNode(**it, this));

};

IndexedNode::~IndexedNode()
{
  removeChildren();
}; // destructor

//const std::vector<IndexedNode>& IndexedNode::children() const
//  {returen mChildren;};

void IndexedNode::removeChildren()
{
  std::vector<IndexedNode*>::iterator it, itEnd = mChildren.end();

  for (it = mChildren.begin(); it != itEnd; ++it)
    delete *it;

  mChildren.clear();
}

bool IndexedNode::removeChild(const std::string & key)
{
  std::vector<IndexedNode*>::iterator it, itEnd = mChildren.end();

  for (it = mChildren.begin(); it != itEnd; ++it)
    {
      if ((*it)->getObjectKey() == key)
        {
          delete *it;
          mChildren.erase(it);
          return true;
        }
    }

  return false;
}

void IndexedNode::addChild(size_t id, const QString & name, const std::string & key)
{
  mChildren.push_back(new IndexedNode(id, name, key, this));
}

size_t IndexedNode::getId() const {return mId;};

//contents methods
const QString & IndexedNode::getName() const {return mName;};

void IndexedNode::setName(const QString & name)
{
  mName = name;
  mSortKey.setNum(mId);
  mSortKey += "_" + name;
}

const std::string & IndexedNode::getObjectKey() const {return mObjectKey;}

void IndexedNode::setObjectKey(const std::string & key) {mObjectKey = key;}

const QString & IndexedNode::getSortKey() const
{
  return mSortKey;
}

const std::vector<IndexedNode*> & IndexedNode::children() const
{return mChildren;};

//*************  Tree *******************

IndexedTree::IndexedTree()
{
  root.mId = C_INVALID_INDEX;
}

void IndexedTree::add(size_t parentId, size_t newId, const QString & name, const std::string & key)
{
  IndexedNode * parent = findNodeFromId(parentId);
  parent->addChild(newId, name, key);
}

IndexedNode * IndexedTree::findNodeFromId(size_t id)
{
  IndexedNode * tmp = findNodeFromId(root, id);
  //assert(tmp != NULL);

  return tmp;
}

IndexedNode * IndexedTree::findNodeFromId(IndexedNode & node, size_t id) const
{
  if (node.getId() == id)
    return &node;

  const std::vector<IndexedNode*> & children = node.children();
  std::vector<IndexedNode*>::const_iterator it, itEnd = children.end();

  IndexedNode * tmp;

  for (it = children.begin(); it != itEnd; ++it)
    {
      tmp = findNodeFromId(**it, id);

      if (tmp) return tmp;
    }

  return NULL;
}

IndexedNode * IndexedTree::findNodeFromKey(const std::string& key)
{
  IndexedNode * tmp = findNodeFromKey(root, key);
  return tmp;
}

IndexedNode * IndexedTree::findNodeFromKey(IndexedNode & node, const std::string& key) const
{
  if (key == "")
    return NULL;

  if (node.getObjectKey() == key)
    return &node;

  const std::vector<IndexedNode*> & children = node.children();
  std::vector<IndexedNode*>::const_iterator it, itEnd = children.end();

  IndexedNode * tmp;

  for (it = children.begin(); it != itEnd; ++it)
    {
      tmp = findNodeFromKey(**it, key);

      if (tmp) return tmp;
    }

  return NULL;
}

IndexedNode* IndexedNode::child(int row)
{
  return mChildren[row];
}

int IndexedNode::childCount() const
{
  return mChildren.size();
}

int IndexedNode::columnCount() const
{
  return 1;
}

const IndexedNode *IndexedNode::parent() const
{
  return mpParentNode;
}

int IndexedNode::row() const
{
  if (mpParentNode)
    {
      const std::vector<IndexedNode*> & children = mpParentNode->children();
      std::vector<IndexedNode*>::const_iterator it, itEnd = children.end();

      int i = 0;

      for (it = children.begin(); it != itEnd; ++it, i++)
        {
          if (*it  == this)
            return i;
        }
    }

  return -1;
}

int IndexedNode::column() const
{
  return (columnCount() - 1);
}
