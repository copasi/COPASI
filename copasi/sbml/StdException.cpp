/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/StdException.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/06/21 09:49:29 $
   End CVS Header */

#include "sbml/StdException.h"

/**
 * Constructor that sets the error message object to "Error."
 */
StdException::StdException() throw()
{
  this->message = "Error.";
}

/**
 * Constructor that sets the error message object to the string given.
 */
StdException::StdException(const std::string what) throw()
{
  this->message = what;
};

/**
 * Destructor that does nothing.
 */
StdException::~StdException() throw()
{}

/**
 * Returns the error message object as a character array.
 */
const char* StdException::what() const throw()
{
  return this->message.c_str();
}
