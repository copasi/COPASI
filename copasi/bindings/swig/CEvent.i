// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CEvent.i,v $ 
//   $Revision: 1.1.2.4 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/04 19:58:32 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "model/CEvent.h"  
#include <assert.h>  
%}

%ignore CEventAssignment::getExpressionPtr() const; 
%ignore CEvent::getTriggerExpressionPtr() const; 
%ignore CEvent::getDelayExpressionPtr() const; 
%ignore CEvent::getAssignments() const; 

// cleanup does not seem to be implemented
%ignore CEvent::cleanup(); 


// some special code for java
#ifdef SWIGJAVA
// we ignore some of the methods and add them back as an extension 
// with the hopefully correct typemaps
%ignore CEventAssignment::setExpressionPtr(CExpression*); 
%ignore CEvent::setDelayExpressionPtr(CExpression*); 
%ignore CEvent::setTriggerExpressionPtr(CExpression*); 

%inline
%{
// some typedef so that we can have specific typemaps
typedef CExpression DisownedExpression;
%}


%typemap(javain) DisownedExpression *pDisownedExpression "getCPtrAndAddReference($javainput)"

%typemap(javacode) CEvent %{
  // Ensure that the GC doesn't collect any element set from Java
  // as the underlying C++ class stores a shallow copy
  private CExpression expressionReference;
  private long getCPtrAndAddReference(CExpression expression) {
    expressionReference = expression;
    return CExpression.getCPtr(expression);
  }
%}

%typemap(javacode) CEventAssignment %{
  // Ensure that the GC doesn't collect any element set from Java
  // as the underlying C++ class stores a shallow copy
  private CExpression expressionReference;
  private long getCPtrAndAddReference(CExpression expression) {
    expressionReference = expression;
    return CExpression.getCPtr(expression);
  }
%}
#endif // SWIGJAVA

#ifdef SWIGPYTHON
%feature("pythonappend") CEventAssignment::setExpressionPtr(CExpression*) %{
   if(len(args) > 0 and args[0] != None and isinstance(args[0], COPASI.CExpression)):
     args[0].__disown__()
%}

%feature("pythonappend") CEvent::setTriggerExpressionPtr(CExpression*) %{
   if(len(args) > 0 and args[0] != None and isinstance(args[0], COPASI.CExpression)):
     args[0].__disown__()
%}

%feature("pythonappend") CEvent::setDelayExpressionPtr(CExpression*) %{
   if(len(args) > 0 and args[0] != None and isinstance(args[0], COPASI.CExpression)):
     args[0].__disown__()
%}
#endif // SWIGPYTHON

%include "model/CEvent.h"

%extend CEvent
{
  CEventAssignment* createAssignment()
  {
    CEventAssignment* pAssignment=new CEventAssignment;
    $self->getAssignments().add(pAssignment,true);
    return pAssignment;
  }

#ifdef SWIGJAVA
  void setTriggerExpressionPtr(DisownedExpression* pDisownedExpression)
  {
     $self->CEvent::setTriggerExpressionPtr(pDisownedExpression);
  }

  void setDelayExpressionPtr(DisownedExpression* pDisownedExpression)
  {
     $self->CEvent::setDelayExpressionPtr(pDisownedExpression);
  }
#endif // SWIGJAVA
}

#ifdef SWIGJAVA
%extend CEventAssignment
{
  void setExpressionPtr(DisownedExpression* pDisownedExpression)
  {
     $self->CEventAssignment::setExpressionPtr(pDisownedExpression);
  }

}
#endif // SWIGJAVA


