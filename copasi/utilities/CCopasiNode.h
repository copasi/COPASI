// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CCopasiNode class.
 * The class CCopasiNode is describes a node of the CCopasiTree.
 *
 * Created for COPASI by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiNode
#define COPASI_CCopasiNode

#include <cstddef>

/**
 * The class CCopasiNode is the interface used by the template class
 * CCopasiTree< class Node> to manage the nodes of a tree. Actual
 * implementation of nodes must be derived from CCopasiNode for the tree
 * to operate properly.
 */
template < class _Data > class CCopasiNode
{
public:
  typedef _Data Data;

  // Attributes
private:
  /**
   * A pointer to the parent of the node.
   */
  CCopasiNode< Data > * mpParent;

  /**
   * A pointer to the first child of the node.
   */
  CCopasiNode< Data > * mpChild;

  /**
   * A pointer to the first sibling of the node.
   */
  CCopasiNode< Data > * mpSibling;

protected:
  /**
   * The data content of the node;
   */
  Data mData;

  // Operations
public:
  /**
   * Default constructor.
   * @param CCopasiNode< Data > * pParent (default: NULL)
   */
  CCopasiNode(CCopasiNode< Data > * pParent = NULL):
    mpParent(pParent),
    mpChild(NULL),
    mpSibling(NULL),
    mData()
  {}

  /**
   * Copy constructor.
   * @param const CCopasiNode< Data > & src
   */
  CCopasiNode(const CCopasiNode< Data > & src):
    mpParent(src.mpParent),
    mpChild(src.mpChild),
    mpSibling(src.mpSibling),
    mData(src.mData)
  {}

  /**
   * Specific constructor.
   * @param const Data & data
   * @param CCopasiNode< Data > * pParent (default: NULL)
   */
  CCopasiNode(const Data & data, CCopasiNode< Data > * pParent = NULL):
    mpParent(pParent),
    mpChild(NULL),
    mpSibling(NULL),
    mData(data)
  {}

  /**
   * Destructor.
   * Note: Within a tree the parent of this node has to be corrected.
   */
  virtual ~CCopasiNode()
  {
    deleteChildren();

    if (mpParent) mpParent->removeChild(this);
  }

  /**
   * Retrieve the data of the Node.
   * @return Data data
   */
  virtual const Data & getData() const
  {
    return mData;
  }

  /**
   * Retrieve the data of the Node.
   * @return Data data
   */
  virtual Data & getData()
  {
    return mData;
  }

  /**
   * Set the data of the Node.
   * @param const Data & data
   * @return bool success
   */
  virtual bool setData(const Data & data)
  {
    mData = data;

    return true;
  }

  /**
   * Retrieve the parent of a Node.
   * @return CCopasiNode< Data > * pParent
   */
  CCopasiNode< Data > * getParent() {return mpParent;}

  /**
   * Retrieve the parent of a Node.
   * @return const CCopasiNode< Data > * pParent
   */
  const CCopasiNode< Data > * getParent() const {return mpParent;}

  /**
   * Add a child to a node.
   * If pAfter == this the child will be inserted at the front of the list
   * of children.
   * @param CCopasiNode< Data > * pChild
   * @param CCopasiNode< Data > * pAfter
   *        (default: NULL appended to the list of children)
   * @return bool Success
   */
  virtual bool addChild(CCopasiNode< Data > * pChild,
                        CCopasiNode< Data > * pAfter = NULL)
  {
    if (!pChild) return false;           // Nothing to insert.

    if (pAfter == this)
      {
        pChild->setSibling(mpChild);
        mpChild = NULL;
      }

    if (mpChild)
      return mpChild->addSibling(pChild, pAfter);

    mpChild = pChild;
    mpChild->setParent(this);

    return true;
  }

  /**
   * Remove a child from a node.
   * @param CCopasiNode< Data > * pChild
   * @return bool Success
   */
  virtual bool removeChild(CCopasiNode< Data > * pChild)
  {
    if (!pChild) return false;           // Nothing to remove.

    if (mpChild != pChild)
      return mpChild->removeSibling(pChild);

    mpChild = mpChild->getSibling();

    pChild->setParent(NULL);
    pChild->setSibling(NULL);

    return true;
  }

  /**
   * Delete all children of the node
   */
  bool deleteChildren()
  {
    while (mpChild) delete mpChild;

    return true;
  }

  /**
   * Retrieve the child of a node.
   * @return CCopasiNode< Data > * pChild
   */
  CCopasiNode< Data > * getChild() {return mpChild;}

  /**
   * Retrieve the child of a node.
   * @return const CCopasiNode< Data > * pChild
   */
  const CCopasiNode< Data > * getChild() const {return mpChild;}

  /**
   * Retrieve the child with given index of a node.
   * If index is out of range NULL is returned.
   * @return const CCopasiNode< Data > * pChild
   */
  CCopasiNode< Data > * getChild(const size_t & index)
  {
    size_t count = 0;

    CCopasiNode< Data > * pChild = getChild();

    while (count < index && pChild != NULL)
      {
        count++;
        pChild = pChild->getSibling();
      }

    return pChild;
  }

  /**
   * Retrieve the child with given index of a node.
   * If index is out of range NULL is returned.
   * @return const CCopasiNode< Data > * pChild
   */
  const CCopasiNode< Data > * getChild(const size_t & index) const
  {
    size_t count = 0;

    const CCopasiNode< Data > * pChild = getChild();

    while (count < index && pChild != NULL)
      {
        count++;
        pChild = pChild->getSibling();
      }

    return pChild;
  }

  /**
   * Retrieve the number of children
   * @return size_t numChildren
   */
  size_t getNumChildren() const
  {
    size_t count = 0;

    const CCopasiNode< Data > * pChild = getChild();

    while (pChild != NULL)
      {
        count++;
        pChild = pChild->getSibling();
      }

    return count;
  }

  /**
   * Add a sibling to a node.
   * If pAfter == this the sibling will be inserted at the front of the list
   * of siblings.
   * @param CCopasiNode< Data > * pSibling
   * @param CCopasiNode< Data > * pAfter
   *        (default: NULL appended to the list of siblings)
   * @return bool Success
   */
  bool addSibling(CCopasiNode< Data > * pSibling,
                  CCopasiNode< Data > * pAfter = NULL)
  {
    if (!pSibling) return false;        // Nothing to insert.

    if (this == pAfter)
      {
        pSibling->setParent(mpParent);
        pSibling->setSibling(mpSibling);
        mpSibling = pSibling;
        return true;
      }

    CCopasiNode< Data > * pTmp = this;

    while (pTmp != pAfter && pTmp->getSibling())
      pTmp = pTmp->getSibling();

    if (pTmp == pAfter || pAfter == NULL)
      return pTmp->addSibling(pSibling, pTmp);
    else
      return false;                      // Insertion point no found.
  }

private:
  /**
   * Remove a sibling.
   * @param CCopasiNode< Data > * pSibling
   * @return bool Success
   */
  bool removeSibling(CCopasiNode< Data > * pSibling)
  {
    if (!pSibling) return false;        // Nothing to remove.

    if (this == pSibling)
      {
        if (mpParent)
          mpParent->removeChild(pSibling);
        else
          return false;                  // Root can not be removed
      }

    CCopasiNode< Data > * pTmp = this;
    CCopasiNode< Data > * pTmpSibling = this->mpSibling;

    while (pTmpSibling != pSibling && pTmpSibling != NULL)
      {
        pTmp = pTmpSibling;
        pTmpSibling = pTmpSibling->getSibling();
      }

    if (!pTmpSibling)
      return false; // We did not find a sibling.

    pTmp->setSibling(pSibling->getSibling());

    pSibling->setParent(NULL);
    pSibling->setSibling(NULL);

    return true;
  }

public:
  /**
   * Retrieve the sibling of a node.
   * @return CCopasiNode< Data > * pSibling
   */
  CCopasiNode< Data > * getSibling() {return mpSibling;}

  /**
   * Retrieve the sibling of a node.
   * @return const CCopasiNode< Data > * pSibling
   */
  const CCopasiNode< Data > * getSibling() const {return mpSibling;}

  /**
   * Retrieve a pointer to the next node, which is either a
   * child, a sibling, or an ancestor. The nodes are evaluated
   * in that order and the first non NULL pointer is returned.
   * If all evaluate to NULL, NULL will be returned.
   * @return CCopasiNode< Data > * pNext
   */
  CCopasiNode< Data > * getNext()
  {
    if (mpChild) return mpChild;

    return getNextNonChild();
  }

  /**
   * Retrieve a pointer to the next node, which is either a
   * child, a sibling, or an ancestor. The nodes are evaluated
   * in that order and the first non NULL pointer is returned.
   * If all evaluate to NULL, NULL will be returned.
   * @return const CCopasiNode< Data > * pNext
   */
  const CCopasiNode< Data > * getNext() const
  {
    if (mpChild) return mpChild;

    return getNextNonChild();
  }

  /**
   * Retrieve a pointer to the next node, which is not a child node
   * This is either a sibling or an ancestor. The nodes are evaluated
   * in that order and the first non NULL pointer is returned.
   * If all evaluate to NULL, NULL will be returned.
   * @return CCopasiNode< Data > * pNextNonChild
   */
  CCopasiNode< Data > * getNextNonChild()
  {
    if (mpSibling) return mpSibling;

    if (mpParent) return mpParent->getNextNonChild();

    return NULL;
  }

  /**
   * Retrieve a pointer to the next node, which is not a child node
   * This is either a sibling or an ancestor. The nodes are evaluated
   * in that order and the first non NULL pointer is returned.
   * If all evaluate to NULL, NULL will be returned.
   * @return const CCopasiNode< Data > * pNextNonChild
   */
  const CCopasiNode< Data > * getNextNonChild() const
  {
    if (mpSibling) return mpSibling;

    if (mpParent) return mpParent->getNextNonChild();

    return NULL;
  }

protected:
  /**
   * Set the parent of a Node.
   * @param CCopasiNode< Data > * pParent
   * @return bool Success
   */
  bool setParent(CCopasiNode< Data > * pParent)
  {
    mpParent = pParent;
    return true;
  }

  /**
   * Set the child of a node.
   * @param CCopasiNode< Data > * pChild
   * @return bool Success
   */
  bool setChild(CCopasiNode< Data > * pChild)
  {
    mpChild = pChild;
    return true;
  }
  /**
   * Set the sibling of a node.
   * @param CCopasiNode< Data > * pSibling
   * @return bool Success
   */
  bool setSibling(CCopasiNode< Data > * pSibling)
  {
    mpSibling = pSibling;
    return true;
  }
};

#endif // COPASI_CCopasiNode
