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

  std::vector<double>::size_type getNumVariables() const;
  const std::vector<VariableDescription> & getVariablesDescription() const;

  virtual const std::vector<double> & getInitialValues() const = 0;

  virtual const std::vector<double> & getMassVector() const;

protected:
  std::vector<VariableDescription> mVarDescription;
  std::vector<double> mMassVector;
};

#endif // CABSTRACTLAYOUTINTERFACE_H
