// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CNormalItem_H__
#define COPASI_CNormalItem_H__

#include <string>
#include "copasi/compareExpressions/CNormalBase.h"

/**
 * The class for items used in CNormal
 */
class CNormalItem : public CNormalBase
  {
  public:
    /**
     * Enumeration of possible item types.
     */
    enum Type
    {
      CONSTANT,
      VARIABLE
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

    CNormalBase * copy() const override;

    /**
     * Copy contructor
     */
    CNormalItem(const CNormalItem& src);

    /**
     * Assignment operator
     */
    CNormalItem& operator=(const CNormalItem& src);

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

    std::string toString() const override;

    bool simplify() override {return true;};

    friend std::ostream & operator<< (std::ostream &os,
                                      const CNormalItem & d);
  };

#endif // COPASI_CNormalItem_H__
