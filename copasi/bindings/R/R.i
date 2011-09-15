// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/R/R.i,v $ 
//   $Revision: 1.1.2.4 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/09/15 20:43:22 $ 
// End CVS Header 

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 



// the following code also did not solve the size_t pointer problem
//%inline %{
//typedef unsigned long size_t;
//%}


// the following typemap replaces the default typemap for enum references
// because I think the default typemap has a bug
%typemap(scoercein) const enum SWIGTYPE &
  %{
      $input = enumToInteger($input, "$*1_mangle"); 
  %}

// this seems to fix the problem that size_t references are
// used as pointers
%typemap("rtype") size_t, size_t*, size_t& "numeric";


/**
 * Convert CFitItem objects into the most specific type possible.
%typemap(out) CFitItem*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCFitItem($1), 0);
}
 */

/**
 * Convert COptItem objects into the most specific type possible.
%typemap(out) COptItem*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCOptItem($1), 0);
}
 */

/**
 * Convert CExperimentSet objects into the most specific type possible.
%typemap(out) CExperimentSet*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCExperimentSet($1), 0);
}
 */

/**
 * Convert CCopasiAbstractArray objects into the most specific type possible.
%typemap(out) CCopasiAbstractArray*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCCopasiAbstractArray($1), 0);
}
 */

/**
 * Convert CEvaluationTree objects into the most specific type possible.
%typemap(out) CEvaluationTree*
{
  // This code is more or less identical to the code that is generated without the typemap.
  // The only difference is that I replaced the fixed SWIG_type for CEvaluationTree which is
  // passed as the second argument with the determined type returned by GetDowncastSwigTypeForCEvaluationTree.
  // Unfortunatelly, although the GetDowncast returns the correct type, it doesn't work, the R
  // side still sees a CEvaluationTree object and not a CFunction when calling CFunctionDB_findFunction.  
  $result = SWIG_R_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForCEvaluationTree($1), R_SWIG_EXTERNAL |  0 );
}
 */

/**
 * Convert COptTask objects into the most specific type possible.
%typemap(out) COptTask*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCOptTask($1), 0);
}
 */


/**
 * Convert Task objects into the most specific type possible.
%typemap(out) CCopasiTask*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForTask($1), 0);
}
 */

/**
 * Convert COptProblem objects into the most specific type possible.
%typemap(out) COptProblem*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCOptProblem($1), 0);
}
 */

/**
 * Convert Problem objects into the most specific type possible.
%typemap(out) CCopasiProblem*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForProblem($1), 0);
}
 */

/**
 * Convert COptMethod objects into the most specific type possible.
%typemap(out) COptMethod*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCOptMethod($1), 0);
}
 */


/**
 * Convert Method objects into the most specific type possible.
%typemap(out) CCopasiMethod*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForMethod($1), 0);
}
 */

/**
 * Convert parametergroup objects into the most specific type possible.
%typemap(out) CCopasiParameterGroup*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCCopasiParameterGroup($1), 0);
}
 */


/**
 * Convert parameter objects into the most specific type possible.
%typemap(out) CCopasiParameter*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCCopasiParameter($1), 0);
}
 */

/**
 * Convert container objects into the most specific type possible.
%typemap(out) CCopasiContainer*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCCopasiContainer($1), 0);
}
 */

/**
 * Convert object objects into the most specific type possible.
%typemap(out) CCopasiObject*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCCopasiObject($1), 0);
}
 */


/*
%pythoncode
%{
import types
%}
*/

%include "../swig/copasi.i"

%{
#include "report/CCopasiRootContainer.h"
#include "commandline/COptions.h"
%}

%init %{

// Taken from CopasiSE.cpp

// Create the root container
CCopasiRootContainer::init(0,NULL,false);

%}



