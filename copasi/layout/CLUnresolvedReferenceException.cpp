// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLUnresolvedReferenceException.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CLUnresolvedReferenceException.h"

CLUnresolvedReferenceException::CLUnresolvedReferenceException(const std::string& id): std::exception()
{
  this->mMessage = "Unresolved reference to style id \"" + id + "\".";
}

const char* CLUnresolvedReferenceException::what() const throw()
{
  return this->mMessage.c_str();
}
