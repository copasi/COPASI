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
class CCopasiNode
  {
    // Attributes
  private:
    /**
     * A pointer to the parent of the node.
     */
    CCopasiNode * mpParent;

    /**
     * A pointer to the first child of the node.
     */
    CCopasiNode * mpChild;

    /**
     * A pointer to the first sibbling of the node.
     */
    CCopasiNode * mpSibbling;

    // Operations
  public:
    /**
     * Default constructor.
     * @param CCopasiNode * pParent (default: NULL)
     */
    CCopasiNode(CCopasiNode * pParent = NULL);

    /**
     * Copy constructor.
     * @param const CCopasiNode & src
     */
    CCopasiNode(const CCopasiNode & src);

    /**
     * Destructor.
     * Note: Within a tree the parent of this node has to be corrected.
     */
    ~CCopasiNode();

    /**
     * Retreive the parent of a Node.
     * @return CCopasiNode * pParent
     */
    CCopasiNode * getParent();

    /**
     * Add a child to a node.
     * @param CCopasiNode * pChild
     * @return bool Success
     */
    bool addChild(CCopasiNode * pChild,
                  CCopasiNode * pAfter = NULL);

    /**
     * Remove a child from a node.
     * @param CCopasiNode * pChild
     * @return bool Success
     */
    bool removeChild(CCopasiNode * pChild);

    /**
     * Retreive the child of a node.
     * @return CCopasiNode * pChild
     */
    CCopasiNode * getChild();

    /**
     * Add a sibbling to a node.
     * If pAfter == this the sibbling will be inserted at the fornt of the list
     * of sibblings.
     * @param CCopasiNode * pSibbling
     * @param CCopasiNode * pAfter 
     *        (default: NULL appended to the list of sibblings)
     * @return bool Success
     */
    bool addSibbling(CCopasiNode * pSibbling,
                     CCopasiNode * pAfter = NULL);

    /**
     * Remove a siblling.
     * @param CCopasiNode * pSibbling
     * @return bool Success
     */
    bool removeSibbling(CCopasiNode * pSibbling);

    /**
     * Retreive the sibbling of a node.
     * @return CCopasiNode * pSibbling
     */
    CCopasiNode * getSibbling();

  protected:
    /**
     * Set the parent of a Node.
     * @param CCopasiNode * pParent
     * @return bool Success
     */
    bool setParent(CCopasiNode * pParent);

    /**
     * Set the child of a node.
     * @param CCopasiNode * pChild
     * @return bool Success
     */
    bool setChild(CCopasiNode * pChild);

    /**
     * Set the sibbling of a node.
     * @param CCopasiNode * pSibbling
     * @return bool Success
     */
    bool setSibbling(CCopasiNode * pSibbling);
  };

#endif // COPASI_CCopasiNode
