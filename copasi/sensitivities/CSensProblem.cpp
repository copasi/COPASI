// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensProblem.cpp,v $
//   $Revision: 1.23.2.2.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/07/10 16:36:24 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>

#include "copasi.h"
#include "CSensProblem.h"
#include "CopasiDataModel/CCopasiDataModel.h"

bool CSensItem::isSingleObject() const
  {
    return (mListType == CObjectLists::SINGLE_OBJECT);
  }

void CSensItem::setSingleObjectCN(const CCopasiObjectName & cn)
{
  mSingleObjectCN = cn;
  if (cn != "")
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
}

const CObjectLists::ListType & CSensItem::getListType() const
  {
    return mListType;
  }

std::string CSensItem::getListTypeDisplayName() const
  {
    return CObjectLists::ListTypeName[mListType];
  }

bool CSensItem::operator==(const CSensItem & rhs) const
  {
    if (isSingleObject() != rhs.isSingleObject())
      return false;

    if (isSingleObject())
      {
        if (getSingleObjectCN() != rhs.getSingleObjectCN())
          return false;
      }
    else
      if (getListType() != rhs.getListType())
        return false;

    return true;
  }

bool CSensItem::operator!=(const CSensItem & rhs) const
  {
    return !(*this == rhs);
  }

std::vector<CCopasiObject*> CSensItem::getVariablesPointerList(CModel* pModel)
{
  std::vector<CCopasiObject*> ret;

  if (isSingleObject())
    {
      CCopasiObject* tmpObject = CCopasiContainer::ObjectFromName(getSingleObjectCN());
      if (!tmpObject) {return ret;}  //return empty list
      if (!tmpObject->isValueDbl()) {return ret;}  //return empty list
      ret.push_back(tmpObject);
    }
  else
    {
      ret = CObjectLists::getListOfObjects(getListType(), pModel);
    }

  return ret;
}

// unsigned C_INT32 CSensItem::dimensionality() const
// {
//}

//************************ CSensProblem ***************************

const std::string CSensProblem::SubTaskName[] =
  {
    "Evaluation",
    "Steady State",
    "Time Series",
    //"Lyapunov Exponents",
    ""
  };

const char * CSensProblem::XMLSubTask[] =
  {
    "Evaluation",
    "SteadyState",
    "TimeSeries",
    //"LyapunovExponents",
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
  CCopasiObjectName cn("");

  if (!pg) return; if (!si) return;

  if (si->isSingleObject())
    cn = si->getSingleObjectCN();

  pg->setValue("SingleObject", cn);
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

  //  if (cn != "")
  si->setSingleObjectCN(cn);
  //  else
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
    mpVariablesGroup(NULL),
    mpResultAnnotation(NULL),
    mpScaledResultAnnotation(NULL),
    mpCollapsedResultAnnotation(NULL)
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

  //create a useful default problem
  setSubTaskType(SteadyState);

  CSensItem item;

  item.setListType(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
  changeTargetFunctions(item);

  item.setListType(CObjectLists::ALL_PARAMETER_VALUES);
  addVariables(item);

  //  initDebugProblem();
  initObjects();
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
    mpVariablesGroup(NULL),
    mpResultAnnotation(NULL),
    mpScaledResultAnnotation(NULL),
    mpCollapsedResultAnnotation(NULL)
{
  mpSubTaskType = (CSensProblem::SubTaskType*)getValue("SubtaskType").pUINT;
  mpTargetFunctions = dynamic_cast<CCopasiParameterGroup*>(getParameter("TargetFunctions"));
  mpVariablesGroup = dynamic_cast<CCopasiParameterGroup*>(getParameter("ListOfVariables"));

  initObjects();
  CONSTRUCTOR_TRACE;
}

void CSensProblem::initObjects()
{
  mpResultAnnotation = new CArrayAnnotation("Sensitivities array", this, &mResult);
  mpResultAnnotation->setDescription("");
  mpResultAnnotation->setMode(CArrayAnnotation::OBJECTS);

  mpScaledResultAnnotation = new CArrayAnnotation("Scaled sensitivities array", this, &mScaledResult);
  mpScaledResultAnnotation->setDescription("");
  mpScaledResultAnnotation->setMode(CArrayAnnotation::OBJECTS);

  mpCollapsedResultAnnotation = new CArrayAnnotation("Summarized sensitivities array", this, &mCollapsedResult);
  mpCollapsedResultAnnotation->setDescription("");
  mpCollapsedResultAnnotation->setMode(CArrayAnnotation::OBJECTS);
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
      return CSensProblem::Evaluation;
  }

CSensItem CSensProblem::getTargetFunctions() const
  {
    CSensItem ret;
    CCopasiParameterGroup* tmp;

    tmp = (CCopasiParameterGroup*)(mpTargetFunctions);

    copyParameterGroupToSensItem(tmp, &ret);

    return ret;
  }

void CSensProblem::changeTargetFunctions(const CSensItem item)
{
  copySensItemToParameterGroup(&item, mpTargetFunctions);
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

bool CSensProblem::removeVariables()
{
  C_INT32 imax = mpVariablesGroup->size();
  for (C_INT32 i = 0; i < imax; ++i)
    mpVariablesGroup->removeParameter(0);
  return true;
}

bool CSensProblem::removeVariables(unsigned C_INT32 index)
{
  return mpVariablesGroup->removeParameter(index);
}

bool CSensProblem::changeVariables(unsigned C_INT32 index, const CSensItem & item)
{
  unsigned C_INT32 num = getNumberOfVariables();

  if (index > num)
    return false;

  if (index == num)
    addVariables(item);
  else
    {
      CCopasiParameterGroup * tmp =
        (CCopasiParameterGroup *)(mpVariablesGroup->getParameter(index));
      copySensItemToParameterGroup(&item, tmp);
    }

  return true;
}

CCopasiArray & CSensProblem::getResult()
{
  return mResult;
}

const CCopasiArray & CSensProblem::getResult() const
  {
    return mResult;
  }

CArrayAnnotation * CSensProblem::getResultAnnotated()
{
  return mpResultAnnotation;
}

const CArrayAnnotation * CSensProblem::getResultAnnotated() const
  {
    return mpResultAnnotation;
  }

CCopasiArray & CSensProblem::getScaledResult()
{
  return mScaledResult;
}

const CCopasiArray & CSensProblem::getScaledResult() const
  {
    return mScaledResult;
  }

CArrayAnnotation * CSensProblem::getScaledResultAnnotated()
{
  return mpScaledResultAnnotation;
}

const CArrayAnnotation * CSensProblem::getScaledResultAnnotated() const
  {
    return mpScaledResultAnnotation;
  }

CCopasiArray & CSensProblem::getCollapsedResult()
{
  return mCollapsedResult;
}

const CCopasiArray & CSensProblem::getCollapsedResult() const
  {
    return mCollapsedResult;
  }

CArrayAnnotation * CSensProblem::getCollapsedResultAnnotated()
{
  return mpCollapsedResultAnnotation;
}

const CArrayAnnotation * CSensProblem::getCollapsedResultAnnotated() const
  {
    return mpCollapsedResultAnnotation;
  }

bool CSensProblem::collapsRequested() const
  {
    return !getTargetFunctions().isSingleObject();
  }

//static
std::vector<CObjectLists::ListType>
CSensProblem::getPossibleTargetFunctions(CSensProblem::SubTaskType type)
{
  std::vector<CObjectLists::ListType> list;

  //list.push_back(CObjectLists::EMPTY_LIST);

  // Add new functions here, under applicable SubTaskType case.
  // Don't forget to provide for a string value in
  //   getTargetFunctionName()
  switch (type)
    {
    case (CSensProblem::Evaluation):
            list.push_back(CObjectLists::SINGLE_OBJECT);
      list.push_back(CObjectLists::REACTION_CONC_FLUXES);
      list.push_back(CObjectLists::REACTION_PART_FLUXES);
      list.push_back(CObjectLists::NON_CONST_METAB_CONC_RATES);
      list.push_back(CObjectLists::NON_CONST_METAB_PART_RATES);
      list.push_back(CObjectLists::GLOBAL_PARAMETER_RATES);
      break;

    case (CSensProblem::SteadyState):
            list.push_back(CObjectLists::SINGLE_OBJECT);
      list.push_back(CObjectLists::ALL_VARIABLES);
      list.push_back(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
      list.push_back(CObjectLists::NON_CONST_METAB_NUMBERS);
      list.push_back(CObjectLists::NON_CONST_METAB_CONC_RATES);
      list.push_back(CObjectLists::NON_CONST_METAB_PART_RATES);
      list.push_back(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES);
      list.push_back(CObjectLists::REACTION_CONC_FLUXES);
      list.push_back(CObjectLists::REACTION_PART_FLUXES);
      break;

    case (CSensProblem::TimeSeries):
            list.push_back(CObjectLists::SINGLE_OBJECT);
      list.push_back(CObjectLists::ALL_VARIABLES);
      list.push_back(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
      list.push_back(CObjectLists::NON_CONST_METAB_NUMBERS);
      list.push_back(CObjectLists::NON_CONST_METAB_CONC_RATES);
      list.push_back(CObjectLists::NON_CONST_METAB_PART_RATES);
      list.push_back(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES);
      list.push_back(CObjectLists::REACTION_CONC_FLUXES);
      list.push_back(CObjectLists::REACTION_PART_FLUXES);
      //TODO all model variables
      break;

      /*case (CSensProblem::LyapunovExp):
              list.push_back(CObjectLists::SINGLE_OBJECT);
              list.push_back(CObjectLists::NON_CONST_METAB_NUMBERS);
              list.push_back(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
              list.push_back(CObjectLists::REACTION_CONC_FLUXES);
              list.push_back(CObjectLists::NON_CONST_METAB_PART_RATES);
        break;*/
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
    case (Evaluation):
            list.push_back(CObjectLists::SINGLE_OBJECT);
      list.push_back(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
      list.push_back(CObjectLists::ALL_METAB_CONCENTRATIONS);
      list.push_back(CObjectLists::NON_CONST_METAB_NUMBERS);
      list.push_back(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES);
      list.push_back(CObjectLists::GLOBAL_PARAMETER_VALUES);
      list.push_back(CObjectLists::ALL_LOCAL_PARAMETER_VALUES);
      list.push_back(CObjectLists::ALL_PARAMETER_VALUES);
      break;

    case (SteadyState):
            list.push_back(CObjectLists::SINGLE_OBJECT);
      list.push_back(CObjectLists::ALL_LOCAL_PARAMETER_VALUES);
      list.push_back(CObjectLists::ALL_PARAMETER_VALUES);
      list.push_back(CObjectLists::ALL_METAB_INITIAL_CONCENTRATIONS);
      //TODO all const values, all model parameters
      break;

    case (TimeSeries):
            list.push_back(CObjectLists::SINGLE_OBJECT);
      list.push_back(CObjectLists::ALL_LOCAL_PARAMETER_VALUES);
      list.push_back(CObjectLists::ALL_PARAMETER_VALUES);
      list.push_back(CObjectLists::ALL_METAB_INITIAL_CONCENTRATIONS);
      list.push_back(CObjectLists::ALL_PARAMETER_AND_INITIAL_VALUES);
      //TODO all const values, all model parameters, all initial values
      break;

      /*case (LyapunovExp):
              list.push_back(CObjectLists::SINGLE_OBJECT);
              list.push_back(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
              list.push_back(CObjectLists::GLOBAL_PARAMETER_VALUES);
              list.push_back(CObjectLists::ALL_LOCAL_PARAMETER_VALUES);
              list.push_back(CObjectLists::ALL_PARAMETER_VALUES);
              list.push_back(CObjectLists::ALL_PARAMETER_AND_INITIAL_VALUES);
        break;*/
    }

  return list;
}

void CSensProblem::printResult(std::ostream * ostream) const
{
    std::ostream & os = *ostream;

    //os << "Sensitivities result." << std::endl;
    if (mpResultAnnotation)
      os << *mpResultAnnotation << std::endl;
    if (mpScaledResultAnnotation)
      os << *mpScaledResultAnnotation << std::endl;
  }

std::ostream &operator<<(std::ostream &os, const CSensItem & si)
{
  if (si.isSingleObject())
    os << si.getSingleObjectDisplayName();
  else
    os << si.getListTypeDisplayName();

  return os;
}

std::ostream &operator<<(std::ostream &os, const CSensProblem & o)
{
  os << "Function(s) to be derived:" << std::endl;
  os << o.getTargetFunctions() << std::endl << std::endl;

  os << "Calculation to perform: "
  << CSensProblem::SubTaskName[o.getSubTaskType()] << std::endl << std::endl;

  unsigned C_INT32 i, imax = o.getNumberOfVariables();
  for (i = 0; i < imax; ++i)
    {
      os << "Variable(s) for " << i + 1 << ". derivation:" << std::endl;
      os << o.getVariables(i) << std::endl << std::endl;
    }

  return os;
}

void CSensProblem::print(std::ostream * ostream) const
  {*ostream << *this;}

void CSensProblem::initDebugProblem()
{
  CSensItem item;

  item.setSingleObjectCN(this->getCN());
  addVariables(item);

  item.setListType(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
  addVariables(item);
}
