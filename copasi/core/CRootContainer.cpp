// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/copasi.h"

#include "CRootContainer.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/report/ArtisticLicense.h"

#include "copasi/function/CFunctionDB.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/commandline/COptions.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CEvaluationNodeOperator.h"
#include "copasi/function/CEvaluationNodeVariable.h"
#include "copasi/function/CEvaluationNodeConstant.h"
#include "copasi/utilities/CUnit.h"
#include "copasi/model/CModel.h"
#include "copasi/layout/CLGlobalRenderInformation.h"
#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/utilities/CUnitDefinitionDB.h"

#include <copasi/MIRIAM/CRDFGraphConverter.h>

extern CDataVector< CLGlobalRenderInformation > * DEFAULT_STYLES;

extern CRootContainer * pRootContainer;

/**
 * The default constructor should be private so that nobody can create
 * new instances of the root container.
 * The only way to create a root container is through the static init
 * method.
 */
CRootContainer::CRootContainer(const bool & withGUI):
  CDataContainer("Root", NULL, "CN", CDataObject::Root),
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
CRootContainer::~CRootContainer()
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
void CRootContainer::init(int argc, char *argv[], const bool & withGUI)
{
  COptions::init(argc, argv);

  CCopasiMessage::setIsGUI(withGUI);

  if (pRootContainer == NULL)
    pRootContainer = new CRootContainer(withGUI);

  if (pRootContainer != NULL)
    pRootContainer->initializeChildren();
}

// static
void CRootContainer::destroy()
{
  if (pRootContainer != NULL)
    {
      delete pRootContainer;
      pRootContainer = NULL;
    }

  pdelete(CFunctionParameterMap::pUnmappedObject);

  COptions::cleanup();
  CRDFGraphConverter::deleteConverterData();
}

void CRootContainer::initializeChildren()
{
  mpUnknownResource = new CMIRIAMResource("Unknown Resource");
  mpUnknownResource->setMIRIAMDisplayName("-- select --");
  mpUnknownResource->setMIRIAMURI("urn:miriam:unknown");

  mpFunctionList = new CFunctionDB("FunctionDB", this);
  mpFunctionList->load();

  mpDataModelList = new CDataVector<CDataModel>("ModelList", this);

  mpConfiguration = new CConfigurationFile;
  mpConfiguration->load();

  mpUndefined = new CFunction("undefined", this);
  mpUndefined->setInfix("nan");
  mpUndefined->compile();

  mpUnitDefinitionList = new CUnitDefinitionDB("Units list", this);
  CUnitDefinition::updateSIUnitDefinitions(mpUnitDefinitionList);
}

// static
const CDataContainer * CRootContainer::getRoot()
{
  return pRootContainer;
}

// static
CConfigurationFile * CRootContainer::getConfiguration()
{
  return pRootContainer->mpConfiguration;
}

// static
CFunctionDB * CRootContainer::getFunctionList()
{
  return pRootContainer->mpFunctionList;
}

// static
CDataVector< CDataModel > * CRootContainer::getDatamodelList()
{
  return pRootContainer->mpDataModelList;
}

// static
CUnitDefinitionDB *CRootContainer::getUnitList()
{
  return pRootContainer->mpUnitDefinitionList;
}

// static
const CUnitDefinition * CRootContainer::getUnitDefFromSymbol(const std::string symbol)
{
  const CUnitDefinition * pUnitDefinition = pRootContainer->mpUnitDefinitionList->getUnitDefFromSymbol(symbol);

  if (pUnitDefinition == NULL)
    {
      // As a fall back we try to find the name this is needed  e.g. for ohm
      size_t Index = pRootContainer->mpUnitDefinitionList->getIndex(symbol);

      if (Index != C_INVALID_INDEX)
        {
          pUnitDefinition = CRootContainer::getUnitList()->begin() + Index;
        }
    }

  return pUnitDefinition;
}

// static
std::string CRootContainer::quoteUnitDefSymbol(const std::string & symbol)
{
  return pRootContainer->mpUnitDefinitionList->quoteSymbol(symbol);
}

// static
void CRootContainer::replaceSymbol(const std::string & oldSymbol,
                                   const std::string & newSymbol)
{
  CDataVector< CDataModel >::iterator it = pRootContainer->mpDataModelList->begin();
  CDataVector< CDataModel >::iterator end = pRootContainer->mpDataModelList->end();

  for (; it != end; ++it)
    {
      it->getModel()->changeUnitExpressionSymbols(oldSymbol, newSymbol);
    }
}

// static
CDataModel * CRootContainer::addDatamodel()
{
  CDataModel* pDataModel = new CDataModel(pRootContainer->mWithGUI);
  pRootContainer->mpDataModelList->add(pDataModel, true);
  return pDataModel;
}

// static
CFunction * CRootContainer::getUndefinedFunction()
{
  return pRootContainer->mpUndefined;
}

// static
void CRootContainer::functionDefinitionChanged(const CFunction * pFunction)
{
  if (pRootContainer->mpDataModelList == NULL) return;

  CDataVector< CDataModel >::iterator it = pRootContainer->mpDataModelList->begin();
  CDataVector< CDataModel >::iterator end = pRootContainer->mpDataModelList->end();

  for (; it != end; ++it)
    if (it->getModel() != NULL)
      {
        it->getModel()->functionDefinitionChanged(pFunction);
      }
}

//static
CKeyFactory* CRootContainer::getKeyFactory()
{
  return &pRootContainer->mKeyFactory;
}

// static
const CMIRIAMResource & CRootContainer::getUnknownMiriamResource()
{
  return *pRootContainer->mpUnknownResource;
}

// static
bool CRootContainer::removeDatamodel(const CDataModel * pDatamodel)
{
  if (!pDatamodel)
    {
      return false;
    }

  pRootContainer->mpDataModelList->remove((CDataModel *)pDatamodel);
  pdelete(pDatamodel);

  return true;
}

// static
bool CRootContainer::removeDatamodel(const unsigned C_INT32 index)
{
  const CDataModel* pDatamodel = &CRootContainer::getDatamodelList()->operator[](index);
  return CRootContainer::removeDatamodel(pDatamodel);
}

// static
const char * CRootContainer::getLicenseTxt()
{
  return CopasiLicenseTxt;
}

// static
const char * CRootContainer::getLicenseHTML()
{
  return CopasiLicenseHtml;
}
