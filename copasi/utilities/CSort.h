/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSort.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/26 20:56:11 $
   End CVS Header */

#ifndef COPASI_CSort
 #define COPASI_CSort

#include <algorithm>

#include "CVector.h"

template <typename RandomAccessIterator>
bool sortDefault(const std::pair<RandomAccessIterator, unsigned C_INT32> & lhs,
                 const std::pair<RandomAccessIterator, unsigned C_INT32> & rhs)
{return *lhs.first < *rhs.first;}

template <typename RandomAccessIterator>
void sortWithPivot(RandomAccessIterator first,
                   RandomAccessIterator last,
                   CVector<unsigned C_INT32> & pivot)
{
  assert(first < last);

  // Initialize the two column array to be sorted
  CVector<std::pair<RandomAccessIterator, unsigned C_INT32> > ToBeSorted;
  ToBeSorted.resize(last - first);

  RandomAccessIterator it;
  unsigned C_INT32 i;

  CVector<std::pair<RandomAccessIterator, unsigned C_INT32> >::elementType * itToBeSorted;

  for (it = first, i = 0, itToBeSorted = ToBeSorted.array();
       it != last;
       ++it, ++i, ++itToBeSorted)
    {
      itToBeSorted->first = it;
      itToBeSorted->second = i;
    }

  itToBeSorted = ToBeSorted.array();

  std::sort(itToBeSorted,
            itToBeSorted + (last - first),
            &sortDefault<RandomAccessIterator>);

  // Copy the resulting pivots to the pivot vector.
  pivot.resize(last - first);
  CVector<unsigned C_INT32>::elementType *itPivot = pivot.array();
  CVector<unsigned C_INT32>::elementType *endPivot = itPivot + (last - first);

  for (; itPivot != endPivot; ++itToBeSorted, ++itPivot)
    *itPivot = itToBeSorted->second;

  return;
}

template <typename RandomAccessIterator>
void partialSortWithPivot(RandomAccessIterator first,
                          RandomAccessIterator middle,
                          RandomAccessIterator last,
                          CVector<unsigned C_INT32> & pivot)
{
  assert(first < middle && middle <= last);

  // Initialize the two column array to be sorted
  CVector<std::pair<RandomAccessIterator, unsigned C_INT32> > ToBeSorted;
  ToBeSorted.resize(last - first);

  RandomAccessIterator it;
  unsigned C_INT32 i;

  CVector<std::pair<RandomAccessIterator, unsigned C_INT32> >::elementType * itToBeSorted;

  for (it = first, i = 0, itToBeSorted = ToBeSorted.array();
       it != last;
       ++it, ++i, ++itToBeSorted)
    {
      itToBeSorted->first = it;
      itToBeSorted->second = i;
    }

  itToBeSorted = ToBeSorted.array();

  std::partial_sort(itToBeSorted,
                    itToBeSorted + (middle - first),
                    itToBeSorted + (last - first),
                    &sortDefault<RandomAccessIterator>);

  // Copy the resulting pivots to the pivot vector.
  pivot.resize(last - first);
  CVector<unsigned C_INT32>::elementType *itPivot = pivot.array();
  CVector<unsigned C_INT32>::elementType *endPivot = itPivot + (last - first);

  for (; itPivot != endPivot; ++itToBeSorted, ++itPivot)
    *itPivot = itToBeSorted->second;

  return;
}

template <typename RandomAccessIterator, typename LessThanCompare>
bool sortSpecified(const std::pair<RandomAccessIterator, unsigned C_INT32> & lhs,
                   const std::pair<RandomAccessIterator, unsigned C_INT32> & rhs)
{return (*LessThanCompare)(*lhs.first, *rhs.first);}

template <typename RandomAccessIterator, typename LessThanCompare>
void sortWithPivot(RandomAccessIterator first,
                   RandomAccessIterator last,
                   LessThanCompare comp,
                   CVector<unsigned C_INT32> & pivot)
{
  assert(first < last);

  // Initialize the two column array to be sorted
  CVector<std::pair<RandomAccessIterator, unsigned C_INT32> > ToBeSorted;
  ToBeSorted.resize(last - first);

  RandomAccessIterator it;
  unsigned C_INT32 i;

  CVector<std::pair<RandomAccessIterator, unsigned C_INT32> >::elementType * itToBeSorted;

  for (it = first, i = 0, itToBeSorted = ToBeSorted.array();
       it != last;
       ++it, ++i, ++itToBeSorted)
    {
      itToBeSorted->first = it;
      itToBeSorted->second = i;
    }

  itToBeSorted = ToBeSorted.array();

  std::sort(itToBeSorted,
            itToBeSorted + (last - first),
            &sortSpecified<RandomAccessIterator>);

  // Copy the resulting pivots to the pivot vector.
  pivot.resize(last - first);
  CVector<unsigned C_INT32>::elementType *itPivot = pivot.array();
  CVector<unsigned C_INT32>::elementType *endPivot = itPivot + (last - first);

  for (; itPivot != endPivot; ++itToBeSorted, ++itPivot)
    *itPivot = itToBeSorted->second;

  return;
}

/**
 * Reorder the elements according to the provided pivots
 * @param const CVector<unsigned C_INT32> & pivot
 * @return bool success
 */
template <typename CType, typename CIndexType, typename CReturnType>
bool applyPivot(const CVector<unsigned C_INT32> & pivot,
                CType *pType,
                CReturnType (CType::*swapElements)(CIndexType, CIndexType))
{
  unsigned C_INT32 size = pivot.size();

  CVector< bool > Applied(size);
  Applied = false;

  unsigned C_INT32 i;
  unsigned C_INT32 to;
  unsigned C_INT32 from;

  for (i = 0; i < size; i++)
    if (!Applied[i])
      {
        to = i;
        from = pivot[i];

        while (from != i)
          {
            (*pType.*swapElements)(to, from);
            Applied[to] = true;

            to = from;
          }

        Applied[to] = true;
      }

  return true;
}

#endif // COPASI_CSort
