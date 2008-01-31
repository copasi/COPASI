// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/Attic/CAuthor.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/01/31 05:01:50 $
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

#include "CAuthor.h"

CAuthor::CAuthor(const std::string & objectName, const CCopasiContainer * pParent,
                 CRDFObject * pRDFObj) :
    CCopasiContainer(objectName, pParent, "Author"),
    mKey(GlobalKeys.add("Author", this)),
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

CAuthor::CAuthor(const CAuthor & src,
                 const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Author", this))
{
  CONSTRUCTOR_TRACE;
  initObjects();
}

void CAuthor::initObjects()
{}

CAuthor::~CAuthor()
{
  GlobalKeys.remove(mKey);
  pdelete(mpRDFObj);
}

const std::string CAuthor::getObjectName() const
  {return getFamilyName();}

const std::string CAuthor::getFamilyName() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("FamilyName", *mpRDFObj);}

const std::string CAuthor::getGivenName() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("GivenName", *mpRDFObj);}

const std::string CAuthor::getEmail() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("Email", *mpRDFObj);}

const std::string CAuthor::getORG() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("Orgname", *mpRDFObj);}

CRDFObject& CAuthor::getRDFObject()
{return *mpRDFObj;}

void CAuthor::setFamilyName(const std::string familyName)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("FamilyName", *mpRDFObj, familyName);}

void CAuthor::setGivenName(const std::string givenName)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("GivenName", *mpRDFObj, givenName);}

void CAuthor::setEmail(const std::string Email)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("Email", *mpRDFObj, Email);}

void CAuthor::setORG(const std::string Orgname)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("Orgname", *mpRDFObj, Orgname);}

const std::string & CAuthor::getKey() const {return mKey;} //By G
