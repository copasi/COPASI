// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CScanTask.i,v $ 
//   $Revision: 1.3 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/01/16 09:03:14 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "scan/CScanTask.h"

%}

%ignore CScanTask::process(const bool& useInitialValues);
%ignore CScanTask::initialize(const OutputFlag & of, std::ostream * pOstream);


%include "scan/CScanTask.h"



