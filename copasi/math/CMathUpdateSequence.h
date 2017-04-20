// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathUpdateSequence
#define COPASI_CMathUpdateSequence

#include <vector>
#include <set>
#include <cstddef>

#include "copasi/core/CVector.h"

class CMathContainer;
class CObjectInterface;
class CMathObject;

class CMathUpdateSequence : protected CVector< CObjectInterface * >
{
public:
  typedef CObjectInterface ** iterator;
  typedef CObjectInterface *const * const_iterator;

  /**
   * Default Constructor
   * @param CMathContainer * pContainer (default: NULL)
   */
  CMathUpdateSequence(CMathContainer * pContainer = NULL);

  /**
   * Copy Constructor
   * @param const CMathUpdateSequence & src
   * @param CMathContainer * pContainer (default: NULL)
   */
  CMathUpdateSequence(const CMathUpdateSequence & src, CMathContainer * pContainer = NULL);

  /**
   * Destructor
   */
  virtual ~CMathUpdateSequence();

  /**
   * Assignment operator
   * @param const CMathUpdateSequence & rhs
   */
  CMathUpdateSequence & operator = (const CMathUpdateSequence & rhs);

  /**
   * Assignment operator
   * @param const std::vector< CObjectInterface * > & rhs
   */
  CMathUpdateSequence & operator = (const std::vector< CObjectInterface * > & rhs);

  void insert(const iterator & loc, const CObjectInterface * pObject);

  template < typename InputIterator >
  void insert(const iterator & loc, InputIterator first, InputIterator last)
  {
    size_t ToBeInserted = 0;

    for (InputIterator it = first; it != last; ++it, ++ToBeInserted) {}

    size_t Index = loc - CVectorCore< CObjectInterface * >::mpBuffer;

    if (ToBeInserted == 0 ||
        CVectorCore< CObjectInterface * >::mSize < Index) return;

    size_t OldSize = CVectorCore< CObjectInterface * >::mSize;
    CObjectInterface ** pOldBuffer = CVectorCore< CObjectInterface * >::mpBuffer;

    CVectorCore< CObjectInterface * >::mSize = OldSize + ToBeInserted;
    CVectorCore< CObjectInterface * >::mpBuffer = NULL;

    if (CVectorCore< CObjectInterface * >::mSize > 0)
      {
        try
          {
            // We need to detect size_t overflow
            if ((C_FLOAT64) CVectorCore< CObjectInterface * >::mSize * (C_FLOAT64) sizeof(CObjectInterface *) >= (C_FLOAT64) std::numeric_limits< size_t >::max())
              {
                CVectorCore< CObjectInterface * >::mpBuffer = NULL;
              }
            else
              {
                CVectorCore< CObjectInterface * >::mpBuffer = new CObjectInterface *[CVectorCore< CObjectInterface * >::mSize];
              }
          }

        catch (...)
          {
            CVectorCore< CObjectInterface * >::mSize = 0;
            CVectorCore< CObjectInterface * >::mpBuffer = NULL;
          }
      }

    if (CVectorCore< CObjectInterface * >::mpBuffer != NULL)
      {
        if (pOldBuffer != NULL)
          {
            memcpy((void *) CVectorCore< CObjectInterface * >::mpBuffer,
                   (void *) pOldBuffer,
                   std::min(CVectorCore< CObjectInterface * >::mSize, Index) * sizeof(CObjectInterface *));
          }

        iterator Insert = CVectorCore< CObjectInterface * >::mpBuffer + Index;

        for (; first != last; ++first, ++Insert)
          {
            *Insert = *first;
          }

        if (pOldBuffer != NULL)
          {
            memcpy((void *)(CVectorCore< CObjectInterface * >::mpBuffer + Index + ToBeInserted),
                   (void *)(pOldBuffer + Index),
                   std::min(CVectorCore< CObjectInterface * >::mSize - Index - ToBeInserted, OldSize - Index) * sizeof(CObjectInterface *));
          }
      }

    if (pOldBuffer != NULL)
      {
        delete [] pOldBuffer;
      }

    // Check if allocation failed
    if (CVectorCore< CObjectInterface * >::mpBuffer == NULL &&
        OldSize + ToBeInserted > 0)
      {
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCopasiBase + 1, (OldSize + ToBeInserted) * sizeof(CObjectInterface *));
      }
  }

  /**
   * Set the math container
   * @param CMathContainer * pContainer
   */
  void setMathContainer(CMathContainer * pContainer);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  const size_t & size() const;
  bool empty() const;
  void clear();

private:
  CMathContainer * mpContainer;
};

#endif // CMathUpdateSequence
