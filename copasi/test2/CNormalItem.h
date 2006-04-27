/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/CNormalItem.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:32:06 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CNormalItem
#define COPASI_CNormalItem

#include "function/CEvaluationTree.h"
#include "function/CEvaluationNode.h"
#include "function/CEvaluationNodeOperator.h"
#include "function/CEvaluationNodeFunction.h"

#include "copasi.h"

/**
 * The class for items used in CNormal
 */
class CNormalItem
  {
  public:
    /**
     * Enumeration of possible item types.
     */
    enum Type
    {
      CONSTANT,
      VARIABLE,
      FUNCTION
    };

    std::string mName;
    Type mType;

    /**
     * Default constructor
     */
    CNormalItem();

    /**
     * Data constructor
     */
    CNormalItem(const std::string& name, const Type& type);

    /**
     * Copy contructor
     */
    CNormalItem(const CNormalItem& src);

    /**
     * Create an item from an evaluation node that need not be of specific type.
     * @return CNormalItem*, pointer to newly created item.
     */
    static CNormalItem* createItem(const CEvaluationNode* node);

    /**
     * Set the name of this item
     * @return true.
     */
    bool setName(const std::string& name);

    /**
     * Set the type of this item.
     * @return true.
     */
    bool setType(const Type& type);

    /**
     * Retrieve the name of this item.
     * @return mName
     */
    const std::string getName() const;

    /**
     * Retrieve the type of this item.
     * @return mType
     */
    const Type& getType() const;

    /**
     * Examine equality of two items.
     * @return bool.
     */
    bool operator==(const CNormalItem & rhs) const;

    /**
     * Examine inequality of two item.
     * @return bool.
     */
    bool operator<(const CNormalItem & rhs) const;

    friend std::ostream & operator<<(std::ostream &os,
                                     const CNormalItem & d);
  };

#endif // COPASI_CNormalItem
