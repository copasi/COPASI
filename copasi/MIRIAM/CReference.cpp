// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CReference.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/03/03 16:58:28 $
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
	mParentTag(""),
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
  {return getPubmedId();}

const std::string CReference::getPubmedId() const
{	
  std::string predicate = "http://www.pubmed.gov/#";
  std::string fieldVal = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("PubmedId", *mpRDFObj);
  std::string::size_type loc = fieldVal.find(predicate, 0);
  if( loc == std::string::npos ) 
  {	return "";	}
  return fieldVal.substr(loc + predicate.length());
}
void CReference::setPubmedId(const std::string pubmedId)
{
	std::string predicate = "http://www.pubmed.gov/#";
	std::string fieldVal = "";
	if (pubmedId.length())
	{	fieldVal =  predicate + pubmedId;	}
	else
	{	fieldVal = pubmedId;	}
	
	if (mParentTag == "dcterms:references")
	{	CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("PubmedId", *mpRDFObj, fieldVal);	}
}

const std::string CReference::getDOI() const
{	
  std::string predicate = "http://dx.doi.org/";
  std::string fieldVal = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("DOI", *mpRDFObj);
  std::string::size_type loc = fieldVal.find(predicate, 0);
  if( loc == std::string::npos ) 
  {	return "";	}
  return fieldVal.substr(loc + predicate.length());
}
void CReference::setDOI(const std::string DOI)
{
	std::string predicate = "http://dx.doi.org/";
	std::string fieldVal = "";
	if (DOI.length())
	{	fieldVal = predicate + DOI;	}
	else
	{	fieldVal = DOI;	}
	
	if (mParentTag == "dcterms:references")
	{	CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("DOI", *mpRDFObj, fieldVal);	}
}

const std::string CReference::getDescription() const
{	
	if (mParentTag == "dcterms:references")
	{	return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("dcterms:description", *mpRDFObj);	}
	return "";
}
void CReference::setDescription(const std::string d)
{
	if (mParentTag == "dcterms:references")
	{	CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("dcterms:description", *mpRDFObj, d);	}
}

CRDFObject& CReference::getRDFObject()
{return *mpRDFObj;}


const std::string CReference::getParentTag() const
{	return mParentTag;	}

void CReference::setParentTag(const std::string pt)
{	mParentTag = pt;	}

const std::string & CReference::getKey() const {return mKey;} //By G
