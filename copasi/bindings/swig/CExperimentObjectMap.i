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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 


%{

#include "copasi/parameterFitting/CExperimentObjectMap.h"

%}

%extend CExperimentObjectMap
{
    bool setObjectCN(const size_t & index,
                    const std::string & CN)
    {

        return $self->setObjectCN(index, CRegisteredCommonName(CN));
    }

    bool setObjectCN(const size_t & index,
                    const CCommonName & CN)
    {

        return $self->setObjectCN(index, CRegisteredCommonName(CN));
    }
}

// suppress warnings on nested structures
%warnfilter(325) CDataColumn;

%include "copasi/parameterFitting/CExperimentObjectMap.h"


