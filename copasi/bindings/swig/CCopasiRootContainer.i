// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CCopasiRootContainer.i,v $ 
//   $Revision: 1.3 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:27 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
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
    CCopasiDataModel* getDatamodel(unsigned C_INT32 index)
    {
      return (*$self->getDatamodelList())[index];
    };

    static void init()
    {
        CCopasiRootContainer::init(0,NULL,false);
    }

}; 
