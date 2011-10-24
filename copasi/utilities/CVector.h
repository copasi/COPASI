// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CVector.h,v $
//   $Revision: 1.41.2.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/10/24 18:46:42 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CVector
#define COPASI_CVector

#include <iostream>
#include <string.h>
#include <limits>

#include "copasi.h"
#include "utilities/CCopasiMessage.h"

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

  // Operations
public:
  /**
   * Default constructor
   */
  CVectorCore() :
      mSize(0),
      mVector(NULL)
  {}

  /**
   * Specific constructor
   * @param const size_t & size
   * @param CType * vector
   */
  CVectorCore(const size_t & size,
              CType * vector):
      mSize(size),
      mVector(vector)
  {}

  /**
   * Destructor.
   */
  ~CVectorCore()
  {}

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
      CVectorCore< CType >()
  {resize(size);}

  /**
   * Copy constructor
   * @param const CVector <CType> & src
   */
  CVector(const CVector <CType> & src):
      CVectorCore< CType >()
  {
    resize(src.CVectorCore< CType >::mSize);

    if (CVectorCore< CType >::mSize)
      memcpy(CVectorCore< CType >::mVector,
             src.CVectorCore< CType >::mVector, CVectorCore< CType >::mSize * sizeof(CType));
  }

  /**
   * Destructor.
   */
  ~CVector()
  {if (CVectorCore< CType >::mVector) delete [] CVectorCore< CType >::mVector;}

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
            if ((C_FLOAT64) CVectorCore< CType >::mSize *(C_FLOAT64) sizeof(CType) >= (C_FLOAT64) std::numeric_limits< size_t >::max())
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
        memcpy(CVectorCore< CType >::mVector, OldVector, std::min(CVectorCore< CType >::mSize, OldSize) * sizeof(CType));
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

  /**
   * Assignment operator
   * @param const CVector <CType> & rhs
   * @return CVector <CType> & lhs
   */
  CVector <CType> & operator = (const CVector <CType> & rhs)
  {
    if (this == &rhs)
      {
        return * this;
      }

    if (CVectorCore< CType >::mSize != rhs.CVectorCore< CType >::mSize)
      resize(rhs.CVectorCore< CType >::mSize);

    memcpy(CVectorCore< CType >::mVector,
           rhs.CVectorCore< CType >::mVector,
           CVectorCore< CType >::mSize * sizeof(CType));

    return * this;
  }

  /**
   * Assignment operator
   * @param const CType & value
   * @return CVector <CType> & lhs
   */
  CVector< CType > & operator = (const CType & value)
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
   * Reorder the elements according to the provided pivots
   * @param const CVector<size_t> & pivot
   * @return bool success
   */
  bool applyPivot(const CVector<size_t> & pivot)
  {
    if (pivot.size() != CVectorCore< CType >::mSize) return false;

    CVector< bool > Applied(CVectorCore< CType >::mSize);
    Applied = false;
    CType tmp;

    size_t i;
    size_t to;
    size_t from;

    for (i = 0; i < CVectorCore< CType >::mSize; i++)
      if (!Applied[i])
        {
          to = i;
          from = pivot[i];

          if (to != from)
            {
              tmp = CVectorCore< CType >::mVector[i];

              while (from != i)
                {
                  CVectorCore< CType >::mVector[to] = CVectorCore< CType >::mVector[from];
                  Applied[to] = true;

                  to = from;
                  from = pivot[to];
                }

              CVectorCore< CType >::mVector[to] = tmp;
            }

          Applied[to] = true;
        }

    return true;
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
