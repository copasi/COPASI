/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiSE/CopasiSE.cpp,v $
   $Revision: 1.26.2.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/24 16:10:42 $
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

#include "copasilicense.h"
#include "copasiversion.h"

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiException.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CCopasiProblem.h"
#include "commandline/COptionParser.h"
#include "commandline/COptions.h"
#include "function/CFunctionDB.h"
#include "function/CEvaluationTree.h"
#include "function/CFunction.h"

#include "randomGenerator/CRandom.h"
#include "report/CCopasiTimer.h"
#include "report/CKeyFactory.h"
#include "utilities/CVersion.h"
#include "utilities/CDirEntry.h"
#include "utilities/CSparseMatrix.h"

int main(int argc, char *argv[])
{
  std::stringstream Out;
  std::stringstream Error;

#ifdef XXXX
  C_FLOAT64 sparseness = 0.00;
  SparseMatrixTest(10, sparseness);
  SparseMatrixTest(25, sparseness);
  SparseMatrixTest(50, sparseness);
  SparseMatrixTest(100, sparseness);
  SparseMatrixTest(250, sparseness);
  SparseMatrixTest(500, sparseness);
  SparseMatrixTest(1000, sparseness);

  return 0;
#endif // XXXX

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
          Out << "Usage: " << CDirEntry::baseName(argv[0]) << " [options] [file]\n";
          Out << e.what();
        }
    }

  catch (copasi::option_error &e)
    {
      Error << CDirEntry::baseName(argv[0]) << ": " << e.what() << "\n";
      Error << e.get_help_comment() << std::endl;
    }

  bool License;
  COptions::getValue("License", License);

  if (License)
    {
      std::cout << CopasiLicense << std::endl;
      return 0;
    }

  try
    {
      // Create the root container.
      CCopasiContainer::init();

      // Create the global data model.
      CCopasiDataModel::Global = new CCopasiDataModel;

      std::cout << "COPASI Version "
      << CCopasiDataModel::Global->getVersion()->getVersion()
      << std::endl << std::endl;

      if (Out.str() != "")
        {
          std::cout << Out.str();
          return 1;
        }

      if (Error.str() != "")
        {
          std::cerr << Error.str();
          return 1;
        }

#ifdef XXXX
      CCallParameters<C_FLOAT64> Variables(20);
      unsigned C_INT32 j, i, imax = Variables.size();
      CRandom * pRandom = CRandom::createGenerator();

      for (i = 0; i < imax; i++)
        {
          C_FLOAT64 * pValue = new C_FLOAT64;
          *pValue = 100.0 * pRandom->getRandomOO();
          Variables[i].value = pValue;
        }

      CCopasiTimer * pCPU =
        const_cast<CCopasiTimer *>(static_cast<const CCopasiTimer *>(CCopasiContainer::Root->getObject((std::string)"CN=Root,Timer=CPU Time")));
      CCopasiTimer * pWall =
        const_cast<CCopasiTimer *>(static_cast<const CCopasiTimer *>(CCopasiContainer::Root->getObject((std::string)"CN=Root,Timer=Wall Clock Time")));

      CCopasiVectorN< CEvaluationTree > & Functions =
        CCopasiDataModel::Global->getFunctionList()->loadedFunctions();
      CFunction * pFunction;

      for (i = 0, imax = Functions.size(); i < imax; i++)
        {
          pFunction = dynamic_cast<CFunction *>(Functions[i]);
          if (pFunction->getType() != CEvaluationTree::MassAction)
            for (j = 0; j < 100000; j++)
              pFunction->calcValue(Variables);
        }

      pCPU->actualize();
      pWall->actualize();

      std::cout << "CPU time:  ";
      pCPU->print(&std::cout);
      std::cout << std::endl;

      std::cout << "Wall time: ";
      pWall->print(&std::cout);
      std::cout << std::endl;
#endif // XXXX

#ifdef XXXX
      CEvaluationTree Expression;
      Expression.setInfix("5**-sin(x)");
      Expression.setInfix("a*5.0/-b");
      Expression.setInfix("EXPONENTIALE+b*c");
      Expression.setInfix("4.0*\"PI+b");
      Expression.setInfix("2*(3+b)");
#endif

      const COptions::nonOptionType & Files = COptions::getNonOptions();

      if (!COptions::compareValue("ImportSBML", std::string("")))
        {
          // Import the SBML File
          std::string ImportSBML;
          COptions::getValue("ImportSBML", ImportSBML);
          CCopasiDataModel::Global->importSBML(ImportSBML);

          // Check whether exporting to SBML is requested.
          if (!COptions::compareValue("ExportSBML", std::string("")))
            {
              // Export the SBML File
              std::string ExportSBML;
              COptions::getValue("ExportSBML", ExportSBML);
              CCopasiDataModel::Global->exportSBML(ExportSBML, true);
            }

          // Check whether a save file is given.
          if (!COptions::compareValue("Save", std::string("")))
            {
              std::string Save;
              COptions::getValue("Save", Save);

              CCopasiDataModel::Global->saveModel(Save, true);
            }

          // If no export or save file was given, we write to the
          // default file, but do not overwrite any existing file.
          if (COptions::compareValue("ExportSBML", std::string("")) &&
              COptions::compareValue("Save", std::string("")))
            CCopasiDataModel::Global->saveModel("", false);
        }
      else
        {
          COptions::nonOptionType::const_iterator it = Files.begin();
          COptions::nonOptionType::const_iterator end = Files.end();

          if (it == end) // Create a usage message
            {
              std::string Help = "--help";
              const char * Argv[2];
              Argv[0] = argv[0];
              Argv[1] = Help.c_str();

              copasi::COptionParser * pParser = new copasi::COptionParser;
              try
                {
                  pParser->parse(2, (char **) Argv);
                }

              catch (copasi::autoexcept &e)
                {
                  switch (e.get_autothrow_id())
                    {
                    case copasi::autothrow_help:
                      std::cout << "Usage: " << CDirEntry::baseName(argv[0]) << " [options] [file]\n";
                      std::cout << e.what();
                    }
                }

              return 1;
            }

          for (; it != end; ++it)
            {
              CCopasiDataModel::Global->loadModel(*it);

              // Check whether exporting to SBML is requested.
              if (!COptions::compareValue("ExportSBML", std::string("")))
                {
                  // Export the SBML File
                  std::string ExportSBML;
                  COptions::getValue("ExportSBML", ExportSBML);
                  CCopasiDataModel::Global->exportSBML(ExportSBML, true);

                  // Since only one export file name can be specified we
                  // stop execution.
                  break;
                }

              CCopasiVectorN< CCopasiTask > & TaskList = * CCopasiDataModel::Global->getTaskList();
              unsigned C_INT32 i, imax = TaskList.size();

              for (i = 0; i < imax; i++)
                if (TaskList[i]->isScheduled())
                  {
                    TaskList[i]->getProblem()->setModel(CCopasiDataModel::Global->getModel());

                    TaskList[i]->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL);
                    TaskList[i]->process(true);
                    TaskList[i]->restore();
                  }

              // Check whether a file for saving the resulting model is given
              if (!COptions::compareValue("Save", std::string("")))
                {
                  std::string Save;
                  COptions::getValue("Save", Save);
                  CCopasiDataModel::Global->saveModel(Save, true);

                  // Since only one save file name can be specified we
                  // stop execution.
                  break;
                }
            }
        }
    }

  catch (CCopasiException Exception)
    {
      std::cout << Exception.getMessage().getText() << std::endl;
    }

  pdelete(CCopasiDataModel::Global);
  pdelete(CCopasiContainer::Root);

  //std::cout << "Leaving main program." << std::endl;
  return 0;
}
