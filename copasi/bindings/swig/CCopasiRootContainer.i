// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 


%{

#include "report/CCopasiRootContainer.h"

%}



%ignore CCopasiRootContainer::CCopasiRootContainer(const std::string& name,
                                           const CCopasiRootContainer * pParent = NULL,
                                           const std::string & type = "CN",
                                           const unsigned C_INT32 & flag);
%ignore CCopasiRootContainer::getConfiguration;
%ignore CCopasiRootContainer::init;

%immutable CCopasiRootContainer::Root;

%rename (RootContainer) CCopasiRootContainer::Root;
%rename (removeDatamodelWithIndex) CCopasiRootContainer::removeDatamodel(const unsigned C_INT32);

%include "report/CCopasiRootContainer.h"

// unignore init
%rename(init) CCopasiRootContainer::init;

%extend CCopasiRootContainer
{
   static CCopasiDataModel* get(unsigned C_INT32 index)
    {
      return (CCopasiDataModel*)(*CCopasiRootContainer::getDatamodelList())[index];
    };

    CCopasiDataModel* getDatamodel(unsigned C_INT32 index)
    {
      return (*$self->getDatamodelList())[index];
    };

    static void init()
    {
        CCopasiRootContainer::init(0,NULL,false);
    }

};
