#include "copasi.h"
#include "utilities.h"
#include "CPriorityQueue.h"

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
    std::vector<pair<C_FLOAT64, C_INT32> > invec;
    CPriorityQueue<C_FLOAT64, C_INT32> pq;
    CRandom *rand = new CRandom();
    C_FLOAT64 pair1;
    C_INT32 pair2;
    cout << "Input vector:\n";
    for (int i = 0; i < count ; i++)
    {
        pair1 = rand->getUniformRandom();
        pair2 = static_cast<int> (100*rand->getUniformRandom());
        pair<C_FLOAT64, C_INT32>pr(pair1, pair2);
        invec.push_back(pr);
        cout << "element " << i << ": (" << pair1 << ", " << pair2 << ")\n";
        pq.addPair(invec[i]);
    }
    // Display the priority queue
    cout << "\nPriority Queue:\n";
    count = 0;
    while (pq.size() > 0)
    {
        pair<C_FLOAT64, C_INT32> pr = pq.getTop();
        cout << "Element " << count++ << ": " << pr.first << ", " << pr.second << endl;
    }
    return 0;
}                       
#endif // TEST_PRIORITY_QUEUE
