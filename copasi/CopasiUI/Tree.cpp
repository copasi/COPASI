/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/Tree.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/11/10 16:03:06 $
   End CVS Header */

#include <assert.h>

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"

#include "Tree.h"

IndexedNode::IndexedNode(int id, const QString & name, const std::string & key)
    : mId(id), mName(name), mObjectKey(key)
{
  mSortKey.setNum(id);
  mSortKey += "_" + name;
  CONSTRUCTOR_TRACE;
};

IndexedNode::IndexedNode(const IndexedNode & src):
    mId(src.mId),
    mSortKey(src.mSortKey),
    mChildren(src.mChildren),
    mName(src.mName),
    mObjectKey(src.mObjectKey)
{
  CONSTRUCTOR_TRACE;
};

IndexedNode::~IndexedNode()
{
  DESTRUCTOR_TRACE;
}; // destructor

const std::vector<IndexedNode>& IndexedNode::children() const
  {return mChildren;};

void IndexedNode::removeChildren()
{mChildren.resize(0);};

void IndexedNode::addChild(int id, const QString & name, const std::string & key)
{mChildren.push_back(IndexedNode(id, name, key));};

int IndexedNode::getId() const {return mId;};

//contents methods
const QString & IndexedNode::getName() const {return mName;};
void IndexedNode::setName(const QString & name)
{
  mName = name;
  mSortKey.setNum(mId);
  mSortKey += "_" + name;
};
const std::string & IndexedNode::getObjectKey() const {return mObjectKey;};
void IndexedNode::setObjectKey(const std::string & key) {mObjectKey = key;};

const QString & IndexedNode::getSortKey() const
  {
    return mSortKey;
  };

const std::vector<IndexedNode> & IndexedNode::children()
{return mChildren;};

void IndexedTree::add(int parentId, int newId, const QString & name, const std::string & key)
{
  IndexedNode & parent = findNodeFromId(parentId);
  parent.addChild(newId, name, key);
}

IndexedNode & IndexedTree::findNodeFromId(int id)
{
  IndexedNode * tmp = const_cast<IndexedNode *>(findNodeFromId(root, id));
  assert(tmp != NULL);

  return *tmp;
}

const IndexedNode * IndexedTree::findNodeFromId(const IndexedNode & node, int id) const
  {
    if (node.getId() == id)
      return &node;

    const std::vector< IndexedNode > & children = node.children();
    std::vector< IndexedNode >::const_iterator it, itEnd = children.end();

    const IndexedNode * tmp;
    for (it = children.begin(); it != itEnd; ++it)
      {
        tmp = findNodeFromId(*it, id);
        if (tmp) return tmp;
      }

    return NULL;
  }
