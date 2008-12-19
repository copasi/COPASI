// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CVector.h,v $
//   $Revision: 1.36.6.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/11/06 08:03:02 $
// End CVS Header

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

template <typename CType> class CVector;

template <typename CType>
std::ostream &operator<<(std::ostream &os, const CVector< CType > & A);

/**
 * Template class CVector < class CType >
 * This template class is a simple vector class  allowing standard
 * C-style and fortran style access to the elements. It also supplies
 * an ostream operator.
 */
template <class CType> class CVector
  {
  public:
    typedef CType elementType;

    // Attributes
  private:
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
     * @param unsigned C_INT32 size (default = 0)
     */
    CVector(unsigned C_INT32 size = 0) :
        mSize(0),
        mVector(NULL)
    {resize(size);}

    /**
     * Copy constructor
     * @param const CVector <CType> & src
     */
    CVector(const CVector <CType> & src):
        mSize(0),
        mVector(NULL)
    {
      resize(src.mSize);

      if (mSize)
        memcpy(mVector, src.mVector, mSize * sizeof(CType));
    }

    /**
     * Destructor.
     */
    ~CVector()
  {if (mVector) delete [] mVector;}

    /**
     * The number of elements stored in the vector.
     * @return unsigned C_INT32 size
     */
    unsigned C_INT32 size() const {return mSize;}

    /**
     * Resize the vector. The previous content is lost
     * @param unsigned C_INT32 size
     */
    void resize(unsigned C_INT32 size)
    {
      //TODO: maybe we should only resize if the vector gets bigger
      //or much smaller?
      if (size == mSize) return;

      if (mVector)
        {
          delete [] mVector;
          mVector = NULL;
        }

      mSize = size;

      if (mSize)
        {
          try
            {
              mVector = new CType[mSize];
            }

          catch (...)
            {
              mVector = NULL;
            }

          if (mVector == NULL)
            {
              mSize = 0;
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCopasiBase + 1, size * sizeof(CType));
            }
        }

      //TODO: maybe we should only resize if the vector gets bigger
      //or much smaller?
    }

    /**
     * Assignement operator
     * @param const CVector <CType> & rhs
     * @return CVector <CType> & lhs
     */
    CVector <CType> & operator = (const CVector <CType> & rhs)
    {
      if (this == &rhs)
        {
          return * this;
        }
      if (mSize != rhs.mSize) resize(rhs.mSize);

      memcpy(mVector, rhs.mVector, mSize * sizeof(CType));

      return * this;
    }

    /**
     * Assignement operator
     * @param const CType & value
     * @return CVector <CType> & lhs
     */
    CVector< CType > & operator = (const CType & value)
    {
      unsigned C_INT32 i;
      CType * tmp = mVector;

      for (i = 0; i < mSize; i++, tmp++) *tmp = value;

      return *this;
    }

    /**
     * Retrieve an element of the vector
     * @param const unsigned C_INT32 & row
     * @return CType & element
     */
    inline CType & operator[](const unsigned C_INT32 & row)
  {return * (mVector + row);}

    /**
     * Retrieve an element of the vector
     * @param const unsigned C_INT32 & row
     * @return const CType & element
     */
    inline const CType & operator[](const unsigned C_INT32 & row) const
      {return * (mVector + row);}

    /**
     * Retrieve a vector element using Fortan style indexing.
     * @param const unsigned C_INT32 & row
     * @return const CType & element
     */
    inline CType & operator()(const unsigned C_INT32 & row)
    {return * (mVector + (row - 1));}

    /**
     * Retrieve a vector element using Fortan style indexing.
     * @param const unsigned C_INT32 & row
     * @return const CType & element
     */
    inline const CType & operator()(const unsigned C_INT32 & row) const
      {return * (mVector + (row - 1));}

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
     * Reorder the elements according to the provided pivots
     * @param const CVector<unsigned C_INT32> & pivot
     * @return bool success
     */
    bool applyPivot(const CVector<unsigned C_INT32> & pivot)
    {
      if (pivot.size() != mSize) return false;

      CVector< bool > Applied(mSize);
      Applied = false;
      CType tmp;

      unsigned C_INT32 i;
      unsigned C_INT32 to;
      unsigned C_INT32 from;

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

      return true;
    }

    /**
     * Output stream operator
     * @param ostream & os
     * @param const CVector< CType > & A
     * @retrun ostream & os
     */
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
    friend std::ostream &operator << (std::ostream &os,
                                      const CVector< CType > & A);
#else
    friend std::ostream &operator << <> (std::ostream &os,
                                         const CVector< CType > & A);
#endif // WIN32
  };

template <class CType>
std::ostream &operator<<(std::ostream &os, const CVector< CType > & A)
{
  os << "(\t";

  if (A.mSize)
    {
      unsigned C_INT32 i;
      CType * tmp = A.mVector;
      os << * (tmp++);

      for (i = 1; i < A.mSize; i++)
        os << "\t" << * (tmp++);
    }

  os << "\t)";
  return os;
}

#endif // COPASI_CVector
