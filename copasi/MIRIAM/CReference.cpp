// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CReference.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/05 15:34:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CRDFNode.h"
#include "CModelMIRIAMInfo.h"
#include "CReference.h"

#include "report/CKeyFactory.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"

CReference::CReference(const std::string & objectName,
                       const CCopasiContainer * pParent):
    CCopasiContainer(objectName, pParent, "Reference"),
    mTriplet(),
    mNodePath(),
    mKey(GlobalKeys.add("Reference", this)),
    mPubMed("PubMed", ""),
    mDOI("DOI", "")
{}

CReference::CReference(const CRDFTriplet & triplet,
                       const std::string & objectName,
                       const CCopasiContainer * pParent):
    CCopasiContainer(objectName, pParent, "Reference"),
    mTriplet(triplet),
    mNodePath(),
    mKey(GlobalKeys.add("Creator", this)),
    mPubMed("PubMed", ""),
    mDOI("DOI", "")
{
  if (!mTriplet)
    return;

  mNodePath = mTriplet.pObject->getPath();

  CRDFPredicate::ePredicateType Predicates[] =
    {
      CRDFPredicate::copasi_isDescribedBy,
      CRDFPredicate::bqbiol_isDescribedBy,
      CRDFPredicate::bqmodel_isDescribedBy,
      CRDFPredicate::end
    };

  std::set< CRDFTriplet > Triples;

  CRDFPredicate::ePredicateType * pPredicate = Predicates;
  std::set< CRDFTriplet >::iterator it;
  std::set< CRDFTriplet >::iterator end;

  for (; *pPredicate != CRDFPredicate::end; ++pPredicate)
    {
      Triples =
        mTriplet.pObject->getTripletsWithPredicate(mNodePath, *pPredicate, mTriplet);

      it = Triples.begin();
      end = Triples.end();

      for (; it != end; ++it)
        {
          const std::string & URI = it->pObject->getObject().getResource();

          if (mPubMed.isValid(URI))
            mPubMed.setNode(it->pObject);
          else if (mDOI.isValid(URI))
            mDOI.setNode(it->pObject);
        }
    }
}

CReference::CReference(const CReference & src,
                       const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mTriplet(src.mTriplet),
    mNodePath(src.mNodePath),
    mKey(GlobalKeys.add("Creator", this)),
    mPubMed(src.mPubMed),
    mDOI(src.mDOI)
{}

CReference::~CReference()
{
  GlobalKeys.remove(mKey);
}

const CRDFTriplet & CReference::getTriplet() const
  {return mTriplet;}

const std::string & CReference::getKey() const
  {return mKey;}

const std::string & CReference::getPubmedId() const
  {return mPubMed.getId();}

const std::string & CReference::getDOI() const
  {return mDOI.getId();}

const std::string & CReference::getDescription() const
  {return mTriplet.pObject->getFieldValue(CRDFPredicate::dcterms_description, mNodePath, mTriplet);}

void CReference::setPubmedId(const std::string & pubmedId)
{
  mPubMed.setId(pubmedId);
  mTriplet.pObject->setFieldValue(mPubMed, CRDFPredicate::copasi_isDescribedBy, mNodePath, mTriplet);
}

void CReference::setDOI(const std::string & DOI)
{
  mDOI.setId(DOI);
  mTriplet.pObject->setFieldValue(mDOI, CRDFPredicate::copasi_isDescribedBy, mNodePath, mTriplet);
}

void CReference::setDescription(const std::string & description)
{
  mTriplet.pObject->setFieldValue(description, CRDFPredicate::dcterms_description, mNodePath, mTriplet);
}
