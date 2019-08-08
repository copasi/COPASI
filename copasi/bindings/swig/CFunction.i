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

#include "copasi/function/CFunction.h"

%}

%ignore operator<<;
%ignore CFunction::operator==;
%ignore CFunction::load;
%ignore CFunction::splitFunction;
%ignore CFunction::writeMathML;

// suppress warnings on multiple inheritance
%warnfilter(813) CFunction;

#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CFunction::getVariables() const;

#endif // SWIGJAVA || CSHARP

%include "copasi/function/CFunction.h" 

%extend CFunction
{

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

