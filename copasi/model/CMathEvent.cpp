// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CMathEvent.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/27 19:03:34 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMathEvent.h"

CMathEvent::CAssignment::CAssignment(const CCopasiContainer * pParent) :
    CCopasiContainer("MathEventAssignment", pParent),
    mpTarget(NULL),
    mExpression("Expression", this)
{}

CMathEvent::CAssignment::CAssignment(const CMathEvent::CAssignment & src,
                                     const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mpTarget(src.mpTarget),
    mExpression(src.mExpression, this)
{}

CMathEvent::CAssignment::~CAssignment()
{}

CMathEvent::CMathEvent(const CCopasiContainer * pParent) :
    CCopasiContainer("MathEvent", pParent),
    mTrigger("TriggerExpression", this),
    mActive(false),
    mEquality(false),
    mHaveDelay(false),
    mDelay("DelayExpression", this),
    mDelayAssignment(true),
    mAssignments("ListOfMathEventAssignment", this)
{}

CMathEvent::CMathEvent(const CMathEvent & src,
                       const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mTrigger(src.mTrigger, this),
    mActive(src.mActive),
    mEquality(src.mEquality),
    mHaveDelay(src.mHaveDelay),
    mDelay(src.mDelay, this),
    mDelayAssignment(src.mDelayAssignment),
    mAssignments(src.mAssignments, this)
{}

CMathEvent::~CMathEvent()
{}
