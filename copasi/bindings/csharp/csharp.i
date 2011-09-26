// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/csharp/csharp.i,v $ 
//   $Revision: 1.1.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/09/26 08:56:56 $ 
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

%typemap(ctype) CCopasiAbstractArray* CArrayAnnotation::array "jobject"
%typemap(imtype) CCopasiAbstractArray* CArrayAnnotation::array "CCopasiAbstractArray"
%typemap(cstype) CCopasiAbstractArray* CArrayAnnotation::array "CCopasiAbstractArray"
%typemap(csout) CCopasiAbstractArray* CArrayAnnotation::array 
{
  return $jnicall;
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
  return $jnicall;
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
  return $jnicall;
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
  return $jnicall;
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
  return $jnicall;
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
  return $jnicall;
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
  return $jnicall;
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
  return $jnicall;
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
  return $jnicall;
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
  return $jnicall;
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
  return $jnicall;
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
  return $jnicall;
}
%typemap(out) CEvaluationTree* CFunctionDB::createFunction
{
    $result = DownCast_CEvaluationTree(jenv,$1);
    if($1 != NULL && !$result)
    {
        std::cout << "Failed to create new mono object" << std::endl;
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
%typemap(ctype) CModelEntity* "jobject"
%typemap(imtype) CModelEntity* "CModelEntity"
%typemap(cstype) CModelEntity* "CModelEntity"
%typemap(csout) CModelEntity* 
{
    return $jnicall;
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
    return $jnicall;
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
    return $jnicall;
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
    return $jnicall;
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
    return $jnicall;
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
    return $jnicall;
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
    return $jnicall;
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
    return $jnicall;
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
    return $jnicall;
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



/**
 * C# does not handle exceptions the same way as java. The code below will have to be adjusted
 * once the build system is finished.
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
*/


%include "../swig/copasi.i"


