// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CLGraphicalObject.i,v $ 
//   $Revision: 1.2.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/09/26 12:14:52 $ 
// End CVS Header 

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "layout/CLGraphicalObject.h"

%}

%ignore operator<<;
%ignore CLGraphicalObject::getBoundingBox() const;
%ignore CLGraphicalObject::operator= (const CLGraphicalObject&);
%ignore CLGraphicalObject::CLGraphicalObject(const GraphicalObject & , std::map<std::string, std::string> & , const CCopasiContainer * pParent = NULL);
%ignore CLGraphicalObject::exportToSBML;
%ignore CLGraphicalObject::print;

// suppress warnings on multiple inheritance
%warnfilter(813) CLGraphicalObject;

#ifdef SWIGCSHARP
// out of some reason C# does not like the getKey wrapper method 
// method
%ignore CLGraphicalObject::getKey() const;

%extend CLGraphicalObject
{
    const std::string& getKey() const
    {  
        return $self->getKey();
    }
}
#endif // SWIGCSHARP


%include "layout/CLGraphicalObject.h"


