// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalLogical.h,v $
//   $Revision: 1.22 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:26:19 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CNormalLogical_H__
#define CNormalLogical_H__

#include <string>
#include <iostream>
#include <set>
#include <map>
#include <utility>

#include "copasi/compareExpressions/CNormalBase.h"
#include "copasi/compareExpressions/CNormalLogicalItem.h"
#include "copasi/compareExpressions/CNormalChoiceLogical.h"

class CNormalLogical : public CNormalBase
{
public:
  template<typename TYPE>
  class SetSorter
  {
  public:
    /**
     * This routine compares a set and returns true if the first
     * argument is smaller than the second.
     */
    bool operator()(const std::pair<TYPE*, bool>& lhs,
                    const std::pair<TYPE*, bool>& rhs) const
    {
      bool result = false;

      // the compiler warnings about broken strict aliasing rules
      // that are issued by e.g. gcc 4.4.5 on linux are bogus
      // see GCC Bug 39390
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
    bool isEqual(const std::pair<TYPE*, bool>& lhs,
                 const std::pair<TYPE*, bool>& rhs) const
    {
      bool result = true;

      if (!(lhs.second == rhs.second && (*lhs.first) == (*rhs.first)))
        {
          result = false;
        }

      return result;
    }
  };

  template<typename TYPE> class TemplateSet:
      public std::set< std::pair< TYPE *, bool >, SetSorter< TYPE > > {};

  template<typename TYPE>
  class SetOfSetsSorter
  {
  public:
    /**
     * This routine compares a set of sets and returns true if the first
     * argument is smaller than the second.
     */
    bool operator()(const std::pair<TemplateSet<TYPE>, bool>& lhs, const std::pair<TemplateSet<TYPE>, bool>& rhs) const
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
                  // first test the other way round because if
                  // it2 is less then it, we can already stop
                  if (sorter(*it2, *it) == true)
                    {
                      break;
                    }

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
     * argument is smaller than the second.
     */
    bool isEqual(const std::pair<TemplateSet<TYPE>, bool>& lhs,
                 const std::pair<TemplateSet<TYPE>, bool>& rhs) const
    {
      bool result = true;

      if (lhs.second == rhs.second)
        {
          if (lhs.first.size() == rhs.first.size())
            {
              typename std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter <TYPE> >::const_iterator
              it = lhs.first.begin(),
                   endit = lhs.first.end(),
                           it2 = rhs.first.begin();

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
  };

  template<typename TYPE> class TemplateSetOfSets:
      public std::set< std::pair< TemplateSet< TYPE >, bool >, SetOfSetsSorter< TYPE > > {};

  typedef TemplateSet< CNormalChoiceLogical > ChoiceSet;
  typedef TemplateSetOfSets< CNormalChoiceLogical > ChoiceSetOfSets;
  typedef TemplateSet< CNormalLogicalItem > ItemSet;
  typedef TemplateSetOfSets< CNormalLogicalItem > ItemSetOfSets;

protected:
  /**
   * Flag to specify whether the whole logical expression has to be
   * negated.
   */
  bool mNot;

  // this is a set of sets.
  // all sets are combined by OR and all items within the sets are
  // combined by AND
  // the boolean value represents negation (NOT)
  // in the normlized form all NOT flags should be false
  ItemSetOfSets mAndSets;

  // this is a set of sets.
  // all sets are combined by OR and all items within the sets are
  // combined by AND
  // the boolean value represents negation (NOT)
  // in the normlized form the set should be empty
  ChoiceSetOfSets mChoices;

public:
  CNormalLogical();
  CNormalLogical(const CNormalLogical& src);
  virtual ~CNormalLogical();

  CNormalLogical& operator=(const CNormalLogical& src);
  bool operator==(const CNormalLogical& rhs) const;
  bool operator<(const CNormalLogical& rhs) const;

  virtual CNormalBase * copy() const;

  virtual std::string toString() const;
  virtual bool simplify();

  bool isNegated() const;

  void setIsNegated(bool negate);

  void negate();

  ChoiceSetOfSets& getChoices();
  const ChoiceSetOfSets& getChoices() const;

  ItemSetOfSets& getAndSets();
  const ItemSetOfSets& getAndSets() const;

  void setAndSets(const ItemSetOfSets& set);
  void setChoices(const ChoiceSetOfSets& set);

  /**
   * This routine calls cleanSet on all inner sets.
   */
  template<typename TYPE>
  static void cleanSetOfSets(TemplateSetOfSets<TYPE> & s)
  {
    typename TemplateSetOfSets<TYPE>::iterator it = s.begin(), endit = s.end();

    while (it != endit)
      {
        //TemplateSet<TYPE> tmpSet=it->first;
        cleanSet(/*tmpSet*/it->first);
        ++it;
      }

    s.clear();
  }

  /**
   * This routine makes a deep copy of all elements in the souce set and
   * appends them to the target set.
   */
  template<typename TYPE>
  static void copySet(const TemplateSet<TYPE> & source, TemplateSet<TYPE> & target)
  {
    typename TemplateSet<TYPE>::const_iterator it = source.begin(), endit = source.end();

    while (it != endit)
      {
        bool tmpRes = target.insert(std::make_pair(new TYPE(*it->first), it->second)).second;
        assert(tmpRes == true);
        ++it;
      }
  }

  /**
   * This routine calls delete an all pointers in the set.
   */
  template<typename TYPE>
  static void cleanSet(const TemplateSet<TYPE> & s)
  {
    typename TemplateSet<TYPE>::const_iterator it = s.begin(), endit = s.end();

    while (it != endit)
      {
        delete it->first;
        ++it;
      }
  }

protected:
  /**
   * Negates a set of elements.
   * The result of the operation is returned in target.
   * The type of result depends on the source. If the source was a set of AND
   * combined elements, the result is a set of OR combined elements and vice versa.
   * target set.
   */
  template<typename TYPE>
  static bool negateSets(const TemplateSet<TYPE> & source,
                         TemplateSet<TYPE> & target)
  {
    bool result = true;
    typename TemplateSet<TYPE>::const_iterator it = source.begin(), endit = source.end();

    while (it != endit)
      {
        if (it->second == false)
          {
            TYPE* pItem = new TYPE(*it->first);
            pItem->negate();
            target.insert(std::make_pair(pItem, false));
          }
        else
          {
            target.insert(std::make_pair(new TYPE(*it->first), false));
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
  static bool negateSetOfSets(const TemplateSetOfSets<TYPE> & source,
                              TemplateSetOfSets<TYPE> & target)
  {
    bool result = true;
    typename TemplateSetOfSets<TYPE>::const_iterator it = source.begin(), endit = source.end();

    while (it != endit && result == true)
      {
        TemplateSet<TYPE> tmpTarget;

        if (it->second == false)
          {
            result = negateSets(it->first, tmpTarget);
          }
        else
          {
            typename std::set<std::pair<TYPE*, bool>, CNormalLogical::SetSorter<TYPE> >::const_iterator it2 = it->first.begin(), endit2 = it->first.end();

            while (it2 != endit2)
              {
                tmpTarget.insert(std::make_pair(new TYPE(*it2->first), it2->second));
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
            typename TemplateSet<TYPE>::const_iterator it2 = it->first.begin(), endit2 = it->first.end();

            while (it2 != endit2)
              {
                delete it2->first;
                ++it2;
              }

            ++it;
          }

        target.clear();
      }

    return result;
  }

  /**
   * Converts a set of AND combined sets of OR combined elements into a
   * target set of OR combined sets of AND combined elements.
   */
  template<typename TYPE>
  static bool convertAndOrToOrAnd(const TemplateSetOfSets<TYPE> & source,
                                  TemplateSetOfSets<TYPE> & target)
  {
    bool result = true;

    if (source.size() > 1)
      {
        TemplateSetOfSets<TYPE> tmpSourceSet(source);
        tmpSourceSet.erase(tmpSourceSet.begin());

        TemplateSetOfSets<TYPE> tmpTargetSet;
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
                typename TemplateSet<TYPE>::const_iterator it = (*source.begin()).first.begin(), endit = (*source.begin()).first.end();

                while (it != endit)
                  {
                    typename TemplateSetOfSets<TYPE>::const_iterator it2 = tmpTargetSet.begin(), endit2 = tmpTargetSet.end();

                    while (it2 != endit2)
                      {
                        TemplateSet<TYPE> tmpSet;
                        TYPE* pNewItem = new TYPE(*it->first);

                        if (tmpSet.insert(std::make_pair(pNewItem, false)).second == false)
                          {
                            delete pNewItem;
                          }

                        typename TemplateSet<TYPE>::const_iterator it3 = it2->first.begin(), endit3 = it2->first.end();

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
            const TemplateSet<TYPE> item = (*source.begin()).first;
            typename TemplateSet<TYPE>::const_iterator it = item.begin(), endit = item.end();

            while (it != endit && result == true)
              {
                if (it->second == true)
                  {
                    result = false;
                  }
                else
                  {
                    TemplateSet<TYPE> tmpSet;
                    TYPE* pNewItem = new TYPE(*it->first);
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
        typename TemplateSetOfSets<TYPE>::iterator it = target.begin(), endit = target.end();

        while (it != endit)
          {
            typename TemplateSet<TYPE>::iterator it2 = it->first.begin(), endit2 = it->first.end();

            while (it2 != endit2)
              {
                delete it2->first;
                ++it2;
              }

            ++it;
          }

        target.clear();
      }

    return result;
  }

  /**
   * This routine makes deep copies of all inner sets and appends them to
   * the target set.
   */
  template<typename TYPE>
  static void copySetOfSets(const TemplateSetOfSets<TYPE> & source,
                            TemplateSetOfSets<TYPE> & target)
  {
    typename TemplateSetOfSets<TYPE>::const_iterator it = source.begin(), endit = source.end();

    while (it != endit)
      {
        TemplateSet<TYPE> tmpSet;
        copySet(it->first, tmpSet);
        bool tmpRes = target.insert(std::make_pair(tmpSet, it->second)).second;
        assert(tmpRes == true);
        ++it;
      }
  }

  /**
   * This method creates the canonical disjunctive normalform for a logical
   * expression. The expression must not contain choices and no negated item
   * sets or items. Since the method scales with exponentially, the number of
   * logical individual logical items in the expression is limited to 16.
   * The return value is true if the call succeeded and false otherwise.
   */
  bool generateCanonicalDNF(ItemSetOfSets& tmpAndSet) const;

  /**
   * Given a map that associates each logical element with a truth value,
   * this method evaluates the whole logical expression.
   */
  bool evaluateExpression(const std::map<CNormalLogicalItem, bool>& truthValueMap) const;

  /**
   * This methods checks wether there is something like A and !A in a set, if
   * such an occurance is found, the whole set is converted to a set with either a false or a true item.
   * For or combined items, this would be true, for and combined
   * sets, it would be false.
   * If there already are sets in the outer set, this set could be eliminated
   * altogether.
   */
  static void eliminateNullItems(const ItemSetOfSets& source, ItemSetOfSets& target, bool orSet);

#ifdef COPASI_DEBUG
  static void printSetOfSets(const ItemSetOfSets& set);
  static void printSetSizes(const ItemSetOfSets& set);
  static void printSetElement(const ItemSetOfSets& set, unsigned int index1, unsigned int index2);
#endif // COPASI_DEBUG
};

std::ostream& operator<<(std::ostream& os, const CNormalLogical& logical);

#endif /* CNormalLogical */
