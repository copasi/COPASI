// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

  const char* what() const throw() override;

  virtual ~CLUnresolvedReferenceException() throw() {}

protected:
  std::string mMessage;
};

#endif // CLUnresolvedReferenceException_H__
