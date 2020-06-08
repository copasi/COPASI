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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Sven Sahle and University of Heidelberg
// All rights reserved.

#ifndef EXPRESSION2PRESENTATIONMML_H
#define EXPRESSION2PRESENTATIONMML_H

#include <iostream>

#include "copasi/copasi.h"

LIBSBML_CPP_NAMESPACE_BEGIN
class ASTNode;
class Model;
class Reaction;
LIBSBML_CPP_NAMESPACE_END

class Expression2PresentationMML
{
public:
  Expression2PresentationMML(const ASTNode* rootnode);

  virtual ~Expression2PresentationMML() {};

  void setModel(const Model* m) {mpModel = m;};

  /**
   * set the reaction to be used as the environment for finding local parameters
   */
  void setReaction(const Reaction* m) {mpReaction = m;};

  /**
   * If this is set to true (the default) the actual name/id of a reaction is added
   * to the name of local parameter. This may lead to rather long expressions.
   * In cases where the reaction is identifiable by other means it should be set to false
   * for more compact expression display.
   */
  void setUseReactionNameInLocalParameters(bool b) {mUseReactionNameInLocalParameters = b;};

  void writeMathML(std::ostream & out) const;

protected:
  void writeMathML(std::ostream & out, const ASTNode* node, size_t l) const;
  virtual void writeMathMLFunction(std::ostream & out, const ASTNode* node, size_t l) const;
  virtual void writeMathMLName(std::ostream & out, const ASTNode* node, size_t l) const;
  virtual void writeMathMLNumber(std::ostream & out, const ASTNode* node, size_t l) const;

  const ASTNode* mRootNode;
  const Model* mpModel;
  const Reaction* mpReaction;

  bool mUseReactionNameInLocalParameters;
};

#endif // EXPRESSION2PRESENTATIONMML_H
