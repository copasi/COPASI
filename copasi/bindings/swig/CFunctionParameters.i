// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CFunctionParameters.i,v $ 
//   $Revision: 1.4.24.3 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/18 09:43:24 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "function/CFunctionParameters.h"

%}


%ignore CFunctionParameters::operator[](unsigned C_INT32);
%ignore CFunctionParameters::operator[](unsigned C_INT32) const;
%ignore CFunctionParameters::operator[](const std::string&);
%ignore CFunctionParameters::operator[](const std::string&) const;
%ignore CFunctionParameters::operator= (const CFunctionParameters&);
%ignore CFunctionParameters::operator==(const CFunctionParameters &) const;
%ignore operator<<(std::ostream&, const CFunctionParameters&);

%rename(addCopy) CFunctionParameters::add(const CFunctionParameter&);

%include "function/CFunctionParameters.h"


%extend CFunctionParameters
{
    /**
     *  Retrieves the first parameter with the specified usage after pos
     *  In a normal situation pos is set to 0 for the first call.
     *  It is increment by the method to allow subsequent searches to start
     *  after the last found item. This is usefull if several parameters
     *  with the same usage exist.
     *  @param "const string &" usage
     *  @param "unsigned C_INT32 &" pos (first call should be with 0)
     *  @return "CFunctionParameter &" usageRange
     */
    const CFunctionParameter * getParameterByUsage(CFunctionParameter::Role usage,
        unsigned C_INT32  pos) const
    {
        return self->getParameterByUsage(usage,pos);
    }

    /**
     * find a parameter by its name and return its index
     */
    unsigned C_INT32 findParameterByName(const std::string & name, CFunctionParameter::DataType  dataType) const
    {
        return self->findParameterByName(name,dataType);
    }

    CFunctionParameter* getParameter(unsigned C_INT32 index)
    {
        return (*self)[index];
    }

}

