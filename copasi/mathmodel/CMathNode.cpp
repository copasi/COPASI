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

CMathNode::CMathNode(CMathNode * pParent):
    CCopasiNode< std::string >(pParent),
    mData()
{}

CMathNode::CMathNode(const CMathNode &src):
    CCopasiNode< std::string >(src),
    mData(src.mData)
{}

CMathNode::CMathNode(const std::string & data, CMathNode * pParent):
    CCopasiNode< std::string >(pParent),
    mData(data)
{}

CMathNode::~CMathNode() {}

std::string CMathNode::getData() const
  {
    CMathNode * pC = (CMathNode *) getChild();
    if (pC) return pC->getData();
    else return "@@@";
  }

bool CMathNode::setData(const std::string & data)
{
  mData = data;
  return true;
}

const std::string CMathNodeOperation::Operations("+-*/%^");

CMathNodeOperation::CMathNodeOperation(CMathNode * pParent):
    CMathNode(pParent)
{}

CMathNodeOperation::CMathNodeOperation(const std::string & operation, CMathNode * pParent):
    CMathNode(operation, pParent)
{assert (Operations.find(operation) != std::string::npos);}

CMathNodeOperation::CMathNodeOperation(const CMathNodeOperation & src):
    CMathNode(src)
{}

CMathNodeOperation::~CMathNodeOperation() {}

std::string CMathNodeOperation::getData() const
  {
    std::stringstream text;
    const CMathNode * pChild = (CMathNode *) getChild();

    if (pChild)
      {
        text << pChild->getData();

        std::string tmp;
        if (pChild->getSibling())
          tmp = ((CMathNode *) pChild->getSibling())->getData();
        else
          tmp = "@@@";

        if (mData == "+" && tmp[0] == '-')
          {
            tmp = tmp.substr(1);
            text << " - ";
          }
        else if (mData == "-" && tmp[0] == '-')
          {
            tmp = tmp.substr(1);
            text << " + ";
          }
        else
          text << " " << mData << " ";

        if (text.str().substr(text.str().length() - 4) == "1 * ")
          text.seekp(-4, std::ios::cur);

        text << tmp;
      }
    else
      text << "@@@" << mData << "@@@";

    return text.str();
  }

CMathNodeDerivative::CMathNodeDerivative(const std::string & operation,
    CMathNode * pParent):
    CMathNodeOperation(pParent)
{mData = operation;}

CMathNodeDerivative::CMathNodeDerivative(const CMathNodeDerivative &src):
    CMathNodeOperation(src)
{}

CMathNodeDerivative::~CMathNodeDerivative() {}

std::string CMathNodeDerivative::getData() const
  {
    std::stringstream text;
    CMathNode * pChild = (CMathNode *) getChild();

    text << "(" << mData << " ";

    if (pChild)
      {
        text << pChild->getData() << ")(";

        if (pChild->getSibling())
          text << ((CMathNode *) pChild->getSibling())->getData();
        else
          text << "@@@";

        text << ")";
      }
    else
      text << "@@@)(@@@)";

    return text.str();
  }

CMathNodeNumber::CMathNodeNumber(const C_FLOAT64 & number,
                                 CMathNode * pParent):
    CMathNode(pParent)
{setData(number);}

CMathNodeNumber::CMathNodeNumber(const CMathNodeNumber &src):
    CMathNode(src)
{}

CMathNodeNumber::~CMathNodeNumber() {}

std::string CMathNodeNumber::getData() const {return mData;}

bool CMathNodeNumber::setData(const C_FLOAT64 & number)
{
  std::stringstream text;
  text << number;
  mData = text.str();

  return true;
}

CMathNodeSymbol::CMathNodeSymbol(const CMathSymbol * pSymbol,
                                 CMathNode * pParent):
    CMathNode(pParent),
    mpSymbol(pSymbol)
{setData(pSymbol);}

CMathNodeSymbol::CMathNodeSymbol(const CMathNodeSymbol & src):
    CMathNode(src),
    mpSymbol(src.mpSymbol)
{}

CMathNodeSymbol::~CMathNodeSymbol() {}

std::string CMathNodeSymbol::getData() const {return mData;}

bool CMathNodeSymbol::setData(const CMathSymbol * pSymbol)
{
  mpSymbol = pSymbol;

  if (mpSymbol)
    mData = mpSymbol->getName();
  else
    mData = "@@@";

  return true;
}

CMathNodeFunction::CMathNodeFunction(const CMathSymbol * pSymbol,
                                     CMathNode * pParent):
    CMathNodeSymbol(pSymbol, pParent)
{}

CMathNodeFunction::CMathNodeFunction(const CMathNodeFunction & src):
    CMathNodeSymbol(src)
{}

CMathNodeFunction::~CMathNodeFunction() {}

std::string CMathNodeFunction::getData() const
  {
    std::stringstream text;

    text << "<emp>" << mData << "</emp>";

    CMathNode * pChild = (CMathNode *) getChild();

    if (pChild) text << pChild->getData();

    return text.str();
  }

CMathNodeList::CMathNodeList(CMathNode * pParent):
    CMathNode(pParent)
{}

CMathNodeList::CMathNodeList(const CMathNodeList & src):
    CMathNode(src)
{}

CMathNodeList::~CMathNodeList() {}

std::string CMathNodeList::getData() const
  {
    std::stringstream text;

    CMathNode * pChild = (CMathNode *) getChild();

    text << "(";

    while (pChild)
      {
        text << pChild->getData();
        pChild = (CMathNode *) pChild->getSibling();

        if (pChild) text << ", ";
      }

    text << ")";

    return text.str();
  }
