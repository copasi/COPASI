// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 


%{

#include "copasi/core/CRootContainer.h"

%}



%ignore CRootContainer::CRootContainer(const std::string& name,
                                           const CRootContainer * pParent = NULL,
                                           const std::string & type = "CN",
                                           const unsigned C_INT32 & flag);
//%ignore CRootContainer::getConfiguration;
%ignore CRootContainer::init;

%immutable CRootContainer::Root;

%rename (RootContainer) CRootContainer::Root;
%rename (removeDatamodelWithIndex) CRootContainer::removeDatamodel(const unsigned C_INT32);

%include "core/CRootContainer.h"

// unignore init
%rename(init) CRootContainer::init;

%extend CRootContainer
{
   static CDataModel* get(unsigned C_INT32 index)
    {
      if (index >= CRootContainer::getDatamodelList()->size())
        return NULL;
      return (CDataModel*)&(*CRootContainer::getDatamodelList())[index];
    };

    CDataModel* getDatamodel(unsigned C_INT32 index)
    {
      if (index >= CRootContainer::getDatamodelList()->size())
        return NULL;
      return &(*$self->getDatamodelList())[index];
    };

    static void init()
    {
      try
      {
        CRootContainer::init(0,NULL,false);
      }
      catch(...)
      {
      }
    }

};
