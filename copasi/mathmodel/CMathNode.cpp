/**
 * CMathNode class.
 * The class CMathNode is describes a node of the equation tree.
 *
 * Created for Copasi by Stefan Hoops 2003
 */

#include <sstream>

#include "copasi.h"
#include "CMathNode.h"
#include "CMathSymbol.h"

CMathNode::CMathNode():
    CCopasiNode()
{}

CMathNode::CMathNode(const CMathNode &src):
    CCopasiNode(src)
{}

CMathNode::~CMathNode() {}

std::string CMathNode::getText() const
  {return ((CMathNode *) const_cast< CMathNode * >(this)->getChild())->getText();}

const std::string CMathNodeOperation::Operations("+-*/%^");

CMathNodeOperation::CMathNodeOperation():
    CMathNode(),
    mOperation()
{}

CMathNodeOperation::CMathNodeOperation(const std::string & operation):
    CMathNode(),
    mOperation(operation)
{assert (Operations.find(operation) != std::string::npos);}

CMathNodeOperation::CMathNodeOperation(const CMathNodeOperation & src):
    CMathNode(src),
    mOperation(src.mOperation)
{}

CMathNodeOperation::~CMathNodeOperation() {}

std::string CMathNodeOperation::getText() const
  {
    std::stringstream text;
    CMathNode * pChild =
      (CMathNode *) const_cast< CMathNodeOperation * >(this)->getChild();

    if (pChild)
      {
        text << pChild->getText() << mOperation;

        if (pChild->getSibbling())
          text << ((CMathNode *) pChild->getSibbling())->getText();
        else
          text << "-?-";
      }
    else
      text << "-?-" << mOperation << "-?-";

    return text.str();
  }

CMathNodeDerivative::CMathNodeDerivative(const std::string & operation):
    CMathNodeOperation()
{mOperation = operation;}

CMathNodeDerivative::CMathNodeDerivative(const CMathNodeDerivative &src):
    CMathNodeOperation(src)
{}

CMathNodeDerivative::~CMathNodeDerivative() {}

std::string CMathNodeDerivative::getText() const
  {
    std::stringstream text;
    CMathNode * pChild =
      (CMathNode *) const_cast< CMathNodeDerivative * >(this)->getChild();

    text << mOperation << " ";

    if (pChild)
      {
        text << pChild->getText() << "(";

        if (pChild->getSibbling())
          text << ((CMathNode *) pChild->getSibbling())->getText();
        else
          text << "-?-";

        text << ")";
      }
    else
      text << "-?-(-?-)";

    return text.str();
  }

CMathNodeNumber::CMathNodeNumber(const C_FLOAT64 & number):
    CMathNode(),
    mNumber(number)
{}

CMathNodeNumber::CMathNodeNumber(const CMathNodeNumber &src):
    CMathNode(src),
    mNumber(src.mNumber)
{}

CMathNodeNumber::~CMathNodeNumber() {}

std::string CMathNodeNumber::getText() const
  {
    std::stringstream text;
    text << mNumber;

    return text.str();
  }

CMathNodeSymbol::CMathNodeSymbol(const CMathSymbol * pSymbol):
    CMathNode(),
    mpSymbol(pSymbol)
{}

CMathNodeSymbol::CMathNodeSymbol(const CMathNodeSymbol & src):
    CMathNode(src),
    mpSymbol(src.mpSymbol)
{}

CMathNodeSymbol::~CMathNodeSymbol() {}

std::string CMathNodeSymbol::getText() const
  {
    if (mpSymbol)
      return mpSymbol->getName();
    else
      return "-?-";
  }

CMathNodeFunction::CMathNodeFunction(const CMathSymbol * pSymbol):
    CMathNodeSymbol(pSymbol)
{}

CMathNodeFunction::CMathNodeFunction(const CMathNodeFunction & src):
    CMathNodeSymbol(src)
{}

CMathNodeFunction::~CMathNodeFunction() {}

std::string CMathNodeFunction::getText() const
  {
    std::stringstream text;

    if (!mpSymbol)
      text << "-?-()";
    else
      {
        text << mpSymbol->getName() << "(";

        CMathNode * pChild =
          (CMathNode *) const_cast< CMathNodeFunction * >(this)->getChild();

        while (pChild)
          {
            text << pChild->getText();
            pChild = (CMathNode *) pChild->getSibbling();
          }

        text << ")";
      }

    return text.str();
  }
