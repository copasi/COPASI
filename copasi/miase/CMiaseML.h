// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseML.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/03/23 14:45:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CMIASEML
#define CMIASEML

#include "CMiaseBase.h"
#include "CMiaseSimulation.h"
#include "CMiaseTask.h"
#include "CMiaseModel.h"
#include "CMiaseOutput.h"

class CMiaseSed : public CMiaseBase
  {
  public:

    CMiaseSed();

    ~CMiaseSed();

    void addSimulation (CMiaseSimulation* simulation);
    void addTask (CMiaseTask* task);
    void addModel (CMiaseModel* model);
    void addOutput (CMiaseOutput* output);

    CMiaseSimulation* getSimulation (int num);
    CMiaseSimulation* getSimulation (std::string id);
    CMiaseSimulation* getLastSimulation ();
    int getNumOfSimulations ();

    CMiaseTask* getTask(int num);
    CMiaseTask* getTask(std::string id);
    CMiaseTask* getLastTask();
    int getNumOfTasks ();

    CMiaseModel* getModel(int num);
    CMiaseModel* getModel(std::string id);
    CMiaseModel* getLastModel();
    int getNumOfModels ();

    CMiaseOutput* getOutput(int num);
    CMiaseOutput* getOutput(std::string id);
    CMiaseOutput* getLastOutput();
    int getNumOfOutputs ();

  private:

    std::vector< CMiaseSimulation* > mListofSimulations;
    std::vector< CMiaseTask* > mListofTasks;
    std::vector< CMiaseModel* > mListofModels;
    std::vector< CMiaseOutput* > mListofOutputs;
  };

class CMiaseML : public CMiaseBase
  {

  public:

    CMiaseML();

    ~CMiaseML();

    void setMiaseSed(CMiaseSed* sed);
    CMiaseSed* getSed();

    std::string getXmlns();
    std::string getVersion();

    void setXmlns(std::string xmlns);
    void setVersion(std::string version);

  private:

    CMiaseSed* mSed;

    std::string mXmlns;
    std::string mVersion;
  };

#endif //CMIASEML
