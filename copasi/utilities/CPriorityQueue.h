#ifndef COPASI_CPriorityQueue
#define COPASI_CPriorityQueue

#include <queue>
#include <utility>

/**
 * CPairCompare is a function object used to compare two pairs,
 * based on the value of the first member of the pair. 
 * Returns true if the first value is greater than the second, false otherwise.
 * N.B. The greater than (">") operator must be defined for the first type in the pair.
 */
template <class CType1, class CType2>
class CPairCompare
{
 public:
    /**
     * Overloads the () operator to return true if pair1.first > pair2.first
     * @param pair1 The first pair
     * @param pair2 The second pair
     * @return True if pair1 > pair 2, false otherwise
     */
    bool operator()( const pair<CType1, CType2> pair1, 
                     const pair<CType1, CType2> pair2 )
        {
            return (pair1.first > pair2.first) ? true : false;
        }
};

/**
 * The CPriorityQueue class is just a simple wrapper around the standard
 * library priority_queue class. This could be reimplemented later if 
 * neccessary for efficiency reasons. The default comparison function object 
 * provides for priority queues with ascending key values.
 */
template <class CType1, class CType2>
class CPriorityQueue : public priority_queue< pair<CType1, CType2>, vector<pair<CType1, CType2> >, CPairCompare<CType1, CType2> >
{
 public:
    /**
     * Constructor
     */
    CPriorityQueue() : priority_queue<pair<CType1, CType2>, vector<pair<CType1, CType2> >, CPairCompare<CType1, CType2> >() {}
    /**
     * Destructor
     */
    ~CPriorityQueue() {};
    /**
     * Add a pair, indexed on the first value, to the head of the queue.
     */
    void addPair(const pair<CType1, CType2>& pr) 
        {
            push(pr);
        }
    /**
     * Retrieve the pair at the top of the queue (i.e. with the highest priority). 
     * This is also removed from the priority queue (which is not normally done 
     * with the usual priority queue top() function).
     */
    pair<CType1, CType2> getTop() 
        {
            pair<CType1, CType2> pr = top();
            pop();
            return pr;
        }
};

#endif // COPASI_CPriorityQueue
