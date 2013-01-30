// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 


%{

#include "parameterFitting/CExperimentSet.h"

%}

#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CExperimentSet::getExperiment(const unsigned long&) const;
%ignore CExperimentSet::getExperiment(const std::string&) const;
%ignore CExperimentSet::getExperiment(size_t const &) const;
#endif // SWIGJAVA || CSHARP


%include "parameterFitting/CExperimentSet.h"



