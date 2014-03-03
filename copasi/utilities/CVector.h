// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CVector
#define COPASI_CVector

#include <algorithm> // for std::min
#include <iostream>
#include <string.h>
#include <limits>

#include "copasi.h"
#include "utilities/CCopasiMessage.h"

#undef min
#undef max

template <typename CType> class CVectorCore;

template <typename CType>
std::ostream &operator<<(std::ostream &os, const CVectorCore< CType > & A);

template <class CType> class CVectorCore
{
public:
  typedef CType elementType;

  // Attributes
protected:
  /**
   * Size of the vector.
   */
  size_t mSize;

  /**
   * The array storing the vector elements
   */
  CType * mVector;

public:
  // Operations
  /**
   * Specific constructor
   * @param const size_t & size (default: 0)
   * @param CType * vector (default: NULL)
   */
  CVectorCore(const size_t & size = 0,
              CType * vector = NULL):
    mSize(size),
    mVector(vector)
  {}

private:
  /**
   * Copy constructor
   * @param const CVectorCore< CType > & src
   */
  CVectorCore(const CVectorCore< CType > & src):
    mSize(src.mSize),
    mVector(src.mVector)
  {}

public:
  /**
   * Destructor.
   */
  ~CVectorCore()
  {}

  /**
   * Initialize the core vector to reference an externally allocated array
   * @param const size_t & size
   * @param CType * vector
   */
  void initialize(const size_t & size,
                  CType * vector)
  {
    mSize = size;
    mVector = vector;
  }

  /**
   * Initialize the core vector to reference an other core vector.
   * @param const size_t & size
   * @param CType * vector
   */
  void initialize(const CVectorCore< CType > & src)
  {
    mSize = src.mSize;
    mVector = src.mVector;
  }

  /**
   * Assignment operator
   * @param const CVectorCore <CType> & rhs
   * @return CVector <CType> & lhs
   */
  CVectorCore< CType > & operator = (const CVectorCore <CType> & rhs)
  {
    // Nothing to do
    if (this == &rhs ||
        (mVector == rhs.mVector && mSize == rhs.mSize))
      {
        return *this;
      }

    // Behave like the assignment operator of CVector if the sizes match
    if (mVector != rhs.mVector &&
        mSize == rhs.mSize &&
        mSize > 0)
      {
        memcpy((void *) mVector, (void *) rhs.array(), mSize * sizeof(CType));
        return *this;
      }

    // We should never use the assignment operator unless the vectors are identical
    // or the vector of values can be copied. If we reach this code we probably should
    // have used initialize(rhs).
    assert(false);

    return *this;
  }

  /**
   * Retrieve the array of the vector elements. This is suitable
   * for interfacing with clapack routines.
   * @return CType * array
   */
  CType * array() {return mVector;}

  /**
   * Retrieve the array of the vector elements. This is suitable
   * for interfacing with clapack routines.
   * @return const CType * array
   */
  const CType * array() const {return mVector;}

  /**
   * Assignment operator
   * @param const CType & value
   */
  CVectorCore< CType> & operator = (const CType & value)
  {
    size_t i;
    CType * tmp = mVector;

    for (i = 0; i < mSize; i++, tmp++)
      {
        *tmp = value;
      }

    return *this;
  }

  /**
   * The number of elements stored in the vector.
   * @return size_t size
   */
  size_t size() const {return mSize;}

  /**
   * Retrieve an element of the vector
   * @param const size_t & row
   * @return CType & element
   */
  inline CType & operator[](const size_t & row)
  {return *(mVector + row);}

  /**
   * Retrieve an element of the vector
   * @param const size_t & row
   * @return const CType & element
   */
  inline const CType & operator[](const size_t & row) const
  {return *(mVector + row);}

  /**
   * Retrieve a vector element using Fortan style indexing.
   * @param const size_t & row
   * @return const CType & element
   */
  inline CType & operator()(const size_t & row)
  {return *(mVector + (row - 1));}

  /**
   * Retrieve a vector element using Fortan style indexing.
   * @param const size_t & row
   * @return const CType & element
   */
  inline const CType & operator()(const size_t & row) const
  {return *(mVector + (row - 1));}

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CVector< CType > & A
   * @return ostream & os
   */
#if defined SWIG
  friend std::ostream &operator << (std::ostream &os,
                                    const CVectorCore< CType > & A);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend std::ostream &operator << (std::ostream &os,
                                    const CVectorCore< CType > & A);
#else
  friend std::ostream &operator << <> (std::ostream &os,
                                       const CVectorCore< CType > & A);
#endif // WIN32
#endif // SWIG

  /**
   * Reorder the elements according to the provided pivots
   * @param const CVectorCore<size_t> & pivot
   * @return bool success
   */
  bool applyPivot(const CVectorCore<size_t> & pivot)
  {
    if (pivot.size() != mSize) return false;

    bool * pApplied = new bool[mSize];
    CVectorCore < bool > Applied(mSize, pApplied);

    Applied = false;
    CType tmp;

    size_t i;
    size_t to;
    size_t from;

    for (i = 0; i < mSize; i++)
      if (!Applied[i])
        {
          to = i;
          from = pivot[i];

          if (to != from)
            {
              tmp = mVector[i];

              while (from != i)
                {
                  mVector[to] = mVector[from];
                  Applied[to] = true;

                  to = from;
                  from = pivot[to];
                }

              mVector[to] = tmp;
            }

          Applied[to] = true;
        }

    delete [] pApplied;

    return true;
  }
};

/**
 * Template class CVector < class CType >
 * This template class is a simple vector class  allowing standard
 * C-style and fortran style access to the elements. It also supplies
 * an ostream operator.
 */
template <class CType> class CVector : public CVectorCore< CType >
{
  // Operations
public:
  /**
   * Default constructor
   * @param size_t size (default = 0)
   */
  CVector(size_t size = 0) :
    CVectorCore< CType >(0, NULL)
  {
    resize(size);
  }

  /**
   * Copy constructor
   * @param const CVectorCore <CType> & src
   */
  CVector(const CVectorCore <CType> & src):
    CVectorCore< CType >(0, NULL)
  {
    copy(src);
  }

  /**
   * Copy constructor
   * @param const CVector <CType> & src
   */
  CVector(const CVector <CType> & src):
    CVectorCore< CType >(0, NULL)
  {
    copy(src);
  }

  /**
   * Destructor.
   */
  ~CVector()
  {
    if (CVectorCore< CType >::mVector != NULL)
      delete [] CVectorCore< CType >::mVector;
  }

  /**
   * Assignment operator
   * @param const CVectorCore <CType> & rhs
   * @return CVector <CType> & lhs
   */
  CVector< CType > & operator = (const CVectorCore <CType> & rhs)
  {
    copy(rhs);

    return * this;
  }

  /**
   * Assignment operator
   * @param const CType & value
   */
  CVector< CType> & operator = (const CType & value)
  {
    size_t i;
    CType * tmp = CVectorCore< CType >::mVector;

    for (i = 0; i < CVectorCore< CType >::mSize; i++, tmp++)
      {
        *tmp = value;
      }

    return *this;
  }

  /**
   * Resize the vector. The previous content is lost
   * @param size_t size
   */
  void resize(size_t size, const bool & copy = false)
  {
    //TODO: maybe we should only resize if the vector gets bigger
    //or much smaller?
    if (size == CVectorCore< CType >::mSize) return;

    size_t OldSize = CVectorCore< CType >::mSize;
    CType * OldVector = CVectorCore< CType >::mVector;

    //TODO: maybe we should only resize if the vector gets bigger
    //or much smaller?
    CVectorCore< CType >::mSize = size;
    CVectorCore< CType >::mVector = NULL;

    if (CVectorCore< CType >::mSize > 0)
      {
        try
          {
            // We need to detect size_t overflow
            if ((C_FLOAT64) CVectorCore< CType >::mSize * (C_FLOAT64) sizeof(CType) >= (C_FLOAT64) std::numeric_limits< size_t >::max())
              {
                CVectorCore< CType >::mVector = NULL;
              }
            else
              {
                CVectorCore< CType >::mVector = new CType[CVectorCore< CType >::mSize];
              }
          }

        catch (...)
          {
            CVectorCore< CType >::mSize = 0;
            CVectorCore< CType >::mVector = NULL;
          }
      }

    if (copy &&
        CVectorCore< CType >::mVector != NULL &&
        OldVector != NULL)
      {
        memcpy((void *) CVectorCore< CType >::mVector,
               (void *) OldVector,
               std::min(CVectorCore< CType >::mSize, OldSize) * sizeof(CType));
      }

    if (OldVector != NULL)
      {
        delete [] OldVector;
      }

    // Check if allocation failed
    if (CVectorCore< CType >::mVector == NULL &&
        size > 0)
      {
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCopasiBase + 1, size * sizeof(CType));
      }
  }

protected:
  void copy(const CVectorCore <CType> & rhs)
  {
    if (this != &rhs)
      {
        if (CVectorCore< CType >::mSize != rhs.size())
          {
            resize(rhs.size());
          }

        if (CVectorCore< CType >::mSize != 0)
          {
            memcpy((void *) CVectorCore< CType >::mVector,
                   (void *) rhs.array(),
                   CVectorCore< CType >::mSize * sizeof(CType));
          }
      }
  }
};

template <class CType>
std::ostream &operator<<(std::ostream &os, const CVectorCore< CType > & A)
{
  os << "(\t";

  if (A.mSize)
    {
      size_t i;
      CType * tmp = A.mVector;
      os << *(tmp++);

      for (i = 1; i < A.mSize; i++)
        os << "\t" << *(tmp++);
    }

  os << "\t)";
  return os;
}

#endif // COPASI_CVector
