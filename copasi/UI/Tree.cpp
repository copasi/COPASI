/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/Tree.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/03/02 09:42:56 $
   End CVS Header */

#include <assert.h>

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"

#include "Tree.h"

IndexedNode::IndexedNode(int id, const QString & name, const std::string & key)
    : mId(id),
    mSortKey(),
    mChildren(),
    mName(name),
    mObjectKey(key)
{
  mChildren.clear();
  mSortKey.setNum(id);
  mSortKey += "_" + name;
  //std::cout << "    IndexedNode::Constructor " << mSortKey << std::endl;
  CONSTRUCTOR_TRACE;
};

IndexedNode::IndexedNode(const IndexedNode & src):
    mId(src.mId),
    mSortKey(src.mSortKey),
    //mChildren(src.mChildren),
    mName(src.mName),
    mObjectKey(src.mObjectKey)
{
  //std::cout << "     IndexedNode::CopyConstr " << mSortKey << std::endl;

  mChildren.clear();
  std::vector<IndexedNode*>::const_iterator it, itEnd = src.mChildren.end();
  for (it = src.mChildren.begin(); it != itEnd; ++it)
    mChildren.push_back(new IndexedNode(**it));

  CONSTRUCTOR_TRACE;
};

IndexedNode::~IndexedNode()
{
  removeChildren();
  DESTRUCTOR_TRACE;
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

void IndexedNode::addChild(int id, const QString & name, const std::string & key)
{mChildren.push_back(new IndexedNode(id, name, key));};

int IndexedNode::getId() const {return mId;};

//contents methods
const QString & IndexedNode::getName() const {return mName;};

void IndexedNode::setName(const QString & name)
{
  mName = name;
  mSortKey.setNum(mId);
  mSortKey += "_" + name;
  //std::cout << "     IndexedNode::setName " << mSortKey << std::endl;
};

const std::string & IndexedNode::getObjectKey() const {return mObjectKey;};

void IndexedNode::setObjectKey(const std::string & key) {mObjectKey = key;};

const QString & IndexedNode::getSortKey() const
  {
    //std::cout << "        IndexedNode::getSortKey " << mSortKey << std::endl;
    return mSortKey;
  };

const std::vector<IndexedNode*> & IndexedNode::children() const
  {return mChildren;};

//*************  Tree *******************

void IndexedTree::add(int parentId, int newId, const QString & name, const std::string & key)
{
  IndexedNode * parent = findNodeFromId(parentId);
  parent->addChild(newId, name, key);
}

IndexedNode * IndexedTree::findNodeFromId(int id)
{
  IndexedNode * tmp = const_cast<IndexedNode*>(findNodeFromId(root, id));
  assert(tmp != NULL);

  return tmp;
}

const IndexedNode * IndexedTree::findNodeFromId(int id) const
  {
    const IndexedNode * tmp = findNodeFromId(root, id);
    assert(tmp != NULL);

    return tmp;
  }

const IndexedNode * IndexedTree::findNodeFromId(const IndexedNode & node, int id) const
  {
    if (node.getId() == id)
      return &node;

    const std::vector<IndexedNode*> & children = node.children();
    std::vector<IndexedNode*>::const_iterator it, itEnd = children.end();

    const IndexedNode * tmp;
    for (it = children.begin(); it != itEnd; ++it)
      {
        tmp = findNodeFromId(**it, id);
        if (tmp) return tmp;
      }

    return NULL;
  }
