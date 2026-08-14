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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CCopasiException class. A more elaborate class description.
 */

// New Class for C++ exception handling.
// (C) Stefan Hoops 2001

#ifndef COPASI_CCopasiException
#define COPASI_CCopasiException

#include "CCopasiMessage.h"

#include <exception>

class CCopasiException : public std::exception
{
private:
  /**
   * Default consructor.
   */
  CCopasiException();

public:
  /**
   * Specific consructor. Creates a exception with a message.
   * @param const CCopasiMessage & message
   */
  CCopasiException(const CCopasiMessage & message);

  /**
   * Destructor.
   */
  ~CCopasiException();

  /**
   * Retrieves the Message associated with the exception
   * @return const CCopasiMessage & message
   */
  const CCopasiMessage & getMessage() const;

  /**
   * Retrieves the Message associated with the exception
   * @return const char* message
   */
#ifndef SWIG
   const char* what() const throw() override;
#else
   virtual const char* what() const;
#endif

private:
  const CCopasiMessage mMessage;
};
#endif // COPASI_CCopasiException
