// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/sbml/StdException.h"

/**
 * Constructor that sets the error message object to "Error."
 */
StdException::StdException() throw()
{
  this->message = "Error.";
}

/**
 * Constructor that sets the error message object to the string given.
 */
StdException::StdException(const std::string what) throw()
{
  this->message = what;
};

/**
 * Destructor that does nothing.
 */
StdException::~StdException() throw()
{}

/**
 * Returns the error message object as a character array.
 */
const char* StdException::what() const throw()
{
  return this->message.c_str();
}
