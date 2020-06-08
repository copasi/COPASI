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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 


%{

#include <iostream>
#include "copasi/function/CFunctionDB.h"

%}

%ignore CFunctionDB::load(CReadConfig& configbuffer);
%ignore CFunctionDB::appendDependentFunctions;

// Actually the add function destroys the object as well if the second argument
// is true
// A fix for this to ignore the add method from the C++ API and to add a new add 
// method that only takes one argument as well as an addAndAdopt method that takes one argument.
// For backward compatibility I add another add method with two arguments that writes a warning
// message when called.
//
%ignore CFunctionDB::add(CFunction*,const bool&);


#ifdef SWIGJAVA
// delobject does not seem to work with java according to the documentation, 
// so we need another solution
// The following code has been adapted from an example in the SWIG documentation.
// The following typemap should only apply to a function that takes a CFunction pointer which has the name
// pFunctionToKeepReferenced. The only function to fit this would be the new addAndAdopt below.
%typemap(javain) CFunction *pFunctionToKeepReferenced "getCPtrAndAddReference($javainput)"

%typemap(javacode) CFunctionDB %{
  // Ensure that the GC doesn't collect any element set from Java
  // as the underlying C++ class stores a shallow copy
  private java.util.ArrayList<CFunction> functionReferences=new java.util.ArrayList<CFunction>();
  private long getCPtrAndAddReference(CFunction function) {
    functionReferences.add(function);
    return CFunction.getCPtr(function);
  }
%}
#else
%delobject CFunctionDB::addAndAdaptName;
%delobject CFunctionDB::addAndAdopt;
#endif // SWIGJAVA

%include "function/CFunctionDB.h"
// actually the add function destorys the object as well if the second argument
// is true
// I will have to find a fix for that.

%extend CFunctionDB
{
    /**
     * This function is a worjaround for the problem with the add function in the
     * language bindings.
     *
     * Alternatively one can now use the add and the addAndAdopt methods. 
     */
    CEvaluationTree* createFunction(const std::string& name,CEvaluationTree::Type t)
    {
        CFunction* tree=new CFunction(name,NULL,t);
        if(!tree) return NULL;
        if(!self->add(tree,true))
        {
            delete tree;
            tree=NULL;
        }
        return tree;
    }

    /**
     * This replaces the original add function and prints a warning.
     */
    bool add(CFunction* pFunction,bool /*adopt*/)
    {
        std::cerr << "Warning. This method is obsolete and using it is dangerous because memory management is broken and your program will likely crash.\nPlease use the createFunction method from the CFunctionDB class to create new user defined functions. These functions don't need to be added to the function database explictely since they are already created as part of it." << std::endl;
        return $self->add(pFunction,false);
    }

    /**
     * This call replaces the old add method when the second argument was specified as true.
     * This means that the COPASI backend takes ownership of the passed in function instance.
     */
    bool addAndAdopt(CFunction *pFunctionToKeepReferenced)
    {
        return $self->add(pFunctionToKeepReferenced,true);
    }

    /**
     * This call replaces the old add method when the second argument was specified as false.
     * This means that the COPASI backend doesn't take ownership of the passed in function instance.
     */
    bool add(CFunction* pFunction)
    {
        return $self->add(pFunction,false);
    }
}



