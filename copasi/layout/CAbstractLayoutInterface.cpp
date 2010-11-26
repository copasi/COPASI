// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CAbstractLayoutInterface.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2010/11/26 16:36:36 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CAbstractLayoutInterface.h"


unsigned int CAbstractLayoutInterface::getNumVariables() const
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
