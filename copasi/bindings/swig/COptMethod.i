// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "copasi/optimization/COptLogItem.h"
#include "copasi/optimization/COptLog.h"
#include "copasi/optimization/COptMethod.h"
#include "copasi/optimization/COptPopulationMethod.h"

%}

%newobject COptMethod::createMethod(CTaskEnum::Method& subType);

%ignore COptLogItem::getTimestamp;
%ignore COptLogItem::MsgIDSubtext;
%ignore COptLogItem::MsgIDHeader;

%include "optimization/COptLogItem.h"
%include "optimization/COptLog.h"
%include "optimization/COptMethod.h"
%include "optimization/COptPopulationMethod.h"


