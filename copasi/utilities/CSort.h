// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CSort
#define COPASI_CSort

#include <cmath>
#include <algorithm>
#include <functional>

#include "copasi/core/CVector.h"

template<typename RandomAccessIterator>
class CompareDefault
{
public:
  /**
   * Constructor
   */
  CompareDefault() {};

  /**
   * Virtual destructor
   */
  virtual ~CompareDefault() {};

  bool operator()(const std::pair< RandomAccessIterator, size_t > & lhs,
                  const std::pair< RandomAccessIterator, size_t > & rhs)
  {
    return *lhs.first < *rhs.first;
  }
};

class CompareDoubleWithNaN
{
public:
  /**
   * Constructor
   */
  CompareDoubleWithNaN() {};

  /**
   * Virtual destructor
   */
  virtual ~CompareDoubleWithNaN() {};

  bool operator()(const std::pair< C_FLOAT64 *, size_t > & lhs,
                  const std::pair< C_FLOAT64 *, size_t > & rhs)
  {
    return
      std::isnan(*lhs.first) ?
      (std::isnan(*rhs.first) ? lhs.first < rhs.first : false) :
      (std::isnan(*rhs.first) ? true : *lhs.first < *rhs.first);
  }
};

/**
 * Sorting method returning a pivot vector instead of performing the sort.
 * The underlying sorting method is std::sort with the operator < used for
 * comparison .
 * @param RandomAccessIterator first
 * @param RandomAccessIterator last
 * @param CVector<size_t> & pivot
 */
template <typename RandomAccessIterator>
void sortWithPivot(RandomAccessIterator first,
                   RandomAccessIterator last,
                   CVector<size_t> & pivot)
{
  CompareDefault<RandomAccessIterator> Compare;

  sortWithPivot(first, last, Compare, pivot);

  return;
}

/**
 * Sorting method returning a pivot vector instead of performing the sort.
 * The underlying sorting method is std::sort with the specified compare
 * method used for comparison .
 * @param RandomAccessIterator first
 * @param RandomAccessIterator last
 * @param LessThanCompare method
 * @param CVector<size_t> & pivot
 */
template <typename RandomAccessIterator, typename LessThanCompare>
void sortWithPivot(RandomAccessIterator first,
                   RandomAccessIterator last,
                   LessThanCompare compare,
                   CVector<size_t> & pivot)
{
  assert(first < last);

  // Initialize the two column array to be sorted
  CVector<std::pair<RandomAccessIterator, size_t> > ToBeSorted;
  ToBeSorted.resize(last - first);

  RandomAccessIterator it;
  size_t i;

  typename std::pair<RandomAccessIterator, size_t> * itToBeSorted;

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
  CVector<size_t>::elementType *itPivot = pivot.array();
  CVector<size_t>::elementType *endPivot = itPivot + (last - first);

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
 * @param CVector<size_t> & pivot
 */
template <typename RandomAccessIterator>
void partialSortWithPivot(RandomAccessIterator first,
                          RandomAccessIterator middle,
                          RandomAccessIterator last,
                          CVector<size_t> & pivot)
{
  CompareDefault<RandomAccessIterator> Compare;

  partialSortWithPivot(first, middle, last, Compare, pivot);

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
 * @param CVector<size_t> & pivot
 */
template <typename RandomAccessIterator, typename LessThanCompare>
void partialSortWithPivot(RandomAccessIterator first,
                          RandomAccessIterator middle,
                          RandomAccessIterator last,
                          LessThanCompare compare,
                          CVector<size_t> & pivot)
{
  assert(first < middle && middle <= last);

  // Initialize the two column array to be sorted
  CVector<std::pair<RandomAccessIterator, size_t> > ToBeSorted;
  ToBeSorted.resize(last - first);

  RandomAccessIterator it;
  size_t i;

  typename std::pair<RandomAccessIterator, size_t> * itToBeSorted;

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
  CVector<size_t>::elementType *itPivot = pivot.array();
  CVector<size_t>::elementType *endPivot = itPivot + (last - first);

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
  FSwapBase():
    mpSwap(NULL)
  {}

public:
  /**
   * Specific constructor
   * @param ReturnType (*swap) (IndexType, IndexType)
   */
  FSwapBase(ReturnType(*swap)(IndexType, IndexType)):
    mpSwap(swap)
  {}

  /**
   * Virtual destructor
   */
  virtual ~FSwapBase() {};

  /**
   * Operator wrapping the provided swap method
   * @param IndexType to
   * @param IndexType from
   * @return ReturnType
   */
  virtual void operator()(IndexType to, IndexType from)
  {
    (*mpSwap)(to, from);
    return;
  }

private:
  /**
   * A pointer to the swap method
   */
  ReturnType(*mpSwap)(IndexType, IndexType);
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
  FSwapClass():
    FSwapBase<IndexType, ReturnType>(),
    mpType(NULL),
    mpSwap(NULL)
  {}

public:
  /**
   * Specific constructor
   * @param ClassType * pType
   * @param ReturnType (ClassType::*swap) (IndexType, IndexType)
   */
  FSwapClass(ClassType * pType, ReturnType(ClassType::*swap)(IndexType, IndexType)):
    FSwapBase<IndexType, ReturnType>(),
    mpType(pType),
    mpSwap(swap)
  {}

  /**
   * Virtual destructor
   */
  virtual ~FSwapClass() {};

  /**
   * Operator wrapping the provided class member swap method
   * @param IndexType to
   * @param IndexType from
   * @return ReturnType
   */
  virtual void operator()(IndexType to, IndexType from)
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
  ReturnType(ClassType::*mpSwap)(IndexType, IndexType);
};

/**
 * Reorder the elements according to the provided pivots
 * The swap method must be of the form:
 *   ReturnType operator() (size_t to, size_t from)
 * where the ReturnType is not used and therefore arbitrary. Objects of
 * type FSwapBase are suitable candidates.
 * @param const CVector<size_t> & pivot
 * @param SwapMethod swap
 * @return bool success
 */
template <typename SwapMethod>
bool applyPivot(const CVector<size_t> & pivot,
                SwapMethod swap)
{
  CVector< bool > Applied(pivot.size());
  Applied = false;

  size_t i, imax = pivot.size();
  size_t to;
  size_t from;

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
 *   ReturnType operator() (size_t to, size_t from)
 * where the ReturnType is not used and therefore arbitrary. Objects of
 * type FSwapBase are suitable candidates.
 * @param const CVector<size_t> & pivot
 * @param const size_t & ordered
 * @param SwapMethod swap
 * @return bool success
 */
template <typename SwapMethod>
bool applyPartialPivot(const CVector<size_t> & pivot,
                       const size_t & ordered,
                       SwapMethod swap)
{
  CVector< bool > Applied(pivot.size());
  Applied = false;

  size_t i;
  size_t to;
  size_t from;

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
