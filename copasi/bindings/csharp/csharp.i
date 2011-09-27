// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/csharp/csharp.i,v $ 
//   $Revision: 1.1.2.4 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/09/27 14:58:06 $ 
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
  static $imclassname() {
    initCopasi();
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




/*
%typemap(ctype) CCopasiAbstractArray* CArrayAnnotation::array "jobject"
%typemap(imtype) CCopasiAbstractArray* CArrayAnnotation::array "CCopasiAbstractArray"
%typemap(cstype) CCopasiAbstractArray* CArrayAnnotation::array "CCopasiAbstractArray"
%typemap(csout) CCopasiAbstractArray* CArrayAnnotation::array 
{
  return $imcall;
}
%typemap(out) CCopasiAbstractArray* CArrayAnnotation::array
{
    $result = DownCast_CCopasiAbstractArray(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}


%typemap(ctype) CCopasiTask* CCopasiDataModel::addTask "jobject"
%typemap(imtype) CCopasiTask* CCopasiDataModel::addTask "CCopasiTask"
%typemap(cstype) CCopasiTask* CCopasiDataModel::addTask "CCopasiTask"
%typemap(csout) CCopasiTask* CCopasiDataModel::addTask 
{
  return $imcall;
}
%typemap(out) CCopasiTask* CCopasiDataModel::addTask
{
    $result = DownCast_CCopasiTask(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}

%typemap(ctype) CCopasiTask* CCopasiDataModel::getTask "jobject"
%typemap(imtype) CCopasiTask* CCopasiDataModel::getTask "CCopasiTask"
%typemap(cstype) CCopasiTask* CCopasiDataModel::getTask "CCopasiTask"
%typemap(csout) CCopasiTask* CCopasiDataModel::getTask 
{
  return $imcall;
}
%typemap(out) CCopasiTask* CCopasiDataModel::getTask
{
    $result = DownCast_CCopasiTask(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}

%typemap(ctype) CCopasiObject* CKeyFactory::get "jobject"
%typemap(imtype) CCopasiObject* CKeyFactory::get "CCopasiObject"
%typemap(cstype) CCopasiObject* CKeyFactory::get "CCopasiObject"
%typemap(csout) CCopasiObject* CKeyFactory::get
{
  return $imcall;
}
%typemap(out) CCopasiObject* CKeyFactory::get
{
    $result = DownCast_CCopasiObject(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}


%typemap(ctype) CCopasiContainer* CCopasiObject::getObjectParent "jobject"
%typemap(imtype) CCopasiContainer* CCopasiObject::getObjectParent "CCopasiContainer"
%typemap(cstype) CCopasiContainer* CCopasiObject::getObjectParent "CCopasiContainer"
%typemap(csout) CCopasiContainer* CCopasiObject::getObjectParent 
{
  return $imcall;
}
%typemap(out) CCopasiContainer* CCopasiObject::getObjectParent
{
    $result = DownCast_CCopasiContainer(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}


%typemap(ctype) CCopasiParameter* CCopasiParameterGroup::getParameter "jobject"
%typemap(imtype) CCopasiParameter* CCopasiParameterGroup::getParameter "CCopasiParameter"
%typemap(cstype) CCopasiParameter* CCopasiParameterGroup::getParameter "CCopasiParameter"
%typemap(csout) CCopasiParameter* CCopasiParameterGroup::getParameter 
{
  return $imcall;
}
%typemap(out) CCopasiParameter* CCopasiParameterGroup::getParameter
{
    $result = DownCast_CCopasiParameter(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}

%typemap(ctype) CCopasiParameterGroup* CCopasiParameterGroup::getGroup "jobject"
%typemap(imtype) CCopasiParameterGroup* CCopasiParameterGroup::getGroup "CCopasiParameterGroup"
%typemap(cstype) CCopasiParameterGroup* CCopasiParameterGroup::getGroup "CCopasiParameterGroup"
%typemap(csout) CCopasiParameterGroup* CCopasiParameterGroup::getGroup 
{
  return $imcall;
}
%typemap(out) CCopasiParameterGroup* CCopasiParameterGroup::getGroup
{
    $result = DownCast_CCopasiParameterGroup(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}


%typemap(ctype) CCopasiProblem* CCopasiTask::getProblem "jobject"
%typemap(imtype) CCopasiProblem* CCopasiTask::getProblem "CCopasiProblem"
%typemap(cstype) CCopasiProblem* CCopasiTask::getProblem "CCopasiProblem"
%typemap(csout) CCopasiProblem* CCopasiTask::getProblem 
{
  return $imcall;
}
%typemap(out) CCopasiProblem* CCopasiTask::getProblem
{
    $result = DownCast_CCopasiProblem(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}


%typemap(ctype) CCopasiMethod* CCopasiTask::getMethod "jobject"
%typemap(imtype) CCopasiMethod* CCopasiTask::getMethod "CCopasiMethod"
%typemap(cstype) CCopasiMethod* CCopasiTask::getMethod "CCopasiMethod"
%typemap(csout) CCopasiMethod* CCopasiTask::getMethod 
{
  return $imcall;
}
%typemap(out) CCopasiMethod* CCopasiTask::getMethod
{
    $result = DownCast_CCopasiMethod(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}


%typemap(ctype) CEvaluationTree* CFunctionDB::findFunction "jobject"
%typemap(imtype) CEvaluationTree* CFunctionDB::findFunction "CEvaluationTree"
%typemap(cstype) CEvaluationTree* CFunctionDB::findFunction "CEvaluationTree"
%typemap(csout) CEvaluationTree* CFunctionDB::findFunction 
{
  return $imcall;
}
%typemap(out) CEvaluationTree* CFunctionDB::findFunction
{
    $result = DownCast_CEvaluationTree(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}


%typemap(ctype) CEvaluationTree* CFunctionDB::findLoadFunction "jobject"
%typemap(imtype) CEvaluationTree* CFunctionDB::findLoadFunction "CEvaluationTree"
%typemap(cstype) CEvaluationTree* CFunctionDB::findLoadFunction "CEvaluationTree"
%typemap(csout) CEvaluationTree* CFunctionDB::findLoadFunction 
{
  return $imcall;
}
%typemap(out) CEvaluationTree* CFunctionDB::findLoadFunction
{
    $result = DownCast_CEvaluationTree(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}


%typemap(ctype) CEvaluationTree* CFunctionDB::createFunction "jobject"
%typemap(imtype) CEvaluationTree* CFunctionDB::createFunction "CEvaluationTree"
%typemap(cstype) CEvaluationTree* CFunctionDB::createFunction "CEvaluationTree"
%typemap(csout) CEvaluationTree* CFunctionDB::createFunction 
{
  return $imcall;
}
%typemap(out) CEvaluationTree* CFunctionDB::createFunction
{
    $result = DownCast_CEvaluationTree(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}

*/

/*  
%typemap(ctype) CModelEntity* "jobject"
%typemap(imtype) CModelEntity* "CModelEntity"
%typemap(cstype) CModelEntity* "CModelEntity"
%typemap(csout) CModelEntity* 
{
    return $imcall;
}

%typemap(out) CModelEntity* 
{
    $result = DownCast_CModelEntity(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}


%typemap(ctype) CEvaluationTree* "jobject"
%typemap(imtype) CEvaluationTree* "CEvaluationTree"
%typemap(cstype) CEvaluationTree* "CEvaluationTree"
%typemap(csout) CEvaluationTree* 
{
    return $imcall;
}

%typemap(out) CEvaluationTree* 
{
    $result = DownCast_CEvaluationTree(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}

%typemap(ctype) CCopasiTask* "jobject"
%typemap(imtype) CCopasiTask* "CCopasiTask"
%typemap(cstype) CCopasiTask* "CCopasiTask"
%typemap(csout) CCopasiTask* 
{
    return $imcall;
}

%typemap(out) CCopasiTask* 
{
    $result=DownCast_CCopasiTask(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}

%typemap(ctype) CCopasiMethod* "jobject"
%typemap(imtype) CCopasiMethod* "CCopasiMethod"
%typemap(cstype) CCopasiMethod* "CCopasiMethod"
%typemap(csout) CCopasiMethod* 
{
    return $imcall;
}

%typemap(out) CCopasiMethod* 
{
    $result = DownCast_CCopasiMethod(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}

%typemap(ctype) CCopasiProblem* "jobject"
%typemap(imtype) CCopasiProblem* "CCopasiProblem"
%typemap(cstype) CCopasiProblem* "CCopasiProblem"
%typemap(csout) CCopasiProblem* 
{
    return $imcall;
}

%typemap(out) CCopasiProblem* 
{
    $result = DownCast_CCopasiProblem(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}



%typemap(ctype) CCopasiParameterGroup* "jobject"
%typemap(imtype) CCopasiParameterGroup* "CCopasiParameterGroup"
%typemap(cstype) CCopasiParameterGroup* "CCopasiParameterGroup"
%typemap(csout) CCopasiParameterGroup* 
{
    return $imcall;
}

%typemap(out) CCopasiParameterGroup* 
{
    $result = DownCast_CCopasiParameterGroup(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}


%typemap(ctype) CCopasiParameter* "jobject"
%typemap(imtype) CCopasiParameter* "CCopasiParameter"
%typemap(cstype) CCopasiParameter* "CCopasiParameter"
%typemap(csout) CCopasiParameter* 
{
    return $imcall;
}

%typemap(out) CCopasiParameter* 
{
    $result = DownCast_CCopasiParameter(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}


%typemap(ctype) CCopasiContainer* "jobject"
%typemap(imtype) CCopasiContainer* "CCopasiContainer"
%typemap(cstype) CCopasiContainer* "CCopasiContainer"
%typemap(csout) CCopasiContainer* 
{
    return $imcall;
}

%typemap(out) CCopasiContainer* 
{
    $result = DownCast_CCopasiContainer(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}

%typemap(ctype) CCopasiObject* "jobject"
%typemap(imtype) CCopasiObject* "CCopasiObject"
%typemap(cstype) CCopasiObject* "CCopasiObject"
%typemap(csout) CCopasiObject* 
{
    return $imcall;
}

%typemap(out) CCopasiObject* 
{
    $result = DownCast_CCopasiObject(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
    }
}
*/



// some general ignore statements that already get rid of most warnings
%ignore *::operator =;
%ignore *::operator [];
%ignore *::operator ();
%ignore *::begin() const;
%ignore *::end() const;

%include "../swig/copasi.i"


