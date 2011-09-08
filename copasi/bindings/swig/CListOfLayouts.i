// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CListOfLayouts.i,v $ 
//   $Revision: 1.2.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/09/08 16:31:37 $ 
// End CVS Header 


// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
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
%ignore CListOfLayouts::getRenderInformation;
%ignore CListOfLayouts::getListOfGlobalRenderInformationObjects;

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
