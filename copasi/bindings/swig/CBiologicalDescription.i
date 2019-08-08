// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 




%{

#include "copasi/MIRIAM/CConstants.h"  
#include "copasi/MIRIAM/CBiologicalDescription.h"  
  
%}

%nodefaultctor CBiologicalDescription;

%ignore CMIRIAMResourceObject::CMIRIAMResourceObject(CRDFNode * pNode);
%ignore CMIRIAMResourceObject::setNode;
%ignore CMIRIAMResourceObject::getNode;

%include "copasi/MIRIAM/CBiologicalDescription.h"
%include "copasi/MIRIAM/CConstants.h"



