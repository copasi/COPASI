// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/unittests/Test_RunSteadyStateCalculation.java,v $ 
//   $Revision: 1.4 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/01/12 15:40:29 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

package org.COPASI.unittests;

import java.lang.Math;
import java.util.HashMap;
import java.util.Set;
import java.util.Iterator;
import org.COPASI.*;
import junit.framework.*;


public class Test_RunSteadyStateCalculation extends TestCase
{

    CModel mModel;

    public Test_RunSteadyStateCalculation(String name)
    {
        super(name);
    }

    public CModel createModel()
    {
        try
        {
            CCopasiDataModel.getGlobal().newModel();
        }
        catch(Exception e)
        {
            return null;
        }
        CModel model=CCopasiDataModel.getGlobal().getModel();
        model.setVolumeUnit(CModel.fl);
        model.setTimeUnit(CModel.s);
        model.setQuantityUnit(CModel.fMol);
        CCompartment comp=model.createCompartment("CompartmentA");
        CMetab A=model.createMetabolite("A",comp.getObjectName());
        A.setInitialConcentration(2.0e-4);
        CMetab B=model.createMetabolite("B",comp.getObjectName());
        B.setInitialConcentration(0.0);
        CReaction react=model.createReaction("Decay_1");
        react.addSubstrate(A.getKey());
        react.addProduct(B.getKey());
        react.setReversible(false);
        react.setFunction("Mass action (irreversible)");
        react.setParameterValue("k1",0.5);
        StringStdVector mapping=new StringStdVector();
        mapping.add(react.getChemEq().getSubstrate(0).getMetabolite().getKey());
        react.setParameterMappingVector(react.getFunction().getVariables().getParameter(1).getObjectName(),mapping);;
        model.compileIfNecessary();
        ObjectStdVector changedObjects=new ObjectStdVector();
        changedObjects.add(comp.getObject(new CCopasiObjectName("Reference=InitialVolume")));
        changedObjects.add(A.getObject(new CCopasiObjectName("Reference=InitialConcentration")));
        changedObjects.add(B.getObject(new CCopasiObjectName("Reference=InitialConcentration")));
        changedObjects.add(react.getParameters().getParameter(0).getObject(new CCopasiObjectName("Reference=Value")));
        model.updateInitialValues(changedObjects);
        return model;
    }

    public void setUp()
    {
        this.mModel=createModel();
    }

    public static CSteadyStateTask runSteadyStateCalculation(HashMap<String,Object> problemParameters,HashMap<String,Object> methodParameters)
    {
        CSteadyStateTask steadyStateTask=(CSteadyStateTask)CCopasiDataModel.getGlobal().addTask(CCopasiTask.steadyState);
        if(steadyStateTask==null) return null;
        CSteadyStateProblem steadyStateProblem=(CSteadyStateProblem)steadyStateTask.getProblem();
        if(steadyStateProblem==null) return null;
        Set<String> keySet=problemParameters.keySet();
        for(Iterator<String> it=keySet.iterator();it.hasNext();)
        {
            String key=(String)it.next();
            CCopasiParameter param=steadyStateProblem.getParameter(key);
            if(param==null)
            {
                return null;
            }
            Object o=problemParameters.get(key);
            if(o instanceof Double)
            {
                param.setDblValue(((Double)o).doubleValue());
            }
            else if(o instanceof Integer)
            {
                param.setIntValue(((Integer)o).intValue());
            }
            else if(o instanceof Boolean)
            {
                param.setBoolValue(((Boolean)o).booleanValue());
            }
            else if(o instanceof String)
            {
                param.setStringValue(((String)o));
            }
            else
            {
                System.err.println("Error. Unknown parameter type.");
            }
        }
        CNewtonMethod newtonMethod=(CNewtonMethod)steadyStateTask.getMethod();
        if(newtonMethod==null)
        {
            return null;
        }
        keySet=methodParameters.keySet();
        for(Iterator<String> it=keySet.iterator();it.hasNext();)
        {
            String key=(String)it.next();
            CCopasiParameter param=newtonMethod.getParameter(key);
            if(param==null)
            {
                return null;
            }
            Object o=methodParameters.get(key);
            if(o instanceof Double)
            {
                param.setDblValue(((Double)o).doubleValue());
            }
            else if(o instanceof Integer)
            {
                param.setIntValue(((Integer)o).intValue());
            }
            else if(o instanceof Boolean)
            {
                param.setBoolValue(((Boolean)o).booleanValue());
            }
            else if(o instanceof String)
            {
                param.setStringValue(((String)o));
            }
            else
            {
                System.err.println("Error. Unknown parameter type.");
            }
        }
        boolean result=false;
        try
        {
            if(steadyStateTask.initialize(CCopasiTask.NO_OUTPUT,null)!=false)
            {
                result=steadyStateTask.process(true);
            }
        }
        catch(Exception e)
        {
            System.err.println("ERROR: "+e.getMessage());
        }
        if(!result)
        {
            return null;
        }
        return steadyStateTask;
    }

    public void test_RunSteadyStateCalculation_Newton()
    {
        HashMap<String,Object> problemParameters=new HashMap<String,Object>();
        problemParameters.put("JacobianRequested",new Boolean(true));
        problemParameters.put("StabilityAnalysisRequested",new Boolean(true));
        // iteration limit
        // tolerance
        HashMap<String,Object> methodParameters=new HashMap<String,Object>();
        methodParameters.put("Resolution",new Double(1e-9));
        methodParameters.put("Derivation Factor",new Double(1e-3));
        methodParameters.put("Use Newton",new Boolean(true));
        methodParameters.put("Use Integration",new Boolean(false));
        methodParameters.put("Use Back Integration",new Boolean(false));
        methodParameters.put("Accept Negative Concentrations",new Boolean(false));
        methodParameters.put("Iteration Limit",new Integer(50));
        // objective function
        CSteadyStateTask steadyStateTask=runSteadyStateCalculation(problemParameters,methodParameters);
        assertFalse(steadyStateTask==null);
        assertTrue(steadyStateTask.getResult()==CSteadyStateMethod.foundEquilibrium);
        CEigen eigenvalues=steadyStateTask.getEigenValues();
        assertFalse(eigenvalues==null);
        assertTrue(eigenvalues.getMaxrealpart() <= 0.0);
        assertTrue(eigenvalues.getNnegreal()+eigenvalues.getNreal() == eigenvalues.getR().size());
    }

    public static void main(String[] args) {
        junit.textui.TestRunner.run(Test_RunSteadyStateCalculation.class);
    }

}
