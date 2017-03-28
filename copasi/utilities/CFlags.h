// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CFlags
#define COPASI_CFlags

#include <bitset>

template < class Enum > class CFlags
{
public:
  static CFlags All;
  static CFlags None;

  CFlags():
    mFlags()
  {}

  CFlags(const CFlags & src):
    mFlags(src.mFlags)
  {}

  CFlags(const Enum & flag):
    mFlags()
  {
    mFlags.set(static_cast< size_t >(flag));
  }

  CFlags(const std::bitset< static_cast< size_t >(Enum::__SIZE) > & flags):
    mFlags(flags)
  {}

  ~CFlags() {}

  CFlags operator & (const CFlags & mask) const
  {
    return (mFlags & mask.mFlags);
  }

  CFlags & operator &= (const CFlags & other)
  {
    mFlags &= other.mFlags;
    return *this;
  }

  CFlags & operator = (const CFlags & rhs)
  {
    mFlags = rhs.mFlags;
    return *this;
  }

  CFlags & operator = (const Enum & flag)
  {
    mFlags.reset();
    mFlags.set(static_cast< size_t >(flag));

    return *this;
  }

  CFlags operator | (const CFlags & other) const
  {
    return mFlags | other.mFlags;
  }

  CFlags operator | (const Enum & flag) const
  {
    return mFlags | CFlags(flag).mFlags;
  }

  CFlags & operator |= (const CFlags & other)
  {
    mFlags |= other.mFlags;
    return *this;
  }

  CFlags operator ~() const
  {
    return ~mFlags;
  }

  bool isSet(const Enum & flag) const
  {
    return mFlags[static_cast< size_t >(flag)];
  }

  bool operator != (const CFlags & rhs) const
  {
    return mFlags != rhs.mFlags;
  }

  bool operator == (const CFlags & rhs) const
  {
    return mFlags == rhs.mFlags;
  }

  operator bool () const
  {
    return this->operator != (None);
  }

  void clear()
  {
    mFlags.reset();
  }

private:
  std::bitset< static_cast< size_t >(Enum::__SIZE) > mFlags;
};

// static
template< class Enum > CFlags< Enum > CFlags< Enum >::All(~ typename CFlags< Enum >::CFlags());

// static
template< class Enum > CFlags< Enum > CFlags< Enum >::None;

#endif // COPASI_CFlags
