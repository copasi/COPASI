// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/copasi.h"

#include "COutputHandler.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/core/CDataTimer.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/trajectory/CTimeSeries.h"

COutputHandler::COutputHandler():
  COutputInterface(),
  mInterfaces(),
  mpMaster(NULL),
  mUpdateSequence(),
  mpContainer(NULL)
{}

COutputHandler::COutputHandler(const COutputHandler & src):
  COutputInterface(src),
  mInterfaces(src.mInterfaces),
  mpMaster(src.mpMaster),
  mUpdateSequence(src.mUpdateSequence),
  mpContainer(NULL)
{}

COutputHandler::~COutputHandler() {};

std::set<COutputInterface *> COutputHandler::getInterfaces() const
{
  return mInterfaces;
}

bool COutputHandler::compile(CObjectInterface::ContainerList listOfContainer)
{
  CObjectInterface::ContainerList::const_iterator itContainer = listOfContainer.begin();
  CObjectInterface::ContainerList::const_iterator endContainer = listOfContainer.end();

  for (mpContainer = NULL; itContainer != endContainer && mpContainer == NULL; ++itContainer)
    {
      mpContainer = dynamic_cast< const CMathContainer * >(*itContainer);
    }

  assert(mpContainer != NULL);

  bool success = true;
  mObjects.clear();

  std::set< COutputInterface *>::iterator it = mInterfaces.begin();
  std::set< COutputInterface *>::iterator end = mInterfaces.end();

  CObjectInterface::ObjectSet::const_iterator itObj;
  CObjectInterface::ObjectSet::const_iterator endObj;

  for (; it != end; ++it)
    {
      success &= (*it)->compile(listOfContainer);

      // Assure that this is the only one master.
      COutputHandler * pHandler = dynamic_cast< COutputHandler * >(*it);

      if (pHandler != NULL) pHandler->setMaster(this);

      // Collect the list of objects
      const CObjectInterface::ObjectSet & Objects = (*it)->getObjects();

      for (itObj = Objects.begin(), endObj = Objects.end(); itObj != endObj; ++itObj)
        mObjects.insert(*itObj);
    }

  if (mpMaster == NULL)
    success &= compileUpdateSequence(listOfContainer);

  return success;
}

void COutputHandler::output(const Activity & activity)
{
  if (mpMaster == NULL)
    applyUpdateSequence();

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

  // Closing a stream is separated from finishing the output
  // since subtask may still need to finish their output.
  for (; it != end; ++it)
    {
      (*it)->finish();
    }

  for (it = mInterfaces.begin(); it != end; ++it)
    {
      (*it)->close();

      // CTimesSeries and CReport are only used once.
      if (dynamic_cast< CReport * >(*it) != NULL ||
          dynamic_cast< CTimeSeries * >(*it) != NULL)
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

bool COutputHandler::isMaster() const
{return (mpMaster == NULL);}

void COutputHandler::applyUpdateSequence()
{
  const_cast< CMathContainer * >(mpContainer)->applyUpdateSequence(mUpdateSequence);
}

bool COutputHandler::compileUpdateSequence(const CObjectInterface::ContainerList & listOfContainer)
{

  mpContainer->getTransientDependencies().getUpdateSequence(mUpdateSequence, CCore::SimulationContext::Default, mpContainer->getStateObjects(), mObjects,
      mpContainer->getSimulationUpToDateObjects());

  CObjectInterface::ObjectSet::const_iterator it = mObjects.begin();
  CObjectInterface::ObjectSet::const_iterator end = mObjects.end();

  // Timers are treated differently they are started during compilation.
  for (; it != end; ++it)
    if (dynamic_cast< const CCopasiTimer * >(*it))
      const_cast< CCopasiTimer * >(static_cast< const CCopasiTimer * >(*it))->start();

  return true;
}

COutputInterface::COutputInterface() :
  mObjects()
{}

COutputInterface::COutputInterface(const COutputInterface & src) :
  mObjects(src.mObjects)
{}

COutputInterface::~COutputInterface()
{}

const CObjectInterface::ObjectSet & COutputInterface::getObjects() const
{
  return mObjects;
}

// virtual
void COutputInterface::close()
{}
