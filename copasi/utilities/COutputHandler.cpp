// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/COutputHandler.cpp,v $
//   $Revision: 1.23 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 00:33:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "COutputHandler.h"
#include "CCopasiTask.h"

#include "report/CCopasiTimer.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "trajectory/CTimeSeries.h"

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
    success &= compileRefresh(listOfContainer);

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

void COutputHandler::refresh()
{
  std::vector< Refresh * >::iterator it = mObjectRefreshes.begin();
  std::vector< Refresh * >::iterator end = mObjectRefreshes.end();

  for (;it != end; ++it) (**it)();
}

bool COutputHandler::compileRefresh(const std::vector< CCopasiContainer * > & listOfContainer)
{
  CModel * pModel =
    dynamic_cast< CModel * >(CCopasiContainer::ObjectFromName(listOfContainer, CCopasiDataModel::Global->getModel()->getCN()));

  mObjectRefreshes = CCopasiObject::buildUpdateSequence(mObjects, pModel->getUptoDateObjects());

  std::set< const CCopasiObject * >::const_iterator it = mObjects.begin();
  std::set< const CCopasiObject * >::const_iterator end = mObjects.end();

  // Timers are treated differently they are started during compilation.
  for (; it != end; ++it)
    if (dynamic_cast< const CCopasiTimer * >(*it))
      const_cast< CCopasiTimer * >(static_cast< const CCopasiTimer * >(*it))->start();

  return true;
}
