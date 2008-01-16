// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/java/unittests/Test_RunScan.java,v $ 
//   $Revision: 1.6 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/01/16 09:03:13 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

package org.COPASI.unittests;

import java.lang.Math;
import java.util.HashMap;
import java.util.Set;
import java.util.Vector;
import java.util.Iterator;
import org.COPASI.*;
import junit.framework.*;


public class Test_RunScan extends TestCase
{

    CModel mModel;

   public Test_RunScan(String name)
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
    CModelValue fixedModelValue=model.createModelValue("R",2.0);
    CModelValue variableModelValue=model.createModelValue("K");
    variableModelValue.setStatus(CModelEntity.ODE);
    String s=fixedModelValue.getObject(new CCopasiObjectName("Reference=Value")).getCN().getString();
    s="<"+s+">^2";
    variableModelValue.setExpression(s);
    variableModelValue.setInitialValue(0.0);
    model.compileIfNecessary();
    ObjectStdVector changedObjects=new ObjectStdVector();
    changedObjects.add(fixedModelValue.getObject(new CCopasiObjectName("Reference=InitialValue")));
    changedObjects.add(variableModelValue.getObject(new CCopasiObjectName("Reference=InitialValue")));
    model.updateInitialValues(changedObjects);
    return model;
   }
    
    public void setUp()
    {
        this.mModel=createModel();
    }

    public static CScanTask runScan(int subTask,Vector<CCopasiParameterGroup> scanItems,boolean adjustInitialValues)
    {
        CScanTask scanTask=(CScanTask)CCopasiDataModel.getGlobal().addTask(CCopasiTask.scan);
        if(scanTask==null) return null;
        CScanProblem scanProblem=(CScanProblem)scanTask.getProblem();
        scanProblem.setSubtask(subTask);
        scanProblem.setAdjustInitialConditions(adjustInitialValues);
        if(scanProblem==null) return null;
        CCopasiParameterGroup problemScanItems=scanProblem.getGroup("ScanItems");
        if(problemScanItems==null) return null;
        for(Iterator<CCopasiParameterGroup> it=scanItems.iterator();it.hasNext();)
        {
           CCopasiParameterGroup scanItem=(CCopasiParameterGroup)it.next();
           problemScanItems.addParameter(scanItem);
        }
        boolean result=false;
        try
        {
          result=scanTask.process(true,CCopasiTask.NO_OUTPUT);
        }
        catch(Exception e)
        {
            System.err.println("ERROR: "+e.getMessage());
        }
        if(!result)
        {
            return null;
        }
        return scanTask;
    }

    public void test_Scan_Repeat()
    {
        // set up the time course task
        CTrajectoryTask task=null;
        for(int  x=0;x < CCopasiDataModel.getGlobal().getTaskList().size();x++)
        {
            if(CCopasiDataModel.getGlobal().getTask(x).getType()==CCopasiTask.timeCourse)
            {
                task=(CTrajectoryTask)CCopasiDataModel.getGlobal().getTask(x);
            }
        }
        assertFalse(task==null);
        task.setMethodType(CCopasiMethod.deterministic);
        CCopasiProblem problem=task.getProblem();
        assertFalse(problem==null);
        CCopasiParameter parameter=problem.getParameter("StepSize");
        assertFalse(parameter==null);
        parameter.setDblValue(0.001);
        parameter=problem.getParameter("Duration");
        assertFalse(parameter==null);
        parameter.setDblValue(10.0);
        // we don't need to set method parameters
        // we just use the default
        //CCopasiMethod method=task.getMethod();
        //assertFalse(method==null);
        // create a report
        CReportDefinitionVector reportDefs=CCopasiDataModel.getGlobal().getReportDefinitionList();
        assertFalse(reportDefs==null);
        CReportDefinition repDef=reportDefs.createReportDefinition("htmlConc","value table in HTML format");
        repDef.setIsTable(false);
        assertFalse(repDef==null);
        CCopasiStaticString htmlHeader=new CCopasiStaticString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">\n<body>\n<table>\n");
        CCopasiStaticString htmlFooter=new CCopasiStaticString("</table>\n</body>\n</html>\n");
        ReportItemVector header=repDef.getHeaderAddr(); 
        assertFalse(header==null);
        header.add(new CRegisteredObjectName(htmlHeader.getCN().getString()));
        ReportItemVector footer=repDef.getFooterAddr(); 
        assertFalse(footer==null);
        footer.add(new CRegisteredObjectName(htmlFooter.getCN().getString()));
        ReportItemVector body=repDef.getBodyAddr(); 
        assertFalse(body==null);
        CModel model=CCopasiDataModel.getGlobal().getModel();
        assertFalse(model==null);
        CCopasiObject timeObject=model.getObject(new CCopasiObjectName("Reference=Time"));
        assertFalse(timeObject==null);
        body.add(new CRegisteredObjectName(new CCopasiStaticString("<tr>\n<td>").getCN().getString()));
        body.add(new CRegisteredObjectName(timeObject.getCN().getString()));
        body.add(new CRegisteredObjectName(new CCopasiStaticString("</td>\n").getCN().getString()));
        long i,iMax=model.getNumModelValues();
        for(i=0;i<iMax;++i)
        {
            body.add(new CRegisteredObjectName(new CCopasiStaticString("<td>").getCN().getString()));
            CModelValue mv=model.getModelValue(i);
            assertFalse(mv==null);
            CCopasiObject valueObject=mv.getObject(new CCopasiObjectName("Reference=Value"));
            assertFalse(valueObject==null);
            body.add(new CRegisteredObjectName(valueObject.getCN().getString()));
            body.add(new CRegisteredObjectName(new CCopasiStaticString("</td>\n").getCN().getString()));
        }
        body.add(new CRegisteredObjectName(new CCopasiStaticString("</tr>\n").getCN().getString()));
        repDef.setTaskType(CCopasiTask.timeCourse);
        CReport report=task.getReport();
        assertFalse(report==null);
        report.setReportDefinition(repDef);
        report.setAppend(false);
        report.setTarget("table.xhtml");
        //CCopasiDataModel.getGlobal().saveModel("testModel.cps",true);
        try
        {
          task.process(true);
        }
        catch(Exception e)
        {
            assertFalse(true);
        }
        report.setReportDefinition(null);
        report.setTarget("");
        // store the result for R and K and set R and K
        // back to their initial values
        CModelValue mv=CCopasiDataModel.getGlobal().getModel().getModelValue("R");
        assertFalse(mv==null);
        double valueR=mv.getValue();
        mv=CCopasiDataModel.getGlobal().getModel().getModelValue("K");
        assertFalse(mv==null);
        double valueK=mv.getValue();
        CCopasiDataModel.getGlobal().getModel().applyInitialValues();
        // now we set the length of the time course to 1/10th
        // and do 10 repetitions and let the scan use the current values
        // instead of the initial values
        // then we should end up with the same result for R and K
        parameter=problem.getParameter("Duration");
        assertFalse(parameter==null);
        parameter.setDblValue(1.0);

        Vector<CCopasiParameterGroup> scanItems=new Vector<CCopasiParameterGroup>();
        boolean adjustInitialConditions=true;
        CCopasiParameterGroup parameterGroup=new CCopasiParameterGroup("scanItems");
        parameterGroup.addParameter("Number of steps", CCopasiParameter.UINT);
        parameterGroup.getParameter("Number of steps").setUIntValue(10);
        parameterGroup.addParameter("Type", CCopasiParameter.UINT);
        parameterGroup.getParameter("Type").setUIntValue(CScanProblem.SCAN_REPEAT);
        parameterGroup.addParameter("Object", CCopasiParameter.CN);
        parameterGroup.getParameter("Object").setStringValue("");
        scanItems.add(parameterGroup);
        CScanTask optTask=runScan(CCopasiTask.timeCourse,scanItems,adjustInitialConditions);
        assertFalse(optTask==null);
        
        mv=CCopasiDataModel.getGlobal().getModel().getModelValue("R");
        assertFalse(mv==null);
        assertTrue((mv.getValue()-valueR)/valueR < 1e-6);
        mv=CCopasiDataModel.getGlobal().getModel().getModelValue("K");
        assertFalse(mv==null);
        assertTrue((mv.getValue()-valueK)/valueK < 1e-6);

    }

  public static void main(String[] args) {
    junit.textui.TestRunner.run(Test_RunScan.class);
  }

}
