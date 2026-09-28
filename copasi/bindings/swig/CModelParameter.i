// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the 
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



%{

#include "copasi/model/CModelParameter.h"

%}

%ignore CModelParameter::TypeNames;
%ignore CModelParameter::CompareResultNames;

%extend CModelParameter
{
  %{
    using CModelParameter_CompareResultNames = decltype(CModelParameter::CompareResultNames);
    using CModelParameter_CompareResultNames_Map = CBidirectionalMap< CModelParameter_CompareResultNames::EnumType, CModelParameter_CompareResultNames::AnnotationType, CModelParameter_CompareResultNames::Size >;
    using CModelParameter_CompareResultNames_AnnotationType = CEnumAnnotation< CModelParameter_CompareResultNames_Map >;
  %}

  // 2. Define the getter function for SWIG using a clean macro string definition
  // We use RealAnnotationType const& so SWIG treats it as a non-owning read-only memory reference
  const CModelParameter_CompareResultNames_AnnotationType& getCompareResultNames() {
    return CModelParameter::CompareResultNames;
  }

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

  void setCN(const std::string & cn)
  {
    $self->setCN(CRegisteredCommonName(cn));
  }

  void setCN(const CCommonName & cn)
  {
    $self->setCN(CRegisteredCommonName(cn));
  }
  
}

%extend CModelParameterSpecies
{

  void setCN(const std::string & cn)
  {
    $self->setCN(CRegisteredCommonName(cn));
  }

  void setCN(const CCommonName & cn)
  {
    $self->setCN(CRegisteredCommonName(cn));
  }
}

%include "model/CModelParameter.h"



