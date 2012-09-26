// Begin git Header 
//   Commit: 28d5663ff3fc99993d3b249dec626841cb5247ab 
//   Author: Frank T. Bergmann fbergman@caltech.edu 
//   Date: 2012-08-29 10:43:00 +0200 
// End git Header 


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
%ignore CEvent::getPriorityExpressionPtr() const;

// cleanup does not seem to be implemented
%ignore CEvent::cleanup();


// some special code for java
#if (defined SWIGJAVA || defined SWIGCSHARP)
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

#endif // SWIGJAVA || CSHARP

#if SWIGJAVA

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

#endif

#ifdef SWIGCSHARP

%typemap(csin) DisownedExpression *pDisownedExpression "getCPtrAndAddReference($csinput)"

%typemap(cscode) CEvent %{
  // Ensure that the GC doesn't collect any element set from Java
  // as the underlying C++ class stores a shallow copy
  private CExpression expressionReference;
  private System.Runtime.InteropServices.HandleRef getCPtrAndAddReference(CExpression expression) {
    expressionReference = expression;
    return CExpression.getCPtr(expression);
  }
%}

%typemap(cscode) CEventAssignment %{
  // Ensure that the GC doesn't collect any element set from Java
  // as the underlying C++ class stores a shallow copy
  private CExpression expressionReference;
  private System.Runtime.InteropServices.HandleRef getCPtrAndAddReference(CExpression expression) {
    expressionReference = expression;
    return CExpression.getCPtr(expression);
  }
%}

#endif

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

// suppress warnings on multiple inheritance
%warnfilter(813) CEvent;

%include "model/CEvent.h"

%extend CEvent
{
  CEventAssignment* createAssignment()
  {
    CEventAssignment* pAssignment=new CEventAssignment;
    $self->getAssignments().add(pAssignment,true);
    return pAssignment;
  }

  // more convenience methods
  unsigned C_INT32 getNumAssignments() const
  {
       return $self->getAssignments().size();
  }

  CEventAssignment* getAssignment(unsigned C_INT32 index)
  {
       return $self->getAssignments()[index];
  }

#if (defined SWIGJAVA || defined SWIGCSHARP)
  void setTriggerExpressionPtr(DisownedExpression* pDisownedExpression)
  {
     $self->CEvent::setTriggerExpressionPtr(pDisownedExpression);
  }

  void setDelayExpressionPtr(DisownedExpression* pDisownedExpression)
  {
     $self->CEvent::setDelayExpressionPtr(pDisownedExpression);
  }

  // the CAnnotation functionality has to be added manually because
  // Java does not know about multiple inheritance
  void setNotes(const std::string& notes)
  {
    self->setNotes(notes);
  }

  const std::string& getNotes() const
  {
    return self->getNotes();
  }

  const std::string& getMiriamAnnotation() const
  {
    return self->getMiriamAnnotation();
  }

  void setMiriamAnnotation(const std::string& miriamAnnotation,
                           const std::string& newId,
                           const std::string& oldId)
  {
	self->setMiriamAnnotation(miriamAnnotation,newId,oldId);
  }
#endif // SWIGJAVA || CSHARP
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


