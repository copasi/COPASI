// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
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
		if (taskType == CCopasiTask.steadyState)
		{	
			return new CSteadyStateTask(cPtr, owner);
		} 
		else if (taskType == CCopasiTask.timeCourse)
		{	
			return new CTrajectoryTask(cPtr, owner);
		}
		else if (taskType == CCopasiTask.scan)
		{	
			return new CScanTask(cPtr, owner);
		}
		else if (taskType == CCopasiTask.fluxMode)
		{	
			return new CEFMTask(cPtr, owner);
		}
		else if (taskType == CCopasiTask.optimization)
		{	
			return new COptTask(cPtr, owner);
		}
		else if (taskType == CCopasiTask.parameterFitting)
		{	
			return new  CFitTask(cPtr, owner);
		}
		else if (taskType == CCopasiTask.mca)
		{	
			return new CMCATask(cPtr, owner);
		}
		else if (taskType == CCopasiTask.lyap)
		{	
			return new CLyapTask(cPtr, owner);
		}		
		else if (taskType == CCopasiTask.tssAnalysis)
		{	
			return new CTSSATask(cPtr, owner);
		}
		else if (taskType == CCopasiTask.sens)
		{	
			return new CSensTask(cPtr, owner);
		}
		else if (taskType == CCopasiTask.moieties)
		{	
			return new CMoietiesTask(cPtr, owner);
		}
		else if (taskType == CCopasiTask.crosssection)
		{	
			return new CCrossSectionTask(cPtr, owner);
		}
		else if (taskType == CCopasiTask.lna)
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
		
		if (methodType == CCopasiTask.parameterFitting)
		{
			return new CFitMethod(cPtr, owner);
		}
		else if (methodType == CCopasiTask.lyap)
		{
			return new CLyapMethod(cPtr, owner);
		}
		else if (methodType == CCopasiTask.mca)
		{
			return new CMCAMethod(cPtr, owner);
		}
		else if (methodType == CCopasiTask.tssAnalysis)
		{
			return new  CTSSAMethod(cPtr, owner);
		}
		else if (methodType == CCopasiTask.moieties)
		{
			return new CMoietiesMethod(cPtr, owner);
		}
		else if (methodType == CCopasiTask.crosssection)
		{
			return new CCrossSectionMethod(cPtr, owner);
		}
		else if (methodType == CCopasiTask.lna)
		{
			return new CLNAMethod(cPtr, owner);
		}
		else if (methodType == CCopasiTask.fluxMode)
		{
			return new CEFMMethod(cPtr, owner);
		}
		else if (methodType == CCopasiTask.steadyState)
		{
			if (methodSubType == CCopasiMethod.Newton)
				return new CNewtonMethod(cPtr, owner);
				
			return new CSteadyStateMethod(cPtr, owner);
		}
		else if (methodType == CCopasiTask.optimization)
		{
			return new COptMethod(cPtr, owner);
		}
		else if (methodType == CCopasiTask.scan)
		{
			return new CScanMethod(cPtr, owner);
		}
		else if (methodType == CCopasiTask.sens)
		{
			return new CSensMethod(cPtr, owner);
		}
		else if (methodType == CCopasiTask.timeCourse)
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
		if (problemType == CCopasiTask.steadyState)
		{	
			return new CSteadyStateProblem(cPtr, owner);
		} 
		else if (problemType == CCopasiTask.timeCourse)
		{	
			return new CTrajectoryProblem(cPtr, owner);
		}
		else if (problemType == CCopasiTask.scan)
		{	
			return new CScanProblem(cPtr, owner);
		}
		else if (problemType == CCopasiTask.fluxMode)
		{	
			return new CEFMProblem(cPtr, owner);
		}
		else if (problemType == CCopasiTask.optimization)
		{	
			return new COptProblem(cPtr, owner);
		}
		else if (problemType == CCopasiTask.parameterFitting)
		{	
			return new CFitProblem(cPtr, owner);
		}
		else if (problemType == CCopasiTask.mca)
		{	
			return new CMCAProblem(cPtr, owner);
		}
		else if (problemType == CCopasiTask.lyap)
		{	
			return new CLyapProblem(cPtr, owner);
		}
		else if (problemType == CCopasiTask.tssAnalysis)
		{	
			return new CTSSAProblem(cPtr, owner);
		}
		else if (problemType == CCopasiTask.sens)
		{	
			return new CSensProblem(cPtr, owner);
		}
		else if (problemType == CCopasiTask.moieties)
		{	
			return new CMoietiesProblem(cPtr, owner);
		}
		else if (problemType == CCopasiTask.crosssection)
		{	
			return new CCrossSectionProblem(cPtr, owner);
		}
		else if (problemType == CCopasiTask.lna)
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
		else
		{
			if (System.getenv("COPASI_JAVA_DEBUG") != null)
			System.err.println("WRAPPER: encountered unwrapped type: '" + type + "'");
		}
		return new CCopasiObject(cPtr, owner);
	}

    public static CCopasiParameter DowncastCCopasiParameter(long cPtr, boolean owner)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}


%typemap(jni) CCopasiTask* CCopasiDataModel::addTask "jobject"
%typemap(jtype) CCopasiTask* CCopasiDataModel::addTask "CCopasiTask"
%typemap(jstype) CCopasiTask* CCopasiDataModel::addTask "CCopasiTask"
%typemap(javaout) CCopasiTask* CCopasiDataModel::addTask
{
  return $jnicall;
}
%typemap(out) CCopasiTask* CCopasiDataModel::addTask
{
    $result = DownCast_CCopasiTask(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}

%typemap(jni) CCopasiTask* CCopasiDataModel::getTask "jobject"
%typemap(jtype) CCopasiTask* CCopasiDataModel::getTask "CCopasiTask"
%typemap(jstype) CCopasiTask* CCopasiDataModel::getTask "CCopasiTask"
%typemap(javaout) CCopasiTask* CCopasiDataModel::getTask
{
  return $jnicall;
}
%typemap(out) CCopasiTask* CCopasiDataModel::getTask
{
    $result = DownCast_CCopasiTask(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
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
  return $jnicall;
}
%typemap(out) CCopasiObject* CKeyFactory::get
{
    $result = DownCast_CCopasiObject(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}


%typemap(jni) CCopasiContainer* CCopasiObject::getObjectParent "jobject"
%typemap(jtype) CCopasiContainer* CCopasiObject::getObjectParent "CCopasiContainer"
%typemap(jstype) CCopasiContainer* CCopasiObject::getObjectParent "CCopasiContainer"
%typemap(javaout) CCopasiContainer* CCopasiObject::getObjectParent
{
  return $jnicall;
}
%typemap(out) CCopasiContainer* CCopasiObject::getObjectParent
{
    $result = DownCast_CCopasiContainer(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}


%typemap(jni) CCopasiParameter* CCopasiParameterGroup::getParameter "jobject"
%typemap(jtype) CCopasiParameter* CCopasiParameterGroup::getParameter "CCopasiParameter"
%typemap(jstype) CCopasiParameter* CCopasiParameterGroup::getParameter "CCopasiParameter"
%typemap(javaout) CCopasiParameter* CCopasiParameterGroup::getParameter
{
  return $jnicall;
}
%typemap(out) CCopasiParameter* CCopasiParameterGroup::getParameter
{
    $result = DownCast_CCopasiParameter(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}

%typemap(jni) CCopasiParameterGroup* CCopasiParameterGroup::getGroup "jobject"
%typemap(jtype) CCopasiParameterGroup* CCopasiParameterGroup::getGroup "CCopasiParameterGroup"
%typemap(jstype) CCopasiParameterGroup* CCopasiParameterGroup::getGroup "CCopasiParameterGroup"
%typemap(javaout) CCopasiParameterGroup* CCopasiParameterGroup::getGroup
{
  return $jnicall;
}
%typemap(out) CCopasiParameterGroup* CCopasiParameterGroup::getGroup
{
    $result = DownCast_CCopasiParameterGroup(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}


%typemap(jni) CCopasiProblem* CCopasiTask::getProblem "jobject"
%typemap(jtype) CCopasiProblem* CCopasiTask::getProblem "CCopasiProblem"
%typemap(jstype) CCopasiProblem* CCopasiTask::getProblem "CCopasiProblem"
%typemap(javaout) CCopasiProblem* CCopasiTask::getProblem
{
  return $jnicall;
}
%typemap(out) CCopasiProblem* CCopasiTask::getProblem
{
    $result = DownCast_CCopasiProblem(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}


%typemap(jni) CCopasiMethod* CCopasiTask::getMethod "jobject"
%typemap(jtype) CCopasiMethod* CCopasiTask::getMethod "CCopasiMethod"
%typemap(jstype) CCopasiMethod* CCopasiTask::getMethod "CCopasiMethod"
%typemap(javaout) CCopasiMethod* CCopasiTask::getMethod
{
  return $jnicall;
}
%typemap(out) CCopasiMethod* CCopasiTask::getMethod
{
    $result = DownCast_CCopasiMethod(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}


%typemap(jni) CEvaluationTree* CFunctionDB::findFunction "jobject"
%typemap(jtype) CEvaluationTree* CFunctionDB::findFunction "CEvaluationTree"
%typemap(jstype) CEvaluationTree* CFunctionDB::findFunction "CEvaluationTree"
%typemap(javaout) CEvaluationTree* CFunctionDB::findFunction
{
  return $jnicall;
}
%typemap(out) CEvaluationTree* CFunctionDB::findFunction
{
    $result = DownCast_CEvaluationTree(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}


%typemap(jni) CEvaluationTree* CFunctionDB::findLoadFunction "jobject"
%typemap(jtype) CEvaluationTree* CFunctionDB::findLoadFunction "CEvaluationTree"
%typemap(jstype) CEvaluationTree* CFunctionDB::findLoadFunction "CEvaluationTree"
%typemap(javaout) CEvaluationTree* CFunctionDB::findLoadFunction
{
  return $jnicall;
}
%typemap(out) CEvaluationTree* CFunctionDB::findLoadFunction
{
    $result = DownCast_CEvaluationTree(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}


%typemap(jni) CEvaluationTree* CFunctionDB::createFunction "jobject"
%typemap(jtype) CEvaluationTree* CFunctionDB::createFunction "CEvaluationTree"
%typemap(jstype) CEvaluationTree* CFunctionDB::createFunction "CEvaluationTree"
%typemap(javaout) CEvaluationTree* CFunctionDB::createFunction
{
  return $jnicall;
}
%typemap(out) CEvaluationTree* CFunctionDB::createFunction
{
    $result = DownCast_CEvaluationTree(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}

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

/*
%typemap(jni) CModelEntity* "jobject"
%typemap(jtype) CModelEntity* "CModelEntity"
%typemap(jstype) CModelEntity* "CModelEntity"
%typemap(javaout) CModelEntity*
{
    return $jnicall;
}

%typemap(out) CModelEntity*
{
    $result = DownCast_CModelEntity(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}


%typemap(jni) CEvaluationTree* "jobject"
%typemap(jtype) CEvaluationTree* "CEvaluationTree"
%typemap(jstype) CEvaluationTree* "CEvaluationTree"
%typemap(javaout) CEvaluationTree*
{
    return $jnicall;
}

%typemap(out) CEvaluationTree*
{
    $result = DownCast_CEvaluationTree(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}

%typemap(jni) CCopasiTask* "jobject"
%typemap(jtype) CCopasiTask* "CCopasiTask"
%typemap(jstype) CCopasiTask* "CCopasiTask"
%typemap(javaout) CCopasiTask*
{
    return $jnicall;
}

%typemap(out) CCopasiTask*
{
    $result=DownCast_CCopasiTask(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}

%typemap(jni) CCopasiMethod* "jobject"
%typemap(jtype) CCopasiMethod* "CCopasiMethod"
%typemap(jstype) CCopasiMethod* "CCopasiMethod"
%typemap(javaout) CCopasiMethod*
{
    return $jnicall;
}

%typemap(out) CCopasiMethod*
{
    $result = DownCast_CCopasiMethod(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}

%typemap(jni) CCopasiProblem* "jobject"
%typemap(jtype) CCopasiProblem* "CCopasiProblem"
%typemap(jstype) CCopasiProblem* "CCopasiProblem"
%typemap(javaout) CCopasiProblem*
{
    return $jnicall;
}

%typemap(out) CCopasiProblem*
{
    $result = DownCast_CCopasiProblem(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}



%typemap(jni) CCopasiParameterGroup* "jobject"
%typemap(jtype) CCopasiParameterGroup* "CCopasiParameterGroup"
%typemap(jstype) CCopasiParameterGroup* "CCopasiParameterGroup"
%typemap(javaout) CCopasiParameterGroup*
{
    return $jnicall;
}

%typemap(out) CCopasiParameterGroup*
{
    $result = DownCast_CCopasiParameterGroup(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}


%typemap(jni) CCopasiParameter* "jobject"
%typemap(jtype) CCopasiParameter* "CCopasiParameter"
%typemap(jstype) CCopasiParameter* "CCopasiParameter"
%typemap(javaout) CCopasiParameter*
{
    return $jnicall;
}

%typemap(out) CCopasiParameter*
{
    $result = DownCast_CCopasiParameter(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}


%typemap(jni) CCopasiContainer* "jobject"
%typemap(jtype) CCopasiContainer* "CCopasiContainer"
%typemap(jstype) CCopasiContainer* "CCopasiContainer"
%typemap(javaout) CCopasiContainer*
{
    return $jnicall;
}

%typemap(out) CCopasiContainer*
{
    $result = DownCast_CCopasiContainer(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}

%typemap(jni) CCopasiObject* "jobject"
%typemap(jtype) CCopasiObject* "CCopasiObject"
%typemap(jstype) CCopasiObject* "CCopasiObject"
%typemap(javaout) CCopasiObject*
{
    return $jnicall;
}

%typemap(out) CCopasiObject*
{
    $result = DownCast_CCopasiObject(jenv,$1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}
*/



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


