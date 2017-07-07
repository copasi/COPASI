// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * This example is similar to example 9.
 * Instead of calculating the Jacobian, we do a metabolic control
 * analysis on the sbml model given as a commandline argument.
 *
 * So in this example, we learn how to work with annotated matrices.
 */
#include <iostream>
#include <iomanip>
#include <vector>

// this define is needed in the file where the main routine is defined
// It has to be defined before copasi.h is included, otherwise
// you will get unresolved symbols when linking your programm.
// Alternatively, you can define the symbols that are defined in copasi.h yourself.
// For that, check copasi.h
#define COPASI_MAIN
#include "copasi/copasi.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CReaction.h"
#include "copasi/core/CDataArray.h"
#include "copasi/steadystate/CMCATask.h"
#include "copasi/steadystate/CMCAProblem.h"
#include "copasi/steadystate/CMCAMethod.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/steadystate/CSteadyStateMethod.h"

/// <summary>
/// Utility function printing an annotated matrix
/// </summary>
/// <param name="title"></param>
/// <param name="annotated_matrix"></param>
void print_annotated_matrix(const std::string & title, const CDataArray & annotated_matrix)
{
  std::cout << title << std::endl;
  std::cout << "==========" << std::endl;

  CDataArray::index_type size = annotated_matrix.size();

  if (size.size() != 2)
    {
      std::cout << "  This simple function only deals with two dimensional matrices" << std::endl;
      return;
    }

  size_t rows = size[0];
  size_t columns = size[1];

  std::cout << "Size of the matrix is: " << rows << " rows x " << columns << " columns" << std::endl;

  const std::vector< std::string > & row_headers = annotated_matrix.getAnnotationsString(0);
  const std::vector< std::string > & col_headers = annotated_matrix.getAnnotationsString(1);

  // print column headers
  std::cout << "\t\t";

  for (size_t i = 0; i < columns; ++i)
    std::cout << col_headers[i] << "\t";

  std::cout  << std::endl;

  for (size_t j = 0; j < rows; ++j)
    {
      for (size_t i = 0; i < columns; ++i)
        {
          if (i == 0)
            std::cout << row_headers[j] << "\t";

          const CDataObject * pObject = CObjectInterface::DataObject(annotated_matrix.getObject(StringPrint("[%d][%d]", j, i)));

          if (pObject != NULL)
            {
              pObject->print(&std::cout);
            }
          else
            {
              std::cout << "NaN";
            }

          std::cout << "\t";
        }

      std::cout << std::endl;
    }

  std::cout << std::endl;
}

int main(int argc, char** argv)
{
  // initialize the backend library
  // since we are not interested in the arguments
  // that are passed to main, we pass 0 and NULL to
  // init
  CRootContainer::init(0, NULL);
  assert(CRootContainer::getRoot() != NULL);
  // create a new datamodel
  CDataModel* pDataModel = CRootContainer::addDatamodel();
  assert(pDataModel != NULL);
  assert(CRootContainer::getDatamodelList()->size() == 1);

  // check if we got exactly one argument, which should be an SBML filename
  if (argc == 2)
    {
      // next we import a simple SBML model from a string
      std::string filename = argv[1];
      // clear the message queue so that we only have error messages from the import in the queue
      CCopasiMessage::clearDeque();
      bool result = true;

      try
        {
          result = pDataModel->importSBML(filename, NULL);
        }
      catch (...)
        {
          result = false;
        }

      if (result == false)
        {
          std::cerr << "Error while importing the model from file named \"" << filename << "\"." << std::endl;
          // final cleanup
          CRootContainer::destroy();
          return 1;
        }

      // check if the import was successful
      CCopasiMessage::Type mostSevere = CCopasiMessage::getHighestSeverity();
      // if it was a filtered error, we convert it to an unfiltered type
      // the filtered error messages have the same value as the unfiltered, but they
      // have the 7th bit set which basically adds 128 to the value
      mostSevere = (CCopasiMessage::Type)((int)mostSevere & 127);

      // we assume that the import succeeded if the return value is true and
      // the most severe error message is not an error or an exception
      if (result != true &&  mostSevere < CCopasiMessage::ERROR)
        {
          std::cerr << "Sorry. Model could not be imported." << std::endl;
          // final cleanup
          CRootContainer::destroy();
          return 1;
        }

      // get the task list
      CDataVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();

      // get the metabolic control analysis task object
      CMCATask* pTask = dynamic_cast<CMCATask*>(&TaskList["Metabolic Control Analysis"]);

      // The task should always be there, but just to be sure, we check and create it, if it wasn't.
      if (pTask == NULL)
        {
          // remove any existing steadystate task just to be sure since in
          // theory only the cast might have failed above
          TaskList.remove("Metabolic Control Analysis");

          // create a new one
          pTask = new CMCATask(& TaskList);

          // add the new task to the task list
          TaskList.add(pTask, true);
        }

      // we can set some options
      // e.g. if we want to calculate the MCA at a steady state
      CMCAProblem* pMCAProblem = dynamic_cast<CMCAProblem*>(pTask->getProblem());
      assert(pMCAProblem != NULL);
      pMCAProblem->setSteadyStateRequested(true);

      // the other parameters are set on the method
      CMCAMethod* pMCAMethod = dynamic_cast<CMCAMethod*>(pTask->getMethod());
      assert(pMCAMethod != NULL);
      // parameters that could be set on the method are:
      // "Modulation Factor" double 1e-9
      // For documentation on the individual parameters for the MCA method
      // and the steadystate method below, please check the COPASI documentation for those
      // methods on http://www.copasi.org
      pMCAMethod->setValue("Modulation Factor", 1e-9);

      // Other parameters that affect the calculation of the steady state and which therefore might affect the calculation of the
      // control coefficients are: (name type default)
      // "Resolution" double 1e-9
      // "Derivation Factor" double 0.001
      // "Use Newton" bool true
      // "Use Integration" bool true
      // "Use Back Integration" bool true
      // "Accept Negative Concentrations" bool false
      // "Iteration Limit" unsigned int 50
      // "Maximum duration for forward integration" double 1e9
      // "Maximum duration for backward integration" double 1e6
      // the parameters have to be set on the steady state method directly
      // get the trajectory task object
      CSteadyStateTask* pSSTask = dynamic_cast<CSteadyStateTask*>(&TaskList["Steady-State"]);
      assert(pSSTask != NULL);
      CSteadyStateMethod* pSSMethod = dynamic_cast<CSteadyStateMethod*>(pSSTask->getMethod());
      assert(pSSMethod != NULL);
      pMCAMethod->setValue("Use Newton", true);
      // sometime the setValue methods needs to passed the correct type
      // to disambiguate the function call
      pMCAMethod->setValue("Iteration Limit", (C_INT32)70);

      // again, better safe than sorry, we check if the task was actually there and if not, we delete it
      if (pSSTask == NULL)
        {
          // remove any existing steadystate task just to be sure since in
          // theory only the cast might have failed above
          TaskList.remove("Steady-State");

          // create a new one
          pSSTask = new CSteadyStateTask(& TaskList);

          // add the new task to the task list
          TaskList.add(pSSTask, true);
        }

      CCopasiMessage::clearDeque();

      try
        {
          // initialize the trajectory task
          // we want complete output (HEADER, BODY and FOOTER)
          pTask->initialize(CCopasiTask::OUTPUT_SE, pDataModel, NULL);
          // now we run the actual trajectory
          pTask->process(true);
        }
      catch (...)
        {
          std::cerr << "Error. Doing the metabolic control analysis failed." << std::endl;

          // check if there are additional error messages
          if (CCopasiMessage::size() > 0)
            {
              // print the messages in chronological order
              std::cerr << CCopasiMessage::getAllMessageText(true);
            }

          // final cleanup
          CRootContainer::destroy();
          return 1;
        }

      // since we want to output a flux, we first have to check if a steady state was found at all
      // otherwise we could only output the elasticities because control coefficients are only calculated
      // if a steady state was found
      CSteadyStateMethod::ReturnCode sstatus = pMCAMethod->getSteadyStateStatus();

      switch (sstatus)
        {
          case CSteadyStateMethod::found:
            // everything is fine, we found a steady state
            break;

          case CSteadyStateMethod::notFound:
          case CSteadyStateMethod::foundEquilibrium:

          // we are also not interested in steady states with negative concentrations
          case CSteadyStateMethod::foundNegative:
            std::cerr << "Could not find a steady state with non-negative concentrations, so I can't output control coefficients." << std::endl;
            CRootContainer::destroy();
            return 1;
            break;
        }

      // the actual results of the MCA can be found in the MCAMethod instance that belongs to the task

      // from the method, we can now get the elasticities, flux control coefficients
      // and concentration control coefficients
      // getScaledElasticities(Ann)
      // getUnscaledElasticities(Ann)
      // getScaledFluxCC(Ann)
      // getUnscaledFluxCC(Ann)
      // getScaledConcentrationCC(Ann)
      // getUnscaledConcentrationCC(Ann)
      // The (Ann) means that there is a method that returns an annotated matrix
      // as well as a method that returns a normal float matrix
      // The method that returns the annotated matrix end with Ann and the method that
      // returns a double matrix doesn't have the Ann.
      print_annotated_matrix("Scaled Concentration Control Coefficients", *pMCAMethod->getScaledConcentrationCCAnn());
      print_annotated_matrix("Scaled Flux Control Coefficients", *pMCAMethod->getScaledFluxCCAnn());
      print_annotated_matrix("Scaled Elasticities", *pMCAMethod->getScaledElasticitiesAnn());
    }
  else
    {
      // give a usage message
      std::cerr << "Usage: example10 SBMLFILE" << std::endl;
      // final cleanup
      CRootContainer::destroy();
      return 1;
    }

  // final cleanup
  CRootContainer::destroy();
  return 0;
}
