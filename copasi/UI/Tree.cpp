/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/Tree.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:51 $
   End CVS Header */

#include <assert.h>

#include "Tree.h"

void IndexedTree::add(int parentId, int newId, const QString & name, const std::string & key)
{
  IndexedNode & parent = findNodeFromId(parentId);
  parent.addChild(newId, name, key);
}

IndexedNode & IndexedTree::findNodeFromId(int id)
{
  IndexedNode* tmp = findNodeFromId(root, id);
  assert(tmp != NULL);

  return *tmp;
}

IndexedNode * IndexedTree::findNodeFromId(IndexedNode & node, int id)
{
  if (node.getId() == id)
    return &node;

  std::vector< IndexedNode > & children = node.children();
  std::vector< IndexedNode >::iterator it, itEnd = children.end();

  IndexedNode * tmp;
  for (it = children.begin(); it != itEnd; ++it)
    {
      tmp = findNodeFromId(*it, id);
      if (tmp) return tmp;
    }

  return NULL;
}
