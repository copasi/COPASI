// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/perl/perl.i,v $ 
//   $Revision: 1.1.2.4 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/09/14 13:04:53 $ 
// End CVS Header 

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

/**
 * Convert CFitItem objects into the most specific type possible.
 */
%typemap(out) CFitItem*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForCFitItem($1),
                                 $owner | %newpointer_flags);
  argvi++;
}

/**
 * Convert COptItem objects into the most specific type possible.
 */
%typemap(out) COptItem*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForCOptItem($1),
                                 $owner | %newpointer_flags);
  argvi++;
}

/**
 * Convert CExperimentSet objects into the most specific type possible.
%typemap(out) CExperimentSet*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForCExperimentSet($1),
                                 $owner | %newpointer_flags);
  argvi++;
}
 */

/**
 * Convert CCopasiAbstractArray objects into the most specific type possible.
 */
%typemap(out) CCopasiAbstractArray*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForCCopasiAbstractArray($1),
                                 $owner | %newpointer_flags);
  argvi++;
}

/**
 * Convert CEvaluationTree objects into the most specific type possible.
 */
%typemap(out) CEvaluationTree*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForCEvaluationTree($1),
                                 $owner | %newpointer_flags);
  argvi++;
}

/**
 * Convert COptTask objects into the most specific type possible.
 */
%typemap(out) COptTask*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForCOptTask($1),
                                 $owner | %newpointer_flags);
  argvi++;
}


/**
 * Convert Task objects into the most specific type possible.
 */
%typemap(out) CCopasiTask*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForTask($1),
                                 $owner | %newpointer_flags);
  argvi++;
}

/**
 * Convert COptProblem objects into the most specific type possible.
 */
%typemap(out) COptProblem*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForCOptProblem($1),
                                 $owner | %newpointer_flags);
  argvi++;
}

/**
 * Convert Problem objects into the most specific type possible.
 */
%typemap(out) CCopasiProblem*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForProblem($1),
                                 $owner | %newpointer_flags);
  argvi++;
}

/**
 * Convert COptMethod objects into the most specific type possible.
 */
%typemap(out) COptMethod*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForCOptMethod($1),
                                 $owner | %newpointer_flags);
  argvi++;
}


/**
 * Convert Method objects into the most specific type possible.
 */
%typemap(out) CCopasiMethod*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForMethod($1),
                                 $owner | %newpointer_flags);
  argvi++;
}

/**
 * Convert parametergroup objects into the most specific type possible.
 */
%typemap(out) CCopasiParameterGroup*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForCCopasiParameterGroup($1),
                                 $owner | %newpointer_flags);
  argvi++;
}


/**
 * Convert parameter objects into the most specific type possible.
 */
%typemap(out) CCopasiParameter*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForCCopasiParameter($1),
                                 $owner | %newpointer_flags);
  argvi++;
}

/**
 * Convert container objects into the most specific type possible.
 */
%typemap(out) CCopasiContainer*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForCCopasiContainer($1),
                                 $owner | %newpointer_flags);
  argvi++;
}

/**
 * Convert object objects into the most specific type possible.
 */
%typemap(out) CCopasiObject*
{
  ST(argvi) = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigTypeForCCopasiObject($1),
                                 $owner | %newpointer_flags);
  argvi++;
}



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


