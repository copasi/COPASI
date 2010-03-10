// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLUnresolvedReferenceException.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLUnresolvedReferenceException_H__
#define CLUnresolvedReferenceException_H__

#include <exception>
#include <string>

class CLUnresolvedReferenceException : std::exception
{
public:
  CLUnresolvedReferenceException(const std::string& id);

  virtual const char* what() const throw();

  virtual ~CLUnresolvedReferenceException() throw() {}

protected:
  std::string mMessage;
};

#endif // CLUnresolvedReferenceException_H__
