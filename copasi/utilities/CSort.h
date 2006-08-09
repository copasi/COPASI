/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSort.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/09 15:05:37 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CSort
#define COPASI_CSort

#include <algorithm>
#include <float.h>

#include "CVector.h"

/**
 * The base functor providing the default compare method for the
 * sorting methods. This default comparison is done with the
 * operator <. to mimic the behaviour of STL sort algorithms
 */
template <typename RandomAccessIterator>
class FCompareBase
  {
  public:
    /**
     * Operator wrapping the comparison operator <
     * @param const std::pair<RandomAccessIterator, unsigned C_INT32> & lhs
     * @param const std::pair<RandomAccessIterator, unsigned C_INT32> & rhs
     * @return bool lessThan
     */
    virtual bool operator() (const std::pair<RandomAccessIterator, unsigned C_INT32> & lhs,
                             const std::pair<RandomAccessIterator, unsigned C_INT32> & rhs)
    {
      return
      isnan(*lhs.first) ?
      (isnan(*rhs.first) ? lhs.first < rhs.first : false) :
          (isnan(*rhs.first) ? true : *lhs.first < *rhs.first);
    }
  };

/**
 * This functor provids the means to specify a compare method
 * for the sorting methods.
 */
template <typename RandomAccessIterator , typename LessThanCompare>
class FCompare : FCompareBase<RandomAccessIterator>
  {
  protected:
    /**
     * Default constructor
     */
    FCompare() {}

  public:
    /**
     * Specific constructor
     * @param LessThanCompare method
     */
    FCompare(LessThanCompare method):
    mpCompare(method)
    {}

    /**
     * Operator wrapping the coparison method
     * @param const std::pair<RandomAccessIterator, unsigned C_INT32> & lhs
     * @param const std::pair<RandomAccessIterator, unsigned C_INT32> & rhs
     * @return bool lessThan
     */
    virtual bool operator() (const std::pair<RandomAccessIterator, unsigned C_INT32> & lhs,
                             const std::pair<RandomAccessIterator, unsigned C_INT32> & rhs)
    {return (*mpCompare)(*lhs.first, *rhs.first);}

  private:
    /**
     * A pointer to the wrapped compare method.
     */
    LessThanCompare mpCompare;
  };

/**
 * Sorting method returning a pivot vector instead of performing the sort.
 * The underlying sorting method is std::sort with the operator < used for
 * comparison .
 * @param RandomAccessIterator first
 * @param RandomAccessIterator last
 * @param CVector<unsigned C_INT32> & pivot
 */
template <typename RandomAccessIterator>
void sortWithPivot(RandomAccessIterator first,
                   RandomAccessIterator last,
                   CVector<unsigned C_INT32> & pivot)
{
  FCompareBase<RandomAccessIterator> Compare;

  __sortWithPivot(first, last, Compare, pivot);

  return;
}

/**
 * Sorting method returning a pivot vector instead of performing the sort.
 * The underlying sorting method is std::sort with the specified compare
 * method used for comparison .
 * @param RandomAccessIterator first
 * @param RandomAccessIterator last
 * @param LessThanCompare method
 * @param CVector<unsigned C_INT32> & pivot
 */
template <typename RandomAccessIterator, typename LessThanCompare>
void sortWithPivot(RandomAccessIterator first,
                   RandomAccessIterator last,
                   LessThanCompare method,
                   CVector<unsigned C_INT32> & pivot)
{
  FCompare<RandomAccessIterator, LessThanCompare> Compare(method);

  __sortWithPivot(first, last, Compare, pivot);

  return;
}

/**
 * The actual implementation of the sortWithPivot algorithm.
 * @param RandomAccessIterator first
 * @param RandomAccessIterator last
 * @param FCompareBase<RandomAccessIterator> & compare
 * @param CVector<unsigned C_INT32> & pivot
 */
template <typename RandomAccessIterator>
void __sortWithPivot(RandomAccessIterator first,
                     RandomAccessIterator last,
                     FCompareBase<RandomAccessIterator> & compare,
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

/**
 * Partial sorting method returning a pivot vector instead of performing
 * the sort. The underlying sorting method is std::partial sort with the
 * operator < used for * comparison .
 * @param RandomAccessIterator first
 * @param RandomAccessIterator middle
 * @param RandomAccessIterator last
 * @param CVector<unsigned C_INT32> & pivot
 */
template <typename RandomAccessIterator>
void partialSortWithPivot(RandomAccessIterator first,
                          RandomAccessIterator middle,
                          RandomAccessIterator last,
                          CVector<unsigned C_INT32> & pivot)
{
  FCompareBase<RandomAccessIterator> Compare;

  __partialSortWithPivot(first, middle, last, Compare, pivot);

  return;
}

/**
 * Partial sorting method returning a pivot vector instead of performing the
 * sort. The underlying sorting method is std::partial_sort with the specified
 * compare method used for comparison .
 * @param RandomAccessIterator first
 * @param RandomAccessIterator middle
 * @param RandomAccessIterator last
 * @param LessThanCompare method
 * @param CVector<unsigned C_INT32> & pivot
 */
template <typename RandomAccessIterator, typename LessThanCompare>
void partialSortWithPivot(RandomAccessIterator first,
                          RandomAccessIterator middle,
                          RandomAccessIterator last,
                          LessThanCompare method,
                          CVector<unsigned C_INT32> & pivot)
{
  FCompare<RandomAccessIterator, LessThanCompare> Compare(method);

  __partialSortWithPivot(first, middle, last, Compare, pivot);

  return;
}

/**
 * The actual implementation of the partialSortWithPivot algorithm.
 * @param RandomAccessIterator first
 * @param RandomAccessIterator middle
 * @param RandomAccessIterator last
 * @param FCompareBase<RandomAccessIterator> & compare
 * @param CVector<unsigned C_INT32> & pivot
 */
template <typename RandomAccessIterator>
void __partialSortWithPivot(RandomAccessIterator first,
                            RandomAccessIterator middle,
                            RandomAccessIterator last,
                            FCompareBase<RandomAccessIterator> & compare,
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
 * The base functor providing a swap method used in the applyPivot methods.
 */
template <typename IndexType, typename ReturnType>
class FSwapBase
  {
  protected:
    /**
     * Default constructor
     */
    FSwapBase() {}

  public:
    /**
     * Specific constructor
     * @param ReturnType (*swap) (IndexType, IndexType)
     */
    FSwapBase(ReturnType (*swap) (IndexType, IndexType)):
        mpSwap(swap)
    {}

    /**
     * Operator wrapping the provided swap method
     * @param IndexType to
     * @param IndexType from
     * @return ReturnType
     */
    virtual void operator() (IndexType to, IndexType from)
    {
      (*mpSwap)(to, from);
      return;
    }

  private:
    /**
     * A pointer to the swap method
     */
    ReturnType (*mpSwap)(IndexType, IndexType);
  };

/**
 * A derived functor providing means to use a class member as the swap method
 * to be used in the applyPivot methods.
 */
template <typename ClassType, typename IndexType, typename ReturnType>
class FSwapClass : public FSwapBase<IndexType, ReturnType>
  {
  protected:
    /**
     * Default constructor
     */
    FSwapClass() {}

  public:
    /**
     * Specific constructor
     * @param ClassType * pType
     * @param ReturnType (ClassType::*swap) (IndexType, IndexType)
     */
    FSwapClass(ClassType * pType, ReturnType (ClassType::*swap) (IndexType, IndexType)):
        FSwapBase<IndexType, ReturnType>(),
        mpType(pType),
        mpSwap(swap)
    {}

    /**
     * Operator wrapping the provided class member swap method
     * @param IndexType to
     * @param IndexType from
     * @return ReturnType
     */
    virtual void operator() (IndexType to, IndexType from)
    {
      (*mpType.*mpSwap)(to, from);
      return;
    }

  private:
    /**
     * A pointer to the class.
     */
    ClassType * mpType;

    /**
     * A pointer to the class member swap method.
     */
    ReturnType (ClassType::*mpSwap)(IndexType, IndexType);
  };

/**
 * Reorder the elements according to the provided pivots
 * The swap method must be of the form:
 *   ReturnType operator() (unsigned C_INT32 to, unsigned C_INT32 from)
 * where the ReturnType is not used and therefore arbitrary. Objects of
 * type FSwapBase are suitable candidates.
 * @param const CVector<unsigned C_INT32> & pivot
 * @param SwapMethod swap
 * @return bool success
 */
template <typename SwapMethod>
bool applyPivot(const CVector<unsigned C_INT32> & pivot,
                SwapMethod swap)
{
  CVector< bool > Applied(pivot.size());
  Applied = false;

  unsigned C_INT32 i, imax = pivot.size();
  unsigned C_INT32 to;
  unsigned C_INT32 from;

  for (i = 0; i < imax; i++)
    if (!Applied[i])
      {
        to = i;
        from = pivot[to];

        while (from != i)
          {
            swap(to, from);
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
 * The swap method must be of the form:
 *   ReturnType operator() (unsigned C_INT32 to, unsigned C_INT32 from)
 * where the ReturnType is not used and therefore arbitrary. Objects of
 * type FSwapBase are suitable candidates.
 * @param const CVector<unsigned C_INT32> & pivot
 * @param const unsigned C_INT32 & ordered
 * @param SwapMethod swap
 * @return bool success
 */
template <typename SwapMethod>
bool applyPartialPivot(const CVector<unsigned C_INT32> & pivot,
                       const unsigned C_INT32 & ordered,
                       SwapMethod swap)
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
                swap(to, from);
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
