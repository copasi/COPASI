// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModified.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/04/21 20:12:31 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "report/CKeyFactory.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"

#include "CModelMIRIAMInfo.h"
#include "CModified.h"

CModified::CModified(const std::string & objectName, const CCopasiContainer * pParent,
                     CRDFObject* pRDFObj) :
    CCopasiContainer(objectName, pParent, "Modified"),
    mKey(GlobalKeys.add("Modified", this)),
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
}

CModified::CModified(const CModified & src,
                     const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Modified", this)),
    mpRDFObj(src.mpRDFObj == NULL ? NULL : new CRDFObject(*src.mpRDFObj))
{}

CModified::~CModified()
{
  GlobalKeys.remove(mKey);
  pdelete(mpRDFObj);
}

const std::string CModified::getObjectName() const
  {return getDateModified();}

const std::string CModified::getDateModified() const
  {return dynamic_cast <CModelMIRIAMInfo*> (getObjectParent()->getObjectParent())->getRDFGraph()->getFieldValue("dcterms:W3CDTF", *mpRDFObj);}

CRDFObject& CModified::getRDFObject()
{return *mpRDFObj;}

void CModified::setDateModified(const std::string dateModified)
{dynamic_cast <CModelMIRIAMInfo*> (getObjectParent()->getObjectParent())->getRDFGraph()->setFieldValue("dcterms:W3CDTF", *mpRDFObj, dateModified);}

const std::string & CModified::getKey() const {return mKey;} //By G
