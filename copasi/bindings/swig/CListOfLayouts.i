// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CListOfLayouts.i,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:27 $ 
// End CVS Header 


// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%template(LayoutVector) CCopasiVector<CLayout>;
typedef CCopasiVector<CLayout> LayoutVector;

%{

#include "layout/CListOfLayouts.h"

%}

%ignore CListOfLayouts::exportToSBML;
%ignore CListOfLayouts::addLayout;

%include "layout/CListOfLayouts.h"

// unignore addLayout
%rename(addLayout) CListOfLayouts::addLayout;

%extend CListOfLayouts
{
    void addLayout(CLayout* pLayout)
    {
        std::map<std::string,std::string> m;
        $self->addLayout(pLayout,m);
    }
}
