/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/COutputHandler.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/04/06 15:01:18 $
   End CVS Header */

#include "copasi.h"
#include "COutputHandler.h"

bool COutputHandler::init()
{
  std::cout << "OutputHandler: init" << std::endl;
  return true;
}

bool COutputHandler::doOutput()
{
  std::cout << "OutputHandler: do" << std::endl;
  return true;
}

bool COutputHandler::finish()
{
  std::cout << "OutputHandler: finish" << std::endl;
  return true;
}
