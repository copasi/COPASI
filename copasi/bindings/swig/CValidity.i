// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 



%{
#include "copasi/utilities/CValidity.h"
%}

%ignore CIssue::operator bool;

%ignore CIssue::Success;
%ignore CIssue::Information;
%ignore CIssue::Warning;
%ignore CIssue::Error;

%ignore CIssue::eKind;
%ignore CIssue::eSeverity;

%include "copasi/utilities/CValidity.h"



