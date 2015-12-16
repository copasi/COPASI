// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual 
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
		if (taskType == CTaskEnum.steadyState)
		{	
			return new CSteadyStateTask(cPtr, owner);
		} 
		else if (taskType == CTaskEnum.timeCourse)
		{	
			return new CTrajectoryTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.scan)
		{	
			return new CScanTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.fluxMode)
		{	
			return new CEFMTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.optimization)
		{	
			return new COptTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.parameterFitting)
		{	
			return new  CFitTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.mca)
		{	
			return new CMCATask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.lyap)
		{	
			return new CLyapTask(cPtr, owner);
		}		
		else if (taskType == CTaskEnum.tssAnalysis)
		{	
			return new CTSSATask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.sens)
		{	
			return new CSensTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.moieties)
		{	
			return new CMoietiesTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.crosssection)
		{	
			return new CCrossSectionTask(cPtr, owner);
		}
		else if (taskType == CTaskEnum.lna)
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
		
		if (methodType == CTaskEnum.parameterFitting)
		{
			return new COptMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.lyap)
		{
			return new CLyapMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.mca)
		{
			return new CMCAMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.tssAnalysis)
		{
			return new  CTSSAMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.moieties)
		{
			return new CMoietiesMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.crosssection)
		{
			return new CCrossSectionMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.lna)
		{
			return new CLNAMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.fluxMode)
		{
			return new CEFMMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.steadyState)
		{
			if (methodSubType == CTaskEnum.Newton)
				return new CNewtonMethod(cPtr, owner);
				
			return new CSteadyStateMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.optimization)
		{
			return new COptMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.scan)
		{
			return new CScanMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.sens)
		{
			return new CSensMethod(cPtr, owner);
		}
		else if (methodType == CTaskEnum.timeCourse)
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
		if (problemType == CTaskEnum.steadyState)
		{	
			return new CSteadyStateProblem(cPtr, owner);
		} 
		else if (problemType == CTaskEnum.timeCourse)
		{	
			return new CTrajectoryProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.scan)
		{	
			return new CScanProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.fluxMode)
		{	
			return new CEFMProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.optimization)
		{	
			return new COptProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.parameterFitting)
		{	
			return new CFitProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.mca)
		{	
			return new CMCAProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.lyap)
		{	
			return new CLyapProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.tssAnalysis)
		{	
			return new CTSSAProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.sens)
		{	
			return new CSensProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.moieties)
		{	
			return new CMoietiesProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.crosssection)
		{	
			return new CCrossSectionProblem(cPtr, owner);
		}
		else if (problemType == CTaskEnum.lna)
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
	
	
	public static CCopasiObject DowncastCCopasiObject(long cPtr, boolean owner)
	{
		if (cPtr == 0) return null;
	
		CCopasiObject co = new CCopasiObject(cPtr,false);
		String type = co.getObjectType();
		
		if (type.equals("Metabolite"))
		{
			return new CMetab(cPtr, owner);
		}
		else if (type.equals("Modification"))
		{
			return new CModification(cPtr, owner);
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
			return new CCopasiDataModel(cPtr, owner);
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
			return new CArrayAnnotation(cPtr, owner);
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
		return new CCopasiObject(cPtr, owner);
	}

    public static CCopasiParameter DowncastCCopasiParameter(long cPtr, boolean owner)
    {
      if (cPtr == 0) return null;
	  
      CCopasiParameter temp = new CCopasiParameter(cPtr, false);
	  CCopasiObject co = temp.toObject();
	  if (co != null)
	  	return (CCopasiParameter)DowncastCCopasiObject(cPtr, owner);	
	  return new CCopasiParameter(cPtr, owner);	
    }
	
	   public static CObjectInterface DowncastCObjectInterface(long cPtr, boolean owner)
    {
      if (cPtr == 0) return null;
	  
      CObjectInterface temp = new CObjectInterface(cPtr, false);
	  CCopasiObject co = temp.toObject();
	  if (co != null)
	  	return DowncastCCopasiObject(cPtr, owner);	
	  return new CObjectInterface(cPtr, owner);	
    }
	
	public static CCopasiContainer DowncastCCopasiContainer(long cPtr, boolean owner)
    {
      if (cPtr == 0) return null;
	  
      CCopasiContainer temp = new CCopasiContainer(cPtr, false);
	  String name = temp.getObjectName();
	  String type = temp.getObjectType();
	  
	  if (name.equals("CN") && type.equals("CN"))
		return new CCopasiRootContainer(cPtr, owner);
	  if (name.equals("CN") && type.equals("Root"))
		return new CCopasiDataModel(cPtr, owner);
	  
	  CCopasiObject co = temp.toObject();
	  if (co != null)
	  	return (CCopasiContainer)DowncastCCopasiObject(cPtr, owner);	
	  return new CCopasiContainer(cPtr, owner);	
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
 * Convert CEvaluationTree objects into the most specific object possible.
 */
%typemap("javaout") CEvaluationTree*
{
  return COPASI.DowncastCEvaluationTree($jnicall, $owner);
}


/**
 * Convert CCopasiObject objects into the most specific object possible.
 */
%typemap("javaout") CCopasiObject*
{
  return COPASI.DowncastCCopasiObject($jnicall, $owner);
}

/**
 * Convert CCopasiObject objects into the most specific object possible.
 */
%typemap("javaout") CCopasiParameter*
{
  return COPASI.DowncastCCopasiParameter($jnicall, $owner);
}


/**
 * Convert CCopasiObject objects into the most specific object possible.
 */
%typemap("javaout") CCopasiContainer*
{
  return COPASI.DowncastCCopasiContainer($jnicall, $owner);
}

/**
 * Convert CCopasiObject objects into the most specific object possible.
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


%javaexception("java.lang.Exception") CCopasiDataModel::importSBML {
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


%javaexception("java.lang.Exception") CCopasiDataModel::newModel {
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

%javaexception("java.lang.Exception") CCopasiDataModel::importSBMLFromString {
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

%javaexception("java.lang.Exception") CCopasiDataModel::exportSBMLToString {
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

%javaexception("java.lang.Exception") CCopasiDataModel::exportSBML {
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


