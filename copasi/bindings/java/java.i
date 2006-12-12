/**
 * Make COPASI and wrapper constants Java compile-time
 * constants so they may be used in switch statements.
 */
%include "enumsimple.swg"
%javaconst(1);

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
    if(dynamic_cast<CCompartment*>($1))
    {
        // return a CCompartment
        jclass clazz=jenv->FindClass("CCompartment");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CCompartment**)&cptr=static_cast<CCompartment*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CMetab*>($1))
    {
        // return a CMetab
        jclass clazz=jenv->FindClass("CMetab");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CMetab**)&cptr=static_cast<CMetab*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CModel*>($1))
    {
        // return a CModel
        jclass clazz=jenv->FindClass("CModel");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CModel**)&cptr=static_cast<CModel*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CModelValue*>($1))
    {
        // return a CModelValue
        jclass clazz=jenv->FindClass("CModelValue");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CModelValue**)&cptr=static_cast<CModelValue*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                *(CModelEntity**)&cptr=static_cast<CModelEntity*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
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
    if(dynamic_cast<CFunction*>($1))
    {
        // return a CFunction
        jclass clazz=jenv->FindClass("CFunction");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CFunction**)&cptr=static_cast<CFunction*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                *(CEvaluationTree**)&cptr=static_cast<CEvaluationTree*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
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
    if(dynamic_cast<CTrajectoryTask*>($1))
    {
        // return a CTrajectoryTask
        jclass clazz=jenv->FindClass("CTrajectoryTask");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CTrajectoryTask**)&cptr=static_cast<CTrajectoryTask*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                *(CCopasiTask**)&cptr=static_cast<CCopasiTask*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
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
    if(dynamic_cast<CTrajectoryMethod*>($1))
    {
        // return a CTrajectoryMethod
        jclass clazz=jenv->FindClass("CTrajectoryMethod");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CTrajectoryMethod**)&cptr=static_cast<CTrajectoryMethod*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                *(CCopasiMethod**)&cptr=static_cast<CCopasiMethod*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
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
    if(dynamic_cast<CTrajectoryProblem*>($1))
    {
        // return a CTrajectoryProblem
        jclass clazz=jenv->FindClass("CTrajectoryProblem");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CTrajectoryProblem**)&cptr=static_cast<CTrajectoryProblem*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                *(CCopasiProblem**)&cptr=static_cast<CCopasiProblem*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
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
    if(dynamic_cast<CCopasiMethod*>($1))
    {
        if(dynamic_cast<CTrajectoryMethod*>($1))
        {
            // return a CTrajectoryMethod
            jclass clazz=jenv->FindClass("CTrajectoryMethod");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CTrajectoryMethod**)&cptr=static_cast<CTrajectoryMethod*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
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
                    *(CCopasiMethod**)&cptr=static_cast<CCopasiMethod*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
    }
    else if(dynamic_cast<CCopasiProblem*>($1))
    {
        if(dynamic_cast<CTrajectoryProblem*>($1))
        {
            // return a CTrajectoryProblem
            jclass clazz=jenv->FindClass("CTrajectoryProblem");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CTrajectoryProblem**)&cptr=static_cast<CTrajectoryProblem*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
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
                    *(CCopasiProblem**)&cptr=static_cast<CCopasiProblem*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
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
                *(CCopasiParameterGroup**)&cptr=static_cast<CCopasiParameterGroup*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
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
    if(dynamic_cast<CCopasiParameterGroup*>($1))
    {
        if(dynamic_cast<CCopasiMethod*>($1))
        {
            if(dynamic_cast<CTrajectoryMethod*>($1))
            {
                // return a CTrajectoryMethod
                jclass clazz=jenv->FindClass("CTrajectoryMethod");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CTrajectoryMethod**)&cptr=static_cast<CTrajectoryMethod*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
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
                        *(CCopasiMethod**)&cptr=static_cast<CCopasiMethod*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
        }
        else if(dynamic_cast<CCopasiProblem*>($1))
        {
            if(dynamic_cast<CTrajectoryProblem*>($1))
            {
                // return a CTrajectoryProblem
                jclass clazz=jenv->FindClass("CTrajectoryProblem");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CTrajectoryProblem**)&cptr=static_cast<CTrajectoryProblem*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
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
                        *(CCopasiProblem**)&cptr=static_cast<CCopasiProblem*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
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
                    *(CCopasiParameterGroup**)&cptr=static_cast<CCopasiParameterGroup*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
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
                *(CCopasiParameter**)&cptr=static_cast<CCopasiParameter*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
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
    if(dynamic_cast<CChemEq*>($1))
    {
        // return a CChemEq
        jclass clazz=jenv->FindClass("CChemEq");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CChemEq**)&cptr=static_cast<CChemEq*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CChemEqElement*>($1))
    {
        // return a CChemEqElement
        jclass clazz=jenv->FindClass("CChemEqElement");
        if(clazz)
        {
           jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
           if(mid)
           {
             jlong cptr = 0;
             *(CChemEqElement**)&cptr=static_cast<CChemEqElement*>($1);
             $result = jenv->NewObject(clazz,mid,cptr,false);
           }
        }
    }
    else if(dynamic_cast<CCopasiTask*>($1))
    {
        if(dynamic_cast<CTrajectoryTask*>($1))
        {
            // return a CTrajectoryTask
            jclass clazz=jenv->FindClass("CTrajectoryTask");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CTrajectoryTask**)&cptr=static_cast<CTrajectoryTask*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
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
                    *(CCopasiTask**)&cptr=static_cast<CCopasiTask*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
    }
    else if(dynamic_cast<CCopasiParameter*>($1))
    {
        if(dynamic_cast<CCopasiParameterGroup*>($1))
        {
            if(dynamic_cast<CCopasiMethod*>($1))
            {
                if(dynamic_cast<CTrajectoryMethod*>($1))
                {
                    // return a CTrajectoryMethod
                    jclass clazz=jenv->FindClass("CTrajectoryMethod");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CTrajectoryMethod**)&cptr=static_cast<CTrajectoryMethod*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
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
                            *(CCopasiMethod**)&cptr=static_cast<CCopasiMethod*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiProblem*>($1))
            {
                if(dynamic_cast<CTrajectoryProblem*>($1))
                {
                    // return a CTrajectoryProblem
                    jclass clazz=jenv->FindClass("CTrajectoryProblem");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CTrajectoryProblem**)&cptr=static_cast<CTrajectoryProblem*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
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
                            *(CCopasiProblem**)&cptr=static_cast<CCopasiProblem*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
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
                        *(CCopasiParameterGroup**)&cptr=static_cast<CCopasiParameterGroup*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
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
                    *(CCopasiParameter**)&cptr=static_cast<CCopasiParameter*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
    }
    else if(dynamic_cast<CEvaluationTree*>($1))
    {
        if(dynamic_cast<CFunction*>($1))
        {
            // return a CFunction
            jclass clazz=jenv->FindClass("CFunction");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CFunction**)&cptr=static_cast<CFunction*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
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
                    *(CEvaluationTree**)&cptr=static_cast<CEvaluationTree*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
    }
    else if(dynamic_cast<CFunctionDB*>($1))
    {
        // return a CFunctionDB
        jclass clazz=jenv->FindClass("CFunctionDB");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CFunctionDB**)&cptr=static_cast<CFunctionDB*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CFunctionParameter*>($1))
    {
        // return a CFunctionParameter
        jclass clazz=jenv->FindClass("CFunctionParameter");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CFunctionParameter**)&cptr=static_cast<CFunctionParameter*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CFunctionParameters*>($1))
    {
        // return a CFunctionParameters
        jclass clazz=jenv->FindClass("CFunctionParameters");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CFunctionParameters**)&cptr=static_cast<CFunctionParameters*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CModelEntity*>($1))
    {
        if(dynamic_cast<CCompartment*>($1))
        {
            // return a CCompartment
            jclass clazz=jenv->FindClass("CCompartment");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CCompartment**)&cptr=static_cast<CCompartment*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CMetab*>($1))
        {
            // return a CMetab
            jclass clazz=jenv->FindClass("CMetab");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CMetab**)&cptr=static_cast<CMetab*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CModel*>($1))
        {
            // return a CModel
            jclass clazz=jenv->FindClass("CModel");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CModel**)&cptr=static_cast<CModel*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CModelValue*>($1))
        {
            // return a CModelValue
            jclass clazz=jenv->FindClass("CModelValue");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CModelValue**)&cptr=static_cast<CModelValue*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
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
                    *(CModelEntity**)&cptr=static_cast<CModelEntity*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }

    }
    else if(dynamic_cast<CMoiety*>($1))
    {
        // return a CMoiety
        jclass clazz=jenv->FindClass("CMoiety");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CMoiety**)&cptr=static_cast<CMoiety*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CReaction*>($1))
    {
        // return a CReaction
        jclass clazz=jenv->FindClass("CReaction");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CReaction**)&cptr=static_cast<CReaction*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else if(dynamic_cast<CReport*>($1))
    {
        // return a CReport
        jclass clazz=jenv->FindClass("CReport");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CReport**)&cptr=static_cast<CReport*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    else
    {
        if($1->isVector())
        {
            if(dynamic_cast<CCopasiVector<CCopasiTask>* >($1))
            {
                if(dynamic_cast<CCopasiVectorN<CCopasiTask>* >($1))
                {
                    // return a TaskVectorN
                    jclass clazz=jenv->FindClass("TaskVectorN");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(TaskVectorN**)&cptr=static_cast<TaskVectorN*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
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
                            *(TaskVector**)&cptr=static_cast<TaskVector*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CModelValue>* >($1))
            {
                if(dynamic_cast<CCopasiVectorN<CModelValue>* >($1))
                {
                    // return a ModelValueVectorN
                    jclass clazz=jenv->FindClass("ModelValueVectorN");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(ModelValueVectorN**)&cptr=static_cast<ModelValueVectorN*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
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
                            *(ModelValueVector**)&cptr=static_cast<ModelValueVector*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CReportDefinition>* >($1))
            {
                if(dynamic_cast<CCopasiVectorN<CReportDefinition>* >($1))
                {
                  // return a CCReportDefinitionVectorN
                  jclass clazz=jenv->FindClass("CReportDefinitionVectorN");
                  if(clazz)
                  {
                      jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                      if(mid)
                      {
                          jlong cptr = 0;
                          *(CReportDefinitionVectorN**)&cptr=static_cast<CReportDefinitionVectorN*>($1);
                          $result = jenv->NewObject(clazz,mid,cptr,false);
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
                            *(CReportDefinitionVector**)&cptr=static_cast<CReportDefinitionVector*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CMoiety>* >($1))
            {
                // return a MoietyVector
                jclass clazz=jenv->FindClass("MoietyVector");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(MoietyVector**)&cptr=static_cast<MoietyVector*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CMetab>* >($1))
            {
                if(dynamic_cast<CCopasiVectorN<CMetab>* >($1))
                {
                    if(dynamic_cast<CCopasiVectorNS<CMetab>* >($1))
                    {
                        // return a MetabVectorNS
                        jclass clazz=jenv->FindClass("MetabVectorNS");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(MetabVectorNS**)&cptr=static_cast<MetabVectorNS*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                *(MetabVectorN**)&cptr=static_cast<MetabVectorN*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                            *(MetabVector**)&cptr=static_cast<MetabVector*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CCompartment>* >($1))
            {
                if(dynamic_cast<CCopasiVectorN<CCompartment>* >($1))
                {
                    if(dynamic_cast<CCopasiVectorNS<CCompartment>* >($1))
                    {
                        // return a CompartmentVectorNS
                        jclass clazz=jenv->FindClass("CompartmentVectorNS");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CompartmentVectorNS**)&cptr=static_cast<CompartmentVectorNS*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                *(CompartmentVectorN**)&cptr=static_cast<CompartmentVectorN*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                            *(CompartmentVector**)&cptr=static_cast<CompartmentVector*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CReaction>* >($1))
            {
                if(dynamic_cast<CCopasiVectorN<CReaction>* >($1))
                {
                    if(dynamic_cast<CCopasiVectorNS<CReaction>* >($1))
                    {
                        // return a ReactionVectorNS
                        jclass clazz=jenv->FindClass("ReactionVectorNS");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(ReactionVectorNS**)&cptr=static_cast<ReactionVectorNS*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                *(ReactionVectorN**)&cptr=static_cast<ReactionVectorN*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                            *(ReactionVector**)&cptr=static_cast<ReactionVector*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CEvaluationTree>* >($1))
            {
                if(dynamic_cast<CCopasiVectorN<CEvaluationTree>* >($1))
                {
                    // return a CEvaluationTreeVectorN
                    jclass clazz=jenv->FindClass("CEvaluationTreeVectorN");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CEvaluationTreeVectorN**)&cptr=static_cast<CEvaluationTreeVectorN*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
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
                            *(CEvaluationTreeVector**)&cptr=static_cast<CEvaluationTreeVector*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
            }
            else if(dynamic_cast<CCopasiVector<CChemEqElement>* >($1))
            {
                // return a CChemEqElementVector
                jclass clazz=jenv->FindClass("CChemEqElementVector");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CChemEqElementVector**)&cptr=static_cast<CChemEqElementVector*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
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
                    *(CCopasiContainer**)&cptr=static_cast<CCopasiContainer*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
    }
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
    
    if(dynamic_cast<CCopasiContainer*>($1))
    {
        if(dynamic_cast<CChemEq*>($1))
        {
            // return a CChemEq
            jclass clazz=jenv->FindClass("CChemEq");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CChemEq**)&cptr=static_cast<CChemEq*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CChemEqElement*>($1))
        {
            // return a CChemEqElement
            jclass clazz=jenv->FindClass("CChemEqElement");
            if(clazz)
            {
               jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
               if(mid)
               {
                 jlong cptr = 0;
                 *(CChemEqElement**)&cptr=static_cast<CChemEqElement*>($1);
                 $result = jenv->NewObject(clazz,mid,cptr,false);
               }
            }
        }
        else if(dynamic_cast<CCopasiTask*>($1))
        {
            if(dynamic_cast<CTrajectoryTask*>($1))
            {
                // return a CTrajectoryTask
                jclass clazz=jenv->FindClass("CTrajectoryTask");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CTrajectoryTask**)&cptr=static_cast<CTrajectoryTask*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
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
                        *(CCopasiTask**)&cptr=static_cast<CCopasiTask*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
        }
        else if(dynamic_cast<CCopasiParameter*>($1))
        {
            if(dynamic_cast<CCopasiParameterGroup*>($1))
            {
                if(dynamic_cast<CCopasiMethod*>($1))
                {
                    if(dynamic_cast<CTrajectoryMethod*>($1))
                    {
                        // return a CTrajectoryMethod
                        jclass clazz=jenv->FindClass("CTrajectoryMethod");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CTrajectoryMethod**)&cptr=static_cast<CTrajectoryMethod*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                *(CCopasiMethod**)&cptr=static_cast<CCopasiMethod*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiProblem*>($1))
                {
                    if(dynamic_cast<CTrajectoryProblem*>($1))
                    {
                        // return a CTrajectoryProblem
                        jclass clazz=jenv->FindClass("CTrajectoryProblem");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CTrajectoryProblem**)&cptr=static_cast<CTrajectoryProblem*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                *(CCopasiProblem**)&cptr=static_cast<CCopasiProblem*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                            *(CCopasiParameterGroup**)&cptr=static_cast<CCopasiParameterGroup*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
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
                        *(CCopasiParameter**)&cptr=static_cast<CCopasiParameter*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
        }
        else if(dynamic_cast<CEvaluationTree*>($1))
        {
            if(dynamic_cast<CFunction*>($1))
            {
                // return a CFunction
                jclass clazz=jenv->FindClass("CFunction");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CFunction**)&cptr=static_cast<CFunction*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
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
                        *(CEvaluationTree**)&cptr=static_cast<CEvaluationTree*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
        }
        else if(dynamic_cast<CFunctionDB*>($1))
        {
            // return a CFunctionDB
            jclass clazz=jenv->FindClass("CFunctionDB");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CFunctionDB**)&cptr=static_cast<CFunctionDB*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CFunctionParameter*>($1))
        {
            // return a CFunctionParameter
            jclass clazz=jenv->FindClass("CFunctionParameter");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CFunctionParameter**)&cptr=static_cast<CFunctionParameter*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CFunctionParameters*>($1))
        {
            // return a CFunctionParameters
            jclass clazz=jenv->FindClass("CFunctionParameters");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CFunctionParameters**)&cptr=static_cast<CFunctionParameters*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CModelEntity*>($1))
        {
            if(dynamic_cast<CCompartment*>($1))
            {
                // return a CCompartment
                jclass clazz=jenv->FindClass("CCompartment");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CCompartment**)&cptr=static_cast<CCompartment*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
            else if(dynamic_cast<CMetab*>($1))
            {
                // return a CMetab
                jclass clazz=jenv->FindClass("CMetab");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CMetab**)&cptr=static_cast<CMetab*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
            else if(dynamic_cast<CModel*>($1))
            {
                // return a CModel
                jclass clazz=jenv->FindClass("CModel");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CModel**)&cptr=static_cast<CModel*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
            else if(dynamic_cast<CModelValue*>($1))
            {
                // return a CModelValue
                jclass clazz=jenv->FindClass("CModelValue");
                if(clazz)
                {
                    jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                    if(mid)
                    {
                        jlong cptr = 0;
                        *(CModelValue**)&cptr=static_cast<CModelValue*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
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
                        *(CModelEntity**)&cptr=static_cast<CModelEntity*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }

        }
        else if(dynamic_cast<CMoiety*>($1))
        {
            // return a CMoiety
            jclass clazz=jenv->FindClass("CMoiety");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CMoiety**)&cptr=static_cast<CMoiety*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CReaction*>($1))
        {
            // return a CReaction
            jclass clazz=jenv->FindClass("CReaction");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CReaction**)&cptr=static_cast<CReaction*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else if(dynamic_cast<CReport*>($1))
        {
            // return a CReport
            jclass clazz=jenv->FindClass("CReport");
            if(clazz)
            {
                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                if(mid)
                {
                    jlong cptr = 0;
                    *(CReport**)&cptr=static_cast<CReport*>($1);
                    $result = jenv->NewObject(clazz,mid,cptr,false);
                }
            }
        }
        else
        {
            if($1->isVector())
            {
                if(dynamic_cast<CCopasiVector<CCopasiTask>* >($1))
                {
                    if(dynamic_cast<CCopasiVectorN<CCopasiTask>* >($1))
                    {
                        // return a TaskVectorN
                        jclass clazz=jenv->FindClass("TaskVectorN");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(TaskVectorN**)&cptr=static_cast<TaskVectorN*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                *(TaskVector**)&cptr=static_cast<TaskVector*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CModelValue>* >($1))
                {
                    if(dynamic_cast<CCopasiVectorN<CModelValue>* >($1))
                    {
                        // return a ModelValueVectorN
                        jclass clazz=jenv->FindClass("ModelValueVectorN");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(ModelValueVectorN**)&cptr=static_cast<ModelValueVectorN*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                *(ModelValueVector**)&cptr=static_cast<ModelValueVector*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CReportDefinition>* >($1))
                {
                    if(dynamic_cast<CCopasiVectorN<CReportDefinition>* >($1))
                    {
                      // return a CCReportDefinitionVectorN
                      jclass clazz=jenv->FindClass("CReportDefinitionVectorN");
                      if(clazz)
                      {
                          jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                          if(mid)
                          {
                              jlong cptr = 0;
                              *(CReportDefinitionVectorN**)&cptr=static_cast<CReportDefinitionVectorN*>($1);
                              $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                *(CReportDefinitionVector**)&cptr=static_cast<CReportDefinitionVector*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CMoiety>* >($1))
                {
                    // return a MoietyVector
                    jclass clazz=jenv->FindClass("MoietyVector");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(MoietyVector**)&cptr=static_cast<MoietyVector*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CMetab>* >($1))
                {
                    if(dynamic_cast<CCopasiVectorN<CMetab>* >($1))
                    {
                        if(dynamic_cast<CCopasiVectorNS<CMetab>* >($1))
                        {
                            // return a MetabVectorNS
                            jclass clazz=jenv->FindClass("MetabVectorNS");
                            if(clazz)
                            {
                                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                                if(mid)
                                {
                                    jlong cptr = 0;
                                    *(MetabVectorNS**)&cptr=static_cast<MetabVectorNS*>($1);
                                    $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                    *(MetabVectorN**)&cptr=static_cast<MetabVectorN*>($1);
                                    $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                *(MetabVector**)&cptr=static_cast<MetabVector*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CCompartment>* >($1))
                {
                    if(dynamic_cast<CCopasiVectorN<CCompartment>* >($1))
                    {
                        if(dynamic_cast<CCopasiVectorNS<CCompartment>* >($1))
                        {
                            // return a CompartmentVectorNS
                            jclass clazz=jenv->FindClass("CompartmentVectorNS");
                            if(clazz)
                            {
                                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                                if(mid)
                                {
                                    jlong cptr = 0;
                                    *(CompartmentVectorNS**)&cptr=static_cast<CompartmentVectorNS*>($1);
                                    $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                    *(CompartmentVectorN**)&cptr=static_cast<CompartmentVectorN*>($1);
                                    $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                *(CompartmentVector**)&cptr=static_cast<CompartmentVector*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CReaction>* >($1))
                {
                    if(dynamic_cast<CCopasiVectorN<CReaction>* >($1))
                    {
                        if(dynamic_cast<CCopasiVectorNS<CReaction>* >($1))
                        {
                            // return a ReactionVectorNS
                            jclass clazz=jenv->FindClass("ReactionVectorNS");
                            if(clazz)
                            {
                                jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                                if(mid)
                                {
                                    jlong cptr = 0;
                                    *(ReactionVectorNS**)&cptr=static_cast<ReactionVectorNS*>($1);
                                    $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                    *(ReactionVectorN**)&cptr=static_cast<ReactionVectorN*>($1);
                                    $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                *(ReactionVector**)&cptr=static_cast<ReactionVector*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CEvaluationTree>* >($1))
                {
                    if(dynamic_cast<CCopasiVectorN<CEvaluationTree>* >($1))
                    {
                        // return a CEvaluationTreeVectorN
                        jclass clazz=jenv->FindClass("CEvaluationTreeVectorN");
                        if(clazz)
                        {
                            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                            if(mid)
                            {
                                jlong cptr = 0;
                                *(CEvaluationTreeVectorN**)&cptr=static_cast<CEvaluationTreeVectorN*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                                *(CEvaluationTreeVector**)&cptr=static_cast<CEvaluationTreeVector*>($1);
                                $result = jenv->NewObject(clazz,mid,cptr,false);
                            }
                        }
                    }
                }
                else if(dynamic_cast<CCopasiVector<CChemEqElement>* >($1))
                {
                    // return a CChemEqElementVector
                    jclass clazz=jenv->FindClass("CChemEqElementVector");
                    if(clazz)
                    {
                        jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
                        if(mid)
                        {
                            jlong cptr = 0;
                            *(CChemEqElementVector**)&cptr=static_cast<CChemEqElementVector*>($1);
                            $result = jenv->NewObject(clazz,mid,cptr,false);
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
                        *(CCopasiContainer**)&cptr=static_cast<CCopasiContainer*>($1);
                        $result = jenv->NewObject(clazz,mid,cptr,false);
                    }
                }
            }
        }
    }
    else if(dynamic_cast<CReportDefinition*>($1))
    {
      // return a CReportDefinition
      jclass clazz=jenv->FindClass("CReportDefinition");
      if(clazz)
      {
          jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
          if(mid)
          {
              jlong cptr = 0;
              *(CReportDefinition**)&cptr=static_cast<CReportDefinition*>($1);
              $result = jenv->NewObject(clazz,mid,cptr,false);
          }
      }
    }
    else if(dynamic_cast<CCopasiStaticString*>($1))
    {
        if(dynamic_cast<CCopasiReportSeparator*>($1))
        {
          // return a CCopasiReportSeparator
        jclass clazz=jenv->FindClass("CCopasiReportSeparator");
        if(clazz)
        {
            jmethodID mid=jenv->GetMethodID(clazz,"<init>","(JZ)V");
            if(mid)
            {
                jlong cptr = 0;
                *(CCopasiReportSeparator**)&cptr=static_cast<CCopasiReportSeparator*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
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
                  *(CCopasiStaticString**)&cptr=static_cast<CCopasiStaticString*>($1);
                  $result = jenv->NewObject(clazz,mid,cptr,false);
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
                *(CCopasiObject**)&cptr=static_cast<CCopasiObject*>($1);
                $result = jenv->NewObject(clazz,mid,cptr,false);
            }
        }
    }
    if(!$result)
    {
        std::cout << "Failed to create new java object" << std::endl;
    }
}



%include "../swig/copasi.i"


