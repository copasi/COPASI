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
template < class Data > class CCopasiNode
    {
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
       * A pointer to the first sibbling of the node.
       */
      CCopasiNode< Data > * mpSibbling;

      // Operations
    public:
      /**
       * Default constructor.
       * @param CCopasiNode< Data > * pParent (default: NULL)
       */
      CCopasiNode(CCopasiNode< Data > * pParent = NULL):
          mpParent(pParent),
          mpChild(NULL),
          mpSibbling(NULL)
      {}

      /**
       * Copy constructor.
       * @param const CCopasiNode< Data > & src
       */
      CCopasiNode(const CCopasiNode< Data > & src):
          mpParent(src.mpParent),
          mpChild(src.mpChild),
          mpSibbling(src.mpSibbling)
      {}

      /**
       * Specific constructor.
       * @param const Data & data
       * @param CCopasiNode< Data > * pParent (default: NULL)
       */
      CCopasiNode(const Data & data, CCopasiNode< Data > * pParent = NULL):
          mpParent(pParent),
          mpChild(NULL),
          mpSibbling(NULL)
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
            pChild->setSibbling(mpChild);
            mpChild = NULL;
          }

        if (mpChild)
          return mpChild->addSibbling(pChild, pAfter);

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
          return mpChild->removeSibbling(pChild);

        mpChild = mpChild->getSibbling();
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
       * Add a sibbling to a node.
       * If pAfter == this the sibbling will be inserted at the fornt of the list
       * of sibblings.
       * @param CCopasiNode< Data > * pSibbling
       * @param CCopasiNode< Data > * pAfter 
       *        (default: NULL appended to the list of sibblings)
       * @return bool Success
       */
      bool addSibbling(CCopasiNode< Data > * pSibbling,
                       CCopasiNode< Data > * pAfter = NULL)
      {
        if (!pSibbling) return false;        // Nothing to insert.

        if (this == pAfter)
          {
            pSibbling->setParent(mpParent);
            pSibbling->setSibbling(mpSibbling);
            mpSibbling = pSibbling;
            return true;
          }

        CCopasiNode< Data > * pTmp = this;
        while (pTmp != pAfter && pTmp->getSibbling())
          pTmp = pTmp->getSibbling();

        if (pTmp == pAfter || pAfter == NULL)
          return pTmp->addSibbling(pSibbling, pTmp);
        else
          return false;                      // Insertion point no found.
      }

      /**
       * Remove a siblling.
       * @param CCopasiNode< Data > * pSibbling
       * @return bool Success
       */
      bool removeSibbling(CCopasiNode< Data > * pSibbling)
      {
        if (!pSibbling) return false;        // Nothing to remove.

        if (this == pSibbling)
          {
            if (mpParent)
              mpParent->removeChild(pSibbling);
            else
              return false;                  // Root can not be removed
          }

        CCopasiNode< Data > * pTmp = this;
        CCopasiNode< Data > * pTmpSibbling = this->mpSibbling;

        while (pTmpSibbling != pSibbling && pTmpSibbling != NULL)
          {
            pTmp = pTmpSibbling;
            pTmpSibbling = pTmpSibbling->getSibbling();
          }

        if (pTmpSibbling)
          return pTmp->setSibbling(pSibbling->getSibbling());
        else
          return false;                      // We did not find pSibbling.
      }

      /**
       * Retreive the sibbling of a node.
       * @return CCopasiNode< Data > * pSibbling
       */
    CCopasiNode< Data > * getSibbling() {return mpSibbling;}

      /**
       * Retreive the sibbling of a node.
       * @return const CCopasiNode< Data > * pSibbling
       */
      const CCopasiNode< Data > * getSibbling() const {return mpSibbling;}

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
       * Set the sibbling of a node.
       * @param CCopasiNode< Data > * pSibbling
       * @return bool Success
       */
      bool setSibbling(CCopasiNode< Data > * pSibbling)
      {
        mpSibbling = pSibbling;
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
