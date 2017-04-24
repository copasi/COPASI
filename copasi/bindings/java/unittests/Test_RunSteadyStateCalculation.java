// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
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

package org.COPASI.unittests;

import java.lang.Math;
import java.util.HashMap;
import java.util.Set;
import java.util.Iterator;
import org.COPASI.*;
import junit.framework.*;


public class Test_RunSteadyStateCalculation extends TestCase
{

    CDataModel mDataModel;
    CModel mModel;

    public Test_RunSteadyStateCalculation(String name)
    {
        super(name);
    }

    public CModel createModel(CDataModel dataModel)
    {
        try
        {
            dataModel.newModel();
        }
        catch(Exception e)
        {
            return null;
        }
        CModel model=dataModel.getModel();
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
        changedObjects.add(comp.getObject(new CCommonName("Reference=InitialVolume")));
        changedObjects.add(A.getObject(new CCommonName("Reference=InitialConcentration")));
        changedObjects.add(B.getObject(new CCommonName("Reference=InitialConcentration")));
        changedObjects.add(react.getParameters().getParameter(0).getObject(new CCommonName("Reference=Value")));
        model.updateInitialValues(changedObjects);
        return model;
    }

    public void setUp()
    {
        mDataModel=CRootContainer.addDatamodel();
        this.mModel=createModel(mDataModel);
    }

    public static CSteadyStateTask runSteadyStateCalculation(CDataModel dataModel,HashMap<String,Object> problemParameters,HashMap<String,Object> methodParameters)
    {
        CSteadyStateTask steadyStateTask=(CSteadyStateTask)dataModel.addTask(CCopasiTask.steadyState);
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
           result=steadyStateTask.process(true);
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
        CSteadyStateTask steadyStateTask=runSteadyStateCalculation(mDataModel,problemParameters,methodParameters);
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
