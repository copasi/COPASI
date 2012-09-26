// Begin git Header 
//   Commit: 28d5663ff3fc99993d3b249dec626841cb5247ab 
//   Author: Frank T. Bergmann fbergman@caltech.edu 
//   Date: 2012-08-29 10:43:00 +0200 
// End git Header 


// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

%ignore CRDFTriplet::operator bool;
%ignore CRDFTriplet::operator <;

%{

#include "MIRIAM/CMIRIAMResource.h"
#include "MIRIAM/CRDFGraph.h"
#include "MIRIAM/CRDFNode.h"
#include "MIRIAM/CRDFObject.h"
#include "MIRIAM/CRDFPredicate.h"
#include "MIRIAM/CRDFSubject.h"
#include "MIRIAM/CRDFTriplet.h"
#include "MIRIAM/CModelMIRIAMInfo.h"

%}

%include "MIRIAM/CMIRIAMResource.h"
%include "MIRIAM/CRDFGraph.h"
#include "MIRIAM/CRDFNode.h"
#include "MIRIAM/CRDFObject.h"
#include "MIRIAM/CRDFPredicate.h"
#include "MIRIAM/CRDFSubject.h"
%include "MIRIAM/CRDFTriplet.h"
%include "MIRIAM/CModelMIRIAMInfo.h"



