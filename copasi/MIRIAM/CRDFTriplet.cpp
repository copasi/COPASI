// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFTriplet.cpp,v $
//   $Revision: 1.3.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/05/25 21:26:31 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CRDFGraph.h"
#include "CRDFSubject.h"

CRDFTriplet::CRDFTriplet(CRDFNode * pSubject,
                         const CRDFPredicate & predicate,
                         CRDFNode * pObject):
    pSubject(pSubject),
    Predicate(predicate),
    pObject(pObject)
{}

CRDFTriplet::~CRDFTriplet()
{}

CRDFTriplet::operator bool() const
{return (pSubject != NULL && pObject != NULL);}

bool CRDFTriplet::operator == (const CRDFTriplet & rhs) const
{
  return (pSubject == rhs.pSubject &&
          pObject == rhs.pObject &&
          Predicate == rhs.Predicate);
}

bool CRDFTriplet::operator < (const CRDFTriplet & rhs) const
{
  if (Predicate != rhs.Predicate)
    return Predicate < rhs.Predicate;

  if (pSubject != rhs.pSubject)
    return pSubject < rhs.pSubject;

  return pObject < rhs.pObject;
}

std::ostream & operator << (std::ostream & os, const CRDFTriplet & triplet)
{
  if (triplet)
    {
      os << triplet.pSubject->getSubject() << ", ";
      os << triplet.Predicate.getURI() << ", ";
      os << triplet.pObject->getObject() << std::endl;
    }
  else
    os << "Invalid Triplet" << std::endl;

  return os;
}
