// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathTrigger.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/27 19:03:57 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMathTrigger.h"

CMathTrigger::CRoot::CRoot(const CCopasiContainer * pParent) :
    CCopasiContainer("Root", pParent),
    mRoot("Expression", this),
    mActive(0.0),
    mEquality(false)
{}

CMathTrigger::CRoot::CRoot(const CMathTrigger::CRoot & src,
                           const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mRoot(src.mRoot, this),
    mActive(src.mActive),
    mEquality(src.mEquality)
{}

CMathTrigger::CRoot::~CRoot()
{}

CMathTrigger::CMathTrigger(const CCopasiContainer * pParent) :
    CCopasiContainer("MathTrigger", pParent),
    mTriggerExpression("TriggerExpression", this),
    mActive(false),
    mActivateExpression("ActivateExpression", this),
    mRoots("ListOfRoots", this)
{}

CMathTrigger::CMathTrigger(const CMathTrigger & src,
                           const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mTriggerExpression(src.mTriggerExpression, this),
    mActive(src.mActive),
    mActivateExpression(src.mActivateExpression, this),
    mRoots(src.mRoots, this)
{}

CMathTrigger::~CMathTrigger()
{}

bool CMathTrigger::compile(const CExpression * pTriggerExpression)
{
  return false;
}

bool CMathTrigger::compileAND()
{
  return false;
}

bool CMathTrigger::compileOR()
{
  return false;
}

bool CMathTrigger::compileXOR()
{
  return false;
}

bool CMathTrigger::compileNOT()
{
  return false;
}

bool CMathTrigger::compileEQUALITY()
{
  return false;
}
