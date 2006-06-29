/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensProblem.cpp,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/06/29 09:02:21 $
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
}

const CCopasiObjectName & CSensItem::getSingleObjectCN() const
  {
    return mSingleObjectCN;
  }

std::string CSensItem::getSingleObjectDisplayName() const
  {
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
    //    return mTargetFunctions;
  }

unsigned C_INT32 CSensProblem::getNumberOfVariables() const
  {
    return mpVariablesGroup->size();
  }

CSensItem CSensProblem::getVariables(unsigned C_INT32 index) const
  {}

void CSensProblem::addVariables(const CSensItem & item)
{
  //create parameter group corresponding to sens item
  CCopasiParameterGroup* tmp;
  mpVariablesGroup->addGroup("Variables");
  tmp = (CCopasiParameterGroup*)(mpVariablesGroup->getParameter(getNumberOfVariables() - 1));

  createParametersInGroup(tmp);

  copySensItemToParameterGroup(&item, tmp);
}

void CSensProblem::initDebugProblem()
{
  CSensItem item;

  item.setSingleObjectCN(this->getCN());
  addVariables(item);

  item.setListType(CObjectLists::NON_CONST_METABS);
  addVariables(item);
}
