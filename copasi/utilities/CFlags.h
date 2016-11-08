// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CFlags
#define COPASI_CFlags

template <class Enum> class CFlags
{
public:
  CFlags():
    mFlags(0)
  {}

  CFlags(const CFlags & src):
    mFlags(src.mFlags)
  {}

  CFlags(const Enum & flag):
    mFlags((int) flag)
  {}

  CFlags(const int & flag):
    mFlags(flag)
  {}

  ~CFlags() {}

  operator int () const
  {
    return mFlags;
  }

  Enum operator & (const Enum & flag) const
  {
    return (Enum)(mFlags & flag);
  }

  CFlags operator & (const CFlags & mask) const
  {
    return (mFlags & mask);
  }

  CFlags operator & (const int & mask) const
  {
    return (mFlags & mask);
  }

  CFlags & operator = (const CFlags & rhs)
  {
    mFlags = rhs.mFlags;
    return *this;
  }

  CFlags operator | (const Enum & flag) const
  {
    return (mFlags | flag);
  }

  CFlags operator | (const CFlags & other) const
  {
    return (mFlags | other);
  }

  CFlags & operator |= (const CFlags & other)
  {
    mFlags |= other.mFlags;
    return *this;
  }

private:
  int mFlags;
};

#endif // COPASI_CFlags
