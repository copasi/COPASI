// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CModelValue.i,v $ 
//   $Revision: 1.9.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/26 16:15:01 $ 
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
%ignore CModelEntity::getValuePointer;

// remove some const methods to get rid of warnings
%ignore CModelEntity::getExpressionPtr() const;
%ignore CModelEntity::getInitialExpressionPtr() const;


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


%include "model/CModelValue.h"

#ifdef SWIGJAVA
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

}
#endif // SWIGJAVA


