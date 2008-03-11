// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CBiologicalDescription.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/03/11 09:12:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "report/CKeyFactory.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"

#include "CBiologicalDescription.h"
#include "CConstants.h"

CBiologicalDescription::CBiologicalDescription(const std::string & objectName, const CCopasiContainer * pParent,
    CRDFObject* pRDFObj) :
    CCopasiContainer(objectName, pParent, "BiologicalDescription"),
    mKey(GlobalKeys.add("BiologicalDescription", this)),
    mpRDFObj(NULL),
    mParentTag("")
{
  if (pRDFObj)
  {mpRDFObj = pRDFObj;}
  else
    {
      mpRDFObj = new CRDFObject();
      mpRDFObj->setType(CRDFObject::RESOURCE);
      mpRDFObj->setResource(mKey, true);
    }
}

CBiologicalDescription::CBiologicalDescription(const CBiologicalDescription & src,
    const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("BiologicalDescription", this)),
    mpRDFObj(src.mpRDFObj == NULL ? NULL : new CRDFObject(*src.mpRDFObj))
{
  mParentTag = src.mParentTag;
}

CBiologicalDescription::~CBiologicalDescription()
{
  GlobalKeys.remove(mKey);
  pdelete(mpRDFObj);
}

const std::string CBiologicalDescription::getObjectName() const
  {return getId();}

const std::string CBiologicalDescription::getRelationship() const
  {
    std::map<std::string, std::string> relationships = CConstants::getRelationships();
    return relationships[getParentTag()];
  }

const std::string CBiologicalDescription::getResource() const
  {
    std::string fieldVal = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("rdf:_#", *mpRDFObj);
    if (fieldVal.length())
      {
        std::string::size_type loc = fieldVal.find('#', 0);
        if (loc == std::string::npos)
        {return "";}
        const std::map<std::string, std::string> resources = CConstants::getResources();
        return CConstants::getKey(resources, fieldVal.substr(0, loc));
      }
    else
    {return "";}
  }

const std::string CBiologicalDescription::getId() const
  {
    std::string fieldVal = CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("rdf:_#", *mpRDFObj);
    if (fieldVal.length())
      {
        std::string::size_type loc = fieldVal.find('#', 0);
        if (loc == std::string::npos)
        {return "";}
        return fieldVal.substr(loc + 1);
      }
    else
    {return "";}
  }
void CBiologicalDescription::setId(const std::string Id, const std::string resource)
{
  std::string predicate;
  if (resource.length())
    {
      std::map<std::string, std::string> resources = CConstants::getResources();
      predicate = resources[resource];
    }

  std::string fieldVal = "";
  if (Id.length())
  {fieldVal = predicate + '#' + Id;}

  CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("rdf:_#", *mpRDFObj, fieldVal);
}

CRDFObject& CBiologicalDescription::getRDFObject()
{return *mpRDFObj;}

const std::string CBiologicalDescription::getParentTag() const
  {return mParentTag;}

void CBiologicalDescription::setParentTag(const std::string pt)
{mParentTag = pt;}

const std::string & CBiologicalDescription::getKey() const {return mKey;} //By G
