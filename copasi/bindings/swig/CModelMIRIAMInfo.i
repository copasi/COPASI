// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
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



