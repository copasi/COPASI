// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CVector
#define COPASI_CVector

#include <algorithm> // for std::min
#include <iostream>
#include <string.h>
#include <limits>

#include "copasi/copasi.h"
#include "copasi/utilities/CCopasiMessage.h"

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
  CType * mpBuffer;

public:
  // Operations
  /**
   * Specific constructor
   * @param const size_t & size (default: 0)
   * @param CType * buffer (default: NULL)
   */
  CVectorCore(const size_t & size = 0,
              CType * buffer = NULL):
    mSize(size),
    mpBuffer(buffer)
  {}

private:
  /**
   * Copy constructor.
   * Note, this is intentionally private as this constructor must not be accessed,
   * i.e., do not declare any class or method as friend.
   * @param const CVectorCore< CType > & src
   */
  CVectorCore(const CVectorCore< CType > & src):
    mSize(src.mSize),
    mpBuffer(src.mpBuffer)
  {}

public:
  /**
   * Destructor.
   */
  virtual ~CVectorCore()
  {}

  /**
   * Initialize the core vector to reference an externally allocated array
   * @param const size_t & size
   * @param CType * vector
   */
  void initialize(const size_t & size,
                  const CType * vector)
  {
    mSize = size;
    mpBuffer = const_cast< CType * >(vector);
  }

  /**
   * Initialize the core vector to reference an other core vector.
   * @param const size_t & size
   * @param CType * vector
   */
  void initialize(const CVectorCore< CType > & src)
  {
    mSize = src.mSize;
    mpBuffer = src.mpBuffer;
  }

  /**
   * Assignment operator
   * @param const CVectorCore <CType> & rhs
   * @return CVector <CType> & lhs
   */
  CVectorCore< CType > & operator = (const CVectorCore <CType> & rhs)
  {
    if (this == &rhs)
      return *this;

    // Nothing to do
    if (this == &rhs ||
        (mpBuffer == rhs.mpBuffer && mSize == rhs.mSize))
      {
        return *this;
      }

    // Behave like the assignment operator of CVector if the sizes match
    if (mpBuffer != rhs.mpBuffer &&
        mSize == rhs.mSize)
      {
        if (mSize > 0)
          {
            memcpy((void *) mpBuffer, (void *) rhs.array(), mSize * sizeof(CType));
          }

        return *this;
      }

    // We should never use the assignment operator unless the vectors are identical
    // or the vector of values can be copied. If we reach this code we probably should
    // have used initialize(rhs).
    assert(false);

    return *this;
  }

  bool operator == (const CVectorCore <CType> & rhs) const
  {
    if (mpBuffer != rhs.mpBuffer)
      {
        if (mSize != rhs.mSize)
          {
            return false;
          }

        return memcmp((void *) mpBuffer, (void *) rhs.mpBuffer, mSize * sizeof(CType)) == 0;
      }

    return mSize == rhs.mSize;
  }

  /**
   * Retrieve the array of the vector elements. This is suitable
   * for interfacing with clapack routines.
   * @return CType * array
   */
  CType * array() {return mpBuffer;}

  /**
   * Retrieve the array of the vector elements. This is suitable
   * for interfacing with clapack routines.
   * @return const CType * array
   */
  const CType * array() const {return mpBuffer;}

  /**
   * Retrieve the a pointer to the first vector element.
   * @return CType * pFirst
   */
  CType * begin() {return mpBuffer;}

  /**
   * Retrieve the a pointer to the first vector element.
   * @return const CType * pFirst
   */
  const CType * begin() const {return mpBuffer;}

  /**
   * Retrieve the a pointer beyond the last vector element.
   * @return CType * pEnd
   */
  CType * end() {return mpBuffer + mSize;}

  /**
   * Retrieve the a pointer beyond the last vector element.
   * @return const CType * End
   */
  const CType * end() const {return mpBuffer + mSize;}

  /**
   * Assignment operator
   * @param const CType & value
   */
  CVectorCore< CType> & operator = (const CType & value)
  {
    size_t i;
    CType * tmp = mpBuffer;

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
  {return *(mpBuffer + row);}

  /**
   * Retrieve an element of the vector
   * @param const size_t & row
   * @return const CType & element
   */
  inline const CType & operator[](const size_t & row) const
  {return *(mpBuffer + row);}

  /**
   * Retrieve a vector element using Fortan style indexing.
   * @param const size_t & row
   * @return const CType & element
   */
  inline CType & operator()(const size_t & row)
  {return *(mpBuffer + (row - 1));}

  /**
   * Retrieve a vector element using Fortan style indexing.
   * @param const size_t & row
   * @return const CType & element
   */
  inline const CType & operator()(const size_t & row) const
  {return *(mpBuffer + (row - 1));}

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
              tmp = mpBuffer[i];

              while (from != i)
                {
                  mpBuffer[to] = mpBuffer[from];
                  Applied[to] = true;

                  to = from;
                  from = pivot[to];
                }

              mpBuffer[to] = tmp;
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
  virtual ~CVector()
  {
    if (CVectorCore< CType >::mpBuffer != NULL)
      delete [] CVectorCore< CType >::mpBuffer;
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
   * @param const CVector <CType> & rhs
   * @return CVector <CType> & lhs
   */
  CVector< CType > & operator = (const CVector <CType> & rhs)
  {
    if (this == &rhs)
      return *this;

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
    CType * tmp = CVectorCore< CType >::mpBuffer;

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
    CType * OldVector = CVectorCore< CType >::mpBuffer;

    //TODO: maybe we should only resize if the vector gets bigger
    //or much smaller?
    CVectorCore< CType >::mSize = size;
    CVectorCore< CType >::mpBuffer = NULL;

    if (CVectorCore< CType >::mSize > 0)
      {
        try
          {
            // We need to detect size_t overflow
            if ((C_FLOAT64) CVectorCore< CType >::mSize * (C_FLOAT64) sizeof(CType) >= (C_FLOAT64) std::numeric_limits< size_t >::max())
              {
                CVectorCore< CType >::mpBuffer = NULL;
              }
            else
              {
                CVectorCore< CType >::mpBuffer = new CType[CVectorCore< CType >::mSize];
              }
          }

        catch (...)
          {
            CVectorCore< CType >::mSize = 0;
            CVectorCore< CType >::mpBuffer = NULL;
          }
      }

    if (copy &&
        CVectorCore< CType >::mpBuffer != NULL &&
        OldVector != NULL)
      {
        memcpy((void *) CVectorCore< CType >::mpBuffer,
               (void *) OldVector,
               std::min(CVectorCore< CType >::mSize, OldSize) * sizeof(CType));
      }

    if (OldVector != NULL)
      {
        delete [] OldVector;
      }

    // Check if allocation failed
    if (CVectorCore< CType >::mpBuffer == NULL &&
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
            memcpy((void *) CVectorCore< CType >::mpBuffer,
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
      CType * tmp = A.mpBuffer;
      os << *(tmp++);

      for (i = 1; i < A.mSize; i++)
        os << "\t" << *(tmp++);
    }

  os << "\t)";
  return os;
}

#endif // COPASI_CVector
