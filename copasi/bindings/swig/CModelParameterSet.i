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





%ignore CModelParameterSet::setModel;
%ignore CModelParameterSet::refreshFromModel(bool const &);
%warnfilter(813) CModelParameterSet;

#if SWIGCSHARP

%csmethodmodifiers  CModelParameterSet::add  "public new"
%csmethodmodifiers  CModelParameterSet::compile  "public new"
%csmethodmodifiers  CModelParameterSet::getName  "public new"
%csmethodmodifiers  CModelParameterSet::getIndex  "public new"
%csmethodmodifiers  CModelParameterSet::toSet  "public new"
%csmethodmodifiers  CModelParameterSet::refreshFromModel  "public new"
%csmethodmodifiers  CModelParameterSet::updateIndex  "public new"
%csmethodmodifiers  CModelParameterSet::updateModel  "public new"

#endif

%{

#include "copasi/model/CModelParameterSet.h"
#include "copasi/model/CModelParameter.h"

%}

%extend CModelParameterSet
{
   // of course CModelParameterSet uses multiple inheritance 
   // which is not supported by swig ... 
   
  /**
   * Add parameter of the given type to the group and return a pointer to it
   * @param const CModelParameter::Type & type
   * @return CModelParameter * pParameter
   */
  CModelParameter * add(C_INT32 type)
  {
	CModelParameter::Type actual = (CModelParameter::Type)type;
	return $self->CModelParameterGroup::add(actual);
  }

  /**
   * Add the given parameter to the group.
   * Note, the parent of the parameter is not updated
   * @param CModelParameter * pModelParameter
   */
  void add(CModelParameter * pModelParameter)
  {
	$self->CModelParameterGroup::add(pModelParameter);
  }

  /**
   * Remove the given parameter from the group.
   * Note, the parameter is not deleted.
   * @param CModelParameter * pModelParameter
   */
  void remove(CModelParameter * pModelParameter)
  {
	$self->CModelParameterGroup::remove(pModelParameter);
  }

  /**
   * Remove the indexed parameter from the group and delete it
   * @param const size_t & index
   */
  void remove(C_INT32 index)
  {
	$self->CModelParameterGroup::remove((size_t)index);
  }

  /**
   * Retrieve the size of the group
   * @return size_t size
   */
  C_INT32 size() const
  {
	return (C_INT32)$self->CModelParameterGroup::size();
  }
  
    /**
   * Compile the parameter
   */
  void compile()
  {
    $self->CModelParameterGroup::compile();
  }

    /**
   * Clear the contained parameters and delete them.
   */
  void clear()
  {
	$self->CModelParameterGroup::clear();
  }
  
  /**
   * Update the corresponding model object with the current parameter settings
  bool updateModel()
  {
	$self->CModelParameterGroup::updateModel();
  }
 */
  
  /**
   * Refresh the parameter from the corresponding model object
   * @param const bool & modifyExistence
   */
  bool refreshFromModel(bool modifyExistence)
  {
	return $self->CModelParameterGroup::refreshFromModel(modifyExistence);
  }

  /**
   * Retrieve a pointer to the parameter with the given CN
   * @param const std::string & cn
   * @return CModelParameter * pModelParameter
   */
  CModelParameter * getModelParameter(const std::string & cn) const
  {
	return $self->CModelParameterGroup::getModelParameter(cn);
  }
   
    /**
   * Retrieve a pointer to the parameter with the given name and type
   * @param const std::string & name
   * @param const CModelParameter::Type & type
   * @return CModelParameter * pModelParameter
   */
  CModelParameter * getModelParameter(const std::string & name,
                                      C_INT32 type) const
  {
	return $self->CModelParameterGroup::getModelParameter(name, (CModelParameter::Type)type);
  }
  
  const CModelParameter * getModelParameter(C_INT32 index) const
  {
	return $self->CModelParameterGroup::getChild((size_t)index);
  }
   
}

%include "model/CModelParameter.h"
%include "model/CModelParameterSet.h"



