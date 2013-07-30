#ifndef QLAYOUT_SCENE_H
#define QLAYOUT_SCENE_H

#include <QGraphicsScene>

class CLayout;
class CLGraphicalObject;
class CLRenderResolver;
class QLayoutScene: public QGraphicsScene
{
  Q_OBJECT
public:
  QLayoutScene(CLayout *layout);
  virtual ~QLayoutScene();
  void setResolver(const CLRenderResolver* resolver);
  const CLRenderResolver* getResolver() const;
public slots:
  void recreate();
protected:
  void dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
private: 
  void addGlyph(const CLGraphicalObject* go);
  void fillFromLayout(const CLayout* layout);
  
  CLayout* mpLayout;
  const CLRenderResolver* mpResolver;
};

#endif