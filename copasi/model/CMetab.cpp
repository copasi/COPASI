// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "copasi/copasi.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/utility.h"
#include "copasi/report/CKeyFactory.h"
#include "CCompartment.h"
#include "CModel.h"
#include "CMetab.h"
#include "CMetabNameInterface.h"
#include "copasi/function/CExpression.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/math/CMathContainer.h"

#define METAB_MOIETY 7

//static
C_FLOAT64 CMetab::convertToNumber(const C_FLOAT64 & concentration,
                                  const CCompartment & compartment,
                                  const CModel & model)
{return concentration * compartment.getInitialValue() * model.getQuantity2NumberFactor();}

//static
C_FLOAT64 CMetab::convertToConcentration(const C_FLOAT64 & number,
    const CCompartment & compartment,
    const CModel & model)
{return number / compartment.getInitialValue() * model.getNumber2QuantityFactor();}

// static
CMetab * CMetab::fromData(const CData & data)
{
  return new CMetab(data.getProperty(CData::OBJECT_NAME).toString(),
                    NO_PARENT);
}

// virtual
CData CMetab::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CMetab::applyData(const CData & data)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CMetab::CMetab(const std::string & name,
               const CDataContainer * pParent):
  CModelEntity(name, pParent, "Metabolite",
               CDataObject::NonUniqueName),
  mConc(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
  mIConc(0.0),
  mConcRate(0.0),
  mIntensiveNoise(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
  mTT(0.0),
  mpCompartment(NULL),
  mpMoiety(NULL),
  mIsInitialConcentrationChangeAllowed(true),
  mIsInitialParticleNumberChangeAllowed(true)

{
  //mKey = CRootContainer::getKeyFactory()->add("Metabolite", this);
  initObjects();

  setStatus(Status::REACTIONS);

  if (getObjectParent())
    {
      initCompartment(NULL);

      setInitialConcentration(1.0);
      setConcentration(1.0);
    }

  CONSTRUCTOR_TRACE;
}

CMetab::CMetab(const CMetab & src,
               const CDataContainer * pParent):
  CModelEntity(src, pParent),
  mConc(src.mConc),
  mIConc(src.mIConc),
  mConcRate(src.mConcRate),
  mIntensiveNoise(src.mIntensiveNoise),
  mTT(src.mTT),
  mpCompartment(NULL),
  mpMoiety(src.mpMoiety),
  mIsInitialConcentrationChangeAllowed(src.mIsInitialConcentrationChangeAllowed),
  mIsInitialParticleNumberChangeAllowed(src.mIsInitialParticleNumberChangeAllowed)
{
  //mKey = CRootContainer::getKeyFactory()->add("Metabolite", this);

  initObjects();

  initCompartment(src.mpCompartment);
  CONSTRUCTOR_TRACE;
}

CMetab &CMetab::operator=(const CMetabOld & RHS)
{
  setObjectName(RHS.getObjectName());

  setStatus(RHS.mStatus);

  // We need to set the initial particle number since that is the expected for the initial state
  C_FLOAT64 InitialParticleNumber =
    CMetab::convertToNumber(RHS.mIConc, *mpCompartment, *mpModel);
  setInitialValue(InitialParticleNumber);

  mRate = 0.0;
  mConcRate = 0.0;
  mTT = 0.0;

  return *this;  // Assignment operator returns left side.
}

CMetab::~CMetab()
{
  CRootContainer::getKeyFactory()->remove(mKey);
  DESTRUCTOR_TRACE;
}

// virtual
const std::string CMetab::getUnits() const
{
  return "#";
}

// virtual
std::string CMetab::getChildObjectUnits(const CDataObject * pObject) const
{
  if (pObject == mpTTReference)
    {
      return mpModel->getTimeUnit();
    }
  else if (pObject == mpIConcReference ||
           pObject == mpConcReference)
    {
      std::string QuantityUnit = (mpModel != NULL) ? mpModel->getQuantityUnit() : "?";
      std::string CompartmentUnit = (mpCompartment != NULL) ? mpCompartment->getInitialValueReference()->getUnits() : "?";

      return  QuantityUnit + "/(" + CompartmentUnit + ")";
    }
  else if (pObject == mpConcRateReference)
    {
      std::string ConcentrationUnit = getChildObjectUnits(mpConcReference);
      std::string TimeUnit = (mpModel != NULL) ? mpModel->getTimeUnit() : "?";

      return  ConcentrationUnit + "/(" + TimeUnit + ")";
    }

  return CModelEntity::getChildObjectUnits(pObject);
}

void CMetab::cleanup() {}

void CMetab::initCompartment(const CCompartment * pCompartment)
{
  mpCompartment =
    dynamic_cast< const CCompartment * >(getObjectAncestor("Compartment"));

  if (mpCompartment == NULL)
    mpCompartment = pCompartment;

  mPrerequisits.clear();

  if (mpCompartment != NULL)
    mPrerequisits.insert(mpCompartment);
}

const C_FLOAT64 & CMetab::getConcentration() const {return mConc;}

const C_FLOAT64 & CMetab::getInitialConcentration() const {return mIConc;}

const CCompartment * CMetab::getCompartment() const {return mpCompartment;}

void CMetab::setTransitionTime(const C_FLOAT64 & transitionTime)
{mTT = transitionTime;}

const C_FLOAT64 & CMetab::getTransitionTime() const {return mTT;}

CDataObject * CMetab::getTransitionTimeReference() const {return mpTTReference;}

bool CMetab::setObjectParent(const CDataContainer * pParent)
{
  CModelEntity::setObjectParent(pParent);
  initCompartment(NULL);

  Status CurrentStatus = getStatus();

  if (CurrentStatus != Status::FIXED)
    setStatus(Status::FIXED);
  else
    setStatus(Status::REACTIONS);

  setStatus(CurrentStatus);

  return true;
}

// ***** set quantities ********

void CMetab::setConcentration(const C_FLOAT64 concentration)
{
  if (isFixed()) return;

  mConc = concentration;
}

void CMetab::setInitialConcentration(const C_FLOAT64 & initialConcentration)
{
  mIConc = initialConcentration;

  return;
}

CIssue CMetab::compile()
{
  CIssue firstWorstIssue, issue;

  // Prepare the compilation
  CObjectInterface::ContainerList listOfContainer;
  listOfContainer.push_back(getObjectAncestor("Model"));

  CDataModel* pDataModel = getObjectDataModel();

  // Compiling of the rest.
  switch (getStatus())
    {
      case Status::FIXED:
        // Fixed values
        mRate = 0.0;
        mConcRate = 0.0;
        mIntensiveNoise = std::numeric_limits<C_FLOAT64>::quiet_NaN();
        mTT = std::numeric_limits<C_FLOAT64>::infinity();
        break;

      case Status::ASSIGNMENT:
        // Concentration
        issue = mpExpression->compile(listOfContainer);
        mValidity.add(issue);
        firstWorstIssue &= issue;

        // Implicit initial expression
        pdelete(mpInitialExpression);
        pDataModel = getObjectDataModel();
        mpInitialExpression = CExpression::createInitialExpression(*mpExpression, pDataModel);
        mpInitialExpression->setObjectName("InitialExpression");

        // Fixed values
        mRate = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
        mConcRate = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
        mIntensiveNoise = std::numeric_limits<C_FLOAT64>::quiet_NaN();
        mTT = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
        break;

      case Status::ODE:
        // Concentration

        // Rate (particle number rate)
        issue = mpExpression->compile(listOfContainer);
        mValidity.add(issue);
        firstWorstIssue &= issue;

        if (mpNoiseExpression != NULL)
          {
            // Noise (particle number rate)
            issue = mpNoiseExpression->compile(listOfContainer);
            mValidity.add(issue);
            firstWorstIssue &= issue;
          }

        break;

      case Status::REACTIONS:
        break;

      default:
        break;
    }

  // The initial values
  firstWorstIssue &= compileInitialValueDependencies();

  return firstWorstIssue;
}

CIssue CMetab::compileInitialValueDependencies()
{
  CIssue issue; //Default: Success

  CObjectInterface::ContainerList listOfContainer;
  listOfContainer.push_back(getObjectAncestor("Model"));

  // If we have an assignment or a valid initial expression we must update both
  if (getStatus() == Status::ASSIGNMENT ||
      (mpInitialExpression != NULL &&
       mpInitialExpression->getInfix() != ""))
    {
      // Initial concentration
      issue &= mpInitialExpression->compile(listOfContainer);
      mValidity.add(issue);
      return issue;
    }

  return issue;
}

void CMetab::compileIsInitialValueChangeAllowed()
{
  mIsInitialConcentrationChangeAllowed = true;
  mIsInitialParticleNumberChangeAllowed = true;

  if (mpModel == NULL || mpCompartment == NULL) return;

  const CMathContainer & Container = mpModel->getMathContainer();

  CMathObject * pInitialSize = Container.getMathObject(mpCompartment->getInitialValueReference());

  // If the compartment size depends on the initial particle number than the initial concentration may not be changed
  // since [] = # / S = # / f(#).
  mIsInitialConcentrationChangeAllowed =
    !Container.getInitialDependencies().dependsOn(pInitialSize, CCore::SimulationContext::Default,
        Container.getMathObject(mpIValueReference));

  // If the compartment size depends on the initial concentration than initial the particle number may not be changed
  // since # = [] * S = [] * f([]).
  mIsInitialParticleNumberChangeAllowed =
    !Container.getInitialDependencies().dependsOn(pInitialSize, CCore::SimulationContext::Default,
        Container.getMathObject(mpIConcReference));

  return;
}

const bool & CMetab::isInitialValueChangeAllowed(CCore::Framework framework) const
{
  if (framework == CCore::Framework::Concentration)
    return mIsInitialConcentrationChangeAllowed;

  return mIsInitialParticleNumberChangeAllowed;
}

void CMetab::calculate()
{
  switch (getStatus())
    {
      case Status::FIXED:
        break;

      case Status::ASSIGNMENT:
        mConc = mpExpression->calcValue();
        break;

      case Status::ODE:
        mRate = mpCompartment->getValue() * mpExpression->calcValue() * mpModel->getQuantity2NumberFactor();
        break;

      case Status::REACTIONS:

        if (isDependent())
          mValue = mpMoiety->getDependentNumber();

        break;

      default:
        break;
    }
}

void CMetab::initObjects()
{
  mpIValueReference->setObjectName("InitialParticleNumber");
  mpValueReference->setObjectName("ParticleNumber");
  mpRateReference->setObjectName("ParticleNumberRate");

  mpIConcReference = addObjectReference("InitialConcentration", mIConc);
  mpConcReference = addObjectReference("Concentration", mConc);

  mpConcRateReference =
    static_cast<CDataObjectReference<C_FLOAT64> *>(addObjectReference("Rate", mConcRate, CDataObject::ValueDbl));

  mpIntensiveNoiseReference =
    static_cast<CDataObjectReference<C_FLOAT64> *>(addObjectReference("IntensiveNoise", mIntensiveNoise, CDataObject::ValueDbl));

  mpTTReference =
    static_cast<CDataObjectReference<C_FLOAT64> *>(addObjectReference("TransitionTime", mTT, CDataObject::ValueDbl));
}

CDataObject * CMetab::getInitialConcentrationReference() const
{return mpIConcReference;}

CDataObject * CMetab::getConcentrationReference() const
{return mpConcReference;}

CDataObject * CMetab::getConcentrationRateReference() const
{return mpConcRateReference;}

CDataObject * CMetab::getIntensiveNoiseReference() const
{return mpIntensiveNoiseReference;}

C_FLOAT64 CMetab::getConcentrationRate() const
{
  return mConcRate;
}

// virtual
const CDataObject * CMetab::getValueObject() const
{
  return mpConcReference;
}

// virtual
void * CMetab::getValuePointer() const
{
  return const_cast<C_FLOAT64 *>(&mConc);
}

std::ostream & operator<<(std::ostream &os, const CMetab & d)
{
  os << "    ++++CMetab: " << d.getObjectName() << std::endl;
  os << "        mConc " << d.mConc << " mIConc " << d.mIConc << std::endl;
  os << "        mValue (particle number) " << d.mValue << " mIValue " << d.mIValue << std::endl;
  os << "        mRate " << d.mRate << " mTT " << d.mTT << " mStatus " << CModelEntity::StatusName[d.getStatus()] << std::endl;

  if (d.mpCompartment)
    os << "        mpCompartment == " << d.mpCompartment << std::endl;
  else
    os << "        mpCompartment == 0 " << std::endl;

  if (d.mpModel)
    os << "        mpModel == " << d.mpModel << std::endl;
  else
    os << "        mpModel == 0 " << std::endl;

  os << "    ----CMetab " << std::endl;

  return os;
}

C_INT32 CMetab::load(CReadConfig &configbuffer)
{
  C_INT32 Fail = 0;

  std::string tmp;
  Fail = configbuffer.getVariable("Metabolite", "string",
                                  (void *) & tmp,
                                  CReadConfig::SEARCH);

  if (Fail)
    return Fail;

  setObjectName(tmp);

  Fail = configbuffer.getVariable("InitialConcentration", "C_FLOAT64",
                                  (void *) & mIConc);

  setInitialConcentration(mIConc);
  setConcentration(mIConc);

  Status GepasiStatus;
  Fail = configbuffer.getVariable("Type", "C_INT16",
                                  (void *) & GepasiStatus);

  if (Fail)
    return Fail;

  setStatus(GepasiStatus);

  // sanity check
  if ((static_cast<int>(GepasiStatus) < 0) || (static_cast<int>(GepasiStatus) > 7))
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     "The file specifies a non-existing type "
                     "for '%s'.\nReset to internal species.",
                     getObjectName().c_str());
      setStatus(Status::REACTIONS);
    }

  // sanity check
  if ((static_cast<int>(GepasiStatus) != METAB_MOIETY) && (mIConc < 0.0))
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     "The file specifies a negative concentration "
                     "for '%s'.\nReset to default.",
                     getObjectName().c_str());
      mIConc = 1.0;
    }

  return Fail;
}

std::string CMetab::getObjectDisplayName() const
{
  CModel* tmp = dynamic_cast<CModel*>(this->getObjectAncestor("Model"));

  if (tmp)
    {
      return CMetabNameInterface::getDisplayName(tmp, *this, false);
    }

  return CDataObject::getObjectDisplayName();
}

void CMetab::setDependsOnMoiety(const CMoiety * pMoiety)
{mpMoiety = pMoiety;}

bool CMetab::isDependent() const
{return mpMoiety != NULL;}

const CMoiety * CMetab::getMoiety() const
{return mpMoiety;}

//******************* CMetabOld ***************************************************

// static
CMetabOld * CMetabOld::fromData(const CData & data)
{
  return new CMetabOld(data.getProperty(CData::OBJECT_NAME).toString(),
                       NO_PARENT);
}

// virtual
CData CMetabOld::toData() const
{
  CData Data;

  // TODO CRITICAL Implement me!
  fatalError();

  return Data;
}

// virtual
bool CMetabOld::applyData(const CData & data)
{
  bool success = true;

  // TODO CRITICAL Implement me!
  fatalError();

  return success;
}

CMetabOld::CMetabOld(const std::string & name,
                     const CDataContainer * pParent):
  CDataContainer(name, pParent, "Old Metabolite"),
  mIConc(1.0),
  mStatus(CModelEntity::Status::REACTIONS),
  mCompartment()
{CONSTRUCTOR_TRACE;}

CMetabOld::CMetabOld(const CMetabOld & src,
                     const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mIConc(src.mIConc),
  mStatus(src.mStatus),
  mCompartment(src.mCompartment)
{CONSTRUCTOR_TRACE;}

CMetabOld::~CMetabOld() {DESTRUCTOR_TRACE;}

void CMetabOld::cleanup() {}

C_INT32 CMetabOld::load(CReadConfig &configbuffer)
{
  C_INT32 Fail = 0;
  std::string tmp;
  Fail = configbuffer.getVariable("Metabolite", "string",
                                  (void *) & tmp,
                                  CReadConfig::SEARCH);

  if (Fail)
    return Fail;

  setObjectName(tmp);

  Fail = configbuffer.getVariable("Concentration", "C_FLOAT64",
                                  (void *) & mIConc);

  if (Fail)
    return Fail;

  Fail = configbuffer.getVariable("Compartment", "C_INT32",
                                  (void *) & mCompartment);

  if (Fail)
    return Fail;

  C_INT32 Status;

  Fail = configbuffer.getVariable("Type", "C_INT32",
                                  (void *) & Status);

  if (Status == 0)
    mStatus = CModelEntity::Status::FIXED;
  else
    mStatus = CModelEntity::Status::REACTIONS;

  // sanity check
  Status = static_cast<C_INT32>(mStatus);

  if ((Status < 0) || (7 < Status))
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     "The file specifies a non-existing type "
                     "for '%s'.\nReset to internal species.",
                     getObjectName().c_str());
      mStatus = CModelEntity::Status::REACTIONS;
    }

  // sanity check
  if ((Status != METAB_MOIETY) && (mIConc < 0.0))
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     "The file specifies a negative concentration "
                     "for '%s'.\nReset to default.",
                     getObjectName().c_str());
      mIConc = 1.0;
    }

  return Fail;
}

C_INT32 CMetabOld::getIndex() const {return mCompartment;}
