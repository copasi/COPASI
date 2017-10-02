// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QCOPASI_GRAPHICS_ITEM
#define QCOPASI_GRAPHICS_ITEM

#define COPASI_OBJECT_CN 1
#define COPASI_LAYOUT_KEY 2

class CLStyle;
class CLRenderResolver;
class CQCopasiGraphicsItem
{
public:
  CQCopasiGraphicsItem(const CLRenderResolver* resolver, const CLStyle* style);
  virtual ~CQCopasiGraphicsItem();
  void setResolver(const CLRenderResolver* resolver);
  const CLRenderResolver* getResolver() const;
  void setStyle(const CLStyle* style);
  const CLStyle* getStyle() const;
  bool isValid() const;
protected:
  const CLStyle* mpStyle;
  const CLRenderResolver* mpResolver;
  bool mIsValid;
};

#endif
