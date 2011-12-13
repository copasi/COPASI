// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CLabel.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/12/13 19:49:57 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CLabel.h"

#include "copasi.h"

#include "copasi/report/CCopasiRootContainer.h"

CLabel::CLabel()
    : CLTextGlyph()
{
  initOrigValues();
}

CLabel::CLabel(const CLTextGlyph & tg)
    : CLTextGlyph(tg)
{
  initOrigValues();
}

CLabel::CLabel(const CLabel & l)
    : CLTextGlyph(l)
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
      CCopasiObject* pObject = CCopasiRootContainer::getKeyFactory()->get(this->mModelObjectKey);

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


