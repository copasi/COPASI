/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/COutputHandler.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/05/04 20:10:09 $
   End CVS Header */

#include "copasi.h"
#include "COutputHandler.h"

bool COutputHandler::init()
{
#ifdef COPASI_DEBUG
  std::cout << "OutputHandler: init" << std::endl;
#endif // COPASI_DEBUG
  return true;
}

bool COutputHandler::doOutput()
{
#ifdef COPASI_DEBUG
  std::cout << "OutputHandler: do" << std::endl;
#endif // COPASI_DEBUG
  return true;
}

bool COutputHandler::finish()
{
#ifdef COPASI_DEBUG
  std::cout << "OutputHandler: finish" << std::endl;
#endif // COPASI_DEBUG
  return true;
}
