/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiException.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:35:32 $
   End CVS Header */

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
     *  Specific consructor. Creates a exception with a message.
     *  @param pmessage pointer to a CCopasiMessage object.
     */
    CCopasiException(CCopasiMessage &message);

    /**
     *  Destructor. 
     */
    ~CCopasiException();

    /**
     *  Retrieves the Message associated with the exception
     */
    CCopasiMessage getMessage();

  private:
    CCopasiMessage mMessage;
  };
#endif // COPASI_CCopasiException
