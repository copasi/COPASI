// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

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
