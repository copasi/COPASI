// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "report/COutputAssistant.h"

%}

%ignore COutputAssistant::getDefaultPlotIndex(const CCopasiProblem* problem);
%ignore COutputAssistant::Map;
%ignore COutputAssistant::mMap;
%ignore COutputAssistant::createPlot(const std::string& name,CDataObject* x, const std::vector<const CDataObject*>& y,const CCopasiTask::Type& taskType);
%ignore COutputAssistant::createTable(const std::string& name, const std::vector<const CDataObject*>& d,const std::string& comment, const CCopasiTask::Type& taskType);
%ignore COutputAssistant::emptyString;
%ignore COutputAssistant::emptyItem;


%include "report/COutputAssistant.h"



