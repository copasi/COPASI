// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMetab.cpp,v $
//   $Revision: 1.127 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/09/17 14:16:17 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/utility.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "CCompartment.h"
#include "CModel.h"
#include "CMetab.h"
#include "CMetabNameInterface.h"
#include "function/CExpression.h"

//static
C_FLOAT64 CMetab::convertToNumber(const C_FLOAT64 & concentration,
                                  const CCompartment & compartment,
                                  const CModel & model)
{return concentration * compartment.getValue() * model.getQuantity2NumberFactor();}

//static
C_FLOAT64 CMetab::convertToConcentration(const C_FLOAT64 & number,
    const CCompartment & compartment,
    const CModel & model)
{return number / compartment.getValue() * model.getNumber2QuantityFactor();}

CMetab::CMetab(const std::string & name,
               const CCopasiContainer * pParent):
    CModelEntity(name, pParent, "Metabolite",
                 CCopasiObject::NonUniqueName),
    mConc(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mIConc(0.0),
    mConcRate(0.0),
    mTT(0.0),
    mpCompartment(NULL),
    mpMoiety(NULL),
    mMoieties()
{
  mKey = GlobalKeys.add("Metabolite", this);
  initObjects();

  setStatus(REACTIONS);

  if (getObjectParent())
    {
      initCompartment(NULL);

      setInitialConcentration(1.0);
      setConcentration(1.0);
    }

  CONSTRUCTOR_TRACE;
}

CMetab::CMetab(const CMetab & src,
               const CCopasiContainer * pParent):
    CModelEntity(src, pParent),
    mConc(src.mConc),
    mIConc(src.mIConc),
    mConcRate(src.mConcRate),
    mTT(src.mTT),
    mpCompartment(NULL),
    mpMoiety(src.mpMoiety),
    mMoieties()
{
  mKey = GlobalKeys.add("Metabolite", this);

  initObjects();

  initCompartment(src.mpCompartment);
  CONSTRUCTOR_TRACE;
}

CMetab &CMetab::operator=(const CMetabOld &RHS)
{
  setObjectName(RHS.getObjectName());

  setStatus(RHS.mStatus);

  setInitialConcentration(RHS.mIConc);
  refreshInitialConcentration();

  mRate = 0.0;
  mConcRate = 0.0;
  mTT = 0.0;

  return *this;  // Assignment operator returns left side.
}

CMetab::~CMetab()
{
  GlobalKeys.remove(mKey);
  DESTRUCTOR_TRACE;
}

void CMetab::cleanup() {}

void CMetab::initCompartment(const CCompartment * pCompartment)
{
  mpCompartment =
    dynamic_cast< const CCompartment * >(getObjectAncestor("Compartment"));

  if (!mpCompartment)
    mpCompartment = pCompartment;
}

const C_FLOAT64 & CMetab::getConcentration() const {return mConc;}

const C_FLOAT64 & CMetab::getInitialConcentration() const {return mIConc;}

const CCompartment * CMetab::getCompartment() const {return mpCompartment;}

const CModel * CMetab::getModel() const {return mpModel;}

void CMetab::setTransitionTime(const C_FLOAT64 & transitionTime)
{mTT = transitionTime;}

const C_FLOAT64 & CMetab::getTransitionTime() const {return mTT;}

bool CMetab::setObjectParent(const CCopasiContainer * pParent)
{
  CModelEntity::setObjectParent(pParent);
  initCompartment(NULL);

  Status CurrentStatus = getStatus();

  if (CurrentStatus != FIXED)
    setStatus(FIXED);
  else
    setStatus(REACTIONS);

  setStatus(CurrentStatus);

  return true;
}

// ***** set quantities ********

void CMetab::setConcentration(const C_FLOAT64 concentration)
{
  if (isFixed()) return;

  mConc = concentration;
  *mpValueData = concentration * mpCompartment->getValue()
                 * mpModel->getQuantity2NumberFactor();

#ifdef COPASI_DEBUG
  //if (mStatus == METAB_FIXED)
  //std::cout << "warning: set the transient concentration on a fixed metab" << std::endl;
#endif
}

void CMetab::setInitialConcentration(const C_FLOAT64 & initialConcentration)
{
  mIConc = initialConcentration;

  if (isnan(mpCompartment->getInitialValue()) ||
      isnan(initialConcentration))
    *mpIValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  else
    *mpIValue =
      initialConcentration * mpCompartment->getInitialValue() * mpModel->getQuantity2NumberFactor();

  std::set< CMoiety * >::iterator it = mMoieties.begin();
  std::set< CMoiety * >::iterator end = mMoieties.end();

  for (; it != end; ++it)
    (*it)->refreshInitialValue();

  return;
}

void CMetab::setValue(const C_FLOAT64 & value)
{
  if (isFixed()) return;

  mConc = value / mpCompartment->getValue()
          * mpModel->getNumber2QuantityFactor();
  *mpValueAccess = value;

#ifdef COPASI_DEBUG
  //  if (mStatus == METAB_FIXED)
  //    std::cout << "warning: set the transient particle number on a fixed metab" << std::endl;
#endif
}

void CMetab::setInitialValue(const C_FLOAT64 & initialValue)
{
  if (*mpIValue == initialValue) return;

  *mpIValue = initialValue;

  if (isnan(mpCompartment->getInitialValue()) || isnan(initialValue))
    mIConc = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  else if (fabs(mpCompartment->getInitialValue()) > DBL_MIN)
    mIConc =
      initialValue / mpCompartment->getInitialValue() * mpModel->getNumber2QuantityFactor();

  std::set< CMoiety * >::iterator it = mMoieties.begin();
  std::set< CMoiety * >::iterator end = mMoieties.end();

  for (; it != end; ++it)
    (*it)->refreshInitialValue();

  return;
}

void CMetab::refreshInitialValue()
{
  *mpIValue = mIConc * mpCompartment->getInitialValue() * mpModel->getQuantity2NumberFactor();
}

void CMetab::refreshInitialConcentration()
{
  if (mpInitialExpression != NULL)
    mIConc = mpInitialExpression->calcValue();
  else
    mIConc =
      *mpIValue / mpCompartment->getInitialValue() * mpModel->getNumber2QuantityFactor();

  if (isFixed()) mConc = mIConc;
}

void CMetab::refreshConcentration()
{
  mConc = *mpValueAccess / mpCompartment->getValue() * mpModel->getNumber2QuantityFactor();
}

void CMetab::refreshNumber()
{
  *mpValueAccess = mConc * mpCompartment->getValue() * mpModel->getQuantity2NumberFactor();
}

void CMetab::setStatus(const CModelEntity::Status & status)
{
  Status OldStatus = getStatus();

  CModelEntity::setStatus(status);

  if (status == OldStatus) return;

  std::set< const CCopasiObject * > Dependencies;

  const CCopasiObject * pVolumeReference = NULL;
  if (mpCompartment)
    pVolumeReference = mpCompartment->getObject(CCopasiObjectName("Reference=Volume"));

  mpIValueReference->setRefresh(this, &CMetab::refreshInitialValue);

  switch (getStatus())
    {
    case FIXED:
      break;

    case ASSIGNMENT:
      Dependencies.insert(mpConcReference);
      if (pVolumeReference)
        Dependencies.insert(pVolumeReference);
      mpValueReference->setDirectDependencies(Dependencies);
      mpValueReference->setRefresh(this, &CMetab::refreshNumber);

      mpConcReference->setDirectDependencies(mpExpression->getDirectDependencies());
      mpConcReference->setRefresh(this, &CMetab::calculate);

      // The dependecies and refresh of the rate are correct (see CModelEntity::setStatus).

      mpConcRateReference->setDirectDependencies(mpRateReference->getDirectDependencies());
      mpConcRateReference->clearRefresh();
      break;

    case ODE:
      mpValueReference->setDirectDependencies(Dependencies);
      mpValueReference->clearRefresh();

      Dependencies.insert(mpValueReference);
      if (pVolumeReference)
        Dependencies.insert(pVolumeReference);
      mpConcReference->setDirectDependencies(Dependencies);
      mpConcReference->setRefresh(this, &CMetab::refreshConcentration);

      Dependencies.clear();
      Dependencies.insert(mpConcRateReference);
      if (pVolumeReference)
        Dependencies.insert(pVolumeReference);
      mpRateReference->setDirectDependencies(Dependencies);
      mpRateReference->setRefresh(this, &CMetab::refreshRate);

      mpConcRateReference->setDirectDependencies(mpExpression->getDirectDependencies());
      mpConcRateReference->setRefresh(this, &CMetab::calculate);

      break;

    case REACTIONS:
      mpValueReference->setDirectDependencies(Dependencies);
      mpValueReference->clearRefresh();

      if (pVolumeReference)
        Dependencies.insert(pVolumeReference);

      Dependencies.insert(mpValueReference);
      mpConcReference->setDirectDependencies(Dependencies);
      mpConcReference->setRefresh(this, &CMetab::refreshConcentration);

      mpRateReference->setRefresh(this, &CMetab::refreshRate);

      Dependencies.clear();
      if (pVolumeReference)
        Dependencies.insert(pVolumeReference);

      Dependencies.insert(mpRateReference);
      mpConcRateReference->setDirectDependencies(Dependencies);
      mpConcRateReference->setRefresh(this, &CMetab::refreshConcentrationRate);
      break;

    default:
      break;
    }

  if (mpModel && mpCompartment) refreshConcentration();
}

#ifdef WIN32
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

bool CMetab::compile()
{
  bool success = true;
  std::set<const CCopasiObject *> Dependencies;
  std::vector< CCopasiContainer * > listOfContainer;
  listOfContainer.push_back(getObjectAncestor("Model"));

  mRateVector.clear();
  mpRateReference->setDirectDependencies(Dependencies);
  mpRateReference->clearRefresh();

  mpConcRateReference->setDirectDependencies(Dependencies);
  mpConcRateReference->clearRefresh();

  mpTTReference->setDirectDependencies(Dependencies);
  mpTTReference->clearRefresh();

  const CCopasiObject * pVolumeReference = NULL;
  if (mpCompartment)
    pVolumeReference = mpCompartment->getValueReference();

  Dependencies.insert(mpIConcReference);
  if (mpCompartment)
    Dependencies.insert(mpCompartment->getInitialValueReference());
  mpIValueReference->setDirectDependencies(Dependencies);
  Dependencies.clear();

  switch (getStatus())
    {
    case FIXED:
      if (mpCompartment)
        Dependencies.insert(mpCompartment->getInitialValueReference());
      mpIConcReference->setDirectDependencies(Dependencies);
      Dependencies.clear();

      mRate = 0.0;
      mConcRate = 0.0;
      mTT = 2 * DBL_MAX;
      break;

    case ASSIGNMENT:
      Dependencies.insert(mpConcReference);
      if (pVolumeReference)
        Dependencies.insert(pVolumeReference);
      mpValueReference->setDirectDependencies(Dependencies);
      mpValueReference->setRefresh(this, &CMetab::refreshNumber);
      Dependencies.clear();
      success = mpExpression->compile(listOfContainer);

      mpConcReference->setDirectDependencies(mpExpression->getDirectDependencies());
      mpConcReference->setRefresh(this, &CMetab::calculate);

      pdelete(mpInitialExpression);
      mpInitialExpression = CExpression::createInitialExpression(*mpExpression);

      if (mpInitialExpression != NULL)
        {
          success &= mpInitialExpression->compile(listOfContainer);
          mpIConcReference->setDirectDependencies(mpInitialExpression->getDirectDependencies());
          mpIConcReference->setRefresh(this, &CMetab::refreshInitialConcentration);
        }
      else
        {
          mpIConcReference->setDirectDependencies(Dependencies);
          mpIConcReference->clearRefresh();
        }

      mRate = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
      mConcRate = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
      mTT = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
      break;

    case ODE:
      if (mpCompartment)
        Dependencies.insert(mpCompartment->getInitialValueReference());
      mpIConcReference->setDirectDependencies(Dependencies);
      Dependencies.clear();

      mpValueReference->addDirectDependency(this);

      Dependencies.insert(mpValueReference);
      if (pVolumeReference)
        Dependencies.insert(pVolumeReference);
      mpConcReference->setDirectDependencies(Dependencies);
      mpConcReference->setRefresh(this, &CMetab::refreshConcentration);

      success = mpExpression->compile(listOfContainer);

      Dependencies = mpExpression->getDirectDependencies();
      if (pVolumeReference)
        Dependencies.insert(pVolumeReference);
      mpRateReference->setDirectDependencies(Dependencies);
      mpRateReference->setRefresh(this, &CMetab::calculate);

      Dependencies.clear();
      Dependencies.insert(mpRateReference);
      Dependencies.insert(mpConcReference);
      if (pVolumeReference)
        Dependencies.insert(pVolumeReference);
      if (mpCompartment)
        Dependencies.insert(mpCompartment->getRateReference());

      mpConcRateReference->setDirectDependencies(Dependencies);
      mpConcRateReference->setRefresh(this, &CMetab::refreshConcentrationRate);

      Dependencies.clear();
      Dependencies.insert(mpValueReference);
      Dependencies.insert(mpRateReference);
      mpTTReference->setDirectDependencies(Dependencies);
      mpTTReference->setRefresh(this, &CMetab::refreshTransitionTime);
      break;

    case REACTIONS:
      if (mpCompartment)
        Dependencies.insert(mpCompartment->getInitialValueReference());
      mpIConcReference->setDirectDependencies(Dependencies);
      Dependencies.clear();

      Dependencies.insert(this);
      mpValueReference->setDirectDependencies(Dependencies);

      Dependencies.clear();
      mRateVector.clear();

      {
        CCopasiVectorN< CReaction >::const_iterator it = mpModel->getReactions().begin();
        CCopasiVectorN< CReaction >::const_iterator end = mpModel->getReactions().end();

        for (; it != end; ++it)
          {
            const CCopasiVector< CChemEqElement > &Balances =
              (*it)->getChemEq().getBalances();
            CCopasiVector< CChemEqElement >::const_iterator itChem = Balances.begin();
            CCopasiVector< CChemEqElement >::const_iterator endChem = Balances.end();

            for (; itChem != endChem; ++itChem)
              if ((*itChem)->getMetaboliteKey() == mKey)
                break;

            if (itChem != endChem)
              {
                Dependencies.insert((*it)->getObject(CCopasiObjectName("Reference=ParticleFlux")));

                std::pair< C_FLOAT64, const C_FLOAT64 * > Insert;
                Insert.first = (*itChem)->getMultiplicity();
                Insert.second = &(*it)->getParticleFlux();

                mRateVector.push_back(Insert);
              }
          }
      }

      mpRateReference->setRefresh(this, &CMetab::refreshRate);
      mpRateReference->setDirectDependencies(Dependencies);

      mpTTReference->setRefresh(this, &CMetab::refreshTransitionTime);
      mpTTReference->setDirectDependencies(Dependencies);

      Dependencies.clear();
      Dependencies.insert(mpRateReference);
      Dependencies.insert(mpConcReference);
      if (pVolumeReference)
        Dependencies.insert(pVolumeReference);
      if (mpCompartment)
        Dependencies.insert(mpCompartment->getRateReference());

      mpConcRateReference->setDirectDependencies(Dependencies);
      mpConcRateReference->setRefresh(this, &CMetab::refreshConcentrationRate);
      break;

    default:
      break;
    }

  return success;
}

void CMetab::calculate()
{
  switch (getStatus())
    {
    case FIXED:
      break;

    case ASSIGNMENT:
      mConc = mpExpression->calcValue();
      break;

    case ODE:
      mRate = mpCompartment->getValue() * mpExpression->calcValue() * mpModel->getQuantity2NumberFactor();
      break;

    case REACTIONS:
      if (isDependent())
        *mpValueData = mpMoiety->getDependentNumber();
      break;

    default:
      break;
    }
}

void CMetab::refreshRate()
{
  switch (getStatus())
    {
    case FIXED:
      break;

    case ASSIGNMENT:
      break;

    case ODE:
      break;

    case REACTIONS:
      {
        mRate = 0.0;

        std::vector< std::pair< C_FLOAT64, const C_FLOAT64 * > >::const_iterator it =
          mRateVector.begin();
        std::vector< std::pair< C_FLOAT64, const C_FLOAT64 * > >::const_iterator end =
          mRateVector.end();

        for (; it != end; ++it)
          mRate += it->first * *it->second;
      }
      break;

    default:
      break;
    }
}

void CMetab::refreshTransitionTime()
{
  switch (getStatus())
    {
    case FIXED:
      break;

    case ASSIGNMENT:
      break;

    case ODE:
      mTT = *mpValueData / fabs(mRate);
      break;

    case REACTIONS:
      {
        C_FLOAT64 PositiveFlux = 0;
        C_FLOAT64 NegativeFlux = 0;
        C_FLOAT64 Flux;

        std::vector< std::pair< C_FLOAT64, const C_FLOAT64 * > >::const_iterator it =
          mRateVector.begin();
        std::vector< std::pair< C_FLOAT64, const C_FLOAT64 * > >::const_iterator end =
          mRateVector.end();

        for (; it != end; ++it)
          {
            Flux = it->first * *it->second;

            if (Flux > 0.0)
              PositiveFlux += Flux;
            else
              NegativeFlux -= Flux;
          }

        Flux = std::min(PositiveFlux, NegativeFlux);

        if (Flux == 0.0)
          mTT = 2 * DBL_MAX;
        else
          mTT = *mpValueData / Flux;
      }
      break;

    default:
      break;
    }
}

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif

void CMetab::initObjects()
{
  mpIValueReference->setObjectName("InitialParticleNumber");
  mpIValueReference->setUpdateMethod(this, &CMetab::setInitialValue);

  mpValueReference->setObjectName("ParticleNumber");

  mpRateReference->setObjectName("ParticleNumberRate");

  mpIConcReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("InitialConcentration", mIConc, CCopasiObject::ValueDbl));
  mpIConcReference->setUpdateMethod(this, &CMetab::setInitialConcentration);
  mpIConcReference->setRefresh(this, &CMetab::refreshInitialConcentration);

  mpConcReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("Concentration", mConc, CCopasiObject::ValueDbl));

  mpConcRateReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("Rate", mConcRate, CCopasiObject::ValueDbl));

  mpTTReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("TransitionTime", mTT, CCopasiObject::ValueDbl));
}

std::set< const CCopasiObject * > CMetab::getDeletedObjects() const
  {
    std::set< const CCopasiObject * > Deleted = CModelEntity::getDeletedObjects();

    Deleted.insert(mpIConcReference);
    Deleted.insert(mpConcReference);
    Deleted.insert(mpConcRateReference);
    Deleted.insert(mpTTReference);

    return Deleted;
  }

CCopasiObject * CMetab::getInitialConcentrationReference() const
  {return mpIConcReference;}

CCopasiObject * CMetab::getConcentrationReference() const
  {return mpConcReference;}

C_FLOAT64 CMetab::getConcentrationRate() const
  {
    const_cast<CMetab *>(this)->refreshConcentrationRate();
    return mConcRate;
  }

void CMetab::refreshConcentrationRate()
{
  // d(Particle Number*conversion/Volume)/dt
  // = (Rate / Volume - Particle Number / Volume^2 * Volume Rate) * conversion
  // = (Rate - Particle Number / Volume * Volume Rate) / Volume * conversion
  // = (Rate  * conversion - Concentration * Volume Rate) / Volume

  mConcRate =
    (mRate * mpModel->getNumber2QuantityFactor() - mConc * mpCompartment->getRate())
    / mpCompartment->getValue();
}

void * CMetab::getValuePointer() const
  {
    //std::cout << "CMetab::getValuePointer();" << std::endl;
    return const_cast<C_FLOAT64 *>(&mConc);
  }

std::ostream & operator<<(std::ostream &os, const CMetab & d)
{
  os << "    ++++CMetab: " << d.getObjectName() << std::endl;
  os << "        mConc " << d.mConc << " mIConc " << d.mIConc << std::endl;
  os << "        mValue (particle number) " << *d.mpValueAccess << " mIValue " << *d.mpIValue << std::endl;
  os << "        mRate " << d.mRate << " mTT " << d.mTT << " mStatus " << d.getStatus() << std::endl;

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
  if ((GepasiStatus < 0) || (GepasiStatus > 7))
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     "The file specifies a non-existing type "
                     "for '%s'.\nReset to internal metabolite.",
                     getObjectName().c_str());
      setStatus(REACTIONS);
    }

  // sanity check
  if ((GepasiStatus != METAB_MOIETY) && (mIConc < 0.0))
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     "The file specifies a negative concentration "
                     "for '%s'.\nReset to default.",
                     getObjectName().c_str());
      mIConc = 1.0;
    }

  return Fail;
}

std::string CMetab::getObjectDisplayName(bool regular, bool richtext) const
  {
    CModel* tmp = dynamic_cast<CModel*>(this->getObjectAncestor("Model"));
    if (tmp)
      {
        return CMetabNameInterface::getDisplayName(tmp, *this);
      }

    return CCopasiObject::getObjectDisplayName(regular, richtext);
  }

void CMetab::setDependentOn(const CMoiety * pMoiety)
{mpMoiety = pMoiety;}

bool CMetab::isDependent() const
  {return mpMoiety != NULL;}

void CMetab::addMoiety(CMoiety * pMoiety)
{mMoieties.insert(pMoiety);}

void CMetab::clearMoieties()
{
  mpMoiety = NULL;
  mMoieties.clear();
}

//******************* CMetabOld ***************************************************

CMetabOld::CMetabOld(const std::string & name,
                     const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Old Metabolite"),
    mIConc(1.0),
    mStatus(CModelEntity::REACTIONS),
    mCompartment()
{CONSTRUCTOR_TRACE;}

CMetabOld::CMetabOld(const CMetabOld & src,
                     const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mIConc(src.mIConc),
    mStatus(src.mStatus),
    mCompartment(src.mCompartment)
{CONSTRUCTOR_TRACE;}

CMetabOld::~CMetabOld() {DESTRUCTOR_TRACE;}

void CMetabOld::cleanup(){}

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
    mStatus = CModelEntity::FIXED;
  else
    mStatus = CModelEntity::REACTIONS;

  // sanity check
  if ((mStatus < 0) || (mStatus > 7))
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     "The file specifies a non-existing type "
                     "for '%s'.\nReset to internal metabolite.",
                     getObjectName().c_str());
      mStatus = CModelEntity::REACTIONS;
    }

  // sanity check
  if ((mStatus != METAB_MOIETY) && (mIConc < 0.0))
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
