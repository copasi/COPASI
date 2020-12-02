// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the 
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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 






%{

#include "copasi/function/CFunctionParameters.h"

%}

%ignore CFunctionParameters::operator [];
%ignore CFunctionParameters::operator[](size_t);
%ignore CFunctionParameters::operator[](size_t) const;

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
        return (unsigned C_INT32)$self->findParameterByName(name,NULL);
    }
    
    CFunctionParameter* getParameter(unsigned C_INT32 index)
    {
        try
        {
            return (*self)[index];
        }
        catch(...)
        {
            return NULL;
        }
        
    }

}

