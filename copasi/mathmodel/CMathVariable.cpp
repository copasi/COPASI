/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/mathmodel/Attic/CMathVariable.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:57 $
   End CVS Header */

/**
 *  CMathVariable class.
 *  The class CMathVariable associates a symbol with a CCopasiObject which
 *  functions as a variable in the system of ODEs.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"
#include "CMathVariable.h"
#include "CMathConstant.h"
#include "CMathEq.h"
#include "model/CMetab.h"
#include "model/CCompartment.h"
#include "model/CModel.h"

CMathVariable::CMathVariable(const CMathVariable & src):
    CMathSymbol(src),
    mType(src.mType),
    mpEq(src.mpEq)
{}

CMathVariable::CMathVariable(const CCopasiObject * pObject):
    CMathSymbol(pObject),
    mType(CMathVariable::Eq),
    mpEq(NULL)
{}

CMathVariable::~CMathVariable() {}

bool CMathVariable::setEq(CMathEq * eq, const CMathVariable::Type & type)
{
  mType = type;
  mpEq = eq;

  return true;
}

CMathEq * CMathVariable::getEq() {return mpEq;}

CMathVariable::Type CMathVariable::getType() const {return mType;}

/* Metabolites */
CMathVariableMetab::CMathVariableMetab(const CMathVariableMetab & src):
    CMathVariable(src),
    mpCompartment(src.mpCompartment)
{}

CMathVariableMetab::CMathVariableMetab(const CMetab & metabolite):
    CMathVariable(& metabolite)
{compile();}

CMathVariableMetab:: ~CMathVariableMetab() {}

bool CMathVariableMetab::setInitialValue(const C_FLOAT64 & value)
{return setInitialConcentration(value);}

const C_FLOAT64 & CMathVariableMetab::getInitialValue() const
  {return getInitialConcentration();}

const C_FLOAT64 & CMathVariableMetab::getValue() const
  {return getConcentration();}

bool CMathVariableMetab::setInitialConcentration(const C_FLOAT64 & concentration)
{
  ((CMetab *) mpObject)->setInitialConcentration(concentration);
  return true;
}

const C_FLOAT64 & CMathVariableMetab::getInitialConcentration() const
  {return ((CMetab *) mpObject)->getInitialConcentration();}

const C_FLOAT64 & CMathVariableMetab::getConcentration() const
  {return ((CMetab *) mpObject)->getConcentration();}

bool CMathVariableMetab::setInitialParticleNumber(const C_FLOAT64 & particleNumber)
{
  ((CMetab *) mpObject)->setInitialNumber(particleNumber);
  return true;
}

C_FLOAT64 CMathVariableMetab::getInitialParticleNumber() const
  {return ((CMetab *) mpObject)->getInitialNumber();}

C_FLOAT64 CMathVariableMetab::getParticleNumber() const
  {return ((CMetab *) mpObject)->getNumber();}

bool CMathVariableMetab::compile()
{
  mpCompartment = (CMathConstantCompartment *)(CMathConstant *)
                  CMathSymbol::find(((CMetab *) mpObject)->getCompartment());

  if (mpCompartment) return true;
  else return false;
}

CMathConstantCompartment & CMathVariableMetab::getCompartment() const
{return *mpCompartment;}

/* Compartment Volumes */
CMathVariableVolume::CMathVariableVolume(const CMathVariableVolume & src):
    CMathVariable(src)
{}

CMathVariableVolume::CMathVariableVolume(const CCompartment & compartment):
    CMathVariable(& compartment)
{}

CMathVariableVolume::~CMathVariableVolume() {}

bool CMathVariableVolume::setInitialValue(const C_FLOAT64 & value)
{
  ((CCompartment *) mpObject)->setInitialVolume(value);
  return true;
}

const C_FLOAT64 & CMathVariableVolume::getInitialValue() const
  {return ((CCompartment *) mpObject)->getInitialVolume();}

const C_FLOAT64 & CMathVariableVolume::getValue() const
  {return ((CCompartment *) mpObject)->getVolume();}

/* Time */
CMathVariableTime::CMathVariableTime(const CMathVariableTime & src):
    CMathVariable(src)
{}

CMathVariableTime::CMathVariableTime(const CModel & model):
    CMathVariable(& model)
{
  std::string Name("Time");
  setName(Name);
}

CMathVariableTime::~CMathVariableTime() {}

bool CMathVariableTime::setInitialValue(const C_FLOAT64 & value)
{
  ((CModel *) mpObject)->setInitialTime(value);
  return true;
}

const C_FLOAT64 & CMathVariableTime::getInitialValue() const
  {return ((CModel *) mpObject)->getInitialTime();}

const C_FLOAT64 & CMathVariableTime::getValue() const
  {return ((CModel *) mpObject)->getTime();}
