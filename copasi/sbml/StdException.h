// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef STDEXCEPTION_H__
#define STDEXCEPTION_H__

#include <string>
#include <exception>

/**
 * Simple exception class that implements the what() function of std::exception
 * to specify an error message.
 */
class StdException: public std::exception
{
public:
  /**
   * Constructor that sets the error message object to "Error."
   */
  StdException() throw();

  /**
   * Constructor that sets the error message object to the string given.
   */
  explicit StdException(const std::string what) throw();

  /**
   * Destructor that does nothing.
   */
  virtual ~StdException() throw();

  /**
   * Returns the error message object as a character array.
   */
  virtual const char* what() const throw();

protected:
  std::string message;
};

#endif
