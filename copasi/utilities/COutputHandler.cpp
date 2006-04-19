/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/COutputHandler.cpp,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/19 18:37:00 $
   End CVS Header */

#include "copasi.h"

#include "COutputHandler.h"
#include "CCopasiTask.h"
#include "report/CCopasiTimer.h"

COutputHandler::COutputHandler(CCopasiTask * pTask):
    mInterfaces(),
    mpMaster(NULL)
{}

COutputHandler::~COutputHandler() {};

bool COutputHandler::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  bool success = true;

  std::set< COutputInterface *>::iterator it = mInterfaces.begin();
  std::set< COutputInterface *>::iterator end = mInterfaces.end();

  std::set< CCopasiObject * >::const_iterator itObj;
  std::set< CCopasiObject * >::const_iterator endObj;

  for (; it != end; ++it)
    {
      success &= (*it)->compile(listOfContainer);

      // Assure that this is the only one master.
      COutputHandler * pHandler = dynamic_cast< COutputHandler * >(*it);
      if (pHandler != NULL) pHandler->setMaster(this);

      // Collect the list of objects
      const std::set< CCopasiObject * > & Objects = (*it)->getObjects();
      for (itObj = Objects.begin(), endObj = Objects.end(); itObj != endObj; ++itObj)
        mObjects.insert(*itObj);
    }

  if (mpMaster == NULL)
    success &= compileRefresh();

  return success;
}

void COutputHandler::output(const Activity & activity)
{
  if (mpMaster == NULL)
    refresh();

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
{
  mInterfaces.insert(pInterface);

  // Assure that this is the only one master.
  COutputHandler * pHandler = dynamic_cast< COutputHandler * >(pInterface);
  if (pHandler != NULL) pHandler->setMaster(this);
}

void COutputHandler::removeInterface(COutputInterface * pInterface)
{
  mInterfaces.erase(pInterface);

  // Assure that the removed handler is its own master.
  COutputHandler * pHandler = dynamic_cast< COutputHandler * >(pInterface);
  if (pHandler != NULL) pHandler->setMaster(NULL);
}

void COutputHandler::setMaster(COutputHandler * pMaster)
{mpMaster = pMaster;}

const bool COutputHandler::isMaster() const
  {return (mpMaster == NULL);}

void COutputHandler::refresh()
{
  std::vector< Refresh * >::iterator it = mObjectRefreshes.begin();
  std::vector< Refresh * >::iterator end = mObjectRefreshes.end();

  for (;it != end; ++it) (**it)();
}

bool COutputHandler::compileRefresh()
{
  mObjectRefreshes.clear();

  std::set< CCopasiObject * >::const_iterator it = mObjects.begin();
  std::set< CCopasiObject * >::const_iterator end = mObjects.end();

  Refresh * pRefresh;

  for (; it != end; ++it)
    if ((pRefresh = (*it)->getRefresh()))
      {
        mObjectRefreshes.push_back(pRefresh);

        // Timers are treated differently they are started during compilation.
        if (dynamic_cast< CCopasiTimer * >(*it))
          dynamic_cast< CCopasiTimer * >(*it)->start();
      }

  return true;
}
