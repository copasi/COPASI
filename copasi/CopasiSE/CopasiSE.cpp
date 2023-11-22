// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// Main
//
// (C) Stefan Hoops 2002
//

#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>

#define COPASI_MAIN

#include "copasi/copasi.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/commandline/COptionParser.h"
#include "copasi/commandline/COptions.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CFunction.h"

#include "copasi/randomGenerator/CRandom.h"
#include "copasi/core/CDataTimer.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/CVersion.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasi/utilities/CSparseMatrix.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/sedml/SEDMLUtils.h"

#include "copasi/OpenMP/CContext.h"

#define OPERATION_SUCCEDED 0
#define OPERATION_FAILED 1
#define NO_EXPORT_REQUESTED 2
#define CONTINUE_IMPORT 3

void writeLogo();
int validate();
int main(int argc, char * argv[]);
int printUsage(const std::string & name);
int exportSBML();
int exportCurrentModel();
int runScheduledTasks(CProcessReport * pProcessReport);
int saveCurrentModel();
int exportParametersToIniFile();

CDataModel* pDataModel = NULL;
bool Validate = false;
bool Verbose;
std::string ReportFileName;
std::string ScheduledTask;
std::string SedmlTask;
bool PrintSedMLTasks;

SedmlImportOptions getSedmlImportOptions(SedmlInfo& info, int& retcode)
{
  SedmlImportOptions options;

  if (PrintSedMLTasks)
    {
      std::cout << "SED-ML Tasks:" << std::endl;

      for (auto & entry : info.getTaskNames())
        {
          std::cout << std::endl;
          std::cout << "Id:\t" << entry.first << std::endl;
          std::cout << "Name:\t" << entry.second << std::endl;
        }

      retcode = OPERATION_SUCCEDED;
      return options;
    }

  if (SedmlTask.empty())
    SedmlTask = info.getFirstTaskWithOutput();

  if (info.getModelForTask(SedmlTask).empty())
    {
      std::cerr << "Invalid SED-ML task: " << SedmlTask << std::endl;
      retcode = OPERATION_FAILED;
      return options;
    }

  retcode = CONTINUE_IMPORT;

  std::vector< std::string > plots;

  for (auto & entry : info.getPlotsForTask(SedmlTask))
    plots.push_back(entry.first);

  options = SedmlImportOptions(
              SedmlTask, info.getFirstModel(SedmlTask),
              plots,
              info.getFirstReport(SedmlTask),
              ReportFileName
            );

  if (Verbose)
    {
      std::cout << "Importing SED-ML with options: " << std::endl;
      std::cout << "  task:   " << SedmlTask << std::endl;
      std::cout << "  model:  " << options.getModelId() << std::endl;
      std::cout << "  report: " << options.getReportId() << std::endl;
      std::cout << "  file:   " << options.getReportFile() << std::endl;

      std::cout << std::endl;
    }

  return options;
}

SedmlImportOptions getSedmlImportOptions(
  const std::string& sedmlFile, int& retcode)
{
  auto info = SedmlInfo::forFile(sedmlFile);
  return getSedmlImportOptions(info, retcode);
}

SedmlImportOptions getSedmlImportOptionsForArchive(
  const std::string & combineArchive,
  int & retcode)
{
  auto info = SedmlInfo::forArchive(combineArchive);
  return getSedmlImportOptions(info, retcode);
}

int main(int argc, char *argv[])
{
  int retcode = 0;
  CProcessReport * pProcessReport = NULL;
  int MaxTime = 0;

#ifdef XXXX
  C_FLOAT64 sparseness = 0.00;
  SparseMatrixTest(10, sparseness, 0, false, true, true, false);
  SparseMatrixTest(25, sparseness, 0, false, true, true, false);
  SparseMatrixTest(50, sparseness, 0, false, true, true, false);
  SparseMatrixTest(100, sparseness, 0, false, true, true, false);
  SparseMatrixTest(250, sparseness, 0, false, true, true, false);
  SparseMatrixTest(500, sparseness, 0, false, true, true, false);
  SparseMatrixTest(1000, sparseness, 0, false, true, true, false);
  SparseMatrixTest(2500, sparseness, 0, false, true, true, false);
  SparseMatrixTest(5000, sparseness, 0, false, true, true, false);

  return 0;
#endif // XXXX

  try
    {
      // Create the root container.
      CRootContainer::init(argc, argv);
    }

  catch (copasi::autoexcept &e)
    {
      writeLogo();

      switch (e.get_autothrow_id())
        {
          case copasi::autothrow_help:
            std::cerr << "Usage: " << CDirEntry::baseName(argv[0]) << " [options] [file]\n";
            std::cerr << e.what();
            break;
        }

      retcode = 0;
      goto finish;
    }

  catch (copasi::option_error &e)
    {
      writeLogo();
      std::cerr << CDirEntry::baseName(argv[0]) << ": " << e.what() << "\n";
      std::cerr << e.get_help_comment() << std::endl;

      retcode = 1;
      goto finish;
    }

  writeLogo();

  bool License;
  COptions::getValue("License", License);

  COptions::getValue("ReportFile", ReportFileName);
  COptions::getValue("ScheduledTask", ScheduledTask);
  COptions::getValue("SedmlTask", SedmlTask);
  COptions::getValue("PrintSedMLTasks", PrintSedMLTasks);
  COptions::getValue("Verbose", Verbose);

  if (License)
    {
      std::cout << CRootContainer::getLicenseTxt() << std::endl;

      retcode = 0;
      goto finish;
    }

  COptions::getValue("MaxTime", MaxTime);

  if (MaxTime > 0)
    {
      pProcessReport = new CProcessReport(MaxTime);
    }

  try
    {
      // Create the global data model.
      pDataModel = CRootContainer::addDatamodel();
      assert(pDataModel != NULL);

#ifdef XXXX
      CCallParameters<C_FLOAT64> Variables(20);
      size_t j, i, imax = Variables.size();
      CRandom * pRandom = CRandom::createGenerator();

      for (i = 0; i < imax; i++)
        {
          C_FLOAT64 * pValue = new C_FLOAT64;
          *pValue = 100.0 * pRandom->getRandomOO();
          Variables[i].value = pValue;
        }

      CCopasiTimer * pCPU =
        const_cast<CCopasiTimer *>(static_cast<const CCopasiTimer *>(CRootContainer::getObject((std::string)"CN=Root,Timer=CPU Time")));
      CCopasiTimer * pWall =
        const_cast<CCopasiTimer *>(static_cast<const CCopasiTimer *>(CRootContainer::getObject((std::string)"CN=Root,Timer=Wall Clock Time")));

      CDataVectorN< CEvaluationTree > & Functions =
        CRootContainer::getFnctionList()->loadedFunctions();
      CFunction * pFunction;

      for (i = 0, imax = Functions.size(); i < imax; i++)
        {
          pFunction = dynamic_cast<CFunction *>(Functions[i]);

          if (pFunction->getType() != CEvaluationTree::MassAction)
            for (j = 0; j < 100000; j++)
              pFunction->calcValue(Variables);
        }

      pCPU->refresh();
      pWall->refresh();
#endif // XXXX

      // Check whether we just have to validate
      COptions::getValue("Validate", Validate);

      bool ConvertToIrreversible;
      COptions::getValue("ConvertToIrreversible", ConvertToIrreversible);

      const COptions::nonOptionType & Files = COptions::getNonOptions();

      bool importSBML = COptions::isSet("ImportSBML") && !COptions::compareValue("ImportSBML", std::string(""));
      bool importSEDML = COptions::isSet("ImportSEDML") && !COptions::compareValue("ImportSEDML", std::string(""));
      bool importCA = COptions::isSet("ImportCombineArchive") && !COptions::compareValue("ImportCombineArchive", std::string(""));
      bool needImport = importSBML | importSEDML | importCA;

      std::string iniFileName;

      if (COptions::isSet("ReparameterizeModel") && !COptions::compareValue("ReparameterizeModel", std::string("")))
        COptions::getValue("ReparameterizeModel", iniFileName);

      if (needImport)
        {
          if (importSBML)
            {
              // Import the SBML File
              std::string ImportSBML;
              COptions::getValue("ImportSBML", ImportSBML);

              if (!pDataModel->importSBML(ImportSBML))
                {
                  std::cerr << "SBML Import File: " << ImportSBML << std::endl;
                  std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

                  retcode = 1;
                  goto finish;
                }
            }

          else if (importSEDML)
            {
              // Import the SED-ML File
              std::string ImportSEDML;
              COptions::getValue("ImportSEDML", ImportSEDML);

              SedmlImportOptions options = getSedmlImportOptions(ImportSEDML, retcode);

              if (retcode != CONTINUE_IMPORT)
                {
                  goto finish;
                }

              retcode = 0;

              if (!pDataModel->importSEDML(ImportSEDML, NULL, true, &options))
                {
                  std::cerr << "SED-ML Import File: " << ImportSEDML << std::endl;
                  std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

                  retcode = 1;
                  goto finish;
                }
            }

          else if (importCA)
            {
              // Import the SED-ML File
              std::string ImportCombineArchive;
              COptions::getValue("ImportCombineArchive", ImportCombineArchive);

              SedmlImportOptions options = getSedmlImportOptionsForArchive(ImportCombineArchive, retcode);

              if (retcode != CONTINUE_IMPORT)
                {
                  goto finish;
                }

              retcode = 0;

              if (!pDataModel->openCombineArchive(ImportCombineArchive, NULL, true, &options))
                {
                  std::cerr << "CombineArchive Import File: " << ImportCombineArchive << std::endl;
                  std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

                  retcode = 1;
                  goto finish;
                }
            }

          else
            {
              std::cerr << "Unsupported Import operation" << std::endl;
              retcode = 1;
              goto finish;
            }

          // Validate and exit
          if (Validate)
            {
              retcode = validate();
              goto finish;
            }

          if (ConvertToIrreversible)
            {
              pDataModel->getModel()->convert2NonReversible();
              pDataModel->getModel()->compileIfNecessary(NULL);
            }

          if (!iniFileName.empty())
            pDataModel->reparameterizeFromIniFile(iniFileName);

          retcode = exportCurrentModel();

          if (retcode != NO_EXPORT_REQUESTED)
            {
              // Since only one export file name can be specified
              // for export we stop execution.
              exportParametersToIniFile();
              goto finish;
            }

          // combine archives or SED-ML will have defined tasks
          retcode = runScheduledTasks(pProcessReport);

          exportParametersToIniFile();

          // If no export file was given, we write to the save file or
          // the default file.
          if (COptions::compareValue("ExportSBML", std::string("")))
            {
              retcode = saveCurrentModel();
              goto finish;
            }
        }
      else
        {
          COptions::nonOptionType::const_iterator it = Files.begin();
          COptions::nonOptionType::const_iterator end = Files.end();

          if (it == end) // Create a usage message
            {
              retcode = printUsage(argv[0]);
              goto finish;
            }

          for (; it != end; ++it)
            {
              if (!pDataModel->loadFromFile(*it, NULL))
                {
                  std::cerr << "File: " << *it << std::endl;
                  std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

                  retcode = 1;
                  continue;
                }

              // Validate and exit
              if (Validate)
                {
                  retcode |= validate();
                  continue;
                }

              if (ConvertToIrreversible)
                {
                  pDataModel->getModel()->convert2NonReversible();
                  pDataModel->getModel()->compileIfNecessary(NULL);
                }

              if (!iniFileName.empty())
                pDataModel->reparameterizeFromIniFile(iniFileName);

              retcode = exportCurrentModel();

              if (retcode != NO_EXPORT_REQUESTED)
                {
                  // Since only one export file name can be specified
                  // for export we stop execution.
                  exportParametersToIniFile();
                  break;
                }

              retcode = runScheduledTasks(pProcessReport);

              exportParametersToIniFile();

              // Check whether a file for saving the resulting model is given
              if (!COptions::compareValue("Save", std::string("")))
                {
                  retcode = saveCurrentModel();

                  // Since only one save file name can be specified we
                  // stop execution.
                  break;
                }
            }
        }
    }

  catch (CCopasiException & Exception)
    {
      std::cerr << "Unhandled Exception:" << std::endl;
      std::cerr << Exception.getMessage().getText() << std::endl;
    }

finish:
  CRootContainer::destroy();
  pdelete(pProcessReport);

  return retcode;
}

int printUsage(const std::string& name)
{
  std::string Self;
  COptions::getValue("Self", Self);

  char * Argv[2];
  Argv[0] = strdup(Self.c_str());
  Argv[1] = strdup("--help");

  copasi::COptionParser Parser;

  try
    {
      Parser.parse(2, Argv);
    }

  catch (copasi::autoexcept &e)
    {
      switch (e.get_autothrow_id())
        {
          case copasi::autothrow_help:
            std::cerr << "Usage: " << CDirEntry::baseName(name) << " [options] [file]\n";
            std::cerr << e.what();
            break;
        }
    }

  return 1;
}

int runScheduledTasks(CProcessReport * pProcessReport)
{
  int retcode = 0;

  if (pDataModel == NULL)
    return 0;

  CDataVectorN< CCopasiTask > & TaskList = *pDataModel->getTaskList();
  size_t imax = TaskList.size();

  if (!ScheduledTask.empty())
    {
      if (TaskList.getIndex(ScheduledTask) == C_INVALID_INDEX)
        {
          std::cerr << "No task '" << ScheduledTask << "' to be marked executable"
                    << std::endl << std::endl;
          return 1;
        }

      // mark all other potential tasks as not scheduled
      for (CCopasiTask & task : TaskList)
        {
          task.setScheduled(false);
        }

      CCopasiTask& toBeScheduled = TaskList[ScheduledTask];
      toBeScheduled.setScheduled(true);

      if (!COptions::compareValue("Save", std::string("")))
        toBeScheduled.setUpdateModel(true);
    }

  for (CCopasiTask & task : TaskList)
    if (task.isScheduled())
      {
        task.setCallBack(pProcessReport);

        bool success = true;

        if (!ReportFileName.empty())
          {
            task.getReport().setTarget(ReportFileName);
          }

        try
          {
            success = task.initialize(CCopasiTask::OUTPUT_UI, pDataModel, NULL);

            // We need to check whether the result is saved in any form.
            // If not we need to stop right here to avoid wasting time.
            if (CCopasiMessage::checkForMessage(MCCopasiTask + 5) &&
                (!task.isUpdateModel() ||
                 COptions::compareValue("Save", std::string(""))))
              {
                success = false;
              }

            if (success)
              success &= task.process(true);
          }

        catch (...)
          {
            success = false;
          }

        task.restore();

        if (!success)
          {
            std::cerr << "File: " << pDataModel->getFileName() << std::endl;
            std::cerr << "Task: " << task.getObjectName() << std::endl;
            std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

            retcode = 1;
          }

        if (pProcessReport != NULL)
          {
            pProcessReport->finish();
          }

        task.setCallBack(NULL);
        pDataModel->finish();
      }

  return retcode;
}

int exportParametersToIniFile()
{
  int retcode = 0;
  std::string exportIni;

  if (COptions::isSet("ExportIni") && !COptions::compareValue("ExportIni", std::string("")))
    COptions::getValue("ExportIni", exportIni);

  if (exportIni.empty())
    return retcode;

  std::ofstream fs(CLocaleString::fromUtf8(exportIni).c_str());

  if (!fs.good()) return -1;

  if (!pDataModel || !pDataModel->getModel()) return -2;

  pDataModel->getModel()->getActiveModelParameterSet().
  saveToStream(fs, CCore::Framework::Concentration, "ini", "");

  fs.close();

  return retcode;
}

int exportCurrentModel()
{
  int retcode = 0;

  // Check whether exporting to SBML is requested.
  if (!COptions::compareValue("ExportSBML", std::string("")))
    {
      retcode = exportSBML();

      return retcode;
    }

  // Check whether exporting to C code is requested.
  if (!COptions::compareValue("ExportC", std::string("")))
    {
      // Export the C code File
      std::string ExportC;
      COptions::getValue("ExportC", ExportC);

      if (!pDataModel->exportMathModel(ExportC, NULL, "C Files (*.c)", true))
        {
          std::cerr << "C File: " << ExportC << std::endl;
          std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

          retcode = 1;
        }

      return retcode;
    }

  // Check whether exporting to Berkeley Madonna is requested.
  if (!COptions::compareValue("ExportBerkeleyMadonna", std::string("")))
    {
      // Export the Berkeley Madonna File
      std::string ExportBerkeleyMadonna;
      COptions::getValue("ExportBerkeleyMadonna", ExportBerkeleyMadonna);

      if (!pDataModel->exportMathModel(ExportBerkeleyMadonna, NULL, "Berkeley Madonna Files (*.mmd)", true))
        {
          std::cerr << "Berkeley Madonna File: " << ExportBerkeleyMadonna << std::endl;
          std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

          retcode = 1;
        }

      return retcode;
    }

  // Check whether exporting to XPPAUT is requested.
  if (!COptions::compareValue("ExportXPPAUT", std::string("")))
    {
      // Export the XPPAUT File
      std::string ExportXPPAUT;
      COptions::getValue("ExportXPPAUT", ExportXPPAUT);

      if (!pDataModel->exportMathModel(ExportXPPAUT, NULL, "XPPAUT (*.ode)", true))
        {
          std::cerr << "XPPAUT File: " << ExportXPPAUT << std::endl;
          std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

          retcode = 1;
        }

      return retcode;
    }

  // Check whether exporting to SEDML is requested.
  if (!COptions::compareValue("ExportSEDML", std::string("")))
    {
      // Export the SEDML File
      std::string ExportSEDML;
      COptions::getValue("ExportSEDML", ExportSEDML);

      if (!pDataModel->exportSEDML(ExportSEDML, true, 1, 2, true))
        {
          std::cerr << "SED-ML File: " << ExportSEDML << std::endl;
          std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

          retcode = 1;
        }
    }

  // Check whether exporting to Combine Archive is requested.
  if (!COptions::compareValue("ExportCombineArchive", std::string("")))
    {
      // Export the Combine Archive File
      std::string ExportCombineArchive;
      COptions::getValue("ExportCombineArchive", ExportCombineArchive);

      if (!pDataModel->exportCombineArchive(ExportCombineArchive, true,
                                            true,
                                            true,
                                            true,
                                            true))
        {
          std::cerr << "Combine Archive File: " << ExportCombineArchive << std::endl;
          std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

          retcode = 1;
        }
    }

  return NO_EXPORT_REQUESTED;
}

int saveCurrentModel()
{
  int retcode = 0;

  std::string Save;
  COptions::getValue("Save", Save);

  if (Save.empty())
    return retcode;

  if (!pDataModel->saveModel(Save, NULL, true))
    {
      std::cerr << "Save File: " << pDataModel->getFileName() << std::endl;
      std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

      retcode = OPERATION_FAILED;
    }

  return retcode;
}

void writeLogo()
{
  bool NoLogo = false;
  COptions::getValue("NoLogo", NoLogo);

  if (NoLogo) return;

  std::cout << "COPASI "
            << CVersion::VERSION.getVersion() <<  omp_info()() << std::endl
            << "The use of this software indicates the acceptance of the attached license." << std::endl
            << "To view the license please use the option: --license" << std::endl
            << std::endl;
}

int validate()
{
  int retcode = 0;

  // We are already sure that the COPASI model compiled. That means
  // we only need to test the active tasks
  CDataVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();
  size_t i, imax = TaskList.size();

  for (i = 0; i < imax; i++)
    if (TaskList[i].isScheduled())
      {
        bool success = true;

        try
          {
            success =
              TaskList[i].initialize(CCopasiTask::OUTPUT_SE, pDataModel, NULL);

            // We need to check whether the result is saved in any form.
            // If not we need to stop right here to avoid wasting time.
            if (CCopasiMessage::checkForMessage(MCCopasiTask + 5) &&
                (!TaskList[i].isUpdateModel() ||
                 COptions::compareValue("Save", std::string(""))))
              success = false;
          }

        catch (...)
          {
            success = false;
          }

        TaskList[i].restore();

        if (!success)
          {
            std::cerr << "File: " << pDataModel->getFileName() << std::endl;
            std::cerr << "Task: " << TaskList[i].getObjectName() << std::endl;
            std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

            retcode = 1;
          }

        pDataModel->finish();
      }

  return retcode;
}

int exportSBML()
{
  int retcode = 0;

  // Export the SBML File
  std::string ExportSBML;
  COptions::getValue("ExportSBML", ExportSBML);
  copasi::SBMLSchema_enum SBMLSchema;
  COptions::getValue("SBMLSchema", SBMLSchema);

  int Level;
  int Version;

  switch (SBMLSchema)
    {
      case copasi::SBMLSchema_L1V1:
        Level = 1;
        Version = 1;
        break;

      case copasi::SBMLSchema_L1V2:
        Level = 1;
        Version = 2;
        break;

      case copasi::SBMLSchema_L2V1:
        Level = 2;
        Version = 1;
        break;

      case copasi::SBMLSchema_L2V2:
        Level = 2;
        Version = 2;
        break;

      case copasi::SBMLSchema_L2V3:
        Level = 2;
        Version = 3;
        break;

      case copasi::SBMLSchema_L2V4:
        Level = 2;
        Version = 4;
        break;

      case copasi::SBMLSchema_L2V5:
        Level = 2;
        Version = 5;
        break;

      case copasi::SBMLSchema_L3V1:
        Level = 3;
        Version = 1;
        break;

      case copasi::SBMLSchema_L3V2:
        Level = 3;
        Version = 2;
        break;

      default:
        Level = 2;
        Version = 4;
        break;
    }

  if (!pDataModel->exportSBML(ExportSBML, true, Level, Version))
    {
      std::cerr << "SBML Export File: " << ExportSBML << std::endl;
      std::cerr << CCopasiMessage::getAllMessageText() << std::endl;
      retcode = 1;
    }

  return retcode;
}
