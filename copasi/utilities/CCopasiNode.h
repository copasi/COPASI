/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiNode.h,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:35:33 $
   End CVS Header */

/**
 * CCopasiNode class.
 * The class CCopasiNode is describes a node of the CCopasiTree.
 *
 * Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiNode
#define COPASI_CCopasiNode

/**
 * The class CCopasiNode is the interface used by the template class
 * CCopasiTree< class Node> to manage the nodes of a tree. Actual 
 * implementation of nodes must be dereived from CCopasiNode for the tree 
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

      // Operations
    public:
      /**
       * Default constructor.
       * @param CCopasiNode< Data > * pParent (default: NULL)
       */
      CCopasiNode(CCopasiNode< Data > * pParent = NULL):
          mpParent(pParent),
          mpChild(NULL),
          mpSibling(NULL)
      {}

      /**
       * Copy constructor.
       * @param const CCopasiNode< Data > & src
       */
      CCopasiNode(const CCopasiNode< Data > & src):
          mpParent(src.mpParent),
          mpChild(src.mpChild),
          mpSibling(src.mpSibling)
      {}

      /**
       * Specific constructor.
       * @param const Data & data
       * @param CCopasiNode< Data > * pParent (default: NULL)
       */
      CCopasiNode(const Data & data, CCopasiNode< Data > * pParent = NULL):
          mpParent(pParent),
          mpChild(NULL),
          mpSibling(NULL)
      {}

      /**
       * Destructor.
       * Note: Within a tree the parent of this node has to be corrected.
       */
      virtual ~CCopasiNode() {deleteChildren();}

      /**
       * Retreive the data of the Node.
       * @return Data data
       */
      virtual Data getData() const = NULL;

      /**
       * Set the data of the Node.
       * @param const Data & data
       * @return bool success
       */
      virtual bool setData(const Data & data) = NULL;

      /**
       * Retreive the parent of a Node.
       * @return CCopasiNode< Data > * pParent
       */
      CCopasiNode< Data > * getParent() {return mpParent;}

      /**
       * Retreive the parent of a Node.
       * @return const CCopasiNode< Data > * pParent
       */
      const CCopasiNode< Data > * getParent() const {return mpParent;}

      /**
       * Add a child to a node.
       * If pAfter == this the child will be inserted at the fornt of the list
       * of children.
       * @param CCopasiNode< Data > * pChild
       * @param CCopasiNode< Data > * pAfter 
       *        (default: NULL appended to the list of children)
       * @return bool Success
       */
      bool addChild(CCopasiNode< Data > * pChild,
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
      bool removeChild(CCopasiNode< Data > * pChild)
      {
        if (!pChild) return false;           // Nothing to remove.

        if (mpChild != pChild)
          return mpChild->removeSibling(pChild);

        mpChild = mpChild->getSibling();
        return true;
      }

      /**
       * Retreive the child of a node.
       * @return CCopasiNode< Data > * pChild
       */
    CCopasiNode< Data > * getChild() {return mpChild;}

      /**
       * Retreive the child of a node.
       * @return const CCopasiNode< Data > * pChild
       */
      const CCopasiNode< Data > * getChild() const {return mpChild;}

      /**
       * Add a sibling to a node.
       * If pAfter == this the sibling will be inserted at the fornt of the list
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

      /**
       * Remove a siblling.
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

        if (pTmpSibling)
          return pTmp->setSibling(pSibling->getSibling());
        else
          return false;                      // We did not find pSibling.
      }

      /**
       * Retreive the sibling of a node.
       * @return CCopasiNode< Data > * pSibling
       */
    CCopasiNode< Data > * getSibling() {return mpSibling;}

      /**
       * Retreive the sibling of a node.
       * @return const CCopasiNode< Data > * pSibling
       */
      const CCopasiNode< Data > * getSibling() const {return mpSibling;}

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

      bool deleteChildren()
      {
        while (mpChild) delete mpChild;
        if (mpParent) mpParent->removeChild(this);

        return true;
      }
    };

#endif // COPASI_CCopasiNode
