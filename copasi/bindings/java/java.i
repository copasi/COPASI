// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the 
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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 












%include <std_pair.i>
%include <std_map.i>
%include <std_string.i>
%include <exception.i>

/**
 * Make COPASI and wrapper constants Java compile-time
 * constants so they may be used in switch statements.
 */
%include "enumsimple.swg"
%javaconst(1);

%pragma(java) modulecode =
%{
	public static CCopasiTask DowncastCCopasiTask(long cPtr, boolean owner)
	{
		if (cPtr == 0) return null;
		CCopasiTask task = new CCopasiTask(cPtr,false);
		int taskType = task.getType();
		if (taskType == CTaskEnum.Task_steadyState)
		{	
			return new CSteadyStateTask(cPtr, owner);
		} 
		else if (taskType == CTaskEnum.Task_timeCourse)
		{	
			return new CTrajectoryTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.Task_scan)
		{	
			return new CScanTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.Task_fluxMode)
		{	
			return new CEFMTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.Task_optimization)
		{	
			return new COptTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.Task_parameterFitting)
		{	
			return new  CFitTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.Task_mca)
		{	
			return new CMCATask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.Task_lyap)
		{	
			return new CLyapTask(cPtr, owner);
		}		
		else if (taskType == CTaskEnum.Task_tssAnalysis)
		{	
			return new CTSSATask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.Task_sens)
		{	
			return new CSensTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.Task_moieties)
		{	
			return new CMoietiesTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.Task_crosssection)
		{	
			return new CCrossSectionTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.Task_lna)
		{	
			return new CLNATask(cPtr, owner);
		}

		return new CCopasiTask(cPtr, owner);
	}
	
	public static CCopasiMethod DowncastCCopasiMethod(long cPtr, boolean owner)
	{
		if (cPtr == 0) return null;
		CCopasiMethod method = new CCopasiMethod(cPtr,false);
		int methodType = method.getType();
		int methodSubType = method.getSubType();
		
		if (methodType == CTaskEnum.Task_parameterFitting)
		{
			return new COptMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.Task_lyap)
		{
			return new CLyapMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.Task_mca)
		{
			return new CMCAMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.Task_tssAnalysis)
		{
			return new  CTSSAMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.Task_moieties)
		{
			return new CMoietiesMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.Task_crosssection)
		{
			return new CCrossSectionMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.Task_lna)
		{
			return new CLNAMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.Task_fluxMode)
		{
			return new CEFMMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.Task_steadyState)
		{
			if (methodSubType == CTaskEnum.Method_Newton)
				return new CNewtonMethod(cPtr, owner);
				
			return new CSteadyStateMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.Task_optimization)
		{
			return new COptMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.Task_scan)
		{
			return new CScanMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.Task_sens)
		{
			return new CSensMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.Task_timeCourse)
		{
			return new CTrajectoryMethod(cPtr, owner);
		}
		
		//RandomSearch,
		//RandomSearchMaster,
		//SimulatedAnnealing,
		//CoranaWalk,
		//DifferentialEvolution,
		//GeneticAlgorithm,
		//EvolutionaryProgram,
		//SteepestDescent,
		//HybridGASA,
		//GeneticAlgorithmSR,
		//HookeJeeves,
		//LevenbergMarquardt,
		//NelderMead,
		//SRES,
		//Statistics,
		//ParticleSwarm,
		//Praxis,
		//TruncatedNewton,
		//Newton,
		//deterministic,
		//LSODAR,
		//directMethod,
		//stochastic,
		//tauLeap,
		//adaptiveSA,
		//hybrid,
		//hybridLSODA,
		//DsaLsodar,
		//tssILDM,
		//tssILDMModified,
		//tssCSP,
		//mcaMethodReder,
		//scanMethod,
		//lyapWolf,
		//sensMethod,
		//stoichiometricStabilityAnalysis,
		//EFMAlgorithm,
		//EFMBitPatternTreeAlgorithm,
		//EFMBitPatternAlgorithm,
		//Householder,
		//crossSectionMethod,
		//linearNoiseApproximation
		
		return new CCopasiMethod(cPtr,owner);
	}
	
	public static CCopasiProblem DowncastCCopasiProblem(long cPtr, boolean owner)
	{
		if (cPtr == 0) return null;
		CCopasiProblem problem = new CCopasiProblem(cPtr,false);
		int problemType = problem.getType();
		if (problemType == CTaskEnum.Task_steadyState)
		{	
			return new CSteadyStateProblem(cPtr, owner);
		} 
		else if (problemType == CTaskEnum.Task_timeCourse)
		{	
			return new CTrajectoryProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.Task_scan)
		{	
			return new CScanProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.Task_fluxMode)
		{	
			return new CEFMProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.Task_optimization)
		{	
			return new COptProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.Task_parameterFitting)
		{	
			return new CFitProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.Task_mca)
		{	
			return new CMCAProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.Task_lyap)
		{	
			return new CLyapProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.Task_tssAnalysis)
		{	
			return new CTSSAProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.Task_sens)
		{	
			return new CSensProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.Task_moieties)
		{	
			return new CMoietiesProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.Task_crosssection)
		{	
			return new CCrossSectionProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.Task_lna)
		{	
			return new CLNAProblem(cPtr, owner);
		}

		return new CCopasiProblem(cPtr, owner);
	}
	
	public static COptItem DowncastCOptItem(long cPtr, boolean owner)
	{
		if (cPtr == 0) return null;
		COptItem co = new COptItem(cPtr,false);
		String name = co.getObjectName();
		
		if (name.equals("FitItem"))
			return new CFitItem(cPtr, owner);
		if (name.equals("FitConstraint"))
			return new CFitConstraint(cPtr, owner);				
		return new COptItem(cPtr, owner);
	}
	
	public static CCopasiParameterGroup DowncastCCopasiParameterGroup(long cPtr, boolean owner)
	{
		if (cPtr == 0) return null;
	
		CCopasiParameterGroup co = new CCopasiParameterGroup(cPtr,false);
		String type = co.getObjectType();
		String name = co.getObjectName();
		
		if (name.equals("OptimizationItem"))
			return new COptItem(cPtr, owner);		
		if (name.equals("FitItem"))
			return new CFitItem(cPtr, owner);
		if (name.equals("FitConstraint"))
			return new CFitConstraint(cPtr, owner);				
		if (name.equals("Object Map"))
			return new CExperimentObjectMap(cPtr, owner);
		if (name.equals("Experiment Set"))
			return new CExperimentSet(cPtr, owner);
%}
#ifdef COPASI_CROSSVALIDATION
%pragma(java) modulecode =
%{
		if (name.equals("Validation Set"))
			return new CCrossValidationSet(cPtr, owner);
%}
#endif
%pragma(java) modulecode =
%{				
		return new CCopasiParameterGroup(cPtr, owner);
	}
	
	
	public static CDataObject DowncastCDataObject(long cPtr, boolean owner)
	{
		if (cPtr == 0) return null;
	
		CDataObject co = new CDataObject(cPtr,false);
		String type = co.getObjectType();
		
		if (type.equals("Metabolite"))
		{
			return new CMetab(cPtr, owner);
		}
		else if (type.equals("Modification"))
		{
			return new CModification(cPtr, owner);
		}
		else if (type.equals("Timer"))
		{
			return new CCopasiTimer(cPtr, owner);
		}
		else if (type.equals("Creator"))
		{
			return new CCreator(cPtr, owner);
		}
		else if (type.equals("BiologicalDescription"))
		{
			return new CBiologicalDescription(cPtr, owner);
		}
		else if (type.equals("CMIRIAMInfo"))
		{
			return new CMIRIAMInfo(cPtr, owner);
		}
		else if (type.equals("Chemical Equation"))
		{
			return new CChemEq(cPtr, owner);
		}
		else if (type.equals("Compartment"))
		{
			return new CCompartment(cPtr, owner);
		}
		else if (type.equals("EventAssignment"))
		{
			return new CEventAssignment(cPtr, owner);
		}
		else if (type.equals("Event"))
		{
			return new CEvent(cPtr, owner);
		}
		else if (type.equals("Function"))
		{
		    CEvaluationTree temp = new CEvaluationTree(cPtr,false);
			if (temp.isFunction())
				return new CFunction(cPtr, owner);
			else 
				return new CEvaluationTree(cPtr, owner);
		}		
		else if (type.equals("FunctionDB"))
		{
			return new CFunctionDB(cPtr, owner);
		}		
		else if (type.equals("Variable Description"))
		{
			return new CFunctionParameters(cPtr, owner);
		}		
		else if (type.equals("Variable"))
		{
			return new CFunctionParameter(cPtr, owner);
		}		
		
		else if (type.equals("Model"))
		{
			return new CModel(cPtr, owner);
		}
		else if (type.equals("ModelValue"))
		{
			return new CModelValue(cPtr, owner);
		}
		else if (type.equals("ModelParameterSet"))
		{
			return new CModelParameterSet(cPtr, owner);
		}
		else if (type.equals("Moiety"))
		{
			return new CMoiety(cPtr, owner);
		}
		else if (type.equals("Reaction"))
		{
			return new CReaction(cPtr, owner);
		}
		else if (type.equals("CN"))
		{
			return new CDataModel(cPtr, owner);
		}
		else if (type.equals("PlotItem"))
		{
			return new CPlotItem(cPtr, owner);
		}
		else if (type.equals("ReportDefinition"))
		{
			return new CReportDefinition(cPtr, owner);
		}
		else if (type.equals("Array"))
		{
			return new CDataArray(cPtr, owner);
		}
		else if (type.equals("Method"))
		{
			return DowncastCCopasiMethod(cPtr, owner);		    
		}
		else if (type.equals("Parameter"))
		{
			return new CCopasiParameter(cPtr, owner);
		}
		else if (type.equals("Fitted Point"))
		{
			return new CFittingPoint(cPtr, owner);
		}
		
		else if (type.equals("ParameterGroup"))
		{
			return DowncastCCopasiParameterGroup(cPtr, owner);			
		}
                /*else if (type.equals("ScanItem"))
		{
			return CScanItem(cPtr, owner);
                }
		else if (type.equals("PlotItem"))
		{
			return CPlotItem(cPtr, owner);
                }*/
		else if (type.equals("Problem"))
		{
			return DowncastCCopasiProblem(cPtr, owner);		    
		}
		else if (type.equals("Task"))
		{
			return DowncastCCopasiTask(cPtr, owner);		    
		}
		else if (type.equals("ModelParameterSet"))
		{
			return new CModelParameterSet(cPtr, owner);		    
		}		
		else
		{
			if (System.getenv("COPASI_JAVA_DEBUG") != null)
			System.err.println("WRAPPER: encountered unwrapped type: '" + type + "'");
		}
		return new CDataObject(cPtr, owner);
	}

  
  public static CModelParameter DowncastCModelParameter(long cPtr, boolean owner)
    {
      if (cPtr == 0) return null;
      
      CModelParameter temp = new CModelParameter (cPtr, false);
      if (temp.asGroup() != null)
        return new CModelParameterGroup(cPtr, owner);
      if (temp.asSpecies() != null)
        return new CModelParameterSpecies(cPtr, owner);
      if (temp.asCompartment() != null)
        return new CModelParameterCompartment(cPtr, owner);
      if (temp.asReactionParameter() != null)
        return new CModelParameterReactionParameter(cPtr, owner);
        
      return new CModelParameter(cPtr, owner);
    }
	
    public static CCopasiParameter DowncastCCopasiParameter(long cPtr, boolean owner)
    {
      if (cPtr == 0) return null;
	  
      CCopasiParameter temp = new CCopasiParameter(cPtr, false);
	  CDataObject co = temp.toObject();
	  if (co != null)
	  	return (CCopasiParameter)DowncastCDataObject(cPtr, owner);	
	  return new CCopasiParameter(cPtr, owner);	
    }
	
	   public static CObjectInterface DowncastCObjectInterface(long cPtr, boolean owner)
    {
      if (cPtr == 0) return null;
	  
      CObjectInterface temp = new CObjectInterface(cPtr, false);
	  CDataObject co = temp.toObject();
	  if (co != null)
	  	return DowncastCDataObject(cPtr, owner);	
	  return new CObjectInterface(cPtr, owner);	
    }
	
	public static CDataContainer DowncastCDataContainer(long cPtr, boolean owner)
    {
      if (cPtr == 0) return null;
	  
      CDataContainer temp = new CDataContainer(cPtr, false);
	  String name = temp.getObjectName();
	  String type = temp.getObjectType();
	  
	  if (name.equals("CN") && type.equals("CN"))
		return new CRootContainer(cPtr, owner);
	  if (name.equals("CN") && type.equals("Root"))
		return new CDataModel(cPtr, owner);
	  
	  CDataObject co = temp.toObject();
	  if (co != null)
	  	return (CDataContainer)DowncastCDataObject(cPtr, owner);	
	  return new CDataContainer(cPtr, owner);	
    }

	public static CEvaluationTree DowncastCEvaluationTree(long cPtr, boolean owner)
    {
      if (cPtr == 0) return null;
	  
      CEvaluationTree temp = new CEvaluationTree(cPtr, false);	
	  if (temp.isFunction())
	  	return new CFunction(cPtr, owner);	
	  return new CEvaluationTree(cPtr, owner);	
    }

	
	
%}

/**
 * Convert CModelParameter objects into the most specific object possible.
 */
%typemap("javaout") CModelParameter*
{
  return COPASI.DowncastCModelParameter($jnicall, $owner);
}

/**
 * Convert CEvaluationTree objects into the most specific object possible.
 */
%typemap("javaout") CEvaluationTree*
{
  return COPASI.DowncastCEvaluationTree($jnicall, $owner);
}


/**
 * Convert CDataObject objects into the most specific object possible.
 */
%typemap("javaout") CDataObject*
{
  return COPASI.DowncastCDataObject($jnicall, $owner);
}

/**
 * Convert CDataObject objects into the most specific object possible.
 */
%typemap("javaout") CCopasiParameter*
{
  return COPASI.DowncastCCopasiParameter($jnicall, $owner);
}


/**
 * Convert CDataObject objects into the most specific object possible.
 */
%typemap("javaout") CDataContainer*
{
  return COPASI.DowncastCDataContainer($jnicall, $owner);
}

/**
 * Convert CDataObject objects into the most specific object possible.
 */
%typemap("javaout") CObjectInterface*
{
  return COPASI.DowncastCObjectInterface($jnicall, $owner);
}

/**
 * Convert CCopasiTask objects into the most specific object possible.
 */
%typemap("javaout") CCopasiTask*
{
  return COPASI.DowncastCCopasiTask($jnicall, $owner);
}

/**
 * Convert CCopasiMethod objects into the most specific object possible.
 */
%typemap("javaout") CCopasiMethod*
{
  return COPASI.DowncastCCopasiMethod($jnicall, $owner);
}

/**
 * Convert CCopasiProblem objects into the most specific object possible.
 */
%typemap("javaout") CCopasiProblem*
{
  return COPASI.DowncastCCopasiProblem($jnicall, $owner);
}

/**
 * Convert COptItem objects into the most specific object possible.
 */
%typemap("javaout") COptItem*, COptItem&, COptItem
{
  return COPASI.DowncastCOptItem($jnicall, $owner);
}

void initCopasi();

%pragma(java) jniclasscode=
%{
  static
  {
    try
    {
      System.loadLibrary("CopasiJava");
    }
    catch(UnsatisfiedLinkError e)
    {
      System.err.println("Native code library failed to load. \n" + e);
      System.exit(1);
    }
		initCopasi();
  }
%}

%javaexception("java.lang.Exception") CCopasiTask::process {
   try
   {
     $action
   }
   catch (std::exception &e)
   {
     jclass clazz = jenv->FindClass("java/lang/Exception");
     jenv->ThrowNew(clazz, e.what());
     return $null;
   }
   catch(CCopasiException& e)
   {
     jclass clazz = jenv->FindClass("java/lang/Exception");
     jenv->ThrowNew(clazz, e.getMessage().getText().c_str());
     return $null;
   }
}


%javaexception("java.lang.Exception") CDataModel::importSBML {
   try
   {
     $action
   }
   catch (std::exception &e)
   {
     jclass clazz = jenv->FindClass("java/lang/Exception");
     jenv->ThrowNew(clazz, e.what());
     return $null;
   }
   catch(CCopasiException& e)
   {
     jclass clazz = jenv->FindClass("java/lang/Exception");
     jenv->ThrowNew(clazz, e.getMessage().getText().c_str());
     return $null;
   }
}


%javaexception("java.lang.Exception") CDataModel::newModel {
   try
   {
     $action
   }
   catch (std::exception &e)
   {
     jclass clazz = jenv->FindClass("java/lang/Exception");
     jenv->ThrowNew(clazz, e.what());
     return $null;
   }
   catch(CCopasiException& e)
   {
     jclass clazz = jenv->FindClass("java/lang/Exception");
     jenv->ThrowNew(clazz, e.getMessage().getText().c_str());
     return $null;
   }
}

%javaexception("java.lang.Exception") CDataModel::importSBMLFromString {
   try
   {
     $action
   }
   catch (std::exception &e)
   {
     jclass clazz = jenv->FindClass("java/lang/Exception");
     jenv->ThrowNew(clazz, e.what());
     return $null;
   }
   catch(CCopasiException& e)
   {
     jclass clazz = jenv->FindClass("java/lang/Exception");
     jenv->ThrowNew(clazz, e.getMessage().getText().c_str());
     return $null;
   }
}

%javaexception("java.lang.Exception") CDataModel::exportSBMLToString {
   try
   {
     $action
   }
   catch (std::exception &e)
   {
     jclass clazz = jenv->FindClass("java/lang/Exception");
     jenv->ThrowNew(clazz, e.what());
     return $null;
   }
   catch(CCopasiException& e)
   {
     jclass clazz = jenv->FindClass("java/lang/Exception");
     jenv->ThrowNew(clazz, e.getMessage().getText().c_str());
     return $null;
   }
}

%javaexception("java.lang.Exception") CDataModel::exportSBML {
   try
   {
     $action
   }
   catch (std::exception &e)
   {
     jclass clazz = jenv->FindClass("java/lang/Exception");
     jenv->ThrowNew(clazz, e.what());
     return $null;
   }
   catch(CCopasiException& e)
   {
     jclass clazz = jenv->FindClass("java/lang/Exception");
     jenv->ThrowNew(clazz, e.getMessage().getText().c_str());
     return $null;
   }
}


%include "../swig/copasi.i"


