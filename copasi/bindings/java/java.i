/**
 * Make COPASI and wrapper constants Java compile-time
 * constants so they may be used in switch statements.
 */
%include "enumsimple.swg"
%javaconst(1);

enum CLASS_TYPE
{
  CHEMICALEQUATION
  , CHEMICALEQUATIONELEMENT
  , CHEMICALEQUATIONELEMENTVECTOR
  , COMPARTMENT
  , COMPARTMENTVECTOR
  , COMPARTMENTVECTORN
  , COMPARTMENTVECTORNS
  , CONTAINER
  , EVALUATIONTREE
  , EVALUATIONTREEVECTOR
  , EVALUATIONTREEVECTORN
  , FUNCTION
  , FUNCTIONDB
  , FUNCTIONPARAMETER
  , FUNCTIONPARAMETERS
  , METABOLITE
  , METABVECTOR
  , METABVECTORN
  , METABVECTORNS
  , METHOD
  , MODEL
  , MODELENTITY
  , MODELVALUE
  , MODELVALUEVECTOR
  , MODELVALUEVECTORN
  , MOIETY
  , MOIETYVECTOR
  , OBJECT
  , OBJECTNAME
  , PARAMETER
  , PARAMETERGROUP
  , PARAMETERVECTOR
  , PROBLEM
  , REACTION
  , REACTIONVECTOR
  , REACTIONVECTORN
  , REACTIONVECTORNS
  , REPORTDEFINITION
  , REPORTDEFINITIONVECTOR
  , REPORTDEFINITIONVECTORN
  , STATICSTRING
  , TASK
  , TASKVECTOR
  , TASKVECTORN
  , TRAJECTORYMETHOD
  , TRAJECTORYPROBLEM
  , TRAJECTORYTASK
};



CLASS_TYPE getClassTypeForObject(const CCopasiObject* pTree);
CLASS_TYPE getClassTypeForContainer(const CCopasiContainer* pTree);
CLASS_TYPE getClassTypeForModelEntity(const CModelEntity* pTree);
CLASS_TYPE getClassTypeForParameterGroup(const CCopasiParameterGroup* pTree);
CLASS_TYPE getClassTypeForParameter(const CCopasiParameter* pTree);
CLASS_TYPE getClassTypeForMethod(const CCopasiMethod* pTree);
CLASS_TYPE getClassTypeForProblem(const CCopasiProblem* pTree);
CLASS_TYPE getClassTypeForTask(const CCopasiTask* pTree);
CLASS_TYPE getClassTypeForCEvaluationTree(const CEvaluationTree* pTree);


/**
 * @return the most specific Java object possible for the given SBase
 * object.
 */
 
%pragma(java) modulecode =
%{
/*
  enum CLASS_TYPE
  {
  CHEMICALEQUATION
  , CHEMICALEQUATIONELEMENT
  , CHEMICALEQUATIONELEMENTVECTOR
  , COMPARTMENT
  , COMPARTMENTVECTOR
  , COMPARTMENTVECTORN
  , COMPARTMENTVECTORNS
  , CONTAINER
  , EVALUATIONTREE
  , EVALUATIONTREEVECTOR
  , EVALUATIONTREEVECTORN
  , FUNCTION
  , FUNCTIONDB
  , FUNCTIONPARAMETER
  , FUNCTIONPARAMETERS
  , METABOLITE
  , METABVECTOR
  , METABVECTORN
  , METABVECTORNS
  , METHOD
  , MODEL
  , MODELENTITY
  , MODELVALUE
  , MODELVALUEVECTOR
  , MODELVALUEVECTORN
  , MOIETY
  , MOIETYVECTOR
  , OBJECT
  , OBJECTNAME
  , PARAMETER
  , PARAMETERGROUP
  , PARAMETERVECTOR
  , PROBLEM
  , REACTION
  , REACTIONVECTOR
  , REACTIONVECTORN
  , REACTIONVECTORNS
  , REPORTDEFINITION
  , REPORTDEFINITIONVECTOR
  , REPORTDEFINITIONVECTORN
  , STATICSTRING
  , TASK
  , TASKVECTOR
  , TASKVECTORN
  , TRAJECTORYMETHOD
  , TRAJECTORYPROBLEM
  , TRAJECTORYTASK
  }
*/

  public static CCopasiObject DowncastObject(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(COPASIJNI.getClassTypeForObject(cPtr) )
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
        return new MoietyVector(cPtr, owner);

      case METABVECTOR:
        return new MetabVector(cPtr, owner);

      case CHEMICALEQUATIONELEMENTVECTOR:
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

    switch(COPASIJNI.getClassTypeForContainer(cPtr) )
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
        return new MoietyVector(cPtr, owner);

      case METABVECTOR:
        return new MetabVector(cPtr, owner);

      case CHEMICALEQUATIONELEMENTVECTOR:
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

  public static CModelEntity DowncastModelEntity(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(COPASIJNI.getClassTypeForModelEntity(cPtr) )
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

  public static CCopasiParameterGroup DowncastParameterGroup(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(COPASIJNI.getClassTypeForParameterGroup(cPtr) )
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

  public static CCopasiParameter DowncastParameter(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(COPASIJNI.getClassTypeForParameter(cPtr) )
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

  public static CCopasiMethod DowncastMethod(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(COPASIJNI.getClassTypeForMethod(cPtr) )
    {
      
      case TRAJECTORYMETHOD:
        return new CTrajectoryMethod(cPtr, owner);

      case METHOD:
        return new CCopasiMethod(cPtr, owner);

      default:
        return new CCopasiMethod(cPtr, owner);
    }
  }

  public static CCopasiProblem DowncastProblem(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(COPASIJNI.getClassTypeForProblem(cPtr) )
    {
      
      case TRAJECTORYPROBLEM:
        return new CTrajectoryProblem(cPtr, owner);

      case PROBLEM:
        return new CCopasiProblem(cPtr, owner);

      default:
        return new CCopasiProblem(cPtr, owner);
    }
  }

  public static CCopasiTask DowncastTask(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(COPASIJNI.getClassTypeForTask(cPtr) )
    {
      
      case TRAJECTORYTASK:
        return new CTrajectoryTask(cPtr, owner);

      case TASK:
        return new CCopasiTask(cPtr, owner);

      default:
        return new CCopasiTask(cPtr, owner);
    }
  }

  public static CEvaluationTree DowncastEvaluationTree(long cPtr, boolean owner)
  {
    if (cPtr == 0) return null;

    switch(COPASIJNI.getClassTypeForCEvaluationTree(cPtr) )
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
  return COPASI.DowncastObject($jnicall, $owner);
}

/**
 * Convert CCopasiContainer objects into the most specific object possible.
 */
%typemap("javaout") CCopasiContainer*
{
  return COPASI.DowncastContainer($jnicall, $owner);
}


/**
 * Convert CEvaluationTree objects into the most specific object possible.
 */
%typemap("javaout") CEvaluationTree*
{
  return COPASI.DowncastEvaluationTree($jnicall, $owner);
}


/**
 * Convert CCopasiParameter objects into the most specific object possible.
 */
%typemap("javaout") CCopasiParameter*
{
  return COPASI.DowncastParameter($jnicall, $owner);
}


/**
 * Convert CCopasiParameterGroup objects into the most specific object possible.
 */
%typemap("javaout") CCopasiParameterGroup*
{
  return COPASI.DowncastParameterGroup($jnicall, $owner);
}


/**
 * Convert CCopasiMethod objects into the most specific object possible.
 */
%typemap("javaout") CCopasiMethod*
{
  return COPASI.DowncastMethod($jnicall, $owner);
}


/**
 * Convert CCopasiProblem objects into the most specific object possible.
 */
%typemap("javaout") CCopasiProblem*
{
  return COPASI.DowncastProblem($jnicall, $owner);
}


/**
 * Convert CCopasiTask objects into the most specific object possible.
 */
%typemap("javaout") CCopasiTask*
{
  return COPASI.DowncastTask($jnicall, $owner);
}

/**
 * Convert CModelEntity objects into the most specific object possible.
 */
%typemap("javaout") CModelEntity*
{
  return COPASI.DowncastModelEntity($jnicall, $owner);
}



%include "../swig/copasi.i"


