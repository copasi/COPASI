/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/COutputHandler.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/25 15:06:30 $
   End CVS Header */

#include "copasi.h"
#include "COutputHandler.h"

bool CCallbackHandler::init()
{
#ifdef COPASI_DEBUG
  std::cout << "CallbackHandler: init" << std::endl;
#endif // COPASI_DEBUG
  return true;
}

bool CCallbackHandler::doOutput()
{
#ifdef COPASI_DEBUG
  std::cout << "CallbackHandler: do" << std::endl;
#endif // COPASI_DEBUG
  return true;
}

bool CCallbackHandler::finish()
{
#ifdef COPASI_DEBUG
  std::cout << "CallbackHandler: finish" << std::endl;
#endif // COPASI_DEBUG
  return true;
}

bool CCallbackHandler::init(C_INT32 maxSteps)
{
#ifdef COPASI_DEBUG
  std::cout << "CallbackHandler: init" << std::endl;
#endif // COPASI_DEBUG
  return true;
}

bool CCallbackHandler::progress(C_INT32 steps)
{
#ifdef COPASI_DEBUG
  std::cout << "CallbackHandler: progress" << std::endl;
#endif // COPASI_DEBUG
  return true;
}
