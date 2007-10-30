// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CEvent.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/10/30 14:40:23 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include <stdio.h>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "CModel.h"
#include "CEvent.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiException.h"
#include "utilities/utility.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"

CEvent::CEvent(const std::string & name,
               const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Event"),
    mKey(GlobalKeys.add("Event", this))
{
  CONSTRUCTOR_TRACE;
  initObjects();
}

CEvent::CEvent(const CEvent & src,
               const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Event", this))
{
  CONSTRUCTOR_TRACE;
  initObjects();
}

CEvent::~CEvent()
{
  GlobalKeys.remove(mKey);
  cleanup();
  DESTRUCTOR_TRACE;
}

void CEvent::cleanup()
{}

const std::string & CEvent::getKey() const {return mKey;}

void CEvent::compile()
{
  mDependencies.clear();
  std::set< const CCopasiObject * > Dependencies;

  //  mpFluxReference->setDirectDependencies(Dependencies);
}

void CEvent::initObjects()
{
  /*  mpFluxReference =
      static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("Flux", mFlux, CCopasiObject::ValueDbl));
    mpFluxReference->setRefresh(this, &CEvent::calculate);*/
}

std::set< const CCopasiObject * > CEvent::getDeletedObjects() const
  {
    std::set< const CCopasiObject * > Deleted;

    Deleted.insert(this);
    //    Deleted.insert(mpFluxReference);

    return Deleted;
  }

std::ostream & operator<<(std::ostream &os, const CEvent & d)
{
  os << "CEvent:  " << d.getObjectName() << std::endl;
  os << "   sbml id:  " << d.mSBMLId << std::endl;

  os << "----CEvent" << std::endl;

  return os;
}

void CEvent::setSBMLId(const std::string& id)
{
  this->mSBMLId = id;
}

const std::string& CEvent::getSBMLId() const
  {
    return this->mSBMLId;
  }

std::string CEvent::getObjectDisplayName(bool regular, bool richtext) const
  {
    CModel* tmp = dynamic_cast<CModel*>(this->getObjectAncestor("Model"));
    if (tmp)
      {
        return "((" + getObjectName() + "))";
      }

    return CCopasiObject::getObjectDisplayName(regular, richtext);
    //TODO
  }
