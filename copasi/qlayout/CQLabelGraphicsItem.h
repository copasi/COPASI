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

#ifndef QLABEL_GRAPHICS_ITEM
#define QLABEL_GRAPHICS_ITEM

#include <QGraphicsTextItem>
#include <copasi/qlayout/CQCopasiGraphicsItem.h>

class CLTextGlyph;
class CLStyle;
class CQLabelGraphicsItem : public QGraphicsTextItem, public CQCopasiGraphicsItem
{
  Q_OBJECT
public:
  CQLabelGraphicsItem(const CLTextGlyph *textGlyph, const CLRenderResolver *resolver = NULL);
  virtual ~CQLabelGraphicsItem();
};

#endif
