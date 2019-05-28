// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * This examples demonstrates how to read in a copasi file, change its
 * parameters and run a parameter scan while changing the report filename
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <copasi/utilities/CParameterEstimationUtils.h>

#define COPASI_MAIN

#include "copasi/CopasiTypes.h"

using namespace std;


/**
 * This function changes the double value of the given element to
 * the specified value
 *
 * @param element the data object whose value to change
 * @param value the new double value
 *
 * @return true, indicating that the model value was changed,
 *         false if it is not a supported object
 */
bool
changeModelParameter(CDataObject* element, double value)
{
  if (element == NULL)
    return false;

  CDataObjectReference<double>* pRef =
    dynamic_cast<CDataObjectReference<double>*>(element);

  if (pRef != NULL)
    {
      if (pRef->getValuePointer() != NULL)
        {
          *static_cast<double*>(pRef->getValuePointer()) = value;

          if (pRef->getObjectName() == "InitialConcentration" &&
              pRef->getObjectDataModel() != NULL &&
              pRef->getObjectDataModel()->getModel() != NULL)
            pRef->getObjectDataModel()->getModel()->updateInitialValues(pRef);

          return true;
        }
    }

  CCopasiParameter* pParam = dynamic_cast<CCopasiParameter*>(element);

  if (pParam != NULL)
    {
      if (pParam->getValuePointer() != NULL)
        {
          *static_cast<double*>(pParam->getValuePointer()) = value;
          return true;
        }
    }

  return false;
}

/**
 * updates the given data model with values from the provided ini file.
 * This file should have the simple syntax, of one of more statements:
 *
 *    name = value
 *
 * where name is a valid DisplayName of a model object, and value a double
 * value to be assigned. To indicate a comment, use the semicolon ';' after
 * which the remaining line will be disregarded.
 *
 * @param pDataModel the data model to update
 * @param fileName the fileName of the ini file
 */
void
changeParametersFromIniFile(CDataModel* pDataModel, const std::string& fileName)
{
  ifstream ifs(fileName.c_str(), std::ios_base::in);

  if (!ifs.good())
    {
      cerr << "Couldn't open file with parameters" << endl;
      exit(1);
    }

  std::string line;

  while (std::getline(ifs, line))
    {
      // remove comments
      size_t pos = line.find(';');

      if (pos != std::string::npos)
        line = line.substr(0, pos);

      pos = line.rfind('=');

      if (pos == std::string::npos) // no equals sign found invalid
        continue;

      std::string key = ResultParser::trim(line.substr(0, pos));
      std::string value = ResultParser::trim(line.substr(pos + 1));

      if (key.empty() || value.empty())
        continue;

      double dValue = ResultParser::saveToDouble(value);

      CDataObject* element =
        const_cast<CDataObject*>(pDataModel->findObjectByDisplayName(key));

      if (element == NULL) // no such element, or no supported element
        continue;

      if (changeModelParameter(element, dValue))
        pDataModel->getModel()->setCompileFlag(); // mark as changed
    }

  pDataModel->getModel()->compileIfNecessary(NULL); // compile if needed
}

/**
 * This function will read in reaction parameters in the form
 *
 *   reaction_id parameterId value
 *
 * and will reparameterize the model with those values
 */
void changeParametersFromTsvFile(CDataModel* pDataModel, const std::string& fileName)
{
  ifstream ifs(fileName.c_str(), std::ios_base::in);

  if (!ifs.good())
    {
      cerr << "Couldn't open file with parameters" << endl;
      exit(1);
    }

  auto& reactions = pDataModel->getModel()->getReactions();

  while (ifs.good())
    {
      string reactionId; string parameterId; double value;
      ifs >> reactionId >> parameterId >> value;

      if (reactionId.empty() || parameterId.empty()) break;

      // find model value ... change value
      try
        {
          reactions[reactionId].setParameterValue(parameterId, value);
          reactions[reactionId].compile();
          pDataModel->getModel()->setCompileFlag();
        }
      catch (...)
        {
          cerr << "Couldn't change parameter '" << reactionId << "." << parameterId << "'." << endl;
          exit(1);
        }
    }

  pDataModel->getModel()->compileIfNecessary(NULL);
}


int main(int argc, char** argv)
{
  // initialize the backend library
  CRootContainer::init(argc, argv);
  assert(CRootContainer::getRoot() != NULL);
  // create a new datamodel
  CDataModel* pDataModel = CRootContainer::addDatamodel();
  assert(CRootContainer::getDatamodelList()->size() == 1);

  // the only argument to the main routine should be the name of an SBML file
  if (argc != 4)
    {
      std::cerr << "Usage: runScan <copasi file> <parameter set> <report name>" << std::endl;
      CRootContainer::destroy();
      return 1;
    }

  std::string filename = argv[1];
  std::string parameterSet = argv[2];
  std::string reportName = argv[3];

  bool result = false;

  try
    {
      // load the model without progress report
      result = pDataModel->loadModel(filename, NULL);
    }
  catch (...)
    {
    }

  if (!result)
    {
      std::cerr << "Error while opening the file named \"" << filename << "\"." << std::endl;
      CRootContainer::destroy();
      return 1;
    }

  // changeParameters
  changeParametersFromIniFile(pDataModel, parameterSet);

  // change the filename
  CScanTask* scanTask = dynamic_cast<CScanTask*>(&(*pDataModel->getTaskList())["Scan"]);
  scanTask->getReport().setTarget(reportName);

  scanTask->setScheduled(true);

  // save to ensure that the model is right
  pDataModel->saveModel("temp.cps", NULL, true);


  // run the task
  try
    {
      scanTask->initialize(CCopasiTask::OUTPUT_SE, pDataModel, NULL);
      scanTask->process(true);
    }
  catch (...)
    {
      std::cerr << "Error. Running the scan failed." << std::endl;

      // check if there are additional error messages
      if (CCopasiMessage::size() > 0)
        {
          // print the messages in chronological order
          std::cerr << CCopasiMessage::getAllMessageText(true);
        }

      CRootContainer::destroy();
      return 1;
    }


  // clean up the library
  CRootContainer::destroy();
  return 0;
}
