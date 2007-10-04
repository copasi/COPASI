// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalLogical.h,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/10/04 12:02:33 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CNormalLogical_H__
#define CNormalLogical_H__

#include "compareExpressions/CNormalBase.h"
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <utility>

class CNormalLogicalItem;
class CNormalChoiceLogical;

class CNormalLogical : public CNormalBase
  {
  public:
    //std::string debug() const;
    //std::set<const CNormalLogical*> findLogicals() const;

    template<typename TYPE>
    class SetSorter
      {
      public:
        /**
         * This routine compares a set and returns true if the first
         * argument is smaller than the second.
         */
        bool operator()(const std::pair<TYPE*, bool>& lhs, const std::pair<TYPE*, bool>& rhs) const;

        /**
         * This routine compares a set and returns true if the first
         * argument is equal to the second.
         */
        bool isEqual(const std::pair<TYPE*, bool>& lhs, const std::pair<TYPE*, bool>& rhs) const;
      };

    template<typename TYPE>
    class SetOfSetsSorter
      {
      public:
        /**
         * This routine compares a set of sets and returns true if the first
         * argument is smaller than the second.
         */
        bool operator()(const std::pair<std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >, bool>& lhs, const std::pair<std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >, bool>& rhs) const;

        /**
         * This routine compares a set of sets and returns true if the first
         * argument is smaller than the second.
         */
        bool isEqual(const std::pair<std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >, bool>& lhs, const std::pair<std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >, bool>& rhs) const;
      };

    typedef std::set<std::pair<std::set<std::pair<CNormalChoiceLogical*, bool>, SetSorter<CNormalChoiceLogical> >, bool>, SetOfSetsSorter<CNormalChoiceLogical> > ChoiceSetOfSets;
    typedef std::set<std::pair<std::set<std::pair<CNormalLogicalItem*, bool>, SetSorter<CNormalLogicalItem> >, bool>, SetOfSetsSorter<CNormalLogicalItem> > ItemSetOfSets;
    typedef std::set<std::pair<CNormalChoiceLogical*, bool>, SetSorter<CNormalChoiceLogical> > ChoiceSet;
    typedef std::set<std::pair<CNormalLogicalItem*, bool>, SetSorter<CNormalLogicalItem> > ItemSet;

  protected:
    /**
     * Flag to specify wether the whole logical expression has to be
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
    static void cleanSetOfSets(std::set<std::pair<std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >, bool>, SetOfSetsSorter<TYPE> >& s);

    /**
     * This routine makes a deep copy of all elements in the souce set and
     * appends them to the target set.
     */
    template<typename TYPE>
    static void copySet(const std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >& source, std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >& target);

    /**
     * This routine calls delete an all pointers in the set.
     */
    template<typename TYPE>
    static void cleanSet(std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >& s);

  protected:
    /**
     * Negates a set of elements.
     * The result of the operation is returned in target.
     * The type of result depends on the source. If the source was a set of AND
     * combined elements, the result is a set of OR combined elements and vice versa.
     * target set.
     */
    template<typename TYPE>
    static bool negateSets(const std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >& source, std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >& target);

    /**
     * Negates a set of sets with elements.
     * The result of the operation is returned in target.
     * The type of the result depends on the source.
     * If the source was a set of AND combined sets of OR combined
     * elements, the rersult will be a set of OR combined sets with AND combined
     * elements.
     */
    template<typename TYPE>
    static bool negateSetOfSets(const std::set<std::pair<std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >, bool>, SetOfSetsSorter<TYPE> >& source, std::set<std::pair<std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >, bool>, SetOfSetsSorter<TYPE> >& target);

    /**
     * Converts a set of AND combined sets of OR combined elements into a
     * target set of OR combined sets of AND combined elements.
     */
    template<typename TYPE, typename SETSORTER, typename SETOFSETSSORTER>
    static bool convertAndOrToOrAnd(const std::set<std::pair<std::set<std::pair<TYPE*, bool>, SETSORTER >, bool>, SETOFSETSSORTER >& source, std::set<std::pair<std::set<std::pair<TYPE*, bool>, SETSORTER >, bool>, SETOFSETSSORTER >& target);

    /**
     * This routine makes deep copies of all inner sets and appends them to
     * the target set.
     */
    template<typename TYPE>
    static void copySetOfSets(const std::set<std::pair<std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >, bool>, SetOfSetsSorter<TYPE> >& source, std::set<std::pair<std::set<std::pair<TYPE*, bool>, SetSorter<TYPE> >, bool>, SetOfSetsSorter<TYPE> >& target);

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
