// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiParameterGroup.i,v $ 
//   $Revision: 1.6.8.7 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/25 11:56:08 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "utilities/CCopasiParameterGroup.h"

%}

%rename(addParameterCopy) CCopasiParameterGroup::addParameter(const CCopasiParameter&);
%rename(getKeyForParameter) CCopasiParameterGroup::getKey;
%ignore operator==;

#ifdef SWIGJAVA
// remove some const methods to get rid of warnings
%ignore CCopasiParameterGroup::operator =;

%ignore CCopasiParameterGroup::getParameter(const std::string&) const;
%ignore CCopasiParameterGroup::getParameter(const unsigned long&) const;
%ignore CCopasiParameterGroup::getGroup(const std::string&) const;
%ignore CCopasiParameterGroup::getGroup(const unsigned long&) const;
%ignore CCopasiParameterGroup::getValue(const std::string&) const;
%ignore CCopasiParameterGroup::getValue(const unsigned long&) const;


#endif // SWIGJAVA

/*
 * The following code should make sure that an object that is added to a group
 * which takes ownership for the parameter is not deleted by python.
 * Unfortunatelly the SWIG documentation for this is a bit scarse and the fact
 * that the code has to be indented correctly, makes this difficult.
 * For now this is disabled and it will be added to the documentation that the
 * user has to call .__disown__() on the parameter that is added to a
 * parameter group.
#ifdef SWIGPYTHON
%pythonprepend CCopasiParameterGroup::addParameter(CCopasiParameter*) %{
        # disown the given object
        if(length(args)==2):
          args[1].__disown__()
%}
#endif // SWIGPYTHON
*/

%include "utilities/CCopasiParameterGroup.h"


%extend CCopasiParameterGroup
{
    // for backward compatibility
    unsigned C_INT32 getIndex(const std::string& name) const
    {
        return $self->getIndexByName(name);
    }
}

