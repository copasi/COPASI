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



%include "../swig/copasi.i"


