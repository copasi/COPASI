// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CFunctionDB.i,v $ 
//   $Revision: 1.5 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2009/01/07 18:51:30 $ 
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



