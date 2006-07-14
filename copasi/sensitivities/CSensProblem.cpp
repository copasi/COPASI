/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensProblem.cpp,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: tjohann $
   $Date: 2006/07/14 12:26:43 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>

#include "copasi.h"
#include "CSensProblem.h"
#include "CopasiDataModel/CCopasiDataModel.h"

bool CSensItem::isSingleObject() const
  {
    return mIsSingleObject;
  }

void CSensItem::setSingleObjectCN(const CCopasiObjectName & cn)
{
  mSingleObjectCN = cn;
  mIsSingleObject = true;
  setListType(CObjectLists::SINGLE_OBJECT);
}

const CCopasiObjectName & CSensItem::getSingleObjectCN() const
  {
    return mSingleObjectCN;
  }

std::string CSensItem::getSingleObjectDisplayName() const
  {
    CCopasiObject* tmpObject = CCopasiContainer::ObjectFromName(mSingleObjectCN);
    if (tmpObject)
      return tmpObject->getObjectDisplayName();
    else
      return "";
  }

void CSensItem::setListType(CObjectLists::ListType lt)
{
  mListType = lt;
  mIsSingleObject = false;
}

const CObjectLists::ListType & CSensItem::getListType() const
  {
    return mListType;
  }

std::string CSensItem::getListTypeDisplayName() const
  {
    return "";
  }

//************************ CSensProblem ***************************

const std::string CSensProblem::SubTaskName[] =
  {
    "Not Set",
    "Steady State",
    "Time Series",
    "Lyapunov Exponents",
    ""
  };

const char * CSensProblem::XMLSubTask[] =
  {
    "NotSet",
    "SteadyState",
    "TimeSeries",
    "LyapunovExponents",
    NULL
  };

//static
void CSensProblem::createParametersInGroup(CCopasiParameterGroup *pg)
{
  if (!pg) return;

  pg->addParameter("SingleObject", CCopasiParameter::CN, CCopasiObjectName(""));
  pg->addParameter("ObjectListType", CCopasiParameter::UINT, (unsigned C_INT32) 0);
}

//static
void CSensProblem::copySensItemToParameterGroup(const CSensItem * si, CCopasiParameterGroup *pg)
{
  if (!pg) return; if (!si) return;

  if (si->isSingleObject())
    pg->setValue("SingleObject", si->getSingleObjectCN());
  else
    pg->setValue("ObjectListType", (unsigned C_INT32)si->getListType());
}

//static
void CSensProblem::copyParameterGroupToSensItem(const CCopasiParameterGroup *pg, CSensItem * si)
{
  if (!pg) return; if (!si) return;

  CCopasiObjectName* pCN = pg->getValue("SingleObject").pCN;
  CObjectLists::ListType* pLT = (CObjectLists::ListType*)pg->getValue("ObjectListType").pUINT;

  CCopasiObjectName cn("");
  if (pCN) cn = *pCN;

  CObjectLists::ListType lt = (CObjectLists::ListType)0;
  if (pLT) lt = *pLT;

  if (cn != "")
    si->setSingleObjectCN(cn);
  else
    si->setListType(lt);
}

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CSensProblem::CSensProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::sens, pParent),
    mpSubTaskType(NULL),
    mpTargetFunctions(NULL),
    mpVariablesGroup(NULL)
{
  addParameter("SubtaskType", CCopasiParameter::UINT, (unsigned C_INT32) 0);
  mpSubTaskType = (CSensProblem::SubTaskType*)getValue("SubtaskType").pUINT;

  //---------------------------------------------------
  addGroup("TargetFunctions");
  mpTargetFunctions = dynamic_cast<CCopasiParameterGroup*>(getParameter("TargetFunctions"));
  createParametersInGroup(mpTargetFunctions);

  //---------------------------------------------------
  addGroup("ListOfVariables");
  mpVariablesGroup = dynamic_cast<CCopasiParameterGroup*>(getParameter("ListOfVariables"));

  //initDebugProblem();
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CSensProblem &" src
 */
CSensProblem::CSensProblem(const CSensProblem & src,
                           const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    mpSubTaskType(NULL),
    mpTargetFunctions(NULL),
    mpVariablesGroup(NULL)
{
  mpSubTaskType = (CSensProblem::SubTaskType*)getValue("SubtaskType").pUINT;
  mpTargetFunctions = dynamic_cast<CCopasiParameterGroup*>(getParameter("TargetFunctions"));
  mpVariablesGroup = dynamic_cast<CCopasiParameterGroup*>(getParameter("ListOfVariables"));
  CONSTRUCTOR_TRACE;
}

/**
 *  Destructor.
 */
CSensProblem::~CSensProblem()
{DESTRUCTOR_TRACE;}

/**
 *   set the problem's SubTaskType:
 */
void
CSensProblem::setSubTaskType(const CSensProblem::SubTaskType & type)
{*mpSubTaskType = type;}

/**
 *   get the problem's SubTaskType:
 **/
const CSensProblem::SubTaskType
CSensProblem::getSubTaskType() const
  {
    if (mpSubTaskType)
      return *mpSubTaskType;
    else
      return CSensProblem::unset;
  }

CSensItem CSensProblem::getTargetFunctions() const
  {
    CSensItem ret;
    CCopasiParameterGroup* tmp;

    tmp = (CCopasiParameterGroup*)(mpTargetFunctions);

    copyParameterGroupToSensItem(tmp, &ret);

    return ret;
  }

unsigned C_INT32 CSensProblem::getNumberOfVariables() const
  {
    return mpVariablesGroup->size();
  }

CSensItem CSensProblem::getVariables(unsigned C_INT32 index) const
  {
    CSensItem ret;
    CCopasiParameterGroup* tmp;

    tmp = (CCopasiParameterGroup*)(mpVariablesGroup->getParameter(index));

    copyParameterGroupToSensItem(tmp, &ret);

    return ret;
  }

void CSensProblem::addVariables(const CSensItem & item)
{
  //create parameter group corresponding to sens item
  CCopasiParameterGroup* tmp;
  mpVariablesGroup->addGroup("Variables");
  tmp = (CCopasiParameterGroup*)(mpVariablesGroup->getParameter(getNumberOfVariables() - 1));

  createParametersInGroup(tmp);

  copySensItemToParameterGroup(&item, tmp);
}

//static
std::vector<CObjectLists::ListType>
CSensProblem::getPossibleTargetFunctions(CSensProblem::SubTaskType type)
{
  std::vector<CObjectLists::ListType> list;

  // the 'unset' type, abusing CObjectLists::ALL_METABS
  list.push_back((CObjectLists::ListType) 0);

  // Add new functions here, under applicable SubTaskType case.
  // Don't forget to provide for a string value in
  //   getTargetFunctionName()
  switch (type)
    {
    case (CSensProblem::unset):
            // all available target functions
            list.push_back(CObjectLists::SINGLE_OBJECT);
      list.push_back(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
      list.push_back(CObjectLists::NON_CONST_METAB_NUMBERS);
      list.push_back(CObjectLists::NON_CONST_METAB_CONC_RATES);
      list.push_back(CObjectLists::NON_CONST_METAB_PART_RATES);
      list.push_back(CObjectLists::REACTION_CONC_FLUXES);
      list.push_back(CObjectLists::REACTION_PART_FLUXES);
      break;

    case (CSensProblem::SteadyState):
            list.push_back(CObjectLists::SINGLE_OBJECT);
      list.push_back(CObjectLists::NON_CONST_METAB_NUMBERS);
      list.push_back(CObjectLists::NON_CONST_METAB_CONC_RATES);
      list.push_back(CObjectLists::REACTION_CONC_FLUXES);
      list.push_back(CObjectLists::REACTION_PART_FLUXES);
      break;

    case (CSensProblem::TimeSeries):
            list.push_back(CObjectLists::SINGLE_OBJECT);
      list.push_back(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
      list.push_back(CObjectLists::NON_CONST_METAB_CONC_RATES);
      list.push_back(CObjectLists::NON_CONST_METAB_PART_RATES);
      list.push_back(CObjectLists::REACTION_PART_FLUXES);
      break;

    case (CSensProblem::LyapunovExp):
            list.push_back(CObjectLists::SINGLE_OBJECT);
      list.push_back(CObjectLists::NON_CONST_METAB_NUMBERS);
      list.push_back(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
      list.push_back(CObjectLists::REACTION_CONC_FLUXES);
      list.push_back(CObjectLists::NON_CONST_METAB_PART_RATES);
      break;
    }

  return list;
}

//static
std::vector<CObjectLists::ListType>
CSensProblem::getPossibleVariables(CSensProblem::SubTaskType type)
{
  std::vector<CObjectLists::ListType> list;

  // the 'unset' type, abusing CObjectLists::ALL_METABS
  list.push_back((CObjectLists::ListType) 0);

  // Add new variables here, to applicable SubTaskType case.
  // Don't forget to provide for a string value in
  //   getVariableName()
  switch (type)
    {
    case (unset):
          case (SteadyState):
            case (TimeSeries):
              case (LyapunovExp):
                  // all available target functions
                  list.push_back(CObjectLists::SINGLE_OBJECT);
      list.push_back(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
      list.push_back(CObjectLists::GLOBAL_PARAMETERS);
    }

  return list;
}

void CSensProblem::initDebugProblem()
{
  CSensItem item;

  item.setSingleObjectCN(this->getCN());
  addVariables(item);

  item.setListType(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
  addVariables(item);
}
