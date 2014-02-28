// Copyright (C) 2012 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 



%ignore CModelParameter::TypeNames;

%{

#include "model/CModelParameter.h"

%}

%extend CModelParameter
{

  /**
   * Set the value of the parameter based on the current framework
   * @param const double & value
   * @param const Framework & framework
   */
  void setValue(double value, C_INT32 framework)
  {
	$self->setValue(value, (CModelParameter::Framework)framework);
  }
  
  void setValue(double value)
  {
	$self->setValue(value, (CModelParameter::Framework)0);
  }

  /**
   * Retrieve the value of the parameter based on the current framework
   * @param const Framework & framework
   * @return const double & value
   */
  double getValue(C_INT32 framework) const
  {
	return $self->getValue((CModelParameter::Framework)framework);
  }
  
  double getValue() const
  {
	return $self->getValue((CModelParameter::Framework)0);
  }

  bool hasValue(C_INT32 framework) const
  {
	volatile double value = $self->getValue((CModelParameter::Framework)framework);
	return !(value != value);
  }
  
  bool hasValue() const
  {
	volatile double value = $self->getValue((CModelParameter::Framework)0);
	return !(value != value);
  }

  
}

%include "model/CModelParameter.h"



