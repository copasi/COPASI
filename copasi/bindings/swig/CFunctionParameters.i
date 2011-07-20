// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CFunctionParameters.i,v $ 
//   $Revision: 1.6.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/07/20 20:03:17 $ 
// End CVS Header 

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

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
%ignore CFunctionParameters::getParameterByUsage;
%ignore CFunctionParameters::findParameterByName;

%include "function/CFunctionParameters.h"

// unignore some methods so that we can use them in the extension
%rename(getParameterByUsage) CFunctionParameters::getParameterByUsage;
%rename(findParameterByName) CFunctionParameters::findParameterByName;

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
        size_t  pos) const
    {
        return self->getParameterByUsage(usage,pos);
    }

    /**
     * find a parameter by its name and return its index
     */
    unsigned C_INT32 findParameterByName(const std::string & name, int dataType) const
    {
        CFunctionParameter::DataType type=(CFunctionParameter::DataType)dataType;
        return $self->findParameterByName(name,type);
    }

    CFunctionParameter* getParameter(unsigned C_INT32 index)
    {
        return (*self)[index];
    }

}

