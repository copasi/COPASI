// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CModelValue.i,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/07/16 18:56:27 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "model/CModelValue.h"

%}

%nodefaultctor CModelEntity;
%nodefaultdtor CModelEntity;

%ignore CModelEntity::XMLStatus;
%ignore CModelEntity::StatusName;
%ignore CModelEntity::getValuePointer;
%ignore CModelEntity::getDeletedObjects;

// remove some const methods to get rid of warnings
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

#if (defined SWIGJAVA || defined SWIGCSHARP)
%extend CModelEntity
{
  void setInitialExpressionPtr(DisownedExpression* pDisownedExpression)
  {
     $self->CModelEntity::setInitialExpressionPtr(pDisownedExpression);
  }

  void setExpressionPtr(DisownedExpression* pDisownedExpression)
  {
     $self->CModelEntity::setExpressionPtr(pDisownedExpression);
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

}
#endif // SWIGJAVA || CSHARP


