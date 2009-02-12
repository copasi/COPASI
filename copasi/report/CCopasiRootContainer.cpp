// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiRootContainer.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/12 15:54:45 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CCopasiRootContainer.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "CCopasiTimer.h"

/**
 * Initialize the root container with NULL
 */
CCopasiRootContainer::CCopasiRootContainer * Root = NULL;

/**
 * The default contructor should be private so that nobody can create
 * new instances of the root container.
 * The only way to create a root container is through the static init
 * method.
 */
CCopasiRootContainer::CCopasiRootContainer(): CCopasiContainer(),
    mpFunctionList(new CFunctionDB),
    mpConfiguration(new CConfigurationFile),
    mpDataModelList(new CCopasiVector<CCopasiDataModel>),
    mWithGUI(false)
{
  mpFunctionList->load();
  mpConfiguration->load();
}

// Destructor
CCopasiRootContainer::~CCopasiRootContainer()
{
  // save and delete the configuration
  if (mpConfiguration != NULL)
    mpConfiguration->save();
  pdelete(mpConfiguration);
  // delete the function list
  pdelete(mpFunctionList);
  // delete the model list
  pdelete(mpDataModelList);
}

/**
 * This method creates the only root container.
 */
void CCopasiRootContainer::init()
{
  CCopasiRootContainer::Root = CCopasiRootContainer::createNewRoot();
}

CCopasiRootContainer* CCopasiRootContainer::createNewRoot()
{
  CCopasiRootContainer* pContainer = new CCopasiRootContainer();
  new CCopasiTimer(CCopasiTimer::WALL, pContainer);
  new CCopasiTimer(CCopasiTimer::CPU, pContainer);
  return pContainer;
}

/**
 * Returns the a pointer to the configuration.
 */
CConfigurationFile* CCopasiRootContainer::getConfiguration()
{
  return this->mpConfiguration;
}

/**
 * Returns the a const pointer to the configuration.
 */
const CConfigurationFile* CCopasiRootContainer::getConfiguration() const
  {
    return this->mpConfiguration;
  }

/**
 * Returns a pointer to the global function database.
 */
CFunctionDB* CCopasiRootContainer::getFunctionList()
{
  return this->mpFunctionList;
}

/**
 * Returns a const pointer to the global function database.
 */
const CFunctionDB* CCopasiRootContainer::getFunctionList() const
  {
    return this->mpFunctionList;
  }

/**
 * Returns a pointer to the list of data models.
 */
CCopasiVector< CCopasiDataModel > * CCopasiRootContainer::getDatamodelList()
{
  return this->mpDataModelList;
}

/**
 * Returns a const pointer to the list of data models.
 */
const CCopasiVector< CCopasiDataModel > * CCopasiRootContainer::getDatamodelList() const
  {
    return this->mpDataModelList;
  }

/**
 * Creates a new datamodel instance and adds it to the list.
 * The new instance is returned by the method.
 */
CCopasiDataModel * CCopasiRootContainer::addDatamodel()
{
  CCopasiDataModel* pDataModel = new CCopasiDataModel(this->mWithGUI);
  assert(this->mpDataModelList->add(pDataModel));
  return pDataModel;
}

// Copy constructor
/*
CCopasiRootContainer::CCopasiRootContainer(const CCopasiRootContainer & src)
{
    // copy the key factory
    this->mKeyFactory=src.mKeyFactory;

    // copy the function list
    this->mpFunctionList=new CFunctionDB(src.mpFunctionList,this);

    // copy the configuration
    this->mpConfiguration=new CConfigurationFile(*src.mpConfiguration,this);

    // copy the GUI flag
    this->mWithGUI=src.mWithGUI;
}
 */

/**
 * The assignment operator is private as well to make sure that there is only
 * one root container that can be initialized through the init call.
CCopasiRootContainer& CCopasiRootContainer::operator=(const CCopasiRootContainer& src)
{
    if(&src != this)
    {
        // copy the key factory
        // TODO key factory does not have an assignment operator yet
        this->mKeyFactory=src.mKeyFactory;

        // copy the function list
        pdelete(this->mpFunctionList);
        // this should work since CFunctionDB only contains non-pointer members
        // which have a copy constructor
        this->mpFunctionList=new CFunctionDB(src.mpFunctionList,this);

        // copy the configuration
        // TODO the copy constructor of CConfigurationFile does not copy the
        // parameters but it creates new ones
        pdelete(this->mpConfiguration);
        this->mpConfiguration=new CConfigurationFile(*src.mpConfiguration,this);

        // copy the GUI flag
        this->mWithGUI=src.mWithGUI;
    }
    return *this;
}
 */
