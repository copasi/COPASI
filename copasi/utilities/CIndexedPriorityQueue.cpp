// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"
#include "CCopasiMessage.h"
#include "CIndexedPriorityQueue.h"

CIndexedPriorityQueue::CIndexedPriorityQueue()
{}

CIndexedPriorityQueue::~CIndexedPriorityQueue()
{}

C_FLOAT64 CIndexedPriorityQueue::topKey() const
{
  if (mHeap.empty()) return std::numeric_limits<C_FLOAT64>::quiet_NaN();

  return mHeap[0].mKey;
}

size_t CIndexedPriorityQueue::topIndex() const
{
  if (mHeap.empty())
    return C_INVALID_INDEX;

  return mHeap[0].mIndex;
}

// juergen: added 26 July, 2002
size_t CIndexedPriorityQueue::removeStochReaction(const size_t index)
{
  size_t t;

  // check if index is valid
  if (index >= mIndexPointer.size()) return C_INVALID_INDEX;

  if ((mIndexPointer[index] != C_INVALID_INDEX) && (mIndexPointer[index] != (mHeap.size() - 1))) // if the node with the given index exists in the tree
    {
      // remove the node with the given index from the tree
      swapNodes(t = mIndexPointer[index], mHeap.size() - 1);
      mHeap.pop_back();
      mIndexPointer[index] = -1;
      heapify(t);
    }
  else if (mIndexPointer[index] == (mHeap.size() - 1)) // last node in the heap
    {
      mHeap.pop_back();
      mIndexPointer[index] = -1;
    }

  return 0;
}

// juergen: added 26 July, 2002
size_t CIndexedPriorityQueue::insertStochReaction(const size_t index, const C_FLOAT64 key)
{
  size_t pos;

  // check if index is valid
  if (index >= mIndexPointer.size()) return - 1;

  // first the node is inserted at the end of the heap
  mIndexPointer[index] = mHeap.size();
  PQNode heap_node(index, key);
  mHeap.push_back(heap_node);
  // bubble the node up the tree to the right position !
  pos = mIndexPointer[index];

  while ((pos > 0) && (mHeap[parent(pos)].mKey > key))
    {
      swapNodes(pos, parent(pos));
      pos = parent(pos);
    }

  return 0;
}

// juergen: added 26 July, 2002
void CIndexedPriorityQueue::initializeIndexPointer(const size_t numberOfReactions)
{
  size_t i;

  for (i = 0; i < numberOfReactions; i++)
    {
      mIndexPointer.push_back(C_INVALID_INDEX);
    }
}

size_t CIndexedPriorityQueue::pushPair(const size_t index, const C_FLOAT64 key)
{
  // Add an element to the priority queue. This merely pushes an item onto
  // the back of the vector corresponding to the heap, and pushes the index
  // onto the back of the vector corresponding to the index structure.
  // Implicit is the assumption that this is done in contiguous ascending order
  // for the index; i.e. in index order 0,1,2,3...
  // N.B. The structures are not yet ordered as an indexed priority queue; this must
  // be done using the buildHeap() method

  // First check that the index corresponds to the heap size before insertion
  if (static_cast<unsigned int>(index) != mHeap.size())
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Error inserting pair into priority queue");
      return - 1;
    }

  PQNode heap_node(index, key);
  mHeap.push_back(heap_node);
  // at first, position == index
  size_t position = index; // for clarity
  mIndexPointer.push_back(position);
  return 0;
}

void CIndexedPriorityQueue::buildHeap()
{
  for (size_t i = mHeap.size() / 2 - 1; i != C_INVALID_INDEX; i--)
    {
      heapify(i);
    }
}

void CIndexedPriorityQueue::clear()
{mHeap.clear(); mIndexPointer.clear();}

void CIndexedPriorityQueue::updateNode(const size_t index, const C_FLOAT64 new_key)
{
  size_t pos = mIndexPointer[index];
  //    cout << "Setting heap at " << pos << " to be " << new_key << endl;
  mHeap[pos].mKey = new_key;
  updateAux(pos);
}

void CIndexedPriorityQueue::swapNodes(const size_t pos1, const size_t pos2)
{
  //    cout << "Swapping node " << pos1 << "(" << mHeap[pos1].mKey << ") with node ";
  //    cout << pos2 << "(" << mHeap[pos2].mKey << ")\n";
  C_FLOAT64 tempkey = mHeap[pos1].mKey;
  size_t index1 = mHeap[pos1].mIndex;
  size_t index2 = mHeap[pos2].mIndex;
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

void CIndexedPriorityQueue::heapify(const size_t current)
{
  size_t left = leftChild(current);
  size_t right = rightChild(current);
  size_t highest_priority = current;

  //    cout << "Heapifying " << current << "(Currently " << mHeap[current].mKey << ")" << endl;
  if ((static_cast<unsigned int>(left) < mHeap.size()) && (mHeap[left].mKey < mHeap[current].mKey))
    {
      highest_priority = left;
    }

  if ((static_cast<unsigned int>(right) < mHeap.size()) && (mHeap[right].mKey < mHeap[highest_priority].mKey))
    {
      highest_priority = right;
    }

  if (highest_priority != current)
    {
      swapNodes(current, highest_priority);
      heapify(highest_priority);
    }
}

void CIndexedPriorityQueue::updateAux(const size_t pos)
{
  size_t parent_pos = parent(pos);
  C_FLOAT64 keyval = mHeap[pos].mKey;

  if (parent_pos != C_INVALID_INDEX &&
      keyval < mHeap[parent_pos].mKey)
    {
      swapNodes(pos, parent_pos);
      updateAux(parent_pos);
    }
  else
    {
      size_t left = leftChild(pos);
      size_t right = rightChild(pos);
      C_FLOAT64 min = 0.0;
      size_t min_pos = 0;

      if (left < mHeap.size())
        {
          min = mHeap[left].mKey;
          min_pos = left;
        }

      C_FLOAT64 val; // = mHeap[right].mKey; //!!!

      if ((right < mHeap.size()) && ((val = mHeap[right].mKey) < min))
        {
          min = val;
          min_pos = right;
        }

      if ((min_pos > 0) && (keyval > min))
        {
          //            swapNodes(mHeap[pos].mIndex, min_pos);
          swapNodes(pos, min_pos);
          updateAux(min_pos);
        }
    }
}

#ifdef TEST_PRIORITY_QUEUE

int main(int argc, char **argv)
{
  // Generates a vector of pairs, with a size given by the first argument. Each element is added to a priority queue.
  if (argc != 2)
    {
      cout << "Usage: " << argv[0] << " <number of pairs to generate>" << endl;
      return - 1;
    }

  int count = atoi(argv[1]);
  cout << "Creating priority queue of size " << count << endl;
  std::vector<C_FLOAT64> invec;
  CIndexedPriorityQueue pq;
  CRandom *rand = new CRandom(1);
  C_FLOAT64 rndval;
  cout << "Input vector:\n";

  for (int i = 0; i < count; i++)
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

std::ostream & operator<<(std::ostream &os, const PQNode & d)
{
  os << "(" << d.mIndex << ", " << d.mKey << ")";
  return os;
}

std::ostream & operator<<(std::ostream &os, const CIndexedPriorityQueue & d)
{
  size_t i;

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
