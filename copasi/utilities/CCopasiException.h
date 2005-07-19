/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiException.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/19 15:17:13 $
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

  private:
    const CCopasiMessage mMessage;
  };
#endif // COPASI_CCopasiException
