// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 




%{

#include "MIRIAM/CConstants.h"  
#include "MIRIAM/CBiologicalDescription.h"  
  
%}

%nodefaultctor CBiologicalDescription;

%ignore CMIRIAMResourceObject::CMIRIAMResourceObject(CRDFNode * pNode);
%ignore CMIRIAMResourceObject::setNode;
%ignore CMIRIAMResourceObject::getNode;

%include "MIRIAM/CBiologicalDescription.h"
%include "MIRIAM/CConstants.h"



