// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"
#include "CSensProblem.h"
#include "CopasiDataModel/CCopasiDataModel.h"

CSensItem::CSensItem()
  : mSingleObjectCN(),
    mListType(CObjectLists::SINGLE_OBJECT)
{}

bool CSensItem::isSingleObject() const
{
  return (mListType == CObjectLists::SINGLE_OBJECT);
}

void CSensItem::setSingleObjectCN(const CCopasiObjectName & cn)
{
  mSingleObjectCN = cn;
  //  if (cn != "")
  setListType(CObjectLists::SINGLE_OBJECT);
}

const CCopasiObjectName & CSensItem::getSingleObjectCN() const
{
  return mSingleObjectCN;
}

std::string CSensItem::getSingleObjectDisplayName(const CCopasiDataModel* pDataModel) const
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

std::vector<CCopasiObject*> CSensItem::getVariablesPointerList(CCopasiDataModel* pDataModel)
{
  std::vector<CCopasiObject*> ret;

  if (isSingleObject())
    {
      const CCopasiObject * tmpObject = CObjectInterface::DataObject(pDataModel->getObjectFromCN(getSingleObjectCN()));

      if (!tmpObject) {return ret;}  //return empty list

      if (!tmpObject->isValueDbl()) {return ret;}  //return empty list

      ret.push_back(const_cast< CCopasiObject * >(tmpObject));
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
  setTargetFunctions(item);

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
  mpResultAnnotation = new CArrayAnnotation("Sensitivities array", this, &mResult, false);
  mpResultAnnotation->setDescription("");
  mpResultAnnotation->setMode(CArrayAnnotation::OBJECTS);

  mpScaledResultAnnotation = new CArrayAnnotation("Scaled sensitivities array", this, &mScaledResult, false);
  mpScaledResultAnnotation->setDescription("");
  mpScaledResultAnnotation->setMode(CArrayAnnotation::OBJECTS);

  mpCollapsedResultAnnotation = new CArrayAnnotation("Summarized sensitivities array", this, &mCollapsedResult, false);
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
  CCopasiParameterGroup* tmp;

  tmp = (CCopasiParameterGroup*)(mpTargetFunctions);

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
  size_t imax = mpVariablesGroup->size();

  for (size_t i = 0; i < imax; ++i)
    mpVariablesGroup->removeParameter(0);

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
      case(CSensProblem::Evaluation):
        list.push_back(CObjectLists::SINGLE_OBJECT);
        list.push_back(CObjectLists::REACTION_CONC_FLUXES);
        list.push_back(CObjectLists::REACTION_PART_FLUXES);
        list.push_back(CObjectLists::METAB_CONC_RATES);
        list.push_back(CObjectLists::METAB_PART_RATES);
        list.push_back(CObjectLists::GLOBAL_PARAMETER_RATES);
        break;

      case(CSensProblem::SteadyState):
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

      case(CSensProblem::TimeSeries):
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

      case(CSensProblem::ParameterEstimation):
      case(CSensProblem::Optimization):
      case(CSensProblem::CrossSection):
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
      case(Evaluation):
        list.push_back(CObjectLists::SINGLE_OBJECT);
        list.push_back(CObjectLists::NON_CONST_METAB_CONCENTRATIONS);
        list.push_back(CObjectLists::METAB_CONCENTRATIONS);
        list.push_back(CObjectLists::NON_CONST_METAB_NUMBERS);
        list.push_back(CObjectLists::NON_CONST_GLOBAL_PARAMETER_VALUES);
        list.push_back(CObjectLists::GLOBAL_PARAMETER_VALUES);
        list.push_back(CObjectLists::ALL_LOCAL_PARAMETER_VALUES);
        list.push_back(CObjectLists::ALL_PARAMETER_VALUES);
        break;

      case(SteadyState):
        list.push_back(CObjectLists::SINGLE_OBJECT);
        list.push_back(CObjectLists::ALL_LOCAL_PARAMETER_VALUES);
        list.push_back(CObjectLists::ALL_PARAMETER_VALUES);
        list.push_back(CObjectLists::METAB_INITIAL_CONCENTRATIONS);
        //TODO all const values, all model parameters
        break;

      case(TimeSeries):
        list.push_back(CObjectLists::SINGLE_OBJECT);
        list.push_back(CObjectLists::ALL_LOCAL_PARAMETER_VALUES);
        list.push_back(CObjectLists::ALL_PARAMETER_VALUES);
        list.push_back(CObjectLists::METAB_INITIAL_CONCENTRATIONS);
        list.push_back(CObjectLists::ALL_PARAMETER_AND_INITIAL_VALUES);
        //TODO all const values, all model parameters, all initial values
        break;

      case(CSensProblem::ParameterEstimation):
      case(CSensProblem::Optimization):
        list.push_back(CObjectLists::SINGLE_OBJECT);
        list.push_back(CObjectLists::ALL_LOCAL_PARAMETER_VALUES);
        list.push_back(CObjectLists::ALL_PARAMETER_VALUES);
        list.push_back(CObjectLists::METAB_INITIAL_CONCENTRATIONS);
        list.push_back(CObjectLists::ALL_PARAMETER_AND_INITIAL_VALUES);
        break;

      case(CSensProblem::CrossSection):
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
  if (mpResultAnnotation)
    os << *mpResultAnnotation << std::endl;

  if (mpScaledResultAnnotation)
    os << *mpScaledResultAnnotation << std::endl;
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

std::string CSensItem::print(const CCopasiDataModel* pDataModel) const
{
  std::ostringstream os;

  if (this->isSingleObject())
    os << this->getSingleObjectDisplayName(pDataModel);
  else
    os << this->getListTypeDisplayName();

  return os.str();
}

std::ostream &operator<<(std::ostream &os, const CSensProblem & o)
{
  os << "Function(s) to be derived:" << std::endl;
  const CCopasiDataModel* pDataModel = o.getObjectDataModel();
  assert(pDataModel != NULL);
  os << o.getTargetFunctions().print(pDataModel) << std::endl << std::endl;

  os << "Calculation to perform: "
     << CSensProblem::SubTaskName[o.getSubTaskType()] << std::endl << std::endl;

  size_t i, imax = o.getNumberOfVariables();

  for (i = 0; i < imax; ++i)
    {
      os << "Variable(s) for " << i + 1 << ". derivation:" << std::endl;
      os << o.getVariables(i).print(pDataModel) << std::endl << std::endl;
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
