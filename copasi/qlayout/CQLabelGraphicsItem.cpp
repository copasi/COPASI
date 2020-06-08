// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <copasi/qlayout/CQLabelGraphicsItem.h>
#include <copasi/qlayout/CQRenderConverter.h>

#include "copasi/copasi.h"

#include <copasi/layout/CLGlyphs.h>
#include <copasi/layout/CLRenderResolver.h>
#include <copasi/UI/qtUtilities.h>

CQLabelGraphicsItem::CQLabelGraphicsItem(const CLTextGlyph* textGlyph, const CLRenderResolver* resolver)
  : QGraphicsTextItem(FROM_UTF8(textGlyph->getText()))
  , CQCopasiGraphicsItem(resolver, resolver != NULL ? resolver->resolveStyle(textGlyph) : NULL)
{
  //setTextInteractionFlags(Qt::TextEditorInteraction);
  //setFlag(QGraphicsItem::ItemIsMovable);
  //setFlag(QGraphicsItem::ItemIsSelectable);

  setPos(textGlyph->getBoundingBox().getPosition().getX(),
         textGlyph->getBoundingBox().getPosition().getY());

  mIsValid = CQRenderConverter::applyStyle(this, &textGlyph->getBoundingBox(), mpStyle == NULL ? NULL : mpStyle->getGroup(), mpResolver);
}

CQLabelGraphicsItem::~CQLabelGraphicsItem()
{
}
