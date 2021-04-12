// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// CCompartment
//
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for COPASI by Pedro Mendes

#include <iostream>
#include <cmath>

#include "copasi/copasi.h"
#include "copasi/utilities/CReadConfig.h"
#include "copasi/core/CDataVector.h"
#include "copasi/utilities/utility.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/report/CKeyFactory.h"
#include "CCompartment.h"
#include "CModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/undo/CUndoData.h"

// static
CCompartment * CCompartment::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CCompartment(data.getProperty(CData::OBJECT_NAME).toString(),
                          NO_PARENT);
}

// virtual
CData CCompartment::toData() const
{
  CData Data = CModelEntity::toData();

  CData InitialValueData;
  InitialValueData.addProperty(CData::VALUE, mIValue);
  InitialValueData.addProperty(CData::FRAMEWORK, CCore::FrameworkNames[CCore::Framework::ParticleNumbers]);
  Data.addProperty(CData::INITIAL_VALUE, InitialValueData);

  Data.addProperty(CData::SPATIAL_DIMENSION, mDimensionality);

  return Data;
}

// virtual
bool CCompartment::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CModelEntity::applyData(data, changes);

  if (data.isSetProperty(CData::INITIAL_VALUE))
    {
      const CData & Data = data.getProperty(CData::INITIAL_VALUE).toData();
      mIValue = Data.getProperty(CData::VALUE).toDouble();
      mpModel->updateInitialValues(CCore::FrameworkNames.toEnum(Data.getProperty(CData::FRAMEWORK).toString(), CCore::Framework::ParticleNumbers));
      changes.add({CUndoData::Type::CHANGE, "State", mpModel->getCN(), mpModel->getCN()});
    }

  if (data.isSetProperty(CData::SPATIAL_DIMENSION))
    {
      success &= setDimensionality(data.getProperty(CData::SPATIAL_DIMENSION).toUint());
    }

  return success;
}

// virtual
void CCompartment::createUndoData(CUndoData & undoData,
                                  const CUndoData::Type & type,
                                  const CData & oldData,
                                  const CCore::Framework & framework) const
{
  CModelEntity::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  CData OldInitialValueData;
  OldInitialValueData.addProperty(CData::VALUE, oldData.getProperty(CData::INITIAL_VALUE).toData().getProperty(CData::VALUE));
  OldInitialValueData.addProperty(CData::FRAMEWORK, CCore::FrameworkNames[framework]);
  CData NewInitialValueData;
  NewInitialValueData.addProperty(CData::VALUE, mIValue);
  NewInitialValueData.addProperty(CData::FRAMEWORK, CCore::FrameworkNames[framework]);

  undoData.addProperty(CData::INITIAL_VALUE, OldInitialValueData, NewInitialValueData);
  undoData.addProperty(CData::SPATIAL_DIMENSION, oldData.getProperty(CData::SPATIAL_DIMENSION), mDimensionality);

  return;
}

CCompartment::CCompartment(const std::string & name,
                           const CDataContainer * pParent):
  CModelEntity(name, pParent, "Compartment"),
  mMetabolites("Metabolites", this),
  mDimensionality(3)
{
  initObjects();

  //mKey = CRootContainer::getKeyFactory()->add("Compartment", this);

  setStatus(Status::FIXED);

  mIValue = 1.0;

  CONSTRUCTOR_TRACE;
}

CCompartment::CCompartment(const CCompartment & src,
                           const CDataContainer * pParent):
  CModelEntity(src, pParent),
  mMetabolites(src.mMetabolites, this),
  mDimensionality(src.mDimensionality)
{
  //mKey = CRootContainer::getKeyFactory()->add("Compartment", this);
  CONSTRUCTOR_TRACE;
  initObjects();
}

CCompartment::~CCompartment()
{
  CRootContainer::getKeyFactory()->remove(mKey);
  DESTRUCTOR_TRACE;
}

// virtual
const std::string CCompartment::getUnits() const
{
  if (mpModel != NULL)
    {
      switch (mDimensionality)
        {
          case 0:
            return "1";
            break;

          case 1:
            return mpModel->getLengthUnit();
            break;

          case 2:
            return mpModel->getAreaUnit();
            break;

          case 3:
            return mpModel->getVolumeUnit();
            break;
        }
    }

  return "?";
}

void CCompartment::cleanup() {mMetabolites.cleanup();}

C_INT32 CCompartment::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;
  std::string tmp;

  if ((Fail = configbuffer.getVariable("Compartment", "string",
                                       (void *) & tmp,
                                       CReadConfig::SEARCH)))
    return Fail;

  setObjectName(tmp);

  C_FLOAT64 tmpdbl;

  if ((Fail = configbuffer.getVariable("Volume", "C_FLOAT64",
                                       (void *) & tmpdbl)))
    return Fail;

  setInitialValue(tmpdbl);

  return Fail;
}

CDataVectorNS < CMetab > & CCompartment::getMetabolites()
{return mMetabolites;}

const CDataVectorNS < CMetab > & CCompartment::getMetabolites() const
{return mMetabolites;}

bool CCompartment::addMetabolite(CMetab * pMetabolite)
{
  if (!pMetabolite) return false;

  std::string oldCN = pMetabolite->getCN();

  bool success = mMetabolites.add(pMetabolite, true);

  //if a metabolite is added to a compartment successfully the CN of
  //the metabolite is changed. This needs to be handled similarly to a
  //rename.
  if (success && getObjectParent())
    {
      std::string newCN = pMetabolite->getCN();
      CRegisteredCommonName::handle(oldCN, newCN);
    }

  return success;
}

bool CCompartment::setDimensionality(unsigned C_INT32 dim)
{
  if (dim > 3)
    return false;

  mDimensionality = dim;
  return true;
}

unsigned C_INT32 CCompartment::getDimensionality() const
{
  return mDimensionality;
}

void CCompartment::initObjects()
{
  mpIValueReference->setObjectName("InitialVolume");
  mpValueReference->setObjectName("Volume");
}

std::ostream & operator<<(std::ostream &os, const CCompartment & d)
{
  os << "++++CCompartment: " << d.getObjectName() << " mValue " << d.mValue;
  os << "    CCompartment.mMetabolites " << std::endl << d.mMetabolites;
  os << "----CCompartment " << std::endl;

  return os;
}
