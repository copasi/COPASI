/**
 *  CMathConstant class.
 *  The class CMathConstant associates a symbol with a CCopasiObject with
 *  that represents a fixed metabolite.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"
#include "CMathConstant.h"
#include "CMathVariable.h"

#include "model/CMetab.h"
#include "model/CReaction.h"
#include "model/CCompartment.h"

CMathConstant::CMathConstant(const CMathConstant & src):
    CMathSymbol(src)
{}

CMathConstant::CMathConstant(const CCopasiObject * pObject):
    CMathSymbol(pObject)
{}

CMathConstant::~CMathConstant() {}

/* Metabolites */
CMathConstantMetab::CMathConstantMetab(const CMathConstantMetab & src):
    CMathConstant(src)
{}

CMathConstantMetab::CMathConstantMetab(const CMetab & metabolite):
    CMathConstant(& metabolite)
{}

CMathConstantMetab::~CMathConstantMetab() {}

bool CMathConstantMetab::setValue(const C_FLOAT64 & value)
{return setConcentration(value);}

const C_FLOAT64 & CMathConstantMetab::getValue() const
  {return getConcentration();}

bool CMathConstantMetab::setConcentration(const C_FLOAT64 & concentration)
{
  ((CMetab *) mpObject)->setInitialConcentration(concentration);
  return true;
}

const C_FLOAT64 & CMathConstantMetab::getConcentration() const
  {return ((CMetab *) mpObject)->getInitialConcentration();}

bool CMathConstantMetab::setParticleNumber(const C_FLOAT64 & particleNumber)
{
  ((CMetab *) mpObject)->setInitialNumberDbl(particleNumber);
  return true;
}

C_FLOAT64 CMathConstantMetab::getParticleNumber() const
  {return ((CMetab *) mpObject)->getInitialNumberDbl();}

bool CMathConstantMetab::compile()
{
  mpCompartment = (CMathConstantCompartment *)
                  CMathSymbol::find(((CMetab *) mpObject)->getCompartment());

  if (mpCompartment) return true;
  else return false;
}

CMathConstantCompartment & CMathConstantMetab::getCompartment() const
{return *mpCompartment;}

/* Parameter */
CMathConstantParameter::CMathConstantParameter(const CMathConstantParameter & src):
    CMathConstant(src)
{}

CMathConstantParameter::CMathConstantParameter(const CReaction::CId2Param & parameter):
    CMathConstant(& parameter)
{}

CMathConstantParameter::~CMathConstantParameter() {}

bool CMathConstantParameter::setValue(const C_FLOAT64 & value)
{
  ((CReaction::CId2Param *) mpObject)->setValue(value);
  return true;
}

const C_FLOAT64 & CMathConstantParameter::getValue() const
  {return ((CReaction::CId2Param *) mpObject)->getValue();}

/* Compartment */
CMathConstantCompartment::CMathConstantCompartment(const CMathConstantCompartment & src):
    CMathConstant(src),
    mMetaboliteList(src.mMetaboliteList)
{}

CMathConstantCompartment::CMathConstantCompartment(const CCompartment & compartment):
    CMathConstant(& compartment)
{compile();}

CMathConstantCompartment::~CMathConstantCompartment() {}

bool CMathConstantCompartment::setValue(const C_FLOAT64 & value)
{
  ((CCompartment *) mpObject)->setInitialVolume(value);
  return true;
}

const C_FLOAT64 & CMathConstantCompartment::getValue() const
  {return ((CCompartment *) mpObject)->getInitialVolume();}

const C_FLOAT64 & CMathConstantCompartment::getTransientValue() const
  {return ((CCompartment *) mpObject)->getVolume();}

const std::vector< CMathSymbol * > &
CMathConstantCompartment::getMetaboliteList() const
  {return mMetaboliteList;}

bool CMathConstantCompartment::compile()
{
  CCopasiVectorN< CMetab > & mList =
    ((CCompartment *) mpObject)->getMetabolites();
  unsigned C_INT32 i, imax = mList.size();
  CMathSymbol * m;
  mMetaboliteList.clear();
  bool Success = true;

  for (i = 0; i < imax; i++)
    {
      m = CMathSymbol::find(mList[i]);

      if (m) mMetaboliteList.push_back(m);
      else Success = false;
    }

  return Success;
}
