// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 






%ignore CAnnotation::operator==;
%ignore CAnnotation::getUnsupportedAnnotations() const;
%ignore CAnnotation::getUnsupportedAnnotations();
%ignore CAnnotation::castObject(const CDataObject * pObject);

%{

#include "copasi/model/CAnnotation.h"  
  
%}


%include "copasi/model/CAnnotation.h"

%extend CAnnotation
{
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
}; 

