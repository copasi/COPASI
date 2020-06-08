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

#include "CLabel.h"

#include "copasi/copasi.h"

#include "copasi/core/CRootContainer.h"

CLabel::CLabel()
  : CLTextGlyph()
{
  initOrigValues();
}

CLabel::CLabel(const CLTextGlyph & tg)
  : CLTextGlyph(tg, NO_PARENT)
{
  initOrigValues();
}

CLabel::CLabel(const CLabel & l)
  : CLTextGlyph(l, NO_PARENT)
{
  initOrigValues();
}

void CLabel::initOrigValues()
{
  orig_x = this->getX();
  orig_y = this->getY();
  orig_width = this->getWidth();
  orig_height = this->getHeight();
}

// scale original values (not the current position/dimensions)
void CLabel::scale(const double & scaleFactor)
{
  this->setX(this->orig_x * scaleFactor);
  this->setY(this->orig_y * scaleFactor);
  this->setWidth(this->orig_width * scaleFactor);
  this->setHeight(this->orig_height * scaleFactor);
}

// set height of mBBox to new value given by the only parameter and scale width of box
// so that ration is preserved
void CLabel::adaptToHeight(const double & h)
{
  C_FLOAT64 scaleFactor = h / mBBox.getDimensions().getHeight();
  C_FLOAT64 w = mBBox.getDimensions().getWidth() * scaleFactor;
  mBBox.setDimensions(CLDimensions(w, h));
}

void CLabel::scalePosition(const double & z)
{
  this->mBBox.getPosition().setX(this->mBBox.getPosition().getX() * z);
  this->mBBox.getPosition().setY(this->mBBox.getPosition().getY() * z);
}
/**
 * Since labels are not part of the model, we can't use the new method for
 * getting the text but have to fall back to the old
 * behavior.
 * Hopefully I can get rid of this implementation sonner than later.
 */
std::string CLabel::getText() const
{
  if (mIsTextSet)
    {
      return mText;
    }
  else
    {
      CDataObject* pObject = CRootContainer::getKeyFactory()->get(this->mModelObjectKey);

      if (pObject)
        {
          return pObject->getObjectName();
        }
      else
        {
          return "unset";
        }
    }
}
