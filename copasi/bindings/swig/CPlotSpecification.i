// Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 



%{

#include "plot/CPlotSpecification.h"

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

	CPlotItem* getItem(int index) const
	{
	try
	{
		return $self->getItems()[index];
	}
	   catch (...)
	   {
		return NULL;
	   }
	}

}

%include "plot/CPlotSpecification.h"

