// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CFlags
#define COPASI_CFlags

#include <bitset>
#include <vector>

#include "copasi/core/CEnumAnnotation.h"

template < class Enum > class CFlags : public std::bitset< static_cast< size_t >(Enum::__SIZE) >
{
public:
  typedef std::bitset< static_cast< size_t >(Enum::__SIZE) > bitset;

  /**
   * Static member where no flag is set
   */
  static const CFlags None;

  /**
   * Static member where all flags are set
   */
  static const CFlags All;

  /**
   * Default constructor
   */
  CFlags():
    bitset()
  {}

  /**
   * Copy constructor
   * @param const CFlags & src
   */
  CFlags(const CFlags & src):
    bitset(src)
  {}

  /**
   * Enum constructor
   * @param const Enum & flag
   */
  CFlags(const Enum & flag):
    bitset()
  {
    bitset::set(static_cast< size_t >(flag));
  }

  /**
   * Bitset constructor
   * @param const bitset & flags
   */
  CFlags(const bitset & flags):
    bitset(flags)
  {}

  /**
   * String constructor
   * @param const std::string & str
   */
  CFlags(const std::string & str):
    bitset(str)
  {}

  /**
   * Destructor
   */
  ~CFlags() {}

  /**
   * Cast to bitset
   */
  operator bitset()
  {
    return *this;
  }

  /**
   * Cast to bool
   */
  operator bool () const
  {
    return operator != (None);
  }

  /**
   * Equality comparison operator
   * @param const CFlags< Enum > & rhs
   * @return bool equal
   */
  bool operator == (const CFlags< Enum > & rhs) const
  {
    return bitset::operator == ((bitset) rhs);
  }

  /**
   * Inequality comparison operator
   * @param const CFlags< Enum > & rhs
   * @return bool notEqual
   */
  bool operator != (const CFlags< Enum > & rhs) const
  {
    return bitset::operator != ((bitset) rhs);
  }

  /**
   * Bitwise OR assignment operator
   * @param const CFlags & flags
   * @return CFlags & *this
   */
  CFlags & operator |= (const CFlags & flags)
  {
    bitset::operator |= ((bitset) flags);

    return *this;
  }

  /**
   * Bitwise OR assignment operator
   * @param const Enum & flag
   * @return CFlags & *this
   */
  CFlags & operator |= (const Enum & flag)
  {
    return operator |= (CFlags(flag));
  }

  /**
   * Bitwise AND assignment operator
   * @param const CFlags & flags
   * @return CFlags & *this
   */
  CFlags & operator &= (const CFlags & flags)
  {
    bitset::operator &= ((bitset) flags);

    return *this;
  }

  /**
   * Bitwise AND assignment operator
   * @param const Enum & flag
   * @return CFlags & *this
   */
  CFlags & operator &= (const Enum & flag)
  {
    return operator &= (CFlags(flag));
  }

  /**
   * Bitwise XOR assignment operator
   * @param const CFlags & flags
   * @return CFlags & *this
   */
  CFlags & operator ^= (const CFlags & flags)
  {
    bitset::operator ^= ((bitset) flags);

    return *this;
  }

  /**
   * Bitwise XOR assignment operator
   * @param const Enum & flag
   * @return CFlags & *this
   */
  CFlags & operator ^= (const Enum & flag)
  {
    return operator ^= (CFlags(flag));
  }

  /**
   * Check whether a the given flag is set
   * @param const Enum & flag
   * @return bool isSet
   */
  bool isSet(const Enum & flag) const
  {
    return bitset::operator[](static_cast< size_t >(flag));
  }

  /**
   * Create the subset of the provided annotations for the flags which are set
   * @param const CEnumAnnotation< AType, Enum > & annotation
   * @param const CFlags & filter (Default: All)
   * @return std::vector< AType > Annotations
   */
  template< typename AType >
  std::vector< AType > getAnnotations(const CEnumAnnotation< AType, Enum > & annotation,
                                      const CFlags & filter = All) const
  {
    std::vector< AType > Annotations;

    for (size_t i = 0; i < static_cast< size_t >(Enum::__SIZE); i++)
      if (bitset::operator[](i) && filter[i])
        {
          Annotations.push_back(annotation[i]);
        }

    return Annotations;
  }
};

/**
 * Bitwise OR operator
 * @param const CFlags< Enum > & lhs
 * @param const CFlags< Enum > & rhs
 * @return CFlags< Enum > result
 */
template < class Enum >
CFlags< Enum > operator | (const CFlags< Enum > & lhs, const CFlags< Enum > & rhs)
{
  return operator | ((std::bitset< static_cast< size_t >(Enum::__SIZE) >) lhs,
                     (std::bitset< static_cast< size_t >(Enum::__SIZE) >) rhs);
}

/**
 * Bitwise OR operator
 * @param const CFlags< Enum > & lhs
 * @param const Enum & rhs
 * @return CFlags< Enum > result
 */
template < class Enum >
CFlags< Enum > operator | (const CFlags< Enum > & lhs, const Enum & rhs)
{
  return operator | (lhs, CFlags< Enum >(rhs));
}

/**
 * Bitwise AND operator
 * @param const CFlags< Enum > & lhs
 * @param const CFlags< Enum > & rhs
 * @return CFlags< Enum > result
 */
template < class Enum >
CFlags< Enum > operator & (const CFlags< Enum > & lhs, const CFlags< Enum > & rhs)
{
  return operator & ((std::bitset< static_cast< size_t >(Enum::__SIZE) >) lhs,
                     (std::bitset< static_cast< size_t >(Enum::__SIZE) >) rhs);
}

/**
 * Bitwise AND operator
 * @param const CFlags< Enum > & lhs
 * @param const Enum & rhs
 * @return CFlags< Enum > result
 */
template < class Enum >
CFlags< Enum > operator & (const CFlags< Enum > & lhs, const Enum & rhs)
{
  return operator & (lhs, CFlags< Enum >(rhs));
}

/**
 * Bitwise XOR operator
 * @param const CFlags< Enum > & lhs
 * @param const CFlags< Enum > & rhs
 * @return CFlags< Enum > result
 */
template < class Enum >
CFlags< Enum > operator ^ (const CFlags< Enum > & lhs, const CFlags< Enum > & rhs)
{
  return operator ^ ((std::bitset< static_cast< size_t >(Enum::__SIZE) >) lhs,
                     (std::bitset< static_cast< size_t >(Enum::__SIZE) >) rhs);
}

/**
 * Bitwise XOR operator
 * @param const CFlags< Enum > & lhs
 * @param const Enum & rhs
 * @return CFlags< Enum > result
 */
template < class Enum >
CFlags< Enum > operator ^ (const CFlags< Enum > & lhs, const Enum & rhs)
{
  return operator ^ (lhs, CFlags< Enum >(rhs));
}

// static
template< class Enum > const CFlags< Enum > CFlags< Enum >::None;

// static
template< class Enum > const CFlags< Enum > CFlags< Enum >::All(~None);

#endif // COPASI_CFlags
