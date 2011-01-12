// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/cpp_examples/example10/example10.cpp,v $
//   $Revision: 1.1.2.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/12 21:43:44 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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
#include <copasi/copasi.h>


#include <copasi/report/CCopasiRootContainer.h>
#include <copasi/CopasiDataModel/CCopasiDataModel.h>
#include <copasi/model/CModel.h>
#include <copasi/model/CReaction.h>
#include <copasi/utilities/CAnnotatedMatrix.h>
#include <copasi/steadystate/CMCATask.h>
#include <copasi/steadystate/CMCAProblem.h>
#include <copasi/steadystate/CMCAMethod.h>
#include <copasi/steadystate/CSteadyStateTask.h>
#include <copasi/steadystate/CSteadyStateMethod.h>

int main(int argc, char** argv)
{
  // initialize the backend library
  // since we are not interested in the arguments
  // that are passed to main, we pass 0 and NULL to
  // init
  CCopasiRootContainer::init(0, NULL);
  assert(CCopasiRootContainer::getRoot() != NULL);
  // create a new datamodel
  CCopasiDataModel* pDataModel = CCopasiRootContainer::addDatamodel();
  assert(pDataModel != NULL);
  assert(CCopasiRootContainer::getDatamodelList()->size() == 1);

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
          CCopasiRootContainer::destroy();
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
          CCopasiRootContainer::destroy();
          return 1;
        }

      // get the task list
      CCopasiVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();

      // get the metabolic control analysis task object
      CMCATask* pTask = dynamic_cast<CMCATask*>(TaskList["Metabolic Control Analysis"]);

      // The task should always be there, but just to be sure, we check and create it, if it wasn't.
      if (pTask == NULL)
        {
          // create a new one
          pTask = new CMCATask();
          // remove any existing steadystate task just to be sure since in
          // theory only the cast might have failed above
          TaskList.remove("Metabolic Control Analysis");

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
      CSteadyStateTask* pSSTask = dynamic_cast<CSteadyStateTask*>(TaskList["Steady-State"]);
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
          // create a new one
          pSSTask = new CSteadyStateTask();
          // remove any existing steadystate task just to be sure since in
          // theory only the cast might have failed above
          TaskList.remove("Steady-State");

          // add the new task to the task list
          TaskList.add(pSSTask, true);
        }


      CCopasiMessage::clearDeque();

      try
        {
          // initialize the trajectory task
          // we want complete output (HEADER, BODY and FOOTER)
          pTask->initialize(CCopasiTask::OUTPUT_COMPLETE, pDataModel, NULL);
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
          CCopasiRootContainer::destroy();
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
            CCopasiRootContainer::destroy();
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
      const CArrayAnnotation* pCCC = pMCAMethod->getScaledFluxCCAnn();
      assert(pCCC != NULL);

      if (pCCC != NULL)
        {
          // since this matrix is probably very large, we will only output the flux control coefficient for
          // the last reaction in the model
          unsigned int numReactions = pDataModel->getModel()->getReactions().size();

          if (numReactions == 0)
            {
              std::cerr << "There are no reactions in the model, can't output a flux control coefficient." << std::endl;
              CCopasiRootContainer::destroy();
              return 1;
            }

          const CReaction* pReaction = pDataModel->getModel()->getReactions()[numReactions-1];

          assert(pReaction != NULL);

          // first the array annotation can tell us how many dimensions it has.
          // Since the matrix is a 2D array, it should have 2 dimensions
          assert(pCCC->dimensionality() == 2);

          // since the matrix has a dimensionality of 2, the index for the underlaying abstract array
          // object is a vector with two unsigned int elements
          // First element is the index for the outer dimension and the second element is the index
          // for the inner dimension
          std::vector<size_t> index(2);

          // since the rows and columns have the same annotation for the flux control coefficients, it doesn't matter
          // for which dimension we get the annotations
          // In this example, we get the annotations that contain the common names.
          // Alternatively, we could have used getAnnatationsString as in example 8 to get the annotations
          // that contain the display names.
          // In this case working with the common names is easier.
          const std::vector<CRegisteredObjectName>& annotations = pCCC->getAnnotationsCN(1);

          std::cout << "Flux Control Coefficient for Reaction \"" << pReaction->getObjectName() << "\" with itself:";

          unsigned int i = 0;

          // find the annotation for the last reaction
          for (; i < annotations.size(); ++i)
            {
              // if the annotation string is the common name of our reaction
              // we can stop because we have found the correct index
              if (annotations[i] == pReaction->getCN())
                {
                  break;
                }
            }

          assert(i != annotations.size());
          // set the 2D index that we want to get from the annotated array
          // In this case we want the control coefficient for the reaction with itself, so
          // the index for both dimensions is the same (i)
          index[0] = i;
          index[1] = i;
          std::cout << std::setprecision(8);
          std::cout << (*pCCC->array())[index] << std::endl;

        }
    }
  else
    {
      // give a usage message
      std::cerr << "Usage: example10 SBMLFILE" << std::endl;
      // final cleanup
      CCopasiRootContainer::destroy();
      return 1;
    }

  // final cleanup
  CCopasiRootContainer::destroy();
  return 0;
}



