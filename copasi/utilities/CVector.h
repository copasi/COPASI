/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CVector.h,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/30 14:22:32 $
   End CVS Header */

#ifndef COPASI_CVector
#define COPASI_CVector

#include <iostream>
#include <stdarg.h>
#include "copasi.h"

template<typename CType> class CVector;

template <class CType>
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
     * Number of rows in the vector.
     */
    unsigned C_INT32 mRows;

    /**
     * The array storing the vector elements
     */
    CType * mVector;

    // Operations
  public:
    /**
     * Default constructor
     * @param unsigned C_INT32 rows (default = 0)
     */
    CVector(unsigned C_INT32 rows = 0) :
        mRows(rows),
        mVector(NULL)
    {if (mRows) mVector = new CType[mRows];}

    /**
     * Copy constructor
     * @param const CVector <CType> & src
     */
    CVector(const CVector <CType> & src):
        mRows(src.mRows),
        mVector(NULL)
    {
      if (mRows)
        {
          mVector = new CType[mRows];
          memcpy(mVector, src.mVector, mRows * sizeof(CType));
        }
    }

    /**
     * Initializing constructor
     * @param const unsigned C_INT32 & rows
     * @param CType first
     * @param ... (rows - 1 arguments of CType)
     */
#ifdef XXXX
    CVector(const unsigned C_INT32 & rows, CType first, ...):
        mRows(rows),
        mVector(NULL)
    {
      if (mRows)
        {
          mVector = new CType[mRows];
          mVector[0] = first;

          va_list values; // = NULL;
          va_start(values, first);

#if (CType ==  SubType)
          for (unsigned C_INT32 i = 1; i < mRows; i++)
            mVector[i] = (CType) va_arg(values, int);
#else
          if (sizeof(CType) > sizeof(int))
            for (unsigned C_INT32 i = 1; i < mRows; i++)
              mVector[i] = va_arg(values, CType);
          else /* sizes smaller or equal to int are promoted to int */
            for (unsigned C_INT32 i = 1; i < mRows; i++)
              mVector[i] = (CType) va_arg(values, int);
#endif

          va_end(values);
        }
    }
#endif // XXXX

    /**
     * Destructor.
     */
    ~CVector()
  {if (mVector) delete [] mVector;}

    /**
     * The number of elements stored in the vector.
     * @return unsigned C_INT32 size
     */
    unsigned C_INT32 size() const {return mRows;}

    /**
     * The number of rows of the vector.
     * @return unsigned C_INT32 rows
     */
    unsigned C_INT32 numRows() const {return mRows;}

    /**
     * Resize the vector. The previous content is lost
     * @param unsigned C_INT32 rows
     */
    void resize(unsigned C_INT32 rows)
    {
      //TODO: maybe we should only resize if the vector gets bigger
      //or much smaller?
      if (rows == mRows) return;

      if (mVector)
        {
          delete [] mVector;
          mVector = NULL;
        }

      mRows = rows;

      if (mRows) mVector = new CType[mRows];
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
      if (this == &rhs) {std::cout << "===" << std::endl; return *this;}
      if (mRows != rhs.mRows) resize(rhs.mRows);

      memcpy(mVector, rhs.mVector, mRows * sizeof(CType));

      return * this;
    }

    /**
     * Assignement operator
     * @param const CType & value
     * @return CVector <CType> & lhs
     */
    virtual CVector< CType > & operator = (const CType & value)
    {
      unsigned C_INT32 i;
      CType * tmp = mVector;

      for (i = 0; i < mRows; i++, tmp++) *tmp = value;

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
     * Output stream operator
     * @param ostream & os
     * @param const CVector< CType > & A
     * @retrun ostream & os
     */
#ifdef WIN32
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
  os << "Vector(" << A.mRows << ")" << std::endl;

  unsigned C_INT32 i;
  CType * tmp = A.mVector;

  for (i = 0; i < A.mRows; i++)
    os << "  " << * (tmp++);
  os << std::endl;
  return os;
}

#endif // COPASI_CVector
