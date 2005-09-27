/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSort.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/27 14:11:04 $
   End CVS Header */

#ifndef COPASI_CSort
 #define COPASI_CSort

#include <algorithm>

#include "CVector.h"

template <typename RandomAccessIterator>
class CCompareFunctorBase
  {
  public:
    bool operator() (const std::pair<RandomAccessIterator, unsigned C_INT32> & lhs,
                     const std::pair<RandomAccessIterator, unsigned C_INT32> & rhs)
    {return *lhs.first < *rhs.first;}
  };

template <typename RandomAccessIterator>
class CCompareFunctor : CCompareFunctorBase<RandomAccessIterator>
  {
  private:
    CCompareFunctor();

  public:
    CCompareFunctor(bool (*method)(const std::pair<RandomAccessIterator, unsigned C_INT32> &,
                                   const std::pair<RandomAccessIterator, unsigned C_INT32> &)):
        mpCompare(method)
    {}

    bool operator() (const std::pair<RandomAccessIterator, unsigned C_INT32> & lhs,
                     const std::pair<RandomAccessIterator, unsigned C_INT32> & rhs)
    {return (*mpCompare)(*lhs.first, *rhs.first);}

  private:
    bool (*mpCompare)(const std::pair<RandomAccessIterator, unsigned C_INT32> &,
                      const std::pair<RandomAccessIterator, unsigned C_INT32> &);
  };

template <typename RandomAccessIterator>
void sortWithPivot(RandomAccessIterator first,
                   RandomAccessIterator last,
                   CVector<unsigned C_INT32> & pivot)
{
  CCompareFunctorBase<RandomAccessIterator> Compare;

  __sortWithPivot(first, last, Compare, pivot);

  return;
}

template <typename RandomAccessIterator, typename LessThanCompare>
void sortWithPivot(RandomAccessIterator first,
                   RandomAccessIterator last,
                   LessThanCompare comp,
                   CVector<unsigned C_INT32> & pivot)
{
  CCompareFunctor<RandomAccessIterator> Compare(comp);

  __sortWithPivot(first, middle, last, Compare, pivot);

  return;
}

template <typename RandomAccessIterator>
void __sortWithPivot(RandomAccessIterator first,
                     RandomAccessIterator last,
                     CCompareFunctorBase<RandomAccessIterator> & compare,
                     CVector<unsigned C_INT32> & pivot)
{
  assert(first < last);

  // Initialize the two column array to be sorted
  CVector<std::pair<RandomAccessIterator, unsigned C_INT32> > ToBeSorted;
  ToBeSorted.resize(last - first);

  RandomAccessIterator it;
  unsigned C_INT32 i;

  typename std::pair<RandomAccessIterator, unsigned C_INT32> * itToBeSorted;

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
            compare);

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
  CCompareFunctorBase<RandomAccessIterator> Compare;

  __partialSortWithPivot(first, middle, last, Compare, pivot);

  return;
}

template <typename RandomAccessIterator, typename LessThanCompare>
void partialSortWithPivot(RandomAccessIterator first,
                          RandomAccessIterator middle,
                          RandomAccessIterator last,
                          LessThanCompare comp,
                          CVector<unsigned C_INT32> & pivot)
{
  CCompareFunctor<RandomAccessIterator> Compare(comp);

  __partialSortWithPivot(first, middle, last, Compare, pivot);

  return;
}

template <typename RandomAccessIterator>
void __partialSortWithPivot(RandomAccessIterator first,
                            RandomAccessIterator middle,
                            RandomAccessIterator last,
                            CCompareFunctorBase<RandomAccessIterator> & compare,
                            CVector<unsigned C_INT32> & pivot)
{
  assert(first < middle && middle <= last);

  // Initialize the two column array to be sorted
  CVector<std::pair<RandomAccessIterator, unsigned C_INT32> > ToBeSorted;
  ToBeSorted.resize(last - first);

  RandomAccessIterator it;
  unsigned C_INT32 i;

  typename std::pair<RandomAccessIterator, unsigned C_INT32> * itToBeSorted;

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
                    compare);

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
  CVector< bool > Applied(pivot.size());
  Applied = false;

  unsigned C_INT32 i;
  unsigned C_INT32 to;
  unsigned C_INT32 from;

  for (i = 0; i < ordered; i++)
    if (!Applied[i])
      {
        to = i;
        from = pivot[to];

        while (from != i)
          {
            (*pType.*swapElements)(to, from);
            Applied[to] = true;

            to = from;
            from = pivot[to];
          }

        Applied[to] = true;
      }

  return true;
}

/**
 * Partial reordering of the first 'ordered' elements according to the
 * provided pivots.
 * @param const CVector<unsigned C_INT32> & pivot
 * @param const unsigned C_INT32 & ordered
 * @return bool success
 */
template <typename CType, typename CIndexType, typename CReturnType>
bool applyPartialPivot(const CVector<unsigned C_INT32> & pivot,
                       const unsigned C_INT32 & ordered,
                       CType *pType,
                       CReturnType (CType::*swapElements)(CIndexType, CIndexType))
{
  CVector< bool > Applied(pivot.size());
  Applied = false;

  unsigned C_INT32 i;
  unsigned C_INT32 to;
  unsigned C_INT32 from;

  for (i = 0; i < ordered; i++)
    if (!Applied[i])
      {
        to = i;
        from = pivot[to];

        while (from != i)
          {
            if (to < ordered || from < ordered)
              {
                (*pType.*swapElements)(to, from);
                Applied[to] = true;

                to = from;
              }

            from = pivot[from];
          }

        Applied[to] = true;
      }

  return true;
}

#endif // COPASI_CSort
