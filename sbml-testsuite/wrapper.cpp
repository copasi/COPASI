// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#define COPASI_MAIN

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
#include <stdlib.h>

#include "copasi/copasi.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/model/CMetab.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/core/CDataVector.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/commandline/COptionParser.h"
#include "copasi/commandline/COptions.h"

#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/core/CDataString.h"

#define THROW_COPASI_EXCEPTION(args)\
  {\
    std::ostringstream os;\
    os << args;\
    CCopasiMessage(CCopasiMessage::EXCEPTION, os.str().c_str());\
  }

void parse_items(const std::string& text, std::list<std::string>& itemList)
{
  // parse the items
  //std::cout << "parsing: " << text << std::endl;
  std::istringstream iss(text);
  std::string token;
  std::string delimiter = " \t\r\n";
  std::size_t begin, end;

  while (getline(iss, token, ','))
    {
      // strip whitespaces
      begin = token.find_first_not_of(delimiter);
      end = token.find_last_not_of(delimiter);

      if (begin != std::string::npos)
        {
          //std::cout << token.substr(begin,end-begin+1) << std::endl;
          itemList.push_back(token.substr(begin, end - begin + 1));
        }
    }
}

/**
 * @brief The SBMLTestRunner class
 * This class parses a given settings file and runs the specified test
 */
class SBMLTestRunner
{
public:
  /**
   * @brief constructs a new SBMLTestRunner object from command line arguments
   *
   * @param argc number of command line arguments
   * @param argv the command line arguments
   */
  SBMLTestRunner(int argc, char* argv[])
    : in_dir("")
    , out_dir("")
    , test_name("")
    , level(0)
    , version(0)
    , start_time(0.0)
    , duration(0.0)
    , steps(0)
    , variables()
    , amounts()
    , concentrations()
    , absolute_error(0.0)
    , relative_error(0.0)
    , settingsFile("")
    , sbml_filename("")
    , end_time(0.0)
    , output_filename("")
    , pTrajectoryTask(NULL)
    , pDataModel(NULL)
    , methodType(CTaskEnum::Method::deterministic)
  {
    if (argc < 6)
      {
        THROW_COPASI_EXCEPTION("Usage: sbml-testsuite INPUT_DIRECTORY TESTNAME OUTPUTDIRECTORY SBMLLEVEL SBMLVERSION [METHOD]" << std::endl);
      }

    in_dir = argv[1];
    test_name = argv[2];
    out_dir = argv[3];
    level = strtol(argv[4], NULL, 10);
    version = strtol(argv[5], NULL, 10);

    if (argc > 6)
      {
        std::stringstream  MethodType;

        for (int i = 6; i < argc; ++i)
          {
            if (i > 6) MethodType << " ";

            MethodType << argv[i];
          }

        methodType = CTaskEnum::MethodName.toEnum(unQuote(MethodType.str()), CTaskEnum::Method::deterministic);
      }

    std::ostringstream os;
    os << in_dir << "/" << test_name << "/" << test_name << "-settings.txt";
    settingsFile = os.str();

    parseAndValidateSettings(settingsFile);

    //printSettings();

    os.str("");
    os << in_dir << "/" << test_name << "/" << test_name << "-sbml-l" << level << "v" << version << ".xml";
    sbml_filename = os.str();
    os.str("");

    os << out_dir << "/" << test_name << ".csv";
    output_filename = os.str();
  }

  /**
   * @brief parses the given settings file and validates the settings
   * @param settingsFile the settings file to parse
   */
  void parseAndValidateSettings(const std::string& settingsFile)
  {
    if (level < 1 || level > 3)
      {
        THROW_COPASI_EXCEPTION("SBML Level " << level << " Version " << version << " not supported." << std::endl);
      }

    if (level == 1 && (version < 1 || version > 2))
      {
        THROW_COPASI_EXCEPTION("SBML Level " << level << " Version " << version << " not supported." << std::endl);
      }

    // open the settings file and parse it
    std::cout << "parsing file: " << settingsFile << std::endl;
    std::ifstream f;
    f.open(settingsFile.c_str());

    if (!f.is_open())
      {
        THROW_COPASI_EXCEPTION("Error. Unable to open file \"" << settingsFile << "\"." << std::endl);
      }

    std::string line;

    while (! f.eof())
      {
        getline(f, line);
        size_t pos = line.find(':');

        if (pos != std::string::npos)
          {
            std::string tag = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            if (tag == "start")
              {
                start_time = strToDouble(value.c_str(), NULL);
              }
            else if (tag == "duration")
              {
                duration = strToDouble(value.c_str(), NULL);
              }
            else if (tag == "steps")
              {
                steps = strtol(value.c_str(), NULL, 10);
              }
            else if (tag == "variables")
              {
                // parse the variables
                parse_items(value, variables);
              }
            else if (tag == "amount")
              {
                // parse the variables
                std::list<std::string> tmp;
                parse_items(value, tmp);
                amounts.insert(tmp.begin(), tmp.end());
              }
            else if (tag == "concentration")
              {
                // parse the variables
                std::list<std::string> tmp;
                parse_items(value, tmp);
                concentrations.insert(tmp.begin(), tmp.end());
              }
            else if (tag == "absolute")
              {
                absolute_error = strToDouble(value.c_str(), NULL);
              }
            else if (tag == "relative")
              {
                relative_error = strToDouble(value.c_str(), NULL);
              }
            else
              {
                std::cerr << "Warning. Unknown tag \"" << tag << "\"." << std::endl;
              }
          }
      }

    f.close();

    if (duration <= 0.0)
      {
        THROW_COPASI_EXCEPTION("Error. Duration < 0.0." << std::endl);
      }

    if (steps == 0)
      {
        THROW_COPASI_EXCEPTION("Error. Number of steps set to 0." << std::endl);
      }

    if (variables.empty())
      {
        THROW_COPASI_EXCEPTION("Error. No variables specified." << std::endl);
      }

    if (start_time < 0.0)
      {
        THROW_COPASI_EXCEPTION("Error. Start time < 0.0." << std::endl);
      }

    if (absolute_error < 0.0)
      {
        THROW_COPASI_EXCEPTION("Error. Absolute error < 0.0." << std::endl);
      }

    if (relative_error < 0.0)
      {
        THROW_COPASI_EXCEPTION("Error. Relative error < 0.0." << std::endl);
      }

    end_time = start_time + duration;

    if (end_time == 0.0)
      {
        THROW_COPASI_EXCEPTION("Error. Invalid endtime " << end_time << std::endl);
      }
  }

  /**
   * @brief prints all settings to std out
   */
  void printSettings()
  {
    std::cout << "Simulating " << in_dir << "/" << test_name << "/" << test_name << "-sbml-l" << level << "v" << version << ".xml" << std::endl;
    std::cout << "Start time: " << start_time << std::endl;
    std::cout << "Duration: " << duration << std::endl;
    std::cout << "Absolute error: " << absolute_error << std::endl;
    std::cout << "Relative error: " << relative_error << std::endl;
    std::list<std::string>::const_iterator it = variables.begin(), endit = variables.end();
    std::cout << "Outputting variables: ";

    while (it != endit)
      {
        std::cout << *it << ", ";
        ++it;
      }

    std::cout << std::endl;
  }

  /**
   * @brief creates the CSV report for the loaded model
   */
  void createReport()
  {
    CReportDefinitionVector* pReports = pDataModel->getReportDefinitionList();
    CReportDefinition* pReport = pReports->createReportDefinition("Report", "Output for SBML testsuite run");
    pReport->setSeparator(",");
    pReport->setTaskType(CTaskEnum::Task::timeCourse);
    pReport->setIsTable(false);
    pReport->setPrecision(std::numeric_limits<double>::digits10 + 2);

    std::vector<CRegisteredCommonName>* pHeaderAddr = pReport->getHeaderAddr();
    std::vector<CRegisteredCommonName>* pBodyAddr = pReport->getBodyAddr();

    //std::vector<CRegisteredCommonName>* pTable = pReport->getTableAddr();
    pHeaderAddr->push_back(CDataString("time").getCN());
    pBodyAddr->push_back(CCommonName(pDataModel->getModel()->getValueReference()->getCN()));
    pHeaderAddr->push_back(pReport->getSeparator().getCN());
    pBodyAddr->push_back(pReport->getSeparator().getCN());
    // create a map of all possible variables
    std::map<std::string, const CDataObject * > variableMap;
    const CDataVector<CMetab>& metabolites = pDataModel->getModel()->getMetabolites();
    unsigned int i, iMax = metabolites.size();

    for (i = 0; i < iMax; ++i)
      {
        variableMap.insert(std::pair<std::string, const CModelEntity*>(metabolites[i].getSBMLId(), &metabolites[i]));
      }

    const CDataVector<CCompartment>& compartments = pDataModel->getModel()->getCompartments();

    iMax = compartments.size();

    for (i = 0; i < iMax; ++i)
      {
        variableMap.insert(std::pair<std::string, const CDataObject*>(compartments[i].getSBMLId(), &compartments[i]));
      }

    const CDataVector<CModelValue>& modelValues = pDataModel->getModel()->getModelValues();

    iMax = modelValues.size();

    for (i = 0; i < iMax; ++i)
      {
        variableMap.insert(std::pair<std::string, const CDataObject*>(modelValues[i].getSBMLId(), &modelValues[i]));
      }

    const CDataVector<CReaction>& reactions = pDataModel->getModel()->getReactions();
    iMax = reactions.size();

    for (i = 0; i < iMax; ++i)
      {
        variableMap.insert(std::pair<std::string, const CDataObject*>(reactions[i].getSBMLId(), &reactions[i]));
      }

    std::list<std::string>::const_iterator it = variables.begin(), endit = variables.end();
    std::map<std::string, const CDataObject*>::const_iterator pos;
    unsigned int dummyCount = 1;

    while (it != endit)
      {
        pos = variableMap.find(*it);

        if (pos == variableMap.end())
          {
            THROW_COPASI_EXCEPTION("Could not find a model entity for the SBML id " << *it << std::endl);
          }

        const CMetab* pMetab = dynamic_cast<const CMetab*>(pos->second);
        const CCompartment* pComp = dynamic_cast<const CCompartment*>(pos->second);
        const CModelValue* pMV = dynamic_cast<const CModelValue*>(pos->second);
        const CReaction* pReaction = dynamic_cast<const CReaction*>(pos->second);

        if (pMetab != NULL)
          {
            pHeaderAddr->push_back(CDataString(pMetab->getSBMLId()).getCN());

            if (amounts.find(*it) != amounts.end())
              {
                // create a new global value with an assignment
                std::stringstream ss;
                ss << "dummy_modelvalue_" << dummyCount;
                CModelValue* pTmpMV = pDataModel->getModel()->createModelValue(ss.str());
                ++dummyCount;
                ss.str("");
                assert(pTmpMV);
                // create an assignment that takes the concentration of the
                // metabolite and multiplies it by the compartment
                ss << "<" << pMetab->getConcentrationReference()->getCN() << "> * <" << pMetab->getCompartment()->getValueReference()->getCN() << ">";
                pTmpMV->setStatus(CModelEntity::Status::ASSIGNMENT);
                bool tmpRes = pTmpMV->setExpression(ss.str());
                assert(tmpRes == true);
                pBodyAddr->push_back(pTmpMV->getValueReference()->getCN());
              }
            else if (concentrations.find(*it) != concentrations.end())
              {
                pBodyAddr->push_back(pMetab->getConcentrationReference()->getCN());
              }
            else
              {
                THROW_COPASI_EXCEPTION("Species \"" << *it << "\" neither given in the amounts or the concentration section." << std::endl);
              }
          }

        if (pComp != NULL)
          {
            pHeaderAddr->push_back(CDataString(pComp->getSBMLId()).getCN());
            pBodyAddr->push_back(pComp->getValueReference()->getCN());
          }

        if (pMV != NULL)
          {
            pHeaderAddr->push_back(CDataString(pMV->getSBMLId()).getCN());
            pBodyAddr->push_back(pMV->getValueReference()->getCN());
          }

        if (pReaction != NULL)
          {
            pHeaderAddr->push_back(CDataString(pReaction->getSBMLId()).getCN());
            pBodyAddr->push_back(pReaction->getFluxReference()->getCN());
          }

        ++it;

        if (it != endit)
          {
            pHeaderAddr->push_back(pReport->getSeparator().getCN());
            pBodyAddr->push_back(pReport->getSeparator().getCN());
          }
      }

    // create a trajectory task
    pTrajectoryTask =  new CTrajectoryTask(pDataModel->getTaskList());
    pTrajectoryTask->setScheduled(true);

    pTrajectoryTask->getReport().setReportDefinition(pReport);
    pTrajectoryTask->getReport().setTarget(output_filename);
    pTrajectoryTask->getReport().setAppend(false);
  }

  /**
   * @brief sets up the simulation
   */
  void setupSimulation()
  {
    CTrajectoryProblem* pProblem = dynamic_cast<CTrajectoryProblem*>(pTrajectoryTask->getProblem());

    pProblem->setStepNumber((const unsigned C_INT32)steps);
    pProblem->setDuration((const C_FLOAT64)end_time);
    pProblem->setTimeSeriesRequested(true);

    pTrajectoryTask->setMethodType(methodType);

    CTrajectoryMethod* pMethod = dynamic_cast<CTrajectoryMethod*>(pTrajectoryTask->getMethod());

    if (pMethod->getParameter("Absolute Tolerance") != NULL)
      {
        pMethod->getParameter("Absolute Tolerance")->setValue(1.0e-12);
      }

    if (pMethod->getParameter("Partitioning Strategy"))
      {
        pMethod->setValue("Partitioning Strategy", std::string("All Reactions Deterministic"));
      }

    if (pMethod->getParameter("Internal Steps Size"))
      {
        pMethod->setValue("Internal Steps Size", 1.0e-4);
      }

    CDataVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();

    TaskList.remove("Time-Course");
    TaskList.add(pTrajectoryTask, true);
  }

  /**
   * @brief runs the test
   *
   * This function loads the specified model, sets up the report and the simulation
   * and then runs it.
   *
   * @param saveCopasiFile if true, the generated COPASI file will be saved
   */
  void runTest(bool saveCopasiFile = true)
  {
    // Create the global data model.
    pDataModel = CRootContainer::addDatamodel();

    // Import the SBML File
    pDataModel->importSBML(sbml_filename.c_str());

    // create a report with the correct filename and all the species against
    // time.
    createReport();

    // set up the simulation
    setupSimulation();

    // save the file for control purposes
    if (saveCopasiFile)
      {
        std::string saveFilename = sbml_filename.substr(0, sbml_filename.length() - 4) + ".cps";
        pDataModel->saveModel(saveFilename, NULL, true, false);
      }

    // Run the trajectory task

    if (!pTrajectoryTask->initialize(CCopasiTask::OUTPUT_SE, pDataModel, NULL))
      {
        std::cerr << CCopasiMessage::getAllMessageText();
      }
    else if (!pTrajectoryTask->process(true))
      {
        std::cerr << CCopasiMessage::getAllMessageText();
      }
    else if (!pTrajectoryTask->restore())
      {
        std::cerr << CCopasiMessage::getAllMessageText();
      }
  }

private:
  std::string in_dir;
  std::string out_dir;
  std::string test_name;
  unsigned int level;
  unsigned int version;
  double start_time;
  double duration;
  unsigned int steps;
  std::list<std::string> variables;
  std::set<std::string> amounts;
  std::set<std::string> concentrations;
  double absolute_error;
  double relative_error;
  std::string settingsFile;
  std::string sbml_filename;
  double end_time;
  std::string output_filename;
  CTrajectoryTask* pTrajectoryTask;
  CDataModel* pDataModel;
  CTaskEnum::Method methodType;
};

int main(int argc, char* argv[])
{
  try
    {
      // Create the root container.
      CRootContainer::init(argc, argv, false);
    }
  catch (copasi::autoexcept &/*e*/)
    {}

  catch (copasi::option_error &/*e*/)
    {}

  int result = 0;

  try
    {
      SBMLTestRunner runner(argc, argv);
      runner.runTest();
      std::cout << "DONE ..." << std::endl;
    }
  catch (CCopasiException & exception)
    {
      std::cout << "Stopped with error ..." << std::endl;
      std::cerr << exception.getMessage().getText() << std::endl;
      result = 1;
    }

  CRootContainer::destroy();

  return result;
}
