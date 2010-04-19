// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CVector.h,v $
//   $Revision: 1.40.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/04/19 17:38:26 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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
  unsigned C_INT32 mSize;

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
   * @param const unsigned C_INT32 & size
   * @param CType * vector
   */
  CVectorCore(const unsigned C_INT32 & size,
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
   * @return unsigned C_INT32 size
   */
  unsigned C_INT32 size() const {return mSize;}

  /**
   * Retrieve an element of the vector
   * @param const unsigned C_INT32 & row
   * @return CType & element
   */
  inline CType & operator[](const unsigned C_INT32 & row)
  {return *(mVector + row);}

  /**
   * Retrieve an element of the vector
   * @param const unsigned C_INT32 & row
   * @return const CType & element
   */
  inline const CType & operator[](const unsigned C_INT32 & row) const
  {return *(mVector + row);}

  /**
   * Retrieve a vector element using Fortan style indexing.
   * @param const unsigned C_INT32 & row
   * @return const CType & element
   */
  inline CType & operator()(const unsigned C_INT32 & row)
  {return *(mVector + (row - 1));}

  /**
   * Retrieve a vector element using Fortan style indexing.
   * @param const unsigned C_INT32 & row
   * @return const CType & element
   */
  inline const CType & operator()(const unsigned C_INT32 & row) const
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
   * @param unsigned C_INT32 size (default = 0)
   */
  CVector(unsigned C_INT32 size = 0) :
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
   * @param unsigned C_INT32 size
   */
  void resize(unsigned C_INT32 size, const bool & copy = false)
  {
    //TODO: maybe we should only resize if the vector gets bigger
    //or much smaller?
    if (size == CVectorCore< CType >::mSize) return;

    unsigned C_INT32 OldSize = CVectorCore< CType >::mSize;
    CType * OldVector = CVectorCore< CType >::mVector;

    //TODO: maybe we should only resize if the vector gets bigger
    //or much smaller?
    CVectorCore< CType >::mSize = size;
    CVectorCore< CType >::mVector = NULL;

    if (CVectorCore< CType >::mSize > 0)
      {
        try
          {
            CVectorCore< CType >::mVector = new CType[CVectorCore< CType >::mSize];
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
    unsigned C_INT32 i;
    CType * tmp = CVectorCore< CType >::mVector;

    for (i = 0; i < CVectorCore< CType >::mSize; i++, tmp++)
      {
        *tmp = value;
      }

    return *this;
  }

  /**
   * Reorder the elements according to the provided pivots
   * @param const CVector<unsigned C_INT32> & pivot
   * @return bool success
   */
  bool applyPivot(const CVector<unsigned C_INT32> & pivot)
  {
    if (pivot.size() != CVectorCore< CType >::mSize) return false;

    CVector< bool > Applied(CVectorCore< CType >::mSize);
    Applied = false;
    CType tmp;

    unsigned C_INT32 i;
    unsigned C_INT32 to;
    unsigned C_INT32 from;

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
      unsigned C_INT32 i;
      CType * tmp = A.mVector;
      os << *(tmp++);

      for (i = 1; i < A.mSize; i++)
        os << "\t" << *(tmp++);
    }

  os << "\t)";
  return os;
}

#endif // COPASI_CVector
