// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
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
%ignore CListOfLayouts::getListOfGlobalRenderInformationObjects() const;
%ignore CListOfLayouts::getRenderInformation(size_t) const;

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
