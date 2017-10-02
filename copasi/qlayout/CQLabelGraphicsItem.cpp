// Copyright (C) 2013 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <qlayout/CQLabelGraphicsItem.h>
#include <qlayout/CQRenderConverter.h>
#include <layout/CLGlyphs.h>
#include <layout/CLRenderResolver.h>
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
