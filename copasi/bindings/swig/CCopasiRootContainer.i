// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
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

#include "copasi/core/CRootContainer.h"

%}



%ignore CRootContainer::CRootContainer(const std::string& name,
                                           const CRootContainer * pParent = NULL,
                                           const std::string & type = "CN",
                                           const unsigned C_INT32 & flag);
%ignore CRootContainer::getConfiguration;
%ignore CRootContainer::init;

%immutable CRootContainer::Root;

%rename (RootContainer) CRootContainer::Root;
%rename (removeDatamodelWithIndex) CRootContainer::removeDatamodel(const unsigned C_INT32);

%include "report/CRootContainer.h"

// unignore init
%rename(init) CRootContainer::init;

%extend CRootContainer
{
   static CDataModel* get(unsigned C_INT32 index)
    {
      return (CDataModel*)&(*CRootContainer::getDatamodelList())[index];
    };

    CDataModel* getDatamodel(unsigned C_INT32 index)
    {
      return &(*$self->getDatamodelList())[index];
    };

    static void init()
    {
        CRootContainer::init(0,NULL,false);
    }

};
