// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CEVALUATIONNODENORMALIZER_H__
#define CEVALUATIONNODENORMALIZER_H__

#include <vector>
#include "copasi/copasi.h"

#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeOperator.h"

class CEvaluationNodeNumber;
class CEvaluationNodeConstant;
class CEvaluationNodeObject;
class CEvaluationNodeFunction;
class CEvaluationNodeCall;
class CEvaluationNodeStructure;
class CEvaluationNodeChoice;
class CEvaluationNodeVariable;
class CEvaluationNodeLogical;
class CEvaluationNodeVector;
class CEvaluationNodeWhiteSpace;

class CEvaluationNodeNormalizer
{
public:
  /**
   * Creates a normalized copy of the given CEvaluationNode.
   */
  static CEvaluationNode* normalize(const CEvaluationNode* node);

private:
  static const double ZERO;

  /**
   * Creates a normalized copy of the given CEvaluationNodeNumber.
   */
  static CEvaluationNode* normalizeCEvaluationNodeNumber(const CEvaluationNodeNumber* pNode);

  /**
   * Creates a normalized copy of the given CEvaluationNodeConstant.
   */
  static CEvaluationNode* normalizeCEvaluationNodeConstant(const CEvaluationNodeConstant* pNode);

  /**
   * Creates a normalized copy of the given CEvaluationNodeDelay.
   */
  static CEvaluationNode* normalizeCEvaluationNodeDelay(const CEvaluationNodeDelay* pNode);

  /**
   * Creates a normalized copy of the given CEvaluationNodeOperator.
   */
  static CEvaluationNode* normalizeCEvaluationNodeOperator(const CEvaluationNodeOperator* pNode);

  /**
   * Creates a normalized copy of the given CEvaluationNodeObject.
   */
  static CEvaluationNode* normalizeCEvaluationNodeObject(const CEvaluationNodeObject* pNode);

  /**
   * Creates a normalized copy of the given CEvaluationNodeFunction.
   */
  static CEvaluationNode* normalizeCEvaluationNodeFunction(const CEvaluationNodeFunction* pNode);

  /**
   * Creates a normalized copy of the given CEvaluationNodeCall.
   */
  static CEvaluationNode* normalizeCEvaluationNodeCall(const CEvaluationNodeCall* pNode);

  /**
   * Creates a normalized copy of the given CEvaluationNodeStructure.
   */
  static CEvaluationNode* normalizeCEvaluationNodeStructure(const CEvaluationNodeStructure* pNode);

  /**
   * Creates a normalized copy of the given CEvaluationNodeChoice.
   */
  static CEvaluationNode* normalizeCEvaluationNodeChoice(const CEvaluationNodeChoice* pNode);

  /**
   * Creates a normalized copy of the given CEvaluationNodeVariable.
   */
  static CEvaluationNode* normalizeCEvaluationNodeVariable(const CEvaluationNodeVariable* pNode);

  /**
   * Creates a normalized copy of the given CEvaluationNodeLogical.
   */
  static CEvaluationNode* normalizeCEvaluationNodeLogical(const CEvaluationNodeLogical* pNode);

  /**
   * Creates a normalized copy of the given CEvaluationNodeVector.
   */
  static CEvaluationNode* normalizeCEvaluationNodeVector(const CEvaluationNodeVector* pNode);

  /**
   * Creates a normalized copy of the given CEvaluationNodeWhitespace.
   */
  static CEvaluationNode* normalizeCEvaluationNodeWhiteSpace(const CEvaluationNodeWhiteSpace* pNode);

  static CEvaluationNode* normalizePowerNode(const CEvaluationNodeOperator* pNode);
  static CEvaluationNode* normalizeMultiplyNode(const CEvaluationNodeOperator* pNode);
  static CEvaluationNode* normalizeDivideNode(const CEvaluationNodeOperator* pNode);
  static CEvaluationNode* normalizeModulusNode(const CEvaluationNodeOperator* pNode);
  static CEvaluationNode* normalizePlusNode(const CEvaluationNodeOperator* pNode);
  static CEvaluationNode* normalizeMinusNode(const CEvaluationNodeOperator* pNode);
  static bool eliminateMultipleNumbers(CEvaluationNode::SubType subType, std::vector<CEvaluationNode*>& chainNodes);
  static bool collectIdenticalBranches(CEvaluationNode::SubType subType, std::vector<CEvaluationNode*>& chainNodes);
  static bool reorderNodes(std::vector<CEvaluationNode*>& chainNodes);
  static void findChainNodes(CEvaluationNodeOperator* pNode, std::vector<CEvaluationNode*>& nodes);
  static CEvaluationNodeOperator* buildOperatorBranchFromChain(CEvaluationNode::SubType subType, const std::vector<CEvaluationNode*>& chainNodes);
};

class lessCEvaluationNodes
{
public:
  bool operator()(const CEvaluationNode* pNode1, const CEvaluationNode* pNode2) {return (*pNode1 < *pNode2);}
};

#endif /* CEVALUTIONNODENORMALIZER */
