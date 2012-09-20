// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CModelMIRIAMInfo.i,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/03 13:53:20 $
// End CVS Header

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



