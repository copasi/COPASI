// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QLAYOUT_SCENE_H
#define QLAYOUT_SCENE_H

#include <QtGui/QGraphicsScene>
#include <QtCore/QSharedPointer>

#include <string>
#include <map>

class CLayout;
class CLGraphicalObject;
class CLRenderResolver;
class CCopasiDataModel;
class CLRenderInformationBase;
class CQCopasiEffect;

class CQLayoutScene: public QGraphicsScene
{
  Q_OBJECT
public:
  CQLayoutScene(CLayout *layout, CCopasiDataModel* model = NULL, CLRenderInformationBase* renderInformation = NULL);
  virtual ~CQLayoutScene();
  void setResolver(CLRenderResolver* resolver);
  const CLRenderResolver* getResolver() const;
  void saveToFile(const std::string& fileName, const std::string& fileType = "pdf");
  void setLayout(CLayout *layout, CCopasiDataModel* model = NULL, CLRenderInformationBase* renderInformation = NULL);
  void setRenderInformation(CCopasiDataModel* model, CLRenderInformationBase* renderInformation);
  QGraphicsItem* getItemFor(const std::string& cn);
  const CLayout* getCurrentLayout() const;
  CLayout* getCurrentLayout();
  const CLRenderInformationBase* getCurrentRenderInfo() const;
  void updatePosition(const QString& key, const QPointF& newPos);
public slots:
  void recreate();
signals:
  void recreateNeeded();
protected:
  void initializeResolver(CCopasiDataModel* model, CLRenderInformationBase* renderInformation);
private:
  void addGlyph(const CLGraphicalObject* go);
  void fillFromLayout(const CLayout* layout);

  CLayout* mpLayout;
  CLRenderInformationBase* mpRender;
  QSharedPointer<CLRenderResolver> mpResolver;

  std::map< std::string, QGraphicsItem*> mItems;
};

#endif
