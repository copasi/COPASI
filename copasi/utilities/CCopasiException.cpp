/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiException.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:03 $
   End CVS Header */

// CErrorMessage
//
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

#include <string>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CCopasiException.h"

CCopasiException::CCopasiException(void) {mMessage = * new CCopasiMessage();}

CCopasiException::CCopasiException(CCopasiMessage &message){mMessage = message;}

CCopasiException::~CCopasiException(void) {}

CCopasiMessage CCopasiException::getMessage() {return mMessage;}
