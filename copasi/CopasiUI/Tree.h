/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/Tree.h,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/03/02 09:42:56 $
   End CVS Header */

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

class IndexedTree;

class IndexedNode
  {
  public:
    IndexedNode(int id = 0, const QString & name = "", const std::string & key = "");

    IndexedNode(const IndexedNode & src);

    ~IndexedNode(); // destructor

    const std::vector<IndexedNode*>& children() const;

    void removeChildren();

    void addChild(int id, const QString & name, const std::string & key);

    int getId() const;

    //contents methods
    const QString & getName() const;
    void setName(const QString & name);
    const std::string & getObjectKey() const;
    void setObjectKey(const std::string & key);

    const QString & getSortKey() const;

    //const std::vector<IndexedNode> & children();

  private:
    int mId;

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

    const IndexedNode * findNodeFromId(const IndexedNode & node, int id) const;

  public :

    IndexedTree() {};

    ~IndexedTree() {};

    void add(int parentId, int newId, const QString & name, const std::string & key);

    IndexedNode * findNodeFromId(int id);
    const IndexedNode * findNodeFromId(int id) const;

    IndexedNode * getRoot() {return &root;};
    const IndexedNode * getRoot() const {return &root;};
  };

#endif
