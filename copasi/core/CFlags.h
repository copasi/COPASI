// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CFlags
#define COPASI_CFlags

#include <bitset>
#include <vector>
#include <array>

template < class Enum > class CFlags
{
public:
  static const CFlags None;
  static const CFlags All;

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

  CFlags(const std::string & str):
    mFlags(str)
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

  std::string toString() const
  {
    return mFlags.to_string();
  }

  void clear()
  {
    mFlags.reset();
  }

  // takes an array of all possible annotations and
  // returns a vector with annotations for only the
  // flags which are set
  template< typename AType >
  std::vector< AType > getAnnotations(const std::array< AType, static_cast< size_t >(Enum::__SIZE) > & annotations) const
  {
    std::vector< AType > setFlagAnnotations;

    for (size_t i = 0; i < mFlags.size(); i++)
      if (mFlags[i]) setFlagAnnotations.push_back(annotations[i]);

    return setFlagAnnotations;
  }

private:
  std::bitset< static_cast< size_t >(Enum::__SIZE) > mFlags;
};

// static
template< class Enum > const CFlags< Enum > CFlags< Enum >::None;

// static
template< class Enum > const CFlags< Enum > CFlags< Enum >::All(~None);

#endif // COPASI_CFlags
