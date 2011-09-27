// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/csharp/csharp.i,v $
//   $Revision: 1.1.2.5 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/09/27 20:08:26 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * Make COPASI and wrapper constants Mono compile-time
 * constants so they may be used in switch statements.
 */
%include "enumsimple.swg"
%csconst(1);


void initCopasi();

// The build system has to call SWIG with the -DSWIG_CSHARP_NO_IMCLASS_STATIC_CONSTRUCTOR
// otherwise newer versions of SWIG will create a static constructor which conflicts with
// the one below
// Since I have no clue about C#, I don't know any other way to make sure that initCopasi
// is called when the module is loaded
%pragma(csharp) imclasscode=
%{

    // the static constructor
    // initializes the COPASI backend
    static $imclassname() {
        initCopasi();
    }

    // typecasting code for polymorphic classes
    // This follows the solution suggested by John McGehee
    // detailed at http://www.voom.net/swig-csharp-java-downcast

    // CEvaluationTree
    public static CEvaluationTree InstantiateConcrete_CEvaluationTree(IntPtr cPtr, bool owner)
    {
        CEvaluationTree ret = null;
        if (cPtr == IntPtr.Zero) {
            return ret;
        }
        enum CLASS_TYPE type = $modulePINVOKE.GetType_CEvaluationTree(cPtr);
        switch (type) {
            case UNDEFINED_CLASS_TYPE:
                break;
            case CFunction_Type:
                ret = new CFunction(cPtr, owner);
                break;
            case CEvaluationTree_Type:
                ret = new CEvaluationTree(cPtr, owner);
                break;
            default:
                System.Diagnostics.Debug.Assert(false,
                        String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                            type.ToString()));
                break;
        }
        return ret;
    }

    // CFitItem
    public static CFitItem InstantiateConcrete_CFitItem(IntPtr cPtr, bool owner)
    {
        CFitItem ret = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_CFitItem(cPtr);
            switch(type)
            {
                case UNDEFINED_CLASS_TYPE:
                    break;
                case CFitConstraint_Type:
                    ret = new CFitConstraint(cPtr, owner);
                    break;
                case CEvaluationTree_Type:
                    ret = new CFitItem(cPtr, owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }


    // CModelEntity
    static CModelEntity InstantiateConcrete_CModelEntity(IntPtr cPtr, bool owner)
    {
        CModelEntity ret = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_CModelEntity(cPtr);
            switch(type)
            {
                case UNDEFINED_CLASS_TYPE:
                    break;
                case CCompartment_Type:
                    // return a CCompartment
                    ret = new CCompartment(cPtr,owner);
                    break;
                case CMetab_Type:
                    // return a CMetab
                    ret = new CMetab(cPtr,owner)
                        break;
                case CModel_Type:
                    // return a CModel
                    ret = new CModel(cPtr,owner);
                    break;
                case CModelValue_Type:
                    // return a CModelValue
                    ret = new CModelValue(cPtr,owner);
                    break;
                case CModelEntity_Type:
                    // return a CModelEntity
                    ret = new CModelEntity(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }


    // COptItem
    static COptItem InstantiateConcerete_COptItem(IntPtr cPtr, bool owner)
    {
        COptItem ret = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_COptItem(cPtr);
            switch(type)
            {
                case UNDEFINED_CLAS_TYPE:
                    break;
                case CFitItem_Type:
                    // return a CFitItem
                    result = InstantiateConcrete_CFitItem(cPtr,owner);
                    break;
                case COptItem_Type:
                    // return a COptItem
                    result = new COptItem(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }

    // COptMethod
    static COptMethod InstantiateConcerete_COptMethod(CIntPtr cPtr, bool owner)
    {
        COptMethod ret = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_COptMethod(cPtr);
            switch(type) {
                case UNDEFINED_CLASS_TYPE:
                    break;
                case CFitMethod_Type:
                    // return a CFitMethod
                    ret = new CFitMethod(cPtr,owner);
                    break;
                case COptMethod_Type:
                    // return a COptMethod
                    ret = new COptMethod(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }

        return ret;
    }

    // COptProblem
    static COptProblem InstantiateConcerete_COptProblem(IntPtr cPtr, bool owner)
    {
        COptProblem ret = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_COptProblem(cPtr);
            switch(type)
            {
                case UNDEFINED_CLASS_TYPE:
                    break;
                case CFitProblem_Type:
                    // return a CFitProblem
                    ret = new CFitProblem(cPtr,owner);
                    break;
                case COptProblem_Type:
                    // return a COptProblem
                    result = new COptProblem(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }


    // COptTask
    static COptTask InstantiateConcerete_COptTask(IntPtr cPtr, bool owner)
    {
        COptTask ret = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_COptTask(cPtr);
            switch(type)
            {
                case UNDEFINED_CLASS_TYPE:
                    break;
                case CFitTask_Type:
                    // return a CFitTask
                    ret = new CFitTask(cPtr,owner);
                    break;
                case COptTask_Type:
                    // return a COptTask
                    ret = new COptTask(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }

        }
        return ret;
    }

    // CCopasiAbstractArray
    static CCopasiAbstractArray InstantiateConcrete_CCopasiAbstractArray(IntPtr cPtr, bool owner)
    {
        CCopasiAbstractArray result = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_CCopasiAbstractArray(cPtr);
            switch(type)
            {
                case CCopasiArray_Type:
                    // return a CCopasiArray
                    ret = new CCopasiArray(cPtr,owner);
                    break;
                case AnnotatedFloatMatrix_Type:
                    // return a AnnotatedFloatMatrix
                    ret = new AnnotatedFloatMatrix(cPtr,owner);
                    break;
                case CCopasiAbstractArray_Type:
                    // return a CCopasiAbstractArray
                    ret = new CCopasiAbstractArray(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }


    // Determine type for CCopasiContainer
    CCopasiContainer InstantiateConcrete_CCopasiContainer(IntPtr cPtr, bool owner)
    {
        CCopasiContainer ret = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_CCopasiContainer(cPtr);
            switch(type)
            {
                case UNDEFINED_CLASS_TYPE:
                    break;
                case CCopasiRootContainer_Type:
                    // return a CCopasiRootContainer
                    ret = new CCopasiRootContainer(cPtr,owner);
                    break;
                case CCopasiDataModel_Type:
                    // return a CCopasiDataModel
                    ret = new CCopasiDataModel(cPtr,owner);
                    break;
                case CChemEq_Type:
                    // return a CChemEq
                    ret = new CChemEq(cPtr,owner);
                    break;
                case CChemEqElement_Type:
                    // return a CChemEqElement
                    ret = new CChemEqElement(cPtr,owner);
                    break;
                case CReference_Type:
                    // return a CReference
                    ret = new CReference(cPtr,owner);
                    break;
                case CModification_Type:
                    // return a CModification
                    ret = new CModification(cPtr,owner);
                    break;
                case CCreator_Type:
                    // return a CCreator
                    ret = new CCreator(cPtr,owner);
                    break;
                case CBiologicalDescription_Type:
                    // return a CBiologicalDescription
                    ret = new CBiologicalDescription(cPtr,owner);
                    break;
                case CMIRIAMInfo_Type:
                    // return a CMIRIAMInfo
                    ret = new CMIRIAMInfo(cPtr,owner);
                    break;
                case CCopasiTask_Type:
                    ret = InstantiateConcrete_CCopasiTask(cptr,owner);
                    break;
                case CCopasiParameter_Type:
                    ret = InstantiateConcrete_CCopasiParameter(cPtr,owner);
                    break;
                case CEvaluationTree_Type:
                    ret = InstantiateConcrete_CEvaluationTree(cPtr,owner);
                    break;
                case CFunctionDB_Type:
                    // return a CFunctionDB
                    ret = new CFunctionDB(cPtr,owner);
                    break;
                case CFunctionParameter_Type:
                    // return a CFunctionParameter
                    ret = new CFunctionParameter(cPtr,owner);
                    break;
                case CFunctionParameters_Type:
                    // return a CFunctionParameters
                    ret = new CFunctionParameters(cPtr,owner);
                    break;
                case CEvent_Type:
                    // return a CEvent
                    ret = new CEvent(cPtr,owner);
                    break;
                case CEventAssignment_Type:
                    // return a CEventAssignment
                    ret = new CEventAssignment(cPtr,owner);
                    break;
                case CModelEntity_Type:
                    ret = InstantiateConcrete_CModelEntity(cPtr,owner);
                    break;
                case CMoiety_Type:
                    // return a CMoiety
                    ret = new CMoiety(cPtr,owner);
                    break;
                case CReaction_Type:
                    // return a CReaction
                    ret = new CReaction(cPtr,owner);
                    break;
                case CFittingPoint_Type:
                    // return a CFittingPoint
                    ret = new CFittingPoint(cPtr,owner);
                    break;
                case TaskVectorN_Type:
                    // return a TaskVectorN
                    ret = new TaskVectorN(cPtr,owner);
                    break;
                case TaskVector_Type:
                    // return a TaskVector
                    ret = new TaskVector(cPtr,owner);
                    break;
                case ModelValueVectorN_Type:
                    // return a ModelValueVectorN
                    ret = new ModelValueVectorN(cPtr,owner);
                    break;
                case ModelValueVector_Type:
                    // return a ModelValueVector
                    ret = new ModelValueVector(cPtr,owner);
                    break;
                case EventVectorN_Type:
                    // return a CEventVectorN
                    ret = new EventVectorN(cPtr,owner);
                    break;
                case EventVector_Type:
                    // return a EventVector
                    ret = new EventVector(cPtr,owner);
                    break;
                case EventAssignmentVectorN_Type:
                    // return a EventAssignmentVectorN
                    ret = new EventAssignmentVectorN(cPtr,owner);
                    break;
                case EventAssignmentVector_Type:
                    // return a EventAssignmentVector
                    ret = new EventAssignmentVector(cPtr,owner);
                    break;
                case CReportDefinitionVectorN_Type:
                    // return a CReportDefinitionVectorN
                    ret = new CReportDefinitionVectorN(cPtr,owner);
                    break;
                case CReportDefinitionVector_Type:
                    // return a CReportDefinitionVector
                    ret = new CReportDefinitionVector(cPtr,owner);
                    break;
                case MoietyVector_Type:
                    // return a MoietyVector
                    ret = new MoietyVector(cPtr,owner);
                    break;
                case MetabVectorNS_Type:
                    // return a MetabVectorNS
                    ret = new MetabVectorNS(cPtr,owner);
                    break;
                case MetabVectorN_Type:
                    // return a MetabVectorN
                    ret = new MetabVectorN(cPtr,owner);
                    break;
                case MetabVector_Type:
                    // return a MetabVector
                    ret = new MetabVector(cPtr,owner);
                    break;
                case CompartmentVectorNS_Type:
                    // return a CompartmentVectorNS
                    ret = new CompartmentVectorNS(cPtr,owner);
                    break;
                case CompartmentVectorN_Type:
                    // return a CompartmentVectorN
                    ret = new CompartmentVectorN(cPtr,owner);
                    break;
                case CompartmentVector_Type:
                    // return a CompartmentVector
                    ret = new CompartmentVector(cPtr,owner);
                    break;
                case ReactionVectorNS_Type:
                    // return a ReactionVectorNS
                    ret = new ReactionVectorNS(cPtr,owner);
                    break;
                case ReationVectorN_Type:
                    // return a ReactionVectorN
                    ret = new ReactionVectorN(cPtr,owner);
                    break;
                case ReactionVector_Type:
                    // return a ReactionVector
                    ret = new ReactionVector(cPtr,owner);
                    break;
                case CEvaluationTreeVectorN_Type:
                    // return a CEvaluationTreeVectorN
                    ret = new CEvaluationTreeVectorN(cPtr,owner);
                    break;
                case CEvaluationTreeVector_Type:
                    // return a CEvaluationTreeVector
                    ret = new CEvaluationTreeVector(cPtr,owner);
                    break;
                case CChemEqElementVector_Type:
                    // return a CChemEqElementVector
                    ret = new CChemEqElementVector(cPtr,owner);
                    break;
                case CArrayAnnotation_Type:
                    // return a CArrayAnnotation
                    ret = new CArrayAnnotation(cPtr,owner);
                    break;
                case CCopasiContainer_Type:
                    // return a CCopasiContainer
                    ret = new CCopasiContainer(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }

        return ret;
    }


    // CCopasiMethod
    CCopasiMethod InstantiateConcrete_CCopasiMethod(IntPtr cPtr, bool owner)
    {
        CCopasiMethod ret = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_CCopasiMethod(cPtr);
            switch(type)
            {
                case UNDEFINED_CLASS_TYPE:
                    break;
                case CTrajectoryMethod_Type:
                    // return a CTrajectoryMethod
                    ret = new CTrajectoryMethod(cPtr,owner);
                    break;
                case CNewtonMethod_Type:
                    // return a CNewtonMethod
                    ret = new CNewtonMethod(cPtr,owner);
                    break;
                case CSteadyStateMethod_Type:
                    // return a CSteadyStateMethod
                    ret = new CSteadyStateMethod(cPtr,owner);
                    break;
                case CMCAMethod_Type:
                    // return a CMCAMethod
                    ret = new CMCAMethod(cPtr,owner);
                    break;
                case CScanMethod_Type:
                    // return a CScanMethod
                    ret = new CScanMethod(cPtr,owner);
                    break;
                case COptMethod_Type:
                    ret = InstantiateConcrete_COptMethod(cPtr,owner);
                    break;
                case CLyapMethod_Type:
                    // return a CLyapMethod
                    ret = new CLaypMethod(cPtr,owner);
                    break;
                case CSensMethod_Type:
                    // return a CSensMethod
                    ret = new CSensMethod(cPtr,owner);
                    break;
                case CCopasiMethod_Type:
                    // return a CCopasiMethod
                    ret = new CCopasiMethod(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }


    // CCopasiObject
    CCopasiObject InstantiateConcrete_CCopasiObject(IntPtr cPtr, bool owner)
    {
        CCopasiObject ret = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_CCopasiObject(cPtr);
            switch(type)
            {
                case UNDEFINED_CLASS_TYPE:
                    break;
                case CCopasiContainer_Type:
                    ret = InstantiateConcrete_CCopasiContainer(cPtr, owner);
                    break;
                case CReportDefinition_Type:
                    // return a CReportDefinition
                    ret = new CReportDefinition(cPtr,owner);
                    break;
                case CCopasiReportSeparator_Type:
                    // return a CCopasiReportSeparator
                    ret = new CCopasiReportSeparator(cPtr,owner);
                    break;
                case CCopasiStaticString_Type:
                    // return a CCopasiStaticString
                    ret = new CCopasiStaticString(cPtr,owner);
                    break;
                case CCopasiObject_Type:
                    // return a CCopasiObject
                    ret = new CCopasiObject(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }

        return ret;
    }


    // CCopasiParameter
    CCopasiParameter InstantiateConcrete_CCopasiParameter(IntPtr cPtr, bool owner)
    {
        CCopasiParameter ret = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_CCopasiParameter(cPtr);
            switch(type)
            {
                case UNDEFINED_CLASS_TYPE:
                    break;
                case CCopasiParameterGroup_Type:
                    ret = InstantiateConcrete_CCopasiParameterGroup(cPtr,owner);
                    break;
                case CCopasiParameter_Type:
                    // return a CCopasiParameter
                    ret = new CCopasiParameter(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }

    // CCopasiParameterGroup
    CCopasiParameterGroup InstantiateConcrete_CCopasiParameterGroup(IntPtr cPtr, bool owner)
    {
        CCopasiParameterGroup ret = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_CCopasiParameterGroup(cPtr);
            switch(type)
            {
                case UNDEFINED_CLASS_TYPE:
                    break;
                case CCopasiMethod_Type:
                    ret = InstantiateConcrete_CCopasiMethod(cPtr,owner);
                    break;
                case CCopasiProblem_Type:
                    ret = InstantiateConcrete_CCopasiProblem(cPtr,owner);
                    break;
                case COptItem_Type:
                    ret = InstantiateConcrete_COptItem(cPtr,owner);
                    break;
                case CExperiment_Type:
                    // return a CExperiment
                    ret = new CExperiment(cPtr,owner);
                    break;
                case CExperimentSet_Type:
                    // return a CExperimentSet
                    ret = new CExperimentSet(cPtr,owner);
                    break;
                case CExperimentObjectMap_Type:
                    // return a CExperimentObjectMap
                    ret = new CExperimentObjectMap(cPtr,owner);
                    break;
                case CCopasiParameterGroup_Type:
                    // return a CCopasiParameterGroup
                    ret = new CCopasiParameterGroup(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }

    // CCopasiProblem
    CCopasiProblem InstantiateConcrete_CCopasiProblem(IntPtr cPtr, bool owner)
    {
        CCopasiProblem ret = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_CCopasiProblem(cPtr);
            switch(type)
            {
                case UNDEFINED_CLASS_TYPE:
                    break;
                case CTrajectoryProblem_Type:
                    // return a CTrajectoryProblem
                    ret = new CTrajectoryProblem(cPtr,owner);
                    break;
                case CSteadyStateProblem_Type:
                    // return a CSteadyStateProblem
                    ret = new CSteadyStateProblem(cPtr,owner);
                    break;
                case CMCAProblem_Type:
                    // return a CMCAProblem
                    ret = new CMCAProblem(cPtr,owner);
                    break;
                case CScanProblem_Type:
                    // return a CScanProblem
                    ret = new CScanProblem(cPtr,owner);
                    break;
                case COptProblem_Type:
                    ret = InstantiateConcrete_COptProblem(cPtr,owner);
                    break;
                case CLyapProblem_Type:
                    // return a CLyapProblem
                    ret = new CLyapProblem(cPtr,owner);
                    break;
                case CSensProblem_Type:
                    // return a CSensProblem
                    ret = new CSensProblem(cPtr,owner);
                    break;
                case CCopasiProblem_Type:
                    // return a CCopasiProblem
                    ret = new CCopasiProblem(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }


    // CCopasiTask
    CCopasiTask InstantiateConcrete_CCopasiTask(IntPtr cPtr, bool owner)
    {
        CCopasiTask ret = null;

        if (cPtr != IntPtr.Zero)
        {
            enum CLASS_TYPE type = $modulePINVOKE.GetType_CCopasiTask(cPtr);
            switch(type)
            {
                case UNDEFINED_CLASS_TYPE:
                    break;
                case CTrajectoryTask_Type:
                    // return a CTrajectoryTask
                    ret = new CTrajectoryTask(cPtr,owner);
                    break;
                case CSteadyStateTask_Type:
                    // return a CSteadyStateTask
                    ret = new CSteadyStateTask(cPtr,owner);
                    break;
                case CMCATask_Type:
                    // return a CMCATask
                    ret = new CMCATask(cPtr,owner);
                    break;
                case CScanTask_Type:
                    // return a CScanTask
                    ret = new CSensTask(cPtr,owner);
                    break;
                case COptTask_Type:
                    ret = InstantiateConcrete_COptTask(cPtr,owner);
                    break;
                case CLyapTask_Type:
                    // return a CLyapTask
                    ret = new CLyapTask(cPtr,owner);
                    break;
                case CSensTask_Type:
                    // return a CSensTask
                    ret = new CSensTask(cPtr,owner);
                    break;
                case CCopasiTask_Type:
                    // return a CCopasiTask
                    ret = new CCopasiTask(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }

%}


/**
 * C# does not handle exceptions the same way as java. The code below will have to be adjusted
 * once the build system is finished.
 */
%exception CCopasiTask::process %{
    try
    {
        $action
    }
    catch (std::exception &e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
        return $null;
    }
    catch(CCopasiException& e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.getMessage().getText().c_str());
        return $null;
    }
%}


%exception CCopasiDataModel::importSBML %{
    try
    {
        $action
    }
    catch (std::exception &e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
        return $null;
    }
    catch(CCopasiException& e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.getMessage().getText().c_str());
        return $null;
    }
%}


%exception CCopasiDataModel::newModel %{
    try
    {
        $action
    }
    catch (std::exception &e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
        return $null;
    }
    catch(CCopasiException& e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.getMessage().getText().c_str());
        return $null;
    }
%}

%exception CCopasiDataModel::importSBMLFromString %{
    try
    {
        $action
    }
    catch (std::exception &e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
        return $null;
    }
    catch(CCopasiException& e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.getMessage().getText().c_str());
        return $null;
    }
%}

%exception CCopasiDataModel::exportSBMLToString %{
    try
    {
        $action
    }
    catch (std::exception &e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
        return $null;
    }
    catch(CCopasiException& e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.getMessage().getText().c_str());
        return $null;
    }
%}

%exception CCopasiDataModel::exportSBML %{
    try
    {
        $action
    }
    catch (std::exception &e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
        return $null;
    }
    catch(CCopasiException& e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.getMessage().getText().c_str());
        return $null;
    }
%}



// some general ignore statements that already get rid of most warnings
%ignore *::operator =;
%ignore *::operator [];
%ignore *::operator ();
%ignore *::begin() const;
%ignore *::end() const;

%include "../swig/copasi.i"


