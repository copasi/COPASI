// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiRootContainer.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/08/01 00:30:25 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CCopasiRootContainer.h"

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
    mpUnsupportedDelay(NULL),
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
  // unsupported delay is owned by the function database
  // and will be destroyed by it
  //pdelete(this->mpUnsupportedDelay);
}

/**
 * This method creates the only root container.
 */
void CCopasiRootContainer::init(int argc, char** argv, const bool & withGUI)
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

  mpUnsupportedDelay = new CFunction("delay");
  mpUnsupportedDelay->addVariable("variable");
  mpUnsupportedDelay->addVariable("timeDelay");

  CEvaluationNodeOperator* pTmpNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
  pTmpNode->addChild(new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, "variable"));
  pTmpNode->addChild(new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, "timeDelay"));
  CEvaluationNodeOperator* pRoot = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
  pRoot->addChild(pTmpNode);
  pRoot->addChild(new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NAN"));

  mpUnsupportedDelay->setRoot(pRoot);
  mpUnsupportedDelay->compile();

  if (mpFunctionList != NULL)
    mpFunctionList->addAndAdaptName(mpUnsupportedDelay);
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
  assert(pRootContainer->mpDataModelList->add(pDataModel, true));
  return pDataModel;
}

// static
CFunction * CCopasiRootContainer::getUnsupportedDelay()
{
  return pRootContainer->mpUnsupportedDelay;
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

bool CCopasiRootContainer::removeDatamodel(const unsigned C_INT32 index)
{
  const CCopasiDataModel* pDatamodel = (*CCopasiRootContainer::getDatamodelList())[index];
  return CCopasiRootContainer::removeDatamodel(pDatamodel);
}
