// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>
#include <sstream>

#include "copasi/copasi.h"
#include "CSensProblem.h"
#include "copasi/CopasiDataModel/CDataModel.h"

CSensItem::CSensItem()
  : mSingleObjectCN()
  , mListType(CObjectLists::SINGLE_OBJECT)
{}

CSensItem::CSensItem(const std::string & cn)
  : mSingleObjectCN(cn)
  , mListType(CObjectLists::SINGLE_OBJECT)
{}

CSensItem::CSensItem(CObjectLists::ListType type)
  : mSingleObjectCN()
  , mListType(type)
{}

bool CSensItem::isSingleObject() const
{
  return (mListType == CObjectLists::SINGLE_OBJECT);
}

void CSensItem::setSingleObjectCN(const CCommonName & cn)
{
  mSingleObjectCN = cn;
  //  if (cn != "")
  setListType(CObjectLists::SINGLE_OBJECT);
}

const CCommonName & CSensItem::getSingleObjectCN() const
{
  return mSingleObjectCN;
}

std::string CSensItem::getSingleObjectDisplayName(const CDataModel * pDataModel) const
{
  const CObjectInterface * pObject = pDataModel->getObjectFromCN(mSingleObjectCN);

  if (pObject)
    return pObject->getObjectDisplayName();
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
  else if (getListType() != rhs.getListType())
    return false;

  return true;
}

bool CSensItem::operator!=(const CSensItem & rhs) const
{
  return !(*this == rhs);
}

std::vector< CDataObject * > CSensItem::getVariablesPointerList(CDataModel * pDataModel)
{
  std::vector< CDataObject * > ret;

  if (isSingleObject())
    {
      const CDataObject * tmpObject = CObjectInterface::DataObject(pDataModel->getObjectFromCN(getSingleObjectCN()));

      if (!tmpObject)
        {
          return ret;
        } //return empty list

      if (!tmpObject->hasFlag(CDataObject::ValueDbl))
        {
          return ret;
        } //return empty list

      ret.push_back(const_cast< CDataObject * >(tmpObject));
    }
  else
    {
      ret = CObjectLists::getListOfObjects(getListType(), pDataModel->getModel());
    }

  return ret;
}

// size_t CSensItem::dimensionality() const
// {
//}

//************************ CSensProblem ***************************

// static
const CEnumAnnotation< CTaskEnum::Task, CSensProblem::SubTaskType > CSensProblem::SubTaskTypeToTask(
{
  CTaskEnum::Task::UnsetTask, // Evaluation
  CTaskEnum::Task::steadyState, // SteadyState
  CTaskEnum::Task::timeCourse, // TimeSeries
  CTaskEnum::Task::parameterFitting, // ParameterEstimation
  CTaskEnum::Task::optimization, // Optimization
  CTaskEnum::Task::crosssection //  CrossSection
});

const std::string CSensProblem::SubTaskName[] =
{
  "Evaluation",
  "Steady State",
  "Time Series",
  "Parameter Estimation",
  "Optimization",
  "Cross Section",
  //"Lyapunov Exponents",
  ""
};

const char * CSensProblem::XMLSubTask[] =
{
  "Evaluation",
  "SteadyState",
  "TimeSeries",
  "ParameterEstimation",
  "Optimization",
  "CrossSection",
  //"LyapunovExponents",
  NULL
};

//static
void CSensProblem::createParametersInGroup(CCopasiParameterGroup * pg)
{
  if (!pg)
    return;

  pg->assertParameter("SingleObject", CCopasiParameter::Type::CN, CCommonName(""));
  pg->assertParameter("ObjectListType", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0);
}

//static
void CSensProblem::copySensItemToParameterGroup(const CSensItem * si, CCopasiParameterGroup * pg)
{
  CCommonName cn("");

  if (!pg)
    return;

  if (!si)
    return;

  if (si->isSingleObject())
    cn = si->getSingleObjectCN();

  pg->setValue("SingleObject", cn);
  pg->setValue("ObjectListType", (unsigned C_INT32) si->getListType());
}

//static
void CSensProblem::copyParameterGroupToSensItem(const CCopasiParameterGroup * pg, CSensItem * si)
{

  if (!pg)
    return;

  if (!si)
    return;

  const CCommonName * pCN = &pg->getValue< CCommonName >("SingleObject");
  const CObjectLists::ListType * pLT = &pg->getValue< CObjectLists::ListType >("ObjectListType");

  CCommonName cn("");

  if (pCN)
    cn = *pCN;

  CObjectLists::ListType lt = (CObjectLists::ListType) 0;

  if (pLT)
    lt = *pLT;

  //  if (cn != "")
  si->setSingleObjectCN(cn);
  //  else
  si->setListType(lt);
}

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CSensProblem::CSensProblem(const CDataContainer * pParent)
  : CCopasiProblem(CTaskEnum::Task::sens, pParent)
  , mpSubTaskType(NULL)
  , mpTargetFunctions(NULL)
  , mpVariablesGroup(NULL)
  , mpResultAnnotation(NULL)
  , mpScaledResultAnnotation(NULL)
  , mpCollapsedResultAnnotation(NULL)
{
  initializeParameter();
  initObjects();

  // Default Problem
  CSensItem item;

  item.setListType(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
  setTargetFunctions(item);

  item.setListType(CObjectLists::ALL_PARAMETER_VALUES);
  addVariables(item);

  item.setListType(CObjectLists::EMPTY_LIST);
  addVariables(item);
}

/**
 *  Copy constructor.
 *  @param "const CSensProblem &" src
 */
CSensProblem::CSensProblem(const CSensProblem & src,
                           const CDataContainer * pParent)
  : CCopasiProblem(src, pParent)
  , mpSubTaskType(NULL)
  , mpTargetFunctions(NULL)
  , mpVariablesGroup(NULL)
  , mpResultAnnotation(NULL)
  , mpScaledResultAnnotation(NULL)
  , mpCollapsedResultAnnotation(NULL)
{
  initializeParameter();
  initObjects();
}

void CSensProblem::initObjects()
{
  mpResultAnnotation = new CDataArray("Sensitivities array", this, &mResult, false);
  mpResultAnnotation->setDescription("");
  mpResultAnnotation->setMode(CDataArray::Mode::Objects);

  mpScaledResultAnnotation = new CDataArray("Scaled sensitivities array", this, &mScaledResult, false);
  mpScaledResultAnnotation->setDescription("");
  mpScaledResultAnnotation->setMode(CDataArray::Mode::Objects);

  mpCollapsedResultAnnotation = new CDataArray("Summarized sensitivities array", this, &mCollapsedResult, false);
  mpCollapsedResultAnnotation->setDescription("");
  mpCollapsedResultAnnotation->setMode(CDataArray::Mode::Objects);
}

void CSensProblem::initializeParameter()
{
  mpSubTaskType = (CSensProblem::SubTaskType *) assertParameter("SubtaskType", CCopasiParameter::Type::UINT, (unsigned C_INT32) SteadyState);
  mpTargetFunctions = assertGroup("TargetFunctions");
  mpVariablesGroup = assertGroup("ListOfVariables");

  createParametersInGroup(mpTargetFunctions);
}

/**
 *  Destructor.
 */
CSensProblem::~CSensProblem()
{
  DESTRUCTOR_TRACE;
}

// virtual
CCopasiTask * CSensProblem::getSubTask() const
{
  CDataModel* pDataModel = getObjectDataModel();

  if (pDataModel != NULL)
    {
      CDataVectorN< CCopasiTask >::iterator it = pDataModel->getTaskList()->begin();
      CDataVectorN< CCopasiTask >::iterator end = pDataModel->getTaskList()->end();

      for (; it != end; ++it)
        if (it->getType() == SubTaskTypeToTask[*mpSubTaskType])
          return &*it;
    }

  return NULL;
}

/**
 *   set the problem's SubTaskType:
 */
void CSensProblem::setSubTaskType(const CSensProblem::SubTaskType & type)
{
  *mpSubTaskType = type;
}

/**
 *   get the problem's SubTaskType:
 **/
CSensProblem::SubTaskType CSensProblem::getSubTaskType() const
{
  if (mpSubTaskType)
    return *mpSubTaskType;
  else
    return CSensProblem::Evaluation;
}

CSensItem CSensProblem::getTargetFunctions() const
{
  CSensItem ret;
  CCopasiParameterGroup * tmp;

  tmp = (CCopasiParameterGroup *)(mpTargetFunctions);

  copyParameterGroupToSensItem(tmp, &ret);

  return ret;
}

void CSensProblem::setTargetFunctions(const CSensItem item)
{
  copySensItemToParameterGroup(&item, mpTargetFunctions);
}

size_t CSensProblem::getNumberOfVariables() const
{
  return mpVariablesGroup->size();
}

CSensItem CSensProblem::getVariables(size_t index) const
{
  CSensItem ret;
  CCopasiParameterGroup * tmp;

  tmp = (CCopasiParameterGroup *)(mpVariablesGroup->getParameter(index));

  copyParameterGroupToSensItem(tmp, &ret);

  return ret;
}

void CSensProblem::addVariables(const CSensItem & item)
{
  //create parameter group corresponding to sens item
  CCopasiParameterGroup * tmp;
  mpVariablesGroup->addGroup("Variables");
  tmp = (CCopasiParameterGroup *)(mpVariablesGroup->getParameter(getNumberOfVariables() - 1));

  createParametersInGroup(tmp);

  copySensItemToParameterGroup(&item, tmp);
}

bool CSensProblem::removeVariables()
{
  mpVariablesGroup->clear();
  return true;
}

bool CSensProblem::removeVariables(size_t index)
{
  return mpVariablesGroup->removeParameter(index);
}

bool CSensProblem::changeVariables(size_t index, const CSensItem & item)
{
  size_t num = getNumberOfVariables();

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

CArray & CSensProblem::getResult()
{
  return mResult;
}

const CArray & CSensProblem::getResult() const
{
  return mResult;
}

CDataArray * CSensProblem::getResultAnnotated()
{
  return mpResultAnnotation;
}

const CDataArray * CSensProblem::getResultAnnotated() const
{
  return mpResultAnnotation;
}

CArray & CSensProblem::getScaledResult()
{
  return mScaledResult;
}

const CArray & CSensProblem::getScaledResult() const
{
  return mScaledResult;
}

CDataArray * CSensProblem::getScaledResultAnnotated()
{
  return mpScaledResultAnnotation;
}

const CDataArray * CSensProblem::getScaledResultAnnotated() const
{
  return mpScaledResultAnnotation;
}

CArray & CSensProblem::getCollapsedResult()
{
  return mCollapsedResult;
}

const CArray & CSensProblem::getCollapsedResult() const
{
  return mCollapsedResult;
}

CDataArray * CSensProblem::getCollapsedResultAnnotated()
{
  return mpCollapsedResultAnnotation;
}

const CDataArray * CSensProblem::getCollapsedResultAnnotated() const
{
  return mpCollapsedResultAnnotation;
}

bool CSensProblem::collapsRequested() const
{
  return !getTargetFunctions().isSingleObject();
}

//static
std::vector< CObjectLists::ListType >
CSensProblem::getPossibleTargetFunctions(CSensProblem::SubTaskType type)
{
  std::vector< CObjectLists::ListType > list;

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
        list.push_back(CObjectLists::METAB_CONC_RATES);
        list.push_back(CObjectLists::METAB_PART_RATES);
        list.push_back(CObjectLists::GLOBAL_PARAMETER_RATES);
        break;

      case (CSensProblem::SteadyState):
        list.push_back(CObjectLists::SINGLE_OBJECT);
        list.push_back(CObjectLists::ALL_VARIABLES);
        list.push_back(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
        list.push_back(CObjectLists::NON_CONST_METAB_NUMBERS);
        list.push_back(CObjectLists::METAB_CONC_RATES);
        list.push_back(CObjectLists::METAB_PART_RATES);
        list.push_back(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES);
        list.push_back(CObjectLists::REACTION_CONC_FLUXES);
        list.push_back(CObjectLists::REACTION_PART_FLUXES);
        list.push_back(CObjectLists::REDUCED_JACOBIAN_EV_RE);
        list.push_back(CObjectLists::REDUCED_JACOBIAN_EV_IM);
        break;

      case (CSensProblem::TimeSeries):
        list.push_back(CObjectLists::SINGLE_OBJECT);
        list.push_back(CObjectLists::ALL_VARIABLES);
        list.push_back(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
        list.push_back(CObjectLists::NON_CONST_METAB_NUMBERS);
        list.push_back(CObjectLists::METAB_CONC_RATES);
        list.push_back(CObjectLists::METAB_PART_RATES);
        list.push_back(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES);
        list.push_back(CObjectLists::REACTION_CONC_FLUXES);
        list.push_back(CObjectLists::REACTION_PART_FLUXES);
        //TODO all model variables
        break;

      case (CSensProblem::ParameterEstimation):
      case (CSensProblem::Optimization):
      case (CSensProblem::CrossSection):
        list.push_back(CObjectLists::SINGLE_OBJECT);
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
std::vector< CObjectLists::ListType >
CSensProblem::getPossibleVariables(CSensProblem::SubTaskType type)
{
  std::vector< CObjectLists::ListType > list;

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
        list.push_back(CObjectLists::METAB_CONCENTRATIONS);
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
        list.push_back(CObjectLists::METAB_INITIAL_CONCENTRATIONS);
        //TODO all const values, all model parameters
        break;

      case (TimeSeries):
        list.push_back(CObjectLists::SINGLE_OBJECT);
        list.push_back(CObjectLists::ALL_LOCAL_PARAMETER_VALUES);
        list.push_back(CObjectLists::ALL_PARAMETER_VALUES);
        list.push_back(CObjectLists::METAB_INITIAL_CONCENTRATIONS);
        list.push_back(CObjectLists::ALL_PARAMETER_AND_INITIAL_VALUES);
        //TODO all const values, all model parameters, all initial values
        break;

      case (CSensProblem::ParameterEstimation):
      case (CSensProblem::Optimization):
        list.push_back(CObjectLists::SINGLE_OBJECT);
        list.push_back(CObjectLists::ALL_LOCAL_PARAMETER_VALUES);
        list.push_back(CObjectLists::ALL_PARAMETER_VALUES);
        list.push_back(CObjectLists::METAB_INITIAL_CONCENTRATIONS);
        list.push_back(CObjectLists::ALL_PARAMETER_AND_INITIAL_VALUES);
        break;

      case (CSensProblem::CrossSection):
        list.push_back(CObjectLists::SINGLE_OBJECT);
        list.push_back(CObjectLists::ALL_LOCAL_PARAMETER_VALUES);
        list.push_back(CObjectLists::ALL_PARAMETER_VALUES);
        list.push_back(CObjectLists::METAB_INITIAL_CONCENTRATIONS);
        list.push_back(CObjectLists::ALL_PARAMETER_AND_INITIAL_VALUES);
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
  if (mpResultAnnotation != NULL)
    os << *mpResultAnnotation << std::endl;

  if (mpScaledResultAnnotation != NULL)
    os << *mpScaledResultAnnotation << std::endl;

  if (collapsRequested()
      && mpCollapsedResultAnnotation != NULL)
    os << *mpCollapsedResultAnnotation << std::endl;
}

/**
 * Had to disable the output operator because the datamodel is needed to print
 * a sensitivity item.
std::ostream &operator<<(std::ostream &os, const CSensItem & si)
{
  if (si.isSingleObject())
    os << si.getSingleObjectDisplayName();
  else
    os << si.getListTypeDisplayName();

  return os;
}
 */

std::string CSensItem::print(const CDataModel * pDataModel) const
{
  std::ostringstream os;

  if (this->isSingleObject())
    os << this->getSingleObjectDisplayName(pDataModel);
  else
    os << this->getListTypeDisplayName();

  return os.str();
}

std::ostream & operator<<(std::ostream & os, const CSensProblem & o)
{
  os << "Function(s) to be derived:" << std::endl;
  const CDataModel * pDataModel = o.getObjectDataModel();
  assert(pDataModel != NULL);
  os << o.getTargetFunctions().print(pDataModel) << std::endl
     << std::endl;

  os << "Calculation to perform: "
     << CSensProblem::SubTaskName[o.getSubTaskType()] << std::endl
     << std::endl;

  size_t i, imax = o.getNumberOfVariables();

  for (i = 0; i < imax; ++i)
    {
      os << "Variable(s) for " << i + 1 << ". derivation:" << std::endl;
      os << o.getVariables(i).print(pDataModel) << std::endl
         << std::endl;
    }

  return os;
}

void CSensProblem::print(std::ostream * ostream) const
{
  *ostream << *this;
}

void CSensProblem::initDebugProblem()
{
  CSensItem item;

  item.setSingleObjectCN(this->getCN());
  addVariables(item);

  item.setListType(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
  addVariables(item);
}
