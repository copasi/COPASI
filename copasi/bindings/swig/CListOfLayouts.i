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




%template(LayoutVector) CDataVector<CLayout>;
typedef CDataVector<CLayout> LayoutVector;
%template(LayoutVectorN) CDataVectorN<CLayout>;
typedef CDataVectorN<CLayout> LayoutVectorN;

%{

#include "copasi/layout/CListOfLayouts.h"

%}

%ignore CListOfLayouts::exportToSBML;
%ignore CListOfLayouts::addLayout;
%ignore CListOfLayouts::getListOfGlobalRenderInformationObjects() const;
%ignore CListOfLayouts::getRenderInformation(size_t) const;

%include "copasi/layout/CListOfLayouts.h"

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
