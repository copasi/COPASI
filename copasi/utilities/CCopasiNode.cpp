/**
 * CCopasiNode class.
 * The class CCopasiNode is describes a node of the CCopasiTree.
 *
 * Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"
#include "CCopasiNode.h"

CCopasiNode::CCopasiNode(CCopasiNode * pParent):
    mpParent(pParent),
    mpChild(NULL),
    mpSibbling(NULL)
{}

CCopasiNode::CCopasiNode(const CCopasiNode & src):
    mpParent(src.mpParent),
    mpChild(src.mpChild),
    mpSibbling(src.mpSibbling)
{}

CCopasiNode::~CCopasiNode()
{
  while (mpChild) delete mpChild;

  if (mpParent)
    mpParent->removeChild(this);
}

bool CCopasiNode::setParent(CCopasiNode * pParent)
{
  mpParent = pParent;
  return true;
}

CCopasiNode * CCopasiNode::getParent() {return mpParent;}

bool CCopasiNode::addChild(CCopasiNode * pChild,
                           CCopasiNode * pAfter)
{
  if (!pChild) return false;           // Nothing to insert.

  if (pAfter == this)
    {
      pChild->setSibbling(mpChild);
      mpChild = NULL;
    }

  if (mpChild)
    return mpChild->addSibbling(pChild, pAfter);

  mpChild = pChild;
  mpChild->setParent(this);

  return true;
}

bool CCopasiNode::removeChild(CCopasiNode * pChild)
{
  if (!pChild) return false;           // Nothing to remove.

  if (mpChild != pChild)
    return mpChild->removeSibbling(pChild);

  mpChild = mpChild->getSibbling();
  return true;
}

bool CCopasiNode::setChild(CCopasiNode * pChild)
{
  mpChild = pChild;
  return true;
}

CCopasiNode * CCopasiNode::getChild() {return mpChild;}

bool CCopasiNode::addSibbling(CCopasiNode * pSibbling,
                              CCopasiNode * pAfter)
{
  if (!pSibbling) return false;        // Nothing to insert.

  if (this == pAfter)
    {
      pSibbling->setParent(mpParent);
      pSibbling->setSibbling(mpSibbling);
      mpSibbling = pSibbling;
      return true;
    }

  CCopasiNode * pTmp = this;
  while (pTmp != pAfter && pTmp->getSibbling())
    pTmp = pTmp->getSibbling();

  if (pTmp == pAfter || pAfter == NULL)
    return pTmp->addSibbling(pSibbling, pTmp);
  else
    return false;                      // Insertion point no found.
}

bool CCopasiNode::removeSibbling(CCopasiNode * pSibbling)
{
  if (!pSibbling) return false;        // Nothing to remove.

  if (this == pSibbling)
    {
      if (mpParent)
        mpParent->removeChild(pSibbling);
      else
        return false;                  // Root can not be removed
    }

  CCopasiNode * pTmp = this;
  CCopasiNode * pTmpSibbling = this->mpSibbling;

  while (pTmpSibbling != pSibbling && pTmpSibbling != NULL)
    {
      pTmp = pTmpSibbling;
      pTmpSibbling = pTmpSibbling->getSibbling();
    }

  if (pTmpSibbling)
    return pTmp->setSibbling(pSibbling->getSibbling());
  else
    return false;                      // We did not find pSibbling.
}

bool CCopasiNode::setSibbling(CCopasiNode * pSibbling)
{
  mpSibbling = pSibbling;
  return true;
}

CCopasiNode * CCopasiNode::getSibbling() {return mpSibbling;}
