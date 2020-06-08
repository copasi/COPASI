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



%{

#include "copasi/plot/CPlotSpecification.h"

%}

%ignore CPlotSpecification::getItems() const;
%ignore CPlotSpecification::getChannels();

%extend CPlotSpecification
{
	CPlotDataChannelSpec getChannel(int index) const
	{
		return $self->getChannels()[index];
	}

	size_t getNumPlotItems() const
	{
		return $self->getItems().size();
	}

	const CPlotItem* getItem(int index) const
	{
	try
	{
		return &$self->getItems()[index];
	}
	   catch (...)
	   {
		return NULL;
	   }
	}

}

%include "plot/CPlotSpecification.h"

