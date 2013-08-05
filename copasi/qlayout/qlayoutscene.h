#ifndef QLAYOUT_SCENE_H
#define QLAYOUT_SCENE_H

#include <QGraphicsScene>

#include <string>

class CLayout;
class CLGraphicalObject;
class CLRenderResolver;
class CCopasiDataModel;
class CLRenderInformationBase;

class QLayoutScene: public QGraphicsScene
{
  Q_OBJECT
public:
  QLayoutScene(CLayout *layout, CCopasiDataModel* model=NULL, CLRenderInformationBase* renderInformation=NULL);
  virtual ~QLayoutScene();
  void setResolver(const CLRenderResolver* resolver);
  const CLRenderResolver* getResolver() const;
  void saveToFile(const std::string& fileName, const std::string& fileType = "pdf");
  void setLayout(CLayout *layout, CCopasiDataModel* model=NULL, CLRenderInformationBase* renderInformation=NULL);
  void setRenderInformation(CCopasiDataModel* model, CLRenderInformationBase* renderInformation);
public slots:
  void recreate();
protected:
  void dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
  void initializeResolver(CCopasiDataModel* model, CLRenderInformationBase* renderInformation);
private: 
  void addGlyph(const CLGraphicalObject* go);
  void fillFromLayout(const CLayout* layout);
  
  CLayout* mpLayout;
  CLRenderInformationBase* mpRender;
  const CLRenderResolver* mpResolver;
};

#endif