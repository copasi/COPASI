/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiException.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/29 17:28:23 $
   End CVS Header */

// CErrorMessage
//
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

#include <string>

#include "copasi.h"
#include "CCopasiException.h"

CCopasiException::CCopasiException(void):
    mMessage()
{}

CCopasiException::CCopasiException(const CCopasiMessage & message):
    mMessage(message)
{}

CCopasiException::~CCopasiException(void) {}

const CCopasiMessage & CCopasiException::getMessage() const
  {return mMessage;}
