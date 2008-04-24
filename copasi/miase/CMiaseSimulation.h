// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseSimulation.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/04/02 12:14:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CMIASESIMULATION
#define CMIASESIMULATION

#include "CMiaseBase.h"

class CMiaseSimulation : public CMiaseBaseEnhanced
  {

  public:

    CMiaseSimulation();

    ~CMiaseSimulation();
  };

class CMiaseUniformTimeCourse : public CMiaseSimulation
  {

  public:

    CMiaseUniformTimeCourse();

    ~CMiaseUniformTimeCourse();

    double getInitialTime();
    double getOutputStartTime();
    double getOutputEndTime();
    int getNumberOfPoints();

    void setInitialTime(double initialTime);
    void setOutputStartTime(double outputStartTime);
    void setOutputEndTime(double outputEndTime);
    void setNumberOfPoints(double oumberOfPoints);

  private:

    double mInitialTime;
    double mOutputStartTime;
    double mOutputEndTime;
    int mNumberOfPoints;
  };

class SteadyStateAnalysis : public CMiaseSimulation
  {
    //TODO
  };

class AnySimulationType : public CMiaseSimulation
  {
    //TODO
  };

#endif //CMIASESIMULATION
