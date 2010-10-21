// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CFunctionDB.i,v $ 
//   $Revision: 1.7.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/10/21 07:54:07 $ 
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

#include "function/CFunctionDB.h"

%}

%ignore CFunctionDB::load(CReadConfig& configbuffer);
%ignore CFunctionDB::listDependentTrees;
%ignore CFunctionDB::appendDependentFunctions;

%include "function/CFunctionDB.h"

%delobject CFunctionDB::addAndAdaptName;

// TODO
// actually the add function destorys the object as well if the second argument
// is true
// I will have to find a fix for that.

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



