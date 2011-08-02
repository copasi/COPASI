// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiRootContainer.i,v $ 
//   $Revision: 1.3.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/08/02 11:23:34 $ 
// End CVS Header 

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
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
    static CCopasiDataModel* getDatamodel(const size_t& index)
    {
      return (*CCopasiRootContainer::getDatamodelList())[index];
    };

    static void init()
    {
        CCopasiRootContainer::init(0,NULL,false);
    }

}; 
