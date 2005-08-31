/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalItem.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/08/31 14:26:54 $
   End CVS Header */

#include "CNormalItem.h"
#include "CNormalTranslation.h"

CNormalItem::CNormalItem()
    : mName("no name")
{}

CNormalItem::CNormalItem(const std::string& name, const Type& type)
    : mName(name), mType(type)
{}

CNormalItem::CNormalItem(const CNormalItem& src)
    : mName(src.mName), mType(src.mType)
{}

CNormalItem * CNormalItem::createItem(const CEvaluationNode* node)
{
  switch (CEvaluationNode::type(node->getType()))
    {
    case CEvaluationNode::VARIABLE:
      {
        CNormalItem* item = new CNormalItem(node->getInfix(), CNormalItem::VARIABLE);
        return item;
      }
    case CEvaluationNode::CONSTANT:
      {
        CNormalItem* item = new CNormalItem(node->getInfix(), CNormalItem::CONSTANT);
        return item;
      }
    case CEvaluationNode::FUNCTION:
      {
        CNormalItem * child = createItem(dynamic_cast<const CEvaluationNode*>(node->getChild()));

        std::stringstream tmp;

        if ((node->getData() == "-") && ((child->getType() == CNormalItem::VARIABLE) || (child->getType() == CNormalItem::CONSTANT)))
          tmp << node->getData() << *child;
        else
          tmp << node->getData() << "(" << *child << ")";

        CNormalItem* item = new CNormalItem(tmp.str(), CNormalItem::FUNCTION);

        delete child;
        return item;
      }
    case CEvaluationNode::OPERATOR:
      {
        if ((node->getData() == "^") || (node->getData() == "%"))
          {
            CNormalItem * child1 = createItem(dynamic_cast<const CEvaluationNode*>(node->getChild()));
            CNormalItem * child2 = createItem(dynamic_cast<const CEvaluationNode*>(node->getChild()->getSibling()));

            std::stringstream tmp;
            if ((child1->getType() == CNormalItem::VARIABLE) || (child1->getType() == CNormalItem::CONSTANT))
              tmp << *child1;
            else
              tmp << "(" << *child1 << ")";
            tmp << node->getData();
            if ((child2->getType() == CNormalItem::VARIABLE) || (child2->getType() == CNormalItem::CONSTANT))
              tmp << *child2;
            else
              tmp << "(" << *child2 << ")";

            CNormalItem* item = new CNormalItem(tmp.str(), CNormalItem::FUNCTION);

            delete child1;
            delete child2;
            return item;
          }
        else // can be called only by createItem('OPERATOR node') or createItem('FUNCTION node')
          {
            CNormalFraction * normedNode = CNormalFraction::createFraction(node);
            normedNode->simplify();

            std::stringstream tmp;
            tmp << *normedNode;
            CNormalItem * item = new CNormalItem(tmp.str(), CNormalItem::FUNCTION);

            delete normedNode;
            return item;
          }
      }
    default:  //cases CALL, CHOICE, LOGICAL, OBJECT, VECTOR.  NUMBER should not occur!
      {
        std::stringstream tmp;
        tmp << "(" << node->getInfix() << ")" << std::endl;
        CNormalItem * item = new CNormalItem(tmp.str(), CNormalItem::FUNCTION);
        return item;
      }
    }
}

bool CNormalItem::setName(const std::string& name)
{
  mName = name;
  return true;
}

bool CNormalItem::setType(const Type& type)
{
  mType = type;
  return true;
}

const std::string CNormalItem::getName() const
  {
    return mName;
  }

const CNormalItem::Type& CNormalItem::getType() const
  {
    return mType;
  }

bool CNormalItem::operator==(const CNormalItem & rhs) const
  {return ((rhs.mName == mName) && (rhs.mType == mType));}

bool CNormalItem::operator<(const CNormalItem & rhs) const
  {
    if (mType < rhs.mType)
      return true;
    if (rhs.mType < mType)
      return false;
    return (mName < rhs.mName);
  }

std::ostream & operator<<(std::ostream &os, const CNormalItem & d)
{
  os << d.mName;
  return os;
}
