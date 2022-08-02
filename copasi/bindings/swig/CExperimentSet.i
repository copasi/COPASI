// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 


%{

#include "copasi/parameterFitting/CExperimentSet.h"

%}

// remove some const methods to get rid of warnings
%ignore CExperimentSet::getExperiment(const unsigned long&) const;
%ignore CExperimentSet::getExperiment(const std::string&) const;
%ignore CExperimentSet::getExperiment(size_t const &) const;


%include "copasi/parameterFitting/CExperimentSet.h"

%extend CExperimentSet
{
    
#ifdef SWIGPYTHON

 size_t __len__() const
 {
    return self->getExperimentCount();
 }

 CExperiment* __getitem__(const std::string& name) 
 {
  try
    {
      return self->getExperiment(name);
    }
    catch(...)
    {
      return NULL;
    }
 }

 CExperiment* __getitem__(unsigned int index) 
 {
    try
    {
        return self->getExperiment(index);
    }
    catch(...)
    {
      return NULL;
    }
 }

#endif // SWIGPYTHON
}

