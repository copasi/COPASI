// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiSE/CopasiSE.cpp,v $
//   $Revision: 1.51 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/04/01 15:06:44 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
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

#ifdef COPASI_LICENSE_COM
# include "commandline/CConfigurationFile.h"
# include "commercial/CRegistration.h"
#endif // COPASI_LICENSE_COM

void writeLogo();
int validate();
int exportSBML();

int main(int argc, char *argv[])
{
  int retcode = 0;

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
      CCopasiRootContainer::init(argc, argv);
    }

  catch (copasi::autoexcept &e)
    {
      writeLogo();

      switch (e.get_autothrow_id())
        {
          case copasi::autothrow_help:
            std::cerr << "Usage: " << CDirEntry::baseName(argv[0]) << " [options] [file]\n";
            std::cerr << e.what();
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

  if (License)
    {
      std::cout << CCopasiRootContainer::getLicenseTxt() << std::endl;

      retcode = 0;
      goto finish;
    }

  try
    {
      // Create the global data model.
      CCopasiDataModel* pDataModel = CCopasiRootContainer::addDatamodel();
      assert(pDataModel != NULL);

#ifdef COPASI_LICENSE_COM
      CRegistration * pRegistration =
        elevate< CRegistration, CCopasiParameterGroup >(CCopasiRootContainer::getConfiguration()->assertGroup("Registration"));

      bool RegistrationChanged = false;
      std::string RegistrationValue;

      if (!COptions::compareValue("RegistrationCode", std::string("")))
        {
          COptions::getValue("RegistrationCode", RegistrationValue);
          pRegistration->setRegistrationCode(RegistrationValue);
          RegistrationChanged = true;
        }

      if (!COptions::compareValue("RegisteredEmail", std::string("")))
        {
          COptions::getValue("RegisteredEmail", RegistrationValue);
          pRegistration->setRegisteredEmail(RegistrationValue);
          RegistrationChanged = true;
        }

      if (!COptions::compareValue("RegisteredUser", std::string("")))
        {
          COptions::getValue("RegisteredUser", RegistrationValue);
          pRegistration->setRegisteredUser(RegistrationValue);
          RegistrationChanged = true;
        }

      if (!RegistrationChanged && !pRegistration->isValidSignature())
        {
          std::cerr << "No license registration." << std::endl;
          std::cerr << "Please add the following arguments to CopasiSE:" << std::endl;
          std::cerr << "   --rUser <Your Name as in registration.>" << std::endl;
          std::cerr << "   --rEmail <Your Email as in registration.>" << std::endl;
          std::cerr << "   --rCode <Your Registration Code.>" << std::endl;

          retcode = 1;
          goto finish;
        }

      if (!pRegistration->isValidRegistration())
        {
          std::cerr << "Invalid license registration." << std::endl;
          std::cerr << CCopasiMessage::getLastMessage().getText() << std::endl;
          std::cerr << "To correct the problem please add one or more of the" << std::endl;
          std::cerr << "following arguments to CopasiSE:" << std::endl;
          std::cerr << "   --rUser <Your Name as in registration.>" << std::endl;
          std::cerr << "   --rEmail <Your Email as in registration.>" << std::endl;
          std::cerr << "   --rCode <Your Registration Code.>" << std::endl;

          retcode = 1;
          goto finish;
        }

#endif // COPASI_LICENSE_COM

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
        const_cast<CCopasiTimer *>(static_cast<const CCopasiTimer *>(CCopasiRootContainer::getObject((std::string)"CN=Root,Timer=CPU Time")));
      CCopasiTimer * pWall =
        const_cast<CCopasiTimer *>(static_cast<const CCopasiTimer *>(CCopasiRootContainer::getObject((std::string)"CN=Root,Timer=Wall Clock Time")));

      CCopasiVectorN< CEvaluationTree > & Functions =
        CCopasiRootContainer::getFnctionList()->loadedFunctions();
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
      bool Validate = false;
      COptions::getValue("Validate", Validate);

      const COptions::nonOptionType & Files = COptions::getNonOptions();

      if (!COptions::compareValue("ImportSBML", std::string("")))
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

          // Validate and exit
          if (Validate)
            {
              retcode = validate();
              goto finish;
            }

          // Check whether exporting to SBML is requested.
          if (!COptions::compareValue("ExportSBML", std::string("")))
            {
              retcode = exportSBML();
              goto finish;
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

              goto finish;
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

              goto finish;
            }

          // Check whether exporting to XPPAUT is requested.
          if (!COptions::compareValue("ExportXPPAUT", std::string("")))
            {
              // Export the Berkeley Madonna File
              std::string ExportXPPAUT;
              COptions::getValue("ExportXPPAUT", ExportXPPAUT);

              if (!pDataModel->exportMathModel(ExportXPPAUT, NULL, "XPPAUT (*.ode)", true))
                {
                  std::cerr << "XPPAUT File: " << ExportXPPAUT << std::endl;
                  std::cerr << CCopasiMessage::getAllMessageText() << std::endl;
                  retcode = 1;
                }

              goto finish;
            }

          // If no export file was given, we write to the save file or
          // the default file.
          if (COptions::compareValue("ExportSBML", std::string("")))
            {
              std::string Save;
              COptions::getValue("Save", Save);

              if (!pDataModel->saveModel(Save, NULL, true))
                {
                  assert(CCopasiRootContainer::getDatamodelList()->size() != 0);
                  std::cerr << "Save File: " << pDataModel->getFileName() << std::endl;
                  std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

                  retcode = 1;
                  goto finish;
                }
            }
        }
      else
        {
          COptions::nonOptionType::const_iterator it = Files.begin();
          COptions::nonOptionType::const_iterator end = Files.end();

          if (it == end) // Create a usage message
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
                        std::cerr << "Usage: " << CDirEntry::baseName(argv[0]) << " [options] [file]\n";
                        std::cerr << e.what();
                    }
                }

              retcode = 1;
              goto finish;
            }

          for (; it != end; ++it)
            {
              if (!pDataModel->loadModel(*it, NULL))
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

              // Check whether exporting to SBML is requested.
              if (!COptions::compareValue("ExportSBML", std::string("")))
                {
                  retcode = exportSBML();

                  // Since only one export file name can be specified we
                  // stop execution.
                  break;
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

                  // Since only one export file name can be specified we
                  // stop execution.
                  break;
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

                  // Since only one export file name can be specified we
                  // stop execution.
                  break;
                }

              // Check whether exporting to XPPAUT is requested.
              if (!COptions::compareValue("ExportXPPAUT", std::string("")))
                {
                  // Export the Berkeley Madonna File
                  std::string ExportXPPAUT;
                  COptions::getValue("ExportXPPAUT", ExportXPPAUT);

                  if (!pDataModel->exportMathModel(ExportXPPAUT, NULL, "XPPAUT (*.ode)", true))
                    {
                      std::cerr << "XPPAUT File: " << ExportXPPAUT << std::endl;
                      std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

                      retcode = 1;
                    }

                  // Since only one export file name can be specified we
                  // stop execution.
                  break;
                }

              CCopasiVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();
              size_t i, imax = TaskList.size();

              for (i = 0; i < imax; i++)
                if (TaskList[i]->isScheduled())
                  {
                    TaskList[i]->getProblem()->setModel(pDataModel->getModel());

                    bool success = true;

                    try
                      {
                        success = TaskList[i]->initialize(CCopasiTask::OUTPUT_SE, pDataModel, NULL);

                        // We need to check whether the result is saved in any form.
                        // If not we need to stop right here to avoid wasting time.
                        if (CCopasiMessage::checkForMessage(MCCopasiTask + 5) &&
                            (!TaskList[i]->isUpdateModel() ||
                             COptions::compareValue("Save", std::string(""))))
                          {
                            success = false;
                          }

                        if (success)
                          success &= TaskList[i]->process(true);
                      }

                    catch (...)
                      {
                        success = false;
                      }

                    TaskList[i]->restore();

                    if (!success)
                      {
                        std::cerr << "File: " << pDataModel->getFileName() << std::endl;
                        std::cerr << "Task: " << TaskList[i]->getObjectName() << std::endl;
                        std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

                        retcode = 1;
                      }

                    pDataModel->finish();
                  }

              // Check whether a file for saving the resulting model is given
              if (!COptions::compareValue("Save", std::string("")))
                {
                  std::string Save;
                  COptions::getValue("Save", Save);

                  if (!pDataModel->saveModel(Save, NULL, true))
                    {
                      std::cerr << "Save File: " << Save << std::endl;
                      std::cerr << CCopasiMessage::getAllMessageText() << std::endl;

                      retcode = 1;
                    }

                  // Since only one save file name can be specified we
                  // stop execution.
                  break;
                }
            }
        }
    }

  catch (CCopasiException Exception)
    {
      std::cerr << "Unhandled Exception:" << std::endl;
      std::cerr << Exception.getMessage().getText() << std::endl;
    }

finish:
  CCopasiRootContainer::destroy();

  return retcode;
}

void writeLogo()
{
  bool NoLogo = false;
  COptions::getValue("NoLogo", NoLogo);

  if (NoLogo) return;

  std::cout << "COPASI "
#ifdef COPASI_LICENSE_COM
            << "(commercial) "
#endif // COPASI_LICENSE_COM
            << CVersion::VERSION.getVersion() << std::endl
            << "The use of this software indicates the acceptance of the attached license." << std::endl
            << "To view the license please use the option: --license" << std::endl
            << std::endl;
}

int validate()
{
  int retcode = 0;

  // We are already sure that the COPASI model compiled. That means
  // we only need to test the active tasks
  assert(CCopasiRootContainer::getDatamodelList()->size() != 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  CCopasiVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();
  size_t i, imax = TaskList.size();

  for (i = 0; i < imax; i++)
    if (TaskList[i]->isScheduled())
      {
        bool success = true;
        TaskList[i]->getProblem()->setModel(pDataModel->getModel());

        try
          {
            success =
              TaskList[i]->initialize(CCopasiTask::OUTPUT_SE, pDataModel, NULL);

            // We need to check whether the result is saved in any form.
            // If not we need to stop right here to avoid wasting time.
            if (CCopasiMessage::checkForMessage(MCCopasiTask + 5) &&
                (!TaskList[i]->isUpdateModel() ||
                 COptions::compareValue("Save", std::string(""))))
              success = false;
          }

        catch (...)
          {
            success = false;
          }

        TaskList[i]->restore();

        if (!success)
          {
            std::cerr << "File: " << pDataModel->getFileName() << std::endl;
            std::cerr << "Task: " << TaskList[i]->getObjectName() << std::endl;
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
      default:
        Level = 2;
        Version = 4;
        break;
    }

  assert(CCopasiRootContainer::getDatamodelList()->size() != 0);

  if (!(*CCopasiRootContainer::getDatamodelList())[0]->exportSBML(ExportSBML, true, Level, Version))
    {
      std::cerr << "SBML Export File: " << ExportSBML << std::endl;
      std::cerr << CCopasiMessage::getAllMessageText() << std::endl;
      retcode = 1;
    }

  return retcode;
}
