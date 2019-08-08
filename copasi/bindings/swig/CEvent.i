// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 






%{

#include "copasi/model/CEvent.h"
#include <assert.h>
%}

%ignore CEventAssignment::getExpressionPtr() const;
%ignore CEvent::getTriggerExpressionPtr() const;
%ignore CEvent::getDelayExpressionPtr() const;
%ignore CEvent::getAssignments() const;
%ignore CEvent::getPriorityExpressionPtr() const;
%ignore CEvent::appendDependentAssignments;

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

%include "copasi/model/CEvent.h"

%extend CEvent
{
  CEventAssignment* createAssignment(std::string targetCN = "")
  {
    CEventAssignment* pAssignment=new CEventAssignment(targetCN);

    if (!$self->getAssignments().add(pAssignment,true))
      {
        delete pAssignment;
        pAssignment = NULL;
      }
     return pAssignment;
  }

  // more convenience methods
  unsigned C_INT32 getNumAssignments() const
  {
       return (unsigned C_INT32)$self->getAssignments().size();
  }

  CEventAssignment* getAssignment(unsigned C_INT32 index)
  {
       return &$self->getAssignments()[index];
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

#endif // SWIGJAVA || CSHARP

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


  std::string getUnsupportedAnnotation(std::string name)
  {
  	return $self->getUnsupportedAnnotations()[name];
  }
  
  bool hasUnsupportedAnnotation(std::string name)
  {
  	const std::string& annot = $self->getUnsupportedAnnotations()[name];
  	return !(annot.empty());
  }
  
  int getNumUnsupportedAnnotations()
  {
  	return (int)$self->getUnsupportedAnnotations().size();
  }
  
  std::string getUnsupportedAnnotation(int index)
  {		
  	std::map< std::string, std::string > &anot = $self->getUnsupportedAnnotations();
  	if (index >= (int)anot.size()) 
  		return "";
  	std::map< std::string, std::string >::iterator iter = anot.begin();
  	for (int i = 0; i < index; ++i)
  		++iter;
  	return (*iter).second;
  }
  
  std::string getUnsupportedAnnotationName(int index)
  {		
  	std::map< std::string, std::string > &anot = $self->getUnsupportedAnnotations();
  	if (index >= (int)anot.size()) 
  		return "";
  	std::map< std::string, std::string >::iterator iter = anot.begin();
  	for (int i = 0; i < index; ++i)
  		++iter;
  	return (*iter).first;
  }
   
  bool addUnsupportedAnnotation(const std::string & name, const std::string & xml)
  {
	try
	{
		return $self->addUnsupportedAnnotation(name, xml);
	}
	catch(...)
	{
		return false;
	}
  }
  
  bool replaceUnsupportedAnnotation(const std::string & name, const std::string & xml)
  {
	try
	{	
		return $self->replaceUnsupportedAnnotation(name, xml);
	}
	catch(...)
	{
		return false;
	}
  }
  
  bool removeUnsupportedAnnotation(const std::string & name)
  {
  	return $self->removeUnsupportedAnnotation(name);
  }


}

#ifdef SWIGJAVA  || CSHARP
%extend CEventAssignment
{
  void setExpressionPtr(DisownedExpression* pDisownedExpression)
  {
     $self->CEventAssignment::setExpressionPtr(pDisownedExpression);
  }

}
#endif // SWIGJAVA  || CSHARP


