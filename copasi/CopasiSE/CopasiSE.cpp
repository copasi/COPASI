/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiSE/CopasiSE.cpp,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/09 13:32:11 $
   End CVS Header */

// Main
//
// (C) Stefan Hoops 2002
//

#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>

#define COPASI_MAIN
#define COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiException.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CCopasiProblem.h"
#include "commandline/COptionParser.h"
#include "commandline/COptions.h"
#include "function/CFunctionDB.h"

int main(int argc, char *argv[])
{
  try
    {
      // Parse the commandline options
      COptions::init(argc, argv);
    }

  catch (copasi::autoexcept &e)
    {
      switch (e.get_autothrow_id())
        {
        case copasi::autothrow_help:
          std::cout << "Usage: " << argv[0] << " [options]\n";
          std::cout << e.what();
        }

      return 1;
    }

  catch (copasi::option_error &e)
    {
      std::cerr << argv[0] << ": " << e.what() << "\n";
      std::cerr << e.get_help_comment() << std::endl;

      return 1;
    }

  try
    {
      // Create the root container.
      CCopasiContainer::init();

      // Create the global data model.
      CCopasiDataModel::Global = new CCopasiDataModel;

      const COptions::nonOptionType & Files = COptions::getNonOptions();

      if (!COptions::compareValue("ImportSBML", std::string("")))
        {
          // Import the SBML File
          std::string ImportSBML;
          COptions::getValue("ImportSBML", ImportSBML);
          CCopasiDataModel::Global->importSBML(ImportSBML);

          // Save the COPASI File, which is the only thing to do.
          std::string Save;
          COptions::getValue("Save", Save);
          CCopasiDataModel::Global->saveModel(Save);
        }

      COptions::nonOptionType::const_iterator it = Files.begin();
      COptions::nonOptionType::const_iterator end = Files.end();

      for (; it != end; ++it)
        {
          CCopasiDataModel::Global->loadModel(*it);

          // Check whether exporting to SBML is requested.
          if (!COptions::compareValue("ExportSBML", std::string("")))
            {
              // Export the SBML File
              std::string ExportSBML;
              COptions::getValue("ExportSBML", ExportSBML);
              CCopasiDataModel::Global->exportSBML(ExportSBML);

              // Since only one export file name can be specified we
              // stop execution.
              return 0;
            }

          CCopasiVectorN< CCopasiTask > & TaskList = * CCopasiDataModel::Global->getTaskList();
          unsigned C_INT32 i, imax = TaskList.size();

          for (i = 0; i < imax; i++)
            if (TaskList[i]->isScheduled())
              {
                TaskList[i]->getProblem()->setModel(CCopasiDataModel::Global->getModel());

                TaskList[i]->initialize();
                TaskList[i]->process();
                TaskList[i]->restore();
              }

          // Check whether a file for saving the resulting model is given
          if (!COptions::compareValue("Save", std::string("")))
            {
              std::string Save;
              COptions::getValue("Save", Save);
              CCopasiDataModel::Global->saveModel(Save);

              // Since only one save file name can be specified we
              // stop execution.
              return 0;
            }

          //      CCopasiDataModel::Global->saveModel("");
        }
    }

  catch (CCopasiException Exception)
    {
      std::cout << Exception.getMessage().getText() << std::endl;
    }

  pdelete(CCopasiDataModel::Global);
  pdelete(CCopasiContainer::Root);

  std::cout << "Leaving main program." << std::endl;
  return 0;
}
