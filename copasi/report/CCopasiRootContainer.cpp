// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CCopasiRootContainer.h"
#include "ArtisticLicense.h"
#include "function/CFunctionDB.h"
#include "commandline/CConfigurationFile.h"
#include "commandline/COptions.h"
#include "function/CFunction.h"
#include "function/CEvaluationNodeOperator.h"
#include "function/CEvaluationNodeVariable.h"
#include "function/CEvaluationNodeConstant.h"
#include "utilities/CUnit.h"
#include "model/CModel.h"
#include "layout/CLGlobalRenderInformation.h"

extern CCopasiVector<CLGlobalRenderInformation>* DEFAULT_STYLES;

extern CCopasiRootContainer * pRootContainer;

/**
 * The default constructor should be private so that nobody can create
 * new instances of the root container.
 * The only way to create a root container is through the static init
 * method.
 */
CCopasiRootContainer::CCopasiRootContainer(const bool & withGUI):
  CCopasiContainer("Root", NULL, "CN", CCopasiObject::Root),
  mKeyFactory(),
  mpUnknownResource(NULL),
  mpFunctionList(NULL),
  mpUnitDefinitionList(NULL),
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

  // delete the configuration
  pdelete(mpConfiguration);

  // delete the unkown resource
  pdelete(mpUnknownResource);

  // delete the model list
  pdelete(mpDataModelList);

  // delete the function list
  pdelete(mpFunctionList);

  // delete the unit list
  pdelete(mpUnitDefinitionList);

  // delete the undefined and the unsupported delay function
  pdelete(mpUndefined);

  // delete other static variables
  pdelete(DEFAULT_STYLES);
}

/**
 * This method creates the only root container.
 */
void CCopasiRootContainer::init(int argc, char *argv[], const bool & withGUI)
{
  COptions::init(argc, argv);

  CCopasiMessage::setIsGUI(withGUI);

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

  pdelete(CFunctionParameterMap::pUnmappedObject);

  COptions::cleanup();
}

void CCopasiRootContainer::initializeChildren()
{
  mpUnknownResource = new CMIRIAMResource("Unknown Resource");
  mpUnknownResource->setMIRIAMDisplayName("-- select --");
  mpUnknownResource->setMIRIAMURI("urn:miriam:unknown");

  mpFunctionList = new CFunctionDB("FunctionDB", this);
  mpFunctionList->load();

  mpDataModelList = new CCopasiVector<CCopasiDataModel>("ModelList", this);

  mpConfiguration = new CConfigurationFile;
  mpConfiguration->load();

  mpUndefined = new CFunction("undefined", this);
  mpUndefined->setInfix("nan");
  mpUndefined->compile();

  mpUnitDefinitionList = new CUnitDefinitionDB("Units list", this);
  CUnitDefinition::updateSIUnitDefinitions(mpUnitDefinitionList);
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
CUnitDefinitionDB *CCopasiRootContainer::getUnitList()
{
  return pRootContainer->mpUnitDefinitionList;
}

// static
const CUnitDefinition * CCopasiRootContainer::getUnitDefFromSymbol(const std::string symbol)
{
  const CUnitDefinition * pUnitDefinition = pRootContainer->mpUnitDefinitionList->getUnitDefFromSymbol(symbol);

  if (pUnitDefinition == NULL)
    {
      // As a fall back we try to find the name this is needed  e.g. for ohm
      size_t Index = pRootContainer->mpUnitDefinitionList->getIndex(symbol);

      if (Index != C_INVALID_INDEX)
        {
          pUnitDefinition = CCopasiRootContainer::getUnitList()->begin() + Index;
        }
    }

  return pUnitDefinition;
}

// static
std::string CCopasiRootContainer::quoteUnitDefSymbol(const std::string & symbol)
{
  return pRootContainer->mpUnitDefinitionList->quoteSymbol(symbol);
}

// static
void CCopasiRootContainer::replaceSymbol(const std::string & oldSymbol,
    const std::string & newSymbol)
{
  CCopasiVector< CCopasiDataModel >::iterator it = pRootContainer->mpDataModelList->begin();
  CCopasiVector< CCopasiDataModel >::iterator end = pRootContainer->mpDataModelList->end();

  for (; it != end; ++it)
    {
      it->getModel()->changeUnitExpressionSymbols(oldSymbol, newSymbol);
    }
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
const CMIRIAMResource & CCopasiRootContainer::getUnknownMiriamResource()
{
  return *pRootContainer->mpUnknownResource;
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
  const CCopasiDataModel* pDatamodel = &CCopasiRootContainer::getDatamodelList()->operator[](index);
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
