#include "copasi.h"
#include "utilities.h"
#include "CPriorityQueue.h"

CIndexedPriorityQueue::CIndexedPriorityQueue()
{}

CIndexedPriorityQueue::~CIndexedPriorityQueue()
{}

C_FLOAT64 CIndexedPriorityQueue::topKey()
{
    return mHeap[0].mKey;
}

C_INT32 CIndexedPriorityQueue::topIndex()
{
    return mHeap[0].mIndex;
}

C_INT32 CIndexedPriorityQueue::pushPair(C_INT32 index, C_FLOAT64 key)
{
    // Add an element to the priority queue. This merely pushes an item onto 
    // the back of the vector corresponding to the heap, and pushes the index  
    // onto the back of the vector corresponding to the index structure. 
    // Implicit is the assumption that this is done in contiguous ascending order
    // for the index; i.e. in index order 0,1,2,3...
    // N.B. The structures are not yet ordered as an indexed priority queue; this must 
    // be done using the buildHeap() method

    // First check that the index corresponds to the heap size before insertion
    if (index != mHeap.size())
    {
        printf("Error inserting pair into priority queue\n");
        return -1;
    }
    PQNode heap_node(index, key);
    mHeap.push_back(heap_node);
    // at first, position == index
    C_INT32 position = index; // for clarity
    mIndexPointer.push_back(position);
    return 0;
}

void CIndexedPriorityQueue::buildHeap()
{
    for (C_INT32 i = mHeap.size()/2 -1 ; i >= 0; i--)
    {
        heapify(i);
    }
}

void CIndexedPriorityQueue::updateNode(C_INT32 index, C_FLOAT64 new_key)
{
    C_INT32 pos = mIndexPointer[index];
    mHeap[pos].mKey = new_key;
    updateAux(pos);
}
    
void CIndexedPriorityQueue::swapNodes(C_INT32 pos1, C_INT32 pos2)
{
    cout << "Swapping node " << pos1 << "(" << mHeap[pos1].mKey << ") with node ";
    cout << pos2 << "(" << mHeap[pos2].mKey << ")\n";
    C_FLOAT64 tempkey = mHeap[pos1].mKey;
    C_INT32 index1 = mHeap[pos1].mIndex;
    C_INT32 index2 = mHeap[pos2].mIndex;
    // Put the contents of the node at pos2 into the node at pos1
    mHeap[pos1].mIndex = index2;
    mHeap[pos1].mKey = mHeap[pos2].mKey;
    // Put the contents formerly in the node at pos1 into the node at pos2
    mHeap[pos2].mIndex = index1;
    mHeap[pos2].mKey = tempkey;
    // Swap the pointers in the index vector
    mIndexPointer[index1] = pos2;
    mIndexPointer[index2] = pos1;
}

void CIndexedPriorityQueue::heapify(C_INT32 current)
{
    C_INT32 left = leftChild(current);
    C_INT32 right = rightChild(current);
    C_INT32 highest_priority = current;
    cout << "Heapifying " << current << "(Currently " << mHeap[current].mKey << ")" << endl;
    if ( (left < mHeap.size()) && (mHeap[left].mKey < mHeap[current].mKey) )
    {
        highest_priority = left;
    }
    if ( (right < mHeap.size()) && (mHeap[right].mKey < mHeap[highest_priority].mKey) )
    {
        highest_priority = right;
    }
    if (highest_priority != current)
    {
        swapNodes(current, highest_priority);
        heapify(highest_priority);
    }
}

void CIndexedPriorityQueue::updateAux(C_INT32 pos)
{
    C_INT32 parent_pos = parent(pos);
    C_FLOAT64 keyval = mHeap[pos].mKey;
    if ((parent_pos >= 0) && (keyval < mHeap[parent_pos].mKey))
    {
        swapNodes(pos, parent_pos);
        updateAux(parent_pos);
    }
    else 
    {
        C_INT32 left = leftChild(pos);
        C_INT32 right = rightChild(pos);
        C_FLOAT64 min;
        C_INT32 min_pos = 0;
        if (left < mHeap.size())
        {
            min = mHeap[left].mKey;
            min_pos = left;
        }
        C_FLOAT64 val = mHeap[right].mKey;
        if ((right < mHeap.size()) && ( val < min ) )
        {
            min = val;
            min_pos = right;
        }
        if ( (min_pos > 0) && (keyval > min) )
        {
            C_INT32 min_index = mHeap[min_pos].mIndex;
            swapNodes(mHeap[pos].mIndex, min_pos);
            updateAux(min_pos);
        }
    }
}

#ifdef TEST_PRIORITY_QUEUE

int main(int argc, char **argv)
{
    // First test the PairCompare function
    pair<C_FLOAT64, C_INT32> pr1(123.456, 1), pr2(345.678, 2);
    CPairCompare<double, int> pc;
    cout << "For pair1 =  (" << pr1.first << ", " << pr1.second << "), pair 2 = (" << pr2.first << ", " << pr2.second << ")\n";
    cout << "Pair compare reports that ";
    if (pc(pr1, pr2) == false)
    {
        cout << "pair1 < pair2\n";
    }
    else
    {
        cout << "pair1 > pair2\n";
        return -1;
    }

    // Generates a vector of pairs, with a size given by the first argument. Each element is added to a priority queue.
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <number of pairs to generate>" << endl;
        return -1;
    }
    int count = atoi(argv[1]);
    cout << "Creating priority queue of size " << count << endl;
    std::vector<C_FLOAT64> invec;
    CIndexedPriorityQueue pq;
    CRandom *rand = new CRandom(1);
    C_FLOAT64 rndval;
    cout << "Input vector:\n";
    for (int i = 0; i < count ; i++)
    {
        rndval = rand->getUniformRandom();
        invec.push_back(rndval);
        cout << "element " << i << ":" << rndval << endl;
        pq.pushPair(i, invec[i]);
    }
    cout << "Building heap\n";
    pq.buildHeap();
    cout << "Done building heap\n";
    // Display the priority queue
    cout << "\nPriority Queue:\n";
    for (int i = 0; i < count; i++)
    {
        cout << "Queue: ";
        for (int j = 0; j < count; j++) cout << " " << j << "-" << pq[j];
        cout << endl;
        cout << "Position: " << i;
        cout << " Index = " << pq.topIndex();
        cout << " Key = " << pq.topKey() << endl;
        pq.updateNode(pq.topIndex(), 10000000);
    }
    
    return 0;
}                       

#endif // TEST_PRIORITY_QUEUE

