// CErrorMessage
// 
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

#include <string>

#include "copasi.h"
#include "CCopasiException.h"


CCopasiException::CCopasiException(void)
{
//    mMessage = 0;
}

CCopasiException::CCopasiException(CCopasiMessage *pmessage)
{
    Message = *pmessage;
}

CCopasiException::~CCopasiException(void)
{
}

