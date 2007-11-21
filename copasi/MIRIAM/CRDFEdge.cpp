// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/Attic/CRDFEdge.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/21 16:15:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CRDFEdge.h"

CRDFEdge::CRDFEdge():
    mPredicate(""),
    mpPropertyNode(NULL)
{}

CRDFEdge::CRDFEdge(const CRDFEdge & src):
    mPredicate(src.mPredicate),
    mpPropertyNode(src.mpPropertyNode)
{}

CRDFEdge::CRDFEdge(const std::string & predicate,
                   CRDFNode * pPropertyNode):
    mPredicate(predicate),
    mpPropertyNode(pPropertyNode)
{}

CRDFEdge::~CRDFEdge()
{}

void CRDFEdge::setPredicate(const std::string & predicate)
{mPredicate = predicate;}

const std::string & CRDFEdge::getPredicate() const
  {return mPredicate;}

void CRDFEdge::setProprtyNode(CRDFNode * pPropertyNode)
{mpPropertyNode = pPropertyNode;}

CRDFNode * CRDFEdge::getPropertyNode()
{return mpPropertyNode;}
