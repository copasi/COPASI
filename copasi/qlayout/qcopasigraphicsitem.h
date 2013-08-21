// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QCOPASI_GRAPHICS_ITEM
#define QCOPASI_GRAPHICS_ITEM

#define COPASI_OBJECT_CN 1
#define COPASI_LAYOUT_KEY 2

class CLStyle;
class CLRenderResolver;
class QCopasiGraphicsItem
{
public:
  QCopasiGraphicsItem(const CLRenderResolver* resolver, const CLStyle* style);
  virtual ~QCopasiGraphicsItem();
  void setResolver(const CLRenderResolver* resolver);
  const CLRenderResolver* getResolver() const;
  void setStyle(const CLStyle* style);
  const CLStyle* getStyle() const;
protected:
  const CLStyle* mpStyle;
  const CLRenderResolver* mpResolver;
};

#endif
