/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/Tree.h,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/24 13:28:38 $
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
#include <qstring.h>

class IndexedTree;

class IndexedNode
  {
  public:
    IndexedNode(int id = 0, const QString & name = "", const std::string & key = "")
        : mId(id), mName(name), mObjectKey(key)
    {
      mSortKey.setNum(id);
      mSortKey += "_" + name;
    };

    //~IndexedNode(); // destructor

    const std::vector<IndexedNode>& children() const
      {return mChildren;};

    void removeChildren()
    {mChildren.resize(0);};

    void addChild(int id, const QString & name, const std::string & key)
    {mChildren.push_back(IndexedNode(id, name, key));};

    int getId() const {return mId;};

    //contents methods
    const QString & getName() const {return mName;};
    void setName(const QString & name)
    {
      mName = name;
      mSortKey.setNum(mId);
      mSortKey += "_" + name;
    };
    const std::string & getObjectKey() const {return mObjectKey;};
    void setObjectKey(const std::string & key) {mObjectKey = key;};

    const QString & getSortKey() const {return mSortKey;}; //TODO

  private:
    int mId;

    QString mSortKey;

    std::vector< IndexedNode > mChildren;

    //contents
    QString mName;
    std::string mObjectKey;

    std::vector<IndexedNode>& children()
    {return mChildren;};

    friend class IndexedTree;
  };

//template <class T>
class IndexedTree
  {
  private:
    IndexedNode root; // declares the head of the tree

    IndexedNode * findNodeFromId(IndexedNode & node, int id);

  public :

    IndexedTree() {};

    ~IndexedTree() {};

    void add(int parentId, int newId, const QString & name, const std::string & key);

    IndexedNode & findNodeFromId(int id);

    IndexedNode & getRoot() {return root;};
    const IndexedNode & getRoot() const {return root;};
  };

#endif
