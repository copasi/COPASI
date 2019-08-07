// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include <sstream>

#include "copasi/copasi.h"

#include "CNormalCall.h"
#include "CNormalChoice.h"
#include "CNormalFunction.h"
#include "CNormalGeneralPower.h"
#include "CNormalItem.h"
#include "CNormalItemPower.h"
#include "CNormalLogical.h"

/**
 * Default constructor
 */
CNormalItemPower::CNormalItemPower(): CNormalBase(), mpItem(NULL), mExp(1.0), mItemType(CNormalItemPower::INVALID)
{}

/**
 * Copy Constructor
 */
CNormalItemPower::CNormalItemPower(const CNormalItemPower& src): CNormalBase(src), mpItem(NULL), mExp(src.mExp), mItemType(src.mItemType)
{
  if (this->mItemType != CNormalItemPower::INVALID)
    {
      this->mpItem = src.mpItem->copy();
    }
}

CNormalItemPower::~CNormalItemPower()
{
  if (this->mpItem != NULL) delete this->mpItem;
}

/**
 * Assignment operator Constructor
 */
CNormalItemPower& CNormalItemPower::operator=(const CNormalItemPower & src)
{
  if (this->mpItem != NULL) delete this->mpItem;

  this->mItemType = src.mItemType;

  if (this->mItemType != CNormalItemPower::INVALID)
    {
      this->mpItem = src.mpItem->copy();
    }
  else
    {
      this->mpItem = NULL;
    }

  mExp = src.mExp;
  return *this;
}

/**
 * Data constructor
 */
CNormalItemPower::CNormalItemPower(const CNormalBase& item, const C_FLOAT64& exp)
  : mpItem(NULL), mExp(exp), mItemType(CNormalItemPower::INVALID)
{
  if (!this->setItem(item))
    {
      this->mExp = 1.0;
    }
}

/**
 * Set the base of this itempower.
 * @return true.
 */
bool CNormalItemPower::setItem(const CNormalBase& item)
{
  bool result = true;

  if (dynamic_cast<const CNormalItem*>(&item))
    {
      if (this->mpItem != NULL) delete this->mpItem;

      this->mItemType = CNormalItemPower::ITEM;
      this->mpItem = item.copy();
    }
  else if (dynamic_cast<const CNormalFunction*>(&item))
    {
      if (this->mpItem != NULL) delete this->mpItem;

      this->mItemType = CNormalItemPower::FUNCTION;
      this->mpItem = item.copy();
    }
  else if (dynamic_cast<const CNormalGeneralPower*>(&item))
    {
      if (this->mpItem != NULL) delete this->mpItem;

      this->mItemType = CNormalItemPower::POWER;
      this->mpItem = item.copy();
    }
  else if (dynamic_cast<const CNormalChoice*>(&item))
    {
      if (this->mpItem != NULL) delete this->mpItem;

      this->mItemType = CNormalItemPower::CHOICE;
      this->mpItem = item.copy();
    }
  else if (dynamic_cast<const CNormalCall*>(&item))
    {
      if (this->mpItem != NULL) delete this->mpItem;

      this->mItemType = CNormalItemPower::CALL;
      this->mpItem = item.copy();
    }
  else if (dynamic_cast<const CNormalLogical*>(&item))
    {
      if (this->mpItem != NULL) delete this->mpItem;

      this->mItemType = CNormalItemPower::LOGICAL;
      this->mpItem = item.copy();
    }
  else
    {
      result = false;
    }

  return result;
}

/**
 * Set the exponent of this power
 * @return true
 */
bool CNormalItemPower::setExp(const C_FLOAT64& number)
{
  if (mExp < 0.0)
    return false;

  mExp = number;
  return true;
}

/**
 * Retrieve the base of this power
 * @return mItem
 */
CNormalBase& CNormalItemPower::getItem()
{
  return *mpItem;
}

/**
 * Retrieve the base of this power
 * @return mItem
 */
const CNormalBase& CNormalItemPower::getItem() const
{
  return *mpItem;
}

/**
 * Retrieve the exponent of this power
 * @return mExp
 */
const C_FLOAT64& CNormalItemPower::getExp() const
{
  return mExp;
}

/**
 * Examine equality of two item powers.
 * @return bool.
 */
bool CNormalItemPower::operator==(const CNormalItemPower & rhs) const
{
  bool result = (this->mItemType == rhs.mItemType);
  result &= (this->mExp == rhs.mExp);

  if (result == true)
    {
      switch (this->mItemType)
        {
          case CNormalItemPower::ITEM:
            result = (dynamic_cast<CNormalItem&>(*this->mpItem) == dynamic_cast<CNormalItem&>(*rhs.mpItem));
            break;

          case CNormalItemPower::FUNCTION:
            result = (dynamic_cast<CNormalFunction&>(*this->mpItem) == dynamic_cast<CNormalFunction&>(*rhs.mpItem));
            break;

          case CNormalItemPower::POWER:
            result = (dynamic_cast<CNormalGeneralPower&>(*this->mpItem) == dynamic_cast<CNormalGeneralPower&>(*rhs.mpItem));
            break;

          case CNormalItemPower::CHOICE:
            result = (dynamic_cast<CNormalChoice&>(*this->mpItem) == dynamic_cast<CNormalChoice&>(*rhs.mpItem));
            break;

          case CNormalItemPower::CALL:
            result = (dynamic_cast<CNormalCall&>(*this->mpItem) == dynamic_cast<CNormalCall&>(*rhs.mpItem));
            break;

          case CNormalItemPower::LOGICAL:
            result = (dynamic_cast<CNormalLogical&>(*this->mpItem) == dynamic_cast<CNormalLogical&>(*rhs.mpItem));
            break;

          case CNormalItemPower::INVALID:
            result = true;
            break;
        }
    }

  return result;
}

/**
 * Examine inequality of two item powers.
 * @return bool.
 */
bool CNormalItemPower::operator<(const CNormalItemPower & rhs) const
{
  bool result = false;

  if (this->mItemType < rhs.mItemType)
    {
      result = true;
    }
  else if (this->mItemType == rhs.mItemType)
    {
      switch (this->mItemType)
        {
          case CNormalItemPower::ITEM:
            result = (dynamic_cast<CNormalItem&>(*this->mpItem) < dynamic_cast<CNormalItem&>(*rhs.mpItem));

            if (!result)
              {
                result = !(dynamic_cast<CNormalItem&>(*rhs.mpItem) < dynamic_cast<CNormalItem&>(*this->mpItem));

                if (result)
                  {
                    result = (rhs.mExp < this->mExp);
                  }
              }

            break;

          case CNormalItemPower::FUNCTION:
            result = (dynamic_cast<CNormalFunction&>(*this->mpItem) < dynamic_cast<CNormalFunction&>(*rhs.mpItem));

            if (!result)
              {
                result = !(dynamic_cast<CNormalFunction&>(*rhs.mpItem) < dynamic_cast<CNormalFunction&>(*this->mpItem));

                if (result)
                  {
                    result = (rhs.mExp < this->mExp);
                  }
              }

            break;

          case CNormalItemPower::POWER:
            result = (dynamic_cast<CNormalGeneralPower&>(*this->mpItem) < dynamic_cast<CNormalGeneralPower&>(*rhs.mpItem));

            if (!result)
              {
                result = !(dynamic_cast<CNormalGeneralPower&>(*rhs.mpItem) < dynamic_cast<CNormalGeneralPower&>(*this->mpItem));

                if (result)
                  {
                    result = (rhs.mExp < this->mExp);
                  }
              }

            break;

          case CNormalItemPower::CHOICE:
            result = (dynamic_cast<CNormalChoice&>(*this->mpItem) < dynamic_cast<CNormalChoice&>(*rhs.mpItem));

            if (!result)
              {
                result = !(dynamic_cast<CNormalChoice&>(*rhs.mpItem) < dynamic_cast<CNormalChoice&>(*this->mpItem));

                if (result)
                  {
                    result = (rhs.mExp < this->mExp);
                  }
              }

            break;

          case CNormalItemPower::CALL:
            result = (dynamic_cast<CNormalCall&>(*this->mpItem) < dynamic_cast<CNormalCall&>(*rhs.mpItem));

            if (!result)
              {
                result = !(dynamic_cast<CNormalCall&>(*rhs.mpItem) < dynamic_cast<CNormalCall&>(*this->mpItem));

                if (result)
                  {
                    result = (rhs.mExp < this->mExp);
                  }
              }

            break;

          case CNormalItemPower::LOGICAL:
            result = (dynamic_cast<CNormalLogical&>(*this->mpItem) < dynamic_cast<CNormalLogical&>(*rhs.mpItem));

            if (!result)
              {
                result = !(dynamic_cast<CNormalLogical&>(*rhs.mpItem) < dynamic_cast<CNormalLogical&>(*this->mpItem));

                if (result)
                  {
                    result = (rhs.mExp < this->mExp);
                  }
              }

            break;

          case CNormalItemPower::INVALID:
            result = false;
            break;
        }
    }

  return result;
}

std::ostream & operator<< (std::ostream &os, const CNormalItemPower & d)
{
  os << d.toString();
  return os;
}

std::string CNormalItemPower::toString() const
{
  std::ostringstream os;

  if (this->mItemType == CNormalItemPower::ITEM || this->mItemType == CNormalItemPower::LOGICAL || this->mItemType == CNormalItemPower::FUNCTION || this->mItemType == CNormalItemPower::CALL || (this->mItemType == CNormalItemPower::POWER && this->mExp == 1.0))
    {
      os << this->mpItem->toString();
    }
  else
    {
      os << "(" << this->mpItem->toString() << ")";
    }

  if (this->mExp != 1.0)
    {
      os << "^" << this->mExp;
    }

  return os.str();
}

CNormalBase * CNormalItemPower::copy() const
{
  return new CNormalItemPower(*this);
}

CNormalItemPower::ItemType CNormalItemPower::getItemType() const
{
  return this->mItemType;
}

bool CNormalItemPower::simplify()
{
  return this->mpItem->simplify();
}
