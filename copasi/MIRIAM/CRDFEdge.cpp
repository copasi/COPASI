// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/Attic/CRDFEdge.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/03 13:20:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CRDFEdge.h"

CRDFEdge::CRDFEdge():
    mPredicate(CRDFPredicate::unknown),
    mPredicateURI(""),
    mpPropertyNode(NULL)
{}

CRDFEdge::CRDFEdge(const CRDFEdge & src):
    mPredicate(src.mPredicate),
    mPredicateURI(src.mPredicateURI),
    mpPropertyNode(src.mpPropertyNode)
{assert(mpPropertyNode != NULL);}

CRDFEdge::CRDFEdge(const CRDFPredicate::ePredicateType & predicate,
                   const CRDFNode * pPropertyNode):
    mPredicate(CRDFPredicate::unknown),
    mPredicateURI(""),
    mpPropertyNode(pPropertyNode)
{
  assert(mpPropertyNode != NULL);
  setPredicate(predicate);
}

CRDFEdge::CRDFEdge(const std::string & predicateURI,
                   const CRDFNode * pPropertyNode):
    mPredicate(CRDFPredicate::unknown),
    mPredicateURI(""),
    mpPropertyNode(pPropertyNode)
{
  assert(mpPropertyNode != NULL);
  setPredicateURI(predicateURI);
}

CRDFEdge::~CRDFEdge()
{}

void CRDFEdge::setPredicate(const CRDFPredicate::ePredicateType & predicate)
{
  mPredicate = predicate;
  mPredicateURI = CRDFPredicate::getURI(predicate);
}

const CRDFPredicate::ePredicateType & CRDFEdge::getPredicate() const
  {return mPredicate;}

void CRDFEdge::setPredicateURI(const std::string & predicateURI)
{
  mPredicateURI = predicateURI;
  mPredicate = CRDFPredicate::getPredicateFromURI(mPredicateURI);

  if (mPredicate == CRDFPredicate::rdf_li)
    mPredicateURI = CRDFPredicate::getURI(mPredicate);
}

const std::string & CRDFEdge::getPredicateURI() const
{return mPredicateURI;}

void CRDFEdge::setPropertyNode(const CRDFNode * pPropertyNode)
{
  mpPropertyNode = pPropertyNode;
  assert(mpPropertyNode != NULL);
}

const CRDFNode * CRDFEdge::getPropertyNode() const
  {return mpPropertyNode;}

bool CRDFEdge::operator == (const CRDFEdge & rhs) const
  {
    // Different predicates
    if (mPredicate != rhs.mPredicate)
      return false;

    // Different unknown predicates
    if (mPredicate == CRDFPredicate::unknown &&
        mPredicateURI != rhs.mPredicateURI)
      return false;

    // Different properties
    if (mpPropertyNode != rhs.mpPropertyNode)
      return false;

    return true;
  }
