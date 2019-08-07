// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 



%ignore CModelParameter::TypeNames;

%{

#include "copasi/model/CModelParameter.h"

%}

%extend CModelParameter
{

   CModelParameterGroup *asGroup() 
   {
     return dynamic_cast<CModelParameterGroup *>($self);
   }

   CModelParameterSpecies *asSpecies() 
   {
     return dynamic_cast<CModelParameterSpecies *>($self);
   }

   CModelParameterCompartment *asCompartment() 
   {
     return dynamic_cast<CModelParameterCompartment *>($self);
   }

   CModelParameterSet *asSet() 
   {
     return dynamic_cast<CModelParameterSet *>($self);
   }

   CModelParameterReactionParameter *asReactionParameter() 
   {
     return dynamic_cast<CModelParameterReactionParameter *>($self);
   }


   /**
   * Set the value of the parameter based on the current framework
   * @param const double & value
   * @param const Framework & framework
   */
  void setValue(double value, C_INT32 framework)
  {
	$self->setValue(value, (CCore::Framework)framework);
  }
  
  void setValue(double value)
  {
	$self->setValue(value, (CCore::Framework)0);
  }

  /**
   * Retrieve the value of the parameter based on the current framework
   * @param const Framework & framework
   * @return const double & value
   */
  double getValue(C_INT32 framework) const
  {
	return $self->getValue((CCore::Framework)framework);
  }
  
  double getValue() const
  {
	return $self->getValue((CCore::Framework)0);
  }

  bool hasValue(C_INT32 framework) const
  {
	volatile double value = $self->getValue((CCore::Framework)framework);
	return !(value != value);
  }
  
  bool hasValue() const
  {
	volatile double value = $self->getValue((CCore::Framework)0);
	return !(value != value);
  }

  
}

%include "model/CModelParameter.h"



