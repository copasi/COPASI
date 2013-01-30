// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include <vector>
#include <bitset>
#include <sstream>
#include <algorithm>

#include <assert.h>

#include "CNormalLogical.h"
#include "CNormalChoiceLogical.h"
#include "CNormalLogicalItem.h"

CNormalLogical::CNormalLogical(): CNormalBase(), mNot(false)
{}

CNormalLogical::CNormalLogical(const CNormalLogical& src): CNormalBase(src), mNot(src.mNot)
{
  cleanSetOfSets(this->mChoices);
  copySetOfSets(src.mChoices, this->mChoices);
  cleanSetOfSets(this->mAndSets);
  copySetOfSets(src.mAndSets, this->mAndSets);
}

CNormalLogical& CNormalLogical::operator=(const CNormalLogical & src)
{
  this->mNot = src.mNot;
  cleanSetOfSets(this->mChoices);
  copySetOfSets(src.mChoices, this->mChoices);
  cleanSetOfSets(this->mAndSets);
  copySetOfSets(src.mAndSets, this->mAndSets);
  return *this;
}

CNormalLogical::~CNormalLogical()
{
  cleanSetOfSets(this->mChoices);
  cleanSetOfSets(this->mAndSets);
}

CNormalBase * CNormalLogical::copy() const
{
  return new CNormalLogical(*this);
}

std::string CNormalLogical::toString() const
{
  std::ostringstream str;

  if (this->mNot == true)
    {
      str << "NOT ";
    }

  str << "(";
  ChoiceSetOfSets::const_iterator it = this->mChoices.begin(), endit = this->mChoices.end();

  while (it != endit)
    {
      if (it->second == true)
        {
          str << "NOT ";
        }

      str << "(";
      ChoiceSet::const_iterator inner = it->first.begin(), innerend = it->first.end();

      while (inner != innerend)
        {
          if (inner->second == true)
            {
              str << "NOT (" << inner->first->toString() << ")";
            }
          else
            {
              str << inner->first->toString();
            }

          ++inner;

          if (inner != innerend)
            {
              str << " & ";
            }
        }

      str << ")";
      ++it;

      if (it != endit)
        {
          str << " | ";
        }
    }

  ItemSetOfSets::const_iterator it2 = this->mAndSets.begin(), endit2 = this->mAndSets.end();

  while (it2 != endit2)
    {
      if (it2->second == true)
        {
          str << "NOT ";
        }

      str << "(";
      ItemSet::const_iterator inner = it2->first.begin(), innerend = it2->first.end();

      while (inner != innerend)
        {
          if (inner->second == true)
            {
              str << "NOT (" << inner->first->toString() << ")";
            }
          else
            {
              str << inner->first->toString();
            }

          ++inner;

          if (inner != innerend)
            {
              str << " & ";
            }
        }

      str << ")";
      ++it2;

      if (it2 != endit2)
        {
          str << " | ";
        }
    }

  str << ")";
  return str.str();
}

bool CNormalLogical::isNegated() const
{
  return this->mNot;
}

void CNormalLogical::setIsNegated(bool negate)
{
  this->mNot = negate;
}

void CNormalLogical::negate()
{
  this->mNot = !this->mNot;
}

std::ostream& operator<<(std::ostream& os, const CNormalLogical& logical)
{
  os << logical.toString();
  return os;
}

CNormalLogical::ChoiceSetOfSets& CNormalLogical::getChoices()
{
  return this->mChoices;
}

const CNormalLogical::ChoiceSetOfSets& CNormalLogical::getChoices() const
{
  return this->mChoices;
}

CNormalLogical::ItemSetOfSets& CNormalLogical::getAndSets()
{
  return this->mAndSets;
}

const CNormalLogical::ItemSetOfSets& CNormalLogical::getAndSets() const
{
  return this->mAndSets;
}

bool CNormalLogical::simplify()
{
  bool result = true;
  // get rid of the choices
  ChoiceSetOfSets::const_iterator it = this->mChoices.begin(), endit = this->mChoices.end();

  while (it != endit && result == true)
    {
      ChoiceSet tmpSet;

      if ((*it).second == true)
        {
          result = negateSets((*it).first, tmpSet);
        }
      else
        {
          copySet((*it).first, tmpSet);
        }

      ChoiceSet::iterator it2 = tmpSet.begin(), endit2 = tmpSet.end();

      while (it2 != endit2 && result == true)
        {
          if ((*it2).second == true)
            {
              (*it2).first->negate();
            }

          (*it2).first->simplify();

          ItemSetOfSets* set1[4];
          ItemSetOfSets* set2[2];

          const CNormalLogical* pLogical = &it2->first->getCondition();
          assert(pLogical != NULL);
          assert(pLogical->getChoices().size() == 0);
          ItemSetOfSets* itemSetOfSets = new ItemSetOfSets();

          if (pLogical->isNegated())
            {
              ItemSetOfSets tmpSetOfSets;
              negateSetOfSets(pLogical->getAndSets(), *itemSetOfSets);
              convertAndOrToOrAnd(*itemSetOfSets, tmpSetOfSets);
              cleanSetOfSets(*itemSetOfSets);
              eliminateNullItems(tmpSetOfSets, *itemSetOfSets, true);
              cleanSetOfSets(tmpSetOfSets);
            }
          else
            {
              copySetOfSets(pLogical->getAndSets(), *itemSetOfSets);
            }

          set1[0] = itemSetOfSets;
          pLogical = &it2->first->getTrueExpression();
          assert(pLogical != NULL);
          assert(pLogical->getChoices().size() == 0);
          itemSetOfSets = new ItemSetOfSets();

          if (pLogical->isNegated())
            {
              ItemSetOfSets tmpSetOfSets;
              negateSetOfSets(pLogical->getAndSets(), *itemSetOfSets);
              convertAndOrToOrAnd(*itemSetOfSets, tmpSetOfSets);
              cleanSetOfSets(*itemSetOfSets);
              eliminateNullItems(tmpSetOfSets, *itemSetOfSets, true);
              cleanSetOfSets(tmpSetOfSets);
            }
          else
            {
              copySetOfSets(pLogical->getAndSets(), *itemSetOfSets);
            }

          set1[1] = itemSetOfSets;
          pLogical = dynamic_cast<const CNormalLogical*>(it2->first->getCondition().copy());
          const_cast<CNormalLogical*>(pLogical)->negate();
          assert(pLogical != NULL);
          assert(pLogical->getChoices().size() == 0);
          itemSetOfSets = new ItemSetOfSets();

          if (pLogical->isNegated())
            {
              ItemSetOfSets tmpSetOfSets;
              negateSetOfSets(pLogical->getAndSets(), *itemSetOfSets);
              convertAndOrToOrAnd(*itemSetOfSets, tmpSetOfSets);
              cleanSetOfSets(*itemSetOfSets);
              eliminateNullItems(tmpSetOfSets, *itemSetOfSets, true);
              cleanSetOfSets(tmpSetOfSets);
            }
          else
            {
              copySetOfSets(pLogical->getAndSets(), *itemSetOfSets);
            }

          set1[2] = itemSetOfSets;
          delete pLogical;
          pLogical = &it2->first->getFalseExpression();
          assert(pLogical != NULL);
          assert(pLogical->getChoices().size() == 0);
          itemSetOfSets = new ItemSetOfSets();

          if (pLogical->isNegated())
            {
              ItemSetOfSets tmpSetOfSets;
              negateSetOfSets(pLogical->getAndSets(), *itemSetOfSets);
              convertAndOrToOrAnd(*itemSetOfSets, tmpSetOfSets);
              cleanSetOfSets(*itemSetOfSets);
              eliminateNullItems(tmpSetOfSets, *itemSetOfSets, true);
              cleanSetOfSets(tmpSetOfSets);
            }
          else
            {
              copySetOfSets(pLogical->getAndSets(), *itemSetOfSets);
            }

          set1[3] = itemSetOfSets;

          ItemSetOfSets tmpSetOfSets;
          itemSetOfSets = new ItemSetOfSets();
          convertAndOrToOrAnd(*set1[0], tmpSetOfSets);
          convertAndOrToOrAnd(*set1[1], tmpSetOfSets);
          eliminateNullItems(tmpSetOfSets, *itemSetOfSets, false);
          cleanSetOfSets(tmpSetOfSets);
          set2[0] = itemSetOfSets;

          itemSetOfSets = new ItemSetOfSets();
          convertAndOrToOrAnd(*set1[2], tmpSetOfSets);
          convertAndOrToOrAnd(*set1[3], tmpSetOfSets);
          eliminateNullItems(tmpSetOfSets, *itemSetOfSets, false);
          cleanSetOfSets(tmpSetOfSets);
          set2[1] = itemSetOfSets;
          cleanSetOfSets(*set1[0]);
          delete set1[0];
          cleanSetOfSets(*set1[1]);
          delete set1[1];
          cleanSetOfSets(*set1[2]);
          delete set1[2];
          cleanSetOfSets(*set1[3]);
          delete set1[3];
          itemSetOfSets = new ItemSetOfSets();
          convertAndOrToOrAnd(*set2[0], tmpSetOfSets);
          convertAndOrToOrAnd(*set2[1], tmpSetOfSets);
          eliminateNullItems(tmpSetOfSets, *itemSetOfSets, true);
          cleanSetOfSets(tmpSetOfSets);

          /**
           * Out of some reason, I can not use the insert method becasuse this
           * seems to lead to different results in certain cases. E.g. I had a
           * itemSetOfSets with 17 entries and if I used the insert, only 15
           * eneded up in mAndItems, whereas when I copied them in a loop, all
           * 17 ended up in mAndItems.
           * This is strange and unsatisfying, but since sets can't be debuged
           * that well, I didn't feel like digging into this.
           * RG
           */
          //this->mAndSets.insert(itemSetOfSets->begin(), itemSetOfSets->end());
          ItemSetOfSets::const_iterator tmpIt = itemSetOfSets->begin(), tmpEndit = itemSetOfSets->end();

          while (tmpIt != tmpEndit)
            {
              /*std::pair<ItemSetOfSets::iterator, bool> tmpResult = */
              this->mAndSets.insert(*tmpIt);
              ++tmpIt;
            }

          cleanSetOfSets(*set2[0]);
          delete set2[0];
          cleanSetOfSets(*set2[1]);
          delete set2[1];
          delete itemSetOfSets;
          ++it2;
        }

      cleanSet(tmpSet);
      tmpSet.clear();
      ++it;
    }

  if (result == true)
    {
      // we can assume that all choices have been converted, so we clean the
      // data structure
      cleanSetOfSets(this->mChoices);

      // get rid of the mNot if it is set
      if (this->mNot == true)
        {
          ItemSetOfSets tmpSetOfSets;
          result = negateSetOfSets(this->mAndSets, tmpSetOfSets);

          if (result == true)
            {
              cleanSetOfSets(this->mAndSets);
              convertAndOrToOrAnd(tmpSetOfSets, this->mAndSets);
              cleanSetOfSets(tmpSetOfSets);
              this->mNot = false;
            }
          else
            {
              cleanSetOfSets(tmpSetOfSets);
            }
        }

      ItemSetOfSets::iterator it2 = this->mAndSets.begin(), endit2 = this->mAndSets.end();
      ItemSetOfSets tmpAndSets;
      eliminateNullItems(this->mAndSets, tmpAndSets, true);
      cleanSetOfSets(tmpAndSets);

      while (it2 != endit2)
        {
          // get rid of all not flags within the items.
          // and simplify all items
          assert((*it2).second == false);
          ItemSet::iterator it3 = (*it2).first.begin(), endit3 = (*it2).first.end();

          while (it3 != endit3)
            {
              assert((*it3).second == false);
              (*it3).first->simplify();
              ++it3;
            }

          // check if one item is equal to negating another item
          // if this is the case, the whole set can be replaced by false
          // because B AND NOT(B) is always false
          // also if we find a FALSE item, we can eliminate all others
          bool eliminate = false;
          it3 = (*it2).first.begin();

          if (it3 != endit3)
            {
              --endit3;
            }

          CNormalLogicalItem* pItem1;
          CNormalLogicalItem* pItem2;

          while (it3 != endit3 && eliminate == false)
            {
              pItem1 = new CNormalLogicalItem(*(*it3).first);

              if (pItem1->getType() == CNormalLogicalItem::FALSE)
                {
                  eliminate = true;
                  delete pItem1;
                  break;
                }

              pItem1->negate();
              ItemSet::iterator it4 = it3, endit4 = (*it2).first.end();

              if (it4 != endit4)
                {
                  ++it4;
                }

              while (it4 != endit4 && eliminate == false)
                {
                  pItem2 = (*it4).first;

                  if (pItem2->getType() == CNormalLogicalItem::FALSE)
                    {
                      eliminate = true;
                      break;
                    }

                  if ((*pItem2) == (*pItem1))
                    {
                      eliminate = true;
                      break;
                    }

                  ++it4;
                }

              delete pItem1;
              ++it3;
            }

          if (eliminate == true)
            {
              ItemSet tmpSet;
              CNormalLogicalItem* pLogical = new CNormalLogicalItem();
              pLogical->setType(CNormalLogicalItem::FALSE);
              tmpSet.insert(std::make_pair(pLogical, false));

              if (tmpAndSets.insert(std::make_pair(tmpSet, false)).second == false)
                {
                  cleanSet(tmpSet);
                  tmpSet.clear();
                }
            }
          else
            {
              ItemSet tmpSet;
              copySet((*it2).first, tmpSet);

              if (tmpAndSets.insert(std::make_pair(tmpSet, false)).second == false)
                {
                  cleanSet(tmpSet);
                  tmpSet.clear();
                }
            }

          ++it2;
        }

      cleanSetOfSets(this->mAndSets);
      this->mAndSets = tmpAndSets;
      // simplify the sets, e.g. if one item in an AND combination is false, the
      // whole set can be replaced by one FALSE item
      // likewise if one item in an OR set is TRUE, the whole set can be replaced
      // by one TRUE item
      //
      it2 = this->mAndSets.begin(), endit2 = this->mAndSets.end();

      if (it2 != endit2)
        {
          --endit2;
        }

      bool eliminate = false;
      CNormalLogicalItem* pLogicalItem1, *pLogicalItem2;

      while (it2 != endit2 && eliminate == false)
        {
          // if the set in it2 contains only one item and that item is a true
          // item, we can eliminate all other sets
          if ((*it2).first.size() == 1)
            {
              pLogicalItem1 = new CNormalLogicalItem(*(*(*it2).first.begin()).first);

              if (pLogicalItem1->getType() == CNormalLogicalItem::TRUE)
                {
                  eliminate = true;
                  delete pLogicalItem1;
                  break;
                }

              pLogicalItem1->negate();
              ItemSetOfSets::iterator it3 = it2, endit3 = this->mAndSets.end();
              ++it3;

              while (it3 != endit3 && eliminate == false)
                {
                  if ((*it3).first.size() == 1)
                    {
                      pLogicalItem2 = (*(*it3).first.begin()).first;

                      if ((*pLogicalItem1) == (*pLogicalItem2))
                        {
                          eliminate = true;
                          delete pLogicalItem1;
                          break;
                        }
                    }

                  ++it3;
                }

              delete pLogicalItem1;
            }

          ++it2;
        }

      if (eliminate == true)
        {
          cleanSetOfSets(this->mAndSets);
          ItemSet tmpSet;
          CNormalLogicalItem* pLogical = new CNormalLogicalItem();
          pLogical->setType(CNormalLogicalItem::TRUE);
          tmpSet.insert(std::make_pair(pLogical, false));
          this->mAndSets.insert(std::make_pair(tmpSet, false));
        }
    }

  // now we go through all or combined sets if there are more then one and
  // erase all FALSE items
  if (this->mAndSets.size() > 1)
    {
      // there can be only one set that contains only one false item
      // in mAndSets since it is a set and the sorter eliminates all
      // others
      ItemSet tmpSet;
      CNormalLogicalItem* pFalseItem = new CNormalLogicalItem();
      pFalseItem->setType(CNormalLogicalItem::FALSE);
      tmpSet.insert(std::make_pair(pFalseItem, false));
      std::pair<ItemSet, bool> falsePair = std::make_pair(tmpSet, false);
      this->mAndSets.erase(falsePair);
      delete pFalseItem;
    }

  // since we worked on the objects in the sets, we might have messed up the order of
  // objects, or some objects might be in there twice, so to fix this, we copy the set
  ItemSetOfSets::iterator it2 = this->mAndSets.begin();
  ItemSetOfSets::iterator endit2 = this->mAndSets.end();
  ItemSetOfSets tmpSet;
  CNormalLogicalItem* pTrueItem = new CNormalLogicalItem();
  pTrueItem->setType(CNormalLogicalItem::TRUE);
  std::pair<CNormalLogicalItem*, bool> truePair = std::make_pair(pTrueItem, false);

  while (it2 != endit2)
    {
      ItemSet tmpSet2(it2->first);

      // while we are at it, we also delete all TRUE items in the inner sets
      // if those have more than one item
      // there can be only one true item per set since it
      // is a set and the sorter eliminates all others
      if (tmpSet2.size() > 1)
        {
          tmpSet2.erase(truePair);
        }

      if (tmpSet.insert(std::make_pair(tmpSet2, it2->second)).second == false)
        {
          // delete the items in this set.
          cleanSet(tmpSet2);
          tmpSet.clear();
        }

      ++it2;
    }

  delete pTrueItem;
  this->mAndSets.clear();
  this->mAndSets = tmpSet;
  tmpSet.clear();
  eliminateNullItems(this->mAndSets, tmpSet, true);
  cleanSetOfSets(tmpSet);

  if ((result = this->generateCanonicalDNF(tmpSet)))
    {
      cleanSetOfSets(this->mAndSets);
      this->mAndSets = tmpSet;
    }
  else
    {
      cleanSetOfSets(tmpSet);
    }

  return result;
}

/**
 * Converts a set of AND combined sets of OR combined elements into a
 * target set of OR combined sets of AND combined elements.
 */

/**
 * Negates a set of elements.
 * The result of the operation is returned in target.
 * The type of result depends on the source. If the source was a set of AND
 * combined elements, the result is a set of OR combined elements and vice versa.
 * target set.
 */
/**
 * Negates a set of sets with elements.
 * The result of the operation is returned in target.
 * The type of the result depends on the source.
 * If the source was a set of AND combined sets of OR combined
 * elements, the rersult will be a set of OR combined sets with AND combined
 * elements.
 */

bool CNormalLogical::operator==(const CNormalLogical& rhs) const
{
  bool result = true;

  if (this->mNot == rhs.mNot)
    {
      if (this->mChoices.size() != rhs.mChoices.size() || this->mAndSets.size() != rhs.mAndSets.size())
        {
          result = false;
        }
      else
        {
          ChoiceSetOfSets::const_iterator it = this->mChoices.begin(), endit = this->mChoices.end(), it2 = rhs.mChoices.begin();
          CNormalLogical::SetOfSetsSorter<CNormalChoiceLogical> comp;

          while (it != endit)
            {
              if (comp.isEqual((*it), (*it2)) == false)
                {
                  result = false;
                  break;
                }

              ++it;
              ++it2;
            }

          ItemSetOfSets::const_iterator it3 = this->mAndSets.begin(), endit3 = this->mAndSets.end(), it4 = rhs.mAndSets.begin();
          CNormalLogical::SetOfSetsSorter<CNormalLogicalItem> comp2;

          while (it3 != endit3 && result == true)
            {
              if (comp2.isEqual((*it3), (*it4)) == false)
                {
                  result = false;
                  break;
                }

              ++it3;
              ++it4;
            }
        }
    }
  else
    {
      result = false;
    }

  return result;
}

bool CNormalLogical::operator<(const CNormalLogical& rhs) const
{
  bool result = true;

  if (this->mNot == false && rhs.mNot == true)
    {
      result = false;
    }
  else if (this->mNot == rhs.mNot)
    {
      if (this->mChoices.size() < rhs.mChoices.size())
        {
          result = false;
        }
      else if (this->mChoices.size() == rhs.mChoices.size())
        {
          ChoiceSetOfSets::const_iterator it = this->mChoices.begin(), endit = this->mChoices.end(), it2 = rhs.mChoices.begin();
          CNormalLogical::SetOfSetsSorter<CNormalChoiceLogical> comp;

          while (it != endit)
            {
              if (comp((*it), (*it2)) == false)
                {
                  result = false;
                  break;
                }

              ++it;
              ++it2;
            }

          if (result == true)
            {
              if (this->mAndSets.size() > rhs.mAndSets.size())
                {
                  result = false;
                }
              else if (this->mAndSets.size() == rhs.mAndSets.size())
                {
                  ItemSetOfSets::const_iterator it3 = this->mAndSets.begin(), endit3 = this->mAndSets.end(), it4 = rhs.mAndSets.begin();
                  CNormalLogical::SetOfSetsSorter<CNormalLogicalItem> comp2;

                  while (it3 != endit3)
                    {
                      if (comp2((*it3), (*it4)) == false)
                        {
                          result = false;
                          break;
                        }

                      ++it3;
                      ++it4;
                    }
                }
            }
        }
    }

  return result;
}

void CNormalLogical::setAndSets(const ItemSetOfSets& set)
{
  cleanSetOfSets(this->mAndSets);
  this->mAndSets.clear();
  copySetOfSets(set, this->mAndSets);
}

void CNormalLogical::setChoices(const ChoiceSetOfSets& set)
{
  cleanSetOfSets(this->mChoices);
  this->mChoices.clear();
  copySetOfSets(set, this->mChoices);
}

/*
std::string CNormalLogical::debug() const
{
    std::ostringstream os;
    os << "Logical: " << *this << std::endl;
    CNormalLogical::ItemSetOfSets::const_iterator it=this->mAndSets.begin();
    CNormalLogical::ItemSetOfSets::const_iterator endit=this->mAndSets.end();
    while(it!=endit)
    {
        os << "new set with " << it->first.size() << " items." << std::endl;
        CNormalLogical::ItemSet::const_iterator it2=it->first.begin();
        CNormalLogical::ItemSet::const_iterator endit2=it->first.end();
        while(it2!=endit2)
        {
           os << "item: " << *(it2->first) << std::endl;
           os << "item left: " << it2->first->getLeft() << std::endl;
           os << "item right: " << it2->first->getRight() << std::endl;
           ++it2;
        }
        ++it;
    }
    return os.str();
}

std::set<const CNormalLogical*> CNormalLogical::findLogicals() const
{
    std::set<const CNormalLogical*> set;
    ChoiceSetOfSets::const_iterator it=this->mChoices.begin();
    ChoiceSetOfSets::const_iterator endit=this->mChoices.end();
    while(it!=endit)
    {
        ChoiceSet::const_iterator it2=it->first.begin();
        ChoiceSet::const_iterator endit2=it->first.end();
        while(it2!=endit2)
        {
            set.insert(&(*it2).first->getCondition());
            std::set<const CNormalLogical*> tmpSet=(*it2).first->getCondition().findLogicals();
            set.insert(tmpSet.begin(),tmpSet.end());
            set.insert(&(*it2).first->getTrueExpression());
            tmpSet.clear();
            tmpSet=(*it2).first->getTrueExpression().findLogicals();
            set.insert(tmpSet.begin(),tmpSet.end());
            set.insert(&(*it2).first->getFalseExpression());
            tmpSet.clear();
            tmpSet=(*it2).first->getFalseExpression().findLogicals();
            set.insert(tmpSet.begin(),tmpSet.end());
            ++it2;
        }
        ++it;
    }
    return set;
}
 */

bool CNormalLogical::generateCanonicalDNF(ItemSetOfSets& tmpAndSets) const
{
  bool result = true;

  if (this->mChoices.empty() && !this->mAndSets.empty())
    {
      // first we have to create a map with logical items as the keys
      // the sorting should be OK since CNormalLogicalItem implements the
      // less operator.
      std::map<CNormalLogicalItem, bool> truthValueMap;
      ItemSetOfSets::const_iterator outerIt = this->mAndSets.begin(), outerEndit = this->mAndSets.end();

      while (outerIt != outerEndit && result == true)
        {
          result = (outerIt->second == false);
          ItemSet::const_iterator innerIt = outerIt->first.begin(), innerEndit = outerIt->first.end();

          while (innerIt != innerEndit && result == true)
            {
              result = (innerIt->second == false);
              truthValueMap[*(innerIt->first)] = false;
              ++innerIt;
            }

          ++outerIt;
        }

      if (truthValueMap.size() <= 16)
        {
          std::vector<CNormalLogicalItem> itemVector;
          std::map<CNormalLogicalItem, bool>::const_iterator mapIt = truthValueMap.begin(), mapEndit = truthValueMap.end();

          while (mapIt != mapEndit)
            {
              // only add the item if the negated item is not already part
              // of the vector
              CNormalLogicalItem* pNegatedItem = new CNormalLogicalItem(mapIt->first);
              pNegatedItem->negate();
              pNegatedItem->simplify();

              if (std::find(itemVector.begin(), itemVector.end(), *pNegatedItem) == itemVector.end())
                {
                  itemVector.push_back(mapIt->first);
                }

              delete pNegatedItem;
              ++mapIt;
            }

          unsigned int i = 0, iMax = (1 << itemVector.size());

          while (i < iMax && result == true)
            {
              // create a new row for the truth table
              // the bits in i can be mapped to the truth values
              std::bitset<16> bitSet((unsigned long long)i);
              unsigned int j, jMax = itemVector.size();

              for (j = 0; j < jMax; ++j)
                {
                  truthValueMap[itemVector[j]] = bitSet[j];
                  // set the truth value for the negated item if it is in the
                  // map
                  CNormalLogicalItem* pNegatedItem = new CNormalLogicalItem(itemVector[j]);
                  pNegatedItem->negate();
                  pNegatedItem->simplify();

                  if (truthValueMap.find(*pNegatedItem) != truthValueMap.end())
                    {
                      truthValueMap[*pNegatedItem] = !(bitSet[j]);
                    }

                  delete pNegatedItem;
                }

              // now we evaluate the logical expression to see if the result
              // is true or false
              if (this->evaluateExpression(truthValueMap) == true)
                {
                  // the result was true, so this combination is part of the
                  // canonical disjunctive normalform
                  ItemSet tmpSet;

                  for (j = 0; j < jMax; ++j)
                    {
                      CNormalLogicalItem* pItem = new CNormalLogicalItem(itemVector[j]);

                      if (bitSet[j] == false)
                        {
                          pItem->negate();
                          pItem->simplify();
                        }

                      tmpSet.insert(std::make_pair(pItem, false));
                    }

                  tmpAndSets.insert(std::make_pair(tmpSet, false));
                }

              ++i;
            }
        }
      else
        {
          result = false;
        }
    }
  else
    {
      result = false;
    }

  return result;
}

bool CNormalLogical::evaluateExpression(const std::map<CNormalLogicalItem, bool>& truthValueMap) const
{
  bool result = false;
  ItemSetOfSets::const_iterator outerIt = this->mAndSets.begin(), outerEndit = this->mAndSets.end();

  while (outerIt != outerEndit)
    {
      ItemSet::const_iterator innerIt = outerIt->first.begin(), innerEndit = outerIt->first.end();
      bool innerResult = true;

      while (innerIt != innerEndit && innerResult == true)
        {
          std::map<CNormalLogicalItem, bool>::const_iterator pos = truthValueMap.find(*(innerIt->first));
          assert(pos != truthValueMap.end());

          if (pos != truthValueMap.end())
            {
              innerResult = pos->second;

              if (innerIt->second == true) innerResult = (!innerResult);
            }
          else
            {
              innerResult = false;
            }

          ++innerIt;
        }

      if (outerIt->second == true)
        {
          innerResult = (!innerResult);
        }

      if (innerResult == true)
        {
          result = true;
          break;
        }

      ++outerIt;
    }

  return result;
}

/**
 * This methods checks wether there is something like A and !A in a set, if
 * such an occurance is found, the whole set is converted to a set with either a false or a true item.
 * For or combined items, this would be true, for and combined
 * sets, it would be false.
 * If there already are sets in the outer set, this set could be eliminated
 * altogether.
 */
void CNormalLogical::eliminateNullItems(const ItemSetOfSets& source, ItemSetOfSets& target, bool orSet)
{
  CNormalLogicalItem neutralItem = CNormalLogicalItem();

  if (orSet == true)
    {
      // the outer set is or combined, so the items in the inner set are and
      // combined and the neutral item is for the outer set is the false item
      // and for the innerset it is the true item
      neutralItem.setType(CNormalLogicalItem::FALSE);
    }
  else
    {
      neutralItem.setType(CNormalLogicalItem::TRUE);
    }

  ItemSetOfSets::const_iterator outerIt = source.begin(), outerEndit = source.end();
  ItemSetOfSets tmpTarget;
  CNormalLogicalItem* pNegatedNeutralItem = new CNormalLogicalItem(neutralItem);
  pNegatedNeutralItem->negate();
  pNegatedNeutralItem->simplify();
  std::pair<CNormalLogicalItem*, bool> pNegatedNeutralItemPair1 = std::make_pair(&neutralItem, false);
  std::pair<CNormalLogicalItem*, bool> pNegatedNeutralItemPair2 = std::make_pair(pNegatedNeutralItem, true);

  while (outerIt != outerEndit)
    {
      ItemSet::const_iterator innerIt = outerIt->first.begin(), innerEndit = outerIt->first.end();
      bool eliminate = false;

      while (innerIt != innerEndit)
        {
          if (outerIt->first.find(pNegatedNeutralItemPair1) != outerIt->first.end() || outerIt->first.find(pNegatedNeutralItemPair2) != outerIt->first.end())
            {
              eliminate = true;
              break;
            }

          CNormalLogicalItem* pNegatedItem = new CNormalLogicalItem(*innerIt->first);
          pNegatedItem->negate();
          std::pair<CNormalLogicalItem*, bool> negatedPair = std::make_pair(pNegatedItem, innerIt->second);
          ItemSet::const_iterator pos = outerIt->first.find(negatedPair);

          if (pos != outerIt->first.end())
            {
              eliminate = true;
              delete pNegatedItem;
              break;
            }

          // also look for the simplified form just in case
          pNegatedItem->simplify();
          pos = outerIt->first.find(negatedPair);

          if (pos != outerIt->first.end())
            {
              eliminate = true;
              delete pNegatedItem;
              break;
            }

          delete pNegatedItem;
          ++innerIt;
        }

      ItemSet tmpSet;

      if (eliminate)
        {
          CNormalLogicalItem* pTmpItem = new CNormalLogicalItem(neutralItem);

          if (innerIt->second == true)
            {
              pTmpItem->negate();
            }

          // only add simplified elements
          pTmpItem->simplify();
          tmpSet.insert(std::make_pair(pTmpItem, false));
        }
      else
        {
          innerIt = outerIt->first.begin(), innerEndit = outerIt->first.end();

          while (innerIt != innerEndit)
            {
              CNormalLogicalItem* pNewItem = new CNormalLogicalItem(*innerIt->first);

              if (innerIt->second == true)
                {
                  pNewItem->negate();
                }

              pNewItem->simplify();
              tmpSet.insert(std::make_pair(pNewItem, false));
              ++innerIt;
            }

          // remove the neutral item of the inner set if there is more than one item in the
          // set
          if (tmpSet.size() > 1)
            {
              // neutralItem is the neutral item for the outer set
              // to get the neutral item for the inner set, we have to negate
              // the one for the outer set
              CNormalLogicalItem* pItem = new CNormalLogicalItem(neutralItem);
              pItem->negate();
              pItem->simplify();
              std::pair<CNormalLogicalItem*, bool> tmpPair = std::make_pair(pItem, false);
              ItemSet::const_iterator p = tmpSet.find(tmpPair);

              if (p != tmpSet.end())
                {
                  CNormalLogicalItem* pTmpItem = p->first;
                  tmpSet.erase(tmpPair);
                  delete pTmpItem;
                }

              delete pItem;
              // since all items in tmpSet are simplified, we don't have to
              // look for the negated form of pItem with a true flag
            }
        }

      if (tmpTarget.insert(std::make_pair(tmpSet, outerIt->second)).second == false)
        {
          // TODO check why this is the case in e.g. test_normalform::test_nested_stepwise_fractions_3levels
          // TODO But right now this does not seem to invalidate the results.
          cleanSet(tmpSet);
          tmpSet.clear();
        }

      ++outerIt;
    }

  // now we have to do the same thing for the outer set
  outerIt = tmpTarget.begin();
  outerEndit = tmpTarget.end();

  while (outerIt != outerEndit)
    {
      const ItemSet& sourceSet = outerIt->first;

      // we can only check for the negated set if there is only one item in
      // the set, everything else is to complicated for now
      if (sourceSet.size() == 1)
        {
          if ((sourceSet.begin()->first->getType() == pNegatedNeutralItem->getType() && sourceSet.begin()->second == false) || (sourceSet.begin()->first->getType() == neutralItem.getType() && sourceSet.begin()->second == true))
            {
              // we can stop here since we now know that the whole set of sets
              // is true or false depending on the logical order of the set of
              // sets.
              cleanSetOfSets(target);
              ItemSet neutralSet;
              CNormalLogicalItem* pI = new CNormalLogicalItem(neutralItem);
              pI->negate();
              neutralSet.insert(std::make_pair(pI, false));

              if (target.insert(std::make_pair(neutralSet, false)).second == false)
                {
                  delete pI;
                }

              break;
            }

          ItemSet tmpSet;
          CNormalLogicalItem* pItem = new CNormalLogicalItem(*sourceSet.begin()->first);
          pItem->negate();
          pItem->simplify();
          tmpSet.insert(std::make_pair(pItem, outerIt->second));
          std::pair<ItemSet, bool> tmpPair = std::make_pair(tmpSet, false);

          if (tmpTarget.find(tmpPair) != tmpTarget.end())
            {
              // we can stop here since we now know that the whole set of sets
              // is true or false depending on the logical order of the set of
              // sets.
              cleanSetOfSets(target);
              ItemSet neutralSet;
              CNormalLogicalItem* pI = new CNormalLogicalItem(neutralItem);
              pI->negate();
              neutralSet.insert(std::make_pair(pI, false));

              if (target.insert(std::make_pair(neutralSet, false)).second == false)
                {
                  delete pI;
                }

              delete pItem;
              break;
            }
          else
            {
              ItemSet tmpSet2;
              copySet(sourceSet, tmpSet2);

              if (target.insert(std::make_pair(tmpSet2, outerIt->second)).second == false)
                {
                  cleanSet(tmpSet2);
                  tmpSet.clear();
                }
            }

          delete pItem;
        }
      else
        {
          ItemSet tmpSet2;
          copySet(sourceSet, tmpSet2);

          if (target.insert(std::make_pair(tmpSet2, outerIt->second)).second == false)
            {
              cleanSet(tmpSet2);
              tmpSet2.clear();
            }
        }

      ++outerIt;
    }

  cleanSetOfSets(tmpTarget);
  delete pNegatedNeutralItem;

  if (target.size() > 1)
    {
      // remove the neutral element from the outer set
      ItemSet neutralSet;
      CNormalLogicalItem* pI = new CNormalLogicalItem(neutralItem);
      neutralSet.insert(std::make_pair(pI, false));
      std::pair<ItemSet, bool> neutralPair = std::make_pair(neutralSet, false);
      ItemSetOfSets::const_iterator pos = target.find(neutralPair);

      if (pos != target.end())
        {
          CNormalLogicalItem* pTmpItem = pos->first.begin()->first;
          target.erase(neutralPair);
          delete pTmpItem;
        }

      pI->negate();
      neutralPair = std::make_pair(neutralSet, true);
      pos = target.find(neutralPair);

      if (pos != target.end())
        {
          CNormalLogicalItem* pTmpItem = pos->first.begin()->first;
          target.erase(neutralPair);
          delete pTmpItem;
        }

      delete pI;
    }
}

#ifdef COPASI_DEBUG

void CNormalLogical::printSetOfSets(const ItemSetOfSets& set)
{
  ItemSetOfSets::const_iterator outerIt = set.begin(), outerEndit = set.end();

  while (outerIt != outerEndit)
    {
      ItemSet::const_iterator innerIt = outerIt->first.begin(), innerEndit = outerIt->first.end();

      while (innerIt != innerEndit)
        {
          std::cout << innerIt->first->toString() << " ^ ";
          ++innerIt;
        }

      std::cout << std::endl;
      ++outerIt;
    }
}

void CNormalLogical::printSetSizes(const ItemSetOfSets& set)
{
  ItemSetOfSets::const_iterator outerIt = set.begin(), outerEndit = set.end();
  std::cout << "Number of Sets: " << set.size() << std::endl;

  while (outerIt != outerEndit)
    {
      std::cout << "   Number of elements in set: " << outerIt->first.size() << std::endl;
      ++outerIt;
    }
}

void CNormalLogical::printSetElement(const ItemSetOfSets& set, unsigned int index1, unsigned int index2)
{
  if (index1 >= set.size()) return;

  ItemSetOfSets::const_iterator outerIt = set.begin();
  unsigned int i = 0;

  while (i < index1)
    {
      ++i;
      ++outerIt;
    }

  if (index2 >= outerIt->first.size()) return;

  i = 0;
  ItemSet::const_iterator innerIt = outerIt->first.begin();

  while (i < index2)
    {
      ++i;
      ++innerIt;
    }

  std::cout << innerIt->first->toString();
}
#endif // COPASI_DEBUG
