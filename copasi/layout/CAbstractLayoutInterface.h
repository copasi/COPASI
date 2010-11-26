// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CAbstractLayoutInterface.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2010/11/26 16:36:36 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CABSTRACTLAYOUTINTERFACE_H
#define CABSTRACTLAYOUTINTERFACE_H

#include <vector>

/**
 * This abstract class describes how an optimization algorithm
 * will see a layout.
 */
class CAbstractLayoutInterface
{
public:
  CAbstractLayoutInterface() {};
  virtual ~CAbstractLayoutInterface() {};

  class VariableDescription
  {
  public:
    bool isAngle;
    //double initialValue;
    double lowerBoundary;
    double upperBoundary;
  };


  virtual bool setState(const std::vector<double> & vars) = 0;
  //virtual bool getState(std::vector<double> & vars) = 0;
  virtual double getPotential() = 0;

  unsigned int getNumVariables() const;
  const std::vector<VariableDescription> & getVariablesDescription() const;

  virtual std::vector<double> getInitialValues() = 0;

  virtual const std::vector<double> & getMassVector() const;

protected:
  std::vector<VariableDescription> mVarDescription;
  std::vector<double> mMassVector;
};

#endif // CABSTRACTLAYOUTINTERFACE_H
