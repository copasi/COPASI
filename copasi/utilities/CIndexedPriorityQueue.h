#ifndef COPASI_CPriorityQueue
#define COPASI_CPriorityQueue

#include <queue>
#include <utility>

class CIndexedPriorityQueue;

/**
 * The PQNode class contains two members, an integer to represent the index, 
 * and a double to represent the key.
 * The heap structure of the indexed priority queue class is implemented as
 * a vector of PQNode.
 */

class PQNode
  {
    friend class CIndexedPriorityQueue;

  public:
    /**
     * Construct a PQNode with the given index and key
     * @param idx The index
     * @param key The key
     */
    PQNode(C_INT32 idx, C_FLOAT64 key) : mIndex(idx), mKey(key) {}

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const PQNode & d)
    {
      os << "(" << d.mIndex << ", " << d.mKey << ")";
      return os;
    }

  private:
    /**
     * The index value
     */
    C_INT32 mIndex;
    /**
     * The key value
     */
    C_FLOAT64 mKey;
  };

/**
 * The CIndexedPriorityQueue class provides an indexed priority queue.
 * Each element consistes of a pair of values, a key and an index.
 *
 * The elements in the queue are ordered according to the value of their key.
 * Since for stochastic simulations the minimum time is required, the queue is 
 * ordered so that the element with the minimum key value is at the top. This is 
 * the opposite of the normal ordering of priority queues.
 * 
 * The index can be used to access elements from positions other than at 
 * the front of the queue. 
 *
 * The indexed priority queue as applied to stochastic simulations is described in 
 * "Efficient Exact Stochastic Simulation of Chemical Systems with Many Species
 * and Many Channels", Gibson and Bruck, J. Phys. Chem. A 104 (2000) 1876-1889
 */

class CIndexedPriorityQueue
  {
  public:
    // Lifecycle methods
    /**
     * Constructor
     */
    CIndexedPriorityQueue();

    /**
     * Destructor
     */
    ~CIndexedPriorityQueue();

    // Accessors
    /**
     * Get the index associated with the highest priority node
     * @return The index
     */
    C_INT32 topIndex() const;

    /**
     * Get the key value associated with the highest priority node
     * @return The key value
     */
    C_FLOAT64 topKey() const;

    /**
     * Deletes the node in the tree with the given index. The pointer 
     * in the index array is removed.
     *
     * added by juergen 26 July, 2002
     */
    C_INT32 removeStochReaction(const C_INT32 index);

    /**
     * Inserts the node with the given index and key into the tree. The index
     * has to exist in the index array of course.
     *
     * added by juergen 26 July, 2002
     */
    C_INT32 insertStochReaction(const C_INT32 index, const C_FLOAT64 key);

    /**
     * Initializes the vector mIndexPointer. The vector will be
     * <numberOfReactions> long and every pointer will be -1, because none of
     * the nodes can be found in the tree so far. Insert the stochastic
     * reactions into the tree with insertStochReaction()
     *
     * added by juergen 26 July, 2002
     */
    void initializeIndexPointer(const C_INT32 numberOfReactions);

    /**
     * Return the size of the heap
     */
    C_INT32 size() const {return mHeap.size();}

    // Operations
    /**
     * Push an index/key pair onto the queue
     * @param index The index used to access the node
     * @param key The key value used to determine the priority
     */
    C_INT32 pushPair(const C_INT32 index, const C_FLOAT64 key);

    /**
     * Build moves entries until the correct ordering is achieved.
     */
    void buildHeap();

    /**
     * Update the key value of a node at a given index. This 
     * also moves the node to the correct position if neccessary.
     * @param index The index used to access the node
     * @param key The key value used to determine the priority     
     */
    void updateNode(const C_INT32 index, const C_FLOAT64 key);

    /**
     * Overloads the [] operator. Gives the index´th element on the heap
     * @return Returns the key
     */
    C_FLOAT64 operator[](const C_INT32 pos) const
      {
        return mHeap[pos].mKey;
      }

    /**
     * gets the key from a given index
     * @return Returns the key
     */
    C_FLOAT64 getKey(const C_INT32 index) const
      {
        // does not consider negative IndexPointer
        return mHeap[mIndexPointer[index]].mKey;
      }

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CIndexedPriorityQueue & d)
    {
      unsigned C_INT32 i;

      os << "PQ: " << std::endl;

      std::vector <PQNode>::const_iterator it;
      os << "  mHeap: " << std::endl;
      for (it = d.mHeap.begin(); it != d.mHeap.end(); it++)
        os << *it << std::endl;
      os << "  mIndexPointer: " << std::endl;
      for (i = 0; i < d.mIndexPointer.size(); i++)
        os << d.mIndexPointer[i] << " ";
      os << std::endl;

      os << std::endl;

      return os;
    }

  private:
    // Private operations
    /**
     *  Swap a pair of nodes and update the index structure accordingly.
     */
    void swapNodes(const C_INT32 index1, const C_INT32 index2);

    /**
     * Make a tree rooted at a given position into a heap
     * @param pos The root position of the tree to heapify
     */
    void heapify(const C_INT32 pos);

    /**
     * Used by the updateNode function. Update the node at a given position.
     */
    void updateAux(const C_INT32 position);

    /**
     * Provide the position in the heap of the parent to a node.
     * The positions are numbered from zero; a parent position less than zero
     * implies that the current node is already at the top of the tree.
     * @param pos The current node position
     * @return The parent node position
     */
  C_INT32 parent(const C_INT32 pos) const {return (pos + 1) / 2 - 1;}

    /**
     * Provide the position in the heap of the left child of the current node.
     * @param pos The current node position
     * @return The left child position
     */
    C_INT32 leftChild(const C_INT32 pos) const {return 2*pos + 1;}

    /**
     * Provide the position in the heap of the right child of the current node.
     * @param pos The current node position
     * @return The right child position
     */
    C_INT32 rightChild(const C_INT32 pos) const {return 2*pos + 2;}

  private:
    // Members
    /**
     * The vector which stores the heap
     */
    std::vector<PQNode> mHeap;
    /**
     * The vector which stores a pointer to each indexed node on the heap
     */
    std::vector<C_INT32> mIndexPointer;
  };

#endif // COPASI_CPriorityQueue
