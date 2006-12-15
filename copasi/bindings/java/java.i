/**
 * Make COPASI and wrapper constants Java compile-time
 * constants so they may be used in switch statements.
 */
%include "enumsimple.swg"
%javaconst(1);

%{


jobject DownCast_CModelEntity(CModelEntity* pPointer)
{
    jobject result=NULL;
    if(dynamic_cast<CCompartment*>(pPointer))
    {
        // return a CCompartment
        jclass clazz=jenv->FindClass("CCompartment");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CCompartment**)&cptr=static_cast<CCompartment*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CMetab*>(pPointer))
    {
        // return a CMetab
        jclass clazz=jenv->FindClass("CMetab");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CMetab**)&cptr=static_cast<CMetab*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CModel*>(pPointer))
    {
        // return a CModel
        jclass clazz=jenv->FindClass("CModel");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CModel**)&cptr=static_cast<CModel*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CModelValue*>(pPointer))
    {
        // return a CModelValue
        jclass clazz=jenv->FindClass("CModelValue");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CModelValue**)&cptr=static_cast<CModelValue*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else
    {
        // return a CModelEntity
        jclass clazz=jenv->FindClass("CModelEntity");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CModelEntity**)&cptr=static_cast<CModelEntity*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    return result;
}

jobject DownCast_CEvaluationTree(CEvaluationTree* pPointer)
{
    jobject result=NULL;
    if(dynamic_cast<CFunction*>(pPointer))
    {
        // return a CFunction
        jclass clazz=jenv->FindClass("CFunction");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CFunction**)&cptr=static_cast<CFunction*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else
    {
        // return a CEvaluationTree
        jclass clazz=jenv->FindClass("CEvaluationTree");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CEvaluationTree**)&cptr=static_cast<CEvaluationTree*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    return result;
}

jobject DownCast_CCopasiTask(CCopasiTask* pPointer)
{
    jobject result=NULL;
    if(dynamic_cast<CTrajectoryTask*>(pPointer))
    {
        // return a CTrajectoryTask
        jclass clazz=jenv->FindClass("CTrajectoryTask");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CTrajectoryTask**)&cptr=static_cast<CTrajectoryTask*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else
    {
        // return a CCopasiTask
        jclass clazz=jenv->FindClass("CCopasiTask");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CCopasiTask**)&cptr=static_cast<CCopasiTask*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    return result;
}

jobject DownCast_CCopasiMethod(CCopasiMethod* pPointer)
{
    jobject result=NULL;
    if(dynamic_cast<CTrajectoryMethod*>(pPointer))
    {
        // return a CTrajectoryMethod
        jclass clazz=jenv->FindClass("CTrajectoryMethod");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CTrajectoryMethod**)&cptr=static_cast<CTrajectoryMethod*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else
    {
        // return a CCopasiMethod
        jclass clazz=jenv->FindClass("CCopasiMethod");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CCopasiMethod**)&cptr=static_cast<CCopasiMethod*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    return result;
}

jobject DownCast_CCopasiProblem(CCopasiProblem* pPointer)
{
    jobject result=NULL;
    if(dynamic_cast<CTrajectoryProblem*>(pPointer))
    {
        // return a CTrajectoryProblem
        jclass clazz=jenv->FindClass("CTrajectoryProblem");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CTrajectoryProblem**)&cptr=static_cast<CTrajectoryProblem*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else
    {
        // return a CCopasiProblem
        jclass clazz=jenv->FindClass("CCopasiProblem");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CCopasiProblem**)&cptr=static_cast<CCopasiProblem*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    return result;
}

jobject DownCast_CCopasiParameterGroup(CCopasiParameterGroup* pPointer)
{
    jobject result=NULL;
    if(dynamic_cast<CCopasiMethod*>(pPointer))
    {
        if(dynamic_cast<CTrajectoryMethod*>(pPointer))
        {
            // return a CTrajectoryMethod
            jclass clazz=jenv->FindClass("CTrajectoryMethod");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CTrajectoryMethod**)&cptr=static_cast<CTrajectoryMethod*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else
        {
            // return a CCopasiMethod
            jclass clazz=jenv->FindClass("CCopasiMethod");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CCopasiMethod**)&cptr=static_cast<CCopasiMethod*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
    }
    else if(dynamic_cast<CCopasiProblem*>(pPointer))
    {
        if(dynamic_cast<CTrajectoryProblem*>(pPointer))
        {
            // return a CTrajectoryProblem
            jclass clazz=jenv->FindClass("CTrajectoryProblem");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CTrajectoryProblem**)&cptr=static_cast<CTrajectoryProblem*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else
        {
            // return a CCopasiProblem
            jclass clazz=jenv->FindClass("CCopasiProblem");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CCopasiProblem**)&cptr=static_cast<CCopasiProblem*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
    }
    else
    {
        // return a CCopasiParameterGroup
        jclass clazz=jenv->FindClass("CCopasiParameterGroup");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CCopasiParameterGroup**)&cptr=static_cast<CCopasiParameterGroup*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    return result;
}

jobject DownCast_CCopasiParameter(CCopasiParameter* pPointer)
{
    jobject result=NULL;
    if(dynamic_cast<CCopasiParameterGroup*>(pPointer))
    {
        if(dynamic_cast<CCopasiMethod*>(pPointer))
        {
            if(dynamic_cast<CTrajectoryMethod*>(pPointer))
            {
                // return a CTrajectoryMethod
                jclass clazz=jenv->FindClass("CTrajectoryMethod");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CTrajectoryMethod**)&cptr=static_cast<CTrajectoryMethod*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
            else
            {
                // return a CCopasiMethod
                jclass clazz=jenv->FindClass("CCopasiMethod");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CCopasiMethod**)&cptr=static_cast<CCopasiMethod*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
        }
        else if(dynamic_cast<CCopasiProblem*>(pPointer))
        {
            if(dynamic_cast<CTrajectoryProblem*>(pPointer))
            {
                // return a CTrajectoryProblem
                jclass clazz=jenv->FindClass("CTrajectoryProblem");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CTrajectoryProblem**)&cptr=static_cast<CTrajectoryProblem*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
            else
            {
                // return a CCopasiProblem
                jclass clazz=jenv->FindClass("CCopasiProblem");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CCopasiProblem**)&cptr=static_cast<CCopasiProblem*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
        }
        else
        {
            // return a CCopasiParameterGroup
            jclass clazz=jenv->FindClass("CCopasiParameterGroup");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CCopasiParameterGroup**)&cptr=static_cast<CCopasiParameterGroup*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
    }
    else
    {
        // return a CCopasiParameter
        jclass clazz=jenv->FindClass("CCopasiParameter");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CCopasiParameter**)&cptr=static_cast<CCopasiParameter*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    return result;
}

jobject DownCast_CCopasiContainer(CCopasiCOntainer* pPointer)
{
    jobject result=NULL;
    if(dynamic_cast<CChemEq*>(pPointer))
    {
        // return a CChemEq
        jclass clazz=jenv->FindClass("CChemEq");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CChemEq**)&cptr=static_cast<CChemEq*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CChemEqElement*>(pPointer))
    {
        // return a CChemEqElement
        jclass clazz=jenv->FindClass("CChemEqElement");
        if(clazz)
        {
           jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
           if(mid)
           {
             jlong cptr = 0;
             *(CChemEqElement**)&cptr=static_cast<CChemEqElement*>(pPointer);
             result = jenv->NewObject(clazz,mid,cptr,false);
           }
        }
    }
    else if(dynamic_cast<CCopasiTask*>(pPointer))
    {
        if(dynamic_cast<CTrajectoryTask*>(pPointer))
        {
            // return a CTrajectoryTask
            jclass clazz=jenv->FindClass("CTrajectoryTask");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CTrajectoryTask**)&cptr=static_cast<CTrajectoryTask*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else
        {
            // return a CCopasiTask
            jclass clazz=jenv->FindClass("CCopasiTask");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CCopasiTask**)&cptr=static_cast<CCopasiTask*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
    }
    else if(dynamic_cast<CCopasiParameter*>(pPointer))
    {
        if(dynamic_cast<CCopasiParameterGroup*>(pPointer))
        {
            if(dynamic_cast<CCopasiMethod*>(pPointer))
            {
                if(dynamic_cast<CTrajectoryMethod*>(pPointer))
                {
                    // return a CTrajectoryMethod
                    jclass clazz=jenv->FindClass("CTrajectoryMethod");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CTrajectoryMethod**)&cptr=static_cast<CTrajectoryMethod*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
                else
                {
                    // return a CCopasiMethod
                    jclass clazz=jenv->FindClass("CCopasiMethod");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CCopasiMethod**)&cptr=static_cast<CCopasiMethod*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiProblem*>(pPointer))
            {
                if(dynamic_cast<CTrajectoryProblem*>(pPointer))
                {
                    // return a CTrajectoryProblem
                    jclass clazz=jenv->FindClass("CTrajectoryProblem");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CTrajectoryProblem**)&cptr=static_cast<CTrajectoryProblem*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
                else
                {
                    // return a CCopasiProblem
                    jclass clazz=jenv->FindClass("CCopasiProblem");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CCopasiProblem**)&cptr=static_cast<CCopasiProblem*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else
            {
                // return a CCopasiParameterGroup
                jclass clazz=jenv->FindClass("CCopasiParameterGroup");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CCopasiParameterGroup**)&cptr=static_cast<CCopasiParameterGroup*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
        }
        else
        {
            // return a CCopasiParameter
            jclass clazz=jenv->FindClass("CCopasiParameter");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CCopasiParameter**)&cptr=static_cast<CCopasiParameter*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
    }
    else if(dynamic_cast<CEvaluationTree*>(pPointer))
    {
        if(dynamic_cast<CFunction*>(pPointer))
        {
            // return a CFunction
            jclass clazz=jenv->FindClass("CFunction");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CFunction**)&cptr=static_cast<CFunction*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else
        {
            // return a CEvaluationTree
            jclass clazz=jenv->FindClass("CEvaluationTree");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CEvaluationTree**)&cptr=static_cast<CEvaluationTree*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
    }
    else if(dynamic_cast<CFunctionDB*>(pPointer))
    {
        // return a CFunctionDB
        jclass clazz=jenv->FindClass("CFunctionDB");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CFunctionDB**)&cptr=static_cast<CFunctionDB*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CFunctionParameter*>(pPointer))
    {
        // return a CFunctionParameter
        jclass clazz=jenv->FindClass("CFunctionParameter");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CFunctionParameter**)&cptr=static_cast<CFunctionParameter*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CFunctionParameters*>(pPointer))
    {
        // return a CFunctionParameters
        jclass clazz=jenv->FindClass("CFunctionParameters");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CFunctionParameters**)&cptr=static_cast<CFunctionParameters*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CModelEntity*>(pPointer))
    {
        if(dynamic_cast<CCompartment*>(pPointer))
        {
            // return a CCompartment
            jclass clazz=jenv->FindClass("CCompartment");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CCompartment**)&cptr=static_cast<CCompartment*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CMetab*>(pPointer))
        {
            // return a CMetab
            jclass clazz=jenv->FindClass("CMetab");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CMetab**)&cptr=static_cast<CMetab*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CModel*>(pPointer))
        {
            // return a CModel
            jclass clazz=jenv->FindClass("CModel");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CModel**)&cptr=static_cast<CModel*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CModelValue*>(pPointer))
        {
            // return a CModelValue
            jclass clazz=jenv->FindClass("CModelValue");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CModelValue**)&cptr=static_cast<CModelValue*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else
        {
            // return a CModelEntity
            jclass clazz=jenv->FindClass("CModelEntity");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CModelEntity**)&cptr=static_cast<CModelEntity*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }

    }
    else if(dynamic_cast<CMoiety*>(pPointer))
    {
        // return a CMoiety
        jclass clazz=jenv->FindClass("CMoiety");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CMoiety**)&cptr=static_cast<CMoiety*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CReaction*>(pPointer))
    {
        // return a CReaction
        jclass clazz=jenv->FindClass("CReaction");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CReaction**)&cptr=static_cast<CReaction*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CReport*>(pPointer))
    {
        // return a CReport
        jclass clazz=jenv->FindClass("CReport");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CReport**)&cptr=static_cast<CReport*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else
    {
        if(pPointer->isVector())
        {
            if(dynamic_cast<CCopasiVector<CCopasiTask>* >(pPointer))
            {
                if(dynamic_cast<CCopasiVectorN<CCopasiTask>* >(pPointer))
                {
                    // return a TaskVectorN
                    jclass clazz=jenv->FindClass("TaskVectorN");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(TaskVectorN**)&cptr=static_cast<TaskVectorN*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
                else
                {
                    // return a TaskVector
                    jclass clazz=jenv->FindClass("TaskVector");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(TaskVector**)&cptr=static_cast<TaskVector*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CModelValue>* >(pPointer))
            {
                if(dynamic_cast<CCopasiVectorN<CModelValue>* >(pPointer))
                {
                    // return a ModelValueVectorN
                    jclass clazz=jenv->FindClass("ModelValueVectorN");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(ModelValueVectorN**)&cptr=static_cast<ModelValueVectorN*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
                else
                {
                    // return a ModelValueVector
                    jclass clazz=jenv->FindClass("ModelValueVector");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(ModelValueVector**)&cptr=static_cast<ModelValueVector*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CReportDefinition>* >(pPointer))
            {
                if(dynamic_cast<CCopasiVectorN<CReportDefinition>* >(pPointer))
                {
                  // return a CCReportDefinitionVectorN
                  jclass clazz=jenv->FindClass("CReportDefinitionVectorN");
                  if(clazz)
                  {
                      jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                      if(mid)
                      {
                          jlong cptr = 0;
                          *(CReportDefinitionVectorN**)&cptr=static_cast<CReportDefinitionVectorN*>(pPointer);
                          result = jenv->NewObject(clazz,mid,cptr,false);
                      }
                  }
                }
                else
                {
                    // return a CReportDefinitionVector
                    jclass clazz=jenv->FindClass("CReportDefinitionVector");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CReportDefinitionVector**)&cptr=static_cast<CReportDefinitionVector*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CMoiety>* >(pPointer))
            {
                // return a MoietyVector
                jclass clazz=jenv->FindClass("MoietyVector");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(MoietyVector**)&cptr=static_cast<MoietyVector*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CMetab>* >(pPointer))
            {
                if(dynamic_cast<CCopasiVectorN<CMetab>* >(pPointer))
                {
                    if(dynamic_cast<CCopasiVectorNS<CMetab>* >(pPointer))
                    {
                        // return a MetabVectorNS
                        jclass clazz=jenv->FindClass("MetabVectorNS");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(MetabVectorNS**)&cptr=static_cast<MetabVectorNS*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                    else
                    {
                        // return a MetabVectorN
                        jclass clazz=jenv->FindClass("MetabVectorN");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(MetabVectorN**)&cptr=static_cast<MetabVectorN*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else
                {
                    // return a MetabVector
                    jclass clazz=jenv->FindClass("MetabVector");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(MetabVector**)&cptr=static_cast<MetabVector*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CCompartment>* >(pPointer))
            {
                if(dynamic_cast<CCopasiVectorN<CCompartment>* >(pPointer))
                {
                    if(dynamic_cast<CCopasiVectorNS<CCompartment>* >(pPointer))
                    {
                        // return a CompartmentVectorNS
                        jclass clazz=jenv->FindClass("CompartmentVectorNS");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CompartmentVectorNS**)&cptr=static_cast<CompartmentVectorNS*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                    else
                    {
                        // return a CompartmentVectorN
                        jclass clazz=jenv->FindClass("CompartmentVectorN");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CompartmentVectorN**)&cptr=static_cast<CompartmentVectorN*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else
                {
                    // return a CompartmentVector
                    jclass clazz=jenv->FindClass("CompartmentVector");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CompartmentVector**)&cptr=static_cast<CompartmentVector*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CReaction>* >(pPointer))
            {
                if(dynamic_cast<CCopasiVectorN<CReaction>* >(pPointer))
                {
                    if(dynamic_cast<CCopasiVectorNS<CReaction>* >(pPointer))
                    {
                        // return a ReactionVectorNS
                        jclass clazz=jenv->FindClass("ReactionVectorNS");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(ReactionVectorNS**)&cptr=static_cast<ReactionVectorNS*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                    else
                    {
                        // return a ReactionVectorN
                        jclass clazz=jenv->FindClass("ReactionVectorN");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(ReactionVectorN**)&cptr=static_cast<ReactionVectorN*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else
                {
                    // return a ReactionVector
                    jclass clazz=jenv->FindClass("ReactionVector");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(ReactionVector**)&cptr=static_cast<ReactionVector*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CEvaluationTree>* >(pPointer))
            {
                if(dynamic_cast<CCopasiVectorN<CEvaluationTree>* >(pPointer))
                {
                    // return a CEvaluationTreeVectorN
                    jclass clazz=jenv->FindClass("CEvaluationTreeVectorN");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CEvaluationTreeVectorN**)&cptr=static_cast<CEvaluationTreeVectorN*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
                else
                {
                    // return a CEvaluationTreeVector
                    jclass clazz=jenv->FindClass("CEvaluationTreeVector");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CEvaluationTreeVector**)&cptr=static_cast<CEvaluationTreeVector*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CChemEqElement>* >(pPointer))
            {
                // return a CChemEqElementVector
                jclass clazz=jenv->FindClass("CChemEqElementVector");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CChemEqElementVector**)&cptr=static_cast<CChemEqElementVector*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
        }
        else
        {
            // return a CCopasiContainer
            jclass clazz=jenv->FindClass("CCopasiContainer");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CCopasiContainer**)&cptr=static_cast<CCopasiContainer*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
    }
    return result;
}

jobject DownCast_CCopasiObject(CCopasiObject* pPointer)
{
    jobject result=NULL;
    if(dynamic_cast<CCopasiContainer*>(pPointer))
    {
        if(dynamic_cast<CChemEq*>(pPointer))
        {
            // return a CChemEq
            jclass clazz=jenv->FindClass("CChemEq");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CChemEq**)&cptr=static_cast<CChemEq*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CChemEqElement*>(pPointer))
        {
            // return a CChemEqElement
            jclass clazz=jenv->FindClass("CChemEqElement");
            if(clazz)
            {
               jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
               if(mid)
               {
                 jlong cptr = 0;
                 *(CChemEqElement**)&cptr=static_cast<CChemEqElement*>(pPointer);
                 result = jenv->NewObject(clazz,mid,cptr,false);
               }
            }
        }
        else if(dynamic_cast<CCopasiTask*>(pPointer))
        {
            if(dynamic_cast<CTrajectoryTask*>(pPointer))
            {
                // return a CTrajectoryTask
                jclass clazz=jenv->FindClass("CTrajectoryTask");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CTrajectoryTask**)&cptr=static_cast<CTrajectoryTask*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
            else
            {
                // return a CCopasiTask
                jclass clazz=jenv->FindClass("CCopasiTask");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CCopasiTask**)&cptr=static_cast<CCopasiTask*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
        }
        else if(dynamic_cast<CCopasiParameter*>(pPointer))
        {
            if(dynamic_cast<CCopasiParameterGroup*>(pPointer))
            {
                if(dynamic_cast<CCopasiMethod*>(pPointer))
                {
                    if(dynamic_cast<CTrajectoryMethod*>(pPointer))
                    {
                        // return a CTrajectoryMethod
                        jclass clazz=jenv->FindClass("CTrajectoryMethod");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CTrajectoryMethod**)&cptr=static_cast<CTrajectoryMethod*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                    else
                    {
                        // return a CCopasiMethod
                        jclass clazz=jenv->FindClass("CCopasiMethod");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CCopasiMethod**)&cptr=static_cast<CCopasiMethod*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiProblem*>(pPointer))
                {
                    if(dynamic_cast<CTrajectoryProblem*>(pPointer))
                    {
                        // return a CTrajectoryProblem
                        jclass clazz=jenv->FindClass("CTrajectoryProblem");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CTrajectoryProblem**)&cptr=static_cast<CTrajectoryProblem*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                    else
                    {
                        // return a CCopasiProblem
                        jclass clazz=jenv->FindClass("CCopasiProblem");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CCopasiProblem**)&cptr=static_cast<CCopasiProblem*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else
                {
                    // return a CCopasiParameterGroup
                    jclass clazz=jenv->FindClass("CCopasiParameterGroup");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CCopasiParameterGroup**)&cptr=static_cast<CCopasiParameterGroup*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else
            {
                // return a CCopasiParameter
                jclass clazz=jenv->FindClass("CCopasiParameter");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CCopasiParameter**)&cptr=static_cast<CCopasiParameter*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
        }
        else if(dynamic_cast<CEvaluationTree*>(pPointer))
        {
            if(dynamic_cast<CFunction*>(pPointer))
            {
                // return a CFunction
                jclass clazz=jenv->FindClass("CFunction");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CFunction**)&cptr=static_cast<CFunction*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
            else
            {
                // return a CEvaluationTree
                jclass clazz=jenv->FindClass("CEvaluationTree");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CEvaluationTree**)&cptr=static_cast<CEvaluationTree*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
        }
        else if(dynamic_cast<CFunctionDB*>(pPointer))
        {
            // return a CFunctionDB
            jclass clazz=jenv->FindClass("CFunctionDB");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CFunctionDB**)&cptr=static_cast<CFunctionDB*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CFunctionParameter*>(pPointer))
        {
            // return a CFunctionParameter
            jclass clazz=jenv->FindClass("CFunctionParameter");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CFunctionParameter**)&cptr=static_cast<CFunctionParameter*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CFunctionParameters*>(pPointer))
        {
            // return a CFunctionParameters
            jclass clazz=jenv->FindClass("CFunctionParameters");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CFunctionParameters**)&cptr=static_cast<CFunctionParameters*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CModelEntity*>(pPointer))
        {
            if(dynamic_cast<CCompartment*>(pPointer))
            {
                // return a CCompartment
                jclass clazz=jenv->FindClass("CCompartment");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CCompartment**)&cptr=static_cast<CCompartment*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
            else if(dynamic_cast<CMetab*>(pPointer))
            {
                // return a CMetab
                jclass clazz=jenv->FindClass("CMetab");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CMetab**)&cptr=static_cast<CMetab*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
            else if(dynamic_cast<CModel*>(pPointer))
            {
                // return a CModel
                jclass clazz=jenv->FindClass("CModel");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CModel**)&cptr=static_cast<CModel*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
            else if(dynamic_cast<CModelValue*>(pPointer))
            {
                // return a CModelValue
                jclass clazz=jenv->FindClass("CModelValue");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CModelValue**)&cptr=static_cast<CModelValue*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
            else
            {
                // return a CModelEntity
                jclass clazz=jenv->FindClass("CModelEntity");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CModelEntity**)&cptr=static_cast<CModelEntity*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }

        }
        else if(dynamic_cast<CMoiety*>(pPointer))
        {
            // return a CMoiety
            jclass clazz=jenv->FindClass("CMoiety");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CMoiety**)&cptr=static_cast<CMoiety*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CReaction*>(pPointer))
        {
            // return a CReaction
            jclass clazz=jenv->FindClass("CReaction");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CReaction**)&cptr=static_cast<CReaction*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CReport*>(pPointer))
        {
            // return a CReport
            jclass clazz=jenv->FindClass("CReport");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CReport**)&cptr=static_cast<CReport*>(pPointer);
                    result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else
        {
            if(pPointer->isVector())
            {
                if(dynamic_cast<CCopasiVector<CCopasiTask>* >(pPointer))
                {
                    if(dynamic_cast<CCopasiVectorN<CCopasiTask>* >(pPointer))
                    {
                        // return a TaskVectorN
                        jclass clazz=jenv->FindClass("TaskVectorN");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(TaskVectorN**)&cptr=static_cast<TaskVectorN*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                    else
                    {
                        // return a TaskVector
                        jclass clazz=jenv->FindClass("TaskVector");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(TaskVector**)&cptr=static_cast<TaskVector*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CModelValue>* >(pPointer))
                {
                    if(dynamic_cast<CCopasiVectorN<CModelValue>* >(pPointer))
                    {
                        // return a ModelValueVectorN
                        jclass clazz=jenv->FindClass("ModelValueVectorN");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(ModelValueVectorN**)&cptr=static_cast<ModelValueVectorN*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                    else
                    {
                        // return a ModelValueVector
                        jclass clazz=jenv->FindClass("ModelValueVector");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(ModelValueVector**)&cptr=static_cast<ModelValueVector*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CReportDefinition>* >(pPointer))
                {
                    if(dynamic_cast<CCopasiVectorN<CReportDefinition>* >(pPointer))
                    {
                      // return a CCReportDefinitionVectorN
                      jclass clazz=jenv->FindClass("CReportDefinitionVectorN");
                      if(clazz)
                      {
                          jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                          if(mid)
                          {
                              jlong cptr = 0;
                              *(CReportDefinitionVectorN**)&cptr=static_cast<CReportDefinitionVectorN*>(pPointer);
                              result = jenv->NewObject(clazz,mid,cptr,false);
                          }
                      }
                    }
                    else
                    {
                        // return a CReportDefinitionVector
                        jclass clazz=jenv->FindClass("CReportDefinitionVector");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CReportDefinitionVector**)&cptr=static_cast<CReportDefinitionVector*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CMoiety>* >(pPointer))
                {
                    // return a MoietyVector
                    jclass clazz=jenv->FindClass("MoietyVector");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(MoietyVector**)&cptr=static_cast<MoietyVector*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CMetab>* >(pPointer))
                {
                    if(dynamic_cast<CCopasiVectorN<CMetab>* >(pPointer))
                    {
                        if(dynamic_cast<CCopasiVectorNS<CMetab>* >(pPointer))
                        {
                            // return a MetabVectorNS
                            jclass clazz=jenv->FindClass("MetabVectorNS");
                            if(clazz)
                            {
                                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                                if(mid)
                                {
                                    jlong cptr = 0;
                                    *(MetabVectorNS**)&cptr=static_cast<MetabVectorNS*>(pPointer);
                                    result = jenv->NewObject(clazz,mid,cptr,false);
                                }
                            }
                        }
                        else
                        {
                            // return a MetabVectorN
                            jclass clazz=jenv->FindClass("MetabVectorN");
                            if(clazz)
                            {
                                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                                if(mid)
                                {
                                    jlong cptr = 0;
                                    *(MetabVectorN**)&cptr=static_cast<MetabVectorN*>(pPointer);
                                    result = jenv->NewObject(clazz,mid,cptr,false);
                                }
                            }
                        }
                    }
                    else
                    {
                        // return a MetabVector
                        jclass clazz=jenv->FindClass("MetabVector");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(MetabVector**)&cptr=static_cast<MetabVector*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CCompartment>* >(pPointer))
                {
                    if(dynamic_cast<CCopasiVectorN<CCompartment>* >(pPointer))
                    {
                        if(dynamic_cast<CCopasiVectorNS<CCompartment>* >(pPointer))
                        {
                            // return a CompartmentVectorNS
                            jclass clazz=jenv->FindClass("CompartmentVectorNS");
                            if(clazz)
                            {
                                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                                if(mid)
                                {
                                    jlong cptr = 0;
                                    *(CompartmentVectorNS**)&cptr=static_cast<CompartmentVectorNS*>(pPointer);
                                    result = jenv->NewObject(clazz,mid,cptr,false);
                                }
                            }
                        }
                        else
                        {
                            // return a CompartmentVectorN
                            jclass clazz=jenv->FindClass("CompartmentVectorN");
                            if(clazz)
                            {
                                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                                if(mid)
                                {
                                    jlong cptr = 0;
                                    *(CompartmentVectorN**)&cptr=static_cast<CompartmentVectorN*>(pPointer);
                                    result = jenv->NewObject(clazz,mid,cptr,false);
                                }
                            }
                        }
                    }
                    else
                    {
                        // return a CompartmentVector
                        jclass clazz=jenv->FindClass("CompartmentVector");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CompartmentVector**)&cptr=static_cast<CompartmentVector*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CReaction>* >(pPointer))
                {
                    if(dynamic_cast<CCopasiVectorN<CReaction>* >(pPointer))
                    {
                        if(dynamic_cast<CCopasiVectorNS<CReaction>* >(pPointer))
                        {
                            // return a ReactionVectorNS
                            jclass clazz=jenv->FindClass("ReactionVectorNS");
                            if(clazz)
                            {
                                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                                if(mid)
                                {
                                    jlong cptr = 0;
                                    *(ReactionVectorNS**)&cptr=static_cast<ReactionVectorNS*>(pPointer);
                                    result = jenv->NewObject(clazz,mid,cptr,false);
                                }
                            }
                        }
                        else
                        {
                            // return a ReactionVectorN
                            jclass clazz=jenv->FindClass("ReactionVectorN");
                            if(clazz)
                            {
                                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                                if(mid)
                                {
                                    jlong cptr = 0;
                                    *(ReactionVectorN**)&cptr=static_cast<ReactionVectorN*>(pPointer);
                                    result = jenv->NewObject(clazz,mid,cptr,false);
                                }
                            }
                        }
                    }
                    else
                    {
                        // return a ReactionVector
                        jclass clazz=jenv->FindClass("ReactionVector");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(ReactionVector**)&cptr=static_cast<ReactionVector*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CEvaluationTree>* >(pPointer))
                {
                    if(dynamic_cast<CCopasiVectorN<CEvaluationTree>* >(pPointer))
                    {
                        // return a CEvaluationTreeVectorN
                        jclass clazz=jenv->FindClass("CEvaluationTreeVectorN");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CEvaluationTreeVectorN**)&cptr=static_cast<CEvaluationTreeVectorN*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                    else
                    {
                        // return a CEvaluationTreeVector
                        jclass clazz=jenv->FindClass("CEvaluationTreeVector");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CEvaluationTreeVector**)&cptr=static_cast<CEvaluationTreeVector*>(pPointer);
                                result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CChemEqElement>* >(pPointer))
                {
                    // return a CChemEqElementVector
                    jclass clazz=jenv->FindClass("CChemEqElementVector");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CChemEqElementVector**)&cptr=static_cast<CChemEqElementVector*>(pPointer);
                            result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else
            {
                // return a CCopasiContainer
                jclass clazz=jenv->FindClass("CCopasiContainer");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CCopasiContainer**)&cptr=static_cast<CCopasiContainer*>(pPointer);
                        result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
        }
    }
    else if(dynamic_cast<CReportDefinition*>(pPointer))
    {
      // return a CReportDefinition
      jclass clazz=jenv->FindClass("CReportDefinition");
      if(clazz)
      {
          jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
          if(mid)
          {
              jlong cptr = 0;
              *(CReportDefinition**)&cptr=static_cast<CReportDefinition*>(pPointer);
              result = jenv->NewObject(clazz,mid,cptr,false);
          }
      }
    }
    else if(dynamic_cast<CCopasiStaticString*>(pPointer))
    {
        if(dynamic_cast<CCopasiReportSeparator*>(pPointer))
        {
          // return a CCopasiReportSeparator
        jclass clazz=jenv->FindClass("CCopasiReportSeparator");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CCopasiReportSeparator**)&cptr=static_cast<CCopasiReportSeparator*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
        }
        else
        {
          // return a CCopasiStaticString
          jclass clazz=jenv->FindClass("CCopasiStaticString");
          if(clazz)
          {
              jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
              if(mid)
              {
                  jlong cptr = 0;
                  *(CCopasiStaticString**)&cptr=static_cast<CCopasiStaticString*>(pPointer);
                  result = jenv->NewObject(clazz,mid,cptr,false);
              }
          }
        }
    }
    else
    {
        // return a CCopasiObject
        jclass clazz=jenv->FindClass("CCopasiObject");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CCopasiObject**)&cptr=static_cast<CCopasiObject*>(pPointer);
                result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    return result;
}

%}


void initCopasi();

%typemap(jni) CModelEntity* "jobject"
%typemap(jtype) CModelEntity* "CModelEntity"
%typemap(jstype) CModelEntity* "CModelEntity"
%typemap(javaout) CModelEntity* 
{
    return $jnicall;
}

%typemap(out) CModelEntity* 
{
    $result = DownCast_CModelEntity($1);
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
    $result = DownCast_CEvaluationTree($1);
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
    $result=DownCast_CCopasiTask($1);
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
    $result = DownCast_CCopasiMethod($1);
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
    $result = DownCast_CCopasiProblem($1);
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
    $result = DownCast_CCopasiParameterGroup($1);
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
    $result = DownCast_CCopasiParameter($1);
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
    $result = DownCast_CCopasiContainer($1);
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
    $result = DownCast_CCopasiObject($1);
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}



%include "../swig/copasi.i"


