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

#include "copasi/model/CObjectLists.h"

%}

%ignore CObjectLists::ListTypeName;
%ignore CObjectLists::getListOfObjects;
%ignore CObjectLists::getListOfConstObjects;
%ignore CObjectLists::getEventTargets;

%include "model/CObjectLists.h"

