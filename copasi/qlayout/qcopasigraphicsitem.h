#ifndef QCOPASI_GRAPHICS_ITEM
#define QCOPASI_GRAPHICS_ITEM

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