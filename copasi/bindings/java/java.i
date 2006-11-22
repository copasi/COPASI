
/**
 * @return the most specific Java object possible for the given SBase
 * object.
 */
%pragma(java) modulecode =
%{
  public static CCopasiObject DowncastObject(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(getClassTypeForObject(cPtr) )
    {
      
      case OBJECT:
        return new CCopasiObject(cPtr, owner);

      case STATICSTRING:
        return new CCopasiStaticString(cPtr, owner);

      case REPORTDEFINITION:
        return new CReportDefinition(cPtr, owner);

      case CONTAINER:
        return new CCopasiContainer(cPtr, owner);

      case MODELENTITY:
        return new CModelEntity(cPtr, owner);

      case TASKVECTORN:
        return new TaskVectorN(cPtr, owner);

      case MODELVALUEVECTORN:
        return new ModelValueVectorN(cPtr, owner);

      case METABVECTORNS:
        return new MetabVectorNS(cPtr, owner);

      case COMPARTMENTVECTORNS:
        return new CompartmentVectorNS(cPtr, owner);

      case REACTIONVECTORNS:
        return new ReactionVectorNS(cPtr, owner);

      case EVALUATIONTREEVECTORN:
        return new CEvaluationTreeVectorN(cPtr, owner);

      case MOIETYVECTOR:
        return new CMoietyVector(cPtr, owner);

      case METABVECTOR:
        return new CMetabVector(cPtr, owner);

      case PARAMETERVECTOR:
        return new CCopasiParameterVector(cPtr, owner);

      case CHEMEQELEMENTVECTOR:
        return new CChemEqElementVector(cPtr, owner);

      case EVALUATIONTREE:
        return new CEvaluationTree(cPtr, owner);

      case TASK:
        return new CCopasiTask(cPtr, owner);

      case CHEMICALEQUATION:
        return new CChemEq(cPtr, owner);

      case CHEMICALEQUATIONELEMENT:
        return new CChemEqElement(cPtr, owner);

      case PARAMETER:
        return new CCopasiParameter(cPtr, owner);

      case FUNCTIONDB:
        return new CFunctionDB(cPtr, owner);

      case FUNCTIONPARAMETER:
        return new CFunctionParameter(cPtr, owner);

      case FUNCTIONPARAMETERS:
        return new CFunctionParameters(cPtr, owner);

      case MOIETY:
        return new CMoiety(cPtr, owner);

      case REACTION:
        return new CReaction(cPtr, owner);

      case METABOLITE:
        return new CMetab(cPtr, owner);

      case MODELVALUE:
        return new CModelValue(cPtr, owner);

      case COMPARTMENT:
        return new CCompartment(cPtr, owner);

      case MODEL:
        return new CModel(cPtr, owner);

      case TRAJECTORYTASK:
        return new CTrajectoryTask(cPtr, owner);

      case TRAJECTORYMETHOD:
        return new CTrajectoryMethod(cPtr, owner);

      case TRAJECTORYPROBLEM:
        return new CTrajectoryProblem(cPtr, owner);

      case PARAMETERGROUP:
        return new CCopasiParameterGroup(cPtr, owner);

      case METHOD:
        return new CCopasiMethod(cPtr, owner);

      case PROBLEM:
        return new CCopasiProblem(cPtr, owner);

      default:
        return new CCopasiObject(cPtr, owner);
    }
  }

  public static CCopasiContainer DowncastContainer(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(getClassTypeForContainer(cPtr) )
    {
      
      case CONTAINER:
        return new CCopasiContainer(cPtr, owner);

      case MODELENTITY:
        return new CModelEntity(cPtr, owner);

      case TASKVECTORN:
        return new TaskVectorN(cPtr, owner);

      case MODELVALUEVECTORN:
        return new ModelValueVectorN(cPtr, owner);

      case METABVECTORNS:
        return new MetabVectorNS(cPtr, owner);

      case COMPARTMENTVECTORNS:
        return new CompartmentVectorNS(cPtr, owner);

      case REACTIONVECTORNS:
        return new ReactionVectorNS(cPtr, owner);

      case EVALUATIONTREEVECTORN:
        return new CEvaluationTreeVectorN(cPtr, owner);

      case MOIETYVECTOR:
        return new CMoietyVector(cPtr, owner);

      case METABVECTOR:
        return new CMetabVector(cPtr, owner);

      case PARAMETERVECTOR:
        return new CCopasiParameterVector(cPtr, owner);

      case CHEMEQELEMENTVECTOR:
        return new CChemEqElementVector(cPtr, owner);

      case EVALUATIONTREE:
        return new CEvaluationTree(cPtr, owner);

      case TASK:
        return new CCopasiTask(cPtr, owner);

      case CHEMICALEQUATION:
        return new CChemEq(cPtr, owner);

      case CHEMICALEQUATIONELEMENT:
        return new CChemEqElement(cPtr, owner);

      case PARAMETER:
        return new CCopasiParameter(cPtr, owner);

      case FUNCTIONDB:
        return new CFunctionDB(cPtr, owner);

      case FUNCTIONPARAMETER:
        return new CFunctionParameter(cPtr, owner);

      case FUNCTIONPARAMETERS:
        return new CFunctionParameters(cPtr, owner);

      case MOIETY:
        return new CMoiety(cPtr, owner);

      case REACTION:
        return new CReaction(cPtr, owner);

      case METABOLITE:
        return new CMetab(cPtr, owner);

      case MODELVALUE:
        return new CModelValue(cPtr, owner);

      case COMPARTMENT:
        return new CCompartment(cPtr, owner);

      case MODEL:
        return new CModel(cPtr, owner);

      case TRAJECTORYTASK:
        return new CTrajectoryTask(cPtr, owner);

      case TRAJECTORYMETHOD:
        return new CTrajectoryMethod(cPtr, owner);

      case TRAJECTORYPROBLEM:
        return new CTrajectoryProblem(cPtr, owner);

      case PARAMETERGROUP:
        return new CCopasiParameterGroup(cPtr, owner);

      case METHOD:
        return new CCopasiMethod(cPtr, owner);

      case PROBLEM:
        return new CCopasiProblem(cPtr, owner);

      default:
        return new CCopasiContainer(cPtr, owner);
    }
  }

  public static CCopasiObject DowncastModelEntity(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(getClassTypeForModelEntity(cPtr) )
    {
      
      case MODELENTITY:
        return new CModelEntity(cPtr, owner);

      case METABOLITE:
        return new CMetab(cPtr, owner);

      case MODELVALUE:
        return new CModelValue(cPtr, owner);

      case COMPARTMENT:
        return new CCompartment(cPtr, owner);

      case MODEL:
        return new CModel(cPtr, owner);

      default:
        return new CModelEntity(cPtr, owner);
    }
  }

  public static CCopasiObject DowncastParameterGroup(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(getClassTypeForParameterGroup(cPtr) )
    {
      
      case TRAJECTORYMETHOD:
        return new CTrajectoryMethod(cPtr, owner);

      case TRAJECTORYPROBLEM:
        return new CTrajectoryProblem(cPtr, owner);

      case PARAMETERGROUP:
        return new CCopasiParameterGroup(cPtr, owner);

      case METHOD:
        return new CCopasiMethod(cPtr, owner);

      case PROBLEM:
        return new CCopasiProblem(cPtr, owner);

      default:
        return new CCopasiParameterGroup(cPtr, owner);
    }
  }

  public static CCopasiObject DowncastParameter(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(getClassTypeForParameter(cPtr) )
    {
      
      case PARAMETER:
        return new CCopasiParameter(cPtr, owner);

      case TRAJECTORYMETHOD:
        return new CTrajectoryMethod(cPtr, owner);

      case TRAJECTORYPROBLEM:
        return new CTrajectoryProblem(cPtr, owner);

      case PARAMETERGROUP:
        return new CCopasiParameterGroup(cPtr, owner);

      case METHOD:
        return new CCopasiMethod(cPtr, owner);

      case PROBLEM:
        return new CCopasiProblem(cPtr, owner);

      default:
        return new CCopasiParameter(cPtr, owner);
    }
  }

  public static CCopasiObject DowncastMethod(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(getClassTypeForMethod(cPtr) )
    {
      
      case TRAJECTORYMETHOD:
        return new CTrajectoryMethod(cPtr, owner);

      case METHOD:
        return new CCopasiMethod(cPtr, owner);

      default:
        return new CCopasiMethod(cPtr, owner);
    }
  }

  public static CCopasiObject DowncastProblem(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(getClassTypeForProblem(cPtr) )
    {
      
      case TRAJECTORYPROBLEM:
        return new CTrajectoryProblem(cPtr, owner);

      case PROBLEM:
        return new CCopasiProblem(cPtr, owner);

      default:
        return new CCopasiProblem(cPtr, owner);
    }
  }

  public static CCopasiObject DowncastTask(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(getClassTypeForTask(cPtr) )
    {
      
      case TRAJECTORYTASK:
        return new CTrajectoryTask(cPtr, owner);

      case TASK:
        return new CCopasiTask(cPtr, owner);

      default:
        return new CCopasiTask(cPtr, owner);
    }
  }

  public static CCopasiObject DowncastEvaluationTree(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(getClassTypeForCEvaluationTree(cPtr) )
    {
      
      case EVALUATIONTREE:
        return new CEvaluationTree(cPtr, owner);

      case FUNCTION:
        return new CFunction(cPtr, owner);

      default:
        return new CEvaluationTree(cPtr, owner);
    }
  }

  
%}


/**
 * Convert CCopasiObject objects into the most specific object possible.
 */
%typemap("javaout") CCopasiObject*
{
  return DowncastObject($jnicall, $owner);
}

/**
 * Convert CCopasiContainer objects into the most specific object possible.
 */
%typemap("javaout") CCopasiContainer*
{
  return DowncastContainer($jnicall, $owner);
}


/**
 * Convert CEvaluationTree objects into the most specific object possible.
 */
%typemap("javaout") CEvaluationTree*
{
  return DowncastEvaluationTree($jnicall, $owner);
}


/**
 * Convert CCopasiParameter objects into the most specific object possible.
 */
%typemap("javaout") CCopasiParameter*
{
  return DowncastParameter($jnicall, $owner);
}


/**
 * Convert CCopasiParameterGroup objects into the most specific object possible.
 */
%typemap("javaout") CCopasiParameterGroup*
{
  return DowncastParameterGroup($jnicall, $owner);
}


/**
 * Convert CCopasiMethod objects into the most specific object possible.
 */
%typemap("javaout") CCopasiMethod*
{
  return DowncastMethod($jnicall, $owner);
}


/**
 * Convert CCopasiProblem objects into the most specific object possible.
 */
%typemap("javaout") CCopasiProblem*
{
  return DowncastProblem($jnicall, $owner);
}


/**
 * Convert CCopasiTask objects into the most specific object possible.
 */
%typemap("javaout") CCopasiTask*
{
  return DowncastTask($jnicall, $owner);
}

/**
 * Convert CModelEntity objects into the most specific object possible.
 */
%typemap("javaout") CModelEntity*
{
  return DowncastModelEntity($jnicall, $owner);
}





%include "../swig/copasi.i"


