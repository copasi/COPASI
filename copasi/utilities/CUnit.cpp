// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include <math.h>

#include "copasi/utilities/CUnit.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/model/CModel.h"

#include <algorithm>

// static
C_FLOAT64 CUnit::Avogadro(6.02214129e23); // http://physics.nist.gov/cgi-bin/cuu/Value?na (Wed Jan 29 18:33:36 EST 2014)

const char * CUnit::VolumeUnitNames[] =
{"dimensionless", "m\xc2\xb3", "l", "ml", "\xc2\xb5l", "nl", "pl", "fl", NULL};

const char * CUnit::AreaUnitNames[] =
{"dimensionless", "m\xc2\xb2", "dm\xc2\xb2", "cm\xc2\xb2", "mm\xc2\xb2", "\xc2\xb5m\xc2\xb2", "nm\xc2\xb2", "pm\xc2\xb2", "fm\xc2\xb2", NULL};

const char * CUnit::LengthUnitNames[] =
{"dimensionless", "m", "dm", "cm", "mm", "\xc2\xb5m", "nm", "pm", "fm", NULL};

const char * CUnit::TimeUnitNames[] =
{"dimensionless", "d", "h", "min", "s", "ms", "\xc2\xb5s", "ns", "ps", "fs", NULL};

// "mol" is the correct name, however in the COPASI XML files "Mol" is used
// up to build 18

const char * CUnit::QuantityUnitOldXMLNames[] =
{"dimensionless", "Mol", "mMol", "\xc2\xb5Mol", "nMol", "pMol", "fMol", "#", NULL};

const char * CUnit::QuantityUnitNames[] =
{"dimensionless", "mol", "mmol", "\xc2\xb5mol", "nmol", "pmol", "fmol", "#", NULL};

// constructors
CUnit::CUnit(const std::string & name,
             const CCopasiContainer * pParent):
  CCopasiContainer(name, pParent, "Unit"),
  mSymbol("none"),
  mKey(),
  mComponents()
{
  setup();
}

// copy constructor
CUnit::CUnit(const CUnit & src,
             const CCopasiContainer * pParent):
  CCopasiContainer(src, pParent),
  mSymbol(src.mSymbol),
  mKey(),
  mComponents(src.mComponents)
{
  setup();
}

CUnit::~CUnit()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
}

void CUnit::setup()
{
  mKey = CCopasiRootContainer::getKeyFactory()->add("Unit", this);
}

void CUnit::fromEnum(VolumeUnit volEnum)
{
  mComponents.clear();

  mSymbol = VolumeUnitNames[volEnum];

  if( volEnum == CUnit::dimensionlessVolume )
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::meter);
  tmpComponent.setExponent(3);

  switch (volEnum)
  {
    case CUnit::m3:  //default scale = 0
      break;

    case CUnit::l:
      tmpComponent.setScale(-3);
      break;

    case CUnit::ml:
      tmpComponent.setScale(-6);
      break;

    case CUnit::microl:
      tmpComponent.setScale(-9);
      break;

    case CUnit::nl:
      tmpComponent.setScale(-12);
      break;

    case CUnit::pl:
      tmpComponent.setScale(-15);
      break;

    case CUnit::fl:
      tmpComponent.setScale(-18);
      break;
  }

  addComponent(tmpComponent);

}

void CUnit::fromEnum(AreaUnit areaEnum)
{
  mComponents.clear();

  mSymbol = AreaUnitNames[areaEnum];

  if( areaEnum == CUnit::dimensionlessArea )
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::meter);
  tmpComponent.setExponent(2);

  switch (areaEnum)
  {
    case CUnit::m2:  //default scale = 0
      break;

    case CUnit::dm2:
      tmpComponent.setScale(-2);
      break;

    case CUnit::cm2:
      tmpComponent.setScale(-4);
      break;

    case CUnit::mm2:
      tmpComponent.setScale(-6);
      break;

    case CUnit::microm2:
      tmpComponent.setScale(-12);
      break;

    case CUnit::nm2:
      tmpComponent.setScale(-18);
      break;

    case CUnit::pm2:
      tmpComponent.setScale(-24);
      break;

    case CUnit::fm2:
      tmpComponent.setScale(-30);
      break;
  }

  addComponent(tmpComponent);

}

void CUnit::fromEnum(LengthUnit lengthEnum)
{
  mComponents.clear();

  mSymbol = LengthUnitNames[lengthEnum];

  if( lengthEnum == CUnit::dimensionlessLength )
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::meter);

  switch (lengthEnum)
  {
    case CUnit::m:  //default scale = 0
      break;

    case CUnit::dm:
      tmpComponent.setScale(-1);
      break;

    case CUnit::cm:
      tmpComponent.setScale(-2);
      break;

    case CUnit::mm:
      tmpComponent.setScale(-3);
      break;

    case CUnit::microm:
      tmpComponent.setScale(-6);
      break;

    case CUnit::nm:
      tmpComponent.setScale(-9);
      break;

    case CUnit::pm:
      tmpComponent.setScale(-12);
      break;

    case CUnit::fm:
      tmpComponent.setScale(-15);
      break;
  }

  addComponent(tmpComponent);

}

void CUnit::fromEnum(TimeUnit timeEnum)
{
  mComponents.clear();

  mSymbol = TimeUnitNames[timeEnum];

  if( timeEnum == CUnit::dimensionlessTime )
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::second);

  switch (timeEnum)
  {
    case CUnit::d:
      tmpComponent.setMultiplier(60*60*24);
      break;

    case CUnit::h:
      tmpComponent.setMultiplier(60*60);
      break;

    case CUnit::min:
    case CUnit::OldMinute:
      tmpComponent.setMultiplier(60);
      break;

    case CUnit::s:  // defaults are appropriate
      break;

    case CUnit::micros:
      tmpComponent.setScale(-6);
      break;

    case CUnit::ns:
      tmpComponent.setScale(-9);
      break;

    case CUnit::ps:
      tmpComponent.setScale(-12);
      break;

    case CUnit::fs:
      tmpComponent.setScale(-15);
      break;
  }

  addComponent(tmpComponent);
}

void CUnit::fromEnum(QuantityUnit quantityEnum)
{
  mComponents.clear();

  mSymbol = QuantityUnitNames[quantityEnum];

  if( quantityEnum == CUnit::dimensionlessQuantity )
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::item);

  const CModel * pModel = dynamic_cast<const CModel *>(getObjectAncestor("Model"));

  C_FLOAT64 usedAvogadro;

  if(pModel != NULL)
    usedAvogadro = pModel->getAvogadro();
  else
    usedAvogadro = Avogadro;

  tmpComponent.setMultiplier(usedAvogadro);

  //   enum QuantityUnit {dimensionlessQuantity = 0, Mol, mMol, microMol, nMol, pMol, fMol, number, OldXML};

  switch (quantityEnum)
  {
    case CUnit::Mol:
      break;

    case CUnit::mMol:
      tmpComponent.setScale(-3);
      break;

    case CUnit::microMol:
      tmpComponent.setScale(-6);
      break;

    case CUnit::nMol:
      tmpComponent.setScale(-9);
      break;

    case CUnit::pMol:
      tmpComponent.setScale(-12);
      break;

    case CUnit::fMol:
      tmpComponent.setScale(-15);
      break;

    case CUnit::number:
    case CUnit::OldXML:
      tmpComponent.setMultiplier(1);
      break;
  }

  addComponent(tmpComponent);
}

void CUnit::setSymbol(std::string symbol)
{
  mSymbol = symbol;
}

std::string CUnit::getSymbol() const
{
  return mSymbol;
}

// See if the component units cancel (divide to 1).
// The CUnitComponent::Kind enumerator uses only prime numbers.
// Multiplying all the components should give 1, if numerators and
// denominators have the same combination of units.
bool CUnit::isDimensionless() const
{
  // If the symbol string has been set to other than "dimensionless",
  // assume it has dimension, regardless of the components
  if(mSymbol != "dimensionless" || mSymbol != "")
    return false;

  std::vector< CUnitComponent >::const_iterator it = mComponents.begin();

  double reduction = 1;

  for (; it != mComponents.end(); it++)
    {
      reduction *= pow((double)(*it).getKind(), (*it).getExponent());
    }

  // If the vector is empy, it will loop 0 times, and the reduction
  // will remain ==1 (i.e. dimensionless if no components)
  return reduction == 1;
}

void CUnit::addComponent(const CUnitComponent & component)
{
  mComponents.push_back(component);
}

bool CUnit::simplifyComponents()
{
  if (mComponents.size() < 2)
    return false;

  std::vector< CUnitComponent > replacementVector;
  std::vector< CUnitComponent >::const_iterator it = mComponents.begin();
  CUnitComponent tempComponent;
  bool didSimplify = false;

  std::sort(mComponents.begin(), mComponents.end()); // make same Kinds adjacent

  for (; it != mComponents.end(); it++)
  {
    tempComponent = (*it);

    while (it != mComponents.end() && tempComponent.getKind() == (*(it + 1)).getKind())
    {
      tempComponent.setExponent((tempComponent.getExponent()) + (*(it + 1)).getExponent());
      tempComponent.setScale(tempComponent.getScale() + (*(it + 1)).getScale());
      tempComponent.setMultiplier(tempComponent.getMultiplier() * (*(it + 1)).getMultiplier());
      didSimplify = true;
      it++;
    }

      replacementVector.push_back(tempComponent);
  }

  if (didSimplify)
  {
    mComponents = replacementVector;
  }

  return didSimplify;
}

std::string CUnit::prefixFromScale(int scale)
{
  switch (scale)
  {
    case 3:
      return "k";  // kilo

    case 2:
      return "h";  // hecto

    case 1:
      return "da"; // deca

    case -1:
      return "d";  // deci

    case -2:
      return "c";  // centi

    case -3:
      return "m";  // milli

    case -6:
      return "\xc2\xb5";  // micro

    case -9:
      return "n";  // nano

    case -12:
      return "p";  // pico

    case -15:
      return "f";  // femto

    default:
      return "";  // anything else, including scale = 0
  }
}

