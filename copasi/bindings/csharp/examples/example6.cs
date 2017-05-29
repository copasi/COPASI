/**
 * This is an example on how to run an parameter fitting task.
 * The example creates a simple model and runs a time course simulation on it.
 * The timecourse data is written to file with some noise added to it.
 * This data is used to fit the original parameters.
 */


using System;
using System.Collections;
using System.Collections.Generic;
using org.COPASI;
using System.Diagnostics;

class example6
{

    static void Main(string[] args)
    {
        Debug.Assert(CRootContainer.getRoot() != null);
        // create a new datamodel
        CDataModel dataModel = CRootContainer.addDatamodel();
        Debug.Assert(CRootContainer.getDatamodelList().size() == 1);
        // first we load a simple model
          try
          {
              // load the model 
              dataModel.importSBMLFromString(MODEL_STRING);
          }
          catch
          {
              System.Console.Error.WriteLine( "Error while importing the model.");
              System.Environment.Exit(1);
          }
		            
        // now we need to run some time course simulation to get data to fit
        // against

        // get the trajectory task object
        CTrajectoryTask trajectoryTask = (CTrajectoryTask)dataModel.getTask("Time-Course");

        // run a deterministic time course
        trajectoryTask.setMethodType(CTaskEnum.Method_deterministic);

        // pass a pointer of the model to the problem
        trajectoryTask.getProblem().setModel(dataModel.getModel());

        // activate the task so that it will be run when the model is saved
        // and passed to CopasiSE
        trajectoryTask.setScheduled(true);

        // get the problem for the task to set some parameters
        CTrajectoryProblem problem = (CTrajectoryProblem)trajectoryTask.getProblem();

        // simulate 4000 steps
        problem.setStepNumber(4000);
        // start at time 0
        dataModel.getModel().setInitialTime(0.0);
        // simulate a duration of 400 time units
        problem.setDuration(400);
        // tell the problem to actually generate time series data
        problem.setTimeSeriesRequested(true);

        // set some parameters for the LSODA method through the method
        // Currently we don't use the method to set anything
        //CTrajectoryMethod method = (CTrajectoryMethod)trajectoryTask.getMethod();

        bool result=true;
        try
        {
            // now we run the actual trajectory
            result=trajectoryTask.processWithOutputFlags(true, (int)CCopasiTask.ONLY_TIME_SERIES);
        }
        catch
        {
            System.Console.Error.WriteLine( "Error. Running the time course simulation failed." );
            String lastErrors =  trajectoryTask.getProcessError();
          // check if there are additional error messages
          if (!string.IsNullOrEmpty(lastErrors))
          {
              // print the messages in chronological order
              System.Console.Error.WriteLine(lastErrors);
          }

            System.Environment.Exit(1);
        }
        if(result==false)
        {
            System.Console.Error.WriteLine( "An error occured while running the time course simulation.");
			String lastErrors =  trajectoryTask.getProcessError();
            // check if there are additional error messages
            if (!string.IsNullOrEmpty(lastErrors))
            {
                // print the messages in chronological order
                System.Console.Error.WriteLine(lastErrors);
            }
            System.Environment.Exit(1);
        }

        // we write the data to a file and add some noise to it
        // This is necessary since COPASI can only read experimental data from
        // file.
        CTimeSeries timeSeries = trajectoryTask.getTimeSeries();
        // we simulated 100 steps, including the initial state, this should be
        // 101 step in the timeseries
        Debug.Assert(timeSeries.getRecordedSteps() == 4001);
        uint i;
        uint iMax = (uint)timeSeries.getNumVariables();
        // there should be four variables, the three metabolites and time
        Debug.Assert(iMax == 5);
        uint lastIndex = (uint)timeSeries.getRecordedSteps() - 1;
        // open the file
        // we need to remember in which order the variables are written to file
        // since we need to specify this later in the parameter fitting task
        List<uint> indexSet=new List<uint>(); 
        List<CMetab> metabVector=new List<CMetab>(); 

        // write the header
        // the first variable in a time series is a always time, for the rest
        // of the variables, we use the SBML id in the header
        double random=0.0;
        System.Random rand_gen = new System.Random();
        try
        {
          System.IO.StreamWriter os = new System.IO.StreamWriter("fakedata_example6.txt");
          os.Write("# time ");
          CKeyFactory keyFactory=CRootContainer.getKeyFactory();
          Debug.Assert(keyFactory != null);
          for(i=1;i<iMax;++i)
          {
            string key=timeSeries.getKey(i);
            CDataObject obj=keyFactory.get(key);
            Debug.Assert(obj != null);
            // only write header data or metabolites
            System.Type type = obj.GetType();
            if(type.FullName.Equals("org.COPASI.CMetab"))
            {
              os.Write(", ");
              os.Write(timeSeries.getSBMLId(i,dataModel));
              CMetab m=(CMetab)obj;
              indexSet.Add(i);
              metabVector.Add(m);
            }
          }
          os.Write("\n");
          double data=0.0;
          for (i = 0;i < lastIndex;++i)
          {
            uint j;
            string s="";
            for(j=0;j<iMax;++j)
            {
              // we only want to  write the data for metabolites
              // the compartment does not interest us here
              if(j==0 || indexSet.Contains(j))
              {
                // write the data with some noise (+-5% max)
                random=rand_gen.NextDouble();
                data=timeSeries.getConcentrationData(i, j);
                // don't add noise to the time
                if(j!=0)
                {
                  data+=data*(random*0.1-0.05);
                }
                s=s+(System.Convert.ToString(data));
                s=s+", ";
              }
            }
            // remove the last two characters again
            os.Write(s.Substring(0,s.Length - 2));
            os.Write("\n");
          }
          os.Close();
        }
        catch (System.ApplicationException e)
        {
            System.Console.Error.WriteLine("Error. Could not write time course data to file.");
            System.Console.WriteLine(e.Message);
            System.Environment.Exit(1);
        }
        
        // now we change the parameter values to see if the parameter fitting
        // can really find the original values
        random=rand_gen.NextDouble()*10;
        CReaction reaction=dataModel.getModel().getReaction(0);
        // we know that it is an irreversible mass action, so there is one
        // parameter
        Debug.Assert(reaction.getParameters().size() == 1);
        Debug.Assert(reaction.isLocalParameter(0));
        // the parameter of a irreversible mass action is called k1
        reaction.setParameterValue("k1",random);
        
        reaction=dataModel.getModel().getReaction(1);
        // we know that it is an irreversible mass action, so there is one
        // parameter
        Debug.Assert(reaction.getParameters().size() == 1);
        Debug.Assert(reaction.isLocalParameter(0));
        reaction.setParameterValue("k1",random);

        CFitTask fitTask=(CFitTask)dataModel.addTask(CTaskEnum.Task_parameterFitting);
        Debug.Assert(fitTask != null);
        // the method in a fit task is an instance of COptMethod or a subclass of
        // it.
        COptMethod fitMethod=(COptMethod)fitTask.getMethod();
        Debug.Assert(fitMethod != null);
        // the object must be an instance of COptMethod or a subclass thereof
        // (CFitMethod)
        CFitProblem fitProblem=(CFitProblem)fitTask.getProblem();
        Debug.Assert(fitProblem != null);
        
        CExperimentSet experimentSet=(CExperimentSet)fitProblem.getParameter("Experiment Set");
        Debug.Assert(experimentSet != null);
        
        // first experiment (we only have one here)
        CExperiment experiment=new CExperiment(dataModel);
        Debug.Assert(experiment != null);
        // tell COPASI where to find the data
        // reading data from string is not possible with the current C++ API
        experiment.setFileName("fakedata_example6.txt");
        // we have to tell COPASI that the data for the experiment is a komma
        // separated list (the default is TAB separated)
        experiment.setSeparator(",");
        // the data start in row 1 and goes to row 4001
        experiment.setFirstRow(1);
        Debug.Assert(experiment.getFirstRow()==1);
        experiment.setLastRow(4001);
        Debug.Assert(experiment.getLastRow()==4001);
        experiment.setHeaderRow(1);
        Debug.Assert(experiment.getHeaderRow()==1);
        experiment.setExperimentType(CTaskEnum.Task_timeCourse);
        Debug.Assert(experiment.getExperimentType()==CTaskEnum.Task_timeCourse);
        experiment.setNumColumns(4);
        Debug.Assert(experiment.getNumColumns()==4);
        CExperimentObjectMap objectMap=experiment.getObjectMap();
        Debug.Assert(objectMap != null);
        result=objectMap.setNumCols(4);
        Debug.Assert(result == true);
        result=objectMap.setRole(0,CExperiment.time);
        Debug.Assert(result == true);
        Debug.Assert(objectMap.getRole(0) == CExperiment.time);

        CModel model=dataModel.getModel();
        Debug.Assert(model!=null);
        CDataObject timeReference=model.getValueReference();
        Debug.Assert(timeReference != null);
        objectMap.setObjectCN(0,timeReference.getCN().getString());
       
        // now we tell COPASI which column contain the concentrations of
        // metabolites and belong to dependent variables
        objectMap.setRole(1,CExperiment.dependent);
        CMetab metab=metabVector[0];
        Debug.Assert(metab != null);
        CDataObject particleReference=metab.getConcentrationReference();
        Debug.Assert(particleReference != null);
        objectMap.setObjectCN(1,particleReference.getCN().getString());

        objectMap.setRole(2,CExperiment.dependent);
        metab=metabVector[1];
        Debug.Assert(metab != null);
        particleReference=metab.getConcentrationReference();
        Debug.Assert(particleReference != null);
        objectMap.setObjectCN(2,particleReference.getCN().getString());

        objectMap.setRole(3,CExperiment.dependent);
        metab=metabVector[2];
        Debug.Assert(metab != null);
        particleReference=metab.getConcentrationReference();
        Debug.Assert(particleReference != null);
        objectMap.setObjectCN(3,particleReference.getCN().getString());
        
        experimentSet.addExperiment(experiment);
        Debug.Assert(experimentSet.getExperimentCount()==1);
        // addExperiment makes a copy, so we need to get the added experiment
        // again
        experiment=experimentSet.getExperiment(0);
        Debug.Assert(experiment != null);

        // now we have to define the two fit items for the two local parameters
        // of the two reactions
        reaction=model.getReaction(0);
        Debug.Assert(reaction != null);
        Debug.Assert(reaction.isLocalParameter(0)==true);
        CCopasiParameter parameter=reaction.getParameters().getParameter(0);
        Debug.Assert(parameter != null);
        
        // define a CFitItem
        CDataObject parameterReference=parameter.getValueReference();
        Debug.Assert(parameterReference != null);
        CFitItem fitItem1=new CFitItem(dataModel);
        Debug.Assert(fitItem1 !=null);
        fitItem1.setObjectCN(parameterReference.getCN());
        fitItem1.setStartValue(4.0);
        fitItem1.setLowerBound(new CCommonName("0.00001"));
        fitItem1.setUpperBound(new CCommonName("10"));
        // add the fit item to the correct parameter group
        CCopasiParameterGroup optimizationItemGroup=(CCopasiParameterGroup)fitProblem.getParameter("OptimizationItemList");
        Debug.Assert(optimizationItemGroup != null);
        optimizationItemGroup.addParameter(fitItem1);
        
        reaction=model.getReaction(1);
        Debug.Assert(reaction != null);
        Debug.Assert(reaction.isLocalParameter(0)==true);
        parameter=reaction.getParameters().getParameter(0);
        Debug.Assert(parameter != null);
        
        // define a CFitItem
        parameterReference=parameter.getValueReference();
        Debug.Assert(parameterReference != null);
        CFitItem fitItem2=new CFitItem(dataModel);
        Debug.Assert(fitItem2 !=null);
        fitItem2.setObjectCN(parameterReference.getCN());
        fitItem2.setStartValue(4.0);
        fitItem2.setLowerBound(new CCommonName("0.00001"));
        fitItem2.setUpperBound(new CCommonName("10"));
        // add the fit item to the correct parameter group
        optimizationItemGroup.addParameter(fitItem2);
        
        result=true;
        try
        {
          // running the task for this example will probably take some time
          System.Console.WriteLine("This can take some time...");
          result=fitTask.processWithOutputFlags(true, (int)CCopasiTask.ONLY_TIME_SERIES);
        }
        catch
        {
          System.Console.Error.WriteLine("Error. Parameter fitting failed.");
          String lastErrors =  fitTask.getProcessError();
          // check if there are additional error messages
          if (!string.IsNullOrEmpty(lastErrors))
          {
              // print the messages in chronological order
              System.Console.Error.WriteLine(lastErrors);
          }

          System.Environment.Exit(1);
        }
		
        Debug.Assert(result == true);
        // assert that there are two optimization items
        Debug.Assert(fitProblem.getOptItemList().Count == 2);
        // the order should be the order in whih we added the items above
        COptItem optItem1 = fitProblem.getOptItemList()[0];
        COptItem optItem2 = fitProblem.getOptItemList()[1];
        // the actual results are stored in the fit problem
        Debug.Assert(fitProblem.getSolutionVariables().size() == 2);
        System.Console.WriteLine("value for " + optItem1.getObject().getCN().getString() + ": " + fitProblem.getSolutionVariables().get(0));
        System.Console.WriteLine("value for " + optItem2.getObject().getCN().getString() + ": " + fitProblem.getSolutionVariables().get(1));
        // depending on the noise, the fit can be quite bad, so we are a litle
        // relaxed here (we should be within 3% of the original values)
        Debug.Assert((System.Math.Abs(fitProblem.getSolutionVariables().get(0) - 0.03) / 0.03) < 3e-2);
        Debug.Assert((System.Math.Abs(fitProblem.getSolutionVariables().get(1) - 0.004) / 0.004) < 3e-2);
 

    }

    static string MODEL_STRING=
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" +
"<!-- Created by COPASI version 4.5.30 (Debug) on 2009-03-30 08:01 with libSBML version 3.3.2. -->\n" +
"<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n" +
"  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"New Model\">\n" +
"    <listOfUnitDefinitions>\n" +
"      <unitDefinition id=\"volume\">\n" +
"        <listOfUnits>\n" +
"          <unit kind=\"litre\" scale=\"-3\"/>\n" +
"        </listOfUnits>\n" +
"      </unitDefinition>\n" +
"      <unitDefinition id=\"substance\">\n" +
"        <listOfUnits>\n" +
"          <unit kind=\"mole\" scale=\"-3\"/>\n" +
"        </listOfUnits>\n" +
"      </unitDefinition>\n" +
"    </listOfUnitDefinitions>\n" +
"    <listOfCompartments>\n" +
"      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n" +
"    </listOfCompartments>\n" +
"    <listOfSpecies>\n" +
"      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"5\"/>\n" +
"      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"0\"/>\n" +
"      <species id=\"species_3\" name=\"C\" compartment=\"compartment_1\" initialConcentration=\"0\"/>\n" +
"    </listOfSpecies>\n" +
"    <listOfReactions>\n" +
"      <reaction id=\"reaction_1\" name=\"reaction\" reversible=\"false\">\n" +
"        <listOfReactants>\n" +
"          <speciesReference species=\"species_1\"/>\n" +
"        </listOfReactants>\n" +
"        <listOfProducts>\n" +
"          <speciesReference species=\"species_2\"/>\n" +
"        </listOfProducts>\n" +
"        <kineticLaw>\n" +
"          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n" +
"            <apply>\n" +
"              <times/>\n" +
"              <ci> compartment_1 </ci>\n" +
"              <ci> k1 </ci>\n" +
"              <ci> species_1 </ci>\n" +
"            </apply>\n" +
"          </math>\n" +
"          <listOfParameters>\n" +
"            <parameter id=\"k1\" name=\"k1\" value=\"0.03\"/>\n" +
"          </listOfParameters>\n" +
"        </kineticLaw>\n" +
"      </reaction>\n" +
"      <reaction id=\"reaction_2\" name=\"reaction_1\" reversible=\"false\">\n" +
"        <listOfReactants>\n" +
"          <speciesReference species=\"species_2\"/>\n" +
"        </listOfReactants>\n" +
"        <listOfProducts>\n" +
"          <speciesReference species=\"species_3\"/>\n" +
"        </listOfProducts>\n" +
"        <kineticLaw>\n" +
"          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n" +
"            <apply>\n" +
"              <times/>\n" +
"              <ci> compartment_1 </ci>\n" +
"              <ci> k1 </ci>\n" +
"              <ci> species_2 </ci>\n" +
"            </apply>\n" +
"          </math>\n" +
"          <listOfParameters>\n" +
"            <parameter id=\"k1\" name=\"k1\" value=\"0.004\"/>\n" +
"          </listOfParameters>\n" +
"        </kineticLaw>\n" +
"      </reaction>\n" +
"    </listOfReactions>\n" +
"  </model>\n" +
"</sbml>";

}
