// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CCreator.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/25 20:37:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "report/CKeyFactory.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"

#include "CCreator.h"

CCreator::CCreator(const std::string & objectName, const CCopasiContainer * pParent,
                   CRDFObject * pRDFObj) :
    CCopasiContainer(objectName, pParent, "Creator"),
    mKey(GlobalKeys.add("Creator", this)),
    mpRDFObj(NULL)
{
  if (pRDFObj)
  {mpRDFObj = pRDFObj;}
  else
    {
      mpRDFObj = new CRDFObject();
      mpRDFObj->setType(CRDFObject::BLANK_NODE);
      mpRDFObj->setBlankNodeId(mKey);
    }
  initObjects();
  CONSTRUCTOR_TRACE;
}

CCreator::CCreator(const CCreator & src,
                   const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Creator", this))
{
  CONSTRUCTOR_TRACE;
  initObjects();
}

void CCreator::initObjects()
{}

CCreator::~CCreator()
{
  GlobalKeys.remove(mKey);
  pdelete(mpRDFObj);
}

const std::string CCreator::getObjectName() const
  {return getFamilyName();}

const std::string CCreator::getFamilyName() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("FamilyName", *mpRDFObj);}

const std::string CCreator::getGivenName() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("GivenName", *mpRDFObj);}

const std::string CCreator::getEmail() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("Email", *mpRDFObj);}

const std::string CCreator::getORG() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("Orgname", *mpRDFObj);}

CRDFObject& CCreator::getRDFObject()
{return *mpRDFObj;}

bool CCreator::setObjectName(const std::string & name)
{
  setFamilyName(name);
  return true;
}
void CCreator::setFamilyName(const std::string familyName)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("FamilyName", *mpRDFObj, familyName);}

void CCreator::setGivenName(const std::string givenName)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("GivenName", *mpRDFObj, givenName);}

void CCreator::setEmail(const std::string Email)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("Email", *mpRDFObj, Email);}

void CCreator::setORG(const std::string Orgname)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("Orgname", *mpRDFObj, Orgname);}

const std::string & CCreator::getKey() const {return mKey;} //By G
