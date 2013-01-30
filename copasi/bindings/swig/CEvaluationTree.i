// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
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
#include "function/CEvaluationTree.h"
%}

%newobject CEvaluationTree::create(CEvaluationTree::Type type);
%newobject CEvaluationTree::copy(const CEvaluationTree& src);

%ignore CEvaluationTree::operator==;
%ignore CEvaluationTree::XMLType;
%ignore CEvaluationTree::TypeName;
%ignore CEvaluationTree::getErrorPosition() const;
%ignore CEvaluationTree::setTree(const ASTNode&);
%ignore CEvaluationTree::convertASTNode(const ASTNode&);
%ignore CEvaluationTree::toAST(const CCopasiDataModel*) const;
%ignore CEvaluationTree::getNodeList;
%ignore CEvaluationTree::calls;
%ignore CEvaluationTree::setRoot;
%ignore CEvaluationTree::getRoot;
%ignore CEvaluationTree::getDeletedObjects;


#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CEvaluationTree::getRoot() const;

#endif // SWIGJAVA || CSHARP

// suppress warnings on multiple inheritance
%warnfilter(813) CEvaluationTree;

%include "function/CEvaluationTree.h"

%extend CEvaluationTree
{
    C_INT32 getErrorLocation() const
    {
        return (C_INT32)$self->getErrorPosition();
    }
/* TODO: CEvaluationTree is no longer inheriting from annotation
#if (defined SWIGJAVA || defined SWIGCSHARP)
  // the CAnnotation functionality has to be added manually because
  // Java does not know about multiple inheritance
  void setNotes(const std::string& notes)
  {
    self->setNotes(notes);
  }

  const std::string& getNotes() const
  {
    return self->getNotes();
  }

  const std::string& getMiriamAnnotation() const
  {
    return self->getMiriamAnnotation();
  }

  void setMiriamAnnotation(const std::string& miriamAnnotation,
                           const std::string& newId,
                           const std::string& oldId)
  {
    self->setMiriamAnnotation(miriamAnnotation,newId,oldId);
  }
#endif // SWIGJAVA || CSHARP
*/
}

