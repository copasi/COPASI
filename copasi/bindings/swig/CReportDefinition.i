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

#include "report/CReportDefinition.h"

%}

%ignore CReportDefinition::getBodyAddr() const;
%ignore CReportDefinition::getHeaderAddr() const;
%ignore CReportDefinition::getFooterAddr() const;
%ignore CReportDefinition::getTableAddr() const;

%include "report/CReportDefinition.h"



