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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 












%{

#include "copasi/model/CModelValue.h"

%}

%nodefaultctor CModelEntity;
%nodefaultdtor CModelEntity;

%ignore CModelEntity::XMLStatus;
%ignore CModelEntity::StatusName;
%ignore CModelEntity::getValuePointer;
%ignore CModelEntity::getDeletedObjects;

// remove some const methods to get rid of warnings
%ignore CModelEntity::getNoiseExpressionPtr() const;
%ignore CModelEntity::getExpressionPtr() const;
%ignore CModelEntity::getInitialExpressionPtr() const;

%ignore CModelEntity::setInitialValuePtr;
%ignore CModelEntity::setValuePtr;

// some special code for java
#ifdef SWIGJAVA
// we ignore some of the methods and add them back as an extension
// with the hopefully correct typemaps
%ignore CModelEntity::setExpressionPtr(CExpression*);
%ignore CModelEntity::setInitialExpressionPtr(CExpression*);

%inline
%{
// some typedef so that we can have specific typemaps
typedef CExpression DisownedExpression;
%}


%typemap(javain) DisownedExpression *pDisownedExpression "getCPtrAndAddReference($javainput)"

%typemap(javacode) CModelEntity %{
  // Ensure that the GC doesn't collect any element set from Java
  // as the underlying C++ class stores a shallow copy
  private CExpression expressionReference;
  private long getCPtrAndAddReference(CExpression expression) {
    expressionReference = expression;
    return CExpression.getCPtr(expression);
  }
%}

#endif // SWIGJAVA

#ifdef SWIGCSHARP
// we ignore some of the methods and add them back as an extension
// with the hopefully correct typemaps
%ignore CModelEntity::setExpressionPtr(CExpression*);
%ignore CModelEntity::setInitialExpressionPtr(CExpression*);

%inline
%{
// some typedef so that we can have specific typemaps
typedef CExpression DisownedExpression;
%}


%typemap(csin) DisownedExpression *pDisownedExpression "getCPtrAndAddReference($csinput)"

%typemap(cscode) CModelEntity %{
  // Ensure that the GC doesn't collect any element set from Java
  // as the underlying C++ class stores a shallow copy
  private CExpression expressionReference;
  private System.Runtime.InteropServices.HandleRef getCPtrAndAddReference(CExpression expression) {
    expressionReference = expression;
    return CExpression.getCPtr(expression);
  }
%}

#endif // SWIGCSHARP


#ifdef SWIGPYTHON

%feature("pythonappend") CModelEntity::setInitialExpressionPtr(CExpression*) %{
   if(len(args) > 0 and args[0] != None and isinstance(args[0], COPASI.CExpression)):
     args[0].__disown__()
%}

%feature("pythonappend") CModelEntity::setExpressionPtr(CExpression*) %{
   if(len(args) > 0 and args[0] != None and isinstance(args[0], COPASI.CExpression)):
     args[0].__disown__()
%}
#endif // SWIGPYTHON

// suppress warnings on multiple inheritance
%warnfilter(813) CModelEntity;

%include "model/CModelValue.h"

%extend CModelEntity
{
#if (defined SWIGJAVA || defined SWIGCSHARP)
  void setInitialExpressionPtr(DisownedExpression* pDisownedExpression)
  {
     $self->CModelEntity::setInitialExpressionPtr(pDisownedExpression);
  }

  void setExpressionPtr(DisownedExpression* pDisownedExpression)
  {
     $self->CModelEntity::setExpressionPtr(pDisownedExpression);
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


