// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 



%{

#include "model/CObjectLists.h"

%}

%ignore CObjectLists::ListTypeName;
%ignore CObjectLists::getListOfObjects;
%ignore CObjectLists::getListOfConstObjects;
%ignore CObjectLists::getEventTargets;

%include "model/CObjectLists.h"

