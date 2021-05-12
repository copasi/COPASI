// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * This examples demonstrates how to rad in a copasi file, and
 * change the filename of the first active report. This is often
 * useful when running a task multiple times.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define COPASI_MAIN

#include <copasi/CopasiTypes.h>

using namespace std;

int main(int argc, char** argv)
{
  // initialize COPASI
  CRootContainer::init(0, NULL);

  // create a data model
  CDataModel* pDataModel = CRootContainer::addDatamodel();

  // accept at least two arguments, the COPASI file and the new report filename
  // if a third argument is given, that will be the output file.
  if (argc < 3)
    {
      std::cerr << "Usage: renameActiveReport <copasi file> <report filename> [<output copasi file>]" << std::endl;
      CRootContainer::destroy();
      return 1;
    }

  std::string filename = argv[1];
  std::string reportFileName = argv[2];
  std::string outputFile = argc > 3 ? argv[3] : argv[1];

  bool result = true;

  try
    {
      // load the model without progress report
      result = pDataModel->loadFromFile(filename);
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

  CDataVectorN< CCopasiTask >& tasks = *pDataModel->getTaskList();
  CDataVectorN< CCopasiTask >::iterator it = tasks.begin();
  CDataVectorN< CCopasiTask >::iterator end = tasks.end();

  for (; it != end; ++it)
    {
      if (!it->isScheduled())
        continue;

      it->getReport().setTarget(reportFileName);
      break;
    }

  // save to ensure that the model is right
  pDataModel->saveModel(outputFile, NULL, true);

  // clean up the library
  CRootContainer::destroy();
}
