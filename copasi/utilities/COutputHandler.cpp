/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/COutputHandler.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/16 17:40:37 $
   End CVS Header */

#include "copasi.h"

#include "COutputHandler.h"
#include "CCopasiTask.h"

COutputHandler::COutputHandler(CCopasiTask * pTask):
    mpTask(pTask),
    mInterfaces()
{}

COutputHandler::~COutputHandler() {};

bool COutputHandler::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  bool success = true;

  std::set< COutputInterface *>::iterator it = mInterfaces.begin();
  std::set< COutputInterface *>::iterator end = mInterfaces.end();

  if (mpTask) listOfContainer.push_back(mpTask);

  for (; it != end; ++it)
    success &= (*it)->compile(listOfContainer);

  return success;
}

void COutputHandler::output(const Activity & activity)
{
  std::set< COutputInterface *>::iterator it = mInterfaces.begin();
  std::set< COutputInterface *>::iterator end = mInterfaces.end();

  for (; it != end; ++it)
    (*it)->output(activity);

  return;
}

void COutputHandler::separate(const Activity & activity)
{
  std::set< COutputInterface *>::iterator it = mInterfaces.begin();
  std::set< COutputInterface *>::iterator end = mInterfaces.end();

  for (; it != end; ++it)
    (*it)->separate(activity);

  return;
}

void COutputHandler::finish()
{
  std::set< COutputInterface *>::iterator it = mInterfaces.begin();
  std::set< COutputInterface *>::iterator end = mInterfaces.end();

  for (; it != end; ++it)
    (*it)->finish();

  return;
}

void COutputHandler::addInterface(COutputInterface * pInterface)
{mInterfaces.insert(pInterface);}

void COutputHandler::removeInterface(COutputInterface * pInterface)
{mInterfaces.erase(pInterface);}
