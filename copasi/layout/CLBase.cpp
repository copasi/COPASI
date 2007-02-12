// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLBase.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/12 00:03:12 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CLBase.h"

std::ostream & operator<<(std::ostream &os, const CLPoint & p)
{
  os << "(x=" << p.mX << ", y=" << p.mY << ")";
  return os;
}

std::ostream & operator<<(std::ostream &os, const CLDimensions & d)
{
  os << "(w=" << d.mWidth << ", h=" << d.mHeight << ")";
  return os;
}

std::ostream & operator<<(std::ostream &os, const CLBoundingBox & bb)
{
  os << "[" << bb.mPosition << bb.mDimensions << "]";
  return os;
}
