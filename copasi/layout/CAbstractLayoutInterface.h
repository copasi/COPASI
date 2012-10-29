// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
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

  virtual const std::vector<double> & getInitialValues() const = 0;

  virtual const std::vector<double> & getMassVector() const;

protected:
  std::vector<VariableDescription> mVarDescription;
  std::vector<double> mMassVector;
};

#endif // CABSTRACTLAYOUTINTERFACE_H
