// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/Attic/CPublication.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/02 13:35:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "report/CKeyFactory.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"

#include "CPublication.h"

CPublication::CPublication(const std::string & objectName, const CCopasiContainer * pParent,
                           CRDFObject* pRDFObj) :
    CCopasiContainer(objectName, pParent, "Publication"),
    mKey(GlobalKeys.add("Publication", this)),
    mpRDFObj(NULL)
{
  if (pRDFObj)
  {mpRDFObj = pRDFObj;}
  else
    {
      mpRDFObj = new CRDFObject();
      mpRDFObj->setType(CRDFObject::RESOURCE);
      mpRDFObj->setResource(mKey, false);
    }
  initObjects();
  CONSTRUCTOR_TRACE;
}

CPublication::CPublication(const CPublication & src,
                           const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Publication", this))
{
  CONSTRUCTOR_TRACE;
  initObjects();
}

void CPublication::initObjects()
{}

CPublication::~CPublication()
{
  GlobalKeys.remove(mKey);
  pdelete(mpRDFObj);
}

const std::string CPublication::getObjectName() const
  {return getURL();}

const std::string CPublication::getURL() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("URL", *mpRDFObj);}

CRDFObject& CPublication::getRDFObject()
{return *mpRDFObj;}

void CPublication::setURL(const std::string URL)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("URL", *mpRDFObj, URL);}

const std::string & CPublication::getKey() const {return mKey;} //By G
