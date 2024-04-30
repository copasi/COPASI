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

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// CErrorMessage
//
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

#include <string>

#include "copasi/copasi.h"
#include "CCopasiException.h"

CCopasiException::CCopasiException(void)
  : std::exception()
  , mMessage()
{}

CCopasiException::CCopasiException(const CCopasiMessage & message)
  : std::exception()
  , mMessage(message)
{}

CCopasiException::~CCopasiException(void) {}

const CCopasiMessage & CCopasiException::getMessage() const
{return mMessage;}

const char*
CCopasiException::what() const throw()
{
  return mMessage.getText().c_str();
}
