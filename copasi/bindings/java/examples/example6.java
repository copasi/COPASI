// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the 
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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 




/**
 * This is an example on how to run an parameter fitting task.
 * The example creates a simple model and runs a time course simulation on it.
 * The timecourse data is written to file with some noise added to it.
 * This data is used to fit the original parameters.
 */


import org.COPASI.*;
import java.io.*;

public class example6
{

    public static void main(String[] args)
    {
        assert CRootContainer.getRoot() != null;
        // create a new datamodel
        CDataModel dataModel = CRootContainer.addDatamodel();
        assert CRootContainer.getDatamodelList().size() == 1;
        // first we load a simple model
          try
          {
              // load the model 
              dataModel.importSBMLFromString(MODEL_STRING);
          }
          catch (java.lang.Exception ex)
          {
              System.err.println( "Error while importing the model.");
              System.exit(1);
          }
          
        // now we need to run some time course simulation to get data to fit
        // against

        // get the trajectory task object
        CTrajectoryTask trajectoryTask = (CTrajectoryTask)dataModel.getTask("Time-Course");
        assert trajectoryTask != null;

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

        boolean result=true;
        try
        {
            // now we run the actual trajectory
            result=trajectoryTask.processWithOutputFlags(true, (int)CCopasiTask.ONLY_TIME_SERIES);
        }
        catch (java.lang.Exception ex)
        {
            System.err.println( "Error. Running the time course simulation failed." );
			String lastError = trajectoryTask.getProcessError();
            // check if there are additional error messages
            if (lastError.length() > 0)
            {
                // print the messages in chronological order
                System.err.println(lastError);
            }
            System.exit(1);
        }
        if(result==false)
        {
            System.err.println( "An error occured while running the time course simulation." );
            // check if there are additional error messages
            if (CCopasiMessage.size() > 0)
            {
                // print the messages in chronological order
                System.err.println(CCopasiMessage.getAllMessageText(true));
            }
            System.exit(1);
        }

        // we write the data to a file and add some noise to it
        // This is necessary since COPASI can only read experimental data from
        // file.
        CTimeSeries timeSeries = trajectoryTask.getTimeSeries();
        // we simulated 100 steps, including the initial state, this should be
        // 101 step in the timeseries
        assert timeSeries.getRecordedSteps() == 4001;
        int i;
        int iMax = (int)timeSeries.getNumVariables();
        // there should be four variables, the three metabolites and time
        assert iMax == 5;
        int lastIndex = (int)timeSeries.getRecordedSteps() - 1;
        // open the file
        // we need to remember in which order the variables are written to file
        // since we need to specify this later in the parameter fitting task
        java.util.Set<Integer> indexSet=new java.util.HashSet<Integer>(); 
        java.util.Vector<CMetab> metabVector=new java.util.Vector<CMetab>(); 

        // write the header
        // the first variable in a time series is a always time, for the rest
        // of the variables, we use the SBML id in the header
        double random=0.0;
        FileWriter os = null;
        try        
        {
          os=new FileWriter("fakedata_example6.txt");
          os.write("# time ");
          CKeyFactory keyFactory=CRootContainer.getKeyFactory();
          assert keyFactory != null;
          for(i=1;i<iMax;++i)
          {
            String key=timeSeries.getKey(i);
            CDataObject object=keyFactory.get(key);
            assert object != null;
            // only write header data or metabolites
            if(object.getClass()==org.COPASI.CMetab.class)
            {
              os.write(", ");
              os.write(timeSeries.getSBMLId(i,dataModel));
              CMetab m=(CMetab)object;
              indexSet.add(new Integer(i));
              metabVector.add(m);
            }
          }
          os.write("\n");
          double data=0.0;
          for (i = 0;i < lastIndex;++i)
          {
            int j;
            String s=new String();
            for(j=0;j<iMax;++j)
            {
              // we only want to  write the data for metabolites
              // the compartment does not interest us here
              if(j==0 || indexSet.contains(j))
              {
                // write the data with some noise (+-5% max)
                random=Math.random();
                data=timeSeries.getConcentrationData(i, j);
                // don't add noise to the time
                if(j!=0)
                {
                  data+=data*(random*0.1-0.05);
                }
                s=s+(new Double(data).toString());
                s=s+", ";
              }
            }
            // remove the last two characters again
            os.write(s.substring(0,s.length()-2));
            os.write("\n");
          }
          os.close();
        }
        catch(java.lang.Exception e)
        {
            System.err.println("Error. Could not write time course data to file.");
            System.out.println(e.getMessage());
            System.exit(1);
        }
        if (os != null)
        {
        	try {
				os.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
        }
        
        // now we change the parameter values to see if the parameter fitting
        // can really find the original values
        random=Math.random()*10;
        CReaction reaction=dataModel.getModel().getReaction(0);
        // we know that it is an irreversible mass action, so there is one
        // parameter
        assert reaction.getParameters().size() == 1;
        assert reaction.isLocalParameter(0);
        // the parameter of a irreversible mass action is called k1
        reaction.setParameterValue("k1",random);
        
        reaction=dataModel.getModel().getReaction(1);
        // we know that it is an irreversible mass action, so there is one
        // parameter
        assert reaction.getParameters().size() == 1;
        assert reaction.isLocalParameter(0);
        reaction.setParameterValue("k1",random);

        CFitTask fitTask=(CFitTask)dataModel.addTask(CTaskEnum.Task_parameterFitting);
        assert fitTask != null;
        // the method in a fit task is an instance of COptMethod or a subclass of
        // it.
        COptMethod fitMethod=(COptMethod)fitTask.getMethod();
        assert fitMethod != null;
        // the object must be an instance of COptMethod or a subclass thereof
        // (CFitMethod)
        CFitProblem fitProblem=(CFitProblem)fitTask.getProblem();
        assert fitProblem != null;
        
        CExperimentSet experimentSet=(CExperimentSet)fitProblem.getParameter("Experiment Set");
        assert experimentSet != null;
        
        // first experiment (we only have one here)
        CExperiment experiment=new CExperiment(dataModel);
        assert experiment != null;
        // tell COPASI where to find the data
        // reading data from string is not possible with the current C++ API
        experiment.setFileName("fakedata_example6.txt");
        // we have to tell COPASI that the data for the experiment is a komma
        // separated list (the default is TAB separated)
        experiment.setSeparator(",");
        // the data start in row 1 and goes to row 4001
        experiment.setFirstRow(1);
        assert experiment.getFirstRow()==1;
        experiment.setLastRow(4001);
        assert experiment.getLastRow()==4001;
        experiment.setHeaderRow(1);
        assert experiment.getHeaderRow()==1;
        experiment.setExperimentType(CTaskEnum.Task_timeCourse);
        assert experiment.getExperimentType()==CTaskEnum.Task_timeCourse;
        experiment.setNumColumns(4);
        assert experiment.getNumColumns()==4;
        CExperimentObjectMap objectMap=experiment.getObjectMap();
        assert objectMap != null;
        result=objectMap.setNumCols(4);
        assert result == true;
        result=objectMap.setRole(0,CExperiment.time);
        assert result == true;
        assert objectMap.getRole(0) == CExperiment.time;

        CModel model=dataModel.getModel();
        assert model!=null;
        CDataObject timeReference=model.getValueReference();
        assert timeReference != null;
        objectMap.setObjectCN(0,timeReference.getCN().getString());
       
        // now we tell COPASI which column contain the concentrations of
        // metabolites and belong to dependent variables
        objectMap.setRole(1,CExperiment.dependent);
        CMetab metab=metabVector.elementAt(0);
        assert metab != null;
        CDataObject particleReference=metab.getConcentrationReference();
        assert particleReference != null;
        objectMap.setObjectCN(1,particleReference.getCN().getString());

        objectMap.setRole(2,CExperiment.dependent);
        metab=metabVector.elementAt(1);
        assert metab != null;
        particleReference=metab.getConcentrationReference();
        assert particleReference != null;
        objectMap.setObjectCN(2,particleReference.getCN().getString());

        objectMap.setRole(3,CExperiment.dependent);
        metab=metabVector.elementAt(2);
        assert metab != null;
        particleReference=metab.getConcentrationReference();
        assert particleReference != null;
        objectMap.setObjectCN(3,particleReference.getCN().getString());
        
        experimentSet.addExperiment(experiment);
        assert experimentSet.getExperimentCount()==1;
        // addExperiment makes a copy, so we need to get the added experiment
        // again
        experiment=experimentSet.getExperiment(0);
        assert experiment != null;

        // now we have to define the two fit items for the two local parameters
        // of the two reactions
        reaction=model.getReaction(0);
        assert reaction != null;
        assert reaction.isLocalParameter(0)==true;
        CCopasiParameter parameter=reaction.getParameters().getParameter(0);
        assert parameter != null;
        
        // define a CFitItem
        CDataObject parameterReference=parameter.getValueReference();
        assert parameterReference != null;
        CFitItem fitItem1=new CFitItem(dataModel);
        assert fitItem1 !=null;
        fitItem1.setObjectCN(parameterReference.getCN());
        fitItem1.setStartValue(4.0);
        fitItem1.setLowerBound(new CCommonName("0.00001"));
        fitItem1.setUpperBound(new CCommonName("10"));
        // add the fit item to the correct parameter group
        CCopasiParameterGroup optimizationItemGroup=(CCopasiParameterGroup)fitProblem.getParameter("OptimizationItemList");
        assert optimizationItemGroup != null;
        optimizationItemGroup.addParameter(fitItem1);
        
        reaction=model.getReaction(1);
        assert reaction != null;
        assert reaction.isLocalParameter(0)==true;
        parameter=reaction.getParameters().getParameter(0);
        assert parameter != null;
        
        // define a CFitItem
        parameterReference=parameter.getValueReference();
        assert parameterReference != null;
        CFitItem fitItem2=new CFitItem(dataModel);
        assert fitItem2 !=null;
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
          System.out.println("This can take some time...");
          result=fitTask.processWithOutputFlags(true, (int)CCopasiTask.ONLY_TIME_SERIES);
        }
        catch(Exception e)
        {
          System.err.println("Error. Parameter fitting failed.");
			String lastError = fitTask.getProcessError();
            // check if there are additional error messages
            if (lastError.length() > 0)
            {
                // print the messages in chronological order
                System.err.println(lastError);
            }
          System.exit(1);
        }
        assert result == true;
        // assert that there are two optimization items
        assert fitProblem.getOptItemList().size() == 2;
        // the order should be the order in whih we added the items above
        COptItem optItem1 = fitProblem.getOptItemList().get(0);
        COptItem optItem2 = fitProblem.getOptItemList().get(1);
        // the actual results are stored in the fit problem
        assert fitProblem.getSolutionVariables().size() == 2;
        System.out.println("value for " + optItem1.getObject().getCN().getString() + ": " + fitProblem.getSolutionVariables().get(0));
        System.out.println("value for " + optItem2.getObject().getCN().getString() + ": " + fitProblem.getSolutionVariables().get(1));
        // depending on the noise, the fit can be quite bad, so we are a litle
        // relaxed here (we should be within 3% of the original values)
        assert (Math.abs(fitProblem.getSolutionVariables().get(0) - 0.03) / 0.03) < 3e-2;
        assert (Math.abs(fitProblem.getSolutionVariables().get(1) - 0.004) / 0.004) < 3e-2;
 
    }

    static String MODEL_STRING=
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
