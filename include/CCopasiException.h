/**
 *  CCopasiException class. A more elaborate class description.
 */

// New Class for C++ exception handling.
// (C) Stefan Hoops 2001


#ifndef COPASI_CCopasiException
#define COPASI_CCopasiException

#include "CCopasiMessage.h"

class CCopasiException
{
public:
    /**
     *  Default consructor. 
     */
    CCopasiException();

    /**
     *  Default consructor. 
     */
    CCopasiException(CCopasiMessage *pmessage);

    /**
     *  Destructor. 
     */
    ~CCopasiException();

    CCopasiMessage Message;
private:

};
#endif // COPASI_CCopasiException
