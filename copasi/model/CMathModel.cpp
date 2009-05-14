// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMathModel.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/05/14 18:49:40 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMathModel.h"

CMathModel::CMathModel(const CCopasiContainer * pParent) :
    CCopasiContainer("MathModel", pParent, "MathModel"),
    mpModel(NULL),
    mProcessQueue(),
    mEvents("ListOfMathEvents", this)
{}

CMathModel::CMathModel(const CMathModel & src,
                       const CCopasiContainer * pParent) :
    CCopasiContainer(src, pParent),
    mpModel(src.mpModel),
    mProcessQueue(src.mProcessQueue),
    mEvents(src.mEvents, this)
{}

// virtual
CMathModel::~CMathModel()
{}

bool CMathModel::compile(CModel * pModel,
                         std::vector< CCopasiContainer * > listOfContainer)
{
  // TODO Implement me!

  // For each CEvent we need to create a CMathEvent

  // We need to create a CVector of values containing the current root finder values

  // We need to compile a refresh sequence which calculates all root values.

  // We need a mapping of integers identifying roots to CMathTrigger and CMathEvents

  return false;
}

bool CMathModel::initialize()
{
  bool success = true;

  success &= mProcessQueue.initialize(this);

  // TODO Implement me!

  return false;
}

bool CMathModel::applyEvent(CMathEvent * pEvent)
{
  // TODO Implement me!

  // We need to update the model values which depend on values changed by the
  // event.

  return false;
}

void CMathModel::changeRootStatus(CVector< C_INT > & roots)
{
  // TODO Implement me!

  // All triggers effected by the found roots need to be evaluated whether they fire.
  // In case one fires the corresponding event needs to be scheduled in the process queue.

  return;
}

void CMathModel::evaluateRoots(CVector< double > & rootValues)
{
  // TODO Implement me!

  return;
}
