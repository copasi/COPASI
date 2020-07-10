// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 




/**
 This example is similar to example 9.
 Instead of calculating the Jacobian, we do a metabolic control
 analysis on the sbml model given as a commandline argument.
 *
 So in this example, we learn how to work with annotated matrices.
 */
import org.COPASI.*;

public class example10
{

 public static void main(String[] args)
 {
  // initialize the backend library
  // since we are not interested in the arguments
  // that are passed to main, we pass 0 and null to
  // init
  CRootContainer.init();
  assert(CRootContainer.getRoot() != null);
  // create a new datamodel
  CDataModel pDataModel = CRootContainer.addDatamodel();
  assert(pDataModel != null);
  assert(CRootContainer.getDatamodelList().size() == 1);

  // check if we got exactly one argument, which should be an SBML filename
  if (args.length == 1)
    {
      // next we import a simple SBML model from a string
      String filename = args[0];
      // clear the message queue so that we only have error messages from the import in the queue
      CCopasiMessage.clearDeque();
      boolean result = true;

      try
        {
          result = pDataModel.importSBML(filename);

        }
      catch (java.lang.Exception ex)
        {
          result = false;
        }

      if (result == false)
        {
          System.err.println("Error while importing the model from file named \"" + filename + "\"." );
          // final cleanup
          CRootContainer.destroy();
          return;
        }

      // check if the import was successful
      int mostSevere = CCopasiMessage.getHighestSeverity();
      // if it was a filtered error, we convert it to an unfiltered type
      // the filtered error messages have the same value as the unfiltered, but they
      // have the 7th bit set which basically adds 128 to the value
      mostSevere = (mostSevere & 127);

      // we assume that the import succeeded if the return value is true and
      // the most severe error message is not an error or an exception
      if (result != true && mostSevere < CCopasiMessage.ERROR)
        {
          System.err.println( "Sorry. Model could not be imported." );
          // final cleanup
          CRootContainer.destroy();
          return;
        }

      // get the metabolic control analysis task object
      CMCATask pTask = (CMCATask)(pDataModel.getTask("Metabolic Control Analysis"));

      // we can set some options
      // e.g. if we want to calculate the MCA at a steady state
      CMCAProblem pMCAProblem = (CMCAProblem)(pTask.getProblem());
      assert(pMCAProblem != null);
      pMCAProblem.setSteadyStateRequested(true);

      // the other parameters are set on the method
      CMCAMethod pMCAMethod = (CMCAMethod)(pTask.getMethod());
      assert(pMCAMethod != null);
      // parameters that could be set on the method are:
      // "Modulation Factor" double 1e-9
      // For documentation on the individual parameters for the MCA method
      // and the steadystate method below, please check the COPASI documentation for those
      // methods on http://www.copasi.org
      pMCAMethod.getParameter("Modulation Factor").setDblValue(1e-9);


      // Other parameters that affect the calculation of the steady state and which therefore might affect the calculation of the
      // control coefficients are: (name type default)
      // "Resolution" double 1e-9
      // "Derivation Factor" double 0.001
      // "Use Newton" bool true
      // "Use Integration" bool true
      // "Use Back Integration" bool true
      // "Accept Negative Concentrations" bool false
      // "Iteration Limit" int 50
      // "Maximum duration for forward integration" double 1e9
      // "Maximum duration for backward integration" double 1e6
      // the parameters have to be set on the steady state method directly
      // get the trajectory task object
      CSteadyStateTask pSSTask = (CSteadyStateTask)(pDataModel.getTask("Steady-State"));
      assert(pSSTask != null);
      CSteadyStateMethod pSSMethod = (CSteadyStateMethod)(pSSTask.getMethod());
      assert(pSSMethod != null);
      pSSMethod.getParameter("Use Newton").setBoolValue(true);
      // sometime the setValue methods needs to passed the correct type
      // to disambiguate the function call
      pSSMethod.getParameter("Iteration Limit").setIntValue(70);

      CCopasiMessage.clearDeque();

      try
        {
          // initialize the trajectory task
          // we want complete output (HEADER, BODY and FOOTER)
          // now we run the actual trajectory
          pTask.processWithOutputFlags(true, (int)CCopasiTask.ONLY_TIME_SERIES);
        }
      catch (java.lang.Exception ex)
        {
          System.err.println("Error. Doing the metabolic control analysis failed.");
			String lastError = pTask.getProcessError();
            // check if there are additional error messages
            if (lastError.length() > 0)
            {
                // print the messages in chronological order
                System.err.println(lastError);
            }
          // final cleanup
          CRootContainer.destroy();
          return;
        }

      // since we want to output a flux, we first have to check if a steady state was found at all
      // otherwise we could only output the elasticities because control coefficients are only calculated
      // if a steady state was found
      int sstatus = pMCAMethod.getSteadyStateStatus();

      switch (sstatus)
        {
          case CSteadyStateMethod.found:
            // everything is fine, we found a steady state
            break;
          case CSteadyStateMethod.notFound:
          case CSteadyStateMethod.foundEquilibrium:
            // we are also not interested in steady states with negative concentrations
          case CSteadyStateMethod.foundNegative:
            System.err.println("Could not find a steady state with non-negative concentrations, so I can't output control coefficients.");
            CRootContainer.destroy();
            return;
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
      CDataArray pCCC = pMCAMethod.getScaledFluxCCAnn();
      assert(pCCC != null);

      if (pCCC != null)
        {
          // since this matrix is probably very large, we will only output the flux control coefficient for
          // the last reaction in the model
          long numReactions = pDataModel.getModel().getReactions().size();

          if (numReactions == 0)
            {
              System.err.println("There are no reactions in the model, can't output a flux control coefficient.");
              CRootContainer.destroy();
              return;
            }

          CReaction pReaction = pDataModel.getModel().getReaction(numReactions-1);

          assert(pReaction != null);

          // first the array annotation can tell us how many dimensions it has.
          // Since the matrix is a 2D array, it should have 2 dimensions
          assert(pCCC.dimensionality() == 2);

          // since the matrix has a dimensionality of 2, the index for the underlaying abstract array
          // object is a vector with two int elements
          // First element is the index for the outer dimension and the second element is the index
          // for the inner dimension
          SizeTStdVector index = new SizeTStdVector(2);

          // since the rows and columns have the same annotation for the flux control coefficients, it doesn't matter
          // for which dimension we get the annotations
          // In this example, we get the annotations that contain the common names.
          // Alternatively, we could have used getAnnatationsString as in example 8 to get the annotations
          // that contain the display names.
          // In this case working with the common names is easier.
          ReportItemVector annotations = pCCC.getAnnotationsCN(1);

          System.out.println( "Flux Control Coefficient for Reaction \"" + pReaction.getObjectName() + "\" with itself:");

          int i = 0;

          // find the annotation for the last reaction
          for (; i < annotations.size(); ++i)
            {
              // if the annotation string is the common name of our reaction
              // we can stop because we have found the correct index
              if (annotations.get(i) == pReaction.getCN())
                {
                  break;
                }
            }

          assert(i != annotations.size());
          // set the 2D index that we want to get from the annotated array
          // In this case we want the control coefficient for the reaction with itself, so
          // the index for both dimensions is the same (i)
          index.set(0,i);
          index.set(1,i);
          System.out.println( pCCC.array().get(index));

        }
    }
  else
    {
      // give a usage message
      System.err.println(  "Usage: example10 SBMLFILE" );
      return;
    }

 }
}



