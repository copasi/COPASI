/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/COutputHandler.cpp,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/05 16:03:52 $
   End CVS Header */

#include <iostream>
#include "copasi.h"
#include "COutputHandler.h"

bool CCallbackHandler::compile(std::vector< CCopasiContainer * > listOfContainer)
{return true;}

void CCallbackHandler::init()
{
#ifdef COPASI_DEBUG
  std::cout << "CallbackHandler: init" << std::endl;
#endif // COPASI_DEBUG
  return;
}

void CCallbackHandler::doOutput()
{
#ifdef COPASI_DEBUG
  std::cout << "CallbackHandler: do" << std::endl;
#endif // COPASI_DEBUG
  return;
}

void CCallbackHandler::finish()
{
#ifdef COPASI_DEBUG
  std::cout << "CallbackHandler: finish" << std::endl;
#endif // COPASI_DEBUG
  return;
}

void CCallbackHandler::doSeparator()
{
#ifdef COPASI_DEBUG
  std::cout << "CallbackHandler: separator" << std::endl;
#endif // COPASI_DEBUG
  return;
}
