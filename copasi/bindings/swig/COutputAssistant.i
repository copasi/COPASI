// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/COutputAssistant.i,v $ 
//   $Revision: 1.4 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2007/06/23 12:45:47 $ 
// End CVS Header 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "report/COutputAssistant.h"

%}

%ignore COutputAssistant::getDefaultPlotIndex(const CCopasiProblem* problem);
%ignore COutputAssistant::Map;
%ignore COutputAssistant::mMap;
%ignore COutputAssistant::createPlot(const std::string& name,CCopasiObject* x, const std::vector<const CCopasiObject*>& y,const CCopasiTask::Type& taskType);
%ignore COutputAssistant::createTable(const std::string& name, const std::vector<const CCopasiObject*>& d,const std::string& comment, const CCopasiTask::Type& taskType);
%ignore COutputAssistant::emptyString;
%ignore COutputAssistant::emptyItem;


%include "report/COutputAssistant.h"



