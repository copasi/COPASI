/**
 * CMathEq class.
 * The class CMathEq is describes the right hand side of an equation describing
 * a CMathVariable.
 *
 * Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"
#include "CMathEq.h"

CMathEq::CMathEq():
    mpVariable(NULL),
    mLeft(),
    mRight()
{}

CMathEq::CMathEq(const CMathEq & src):
    mpVariable(src.mpVariable),
    mLeft(src.mLeft),
    mRight(src.mRight)
{}

CMathEq::~CMathEq() {}

bool CMathEq::setVariable(const CMathVariable * pVariable)
{
  mpVariable = pVariable;
  return true;
}

const CMathVariable * CMathEq::getVariable() const {return mpVariable;}

CCopasiTree< CMathNode > & CMathEq::getLeft() {return mLeft;}

CCopasiTree< CMathNode > & CMathEq::getRight() {return mRight;}

std::string CMathEq::getLeftText() const
  {
    CMathNode * pChild =
      (CMathNode *) const_cast< CMathEq * >(this)->mLeft.begin()->getChild();

    if (pChild)
      return pChild->getText();
    else
      return "Not defined";
  }

std::string CMathEq::getRightText() const
  {
    CMathNode * pChild =
      (CMathNode *) const_cast< CMathEq * >(this)->mRight.begin()->getChild();

    if (pChild)
      return pChild->getText();
    else
      return "Not defined";
  }
