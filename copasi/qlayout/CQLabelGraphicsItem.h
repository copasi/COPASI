// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QLABEL_GRAPHICS_ITEM
#define QLABEL_GRAPHICS_ITEM

#include <QGraphicsTextItem>
#include <qlayout/CQCopasiGraphicsItem.h>

class CLTextGlyph;
class CLStyle;
class CQLabelGraphicsItem : public QGraphicsTextItem, public CQCopasiGraphicsItem
{
  Q_OBJECT
public:
  CQLabelGraphicsItem(const CLTextGlyph* textGlyph, const CLRenderResolver* resolver = NULL);
  virtual ~CQLabelGraphicsItem();
};

#endif
