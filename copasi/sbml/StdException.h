/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/StdException.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/06/21 09:49:29 $
   End CVS Header */

#ifndef STDEXCEPTION_H__
#define STDEXCEPTION_H__

#include <string>
#include <exception>

/**
 * Simple exception class that implements the what() function of std::exception
 * to specify an error message.
 */
class StdException: public std::exception
  {
  public:
    /**
     * Constructor that sets the error message object to "Error."
     */
    StdException() throw();

    /**
     * Constructor that sets the error message object to the string given.
     */
    explicit StdException(const std::string what) throw();

    /**
     * Destructor that does nothing.
     */
    virtual ~StdException() throw();

    /**
     * Returns the error message object as a character array.
     */
    virtual const char* what() const throw();

  protected:
    std::string message;
  };

#endif
