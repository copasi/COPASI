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

#include "CAbstractLayoutInterface.h"


std::vector<double>::size_type CAbstractLayoutInterface::getNumVariables() const
{
  return mVarDescription.size();
}

const std::vector<CAbstractLayoutInterface::VariableDescription> & CAbstractLayoutInterface::getVariablesDescription() const
{
  return mVarDescription;
}

const std::vector<double> & CAbstractLayoutInterface::getMassVector() const
{
  return mMassVector;
}
