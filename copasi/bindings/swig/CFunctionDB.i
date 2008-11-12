// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CFunctionDB.i,v $ 
//   $Revision: 1.4.24.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/12 15:18:48 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "function/CFunctionDB.h"

%}

%include "function/CFunctionDB.h"


%extend CFunctionDB
{
    CEvaluationTree* createFunction(const std::string& name,CEvaluationTree::Type t)
    {
        CEvaluationTree* tree=CEvaluationTree::create(t);
        if(!tree) return NULL;
        tree->setObjectName(name);
        if(!self->add(tree,true))
        {
            delete tree;
            tree=NULL;
        }
        return tree;
    }
}



