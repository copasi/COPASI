// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <qlayout/qcopasigraphicsitem.h>
#include <layout/CLStyle.h>
#include <layout/CLRenderResolver.h>

CQCopasiGraphicsItem::~CQCopasiGraphicsItem()
{
}

CQCopasiGraphicsItem::CQCopasiGraphicsItem(const CLRenderResolver* resolver, const CLStyle* style)
  : mpStyle(style)
  , mpResolver(resolver)
{
}

void CQCopasiGraphicsItem::setResolver(const CLRenderResolver* resolver)
{
  mpResolver = resolver;
}

const CLRenderResolver* CQCopasiGraphicsItem::getResolver() const
{
  return mpResolver;
}

void CQCopasiGraphicsItem::setStyle(const CLStyle* style)
{
  mpStyle = style;
}

const CLStyle* CQCopasiGraphicsItem::getStyle() const
{
  return mpStyle;
}
