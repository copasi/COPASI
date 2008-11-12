// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CEvaluationTree.i,v $ 
//   $Revision: 1.5.24.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/12 15:56:12 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "function/CEvaluationTree.h"

%}

%newobject CEvaluationTree::create(CEvaluationTree::Type type);
%newobject CEvaluationTree::copy(const CEvaluationTree& src);

%ignore CEvaluationTree::XMLType;

%include "function/CEvaluationTree.h"

%extend CEvaluationTree
{
  /**
   * Retrieve the position of the error in the string description.
   * std::string::npos indicates no error.
   * @return std::string::size_type errorPosition
  C_INT32 getErrorPosition() const
  {
    return (C_INT32)self->getErrorPosition();
  }
   */

}



