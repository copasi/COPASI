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
