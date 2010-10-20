// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiRootContainer.cpp,v $
//   $Revision: 1.14.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/10/20 15:14:25 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CCopasiRootContainer.h"
#include "ArtisticLicense.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/commandline/COptions.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CEvaluationNodeOperator.h"
#include "copasi/function/CEvaluationNodeVariable.h"
#include "copasi/function/CEvaluationNodeConstant.h"

extern CCopasiRootContainer * pRootContainer;

/**
 * The default constructor should be private so that nobody can create
 * new instances of the root container.
 * The only way to create a root container is through the static init
 * method.
 */
CCopasiRootContainer::CCopasiRootContainer(const bool & withGUI):
    CCopasiContainer("Root", NULL, "CN", CCopasiObject::Root),
    mpFunctionList(NULL),
    mpConfiguration(NULL),
    mpDataModelList(NULL),
    mWithGUI(withGUI),
    mpUndefined(NULL)
{}

// Destructor
CCopasiRootContainer::~CCopasiRootContainer()
{
  // save and delete the configuration
  if (mpConfiguration != NULL &&
      mWithGUI)
    {
      mpConfiguration->save();
    }

  pdelete(mpConfiguration);
  // delete the function list
  pdelete(mpFunctionList);
  // delete the model list
  pdelete(mpDataModelList);
  // delete the undefined and the unsupported delay function
  pdelete(mpUndefined);
}

/**
 * This method creates the only root container.
 */
void CCopasiRootContainer::init(int argc, char *argv[], const bool & withGUI)
{
  COptions::init(argc, argv);

  if (pRootContainer == NULL)
    pRootContainer = new CCopasiRootContainer(withGUI);

  if (pRootContainer != NULL)
    pRootContainer->initializeChildren();
}

// static
void CCopasiRootContainer::destroy()
{
  if (pRootContainer != NULL)
    {
      delete pRootContainer;
      pRootContainer = NULL;
    }

  COptions::cleanup();
}

void CCopasiRootContainer::initializeChildren()
{
  mpFunctionList = new CFunctionDB("FunctionDB", this);
  mpFunctionList->load();

  mpDataModelList = new CCopasiVector<CCopasiDataModel>("ModelList", this);

  mpConfiguration = new CConfigurationFile;
  mpConfiguration->load();

  mpUndefined = new CFunction("undefined");
  mpUndefined->setInfix("nan");
  mpUndefined->compile();

  mKeyFactory.remove(mpUndefined->getKey());
  mKeyFactory.addFix("UndefinedFunction_0", mpUndefined);
}

// static
const CCopasiContainer * CCopasiRootContainer::getRoot()
{
  return pRootContainer;
}

// static
CConfigurationFile * CCopasiRootContainer::getConfiguration()
{
  return pRootContainer->mpConfiguration;
}

// static
CFunctionDB * CCopasiRootContainer::getFunctionList()
{
  return pRootContainer->mpFunctionList;
}

// static
CCopasiVector< CCopasiDataModel > * CCopasiRootContainer::getDatamodelList()
{
  return pRootContainer->mpDataModelList;
}

// static
CCopasiDataModel * CCopasiRootContainer::addDatamodel()
{
  CCopasiDataModel* pDataModel = new CCopasiDataModel(pRootContainer->mWithGUI);
  pRootContainer->mpDataModelList->add(pDataModel, true);
  return pDataModel;
}

// static
CFunction * CCopasiRootContainer::getUndefinedFunction()
{
  return pRootContainer->mpUndefined;
}

//static
CKeyFactory* CCopasiRootContainer::getKeyFactory()
{
  return &pRootContainer->mKeyFactory;
}

// static
bool CCopasiRootContainer::removeDatamodel(const CCopasiDataModel * pDatamodel)
{
  if (!pDatamodel)
    {
      return false;
    }

  pRootContainer->mpDataModelList->remove((CCopasiDataModel *)pDatamodel);
  pdelete(pDatamodel);

  return true;
}

// static
bool CCopasiRootContainer::removeDatamodel(const unsigned C_INT32 index)
{
  const CCopasiDataModel* pDatamodel = (*CCopasiRootContainer::getDatamodelList())[index];
  return CCopasiRootContainer::removeDatamodel(pDatamodel);
}

// static
const char * CCopasiRootContainer::getLicenseTxt()
{
  return CopasiLicenseTxt;
}

// static
const char * CCopasiRootContainer::getLicenseHTML()
{
  return CopasiLicenseHtml;
}


