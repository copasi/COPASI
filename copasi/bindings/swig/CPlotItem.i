// Copyright (C) 2012 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 




%{

#include "plot/CPlotItem.h"

%}

%ignore CPlotItem::getChannels() const;
%ignore CPlotItem::XMLRecordingActivity;
%ignore CPlotItem::getRecordingActivityName;


%include "plot/CPlotItem.h"

