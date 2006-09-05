/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMetab.cpp,v $
   $Revision: 1.107 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/05 13:04:51 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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
      initModel();
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

  initModel();
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

void CMetab::initModel()
{
  //  mpModel = dynamic_cast< CModel * >(getObjectAncestor("Model"));
  //  if (!mpModel && CCopasiDataModel::Global) mpModel = CCopasiDataModel::Global->getModel();
}

void CMetab::initCompartment(const CCompartment * pCompartment)
{
  mpCompartment = (const CCompartment *) getObjectAncestor("Compartment");
  if (!mpCompartment) mpCompartment = pCompartment;
  //  if (!mpCompartment) mpCompartment = mpParentCompartment;
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

  CCopasiObject * pObject =
    const_cast< CCopasiObject * >(getObject(CCopasiObjectName("Reference=Concentration")));

  pObject->setRefresh(this, &CMetab::refreshConcentration);

  pObject =
    const_cast< CCopasiObject * >(getObject(CCopasiObjectName("Reference=TransitionTime")));

  if (mpModel)
    pObject->setRefresh(mpModel, &CModel::setTransitionTimes);
  else
    pObject->clearRefresh();

  initCompartment(NULL);
  initModel();

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
  if (!isnan(initialConcentration) &&
      !isnan(mpCompartment->getInitialValue()))
    *mpIValue =
      initialConcentration * mpCompartment->getInitialValue() * mpModel->getQuantity2NumberFactor();

  std::set< CMoiety * >::iterator it = mMoieties.begin();
  std::set< CMoiety * >::iterator end = mMoieties.end();

  for (; it != end; ++it)
    (*it)->setInitialValue();

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

  if (initialValue != 0 &&
      !isnan(initialValue) &&
      !isnan(mpCompartment->getInitialValue()))
    mIConc =
      initialValue / mpCompartment->getInitialValue() * mpModel->getNumber2QuantityFactor();

  *mpIValue = initialValue;

  // This is obsolete.
  // if (isFixed())
  //   setNumber(initialValue);

  std::set< CMoiety * >::iterator it = mMoieties.begin();
  std::set< CMoiety * >::iterator end = mMoieties.end();

  for (; it != end; ++it)
    (*it)->setInitialValue();

  return;
}

void CMetab::refreshInitialConcentration()
{
  if (!isnan(mpCompartment->getInitialValue()) &&
      !isnan(*mpIValue))
    mIConc =
      *mpIValue / mpCompartment->getInitialValue() * mpModel->getNumber2QuantityFactor();

  if (isFixed()) mConc = mIConc;
}

void CMetab::refreshConcentration()
{
  mConc = *mpValueAccess / mpCompartment->getValue() * mpModel->getNumber2QuantityFactor();
}

void CMetab::setStatus(const CModelEntity::Status & status)
{
  CModelEntity::setStatus(status);

  std::set< const CCopasiObject * > Dependencies;

  const CCopasiObject * pVolumeReference = NULL;
  if (mpCompartment)
    pVolumeReference = mpCompartment->getObject(CCopasiObjectName("Reference=Volume"));

  switch (getStatus())
    {
    case FIXED:
      break;

    case ASSIGNMENT:
      // :TODO: This needs to be implemented when this status becomes available
      break;

    case ODE:
      // :TODO: This needs to be implemented when this status becomes available
      break;

    case REACTIONS:
      Dependencies.insert(this);

      mpValueReference->setDirectDependencies(Dependencies);
      mpValueReference->clearRefresh();

      if (pVolumeReference)
        Dependencies.insert(pVolumeReference);
      mpConcReference->setDirectDependencies(Dependencies);
      mpConcReference->setRefresh(this, &CMetab::refreshConcentration);

      if (mpModel)
        mpRateReference->setRefresh(mpModel, &CModel::refreshRates);
      else
        mpRateReference->clearRefresh();

      Dependencies.clear();
      Dependencies.insert(mpRateReference);
      if (pVolumeReference)
        Dependencies.insert(pVolumeReference);

      mpConcRateReference->setDirectDependencies(Dependencies);
      mpConcRateReference->setRefresh(this, &CMetab::refreshConcentrationRate);
      break;
    }

  if (mpModel && mpCompartment) refreshConcentration();
}

bool CMetab::compile()
{
  switch (getStatus())
    {
    case FIXED:
      break;

    case ASSIGNMENT:
      // :TODO: This needs to be implemented when this status becomes available
      break;

    case ODE:
      // :TODO: This needs to be implemented when this status becomes available
      break;

    case REACTIONS:
      mDependencies.clear();
      mRateVector.clear();

      std::set< const CCopasiObject * > Dependencies;

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

      mpRateReference->setRefresh(this, &CMetab::refreshRate);
      mpRateReference->setDirectDependencies(Dependencies);
    }

  return true;
}

void CMetab::calculate()
{
  switch (getStatus())
    {
    case FIXED:
      break;

    case ASSIGNMENT:
      // :TODO: This needs to be implemented when this status becomes available
      break;

    case ODE:
      // :TODO: This needs to be implemented when this status becomes available
      break;

    case REACTIONS:
      if (isDependent())
        *mpValueData = mpMoiety->getDependentNumber();
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
      // :TODO: This needs to be implemented when this status becomes available
      break;

    case ODE:
      // :TODO: This needs to be implemented when this status becomes available
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
    }
}

void CMetab::initObjects()
{
  // pObject->setRefresh(this, &CMetab::refreshInitialConcentration);

  mpValueReference->setObjectName("ParticleNumber");
  mpIValueReference->setObjectName("InitialParticleNumber");
  mpIValueReference->setUpdateMethod(this, &CMetab::setInitialValue);
  mpRateReference->setObjectName("ParticleNumberRate");

  mpConcReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("Concentration", mConc, CCopasiObject::ValueDbl));
  mpIConcReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("InitialConcentration", mIConc, CCopasiObject::ValueDbl));
  mpIConcReference->setUpdateMethod(this, &CMetab::setInitialConcentration);

  mpConcRateReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("Rate", mConcRate, CCopasiObject::ValueDbl));

  // :TODO: This will have to be replaced when ASSIGNMENTS and ODE are implemented
  CCopasiObject * pObject;
  std::set<const CCopasiObject *> NoDependencies;

  pObject = addObjectReference("TransitionTime", mTT, CCopasiObject::ValueDbl);
  pObject->setDirectDependencies(NoDependencies);
  if (mpModel)
    pObject->setRefresh(mpModel, &CModel::setTransitionTimes);
}

std::set< const CCopasiObject * > CMetab::getDeletedObjects() const
  {
    std::set< const CCopasiObject * > Deleted = CModelEntity::getDeletedObjects();

    Deleted.insert(mpIConcReference);
    Deleted.insert(mpConcReference);
    Deleted.insert(mpConcRateReference);
    Deleted.insert(getObject(CCopasiObjectName("Reference=TransitionTime")));

    return Deleted;
  }

C_FLOAT64 CMetab::getConcentrationRate() const
  {
    const_cast<CMetab *>(this)->refreshConcentrationRate();
    return mConcRate;
  }

void CMetab::refreshConcentrationRate()
{
  mConcRate = mRate / getCompartment()->getValue() * mpModel->getNumber2QuantityFactor();
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
  std::set< CMoiety * >::iterator it = mMoieties.begin();
  std::set< CMoiety * >::iterator end = mMoieties.end();

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

  mStatus = (CMetab::Status) Status;

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
