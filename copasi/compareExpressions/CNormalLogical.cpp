// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalLogical.cpp,v $
//   $Revision: 1.25 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/10/04 12:02:33 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CNormalLogical.h"
#include "CNormalChoiceLogical.h"
#include "CNormalLogicalItem.h"
#include <vector>
#include <bitset>
#include <sstream>
#include <assert.h>

CNormalLogical::CNormalLogical(): CNormalBase(), mNot(false)
{}

CNormalLogical::CNormalLogical(const CNormalLogical& src): CNormalBase(src), mNot(src.mNot)
{
  cleanSetOfSets(this->mChoices);
  copySetOfSets(src.mChoices, this->mChoices);
  cleanSetOfSets(this->mAndSets);
  copySetOfSets(src.mAndSets, this->mAndSets);
}

CNormalLogical& CNormalLogical::operator=(const CNormalLogical& src)
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
    ChoiceSetOfSets::const_iterator it = this->mChoices.begin(), endit = this->mChoices.end();
    if (this->mNot == true)
      {
        str << "NOT ";
      }
    str << "(";
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
  //std::cout << this->toString() << std::endl;
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
              negateSetOfSets(pLogical->getAndSets(), tmpSetOfSets);
              convertAndOrToOrAnd(tmpSetOfSets, *itemSetOfSets);
              cleanSetOfSets(tmpSetOfSets);
              //cleanSetOfSets(*itemSetOfSets);
              //eliminateNullItems(tmpSetOfSets,*itemSetOfSets,true);
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
              negateSetOfSets(pLogical->getAndSets(), tmpSetOfSets);
              convertAndOrToOrAnd(tmpSetOfSets, *itemSetOfSets);
              //cleanSetOfSets(*itemSetOfSets);
              cleanSetOfSets(tmpSetOfSets);
              //eliminateNullItems(tmpSetOfSets,*itemSetOfSets,true);
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
              negateSetOfSets(pLogical->getAndSets(), tmpSetOfSets);
              convertAndOrToOrAnd(tmpSetOfSets, *itemSetOfSets);
              //cleanSetOfSets(*itemSetOfSets);
              cleanSetOfSets(tmpSetOfSets);
              //eliminateNullItems(tmpSetOfSets,*itemSetOfSets,true);
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
              negateSetOfSets(pLogical->getAndSets(), tmpSetOfSets);
              convertAndOrToOrAnd(tmpSetOfSets, *itemSetOfSets /*tmpSetOfSets*/);
              cleanSetOfSets(tmpSetOfSets);
              //cleanSetOfSets(*itemSetOfSets);
              //eliminateNullItems(tmpSetOfSets,*itemSetOfSets,true);
            }
          else
            {
              copySetOfSets(pLogical->getAndSets(), *itemSetOfSets);
            }
          set1[3] = itemSetOfSets;

          itemSetOfSets = new ItemSetOfSets();
          ItemSetOfSets tmpSetOfSets;
          convertAndOrToOrAnd(*set1[0], *itemSetOfSets);
          convertAndOrToOrAnd(*set1[1], *itemSetOfSets);
          //eliminateNullItems(tmpSetOfSets,*itemSetOfSets,false);
          //cleanSetOfSets(tmpSetOfSets);
          set2[0] = itemSetOfSets;

          itemSetOfSets = new ItemSetOfSets();
          convertAndOrToOrAnd(*set1[2], *itemSetOfSets);
          convertAndOrToOrAnd(*set1[3], *itemSetOfSets);
          //eliminateNullItems(tmpSetOfSets,*itemSetOfSets,false);
          //cleanSetOfSets(tmpSetOfSets);
          set2[1] = itemSetOfSets;
          cleanSetOfSets(*set1[0]);
          cleanSetOfSets(*set1[1]);
          cleanSetOfSets(*set1[2]);
          cleanSetOfSets(*set1[3]);

          itemSetOfSets = new ItemSetOfSets();
          convertAndOrToOrAnd(*set2[0], *itemSetOfSets);
          convertAndOrToOrAnd(*set2[1], *itemSetOfSets);
          //eliminateNullItems(tmpSetOfSets,*itemSetOfSets,true);
          //cleanSetOfSets(tmpSetOfSets);

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
              std::pair<ItemSetOfSets::iterator, bool> tmpResult = this->mAndSets.insert(*tmpIt);
              ++tmpIt;
            }

          cleanSetOfSets(*set2[0]);
          cleanSetOfSets(*set2[1]);
          delete itemSetOfSets;
          ++it2;
        }
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
              this->mNot = false;
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
                }
            }
          else
            {
              ItemSet tmpSet;
              copySet((*it2).first, tmpSet);
              if (tmpAndSets.insert(std::make_pair(tmpSet, false)).second == false)
                {
                  cleanSet(tmpSet);
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
      ItemSet tmpSet2(it2->first.begin(), it2->first.end());
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
        }
      ++it2;
    }
  delete pTrueItem;
  this->mAndSets.clear();
  this->mAndSets = tmpSet;
  tmpSet.clear();
  if (result = this->generateCanonicalDNF(tmpSet))
    {
      cleanSetOfSets(this->mAndSets);
      this->mAndSets = tmpSet;
    }
  return result;
}

/**
 * Converts a set of AND combined sets of OR combined elements into a
 * target set of OR combined sets of AND combined elements.
 */
template<typename TYPE, typename SETSORTER, typename SETOFSETSSORTER>
bool CNormalLogical::convertAndOrToOrAnd(const std::set<std::pair<std::set<std::pair<TYPE*, bool>, SETSORTER >, bool>, SETOFSETSSORTER >& source,
    std::set<std::pair<std::set<std::pair<TYPE*, bool>, SETSORTER >, bool>, SETOFSETSSORTER >& target)
{
  bool result = true;
  if (source.size() > 1)
    {
      typename std::set<std::pair<std::set<std::pair<TYPE*, bool>, SETSORTER >, bool>, SETOFSETSSORTER > tmpSourceSet((++source.begin()), source.end());
      typename std::set<std::pair<std::set<std::pair<TYPE*, bool>, SETSORTER >, bool>, SETOFSETSSORTER > tmpTargetSet;
      result = ((*source.begin()).second == false);
      if (result == true)
        {
          // recursively call this function
          // the result returned in tmpTargetSet is a combination of and combined sets of or combined items
          result = convertAndOrToOrAnd(tmpSourceSet, tmpTargetSet);
          if (result == true)
            {
              // for each item in source.begin().first go through all sets in
              // tmpTarget
              typename std::set<std::pair<TYPE*, bool>, SETSORTER >::const_iterator it = (*source.begin()).first.begin(), endit = (*source.begin()).first.end();
              while (it != endit)
                {
                  typename std::set<std::pair<std::set<std::pair<TYPE*, bool>, SETSORTER >, bool>, SETOFSETSSORTER >::const_iterator it2 = tmpTargetSet.begin(), endit2 = tmpTargetSet.end();
                  while (it2 != endit2)
                    {
                      typename std::set<std::pair<TYPE*, bool>, SETSORTER > tmpSet;
                      TYPE* pNewItem = new TYPE(*(*it).first);
                      if (tmpSet.insert(std::make_pair(pNewItem, false)).second == false)
                        {
                          delete pNewItem;
                        }
                      typename std::set<std::pair<TYPE*, bool>, SETSORTER >::const_iterator it3 = (*it2).first.begin(), endit3 = (*it2).first.end();
                      while (it3 != endit3)
                        {
                          pNewItem = new TYPE(*(*it3).first);
                          if (tmpSet.insert(std::make_pair(pNewItem, false)).second == false)
                            {
                              delete pNewItem;
                            }
                          ++it3;
                        }
                      ++it2;
                      if (target.insert(std::make_pair(tmpSet, false)).second == false)
                        {
                          cleanSet(tmpSet);
                        }
                    }
                  ++it;
                }
            }
        }
      // cleanup tmpTarget
      cleanSetOfSets(tmpTargetSet);
    }
  else if (source.size() == 1)
    {
      // all not flags have to be eliminated at this point
      if ((*source.begin()).second == true)
        {
          result = false;
        }
      else
        {
          // we have a set of and combined elements in (*source.begin()).first
          // and we convert them to a set of or combined items
          // So one set of n items becomes n sets of one item each.
          const typename std::set<std::pair<TYPE*, bool>, SETSORTER > item = (*source.begin()).first;
          typename std::set<std::pair<TYPE*, bool>, SETSORTER >::const_iterator it = item.begin(), endit = item.end();
          while (it != endit && result == true)
            {
              if ((*it).second == true)
                {
                  result = false;
                }
              else
                {
                  typename std::set<std::pair<TYPE*, bool>, SETSORTER > tmpSet;
                  TYPE* pNewItem = new TYPE(*(*it).first);
                  tmpSet.insert(std::make_pair(pNewItem, false));
                  if (target.insert(std::make_pair(tmpSet, false)).second == false)
                    {
                      // clean up if the insert failed.
                      delete pNewItem;
                    }
                }
              ++it;
            }
        }
    }
  if (result == false)
    {
      // delete all elements in target
      typename std::set<std::pair<std::set<std::pair<TYPE*, bool>, SETSORTER >, bool>, SETOFSETSSORTER >::iterator it = target.begin(), endit = target.end();
      while (it != endit)
        {
          typename std::set<std::pair<TYPE*, bool>, SETSORTER >::iterator it2 = (*it).first.begin(), endit2 = (*it).first.end();
          while (it2 != endit2)
            {
              delete (*it2).first;
              ++it2;
            }
          ++it;
        }
      target.clear();
    }
  return result;
}

/**
 * Negates a set of elements.
 * The result of the operation is returned in target.
 * The type of result depends on the source. If the source was a set of AND
 * combined elements, the result is a set of OR combined elements and vice versa.
 * target set.
 */
template<typename TYPE>
bool CNormalLogical::negateSets(const std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >& source, std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >& target)
{
  bool result = true;
  typename std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >::const_iterator it = source.begin(), endit = source.end();
  while (it != endit)
    {
      if ((*it).second == false)
        {
          TYPE* pItem = new TYPE(*(*it).first);
          pItem->negate();
          target.insert(std::make_pair(pItem, false));
        }
      else
        {
          target.insert(std::make_pair(new TYPE(*(*it).first), false));
        }
      ++it;
    }
  return result;
}

/**
 * Negates a set of sets with elements.
 * The result of the operation is returned in target.
 * The type of the result depends on the source.
 * If the source was a set of AND combined sets of OR combined
 * elements, the rersult will be a set of OR combined sets with AND combined
 * elements.
 */
template<typename TYPE>
bool CNormalLogical::negateSetOfSets(const std::set<std::pair<std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >, bool>, CNormalLogical::SetOfSetsSorter<TYPE> >& source, std::set<std::pair<std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >, bool>, CNormalLogical::SetOfSetsSorter<TYPE> >& target)
{
  bool result = true;
  typename std::set<std::pair<std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >, bool>, CNormalLogical::SetOfSetsSorter<TYPE> >::const_iterator it = source.begin(), endit = source.end();
  while (it != endit && result == true)
    {
      std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> > tmpTarget;
      if ((*it).second == false)
        {
          result = negateSets((*it).first, tmpTarget);
        }
      else
        {
          typename std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >::const_iterator it2 = (*it).first.begin(), endit2 = (*it).first.end();
          while (it2 != endit2)
            {
              tmpTarget.insert(std::make_pair(new TYPE(*(*it2).first), (*it2).second));
              ++it2;
            }
        }
      target.insert(std::make_pair(tmpTarget, false));
      ++it;
    }
  if (result == false)
    {
      // cleanup target
      it = target.begin(), endit = target.end();
      while (it != endit)
        {
          typename std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >::const_iterator it2 = (*it).first.begin(), endit2 = (*it).first.end();
          while (it2 != endit2)
            {
              delete (*it2).first;
              ++it2;
            }
          ++it;
        }
      target.clear();
    }
  return result;
}

template<typename TYPE>
void CNormalLogical::cleanSet(std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >& s)
{
  typename std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >::const_iterator it = s.begin(), endit = s.end();
  while (it != endit)
    {
      delete (*it).first;
      ++it;
    }
  s.clear();
}

template<typename TYPE>
void CNormalLogical::cleanSetOfSets(std::set<std::pair<std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >, bool>, CNormalLogical::SetOfSetsSorter<TYPE> >& s)
{
  typename std::set<std::pair<std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >, bool>, CNormalLogical::SetOfSetsSorter<TYPE> >::iterator it = s.begin(), endit = s.end();
  while (it != endit)
    {
      std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> > tmpSet = (*it).first;
      cleanSet(tmpSet);
      ++it;
    }
  s.clear();
}

template<typename TYPE>
void CNormalLogical::copySet(const std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >& source, std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >& target)
{
  typename std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >::const_iterator it = source.begin(), endit = source.end();
  while (it != endit)
    {
      TYPE* pNewItem = new TYPE(*(*it).first);
      if (target.insert(std::make_pair(pNewItem, (*it).second)).second == false)
        {
          // clean up the item if the insert failed
          delete pNewItem;
        }
      ++it;
    }
}

template<typename TYPE>
void CNormalLogical::copySetOfSets(const std::set<std::pair<std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >, bool>, CNormalLogical::SetOfSetsSorter<TYPE> >& source,
                                   std::set<std::pair<std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >, bool>, CNormalLogical::SetOfSetsSorter<TYPE> >& target)
{
  typename std::set<std::pair<std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >, bool>, CNormalLogical::SetOfSetsSorter<TYPE> >::const_iterator it = source.begin(), endit = source.end();
  while (it != endit)
    {
      typename std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> > tmpSet;
      copySet((*it).first, tmpSet);
      if (target.insert(std::make_pair(tmpSet, (*it).second)).second == false)
        {
          // clean the set if the insert failed
          cleanSet(tmpSet);
        }
      ++it;
    }
}

/**
 * This routine compares a set of sets and returns true if the first
 * argument is smaller than the second.
 */
template<typename TYPE>
bool CNormalLogical::SetOfSetsSorter<TYPE>::operator()(const std::pair<std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >, bool>& lhs,
    const std::pair<std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >, bool>& rhs) const
  {
    bool result = false;
    if (lhs.second == rhs.second)
      {
        if (lhs.first.size() == rhs.first.size())
          {
            typename std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >::const_iterator it = lhs.first.begin(), endit = lhs.first.end(), it2 = rhs.first.begin();
            SetSorter<TYPE> sorter;
            while (it != endit && result == false)
              {
                result = sorter(*it, *it2);
                ++it;
                ++it2;
              }
          }
        else if (lhs.first.size() < rhs.first.size())
          {
            result = true;
          }
      }
    else if (lhs.second == true)
      {
        result = true;
      }
    return result;
  }

/**
 * This routine compares a set of sets and returns true if the first
 * argument is equal to the second argument
 */
template<typename TYPE>
bool CNormalLogical::SetOfSetsSorter<TYPE>::isEqual(const std::pair<std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >, bool>& lhs,
    const std::pair<std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >, bool>& rhs) const
  {
    bool result = true;
    if (lhs.second == rhs.second)
      {
        if (lhs.first.size() == rhs.first.size())
          {
            typename std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >::const_iterator it = lhs.first.begin(), endit = lhs.first.end(), it2 = rhs.first.begin();
            SetSorter<TYPE> sorter;
            while (it != endit && result == true)
              {
                result = sorter.isEqual(*it, *it2);
                ++it;
                ++it2;
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

/**
 * This routine compares a set and returns true if the first
 * argument is smaller than the second.
 */
template<typename TYPE>
bool CNormalLogical::SetSorter<TYPE>::operator()(const std::pair<TYPE*, bool>& lhs, const std::pair<TYPE*, bool>& rhs) const
  {
    bool result = false;
    if (lhs.second == rhs.second)
      {
        result = ((*lhs.first) < (*rhs.first));
      }
    else if (lhs.second == true)
      {
        result = true;
      }
    return result;
  }

/**
 * This routine compares a set and returns true if the first
 * argument is equal to the second.
 */
template<typename TYPE>
bool CNormalLogical::SetSorter<TYPE>::isEqual(const std::pair<TYPE*, bool>& lhs, const std::pair<TYPE*, bool>& rhs) const
  {
    bool result = true;
    if (!(lhs.second == rhs.second && (*lhs.first) == (*rhs.first)))
      {
        result = false;
      }
    return result;
  }

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
                if (comp.isEqual(*it, *it2) == false)
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
                if (comp2.isEqual(*it3, *it4) == false)
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
                if (comp(*it, *it2) == false)
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
                        if (comp2(*it3, *it4) == false)
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
                std::bitset<16> bitSet(i);
                unsigned int j, jMax = itemVector.size();
                for (j = 0;j < jMax;++j)
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
                    for (j = 0;j < jMax;++j)
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
      // combined and the neutral item is false
      neutralItem.setType(CNormalLogicalItem::FALSE);
    }
  else
    {
      neutralItem.setType(CNormalLogicalItem::TRUE);
    }
  ItemSetOfSets::const_iterator outerIt = source.begin(), outerEndit = source.end();
  ItemSetOfSets tmpTarget;
  while (outerIt != outerEndit)
    {
      ItemSet::const_iterator innerIt = outerIt->first.begin(), innerEndit = outerIt->first.end();
      bool eliminate = false;
      while (innerIt != innerEndit)
        {
          CNormalLogicalItem* pNegatedItem = new CNormalLogicalItem(*innerIt->first);
          pNegatedItem->negate();
          std::pair<CNormalLogicalItem*, bool> negatedSet = std::make_pair(pNegatedItem, innerIt->second);
          ItemSet::const_iterator pos = outerIt->first.find(negatedSet);
          if (pos != outerIt->first.end())
            {
              eliminate = true;
              break;
            }
          // also look for the simplified form just on case
          pNegatedItem->simplify();
          pos = outerIt->first.find(negatedSet);
          if (pos != outerIt->first.end())
            {
              eliminate = true;
              break;
            }
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
              if (innerIt->second == false)
                {
                  pNewItem->negate();
                }
              pNewItem->simplify();
              tmpSet.insert(std::make_pair(pNewItem, false));
              ++innerIt;
            }
          // remove the neutral item if there is more than one item in the
          // set
          if (tmpSet.size() > 1)
            {
              CNormalLogicalItem* pItem = new CNormalLogicalItem(neutralItem);
              std::pair<CNormalLogicalItem*, bool> tmpPair = std::make_pair(pItem, false);
              ItemSet::const_iterator p = tmpSet.find(tmpPair);
              if (p != tmpSet.end())
                {
                  CNormalLogicalItem* pTmpItem = p->first;
                  tmpSet.erase(tmpPair);
                  delete pTmpItem;
                }
              // since all items in tmpSet are simplified, we don't have to
              // look for the negated form of pItem with a true flag
            }
        }
      if (tmpTarget.insert(std::make_pair(tmpSet, outerIt->second)).second == false)
        {
          cleanSet(tmpSet);
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
          ItemSet tmpSet;
          CNormalLogicalItem* pItem = new CNormalLogicalItem(*sourceSet.begin()->first);
          pItem->negate();
          pItem->simplify();
          tmpSet.insert(std::make_pair(pItem, outerIt->second));
          std::pair<ItemSet, bool> tmpPair = std::make_pair(tmpSet, false);
          if (tmpTarget.find(tmpPair) != tmpTarget.end())
            {
              // the neutral element for the outer set is the negated neutral
              // element for the inner set
              ItemSet neutralSet;
              CNormalLogicalItem* pI = new CNormalLogicalItem(neutralItem);
              pI->negate();
              neutralSet.insert(std::make_pair(pI, false));
              if (target.insert(std::make_pair(neutralSet, false)).second == false)
                {
                  delete pI;
                }
            }
          else
            {
              ItemSet tmpSet2;
              copySet(sourceSet, tmpSet2);
              if (target.insert(std::make_pair(tmpSet2, outerIt->second)).second == false)
                {
                  cleanSet(tmpSet2);
                }
            }
        }
      ++outerIt;
    }
  if (target.size() > 1)
    {
      // remove the neutral element from the outer set
      ItemSet neutralSet;
      CNormalLogicalItem* pI = new CNormalLogicalItem(neutralItem);
      neutralSet.insert(std::make_pair(pI, false));
      std::pair<ItemSet, bool> neutralPair = std::make_pair(neutralSet, true);
      ItemSetOfSets::const_iterator pos = target.find(neutralPair);
      if (pos != target.end())
        {
          CNormalLogicalItem* pTmpItem = pos->first.begin()->first;
          target.erase(neutralPair);
          delete pTmpItem;
        }
      pI->negate();
      neutralPair = std::make_pair(neutralSet, false);
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
