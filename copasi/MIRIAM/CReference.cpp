// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CReference.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/25 20:37:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "report/CKeyFactory.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"

#include "CReference.h"

CReference::CReference(const std::string & objectName, const CCopasiContainer * pParent,
                       CRDFObject* pRDFObj) :
    CCopasiContainer(objectName, pParent, "Reference"),
    mKey(GlobalKeys.add("Reference", this)),
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

CReference::CReference(const CReference & src,
                       const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Reference", this))
{
  CONSTRUCTOR_TRACE;
  initObjects();
}

void CReference::initObjects()
{}

CReference::~CReference()
{
  GlobalKeys.remove(mKey);
  pdelete(mpRDFObj);
}

const std::string CReference::getObjectName() const
  {return getURL();}

const std::string CReference::getURL() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("PubmedID", *mpRDFObj);}

CRDFObject& CReference::getRDFObject()
{return *mpRDFObj;}

void CReference::setURL(const std::string URL)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("PubmedID", *mpRDFObj, URL);}

bool CReference::setObjectName(const std::string & name)
{
  setURL(name);
  return true;
}
const std::string & CReference::getKey() const {return mKey;} //By G
