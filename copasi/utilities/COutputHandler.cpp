/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/COutputHandler.cpp,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/25 13:20:35 $
   End CVS Header */

#include "copasi.h"

#include "COutputHandler.h"
#include "CCopasiTask.h"
#include "report/CCopasiTimer.h"

COutputHandler::COutputHandler():
    COutputInterface(),
    mInterfaces(),
    mpMaster(NULL),
    mObjectRefreshes()
{}

COutputHandler::COutputHandler(const COutputHandler & src):
    COutputInterface(src),
    mInterfaces(src.mInterfaces),
    mpMaster(src.mpMaster),
    mObjectRefreshes(src.mObjectRefreshes)
{}

COutputHandler::~COutputHandler() {};

bool COutputHandler::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  bool success = true;
  mObjects.clear();

  std::set< COutputInterface *>::iterator it = mInterfaces.begin();
  std::set< COutputInterface *>::iterator end = mInterfaces.end();

  std::set< const CCopasiObject * >::const_iterator itObj;
  std::set< const CCopasiObject * >::const_iterator endObj;

  for (; it != end; ++it)
    {
      success &= (*it)->compile(listOfContainer);

      // Assure that this is the only one master.
      COutputHandler * pHandler = dynamic_cast< COutputHandler * >(*it);
      if (pHandler != NULL) pHandler->setMaster(this);

      // Collect the list of objects
      const std::set< const CCopasiObject * > & Objects = (*it)->getObjects();
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

  // This hack is necessary as the reverse iterator behaves strangely
  // under Visual C++ 6.0, i.e., removing an object advances the iterator.
  std::vector< COutputInterface * > ToBeRemoved;

  for (; it != end; ++it)
    {
      (*it)->finish();

      if (dynamic_cast< CReport * >(*it) != NULL)
        ToBeRemoved.push_back(*it);
    }

  std::vector< COutputInterface * >::iterator itRemove = ToBeRemoved.begin();
  std::vector< COutputInterface * >::iterator endRemove = ToBeRemoved.end();

  for (; itRemove != endRemove; ++itRemove)
    removeInterface(*itRemove);

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
  mObjectRefreshes = CCopasiObject::buildUpdateSequence(mObjects);

  std::set< const CCopasiObject * >::const_iterator it = mObjects.begin();
  std::set< const CCopasiObject * >::const_iterator end = mObjects.end();

  // Timers are treated differently they are started during compilation.
  for (; it != end; ++it)
    if (dynamic_cast< const CCopasiTimer * >(*it))
      const_cast< CCopasiTimer * >(static_cast< const CCopasiTimer * >(*it))->start();

  return true;
}
