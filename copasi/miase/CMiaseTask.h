// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseTask.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/04/02 12:14:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CMIASETASK
#define CMIASETASK

#include "CMiaseBase.h"
#include "CMiaseModel.h"
#include "CMiaseSimulation.h"

class CMiaseMeasurementData : public CMiaseBase
  {

  public:

    CMiaseMeasurementData();

    ~CMiaseMeasurementData();

    std::string getSource();
    std::string getName();

    void setSource(std::string source);
    void setName(std::string name);

  private:

    std::string mSource;
    std::string mName;
  };

class CMiaseTask : public CMiaseBaseEnhanced
  {

  public:

    CMiaseTask();

    ~CMiaseTask();

    void setModelReference (std::string model);
    void setSimulationReference (std::string simulation);

    std::string getModelReference ();
    std::string getSimulationReference ();

    void addMeasurement (CMiaseMeasurementData* measurement);

    CMiaseMeasurementData* getMeasurement(int num);

    CMiaseMeasurementData* getLastMeasurement();

    int getNumberOfMeasurements();

  private:

    std::string mModelReference;
    std::string mSimulationReference;

    std::vector < CMiaseMeasurementData* > mListOfMeasurements;
  };
#endif //CMIASETASK
