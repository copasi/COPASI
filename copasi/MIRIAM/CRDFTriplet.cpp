// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFTriplet.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/05 15:34:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CRDFTriplet.h"

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
